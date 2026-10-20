#include <stdio.h>
#include <stdlib.h>
/* v1.62, ported117 — см. ported117.h */
/* ported117.c — tyre skid marks (two ring buffers of 4 wheels x 256 records), the HUD radar, the
   full-screen map, and the static menu text list.  English summary of ported117.h:
   a skid record (0x48 bytes) is one quad of a skid strip — two cross-lines 50 units wide through the
   previous and the current wheel contact point — plus a surface flag that picks the dust/spark effect. */
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
#pragma push_macro("P117_MenuA") /*gvi*/
#undef P117_MenuA /*gvi*/
p117_menuA_t P117_MenuA = P117_MENUA_INIT;
#pragma pop_macro("P117_MenuA") /*gvi*/
#pragma push_macro("P117_MenuB") /*gvi*/
#undef P117_MenuB /*gvi*/
p117_menuB_t P117_MenuB = P117_MENUB_INIT;
#pragma pop_macro("P117_MenuB") /*gvi*/
#pragma push_macro("P117_MenuC") /*gvi*/
#undef P117_MenuC /*gvi*/
p117_menuC_t P117_MenuC = P117_MENUC_INIT;
#pragma pop_macro("P117_MenuC") /*gvi*/
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P117_PrevCorn")
#undef P117_PrevCorn
#pragma push_macro("P117_PrevCorn") /*gvi*/
#undef P117_PrevCorn /*gvi*/
p117_i16_t P117_PrevCorn;
#pragma pop_macro("P117_PrevCorn") /*gvi*/
#pragma pop_macro("P117_PrevCorn")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P117_SkidStA")
#undef P117_SkidStA
#pragma push_macro("P117_SkidStA") /*gvi*/
#undef P117_SkidStA /*gvi*/
p117_i4_t P117_SkidStA;
#pragma pop_macro("P117_SkidStA") /*gvi*/
#pragma pop_macro("P117_SkidStA")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P117_SkidLastA")
#undef P117_SkidLastA
#pragma push_macro("P117_SkidLastA") /*gvi*/
#undef P117_SkidLastA /*gvi*/
p117_u4_t P117_SkidLastA;
#pragma pop_macro("P117_SkidLastA") /*gvi*/
#pragma pop_macro("P117_SkidLastA")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P117_SkidStB")
#undef P117_SkidStB
#pragma push_macro("P117_SkidStB") /*gvi*/
#undef P117_SkidStB /*gvi*/
p117_i4_t P117_SkidStB;
#pragma pop_macro("P117_SkidStB") /*gvi*/
#pragma pop_macro("P117_SkidStB")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P117_SkidLastB")
#undef P117_SkidLastB
#pragma push_macro("P117_SkidLastB") /*gvi*/
#undef P117_SkidLastB /*gvi*/
p117_u4_t P117_SkidLastB;
#pragma pop_macro("P117_SkidLastB") /*gvi*/
#pragma pop_macro("P117_SkidLastB")
#endif
GAME_VAR_DEF(p117_clip_fn, P117_ClipFn, 0x01270d30)

#define SKID_RECS        0x100    /* records per wheel ring */
#define SKID_REC_SIZE    0x48
#define SKID_WHEEL_SIZE  0x4800   /* SKID_RECS * SKID_REC_SIZE */
#define SKID_ON          0x00     /* u8: 1 = record continues a running strip (joined to the previous) */
#define SKID_STATE       0x02     /* int16: 2 = latest piece of a strip (turned to 1 when the next joins), 0 = single */
#define SKID_SURFACE     0x04     /* u8: 1 = cell model has flag 0x4000 (P118_SkidFx effect 3), 0 = normal (effect 2) */
#define SKID_PTS         0x08     /* 4 points x {x, y, z, unused}: prev+side, prev, cur+side, cur */
#define SKID_HALF_WIDTH  50.0f    /* .rdata 0054609c: strip width across the direction of travel */
#define SKID_LIFT        20.0f    /* .rdata 00546118: strip drawn 20 units above the contact point (y up = -y) */
#define MDL_F_HARD       0x4000   /* model flags word +8: surface that gives effect 3 (TODO(RE): unsure — hard/concrete?) */
#define RADAR_FRAME_COL  0x111111 /* radar border colour */

static uint32_t rd_u32(const uint8_t *p) { uint32_t v; memcpy(&v, p, 4); return v; }
static void wr_f(uint8_t *p, float f) { memcpy(p, &f, 4); }

/* ---- общий хвост 0051dd1b / 0051e1b7 ---- */
typedef struct {
  uint8_t *tab; int32_t *cnt, *start, *st; uint32_t *last; int32_t flag; int32_t set5624;
} skid_side_t;
/* Shared tail of P117_SkidRecA / P117_SkidRecB: appends one record to wheel w's ring (start/cnt, 256
   entries; when full the oldest is overwritten), joins it to the running strip if the wheel was
   already skidding and s->flag == 1, writes the four strip points (b = previous point, a = current;
   side offset = 50 * (sin, cos) of -ang), applies the camera wobble when MenuVar55384C is set, picks the
   surface from the road cell's model and spawns dust (every other frame, unless P26_FxA).
   s->set5624: also set P102_5624A4 (1 normal, 0 hard surface) — only the A side does. */
