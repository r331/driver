/* v1.62, ported117 — см. ported117.h */
#include "ported117.h"
#include "ported118.h"
#include "p117_data.h"
#include "reptr.h"
#include "ported116.h"
#include "ported102.h"
#include "ported56.h"
#include "ported74.h"
#include "ported43.h"
#include "ported44.h"
#include "ported94.h"
#include "ported72.h"
#include "ported79.h"
#include "ported26.h"
#include "ported62.h"
#include "ported13.h"
#include "menustate.h"
#include "ported11.h"
#include "ported12.h"
#include "ported85.h"
#include "ported86.h"
#include "ported69.h"
#include "ported19.h"
#include "ported55.h"
#include "ported6.h"
#include "ported14.h"
#include "ported95.h"
#include "ported100.h"
#include "ported107.h"
#include "ported108.h"
#include "ported109.h"
#include "ported70.h"
#include "ported58.h"
#include "ported110.h"
#include "ported114.h"
#include "ported99.h"
#include "ported57.h"
#include "ported65.h"
#include "smallfuncs.h"
#include "unported.h"
#include "engine.h"
#include "ported45.h"
#include "globalsets.h"
#include <math.h>
#include <string.h>

#ifndef RE_HOOK_BUILD
p117_menuA_t P117_MenuA = P117_MENUA_INIT;
p117_menuB_t P117_MenuB = P117_MENUB_INIT;
p117_menuC_t P117_MenuC = P117_MENUC_INIT;
#endif
GAME_VAR_DEF(p117_i16_t, P117_PrevCorn, 0x00b5c858)
GAME_VAR_DEF(p117_i4_t, P117_SkidStA, 0x00b5c8f4)
GAME_VAR_DEF(p117_u4_t, P117_SkidLastA, 0x00b5c844)
GAME_VAR_DEF(p117_i4_t, P117_SkidStB, 0x00b5c824)
GAME_VAR_DEF(p117_u4_t, P117_SkidLastB, 0x00b5c834)
GAME_VAR_DEF(p117_clip_fn, P117_ClipFn, 0x01270d30)

static uint32_t rd_u32(const uint8_t *p) { uint32_t v; memcpy(&v, p, 4); return v; }
static void wr_f(uint8_t *p, float f) { memcpy(p, &f, 4); }

/* ---- общий хвост 0051dd1b / 0051e1b7 ---- */
typedef struct {
  uint8_t *tab; int32_t *cnt, *start, *st; uint32_t *last; int32_t flag; int32_t set5624;
} skid_side_t;
static void skid_rec(const skid_side_t *s, int32_t w, int32_t ang,
                     float bx, float by, float bz, float ax, float ay, float az,
                     const float *pos, int32_t rx, int32_t rz) {
  int32_t i = -ang & 0xfff;
  float c = P43_Sin[0x400 + i] * 50.0f;   /* .rdata 0054609c = 50.0 */
  float sn = P43_Sin[i] * 50.0f;
  int32_t k = s->start[w] + s->cnt[w];
  if (0xff < k) k -= 0x100;
#ifndef RE_HOOK_BUILD
  if (k < 0 || k > 0xff) return;   /* начало вне 0..0xff (в оригинале — запись за таблицей) */
#endif
  uint8_t *rec = s->tab + k * 0x48 + w * 0x4800;
  if (s->cnt[w] == 0x100) { s->start[w]++; if (0xff < s->start[w]) s->start[w] -= 0x100; }
  else s->cnt[w]++;
  int16_t v;
  if (s->st[w] == 1 && (uint8_t)s->flag == 1) {
    rec[0] = 1; v = 2; memcpy(rec + 2, &v, 2);
    uint8_t *pr = s->last[w] != 0 ? (uint8_t *)re_ptr(s->last[w]) : NULL;
    if (pr != NULL) { int16_t q; memcpy(&q, pr + 2, 2); if (q == 2) { q = 1; memcpy(pr + 2, &q, 2); } }
  } else { rec[0] = 0; v = 0; memcpy(rec + 2, &v, 2); }
  /* четвёртые слова точек (+0x14/+0x24/+0x34/+0x44) в оригинале — мусор стека; здесь не трогаются */
  wr_f(rec + 0x08, bx + sn); wr_f(rec + 0x0c, by); wr_f(rec + 0x10, bz + c);
  wr_f(rec + 0x18, bx);      wr_f(rec + 0x1c, by); wr_f(rec + 0x20, bz);
  wr_f(rec + 0x28, ax + sn); wr_f(rec + 0x2c, ay); wr_f(rec + 0x30, az + c);
  wr_f(rec + 0x38, ax);      wr_f(rec + 0x3c, ay); wr_f(rec + 0x40, az);
  float m[4] = { 0, 0, 0, 0 };
  if (MenuVar55384C != 0) { P94_Wobble(m, 0); P44_XformT(m); }
  float p[3] = { pos[0], pos[1], pos[2] };
  int32_t fr = P62_Frame & 2;
  int32_t hard = 0;
  if (P72_RoadLookup(rx, rz) != 0) {
    uint32_t ma = (P72_Id < 1126) ? P79_ModelTab[P72_Id] : 0;
    if (ma != 0) {
      const uint8_t *mdl = (const uint8_t *)P79_PTR(ma);
      if (mdl != NULL && (rd_u32(mdl + 8) & 0x4000) != 0) hard = 1;
    }
  }
  if (!hard) {
    rec[4] = 0;
    if (P26_FxA == 0 && fr != 0) P118_SkidFx(p, 100, 500, 2, 0, m, 0);
    if (s->set5624) P102_5624A4 = 1;
  } else {
    if (P26_FxA == 0 && fr != 0) P118_SkidFx(p, 100, 500, 3, 0, m, 0);
    rec[4] = 1;
    if (s->set5624) P102_5624A4 = 0;
  }
  s->st[w] = 1;
  s->last[w] = re_addr(rec);
}

