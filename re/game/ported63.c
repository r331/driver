/* Traffic helpers: cars near a road node, nearest traffic car, junction entry test, target
   speed; plus a plane test, sphere hits and two spline evaluators (x87 precision kept). */
#include "ported63.h"
#include <math.h>
#include <string.h>
#include "names_g3.h"
#include "carfields.h"

#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P63_Scale")
#undef P63_Scale
#pragma push_macro("P63_Scale") /*gvi*/
#undef P63_Scale /*gvi*/
float P63_Scale;
#pragma pop_macro("P63_Scale") /*gvi*/
#pragma pop_macro("P63_Scale")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P63_Near")
#undef P63_Near
#pragma push_macro("P63_Near") /*gvi*/
#undef P63_Near /*gvi*/
int32_t P63_Near;
#pragma pop_macro("P63_Near") /*gvi*/
#pragma pop_macro("P63_Near")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P63_Dist")
#undef P63_Dist
#pragma push_macro("P63_Dist") /*gvi*/
#undef P63_Dist /*gvi*/
p63_i32x64_t P63_Dist;
#pragma pop_macro("P63_Dist") /*gvi*/
#pragma pop_macro("P63_Dist")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P63_Ids")
#undef P63_Ids
#pragma push_macro("P63_Ids") /*gvi*/
#undef P63_Ids /*gvi*/
p63_i32x64_t P63_Ids;
#pragma pop_macro("P63_Ids") /*gvi*/
#pragma pop_macro("P63_Ids")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P63_Cnt0")
#undef P63_Cnt0
#pragma push_macro("P63_Cnt0") /*gvi*/
#undef P63_Cnt0 /*gvi*/
int32_t P63_Cnt0;
#pragma pop_macro("P63_Cnt0") /*gvi*/
#pragma pop_macro("P63_Cnt0")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P63_Cnt1")
#undef P63_Cnt1
#pragma push_macro("P63_Cnt1") /*gvi*/
#undef P63_Cnt1 /*gvi*/
int32_t P63_Cnt1;
#pragma pop_macro("P63_Cnt1") /*gvi*/
#pragma pop_macro("P63_Cnt1")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P63_Cnt2")
#undef P63_Cnt2
#pragma push_macro("P63_Cnt2") /*gvi*/
#undef P63_Cnt2 /*gvi*/
int32_t P63_Cnt2;
#pragma pop_macro("P63_Cnt2") /*gvi*/
#pragma pop_macro("P63_Cnt2")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P63_Cnt3")
#undef P63_Cnt3
#pragma push_macro("P63_Cnt3") /*gvi*/
#undef P63_Cnt3 /*gvi*/
int32_t P63_Cnt3;
#pragma pop_macro("P63_Cnt3") /*gvi*/
#pragma pop_macro("P63_Cnt3")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P63_LimA")
#undef P63_LimA
#pragma push_macro("P63_LimA") /*gvi*/
#undef P63_LimA /*gvi*/
p63_i32x4_t P63_LimA;
#pragma pop_macro("P63_LimA") /*gvi*/
#pragma pop_macro("P63_LimA")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P63_LimB")
#undef P63_LimB
#pragma push_macro("P63_LimB") /*gvi*/
#undef P63_LimB /*gvi*/
p63_i32x4_t P63_LimB;
#pragma pop_macro("P63_LimB") /*gvi*/
#pragma pop_macro("P63_LimB")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P63_SphN")
#undef P63_SphN
#pragma push_macro("P63_SphN") /*gvi*/
#undef P63_SphN /*gvi*/
int32_t P63_SphN;
#pragma pop_macro("P63_SphN") /*gvi*/
#pragma pop_macro("P63_SphN")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P63_Hits")
#undef P63_Hits
#pragma push_macro("P63_Hits") /*gvi*/
#undef P63_Hits /*gvi*/
p63_hits_t P63_Hits;
#pragma pop_macro("P63_Hits") /*gvi*/
#pragma pop_macro("P63_Hits")
#endif

