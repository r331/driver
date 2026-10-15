#include "ported6.h"
#include "ported40.h"
#include "engine.h"
#include "flush.h"
GAME_VAR_DEF(int32_t, G6_011368C4, 0x011368c4)
GAME_VAR_DEF(int32_t, G6_01136920, 0x01136920)
GAME_VAR_DEF(g6a_01145A60, G6_01145A60, 0x01145a60)
GAME_VAR_DEF(int32_t, G6_0125F3F0, 0x0125f3f0)
GAME_VAR_DEF(int32_t, G6_01270C28, 0x01270c28)
GAME_VAR_DEF(int32_t, G6_01270C34, 0x01270c34)
GAME_VAR_DEF(FnI1, G6_01270D20, 0x01270d20)
GAME_VAR_DEF(FnV1, G6_01270D28, 0x01270d28)
GAME_VAR_DEF(FnV1, G6_01270DE4, 0x01270de4)
GAME_VAR_DEF(g6a_00549F84, G6_00549F84, 0x00549f84)
GAME_VAR_DEF(g6a_0054A25C, G6_0054A25C, 0x0054a25c)
GAME_VAR_DEF(g6a_0054DBCC, G6_0054DBCC, 0x0054dbcc)
GAME_VAR_DEF(g6a_0054E56C, G6_0054E56C, 0x0054e56c)
GAME_VAR_DEF(g6a_0054E834, G6_0054E834, 0x0054e834)
GAME_VAR_DEF(int32_t, G6_0054EF2C, 0x0054ef2c)
GAME_VAR_DEF(int32_t, G6_005624A0, 0x005624a0)
GAME_VAR_DEF(g6a_00562B70, G6_00562B70, 0x00562b70)
GAME_VAR_DEF(int32_t, G6_005755C8, 0x005755c8)
GAME_VAR_DEF(int32_t, G6_00575A70, 0x00575a70)
GAME_VAR_DEF(int32_t, G6_00575EBC, 0x00575ebc)
GAME_VAR_DEF(int32_t, G6_00575EC0, 0x00575ec0)
GAME_VAR_DEF(int32_t, G6_00575EEC, 0x00575eec)
GAME_VAR_DEF(int32_t, G6_00575EF4, 0x00575ef4)
GAME_VAR_DEF(int32_t, G6_00575F00, 0x00575f00)
GAME_VAR_DEF(int32_t, G6_00575F04, 0x00575f04)
GAME_VAR_DEF(int32_t, G6_00575F20, 0x00575f20)
GAME_VAR_DEF(int32_t, G6_00575F34, 0x00575f34)
GAME_VAR_DEF(int32_t, G6_00575F38, 0x00575f38)
GAME_VAR_DEF(int32_t, G6_0057B728, 0x0057b728)
GAME_VAR_DEF(int32_t, G6_005D5788, 0x005d5788)
GAME_VAR_DEF(int32_t, G6_005FE9BC, 0x005fe9bc)
GAME_VAR_DEF(int32_t, G6_005FE9CC, 0x005fe9cc)
GAME_VAR_DEF(int32_t, G6_005FEA7C, 0x005fea7c)
GAME_VAR_DEF(int32_t, G6_005FED9C, 0x005fed9c)
GAME_VAR_DEF(int32_t, G6_00A421F0, 0x00a421f0)
GAME_VAR_DEF(int32_t, G6_00B1C224, 0x00b1c224)
GAME_VAR_DEF(int32_t, G6_00B20364, 0x00b20364)
GAME_VAR_DEF(int32_t, G6_00B20368, 0x00b20368)
GAME_VAR_DEF(g6a_00B2F30C, G6_00B2F30C, 0x00b2f30c)
GAME_VAR_DEF(int32_t, G6_00B31F40, 0x00b31f40)
GAME_VAR_DEF(int32_t, G6_00B5A778, 0x00b5a778)
GAME_VAR_DEF(uint8_t, G6_00B5A838, 0x00b5a838)
GAME_VAR_DEF(uint8_t, G6_00B5A839, 0x00b5a839)
GAME_VAR_DEF(uint8_t, G6_00B5A83A, 0x00b5a83a)
GAME_VAR_DEF(void*, G6_00B5A83C, 0x00b5a83c)
GAME_VAR_DEF(void*, G6_00B5A840, 0x00b5a840)
GAME_VAR_DEF(int32_t, G6_00B5A8A0, 0x00b5a8a0)
GAME_VAR_DEF(int32_t, G6_00B5A8AC, 0x00b5a8ac)
GAME_VAR_DEF(int32_t, G6_00B5A8B0, 0x00b5a8b0)
GAME_VAR_DEF(int32_t, G6_00B87E20, 0x00b87e20)
GAME_VAR_DEF(int32_t, G6_00B87E50, 0x00b87e50)
GAME_VAR_DEF(int32_t, G6_00B87E74, 0x00b87e74)
GAME_VAR_DEF(int32_t, G6_00B87EA0, 0x00b87ea0)
GAME_VAR_DEF(int32_t, G6_00B87EAC, 0x00b87eac)
GAME_VAR_DEF(int32_t, G6_00B87EB0, 0x00b87eb0)
GAME_VAR_DEF(int32_t, G6_00B87EEC, 0x00b87eec)
GAME_VAR_DEF(int32_t, G6_00B87EFC, 0x00b87efc)
GAME_VAR_DEF(g6a_00B91BC4, G6_00B91BC4, 0x00b91bc4)
GAME_VAR_DEF(int32_t, G6_00B91CF4, 0x00b91cf4)
GAME_VAR_DEF(int32_t, G6_00B91D2C, 0x00b91d2c)
GAME_VAR_DEF(int32_t, G6_00B91D34, 0x00b91d34)
GAME_VAR_DEF(FnV2, G6_00BDCB14, 0x00bdcb14)
GAME_VAR_DEF(FnV1, G6_00BDCB18, 0x00bdcb18)
GAME_VAR_DEF(FnV1, G6_00BDCB20, 0x00bdcb20)
GAME_VAR_DEF(int32_t, G6_00BDF9C0, 0x00bdf9c0)
GAME_VAR_DEF(int32_t, G6_00BDF9C4, 0x00bdf9c4)
GAME_VAR_DEF(int32_t, G6_00C557F8, 0x00c557f8)
GAME_VAR_DEF(int32_t, G6_00C55800, 0x00c55800)
GAME_VAR_DEF(int32_t, G6_00C56764, 0x00c56764)
GAME_VAR_DEF(g6a_00C5678C, G6_00C5678C, 0x00c5678c)
GAME_VAR_DEF(g6a_00C594A0, G6_00C594A0, 0x00c594a0)
GAME_VAR_DEF(void*, G6_00C80C50, 0x00c80c50)
GAME_VAR_DEF(int32_t, G6_00C81108, 0x00c81108)
GAME_VAR_DEF(void*, G6_00CE0F20, 0x00ce0f20)
GAME_VAR_DEF(void*, G6_00D00208, 0x00d00208)
GAME_VAR_DEF(void*, G6_00D01268, 0x00d01268)
GAME_VAR_DEF(g6a_00D04A50, G6_00D04A50, 0x00d04a50)
GAME_VAR_DEF(int32_t, G6_00D0DDC0, 0x00d0ddc0)
GAME_VAR_DEF(uint32_t, G6_00D10E40, 0x00d10e40)
GAME_VAR_DEF(int32_t, G6_00D117A4, 0x00d117a4)
GAME_VAR_DEF(int32_t, G6_00D117A8, 0x00d117a8)
GAME_VAR_DEF(uint32_t, G6_00D11800, 0x00d11800)
GAME_VAR_DEF(int32_t, G6_00D11880, 0x00d11880)
GAME_VAR_DEF(int32_t, G6_00D11928, 0x00d11928)
/* ---- цвета строк меню (пары Select/Leave): байты RGB в таблице записей по 16 байт ---- */
static void rgb3(uint8_t *tab, int32_t idx, uint8_t r, uint8_t g, uint8_t b) {
    tab[idx * 0x10] = r; tab[idx * 0x10 + 1] = g; tab[idx * 0x10 + 2] = b;
}
static void hilite_pair(uint8_t *tab, int32_t a, int32_t b, uint8_t r, uint8_t g, uint8_t bl) {
    rgb3(tab, a, r, g, bl);
    if (b != -1) rgb3(tab, b, r, g, bl);
}
void MenuRed0040766D(void) { if (G6_0057B728 != -1) hilite_pair(G6_00549F84, MenuI0057B730, MenuI0054A060, 0xff, 0, 0); }
void MenuWhite004076E2(void) { rgb3(G6_00549F84, MenuI0057B730, 0xff, 0xff, 0xff); if (MenuI0054A060 != -1) rgb3(G6_00549F84, MenuI0054A060, 0xff, 0xff, 0xff); }
void MenuRed00409C85(void) { if (G6_005D5788 != -1) hilite_pair(G6_0054A25C, MenuI005D578C, MenuI0054A694, 0xff, 0, 0); }
void MenuWhite00409CFA(void) { hilite_pair(G6_0054A25C, MenuI005D578C, MenuI0054A694, 0xff, 0xff, 0xff); }
void MenuRed00415904(void) { if (G6_005FE9CC != -1) hilite_pair(G6_0054DBCC, MenuI005FE9D0, MenuI0054DE08, 0xff, 0, 0); }
void MenuWhite00415979(void) { hilite_pair(G6_0054DBCC, MenuI005FE9D0, MenuI0054DE08, 0xff, 0xff, 0xff); }
void MenuRed00419D3E(void) { if (G6_005FEA7C != -1) hilite_pair(G6_0054E56C, UiVar005FEA80, UiVar0054E654, 0xff, 0, 0); }
void MenuWhite00419DB3(void) { hilite_pair(G6_0054E56C, UiVar005FEA80, UiVar0054E654, 0xff, 0xff, 0xff); }
void MenuWhite0041AF29(int32_t i) { rgb3(G6_0054E834, i, 0xff, 0xff, 0xff); rgb3(G6_0054E834, i + 1, 0xff, 0xff, 0xff); }
void MenuMark00412228(void) { WB0054C6D4[(UiVar005FE84C * 2 + 3) * 0x10] = 3; WB0054C6D4[(UiVar005FE84C * 2 + 4) * 0x10] = 3; }