/* ---- 0051dd1b ---- */
void P117_SkidRecA(int32_t w) {
  if (P13_00575ec0 == 0) return;
#ifndef RE_HOOK_BUILD
  if (w < 0 || w > 3) return;
#endif
  const int32_t *cur = &P102_Corners[w * 4], *prv = &P117_PrevCorn[w * 4];
  int32_t ang = P44_Atan2(prv[2] - cur[2], prv[0] - cur[0]);
  skid_side_t s = { &P116_SkidRecA[0], P74_SkidD, P74_SkidB, P117_SkidStA, P117_SkidLastA, P102_D0DD80, 1 };
  float pos[3] = { (float)cur[0], (float)-cur[1], (float)cur[2] };
  skid_rec(&s, w, ang, (float)prv[0], (float)-prv[1] - 20.0f, (float)prv[2],   /* .rdata 00546118 = 20.0 */
           (float)cur[0], (float)-cur[1] - 20.0f, (float)cur[2], pos, cur[0], cur[2]);
}

/* ---- 0051e1b7 ---- */
void P117_SkidRecB(int32_t w, const float *q) {
  if (P13_00575ec0 == 0) return;
#ifndef RE_HOOK_BUILD
  if (w < 0 || w > 3 || q == NULL) return;
#endif
  float px = p116_f((int32_t)P56_Blk16[w * 4]), py = p116_f((int32_t)P56_Blk16[w * 4 + 1]), pz = p116_f((int32_t)P56_Blk16[w * 4 + 2]);
  P11_00ba52d0 = (int32_t)lrintf(px - q[0]); int32_t dx = P11_00ba52d0;
  P11_00ba52d0 = (int32_t)lrintf(pz - q[2]);
  int32_t ang = P44_Atan2(P11_00ba52d0, dx);
  skid_side_t s = { &P116_SkidRecB[0], P74_SkidC, P74_SkidA, P117_SkidStB, P117_SkidLastB, P102_D04D14, 0 };
  float pos[3] = { q[0], -q[1], q[2] };
  P11_00ba52d0 = (int32_t)lrintf(q[2]); int32_t rz = P11_00ba52d0;
  P11_00ba52d0 = (int32_t)lrintf(q[0]);
  skid_rec(&s, w, ang, px, -py - 20.0f, pz, q[0], -q[1] - 20.0f, q[2], pos, P11_00ba52d0, rz);
}

