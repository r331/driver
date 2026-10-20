/* menustate.c — tiny frontend-menu handlers from Game.exe (cdecl): option toggles, redraw requests, mode enter /
   leave pairs, colour / position setters.  Each function is tagged with its Game.exe address; names carry the
   address of the variable they touch, because the options' meanings are not established (TODO(RE)).
   Note: about 60 of these addresses are also implemented in uihandlers4.c (the hook DLL installs the last
   re_hook, native fn_table.c the first) — see docs/DEAD_CODE_AUDIT.md; do not rename either copy. */
#include "menustate.h"
#include "unported.h"
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("MenuFlag5F7E4C")
#undef MenuFlag5F7E4C
#pragma push_macro("MenuFlag5F7E4C") /*gvi*/
#undef MenuFlag5F7E4C /*gvi*/
int32_t MenuFlag5F7E4C;
#pragma pop_macro("MenuFlag5F7E4C") /*gvi*/
#pragma pop_macro("MenuFlag5F7E4C")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("MenuState575EF0")
#undef MenuState575EF0
#pragma push_macro("MenuState575EF0") /*gvi*/
#undef MenuState575EF0 /*gvi*/
int32_t MenuState575EF0;
#pragma pop_macro("MenuState575EF0") /*gvi*/
#pragma pop_macro("MenuState575EF0")
#endif
/* MenuFlagSet — Game.exe 00404687 */
void MenuFlagSet(void) { MenuFlag5F7E4C = 1; }
/* MenuFlagUpdate — Game.exe 00404696 */
void MenuFlagUpdate(int mode) { if (mode == 0 || mode == 2) MenuFlag5F7E4C = 0; }
/* MenuStateSetFour — Game.exe 00404f5f */
int MenuStateSetFour(void) { MenuState575EF0 = 4; return 0; }
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("MenuOptBDFA44")
#undef MenuOptBDFA44
#pragma push_macro("MenuOptBDFA44") /*gvi*/
#undef MenuOptBDFA44 /*gvi*/
int32_t MenuOptBDFA44;
#pragma pop_macro("MenuOptBDFA44") /*gvi*/
#pragma pop_macro("MenuOptBDFA44")
#endif
/* Seven on/off menu options (MenuOpt*): toggle and refresh the menu.  The same variables select the row icons in
   P54_MenuTexSel and gate damage / cop behaviour elsewhere (e.g. ported129.c). */