/* ---- переключатели «вкл/альт» и циклы ---- */
static void dual_toggle(int32_t *on, int32_t *alt) {
    if (*on == 0) { *on = 1; *alt = 0; }
    else { if (*alt != 0) *on = 0; *alt = (*alt == 0); }
}
static void tri_state(void) {
    if (G6_00575F34 == 0) { G6_00575F34 = 1; G6_00575F38 = 0; G6_00575EEC = 1; }
    else if (G6_00575F38 == 1) { G6_00575F38 = 0; G6_00575F34 = 0; }
    else if (G6_00575EEC == 5) { G6_00575F38 = 1; }
    else { G6_00575EEC = G6_00575EEC + 1; }
}
int32_t MenuToggle00408994(void) { dual_toggle(&G6_00D11880, &G6_00575F20); G00575EF8 = 4; MenuRedraw(); return 0; }
int32_t MenuToggle00408C37(void) { dual_toggle(&G6_00575EC0, &G6_00575EBC); G00575EF8 = 4; MenuRedraw(); return 0; }
int32_t MenuToggle00409142(void) { dual_toggle(&G6_00575EF4, &G6_00B87E74); G00575EF8 = 4; MenuRedraw(); return 0; }
int32_t MenuToggle0050FE26(void) { dual_toggle(&G6_00D11880, &G6_00575F20); G00575EF8 = 4; Call0050FBF4(); return 0; }
int32_t MenuToggle0050FEE5(void) { dual_toggle(&G6_00575EC0, &G6_00575EBC); G00575EF8 = 4; Call0050FBF4(); return 0; }
int32_t MenuToggle00510028(void) { dual_toggle(&G6_00575EF4, &G6_00B87E74); G00575EF8 = 4; Call0050FBF4(); return 0; }
int32_t MenuTri0040E9B5(void) { tri_state(); Call0040EA70(); return 0; }
int32_t MenuTri00419C8C(void) { tri_state(); Call00419B35(); return 0; }
int32_t MenuQuality004088DB(void) {
    G00575EF8 = G00575EF8 + 1; if (3 < G00575EF8) G00575EF8 = 0;
    G6Call004064B4(G00575EF8, 0); G6Call004094E3(); MenuRedraw(); return 0;
}
int32_t MenuQuality0050FA70(void) {
    G00575EF8 = G00575EF8 + 1; if (3 < G00575EF8) G00575EF8 = 0;
    G6Call004064B4(G00575EF8, 1); G6Call0050FAB0(); Call0050FBF4(); return 0;
}

