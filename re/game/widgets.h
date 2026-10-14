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
extern int32_t WI00575EE4;
#endif
#define WI00B87E2C GAME_VAR(int32_t, WI00B87E2C, 0x00b87e2c)
#ifndef RE_HOOK_BUILD
extern int32_t WI00B87E2C;
#endif
#define WI005FE694 GAME_VAR(int32_t, WI005FE694, 0x005fe694)
#ifndef RE_HOOK_BUILD
extern int32_t WI005FE694;
#endif
#define WU005FE788 GAME_VAR(uint32_t, WU005FE788, 0x005fe788)
#ifndef RE_HOOK_BUILD
extern uint32_t WU005FE788;
#endif
#define WI005FE78C GAME_VAR(int32_t, WI005FE78C, 0x005fe78c)
#ifndef RE_HOOK_BUILD
extern int32_t WI005FE78C;
#endif
#define WI005FE790 GAME_VAR(int32_t, WI005FE790, 0x005fe790)
#ifndef RE_HOOK_BUILD
extern int32_t WI005FE790;
#endif
#define WF00575F14 GAME_VAR(float, WF00575F14, 0x00575f14)
#ifndef RE_HOOK_BUILD
extern float WF00575F14;
#endif
#define WF00575F18 GAME_VAR(float, WF00575F18, 0x00575f18)
#ifndef RE_HOOK_BUILD
extern float WF00575F18;
#endif
#define WF00546020 GAME_VAR(float, WF00546020, 0x00546020)
#ifndef RE_HOOK_BUILD
extern float WF00546020;
#endif
#define WF00546024 GAME_VAR(float, WF00546024, 0x00546024)
#ifndef RE_HOOK_BUILD
extern float WF00546024;
#endif
#define WF0054606C GAME_VAR(float, WF0054606C, 0x0054606c)
#ifndef RE_HOOK_BUILD
extern float WF0054606C;
#endif
#define WU0054E830 GAME_VAR(uint32_t, WU0054E830, 0x0054e830)
#ifndef RE_HOOK_BUILD
extern uint32_t WU0054E830;
#endif
#define WU00C55A70 GAME_VAR(uint32_t, WU00C55A70, 0x00c55a70)
#ifndef RE_HOOK_BUILD
extern uint32_t WU00C55A70;
#endif
#define WU0054CBB0 GAME_VAR(uint32_t, WU0054CBB0, 0x0054cbb0)
#ifndef RE_HOOK_BUILD
extern uint32_t WU0054CBB0;
#endif
#define WU0054CBC4 GAME_VAR(uint32_t, WU0054CBC4, 0x0054cbc4)
#ifndef RE_HOOK_BUILD
extern uint32_t WU0054CBC4;
#endif
#define WU0054CBD8 GAME_VAR(uint32_t, WU0054CBD8, 0x0054cbd8)
#ifndef RE_HOOK_BUILD
extern uint32_t WU0054CBD8;
#endif
#define WU0054CBEC GAME_VAR(uint32_t, WU0054CBEC, 0x0054cbec)
#ifndef RE_HOOK_BUILD
extern uint32_t WU0054CBEC;
#endif
#define WU0054CC00 GAME_VAR(uint32_t, WU0054CC00, 0x0054cc00)
#ifndef RE_HOOK_BUILD
extern uint32_t WU0054CC00;
#endif
#define WU0054CC14 GAME_VAR(uint32_t, WU0054CC14, 0x0054cc14)
#ifndef RE_HOOK_BUILD
extern uint32_t WU0054CC14;
#endif
#define WU0054CC28 GAME_VAR(uint32_t, WU0054CC28, 0x0054cc28)
#ifndef RE_HOOK_BUILD
extern uint32_t WU0054CC28;
#endif
#define WA00B20330 GAME_VAR(wd_ints5_t, WA00B20330, 0x00b20330)
#ifndef RE_HOOK_BUILD
extern wd_ints5_t WA00B20330;
#endif
#define WI00B20344 GAME_VAR(int32_t, WI00B20344, 0x00b20344)
#ifndef RE_HOOK_BUILD
extern int32_t WI00B20344;
#endif
#define WA0056039C GAME_VAR(wd_pairs4_t, WA0056039C, 0x0056039c)
#ifndef RE_HOOK_BUILD
extern wd_pairs4_t WA0056039C;
#endif
#define WI00B20348 GAME_VAR(int32_t, WI00B20348, 0x00b20348)
#ifndef RE_HOOK_BUILD
extern int32_t WI00B20348;
#endif
#define WH00B2C3A8 GAME_VAR(uint16_t, WH00B2C3A8, 0x00b2c3a8)
#ifndef RE_HOOK_BUILD
extern uint16_t WH00B2C3A8;
#endif
#define WB0054C6D4 GAME_VAR(wd_bytes_t, WB0054C6D4, 0x0054c6d4)
#ifndef RE_HOOK_BUILD
extern wd_bytes_t WB0054C6D4;
#endif
#define WB0054C944 GAME_VAR(wd_bytes_t, WB0054C944, 0x0054c944)
#ifndef RE_HOOK_BUILD
extern wd_bytes_t WB0054C944;
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
