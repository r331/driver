/* 50 routines around cars, traffic and cops: car lights, traffic placement and collisions,
   mission HUD bars, the cop "can see the player" tick and cop paths, director free camera and
   menu nodes, CONFIG.DAT snapshot, car reset, road-cell scanning and dust, lamp colours,
   radar walls, ghost trail, box contacts and clipping, road side, tyre tracks.
   English headers below summarise the Russian notes at each function. */
/* v1.47: 23 функции (см. ported102.h). Стандарт указателей v1.42: адреса узлов пути копа (+0xc60, узел +0 следующий),
   ссылка копа на машину (+0xcd0), адреса переменных скрипта полос HUD, ссылки моделей (P79_PTR) — uint32_t + re_ptr/re_addr;
   глобальные скалярные указатели (P56_Sprite, P100_RadarIcon, P44_MatPtr) — родные. Узлы дороги — P11_00bf1c40 (nodetab.h). */
#include "ported102.h"
#include "carfields.h"
#include "nodetab.h"
#include "cartab.h"
#include "director.h"
#include "smallfuncs.h"
#include "smallfuncs2.h"
#include "uihandlers3.h"
#include "menustate.h"
#include "widgets.h"
#include "globalsets.h"
#include "ported4.h"
#include "ported5.h"
#include "ported6.h"
#include "ported7.h"
#include "ported11.h"
#include "ported12.h"
#include "ported13.h"
#include "ported14.h"
#include "ported16.h"
#include "ported19.h"
#include "ported20.h"
#include "ported21.h"
#include "ported29.h"
#include "ported35.h"
#include "ported40.h"
#include "ported42.h"
#include "ported43.h"
#include "ported44.h"
#include "ported45.h"
#include "ported51.h"
#include "ported54.h"
#include "ported55.h"
#include "ported56.h"
#include "ported59.h"
#include "ported60.h"
#include "ported61.h"
#include "ported62.h"
#include "ported63.h"
#include "ported71.h"
#include "ported72.h"
#include "ported75.h"
#include "ported76.h"
#include "ported77.h"
#include "ported79.h"
#include "ported88.h"
#include "ported91.h"
#include "ported93.h"
#include "ported94.h"
#include "ported95.h"
#include "ported96.h"
#include "ported97.h"
#include "ported98.h"
#include "ported99.h"
#include "ported100.h"
#include "ported101.h"
#include "ported52.h"
#include "dirnodes.h"
#include <math.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P102_HudDmg")
#undef P102_HudDmg
#pragma push_macro("P102_HudDmg") /*gvi*/
#undef P102_HudDmg /*gvi*/
p102_hud_t P102_HudDmg;
#pragma pop_macro("P102_HudDmg") /*gvi*/
#pragma pop_macro("P102_HudDmg")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P102_HudFel")
#undef P102_HudFel
#pragma push_macro("P102_HudFel") /*gvi*/
#undef P102_HudFel /*gvi*/
p102_hud_t P102_HudFel;
#pragma pop_macro("P102_HudFel") /*gvi*/
#pragma pop_macro("P102_HudFel")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P102_DmgVar")
#undef P102_DmgVar
#pragma push_macro("P102_DmgVar") /*gvi*/
#undef P102_DmgVar /*gvi*/
uint32_t P102_DmgVar;
#pragma pop_macro("P102_DmgVar") /*gvi*/
#pragma pop_macro("P102_DmgVar")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P102_FelVar")
#undef P102_FelVar
#pragma push_macro("P102_FelVar") /*gvi*/
#undef P102_FelVar /*gvi*/
uint32_t P102_FelVar;
#pragma pop_macro("P102_FelVar") /*gvi*/
#pragma pop_macro("P102_FelVar")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P102_OppVar")
#undef P102_OppVar
#pragma push_macro("P102_OppVar") /*gvi*/
#undef P102_OppVar /*gvi*/
uint32_t P102_OppVar;
#pragma pop_macro("P102_OppVar") /*gvi*/
#pragma pop_macro("P102_OppVar")
#endif
GAME_VAR_DEF(uint8_t *, P102_MapIcon2, 0x00c80894)
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P102_HudF4")
#undef P102_HudF4
#pragma push_macro("P102_HudF4") /*gvi*/
#undef P102_HudF4 /*gvi*/
int32_t P102_HudF4;
#pragma pop_macro("P102_HudF4") /*gvi*/
#pragma pop_macro("P102_HudF4")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P102_DmgMax")
#undef P102_DmgMax
#pragma push_macro("P102_DmgMax") /*gvi*/
#undef P102_DmgMax /*gvi*/
int32_t P102_DmgMax;
#pragma pop_macro("P102_DmgMax") /*gvi*/
#pragma pop_macro("P102_DmgMax")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P102_B52A3C")
#undef P102_B52A3C
#pragma push_macro("P102_B52A3C") /*gvi*/
#undef P102_B52A3C /*gvi*/
int32_t P102_B52A3C;
#pragma pop_macro("P102_B52A3C") /*gvi*/
#pragma pop_macro("P102_B52A3C")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P102_DustPts")
#undef P102_DustPts
#pragma push_macro("P102_DustPts") /*gvi*/
#undef P102_DustPts /*gvi*/
p102_pts_t P102_DustPts;
#pragma pop_macro("P102_DustPts") /*gvi*/
#pragma pop_macro("P102_DustPts")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P102_DustN")
#undef P102_DustN
#pragma push_macro("P102_DustN") /*gvi*/
#undef P102_DustN /*gvi*/
int32_t P102_DustN;
#pragma pop_macro("P102_DustN") /*gvi*/
#pragma pop_macro("P102_DustN")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P102_NbrC")
#undef P102_NbrC
#pragma push_macro("P102_NbrC") /*gvi*/
#undef P102_NbrC /*gvi*/
int16_t P102_NbrC;
#pragma pop_macro("P102_NbrC") /*gvi*/
#pragma pop_macro("P102_NbrC")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P102_Corners")
#undef P102_Corners
#pragma push_macro("P102_Corners") /*gvi*/
#undef P102_Corners /*gvi*/
p102_i16_t P102_Corners;
#pragma pop_macro("P102_Corners") /*gvi*/
#pragma pop_macro("P102_Corners")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P102_GhostMat")
#undef P102_GhostMat
#pragma push_macro("P102_GhostMat") /*gvi*/
#undef P102_GhostMat /*gvi*/
p102_m16_t P102_GhostMat;
#pragma pop_macro("P102_GhostMat") /*gvi*/
#pragma pop_macro("P102_GhostMat")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P102_SixFlag")
#undef P102_SixFlag
#pragma push_macro("P102_SixFlag") /*gvi*/
#undef P102_SixFlag /*gvi*/
int32_t P102_SixFlag;
#pragma pop_macro("P102_SixFlag") /*gvi*/
#pragma pop_macro("P102_SixFlag")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P102_D06A00")
#undef P102_D06A00
#pragma push_macro("P102_D06A00") /*gvi*/
#undef P102_D06A00 /*gvi*/
int32_t P102_D06A00;
#pragma pop_macro("P102_D06A00") /*gvi*/
#pragma pop_macro("P102_D06A00")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P102_D06A04")
#undef P102_D06A04
#pragma push_macro("P102_D06A04") /*gvi*/
#undef P102_D06A04 /*gvi*/
int32_t P102_D06A04;
#pragma pop_macro("P102_D06A04") /*gvi*/
#pragma pop_macro("P102_D06A04")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P102_BlkA")
#undef P102_BlkA
#pragma push_macro("P102_BlkA") /*gvi*/
#undef P102_BlkA /*gvi*/
p102_d68_t P102_BlkA;
#pragma pop_macro("P102_BlkA") /*gvi*/
#pragma pop_macro("P102_BlkA")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P102_BlkB")
#undef P102_BlkB
#pragma push_macro("P102_BlkB") /*gvi*/
#undef P102_BlkB /*gvi*/
p102_d68_t P102_BlkB;
#pragma pop_macro("P102_BlkB") /*gvi*/
#pragma pop_macro("P102_BlkB")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P102_BlkC")
#undef P102_BlkC
#pragma push_macro("P102_BlkC") /*gvi*/
#undef P102_BlkC /*gvi*/
p102_d68_t P102_BlkC;
#pragma pop_macro("P102_BlkC") /*gvi*/
#pragma pop_macro("P102_BlkC")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P102_D0DD74")
#undef P102_D0DD74
#pragma push_macro("P102_D0DD74") /*gvi*/
#undef P102_D0DD74 /*gvi*/
int32_t P102_D0DD74;
#pragma pop_macro("P102_D0DD74") /*gvi*/
#pragma pop_macro("P102_D0DD74")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P102_D0DD78")
#undef P102_D0DD78
#pragma push_macro("P102_D0DD78") /*gvi*/
#undef P102_D0DD78 /*gvi*/
int32_t P102_D0DD78;
#pragma pop_macro("P102_D0DD78") /*gvi*/
#pragma pop_macro("P102_D0DD78")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P102_D0DD7C")
#undef P102_D0DD7C
#pragma push_macro("P102_D0DD7C") /*gvi*/
#undef P102_D0DD7C /*gvi*/
int32_t P102_D0DD7C;
#pragma pop_macro("P102_D0DD7C") /*gvi*/
#pragma pop_macro("P102_D0DD7C")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P102_D0DD80")
#undef P102_D0DD80
#pragma push_macro("P102_D0DD80") /*gvi*/
#undef P102_D0DD80 /*gvi*/
int32_t P102_D0DD80;
#pragma pop_macro("P102_D0DD80") /*gvi*/
#pragma pop_macro("P102_D0DD80")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P102_D0DD84")
#undef P102_D0DD84
#pragma push_macro("P102_D0DD84") /*gvi*/
#undef P102_D0DD84 /*gvi*/
int32_t P102_D0DD84;
#pragma pop_macro("P102_D0DD84") /*gvi*/
#pragma pop_macro("P102_D0DD84")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P102_D0DDD0")
#undef P102_D0DDD0
#pragma push_macro("P102_D0DDD0") /*gvi*/
#undef P102_D0DDD0 /*gvi*/
p102_i4_t P102_D0DDD0;
#pragma pop_macro("P102_D0DDD0") /*gvi*/
#pragma pop_macro("P102_D0DDD0")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P102_D0DDE8")
#undef P102_D0DDE8
#pragma push_macro("P102_D0DDE8") /*gvi*/
#undef P102_D0DDE8 /*gvi*/
int32_t P102_D0DDE8;
#pragma pop_macro("P102_D0DDE8") /*gvi*/
#pragma pop_macro("P102_D0DDE8")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P102_D0DDEC")
#undef P102_D0DDEC
#pragma push_macro("P102_D0DDEC") /*gvi*/
#undef P102_D0DDEC /*gvi*/
int32_t P102_D0DDEC;
#pragma pop_macro("P102_D0DDEC") /*gvi*/
#pragma pop_macro("P102_D0DDEC")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P102_D0DDF0")
#undef P102_D0DDF0
#pragma push_macro("P102_D0DDF0") /*gvi*/
#undef P102_D0DDF0 /*gvi*/
int32_t P102_D0DDF0;
#pragma pop_macro("P102_D0DDF0") /*gvi*/
#pragma pop_macro("P102_D0DDF0")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P102_D077A0")
#undef P102_D077A0
#pragma push_macro("P102_D077A0") /*gvi*/
#undef P102_D077A0 /*gvi*/
p102_i4_t P102_D077A0;
#pragma pop_macro("P102_D077A0") /*gvi*/
#pragma pop_macro("P102_D077A0")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P102_B2EA38")
#undef P102_B2EA38
#pragma push_macro("P102_B2EA38") /*gvi*/
#undef P102_B2EA38 /*gvi*/
p102_i4_t P102_B2EA38;
#pragma pop_macro("P102_B2EA38") /*gvi*/
#pragma pop_macro("P102_B2EA38")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P102_D04D14")
#undef P102_D04D14
#pragma push_macro("P102_D04D14") /*gvi*/
#undef P102_D04D14 /*gvi*/
int32_t P102_D04D14;
#pragma pop_macro("P102_D04D14") /*gvi*/
#pragma pop_macro("P102_D04D14")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P102_5624A4")
#undef P102_5624A4
#pragma push_macro("P102_5624A4") /*gvi*/
#undef P102_5624A4 /*gvi*/
int32_t P102_5624A4;
#pragma pop_macro("P102_5624A4") /*gvi*/
#pragma pop_macro("P102_5624A4")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P102_C816F8")
#undef P102_C816F8
#pragma push_macro("P102_C816F8") /*gvi*/
#undef P102_C816F8 /*gvi*/
int32_t P102_C816F8;
#pragma pop_macro("P102_C816F8") /*gvi*/
#pragma pop_macro("P102_C816F8")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P102_C816FC")
#undef P102_C816FC
#pragma push_macro("P102_C816FC") /*gvi*/
#undef P102_C816FC /*gvi*/
int32_t P102_C816FC;
#pragma pop_macro("P102_C816FC") /*gvi*/
#pragma pop_macro("P102_C816FC")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P102_57B6A8")
#undef P102_57B6A8
#pragma push_macro("P102_57B6A8") /*gvi*/
#undef P102_57B6A8 /*gvi*/
int32_t P102_57B6A8;
#pragma pop_macro("P102_57B6A8") /*gvi*/
#pragma pop_macro("P102_57B6A8")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P102_57B6F8")
#undef P102_57B6F8
#pragma push_macro("P102_57B6F8") /*gvi*/
#undef P102_57B6F8 /*gvi*/
int32_t P102_57B6F8;
#pragma pop_macro("P102_57B6F8") /*gvi*/
#pragma pop_macro("P102_57B6F8")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P102_BDF9E0")
#undef P102_BDF9E0
#pragma push_macro("P102_BDF9E0") /*gvi*/
#undef P102_BDF9E0 /*gvi*/
p102_i16_t P102_BDF9E0;
#pragma pop_macro("P102_BDF9E0") /*gvi*/
#pragma pop_macro("P102_BDF9E0")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P102_B5A914")
#undef P102_B5A914
#pragma push_macro("P102_B5A914") /*gvi*/
#undef P102_B5A914 /*gvi*/
int32_t P102_B5A914;
#pragma pop_macro("P102_B5A914") /*gvi*/
#pragma pop_macro("P102_B5A914")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P102_HitFrame")
#undef P102_HitFrame
#pragma push_macro("P102_HitFrame") /*gvi*/
#undef P102_HitFrame /*gvi*/
int32_t P102_HitFrame;
#pragma pop_macro("P102_HitFrame") /*gvi*/
#pragma pop_macro("P102_HitFrame")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P102_ObjBKey")
#undef P102_ObjBKey
#pragma push_macro("P102_ObjBKey") /*gvi*/
#undef P102_ObjBKey /*gvi*/
int32_t P102_ObjBKey;
#pragma pop_macro("P102_ObjBKey") /*gvi*/
#pragma pop_macro("P102_ObjBKey")
#endif

