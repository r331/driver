/* ported18.c — one tiny helper: clears the 16-bit flag word P18_Flag0057A0E6 (Game.exe 0057a0e6).
   TODO(RE): unsure what the flag means; only this clear is ported. */
#include "ported18.h"
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P18_Flag0057A0E6")
#undef P18_Flag0057A0E6
#pragma push_macro("P18_Flag0057A0E6") /*gvi*/
#undef P18_Flag0057A0E6 /*gvi*/
uint16_t P18_Flag0057A0E6;
#pragma pop_macro("P18_Flag0057A0E6") /*gvi*/
#pragma pop_macro("P18_Flag0057A0E6")
#endif
/* P18_ClearFlag — Game.exe 0052840c, cdecl.  Sets the 16-bit word P18_Flag0057A0E6 to 0. */
void P18_ClearFlag(void) { P18_Flag0057A0E6 = 0; }
