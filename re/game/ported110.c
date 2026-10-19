/* v1.55 (см. ported110.h). */
#include "ported110.h"
#include "aspect.h"
#include "p110_data.h"
#include "ported109.h"
#include "ported108.h"
#include "ported107.h"
#include "ported106.h"
#include "ported105.h"
#include "ported11.h"
#include "ported12.h"
#include "ported14.h"
#include "ported15.h"
#include "ported16.h"
#include "ported17.h"
#include "ported18.h"
#include "ported19.h"
#include "ported20.h"
#include "ported21.h"
#include "ported22.h"
#include "ported23.h"
#include "ported24.h"
#include "ported25.h"
#include "ported26.h"
#include "ported27.h"
#include "ported28.h"
#include "ported29.h"
#include "ported30.h"
#include "ported31.h"
#include "ported33.h"
#include "ported32.h"
#include "ported34.h"
#include "ported35.h"
#include "ported36.h"
#include "ported37.h"
#include "ported38.h"
#include "ported39.h"
#include "ported40.h"
#include "ported41.h"
#include "ported42.h"
#include "ported43.h"
#include "ported44.h"
#include "ported45.h"
#include "ported46.h"
#include "ported47.h"
#include "ported48.h"
#include "ported49.h"
#include "ported50.h"
#include "ported51.h"
#include "ported52.h"
#include "ported53.h"
#include "ported54.h"
#include "ported55.h"
#include "ported56.h"
#include "ported57.h"
#include "ported58.h"
#include "ported59.h"
#include "ported60.h"
#include "ported61.h"
#include "ported62.h"
#include "ported63.h"
#include "ported64.h"
#include "ported65.h"
#include "ported66.h"
#include "ported67.h"
#include "ported68.h"
#include "ported69.h"
#include "ported70.h"
#include "ported71.h"
#include "ported72.h"
#include "ported73.h"
#include "ported74.h"
#include "ported75.h"
#include "ported76.h"
#include "ported77.h"
#include "ported78.h"
#include "ported79.h"
#include "ported80.h"
#include "ported81.h"
#include "ported82.h"
#include "ported83.h"
#include "ported84.h"
#include "ported85.h"
#include "ported86.h"
#include "ported87.h"
#include "ported88.h"
#include "ported89.h"
#include "ported90.h"
#include "ported91.h"
#include "ported92.h"
#include "ported93.h"
#include "ported94.h"
#include "ported95.h"
#include "ported96.h"
#include "ported97.h"
#include "ported98.h"
#include "ported99.h"
#include "ported100.h"
#include "ported101.h"
#include "ported102.h"
#include "ported13.h"
#include "director.h"
#include "directorstorage.h"
#include "dirnodes.h"
#include "menustate.h"
#include "noop.h"
#include "uihandlers.h"
#include "uihandlers2.h"
#include "uihandlers3.h"
#include "uihandlers4.h"
#include "globalsets.h"
#include "smallfuncs.h"
#include "smallfuncs2.h"
#include "menuselect.h"
#include "widgets.h"
#include "ported4.h"
#include "ported5.h"
#include "ported6.h"
#include "ported7.h"
#include "ported8.h"
#include "ported9.h"
#include "ported10.h"
#include "unported.h"
#include "nodetab.h"
#include "cartab.h"
#include "menutab.h"
#include "p100_data.h"
#include "p103_data.h"
#include <math.h>
#include <string.h>
#include "ported103.h"
#include "p104_data.h"
#include <math.h>
#include <string.h>
#include "ported104.h"
#include "ported105.h"
#include "../platform/plat.h"
#include "ported4.h"
#include "ported6.h"
#include "ported7.h"
#include "ported8.h"
#include "unported.h"
#include "noop.h"
#include "globalsets.h"
#include "menustate.h"
#include "smallfuncs.h"
#include "smallfuncs2.h"
#include "uihandlers3.h"
#include "uihandlers4.h"
#include "widgets.h"
#include "cartab.h"
#include "director.h"
#include "dirnodes.h"

#include "ported107.h"



