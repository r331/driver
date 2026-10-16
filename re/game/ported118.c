/* v1.63: ported118 — см. ported118.h */
#include "ported118.h"
#include "p118_data.h"
#include "ported4.h"
#include "ported6.h"
#include "ported7.h"
#include "ported8.h"
#include "ported12.h"
#include "ported43.h"
#include "ported44.h"
#include "ported51.h"
#include "ported59.h"
#include "ported62.h"
#include "ported74.h"
#include "ported95.h"
#include "ported96.h"
#include "ported98.h"
#include "ported99.h"
#include "ported101.h"
#include "ported102.h"
#include "ported11.h"
#include "nodetab.h"
#include "director.h"
#include "globalsets.h"
#include "menustate.h"
#include "smallfuncs.h"
#include "uihandlers2.h"
#include "uihandlers3.h"
#include "unported.h"
#include <string.h>

#ifndef RE_HOOK_BUILD
#pragma push_macro("P118_RouteTab") /*gvi*/
#undef P118_RouteTab /*gvi*/
p118_routetab_t P118_RouteTab = P118_ROUTE_INIT;
#pragma pop_macro("P118_RouteTab") /*gvi*/
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P118_Route")
#undef P118_Route
#pragma push_macro("P118_Route") /*gvi*/
#undef P118_Route /*gvi*/
p118_route_t P118_Route;
#pragma pop_macro("P118_Route") /*gvi*/
#pragma pop_macro("P118_Route")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P118_RouteTo")
#undef P118_RouteTo
#pragma push_macro("P118_RouteTo") /*gvi*/
#undef P118_RouteTo /*gvi*/
int32_t P118_RouteTo;
#pragma pop_macro("P118_RouteTo") /*gvi*/
#pragma pop_macro("P118_RouteTo")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P118_RouteKey")
#undef P118_RouteKey
#pragma push_macro("P118_RouteKey") /*gvi*/
#undef P118_RouteKey /*gvi*/
int32_t P118_RouteKey;
#pragma pop_macro("P118_RouteKey") /*gvi*/
#pragma pop_macro("P118_RouteKey")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P118_RouteMax")
#undef P118_RouteMax
#pragma push_macro("P118_RouteMax") /*gvi*/
#undef P118_RouteMax /*gvi*/
int32_t P118_RouteMax;
#pragma pop_macro("P118_RouteMax") /*gvi*/
#pragma pop_macro("P118_RouteMax")
#endif

static int32_t rd32(const uint8_t *p) { int32_t v; memcpy(&v, p, 4); return v; }
static void wr32(uint8_t *p, int32_t v) { memcpy(p, &v, 4); }
static int16_t rd16(const uint8_t *p) { int16_t v; memcpy(&v, p, 2); return v; }
static void wr16(uint8_t *p, int16_t v) { memcpy(p, &v, 2); }
static float rdf(const uint8_t *p) { float v; memcpy(&v, p, 4); return v; }
static void wrf(uint8_t *p, float v) { memcpy(p, &v, 4); }
static int32_t iabs(int32_t v) { return v < 0 ? -v : v; }

/* запись i таблицы tab (шаг st); в native вне таблицы — нули */
static const uint8_t *rec(const uint8_t *tab, uint32_t sz, int32_t i, uint32_t st) {
#ifndef RE_HOOK_BUILD
  static const uint8_t zero[0x100];
  if (i < 0 || (uint32_t)(i + 1) * st > sz) return zero;
#else
  (void)sz;
#endif
  return tab + (uint32_t)i * st;
}