/* ---- звуковые параметры (через указатели на функции драйвера звука) ---- */
void SoundSetFormat005235D3(int32_t a, int32_t b) { if (G6_00B91CF4 != 0) G6_00BDCB14(a, b); }
void SoundSetVolA005235F2(int32_t a) { if (G6_00B91CF4 != 0) G6_00BDCB18(a); }
void SoundSetVolB0052360D(int32_t a) { if (G6_00B91CF4 != 0) G6_00BDCB20(a); }
int32_t MenuBits0041556C(void) {
    G6_00575F00 = (G6_00575F00 == 8) ? 0x10 : 8;
    SoundSetFormat005235D3(G6_00575F00, G6_00575F04); Call00414D1F(); return 0;
}
int32_t MenuRate00415623(void) {
    G6_00575F04 = (G6_00575F04 == 0x5622) ? 0xac44 : 0x5622;
    SoundSetFormat005235D3(G6_00575F00, G6_00575F04); Call00414D1F(); return 0;
}
int32_t MenuSoundCh004156DD(void) {
    G6_00B87E50 = G6_00B87E50 + 1; if (G6_00B87E50 == 5) G6_00B87E50 = 0;
    SoundSetVolA005235F2(G6_00B87E50); Call00414D1F(); return 0;
}
void MenuBits0050F8F2(void) {
    G6_00575F00 = (G6_00575F00 == 8) ? 0x10 : 8;
    SoundSetFormat005235D3(G6_00575F00, G6_00575F04); Call0050F7B2();
}
void MenuRate0050F930(void) {
    G6_00575F04 = (G6_00575F04 == 0x5622) ? 0xac44 : 0x5622;
    SoundSetFormat005235D3(G6_00575F00, G6_00575F04); Call0050F7B2();
}
void MenuSoundCh0050F971(void) {
    G6_00B87E50 = G6_00B87E50 + 1; if (G6_00B87E50 == 5) G6_00B87E50 = 0;
    SoundSetVolA005235F2(G6_00B87E50); Call0050F7B2();
}
void MenuSound0050F781(void) {
    G00575F40 = G00575F40 ^ 1;
    if (G00575F40 == 0) G6Call004D5FFC(); else { G6Call004D5CE0(); G6Call00524398(); }
    Call0050F7B2();
}
void MenuMusic0050F8A2(void) {
    Q00B87E90 = Q00B87E90 ^ 1;
    if (Q00B87E90 == 0) { Call00524873(); Call00524763(); }
    Call0050F7B2();
}
void MenuMusic0050F8CC(void) { Q00B87E94 = Q00B87E94 ^ 1; Call0052369B(Q00B87E94); Call0050F7B2(); }
int32_t MenuAnyFlag00413DF3(void) {
    if (G00BDFA44 == 0 && G00BDFA48 == 0 && G00BDFA4C == 0 && (G00BDFA50 == 0 || G01271060 == 7) && G00BDFA58 == 0) return 0;
    return 1;
}

