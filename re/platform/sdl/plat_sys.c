#if defined(__linux__) && !defined(_GNU_SOURCE)
#define _GNU_SOURCE   /* v2.10: dladdr, ucontext (RE_CRASH_BT) */
#endif
#include "../plat.h"
#include "plat_gfx.h"
#include <SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <strings.h>
#include <dirent.h>
#include <sys/stat.h>
#include <limits.h>
static SDL_Window *g_win; static SDL_GLContext g_gl;
static void update_drawable(void);
int plat_fixed_dt(void);
/* v2.16: ограничение FPS (fps_limit, driver.cfg/RE_FPS_LIMIT) — ожидание до следующего срока после показа; при RE_FIXED_DT не действует */
static void fps_wait(void) {
    static Uint64 next; int lim = re_gfx()->fps_limit;
    if (lim <= 0 || plat_fixed_dt()) return;
    Uint64 f = SDL_GetPerformanceFrequency(), per = f / (Uint64)lim, now = SDL_GetPerformanceCounter();
    if (!next || now > next + per * 4) next = now;   /* старт или долгий кадр — без «догоняния» */
    next += per;
    while ((now = SDL_GetPerformanceCounter()) < next) { Uint64 ms = (next - now) * 1000 / f; if (ms > 1) SDL_Delay((Uint32)(ms - 1)); }
}
void plat_gfx_err(const char *m) { plat_log("[gfx] %s\n", m); }
static void swap_win(void){ SDL_GL_SwapWindow(g_win); fps_wait(); update_drawable(); }   /* v2.14: размер буфера мог измениться (окно, полный экран, Retina) */
/* v2.08: RE_FIXED_DT=1 — виртуальное время для воспроизводимых прогонов: каждый вызов plat_time_ms +1 мс, каждый показанный
   кадр (plat_flip) — не меньше кадр·20 мс (такт логики P21_FrameTicks = 20 мс → один такт на кадр), plat_sleep_ms только
   сдвигает часы; таймеры (plat_timer_start) срабатывают в основном потоке по виртуальным часам (plat_vt_timers, plat_snd.c). */
static int g_fixed_dt = -1; static uint32_t g_vt;
void plat_vt_timers(uint32_t now);
int plat_fixed_dt(void){ if (g_fixed_dt < 0) { const char *e = getenv("RE_FIXED_DT"); g_fixed_dt = e && *e && *e != '0'; } return g_fixed_dt; }
static void vt_advance(uint32_t t){ if (t > g_vt) g_vt = t; plat_vt_timers(g_vt); }
uint32_t plat_time_ms(void){ if (!plat_fixed_dt()) return SDL_GetTicks(); vt_advance(g_vt + 1); return g_vt; }
void plat_vt_poll(void){ if (plat_fixed_dt()) vt_advance(g_vt + 1); }
void plat_sleep_ms(uint32_t ms){ if (!plat_fixed_dt()) { SDL_Delay(ms); return; } vt_advance(g_vt + ms); }
void plat_log(const char *f, ...){ va_list a; va_start(a,f); vfprintf(stderr,f,a); va_end(a); }
void *plat_file_open(const char *path, const char *mode){
    FILE *f = fopen(path, mode); if (f) return f;
    char dir[PATH_MAX], *s; strncpy(dir, path, sizeof dir - 1); dir[sizeof dir - 1] = 0;
    s = strrchr(dir, '/'); const char *base = s ? s + 1 : dir;
    if (s) *s = 0; else strcpy(dir, ".");
    DIR *d = opendir(dir); if (!d) return NULL;
    struct dirent *e; char full[PATH_MAX*2];
    while ((e = readdir(d))) if (!strcasecmp(e->d_name, base)) {
        snprintf(full, sizeof full, "%s/%s", dir, e->d_name); closedir(d); return fopen(full, mode); }
    closedir(d); return NULL;
}
/* v2.14: окно в нативном разрешении. Логический кадр игры w×h (640×480) вписывается в буфер окна (plat_render_set_drawable).
   macOS — по умолчанию полный экран рабочего стола (SDL_WINDOW_FULLSCREEN_DESKTOP), другие системы — окно.
   RE_WINDOWED=1 — окно; RE_FULLSCREEN=1 — полный экран; RE_RES=WxH — размер окна (точки; подразумевает окно, если нет RE_FULLSCREEN).
   Окно без RE_RES — наибольшее целое кратное w×h, умещающееся в 85% рабочей области дисплея. Cmd+Enter / Alt+Enter — переключение. */
