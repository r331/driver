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
void MenuFlagSet(void) { MenuFlag5F7E4C = 1; }
void MenuFlagUpdate(int mode) { if (mode == 0 || mode == 2) MenuFlag5F7E4C = 0; }
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
int MenuToggleOptBDFA58(void) { MenuOptBDFA58 ^= 1; MenuRefresh(); return 0; }
int MenuReturnOne(void) { return 1; }
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
void MenuFlag54A0BCSet(void) { MenuFlag54A0BC = 1; }
void MenuFlag54A0BCClear(void) { MenuFlag54A0BC = 0; }
void MenuVar54A0CCClear(void) { MenuVar54A0CC = 0; }
void MenuCounter5D577CInc(void) { MenuCounter5D577C++; }
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
int MenuToggle55384CRedraw(void) { MenuVar55384C ^= 1; MenuVar575EF8 = 4; MenuRedraw(); return 0; }
int MenuToggle553850Redraw(void) { MenuVar553850 ^= 1; MenuVar575EF8 = 4; MenuRedraw(); return 0; }
int MenuToggleB31F04Redraw(void) { MenuVarB31F04 ^= 1; MenuVar575EF8 = 4; MenuRedraw(); return 0; }
int MenuToggle575F44Redraw(void) { MenuVar575F44 ^= 1; MenuVar575EF8 = 4; MenuRedraw(); return 0; }
int MenuToggle55C974Redraw(void) { MenuVar55C974 ^= 1; MenuVar575EF8 = 4; MenuRedraw(); return 0; }
int MenuToggle575F30Redraw(void) { MenuVar575F30 ^= 1; MenuVar575EF8 = 4; MenuRedraw(); return 0; }
int MenuToggleB201DCRedraw(void) { MenuVarB201DC ^= 1; MenuVar575EF8 = 4; MenuRedraw(); return 0; }
int MenuToggle575EE8Redraw(void) { MenuVar575EE8 ^= 1; MenuVar575EF8 = 4; MenuRedraw(); return 0; }
int MenuToggle575F3CRedraw(void) { MenuVar575F3C ^= 1; MenuVar575EF8 = 4; MenuRedraw(); return 0; }
int MenuToggleD118C8Redraw(void) { MenuVarD118C8 ^= 1; MenuVar575EF8 = 4; MenuRedraw(); return 0; }
int MenuRedraw409231(void) { MenuVar575EF8 = 4; MenuRedraw(); return 0; }
int MenuRedraw4092D8(void) { MenuVar575EF8 = 4; MenuRedraw(); return 0; }
int MenuRedraw40937F(void) { MenuVar575EF8 = 4; MenuRedraw(); return 0; }
int MenuRedraw409426(void) { MenuVar575EF8 = 4; MenuRedraw(); return 0; }
int MenuRedraw4094CD(void) { MenuVar575EF8 = 4; MenuRedraw(); return 0; }
void MenuIncVar5759A4(void) { if (MenuVar5759A4 < 0x40) { MenuVar5759A4++; MenuVar575EF8 = 4; MenuRedraw(); } }
void MenuDecVar5759A4(void) { if (0 < MenuVar5759A4) { MenuVar5759A4--; MenuVar575EF8 = 4; MenuRedraw(); } }
void MenuIncVarB87E4C(void) { if (MenuVarB87E4C < 3) { MenuVarB87E4C++; MenuVar575EF8 = 4; MenuRedraw(); } }
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
void MenuSet54A844On(void) { MenuVar54A844 = 1; }
void MenuSet54A844Off(void) { MenuVar54A844 = 0; }
void MenuSet54A854On(void) { MenuVar54A854 = 1; }
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
void MenuEnterMode2(void) { MenuFlag54A90C = 1; MenuMode1271060 = 2; }
void MenuLeaveMode2(int32_t v) { if (v == 0) MenuFlag54A90C = 0; }
void MenuEnterMode1(void) { MenuFlag54A91C = 1; MenuMode1271060 = 1; }
void MenuLeaveMode1(int32_t v) { if (v == 0) MenuFlag54A91C = 0; }
void MenuEnterMode5(void) { MenuFlag54A8FC = 1; MenuMode1271060 = 5; }
void MenuLeaveMode5(int32_t v) { if (v == 0) MenuFlag54A8FC = 0; }
void MenuEnterMode3(void) { MenuFlag54A92C = 1; MenuMode1271060 = 3; }
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
void MenuEnterMode4(void) { MenuFlag54A8EC = 1; MenuMode1271060 = 4; }
void MenuLeaveMode4(int32_t v) { if (v == 0) MenuFlag54A8EC = 0; }
void MenuEnterMode7(void) { MenuFlag54A94C = 1; MenuMode1271060 = 7; }
void MenuLeaveMode7(int32_t v) { if (v == 0) MenuFlag54A94C = 0; }
void MenuEnterMode6(void) { MenuFlag54A93C = 1; MenuMode1271060 = 6; }
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
void MenuSetColor(uint8_t r, uint8_t g, uint8_t b) { MenuColorR54AA2C = r; MenuColorG54AA2D = g; MenuColorB54AA2E = b; }
void MenuSetPos(int32_t x, int32_t y) { MenuPosX54AA24 = x; MenuPosY54AA28 = y; }
void MenuSetVals5D77C0(int32_t a, int32_t b, uint8_t c, uint8_t d) { MenuVal5D77CC = a; MenuVal5D77C4 = a; MenuVal5D77C8 = b; MenuByte5D77C1 = c; MenuByte5D77C0 = d; }
void MenuSetByte5D77C1(uint8_t v) { MenuByte5D77C1 = v; }
void MenuSet54BE5CTo3(void) { MenuByte54BE5C = 3; }
void MenuSet54BE5CTo2(void) { MenuByte54BE5C = 2; }
void MenuSet54BE7CTo3(void) { MenuByte54BE7C = 3; }
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
void MenuSet54ACD4To3(void) { MenuByte54ACD4 = 3; MenuByte54ACE4 = 3; }
void MenuSet54ACF4To3(void) { MenuByte54ACF4 = 3; MenuByte54AD04 = 3; }
void MenuSet54AD14To3(void) { MenuByte54AD14 = 3; MenuByte54AD24 = 3; }
void MenuSet54AD34To3(void) { MenuByte54AD34 = 3; MenuByte54AD44 = 3; }
uint32_t MenuTableGet54B010(uint32_t i) { return MenuTable54B010[i & 0xff]; }