/* ---- запись состояния кнопок меню: байт состояния в записи, смещение зависит от режима ---- */
static void btn_state(int32_t p, int off1, int off2) {
    if (p != 0) return;
    if (G6_005FE9BC != 0) {
        if (G6_005FE9BC == 1) { UiPtr005FE9B8[off1] = 2; return; }
        if (G6_005FE9BC != 2) return;
    }
    UiPtr005FE9B8[off2] = 2;
}
void MenuBtn00414264(int32_t p) { btn_state(p, 0x14, 0x14); }
void MenuBtn00414376(int32_t p) { btn_state(p, 0x34, 0x24); }
void MenuBtn00414488(int32_t p) { btn_state(p, 0x54, 0x34); }
void MenuBtn0041459A(int32_t p) { btn_state(p, 0x74, 0x44); }

/* ---- затухание и листание ---- */
void SetFade0051707A(uint8_t r, uint8_t g, uint8_t b, int32_t d) {
    G6_00B5A838 = r; G6_00B5A839 = g; G6_00B5A83A = b; G6_00C557F8 = d; G6_00C55800 = 0;
}
void MenuPageNext00417F59(void) {
    SetFade0051707A(0, 0, 0, 0x32); G6_005FED9C = G6_005FED9C + 1; if (4 < G6_005FED9C) G6_005FED9C = 0;
    G6Call00418119(G6_005FED9C); G6Call00417CBB(); G005FEA54 = 1;
}
void MenuPagePrev00417FAC(void) {
    SetFade0051707A(0, 0, 0, 0x32); G6_005FED9C = G6_005FED9C - 1; if (G6_005FED9C < 0) G6_005FED9C = 4;
    G6Call00418119(G6_005FED9C); G6Call00417CBB(); G005FEA54 = 1;
}

