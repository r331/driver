/* v1.56 (см. ported111.h). */
#include "ported111.h"
#include "p111_data.h"
#include "icontab.h"
#include "reptr.h"
#include "ported6.h"
#include "ported8.h"
#include "ported10.h"
#include "ported12.h"
#include "ported13.h"
#include "ported15.h"
#include "ported21.h"
#include "ported33.h"
#include "ported43.h"
#include "ported44.h"
#include "ported51.h"
#include "ported62.h"
#include "ported69.h"
#include "ported80.h"
#include "ported84.h"
#include "ported85.h"
#include "ported86.h"
#include "ported93.h"
#include "ported94.h"
#include "ported95.h"
#include "ported96.h"
#include "ported98.h"
#include "ported100.h"
#include "ported101.h"
#include "ported104.h"
#include "ported108.h"
#include "ported110.h"
#include "smallfuncs.h"
#include "menustate.h"
#include <string.h>
#include <math.h>

#ifndef RE_HOOK_BUILD
p111_icontab_t P111_IconTab;
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P111_SparkIcon")
#undef P111_SparkIcon
#pragma push_macro("P111_SparkIcon") /*gvi*/
#undef P111_SparkIcon /*gvi*/
uint32_t P111_SparkIcon;
#pragma pop_macro("P111_SparkIcon") /*gvi*/
#pragma pop_macro("P111_SparkIcon")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P111_LeafIcon")
#undef P111_LeafIcon
#pragma push_macro("P111_LeafIcon") /*gvi*/
#undef P111_LeafIcon /*gvi*/
uint32_t P111_LeafIcon;
#pragma pop_macro("P111_LeafIcon") /*gvi*/
#pragma pop_macro("P111_LeafIcon")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P111_Ic0110B020")
#undef P111_Ic0110B020
#pragma push_macro("P111_Ic0110B020") /*gvi*/
#undef P111_Ic0110B020 /*gvi*/
uint32_t P111_Ic0110B020;
#pragma pop_macro("P111_Ic0110B020") /*gvi*/
#pragma pop_macro("P111_Ic0110B020")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P111_Ic0111D400")
#undef P111_Ic0111D400
#pragma push_macro("P111_Ic0111D400") /*gvi*/
#undef P111_Ic0111D400 /*gvi*/
uint32_t P111_Ic0111D400;
#pragma pop_macro("P111_Ic0111D400") /*gvi*/
#pragma pop_macro("P111_Ic0111D400")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P111_CopFlare")
#undef P111_CopFlare
#pragma push_macro("P111_CopFlare") /*gvi*/
#undef P111_CopFlare /*gvi*/
uint32_t P111_CopFlare;
#pragma pop_macro("P111_CopFlare") /*gvi*/
#pragma pop_macro("P111_CopFlare")
#endif

#ifdef RE_HOOK_BUILD
#  define P111_STD __attribute__((stdcall))
#else
#  define P111_STD
#endif
static float rdf(const void *p) { float v; memcpy(&v, p, 4); return v; }
static uint16_t rd16(const void *p) { uint16_t v; memcpy(&v, p, 2); return v; }
static int32_t rd32(const void *p) { int32_t v; memcpy(&v, p, 4); return v; }
static void wr32(void *p, uint32_t v) { memcpy(p, &v, 4); }
static const float SNAP = 1048576.0f;   /* .rdata 0054607c */
static const float Z_FAR = 45000.0f;    /* .rdata 00546030 */

static void *glide_proc(const char *name) {
  for (int i = 0; i < P33_GlideCount(); i++)
    if (strcmp(P33_GlideName(i), name) == 0) return P33_GlideProc(i);
  return NULL;
}
static void depth_bias(int32_t v) {   /* 01270e20 */
  void (P111_STD *f)(int32_t) = (void (P111_STD *)(int32_t))glide_proc("_grDepthBiasLevel@4");
  if (f != NULL) f(v);
}
static void raster(const p85_rv *a, const p85_rv *b, const p85_rv *c) { if (P85_RasterB) P85_RasterB(a, b, c); }
static void tex_page(uint32_t tex) {
  if (tex != (uint32_t)P86_CurTex) {
    P86_CurTex = (int32_t)tex;
    if (P86_TexSrc) P86_TexSrc(0, (uint32_t)rd32(&g_01145a60[tex * 0x10 + 8]), 3, (uint32_t)rd32(&g_01145a60[tex * 0x10 + 0xc]));
  }
}
static float oow_at(float z) {
  long zi = lrintf(z);
#ifndef RE_HOOK_BUILD
  if (zi < 0 || zi >= (long)(RE_OOW_N)) return 0.0f;
#endif
  return RE_OOW(zi);
}

