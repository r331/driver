/* v1.46: 26 функций (см. ported101.h). Стандарт указателей v1.42: адреса объектов капель, записей объектов B/C (01105d60,
   0110b24c), буфера маски зеркала (00b31efc) и текстурных страниц — uint32_t + re_ptr/re_addr; глобальные скалярные указатели —
   родные. Узлы дороги/слоты читаются из P11_00bf1c40/P11_00c12c60/P11_00c1ed80 (game/nodetab.h). */
#include "ported101.h"
#include "nodetab.h"
#include "cartab.h"
#include "director.h"
#include "smallfuncs.h"
#include "uihandlers3.h"
#include "globalsets.h"
#include "ported4.h"
#include "ported5.h"
#include "ported6.h"
#include "ported7.h"
#include "ported11.h"
#include "ported12.h"
#include "ported13.h"
#include "ported14.h"
#include "ported15.h"
#include "ported16.h"
#include "ported17.h"
#include "ported26.h"
#include "ported41.h"
#include "ported43.h"
#include "ported44.h"
#include "ported48.h"
#include "ported54.h"
#include "ported55.h"
#include "ported56.h"
#include "ported58.h"
#include "ported59.h"
#include "ported62.h"
#include "ported68.h"
#include "ported71.h"
#include "ported72.h"
#include "ported74.h"
#include "ported75.h"
#include "ported79.h"
#include "ported85.h"
#include "ported93.h"
#include "ported94.h"
#include "ported95.h"
#include "ported96.h"
#include "ported97.h"
#include "ported98.h"
#include "ported99.h"
#include "ported100.h"
#include <math.h>
#include <stdlib.h>
#include <string.h>

#ifndef RE_HOOK_BUILD
#pragma push_macro("P101_FxCol") /*gvi*/
#undef P101_FxCol /*gvi*/
p101_b16_t P101_FxCol = { 0x00, 0x3f, 0x7f, 0xbf, 0xff, 0xbf, 0x7f, 0x3f, 0x00, 0x3f, 0x7f, 0xbf, 0xff, 0xbf, 0x7f, 0x3f };  /* .data 005537c8 */
#pragma pop_macro("P101_FxCol") /*gvi*/
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P101_Hud")
#undef P101_Hud
#pragma push_macro("P101_Hud") /*gvi*/
#undef P101_Hud /*gvi*/
p101_hud_t P101_Hud;
#pragma pop_macro("P101_Hud") /*gvi*/
#pragma pop_macro("P101_Hud")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P101_HudVal")
#undef P101_HudVal
#pragma push_macro("P101_HudVal") /*gvi*/
#undef P101_HudVal /*gvi*/
int32_t P101_HudVal;
#pragma pop_macro("P101_HudVal") /*gvi*/
#pragma pop_macro("P101_HudVal")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P101_GoalPos")
#undef P101_GoalPos
#pragma push_macro("P101_GoalPos") /*gvi*/
#undef P101_GoalPos /*gvi*/
p101_f3_t P101_GoalPos;
#pragma pop_macro("P101_GoalPos") /*gvi*/
#pragma pop_macro("P101_GoalPos")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P101_SaveCar")
#undef P101_SaveCar
#pragma push_macro("P101_SaveCar") /*gvi*/
#undef P101_SaveCar /*gvi*/
p101_b148_t P101_SaveCar;
#pragma pop_macro("P101_SaveCar") /*gvi*/
#pragma pop_macro("P101_SaveCar")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P101_SaveCar2")
#undef P101_SaveCar2
#pragma push_macro("P101_SaveCar2") /*gvi*/
#undef P101_SaveCar2 /*gvi*/
p101_b148_t P101_SaveCar2;
#pragma pop_macro("P101_SaveCar2") /*gvi*/
#pragma pop_macro("P101_SaveCar2")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P101_SaveA")
#undef P101_SaveA
#pragma push_macro("P101_SaveA") /*gvi*/
#undef P101_SaveA /*gvi*/
p101_b34_t P101_SaveA;
#pragma pop_macro("P101_SaveA") /*gvi*/
#pragma pop_macro("P101_SaveA")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P101_SaveA2")
#undef P101_SaveA2
#pragma push_macro("P101_SaveA2") /*gvi*/
#undef P101_SaveA2 /*gvi*/
p101_b34_t P101_SaveA2;
#pragma pop_macro("P101_SaveA2") /*gvi*/
#pragma pop_macro("P101_SaveA2")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P101_SaveB")
#undef P101_SaveB
#pragma push_macro("P101_SaveB") /*gvi*/
#undef P101_SaveB /*gvi*/
p101_b34_t P101_SaveB;
#pragma pop_macro("P101_SaveB") /*gvi*/
#pragma pop_macro("P101_SaveB")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P101_SaveB2")
#undef P101_SaveB2
#pragma push_macro("P101_SaveB2") /*gvi*/
#undef P101_SaveB2 /*gvi*/
p101_b34_t P101_SaveB2;
#pragma pop_macro("P101_SaveB2") /*gvi*/
#pragma pop_macro("P101_SaveB2")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P101_SaveC")
#undef P101_SaveC
#pragma push_macro("P101_SaveC") /*gvi*/
#undef P101_SaveC /*gvi*/
p101_b34_t P101_SaveC;
#pragma pop_macro("P101_SaveC") /*gvi*/
#pragma pop_macro("P101_SaveC")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P101_SaveC2")
#undef P101_SaveC2
#pragma push_macro("P101_SaveC2") /*gvi*/
#undef P101_SaveC2 /*gvi*/
p101_b34_t P101_SaveC2;
#pragma pop_macro("P101_SaveC2") /*gvi*/
#pragma pop_macro("P101_SaveC2")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P101_LiveA")
#undef P101_LiveA
#pragma push_macro("P101_LiveA") /*gvi*/
#undef P101_LiveA /*gvi*/
p101_b34_t P101_LiveA;
#pragma pop_macro("P101_LiveA") /*gvi*/
#pragma pop_macro("P101_LiveA")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P101_LiveB")
#undef P101_LiveB
#pragma push_macro("P101_LiveB") /*gvi*/
#undef P101_LiveB /*gvi*/
p101_b34_t P101_LiveB;
#pragma pop_macro("P101_LiveB") /*gvi*/
#pragma pop_macro("P101_LiveB")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P101_LiveC")
#undef P101_LiveC
#pragma push_macro("P101_LiveC") /*gvi*/
#undef P101_LiveC /*gvi*/
p101_b34_t P101_LiveC;
#pragma pop_macro("P101_LiveC") /*gvi*/
#pragma pop_macro("P101_LiveC")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P101_RecState")
#undef P101_RecState
#pragma push_macro("P101_RecState") /*gvi*/
#undef P101_RecState /*gvi*/
int32_t P101_RecState;
#pragma pop_macro("P101_RecState") /*gvi*/
#pragma pop_macro("P101_RecState")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P101_RecFrame")
#undef P101_RecFrame
#pragma push_macro("P101_RecFrame") /*gvi*/
#undef P101_RecFrame /*gvi*/
int32_t P101_RecFrame;
#pragma pop_macro("P101_RecFrame") /*gvi*/
#pragma pop_macro("P101_RecFrame")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P101_RecFrame2")
#undef P101_RecFrame2
#pragma push_macro("P101_RecFrame2") /*gvi*/
#undef P101_RecFrame2 /*gvi*/
int32_t P101_RecFrame2;
#pragma pop_macro("P101_RecFrame2") /*gvi*/
#pragma pop_macro("P101_RecFrame2")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P101_RecSaved")
#undef P101_RecSaved
#pragma push_macro("P101_RecSaved") /*gvi*/
#undef P101_RecSaved /*gvi*/
int32_t P101_RecSaved;
#pragma pop_macro("P101_RecSaved") /*gvi*/
#pragma pop_macro("P101_RecSaved")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P101_Drops")
#undef P101_Drops
#pragma push_macro("P101_Drops") /*gvi*/
#undef P101_Drops /*gvi*/
p101_drops_t P101_Drops;
#pragma pop_macro("P101_Drops") /*gvi*/
#pragma pop_macro("P101_Drops")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P101_Nbr")
#undef P101_Nbr
#pragma push_macro("P101_Nbr") /*gvi*/
#undef P101_Nbr /*gvi*/
p101_nbr_t P101_Nbr;
#pragma pop_macro("P101_Nbr") /*gvi*/
#pragma pop_macro("P101_Nbr")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P101_RdNode")
#undef P101_RdNode
#pragma push_macro("P101_RdNode") /*gvi*/
#undef P101_RdNode /*gvi*/
uint16_t P101_RdNode;
#pragma pop_macro("P101_RdNode") /*gvi*/
#pragma pop_macro("P101_RdNode")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P101_RdCell")
#undef P101_RdCell
#pragma push_macro("P101_RdCell") /*gvi*/
#undef P101_RdCell /*gvi*/
uint16_t P101_RdCell;
#pragma pop_macro("P101_RdCell") /*gvi*/
#pragma pop_macro("P101_RdCell")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P101_RdLane")
#undef P101_RdLane
#pragma push_macro("P101_RdLane") /*gvi*/
#undef P101_RdLane /*gvi*/
int16_t P101_RdLane;
#pragma pop_macro("P101_RdLane") /*gvi*/
#pragma pop_macro("P101_RdLane")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P101_RdB2")
#undef P101_RdB2
#pragma push_macro("P101_RdB2") /*gvi*/
#undef P101_RdB2 /*gvi*/
uint8_t P101_RdB2;
#pragma pop_macro("P101_RdB2") /*gvi*/
#pragma pop_macro("P101_RdB2")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P101_RdDist")
#undef P101_RdDist
#pragma push_macro("P101_RdDist") /*gvi*/
#undef P101_RdDist /*gvi*/
int32_t P101_RdDist;
#pragma pop_macro("P101_RdDist") /*gvi*/
#pragma pop_macro("P101_RdDist")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P101_RdLeft")
#undef P101_RdLeft
#pragma push_macro("P101_RdLeft") /*gvi*/
#undef P101_RdLeft /*gvi*/
int32_t P101_RdLeft;
#pragma pop_macro("P101_RdLeft") /*gvi*/
#pragma pop_macro("P101_RdLeft")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P101_ObjBOn2")
#undef P101_ObjBOn2
#pragma push_macro("P101_ObjBOn2") /*gvi*/
#undef P101_ObjBOn2 /*gvi*/
int32_t P101_ObjBOn2;
#pragma pop_macro("P101_ObjBOn2") /*gvi*/
#pragma pop_macro("P101_ObjBOn2")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P101_CarFx")
#undef P101_CarFx
#pragma push_macro("P101_CarFx") /*gvi*/
#undef P101_CarFx /*gvi*/
p101_b66_t P101_CarFx;
#pragma pop_macro("P101_CarFx") /*gvi*/
#pragma pop_macro("P101_CarFx")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P101_ScrX0")
#undef P101_ScrX0
#pragma push_macro("P101_ScrX0") /*gvi*/
#undef P101_ScrX0 /*gvi*/
float P101_ScrX0;
#pragma pop_macro("P101_ScrX0") /*gvi*/
#pragma pop_macro("P101_ScrX0")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P101_ScrY0")
#undef P101_ScrY0
#pragma push_macro("P101_ScrY0") /*gvi*/
#undef P101_ScrY0 /*gvi*/
float P101_ScrY0;
#pragma pop_macro("P101_ScrY0") /*gvi*/
#pragma pop_macro("P101_ScrY0")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P101_TmpY")
#undef P101_TmpY
#pragma push_macro("P101_TmpY") /*gvi*/
#undef P101_TmpY /*gvi*/
float P101_TmpY;
#pragma pop_macro("P101_TmpY") /*gvi*/
#pragma pop_macro("P101_TmpY")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P101_PalLfb")
#undef P101_PalLfb
#pragma push_macro("P101_PalLfb") /*gvi*/
#undef P101_PalLfb /*gvi*/
p101_pal_t P101_PalLfb;
#pragma pop_macro("P101_PalLfb") /*gvi*/
#pragma pop_macro("P101_PalLfb")
#endif

