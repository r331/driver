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
int re_hook(uintptr_t addr, void *impl, const char *name) {
    if (disabled(name)) { re_log("skip   %08x %s (disabled in ini)", (unsigned)addr, name); return 0; }
    unsigned char *p = (unsigned char *)addr; DWORD old;
    if (!VirtualProtect(p, 5, PAGE_EXECUTE_READWRITE, &old)) { re_log("FAIL   %08x %s", (unsigned)addr, name); return 0; }
    p[0] = 0xE9; *(int32_t *)(p + 1) = (int32_t)((uintptr_t)impl - (addr + 5));
    VirtualProtect(p, 5, old, &old);
    FlushInstructionCache(GetCurrentProcess(), p, 5);
    re_log("hook   %08x %s", (unsigned)addr, name);
    return 1;
}
