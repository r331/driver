/* Мелкие функции Game.exe: сеттеры, пулы индексов, опкоды скрипта, примитивы вектора. Адрес в имени = оригинал. */
#pragma once
#include "gvar.h"
typedef uint8_t sf_bytes_t[0x4000];
typedef int32_t sf_ints_t[0x1000];
#define S_00549B04 GAME_VAR(sf_bytes_t, S_00549B04, 0x00549b04)
#ifndef RE_HOOK_BUILD
extern sf_bytes_t S_00549B04;
#endif
#define S_0054E44C GAME_VAR(sf_bytes_t, S_0054E44C, 0x0054e44c)
#ifndef RE_HOOK_BUILD
extern sf_bytes_t S_0054E44C;
#endif
#define S_0054E44D GAME_VAR(sf_bytes_t, S_0054E44D, 0x0054e44d)
#ifndef RE_HOOK_BUILD
extern sf_bytes_t S_0054E44D;
#endif
#define S_0054E44E GAME_VAR(sf_bytes_t, S_0054E44E, 0x0054e44e)
#ifndef RE_HOOK_BUILD
extern sf_bytes_t S_0054E44E;
#endif
#define S_0054E6AC GAME_VAR(sf_bytes_t, S_0054E6AC, 0x0054e6ac)
#ifndef RE_HOOK_BUILD
extern sf_bytes_t S_0054E6AC;
#endif
#define S_0054E6AD GAME_VAR(sf_bytes_t, S_0054E6AD, 0x0054e6ad)
#ifndef RE_HOOK_BUILD
extern sf_bytes_t S_0054E6AD;
#endif
#define S_0054E6AE GAME_VAR(sf_bytes_t, S_0054E6AE, 0x0054e6ae)
#ifndef RE_HOOK_BUILD
extern sf_bytes_t S_0054E6AE;
#endif
#define S_00560A88 GAME_VAR(sf_bytes_t, S_00560A88, 0x00560a88)
#ifndef RE_HOOK_BUILD
extern sf_bytes_t S_00560A88;
#endif
#define S_0057B658 GAME_VAR(int32_t, S_0057B658, 0x0057b658)
#ifndef RE_HOOK_BUILD
extern int32_t S_0057B658;
#endif
#define S_0057B65C GAME_VAR(int32_t, S_0057B65C, 0x0057b65c)
#ifndef RE_HOOK_BUILD
extern int32_t S_0057B65C;
#endif
#define S_005FEA30 GAME_VAR(int32_t, S_005FEA30, 0x005fea30)
#ifndef RE_HOOK_BUILD
extern int32_t S_005FEA30;
#endif
#define S_005FEA8C GAME_VAR(int32_t, S_005FEA8C, 0x005fea8c)
#ifndef RE_HOOK_BUILD
extern int32_t S_005FEA8C;
#endif
#define S_00A421D8 GAME_VAR(uint32_t, S_00A421D8, 0x00a421d8)
#ifndef RE_HOOK_BUILD
extern uint32_t S_00A421D8;
#endif
#define S_00B31E40 GAME_VAR(uint8_t, S_00B31E40, 0x00b31e40)
#ifndef RE_HOOK_BUILD
extern uint8_t S_00B31E40;
#endif
#define S_00B31E41 GAME_VAR(uint8_t, S_00B31E41, 0x00b31e41)
#ifndef RE_HOOK_BUILD
extern uint8_t S_00B31E41;
#endif
#define S_00B31E42 GAME_VAR(uint8_t, S_00B31E42, 0x00b31e42)
#ifndef RE_HOOK_BUILD
extern uint8_t S_00B31E42;
#endif
#define S_00B31E43 GAME_VAR(uint8_t, S_00B31E43, 0x00b31e43)
#ifndef RE_HOOK_BUILD
extern uint8_t S_00B31E43;
#endif
#define S_00B5A76C GAME_VAR(int32_t, S_00B5A76C, 0x00b5a76c)
#ifndef RE_HOOK_BUILD
extern int32_t S_00B5A76C;
#endif
#define S_00B5A770 GAME_VAR(int32_t, S_00B5A770, 0x00b5a770)
#ifndef RE_HOOK_BUILD
extern int32_t S_00B5A770;
#endif
#define S_00B5A77C GAME_VAR(int32_t, S_00B5A77C, 0x00b5a77c)
#ifndef RE_HOOK_BUILD
extern int32_t S_00B5A77C;
#endif
#define S_00B5A834 GAME_VAR(uint8_t, S_00B5A834, 0x00b5a834)
#ifndef RE_HOOK_BUILD
extern uint8_t S_00B5A834;
#endif
#define S_00B5A835 GAME_VAR(uint8_t, S_00B5A835, 0x00b5a835)
#ifndef RE_HOOK_BUILD
extern uint8_t S_00B5A835;
#endif
#define S_00B5A836 GAME_VAR(uint8_t, S_00B5A836, 0x00b5a836)
#ifndef RE_HOOK_BUILD
extern uint8_t S_00B5A836;
#endif
#define S_00B93E6C GAME_VAR(uint32_t, S_00B93E6C, 0x00b93e6c)
#ifndef RE_HOOK_BUILD
extern uint32_t S_00B93E6C;
#endif
#define S_00B93E70 GAME_VAR(uint32_t, S_00B93E70, 0x00b93e70)
#ifndef RE_HOOK_BUILD
extern uint32_t S_00B93E70;
#endif
#define S_00B93E74 GAME_VAR(uint32_t, S_00B93E74, 0x00b93e74)
#ifndef RE_HOOK_BUILD
extern uint32_t S_00B93E74;
#endif
#define S_00BA5280 GAME_VAR(uint32_t, S_00BA5280, 0x00ba5280)
#ifndef RE_HOOK_BUILD
extern uint32_t S_00BA5280;
#endif
#define S_00BA52D4 GAME_VAR(uint32_t, S_00BA52D4, 0x00ba52d4)
#ifndef RE_HOOK_BUILD
extern uint32_t S_00BA52D4;
#endif
#define S_00BA5380 GAME_VAR(uint32_t, S_00BA5380, 0x00ba5380)
#ifndef RE_HOOK_BUILD
extern uint32_t S_00BA5380;
#endif
#define S_00BDC2A0 GAME_VAR(sf_bytes_t, S_00BDC2A0, 0x00bdc2a0)
#ifndef RE_HOOK_BUILD
extern sf_bytes_t S_00BDC2A0;
#endif
#define S_00BDC2A1 GAME_VAR(sf_bytes_t, S_00BDC2A1, 0x00bdc2a1)
#ifndef RE_HOOK_BUILD
extern sf_bytes_t S_00BDC2A1;
#endif
#define S_00BDCD00 GAME_VAR(sf_ints_t, S_00BDCD00, 0x00bdcd00)
#ifndef RE_HOOK_BUILD
extern sf_ints_t S_00BDCD00;
#endif
#define S_00C808A0 GAME_VAR(int32_t, S_00C808A0, 0x00c808a0)
#ifndef RE_HOOK_BUILD
extern int32_t S_00C808A0;
#endif
#define S_00D0CC60 GAME_VAR(sf_bytes_t, S_00D0CC60, 0x00d0cc60)
#ifndef RE_HOOK_BUILD
extern sf_bytes_t S_00D0CC60;
#endif
#define S_00D0DDE0 GAME_VAR(int32_t, S_00D0DDE0, 0x00d0dde0)
#ifndef RE_HOOK_BUILD
extern int32_t S_00D0DDE0;
#endif
#define S_00D11804 GAME_VAR(int32_t, S_00D11804, 0x00d11804)
#ifndef RE_HOOK_BUILD
extern int32_t S_00D11804;
#endif
#define S_00D11878 GAME_VAR(int32_t, S_00D11878, 0x00d11878)
#ifndef RE_HOOK_BUILD
extern int32_t S_00D11878;
#endif
#define S_00D1192C GAME_VAR(int32_t, S_00D1192C, 0x00d1192c)
#ifndef RE_HOOK_BUILD
extern int32_t S_00D1192C;
#endif
#define S_00D1240C GAME_VAR(uint8_t*, S_00D1240C, 0x00d1240c)
#ifndef RE_HOOK_BUILD
extern uint8_t* S_00D1240C;
#endif
#define S_00D12410 GAME_VAR(uint16_t*, S_00D12410, 0x00d12410)
#ifndef RE_HOOK_BUILD
extern uint16_t* S_00D12410;
#endif
#define S_00D12414 GAME_VAR(int32_t, S_00D12414, 0x00d12414)
#ifndef RE_HOOK_BUILD
extern int32_t S_00D12414;
#endif
#define S_010EA8A0 GAME_VAR(sf_bytes_t, S_010EA8A0, 0x010ea8a0)
#ifndef RE_HOOK_BUILD
extern sf_bytes_t S_010EA8A0;
#endif
#define S_010FAF40 GAME_VAR(sf_bytes_t, S_010FAF40, 0x010faf40)
#ifndef RE_HOOK_BUILD
extern sf_bytes_t S_010FAF40;
#endif
#define S_010FB0E0 GAME_VAR(sf_bytes_t, S_010FB0E0, 0x010fb0e0)
#ifndef RE_HOOK_BUILD
extern sf_bytes_t S_010FB0E0;
#endif
#define S_010FFA24 GAME_VAR(int32_t, S_010FFA24, 0x010ffa24)
#ifndef RE_HOOK_BUILD
extern int32_t S_010FFA24;
#endif
#define S_0110E144 GAME_VAR(int32_t, S_0110E144, 0x0110e144)
#ifndef RE_HOOK_BUILD
extern int32_t S_0110E144;
#endif
#define S_011173C8 GAME_VAR(int32_t, S_011173C8, 0x011173c8)
#ifndef RE_HOOK_BUILD
extern int32_t S_011173C8;
#endif
#define S_01136C74 GAME_VAR(int32_t, S_01136C74, 0x01136c74)
#ifndef RE_HOOK_BUILD
extern int32_t S_01136C74;
#endif
#define S_01139A34 GAME_VAR(int32_t, S_01139A34, 0x01139a34)
#ifndef RE_HOOK_BUILD
extern int32_t S_01139A34;
#endif
#define S_011443EA GAME_VAR(sf_bytes_t, S_011443EA, 0x011443ea)
#ifndef RE_HOOK_BUILD
extern sf_bytes_t S_011443EA;
#endif
#define S_0127104C GAME_VAR(uint32_t, S_0127104C, 0x0127104c)
#ifndef RE_HOOK_BUILD
extern uint32_t S_0127104C;
#endif
void NoopFn0041F81E(void);
void NoopFn0041FA49(void);
void NoopFn0041FA50(void);
void NoopFn0041FA57(void);
void NoopFn0041FA7D(void);
void NoopFn0041FA8B(void);
void NoopFn0041FA92(void);
void NoopFn0041FAB9(void);
int32_t ReturnZero004D03FD(void);
int32_t ReturnZero004E3B19(void);
int32_t ReturnOne00519D22(void);
void SetField24_00502779(uint8_t* p, int32_t v);
void ClearField2C_00502680(uint8_t* p);
void AddToCounter00519D09(int32_t v);
void ClearFlagByte0048FBBA(int32_t n);
void ScriptSetWait004F5C72(int32_t* p, int32_t v);
void ScriptSetWaitX50_004F5C58(int32_t* p, int32_t v);
void ToggleBit0051049E(void);
int32_t IsFlag80_00514E4C(uint8_t* p);
void SetFlagFromArg0041E1E4(int32_t v);
void SetLatchValue0050E940(int32_t v);
int32_t IsSlotActive00524473(int32_t i);
int32_t TestBit0041B7AD(uint32_t n);
void SetRGB00516EB4(uint8_t r, uint8_t g, uint8_t b);
void SlotSetOn0052432A(int32_t i);
void SlotSetOff0052434A(int32_t i);
void PoolPush004AC6AC(uint16_t v);
void PoolPush004AC702(uint16_t v);
void PoolPush004AC755(uint16_t v);
int32_t PoolPop004AC726(void);
int32_t PoolPop004AC6D0(void);
int32_t CounterDecrement004D97B8(void);
int32_t AllocSlot00492508(void);
uint32_t PackRGB00503ECC(uint8_t* p);
int32_t IsKeyOnly004E38B4(void);
int32_t IsKeyOnly004E38D9(void);
int32_t ExchangeTable00522F2A(int32_t i, int32_t v);
void InitFlags004946DA(uint8_t* p);
void WrapCounter004A3A80(uint8_t* p);
void CopyVec3_005265BC(uint32_t* v);
void CopyVec3_0052797A(uint32_t* v);
void NegateVec3_00526FB6(float* v);
void NegateVec3_005270F6(float* v);
void NegateVec3To_00526FE3(float* d, float* s);
void ResetVec_005272C6(uint32_t* v);
void CopySlotTemplate004A1010(void);
int32_t ScriptOpSkipClear004D1111(void);
int32_t ScriptOpSetBit4_004D13D8(void);
int32_t ScriptOpClearBit2_004D1402(void);
int32_t ScriptOpSetBit200_004D03D0(void);
int32_t ScriptOpSetBit2_004D0404(void);
int32_t ScriptOpToggle10_004D1737(void);
int32_t ScriptOpSkip4_004D1601(void);
void RingAdvance004D7B36(void);
void MenuRowsTo3_00404E52(void);
void MenuRowsIf0To2_00404E7E(int32_t f);
void SetColorRed00417A55(void);
void SetColorWhite00417AA2(void);
void SetColorRed0041A051(void);
void SetColorWhite0041A085(void);