/* rd32 — Unaligned int32 read at p + o. */
static int32_t rd32(const uint8_t *p, uint32_t o) { int32_t v; memcpy(&v, p + o, 4); return v; }
/* wr32 — Unaligned int32 write at p + o. */
static void    wr32(uint8_t *p, uint32_t o, int32_t v) { memcpy(p + o, &v, 4); }
/* rdf — Unaligned float read at p + o. */
static float   rdf(const uint8_t *p, uint32_t o) { float v; memcpy(&v, p + o, 4); return v; }
/* fistp: к ближайшему чётному; произведение float*float считается в расширенной точности, как в x87 */
/* RoundMul — round-to-nearest-even(v * P63_Scale) as x87 fistp, product in extended precision. */
static int32_t RoundMul(int32_t v) { return (int32_t)lrintl((long double)(float)v * (long double)P63_Scale); }
/* В native таблица трафика ровно 0x40 записей; оригинал при «режиме 0x41» читает ещё одну запись за ней. */
/* RecLimit — Native: clamp a traffic record count to the 0x40 records that exist (the original reads one
   record past the table in "0x41 mode"). */
static int32_t RecLimit(int32_t n) {
#ifndef RE_HOOK_BUILD
  if (n > 0x40) n = 0x40;
#endif
  return n;
}

/* P63_InitConsts — Native: initialise the .data constants — per-class speed caps P63_LimA {130, 162, 194, 226},
   distance thresholds P63_LimB {3500..3800} and the float 3.0 (0x00546034). */
void P63_InitConsts(void) {
#ifndef RE_HOOK_BUILD
  static const int32_t a[4] = { 130, 162, 194, 226 }, b[4] = { 3500, 3600, 3700, 3800 };
  memcpy(P63_LimA, a, sizeof a); memcpy(P63_LimB, b, sizeof b);
  P8_00546034 = 3.0f;   /* float-константа 3.0 из .data */
#endif
}

/* P63_NearOnNode — Game.exe 0048ea2c, cdecl.  Collect the traffic cars (other than `self`) relevant to entering `node`: cars heading to
   `node` in direction `dir` (TREC_ROAD_DIR or TREC_DIR2) are listed with their road distance;
   cars with TREC_F03 set still on node `alt` are listed with id | 0x80 and distance -1.
   Out: P63_Ids[], P63_Dist[].  Returns the count.  No bound on the output arrays (as original). */
int32_t P63_NearOnNode(uint32_t self, int32_t node, int32_t dir, int32_t alt) {
  const uint8_t *r = (const uint8_t *)TrafficRecs;
  int32_t n = 0;
  for (int32_t i = 0; i < RecLimit(P51_TrafficN); i++, r += TREC_SIZE) {
    if (r[TREC_F08] != 0 && r[TREC_CAR] != self) {
      if (rd32(r, TREC_NEXT_NODE) == node) {
        if (rd32(r, TREC_ROAD_DIR) == dir || rd32(r, TREC_DIR2) == dir) {
          P63_Dist[n] = rd32(r, TREC_ROAD_DIST);
          P63_Ids[n] = r[TREC_CAR];
          n++;
        }
      } else if (r[TREC_F03] != 0 && rd32(r, TREC_ROAD_NODE) == alt) {
        P63_Dist[n] = -1;
        P63_Ids[n] = r[TREC_CAR] | 0x80;   /* 0x80: car on the other node, no distance */
        n++;
      }
    }
  }
  return n;
}

/* P63_CountByNode — Game.exe 0048f3b4, cdecl.  Count active traffic cars heading to each of the nodes a, b, c, d (P63_Cnt0..3).
   Returns the total. */
