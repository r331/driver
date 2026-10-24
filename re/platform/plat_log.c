/* plat_log.c — RE_LOG, the unified debug logger (v2.37); see plat_log.h and docs/DIAGNOSTICS.md («RE_LOG»).
   Plain C (no SDL): POSIX threads / signals on Linux and macOS, SRW lock on Windows.  Native build only.

   Off unless RE_LOG (or driver.cfg "log = ...") turns a channel on: then nothing is opened, no handler is
   installed and the macros never call in here, so a run without RE_LOG behaves exactly as before.

   One line per message, written whole under a mutex (the audio callback runs on its own thread):
       "    1234 ms f56     game    INFO  text"      (+ " [tN]" after the level for a thread other than the first)
   error / warn lines are flushed at once, others at least once a second and at exit.  Identical consecutive lines
   collapse into "(previous line repeated N more times)"; more than RE_LOG_RATE lines per second from one call site
   (one format string) are dropped and counted ("suppressed N lines").  The file is rotated to <file>.1 when it
   exceeds RE_LOG_MAX_MB. */
#if defined(__linux__) && !defined(_GNU_SOURCE)
#define _GNU_SOURCE
#endif
#include "plat_log.h"
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <time.h>
#include <signal.h>
#include <sys/stat.h>
#if defined(_WIN32)
#  include <windows.h>
#  include <direct.h>
#  include <process.h>
#  define log_mkdir(p) _mkdir(p)
#  define log_pid()    _getpid()
typedef SRWLOCK log_mutex;
#  define LOG_MUTEX_INIT SRWLOCK_INIT
static void mx_lock(log_mutex *m)    { AcquireSRWLockExclusive(m); }
static void mx_unlock(log_mutex *m)  { ReleaseSRWLockExclusive(m); }
static int  mx_trylock(log_mutex *m) { return TryAcquireSRWLockExclusive(m) ? 0 : -1; }
#else
#  include <pthread.h>
#  include <unistd.h>
#  define log_mkdir(p) mkdir(p, 0755)
#  define log_pid()    getpid()
typedef pthread_mutex_t log_mutex;
#  define LOG_MUTEX_INIT PTHREAD_MUTEX_INITIALIZER
static void mx_lock(log_mutex *m)    { pthread_mutex_lock(m); }
static void mx_unlock(log_mutex *m)  { pthread_mutex_unlock(m); }
static int  mx_trylock(log_mutex *m) { return pthread_mutex_trylock(m); }
#endif

int plat_frame_no(void);   /* plat.h (platform/sdl/plat_sys.c): number of the last shown frame */

#define RE_LOG_VERSION "v2.37"
#define LINE_MAX_CHARS 1024
#define RATE_SLOTS 256

unsigned char re_log_level_of[RE_LC_COUNT];

static const char *const ch_names[RE_LC_COUNT] = { "sys", "load", "game", "mission", "render", "audio", "input", "mem", "save" };
static const char *const lv_names[6] = { "OFF", "ERROR", "WARN", "INFO", "DEBUG", "TRACE" };

static log_mutex g_mx = LOG_MUTEX_INIT;
static struct {
    int      started;          /* time origin taken */
    int      env_spec;         /* RE_LOG was set: driver.cfg "log" is ignored */
    int      to_stderr;        /* RE_LOG_STDERR=1 */
    int      no_file;          /* RE_LOG_FILE=- / stderr */
    int      opened;           /* tried to open the file */
    int      hooks;            /* atexit / signal handlers installed */
    int      closed;
    FILE    *f;
    char     path[1200];
    char     want_path[1024];  /* RE_LOG_FILE */
    char     exe_dir[1024];
    char     spec[256];
    char     bad[64];          /* first bad token of the last spec */
    int      bad_count;
    long     max_bytes;
    long     written;
    unsigned last_flush;
    int      rate;             /* lines per second per call site, 0 — unlimited */
    int      next_tid;
    /* identical consecutive lines */
    int      last_ch, last_lv;
    char     last_text[LINE_MAX_CHARS];
    unsigned last_rep;
    /* per call site (format pointer) budget */
    struct { const char *fmt; unsigned sec; unsigned n, dropped; int ch, lv; } rl[RATE_SLOTS];
} L = { .rate = 200, .max_bytes = 64L * 1024 * 1024, .last_ch = -1 };

