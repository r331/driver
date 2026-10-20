/* ported119.c — hubcap physics, traffic spawning / turning / speed control, car-select keys, the menu frame,
   car dust and skid marks, parked traffic and the HUD (English overview; Russian notes in ported119.h and
   above each function).  All cdecl. */
/* v1.64: ported119 — см. ported119.h */
#include "../platform/plat.h"
#include "ported119.h"
#include "cartab.h"
#include "carfields.h"
#include "nodetab.h"
#include "director.h"
#include "globalsets.h"
#include "menustate.h"
#include "smallfuncs.h"
#include "smallfuncs2.h"
#include "uihandlers2.h"
#include "uihandlers3.h"
#include "ported4.h"
#include "ported5.h"
#include "ported6.h"
#include "ported7.h"
#include "ported8.h"
#include "ported11.h"
#include "ported12.h"
#include "ported13.h"
#include "ported14.h"
#include "ported17.h"
#include "ported19.h"
#include "ported21.h"
#include "ported25.h"
#include "ported26.h"
#include "ported28.h"
#include "ported29.h"
#include "ported31.h"
#include "ported33.h"
#include "ported43.h"
#include "ported44.h"
#include "ported45.h"
#include "ported47.h"
#include "ported51.h"
#include "ported52.h"
#include "ported54.h"
#include "ported56.h"
#include "ported58.h"
#include "ported59.h"
#include "ported62.h"
#include "ported63.h"
#include "ported68.h"
#include "ported72.h"
#include "ported74.h"
#include "ported75.h"
#include "ported79.h"
#include "ported82.h"
#include "ported84.h"
#include "ported85.h"
#include "ported86.h"
#include "ported94.h"
#include "ported95.h"
#include "ported97.h"
#include "ported98.h"
#include "ported99.h"
#include "ported100.h"
#include "ported101.h"
#include "ported102.h"
#include "ported103.h"
#include "ported105.h"
#include "ported109.h"
#include "ported110.h"
#include "ported115.h"
#include "ported117.h"
#include "ported118.h"
#include "reptr.h"
#include <math.h>
#include <string.h>

#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P119_GroundY")
#undef P119_GroundY
#pragma push_macro("P119_GroundY") /*gvi*/
#undef P119_GroundY /*gvi*/
int32_t P119_GroundY;
#pragma pop_macro("P119_GroundY") /*gvi*/
#pragma pop_macro("P119_GroundY")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P119_Wheels")
#undef P119_Wheels
#pragma push_macro("P119_Wheels") /*gvi*/
#undef P119_Wheels /*gvi*/
p119_wheels_t P119_Wheels;
#pragma pop_macro("P119_Wheels") /*gvi*/
#pragma pop_macro("P119_Wheels")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P119_SelPtr")
#undef P119_SelPtr
#pragma push_macro("P119_SelPtr") /*gvi*/
#undef P119_SelPtr /*gvi*/
uint32_t P119_SelPtr;
#pragma pop_macro("P119_SelPtr") /*gvi*/
#pragma pop_macro("P119_SelPtr")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P119_SelIdx")
#undef P119_SelIdx
#pragma push_macro("P119_SelIdx") /*gvi*/
#undef P119_SelIdx /*gvi*/
int32_t P119_SelIdx;
#pragma pop_macro("P119_SelIdx") /*gvi*/
#pragma pop_macro("P119_SelIdx")
#endif

#if defined(RE_HOOK_BUILD)
#  define P119_STD __attribute__((stdcall))
#else
#  define P119_STD
#endif

#include "memrw.h"
static void wr16(uint8_t *p, int16_t v) { memcpy(p, &v, 2); }
static void wrf(uint8_t *p, float v) { memcpy(p, &v, 4); }

#include "trafficrec.h"   /* traffic record fields (TREC_*) */

/* carp: car record i of the car table; tcar: car driven by traffic record i; trec: traffic record i;
   carmodel: per-model parameter record m (00d0cc60 + m * 0x16c); nodeb: road node table entry. */
static uint8_t *carp(int32_t i) {
#ifndef RE_HOOK_BUILD
  if (i < 0 || i >= P99_CARS_N) i = P99_CARS_N - 1;
#endif
  return (uint8_t *)&P99_Cars[i];
}
static uint8_t *tcar(int32_t i) {   /* машина трафика i по указателю 0113a6c4; в native без указателя — P99_Cars[1 + i] */
#ifndef RE_HOOK_BUILD
  if (P59_CarsTab == NULL) return carp(i + 1);
#endif
  return P59_CarsTab + (uint32_t)i * 0x148;
}
static uint8_t *trec(int32_t i) {
#ifndef RE_HOOK_BUILD
  if (i < 0 || i >= 0x40) { static uint8_t dummy[0x54]; memset(dummy, 0, sizeof dummy); return dummy; }
#endif
  return &TrafficRecs[i * 0x54];
}
static const uint8_t *carmodel(uint32_t m) {   /* 00d0cc60 + m*0x16c */
#ifndef RE_HOOK_BUILD
  static const uint8_t zero[0x16c];
  if ((m + 1) * 0x16c > sizeof S_00D0CC60) return zero;
#endif
  return &S_00D0CC60[m * 0x16c];
}
static const uint8_t *nodeb(int32_t n, uint32_t st, uint32_t base_off, const uint8_t *tab) {
#ifndef RE_HOOK_BUILD
  static const uint8_t zero[0x48];
  if (n < 0 || (uint32_t)n * st + base_off + st > 0x40000u) return zero;
#else
  (void)base_off;
#endif
  return tab + (uint32_t)n * st;
}
static void *glide_proc(const char *name) {
  for (int i = 0; i < P33_GlideCount(); i++)
    if (strcmp(P33_GlideName(i), name) == 0) return P33_GlideProc(i);
  return NULL;
}
static void tex_filter(int32_t a, int32_t b, int32_t c) {   /* (*01270d6c) = grTexFilterMode */
  void (P119_STD *f)(int32_t, int32_t, int32_t) = (void (P119_STD *)(int32_t, int32_t, int32_t))glide_proc("_grTexFilterMode@12");
  if (f != NULL) f(a, b, c);
}
static float oow_at(float z) {
  long zi = lrintf(z);
#ifndef RE_HOOK_BUILD
  if (zi < 0 || zi >= (long)(RE_OOW_N)) return 0.0f;
#endif
  return RE_OOW(zi);
}