#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P110_GlowIcon")
#undef P110_GlowIcon
#pragma push_macro("P110_GlowIcon") /*gvi*/
#undef P110_GlowIcon /*gvi*/
uint32_t P110_GlowIcon;
#pragma pop_macro("P110_GlowIcon") /*gvi*/
#pragma pop_macro("P110_GlowIcon")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P110_SelCnt")
#undef P110_SelCnt
#pragma push_macro("P110_SelCnt") /*gvi*/
#undef P110_SelCnt /*gvi*/
int32_t P110_SelCnt;
#pragma pop_macro("P110_SelCnt") /*gvi*/
#pragma pop_macro("P110_SelCnt")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P110_ClipX0")
#undef P110_ClipX0
#pragma push_macro("P110_ClipX0") /*gvi*/
#undef P110_ClipX0 /*gvi*/
float P110_ClipX0;
#pragma pop_macro("P110_ClipX0") /*gvi*/
#pragma pop_macro("P110_ClipX0")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P110_ClipX1")
#undef P110_ClipX1
#pragma push_macro("P110_ClipX1") /*gvi*/
#undef P110_ClipX1 /*gvi*/
float P110_ClipX1;
#pragma pop_macro("P110_ClipX1") /*gvi*/
#pragma pop_macro("P110_ClipX1")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P110_ClipY0")
#undef P110_ClipY0
#pragma push_macro("P110_ClipY0") /*gvi*/
#undef P110_ClipY0 /*gvi*/
float P110_ClipY0;
#pragma pop_macro("P110_ClipY0") /*gvi*/
#pragma pop_macro("P110_ClipY0")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P110_ClipY1")
#undef P110_ClipY1
#pragma push_macro("P110_ClipY1") /*gvi*/
#undef P110_ClipY1 /*gvi*/
float P110_ClipY1;
#pragma pop_macro("P110_ClipY1") /*gvi*/
#pragma pop_macro("P110_ClipY1")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P110_FullClip")
#undef P110_FullClip
#pragma push_macro("P110_FullClip") /*gvi*/
#undef P110_FullClip /*gvi*/
int32_t P110_FullClip;
#pragma pop_macro("P110_FullClip") /*gvi*/
#pragma pop_macro("P110_FullClip")
#endif
#ifndef RE_HOOK_BUILD
#pragma push_macro("P110_SelRep") /*gvi*/
#undef P110_SelRep /*gvi*/
int32_t P110_SelRep = 10;                         /* .data 0054e52c */
#pragma pop_macro("P110_SelRep") /*gvi*/
#pragma push_macro("P110_IconKX") /*gvi*/
#undef P110_IconKX /*gvi*/
#pragma push_macro("P110_IconKY") /*gvi*/
#undef P110_IconKY /*gvi*/
float P110_IconKX = 1.0f, P110_IconKY = 1.0f;     /* .data 0054e520 / 0054e524 */
#pragma pop_macro("P110_IconKY") /*gvi*/
#pragma pop_macro("P110_IconKX") /*gvi*/
#pragma push_macro("P110_CellTab") /*gvi*/
#undef P110_CellTab /*gvi*/
p110_celltab_t P110_CellTab = P110_CELLTAB_INIT;  /* .data 00574574 (tools/gen_p110_data.py) */
#pragma pop_macro("P110_CellTab") /*gvi*/
#endif

#include "memrw.h"
static uint16_t rd16(const void *p) { uint16_t v; memcpy(&v, p, 2); return v; }
static void wrf(void *p, float v) { memcpy(p, &v, 4); }
static const float OOW_LO = 0.015625f;   /* 0x3c800000 */
#ifdef RE_HOOK_BUILD
#  define P110_STD __attribute__((stdcall))
#  define P110_KEY(a) (*(uint8_t *)(uintptr_t)(a))
#else
#  define P110_STD
#  define P110_KEY(a) KeyState[(a) - 0x00d04b00]
#endif
static void *glide_proc(const char *name) {
  for (int i = 0; i < P33_GlideCount(); i++)
    if (strcmp(P33_GlideName(i), name) == 0) return P33_GlideProc(i);
  return NULL;
}
static void poly_list(int32_t n, const void *v) {
  void (P110_STD *f)(int32_t, const void *) = (void (P110_STD *)(int32_t, const void *))glide_proc("_grDrawPolygonVertexList@8");
  if (f != NULL) f(n, v);
}
static void depth_bias(int32_t v) {   /* 01270e20 */
  void (P110_STD *f)(int32_t) = (void (P110_STD *)(int32_t))glide_proc("_grDepthBiasLevel@4");
  if (f != NULL) f(v);
}
static void state_tex(void) {
  if (P85_StateDirty != 4) { if (P85_StateFn) P85_StateFn(3, 1, 0, 1, 0); P85_StateDirty = 4; G6_01270C34 = 4; }
}
static void state_flat(void) {
  if (P85_StateDirty != 0) { if (P85_StateFn) P85_StateFn(1, 0, 0, 2, 0); P85_StateDirty = 0; G6_01270C34 = 0; }
}
static void blend(uint8_t m) {
  static const int32_t k[4][4] = { { 4, 0, 4, 0 }, { 0, 5, 4, 0 }, { 0, 6, 4, 0 }, { 4, 4, 0, 0 } };
  if (m > 3) return;
  if (P85_BlendCur != m) { if (P85_BlendFn) P85_BlendFn(k[m][0], k[m][1], k[m][2], k[m][3]); P85_BlendCur = m; P69_BlendOn = m; }
}
static void tex_page(uint32_t tex) {
  if (tex != (uint32_t)P86_CurTex) {
    P86_CurTex = (int32_t)tex;
#ifndef RE_HOOK_BUILD
    if (tex >= 0x100) return;
#endif
    if (P86_TexSrc) P86_TexSrc(0, (uint32_t)rd32(&g_01145a60[tex * 0x10 + 8]), 3, (uint32_t)rd32(&g_01145a60[tex * 0x10 + 0xc]));
  }
}
static void raster(const p85_rv *a, const p85_rv *b, const p85_rv *c) { if (P85_RasterB) P85_RasterB(a, b, c); }
static float oow_at(float z) {
  long zi = lrintf(z);
#ifndef RE_HOOK_BUILD
  if (zi < 0 || zi >= (long)(RE_OOW_N)) return 0.0f;
#endif
  return RE_OOW(zi);
}

