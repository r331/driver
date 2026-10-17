#include "aspect.h"
#include "reptr.h"
#include "ported85.h"
#include "ported86.h"
#include "../platform/plat.h"
#include <string.h>

GAME_VAR_DEF(p85_vcache_t, P85_VCache, 0x011cffa0)
GAME_VAR_DEF(p85_rv3_t, P85_RV, 0x00b1c290)
GAME_VAR_DEF(p85_raster_fn, P85_RasterA, 0x01270e08)
GAME_VAR_DEF(p85_raster_fn, P85_RasterB, 0x01270dfc)
GAME_VAR_DEF(p85_blend_fn, P85_BlendFn, 0x01270dd0)
GAME_VAR_DEF(p85_state_fn, P85_StateFn, 0x01270ea0)
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P85_StateDirty")
#undef P85_StateDirty
#pragma push_macro("P85_StateDirty") /*gvi*/
#undef P85_StateDirty /*gvi*/
int32_t P85_StateDirty;
#pragma pop_macro("P85_StateDirty") /*gvi*/
#pragma pop_macro("P85_StateDirty")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P85_BlendForce")
#undef P85_BlendForce
#pragma push_macro("P85_BlendForce") /*gvi*/
#undef P85_BlendForce /*gvi*/
int32_t P85_BlendForce;
#pragma pop_macro("P85_BlendForce") /*gvi*/
#pragma pop_macro("P85_BlendForce")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P85_BlendCur")
#undef P85_BlendCur
#pragma push_macro("P85_BlendCur") /*gvi*/
#undef P85_BlendCur /*gvi*/
uint8_t P85_BlendCur;
#pragma pop_macro("P85_BlendCur") /*gvi*/
#pragma pop_macro("P85_BlendCur")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P85_Clip")
#undef P85_Clip
#pragma push_macro("P85_Clip") /*gvi*/
#undef P85_Clip /*gvi*/
uint32_t P85_Clip;
#pragma pop_macro("P85_Clip") /*gvi*/
#pragma pop_macro("P85_Clip")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P85_D")
#undef P85_D
#pragma push_macro("P85_D") /*gvi*/
#undef P85_D /*gvi*/
p85_d_t P85_D;
#pragma pop_macro("P85_D") /*gvi*/
#pragma pop_macro("P85_D")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P85_D3")
#undef P85_D3
#pragma push_macro("P85_D3") /*gvi*/
#undef P85_D3 /*gvi*/
uint32_t P85_D3;
#pragma pop_macro("P85_D3") /*gvi*/
#pragma pop_macro("P85_D3")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P85_MaxX")
#undef P85_MaxX
#pragma push_macro("P85_MaxX") /*gvi*/
#undef P85_MaxX /*gvi*/
float P85_MaxX;
#pragma pop_macro("P85_MaxX") /*gvi*/
#pragma pop_macro("P85_MaxX")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P85_MaxY")
#undef P85_MaxY
#pragma push_macro("P85_MaxY") /*gvi*/
#undef P85_MaxY /*gvi*/
float P85_MaxY;
#pragma pop_macro("P85_MaxY") /*gvi*/
#pragma pop_macro("P85_MaxY")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P85_Tmp")
#undef P85_Tmp
#pragma push_macro("P85_Tmp") /*gvi*/
#undef P85_Tmp /*gvi*/
float P85_Tmp;
#pragma pop_macro("P85_Tmp") /*gvi*/
#pragma pop_macro("P85_Tmp")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P85_ZI")
#undef P85_ZI
#pragma push_macro("P85_ZI") /*gvi*/
#undef P85_ZI /*gvi*/
int32_t P85_ZI;
#pragma pop_macro("P85_ZI") /*gvi*/
#pragma pop_macro("P85_ZI")
#endif

typedef long double ld;
static uint32_t bits(float f) { uint32_t u; memcpy(&u, &f, 4); return u; }