/* ---- пулы индексов ---- */
int32_t PoolAlloc004A2C12(void) {
    int32_t i;
    if (D_01134528 < 100) { i = D_01134ec0[D_01134528]; D_01134528 = D_01134528 + 1; D_01134554[i * 6] = 1; }
    else i = -1;
    return i;
}
int32_t PoolNext004AC671(void) {
    int32_t i;
    if (G00553850 == 0 || 199 < S_011173C8) i = -1;
    else { i = (int32_t)S_010FAF40[S_011173C8]; S_011173C8 = S_011173C8 + 1; }
    return i;
}
int32_t PoolAlloc0051210C(void) {
    int32_t i;
    if (G6_00C56764 < 0x40) { i = G6_00C594A0[G6_00C56764]; G6_00C56764 = G6_00C56764 + 1; G6_00C5678C[i * 0x2d] = 0x10; G6_00C5678C[i * 0x2d + 8] = 0; G6_00C5678C[i * 0x2d + 0x12] = 0; }
    else i = -1;
    return i;
}

/* ---- обёртки с вызовами ---- */
void ShutdownAudio004183A3(void) {
    if (Q00B87E90 != 0) { Call00524873(); Call00524763(); }
    G6Call00523628(); G6Call0041A16C(); G6Call004D4663();
    G6_00B87EEC = 0; G6_00B87EFC = 0; G6Call0040C5BE(4);
}
void MenuBack005103EC(void) { G005F7E54 = 2; G6_00B87E20 = 0; G6Call0050E940(0); }
void SoundMenuIn00419814(void) { FnPtr01270E80(2); Call0042655A(G0054E540); G6_01270DE4(3); }
void SoundMenuOut0051082A(void) { FnPtr01270E80(2); Call0042655A(G6_005755C8); G6_01270DE4(3); }
void SoundMenuSave0051080E(void) { G6_005755C8 = Call0042655A(0); FnPtr01270E80(0); }
int32_t DrvCall004246D1(int32_t a) { return G00B1C0D4 == 0 ? 1 : G6_01270D20(a); }
int32_t DrvSetMode0042655A(int32_t a) { int32_t old = G6_00B1C224; G6_00B1C224 = a; G6_01270D28(a); return old; }
void ClearHandles005223BE(void) { G6_00BDF9C0 = 0; G6_00BDF9C4 = 0; G6Call004A2B70(); }
void StartAudio005233A0(void) { if (G6_00B91CF4 == 0 && G6_00B91D2C == 0) G6Call0048BA20(); }
void NoopFn00528455(void) { }
void InitSubsys004BA443(void) { G6Call004BA457(); G6Call004BA57A(); G6Call004BA64D(); }
void Fwd004D2D9F(int32_t a, int32_t b, int32_t c, int32_t d) { if (G00575F08 != 0) G6Call004D614A(a, b, c, d); }
void Reset004D600B(void) { G6Call004D5FFC(); G6Call00523628(); G6_00B20368 = 0; G6_00B20364 = 0; }
void MenuAddItem004DC8B0(uint8_t *item, int32_t flag) {
    item[3] = (flag == 0) ? 0 : 1; G6_00B2F30C[G6_00D0DDC0] = item; G6_00D0DDC0 = G6_00D0DDC0 + 1;
}
int32_t StepToward004E60C1(int32_t i) {
    if (G6_00D04A50[i] < G6_00562B70[i]) {
        G6_00D04A50[i] = (uint8_t)(G6_00D04A50[i] + 0x13);
        if (G6_00562B70[i] < G6_00D04A50[i]) G6_00D04A50[i] = G6_00562B70[i];
        return 1;
    }
    return 0;
}
uint32_t AngleToDir00514103(uint32_t a) {
    a &= 0xfff;
    if (a < 0x200) return 4;
    if (a < 0x600) return 2;
    if (a < 0xa00) return 8;
    if (a < 0xe00) return 1;
    if (a < 0x1000) return 4;
    return 0;
}
void ObjInit00514C43(uint8_t *o, uint16_t a, uint32_t b, uint32_t flags) {
    uint32_t z = 0, f = flags | 0x400;
    memcpy(o + 4, &a, 2); memcpy(o + 0x24, &b, 4); memcpy(o + 0x40, &z, 4); memcpy(o + 0xc, &f, 4);
}
int32_t TypeIsKnown00514F0A(const int16_t *p) { return (*p == 1 || *p == 2 || *p == 3) ? 1 : -1; }

