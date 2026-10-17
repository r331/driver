#include <stdlib.h>
#include <stdio.h>
#include <math.h>
/* v1.87: ported142 — см. ported142.h.
   004a7fec — коп rec[5] (запись 0112da00 + (n−1)·0xcd8, машина 0113a6c4 + rec[0]·0x148): при 0112b268 == 0 или 00c824a0 — газ 0;
     выбывший коп (+0xcc4 == 1) — газ 0, таймер +0xcd4 −= 0.01; сумма повреждений +0x11c..+0x130 (если 0112d9d0 == 0) > 00575ee0 —
     выбыл; иначе счётчики застревания (+0x30, +0x58 ≥ 0xc9 — выбыл), разворот (+0x38 = 0x16), расстояние 004a7f0e, цель —
     упреждение игрока (12000) или точка пути 004a7aa7, сглаживание по истории +0xc74..+0xcb0, выбор режима руления 0..3
     (таблица 00552770 по 00b87e2c), газ ±(00b87e2c+8)·0x400·(0112b2b8 + 00d11a5c·011340c4 >> 12), руль ±200 к +0xfc;
     каждый 8-й кадр (00d118c0 % 8 == n−1) — 004a742a и курс по пути 004daac7.
   004df024 — состояние 0x64 байта на стеке (+0x14 позиция, +0x20 скорость, +0x30 сила, +0x40 угл. скорость, +0x50 момент,
     +0x60 флаг) — в native массив st[25]; маркер 00d02630: отталкивание от 00d02650/58 (ftol), при 00d02644 — повреждения 0xfff;
     контакт 12 (4 при +0xc > 0x800) точек кузова модели 00d0cc60 + тип·0x16c (+0x104) с землёй 004dd262, затем 4 колеса (+0xe0):
     подвеска, боковая сила (таблица синусов 00576f10), газ/тормоз/ручник, звук удара колеса игрока (00b2ea38), 004e0fd4.
   004dacee — 004defd1 (004df024 для всех), 004deb99; интеграция скорости/вращения (кватернион +0x30..+0x3c) и 004da8d9;
     4 × 2 подшага: 004dab80 → 00d0de00/00d0eb80, попарные столкновения 00499bb2 (|d| ≤ 0x4b0) с импульсами и повреждениями
     0049aa14, искры/дым 004b955c/004b8d49, звук 00523cda, 0048f899; полушаг 00d06a20 и шаг (>>4); курс +0x100, углы +0xe8..+0xec,
     копии позиции/скорости, точки колёс +0x88 (004dd262).
   Отступления native: 004a7fec — rec[5] вне 1..8 или машина вне таблицы — выход; деление на 0 (в оригинале исключение) — 0;
     неинициализированные в оригинале 2-е/4-е слова цели (ветка 0x333) — 0. 004df024/004dacee — байт 011443e5/011443e2 записи
     трафика для объекта 0 (в оригинале чтение перед таблицей) — 0; тип модели вне 00d0cc60 (0x4000) — точки (0, 0, 0);
     деление на 0 в 004df024 (сумма квадратов/знаменатель) — 0. */
#include "ported142.h"
#include "cartab.h"
#include "director.h"
#include "directorstorage.h"
#include "reptr.h"
#include "ported4.h"
#include "ported6.h"
#include "ported7.h"
#include "ported8.h"
#include "ported12.h"
#include "ported14.h"
#include "ported17.h"
#include "ported35.h"
#include "ported44.h"
#include "ported46.h"
#include "ported48.h"
#include "ported56.h"
#include "ported58.h"
#include "ported59.h"
#include "ported62.h"
#include "ported74.h"
#include "ported76.h"
#include "ported88.h"
#include "ported94.h"
#include "ported95.h"
#include "ported97.h"
#include "ported98.h"
#include "ported99.h"
#include "ported102.h"
#include "ported103.h"
#include "ported107.h"
#include "ported112.h"
#include "ported114.h"
#include "ported125.h"
#include "ported128.h"
#include "ported140.h"
#include "smallfuncs.h"
#include "smallfuncs2.h"
#include "menustate.h"
#include "uihandlers3.h"
#include "uihandlers4.h"
#include "widgets.h"
#include <string.h>

#ifndef RE_HOOK_BUILD
int plat_frame_no(void);   /* v2.29: номер показанного кадра — для журналов отладки */
#endif
#ifndef RE_HOOK_BUILD
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P142_CopNoDmg")
#undef P142_CopNoDmg
#pragma push_macro("P142_CopNoDmg") /*gvi*/
#undef P142_CopNoDmg /*gvi*/
int32_t P142_CopNoDmg;
#pragma pop_macro("P142_CopNoDmg") /*gvi*/
#pragma pop_macro("P142_CopNoDmg")
#endif
#pragma push_macro("P142_CopDmgMax") /*gvi*/
#undef P142_CopDmgMax /*gvi*/
int32_t P142_CopDmgMax = 7000;                    /* .data 00575ee0 */
#pragma pop_macro("P142_CopDmgMax") /*gvi*/
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P142_B278")
#undef P142_B278
#pragma push_macro("P142_B278") /*gvi*/
#undef P142_B278 /*gvi*/
int32_t P142_B278;
#pragma pop_macro("P142_B278") /*gvi*/
#pragma pop_macro("P142_B278")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P142_B27C")
#undef P142_B27C
#pragma push_macro("P142_B27C") /*gvi*/
#undef P142_B27C /*gvi*/
int32_t P142_B27C;
#pragma pop_macro("P142_B27C") /*gvi*/
#pragma pop_macro("P142_B27C")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P142_B2AC")
#undef P142_B2AC
#pragma push_macro("P142_B2AC") /*gvi*/
#undef P142_B2AC /*gvi*/
int32_t P142_B2AC;
#pragma pop_macro("P142_B2AC") /*gvi*/
#pragma pop_macro("P142_B2AC")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P142_B2B8")
#undef P142_B2B8
#pragma push_macro("P142_B2B8") /*gvi*/
#undef P142_B2B8 /*gvi*/
int32_t P142_B2B8;
#pragma pop_macro("P142_B2B8") /*gvi*/
#pragma pop_macro("P142_B2B8")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P142_340C0")
#undef P142_340C0
#pragma push_macro("P142_340C0") /*gvi*/
#undef P142_340C0 /*gvi*/
int32_t P142_340C0;
#pragma pop_macro("P142_340C0") /*gvi*/
#pragma pop_macro("P142_340C0")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P142_340C4")
#undef P142_340C4
#pragma push_macro("P142_340C4") /*gvi*/
#undef P142_340C4 /*gvi*/
int32_t P142_340C4;
#pragma pop_macro("P142_340C4") /*gvi*/
#pragma pop_macro("P142_340C4")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P142_D07788")
#undef P142_D07788
#pragma push_macro("P142_D07788") /*gvi*/
#undef P142_D07788 /*gvi*/
int32_t P142_D07788;
#pragma pop_macro("P142_D07788") /*gvi*/
#pragma pop_macro("P142_D07788")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P142_B87E18")
#undef P142_B87E18
#pragma push_macro("P142_B87E18") /*gvi*/
#undef P142_B87E18 /*gvi*/
int32_t P142_B87E18;
#pragma pop_macro("P142_B87E18") /*gvi*/
#pragma pop_macro("P142_B87E18")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P142_B2F304")
#undef P142_B2F304
#pragma push_macro("P142_B2F304") /*gvi*/
#undef P142_B2F304 /*gvi*/
int32_t P142_B2F304;
#pragma pop_macro("P142_B2F304") /*gvi*/
#pragma pop_macro("P142_B2F304")
#endif
#endif

