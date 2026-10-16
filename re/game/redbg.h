/* v2.05: счётчики отладки кадра (RE_GSTAT=N — печать раз в N кадров, platform/sdl/plat_sys.c). В hook — пусто. */
#ifndef REDBG_H
#define REDBG_H
#ifndef RE_HOOK_BUILD
extern int g_re_dbg[16];
#define RE_DBG(i) (g_re_dbg[i]++)
#define RE_DBG_SET(i, v) (g_re_dbg[i] = (int)(v))
#else
#define RE_DBG(i) ((void)0)
#define RE_DBG_SET(i, v) ((void)0)
#endif
#endif
