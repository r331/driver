/* Осевой вариант рисования модели и модель с вращающейся текстурой — восстановлено из Game.exe (0042982e, 0042a5de). */
#include "ported92.h"
#include "ported8.h"
#include <string.h>

GAME_VAR_DEF(int32_t, P92_SinIdx, 0x00b1c284)
#ifndef RE_HOOK_BUILD
const uint8_t *P92_SpinTex;
#endif

typedef long double ld;
static int neg(float f) { uint32_t u; memcpy(&u, &f, 4); return (int)(u >> 31); }
/* (a·x + b·y) + c·z в расширенной точности, затем во float (fld/fmul/faddp/fstp) */
static float dot3(const float *n, float x, float y, float z) {
  ld r = (ld)x * (ld)n[0];
  r += (ld)y * (ld)n[1];
  r += (ld)z * (ld)n[2];
  return (float)r;
}
/* dot < 0 → фон 01251a68; иначе фон + dot, не больше 1.0 (сравнение как целых) */
static float shade(float d) {
  float amb = P19_Out68;
  int32_t u;
  if (neg(d)) return amb;
  d = (float)((ld)amb + (ld)d);
  memcpy(&u, &d, 4);
  if (u > 0x3f800000) d = 1.0f;
  return d;
}

/* 0042982e */
void P92_DrawAxis(uint32_t mref, int32_t idx, const float *pos, int32_t mode) {
  uint8_t *mdl = (uint8_t *)P79_PTR(mref);
  static float local[16];   /* зеркальная копия матрицы: в оригинале на стеке, указатель остаётся в P44_MatPtr */
  const uintptr_t *tab;
  uint8_t md = (uint8_t)mode;
  uint16_t flags, nrec, nnrm;
  float p[3], px, py, pz, nx, ny, nz, lx, ly, lz;
  float aZ = 0, aX = 0, aZ2 = 0, aX2 = 0;   /* local_60/30/34/14: при idx вне {0,0x400,0x800,0xc00} в оригинале не заданы */
  int32_t k;
#ifndef RE_HOOK_BUILD
  if ((uint32_t)idx >= 4096) return;        /* охранная проверка native: кэш P84_MatCache — 4096 записей */
#endif
  if (G2_011F43B0 == 0) P63_SphN = 0;
  else P63_SphereHits(pos, (const uint8_t *)mdl);
  tab = md == 1 ? P84_Tab1 : (md == 0 ? P84_Tab0 : P84_Tab2);
  flags = *(uint16_t *)(mdl + 2);
  P44_BiasX = P84_Mirror ? -pos[0] : pos[0];
  P44_BiasY = pos[1];
  P44_BiasZ = pos[2];
  P84_VertRef = *(uint32_t *)(mdl + 0x20);
  P84_Planes = (float *)P79_PTR(*(uint32_t *)(mdl + 0x24));
  P44_MatPtr = P84_MatCache[idx];
  p[0] = pos[0]; p[1] = pos[1]; p[2] = pos[2];
  P44_XformT(p);
  px = p[0]; py = p[1]; pz = p[2];
  nx = -px; ny = -py; nz = -pz;
  k = idx / 1024;                           /* cdq / and 0x3ff / sar 10 — деление с округлением к нулю */
#ifndef RE_HOOK_BUILD
  k &= 3;                                   /* охранная проверка native: 4 вектора света */
#endif
  lx = P83_LightVec[k * 4 + 0]; ly = P83_LightVec[k * 4 + 1]; lz = P83_LightVec[k * 4 + 2];
  if (P84_Mirror) {
    memcpy(local, P84_MatCache[idx], sizeof(local));
    local[0] = -local[0]; local[3] = -local[3]; local[6] = -local[6];
    P44_MatPtr = local;
  }
  G2_011F4064 = (uint8_t *)P79_PTR(*(uint32_t *)(mdl + 0x2c));
  nrec = *(uint16_t *)(mdl + 0x16);
  nnrm = *(uint16_t *)(mdl + 0x18);
  int lit = flags & 1;
  if (lit) {
    if (idx == 0x800)      { aZ = P81_NegZ; aX = P81_NegX; aZ2 = P81_PosZ; aX2 = P81_PosX; }
    else if (idx == 0)     { aZ = P81_PosZ; aX = P81_PosX; aZ2 = P81_NegZ; aX2 = P81_NegX; }
    else if (idx == 0x400) { aZ = P81_PosX; aX = P81_NegZ; aZ2 = P81_NegX; aX2 = P81_PosZ; }
    else if (idx == 0xc00) { aZ = P81_NegX; aX = P81_PosZ; aZ2 = P81_PosX; aX2 = P81_NegZ; }
    const float *n = (const float *)P79_PTR(*(uint32_t *)(mdl + 0x28));
    for (int i = 0; i < nnrm; i++, n += 4) P84_NormLight[i] = shade(dot3(n, lx, ly, lz));
  }
  for (int i = 0; i < nrec; i++) {
    uint8_t *rec = G2_011F4064;
    uint32_t type = rec[0];
    int32_t pi = *(int32_t *)(rec + 4);
    const float *pl = P84_Planes + (size_t)pi * 4;
    uint8_t *vis = &P84_Vis[pi];
    int32_t step = G2_TABLE_00550ACC[type];
    float t;
    if (!(rec[1] & 8)) {
      if (!*vis) { G2_011F4064 = rec + step; continue; }
    } else {
      int ax = rec[1] & 7;
      if (ax == 7) continue;                  /* в оригинале switch без ветки 7: запись не трогается */
      switch (ax) {
      case 0: { ld a = (ld)nx * (ld)pl[0]; a += (ld)ny * (ld)pl[1]; a += (ld)nz * (ld)pl[2]; a -= (ld)pl[3]; t = (float)a; break; }
      case 1: t = px - pl[3]; break;
      case 2: t = nx - pl[3]; break;
      case 3: t = nz - pl[3]; break;
      case 4: t = pz - pl[3]; break;
      case 5: t = py - pl[3]; break;
      default: t = ny - pl[3]; break;
      }
      if (!neg(t)) { *vis = 0; G2_011F4064 = rec + step; continue; }
      *vis = 1;
      if (lit) {
        switch (ax) {
        case 0: if (P84_Lit[type]) P84_LightIn[pi] = shade(dot3(pl, lx, ly, lz)); break;
        case 1: P84_LightIn[pi] = aX2; break;
        case 2: P84_LightIn[pi] = aX; break;
        case 3: P84_LightIn[pi] = aZ; break;
        case 4: P84_LightIn[pi] = aZ2; break;
        case 5: P84_LightIn[pi] = P81_NegY; break;
        default: P84_LightIn[pi] = P81_PosY; break;
        }
      }
    }
    { uintptr_t f = tab ? tab[type] : 0; if (f) ((p84_handler_t)f)((uint32_t)P84_Arg[type]); }
  }
  P44_XformTag++;
}