/* ---- 0050bd09: отладочная сетка радара — 55×55 клеток P77_C5FE00 по 4×4 пикселя, цвет по типу клетки (.data 00574574).
   Типы 8/9 — четыре квадранта 2×2 по битам 2/4/8/0x10. Цвет прошлой клетки сохраняется для типов без своего цвета
   (в оригинале начальное значение не задано; здесь — «не рисовать»). ---- */
void P110_RadarGrid(void) {
  uint32_t col = 0xffffffffu, cc = 0;
  for (uint32_t y = 0; y < 0x37; y++) {
    for (uint32_t x = 0; x < 0x37; x++) {
      uint32_t c = (uint32_t)rd32(&P77_C5FE00[(y * 0x37 + x) * 4]);
#ifndef RE_HOOK_BUILD
      int32_t k = (c < 64) ? P110_CellTab[c] : 0;
#else
      int32_t k = P110_CellTab[c];
#endif
      if (k < 10) {
        if (k < 8) {
          if (k == 3) col = 0x40;
          else if (k == 7) col = 0x7f00;
        } else {
          cc = (k == 9) ? 0x7f7f00u : 0x7f0000u;
          P108_FillRect((float)(x << 2), (float)(y << 2), 2.0f, 2.0f, (c & 2) ? cc : 0x7f00u);
          P108_FillRect((float)(x * 4 + 2), (float)(y << 2), 2.0f, 2.0f, (c & 4) ? cc : 0x7f00u);
          P108_FillRect((float)(x << 2), (float)(y * 4 + 2), 2.0f, 2.0f, (c & 8) ? cc : 0x7f00u);
          P108_FillRect((float)(x * 4 + 2), (float)(y * 4 + 2), 2.0f, 2.0f, (c & 0x10) ? cc : 0x7f00u);
          col = 0xffffffffu;
        }
      } else if (k == 0x20) col = 0x407f7f;
      else if (k == 0x1000) col = 0x7f0000;
      if (x == 0x1b && y == 0x1b) col = 0x7f7f7f;
      if (col != 0xffffffffu) P108_FillRect((float)(x << 2), (float)(y << 2), 4.0f, 4.0f, col);
    }
  }
}

/* ---- 00502787: полоса-индикатор. Запись: +0 x, +4 y, +8 w, +0xc h (640×480), +0x10 значение, +0x14 максимум, +0x18..+0x20 цвет,
   +0x24 адрес подписи, +0x28 флаги (1 — вертикально, 2 — справа налево), +0x2c включено. Рамка 0x808080, фон 0x303030,
   заливка — grDrawPolygonVertexList (низ темнее в 4 раза), подпись с тенью. ---- */