/* MenuToggleOptBDFA44 — Game.exe 00404eb0 */
int MenuToggleOptBDFA44(void) { MenuOptBDFA44 ^= 1; MenuRefresh(); return 0; }
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("MenuOptBDFA48")
#undef MenuOptBDFA48
#pragma push_macro("MenuOptBDFA48") /*gvi*/
#undef MenuOptBDFA48 /*gvi*/
int32_t MenuOptBDFA48;
#pragma pop_macro("MenuOptBDFA48") /*gvi*/
#pragma pop_macro("MenuOptBDFA48")
#endif
/* MenuToggleOptBDFA48 — Game.exe 00404ec9 */
int MenuToggleOptBDFA48(void) { MenuOptBDFA48 ^= 1; MenuRefresh(); return 0; }
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("MenuOptBDFA4C")
#undef MenuOptBDFA4C
#pragma push_macro("MenuOptBDFA4C") /*gvi*/
#undef MenuOptBDFA4C /*gvi*/
int32_t MenuOptBDFA4C;
#pragma pop_macro("MenuOptBDFA4C") /*gvi*/
#pragma pop_macro("MenuOptBDFA4C")
#endif
/* MenuToggleOptBDFA4C — Game.exe 00404ee2 */
int MenuToggleOptBDFA4C(void) { MenuOptBDFA4C ^= 1; MenuRefresh(); return 0; }
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("MenuOptBDFA50")
#undef MenuOptBDFA50
#pragma push_macro("MenuOptBDFA50") /*gvi*/
#undef MenuOptBDFA50 /*gvi*/
int32_t MenuOptBDFA50;
#pragma pop_macro("MenuOptBDFA50") /*gvi*/
#pragma pop_macro("MenuOptBDFA50")
#endif
/* MenuToggleOptBDFA50 — Game.exe 00404efb */
int MenuToggleOptBDFA50(void) { MenuOptBDFA50 ^= 1; MenuRefresh(); return 0; }
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("MenuOptBDFA54")
#undef MenuOptBDFA54
#pragma push_macro("MenuOptBDFA54") /*gvi*/
#undef MenuOptBDFA54 /*gvi*/
int32_t MenuOptBDFA54;
#pragma pop_macro("MenuOptBDFA54") /*gvi*/
#pragma pop_macro("MenuOptBDFA54")
#endif
/* MenuToggleOptBDFA54 — Game.exe 00404f14 */
int MenuToggleOptBDFA54(void) { MenuOptBDFA54 ^= 1; MenuRefresh(); return 0; }
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("MenuOptB87E9C")
#undef MenuOptB87E9C
#pragma push_macro("MenuOptB87E9C") /*gvi*/
#undef MenuOptB87E9C /*gvi*/
int32_t MenuOptB87E9C;
#pragma pop_macro("MenuOptB87E9C") /*gvi*/
#pragma pop_macro("MenuOptB87E9C")
#endif
/* MenuToggleOptB87E9C — Game.exe 00404f2d */
int MenuToggleOptB87E9C(void) { MenuOptB87E9C ^= 1; MenuRefresh(); return 0; }
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("MenuOptBDFA58")
#undef MenuOptBDFA58
#pragma push_macro("MenuOptBDFA58") /*gvi*/
#undef MenuOptBDFA58 /*gvi*/
int32_t MenuOptBDFA58;
#pragma pop_macro("MenuOptBDFA58") /*gvi*/
#pragma pop_macro("MenuOptBDFA58")
#endif
/* MenuToggleOptBDFA58 — Game.exe 00404f46 */
int MenuToggleOptBDFA58(void) { MenuOptBDFA58 ^= 1; MenuRefresh(); return 0; }
/* MenuReturnOne — Game.exe 00407c42 */
int MenuReturnOne(void) { return 1; }
/* MenuCallAction40CD17 — Game.exe 00404ffe */
int MenuCallAction40CD17(void) { MenuAction40CD17(); return 1; }
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("MenuFlag54A0BC")
#undef MenuFlag54A0BC
#pragma push_macro("MenuFlag54A0BC") /*gvi*/
#undef MenuFlag54A0BC /*gvi*/
int32_t MenuFlag54A0BC;
#pragma pop_macro("MenuFlag54A0BC") /*gvi*/
#pragma pop_macro("MenuFlag54A0BC")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("MenuVar54A0CC")
#undef MenuVar54A0CC
#pragma push_macro("MenuVar54A0CC") /*gvi*/
#undef MenuVar54A0CC /*gvi*/
int32_t MenuVar54A0CC;
#pragma pop_macro("MenuVar54A0CC") /*gvi*/
#pragma pop_macro("MenuVar54A0CC")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("MenuCounter5D577C")
#undef MenuCounter5D577C
#pragma push_macro("MenuCounter5D577C") /*gvi*/
#undef MenuCounter5D577C /*gvi*/
int32_t MenuCounter5D577C;
#pragma pop_macro("MenuCounter5D577C") /*gvi*/
#pragma pop_macro("MenuCounter5D577C")
#endif
/* MenuFlag54A0BCSet — Game.exe 00408337 */
void MenuFlag54A0BCSet(void) { MenuFlag54A0BC = 1; }
/* MenuFlag54A0BCClear — Game.exe 00408343 */
void MenuFlag54A0BCClear(void) { MenuFlag54A0BC = 0; }
/* MenuVar54A0CCClear — Game.exe 0040844c */
void MenuVar54A0CCClear(void) { MenuVar54A0CC = 0; }
/* MenuCounter5D577CInc — Game.exe 00408710 */
void MenuCounter5D577CInc(void) { MenuCounter5D577C++; }
/* SumBytes — Game.exe 0040682d: byte sum (replay name-block checksum, see P64_ReplayStart) */
int32_t SumBytes(const uint8_t *data, int32_t count) { int32_t s = 0; for (int32_t i = 0; i < count; i++) s += data[i]; return s; }
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("MenuSrcC559A4")
#undef MenuSrcC559A4
#pragma push_macro("MenuSrcC559A4") /*gvi*/
#undef MenuSrcC559A4 /*gvi*/
int32_t MenuSrcC559A4;
#pragma pop_macro("MenuSrcC559A4") /*gvi*/
#pragma pop_macro("MenuSrcC559A4")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("MenuSrcC559A8")
#undef MenuSrcC559A8
#pragma push_macro("MenuSrcC559A8") /*gvi*/
#undef MenuSrcC559A8 /*gvi*/
int32_t MenuSrcC559A8;
#pragma pop_macro("MenuSrcC559A8") /*gvi*/
#pragma pop_macro("MenuSrcC559A8")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("MenuDst54A0C0")
#undef MenuDst54A0C0
#pragma push_macro("MenuDst54A0C0") /*gvi*/
#undef MenuDst54A0C0 /*gvi*/
int32_t MenuDst54A0C0;
#pragma pop_macro("MenuDst54A0C0") /*gvi*/
#pragma pop_macro("MenuDst54A0C0")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("MenuDst54A0D0")
#undef MenuDst54A0D0
#pragma push_macro("MenuDst54A0D0") /*gvi*/
#undef MenuDst54A0D0 /*gvi*/
int32_t MenuDst54A0D0;
#pragma pop_macro("MenuDst54A0D0") /*gvi*/
#pragma pop_macro("MenuDst54A0D0")
#endif
/* MenuCopyPos — Game.exe 0040831c */
void MenuCopyPos(void) { MenuDst54A0C0 = MenuSrcC559A4; MenuDst54A0D0 = MenuSrcC559A8; }

