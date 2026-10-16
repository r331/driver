/* v1.52 (см. ported107.h). Стандарт указателей v1.42: записи .data (CARLIGHT, пункты меню, цвета) — по адресу через re_ptr; обработчики меню — re_fn. */
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

#ifdef RE_HOOK_BUILD
#  define P107_STD __attribute__((stdcall))
#  define P107_KEY(a) (*(uint8_t *)(uintptr_t)(a))
#else
#  define P107_STD
#  define P107_KEY(a) KeyState[(a) - 0x00d04b00]
#endif

#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P107_SprV")
#undef P107_SprV
#pragma push_macro("P107_SprV") /*gvi*/
#undef P107_SprV /*gvi*/
p107_vblk_t P107_SprV;
#pragma pop_macro("P107_SprV") /*gvi*/
#pragma pop_macro("P107_SprV")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P107_DDE6")
#undef P107_DDE6
#pragma push_macro("P107_DDE6") /*gvi*/
#undef P107_DDE6 /*gvi*/
uint8_t P107_DDE6;
#pragma pop_macro("P107_DDE6") /*gvi*/
#pragma pop_macro("P107_DDE6")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P107_SteerK")
#undef P107_SteerK
#pragma push_macro("P107_SteerK") /*gvi*/
#undef P107_SteerK /*gvi*/
int32_t P107_SteerK;
#pragma pop_macro("P107_SteerK") /*gvi*/
#pragma pop_macro("P107_SteerK")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P107_NavCnt")
#undef P107_NavCnt
#pragma push_macro("P107_NavCnt") /*gvi*/
#undef P107_NavCnt /*gvi*/
int32_t P107_NavCnt;
#pragma pop_macro("P107_NavCnt") /*gvi*/
#pragma pop_macro("P107_NavCnt")
#endif
#ifndef RE_HOOK_BUILD
#pragma push_macro("P107_HornVol") /*gvi*/
#undef P107_HornVol /*gvi*/
int32_t P107_HornVol = -10000;   /* .data 005603cc */
#pragma pop_macro("P107_HornVol") /*gvi*/
#pragma push_macro("P107_NavWait") /*gvi*/
#undef P107_NavWait /*gvi*/
int32_t P107_NavWait = 10;       /* .data 005755bc */
#pragma pop_macro("P107_NavWait") /*gvi*/
#pragma push_macro("P107_NavRep") /*gvi*/
#undef P107_NavRep /*gvi*/
int32_t P107_NavRep = 10;        /* .data 005755c4 */
#pragma pop_macro("P107_NavRep") /*gvi*/
#endif

static int32_t rd32(const void *p) { int32_t v; memcpy(&v, p, 4); return v; }
static float rdf(const void *p) { float v; memcpy(&v, p, 4); return v; }
static void wr32(void *p, int32_t v) { memcpy(p, &v, 4); }
static void wrf(void *p, float v) { memcpy(p, &v, 4); }
static const float OOW_LO = 0.015625f;   /* 0x3c800000 */

static void *glide_proc(const char *name) {
  for (int i = 0; i < P33_GlideCount(); i++)
    if (strcmp(P33_GlideName(i), name) == 0) return P33_GlideProc(i);
  return NULL;
}

/* ---- 00490f3a: следы шин (004af619) и фары (004aef57) машины трафика, затем задние огни/стоп-сигналы ---- */
void P107_TrafficLights(int32_t n, uint8_t *rec) {
  if ((rec[0xc] == 1 && rec[5] != 0 && rec[1] == 4) || rec[1] == 9) {
    if (rec[1] == 9) P102_CarTracks(n, (const int16_t *)(rec + 0x16), 1.0f);
    else {
#ifndef RE_HOOK_BUILD
      if (rec[5] <= 8)
#endif
      P102_CarTracks(n, (const int16_t *)(rec + 0x16), rdf((const uint8_t *)P12_0112da00 + (rec[5] - 1) * 0xcd8 + 0xcd4));
    }
  }
  if ((rec[0x13] & 1) == 0) {
    int32_t fl = rd32(rec + 0x28), d = rd32(rec + 0x34);
    if (rec[1] != 1 && ((fl & 0x4000) != 0 || rec[1] == 3 || rd32(rec + 0x18) < 5000)) {
      if (d == -1) P102_CarLights(n, 1);
      else if (d == 1) P102_CarLights(n, 0);
    }
  } else {
    const uint8_t *car;
#ifndef RE_HOOK_BUILD
    if (P59_CarsTab == NULL) car = (const uint8_t *)&P99_Cars[rec[0] + 1 < P99_CARS_N ? rec[0] + 1 : P99_CARS_N - 1]; else
#endif
    car = P59_CarsTab + (uint32_t)rec[0] * 0x148;
    int32_t dir = rd32(rec + 0x24);
    if ((dir & 1) == 0) {
      if (rd32(rec + 0x40) != 0x7fffffff) {
        int32_t d = rd32(rec + 0x40) - rd32(car + 0x18);
        if (d < -0x100) P102_CarLights(n, dir == 0 ? 1 : 0);
        else if (d > 0x100) P102_CarLights(n, dir == 2 ? 1 : 0);
      }
    } else if (rd32(rec + 0x44) != 0x7fffffff) {
      int32_t d = rd32(rec + 0x44) - rd32(car + 0x20);
      if (d < -0x100) P102_CarLights(n, dir == 3 ? 1 : 0);
      else if (d > 0x100) P102_CarLights(n, dir == 1 ? 1 : 0);
    }
  }
  if (rec[0x13] & 0x10) P102_CarLights(n, 0);
  if (rec[0x13] & 0x20) P102_CarLights(n, 1);
  if (rec[0x11] < 5) P106_CarTailLights(n); else P106_CarBrakeLights(n);
}

