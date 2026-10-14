/* Файловый ввод-вывод. В hook-сборке — CRT самой игры (FILE* из Game.exe), в native — libc. */
#pragma once
#include "gvar.h"
#ifdef RE_HOOK_BUILD
#  define g_fwrite ((size_t(__cdecl*)(const void*, size_t, size_t, void*))0x0052ae80)
#  define g_ftell  ((long  (__cdecl*)(void*))0x0052b260)
#  define g_fseek  ((int   (__cdecl*)(void*, long, int))0x0052b4f0)
#  define g_fopen  ((void* (__cdecl*)(const char*, const char*))0x0052adb0)
#  define g_fclose ((int   (__cdecl*)(void*))0x0052aa10)
#else
#  include <stdio.h>
#  define g_fwrite(p, s, n, f) fwrite((p), (s), (n), (FILE*)(f))
#  define g_ftell(f)           ftell((FILE*)(f))
#  define g_fseek(f, o, w)     fseek((FILE*)(f), (o), (w))
#  define g_fopen(n, m)        ((void*)fopen((n), (m)))
#  define g_fclose(f)          fclose((FILE*)(f))
#endif