#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("MenuVar55384C")
#undef MenuVar55384C
#pragma push_macro("MenuVar55384C") /*gvi*/
#undef MenuVar55384C /*gvi*/
int32_t MenuVar55384C;
#pragma pop_macro("MenuVar55384C") /*gvi*/
#pragma pop_macro("MenuVar55384C")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("MenuVar553850")
#undef MenuVar553850
#pragma push_macro("MenuVar553850") /*gvi*/
#undef MenuVar553850 /*gvi*/
int32_t MenuVar553850;
#pragma pop_macro("MenuVar553850") /*gvi*/
#pragma pop_macro("MenuVar553850")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("MenuVar55C974")
#undef MenuVar55C974
#pragma push_macro("MenuVar55C974") /*gvi*/
#undef MenuVar55C974 /*gvi*/
int32_t MenuVar55C974;
#pragma pop_macro("MenuVar55C974") /*gvi*/
#pragma pop_macro("MenuVar55C974")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("MenuVar5759A4")
#undef MenuVar5759A4
#pragma push_macro("MenuVar5759A4") /*gvi*/
#undef MenuVar5759A4 /*gvi*/
int32_t MenuVar5759A4;
#pragma pop_macro("MenuVar5759A4") /*gvi*/
#pragma pop_macro("MenuVar5759A4")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("MenuVar575EE8")
#undef MenuVar575EE8
#pragma push_macro("MenuVar575EE8") /*gvi*/
#undef MenuVar575EE8 /*gvi*/
int32_t MenuVar575EE8;
#pragma pop_macro("MenuVar575EE8") /*gvi*/
#pragma pop_macro("MenuVar575EE8")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("MenuVar575EF8")
#undef MenuVar575EF8
#pragma push_macro("MenuVar575EF8") /*gvi*/
#undef MenuVar575EF8 /*gvi*/
int32_t MenuVar575EF8;
#pragma pop_macro("MenuVar575EF8") /*gvi*/
#pragma pop_macro("MenuVar575EF8")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("MenuVar575F30")
#undef MenuVar575F30
#pragma push_macro("MenuVar575F30") /*gvi*/
#undef MenuVar575F30 /*gvi*/
int32_t MenuVar575F30;
#pragma pop_macro("MenuVar575F30") /*gvi*/
#pragma pop_macro("MenuVar575F30")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("MenuVar575F3C")
#undef MenuVar575F3C
#pragma push_macro("MenuVar575F3C") /*gvi*/
#undef MenuVar575F3C /*gvi*/
int32_t MenuVar575F3C;
#pragma pop_macro("MenuVar575F3C") /*gvi*/
#pragma pop_macro("MenuVar575F3C")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("MenuVar575F44")
#undef MenuVar575F44
#pragma push_macro("MenuVar575F44") /*gvi*/
#undef MenuVar575F44 /*gvi*/
int32_t MenuVar575F44;
#pragma pop_macro("MenuVar575F44") /*gvi*/
#pragma pop_macro("MenuVar575F44")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("MenuVarB201DC")
#undef MenuVarB201DC
#pragma push_macro("MenuVarB201DC") /*gvi*/
#undef MenuVarB201DC /*gvi*/
int32_t MenuVarB201DC;
#pragma pop_macro("MenuVarB201DC") /*gvi*/
#pragma pop_macro("MenuVarB201DC")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("MenuVarB31F04")
#undef MenuVarB31F04
#pragma push_macro("MenuVarB31F04") /*gvi*/
#undef MenuVarB31F04 /*gvi*/
int32_t MenuVarB31F04;
#pragma pop_macro("MenuVarB31F04") /*gvi*/
#pragma pop_macro("MenuVarB31F04")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("MenuVarB87E4C")
#undef MenuVarB87E4C
#pragma push_macro("MenuVarB87E4C") /*gvi*/
#undef MenuVarB87E4C /*gvi*/
int32_t MenuVarB87E4C;
#pragma pop_macro("MenuVarB87E4C") /*gvi*/
#pragma pop_macro("MenuVarB87E4C")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("MenuVarD118C8")
#undef MenuVarD118C8
#pragma push_macro("MenuVarD118C8") /*gvi*/
#undef MenuVarD118C8 /*gvi*/
int32_t MenuVarD118C8;
#pragma pop_macro("MenuVarD118C8") /*gvi*/
#pragma pop_macro("MenuVarD118C8")
#endif
/* Graphics-menu switches (see P104_GfxMenuInit): toggle, mark the menu dirty (MenuVar575EF8 = 4) and redraw;
   the Inc/Dec pairs step two sliders (0..0x40 and 0..3). */
