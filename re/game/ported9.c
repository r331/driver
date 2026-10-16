#include "ported9.h"
#include <string.h>
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P9_01134530")
#undef P9_01134530
#pragma push_macro("P9_01134530") /*gvi*/
#undef P9_01134530 /*gvi*/
int32_t P9_01134530;
#pragma pop_macro("P9_01134530") /*gvi*/
#pragma pop_macro("P9_01134530")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P9_0113452c")
#undef P9_0113452c
#pragma push_macro("P9_0113452c") /*gvi*/
#undef P9_0113452c /*gvi*/
int32_t P9_0113452c;
#pragma pop_macro("P9_0113452c") /*gvi*/
#pragma pop_macro("P9_0113452c")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P9_011342e8")
#undef P9_011342e8
#pragma push_macro("P9_011342e8") /*gvi*/
#undef P9_011342e8 /*gvi*/
int32_t P9_011342e8;
#pragma pop_macro("P9_011342e8") /*gvi*/
#pragma pop_macro("P9_011342e8")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P9_005fe9f0")
#undef P9_005fe9f0
#pragma push_macro("P9_005fe9f0") /*gvi*/
#undef P9_005fe9f0 /*gvi*/
int32_t P9_005fe9f0;
#pragma pop_macro("P9_005fe9f0") /*gvi*/
#pragma pop_macro("P9_005fe9f0")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P9_00c55a48")
#undef P9_00c55a48
#pragma push_macro("P9_00c55a48") /*gvi*/
#undef P9_00c55a48 /*gvi*/
int32_t P9_00c55a48;
#pragma pop_macro("P9_00c55a48") /*gvi*/
#pragma pop_macro("P9_00c55a48")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P9_00c55a4c")
#undef P9_00c55a4c
#pragma push_macro("P9_00c55a4c") /*gvi*/
#undef P9_00c55a4c /*gvi*/
int32_t P9_00c55a4c;
#pragma pop_macro("P9_00c55a4c") /*gvi*/
#pragma pop_macro("P9_00c55a4c")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P9_00c55a50")
#undef P9_00c55a50
#pragma push_macro("P9_00c55a50") /*gvi*/
#undef P9_00c55a50 /*gvi*/
int32_t P9_00c55a50;
#pragma pop_macro("P9_00c55a50") /*gvi*/
#pragma pop_macro("P9_00c55a50")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P9_00c55a54")
#undef P9_00c55a54
#pragma push_macro("P9_00c55a54") /*gvi*/
#undef P9_00c55a54 /*gvi*/
int32_t P9_00c55a54;
#pragma pop_macro("P9_00c55a54") /*gvi*/
#pragma pop_macro("P9_00c55a54")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P9_0054e258")
#undef P9_0054e258
#pragma push_macro("P9_0054e258") /*gvi*/
#undef P9_0054e258 /*gvi*/
int32_t P9_0054e258;
#pragma pop_macro("P9_0054e258") /*gvi*/
#pragma pop_macro("P9_0054e258")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P9_00b31e20")
#undef P9_00b31e20
#pragma push_macro("P9_00b31e20") /*gvi*/
#undef P9_00b31e20 /*gvi*/
int32_t P9_00b31e20;
#pragma pop_macro("P9_00b31e20") /*gvi*/
#pragma pop_macro("P9_00b31e20")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P9_00b31dfc")
#undef P9_00b31dfc
#pragma push_macro("P9_00b31dfc") /*gvi*/
#undef P9_00b31dfc /*gvi*/
int32_t P9_00b31dfc;
#pragma pop_macro("P9_00b31dfc") /*gvi*/
#pragma pop_macro("P9_00b31dfc")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P9_00b31db8")
#undef P9_00b31db8
#pragma push_macro("P9_00b31db8") /*gvi*/
#undef P9_00b31db8 /*gvi*/
g8_bytes_t P9_00b31db8;
#pragma pop_macro("P9_00b31db8") /*gvi*/
#pragma pop_macro("P9_00b31db8")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P9_00b31d30")
#undef P9_00b31d30
#pragma push_macro("P9_00b31d30") /*gvi*/
#undef P9_00b31d30 /*gvi*/
g8_bytes_t P9_00b31d30;
#pragma pop_macro("P9_00b31d30") /*gvi*/
#pragma pop_macro("P9_00b31d30")
#endif
void SelectByDifficulty_00416D17(void) {
  if (P9_005fe9f0 == 1) P9_0054e258 = P9_00c55a4c;
  else if (P9_005fe9f0 == 2) P9_0054e258 = P9_00c55a50;
  else if (P9_005fe9f0 == 3) P9_0054e258 = P9_00c55a54;
  else P9_0054e258 = P9_00c55a48; }
void ResetSlots_004A2B70(void) {
  P9_01134530 = 0; P9_0113452c = 0; P9_011342e8 = 0; D_01134ea0 = 0;
  memset(&A_01134540[0], 0, 0x960);
  for (int32_t i = 0; i < 100; i++) { D_01134ec0[i] = i; memcpy(&A_01134540[i*24], &i, 4); }
  D_01134528 = 0; }
uint32_t IsButtonActive_004E3924(uint8_t i) {
  if (i == 0x20) { if (P9_00b31e20 < -0xe && -0xf < P9_00b31dfc) return 1; }
  else if (i == 0x21) { if (0xe < P9_00b31e20 && P9_00b31dfc < 0xf) return 1; }
  else if (i != 0x22 && P9_00b31db8[i] != 0 && P9_00b31d30[i] == 0) return 1;
  return 0; }
