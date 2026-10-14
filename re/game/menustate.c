#include "menustate.h"
#include "unported.h"
GAME_VAR_DEF(int32_t, MenuFlag5F7E4C, 0x005f7e4c)
GAME_VAR_DEF(int32_t, MenuState575EF0, 0x00575ef0)
void MenuFlagSet(void) { MenuFlag5F7E4C = 1; }
void MenuFlagUpdate(int mode) { if (mode == 0 || mode == 2) MenuFlag5F7E4C = 0; }
int MenuStateSetFour(void) { MenuState575EF0 = 4; return 0; }
GAME_VAR_DEF(int32_t, MenuOptBDFA44, 0x00bdfa44)
int MenuToggleOptBDFA44(void) { MenuOptBDFA44 ^= 1; MenuRefresh(); return 0; }
GAME_VAR_DEF(int32_t, MenuOptBDFA48, 0x00bdfa48)
int MenuToggleOptBDFA48(void) { MenuOptBDFA48 ^= 1; MenuRefresh(); return 0; }
GAME_VAR_DEF(int32_t, MenuOptBDFA4C, 0x00bdfa4c)
int MenuToggleOptBDFA4C(void) { MenuOptBDFA4C ^= 1; MenuRefresh(); return 0; }
GAME_VAR_DEF(int32_t, MenuOptBDFA50, 0x00bdfa50)
int MenuToggleOptBDFA50(void) { MenuOptBDFA50 ^= 1; MenuRefresh(); return 0; }
GAME_VAR_DEF(int32_t, MenuOptBDFA54, 0x00bdfa54)
int MenuToggleOptBDFA54(void) { MenuOptBDFA54 ^= 1; MenuRefresh(); return 0; }
GAME_VAR_DEF(int32_t, MenuOptB87E9C, 0x00b87e9c)
int MenuToggleOptB87E9C(void) { MenuOptB87E9C ^= 1; MenuRefresh(); return 0; }
GAME_VAR_DEF(int32_t, MenuOptBDFA58, 0x00bdfa58)
int MenuToggleOptBDFA58(void) { MenuOptBDFA58 ^= 1; MenuRefresh(); return 0; }
int MenuReturnOne(void) { return 1; }
int MenuCallAction40CD17(void) { MenuAction40CD17(); return 1; }
GAME_VAR_DEF(int32_t, MenuFlag54A0BC, 0x0054a0bc)
GAME_VAR_DEF(int32_t, MenuVar54A0CC, 0x0054a0cc)
GAME_VAR_DEF(int32_t, MenuCounter5D577C, 0x005d577c)
void MenuFlag54A0BCSet(void) { MenuFlag54A0BC = 1; }
void MenuFlag54A0BCClear(void) { MenuFlag54A0BC = 0; }
void MenuVar54A0CCClear(void) { MenuVar54A0CC = 0; }
void MenuCounter5D577CInc(void) { MenuCounter5D577C++; }
int32_t SumBytes(const uint8_t *data, int32_t count) { int32_t s = 0; for (int32_t i = 0; i < count; i++) s += data[i]; return s; }
GAME_VAR_DEF(int32_t, MenuSrcC559A4, 0x00c559a4)
GAME_VAR_DEF(int32_t, MenuSrcC559A8, 0x00c559a8)
GAME_VAR_DEF(int32_t, MenuDst54A0C0, 0x0054a0c0)
GAME_VAR_DEF(int32_t, MenuDst54A0D0, 0x0054a0d0)
void MenuCopyPos(void) { MenuDst54A0C0 = MenuSrcC559A4; MenuDst54A0D0 = MenuSrcC559A8; }