static int g_fs_on;
static int env_on(const char *n) { const char *e = getenv(n); return e && *e && *e != '0'; }
static void update_drawable(void) { int dw = 0, dh = 0; if (!g_win) return; SDL_GL_GetDrawableSize(g_win, &dw, &dh); plat_render_set_drawable(dw, dh); }
void plat_input_dbg(const char *fmt, ...);   /* plat_di.c */
void plat_toggle_fullscreen(void) {
    if (!g_win) return;
    g_fs_on = !g_fs_on;
    SDL_SetWindowFullscreen(g_win, g_fs_on ? SDL_WINDOW_FULLSCREEN_DESKTOP : 0);
    update_drawable();
    plat_input_dbg("полный экран %d", g_fs_on);
}
int plat_window_open(const char *t,int w,int h,int fs){
#ifdef SDL_HINT_MAC_BACKGROUND_APP
    SDL_SetHint(SDL_HINT_MAC_BACKGROUND_APP, "0");     /* v2.14: обычное приложение с окном/Dock — получает клавиатуру */
#endif
    if (SDL_Init(SDL_INIT_VIDEO|SDL_INIT_TIMER)) return -1;
    /* v2.16: driver.cfg — RE_CFG, рядом с бинарником, затем каталог пользователя (macOS: ~/Library/Application Support/Driver,
       Linux: $XDG_CONFIG_HOME/driver или ~/.config/driver); переменные RE_* важнее файла */
    {   char ud[PATH_MAX] = ""; const char *home = getenv("HOME");
#if defined(__APPLE__)
        if (home) snprintf(ud, sizeof ud, "%s/Library/Application Support/Driver", home);
#else
        const char *xdg = getenv("XDG_CONFIG_HOME");
        if (xdg && *xdg) snprintf(ud, sizeof ud, "%s/driver", xdg); else if (home) snprintf(ud, sizeof ud, "%s/.config/driver", home);
#endif
        char *bp = SDL_GetBasePath();
        int errs = re_gfx_load(bp, ud, plat_gfx_err);
        if (bp) SDL_free(bp);
        if (errs) plat_log("[gfx] driver.cfg/RE_*: %d ошибок разбора (строки пропущены)\n", errs);
        const re_gfx_cfg *gc = re_gfx();
        if (gc->aspect[0] && !getenv("RE_ASPECT")) plat_render_set_aspect(gc->aspect);
    }
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3); SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, SDL_GL_CONTEXT_FORWARD_COMPATIBLE_FLAG); /* macOS требует */
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
#if defined(__APPLE__)
    int full = 1;
#else
    int full = fs;