/* ---- 004221bf: освободить слот текстуры i (палитра, текстура, поверхность — Release) ---- */
void P107_TexRelease(int32_t i) {
#ifndef RE_HOOK_BUILD
  if (i < 0 || i >= 32) return;
#endif
  P32_Slot *s = &P32_Slots[i];
  if (s->bpp == -1) return;
  NoopFn0042243f();   /* "Releasing texture" */
  if (s->pal != NULL) { plat_dd_release(s->pal); s->pal = NULL; }
  if (s->tex != NULL) {
    if (P32_CurHandle == s->tex) P32_CurHandle = NULL;
    plat_dd_release(s->tex); s->tex = NULL;
  }
  if (s->surf != NULL) { plat_dd_release(s->surf); s->surf = NULL; }
  s->bpp = -1; s->has_list = 0; s->cur_id = -1; s->list = NULL; s->cur_handle = NULL;
}

/* ---- 004262ce: линия Glide между точками экрана 640×480 (масштаб P19_Scale к центру), цвет 0xRRGGBB ---- */
void P107_Line(float x0, float y0, float x1, float y1, uint32_t rgb) {
  float a[16], b[16];
  memset(a, 0, sizeof a); memset(b, 0, sizeof b);   /* z, ooz, a в оригинале не заданы (стек) */
  if (P85_StateDirty != 0) { if (P85_StateFn) P85_StateFn(1, 0, 0, 2, 0); P85_StateDirty = 0; }
  if (P85_BlendCur != 0) { if (P85_BlendFn) P85_BlendFn(4, 0, 4, 0); P85_BlendCur = 0; }
  b[0] = ((x1 / P19_DivW - P51_Half) * P19_Scale + P51_Half) * (float)P19_ScrW;
  b[1] = ((y1 / P19_DivH - P51_Half) * P19_Scale + P51_Half) * (float)P19_ScrH;
  a[0] = ((x0 / P19_DivW - P51_Half) * P19_Scale + P51_Half) * (float)P19_ScrW;
  a[1] = ((y0 / P19_DivH - P51_Half) * P19_Scale + P51_Half) * (float)P19_ScrH;
  b[3] = a[3] = (float)((int32_t)rgb >> 16 & 0xff);
  b[4] = a[4] = (float)((int32_t)rgb >> 8 & 0xff);
  b[5] = a[5] = (float)(rgb & 0xff);
  b[8] = a[8] = (P55_BDFA18 == 0) ? OOW_LO : 1.0f;
  if (P95_DrawLine) P95_DrawLine(a, b);
  P85_StateDirty = -1;
  P85_BlendCur = 0xff;
}