void P110_Gauge(uint8_t *p) {
#ifndef RE_HOOK_BUILD
  if (p == NULL) return;
#endif
  if (rd32(p + 0x2c) == 0) return;
  float kx = (float)P19_ScrW / P19_DivW, ky = (float)P19_ScrH / P19_DivH;
  uint32_t fl = (uint32_t)rd32(p + 0x28);
  float tx = ((fl & 2) == 0) ? rdf(p) : rdf(p) - rdf(p + 8);
  float ty = rdf(p + 4) - rdf(p + 0xc);
  float x = P19_ScaleX(tx), y = P19_ScaleY(rdf(p + 4));
  float w = kx * rdf(p + 8) * P19_Scale, h = ky * rdf(p + 0xc) * P19_Scale;
  P108_FillRect(x - 1.0f, y - 1.0f, w + 2.0f, 1.0f, 0x808080);
  P108_FillRect(x - 1.0f, y + h, w + 2.0f, 1.0f, 0x808080);
  P108_FillRect(x - 1.0f, y, 1.0f, h + 1.0f, 0x808080);
  P108_FillRect(x + w, y, 1.0f, h + 1.0f, 0x808080);
  P108_FillRectB(x, y, w, h, 0x303030);
  if (rdf(p + 0x14) < rdf(p + 0x10)) wrf(p + 0x10, rdf(p + 0x14));
  float x0, x1, y0;
  if ((fl & 1) == 0) {
    if ((fl & 2) == 0) { x0 = 0.0f; x1 = rdf(p + 0x10) / rdf(p + 0x14); y0 = 0.0f; }
    else { x0 = 1.0f - rdf(p + 0x10) / rdf(p + 0x14); x1 = 1.0f; y0 = 0.0f; }
  } else { x0 = 0.0f; x1 = 1.0f; y0 = 1.0f - rdf(p + 0x10) / rdf(p + 0x14); }
  if (x0 != x1 && y0 != 1.0f) {
    float oow = (P55_BDFA18 == 0) ? OOW_LO : 1.0f;
    float v[4][15];
    memset(v, 0, sizeof v);   /* z, ooz, a, tmu в оригинале не заданы */
    float r = rdf(p + 0x18), g = rdf(p + 0x1c), b = rdf(p + 0x20);
    v[0][0] = x0 * w + x; v[0][1] = y0 * h + y; v[0][3] = r; v[0][4] = g; v[0][5] = b; v[0][8] = oow;
    v[1][0] = x1 * w + x; v[1][1] = y0 * h + y; v[1][3] = r; v[1][4] = g; v[1][5] = b; v[1][8] = oow;
    v[2][0] = x1 * w + x; v[2][1] = h * 1.0f + y; v[2][3] = r / 4.0f; v[2][4] = g / 4.0f; v[2][5] = b / 4.0f; v[2][8] = oow;
    v[3][0] = x0 * w + x; v[3][1] = h * 1.0f + y; v[3][3] = r / 4.0f; v[3][4] = g / 4.0f; v[3][5] = b / 4.0f; v[3][8] = oow;
    state_flat();
    blend(0);
    poly_list(4, v);
  }
  P12_Fn00426580(0x18);
  SetRGB00516EB4(0xff, 0xff, 0xff);
  uint32_t txt = (uint32_t)rd32(p + 0x24);
  P96_TextAt(tx + 2.0f, ty + 2.0f, txt, 0, -1);
  P96_TextAt(tx, ty, txt, 0, 1);
}

/* ---- 004aa4ea: значок icon (+8 страница, +9/+0xa u/v, +0xb/+0xc w/h; 0 — 256) в прямоугольнике 640×480; page ≠ -1 — своя страница ---- */
void P110_IconRect(int32_t x, int32_t y, int32_t w, int32_t h, void *icon, int32_t page) {
  if (y <= -0x201) return;
  const uint8_t *ic = (const uint8_t *)icon;
#ifndef RE_HOOK_BUILD
  if (ic == NULL) return;
#endif
  float u0 = (float)ic[9] + 0.5f, v0 = (float)ic[10] + 0.5f;
  float uw = (ic[0xb] == 0) ? 255.5f : (float)ic[0xb] - 0.5f;
  float vh = (ic[0xc] == 0) ? 255.5f : (float)ic[0xc] - 0.5f;
  float oow = (P55_BDFA18 == 0) ? OOW_LO : 1.0f;
  float x0 = P19_ScaleX((float)x), y0 = P19_ScaleY((float)y), x1 = P19_ScaleX((float)(x + w)), y1 = P19_ScaleY((float)(y + h));
  float v[4][15];
  memset(v, 0, sizeof v);
  const float px[4] = { x0, x1, x1, x0 }, py[4] = { y0, y0, y1, y1 };
  const float s[4] = { u0, u0 + uw, u0 + uw, u0 }, t[4] = { v0, v0, v0 + vh, v0 + vh };
  for (int i = 0; i < 4; i++) {
    v[i][0] = px[i]; v[i][1] = py[i]; v[i][3] = v[i][4] = v[i][5] = v[i][7] = 255.0f;
    v[i][8] = oow; v[i][9] = s[i] * oow; v[i][10] = t[i] * oow;
  }
  state_tex();
  tex_page(page == -1 ? (uint32_t)ic[8] : (uint32_t)page);
  blend(0);
  poly_list(4, v);
}

