/* v1.53 (см. ported108.h). */
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

GAME_VAR_DEF(double, P108_FmvLen, 0x00b1c850)

static int32_t rd32(const void *p) { int32_t v; memcpy(&v, p, 4); return v; }
static float rdf(const void *p) { float v; memcpy(&v, p, 4); return v; }
static const float OOW_LO = 0.015625f;   /* 0x3c800000 */
static const float SNAP = 1048576.0f;    /* .rdata 0054607c */

static void state_flat(void) {
  if (P85_StateDirty != 0) { if (P85_StateFn) P85_StateFn(1, 0, 0, 2, 0); P85_StateDirty = 0; }
}
static void blend3(void) {
  if (P85_BlendCur != 3) { if (P85_BlendFn) P85_BlendFn(4, 4, 0, 0); P85_BlendCur = 3; P69_BlendOn = 3; }
}
static void raster(const p85_rv *a, const p85_rv *b, const p85_rv *c) { if (P85_RasterB) P85_RasterB(a, b, c); }
static void tex_select(const uint8_t *ic) {
  if (ic[8] != (uint32_t)P86_CurTex) {
    P86_CurTex = ic[8];
    if (P86_TexSrc) P86_TexSrc(0, (uint32_t)rd32(&g_01145a60[ic[8] * 0x10 + 8]), 3, (uint32_t)rd32(&g_01145a60[ic[8] * 0x10 + 0xc]));
  }
}

/* ---- 00518ab4: такт воспроизведения записи машины 0x41; на последнем кадре — вернуть сохранённое состояние ---- */
void P108_ReplayStep(void) {
  if (G6_00B87EA0 != 0 && P88_Mode575 == 2 && P101_RecState == 0) return;
  if (P101_RecSaved == 0) return;
  int32_t k = P100_RecRead(1);
  if (P100_RecCnt[1] == P101_RecFrame2) {
    P44_Copy4(&P99_Cars[0x41], P101_SaveCar, 0x148);
    P44_Copy4(P101_LiveA, P101_SaveA, 0x34);
    P44_Copy4(P101_LiveB, P101_SaveB, 0x34);
    P44_Copy4(P101_LiveC, P101_SaveC, 0x34);
    P99_Cars[0x41].f00[0] = 0x41;
    P99_CarModelClean(0x41);
    P100_RecRep[1] = 0; P100_RecVal[1] = 0; P100_RecCnt[1] = 0; P100_RecOff[1] = 0;
    P101_RecState = 0;
  } else {
    P107_CarInput(0x41, (uint32_t)k);
    MenuAddItem004DC8B0((uint8_t *)&P99_Cars[0x41], 1);
  }
}

/* ---- 0042205e / 00421e6c: эмулируемая текстура слота 256×256 (DDSURFACEDESC 0x7c, флаги 0x1007) ---- */
static int32_t emul_make(int32_t slot, int32_t pf_ofs, int32_t bpp, int32_t list) {
  uint32_t d[31];
  memset(d, 0, sizeof d);
  d[0] = 0x7c; d[1] = 0x1007;
  memcpy(&d[26], P32_DevInfo + 0x520, 8);
  memcpy(&d[18], P32_DevInfo + pf_ofs, 32);
  d[3] = 0x100; d[2] = 0x100;
  P32_Slot *s = &P32_Slots[slot];
  s->surf = P24_CreateSurface(P24_DD, d);
  if (s->surf == NULL) return 0;
  s->tex = P54_GetTexture2(s->surf);
  if (s->tex == NULL) return 0;
  s->bpp = bpp; s->has_list = list; s->cur_id = -1; s->list = NULL; s->cur_handle = NULL;
  return 1;
}
int32_t P108_EmulTex16(int32_t slot) {
#ifndef RE_HOOK_BUILD
  if (slot < 0 || slot + 1 >= 32 || P32_DevInfo == NULL) return 0;
#endif
  if (P32_Slots[slot].bpp == 0x10) return 1;
  P107_TexRelease(slot);
  if (G6_00A421F0 == 0) P107_TexRelease(slot + 1);
  return emul_make(slot, 0x528, 0x10, 0);
}
int32_t P108_EmulTex8(int32_t slot) {
#ifndef RE_HOOK_BUILD
  if (slot < 0 || slot + 1 >= 32 || P32_DevInfo == NULL) return 0;
#endif
  for (int32_t i = slot; i < slot + 2; i++) {
    if (P32_Slots[i].bpp == 8) continue;
    P107_TexRelease(i);
    if (emul_make(i, G6_00A421F0 == 0 ? 0x548 : 0x528, 8, G6_00A421F0) == 0) return 0;
    P32_CreateSlotPalette(i);
  }
  return 1;
}

