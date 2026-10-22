/* Простые функции (сеттеры, переключатели, обёртки). */
#pragma once
#include "gvar.h"
#include "unported.h"
#include "uihandlers2.h"
#include "noop.h"
typedef void (*FnVoidI)(int32_t);
typedef void (*FnVoidV)(void);
typedef int32_t (*FnIntI)(int32_t);
typedef int32_t (*FnIntII)(int32_t, int32_t);
#define G00575F24 GAME_VAR(int32_t, G00575F24, 0x00575f24)
#ifndef RE_HOOK_BUILD
#pragma push_macro("G00575F24") /*gvi*/
#undef G00575F24 /*gvi*/
extern int32_t G00575F24;
#pragma pop_macro("G00575F24") /*gvi*/
#endif
#define G00575F48 GAME_VAR(int32_t, G00575F48, 0x00575f48)
#ifndef RE_HOOK_BUILD
#pragma push_macro("G00575F48") /*gvi*/
#undef G00575F48 /*gvi*/
extern int32_t G00575F48;
#pragma pop_macro("G00575F48") /*gvi*/
#endif
#define G00575F40 GAME_VAR(int32_t, G00575F40, 0x00575f40)
#ifndef RE_HOOK_BUILD
#pragma push_macro("G00575F40") /*gvi*/
#undef G00575F40 /*gvi*/
extern int32_t G00575F40;
#pragma pop_macro("G00575F40") /*gvi*/
#endif
#define UiPtr005FE9B8 GAME_VAR(uint8_t *, UiPtr005FE9B8, 0x005fe9b8)
#ifndef RE_HOOK_BUILD
extern uint8_t * UiPtr005FE9B8;
#endif
#define G005FEA54 GAME_VAR(int32_t, G005FEA54, 0x005fea54)
#ifndef RE_HOOK_BUILD
#pragma push_macro("G005FEA54") /*gvi*/
#undef G005FEA54 /*gvi*/
extern int32_t G005FEA54;
#pragma pop_macro("G005FEA54") /*gvi*/
#endif
#define G005FEA5C GAME_VAR(int32_t, G005FEA5C, 0x005fea5c)
#ifndef RE_HOOK_BUILD
#pragma push_macro("G005FEA5C") /*gvi*/
#undef G005FEA5C /*gvi*/
extern int32_t G005FEA5C;
#pragma pop_macro("G005FEA5C") /*gvi*/
#endif
#define G005FEA60 GAME_VAR(int32_t, G005FEA60, 0x005fea60)
#ifndef RE_HOOK_BUILD
#pragma push_macro("G005FEA60") /*gvi*/
#undef G005FEA60 /*gvi*/
extern int32_t G005FEA60;
#pragma pop_macro("G005FEA60") /*gvi*/
#endif
#define G0054E540 GAME_VAR(int32_t, G0054E540, 0x0054e540)
#ifndef RE_HOOK_BUILD
#pragma push_macro("G0054E540") /*gvi*/
#undef G0054E540 /*gvi*/
extern int32_t G0054E540;
#pragma pop_macro("G0054E540") /*gvi*/
#endif
#define FnPtr01270E80 GAME_VAR(FnVoidI, FnPtr01270E80, 0x01270e80)
#ifndef RE_HOOK_BUILD
extern FnVoidI FnPtr01270E80;
#endif
#define G005FEB00 GAME_VAR(int32_t, G005FEB00, 0x005feb00)
#ifndef RE_HOOK_BUILD
#pragma push_macro("G005FEB00") /*gvi*/
#undef G005FEB00 /*gvi*/
extern int32_t G005FEB00;
#pragma pop_macro("G005FEB00") /*gvi*/
#endif
#define G005FEEEC GAME_VAR(int32_t, G005FEEEC, 0x005feeec)
#ifndef RE_HOOK_BUILD
#pragma push_macro("G005FEEEC") /*gvi*/
#undef G005FEEEC /*gvi*/
extern int32_t G005FEEEC;
#pragma pop_macro("G005FEEEC") /*gvi*/
#endif
#define G0127104C GAME_VAR(uint32_t, G0127104C, 0x0127104c)
#ifndef RE_HOOK_BUILD
#pragma push_macro("G0127104C") /*gvi*/
#undef G0127104C /*gvi*/
extern uint32_t G0127104C;
#pragma pop_macro("G0127104C") /*gvi*/
#endif
#define G0054EF38 GAME_VAR(float, G0054EF38, 0x0054ef38)
#ifndef RE_HOOK_BUILD
#pragma push_macro("G0054EF38") /*gvi*/
#undef G0054EF38 /*gvi*/
extern float G0054EF38;
#pragma pop_macro("G0054EF38") /*gvi*/
#endif
#define G0054EF3C GAME_VAR(float, G0054EF3C, 0x0054ef3c)
#ifndef RE_HOOK_BUILD
#pragma push_macro("G0054EF3C") /*gvi*/
#undef G0054EF3C /*gvi*/
extern float G0054EF3C;
#pragma pop_macro("G0054EF3C") /*gvi*/
#endif
#define G0054603C GAME_VAR(float, G0054603C, 0x0054603c)
#ifndef RE_HOOK_BUILD
#pragma push_macro("G0054603C") /*gvi*/
#undef G0054603C /*gvi*/
extern float G0054603C;
#pragma pop_macro("G0054603C") /*gvi*/
#endif
#define G00A421A8 GAME_VAR(int32_t, G00A421A8, 0x00a421a8)
#ifndef RE_HOOK_BUILD
#pragma push_macro("G00A421A8") /*gvi*/
#undef G00A421A8 /*gvi*/
extern int32_t G00A421A8;
#pragma pop_macro("G00A421A8") /*gvi*/
#endif
#define G00A421A4 GAME_VAR(int32_t, G00A421A4, 0x00a421a4)
#ifndef RE_HOOK_BUILD
#pragma push_macro("G00A421A4") /*gvi*/
#undef G00A421A4 /*gvi*/
extern int32_t G00A421A4;
#pragma pop_macro("G00A421A4") /*gvi*/
#endif
#define G00B1C0D8 GAME_VAR(int32_t, G00B1C0D8, 0x00b1c0d8)
#ifndef RE_HOOK_BUILD
#pragma push_macro("G00B1C0D8") /*gvi*/
#undef G00B1C0D8 /*gvi*/
extern int32_t G00B1C0D8;
#pragma pop_macro("G00B1C0D8") /*gvi*/
#endif
#define G00B1C0D4 GAME_VAR(int32_t, G00B1C0D4, 0x00b1c0d4)
#ifndef RE_HOOK_BUILD
#pragma push_macro("G00B1C0D4") /*gvi*/
#undef G00B1C0D4 /*gvi*/
extern int32_t G00B1C0D4;
#pragma pop_macro("G00B1C0D4") /*gvi*/
#endif
#define FnPtr01270E54 GAME_VAR(FnVoidV, FnPtr01270E54, 0x01270e54)
#ifndef RE_HOOK_BUILD
extern FnVoidV FnPtr01270E54;
#endif
#define FnPtr01271020 GAME_VAR(FnVoidV, FnPtr01271020, 0x01271020)
#ifndef RE_HOOK_BUILD
extern FnVoidV FnPtr01271020;
#endif
#define FnPtr01270EB0 GAME_VAR(FnVoidV, FnPtr01270EB0, 0x01270eb0)
#ifndef RE_HOOK_BUILD
extern FnVoidV FnPtr01270EB0;
#endif
#define FnPtr01270E50 GAME_VAR(FnIntI, FnPtr01270E50, 0x01270e50)
#ifndef RE_HOOK_BUILD
extern FnIntI FnPtr01270E50;
#endif
#define FnPtr01270EAC GAME_VAR(FnIntII, FnPtr01270EAC, 0x01270eac)
#ifndef RE_HOOK_BUILD
extern FnIntII FnPtr01270EAC;
#endif
#define G012085F4 GAME_VAR(uint32_t, G012085F4, 0x012085f4)
#ifndef RE_HOOK_BUILD
#pragma push_macro("G012085F4") /*gvi*/
#undef G012085F4 /*gvi*/
extern uint32_t G012085F4;
#pragma pop_macro("G012085F4") /*gvi*/
#endif
#define G00550808 GAME_VAR(uint8_t, G00550808, 0x00550808)
#ifndef RE_HOOK_BUILD
#pragma push_macro("G00550808") /*gvi*/
#undef G00550808 /*gvi*/
extern uint8_t G00550808;
#pragma pop_macro("G00550808") /*gvi*/
#endif
#define G01159D74 GAME_VAR(int32_t, G01159D74, 0x01159d74)
#ifndef RE_HOOK_BUILD
#pragma push_macro("G01159D74") /*gvi*/
#undef G01159D74 /*gvi*/
extern int32_t G01159D74;
#pragma pop_macro("G01159D74") /*gvi*/
#endif
#define G0115A13C GAME_VAR(uint8_t *, G0115A13C, 0x0115a13c)
#ifndef RE_HOOK_BUILD
extern uint8_t * G0115A13C;
#endif
/* v1.95: очередь отложенных треугольников Glide 0115a140..011b6140 (записи 0xb8: тег + 3 вершины по 0x3c; 0042d2c9/0042d384);
   раньше в native был 1 байт — запись очереди выходила за переменную */