#if defined(_WIN32)
static __declspec(thread) int tl_tid = -1;
#else
static __thread int tl_tid = -1;
#endif

/* ---- clock ---- */
static unsigned (*g_test_clock)(void);
#if defined(_WIN32)
static LARGE_INTEGER g_t0, g_freq;
static void clock_start(void) { QueryPerformanceFrequency(&g_freq); QueryPerformanceCounter(&g_t0); }
static unsigned clock_ms(void) {
    if (g_test_clock) return g_test_clock();
    LARGE_INTEGER n; QueryPerformanceCounter(&n);
    return (unsigned)((n.QuadPart - g_t0.QuadPart) * 1000 / (g_freq.QuadPart ? g_freq.QuadPart : 1));
}
#else
static struct timespec g_t0;
static void clock_start(void) { clock_gettime(CLOCK_MONOTONIC, &g_t0); }
static unsigned clock_ms(void) {
    if (g_test_clock) return g_test_clock();
    struct timespec n; clock_gettime(CLOCK_MONOTONIC, &n);
    return (unsigned)((n.tv_sec - g_t0.tv_sec) * 1000 + (n.tv_nsec - g_t0.tv_nsec) / 1000000);
}
#endif
static void ensure_started(void) { if (!L.started) { L.started = 1; clock_start(); } }

const char *re_log_channel_name(int ch) { return ch >= 0 && ch < RE_LC_COUNT ? ch_names[ch] : "?"; }
const char *re_log_path(void) { return L.path; }
int re_log_enabled(void) { for (int i = 0; i < RE_LC_COUNT; i++) if (re_log_level_of[i]) return 1; return 0; }

/* ---- spec parsing: "all:info,render:debug,audio:off", "debug", "1", "game,mission:trace" ---- */
static int ieq(const char *a, const char *b) {
    for (; *a && *b; a++, b++) { int x = *a, y = *b; if (x >= 'A' && x <= 'Z') x += 32; if (y >= 'A' && y <= 'Z') y += 32; if (x != y) return 0; }
    return *a == *b;
}
static int parse_level(const char *s) {
    static const char *const names[][4] = { { "off", "none", "0", "no" }, { "error", "err", "e", "1" }, { "warn", "warning", "w", "2" },
                                            { "info", "i", "3", "on" }, { "debug", "d", "4", "dbg" }, { "trace", "t", "5", "all" } };
    for (int l = 0; l < 6; l++) for (int k = 0; k < 4; k++) if (ieq(s, names[l][k])) return l;
    return -1;
}
static int parse_channel(const char *s) {   /* -2 — all */
    if (ieq(s, "all") || ieq(s, "*")) return -2;
    for (int c = 0; c < RE_LC_COUNT; c++) if (ieq(s, ch_names[c])) return c;
    return -1;
}
int re_log_parse(const char *spec, unsigned char *lv, char *bad, int badn) {
    int errs = 0;
    for (int c = 0; c < RE_LC_COUNT; c++) lv[c] = RE_LV_OFF;
    if (bad && badn > 0) bad[0] = 0;
    if (!spec) return 0;
    const char *p = spec;
    while (*p) {
        while (*p == ',' || *p == ';' || *p == ' ' || *p == '\t') p++;
        if (!*p) break;
        char tok[64]; int n = 0;
        while (*p && *p != ',' && *p != ';' && *p != ' ' && *p != '\t') { if (n < (int)sizeof tok - 1) tok[n++] = *p; p++; }
        tok[n] = 0;
        char *colon = strchr(tok, ':'); if (!colon) colon = strchr(tok, '=');
        int ch, l;
        if (colon) {
            *colon = 0; ch = parse_channel(tok); l = parse_level(colon + 1);
            if (l == 5 && ieq(colon + 1, "all")) l = -1;   /* "all" is a level only on its own */
        } else if (ieq(tok, "1") || ieq(tok, "on") || ieq(tok, "yes") || ieq(tok, "true")) {
            ch = -2; l = RE_LV_INFO;                            /* RE_LOG=1 — everything at info */
        } else {
            l = parse_level(tok);
            if (l >= 0 && !ieq(tok, "all")) ch = -2;       /* "debug" — every channel */
            else if (ieq(tok, "all")) { ch = -2; l = RE_LV_INFO; }
            else { ch = parse_channel(tok); l = RE_LV_INFO; }   /* "game" — that channel at info */
        }
        if (ch == -1 || l < 0) {
            if (bad && badn > 0 && errs == 0) { if (colon) *colon = ':'; snprintf(bad, (size_t)badn, "%s", tok); }
            errs++; continue;
        }
        if (ch == -2) for (int c = 0; c < RE_LC_COUNT; c++) lv[c] = (unsigned char)l;
        else lv[ch] = (unsigned char)l;
    }
    return errs;
}

