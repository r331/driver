/* ported129 — car collisions with static map objects (Game.exe, cdecl): object collision boxes, merging of adjacent
   boxes, the car-vs-box impulse response with breakable objects, and marking traffic cars on the radar grid.
   Collision box (int32[8], P129_Boxes): [0..2] centre x, y, z; [4] half-size x; [5] half-size z; [6] angle 0..0xfff
   (+ flag 0x400 after a merge swap); [7] height.  Original note: */
/* v1.74: ported129 — столкновения машин со статическими объектами (см. ported129.h).
   005001bb — слияние двух отложенных коробок (обе без поворота &0x3ff, по высоте рядом с машиной): при первом слиянии
     полуоси X/Z меняются местами и флаг = 0x400; соседство по X (сторона машины одна, края ближе 0x32, по Z перекрытие)
     или по Z — коробка i становится охватывающей, у j полуX = 0.
   0049b14d — удар машины по коробке объекта: две записи по 0x18 слов (машина, коробка) → P100_BoxOverlap,
     P103_BoxContactTime, P102_BoxContact; импульс по нормали, звук (P95_SndTrigger 6/7), разбиваемые объекты (&0x400:
     P125_DropHit, звук из .data 00572b40 по адресу модели, частицы), обломки/пыль (&0x2000) или искры, P100_CarHit,
     импульс в угловую (+0x68..) и линейную (+0x40..) скорость. Высота над землёй — .data 00551438 по городу D_00b87e30.
   00500937 — коробки модели объекта (+0x34 модели: n, записи по 10 слов вида 0/1) в мировые координаты по P56_EulerTab;
     сразу P129_ObjHit или (defer) — в отложенный список P129_Boxes (до 60).
   00500e1d — для машины: клетка сетки P54_GridN, P97_ScriptEachP, P53_CallWithStateP, объекты клетки → 00500937(defer),
     слияние, удары. Отладочный блок 00501173.. недостижим (xor edx,edx) — не переносится.
   0050b088 — машины трафика рядом (P59_NearList) кроме цели записи: прямоугольник машины (180 × длина по скорости, хвост
     −900) в клетках радара; клетки 0x37×0x37 с площадью пересечения (P128_ClipAreaN) > 50000 получают биты 0x22/24/28/30
     в P77_C5FE00. Многоугольник 00c7d820 оригинала (список со ссылками) — локальный массив точек в native. */
#include "ported129.h"
#include <stdio.h>
#include <stdlib.h>
#include "ported128.h"
#include "unported.h"
#include "engine.h"
#include "reptr.h"
#include "cartab.h"
#include "director.h"
#include "smallfuncs.h"
#include "smallfuncs2.h"
#include "ported4.h"
#include "ported6.h"
#include "ported11.h"
#include "ported14.h"
#include "ported42.h"
#include "ported43.h"
#include "ported44.h"
#include "ported48.h"
#include "ported53.h"
#include "ported54.h"
#include "ported56.h"
#include "ported58.h"
#include "ported59.h"
#include "ported62.h"
#include "ported63.h"
#include "ported66.h"
#include "ported68.h"
#include "ported77.h"
#include "ported79.h"
#include "ported95.h"
#include "ported96.h"
#include "ported97.h"
#include "ported100.h"
#include "ported102.h"
#include "ported103.h"
#include "ported125.h"
#include "menustate.h"
#include <math.h>
#include <string.h>

#ifndef RE_HOOK_BUILD
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P129_Boxes")
#undef P129_Boxes
#pragma push_macro("P129_Boxes") /*gvi*/
#undef P129_Boxes /*gvi*/
p129_boxes_t P129_Boxes;
#pragma pop_macro("P129_Boxes") /*gvi*/
#pragma pop_macro("P129_Boxes")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P129_BoxN")
#undef P129_BoxN
#pragma push_macro("P129_BoxN") /*gvi*/
#undef P129_BoxN /*gvi*/
int32_t P129_BoxN;
#pragma pop_macro("P129_BoxN") /*gvi*/
#pragma pop_macro("P129_BoxN")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P129_HitModel")
#undef P129_HitModel
#pragma push_macro("P129_HitModel") /*gvi*/
#undef P129_HitModel /*gvi*/
uint16_t P129_HitModel;
#pragma pop_macro("P129_HitModel") /*gvi*/
#pragma pop_macro("P129_HitModel")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P129_C81680")
#undef P129_C81680
#pragma push_macro("P129_C81680") /*gvi*/
#undef P129_C81680 /*gvi*/
int32_t P129_C81680;
#pragma pop_macro("P129_C81680") /*gvi*/
#pragma pop_macro("P129_C81680")
#endif
#endif
/* 00b326d0: объект каждой отложенной коробки. Пишется и читается только внутри одного вызова 00500e1d (00500937 → цикл
   ударов), объекты — записи кучи G6_00D00208; в native — родные указатели (поле нигде больше не читается). */