int32_t P63_CountByNode(int32_t a, int32_t b, int32_t c, int32_t d) {
  const uint8_t *r = (const uint8_t *)TrafficRecs;
  P63_Cnt3 = 0; P63_Cnt2 = 0; P63_Cnt1 = 0; P63_Cnt0 = 0;
  for (int32_t i = 0; i < RecLimit(P51_TrafficN); i++, r += TREC_SIZE) {
    if (r[TREC_STATE] != 0) {
      int32_t node = rd32(r, TREC_NEXT_NODE);
      if (node == a) P63_Cnt0++;
      else if (node == b) P63_Cnt1++;
      else if (node == c) P63_Cnt2++;
      else if (node == d) P63_Cnt3++;
    }
  }
  return P63_Cnt0 + P63_Cnt1 + P63_Cnt2 + P63_Cnt3;
}

/* Abs — |v| (int32). */
static int32_t Abs(int32_t v) { return v < 0 ? -v : v; }

/* P63_NearestAdd — Game.exe 0048f4ad, cdecl.  Smallest Manhattan distance, in scaled map cells, from world (x, z) (rounded by half a cell
   0x2ee) to an active traffic car (state 1 or non-zero sub-state); starts at 0x400.  Stores it
   in P63_Near.  In chase modes (00b87eb0 / 00b87eac) 0x41 records are scanned.  The scaled
   coordinates are staged through 00ba52d0 as in the original. */
void P63_NearestAdd(int32_t x, int32_t z) {
  const uint8_t *r = (const uint8_t *)TrafficRecs;
  P11_00ba52d0 = RoundMul(x + 0x2ee);
  int32_t px = P11_00ba52d0;
  P11_00ba52d0 = RoundMul(z - 0x2ee);
  int32_t n = (P58_SB87EB0 == 0 && G6_00B87EAC == 0) ? P51_TrafficN : 0x41;
  P63_Near = 0x400;
  for (int32_t i = 0; i < RecLimit(n); i++, r += TREC_SIZE) {
    if (r[TREC_STATE] == 1 || r[TREC_SUBSTATE] != 0) {
      int32_t d = Abs(rd32(r, TREC_CELL_X) - px) + Abs(rd32(r, TREC_CELL_Z) - P11_00ba52d0);
      if (d < P63_Near) P63_Near = d;
    }
  }
}

/* P63_NearestRec — Game.exe 0048f5d8, cdecl.  Index of the active traffic car nearest (Manhattan, scaled cells, < 10000) to the player
   position P59_PosX/Z; -1 if none.  Also stored in P63_Near. */
int32_t P63_NearestRec(void) {
  const uint8_t *r = (const uint8_t *)TrafficRecs;
  int32_t best = 10000;
  P11_00ba52d0 = RoundMul(P59_PosX);
  int32_t px = P11_00ba52d0;
  P11_00ba52d0 = RoundMul(P59_PosZ);
  P63_Near = -1;
  for (int32_t i = 0; i < RecLimit(P51_TrafficN); i++, r += TREC_SIZE) {
    if (r[TREC_STATE] != 0) {
      int32_t d = Abs(rd32(r, TREC_CELL_X) - px) + Abs(rd32(r, TREC_CELL_Z) - P11_00ba52d0);
      if (d < best) { P63_Near = i; best = d; }
    }
  }
  return P63_Near;
}

/* P63_CanEnter — Game.exe 0048f1c6, cdecl.  May traffic car `rec` enter the next node?  Always 1 when the current node is not a junction
   (slot byte 3).  Otherwise looks at the neighbour node in the car's direction: blocked (0) by an
   unlisted-distance car (id | 0x80), or by a car closer than 15000 whose TREC_F34 is 0, or
   closer than 9000 unless TREC_F34 is -1.  Finally the P59_TrafficCheck(rec, 1) test must
   pass.  Slot byte 3 is set by P14_Fn0051BED5 for nodes with exactly two connections (plain road,
   no junction). */