#define RE_MEMRW_LOCAL16   /* keep the local 16-bit helpers below (hook object identity, see memrw.h) */
#include "memrw.h"
/* rd16s — Unaligned int16 read. */
static int16_t rd16s(const void *p) { int16_t v; memcpy(&v, p, 2); return v; }
/* wr16 — Unaligned uint16 write. */
static void wr16(void *p, uint16_t v) { memcpy(p, &v, 2); }
/* wrf — Store a float (bit copy). */
static void wrf(void *p, float v) { memcpy(p, &v, 4); }
/* rdf_ — Unaligned float read. */
static float rdf_(const void *p) { float v; memcpy(&v, p, 4); return v; }
/* fbits — Bit pattern of a float. */
static uint32_t fbits(float v) { uint32_t u; memcpy(&u, &v, 4); return u; }
/* mul — int32 multiply with 32-bit wrap-around (imul). */
static int32_t mul(int32_t a, int32_t b) { return (int32_t)((uint32_t)a * (uint32_t)b); }   /* imul с переполнением */
/* carp — Car record i of P99_Cars. */
static uint8_t *carp(int32_t i) { return (uint8_t *)&P99_Cars[i]; }
/* запись модели машины m (00d0cc60 + m*0x16c); в native — в пределах S_00D0CC60 (0x4000 байт), иначе нули */
/* carmodel — Car model record m (00d0cc60 + m * 0x16c).  Native: zero record when m is outside the image. */
static const uint8_t *carmodel(uint32_t m) {
#ifndef RE_HOOK_BUILD
  static const uint8_t zero[0x16c];
  if ((m + 1) * 0x16c > sizeof S_00D0CC60) return zero;
#endif
  return S_00D0CC60 + m * 0x16c;
}
/* машина трафика i по указателю 0113a6c4 (в Game.exe — 00d07908 = запись 1); в native, если указатель не задан, — P99_Cars[1 + i] */
/* tcar — Traffic car i (record i + 1) via pointer 0113a6c4.  Native: falls back to P99_Cars when unset. */
static uint8_t *tcar(int32_t i) {
#ifndef RE_HOOK_BUILD
  if (P59_CarsTab == NULL) return (i + 1 >= 0 && i + 1 < P99_CARS_N) ? carp(i + 1) : carp(P99_CARS_N - 1);
#endif
  return P59_CarsTab + (uint32_t)i * 0x148;
}
/* trec — Traffic record i (TREC_* in trafficrec.h).  Native: a zeroed dummy outside 0..0x3f. */
static uint8_t *trec(int32_t i) {
#ifndef RE_HOOK_BUILD
  if (i < 0 || i >= 0x40) { static uint8_t dummy[0x54]; memset(dummy, 0, sizeof dummy); return dummy; }
#endif
  return &TrafficRecs[i * 0x54];
}

/* ---- 004aef57: фары машины car (side 0 — передние, 1 — задние, 2 — обе), пока счётчики повреждений < 500 ---- */
/* P102_CarLights — Game.exe 004aef57, cdecl.  Head- / tail-lights of car `car` (side 0 front, 1 rear, 2 both), drawn only while the damage
   counters of that side are below 500. */
void P102_CarLights(int32_t car, int32_t side) {
#ifndef RE_HOOK_BUILD
  if (car < 0 || car >= 65) return;
#endif
  const uint8_t *c = carp(car);
  const uint8_t *m = carmodel(c[2]);
  if (side == 0 || side == 2) {
    if (rd32(c + 0x128) < 500) P101_CarLight(car, (const float *)(m + 0x40), 0x80);
    if (rd32(c + 0x120) < 500) P101_CarLight(car, (const float *)(m + 0x20), 0x40);
  }
  if (side == 1 || side == 2) {
    if (rd32(c + 0x12c) < 500) P101_CarLight(car, (const float *)(m + 0x50), 0x80);
    if (rd32(c + 0x11c) < 500) P101_CarLight(car, (const float *)(m + 0x30), 0x40);
  }
  if (G6_00B5A778 == 0) P101_CarFx[car] = (uint8_t)((P101_CarFx[car] + 1) & 0x1f);
}

/* ---- 00496372: можно ли поставить машину трафика в (x, z): узел дороги, далеко от игрока и от машин хозяина owner ---- */
/* P102_TrafficRoom — Game.exe 00496372, cdecl.  May a traffic car be placed at (x, z)?  Needs a road node there, distance from the player, and
   no car of `owner` nearby. */
int32_t P102_TrafficRoom(int32_t x, int32_t z, int32_t owner, uint32_t flags) {
  int32_t side = Round1024(P99_Cars[0].heading);
  if ((int16_t)P101_RoadNode(x, z, (int8_t)side) != 0) return 0;
  if ((int16_t)P101_RdCell != -1 && (int32_t)(int16_t)P101_RdCell != G011426F8) { P12_Fn00496505(); return 0; }
  if (P101_RdDist < 30000) { P12_Fn00496505(); return 0; }
  for (int32_t i = 0; i < P51_TrafficN; i++) {
    const uint8_t *r = trec(i);
    if (r[1] != 0 && rd32(r + 0x28) == owner) {
      int32_t d = (flags & 1) == 0 ? z - rd32(tcar(i) + 0xd0) : x - rd32(tcar(i) + 0xc8);
      if (iabs(d) < 2000) return 0;
    }
  }
  return 1;
}

/* коробка машины c для P101_BoxHit: оси (матрица +4), центр (+0x18), размеры модели (+0x164..+0x168) */
/* car_box — Collision box of car c for P101_BoxHit: axes from the orientation matrix (CAR_MAT), centre
   CAR_POS2, half sizes from the car model (+0x164..+0x168). */
static void car_box(int32_t *o, const uint8_t *c, const uint8_t *other) {
  o[0] = rd16s(c + 4); o[1] = rd16s(c + 10); o[2] = rd16s(c + 0x10);
  o[8] = rd16s(c + 6); o[9] = rd16s(c + 0xc); o[10] = rd16s(c + 0x12);
  o[4] = rd16s(c + 8); o[5] = rd16s(c + 0xe); o[6] = rd16s(c + 0x14);
  o[0xc] = rd32(c + 0x18); o[0xd] = rd32(c + 0x1c); o[0xe] = rd32(c + 0x20);
  const uint8_t *m = carmodel(c[2]);
  int32_t w = rd16s(m + 0x164), l = rd16s(m + 0x168);
  if (c[0x13e] == 1 && other[0] != 0 && other[0x13e] != 1) { o[0x10] = (w * 7) / 8; o[0x11] = (l * 9) / 10; }
  else { o[0x10] = w; o[0x11] = l; }
  o[0x12] = rd16s(m + 0x166);
}
/* ---- 00499bb2: столкновение машин a и b (коробки): глубина, точка, нормаль, ось ---- */
/* P102_CarsHit — Game.exe 00499bb2, cdecl.  Box collision test of cars a and b: penetration depth, contact point, normal and axis. */
int32_t P102_CarsHit(const uint8_t *a, const uint8_t *b, int32_t *depth, int32_t *p, int32_t *n, int32_t *q) {
  int32_t ba[0x20], bb[0x20], best[10];
  memset(ba, 0, sizeof ba); memset(bb, 0, sizeof bb); memset(best, 0, sizeof best);
  car_box(ba, a, b);
  car_box(bb, b, a);
  int32_t r = P101_BoxHit(ba, bb, best);
  if (r != 0) {
    *depth = best[0];
    p[0] = best[1]; p[1] = best[2]; p[2] = best[3];
    n[0] = best[5]; n[1] = best[6]; n[2] = best[7];
    if (best[9] == 0) { q[2] = 0; q[1] = 0; q[0] = 0; }
    else { q[0] = ba[0x1b]; q[1] = ba[0x1c]; q[2] = ba[0x1d]; }
  }
  return r;
}

/* ---- 00492b98: новая машина трафика в (x, z) с курсом heading (parked ≠ 0 — стоящая); номер или -1 ---- */
/* P102_TrafficAdd — Game.exe 00492b98, cdecl.  Create a traffic car at (x, z) with heading `heading` (parked != 0: standing still).  Returns
   its index or -1. */
