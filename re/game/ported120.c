/* v1.65: ported120 — восстановлено из Game.exe. Все функции cdecl (ret без операнда; work/rets.py).
   004af93c — объект B с затенением по счётчику повторов P68_Rep_ (ключ — адрес объекта) и источником света AddEntry_00426ABC;
   004cd875 — сброс таблицы записей скрипта (100 номеров, значок SNOW → G00D17B1C, P26_FxC);
   004ad6f5 — до 20 обломков у машины i (пул P95_ObjA, PoolPop004AC6D0, случайный сдвиг, P44_XformT);
   004afe3c — дым из выхлопа машины i (точка модели +0xb0, P118_SkidFx тип 2, искры игрока P96_SpawnSpark);
   004b00ad — искры двух точек модели +0xd0 машины i (таймеры 0110b040/011171c0/0110e2e0);
   004f60b7 — отладочная информация (позиция, курс, скорость игрока, пешеходы, конусы) через P96_LogLine;
   004a4d84 — разбор целого (или имени модели при mode 4) для P68_CamI0..3;
   004fbeb2 — запись конусов в файл Q00C812F0 (клавиши 00d04b3f/00d04b40);
   005032ce — HUD времени/счёта по режиму игры 01271060 (строки P97_StrAddr, sprintf → P70_ShadowText). */
#include "ported120.h"
#include "cartab.h"
#include "globalsets.h"
#include "uihandlers3.h"
#include "unported.h"
#include "crt.h"
#include "ported6.h"
#include "ported5.h"
#include "ported7.h"
#include "ported11.h"
#include "ported13.h"
#include "ported14.h"
#include "ported15.h"
#include "ported19.h"
#include "ported26.h"
#include "ported34.h"
#include "ported43.h"
#include "ported44.h"
#include "ported56.h"
#include "ported62.h"
#include "ported65.h"
#include "ported68.h"
#include "ported69.h"
#include "ported70.h"
#include "ported71.h"
#include "ported93.h"
#include "ported94.h"
#include "ported95.h"
#include "ported96.h"
#include "ported97.h"
#include "ported98.h"
#include "ported100.h"
#include "ported101.h"
#include "ported118.h"
#include "reptr.h"
#include <stdio.h>
#include <string.h>

#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P120_ScrA")
#undef P120_ScrA
#pragma push_macro("P120_ScrA") /*gvi*/
#undef P120_ScrA /*gvi*/
int32_t P120_ScrA;
#pragma pop_macro("P120_ScrA") /*gvi*/
#pragma pop_macro("P120_ScrA")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P120_ScrB")
#undef P120_ScrB
#pragma push_macro("P120_ScrB") /*gvi*/
#undef P120_ScrB /*gvi*/
int32_t P120_ScrB;
#pragma pop_macro("P120_ScrB") /*gvi*/
#pragma pop_macro("P120_ScrB")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P120_ScrC")
#undef P120_ScrC
#pragma push_macro("P120_ScrC") /*gvi*/
#undef P120_ScrC /*gvi*/
int32_t P120_ScrC;
#pragma pop_macro("P120_ScrC") /*gvi*/
#pragma pop_macro("P120_ScrC")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P120_ScrD")
#undef P120_ScrD
#pragma push_macro("P120_ScrD") /*gvi*/
#undef P120_ScrD /*gvi*/
int32_t P120_ScrD;
#pragma pop_macro("P120_ScrD") /*gvi*/
#pragma pop_macro("P120_ScrD")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P120_ScrE")
#undef P120_ScrE
#pragma push_macro("P120_ScrE") /*gvi*/
#undef P120_ScrE /*gvi*/
int32_t P120_ScrE;
#pragma pop_macro("P120_ScrE") /*gvi*/
#pragma pop_macro("P120_ScrE")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P120_ScrSeed")
#undef P120_ScrSeed
#pragma push_macro("P120_ScrSeed") /*gvi*/
#undef P120_ScrSeed /*gvi*/
int32_t P120_ScrSeed;
#pragma pop_macro("P120_ScrSeed") /*gvi*/
#pragma pop_macro("P120_ScrSeed")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P120_DbgOn")
#undef P120_DbgOn
#pragma push_macro("P120_DbgOn") /*gvi*/
#undef P120_DbgOn /*gvi*/
int32_t P120_DbgOn;
#pragma pop_macro("P120_DbgOn") /*gvi*/
#pragma pop_macro("P120_DbgOn")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P120_ConeN")
#undef P120_ConeN
#pragma push_macro("P120_ConeN") /*gvi*/
#undef P120_ConeN /*gvi*/
int32_t P120_ConeN;
#pragma pop_macro("P120_ConeN") /*gvi*/
#pragma pop_macro("P120_ConeN")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P120_ConeTick")
#undef P120_ConeTick
#pragma push_macro("P120_ConeTick") /*gvi*/
#undef P120_ConeTick /*gvi*/
uint16_t P120_ConeTick;
#pragma pop_macro("P120_ConeTick") /*gvi*/
#pragma pop_macro("P120_ConeTick")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P120_HudA")
#undef P120_HudA
#pragma push_macro("P120_HudA") /*gvi*/
#undef P120_HudA /*gvi*/
int32_t P120_HudA;
#pragma pop_macro("P120_HudA") /*gvi*/
#pragma pop_macro("P120_HudA")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P120_HudB")
#undef P120_HudB
#pragma push_macro("P120_HudB") /*gvi*/
#undef P120_HudB /*gvi*/
int32_t P120_HudB;
#pragma pop_macro("P120_HudB") /*gvi*/
#pragma pop_macro("P120_HudB")
#endif

