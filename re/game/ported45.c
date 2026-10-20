/* ported45.c — small front-end menu helpers (English overview; original notes follow).
   Switching a menu item between its two variants, a short blocking "wait" animation, and picking a
   button colour by the selected level.  All cdecl. */
/* Меню и ожидание — восстановлено из Game.exe (cdecl). */
#include "ported45.h"
#include "ported58.h"
#include "reptr.h"
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P45_Mode")
#undef P45_Mode
#pragma push_macro("P45_Mode") /*gvi*/
#undef P45_Mode /*gvi*/
int32_t P45_Mode;
#pragma pop_macro("P45_Mode") /*gvi*/
#pragma pop_macro("P45_Mode")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P45_PtrA")
#undef P45_PtrA
#pragma push_macro("P45_PtrA") /*gvi*/
#undef P45_PtrA /*gvi*/
uint32_t P45_PtrA;
#pragma pop_macro("P45_PtrA") /*gvi*/
#pragma pop_macro("P45_PtrA")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P45_Busy")
#undef P45_Busy
#pragma push_macro("P45_Busy") /*gvi*/
#undef P45_Busy /*gvi*/
int32_t P45_Busy;
#pragma pop_macro("P45_Busy") /*gvi*/
#pragma pop_macro("P45_Busy")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P45_Step")
#undef P45_Step
#pragma push_macro("P45_Step") /*gvi*/
#undef P45_Step /*gvi*/
int32_t P45_Step;
#pragma pop_macro("P45_Step") /*gvi*/
#pragma pop_macro("P45_Step")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P45_Pick")
#undef P45_Pick
#pragma push_macro("P45_Pick") /*gvi*/
#undef P45_Pick /*gvi*/
int32_t P45_Pick;
#pragma pop_macro("P45_Pick") /*gvi*/
#pragma pop_macro("P45_Pick")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P45_Color")
#undef P45_Color
#pragma push_macro("P45_Color") /*gvi*/
#undef P45_Color /*gvi*/
uint32_t P45_Color;
#pragma pop_macro("P45_Color") /*gvi*/
#pragma pop_macro("P45_Color")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P45_Col0")
#undef P45_Col0
#pragma push_macro("P45_Col0") /*gvi*/
#undef P45_Col0 /*gvi*/
uint32_t P45_Col0;
#pragma pop_macro("P45_Col0") /*gvi*/
#pragma pop_macro("P45_Col0")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P45_Col1")
#undef P45_Col1
#pragma push_macro("P45_Col1") /*gvi*/
#undef P45_Col1 /*gvi*/
uint32_t P45_Col1;
#pragma pop_macro("P45_Col1") /*gvi*/
#pragma pop_macro("P45_Col1")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P45_Col2")
#undef P45_Col2
#pragma push_macro("P45_Col2") /*gvi*/
#undef P45_Col2 /*gvi*/
uint32_t P45_Col2;
#pragma pop_macro("P45_Col2") /*gvi*/
#pragma pop_macro("P45_Col2")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P45_Col3")
#undef P45_Col3
#pragma push_macro("P45_Col3") /*gvi*/
#undef P45_Col3 /*gvi*/
uint32_t P45_Col3;
#pragma pop_macro("P45_Col3") /*gvi*/
#pragma pop_macro("P45_Col3")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P45_Col4")
#undef P45_Col4
#pragma push_macro("P45_Col4") /*gvi*/
#undef P45_Col4 /*gvi*/
uint32_t P45_Col4;
#pragma pop_macro("P45_Col4") /*gvi*/
#pragma pop_macro("P45_Col4")
#endif

/* P45_ModeA — Game.exe 0040834f.  Maps the current item code P45_Mode to its "A" variant (0x2e..0x31;
   the "B" codes 0x92..0x95 map back), redraws the menu (0040cd17, 0040c455(1, 0)).  Returns 1.
   TODO(RE): unsure what the A/B variants are on screen. */
int32_t P45_ModeA(void) {
  switch (P45_Mode) {
    case 0x2e: case 0x92: P45_Mode = 0x2e; break;
    case 0x2f: case 0x93: P45_Mode = 0x2f; break;
    case 0x30: case 0x94: P45_Mode = 0x30; break;
    case 0x31: case 0x95: P45_Mode = 0x31; break;
    default: break;
  }
  MenuAction40CD17();
  Call3_0040C455(1, 0);
  return 1;
}
/* P45_ModeB — Game.exe 00408458.  Same as P45_ModeA but selects the "B" variant 0x92..0x95.  Returns 1. */
int32_t P45_ModeB(void) {
  switch (P45_Mode) {
    case 0x2e: case 0x92: P45_Mode = 0x92; break;
    case 0x2f: case 0x93: P45_Mode = 0x93; break;
    case 0x30: case 0x94: P45_Mode = 0x94; break;
    case 0x31: case 0x95: P45_Mode = 0x95; break;
    default: break;
  }
  MenuAction40CD17();
  Call3_0040C455(1, 0);
  return 1;
}
/* P45_Wait — Game.exe 0040ccb4.  Sets the menu item list (P58_ItemList = items_addr, a Game.exe address
   translated with re_ptr) and P45_PtrA = b, then runs 6 frames with P45_Busy = 1 and P45_Step counting
   5..0 (messages 00522323, input, draw 0040cb9f); finally restarts the menu timer (004086b4). */
void P45_Wait(uint32_t items_addr, uint32_t b) {
  P58_ItemList = (int16_t *)re_ptr(items_addr);   /* бывший P45_PtrB: тот же 005f7e64 */
  P45_PtrA = b;
  P45_Busy = 1;
  for (int32_t step = 5; step > -1; step--) {
    Call00522323();
    P36_PollInput();
    P45_Step = step;
    Call0040CB9F();
  }
  P45_Busy = 0;
  StartTimer004086B4();
}
/* P45_PickColor — Game.exe 00417cbb.  P45_Color = P45_Col0..4 by P45_Pick (other values keep it), black
   background and a fade/flash towards (0xff, 0xff, 0x80) over 0x32 steps (0051707a). */
void P45_PickColor(void) {
  switch (P45_Pick) {
    case 0: P45_Color = P45_Col0; break;
    case 1: P45_Color = P45_Col1; break;
    case 2: P45_Color = P45_Col2; break;
    case 3: P45_Color = P45_Col3; break;
    case 4: P45_Color = P45_Col4; break;
    default: break;
  }
  SetRGB00516EB4(0, 0, 0);
  SetFade0051707A(0xff, 0xff, 0x80, 0x32);
}