#endif
    int ww = w, wh = h; const char *res = getenv("RE_RES");
    if (res && sscanf(res, "%dx%d", &ww, &wh) == 2 && ww > 0 && wh > 0) full = 0;
    else {
        ww = w; wh = h; SDL_Rect ub;
        if (SDL_GetDisplayUsableBounds(0, &ub) == 0 && ub.w > 0 && ub.h > 0) {
            int k = 1; while (w * (k + 1) <= ub.w * 85 / 100 && h * (k + 1) <= ub.h * 85 / 100) k++;
            ww = w * k; wh = h * k;
        }
    }
    {   const re_gfx_cfg *gc = re_gfx();   /* v2.16: driver.cfg fullscreen / windowed_res (переменные RE_* — ниже, важнее) */
        if (gc->fullscreen >= 0) full = gc->fullscreen;
        if (!(res && *res) && gc->win_w > 0 && gc->win_h > 0) { ww = gc->win_w; wh = gc->win_h; if (gc->fullscreen != 1) full = 0; }
    }
    if (env_on("RE_WINDOWED")) full = 0;
    if (env_on("RE_FULLSCREEN")) full = 1;
    g_fs_on = full;
    g_win = SDL_CreateWindow(t, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, ww, wh,
                             SDL_WINDOW_OPENGL | SDL_WINDOW_ALLOW_HIGHDPI | SDL_WINDOW_RESIZABLE | (full ? SDL_WINDOW_FULLSCREEN_DESKTOP : 0));
    if (!g_win) return -1;
    SDL_SetWindowMinimumSize(g_win, w / 2, h / 2);
    g_gl = SDL_GL_CreateContext(g_win); if (!g_gl) return -2;
    {   int vs = re_gfx()->vsync;   /* v2.16: vsync on/off/adaptive (adaptive недоступен — on) */
        if (SDL_GL_SetSwapInterval(vs) != 0) { plat_log("[gfx] vsync %d недоступен (%s)%s\n", vs, SDL_GetError(), vs == -1 ? " — включён обычный" : ""); if (vs == -1) SDL_GL_SetSwapInterval(1); }
    }
    SDL_RaiseWindow(g_win);   /* v2.14: окно — ключевое (фокус клавиатуры) сразу после запуска */
    int r = plat_render_attach((void *(*)(const char *))SDL_GL_GetProcAddress, swap_win, w, h);
    if (r == 0) update_drawable();
    { int dw = 0, dh = 0; SDL_GL_GetDrawableSize(g_win, &dw, &dh);
      fprintf(stderr, "[window] кадр игры %dx%d, окно %dx%d, буфер %dx%d, %s, главный поток %d\n", w, h, ww, wh, dw, dh,
              full ? "полный экран" : "окно", plat_is_main_thread());
      plat_input_dbg("окно: кадр %dx%d, окно %dx%d, буфер %dx%d, полный экран %d, главный поток %d", w, h, ww, wh, dw, dh, full, plat_is_main_thread()); }
    return r;
}
int plat_poll_events(void){ SDL_Event e; while (SDL_PollEvent(&e)) if (e.type==SDL_QUIT) return 0; return 1; }
int plat_key_down(int sc){ const Uint8 *k = SDL_GetKeyboardState(NULL); return k ? k[sc] : 0; }
void plat_window_close(void){ plat_render_shutdown(); if (g_gl) SDL_GL_DeleteContext(g_gl); g_gl=0; if (g_win) SDL_DestroyWindow(g_win); g_win=0; SDL_Quit(); }
#include <time.h>
void plat_local_hms(int *h,int *m,int *s){ time_t t=time(0); struct tm *l=localtime(&t); *h=l->tm_hour; *m=l->tm_min; *s=l->tm_sec; }

void plat_utc_hms(int *h,int *m,int *s){ time_t t=time(0); struct tm *l=gmtime(&t); *h=l->tm_hour; *m=l->tm_min; *s=l->tm_sec; }
static char g_mb_text[512], g_mb_title[128]; static int g_mb_count;
int plat_message_box(void *hwnd,const char *text,const char *title,unsigned flags){
    (void)hwnd; g_mb_count++;
    snprintf(g_mb_text,sizeof g_mb_text,"%s",text?text:""); snprintf(g_mb_title,sizeof g_mb_title,"%s",title?title:"");
    fprintf(stderr,"[%s] %s\n",g_mb_title,g_mb_text);
    if(!getenv("RE_NO_MSGBOX")) SDL_ShowSimpleMessageBox((flags&0x10)?SDL_MESSAGEBOX_ERROR:((flags&0x30)==0x30?SDL_MESSAGEBOX_WARNING:SDL_MESSAGEBOX_INFORMATION),g_mb_title,g_mb_text,g_win);
    return 1;
}
int plat_message_box_last(const char **text,const char **title){ if(text)*text=g_mb_text; if(title)*title=g_mb_title; return g_mb_count; } /* тесты */
static uint32_t g_wavevol=0xffffffffu;
void plat_wave_set_volume(uint32_t lr){ g_wavevol=lr; }
uint32_t plat_wave_volume(void){ return g_wavevol; }
int plat_cd_roots(char *buf,int size){   /* macOS: тома в /Volumes; Linux: /media, /mnt не сканируем */
    int n=0; DIR *d=opendir("/Volumes");
    if(!d){ if(size>0){ buf[0]=0; } return 0; }
    struct dirent *e;
    while((e=readdir(d))){ if(e->d_name[0]=='.') continue;
        int l=snprintf(buf+n,(size_t)(size-n-1),"/Volumes/%s/",e->d_name);
        if(l<0||n+l+2>=size){ break; }
        n+=l+1; }
    closedir(d); buf[n]=0; return n;
}

