/* v1.89: ported144 — см. ported144.h.
   004b588e — объект o (+0 x, +4 y, +8 z, +0x10 точка для 004cc784, +0x50/+0x54 int16 машина/фонарь, +0x64 uint16 тип (& 0x7f)
     и флаг 0x80, +0x68 флаги, +0x6c/+0x6e направление). При 50 ≤ z < 01270c44: отклонения a/b направления на камеру от
     +0x6c/+0x6e (углы 00b1c268/6a, 004024ff → 00525e7e, fistp в 00ba52d0). Запись c = .data 00553870 + тип · 0x1c
     (int r, g, b; float +0xc, +0x10, +0x14; флаги +0x18). Без флага 0x80: полуразмер h = c+0x10, яркость k = 1. С 0x80: a ≥ 0x400
     или b ≥ 0x496 — выход; при z > 10240.0 (double 005461d0): h = c+0xc, k = (45000 − z) · c+0x14 · 2.87687e−5 (или
     (15000 − z) · c+0x14 · 2.10084e−4 при байте 011373c0 == 0 и c+0x18 & 8), k2 = 0.8k; иначе при c+0x18 & 1 — f = (cos a · cos b ·
     cos(fistp(z · 0.1)))³, h = (c+0x10 − c+0xc) f + c+0xc, k2 = (1 − 0.8 c+0x14) f + 0.8 c+0x14, k = (1 − c+0x14) f + c+0x14, при
     c+0x18 & 4 и b > 0x400 всё × ((0x496 − b) / 150)³; без & 1 — s = min(a + b, 1024): h = (c+0x10 − c+0xc) s / 1024 + c+0xc,
     k = (1 − c+0x14) s / 1024 + c+0x14; угол поворота q = a' + b' + (fistp z >> 4) (a', b' — со знаком). При 00b202e0 и 00b87e84 —
     004cc784(o + 0x10, тип (5 → 9), (byte) ftol(k · 255)) (ассемблер 004b5d96..004b5de3). Квадрат 2h × 2h, повёрнутый на
     (2q) & 0xfff, вокруг (x, y) в экран через 00ba53a0[fistp z] · 01251a64 (зеркало 00bdc288 — x с минусом); цвет (k · r, k · g,
     (c+0x18 & 2 ? k2 : k) · b); значок 010fb204 (CARLYT) и grDepthBiasLevel(−200) или, при 0111a3e4 ≠ 0 и типе 9..12,
     COPFLARE и −2500 (push WORD [ebp−0x190]); два треугольника 01270dfc, bias 0. След — при 00b87e84, o+0x68 & 0xe00000, без
     зеркала и фонаре ≠ −1: история 01105da0 + машина · 0x140 + фонарь · 0x28 (o+0x68 & 0x800000) или 011232e0 + фонарь · 0x28;
     центр квадрата (ftol((x0 + x2) · 0.5), ftol((y0 + y2) · 0.5)); если запись была в прошлом кадре 00d11924 и режим камеры не
     менялся (01137324 == 01137354, 01136c5c == 0): ширина w = ftol(h · s · 0.35) (s = 01251a64 · oow, ассемблер 004b68d7), при
     сдвиге 4..199 пикселей и w ≥ 1 — полоса от позиции 2 кадра назад значком 01123208, цвет конца — /4, bias ftol(−1000 · oow);
     иначе вся история заполняется текущим центром. Все __ftol сверены с ассемблером (004b5da2, 004b67ca/ed, 004b6867/82,
     004b68e3, 004b6a23..77 — два первых результата не используются, 004b6da0).
   Отступления native: тип вне 0..13 (за таблицей 00553870) — выход; неинициализированные в оригинале угол q (без флага 0x80) и
     k2 (ветви без него) — 0; отсутствующий значок (re_ptr == NULL) — без рисования; Glide-указатели NULL пропускаются; история
     вне таблиц (машина вне 0..65, фонарь вне 0..7; без 0x800000 — фонарь ≠ 0) не пишется; запись 011232e0 в native — отдельный
     буфер P144_Hist0 (в оригинале её +0x20 совпадает с 01123300 P67_Ents); неинициализированные поля вершин — 0. */