/* ---- 0048b5e3: второй поток FMV — SetState(RUN), таймер на (длительность + 1) с ---- */
int32_t P108_FmvStart(void) {
  if (P38_Mms2 == NULL || plat_mms_set_state(P38_Mms2, 1) != 0) return 0;
  P38_TimerFlag = 0; G00551134 = 0;
  int32_t ms = (int32_t)((P108_FmvLen + 1.0) * 1000.0);   /* __ftol */
  P38_TimerSlot = P25_TimerStart((uint32_t)ms, 0, Set551134);
  return P38_TimerSlot == -1 ? 0 : 1;
}

/* ---- 00504a0a: треугольник-стрелка радара (вершина вверх), красный с яркостью red ≤ 255 ---- */
void P108_RadarArrow(int32_t x, int32_t red) {
  if (red > 0xff) red = 0xff;
  int32_t W = P19_ScrW, H = P19_ScrH;
  float fw = (float)W / 512.0f, fh = (float)H / 480.0f;
  int32_t cx = (int32_t)((double)(float)(x + 0x100) * fw);
  cx = (int32_t)((double)(float)(cx - (W >> 1)) * P19_Scale) + (W >> 1);
  fw = (float)W / P19_DivW;
  int32_t hw = (int32_t)(22.5 * (double)fw * (double)P19_Scale);
  int32_t hh = (int32_t)(45.0 * (double)fh * (double)P19_Scale);
  float cy = (float)((double)(float)(H >> 1) * P19_Scale + (double)(float)(H >> 1));
  p85_rv a, b, c;
  memset(&a, 0, sizeof a); memset(&b, 0, sizeof b); memset(&c, 0, sizeof c);
  a.x = (float)cx; a.y = cy - (float)hh;
  b.x = (float)(cx + hw); b.y = cy;
  c.x = (float)(cx - hw); c.y = cy;
  a.oow = b.oow = c.oow = (P55_BDFA18 == 0) ? OOW_LO : 1.0f;
  state_flat(); blend3();
  a.r = b.r = c.r = (float)red;
  raster(&a, &b, &c);
}

/* ---- 00505e2b: машина трафика на радаре — треугольник по курсу (длина 00d11a42, раствор 00d11a44) ---- */
void P108_RadarCar(float x, float z, int32_t i) {
  int32_t red = (0x2a9 < G2_00D11A5C && (P95_SndReady != 0 || 0 < P95_AmbN)) ? 1 : 0;
  state_flat(); blend3();
#ifndef RE_HOOK_BUILD
  if (i < 0 || i >= 0x40) return;
#endif
  const uint8_t *rec = &TrafficRecs[i * 0x54];
  const uint8_t *car;
#ifndef RE_HOOK_BUILD
  if (P59_CarsTab == NULL) car = (const uint8_t *)&P99_Cars[rec[0] + 1 < P99_CARS_N ? rec[0] + 1 : P99_CARS_N - 1]; else
#endif
  car = P59_CarsTab + (uint32_t)rec[0] * 0x148;
  int32_t hd = rd32(car + 0x100), half = (int32_t)(int16_t)P97_D11A44 / 2;
  float len = (float)(int32_t)(int16_t)((uint32_t)P95_SndRate >> 16);   /* 00d11a42 — старшее слово 00d11a40 */
  uint32_t u1 = ((uint32_t)(-half - hd) + 0x400u) & 0xfff, u2 = ((uint32_t)(half - hd) + 0x400u) & 0xfff;
  float ax = P43_Sin[0x400 + u1] * len + x, az = P43_Sin[u1] * len + z;
  float bx = P43_Sin[0x400 + u2] * len + x, bz = P43_Sin[u2] * len + z;
  p85_rv a, b, c;
  memset(&a, 0, sizeof a); memset(&b, 0, sizeof b); memset(&c, 0, sizeof c);
  P94_RadarXY(ax, az, &ax, &az);
  P94_RadarXY(bx, bz, &bx, &bz);
  P94_RadarXY(x, z, &c.x, &c.y);
  a.x = ax; a.y = az; b.x = bx; b.y = bz;
  float gb = red ? 0.0f : 80.0f;
  a.r = b.r = c.r = 80.0f; a.g = b.g = c.g = gb; a.b = b.b = c.b = gb;
  a.oow = b.oow = c.oow = (P55_BDFA18 == 0) ? OOW_LO : 1.0f;
  raster(&a, &b, &c);
}