/* ---- 004b53de / 004b8871 / 004b82b2: значок 01123208 размером 40×40 вокруг точки камеры p (+0 x, +4 y, +8 z) со сдвигом глубины -90 ---- */
static void glow_quad(const uint8_t *p, float r, float g, float b) {
  const uint8_t *ic = (const uint8_t *)re_ptr(P110_GlowIcon);
#ifndef RE_HOOK_BUILD
  if (ic == NULL) return;
#endif
  float px = rdf(p), py = rdf(p + 4);
  float xl = px - 20.0f, xr = px + 20.0f, yt = py - 20.0f, yb = py + 20.0f;
  if (P84_Mirror != 0) { xl = -xl; xr = -xr; }
  float oow = oow_at(rdf(p + 8)), f = P43_ScaleA * oow;
  p85_rv v[4];
  memset(v, 0, sizeof v);   /* z, ooz, a в оригинале не заданы */
  const float X[4] = { xl, xr, xr, xl }, Y[4] = { yt, yt, yb, yb };
  const uint8_t U[4] = { ic[9], ic[0xb], ic[0xb], ic[9] }, V[4] = { ic[10], ic[10], ic[0xc], ic[0xc] };
  for (int i = 0; i < 4; i++) {
    v[i].x = (X[i] * f + P43_OffX) - P43_Half; v[i].y = (Y[i] * f + P43_OffY) - P43_Half;
    v[i].r = r; v[i].g = g; v[i].b = b; v[i].oow = oow;
  }
  tex_page(ic[8]);
  for (int i = 0; i < 4; i++) { v[i].tmu[0] = (float)U[i] * oow; v[i].tmu[1] = (float)V[i] * oow; }
  depth_bias(-90);
  raster(&v[0], &v[1], &v[2]);
  raster(&v[2], &v[3], &v[0]);
  depth_bias(0);
}
static int glow_ok(const uint8_t *p) {
  return P95_Near <= rdf(p + 8) && rdf(p + 8) < (float)P62_I270C44 && P110_GlowIcon != 0;
}
void P110_GlowA(const uint8_t *p) {
#ifndef RE_HOOK_BUILD
  if (p == NULL) return;
#endif
  if (glow_ok(p)) glow_quad(p, 100.0f, 100.0f, 100.0f);
}
void P110_GlowB(const uint8_t *p) {
#ifndef RE_HOOK_BUILD
  if (p == NULL) return;
#endif
  if (P52_Ones2 != 0 && glow_ok(p)) glow_quad(p, (float)rd16(p + 0x64), 0.0f, 0.0f);
}
/* 004b82b2: яркость по отклонению углов камеры P59_AngA/AngB от углов записи (+0x6c/+0x6e), видно при |d| < 800 по обоим */
void P110_GlowC(const uint8_t *p) {
#ifndef RE_HOOK_BUILD
  if (p == NULL) return;
#endif
  if (!glow_ok(p)) return;
  int32_t d1 = (int32_t)((((uint32_t)(int32_t)(int16_t)P59_AngA - rd16(p + 0x6c)) + 0x800u) & 0xfffu) - 0x800;
  int32_t d2 = (int32_t)(((((uint32_t)-(int32_t)(int16_t)P59_AngB & 0xfffu) - rd16(p + 0x6e)) + 0x800u) & 0xfffu) - 0x800;
  int32_t a1 = d1 < 0 ? -d1 : d1, a2 = d2 < 0 ? -d2 : d2;
  if (a1 < 800 && a2 < 800) {
    float k = (float)(0x400 - (a1 + a2)) / 1024.0f;
    glow_quad(p, k * (float)rd16(p + 0x64), 0.0f, 0.0f);
  }
}

/* ---- 004cdda6: спрайты стека скрипта G2_ScriptStack — [0] число записей, записи по 0xd слов с +0x65 (слова 8/9 — x/y, 10 — 1/w),
   значок G00D17B1C, размер 16 × P43_ScaleA × 1/w; смешивание 3, режим драйвера 0 на время вывода ---- */
