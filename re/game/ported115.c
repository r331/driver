/* v1.60 (см. ported115.h). */
#include "ported115.h"
#include "cartab.h"
#include "reptr.h"
#include "ported5.h"
#include "ported6.h"
#include "ported8.h"
#include "ported12.h"
#include "ported14.h"
#include "ported16.h"
#include "ported19.h"
#include "ported33.h"
#include "ported43.h"
#include "ported44.h"
#include "ported48.h"
#include "ported55.h"
#include "ported56.h"
#include "ported59.h"
#include "ported62.h"
#include "ported65.h"
#include "ported76.h"
#include "ported79.h"
#include "ported80.h"
#include "ported82.h"
#include "ported84.h"
#include "ported86.h"
#include "ported96.h"
#include "ported97.h"
#include "ported98.h"
#include "ported101.h"
#include "ported102.h"
#include "ported107.h"
#include "ported110.h"
#include "ported112.h"
#include "ported114.h"
#include "globalsets.h"
#include "smallfuncs.h"
#include "uihandlers3.h"
#include <string.h>

GAME_VAR_DEF(p85_raster_fn, P115_RasterC, 0x01270e30)
GAME_VAR_DEF(p85_raster_fn, P115_RasterD, 0x01270d9c)
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P115_TgtOn")
#undef P115_TgtOn
#pragma push_macro("P115_TgtOn") /*gvi*/
#undef P115_TgtOn /*gvi*/
int32_t P115_TgtOn;
#pragma pop_macro("P115_TgtOn") /*gvi*/
#pragma pop_macro("P115_TgtOn")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P115_Tgt")
#undef P115_Tgt
#pragma push_macro("P115_Tgt") /*gvi*/
#undef P115_Tgt /*gvi*/
p115_i4_t P115_Tgt;
#pragma pop_macro("P115_Tgt") /*gvi*/
#pragma pop_macro("P115_Tgt")
#endif

static int32_t rd32(const void *p) { int32_t v; memcpy(&v, p, 4); return v; }
static float rdf(const void *p) { float v; memcpy(&v, p, 4); return v; }
static void wrf(void *p, float v) { memcpy(p, &v, 4); }
static float f_of(int32_t i) { float f; memcpy(&f, &i, 4); return f; }
static int32_t i_of(float f) { int32_t i; memcpy(&i, &f, 4); return i; }
#ifdef RE_HOOK_BUILD
#  define P115_STD __attribute__((stdcall))
#else
#  define P115_STD
#endif
static void *glide_proc(const char *name) {
  for (int i = 0; i < P33_GlideCount(); i++)
    if (strcmp(P33_GlideName(i), name) == 0) return P33_GlideProc(i);
  return NULL;
}
static void poly_list(int32_t n, const void *v) {
  void (P115_STD *f)(int32_t, const void *) = (void (P115_STD *)(int32_t, const void *))glide_proc("_grDrawPolygonVertexList@8");
  if (f != NULL) f(n, v);
}
static void state4(void) {
  if (P85_StateDirty != 4) { if (P85_StateFn) P85_StateFn(3, 1, 0, 1, 0); P85_StateDirty = 4; }
}
/* смешивание значков: режим 3 — (4,4,0,0), в отличие от P85_SetBlend */
static void blend_icon(uint8_t m) {
  static const int32_t t[4][4] = { { 4, 0, 4, 0 }, { 0, 5, 4, 0 }, { 0, 6, 4, 0 }, { 4, 4, 0, 0 } };
  if (m > 3 || P85_BlendCur == m) return;
  if (P85_BlendFn) P85_BlendFn(t[m][0], t[m][1], t[m][2], t[m][3]);
  P85_BlendCur = m;
}
static void tex_page(int32_t tex) {
  if (tex != P86_CurTex) {
    P86_CurTex = tex;
#ifndef RE_HOOK_BUILD
    if (tex < 0 || tex >= 0x100) return;
#endif
    if (P86_TexSrc) P86_TexSrc(0, (uint32_t)rd32(&P12_01145a60[tex * 0x10 + 8]), 3, (uint32_t)rd32(&P12_01145a60[tex * 0x10 + 0xc]));
  }
}
/* четыре GrVertex по 60 байт: x,y,z,r,g,b,ooz,a,oow,s,t */
typedef float p115_gv[15];
static void put_v(float *v, float x, float y, float r, float g, float b, float a, float oow, float s, float t) {
  v[0] = x; v[1] = y; v[3] = r; v[4] = g; v[5] = b; v[7] = a; v[8] = oow; v[9] = s; v[10] = t;
}