/* 0042a5de */
void P92_DrawSpin(uint32_t mref, int32_t idx, const float *pos, int32_t mode) {
  uint8_t *mdl = (uint8_t *)P79_PTR(mref);
  static float local[16];   /* зеркальная копия: в оригинале на стеке, указатель остаётся в P44_MatPtr */
  uint8_t md = (uint8_t)mode;
  float *mat;
  uint8_t *rec;
  const uintptr_t *tab;
  uintptr_t f;
#ifndef RE_HOOK_BUILD
  if ((uint32_t)idx >= 4096) return;        /* охранная проверка native: кэш P84_MatCache — 4096 записей */
#endif
  if (G2_011F43B0 == 0) P63_SphN = 0;
  else P63_SphereHits(pos, (const uint8_t *)mdl);
  P84_LightIn[0] = P81_PosY;
  P44_BiasX = P84_Mirror ? -pos[0] : pos[0];
  P44_BiasY = pos[1];
  P44_BiasZ = pos[2];
  P84_VertRef = *(uint32_t *)(mdl + 0x20);
  P84_Planes = (float *)P79_PTR(*(uint32_t *)(mdl + 0x24));
  mat = P84_MatCache[idx];
  if (P84_MatFlag[idx] != (int32_t)P47_SwapCnt) {
    Mat3Mul_0052859A(P44_ViewMat, (const float *)(P56_EulerTab + (size_t)idx * 0x40), mat);
    P84_MatFlag[idx] = (int32_t)P47_SwapCnt;
  }
  P44_MatPtr = mat;
  if (P84_Mirror) {
    memcpy(local, mat, sizeof(local));
    local[0] = -local[0]; local[3] = -local[3]; local[6] = -local[6];
    P44_MatPtr = local;
  }
  rec = (uint8_t *)P79_PTR(*(uint32_t *)(mdl + 0x2c));
  G2_011F4064 = rec;
  { float c0 = 159.0f, c1 = 168.0f, c2 = 192.0f; memcpy(rec + 0x38, &c0, 4); memcpy(rec + 0x3c, &c1, 4); memcpy(rec + 0x40, &c2, 4); }
  P92_SinIdx = (int32_t)(((uint32_t)P62_Frame & 0xff) << 4);
  float s1 = P43_Sin[P92_SinIdx];
  P92_SinIdx = (int32_t)((((uint32_t)P62_Frame & 0xff) << 4) + 0x6c9);
  float s2 = P43_Sin[P92_SinIdx & 0xfff];
#ifdef RE_HOOK_BUILD
  const uint8_t *tx = (const uint8_t *)(uintptr_t)G012085F4;
#else
  const uint8_t *tx = P92_SpinTex;         /* native: родной указатель (G012085F4 — 32 бита) */
#endif
  if (tx) {
    int32_t r = (int32_t)tx[0xb] / 32;
    float fr = (float)r;
    float a18 = s1 * fr, a10 = s2 * fr;
    float a14 = (float)r + (float)tx[9];
    float a1c = (float)r + (float)tx[10];
    float a24 = (float)((int32_t)tx[0xb] - r) + (float)tx[9];
    float a2c = (float)((int32_t)tx[0xc] - r) + (float)tx[10];
    float uv[8] = { a14 + a18, a1c + a10, a24 + a10, a1c - a18, a24 - a18, a2c - a10, a14 - a10, a2c + a10 };
    memcpy(rec + 0x18, uv, sizeof(uv));
  }
  tab = md == 0 ? P84_Tab0 : md == 1 ? P84_Tab1 : P84_Tab2;
  f = tab ? tab[rec[0]] : 0;
  if (f) ((p84_handler_t)f)(P13_00575ee8 == 0 ? 0u : 3u);
  P44_XformTag++;
}
