#include "ported79.h"
#include <math.h>
#include <string.h>
#include "p79_data.h"

#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P79_ModelTab")
#undef P79_ModelTab
#pragma push_macro("P79_ModelTab") /*gvi*/
#undef P79_ModelTab /*gvi*/
p79_tab_t P79_ModelTab;
#pragma pop_macro("P79_ModelTab") /*gvi*/
#pragma pop_macro("P79_ModelTab")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P79_Total")
#undef P79_Total
#pragma push_macro("P79_Total") /*gvi*/
#undef P79_Total /*gvi*/
int32_t P79_Total;
#pragma pop_macro("P79_Total") /*gvi*/
#pragma pop_macro("P79_Total")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P79_Outside")
#undef P79_Outside
#pragma push_macro("P79_Outside") /*gvi*/
#undef P79_Outside /*gvi*/
int32_t P79_Outside;
#pragma pop_macro("P79_Outside") /*gvi*/
#pragma pop_macro("P79_Outside")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P79_SumTotal")
#undef P79_SumTotal
#pragma push_macro("P79_SumTotal") /*gvi*/
#undef P79_SumTotal /*gvi*/
int32_t P79_SumTotal;
#pragma pop_macro("P79_SumTotal") /*gvi*/
#pragma pop_macro("P79_SumTotal")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P79_SumOut")
#undef P79_SumOut
#pragma push_macro("P79_SumOut") /*gvi*/
#undef P79_SumOut /*gvi*/
int32_t P79_SumOut;
#pragma pop_macro("P79_SumOut") /*gvi*/
#pragma pop_macro("P79_SumOut")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P79_NumAll")
#undef P79_NumAll
#pragma push_macro("P79_NumAll") /*gvi*/
#undef P79_NumAll /*gvi*/
int32_t P79_NumAll;
#pragma pop_macro("P79_NumAll") /*gvi*/
#pragma pop_macro("P79_NumAll")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P79_NumMixed")
#undef P79_NumMixed
#pragma push_macro("P79_NumMixed") /*gvi*/
#undef P79_NumMixed /*gvi*/
int32_t P79_NumMixed;
#pragma pop_macro("P79_NumMixed") /*gvi*/
#pragma pop_macro("P79_NumMixed")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P79_NumNone")
#undef P79_NumNone
#pragma push_macro("P79_NumNone") /*gvi*/
#undef P79_NumNone /*gvi*/
int32_t P79_NumNone;
#pragma pop_macro("P79_NumNone") /*gvi*/
#pragma pop_macro("P79_NumNone")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P79_ClsHi")
#undef P79_ClsHi
#pragma push_macro("P79_ClsHi") /*gvi*/
#undef P79_ClsHi /*gvi*/
float P79_ClsHi;
#pragma pop_macro("P79_ClsHi") /*gvi*/
#pragma pop_macro("P79_ClsHi")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P79_ClsLo")
#undef P79_ClsLo
#pragma push_macro("P79_ClsLo") /*gvi*/
#undef P79_ClsLo /*gvi*/
float P79_ClsLo;
#pragma pop_macro("P79_ClsLo") /*gvi*/
#pragma pop_macro("P79_ClsLo")
#endif

/* Значения из .data Game.exe: 0x005460a0 = 1.001f, 0x005460a4 = 0.998f; таблицы шагов записей 0x550acc (112 int) */
void P79_InitConsts(void) {
#ifndef RE_HOOK_BUILD
  P79_ClsHi = 1.0010000467300415f; P79_ClsLo = 0.9980000257492065f;
  for (int i = 0; i < 112; i++) G2_TABLE_00550ACC[i] = P79_Steps[i];
#endif
}

static uint32_t g_pool = 0x400000;
void P79_PoolReset(void) { g_pool = 0x400000; }
void *P79_EventAlloc(int32_t size) {
#ifdef RE_HOOK_BUILD
  return DebugMalloc(size, "D:\\Driver\\Game\\map.c", 0x3ed);
#else
  if (size < 0 || g_pool + (uint32_t)size > 0x500000) return NULL;
  void *p = (uint8_t *)D_00c98ed0 + g_pool;
  g_pool += ((uint32_t)size + 15u) & ~15u;
  return p;
#endif
}
void P79_EventFree(void *p) {
#ifdef RE_HOOK_BUILD
  DebugFree(p);
#else
  (void)p;
#endif
}

static uint32_t rd32(const void *p, int o) { uint32_t v; memcpy(&v, (const uint8_t *)p + o, 4); return v; }
static void wr32(void *p, int o, uint32_t v) { memcpy((uint8_t *)p + o, &v, 4); }
static uint16_t rd16(const void *p, int o) { uint16_t v; memcpy(&v, (const uint8_t *)p + o, 2); return v; }
static void wr16(void *p, int o, uint16_t v) { memcpy((uint8_t *)p + o, &v, 2); }
static void addf(void *p, int o, uint32_t d) { wr32(p, o, rd32(p, o) + d); }
static int32_t step1(uint8_t t) { return G2_TABLE_00550ACC[t]; }       /* 00550acc + t*4 */

