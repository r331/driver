/* ported74.c — assorted small functions (English overview): freeing a traffic record, cycling animated
   palette/texture rows, HUD reset, 8-bit to 16-bit texture conversion, render device selection, the fast
   octagonal distance P74_Dist, text-file number parsing, skid mark init and text-entry key scan.  All cdecl. */
#include "ported151.h"
#include "ported74.h"
#include <string.h>
#include "dik.h"   /* DirectInput scan codes used by P74_KeyScan */

#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P74_DistTab")
#undef P74_DistTab
#pragma push_macro("P74_DistTab") /*gvi*/
#undef P74_DistTab /*gvi*/
p74_dist_t P74_DistTab;
#pragma pop_macro("P74_DistTab") /*gvi*/
#pragma pop_macro("P74_DistTab")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P74_KeyA")
#undef P74_KeyA
#pragma push_macro("P74_KeyA") /*gvi*/
#undef P74_KeyA /*gvi*/
p74_keys_t P74_KeyA;
#pragma pop_macro("P74_KeyA") /*gvi*/
#pragma pop_macro("P74_KeyA")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P74_KeyB")
#undef P74_KeyB
#pragma push_macro("P74_KeyB") /*gvi*/
#undef P74_KeyB /*gvi*/
p74_keys_t P74_KeyB;
#pragma pop_macro("P74_KeyB") /*gvi*/
#pragma pop_macro("P74_KeyB")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P74_DevTab")
#undef P74_DevTab
#pragma push_macro("P74_DevTab") /*gvi*/
#undef P74_DevTab /*gvi*/
p74_dev_t P74_DevTab;
#pragma pop_macro("P74_DevTab") /*gvi*/
#pragma pop_macro("P74_DevTab")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P74_Cars")
#undef P74_Cars
#pragma push_macro("P74_Cars") /*gvi*/
#undef P74_Cars /*gvi*/
p74_cars_t P74_Cars;
#pragma pop_macro("P74_Cars") /*gvi*/
#pragma pop_macro("P74_Cars")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P74_C4DA58")
#undef P74_C4DA58
#pragma push_macro("P74_C4DA58") /*gvi*/
#undef P74_C4DA58 /*gvi*/
int32_t P74_C4DA58;
#pragma pop_macro("P74_C4DA58") /*gvi*/
#pragma pop_macro("P74_C4DA58")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P74_B5A858")
#undef P74_B5A858
#pragma push_macro("P74_B5A858") /*gvi*/
#undef P74_B5A858 /*gvi*/
p74_i5_t P74_B5A858;
#pragma pop_macro("P74_B5A858") /*gvi*/
#pragma pop_macro("P74_B5A858")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P74_B5A86C")
#undef P74_B5A86C
#pragma push_macro("P74_B5A86C") /*gvi*/
#undef P74_B5A86C /*gvi*/
p74_i5_t P74_B5A86C;
#pragma pop_macro("P74_B5A86C") /*gvi*/
#pragma pop_macro("P74_B5A86C")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P74_B5A880")
#undef P74_B5A880
#pragma push_macro("P74_B5A880") /*gvi*/
#undef P74_B5A880 /*gvi*/
p74_i5_t P74_B5A880;
#pragma pop_macro("P74_B5A880") /*gvi*/
#pragma pop_macro("P74_B5A880")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P74_C4D7A0")
#undef P74_C4D7A0
#pragma push_macro("P74_C4D7A0") /*gvi*/
#undef P74_C4D7A0 /*gvi*/
p74_i5_t P74_C4D7A0;
#pragma pop_macro("P74_C4D7A0") /*gvi*/
#pragma pop_macro("P74_C4D7A0")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P74_B5A89C")
#undef P74_B5A89C
#pragma push_macro("P74_B5A89C") /*gvi*/
#undef P74_B5A89C /*gvi*/
int32_t P74_B5A89C;
#pragma pop_macro("P74_B5A89C") /*gvi*/
#pragma pop_macro("P74_B5A89C")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P74_B5A894")
#undef P74_B5A894
#pragma push_macro("P74_B5A894") /*gvi*/
#undef P74_B5A894 /*gvi*/
uint8_t P74_B5A894;
#pragma pop_macro("P74_B5A894") /*gvi*/
#pragma pop_macro("P74_B5A894")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P74_C4D668")
#undef P74_C4D668
#pragma push_macro("P74_C4D668") /*gvi*/
#undef P74_C4D668 /*gvi*/
int32_t P74_C4D668;
#pragma pop_macro("P74_C4D668") /*gvi*/
#pragma pop_macro("P74_C4D668")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P74_C4BDE0")
#undef P74_C4BDE0
#pragma push_macro("P74_C4BDE0") /*gvi*/
#undef P74_C4BDE0 /*gvi*/
int32_t P74_C4BDE0;
#pragma pop_macro("P74_C4BDE0") /*gvi*/
#pragma pop_macro("P74_C4BDE0")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P74_C54D08")
#undef P74_C54D08
#pragma push_macro("P74_C54D08") /*gvi*/
#undef P74_C54D08 /*gvi*/
int32_t P74_C54D08;
#pragma pop_macro("P74_C54D08") /*gvi*/
#pragma pop_macro("P74_C54D08")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P74_SkidA")
#undef P74_SkidA
#pragma push_macro("P74_SkidA") /*gvi*/
#undef P74_SkidA /*gvi*/
p74_i4_t P74_SkidA;
#pragma pop_macro("P74_SkidA") /*gvi*/
#pragma pop_macro("P74_SkidA")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P74_SkidB")
#undef P74_SkidB
#pragma push_macro("P74_SkidB") /*gvi*/
#undef P74_SkidB /*gvi*/
p74_i4_t P74_SkidB;
#pragma pop_macro("P74_SkidB") /*gvi*/
#pragma pop_macro("P74_SkidB")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P74_SkidC")
#undef P74_SkidC
#pragma push_macro("P74_SkidC") /*gvi*/
#undef P74_SkidC /*gvi*/
p74_i4_t P74_SkidC;
#pragma pop_macro("P74_SkidC") /*gvi*/
#pragma pop_macro("P74_SkidC")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P74_SkidD")
#undef P74_SkidD
#pragma push_macro("P74_SkidD") /*gvi*/
#undef P74_SkidD /*gvi*/
p74_i4_t P74_SkidD;
#pragma pop_macro("P74_SkidD") /*gvi*/
#pragma pop_macro("P74_SkidD")
#endif
GAME_VAR_DEF(uint8_t *, P74_Skid, 0x00b5c90c)
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P74_Rows")
#undef P74_Rows
#pragma push_macro("P74_Rows") /*gvi*/
#undef P74_Rows /*gvi*/
p74_rows_t P74_Rows;
#pragma pop_macro("P74_Rows") /*gvi*/
#pragma pop_macro("P74_Rows")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P74_RowTab")
#undef P74_RowTab
#pragma push_macro("P74_RowTab") /*gvi*/
#undef P74_RowTab /*gvi*/
p74_rowtab_t P74_RowTab;
#pragma pop_macro("P74_RowTab") /*gvi*/
#pragma pop_macro("P74_RowTab")
#endif

