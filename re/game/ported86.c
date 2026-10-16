/* Текстурные и гуро-обработчики записей модели (набор 1, режим 0) — восстановлено из Game.exe. */
#include "ported86.h"
#include "ported12.h"
#include "ported14.h"
#include "smallfuncs2.h"
#include "ported33.h"
#include "../platform/plat.h"
#include <string.h>

#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P86_CurTex")
#undef P86_CurTex
#pragma push_macro("P86_CurTex") /*gvi*/
#undef P86_CurTex /*gvi*/
int32_t P86_CurTex;
#pragma pop_macro("P86_CurTex") /*gvi*/
#pragma pop_macro("P86_CurTex")
#endif
GAME_VAR_DEF(p86_texsrc_fn, P86_TexSrc, 0x01270d5c)
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P86_Detail")
#undef P86_Detail
#pragma push_macro("P86_Detail") /*gvi*/
#undef P86_Detail /*gvi*/
uint8_t P86_Detail;
#pragma pop_macro("P86_Detail") /*gvi*/
#pragma pop_macro("P86_Detail")
#endif

typedef struct { int nv; int uv; int col; int size; int detail; } p86_fmt;
static const p86_fmt F20 = { 3, 0x14, 0x2c, 0x38, 0 };
static const p86_fmt F21 = { 4, 0x18, 0x38, 0x44, 0 };
static const p86_fmt F22 = { 3, 0x20, 0x38, 0x44, 1 };
static const p86_fmt F23 = { 4, 0x28, 0x48, 0x54, 1 };

static float rf(const uint8_t *p, int off) { float f; memcpy(&f, p + off, 4); return f; }
static int32_t ri(const uint8_t *p, int off) { int32_t i; memcpy(&i, p + off, 4); return i; }

/* прибавить к цвету вершины вклад всех динамических источников света (запись 0x24 в 011f40e0) */
static void add_lights(float c[3], const p85_vtx *v) {
  for (int i = 0; i < P63_SphN; i++) {
    const float *L = (const float *)((const uint8_t *)G2_011F40E0 + (size_t)(uint32_t)P63_Hits[i] * 0x24);
    float dx = L[0] - v->vx, dy = L[1] - v->vy, dz = L[2] - v->z;
    float d2 = dx * dx + dy * dy;
    d2 = d2 + dz * dz;
    if (d2 < L[7]) {                      /* радиус² */
      float f = L[7] - d2;
      f = f * L[8];
      for (int k = 0; k < 3; k++) {
        float x = f * L[4 + k];
        c[k] = x + c[k];
        if (c[k] > 255.0f) c[k] = 255.0f;
      }
    }
  }
}
static void set_color(p85_rv *r, const float c[3]) { r->r = c[0]; r->g = c[1]; r->b = c[2]; }
static void set_uv(p85_rv *r, const uint8_t *rec, int off, const p85_vtx *v) {
  r->tmu[0] = rf(rec, off) * v->oow;
  r->tmu[1] = rf(rec, off + 4) * v->oow;
}
static void tex_state(const uint8_t *rec) {
  if (P85_StateDirty != 4) { P85_StateFn(3, 1, 0, 1, 0); P85_StateDirty = 4; }
  if ((int32_t)rec[2] != P86_CurTex) {
    P86_CurTex = rec[2];
    const P40_Slot *s = &P40_Slots[rec[2]];
    P86_TexSrc(0, s->texaddr, 3, s->info);
  }
}