int32_t P102_TrafficAdd(int32_t x, int32_t y, int32_t z, int32_t heading, int32_t parked) {
  (void)y;
  int32_t i = PopIndex00493E9B();
  if (i == -1) return -1;
#ifndef RE_HOOK_BUILD
  if (i < 0 || i >= 0x40) return -1;
#endif
  uint8_t *r = trec(i), *c = tcar(i);
  P14_Fn0048DB65(c, 0x148);
  c[0] = (uint8_t)(i + 1);
  r[7] = 0; r[8] = 0; r[2] = 0;
  wr32(r + 0x28, -1);
  if (parked == 0) P63_NearestAdd(x, z);
  if ((Rand_004D9078() & 1) != 0 && parked == 0) r[7] = 1;
  r[0xa] = 0; r[0xb] = 0xff;
  wr32(c + 0x100, heading);
  wr32(r + 0x44, 0x7fffffff); wr32(r + 0x40, 0x7fffffff); wr32(r + 0x38, 0);
  if (parked == 0) {
    r[0xc] = (uint8_t)((int32_t)Rand_004D9078() % 9 + 3);
    r[0xd] = (uint8_t)((int32_t)Rand_004D9078() % 10 + 4);
    wr32(r + 0x3c, 0x82);
    r[1] = 1;
  } else {
    r[0xc] = 1; r[0xd] = 0x19;
    wr16(r + 0x16, 0);
    wr32(r + 0x3c, 0);
    r[1] = 9;
  }
  r[5] = 0;
  c[2] = r[0xc];
  wr32(c + 0xc8, x);
  wr32(c + 0xd0, z);
  P101_CarGround((p99_car_t *)c, r);
  P99_CarModelClean(i);
  P59_ObjDir(c, 1);
  const uint8_t *o = tcar(r[0]);
  wr32(r + 0x48, rd32(o + 0xc8) + 0x2ee);
  wr32(r + 0x4c, rd32(o + 0xd0) - 0x2ee);
  P11_00ba52d0 = fround((float)rd32(r + 0x48) * P63_Scale);
  wr32(r + 0x48, P11_00ba52d0);
  P11_00ba52d0 = fround((float)rd32(r + 0x4c) * P63_Scale);
  wr32(r + 0x4c, P11_00ba52d0);
  return i;
}

/* ---- 00501c63: полосы HUD миссии (повреждения, розыск, соперник), значки карты MAP_X / DOT ---- */
/* var_addr — Game.exe address of a mission script variable used by the HUD bars. */
static uint32_t var_addr(const char *name) {
  int32_t i = P42_FindVar(name);
  return i < 0 ? 0u : re_addr(&P42_Vars[i]);
}
/* P102_HudInit — Game.exe 00501c63, cdecl.  Mission HUD bars (damage, wanted level, opponent) from the mission script variables and the map
   icons MAP_X / DOT. */
void P102_HudInit(void) {
  P102_B52A3C = 0;
  P102_HudF4 = 0;
  P100_RadarX = -1; P100_RadarZ = -1;
  if (P62_BusyC == 0) ClearField2C_00502680((uint8_t *)P102_HudDmg);
  ClearField2C_00502680((uint8_t *)P102_HudFel);
  ClearField2C_00502680((uint8_t *)P101_Hud);
  if (P62_BusyC == 0) P16_FillHudRect(P102_HudDmg, fbits((float)P102_DmgMax), 0xff0000, re_addr("?"), 0, 0);   /* .data 0057412c */
  P102_DmgVar = var_addr("DAMAGEBAR");
  P102_FelVar = var_addr("FELONYBAR");
  P102_OppVar = var_addr("OPPONENTBAR");
  switch (MenuMode1271060) {
  case 1: case 2: case 3: case 6: case 7: case 0xb: break;
  default: P16_FillHudRect(P102_HudFel, 0x457ff000u, 0xff, re_addr("?"), 0, 1); break;              /* 4095.0, .data 00574154 */
  }
  if (P95_B87F08 == 0) {
    if (P95_C818B8 != 0) P16_FillHudRect(P101_Hud, 0x42a00000u, 0xff00, re_addr("?"), 1, 0);       /* 80.0, .data 0057415c */
  } else P16_FillHudRect(P101_Hud, fbits((float)P95_BDFA5C), 0xff00, re_addr("?"), 1, 0);          /* .data 00574158 */
  P100_RadarIcon = P93_FindIcon("MAP_X");
  P56_Sprite = P93_FindIcon("DOT");
  uint8_t slot = (uint8_t)P12_00c55034;
  P102_MapIcon2 = P100_RadarIcon;
  P58_S32980 = 0; P12_00b32980 = 0.0f;   /* 00b32980: оба псевдонима */
  P12_00b3297c = 0.0f;
  if (D_00b87e30 < 4) {
    if (P100_RadarIcon != NULL) {
      P12_01145a60[(uint32_t)P100_RadarIcon[8] * 0x10] |= 2;
      P40_UploadSlotPair(P100_RadarIcon[8], 0, 0);
    }
  } else {
    P12_01145a60[(uint32_t)slot * 0x10] |= 2;
    P40_UploadSlotPair(slot, 0, 0);
  }
}

/* поле обзора копов 00d11a40: 3 × int16 (в native — P95_SndRate (2 слова) и P97_D11A44) */
/* cop_view_fill — Cop field-of-view parameters 00d11a40 (3 x int16).  Native: assembled from the variables that
   alias those bytes (P95_SndRate, P97_D11A44). */
static void cop_view_fill(int16_t *v) {
#ifdef RE_HOOK_BUILD
  (void)v;
  FillRange004D2B16((uint16_t *)&P95_SndRate);
#else
  uint16_t t[3]; FillRange004D2B16(t); memcpy(&P95_SndRate, t, 4); P97_D11A44 = t[2];
  memcpy(v, t, 6);
#endif
}
/* ---- 004a6403: копы видят игрока? уровень погони P95_AmbN (2 — видят, 1 — первый кадр, 0/-1 — потеряли) ---- */
#ifndef RE_HOOK_BUILD
/* v2.11: RE_COPNEAR=K[:кадр] — отладка погони: один раз (по умолчанию на кадре 1000) первая патрульная машина ставится
   перед машиной игрока (машина + K/1000 · (машина − камера) по XZ, как RE_PEDNEAR) — дальше её ведёт обычный ИИ копов. */
/* cop_near_dbg — Native debug RE_COPNEAR=K[:frame]: once (frame 1000 by default) put the first patrol car in front
   of the player (car + K/1000 * (car - camera) on XZ); the normal cop AI drives it from there. */
static void cop_near_dbg(void) {
  static int on = -1, done = 0, at = 1000; static float kk;
  if (on < 0) { const char *e = getenv("RE_COPNEAR"); on = e != NULL;
    if (on) { kk = (float)atof(e) / 1000.0f; const char *p = strchr(e, ':'); if (p) at = atoi(p + 1); } }
  if (!on || done || (int32_t)P62_Frame < at) return;
  for (int32_t k = 0; k < 8; k++) {
    uint32_t *c = &P12_0112da00[k * 0x336];
    if (c[0x32d] == 0) continue;
    uint8_t *car = (uint8_t *)re_ptr(c[0x334]);
    if (car == NULL) { fprintf(stderr, "[cop] RE_COPNEAR: коп %d — re_ptr(%08x) = NULL\n", (int)k, (unsigned)c[0x334]); continue; }
    float cx = (float)P99_Cars[0].pos[0], cz = (float)P99_Cars[0].pos[2];
    int32_t x = (int32_t)(cx + kk * (cx - P44_CamX)), z = (int32_t)(cz + kk * (cz - P44_CamZ));
    wr32(car + 0xc8, x); wr32(car + 0xd0, z);
    P101_CarGround((p99_car_t *)car, trec(car[0] - 1));
    P59_ObjDir(car, 1);
    c[0x319] = (uint32_t)x; c[0x31b] = (uint32_t)z;
    fprintf(stderr, "[cop] RE_COPNEAR: коп %d → %d %d (кадр %d)\n", (int)k, (int)x, (int)z, (int)P62_Frame);
    done = 1; break;
  }
}
#endif
/* P102_CopsTick — Game.exe 004a6403, cdecl.  Do the cops see the player?  Unless option 00bdfa58 is set: for each active cop-AI slot, the
   player is seen when the slot is forced (+0x333) or the cop is in the player's cell box and
   P99_CopsNear (view cone) says so.  Seen resets the lost-timer 0112b280; after 0x200 unseen
   ticks the chase is lost (P95_AmbN = -1, event 0x800a).  Cops outside the box for more than 100
   ticks drop from TRF_COP back to TRF_DRIVE. */
void P102_CopsTick(void) {
#ifndef RE_HOOK_BUILD
  cop_near_dbg();
#endif
  if (MenuOptBDFA58 != 0) { P95_AmbN = 2; P95_SndReady = 1; return; }
  int32_t seen = 0, cx = 0, cy = 0;
  float pos[3] = { (float)P99_Cars[0].pos[0], 0.0f, (float)P99_Cars[0].pos[2] };
  P76_CellFromPos(pos, P97_B2C0, &cx, &cy);
#ifdef RE_HOOK_BUILD
  const int16_t *view = (const int16_t *)&P95_SndRate;
  cop_view_fill(NULL);
#else
  int16_t vbuf[3]; cop_view_fill(vbuf);
  const int16_t *view = vbuf;
#endif
  P95_AmbN = P95_AmbN < 1 ? 1 : 2;
  P95_SndReady = 0;
  for (int32_t k = 0; k < 8; k++) {
    uint32_t *c = &P12_0112da00[k * 0x336];
    if (c[0x32d] != 0 && c[0x331] == 0) {
      const uint8_t *car = (const uint8_t *)re_ptr(c[0x334]);
#ifndef RE_HOOK_BUILD
      if (car == NULL) continue;
#endif
      trec(car[0] - 1)[2] = 0;
      pos[0] = (float)(int32_t)c[0x319]; pos[2] = (float)(int32_t)c[0x31b];
      if (c[0x333] != 0 || (P76_InBox(pos, P97_B2C0, cx, cy) != 0 && P99_CopsNear(view, (uint8_t *)c) != 0)) {
        seen = 1; P95_SndReady = 1; break;
      }
    }
  }
  if (seen == 1) G0112B280 = 0;
  else if (G0112B280 < 0x200) G0112B280++;
  else if (G0112B280 == 0x200) {
    P95_AmbN = -1; G0112B280 = 0x201;
    if (0x2a9 < G2_00D11A5C) Call004D2D85(0x800a);
  } else P95_AmbN = 0;
  if (P95_AmbN < 1) {
    for (int32_t k = 7; k >= 0; k--) {
      uint32_t *c = &P12_0112da00[(7 - k) * 0x336];
      if (c[0x32d] == 0) continue;
      const uint8_t *car = (const uint8_t *)re_ptr(c[0x334]);
#ifndef RE_HOOK_BUILD
      if (car == NULL) continue;
#endif
      pos[0] = (float)rd32(car + 0xc8); pos[2] = (float)rd32(car + 0xd0);
      if ((int32_t)c[7] < 5 && c[0x331] == 0 && P76_InBox(pos, P97_B2C0, cx, cy) == 0) {
        c[0x11]++;
        if (100 < (int32_t)c[0x11]) {
          uint8_t *r = trec(car[0] - 1);
          c[0x11] = 0;
          if (r[1] == 4) r[1] = 2;
        }
      }
    }
  }
}