/* ---- 004ca98d: надпись отсчёта/финиша kind (0 «3», 1 «2», 2 «1», 3 GO, 4 CHECK, 5 FINISH) на кадре t: приближение, поворот, яркость ---- */
void P107_CountModel(int32_t kind, int32_t t) {
  uint32_t m;
  switch (kind) {
  case 0: m = P69_Num3; break;
  case 1: m = P69_Num2; break;
  case 2: m = P69_Num1; break;
  case 3: m = P69_Go; break;
  case 4: m = P69_Check; break;
  case 5: m = P69_Finish; break;
  default: return;   /* в оригинале — неинициализированная переменная */
  }
  if (m == 0) return;
  float pos[3] = { 0.0f, 0.0f, (t < 0x1e) ? (float)(t * -0x10 + 1000) : 520.0f };
  uint8_t c;
  if (t < 5) c = (uint8_t)(t * 0x32);
  else if (t < 0x15) c = 0xff;
  else c = (uint8_t)((t - 0x14) * -0x19 - 1);
  float mat[9];
  memcpy(mat, P44_ViewMatT, sizeof mat);   /* в оригинале копируются 16 dword; используются первые 9 */
  int32_t ang = (t * 0x40 - 0x400) & 0xfff;
  if (kind == 5) {
    pos[2] = (float)(t * t + 0x208);
    c = 0xff;
    ang = (t * t + 0xd8f) & 0xfff;
    if (t < 0x19) { ang = 0; c = (uint8_t)(t * 5); }
    if (t > 0x1e) c = (uint8_t)(-1 - (t * 4 - 0x78));
    if (t > 0x5d) c = 0;
  }
  P44_RotX(mat, ang);
  const uint8_t *mp = (const uint8_t *)P79_PTR(m);
#ifndef RE_HOOK_BUILD
  if (mp == NULL) return;
#endif
  uint8_t *p = (uint8_t *)P79_PTR((uint32_t)rd32(mp + 0x2c));
  uint32_t n = (uint16_t)(mp[0x16] | mp[0x17] << 8);
  while (n-- != 0) {
    if (*p == 0x32) {
      wrf(p + 0x20, (float)c); wrf(p + 0x24, (float)c); wrf(p + 0x28, (float)c);
      p += G2_TABLE_00550ACC[*p];
    } else if (*p == 0x33) {
      wrf(p + 0x28, (float)c); wrf(p + 0x2c, (float)c); wrf(p + 0x30, (float)c);
      p += G2_TABLE_00550ACC[*p];
    }
  }
  if (P85_BlendCur != 3) if (P85_BlendFn) P85_BlendFn(4, 4, 0, 0);
  P85_BlendCur = 1;
  if (FnPtr01270E80) FnPtr01270E80(0);
  P84_DrawModel(m, mat, pos, 1);
  if (FnPtr01270E80) FnPtr01270E80(2);
}

/* ---- 004a9f45 / 004aa217: прямоугольник 640×480 (P19_ScaleX/Y) — четыре GrVertex по 60 байт, grDrawPolygonVertexList(4) ---- */
static void rect4(int32_t x, int32_t y, int32_t w, int32_t h, const uint8_t *c0, const uint8_t *c1, int grad) {
  float oow = (P55_BDFA18 == 0) ? OOW_LO : 1.0f;
  if (y <= -0x201) return;
  float v[4][15];
  memset(v, 0, sizeof v);   /* z, ooz, tmu в оригинале не заданы */
  float x0 = P19_ScaleX((float)x), y0 = P19_ScaleY((float)y), x1 = P19_ScaleX((float)(x + w)), y1 = P19_ScaleY((float)(y + h));
  const float px[4] = { x0, x1, x1, x0 }, py[4] = { y0, y0, y1, y1 };
  for (int i = 0; i < 4; i++) {
    const uint8_t *c = (i < 2) ? c0 : c1;
    v[i][0] = px[i]; v[i][1] = py[i];
    v[i][3] = (float)c[0]; v[i][4] = (float)c[1]; v[i][5] = (float)c[2];
    v[i][7] = 255.0f; v[i][8] = oow;
  }
  if (P85_StateDirty != 0) { if (P85_StateFn) P85_StateFn(1, 0, 0, 2, 0); P85_StateDirty = 0; }
  if (!grad) { if (P85_BlendCur != 0) { if (P85_BlendFn) P85_BlendFn(4, 0, 4, 0); P85_BlendCur = 0; } }
  else if (P85_BlendCur != 2) { if (P85_BlendFn) P85_BlendFn(0, 6, 4, 0); P85_BlendCur = 2; }
  void (P107_STD *f)(int32_t, const void *) = (void (P107_STD *)(int32_t, const void *))glide_proc("_grDrawPolygonVertexList@8");
  if (f != NULL) f(4, v);
}
void P107_Rect(int32_t x, int32_t y, int32_t w, int32_t h, uint32_t rgb) {
  const uint8_t *c = (const uint8_t *)re_ptr(rgb);
#ifndef RE_HOOK_BUILD
  if (c == NULL) return;
#endif
  rect4(x, y, w, h, c, c, 0);
}
void P107_RectGrad(int32_t x, int32_t y, int32_t w, int32_t h, uint32_t top, uint32_t bot) {
  const uint8_t *a = (const uint8_t *)re_ptr(top), *b = (const uint8_t *)re_ptr(bot);
#ifndef RE_HOOK_BUILD
  if (a == NULL || b == NULL) return;
#endif
  rect4(x, y, w, h, a, b, 1);
}