/* --- выход, хранитель экрана, обработчик аварий --- */
#include <stdlib.h>
#include <signal.h>
static int g_exit_trap, g_exit_last, g_saver = 1;
static void (*g_crash)(void);
void plat_exit_trap(int on){ g_exit_trap=on; }
int plat_exit_last(void){ return g_exit_last; }
void plat_exit(int code){ g_exit_last=code; if(g_exit_trap) return; exit(code); }
int plat_screensaver_get(void){ return g_saver; }
void plat_screensaver_set(int on){
    g_saver = on?1:0;
    if(SDL_WasInit(SDL_INIT_VIDEO)){ if(g_saver) SDL_EnableScreenSaver(); else SDL_DisableScreenSaver(); }
}
#if defined(__GLIBC__)
#include <execinfo.h>
#endif
#include <signal.h>
#if defined(__GLIBC__)
#include <ucontext.h>
#include <dlfcn.h>
#endif
/* v2.03: RE_CRASH_BT=1 — стек в stderr перед обработчиком игры (glibc backtrace; адреса — addr2line -f -e driver) */
static void crash_sig(int sig, siginfo_t *si, void *uc){
    signal(sig,SIG_DFL);
#if defined(__GLIBC__)
    if (getenv("RE_CRASH_BT")) {
        void *bt[48]; int n = backtrace(bt, 48); uintptr_t pc = 0, lr = 0;
        /* v2.10: PC/LR из контекста сигнала — backtrace из обработчика видит только сам обработчик */
#if defined(__aarch64__)
        pc = (uintptr_t)((ucontext_t *)uc)->uc_mcontext.pc; lr = (uintptr_t)((ucontext_t *)uc)->uc_mcontext.regs[30];
#elif defined(__x86_64__)
        pc = (uintptr_t)((ucontext_t *)uc)->uc_mcontext.gregs[REG_RIP];
#endif
        Dl_info di; uintptr_t base = dladdr((void *)crash_sig, &di) ? (uintptr_t)di.dli_fbase : 0;
        fprintf(stderr, "[crash] сигнал %d, адрес %p, pc +0x%lx lr +0x%lx, стек:\n", sig, si ? si->si_addr : NULL,
                (unsigned long)(pc - base), (unsigned long)(lr - base));
        backtrace_symbols_fd(bt, n, 2);
    }
#else
    (void)si; (void)uc;
#endif
    if(g_crash) g_crash(); _Exit(1);
}
void plat_set_crash_handler(void (*fn)(void)){
    g_crash=fn;
    if (getenv("RE_NO_CRASH")) return;   /* v2.01: отладка — сигналы видит ASan/gdb */
    struct sigaction sa; memset(&sa, 0, sizeof sa);
    if (fn) { sa.sa_sigaction = crash_sig; sa.sa_flags = SA_SIGINFO; } else sa.sa_handler = SIG_DFL;
    sigemptyset(&sa.sa_mask);
#define signal(s, h_) sigaction((s), &sa, NULL)
    /* v2.01: SIGILL не перехватывается — Mesa (llvmpipe, arm64) пробует инструкции CPU через SIGILL при первой загрузке
       текстуры; обработчик игры превращал это в «Application Error» */
    signal(SIGSEGV,h); signal(SIGFPE,h);
#ifdef SIGBUS
    signal(SIGBUS,h);
#endif
#undef signal
}
void (*plat_crash_handler(void))(void){ return g_crash; }

/* --- окно игры, цикл сообщений --- */
static int g_wtrap, g_wcur=1, g_wprio, g_wquit, g_wclose, g_ww, g_wh; static char g_wtitle[64]; static plat_wndproc g_wproc;
void plat_win_trap(int on){ g_wtrap=on; }
void *plat_game_window_create(void *hinst,int32_t show,const char *title,int w,int h,plat_wndproc proc){
    (void)hinst; (void)show; g_ww=w; g_wh=h; g_wproc=proc; snprintf(g_wtitle,sizeof g_wtitle,"%s",title?title:"");
    if(g_wtrap) return (void *)(intptr_t)1;
    return plat_window_open(title,w,h,0)==0 ? (void *)(intptr_t)1 : NULL;
}
void plat_input_dbg_event(const void *ev);   /* v2.14: plat_di.c, RE_INPUTDBG=1 */
void plat_input_key_event(int scancode, int down, int repeat);   /* v2.14: plat_di.c — защёлка коротких нажатий */
/* v2.14: разбор очереди событий SDL — только из главного потока (на macOS события Cocoa приходят только туда).
   Зовётся из цикла сообщений игры (plat_pump_messages) и из plat_flip, если с прошлого кадра цикла сообщений не было
   (заставки/FMV/загрузка: игра не качает сообщения по 15+ с — на macOS окно «не отвечает» и не получает фокус). */