/* ---- 004c0c6f: колпак ---- */
/* P119_Hubcap — Game.exe 004c0c6f.  The hubcap that flies off the player's car.  draw = 0: physics step (spawned
   when the car rolls hard; flight in P98_CarBufC: matrix, position +0xd0, velocity +0xe0, counter +0xf4; bounces
   off the road).  draw = 1: draws the HUBCAP model and its shadow (P110_GlowIcon quad). */
void P119_Hubcap(int32_t draw) {
  uint8_t *b = P98_CarBufC;   /* 010de220..010de318 */
  if (draw == 0) {
    if (G6_00B5A778 == 0 && 0 < P95_Deb0) P95_Deb0 = P95_Deb0 - 1;
    if (rd32(b + 0xf4) < 1 && P95_Deb0 == 0) {
      const uint8_t *c = carp(0);
      int32_t s = (int32_t)((uint32_t)rd32(c + 0x4c) + (uint32_t)rd32(c + 0x50) + (uint32_t)rd32(c + 0x54));
      if (s < -1000000 || 1000000 < s) {
        P100_MarkerSpawn(s < -1000000 ? 2 : 0);
#ifndef RE_HOOK_BUILD
        P95_Deb0 = (P95_Deb1 >= 0 && P95_Deb1 < 4) ? (int32_t)P95_DebRnd[P95_Deb1] : 0;
#else
        P95_Deb0 = (int32_t)P95_DebRnd[P95_Deb1];
#endif
        P95_Deb1 = P95_Deb1 + 1;
      }
    } else {
      if (G6_00B5A778 == 0) wr32(b + 0xf4, rd32(b + 0xf4) - 1);
      if (0 < rd32(b + 0xf4) && G6_00B5A778 == 0) {
        wrf(b + 0xd0, rdf(b + 0xe0) / 2.0f + rdf(b + 0xd0));   /* 00546050 = 2.0 */
        wrf(b + 0xd4, rdf(b + 0xe4) / 2.0f + rdf(b + 0xd4));
        wrf(b + 0xd8, rdf(b + 0xe8) / 2.0f + rdf(b + 0xd8));
        P44_RotX((float *)(void *)(b + 0x90), 0x6e);
        wrf(b + 0xe4, rdf(b + 0xe4) + 5.0f);                    /* 00546188 */
        int32_t h = P100_RoadHeightF((const float *)(const void *)(b + 0xd0));
        P119_GroundY = -0x3c - h;
        if ((float)P119_GroundY <= rdf(b + 0xd4)) {
          wrf(b + 0xe4, -(rdf(b + 0xe4) * 0.7f));               /* 00546168 */
          wrf(b + 0xd4, (float)P119_GroundY);
        }
      }
    }
    return;
  }
  if (rd32(b + 0xf4) < 1) return;
#ifndef RE_HOOK_BUILD
  if (P26_ModelHubcap == 0) return;
#endif
  float m[16];
  Mat3MulT_005284AC((const float *)(const void *)(b + 0x50), (const float *)(const void *)(b + 0x90), m);
  const uint8_t *mdl = (const uint8_t *)P79_PTR(P26_ModelHubcap);
  int32_t vis = P82_SphereVis3D((const float *)(const void *)(b + 0xd0), rdf(mdl + 0xc));
  if (vis == 0 || P110_GlowIcon == 0) return;
  const float px = rdf(b + 0xd0), py = rdf(b + 0xd4), pz = rdf(b + 0xd8);
  float v[3] = { px - P44_CamX, py - P44_CamY, pz - P44_CamZ };
  P44_MatPtr = (float *)P44_ViewMatT;
  P44_Xform(v);
  if (P62_I252B78 != 1) { if (P97_GrAlpha) P97_GrAlpha(3, 8, 0, 1, 1); if (P97_GrDepth) P97_GrDepth(4); P62_I252B78 = 1; }
  P84_DrawModel((uint32_t)P26_ModelHubcap, m, v, vis == 1 ? 0 : 1);
  if (P62_I252B78 != 0) { if (P97_GrAlpha) P97_GrAlpha(3, 8, 0, 2, 1); if (P97_GrDepth) P97_GrDepth(7); P62_I252B78 = 0; }
  if (P13_00d11880 == 0) return;
  /* тень: квадрат ±25 на высоте дороги − 5 */
  static const float sx[4] = { -1, 1, 1, -1 }, sz[4] = { -1, -1, 1, 1 };
  float q[4][3];
  const float gy = (float)(P119_GroundY - 5) - P44_CamY;
  for (int k = 0; k < 4; k++) {
    q[k][0] = (px - P44_CamX) + sx[k] * 25.0f;   /* 005461f0 */
    q[k][1] = gy;
    q[k][2] = (pz - P44_CamZ) + sz[k] * 25.0f;
    P44_MatPtr = (float *)P44_ViewMatT;
    P44_Xform(q[k]);
  }
  for (int k = 0; k < 4; k++) if (!(P95_Near < q[k][2])) return;
  for (int k = 0; k < 4; k++) if (!(q[k][2] < Q01270C24)) return;
  const uint8_t *ic = (const uint8_t *)re_ptr(P110_GlowIcon);
#ifndef RE_HOOK_BUILD
  if (ic == NULL) return;
#endif
  p85_rv rv[4];
  memset(rv, 0, sizeof rv);   /* z, ooz, a в оригинале не заданы */
  for (int k = 0; k < 4; k++) {
    float oow = oow_at(q[k][2]);
    rv[k].oow = oow;
    rv[k].x = (q[k][0] * P43_ScaleA * oow + P43_OffX) - P43_Half;
    rv[k].y = (q[k][1] * P43_ScaleA * oow + P43_OffY) - P43_Half;
    rv[k].r = 100.0f; rv[k].g = 100.0f; rv[k].b = 100.0f;
  }
  P12_Fn00426580(0);
  if ((uint32_t)ic[8] != (uint32_t)P86_CurTex) {
    P86_CurTex = (int32_t)ic[8];
    if (P86_TexSrc) P86_TexSrc(0, (uint32_t)rd32(&g_01145a60[ic[8] * 0x10 + 8]), 3, (uint32_t)rd32(&g_01145a60[ic[8] * 0x10 + 0xc]));
  }
  const uint8_t U[4] = { ic[9], ic[0xb], ic[0xb], ic[9] }, V[4] = { ic[10], ic[10], ic[0xc], ic[0xc] };
  for (int k = 0; k < 4; k++) { rv[k].tmu[0] = (float)U[k] * rv[k].oow; rv[k].tmu[1] = (float)V[k] * rv[k].oow; }
  if (P85_BlendCur != 2) { if (P85_BlendFn) P85_BlendFn(0, 6, 4, 0); P85_BlendCur = 2; P69_BlendOn = 2; }
  if (P85_RasterB) { P85_RasterB(&rv[0], &rv[1], &rv[2]); P85_RasterB(&rv[0], &rv[2], &rv[3]); }
}