/* ---- file ---- */
static void header_locked(void);
static void install_hooks(void);
#if defined(__APPLE__)
static int mkdirs(const char *dir) {
    char d[1024]; snprintf(d, sizeof d, "%s", dir);
    for (char *c = d + 1; *c; c++) if (*c == '/') { *c = 0; log_mkdir(d); *c = '/'; }
    return log_mkdir(d);
}
#endif
static FILE *try_open(const char *p) { FILE *f = fopen(p, "w"); if (f) snprintf(L.path, sizeof L.path, "%s", p); return f; }
static void open_locked(void) {
    if (L.opened) return;
    L.opened = 1;
    if (L.no_file) return;
    char p[1100];
    if (L.want_path[0]) L.f = try_open(L.want_path);
#if defined(__APPLE__)
    if (!L.f && !L.want_path[0]) {
        const char *home = getenv("HOME");
        if (home && *home) { snprintf(p, sizeof p, "%s/Library/Logs/Driver", home); mkdirs(p); snprintf(p, sizeof p, "%s/Library/Logs/Driver/driver.log", home); L.f = try_open(p); }
    }
#endif
    if (!L.f && L.exe_dir[0]) {
        size_t n = strlen(L.exe_dir);
        snprintf(p, sizeof p, "%s%sdriver.log", L.exe_dir, (L.exe_dir[n - 1] == '/' || L.exe_dir[n - 1] == '\\') ? "" : "/");
        L.f = try_open(p);
    }
    if (!L.f) L.f = try_open("driver.log");
    if (!L.f) { L.path[0] = 0; L.to_stderr = 1; fprintf(stderr, "[log] RE_LOG: не удалось открыть файл журнала (%s) — пишу в stderr\n", strerror(errno)); return; }
    setvbuf(L.f, NULL, _IOFBF, 1 << 16);
    fprintf(stderr, "[log] RE_LOG: журнал %s\n", L.path);
    header_locked();
}
static void header_locked(void) {
    if (!L.f) return;
    time_t t = time(NULL); char ts[64]; strftime(ts, sizeof ts, "%Y-%m-%d %H:%M:%S", localtime(&t));
    char lv[RE_LC_COUNT * 16] = ""; size_t n = 0;
    for (int c = 0; c < RE_LC_COUNT; c++) n += (size_t)snprintf(lv + n, sizeof lv - n, "%s%s:%s", c ? "," : "", ch_names[c], lv_names[re_log_level_of[c]]);
    int k = fprintf(L.f, "# Driver RE_LOG %s, %s, pid %d, RE_LOG=\"%s\" -> %s\n# колонки: мс от старта, f<кадр>, канал, уровень[, поток], сообщение\n",
                    RE_LOG_VERSION, ts, (int)log_pid(), L.spec, lv);
    if (k > 0) L.written += k;
    fflush(L.f);
}
static void rotate_locked(void) {
    if (!L.f || !L.path[0]) return;
    fprintf(L.f, "# лимит размера журнала (%ld байт) — продолжение в новом файле, старый: %s.1\n", L.max_bytes, L.path);
    fclose(L.f); L.f = NULL;
    char old[1300]; snprintf(old, sizeof old, "%s.1", L.path);
    remove(old); rename(L.path, old);
    L.f = fopen(L.path, "w"); L.written = 0;
    if (L.f) { setvbuf(L.f, NULL, _IOFBF, 1 << 16); fprintf(L.f, "# Driver RE_LOG %s — продолжение после ротации (предыдущая часть: %s.1)\n", RE_LOG_VERSION, L.path); }
}

