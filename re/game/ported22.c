#include "ported22.h"
#include "unported.h"
GAME_VAR_DEF(int32_t, P22_OptBDFA44, 0x00bdfa44)
GAME_VAR_DEF(int32_t, P22_OptBDFA48, 0x00bdfa48)
GAME_VAR_DEF(int32_t, P22_OptBDFA4C, 0x00bdfa4c)
GAME_VAR_DEF(int32_t, P22_OptBDFA50, 0x00bdfa50)
GAME_VAR_DEF(int32_t, P22_OptBDFA54, 0x00bdfa54)
GAME_VAR_DEF(int32_t, P22_OptB87E9C, 0x00b87e9c)
GAME_VAR_DEF(int32_t, P22_OptBDFA58, 0x00bdfa58)
GAME_VAR_DEF(int32_t, P22_Flag5F7E4C, 0x005f7e4c)
GAME_VAR_DEF(int32_t, P22_Mode575EF0, 0x00575ef0)
GAME_VAR_DEF(int32_t, P22_Flag54A0BC, 0x0054a0bc)
GAME_VAR_DEF(int32_t, P22_Flag54A0CC, 0x0054a0cc)
GAME_VAR_DEF(int32_t, P22_Cnt5D577C, 0x005d577c)
int32_t P22_ToggleBDFA44(void) { P22_OptBDFA44 ^= 1; MenuRefresh(); return 0; }
int32_t P22_ToggleBDFA48(void) { P22_OptBDFA48 ^= 1; MenuRefresh(); return 0; }
int32_t P22_ToggleBDFA4C(void) { P22_OptBDFA4C ^= 1; MenuRefresh(); return 0; }
int32_t P22_ToggleBDFA50(void) { P22_OptBDFA50 ^= 1; MenuRefresh(); return 0; }
int32_t P22_ToggleBDFA54(void) { P22_OptBDFA54 ^= 1; MenuRefresh(); return 0; }
int32_t P22_ToggleB87E9C(void) { P22_OptB87E9C ^= 1; MenuRefresh(); return 0; }
int32_t P22_ToggleBDFA58(void) { P22_OptBDFA58 ^= 1; MenuRefresh(); return 0; }
int32_t P22_SetMode4(void) { P22_Mode575EF0 = 4; return 0; }
int32_t P22_RunMenuAction40CD17(void) { MenuAction40CD17(); return 1; }
void P22_SetFlag5F7E4C(void) { P22_Flag5F7E4C = 1; }
void P22_SetFlag54A0BC(void) { P22_Flag54A0BC = 1; }
void P22_ClearFlag54A0BC(void) { P22_Flag54A0BC = 0; }
void P22_ClearFlag54A0CC(void) { P22_Flag54A0CC = 0; }
void P22_Inc5D577C(void) { P22_Cnt5D577C++; }