/* ---- 004c2d73: свободная камера режиссёра — сдвиг клавишами (1/2 — вбок, 4/8 — вперёд/назад, 0x20/0x40 — вверх/вниз, 0x80 — быстро) ---- */
/* P102_DirFreeCam — Game.exe 004c2d73, cdecl.  Director free camera: move with keys (1/2 sideways, 4/8 forward/back, 0x20/0x40 up/down, 0x80 fast). */
void P102_DirFreeCam(uint32_t keys) {
  uint8_t *cam = (uint8_t *)&DirectorCam;
  if ((keys & 0x10) == 0) P29_Flag94 = 0;
  else if (P29_Flag94 == 0) { SetDirectorMode(0xc, DirectorUnk7C, 0); return; }
  if (DirectorCam.unk00 == 0) {
    P100_FreeCamKeys(keys);
    ClampCameraHeight((int32_t *)cam);
    P61_RestoreCamState(cam);
    return;
  }
  float y = (float)rd32(cam + 0x50), x = (float)rd32(cam + 0x4c), z = (float)rd32(cam + 0x54);
  float s = (keys & 0x80) == 0 ? 20.0f : 80.0f;
  if ((keys & 4) != 0) { x = s * P44_ViewMatT[2] + x; z = s * P44_ViewMatT[8] + z; }
  if ((keys & 8) != 0) { x = x - s * P44_ViewMatT[2]; z = z - s * P44_ViewMatT[8]; }
  if ((keys & 1) != 0) { x = x - s * P44_ViewMatT[0]; z = z - s * P44_ViewMatT[6]; }
  if ((keys & 2) != 0) { x = s * P44_ViewMatT[0] + x; z = s * P44_ViewMatT[6] + z; }
  if ((keys & 0x20) != 0) y = y - s;
  if ((keys & 0x40) != 0) y = y + s;
  P11_00ba52d0 = fround(x); wr32(cam + 0x4c, P11_00ba52d0);
  P11_00ba52d0 = fround(y); wr32(cam + 0x50, P11_00ba52d0);
  P11_00ba52d0 = fround(z); wr32(cam + 0x54, P11_00ba52d0);
  P11_00ba52d0 = fround(x); wr32(cam + 0x5c, P11_00ba52d0);
  P11_00ba52d0 = fround(y); wr32(cam + 0x60, P11_00ba52d0);
  P11_00ba52d0 = fround(z); wr32(cam + 0x64, P11_00ba52d0);
  if (P98_CamClamp((int32_t *)cam) == 0) P61_StoreCamState(cam);
  else {
    CurCamera = &DirectorCam;   /* в оригинале — ещё копия записи самой в себя (0x23 слова) */
    ClampCameraHeight((int32_t *)cam);
  }
}

/* ---- 004a7aa7: точка пути копа (список +0xc60: узел +0 следующий, +8/+0xc точка, +0x1c номер) на расстоянии dist ---- */
/* oct_len — Octagonal length approximation (max + min/2) of (dx, dz). */
static int32_t oct_len(int32_t dx, int32_t dz) {
  int32_t ax = iabs(dx), az = iabs(dz), hi = ax, lo = az;
  if (ax < az) { hi = az; lo = ax; }
  return hi + (lo * 0xd >> 5);
}
/* P102_CopPathPoint — Game.exe 004a7aa7, cdecl.  Point at distance `dist` along a cop's path list (+0xc60: node +0 = next, +8/+0xc = point, +0x1c = number). */
void P102_CopPathPoint(uint8_t *cop, int32_t dist, int32_t *out) {
  uint8_t *n = (uint8_t *)re_rd_ptr(cop + 0xc60);
  if (n == NULL) { wr32(cop + 0xcb8, 0); return; }
  uint8_t *nx;
  while ((nx = (uint8_t *)re_rd_ptr(n)) != NULL) {
    int32_t z0 = rd32(n + 0xc), dx = rd32(nx + 8) - rd32(n + 8), dz = rd32(nx + 0xc) - z0;
    int32_t len = oct_len(dx, dz);
    if (dist < len) {
      if (dist < 0) dist = 0;
      out[0] = rd32(n + 8) + (dx * dist) / len;
      out[2] = z0 + (dz * dist) / len;
      uint8_t *nn = (uint8_t *)re_rd_ptr(nx);
      int32_t same = rd16s(n + 0x1c) == rd16s(nx + 0x1c) && rd32(nx) != 0 && nn != NULL && rd16s(nx + 0x1c) == rd16s(nn + 0x1c);
      P97_129584 = same ? 1 : 0;
      return;
    }
    dist -= len;
    n = nx;
  }
  int32_t z0 = rd32(n + 0xc), dx = P97_B2A0 - rd32(n + 8), dz = P97_B2A8 - z0;
  int32_t len = oct_len(dx, dz);
  if (dist < 0) dist = 0;
#ifndef RE_HOOK_BUILD
  if (len == 0) { out[0] = rd32(n + 8); out[2] = z0; P97_129584 = 0; return; }   /* оригинал делил бы на 0 */
#endif
  out[0] = rd32(n + 8) + (dx * dist) / len;
  out[2] = z0 + (dz * dist) / len;
  P97_129584 = 0;
}

/* ---- 00406875: снимок настроек для CONFIG.DAT (0x10c байт, 0x43 слова) ---- */
/* P102_ConfigSnap — Game.exe 00406875, cdecl.  Snapshot of the settings for CONFIG.DAT (0x10c bytes, 0x43 words). */
void P102_ConfigSnap(uint32_t *cfg) {
  memset(cfg, 0, 0x10c);
  cfg[0] = (uint32_t)P55_V57B6FC;
  cfg[1] = (uint32_t)P95_ModeSel;
  cfg[2] = (uint32_t)P35_ReqBpp;
  cfg[3] = (uint32_t)P35_InputMode;
  memcpy(&cfg[4], &P54_KeySrc[6], 5 * 4);   /* 0054b7c0 */
  cfg[9] = P54_Keys3[0]; cfg[10] = P54_Keys3[1]; cfg[11] = P54_Keys3[2];
  cfg[0xc] = (uint32_t)GetB31E18();
  cfg[0xd] = (uint32_t)G6_00D11880;
  cfg[0xe] = (uint32_t)MenuVar55384C;
  cfg[0xf] = (uint32_t)P13_00553850;
  cfg[0x10] = (uint32_t)P13_00b31f04;
  cfg[0x11] = (uint32_t)P13_00575ebc;
  cfg[0x12] = (uint32_t)P13_00575ec0;
  cfg[0x13] = (uint32_t)P13_0055c974;
  cfg[0x14] = (uint32_t)P13_00575f30;
  cfg[0x15] = (uint32_t)P13_00b201dc;
  cfg[0x16] = (uint32_t)P13_00575ee8;
  cfg[0x17] = (uint32_t)P13_00d118c8;
  cfg[0x18] = (uint32_t)G00575F40;
  cfg[0x19] = (uint32_t)Q00B87E90;
  cfg[0x1a] = (uint32_t)Q00B87E94;
  cfg[0x1b] = fbits(WF00575F14);
  cfg[0x1c] = fbits(WF00575F18);
  cfg[0x1d] = (uint32_t)MenuState575EF0;
  cfg[0x1e] = fbits(P11_01270c24);
  cfg[0x1f] = fbits(P11_0125f3f8);
  cfg[0x20] = fbits(P19_Scale);
  cfg[0x21] = (uint32_t)P60_PartLimit;
  cfg[0x22] = (uint32_t)Q00B87EF0;
  cfg[0x23] = (uint32_t)P13_00575ef4;
  cfg[0x2e] = (uint32_t)P13_00b87e74;
  cfg[0x24] = (uint32_t)P13_00575f3c;
  cfg[0x25] = (uint32_t)G6_00575F20;
  cfg[0x26] = (uint32_t)P13_00575f44;
  cfg[0x27] = (uint32_t)G00575F48;
  cfg[0x28] = (uint32_t)G00575F24;
  cfg[0x29] = (uint32_t)WI00B87E2C;
  cfg[0x2a] = (uint32_t)P21_FrameFlagB;
  cfg[0x2b] = (uint32_t)P21_FrameFlagA;
  cfg[0x2c] = (uint32_t)P21_FrameMin;
  cfg[0x2d] = (uint32_t)G00575EF8;
  cfg[0x2f] = (uint32_t)G6_00575F00;
  cfg[0x30] = (uint32_t)G6_00575F04;
  cfg[0x31] = (uint32_t)G6_00B87E50;
  memcpy(&cfg[0x32], P102_BDF9E0, 0xb * 4);
  cfg[0x3d] = (uint32_t)P51_TrafficN;
  cfg[0x3e] = (uint32_t)P12_00b87e58;
  cfg[0x3f] = (uint32_t)P12_00b87e5c;
  cfg[0x40] = (uint32_t)P12_00575f50;
  cfg[0x41] = (uint32_t)P102_57B6A8;
  cfg[0x42] = (uint32_t)P102_57B6F8;
}

/* ---- 004dd7ec: сброс таблицы машин перед заездом (номера, модели, положение игрока на дороге) ---- */
/* P102_ResetCars — Game.exe 004dd7ec, cdecl.  Reset the car table before a level: indices, models and the player's road position. */
void P102_ResetCars(void) {
  int32_t q[4] = { 0, 0, 0, 0 };
  P14_00d0778c = 0;
  memset(P102_B2EA38, 0, sizeof P102_B2EA38);
  P35_PadX = 0;
  G00BDF984 = 0;
  P102_D06A00 = 0; P102_D0DD84 = 0; P102_D0DDEC = 0; P102_D0DD7C = 0;
  for (int32_t k = 0; k < 4; k++) { P102_D0DDD0[k] = -1; P102_D077A0[k] = -1; }
  P102_D0DD74 = 0; P102_D0DDE8 = 0; P102_D0DDF0 = 0; P102_D0DD78 = 0; P102_D0DD80 = 0;
  P102_D04D14 = 0;
  P102_5624A4 = 1;
  P56_B2EA48 = 0;
  G6_005624A0 = 0xf;
  P14_Fn0048DB65(P102_BlkA, 0xd68);
  P14_Fn0048DB65(P102_BlkB, 0xd68);
  P14_Fn0048DB65(P102_BlkC, 0xd68);
  P94_InitCurves();
  P102_D0DDEC = 0; G6_00D0DDC0 = 0; P102_D0DD7C = 0;
  for (int32_t k = 0; k < 0x42; k++) {
    uint8_t *c = carp(k);
    c[0] = (uint8_t)k;
    if (P95_B87EB4 == 0) { if (k < 0x41) c[2] = 0; }
    else c[2] = (uint8_t)P95_BDF9D4;
    if (k != S_00D11878 && k < 0x41) P56_ObjInit(c, q);
  }
  P102_D06A00 = 0;
  P102_D0DD84 = 1;
  if (P102_D06A04 != 0) {
    G2_00D11A5C = P102_C816F8;
    P99_Cars[0].heading = P102_C816FC;
    P59_ObjDir(carp(0), 0);
  }
  if (G6_00B87EAC == 0 && G6_00B87EB0 == 0) {
    const uint8_t *m = carmodel(P99_Cars[0].f00[2]);
    int32_t h = P100_RoadHeight(P99_Cars[0].pos);
    P99_Cars[0].pos[1] = h - rd16s(m + 0xe2);
    P59_ObjDir(carp(0), 1);
    for (int32_t k = 3; k >= 0; k--) P99_Cars[0].f78[k][0] = 0x10;
  }
  if (G6_00B87EAC != 0) G00575F24 = 1;
}

/* ---- 004902a8: клетки вокруг игрока по таблице направлений: дорожные — места трафика (P75_Spawn), пустые — точки пыли ---- */
/* P102_ScanCells — Game.exe 004902a8, cdecl.  Scan the map cells around the player via the direction table: road cells become traffic spawn
   points (P75_Spawn), empty cells dust points. */