int32_t P63_CanEnter(const uint8_t *rec) {
  int32_t node = rd32(rec, TREC_ROAD_NODE);
  const uint8_t *tab = (const uint8_t *)P14_00c1ed80 + (uint32_t)node * 0x2c;
  if (tab[3] != 0) return 1;
  int32_t dir = rd32(rec, TREC_ROAD_DIR);
  int16_t next = P11_00c1ed8a[node * 0x16 + dir * 4];
  if (next != -1) {
    int32_t cnt = P63_NearOnNode(rec[TREC_CAR], next, (dir + 2) & 3, node);
    for (int32_t i = 0; i < cnt; i++) {
      if (P63_Dist[i] < 15000) {
        uint32_t id = (uint32_t)P63_Ids[i];
        if (id & 0x80) return 0;
        int32_t st = rd32((const uint8_t *)TrafficRecs, id * TREC_SIZE + TREC_F34);   /* 0x01144414 */
        if (st != -1) {
          if (st == 0) return 0;
          if (P63_Dist[i] < 9000) return 0;
        }
      }
    }
  }
  return P59_TrafficCheck(rec, 1) == 0 ? 1 : 0;
}

/* P63_CarSpeed — Game.exe 004901c0, cdecl.  Target speed of traffic car `rec` (stored in TREC_TGT_SPEED and returned).
   Not slowing (TREC_FLAGS13 bit 3 clear): 0 when the road distance is below 0x28a or
   0049521e finds an obstacle; road distance / 0x18 (at least 5) while below the class
   threshold P63_LimB, else the class cap P63_LimA.  Slowing: decays by 0x10 per call to 0. */
int32_t P63_CarSpeed(uint8_t *rec) {
  if ((rec[TREC_FLAGS13] & 8) == 0) {
    int32_t v = rd32(rec, TREC_ROAD_DIST);
    if (v < 0x28a) { wr32(rec, TREC_TGT_SPEED, 0); return 0; }
    if (P63_Fn49521E(rec, 1, 0) == -1) {
      int32_t cls = rec[TREC_CLASS] & 3;
      if (rd32(rec, TREC_ROAD_DIST) < P63_LimB[cls]) {
        wr32(rec, TREC_TGT_SPEED, rd32(rec, TREC_ROAD_DIST) / 0x18);
        if (rd32(rec, TREC_TGT_SPEED) < 5) wr32(rec, TREC_TGT_SPEED, 5);
      } else {
        wr32(rec, TREC_TGT_SPEED, P63_LimA[cls]);
      }
      return rd32(rec, TREC_TGT_SPEED);
    }
    wr32(rec, TREC_TGT_SPEED, 0);
    return 0;
  }
  wr32(rec, TREC_TGT_SPEED, rd32(rec, TREC_TGT_SPEED) - 0x10);
  if (rd32(rec, TREC_TGT_SPEED) < 0) wr32(rec, TREC_TGT_SPEED, 0);
  return rd32(rec, TREC_TGT_SPEED);
}

/* 004966fd: x87 — fild + fmul/fadd в расширенной точности, сравнение с float */
/* P63_InPlanes — Game.exe 004966fd, cdecl.  1 if the car/object `obj` (CAR_POS_X/Z) lies on the inner side of all 4 vertical planes p
   (a, ?, c, d per plane: a*x + c*z <= d); 0 otherwise.  Extended precision as x87. */
int32_t P63_InPlanes(const uint8_t *obj, const float *p) {
  long double x = (long double)rd32(obj, CAR_POS_X), z = (long double)rd32(obj, CAR_POS_Z);
  for (int i = 0; i < 4; i++) {
    long double lhs = z * (long double)p[i * 4 + 2] + x * (long double)p[i * 4];
    if (!(lhs <= (long double)p[i * 4 + 3])) return 0;
  }
  return 1;
}

/* P63_SphereHits — Game.exe 00426b34, cdecl.  Indices of the spheres in table 011f40e0 (0x24-byte entries: float centre, int32 radius at
   +0xc) that the sphere (p, radius obj+0xc) intersects.  Out: P63_Hits (first 256),
   P63_SphN = total count. */
