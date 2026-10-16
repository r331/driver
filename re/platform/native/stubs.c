/* Нативные заглушки для ещё не перенесённых функций Game.exe (список — game/unported.h). */
#include "../../game/unported.h"
#include "../../game/engine.h"
#include <stdio.h>
static void not_ported(const char *name, unsigned addr) {
    char m[128]; snprintf(m, sizeof m, "not ported: %s (%08x)", name, addr); DebugLog(m);
}
#define STUB_V(name, addr, params, args)      __attribute__((weak)) void name params { not_ported(#name, addr); }
#define STUB_R(ret, name, addr, params, args) __attribute__((weak)) ret name params { not_ported(#name, addr); return (ret)0; }
UNPORTED_LIST(STUB_V, STUB_R)
void G6Call0041F57D(int32_t a0, int32_t a1, int32_t a2) { (void)a0; (void)a1; (void)a2; not_ported("G6Call0041F57D", 0x0041f57d); }
