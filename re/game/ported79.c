/* Map models: link relocation, record list, bounding radius, axis classification of polygon
   vectors, duplicate search and disk -> memory conversion.  Header layout: MDL_* in names_g3.h. */
#include "ported79.h"
#include <math.h>
#include <string.h>
#include "p79_data.h"
#include "names_g3.h"

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
/* P79_InitConsts — Native: the .data constants 1.001f / 0.998f (axis test window) and the 112-entry record size
   table 00550acc. */
void P79_InitConsts(void) {
#ifndef RE_HOOK_BUILD
  P79_ClsHi = 1.0010000467300415f; P79_ClsLo = 0.9980000257492065f;
  for (int i = 0; i < 112; i++) G2_TABLE_00550ACC[i] = P79_Steps[i];
#endif
}

static uint32_t g_pool = 0x400000;
/* P79_PoolReset — Native: reset the event-model pool (1 MiB after the 4 MiB map arena). */
void P79_PoolReset(void) { g_pool = 0x400000; }
/* P79_EventAlloc — Allocate `size` bytes for an event model.  Hook: DebugMalloc.  Native: bump allocation from
   the pool, 16-byte aligned, so links stay arena offsets; NULL when the pool is exhausted. */
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
/* P79_EventFree — Free an event model (native: no-op, the pool is reset as a whole). */
void P79_EventFree(void *p) {
#ifdef RE_HOOK_BUILD
  DebugFree(p);
#else
  (void)p;
#endif
}

/* rd32 — Unaligned uint32 read at p + o. */
static uint32_t rd32(const void *p, int o) { uint32_t v; memcpy(&v, (const uint8_t *)p + o, 4); return v; }
/* wr32 — Unaligned uint32 write at p + o. */
static void wr32(void *p, int o, uint32_t v) { memcpy((uint8_t *)p + o, &v, 4); }
/* rd16 — Unaligned uint16 read at p + o. */
static uint16_t rd16(const void *p, int o) { uint16_t v; memcpy(&v, (const uint8_t *)p + o, 2); return v; }
/* wr16 — Unaligned uint16 write at p + o. */
static void wr16(void *p, int o, uint16_t v) { memcpy((uint8_t *)p + o, &v, 2); }
/* addf — Add d to the uint32 at p + o (relocate a link). */
static void addf(void *p, int o, uint32_t d) { wr32(p, o, rd32(p, o) + d); }
/* step1 — Size in bytes of a polygon record of type t (table 00550acc). */
static int32_t step1(uint8_t t) { return G2_TABLE_00550ACC[t]; }       /* 00550acc + t*4 */

/* 0042754a: адреса всех записей модели → out[i] (ссылки) */
/* P79_ModelList — Game.exe 0042754a, cdecl.  Write the link of every polygon record of model m to out[0..MDL_NRECS-1]. */
void P79_ModelList(void *m, uint32_t *out) {
  uint8_t *rec = (uint8_t *)P79_PTR(rd32(m, MDL_RECS));
  for (int i = 0; i < (int)rd16(m, MDL_NRECS); i++) {
    out[i] = P79_OFF(rec);
    rec += step1(*rec);
  }
}

/* P79_Relocate — Game.exe 00427757, cdecl.  Make model m's links absolute (add the model's own link) and set MDL_LINKED; no-op when
   already linked.  Own-geometry models also relocate table +0x34 and the sub-block (its links
   are relative to itself) and rebuild the record list there.  Models with a parent copy the
   parent's MDL_VERTS / MDL_RECVEC / MDL_L34 links (relocating the parent temporarily if needed). */
void P79_Relocate(void *m) {
  uint16_t fl = rd16(m, MDL_FLAGS);
  if (fl & MDL_LINKED) return;
  uint32_t me = P79_OFF(m);
  int32_t parent = (int32_t)rd32(m, MDL_PARENT);
  if (parent == -1) {
    wr16(m, MDL_FLAGS, fl ^ MDL_LINKED);
    addf(m, MDL_L1C, me); addf(m, MDL_VERTS, me); addf(m, MDL_RECVEC, me); addf(m, MDL_L28, me); addf(m, MDL_RECS, me);
    if (rd32(m, MDL_L34) != 0) addf(m, MDL_L34, me);
    if (rd32(m, MDL_SUB) != 0) {
      addf(m, MDL_SUB, me);
      uint32_t s = rd32(m, MDL_SUB);
      void *sp = P79_PTR(s);
      addf(sp, 0x10, s); addf(sp, 0x14, s); addf(sp, 0x18, s); addf(sp, 0xc, s);
      P79_ModelList(m, (uint32_t *)P79_PTR(rd32(sp, 0xc)));
    }
  } else {
    void *par = P79_PTR(P79_ModelTab[parent]);
    wr16(m, MDL_FLAGS, fl ^ MDL_LINKED);
    addf(m, MDL_L1C, me); addf(m, MDL_RECS, me); addf(m, MDL_L28, me);
    if (!(rd16(par, MDL_FLAGS) & MDL_LINKED)) {
      P79_Relocate(par);
      wr32(m, MDL_VERTS, rd32(par, MDL_VERTS)); wr32(m, MDL_RECVEC, rd32(par, MDL_RECVEC)); wr32(m, MDL_L34, rd32(par, MDL_L34));
      P79_Unrelocate(par);
    } else {
      wr32(m, MDL_VERTS, rd32(par, MDL_VERTS)); wr32(m, MDL_RECVEC, rd32(par, MDL_RECVEC)); wr32(m, MDL_L34, rd32(par, MDL_L34));
    }
  }
}

