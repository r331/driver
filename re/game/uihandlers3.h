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
extern int32_t G00575F24;
#endif
#define G00575F48 GAME_VAR(int32_t, G00575F48, 0x00575f48)
#ifndef RE_HOOK_BUILD
extern int32_t G00575F48;
#endif
#define G00575F40 GAME_VAR(int32_t, G00575F40, 0x00575f40)
#ifndef RE_HOOK_BUILD
extern int32_t G00575F40;
#endif
#define UiPtr005FE9B8 GAME_VAR(uint8_t *, UiPtr005FE9B8, 0x005fe9b8)
#ifndef RE_HOOK_BUILD
extern uint8_t * UiPtr005FE9B8;
#endif
#define G005FEA54 GAME_VAR(int32_t, G005FEA54, 0x005fea54)
#ifndef RE_HOOK_BUILD
extern int32_t G005FEA54;
#endif
#define G005FEA5C GAME_VAR(int32_t, G005FEA5C, 0x005fea5c)
#ifndef RE_HOOK_BUILD
extern int32_t G005FEA5C;
#endif
#define G005FEA60 GAME_VAR(int32_t, G005FEA60, 0x005fea60)
#ifndef RE_HOOK_BUILD
extern int32_t G005FEA60;
#endif
#define G0054E540 GAME_VAR(int32_t, G0054E540, 0x0054e540)
#ifndef RE_HOOK_BUILD
extern int32_t G0054E540;
#endif
#define FnPtr01270E80 GAME_VAR(FnVoidI, FnPtr01270E80, 0x01270e80)
#ifndef RE_HOOK_BUILD
extern FnVoidI FnPtr01270E80;
#endif
#define G005FEB00 GAME_VAR(int32_t, G005FEB00, 0x005feb00)
#ifndef RE_HOOK_BUILD
extern int32_t G005FEB00;
#endif
#define G005FEEEC GAME_VAR(int32_t, G005FEEEC, 0x005feeec)
#ifndef RE_HOOK_BUILD
extern int32_t G005FEEEC;
#endif
#define G0127104C GAME_VAR(uint32_t, G0127104C, 0x0127104c)
#ifndef RE_HOOK_BUILD
extern uint32_t G0127104C;
#endif
#define G0054EF38 GAME_VAR(float, G0054EF38, 0x0054ef38)
#ifndef RE_HOOK_BUILD
extern float G0054EF38;
#endif
#define G0054EF3C GAME_VAR(float, G0054EF3C, 0x0054ef3c)
#ifndef RE_HOOK_BUILD
extern float G0054EF3C;
#endif
#define G0054603C GAME_VAR(float, G0054603C, 0x0054603c)
#ifndef RE_HOOK_BUILD
extern float G0054603C;
#endif
#define G00A421A8 GAME_VAR(int32_t, G00A421A8, 0x00a421a8)
#ifndef RE_HOOK_BUILD
extern int32_t G00A421A8;
#endif
#define G00A421A4 GAME_VAR(int32_t, G00A421A4, 0x00a421a4)
#ifndef RE_HOOK_BUILD
extern int32_t G00A421A4;
#endif
#define G00B1C0D8 GAME_VAR(int32_t, G00B1C0D8, 0x00b1c0d8)
#ifndef RE_HOOK_BUILD
extern int32_t G00B1C0D8;
#endif
#define G00B1C0D4 GAME_VAR(int32_t, G00B1C0D4, 0x00b1c0d4)
#ifndef RE_HOOK_BUILD
extern int32_t G00B1C0D4;
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
extern uint32_t G012085F4;
#endif
#define G00550808 GAME_VAR(uint8_t, G00550808, 0x00550808)
#ifndef RE_HOOK_BUILD
extern uint8_t G00550808;
#endif
#define G01159D74 GAME_VAR(int32_t, G01159D74, 0x01159d74)
#ifndef RE_HOOK_BUILD
extern int32_t G01159D74;
#endif
#define G0115A13C GAME_VAR(uint8_t *, G0115A13C, 0x0115a13c)
#ifndef RE_HOOK_BUILD
extern uint8_t * G0115A13C;
#endif
#define G0115A140 GAME_VAR(uint8_t, G0115A140, 0x0115a140)
#ifndef RE_HOOK_BUILD
extern uint8_t G0115A140;
#endif
#define G00551134 GAME_VAR(int32_t, G00551134, 0x00551134)
#ifndef RE_HOOK_BUILD
extern int32_t G00551134;
#endif
#define G01145934 GAME_VAR(int32_t, G01145934, 0x01145934)
#ifndef RE_HOOK_BUILD
extern int32_t G01145934;
#endif
#define G0113A6C4 GAME_VAR(uint8_t *, G0113A6C4, 0x0113a6c4)
#ifndef RE_HOOK_BUILD
extern uint8_t * G0113A6C4;
#endif
#define G0112B284 GAME_VAR(int32_t, G0112B284, 0x0112b284)
#ifndef RE_HOOK_BUILD
extern int32_t G0112B284;
#endif
#define G00B1FFBC GAME_VAR(int32_t, G00B1FFBC, 0x00b1ffbc)
#ifndef RE_HOOK_BUILD
extern int32_t G00B1FFBC;
#endif
#define G0110E180 GAME_VAR(int32_t, G0110E180, 0x0110e180)
#ifndef RE_HOOK_BUILD
extern int32_t G0110E180;
#endif
#define G00B87E7C GAME_VAR(int32_t, G00B87E7C, 0x00b87e7c)
#ifndef RE_HOOK_BUILD
extern int32_t G00B87E7C;
#endif
#define G00575F08 GAME_VAR(int32_t, G00575F08, 0x00575f08)
#ifndef RE_HOOK_BUILD
extern int32_t G00575F08;
#endif
#define G00560388 GAME_VAR(int32_t, G00560388, 0x00560388)
#ifndef RE_HOOK_BUILD
extern int32_t G00560388;
#endif
#define G00B2C3B8 GAME_VAR(int32_t, G00B2C3B8, 0x00b2c3b8)
#ifndef RE_HOOK_BUILD
extern int32_t G00B2C3B8;
#endif
#define G00D11804 GAME_VAR(int32_t, G00D11804, 0x00d11804)
#ifndef RE_HOOK_BUILD
extern int32_t G00D11804;
#endif
#define G00BDF984 GAME_VAR(int32_t, G00BDF984, 0x00bdf984)
#ifndef RE_HOOK_BUILD
extern int32_t G00BDF984;
#endif
#define G00D078F8 GAME_VAR(int32_t, G00D078F8, 0x00d078f8)
#ifndef RE_HOOK_BUILD
extern int32_t G00D078F8;
#endif
#define G00B31E18 GAME_VAR(int32_t, G00B31E18, 0x00b31e18)
#ifndef RE_HOOK_BUILD
extern int32_t G00B31E18;
#endif
#define G00B31E00 GAME_VAR(int32_t, G00B31E00, 0x00b31e00)
#ifndef RE_HOOK_BUILD
extern int32_t G00B31E00;
#endif
#define G00B31E0C GAME_VAR(int32_t, G00B31E0C, 0x00b31e0c)
#ifndef RE_HOOK_BUILD
extern int32_t G00B31E0C;
#endif
#define G00D044C8 GAME_VAR(int32_t, G00D044C8, 0x00d044c8)
#ifndef RE_HOOK_BUILD
extern int32_t G00D044C8;
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
int32_t GameCall00424661(int32_t a0); /* 00424661 */
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
