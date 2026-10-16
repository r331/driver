/* MenuState — мелкие переключатели состояния меню. */
#pragma once
#include "ported141.h"
#include "gvar.h"
#define MenuFlag5F7E4C GAME_VAR(int32_t, MenuFlag5F7E4C, 0x005f7e4c)
#define MenuState575EF0 GAME_VAR(int32_t, MenuState575EF0, 0x00575ef0)
#ifndef RE_HOOK_BUILD
#pragma push_macro("MenuFlag5F7E4C") /*gvi*/
#undef MenuFlag5F7E4C /*gvi*/
#pragma push_macro("MenuState575EF0") /*gvi*/
#undef MenuState575EF0 /*gvi*/
extern int32_t MenuFlag5F7E4C, MenuState575EF0;
#pragma pop_macro("MenuState575EF0") /*gvi*/
#pragma pop_macro("MenuFlag5F7E4C") /*gvi*/
#endif
void MenuFlagSet(void);              /* 00404687 */
void MenuFlagUpdate(int mode);       /* 00404696: 0 и 2 сбрасывают флаг */
int MenuStateSetFour(void);          /* 00404f5f */
#define MenuOptBDFA44 GAME_VAR(int32_t, MenuOptBDFA44, 0x00bdfa44)
#ifndef RE_HOOK_BUILD
#pragma push_macro("MenuOptBDFA44") /*gvi*/
#undef MenuOptBDFA44 /*gvi*/
extern int32_t MenuOptBDFA44;
#pragma pop_macro("MenuOptBDFA44") /*gvi*/
#endif
int MenuToggleOptBDFA44(void); /* 00404eb0 */
#define MenuOptBDFA48 GAME_VAR(int32_t, MenuOptBDFA48, 0x00bdfa48)
#ifndef RE_HOOK_BUILD
#pragma push_macro("MenuOptBDFA48") /*gvi*/
#undef MenuOptBDFA48 /*gvi*/
extern int32_t MenuOptBDFA48;
#pragma pop_macro("MenuOptBDFA48") /*gvi*/
#endif
int MenuToggleOptBDFA48(void); /* 00404ec9 */
#define MenuOptBDFA4C GAME_VAR(int32_t, MenuOptBDFA4C, 0x00bdfa4c)
#ifndef RE_HOOK_BUILD
#pragma push_macro("MenuOptBDFA4C") /*gvi*/
#undef MenuOptBDFA4C /*gvi*/
extern int32_t MenuOptBDFA4C;
#pragma pop_macro("MenuOptBDFA4C") /*gvi*/
#endif
int MenuToggleOptBDFA4C(void); /* 00404ee2 */
#define MenuOptBDFA50 GAME_VAR(int32_t, MenuOptBDFA50, 0x00bdfa50)
#ifndef RE_HOOK_BUILD
#pragma push_macro("MenuOptBDFA50") /*gvi*/
#undef MenuOptBDFA50 /*gvi*/
extern int32_t MenuOptBDFA50;
#pragma pop_macro("MenuOptBDFA50") /*gvi*/
#endif
int MenuToggleOptBDFA50(void); /* 00404efb */
#define MenuOptBDFA54 GAME_VAR(int32_t, MenuOptBDFA54, 0x00bdfa54)
#ifndef RE_HOOK_BUILD
#pragma push_macro("MenuOptBDFA54") /*gvi*/
#undef MenuOptBDFA54 /*gvi*/
extern int32_t MenuOptBDFA54;
#pragma pop_macro("MenuOptBDFA54") /*gvi*/
#endif
int MenuToggleOptBDFA54(void); /* 00404f14 */
#define MenuOptB87E9C GAME_VAR(int32_t, MenuOptB87E9C, 0x00b87e9c)
#ifndef RE_HOOK_BUILD
#pragma push_macro("MenuOptB87E9C") /*gvi*/
#undef MenuOptB87E9C /*gvi*/
extern int32_t MenuOptB87E9C;
#pragma pop_macro("MenuOptB87E9C") /*gvi*/
#endif
int MenuToggleOptB87E9C(void); /* 00404f2d */
#define MenuOptBDFA58 GAME_VAR(int32_t, MenuOptBDFA58, 0x00bdfa58)
#ifndef RE_HOOK_BUILD
#pragma push_macro("MenuOptBDFA58") /*gvi*/
#undef MenuOptBDFA58 /*gvi*/
extern int32_t MenuOptBDFA58;
#pragma pop_macro("MenuOptBDFA58") /*gvi*/
#endif
int MenuToggleOptBDFA58(void); /* 00404f46 */
int MenuReturnOne(void); /* 00407c42 */
int MenuCallAction40CD17(void); /* 00404ffe */
#define MenuFlag54A0BC GAME_VAR(int32_t, MenuFlag54A0BC, 0x0054a0bc)
#define MenuVar54A0CC  GAME_VAR(int32_t, MenuVar54A0CC,  0x0054a0cc)
#define MenuCounter5D577C GAME_VAR(int32_t, MenuCounter5D577C, 0x005d577c)
#ifndef RE_HOOK_BUILD
#pragma push_macro("MenuFlag54A0BC") /*gvi*/
#undef MenuFlag54A0BC /*gvi*/
#pragma push_macro("MenuVar54A0CC") /*gvi*/
#undef MenuVar54A0CC /*gvi*/
#pragma push_macro("MenuCounter5D577C") /*gvi*/
#undef MenuCounter5D577C /*gvi*/
extern int32_t MenuFlag54A0BC, MenuVar54A0CC, MenuCounter5D577C;
#pragma pop_macro("MenuCounter5D577C") /*gvi*/
#pragma pop_macro("MenuVar54A0CC") /*gvi*/
#pragma pop_macro("MenuFlag54A0BC") /*gvi*/
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
#pragma push_macro("MenuSrcC559A4") /*gvi*/
#undef MenuSrcC559A4 /*gvi*/
#pragma push_macro("MenuSrcC559A8") /*gvi*/
#undef MenuSrcC559A8 /*gvi*/
#pragma push_macro("MenuDst54A0C0") /*gvi*/
#undef MenuDst54A0C0 /*gvi*/
#pragma push_macro("MenuDst54A0D0") /*gvi*/
#undef MenuDst54A0D0 /*gvi*/
extern int32_t MenuSrcC559A4, MenuSrcC559A8, MenuDst54A0C0, MenuDst54A0D0;
#pragma pop_macro("MenuDst54A0D0") /*gvi*/
#pragma pop_macro("MenuDst54A0C0") /*gvi*/
#pragma pop_macro("MenuSrcC559A8") /*gvi*/
#pragma pop_macro("MenuSrcC559A4") /*gvi*/
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
#pragma push_macro("MenuVar54A844") /*gvi*/
#undef MenuVar54A844 /*gvi*/
#pragma push_macro("MenuVar54A854") /*gvi*/
#undef MenuVar54A854 /*gvi*/
extern int32_t MenuVar54A844, MenuVar54A854;
#pragma pop_macro("MenuVar54A854") /*gvi*/
#pragma pop_macro("MenuVar54A844") /*gvi*/
#pragma push_macro("MenuVar55384C") /*gvi*/
#undef MenuVar55384C /*gvi*/
#pragma push_macro("MenuVar553850") /*gvi*/
#undef MenuVar553850 /*gvi*/
#pragma push_macro("MenuVar55C974") /*gvi*/
#undef MenuVar55C974 /*gvi*/
#pragma push_macro("MenuVar5759A4") /*gvi*/
#undef MenuVar5759A4 /*gvi*/
#pragma push_macro("MenuVar575EE8") /*gvi*/
#undef MenuVar575EE8 /*gvi*/
#pragma push_macro("MenuVar575EF8") /*gvi*/
#undef MenuVar575EF8 /*gvi*/
#pragma push_macro("MenuVar575F30") /*gvi*/
#undef MenuVar575F30 /*gvi*/
#pragma push_macro("MenuVar575F3C") /*gvi*/
#undef MenuVar575F3C /*gvi*/
#pragma push_macro("MenuVar575F44") /*gvi*/
#undef MenuVar575F44 /*gvi*/
#pragma push_macro("MenuVarB201DC") /*gvi*/
#undef MenuVarB201DC /*gvi*/
#pragma push_macro("MenuVarB31F04") /*gvi*/
#undef MenuVarB31F04 /*gvi*/
#pragma push_macro("MenuVarB87E4C") /*gvi*/
#undef MenuVarB87E4C /*gvi*/
#pragma push_macro("MenuVarD118C8") /*gvi*/
#undef MenuVarD118C8 /*gvi*/
extern int32_t MenuVar55384C, MenuVar553850, MenuVar55C974, MenuVar5759A4, MenuVar575EE8, MenuVar575EF8, MenuVar575F30, MenuVar575F3C, MenuVar575F44, MenuVarB201DC, MenuVarB31F04, MenuVarB87E4C, MenuVarD118C8;
#pragma pop_macro("MenuVarD118C8") /*gvi*/
#pragma pop_macro("MenuVarB87E4C") /*gvi*/
#pragma pop_macro("MenuVarB31F04") /*gvi*/
#pragma pop_macro("MenuVarB201DC") /*gvi*/
#pragma pop_macro("MenuVar575F44") /*gvi*/
#pragma pop_macro("MenuVar575F3C") /*gvi*/
#pragma pop_macro("MenuVar575F30") /*gvi*/
#pragma pop_macro("MenuVar575EF8") /*gvi*/
#pragma pop_macro("MenuVar575EE8") /*gvi*/
#pragma pop_macro("MenuVar5759A4") /*gvi*/
#pragma pop_macro("MenuVar55C974") /*gvi*/
#pragma pop_macro("MenuVar553850") /*gvi*/
#pragma pop_macro("MenuVar55384C") /*gvi*/
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
#pragma push_macro("MenuMode1271060") /*gvi*/
#undef MenuMode1271060 /*gvi*/
extern int32_t MenuMode1271060;
#pragma pop_macro("MenuMode1271060") /*gvi*/
#pragma push_macro("MenuFlag54A90C") /*gvi*/
#undef MenuFlag54A90C /*gvi*/
#pragma push_macro("MenuFlag54A91C") /*gvi*/
#undef MenuFlag54A91C /*gvi*/
#pragma push_macro("MenuFlag54A8FC") /*gvi*/
#undef MenuFlag54A8FC /*gvi*/
#pragma push_macro("MenuFlag54A92C") /*gvi*/
#undef MenuFlag54A92C /*gvi*/
extern uint8_t MenuFlag54A90C, MenuFlag54A91C, MenuFlag54A8FC, MenuFlag54A92C;
#pragma pop_macro("MenuFlag54A92C") /*gvi*/
#pragma pop_macro("MenuFlag54A8FC") /*gvi*/
#pragma pop_macro("MenuFlag54A91C") /*gvi*/
#pragma pop_macro("MenuFlag54A90C") /*gvi*/
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
#pragma push_macro("MenuFlag54A8EC") /*gvi*/
#undef MenuFlag54A8EC /*gvi*/
#pragma push_macro("MenuFlag54A94C") /*gvi*/
#undef MenuFlag54A94C /*gvi*/
#pragma push_macro("MenuFlag54A93C") /*gvi*/
#undef MenuFlag54A93C /*gvi*/
extern uint8_t MenuFlag54A8EC, MenuFlag54A94C, MenuFlag54A93C;
#pragma pop_macro("MenuFlag54A93C") /*gvi*/
#pragma pop_macro("MenuFlag54A94C") /*gvi*/
#pragma pop_macro("MenuFlag54A8EC") /*gvi*/
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
#define MenuByte54BE5C P141_HSM8(0x0054be5cu)   /* v1.86: байт таблицы P141_HsMenu */
#define MenuByte54BE7C P141_HSM8(0x0054be7cu)
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
#pragma push_macro("MenuTable54B010") /*gvi*/
#undef MenuTable54B010 /*gvi*/
extern MenuTable256_t MenuTable54B010;
#pragma pop_macro("MenuTable54B010") /*gvi*/
#pragma push_macro("MenuByte54ACD4") /*gvi*/
#undef MenuByte54ACD4 /*gvi*/
#pragma push_macro("MenuByte54ACE4") /*gvi*/
#undef MenuByte54ACE4 /*gvi*/
#pragma push_macro("MenuByte54ACF4") /*gvi*/
#undef MenuByte54ACF4 /*gvi*/
#pragma push_macro("MenuByte54AD04") /*gvi*/
#undef MenuByte54AD04 /*gvi*/
#pragma push_macro("MenuByte54AD14") /*gvi*/
#undef MenuByte54AD14 /*gvi*/
#pragma push_macro("MenuByte54AD24") /*gvi*/
#undef MenuByte54AD24 /*gvi*/
#pragma push_macro("MenuByte54AD34") /*gvi*/
#undef MenuByte54AD34 /*gvi*/
#pragma push_macro("MenuByte54AD44") /*gvi*/
#undef MenuByte54AD44 /*gvi*/
extern uint8_t MenuByte54ACD4, MenuByte54ACE4, MenuByte54ACF4, MenuByte54AD04, MenuByte54AD14, MenuByte54AD24, MenuByte54AD34, MenuByte54AD44;
#pragma pop_macro("MenuByte54AD44") /*gvi*/
#pragma pop_macro("MenuByte54AD34") /*gvi*/
#pragma pop_macro("MenuByte54AD24") /*gvi*/
#pragma pop_macro("MenuByte54AD14") /*gvi*/
#pragma pop_macro("MenuByte54AD04") /*gvi*/
#pragma pop_macro("MenuByte54ACF4") /*gvi*/
#pragma pop_macro("MenuByte54ACE4") /*gvi*/
#pragma pop_macro("MenuByte54ACD4") /*gvi*/
#pragma push_macro("MenuColorR54AA2C") /*gvi*/
#undef MenuColorR54AA2C /*gvi*/
#pragma push_macro("MenuColorG54AA2D") /*gvi*/
#undef MenuColorG54AA2D /*gvi*/
#pragma push_macro("MenuColorB54AA2E") /*gvi*/
#undef MenuColorB54AA2E /*gvi*/
#pragma push_macro("MenuByte5D77C1") /*gvi*/
#undef MenuByte5D77C1 /*gvi*/
#pragma push_macro("MenuByte5D77C0") /*gvi*/
#undef MenuByte5D77C0 /*gvi*/
extern uint8_t MenuColorR54AA2C, MenuColorG54AA2D, MenuColorB54AA2E, MenuByte5D77C1, MenuByte5D77C0;
#pragma pop_macro("MenuByte5D77C0") /*gvi*/
#pragma pop_macro("MenuByte5D77C1") /*gvi*/
#pragma pop_macro("MenuColorB54AA2E") /*gvi*/
#pragma pop_macro("MenuColorG54AA2D") /*gvi*/
#pragma pop_macro("MenuColorR54AA2C") /*gvi*/
#pragma push_macro("MenuPosX54AA24") /*gvi*/
#undef MenuPosX54AA24 /*gvi*/
#pragma push_macro("MenuPosY54AA28") /*gvi*/
#undef MenuPosY54AA28 /*gvi*/
#pragma push_macro("MenuVal5D77CC") /*gvi*/
#undef MenuVal5D77CC /*gvi*/
#pragma push_macro("MenuVal5D77C4") /*gvi*/
#undef MenuVal5D77C4 /*gvi*/
#pragma push_macro("MenuVal5D77C8") /*gvi*/
#undef MenuVal5D77C8 /*gvi*/
extern int32_t MenuPosX54AA24, MenuPosY54AA28, MenuVal5D77CC, MenuVal5D77C4, MenuVal5D77C8;
#pragma pop_macro("MenuVal5D77C8") /*gvi*/
#pragma pop_macro("MenuVal5D77C4") /*gvi*/
#pragma pop_macro("MenuVal5D77CC") /*gvi*/
#pragma pop_macro("MenuPosY54AA28") /*gvi*/
#pragma pop_macro("MenuPosX54AA24") /*gvi*/
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
/* gvar-img v2.03 begin (tools/gen_gvar_img.py) */
#if !defined(RE_HOOK_BUILD) && !defined(RE_GVAR_PLAIN)
#undef MenuFlag5F7E4C
#define MenuFlag5F7E4C (*(int32_t *)re_gvar(0x005f7e4cu, sizeof(int32_t), (void *)&MenuFlag5F7E4C))
#undef MenuState575EF0
#define MenuState575EF0 (*(int32_t *)re_gvar(0x00575ef0u, sizeof(int32_t), (void *)&MenuState575EF0))
#undef MenuOptBDFA44
#define MenuOptBDFA44 (*(int32_t *)re_gvar(0x00bdfa44u, sizeof(int32_t), (void *)&MenuOptBDFA44))
#undef MenuOptBDFA48
#define MenuOptBDFA48 (*(int32_t *)re_gvar(0x00bdfa48u, sizeof(int32_t), (void *)&MenuOptBDFA48))
#undef MenuOptBDFA4C
#define MenuOptBDFA4C (*(int32_t *)re_gvar(0x00bdfa4cu, sizeof(int32_t), (void *)&MenuOptBDFA4C))
#undef MenuOptBDFA50
#define MenuOptBDFA50 (*(int32_t *)re_gvar(0x00bdfa50u, sizeof(int32_t), (void *)&MenuOptBDFA50))
#undef MenuOptBDFA54
#define MenuOptBDFA54 (*(int32_t *)re_gvar(0x00bdfa54u, sizeof(int32_t), (void *)&MenuOptBDFA54))
#undef MenuOptB87E9C
#define MenuOptB87E9C (*(int32_t *)re_gvar(0x00b87e9cu, sizeof(int32_t), (void *)&MenuOptB87E9C))
#undef MenuOptBDFA58
#define MenuOptBDFA58 (*(int32_t *)re_gvar(0x00bdfa58u, sizeof(int32_t), (void *)&MenuOptBDFA58))
#undef MenuFlag54A0BC
#define MenuFlag54A0BC (*(int32_t *)re_gvar(0x0054a0bcu, sizeof(int32_t), (void *)&MenuFlag54A0BC))
#undef MenuVar54A0CC
#define MenuVar54A0CC (*(int32_t *)re_gvar(0x0054a0ccu, sizeof(int32_t), (void *)&MenuVar54A0CC))
#undef MenuCounter5D577C
#define MenuCounter5D577C (*(int32_t *)re_gvar(0x005d577cu, sizeof(int32_t), (void *)&MenuCounter5D577C))
#undef MenuSrcC559A4
#define MenuSrcC559A4 (*(int32_t *)re_gvar(0x00c559a4u, sizeof(int32_t), (void *)&MenuSrcC559A4))
#undef MenuSrcC559A8
#define MenuSrcC559A8 (*(int32_t *)re_gvar(0x00c559a8u, sizeof(int32_t), (void *)&MenuSrcC559A8))
#undef MenuDst54A0C0
#define MenuDst54A0C0 (*(int32_t *)re_gvar(0x0054a0c0u, sizeof(int32_t), (void *)&MenuDst54A0C0))
#undef MenuDst54A0D0
#define MenuDst54A0D0 (*(int32_t *)re_gvar(0x0054a0d0u, sizeof(int32_t), (void *)&MenuDst54A0D0))
#undef MenuVar55384C
#define MenuVar55384C (*(int32_t *)re_gvar(0x0055384cu, sizeof(int32_t), (void *)&MenuVar55384C))
#undef MenuVar553850
#define MenuVar553850 (*(int32_t *)re_gvar(0x00553850u, sizeof(int32_t), (void *)&MenuVar553850))
#undef MenuVar55C974
#define MenuVar55C974 (*(int32_t *)re_gvar(0x0055c974u, sizeof(int32_t), (void *)&MenuVar55C974))
#undef MenuVar5759A4
#define MenuVar5759A4 (*(int32_t *)re_gvar(0x005759a4u, sizeof(int32_t), (void *)&MenuVar5759A4))
#undef MenuVar575EE8
#define MenuVar575EE8 (*(int32_t *)re_gvar(0x00575ee8u, sizeof(int32_t), (void *)&MenuVar575EE8))
#undef MenuVar575EF8
#define MenuVar575EF8 (*(int32_t *)re_gvar(0x00575ef8u, sizeof(int32_t), (void *)&MenuVar575EF8))
#undef MenuVar575F30
#define MenuVar575F30 (*(int32_t *)re_gvar(0x00575f30u, sizeof(int32_t), (void *)&MenuVar575F30))
#undef MenuVar575F3C
#define MenuVar575F3C (*(int32_t *)re_gvar(0x00575f3cu, sizeof(int32_t), (void *)&MenuVar575F3C))
#undef MenuVar575F44
#define MenuVar575F44 (*(int32_t *)re_gvar(0x00575f44u, sizeof(int32_t), (void *)&MenuVar575F44))
#undef MenuVarB201DC
#define MenuVarB201DC (*(int32_t *)re_gvar(0x00b201dcu, sizeof(int32_t), (void *)&MenuVarB201DC))
#undef MenuVarB31F04
#define MenuVarB31F04 (*(int32_t *)re_gvar(0x00b31f04u, sizeof(int32_t), (void *)&MenuVarB31F04))
#undef MenuVarB87E4C
#define MenuVarB87E4C (*(int32_t *)re_gvar(0x00b87e4cu, sizeof(int32_t), (void *)&MenuVarB87E4C))
#undef MenuVarD118C8
#define MenuVarD118C8 (*(int32_t *)re_gvar(0x00d118c8u, sizeof(int32_t), (void *)&MenuVarD118C8))
#undef MenuVar54A844
#define MenuVar54A844 (*(int32_t *)re_gvar(0x0054a844u, sizeof(int32_t), (void *)&MenuVar54A844))
#undef MenuVar54A854
#define MenuVar54A854 (*(int32_t *)re_gvar(0x0054a854u, sizeof(int32_t), (void *)&MenuVar54A854))
#undef MenuMode1271060
#define MenuMode1271060 (*(int32_t *)re_gvar(0x01271060u, sizeof(int32_t), (void *)&MenuMode1271060))
#undef MenuFlag54A90C
#define MenuFlag54A90C (*(uint8_t *)re_gvar(0x0054a90cu, sizeof(uint8_t), (void *)&MenuFlag54A90C))
#undef MenuFlag54A91C
#define MenuFlag54A91C (*(uint8_t *)re_gvar(0x0054a91cu, sizeof(uint8_t), (void *)&MenuFlag54A91C))
#undef MenuFlag54A8FC
#define MenuFlag54A8FC (*(uint8_t *)re_gvar(0x0054a8fcu, sizeof(uint8_t), (void *)&MenuFlag54A8FC))
#undef MenuFlag54A92C
#define MenuFlag54A92C (*(uint8_t *)re_gvar(0x0054a92cu, sizeof(uint8_t), (void *)&MenuFlag54A92C))
#undef MenuFlag54A8EC
#define MenuFlag54A8EC (*(uint8_t *)re_gvar(0x0054a8ecu, sizeof(uint8_t), (void *)&MenuFlag54A8EC))
#undef MenuFlag54A94C
#define MenuFlag54A94C (*(uint8_t *)re_gvar(0x0054a94cu, sizeof(uint8_t), (void *)&MenuFlag54A94C))
#undef MenuFlag54A93C
#define MenuFlag54A93C (*(uint8_t *)re_gvar(0x0054a93cu, sizeof(uint8_t), (void *)&MenuFlag54A93C))
#undef MenuColorR54AA2C
#define MenuColorR54AA2C (*(uint8_t *)re_gvar(0x0054aa2cu, sizeof(uint8_t), (void *)&MenuColorR54AA2C))
#undef MenuColorG54AA2D
#define MenuColorG54AA2D (*(uint8_t *)re_gvar(0x0054aa2du, sizeof(uint8_t), (void *)&MenuColorG54AA2D))
#undef MenuColorB54AA2E
#define MenuColorB54AA2E (*(uint8_t *)re_gvar(0x0054aa2eu, sizeof(uint8_t), (void *)&MenuColorB54AA2E))
#undef MenuPosX54AA24
#define MenuPosX54AA24 (*(int32_t *)re_gvar(0x0054aa24u, sizeof(int32_t), (void *)&MenuPosX54AA24))
#undef MenuPosY54AA28
#define MenuPosY54AA28 (*(int32_t *)re_gvar(0x0054aa28u, sizeof(int32_t), (void *)&MenuPosY54AA28))
#undef MenuVal5D77CC
#define MenuVal5D77CC (*(int32_t *)re_gvar(0x005d77ccu, sizeof(int32_t), (void *)&MenuVal5D77CC))
#undef MenuVal5D77C4
#define MenuVal5D77C4 (*(int32_t *)re_gvar(0x005d77c4u, sizeof(int32_t), (void *)&MenuVal5D77C4))
#undef MenuVal5D77C8
#define MenuVal5D77C8 (*(int32_t *)re_gvar(0x005d77c8u, sizeof(int32_t), (void *)&MenuVal5D77C8))
#undef MenuByte5D77C1
#define MenuByte5D77C1 (*(uint8_t *)re_gvar(0x005d77c1u, sizeof(uint8_t), (void *)&MenuByte5D77C1))
#undef MenuByte5D77C0
#define MenuByte5D77C0 (*(uint8_t *)re_gvar(0x005d77c0u, sizeof(uint8_t), (void *)&MenuByte5D77C0))
#undef MenuTable54B010
#define MenuTable54B010 (*(MenuTable256_t *)re_gvar(0x0054b010u, sizeof(MenuTable256_t), (void *)&MenuTable54B010))
#undef MenuByte54ACD4
#define MenuByte54ACD4 (*(uint8_t *)re_gvar(0x0054acd4u, sizeof(uint8_t), (void *)&MenuByte54ACD4))
#undef MenuByte54ACE4
#define MenuByte54ACE4 (*(uint8_t *)re_gvar(0x0054ace4u, sizeof(uint8_t), (void *)&MenuByte54ACE4))
#undef MenuByte54ACF4
#define MenuByte54ACF4 (*(uint8_t *)re_gvar(0x0054acf4u, sizeof(uint8_t), (void *)&MenuByte54ACF4))
#undef MenuByte54AD04
#define MenuByte54AD04 (*(uint8_t *)re_gvar(0x0054ad04u, sizeof(uint8_t), (void *)&MenuByte54AD04))
#undef MenuByte54AD14
#define MenuByte54AD14 (*(uint8_t *)re_gvar(0x0054ad14u, sizeof(uint8_t), (void *)&MenuByte54AD14))
#undef MenuByte54AD24
#define MenuByte54AD24 (*(uint8_t *)re_gvar(0x0054ad24u, sizeof(uint8_t), (void *)&MenuByte54AD24))
#undef MenuByte54AD34
#define MenuByte54AD34 (*(uint8_t *)re_gvar(0x0054ad34u, sizeof(uint8_t), (void *)&MenuByte54AD34))
#undef MenuByte54AD44
#define MenuByte54AD44 (*(uint8_t *)re_gvar(0x0054ad44u, sizeof(uint8_t), (void *)&MenuByte54AD44))
#endif
/* gvar-img v2.03 end */