/* ---- 004b1993 / 004b1ea0: квадрат дыма объекта (+0x10/+0x14/+0x18 вид, +0x50 размер), значок SMOKE ---- */
#ifndef RE_HOOK_BUILD
static const uint8_t k_smoke_rgb[24][3] = {   /* .data 00553680 */
  {7,7,7},{25,2,2},{35,0,0},{60,0,0},{60,25,0},{60,35,0},{60,55,0},{60,55,25},{60,55,35},{60,55,55},{70,70,70},{0,0,0},
  {0,0,0},{0,216,55},{85,0,0},{0,0,255},{240,192,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0} };
#endif
static void smoke_quad(const uint8_t *o, const uint8_t *ic, float cr, float cg, float cb) {
  float x = rdf(o + 0x10), y = rdf(o + 0x14), z = rdf(o + 0x18);
  int32_t sz = rd32(o + 0x50);
  float h = (float)(sz >> 1);
  float xl = x - h, xr = x + h, yt = y - (float)sz, yb = y;
  if (P84_Mirror != 0) { xl = -xl; xr = -xr; }
  int32_t zi = (int32_t)lrintf(z);
#ifndef RE_HOOK_BUILD
  if (zi < 0 || zi >= (int32_t)(sizeof P12_00ba53a0 / sizeof P12_00ba53a0[0])) return;
#endif
  float w = P12_00ba53a0[zi], f = P43_ScaleA * w;
  p85_rv v[4];
  memset(v, 0, sizeof v);
  v[0].x = (xl * f + P43_OffX) - SNAP; v[0].y = (yt * f + P43_OffY) - SNAP;
  v[1].x = (xr * f + P43_OffX) - SNAP; v[1].y = (yt * f + P43_OffY) - SNAP;
  v[2].x = (xr * f + P43_OffX) - SNAP; v[2].y = (yb * f + P43_OffY) - SNAP;
  v[3].x = (xl * f + P43_OffX) - SNAP; v[3].y = (yb * f + P43_OffY) - SNAP;
  if (!(v[1].x - v[0].x <= 320.0f && v[0].x - v[1].x <= 320.0f)) return;
  for (int k = 0; k < 4; k++) { v[k].r = cr; v[k].g = cg; v[k].b = cb; v[k].oow = w; }
  tex_select(ic);
  v[0].tmu[0] = (float)ic[9] * w;   v[0].tmu[1] = (float)ic[10] * w;
  v[1].tmu[0] = (float)ic[0xb] * w; v[1].tmu[1] = (float)ic[10] * w;
  v[2].tmu[0] = (float)ic[0xb] * w; v[2].tmu[1] = (float)ic[0xc] * w;
  v[3].tmu[0] = (float)ic[9] * w;   v[3].tmu[1] = (float)ic[0xc] * w;
  raster(&v[0], &v[1], &v[2]);
  raster(&v[2], &v[3], &v[0]);
}
void P108_SmokeA(const uint8_t *o) {
  float z = rdf(o + 0x18);
  if (!(300.0f < z && z < (float)P62_I270C44) || P108_SmokeIcon == 0) return;
  const uint8_t *ic = (const uint8_t *)re_ptr(P108_SmokeIcon);
#ifndef RE_HOOK_BUILD
  if (ic == NULL) return;
#endif
  int32_t c = rd32(o + 0x58);
  smoke_quad(o, ic, (float)c, (float)c, (float)(c + 0x32));
}
void P108_SmokeB(const uint8_t *o) {
  if (P108_SmokeIcon == 0) return;
  float z = rdf(o + 0x18);
  if (!(300.0f < z && z < (float)P62_I270C44)) return;
  const uint8_t *ic = (const uint8_t *)re_ptr(P108_SmokeIcon);
  uint16_t k; memcpy(&k, o + 100, 2);
#ifndef RE_HOOK_BUILD
  if (ic == NULL || k >= 24) return;
  const uint8_t *c = k_smoke_rgb[k];
#else
  const uint8_t *c = (const uint8_t *)(uintptr_t)(0x00553680u + (uint32_t)k * 3);
#endif
  smoke_quad(o, ic, (float)c[0], (float)c[1], (float)c[2]);
}