/* 32-битная арифметика оригинала: выражение в int64, затем по модулю 2^32 */
#define W(x)  ((int32_t)(uint32_t)(int64_t)(x))
#define L(x)  ((int64_t)(x))
static int32_t dv(int32_t v, int sh) { return (int32_t)((uint32_t)v + ((uint32_t)(v >> 31) & ((1u << sh) - 1u))) >> sh; }  /* v / 2^sh к нулю */
static int32_t rd32(const uint8_t *p) { int32_t v; memcpy(&v, p, 4); return v; }
static void wr32(uint8_t *p, int32_t v) { memcpy(p, &v, 4); }
static void add32(uint8_t *p, int32_t v) { wr32(p, W(L(rd32(p)) + v)); }
static int32_t rd16(const uint8_t *p) { int16_t v; memcpy(&v, p, 2); return v; }
static void wr16(uint8_t *p, int32_t v) { int16_t s = (int16_t)v; memcpy(p, &s, 2); }
static int32_t sn(uint32_t a) { return P59_Sin[a & 0xfff]; }
static int32_t iabs32(int32_t v) { return v < 0 ? -v : v; }
static uint32_t oaddr(const uint8_t *o) { return re_addr(o); }
static const uint8_t *cars_base(void) { return (const uint8_t *)&P99_Cars[0]; }
static int is_player(const uint8_t *o) { return o == cars_base(); }
static int is_cur(const uint8_t *o) { return o == cars_base() + (size_t)S_00D11878 * sizeof(p99_car_t); }
static uint8_t traffic_b(int32_t obj_id, int off) {     /* (&011443e0 + off)[(id − 1)·0x54] */
  int32_t i = obj_id - 1;
  if (i < 0 || (uint32_t)(i * 0x54 + off) >= sizeof TrafficRecs) return 0;
  return TrafficRecs[i * 0x54 + off];
}
static const uint8_t *model_pt(uint32_t type, int32_t idx) {   /* 00d0cc60 + тип·0x16c + idx·4 */
  static const int16_t zero3[3] = { 0, 0, 0 };
  uint32_t off = type * 0x16cu + (uint32_t)idx * 4u;
  if (off + 6u > sizeof S_00D0CC60) return (const uint8_t *)zero3;
  return &S_00D0CC60[off];
}
static void load_pt(const uint8_t *p) { int16_t s[3]; memcpy(s, p, 6); LoadShort3FromPtr(s); }

/* ---------------- 004a7fec ---------------- */
static const int32_t k_552770[6] = { 290, 300, 310, 340, 380, 420 };   /* .data 00552770: скорость копа по сложности (+3 — 01129584) */
static uint8_t *cop_car(uint32_t i) {
#ifndef RE_HOOK_BUILD
  if (P59_CarsTab == NULL) { uint32_t k = i + 1; return (k < P99_CARS_N) ? (uint8_t *)&P99_Cars[k] : NULL; }
#endif
  return P59_CarsTab + i * 0x148u;
}
static int32_t cop_f(int32_t *c, int i) { return c[i]; }