/* ---- 00418e70: значок в координатах 640×480 × P110_IconKX/KY, uv × oow; flip — зеркально по u ---- */
void P115_IconAt(float x, float y, uint32_t icon, int32_t r, int32_t g, int32_t b, int32_t flip, int32_t mode) {
  const uint8_t *ic = (const uint8_t *)re_ptr(icon);
#ifndef RE_HOOK_BUILD
  if (ic == NULL) return;
#endif
  float k = (P55_BDFA18 == 0) ? 0.015625f : 1.0f;
  float cr = (float)(uint8_t)r * P19_Cur, cg = (float)(uint8_t)g * P19_Cur, cb = (float)(uint8_t)b * P19_Cur;
  float u0 = (float)ic[9] + P80_Half, v0 = (float)ic[10] + P80_Half;
  float w = (float)ic[0xb] - P80_Half, h = (float)ic[0xc] - P80_Half;
  float x0 = x * P110_IconKX, y0 = y * P110_IconKY, sw = w * P110_IconKX, sh = h * P110_IconKY;
  state4();
  blend_icon((uint8_t)mode);
  if ((int32_t)ic[8] != P86_CurTex) {
    P86_CurTex = ic[8];
    if (P86_TexSrc) P86_TexSrc(0, (uint32_t)rd32(&P12_01145a60[(uint32_t)ic[8] * 0x10 + 8]), 3, (uint32_t)rd32(&P12_01145a60[(uint32_t)ic[8] * 0x10 + 0xc]));
  }
  float ua = u0, ub = u0 + w;
  if ((int8_t)flip != 0) { ua = u0 + w; ub = u0; }
  p115_gv v[4];
  memset(v, 0, sizeof v);
  put_v(v[0], x0, y0, cr, cg, cb, 255.0f, k, ua * k, v0 * k);
  put_v(v[1], x0 + sw, y0, cr, cg, cb, 255.0f, k, ub * k, v0 * k);
  put_v(v[2], x0 + sw, y0 + sh, cr, cg, cb, 255.0f, k, ub * k, (v0 + h) * k);
  put_v(v[3], x0, y0 + sh, cr, cg, cb, 255.0f, k, ua * k, (v0 + h) * k);
  poly_list(4, v);
}