/* 00528ac8 */
void P85_Project(p85_vtx *v) {
  const float *m = P44_MatPtr;
  ld x = v->x, y = v->y, z = v->z;
  ld a = x * m[2] + P44_BiasZ;                     /* x·M2 + смещение Z */
  ld c = x * m[1] + P44_BiasY;                     /* x·M1 + смещение Y */
  ld sx = x * m[0] + (y * m[3] + (z * m[6] + P44_BiasX));
  ld sy = c + (y * m[4] + z * m[7]);
  ld sz = (a + y * m[5]) + z * m[8];
  float fx = (float)sx, fy = (float)sy, fz = (float)sz;
  P85_ZI = (int32_t)lrintl(sz);                    /* fist: округление к ближайшему чётному */
  v->vx = fx; v->vy = fy; v->z = fz;
  v->stamp = P44_XformTag;
  {
    int32_t zi = P85_ZI;
#ifndef RE_HOOK_BUILD
    /* v2.05, отступление native: z вне таблицы 1/z (за камерой или ≥ 0xdbba) — в оригинале такие вершины уходят в набор с
       отсечением (не перенесён); только в игре (вне игры — прежнее поведение тестов города): oow = 0 — P85_CallRaster такой треугольник не рисует (вместо чтения за границей таблицы). */
    if ((zi < 1 || zi >= (int32_t)(sizeof(p12_00ba53a0_t) / sizeof(float))) && re_ptr_has_image()) {
      /* v2.07: ближе z = 1 — метка P85_OOW_NEAR (u·oow остаётся восстановимым), P85_CallRaster отсекает треугольник по z = 1 */
      v->oow = zi < 1 ? P85_OOW_NEAR : 0.0f; v->x = 0; v->y = 0; return; }
#endif
    v->oow = ((const float *)&P12_00ba53a0[0])[zi];
  }
  {
    ld kk = (ld)v->oow * (ld)P43_ScaleA;           /* держится на стеке x87 (расширенная точность) */
    P85_Tmp = (float)(kk * (ld)fx);
    /* дальше x87 работает в 24-битном режиме (после инициализации Glide/D3D): каждая операция округляется до float */
    {
      float px = (float)((ld)P85_Tmp + (ld)P43_OffX);
      float py = (float)((ld)(float)(kk * (ld)fy) + (ld)P43_OffY);
      px = (float)((ld)px - (ld)P43_Half);
      py = (float)((ld)py - (ld)P43_Half);
      v->x = px; v->y = py;
    }
  }
}

/* общие части обработчиков */
p85_vtx *P85_Prep(int32_t idx) {
  p85_vtx *c = &P85_VCache[idx];
  if (c->stamp != P44_XformTag) {
    const float *src = (const float *)((const uint8_t *)P79_PTR(P84_VertRef) + (size_t)idx * 16);
    c->x = src[0]; c->y = src[1]; c->z = src[2];
    P85_Project(c);
  }
  return c;
}
void P85_CallState(void) {
  if (P85_StateDirty != 0) { P85_StateFn(1, 0, 0, 2, 0); P85_StateDirty = 0; }
}
void P85_SetBlend(uint8_t m) {
  if (m != 0 && (uint8_t)P85_BlendForce != 0) m = (uint8_t)P85_BlendForce;
  if (P85_BlendCur != m) {
    switch (m) {
    case 0: P85_BlendFn(4, 0, 4, 0); break;
    case 1: P85_BlendFn(0, 5, 4, 0); break;
    case 2: P85_BlendFn(0, 6, 4, 0); break;
    case 3: P85_BlendFn(4, 4, 4, 0); break;
    default: break;
    }
  }
  P85_BlendCur = m;
}
#ifndef RE_HOOK_BUILD
/* v2.07, отступление native (только игра): отсечение по ближней плоскости z = 1 для обработчиков без отсечения.
   В оригинале такие полигоны рисует набор с отсечением (00436ab0.., не перенесён); до v2.07 треугольник с вершиной ближе z = 1
   пропускался целиком — у камеры пропадали пол и стены (чёрные дыры). P85_PutVtx запоминает координаты камеры вершины;
   новая вершина на z = 1 проецируется как в P85_Project, u/v (хранятся как u·oow) — с учётом перспективы, цвет — линейно. */
