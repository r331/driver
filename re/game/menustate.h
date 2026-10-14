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

/* Меню 2: переключатели + перерисовка (00409622) */
#define MenuVar55384C GAME_VAR(int32_t, MenuVar55384C, 0x0055384c)
#define MenuVar553850 GAME_VAR(int32_t, MenuVar553850, 0x00553850)
#define MenuVar55C974 GAME_VAR(int32_t, MenuVar55C974, 0x0055c974)
#define MenuVar5759A4 GAME_VAR(int32_t, MenuVar5759A4, 0x005759a4)
#define MenuVar575EE8 GAME_VAR(int32_t, MenuVar575EE8, 0x00575ee8)
#define MenuVar575EF8 GAME_VAR(int32_t, MenuVar575EF8, 0x00575ef8)
#define MenuVar575F30 GAME_VAR(int32_t, MenuVar575F30, 0x00575f30)
#define MenuVar575F3C GAME_VAR(int32_t, MenuVar575F3C, 0x00575f3c)
#define MenuVar575F44 GAME_VAR(int32_t, MenuVar575F44, 0x00575f44)
#define MenuVarB201DC GAME_VAR(int32_t, MenuVarB201DC, 0x00b201dc)
#define MenuVarB31F04 GAME_VAR(int32_t, MenuVarB31F04, 0x00b31f04)
#define MenuVarB87E4C GAME_VAR(int32_t, MenuVarB87E4C, 0x00b87e4c)
#define MenuVarD118C8 GAME_VAR(int32_t, MenuVarD118C8, 0x00d118c8)
#define MenuVar54A844 GAME_VAR(int32_t, MenuVar54A844, 0x0054a844)
#define MenuVar54A854 GAME_VAR(int32_t, MenuVar54A854, 0x0054a854)
#ifndef RE_HOOK_BUILD
extern int32_t MenuVar54A844, MenuVar54A854;
extern int32_t MenuVar55384C, MenuVar553850, MenuVar55C974, MenuVar5759A4, MenuVar575EE8, MenuVar575EF8, MenuVar575F30, MenuVar575F3C, MenuVar575F44, MenuVarB201DC, MenuVarB31F04, MenuVarB87E4C, MenuVarD118C8;
#endif
int MenuToggle55384CRedraw(void); /* 00408a69 */
int MenuToggle553850Redraw(void); /* 00408b03 */
int MenuToggleB31F04Redraw(void); /* 00408b9d */
int MenuToggle575F44Redraw(void); /* 00408d0c */
int MenuToggle55C974Redraw(void); /* 00408da6 */
int MenuToggle575F30Redraw(void); /* 00408e40 */
int MenuToggleB201DCRedraw(void); /* 00408eda */
int MenuToggle575EE8Redraw(void); /* 00408f74 */
int MenuToggle575F3CRedraw(void); /* 0040900e */
int MenuToggleD118C8Redraw(void); /* 004090a8 */
int MenuRedraw409231(void); /* 00409231 */
int MenuRedraw4092D8(void); /* 004092d8 */
int MenuRedraw40937F(void); /* 0040937f */
int MenuRedraw409426(void); /* 00409426 */
int MenuRedraw4094CD(void); /* 004094cd */
void MenuIncVar5759A4(void); /* 00409b75 */
void MenuDecVar5759A4(void); /* 00409b9f */
void MenuIncVarB87E4C(void); /* 00409c31 */
void MenuDecVarB87E4C(void); /* 00409c5b */
void MenuSet54A844On(void); /* 0040a443 */
void MenuSet54A844Off(void); /* 0040a44f */
void MenuSet54A854On(void); /* 0040a495 */
void MenuSet54A854Off(void); /* 0040a4a1 */
#define MenuMode1271060 GAME_VAR(int32_t, MenuMode1271060, 0x01271060)
#define MenuFlag54A90C GAME_VAR(uint8_t, MenuFlag54A90C, 0x0054a90c)
#define MenuFlag54A91C GAME_VAR(uint8_t, MenuFlag54A91C, 0x0054a91c)
#define MenuFlag54A8FC GAME_VAR(uint8_t, MenuFlag54A8FC, 0x0054a8fc)
#define MenuFlag54A92C GAME_VAR(uint8_t, MenuFlag54A92C, 0x0054a92c)
#ifndef RE_HOOK_BUILD
extern int32_t MenuMode1271060;
extern uint8_t MenuFlag54A90C, MenuFlag54A91C, MenuFlag54A8FC, MenuFlag54A92C;
#endif
void MenuEnterMode2(void); /* 0040a625 */
void MenuLeaveMode2(int32_t v); /* 0040a63b */
void MenuEnterMode1(void); /* 0040a64d */
void MenuLeaveMode1(int32_t v); /* 0040a663 */
void MenuEnterMode5(void); /* 0040a675 */
void MenuLeaveMode5(int32_t v); /* 0040a68b */
void MenuEnterMode3(void); /* 0040a69d */
void MenuLeaveMode3(int32_t v); /* 0040a6b3 */
#define MenuFlag54A8EC GAME_VAR(uint8_t, MenuFlag54A8EC, 0x0054a8ec)
#define MenuFlag54A94C GAME_VAR(uint8_t, MenuFlag54A94C, 0x0054a94c)
#define MenuFlag54A93C GAME_VAR(uint8_t, MenuFlag54A93C, 0x0054a93c)
#ifndef RE_HOOK_BUILD
extern uint8_t MenuFlag54A8EC, MenuFlag54A94C, MenuFlag54A93C;
#endif
void MenuEnterMode4(void); /* 0040a6c5 */
void MenuLeaveMode4(int32_t v); /* 0040a6db */
void MenuEnterMode7(void); /* 0040a6ed */
void MenuLeaveMode7(int32_t v); /* 0040a703 */
void MenuEnterMode6(void); /* 0040a715 */
void MenuLeaveMode6(int32_t v); /* 0040a72b */
#define MenuColorR54AA2C GAME_VAR(uint8_t, MenuColorR54AA2C, 0x0054aa2c)
#define MenuColorG54AA2D GAME_VAR(uint8_t, MenuColorG54AA2D, 0x0054aa2d)
#define MenuColorB54AA2E GAME_VAR(uint8_t, MenuColorB54AA2E, 0x0054aa2e)
#define MenuPosX54AA24 GAME_VAR(int32_t, MenuPosX54AA24, 0x0054aa24)
#define MenuPosY54AA28 GAME_VAR(int32_t, MenuPosY54AA28, 0x0054aa28)
#define MenuVal5D77CC GAME_VAR(int32_t, MenuVal5D77CC, 0x005d77cc)
#define MenuVal5D77C4 GAME_VAR(int32_t, MenuVal5D77C4, 0x005d77c4)
#define MenuVal5D77C8 GAME_VAR(int32_t, MenuVal5D77C8, 0x005d77c8)
#define MenuByte5D77C1 GAME_VAR(uint8_t, MenuByte5D77C1, 0x005d77c1)
#define MenuByte5D77C0 GAME_VAR(uint8_t, MenuByte5D77C0, 0x005d77c0)
#define MenuByte54BE5C GAME_VAR(uint8_t, MenuByte54BE5C, 0x0054be5c)
#define MenuByte54BE7C GAME_VAR(uint8_t, MenuByte54BE7C, 0x0054be7c)
typedef uint32_t MenuTable256_t[256];
#define MenuTable54B010 GAME_VAR(MenuTable256_t, MenuTable54B010, 0x0054b010)
#define MenuByte54ACD4 GAME_VAR(uint8_t, MenuByte54ACD4, 0x0054acd4)
#define MenuByte54ACE4 GAME_VAR(uint8_t, MenuByte54ACE4, 0x0054ace4)
#define MenuByte54ACF4 GAME_VAR(uint8_t, MenuByte54ACF4, 0x0054acf4)
#define MenuByte54AD04 GAME_VAR(uint8_t, MenuByte54AD04, 0x0054ad04)
#define MenuByte54AD14 GAME_VAR(uint8_t, MenuByte54AD14, 0x0054ad14)
#define MenuByte54AD24 GAME_VAR(uint8_t, MenuByte54AD24, 0x0054ad24)
#define MenuByte54AD34 GAME_VAR(uint8_t, MenuByte54AD34, 0x0054ad34)
#define MenuByte54AD44 GAME_VAR(uint8_t, MenuByte54AD44, 0x0054ad44)
#ifndef RE_HOOK_BUILD
extern uint8_t MenuByte54BE5C, MenuByte54BE7C;
extern MenuTable256_t MenuTable54B010;
extern uint8_t MenuByte54ACD4, MenuByte54ACE4, MenuByte54ACF4, MenuByte54AD04, MenuByte54AD14, MenuByte54AD24, MenuByte54AD34, MenuByte54AD44;
extern uint8_t MenuColorR54AA2C, MenuColorG54AA2D, MenuColorB54AA2E, MenuByte5D77C1, MenuByte5D77C0;
extern int32_t MenuPosX54AA24, MenuPosY54AA28, MenuVal5D77CC, MenuVal5D77C4, MenuVal5D77C8;
#endif
void MenuSetColor(uint8_t r, uint8_t g, uint8_t b); /* 0040ab3a */
void MenuSetPos(int32_t x, int32_t y); /* 0040ab59 */
void MenuSetVals5D77C0(int32_t a, int32_t b, uint8_t c, uint8_t d); /* 0040ab6f */
void MenuSetByte5D77C1(uint8_t v); /* 0040ab9f */
void MenuSet54BE5CTo3(void); /* 0040f34c */
void MenuSet54BE5CTo2(void); /* 0040f358 */
void MenuSet54BE7CTo3(void); /* 0040f395 */
void MenuSet54BE7CTo2(void); /* 0040f3a1 */
void MenuSet54ACD4To3(void); /* 0040e8ec */
void MenuSet54ACF4To3(void); /* 0040e944 */
void MenuSet54AD14To3(void); /* 0040e989 */
void MenuSet54AD34To3(void); /* 0040ea2b */
uint32_t MenuTableGet54B010(uint32_t i); /* 0040f0e7 */