/* экранные координаты: (x·ScrW/640 − ScrW/2)·Scale + ScrW/2 */
static void scr_xy(float x, float y, float *sx, float *sy, float *kx, float *ky) {
  *kx = (float)P19_ScrW / P19_DivW;
  *ky = (float)P19_ScrH / P19_DivH;
  *sx = (x * *kx - (float)(P19_ScrW >> 1)) * P19_Scale + (float)(P19_ScrW >> 1);
  *sy = (y * *ky - (float)(P19_ScrH >> 1)) * P19_Scale + (float)(P19_ScrH >> 1);
}
static void icon_scr(float x, float y, float mx, float my, const uint8_t *ic, int32_t r, int32_t g, int32_t b, int32_t flip, int32_t mode) {
  float kx, ky, sx, sy;
  scr_xy(x, y, &sx, &sy, &kx, &ky);
  float u0 = (float)ic[9] + P80_Half, v0 = (float)ic[10] + P80_Half;
  float w = (float)ic[0xb] * mx - P80_Half, h = (float)ic[0xc] * my - P80_Half;   /* 0051084d: mx = my = 1 — без умножения, тот же результат */
  float sw = w * kx * P19_Scale, sh = h * ky * P19_Scale;
  state4();
  blend_icon((uint8_t)mode);
  if ((int32_t)ic[8] != P86_CurTex) {
    P86_CurTex = ic[8];
    if (P86_TexSrc) P86_TexSrc(0, (uint32_t)rd32(&P12_01145a60[(uint32_t)ic[8] * 0x10 + 8]), 3, (uint32_t)rd32(&P12_01145a60[(uint32_t)ic[8] * 0x10 + 0xc]));
  }
  float ua = u0, ub = u0 + w;
  if ((int8_t)flip != 0) { ua = u0 + w; ub = u0; }
  float cr = (float)(uint8_t)r, cg = (float)(uint8_t)g, cb = (float)(uint8_t)b;
  p115_gv v[4];
  memset(v, 0, sizeof v);
  put_v(v[0], sx, sy, cr, cg, cb, 255.0f, 1.0f, ua, v0);
  put_v(v[1], sx + sw, sy, cr, cg, cb, 255.0f, 1.0f, ub, v0);
  put_v(v[2], sx + sw, sy + sh, cr, cg, cb, 255.0f, 1.0f, ub, v0 + h);
  put_v(v[3], sx, sy + sh, cr, cg, cb, 255.0f, 1.0f, ua, v0 + h);
  poly_list(4, v);
}
/* ---- 00510e1d: значок в масштабе экрана с множителями размера sx, sy (oow = 1, uv в текселях) ---- */
void P115_IconScaled(float x, float y, float sx, float sy, uint32_t icon, int32_t r, int32_t g, int32_t b, int32_t mode) {
  const uint8_t *ic = (const uint8_t *)re_ptr(icon);
#ifndef RE_HOOK_BUILD
  if (ic == NULL) return;
#endif
  icon_scr(x, y, sx, sy, ic, r, g, b, 0, mode);
}
/* ---- 0051084d: то же без масштаба, flip — зеркально по u ---- */
void P115_IconFlip(float x, float y, uint32_t icon, int32_t r, int32_t g, int32_t b, int32_t flip, int32_t mode) {
  const uint8_t *ic = (const uint8_t *)re_ptr(icon);
#ifndef RE_HOOK_BUILD
  if (ic == NULL) return;
#endif
  icon_scr(x, y, 1.0f, 1.0f, ic, r, g, b, flip, mode);
}