typedef uint8_t g0115a140_t[0x5c000];
#define G0115A140 GAME_VAR(g0115a140_t, G0115A140, 0x0115a140)
#ifndef RE_HOOK_BUILD
#pragma push_macro("G0115A140") /*gvi*/
#undef G0115A140 /*gvi*/
extern g0115a140_t G0115A140;
#pragma pop_macro("G0115A140") /*gvi*/
#endif
#define G00551134 GAME_VAR(int32_t, G00551134, 0x00551134)
#ifndef RE_HOOK_BUILD
#pragma push_macro("G00551134") /*gvi*/
#undef G00551134 /*gvi*/
extern int32_t G00551134;
#pragma pop_macro("G00551134") /*gvi*/
#endif
#define G01145934 GAME_VAR(int32_t, G01145934, 0x01145934)
#ifndef RE_HOOK_BUILD
#pragma push_macro("G01145934") /*gvi*/
#undef G01145934 /*gvi*/
extern int32_t G01145934;
#pragma pop_macro("G01145934") /*gvi*/
#endif
#define G0113A6C4 GAME_VAR(uint8_t *, G0113A6C4, 0x0113a6c4)
#ifndef RE_HOOK_BUILD
extern uint8_t * G0113A6C4;
#endif
#define G0112B284 GAME_VAR(int32_t, G0112B284, 0x0112b284)
#ifndef RE_HOOK_BUILD
#pragma push_macro("G0112B284") /*gvi*/
#undef G0112B284 /*gvi*/
extern int32_t G0112B284;
#pragma pop_macro("G0112B284") /*gvi*/
#endif
#define G00B1FFBC GAME_VAR(int32_t, G00B1FFBC, 0x00b1ffbc)
#ifndef RE_HOOK_BUILD
#pragma push_macro("G00B1FFBC") /*gvi*/
#undef G00B1FFBC /*gvi*/
extern int32_t G00B1FFBC;
#pragma pop_macro("G00B1FFBC") /*gvi*/
#endif
#define G0110E180 GAME_VAR(int32_t, G0110E180, 0x0110e180)
#ifndef RE_HOOK_BUILD
#pragma push_macro("G0110E180") /*gvi*/
#undef G0110E180 /*gvi*/
extern int32_t G0110E180;
#pragma pop_macro("G0110E180") /*gvi*/
#endif
#define G00B87E7C GAME_VAR(int32_t, G00B87E7C, 0x00b87e7c)
#ifndef RE_HOOK_BUILD
#pragma push_macro("G00B87E7C") /*gvi*/
#undef G00B87E7C /*gvi*/
extern int32_t G00B87E7C;
#pragma pop_macro("G00B87E7C") /*gvi*/
#endif
#define G00575F08 GAME_VAR(int32_t, G00575F08, 0x00575f08)
#ifndef RE_HOOK_BUILD
#pragma push_macro("G00575F08") /*gvi*/
#undef G00575F08 /*gvi*/
extern int32_t G00575F08;
#pragma pop_macro("G00575F08") /*gvi*/
#endif
#define G00560388 GAME_VAR(int32_t, G00560388, 0x00560388)
#ifndef RE_HOOK_BUILD
#pragma push_macro("G00560388") /*gvi*/
#undef G00560388 /*gvi*/
extern int32_t G00560388;
#pragma pop_macro("G00560388") /*gvi*/
#endif
#define G00B2C3B8 GAME_VAR(int32_t, G00B2C3B8, 0x00b2c3b8)
#ifndef RE_HOOK_BUILD
#pragma push_macro("G00B2C3B8") /*gvi*/
#undef G00B2C3B8 /*gvi*/
extern int32_t G00B2C3B8;
#pragma pop_macro("G00B2C3B8") /*gvi*/
#endif
#define G00D11804 GAME_VAR(int32_t, G00D11804, 0x00d11804)
#ifndef RE_HOOK_BUILD
#pragma push_macro("G00D11804") /*gvi*/
#undef G00D11804 /*gvi*/
extern int32_t G00D11804;
#pragma pop_macro("G00D11804") /*gvi*/
#endif
#define G00BDF984 GAME_VAR(int32_t, G00BDF984, 0x00bdf984)
#ifndef RE_HOOK_BUILD
#pragma push_macro("G00BDF984") /*gvi*/
#undef G00BDF984 /*gvi*/
extern int32_t G00BDF984;
#pragma pop_macro("G00BDF984") /*gvi*/
#endif
#define G00D078F8 CARTAB_VAR(int32_t, G00D078F8, 0x00d078f8)
#ifndef RE_HOOK_BUILD