/* ---- 0041a1f9: маршрут камеры меню ---- */
static uint8_t *key(uint32_t k) {            /* P99_CamKeys[k] */
#ifndef RE_HOOK_BUILD
  if ((k + 1) * 0x34 > sizeof P99_CamKeys) k = (uint32_t)(sizeof P99_CamKeys / 0x34 - 1);
#endif
  return &P99_CamKeys[k * 0x34];
}
static uint8_t *rkey(int32_t n) {            /* P118_Route[n] */
#ifndef RE_HOOK_BUILD
  if (n < 0 || (uint32_t)(n + 1) * 0x34 > sizeof P118_Route) n = (int32_t)(sizeof P118_Route / 0x34 - 1);
#endif
  return &P118_Route[(uint32_t)n * 0x34];
}
static uint32_t rt(uint32_t i) {             /* байт таблицы 0054e774 */
#ifndef RE_HOOK_BUILD
  if (i >= sizeof P118_RouteTab) return 0;
#endif
  return P118_RouteTab[i];
}
#define FIRST(c) rt(0x25u + (uint32_t)(c) * 3u)   /* 0054e799 */
#define LAST(c)  rt(0x26u + (uint32_t)(c) * 3u)   /* 0054e79a */
#define DIRECT(c) rt(0x24u + (uint32_t)(c) * 3u)  /* 0054e798 */
static void qfix(uint8_t *a, const uint8_t *b) {   /* кватернион a +0x10 в полушарие b +0x10 */
  if (Dot4_005270BD((const float *)(const void *)(a + 0x10), (const float *)(const void *)(b + 0x10)) < (long double)P8_00546024)
    VecNeg4_00527123((float *)(void *)(a + 0x10));
}
static void set_noKey(int32_t v) {
  D_005feda0 = v;
#ifndef RE_HOOK_BUILD
  P59_NoKeyFlag = v; UiVar005FEDA0 = v;          /* native-псевдонимы 005feda0 */
#endif
}
static void set_frame(int32_t v) {
  D_005fea98 = v;
#ifndef RE_HOOK_BUILD
  UiVar005FEA98 = v;                             /* native-псевдоним 005fea98 */
#endif
}
void P118_CamRoute(uint32_t p) {
  P118_RouteTo = (int32_t)p;
  uint32_t cur = (uint32_t)G005FEB00;
  if (p == cur) {
    uint8_t *k = key(FIRST(cur));
    P95_CamFromQuat((const float *)(const void *)(k + 0x10));
    P43_ScaleA = rdf(k + 0x24);
    P44_CamX = rdf(k); P44_CamY = rdf(k + 4); P44_CamZ = rdf(k + 8); P98_CamW = (uint32_t)rd32(k + 0xc);
#ifndef RE_HOOK_BUILD
    P59_VX = P44_CamX; P59_VY = P44_CamY; P59_VZ = P44_CamZ;
#endif
    return;
  }
  if ((int32_t)p < 10) P118_RouteMax = 0x19;
  else if ((int32_t)p < 0xe) P118_RouteMax = 10;
  else P118_RouteMax = 0xf;
  int32_t dir = 0;   /* в оригинале local_c не инициализирован, если пары нет (ведёт себя как «не 1») */
  for (uint32_t i = 0; i < 0x11; i++) {
    if (cur == rt(i * 2) && p == rt(i * 2 + 1)) { dir = 1; break; }
    if (cur == rt(i * 2 + 1) && p == rt(i * 2)) { dir = -1; break; }
  }
  if (D_005feda0 == 0) {
    if (DIRECT(p) == 1 || DIRECT(cur) == 1) {
      UiVar005FEB48 = 3;
      if (Dot4_005270BD((const float *)(const void *)(key(FIRST(cur)) + 0x10), (const float *)(const void *)(key(FIRST(p)) + 0x10)) < (long double)P8_00546024)
        VecNeg4_00527123((float *)(void *)(key(FIRST(P118_RouteTo)) + 0x10));
      memmove(rkey(1), key(FIRST(cur)), 0x34);
      memmove(rkey(0), rkey(1), 0x34);
      wr32(rkey(1) + 0x2c, 0);
      wr32(rkey(0) + 0x2c, 0);
      memmove(rkey(3), key(FIRST(P118_RouteTo)), 0x34);
      memmove(rkey(2), rkey(3), 0x34);
      wr32(rkey(3) + 0x2c, 0x32);
      wr32(rkey(2) + 0x2c, 0x32);
      P118_RouteKey = (int32_t)FIRST(P118_RouteTo);
    } else if (dir == 1) {
      memmove(rkey(0), key(FIRST(cur)), 0x34);
      int32_t n = 1;
      uint32_t k = LAST(cur);
      for (;;) {
        memmove(rkey(n), key(k), 0x34);
        if (k == 1) wr32(rkey(n) + 0x2c, rd32(rkey(n - 1) + 0x2c) + 0x1e);
        else wr32(rkey(n) + 0x2c, (rd32(rkey(n - 1) + 0x2c) + rd32(rkey(n) + 0x2c)) - rd32(key(k - 1) + 0x2c));
        if (k == LAST(P118_RouteTo)) break;
        k++;
        if (P118_RouteMax < (int32_t)k) k = 1;
        qfix(rkey(n), rkey(n - 1));
        n++;
      }
      UiVar005FEB48 = n;
    } else {
      memmove(rkey(0), key(LAST(cur)), 0x34);
      int32_t n = 1;
      uint32_t k = FIRST(cur);
      for (;;) {
        memmove(rkey(n), key(k), 0x34);
        if ((int32_t)k == P118_RouteMax) wr32(rkey(n) + 0x2c, rd32(rkey(n - 1) + 0x2c) + 0x1e);
        else wr32(rkey(n) + 0x2c, (rd32(rkey(n - 1) + 0x2c) + rd32(key(k + 1) + 0x2c)) - rd32(rkey(n) + 0x2c));
        if (k == FIRST(P118_RouteTo)) break;
        k--;
        if ((int32_t)k < 1) k = (uint32_t)P118_RouteMax;
        qfix(rkey(n), rkey(n - 1));
        n++;
      }
      UiVar005FEB48 = n;
    }
    set_noKey(1);
    set_frame(rd32(rkey(1) + 0x2c));
  } else {
    int32_t c = P12_005feb60;
    memmove(rkey(0), rkey(c - 1), 0x34);
    memmove(rkey(1), rkey(c), 0x34);
    memmove(rkey(2), rkey(c + 1), 0x34);
    memmove(rkey(3), key(FIRST(P118_RouteTo)), 0x34);
    wr32(rkey(3) + 0x2c, rd32(rkey(2) + 0x2c) + 0x1e);
    qfix(rkey(3), rkey(2));
    memmove(rkey(4), rkey(3), 0x34);
    wr32(rkey(4) + 0x2c, rd32(rkey(3) + 0x2c) + 0x1e);
    UiVar005FEB48 = 4;
  }
  P12_005feb60 = 1;
  G005FEB00 = (int32_t)p;
}

