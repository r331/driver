/* ported92.c — two special cases of drawing a map-block model (English overview; original notes follow).
   P92_DrawAxis: models rotated by a multiple of 90 degrees, with axis-aligned plane tests and pre-rotated
   lighting.  P92_DrawSpin: models with a rotating texture (flag 0x80: wheels, fans).
   Both keep the original x87 precision (long double intermediates, float stores) — see dot3/shade. */
/* Осевой вариант рисования модели и модель с вращающейся текстурой — восстановлено из Game.exe (0042982e, 0042a5de). */
#include "ported92.h"
#include "ported8.h"
#include <string.h>

#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P92_SinIdx")
#undef P92_SinIdx
#pragma push_macro("P92_SinIdx") /*gvi*/
#undef P92_SinIdx /*gvi*/
int32_t P92_SinIdx;
#pragma pop_macro("P92_SinIdx") /*gvi*/
#pragma pop_macro("P92_SinIdx")
#endif
#ifndef RE_HOOK_BUILD
const uint8_t *P92_SpinTex;
#endif

typedef long double ld;
/* neg — local helper: sign bit of a float (1 for negative, including -0.0), as the original tests it. */
static int neg(float f) { uint32_t u; memcpy(&u, &f, 4); return (int)(u >> 31); }
/* (a·x + b·y) + c·z в расширенной точности, затем во float (fld/fmul/faddp/fstp) */
/* dot3 — local helper: n[0]*x + n[1]*y + n[2]*z in extended precision, rounded to float once at the end
   (fld/fmul/faddp/fstp in the original). */
static float dot3(const float *n, float x, float y, float z) {
  ld r = (ld)x * (ld)n[0];
  r += (ld)y * (ld)n[1];
  r += (ld)z * (ld)n[2];
  return (float)r;
}
/* dot < 0 → фон 01251a68; иначе фон + dot, не больше 1.0 (сравнение как целых) */
/* shade — local helper: lighting intensity from a light dot product: ambient (01251a68) when d < 0,
   otherwise ambient + d clamped to 1.0 (the clamp compares the float bits as integers, as Game.exe does). */
static float shade(float d) {
  float ambient = P19_Out68;
  int32_t u;
  if (neg(d)) return ambient;
  d = (float)((ld)ambient + (ld)d);
  memcpy(&u, &d, 4);
  if (u > 0x3f800000) d = 1.0f;
  return d;
}

/* 0042982e */
/* P92_DrawAxis — Game.exe 0042982e, cdecl.  Draws map model `mref` whose rotation idx is a multiple of
   0x400 (0 / 90 / 180 / 270 deg); called from 004ee18b / 004ee4b7 instead of the general path 00429143.
   In:  idx — rotation (index into the per-frame matrix cache P84_MatCache), pos — model position,
        mode — handler table (0 -> P84_Tab0, 1 -> P84_Tab1, else P84_Tab2).
   The camera is transformed into model space (XformT); each primitive record carries a plane: type 0 is
   general (n . (-p) - d), types 1..6 are axis-aligned (x-d, -x-d, -z-d, z-d, y-d, -y-d), 7 is skipped.
   Back-facing records are marked invisible in P84_Vis and skipped by their record size.  With model flag 1
   (lit), normals and general planes are shaded with light vector P83_LightVec[idx/1024]; axis planes take
   the pre-computed P81_* intensities, rotated by idx.  Ends with P44_XformTag++ (invalidates the vertex cache).
   Native guards: idx >= 4096 returns; light index masked to 0..3. */