/* ---- 004abd69: значок по имени (P93_FindIcon); +9/+10 += 1, +0xb/+0xc — правый/нижний край (ширина/высота + левый/верхний − 1) ---- */
static uint32_t icon_load(const char *name) {
  uint8_t *r = P93_FindIcon(name);
  if (r != NULL) {
    r[9] = (uint8_t)(r[9] + 1); r[10] = (uint8_t)(r[10] + 1);
    r[0xb] = (uint8_t)(r[0xb] + r[9] - 1); r[0xc] = (uint8_t)(r[0xc] + r[10] - 1);
  }
  return re_addr(r);
}
void P111_IconsInit(void) {
  P69_OvlOn = (int32_t)icon_load("DEBRIS");
  P111_SparkIcon = icon_load("SPARK");
  P108_SmokeIcon = icon_load("SMOKE");
  P96_SparkOn = (int32_t)icon_load("SWBIRD1");
  P96_DustOn = (int32_t)icon_load("SWBIRD2");
  P111_IconTab[2] = icon_load("JLITTER1");
  P111_IconTab[3] = icon_load("JLITTER2");
  P111_IconTab[4] = icon_load("JLITTER3");
  P111_IconTab[5] = icon_load("JLITTER4");
  P110_GlowIcon = icon_load("LIGHT");
  P96_ObjBOn = (int32_t)icon_load("CARLYT");
  P101_ObjBOn2 = (int32_t)icon_load("SMALLFLR");
  P98_SixRec = icon_load("SPOTL");
  P111_LeafIcon = icon_load("YLEAF");
  P8_011171a4 = (int32_t)icon_load("CARLIGHT");
  P8_010ffd0c = (int32_t)icon_load("SUN2");
  P111_Ic0110B020 = (uint32_t)P96_ObjBOn;
  P111_Ic0111D400 = P110_GlowIcon;
  P101_ObjBOn2 = P8_011171a4;
  P94_IconRec = (uint32_t)P8_011171a4;
  P111_CopFlare = icon_load("COPFLARE");
}

/* ---- 004b05ea: обломок o (+0 позиция, +0x26 индекс треугольника, +0x2c..0x2e цвет, +0x3a значок) — четырёхугольник значка по
   трём вершинам треугольника (4-я — достроенная); shadow ≠ 0 — серый (96) треугольник на высоте дороги − 10 (при P13_00d11880) ---- */
