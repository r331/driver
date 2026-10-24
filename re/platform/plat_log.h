#ifndef PLAT_LOG_H
#define PLAT_LOG_H
/* plat_log.h — RE_LOG, the unified debug logger (v2.37).  Plain C, no SDL; game code reaches it only through
   plat.h (which includes this header).

   Usage:  RE_LOGI(game, "level load: city %d", city);       channels: sys load game mission render audio input mem save
           RE_LOGE / RE_LOGW / RE_LOGI / RE_LOGD / RE_LOGT   levels:   error warn info debug trace
           if (RE_LOG_ON(render, RE_LV_DEBUG)) { ...expensive formatting... }

   Off by default.  Each macro is one byte load and a compare (per-channel level table); when the channel is off
   no call is made and the arguments are not evaluated.  In the hook build (RE_HOOK_BUILD, inside the original
   Game.exe) every macro compiles to nothing (the arguments are still type-checked, never evaluated).

   Setup (native): RE_LOG="all:info,render:debug,audio:off" or driver.cfg "log = ..." (RE_LOG wins);
   RE_LOG_FILE=path ("-" / "stderr" — no file); default <exe dir>/driver.log, macOS ~/Library/Logs/Driver/driver.log;
   RE_LOG_STDERR=1 — copy every line to stderr; RE_LOG_RATE=N — lines per second per call site (default 200, 0 = no
   limit); RE_LOG_MAX_MB=N — file size limit before rotation to driver.log.1 (default 64).
   Line: "<ms since start> f<frame> <channel> <LEVEL> message"; see docs/DIAGNOSTICS.md, section RE_LOG. */
#include <stdarg.h>

enum re_log_channel {
  RE_LC_sys, RE_LC_load, RE_LC_game, RE_LC_mission, RE_LC_render, RE_LC_audio, RE_LC_input, RE_LC_mem, RE_LC_save,
  RE_LC_COUNT
};
enum re_log_level { RE_LV_OFF = 0, RE_LV_ERROR = 1, RE_LV_WARN = 2, RE_LV_INFO = 3, RE_LV_DEBUG = 4, RE_LV_TRACE = 5 };

#if defined(__GNUC__) || defined(__clang__)
#  define RE_LOG_PRINTF(a, b) __attribute__((format(printf, a, b)))
#  define RE_LOG_UNLIKELY(x)  __builtin_expect(!!(x), 0)
#else
#  define RE_LOG_PRINTF(a, b)
#  define RE_LOG_UNLIKELY(x)  (x)
#endif

#ifndef RE_HOOK_BUILD
/* Per-channel maximum level (RE_LV_*); 0 — channel off.  Written only while configuring (main thread, before the
   game starts), read lock-free by the macros. */
extern unsigned char re_log_level_of[RE_LC_COUNT];

void re_log(int ch, int lv, const char *fmt, ...) RE_LOG_PRINTF(3, 4);
void re_logv(int ch, int lv, const char *fmt, va_list ap);
/* Start of the process: remembers the time origin and the executable directory (NULL — unknown), reads RE_LOG,
   RE_LOG_FILE, RE_LOG_STDERR, RE_LOG_RATE, RE_LOG_MAX_MB.  Without RE_LOG nothing is opened or installed. */
void re_log_init(const char *exe_dir);
/* driver.cfg "log = spec": applied only when RE_LOG is not set in the environment.  Returns parse errors. */
int  re_log_cfg(const char *spec);
/* Parses a spec into lv[RE_LC_COUNT] (starting from all off); returns the number of bad tokens, first one in bad. */
int  re_log_parse(const char *spec, unsigned char *lv, char *bad, int badn);
int  re_log_apply(const char *spec);          /* parse + set re_log_level_of (opens the file when something is on) */
int  re_log_enabled(void);                    /* any channel on */
const char *re_log_channel_name(int ch);
const char *re_log_path(void);                /* current file ("" — none) */
void re_log_flush(void);                      /* pending "repeated N times" / "suppressed N" notes + fflush */
void re_log_shutdown(const char *why);        /* last line, flush, close (also from atexit) */
void re_log_crash(int sig);                   /* from signal handlers: one line + flush, never blocks */
/* Tests (selftest): rate per call site per second (0 — unlimited), fake clock (NULL — real), reset to off. */
void re_log_test_rate(int per_sec);
void re_log_test_clock(unsigned (*ms)(void));
void re_log_test_reset(void);
int  re_log_test_open(const char *path);      /* log into this file (truncated) without touching RE_LOG */

#  define RE_LOG_ON(ch, lv)       RE_LOG_UNLIKELY(re_log_level_of[RE_LC_##ch] >= (lv))
#  define RE_LOG_AT(ch, lv, ...)  do { if (RE_LOG_ON(ch, lv)) re_log(RE_LC_##ch, (lv), __VA_ARGS__); } while (0)
#else
static inline void re_log_nop(const char *fmt, ...) RE_LOG_PRINTF(1, 2);
static inline void re_log_nop(const char *fmt, ...) { (void)fmt; }
#  define RE_LOG_ON(ch, lv)       0
#  define RE_LOG_AT(ch, lv, ...)  do { if (0) re_log_nop(__VA_ARGS__); } while (0)
#endif

#define RE_LOGE(ch, ...) RE_LOG_AT(ch, RE_LV_ERROR, __VA_ARGS__)
#define RE_LOGW(ch, ...) RE_LOG_AT(ch, RE_LV_WARN,  __VA_ARGS__)
#define RE_LOGI(ch, ...) RE_LOG_AT(ch, RE_LV_INFO,  __VA_ARGS__)
#define RE_LOGD(ch, ...) RE_LOG_AT(ch, RE_LV_DEBUG, __VA_ARGS__)
#define RE_LOGT(ch, ...) RE_LOG_AT(ch, RE_LV_TRACE, __VA_ARGS__)
#endif
