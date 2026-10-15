#include "ported84.h"
#include "ported8.h"
#include <string.h>

GAME_VAR_DEF(uint8_t, P84_Mirror, 0x00bdc288)
GAME_VAR_DEF(const uintptr_t *, P84_Tab0, 0x011effe0)
GAME_VAR_DEF(const uintptr_t *, P84_Tab1, 0x01209660)
GAME_VAR_DEF(const uintptr_t *, P84_Tab2, 0x011f4060)
GAME_VAR_DEF(uint32_t, P84_VertRef, 0x01209614)
GAME_VAR_DEF(float *, P84_Planes, 0x012085f0)
GAME_VAR_DEF(p84_light_t, P84_LightIn, 0x012043c0)
GAME_VAR_DEF(p84_vis_t, P84_Vis, 0x01208600)
GAME_VAR_DEF(p84_nlight_t, P84_NormLight, 0x012496c0)
GAME_VAR_DEF(p84_mats_t, P84_MatCache, 0x01209680)
GAME_VAR_DEF(p84_flags_t, P84_MatFlag, 0x011f0060)
GAME_VAR_DEF(p84_b56_t, P84_Arg, 0x00550cc4)
GAME_VAR_DEF(p84_b56_t, P84_Lit, 0x00550c8c)
#ifndef RE_HOOK_BUILD
uintptr_t P84_Handlers[6][56];
#include "p84_data.h"
void P84_InitConsts(void) {
  memcpy(P84_Arg, P84_ArgInit, 56);
  memcpy(P84_Lit, P84_LitInit, 56);
}
/* 011effe0/01209660/011f4060 ← таблицы набора (режимы 0, 1, другой) */
void P84_SelectTables(int32_t alt) {
  P84_Tab0 = P84_Handlers[alt ? 3 : 0];
  P84_Tab1 = P84_Handlers[alt ? 4 : 1];
  P84_Tab2 = P84_Handlers[alt ? 5 : 2];
}
#else
void P84_InitConsts(void) {}
#endif

typedef long double ld;
static int neg(float f) { uint32_t u; memcpy(&u, &f, 4); return (int)(u >> 31); }
/* (a·x + b·y) + c·z в расширенной точности, затем во float, как fld/fmul/faddp/fstp */
static float dot3(const float *a, float x, float y, float z) {
  ld r = (ld)x * (ld)a[0];
  r += (ld)y * (ld)a[1];
  r += (ld)z * (ld)a[2];
  return (float)r;
}
/* освещение: dot < 0 (знаковый бит) → фон; иначе фон + dot, не больше 1.0 (сравнение как целых) */
static float shade(float d) {
  float amb = P19_Out68;
  if (neg(d)) return amb;
  d = (float)((ld)amb + (ld)d);
  { int32_t u; memcpy(&u, &d, 4); if (u > 0x3f800000) d = 1.0f; }
  return d;
}
static void call_h(const uintptr_t *tab, uint32_t type) {
  uintptr_t f = tab ? tab[type] : 0;
  if (f) ((p84_handler_t)f)((uint32_t)P84_Arg[type]);
}

