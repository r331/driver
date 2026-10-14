#include "ported7.h"
#include <string.h>
GAME_VAR_DEF(g8_bytes_t, A_005D57AE, 0x005d57ae)
GAME_VAR_DEF(g8_bytes_t, A_0054DFC5, 0x0054dfc5)
GAME_VAR_DEF(g8_bytes_t, A_006017C0, 0x006017c0)
GAME_VAR_DEF(int32_t, G8_00A4217C, 0x00a4217c)
GAME_VAR_DEF(int32_t, G8_011EFFE4, 0x011effe4)
GAME_VAR_DEF(g8_bytes_t, A_012083C0, 0x012083c0)
GAME_VAR_DEF(g8_bytes_t, A_01146F20, 0x01146f20)
GAME_VAR_DEF(g8_bytes_t, A_011443E0, 0x011443e0)
GAME_VAR_DEF(int32_t, G8_00575EE4, 0x00575ee4)
GAME_VAR_DEF(g8_bytes_t, A_01134540, 0x01134540)
GAME_VAR_DEF(g8_bytes_t, A_010F51C8, 0x010f51c8)
GAME_VAR_DEF(g8_bytes_t, A_010EA8A0, 0x010ea8a0)
GAME_VAR_DEF(int32_t, G8_0110E144, 0x0110e144)
GAME_VAR_DEF(g8_bytes_t, A_0110B040, 0x0110b040)
GAME_VAR_DEF(g8_bytes_t, A_0110E2E0, 0x0110e2e0)
GAME_VAR_DEF(g8_bytes_t, A_011171C0, 0x011171c0)
GAME_VAR_DEF(g8_bytes_t, A_01123302, 0x01123302)
GAME_VAR_DEF(g8_bytes_t, A_010FFB60, 0x010ffb60)
GAME_VAR_DEF(int32_t, G8_0110B024, 0x0110b024)
GAME_VAR_DEF(g8_bytes_t, A_010EA620, 0x010ea620)
GAME_VAR_DEF(g8_bytes_t, A_010DE120, 0x010de120)
GAME_VAR_DEF(int32_t, G8_00DBB450, 0x00dbb450)
GAME_VAR_DEF(g8_bytes_t, A_00D132C0, 0x00d132c0)
GAME_VAR_DEF(int32_t, G8_00D17B0C, 0x00d17b0c)
GAME_VAR_DEF(g8_bytes_t, A_00B20330, 0x00b20330)
GAME_VAR_DEF(int32_t, G8_00B20344, 0x00b20344)
GAME_VAR_DEF(g8_bytes_t, A_00B20310, 0x00b20310)
GAME_VAR_DEF(g8_bytes_t, A_00D11830, 0x00d11830)
GAME_VAR_DEF(int32_t, G8_00B20368, 0x00b20368)
GAME_VAR_DEF(int32_t, G8_00B2034C, 0x00b2034c)
GAME_VAR_DEF(int32_t, G8_00D118C0, 0x00d118c0)
GAME_VAR_DEF(int32_t, G8_00B87EAC, 0x00b87eac)
GAME_VAR_DEF(int32_t, G8_00B87EB0, 0x00b87eb0)
GAME_VAR_DEF(int32_t, G8_00D11800, 0x00d11800)
GAME_VAR_DEF(int32_t, G8_00D10E40, 0x00d10e40)
GAME_VAR_DEF(g8_bytes_t, A_00D04B00, 0x00d04b00)
GAME_VAR_DEF(g8_bytes_t, A_00D044E0, 0x00d044e0)
GAME_VAR_DEF(g8_bytes_t, A_00C8198C, 0x00c8198c)
GAME_VAR_DEF(int32_t, G8_00B91CF4, 0x00b91cf4)
GAME_VAR_DEF(int32_t, G8_00575F40, 0x00575f40)
GAME_VAR_DEF(g8_bytes_t, A_00BDC2A0, 0x00bdc2a0)
GAME_VAR_DEF(g8_bytes_t, A_00B93E58, 0x00b93e58)
GAME_VAR_DEF(int32_t, G8_00C56710, 0x00c56710)
GAME_VAR_DEF(g8_bytes_t, A_00C56780, 0x00c56780)
GAME_VAR_DEF(uint16_t, G8_0057A0E2_u16, 0x0057a0e2)
GAME_VAR_DEF(uint16_t, G8_0057A0E0_u16, 0x0057a0e0)
uint8_t ScanSlot_0040AAE2(int32_t p) { for (int32_t i = 0; i <= 0xff; i++) { uint16_t v; memcpy(&v, &A_005D57AE[i*8 + p*0x806], 2); if (v != 0) return A_005D57AE[i*8 + p*0x806 + 7]; } return 0; }
void SetHiliteBits_0041621C(int32_t a, int32_t c) { for (int32_t i = 0; i < a; i++) A_0054DFC5[i*0x10] &= 0xf7; for (int32_t i = a; i <= c; i++) A_0054DFC5[i*0x10] |= 8; }
void InitIdentityPalette_0041D8E9(void) { for (int32_t i = 0; i < 0x100; i++) { A_006017C0[i*4] = (uint8_t)i; A_006017C0[i*4+1] = (uint8_t)i; A_006017C0[i*4+2] = (uint8_t)i; A_006017C0[i*4+3] = 2; } G8_00A4217C = 0; }
int32_t MaskShift_00421C1D(uint32_t m) { int32_t n; if (m == 0) return 8; while ((m & 1) == 0) m >>= 1; n = 0; while ((m & 1) != 0) { m >>= 1; n++; } return 8 - n; }
void AddEntry_00426ABC(const uint32_t *p, uint32_t w, int32_t a, int32_t c, int32_t d) { if (G8_011EFFE4 != 0x14) { uint8_t *e = &A_012083C0[G8_011EFFE4 * 0x1c]; float fa = (float)a, fc = (float)c, fd = (float)d; G8_011EFFE4++; memcpy(e, p, 12); memcpy(e+12, &w, 4); memcpy(e+16, &fa, 4); memcpy(e+20, &fc, 4); memcpy(e+24, &fd, 4); } }
int32_t FindFreeEven_0048A4E6(void) { for (int32_t i = 0; i <= 0x3f; i += 2) if ((A_01146F20[i*0x1c] & 7) == 0) return i; return -1; }
int32_t CountByOwner_0048F2E7(int32_t owner) { int32_t cnt = 0; for (int32_t i = 0; i < G8_00575EE4; i++) { int32_t v; memcpy(&v, &A_011443E0[i*0x54 + 0x28], 4); if (A_011443E0[i*0x54 + 1] != 0 && v == owner) cnt++; } return cnt; }
int32_t FindSlot_004A2DB5(int32_t a, int32_t c) { for (int32_t i = 0; i < 100; i++) { uint32_t f; int32_t x, y; memcpy(&x, &A_01134540[i*24+12], 4); memcpy(&y, &A_01134540[i*24+16], 4); memcpy(&f, &A_01134540[i*24+20], 4); if ((f & 1) != 0 && x == a && y == c) return 1; } return 0; }
const uint8_t *SkipToIdentStart_004A596B(const uint8_t *p) { for (; (*p < 0x41 || (0x5a < *p && *p < 0x61) || 0x7a < *p) && *p != 0x5f && *p != 0x23; p++) {} return p; }
void FillThresholds_004A6370(uint8_t *p) { int32_t v = 0x2aa; for (int32_t i = 0; i < 8; i++) { memcpy(p + 0x18 + i*4, &v, 4); v += 0x40; } v = 0x7fffffff; memcpy(p + 0x18 + 32, &v, 4); }
void ResetSlots_004AB712(void) { for (int32_t i = 0; i < 200; i++) { uint16_t z = 0, ii = (uint16_t)i; uint32_t z4 = 0; memcpy(&A_010F51C8[i*0x78 + 6], &z, 2); memcpy(&A_010F51C8[i*0x78 + 4], &ii, 2); memcpy(&A_010F51C8[i*0x78], &z4, 4); memcpy(&A_010EA8A0[i*2], &ii, 2); } G8_0110E144 = 0; }
void ClearTables_004AB780(void) { memset(&A_0110B040[0], 0, 0x41*8); memset(&A_0110E2E0[0], 0, 0x41*8); memset(&A_011171C0[0], 0, 0x41*8); }
int32_t FindOrAdd_004BB11F(int32_t id) { for (int32_t i = 0; i < 0x1e; i++) { int32_t v; memcpy(&v, &A_01123302[i*0x28 + 2], 4); if (v == id) { uint16_t one = 1; memcpy(&A_01123302[i*0x28], &one, 2); return i; } } if (G8_0110B024 < 0x1e) { memcpy(&A_010FFB60[G8_0110B024*4], &id, 4); G8_0110B024++; } return -1; }
void ClearEntry_004BF8A1(int32_t id) { for (int32_t i = 0; i < 0x20; i++) { int32_t v; memcpy(&v, &A_010EA620[i*0xc + 4], 4); if (v == id) { memset(&A_010EA620[i*0xc], 0, 4); memset(&A_010EA620[i*0xc + 4], 0, 4); A_010EA620[i*0xc + 8] = 0; A_010EA620[i*0xc + 9] = 0; return; } } }
void AddUnique_004C1F9B(int32_t id) { for (int32_t i = 0; i < G8_00DBB450; i++) { int32_t v; memcpy(&v, &A_010DE120[i*4], 4); if (v == id) return; } memcpy(&A_010DE120[G8_00DBB450*4], &id, 4); G8_00DBB450++; }
void PushEntry_004CC784(const uint32_t *p, uint8_t a, uint8_t c) { if (G8_00D17B0C != 100) { uint8_t *e = &A_00D132C0[G8_00D17B0C * 0x48]; memcpy(e, p, 12); e[0x10] = a; e[0x11] = c; G8_00D17B0C++; } }
void SetFirstFree_004D6190(int32_t v) { for (int32_t i = G8_00B20344; i <= 3; i++) { int32_t cur; memcpy(&cur, &A_00B20330[i*4], 4); if (cur == -1) { memcpy(&A_00B20330[i*4], &v, 4); return; } } }
void CopyTable_004D6E9F(void) { for (int32_t i = 0; i < G8_00B20368; i++) { memcpy(&A_00B20310[i*8], &A_00D11830[i*4], 4); memset(&A_00B20310[i*8 + 4], 0, 4); } G8_00B2034C = 0; }
uint32_t Rand_004D9078(void) { uint32_t v = (uint32_t)G8_00D118C0; if (G8_00B87EAC == 0 && G8_00B87EB0 == 0) { v = (uint32_t)G8_00D11800 ^ ((uint32_t)G8_00D11800 >> 15); G8_00D11800 = (int32_t)((v << 17) ^ v); G8_00D10E40 = (int32_t)((uint32_t)G8_00D10E40 * 0x10dcd); v = (uint32_t)G8_00D10E40 ^ (uint32_t)G8_00D11800; } return v & 0x7fffffff; }
int32_t AnyKeyHeld_004E3871(void) { for (int32_t i = 0; i <= 0xff; i++) if ((A_00D04B00[i] & 0x80) != 0) return 1; return 0; }
void PushHistory_004E5938(int32_t v) { int32_t cur; memcpy(&cur, &A_00D044E0[0], 4); if (v != cur) { for (int32_t i = 0x13; i >= 0; i--) memmove(&A_00D044E0[(i+1)*4], &A_00D044E0[i*4], 4); memcpy(&A_00D044E0[0], &v, 4); } }
void SetObjState_00514C72(uint8_t *p, uint16_t a, uint32_t c, uint32_t d, uint32_t e) { uint32_t f; memcpy(p + 4, &a, 2); memcpy(p + 0x24, &c, 4); memcpy(p + 0x40, &e, 4); f = d | 0x80; memcpy(p + 0xc, &f, 4); }
void InitObjState_00514BC7(uint8_t *p, int32_t mode, uint32_t arg) { uint16_t z16 = 0; uint32_t z = 0, f, t, w; memcpy(p + 4, &z16, 2); memcpy(p + 0x24, &z, 4); memcpy(p + 0x40, &z, 4); memcpy(&f, p + 0xc, 4); f &= 0xfffffb7f; memcpy(p + 0xc, &f, 4); memcpy(p + 0x1c, &mode, 4); memcpy(p + 0x20, &arg, 4); memcpy(&t, &A_00C8198C[mode*4], 4); memcpy(p + 0x2c, &t, 4); memcpy(p + 0x34, &z, 4); w = (mode == 2) ? 2 : 1; memcpy(p + 0x30, &w, 4); }
void ResetObjState_00514E99(uint8_t *p) { int16_t s; int32_t m; uint32_t o, t, z = 0, one = 1, f; uint16_t z16 = 0; memcpy(&s, p + 4, 2); m = s; memcpy(p + 0x1c, &m, 4); memcpy(&o, p + 0x24, 4); memcpy(p + 0x20, &o, 4); memcpy(p + 4, &z16, 2); memcpy(p + 0x24, &z, 4); memcpy(&t, &A_00C8198C[m*4], 4); memcpy(p + 0x2c, &t, 4); memcpy(p + 0x30, &one, 4); memcpy(p + 0x34, &z, 4); memcpy(p + 0x50, &z, 4); memcpy(&f, p + 0xc, 4); f &= 0xffffff7f; memcpy(p + 0xc, &f, 4); }
void InitSoundVolumes_00523C56(void) { if (G8_00B91CF4 == 0 || G8_00575F40 == 0) for (int32_t i = 0; i < 0x14; i++) { uint16_t v = 0xd8f0; memcpy(&A_00BDC2A0[i*0x34 + 0x2e], &v, 2); } }
void SoundLoop_0052422D(int32_t i, int32_t v) { if (G8_00B91CF4 != 0 && G8_00575F40 != 0 && (A_00BDC2A0[i*0x34] & 0x11) != 0) { if (v == 0) A_00BDC2A0[i*0x34] &= 0xdf; else { memcpy(&A_00BDC2A0[i*0x34 + 0x1c], &v, 4); A_00BDC2A0[i*0x34] |= 0x20; } } }
void Lerp4_00527885(const float *a, const float *c, float t, float *o) { o[4] = (c[4] - a[4]) * t + a[4]; o[0] = (c[0] - a[0]) * t + a[0]; o[1] = (c[1] - a[1]) * t + a[1]; o[2] = (c[2] - a[2]) * t + a[2]; }
void CopyShort9_005278FB(const int16_t *p) { memcpy(&A_00B93E58[0], p, 18); }
long double Dot4_005270BD(const float *a, const float *c) { return (long double)a[2] * c[2] + (long double)a[1] * c[1] + (long double)a[0] * c[0] + (long double)a[4] * c[4]; }
void CountActive_005120A7(void) { G8_00C56710 = 0; for (int32_t i = 0; i < 0x40; i++) { uint16_t t; uint32_t f; memcpy(&t, &A_00C56780[i*0xb4], 2); memcpy(&f, &A_00C56780[i*0xb4 + 12], 4); if ((f & 0x10) != 0 && t == 3) G8_00C56710++; } }
void InitFpuCw_005283E2(void) { G8_0057A0E2_u16 = 0x37f; G8_0057A0E0_u16 = 0xc7f; }