void P92_DrawAxis(uint32_t mref, int32_t idx, const float *pos, int32_t mode) {
  uint8_t *mdl = (uint8_t *)P79_PTR(mref);
  static float local[16];   /* зеркальная копия матрицы: в оригинале на стеке, указатель остаётся в P44_MatPtr */
  const uintptr_t *tab;
  uint8_t md = (uint8_t)mode;
  uint16_t flags, nrec, nnrm;
  float p[3], px, py, pz, nx, ny, nz, light_x, light_y, light_z;
  float aZ = 0, aX = 0, aZ2 = 0, aX2 = 0;   /* local_60/30/34/14: при idx вне {0,0x400,0x800,0xc00} в оригинале не заданы */
  int32_t light_idx;
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
  light_idx = idx / 1024;                           /* cdq / and 0x3ff / sar 10 — деление с округлением к нулю */
#ifndef RE_HOOK_BUILD
  light_idx &= 3;                                   /* охранная проверка native: 4 вектора света */
#endif
  light_x = P83_LightVec[light_idx * 4 + 0]; light_y = P83_LightVec[light_idx * 4 + 1]; light_z = P83_LightVec[light_idx * 4 + 2];
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
    for (int i = 0; i < nnrm; i++, n += 4) P84_NormLight[i] = shade(dot3(n, light_x, light_y, light_z));
  }
  for (int i = 0; i < nrec; i++) {
    uint8_t *rec = G2_011F4064;
    uint32_t type = rec[0];
    int32_t plane_idx = *(int32_t *)(rec + 4);
    const float *plane = P84_Planes + (size_t)plane_idx * 4;
    uint8_t *plane_vis = &P84_Vis[plane_idx];
    int32_t step = G2_TABLE_00550ACC[type];
    float side;
    if (!(rec[1] & 8)) {
      if (!*plane_vis) { G2_011F4064 = rec + step; continue; }
    } else {
      int axis = rec[1] & 7;
      if (axis == 7) continue;                  /* в оригинале switch без ветки 7: запись не трогается */
      switch (axis) {
      case 0: { ld a = (ld)nx * (ld)plane[0]; a += (ld)ny * (ld)plane[1]; a += (ld)nz * (ld)plane[2]; a -= (ld)plane[3]; side = (float)a; break; }
      case 1: side = px - plane[3]; break;
      case 2: side = nx - plane[3]; break;
      case 3: side = nz - plane[3]; break;
      case 4: side = pz - plane[3]; break;
      case 5: side = py - plane[3]; break;
      default: side = ny - plane[3]; break;
      }
      if (!neg(side)) { *plane_vis = 0; G2_011F4064 = rec + step; continue; }
      *plane_vis = 1;
      if (lit) {
        switch (axis) {
        case 0: if (P84_Lit[type]) P84_LightIn[plane_idx] = shade(dot3(plane, light_x, light_y, light_z)); break;
        case 1: P84_LightIn[plane_idx] = aX2; break;
        case 2: P84_LightIn[plane_idx] = aX; break;
        case 3: P84_LightIn[plane_idx] = aZ; break;
        case 4: P84_LightIn[plane_idx] = aZ2; break;
        case 5: P84_LightIn[plane_idx] = P81_NegY; break;
        default: P84_LightIn[plane_idx] = P81_PosY; break;
        }
      }
    }
    { uintptr_t f = tab ? tab[type] : 0; if (f) ((p84_handler_t)f)((uint32_t)P84_Arg[type]); }
  }
  P44_XformTag++;
}

/* 0042a5de */
/* P92_DrawSpin — Game.exe 0042a5de, cdecl.  Draws a model with a rotating texture (flag 0x80).
   Matrix: cache entry idx, recomputed (view x Euler table) once per swap (P84_MatFlag vs P47_SwapCnt);
   mirrored copy when P84_Mirror.  The first record gets colour 159/168/192 and four UVs: a square inset by
   width/32 inside the texture rectangle (bytes +9 u0, +10 v0, +0xb width, +0xc height), rotated by an angle
   from the frame counter (sin at (frame & 0xff) * 16 and at that + 0x6c9).  Then the record's handler runs
   with argument 0, or 3 when 00575ee8 is set.  P44_XformTag++.
   Native: the texture rectangle comes from P92_SpinTex (G012085F4 is a 32-bit pointer); while it is NULL the
   UVs are left unchanged (not in the original). */
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
  float sin_a = P43_Sin[P92_SinIdx];
  P92_SinIdx = (int32_t)((((uint32_t)P62_Frame & 0xff) << 4) + 0x6c9);
  float sin_b = P43_Sin[P92_SinIdx & 0xfff];
#ifdef RE_HOOK_BUILD
  const uint8_t *tex_rect = (const uint8_t *)(uintptr_t)G012085F4;
#else
  const uint8_t *tex_rect = P92_SpinTex;         /* native: родной указатель (G012085F4 — 32 бита) */
#endif
  if (tex_rect) {
    int32_t inset = (int32_t)tex_rect[0xb] / 32;
    float inset_f = (float)inset;
    float a18 = sin_a * inset_f, a10 = sin_b * inset_f;
    float a14 = (float)inset + (float)tex_rect[9];
    float a1c = (float)inset + (float)tex_rect[10];
    float a24 = (float)((int32_t)tex_rect[0xb] - inset) + (float)tex_rect[9];
    float a2c = (float)((int32_t)tex_rect[0xc] - inset) + (float)tex_rect[10];
    float uv[8] = { a14 + a18, a1c + a10, a24 + a10, a1c - a18, a24 - a18, a2c - a10, a14 - a10, a2c + a10 };
    memcpy(rec + 0x18, uv, sizeof(uv));
  }
  tab = md == 0 ? P84_Tab0 : md == 1 ? P84_Tab1 : P84_Tab2;
  f = tab ? tab[rec[0]] : 0;
  if (f) ((p84_handler_t)f)(P13_00575ee8 == 0 ? 0u : 3u);
  P44_XformTag++;
}
