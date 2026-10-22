/* ported18.c — one tiny helper: clears the 16-bit flag word P18_Flag0057A0E6 (Game.exe 0057a0e6).
   TODO(RE): unsure what the flag means; only this clear is ported. */
#include "ported18.h"
#include "ported7.h"   /* G8_0057A0E0_u16 */
#include "fpucw.h"
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P18_Flag0057A0E6")
#undef P18_Flag0057A0E6
#pragma push_macro("P18_Flag0057A0E6") /*gvi*/
#undef P18_Flag0057A0E6 /*gvi*/
uint16_t P18_Flag0057A0E6;
#pragma pop_macro("P18_Flag0057A0E6") /*gvi*/
#pragma pop_macro("P18_Flag0057A0E6")
#endif
/* P18_ClearFlag — Game.exe 0052840c, cdecl.  Sets the word P18_Flag0057A0E6 to 0, then finit; fldcw 0057a0e0 — reloads the
   truncating x87 control word (InitFpuCw_005283E2) at the start of every logic tick (P132_GameLogic 004d4bfb).
   v2.34: the fldcw was missing (see fpucw.h).  Hook: the real fninit/fldcw; native: re_fpu_load_cw emulates it. */
void P18_ClearFlag(void) {
  P18_Flag0057A0E6 = 0;
#if defined(RE_HOOK_BUILD) && (defined(__i386__) || defined(__x86_64__))
  __asm__ volatile("fninit\n\tfldcw %0" : : "m"(G8_0057A0E0_u16));
#endif
  re_fpu_load_cw(1);
}