/* ---- 004b4b27: спрайт записи .data (+4 значок, +8 rgb, +0xc яркость, +0x10/+0x14 x,y, +0x18 размер), поворот ang; вершины 00b20060.. ---- */
#define SV(addr) ((p85_rv *)&P107_SprV[((addr) - 0x00b1ffd0u) / 4])
void P108_Sprite(uint32_t recaddr, float oow, uint32_t ang) {
  const uint8_t *r = (const uint8_t *)re_ptr(recaddr);
#ifndef RE_HOOK_BUILD
  if (r == NULL) return;
#endif
  if (rd32(r + 4) == 0) return;
  float x = rdf(r + 0x10), y = rdf(r + 0x14);
  float f = ((float)P19_ScrW / P19_DivW) * (rdf(r + 0x18) / P19_DivC) * P19_Scale;
  if (!(0.0f <= f + x && x - f < (float)P19_ScrW && 0.0f <= f + y && y - f < (float)P19_ScrH)) return;
  const uint8_t *ic = (const uint8_t *)re_rd_ptr(r + 4);
#ifndef RE_HOOK_BUILD
  if (ic == NULL) return;
#endif
  float m = -f, s = P43_Sin[ang & 0xfff], c = P43_Sin[(ang + 0x400) & 0xfff];
  p85_rv *A = SV(0x00b20060), *B = SV(0x00b200e0), *C = SV(0x00b20160), *D = SV(0x00b20120);
  A->x = (m * c - f * s) + x; A->y = f * c + m * s + y;
  B->x = (f * c - f * s) + x; B->y = f * c + f * s + y;
  C->x = (f * c - m * s) + x; C->y = m * c + f * s + y;
  D->x = (m * c - m * s) + x; D->y = m * c + m * s + y;
  D->oow = C->oow = B->oow = A->oow = oow;
  if (P84_Mirror != 0) { A->x = -A->x; B->x = -B->x; C->x = -C->x; D->x = -D->x; }
  float k = rdf(r + 0xc);
  A->r = (float)r[8] * k; A->g = (float)r[9] * k; A->b = (float)r[10] * k;
  B->r = D->r = C->r = A->r; B->g = D->g = C->g = A->g; B->b = D->b = C->b = A->b;
  tex_select(ic);
  A->tmu[0] = (float)(ic[9] + 1) * A->oow;
  A->tmu[1] = (float)(ic[10] + 1) * A->oow;
  B->tmu[0] = (float)ic[0xb] * A->oow;
  D->tmu[1] = (float)ic[0xc] * A->oow;
  B->tmu[1] = A->tmu[1]; D->tmu[0] = A->tmu[0]; C->tmu[0] = B->tmu[0]; C->tmu[1] = D->tmu[1];
  raster(A, B, C);
  raster(C, D, A);
}
#undef SV

/* ---- 00503f76: фигура радара — запись .data {вершины (по 16 байт), индексы (по 3), число треугольников} в точке pos+ofs.
   Фигура 00573f08 смещается по x на 4·00c808f4 (мигание). ---- */