static struct { float vx, vy, z, oow, x; int ok; } s_cam[3];
static float near_oow(void) { return ((const float *)&P12_00ba53a0[0])[1]; }
static void near_vtx(p85_rv *o, const p85_rv *a, const p85_rv *b, int ia, int ib) {
  float za = s_cam[ia].z, zb = s_cam[ib].z, t = (1.0f - za) / (zb - za);
  float vx = s_cam[ia].vx + t * (s_cam[ib].vx - s_cam[ia].vx), vy = s_cam[ia].vy + t * (s_cam[ib].vy - s_cam[ia].vy);
  float w = near_oow(), kk = w * P43_ScaleA;
  *o = *a;
  o->r = a->r + t * (b->r - a->r); o->g = a->g + t * (b->g - a->g); o->b = a->b + t * (b->b - a->b);
  o->a = a->a + t * (b->a - a->a); o->z = a->z + t * (b->z - a->z); o->ooz = a->ooz + t * (b->ooz - a->ooz);
  for (int k = 0; k < 2; k++) {
    float ua = a->tmu[k] / a->oow, ub = b->tmu[k] / b->oow;
    o->tmu[k] = (ua + t * (ub - ua)) * w;
  }
  o->oow = w;
  o->x = (kk * vx + P43_OffX) - P43_Half;
  o->y = (kk * vy + P43_OffY) - P43_Half;
}
static int near_clip_raster(void) {
  p85_rv in[3], out[4];
  int n = 0, inside[3], cnt = 0;
  for (int i = 0; i < 3; i++) {
    if (!(s_cam[i].ok && s_cam[i].oow == P85_RV[i].oow && s_cam[i].x == P85_RV[i].x)) return 0;   /* вершина не из P85_PutVtx */
    if (!(P85_RV[i].oow > 0.0f)) return 0;                                                          /* дальняя — пропуск, как в v2.05 */
    inside[i] = P85_RV[i].oow != P85_OOW_NEAR && s_cam[i].z >= 1.0f; cnt += inside[i];
  }
  if (cnt == 0) return 0;
  memcpy(in, P85_RV, sizeof in);
  for (int i = 0; i < 3; i++) {
    int j = (i + 1) % 3;
    if (inside[i]) out[n++] = in[i];
    if (inside[i] != inside[j]) near_vtx(&out[n++], inside[i] ? &in[i] : &in[j], inside[i] ? &in[j] : &in[i], inside[i] ? i : j, inside[i] ? j : i);
  }
  for (int k = 1; k + 1 < n; k++) {
    P85_RV[0] = out[0]; P85_RV[1] = out[k]; P85_RV[2] = out[k + 1];
    if ((uint8_t)P82_Edge == 0) P85_RasterA(&P85_RV[0], &P85_RV[1], &P85_RV[2]);
    else P85_RasterB(&P85_RV[0], &P85_RV[1], &P85_RV[2]);
  }
  memcpy(P85_RV, in, sizeof in);   /* обработчик четырёхугольника использует RV[0], RV[1] повторно */
  return 1;
}
#endif
void P85_CallRaster(void) {
#ifndef RE_HOOK_BUILD
  if (re_ptr_has_image() && (!(P85_RV[0].oow > 0.0f) || !(P85_RV[1].oow > 0.0f) || !(P85_RV[2].oow > 0.0f) ||
      P85_RV[0].oow == P85_OOW_NEAR || P85_RV[1].oow == P85_OOW_NEAR || P85_RV[2].oow == P85_OOW_NEAR)) {   /* v2.05/v2.07: только игра, см. P85_Project */
    (void)near_clip_raster();
    return;
  }
#endif
  if ((uint8_t)P82_Edge == 0) P85_RasterA(&P85_RV[0], &P85_RV[1], &P85_RV[2]);
  else P85_RasterB(&P85_RV[0], &P85_RV[1], &P85_RV[2]);
}
/* отсечение при P82_Edge≠0: 1 — треугольник/четырёхугольник пропускается */
int P85_EdgeReject(const p85_vtx *const *vs, int n) {
  uint32_t a = 0x80000000u;
#ifndef RE_HOOK_BUILD
  const int ex = re_view_extra();   /* v2.15 Hor+: экран по x — [−S, 639 + S] */
  if (ex > 0) {
    for (int i = 0; i < n; i++) a &= bits(vs[i]->x + (float)ex);
    P85_Clip = a; if (a) return 1;
    a = 0x80000000u;
    for (int i = 0; i < n; i++) a &= bits(vs[i]->y);
    P85_Clip = a; if (a) return 1;
    uint32_t o = 0;
    for (int i = 0; i < n; i++) { float d = (float)((ld)vs[i]->x - (ld)P85_MaxX - (ld)ex); uint32_t u = bits(d); if (i < 3) P85_D[i] = u; else P85_D3 = u; o |= u; }
    P85_Clip = o; if (o == 0) return 1;
    o = 0;
    for (int i = 0; i < n; i++) { float d = (float)((ld)vs[i]->y - (ld)P85_MaxY); uint32_t u = bits(d); if (i < 3) P85_D[i] = u; else P85_D3 = u; o |= u; }
    P85_Clip = o; if (o == 0) return 1;
    return 0;
  }
#endif
  for (int i = 0; i < n; i++) a &= bits(vs[i]->x);
  P85_Clip = a; if (a) return 1;
  a = 0x80000000u;
  for (int i = 0; i < n; i++) a &= bits(vs[i]->y);
  P85_Clip = a; if (a) return 1;
  {
    uint32_t o = 0;
    for (int i = 0; i < n; i++) { float d = (float)((ld)vs[i]->x - (ld)P85_MaxX); uint32_t u = bits(d); if (i < 3) P85_D[i] = u; else P85_D3 = u; o |= u; }
    P85_Clip = o; if (o == 0) return 1;
    o = 0;
    for (int i = 0; i < n; i++) { float d = (float)((ld)vs[i]->y - (ld)P85_MaxY); uint32_t u = bits(d); if (i < 3) P85_D[i] = u; else P85_D3 = u; o |= u; }
    P85_Clip = o; if (o == 0) return 1;
  }
  return 0;
}
void P85_PutVtx(p85_rv *r, const p85_vtx *v) {
  r->x = v->x; r->y = v->y; r->oow = v->oow;
#ifndef RE_HOOK_BUILD
  { ptrdiff_t i = r - &P85_RV[0]; if (i >= 0 && i < 3) { s_cam[i].vx = v->vx; s_cam[i].vy = v->vy; s_cam[i].z = v->z; s_cam[i].oow = v->oow; s_cam[i].x = v->x; s_cam[i].ok = 1; } }
#endif
}
/* цвет записи → r,g,b трёх вершин; lit: умножается на освещённость плоскости (P84_LightIn[номер], как fmul → fstp во float) */
static void put_color(const uint8_t *rec, int off, int lit) {
  float k = lit ? P84_LightIn[*(const int32_t *)(rec + 4)] : 1.0f;
  for (int i = 0; i < 3; i++) {
    float c; memcpy(&c, rec + off + 4 * i, 4);
    if (lit) c = (float)((ld)k * (ld)c);
    (&P85_RV[0].r)[i] = c; (&P85_RV[1].r)[i] = c; (&P85_RV[2].r)[i] = c;
  }
}

