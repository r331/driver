/* hook-вариант plat: система через WinAPI (только в DLL-сборке) */
#include "../plat.h"
#include <windows.h>
#include <objbase.h>
#include <stdio.h>
#include <string.h>
#include <stdarg.h>
uint32_t plat_time_ms(void){ return GetTickCount(); }
void plat_vt_poll(void){}   /* v2.08: RE_FIXED_DT только в native */
void plat_sleep_ms(uint32_t ms){ Sleep(ms); }
void plat_log(const char *f, ...){ char b[512]; va_list a; va_start(a,f); vsnprintf(b,sizeof b,f,a); va_end(a); OutputDebugStringA(b); }
void *plat_file_open(const char *p, const char *m){ return fopen(p,m); }
void plat_local_hms(int *h,int *m,int *s){ SYSTEMTIME st; GetLocalTime(&st); *h=st.wHour; *m=st.wMinute; *s=st.wSecond; }
void plat_window_maximize(void *wnd){ ShowWindow((HWND)wnd, SW_MAXIMIZE); }
void plat_window_client_rect(void *h, int32_t *rc){ RECT r; GetClientRect((HWND)h, &r); rc[0] = r.left; rc[1] = r.top; rc[2] = r.right; rc[3] = r.bottom; }
void plat_client_to_screen(void *h, int32_t *pt){ POINT p; p.x = pt[0]; p.y = pt[1]; ClientToScreen((HWND)h, &p); pt[0] = p.x; pt[1] = p.y; }
void plat_utc_hms(int *h,int *m,int *s){ SYSTEMTIME st; GetSystemTime(&st); *h=st.wHour; *m=st.wMinute; *s=st.wSecond; }
int plat_message_box(void *hwnd,const char *text,const char *title,unsigned flags){ return MessageBoxA((HWND)hwnd,text,title,flags); }
int plat_message_box_last(const char **text,const char **title){ if(text)*text=""; if(title)*title=""; return 0; }
void plat_wave_set_volume(uint32_t lr){ waveOutSetVolume((HWAVEOUT)0,lr); }
uint32_t plat_wave_volume(void){ return 0; }
int plat_cd_roots(char *buf,int size){
    char all[256]; DWORD r=GetLogicalDriveStringsA(sizeof all,all); int n=0; if(size>0) buf[0]=0; if(r==0) return 0;
    for(const char *p=all;*p;p+=strlen(p)+1){
        if(GetDriveTypeA(p)!=5) continue;
        int l=(int)strlen(p); if(n+l+2>=size) break; memcpy(buf+n,p,(size_t)l+1); n+=l+1; }
    buf[n]=0; return n;
}

/* --- выход, хранитель экрана, обработчик аварий --- */
static int g_exit_trap, g_exit_last;
static void (*g_crash)(void);
void plat_exit_trap(int on){ g_exit_trap=on; }
int plat_exit_last(void){ return g_exit_last; }
void plat_exit(int code){ g_exit_last=code; if(g_exit_trap) return; ((void(__cdecl*)(int,int,int))0x0052e480)(code,0,0); }
int plat_screensaver_get(void){ BOOL b=0; SystemParametersInfoA(SPI_GETSCREENSAVEACTIVE,0,&b,0); return (int)b; }
void plat_screensaver_set(int on){ SystemParametersInfoA(SPI_SETSCREENSAVEACTIVE,(UINT)on,NULL,0); }
static LONG WINAPI crash_filter(EXCEPTION_POINTERS *ep){ (void)ep; if(g_crash) g_crash(); return EXCEPTION_EXECUTE_HANDLER; }
void plat_set_crash_handler(void (*fn)(void)){ g_crash=fn; SetUnhandledExceptionFilter(fn?crash_filter:NULL); }
void (*plat_crash_handler(void))(void){ return g_crash; }

