/* hook.c (hook-сборка, DINPUT.dll): журнал re_driver.log, установка перехватов JMP rel32 поверх функций Game.exe
   (re_hook), переходники для stdcall-функций (stdcall_tbl.h), отключение функций через re_driver.ini [disable]. */
#include "hook.h"
#include <stdio.h>
#include <stdarg.h>
#include <string.h>
static FILE *g_log;
void re_log(const char *fmt, ...) {
    if (!g_log) g_log = fopen("re_driver.log", "w");
    if (!g_log) return;
    va_list ap; va_start(ap, fmt); vfprintf(g_log, fmt, ap); va_end(ap);
    fputc('\n', g_log); fflush(g_log);
}
/* Список функций, отключённых в re_driver.ini (секция [disable], ключ = имя, 1 = выкл) */
static int disabled(const char *name) {
    return GetPrivateProfileIntA("disable", name, 0, ".\\re_driver.ini") != 0;
}
/* Хукнутые функции Game.exe с `ret N` (stdcall): наша реализация — cdecl, поэтому ставим переходник:
   копирует N байт аргументов, зовёт impl, чистит стек и делает `ret N` (реентерабельно). */
static const struct { uint32_t addr; int bytes; } g_std[] = {
#include "stdcall_tbl.h"
    { 0, 0 }
};
static void *make_std_stub(void *impl, int n) {
    unsigned char *b = VirtualAlloc(NULL, 64, MEM_COMMIT | MEM_RESERVE, PAGE_EXECUTE_READWRITE), *p = b;
    if (!b || n <= 0 || n > 120 || (n & 3)) return impl;
    *p++ = 0x55; *p++ = 0x89; *p++ = 0xE5;                       /* push ebp; mov ebp,esp */
    for (int k = n / 4 - 1; k >= 0; k--) { *p++ = 0xFF; *p++ = 0x75; *p++ = (unsigned char)(8 + 4 * k); } /* push [ebp+8+4k] */
    *p++ = 0xB9; *(uint32_t *)p = (uint32_t)(uintptr_t)impl; p += 4;  /* mov ecx,impl */
    *p++ = 0xFF; *p++ = 0xD1;                                    /* call ecx */
    *p++ = 0x83; *p++ = 0xC4; *p++ = (unsigned char)n;           /* add esp,n */
    *p++ = 0x5D; *p++ = 0xC2; *p++ = (unsigned char)n; *p++ = 0; /* pop ebp; ret n */
    FlushInstructionCache(GetCurrentProcess(), b, 64);
    return b;
}
int re_hook(uintptr_t addr, void *impl, const char *name) {
    for (int i = 0; g_std[i].addr; i++) if (g_std[i].addr == addr) { impl = make_std_stub(impl, g_std[i].bytes); break; }
    if (disabled(name)) { re_log("skip   %08x %s (disabled in ini)", (unsigned)addr, name); return 0; }
    unsigned char *p = (unsigned char *)addr; DWORD old;
    if (!VirtualProtect(p, 5, PAGE_EXECUTE_READWRITE, &old)) { re_log("FAIL   %08x %s", (unsigned)addr, name); return 0; }
    p[0] = 0xE9; *(int32_t *)(p + 1) = (int32_t)((uintptr_t)impl - (addr + 5));
    VirtualProtect(p, 5, old, &old);
    FlushInstructionCache(GetCurrentProcess(), p, 5);
    re_log("hook   %08x %s", (unsigned)addr, name);
    return 1;
}