/* ---- writing ---- */
static void put_locked(const char *line, size_t len, int lv, unsigned now) {
    if (!L.opened) open_locked();
    if (L.f) {
        fwrite(line, 1, len, L.f); L.written += (long)len;
        if (lv <= RE_LV_WARN || now - L.last_flush >= 1000u) { fflush(L.f); L.last_flush = now; }
        if (L.max_bytes > 0 && L.written > L.max_bytes) rotate_locked();
    }
    if (L.to_stderr) fwrite(line, 1, len, stderr);
}
static size_t format_line(char *out, size_t cap, unsigned now, int frame, int ch, int lv, int tid, const char *text) {
    char tt[16] = "";
    if (tid > 0) snprintf(tt, sizeof tt, " [t%d]", tid);
    int n = snprintf(out, cap, "%8u ms f%-6d %-7s %-5s%s %s\n", now, frame, re_log_channel_name(ch), lv_names[lv], tt, text);
    if (n < 0) return 0;
    if ((size_t)n >= cap) { out[cap - 2] = '\n'; out[cap - 1] = 0; return cap - 1; }
    return (size_t)n;
}
static void note_locked(int ch, int lv, unsigned now, int frame, const char *fmt, ...) RE_LOG_PRINTF(5, 6);
static void note_locked(int ch, int lv, unsigned now, int frame, const char *fmt, ...) {
    char text[LINE_MAX_CHARS], line[LINE_MAX_CHARS + 64];
    va_list a; va_start(a, fmt); vsnprintf(text, sizeof text, fmt, a); va_end(a);
    size_t n = format_line(line, sizeof line, now, frame, ch, lv, 0, text);
    put_locked(line, n, lv, now);
}
static void flush_repeat_locked(unsigned now, int frame) {
    if (L.last_rep) { note_locked(L.last_ch, L.last_lv, now, frame, "(предыдущая строка повторена ещё %u раз)", L.last_rep); L.last_rep = 0; }
}
static void flush_dropped_locked(unsigned now, int frame, int all) {
    for (int i = 0; i < RATE_SLOTS; i++)
        if (L.rl[i].fmt && L.rl[i].dropped && (all || L.rl[i].sec != now / 1000u)) {
            char f[96]; snprintf(f, sizeof f, "%s", L.rl[i].fmt);
            for (char *c = f; *c; c++) if (*c == '\n') *c = ' ';
            note_locked(L.rl[i].ch, L.rl[i].lv, now, frame, "(ограничение частоты: подавлено %u строк «%s»)", L.rl[i].dropped, f);
            L.rl[i].dropped = 0;
        }
}
/* 1 — over the budget of this call site in the current second (counted as dropped). */
static int rate_drop_locked(const char *fmt, int ch, int lv, unsigned now, int frame) {
    if (L.rate <= 0) return 0;
    unsigned h = (unsigned)(((uintptr_t)fmt >> 3) * 2654435761u) % RATE_SLOTS, sec = now / 1000u;
    for (int k = 0; k < RATE_SLOTS; k++) {
        unsigned i = (h + (unsigned)k) % RATE_SLOTS;
        if (L.rl[i].fmt == NULL) { L.rl[i].fmt = fmt; L.rl[i].sec = sec; L.rl[i].n = 1; L.rl[i].dropped = 0; L.rl[i].ch = ch; L.rl[i].lv = lv; return 0; }
        if (L.rl[i].fmt != fmt) continue;
        if (L.rl[i].sec != sec) {
            if (L.rl[i].dropped) {
                char f[96]; snprintf(f, sizeof f, "%s", fmt); for (char *c = f; *c; c++) if (*c == '\n') *c = ' ';
                note_locked(ch, lv, now, frame, "(ограничение частоты: подавлено %u строк «%s»)", L.rl[i].dropped, f);
                L.rl[i].dropped = 0;
            }
            L.rl[i].sec = sec; L.rl[i].n = 0;
        }
        if (++L.rl[i].n > (unsigned)L.rate) { L.rl[i].dropped++; return 1; }
        return 0;
    }
    return 0;   /* table full — no limit */
}

