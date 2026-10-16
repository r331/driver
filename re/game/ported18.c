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
void P18_ClearFlag(void) { P18_Flag0057A0E6 = 0; }