void P110_ScriptSprites(void) {
  int32_t *st = G2_ScriptStack;
#ifndef RE_HOOK_BUILD
  if (st == NULL) return;
#endif
  if (st[0] == 0) return;
  const uint8_t *ic = (const uint8_t *)re_ptr((uint32_t)G00D17B1C);
#ifndef RE_HOOK_BUILD
  if (ic == NULL) return;
#endif
  P12_Fn00426580(0);
  state_tex();
  tex_page(ic[8]);
  blend(3);
  int32_t old = DrvSetMode0042655A(0);
  p85_rv v[4];
  memset(v, 0, sizeof v);
  for (int i = 0; i < 4; i++) v[i].r = v[i].g = v[i].b = 255.0f;
  const int32_t *r = st + 0x65;
  for (int32_t n = st[0]; n != 0; n--, r += 0xd) {
    float k = (float)r[10];
    float s = 16.0f * P43_ScaleA * k;
    float x = (float)r[8], y = (float)r[9];
    v[0].x = x;     v[0].y = y + s; v[0].oow = k; v[0].tmu[0] = (float)ic[9] * k;   v[0].tmu[1] = (float)ic[0xc] * k;
    v[1].x = x + s; v[1].y = y + s; v[1].oow = k; v[1].tmu[0] = (float)ic[0xb] * k; v[1].tmu[1] = (float)ic[0xc] * k;
    v[2].x = x + s; v[2].y = y;     v[2].oow = k; v[2].tmu[0] = (float)ic[0xb] * k; v[2].tmu[1] = (float)ic[10] * k;
    v[3].x = x;     v[3].y = y;     v[3].oow = k; v[3].tmu[0] = (float)ic[9] * k;   v[3].tmu[1] = (float)ic[10] * k;
    raster(&v[3], &v[2], &v[1]);
    raster(&v[3], &v[1], &v[0]);
  }
  DrvSetMode0042655A(old);
}

/* ---- 0041938a: значок ic в точке (x, y) 640×480 с масштабом (sx, sy), цветом (r, g, b) × P19_Cur и смешиванием mode 0..3;
   масштаб экрана — .data 0054e520/0054e524 ---- */
void P110_IconQuad(float x, float y, float sx, float sy, const uint8_t *ic, uint32_t r, uint32_t g, uint32_t b, uint32_t mode) {
#ifndef RE_HOOK_BUILD
  if (ic == NULL) return;
#endif
  float oow = (P55_BDFA18 == 0) ? OOW_LO : 1.0f;
  float cr = (float)(uint8_t)r * P19_Cur, cg = (float)(uint8_t)g * P19_Cur, cb = (float)(uint8_t)b * P19_Cur;
  float u0 = (float)ic[9] + 0.5f, v0 = (float)ic[10] + 0.5f;
  float uw = (float)ic[0xb] * sx - 0.5f, vh = (float)ic[0xc] * sy - 0.5f;
  float X = x * P110_IconKX, Y = y * P110_IconKY, W = uw * P110_IconKX, H = vh * P110_IconKY;
  state_tex();
  blend((uint8_t)mode);
  tex_page(ic[8]);
  float v[4][15];
  memset(v, 0, sizeof v);
  const float px[4] = { X, X + W, X + W, X }, py[4] = { Y, Y, Y + H, Y + H };
  const float s[4] = { u0, u0 + uw, u0 + uw, u0 }, t[4] = { v0, v0, v0 + vh, v0 + vh };
  for (int i = 0; i < 4; i++) {
    v[i][0] = px[i]; v[i][1] = py[i]; v[i][3] = cr; v[i][4] = cg; v[i][5] = cb; v[i][7] = 255.0f;
    v[i][8] = oow; v[i][9] = s[i] * oow; v[i][10] = t[i] * oow;
  }
  poly_list(4, v);
}

/* ---- 00418675: выбор пункта меню — пункты по 0x10 (+0 выделить(2), +4 снять(2), +8 выполнить(), +0xc..+0xf соседи влево/вправо/вверх/вниз).
   При 005f7e4c ≠ 0 влево/вправо вызывают обработчик соседа с автоповтором (40, затем 3 кадра). Esc → -1. Обработчики — re_fn. ---- */