/* ---- 00506fa0: стрелка компаса радара — три линии от центра (P56_F573FA0/A4) и крестик; смещение по городу (.data 00573f68) ---- */
void P107_Compass(void) {
  static const int32_t k_ofs[7][2] = { { -20, 0 }, { 3, 20 }, { 6, -19 }, { -6, -19 }, { 20, 0 }, { 9, 18 }, { 9, 18 } };   /* .data 00573f68 */
  int32_t city = D_00b87e30;
#ifndef RE_HOOK_BUILD
  if (city < 0 || city >= 7) return;
  if (S_00D11878 < 0 || S_00D11878 >= P99_CARS_N) return;
#endif
  uint32_t h = (uint32_t)P99_Cars[S_00D11878].heading;
#ifndef RE_HOOK_BUILD
  h &= 0xfff;
#endif
  float c = P43_Sin[0x400 + h], s = P43_Sin[h];
  if (MenuOptBDFA54 != 0) { s = P43_Sin[0]; c = P43_Sin[0x400]; }
  float ox = (float)k_ofs[city][0], oz = (float)k_ofs[city][1];
  float px = (oz * s + ox * c) * P19_Scale;
  float pz = (oz * c - ox * s) * P19_Scale;
  if (P85_StateDirty != 0) { if (P85_StateFn) P85_StateFn(1, 0, 0, 2, 0); P85_StateDirty = 0; }
  if (P85_BlendCur != 0) { if (P85_BlendFn) P85_BlendFn(4, 0, 4, 0); P85_BlendCur = 0; }
  float col = (P14_00b87e84 == 0) ? 255.0f : 220.0f;   /* 0x437f0000 / 0x435c0000 */
  P95_LineV1[3] = P95_LineV1[4] = P95_LineV1[5] = col;
  P95_LineV0[3] = P95_LineV0[4] = P95_LineV0[5] = col;
  P95_LineV1[8] = P95_LineV0[8] = (P55_BDFA18 == 0) ? OOW_LO : 1.0f;
  float f2 = px + 2.0f, f3 = pz + 2.0f;
  float f4 = (pz - px) * 171.0f * 0.0009765625f;
  float l1c = (-pz - px) * 171.0f * 0.0009765625f;
  float p[12];
  p[4] = f4 + px; p[6] = l1c + pz; p[8] = l1c + px; p[10] = -f4 + pz;
  float cross[4];
  cross[0] = (px * 20.0f + 8.0f) * 0.0625f + P56_F573FA0;
  cross[2] = (pz * 20.0f + 8.0f) * 0.0625f + P56_F573FA4;
  cross[1] = cross[3] = 0.0f;
  px += P56_F573FA0; pz += P56_F573FA4;
  p[0] = f2 * 0.25f + P56_F573FA0; p[2] = f3 * 0.25f + P56_F573FA4;
  p[4] += P56_F573FA0; p[6] += P56_F573FA4; p[8] += P56_F573FA0; p[10] += P56_F573FA4;
  for (int i = 0; i < 3; i++) {
    P95_LineV0[0] = px; P95_LineV0[1] = pz;
    P95_LineV1[0] = p[i * 4]; P95_LineV1[1] = p[i * 4 + 2];
    if (P95_DrawLine) P95_DrawLine(P95_LineV0, P95_LineV1);
  }
  P95_DrawCross(cross);
}

/* ---- 004b5049: огонь машины — запись .data 0x1c (+4 значок, +8 rgb, +0xc яркость, +0x10/+0x14 экранные x,y, +0x18 размер),
   четыре GrVertex 00b1ffd0/00b20020/00b200a0/00b201a0, два треугольника P85_RasterB ---- */