/* P79_Unrelocate — Game.exe 004275ae, cdecl.  Inverse of P79_Relocate: make links relative again and clear MDL_LINKED.  For own-geometry
   models the sub-block's +0xc link is left absolute (as in the original). */
void P79_Unrelocate(void *m) {
  uint16_t fl = rd16(m, MDL_FLAGS);
  if (!(fl & MDL_LINKED)) return;
  uint32_t me = P79_OFF(m);
  if ((int32_t)rd32(m, MDL_PARENT) == -1) {
    wr16(m, MDL_FLAGS, fl ^ MDL_LINKED);
    addf(m, MDL_L1C, -me); addf(m, MDL_VERTS, -me); addf(m, MDL_RECVEC, -me); addf(m, MDL_L28, -me); addf(m, MDL_RECS, -me);
    if (rd32(m, MDL_L34) != 0) addf(m, MDL_L34, -me);
    if (rd32(m, MDL_SUB) != 0) {
      uint32_t s = rd32(m, MDL_SUB);
      void *sp = P79_PTR(s);
      addf(sp, 0x10, -s); addf(sp, 0x14, -s); addf(sp, 0x18, -s);      /* +0xc остаётся (как в оригинале) */
      addf(m, MDL_SUB, -me);
    }
  } else {
    wr16(m, MDL_FLAGS, fl ^ MDL_LINKED);
    addf(m, MDL_L1C, -me); addf(m, MDL_RECS, -me); addf(m, MDL_L28, -me);
    if (rd32(m, MDL_SUB) != 0) {
      uint32_t s = rd32(m, MDL_SUB);
      void *sp = P79_PTR(s);
      addf(sp, 0x10, -s); addf(sp, 0x14, -s); addf(sp, 0x18, -s); addf(sp, 0xc, -s);
      addf(m, MDL_SUB, -me);
    }
  }
}

/* 0042793f: наибольшая длина вершины (x87: произведения во long double, Y² усечено до float) */
/* P79_Radius — Game.exe 0042793f, cdecl.  Largest vertex distance of model m: mode 0 with Y -> MDL_RADIUS, mode 1 ignoring Y ->
   MDL_RADIUS_XZ.  Y^2 is rounded to float before the sum (x87 order kept). */
void P79_Radius(void *m, int32_t mode) {
  float best = 0.0f;
  const uint8_t *v = (const uint8_t *)P79_PTR(rd32(m, MDL_VERTS));
  for (int i = 0; i < (int)rd16(m, MDL_NVERTS); i++, v += 16) {
    float x, y, z, y2; memcpy(&x, v, 4); memcpy(&y, v + 4, 4); memcpy(&z, v + 8, 4);
    y2 = mode == 0 ? (float)((long double)y * y) : 0.0f;
    double s = (double)((long double)x * x + y2 + (long double)z * z);
    float r = (float)sqrt(s);
    if (best < r) best = r;
  }
  if (mode == 0) memcpy((uint8_t *)m + MDL_RADIUS, &best, 4); else memcpy((uint8_t *)m + MDL_RADIUS_XZ, &best, 4);
}

/* 0047560b: 1/2 — ось X (−/+), 5/6 — Y, 4/3 — Z; 0 — вершина не лежит на оси */
/* P79_VertClass — Game.exe 0047560b, cdecl.  Classify a unit vector: 1/2 = -X/+X, 5/6 = -Y/+Y, 4/3 = -Z/+Z when that component is within
   (0.998, 1.001) in magnitude (first axis wins); 0 otherwise.  Counts in P79_Total / P79_Outside. */
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

/* P79_MarkRecords — Game.exe 004757d2, cdecl.  Store the axis class of each record's vector (MDL_RECVEC) in record byte 1, then flag the
   model: all records axis-aligned -> MDL_FLAGS |= 0x30, some -> |= 0x10; updates statistics. */