GAME_VAR_DEF(int32_t, MenuVar55384C, 0x0055384c)
GAME_VAR_DEF(int32_t, MenuVar553850, 0x00553850)
GAME_VAR_DEF(int32_t, MenuVar55C974, 0x0055c974)
GAME_VAR_DEF(int32_t, MenuVar5759A4, 0x005759a4)
GAME_VAR_DEF(int32_t, MenuVar575EE8, 0x00575ee8)
GAME_VAR_DEF(int32_t, MenuVar575EF8, 0x00575ef8)
GAME_VAR_DEF(int32_t, MenuVar575F30, 0x00575f30)
GAME_VAR_DEF(int32_t, MenuVar575F3C, 0x00575f3c)
GAME_VAR_DEF(int32_t, MenuVar575F44, 0x00575f44)
GAME_VAR_DEF(int32_t, MenuVarB201DC, 0x00b201dc)
GAME_VAR_DEF(int32_t, MenuVarB31F04, 0x00b31f04)
GAME_VAR_DEF(int32_t, MenuVarB87E4C, 0x00b87e4c)
GAME_VAR_DEF(int32_t, MenuVarD118C8, 0x00d118c8)
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
GAME_VAR_DEF(int32_t, MenuVar54A844, 0x0054a844)
GAME_VAR_DEF(int32_t, MenuVar54A854, 0x0054a854)
void MenuSet54A844On(void) { MenuVar54A844 = 1; }
void MenuSet54A844Off(void) { MenuVar54A844 = 0; }
void MenuSet54A854On(void) { MenuVar54A854 = 1; }
void MenuSet54A854Off(void) { MenuVar54A854 = 0; }
GAME_VAR_DEF(int32_t, MenuMode1271060, 0x01271060)
GAME_VAR_DEF(uint8_t, MenuFlag54A90C, 0x0054a90c)
GAME_VAR_DEF(uint8_t, MenuFlag54A91C, 0x0054a91c)
GAME_VAR_DEF(uint8_t, MenuFlag54A8FC, 0x0054a8fc)
GAME_VAR_DEF(uint8_t, MenuFlag54A92C, 0x0054a92c)
void MenuEnterMode2(void) { MenuFlag54A90C = 1; MenuMode1271060 = 2; }
void MenuLeaveMode2(int32_t v) { if (v == 0) MenuFlag54A90C = 0; }
void MenuEnterMode1(void) { MenuFlag54A91C = 1; MenuMode1271060 = 1; }
void MenuLeaveMode1(int32_t v) { if (v == 0) MenuFlag54A91C = 0; }
void MenuEnterMode5(void) { MenuFlag54A8FC = 1; MenuMode1271060 = 5; }
void MenuLeaveMode5(int32_t v) { if (v == 0) MenuFlag54A8FC = 0; }
void MenuEnterMode3(void) { MenuFlag54A92C = 1; MenuMode1271060 = 3; }
void MenuLeaveMode3(int32_t v) { if (v == 0) MenuFlag54A92C = 0; }
GAME_VAR_DEF(uint8_t, MenuFlag54A8EC, 0x0054a8ec)
GAME_VAR_DEF(uint8_t, MenuFlag54A94C, 0x0054a94c)
GAME_VAR_DEF(uint8_t, MenuFlag54A93C, 0x0054a93c)
void MenuEnterMode4(void) { MenuFlag54A8EC = 1; MenuMode1271060 = 4; }
void MenuLeaveMode4(int32_t v) { if (v == 0) MenuFlag54A8EC = 0; }
void MenuEnterMode7(void) { MenuFlag54A94C = 1; MenuMode1271060 = 7; }
void MenuLeaveMode7(int32_t v) { if (v == 0) MenuFlag54A94C = 0; }
void MenuEnterMode6(void) { MenuFlag54A93C = 1; MenuMode1271060 = 6; }
void MenuLeaveMode6(int32_t v) { if (v == 0) MenuFlag54A93C = 0; }
GAME_VAR_DEF(uint8_t, MenuColorR54AA2C, 0x0054aa2c)
GAME_VAR_DEF(uint8_t, MenuColorG54AA2D, 0x0054aa2d)
GAME_VAR_DEF(uint8_t, MenuColorB54AA2E, 0x0054aa2e)
GAME_VAR_DEF(int32_t, MenuPosX54AA24, 0x0054aa24)
GAME_VAR_DEF(int32_t, MenuPosY54AA28, 0x0054aa28)
GAME_VAR_DEF(int32_t, MenuVal5D77CC, 0x005d77cc)
GAME_VAR_DEF(int32_t, MenuVal5D77C4, 0x005d77c4)
GAME_VAR_DEF(int32_t, MenuVal5D77C8, 0x005d77c8)
GAME_VAR_DEF(uint8_t, MenuByte5D77C1, 0x005d77c1)
GAME_VAR_DEF(uint8_t, MenuByte5D77C0, 0x005d77c0)
void MenuSetColor(uint8_t r, uint8_t g, uint8_t b) { MenuColorR54AA2C = r; MenuColorG54AA2D = g; MenuColorB54AA2E = b; }
void MenuSetPos(int32_t x, int32_t y) { MenuPosX54AA24 = x; MenuPosY54AA28 = y; }
void MenuSetVals5D77C0(int32_t a, int32_t b, uint8_t c, uint8_t d) { MenuVal5D77CC = a; MenuVal5D77C4 = a; MenuVal5D77C8 = b; MenuByte5D77C1 = c; MenuByte5D77C0 = d; }
void MenuSetByte5D77C1(uint8_t v) { MenuByte5D77C1 = v; }
