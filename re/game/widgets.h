/* Партия функций: кнопки-обработчики меню, выбор пункта, шаги float, мелкие геттеры. Адрес в имени = оригинал. */
#pragma once
#include "gvar.h"
#include "unported.h"
#include "menuselect.h"
#include "menustate.h"
#include "uihandlers.h"
#include "uihandlers4.h"
typedef int32_t wd_ints5_t[5];
typedef int32_t wd_pairs4_t[8];
typedef uint8_t wd_bytes_t[0x400];
#define WI00575EE4 GAME_VAR(int32_t, WI00575EE4, 0x00575ee4)
#ifndef RE_HOOK_BUILD
#pragma push_macro("WI00575EE4") /*gvi*/
#undef WI00575EE4 /*gvi*/
extern int32_t WI00575EE4;
#pragma pop_macro("WI00575EE4") /*gvi*/
#endif
#define WI00B87E2C GAME_VAR(int32_t, WI00B87E2C, 0x00b87e2c)
#ifndef RE_HOOK_BUILD
#pragma push_macro("WI00B87E2C") /*gvi*/
#undef WI00B87E2C /*gvi*/
extern int32_t WI00B87E2C;
#pragma pop_macro("WI00B87E2C") /*gvi*/
#endif
#define WI005FE694 GAME_VAR(int32_t, WI005FE694, 0x005fe694)
#ifndef RE_HOOK_BUILD
#pragma push_macro("WI005FE694") /*gvi*/
#undef WI005FE694 /*gvi*/
extern int32_t WI005FE694;
#pragma pop_macro("WI005FE694") /*gvi*/
#endif
#define WU005FE788 GAME_VAR(uint32_t, WU005FE788, 0x005fe788)
#ifndef RE_HOOK_BUILD
#pragma push_macro("WU005FE788") /*gvi*/
#undef WU005FE788 /*gvi*/
extern uint32_t WU005FE788;
#pragma pop_macro("WU005FE788") /*gvi*/
#endif
#define WI005FE78C GAME_VAR(int32_t, WI005FE78C, 0x005fe78c)
#ifndef RE_HOOK_BUILD
#pragma push_macro("WI005FE78C") /*gvi*/
#undef WI005FE78C /*gvi*/
extern int32_t WI005FE78C;
#pragma pop_macro("WI005FE78C") /*gvi*/
#endif
#define WI005FE790 GAME_VAR(int32_t, WI005FE790, 0x005fe790)
#ifndef RE_HOOK_BUILD
#pragma push_macro("WI005FE790") /*gvi*/
#undef WI005FE790 /*gvi*/
extern int32_t WI005FE790;
#pragma pop_macro("WI005FE790") /*gvi*/
#endif
#define WF00575F14 GAME_VAR(float, WF00575F14, 0x00575f14)
#ifndef RE_HOOK_BUILD
#pragma push_macro("WF00575F14") /*gvi*/
#undef WF00575F14 /*gvi*/
extern float WF00575F14;
#pragma pop_macro("WF00575F14") /*gvi*/
#endif
#define WF00575F18 GAME_VAR(float, WF00575F18, 0x00575f18)
#ifndef RE_HOOK_BUILD
#pragma push_macro("WF00575F18") /*gvi*/
#undef WF00575F18 /*gvi*/
extern float WF00575F18;
#pragma pop_macro("WF00575F18") /*gvi*/
#endif
#define WF00546020 GAME_VAR(float, WF00546020, 0x00546020)
#ifndef RE_HOOK_BUILD
#pragma push_macro("WF00546020") /*gvi*/
#undef WF00546020 /*gvi*/
extern float WF00546020;
#pragma pop_macro("WF00546020") /*gvi*/
#endif
#define WF00546024 GAME_VAR(float, WF00546024, 0x00546024)
#ifndef RE_HOOK_BUILD
#pragma push_macro("WF00546024") /*gvi*/
#undef WF00546024 /*gvi*/
extern float WF00546024;
#pragma pop_macro("WF00546024") /*gvi*/
#endif
#define WF0054606C GAME_VAR(float, WF0054606C, 0x0054606c)
#ifndef RE_HOOK_BUILD
#pragma push_macro("WF0054606C") /*gvi*/
#undef WF0054606C /*gvi*/
extern float WF0054606C;
#pragma pop_macro("WF0054606C") /*gvi*/
#endif
#define WU0054E830 GAME_VAR(uint32_t, WU0054E830, 0x0054e830)
#ifndef RE_HOOK_BUILD
#pragma push_macro("WU0054E830") /*gvi*/
#undef WU0054E830 /*gvi*/
extern uint32_t WU0054E830;
#pragma pop_macro("WU0054E830") /*gvi*/
#endif
#define WU00C55A70 GAME_VAR(uint32_t, WU00C55A70, 0x00c55a70)
#ifndef RE_HOOK_BUILD
#pragma push_macro("WU00C55A70") /*gvi*/
#undef WU00C55A70 /*gvi*/
extern uint32_t WU00C55A70;
#pragma pop_macro("WU00C55A70") /*gvi*/
#endif
#define WU0054CBB0 GAME_VAR(uint32_t, WU0054CBB0, 0x0054cbb0)
#ifndef RE_HOOK_BUILD
#pragma push_macro("WU0054CBB0") /*gvi*/
#undef WU0054CBB0 /*gvi*/
extern uint32_t WU0054CBB0;
#pragma pop_macro("WU0054CBB0") /*gvi*/
#endif
#define WU0054CBC4 GAME_VAR(uint32_t, WU0054CBC4, 0x0054cbc4)
#ifndef RE_HOOK_BUILD
#pragma push_macro("WU0054CBC4") /*gvi*/
#undef WU0054CBC4 /*gvi*/
extern uint32_t WU0054CBC4;
#pragma pop_macro("WU0054CBC4") /*gvi*/
#endif
#define WU0054CBD8 GAME_VAR(uint32_t, WU0054CBD8, 0x0054cbd8)
#ifndef RE_HOOK_BUILD
#pragma push_macro("WU0054CBD8") /*gvi*/
#undef WU0054CBD8 /*gvi*/
extern uint32_t WU0054CBD8;
#pragma pop_macro("WU0054CBD8") /*gvi*/
#endif
#define WU0054CBEC GAME_VAR(uint32_t, WU0054CBEC, 0x0054cbec)
#ifndef RE_HOOK_BUILD
#pragma push_macro("WU0054CBEC") /*gvi*/
#undef WU0054CBEC /*gvi*/
extern uint32_t WU0054CBEC;
#pragma pop_macro("WU0054CBEC") /*gvi*/
#endif
#define WU0054CC00 GAME_VAR(uint32_t, WU0054CC00, 0x0054cc00)
#ifndef RE_HOOK_BUILD
#pragma push_macro("WU0054CC00") /*gvi*/
#undef WU0054CC00 /*gvi*/
extern uint32_t WU0054CC00;
#pragma pop_macro("WU0054CC00") /*gvi*/
#endif
#define WU0054CC14 GAME_VAR(uint32_t, WU0054CC14, 0x0054cc14)
#ifndef RE_HOOK_BUILD
#pragma push_macro("WU0054CC14") /*gvi*/
#undef WU0054CC14 /*gvi*/
extern uint32_t WU0054CC14;
#pragma pop_macro("WU0054CC14") /*gvi*/
#endif
#define WU0054CC28 GAME_VAR(uint32_t, WU0054CC28, 0x0054cc28)
#ifndef RE_HOOK_BUILD
#pragma push_macro("WU0054CC28") /*gvi*/
#undef WU0054CC28 /*gvi*/
extern uint32_t WU0054CC28;
#pragma pop_macro("WU0054CC28") /*gvi*/
#endif
#define WA00B20330 GAME_VAR(wd_ints5_t, WA00B20330, 0x00b20330)
#ifndef RE_HOOK_BUILD
#pragma push_macro("WA00B20330") /*gvi*/
#undef WA00B20330 /*gvi*/
extern wd_ints5_t WA00B20330;
#pragma pop_macro("WA00B20330") /*gvi*/
#endif
#define WI00B20344 GAME_VAR(int32_t, WI00B20344, 0x00b20344)
#ifndef RE_HOOK_BUILD
#pragma push_macro("WI00B20344") /*gvi*/
#undef WI00B20344 /*gvi*/
extern int32_t WI00B20344;
#pragma pop_macro("WI00B20344") /*gvi*/
#endif
#define WA0056039C GAME_VAR(wd_pairs4_t, WA0056039C, 0x0056039c)
#ifndef RE_HOOK_BUILD
#pragma push_macro("WA0056039C") /*gvi*/
#undef WA0056039C /*gvi*/
extern wd_pairs4_t WA0056039C;
#pragma pop_macro("WA0056039C") /*gvi*/
#endif
#define WI00B20348 GAME_VAR(int32_t, WI00B20348, 0x00b20348)
#ifndef RE_HOOK_BUILD
#pragma push_macro("WI00B20348") /*gvi*/
#undef WI00B20348 /*gvi*/
extern int32_t WI00B20348;
#pragma pop_macro("WI00B20348") /*gvi*/
#endif
#define WH00B2C3A8 GAME_VAR(uint16_t, WH00B2C3A8, 0x00b2c3a8)
#ifndef RE_HOOK_BUILD
#pragma push_macro("WH00B2C3A8") /*gvi*/
#undef WH00B2C3A8 /*gvi*/
extern uint16_t WH00B2C3A8;
#pragma pop_macro("WH00B2C3A8") /*gvi*/
#endif
#define WB0054C6D4 GAME_VAR(wd_bytes_t, WB0054C6D4, 0x0054c6d4)
#ifndef RE_HOOK_BUILD
#pragma push_macro("WB0054C6D4") /*gvi*/
#undef WB0054C6D4 /*gvi*/
extern wd_bytes_t WB0054C6D4;
#pragma pop_macro("WB0054C6D4") /*gvi*/
#endif
#define WB0054C944 GAME_VAR(wd_bytes_t, WB0054C944, 0x0054c944)
#ifndef RE_HOOK_BUILD
#pragma push_macro("WB0054C944") /*gvi*/
#undef WB0054C944 /*gvi*/
extern wd_bytes_t WB0054C944;
#pragma pop_macro("WB0054C944") /*gvi*/
#endif
int32_t SelectRow004110C2(void);
int32_t SelectRow00411177(void);
int32_t SelectRow0041122C(void);
int32_t SelectRow004112E1(void);
int32_t SelectRow00411396(void);
int32_t SelectRow0041144B(void);
int32_t SelectRow00411500(void);
int32_t SelectRow004115B5(void);
int32_t SelectRow0041166A(void);
int32_t SelectRow0041171F(void);
int32_t SelectRow004117D4(void);
int32_t SelectRow00411889(void);
int32_t SelectRow0041193E(void);
int32_t SelectRow004119F3(void);
void VolumeUp00409BC9(void);
void VolumeDown00409BFD(void);
int32_t CycleInc0040E918(void);
int32_t CycleDec0040F364(void);
int32_t CycleInc0040F3AD(void);
void MenuRowsTo2_00412254(void);
void MenuAllRowsTo2_00412280(void);
void MenuRowsTo3_00412643(void);
void MenuRowsTo2_0041266F(void);
void MenuAllRowsTo2_0041269B(void);
void SetIconName00412A36(int32_t reset);
void SetIconName00412AA4(int32_t reset);
void SetIconName00412B12(int32_t reset);
void SetIconName00412B80(int32_t reset);
void SetIconName00412BEE(int32_t reset);
void SetIconName00412C5C(int32_t reset);
void SetIconName00412CCA(int32_t reset);
void SetIconName00412D38(int32_t reset);
void StepUp00415848(void);
void StepDown00415877(void);
void StepUp004158A6(void);
void StepDown004158D5(void);
void StepUp0050F9B4(void);
void StepDown0050F9E3(void);
void StepUp0050FA12(void);
void StepDown0050FA41(void);
void CopyWord0041AD8D(void);
int32_t RangeCheck00514E6A(const int32_t* p, int32_t n);
float Dot3_00526029(const float* a, const float* b);
float GetConst0041FA5E(void);
void ClearSlots004D61CF(void);
void ClearPairs004D6C20(void);
void Pack565_004D950F(int16_t r, int16_t g, int16_t b);
void AddVelocity004E122C(int32_t* o);
int32_t Get4Words004E4379(const int32_t* s, int32_t* d);
void Toggle0050FE82(void);
void Toggle0050FEA3(void);
void Toggle0050FEC4(void);
void Toggle0050FF41(void);
void Toggle0050FF62(void);
void Toggle0050FF83(void);
void Toggle0050FFA4(void);
void Toggle0050FFC5(void);
void Toggle0050FFE6(void);
void Toggle00510007(void);
/* gvar-img v2.03 begin (tools/gen_gvar_img.py) */
#if !defined(RE_HOOK_BUILD) && !defined(RE_GVAR_PLAIN)
#undef WI00575EE4
#define WI00575EE4 (*(int32_t *)re_gvar(0x00575ee4u, sizeof(int32_t), (void *)&WI00575EE4))
#undef WI00B87E2C
#define WI00B87E2C (*(int32_t *)re_gvar(0x00b87e2cu, sizeof(int32_t), (void *)&WI00B87E2C))
#undef WI005FE694
#define WI005FE694 (*(int32_t *)re_gvar(0x005fe694u, sizeof(int32_t), (void *)&WI005FE694))
#undef WU005FE788
#define WU005FE788 (*(uint32_t *)re_gvar(0x005fe788u, sizeof(uint32_t), (void *)&WU005FE788))
#undef WI005FE78C
#define WI005FE78C (*(int32_t *)re_gvar(0x005fe78cu, sizeof(int32_t), (void *)&WI005FE78C))
#undef WI005FE790
#define WI005FE790 (*(int32_t *)re_gvar(0x005fe790u, sizeof(int32_t), (void *)&WI005FE790))
#undef WF00575F14
#define WF00575F14 (*(float *)re_gvar(0x00575f14u, sizeof(float), (void *)&WF00575F14))
#undef WF00575F18
#define WF00575F18 (*(float *)re_gvar(0x00575f18u, sizeof(float), (void *)&WF00575F18))
#undef WF00546020
#define WF00546020 (*(float *)re_gvar(0x00546020u, sizeof(float), (void *)&WF00546020))
#undef WF00546024
#define WF00546024 (*(float *)re_gvar(0x00546024u, sizeof(float), (void *)&WF00546024))
#undef WF0054606C
#define WF0054606C (*(float *)re_gvar(0x0054606cu, sizeof(float), (void *)&WF0054606C))
#undef WU0054E830
#define WU0054E830 (*(uint32_t *)re_gvar(0x0054e830u, sizeof(uint32_t), (void *)&WU0054E830))
#undef WU00C55A70
#define WU00C55A70 (*(uint32_t *)re_gvar(0x00c55a70u, sizeof(uint32_t), (void *)&WU00C55A70))
#undef WU0054CBB0
#define WU0054CBB0 (*(uint32_t *)re_gvar(0x0054cbb0u, sizeof(uint32_t), (void *)&WU0054CBB0))
#undef WU0054CBC4
#define WU0054CBC4 (*(uint32_t *)re_gvar(0x0054cbc4u, sizeof(uint32_t), (void *)&WU0054CBC4))
#undef WU0054CBD8
#define WU0054CBD8 (*(uint32_t *)re_gvar(0x0054cbd8u, sizeof(uint32_t), (void *)&WU0054CBD8))
#undef WU0054CBEC
#define WU0054CBEC (*(uint32_t *)re_gvar(0x0054cbecu, sizeof(uint32_t), (void *)&WU0054CBEC))
#undef WU0054CC00
#define WU0054CC00 (*(uint32_t *)re_gvar(0x0054cc00u, sizeof(uint32_t), (void *)&WU0054CC00))
#undef WU0054CC14
#define WU0054CC14 (*(uint32_t *)re_gvar(0x0054cc14u, sizeof(uint32_t), (void *)&WU0054CC14))
#undef WU0054CC28
#define WU0054CC28 (*(uint32_t *)re_gvar(0x0054cc28u, sizeof(uint32_t), (void *)&WU0054CC28))
#undef WA00B20330
#define WA00B20330 (*(wd_ints5_t *)re_gvar(0x00b20330u, sizeof(wd_ints5_t), (void *)&WA00B20330))
#undef WI00B20344
#define WI00B20344 (*(int32_t *)re_gvar(0x00b20344u, sizeof(int32_t), (void *)&WI00B20344))
#undef WA0056039C
#define WA0056039C (*(wd_pairs4_t *)re_gvar(0x0056039cu, sizeof(wd_pairs4_t), (void *)&WA0056039C))
#undef WI00B20348
#define WI00B20348 (*(int32_t *)re_gvar(0x00b20348u, sizeof(int32_t), (void *)&WI00B20348))
#undef WH00B2C3A8
#define WH00B2C3A8 (*(uint16_t *)re_gvar(0x00b2c3a8u, sizeof(uint16_t), (void *)&WH00B2C3A8))
#undef WB0054C6D4
#define WB0054C6D4 (*(wd_bytes_t *)re_gvar(0x0054c6d4u, sizeof(wd_bytes_t), (void *)&WB0054C6D4))
#undef WB0054C944
#define WB0054C944 (*(wd_bytes_t *)re_gvar(0x0054c944u, sizeof(wd_bytes_t), (void *)&WB0054C944))
#endif
/* gvar-img v2.03 end */