void re_logv(int ch, int lv, const char *fmt, va_list ap) {
    if (ch < 0 || ch >= RE_LC_COUNT || lv < RE_LV_ERROR || lv > RE_LV_TRACE || !fmt) return;
    if (re_log_level_of[ch] < lv || L.closed) return;
    ensure_started();
    char text[LINE_MAX_CHARS], line[LINE_MAX_CHARS + 64];
    vsnprintf(text, sizeof text, fmt, ap);
    size_t tl = strlen(text);
    while (tl && (text[tl - 1] == '\n' || text[tl - 1] == '\r')) text[--tl] = 0;   /* "…\n" of the printf-style sources */
    for (char *c = text; *c; c++) if (*c == '\n' || *c == '\r') *c = ' ';
    unsigned now = clock_ms(); int frame = plat_frame_no();
    mx_lock(&g_mx);
    if (tl_tid < 0) tl_tid = L.next_tid++;
    if (ch == L.last_ch && lv == L.last_lv && !strcmp(text, L.last_text)) {
        if (++L.last_rep % 10000u == 0) flush_repeat_locked(now, frame);
        mx_unlock(&g_mx); return;
    }
    if (rate_drop_locked(fmt, ch, lv, now, frame)) { mx_unlock(&g_mx); return; }
    flush_repeat_locked(now, frame);
    L.last_ch = ch; L.last_lv = lv; memcpy(L.last_text, text, tl + 1);
    size_t n = format_line(line, sizeof line, now, frame, ch, lv, tl_tid, text);
    put_locked(line, n, lv, now);
    mx_unlock(&g_mx);
}
void re_log(int ch, int lv, const char *fmt, ...) { va_list a; va_start(a, fmt); re_logv(ch, lv, fmt, a); va_end(a); }

void re_log_flush(void) {
    if (!L.opened) return;
    unsigned now = clock_ms(); int frame = plat_frame_no();
    mx_lock(&g_mx);
    flush_repeat_locked(now, frame); flush_dropped_locked(now, frame, 1);
    L.last_ch = -1;
    if (L.f) fflush(L.f);
    if (L.to_stderr) fflush(stderr);
    mx_unlock(&g_mx);
}
void re_log_shutdown(const char *why) {
    if (!L.opened || L.closed) return;
    unsigned now = clock_ms(); int frame = plat_frame_no();
    mx_lock(&g_mx);
    flush_repeat_locked(now, frame); flush_dropped_locked(now, frame, 1);
    if (re_log_level_of[RE_LC_sys] >= RE_LV_INFO) note_locked(RE_LC_sys, RE_LV_INFO, now, frame, "журнал закрыт: %s", why ? why : "выход");
    if (L.f) { fflush(L.f); fclose(L.f); L.f = NULL; }
    L.closed = 1;
    mx_unlock(&g_mx);
}
static void at_exit(void) { re_log_shutdown("выход процесса (atexit)"); }

/* Signal path: no allocation, never waits for the lock (the crash may be inside a locked write). */
void re_log_crash(int sig) {
    if (!L.opened || L.closed) return;
    int locked = mx_trylock(&g_mx) == 0;
    char line[160];
    int n = snprintf(line, sizeof line, "%8u ms f%-6d %-7s %-5s сигнал %d — аварийное завершение, журнал сброшен\n", clock_ms(), plat_frame_no(), "sys", "ERROR", sig);
    if (L.f && n > 0) { fwrite(line, 1, (size_t)n, L.f); fflush(L.f); }
    if (L.to_stderr && n > 0) { fwrite(line, 1, (size_t)n, stderr); }
    if (locked) mx_unlock(&g_mx);
}

#if !defined(_WIN32)
static struct sigaction g_old[32];
static const int g_sigs[] = { SIGINT, SIGTERM, SIGABRT, SIGSEGV, SIGBUS, SIGFPE, SIGILL };
static void on_signal(int sig) {
    re_log_crash(sig);
    if (sig > 0 && sig < 32) sigaction(sig, &g_old[sig], NULL); else signal(sig, SIG_DFL);
    raise(sig);
}
#else
static void on_signal(int sig) { re_log_crash(sig); signal(sig, SIG_DFL); raise(sig); }
#endif
static void install_hooks(void) {
    if (L.hooks) return;
    L.hooks = 1;
    atexit(at_exit);
#if !defined(_WIN32)
    for (unsigned i = 0; i < sizeof g_sigs / sizeof g_sigs[0]; i++) {
        int s = g_sigs[i]; struct sigaction cur;
        if (s == SIGILL) continue;   /* Mesa probes CPU features through SIGILL (see plat_sys.c) — leave it alone */
        if (sigaction(s, NULL, &cur) != 0 || cur.sa_handler != SIG_DFL || (cur.sa_flags & SA_SIGINFO)) continue;   /* someone else's handler stays */
        struct sigaction sa; memset(&sa, 0, sizeof sa); sa.sa_handler = on_signal; sigemptyset(&sa.sa_mask);
        if (s > 0 && s < 32) sigaction(s, &sa, &g_old[s]);
    }
#else
    signal(SIGINT, on_signal); signal(SIGTERM, on_signal); signal(SIGABRT, on_signal);
#endif
}