static uint8_t *s_box_obj[60];
/* .data 00551438: высота подъёма частиц по городу (D_00b87e30) */
static const int32_t k_lift[8] = { 735, 580, 0, 1190, 0, 0, 0, 0 };

#include "memrw.h"
#include "carfields.h"
static int16_t rd16(const void *p) { int16_t v; memcpy(&v, p, 2); return v; }
/* 32-bit helpers: M = wrapping imul, add32 = wrapping add in memory, f12 = round 20.12 to integer. */
static int32_t M(int32_t a, int32_t b) { return (int32_t)((uint32_t)a * (uint32_t)b); }   /* imul с переполнением */
static void add32(uint8_t *p, int32_t d) { wr32(p, (int32_t)((uint32_t)rd32(p) + (uint32_t)d)); }
static int32_t f12(int32_t v) { return (int32_t)((uint32_t)v + 0x800u) >> 12; }
/* Map model mi (or NULL) and its flags (+8: 0x400 breakable, 0x1000 / 0x2000 hit effects) / flags2 (+2: 8 = silent). */
static const uint8_t *model(int32_t mi) {
  if ((uint32_t)mi >= 1126u) return NULL;                                              /* защита */
  return P79_ModelTab[mi] ? (const uint8_t *)P79_PTR(P79_ModelTab[mi]) : NULL;   /* v2.07: ссылка арены карты (в hook — адрес) */
}
static uint32_t mflags(int32_t mi) { const uint8_t *m = model(mi); return m ? (uint32_t)rd32(m + 8) : 0; }
static uint16_t mflags2(int32_t mi) { const uint8_t *m = model(mi); return m ? rdu16(m + 2) : 0; }
/* -1 when c <= v, else +1 (which side of a box centre the car is on). */
static int le_side(int32_t c, int32_t v) { return (c == v || (int32_t)((uint32_t)c - (uint32_t)v) < 0) ? -1 : 1; }

/* ---- 005001bb ---- */
/* Grows box a to the bounding box of a and b (x / z extents, y by half heights) and disables b (half x = 0). */
static int32_t merge_into(int32_t *a, int32_t *b) {
  int32_t hx = (b[0] + b[4] < a[0] + a[4]) ? a[0] + a[4] : b[0] + b[4];
  int32_t hz = (b[2] + b[5] < a[2] + a[5]) ? a[2] + a[5] : b[2] + b[5];
  int32_t hy = (b[1] + b[7] / 2 < a[1] + a[7] / 2) ? a[1] + a[7] / 2 : b[1] + b[7] / 2;
  int32_t lx = (a[0] - a[4] < b[0] - b[4]) ? a[0] - a[4] : b[0] - b[4];
  int32_t lz = (a[2] - a[5] < b[2] - b[5]) ? a[2] - a[5] : b[2] - b[5];
  int32_t ly = (a[1] - a[7] / 2 < b[1] - b[7] / 2) ? a[1] - a[7] / 2 : b[1] - b[7] / 2;
  a[0] = (hx + lx) >> 1; a[1] = (hy + ly) >> 1; a[2] = (hz + lz) >> 1;
  a[4] = (hx - lx) >> 1; a[5] = (hz - lz) >> 1; a[7] = iabs(hy - ly);
  b[4] = 0;
  return 1;
}
/* P129_BoxMerge — Game.exe 005001bb.  Merges deferred boxes i and j when both are axis-aligned, both are at the car's
   height (within height + 0x7d), the car is on the same side of both, and their facing edges are within 0x32 with
   overlap along the other axis — so a car sliding along a row of objects hits one wall instead of the seams.
   Only for the player (car 0) and cars above 0x40.  On first merge the half sizes x/z are swapped and the box
   marked 0x400 (TODO(RE): unsure why the swap).  Returns 1 if merged. */