void P142_CopDrive(uint8_t *rec) {
#ifndef RE_HOOK_BUILD
  static int reg;
  if (!reg) {
    reg = 1;
    re_ptr_register(0x0112b278u, &P142_B278, 4); re_ptr_register(0x0112b27cu, &P142_B27C, 4);
    re_ptr_register(0x0112b2b8u, &P142_B2B8, 4); re_ptr_register(0x011340c0u, &P142_340C0, 4);
    re_ptr_register(0x011340c4u, &P142_340C4, 4);
  }
#endif
  int32_t k = (int32_t)rec[5] - 1;
  if (k < 0 || k >= 8) return;
  int32_t *c = (int32_t *)(void *)&P12_0112da00[k * 0x336];
  uint8_t *car = cop_car(rec[0]);
  if (car == NULL) return;
  if (P56_B268 == 0 || P98_C824A0 != 0) { wr32(car + 0xf8, 0); return; }
  if (c[0x331] == 1) {
    float f;
    wr32(car + 0xf8, 0);
    memcpy(&f, &c[0x335], 4);
    if (0.01f < f) { f = f - 0.01f; memcpy(&c[0x335], &f, 4); }
    return;
  }
  if (P142_CopNoDmg == 0) {
    c[0x10] = 0;
    for (int i = 0; i < 6; i++) c[0x10] = W(L(c[0x10]) + rd32(car + 0x11c + i * 4));
  } else c[0x10] = 0;
  if (P142_CopDmgMax < c[0x10]) { c[0x331] = 1; wr32(car + 0xf8, 0); return; }
  c[0x331] = 0;
  c[0x319] = rd32(car + 200);
  c[0x31b] = rd32(car + 0xd0);
  c[10] = rd32(car + 0x110);
  c[3] = rd32(car + 0x100);
  int32_t l8 = W(L(rd32(car + 0x10c)) + 0x800) >> 12;
  int32_t x38 = rd32(car + 200), z3 = rd32(car + 0xd0);
  int32_t dx = W(L(P99_Cars[0].f40[0]) - rd32(car + 0x40));    /* 00d07800 */
  int32_t dz = W(L(P99_Cars[0].f40[2]) - rd32(car + 0x48));    /* 00d07808 */
  int32_t m24 = rd16(car + 4), m1c = rd16(car + 0x10);
  int32_t go = 0;
  int32_t pt[4] = { 0, 0, 0, 0 };
  P97_129584 = 0;
  if (rd32(car + 0x110) < 5 && c[9] != 0) c[12]++; else c[12] = 0;
  if (rd32(car + 0xf0) < 3) c[0x16]++; else c[0x16] = 0;
  if (c[0x16] >= 0xc9) { c[0x331] = 1; return; }
  if (10 < c[12] && c[14] == 0) {
    c[14] = 0x16;
    c[13] = (c[13] & 7) + 1;
    c[9] = (c[9] >= 0) ? -300 : 300;
    c[8] = ((((c[13] * 5) >> 1) & 3) * 2 - 3) * 0x80;
    c[12] = 0;
  }
  int32_t d28 = P74_Dist(x38, z3, dx, dz);
  c[0x333] = (d28 < 2000 || (c[0x32e] == 0 && d28 < 0x20d0)) ? 1 : 0;
  if (c[14] < 1) {
    if (d28 < 12000) {
      int32_t a = W(L(dx) + 0x800) >> 12, b = W(L(dz) + 0x800) >> 12;
      int32_t den = W(L(a) * a + 1 + L(b) * b);
      int32_t num = W(-L(W(L(PlayerPosX) - x38)) * a - L(W(L(PlayerPosZ) - z3)) * b);
      int32_t t = den ? (int32_t)(L(num) / den) : 0;
      if (P112_Wanted == 0) t = dv(W(L(t) * 3), 2);
      int32_t c0 = t < 0 ? 0 : (t < 0x3d ? t : 0x3c);
      int32_t o1, o2;
      if (P112_Wanted == 0) { o1 = -dv(P99_Cars[0].mat[2], 4); o2 = -dv(P99_Cars[0].mat[8], 4); }
      else { o1 = dv(P99_Cars[0].mat[0], 5); o2 = dv(P99_Cars[0].mat[6], 5); }
      P97_B2A8 = W(L(PlayerPosZ) + (W(L(P99_Cars[0].f40[2]) * c0 + 0x800) >> 12) + o2);
      P97_B2A0 = W(L(PlayerPosX) + (W(L(P99_Cars[0].f40[0]) * c0 + 0x800) >> 12) + o1);
    } else { P97_B2A0 = PlayerPosX; P97_B2A8 = PlayerPosZ; }
    if (c[0x333] == 0) {
      if (c[0x32e] != 0) {
        P114_PathDraw((uint8_t *)(c + 0x18), 0);
        int32_t ah = P99_PathAhead((uint8_t *)c);
        P102_CopPathPoint((uint8_t *)c, ah, pt);
        int32_t q = W(L(W(L(pt[0]) - x38)) * m24 + L(W(L(pt[2]) - z3)) * m1c) >> 12;
        if (q < 0) q = -q;
        if (q < 0xd49) {
          if (c[0x32e] != 0) { P102_CopPathPoint((uint8_t *)c, W(L(ah) + L(rd32(car + 0x110)) * 10 + 1000), pt); go = 1; }
        } else c[0x32e] = 0;
      }
    } else {
      pt[0] = P97_B2A0; pt[2] = P97_B2A8;
      c[0x32e] = 0;
      c[0x12] = PlayerPosX; c[0x13] = PlayerPosZ;
      int32_t i1 = W(L(P62_Map2C40) - (L(c[0x13]) - 0x2ee));
      c[0x14] = W(L(c[0x12]) + 0x2ee + P62_MapC64) / 0x5dc;
      c[0x15] = i1 / 0x5dc;
      go = 1;
    }
  } else c[14]--;
  if (go == 0) { pt[0] = P97_B2A0; pt[1] = P97_B2A4; pt[2] = P97_B2A8; pt[3] = P142_B2AC; }
  pt[0] = W(L(c[0x321]) * 2 - c[0x329] + pt[0]) >> 1;
  pt[2] = W(L(c[0x323]) * 2 - c[0x32b] + pt[2]) >> 1;
  for (int i = 0; i < 4; i++) {
    c[0x329 + i] = c[0x325 + i]; c[0x325 + i] = c[0x321 + i]; c[0x321 + i] = c[0x31d + i]; c[0x31d + i] = pt[i];
  }
  if (G6_005624A0 == 0) go = 0;
  if (go == 0) {
    if (c[14] < 1) { c[9] = 0; c[8] = 0; }
  } else {
    int32_t i1 = W(L(m24) * rd32(car + 0x40) + 0x800 + L(m1c) * rd32(car + 0x48)) >> 12;
    int32_t ex = W(L(pt[0]) - x38), ez = W(L(pt[2]) - z3);
    int32_t i2 = W(-L(ex) * m1c + L(ez) * m24) >> 12;
    int32_t i3 = (W(L(ex) * m24 + L(ez) * m1c) >> 12) - i1 / 0xc6;
    int32_t sel;
    if (i3 < 1) {
      if (W(L(i3) * -2) < i2) sel = 0;
      else sel = (-i3 < W(L(i2) * 4) && c[0x333] != 0) ? 1 : 2;
    } else {
      if (W(L(i3) * 2) < i2) sel = 0;
      else sel = (i3 < W(L(i2) * 4) && c[0x333] != 0) ? 1 : 3;
    }
    uint32_t u4 = (uint32_t)(i3 + i1 / 0xc6);
    car[0x13e] = (uint8_t)(0 < (int32_t)((uint32_t)c[9] ^ (uint32_t)l8));
    int32_t sgn = (int32_t)(u4 ^ (uint32_t)l8) >= 0;
    switch (sel) {
    case 0: {
      int32_t di = WI00B87E2C;
      int32_t ti = (P97_129584 == 0) ? di : di + 3;
      c[9] = (ti >= 0 && ti < 6) ? k_552770[ti] : 0;
      c[9] = W(L(c[9]) * W(L(P142_B278) + (W(L(G2_00D11A5C) * P142_B27C) >> 12))) >> 12;
      if (P142_340C0 != 0 && c[0x333] != 0) {
        if (d28 < 0xfa1) c[9] = P62_Spd + 10;
        else c[9] = W(L(P62_Spd) + 10 + W(L(W(L(c[9]) - (P62_Spd + 10))) * (d28 - 4000)) / 4000);
      }
      c[8] = i2 ? W(L(u4) * 0x200) / i2 : 0;
      break;
    }
    case 1:
      c[9] = -100;
      c[8] = sgn ? 0x11c : -0x11c;
      break;
    default:
      c[9] = (P112_Wanted == 0 || c[0x333] == 0 || c[9] >= 0) ? 0x6e : -0x6e;
      c[8] = sgn ? 0x200 : -0x200;
      break;
    }
    car[0x13e] = 1;
  }
  if (c[0xf] != 0) c[0xf]--;
  if (d28 < 0x1000 && 0 < c[9] && P112_Wanted == 0) {
    int32_t a0 = P62_Spd - 0x14;
    if (a0 < 0x14) a0 = 0x14;
    c[9] = W(L(d28) * c[9] + 0x800 + L(0x1000 - d28) * a0) >> 12;
  }
  int32_t df = W(L(c[9]) - l8);
  int32_t ac = (WI00B87E2C + 8) * 0x400;
  if (P97_129584 != 0) ac += (WI00B87E2C + 4) * 0x400;
  ac = W(L(ac) * W(L(P142_B2B8) + (W(L(G2_00D11A5C) * P142_340C4) >> 12))) >> 12;
  if (c[0x17] != 0) ac = ac / 2;
  int32_t f8;
  if (df < -0x32) f8 = -ac;
  else if (df < 0x33) f8 = W(L(df) * ac) / 0x32;
  else f8 = ac;
  if (rd32(car + 0x110) < 0x30) f8 = W(L(f8) * (rd32(car + 0x110) + 0x50)) >> 7;
  if (car[0x13e] == 1) f8 >>= 1;
  wr32(car + 0xf8, f8);
  int32_t e8 = W(L(c[8]) - rd32(car + 0xfc));
  if (e8 < -200) e8 = -200; else if (200 < e8) e8 = 200;
  add32(car + 0xfc, e8);
  c[0xb]--;
  if (P62_Frame % 8 == k) {
    if (c[0xb] < 0) c[0x32e] = 0;
    P128_CopReplan((uint8_t *)c);
    if (c[0x32e] != 0 && cop_f(c, 0x32f) == 1) {
      wr32(car + 0x100, rd16((const uint8_t *)(c + 0x1f)));
      P59_ObjDir(car, 0);
      c[0x32f] = 0;
      c[0xf] = 0;
    }
  }
}

/* ---------------- 004df024 ---------------- */
static int drv_test(const uint8_t *o) {    /* 00575f24 / 0x41 / 00b87ea0 / 00575efc */
  if (G00575F24 == 0) return o[0] == 0x41 && (G6_00B87EA0 == 0 || P88_Mode575 != 2);
  return o[0] == 0 || o[0] == 0x41;
}
static int32_t traction(const uint8_t *o, int32_t v) {
  if (o[2] == 1) return 0x1000;
  if (o[0] == 0 || 0x40 < o[0]) return W(L(v) * (0x7e90 - P142_D07788)) >> 15;
  return v;
}