/* ---- векторы (x,y,z, w = индекс 4 в float-массиве игры) ---- */
void VecAdd3_00526F7E(float *a, const float *b) { a[0] += b[0]; a[1] += b[1]; a[2] += b[2]; }
void VecNeg4_00527123(float *a) { a[4] = -a[4]; a[0] = -a[0]; a[1] = -a[1]; a[2] = -a[2]; }
void VecAdd4_0052715E(const float *a, const float *b, float *r) { r[4] = a[4] + b[4]; r[0] = a[0] + b[0]; r[1] = a[1] + b[1]; r[2] = a[2] + b[2]; }
void VecSub4_005271A8(const float *a, const float *b, float *r) { r[4] = a[4] - b[4]; r[0] = a[0] - b[0]; r[1] = a[1] - b[1]; r[2] = a[2] - b[2]; }
void MatIdentity3_0052614F(float *m) { for (int i = 0; i < 9; i++) m[i] = (i % 4 == 0) ? 1.0f : 0.0f; }

/* ---- титры, звук, буферы ---- */
void CreditsTick005193D4(void) {
    if (G6_00B5A8AC == 0) { G6_00B5A8AC = 0x1c2; G6_00575A70 = G6_00575A70 + 1; }
    G6_00B5A8AC = G6_00B5A8AC - 1;
}
int32_t CreditsNext00519D2C(void) {
    int32_t r = G6_00575A70 < G6_00B5A8B0 - 1;
    if (r) { G6Call00519D22(G6_00575A70 + 1); G6_005624A0 = 0xf; G6_00D11928 = 0xb4; }
    return r;
}
int32_t CreditsPrev00519D70(void) {
    if (G6_00575A70 == 0) { G6_00B5A8A0 = 0; G6Call00519D22(0); }
    else if (G6_00B5A8AC < 0x1b4) G6Call00519D22(G6_00575A70);
    else G6Call00519D22(G6_00575A70 - 1);
    G6_005624A0 = 0xf; G6_00D11928 = 0xb4; return 1;
}
void ResetPalette00519DF3(void) { G6Call00426580(0x18); G6Call00516EB4(0xff, 0xff, 0xff); G6_01270C34 = -1; }
void MenuClick004F8ACC(int32_t a) {
    if (G6_00B31F40 == 0) UiCall00523E50(a, 0xd, -1); else UiCall00523E50(a, 0xe, -1);
    G6_00B31F40 = ~G6_00B31F40;
}
void DrawTextLine004FBBC5(int32_t t) { if (G6_00B5A778 == 0) DrawSprite(0x140, 0xf0, (uint32_t)t, 0, 1, 0xff, 0xff, 0xff); }
void FreeBuf004FC57B(void) { if (G6_00C80C50 != 0) DebugFree(G6_00C80C50); G6_00C80C50 = 0; G6_00C81108 = 0; }
void FreeMapBufs004ECE1A(void) {
    if (G6_00D01268 != 0) { DebugFree(G6_00D01268); G6_00D01268 = 0; }
    if (G6_00D00208 != 0) { DebugFree(G6_00D00208); G6_00D00208 = 0; }
    if (G6_00CE0F20 != 0) { DebugFree(G6_00CE0F20); G6_00CE0F20 = 0; }
}
void FreeBufs00516E2E(void) {
    if (G6_00B5A840 != 0) { DebugFree(G6_00B5A840); G6_00B5A840 = 0; }
    if (G6_00B5A83C != 0) { DebugFree(G6_00B5A83C); G6_00B5A83C = 0; }
}
void Update005012A3(void) {
    G6Call00500E1D(0);
    if (G6_00B87EAC != 0 || G6_00B87EB0 != 0) G6Call00500E1D(0x41);
    if (G6_00B87EA0 == 0) G6Call00491360();
}
void ActorStep00494678(uint8_t *p) {
    if (p[0xb] == 0) { p[1] = 2; p[2] = 1; }
    else {
        uint32_t v = 0x23f;
        memcpy(G0113A6C4 + (uint32_t)p[0] * 0x148 + 0xfc, &v, 4);
        p[0xb] = (uint8_t)(p[0xb] - 1);
    }
}
int32_t StartFlyby004A05C0(void) {
    G6_01136920 = 0;
    if (G01271060 == 7) { G6_01136920 = 1; G6_011368C4 = 0; G6Call004A05FA(); return 0; }
    return -1;
}
void Dispatch0048A68E(int32_t i) {
    if ((P12_01145a60[i * 0x10] & 4) == 0) P40_UploadSlot(i, 0); else P40_UploadSlotPair(i, 0, 0);
}
void Dispatch0041D50E(int32_t a, int32_t b, int32_t c, int32_t d) {
    G6Call00422AE7(); G6_0054EF2C = d; if (G6_00A421F0 == 0) G6Call0041F57D(a, b, c);
}
int32_t Fwd0042482B(int32_t a, int32_t b, int32_t c, int32_t d) {
    return G00B1C0D8 == 1 ? G6Call0041D63B(a, b, c, d) : 1;
}
int32_t SoundGetPos005242A7(int32_t i) {
    uint32_t v;
    if (G6_00B91CF4 == 0 || G00575F40 == 0) return 0;
    if ((S_00BDC2A0[i * 0x34] & 1) == 0) return 0;
    memcpy(&v, &S_00BDC2A0[i * 0x34 + 0x28], 4); return (int32_t)v;
}
void SoundSetPos00523F8A(int32_t i, int32_t v) {
    if (G6_00B91CF4 != 0 && G00575F40 != 0 && (S_00BDC2A0[i * 0x34] & 0x11) != 0) {
        if (v == -1) memcpy(&v, &S_00BDC2A0[i * 0x34 + 0x24], 4);
        memcpy(&S_00BDC2A0[i * 0x34 + 0x28], &v, 4);
        S_00BDC2A0[i * 0x34] |= 4;
    }
}
void SoundPlay00523E50(uint32_t id, int32_t b, int32_t c) {
    int32_t h;
    if (G6_00B91CF4 != 0 && G00575F40 != 0) {
        if (0xfff < (int32_t)id) id = (id & 0xff) + (uint32_t)G6_00B91BC4[(int32_t)id >> 12];
        if ((int32_t)id < G6_00B91D34 && (h = G6Call00523CDA(id, b, 0, 0, 0)) != -1) SoundSetPos00523F8A(h, c);
    }
}
void Mask004D9028(uint32_t a, uint32_t b) {
    G6_00D10E40 = a == 0 ? 0 : (a | 1);
    G6_00D11800 = b == 0 ? 0 : ((b & 0x7ff) | 1);
}
void CursorWrap004D9478(void) {
    G6_00D117A4 = 0; G6_00D117A8 = G6_00D117A8 + 1;
    if ((G6_0125F3F0 - 8) / 8 < G6_00D117A8) G6_00D117A8 = 0;
}
void CursorSet004D94B7(int32_t a, int32_t b) {
    if (G6_00D117A4 < 0) G6_00D117A4 = G6_01270C28 / 8 - a; else G6_00D117A4 = a;
    if (G6_00D117A8 < 0) G6_00D117A8 = G6_0125F3F0 / 8 - b; else G6_00D117A8 = b;
}