/* общая часть 00428b69/00429143: mdl — заголовок, modmat — матрица модели (для света), viewm — ViewMat×modmat */
static void draw_core(uint8_t *mdl, const float *modmat, const float *viewm, const float *pos, const uintptr_t *tab) {
  uint16_t flags = *(uint16_t *)(mdl + 2), nrec = *(uint16_t *)(mdl + 0x16), nnrm = *(uint16_t *)(mdl + 0x18);
  float lx = 0, ly = 0, lz = 0;
  static float local[16];   /* зеркальная копия матрицы остаётся в P44_MatPtr после возврата (в оригинале — стек) */
  float p3[3] = { pos[0], pos[1], pos[2] };
  float nx, ny, nz;
  int lit = flags & 1;
  if (lit) {
    float lv[4] = { P19_OutA, P19_OutB, P19_OutC, 0 };   /* 4-е слово (005507dc) Xform не читает */
    P44_MatPtr = (float *)modmat;
    P44_Xform(lv);
    lx = lv[0]; ly = lv[1]; lz = lv[2];
  }
  P44_MatPtr = (float *)viewm;
  P44_XformT(p3);
  nx = -p3[0]; ny = -p3[1]; nz = -p3[2];
  G2_011F4064 = (uint8_t *)P79_PTR(*(uint32_t *)(mdl + 0x2c));
  if (P84_Mirror) {
    memcpy(local, viewm, sizeof(local));
    local[0] = -local[0]; local[3] = -local[3]; local[6] = -local[6];
    P44_MatPtr = local;
  }
  if (lit) {
    const float *n = (const float *)P79_PTR(*(uint32_t *)(mdl + 0x28));
    for (int i = 0; i < nnrm; i++, n += 4) P84_NormLight[i] = shade(dot3(n, lx, ly, lz));
  }
  for (int i = 0; i < nrec; i++) {
    uint8_t *rec = G2_011F4064;
    uint32_t type = rec[0];
    int32_t pi = *(int32_t *)(rec + 4);
    float *pl = P84_Planes + (size_t)pi * 4;
    uint8_t *vis = &P84_Vis[pi];
    int step = G2_TABLE_00550ACC[type];
    if (!(rec[1] & 8)) {
      if (!*vis) G2_011F4064 = rec + step;
      else call_h(tab, type);
    } else {
      ld a = (ld)nx * (ld)pl[0];
      a += (ld)ny * (ld)pl[1];
      a += (ld)nz * (ld)pl[2];
      a -= (ld)pl[3];
      if (!neg((float)a)) { *vis = 0; G2_011F4064 = rec + step; }
      else {
        *vis = 1;
        if (lit && P84_Lit[type]) P84_LightIn[pi] = shade(dot3(pl, lx, ly, lz));
        call_h(tab, type);
      }
    }
  }
  P44_XformTag++;
}

static const uintptr_t *pick_tab(int32_t mode) {
  uint8_t m = (uint8_t)mode;
  return m == 1 ? P84_Tab1 : (m == 0 ? P84_Tab0 : P84_Tab2);
}
static void prologue(uint8_t *mdl, uint32_t mref, const float *pos) {
  if (G2_011F43B0 == 0) P63_SphN = 0; else P63_SphereHits(pos, (const uint8_t *)mdl);
  (void)mref;
  P44_BiasX = P84_Mirror ? -pos[0] : pos[0];
  P44_BiasY = pos[1];
  P44_BiasZ = pos[2];
  P84_VertRef = *(uint32_t *)(mdl + 0x20);
  P84_Planes = (float *)P79_PTR(*(uint32_t *)(mdl + 0x24));
}

/* 00428b69 */
void P84_DrawModel(uint32_t mref, const float *mat, const float *pos, int32_t mode) {
  uint8_t *mdl = (uint8_t *)P79_PTR(mref);
  float view[16];
  const uintptr_t *tab = pick_tab(mode);
  prologue(mdl, mref, pos);
  if (*(uint16_t *)(mdl + 2) & 0x4000)
    mat = (const float *)(P56_EulerTab + (size_t)(((uint32_t)(-(int32_t)(int16_t)P59_AngB)) & 0xfff) * 0x40);
  memset(view, 0, sizeof(view));
  Mat3Mul_0052859A(P44_ViewMat, mat, view);
  draw_core(mdl, mat, view, pos, tab);
}

/* 00429143 */
void P84_DrawModelIdx(uint32_t mref, int32_t idx, const float *pos, int32_t mode) {
  uint8_t *mdl = (uint8_t *)P79_PTR(mref);
  const uintptr_t *tab = pick_tab(mode);
  const float *mat;
  prologue(mdl, mref, pos);
  if (*(uint16_t *)(mdl + 2) & 0x4000) idx = (int32_t)(((uint32_t)(-(int32_t)(int16_t)P59_AngB)) & 0xfff);
  mat = (const float *)(P56_EulerTab + (size_t)idx * 0x40);
  if (P84_MatFlag[idx] != (int32_t)P47_SwapCnt) {
    Mat3Mul_0052859A(P44_ViewMat, mat, P84_MatCache[idx]);
    P84_MatFlag[idx] = (int32_t)P47_SwapCnt;
  }
  draw_core(mdl, mat, P84_MatCache[idx], pos, tab);
}
