/* hook-вариант plat: система через WinAPI (только в DLL-сборке) */
#include "../plat.h"
#include <windows.h>
#include <stdio.h>
#include <string.h>
#include <stdarg.h>
uint32_t plat_time_ms(void){ return GetTickCount(); }
void plat_sleep_ms(uint32_t ms){ Sleep(ms); }
void plat_log(const char *f, ...){ char b[512]; va_list a; va_start(a,f); vsnprintf(b,sizeof b,f,a); va_end(a); OutputDebugStringA(b); }
void *plat_file_open(const char *p, const char *m){ return fopen(p,m); }
void plat_local_hms(int *h,int *m,int *s){ SYSTEMTIME st; GetLocalTime(&st); *h=st.wHour; *m=st.wMinute; *s=st.wSecond; }
void plat_window_maximize(void *wnd){ ShowWindow((HWND)wnd, SW_MAXIMIZE); }
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
