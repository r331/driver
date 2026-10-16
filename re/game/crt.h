/* Файловый ввод-вывод. В hook-сборке — CRT самой игры (FILE* из Game.exe), в native — libc. */
#pragma once
#include "gvar.h"
#ifdef RE_HOOK_BUILD
#  define g_fread  ((size_t(__cdecl*)(void*, size_t, size_t, void*))0x0052aaf0)
#  define g_remove ((int   (__cdecl*)(const char*))0x0052b1f0)
#  define g_fwrite ((size_t(__cdecl*)(const void*, size_t, size_t, void*))0x0052ae80)
#  define g_ftell  ((long  (__cdecl*)(void*))0x0052b260)
#  define g_fseek  ((int   (__cdecl*)(void*, long, int))0x0052b4f0)
#  define g_fopen  ((void* (__cdecl*)(const char*, const char*))0x0052adb0)
#  define g_fclose ((int   (__cdecl*)(void*))0x0052aa10)
#  define g_fgets  ((char* (__cdecl*)(char*, int, void*))0x0052c000)
#  define g_fgetc  ((int  (__cdecl*)(void*))0x0052baf0)
#  define g_sscanf ((int  (__cdecl*)(const char*, const char*, ...))0x0052e250)
#  define g_fscanf ((int  (__cdecl*)(void*, const char*, ...))0x0052e1c0)
#  define g_malloc ((void* (__cdecl*)(size_t))0x0052c130)
#  define g_free   ((void  (__cdecl*)(void*))0x0052cb70)
#  define g_mkdir  ((int   (__cdecl*)(const char*))0x0053fa70)   /* v1.85: _mkdir */
#else
#  include <stdio.h>
#  define g_fread(p, s, n, f)  fread((p), (s), (n), (FILE*)(f))
#  define g_remove(n)          plat_remove_game((n))   /* v2.04: тот же перевод пути, что у g_fopen */
#  define g_fwrite(p, s, n, f) fwrite((p), (s), (n), (FILE*)(f))
#  define g_ftell(f)           ftell((FILE*)(f))
#  define g_fseek(f, o, w)     fseek((FILE*)(f), (o), (w))
void *plat_fopen_game(const char *path, const char *mode);   /* v2.00: пути Windows → native */
#  define g_fopen(n, m)        plat_fopen_game((n), (m))
#  define g_fclose(f)          fclose((FILE*)(f))
#  include <string.h>
/* v2.03: fgets текстового режима MSVC — «\r\n» → «\n» (файлы данных с CRLF: MLADDER.DML давал «[MIAMI]\r» → Unknown CITY) */
static inline char *re_crt_fgets(char *b, int n, void *f) {
  char *r = fgets(b, n, (FILE *)f);
  if (r != NULL) { size_t l = strlen(b); if (l >= 2 && b[l - 2] == '\r' && b[l - 1] == '\n') { b[l - 2] = '\n'; b[l - 1] = 0; } }
  return r;
}
#  define g_fgets(b, n, f)     re_crt_fgets((b), (n), (f))
#  define g_fgetc(f)           fgetc((FILE*)(f))
#  define g_sscanf             sscanf
#  define g_fscanf(f, ...)     fscanf((FILE*)(f), __VA_ARGS__)
#  include <stdlib.h>
#  define g_malloc(n)          malloc((n))
#  define g_free(p)            free((p))
int re_crt_mkdir(const char *path);   /* v1.85: _mkdir (native — game/ported140.c) */
#  define g_mkdir(n)           re_crt_mkdir((n))
#endif