void P142_WheelPhys(uint8_t *obj, int32_t drive) {
  int32_t st[25];
  memset(st, 0, sizeof st);
  int32_t fx = 0, fy = 0, fz = 0;
  uint32_t type = obj[2];
  for (int i = 2; i >= 0; i--) {
    int32_t v = (rd32(obj + 0x24 + i * 4) & 0xf) + W(L(rd32(obj + 0x18 + i * 4)) * 0x10);
    wr32(obj + 0x24 + i * 4, v);
    st[8 + i] = rd32(obj + 0x40 + i * 4);
    st[5 + i] = rd32(obj + 0x18 + i * 4);
    st[16 + i] = rd32(obj + 0x4c + i * 4);
    st[20 + i] = rd32(obj + 0x68 + i * 4);
  }
  if (P98_MrkOff != 0 && obj[0] != 0) {
    float mx, mz;
    memcpy(&mx, &P76_ColObj[0], 4); memcpy(&mz, &P76_ColObj[8], 4);   /* 00d02650 / 00d02658 */
    int32_t a0 = W(L(rd32(obj + 200)) - (int32_t)mx);
    int32_t a4 = W(L(rd32(obj + 0xd0)) - (int32_t)mz);
    if (a0 < 10000 && -10000 < a0 && a4 < 10000 && -10000 < a4) {
      int32_t n = W(L(a0) * a0 + L(a4) * a4);
      if (n != 0) {
        fx = W(L((int32_t)(0x7530000LL / n)) * a0);
        fy = (int32_t)(-0xd052140LL / n);
        fz = W(L((int32_t)(0x7530000LL / n)) * a4);
      }
    }
    if (P140_Mrk2644 != 0) {
      for (int i = 0; i < 6; i++) wr32(obj + 0x11c + i * 4, 0xfff);
      wr32(obj + 0x138, 0x5ffa);
      AddUnique_004C1F9B((int32_t)obj[0] - 1);
      uint8_t b = traffic_b(obj[0], 5);
      if (b != 0 && b <= 8) P12_0112da00[(b - 1) * 0x336 + 0x331] = 1;   /* native: только 8 записей */
    }
  }
  st[12] = fx; st[13] = W(L(fy) - 0x2aaa); st[14] = fz;
  int32_t a8 = iabs32(W(L(st[8]) + 0x800) >> 12), ac = iabs32(W(L(st[10]) + 0x800) >> 12);
  int32_t l8 = (a8 < ac) ? ac + a8 / 2 : a8 + ac / 2;
  wr32(obj + 0x110, l8);
  { int16_t m[9]; memcpy(m, obj + 4, 18); CopyShort9_005278FB(m); }
  CopyVec3_0052797A((uint32_t *)(void *)&st[5]);
  int32_t b0 = 0;
  int32_t n_pts = (0x800 < rd16(obj + 0xc)) ? 4 : 0xc;
  for (int32_t i = n_pts - 1; i >= 0; i--) {
    int32_t e[4] = { 0 }, nrm[4] = { 0 }, g[4] = { 0 };
    load_pt(model_pt(type, 0x41 + i * 2));
    RotVec_005279CB(e);
    int32_t d8 = W(L(e[0]) - st[5]), d4 = W(L(e[1]) - st[6]), d0 = W(L(e[2]) - st[7]);
    int32_t l10 = traction(obj, P103_GroundAt(e, nrm, g));
    (void)l10;
    if (i < 4) { wr32(obj + 0x88 + i * 0x10, g[0]); wr32(obj + 0x8c + i * 0x10, g[1]); wr32(obj + 0x90 + i * 0x10, g[2]); }
    int32_t c8 = W(L(g[1]) - e[1]);
    if (0 < c8) {
      int32_t f8v[3], c4[3];
      if (b0 < c8) b0 = c8;
      f8v[0] = (W(L(st[17]) * d0 - L(st[18]) * d4 + 0x800) >> 12) + st[8];
      f8v[1] = (W(L(st[18]) * d8 - L(st[16]) * d0 + 0x800) >> 12) + st[9];
      f8v[2] = (W(L(st[16]) * d4 - L(st[17]) * d8 + 0x800) >> 12) + st[10];
      int32_t l130 = W(L(d8) * nrm[0] + L(d4) * nrm[1] + 0x800 + L(d0) * nrm[2]) >> 12;
      int32_t l12c = W(L(d8) * d8 + L(d4) * d4 + L(d0) * d0 - L(l130) * l130);
      int32_t l128 = (W(L(l12c) * 0x6e + 0x800) >> 12) + 0x1000;
      int32_t dot = W(L(f8v[0]) * nrm[0] + L(f8v[1]) * nrm[1] + 0x800 + L(f8v[2]) * nrm[2]) >> 12;
      int32_t l11c = W(L(l128 ? dot / l128 : 0) * -0x800);
      static const int32_t k_5624b0[3] = { 0x5a0000, 0x21c0000, 0x5a0000 };   /* .data 005624b0 */
      for (int j = 2; j >= 0; j--) {
        int32_t l134 = W(L(f8v[j]) * 0x60);
        if (k_5624b0[j] < l134) l134 = k_5624b0[j];
        else if (l134 < -k_5624b0[j]) l134 = -k_5624b0[j];
        c4[j] = W(L(l11c) * nrm[j] - l134 + 0x800) >> 12;
      }
      if (20000 < l11c) {
        if (P14_00b87e84 == 0) { int32_t v[4] = { 0, 0x28, 0, 0 }; P125_SmokePuffs(g, v, 10, 0, obj[2]); }
        else { int32_t v[4] = { 0, 0x32, 0, 0 }; P125_ObjABurst(g, v, 0xf, 1); }
        if ((is_player(obj) || 0xd0cb07u < oaddr(obj)) && 30000 < l11c) P97_SndStart(3, 3, (float)g[0], (float)g[1], (float)g[2]);
      }
      st[22] = W(L(st[22]) - (W(L(d4) * c4[0] + 0x800) >> 12));
      st[21] = W(L(st[21]) + (W(L(d0) * c4[0] + 0x800) >> 12));
      st[12] = W(L(st[12]) + c4[0]);
      st[20] = W(L(st[20]) - (W(L(d0) * c4[1] + 0x800) >> 12));
      st[22] = W(L(st[22]) + (W(L(d8) * c4[1] + 0x800) >> 12));
      st[13] = W(L(st[13]) + c4[1]);
      st[21] = W(L(st[21]) - (W(L(d8) * c4[2] + 0x800) >> 12));
      st[20] = W(L(st[20]) + (W(L(d4) * c4[2] + 0x800) >> 12));
      st[14] = W(L(st[14]) + c4[2]);
    }
  }
  if (b0 != 0) {
    st[6] = W(L(st[6]) + b0);
    add32(obj + 0x28, W(L(b0) * 0x10));
    add32(obj + 0xcc, b0);
    CopyVec3_0052797A((uint32_t *)(void *)&st[5]);
    st[24] = 1;
    if (0x78 < b0) wr32(obj + 0x44, 0);
  }
  int32_t l164 = ((l8 < 0x20) ? l8 * -0x48 + 0x1000 : 0x720 - l8) - 400;
  int32_t h = rd32(obj + 0x100);
  int32_t s17c = sn((uint32_t)h), s160 = sn((uint32_t)h + 0x400u);
  int32_t l158 = W(L(st[8]) * -0xc), l15c = W(L(st[9]) * -0xc), l168 = W(L(st[10]) * -0xc);
  int32_t l18 = rd32(obj + 0xfc);
  int32_t s16c = sn((uint32_t)h + (uint32_t)l18), s170 = sn((uint32_t)h + 0x400u + (uint32_t)l18);
  if (0xce4 < l164) l164 = 0xce4;
  int32_t l174 = (rd32(obj + 0xf8) < 0) ? 0x5ad : (rd32(obj + 0xf8) < 1 ? 0x3a9 : 0x334);
  if (drv_test(obj) && rd32(obj + 0x108) == 0 && 0 < rd32(obj + 0x10c)) {
    int32_t l184 = (int8_t)obj[0x140];
    if (0 < l184) { if (0x1a < l184) l184 = 0x1a; l174 += l184 * 0x16; }
  }
  {
    uint8_t v = (rd32(obj + 0xf8) < 0 && 0xf000 < rd32(obj + 0x10c) && drive != 0) ? 1 : 0;
    obj[0x85] = v; obj[0x81] = v; obj[0x7d] = v; obj[0x79] = v;
  }
  if (rd32(obj + 0x104) == 0) {
    if (rd32(obj + 0x108) != 0) l174 += 600;
  } else {
    if (rd32(obj + 0xf8) >= 0) wr32(obj + 0xf8, 0);
    l174 += (rd32(obj + 0x10c) < 1) ? -0x177 : 0x290;
    obj[0x7d] = 1; obj[0x85] = 1;
    wr32(obj + 0x108, 0);
  }
  if (rd32(obj + 0x10c) < 0 && rd32(obj + 0xf8) >= 0 && rd32(obj + 0x104) == 0) l174 -= 400;
  int32_t l178 = 0x780 - l174;
  if (rd32(obj + 0x108) != 0) {
    wr32(obj + 0xf8, MenuOptBDFA44 == 0 ? 0x1b58 : 0x36b0);
    if (0xf < obj[2]) wr32(obj + 0xf8, (int32_t)((uint32_t)rd32(obj + 0xf8) << 1));
    if (obj[0] == 0) wr32(obj + 0xf8, dv(W(L(rd32(obj + 0xf8)) * P107_SteerK), 12));
  }
  if (rd32(obj + 0xf8) < 0 && 0xf000 < rd32(obj + 0x10c) && drive != 0) {
    l174 = dv(l174 * 10, 3); l178 = dv(l178 * 10, 3);
    if (obj[0] == 0) { l174 = dv(W(L(l174) * P142_B87E18), 12); l178 = dv(W(L(l178) * P142_B87E18), 12); }
  } else if (drv_test(obj) == 0) {
    if (drive != 0 && obj[0x7a] != 0) l174 = dv(l174 * 0x24, 5);
  } else {
    l174 = dv(l174 * (obj[0x7a] == 0 ? 0x23 : 0x27), 5);
  }
  if (obj[0x13e] == 1) {
    int32_t m = WI00B87E2C == 0 ? 0x2d : (WI00B87E2C == 1 ? 0x37 : 0x44);
    l174 = dv(l174 * m, 5); l178 = dv(l178 * m, 5);
  } else if (!is_player(obj) && obj[0] != 0x41) {
    l174 = dv(l174 * 0x1d, 5); l178 = dv(l178 * 0x1d, 5);
  }
  int32_t l14 = 0, lc = 0;
  wr32(obj + 0xf0, 0);
  for (int32_t i = 3; i >= 0; i--) {
    uint8_t *w = obj + i * 4 + 0x78;
    int32_t a[4] = { 0 }, b[4] = { 0 }, gc[4] = { 0 };
    load_pt(model_pt(type, 0x38 + i * 2));
    RotVec_005279CB(a);
    int32_t l10 = P103_GroundAt(a, b, gc);
    int32_t iy = gc[1];
    if (is_player(obj)) {
      if (0x10 < W(L(gc[1]) - P102_B2EA38[i])) {
        int b5 = P59_Mode1137324 == 2;
        if (P97_SndStart(0x1d, 0x10, (float)gc[0], (float)-gc[1], (float)gc[2]) != -1) {
          SoundSetPos00523F8A(0x10, 5000);
          P48_SetVoiceVolume(0x10, b5 ? 0 : -7000);
        }
      }
      P102_B2EA38[i] = iy;
    }
    l10 = traction(obj, l10);
    if (!is_cur(obj) && oaddr(obj) < 0xd0cb08u && traffic_b(obj[0], 2) != 1 && obj[2] != 1) {
      b[0] = 0; b[1] = 0x1000; b[2] = 0; l10 = 0x2800;
    }
    w[2] = (uint8_t)P56_B2EA48;
    uint32_t u190 = w[0];
    int32_t l194 = W(L(gc[1]) + 0x14 - a[1]);
    if (obj[0] == 0) P142_B2F304 = 0;
    if (l194 < 0) l194 = 0;
    if (obj[0] == 0) { if (0x78 < l194 || 0x30 < l194) ReturnZero004E3B19(); }
    if (0x3c < l194) l194 = 0x3c;
    if (l194 == 0 && u190 == 0) { w[0] = 0; continue; }
    int32_t l18c = l194 * 0x14a + (int32_t)u190 * -200;
    a[0] = W(L(a[0]) - st[5]); a[1] = W(L(a[1]) - st[6]); a[2] = W(L(a[2]) - st[7]);
    int32_t i2 = (W(L(st[17]) * a[2] - L(st[18]) * a[1] + 0x800) >> 12) + st[8];
    int32_t i4 = (W(L(st[16]) * a[1] - L(st[17]) * a[0] + 0x800) >> 12) + st[10];
    int32_t l1e0 = 0, l1d4 = 0, e4, f8_;
    if (w[1] == 0) {
      if ((i & 1) == 0) { e4 = s170; f8_ = -s16c; } else { e4 = s160; f8_ = -s17c; }
    } else {
      uint32_t u3 = (uint32_t)P44_Atan2(dv(i2, 6), dv(i4, 6));
      f8_ = sn(((u3 & 0xfff) + 0x400) & 0xfff);
      e4 = sn(u3 & 0xfff);
    }
    i2 = W(L(dv(i2, 6)) * dv(e4, 6) + L(dv(i4, 6)) * dv(f8_, 6));
    i4 = iabs32(W(L(dv(l164, 6)) * dv(i2, 6)));
    int32_t l1fc;
    if (i2 < 0x11941) {
      if (i2 < -72000) l1fc = -18000;
      else {
        l1fc = W(L(l164) * i2 + 0x800) >> 12;
        if (0x4650 < l1fc) l1fc = 18000; else if (l1fc < -18000) l1fc = -18000;
      }
    } else l1fc = 18000;
    int32_t f8o = rd32(obj + 0xf8);
    if ((i & 1) == 0) {
      int32_t t = W(L(l174) * l1fc + 0x800);
      l1fc = t >> 12;
      if (w[1] == 0) {
        if (obj[0x13e] == 1) {
          l1d4 = W(L(s16c) * f8o + 0x800) >> 12;
          l1e0 = W(L(s170) * f8o + 0x800) >> 12;
          if (obj[0] == 0) P142_B2F304 = W(L(P142_B2F304) + l1fc);
        } else if (obj[0] == 0) P142_B2F304 = W(L(P142_B2F304) + L(l1fc) * -2);
      } else {
        l1fc = ((t >> 13) + l1fc) >> 1;
        int32_t q = W(L(W(L(-l1fc) * e4 + 0x800) >> 12) * s170 - L(W(L(-l1fc) * f8_ + 0x800) >> 12) * s16c + 0x400) >> 11;
        l1d4 = W(L(q) * s170 + 0x800) >> 12;
        l1e0 = W(L(-q) * s16c + 0x800) >> 12;
        if (obj[0] == 0) P142_B2F304 = W(L(P142_B2F304) + q);
      }
      if (l14 < i4) l14 = i4;
    } else {
      if (w[1] == 0) {
        l1fc = W(L(l178) * l1fc + 0x800) >> 12;
        int b5 = obj[0] == 0 || (obj[0] == 0x41 && G6_00B87EA0 != 0 && P88_Mode575 == 2);
        if ((obj[0] == 0 || obj[0] == 0x41) &&
            ((b5 && W(L(l1fc) * (int8_t)obj[0x141]) < 0) || 0 < W(L(l1fc) * rd32(obj + 0xfc)))) obj[0x140] = 0xff;
        l1d4 = W(L(-f8_) * f8o + 0x800) >> 12;
        l1e0 = W(L(e4) * f8o + 0x800) >> 12;
      } else l1fc = W(L(l174) * l1fc + 0x2000) >> 14;
      if (lc < i4) lc = i4;
    }
    int32_t iy4 = W(L(l18c) * b[1] + 0x800 + l15c) >> 12;
    l1d4 = W(L(W(L(l1d4) + (W(L(l18c) * b[0] - L(l1fc) * e4 + 0x800 + l158) >> 12))) * (l10 + 500)) >> 12;
    l1e0 = W(L(W(L(l1e0) + (W(L(l18c) * b[2] - L(l1fc) * f8_ + 0x800 + l168) >> 12))) * (l10 + 500)) >> 12;
    if (rd16(obj + 0xc) < 0x800) {
      int32_t t = 0x1000 - rd16(obj + 0xc);
      int32_t l240 = (t < 0x1001) ? 0x1000 - (W(L(t) * t + 0x800) >> 12) : 0;
      l1d4 = W(L(l1d4) * l240 + 0x800) >> 12;
      l1e0 = W(L(l1e0) * l240 + 0x800) >> 12;
    }
    if (obj[0x13e] == 1) a[1] = dv(W(L(a[1]) * (WI00B87E2C == 2 ? 7 : 8)), 5);
    else a[1] = dv(W(L(a[1]) * 5), 4);
    if (P98_MrkOff == 0 || obj[0] != 0) {
      st[22] = W(L(st[22]) - (W(L(a[1]) * l1d4 + 0x800) >> 12));
      st[21] = W(L(st[21]) + (W(L(a[2]) * l1d4 + 0x800) >> 12));
      st[12] = W(L(st[12]) + l1d4);
      st[20] = W(L(st[20]) - (W(L(a[2]) * iy4 + 0x800) >> 12));
      st[22] = W(L(st[22]) + (W(L(a[0]) * iy4 + 0x800) >> 12));
      st[13] = W(L(st[13]) + iy4);
      st[21] = W(L(st[21]) - (W(L(a[0]) * l1e0 + 0x800) >> 12));
      st[20] = W(L(st[20]) + (W(L(a[1]) * l1e0 + 0x800) >> 12));
      st[14] = W(L(st[14]) + l1e0);
    } else {
      int32_t up = ((i & 1) == 0) ? 0x23000 : 0xb000;
      st[20] = W(L(st[20]) - (W(L(a[2]) * up + 0x800) >> 12));
      st[22] = W(L(st[22]) + (W(L(a[0]) * up + 0x800) >> 12));
      st[13] = W(L(st[13]) + up);
    }
    w[0] = (uint8_t)l194;
    add32(obj + 0xf0, 1);
  }
  if (obj[0x7c] == 0 && obj[0x84] == 0) {
    int32_t f8 = rd32(obj + 0xf8);
    wr32(obj + 0x10c, f8 < 1 ? (f8 >= 0 ? 0 : (int32_t)0xffed4000u) : 0x1a4000);
  } else {
    wr32(obj + 0x10c, W(L(dv(st[8], 6)) * dv(s17c, 6) + L(dv(st[10], 6)) * dv(s160, 6)));
  }
  wr32(obj + 0x114, l14);
  wr32(obj + 0x118, lc);
  P94_SpringStep(obj, (uint8_t *)st);
  obj[0x13c] = 0; obj[0x13d] = 0;
  if (obj[0] == 0) P35_PadX = dv(W(L(P35_PadX) * 3 + P142_B2F304), 2);
}