/* ---- 0048d4e0: стрелка стороны дороги в точке pos (−5 по y, 750/300 по сторонам), пурпурная, P85_RasterB ---- */
void P115_RoadArrow(const float *pos) {
  if (P85_StateDirty != 0) { if (P85_StateFn) P85_StateFn(1, 0, 0, 2, 0); P85_StateDirty = 0; }
  if (P85_BlendCur != 0) { if (P85_BlendFn) P85_BlendFn(4, 0, 4, 0); P85_BlendCur = 0; }
#ifndef RE_HOOK_BUILD
  if (pos == NULL) return;
#endif
  int32_t side = P102_RoadSide(pos[0], pos[2]);
  if (side == -1) return;
  static const float tab[4][6] = {          /* a(x,z), b(x,z), c(x,z) */
    { 0.0f, 750.0f, 300.0f, -750.0f, -300.0f, -750.0f },
    { 750.0f, 0.0f, -750.0f, -300.0f, -750.0f, 300.0f },
    { 0.0f, -750.0f, 300.0f, 750.0f, -300.0f, 750.0f },
    { -750.0f, 0.0f, 750.0f, -300.0f, 750.0f, 300.0f } };
  if (side < 0 || side > 3) return;        /* в оригинале — неинициализированные смещения */
  float p[3] = { pos[0] - P44_CamX, pos[1] - P44_CamY, pos[2] - P44_CamZ };
  P44_Xform(p);
  float q[3][3];
  for (int i = 0; i < 3; i++) {
    q[i][0] = tab[side][i * 2]; q[i][1] = -5.0f; q[i][2] = tab[side][i * 2 + 1];
    P44_Xform(q[i]);
    q[i][0] += p[0]; q[i][1] += p[1]; q[i][2] += p[2];
  }
  if (!(q[0][2] >= P8_00546024 && q[1][2] >= P8_00546024 && q[2][2] >= P8_00546024)) return;
  p85_rv rv[3];
  memset(rv, 0, sizeof rv);
  for (int i = 0; i < 3; i++) {
    int32_t zi = (int32_t)q[i][2];                                 /* __ftol */
#ifndef RE_HOOK_BUILD
    if (zi < 0 || zi >= (int32_t)(RE_OOW_N)) return;
#endif
    float oow = RE_OOW(zi);
    float k = oow * P43_ScaleA;
    rv[i].x = (q[i][0] * k + P43_OffX) - P43_Half;
    rv[i].y = (q[i][1] * k + P43_OffY) - P43_Half;
    rv[i].oow = oow;
    rv[i].r = 255.0f; rv[i].g = 0.0f; rv[i].b = 255.0f;
  }
  if (P85_RasterB) P85_RasterB(&rv[0], &rv[1], &rv[2]);
  P85_StateDirty = -1;
}

/* ---- записи модели с растеризатором 01270e30 / 01270d9c ---- */
static p85_vtx *prep(int32_t idx) {
  p85_vtx *c = &P85_VCache[idx];
  if (!P85_VC_VALID(c, P85_FMT_BIAS)) {
    const float *src = (const float *)((const uint8_t *)P79_PTR(P84_VertRef) + (size_t)idx * 16);
    c->x = src[0]; c->y = src[1]; c->z = src[2];
    P101_ProjT((float *)c);
#ifndef RE_HOOK_BUILD
    /* v2.23, только игра: z вне таблицы 1/z — метки как у P85_Project (ближе z = 1 — P85_OOW_NEAR, x = y = 0; дальше — oow 0).
       Без них P101_ProjT давал oow 0 и центр экрана (320, 240), а запись того же кадра от P85_Project — (0, 0) с oow 1e−30. */
    if ((P85_ZI < 1 || P85_ZI >= (int32_t)(RE_OOW_N)) && re_ptr_has_image()) { c->oow = P85_ZI < 1 ? P85_OOW_NEAR : 0.0f; c->x = 0; c->y = 0; }
#endif
    P85_VC_FMT(c, P85_FMT_PROJ);
  }
  return c;
}
/* v2.23, отступление native: в наборе с ближней плоскостью (режим 1) типы 0..3 не перенесены (00459b21..), вместо них стоят эти
   обработчики режима 0 — вершины за камерой (метки P85_OOW_NEAR / oow 0, экран (0,0) / (320,240)) уходили в растеризатор как есть:
   треугольник от левого верхнего угла/центра на дальней плоскости — серый полигон поверх неба (виден там, где ничего ближе нет).
   Теперь — как P85_CallRaster: целиком за камерой — пропуск, пересекающий z = 1 — отсечение (P85_CallRasterWith). */