void P108_RadarShape(uint32_t shape, const int32_t *pos, const int32_t *ofs, const int32_t *scr) {
  if (P98_C824A0 != 0) return;
  float v[3];
  v[1] = (float)pos[1];
  v[0] = (float)pos[0] + (float)ofs[0];
  v[2] = (float)pos[2] + (float)ofs[2];
  if (P76_InBox(v, (const uint8_t *)P82_LightGrid, P82_CellCX, P82_CellCY) == 0) return;
  int32_t gh = P100_RoadHeightF(v);
  if (G6_00B5A778 == 0) P102_HudF4 += 2;
  if (0x3f < P102_HudF4) P102_HudF4 = 0;
  v[0] = v[0] - P44_CamX;
  v[1] = ((float)(-0x280 - gh) - (float)ofs[1]) - P44_CamY;
  v[2] = v[2] - P44_CamZ;
  P44_MatPtr = (float *)P44_ViewMatT;
  P44_Xform(v);
  if (shape == 0x00573f08u) v[0] += (float)(P102_HudF4 << 2);
  v[0] += (float)scr[0];
  v[1] += (float)(scr[1] + P102_HudF4 * 4);
  v[2] += (float)scr[2];
  if (!(50.0f <= v[2])) return;
  int32_t zi = (int32_t)lrintf(v[2]);
#ifndef RE_HOOK_BUILD
  if (zi < 0 || zi >= (int32_t)(sizeof P12_00ba53a0 / sizeof P12_00ba53a0[0])) return;
#endif
  float w = P12_00ba53a0[zi], f = P43_ScaleA * w;
  p85_rv a, b, c;
  memset(&a, 0, sizeof a); memset(&b, 0, sizeof b); memset(&c, 0, sizeof c);
  a.r = b.r = c.r = 255.0f;
  a.oow = b.oow = c.oow = w;
  state_flat();
  if (P85_BlendCur != 0) { if (P85_BlendFn) P85_BlendFn(4, 0, 4, 0); P85_BlendCur = 0; P69_BlendOn = 0; }
  const uint8_t *sh = (const uint8_t *)re_ptr(shape);
#ifndef RE_HOOK_BUILD
  if (sh == NULL) return;
#endif
  const uint8_t *vt = (const uint8_t *)re_rd_ptr(sh), *ix = (const uint8_t *)re_rd_ptr(sh + 4);
  int32_t n = rd32(sh + 8);
#ifndef RE_HOOK_BUILD
  if (vt == NULL || ix == NULL) return;
#endif
  for (int32_t t = 0; t < n; t++, ix += 3) {
    a.x = ((v[0] + rdf(vt + ix[0] * 0x10)) * f + P43_OffX) - SNAP; a.y = ((v[1] + rdf(vt + ix[0] * 0x10 + 4)) * f + P43_OffY) - SNAP;
    b.x = ((v[0] + rdf(vt + ix[1] * 0x10)) * f + P43_OffX) - SNAP; b.y = ((v[1] + rdf(vt + ix[1] * 0x10 + 4)) * f + P43_OffY) - SNAP;
    c.x = ((v[0] + rdf(vt + ix[2] * 0x10)) * f + P43_OffX) - SNAP; c.y = ((v[1] + rdf(vt + ix[2] * 0x10 + 4)) * f + P43_OffY) - SNAP;
    raster(&a, &b, &c);
  }
}