/* MenuToggle55384CRedraw — Game.exe 00408a69 */
int MenuToggle55384CRedraw(void) { MenuVar55384C ^= 1; MenuVar575EF8 = 4; MenuRedraw(); return 0; }
/* MenuToggle553850Redraw — Game.exe 00408b03 */
int MenuToggle553850Redraw(void) { MenuVar553850 ^= 1; MenuVar575EF8 = 4; MenuRedraw(); return 0; }
/* MenuToggleB31F04Redraw — Game.exe 00408b9d */
int MenuToggleB31F04Redraw(void) { MenuVarB31F04 ^= 1; MenuVar575EF8 = 4; MenuRedraw(); return 0; }
/* MenuToggle575F44Redraw — Game.exe 00408d0c */
int MenuToggle575F44Redraw(void) { MenuVar575F44 ^= 1; MenuVar575EF8 = 4; MenuRedraw(); return 0; }
/* MenuToggle55C974Redraw — Game.exe 00408da6 */
int MenuToggle55C974Redraw(void) { MenuVar55C974 ^= 1; MenuVar575EF8 = 4; MenuRedraw(); return 0; }
/* MenuToggle575F30Redraw — Game.exe 00408e40 */
int MenuToggle575F30Redraw(void) { MenuVar575F30 ^= 1; MenuVar575EF8 = 4; MenuRedraw(); return 0; }
/* MenuToggleB201DCRedraw — Game.exe 00408eda */
int MenuToggleB201DCRedraw(void) { MenuVarB201DC ^= 1; MenuVar575EF8 = 4; MenuRedraw(); return 0; }
/* MenuToggle575EE8Redraw — Game.exe 00408f74 */
int MenuToggle575EE8Redraw(void) { MenuVar575EE8 ^= 1; MenuVar575EF8 = 4; MenuRedraw(); return 0; }
/* MenuToggle575F3CRedraw — Game.exe 0040900e */
int MenuToggle575F3CRedraw(void) { MenuVar575F3C ^= 1; MenuVar575EF8 = 4; MenuRedraw(); return 0; }
/* MenuToggleD118C8Redraw — Game.exe 004090a8 */
int MenuToggleD118C8Redraw(void) { MenuVarD118C8 ^= 1; MenuVar575EF8 = 4; MenuRedraw(); return 0; }
/* MenuRedraw409231 — Game.exe 00409231 */
int MenuRedraw409231(void) { MenuVar575EF8 = 4; MenuRedraw(); return 0; }
/* MenuRedraw4092D8 — Game.exe 004092d8 */
int MenuRedraw4092D8(void) { MenuVar575EF8 = 4; MenuRedraw(); return 0; }
/* MenuRedraw40937F — Game.exe 0040937f */
int MenuRedraw40937F(void) { MenuVar575EF8 = 4; MenuRedraw(); return 0; }
/* MenuRedraw409426 — Game.exe 00409426 */
int MenuRedraw409426(void) { MenuVar575EF8 = 4; MenuRedraw(); return 0; }
/* MenuRedraw4094CD — Game.exe 004094cd */
int MenuRedraw4094CD(void) { MenuVar575EF8 = 4; MenuRedraw(); return 0; }
/* MenuIncVar5759A4 — Game.exe 00409b75 */
void MenuIncVar5759A4(void) { if (MenuVar5759A4 < 0x40) { MenuVar5759A4++; MenuVar575EF8 = 4; MenuRedraw(); } }
/* MenuDecVar5759A4 — Game.exe 00409b9f */
void MenuDecVar5759A4(void) { if (0 < MenuVar5759A4) { MenuVar5759A4--; MenuVar575EF8 = 4; MenuRedraw(); } }
/* MenuIncVarB87E4C — Game.exe 00409c31 */
void MenuIncVarB87E4C(void) { if (MenuVarB87E4C < 3) { MenuVarB87E4C++; MenuVar575EF8 = 4; MenuRedraw(); } }
/* MenuDecVarB87E4C — Game.exe 00409c5b */
void MenuDecVarB87E4C(void) { if (0 < MenuVarB87E4C) { MenuVarB87E4C--; MenuVar575EF8 = 4; MenuRedraw(); } }
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("MenuVar54A844")
#undef MenuVar54A844
#pragma push_macro("MenuVar54A844") /*gvi*/
#undef MenuVar54A844 /*gvi*/
int32_t MenuVar54A844;
#pragma pop_macro("MenuVar54A844") /*gvi*/
#pragma pop_macro("MenuVar54A844")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("MenuVar54A854")
#undef MenuVar54A854
#pragma push_macro("MenuVar54A854") /*gvi*/
#undef MenuVar54A854 /*gvi*/
int32_t MenuVar54A854;
#pragma pop_macro("MenuVar54A854") /*gvi*/
#pragma pop_macro("MenuVar54A854")
#endif
/* MenuSet54A844On — Game.exe 0040a443 */
void MenuSet54A844On(void) { MenuVar54A844 = 1; }
/* MenuSet54A844Off — Game.exe 0040a44f */
void MenuSet54A844Off(void) { MenuVar54A844 = 0; }
/* MenuSet54A854On — Game.exe 0040a495 */
void MenuSet54A854On(void) { MenuVar54A854 = 1; }
/* MenuSet54A854Off — Game.exe 0040a4a1 */
void MenuSet54A854Off(void) { MenuVar54A854 = 0; }
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("MenuMode1271060")
#undef MenuMode1271060
#pragma push_macro("MenuMode1271060") /*gvi*/
#undef MenuMode1271060 /*gvi*/
int32_t MenuMode1271060;
#pragma pop_macro("MenuMode1271060") /*gvi*/
#pragma pop_macro("MenuMode1271060")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("MenuFlag54A90C")
#undef MenuFlag54A90C
#pragma push_macro("MenuFlag54A90C") /*gvi*/
#undef MenuFlag54A90C /*gvi*/
uint8_t MenuFlag54A90C;
#pragma pop_macro("MenuFlag54A90C") /*gvi*/
#pragma pop_macro("MenuFlag54A90C")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("MenuFlag54A91C")
#undef MenuFlag54A91C
#pragma push_macro("MenuFlag54A91C") /*gvi*/
#undef MenuFlag54A91C /*gvi*/
uint8_t MenuFlag54A91C;
#pragma pop_macro("MenuFlag54A91C") /*gvi*/
#pragma pop_macro("MenuFlag54A91C")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("MenuFlag54A8FC")
#undef MenuFlag54A8FC
#pragma push_macro("MenuFlag54A8FC") /*gvi*/
#undef MenuFlag54A8FC /*gvi*/
uint8_t MenuFlag54A8FC;
#pragma pop_macro("MenuFlag54A8FC") /*gvi*/
#pragma pop_macro("MenuFlag54A8FC")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("MenuFlag54A92C")
#undef MenuFlag54A92C
#pragma push_macro("MenuFlag54A92C") /*gvi*/
#undef MenuFlag54A92C /*gvi*/
uint8_t MenuFlag54A92C;
#pragma pop_macro("MenuFlag54A92C") /*gvi*/
#pragma pop_macro("MenuFlag54A92C")
#endif
/* Enter / leave pairs of the menu modes 1..7 in MenuMode1271060: entering sets the mode and its highlight flag
   (a byte, as Game.exe's movb), leaving with v == 0 clears the flag.  Driving Games menu 0054a968 (RE_PROBE menu
   walk): mode 4 Pursuit, 5 Getaway, 2 Cross Town Checkpoint, 1 Trail Blazer, 3 Survival, 6 Dirt Track (then
   Practice 6 / Time Trial 0xb), 7 Carnage. */
