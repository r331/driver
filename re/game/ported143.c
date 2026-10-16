/* v1.88: ported143 — см. ported143.h.
   004b418d — при P84_Mirror == 0, 00b87e84 == 0, 00575f30 ≠ 0 и 00b202d8/dc/e0 == 0: состояние «текстура» (3,1,0,1,0) и смешение 3;
     направление на солнце (0, −10000, 32000) через матрицу вида 011effa0 (00528982); при z ≥ 50: экранная точка (x, y) через
     00ba53a0[fistp z] · 01251a64, спрайт SUN2 005536a8 (размер 24, яркость 1, 004b5049 с oow 0x37806855); grLfbConstantDepth(2);
     видимость при 00bdfa18 ≠ 0 и точке не ближе 4 пикселей к краю: grSstResetPerfStats, затем 8 × 8 пикселей 0xff98 в LFB
     (grLfbLock(1, 1, 0, 0, 1)) или, при .data 00553854 ≠ 0 (по умолчанию 1), два чёрных треугольника 8 × 8 вокруг точки
     (oow 0x37806c5b), grSstIdle; grSstPerfStats(0111d420) → pixelsOut (+0x10) в 010fb0d0, видимость = pixelsOut / 64; иначе
     прошлый 010fb0d0. Длина d = sqrt(x² + y²) смещения от центра; BLANK 005536c8: яркость (L − min(d, L)) / L · видимость
     (L = 01270c28 · 0125f3e0), размер 120 · 00553848, значок 0110b020, угол ftol((x << 10) / (640 · 0125f3e0)) (проверено по
     ассемблеру 004b4782..004b47ac), 004b4b27 с oow 0x37806855; grDepthBufferMode(0). При d < L — 8 CARLIGHT вдоль оси
     центр → солнце (шаг x/8, y/8; размер .data 00553678[i] · 00553848, яркость (L − d) / (2L) · видимость, рисуется при > 0);
     при d < L/2 — засветка всего окна 01252a84..90 двумя треугольниками цвета (140 − d/(L/2) · 140) · видимость, oow 1
     (при 00bdfa18 == 0 — 1/64). В конце grDepthBufferMode(2), 01270c34 = −1. Аргументы 004b5049/004b4b27/grDepthBufferMode,
     которые Ghidra потеряла, восстановлены по push в ассемблере.
   004b73f3 — объект o (+0 x, +4 y, +8 z, +0x10 точка для 004cc784, +0x50/+0x54 int16 машина/фонарь, +0x6c/+0x6e направление):
     при 50 ≤ z < 01270c44 и значке 01123208: отклонение направления на камеру от +0x6c/+0x6e (углы 00b1c268/6a), оба < 0x400 —
     яркость k = cos·cos (таблица 00b95280); при 00b202e0 и 00b87e84 — 004cc784(o + 0x10, 5, ftol(k · 255)); квадрат 40 × 40
     от (x − 20, y − 20) с цветом (255k, 10k, 10k), текстура по значку, grDepthBiasLevel(−90), два треугольника, bias 0.
     При 00b87e84 ≠ 0 и без зеркала — след: центр квадрата (ftol((x0 + x2) · 0.5), ftol((y0 + y2) · 0.5)) пишется в историю
     машины/фонаря 01105da0 по кадру 00d11924 & 3; если запись была в прошлом кадре и режим камеры не менялся (01137324 ==
     01137354, 01136c5c == 0): от позиции 2 кадра назад — полоса шириной |ftol(x0 − x2) >> 1| (сдвиг 4..199 пикселей), цвета
     (160k, 6k, 6k) / × 0.25 на дальнем конце, bias ftol(−1000 · oow); иначе вся история заполняется текущим центром.
     Все __ftol сверены с ассемблером (004b75ae, 004b7b47..8b, 004b7c55..79, 004b7d12, 004b7e7f..edf, 004b825b).
   Отступления native: Glide-указатели, которых нет (NULL), пропускаются; при отсутствии grSstPerfStats pixelsOut — прежнее
     0111d430; LFB, который не заблокировался (lfb == NULL), не пишется; номер машины/фонаря вне 0..65 / 0..7 — след не рисуется
     (в оригинале запись за пределом таблицы); неинициализированные в оригинале поля вершин (z, ooz, a) — 0. */
