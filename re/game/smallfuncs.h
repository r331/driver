/* Мелкие функции Game.exe: сеттеры, пулы индексов, опкоды скрипта, примитивы вектора. Адрес в имени = оригинал. */
#pragma once
#include "gvar.h"
typedef uint8_t sf_bytes_t[0x4000];
typedef int32_t sf_ints_t[0x1000];
#define S_00549B04 GAME_VAR(sf_bytes_t, S_00549B04, 0x00549b04)
#ifndef RE_HOOK_BUILD
#pragma push_macro("S_00549B04") /*gvi*/
#undef S_00549B04 /*gvi*/
extern sf_bytes_t S_00549B04;
#pragma pop_macro("S_00549B04") /*gvi*/
#endif
#define S_0054E44C GAME_VAR(sf_bytes_t, S_0054E44C, 0x0054e44c)
#ifndef RE_HOOK_BUILD
#pragma push_macro("S_0054E44C") /*gvi*/
#undef S_0054E44C /*gvi*/
extern sf_bytes_t S_0054E44C;
#pragma pop_macro("S_0054E44C") /*gvi*/
#endif
#define S_0054E44D GAME_VAR(sf_bytes_t, S_0054E44D, 0x0054e44d)
#ifndef RE_HOOK_BUILD
#pragma push_macro("S_0054E44D") /*gvi*/
#undef S_0054E44D /*gvi*/
extern sf_bytes_t S_0054E44D;
#pragma pop_macro("S_0054E44D") /*gvi*/
#endif
#define S_0054E44E GAME_VAR(sf_bytes_t, S_0054E44E, 0x0054e44e)
#ifndef RE_HOOK_BUILD
#pragma push_macro("S_0054E44E") /*gvi*/
#undef S_0054E44E /*gvi*/
extern sf_bytes_t S_0054E44E;
#pragma pop_macro("S_0054E44E") /*gvi*/
#endif
#define S_0054E6AC GAME_VAR(sf_bytes_t, S_0054E6AC, 0x0054e6ac)
#ifndef RE_HOOK_BUILD
#pragma push_macro("S_0054E6AC") /*gvi*/
#undef S_0054E6AC /*gvi*/
extern sf_bytes_t S_0054E6AC;
#pragma pop_macro("S_0054E6AC") /*gvi*/
#endif
#define S_0054E6AD GAME_VAR(sf_bytes_t, S_0054E6AD, 0x0054e6ad)
#ifndef RE_HOOK_BUILD
#pragma push_macro("S_0054E6AD") /*gvi*/
#undef S_0054E6AD /*gvi*/
extern sf_bytes_t S_0054E6AD;
#pragma pop_macro("S_0054E6AD") /*gvi*/
#endif
#define S_0054E6AE GAME_VAR(sf_bytes_t, S_0054E6AE, 0x0054e6ae)
#ifndef RE_HOOK_BUILD
#pragma push_macro("S_0054E6AE") /*gvi*/
#undef S_0054E6AE /*gvi*/
extern sf_bytes_t S_0054E6AE;
#pragma pop_macro("S_0054E6AE") /*gvi*/
#endif
#define S_00560A88 GAME_VAR(sf_bytes_t, S_00560A88, 0x00560a88)
#ifndef RE_HOOK_BUILD
#pragma push_macro("S_00560A88") /*gvi*/
#undef S_00560A88 /*gvi*/
extern sf_bytes_t S_00560A88;
#pragma pop_macro("S_00560A88") /*gvi*/
#endif
#define S_0057B658 GAME_VAR(int32_t, S_0057B658, 0x0057b658)
#ifndef RE_HOOK_BUILD
#pragma push_macro("S_0057B658") /*gvi*/
#undef S_0057B658 /*gvi*/
extern int32_t S_0057B658;
#pragma pop_macro("S_0057B658") /*gvi*/
#endif
#define S_0057B65C GAME_VAR(int32_t, S_0057B65C, 0x0057b65c)
#ifndef RE_HOOK_BUILD
#pragma push_macro("S_0057B65C") /*gvi*/
#undef S_0057B65C /*gvi*/
extern int32_t S_0057B65C;
#pragma pop_macro("S_0057B65C") /*gvi*/
#endif
#define S_005FEA30 GAME_VAR(int32_t, S_005FEA30, 0x005fea30)
#ifndef RE_HOOK_BUILD
#pragma push_macro("S_005FEA30") /*gvi*/
#undef S_005FEA30 /*gvi*/
extern int32_t S_005FEA30;
#pragma pop_macro("S_005FEA30") /*gvi*/
#endif
#define S_005FEA8C GAME_VAR(int32_t, S_005FEA8C, 0x005fea8c)
#ifndef RE_HOOK_BUILD
#pragma push_macro("S_005FEA8C") /*gvi*/
#undef S_005FEA8C /*gvi*/
extern int32_t S_005FEA8C;
#pragma pop_macro("S_005FEA8C") /*gvi*/
#endif
#define S_00A421D8 GAME_VAR(uint32_t, S_00A421D8, 0x00a421d8)
#ifndef RE_HOOK_BUILD
#pragma push_macro("S_00A421D8") /*gvi*/
#undef S_00A421D8 /*gvi*/
extern uint32_t S_00A421D8;
#pragma pop_macro("S_00A421D8") /*gvi*/
#endif
#define S_00B31E40 GAME_VAR(uint8_t, S_00B31E40, 0x00b31e40)
#ifndef RE_HOOK_BUILD
#pragma push_macro("S_00B31E40") /*gvi*/
#undef S_00B31E40 /*gvi*/
extern uint8_t S_00B31E40;
#pragma pop_macro("S_00B31E40") /*gvi*/
#endif
#define S_00B31E41 GAME_VAR(uint8_t, S_00B31E41, 0x00b31e41)
#ifndef RE_HOOK_BUILD
#pragma push_macro("S_00B31E41") /*gvi*/
#undef S_00B31E41 /*gvi*/
extern uint8_t S_00B31E41;
#pragma pop_macro("S_00B31E41") /*gvi*/
#endif
#define S_00B31E42 GAME_VAR(uint8_t, S_00B31E42, 0x00b31e42)
#ifndef RE_HOOK_BUILD
#pragma push_macro("S_00B31E42") /*gvi*/
#undef S_00B31E42 /*gvi*/
extern uint8_t S_00B31E42;
#pragma pop_macro("S_00B31E42") /*gvi*/
#endif
#define S_00B31E43 GAME_VAR(uint8_t, S_00B31E43, 0x00b31e43)
#ifndef RE_HOOK_BUILD
#pragma push_macro("S_00B31E43") /*gvi*/
#undef S_00B31E43 /*gvi*/
extern uint8_t S_00B31E43;
#pragma pop_macro("S_00B31E43") /*gvi*/
#endif
#define S_00B5A76C GAME_VAR(int32_t, S_00B5A76C, 0x00b5a76c)
#ifndef RE_HOOK_BUILD
#pragma push_macro("S_00B5A76C") /*gvi*/
#undef S_00B5A76C /*gvi*/
extern int32_t S_00B5A76C;
#pragma pop_macro("S_00B5A76C") /*gvi*/
#endif
#define S_00B5A770 GAME_VAR(int32_t, S_00B5A770, 0x00b5a770)
#ifndef RE_HOOK_BUILD
#pragma push_macro("S_00B5A770") /*gvi*/
#undef S_00B5A770 /*gvi*/
extern int32_t S_00B5A770;
#pragma pop_macro("S_00B5A770") /*gvi*/
#endif
#define S_00B5A77C GAME_VAR(int32_t, S_00B5A77C, 0x00b5a77c)
#ifndef RE_HOOK_BUILD
#pragma push_macro("S_00B5A77C") /*gvi*/
#undef S_00B5A77C /*gvi*/
extern int32_t S_00B5A77C;
#pragma pop_macro("S_00B5A77C") /*gvi*/
#endif
#define S_00B5A834 GAME_VAR(uint8_t, S_00B5A834, 0x00b5a834)
#ifndef RE_HOOK_BUILD
#pragma push_macro("S_00B5A834") /*gvi*/
#undef S_00B5A834 /*gvi*/
extern uint8_t S_00B5A834;
#pragma pop_macro("S_00B5A834") /*gvi*/
#endif
#define S_00B5A835 GAME_VAR(uint8_t, S_00B5A835, 0x00b5a835)
#ifndef RE_HOOK_BUILD
#pragma push_macro("S_00B5A835") /*gvi*/
#undef S_00B5A835 /*gvi*/
extern uint8_t S_00B5A835;
#pragma pop_macro("S_00B5A835") /*gvi*/
#endif
#define S_00B5A836 GAME_VAR(uint8_t, S_00B5A836, 0x00b5a836)
#ifndef RE_HOOK_BUILD
#pragma push_macro("S_00B5A836") /*gvi*/
#undef S_00B5A836 /*gvi*/
extern uint8_t S_00B5A836;
#pragma pop_macro("S_00B5A836") /*gvi*/
#endif
#define S_00B93E6C GAME_VAR(uint32_t, S_00B93E6C, 0x00b93e6c)
#ifndef RE_HOOK_BUILD
#pragma push_macro("S_00B93E6C") /*gvi*/
#undef S_00B93E6C /*gvi*/
extern uint32_t S_00B93E6C;
#pragma pop_macro("S_00B93E6C") /*gvi*/
#endif
#define S_00B93E70 GAME_VAR(uint32_t, S_00B93E70, 0x00b93e70)
#ifndef RE_HOOK_BUILD
#pragma push_macro("S_00B93E70") /*gvi*/
#undef S_00B93E70 /*gvi*/
extern uint32_t S_00B93E70;
#pragma pop_macro("S_00B93E70") /*gvi*/
#endif
#define S_00B93E74 GAME_VAR(uint32_t, S_00B93E74, 0x00b93e74)
#ifndef RE_HOOK_BUILD
#pragma push_macro("S_00B93E74") /*gvi*/
#undef S_00B93E74 /*gvi*/
extern uint32_t S_00B93E74;
#pragma pop_macro("S_00B93E74") /*gvi*/
#endif
#define S_00BA5280 GAME_VAR(uint32_t, S_00BA5280, 0x00ba5280)
#ifndef RE_HOOK_BUILD
#pragma push_macro("S_00BA5280") /*gvi*/
#undef S_00BA5280 /*gvi*/
extern uint32_t S_00BA5280;
#pragma pop_macro("S_00BA5280") /*gvi*/
#endif
#define S_00BA52D4 GAME_VAR(uint32_t, S_00BA52D4, 0x00ba52d4)
#ifndef RE_HOOK_BUILD
#pragma push_macro("S_00BA52D4") /*gvi*/
#undef S_00BA52D4 /*gvi*/
extern uint32_t S_00BA52D4;
#pragma pop_macro("S_00BA52D4") /*gvi*/
#endif
#define S_00BA5380 GAME_VAR(uint32_t, S_00BA5380, 0x00ba5380)
#ifndef RE_HOOK_BUILD
#pragma push_macro("S_00BA5380") /*gvi*/
#undef S_00BA5380 /*gvi*/
extern uint32_t S_00BA5380;
#pragma pop_macro("S_00BA5380") /*gvi*/
#endif
#define S_00BDC2A0 GAME_VAR(sf_bytes_t, S_00BDC2A0, 0x00bdc2a0)
#ifndef RE_HOOK_BUILD
#pragma push_macro("S_00BDC2A0") /*gvi*/
#undef S_00BDC2A0 /*gvi*/
extern sf_bytes_t S_00BDC2A0;
#pragma pop_macro("S_00BDC2A0") /*gvi*/
#endif
#define S_00BDC2A1 GAME_VAR(sf_bytes_t, S_00BDC2A1, 0x00bdc2a1)
#ifndef RE_HOOK_BUILD
#pragma push_macro("S_00BDC2A1") /*gvi*/
#undef S_00BDC2A1 /*gvi*/
extern sf_bytes_t S_00BDC2A1;
#pragma pop_macro("S_00BDC2A1") /*gvi*/
#endif
#define S_00BDCD00 GAME_VAR(sf_ints_t, S_00BDCD00, 0x00bdcd00)
#ifndef RE_HOOK_BUILD
#pragma push_macro("S_00BDCD00") /*gvi*/
#undef S_00BDCD00 /*gvi*/
extern sf_ints_t S_00BDCD00;
#pragma pop_macro("S_00BDCD00") /*gvi*/
#endif
#define S_00C808A0 GAME_VAR(int32_t, S_00C808A0, 0x00c808a0)
#ifndef RE_HOOK_BUILD
#pragma push_macro("S_00C808A0") /*gvi*/
#undef S_00C808A0 /*gvi*/
extern int32_t S_00C808A0;
#pragma pop_macro("S_00C808A0") /*gvi*/
#endif
#define S_00D0CC60 GAME_VAR(sf_bytes_t, S_00D0CC60, 0x00d0cc60)
#ifndef RE_HOOK_BUILD
#pragma push_macro("S_00D0CC60") /*gvi*/
#undef S_00D0CC60 /*gvi*/
extern sf_bytes_t S_00D0CC60;
#pragma pop_macro("S_00D0CC60") /*gvi*/
#endif
#define S_00D0DDE0 GAME_VAR(int32_t, S_00D0DDE0, 0x00d0dde0)
#ifndef RE_HOOK_BUILD
#pragma push_macro("S_00D0DDE0") /*gvi*/
#undef S_00D0DDE0 /*gvi*/
extern int32_t S_00D0DDE0;
#pragma pop_macro("S_00D0DDE0") /*gvi*/
#endif
#define S_00D11804 GAME_VAR(int32_t, S_00D11804, 0x00d11804)
#ifndef RE_HOOK_BUILD
#pragma push_macro("S_00D11804") /*gvi*/
#undef S_00D11804 /*gvi*/
extern int32_t S_00D11804;
#pragma pop_macro("S_00D11804") /*gvi*/
#endif
#define S_00D11878 GAME_VAR(int32_t, S_00D11878, 0x00d11878)
#ifndef RE_HOOK_BUILD
#pragma push_macro("S_00D11878") /*gvi*/
#undef S_00D11878 /*gvi*/
extern int32_t S_00D11878;
#pragma pop_macro("S_00D11878") /*gvi*/
#endif
#define S_00D1192C GAME_VAR(int32_t, S_00D1192C, 0x00d1192c)
#ifndef RE_HOOK_BUILD
#pragma push_macro("S_00D1192C") /*gvi*/
#undef S_00D1192C /*gvi*/
extern int32_t S_00D1192C;
#pragma pop_macro("S_00D1192C") /*gvi*/
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
#pragma push_macro("S_00D12414") /*gvi*/
#undef S_00D12414 /*gvi*/
extern int32_t S_00D12414;
#pragma pop_macro("S_00D12414") /*gvi*/
#endif
#define S_010EA8A0 GAME_VAR(sf_bytes_t, S_010EA8A0, 0x010ea8a0)
#ifndef RE_HOOK_BUILD
#pragma push_macro("S_010EA8A0") /*gvi*/
#undef S_010EA8A0 /*gvi*/
extern sf_bytes_t S_010EA8A0;
#pragma pop_macro("S_010EA8A0") /*gvi*/
#endif
#define S_010FAF40 GAME_VAR(sf_bytes_t, S_010FAF40, 0x010faf40)
#ifndef RE_HOOK_BUILD
#pragma push_macro("S_010FAF40") /*gvi*/
#undef S_010FAF40 /*gvi*/
extern sf_bytes_t S_010FAF40;
#pragma pop_macro("S_010FAF40") /*gvi*/
#endif
#define S_010FB0E0 GAME_VAR(sf_bytes_t, S_010FB0E0, 0x010fb0e0)
#ifndef RE_HOOK_BUILD
#pragma push_macro("S_010FB0E0") /*gvi*/
#undef S_010FB0E0 /*gvi*/
extern sf_bytes_t S_010FB0E0;
#pragma pop_macro("S_010FB0E0") /*gvi*/
#endif
#define S_010FFA24 GAME_VAR(int32_t, S_010FFA24, 0x010ffa24)
#ifndef RE_HOOK_BUILD
#pragma push_macro("S_010FFA24") /*gvi*/
#undef S_010FFA24 /*gvi*/
extern int32_t S_010FFA24;
#pragma pop_macro("S_010FFA24") /*gvi*/
#endif
#define S_0110E144 GAME_VAR(int32_t, S_0110E144, 0x0110e144)
#ifndef RE_HOOK_BUILD
#pragma push_macro("S_0110E144") /*gvi*/
#undef S_0110E144 /*gvi*/
extern int32_t S_0110E144;
#pragma pop_macro("S_0110E144") /*gvi*/
#endif
#define S_011173C8 GAME_VAR(int32_t, S_011173C8, 0x011173c8)
#ifndef RE_HOOK_BUILD
#pragma push_macro("S_011173C8") /*gvi*/
#undef S_011173C8 /*gvi*/
extern int32_t S_011173C8;
#pragma pop_macro("S_011173C8") /*gvi*/
#endif
#define S_01136C74 GAME_VAR(int32_t, S_01136C74, 0x01136c74)
#ifndef RE_HOOK_BUILD
#pragma push_macro("S_01136C74") /*gvi*/
#undef S_01136C74 /*gvi*/
extern int32_t S_01136C74;
#pragma pop_macro("S_01136C74") /*gvi*/
#endif
#define S_01139A34 GAME_VAR(int32_t, S_01139A34, 0x01139a34)
#ifndef RE_HOOK_BUILD
#pragma push_macro("S_01139A34") /*gvi*/
#undef S_01139A34 /*gvi*/
extern int32_t S_01139A34;
#pragma pop_macro("S_01139A34") /*gvi*/
#endif
#define S_011443EA GAME_VAR(sf_bytes_t, S_011443EA, 0x011443ea)
#ifndef RE_HOOK_BUILD
#pragma push_macro("S_011443EA") /*gvi*/
#undef S_011443EA /*gvi*/
extern sf_bytes_t S_011443EA;
#pragma pop_macro("S_011443EA") /*gvi*/
#endif
#define S_0127104C GAME_VAR(uint32_t, S_0127104C, 0x0127104c)
#ifndef RE_HOOK_BUILD
#pragma push_macro("S_0127104C") /*gvi*/
#undef S_0127104C /*gvi*/
extern uint32_t S_0127104C;
#pragma pop_macro("S_0127104C") /*gvi*/
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
/* gvar-img v2.03 begin (tools/gen_gvar_img.py) */
#if !defined(RE_HOOK_BUILD) && !defined(RE_GVAR_PLAIN)
#undef S_00549B04
#define S_00549B04 (*(sf_bytes_t *)re_gvar(0x00549b04u, sizeof(sf_bytes_t), (void *)&S_00549B04))
#undef S_0054E44C
#define S_0054E44C (*(sf_bytes_t *)re_gvar(0x0054e44cu, sizeof(sf_bytes_t), (void *)&S_0054E44C))
#undef S_0054E44D
#define S_0054E44D (*(sf_bytes_t *)re_gvar(0x0054e44du, sizeof(sf_bytes_t), (void *)&S_0054E44D))
#undef S_0054E44E
#define S_0054E44E (*(sf_bytes_t *)re_gvar(0x0054e44eu, sizeof(sf_bytes_t), (void *)&S_0054E44E))
#undef S_0054E6AC
#define S_0054E6AC (*(sf_bytes_t *)re_gvar(0x0054e6acu, sizeof(sf_bytes_t), (void *)&S_0054E6AC))
#undef S_0054E6AD
#define S_0054E6AD (*(sf_bytes_t *)re_gvar(0x0054e6adu, sizeof(sf_bytes_t), (void *)&S_0054E6AD))
#undef S_0054E6AE
#define S_0054E6AE (*(sf_bytes_t *)re_gvar(0x0054e6aeu, sizeof(sf_bytes_t), (void *)&S_0054E6AE))
#undef S_00560A88
#define S_00560A88 (*(sf_bytes_t *)re_gvar(0x00560a88u, sizeof(sf_bytes_t), (void *)&S_00560A88))
#undef S_0057B658
#define S_0057B658 (*(int32_t *)re_gvar(0x0057b658u, sizeof(int32_t), (void *)&S_0057B658))
#undef S_0057B65C
#define S_0057B65C (*(int32_t *)re_gvar(0x0057b65cu, sizeof(int32_t), (void *)&S_0057B65C))
#undef S_005FEA30
#define S_005FEA30 (*(int32_t *)re_gvar(0x005fea30u, sizeof(int32_t), (void *)&S_005FEA30))
#undef S_005FEA8C
#define S_005FEA8C (*(int32_t *)re_gvar(0x005fea8cu, sizeof(int32_t), (void *)&S_005FEA8C))
#undef S_00A421D8
#define S_00A421D8 (*(uint32_t *)re_gvar(0x00a421d8u, sizeof(uint32_t), (void *)&S_00A421D8))
#undef S_00B31E40
#define S_00B31E40 (*(uint8_t *)re_gvar(0x00b31e40u, sizeof(uint8_t), (void *)&S_00B31E40))
#undef S_00B31E41
#define S_00B31E41 (*(uint8_t *)re_gvar(0x00b31e41u, sizeof(uint8_t), (void *)&S_00B31E41))
#undef S_00B31E42
#define S_00B31E42 (*(uint8_t *)re_gvar(0x00b31e42u, sizeof(uint8_t), (void *)&S_00B31E42))
#undef S_00B31E43
#define S_00B31E43 (*(uint8_t *)re_gvar(0x00b31e43u, sizeof(uint8_t), (void *)&S_00B31E43))
#undef S_00B5A76C
#define S_00B5A76C (*(int32_t *)re_gvar(0x00b5a76cu, sizeof(int32_t), (void *)&S_00B5A76C))
#undef S_00B5A770
#define S_00B5A770 (*(int32_t *)re_gvar(0x00b5a770u, sizeof(int32_t), (void *)&S_00B5A770))
#undef S_00B5A77C
#define S_00B5A77C (*(int32_t *)re_gvar(0x00b5a77cu, sizeof(int32_t), (void *)&S_00B5A77C))
#undef S_00B5A834
#define S_00B5A834 (*(uint8_t *)re_gvar(0x00b5a834u, sizeof(uint8_t), (void *)&S_00B5A834))
#undef S_00B5A835
#define S_00B5A835 (*(uint8_t *)re_gvar(0x00b5a835u, sizeof(uint8_t), (void *)&S_00B5A835))
#undef S_00B5A836
#define S_00B5A836 (*(uint8_t *)re_gvar(0x00b5a836u, sizeof(uint8_t), (void *)&S_00B5A836))
#undef S_00B93E6C
#define S_00B93E6C (*(uint32_t *)re_gvar(0x00b93e6cu, sizeof(uint32_t), (void *)&S_00B93E6C))
#undef S_00B93E70
#define S_00B93E70 (*(uint32_t *)re_gvar(0x00b93e70u, sizeof(uint32_t), (void *)&S_00B93E70))
#undef S_00B93E74
#define S_00B93E74 (*(uint32_t *)re_gvar(0x00b93e74u, sizeof(uint32_t), (void *)&S_00B93E74))
#undef S_00BA5280
#define S_00BA5280 (*(uint32_t *)re_gvar(0x00ba5280u, sizeof(uint32_t), (void *)&S_00BA5280))
#undef S_00BA52D4
#define S_00BA52D4 (*(uint32_t *)re_gvar(0x00ba52d4u, sizeof(uint32_t), (void *)&S_00BA52D4))
#undef S_00BA5380
#define S_00BA5380 (*(uint32_t *)re_gvar(0x00ba5380u, sizeof(uint32_t), (void *)&S_00BA5380))
#undef S_00BDC2A0
#define S_00BDC2A0 (*(sf_bytes_t *)re_gvar(0x00bdc2a0u, sizeof(sf_bytes_t), (void *)&S_00BDC2A0))
#undef S_00BDC2A1
#define S_00BDC2A1 (*(sf_bytes_t *)re_gvar(0x00bdc2a1u, sizeof(sf_bytes_t), (void *)&S_00BDC2A1))
#undef S_00BDCD00
#define S_00BDCD00 (*(sf_ints_t *)re_gvar(0x00bdcd00u, sizeof(sf_ints_t), (void *)&S_00BDCD00))
#undef S_00C808A0
#define S_00C808A0 (*(int32_t *)re_gvar(0x00c808a0u, sizeof(int32_t), (void *)&S_00C808A0))
#undef S_00D0CC60
#define S_00D0CC60 (*(sf_bytes_t *)re_gvar(0x00d0cc60u, sizeof(sf_bytes_t), (void *)&S_00D0CC60))
#undef S_00D0DDE0
#define S_00D0DDE0 (*(int32_t *)re_gvar(0x00d0dde0u, sizeof(int32_t), (void *)&S_00D0DDE0))
#undef S_00D11804
#define S_00D11804 (*(int32_t *)re_gvar(0x00d11804u, sizeof(int32_t), (void *)&S_00D11804))
#undef S_00D11878
#define S_00D11878 (*(int32_t *)re_gvar(0x00d11878u, sizeof(int32_t), (void *)&S_00D11878))
#undef S_00D1192C
#define S_00D1192C (*(int32_t *)re_gvar(0x00d1192cu, sizeof(int32_t), (void *)&S_00D1192C))
#undef S_00D12414
#define S_00D12414 (*(int32_t *)re_gvar(0x00d12414u, sizeof(int32_t), (void *)&S_00D12414))
#undef S_010EA8A0
#define S_010EA8A0 (*(sf_bytes_t *)re_gvar(0x010ea8a0u, sizeof(sf_bytes_t), (void *)&S_010EA8A0))
#undef S_010FAF40
#define S_010FAF40 (*(sf_bytes_t *)re_gvar(0x010faf40u, sizeof(sf_bytes_t), (void *)&S_010FAF40))
#undef S_010FB0E0
#define S_010FB0E0 (*(sf_bytes_t *)re_gvar(0x010fb0e0u, sizeof(sf_bytes_t), (void *)&S_010FB0E0))
#undef S_010FFA24
#define S_010FFA24 (*(int32_t *)re_gvar(0x010ffa24u, sizeof(int32_t), (void *)&S_010FFA24))
#undef S_0110E144
#define S_0110E144 (*(int32_t *)re_gvar(0x0110e144u, sizeof(int32_t), (void *)&S_0110E144))
#undef S_011173C8
#define S_011173C8 (*(int32_t *)re_gvar(0x011173c8u, sizeof(int32_t), (void *)&S_011173C8))
#undef S_01136C74
#define S_01136C74 (*(int32_t *)re_gvar(0x01136c74u, sizeof(int32_t), (void *)&S_01136C74))
#undef S_01139A34
#define S_01139A34 (*(int32_t *)re_gvar(0x01139a34u, sizeof(int32_t), (void *)&S_01139A34))
#undef S_011443EA
#define S_011443EA (*(sf_bytes_t *)re_gvar(0x011443eau, sizeof(sf_bytes_t), (void *)&S_011443EA))
#undef S_0127104C
#define S_0127104C (*(uint32_t *)re_gvar(0x0127104cu, sizeof(uint32_t), (void *)&S_0127104C))
#endif
/* gvar-img v2.03 end */