/* --- окно игры, цикл сообщений --- */
static plat_wndproc g_wp;
static LRESULT CALLBACK wnd_tramp(HWND h, UINT m, WPARAM w, LPARAM l){
    /* v1.95: lparam WM_CREATE передаётся как есть (CREATESTRUCTA*), hInstance берёт игра через plat_wm_create_hinst */
    return (LRESULT)g_wp((void*)h,m,(uint32_t)w,(int32_t)l);
}
void *plat_game_window_create(void *hinst,int32_t show,const char *title,int w,int h,plat_wndproc proc){
    WNDCLASSA wc; g_wp=proc;
    wc.style=3; wc.lpfnWndProc=wnd_tramp; wc.cbClsExtra=0; wc.cbWndExtra=0; wc.hInstance=(HINSTANCE)hinst;
    wc.hIcon=LoadIconA((HINSTANCE)hinst,(LPCSTR)0x7f00); wc.hCursor=LoadCursorA(NULL,(LPCSTR)0x7f00);
    wc.hbrBackground=CreateSolidBrush(0); wc.lpszMenuName=NULL; wc.lpszClassName="Driver";
    RegisterClassA(&wc);
    HWND hw=CreateWindowExA(0,"Driver",title,0x80000000,0,0,w,h,NULL,NULL,(HINSTANCE)hinst,NULL);
    if(hw) ShowWindow(hw,show);
    return (void*)hw;
}
void plat_pump_messages(void){ MSG m; while(PeekMessageA(&m,NULL,0,0,0)){ GetMessageA(&m,NULL,0,0); TranslateMessage(&m); DispatchMessageA(&m); } }
void plat_set_priority(int level){ SetPriorityClass(GetCurrentProcess(), level==0?0x20:(level==1?0x80:0x100)); }
void plat_post_quit(int code){ PostQuitMessage(code); }
void plat_post_close(void *hwnd){ PostMessageA((HWND)hwnd,WM_CLOSE,0,0); }
void plat_set_cursor(int visible){ SetCursor(visible?LoadCursorA(NULL,(LPCSTR)0x7f00):NULL); }
int32_t plat_def_window_proc(void *hwnd,uint32_t msg,uint32_t wp,int32_t lp){ return (int32_t)DefWindowProcA((HWND)hwnd,msg,wp,(LPARAM)lp); }
void plat_dll_unload(void *mod){ FreeLibrary((HMODULE)mod); }
void *plat_dll_load(const char *name){ return (void*)LoadLibraryA(name); }
void *plat_dll_proc(void *mod, const char *name){ return (void*)GetProcAddress((HMODULE)mod, name); }
void *plat_lock_resource(void *res){ return LockResource((HGLOBAL)res); }
void plat_win_trap(int on){ (void)on; }
int plat_win_state(int *a,int *b,int *c,int *d,int *e,int *f,const char **g,plat_wndproc *h){ (void)a;(void)b;(void)c;(void)d;(void)e;(void)f;(void)g;(void)h; return 0; }
void plat_event_close(void *h){ CloseHandle((HANDLE)h); }

int plat_com_init(void){ return (int)CoInitialize(NULL); }
void plat_com_uninit(void){ CoUninitialize(); }
int plat_com_count(void){ return 0; }
/* v1.95: окно — UpdateWindow/SetForegroundWindow (0048a940), WM_CREATE (005224a8) */
void plat_window_update(void *h){ UpdateWindow((HWND)h); }
void plat_window_foreground(void *h){ SetForegroundWindow((HWND)h); }
int32_t plat_wm_create_hinst(int32_t lp){ return lp ? (int32_t)(intptr_t)((CREATESTRUCTA*)(intptr_t)lp)->hInstance : 0; }
/* v1.96: MoveWindow (00425f7b), GetActiveWindow (0041ed98), SetCursor/GetCurrentProcess/LoadAcceleratorsA (00521f10) */
void plat_window_move(void *h, int x, int y, int w, int hh, int rep){ MoveWindow((HWND)h, x, y, w, hh, rep); }
int plat_win_moves(int32_t *l){ (void)l; return 0; }
void *plat_window_active(void){ return (void*)GetActiveWindow(); }
void *plat_cursor_set(void *c){ return (void*)SetCursor((HCURSOR)c); }
void *plat_current_process(void){ return (void*)GetCurrentProcess(); }
void *plat_load_accelerators(void *hinst, const char *name){ return (void*)LoadAcceleratorsA((HINSTANCE)hinst, name); }