int32_t P129_BoxMerge(int32_t i, int32_t j, int32_t car) {
  if (car != 0 && car <= 0x40) return 0;
  if ((uint32_t)i >= 60u || (uint32_t)j >= 60u || (uint32_t)car >= (uint32_t)P99_CARS_N) return 0;   /* защита */
  int32_t *a = P129_Boxes[i], *b = P129_Boxes[j];
  const uint8_t *c = (const uint8_t *)&P99_Cars[car];
  if ((a[6] & 0x3ff) != 0 || (b[6] & 0x3ff) != 0) return 0;
  int32_t cy = rd32(c + CAR_POS2 + 4);
  if (iabs(cy - a[1]) > a[7] + 0x7d) return 0;
  if (iabs(cy - b[1]) > b[7] + 0x7d) return 0;
  if ((a[6] & 0x400) == 0) { int32_t t = a[4]; a[4] = a[5]; a[5] = t; a[6] = 0x400; }
  if ((b[6] & 0x400) == 0) { int32_t t = b[4]; b[4] = b[5]; b[5] = t; b[6] = 0x400; }
  int32_t cx = rd32(c + CAR_POS2), cz = rd32(c + CAR_POS2 + 8), s, d;
  s = le_side(cx, a[0]);
  if (s == le_side(cx, b[0])) {
    d = a[0] + s * a[4] - b[0] - s * b[4];
    if (d < 0x32 && -0x32 < d && iabs(a[2] - b[2]) < a[5] + 0x32 + b[5]) return merge_into(a, b);
  }
  s = le_side(cz, a[2]);
  if (s == le_side(cz, b[2])) {
    d = a[2] + s * a[5] - b[2] - s * b[5];
    if (d < 0x32 && -0x32 < d && iabs(a[0] - b[0]) < a[4] + 0x32 + b[4]) return merge_into(a, b);
  }
  return 0;
}

/* ---- 0049b14d ---- */
/* 3D sound smp on voice at integer point o. */
static void snd_at(uint32_t smp, int32_t voice, const int32_t *o) { P97_SndStart(smp, voice, (float)o[0], (float)o[1], (float)o[2]); }
/* P129_ObjHit — Game.exe 0049b14d.  Collision of car record c with collision box box of map object obj.
   The car is moved one velocity step ahead and tested as an oriented box (length 3/4 or 11/12 of the model
   length when AI-driven / not) against the object box (P100_BoxOverlap); no overlap -> step undone, 0.
   On contact: separation along the normal, contact point velocity (linear + angular x lever), impulse
   imp = -(v . n).  If closing (imp > 0): crash sounds, breakable objects (model flag 0x400) are knocked over with
   their own sound / particles and the car keeps its position; hard hits (> 0xa000) spawn sparks or debris
   (model flag 0x2000) and smoke; the car takes damage (P100_CarHit, subject to menu options); then the impulse is
   divided by the effective mass term and applied to the linear velocity and the angular accumulator, with
   time-of-impact correction tt.  Returns 1 when the boxes touched.  TODO(RE): unsure — +0x68..0x70 receives the
   angular impulse (CAR_DANGVEL_PEND in carfields.h). */