/* ---- общее окончание появления машины трафика: модель, земля, точка отсчёта ---- */
/* Common end of a traffic spawn: model, ground height and reference point of car i. */
static void spawn_tail(int32_t i, uint8_t *r, uint8_t *c, int32_t x, int32_t z, int32_t late_model) {
  c[2] = r[0xc];
  wr32(c + 0xc8, x);
  wr32(c + 0xd0, z);
  P101_CarGround((p99_car_t *)(void *)c, r);
  if (late_model == 0) { P99_CarModelClean(i); P59_ObjDir(c, 1); }
  const uint8_t *o = tcar(r[0]);
  wr32(r + 0x48, rd32(o + 0xc8) + 0x2ee);
  wr32(r + 0x4c, rd32(o + 0xd0) - 0x2ee);
  P11_00ba52d0 = fround((float)rd32(r + 0x48) * P63_Scale);
  wr32(r + 0x48, P11_00ba52d0);
  P11_00ba52d0 = fround((float)rd32(r + 0x4c) * P63_Scale);
  wr32(r + 0x4c, P11_00ba52d0);
  r[9] = (uint8_t)P59_CellLeft(r);
  r[0x13] = 2;
  if (late_model != 0) { P99_CarModelClean(i); P59_ObjDir(c, 1); }
}
/* Assigns cop slot k to traffic record r / car c (see P119_TrafficSpawn). */
static void cop_slot(int32_t i, uint8_t *r, uint8_t *c, int32_t k) {
  r[5] = (uint8_t)k;
  r[0xd] = 0x19;
  wr16(r + 0x16, 0);
#ifndef RE_HOOK_BUILD
  if (k < 1 || k > 8) { G0112B284 = G0112B284 + 1; return; }
#endif
#ifdef RE_HOOK_BUILD
  P51_InitCarSlot((uint32_t)(uintptr_t)c, (uint8_t *)&P12_0112da00[(k - 1) * 0x336], (uint32_t)(k - 1));
#else
  P51_InitCarSlot(re_addr(c), (uint8_t *)&P12_0112da00[(k - 1) * 0x336], (uint32_t)(k - 1));
#endif
  (void)i;
  G0112B284 = G0112B284 + 1;
}

/* ---- 00491a56: появление машины трафика ---- */
/* P119_TrafficSpawn — Game.exe 00491a56.  Spawns traffic car i at road node `node` on side `lane` (or at point
   (x, z) when node == -1): checks the space, picks model and colour.  Returns 1 on success, 0 if refused. */