void P102_ScanCells(void) {
  P75_43CC = 0;
  P102_DustN = 0;
  int32_t x, z;
  if (G6_00B87EB0 != 0 || G6_00B87EAC != 0) { x = P99_Cars[0x41].pos[0]; z = P99_Cars[0x41].pos[2]; }
  else { x = P99_Cars[0].pos[0]; z = P99_Cars[0].pos[2]; }
  P11_00ba52d0 = fround((float)(x + P62_MapC64) * P63_Scale);
  int32_t px = P11_00ba52d0;
  P11_00ba52d0 = fround((float)(P62_Map2C40 - z) * P63_Scale);
  int32_t pz = P11_00ba52d0;
  int32_t n = P62_MapN;
#ifndef RE_HOOK_BUILD
  if (n <= 0) return;
#endif
  uint8_t *sp = P75_Spawn, *dp = P102_DustPts;
  for (int32_t k = 0; k < P94_DirCnt; k++) {
#ifndef RE_HOOK_BUILD
    if (k >= 128) break;
#endif
    int32_t cx = px + P94_DirTab[k][0], cz = pz + P94_DirTab[k][1];
    if (cx < 0 || P62_MapW <= cx || cz < 0 || P62_MapH <= cz) continue;
    uint32_t ux = (uint32_t)(cx / n), uz = (uint32_t)((P72_Rows - 1) - cz / n);
    int32_t fx = cx - (int32_t)ux * n, fz = cz - (cz / n) * n;
    uint32_t t = (ux & 1) + (uz & 1) * 2;
    const int16_t *ta = (const int16_t *)P54_RoadA[t];
    const uint32_t *tb = (const uint32_t *)P54_RoadB[t];
#ifndef RE_HOOK_BUILD
    if (ta == NULL) continue;
#endif
    int16_t s = ta[fz * n + fx];
    if (s == -0x8000) {
#ifndef RE_HOOK_BUILD
      if (dp + 0xc > P102_DustPts + sizeof P102_DustPts) continue;
#endif
      wr32(dp + 4, cx * 0x5dc - P62_MapC64);
      wr32(dp + 8, -(cz * 0x5dc - P62_Map2C40));
      P102_DustN++;
      dp += 0xc;
      continue;
    }
#ifndef RE_HOOK_BUILD
    if (tb == NULL || sp + 0xc > P75_Spawn + sizeof P75_Spawn) continue;
#endif
    uint32_t w = tb[fz * n + fx];
    sp[2] = (uint8_t)((int32_t)w >> 0x1e);
    if ((w & 2) == 0) {
      if (s < 0 || P11_00b5a8e8 < s) continue;
#ifndef RE_HOOK_BUILD
      if ((uint32_t)(s + 1) * 0x42 > sizeof P11_00bf1c40) continue;
#endif
      if (rd16s(&P11_00bf1c40[8 + s * 0x42]) < 4) continue;
      wr16(sp, (uint16_t)s);
    } else wr16(sp, 0xffff);
    wr32(sp + 4, cx * 0x5dc - P62_MapC64);
    wr32(sp + 8, -(cz * 0x5dc - P62_Map2C40));
    P75_43CC++;
    sp += 0xc;
  }
}

/* ---- 00493b51: подвод машины трафика к цели по x (+0x40, mode 0/2) или z (+0x44, mode 1/3); 1 — на месте ---- */
/* align_axis — Move a traffic car toward its target along x (velocity +0x40, mode 0/2) or z (+0x44, mode 1/3);
   returns 1 when in place. */
static int32_t align_axis(uint8_t *r, uint8_t *c, uint32_t toff, uint32_t coff, int32_t neg_dir) {
  int32_t d = rd32(r + toff) - rd32(c + coff);
  if (iabs(d) < 0x21) {
    wr32(c + coff, rd32(r + toff));
    wr32(r + toff, 0x7fffffff);
    r[0x13] &= 0xde;
    wr32(c + 0xfc, 0);
    wr16(c + 0xea, 0);
    if ((r[0x13] & 0x10) != 0) { r[0x13] &= 0xef; r[0x13] |= 8; }
    return 1;
  }
  int32_t v = (r[0x13] & 0x30) == 0 ? d / 32 : d / 8;
  wr32(c + 0xfc, rd32(r + 0x24) == neg_dir ? -v : v);
  return 0;
}
/* P102_TrafficAlign — Game.exe 00493b51, cdecl.  Align a traffic car with its lane (called by P103_TrafficTick when nearly on the road direction). */
int32_t P102_TrafficAlign(uint8_t *rec, int32_t a, int32_t b, int8_t mode) {
  (void)a; (void)b;
  uint8_t *c = tcar(rec[0]);
  int32_t ok = 1;
  if (rd32(rec + 0x40) != 0x7fffffff && rd32(rec + 0x38) != 0 && (mode == 0 || mode == 2))
    if (align_axis(rec, c, 0x40, 0x18, 2) == 0) ok = 0;
  if (rd32(rec + 0x44) != 0x7fffffff && rd32(rec + 0x38) != 0 && (mode == 1 || mode == 3))
    if (align_axis(rec, c, 0x44, 0x20, 1) == 0) ok = 0;
  if (ok != 0) { wr32(rec + 0x40, 0x7fffffff); wr32(rec + 0x44, 0x7fffffff); }
  return ok;
}

/* ---- 004aba7c: параметры шести обломков для города 2 (0x120 байт P98_Six) ---- */
static const uint32_t k_six[72] = {
  300, 10, 0x15e, 800, 0x223, 600, 0x41700000, 0x41c80000, 0x640, 0x41700000, 0x3ee66666, 0x6c,
  100, 0xf, 300, 0x28a, 0x520, 400, 0x41200000, 0x41400000, 0, 0x3f800000, 0x3ee66666, 0x5a,
  4000, 0xc, 100, 700, 0xa57, 400, 0x40e00000, 0x41000000, 300, 0, 0x3f000000, 0x78,
  0xf6a, 0x14, 0xed8, 900, 0, 0x1c2, 0x41500000, 0x42200000, 0x6a4, 0x41f00000, 0x3e99999a, 0x5a,
  0xf50, 5, 0xd16, 600, 0xa07, 0xfa, 0x41500000, 0x41700000, 0x400, 0x40800000, 0x3f0ccccd, 0x5a,
  0xed8, 5, 0xe10, 600, 0x400, 300, 0x41200000, 0x41a00000, 2000, 0x41400000, 0x3ee66666, 0x69 };
_Static_assert(sizeof k_six == sizeof(p98_six_t), "k_six");
/* P102_SixInit — Game.exe 004aba7c, cdecl.  In game state 2 load the six-entry parameter table k_six into P98_Six and clear P102_SixFlag.
   TODO(RE): unsure what the six entries configure (cop / AI tuning?). */
void P102_SixInit(void) {
  if (D_00b87e30 != 2) return;
  P102_SixFlag = 0;
  memcpy(P98_Six, k_six, sizeof k_six);
}

/* ---- 005259c8: реплики копов по скорости/заносу/ударам игрока (P12_Fn00525CB7(номер)) ---- */
/* P102_CopTalk — Game.exe 005259c8, cdecl.  Police radio / commentary triggers (speech 00525cb7(n)) from the player's driving: high speed,
   spinning (yaw rate CAR_ANGVEL y above 0x12d / 0xfb, the latter with the handbrake), damage
   jumps of more than 0x1e (and an external hit flag 00b31ea0), sustained speed, braking at speed,
   handbrake (pad bit 0x20) or burnout (0x40) above speed 0x32; each with its own cool-down
   counter.  Also records the maximum speed and yaw rate.  keys = PAD_* bits (ported36.c).
   The state variables (00b93ccc..00b93e00) are the ones P44_ResetState clears. */
void P102_CopTalk(uint32_t keys) {
  int32_t sp = P99_Cars[0].f10c >> 0xc;
  P44_Rst_B93DF4 = sp < 0 ? 1 : 0;
  if (sp < 0) sp = -sp;
  if (P44_Rst_B93CE8 < sp) P44_Rst_B93CE8 = sp;
  int32_t sl = rd32(carp(0) + CAR_ANGVEL + 4) >> 0xc;   /* yaw rate */
  if (sl < 0) sl = -sl;
  if (P44_Rst_B93CD8 < sl) P44_Rst_B93CD8 = sl;
  int32_t dmg = Get138(carp(0)) >> 3;
  if (sl < 0x12d) P44_Rst_B93E00 = 0;
  else if (P44_Rst_B93E00 == 0) { P44_Rst_B93E00 = 1; P44_Rst_B93CDC = 0x46; }
  else if (P44_Rst_B93CDC == 0) P12_Fn00525CB7(4);
  else P44_Rst_B93CDC--;
  if (sl < 0xfb) P44_Rst_B93DFC = 0;
  else if (P44_Rst_B93DFC == 0) { if ((keys & 0x20) != 0) { P44_Rst_B93DFC = 1; P44_Rst_B93CD4 = 0x28; } }
  else if (P44_Rst_B93CD4 == 0) P12_Fn00525CB7(2);
  else P44_Rst_B93CD4--;
  if (P44_Rst_B31EA0 != 0) { P44_Rst_B31EA0 = 0; P44_Rst_B93CD0 = dmg; P12_Fn00525CB7(5); }
  int32_t hit = 0x1e < dmg - P44_Rst_B93CD0;
  if (hit) { P44_Rst_B93CD0 = dmg; P12_Fn00525CB7(7); }
  if (sl < 0xc9 || P44_Rst_B93CF0 == 0) { P44_Rst_B93CF0 = 0; P44_Rst_B93CCC = 0x28; }
  else if (P44_Rst_B93CCC == 0) P12_Fn00525CB7(3);
  else P44_Rst_B93CCC--;
  if (P99_Cars[0].f10c < 0xaa001) { if ((keys & 1) == 0 || hit) P44_Rst_B93DF8 = 0; }
  else { P44_Rst_B93DF8 = 1; P44_Rst_B93CEC = 0x28; }
  if (P44_Rst_B93DF8 != 0) { if (P44_Rst_B93CEC == 0) P12_Fn00525CB7(0); else P44_Rst_B93CEC--; }
  if (0x10e < P99_Cars[0].speed) P44_Rst_B93CE4++;
  if (hit || P99_Cars[0].speed < 0x10e) P44_Rst_B93CE4 = 0;
  if (5 < P44_Rst_B93CE4) { P12_Fn00525CB7(8); P44_Rst_B93CE4 = 0; }
  if ((keys & 0x40) != 0 && 0x32 < sp) P12_Fn00525CB7(6);
  if ((keys & 0x20) != 0 && 0x32 < sp) P12_Fn00525CB7(1);
}

/* ---- 004fe869: цвет моделей фонарей LAMP/LAMP2/LAMP3/DLAMP/DLAMP2 и их потомков (on=1 — горят) ---- */
/* lamp_ops — Apply the lamp colour to one lamp model and its children. */
static void lamp_ops(uint32_t ref, int32_t second, float r, float g, float b) {
#ifndef RE_HOOK_BUILD
  if (ref == 0) return;
#endif
  const uint8_t *mdl = (const uint8_t *)P79_PTR(ref);
  uint8_t *p = (uint8_t *)P79_PTR(rd32(mdl + 0x2c));
  uint32_t n = (uint16_t)rd16s(mdl + 0x16);
  for (; n != 0; n--) {
    if (*p == 0x10 || *p == (second ? 0 : 0x10)) {   /* в первом проходе оригинал дважды проверяет 0x10 */
      wrf(p + 0x14, r); wrf(p + 0x18, g); wrf(p + 0x1c, b); *p = 0;
    } else if (*p == 0x11 || *p == 1) {
      wrf(p + 0x18, r); wrf(p + 0x1c, g); wrf(p + 0x20, b); *p = 1;
    }
    p += G2_TABLE_00550ACC[*p];
  }
}
/* P102_LampColor — Game.exe 004fe869, cdecl.  Colour of the lamp models LAMP / LAMP2 / LAMP3 / DLAMP / DLAMP2 and their children (on = 1: lit). */
void P102_LampColor(int32_t on) {
  static const char *const names[5] = { "LAMP", "LAMP2", "LAMP3", "DLAMP", "DLAMP2" };   /* .data 0057380c.. */
  float r, g, b;
  if (on == 1) { r = 255.0f; g = 255.0f; b = 240.0f; } else { r = 48.0f; g = 48.0f; b = 45.0f; }
  for (int32_t k = 0; k < 5; k++) {
    int32_t idx = P20_FindNameNoCase(names[k]);
    if (idx == -1) continue;
#ifndef RE_HOOK_BUILD
    if (idx < 0 || idx >= 1126) continue;
#endif
    lamp_ops(P79_ModelTab[idx], 0, r, g, b);
    for (int32_t j = 0; j < P20_Count; j++) {
#ifndef RE_HOOK_BUILD
      if (j >= 1126) break;
      if (P79_ModelTab[j] == 0) continue;
#endif
      if (rd32((const uint8_t *)P79_PTR(P79_ModelTab[j]) + 4) == idx) lamp_ops(P79_ModelTab[j], 1, r, g, b);
    }
  }
}