#include "ported143.h"
#include "reptr.h"
#include "ported7.h"
#include "ported8.h"
#include "ported11.h"
#include "ported12.h"
#include "ported13.h"
#include "ported14.h"
#include "ported19.h"
#include "ported26.h"
#include "ported33.h"
#include "ported43.h"
#include "ported44.h"
#include "ported52.h"
#include "ported55.h"
#include "ported59.h"
#include "ported62.h"
#include "ported67.h"
#include "ported84.h"
#include "ported85.h"
#include "ported86.h"
#include "ported95.h"
#include "ported97.h"
#include "ported99.h"
#include "ported107.h"
#include "ported108.h"
#include "ported110.h"
#include "ported111.h"
#include "uihandlers3.h"
#include <math.h>
#include <string.h>

#ifndef RE_HOOK_BUILD
p143_fx_t P143_Fx = P143_FX_INIT;
GAME_VAR_DEF(p143_hist_t, P143_LampHist, 0x01105da0)
GAME_VAR_DEF(p143_perf_t, P143_Perf, 0x0111d420)
#endif

#ifdef RE_HOOK_BUILD
#  define P143_STD __attribute__((stdcall))
#else
#  define P143_STD
#endif
typedef void (P143_STD *p143_v0_fn)(void);
typedef void (P143_STD *p143_v1_fn)(int32_t);
typedef void (P143_STD *p143_vp_fn)(void *);
typedef int32_t (P143_STD *p143_lock_fn)(int32_t, int32_t, int32_t, int32_t, int32_t, void *);
typedef int32_t (P143_STD *p143_unlock_fn)(int32_t, int32_t);

static const uint8_t k_553678[8] = { 0x20, 0x60, 0x60, 0x20, 0x80, 0x40, 0x40, 0x60 };  /* .data 00553678: размеры CARLIGHT */
static const float   k_553848 = 1.0f;     /* .data 00553848: масштаб размеров */
static const int32_t k_553854 = 1;        /* .data 00553854: 1 — проверка видимости треугольниками, 0 — через LFB */

static float u2f(uint32_t u) { float f; memcpy(&f, &u, 4); return f; }
static float rdf(const uint8_t *p) { float v; memcpy(&v, p, 4); return v; }
static void wrf(uint8_t *p, float v) { memcpy(p, &v, 4); }
static int32_t rd32(const uint8_t *p) { int32_t v; memcpy(&v, p, 4); return v; }
static void wr32(uint8_t *p, int32_t v) { memcpy(p, &v, 4); }
static int32_t rd16(const uint8_t *p) { int16_t v; memcpy(&v, p, 2); return v; }
static uint32_t rdu16(const uint8_t *p) { uint16_t v; memcpy(&v, p, 2); return v; }
static void wr16(uint8_t *p, int32_t v) { int16_t s = (int16_t)v; memcpy(p, &s, 2); }
static int32_t ftol(double v) { return (int32_t)v; }                  /* __ftol: усечение к нулю */
static int32_t fist(float v) { int32_t i = (int32_t)lrintf(v); P11_00ba52d0 = i; return i; }  /* fistp → 00ba52d0 */
static void *glide(const char *name) {
  for (int i = 0; i < P33_GlideCount(); i++)
    if (strcmp(P33_GlideName(i), name) == 0) return P33_GlideProc(i);
  return NULL;
}
static void gcall0(const char *n) { p143_v0_fn f = (p143_v0_fn)glide(n); if (f) f(); }
static void gcall1(const char *n, int32_t a) { p143_v1_fn f = (p143_v1_fn)glide(n); if (f) f(a); }
static void depth_mode(int32_t m) { p143_v1_fn f = (p143_v1_fn)FnPtr01270E80; if (f) f(m); }
static void raster(const p85_rv *a, const p85_rv *b, const p85_rv *c) { if (P85_RasterB) P85_RasterB(a, b, c); }
static void state_tex(void) { if (P85_StateDirty != 4) { if (P85_StateFn) P85_StateFn(3, 1, 0, 1, 0); P85_StateDirty = 4; } }
static void state_flat(void) { if (P85_StateDirty != 0) { if (P85_StateFn) P85_StateFn(1, 0, 0, 2, 0); P85_StateDirty = 0; } }
static void blend3(void) { if (P85_BlendCur != 3) { if (P85_BlendFn) P85_BlendFn(4, 4, 0, 0); P85_BlendCur = 3; } }
static float sinf_t(int32_t i) { return P43_Sin[i]; }                 /* 00b94280 (+0x400 — 00b95280) */
static uint8_t *fx(uint32_t a) { return (uint8_t *)P143_Fx + (a - 0x005536a8u); }
static void icon_tex(const uint8_t *ic) {
  if ((uint32_t)ic[8] != (uint32_t)P86_CurTex) {
    P86_CurTex = ic[8];
    if (P86_TexSrc) P86_TexSrc(0, (uint32_t)rd32(&g_01145a60[ic[8] * 0x10 + 8]), 3, (uint32_t)rd32(&g_01145a60[ic[8] * 0x10 + 0xc]));
  }
}
typedef struct { uint32_t size; void *lfb; uint32_t stride; uint32_t mode; uint32_t origin; } p143_lfbinfo_t;