static int32_t rd32(const void *p) { int32_t v; memcpy(&v, p, 4); return v; }
static void wr32(void *p, int32_t v) { memcpy(p, &v, 4); }
static uint16_t rd16(const void *p) { uint16_t v; memcpy(&v, p, 2); return v; }
static int16_t rd16s(const void *p) { int16_t v; memcpy(&v, p, 2); return v; }
static void wr16(void *p, uint16_t v) { memcpy(p, &v, 2); }
static float rdf(const void *p) { float v; memcpy(&v, p, 4); return v; }
static void wrf(void *p, float v) { memcpy(p, &v, 4); }
static uint32_t fbits(float v) { uint32_t u; memcpy(&u, &v, 4); return u; }
static int32_t iabs(int32_t v) { return v < 0 ? -v : v; }
static int32_t fround(float v) { return (int32_t)lrintf(v); }   /* fistp */
static int32_t fx12(int32_t a, int32_t b) { return (int32_t)((uint32_t)a * (uint32_t)b + 0x800u) >> 12; }
static uint8_t *texpage(uint32_t slot) { return (uint8_t *)re_ptr((uint32_t)rd32(&g_01145a60[slot * 0x10 + 4])); }
/* запись модели машины m (00d0cc60 + m*0x16c); в native — в пределах S_00D0CC60 (0x4000 байт), иначе нули */
static const uint8_t *carmodel(uint32_t m) {
#ifndef RE_HOOK_BUILD
  static const uint8_t zero[0x16c];
  if ((m + 1) * 0x16c > sizeof S_00D0CC60) return zero;
#endif
  return S_00D0CC60 + m * 0x16c;
}
/* запись i шага st таблицы tab размера sz (в native вне таблицы — нули) */
static const uint8_t *rec(const uint8_t *tab, uint32_t sz, int32_t i, uint32_t st) {
#ifndef RE_HOOK_BUILD
  static const uint8_t zero[0x100];
  if (i < 0 || (uint32_t)(i + 1) * st > sz) return zero;
#else
  (void)sz;
#endif
  return tab + (uint32_t)i * st;
}

/* ---- 004f51b4: шаг цели скрипта (состояние +4: 4 — напугать, 5 — соперник, 6 — доехать до объекта, 8 — машина трафика) ---- */
void P101_GoalTick(uint8_t *g) {
  P100_GoalsCheck(g);
  switch (rd32(g + 4)) {
  case 4:
    if (P101_Hud[11] == 0) P16_FillHudRect(P101_Hud, fbits((float)P101_HudVal), 0xff00, re_addr("Scare?"), 1, 0);   /* .data 0056ee50 */
    else if (rdf(&P101_Hud[4]) >= rdf(&P101_Hud[5])) wr32(g + 4, 0x7fff);
    break;
  case 5:
    if (P101_Hud[11] == 0 && P95_B87F08 != 0)
      P16_FillHudRect(P101_Hud, fbits((float)P95_BDFA5C), 0xff00, re_addr("Opponent?"), 1, 0);              /* .data 0056ee44 */
    if (P95_B87F08 != 0) wrf(&P101_Hud[4], (float)P95_BDFA0C);
    if (P95_B87F08 == 0 || P95_BDFA0C < P95_BDFA5C) {
      if (P100_1426FC == 0) {
        if (P75_E4 == 0) {
          if (P100_143720 != 0) {
            wr32(g + 4, 0x7fff);
            P101_GoalPos[0] = (float)P99_Cars[0x41].pos[0]; P101_GoalPos[1] = (float)P99_Cars[0x41].pos[1]; P101_GoalPos[2] = (float)P99_Cars[0x41].pos[2];
          }
        } else wr32(g + 4, 0x7fff);
      } else { wr32(g + 4, 0xff0); wr32(g + 0x28, 3); wr32(g + 0x40, 0x5a); }
    } else {
      wr32(g + 4, 0x7fff);
      P95_B87F08 = 0;
      P75_E4 = 1;
      P101_GoalPos[0] = (float)P99_Cars[0x41].pos[0]; P101_GoalPos[1] = (float)P99_Cars[0x41].pos[1]; P101_GoalPos[2] = (float)P99_Cars[0x41].pos[2];
    }
    break;
  case 6:
    for (int32_t k = 0; k < 10; k++) {
      uint8_t *o = P58_Objs[k];
      uint32_t f = (uint32_t)rd32(o + 0x10);
      if ((f & 1) != 0 && (f & 0x100) != 0 && P56_CarPosCheck(rd32(o + 8), rd32(o + 4), (uint32_t *)(o + 0x14)) != 0) {
        wr32(g + 4, 0x7fff);
        wr32(o + 0x10, (int32_t)((uint32_t)rd32(o + 0x10) & 0xfffffefeu));
      }
    }
    break;
  case 8: {
    int32_t n = rd32(g + 0x68);
    uint8_t *o = P58_Objs[0];
    if (n == -1) { wr32(g + 4, 0x7fff); break; }
#ifndef RE_HOOK_BUILD
    if (n < 0 || n >= 0x40) break;   /* в оригинале — чтение вне таблицы трафика */
#endif
    uint8_t *t = &TrafficRecs[n * 0x54];
    if (t[0x15] == 0) {
      wr32(o + 0x10, (int32_t)((uint32_t)rd32(o + 0x10) & 0xfffffffeu));
      wr32(g + 4, 0xff0); wr32(g + 0x28, 4); wr32(g + 0x40, 0x5a);
    } else if (Get138Entry148(n) < rd32(g + 0x6c)) {
      wr32(o + 0x14, P99_Cars[n + 1].pos[0]);
      wr32(o + 0x1c, P99_Cars[n + 1].pos[2]);
    } else {
      t[0x15] = 0;
      wr32(g + 0x68, -1);
      wr32(o + 0x10, (int32_t)((uint32_t)rd32(o + 0x10) & 0xfffffffeu));
    }
    break;
  }
  default: break;
  }
  int32_t st = rd32(g + 4);
  if (st != 0xff0 && st != 0x7fff && st != 0x8000 && st != 0xf1 && P62_FarFromPlayer(rd32(g + 0x78), rd32(g + 0x74)) != 0) {
    wr32(g + 0x74, 0); wr32(g + 4, 0xff0); wr32(g + 0x28, 4); wr32(g + 0x40, 0x5a);
  }
}

