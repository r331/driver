#include "ported151.h"
#include "ported74.h"
#include <string.h>

GAME_VAR_DEF(p74_dist_t, P74_DistTab, 0x0055272c)
GAME_VAR_DEF(p74_keys_t, P74_KeyA, 0x0054ae10)
GAME_VAR_DEF(p74_keys_t, P74_KeyB, 0x0054af10)
GAME_VAR_DEF(p74_dev_t, P74_DevTab, 0x01270ec0)
GAME_VAR_DEF(p74_cars_t, P74_Cars, 0x0112e6b4)
GAME_VAR_DEF(int32_t, P74_C4DA58, 0x00c4da58)
GAME_VAR_DEF(p74_i5_t, P74_B5A858, 0x00b5a858)
GAME_VAR_DEF(p74_i5_t, P74_B5A86C, 0x00b5a86c)
GAME_VAR_DEF(p74_i5_t, P74_B5A880, 0x00b5a880)
GAME_VAR_DEF(p74_i5_t, P74_C4D7A0, 0x00c4d7a0)
GAME_VAR_DEF(int32_t, P74_B5A89C, 0x00b5a89c)
GAME_VAR_DEF(uint8_t, P74_B5A894, 0x00b5a894)
GAME_VAR_DEF(int32_t, P74_C4D668, 0x00c4d668)
GAME_VAR_DEF(int32_t, P74_C4BDE0, 0x00c4bde0)
GAME_VAR_DEF(int32_t, P74_C54D08, 0x00c54d08)
GAME_VAR_DEF(p74_i4_t, P74_SkidA, 0x00bdfae0)
GAME_VAR_DEF(p74_i4_t, P74_SkidB, 0x00bdfb10)
GAME_VAR_DEF(p74_i4_t, P74_SkidC, 0x00bdfab0)
GAME_VAR_DEF(p74_i4_t, P74_SkidD, 0x00bdfb00)
GAME_VAR_DEF(uint8_t *, P74_Skid, 0x00b5c90c)
GAME_VAR_DEF(p74_rows_t, P74_Rows, 0x012577e0)
GAME_VAR_DEF(p74_rowtab_t, P74_RowTab, 0x00572a80)

#ifndef RE_HOOK_BUILD
#include "p74_data.h"
void P74_InitConsts(void) {
  memcpy(P74_DistTab, P74_DistInit, sizeof P74_DistTab);
  memcpy(P74_KeyA, P74_KeyAInit, sizeof P74_KeyA);
  memcpy(P74_KeyB, P74_KeyBInit, sizeof P74_KeyB);
}
#endif

/* 00493ece: запись трафика (0x54 байта): +1 состояние (9 — особое), +5 номер слота машины (1-based), +8, +0x15 — флаги.
   Свободные записи лежат стеком в 01145940, счётчик 01143600. */
void P74_FreeTraffic(int32_t i) {
  uint8_t *r = (uint8_t *)TrafficRecs + i * 0x54;
  uint8_t slot = r[5];
  if (slot != 0) {
    if ((int32_t)slot - 1 < 16) memset(P74_Cars + (slot - 1) * 0xcd8, 0, 4);
    G0112B284 = G0112B284 - 1;
    r[5] = 0;
  }
  if (r[1] == 9) GlobalSet004964E2();
  r[1] = 0; r[8] = 0; r[0x15] = 0;
  G2_01143600 = G2_01143600 - 1;
  if ((uint32_t)G2_01143600 < 0x1000) G2_ARR_01145940[G2_01143600] = i;
}

/* 004ffad8: для каждой из 16 записей (начало a, конец b, маска m) при (кадр & m) == 0 значения a..b сдвигаются на одну позицию вверх,
   последнее становится первым (в оригинале при b < a цикл бесконечен — тут запись пропускается). */
void P74_ShiftRows(void) {
  if (G6_00B5A778 != 0 || P13_00b201dc == 0) return;
  for (int32_t k = 0; k < 16; k++) {
    int32_t a = P74_RowTab[k * 3], b = P74_RowTab[k * 3 + 1], m = P74_RowTab[k * 3 + 2];
    if (a == 0 || ((P62_Frame & m) != 0)) continue;
    int32_t n = b - a;
    if (b < 0 || b >= 0x1000 || n < 0 || n > b) continue;
    int32_t *p = &P74_Rows[b];
    int32_t saved = *p;
    while (n != 0) { *p = p[-1]; p--; n--; }
    *p = saved;
  }
}

/* 005186ce */
void P74_ResetHud(void) {
  P74_C4DA58 = P62_Frame + 1;
  for (int i = 0; i < 5; i++) { P74_B5A858[i] = 0; P74_B5A86C[i] = 0; P74_B5A880[i] = 0; P74_C4D7A0[i] = 0; }
  P74_B5A89C = 0;
  G6_00B5A8A0 = 0;
  P47_CamB = 0;
  if (G8_00B87EAC != 0) P74_C4D668 = 0;
  P36_JoyX = 0;
  P21_AxisValue = 0;
  P74_C4BDE0 = 0;
  P74_C54D08 = 0;
  P55_RecCnt = 0;
  P74_B5A894 = 1;
}

