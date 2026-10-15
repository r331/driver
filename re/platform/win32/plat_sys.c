/* hook-вариант plat: система через WinAPI (только в DLL-сборке) */
#include "../plat.h"
#include <windows.h>
#include <stdio.h>
#include <stdarg.h>
uint32_t plat_time_ms(void){ return GetTickCount(); }
void plat_sleep_ms(uint32_t ms){ Sleep(ms); }
void plat_log(const char *f, ...){ char b[512]; va_list a; va_start(a,f); vsnprintf(b,sizeof b,f,a); va_end(a); OutputDebugStringA(b); }
void *plat_file_open(const char *p, const char *m){ return fopen(p,m); }
void plat_local_hms(int *h,int *m,int *s){ SYSTEMTIME st; GetLocalTime(&st); *h=st.wHour; *m=st.wMinute; *s=st.wSecond; }