/* ---- 004b998b: шаг обломка с отскоком от дороги (int x,y,z +0; скорость +0x10; таймер int16 +0x20; номер +0x24) ---- */
void P101_DebrisBounce(int32_t *p) {
  uint8_t *b = (uint8_t *)p;
  int16_t c = (int16_t)(rd16s(b + 0x20) - 1);
  wr16(b + 0x20, (uint16_t)c);
  if (c == 0) { wr16(b + 0x22, 0); PoolPush004AC6AC((uint16_t)rd16s(b + 0x24)); return; }
  p[0] += p[4]; p[1] += p[5]; p[2] += p[6];
  p[5] += 6;
  wr16(b + 0x26, (uint16_t)((rd16(b + 0x26) + rd16(b + 0x28)) & 0xff));
  int32_t h = P100_RoadHeight(p);
  if ((float)-h < (float)p[1]) {
    float v = (float)p[5] * 0.7f;           /* .rdata 00546168 */
    P11_00ba52d0 = fround(v);
    p[5] = -P11_00ba52d0;
    P11_00ba52d0 = fround((float)-h);
    p[1] = P11_00ba52d0;
    p[0xc]++;
    if (2 < p[0xc]) wr16(b + 0x20, 1);
  }
}

/* ---- 00518953: начало воспроизведения — снимки игрока/камер (keep: сохранить текущие), сброс указателей записи, машина 0x41 ---- */
void P101_ReplayBegin(int32_t keep) {
  P100_RecKeys = 0x10100000;
  P100_RecInput(P12_00b5a898);
  if (keep != 0) {
    P44_Copy4(P101_SaveCar, P101_SaveCar2, 0x148);
    P44_Copy4(P101_SaveA, P101_SaveA2, 0x34);
    P44_Copy4(P101_SaveB, P101_SaveB2, 0x34);
    P44_Copy4(P101_SaveC, P101_SaveC2, 0x34);
    uint8_t *d = (uint8_t *)re_ptr(P100_RecPtr[1]);
#ifndef RE_HOOK_BUILD
    if (d != NULL && P100_RecBuf != NULL)
#endif
    P44_Copy4(d, P100_RecBuf, (uint32_t)P74_C4BDE0);
    P101_RecFrame2 = P74_C54D08;
    P101_RecSaved = 1;
  }
  P12_Fn005188EC();
  P100_RecRep[1] = P100_RecRep[0];
  P100_RecOff[1] = P100_RecOff[0];
  P100_RecCnt[1] = P100_RecCnt[0];
  P74_B5A86C[1] = P74_B5A86C[0];
  P74_B5A880[1] = P74_B5A880[0];
  P44_Copy4(&P99_Cars[0x41], P101_SaveCar, 0x148);
  P44_Copy4(P101_LiveA, P101_SaveA, 0x34);
  P44_Copy4(P101_LiveB, P101_SaveB, 0x34);
  P44_Copy4(P101_LiveC, P101_SaveC, 0x34);
  P99_Cars[0x41].f00[0] = 0x41;
  P99_CarModelClean(0x41);
  P101_RecFrame = 0;
  P101_RecState = 1;
}

/* ---- 00522d02: 6 капель (запись 0x1c: +0xc x, +0x10/+0x12/+0x14 скорости int16, +0x18 адрес объекта) падают до дороги ---- */
void P101_Drips(void) {
  if (G6_00B5A778 != 0) return;
  for (int32_t k = 0; k < 6; k++) {
    uint8_t *d = &P101_Drops[k * 0x1c];
    if (rd32(d + 0x18) == 0) continue;
    uint8_t *o = (uint8_t *)re_ptr((uint32_t)rd32(d + 0x18));
#ifndef RE_HOOK_BUILD
    if (o == NULL) continue;
#endif
    float pos[3] = { (float)rd32(d + 0xc), 0.0f, rdf(o + 0x10) };   /* [1] в оригинале не задан, не читается */
    int32_t h = P100_RoadHeightF(pos);
    if ((float)(-h + 0x32) <= rdf(o + 0xc)) {
      int16_t vy = rd16s(d + 0x12);
      if (vy < 0x15) wr32(d + 0x18, 0);
      else { wrf(o + 0xc, (float)(-h + 0x31)); wr16(d + 0x12, (uint16_t)(int16_t)-(int16_t)(vy / 4)); }
    } else {
      wr32(d + 0xc, rd32(d + 0xc) + rd16s(d + 0x10) / 2);
      wrf(o + 0xc, (float)(rd16s(d + 0x12) / 2) + rdf(o + 0xc));
      wrf(o + 0x10, (float)(rd16s(d + 0x14) / 2) + rdf(o + 0x10));
      wr32(d, rd32(d) + 1);
      wr16(d + 0x12, (uint16_t)(rd16s(d + 0x12) + 8));
    }
  }
}

/* ---- 004dea35: машина на дороге — высота по земле минус клиренс модели (+0xe2), колёса в контакте, out[0x14] = 1 ---- */
void P101_CarGround(p99_car_t *car, uint8_t *out) {
  const p99_car_t *ref = (G6_00B87EAC == 0 && G6_00B87EB0 == 0) ? &P99_Cars[0] : &P99_Cars[0x41];
  int32_t dx = iabs(ref->pos[0] - car->pos[0]), dz = iabs(ref->pos[2] - car->pos[2]);
  int32_t d = dx < dz ? dz + dx / 2 : dx + dz / 2;
  /* в оригинале: xor ecx,ecx; setl cl; sub ecx,6000; jne — условие «далеко» никогда не выполняется */
  if ((int32_t)(d < 0x9e34) - 6000 == 0 && G6_00B87EAC == 0 && G6_00B87EB0 == 0) { out[0x14] = 0; return; }
  const uint8_t *m = carmodel(car->f00[2]);
  int32_t h = P100_RoadHeight((const int32_t *)((uint8_t *)car + 0xc8));
  car->pos[1] = h - rd16s(m + 0xe2);
  for (int32_t k = 4; k != 0; k--) car->f78[k - 1][0] = 0x10;
  out[0x14] = 1;
}

/* выбор одного свободного соседа: биты 1/2/4/8 — da8/da6/da2/da4 == -0x8000 */
static uint32_t free_nbr(uint32_t *cnt) {
  uint32_t n = (P101_Nbr[3] == -0x8000), m = n;
  if (P101_Nbr[2] == -0x8000) { m |= 2; n++; }
  if (P101_Nbr[0] == -0x8000) { m |= 4; n++; }
  if (P101_Nbr[1] == -0x8000) { m |= 8; n++; }
  *cnt = n;
  return m;
}
static uint32_t rand_bit(uint32_t m, uint32_t n) {
  uint32_t bit = 0x10;
  int32_t k = (int32_t)Rand_004D9078() % (int32_t)n + 1;
  while (k != 0) {
    bit = (uint32_t)((int32_t)bit >> 1);
#ifndef RE_HOOK_BUILD
    if (bit == 0) break;
#endif
    if ((m & bit) != 0) k--;
  }
  return m & bit;
}

/* ---- 005139d7: соседняя свободная клетка (предпочтительно want) — центр клетки в out[0]/out[2], высота дороги в out[1] ---- */
uint32_t P101_PickCell(uint32_t want, int32_t x, int32_t z, float *out) {
  uint32_t n, m = free_nbr(&n);
  if ((m & want) == 0) { if (1 < n) m = rand_bit(m, n); }
  else m &= want;
  int32_t cx = (x + 0x2ee + P62_MapC64) / 0x5dc;
  int32_t cz = (P62_Map2C40 - (z - 0x2ee)) / 0x5dc;
  switch (m) {
  case 1: out[0] = (float)((cx - 1) * 0x5dc - P62_MapC64); out[2] = (float)-(cz * 0x5dc - P62_Map2C40); break;
  case 2: out[0] = (float)((cx + 1) * 0x5dc - P62_MapC64); out[2] = (float)-(cz * 0x5dc - P62_Map2C40); break;
  case 4: out[0] = (float)(cx * 0x5dc - P62_MapC64); out[2] = (float)-((cz + 1) * 0x5dc - P62_Map2C40); break;
  case 8: out[0] = (float)(cx * 0x5dc - P62_MapC64); out[2] = (float)-((cz - 1) * 0x5dc - P62_Map2C40); break;
  default: break;
  }
  out[1] = (float)-P100_RoadHeightF(out);
  return m;
}