int32_t P119_TrafficSpawn(int32_t i, int32_t node, int32_t lane, int32_t x, int32_t z) {
  int32_t far_ = 0;
  uint8_t lane8 = (uint8_t)lane;
  uint8_t *r = trec(i), *c = tcar(i);
  r[1] = 0;
  const uint8_t *nd = nodeb(node, 0x14, 0, P11_00c12c60), *nn = nodeb(node, 0x42, 0, P11_00bf1c40);
  P14_Fn0048DB65(c, 0x148);
  c[0] = (uint8_t)(i + 1);
  if (node != -1) {
    const int use41 = !(G6_00B87EB0 == 0 && G6_00B87EAC == 0);
    int8_t nk = (int8_t)nn[0x3d];
    if (nd[0x10] == 1) {
      int32_t px = rd32((use41 ? carp(0x41) : carp(0)) + 0xc8);
      int bv = px <= rd32(nd) * 0x5dc;
      uint8_t b3 = bv ? 3 : 1, l1c = b3 == 1 ? 3 : 1;
      if (nk == -0x7f) { lane8 = 1; l1c = 1; }
      else if (nk == -0x7d) { lane8 = 1; l1c = 3; }
      wr32(r + 0x24, lane8 == 1 ? l1c : b3);
    } else {
      int32_t pz = rd32((use41 ? carp(0x41) : carp(0)) + 0xd0);
      int bv = pz <= rd32(nd + 4) * -0x5dc;
      uint32_t l1c = bv ? 2 : 0;
      if (nk == -0x80) { lane8 = 1; l1c = 0; }
      else if (nk == -0x7e) { lane8 = 1; l1c = 2; }
      wr32(r + 0x24, (int32_t)(lane8 == 1 ? l1c : (bv ? 0u : 2u)));
    }
  }
  r[7] = 0; r[8] = 0; r[2] = 0;
  wr32(r + 0x28, node);
  if (node == -1) far_ = 1;
  else if ((nn[0x3c] & 1) != 0 && (Rand_004D9078() & 7) == 0 && P21_CountActiveEntries(node) == 0) far_ = 1;
  if (far_) {
    if (node == -1) {
      P63_NearestAdd(x, z);
      if (P63_Near < P103_145A44) { P74_FreeTraffic(i); return 0; }
    } else {
      P75_TrafficPos(node, rd32(r + 0x24), rd32(r + 0x34), 1, 0xff);
      if ((rd32(r + 0x24) & 1) == 0) x = P54_G40; else z = P54_G44;
      switch (rd32(r + 0x24)) {
        case 0: x += 0x1d6; break;
        case 1: z -= 0x1d6; break;
        case 2: x -= 0x1d6; break;
        case 3: z += 0x1d6; break;
      }
      P63_NearestAdd(x, z);
      if (P63_Near < P103_145A44) { P74_FreeTraffic(i); return 0; }
      if (P101_RoadNode(x, z, (int8_t)r[0x24]) != 0) { P74_FreeTraffic(i); return 0; }
      if (P101_RdLeft < 0x1194 || P101_RdDist < 3000) { P74_FreeTraffic(i); return 0; }
    }
    if ((Rand_004D9078() & 3) != 0) r[7] = 1;
    r[1] = 1; r[0xa] = 0; r[0xb] = 0xff;
    const uint8_t *o = tcar(r[0]);
    wr32(r + 0x48, rd32(o + 0xc8) + 0x2ee);
    wr32(r + 0x4c, rd32(o + 0xd0) - 0x2ee);
    P11_00ba52d0 = fround((float)rd32(r + 0x48) * P63_Scale);
    wr32(r + 0x48, P11_00ba52d0);
    P11_00ba52d0 = fround((float)rd32(r + 0x4c) * P63_Scale);
    wr32(r + 0x4c, P11_00ba52d0);
  } else {
    r[1] = 2; r[8] = 1;
    P101_RoadNode(x, z, (int8_t)r[0x24]);
    if (P118_TrafficTurn(r) == 0) return 0;
    P75_TrafficPos(rd32(r + 0x28), rd32(r + 0x24), rd32(r + 0x34), 0, 0xff);
    if ((rd32(r + 0x24) & 1) == 0) x = P54_G40; else z = P54_G44;
    if (P103_143724 < P95_CountNear(x, z, P103_1426F4)) { P74_FreeTraffic(i); return 0; }
    if (P63_Near < P103_1426EC) { P74_FreeTraffic(i); return 0; }
    wr32(r + 0x18, P101_RdDist);
    wr32(r + 0x1c, P101_RdLeft);
    wr32(r + 0x20, (int32_t)(int16_t)P101_RdNode);
    wr16(r + 0xe, P101_RdLane);
  }
  wr32(c + 0x100, node == -1 ? (int32_t)((uint32_t)lane8 << 10) : (int32_t)((uint32_t)rd32(r + 0x24) << 10));
  wr32(r + 0x44, 0x7fffffff); wr32(r + 0x40, 0x7fffffff); wr32(r + 0x38, 0); wr32(r + 0x3c, 0x82);
  if (D_00b87e30 == 6) r[0xc] = (uint8_t)((int32_t)Rand_004D9078() % 2 + 3);
  else r[0xc] = (uint8_t)((int32_t)Rand_004D9078() % 9 + 3);
  if (r[0xc] == 9) r[0xd] = 0x10;
  else r[0xd] = (uint8_t)((int32_t)Rand_004D9078() % 10 + 4);
  r[5] = 0;
  if (P62_I14428C == 1 && !far_) {
    int32_t k = P62_FindFreeTrafficSlot();
    if (k != -1) cop_slot(i, r, c, k);
    P62_I14428C = 0;
  }
  if (r[5] != 0) {
    if (P28_BadGuyFlag == 1) {
      if (P95_SndOn == 1 && (Rand_004D9078() & 1) != 0) r[0xc] = 1;
      else {
        /* .data 005512f0: по 4 байта на режим игры — число вариантов и до трёх моделей */
        static const uint8_t tab[6][4] = { { 2, 17, 8, 0 }, { 3, 10, 4, 7 }, { 0, 0, 0, 0 }, { 3, 5, 12, 8 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } };
        r[0xc] = 2;
        int32_t md = D_00b87e30;
#ifndef RE_HOOK_BUILD
        if (md < 0 || md > 5) md = 2;
#endif
        uint8_t n = tab[md][0];
        int32_t rr = (int32_t)Rand_004D9078();
        if (rr < 0) rr = -rr;
#ifndef RE_HOOK_BUILD
        if (n == 0) n = 1;   /* в оригинале деление на 0 */
#endif
        r[0xd] = tab[md][1 + rr % (int32_t)n];
      }
    } else r[0xc] = 1;
  }
  spawn_tail(i, r, c, x, z, 1);
  return 1;
}