static void do_tex(uint32_t arg, const p86_fmt *f) {
  const uint8_t *rec = G2_011F4064;
  int32_t ix[4];
  p85_vtx *v[4];
  for (int i = 0; i < f->nv; i++) ix[i] = ri(rec, 8 + 4 * i);
  G2_011F4064 = (uint8_t *)rec + f->size;
  for (int i = 0; i < f->nv; i++) v[i] = P85_Prep(ix[i]);
  if ((uint8_t)P82_Edge) { const p85_vtx *vs[4] = { v[0], v[1], v[2], v[3] }; if (P85_EdgeReject(vs, f->nv)) return; }
  float k = P84_LightIn[ri(rec, 4)];
  float base[3];
  for (int i = 0; i < 3; i++) base[i] = k * rf(rec, f->col + 4 * i);
  /* порядок вершин растеризатора: треугольник (0,1,2); четырёхугольник (0,2,1) и затем (0,2,3) */
  static const int ord[3] = { 0, 2, 1 };
  const int *o = f->nv == 3 ? (const int[3]){ 0, 1, 2 } : ord;
  float c[3][3];
  for (int i = 0; i < 3; i++) { memcpy(c[i], base, sizeof base); if (P63_SphN != 0) add_lights(c[i], v[o[i]]); }
  tex_state(rec);
  P85_SetBlend((uint8_t)arg);
  for (int i = 0; i < 3; i++) {
    p85_rv *r = &P85_RV[i];
    P85_PutVtx(r, v[o[i]]);
    set_uv(r, rec, f->uv + 8 * o[i], v[o[i]]);
    set_color(r, c[i]);
  }
  if (!(f->detail && P86_Detail == 2)) P85_CallRaster();
  if (f->nv == 4) {
    float c3[3];
    memcpy(c3, base, sizeof base);
    if (P63_SphN != 0) add_lights(c3, v[3]);
    P85_PutVtx(&P85_RV[2], v[3]);
    set_uv(&P85_RV[2], rec, f->uv + 24, v[3]);
    if (P63_SphN != 0) set_color(&P85_RV[2], c3);
    if (!(f->detail && P86_Detail == 2)) P85_CallRaster();
  }
}
void P86_TexTri(uint32_t arg) { do_tex(arg, &F20); }
void P86_TexQuad(uint32_t arg) { do_tex(arg, &F21); }
void P86_TexTriD(uint32_t arg) { do_tex(arg, &F22); }
void P86_TexQuadD(uint32_t arg) { do_tex(arg, &F23); }

/* гуро: цвет записи × освещённость нормали вершины */
static void do_gouraud(uint32_t arg, int nv, int nloff, int coloff, int size) {
  const uint8_t *rec = G2_011F4064;
  int32_t ix[4];
  p85_vtx *v[4];
  for (int i = 0; i < nv; i++) ix[i] = ri(rec, 8 + 4 * i);
  G2_011F4064 = (uint8_t *)rec + size;
  for (int i = 0; i < nv; i++) v[i] = P85_Prep(ix[i]);
  if ((uint8_t)P82_Edge) { const p85_vtx *vs[4] = { v[0], v[1], v[2], v[3] }; if (P85_EdgeReject(vs, nv)) return; }
  float col[3];
  for (int i = 0; i < 3; i++) col[i] = rf(rec, coloff + 4 * i);
  static const int ord4[3] = { 0, 2, 1 };
  const int *o = nv == 3 ? (const int[3]){ 0, 1, 2 } : ord4;
  P85_CallState();
  P85_SetBlend((uint8_t)arg);
  for (int i = 0; i < 3; i++) {
    p85_rv *r = &P85_RV[i];
    float nl = P84_NormLight[ri(rec, nloff + 4 * o[i])];
    P85_PutVtx(r, v[o[i]]);
    r->r = col[0] * nl; r->g = col[1] * nl; r->b = col[2] * nl;
  }
  P85_CallRaster();
  if (nv == 4) {
    float nl = P84_NormLight[ri(rec, nloff + 12)];
    P85_PutVtx(&P85_RV[2], v[3]);
    P85_RV[2].r = col[0] * nl; P85_RV[2].g = col[1] * nl; P85_RV[2].b = col[2] * nl;
    P85_CallRaster();
  }
}
void P86_GouraudTri(uint32_t arg) { do_gouraud(arg, 3, 0x14, 0x20, 0x2c); }
void P86_GouraudQuad(uint32_t arg) { do_gouraud(arg, 4, 0x18, 0x28, 0x34); }