#define P120_HudC   (*(int32_t *)&P56_Blk84[(0x00c8110c - 0x00c810c0) / 4])    /* 00c8110c — внутри P56_Blk84 */
#define P120_HudPtr (*(uint32_t *)&P56_Blk84[(0x00c812b8 - 0x00c810c0) / 4])   /* 00c812b8 — uint32-адрес пары int32 */

static int32_t rd32(const uint8_t *p) { int32_t v; memcpy(&v, p, 4); return v; }
static void wr32(uint8_t *p, int32_t v) { memcpy(p, &v, 4); }
static void wr16(uint8_t *p, int16_t v) { memcpy(p, &v, 2); }
static float rdf(const uint8_t *p) { float v; memcpy(&v, p, 4); return v; }
static void wrf(uint8_t *p, float v) { memcpy(p, &v, 4); }

static uint8_t *carp(int32_t i) {
#ifndef RE_HOOK_BUILD
  if (i < 0 || i >= P99_CARS_N) i = P99_CARS_N - 1;
#endif
  return (uint8_t *)&P99_Cars[i];
}
static const uint8_t *carmodel(uint32_t m) {   /* 00d0cc60 + m*0x16c */
#ifndef RE_HOOK_BUILD
  static const uint8_t zero[0x16c];
  if ((m + 1) * 0x16c > sizeof S_00D0CC60) return zero;
#endif
  return &S_00D0CC60[m * 0x16c];
}
static void set_mat(int32_t i) {   /* 00bdc28c = &01135060[i] (P44_MatPtr / P11_00bdc28c) */
#ifndef RE_HOOK_BUILD
  if (i < 0 || i >= 65) i = 0;
#endif
  P44_MatPtr = (float *)(void *)P98_CarMat[i];
}

