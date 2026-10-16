#include "ported63.h"
#include <math.h>
#include <string.h>

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

static int32_t rd32(const uint8_t *p, uint32_t o) { int32_t v; memcpy(&v, p + o, 4); return v; }
static void    wr32(uint8_t *p, uint32_t o, int32_t v) { memcpy(p + o, &v, 4); }
static float   rdf(const uint8_t *p, uint32_t o) { float v; memcpy(&v, p + o, 4); return v; }
/* fistp: к ближайшему чётному; произведение float*float считается в расширенной точности, как в x87 */
static int32_t RoundMul(int32_t v) { return (int32_t)lrintl((long double)(float)v * (long double)P63_Scale); }
/* В native таблица трафика ровно 0x40 записей; оригинал при «режиме 0x41» читает ещё одну запись за ней. */
static int32_t RecLimit(int32_t n) {
#ifndef RE_HOOK_BUILD
  if (n > 0x40) n = 0x40;
#endif
  return n;
}

void P63_InitConsts(void) {
#ifndef RE_HOOK_BUILD
  static const int32_t a[4] = { 130, 162, 194, 226 }, b[4] = { 3500, 3600, 3700, 3800 };
  memcpy(P63_LimA, a, sizeof a); memcpy(P63_LimB, b, sizeof b);
  P8_00546034 = 3.0f;   /* float-константа 3.0 из .data */
#endif
}

/* 0048ea2c */
int32_t P63_NearOnNode(uint32_t self, int32_t node, int32_t dir, int32_t alt) {
  const uint8_t *r = (const uint8_t *)TrafficRecs;
  int32_t n = 0;
  for (int32_t i = 0; i < RecLimit(P51_TrafficN); i++, r += 0x54) {
    if (r[8] != 0 && r[0] != self) {
      if (rd32(r, 0x28) == node) {
        if (rd32(r, 0x24) == dir || rd32(r, 0x30) == dir) {
          P63_Dist[n] = rd32(r, 0x18);
          P63_Ids[n] = r[0];
          n++;
        }
      } else if (r[3] != 0 && rd32(r, 0x20) == alt) {
        P63_Dist[n] = -1;
        P63_Ids[n] = r[0] | 0x80;
        n++;
      }
    }
  }
  return n;
}

/* 0048f3b4 */
int32_t P63_CountByNode(int32_t a, int32_t b, int32_t c, int32_t d) {
  const uint8_t *r = (const uint8_t *)TrafficRecs;
  P63_Cnt3 = 0; P63_Cnt2 = 0; P63_Cnt1 = 0; P63_Cnt0 = 0;
  for (int32_t i = 0; i < RecLimit(P51_TrafficN); i++, r += 0x54) {
    if (r[1] != 0) {
      int32_t node = rd32(r, 0x28);
      if (node == a) P63_Cnt0++;
      else if (node == b) P63_Cnt1++;
      else if (node == c) P63_Cnt2++;
      else if (node == d) P63_Cnt3++;
    }
  }
  return P63_Cnt0 + P63_Cnt1 + P63_Cnt2 + P63_Cnt3;
}

static int32_t Abs(int32_t v) { return v < 0 ? -v : v; }

/* 0048f4ad */
void P63_NearestAdd(int32_t x, int32_t z) {
  const uint8_t *r = (const uint8_t *)TrafficRecs;
  P11_00ba52d0 = RoundMul(x + 0x2ee);
  int32_t px = P11_00ba52d0;
  P11_00ba52d0 = RoundMul(z - 0x2ee);
  int32_t n = (P58_SB87EB0 == 0 && G6_00B87EAC == 0) ? P51_TrafficN : 0x41;
  P63_Near = 0x400;
  for (int32_t i = 0; i < RecLimit(n); i++, r += 0x54) {
    if (r[1] == 1 || r[2] != 0) {
      int32_t d = Abs(rd32(r, 0x48) - px) + Abs(rd32(r, 0x4c) - P11_00ba52d0);
      if (d < P63_Near) P63_Near = d;
    }
  }
}

/* 0048f5d8 */
int32_t P63_NearestRec(void) {
  const uint8_t *r = (const uint8_t *)TrafficRecs;
  int32_t best = 10000;
  P11_00ba52d0 = RoundMul(P59_PosX);
  int32_t px = P11_00ba52d0;
  P11_00ba52d0 = RoundMul(P59_PosZ);
  P63_Near = -1;
  for (int32_t i = 0; i < RecLimit(P51_TrafficN); i++, r += 0x54) {
    if (r[1] != 0) {
      int32_t d = Abs(rd32(r, 0x48) - px) + Abs(rd32(r, 0x4c) - P11_00ba52d0);
      if (d < best) { P63_Near = i; best = d; }
    }
  }
  return P63_Near;
}

/* 0048f1c6 */
int32_t P63_CanEnter(const uint8_t *rec) {
  int32_t node = rd32(rec, 0x20);
  const uint8_t *tab = (const uint8_t *)P14_00c1ed80 + (uint32_t)node * 0x2c;
  if (tab[3] != 0) return 1;
  int32_t dir = rd32(rec, 0x24);
  int16_t next = P11_00c1ed8a[node * 0x16 + dir * 4];
  if (next != -1) {
    int32_t cnt = P63_NearOnNode(rec[0], next, (dir + 2) & 3, node);
    for (int32_t i = 0; i < cnt; i++) {
      if (P63_Dist[i] < 15000) {
        uint32_t id = (uint32_t)P63_Ids[i];
        if (id & 0x80) return 0;
        int32_t st = rd32((const uint8_t *)TrafficRecs, id * 0x54 + 0x34);   /* 0x01144414 */
        if (st != -1) {
          if (st == 0) return 0;
          if (P63_Dist[i] < 9000) return 0;
        }
      }
    }
  }
  return P59_TrafficCheck(rec, 1) == 0 ? 1 : 0;
}

/* 004901c0 */
int32_t P63_CarSpeed(uint8_t *rec) {
  if ((rec[0x13] & 8) == 0) {
    int32_t v = rd32(rec, 0x18);
    if (v < 0x28a) { wr32(rec, 0x3c, 0); return 0; }
    if (P63_Fn49521E(rec, 1, 0) == -1) {
      int32_t cls = rec[9] & 3;
      if (rd32(rec, 0x18) < P63_LimB[cls]) {
        wr32(rec, 0x3c, rd32(rec, 0x18) / 0x18);
        if (rd32(rec, 0x3c) < 5) wr32(rec, 0x3c, 5);
      } else {
        wr32(rec, 0x3c, P63_LimA[cls]);
      }
      return rd32(rec, 0x3c);
    }
    wr32(rec, 0x3c, 0);
    return 0;
  }
  wr32(rec, 0x3c, rd32(rec, 0x3c) - 0x10);
  if (rd32(rec, 0x3c) < 0) wr32(rec, 0x3c, 0);
  return rd32(rec, 0x3c);
}

/* 004966fd: x87 — fild + fmul/fadd в расширенной точности, сравнение с float */
int32_t P63_InPlanes(const uint8_t *obj, const float *p) {
  long double x = (long double)rd32(obj, 200), z = (long double)rd32(obj, 0xd0);
  for (int i = 0; i < 4; i++) {
    long double lhs = z * (long double)p[i * 4 + 2] + x * (long double)p[i * 4];
    if (!(lhs <= (long double)p[i * 4 + 3])) return 0;
  }
  return 1;
}

/* 00426b34 */
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