static void skid_rec(const skid_side_t *s, int32_t w, int32_t ang,
                     float bx, float by, float bz, float ax, float ay, float az,
                     const float *pos, int32_t rx, int32_t rz) {
  int32_t i = -ang & 0xfff;
  float c = P43_Sin[0x400 + i] * SKID_HALF_WIDTH;   /* cos: sin table at angle + 90 deg */
  float sn = P43_Sin[i] * SKID_HALF_WIDTH;
  int32_t k = s->start[w] + s->cnt[w];               /* ring slot for the new record */
  if (0xff < k) k -= SKID_RECS;
#ifndef RE_HOOK_BUILD
  if (k < 0 || k > 0xff) return;   /* начало вне 0..0xff (в оригинале — запись за таблицей) */
#endif
  uint8_t *rec = s->tab + k * SKID_REC_SIZE + w * SKID_WHEEL_SIZE;
  if (s->cnt[w] == SKID_RECS) { s->start[w]++; if (0xff < s->start[w]) s->start[w] -= SKID_RECS; }
  else s->cnt[w]++;
  int16_t v;
  if (s->st[w] == 1 && (uint8_t)s->flag == 1) {
    rec[SKID_ON] = 1; v = 2; memcpy(rec + SKID_STATE, &v, 2);
    uint8_t *pr = s->last[w] != 0 ? (uint8_t *)re_ptr(s->last[w]) : NULL;   /* previous record of this wheel */
    if (pr != NULL) { int16_t q; memcpy(&q, pr + SKID_STATE, 2); if (q == 2) { q = 1; memcpy(pr + SKID_STATE, &q, 2); } }
  } else { rec[SKID_ON] = 0; v = 0; memcpy(rec + SKID_STATE, &v, 2); }
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
      if (mdl != NULL && (rd_u32(mdl + 8) & MDL_F_HARD) != 0) hard = 1;
    }
  }
  if (!hard) {
    rec[SKID_SURFACE] = 0;
    if (P26_FxA == 0 && fr != 0) P118_SkidFx(p, 100, 500, 2, 0, m, 0);
    if (s->set5624) P102_5624A4 = 1;
  } else {
    if (P26_FxA == 0 && fr != 0) P118_SkidFx(p, 100, 500, 3, 0, m, 0);
    rec[SKID_SURFACE] = 1;
    if (s->set5624) P102_5624A4 = 0;
  }
  s->st[w] = 1;
  s->last[w] = re_addr(rec);
}

/* ---- 0051dd1b ---- */
/* P117_SkidRecA — Game.exe 0051dd1b.  Adds a skid-mark piece for body corner / wheel w (0..3) of the
   player car into ring A (P116_SkidRecA): from the previous corner position P117_PrevCorn to the
   current P102_Corners (int, y negated to y-up), direction = atan2 of the movement.  Does nothing when
   skid marks are off (P13_00575ec0 == 0).  Native: w range guard. */
void P117_SkidRecA(int32_t w) {
  if (P13_00575ec0 == 0) return;
#ifndef RE_HOOK_BUILD
  if (w < 0 || w > 3) return;
#endif
  const int32_t *cur = &P102_Corners[w * 4], *prv = &P117_PrevCorn[w * 4];
  int32_t ang = P44_Atan2(prv[2] - cur[2], prv[0] - cur[0]);
  skid_side_t s = { &P116_SkidRecA[0], P74_SkidD, P74_SkidB, P117_SkidStA, P117_SkidLastA, P102_D0DD80, 1 };
  float pos[3] = { (float)cur[0], (float)-cur[1], (float)cur[2] };
  skid_rec(&s, w, ang, (float)prv[0], (float)-prv[1] - SKID_LIFT, (float)prv[2],
           (float)cur[0], (float)-cur[1] - SKID_LIFT, (float)cur[2], pos, cur[0], cur[2]);
}

/* ---- 0051e1b7 ---- */
/* P117_SkidRecB — Game.exe 0051e1b7.  Same as P117_SkidRecA for ring B (P116_SkidRecB), with the current
   point given as floats q and the previous point from P56_Blk16 (stored as float bit patterns).
   Every float -> int conversion goes through the global P11_00ba52d0, as the original's fistp did.
   TODO(RE): unsure which wheels / which car ring B serves. */
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
  skid_rec(&s, w, ang, px, -py - SKID_LIFT, pz, q[0], -q[1] - SKID_LIFT, q[2], pos, P11_00ba52d0, rz);
}