#include "ported144.h"
#include "reptr.h"
#include "ported7.h"
#include "ported11.h"
#include "ported12.h"
#include "ported14.h"
#include "ported26.h"
#include "ported33.h"
#include "ported43.h"
#include "ported44.h"
#include "ported52.h"
#include "ported59.h"
#include "ported60.h"
#include "ported62.h"
#include "ported67.h"
#include "ported84.h"
#include "ported85.h"
#include "ported86.h"
#include "ported95.h"
#include "ported96.h"
#include "ported99.h"
#include "ported110.h"
#include "ported111.h"
#include "ported143.h"
#include "p111_data.h"
#include <math.h>
#include <string.h>

#ifndef RE_HOOK_BUILD
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P144_Hist0")
#undef P144_Hist0
#pragma push_macro("P144_Hist0") /*gvi*/
#undef P144_Hist0 /*gvi*/
p144_rec28_t P144_Hist0;
#pragma pop_macro("P144_Hist0") /*gvi*/
#pragma pop_macro("P144_Hist0")
#endif
#endif

#ifdef RE_HOOK_BUILD
#  define P144_STD __attribute__((stdcall))
#else
#  define P144_STD
#endif
typedef void (P144_STD *p144_v1_fn)(int32_t);

#ifndef RE_HOOK_BUILD
static const int32_t k_553870[P111_FLARE_N][7] = P111_FLARE_INIT;   /* .data 00553870 */
#endif

static float u2f(uint32_t u) { float f; memcpy(&f, &u, 4); return f; }
static float rdf(const uint8_t *p) { float v; memcpy(&v, p, 4); return v; }
static void wr32(uint8_t *p, int32_t v) { memcpy(p, &v, 4); }
static int32_t rd16(const uint8_t *p) { int16_t v; memcpy(&v, p, 2); return v; }
static uint32_t rdu16(const uint8_t *p) { uint16_t v; memcpy(&v, p, 2); return v; }
static uint32_t rdu32(const uint8_t *p) { uint32_t v; memcpy(&v, p, 4); return v; }
static void wr16(uint8_t *p, int32_t v) { int16_t s = (int16_t)v; memcpy(p, &s, 2); }
static int32_t ftol(double v) { return (int32_t)v; }                  /* __ftol: усечение к нулю */
static int32_t fist(float v) { int32_t i = (int32_t)lrintf(v); P11_00ba52d0 = i; return i; }  /* fistp → 00ba52d0 */
#ifdef RE_HOOK_BUILD
static int32_t cw(int32_t typ, int32_t j) { return *(const int32_t *)(uintptr_t)(0x00553870u + (uint32_t)typ * 0x1c + (uint32_t)j * 4); }
#else
static int32_t cw(int32_t typ, int32_t j) { return k_553870[typ][j]; }
#endif
static float cf(int32_t typ, int32_t j) { return u2f((uint32_t)cw(typ, j)); }
static void *glide(const char *name) {
  for (int i = 0; i < P33_GlideCount(); i++)
    if (strcmp(P33_GlideName(i), name) == 0) return P33_GlideProc(i);
  return NULL;
}
static void depth_bias(int32_t v) { p144_v1_fn f = (p144_v1_fn)glide("_grDepthBiasLevel@4"); if (f) f(v); }   /* 01270e20 */
static void raster(const p85_rv *a, const p85_rv *b, const p85_rv *c) { if (P85_RasterB) P85_RasterB(a, b, c); }
static void icon_tex(const uint8_t *ic) {
  if ((uint32_t)ic[8] != (uint32_t)P86_CurTex) {
    P86_CurTex = ic[8];
    uint32_t a, b; memcpy(&a, &g_01145a60[ic[8] * 0x10 + 8], 4); memcpy(&b, &g_01145a60[ic[8] * 0x10 + 0xc], 4);
    if (P86_TexSrc) P86_TexSrc(0, a, 3, b);
  }
}