/* ---- 004997a0: пересечение двух коробок (оси +0.., полуразмеры +0x40, оси×размер → +0x4c) — 1, если нет разделяющей грани ---- */
int32_t P101_BoxHit(int32_t *a, int32_t *b, int32_t *best) {
  *best = 0x40000000;
  for (int32_t k = 0; k < 3; k++) {
    a[0x13 + k * 4] = fx12(a[k * 4], a[0x10 + k]);
    a[0x14 + k * 4] = fx12(a[1 + k * 4], a[0x10 + k]);
    a[0x15 + k * 4] = fx12(a[2 + k * 4], a[0x10 + k]);
    b[0x13 + k * 4] = fx12(b[k * 4], b[0x10 + k]);
    b[0x14 + k * 4] = fx12(b[1 + k * 4], b[0x10 + k]);
    b[0x15 + k * 4] = fx12(b[2 + k * 4], b[0x10 + k]);
  }
  for (int32_t k = 0; k < 3; k++) {
    P100_BoxFace(a, b, k, best, 1);
    if (*best < 0) return 0;
    P100_BoxFace(b, a, k, best, -1);
    if (*best < 0) return 0;
  }
  return 1;
}

/* ---- 0051c07a: границы дорог по 4 сторонам (P59_C39DC0, запись 0x24: длины +0..3, точки +4..+0x20) ---- */
void P101_RoadBounds(void) {
  uint8_t *r = P59_C39DC0;
  for (int32_t i = 0; i < P11_00b5a8e8; i++, r += 0x24) {
#ifndef RE_HOOK_BUILD
    if ((uint32_t)(i + 1) * 0x24 > sizeof P59_C39DC0) break;
#endif
    uint8_t s = P17_SlotMapSide(i);
    P100_RoadRect(i, 0);
    r[0] = s == 0 ? (uint8_t)(P100_Rect[2] - P100_Rect[0] + 1) : 0;
    wr32(r + 4, P100_Rect[0] * 0x5dc); wr32(r + 8, P100_Rect[3] * -0x5dc);
    P100_RoadRect(i, 1);
    r[1] = s == 1 ? (uint8_t)(P100_Rect[3] - P100_Rect[1] + 1) : 0;
    wr32(r + 0xc, P100_Rect[0] * 0x5dc); wr32(r + 0x10, P100_Rect[1] * -0x5dc);
    P100_RoadRect(i, 2);
    r[2] = s == 0 ? (uint8_t)(P100_Rect[2] - P100_Rect[0] + 1) : 0;
    wr32(r + 0x14, P100_Rect[2] * 0x5dc); wr32(r + 0x18, P100_Rect[1] * -0x5dc);
    P100_RoadRect(i, 3);
    r[3] = s == 1 ? (uint8_t)(P100_Rect[3] - P100_Rect[1] + 1) : 0;
    wr32(r + 0x1c, P100_Rect[2] * 0x5dc); wr32(r + 0x20, P100_Rect[3] * -0x5dc);
  }
}

/* ---- 00513d0a: падение частицы (позиция +0x84, скорость +0x74, флаги +0x10: 0x10 — кадры, 0x20 — падение) ---- */
void P101_PartFall(uint8_t *p) {
  wrf(p + 0x84, rdf(p + 0x84) + rdf(p + 0x74));
  wrf(p + 0x88, rdf(p + 0x88) + rdf(p + 0x78));
  wrf(p + 0x8c, rdf(p + 0x8c) + rdf(p + 0x7c));
  int32_t h = P100_RoadHeightF((const float *)(p + 0x84));
  P11_00ba52d0 = fround(rdf(p + 0x88));
  uint32_t f = (uint32_t)rd32(p + 0x10);
  if ((f & 0x10) == 0) {
    if ((f & 0x20) == 0) {
      float vy = rdf(p + 0x78);
      if (0.0f <= vy) wrf(p + 0x78, vy + 9.0f);             /* .rdata 00546024 = 0, 005469fc = 9 */
      else if (vy + 9.0f < 0.0f) wrf(p + 0x78, vy + 9.0f);
      else { wr32(p + 0x78, 0); wr32(p + 0x10, (int32_t)(f | 0x10)); }
    } else if (rdf(p + 0x88) <= (float)-h) wrf(p + 0x78, rdf(p + 0x78) + 9.0f);
    else {
      wrf(p + 0x88, (float)-h);
      wr32(p + 0xc, (int32_t)((uint32_t)rd32(p + 0xc) & 0xfffff7ffu));
      wr32(p + 0x10, 0);
    }
  } else {
    uint32_t v = ((f & 3) + 1) & 3;
    f = (f & 0xfffffffcu) | v;
    if (v == 0) f = (f & 0xffffffefu) | 0x20;
    wr32(p + 0x10, (int32_t)f);
  }
  if (55.0f < rdf(p + 0x78)) wr32(p + 0x78, 0x425c0000);    /* .rdata 00546a78 = 55 */
}

/* ---- 0051500c: поворот частицы на соседнюю клетку (направление +0x38: 1/2/4/8), иначе освободить слот ---- */
void P101_PartTurn(uint8_t *p) {
  float *pv = (float *)(p + 0x94);
  P11_00ba52d0 = fround(rdf(p + 0x84));
  int32_t x = P11_00ba52d0;
  P11_00ba52d0 = fround(rdf(p + 0x8c));
  int32_t z = P11_00ba52d0;
  uint32_t n, m = free_nbr(&n);
  if (n == 0) { P43_FreeSlot(p); return; }
  uint32_t own = 0, opp = 0;
  switch (rd32(p + 0x38)) {
  case 1: own = 1; opp = 2; break;
  case 2: own = 2; opp = 1; break;
  case 4: own = 4; opp = 8; break;
  case 8: own = 8; opp = 4; break;
  default: break;
  }
  if (own != 0) {
    if ((m & opp) != 0) { m = (m & (0xffffu ^ opp)) | (opp << 8); n--; }
    if ((m & own) == 0) {
      if (n == 0) m = (uint32_t)((int32_t)m >> 8);
      else m = rand_bit(m, n);
    } else m &= own;
  }
  if (m == 0) { P43_FreeSlot(p); return; }
  wr32(p + 0x38, (int32_t)m);
  int32_t bx = ((x + 0x2ee + P62_MapC64) / 0x5dc) * 0x5dc - P62_MapC64;
  int32_t bz = -(((P62_Map2C40 - (z - 0x2ee)) / 0x5dc) * 0x5dc - P62_Map2C40);
  switch (m) {
  case 1: pv[0] = (float)(bx - 0x5dc); wrf(p + 0x9c, (float)bz); break;
  case 2: pv[0] = (float)(bx + 0x5dc); wrf(p + 0x9c, (float)bz); break;
  case 4: pv[0] = (float)bx; wrf(p + 0x9c, (float)(bz - 0x5dc)); break;
  case 8: pv[0] = (float)bx; wrf(p + 0x9c, (float)(bz + 0x5dc)); break;
  default: break;
  }
  int32_t h = P100_RoadHeightF(pv);
  wrf(p + 0x98, (float)-h);
  P71_EdgeB(p, pv);
  P68_AimSetup(p);
}

/* громкость звука машины трафика n (номер+1): поле +0xcd4 записи физики (00112da00, шаг 0xcd8) по слоту +5 записи трафика */
static float traffic_vol(int32_t n) {
#ifndef RE_HOOK_BUILD
  if (n < 1 || n > 0x40) return 0.0f;
#endif
  uint32_t s = TrafficRecs[(n - 1) * 0x54 + 5];
#ifndef RE_HOOK_BUILD
  if (s < 1 || s > 8) return 0.0f;
#endif
  return rdf((const uint8_t *)P12_0112da00 + (s - 1) * 0xcd8 + 0xcd4);
}
static int32_t near_voice(int32_t n, int32_t slot) {
  if (n == -1) return 0;
#ifndef RE_HOOK_BUILD
  if (n < 0 || n >= P99_CARS_N) return 0;
#endif
  float v = traffic_vol(n);
  if (!(0.01f < v)) return 0;                                 /* .rdata 0054614c */
  SoundLoop_0052422D(slot, (int32_t)re_addr((uint8_t *)&P99_Cars[n] + 0xc8));
  P48_SetVoiceVolume(slot, -100);
  SoundSetPos00523F8A(slot, (int32_t)((double)v * 11025.0));  /* .rdata 005468c8, __ftol */
  return 1;
}