int re_log_apply(const char *spec) {
    unsigned char lv[RE_LC_COUNT];
    ensure_started();
    int errs = re_log_parse(spec, lv, L.bad, sizeof L.bad);
    L.bad_count = errs;
    snprintf(L.spec, sizeof L.spec, "%s", spec ? spec : "");
    for (int c = 0; c < RE_LC_COUNT; c++) re_log_level_of[c] = lv[c];
    if (re_log_enabled()) {
        if (L.closed) { L.closed = 0; L.opened = 0; }
        mx_lock(&g_mx); open_locked(); mx_unlock(&g_mx);
        install_hooks();
        if (errs) re_log(RE_LC_sys, RE_LV_WARN, "RE_LOG: %d неразобранных элементов в \"%s\" (первый: \"%s\"); каналы: sys load game mission render audio input mem save, уровни: off error warn info debug trace", errs, L.spec, L.bad);
    }
    return errs;
}
void re_log_init(const char *exe_dir) {
    ensure_started();
    if (tl_tid < 0) tl_tid = L.next_tid++;
    if (exe_dir) snprintf(L.exe_dir, sizeof L.exe_dir, "%s", exe_dir);
    const char *spec = getenv("RE_LOG");
    if (!spec || !*spec) return;   /* off: nothing else is read, opened or installed */
    L.env_spec = 1;
    const char *e;
    if ((e = getenv("RE_LOG_FILE")) && *e) {
        if (!strcmp(e, "-") || ieq(e, "stderr") || ieq(e, "off")) { L.no_file = 1; if (!ieq(e, "off")) L.to_stderr = 1; }
        else snprintf(L.want_path, sizeof L.want_path, "%s", e);
    }
    if ((e = getenv("RE_LOG_STDERR")) && *e && *e != '0') L.to_stderr = 1;
    if ((e = getenv("RE_LOG_RATE")) && *e) L.rate = atoi(e);
    if ((e = getenv("RE_LOG_MAX_MB")) && *e) L.max_bytes = atol(e) * 1024L * 1024L;
    re_log_apply(spec);
}
int re_log_cfg(const char *spec) {
    if (L.env_spec || !spec || !*spec) return 0;
    const char *e;
    if ((e = getenv("RE_LOG_FILE")) && *e && !L.want_path[0] && !L.no_file) {
        if (!strcmp(e, "-") || ieq(e, "stderr") || ieq(e, "off")) { L.no_file = 1; if (!ieq(e, "off")) L.to_stderr = 1; }
        else snprintf(L.want_path, sizeof L.want_path, "%s", e);
    }
    if ((e = getenv("RE_LOG_STDERR")) && *e && *e != '0') L.to_stderr = 1;
    return re_log_apply(spec);
}

/* ---- tests ---- */
void re_log_test_rate(int per_sec) { L.rate = per_sec; }
void re_log_test_clock(unsigned (*ms)(void)) { g_test_clock = ms; }
void re_log_test_reset(void) {
    mx_lock(&g_mx);
    if (L.f) { fclose(L.f); L.f = NULL; }
    for (int c = 0; c < RE_LC_COUNT; c++) re_log_level_of[c] = 0;
    L.opened = 0; L.closed = 0; L.no_file = 0; L.to_stderr = 0; L.want_path[0] = 0; L.path[0] = 0; L.written = 0;
    L.last_ch = -1; L.last_rep = 0; L.last_text[0] = 0; L.rate = 200; L.max_bytes = 64L * 1024 * 1024;
    memset(L.rl, 0, sizeof L.rl);
    mx_unlock(&g_mx);
}
int re_log_test_open(const char *path) {
    mx_lock(&g_mx);
    snprintf(L.want_path, sizeof L.want_path, "%s", path); L.opened = 0; L.closed = 0; L.no_file = 0;
    open_locked();
    int ok = L.f != NULL;
    mx_unlock(&g_mx);
    return ok;
}