/* ---- 004932d5: поворот машины трафика на перекрёстке (направления 0..3) ---- */
static int32_t turn_sign(const uint8_t *r) {
  int32_t to = rd32(r + 0x30), from = rd32(r + 0x24);
  if (to == from) return 0;
  int32_t d = (int32_t)(((uint32_t)to * 0x400u - (uint32_t)from * 0x400u + 0x800u) & 0xfffu) - 0x800;
  return d < 0 ? -1 : 1;
}
int32_t P118_TrafficTurn(uint8_t *r) {
  uint16_t node = P101_RdNode;
  if (node == 0xffff || node == 0x3fff) { P74_FreeTraffic(r[0]); return 0; }
  const uint8_t *s = rec(P11_00c1ed80, sizeof P11_00c1ed80, (int16_t)node, 0x2c);
  int ok[4];   /* local_14, bStack_13, bStack_12, bStack_11 — разрешены направления 0..3 */
  int en = s[3] != 0;
  ok[0] = ok[1] = ok[2] = ok[3] = en;
  int32_t road = rd32(r + 0x28), from = rd32(r + 0x24);
  if (road < 0 || 0x3fff < road) { ok[0] = ok[1] = ok[2] = ok[3] = 1; }
  else if (from >= 0 && from <= 3) {
    uint8_t lane = r[9];
    uint8_t cv = (uint8_t)(rec(P59_C39DC0, sizeof P59_C39DC0, road, 0x24)[from] - 1);
    static const uint8_t k_set[4][4] = {   /* [dir][cv==0, lane==0, lane==cv, иначе] — биты направлений */
      { 0x0b, 0x03, 0x09, 0x01 }, { 0x07, 0x06, 0x03, 0x02 }, { 0x0e, 0x0c, 0x06, 0x04 }, { 0x0d, 0x09, 0x0c, 0x08 } };
    int c = cv == 0 ? 0 : lane == 0 ? 1 : lane == cv ? 2 : 3;
    for (int i = 0; i < 4; i++) if (k_set[from][c] & (1 << i)) ok[i] = 1;
  }
  wr32(r + 0x3c, 0x82);
  r[4] = (uint8_t)(G00BF1C20 + 2);
  r[3] = 0;
  int16_t nb[4];
  for (int i = 0; i < 4; i++) nb[i] = rd16(s + 0xa + 8 * i);
  uint8_t pick[4] = { 0, 0, 0, 0 };
  uint32_t n = 0;
  static const int k_order[4] = { 0, 2, 1, 3 };
  for (int j = 0; j < 4; j++) {
    int i = k_order[j];
    int32_t m = nb[i];
    if ((rd16(s + 0xc + 8 * i) & 2) == 0 && m != -1 && m != road &&
        rec(P11_00bf1c40, sizeof P11_00bf1c40, m, 0x42)[0x3d] != (uint8_t)(((i + 2) & 3) + 0x80) && ok[i]) {
      uint32_t was = n;
      pick[n & 3] = (uint8_t)i; n++;
      if (from == i && (uint8_t)(rec(P59_C39DC0, sizeof P59_C39DC0, m, 0x24)[i] - 1) < r[9]) n = was;
    }
  }
  if (n == 0) {
    for (int i = 0; i < 4; i++) {
      int32_t m = nb[i];
      if ((rd16(s + 0xc + 8 * i) & 2) == 0 && m != -1 && m != road &&
          rec(P11_00bf1c40, sizeof P11_00bf1c40, m, 0x42)[0x3d] != (uint8_t)(((i + 2) & 3) + 0x80)) { pick[n & 3] = (uint8_t)i; n++; }
    }
    if (n == 0) { P74_FreeTraffic(r[0]); return 0; }
  }
  if (n == 1) r[0x13] |= 4;
  uint32_t idx = (uint32_t)((int32_t)Rand_004D9078() % (int32_t)n) & 0xff;
  wr32(r + 0x30, pick[idx & 3]);
  wr32(r + 0x2c, nb[rd32(r + 0x30) & 3]);
  wr32(r + 0x34, turn_sign(r));
  if (n == 3 && rd32(r + 0x34) < 0) {
    int32_t to = rd32(r + 0x30);
    int again = (node & 1) == 0 ? (to == 0 || to == 1) : (to == 2 || to == 3);
    if (again) {
      uint32_t j = (uint8_t)(idx + 1);
      if (n <= j) j = (uint8_t)(j - n);
      wr32(r + 0x30, pick[j & 3]);
      wr32(r + 0x2c, nb[rd32(r + 0x30) & 3]);
      wr32(r + 0x34, turn_sign(r));
    }
  }
  return 1;
}