void P79_MarkRecords(void *m) {
  const uint8_t *vert = (const uint8_t *)P79_PTR(rd32(m, MDL_RECVEC));
  uint8_t *rec = (uint8_t *)P79_PTR(rd32(m, MDL_RECS));
  P79_Outside = 0; P79_Total = 0;
  for (int i = 0; i < (int)rd16(m, MDL_NRECS); i++) {
    uint8_t t = *rec;
    rec[1] = (uint8_t)P79_VertClass((const float *)vert);
    rec += step1(t);
    vert += 16;
  }
  uint16_t n = rd16(m, MDL_NRECS);
  if ((int32_t)n == P79_Total) { wr16(m, MDL_FLAGS, rd16(m, MDL_FLAGS) | 0x30); P79_NumAll++;   /* every record axis-aligned */ }
  else if ((int32_t)n == P79_Outside) { P79_NumNone++; }
  else { wr16(m, MDL_FLAGS, rd16(m, MDL_FLAGS) | 0x10); P79_NumMixed++; }
  P79_SumTotal += P79_Total;
  P79_SumOut += P79_Outside;
}

/* 00475906: для каждой записи ищет первую такую же вершину; свою — помечает 8, чужую — считает */
/* P79_FindSameVerts — Game.exe 00475906, cdecl.  For each record find the first identical vector (all 4 floats) in MDL_RECVEC and store its
   index in record +4; a record that is its own first match gets byte 1 |= 8.  Returns the
   number of records that reuse an earlier vector. */
int32_t P79_FindSameVerts(void *m) {
  int32_t cnt = 0;
  uint8_t *rec = (uint8_t *)P79_PTR(rd32(m, MDL_RECS));
  const float *verts = (const float *)P79_PTR(rd32(m, MDL_RECVEC));
  int n = rd16(m, MDL_NRECS);
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
/* P79_Convert — Game.exe 00475a3d, cdecl.  Convert a disk model (links relative to src) into memory format at dst (links relative to dst):
   copies the header, widens xyz triples to float4 with w = 1.0 (vertices, and the MDL_L28
   array), copies the record vectors (MDL_RECVEC), the byte array (padded to 4) and table +0x34 (own-geometry models
   only), and rebuilds each polygon record via the field-copy program P79_Ops (U = u16 -> u32,
   F = u8 -> float, else byte).  Record types >= 0x38 or with bit 3 are only skipped.
   Returns the memory size.  Native: src is read-only (the original relocated it in place). */
int32_t P79_Convert(void *srcv, void *dstv) {
  const uint8_t *src = (const uint8_t *)srcv; uint8_t *dst = (uint8_t *)dstv;
  const float one = 1.0f;
  int32_t cur = MDL_HDR_SIZE;
  memcpy(dst, src, MDL_HDR_SIZE);
  int32_t parent = (int32_t)rd32(src, MDL_PARENT);
  uint32_t o34 = rd32(src, MDL_L34);
  if (parent == -1) {
    int n = rd16(src, MDL_NVERTS);
    const uint8_t *s = src + rd32(src, MDL_VERTS); uint8_t *d = dst + MDL_HDR_SIZE;
    for (int i = 0; i < n; i++, s += 12, d += 16) { memcpy(d, s, 12); memcpy(d + 12, &one, 4); }
    wr32(dst, MDL_VERTS, MDL_HDR_SIZE);
    cur = n * 16 + MDL_HDR_SIZE;
    int nr = rd16(src, MDL_NRECS);
    if (nr != 0) memcpy(dst + cur, src + rd32(src, MDL_RECVEC), (size_t)nr << 4);
    wr32(dst, MDL_RECVEC, (uint32_t)cur);
    cur += nr * 16;
  }
  int nn = rd16(src, MDL_N28);
  if (nn != 0) {
    const uint8_t *s = src + rd32(src, MDL_L28); uint8_t *d = dst + cur;
    for (int i = 0; i < nn; i++, s += 12, d += 16) { memcpy(d, s, 12); memcpy(d + 12, &one, 4); }
  }
  wr32(dst, MDL_L28, (uint32_t)cur);
  cur += nn * 16;
  int nb = rd16(src, MDL_NBYTES1C);
  if (nb != 0) memcpy(dst + cur, src + rd32(src, MDL_L1C), (size_t)nb);
  wr32(dst, MDL_L1C, (uint32_t)cur);
  cur += (nb + 3) & ~3;
  if (parent == -1) {
    if (o34 == 0) wr32(dst, MDL_L34, 0);
    else {
      const uint8_t *t = src + o34;
      int32_t k = (int32_t)rd32(t, 0);
      memcpy(dst + cur, t, (size_t)(k * 0x14 + 4));
      wr32(dst, MDL_L34, (uint32_t)cur);
      cur += 4 + k * 0x14;
    }
  }
  const uint8_t *rs = src + rd32(src, MDL_RECS);
  wr32(dst, MDL_RECS, (uint32_t)cur);
  int nrec = rd16(src, MDL_NRECS);
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