#endif
#define G00B31E18 GAME_VAR(int32_t, G00B31E18, 0x00b31e18)
#ifndef RE_HOOK_BUILD
#pragma push_macro("G00B31E18") /*gvi*/
#undef G00B31E18 /*gvi*/
extern int32_t G00B31E18;
#pragma pop_macro("G00B31E18") /*gvi*/
#endif
#define G00B31E00 GAME_VAR(int32_t, G00B31E00, 0x00b31e00)
#ifndef RE_HOOK_BUILD
#pragma push_macro("G00B31E00") /*gvi*/
#undef G00B31E00 /*gvi*/
extern int32_t G00B31E00;
#pragma pop_macro("G00B31E00") /*gvi*/
#endif
#define G00B31E0C GAME_VAR(int32_t, G00B31E0C, 0x00b31e0c)
#ifndef RE_HOOK_BUILD
#pragma push_macro("G00B31E0C") /*gvi*/
#undef G00B31E0C /*gvi*/
extern int32_t G00B31E0C;
#pragma pop_macro("G00B31E0C") /*gvi*/
#endif
#define G00D044C8 GAME_VAR(int32_t, G00D044C8, 0x00d044c8)
#ifndef RE_HOOK_BUILD
#pragma push_macro("G00D044C8") /*gvi*/
#undef G00D044C8 /*gvi*/
extern int32_t G00D044C8;
#pragma pop_macro("G00D044C8") /*gvi*/
#endif
int32_t MenuToggle575F24Call40EA70(void); /* 0040e970 */
int32_t MenuToggle575F48Call40EA70(void); /* 0040ea57 */
int32_t MenuToggle575F24Call419B35(void); /* 00419c50 */
int32_t MenuToggle575F48Call419B35(void); /* 00419d25 */
int32_t MenuToggle575F40Call414D1F(void); /* 0041539a */
void UiSetSlot004142E8(int32_t a0); /* 004142e8 */
void UiSetSlot004143FA(int32_t a0); /* 004143fa */
void UiSetSlot0041450C(int32_t a0); /* 0041450c */
void UiSetSlot00414621(int32_t a0); /* 00414621 */
void Ui00418119(int32_t a0); /* 00418119 */
void Ui004184DE(int32_t a0); /* 004184de */
void Ui004197F8(void); /* 004197f8 */
void Ui0041A1EC(int32_t a0); /* 0041a1ec */
void UiSetMode005FEEEC_0(void); /* 0041ae2f */
void UiSetMode005FEEEC_1(void); /* 0041ae43 */
void UiSetMode005FEEEC_2(void); /* 0041ae57 */
void UiSetMode005FEEEC_3(void); /* 0041ae6b */
void UiSetMode005FEEEC_4(void); /* 0041ae7f */
void UiSetMode005FEEEC_5(void); /* 0041ae93 */
void UiSetMode005FEEEC_6(void); /* 0041aea7 */
void UiSetMode005FEEEC_7(void); /* 0041aebb */
void Ui0041B059(void); /* 0041b059 */
void FlagSet0127104C(uint8_t bit); /* 0041b790 */
void SetScale54EF38(float v); /* 0041d8cd */
void Ui0041ED53(int32_t a0); /* 0041ed53 */
int32_t GetVarA421A8(void); /* 0041ed68 */
int32_t GetVarA421A4(void); /* 0041ed72 */
int32_t Ret1FFFF8IfZero(int32_t a0); /* 0041f734 */
uint16_t RetZero0041FA36(void); /* 0041fa36 */
int32_t GetVarB1C0D8(void); /* 004245e2 */
void Dev00424633(void); /* 00424633 */
void Dev00424647(void); /* 00424647 */
int32_t GameCall00424661(intptr_t a0); /* 00424661; v2.00: адрес GrHwConfiguration — intptr_t (64 бит native) */
void Dev004246BD(void); /* 004246bd */
int32_t Dev0042480D(int32_t a0); /* 0042480d */
void Dev00424858(void); /* 00424858 */
void Ui00426CAF(void); /* 00426caf */
void Ui00426CC6(void); /* 00426cc6 */
void Reset0042D2B0(void); /* 0042d2b0 */
void Set551134(void); /* 0048b6a9 */
int32_t Ret1(void); /* 0048ec34 */
void Dec145934(void); /* 004964c7 */
int32_t Get138Entry148(int32_t i); /* 004a1d31 */
int32_t IsVar112B284Lt8(void); /* 004a66d8 */
void Inc0B1FFBC(void); /* 004a994a */
void Clear110E180(void); /* 004ab7fa */
void Call004BF485(int32_t a0); /* 004bf485 */
void CopyWords8000(uint32_t *src, uint32_t *dst); /* 004c16c1 */
void Call004D2D85(int32_t a0); /* 004d2d85 */
void Set560388(int32_t a0); /* 004d629e */
int32_t Round1024(int32_t a0); /* 004d9013 */
void Clear2C3B8(void); /* 004d9587 */
void SetD11804(int32_t a0); /* 004d97dc */
void CopyBDF984(void); /* 004da75b */
int32_t GetB31E18(void); /* 004e3830 */
int32_t SetB31E00(int32_t a0); /* 004e3b20 */
int32_t Get138(uint8_t *p); /* 004e5f4d */
void Set0D044C8(void); /* 004e6166 */
void Call004A2C08(void); /* 004a2c08 */
void Call004BF476(void); /* 004bf476 */
void Call004C020E(void); /* 004c020e */
/* gvar-img v2.03 begin (tools/gen_gvar_img.py) */
#if !defined(RE_HOOK_BUILD) && !defined(RE_GVAR_PLAIN)
#undef G00575F24
#define G00575F24 (*(int32_t *)re_gvar(0x00575f24u, sizeof(int32_t), (void *)&G00575F24))
#undef G00575F48
#define G00575F48 (*(int32_t *)re_gvar(0x00575f48u, sizeof(int32_t), (void *)&G00575F48))
#undef G00575F40
#define G00575F40 (*(int32_t *)re_gvar(0x00575f40u, sizeof(int32_t), (void *)&G00575F40))
#undef G005FEA54
#define G005FEA54 (*(int32_t *)re_gvar(0x005fea54u, sizeof(int32_t), (void *)&G005FEA54))
#undef G005FEA5C
#define G005FEA5C (*(int32_t *)re_gvar(0x005fea5cu, sizeof(int32_t), (void *)&G005FEA5C))
#undef G005FEA60
#define G005FEA60 (*(int32_t *)re_gvar(0x005fea60u, sizeof(int32_t), (void *)&G005FEA60))
#undef G0054E540
#define G0054E540 (*(int32_t *)re_gvar(0x0054e540u, sizeof(int32_t), (void *)&G0054E540))
#undef G005FEB00
#define G005FEB00 (*(int32_t *)re_gvar(0x005feb00u, sizeof(int32_t), (void *)&G005FEB00))
#undef G005FEEEC
#define G005FEEEC (*(int32_t *)re_gvar(0x005feeecu, sizeof(int32_t), (void *)&G005FEEEC))
#undef G0127104C
#define G0127104C (*(uint32_t *)re_gvar(0x0127104cu, sizeof(uint32_t), (void *)&G0127104C))
#undef G0054EF38
#define G0054EF38 (*(float *)re_gvar(0x0054ef38u, sizeof(float), (void *)&G0054EF38))
#undef G0054EF3C
#define G0054EF3C (*(float *)re_gvar(0x0054ef3cu, sizeof(float), (void *)&G0054EF3C))
#undef G0054603C
#define G0054603C (*(float *)re_gvar(0x0054603cu, sizeof(float), (void *)&G0054603C))
#undef G00A421A8
#define G00A421A8 (*(int32_t *)re_gvar(0x00a421a8u, sizeof(int32_t), (void *)&G00A421A8))
#undef G00A421A4
#define G00A421A4 (*(int32_t *)re_gvar(0x00a421a4u, sizeof(int32_t), (void *)&G00A421A4))
#undef G00B1C0D8
#define G00B1C0D8 (*(int32_t *)re_gvar(0x00b1c0d8u, sizeof(int32_t), (void *)&G00B1C0D8))
#undef G00B1C0D4
#define G00B1C0D4 (*(int32_t *)re_gvar(0x00b1c0d4u, sizeof(int32_t), (void *)&G00B1C0D4))
#undef G012085F4
#define G012085F4 (*(uint32_t *)re_gvar(0x012085f4u, sizeof(uint32_t), (void *)&G012085F4))
#undef G00550808
#define G00550808 (*(uint8_t *)re_gvar(0x00550808u, sizeof(uint8_t), (void *)&G00550808))
#undef G01159D74
#define G01159D74 (*(int32_t *)re_gvar(0x01159d74u, sizeof(int32_t), (void *)&G01159D74))
#undef G0115A140
#define G0115A140 (*(g0115a140_t *)re_gvar(0x0115a140u, sizeof(g0115a140_t), (void *)&G0115A140))
#undef G00551134
#define G00551134 (*(int32_t *)re_gvar(0x00551134u, sizeof(int32_t), (void *)&G00551134))
#undef G01145934
#define G01145934 (*(int32_t *)re_gvar(0x01145934u, sizeof(int32_t), (void *)&G01145934))
#undef G0112B284
#define G0112B284 (*(int32_t *)re_gvar(0x0112b284u, sizeof(int32_t), (void *)&G0112B284))
#undef G00B1FFBC
#define G00B1FFBC (*(int32_t *)re_gvar(0x00b1ffbcu, sizeof(int32_t), (void *)&G00B1FFBC))
#undef G0110E180
#define G0110E180 (*(int32_t *)re_gvar(0x0110e180u, sizeof(int32_t), (void *)&G0110E180))
#undef G00B87E7C
#define G00B87E7C (*(int32_t *)re_gvar(0x00b87e7cu, sizeof(int32_t), (void *)&G00B87E7C))
#undef G00575F08
#define G00575F08 (*(int32_t *)re_gvar(0x00575f08u, sizeof(int32_t), (void *)&G00575F08))
#undef G00560388
#define G00560388 (*(int32_t *)re_gvar(0x00560388u, sizeof(int32_t), (void *)&G00560388))
#undef G00B2C3B8
#define G00B2C3B8 (*(int32_t *)re_gvar(0x00b2c3b8u, sizeof(int32_t), (void *)&G00B2C3B8))
#undef G00D11804
#define G00D11804 (*(int32_t *)re_gvar(0x00d11804u, sizeof(int32_t), (void *)&G00D11804))
#undef G00BDF984
#define G00BDF984 (*(int32_t *)re_gvar(0x00bdf984u, sizeof(int32_t), (void *)&G00BDF984))
#undef G00B31E18
#define G00B31E18 (*(int32_t *)re_gvar(0x00b31e18u, sizeof(int32_t), (void *)&G00B31E18))
#undef G00B31E00
#define G00B31E00 (*(int32_t *)re_gvar(0x00b31e00u, sizeof(int32_t), (void *)&G00B31E00))
#undef G00B31E0C
#define G00B31E0C (*(int32_t *)re_gvar(0x00b31e0cu, sizeof(int32_t), (void *)&G00B31E0C))
#undef G00D044C8
#define G00D044C8 (*(int32_t *)re_gvar(0x00d044c8u, sizeof(int32_t), (void *)&G00D044C8))
#endif
/* gvar-img v2.03 end */
/* v2.35: 005fe9b8 — one object: the data-image cell P58_S5FE9B8 (32-bit address); UiPtr005FE9B8 = P15_MenuItems, a view */
#if !defined(RE_HOOK_BUILD) && !defined(RE_GVAR_PLAIN)
#include "ported15.h"
#undef UiPtr005FE9B8
#define UiPtr005FE9B8 P15_MenuItems
#endif
/* v2.35: 0113a6c4 — one object: the car table pointer P59_CarsTab (P103 writes it); G0113A6C4 names the same native variable */
#ifndef RE_HOOK_BUILD
extern uint8_t *P59_CarsTab;
#undef G0113A6C4
#define G0113A6C4 P59_CarsTab
#endif