static void proj(p85_rv *v, float x, float y, float oow) {
  float f = P43_ScaleA * oow;
  v->x = (x * f + P43_OffX) - SNAP; v->y = (y * f + P43_OffY) - SNAP; v->oow = oow;
}
void P111_DebrisIcon(const float *o, int32_t shadow) {
  if (MenuVar553850 == 0) return;
  const uint8_t *ob = (const uint8_t *)o;
  uint32_t k = rd16(ob + 0x26), ia;
  const float *t;
#ifndef RE_HOOK_BUILD
  if (k >= 0x100) return;
#endif
  if (ob[0x3a] == 1) { ia = P111_LeafIcon; t = &P100_DebTri[k * 12]; }
  else {
#ifndef RE_HOOK_BUILD
    if (ob[0x3a] >= P111_ICONTAB_N) return;
#endif
    ia = P111_IconTab[ob[0x3a]]; t = &P104_DebC[k * 12];
  }
  if (ia == 0) return;
  const uint8_t *ic = (const uint8_t *)re_ptr(ia);
#ifndef RE_HOOK_BUILD
  if (ic == NULL) return;
#endif
  tex_page(ic[8]);
  p85_rv v[4];
  memset(v, 0, sizeof v);
  if (shadow == 0) {
    float a[3] = { (t[0] + o[0]) - P44_CamX, (t[1] + o[1]) - P44_CamY, (t[2] + o[2]) - P44_CamZ };
    P44_Xform(a);
    float b[3] = { (t[4] + o[0]) - P44_CamX, (t[5] + o[1]) - P44_CamY, (t[6] + o[2]) - P44_CamZ };
    float c[3] = { (t[8] + o[0]) - P44_CamX, (t[9] + o[1]) - P44_CamY, (t[10] + o[2]) - P44_CamZ };
    P44_Xform(b); P44_Xform(c);
    float d[3];
    for (int i = 0; i < 3; i++) d[i] = (c[i] - a[i]) / 2.0f + b[i];
    for (int i = 0; i < 3; i++) b[i] = (a[i] - c[i]) / 2.0f + b[i];
    if (P84_Mirror != 0) { a[0] = -a[0]; b[0] = -b[0]; c[0] = -c[0]; d[0] = -d[0]; }
    if (!(P95_Near <= a[2] && a[2] <= Z_FAR && P95_Near <= b[2] && b[2] <= Z_FAR && P95_Near <= c[2] && c[2] <= Z_FAR)) return;
    proj(&v[0], a[0], a[1], oow_at(a[2])); proj(&v[1], b[0], b[1], oow_at(b[2]));
    proj(&v[2], c[0], c[1], oow_at(c[2])); proj(&v[3], d[0], d[1], oow_at(d[2]));
    const uint8_t U[4] = { ic[9], ic[0xb], ic[9], ic[0xb] }, V[4] = { ic[10], ic[10], ic[0xc], ic[0xc] };
    for (int i = 0; i < 4; i++) {
      v[i].tmu[0] = (float)U[i] * v[i].oow; v[i].tmu[1] = (float)V[i] * v[i].oow;
      v[i].r = (float)ob[0x2c]; v[i].g = (float)ob[0x2d]; v[i].b = (float)ob[0x2e];
    }
    raster(&v[0], &v[1], &v[2]);
    raster(&v[3], &v[1], &v[2]);
  } else if (P13_00d11880 != 0) {
    float y = (float)(-10 - P100_RoadHeightF(o)) - P44_CamY;
    float a[3] = { (t[0] + o[0]) - P44_CamX, y, (t[2] + o[2]) - P44_CamZ };
    P44_Xform(a);
    if (!(P95_Near <= a[2])) return;
    float b[3] = { (t[4] + o[0]) - P44_CamX, y, (t[6] + o[2]) - P44_CamZ };
    float c[3] = { (t[8] + o[0]) - P44_CamX, y, (t[10] + o[2]) - P44_CamZ };
    P44_Xform(b); P44_Xform(c);
    if (P84_Mirror != 0) { a[0] = -a[0]; b[0] = -b[0]; c[0] = -c[0]; }
    proj(&v[0], a[0], a[1], oow_at(a[2])); proj(&v[1], b[0], b[1], oow_at(b[2])); proj(&v[2], c[0], c[1], oow_at(c[2]));
    for (int i = 0; i < 3; i++) { v[i].r = 96.0f; v[i].g = 96.0f; v[i].b = 96.0f; }   /* uv в оригинале не заданы */
    raster(&v[0], &v[1], &v[2]);
  }
}

/* ---- 004b6deb: вспышка p (+0 x, +4 y, +8 z камеры, +0x64 тип, +0x66 яркость, +0x6e полуразмер/4) — квадрат значка 0111a3e0,
   цвет = .data 00553870[тип].rgb × яркость / 256 (деление с усечением к нулю), сдвиг глубины −250 ---- */