#ifndef RE_HOOK_BUILD
#include "p74_data.h"
/* Native only: copies the initial values of the constant tables (distance factors, key maps) into their
   data-image variables. */
void P74_InitConsts(void) {
  memcpy(P74_DistTab, P74_DistInit, sizeof P74_DistTab);
  memcpy(P74_KeyA, P74_KeyAInit, sizeof P74_KeyA);
  memcpy(P74_KeyB, P74_KeyBInit, sizeof P74_KeyB);
}
#endif

/* P74_FreeTraffic — Game.exe 00493ece.  Releases traffic record i: clears its cop slot (first dword of the
   0xcd8-byte cop AI record, cop count G0112B284 - 1), calls GlobalSet004964E2 for state 9, clears state and
   flags (+1, +8, +0x15) and pushes i on the free-record stack (G2_ARR_01145940, count G2_01143600). */
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

/* P74_ShiftRows — Game.exe 004ffad8.  Colour cycling: for each of 16 entries {first a, last b, frame mask m}
   of P74_RowTab, when (frame & m) == 0 the values P74_Rows[a..b] rotate by one (the last becomes the first).
   Disabled while G6_00B5A778 != 0 or P13_00b201dc == 0.  Native skips entries with b < a (endless loop in
   the original). */
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
/* P74_ResetHud — Game.exe 005186ce.  Clears HUD/input state at level start: five 5-entry tables, counters,
   joystick axis values and the replay record counter.  TODO(RE): meaning of the individual P74_* tables. */
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

/* P74_Conv8to16 — Game.exe 004229fa.  Converts a 256x256 8-bit texture page to 16 bits through the 4-byte
   palette (B, G, R, x) using the surface channel shifts P24_[RGB]Shift[RL]; pitch = destination row bytes. */
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

/* P74_DevSelect — Game.exe 00424530.  Selects render device idx (enumerating devices on first use):
   device kind 0 = 3Dfx Glide (load the Glide exports), 1 = Direct3D (P151_InstallD3D(idx, a, b)), else none.
   Result in G00B1C0D4 (success) and G00B1C0D8 (1 = Direct3D).  Out-of-range idx -> 0. */
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

/* P74_Dist — Game.exe 004a7f0e.  Approximate distance from the player (P59_PosX/Z) to (x + ox/256, z + oz/256):
   big * P74_DistTab[small * 64 / big] / 128, where big/small are the larger/smaller of |dx|, |dz| — i.e.
   sqrt(1 + t^2) from a 65-entry table.  Divisions round toward zero (MSVC idiom kept). */
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

/* P74_ParseFloat — Game.exe 004a4f7d.  Parses "[-]float" from a text file line into camera float word idx
   (P68_CamF[3 - idx], idx 0..3).  Returns 1, or 0 with an "Expecting floating point value!" box. */
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

/* P74_ParseShorts — Game.exe 004a5afb.  Parses n comma-separated numbers into out (u16 each), then skips to the
   next line.  Returns the new position, or NULL after a "Comma Expected!" box. */
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
/* P74_SkidInit — Game.exe 0051d440.  Clears the four skid mark tables and finds the SKID icon; without it skid
   marks are disabled (P13_00575ebc = 0).  Shrinks the icon's texture rectangle by one texel at the top/bottom
   (TODO(RE): the +0xb / +0xc adjustment turns the rectangle into origin + size? unsure). */
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
/* P74_KeyScan — Game.exe 0040efd5.  Key scan for text entry: -3 = Escape, -2 = Enter, -1 = Backspace, else the
   character of the first pressed key from P74_KeyA (P74_KeyB with Caps Lock or Shift), 0 = none. */
int32_t P74_KeyScan(void) {
  const uint8_t *tab = P74_KeyA;
  if (IsKeyDown(DIK_ESCAPE) != 0) return -3;
  if (IsKeyDown(DIK_RETURN) != 0) return -2;
  if (IsKeyDown(DIK_BACK) != 0) return -1;
  if (A_00D04B00[DIK_CAPITAL] != 0 || A_00D04B00[DIK_LSHIFT] != 0 || A_00D04B00[DIK_RSHIFT] != 0) tab = P74_KeyB;
  for (int32_t i = 0; i < 0x100; i++)
    if (tab[i] != 0 && IsKeyDown(i) != 0) return tab[i];
  return 0;
}