/* ---------------- 004dacee ---------------- */
static uint8_t *blk(p102_d68_t b, int32_t i) { return &b[i * 0x34]; }
static void clamp24(uint8_t *p) {
  int32_t v = rd32(p);
  if (0x1000000 < v) wr32(p, 0x1000000); else if (v < -0x1000000) wr32(p, -0x1000000);
}
static void impulse(uint8_t *r, const int32_t *g, const int32_t *arm, int32_t k, int32_t sign) {
  for (int m = 0; m < 3; m++) add32(r + 0x1c + m * 4, sign * g[m]);
  int32_t t0, t1, t2;
  if (sign < 0) {   /* a: (g × arm) */
    t0 = W(L(g[1]) * arm[2] - L(g[2]) * arm[1] + 0x800) >> 12;
    t1 = W(L(g[2]) * arm[0] - L(g[0]) * arm[2] + 0x800) >> 12;
    t2 = W(L(g[0]) * arm[1] - L(g[1]) * arm[0] + 0x800) >> 12;
  } else {          /* b: (arm × g) */
    t0 = W(L(arm[1]) * g[2] - L(arm[2]) * g[1] + 0x800) >> 12;
    t1 = W(L(arm[2]) * g[0] - L(arm[0]) * g[2] + 0x800) >> 12;
    t2 = W(L(arm[0]) * g[1] - L(arm[1]) * g[0] + 0x800) >> 12;
  }
  add32(r + 0x28, W(L(t0) * k)); add32(r + 0x2c, W(L(t1) * k)); add32(r + 0x30, W(L(t2) * k));
}
static void body_pt(const uint8_t *p, const int32_t *arm, int32_t *o) {   /* p: состояние (+0x1c позиция, +0x28 угл. скорость) */
  o[0] = (W(L(rd32(p + 0x2c)) * arm[2] - L(rd32(p + 0x30)) * arm[1] + 0x800) >> 12) + rd32(p + 0x1c);
  o[1] = (W(L(rd32(p + 0x30)) * arm[0] - L(rd32(p + 0x28)) * arm[2] + 0x800) >> 12) + rd32(p + 0x20);
  o[2] = (W(L(rd32(p + 0x28)) * arm[1] - L(rd32(p + 0x2c)) * arm[0] + 0x800) >> 12) + rd32(p + 0x24);
}