static void raster_c(void) {
#ifndef RE_HOOK_BUILD
  P85_CallRasterWith(P115_RasterC, P115_RasterD);
#else
  p85_raster_fn f = ((uint8_t)P82_Edge == 0) ? P115_RasterC : P115_RasterD;
  if (f) f(&P85_RV[0], &P85_RV[1], &P85_RV[2]);
#endif
}
static void put_xyz(p85_rv *r, const p85_vtx *v) {
  r->x = v->x; r->y = v->y; r->z = v->z; r->oow = v->oow;
#ifndef RE_HOOK_BUILD
  P85_NoteCam((int)(r - &P85_RV[0]), v);
#endif
}
static void put_rgb(p85_rv *r, const uint8_t *c) { r->r = rdf(c); r->g = rdf(c + 4); r->b = rdf(c + 8); }
static void tri_c(uint32_t arg, uint32_t size, int gouraud) {
  const uint8_t *rec = G2_011F4064;
  int32_t i0 = rd32(rec + 8), i1 = rd32(rec + 0xc), i2 = rd32(rec + 0x10);
  G2_011F4064 = (uint8_t *)rec + size;
#ifndef RE_HOOK_BUILD
  if ((uint32_t)i0 >= 0x2000u || (uint32_t)i1 >= 0x2000u || (uint32_t)i2 >= 0x2000u) return;
#endif
  p85_vtx *v0 = prep(i0), *v1 = prep(i1), *v2 = prep(i2);
  if ((uint8_t)P82_Edge) { const p85_vtx *vs[3] = { v0, v1, v2 }; if (P85_EdgeReject(vs, 3)) return; }
  for (int i = 0; i < 3; i++) put_rgb(&P85_RV[i], rec + 0x14 + (gouraud ? 0xc * i : 0));
  if (P85_StateDirty != 0) { if (P85_StateFn) P85_StateFn(1, 0, 0, 2, 0); P85_StateDirty = 0; }
  if (P85_BlendFn) P85_SetBlend((uint8_t)arg); else { uint8_t m = (uint8_t)arg; if (m != 0 && (uint8_t)P85_BlendForce != 0) m = (uint8_t)P85_BlendForce; P85_BlendCur = m; }
  put_xyz(&P85_RV[0], v0); put_xyz(&P85_RV[1], v1); put_xyz(&P85_RV[2], v2);
  raster_c();
}
static void quad_c(uint32_t arg, uint32_t size, int gouraud) {
  const uint8_t *rec = G2_011F4064;
  int32_t i0 = rd32(rec + 8), i1 = rd32(rec + 0xc), i2 = rd32(rec + 0x10), i3 = rd32(rec + 0x14);
  G2_011F4064 = (uint8_t *)rec + size;
#ifndef RE_HOOK_BUILD
  if ((uint32_t)i0 >= 0x2000u || (uint32_t)i1 >= 0x2000u || (uint32_t)i2 >= 0x2000u || (uint32_t)i3 >= 0x2000u) return;
#endif
  p85_vtx *v0 = prep(i0), *v1 = prep(i1), *v2 = prep(i2), *v3 = prep(i3);
  if ((uint8_t)P82_Edge) { const p85_vtx *vs[4] = { v0, v1, v2, v3 }; if (P85_EdgeReject(vs, 4)) return; }
  for (int i = 0; i < 3; i++) put_rgb(&P85_RV[i], rec + 0x18 + (gouraud ? 0xc * i : 0));   /* цвет четвёртой вершины не используется */
  if (P85_StateDirty != 0) { if (P85_StateFn) P85_StateFn(1, 0, 0, 2, 0); P85_StateDirty = 0; }
  if (P85_BlendFn) P85_SetBlend((uint8_t)arg); else { uint8_t m = (uint8_t)arg; if (m != 0 && (uint8_t)P85_BlendForce != 0) m = (uint8_t)P85_BlendForce; P85_BlendCur = m; }
  put_xyz(&P85_RV[0], v0); put_xyz(&P85_RV[1], v2); put_xyz(&P85_RV[2], v1);
  raster_c();
  put_xyz(&P85_RV[2], v3);
  raster_c();
}
void P115_FlatTriC(uint32_t arg) { tri_c(arg, 0x20, 0); }
void P115_GouraudTriC(uint32_t arg) { tri_c(arg, 0x38, 1); }
void P115_FlatQuadC(uint32_t arg) { quad_c(arg, 0x24, 0); }
void P115_GouraudQuadC(uint32_t arg) { quad_c(arg, 0x48, 1); }

