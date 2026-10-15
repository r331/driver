#pragma once
#include "gvar.h"
#include <stdint.h>
/* Переключатели меню и мелкие флаги. */
#define P22_OptBDFA44 GAME_VAR(int32_t, P22_OptBDFA44, 0x00bdfa44)
#define P22_OptBDFA48 GAME_VAR(int32_t, P22_OptBDFA48, 0x00bdfa48)
#define P22_OptBDFA4C GAME_VAR(int32_t, P22_OptBDFA4C, 0x00bdfa4c)
#define P22_OptBDFA50 GAME_VAR(int32_t, P22_OptBDFA50, 0x00bdfa50)
#define P22_OptBDFA54 GAME_VAR(int32_t, P22_OptBDFA54, 0x00bdfa54)
#define P22_OptB87E9C GAME_VAR(int32_t, P22_OptB87E9C, 0x00b87e9c)
#define P22_OptBDFA58 GAME_VAR(int32_t, P22_OptBDFA58, 0x00bdfa58)
#define P22_Flag5F7E4C GAME_VAR(int32_t, P22_Flag5F7E4C, 0x005f7e4c)
#define P22_Mode575EF0 GAME_VAR(int32_t, P22_Mode575EF0, 0x00575ef0)
#define P22_Flag54A0BC GAME_VAR(int32_t, P22_Flag54A0BC, 0x0054a0bc)
#define P22_Flag54A0CC GAME_VAR(int32_t, P22_Flag54A0CC, 0x0054a0cc)
#define P22_Cnt5D577C GAME_VAR(int32_t, P22_Cnt5D577C, 0x005d577c)
#ifndef RE_HOOK_BUILD
extern int32_t P22_OptBDFA44, P22_OptBDFA48, P22_OptBDFA4C, P22_OptBDFA50, P22_OptBDFA54, P22_OptB87E9C, P22_OptBDFA58, P22_Flag5F7E4C, P22_Mode575EF0, P22_Flag54A0BC, P22_Flag54A0CC, P22_Cnt5D577C;
#endif
int32_t P22_ToggleBDFA44(void); /* 00404eb0 */
int32_t P22_ToggleBDFA48(void); /* 00404ec9 */
int32_t P22_ToggleBDFA4C(void); /* 00404ee2 */
int32_t P22_ToggleBDFA50(void); /* 00404efb */
int32_t P22_ToggleBDFA54(void); /* 00404f14 */
int32_t P22_ToggleB87E9C(void); /* 00404f2d */
int32_t P22_ToggleBDFA58(void); /* 00404f46 */
int32_t P22_SetMode4(void); /* 00404f5f */
int32_t P22_RunMenuAction40CD17(void); /* 00404ffe */
void P22_SetFlag5F7E4C(void); /* 00404687 */
void P22_SetFlag54A0BC(void); /* 00408337 */
void P22_ClearFlag54A0BC(void); /* 00408343 */
void P22_ClearFlag54A0CC(void); /* 0040844c */
void P22_Inc5D577C(void); /* 00408710 */
