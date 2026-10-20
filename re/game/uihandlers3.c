/* uihandlers3.c — a batch of tiny Game.exe functions: menu toggles and slot setters, Glide device
   wrappers, and one-line getters/setters (English overview).  Names carry the Game.exe address or the
   global they touch; do not rename them (hook lists / fn_table.c refer to them). */
#include "uihandlers3.h"
#include "ported149.h"
#include "ported118.h"
#include "carfields.h"
#ifndef RE_HOOK_BUILD
#include "ported92.h"
#include "ported93.h"
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("G00575F24")
#undef G00575F24
#pragma push_macro("G00575F24") /*gvi*/
#undef G00575F24 /*gvi*/
int32_t G00575F24;
#pragma pop_macro("G00575F24") /*gvi*/
#pragma pop_macro("G00575F24")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("G00575F48")
#undef G00575F48
#pragma push_macro("G00575F48") /*gvi*/
#undef G00575F48 /*gvi*/
int32_t G00575F48;
#pragma pop_macro("G00575F48") /*gvi*/
#pragma pop_macro("G00575F48")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("G00575F40")
#undef G00575F40
#pragma push_macro("G00575F40") /*gvi*/
#undef G00575F40 /*gvi*/
int32_t G00575F40;
#pragma pop_macro("G00575F40") /*gvi*/
#pragma pop_macro("G00575F40")
#endif
GAME_VAR_DEF(uint8_t *, UiPtr005FE9B8, 0x005fe9b8)
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("G005FEA54")
#undef G005FEA54
#pragma push_macro("G005FEA54") /*gvi*/
#undef G005FEA54 /*gvi*/
int32_t G005FEA54;
#pragma pop_macro("G005FEA54") /*gvi*/
#pragma pop_macro("G005FEA54")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("G005FEA5C")
#undef G005FEA5C
#pragma push_macro("G005FEA5C") /*gvi*/
#undef G005FEA5C /*gvi*/
int32_t G005FEA5C;
#pragma pop_macro("G005FEA5C") /*gvi*/
#pragma pop_macro("G005FEA5C")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("G005FEA60")
#undef G005FEA60
#pragma push_macro("G005FEA60") /*gvi*/
#undef G005FEA60 /*gvi*/
int32_t G005FEA60;
#pragma pop_macro("G005FEA60") /*gvi*/
#pragma pop_macro("G005FEA60")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("G0054E540")
#undef G0054E540
#pragma push_macro("G0054E540") /*gvi*/
#undef G0054E540 /*gvi*/
int32_t G0054E540;
#pragma pop_macro("G0054E540") /*gvi*/
#pragma pop_macro("G0054E540")
#endif
GAME_VAR_DEF(FnVoidI, FnPtr01270E80, 0x01270e80)
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("G005FEB00")
#undef G005FEB00
#pragma push_macro("G005FEB00") /*gvi*/
#undef G005FEB00 /*gvi*/
int32_t G005FEB00;
#pragma pop_macro("G005FEB00") /*gvi*/
#pragma pop_macro("G005FEB00")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("G005FEEEC")
#undef G005FEEEC
#pragma push_macro("G005FEEEC") /*gvi*/
#undef G005FEEEC /*gvi*/
int32_t G005FEEEC;
#pragma pop_macro("G005FEEEC") /*gvi*/
#pragma pop_macro("G005FEEEC")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("G0127104C")
#undef G0127104C
#pragma push_macro("G0127104C") /*gvi*/
#undef G0127104C /*gvi*/
uint32_t G0127104C;
#pragma pop_macro("G0127104C") /*gvi*/
#pragma pop_macro("G0127104C")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("G0054EF38")
#undef G0054EF38
#pragma push_macro("G0054EF38") /*gvi*/
#undef G0054EF38 /*gvi*/
float G0054EF38;
#pragma pop_macro("G0054EF38") /*gvi*/
#pragma pop_macro("G0054EF38")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("G0054EF3C")
#undef G0054EF3C
#pragma push_macro("G0054EF3C") /*gvi*/
#undef G0054EF3C /*gvi*/
float G0054EF3C;
#pragma pop_macro("G0054EF3C") /*gvi*/
#pragma pop_macro("G0054EF3C")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("G0054603C")
#undef G0054603C
#pragma push_macro("G0054603C") /*gvi*/
#undef G0054603C /*gvi*/
float G0054603C;
#pragma pop_macro("G0054603C") /*gvi*/
#pragma pop_macro("G0054603C")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("G00A421A8")
#undef G00A421A8
#pragma push_macro("G00A421A8") /*gvi*/
#undef G00A421A8 /*gvi*/
int32_t G00A421A8;
#pragma pop_macro("G00A421A8") /*gvi*/
#pragma pop_macro("G00A421A8")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("G00A421A4")
#undef G00A421A4
#pragma push_macro("G00A421A4") /*gvi*/
#undef G00A421A4 /*gvi*/
int32_t G00A421A4;
#pragma pop_macro("G00A421A4") /*gvi*/
#pragma pop_macro("G00A421A4")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("G00B1C0D8")
#undef G00B1C0D8
#pragma push_macro("G00B1C0D8") /*gvi*/
#undef G00B1C0D8 /*gvi*/
int32_t G00B1C0D8;
#pragma pop_macro("G00B1C0D8") /*gvi*/
#pragma pop_macro("G00B1C0D8")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("G00B1C0D4")
#undef G00B1C0D4
#pragma push_macro("G00B1C0D4") /*gvi*/
#undef G00B1C0D4 /*gvi*/
int32_t G00B1C0D4;
#pragma pop_macro("G00B1C0D4") /*gvi*/
#pragma pop_macro("G00B1C0D4")
#endif
GAME_VAR_DEF(FnVoidV, FnPtr01270E54, 0x01270e54)
GAME_VAR_DEF(FnVoidV, FnPtr01271020, 0x01271020)
GAME_VAR_DEF(FnVoidV, FnPtr01270EB0, 0x01270eb0)
GAME_VAR_DEF(FnIntI, FnPtr01270E50, 0x01270e50)
GAME_VAR_DEF(FnIntII, FnPtr01270EAC, 0x01270eac)
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("G012085F4")
#undef G012085F4
#pragma push_macro("G012085F4") /*gvi*/
#undef G012085F4 /*gvi*/
uint32_t G012085F4;
#pragma pop_macro("G012085F4") /*gvi*/
#pragma pop_macro("G012085F4")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("G00550808")
#undef G00550808
#pragma push_macro("G00550808") /*gvi*/
#undef G00550808 /*gvi*/
uint8_t G00550808;
#pragma pop_macro("G00550808") /*gvi*/
#pragma pop_macro("G00550808")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("G01159D74")
#undef G01159D74
#pragma push_macro("G01159D74") /*gvi*/
#undef G01159D74 /*gvi*/
int32_t G01159D74;
#pragma pop_macro("G01159D74") /*gvi*/
#pragma pop_macro("G01159D74")
#endif
GAME_VAR_DEF(uint8_t *, G0115A13C, 0x0115a13c)
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("G0115A140")
#undef G0115A140
#pragma push_macro("G0115A140") /*gvi*/
#undef G0115A140 /*gvi*/
g0115a140_t G0115A140;
#pragma pop_macro("G0115A140") /*gvi*/
#pragma pop_macro("G0115A140")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("G00551134")
#undef G00551134
#pragma push_macro("G00551134") /*gvi*/
#undef G00551134 /*gvi*/
int32_t G00551134;
#pragma pop_macro("G00551134") /*gvi*/
#pragma pop_macro("G00551134")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("G01145934")
#undef G01145934
#pragma push_macro("G01145934") /*gvi*/
#undef G01145934 /*gvi*/
int32_t G01145934;
#pragma pop_macro("G01145934") /*gvi*/
#pragma pop_macro("G01145934")
#endif
GAME_VAR_DEF(uint8_t *, G0113A6C4, 0x0113a6c4)
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("G0112B284")
#undef G0112B284
#pragma push_macro("G0112B284") /*gvi*/
#undef G0112B284 /*gvi*/
int32_t G0112B284;
#pragma pop_macro("G0112B284") /*gvi*/
#pragma pop_macro("G0112B284")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("G00B1FFBC")
#undef G00B1FFBC
#pragma push_macro("G00B1FFBC") /*gvi*/
#undef G00B1FFBC /*gvi*/
int32_t G00B1FFBC;
#pragma pop_macro("G00B1FFBC") /*gvi*/
#pragma pop_macro("G00B1FFBC")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("G0110E180")
#undef G0110E180
#pragma push_macro("G0110E180") /*gvi*/
#undef G0110E180 /*gvi*/
int32_t G0110E180;
#pragma pop_macro("G0110E180") /*gvi*/
#pragma pop_macro("G0110E180")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("G00B87E7C")
#undef G00B87E7C
#pragma push_macro("G00B87E7C") /*gvi*/
#undef G00B87E7C /*gvi*/
int32_t G00B87E7C;
#pragma pop_macro("G00B87E7C") /*gvi*/
#pragma pop_macro("G00B87E7C")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("G00575F08")
#undef G00575F08
#pragma push_macro("G00575F08") /*gvi*/
#undef G00575F08 /*gvi*/
int32_t G00575F08;
#pragma pop_macro("G00575F08") /*gvi*/
#pragma pop_macro("G00575F08")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("G00560388")
#undef G00560388
#pragma push_macro("G00560388") /*gvi*/
#undef G00560388 /*gvi*/
int32_t G00560388;
#pragma pop_macro("G00560388") /*gvi*/
#pragma pop_macro("G00560388")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("G00B2C3B8")
#undef G00B2C3B8
#pragma push_macro("G00B2C3B8") /*gvi*/
#undef G00B2C3B8 /*gvi*/
int32_t G00B2C3B8;
#pragma pop_macro("G00B2C3B8") /*gvi*/
#pragma pop_macro("G00B2C3B8")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("G00D11804")
#undef G00D11804
#pragma push_macro("G00D11804") /*gvi*/
#undef G00D11804 /*gvi*/
int32_t G00D11804;
#pragma pop_macro("G00D11804") /*gvi*/
#pragma pop_macro("G00D11804")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("G00BDF984")
#undef G00BDF984
#pragma push_macro("G00BDF984") /*gvi*/
#undef G00BDF984 /*gvi*/
int32_t G00BDF984;
#pragma pop_macro("G00BDF984") /*gvi*/
#pragma pop_macro("G00BDF984")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("G00B31E18")
#undef G00B31E18
#pragma push_macro("G00B31E18") /*gvi*/
#undef G00B31E18 /*gvi*/
int32_t G00B31E18;
#pragma pop_macro("G00B31E18") /*gvi*/
#pragma pop_macro("G00B31E18")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("G00B31E00")
#undef G00B31E00
#pragma push_macro("G00B31E00") /*gvi*/
#undef G00B31E00 /*gvi*/
int32_t G00B31E00;
#pragma pop_macro("G00B31E00") /*gvi*/
#pragma pop_macro("G00B31E00")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("G00B31E0C")
#undef G00B31E0C
#pragma push_macro("G00B31E0C") /*gvi*/
#undef G00B31E0C /*gvi*/
int32_t G00B31E0C;
#pragma pop_macro("G00B31E0C") /*gvi*/
#pragma pop_macro("G00B31E0C")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("G00D044C8")
#undef G00D044C8
#pragma push_macro("G00D044C8") /*gvi*/
#undef G00D044C8 /*gvi*/
int32_t G00D044C8;
#pragma pop_macro("G00D044C8") /*gvi*/
#pragma pop_macro("G00D044C8")
#endif
/* MenuToggle* — Game.exe 0040e970, 0040ea57, 00419c50, 00419d25, 0041539a.  Flip option flag 00575f24 / 00575f48
   / 00575f40 and redraw the screen they belong to (0040ea70, 00419b35, 00414d1f).  Return 0.
   RE_PROBE menu walk: 00575f24 = "Auto Handbrake", 00575f48 = "FMV" (Gameplay menu 0054ad60, page 0040ea70),
   00575f40 = sound "Effects" On/Off (Sound menu 0054dd10, page 00414d1f). */
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
/* UiSetSlot* — Game.exe 004142e8, 004143fa, 0041450c, 00414621.  On normal entry (arg 0) set the state byte of
   item 1..4 (+0x24, +0x44, +0x64, +0x84 of the menu table 005fe9b8) to 2. */
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
/* Ui00418119 — Game.exe 00418119.  Sets 005fea54 = 1 and starts camera route a0 (P118_CamRoute). */
void Ui00418119(int32_t a0) {
    G005FEA54 = 1; P118_CamRoute((uint32_t)a0);
}
/* Ui004184DE — Game.exe 004184de.  005fea5c = a0, 005fea60 = 1. */
void Ui004184DE(int32_t a0) {
    G005FEA5C = a0; G005FEA60 = 1;
}
/* Ui004197F8 — Game.exe 004197f8.  Saves the driver mode (0042655a(0)) in 0054e540 and calls 01270e80(0) if set. */
void Ui004197F8(void) {
    G0054E540 = Call0042655A(0); if (FnPtr01270E80) FnPtr01270E80(0);   /* v2.10: NULL в native */
}
/* Ui0041A1EC — Game.exe 0041a1ec.  005feb00 = a0. */
void Ui0041A1EC(int32_t a0) {
    G005FEB00 = a0;
}
/* UiSetMode005FEEEC_0..7 — Game.exe 0041ae2f ... 0041aebb.  Select entry 0..7 (005feeec) of a list menu. */
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
/* Ui0041B059 — Game.exe 0041b059.  Calls 0041af29 with 2 * selected entry + 1. */
void Ui0041B059(void) {
    UiCall0041AF29(G005FEEEC * 2 + 1);
}
/* FlagSet0127104C — Game.exe 0041b790.  Sets bit `bit` (mod 32) of 0127104c. */
void FlagSet0127104C(uint8_t bit) {
    G0127104C |= 1u << (bit & 31);
}
/* SetScale54EF38 — Game.exe 0041d8cd.  0054ef38 = v, 0054ef3c = v * constant 0054603c. */
void SetScale54EF38(float v) {
    G0054EF38 = v; G0054EF3C = v * G0054603C;
}
/* Ui0041ED53 — Game.exe 0041ed53.  Forwards to GameCall00424661 (grSstQueryHardware). */
void Ui0041ED53(int32_t a0) {
    GameCall00424661(a0);
}
/* GetVarA421A8 / GetVarA421A4 / GetVarB1C0D8 — Game.exe 0041ed68 / 0041ed72 / 004245e2.  Return the global.
   (00b1c0d8 is the renderer kind: 0 = Glide, 1 = Direct3D emulation.) */