static int g_active_sent = -1, g_pumped;
static void send_activate(int on) {
    if (g_wtrap || !g_wproc || g_active_sent == on) return;
    g_active_sent = on; plat_input_dbg("WM_ACTIVATEAPP %d", on);
    g_wproc((void *)(intptr_t)1, 0x1c, (uint32_t)on, 0);
}
static void drain_events(void) {
    static int warned;
    if (!warned && plat_is_main_thread() == 0) { warned = 1; fprintf(stderr, "[input] ВНИМАНИЕ: события SDL разбираются не в главном потоке\n"); plat_input_dbg("ВНИМАНИЕ: цикл событий не в главном потоке"); }
    SDL_Event e;
    while (SDL_PollEvent(&e)) {
        plat_input_dbg_event(&e);
        if (e.type == SDL_QUIT) {
            g_wquit = 1;
            if (!g_wtrap) { fprintf(stderr, "[window] закрытие окна — выход\n"); fflush(NULL); exit(0); }   /* v2.14: Cmd+Q / закрытие окна */
        } else if (e.type == SDL_KEYDOWN || e.type == SDL_KEYUP) {
            int sc = e.key.keysym.scancode, mod = e.key.keysym.mod;
            if (e.type == SDL_KEYDOWN && !e.key.repeat && (sc == SDL_SCANCODE_RETURN || sc == SDL_SCANCODE_KP_ENTER) && (mod & (KMOD_GUI | KMOD_ALT))) {
                plat_toggle_fullscreen(); continue;   /* Cmd+Enter / Alt+Enter — игре не передаётся */
            }
            plat_input_key_event(sc, e.type == SDL_KEYDOWN, e.key.repeat);
        } else if (e.type == SDL_WINDOWEVENT) {
            if (e.window.event == SDL_WINDOWEVENT_SIZE_CHANGED || e.window.event == SDL_WINDOWEVENT_RESIZED) update_drawable();
            else if (e.window.event == SDL_WINDOWEVENT_FOCUS_GAINED || e.window.event == SDL_WINDOWEVENT_FOCUS_LOST)
                send_activate(e.window.event == SDL_WINDOWEVENT_FOCUS_GAINED);
        }
    }
    /* v2.14: окно с фокусом клавиатуры, а игра считает себя неактивной (пропущено FOCUS_GAINED, порядок событий при запуске
       или переходе в полноэкранное пространство macOS) — сообщить активацию; иначе P36_PollInput не читает клавиатуру */
    if (g_win && g_active_sent == 0 && (SDL_GetWindowFlags(g_win) & SDL_WINDOW_INPUT_FOCUS)) send_activate(1);
}
void plat_pump_messages(void){
    if(!SDL_WasInit(SDL_INIT_VIDEO)) return;
    /* v2.01: оконная процедура игры получает WM_ACTIVATEAPP (0x1c): 1 при первом цикле сообщений (окно SDL создаётся активным;
       под Xvfb фокус-событий нет) и при SDL_WINDOWEVENT_FOCUS_GAINED/LOST — иначе фронтенд ждёт P31_Active вечно */
    if (g_active_sent < 0) send_activate(1);
    drain_events(); g_pumped = 1;
    if(!g_wtrap) plat_frame_tick("pump");
}
static void flip_events(void) {   /* из plat_frame_tick("flip") */
    if (!g_pumped && g_win && !g_wtrap && SDL_WasInit(SDL_INIT_VIDEO)) drain_events();
    g_pumped = 0;
}
void plat_set_priority(int level){
    g_wprio=level;
    SDL_SetThreadPriority(level>0?SDL_THREAD_PRIORITY_HIGH:SDL_THREAD_PRIORITY_NORMAL);
}
void plat_post_quit(int code){ (void)code; g_wquit=1; }
void plat_post_close(void *hwnd){ (void)hwnd; g_wclose++; }
void plat_set_cursor(int visible){ g_wcur=visible?1:0; if(SDL_WasInit(SDL_INIT_VIDEO)) SDL_ShowCursor(g_wcur); }
int32_t plat_def_window_proc(void *hwnd,uint32_t msg,uint32_t wp,int32_t lp){ (void)hwnd;(void)msg;(void)wp;(void)lp; return 0; }
void plat_dll_unload(void *mod){ (void)mod; }
void *plat_dll_load(const char *name){ (void)name; return NULL; }
void *plat_dll_proc(void *mod, const char *name){ (void)mod; (void)name; return NULL; }
void *plat_lock_resource(void *res){ return res; }
int plat_win_state(int *cur,int *prio,int *quit,int *closes,int *w,int *h,const char **title,plat_wndproc *proc){
    if(cur){ *cur=g_wcur; }
    if(prio){ *prio=g_wprio; }
    if(quit){ *quit=g_wquit; }
    if(closes){ *closes=g_wclose; }
    if(w){ *w=g_ww; }
    if(h){ *h=g_wh; }
    if(title){ *title=g_wtitle; }
    if(proc){ *proc=g_wproc; }
    return 1;
}