static void sel_call(const uint8_t *t, uint32_t off, int arg) {
  re_fn_t f = re_fn((uint32_t)rd32(t + off));
  if (f == NULL) return;
  if (arg) ((void (*)(int32_t))f)(2);
  else f();
}
int32_t P110_MenuSel(uint32_t tbl, int32_t cur) {
  const uint8_t *t = (const uint8_t *)re_ptr(tbl);
#ifndef RE_HOOK_BUILD
  if (t == NULL) return cur;
#endif
  uint32_t p = (uint32_t)cur, old = p;
  if (IsKeyDown(1) != 0) {
    Ui00418886();
    sel_call(t, 4 + p * 0x10, 1);
    return -1;
  }
  if ((MenuFlag5F7E4C | D_005f7e4c | G005F7E4C) == 0) {
    if (IsKeyDown(0xcb) != 0) p = t[0xc + p * 0x10];
    else if (IsKeyDown(0xcd) != 0) p = t[0xd + p * 0x10];
  } else {
    uint8_t l = P110_KEY(0x00d04bcb), rr = P110_KEY(0x00d04bcd);
    if (((l | rr) & 0x80) == 0) { P110_SelCnt = 0; P110_SelRep = 0x28; }
    if (P110_SelCnt == 0) {
      if (l & 0x80) { sel_call(t, (uint32_t)t[0xc + p * 0x10] * 0x10, 1); P110_SelCnt = P110_SelRep; P110_SelRep = 3; }
      else if (rr & 0x80) { sel_call(t, (uint32_t)t[0xd + p * 0x10] * 0x10, 1); P110_SelCnt = P110_SelRep; P110_SelRep = 3; }
    } else P110_SelCnt--;
  }
  if (IsKeyDown(200) != 0) p = t[0xe + p * 0x10];
  else if (IsKeyDown(0xd0) != 0) p = t[0xf + p * 0x10];
  else if (IsKeyDown(0x1c) != 0) { Ui00418886(); sel_call(t, 8 + p * 0x10, 0); }
  if (old != p) {
    Ui00418886();
    sel_call(t, 4 + old * 0x10, 1);
    sel_call(t, p * 0x10, 1);
  }
  return (int32_t)p;
}

/* ---- 004e8595: кольца дыма — 6 полос по 66 вершин сферы P96_Sphere (повёрнутой на ang, масштаб sc, flat — высота × 20),
   цвет (r, g, b) темнее к краям (−20/−30/−50 за ряд), значок SMOKE P108_SmokeIcon; треугольники полосы — скользящее окно из 3 вершин ---- */
void P110_SmokeRing(float sc, const float *pos, int32_t ang, uint32_t r, uint32_t g, uint32_t b, int32_t flat, int32_t tex) {
  const uint8_t *ic = (const uint8_t *)re_ptr(P108_SmokeIcon);
#ifndef RE_HOOK_BUILD
  if (ic == NULL || pos == NULL || ang < 0 || ang + 0x400 >= (int32_t)(sizeof P43_Sin / sizeof P43_Sin[0])) return;
#endif
  int32_t skip = 2;
  blend(3);
  if (tex == 0) state_flat();
  else { tex_page(ic[8]); state_tex(); P12_Fn00426580(0); }
  P44_MatPtr = (float *)P44_ViewMatT;
  p85_rv tri[3];
  memset(tri, 0, sizeof tri);   /* z, ooz, a в оригинале не заданы */
  float cs = P43_Sin[0x400 + ang], sn = P43_Sin[ang];
  for (int32_t e = 0; e < 6; e++) {
    int32_t k = 0;
    for (int32_t d = 0; d < 0x42; d++) {
      int32_t i = ((d & 0x3f) >> 1) + (e + (d & 1)) * 0x20;
      float v[3];
      v[0] = (cs * P96_Sphere[i][0] - sn * P96_Sphere[i][2]) * sc + pos[0];
      v[1] = (flat == 0) ? -P96_Sphere[i][1] * sc + pos[1] : -P96_Sphere[i][1] * 20.0f + pos[1];
      v[2] = (cs * P96_Sphere[i][2] + sn * P96_Sphere[i][0]) * sc + pos[2];
      P44_Xform(v);
      if (P95_Near <= v[2]) {
        p85_rv *o = &tri[k];
        float oow = oow_at(v[2]), f = P43_ScaleA * oow;
        o->oow = oow;
        o->x = (v[0] * f + P43_OffX) - P43_Half;
        o->y = (v[1] * f + P43_OffY) - P43_Half;
        int32_t a = 3 - (e + (d & 1));
        if (a < 0) a = -a;
        o->r = (float)(int32_t)((r & 0xff) + (uint32_t)(a * -0x14)); if (o->r < P8_00546024) o->r = 0.0f;
        o->g = (float)(int32_t)((g & 0xff) + (uint32_t)(a * -0x1e)); if (o->g < P8_00546024) o->g = 0.0f;
        o->b = (float)(int32_t)((b & 0xff) + (uint32_t)(a * -0x32)); if (o->b < P8_00546024) o->b = 0.0f;
        o->tmu[0] = (float)((k % 3 == 0) ? ic[0xb] : ic[9]) * oow;
        o->tmu[1] = (float)(((k + 1) % 3 == 0) ? ic[0xc] : ic[10]) * oow;
        if (skip == 0) raster(&tri[0], &tri[1], &tri[2]);
        else skip--;
      } else skip = 2;
      if (++k == 3) k = 0;
    }
  }
}