#ifndef RE_HOOK_BUILD
int32_t P86_TexCount;
static int g_tex[256];
static int g_bound;
void P86_NativeReset(void) {
  for (int i = 0; i < 256; i++) { if (g_tex[i]) plat_tex_free(g_tex[i]); g_tex[i] = 0; }
  P86_TexCount = 0;
}
int P86_NativeHandle(int32_t slot) { return slot >= 0 && slot < 256 ? g_tex[slot] : 0; }
static int pick_palette(void) {
  if (P12_01252aa0[1]) return 1;
  for (int i = 0; i < 0x32; i++) if (P12_01252aa0[i]) return i;
  return -1;
}
void P86_NativeCapture(int32_t slot, int pair, const void *page0, const void *page1) {
  static uint32_t px[256 * 256];
  if (slot < 0 || slot >= 256) return;
  if (!pair) {
    const uint16_t *s = (const uint16_t *)page0;       /* ARGB1555 */
    for (int i = 0; i < 256 * 256; i++) {
      uint16_t w = s[i];
      uint32_t r = (w >> 10) & 31, g = (w >> 5) & 31, b = w & 31, a = (w & 0x8000) ? 255u : 0u;
      r = r << 3 | r >> 2; g = g << 3 | g >> 2; b = b << 3 | b >> 2;
      px[i] = a << 24 | b << 16 | g << 8 | r;
    }
    if (g_tex[slot]) plat_tex_free(g_tex[slot]);
    g_tex[slot] = plat_tex_create(256, 256, px);
    if (g_tex[slot]) P86_TexCount++;
    return;
  }
  for (int h = 0; h < 2; h++) {
    const uint8_t *s = (const uint8_t *)(h ? page1 : page0);
    int pal = pick_palette();
    const uint8_t *pe = pal >= 0 ? &P14_01252be0[pal * 0x400] : NULL;
    for (int i = 0; i < 256 * 256; i++) {
      uint32_t idx = s[i];
      uint32_t r = idx, g = idx, b = idx;
      if (pe) { b = pe[idx * 4]; g = pe[idx * 4 + 1]; r = pe[idx * 4 + 2]; }
      px[i] = 0xFF000000u | b << 16 | g << 8 | r;
    }
    if (slot + h >= 256) break;
    if (g_tex[slot + h]) plat_tex_free(g_tex[slot + h]);
    g_tex[slot + h] = plat_tex_create(256, 256, px);
    if (g_tex[slot + h]) P86_TexCount++;
  }
}
static void native_texsrc(int32_t tmu, uint32_t addr, int32_t mask, uint32_t info) {
  (void)tmu; (void)addr; (void)mask; (void)info;
  g_bound = P86_NativeHandle(P86_CurTex);
  plat_tex_bind(g_bound);
}
/* _grAlphaTestFunction@4 в native: GR_CMP_ALWAYS (7) — альфа-тест выключен (так рисуется всё непрозрачное,
   в т.ч. асфальт — у его текселей ARGB1555 бит альфы 0), остальные функции — отбрасывание по альфе */
static void native_alpha_test(int32_t fn) { plat_set_render_state(15, fn != 7); }
void P86_NativeInit(void) {
  P33_SetNativeProc("_grAlphaTestFunction@4", (void *)native_alpha_test);
  native_alpha_test(7);                                /* состояние Glide после grSstWinOpen — GR_CMP_ALWAYS */
  P86_TexSrc = native_texsrc;
  P86_CurTex = -1;
  for (int t = 0; t < 6; t++) {
    P84_Handlers[t][20] = (uintptr_t)P86_TexTri;
    P84_Handlers[t][21] = (uintptr_t)P86_TexQuad;
    P84_Handlers[t][22] = (uintptr_t)P86_TexTriD;
    P84_Handlers[t][23] = (uintptr_t)P86_TexQuadD;
    P84_Handlers[t][50] = (uintptr_t)P86_GouraudTri;
    P84_Handlers[t][51] = (uintptr_t)P86_GouraudQuad;
  }
}
#endif
