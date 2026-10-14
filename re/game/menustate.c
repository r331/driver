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