/* ---- 00417386: клавиши экрана выбора машины ---- */
static uint8_t sel_byte(int32_t off) {   /* байт таблицы 005fea14; .data 0054e320..0054e33b — копия в native */
  static const uint8_t k_sel[0x1c] = { 10, 1, 1, 1, 11, 0, 0, 0, 12, 1, 1, 1, 13, 0, 0, 0, 14, 1, 1, 2, 15, 2, 2, 0, 16, 0, 0, 1 };
  uint32_t a = P119_SelPtr + (uint32_t)off;
#ifndef RE_HOOK_BUILD
  if (a >= 0x0054e320u && a < 0x0054e33cu) return k_sel[a - 0x0054e320u];
  const uint8_t *p = (const uint8_t *)re_ptr(a);
  return p ? *p : 0;
#else
  (void)k_sel;
  return *(const uint8_t *)re_ptr(a);
#endif
}
uint8_t P119_SelByte(int32_t off) { return sel_byte(off); }
/* P119_CarSelKey — Game.exe 00417386.  Keys of the car-select screen: Esc -> -1, Left/Right -> neighbour camera
   from the table 005fea14 (P118_CamRoute), Enter -> replay speed.  row = current menu row. */
int32_t P119_CarSelKey(int32_t row) {
  if (IsFlagSetNotMasked_004E383A(1) != 0) { Ui00418886(); return -1; }
  if (IsFlagSetNotMasked_004E383A(0xcb) != 0) {
    Ui00418886();
    P119_SelIdx = sel_byte(2 + P119_SelIdx * 4);
    P118_CamRoute(sel_byte(P119_SelIdx * 4));
    return 0;
  }
  if (IsFlagSetNotMasked_004E383A(0xcd) != 0) {
    Ui00418886();
    P119_SelIdx = sel_byte(3 + P119_SelIdx * 4);
    P118_CamRoute(sel_byte(P119_SelIdx * 4));
    return 0;
  }
  if (IsFlagSetNotMasked_004E383A(0x1c) != 0) {
    Ui00418886();
    int32_t k = (int32_t)sel_byte(1 + P119_SelIdx * 4) + row * 3;
#ifndef RE_HOOK_BUILD
    if (k < 0 || k >= 9) { P68_B87E54 = 0; return -1; }
#endif
    P68_B87E54 = (int32_t)P100_SpeedTab[k];
    return -1;
  }
  return 0;
}

/* ---- 0040cb9f: кадр меню ---- */
/* P119_MenuFrame — Game.exe 0040cb9f.  One front-end frame on timer 005f7e60: CD audio, sound, backgrounds, menu
   items, captions, wait bars, LFB access and buffer swap. */
void P119_MenuFrame(void) {
  if (P31_Active == 0) return;
  P12_005f7e60 = P12_005f7e60 - 1;
  if (P12_005f7e60 != 0) return;
  if (Q00B87E90 != 0 && P25_CdPlaying == 0) { P25_InitCDAudio(); P25_PlayCDTrack(2); }
  P115_SndUpdate();
  InitSoundVolumes_00523C56();
  P52_GlideFogMode();
  MenuReturnOne();
  P58_Backgrounds();
  P98_ItemsDraw();
  P117_TextList();
  if (P45_Busy != 0) {
    static uint8_t col[4];   /* чёрный (локальная в оригинале) */
    int32_t h = P45_Step;
    SndHelper_00407D56(0, 0x30, re_addr(col), 0x280, (uint32_t)h);
    SndHelper_00407D56(0, 0x1b0 - h, re_addr(col), 0x280, (uint32_t)(h + 1));
  }
  SndHelper_00407D97(0, 0xff);
  P105_LfbToMenu();
  P47_GlideSwap();
  P12_005f7e60 = (int32_t)P21_FrameTicks();
}

