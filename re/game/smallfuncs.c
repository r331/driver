#include "smallfuncs.h"
#include <stdint.h>
GAME_VAR_DEF(sf_bytes_t, S_00549B04, 0x00549b04)
GAME_VAR_DEF(sf_bytes_t, S_0054E44C, 0x0054e44c)
GAME_VAR_DEF(sf_bytes_t, S_0054E44D, 0x0054e44d)
GAME_VAR_DEF(sf_bytes_t, S_0054E44E, 0x0054e44e)
GAME_VAR_DEF(sf_bytes_t, S_0054E6AC, 0x0054e6ac)
GAME_VAR_DEF(sf_bytes_t, S_0054E6AD, 0x0054e6ad)
GAME_VAR_DEF(sf_bytes_t, S_0054E6AE, 0x0054e6ae)
GAME_VAR_DEF(sf_bytes_t, S_00560A88, 0x00560a88)
GAME_VAR_DEF(int32_t, S_0057B658, 0x0057b658)
GAME_VAR_DEF(int32_t, S_0057B65C, 0x0057b65c)
GAME_VAR_DEF(int32_t, S_005FEA30, 0x005fea30)
GAME_VAR_DEF(int32_t, S_005FEA8C, 0x005fea8c)
GAME_VAR_DEF(uint32_t, S_00A421D8, 0x00a421d8)
GAME_VAR_DEF(uint8_t, S_00B31E40, 0x00b31e40)
GAME_VAR_DEF(uint8_t, S_00B31E41, 0x00b31e41)
GAME_VAR_DEF(uint8_t, S_00B31E42, 0x00b31e42)
GAME_VAR_DEF(uint8_t, S_00B31E43, 0x00b31e43)
GAME_VAR_DEF(int32_t, S_00B5A76C, 0x00b5a76c)
GAME_VAR_DEF(int32_t, S_00B5A770, 0x00b5a770)
GAME_VAR_DEF(int32_t, S_00B5A77C, 0x00b5a77c)
GAME_VAR_DEF(uint8_t, S_00B5A834, 0x00b5a834)
GAME_VAR_DEF(uint8_t, S_00B5A835, 0x00b5a835)
GAME_VAR_DEF(uint8_t, S_00B5A836, 0x00b5a836)
GAME_VAR_DEF(uint32_t, S_00B93E6C, 0x00b93e6c)
GAME_VAR_DEF(uint32_t, S_00B93E70, 0x00b93e70)
GAME_VAR_DEF(uint32_t, S_00B93E74, 0x00b93e74)
GAME_VAR_DEF(uint32_t, S_00BA5280, 0x00ba5280)
GAME_VAR_DEF(uint32_t, S_00BA52D4, 0x00ba52d4)
GAME_VAR_DEF(uint32_t, S_00BA5380, 0x00ba5380)
GAME_VAR_DEF(sf_bytes_t, S_00BDC2A0, 0x00bdc2a0)
GAME_VAR_DEF(sf_bytes_t, S_00BDC2A1, 0x00bdc2a1)
GAME_VAR_DEF(sf_ints_t, S_00BDCD00, 0x00bdcd00)
GAME_VAR_DEF(int32_t, S_00C808A0, 0x00c808a0)
GAME_VAR_DEF(sf_bytes_t, S_00D0CC60, 0x00d0cc60)
GAME_VAR_DEF(int32_t, S_00D0DDE0, 0x00d0dde0)
GAME_VAR_DEF(int32_t, S_00D11804, 0x00d11804)
GAME_VAR_DEF(int32_t, S_00D11878, 0x00d11878)
GAME_VAR_DEF(int32_t, S_00D1192C, 0x00d1192c)
GAME_VAR_DEF(uint8_t*, S_00D1240C, 0x00d1240c)
GAME_VAR_DEF(uint16_t*, S_00D12410, 0x00d12410)
GAME_VAR_DEF(int32_t, S_00D12414, 0x00d12414)
GAME_VAR_DEF(sf_bytes_t, S_010EA8A0, 0x010ea8a0)
GAME_VAR_DEF(sf_bytes_t, S_010FAF40, 0x010faf40)
GAME_VAR_DEF(sf_bytes_t, S_010FB0E0, 0x010fb0e0)
GAME_VAR_DEF(int32_t, S_010FFA24, 0x010ffa24)
GAME_VAR_DEF(int32_t, S_0110E144, 0x0110e144)
GAME_VAR_DEF(int32_t, S_011173C8, 0x011173c8)
GAME_VAR_DEF(int32_t, S_01136C74, 0x01136c74)
GAME_VAR_DEF(int32_t, S_01139A34, 0x01139a34)
GAME_VAR_DEF(sf_bytes_t, S_011443EA, 0x011443ea)
GAME_VAR_DEF(uint32_t, S_0127104C, 0x0127104c)
#define U8P(p,o)  ((uint8_t*)(p)+(o))
#define U32(p,o)  (*(uint32_t*)U8P(p,o))
#define I32(p,o)  (*(int32_t*)U8P(p,o))
#define U16(p,o)  (*(uint16_t*)U8P(p,o))
/* --- пустые --- */
void NoopFn0041F81E(void) {}
void NoopFn0041FA49(void) {}
void NoopFn0041FA50(void) {}
void NoopFn0041FA57(void) {}
void NoopFn0041FA7D(void) {}
void NoopFn0041FA8B(void) {}
void NoopFn0041FA92(void) {}
void NoopFn0041FAB9(void) {}
int32_t ReturnZero004D03FD(void) { return 0; }
int32_t ReturnZero004E3B19(void) { return 0; }
int32_t ReturnOne00519D22(void) { return 1; }
/* --- сеттеры полей структур --- */
void SetField24_00502779(uint8_t* p, int32_t v) { I32(p, 0x24) = v; }
void ClearField2C_00502680(uint8_t* p) { I32(p, 0x2c) = 0; }
void AddToCounter00519D09(int32_t v) { S_01136C74 += v; }
void ClearFlagByte0048FBBA(int32_t n) { S_011443EA[(n - 1) * 0x54] = 0; }
void ScriptSetWait004F5C72(int32_t* p, int32_t v) { p[0] = v; p[1] = 12; }
void ScriptSetWaitX50_004F5C58(int32_t* p, int32_t v) { p[0] = v * 0x32; p[1] = 12; }
void ToggleBit0051049E(void) { if (S_00C808A0 != 0) S_00B5A77C ^= 1; }
int32_t IsFlag80_00514E4C(uint8_t* p) { return (U32(p, 0xc) & 0x80) != 0; }
void SetFlagFromArg0041E1E4(int32_t v) { S_00A421D8 = (uint32_t)(v != 1); }
void SetLatchValue0050E940(int32_t v) { if (v == S_00B5A76C) S_00B5A770 = 1; S_00B5A76C = v; }
int32_t IsSlotActive00524473(int32_t i) { return (S_00BDC2A0[i * 0x34] & 0x11) != 0; }
int32_t TestBit0041B7AD(uint32_t n) { return (S_0127104C & (1u << (n & 31))) != 0; }
void SetRGB00516EB4(uint8_t r, uint8_t g, uint8_t b) { S_00B5A834 = r; S_00B5A835 = g; S_00B5A836 = b; }
void SlotSetOn0052432A(int32_t i) { if (-1 < i && i < 0x14) S_00BDC2A1[i * 0x34] = 1; }
void SlotSetOff0052434A(int32_t i) { if (-1 < i && i < 0x14) S_00BDC2A1[i * 0x34] = 0; }
/* --- стеки индексов (пулы) --- */
void PoolPush004AC6AC(uint16_t v) { S_011173C8 -= 1; ((uint16_t*)S_010FAF40)[S_011173C8] = v; }
void PoolPush004AC702(uint16_t v) { S_0110E144 -= 1; ((uint16_t*)S_010EA8A0)[S_0110E144] = v; }
void PoolPush004AC755(uint16_t v) { S_010FFA24 -= 1; ((uint16_t*)S_010FB0E0)[S_010FFA24] = v; }
int32_t PoolPop004AC726(void) {
    int32_t r;
    if (S_010FFA24 < 100) { r = ((int16_t*)S_010FB0E0)[S_010FFA24]; S_010FFA24++; } else r = -1;
    return r;
}
int32_t PoolPop004AC6D0(void) {
    int32_t r;
    if (S_0110E144 < 200) { r = ((int16_t*)S_010EA8A0)[S_0110E144]; S_0110E144++; } else r = -1;
    return r;
}
int32_t CounterDecrement004D97B8(void) {
    int32_t old = S_00D11804;
    if (0 < S_00D11804) S_00D11804--;
    return 0 < old;
}
int32_t AllocSlot00492508(void) {
    int32_t r;
    if (S_01139A34 == 8) r = -1; else { r = S_01139A34 + 0x14; S_01139A34++; }
    return r;
}
uint32_t PackRGB00503ECC(uint8_t* p) { return (uint32_t)I32(p, 0x14) << 16 | (uint32_t)I32(p, 0x10) << 8 | U32(p, 0xc); }
int32_t IsKeyOnly004E38B4(void) { return !(S_00B31E42 == 0 || S_00B31E40 != 0); }
int32_t IsKeyOnly004E38D9(void) { return !(S_00B31E43 == 0 || S_00B31E41 != 0); }
int32_t ExchangeTable00522F2A(int32_t i, int32_t v) { int32_t o = S_00BDCD00[i]; S_00BDCD00[i] = v; return o; }
void InitFlags004946DA(uint8_t* p) { I32(p, 0x3c) = 0; I32(p, 0x38) = 0; p[0x11] = 1; p[0x12] = 1; }
void WrapCounter004A3A80(uint8_t* p) {
    if (0x1d < I32(p, 0xc)) { U32(p, 0x10) &= 0xfffffeffu; I32(p, 0xc) = 0; }
}
void CopyVec3_005265BC(uint32_t* v) { S_00BA5280 = v[0]; S_00BA52D4 = v[1]; S_00BA5380 = v[2]; }
void CopyVec3_0052797A(uint32_t* v) { S_00B93E6C = v[0]; S_00B93E70 = v[1]; S_00B93E74 = v[2]; }
void NegateVec3_00526FB6(float* v) { v[0] = -v[0]; v[1] = -v[1]; v[2] = -v[2]; }
void NegateVec3_005270F6(float* v) { v[0] = -v[0]; v[1] = -v[1]; v[2] = -v[2]; }
void NegateVec3To_00526FE3(float* d, float* s) { d[0] = -s[0]; d[1] = -s[1]; d[2] = -s[2]; }
void ResetVec_005272C6(uint32_t* v) { v[4] = 0x3f800000u; v[2] = 0; v[1] = 0; v[0] = 0; }
void CopySlotTemplate004A1010(void) {
    uint32_t* s = (uint32_t*)(S_00560A88 + (size_t)S_00D1192C * 0x16c);
    uint32_t* d = (uint32_t*)S_00D0CC60;
    for (int i = 0; i < 0x5b; i++) d[i] = s[i];
}
/* --- опкоды скрипта (смещение указателя + флаги) --- */
int32_t ScriptOpSkipClear004D1111(void) { S_00D12414 += 2; I32(S_00D1240C, 0x44) = 0; return 1; }
int32_t ScriptOpSetBit4_004D13D8(void) { S_00D12414 += 2; U16(S_00D1240C, 0x48) |= 4; return 0; }
int32_t ScriptOpClearBit2_004D1402(void) { S_00D12414 += 2; *S_00D12410 &= 0xfffd; return 0; }
int32_t ScriptOpSetBit200_004D03D0(void) { S_00D12414 += 2; U16(S_00D1240C, 0x48) |= 0x200; return 1; }
int32_t ScriptOpSetBit2_004D0404(void) { S_00D12414 += 2; U16(S_00D1240C, 0x48) = (U16(S_00D1240C, 0x48) & 0xff7e) | 2; return 1; }
int32_t ScriptOpToggle10_004D1737(void) { S_00D12414 += 2; U16(S_00D1240C, 0x48) ^= 0x10; return 1; }
int32_t ScriptOpSkip4_004D1601(void) { S_00D12414 += 4; return 1; }
void RingAdvance004D7B36(void) { S_00D11878++; if (S_00D11878 == S_00D0DDE0) S_00D11878 = 0; }
/* --- подсветка пунктов меню (значения 2/3 в таблицах) --- */
void MenuRowsTo3_00404E52(void) { S_00549B04[(S_0057B658 * 2 + 1) * 0x10] = 3; S_00549B04[(S_0057B658 * 2 + 2) * 0x10] = 3; }
void MenuRowsIf0To2_00404E7E(int32_t f) {
    if (f == 0) { S_00549B04[(S_0057B65C * 2 + 1) * 0x10] = 2; S_00549B04[(S_0057B65C * 2 + 2) * 0x10] = 2; }
}
void SetColorRed00417A55(void) { S_0054E44C[S_005FEA30 * 0x10] = 0xff; S_0054E44D[S_005FEA30 * 0x10] = 0; S_0054E44E[S_005FEA30 * 0x10] = 0; }
void SetColorWhite00417AA2(void) { S_0054E44C[S_005FEA30 * 0x10] = 0xff; S_0054E44D[S_005FEA30 * 0x10] = 0xff; S_0054E44E[S_005FEA30 * 0x10] = 0xff; }
void SetColorRed0041A051(void) { S_0054E6AC[S_005FEA8C * 0x10] = 0xff; S_0054E6AD[S_005FEA8C * 0x10] = 0; S_0054E6AE[S_005FEA8C * 0x10] = 0; }
void SetColorWhite0041A085(void) { S_0054E6AC[S_005FEA8C * 0x10] = 0xff; S_0054E6AD[S_005FEA8C * 0x10] = 0xff; S_0054E6AE[S_005FEA8C * 0x10] = 0xff; }