int32_t GetVarA421A8(void) {
    return G00A421A8;
}
int32_t GetVarA421A4(void) {
    return G00A421A4;
}
/* Ret1FFFF8IfZero — Game.exe 0041f734.  0x1ffff8 if a0 == 0, else 0.  TODO(RE): unsure (looks like a Glide
   texture-memory query stub). */
int32_t Ret1FFFF8IfZero(int32_t a0) {
    return a0 == 0 ? 0x1ffff8 : 0;
}
/* RetZero0041FA36 — Game.exe 0041fa36.  Returns 0. */
uint16_t RetZero0041FA36(void) {
    return 0;
}
int32_t GetVarB1C0D8(void) {
    return G00B1C0D8;
}
/* Dev00424633 / Dev00424647 / Dev004246BD — Game.exe 00424633 / 00424647 / 004246bd.  When Glide is in use
   (00b1c0d4) call the Glide entry points stored at 01270e54 / 01271020 + 01270eb0 / 01271020.
   TODO(RE): which Glide functions these pointers hold. */
void Dev00424633(void) {
    if (G00B1C0D4 != 0) FnPtr01270E54();
}
void Dev00424647(void) {
    if (G00B1C0D4 != 0) { FnPtr01271020(); FnPtr01270EB0(); }
}
/* GameCall00424661 — Game.exe 00424661.  grSstQueryHardware(a0) through 01270e50 when Glide is in use, else 0.
   Native: the GrHwConfiguration pointer is passed as intptr_t (64-bit). */