int32_t P129_ObjHit(uint8_t *c, int32_t *box, uint8_t *obj) {
  if (c == NULL || box == NULL || obj == NULL) return 0;                               /* защита */
  int32_t mi = rd32(obj + 4);
  uint32_t fl = mflags(mi);
  int32_t brk = 0;
  if ((fl & 0x400) != 0) { brk = 1; if (P129_C81130 == 1 && c[0] == 0x41) return 0; }
  if ((uint32_t)mi >= 0x1000u || S_00BDCD00[mi] == 0) return 0;
  if (box[7] + 0x7d < iabs(rd32(c + CAR_POS2 + 4) - box[1])) return 0;
  int32_t x0 = rd32(c + CAR_POS2), z0 = rd32(c + CAR_POS2 + 8);
  uint32_t ty = c[2] < 0x20 ? c[2] : 0;                                                /* защита */
  int16_t len = rd16(&P100_CarDim[ty * 0x16c]), wid = rd16(&P100_CarDim[ty * 0x16c + 4]);
  int32_t b[64]; memset(b, 0, sizeof b);              /* local_f0: две записи по 0x18 слов; b + 49 — точка контакта */
  int32_t vx = f12(rd32(c + CAR_VEL)), vz = f12(rd32(c + CAR_VEL + 8));
  add32(c + CAR_POS2, vx); add32(c + CAR_POS2 + 8, vz);
  b[0] = rd32(c + CAR_POS2); b[2] = rd32(c + CAR_POS2 + 8); b[12] = vx; b[14] = vz;
  b[16] = rd32(c + CAR_HEADING); b[17] = wid;
  b[18] = (c[CAR_AI_DRIVEN] == 1) ? (len * 3) / 4 : (len * 0xb) / 0xc;
  b[23] = (f12(rd32(c + CAR_ANGVEL + 4)) * 0x28) >> 8;
  b[24] = box[0]; b[26] = box[2]; b[40] = box[6]; b[41] = box[4]; b[42] = box[5];
  if (P100_BoxOverlap(b) == 0) {
    add32(c + CAR_POS2, -f12(rd32(c + CAR_VEL))); add32(c + CAR_POS2 + 8, -f12(rd32(c + CAR_VEL + 8)));
    return 0;
  }
  int32_t *o = b + 49;                                /* {x, y, z, -, nx, ny, nz, -, глубина} */
  int32_t tt = P103_BoxContactTime(b, (uint8_t *)o);
  P102_BoxContact(b, o);
  o[1] = rd32(c + CAR_POS2 + 4) + 0x3c;
  o[4] = -o[4]; o[5] = 0; o[6] = -o[6];
  add32(c + CAR_POS2, (M(o[8], o[4]) + 0x800) >> 12);
  add32(c + CAR_POS2 + 8, (M(o[8], o[6]) + 0x800) >> 12);
  int32_t rx = o[0] - rd32(c + CAR_POS2), ry = o[1] - rd32(c + CAR_POS2 + 4), rz = o[2] - rd32(c + CAR_POS2 + 8);
  int32_t c40 = rd32(c + CAR_VEL), c44 = rd32(c + CAR_VEL + 4), c48 = rd32(c + CAR_VEL + 8), c4c = rd32(c + CAR_ANGVEL), c50 = rd32(c + CAR_ANGVEL + 4), c54 = rd32(c + CAR_ANGVEL + 8);
  int32_t wx = ((M(c50, rz) - M(c54, ry) + 0x800) >> 12) + c40;
  int32_t wz = ((M(c4c, ry) - M(c50, rx) + 0x800) >> 12) + c48;
  (void)c44;
  /* wx / wz: velocity of the contact point = v + w x r (x and z only) */
  int32_t imp = -(M(wx / 256, o[4] / 16) + M(wz / 256, o[6] / 16));   /* closing speed along the normal */
  if (0 < imp) {
    if (c[0] == 0) {
      int32_t ch = 6;
      if (!(P129_C81680 == 0x1be || P129_C81680 == 0x1bf || P129_C81680 == 0x15a || P129_C81680 == 0x15b) && brk != 0) ch = 7;
      P95_SndTrigger((uint8_t *)P97_D11980, ch, 0x1000);
    }
    o[1] = -o[1];
    int32_t dv[3] = { c40 / 4096, -0x11, c48 / 4096 };
    if ((fl & 0x400) != 0) {
      if (P129_C81130 != 0 && c[0] == 0x41) return 0;
      P125_DropHit(obj, dv);
      if ((mflags2(mi) & 8) == 0) {
        const uint32_t *t = (const uint32_t *)P11_00572b40, *r = NULL;
        uint32_t ma = (uint32_t)mi < 1126u ? P79_ModelTab[mi] : 0;
        for (const uint32_t *p = t; p[1] != 0 && p + 5 <= t + 0x400; p += 5) if (p[0] == ma) { r = p; break; }
        if (r == NULL) r = t;
        int32_t v = P97_SndStart(r[2], -1, (float)o[0], (float)o[1], (float)o[2]);
        if (v != -1) { SoundSetPos00523F8A(v, (int32_t)r[4]); P48_SetVoiceVolume(v, (int32_t)r[3]); }
      } else snd_at(3, 3, o);
      wr32(c + CAR_POS2, x0); wr32(c + CAR_POS2 + 8, z0);
      o[1] += 0x1e;
      P125_ObjABurst(o, dv, 10, 0);
      o[1] = -0x1e;
      P125_SmokePuffs(o, dv, 10, 0, -1);
      if (c[0] == 0) ReturnZero004E3B19();
      return 0;
    }
    if (0xa000 < imp) {
      uint32_t hf = mflags(P129_HitModel);
      if ((hf & 0x2000) == 0) {
        if (P14_00b87e84 != 0 && (hf & 0x1000) != 0 && P68_RepeatCheck((int32_t)(uint32_t)(uintptr_t)obj) != 0) {
          int32_t v0[4] = { 0, 0, 0, 0 };
          uint32_t lv = (uint32_t)D_00b87e30 < 8u ? (uint32_t)D_00b87e30 : 0;      /* защита */
          int32_t p[3] = { (int32_t)rdf(obj + 8), (int32_t)rdf(obj + 0xc) - k_lift[lv], (int32_t)rdf(obj + 0x10) };
          P125_ObjABurst(p, v0, 0x14, 1);
        }
        dv[1] -= 0x14; o[1] += 0x1e;
        P125_ObjABurst(o, dv, 4, 0);
        o[1] -= 0x1e; dv[1] += 0x14;
      } else {
        float f[3];
        f[0] = (float)o[0];
        float fy = -(float)o[1] - 250.0f;                                               /* .data 005460e4 */
        f[1] = (fy - (float)(N14_Rand() & 0xfe)) - P66_C128;
        f[2] = (float)o[2];
        P125_DebrisBurst(f, 3, 1);
        if ((N14_Rand() & 0xf) == 1) { f[1] += 100.0f; P96_SpawnDust(f, (int32_t)(N14_Rand() & 7)); }   /* .data 005460e0 */
        if (c[0] == 0) ReturnZero004E3B19();
        snd_at(4, 3, o);
      }
      if (imp < 0x28001) ReturnZero004E3B19();
      else {
        P125_SmokePuffs(o, dv, 6, 0, c[2]);
        if (c[0] == 0) ReturnZero004E3B19();
        if (c[0] == 0 || 0x40 < c[0]) snd_at(3, 3, o);
      }
    }
    if (((c[0] != 0 && G6_00B87EA0 == 0) || MenuOptBDFA4C == 0) && (MenuOptBDFA58 == 0 || c[2] != 1))
      P100_CarHit(c, b, o, imp);
    int32_t k = (M(rx, o[4]) + M(ry, o[5]) + 0x800 + M(rz, o[6])) >> 12;
    int32_t den = ((M(M(rx, rx) + M(rz, rz) - M(k, k), 0x6e) + 0x800) >> 12) + 0x1000;
    if (den == 0) den = 1;                                                               /* защита */
    if (imp < 0x7f001) imp = M(imp, 0x1000) / den; else imp = M(imp / den, 0x1000);
    int32_t q = M(imp, 9) / 16 / 64;
    int32_t ix = M(q, o[4] / 64), iy = M(q, o[5] / 64), iz = M(q, o[6] / 64);
    add32(c + CAR_POS2, -((M(0x1000 - tt, f12(rd32(c + CAR_VEL))) + 0x800) >> 12));
    add32(c + CAR_POS2 + 8, -((M(0x1000 - tt, f12(rd32(c + CAR_VEL + 8))) + 0x800) >> 12));
    add32(c + CAR_DANGVEL_PEND, (M(ry, iz) + 0x800) >> 12); add32(c + CAR_DANGVEL_PEND, -((M(rz, iy) + 0x800) >> 12));
    add32(c + CAR_DANGVEL_PEND + 4, (M(rz, ix) + 0x800) >> 12); add32(c + CAR_DANGVEL_PEND + 4, -((M(rx, iz) + 0x800) >> 12));
    add32(c + CAR_DANGVEL_PEND + 8, (M(rx, iy) + 0x800) >> 12); add32(c + CAR_DANGVEL_PEND + 8, -((M(ry, ix) + 0x800) >> 12));
    add32(c + CAR_VEL, ix); add32(c + CAR_VEL + 4, iy); add32(c + CAR_VEL + 8, iz);
    add32(c + CAR_POS2, (M(0x1000 - tt, f12(rd32(c + CAR_VEL))) + 0x800) >> 12);
    add32(c + CAR_POS2 + 8, (M(0x1000 - tt, f12(rd32(c + CAR_VEL + 8))) + 0x800) >> 12);
  }
  add32(c + CAR_POS2, -f12(rd32(c + CAR_VEL))); add32(c + CAR_POS2 + 8, -f12(rd32(c + CAR_VEL + 8)));
  return 1;
}