/* ---- 004af93c ---- */
void P120_ObjBShade(uint8_t *obj, float x, float y, float z, int16_t kind, int16_t b) {
  int16_t v = 0xff;
  if (P14_00b87e84 == 0) return;
  int32_t key = (int32_t)re_addr(obj);
  for (int k = 0; k < 4; k++) {
    if (P68_Rep_[k].key == key) {
      if (P68_Rep_[k].cnt > 2) return;
      if (G6_00B5A778 == 0) v = (int16_t)(v - (int16_t)(P68_Rep_[k].cnt * 0x40 + (N14_Rand() & 0x7f)));
      else v = (int16_t)(0xff - P68_Rep_[k].cnt * 0x40);
      break;
    }
  }
  float p[3];
  p[0] = rdf(obj + 8); p[1] = y + rdf(obj + 0xc); p[2] = rdf(obj + 0x10);
  P101_AddObjB(obj, x, y, z, kind, b, v);
  AddEntry_00426ABC((const uint32_t *)(void *)p, 2000, v, v, v);
}

/* ---- 004cd875 ---- */
void P120_ScriptReset(int32_t *p) {
  P120_ScrC = 0; P120_ScrB = 0; P120_ScrA = 0; P120_ScrD = 0; P120_ScrE = 0;
  P120_ScrSeed = (int32_t)(N14_Rand() & 0xff);
  for (int32_t i = 0; i < 100; i++) {
    p[i + 1] = i;
    wr16((uint8_t *)p + i * 0x34 + 0x1c6, (int16_t)i);
  }
  p[0] = 0;
  uint8_t *ic = P93_FindIcon("SNOW");
  G00D17B1C = (int32_t)re_addr(ic);
  if (ic == NULL) { P26_FxC = 0; return; }
  ic[9]++; ic[10]++;
  ic[0xb] = (uint8_t)(ic[0xb] + ic[9] - 1);
  ic[0xc] = (uint8_t)(ic[0xc] + ic[10] - 1);
}

/* ---- 004ad6f5 ---- */
void P120_CarDebris(int32_t i, int32_t h) {
  set_mat(i);
  const uint8_t *c = carp(i);
  int32_t n = 0x14;
  while (n != 0) {
    n--;
    int32_t k = PoolPop004AC6D0();
    if (k < 0) break;
#ifndef RE_HOOK_BUILD
    if (k >= 200) continue;
#endif
    float v[3];
    v[0] = (float)(int32_t)((N14_Rand() & 0x1ff) - 0x100);
    v[2] = (float)(int32_t)((N14_Rand() & 0x3ff) - 0x200);
    v[1] = 0.0f;   /* в оригинале local_18 до XformT не задан (мусор стека) */
    P44_XformT(v);
    v[0] += (float)rd32(c + 0xc8);
    v[1] = (float)-h;
    v[2] += (float)rd32(c + 0xd0);
    uint8_t *r = &P95_ObjA[k * 0x78];
    wrf(r, v[0]); wrf(r + 4, v[1]); wrf(r + 8, v[2]);
    wr32(r + 0xc, 0);   /* local_10 — мусор стека в оригинале */
    wr32(r + 0x68, 0x8002);
    wr32(r + 0x58, 200);
    wrf(r + 0x5c, (float)((N14_Rand() & 0xf) + 10));
    wr32(r + 0x50, 100); wr32(r + 0x54, 400); wr32(r + 0x60, 10);
    wr16(r + 0x64, 100);
  }
}

/* ---- 004afe3c ---- */
void P120_CarSmoke(int32_t i, int32_t dist) {
  if (G6_00B5A778 != 0) return;
  const uint8_t *c = carp(i);
  const uint8_t *m = carmodel(c[2]);
  float p[4], v[4];
  p[0] = rdf(m + 0xb0); p[1] = rdf(m + 0xb4);
  p[2] = rdf(m + 0xb8) - (float)(rd32(c + 0x128) >> 6);
  p[3] = rdf(m + 0xbc);
  set_mat(i);
  P44_XformT(p);
  p[0] += (float)rd32(c + 0xc8);
  p[1] -= (float)rd32(c + 0xcc);
  p[2] += (float)rd32(c + 0xd0);
  v[0] = 0.0f; v[1] = 0.0f; v[2] = 5.0f; v[3] = 0.0f;
  P44_XformT(v);
  P118_SkidFx(p, 0x14, 0x32, 2, dist, v, 1);
  if (i == 0 && P62_BusyA != 0) P96_SpawnSpark(p, 0x32, 200, (int16_t)((N14_Rand() & 3) + 8));
}