/* ---- 004b418d ---- */
void P143_SunFlare(void) {
  if (P84_Mirror != 0 || P14_00b87e84 != 0 || P13_00575f30 == 0 || P14_00b202d8 != 0 || P14_00b202dc != 0 || P26_FxA != 0) return;
  float L = P19_Scale * (float)P19_ScrW;
  P12_Fn00426580(0);
  state_tex();
  blend3();
  P44_MatPtr = (float *)P44_ViewMatT;
  float *sv = &P107_SprV[(0x00b20010u - 0x00b1ffd0u) / 4];
  sv[0] = 0.0f; sv[1] = -10000.0f; sv[2] = 32000.0f;
  P44_Xform(sv);
  if (sv[2] < P95_Near) return;
  float oow = P12_00ba53a0[fist(sv[2])];
  float s = P43_ScaleA * oow;
  sv[0] *= s; sv[1] *= s;
  float fx0 = (P43_OffX - P43_Half) + sv[0], fy0 = (P43_OffY - P43_Half) + sv[1];
  int32_t x = fist(fx0), y = fist(fy0);
  wrf(fx(0x005536c0u), 24.0f);
  wrf(fx(0x005536b8u), (float)x);
  wrf(fx(0x005536bcu), (float)y);
  wrf(fx(0x005536b4u), 1.0f);
  P107_CarLight(0x005536a8u, u2f(0x37806855u));
  gcall1("_grLfbConstantDepth@4", 2);
  float vis;
  if (P55_BDFA18 == 0) vis = 1.0f;
  else {
    int32_t px;
    if (x < 4 || !((P43_OffX - P43_Half) + (P43_OffX - P43_Half) - P8_00546034 > (float)x) ||
        y < 4 || !((P43_OffY - P43_Half) + (P43_OffY - P43_Half) - P8_00546034 > (float)y)) {
      px = P8_010fb0d0;
    } else {
      gcall0("_grSstResetPerfStats@0");
      if (k_553854 == 0) {
        p143_lfbinfo_t info; memset(&info, 0, sizeof info);
        info.size = 0x14;
        p143_lock_fn lock = (p143_lock_fn)P97_LfbLock;
        if (lock) lock(1, 1, 0, 0, 1, &info);
        if (info.lfb != NULL) {
          uint8_t *p = (uint8_t *)info.lfb + (size_t)((y - 4) * (int32_t)(info.stride >> 1)) * 2 + (size_t)x * 2 - 8;
          for (int32_t r = 0; r < 8; r++) {
            uint8_t *row = p;
            for (int32_t c = 0; c < 8; c++) { wr16(p, 0xff98); p += 2; }
            p = row + (size_t)(info.stride >> 1) * 2;
          }
        }
        p143_unlock_fn ul = (p143_unlock_fn)FnPtr01270EAC;
        if (ul) ul(1, 1);
      } else {
        state_flat();
        blend3();
        p85_rv a, b, c; memset(&a, 0, sizeof a); memset(&b, 0, sizeof b); memset(&c, 0, sizeof c);
        a.x = (float)(x + 4); a.y = (float)(y - 4);
        b.x = (float)(x - 4); b.y = (float)(y + 4);
        c.x = (float)(x - 4); c.y = (float)(y - 4);
        a.oow = b.oow = c.oow = u2f(0x37806c5bu);
        raster(&a, &b, &c);
        c.x = (float)(x + 4); c.y = (float)(y + 4);
        raster(&a, &b, &c);
        if (P85_StateDirty != 4) { if (P85_StateFn) P85_StateFn(3, 1, 0, 1, 0); P85_StateDirty = 4; }
        P85_StateDirty = -1;
        gcall0("_grSstIdle@0");
      }
      p143_vp_fn ps = (p143_vp_fn)glide("_grSstPerfStats@4");
      if (ps) ps(P143_Perf);
      px = (int32_t)P143_Perf[4];
      P8_010fb0d0 = px;
    }
    vis = (float)px / G0054603C;
  }
  float d = (float)sqrt((double)(sv[1] * sv[1] + sv[0] * sv[0]));
  float m = (d < L) ? d : L;
  float k = ((L - m) / L) * vis;
  wrf(fx(0x005536e0u), 120.0f * k_553848);                         /* .rdata 005461a4 = 120 */
  wrf(fx(0x005536d8u), (float)x);
  wrf(fx(0x005536dcu), (float)y);
  wrf(fx(0x005536d4u), k);
  wr32(fx(0x005536ccu), (int32_t)P111_Ic0110B020);
  float ang = (float)(int32_t)((uint32_t)x << 10) / (P19_DivW * P19_Scale);
  P108_Sprite(0x005536c8u, u2f(0x37806855u), (uint32_t)ftol(ang));
  depth_mode(0);
  if (d < L) {
    float k2 = ((L - d) / (P19_DivC * L)) * vis;
    float dx = sv[0] / 8.0f, dy = sv[1] / 8.0f;                     /* .rdata 0054616c = 8 */
    for (int32_t i = 0; i < 8; i++) {
      uint8_t *r = fx(0x005536e8u + (uint32_t)i * 0x1c);
      wrf(r + 0x18, (float)k_553678[i] * k_553848);
      float lx = -dx + dx * (float)(i * 2 - 8), ly = -dy + dy * (float)(i * 2 - 8);
      lx = (P43_OffX - P43_Half) + lx;
      ly = (P43_OffY - P43_Half) + ly;
      wrf(r + 0x10, lx);
      wrf(r + 0x14, ly);
      wrf(r + 0xc, k2);
      if (rdf(r + 0xc) > 0.0f) P107_CarLight(0x005536e8u + (uint32_t)i * 0x1c, 1.0f);   /* .rdata 00546024 = 0 */
    }
    if (d < L / P19_DivC) {
      float c = (140.0f - (d / (L / P19_DivC)) * 140.0f) * vis;      /* .rdata 005461a0 = 140 */
      state_flat();
      blend3();
      p85_rv a, b, t; memset(&a, 0, sizeof a); memset(&b, 0, sizeof b); memset(&t, 0, sizeof t);
      a.r = a.g = a.b = b.r = b.g = b.b = t.r = t.g = t.b = c;
      a.x = P110_ClipX1; a.y = P110_ClipY0;
      b.x = P110_ClipX0; b.y = P110_ClipY1;
      t.x = P110_ClipX0; t.y = P110_ClipY0;
      a.oow = b.oow = t.oow = (P55_BDFA18 == 0) ? u2f(0x3c800000u) : 1.0f;
      raster(&a, &b, &t);
      t.x = P110_ClipX1; t.y = P110_ClipY1;
      raster(&a, &b, &t);
    }
  }
  depth_mode(2);
  P85_StateDirty = -1;
}