/* ---- 00425b12: окно 3D-вида — центр (P101_ScrX0/Y0, P43_OffX/OffY) со сдвигом (x, y), окно отсечения P110_Clip* по масштабу 0125f3e0
   (при смене масштаба — пересчёт 00526427 с масштабом × ширина/640). mode 1 — сначала очистка всего экрана, 2 — окно усечением (__ftol)
   и очистка, иначе — окно с округлением (fistp через 00ba52d0). Glide-функции — по имени через P33. ---- */
static void clip_window(int32_t a, int32_t b, int32_t c, int32_t d) {
  void (P110_STD *f)(int32_t, int32_t, int32_t, int32_t) = (void (P110_STD *)(int32_t, int32_t, int32_t, int32_t))glide_proc("_grClipWindow@16");
  if (f != NULL) f(a, b, c, d);
}
static void buffer_clear(int32_t a, int32_t b, int32_t c) {
  void (P110_STD *f)(int32_t, int32_t, int32_t) = (void (P110_STD *)(int32_t, int32_t, int32_t))glide_proc("_grBufferClear@12");
  if (f != NULL) f(a, b, c);
}
static void set_scale(float v) { P11_0125f3e0 = v; P19_Scale = v; }
static void clip_round(void) {
  int32_t y1 = (int32_t)lrintf(P110_ClipY1), x1 = (int32_t)lrintf(P110_ClipX1), y0 = (int32_t)lrintf(P110_ClipY0), x0 = (int32_t)lrintf(P110_ClipX0);
  P11_00ba52d0 = x0;
  clip_window(x0, y0, x1, y1);
}
void P110_ViewSetup(int32_t x, int32_t y, int32_t mode) {
  float sc = P11_0125f3e0;
  int32_t W = P19_ScrW, H = P19_ScrH;
  if (P62_F25F404 != sc) {
    P62_F25F404 = sc;
    set_scale(((float)W / P19_DivW) * sc);
    P12_Fn00526427();
    set_scale(P62_F25F404);
  }
  sc = P11_0125f3e0;
  P19_Scale = sc;   /* native-псевдонимы 0125f3e0 */
#ifndef RE_HOOK_BUILD
  /* v2.15 Hor+ (aspect.h): основной вид (ширина 640) — окно отсечения шире на S с каждой стороны, центр проекции прежний (W/2 + x) */
  const int32_t ex = re_view_extra();
  const float Wc = (float)(W + 2 * ex);
#else
  const int32_t ex = 0;
  const float Wc = (float)W;
#endif
  if (P110_FullClip == 0) {
    P110_ClipX0 = ((float)W / 2.0f + (float)x) - (Wc * sc) / 2.0f;
    P110_ClipY0 = ((float)H / 2.0f + (float)y) - ((float)H * sc) / 2.0f;
    P110_ClipX1 = Wc * sc + P110_ClipX0;
    P110_ClipY1 = (float)H * sc + P110_ClipY0;
  } else {
    P110_ClipX0 = 0.0f - (float)ex; P110_ClipY0 = 0.0f;
    P110_ClipX1 = (float)(W + ex) + 0.0f; P110_ClipY1 = (float)H + 0.0f;
  }
  P101_ScrX0 = (float)(W / 2) + (float)x;
  P101_ScrY0 = (float)(H / 2) + (float)y;
  P43_OffX = (float)x + P43_Half + (float)(W / 2);
  P43_OffY = (float)y + P43_Half + (float)(H / 2);
  P62_F252A94 = (float)(W / 2);
  P62_F25F3F4 = (float)(H / 2);
  uint8_t m = (uint8_t)mode;
  if (m == 1) {
    clip_window(-ex, 0, W + ex, H);
    buffer_clear(0, 0, 0xffff);
    clip_round();
  } else if (m == 2) {
    clip_window((int32_t)P110_ClipX0, (int32_t)P110_ClipY0, (int32_t)P110_ClipX1, (int32_t)P110_ClipY1);
    buffer_clear(0, 0, 0xffff);
  } else clip_round();
  SetScale54EF38(P11_0125f3e0);
}