/* ---- 004d63bc: звуки двух ближайших машин трафика (голоса 5..8) ---- */
void P101_TrafficSounds(void) {
  if ((P62_Frame & 0x3f) == 0) {
    P95_NearestTwo();
    int32_t a = near_voice(P95_Near1, 7);
    int32_t b = near_voice(P95_Near2, 8);
    if (!a) { SoundLoop_0052422D(7, 0); P48_SetVoiceVolume(7, -10000); }
    if (!b) { SoundLoop_0052422D(8, 0); P48_SetVoiceVolume(8, -10000); }
  }
  if (P95_Near1 == -1) P48_SetVoiceVolume(5, -10000);
  else { P100_CarRevs(P95_Near1); P75_CarVoice(P95_Near1, 5, -1); P48_SetVoiceVolume(5, 0); }
  if (P95_Near2 == -1) P48_SetVoiceVolume(6, -10000);
  else { P100_CarRevs(P95_Near2); P75_CarVoice(P95_Near2, 6, -1); P48_SetVoiceVolume(6, 0); }
}

/* ---- 004b0256: объект B (01105d60) у точки (x,y,z) в системе объекта src (+8 позиция, +0x18 курс) ---- */
void P101_AddObjB(const uint8_t *src, float x, float y, float z, int16_t kind, int16_t b, int16_t val) {
  int32_t sv = P13_00b201dc;
  if (P96_ObjBOn != 0 && P13_00b201dc != 0 && (P14_00b87e84 != 0 || P26_FxD != 0)) {
    int32_t ang = rd32(src + 0x18);
    P13_00b201dc = 1;
    float v[4] = { x, y, z, 0.0f };
#ifndef RE_HOOK_BUILD
    if (P56_EulerTab == NULL) { P13_00b201dc = sv; return; }
#endif
    P44_MatPtr = (float *)(P56_EulerTab + ((uint32_t)-ang & 0xfffu) * 0x40);
    P44_Xform(v);
    v[0] += rdf(src + 8); v[1] += rdf(src + 0xc); v[2] += rdf(src + 0x10);
    if (P26_FxA != 0 && P14_00b87e84 != 0) {
      if (0xff < val) val = 0xff;
      uint8_t t = kind == 6 ? 6 : kind == 7 ? 7 : kind == 8 ? 8 : 0;
      PushEntry_004CC784((const uint32_t *)v, t, (uint8_t)val);
    }
    v[0] -= P44_CamX; v[1] -= P44_CamY; v[2] -= P44_CamZ;
    P44_MatPtr = P44_ViewMatT;
    P44_Xform(v);
    if (P95_Near <= v[2] && P101_ObjBOn2 != 0) {
      uint8_t *r = P95_ObjPtr((uint32_t)G01105D60);
      if (r != NULL) {
        wrf(r, v[0]); wrf(r + 4, v[1]); wrf(r + 8, v[2]); wrf(r + 0x18, v[2]);
        wr32(r + 0x68, 0x40002); wr32(r + 0x74, 0); wr32(r + 0x70, 0);
        wr16(r + 0x64, (uint16_t)kind); wr16(r + 0x6e, (uint16_t)b); wr16(r + 0x6c, (uint16_t)ang); wr16(r + 0x66, (uint16_t)val);
        G01105D60 += 0x78;
        G010FFD04++;
      }
    }
  }
  P13_00b201dc = sv;
}

/* точка v (в системе машины car) → вид: матрица машины, позиция машины, камера; r — запись объекта C */
static void car_to_view(float *r, int32_t car) {
  P44_MatPtr = P98_CarMat[car];
  P44_XformT(r);
  r[0] = (float)P99_Cars[car].pos[0] + r[0];
  r[1] = (float)-P99_Cars[car].pos[1] + r[1];
  r[2] = (float)P99_Cars[car].pos[2] + r[2];
  r[0] -= P44_CamX; r[1] -= P44_CamY; r[2] -= P44_CamZ;
  P44_MatPtr = P44_ViewMatT;
  P44_Xform(r);
}

/* ---- 004af076: фара/огонь машины car — объект C (0110b24c), если повёрнут к камере (|угол| ≤ 900) ---- */
void P101_CarLight(int32_t car, const float *v, int32_t flags) {
#ifndef RE_HOOK_BUILD
  if (car < 0 || car >= 65) return;
#endif
  float *r = (float *)P95_ObjPtr((uint32_t)G0110B24C);
#ifndef RE_HOOK_BUILD
  if (r == NULL) return;
#endif
  int32_t vis = 1;
  uint8_t fx = P101_CarFx[car];
  uint16_t a0 = (uint16_t)P99_Cars[car].ang[0];
  uint32_t hd = flags == 0x80 ? (uint32_t)P99_Cars[car].heading : ((uint32_t)P99_Cars[car].heading + 0x800) & 0xfff;
  int32_t d = (int32_t)(((((uint32_t)-(int32_t)P59_AngB & 0xfffu) - hd) + 0x800) & 0xfff) - 0x800;
  if (900 < d || d < -900) vis = 0;
  r[0] = v[0]; r[1] = v[1]; r[2] = v[2]; r[3] = v[3];
  car_to_view(r, car);
  if (P95_Near <= r[2] && vis) {
    r[4] = r[0]; r[5] = r[1]; r[6] = r[2]; r[7] = r[3];
    wr32(&r[0x1a], flags);
    wr32(&r[0x1c], 0); wr32(&r[0x1d], 0);
    wr16(&r[0x19], P101_FxCol[(fx & 0x1f) >> 1]);
    wr16(&r[0x1b], a0);
    wr16((uint8_t *)r + 0x6e, (uint16_t)hd);
    G0110B24C += 0x78;
    G010FFA20++;
  }
}

/* ---- 004b9aec: полёт 100 обломков (P97_Debris, 0x3c) около игрока: покачивание, падение до дороги ---- */
void P101_DebrisFly(void) {
  uint8_t *r = P97_Debris;
  for (int32_t k = 100; k != 0; k--, r += 0x3c) {
    if ((rd16(r + 0x22) & 2) == 0) continue;
    P11_00ba52d0 = fround(rdf(r));
    int32_t dx = iabs(P11_00ba52d0 - P99_Cars[0].pos[0]);
    P11_00ba52d0 = fround(rdf(r + 8));
    int32_t dz = iabs(P11_00ba52d0 - P99_Cars[0].pos[2]);
    int32_t d = dx < dz ? dz + dx / 2 : dx + dz / 2;
    if (d < 0x34bd) {
      wr16(r + 0x34, (uint16_t)((rd16(r + 0x34) + r[0x38]) & 0xfff));
      wr16(r + 0x36, (uint16_t)((rd16(r + 0x36) + r[0x39]) & 0xfff));
      int32_t a1 = rd16s(r + 0x34), a2 = rd16s(r + 0x36);
      float c = P43_Sin[a1] + P43_Sin[a2];
      float c1 = P43_Sin[(uint32_t)(a1 + 0x400) & 0xfff], c2 = P43_Sin[(uint32_t)(a2 + 0x400) & 0xfff];
      wrf(r + 0x10, c * 10.0f);                    /* .rdata 0054612c */
      wrf(r + 0x18, (c1 + c2) * 10.0f);
      float w[4] = { 0, 0, 0, 0 };
      P94_Wobble(w, 0);
      int32_t h = P100_RoadHeightF((const float *)r);
      if (rdf(r + 4) < (float)(-10 - h)) {
        wrf(r, w[0] + rdf(r + 0x10) + rdf(r));
        wrf(r + 4, w[1] + rdf(r + 0x14) + rdf(r + 4));
        wrf(r + 8, w[2] + rdf(r + 0x18) + rdf(r + 8));
        wr16(r + 0x26, (uint16_t)((rd16(r + 0x26) + rd16(r + 0x28)) & 0xff));
      } else wrf(r + 4, (float)(-10 - h));
      wrf(r + 0x14, c + c + 3.0f);                  /* .rdata 00546034 */
    } else {
      wr16(r + 0x22, 0);
      PoolPush004AC755(rd16(r + 0x24));
    }
  }
}