static int g_com;
int plat_com_init(void){ g_com++; return 0; }
void plat_com_uninit(void){ if(g_com>0) g_com--; }
int plat_com_count(void){ return g_com; }
/* v1.95: WM_CREATE — в SDL оконная процедура получает hInstance прямо в lparam (как и раньше) */
int32_t plat_wm_create_hinst(int32_t lparam){ return lparam; }
/* --- v1.96: MoveWindow (размер окна SDL), активное окно, курсор, процесс, ускорители --- */
static int g_moves; static int32_t g_move[5];
void plat_window_move(void *h, int x, int y, int w, int hh, int rep) {
    (void)h; g_moves++; g_move[0] = x; g_move[1] = y; g_move[2] = w; g_move[3] = hh; g_move[4] = rep;
    /* v2.14: размер окна задаёт платформа (нативное разрешение); MoveWindow игры меняет только логический кадр */
    if (g_win && !g_wtrap && w > 0 && hh > 0) { plat_render_set_logical(w, hh); update_drawable(); } }
int plat_win_moves(int32_t *l) { if (l) memcpy(l, g_move, sizeof g_move); return g_moves; }
void *plat_window_active(void) { return (g_win || g_wtrap) ? (void *)(intptr_t)1 : NULL; }
void *plat_cursor_set(void *c) { void *old = (void *)(intptr_t)g_wcur; plat_set_cursor(c != NULL); return old; }
void *plat_current_process(void) { return (void *)(intptr_t)-1; }
void *plat_load_accelerators(void *hinst, const char *name) { (void)hinst; (void)name; return NULL; }