/* ---- 0048dddb: впереди машина (1) — прямоугольник по курсу и углы машин P96_RotTab ---- */
static const uint8_t *carp(int32_t i) {
#ifndef RE_HOOK_BUILD
  if (i < 0 || i >= P99_CARS_N) i = P99_CARS_N - 1;
#endif
  return (const uint8_t *)&P99_Cars[i];
}
static const uint8_t *tcar(int32_t i) {   /* машина трафика i по указателю 0113a6c4; в native без указателя — P99_Cars[1 + i] */
#ifndef RE_HOOK_BUILD
  if (P59_CarsTab == NULL) return carp(i + 1);
#endif
  return P59_CarsTab + (uint32_t)i * 0x148;
}
static const uint8_t *trec(int32_t i) { return rec(TrafficRecs, sizeof TrafficRecs, i, 0x54); }
int32_t P118_TrafficBlocked(uint8_t *p) {
  uint8_t dir = p[0x24];
  uint32_t me = p[0];
  int32_t side, len;
  if (p[1] == 3) { side = 0xb4; len = rd32(p + 0x38) + 900; }
  else { side = 0x1c2; len = rd32(p + 0x38) * 0x10 + 0x708; }
  const uint8_t *mc = tcar((int32_t)me);
  uint32_t ang = (uint32_t)-rd32(mc + 0x100) & 0xfff;
  int32_t cx, cz;
  if (p[1] != 3) {
    if (P102_TrafficAhead(p, 1, 0) != -1) return 1;
    cx = rd32(mc + 0xc8); cz = rd32(mc + 0xd0);
    int box = 1;
    int32_t x0 = 0, x1 = 0, z0 = 0, z1 = 0;   /* local_b0, local_a8, local_a0, local_a4 */
    if (ang < 0xfe1 && 0x1f < ang) {
      if (ang < 0x7e1 || 0x81f < ang) {
        if (ang < 0xbe1 || 0xc1f < ang) {
          if (ang < 0x3e1 || 0x41f < ang) box = 0;
          else { x0 = cx - len; z1 = side + cz; z0 = cz - side; x1 = cx; }
        } else { z1 = side + cz; z0 = cz - side; x0 = cx; x1 = len + cx; }
      } else { z0 = cz - len; x0 = cx - side; x1 = side + cx; z1 = cz; }
    } else { x0 = cx - side; x1 = side + cx; z1 = len + cz; z0 = cz; }
    if (box) {
      for (int32_t k = 0; k < P51_TrafficN + 1; k++) {
        const uint8_t *o = k != 0 ? trec(k - 1) : NULL;
        if (k != 0 && (o[1] == 0 || o[0] == me)) continue;
        const uint8_t *c = carp(k);
        int32_t ox = rd32(c + 0xc8), oz = rd32(c + 0xd0);
        if (iabs(ox - cx) >= len || iabs(oz - cz) >= len) continue;
        const int32_t *t = P96_RotTab[(int32_t)((uint32_t)-rd32(c + 0x100) & 0xfff) >> 2];
        int inx = (x0 <= t[0] + ox || x0 <= t[2] + ox || x0 <= t[4] + ox || x0 <= t[6] + ox) &&
                  (t[0] + ox <= x1 || t[2] + ox <= x1 || t[4] + ox <= x1 || t[6] + ox <= x1);
        if (!inx) continue;
        int inz = (t[1] + oz <= z1 || t[3] + oz <= z1 || t[5] + oz <= z1 || t[7] + oz <= z1) &&
                  (z0 <= t[1] + oz || z0 <= t[3] + oz || z0 <= t[5] + oz || z0 <= t[7] + oz);
        if (inz && (k == 0 || o[2] == 1 || (o[1] == 3 && rd32(o + 0x34) != 0) || (uint32_t)rd32(o + 0x24) != dir || o[1] != 1)) return 1;
      }
      return 0;
    }
  }
  cx = rd32(mc + 0xc8); cz = rd32(mc + 0xd0);
  int ready = 0;
  float s9c = 0, s94 = 0, s6c = 0, s84 = 0, d2c = 0, d90 = 0, d78 = 0, d68 = 0;
  for (int32_t k = 0; k < P51_TrafficN + 1; k++) {
    const uint8_t *o = k != 0 ? trec(k - 1) : NULL;
    if (k != 0 && (o[1] == 0 || o[0] == me)) continue;
    const uint8_t *c = carp(k);
    int32_t ox = rd32(c + 0xc8), oz = rd32(c + 0xd0);
    if (iabs(ox - cx) >= len || iabs(oz - cz) >= len) continue;
    if (!ready) {
      ready = 1;
      s9c = P43_Sin[(ang + 0x400) & 0xfff]; s94 = P43_Sin[ang];
      s6c = -s9c; s84 = -s94;
      d2c = s84 * ((float)-side * s94 + (float)cz) + s6c * ((float)-side * s9c + (float)cx);
      d90 = s94 * ((float)side * s94 + (float)cz) + s9c * ((float)side * s9c + (float)cx);
      d78 = s9c * ((float)len * s9c + (float)cz) + s84 * ((float)len * s84 + (float)cx);
      d68 = s6c * (float)cz + s94 * (float)cx;
    }
    const int32_t *t = P96_RotTab[(int32_t)((uint32_t)-rd32(c + 0x100) & 0xfff) >> 2];
    float x[4], z[4];
    for (int i = 0; i < 4; i++) { x[i] = (float)(t[i * 2] + ox); z[i] = (float)(t[i * 2 + 1] + oz); }
    int a = 0, b = 0, e = 0, f = 0;
    for (int i = 0; i < 4; i++) {
      if (s84 * z[i] + s6c * x[i] <= d2c) a = 1;
      if (s94 * z[i] + s9c * x[i] <= d90) b = 1;
      if (s9c * z[i] + s84 * x[i] <= d78) e = 1;
      if (s6c * z[i] + s94 * x[i] <= d68) f = 1;
    }
    if (a && b && e && f) return 1;
  }
  return 0;
}