void P142_CarsStep(void) {
  int32_t n = G6_00D0DDC0;
#ifndef RE_HOOK_BUILD
  { static int k; if (getenv("RE_CARDBG") && (k++ % atoi(getenv("RE_CARDBG"))) == 0) { uint8_t *c = (uint8_t *)&P99_Cars[0];
    fprintf(stderr, "[car] n %d o0 %s 13c %d 110 %d pos %d %d %d p24 %d %d %d v %d %d %d f8 %d fc %d 104 %d 108 %d 10c %d o3 %d\n", n, (n > 0 && G6_00B2F30C[0] == c) ? "car0" : "?",
      rd16(c + 0x13c), rd32(c + 0x110), rd32(c + 0x18), rd32(c + 0x1c), rd32(c + 0x20), rd32(c + 0x24), rd32(c + 0x28), rd32(c + 0x2c), rd32(c + 0x40), rd32(c + 0x44), rd32(c + 0x48),
      rd32(c + 0xf8), rd32(c + 0xfc), rd32(c + 0x104), rd32(c + 0x108), rd32(c + 0x10c), c[3]); } }
  { /* v2.21: RE_TELEPORT="кадр:x:z;кадр:x:z…" (v2.25: до 64 точек) — отладка прохождения миссий (как RE_COPNEAR): на кадре P62_Frame машина игрока
       переносится в (x, z): позиция +0x18/+0xc8 и fixed ×16 +0x24, скорости +0x40..+0x74 обнуляются, высота и курс прежние */
    static int tn = -1; static int32_t tf[64], tx[64], tz[64];   /* v2.25: до 64 точек (обход клеток интервью) */
    if (tn < 0) { tn = 0; const char *e = getenv("RE_TELEPORT");
      while (e && *e && tn < 64) { int32_t f, x, z;
        if (sscanf(e, "%d:%d:%d", &f, &x, &z) != 3) break;
        tf[tn] = f; tx[tn] = x; tz[tn] = z; tn++; e = strchr(e, ';'); if (e) e++; } }
    for (int t = 0; t < tn; t++) if ((int32_t)P62_Frame == tf[t]) {
      uint8_t *c = (uint8_t *)&P99_Cars[0];
      wr32(c + 0x18, tx[t]); wr32(c + 0x20, tz[t]); wr32(c + 0x24, tx[t] * 16); wr32(c + 0x2c, tz[t] * 16);
      P99_Cars[0].pos[0] = tx[t]; P99_Cars[0].pos[2] = tz[t];
      for (int m = 0x40; m < 0x78; m += 4) wr32(c + m, 0);
      P88_TeleportReload = 1;   /* v2.29: блоки карты вокруг нового места */
      fprintf(stderr, "[teleport] кадр %d → %d %d\n", (int)P62_Frame, (int)tx[t], (int)tz[t]);
    }
  }
  { /* v2.29: RE_AUTOTARGET=N[:D] — отладка прохождения кампании: с кадра P62_Frame N (каждой миссии) машина игрока переносится
       к включённой цели скрипта миссии (00c80ce0 + i·0x34: +0x10 флаги, 1 — включена, 8 — цель-событие; +0 радиус, +0x14 x, +0x1c z),
       если цель включена не меньше D кадров (по умолчанию 150) и игрок дальше трети радиуса. Засчитывает цель игра сама
       (P115_TargetTick/скрипт), перенос только заменяет езду; цели-события (машина) не трогаются — только журнал. */
    static int on = -1; static int32_t from = 0, delay = 150, seen[10], since[10];
    if (on < 0) { const char *e = getenv("RE_AUTOTARGET"); on = e != NULL; if (e) { from = atoi(e); const char *c = strchr(e, ':'); if (c) delay = atoi(c + 1); } }
    if (on && (int32_t)P62_Frame >= from && P99_Cars[0].pos[0] | P99_Cars[0].pos[2]) {
      uint8_t *c = (uint8_t *)&P99_Cars[0];
      for (int i = 0; i < 10; i++) {
        const uint8_t *o = P58_Objs[i];
        int32_t fl = (int32_t)rd32(o + 0x10), rad = (int32_t)rd32(o), x = (int32_t)rd32(o + 0x14), z = (int32_t)rd32(o + 0x1c);
        int32_t key = (fl & 9) == 1 ? (x ^ (z << 1) ^ rad) | 1 : 0;
        if (key != seen[i] || (int32_t)P62_Frame < since[i]) { seen[i] = key; since[i] = (int32_t)P62_Frame;
          if (fl & 1) fprintf(stderr, "[autotarget] кадр %d: цель %d флаги %x радиус %d (%d, %d)%s\n", (int)P62_Frame, i, (unsigned)fl, (int)rad,
                              (int)x, (int)z, (fl & 8) ? " — событие, не переносим" : ""); }
        if (key == 0 || (int32_t)P62_Frame - since[i] < delay) continue;
        double dx = (double)x - (int32_t)rd32(c + 0x18), dz = (double)z - (int32_t)rd32(c + 0x20);
        if (dx * dx + dz * dz <= ((double)rad / 3) * ((double)rad / 3)) continue;
        wr32(c + 0x18, x); wr32(c + 0x20, z); wr32(c + 0x24, x * 16); wr32(c + 0x2c, z * 16);
        P99_Cars[0].pos[0] = x; P99_Cars[0].pos[2] = z;
        for (int m = 0x40; m < 0x78; m += 4) wr32(c + m, 0);
        P88_TeleportReload = 1;
        fprintf(stderr, "[autotarget] w=%d кадр %d → цель %d (%d, %d), было в %.0f\n", plat_frame_no(), (int)P62_Frame, i, (int)x, (int)z, sqrt(dx * dx + dz * dz));
        break;
      }
    }
  }
#endif
  if (n > (int32_t)(sizeof P102_BlkA / 0x34)) n = (int32_t)(sizeof P102_BlkA / 0x34);
  if (P102_D0DD7C != 0) P102_D0DD7C--;
  P46_UpdateObjects();
  P103_CarsOverlap();
  for (int32_t i = 0; i < n; i++) {
    uint8_t *o = G6_00B2F30C[i];
    if (o == NULL) continue;
    for (int m = 0; m < 3; m++) {
      wr32(o + 0x58 + m * 4, rd32(o + 0x58 + m * 4) >> 1);
      add32(o + 0x40 + m * 4, rd32(o + 0x58 + m * 4));
    }
    for (int m = 0; m < 3; m++) {
      wr32(o + 0x68 + m * 4, rd32(o + 0x68 + m * 4) >> 1);
      add32(o + 0x4c + m * 4, rd32(o + 0x68 + m * 4));
    }
    wr32(o + 0x68, 0); wr32(o + 0x6c, 0); wr32(o + 0x70, 0);
    if (rd32(o + 0x110) == 0) {
      int32_t s = W(L(iabs32(rd32(o + 0x40))) + iabs32(rd32(o + 0x44)) + iabs32(rd32(o + 0x48)));
      if (s < 1000) { wr32(o + 0x40, 0); wr32(o + 0x44, 0); wr32(o + 0x48, 0); }
      else wr32(o + 0x110, 1);
    }
    clamp24(o + 0x4c); clamp24(o + 0x50); clamp24(o + 0x54);
    if (G6_00B87EAC != 0 || G6_00B87EB0 != 0) wr16(o + 0x13c, 1);
    if (G6_00B87EA0 != 0) wr16(o + 0x13c, 0);
    if (rd16(o + 0x13c) == 0) {
      add32(o + 0x24, rd32(o + 0x40) >> 9);
      add32(o + 0x28, rd32(o + 0x44) >> 9);
      add32(o + 0x2c, rd32(o + 0x48) >> 9);
      int32_t wx = W(L(rd32(o + 0x4c)) + 0x1000) >> 13, wy = W(L(rd32(o + 0x50)) + 0x1000) >> 13, wz = W(L(rd32(o + 0x54)) + 0x1000) >> 13;
      int32_t qx = rd32(o + 0x30), qy = rd32(o + 0x34), qz = rd32(o + 0x38), qw = rd32(o + 0x3c);
      int32_t i3 = W(-L(qy) * wz + L(qz) * wy + 0x800 + L(qw) * wx);
      int32_t i4 = W(L(qx) * wz - L(qz) * wx + 0x800 + L(qw) * wy);
      int32_t i1 = W(-L(qx) * wy + L(qy) * wx + 0x800 + L(qw) * wz);
      int32_t i7 = W(-L(qx) * wx - L(qy) * wy - L(qz) * wz + 0x800);
      add32(o + 0x30, i3 >> 13); add32(o + 0x34, i4 >> 13); add32(o + 0x38, i1 >> 13); add32(o + 0x3c, i7 >> 13);
      P56_ObjSync((int32_t *)(void *)(o + 0x24), o);
    }
  }
  for (int32_t pass = 0; pass < 4; pass++) {
    for (int32_t s = 0; s < 2; s++) {
      for (int32_t i = 0; i < n; i++) {
        uint8_t *a = G6_00B2F30C[i];
        if (a == NULL || rd16(a + 0x13c) == 0) continue;
        uint8_t *pa = (s == 0) ? a + 0x24 : blk(P102_BlkA, i);
        uint8_t *bb = (s == 0) ? P102_BlkB : P102_BlkC;
        P94_PackState(pa, (int32_t *)(void *)(bb + i * 0x34));
        if (P95_B87E14 != 0 || G6_00B87EA0 != 0) continue;
        for (int32_t j = 0; j < i; j++) {
          uint8_t *b = G6_00B2F30C[j];
          if (b == NULL) continue;
          uint8_t *pb = (0 < s) ? blk(P102_BlkA, j) : b + 0x24;
          if (rd16(b + 0x13c) == 0 || (rd32(b + 0x110) == 0 && rd32(a + 0x110) == 0)) continue;
          int32_t ap[3] = { rd32(a + 0x18), rd32(a + 0x1c), rd32(a + 0x20) };
          int32_t bp[3] = { rd32(b + 0x18), rd32(b + 0x1c), rd32(b + 0x20) };
          int32_t dd[3] = { W(L(bp[0]) - ap[0]), W(L(bp[1]) - ap[1]), W(L(bp[2]) - ap[2]) };
          if (!(dd[0] < 0x4b1 && -0x4b1 < dd[0] && dd[1] < 0x4b1 && -0x4b1 < dd[1] && dd[2] < 0x4b1 && -0x4b1 < dd[2])) continue;
          int32_t depth = 0, hit[4] = { 0 }, nv[4] = { 0 }, q[4] = { 0 };
          if (P102_CarsHit(a, b, &depth, hit, nv, q) == 0) continue;
          int32_t d4 = (int32_t)((uint32_t)depth << 15);
          hit[1] = W(L(hit[1]) + 0x46);
          int32_t ea[3] = { W(L(hit[0]) - ap[0]), W(L(hit[1]) - ap[1]), W(L(hit[2]) - ap[2]) };
          int32_t eb[3] = { W(L(hit[0]) - bp[0]), W(L(hit[1]) - bp[1]), W(L(hit[2]) - bp[2]) };
          if (j == 0 || 0x40 < j) eb[1] -= 0x32;
          int32_t vb[3], va[3], r[3];
          body_pt(pb, eb, vb);
          body_pt(pa, ea, va);
          for (int m = 0; m < 3; m++) r[m] = W(L(va[m]) - vb[m]);
          int32_t dc = W(L(dv(r[0], 8)) * dv(nv[0], 5) + L(dv(r[1], 8)) * dv(nv[1], 5) + L(dv(r[2], 8)) * dv(nv[2], 5));
          if (0 < dc && s == 0) {
            if (a[0x13e] != 1 || b[0x13e] != 1) {
              if ((G00BDFA50 == 0 || a[0] != 0) && (G00BDFA58 == 0 || a[2] != 1) && P103_CarDamage(a, ea, dc) != 0) a[0x13f] = 1;
              if ((G00BDFA50 == 0 || b[0] != 0) && (G00BDFA58 == 0 || a[2] != 1) && P103_CarDamage(b, eb, dc) != 0) b[0x13f] = 1;
            }
            if (0x5000 < dc) {
              const uint8_t *src = (a[0] == 0 || 0x40 < a[0]) ? a : b;
              int32_t v[4];
              v[0] = dv(rd32(src + 0x40), 12); v[2] = dv(rd32(src + 0x48), 12); v[1] = -17; v[3] = 0;
              hit[0] = W(L(hit[0]) - q[0]); hit[2] = W(L(hit[2]) - q[2]);
              hit[1] = W(-(L(W(L(hit[1]) - 0x46)) - q[1]));
              P125_ObjABurst(hit, v, 6, 1);
              hit[1] = -hit[1];
              if (a[0] == 0 || b[0] == 0) {
                if (P62_HudOff2 != 0) P44_Rst_B31EA0 = 1;
                ReturnZero004E3B19();
              }
              P125_SmokePuffs(hit, v, 2, 1, a[2]);
              P125_SmokePuffs(hit, v, 4, 0, a[2]);
              P125_SmokePuffs(hit, v, 2, 1, b[2]);
              P125_SmokePuffs(hit, v, 4, 0, b[2]);
              P97_SndStart(3, 3, (float)hit[0], (float)hit[1], (float)hit[2]);
            }
          }
          d4 = W(L(d4) + dv(W(L(dc) * 9), 2));
          if (0x190000 < d4) d4 = 0x190000;
          {
            int32_t kk = d4 >> 3;
            for (int m = 0; m < 3; m++) nv[m] = W(L(nv[m] >> 3) * kk) >> 6;
          }
          int32_t f60 = 1, f5c = 1, f58 = 0x37;
          if (G6_00B87EB0 != 0 || G6_00B87EAC != 0 || G00BDFA50 != 0 || G00BDFA58 != 0) {
            if (0x40 < b[0] || (G00BDFA50 != 0 && b[0] == 0) || (G00BDFA58 != 0 && b[2] == 1)) {
              f58 = 0x1b;
              if (a[0] == 0 && P102_D0DD7C == 0 && 8000 < dc) { P102_D0DD7C = 0x32; P95_BDFA0C++; }
              f60 = 0;
            }
            if (0x40 < a[0] || (G00BDFA50 != 0 && a[0] == 0) || (G00BDFA58 != 0 && a[2] == 1)) {
              f58 >>= 1;
              if (b[0] == 0 && P102_D0DD7C == 0 && 8000 < dc) { P102_D0DD7C = 0x32; P95_BDFA0C++; }
              f5c = 0;
            }
          }
          int32_t g[3];
          if (f5c != 0) {
            for (int m = 0; m < 3; m++) {
              if (a[0x13e] == 1 && b[0x13e] != 1 && b[0] != 0) g[m] = dv(W(L(nv[m]) * (7 - WI00B87E2C)), 3);
              else if (a[2] == 6 && b[2] != 6) g[m] = (int32_t)((uint32_t)nv[m] << 1) / 3;
              else g[m] = nv[m];
            }
            impulse(bb + i * 0x34, g, ea, f58, -1);
          }
          if (f60 != 0) {
            for (int m = 0; m < 3; m++) {
              if (a[0x13e] == 1 || b[0x13e] != 1 || a[0] == 0) {
                if (a[2] == 6 || b[2] != 6) g[m] = nv[m];
                else g[m] = (int32_t)((uint32_t)nv[m] << 1) / 3;
              } else g[m] = dv(W(L(nv[m]) * (7 - WI00B87E2C)), 3);
            }
            impulse(bb + j * 0x34, g, eb, f58, 1);
          }
          P102_CarsCollide(a[0], b[0], dc);
        }
      }
      for (int32_t i = 0; i < n; i++) {
        uint8_t *o = G6_00B2F30C[i];
        if (o == NULL || rd16(o + 0x13c) == 0) continue;
        uint8_t *p = o + 0x24, *t = blk(P102_BlkA, i), *rb = blk(P102_BlkB, i), *rc = blk(P102_BlkC, i);
        if (s == 0) {
          for (int m = 0xc; m >= 0; m--) wr32(t + m * 4, W(L(rd32(p + m * 4)) + (rd32(rb + m * 4) >> 3)));
          P56_ObjSync((int32_t *)(void *)t, o);
        } else {
          for (int m = 0xc; m >= 0; m--) add32(p + m * 4, W(L(rd32(rb + m * 4)) + rd32(rc + m * 4)) >> 4);
          P56_ObjSync((int32_t *)(void *)p, o);
        }
      }
    }
  }
  for (int32_t i = 0; i < n; i++) {
    uint8_t *o = G6_00B2F30C[i];
    if (o == NULL) continue;
    uint32_t type = o[2];
    if (o[0x13f] != 0 && (G6_00B87EA0 != 0 || ((uint32_t)(P62_Frame + i) & 3u) == 0)) {
      AddUnique_004C1F9B((int32_t)o[0] - 1);
      o[0x13f] = 0;
    }
    wr32(o + 0x100, (int32_t)((uint32_t)P44_Atan2(rd16(o + 8), rd16(o + 0x14)) & 0xfffu));
    if (traffic_b(o[0], 5) != 0 || is_cur(o) || 0xd0cb07u < oaddr(o)) {
      uint32_t r = P17_ISqrt((uint32_t)W(L(rd16(o + 10)) * rd16(o + 10) + L(rd16(o + 0xc)) * rd16(o + 0xc)));
      wr16(o + 0xe8, (int32_t)((uint32_t)P44_Atan2(-rd16(o + 0xe), (int32_t)r) & 0xfffu));
      wr16(o + 0xea, rd32(o + 0x100));
      wr16(o + 0xec, (int32_t)((uint32_t)P44_Atan2(rd16(o + 10), rd16(o + 0xc)) & 0xfffu));
    }
    wr32(o + 200, rd32(o + 0x18)); wr32(o + 0xcc, rd32(o + 0x1c)); wr32(o + 0xd0, rd32(o + 0x20));
    wr32(o + 0xd8, W(L(rd32(o + 0x40)) + 0x800) >> 12);
    wr32(o + 0xdc, W(L(rd32(o + 0x44)) + 0x800) >> 12);
    wr32(o + 0xe0, W(L(rd32(o + 0x48)) + 0x800) >> 12);
    { int16_t m[9]; memcpy(m, o + 4, 18); CopyShort9_005278FB(m); }
    { uint32_t v[3]; memcpy(v, o + 0x18, 12); CopyVec3_0052797A(v); }
    P102_D0DD74 = 0;
    for (int32_t w = 0; w < 4; w++) {
      int32_t pp[4] = { 0 }, nn[4] = { 0 }, gg[4] = { 0 };
      load_pt(model_pt(type, 0x41 + w * 2));
      RotVec_005279CB(pp);
      (void)P103_GroundAt(pp, nn, gg);
      wr32(o + 0x88 + w * 0x10, gg[0]); wr32(o + 0x8c + w * 0x10, gg[1]); wr32(o + 0x90 + w * 0x10, gg[2]);
    }
    wr32(o + 0xf4, P102_D0DD74);
  }
}