/* ---- 004b00ad ---- */
void P120_CarSparks(int32_t i) {
  if (G6_00B5A778 != 0) return;
#ifndef RE_HOOK_BUILD
  if (i < 0 || i >= 0x41) return;
#endif
  const uint8_t *c = carp(i);
  const uint8_t *m = carmodel(c[2]);
  for (int32_t k = 1; k >= 0; k--) {
    uint8_t *tm = &A_0110B040[i * 8 + k * 4], *sz = &A_011171C0[i * 8 + k * 4], *dx = &A_0110E2E0[i * 8 + k * 4];
    float p[4];
    p[1] = rdf(m + 0xd4); p[2] = rdf(m + 0xd8); p[3] = rdf(m + 0xdc);
    p[0] = rdf(m + 0xd0) + (float)rd32(dx);
    wr32(tm, rd32(tm) - 1);
    if (rd32(tm) < 1) {
      wr32(tm, (int32_t)(N14_Rand() & 7));
      wr32(sz, (int32_t)((N14_Rand() & 3) + 8));
      wr32(dx, (int32_t)((N14_Rand() & 0x3f) - 0x20));
    }
    set_mat(i);
    P44_XformT(p);
    p[0] += (float)rd32(c + 0xc8);
    p[1] -= (float)rd32(c + 0xcc);
    p[2] += (float)rd32(c + 0xd0);
    P96_SpawnSpark(p, 0x32, 200, (int16_t)rd32(sz));
  }
}

/* ---- 004f60b7 ---- */
void P120_DebugInfo(void) {
  char b[64];
  if (P11_00b87e7c != 0 || P120_DbgOn == 0) return;
  const uint8_t *c = carp(0);
  int32_t y = P19_ScrH / 8 - 9;
  CursorSet004D94B7(0, y);
  P96_LogLine("--- Debug Information ---");
  snprintf(b, sizeof b, "Player car X position = %d", rd32(c + 0xc8)); P96_LogLine(b);
  snprintf(b, sizeof b, "Player car Y position = %d", rd32(c + 0xcc)); P96_LogLine(b);
  snprintf(b, sizeof b, "Player car Z position = %d", rd32(c + 0xd0)); P96_LogLine(b);
  int16_t ry; memcpy(&ry, c + 0xea, 2);
  snprintf(b, sizeof b, "Player car Y rotation = %d (Curr %d)", (int)ry, G00BDF984); P96_LogLine(b);
  snprintf(b, sizeof b, "Player car speed = %d", rd32(c + 0x10c)); P96_LogLine(b);
  snprintf(b, sizeof b, "Number of pedestrians active = %d/%d", P43_FreeCnt, P13_005759a4); P96_LogLine(b);
  if (P120_ConeN > 0) { snprintf(b, sizeof b, "Number of cones recorded = %d", P120_ConeN); P96_LogLine(b); }
}

/* ---- 004a4d84 ---- */
int32_t P120_ParseCamInt(char **pp, int32_t which, int32_t mode) {
  char neg = **pp;
  if (neg == '-') (*pp)++;
  uint32_t u = 0;
  uint16_t val;
  int32_t n = g_sscanf(*pp, "%u", &u);
  val = (uint16_t)u;
  P15_SkipInteger(pp);
  if ((n == 0 || n == -1) && (int16_t)mode == 4) {
    uint8_t name[256];
    *pp = (char *)P94_ReadIdent((uint8_t *)*pp, name);
    if (P62_ModelLookup((const char *)name, &val) == 0) {
      P26_ErrorInLine("Model number must be an unsigned integer or name");
      return 0;
    }
  } else if (n == 0 || n == -1) {
    P26_ErrorInLine("Expecting integer value.");
    return 0;
  }
  if (neg == '-') val = (uint16_t)-val;
  switch (which) {
  case 0: P68_CamI0 = val; break;
  case 1: P68_CamI1 = val; break;
  case 2: P68_CamI2 = val; break;
  case 3: P68_CamI3 = val; break;
  }
  return 1;
}