/* 004229fa: палитра — 4 байта на цвет (B,G,R,x); байт альфы 0xff в оригинале никогда не совпадает (индекс байтовый, сравнение с -1) */
void P74_Conv8to16(const uint8_t *src, const uint8_t *pal, uint16_t *dst, int32_t pitch) {
  for (int row = 0; row < 256; row++) {
    for (int col = 0; col < 256; col++) {
      const uint8_t *c = pal + (uint32_t)(*src++) * 4;
      uint16_t v = 0;
      v |= (uint16_t)(((uint32_t)(c[2] >> (P24_RShiftR & 31))) << (P24_RShiftL & 31));
      v |= (uint16_t)(((uint32_t)(c[1] >> (P24_GShiftR & 31))) << (P24_GShiftL & 31));
      v |= (uint16_t)(((uint32_t)(c[0] >> (P24_BShiftR & 31))) << (P24_BShiftL & 31));
      *dst = v;
      dst++;
    }
    dst = (uint16_t *)((uint8_t *)dst + (pitch - 0x200));
  }
}

/* 00424530 (метка __thiscall ложная: первый аргумент — номер устройства) */
void P74_DevSelect(int32_t idx, int32_t a, int32_t b) {
  if (P69_DevOn == 0) {
    P74_Fn41CE90();
    P74_Fn424B70();
    if (P42_DevCount > 0) P69_DevOn = 1;
  }
  if (idx < 0 || idx >= P42_DevCount) idx = 0;
  int32_t kind = idx < 16 ? P74_DevTab[idx * 19] : 2;
  if (kind == 0) {
    G00B1C0D4 = P33_LoadGlideProcs();
    G00B1C0D8 = 0;
  } else if (kind == 1) {
    G00B1C0D4 = P151_InstallD3D(idx, a, b);
    G00B1C0D8 = 1;
  } else {
    G00B1C0D4 = 0;
    G00B1C0D8 = 0;
  }
}

/* 004a7f0e: dx, dz — разности с положением игрока (в клетках; p3/p4 — дробная часть /256), результат ≈ max + min*k/128 по таблице */
int32_t P74_Dist(int32_t x, int32_t z, int32_t ox, int32_t oz) {
  int32_t dx = x - (P59_PosX + ((ox + ((ox >> 31) & 0xff)) >> 8));
  int32_t dz = z - (P59_PosZ + ((oz + ((oz >> 31) & 0xff)) >> 8));
  if (dx < 0) dx = -dx;
  if (dz < 0) dz = -dz;
  int32_t big = dx, small = dz;
  if (dx < dz) { big = dz; small = dx; }
  if (big == 0) return 0;
  int32_t idx = (int32_t)((uint32_t)small << 6) / big;
  if (idx < 0 || idx > 64) idx = 64;
  int32_t t = (int32_t)((uint32_t)big * (uint32_t)P74_DistTab[idx]);
  return (t + ((t >> 31) & 0x7f)) >> 7;
}

/* 004a4f7d: число "[-]%f" -> слово камеры (0x0113425c - idx*4: idx 0..3) */
int32_t P74_ParseFloat(char *s, int32_t idx) {
  int32_t neg = 0;
  float f = 0;
  if (*s == '-') { s++; neg = 1; }
  int32_t r = g_sscanf(s, "%f", &f);
  P51_SkipNumber(&s);
  if (r == 0 || r == -1) { P26_ErrorInLine("Expecting floating point value!"); return 0; }
  if (neg) f = -f;
  if (idx >= 0 && idx <= 3) memcpy(&P68_CamF[3 - idx], &f, 4);
  return 1;
}

/* 004a5afb: n коротких чисел, разделитель запятая; после последнего — продолжение разбора (004a59c6) */
char *P74_ParseShorts(char *s, uint16_t *out, int32_t n) {
  for (;;) {
    for (;;) {
      if (n == 0) return SkipLine004A59C6(s);
      while (*s == ' ' || *s == '\t') s++;
      n--;
      P74_Fn4A4D84(&s, 0, 0);
      *out++ = P68_CamI0;
      if (n >= 1) break;
    }
    while (*s == ' ' || *s == '\t') s++;
    char c = *s++;
    if (c != ',') break;
  }
  P26_ErrorInLine("Comma Expected!");
  return NULL;
}

/* 0051d440 */
void P74_SkidInit(void) {
  for (int i = 0; i < 4; i++) { P74_SkidA[i] = 0; P74_SkidB[i] = 0; P74_SkidC[i] = 0; P74_SkidD[i] = 0; }
  P74_Skid = P56_FindIcon("SKID");
  if (P74_Skid == 0) { P13_00575ebc = 0; return; }
  P74_Skid[10] = (uint8_t)(P74_Skid[10] + 1);
  P74_Skid[0xc] = (uint8_t)(P74_Skid[0xc] - 1);
  P74_Skid[0xb] = (uint8_t)(P74_Skid[0xb] + P74_Skid[9]);
  P74_Skid[0xc] = (uint8_t)(P74_Skid[0xc] + P74_Skid[10]);
}

/* 0040efd5 */
int32_t P74_KeyScan(void) {
  const uint8_t *tab = P74_KeyA;
  if (IsKeyDown(1) != 0) return -3;
  if (IsKeyDown(0x1c) != 0) return -2;
  if (IsKeyDown(0xe) != 0) return -1;
  if (A_00D04B00[0x3a] != 0 || A_00D04B00[0x2a] != 0 || A_00D04B00[0x36] != 0) tab = P74_KeyB;
  for (int32_t i = 0; i < 0x100; i++)
    if (tab[i] != 0 && IsKeyDown(i) != 0) return tab[i];
  return 0;
}