/* ---- 004aff92: пыль из-под машины ---- */
/* P119_CarDust — Game.exe 004aff92.  Dust / smoke from under car i (model point +0xc0) via P118_SkidFx kind 2/1. */
void P119_CarDust(int32_t i, int32_t kind, int32_t dist) {
  if (G6_00B5A778 != 0) return;
  const uint8_t *c = carp(i), *m = carmodel(c[2]);
  float v[4] = { rdf(m + 0xc0), rdf(m + 0xc4), rdf(m + 0xc8), rdf(m + 0xcc) };
#ifndef RE_HOOK_BUILD
  if (i < 0 || i >= 65) i = 0;
#endif
  P44_MatPtr = (float *)(void *)P98_CarMat[i];
  P44_XformT(v);
  v[0] += (float)rd32(c + 0xc8);
  v[1] -= (float)rd32(c + 0xcc);
  v[2] += (float)rd32(c + 0xd0);
  float w[4] = { 0, 0, 0, 0 };
  P94_Wobble(w, 0);
  P118_SkidFx(v, 0x46, 0xfa, kind == 0 ? 2 : 1, dist, w, 0);
}

/* ---- 004943dc: такт поворота записи трафика ---- */
/* P119_TrafficStep — Game.exe 004943dc (traffic state 3, TRF_STEP).  Turning at a junction: once the car is within
   TREC_SPEED + 0x352 of the target point (along its direction) and its heading is within 0x20 of the new direction
   (+0x30), switches back to driving (state 2) on the new segment: new road node, P118_TrafficTurn and the next
   target point; while the road word has bit 0x4000 it only aligns the car (P102_TrafficAlign). */
void P119_TrafficStep(uint8_t *r) {
  if (r[TREC_SUBSTATE] == 1) return;
  if (rd32(r + TREC_SPEED) == 0) return;
  uint8_t *c = tcar(r[TREC_CAR]);
  int16_t s = (int16_t)P72_RoadWord(rd32(c + CAR_POS_X), rd32(c + CAR_POS_Z));
  wr32(r + TREC_NEXT_NODE, s);
  if (r[TREC_AT_TARGET] == 0) {
    switch (rd32(r + TREC_ROAD_DIR)) {
      case 0: case 2:
        if (rd32(r + TREC_SPEED) + 0x352 <= iabs(rd32(c + CAR_POS_Z) - rd32(r + TREC_TGT_Z))) return;
        r[TREC_AT_TARGET] = 1; break;
      case 1: case 3:
        if (rd32(r + TREC_SPEED) + 0x352 <= iabs(rd32(c + CAR_POS_X) - rd32(r + TREC_TGT_X))) return;
        r[TREC_AT_TARGET] = 1; break;
      default: break;
    }
  }
  if (P62_HeadingDelta(r, (uint32_t)rd32(r + TREC_DIR2) << 10) >= 0x20) return;
  if (((int32_t)s & 0x4000) == 0) {
    r[TREC_STATE] = 2;
    wr32(r + TREC_ROAD_DIR, rd32(r + TREC_DIR2));
    wr32(r + TREC_NEXT_NODE, rd32(r + TREC_NEXT_NODE2));
    P101_RoadNode(rd32(c + CAR_POS_X), rd32(c + CAR_POS_Z), (int8_t)r[TREC_ROAD_DIR]);
    wr32(r + TREC_ROAD_DIST, P101_RdDist);
    wr32(r + TREC_ROAD_DONE, P101_RdLeft);
    wr32(r + TREC_ROAD_NODE, (int32_t)(int16_t)P101_RdNode);
    wr16(r + TREC_LANE, P101_RdLane);
    P118_TrafficTurn(r);
    if (r[TREC_STATE] == 2) {
      P75_TrafficPos(rd32(r + TREC_NEXT_NODE), rd32(r + TREC_ROAD_DIR), rd32(r + TREC_F34), 2, r[TREC_CLASS]);
      wr32(r + TREC_TGT_Z, P54_G44);
      wr32(r + TREC_TGT_X, P54_G40);
    }
  } else P102_TrafficAlign(r, 0, 0, (int8_t)r[TREC_DIR2]);
}

/* ---- 004de86c: следы шин машины i ---- */
/* P119_CarSkids — Game.exe 004de86c.  Skid marks of car i (not in rain): front wheels when the front slip exceeds
   15000, rear wheels when CAR_BURNOUT is set or the rear slip >= 0x3a99, only for wheels on
   the ground; P102_D077A0[w] = -1 ends a mark, 1 continues it. */
void P119_CarSkids(int32_t i) {
  if (G6_00B5A778 != 0 || P26_FxA != 0) return;
  if (i == 0x41 && P101_RecSaved != 0 && P101_RecState == 0) return;
  const uint8_t *c = carp(i);
  int b = 0;
  if (rd32(c + CAR_WHEELS_DOWN) != 0) {
    if (rd32(c + CAR_BURNOUT) != 0 || iabs(rd32(c + CAR_SLIP_REAR)) >= 0x3a99) b = 1;
  }
  int32_t sp = iabs(rd32(c + CAR_SLIP_FRONT));
  P101_WheelsGround(c, P119_Wheels);
  if (15000 < sp || b) {
    for (int32_t w = 0; w < 4; w++) {
      if (c[CAR_WHEEL + w * CAR_WHEEL_SIZE] == 0 || ((w & 1) != 0 && !b) || ((w & 1) == 0 && sp <= 15000)) P102_D077A0[w] = -1;
      else {
        P102_D04D14 = P102_D077A0[w] != -1;
        P117_SkidRecB(w, &P119_Wheels[w * 4]);
        P102_D077A0[w] = 1;
      }
    }
  } else {
    P102_D077A0[0] = -1; P102_D077A0[1] = -1; P102_D077A0[2] = -1; P102_D077A0[3] = -1;
  }
  P56_CopyBlock16((const uint32_t *)(const void *)P119_Wheels);
}