/* 0042754a: адреса всех записей модели → out[i] (ссылки) */
void P79_ModelList(void *m, uint32_t *out) {
  uint8_t *rec = (uint8_t *)P79_PTR(rd32(m, 0x2c));
  for (int i = 0; i < (int)rd16(m, 0x16); i++) {
    out[i] = P79_OFF(rec);
    rec += step1(*rec);
  }
}

/* 00427757 */
void P79_Relocate(void *m) {
  uint16_t fl = rd16(m, 2);
  if (fl & 0x8000) return;
  uint32_t me = P79_OFF(m);
  int32_t parent = (int32_t)rd32(m, 4);
  if (parent == -1) {
    wr16(m, 2, fl ^ 0x8000);
    addf(m, 0x1c, me); addf(m, 0x20, me); addf(m, 0x24, me); addf(m, 0x28, me); addf(m, 0x2c, me);
    if (rd32(m, 0x34) != 0) addf(m, 0x34, me);
    if (rd32(m, 0x30) != 0) {
      addf(m, 0x30, me);
      uint32_t s = rd32(m, 0x30);
      void *sp = P79_PTR(s);
      addf(sp, 0x10, s); addf(sp, 0x14, s); addf(sp, 0x18, s); addf(sp, 0xc, s);
      P79_ModelList(m, (uint32_t *)P79_PTR(rd32(sp, 0xc)));
    }
  } else {
    void *par = P79_PTR(P79_ModelTab[parent]);
    wr16(m, 2, fl ^ 0x8000);
    addf(m, 0x1c, me); addf(m, 0x2c, me); addf(m, 0x28, me);
    if (!(rd16(par, 2) & 0x8000)) {
      P79_Relocate(par);
      wr32(m, 0x20, rd32(par, 0x20)); wr32(m, 0x24, rd32(par, 0x24)); wr32(m, 0x34, rd32(par, 0x34));
      P79_Unrelocate(par);
    } else {
      wr32(m, 0x20, rd32(par, 0x20)); wr32(m, 0x24, rd32(par, 0x24)); wr32(m, 0x34, rd32(par, 0x34));
    }
  }
}

/* 004275ae */
void P79_Unrelocate(void *m) {
  uint16_t fl = rd16(m, 2);
  if (!(fl & 0x8000)) return;
  uint32_t me = P79_OFF(m);
  if ((int32_t)rd32(m, 4) == -1) {
    wr16(m, 2, fl ^ 0x8000);
    addf(m, 0x1c, -me); addf(m, 0x20, -me); addf(m, 0x24, -me); addf(m, 0x28, -me); addf(m, 0x2c, -me);
    if (rd32(m, 0x34) != 0) addf(m, 0x34, -me);
    if (rd32(m, 0x30) != 0) {
      uint32_t s = rd32(m, 0x30);
      void *sp = P79_PTR(s);
      addf(sp, 0x10, -s); addf(sp, 0x14, -s); addf(sp, 0x18, -s);      /* +0xc остаётся (как в оригинале) */
      addf(m, 0x30, -me);
    }
  } else {
    wr16(m, 2, fl ^ 0x8000);
    addf(m, 0x1c, -me); addf(m, 0x2c, -me); addf(m, 0x28, -me);
    if (rd32(m, 0x30) != 0) {
      uint32_t s = rd32(m, 0x30);
      void *sp = P79_PTR(s);
      addf(sp, 0x10, -s); addf(sp, 0x14, -s); addf(sp, 0x18, -s); addf(sp, 0xc, -s);
      addf(m, 0x30, -me);
    }
  }
}

/* 0042793f: наибольшая длина вершины (x87: произведения во long double, Y² усечено до float) */
void P79_Radius(void *m, int32_t mode) {
  float best = 0.0f;
  const uint8_t *v = (const uint8_t *)P79_PTR(rd32(m, 0x20));
  for (int i = 0; i < (int)rd16(m, 0x14); i++, v += 16) {
    float x, y, z, y2; memcpy(&x, v, 4); memcpy(&y, v + 4, 4); memcpy(&z, v + 8, 4);
    y2 = mode == 0 ? (float)((long double)y * y) : 0.0f;
    double s = (double)((long double)x * x + y2 + (long double)z * z);
    float r = (float)sqrt(s);
    if (best < r) best = r;
  }
  if (mode == 0) memcpy((uint8_t *)m + 0xc, &best, 4); else memcpy((uint8_t *)m + 0x10, &best, 4);
}

/* 0047560b: 1/2 — ось X (−/+), 5/6 — Y, 4/3 — Z; 0 — вершина не лежит на оси */
int32_t P79_VertClass(const float *v) {
  P79_Total++;
  static const int8_t neg[3] = {1, 5, 4}, pos[3] = {2, 6, 3};
  for (int i = 0; i < 3; i++) {
    if (0.0f <= v[i]) { if (P79_ClsLo < v[i] && v[i] < P79_ClsHi) return pos[i]; }
    else { float a = fabsf(v[i]); if (P79_ClsLo < a && a < P79_ClsHi) return neg[i]; }
  }
  P79_Outside++;
  P79_Total--;
  return 0;
}

