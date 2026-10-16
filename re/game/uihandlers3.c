#include "uihandlers3.h"
#include "ported149.h"
#include "ported118.h"
#ifndef RE_HOOK_BUILD
#include "ported92.h"
#include "ported93.h"
#endif
GAME_VAR_DEF(int32_t, G00575F24, 0x00575f24)
GAME_VAR_DEF(int32_t, G00575F48, 0x00575f48)
GAME_VAR_DEF(int32_t, G00575F40, 0x00575f40)
GAME_VAR_DEF(uint8_t *, UiPtr005FE9B8, 0x005fe9b8)
GAME_VAR_DEF(int32_t, G005FEA54, 0x005fea54)
GAME_VAR_DEF(int32_t, G005FEA5C, 0x005fea5c)
GAME_VAR_DEF(int32_t, G005FEA60, 0x005fea60)
GAME_VAR_DEF(int32_t, G0054E540, 0x0054e540)
GAME_VAR_DEF(FnVoidI, FnPtr01270E80, 0x01270e80)
GAME_VAR_DEF(int32_t, G005FEB00, 0x005feb00)
GAME_VAR_DEF(int32_t, G005FEEEC, 0x005feeec)
GAME_VAR_DEF(uint32_t, G0127104C, 0x0127104c)
GAME_VAR_DEF(float, G0054EF38, 0x0054ef38)
GAME_VAR_DEF(float, G0054EF3C, 0x0054ef3c)
GAME_VAR_DEF(float, G0054603C, 0x0054603c)
GAME_VAR_DEF(int32_t, G00A421A8, 0x00a421a8)
GAME_VAR_DEF(int32_t, G00A421A4, 0x00a421a4)
GAME_VAR_DEF(int32_t, G00B1C0D8, 0x00b1c0d8)
GAME_VAR_DEF(int32_t, G00B1C0D4, 0x00b1c0d4)
GAME_VAR_DEF(FnVoidV, FnPtr01270E54, 0x01270e54)
GAME_VAR_DEF(FnVoidV, FnPtr01271020, 0x01271020)
GAME_VAR_DEF(FnVoidV, FnPtr01270EB0, 0x01270eb0)
GAME_VAR_DEF(FnIntI, FnPtr01270E50, 0x01270e50)
GAME_VAR_DEF(FnIntII, FnPtr01270EAC, 0x01270eac)
GAME_VAR_DEF(uint32_t, G012085F4, 0x012085f4)
GAME_VAR_DEF(uint8_t, G00550808, 0x00550808)
GAME_VAR_DEF(int32_t, G01159D74, 0x01159d74)
GAME_VAR_DEF(uint8_t *, G0115A13C, 0x0115a13c)
GAME_VAR_DEF(uint8_t, G0115A140, 0x0115a140)
GAME_VAR_DEF(int32_t, G00551134, 0x00551134)
GAME_VAR_DEF(int32_t, G01145934, 0x01145934)
GAME_VAR_DEF(uint8_t *, G0113A6C4, 0x0113a6c4)
GAME_VAR_DEF(int32_t, G0112B284, 0x0112b284)
GAME_VAR_DEF(int32_t, G00B1FFBC, 0x00b1ffbc)
GAME_VAR_DEF(int32_t, G0110E180, 0x0110e180)
GAME_VAR_DEF(int32_t, G00B87E7C, 0x00b87e7c)
GAME_VAR_DEF(int32_t, G00575F08, 0x00575f08)
GAME_VAR_DEF(int32_t, G00560388, 0x00560388)
GAME_VAR_DEF(int32_t, G00B2C3B8, 0x00b2c3b8)
GAME_VAR_DEF(int32_t, G00D11804, 0x00d11804)
GAME_VAR_DEF(int32_t, G00BDF984, 0x00bdf984)
GAME_VAR_DEF(int32_t, G00B31E18, 0x00b31e18)
GAME_VAR_DEF(int32_t, G00B31E00, 0x00b31e00)
GAME_VAR_DEF(int32_t, G00B31E0C, 0x00b31e0c)
GAME_VAR_DEF(int32_t, G00D044C8, 0x00d044c8)
int32_t MenuToggle575F24Call40EA70(void) {
    G00575F24 ^= 1; Call0040EA70(); return 0;
}
int32_t MenuToggle575F48Call40EA70(void) {
    G00575F48 ^= 1; Call0040EA70(); return 0;
}
int32_t MenuToggle575F24Call419B35(void) {
    G00575F24 ^= 1; Call00419B35(); return 0;
}
int32_t MenuToggle575F48Call419B35(void) {
    G00575F48 ^= 1; Call00419B35(); return 0;
}
int32_t MenuToggle575F40Call414D1F(void) {
    G00575F40 ^= 1; Call00414D1F(); return 0;
}
void UiSetSlot004142E8(int32_t a0) {
    if (a0 == 0) UiPtr005FE9B8[0x24] = 2;
}
void UiSetSlot004143FA(int32_t a0) {
    if (a0 == 0) UiPtr005FE9B8[0x44] = 2;
}
void UiSetSlot0041450C(int32_t a0) {
    if (a0 == 0) UiPtr005FE9B8[0x64] = 2;
}
void UiSetSlot00414621(int32_t a0) {
    if (a0 == 0) UiPtr005FE9B8[0x84] = 2;
}
void Ui00418119(int32_t a0) {
    G005FEA54 = 1; P118_CamRoute((uint32_t)a0);
}
void Ui004184DE(int32_t a0) {
    G005FEA5C = a0; G005FEA60 = 1;
}
void Ui004197F8(void) {
    G0054E540 = Call0042655A(0); FnPtr01270E80(0);
}
void Ui0041A1EC(int32_t a0) {
    G005FEB00 = a0;
}
void UiSetMode005FEEEC_0(void) {
    G005FEEEC = 0; NoopFn0041b054();
}
void UiSetMode005FEEEC_1(void) {
    G005FEEEC = 1; NoopFn0041b054();
}
void UiSetMode005FEEEC_2(void) {
    G005FEEEC = 2; NoopFn0041b054();
}
void UiSetMode005FEEEC_3(void) {
    G005FEEEC = 3; NoopFn0041b054();
}
void UiSetMode005FEEEC_4(void) {
    G005FEEEC = 4; NoopFn0041b054();
}
void UiSetMode005FEEEC_5(void) {
    G005FEEEC = 5; NoopFn0041b054();
}
void UiSetMode005FEEEC_6(void) {
    G005FEEEC = 6; NoopFn0041b054();
}
void UiSetMode005FEEEC_7(void) {
    G005FEEEC = 7; NoopFn0041b054();
}
void Ui0041B059(void) {
    UiCall0041AF29(G005FEEEC * 2 + 1);
}
void FlagSet0127104C(uint8_t bit) {
    G0127104C |= 1u << (bit & 31);
}
void SetScale54EF38(float v) {
    G0054EF38 = v; G0054EF3C = v * G0054603C;
}
void Ui0041ED53(int32_t a0) {
    GameCall00424661(a0);
}
int32_t GetVarA421A8(void) {
    return G00A421A8;
}
int32_t GetVarA421A4(void) {
    return G00A421A4;
}
int32_t Ret1FFFF8IfZero(int32_t a0) {
    return a0 == 0 ? 0x1ffff8 : 0;
}
uint16_t RetZero0041FA36(void) {
    return 0;
}
int32_t GetVarB1C0D8(void) {
    return G00B1C0D8;
}
void Dev00424633(void) {
    if (G00B1C0D4 != 0) FnPtr01270E54();
}
void Dev00424647(void) {
    if (G00B1C0D4 != 0) { FnPtr01271020(); FnPtr01270EB0(); }
}
int32_t GameCall00424661(int32_t a0) {
    return G00B1C0D4 == 0 ? 0 : FnPtr01270E50(a0);
}
void Dev004246BD(void) {
    if (G00B1C0D4 != 0) FnPtr01271020();
}
int32_t Dev0042480D(int32_t a0) {
    return G00B1C0D4 == 0 ? 0 : FnPtr01270EAC(1, a0);
}
void Dev00424858(void) {
    if (GetVarB1C0D8() == 1) P149_EmulFreeAll();
}
void Ui00426CAF(void) {
#ifdef RE_HOOK_BUILD
    G012085F4 = LoadIconByName((const char *)&G00550808);
#else
    /* native: строки 00550808 ("SEA") в .data нет, а 32-битный G012085F4 родной указатель не вмещает —
       прямоугольник текстуры кладётся в P92_SpinTex (его читает P92_DrawSpin 0042a5de). */
    P92_SpinTex = P93_FindIcon("SEA");
    G012085F4 = 0;
#endif
}
void Ui00426CC6(void) {
    UiCall004D8F30(UiVar00B1C280); UiVar00B1C280 = 0;
}
void Reset0042D2B0(void) {
    G01159D74 = 0; G0115A13C = &G0115A140;
}
void Set551134(void) {
    G00551134 = 1;
}
int32_t Ret1(void) {
    return 1;
}
void Dec145934(void) {
    if (G01145934 != 0) G01145934--;
}
int32_t Get138Entry148(int32_t i) {
    return *(int32_t *)(G0113A6C4 + 0x138 + i * 0x148);
}
int32_t IsVar112B284Lt8(void) {
    return G0112B284 < 8;
}
void Inc0B1FFBC(void) {
    G00B1FFBC++;
}
void Clear110E180(void) {
    G0110E180 = 0;
}
void Call004BF485(int32_t a0) {
    if (G00B87E7C == 0) Call004D90F4(a0);
}
void CopyWords8000(uint32_t *src, uint32_t *dst) {
    for (int i = 0; i < 0x8000; i++) dst[i] = src[i];
}
void Call004D2D85(int32_t a0) {
    if (G00575F08 != 0) Call004D611B(a0);
}
void Set560388(int32_t a0) {
    G00560388 = a0 + 0xf;
}
int32_t Round1024(int32_t a0) {
    return (int32_t)((uint32_t)(a0 + 0x200) & 0xfff) >> 10;
}
void Clear2C3B8(void) {
    G00B2C3B8 = 0;
}
void SetD11804(int32_t a0) {
    G00D11804 = a0;
}
void CopyBDF984(void) {
    G00BDF984 = G00D078F8;
}
int32_t GetB31E18(void) {
    return G00B31E18;
}
int32_t SetB31E00(int32_t a0) {
    G00B31E00 = a0; G00B31E0C = 1; return 1;
}
int32_t Get138(uint8_t *p) {
    return *(int32_t *)(p + 0x138);
}
void Set0D044C8(void) {
    G00D044C8 = 0xb4;
}
void Call004A2C08(void) {
    Call004A2C98();
}
void Call004BF476(void) {
    Call004D9478();
}
void Call004C020E(void) {
    Call004C1B46();
}