/* --- v2.00: пути игры (Windows) → native: '\\' → '/', каждый компонент ищется без учёта регистра --- */
static int ci_component(const char *dir, const char *name, char *out, size_t n) {
    DIR *d = opendir(*dir ? dir : "."); if (!d) return 0;
    struct dirent *e; int ok = 0;
    while ((e = readdir(d))) if (!strcasecmp(e->d_name, name)) { snprintf(out, n, "%s", e->d_name); ok = 1; break; }
    closedir(d); return ok;
}
int plat_path_native(const char *path, char *out, int size) {
    char tmp[PATH_MAX], res[PATH_MAX] = "", comp[256];
    if (!path || !out || size <= 0) return 0;
    snprintf(tmp, sizeof tmp, "%s", path);
    for (char *c = tmp; *c; c++) if (*c == '\\') *c = '/';
    const char *p = tmp; int found = 1;
    if (*p == '/') { strcpy(res, "/"); while (*p == '/') p++; }
    while (*p) {
        const char *q = strchr(p, '/'); size_t l = q ? (size_t)(q - p) : strlen(p);
        if (l >= sizeof comp) l = sizeof comp - 1;
        memcpy(comp, p, l); comp[l] = 0;
        char real[256];
        const char *use = comp;
        if (found && strcmp(comp, ".") && strcmp(comp, "..") && ci_component(res, comp, real, sizeof real)) use = real;
        else if (strcmp(comp, ".") && strcmp(comp, "..")) found = 0;
        size_t rl = strlen(res);
        snprintf(res + rl, sizeof res - rl, "%s%s", (rl && res[rl - 1] != '/') ? "/" : "", use);
        if (!q) break;
        p = q; while (*p == '/') p++;
    }
    snprintf(out, (size_t)size, "%s", res);
    return found;
}
static int g_mkdirs;   /* v2.04: создавать недостающие каталоги при записи — только игра (platform/native/main.c) */
void plat_fs_mkdirs(int on) { g_mkdirs = on; }
void *plat_fopen_game(const char *path, const char *mode) {
    if (!path || !mode) return NULL;
    char np[PATH_MAX];
    plat_path_native(path, np, sizeof np);
    FILE *f = fopen(np, mode);
    if (!f && g_mkdirs && (strchr(mode, 'w') || strchr(mode, 'a'))) {
        /* v2.04: запись в несуществующий подкаталог («SAVES\\SCORES.HI») — создаём недостающие каталоги пути
           (mkdir по компонентам native-пути) и пробуем снова. Прежний откат к fopen(path) с буквальной «\\» создавал
           в текущем каталоге файл с обратной косой чертой в имени — убран. */
        char d[PATH_MAX]; snprintf(d, sizeof d, "%s", np);
        for (char *c = d + 1; *c; c++) if (*c == '/') { *c = 0; mkdir(d, 0777); *c = '/'; }
        f = fopen(np, mode);
    }
    if (!f && !strchr(path, '\\')) f = fopen(path, mode);   /* путь без «\\» — как раньше */
    if (!f && !g_mkdirs && strchr(path, '\\')) {
        /* v2.04, вне игры (selftest): прежнее поведение v2.03 — путь как есть (файл с «\\» в имени в каталоге теста).
           Перевод в каталог или плоское имя ломает selftest (SIGSEGV позже в тестах — не выяснено, см. NATIVE_GAPS.md). */
        f = fopen(path, mode);
    }
    return f;
}

/* v2.04: удаление файла игры — путь переводится так же, как в plat_fopen_game (иначе remove("SAVES\\REPLAY3.BIN")
   не находил файл, созданный по native-пути, и в selftest оставался обрезанный повтор) */
int plat_remove_game(const char *path) {
    if (!path) return -1;
    char np[PATH_MAX]; plat_path_native(path, np, sizeof np);
    if (remove(np) == 0) return 0;
    return remove(path);   /* как раньше: путь как есть */
}

/* --- v2.00: кадры запуска игры: RE_MAX_FRAMES=N — после N-го plat_flip выход 0; RE_SHOT_PNG=путь — снимок кадра N
       (или первого, если RE_SHOT_FIRST=1); RE_MAX_PUMPS=N — выход после N циклов сообщений без кадров (защита) --- */