/* ---- 004fbeb2 ---- */
void P120_ConeRec(void) {
  if (P34_Keys[0x3f] != 0) P95_B87ED8 = 1;
  if (P34_Keys[0x40] != 0) P95_B87ED8 = 0;
  if (P95_B87ED8 == 0 || P120_ConeN == 100) return;
  uint16_t t = (uint16_t)(P120_ConeTick + 1);
  if (P120_ConeTick == 0) {
    const uint8_t *c = carp(0);
    int32_t pos[3] = { rd32(c + 0xc8), 0, rd32(c + 0xd0) };
    P120_ConeTick = t;
    int32_t h = -P100_RoadHeight(pos);
#ifdef RE_HOOK_BUILD
    void *f = (void *)(uintptr_t)(uint32_t)Q00C812F0;
#else
    void *f = NULL;   /* в native файл 00c812f0 не открывается (Call0052ADB0 — заглушка) */
#endif
    if (f != NULL) { g_fwrite(&pos[0], 1, 4, f); g_fwrite(&h, 1, 4, f); g_fwrite(&pos[2], 1, 4, f); }
    P120_ConeN++;
  } else {
    P120_ConeTick = t;
    if (P95_B87E40 < (int32_t)t) P120_ConeTick = 0;
  }
}

/* ---- 005032ce ---- */
static char p120_buf[32];
static uint32_t S(int32_t idx) { return P97_StrAddr[idx]; }   /* адрес строки 00c55820 + idx*4 */
static void T(int32_t x, int32_t y, uint32_t s, int32_t a, int32_t f, uint8_t r, uint8_t g, uint8_t b) { P70_ShadowText(x, y, s, a, (uint32_t)f, r, g, b); }
#define BUF ((uint32_t)(uintptr_t)p120_buf)
#define PR(...) snprintf(p120_buf, sizeof p120_buf, __VA_ARGS__)
static const uint8_t *tab(int32_t a) { return (const uint8_t *)re_ptr((uint32_t)a); }
static int hms(const uint8_t *t, uint32_t st, uint32_t o) { return t != NULL && rd32(t + st) == 8 && (PR("%02d:%02d:%02d", rd32(t + o + 8), rd32(t + o + 4), rd32(t + o)), 1); }
void P120_HudTimes(void) {
  const uint8_t *ta = tab(P71_Tab2A40);
  switch (MenuMode1271060) {
  case 1:
    T(0x1d6, 10, S(0xd7), 0, 0, 0xff, 0xff, 0x80);
    PR("%d", P120_HudC); T(0x23a, 0x19, BUF, 1, 2, 0xff, 0xff, 0xff);
    PR("/%d", G6_00C81108); T(0x23a, 0x32, BUF, 0, 0, 0xff, 0xff, 0xff);
    T(0x1d6, 0x50, S(0xd9), 0, 0, 0xff, 0xff, 0x80);
    PR("%s:", P65_STR(0xd8)); T(0x1d6, 0x69, BUF, 0, 0, 0xff, 0xff, 0x80);
    PR("-");
    if (ta != NULL && rd32(ta + 0x18) == 8) PR("%d", rd32(ta + 0x10));
    T(0x21c, 0x69, BUF, 0, 0, 0xff, 0xff, 0x80);
    PR("%s:", P65_STR(0xda)); T(0x1d6, 0x82, BUF, 0, 0, 0xff, 0xff, 0x80);
    PR("--:--:--"); hms(ta, 0x18, 0x20);
    T(0x21c, 0x82, BUF, 0, 0, 0xff, 0xff, 0x80);
    break;
  case 2: {
    const int32_t *pr = (const int32_t *)re_ptr(P120_HudPtr);
    T(0x226, 10, S(0xde), 0, 1, 0xff, 0xff, 0x80);
    PR("%d", pr != NULL ? pr[1] : 0); T(0x226, 0x1e, BUF, 1, 2, 0xff, 0xff, 0xff);
    PR("/%d", pr != NULL ? pr[0] : 0); T(0x226, 0x37, BUF, 0, 0, 0xff, 0xff, 0xff);
    PR("%s: --:--:--", P65_STR(0xd9));
    if (ta != NULL && rd32(ta + 0x18) == 8) PR("%s: %02d:%02d:%02d", P65_STR(0xd9), rd32(ta + 0x28), rd32(ta + 0x24), rd32(ta + 0x20));
    T(0x226, 0x50, BUF, 0, 1, 0xff, 0xff, 0x80);
    break; }
  case 3:
    PR("%s: --:--:--", P65_STR(0xd9));
    if (ta != NULL && rd32(ta + 0x18) == 8) PR("%s: %02d:%02d:%02d", P65_STR(0xd9), rd32(ta + 0x28), rd32(ta + 0x24), rd32(ta + 0x20));
    T(0x1d6, 10, BUF, 0, 0, 0xff, 0xff, 0x80);
    break;
  case 6: case 0xb: {
    T(0x1d6, 10, S(0xdf), 0, 0, 0xff, 0xff, 0x80);
    PR("%d", P120_HudB); T(0x226, 0x1e, BUF, 1, 2, 0xff, 0xff, 0xff);
    if (MenuMode1271060 == 6) PR("/%c", 0x7f); else PR("/%d", P120_HudA);
    T(0x226, 0x37, BUF, 0, 0, 0xff, 0xff, 0xff);
    PR("%s:", P65_STR(0xdb)); T(0x1d6, 0x50, BUF, 0, 0, 0xff, 0xff, 0x80);
    if (P71_V2A14 == 8) PR("%02d:%02d:%02d", P71_V2A24, P71_V2A20, P71_V2A1C); else PR("--:--:--");
    T(0x21c, 0x50, BUF, 0, 0, 0xff, 0xff, 0x80);
    PR("%s:", P65_STR(0xd9)); T(0x1d6, 0x69, BUF, 0, 0, 0xff, 0xff, 0x80);
    PR("--:--:--"); hms(tab((int32_t)P71_Ptr2A08), 4, 0xc);
    T(0x21c, 0x69, BUF, 0, 0, 0xff, 0xff, 0x80);
    T(0x10, 0x37, S(0xd6), 0, 0, 0xff, 0xff, 0x80);
    PR("%s:", P65_STR(0xdc)); T(0x10, 0x50, BUF, 0, 0, 0xff, 0xff, 0x80);
    PR("--:--:--"); hms(tab(P71_Tab974), 0x18, 0x20);
    T(0x56, 0x50, BUF, 0, 0, 0xff, 0xff, 0x80);
    PR("%s:", P65_STR(0xdd)); T(0x10, 0x69, BUF, 0, 0, 0xff, 0xff, 0x80);
    PR("--:--:--"); hms(ta, 0x18, 0x20);
    T(0x56, 0x69, BUF, 0, 0, 0xff, 0xff, 0x80);
    break; }
  case 7:
    PR("%s:", P65_STR(0xe1)); T(0x217, 0x50, BUF, 0, 2, 0xff, 0xff, 0x80);
    PR("$%d", P69_Score); T(0x221, 0x50, BUF, 0, 0, 0xff, 0xff, 0xff);
    T(0x10, 0x37, S(0xd6), 0, 0, 0xff, 0xff, 0x80);
    PR("%s:", P65_STR(0xe1)); T(0x10, 0x50, BUF, 0, 0, 0xff, 0xff, 0x80);
    PR("$-");
    if (ta != NULL && rd32(ta + 0x18) == 8) PR("$%d", rd32(ta + 0x10));
    T(0x78, 0x50, BUF, 0, 0, 0xff, 0xff, 0x80);
    break;
  }
}