static void do_tri(uint32_t arg, int lit) {
  const uint8_t *rec = G2_011F4064;
  int32_t i0 = *(const int32_t *)(rec + 8), i1 = *(const int32_t *)(rec + 0xc), i2 = *(const int32_t *)(rec + 0x10);
  G2_011F4064 = (uint8_t *)rec + 0x20;
  p85_vtx *v0 = P85_Prep(i0), *v1 = P85_Prep(i1), *v2 = P85_Prep(i2);
  if ((uint8_t)P82_Edge) { const p85_vtx *vs[3] = { v0, v1, v2 }; if (P85_EdgeReject(vs, 3)) return; }
  put_color(rec, 0x14, lit);
  P85_CallState();
  P85_SetBlend((uint8_t)arg);
  P85_PutVtx(&P85_RV[0], v0); P85_PutVtx(&P85_RV[1], v1); P85_PutVtx(&P85_RV[2], v2);
  P85_CallRaster();
}
static void do_quad(uint32_t arg, int lit) {
  const uint8_t *rec = G2_011F4064;
  int32_t i0 = *(const int32_t *)(rec + 8), i1 = *(const int32_t *)(rec + 0xc), i2 = *(const int32_t *)(rec + 0x10), i3 = *(const int32_t *)(rec + 0x14);
  G2_011F4064 = (uint8_t *)rec + 0x24;
  p85_vtx *v0 = P85_Prep(i0), *v1 = P85_Prep(i1), *v2 = P85_Prep(i2), *v3 = P85_Prep(i3);
  if ((uint8_t)P82_Edge) { const p85_vtx *vs[4] = { v0, v1, v2, v3 }; if (P85_EdgeReject(vs, 4)) return; }
  put_color(rec, 0x18, lit);
  P85_CallState();
  P85_SetBlend((uint8_t)arg);
  P85_PutVtx(&P85_RV[0], v0); P85_PutVtx(&P85_RV[1], v2); P85_PutVtx(&P85_RV[2], v1);
  P85_CallRaster();
  P85_PutVtx(&P85_RV[2], v3);
  P85_CallRaster();
}
/* 0042f7d9 */
void P85_FlatTri(uint32_t arg) { do_tri(arg, 0); }
/* 0042fc29 */
void P85_FlatQuad(uint32_t arg) { do_quad(arg, 0); }
/* 00432186 */
void P85_LitTri(uint32_t arg) { do_tri(arg, 1); }
/* 00432601 */
void P85_LitQuad(uint32_t arg) { do_quad(arg, 1); }