int png_write_rgba(const char *path, const uint32_t *px, int w, int h);   /* tests/render_test.c */
static int g_frames, g_pumps, g_shot_done;
int plat_frame_no(void) { return g_frames; }
static void frame_shot(void) {
    const char *png = getenv("RE_SHOT_PNG"); int w = 0, h = 0;
    if (!png || !*png || !g_win) return;
    SDL_GL_GetDrawableSize(g_win, &w, &h);
    if (w <= 0 || h <= 0) return;
    uint32_t *px = malloc((size_t)w * h * 4); if (!px) return;
    if (plat_render_readback(px) == 0 && png_write_rgba(png, px, w, h) == 0) { fprintf(stderr, "[frame] снимок %s (%dx%d), кадр %d\n", png, w, h, g_frames); g_shot_done = 1; }
    free(px);
}
/* v2.16: RE_FRAMESTAT=N — время кадра (стенные часы между plat_flip: логика игры + рендер + показ) с кадра N; итог при выходе */
static double *g_ft; static int g_ftn, g_ftcap, g_ftfrom = -2; static Uint64 g_ftlast;
static int dcmp(const void *a, const void *b) { double x = *(const double *)a, y = *(const double *)b; return x < y ? -1 : x > y; }
static void frame_stat_report(void) {
    if (g_ftn <= 0) return;
    double sum = 0; for (int i = 0; i < g_ftn; i++) sum += g_ft[i];
    qsort(g_ft, (size_t)g_ftn, sizeof *g_ft, dcmp);
    int up_px = 0, up = plat_render_uploads(&up_px);
    fprintf(stderr, "[framestat] кадров %d (с %d): среднее %.2f мс, медиана %.2f, p95 %.2f, мин %.2f, макс %.2f; загрузок текстур всего %d (%d Мпикс)\n", g_ftn, g_ftfrom,
            sum / g_ftn, g_ft[g_ftn / 2], g_ft[(int)(g_ftn * 0.95)], g_ft[0], g_ft[g_ftn - 1], up, up_px / 1000000);
}
static void frame_stat(void) {
    if (g_ftfrom == -2) { const char *e = getenv("RE_FRAMESTAT"); g_ftfrom = e ? atoi(e) : -1; }
    if (g_ftfrom < 0) return;
    Uint64 now = SDL_GetPerformanceCounter();
    if (g_frames > g_ftfrom && g_ftlast) {
        if (g_ftn == g_ftcap) { g_ftcap = g_ftcap ? g_ftcap * 2 : 1024; g_ft = (double *)realloc(g_ft, (size_t)g_ftcap * sizeof *g_ft); if (!g_ft) { g_ftfrom = -1; return; } }
        g_ft[g_ftn++] = (double)(now - g_ftlast) * 1000.0 / (double)SDL_GetPerformanceFrequency();
    }
    g_ftlast = now;
}
int g_re_dbg[16];   /* v2.05: счётчики RE_GSTAT=N: 0 GameFrame, 1 GameDraw, 2 GlideSwap, 3 draw_prim, 4 вершин, 5 записей P85_SkipRecord, 6 DrawMap, 7 клеток, 8 моделей (draw_core), 9 обработчиков записей, 10 CarsStep, 11 P100_RecKeys, 12 P36_PadMode, 13 KeyCfg[6,4,5], 14 условие демо-клавиш */
void plat_frame_tick(const char *where) {
    static int maxf = -2, maxp = -2, gst = -2;
    if (gst == -2) { const char *e = getenv("RE_GSTAT"); gst = e ? atoi(e) : 0; }
    if (gst > 0 && where && !strcmp(where, "flip") && (g_frames + 1) % gst == 0) {
        fprintf(stderr, "[gstat] кадр %d: GameFrame %d GameDraw %d Swap %d prim %d верш %d skip %d | map %d cell %d core %d h %d | cars %d keys %x padmode %d cfg %06x cond %d\n", g_frames + 1,
                g_re_dbg[0], g_re_dbg[1], g_re_dbg[2], g_re_dbg[3], g_re_dbg[4], g_re_dbg[5], g_re_dbg[6], g_re_dbg[7], g_re_dbg[8], g_re_dbg[9], g_re_dbg[10], g_re_dbg[11], g_re_dbg[12], g_re_dbg[13], g_re_dbg[14]);
        memset(g_re_dbg, 0, sizeof g_re_dbg);
    }
    if (maxf == -2) { const char *e = getenv("RE_MAX_FRAMES"); maxf = e ? atoi(e) : -1; e = getenv("RE_MAX_PUMPS"); maxp = e ? atoi(e) : -1; }
    if (where && !strcmp(where, "flip")) {
        g_frames++;
        frame_stat();
        flip_events();
        if (plat_fixed_dt()) vt_advance((uint32_t)g_frames * 20u);   /* v2.08: RE_FIXED_DT */
        if (g_frames == 1) fprintf(stderr, "[frame] первый кадр (plat_flip)\n");
        const char *sf = getenv("RE_SHOT_FIRST");
        if (!g_shot_done && sf && *sf == '1') frame_shot();
        if (maxf > 0 && g_frames >= maxf) {
            if (!g_shot_done) frame_shot();
            frame_stat_report();
            fprintf(stderr, "[frame] RE_MAX_FRAMES=%d достигнут — выход\n", maxf); fflush(NULL); _Exit(0);
        }
    } else {
        g_pumps++;
        if (plat_fixed_dt()) vt_advance(g_vt + 1);   /* v2.08: цикл сообщений без кадров тоже двигает часы/таймеры */
        if (maxp > 0 && g_pumps >= maxp) { fprintf(stderr, "[frame] RE_MAX_PUMPS=%d (кадров %d) — выход\n", maxp, g_frames); fflush(NULL); _Exit(0); }
    }
}