#ifndef RE_HOOK_BUILD
static const int32_t k_flare[P111_FLARE_N][7] = P111_FLARE_INIT;
#endif
static float flare_c(uint32_t typ, int j, uint32_t k) {
#ifdef RE_HOOK_BUILD
  int32_t c = *(const int32_t *)(uintptr_t)(0x00553870u + typ * 0x1c + (uint32_t)j * 4);
#else
  int32_t c = k_flare[typ][j];
#endif
  return (float)((int32_t)((uint32_t)c * k) / 256);
}
void P111_Flare(const float *p) {
  float z = p[2];
  if (!(P95_Near <= z && z < (float)P62_I270C44)) return;
  const uint8_t *pb = (const uint8_t *)p;
  uint32_t typ = rd16(pb + 0x64), k = rd16(pb + 0x66);
  float s = (float)((uint32_t)rd16(pb + 0x6e) << 2);
  float xl = p[0] - s, xr = p[0] + s, yt = p[1] - s, yb = p[1] + s;
  if (P84_Mirror != 0) { xl = -xl; xr = -xr; }
  float oow = oow_at(z);
  p85_rv v[4];
  memset(v, 0, sizeof v);
  proj(&v[0], xl, yt, oow); proj(&v[1], xr, yt, oow); proj(&v[2], xr, yb, oow); proj(&v[3], xl, yb, oow);
  if (!(v[1].x - v[0].x <= 320.0f && v[0].x - v[1].x <= 320.0f)) return;
#ifndef RE_HOOK_BUILD
  if (typ >= P111_FLARE_N) return;
#endif
  float r = flare_c(typ, 0, k), g = flare_c(typ, 1, k), b = flare_c(typ, 2, k);
  for (int i = 0; i < 4; i++) { v[i].r = r; v[i].g = g; v[i].b = b; }
  const uint8_t *ic = (const uint8_t *)re_ptr((uint32_t)P101_ObjBOn2);
#ifndef RE_HOOK_BUILD
  if (ic == NULL) return;
#endif
  tex_page(ic[8]);
  v[0].tmu[0] = ((float)ic[9] + 0.5f) * oow; v[0].tmu[1] = ((float)ic[10] + 0.5f) * oow;
  v[1].tmu[0] = (float)ic[0xb] * oow;         v[1].tmu[1] = ((float)ic[10] + 0.5f) * oow;
  v[2].tmu[0] = (float)ic[0xb] * oow;         v[2].tmu[1] = (float)ic[0xc] * oow;
  v[3].tmu[0] = ((float)ic[9] + 0.5f) * oow;  v[3].tmu[1] = (float)ic[0xc] * oow;
  depth_bias(-250);
  raster(&v[0], &v[1], &v[2]);
  raster(&v[2], &v[3], &v[0]);
  depth_bias(0);
}

/* ---- 004cf2cf: такт текущей записи скрипта S_00D12410 (+0 флаги u16, +0xc клетка, +0x10 радиус², +0x14/+0x18 центр x/z,
   +0x1c первый контекст). Бит 4 — запись активна в клетке игрока, иначе (без бита 8) — в круге; вне — флаг 2 снимается.
   Контексты (+0x58 следующий, +0x54 указатель потока, +0x48 флаги, +0x44 скорость, +0x12 курс): опкоды u16 потока по таблице
   .data 0055fcac, пока обработчик возвращает ≠ 0; затем поворот к цели (+0x18) и шаг по курсу. ---- */
const uint32_t P111_OpAddr[P111_OPS_N] = {
  0x004d03fdu, 0x004d03fdu, 0x004d03fdu, 0x004d03fdu, 0x004d020bu, 0x004d02c6u, 0x004d033fu, 0x004d0404u,
  0x004d09fdu, 0x004d107eu, 0x004d1111u, 0x004d1135u, 0x004d116cu, 0x004d121bu, 0x004d133cu, 0x004d13d8u,
  0x004d1402u, 0x004d142cu, 0x004d14d8u, 0x004d03fdu, 0x004d1635u, 0x004d1672u, 0x004d1529u, 0x004d1601u,
  0x004d12cau, 0x004d03fdu, 0x004d1737u, 0x004d1765u, 0x004d156au, 0x004d0d7cu, 0x004d0734u, 0x004d0f28u, 0x004d03d0u };