int32_t GameCall00424661(intptr_t a0) {
    /* v2.00: grSstQueryHardware(GrHwConfiguration *) — указатель не режется до int32 в native (64 бит) */
    return G00B1C0D4 == 0 ? 0 : ((int32_t (*)(intptr_t))FnPtr01270E50)(a0);
}
void Dev004246BD(void) {
    if (G00B1C0D4 != 0) FnPtr01271020();
}
/* Dev0042480D — Game.exe 0042480d.  01270eac(1, a0) when Glide is in use, else 0 (called after frame-buffer
   writes with a0 = 1; TODO(RE): likely grLfbUnlock(GR_LFB_WRITE_ONLY, buffer)). */
int32_t Dev0042480D(int32_t a0) {
    return G00B1C0D4 == 0 ? 0 : FnPtr01270EAC(1, a0);
}
/* Dev00424858 — Game.exe 00424858.  On the Direct3D path frees the emulated textures (P149_EmulFreeAll). */
void Dev00424858(void) {
    if (GetVarB1C0D8() == 1) P149_EmulFreeAll();
}
/* Ui00426CAF — Game.exe 00426caf.  Looks up the "SEA" icon used by the rotating-texture models
   (P92_DrawSpin).  Native: stored in P92_SpinTex (a native pointer does not fit G012085F4). */
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
/* Ui00426CC6 — Game.exe 00426cc6.  Calls 004d8f30(00b1c280) and clears 00b1c280. */
void Ui00426CC6(void) {
    UiCall004D8F30(UiVar00B1C280); UiVar00B1C280 = 0;
}
/* Reset0042D2B0 — Game.exe 0042d2b0.  01159d74 = 0 and rewinds the pointer 0115a13c to 0115a140. */
void Reset0042D2B0(void) {
    G01159D74 = 0; G0115A13C = G0115A140;
}
/* Set551134 / Ret1 / Dec145934 / Inc0B1FFBC / Clear110E180 / Clear2C3B8 / SetD11804 / CopyBDF984 / GetB31E18 /
   Set0D044C8 / Set560388 — one-line setters/getters (Game.exe addresses in the hook lists); see each body. */