/* P102_SpawnDust — Game.exe 0051329b, cdecl.  Spawns PEDESTRIANS (not dust; see ported71.c) at the spawn points
   P102_DustPts while fewer than the "Pedestrian Density" option (P60_PartLimit = 005759a4) are active: each new
   record of the pool A_00C56780 is first offered a chair (P99_PartOnChair — a sitting pedestrian), else becomes a
   walker (P60_SpawnParticle), else is freed again.  Names kept (address aliases / existing users). */
void P102_SpawnDust(void) {
  const uint8_t *pt = P102_DustPts;
  for (int32_t k = P102_DustN; k != 0 && G6_00C56764 < P60_PartLimit; k--, pt += 0xc) {
#ifndef RE_HOOK_BUILD
    if (pt + 0xc > P102_DustPts + sizeof P102_DustPts) break;
#endif
    int32_t cnt = P71_CountNear(rd32(pt + 4), rd32(pt + 8));
    int32_t i = PoolAlloc0051210C();
    if (i == -1) return;
#ifndef RE_HOOK_BUILD
    if (i < 0 || i >= 0x40) return;
#endif
    uint8_t *p = (uint8_t *)A_00C56780 + i * 0xb4;
    float *f = (float *)(p + 0x84);
    f[0] = (float)rd32(pt + 4);
    f[2] = (float)rd32(pt + 8);
    f[1] = (float)-P100_RoadHeightF(f);
    int32_t zz, xx;
    P11_00ba52d0 = fround(f[2]); zz = P11_00ba52d0; P11_00ba52d0 = fround(f[0]); xx = P11_00ba52d0;
    P102_NbrC = (int16_t)P72_RoadWord(xx, zz);
    P101_Nbr[0] = (int16_t)P72_RoadWord(xx, zz - 0x5dc);
    P101_Nbr[1] = (int16_t)P72_RoadWord(xx, zz + 0x5dc);
    P101_Nbr[2] = (int16_t)P72_RoadWord(xx + 0x5dc, zz);
    P101_Nbr[3] = (int16_t)P72_RoadWord(xx - 0x5dc, zz);
    int32_t ok = P99_PartOnChair(p, cnt);
    if (ok == 0 && (ok = P60_SpawnParticle(p, cnt)) == 0) P43_FreeSlot(p);
    if (ok != 0) wr32(p + 8, iabs((int32_t)Rand_004D9078() % 5));
  }
}

/* ---- 0051d51c: матрица машины игрока (P98_CarMat[0]) и 4 угла днища на дороге (P102_Corners: x, высота, z) ---- */
/* P102_PlayerCorners — Game.exe 0051d51c, cdecl.  Player car matrix (P98_CarMat[0]) and the four underbody corners on the road (P102_Corners: x,
   height, z). */
void P102_PlayerCorners(void) {
  const float k = 1.0f / 4096.0f;   /* .rdata 00546134 */
  const int16_t *mt = P99_Cars[0].mat;
  float *M = P98_CarMat[0];
  M[3] = (float)mt[3] * k; M[4] = (float)mt[4] * k; M[5] = (float)mt[5] * k;
  M[0] = -((float)mt[0] * k); M[1] = -((float)mt[1] * k); M[2] = -((float)mt[2] * k);
  M[6] = -((float)mt[6] * k); M[7] = -((float)mt[7] * k); M[8] = -((float)mt[8] * k);
  P44_MatPtr = M;
  const uint8_t *m = carmodel(P99_Cars[0].f00[2]);
  for (uint32_t i = 0; i < 4; i++) {
    float v[4];
    float sx = (float)rd16s(m + 0xe0 + i * 8);
    v[0] = (i & 2) == 0 ? sx - 25.0f : sx + 25.0f;   /* .rdata 005461f0 */
    v[1] = 0.0f;
    v[2] = (float)-rd16s(m + 0xe4 + ((i + 1) & 3) * 8);
    v[3] = 0.0f;
    P44_XformT(v);
    v[0] = v[0] + (float)P99_Cars[0].pos[0];
    v[2] = v[2] + (float)P99_Cars[0].pos[2];
    P11_00ba52d0 = fround(v[0]); P102_Corners[i * 4] = P11_00ba52d0;
    P11_00ba52d0 = fround(v[2]); P102_Corners[i * 4 + 2] = P11_00ba52d0;
    P102_Corners[i * 4 + 1] = P100_RoadHeightF(v);
  }
  G00B5C910 = P102_Corners[0]; G00B5C914 = P102_Corners[1]; G00B5C918 = P102_Corners[2];   /* прежние псевдонимы угла 0 */
}

/* ---- 00509e64: нет ли стены (0x1e) в сетке радара 55×55 (P77_C5FE00) на отрезке от игрока до pos; 1 — свободно ---- */
/* grid_wall — 1 if radar grid cell (x, y) of the 55 x 55 grid P77_C5FE00 is a wall (0x1e). */
static int32_t grid_wall(int32_t idx) {
#ifndef RE_HOOK_BUILD
  if (idx < 0 || (uint32_t)(idx + 1) * 4 > sizeof P77_C5FE00) return 0;
#endif
  return rd32(&P77_C5FE00[idx * 4]) == 0x1e;
}
/* P102_RadarClear — Game.exe 00509e64, cdecl.  1 if no wall cell lies on the segment from the player to pos in the radar grid. */
int32_t P102_RadarClear(const int32_t *pos, int32_t dx, int32_t dz) {
  P11_00ba52d0 = fround((float)(P99_Cars[0].pos[0] + 0x2ee + P62_MapC64) * P63_Scale);
  int32_t x0 = P11_00ba52d0 + dx;
  P11_00ba52d0 = fround((float)(P62_Map2C40 - (P99_Cars[0].pos[2] - 0x2ee)) * P63_Scale);
  int32_t z0 = P11_00ba52d0 + dz;
  P11_00ba52d0 = fround((float)(pos[0] + 0x2ee + P62_MapC64) * P63_Scale);
  int32_t x1 = P11_00ba52d0;
  P11_00ba52d0 = fround((float)(P62_Map2C40 - (pos[2] - 0x2ee)) * P63_Scale);
  int32_t z1 = P11_00ba52d0;
  int32_t ddx = x1 - x0, ddz = z1 - z0, adx = iabs(ddx), adz = iabs(ddz);
  int32_t sx = ddx < 0 ? -1 : 1, sz = ddz < 0 ? -1 : 1;
  int32_t idx = dx + 0x1b + (dz + 0x1b) * 0x37;
  if (adz < adx) {
    int32_t e = adz;
    for (int32_t k = 0; k != ddx; k += sx) {
      if (adx < e) { e -= adx; idx += sz * 0x37; }
      if (grid_wall(idx)) return 0;
      idx += sx; e += adz;
    }
  } else if (adx < adz) {
    int32_t e = adx;
    for (int32_t k = 0; k != ddz; k += sz) {
      if (adz < e) { idx += sx; e -= adz; }
      if (grid_wall(idx)) return 0;
      idx += sz * 0x37; e += adx;
    }
  } else {
    for (int32_t k = 0; k != ddx; k += sx) {
      if (grid_wall(idx)) return 0;
      idx += sz * 0x37 + sx;
    }
  }
  return 1;
}

/* ---- 004d0439: пересекает ли прямоугольник (x, z, курс ang, полуширина half, длина len) какую-либо машину;
        оригинал возвращает начало таблицы машин (00d077c0), а не найденную запись ---- */
/* P102_BoxAnyCar — Game.exe 004d0439, cdecl.  Does the rectangle (x, z, heading ang, half width `half`, length `len`) overlap any car?  The
   original returns the start of the car table (00d077c0) rather than the car found — kept. */
uint8_t *P102_BoxAnyCar(int32_t x, int32_t z, int32_t ang, int32_t half, int32_t len) {
  int32_t x0 = 0, x1 = 0, z1 = 0, z0 = 0;   /* в оригинале при ang вне четырёх секторов — неинициализированные */
  if (ang < 0xfe1 && 0x1f < ang) {
    if (ang < 0x7e1 || 0x81f < ang) {
      if (ang < 0xbe1 || 0xc1f < ang) {
        if (0x3e0 < ang && ang < 0x420) { x0 = x - len; x1 = x; z1 = half + z; z0 = z - half; }
      } else { x0 = x; x1 = len + x; z1 = half + z; z0 = z - half; }
    } else { x0 = x - half; x1 = half + x; z1 = z; z0 = z - len; }
  } else { x0 = x - half; x1 = half + x; z1 = len + z; z0 = z; }
  for (int32_t k = 0; k <= 0x40; k++) {
    if (k != 0 && trec(k - 1)[1] == 0) continue;
    int32_t cx = P99_Cars[k].pos[0], cz = P99_Cars[k].pos[2];
    if (iabs(cx - x) >= len || iabs(cz - z) >= len) continue;
    uint32_t a = (uint32_t)-P99_Cars[k].heading & 0xfff;
    const int32_t *t = P96_RotTab[(int32_t)a >> 2];
    if ((x0 <= t[0] + cx || x0 <= t[2] + cx || x0 <= t[4] + cx || x0 <= t[6] + cx) &&
        (t[0] + cx <= x1 || t[2] + cx <= x1 || t[4] + cx <= x1 || t[6] + cx <= x1) &&
        (t[1] + cz <= z1 || t[3] + cz <= z1 || t[5] + cz <= z1 || t[7] + cz <= z1) &&
        (z0 <= t[1] + cz || z0 <= t[3] + cz || z0 <= t[5] + cz || z0 <= t[7] + cz))
      return carp(0);
  }
  return NULL;
}

/* ---- 004e6c92: след призрака — 40 пар точек за машиной 0x41 (P56_GhostBuf по 0x48), затухание цвета ---- */
/* ghost_pt — One point pair of the ghost trail. */
static void ghost_pt(uint8_t *e, float sx) {
  float v[4] = { sx, 0.0f, -200.0f, 0.0f };
  P44_XformT(v);
  v[0] = v[0] + (float)P99_Cars[0x41].pos[0];
  v[2] = v[2] + (float)P99_Cars[0x41].pos[2];
  float y = (float)-P100_RoadHeightF(v) - 10.0f;   /* .rdata 0054612c */
  wrf(e, v[0]); wrf(e + 4, y); wrf(e + 8, v[2]); wrf(e + 0xc, v[3]);
}
/* P102_GhostTrail — Game.exe 004e6c92, cdecl.  Ghost trail: 40 point pairs behind car 0x41 (P56_GhostBuf, 0x48 bytes each) with fading colour. */
void P102_GhostTrail(void) {
  if (G6_00B5A778 != 0 || (G6_00B87EA0 == 0 && P45_Mode != 0xc9) || (G6_00B87EA0 != 0 && P88_Mode575 != 1)) return;
  for (int32_t k = 0; k < 0x28; k++) {
    uint8_t *e = &P56_GhostBuf[k * 0x48];
    if (2 < e[0x44]) e[0x44] -= 3;
    if (3 < e[0x45]) e[0x45] -= 4;
    if (3 < e[0x46]) e[0x46] -= 4;
  }
  if ((P62_Frame & 3) != 0) return;
#ifndef RE_HOOK_BUILD
  if (P56_G4538 < 0 || P56_G4538 >= 0x28) P56_G4538 = 0;
#endif
  P44_MatPtr = P102_GhostMat;
  uint8_t *e = &P56_GhostBuf[P56_G4538 * 0x48];
  e[0x44] = 0; e[0x45] = 0; e[0x46] = 0; e[0x47] = 1;
  if (P56_G4538 == 0) {
    if (P56_G3908 != 0) { P56_GhostBuf[0xb3c] = 0xff; P56_GhostBuf[0xb3d] = 0xff; P56_GhostBuf[0xb3e] = 0xff; }
  } else { e[-0x48 + 0x44] = 0xff; e[-0x48 + 0x45] = 0xff; e[-0x48 + 0x46] = 0xff; }
  ghost_pt(e, 200.0f);
  ghost_pt(e + 0x10, -200.0f);
  P56_G4538++;
  if (0x27 < P56_G4538) { P56_G4538 = 0; P56_G3908 = 1; }
}