/* ---- 0040b286: значок (u,v, tw×th текселей) в (x,y) с масштабом sx,sy; смешивание по 005d77c0: 4 — режим 3, 8 — альфа 128
        (вершина 0) + grAlphaCombine, 0x10 — режим 2, иначе 0; без 3D (005f7e58) — спрайт в буфер (__ftol — усечение) ---- */
void P115_IconDraw(float x, float y, float sx, float sy, float u, float vv, float tw, float th, int32_t page, const uint8_t *rgb) {
  if (P56_F7E58 != 0) {
    if ((G005D77C0 & 8) == 0) P65_SpriteKeyed((int32_t)x, (int32_t)y, page, (int32_t)u, (int32_t)vv, (int32_t)tw, (int32_t)th);
    else P65_SpriteBlend((int32_t)x, (int32_t)y, page, (int32_t)u, (int32_t)vv, (int32_t)tw, (int32_t)th);
    return;
  }
#ifndef RE_HOOK_BUILD
  if (rgb == NULL) return;
#endif
  float k = (P55_BDFA18 == 0) ? 0.015625f : 1.0f, c = f_of((int32_t)P56_AA30);   /* .data 0054aa30 = 0.5 */
  u = u + c; vv = vv + c; tw = tw - c; th = th - c;
  float cr = (float)rgb[0], cg = (float)rgb[1], cb = (float)rgb[2];
  p115_gv v[4];
  memset(v, 0, sizeof v);
  put_v(v[0], x, y, cr, cg, cb, 255.0f, k, u * k, vv * k);
  put_v(v[1], tw * sx + x, y, cr, cg, cb, 255.0f, k, (u + tw) * k, vv * k);
  put_v(v[2], tw * sx + x, th * sy + y, cr, cg, cb, 255.0f, k, (u + tw) * k, (vv + th) * k);
  put_v(v[3], x, th * sy + y, cr, cg, cb, 255.0f, k, u * k, (vv + th) * k);
  tex_page(page);
  state4();
  if ((G005D77C0 & 4) != 0) blend_icon(3);
  else if ((G005D77C0 & 8) != 0) {
    v[0][7] = 128.0f;
    if (P85_BlendFn) P85_BlendFn(1, 5, 4, 0);
    if (P97_GrAlpha) P97_GrAlpha(3, 1, 0, 2, 0);
    P62_I252B78 = 0x80;
    P85_BlendCur = 0x80;
  } else if ((G005D77C0 & 0x10) != 0) blend_icon(2);
  else blend_icon(0);
  poly_list(4, v);
}