static int32_t run_op(uint16_t op) {
#ifdef RE_HOOK_BUILD
  return ((int32_t (*)(void))(*(uint32_t *)(uintptr_t)(0x0055fcacu + (uint32_t)op * 4)))();
#else
  if (op >= P111_OPS_N) return 0;
  re_fn_t f = re_fn(P111_OpAddr[op]);
  if (f == NULL) return 0;              /* обработчик не перенесён — поток стоит */
  return ((int32_t (*)(void))f)();
#endif
}
static int32_t car_rd(uint32_t off) {   /* поле записи игрока S_00D11878 таблицы 00d077c0 (шаг 0x148) */
#ifndef RE_HOOK_BUILD
  if (S_00D11878 < 0 || S_00D11878 >= P99_CARS_N) return 0;
#endif
  return rd32((const uint8_t *)&P99_Cars[S_00D11878] + off);
}
static void set_ctx(uint8_t *c) { P10_ScriptCtx = c; S_00D1240C = c; }
static void set_sp(uint8_t *p) { P10_ScriptPtr = p; S_00D12414 = (int32_t)re_addr(p); }
void P111_ScriptTick(void) {
  if (G6_00B5A778 != 0) return;
  uint16_t *rec = S_00D12410;
#ifndef RE_HOOK_BUILD
  if (rec == NULL) return;
#endif
  uint8_t *rb = (uint8_t *)rec;
  if ((rec[0] & 4) != 0) {
    int32_t px = car_rd(0xc8), pz = car_rd(0xd0);
    int32_t cx = px / P80_Cell + P80_HalfW, cz = pz / P80_Cell + P80_HalfH;
    if (rd32(rb + 0xc) != cz * P21_GridDiv + cx) { rec[0] &= 0xfffd; return; }
  } else if ((rec[0] & 8) == 0) {
    int32_t dx = car_rd(0xc8) - (int32_t)lrintf(rdf(rb + 0x14));
    int32_t dz = car_rd(0xd0) - (int32_t)lrintf(rdf(rb + 0x18));
    P11_00ba52d0 = (int32_t)lrintf(rdf(rb + 0x18));
    if (dx < 0) dx = -dx;
    if (dz < 0) dz = -dz;
    if (rdf(rb + 0x10) < (float)(dx * dx + dz * dz)) { rec[0] &= 0xfffd; return; }
  }
  for (set_ctx((uint8_t *)re_rd_ptr(rb + 0x1c)); P10_ScriptCtx != NULL; set_ctx((uint8_t *)re_rd_ptr(P10_ScriptCtx + 0x58))) {
    uint8_t *c = P10_ScriptCtx;
    if ((rd32(c + 0x48) & 4) != 0) continue;
    set_sp((uint8_t *)re_rd_ptr(c + 0x54));
    for (;;) {
#ifndef RE_HOOK_BUILD
      if (P10_ScriptPtr == NULL) break;
#endif
      if (run_op(rd16(P10_ScriptPtr)) == 0) break;
    }
    if ((rec[0] & 2) == 0) return;
    if ((rd32(c + 0x48) & 4) != 0) continue;
    if ((rd32(c + 0x48) & 0x10) != 0 && (rd32(c + 0x48) & 0x80) == 0) {
      int32_t d[3] = { (int32_t)lrintf(rdf(c + 0x18) - rdf(c)), (int32_t)lrintf(rdf(c + 0x1c) - rdf(c + 4)),
                       (int32_t)lrintf(rdf(c + 0x20) - rdf(c + 8)) };
      P11_00ba52d0 = d[2];
      P51_SteerHeading(c, d);
    }
    float sp = rdf(c + 0x44);
    if (sp != P8_00546024 && (rd32(c + 0x48) & 0x40) != 0) {
      int32_t a = (int16_t)rd16(c + 0x12);
#ifndef RE_HOOK_BUILD
      if (a < 0 || a + 0x400 >= 5120) a &= 0xfff;
#endif
      float x = P43_Sin[0x400 + a] * sp + rdf(c), z = P43_Sin[a] * sp + rdf(c + 8);
      memcpy(c, &x, 4); memcpy(c + 8, &z, 4);
    }
    wr32(c + 0x54, re_addr(P10_ScriptPtr));
  }
}