/* ---- 0051d97e: 4 точки колёс машины на дороге: матрица машины (P98_MrkMat), смещения колёс модели (+0xe0, шаг 8) ---- */
void P101_WheelsGround(const uint8_t *car, float *out) {
  const float k = 1.0f / 4096.0f;   /* .rdata 00546134 */
  float *M = P98_MrkMat;
  M[3] = (float)rd16s(car + 10) * k;
  M[4] = (float)rd16s(car + 0xc) * k;
  M[5] = (float)rd16s(car + 0xe) * k;
  M[0] = -((float)rd16s(car + 4) * k);
  M[1] = -((float)rd16s(car + 6) * k);
  M[2] = -((float)rd16s(car + 8) * k);
  M[6] = -((float)rd16s(car + 0x10) * k);
  M[7] = -((float)rd16s(car + 0x12) * k);
  M[8] = -((float)rd16s(car + 0x14) * k);
  P44_MatPtr = M;
  const uint8_t *m = carmodel(car[2]);
  for (uint32_t i = 0; i < 4; i++) {
    float v[4];
    float lx = (float)rd16s(m + 0xe0 + i * 8);
    v[0] = (i & 2) == 0 ? lx - 25.0f : lx + 25.0f;   /* .rdata 005461f0 */
    v[1] = 0.0f;
    v[2] = (float)-rd16s(m + 0xe4 + ((i + 1) & 3) * 8);
    v[3] = 0.0f;
    P44_XformT(v);
    v[0] += (float)rd32(car + 200);
    v[2] += (float)rd32(car + 0xd0);
    out[0] = v[0];
    out[2] = v[2];
    out[1] = (float)P100_RoadHeightF(v);
    out += 4;
  }
}

/* небо: таблица имён значков .data 00562e28 (4 города × 10: день, ночь, дождь, ночь, рассвет; «+» — вторая половина) */
#ifdef RE_HOOK_BUILD
#  define SKYTAB ((const char *const *)(uintptr_t)0x00562e28)
#else
static const char *const SKYTAB[44] = {
  "PCSKY", 0, "MIANIGHT", 0, "MIAMRAIN", 0, "MIANIGHT", 0, "MIAMDAWN", 0,
  "SFRANSKY", "SFRANSK+", "NIGHTSKY", "NIGHTSK+", "SF_RAIN", "SF_RAIN+", "NIGHTSKY", "NIGHTSK+", "SF_DAWN", "SF_DAWN+",
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  "NY_SKY", 0, "NY_NIGHT", 0, "NY_RAIN", 0, "NY_NIGHT", 0, "NY_DUSK", 0, 0, 0, 0, 0 };
#endif
#ifndef RE_HOOK_BUILD
/* v2.27: шов неба. Купол — 4 модели-четверти (P79_ModelTab[0..3]) с кольцами вершин на одинаковой высоте, но координата v
   текстуры на кольцах в данных уровня у четвертей расходится (Майами: кольцо 29° — v 50/47/48/48, кольцо 8° — 115/116/115/115),
   поэтому на стыках облака и градиент сдвинуты на 1–3 строки — тонкий косой шов (есть и в оригинале 1999 г.).
   Только native и только UV (логика, геометрия, порядок рисования не меняются): по каждому кольцу (одинаковая высота y вершины)
   v всех четвертей приводится к медиане, если разброс 1..4 текселя; v <= 1.5 (шапка купола — одна строка текстуры) не трогается.
   Записи моделей неба: тип 4 (треугольник, 56 байт) и 5 (четырёхугольник, 68 байт): заголовок 4, плоскость 4, индексы вершин n×4,
   UV n×(float u, float v) в текселях, цвет 3×float. Другой тип — ничего не меняется. RE_SKYFIX=0 — без исправления. */
#define SKY_RINGS 16
int32_t P101_SkyUvFixed;   /* сколько координат v изменено при последней загрузке уровня (тесты) */
static int sky_rec_n(const uint8_t *r) { return r[0] == 4 ? 3 : r[0] == 5 ? 4 : 0; }
void P101_SkyUvFix(void) {
  P101_SkyUvFixed = 0;
  { const char *e = getenv("RE_SKYFIX"); if (e && e[0] == '0') return; }
  float ry[SKY_RINGS], rv[SKY_RINGS][64], target[SKY_RINGS]; int rn[SKY_RINGS], nring = 0;
  for (int pass = 0; pass < 2; pass++) {
    if (pass == 1) {
      for (int i = 0; i < nring; i++) {
        float lo = rv[i][0], hi = rv[i][0];
        for (int j = 1; j < rn[i]; j++) { if (rv[i][j] < lo) lo = rv[i][j]; if (rv[i][j] > hi) hi = rv[i][j]; }
        target[i] = -1.0f;
        if (rn[i] < 4 || hi - lo < 0.5f || hi - lo > 4.0f) continue;
        for (int a = 1; a < rn[i]; a++) for (int b = a; b > 0 && rv[i][b - 1] > rv[i][b]; b--) { float t = rv[i][b]; rv[i][b] = rv[i][b - 1]; rv[i][b - 1] = t; }
        target[i] = rv[i][rn[i] / 2];
      }
    }
    for (int k = 0; k < 4; k++) {
      uint8_t *m = (uint8_t *)P79_PTR(P79_ModelTab[k]);
      int nv = *(uint16_t *)(m + 0x14), nr = *(uint16_t *)(m + 0x16);
      const float *vv = (const float *)P79_PTR(*(uint32_t *)(m + 0x20));
      uint8_t *r = (uint8_t *)P79_PTR(*(uint32_t *)(m + 0x2c));
      for (int i = 0, n; i < nr; i++, r += 8 + n * 4 + n * 8 + 12) {
        n = sky_rec_n(r);
        if (!n) { if (pass == 0) return; break; }   /* незнакомая запись — ничего не меняем */
        for (int j = 0; j < n; j++) {
          int32_t vi; float v; memcpy(&vi, r + 8 + j * 4, 4); memcpy(&v, r + 8 + n * 4 + j * 8 + 4, 4);
          if (vi < 0 || vi >= nv || v <= 1.5f) continue;
          float y = vv[vi * 4 + 1]; int ri = 0;
          while (ri < nring && fabsf(ry[ri] - y) > 0.01f) ri++;
          if (pass == 0) {
            if (ri == nring) { if (nring == SKY_RINGS) continue; ry[nring] = y; rn[nring++] = 0; }
            if (rn[ri] < 64) rv[ri][rn[ri]++] = v;
          } else if (ri < nring && target[ri] >= 0.0f && v != target[ri]) {
            memcpy(r + 8 + n * 4 + j * 8 + 4, &target[ri], 4); P101_SkyUvFixed++;
          }
        }
      }
    }
  }
}
#endif
/* ---- 004ef3cd: масштаб моделей неба ×1.7, копия текстуры неба по погоде/времени на место дневной ---- */
/* v2.20: в native ссылка модели — смещение в арене карты, и первая модель уровня (небо, P79_ModelTab[0]) лежит по смещению 0.
   Прежняя проверка «ссылка == 0 → пропуск» (как пустой указатель оригинала) пропускала её: четверть купола оставалась в масштабе
   1/1.7 — ближе и ниже трёх других, на стыках — незакрашенная чёрная изогнутая полоса неба. Теперь пропуска нет (в оригинале
   его тоже нет: 004ef3cd масштабирует 00cfe7a0..ac безусловно); без арены (тесты) — выход. */
void P101_SkyInit(void) {
#ifndef RE_HOOK_BUILD
  if (P79_MBASE == 0) return;
#endif
  for (int32_t k = 0; k < 4; k++) P15_ScaleVertices((uint8_t *)P79_PTR(P79_ModelTab[k]), 1.7f, 1.7f, 1.7f);
  for (int32_t k = 0; k < 4; k++) P15_ScaleNormalW((uint8_t *)P79_PTR(P79_ModelTab[k]), 1.7f);
#ifndef RE_HOOK_BUILD
  P101_SkyUvFix();
#endif
  if (D_00b87e30 >= 4) return;
#ifndef RE_HOOK_BUILD
  if (D_00b87e30 < 0) return;
#endif
  int32_t base = D_00b87e30 * 10, i;
  if (P14_00b202d8 == 0 && P14_00b202dc == 0) i = base + P26_FxA * 4 + P14_00b87e84 * 2;
  else i = base + 8;
  if (i == base) return;
#ifndef RE_HOOK_BUILD
  if (i < 0 || i > 41) return;
#endif
  int32_t cnt = 0;
  uint32_t dslot = 0;
  for (; cnt < 2 && SKYTAB[i] != NULL; i++) {
    const uint8_t *s = P93_FindIcon(SKYTAB[base]);
#ifndef RE_HOOK_BUILD
    if (s == NULL) return;
#endif
    dslot = s[8];
    const uint8_t *t = P93_FindIcon(SKYTAB[i]);
    if (t == NULL) return;
    if (P41_Flag == 0)
      P15_BlitRect8(texpage(t[8]), t[9], t[10], (uint32_t)t[0xb] + 1, t[0xc] + 1, texpage(dslot), s[9], s[10]);
    else
      P15_BlitRect16(texpage(t[8]), t[9], t[10], (uint32_t)t[0xb] + 1, t[0xc] + 1, texpage(dslot), s[9], s[10]);
    base++;
    cnt++;
  }
  if (cnt != 0) P12_Fn0048A46B((int32_t)dslot, rd32(&g_01145a60[dslot * 0x10 + 4]));
}