/* ---- 00500937 ---- */
/* P129_ObjBoxes — Game.exe 00500937.  Builds the world-space collision boxes of object obj (model mdl, list at model
   +0x34: count, then 10-int16 entries of kind 0 = rotated box / 1 = square box) when the car (radius + model radius +
   0x488) is near, and tests them at once (P129_ObjHit, idx = car index for the damage queue) or appends them to the
   deferred list (at most 60; breakable objects are never deferred). */
void P129_ObjBoxes(uint8_t *obj, const float *pos, uint8_t *car, int32_t idx, uint32_t mdl, int32_t defer) {
  const uint8_t *m = mdl ? (const uint8_t *)P79_PTR(mdl) : NULL;                       /* v2.07: P79_PTR, не re_ptr */
  if (m == NULL || obj == NULL || pos == NULL || car == NULL) return;                  /* защита */
  const uint8_t *L = rd32(m + 0x34) ? (const uint8_t *)P79_PTR((uint32_t)rd32(m + 0x34)) : NULL;
  if (L == NULL) return;
  P11_00ba52d0 = fround(rdf(m + 0x10));
  int32_t r = P11_00ba52d0 + 0x488 + rd32(car + CAR_SPEED);
  int32_t dx = (int32_t)fabs((double)(rdf(obj + 8) - pos[0]));
  int32_t dz = (int32_t)fabs((double)(rdf(obj + 0x10) - pos[2]));
#ifndef RE_HOOK_BUILD
  { static int k; if (getenv("RE_COLDBG2") && k++ < 60) fprintf(stderr, "[colb] obj %d mdl %08x L %08x n %d rad %d r %d dx %d dz %d opos %.0f %.0f %.0f ang %d\n", rdu16(obj + 4), mdl,
      (unsigned)rd32(m + 0x34), rd32(L), fround(rdf(m + 0x10)), r, dx, dz, rdf(obj + 8), rdf(obj + 0xc), rdf(obj + 0x10), rd32(obj + 0x18)); }
#endif
  if (!(M(dx, dx) + M(dz, dz) < M(r, r))) return;
  int32_t n = rd32(L);
  const uint8_t *e = L + 4;
  int32_t b[8] = { 0, 0, 0, 0, 0, 0, 0, 0 };
  for (int32_t k = 0; k < n && k < 0x400; k++, e += 20) {                               /* k < 0x400 — защита */
    int16_t e0 = rd16(e), e1 = rd16(e + 2), e2 = rd16(e + 4), e3 = rd16(e + 6), e5 = rd16(e + 10), e7 = rd16(e + 14), e8 = rd16(e + 16), e9 = rd16(e + 18);
    if (e0 == 0 || e0 == 1) {
      const float *t = (const float *)(void *)(P56_EulerTab + ((uint32_t)(-rd32(obj + 0x18)) & 0xfffu) * 0x40);
      P11_00ba52d0 = fround((float)e3 * t[6] + (float)e1 * t[0] + rdf(obj + 8)); b[0] = P11_00ba52d0;
      P11_00ba52d0 = fround(-((float)e2 + rdf(obj + 0xc))); b[1] = P11_00ba52d0;
      P11_00ba52d0 = fround((float)e3 * t[8] + (float)e1 * t[2] + rdf(obj + 0x10)); b[2] = P11_00ba52d0;
      if (e0 == 0) { b[4] = e9 / 2; b[5] = e7 / 2; b[6] = (rd32(obj + 0x18) + e5) & 0xfff; }
      else { b[4] = e7 / 2; b[5] = e7 / 2; b[6] = rd32(obj + 0x18) & 0xfff; }
      b[7] = e8 / 2;
      P129_HitModel = rdu16(obj + 4);
    }
    if (defer == 0 || 0x3b < P129_BoxN || (mflags(rd32(obj + 4)) & 0x400) != 0) {
      if (P129_ObjHit(car, b, obj) != 0) AddUnique_004C1F9B(idx - 1);
    } else {
      memcpy(P129_Boxes[P129_BoxN], b, sizeof b);
      s_box_obj[P129_BoxN] = obj;
      P129_BoxN++;
    }
  }
}