#define SV(addr) (&P107_SprV[((addr) - 0x00b1ffd0u) / 4])
void P107_CarLight(uint32_t recaddr, float k) {
  const uint8_t *r = (const uint8_t *)re_ptr(recaddr);
#ifndef RE_HOOK_BUILD
  if (r == NULL) return;
#endif
  if (rd32(r + 4) == 0 || P13_00575f30 == 0) return;
  float x = rdf(r + 0x10), y = rdf(r + 0x14);
  float f = ((float)P19_ScrW / P19_DivW) * (rdf(r + 0x18) / P19_DivC) * P19_Scale;
  if (!(0.0f <= f + x && x - f < (float)P19_ScrW && 0.0f <= f + y && y - f < (float)P19_ScrH)) return;
  const uint8_t *ic = (const uint8_t *)re_rd_ptr(r + 4);
#ifndef RE_HOOK_BUILD
  if (ic == NULL) return;
#endif
  float *A = SV(0x00b201a0), *B = SV(0x00b20020), *C = SV(0x00b1ffd0), *D = SV(0x00b200a0);
  A[0] = x - f; B[0] = f + x; C[1] = y - f; B[1] = f + y;
  C[8] = B[8] = D[8] = A[8] = k;
  if (P84_Mirror != 0) { A[0] = -A[0]; B[0] = -B[0]; }
  float cr = (float)r[8] * rdf(r + 0xc), cg = (float)r[9] * rdf(r + 0xc), cb = (float)r[10] * rdf(r + 0xc);
  C[3] = cr; C[4] = cg; C[5] = cb;
  C[0] = B[0];
  B[3] = cr; B[4] = cg; B[5] = cb;
  D[0] = A[0]; D[1] = B[1];
  D[3] = cr; D[4] = cg; D[5] = cb;
  A[1] = C[1]; A[3] = cr; A[4] = cg; A[5] = cb;
  if (ic[8] != (uint32_t)P86_CurTex) {
    P86_CurTex = ic[8];
    if (P86_TexSrc) P86_TexSrc(0, (uint32_t)rd32(&g_01145a60[ic[8] * 0x10 + 8]), 3, (uint32_t)rd32(&g_01145a60[ic[8] * 0x10 + 0xc]));
  }
  D[9] = (float)(ic[9] + 1) * A[8];
  C[10] = (float)(ic[10] + 1) * A[8];
  C[9] = (float)ic[0xb] * A[8];
  B[10] = (float)ic[0xc] * A[8];
  B[9] = C[9]; D[10] = B[10]; A[9] = D[9]; A[10] = C[10];
  if (P85_RasterB) P85_RasterB((const p85_rv *)A, (const p85_rv *)C, (const p85_rv *)B);
  if (P85_RasterB) P85_RasterB((const p85_rv *)B, (const p85_rv *)D, (const p85_rv *)A);
}
#undef SV

/* ---- 0050f304: навигация по меню — пункты по 0x14 (+5 флаги, +8 тип, +0xc обработчик, +0x10..+0x13 соседи влево/вправо/вверх/вниз).
   Возвращает новый пункт или -1 (Esc). Обработчики — re_fn по адресу. ---- */
static void nav_call(const uint8_t *t, uint32_t i) {
  re_fn_t f = re_fn((uint32_t)rd32(t + 0xc + i * 0x14));
  if (f != NULL) f();
}
static void set_cur(int32_t v) { P8_00575550 = v; G00575550 = v; P11_00575550 = v; P17_ValA = v; }
int32_t P107_MenuNav(uint32_t tab, int32_t pos) {
  if (P107_NavWait != 0) { P107_NavWait--; return pos; }
  const uint8_t *t = (const uint8_t *)re_ptr(tab);
#ifndef RE_HOOK_BUILD
  if (t == NULL) return pos;
#endif
  if (IsKeyDown(1) != 0 && (P8_00b5a764 == 0 || P8_00b5a734 != 0)) return -1;
  uint32_t p = (uint32_t)pos;
  if ((t[5 + p * 0x14] & 8) == 0) {
    if (IsKeyDown(0xcb) != 0) p = t[0x10 + p * 0x14];
    else if (IsKeyDown(0xcd) != 0) p = t[0x11 + p * 0x14];
  } else {
    uint8_t l = P107_KEY(0x00d04bcb), r = P107_KEY(0x00d04bcd);
    if (((l | r) & 0x80) == 0) { P107_NavCnt = 0; P107_NavRep = 0x28; }
    if (P107_NavCnt == 0) {
      if (l & 0x80) { nav_call(t, t[0x10 + p * 0x14]); P107_NavCnt = P107_NavRep; P107_NavRep = 3; }
      else if (r & 0x80) { nav_call(t, t[0x11 + p * 0x14]); P107_NavCnt = P107_NavRep; P107_NavRep = 3; }
    } else P107_NavCnt--;
  }
  if (IsKeyDown(200) != 0) {
    p = t[0x12 + p * 0x14];
    if (P8_00b5a768 != 0 && rd32(t + 8 + p * 0x14) == 0xa5) p = t[0x12 + p * 0x14];
  } else if (IsKeyDown(0xd0) != 0) {
    p = t[0x13 + p * 0x14];
    if (P8_00b5a768 != 0 && rd32(t + 8 + p * 0x14) == 0xa5) p = t[0x13 + p * 0x14];
  } else if (IsKeyDown(0x1c) != 0) {
    set_cur((int32_t)p);
    nav_call(t, p);
    p = (uint32_t)P8_00575550;
  }
  return (int32_t)p;
}

