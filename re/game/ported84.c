#include "ported84.h"
#include "ported8.h"
#include "ported11.h"
#include "ported28.h"
#include "ported33.h"
#include "ported62.h"
#include "ported86.h"
#include "ported98.h"
#include "ported102.h"
#include "reptr.h"
#include "cartab.h"
#include <math.h>
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
GAME_VAR_DEF(int32_t, P84_TexFiltOn, 0x01252bc0)
GAME_VAR_DEF(float, P84_ShineK, 0x01159d58)
GAME_VAR_DEF(p84_uv_t, P84_ShineUV, 0x01159d80)
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
static void call_ha(const uintptr_t *tab, uint32_t type, uint32_t arg) {
  uintptr_t f = tab ? tab[type] : 0;
  if (f) ((p84_handler_t)f)(arg);
}
/* var = 0 — 00428b69/00429143; var = 1 — 0042b7cb (аргумент обработчика 2 без света / 3 со светом, свет плоскости = shade(0.01)) */
static void draw_core(uint8_t *mdl, const float *modmat, const float *viewm, const float *pos, const uintptr_t *tab, int var) {
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
      else if (var) call_ha(tab, type, lit ? 3u : 2u);
      else call_h(tab, type);
    } else {
      ld a = (ld)nx * (ld)pl[0];
      a += (ld)ny * (ld)pl[1];
      a += (ld)nz * (ld)pl[2];
      a -= (ld)pl[3];
      if (!neg((float)a)) { *vis = 0; G2_011F4064 = rec + step; }
      else {
        *vis = 1;
        if (lit && P84_Lit[type]) P84_LightIn[pi] = var ? shade(0.01f) : shade(dot3(pl, lx, ly, lz));
        if (var) call_ha(tab, type, lit ? 3u : 2u); else call_h(tab, type);
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
  draw_core(mdl, mat, view, pos, tab, 0);
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
  draw_core(mdl, mat, P84_MatCache[idx], pos, tab, 0);
}

/* ---- v1.81 ---- */
/* 0042b7cb: как 00428b69 (угол 0x4000 — та же таблица 00b1c280 по −00b1c26a), но обработчик получает константу:
   2 — модель без света, 3 — со светом; освещённость видимой плоскости (P84_Lit[тип]) — shade(0.01) вместо n·L
   (в оригинале dot записывается и сразу перезаписывается 0x3c23d70a). */
void P84_DrawModelC(uint32_t mref, const float *mat, const float *pos, int32_t mode) {
  uint8_t *mdl = (uint8_t *)P79_PTR(mref);
  float view[16];
  const uintptr_t *tab = pick_tab(mode);
  prologue(mdl, mref, pos);
  if (*(uint16_t *)(mdl + 2) & 0x4000)
    mat = (const float *)(P56_EulerTab + (size_t)(((uint32_t)(-(int32_t)(int16_t)P59_AngB)) & 0xfff) * 0x40);
  memset(view, 0, sizeof(view));
  Mat3Mul_0052859A(P44_ViewMat, mat, view);
  draw_core(mdl, mat, view, pos, tab, 1);
}

#ifdef RE_HOOK_BUILD
#  define P84_STD __attribute__((stdcall))
#else
#  define P84_STD
#endif
static void tex_filter(int32_t a, int32_t b, int32_t c) {   /* (*01270d6c) = grTexFilterMode — по имени (как ported124) */
  for (int i = 0; i < P33_GlideCount(); i++)
    if (strcmp(P33_GlideName(i), "_grTexFilterMode@12") == 0) {
      void (P84_STD *f)(int32_t, int32_t, int32_t) = (void (P84_STD *)(int32_t, int32_t, int32_t))P33_GlideProc(i);
      if (f != NULL) f(a, b, c);
      return;
    }
}
static int32_t fist(ld v) { return (int32_t)lrintl(v); }    /* fistp, округление к ближайшему */

/* 0042a9f1: кузов машины car (00d077c0 + car·0x148). Пролог как 00428b69; один раз grTexFilterMode(0,1,1) (флаг 01252bc0);
   ViewMat×mat; освещение нормалей — всегда (свет через mat). Записи обходятся подряд: плоскость и освещённость берутся по номеру
   записи (не по +4), без кэша видимости. Обычный режим (нет 0055c974 или shk = 0): P86_Detail = 0, обработчики по P84_Arg.
   Блик (shk ≠ 0): UV нормалей в 01159d80 по столбцам 0 и 2 матрицы машины P98_CarMat[car] и значку CARSHINE (байты 9..0xc),
   сдвиг по позиции машины / 256 по модулю половины значка; для записи — P28_Dst2[запись + shine·0x170]: 0 — Detail 0, 1..2 — Detail 1
   и 01159d58 = shk·50. Машина 0x41 при 00b87ea0 ≠ 0 (призрак) — матрица 011360a0, Detail всегда 2 и 01159d58 = 100.
   Отступления native: shine ≠ 0 или запись ≥ 0x170 — байт 0; NULL значка / нулевые размеры — обычный режим не меняется, UV = 0;
   car вне 0..0x41 — выход. a7 (в оригинале a7 >> 2 в неиспользуемой локали) не читается. */
static float g_view[16];   /* остаётся в P44_MatPtr после возврата (в оригинале — стек) */
void P84_DrawCar(uint32_t mref, const float *mat, const float *pos, int32_t mode, int32_t car, int32_t shine, int32_t a7, float shk) {
  uint8_t *mdl = (uint8_t *)P79_PTR(mref);
  const uintptr_t *tab = pick_tab(mode);
  uint16_t nrec = *(uint16_t *)(mdl + 0x16), nnrm = *(uint16_t *)(mdl + 0x18);
  float p3[3] = { pos[0], pos[1], pos[2] }, nx, ny, nz, lx, ly, lz;
  const float *pl;
  int ghost, shinemode;
  (void)a7;
  if (car < 0 || car > 0x41) return;
  prologue(mdl, mref, pos);
  if (P84_TexFiltOn != 1) { tex_filter(0, 1, 1); P84_TexFiltOn = 1; }
  memset(g_view, 0, sizeof(g_view));
  Mat3Mul_0052859A(P44_ViewMat, mat, g_view);
  {
    float lv[4] = { P19_OutA, P19_OutB, P19_OutC, 0 };
    P44_MatPtr = (float *)mat;
    P44_Xform(lv);
    lx = lv[0]; ly = lv[1]; lz = lv[2];
  }
  P44_MatPtr = g_view;
  P44_XformT(p3);
  nx = -p3[0]; ny = -p3[1]; nz = -p3[2];
  {
    const float *n = (const float *)P79_PTR(*(uint32_t *)(mdl + 0x28));
    for (int i = 0; i < nnrm; i++, n += 4) P84_NormLight[i] = shade(dot3(n, lx, ly, lz));
  }
  if (P84_Mirror) { g_view[0] = -g_view[0]; g_view[3] = -g_view[3]; g_view[6] = -g_view[6]; }
  ghost = (P62_HudOff1 != 0 && car == 0x41);
  shinemode = ghost || !(P28_ShineFlag == 0 || shk == 0.0f);
  if (shinemode) {
    const uint8_t *ic = (const uint8_t *)re_ptr((uint32_t)P28_CarShine);
    const float *m = ghost || car == 0x41 ? P102_GhostMat : P98_CarMat[car];
    const p99_car_t *c = &P99_Cars[car];
    int32_t hw = ic ? ic[0xb] >> 1 : 0, hh = ic ? ic[0xc] >> 1 : 0;
    float fh = (float)hh, b9 = ic ? (float)ic[9] : 0, b10 = ic ? (float)ic[10] : 0;
    float q9c = ic ? (float)(ic[0xb] >> 2) : 0, q98 = ic ? (float)(ic[0xc] >> 2) : 0, ub, vb, ua, va;
    int32_t t;
    t = fist((ld)(float)c->pos[0] * (ld)0.00390625f); P11_00ba52d0 = t;
    ub = hw ? (float)(-t % hw) : 0.0f;
    t = fist((ld)(float)c->pos[2] * (ld)0.00390625f); P11_00ba52d0 = t;
    va = hh ? (float)(t % hh) : 0.0f;
    if (neg(ub)) ub = ub + fh;      /* в оригинале к обоим прибавляется половина высоты */
    if (neg(va)) va = va + fh;
    ua = ub + b9; vb = va + b10;
    {
      const float *n = (const float *)P79_PTR(*(uint32_t *)(mdl + 0x28));
      uint8_t *uv = P84_ShineUV;
      for (int i = 0; i < nnrm && i < 0x100; i++, n += 4, uv += 2) {
        float a = (float)(((ld)n[0] * (ld)m[0] + (ld)n[1] * (ld)m[3]) + (ld)n[2] * (ld)m[6]);
        float b = (float)(((ld)n[0] * (ld)m[2] + (ld)n[1] * (ld)m[5]) + (ld)n[2] * (ld)m[8]);
        t = fist(((ld)-a + (ld)1.0f) * (ld)q9c + (ld)ua); P11_00ba52d0 = t; uv[0] = (uint8_t)t;
        t = fist(((ld)-b + (ld)1.0f) * (ld)q98 + (ld)vb); P11_00ba52d0 = t; uv[1] = (uint8_t)t;
      }
    }
  } else P86_Detail = 0;
  G2_011F4064 = (uint8_t *)P79_PTR(*(uint32_t *)(mdl + 0x2c));
  pl = P84_Planes;
  for (int i = 0; i < nrec; i++, pl += 4) {
    uint8_t *rec = G2_011F4064;
    uint32_t type = rec[0];
    ld a = (ld)nx * (ld)pl[0];
    a += (ld)ny * (ld)pl[1];
    a += (ld)nz * (ld)pl[2];
    a -= (ld)pl[3];
    if (!neg((float)a)) { G2_011F4064 = rec + G2_TABLE_00550ACC[type]; continue; }
    if (P84_Lit[type]) P84_LightIn[i] = shade(dot3(pl, lx, ly, lz));
    if (shinemode) {
      uint32_t k = (uint32_t)i + (uint32_t)shine * 0x170u;
      uint8_t d = (shine == 0 && k < sizeof(P28_Dst2)) ? P28_Dst2[k] : 0;
      if (ghost) { P86_Detail = 2; if (d != 0 && d < 3) P84_ShineK = 100.0f; }
      else if (d == 0) P86_Detail = 0;
      else if (d < 3) { P86_Detail = 1; P84_ShineK = shk * 50.0f; }
    }
    call_h(tab, type);
  }
  if (shinemode) P86_Detail = 0;
  P44_XformTag++;
}