/* ---- 00500e1d ---- */
/* P129_CarObjects — Game.exe 00500e1d.  Static-object collisions of car: (far cars skipped in some modes) finds the
   map cell of the car in the 4-quadrant object grid, runs script / state callbacks, collects the boxes of all
   objects in the cell (deferred), merges adjacent boxes and resolves each remaining hit; a hit queues the car's
   damage-model update (AddUnique_004C1F9B).  RE_COLDBG=n prints a debug line every n calls for the player. */
void P129_CarObjects(int32_t car) {
  if (P95_B87E14 != 0) return;
  if ((uint32_t)car >= (uint32_t)P99_CARS_N) return;                                    /* защита */
  uint8_t *c = (uint8_t *)&P99_Cars[car];
  float pos[3] = { (float)rd32(c + CAR_POS_X), (float)rd32(c + CAR_POS_Y), (float)rd32(c + CAR_POS_Z) };
  if (P58_SB87EB0 != 0 && 0x13 < car) {
    float a = (float)fabs((double)(pos[0] - P44_CamX)), d = (float)fabs((double)(pos[2] - P44_CamZ));
    if (2024999936.0f < d * d + a * a) return;                                          /* .data 00546128 */
  }
  int32_t gx = (int32_t)((pos[0] + (float)P42_CellX) * P42_CellScale);
  int32_t gz = (int32_t)((pos[2] + (float)P42_CellY) * P42_CellScale);
  int32_t N = P54_GridN;
  if (N <= 0 || G6_00D01268 == NULL || G6_00CE0F20 == NULL || G6_00D00208 == NULL) return;   /* защита */
  int32_t qx = gx / N, qz = gz / N;
  int32_t cell = ((qx & 1) + (qz & 1) * 2) * N * N + (gx - qx * N) + (gz - qz * N) * N;
  if (cell < 0 || cell >= N * N * 4) return;
  int32_t node = ((const int32_t *)G6_00D01268)[cell];
  P129_BoxN = 0;
  P97_ScriptEachP(pos, c, car);
  if (P95_BDFA14 != 0) P53_CallWithStateP(pos, c, car);
#ifndef RE_HOOK_BUILD
  static int s_cdbg = -1; if (s_cdbg < 0) s_cdbg = getenv("RE_COLDBG") ? atoi(getenv("RE_COLDBG")) : 0;
  int32_t dbg_objs = 0, dbg_node0 = node; static int s_ck;
#endif
  for (int32_t guard = 0; node != -1 && guard < 0x14000; guard++) {                     /* guard — защита */
    if (node < 0 || node >= 0x14000) break;                                             /* защита */
    const int32_t *nd = (const int32_t *)((const uint8_t *)G6_00CE0F20 + (size_t)node * 8);
    uint8_t *o = (uint8_t *)G6_00D00208 + (size_t)nd[0] * 0x20;
    int32_t mi = rd32(o + 4);
    P129_ObjBoxes(o, pos, c, car, (uint32_t)mi < 1126u ? P79_ModelTab[mi] : 0, 1);
    node = nd[1];
#ifndef RE_HOOK_BUILD
    dbg_objs++;
#endif
  }
#ifndef RE_HOOK_BUILD
  if (s_cdbg > 0 && car == 0 && (s_ck++ % s_cdbg) == 0)
    fprintf(stderr, "[col] car0 pos %.0f %.0f %.0f g %d,%d cell %d node0 %d objs %d boxes %d\n", pos[0], pos[1], pos[2], gx, gz, cell, dbg_node0, dbg_objs, P129_BoxN);
#endif
  int32_t n = P129_BoxN < 60 ? P129_BoxN : 60;                                          /* защита */
  for (int32_t i = 0; i < n; i++) {
    if (P129_Boxes[i][4] == 0) continue;
    int32_t j = i;
    for (;;) {
      int32_t nx = j + 1;
      if (n <= nx) break;
      j = nx;
      if (P129_Boxes[nx][4] != 0 && P129_BoxMerge(nx, i, car) != 0) break;
    }
  }
  for (int32_t i = 0; i < n; i++) {
    if (P129_Boxes[i][4] == 0 || s_box_obj[i] == NULL) continue;
    P129_HitModel = rdu16(s_box_obj[i] + 4);
    if (P129_ObjHit(c, P129_Boxes[i], s_box_obj[i]) != 0) AddUnique_004C1F9B(car - 1);
  }
}