/* MenuEnterMode2 — Game.exe 0040a625 */
void MenuEnterMode2(void) { MenuFlag54A90C = 1; MenuMode1271060 = 2; }
/* MenuLeaveMode2 — Game.exe 0040a63b */
void MenuLeaveMode2(int32_t v) { if (v == 0) MenuFlag54A90C = 0; }
/* MenuEnterMode1 — Game.exe 0040a64d */
void MenuEnterMode1(void) { MenuFlag54A91C = 1; MenuMode1271060 = 1; }
/* MenuLeaveMode1 — Game.exe 0040a663 */
void MenuLeaveMode1(int32_t v) { if (v == 0) MenuFlag54A91C = 0; }
/* MenuEnterMode5 — Game.exe 0040a675 */
void MenuEnterMode5(void) { MenuFlag54A8FC = 1; MenuMode1271060 = 5; }
/* MenuLeaveMode5 — Game.exe 0040a68b */
void MenuLeaveMode5(int32_t v) { if (v == 0) MenuFlag54A8FC = 0; }
/* MenuEnterMode3 — Game.exe 0040a69d */
void MenuEnterMode3(void) { MenuFlag54A92C = 1; MenuMode1271060 = 3; }
/* MenuLeaveMode3 — Game.exe 0040a6b3 */
void MenuLeaveMode3(int32_t v) { if (v == 0) MenuFlag54A92C = 0; }
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("MenuFlag54A8EC")
#undef MenuFlag54A8EC
#pragma push_macro("MenuFlag54A8EC") /*gvi*/
#undef MenuFlag54A8EC /*gvi*/
uint8_t MenuFlag54A8EC;
#pragma pop_macro("MenuFlag54A8EC") /*gvi*/
#pragma pop_macro("MenuFlag54A8EC")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("MenuFlag54A94C")
#undef MenuFlag54A94C
#pragma push_macro("MenuFlag54A94C") /*gvi*/
#undef MenuFlag54A94C /*gvi*/
uint8_t MenuFlag54A94C;
#pragma pop_macro("MenuFlag54A94C") /*gvi*/
#pragma pop_macro("MenuFlag54A94C")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("MenuFlag54A93C")
#undef MenuFlag54A93C
#pragma push_macro("MenuFlag54A93C") /*gvi*/
#undef MenuFlag54A93C /*gvi*/
uint8_t MenuFlag54A93C;
#pragma pop_macro("MenuFlag54A93C") /*gvi*/
#pragma pop_macro("MenuFlag54A93C")
#endif
/* MenuEnterMode4 — Game.exe 0040a6c5 */
void MenuEnterMode4(void) { MenuFlag54A8EC = 1; MenuMode1271060 = 4; }
/* MenuLeaveMode4 — Game.exe 0040a6db */
void MenuLeaveMode4(int32_t v) { if (v == 0) MenuFlag54A8EC = 0; }
/* MenuEnterMode7 — Game.exe 0040a6ed */
void MenuEnterMode7(void) { MenuFlag54A94C = 1; MenuMode1271060 = 7; }
/* MenuLeaveMode7 — Game.exe 0040a703 */
void MenuLeaveMode7(int32_t v) { if (v == 0) MenuFlag54A94C = 0; }
/* MenuEnterMode6 — Game.exe 0040a715 */
void MenuEnterMode6(void) { MenuFlag54A93C = 1; MenuMode1271060 = 6; }
/* MenuLeaveMode6 — Game.exe 0040a72b */
void MenuLeaveMode6(int32_t v) { if (v == 0) MenuFlag54A93C = 0; }
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("MenuColorR54AA2C")
#undef MenuColorR54AA2C
#pragma push_macro("MenuColorR54AA2C") /*gvi*/
#undef MenuColorR54AA2C /*gvi*/
uint8_t MenuColorR54AA2C;
#pragma pop_macro("MenuColorR54AA2C") /*gvi*/
#pragma pop_macro("MenuColorR54AA2C")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("MenuColorG54AA2D")
#undef MenuColorG54AA2D
#pragma push_macro("MenuColorG54AA2D") /*gvi*/
#undef MenuColorG54AA2D /*gvi*/
uint8_t MenuColorG54AA2D;
#pragma pop_macro("MenuColorG54AA2D") /*gvi*/
#pragma pop_macro("MenuColorG54AA2D")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("MenuColorB54AA2E")
#undef MenuColorB54AA2E
#pragma push_macro("MenuColorB54AA2E") /*gvi*/
#undef MenuColorB54AA2E /*gvi*/
uint8_t MenuColorB54AA2E;
#pragma pop_macro("MenuColorB54AA2E") /*gvi*/
#pragma pop_macro("MenuColorB54AA2E")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("MenuPosX54AA24")
#undef MenuPosX54AA24
#pragma push_macro("MenuPosX54AA24") /*gvi*/
#undef MenuPosX54AA24 /*gvi*/
int32_t MenuPosX54AA24;
#pragma pop_macro("MenuPosX54AA24") /*gvi*/
#pragma pop_macro("MenuPosX54AA24")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("MenuPosY54AA28")
#undef MenuPosY54AA28
#pragma push_macro("MenuPosY54AA28") /*gvi*/
#undef MenuPosY54AA28 /*gvi*/
int32_t MenuPosY54AA28;
#pragma pop_macro("MenuPosY54AA28") /*gvi*/
#pragma pop_macro("MenuPosY54AA28")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("MenuVal5D77CC")
#undef MenuVal5D77CC
#pragma push_macro("MenuVal5D77CC") /*gvi*/
#undef MenuVal5D77CC /*gvi*/
int32_t MenuVal5D77CC;
#pragma pop_macro("MenuVal5D77CC") /*gvi*/
#pragma pop_macro("MenuVal5D77CC")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("MenuVal5D77C4")
#undef MenuVal5D77C4
#pragma push_macro("MenuVal5D77C4") /*gvi*/
#undef MenuVal5D77C4 /*gvi*/
int32_t MenuVal5D77C4;
#pragma pop_macro("MenuVal5D77C4") /*gvi*/
#pragma pop_macro("MenuVal5D77C4")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("MenuVal5D77C8")
#undef MenuVal5D77C8
#pragma push_macro("MenuVal5D77C8") /*gvi*/
#undef MenuVal5D77C8 /*gvi*/
int32_t MenuVal5D77C8;
#pragma pop_macro("MenuVal5D77C8") /*gvi*/
#pragma pop_macro("MenuVal5D77C8")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("MenuByte5D77C1")
#undef MenuByte5D77C1
#pragma push_macro("MenuByte5D77C1") /*gvi*/
#undef MenuByte5D77C1 /*gvi*/
uint8_t MenuByte5D77C1;
#pragma pop_macro("MenuByte5D77C1") /*gvi*/
#pragma pop_macro("MenuByte5D77C1")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("MenuByte5D77C0")
#undef MenuByte5D77C0
#pragma push_macro("MenuByte5D77C0") /*gvi*/
#undef MenuByte5D77C0 /*gvi*/
uint8_t MenuByte5D77C0;
#pragma pop_macro("MenuByte5D77C0") /*gvi*/
#pragma pop_macro("MenuByte5D77C0")
#endif
/* Text colour / position setters and small byte setters of menu items. */
/* MenuSetColor — Game.exe 0040ab3a */
void MenuSetColor(uint8_t r, uint8_t g, uint8_t b) { MenuColorR54AA2C = r; MenuColorG54AA2D = g; MenuColorB54AA2E = b; }
/* MenuSetPos — Game.exe 0040ab59 */
void MenuSetPos(int32_t x, int32_t y) { MenuPosX54AA24 = x; MenuPosY54AA28 = y; }
/* MenuSetVals5D77C0 — Game.exe 0040ab6f */
void MenuSetVals5D77C0(int32_t a, int32_t b, uint8_t c, uint8_t d) { MenuVal5D77CC = a; MenuVal5D77C4 = a; MenuVal5D77C8 = b; MenuByte5D77C1 = c; MenuByte5D77C0 = d; }
/* MenuSetByte5D77C1 — Game.exe 0040ab9f */
void MenuSetByte5D77C1(uint8_t v) { MenuByte5D77C1 = v; }
/* MenuSet54BE5CTo3 — Game.exe 0040f34c */
void MenuSet54BE5CTo3(void) { MenuByte54BE5C = 3; }
/* MenuSet54BE5CTo2 — Game.exe 0040f358 */
void MenuSet54BE5CTo2(void) { MenuByte54BE5C = 2; }
/* MenuSet54BE7CTo3 — Game.exe 0040f395 */
void MenuSet54BE7CTo3(void) { MenuByte54BE7C = 3; }
/* MenuSet54BE7CTo2 — Game.exe 0040f3a1 */
void MenuSet54BE7CTo2(void) { MenuByte54BE7C = 2; }
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("MenuTable54B010")
#undef MenuTable54B010
#pragma push_macro("MenuTable54B010") /*gvi*/
#undef MenuTable54B010 /*gvi*/
MenuTable256_t MenuTable54B010;
#pragma pop_macro("MenuTable54B010") /*gvi*/
#pragma pop_macro("MenuTable54B010")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("MenuByte54ACD4")
#undef MenuByte54ACD4
#pragma push_macro("MenuByte54ACD4") /*gvi*/
#undef MenuByte54ACD4 /*gvi*/
uint8_t MenuByte54ACD4;
#pragma pop_macro("MenuByte54ACD4") /*gvi*/
#pragma pop_macro("MenuByte54ACD4")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("MenuByte54ACE4")
#undef MenuByte54ACE4
#pragma push_macro("MenuByte54ACE4") /*gvi*/
#undef MenuByte54ACE4 /*gvi*/
uint8_t MenuByte54ACE4;
#pragma pop_macro("MenuByte54ACE4") /*gvi*/
#pragma pop_macro("MenuByte54ACE4")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("MenuByte54ACF4")
#undef MenuByte54ACF4
#pragma push_macro("MenuByte54ACF4") /*gvi*/
#undef MenuByte54ACF4 /*gvi*/
uint8_t MenuByte54ACF4;
#pragma pop_macro("MenuByte54ACF4") /*gvi*/
#pragma pop_macro("MenuByte54ACF4")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("MenuByte54AD04")
#undef MenuByte54AD04
#pragma push_macro("MenuByte54AD04") /*gvi*/
#undef MenuByte54AD04 /*gvi*/
uint8_t MenuByte54AD04;
#pragma pop_macro("MenuByte54AD04") /*gvi*/
#pragma pop_macro("MenuByte54AD04")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("MenuByte54AD14")
#undef MenuByte54AD14
#pragma push_macro("MenuByte54AD14") /*gvi*/
#undef MenuByte54AD14 /*gvi*/
uint8_t MenuByte54AD14;
#pragma pop_macro("MenuByte54AD14") /*gvi*/
#pragma pop_macro("MenuByte54AD14")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("MenuByte54AD24")
#undef MenuByte54AD24
#pragma push_macro("MenuByte54AD24") /*gvi*/
#undef MenuByte54AD24 /*gvi*/
uint8_t MenuByte54AD24;
#pragma pop_macro("MenuByte54AD24") /*gvi*/
#pragma pop_macro("MenuByte54AD24")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("MenuByte54AD34")
#undef MenuByte54AD34
#pragma push_macro("MenuByte54AD34") /*gvi*/
#undef MenuByte54AD34 /*gvi*/
uint8_t MenuByte54AD34;
#pragma pop_macro("MenuByte54AD34") /*gvi*/
#pragma pop_macro("MenuByte54AD34")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("MenuByte54AD44")
#undef MenuByte54AD44
#pragma push_macro("MenuByte54AD44") /*gvi*/
#undef MenuByte54AD44 /*gvi*/
uint8_t MenuByte54AD44;
#pragma pop_macro("MenuByte54AD44") /*gvi*/
#pragma pop_macro("MenuByte54AD44")
#endif
/* MenuSet54ACD4To3 — Game.exe 0040e8ec */
void MenuSet54ACD4To3(void) { MenuByte54ACD4 = 3; MenuByte54ACE4 = 3; }
/* MenuSet54ACF4To3 — Game.exe 0040e944 */
void MenuSet54ACF4To3(void) { MenuByte54ACF4 = 3; MenuByte54AD04 = 3; }
/* MenuSet54AD14To3 — Game.exe 0040e989 */
void MenuSet54AD14To3(void) { MenuByte54AD14 = 3; MenuByte54AD24 = 3; }
/* MenuSet54AD34To3 — Game.exe 0040ea2b */
void MenuSet54AD34To3(void) { MenuByte54AD34 = 3; MenuByte54AD44 = 3; }
/* MenuTableGet54B010 — Game.exe 0040f0e7 */
uint32_t MenuTableGet54B010(uint32_t i) { return MenuTable54B010[i & 0xff]; }