/* ---- 00523829: такт звукового драйвера ---- */
typedef void (*p115_f6)(float, float, float, float, float, float);
typedef void (*p115_f3)(float, float, float);
typedef void (*p115_fi3)(int32_t, float, float, float);
typedef void (*p115_fii)(int32_t, int32_t);
typedef int32_t (*p115_rii)(int32_t, int32_t);
typedef void (*p115_fip)(int32_t, uint32_t *);
void P115_SndUpdate(void) {
  if (G6_00B91CF4 == 0 || G00575F40 == 0) return;
  if (P43_FadeOn != 0) {
    if (P43_FadeSteps == 0) return;
    P43_FadeSteps--;
    float fb = f_of(P43_FadeB);                                  /* 00b91d24 — float-биты */
    if (P43_FadeSteps == 0) P43_FadeA = fb;
    else if (P43_FadeA <= fb) P43_FadeA = P43_FadeA + P43_FadeStep;
    else P43_FadeA = P43_FadeA - P43_FadeStep;
    P48_SetMasterVolume(P43_FadeA);
  }
  P8_00b91c14 = P8_00b91c08; P8_00b91c18 = P8_00b91c0c; P8_00b91c1c = P8_00b91c10;   /* позиция слушателя (float-биты) */
  P8_00b91c08 = i_of(P44_CamX); P8_00b91c0c = i_of(P44_CamY); P8_00b91c10 = i_of(P44_CamZ);
  const float *m = P44_ViewMatT;
  if (P97_DrvE) ((p115_f6)P97_DrvE)(m[2], m[5], m[8], m[1], m[4], m[7]);
  float cx = f_of(P8_00b91c08), cy = f_of(P8_00b91c0c), cz = f_of(P8_00b91c10);
  if (P97_DrvD) ((p115_f3)P97_DrvD)(cx, cy, cz);
  if (Q00B87E94 != 0 && P48_Drv38)
    ((p115_f3)(re_fn_t)P48_Drv38)(cx - f_of(P8_00b91c14), cy - f_of(P8_00b91c18), cz - f_of(P8_00b91c1c));
  for (int32_t i = 0; i < 0x14; i++) {
    uint8_t *s = &S_00BDC2A0[i * 0x34];
    if ((s[0] & 1) != 0) {
      uint32_t st = 0;
      if (P97_DrvL) ((p115_fip)P97_DrvL)(i, &st);
      if ((st & 1) == 0) { P48_FreeVoice(i); continue; }
    }
    if ((s[0] & 0x20) != 0) {
      memcpy(s + 0x10, s + 4, 0xc);                                /* прежняя позиция */
      const int32_t *src = (const int32_t *)re_ptr((uint32_t)rd32(s + 0x1c));
#ifndef RE_HOOK_BUILD
      if (src != NULL)
#endif
      { wrf(s + 4, (float)src[0]); wrf(s + 8, (float)-src[1]); wrf(s + 0xc, (float)src[2]); }
      s[0] |= 2;
#ifndef RE_HOOK_BUILD
      if (i == 2) { static int k; const char *e = getenv("RE_HORNDBG"); if (e && (k++ % (atoi(e) > 0 ? atoi(e) : 50)) == 0)
        fprintf(stderr, "[horn] 3D ptr %08x → %p pos %.0f %.0f %.0f; P99_Cars[0].pos %p = %d %d\n", (unsigned)rd32(s + 0x1c), (const void *)src, rdf(s + 4), rdf(s + 8), rdf(s + 0xc), (void *)&P99_Cars[0].pos[0], (int)P99_Cars[0].pos[0], (int)P99_Cars[0].pos[2]); }
#endif
    }
    if ((s[0] & 4) != 0) {
      if (P97_DrvI) ((p115_fii)P97_DrvI)(i, rd32(s + 0x28));
      s[0] &= 0xfb;
    }
    if ((s[0] & 8) != 0) {
      int16_t vol; memcpy(&vol, s + 0x2e, 2);
      if (P97_DrvH) ((p115_fii)P97_DrvH)(i, (int32_t)vol);
      s[0] &= 0xf7;
    }
    if ((s[0] & 2) != 0) {
      if (P97_DrvJ) ((p115_fi3)P97_DrvJ)(i, rdf(s + 4), rdf(s + 8), rdf(s + 0xc));
      if (Q00B87E94 != 0 && P48_Drv54)
        ((p115_fi3)(re_fn_t)P48_Drv54)(i, rdf(s + 4) - rdf(s + 0x10), rdf(s + 8) - rdf(s + 0x14), rdf(s + 0xc) - rdf(s + 0x18));
      s[0] &= 0xfd;
    }
    if ((s[0] & 0x10) != 0) {
      int32_t ok = P97_DrvF ? ((p115_rii)P97_DrvF)(i, rd32(s + 0x20)) : 0;
      if (ok == 0) P48_FreeVoice(i);
      else { s[0] &= 0xef; s[0] |= 1; }
    }
  }
  if (P48_Drv0C) P48_Drv0C();
  if (P48_Drv08) P48_Drv08();
}