/* ---- 0048fbcf: скорость записи трафика ---- */
/* Re-reads the road node of the record's car and re-plans the turn. */
static void turn_again(uint8_t *r) {
  const uint8_t *c = tcar(r[0]);
  P101_RoadNode(rd32(c + CAR_POS_X), rd32(c + CAR_POS_Z), (int8_t)r[0x24]);
  P118_TrafficTurn(r);
}
static void limit(uint8_t *r, int32_t v) { wr32(r + TREC_TGT_SPEED, v); r[3] = 1; }
/* P119_TrafficSpeed — Game.exe 0048fbcf.  Speed control of a traffic car: target speed from the road (P63_CarSpeed),
   stop lines / give-way checks near junctions (0x82 / 0x3c = slow speeds), the junction type of the node
   (P51_NodeKind) and an obstacle ahead (checked every 4th frame); converts the speed error to throttle
   (CAR_THROTTLE: brake (d * 0xdac) / 32, d >= -0x20; accelerate (d * 0x9c4) / 32, d <= 0x20).  A stopped car with
   flag 8 parks (state 1). */
void P119_TrafficSpeed(uint8_t *r, uint8_t *car) {
  wr32(car + CAR_THROTTLE, 0);
  if (r[2] == 1 || r[1] == 1 || r[1] == 9) { r[0x11] = 0; return; }
  if (r[3] == 0) wr32(r + TREC_TGT_SPEED, P63_CarSpeed(r));
  if ((r[0x13] & 8) != 0 && rd32(car + CAR_SPEED) == 0 && rd32(r + TREC_TGT_SPEED) == 0) {
    r[0x13] &= 0xf7;
    r[1] = 1; r[8] = 0; r[0xb] = 0xff;
    if ((Rand_004D9078() & 3) != 0) r[7] = 1;
    return;
  }
  if (rd32(r + TREC_ROAD_DIST) < 3000 && (r[0x13] & 2) != 0) {
    wr32(r + TREC_TGT_Z, 0x7fffffff); wr32(r + TREC_TGT_X, 0x7fffffff);
    r[0x13] &= 0xfd;
    turn_again(r);
  }
  switch (P51_NodeKind(r)) {
    case 0: case 3:
      if (r[3] == 0 && rd32(r + TREC_ROAD_DIST) < 0x28a && (uint32_t)(P62_Frame & 3) == (uint32_t)rd32(r + TREC_ROAD_DIR)) {
        int32_t k = rd32(r + 0x34), stop;
        if (k == -1) stop = P63_CanEnter(r) == 1 ? 0x3c : -1;
        else if (k == 0) stop = P59_TrafficCheck(r, 0) == 0 ? 0x82 : -1;
        else if (k == 1) stop = P59_TrafficCheck(r, 1) == 0 ? 0x3c : -1;
        else break;
        if (stop != -1) limit(r, stop);
        else if ((r[0xe] & 4) != 0 && r[4] <= G00BF1C20 && r[3] == 0) turn_again(r);
      }
      break;
    case 1:
      if (r[3] == 0 && rd32(r + TREC_ROAD_DIST) < 0x28a && P103_TrafficCanGo(r) != 0) {
        r[3] = 1;
        wr32(r + TREC_TGT_SPEED, rd32(r + 0x34) == 0 ? 0x82 : 0x3c);
      }
      break;
    case 2:
      if (r[1] != 3 && (rd32(r + 0x34) != 0 || r[3] == 0)) {
        r[3] = 0;
        if (0x5a < rd32(r + TREC_TGT_SPEED)) wr32(r + TREC_TGT_SPEED, 0x5a);
        if (rd32(r + TREC_ROAD_DIST) < 0x28a) { r[0x13] &= 0xde; wr32(r + TREC_TGT_SPEED, 0); }
      }
      break;
    default: break;
  }
  int32_t want = rd32(r + TREC_TGT_SPEED);
  if ((r[0] & 3) == (uint32_t)(P62_Frame & 3)) r[0x12] = (uint8_t)P118_TrafficBlocked(r);
  if (r[0x12] != 0) want = 0;
  int32_t d = want - rd32(r + TREC_SPEED);
  if (rd32(car + CAR_WHEELS_DOWN) < 4 && 0 < d) r[0x11] = 0;
  else if (d < 1) {
    if (d < 0) {
      if (r[0x11] < 0x80) r[0x11]++;
      if (r[0x11] < 2) d = -8;
      if (d < -0x20) d = -0x20;
      wr32(car + CAR_THROTTLE, (d * 0xdac) / 32);
    }
  } else {
    r[0x11] = 0;
    if (0x20 < d) d = 0x20;
    wr32(car + CAR_THROTTLE, (d * 0x9c4) / 32);
  }
}

/* ---- 004928c9: стоящая машина трафика ---- */
/* P119_TrafficParked — Game.exe 004928c9.  Places a parked traffic car (a police car when a cop slot is free,
   004a6749) at (x, z) with the given heading. */