void P63_SphereHits(const float *p, const uint8_t *obj) {
  const uint8_t *s = (const uint8_t *)G2_011F40E0;
  float rad = rdf(obj, 0xc);
  P63_SphN = 0;
  for (int32_t i = 0; i < G2_011F43B0; i++, s += 0x24) {
    float r = (float)((long double)rd32(s, 0xc) + (long double)rad);
    long double dx = (long double)p[0] - (long double)rdf(s, 0);
    long double dy = (long double)p[1] - (long double)rdf(s, 4);
    long double dz = (long double)p[2] - (long double)rdf(s, 8);
    if (dz * dz + dy * dy + dx * dx < (long double)r * (long double)r) {
      if (P63_SphN < 0x100) P63_Hits[P63_SphN] = i;
      P63_SphN++;
    }
  }
}

/* 0049ef12: сплайн Катмулла–Рома; float-переменные оригинала сохраняются как float, выражения — в расширенной точности */
/* P63_CatmullRom — Game.exe 0049ef12, cdecl.  Catmull-Rom spline point at t between p1 and p2: weights a..d for p0..p3 from t, t^2, t^3
   (constants 0.5, 1.5, 2.5, 2.0 from .data), out = sum of weighted points.  Float temporaries
   are kept as float, expressions in extended precision, as in the original. */
void P63_CatmullRom(const float *t, float *out, const float *p0, const float *p1, const float *p2, const float *p3) {
  long double h = P51_Half;
  float f1 = *t;
  float f2 = (float)((long double)f1 * f1);
  float f3 = (float)((long double)f2 * f1);
  float a = (float)(((long double)f2 - h * f3) - h * f1);                                  /* вес p0 */
  float b = (float)((long double)P56_C546120 * f3 - (long double)P56_C54611C * f2 + P59_One);   /* вес p1 */
  float c = (float)(h * f1 + ((long double)P19_DivC * f2 - (long double)P56_C546120 * f3));     /* вес p2 */
  float d = (float)(h * f3 - h * f2);                                                      /* вес p3 */
  for (int i = 0; i < 3; i++)
    out[i] = (float)((long double)d * p3[i] + (long double)c * p2[i] + (long double)b * p1[i] + (long double)a * p0[i]);
}

/* 0049ed20: кубическая кривая по трём узлам; арифметика целых — int32 с переполнением, дальше x87 */
/* P63_Hermite — Game.exe 0049ed20, cdecl.  Cubic curve through three keys: a, c, d are made relative to b (int32 wrap-around kept);
   evaluates at u = t - b a cubic with slope from the key spacing.  TODO(RE): unsure of the
   exact curve family (looks like a monotone cubic used for camera/replay interpolation). */
void P63_Hermite(int32_t t, float *out, int32_t a, int32_t b, int32_t c, int32_t d) {
  a = (int32_t)((uint32_t)a - (uint32_t)b);
  c = (int32_t)((uint32_t)c - (uint32_t)b);
  d = (int32_t)((uint32_t)d - (uint32_t)b);
  if (c == d) d = (int32_t)((uint32_t)d + (uint32_t)c);
  if (a == 0) a = -c;
  long double two = P19_DivC, three = P8_00546034;
  float k = (float)(two * (long double)(int32_t)((uint32_t)(c + d) - (uint32_t)a) /
                    (long double)(int32_t)((uint32_t)d * (uint32_t)(c - a)));
  float u = (float)(t - b);
  int32_t c3 = (int32_t)((uint32_t)c * (uint32_t)c * (uint32_t)c), c2 = (int32_t)((uint32_t)c * (uint32_t)c);
  long double ca = two / (long double)(c - a);
  *out = (float)((((long double)k * c - two) / (long double)c3) * u * u * u +
                 ((three - (long double)c * (ca + k)) / (long double)c2) * u * u + ca * u);
}
