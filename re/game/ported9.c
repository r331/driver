/* ported9.c — three small unrelated helpers (batch v0.44): pick a value by a menu option, reset a
   100-slot table, and edge-triggered joystick buttons for menus. */
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
/* SelectByDifficulty_00416D17 — Game.exe 00416d17, cdecl.  P9_0054e258 = one of four values chosen by
   P9_005fe9f0 (1 -> 00c55a4c, 2 -> 00c55a50, 3 -> 00c55a54, anything else -> 00c55a48).  The motel menu
   (P124_MotelKeys) cycles P9_005fe9f0 through 0..3 with left/right and calls this after each change.
   TODO(RE): unsure — the "difficulty" in the name is Ghidra-era; what the four values are is not confirmed. */
void SelectByDifficulty_00416D17(void) {
  if (P9_005fe9f0 == 1) P9_0054e258 = P9_00c55a4c;
  else if (P9_005fe9f0 == 2) P9_0054e258 = P9_00c55a50;
  else if (P9_005fe9f0 == 3) P9_0054e258 = P9_00c55a54;
  else P9_0054e258 = P9_00c55a48; }
/* ResetSlots_004A2B70 — Game.exe 004a2b70, cdecl.  Clears three counters and D_01134ea0, zeroes the
   table A_01134540 (100 records x 24 bytes = 0x960), then stores i both in D_01134ec0[i] and in the first
   dword of record i (identity free-list / index), and clears D_01134528.
   TODO(RE): unsure what the 100 slots hold. */
void ResetSlots_004A2B70(void) {
#ifdef RE_HOOK_BUILD
  P9_01134530 = 0; P9_0113452c = 0; P9_011342e8 = 0; D_01134ea0 = 0;
#else
  P9_01134530 = 0; P9_0113452c = 0; P58_Grid = NULL; D_01134ea0 = 0;   /* 011342e8 = the chair grid pointer P58_Grid (v2.35) */
#endif
  memset(&A_01134540[0], 0, 0x960);
  for (int32_t i = 0; i < 100; i++) { D_01134ec0[i] = i; memcpy(&A_01134540[i*24], &i, 4); }
  D_01134528 = 0; }
/* IsButtonActive_004E3924 — Game.exe 004e3924, cdecl.  "Pressed this frame" test for a joystick input:
     i == 0x20: stick pushed up   — Y axis now < -14 and previous Y > -15 (P9_00b31e20 = DIJOYSTATE.lY,
                                    alias of P21_AxisValue; P9_00b31dfc = last frame's lY);
     i == 0x21: stick pushed down — Y now > 14 and previous Y < 15;
     i == 0x22: never;
     otherwise: button i down now and up last frame (P9_00b31db8 = DIJOYSTATE.rgbButtons at 00b31d88+0x30,
                P9_00b31d30 = previous state's buttons).
   Returns 1 / 0.  Used by the joystick menu mapping in ported36.c (button 0 = Enter, 1 = Esc). */
uint32_t IsButtonActive_004E3924(uint8_t i) {
  if (i == 0x20) { if (P9_00b31e20 < -0xe && -0xf < P9_00b31dfc) return 1; }
  else if (i == 0x21) { if (0xe < P9_00b31e20 && P9_00b31dfc < 0xf) return 1; }
  else if (i != 0x22 && P9_00b31db8[i] != 0 && P9_00b31d30[i] == 0) return 1;
  return 0; }
