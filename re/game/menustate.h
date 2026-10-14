/* MenuState — мелкие переключатели состояния меню. */
#pragma once
#include "gvar.h"
#define MenuFlag5F7E4C GAME_VAR(int32_t, MenuFlag5F7E4C, 0x005f7e4c)
#define MenuState575EF0 GAME_VAR(int32_t, MenuState575EF0, 0x00575ef0)
#ifndef RE_HOOK_BUILD
extern int32_t MenuFlag5F7E4C, MenuState575EF0;
#endif
void MenuFlagSet(void);              /* 00404687 */
void MenuFlagUpdate(int mode);       /* 00404696: 0 и 2 сбрасывают флаг */
int MenuStateSetFour(void);          /* 00404f5f */
#define MenuOptBDFA44 GAME_VAR(int32_t, MenuOptBDFA44, 0x00bdfa44)
#ifndef RE_HOOK_BUILD
extern int32_t MenuOptBDFA44;
#endif
int MenuToggleOptBDFA44(void); /* 00404eb0 */
#define MenuOptBDFA48 GAME_VAR(int32_t, MenuOptBDFA48, 0x00bdfa48)
#ifndef RE_HOOK_BUILD
extern int32_t MenuOptBDFA48;
#endif
int MenuToggleOptBDFA48(void); /* 00404ec9 */
#define MenuOptBDFA4C GAME_VAR(int32_t, MenuOptBDFA4C, 0x00bdfa4c)
#ifndef RE_HOOK_BUILD
extern int32_t MenuOptBDFA4C;
#endif
int MenuToggleOptBDFA4C(void); /* 00404ee2 */
#define MenuOptBDFA50 GAME_VAR(int32_t, MenuOptBDFA50, 0x00bdfa50)
#ifndef RE_HOOK_BUILD
extern int32_t MenuOptBDFA50;
#endif
int MenuToggleOptBDFA50(void); /* 00404efb */
#define MenuOptBDFA54 GAME_VAR(int32_t, MenuOptBDFA54, 0x00bdfa54)
#ifndef RE_HOOK_BUILD
extern int32_t MenuOptBDFA54;
#endif
int MenuToggleOptBDFA54(void); /* 00404f14 */
#define MenuOptB87E9C GAME_VAR(int32_t, MenuOptB87E9C, 0x00b87e9c)
#ifndef RE_HOOK_BUILD
extern int32_t MenuOptB87E9C;
#endif
int MenuToggleOptB87E9C(void); /* 00404f2d */
#define MenuOptBDFA58 GAME_VAR(int32_t, MenuOptBDFA58, 0x00bdfa58)
#ifndef RE_HOOK_BUILD
extern int32_t MenuOptBDFA58;
#endif
int MenuToggleOptBDFA58(void); /* 00404f46 */
int MenuReturnOne(void); /* 00407c42 */
int MenuCallAction40CD17(void); /* 00404ffe */
#define MenuFlag54A0BC GAME_VAR(int32_t, MenuFlag54A0BC, 0x0054a0bc)
#define MenuVar54A0CC  GAME_VAR(int32_t, MenuVar54A0CC,  0x0054a0cc)
#define MenuCounter5D577C GAME_VAR(int32_t, MenuCounter5D577C, 0x005d577c)
#ifndef RE_HOOK_BUILD
extern int32_t MenuFlag54A0BC, MenuVar54A0CC, MenuCounter5D577C;
#endif
void MenuFlag54A0BCSet(void);   /* 00408337 */
void MenuFlag54A0BCClear(void); /* 00408343 */
void MenuVar54A0CCClear(void);  /* 0040844c */
void MenuCounter5D577CInc(void);/* 00408710 */
int32_t SumBytes(const uint8_t *data, int32_t count); /* 0040682d */
#define MenuSrcC559A4 GAME_VAR(int32_t, MenuSrcC559A4, 0x00c559a4)
#define MenuSrcC559A8 GAME_VAR(int32_t, MenuSrcC559A8, 0x00c559a8)
#define MenuDst54A0C0 GAME_VAR(int32_t, MenuDst54A0C0, 0x0054a0c0)
#define MenuDst54A0D0 GAME_VAR(int32_t, MenuDst54A0D0, 0x0054a0d0)
#ifndef RE_HOOK_BUILD
extern int32_t MenuSrcC559A4, MenuSrcC559A8, MenuDst54A0C0, MenuDst54A0D0;
#endif
void MenuCopyPos(void); /* 0040831c */
