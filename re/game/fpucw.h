/* fpucw.h — x87 rounding mode of Game.exe (control word 0057a0e0 / 0057a0e2) for the ported code.
 *
 * Game.exe runs its game logic with the x87 rounding control set to TRUNCATE ("chop") and 24-bit precision:
 *   005283e2 (InitFpuCw_005283E2, from P151_Reopen at display init): finit; fstcw 0057a0e2 (0x37f);
 *            0057a0e0 = (0x37f & 0xfcff) | 0xc00 = 0xc7f; fldcw 0057a0e0
 *   0052840c (P18_ClearFlag, first call of every logic tick P132_GameLogic 004d4bfb): finit; fldcw 0057a0e0
 *   00528455 (NoopFn00528455, shutdown 004264a7): finit; fldcw 0057a0e2 (back to round-to-nearest)
 * so every fistp of the game (Ghidra "ROUND(x)", ported as lrintf/lrintl/fround) truncates toward zero.
 * Map lookups rely on it: (x + 0x2ee + P62_MapC64) * (1/1500) adds half a cell and expects the fistp to
 * truncate (the integer path P72 tile_of does the same with idiv); rounding to nearest picks the
 * neighbouring cell half of the time (the cop route window then sees the player's road cell as a
 * building, P128_CopReplan never finds a route and the patrol stops — v2.34, docs/NATIVE_GAPS.md).
 *
 * Hook build (RE_HOOK_BUILD): the three functions above execute the real fninit/fldcw (ported7.c,
 * ported18.c, ported6.c), lrintf etc. are the C library ones and honour the x87 mode — nothing here.
 * Native build: the rounding mode is emulated only for the float -> integer conversions: this header is
 * force-included into every game source file (CMakeLists.txt) and maps lrintf / lrint / lrintl / llrintl to
 * versions that truncate while re_fpu_chop is set.  Arithmetic rounding and the 24-bit precision of the
 * x87 are not emulated (native float arithmetic is single precision, round to nearest).
 * RE_FPU_CHOP=0 (native debug) keeps round-to-nearest everywhere (behaviour before v2.34).
 */
#ifndef RE_FPUCW_H
#define RE_FPUCW_H
#include <math.h>

extern int re_fpu_chop;            /* 1 while the emulated x87 control word is 0057a0e0 (truncate) */
void re_fpu_load_cw(int chop);     /* fldcw: 1 = 0057a0e0 (truncate), 0 = 0057a0e2 (nearest) */

#ifndef RE_HOOK_BUILD
/* fistp with RC = truncate; outside the int32 range the C library result is kept (x87: integer indefinite). */
static inline long re_lrintf(float v) {
  if (re_fpu_chop && v > -2147483648.0f && v < 2147483648.0f) return (long)(int)v;
  return (lrintf)(v);
}
static inline long re_lrint(double v) {
  if (re_fpu_chop && v > -2147483649.0 && v < 2147483648.0) return (long)(int)v;
  return (lrint)(v);
}
static inline long re_lrintl(long double v) {
  if (re_fpu_chop && v > -2147483649.0L && v < 2147483648.0L) return (long)(int)v;
  return (lrintl)(v);
}
static inline long long re_llrintl(long double v) {
  if (re_fpu_chop && v > -9223372036854775808.0L && v < 9223372036854775808.0L) return (long long)v;
  return (llrintl)(v);
}
#define lrintf(v)  re_lrintf(v)
#define lrint(v)   re_lrint(v)
#define lrintl(v)  re_lrintl(v)
#define llrintl(v) re_llrintl(v)
#endif
#endif