/* ---- 00504cad: радар ---- */
void P117_Radar(void) {
  P12_Fn00426580(0x17);
  uint8_t *ic = P100_RadarIcon;
  if (ic == NULL || P109_C8089C == 0) return;
  P100_RadarMap(0);
  P11_00ba52d0 = (int32_t)lrintf(p116_f(0x3dcccccd) * (float)P19_ScrW * P19_Scale);   /* .rdata 005461bc = 0.1 */
  int32_t r = P11_00ba52d0;
  float f = p116_f(0x3e11999a) * (float)P19_ScrW * P19_Scale;                       /* .rdata 00546a2c = 0.1421875 */
  int32_t d = r * 2, t = (0.5f <= P19_Scale) ? 2 : 1;
  int32_t x0 = (int32_t)(P56_F573FA0 - (float)r), y0 = (int32_t)(P56_F573FA4 - (float)r);
  int32_t x1 = (int32_t)(P56_F573FA0 + (float)r), y1 = (int32_t)(P56_F573FA4 + (float)r);
  P108_FillRect((float)(x0 - t), (float)(y0 - t), (float)(d + t * 2), (float)t, 0x111111);
  P108_FillRect((float)(x0 - t), (float)y1, (float)(d + t * 2), (float)t, 0x111111);
  P108_FillRect((float)(x0 - t), (float)y0, (float)t, (float)d, 0x111111);
  P108_FillRect((float)x1, (float)y0, (float)t, (float)d, 0x111111);
  float sn, cs;
  if (MenuOptBDFA54 != 0) { sn = P43_Sin[0x800]; cs = P43_Sin[0xc00]; }
  else {
    int32_t h = (G6_00B87EAC == 0) ? P94_Heading : P99_Cars[0x41].ang[1];
    h = -(h + 0x800) & 0xfff;
    sn = P43_Sin[h]; cs = P43_Sin[0x400 + h];
  }
  float cx = P56_F573FA0, cy = P56_F573FA4;
  p85_rv v[4];
  memset(v, 0, sizeof v);
  v[0].x = cx + (cs * -f - sn * -f); v[0].y = cy + cs * -f + sn * -f;
  v[1].x = cx + (cs * f - sn * -f);  v[1].y = cy + cs * -f + sn * f;
  v[2].x = cx + (cs * f - sn * f);   v[2].y = cy + cs * f + sn * f;
  v[3].x = cx + (cs * -f - sn * f);  v[3].y = cy + (cs * f + sn * -f);
  float k = (P55_BDFA18 == 0) ? 0.015625f : 1.0f;
  float full = (P14_00b87e84 == 0) ? 255.0f : 155.0f;
  float rr = full, gg = full, bb = full;
  if (!((int32_t)P14_00d11a5c < 0x2aa || P95_AmbN < 1)) {
    if (P102_B52A3C < 0x41) { float l = ((float)((P102_B52A3C >> 1) + 0x20) / 64.0f) * full; rr = l; gg = l; }
    else { float l = ((float)(((P102_B52A3C - 0x40) >> 1) + 0x20) / 64.0f) * full; gg = l; bb = l; }
  }
  if (G6_00B5A778 == 0) P102_B52A3C = (P102_B52A3C - 8) & 0x7f;
  for (int i = 0; i < 4; i++) { v[i].r = rr; v[i].g = gg; v[i].b = bb; v[i].oow = k; }
  if ((int32_t)ic[8] != P86_CurTex) {
    P86_CurTex = ic[8];
    if (P86_TexSrc) P86_TexSrc(0, rd_u32(&g_01145a60[ic[8] * 0x10 + 8]), 3, rd_u32(&g_01145a60[ic[8] * 0x10 + 0xc]));
  }
  float u = (float)ic[9], w = (float)ic[10], uw = (float)((uint32_t)ic[9] + ic[0xb]), vh = (float)((uint32_t)ic[10] + ic[0xc]);
  v[0].tmu[0] = uw * k; v[0].tmu[1] = vh * k;
  v[1].tmu[0] = u * k;  v[1].tmu[1] = vh * k;
  v[2].tmu[0] = u * k;  v[2].tmu[1] = w * k;
  v[3].tmu[0] = uw * k; v[3].tmu[1] = w * k;
  if (P85_StateDirty != 4) { if (P85_StateFn) P85_StateFn(3, 1, 0, 1, 0); P85_StateDirty = 4; }
  if (P85_BlendCur != 0) { if (P85_BlendFn) P85_BlendFn(4, 0, 4, 0); P85_BlendCur = 0; P69_BlendOn = 0; }
  if (P117_ClipFn) P117_ClipFn(x0, y0, x1, y1);
  if (P85_RasterB) { P85_RasterB(&v[0], &v[1], &v[2]); P85_RasterB(&v[2], &v[3], &v[0]); }
  P12_Fn00426580(0);
  P56_DrawSprite();
  P58_DrawObjs();
  P109_RadarTraffic();
  P70_RadarNearest();
  P107_Compass();
  P11_00ba52d0 = (int32_t)lrintf(P110_ClipY1); int32_t cy1 = P11_00ba52d0;
  P11_00ba52d0 = (int32_t)lrintf(P110_ClipX1); int32_t cx1 = P11_00ba52d0;
  P11_00ba52d0 = (int32_t)lrintf(P110_ClipY0); int32_t cy0 = P11_00ba52d0;
  P11_00ba52d0 = (int32_t)lrintf(P110_ClipX0);
  if (P117_ClipFn) P117_ClipFn(P11_00ba52d0, cy0, cx1, cy1);
}