/* ---- 004ddaca: ввод машины car (биты keys: 1 газ назад, 2 газ, 4/8 руль, 0x10 резкий руль, 0x20 ручник, 0x40 тормоз, 0x80 круиз, 0x100 сигнал) ---- */
static int32_t imul12(int32_t v, int32_t k) { int32_t m = (int32_t)((uint32_t)v * (uint32_t)k); return (m + (int32_t)((uint32_t)(m >> 31) & 0xfffu)) >> 12; }
void P107_CarInput(int32_t car, uint32_t keys) {
  static const int32_t k_steer[32] = { 0, 0, 0, 0, 16, 16, 32, 32, 48, 48, 64, 64, 96, 96, 128, 128, 160, 160, 192, 192,
                                       224, 224, 256, 256, 288, 320, 352, 384, 460, 460, 511, 511 };   /* .data 00562420 */
#ifndef RE_HOOK_BUILD
  if (car < 0 || car >= P99_CARS_N) return;
#endif
  p99_car_t *c = &P99_Cars[car];
  if (car == 0) {
    if ((keys & 0x100) == 0) {
      if (S_00D1192C == 10) P107_DDE6 = 0;
      else P107_HornVol = -10000;
    } else {
      P71_InitNear((uint8_t *)&P99_Cars[0]);
      if (S_00D1192C == 10) {
        if (P107_DDE6 == 0) {
          if (P98_DD70 == 0) { P98_DD70 = 1; P107_HornVol = 0; }
          else { P98_DD70 = 0; P107_HornVol = -10000; }
        }
        P107_DDE6 = 1;
      } else if (P107_HornVol != 0 && (P107_HornVol += 4000, 0 < P107_HornVol)) P107_HornVol = 0;
    }
    P48_SetVoiceVolume(2, P107_HornVol);
    P14_Fn004D623B((int32_t)keys);
    P56_HudTick((int32_t)keys);
  }
  if (G6_00B87EAC != 0 && car == 0x41) { P14_Fn004D623B((int32_t)keys); P56_HudTick((int32_t)keys); }
  if ((int8_t)c->f140 > 'Z') c->f140 = 0x5a;
  if ((keys & 0x20) == 0) {
    c->f104 = 0;
    if ((keys & 0x40) == 0 || P98_C824A0 != 0) c->f108 = 0;
    else { P102_D0DDEC = 0; c->f108 = 1; }
    if (c->f108 != 0 && 0xa2000 < c->f10c) { c->f108 = 0; keys |= 2; }
  } else { P102_D0DDEC = 0; c->f104 = 1; }
  int pad = 0;
  if (car > 0x40 || car == S_00D11878) {
    if ((keys & 0x80) != 0 && P102_D0DDEC == 0) P102_D0DDEC = (c->f10c + 0x800) >> 0xc;
    if (P36_PadMode == 2) pad = P103_C4D9A4 != 0;
    else if ((P36_PrevFlag != 0 && car == 0) || (P36_PrevFlag != 0 && G6_00B87EA0 != 0 && car != 0 && P88_Mode575 == 2)) pad = 1;
    if (pad) {
      int32_t j = P36_JoyX < 0 ? -P36_JoyX : P36_JoyX;
#ifndef RE_HOOK_BUILD
      if (j > 31) j = 31;   /* в оригинале — чтение за таблицей */
#endif
      c->ffc = P36_JoyX < 0 ? -k_steer[j] : k_steer[j];
    } else {
      int32_t step = (keys & 0x10) ? 0x20 : 0x10, lim = (keys & 0x10) ? 0x1ff : 0x160;
      if ((keys & 4) != 0 && (c->ffc += step, lim < c->ffc)) c->ffc = lim;
      if ((keys & 8) != 0 && (c->ffc -= step, c->ffc < -lim)) c->ffc = -lim;
      if ((keys & 0xc) == 0) {
        if (c->ffc < -0x40) c->ffc += 0x20;
        else if (c->ffc < 0x41) c->ffc = 0;
        else c->ffc -= 0x20;
      }
    }
  }
  if ((keys & 0xc) != 0 || (pad && (P36_JoyX < -0x10 || 0x10 < P36_JoyX))) c->f140 = (uint8_t)(c->f140 + 1);
  else c->f140 = 0;
  const uint8_t *mdl = S_00D0CC60 + 0x100 + (uint32_t)c->f00[2] * 0x16c;
#ifndef RE_HOOK_BUILD
  static const uint8_t zero2[2];
  if ((uint32_t)c->f00[2] * 0x16c + 0x102 > sizeof S_00D0CC60) mdl = zero2;
#endif
  int32_t mx = (int16_t)(mdl[0] | mdl[1] << 8);
  if ((keys & 1) == 0 || (keys & 0x20) != 0) {
    if ((keys & 2) == 0) c->ff8 = 0;
    else {
      c->ff8 = mx;
      P102_D0DDEC = 0;
      if (P58_SB87EB0 != 0 && G6_00B87EA0 == 0 && c->f00[0] == 0) {
        int32_t dx = P99_Cars[0x41].pos[0] - c->pos[0], dz = P99_Cars[0x41].pos[2] - c->pos[2];
        if (dx < 0) dx = -dx;
        if (dz < 0) dz = -dz;
        int32_t d = (dx < dz) ? dz + dx / 2 : dx + dz / 2;
        d += d >> 2;
        if (d >= 0x4651) c->ff8 += 3000;
        else if (d >= 0x34bd) c->ff8 += 0x9c4;
        else if (d >= 0x2329) c->ff8 += 2000;
        else if (d >= 0x1771) c->ff8 += 0x5dc;
        else c->ff8 += 500;
      }
      if (car == 0) c->ff8 = imul12(c->ff8, P107_SteerK);
      else if (car != 0x41) goto tail;
      if (c->f143 != 0) c->ff8 = 1;
    }
  } else {
    int32_t r = -((c->f10c + 0x800) >> 0xc);
    P102_D0DDEC = 0;
    if (r < 0x17) c->ff8 = -mx;
    else c->ff8 = (-mx * (0x100 - (r - 0x16))) >> 8;
    if (c->f10c < 0 && car == 0) c->ff8 = imul12(c->ff8, P107_SteerK);
  }
tail:
  if (car == 0) {
    if (G6_00B87EA0 == 0) {
      int32_t d = P102_D0DDEC - ((c->f10c + 0x800) >> 0xc);
      if (d < 0) d = -d;
      if (0x24 < d) P102_D0DDEC = 0;
      if (P102_D0DDEC != 0) {
        c->ff8 = (P102_D0DDEC * 2 - ((c->f10c + 0x800) >> 0xc)) * 0x16;
        if (c->ff8 > 8000) c->ff8 = 8000;
        else if (c->ff8 < -8000) c->ff8 = -8000;
        if (c->ff8 < 0) c->ff8 = 0;
      }
    }
    if (0xf < S_00D1192C) c->ff8 <<= 1;
    if (MenuOptBDFA44 != 0) c->ff8 <<= 1;
  }
  c->f141 = (keys & 8) ? 1 : (keys & 4) ? 0xff : 0;
}