/* ---- 004d7c46 / 004d7deb: прямоугольник 0xRRGGBB двумя треугольниками (смешивание 0 / 3), после — состояние «грязное» (-1) ---- */
static void fill_rect(float x, float y, float w, float h, uint32_t rgb, int blend) {
  state_flat();
  if (blend == 0) { if (P85_BlendCur != 0) { if (P85_BlendFn) P85_BlendFn(4, 0, 4, 0); P85_BlendCur = 0; P69_BlendOn = 0; } }
  else blend3();
  p85_rv a, b, c;
  memset(&a, 0, sizeof a); memset(&b, 0, sizeof b); memset(&c, 0, sizeof c);
  float r = (float)((int32_t)(rgb & 0xff0000) >> 16), g = (float)((int32_t)(rgb & 0xff00) >> 8), bl = (float)(rgb & 0xff);
  a.r = b.r = c.r = r; a.g = b.g = c.g = g; a.b = b.b = c.b = bl;
  a.x = x; a.y = y; b.x = x + w; b.y = y + h; c.x = x; c.y = y + h;
  a.oow = b.oow = c.oow = (P55_BDFA18 == 0) ? OOW_LO : 1.0f;
  raster(&a, &b, &c);
  a.x = x; a.y = y; b.x = x + w; b.y = y; c.x = x + w; c.y = y + h;
  raster(&a, &b, &c);
  P85_StateDirty = -1;
}
void P108_FillRect(float x, float y, float w, float h, uint32_t rgb) { fill_rect(x, y, w, h, rgb, 0); }
void P108_FillRectB(float x, float y, float w, float h, uint32_t rgb) { fill_rect(x, y, w, h, rgb, 3); }

/* ---- 00507eea: текстурный прямоугольник карты (страница tex, uv u0,v0..u1,v1 с поправкой 0.5), вершины через P94_MapToScreen,
   grDrawPolygonVertexList (01270e78) по имени из P33 ---- */
#ifdef RE_HOOK_BUILD
#  define P108_STD __attribute__((stdcall))
#else
#  define P108_STD
#endif
static void *glide_proc(const char *name) {
  for (int i = 0; i < P33_GlideCount(); i++)
    if (strcmp(P33_GlideName(i), name) == 0) return P33_GlideProc(i);
  return NULL;
}
void P108_MapTexRect(float x, float y, float w, float h, float u0, float v0, float u1, float v1, int32_t tex) {
  float k = (P55_BDFA18 == 0) ? 0.015625f : 1.0f;
  u1 = u1 - 0.5f; v1 = v1 - 0.5f;
  if (255.0f < u1) u1 = 255.0f;
  if (255.0f < v1) v1 = 255.0f;
  float v[4][15];   /* 00 — (x+w, y+h), 1 — (x, y+h), 2 — (x, y), 3 — (x+w, y) */
  memset(v, 0, sizeof v);
  const float px[4] = { x + w, x, x, x + w }, py[4] = { y + h, y + h, y, y };
  const float su[4] = { u1 * k, (u0 + 0.5f) * k, (u0 + 0.5f) * k, u1 * k }, tv[4] = { v1 * k, v1 * k, (v0 + 0.5f) * k, (v0 + 0.5f) * k };
  for (int i = 0; i < 4; i++) {
    v[i][0] = px[i]; v[i][1] = py[i];
    v[i][3] = v[i][4] = v[i][5] = v[i][7] = 255.0f;
    v[i][8] = k; v[i][9] = su[i]; v[i][10] = tv[i];
  }
  if (tex != P86_CurTex) {
    P86_CurTex = tex;
#ifndef RE_HOOK_BUILD
    if (tex >= 0 && tex < 0x100)
#endif
    if (P86_TexSrc) P86_TexSrc(0, (uint32_t)rd32(&g_01145a60[tex * 0x10 + 8]), 3, (uint32_t)rd32(&g_01145a60[tex * 0x10 + 0xc]));
  }
  if (P85_StateDirty != 4) { if (P85_StateFn) P85_StateFn(3, 1, 0, 1, 0); P85_StateDirty = 4; }
  if (P85_BlendCur != 0) { if (P85_BlendFn) P85_BlendFn(4, 0, 4, 0); P85_BlendCur = 0; P69_BlendOn = 0; }
  P94_MapToScreen(&v[0][0], &v[0][1]);
  P94_MapToScreen(&v[1][0], &v[1][1]);
  P94_MapToScreen(&v[2][0], &v[2][1]);
  P94_MapToScreen(&v[3][0], &v[3][1]);
  void (P108_STD *f)(int32_t, const void *) = (void (P108_STD *)(int32_t, const void *))glide_proc("_grDrawPolygonVertexList@8");
  if (f != NULL) f(4, v);
}