/* ---- 0051b974: узел дороги под точкой (x,z) со стороны side: −1 — нет дороги, 1 — перекрёсток (P101_RdNode),
   0 — участок: узел/полоса/расстояния в 00c1cca0..00c1ccb8, P72_Id/P72_Low ---- */
int32_t P101_RoadNode(int32_t x, int32_t z, int8_t side) {
  P101_RdNode = 0xffff; P101_RdCell = 0xffff; P101_RdB2 = 0; P101_RdLane = 0;
  int32_t cx = (x + 0x2ee + P62_MapC64) / 0x5dc;
  int32_t cz = (P62_Map2C40 - (z - 0x2ee)) / 0x5dc;
  if (cx < 0 || P54_MapB1 <= cx || cz < 0 || P54_MapB2 <= cz) return -1;
  int32_t n = P62_MapN;
#ifndef RE_HOOK_BUILD
  if (n == 0) return -1;   /* в оригинале — деление на ноль */
#endif
  int32_t w = ((cx / n) & 1) + (((P72_Rows - 1) - cz / n) & 1) * 2;
  int32_t idx = (cz - (cz / n) * n) * n + (cx - (cx / n) * n);
  const uint16_t *ta = (const uint16_t *)P54_RoadA[w];
  const uint32_t *tb = (const uint32_t *)P54_RoadB[w];
#ifndef RE_HOOK_BUILD
  if (ta == NULL || tb == NULL) return -1;
#endif
  uint16_t c = ta[idx];
  uint32_t v = tb[idx];
  P101_RdLeft = 0x7fffffff;
  P101_RdDist = 0x7fffffff;
  if (c == 0xffff) return -1;
  if (((int32_t)(int16_t)c & 0xc000) != 0) { P101_RdNode = c & 0x3fff; return 1; }
  P72_Id = (uint16_t)(((int32_t)v >> 16) & 0xc3ff);
  P72_Low = (int32_t)(v & 0xffff);
  P101_RdCell = c;
  int32_t node = (int16_t)c;
  const uint8_t *nd = rec(P11_00bf1c40, sizeof P11_00bf1c40, node, 0x42);
  uint16_t up = rd16(nd + 2), alt = rd16(nd + 4);
  uint32_t lane = ((uint32_t)(uint8_t)side + 2) & 3;
  if (rd16s(rec(P11_00c1ed80, sizeof P11_00c1ed80, (int16_t)up, 0x2c) + 0xa + lane * 8) == node) P101_RdNode = up;
  else P101_RdNode = alt;
  const uint8_t *sl = rec(P11_00c1ed80, sizeof P11_00c1ed80, (int16_t)P101_RdNode, 0x2c);
  P101_RdLane = rd16s(sl + 0xc + lane * 8);
  if (sl[2] == 1) P101_RdLane = 4;
  const uint8_t *rc = rec(P11_00c12c60, sizeof P11_00c12c60, node, 0x14);
  int32_t d = 0;   /* side > 3: в оригинале неинициализированная локальная */
  switch ((uint8_t)side) {
  case 0: d = -(rd32(rc + 4) * 0x5dc - 0x2ee + z); break;
  case 1: d = (rd32(rc + 8) + 1) * 0x5dc - (x + 0x2ee); break;
  case 2: d = (rd32(rc + 0xc) + 1) * 0x5dc - 0x2ee + z; break;
  case 3: d = -(rd32(rc) * 0x5dc - (x + 0x2ee)); break;
  default: break;
  }
  P101_RdDist = d;
  P101_RdLeft = rd16s(nd + 8) * 0x5dc - d;
  return 0;
}

/* ---- 004f29f7: маска зеркала радиуса r (буфер 00b31efc — адрес DebugMalloc) ---- */
void P101_MirrorMaskR(float r) {
  const int32_t N = 0x1f;
  if (P11_00b31efc != 0) FreeBuffer_004F30E6();
  uint8_t *buf = (uint8_t *)P98_DebugMalloc(0x8000, "D:\\Driver\\Game\\mirror.c", 0x109);
  P11_00b31efc = (int32_t)re_addr(buf);
  if (buf == NULL) { P11_00c823d0 = 0; P13_00b31f04 = 0; return; }
  P14_Fn0048DB65(buf, 0x8000);
  for (int32_t row = 0; row < 0x100; row++) {
    uint8_t g[964];
    P14_Fn0048DB65(g, (uint32_t)(N * N));
    const uint8_t *fr = &P55_Frustum[row * 0x80];
    int32_t k = rd16s(fr) == -1 ? 0 : rd16s(fr);
    const uint8_t *sp = fr + 4 + k * 4;
    for (; k < N; k++, sp += 4) {
      if (rd16s(sp) == -1) continue;
      uint8_t *c = g + rd16s(sp) + k * N;
      for (int32_t i = 0; i < rd16s(sp + 2); i++) *c++ = 1;
    }
    for (int32_t y = -0xf; y < 0x10; y++) {
      int32_t i = (y + 0xf) * N;
      for (int32_t x = -0xf; x < 0x10; x++, i++)
        if (g[i] != 0 && r * r < (float)(x * x + y * y)) g[i] = 0;
    }
    P94_RowSpans((int16_t *)(buf + row * 0x80), g);
  }
  P11_00c823d0 = 1;
}

/* ---- 004aecb1: два следа шин машины car (объекты C, флаг 0x100), пока их меньше 201 ---- */
void P101_CarSkids(int32_t car) {
#ifndef RE_HOOK_BUILD
  if (car < 0 || car >= 65) return;
#endif
  const uint8_t *m = carmodel(P99_Cars[car].f00[2]);
  if (0xc8 < G010FFA20) return;
  for (int32_t k = 0; k < 2; k++) {
    int32_t c; float sx;
    if (k == 0) { c = P99_Cars[car].f12c; sx = rdf(m + 0x80); }
    else { c = P99_Cars[car].f128; sx = -rdf(m + 0x80); }
    if (c >= 500) continue;
    float *r = (float *)P95_ObjPtr((uint32_t)G0110B24C);
#ifndef RE_HOOK_BUILD
    if (r == NULL) return;
#endif
    r[0] = sx;
    r[1] = rdf(m + 0x84);
    r[2] = rdf(m + 0x88) - (float)(c >> 7);
    car_to_view(r, car);
    if (P95_Near <= r[2]) {
      r[6] = r[2];
      wr32(&r[0x1a], 0x100);
      wr32(&r[0x1d], 0); wr32(&r[0x1c], 0);
      G0110B24C += 0x78;
      G010FFA20++;
    }
  }
}

/* z → обратная глубина из таблицы 00ba53a0 (в native индекс вне таблицы — 0) */
static float zinv(float z) {
  P85_ZI = (int32_t)lrintf(z);   /* fist */
#ifndef RE_HOOK_BUILD
  if (P85_ZI < 0 || P85_ZI >= (int32_t)(RE_OOW_N)) return 0.0f;
#endif
  return RE_OOW(P85_ZI);
}

/* ---- 00528bb7: v[3..5] → вид по транспонированной матрице + смещение; x,y → v[6],v[7]; z → v[5]; экран → v[3],v[4] ---- */
void P101_ProjT(float *v) {
  const float *M = P44_MatPtr;
  uint32_t tag = P44_XformTag;
  float x = v[3], y = v[4], z = v[5];
  float sx = x * M[0] + (y * M[3] + (z * M[6] + P44_BiasX));
  float sy = (x * M[1] + P44_BiasY) + (y * M[4] + z * M[7]);
  float sz = (x * M[2] + P44_BiasZ + y * M[5]) + z * M[8];
  v[6] = sx; v[7] = sy;
  float iz = zinv(sz);
  v[5] = sz;
  memcpy(&v[0], &tag, 4);
  v[1] = iz;
  float a = v[1] * P43_ScaleA;
  P85_Tmp = v[6] * a;
  float py = a * v[7];
  v[3] = P85_Tmp + P101_ScrX0;
  v[4] = py + P101_ScrY0;
}

/* ---- 00528c91: v[3..5] = M·v[3..5] + смещение, v[0] = метка кадра ---- */
void P101_XformBias2(float *v) {
  const float *M = P44_MatPtr;
  uint32_t tag = P44_XformTag;
  float x = v[3], y = v[4], z = v[5];
  v[3] = x * M[0] + (y * M[1] + (z * M[2] + P44_BiasX));
  v[4] = (x * M[3] + P44_BiasY) + (y * M[4] + z * M[5]);
  v[5] = (x * M[6] + P44_BiasZ + y * M[7]) + z * M[8];
  memcpy(&v[0], &tag, 4);
}

