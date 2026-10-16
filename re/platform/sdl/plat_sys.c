#include "../plat.h"
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
static void swap_win(void){ SDL_GL_SwapWindow(g_win); }
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
int plat_window_open(const char *t,int w,int h,int fs){
    if (SDL_Init(SDL_INIT_VIDEO|SDL_INIT_TIMER)) return -1;
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3); SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, SDL_GL_CONTEXT_FORWARD_COMPATIBLE_FLAG); /* macOS требует */
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
    g_win = SDL_CreateWindow(t, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, w, h, SDL_WINDOW_OPENGL|(fs?SDL_WINDOW_FULLSCREEN_DESKTOP:0));
    if (!g_win) return -1;
    g_gl = SDL_GL_CreateContext(g_win); if (!g_gl) return -2;
    SDL_GL_SetSwapInterval(1);
    return plat_render_attach((void *(*)(const char *))SDL_GL_GetProcAddress, swap_win, w, h);
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
/* v2.03: RE_CRASH_BT=1 — стек в stderr перед обработчиком игры (glibc backtrace; адреса — addr2line -f -e driver) */
static void crash_sig(int sig){
    signal(sig,SIG_DFL);
#if defined(__GLIBC__)
    if (getenv("RE_CRASH_BT")) { void *bt[48]; int n = backtrace(bt, 48); fprintf(stderr, "[crash] сигнал %d, стек:\n", sig); backtrace_symbols_fd(bt, n, 2); }
#endif
    if(g_crash) g_crash(); _Exit(1);
}
void plat_set_crash_handler(void (*fn)(void)){
    g_crash=fn;
    void (*h)(int)= fn?crash_sig:SIG_DFL;
    if (getenv("RE_NO_CRASH")) return;   /* v2.01: отладка — сигналы видит ASan/gdb */
    /* v2.01: SIGILL не перехватывается — Mesa (llvmpipe, arm64) пробует инструкции CPU через SIGILL при первой загрузке
       текстуры; обработчик игры превращал это в «Application Error» */
    signal(SIGSEGV,h); signal(SIGFPE,h);
#ifdef SIGBUS
    signal(SIGBUS,h);
#endif
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
void plat_pump_messages(void){
    if(!SDL_WasInit(SDL_INIT_VIDEO)) return;
    /* v2.01: оконная процедура игры получает WM_ACTIVATEAPP (0x1c): 1 при первом цикле сообщений (окно SDL создаётся активным;
       под Xvfb фокус-событий нет) и при SDL_WINDOWEVENT_FOCUS_GAINED/LOST — иначе фронтенд ждёт P31_Active вечно */
    static int activated;
    if(!g_wtrap && g_wproc && !activated){ activated=1; g_wproc((void *)(intptr_t)1,0x1c,1,0); }
    SDL_Event e; while(SDL_PollEvent(&e)) {
        if(e.type==SDL_QUIT) g_wquit=1;
        else if(e.type==SDL_WINDOWEVENT && g_wproc && !g_wtrap &&
                (e.window.event==SDL_WINDOWEVENT_FOCUS_GAINED || e.window.event==SDL_WINDOWEVENT_FOCUS_LOST))
            g_wproc((void *)(intptr_t)1,0x1c,e.window.event==SDL_WINDOWEVENT_FOCUS_GAINED,0);
    }
    if(!g_wtrap) plat_frame_tick("pump");
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
    if (g_win && !g_wtrap && w > 0 && hh > 0) SDL_SetWindowSize(g_win, w, hh); }
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
        if (plat_fixed_dt()) vt_advance((uint32_t)g_frames * 20u);   /* v2.08: RE_FIXED_DT */
        if (g_frames == 1) fprintf(stderr, "[frame] первый кадр (plat_flip)\n");
        const char *sf = getenv("RE_SHOT_FIRST");
        if (!g_shot_done && sf && *sf == '1') frame_shot();
        if (maxf > 0 && g_frames >= maxf) {
            if (!g_shot_done) frame_shot();
            fprintf(stderr, "[frame] RE_MAX_FRAMES=%d достигнут — выход\n", maxf); fflush(NULL); _Exit(0);
        }
    } else {
        g_pumps++;
        if (plat_fixed_dt()) vt_advance(g_vt + 1);   /* v2.08: цикл сообщений без кадров тоже двигает часы/таймеры */
        if (maxp > 0 && g_pumps >= maxp) { fprintf(stderr, "[frame] RE_MAX_PUMPS=%d (кадров %d) — выход\n", maxp, g_frames); fflush(NULL); _Exit(0); }
    }
}