/* ---- 004b588e ---- */
void P144_FlagFx(const uint8_t *o) {
  float z = rdf(o + 8);
  if (!(P95_Near <= z) || !(z < (float)P62_I270C44)) return;
  int32_t iz = fist(z), iy = fist(rdf(o + 4));
  int32_t sa = (int32_t)(((((uint32_t)(int32_t)(int16_t)P59_AngA - (uint32_t)P44_Atan2(iy, iz)) & 0xfffu) - rdu16(o + 0x6c) + 0x800u) & 0xfffu) - 0x800;
  int32_t a = sa < 0 ? -sa : sa;
  iz = fist(z); int32_t ix = fist(rdf(o));
  int32_t sb = (int32_t)(((((uint32_t)P44_Atan2(ix, iz) - (uint32_t)(int32_t)(int16_t)P59_AngB) & 0xfffu) - rdu16(o + 0x6e) + 0x800u) & 0xfffu) - 0x800;
  int32_t b = sb < 0 ? -sb : sb;
  uint32_t typ = rdu16(o + 0x64) & 0x7fu;
#ifndef RE_HOOK_BUILD
  if (typ >= P111_FLARE_N) return;
#endif
  int32_t t = (int32_t)typ;
  uint32_t cfl = (uint32_t)cw(t, 6);
  float h, k, k2 = 0.0f;
  uint32_t q = 0;
  if ((rdu16(o + 0x64) & 0x80u) == 0) {
    h = cf(t, 4); k = 1.0f;
  } else {
    if (a >= 0x400 || b >= 0x496) return;
    if (!((double)z <= 10240.0)) {                                    /* .rdata 005461d0 (double) */
      if ((uint8_t)P60_Var1373C0 == 0 && (cfl & 8u) != 0) k = (15000.0f - z) * cf(t, 5) * u2f(0x395c4a01u);   /* 0054602c, 005461c4 */
      else k = (45000.0f - z) * cf(t, 5) * u2f(0x37f15450u);                                                  /* 00546030, 005461c8 */
      h = cf(t, 3);
      k2 = u2f(0x3f4ccccdu) * k;                                                                              /* 005461c0 = 0.8 */
    } else {
      float zt = z * u2f(0x3dcccccdu);                                                                        /* 005461bc = 0.1 */
      if (cfl & 1u) {
        float c08 = u2f(0x3f4ccccdu) * cf(t, 5);
        int32_t i = fist(zt);
        float f = P43_Sin[0x400 + a] * P43_Sin[0x400 + b] * P43_Sin[0x400 + i];
        k = f * f * f;
        h = (cf(t, 4) - cf(t, 3)) * k + cf(t, 3);
        k2 = (1.0f - c08) * k + c08;
        k = (1.0f - cf(t, 5)) * k + cf(t, 5);
        if ((cfl & 4u) != 0 && b > 0x400) {
          float m = (float)(0x496 - b) / 150.0f;                                                              /* 005461b8 = 150 */
          m = m * m * m;
          k *= m; k2 *= m; h *= m;
        }
      } else {
        float s = (float)(a + b);
        if (s > 1024.0f) s = 1024.0f;                                                                         /* 00546160 */
        h = (cf(t, 4) - cf(t, 3)) * s * (1.0f / 1024.0f) + cf(t, 3);                                         /* 005461b4 */
        k = (1.0f - cf(t, 5)) * s * (1.0f / 1024.0f) + cf(t, 5);
      }
    }
    q = (uint32_t)(sa + sb + (fist(z) >> 4));
  }
  if (P26_FxA != 0 && P14_00b87e84 != 0) {
    uint8_t br = (uint8_t)ftol(k * 255.0f);                                                                   /* 00546064 */
    PushEntry_004CC784((const uint32_t *)(o + 0x10), (uint8_t)(typ == 5 ? 9 : typ), br);
  }
  float oow = RE_OOW((int32_t)lrintf(z));
  float sc = P43_ScaleA * oow;
  float hs = h * sc;                                                  /* [ebp−0x198] — ширина следа */
  float nh = -h;
  q = (q * 2u) & 0xfffu;
  float sn = P43_Sin[q], cs = P43_Sin[(q + 0x400u) & 0xfffu];
  float f1 = nh * cs - h * sn, f2 = h * cs + nh * sn;
  float px = rdf(o), py = rdf(o + 4);
  float x0 = f1 + px, x1 = f2 + px, x2 = -f1 + px, x3 = -f2 + px;
  float y0 = f2 + py, y1 = -f1 + py, y2 = -f2 + py, y3 = f1 + py;
  if (P84_Mirror != 0) { x0 = -x0; x1 = -x1; x2 = -x2; x3 = -x3; }
  p85_rv v0, v1, v2, v3;
  memset(&v0, 0, sizeof v0); memset(&v1, 0, sizeof v1); memset(&v2, 0, sizeof v2); memset(&v3, 0, sizeof v3);
  v0.x = (x0 * sc + P43_OffX) - P43_Half; v0.y = (y0 * sc + P43_OffY) - P43_Half;
  v1.x = (x1 * sc + P43_OffX) - P43_Half; v1.y = (y1 * sc + P43_OffY) - P43_Half;
  v2.x = (x2 * sc + P43_OffX) - P43_Half; v2.y = (y2 * sc + P43_OffY) - P43_Half;
  v3.x = (x3 * sc + P43_OffX) - P43_Half; v3.y = (y3 * sc + P43_OffY) - P43_Half;
  float cr = k * (float)cw(t, 0), cg = k * (float)cw(t, 1);
  float cb = ((cfl & 2u) ? k2 : k) * (float)cw(t, 2);
  v0.r = v1.r = v2.r = v3.r = cr;
  v0.g = v1.g = v2.g = v3.g = cg;
  v0.b = v1.b = v2.b = v3.b = cb;
  v0.oow = v1.oow = v2.oow = v3.oow = oow;
  uint32_t icn; int32_t bias;
  if (P111_CopFlare == 0 || typ < 9 || typ > 12) { icn = (uint32_t)P96_ObjBOn; bias = -200; }   /* 0xff38 */
  else { icn = P111_CopFlare; bias = -2500; }                                                   /* 0xf63c */
  const uint8_t *ic = (const uint8_t *)re_ptr(icn);
#ifndef RE_HOOK_BUILD
  if (ic == NULL) return;
#endif
  icon_tex(ic);
  v0.tmu[0] = (float)ic[9] * oow;   v0.tmu[1] = (float)ic[10] * oow;
  v1.tmu[0] = (float)ic[0xb] * oow; v1.tmu[1] = (float)ic[10] * oow;
  v2.tmu[0] = (float)ic[0xb] * oow; v2.tmu[1] = (float)ic[0xc] * oow;
  v3.tmu[0] = (float)ic[9] * oow;   v3.tmu[1] = (float)ic[0xc] * oow;
  depth_bias(bias);
  raster(&v0, &v1, &v2);
  raster(&v2, &v3, &v0);
  depth_bias(0);
  uint32_t ofl = rdu32(o + 0x68);
  if (P14_00b87e84 == 0 || (ofl & 0xe00000u) == 0 || P84_Mirror != 0) return;
  int32_t car = rd16(o + 0x50), lamp = rd16(o + 0x54);
  if (lamp == -1) return;
  uint8_t *hr;
  if (ofl & 0x800000u) {
#ifndef RE_HOOK_BUILD
    if (car < 0 || car >= 0x42 || lamp < 0 || lamp >= 8) return;
#endif
    hr = (uint8_t *)P143_LampHist + car * 0x140 + lamp * 0x28;
  } else {
#ifndef RE_HOOK_BUILD
    if (lamp != 0) return;
#endif
    hr = (uint8_t *)P144_Hist0 + lamp * 0x28;
  }
  float ax0 = v0.x, ay0 = v0.y, ax2 = v2.x, ay2 = v2.y;
  int32_t cur = P67_Cur;
  if (rd16(hr + 0x20) == (int32_t)((uint32_t)cur & 0xffffu) - 1 && P59_Mode1137324 == P52_ResetB && P99_CamEnd == 0) {
    int32_t qx = rd16(hr + ((uint32_t)(cur - 2) & 3u) * 8), qy = rd16(hr + ((uint32_t)(cur - 2) & 3u) * 8 + 4);
    int32_t sx = (int16_t)ftol((ax0 + ax2) * 0.5f), sy = (int16_t)ftol((ay0 + ay2) * 0.5f);   /* 00546068 = 0.5 */
    wr16(hr + 0x20, cur);
    wr32(hr + ((uint32_t)cur & 3u) * 8, sx);
    wr32(hr + ((uint32_t)cur & 3u) * 8 + 4, sy);
    int32_t w = ftol(hs * u2f(0x3eb33333u));                                                     /* 005461b0 = 0.35 */
    int32_t ddx = qx - sx, ddy = qy - sy;
    int32_t adx = ddx < 1 ? -ddx : ddx, ady = ddy < 1 ? -ddy : ddy;
    if (adx + ady <= 4 || adx + ady >= 200 || w < 1) return;
    uint32_t an = (uint32_t)P44_Atan2(ddy, ddx) & 0xfffu;
    float g1 = (float)w * P43_Sin[an], g2 = (float)w * P43_Sin[(an + 0x400u) & 0xfffu];
    int32_t s1f4 = (int16_t)ftol(g2 - g1 * 0.5f), s1f2 = (int16_t)ftol(g2 * 0.5f + g1);
    v0.x = (float)sx + g1;          v0.y = (float)sy - g2;
    v1.x = (float)(qx + s1f2);      v1.y = (float)(qy - s1f4);
    v2.x = (float)(qx + s1f4);      v2.y = (float)(qy + s1f2);
    v3.x = (float)sx - g1;          v3.y = (float)sy + g2;
    v1.r = v2.r = v0.r / 4.0f; v1.g = v2.g = v0.g / 4.0f; v1.b = v2.b = v0.b / 4.0f;          /* 005461ac = 4 */
    v0.oow = v1.oow = v2.oow = v3.oow = oow;
    const uint8_t *gi = (const uint8_t *)re_ptr(P110_GlowIcon);
#ifndef RE_HOOK_BUILD
    if (gi == NULL) return;
#endif
    icon_tex(gi);
    float su1 = (float)gi[0xb] * oow, su0 = (float)gi[9] * oow;
    float tm = ((float)((int32_t)gi[0xc] - (int32_t)gi[10]) / 2.0f + (float)gi[10]) * oow, tv1 = (float)gi[0xc] * oow;   /* 00546050 = 2 */
    v0.tmu[0] = su1; v1.tmu[0] = su1;
    v0.tmu[1] = tm;  v3.tmu[1] = tm;
    v1.tmu[1] = tv1; v2.tmu[1] = tv1;
    v2.tmu[0] = su0; v3.tmu[0] = su0;
    depth_bias(ftol(-1000.0f * oow));                                                            /* 005461a8 = −1000 */
    raster(&v0, &v1, &v2);
    raster(&v2, &v3, &v0);
    depth_bias(0);
  } else {
    for (int32_t i = 0; i < 4; i++) {
      wr32(hr + i * 8, ftol((ax0 + ax2) * 0.5f));
      wr32(hr + i * 8 + 4, ftol((ay0 + ay2) * 0.5f));
    }
    wr16(hr + 0x20, cur);
  }
}