/* ---- 0050b088 ---- */
/* P129_MapCars — Game.exe 0050b088.  Marks the cars near traffic record rec (except its own target car) on the
   55 x 55 radar / route grid P77_C5FE00: each car is a rectangle 360 wide reaching ahead by speed * 20 + 0x1c2 and
   900 behind; every quarter cell (0x2ee units) it covers by more than 50000 square units gets bit 0x20 plus a
   quarter bit 2 << quarter (2, 4, 8, 0x10; quarter = (y & 1) * 2 + (x & 1)).  TODO(RE): unsure what consumes these bits. */
void P129_MapCars(int32_t *rec) {
  if (rec == NULL) return;                                                              /* защита */
  for (int32_t k = 0; k < P59_NearN && k < 64; k++) {
    uint32_t n = P59_NearList[k];
    if (n + 1 >= (uint32_t)P99_CARS_N) continue;                                        /* защита */
    const uint8_t *c = (const uint8_t *)&P99_Cars[n + 1];
    const uint8_t *tr = (const uint8_t *)TrafficRecs + n * 0x54;
    if (tr[1] == 0 || (uint32_t)tr[5] == (uint32_t)rec[0] + 1u) continue;
    int32_t x8 = rd32(c + CAR_POS_X) + 0x2ee + P62_MapC64;
    int32_t z1c = P62_Map2C40 - (rd32(c + CAR_POS_Z) - 0x2ee);
    uint32_t a = (uint32_t)(-rd32(c + CAR_HEADING)) & 0xfff;
    float s = P43_Sin[a], co = P43_Sin[(a + 0x400) & 0xfff];
    int32_t sp = rd32(c + CAR_SPEED) * 0x10;
    float L = (float)(sp + (sp >> 2) + 0x1c2);
    int32_t px[4], pz[4];
    P11_00ba52d0 = fround(-180.0f * co - L * s);       px[0] = P11_00ba52d0 + x8;   /* .data 005460d8 = −180 */
    P11_00ba52d0 = fround(L * co + -180.0f * s);       pz[0] = z1c - P11_00ba52d0;
    P11_00ba52d0 = fround(180.0f * co - L * s);        px[1] = P11_00ba52d0 + x8;   /* .data 005460d0 = 180 */
    P11_00ba52d0 = fround(L * co + 180.0f * s);        pz[1] = z1c - P11_00ba52d0;
    P11_00ba52d0 = fround(-180.0f * co - -900.0f * s); px[2] = P11_00ba52d0 + x8;   /* .data 00546a4c = −900 */
    P11_00ba52d0 = fround(-900.0f * co + -180.0f * s); pz[2] = z1c - P11_00ba52d0;
    P11_00ba52d0 = fround(180.0f * co - -900.0f * s);  px[3] = P11_00ba52d0 + x8;
    P11_00ba52d0 = fround(-900.0f * co + 180.0f * s);  pz[3] = z1c - P11_00ba52d0;
    int32_t lx = px[0], hx = px[0], lz = pz[0], hz = pz[0];
    for (int32_t i = 1; i < 4; i++) {
      if (px[i] < lx) lx = px[i];
      if (hx < px[i]) hx = px[i];
      if (pz[i] < lz) lz = pz[i];
      if (hz < pz[i]) hz = pz[i];
    }
    P11_00ba52d0 = fround((float)lx * P63_Scale); int32_t i1 = P11_00ba52d0 - 1;
    P11_00ba52d0 = fround((float)hx * P63_Scale); int32_t xe = P11_00ba52d0;
    P11_00ba52d0 = fround((float)lz * P63_Scale); int32_t i2 = P11_00ba52d0 - 1;
    P11_00ba52d0 = fround((float)hz * P63_Scale); int32_t ze = P11_00ba52d0;
    int32_t poly[8];
    for (int32_t i = 0; i < 4; i++) { poly[i * 2] = px[i] - i1 * 0x5dc; poly[i * 2 + 1] = pz[i] - i2 * 0x5dc; }
    int32_t x0 = i1 + (0x1b - rec[0x14]), x1 = xe + (0x1c - rec[0x14]);
    int32_t z0 = i2 + (0x1b - rec[0x15]), z1 = ze + (0x1c - rec[0x15]);
    if (x0 < 0) x0 = 0;
    if (z0 < 0) z0 = 0;
    if (0x36 < x1) x1 = 0x36;
    if (0x36 < z1) z1 = 0x36;
    int32_t rc[4];
    rc[1] = 0; rc[3] = 0x2ee;
    for (int32_t y = z0 * 2; y <= z1 * 2; y++) {
      rc[0] = 0; rc[2] = 0x2ee;
      for (int32_t x = x0 * 2; x <= x1 * 2; x++) {
        if (50000 < P128_ClipAreaN(poly, 4, rc)) {
          int32_t ci = (x >> 1) + (y >> 1) * 0x37;
          uint32_t bit = 0x20 | (2u << (((uint32_t)y & 1) << 1 | ((uint32_t)x & 1)));
          if (ci >= 0 && (uint32_t)(ci + 1) * 4 <= sizeof P77_C5FE00)                    /* защита */
            wr32(&P77_C5FE00[ci * 4], (int32_t)((uint32_t)rd32(&P77_C5FE00[ci * 4]) | bit));
        }
        rc[0] += 0x2ee; rc[2] += 0x2ee;
      }
      rc[1] += 0x2ee; rc[3] += 0x2ee;
    }
  }
}