/* ---- 00502fe2: полноэкранная карта ---- */
void P117_FullMap(void) {
  if (P102_MapIcon2 == NULL) { DebugLog("DrawFullscreenMap: No target texture"); return; }
  if (P99_C80880 == NULL) { DebugLog("DrawFullscreenMap: No source map"); return; }
  uint32_t ti = P102_MapIcon2[8];
  void *saved = NULL;
  int swap = (P100_Radar16 == 0);
#ifndef RE_HOOK_BUILD
  if (ti >= 16) swap = 0;   /* в native таблица страниц P65_Texs — 16 записей */
#endif
  if (swap) { saved = P65_Texs[ti].p; P65_Texs[ti].p = (void *)&P56_Page[0]; }
  P12_Fn00426580(0x17);
  int32_t nc = P57_ScrW >> 8, nr = S_00C808A0 >> 8;
  if ((P57_ScrW & 0xff) != 0) nc++;
  if ((S_00C808A0 & 0xff) != 0) nr++;
  for (int32_t row = 0; row < nr; row++) {
    float h = (float)(S_00C808A0 - row * 0x100);
    if (255.0f < h) h = 256.0f;
    for (int32_t col = 0; col < nc; col++) {
      float w = (float)(P57_ScrW - col * 0x100);
      if (255.0f < w) w = 256.0f;
      if (P100_Radar16 == 0) {
        P56_BmpPage(P102_MapIcon2[8], (const uint8_t *)P99_C80880, col << 8, row << 8, (int32_t)w, (int32_t)h, P57_ScrW);
        P108_MapTexRect((float)col * 256.0f, (float)row * 256.0f, w, h, 0, 0, w, h, P102_MapIcon2[8]);
      } else {
#ifndef RE_HOOK_BUILD
        if (P100_RadarIcon == NULL) continue;
#endif
        P62_DownloadPage(P100_RadarIcon[8], (const uint16_t *)P99_C80880, col << 8, row << 8, (int32_t)w, (int32_t)h, P57_ScrW);
        P108_MapTexRect((float)col * 256.0f, (float)row * 256.0f, w, h, 0, 0, w, h, P100_RadarIcon[8]);
      }
    }
  }
  if (P100_Radar16 == 0) {
    if (swap) { P65_Texs[ti].p = saved; P12_Fn0048A46B((int32_t)ti, (int32_t)(uintptr_t)saved); }
  } else P100_RadarMap(1);
  P114_RadarMarks();
}

/* ---- 0040ce31: список надписей меню (P45_PtrA → записи 16 байт: s16 x, y; [4] шрифт, [5] флаги, [8] адрес строки, 0 — конец; [0xc..0xe] цвет) ---- */
static int32_t f_bits(float f) { int32_t v; memcpy(&v, &f, 4); return v; }
void P117_TextList(void) {
  if (P45_PtrA == 0) return;
  const uint8_t *e = (const uint8_t *)re_ptr(P45_PtrA);
#ifndef RE_HOOK_BUILD
  if (e == NULL) return;
#endif
  GlobalSet0040B0A4();
  for (; rd_u32(e + 8) != 0; e += 0x10) {
    MenuSetColor(e[0xc], e[0xd], e[0xe]);
    int16_t x, y; memcpy(&x, e, 2); memcpy(&y, e + 2, 2);
    float fy = (e[4] < 2) ? (float)y - 1.0f : (float)y - 3.0f;   /* .rdata 00546020 = 1.0, 00546034 = 3.0 */
    MenuSetVals5D77C0(f_bits((float)x), f_bits(fy), e[4], e[5]);
    P116_Text(rd_u32(e + 8));
  }
}