/* ---- 004a3808: такт объекта-цели ---- */
void P115_TargetTick(uint8_t *o) {
#ifndef RE_HOOK_BUILD
  if (o == NULL) return;
#endif
  uint32_t fl = (uint32_t)rd32(o + 0x10);
  if (fl == 0) return;
  int32_t on = (fl & 0x200) != 0;
  if (on) for (int i = 0; i < 4; i++) P115_Tgt[i] = rd32(o + 0x20 + 4 * i);
  P115_TgtOn = on;
  P114_Timer((int32_t *)(o + 0x30));
  int32_t cnt = rd32(o + 0xc) + 1; memcpy(o + 0xc, &cnt, 4);
  if (rd32(o + 0x14) == 1) { P76_FlashStep((int32_t *)o); return; }
  if ((rd32(o + 0x10) & 0x100) != 0) WrapCounter004A3A80(o);
  if ((rd32(o + 8) & 0x80) == 0 && (rd32(o + 0x10) & 0x200) != 0) {
    int32_t dx = rd32(o + 0x20) - P59_PosX, dz = rd32(o + 0x28) - P59_PosZ;
    if ((dx < 0 ? -dx : dx) < 500 && (dz < 0 ? -dz : dz) < 500 && dx * dx + dz * dz < rd32(o + 0x1c)) {
      P115_TgtOn = 0;
      int32_t f8 = rd32(o + 8) | 0x80; memcpy(o + 8, &f8, 4);
      int32_t f10 = rd32(o + 0x10) & ~0x200; memcpy(o + 0x10, &f10, 4);
      int32_t z = 0; memcpy(o + 0xc, &z, 4);
      if (P14_00c810c4 == 1) { P14_00c810c4 = 0x7fff; P16_IdleMode = 0x7fff; P56_Blk84[1] = 0x7fff; }   /* псевдонимы в native */
    }
  }
}

/* ---- 004e5b78: HUD «бумаги»: значок ELPAPEL у правого края, отметки, затем P98_M4660 крестов/значков CROSS ---- */
void P115_PaperHud(void) {
  const uint8_t *paper = (const uint8_t *)re_ptr((uint32_t)P55_Paper0);
  if (P55_Paper0 == 0) return;
#ifndef RE_HOOK_BUILD
  if (paper == NULL) return;
#endif
  float x = P19_DivW - (float)paper[0xb];                         /* .rdata 00546060 = 640 */
  if (P62_I252B78 != 1) { if (P97_GrAlpha) P97_GrAlpha(3, 8, 0, 1, 1); if (P97_GrDepth) P97_GrDepth(4); P62_I252B78 = 1; }
  P96_IconAt(x, 0.0f, paper, 0xff, 0xff, 0xff);
  if (P62_I252B78 != 0) { if (P97_GrAlpha) P97_GrAlpha(3, 8, 0, 2, 1); if (P97_GrDepth) P97_GrDepth(7); P62_I252B78 = 0; }
  for (int32_t i = 0; i < 9; i++) if (P59_Flags9[i] != 0) P114_PaperMark(i);
  x = x + 11.0f;                                                  /* .rdata 005469b4 */
  float y = 10.0f + 0.0f;                                         /* .rdata 0054612c */
  for (int32_t n = P98_M4660; n != 0; n--) {
    float step;
    if (P55_Paper2 == 0) {
      P107_Line(x, y, x + 10.0f, y + 8.0f, 0xff0000);            /* .rdata 0054616c = 8 */
      P107_Line(x, y + 8.0f, x + 10.0f, y, 0xff0000);
      step = 20.0f;                                               /* .rdata 00546118 */
    } else {
      const uint8_t *cr = (const uint8_t *)re_ptr((uint32_t)P55_Paper2);
#ifndef RE_HOOK_BUILD
      if (cr == NULL) return;
#endif
      P112_IconScaled(cr, x, y, 0.5f, 0.5f);
      step = (float)cr[0xb];
    }
    x = x + step;
  }
}