/* ---- 00528d17: v[3..5] = M·v + смещение → экран (P43_OffX/OffY − 0.5) в v[3],v[4], z в v[5], 1/z в v[1] ---- */
void P101_Proj(float *v) {
  const float *M = P44_MatPtr;
  uint32_t tag = P44_XformTag;
  float x = v[3], y = v[4], z = v[5];
  P85_Tmp = x * M[0] + (y * M[1] + (z * M[2] + P44_BiasX));
  P101_TmpY = (x * M[3] + P44_BiasY) + (y * M[4] + z * M[5]);
  float sz = (x * M[6] + P44_BiasZ + y * M[7]) + z * M[8];
  float iz = zinv(sz);
  v[5] = sz;
  memcpy(&v[0], &tag, 4);
  v[1] = iz;
  float a = v[1] * P43_ScaleA;
  P85_Tmp = P85_Tmp * a;
  float py = a * P101_TmpY;
  v[3] = P85_Tmp + P43_OffX - P43_Half;
  v[4] = py + P43_OffY - P43_Half;
}

/* ---- 005291ed: заливка rows строк (шаг 640 байт) по w байт блоками 32 байтом c ---- */
void P101_FillRows(uint8_t *dst, int32_t w, int32_t rows, uint8_t c) {
  uint32_t v = (uint32_t)c * 0x01010101u;
  for (; rows > 0; rows--, dst += 0x280)
    for (int32_t x = 0; x < w; x += 0x20)
      for (int32_t j = 0; j < 8; j++) memcpy(dst + x + j * 4, &v, 4);
}

/* ---- 00529253: строки 640 индексов → 16-битные пиксели по P101_PalLfb (шаг строки P100_LfbPitch) ---- */
void P101_Pal16(const uint8_t *src, uint8_t *dst, int32_t unused, int32_t rows) {
  (void)unused;
#ifndef RE_HOOK_BUILD
  if (rows <= 0) return;   /* в оригинале do-while: 0 — 2^32 строк */
#endif
  do {
    for (int32_t k = 0xa0; k != 0; k--, src += 4, dst += 8) {
      uint32_t a = (P101_PalLfb[src[1]] << 16) | P101_PalLfb[src[0]];
      uint32_t b = (P101_PalLfb[src[3]] << 16) | P101_PalLfb[src[2]];
      memcpy(dst, &a, 4); memcpy(dst + 4, &b, 4);
    }
    dst += P100_LfbPitch - 0x500;
  } while (--rows != 0);
}

/* ---- 005292d1: строки 640 индексов → 32-битные пиксели по P101_PalLfb ---- */
void P101_Pal32(const uint8_t *src, uint8_t *dst, int32_t unused, int32_t rows) {
  (void)unused;
#ifndef RE_HOOK_BUILD
  if (rows <= 0) return;
#endif
  do {
    for (int32_t k = 0x50; k != 0; k--, src += 8, dst += 0x20)
      for (int32_t j = 0; j < 8; j++) memcpy(dst + j * 4, &P101_PalLfb[src[j]], 4);
    dst += P100_LfbPitch - 0xa00;
  } while (--rows != 0);
}

/* отсечение ребра a–b (вершины вида: x +0xc, y +0x10, z +0x14) ближней (P95_Near, z точки = 50) или дальней (01270c24)
   плоскостью с n атрибутами ua/ub → поля slot[] выходных вершин (12 float, P100_ClipOut, счётчик P100_ClipN) */
static void clip_attr(const uint8_t *a, const uint8_t *b, int32_t far, const float *ua, const float *ub, const uint8_t *slot, int32_t n) {
  float P = far ? Q01270C24 : P95_Near, zc = far ? Q01270C24 : 50.0f;
  float za = rdf(a + 0x14), zb = rdf(b + 0x14);
  int in_a = far ? za <= P : P <= za, in_b = far ? zb <= P : P <= zb;
  if (!(in_a || in_b)) return;
#ifndef RE_HOOK_BUILD
  if (P100_ClipOut == NULL) return;
#endif
  float *o = P100_ClipOut;
  if (!in_a || !in_b) {
    if (in_a || !in_b) {
      float t = (za - P) / (za - zb);
      for (int32_t i = 0; i < n; i++) o[slot[i]] = ua[i] - (ua[i] - ub[i]) * t;
      o[0] = rdf(a + 0xc) - (rdf(a + 0xc) - rdf(b + 0xc)) * t;
      o[1] = rdf(a + 0x10) - (rdf(a + 0x10) - rdf(b + 0x10)) * t;
      o[2] = zc;
      P100_ClipN += 1;
      P100_ClipOut += 0xc;
    } else {
      float t = (zb - P) / (zb - za);
      for (int32_t i = 0; i < n; i++) o[slot[i]] = ub[i] - (ub[i] - ua[i]) * t;
      o[0] = rdf(b + 0xc) - (rdf(b + 0xc) - rdf(a + 0xc)) * t;
      o[1] = rdf(b + 0x10) - (rdf(b + 0x10) - rdf(a + 0x10)) * t;
      o[2] = zc;
      o += 0xc;
      for (int32_t i = 0; i < n; i++) o[slot[i]] = ub[i];
      o[0] = rdf(b + 0xc); o[1] = rdf(b + 0x10); o[2] = zb;
      P100_ClipN += 2;
      P100_ClipOut += 0x18;
    }
  } else {
    for (int32_t i = 0; i < n; i++) o[slot[i]] = ub[i];
    o[0] = rdf(b + 0xc); o[1] = rdf(b + 0x10); o[2] = zb;
    P100_ClipN += 1;
    P100_ClipOut += 0xc;
  }
}
static const uint8_t k_s45[] = { 4, 5 }, k_s456[] = { 4, 5, 6 }, k_s789[] = { 7, 8, 9 };
static const uint8_t k_s5a[] = { 4, 5, 10, 11, 6 }, k_s5b[] = { 7, 8, 9, 4, 5 };

/* ---- 0042da16 / 0042f124: ближняя / дальняя плоскость, 2 атрибута (u, v → [4], [5]) ---- */
void P101_ClipNearUV(const uint8_t *a, const uint8_t *b, float ua0, float ua1, float ub0, float ub1) {
  const float ua[2] = { ua0, ua1 }, ub[2] = { ub0, ub1 };
  clip_attr(a, b, 0, ua, ub, k_s45, 2);
}
void P101_ClipFarUV(const uint8_t *a, const uint8_t *b, float ua0, float ua1, float ub0, float ub1) {
  const float ua[2] = { ua0, ua1 }, ub[2] = { ub0, ub1 };
  clip_attr(a, b, 1, ua, ub, k_s45, 2);
}
/* ---- 0042dce8: ближняя, 3 атрибута → [4], [5], [6] ---- */
void P101_ClipNearUVW(const uint8_t *a, const uint8_t *b, float ua0, float ua1, float ua2, float ub0, float ub1, float ub2) {
  const float ua[3] = { ua0, ua1, ua2 }, ub[3] = { ub0, ub1, ub2 };
  clip_attr(a, b, 0, ua, ub, k_s456, 3);
}
/* ---- 0042e3c7: ближняя, 3 атрибута (цвет) → [7], [8], [9] ---- */
void P101_ClipNearRGB(const uint8_t *a, const uint8_t *b, float ua0, float ua1, float ua2, float ub0, float ub1, float ub2) {
  const float ua[3] = { ua0, ua1, ua2 }, ub[3] = { ub0, ub1, ub2 };
  clip_attr(a, b, 0, ua, ub, k_s789, 3);
}
/* ---- 0042e007: ближняя, 5 атрибутов → [4], [5], [10], [11], [6] ---- */
void P101_ClipNear5A(const uint8_t *a, const uint8_t *b, float ua0, float ua1, float ua2, float ua3, float ua4,
                     float ub0, float ub1, float ub2, float ub3, float ub4) {
  const float ua[5] = { ua0, ua1, ua2, ua3, ua4 }, ub[5] = { ub0, ub1, ub2, ub3, ub4 };
  clip_attr(a, b, 0, ua, ub, k_s5a, 5);
}
/* ---- 0042e6e6: ближняя, 5 атрибутов (цвет + u, v) → [7], [8], [9], [4], [5] ---- */
void P101_ClipNear5B(const uint8_t *a, const uint8_t *b, float ua0, float ua1, float ua2, float ua3, float ua4,
                     float ub0, float ub1, float ub2, float ub3, float ub4) {
  const float ua[5] = { ua0, ua1, ua2, ua3, ua4 }, ub[5] = { ub0, ub1, ub2, ub3, ub4 };
  clip_attr(a, b, 0, ua, ub, k_s5b, 5);
}