#ifndef RE_HOOK_BUILD
int32_t P85_Tris;
int32_t P85_TrisBy[4];
uint8_t P85_LastBlend;
static int g_blend_mode;
static int g_textured;
static void P85_STD native_blend(int32_t a, int32_t b, int32_t c, int32_t d) {
  (void)c; (void)d;
  if (a == 4 && b == 0) { g_blend_mode = 0; plat_set_blend(0, 0, 0); }
  else if (a == 4 && b == 4) { g_blend_mode = 3; plat_set_blend(1, 2, 2); }   /* ONE, ONE: сложение */
  else if (a == 0 && b == 5) { g_blend_mode = 1; plat_set_blend(1, 1, 6); }   /* ZERO, ONE_MINUS_SRC_ALPHA: затемнение по альфе (v1.41) */
  else if (a == 0 && b == 6) { g_blend_mode = 2; plat_set_blend(1, 1, 4); }   /* ZERO, ONE_MINUS_SRC_COLOR: затемнение по цвету (v1.41) */
  else { g_blend_mode = 2; plat_set_blend(0, 0, 0); }                          /* прочие сочетания — непрозрачно */
  P85_LastBlend = (uint8_t)g_blend_mode;
}
static void P85_STD native_state(int32_t a, int32_t b, int32_t c, int32_t d, int32_t e) {
  (void)b; (void)c; (void)d; (void)e;
  g_textured = a == 3;                                  /* 3 — текстура + цвет, 1 — только цвет */
  plat_tex_bind(g_textured ? P86_NativeHandle(P86_CurTex) : 0);
}
static uint32_t col8(float f) { int i = (int)lrintf(f); return (uint32_t)(i < 0 ? 0 : i > 255 ? 255 : i); }
/* Glide GrVertex → plat_vertex; цвета 0..255, глубина из oow (больше oow — ближе) */
static void P85_STD native_raster(const p85_rv *a, const p85_rv *b, const p85_rv *c) {
  const p85_rv *vs[3] = { a, b, c };
  plat_vertex pv[3];
  for (int i = 0; i < 3; i++) {
    const p85_rv *r = vs[i];
    float oow = r->oow < 0 ? 0 : r->oow;
    pv[i].x = r->x; pv[i].y = r->y; pv[i].z = 1.0f / (1.0f + oow); pv[i].rhw = oow > 1e-7f ? oow : 1e-7f;
    pv[i].color = 0xFF000000u | col8(r->r) << 16 | col8(r->g) << 8 | col8(r->b);
    pv[i].specular = 0; pv[i].u = 0; pv[i].v = 0;
    if (g_textured && oow > 1e-7f) { pv[i].u = r->tmu[0] / oow / 256.0f; pv[i].v = r->tmu[1] / oow / 256.0f; }
  }
  P85_Tris++; P85_TrisBy[g_blend_mode & 3]++;
  plat_draw_tris(pv, 3);
}
void P85_SkipRecord(uint32_t arg) {
  (void)arg;
  G2_011F4064 += G2_TABLE_00550ACC[G2_011F4064[0]];
}
void P85_RegisterNative(void) {
  for (int t = 0; t < 6; t++) {
    for (int k = 0; k < 56; k++) {
      uintptr_t f = (uintptr_t)P85_SkipRecord;
      if (k == 0 || k == 32) f = (uintptr_t)P85_FlatTri;
      else if (k == 1 || k == 33) f = (uintptr_t)P85_FlatQuad;
      else if (k == 16 || k == 48) f = (uintptr_t)P85_LitTri;
      else if (k == 17 || k == 49) f = (uintptr_t)P85_LitQuad;
      else if (!G2_TABLE_00550ACC[k]) continue;
      P84_Handlers[t][k] = f;
    }
  }
  P85_RasterA = P85_RasterB = native_raster;
  P85_BlendFn = native_blend;
  P85_StateFn = native_state;
  P86_NativeInit();
}
void P85_InitConsts(void) {
  P85_MaxX = 639.0f; P85_MaxY = 479.0f;
}
#else
void P85_InitConsts(void) {}
#endif
