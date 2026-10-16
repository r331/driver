#include "../plat.h"
#include <SDL.h>
#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <strings.h>
#include <dirent.h>
#include <limits.h>
static SDL_Window *g_win; static SDL_GLContext g_gl;
static void swap_win(void){ SDL_GL_SwapWindow(g_win); }
uint32_t plat_time_ms(void){ return SDL_GetTicks(); }
void plat_sleep_ms(uint32_t ms){ SDL_Delay(ms); }
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
    SDL_ShowSimpleMessageBox((flags&0x10)?SDL_MESSAGEBOX_ERROR:((flags&0x30)==0x30?SDL_MESSAGEBOX_WARNING:SDL_MESSAGEBOX_INFORMATION),g_mb_title,g_mb_text,g_win);
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
static void crash_sig(int sig){ signal(sig,SIG_DFL); if(g_crash) g_crash(); _Exit(1); }
void plat_set_crash_handler(void (*fn)(void)){
    g_crash=fn;
    void (*h)(int)= fn?crash_sig:SIG_DFL;
    signal(SIGSEGV,h); signal(SIGFPE,h); signal(SIGILL,h);
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
    SDL_Event e; while(SDL_PollEvent(&e)) if(e.type==SDL_QUIT) g_wquit=1;
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