/* 004757d2 */
void P79_MarkRecords(void *m) {
  const uint8_t *vert = (const uint8_t *)P79_PTR(rd32(m, 0x24));
  uint8_t *rec = (uint8_t *)P79_PTR(rd32(m, 0x2c));
  P79_Outside = 0; P79_Total = 0;
  for (int i = 0; i < (int)rd16(m, 0x16); i++) {
    uint8_t t = *rec;
    rec[1] = (uint8_t)P79_VertClass((const float *)vert);
    rec += step1(t);
    vert += 16;
  }
  uint16_t n = rd16(m, 0x16);
  if ((int32_t)n == P79_Total) { wr16(m, 2, rd16(m, 2) | 0x30); P79_NumAll++; }
  else if ((int32_t)n == P79_Outside) { P79_NumNone++; }
  else { wr16(m, 2, rd16(m, 2) | 0x10); P79_NumMixed++; }
  P79_SumTotal += P79_Total;
  P79_SumOut += P79_Outside;
}

/* 00475906: для каждой записи ищет первую такую же вершину; свою — помечает 8, чужую — считает */
int32_t P79_FindSameVerts(void *m) {
  int32_t cnt = 0;
  uint8_t *rec = (uint8_t *)P79_PTR(rd32(m, 0x2c));
  const float *verts = (const float *)P79_PTR(rd32(m, 0x24));
  int n = rd16(m, 0x16);
  for (int i = 0; i < n; i++) {
    const float *a = verts + i * 4, *b = verts;
    for (int j = 0; j < n; j++, b += 4) {
      if (b[0] == a[0] && b[1] == a[1] && b[2] == a[2] && b[3] == a[3]) {
        wr32(rec, 4, (uint32_t)j);
        if (j == i) rec[1] |= 8; else cnt++;
        break;
      }
    }
    rec += step1(*rec);
  }
  return cnt;
}

/* 00475a3d: src — модель с диска (смещения от начала src), dst — модель в памяти (смещения от начала dst).
   В оригинале src правился на месте (+= src); здесь он только читается. */
int32_t P79_Convert(void *srcv, void *dstv) {
  const uint8_t *src = (const uint8_t *)srcv; uint8_t *dst = (uint8_t *)dstv;
  const float one = 1.0f;
  int32_t cur = 0x38;
  memcpy(dst, src, 0x38);
  int32_t parent = (int32_t)rd32(src, 4);
  uint32_t o34 = rd32(src, 0x34);
  if (parent == -1) {
    int n = rd16(src, 0x14);
    const uint8_t *s = src + rd32(src, 0x20); uint8_t *d = dst + 0x38;
    for (int i = 0; i < n; i++, s += 12, d += 16) { memcpy(d, s, 12); memcpy(d + 12, &one, 4); }
    wr32(dst, 0x20, 0x38);
    cur = n * 16 + 0x38;
    int nr = rd16(src, 0x16);
    if (nr != 0) memcpy(dst + cur, src + rd32(src, 0x24), (size_t)nr << 4);
    wr32(dst, 0x24, (uint32_t)cur);
    cur += nr * 16;
  }
  int nn = rd16(src, 0x18);
  if (nn != 0) {
    const uint8_t *s = src + rd32(src, 0x28); uint8_t *d = dst + cur;
    for (int i = 0; i < nn; i++, s += 12, d += 16) { memcpy(d, s, 12); memcpy(d + 12, &one, 4); }
  }
  wr32(dst, 0x28, (uint32_t)cur);
  cur += nn * 16;
  int nb = rd16(src, 0x1a);
  if (nb != 0) memcpy(dst + cur, src + rd32(src, 0x1c), (size_t)nb);
  wr32(dst, 0x1c, (uint32_t)cur);
  cur += (nb + 3) & ~3;
  if (parent == -1) {
    if (o34 == 0) wr32(dst, 0x34, 0);
    else {
      const uint8_t *t = src + o34;
      int32_t k = (int32_t)rd32(t, 0);
      memcpy(dst + cur, t, (size_t)(k * 0x14 + 4));
      wr32(dst, 0x34, (uint32_t)cur);
      cur += 4 + k * 0x14;
    }
  }
  const uint8_t *rs = src + rd32(src, 0x2c);
  wr32(dst, 0x2c, (uint32_t)cur);
  int nrec = rd16(src, 0x16);
  for (int i = 0; i < nrec; i++) {
    uint8_t t = *rs;
    uint8_t *d = dst + cur;
    if (t < 0x38 && !(t & 8)) {
      int k = (t & 7) | ((t & 0x10) ? 8 : 0);
      d[0] = t;
      for (int q = 0; q < P79_OpIdx[k][1]; q++) {
        const p79_op_t *op = &P79_Ops[P79_OpIdx[k][0] + q];
        if (op->op == 'U') wr32(d, op->dst, rd16(rs, op->src));
        else if (op->op == 'F') { float f = (float)rs[op->src]; memcpy(d + op->dst, &f, 4); }
        else d[op->dst] = rs[op->src];
      }
    }
    cur += G2_TABLE_00550ACC[t];
    rs += G2_TABLE_00550ACC[56 + t];
  }
  return cur;
}