void Set551134(void) {
    G00551134 = 1;
}
int32_t Ret1(void) {
    return 1;
}
void Dec145934(void) {
    if (G01145934 != 0) G01145934--;
}
/* Get138Entry148 — Game.exe 004a1d31.  Total damage (CAR_DAMAGE_SUM) of car i of the car table at 0113a6c4. */
int32_t Get138Entry148(int32_t i) {
    return *(int32_t *)(G0113A6C4 + CAR_DAMAGE_SUM + i * 0x148);   /* car table 0113a6c4, 0x148 bytes per car */
}
/* IsVar112B284Lt8 — Game.exe 004a66d8.  1 if 0112b284 < 8. */
int32_t IsVar112B284Lt8(void) {
    return G0112B284 < 8;
}
void Inc0B1FFBC(void) {
    G00B1FFBC++;
}
void Clear110E180(void) {
    G0110E180 = 0;
}
/* Call004BF485 — Game.exe 004bf485.  Debug print 004d90f4(a0) unless 00b87e7c suppresses debug output. */
void Call004BF485(int32_t a0) {
    if (G00B87E7C == 0) Call004D90F4(a0);
}
/* CopyWords8000 — Game.exe 004c16c1.  Copies 0x8000 words (128 KB, one 16-bit 256x256 texture page) src -> dst. */
void CopyWords8000(uint32_t *src, uint32_t *dst) {
    for (int i = 0; i < 0x8000; i++) dst[i] = src[i];
}
/* Call004D2D85 — Game.exe 004d2d85.  004d611b(a0) when 00575f08 is set. */
void Call004D2D85(int32_t a0) {
    if (G00575F08 != 0) Call004D611B(a0);
}
void Set560388(int32_t a0) {
    G00560388 = a0 + 0xf;
}
/* Round1024 — Game.exe 004d9013.  Heading (4096 = 360 deg) rounded to the nearest quarter turn: 0..3
   (N / E / S / W in P47_DirText). */
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
/* SetB31E00 — Game.exe 004e3b20.  Sets the force-feedback engine level 00b31e00 and marks it changed
   (00b31e0c, sent by P35_UpdateForce).  Returns 1. */
int32_t SetB31E00(int32_t a0) {
    G00B31E00 = a0; G00B31E0C = 1; return 1;
}
/* Get138 — Game.exe 004e5f4d.  Total damage of car record p (CAR_DAMAGE_SUM). */
int32_t Get138(uint8_t *p) {
    return *(int32_t *)(p + CAR_DAMAGE_SUM);
}
void Set0D044C8(void) {
    G00D044C8 = 0xb4;
}
/* Call004A2C08 / Call004BF476 / Call004C020E — Game.exe 004a2c08 / 004bf476 / 004c020e.  Forwarders to 004a2c98 /
   004d9478 / 004c1b46. */
void Call004A2C08(void) {
    Call004A2C98();
}
void Call004BF476(void) {
    Call004D9478();
}
void Call004C020E(void) {
    Call004C1B46();
}