void P119_TrafficParked(int32_t heading, int32_t x, int32_t z) {
  int32_t i = PopIndex00493E9B();
  if (i == -1) return;
#ifndef RE_HOOK_BUILD
  if (i < 0 || i >= 0x40) return;
#endif
  uint8_t *r = trec(i), *c = tcar(i);
  P14_Fn0048DB65(c, 0x148);
  c[0] = (uint8_t)(i + 1);
  r[7] = 0; r[8] = 0; r[2] = 0;
  wr32(r + 0x28, -1);
  r[1] = 2; r[8] = 1;
  if (P118_TrafficTurn(r) == 0) return;
  wr32(c + 0x100, heading);
  wr32(r + 0x44, 0x7fffffff); wr32(r + 0x40, 0x7fffffff); wr32(r + 0x38, 0); wr32(r + 0x3c, 0x82);
  r[0xd] = (uint8_t)((int32_t)Rand_004D9078() % 10 + 4);
  r[0xc] = 1;
  r[5] = 0;
  int32_t k = P62_FindFreeTrafficSlot();
  if (k == -1) return;
  cop_slot(i, r, c, k);
  r[1] = 4;
  spawn_tail(i, r, c, x, z, 0);
}

/* ---- 0050230a: HUD ---- */
/* HUD (0050230a) helpers: store a float into a HUD record, read a script variable by address, place a gauge. */
static void hud_setf(uint32_t *h, int k, float v) { memcpy(&h[k], &v, 4); }
static int32_t var24(uint32_t addr) {
  const uint8_t *p = (const uint8_t *)re_ptr(addr);
#ifndef RE_HOOK_BUILD
  if (p == NULL) return 0;
#endif
  return rd32(p + 0x24);
}
/* v2.15: полоса (Damage/Felony/соперник) — якорь по её центру в 640-кадре: левая треть — к левому краю, правая — к правому */
static void gauge_anchored(uint8_t *p) {
#ifndef RE_HOOK_BUILD
  float x, w; memcpy(&x, p, 4); memcpy(&w, p + 8, 4);
  float c = x + w * 0.5f;
  plat_hud_anchor(c < 213.0f ? -1 : (c > 427.0f ? 1 : 0));
#endif
  P110_Gauge(p);
#ifndef RE_HOOK_BUILD
  plat_hud_anchor(0);
#endif
}
/* P119_Hud — Game.exe 0050230a.  Updates and draws the HUD: bar values (damage, felony, opponent), radar scale,
   radar, arrows and speed. */
void P119_Hud(void) {
  if (P29_Mode != 0) return;
  if (P102_DmgVar != 0 && MenuOptBDFA4C == 0) SetField24_00502779((uint8_t *)P102_HudDmg, var24(P102_DmgVar));
  if (P102_FelVar != 0) SetField24_00502779((uint8_t *)P102_HudFel, var24(P102_FelVar));
  if (P102_OppVar != 0) SetField24_00502779((uint8_t *)P101_Hud, var24(P102_OppVar));
  const int32_t W = P19_ScrW, H = P19_ScrH;
  P94_RadarK = 0.00222167978f * (float)W * P19_Scale;               /* 00546a1c */
  P56_F573FA0 = (((float)W / 640.0f) * 540.0f - (float)(W / 2)) * P19_Scale + (float)(W / 2);   /* 00546a18 = 540 */
  P56_F573FA4 = (((float)H / 480.0f) * 380.0f - (float)(H / 2)) * P19_Scale + (float)(H / 2);   /* 00546a14 = 380 */
  if (P95_B87F08 == 0) { if (P95_C818B8 != 0) P12_00c808d0 = (float)P99_MrkA; }
  else P12_00c808d0 = (float)P95_BDFA0C;
  if (D_00b87e30 < 4) hud_setf(P102_HudFel, 4, (float)G2_00D11A5C);
  if (MenuOptBDFA4C == 0) hud_setf(P102_HudDmg, 4, (float)G00BDF984);
#ifndef RE_HOOK_BUILD
  plat_hud_anchor(1);   /* v2.15: радар, стрелки погони и спидометр — к правому краю (x 640-кадра + 2S) */
#endif
  if (MenuVarD118C8 != 0 && P62_HudOff1 == 0 && P56_B87EA8 == 0 && P62_HudOff2 == 0) {
    if (P95_SndReady != 0 && 0x2a9 < G2_00D11A5C && MenuVarB31F04 == 0) P109_RadarArrows();
    tex_filter(0, 0, 0);
    P117_Radar();
    tex_filter(0, 1, 1);
    P62_SpeedText();
  }
#ifndef RE_HOOK_BUILD
  plat_hud_anchor(0);
#endif
  if (P62_HudOff1 == 0 && P62_HudOff2 == 0 && P17_Cond1 == 0) {
    if (MenuOptBDFA4C == 0) { hud_setf(P102_HudDmg, 5, (float)P102_DmgMax); gauge_anchored((uint8_t *)P102_HudDmg); }
    gauge_anchored((uint8_t *)P102_HudFel);
    gauge_anchored((uint8_t *)P101_Hud);
  } else if ((MenuMode1271060 == 6 || MenuMode1271060 == 0xb) && MenuOptBDFA4C == 0) {
    hud_setf(P102_HudDmg, 5, (float)P102_DmgMax);
    gauge_anchored((uint8_t *)P102_HudDmg);
  }
}