/* ---- 0049a21d: точка контакта двух коробок (запись 0x60 на коробку, P100_BoxFace) → out[0], out[2], нормаль out[4..6], глубина out[8] ---- */
#define BX(u, off) (box[((uint32_t)(u) * 0x60 + (off)) / 4])
/* P102_BoxContact — Game.exe 0049a21d, cdecl.  Contact of two collision boxes (0x60 bytes each, P100_BoxFace): picks the face with the
   smallest penetration; out[0]/out[2] = contact x/z, out[4..6] = normal (y = 0), out[8] = depth. */
void P102_BoxContact(const int32_t *box, int32_t *out) {
  int32_t best = box[0x15] + 1, bj = 0, sg = 0;
  uint32_t bu = 0;
  for (int32_t u = 1; u >= 0; u--) {
    for (int32_t j = 1; j >= 0; j--) {
      int32_t d1 = BX(u, 0x54 + j * 4) - BX(u, 0x4c + j * 4);
      int32_t d2 = BX(u, 0x4c + j * 4) + BX(u, 0x54 + j * 4);
      if (d1 < best) { sg = u != 1 ? -1 : 1; best = d1; bj = j; bu = (uint32_t)u; }
      if (d2 < best) { sg = u != 1 ? 1 : -1; best = d2; bj = j; bu = (uint32_t)u; }
    }
  }
  uint32_t o = bu ^ 1;
  int32_t nx = BX(bu, 0x10 + bj * 0x10), nz = BX(bu, 0x18 + bj * 0x10);
  int32_t s1 = (mul(BX(o, 0x10), nx) + 0x800 + mul(BX(o, 0x18), nz)) >> 0xc < 0 ? sg : -sg;
  int32_t s2 = (mul(BX(o, 0x20), nx) + 0x800 + mul(BX(o, 0x28), nz)) >> 0xc < 0 ? sg : -sg;
  out[0] = BX(o, 0) + ((mul(mul(BX(o, 0x10), BX(o, 0x44)), s1) + 0x800 + mul(mul(BX(o, 0x20), BX(o, 0x48)), s2)) >> 0xc);
  out[2] = BX(o, 8) + ((mul(mul(BX(o, 0x18), BX(o, 0x44)), s1) + 0x800 + mul(mul(BX(o, 0x28), BX(o, 0x48)), s2)) >> 0xc);
  out[8] = best;
  if (bu != 0) sg = -sg;
  out[4] = mul(nx, sg);
  out[5] = 0;
  out[6] = mul(nz, sg);
}
#undef BX

/* отсечение ребра a–b ближней (P95_Near, z точки = 50) или дальней (Q01270C24) плоскостью; n атрибутов → slot[];
   у второй вершины (b внутри, a снаружи) оригинал пишет только первые n2 атрибутов */
/* clip_attr2 — Clip edge a-b against the near (P95_Near, point z = 50) or far (01270c24) plane, interpolating n
   attributes into slot[]; for the second vertex the original writes only the first n2 attributes. */
static void clip_attr2(const uint8_t *a, const uint8_t *b, int32_t far, const float *ua, const float *ub, const uint8_t *slot, int32_t n, int32_t n2) {
  float P = far ? Q01270C24 : P95_Near, zc = far ? Q01270C24 : 50.0f;
  float za, zb; memcpy(&za, a + 0x14, 4); memcpy(&zb, b + 0x14, 4);
  float ax, ay, bx, by; memcpy(&ax, a + 0xc, 4); memcpy(&ay, a + 0x10, 4); memcpy(&bx, b + 0xc, 4); memcpy(&by, b + 0x10, 4);
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
      o[0] = ax - (ax - bx) * t; o[1] = ay - (ay - by) * t; o[2] = zc;
      P100_ClipN += 1; P100_ClipOut += 0xc;
    } else {
      float t = (zb - P) / (zb - za);
      for (int32_t i = 0; i < n; i++) o[slot[i]] = ub[i] - (ub[i] - ua[i]) * t;
      o[0] = bx - (bx - ax) * t; o[1] = by - (by - ay) * t; o[2] = zc;
      o += 0xc;
      for (int32_t i = 0; i < n2; i++) o[slot[i]] = ub[i];
      o[0] = bx; o[1] = by; o[2] = zb;
      P100_ClipN += 2; P100_ClipOut += 0x18;
    }
  } else {
    for (int32_t i = 0; i < n; i++) o[slot[i]] = ub[i];
    o[0] = bx; o[1] = by; o[2] = zb;
    P100_ClipN += 1; P100_ClipOut += 0xc;
  }
}
static const uint8_t k_s7[] = { 7, 8, 9, 4, 5, 10, 11 }, k_s5[] = { 7, 8, 9, 4, 5 };
/* ---- 0042eaa6: ближняя плоскость, 7 атрибутов (цвет, u, v, u2, v2) → [7], [8], [9], [4], [5], [10], [11] ---- */
void P102_ClipNear7(const uint8_t *a, const uint8_t *b, float ua0, float ua1, float ua2, float ua3, float ua4, float ua5, float ua6,
                    float ub0, float ub1, float ub2, float ub3, float ub4, float ub5, float ub6) {
  const float ua[7] = { ua0, ua1, ua2, ua3, ua4, ua5, ua6 }, ub[7] = { ub0, ub1, ub2, ub3, ub4, ub5, ub6 };
  clip_attr2(a, b, 0, ua, ub, k_s7, 7, 5);
}
/* ---- 0042f3f7: дальняя плоскость, 5 атрибутов (цвет + u, v) → [7], [8], [9], [4], [5] ---- */
void P102_ClipFar5(const uint8_t *a, const uint8_t *b, float ua0, float ua1, float ua2, float ua3, float ua4,
                   float ub0, float ub1, float ub2, float ub3, float ub4) {
  const float ua[5] = { ua0, ua1, ua2, ua3, ua4 }, ub[5] = { ub0, ub1, ub2, ub3, ub4 };
  clip_attr2(a, b, 1, ua, ub, k_s5, 5, 5);
}

/* ---- 0051a750: сторона дороги в точке (x, z): 0..3 (бит 1 — полоса закрыта по маске узла), -1 — не дорога ---- */
/* P102_RoadSide — Game.exe 0051a750, cdecl.  Road side at (x, z): 0..3 (bit 1 = lane closed by the node mask), -1 = not a road. */
int32_t P102_RoadSide(float x, float z) {
  if (P11_00b5a8e8 == 0) return -1;
  P11_00ba52d0 = fround(x);
  int32_t cx = (P11_00ba52d0 + 0x2ee + P62_MapC64) / 0x5dc;
  P11_00ba52d0 = fround(z);
  int32_t cz = (P62_Map2C40 - (P11_00ba52d0 - 0x2ee)) / 0x5dc;
  if (cx < 0 || P62_MapW <= cx || cz < 0 || P62_MapH <= cz) return -1;
  int32_t n = P62_MapN;
#ifndef RE_HOOK_BUILD
  if (n <= 0) return -1;
#endif
  const int16_t *t = (const int16_t *)P54_RoadA[((uint32_t)(cx / n) & 1u) + ((uint32_t)((P72_Rows - 1) - cz / n) & 1u) * 2];
#ifndef RE_HOOK_BUILD
  if (t == NULL) return -1;
#endif
  int16_t s = t[(cz - (cz / n) * n) * n + (cx - (cx / n) * n)];
  if (((int32_t)s & 0xc000) != 0) return -1;
#ifndef RE_HOOK_BUILD
  if ((uint32_t)(s + 1) * 0x42 > sizeof P11_00bf1c40) return -1;
#endif
  P102_B5A914 = s;
  int32_t vert = 0;
  int16_t a = rd16s(&P11_00bf1c40[2 + s * 0x42]);
  for (int32_t k = 0; k < 4; k++) {
#ifndef RE_HOOK_BUILD
    if (a < 0 || (uint32_t)(a + 1) * 0x2c > sizeof P11_00c1ed80) break;
#endif
    if (rd16s(&P11_00c1ed80[0xa + a * 0x2c + k * 8]) == s) break;
    vert ^= 1;
  }
  int8_t cnt = 0;
  for (;;) {   /* сдвиг по клетке, пока тот же узел (в оригинале — без проверки границ) */
    if (cx < 0 || P62_MapW <= cx || cz < 0 || P62_MapH <= cz) break;
    const int16_t *tt = (const int16_t *)P54_RoadA[((uint32_t)(cx / n) & 1u) + ((uint32_t)((P72_Rows - 1) - cz / n) & 1u) * 2];
#ifndef RE_HOOK_BUILD
    if (tt == NULL) break;
#endif
    if (tt[(cz - (cz / n) * n) * n + (cx - (cx / n) * n)] != s) break;
    cnt++;
    if (vert) cz++; else cx++;
  }
  const uint8_t *nd = &P11_00bf1c40[s * 0x42];
  if (((uint8_t)(1u << ((uint32_t)(nd[6] - (uint8_t)cnt) & 0x1fu)) & nd[7]) == 0) return vert ? 3 : 2;
  return vert ? 1 : 0;
}

/* ---- 0048f899: столкновение машин a и b (0 — игрок, 0x41 — соперник): трафик сворачивает, сирена/звук удара ---- */
/* P102_CarsCollide — Game.exe 0048f899, cdecl.  Collision reaction between cars a and b (0 = player, 0x41 = opponent): traffic swerves; siren /
   crash sound. */
void P102_CarsCollide(int32_t a, int32_t b, int32_t force) {
  uint8_t *ra = trec(a - 1), *rb = trec(b - 1);
  uint8_t a_c = a == 0 ? ((const uint8_t *)P12_01144340)[0x58] : ra[0xc];   /* при a = 0 оригинал читает «запись -1» (01144398) */
  if ((a == 0 && rb[5] == 0 && a_c == 1) || (b == 0 && ra[5] == 0 && ra[0xc] == 1))
    P62_SpawnTrafficCar(a == 0 ? b - 1 : a - 1);
  if (G6_00B87EB0 != 0 && ((a == 0 && b == 0x41) || (a == 0x41 && b == 0)) &&
      P95_B87F08 == 0 && P100_1426FC == 0 && P75_E4 == 0 && P100_143720 == 0) {
    P75_E4 = 1;
    P101_GoalPos[0] = (float)P99_Cars[0x41].pos[0]; P101_GoalPos[1] = (float)P99_Cars[0x41].pos[1]; P101_GoalPos[2] = (float)P99_Cars[0x41].pos[2];
  }
  if (a == 0 || 0x40 < a) {
    if (rb[7] != 0) P56_LoopStart(b);
    rb[2] = 1; rb[8] = 0;
  } else if (b == 0 || 0x40 < b) {
    if (ra[7] != 0) P56_LoopStart(a);
    ra[2] = 1; ra[8] = 0;
    if (ra[5] == 0) P95_SndTrigger(P97_D11980, 4, 0x1000);       /* в оригинале обе ветви force < 0x20 одинаковы */
    else if (ra[1] != 4) P95_SndTrigger(P97_D11980, 5, 0x1000);
    if (b == 0) P102_HitFrame = P62_Frame;
  } else if (ra[2] == 1 || rb[2] == 1 || ra[5] != 0 || rb[5] != 0) {
    if (ra[7] != 0) P56_LoopStart(a);
    if (rb[7] != 0) P56_LoopStart(b);
    ra[2] = 1; ra[8] = 0; rb[2] = 1; rb[8] = 0;
  }
  (void)force;
}

/* ---- 005158cf: 4 плоскости коробки машины по направлению скорости (out: 4 × {nx, —, nz, d}); dist — сдвиг передней ---- */
/* P102_CarPlanes — Game.exe 005158cf, cdecl.  Four planes of a car's box oriented along its velocity (out: 4 x {nx, -, nz, d}); dist moves the
   front plane. */