/* ---- 004958b7: ряд машин трафика вдоль дороги перед игроком (сторона P103_1426E0, участки 011426f8 / 011443c0 таблицы 00c12c60),
   затем заполнение промежутков припаркованными. 1 — выполнено. ---- */
static int32_t row_cell(int32_t seg, int off) {
#ifndef RE_HOOK_BUILD
  if (seg < 0 || (uint32_t)seg * 0x14 + off + 4 > sizeof P11_00c12c60) return 0;
#endif
  return rd32(&P11_00c12c60[(uint32_t)seg * 0x14 + off]);
}
static int32_t row_add(int32_t x, int32_t z, int32_t heading) {
  int32_t i = P102_TrafficAdd(x, -0xfa, z, heading, 1);
#ifndef RE_HOOK_BUILD
  if (i < 0 || i >= 0x40) return -1;
#endif
  TrafficRecs[i * 0x54 + 0xc] = 1;
  return i;
}
int32_t P107_TrafficRow(void) {
  static const int32_t k_dir[4] = { 0, 0x400, 0x800, 0xc00 };   /* .data 00551330 */
  int32_t pts[16][4];
  int32_t n = 0;
  uint8_t side = (uint8_t)P103_1426E0;
  G0113A6C0 = 0;
  int32_t x = P99_Cars[0].pos[0], z = P99_Cars[0].pos[2];
  P101_RoadNode(x, z, (int8_t)side);
  switch (side) {
  case 0: x = row_cell(G011426F8, 0) * 0x5dc; z += 30000; break;
  case 1: x += 30000; z = row_cell(G011426F8, 0xc) * -0x5dc; break;
  case 2: x = row_cell(G011426F8, 0) * 0x5dc; z -= 30000; break;
  case 3: x -= 30000; z = row_cell(G011426F8, 0xc) * -0x5dc; break;
  }
  if (P102_TrafficRoom(x, z, G011426F8, side) == 0) return 0;
  if (P103_1443C0 != -1 && P102_TrafficRoom(x, z, P103_1443C0, side) == 0) return 0;
  int32_t saved = P62_I14428C;
  P62_I14428C = 0;
  for (int32_t i = 0; i < G01144284; i++) {
#ifndef RE_HOOK_BUILD
    if (i >= 0x100) break;
#endif
    P74_FreeTraffic((int32_t)P12_01144340[i]);
  }
  G01144284 -= P104_139A28;
  int32_t hd = k_dir[(side + 2) & 3];
#define ROW_PT() do { if (n < 16) { pts[n][0] = x; pts[n][1] = 0; pts[n][2] = z; pts[n][3] = 0; n++; } } while (0)
#define ROW_STEP() do { if ((side & 1) == 0) { x += 0x5dc; z += 0x80 - (int32_t)(Rand_004D9078() & 0xff); } \
                        else { z += 0x5dc; x += 0x80 - (int32_t)(Rand_004D9078() & 0xff); } } while (0)
  for (; P103_1373D4 != 0; P103_1373D4--) {
    if (P47_NoFlags(x, z) != 0) {
      int32_t i = row_add(x, z, hd + (0x600 - (int32_t)(Rand_004D9078() & 0x3ff)));
      if (i >= 0) wr32(&TrafficRecs[i * 0x54 + 0x28], G011426F8);
      ROW_PT();
    }
    ROW_STEP();
    G01144284--;
  }
  if (P103_1443C0 == -1) { G01145934 = P104_12B26C; P62_I14428C = saved; return 1; }
  if ((int8_t)P103_1426F0 == 0) {
    if (P47_NoFlags(x, z) != 0) {
      int32_t i = row_add(x, z, hd + (0x600 - (int32_t)(Rand_004D9078() & 0x3ff)));
      if (i >= 0) { wr32(&TrafficRecs[i * 0x54 + 0x28], -1); TrafficRecs[i * 0x54 + 2] = 1; }
      ROW_PT();
    }
    G01144284--;
  }
  switch (side) {
  case 0: case 2: x = row_cell(P103_1443C0, 0) * 0x5dc; break;
  case 1: case 3: z = row_cell(P103_1443C0, 0xc) * -0x5dc; break;
  }
  for (; G01144284 != 0; G01144284--) {
    if (P47_NoFlags(x, z) != 0) {
      int32_t i = row_add(x, z, hd + (0x600 - (int32_t)(Rand_004D9078() & 0x3ff)));
      if (i >= 0) wr32(&TrafficRecs[i * 0x54 + 0x28], P103_1443C0);
      ROW_PT();
    }
    ROW_STEP();
  }
  if (WI00B87E2C != 0) {
    int k = (side & 1) ? 2 : 0;
    for (int32_t a = 0; a < n - 1; a++)
      for (int32_t b = 0; b < n - 1; b++)
        if (pts[b + 1][k] < pts[b][k]) { int32_t t[4]; memcpy(t, pts[b], 16); memcpy(pts[b], pts[b + 1], 16); memcpy(pts[b + 1], t, 16); }
    if (1 < n) {
      int32_t hx = (WI00B87E2C == 1) ? 0x40 : 0x440;
      if ((side & 1) == 0) {
        z = pts[0][2] - 0x3b6;
        for (x = pts[0][0] + 0x2ee; x < pts[n - 1][0]; x += 0x5dc)
          if (P47_NoFlags(x, z) != 0) row_add(x, z, hd + (hx - (int32_t)(Rand_004D9078() & 0x1f)));
      } else {
        x = pts[0][0] - 0x3b6;
        for (z = pts[0][2] - 0x2ee; z < pts[n - 1][2]; z += 0x5dc)
          if (P47_NoFlags(x, z) != 0) row_add(x, z, hd + (hx - (int32_t)(Rand_004D9078() & 0x1f)));
      }
    }
  }
#undef ROW_PT
#undef ROW_STEP
  G01145934 = P104_12B26C;
  P62_I14428C = saved;
  return 1;
}