/* ---- 00504cad: радар ---- */
/* P117_Radar — Game.exe 00504cad.  Draws the HUD radar centred at (P56_F573FA0, P56_F573FA4):
   radius r = 0.1 * screen width * scale, a frame 1-2 px wide (2 when scale >= 0.5), then the map
   texture P100_RadarIcon as a quad of half-size f = 0.1421875 * width * scale rotated by the player's
   heading (north-up when MenuOptBDFA54; car 0x41's heading when G6_00B87EAC), tinted grey at night
   (155 instead of 255), pulsing red/blue while P14_00d11a5c >= 0x2aa and there are cops (P95_AmbN >= 1;
   cf. the felony/chase indicator).  UVs are in texels scaled by 1/64 unless P55_BDFA18.  Clipped to the
   radar square, then the icons (sprite, mission objects, traffic, nearest target, compass) and the
   clip window restored from P110_Clip*. */
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
  /* frame: top, bottom, left, right */
  P108_FillRect((float)(x0 - t), (float)(y0 - t), (float)(d + t * 2), (float)t, RADAR_FRAME_COL);
  P108_FillRect((float)(x0 - t), (float)y1, (float)(d + t * 2), (float)t, RADAR_FRAME_COL);
  P108_FillRect((float)(x0 - t), (float)y0, (float)t, (float)d, RADAR_FRAME_COL);
  P108_FillRect((float)x1, (float)y0, (float)t, (float)d, RADAR_FRAME_COL);
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
  if (G6_00B5A778 == 0) P102_B52A3C = (P102_B52A3C - 8) & 0x7f;   /* pulse phase 0..127 (not while paused? TODO(RE)) */
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
/* P117_FullMap — Game.exe 00502fe2.  Draws the full-screen map from the source bitmap P99_C80880
   (P57_ScrW x S_00C808A0) as 256x256 tiles: each tile is copied into the map texture page (8-bit via
   P56_BmpPage into a temporarily swapped P65_Texs entry, or 16-bit via P62_DownloadPage) and drawn
   with P108_MapTexRect; then the radar marks.  Logs and returns if a texture or the source is missing. */
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
/* Bit pattern of a float (the menu setters take floats as raw dwords). */
static int32_t f_bits(float f) { int32_t v; memcpy(&v, &f, 4); return v; }
/* P117_TextList — Game.exe 0040ce31.  Draws the current menu's static text list (P45_PtrA): per 16-byte
   entry colour, position (y lifted by 1 for fonts 0/1, by 3 for bigger fonts), font, flags, then the
   string; the list ends at an entry with string address 0.  Native: RE_TRACE_TEXT debug dump. */
void P117_TextList(void) {
  if (P45_PtrA == 0) return;
  const uint8_t *e = (const uint8_t *)re_ptr(P45_PtrA);
#ifndef RE_HOOK_BUILD
  if (e == NULL) return;
#endif
  GlobalSet0040B0A4();
#ifndef RE_HOOK_BUILD
  { static int dbg = -1, cnt = 0; if (dbg < 0) dbg = getenv("RE_TRACE_TEXT") != NULL;
    if (dbg && (cnt++ % 50) == 0) { int n = 0; for (const uint8_t *q = e; rd_u32(q + 8) != 0 && n < 64; q += 0x10) n++;
      const char *s0 = n ? (const char *)re_ptr(rd_u32(e + 8)) : NULL; int fz = 0; for (int i = 0; i < 0x806 * 8; i++) fz += P58_Font[i] != 0;
      { const uint32_t *q1 = (const uint32_t *)re_ptr(0x0054cc58u), *q2 = (const uint32_t *)re_ptr(0x00c5585cu), *q3 = (const uint32_t *)re_ptr(0x00c55820u); fprintf(stderr, "[text] img cc58=%08x c5585c=%08x c55820=%08x\n", q1 ? *q1 : 0xdead, q2 ? *q2 : 0xdead, q3 ? *q3 : 0xdead); }
      fprintf(stderr, "[text] PtrA=%08x n=%d f7e58=%d font nz=%d s0=%s font0=%d x=%d y=%d\n", P45_PtrA, n, (int)P56_F7E58, fz, s0 ? s0 : "(null)", n ? e[4] : -1, n ? (int)(int16_t)rd_u32(e) : 0, n ? (int)(int16_t)(rd_u32(e) >> 16) : 0); } }
#endif
  for (; rd_u32(e + 8) != 0; e += 0x10) {
    MenuSetColor(e[0xc], e[0xd], e[0xe]);
    int16_t x, y; memcpy(&x, e, 2); memcpy(&y, e + 2, 2);
    float fy = (e[4] < 2) ? (float)y - 1.0f : (float)y - 3.0f;   /* .rdata 00546020 = 1.0, 00546034 = 3.0 */
    MenuSetVals5D77C0(f_bits((float)x), f_bits(fy), e[4], e[5]);
    P116_Text(rd_u32(e + 8));
  }
}