void P102_CarPlanes(const uint8_t *car, float *out, int32_t dist) {
  float fx = (float)rd32(car + 0xc8), fz = (float)rd32(car + 0xd0);
  uint32_t u = (uint32_t)-P44_Atan2(rd32(car + 0x40) >> 8, rd32(car + 0x48) >> 8) & 0xfff;
  int32_t i = (int32_t)((((((uint32_t)rd32(car + 0x100) - u) + 0x800) & 0xfff) - 0x800) & 0xfff) >> 2;
  const int32_t *t = P96_RotTab[i];
  float mn = (float)t[0], mx = (float)t[0];
  for (int32_t k = 2; k <= 6; k += 2) { if ((float)t[k] < mn) mn = (float)t[k]; }
  for (int32_t k = 2; k <= 6; k += 2) { if (mx < (float)t[k]) mx = (float)t[k]; }
  float w = mx - mn;
  if (w < 0.0f) w = -w;   /* .rdata 00546024 = 0 */
  P11_00ba52d0 = fround(w);
  int32_t h = P11_00ba52d0 >> 1;
  float c = P43_Sin[u + 0x400], s = P43_Sin[u], ns = -s;
  out[0] = -c; out[2] = ns;
  out[3] = ((float)-h * s + fz) * out[2] + ((float)-h * c + fx) * out[0];
  out[4] = c; out[6] = s;
  out[7] = ((float)h * s + fz) * out[6] + ((float)h * c + fx) * out[4];
  out[8] = ns; out[10] = c;
  out[0xb] = ((float)dist * c + fz) * out[10] + ((float)dist * ns + fx) * out[8];
  out[0xc] = s; out[0xe] = -c;
  out[0xf] = fz * out[0xe] + fx * out[0xc];
}

/* ---- 0049521e: машина трафика впереди на той же полосе (+0x28 дорога, +0x24 направление, +9 полоса) не дальше dist; номер или -1 ---- */
/* rec_cell — Map cell of a traffic record. */
static void rec_cell(uint8_t *r) {
  const uint8_t *c = tcar(r[0]);
  wr32(r + 0x48, rd32(c + 0xc8) + 0x2ee);
  wr32(r + 0x4c, rd32(c + 0xd0) - 0x2ee);
  P11_00ba52d0 = fround((float)rd32(r + 0x48) * P63_Scale); wr32(r + 0x48, P11_00ba52d0);
  P11_00ba52d0 = fround((float)rd32(r + 0x4c) * P63_Scale); wr32(r + 0x4c, P11_00ba52d0);
}
/* P102_TrafficAhead — Game.exe 0049521e, cdecl.  Traffic car ahead in the same lane (TREC_NEXT_NODE road, TREC_ROAD_DIR direction, byte 9 lane)
   within dist; returns its index or -1. */
int32_t P102_TrafficAhead(uint8_t *rec, int32_t dist, int32_t parked) {
  int32_t d = 1000;
  if (rec[0x10] != 0) return -1;
  rec_cell(rec);
  for (int32_t i = 0; i < P51_TrafficN; i++) {
    uint8_t *o = trec(i);
    if (rec[0] == o[0] || o[1] == 0 || (parked == 0 && o[1] == 1)) continue;
    if (rd32(rec + 0x28) != rd32(o + 0x28) || rd32(rec + 0x24) != rd32(o + 0x24) || rec[9] != o[9]) continue;
    int32_t ax = rd32(rec + 0x48), az = rd32(rec + 0x4c);
    if (parked == 0) {
      rec_cell(o);
      int32_t bx = rd32(o + 0x48), bz = rd32(o + 0x4c);
      switch (rd32(rec + 0x24)) {
      case 0: if (az < bz) d = bz - az; break;
      case 1: if (ax < bx) d = bx - ax; break;
      case 2: if (bz < az) d = az - bz; break;
      case 3: if (bx < ax) d = ax - bx; break;
      default: break;
      }
      if (iabs(d) <= dist) return i;
    } else {
      int32_t bx = rd32(o + 0x48), bz = rd32(o + 0x4c);
      switch (rd32(rec + 0x24)) {
      case 0: if (bz < az) d = az - bz; break;
      case 1: if (ax < bx) d = bx - ax; break;
      case 2: if (az < bz) d = bz - az; break;
      case 3: if (bx < ax) d = ax - bx; break;
      default: break;
      }
      if (-1 < d && d <= dist) return i;
    }
  }
  return -1;
}

/* ---- 004c4ef9: доступность пунктов меню режиссёра (узлы 1..0x23) по кадру, режиму и камерам; метка __fastcall ложная ---- */
/* P102_DirMenuNodes — Game.exe 004c4ef9, cdecl.  Which director menu entries (nodes 1..0x23) are available, by frame, mode and cameras.  The
   __fastcall label in Ghidra is wrong. */
void P102_DirMenuNodes(void) {
  for (int32_t id = 1; id <= 0x23; id++) SetNodeEnabled(id, 1);
  if (DirectorUnk6C < 3) SetNodeEnabled(5, 0);
  if (DirectorLastFrame <= DirectorUnk6C) {
    SetNodeEnabled(1, 0); SetNodeEnabled(2, 0); SetNodeEnabled(3, 0); SetNodeEnabled(4, 0); SetNodeEnabled(6, 0); SetNodeEnabled(7, 0);
    if (DirectorUnk6C < 3) DirectorUnk7C = 8;
    else if (DirectorUnk7C != 5 && DirectorUnk7C != 8) DirectorUnk7C = 5;
  }
  if (P59_Mode1137324 == 2) { SetNodeEnabled(0x14, 0); SetNodeEnabled(0x16, 0); SetNodeEnabled(0x18, 0); SetNodeEnabled(0x1a, 0); }
  if (CountNearbyCars() == 0) { SetNodeEnabled(0x1e, 0); SetNodeEnabled(0x22, 0); SetNodeEnabled(0x1c, 0); SetNodeEnabled(0x1d, 0); }
  if (P59_Mode1137324 == 0) { SetNodeEnabled(0x16, 0); SetNodeEnabled(0x1a, 0); }
  if (P59_Mode1137324 != 0x11) { SetNodeEnabled(0x16, 0); SetNodeEnabled(0x1a, 0); }
  if (FindCameraForFrame(DirectorUnk6C) == NULL) SetNodeEnabled(7, 0);
}

/* флаг 00b201dc «рисовать объекты B» (читает P96_AddObjB) — все псевдонимы */
/* set_b201dc — Write 00b201dc ("draw B objects", read by P96_AddObjB) and all its aliases. */
static void set_b201dc(int32_t v) { P13_00b201dc = v; G00B201DC = v; MenuVarB201DC = v; }
/* ---- 004af2fd: отметка (тень/след) объекта obj по смещению (x, y, z) в его системе: запись C (G01105D80) + объект B ---- */
/* P102_ObjMark — Game.exe 004af2fd, cdecl.  Mark (shadow / track) for object obj at offset (x, y, z) in its own frame: a C record
   (01105d80) plus a B object. */
void P102_ObjMark(const uint8_t *obj, float x, float y, float z, int16_t kind) {
  int32_t sv = P13_00b201dc;
  if (P52_Ones3 != 0) {
    int32_t ang = rd32(obj + 0x18);
    float *r = (float *)P95_ObjPtr((uint32_t)G01105D80);
#ifndef RE_HOOK_BUILD
    if (r == NULL || P56_EulerTab == NULL) return;
#endif
    set_b201dc(1);
    r[0] = x; r[1] = y; r[2] = z;
    P44_MatPtr = (float *)(void *)(P56_EulerTab + ((uint32_t)-ang & 0xfffu) * 0x40);
    P44_Xform(r);
    r[0] = r[0] + rdf_(obj + 8); r[1] = r[1] + rdf_(obj + 0xc); r[2] = r[2] + rdf_(obj + 0x10);
    float w[4] = { r[0], r[1], r[2], r[3] };
    r[0] = r[0] - P44_CamX; r[1] = r[1] - P44_CamY; r[2] = r[2] - P44_CamZ;
    P44_MatPtr = P44_ViewMatT;
    P44_Xform(r);
    if (P95_Near <= r[2]) {
      P11_00ba52d0 = fround(x); int32_t ix = P11_00ba52d0;
      P11_00ba52d0 = fround(y);
      P102_ObjBKey = FindOrAdd_004BB11F((int32_t)re_addr(obj) + ix + P11_00ba52d0);
      int32_t fl = P102_ObjBKey < 0 ? 0 : 0x200000;
      int32_t uv[4]; memcpy(uv, w, sizeof uv);
      if (kind == 0x200) P96_AddObjB(r, uv, 0, (int16_t)ang, (uint32_t)(fl + 1), 1, -1, P102_ObjBKey);
      else if (kind == 0x400) P96_AddObjB(r, uv, 0, (int16_t)ang, (uint32_t)(fl + 3), 1, -1, P102_ObjBKey);
      else if (kind == 0x800) P96_AddObjB(r, uv, 0, (int16_t)ang, (uint32_t)(fl + 2), 1, -1, P102_ObjBKey);
      r[4] = r[0]; r[5] = r[1]; r[6] = r[2]; r[7] = r[3];
      r[0x1a] = (float)kind;
      wr16(&r[0x19], 100);
      wr16(&r[0x1b], 0);
      wr16((uint8_t *)r + 0x6e, (uint16_t)ang);
      G01105D80 += 0x78;
      G01129580++;
    }
  }
  set_b201dc(sv);
}

/* ---- 004af619: следы шин машины car (8 точек: 4 × 2 стороны) объектами B, если скорость ≥ 0.01 и машина на земле ---- */
/* P102_CarTracks — Game.exe 004af619, cdecl.  Tyre tracks of car `car`: 8 points (4 x 2 sides) as B objects when its speed >= 0.01 and it is
   on the ground. */
void P102_CarTracks(int32_t car, const int16_t *phase, float speed) {
  static const float k_off[4] = { 48.0f, 68.0f, 90.0f, 112.0f };   /* .data 005539f8 */
  int32_t sv = P13_00b201dc;
#ifndef RE_HOOK_BUILD
  if (car < 0 || car >= 65) return;
#endif
  const uint8_t *c = carp(car);
  const uint8_t *m = carmodel(c[2]);
  if (P52_Ones1 != 0 && 99 < rd16s(c + 0xc) && 0.01f <= speed) {   /* .rdata 0054614c */
    float *r = (float *)P95_ObjPtr((uint32_t)G010FFD08);
#ifndef RE_HOOK_BUILD
    if (r == NULL) return;
#endif
    set_b201dc(1);
    int16_t a0 = rd16s(c + 0xe8);
    uint32_t hd = ((uint32_t)rd32(c + 0x100) + 0x800) & 0xfff;
    uint32_t ph = (uint32_t)((car * 0x200 + (int32_t)*phase) & 0xfff) >> 9;
    int32_t sg = 1;
    for (int32_t side = 2; side != 0; side--) {
      for (int32_t k = 4; k != 0; k--) {
        r[0] = (float)sg * k_off[k - 1];
        r[1] = rdf_(m + 0xa4);
        wr16(&r[0x1b], (uint16_t)a0);
        wr16((uint8_t *)r + 0x6e, (uint16_t)hd);
        r[2] = 0.0f;
        P44_MatPtr = P98_CarMat[car];
        P44_XformT(r);
        P44_MatPtr = P44_ViewMatT;
        r[0] = ((float)rd32(c + 0xc8) - P44_CamX) + r[0];
        r[1] = ((float)-rd32(c + 0xcc) - P44_CamY) + r[1];
        r[2] = ((float)rd32(c + 0xd0) - P44_CamZ) + r[2];
        P44_Xform(r);
        if (ph < 3) {
          uint32_t fl = side - 1 == 1 ? (ph == 1 ? 0xb : 9) : (ph == 1 ? 0xc : 10);
          P96_AddObjB(r, (const int32_t *)(const void *)r, a0, (int16_t)hd, fl, 0, -1, -1);
        }
        ph = (ph & 7) + 1;
      }
      sg = -sg;
    }
  }
  set_b201dc(sv);
}