/* ---- 004b8f4e: пыль (1), дым (2: spark=0) / искры (2: spark≠0), иное — дым; запись 0x78 P95_ObjA ---- */
void P118_SkidFx(const float *pos, int32_t a, int32_t b, int32_t type, int32_t dist, const float *vel, int32_t spark) {
  if (G6_00B5A778 != 0 || MenuVar55384C == 0 || (P62_Frame & 1) != 0) return;
  int32_t i = PoolPop004AC6D0();
  if (i < 0) return;
#ifndef RE_HOOK_BUILD
  if (i >= 200) return;
#endif
  uint8_t *r = P95_ObjA + i * 0x78;
  if (type == 1) {
    wrf(r, (float)(N14_Rand() & 0x7f) + pos[0]);
    wrf(r + 4, pos[1]);
    wrf(r + 8, (float)(N14_Rand() & 0x7f) + pos[2]);
    wr32(r + 0x50, a); wr32(r + 0x54, b);
    wr32(r + 0x60, 0x19);
    wr32(r + 0x68, 0x2006);
    wr16(r + 0x64, 0x28);
    wr16(r + 0x66, 0x14);
    wr32(r + 0x58, dist < 0x30d41 ? 0xff : (800000 - dist) >> 0xb);
    wr32(r + 0x5c, 10);
  } else if (type == 2) {
    if (spark == 0) {
      wrf(r, (float)(N14_Rand() & 0x3f) + pos[0]);
      wrf(r + 4, pos[1]);
      wrf(r + 8, (float)(N14_Rand() & 0x3f) + pos[2]);
      wr32(r + 0x68, 6); wr32(r + 0x60, 0x11); wr32(r + 0x58, 0x50); wr32(r + 0x5c, 4);
    } else {
      wrf(r, (float)(N14_Rand() & 0x15) + pos[0]);
      wrf(r + 4, pos[1]);
      wrf(r + 8, (float)(N14_Rand() & 0x15) + pos[2]);
      wr32(r + 0x68, 0x4006); wr32(r + 0x60, 2); wr32(r + 0x58, 0x28); wr32(r + 0x5c, 1);
    }
    wr32(r + 0x50, a); wr32(r + 0x54, b);
    wr16(r + 0x64, 100);
    wr16(r + 0x66, 0x32);
  } else {
    wrf(r, (float)(N14_Rand() & 0x3f) + pos[0]);
    wrf(r + 4, pos[1]);
    wrf(r + 8, (float)(N14_Rand() & 0x3f) + pos[2]);
    wr32(r + 0x68, 0x10006); wr32(r + 0x58, 0x96); wr32(r + 0x5c, 10);
    wr32(r + 0x50, a); wr32(r + 0x54, b);
    wr32(r + 0x60, 0x19);
    wr16(r + 0x64, 100);
    wr16(r + 0x66, 0x32);
  }
  wrf(r + 0x20, vel[0]); wrf(r + 0x24, vel[1]); wrf(r + 0x28, vel[2]);
  uint16_t life; memcpy(&life, r + 0x64, 2);
  float k = P8_00546020 / (float)((int32_t)(uint32_t)life >> 1);
  wrf(r + 0x30, k * vel[0]); wrf(r + 0x34, k * vel[1]); wrf(r + 0x38, k * vel[2]);
}