/* ---- 004b73f3 ---- */
void P143_LampGlow(const uint8_t *o) {
  float z = rdf(o + 8);
  if (!(P95_Near <= z) || !(z < (float)P62_I270C44) || P110_GlowIcon == 0) return;
  const uint8_t *ic = (const uint8_t *)re_ptr(P110_GlowIcon);
#ifndef RE_HOOK_BUILD
  if (ic == NULL) return;
#endif
  int32_t iz = fist(z), iy = fist(rdf(o + 4));
  int32_t a = (int32_t)(((((uint32_t)(int32_t)(int16_t)P59_AngA - (uint32_t)P44_Atan2(iy, iz)) & 0xfffu) - rdu16(o + 0x6c) + 0x800u) & 0xfffu) - 0x800;
  if (a < 0) a = -a;
  iz = fist(z); int32_t ix = fist(rdf(o));
  int32_t b = (int32_t)(((((uint32_t)P44_Atan2(ix, iz) - (uint32_t)(int32_t)(int16_t)P59_AngB) & 0xfffu) - rdu16(o + 0x6e) + 0x800u) & 0xfffu) - 0x800;
  if (b < 0) b = -b;
  if (a >= 0x400 || b >= 0x400) return;
  float k = P43_Sin[0x400 + a] * P43_Sin[0x400 + b];
  if (P26_FxA != 0 && P14_00b87e84 != 0) PushEntry_004CC784((const uint32_t *)(o + 0x10), 5, (uint8_t)ftol(k * 255.0f));
  float x = rdf(o) - 20.0f, y = rdf(o + 4) - 20.0f;                /* .rdata 00546118 = 20 */
  float xb = x + 40.0f, xc = x + 40.0f, xd = x;                       /* .rdata 005460fc = 40 */
  float yc = y + 40.0f, yd = y + 40.0f;
  if (P84_Mirror != 0) { x = -x; xb = -xb; xc = -xc; xd = -xd; }
  float oow = P12_00ba53a0[(int32_t)lrintf(z)];
  float s = P43_ScaleA * oow;
  p85_rv v0, v1, v2, v3;
  memset(&v0, 0, sizeof v0); memset(&v1, 0, sizeof v1); memset(&v2, 0, sizeof v2); memset(&v3, 0, sizeof v3);
  v0.x = (x * s + P43_OffX) - P43_Half;  v0.y = (y * s + P43_OffY) - P43_Half;
  v1.x = (xb * s + P43_OffX) - P43_Half; v1.y = (y * s + P43_OffY) - P43_Half;
  v2.x = (xc * s + P43_OffX) - P43_Half; v2.y = (yc * s + P43_OffY) - P43_Half;
  v3.x = (xd * s + P43_OffX) - P43_Half; v3.y = (yd * s + P43_OffY) - P43_Half;
  v0.oow = v1.oow = v2.oow = v3.oow = oow;
  float cr = k * 255.0f, cg = k * 10.0f;                               /* .rdata 00546064 = 255, 0054612c = 10 */
  v0.r = v1.r = v2.r = v3.r = cr;
  v0.g = v1.g = v2.g = v3.g = cg;
  v0.b = v1.b = v2.b = v3.b = cg;
  icon_tex(ic);
  v0.tmu[0] = (float)ic[9] * oow;   v0.tmu[1] = (float)ic[10] * oow;
  v1.tmu[0] = (float)ic[0xb] * oow; v1.tmu[1] = (float)ic[10] * oow;
  v2.tmu[0] = (float)ic[0xb] * oow; v2.tmu[1] = (float)ic[0xc] * oow;
  v3.tmu[0] = (float)ic[9] * oow;   v3.tmu[1] = (float)ic[0xc] * oow;
  gcall1("_grDepthBiasLevel@4", -0x5a);
  raster(&v0, &v1, &v2);
  raster(&v2, &v3, &v0);
  gcall1("_grDepthBiasLevel@4", 0);
  if (P14_00b87e84 == 0 || P84_Mirror != 0) return;
  int32_t car = rd16(o + 0x50), lamp = rd16(o + 0x54);
#ifndef RE_HOOK_BUILD
  if (car < 0 || car >= 0x42 || lamp < 0 || lamp >= 8) return;
#endif
  uint8_t *h = (uint8_t *)P143_LampHist + car * 0x140 + lamp * 0x28;
  float x0 = v0.x, y0 = v0.y, x2 = v2.x, y2 = v2.y;
  int32_t cur = P67_Cur;
  if (rd16(h + 0x20) == (int32_t)((uint32_t)cur & 0xffffu) - 1 && P59_Mode1137324 == P52_ResetB && P99_CamEnd == 0) {
    int32_t px = rd16(h + ((uint32_t)(cur - 2) & 3u) * 8), py = rd16(h + ((uint32_t)(cur - 2) & 3u) * 8 + 4);
    int32_t sx = (int16_t)ftol((x0 + x2) * 0.5f), sy = (int16_t)ftol((y0 + y2) * 0.5f);   /* .rdata 00546068 = 0.5 */
    wr16(h + 0x20, cur);
    wr32(h + ((uint32_t)cur & 3u) * 8, sx);
    wr32(h + ((uint32_t)cur & 3u) * 8 + 4, sy);
    int32_t w = ftol(x0 - x2) >> 1;
    if (w < 1) w = -w;
    int32_t ddx = px - sx, ddy = py - sy;
    int32_t ax = ddx < 1 ? -ddx : ddx, ay = ddy < 1 ? -ddy : ddy;
    if (ax + ay <= 4 || ax + ay >= 200 || w < 1) return;
    uint32_t an = (uint32_t)P44_Atan2(ddy, ddx) & 0xfffu;
    float f1 = (float)w * sinf_t((int32_t)an), f2 = (float)w * sinf_t((int32_t)((an + 0x400u) & 0xfffu));
    int32_t s18c = (int16_t)ftol(f2 - f1 * 0.5f), s18a = (int16_t)ftol(f2 * 0.5f + f1);
    v0.x = (float)sx + f1;          v0.y = (float)sy - f2;
    v1.x = (float)(px + s18a);      v1.y = (float)(py - s18c);
    v2.x = (float)(px + s18c);      v2.y = (float)(py + s18a);
    v3.x = (float)sx - f1;          v3.y = (float)sy + f2;
    v0.oow = v1.oow = v2.oow = v3.oow = oow;
    float c1 = k * 160.0f, c2 = k * 6.0f;                              /* .rdata 005461e4 = 160, 005461e0 = 6 */
    v0.r = v3.r = c1; v0.g = v0.b = v3.g = v3.b = c2;
    v1.r = v2.r = c1 * 0.25f;                                          /* .rdata 005461dc = 0.25 */
    v1.g = v1.b = v2.g = v2.b = c2 * 0.25f;
    icon_tex(ic);
    float su1 = (float)ic[0xb] * oow, su0 = (float)ic[9] * oow;
    float tm = ((float)((int32_t)ic[0xc] - (int32_t)ic[10]) / P19_DivC + (float)ic[10]) * oow, tv1 = (float)ic[0xc] * oow;
    v0.tmu[0] = su1; v1.tmu[0] = su1;
    v0.tmu[1] = tm;  v3.tmu[1] = tm;
    v1.tmu[1] = tv1; v2.tmu[1] = tv1;
    v2.tmu[0] = su0; v3.tmu[0] = su0;
    gcall1("_grDepthBiasLevel@4", ftol(-1000.0f * oow));              /* .rdata 005461a8 = −1000 */
    raster(&v0, &v1, &v2);
    raster(&v2, &v3, &v0);
    gcall1("_grDepthBiasLevel@4", 0);
  } else {
    for (int32_t i = 0; i < 4; i++) {
      wr32(h + i * 8, ftol((x0 + x2) * 0.5f));
      wr32(h + i * 8 + 4, ftol((y0 + y2) * 0.5f));
    }
    wr16(h + 0x20, cur);
  }
}
