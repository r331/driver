/* v1.44: таблица игроков/машин 00d077c0 (game/cartab.h) и функции, читающие её (см. ported99.h). */
#include "ported99.h"
#include "p99_data.h"
#include "reptr.h"
#include "crt.h"
#include "engine.h"
#include "director.h"
#include "dirnodes.h"
#include "menustate.h"
#include "smallfuncs.h"
#include "uihandlers3.h"
#include "ported4.h"
#include "ported11.h"
#include "ported12.h"
#include "ported15.h"
#include "ported20.h"
#include "ported27.h"
#include "ported28.h"
#include "ported29.h"
#include "ported36.h"
#include "ported43.h"
#include "ported44.h"
#include "ported53.h"
#include "ported54.h"
#include "ported56.h"
#include "ported59.h"
#include "ported61.h"
#include "ported62.h"
#include "ported65.h"
#include "ported72.h"
#include "ported76.h"
#include "ported79.h"
#include "ported81.h"
#include "ported42.h"
#include "ported94.h"
#include "ported95.h"
#include "ported96.h"
#include "ported97.h"
#include "ported98.h"
#include "ported6.h"
#include "ported7.h"
#include "ported8.h"
#include "ported21.h"
#include "ported24.h"
#include "ported41.h"
#include "ported46.h"
#include "ported55.h"
#include "ported58.h"
#include "ported68.h"
#include "ported70.h"
#include "ported73.h"
#include "ported77.h"
#include "ported78.h"
#include "ported80.h"
#include "ported26.h"
#include "globalsets.h"
#include "uihandlers.h"
#include "smallfuncs2.h"
#include "ported17.h"
#include "ported14.h"
#include "unported.h"
#include <string.h>

#ifndef RE_HOOK_BUILD
p99_cars_t P99_Cars;
/* .data 00560328 (Game.exe): по передаче — порог вниз (назад), порог вниз (вперёд), порог вверх, множитель (вперёд), множитель (назад) */
#pragma push_macro("P99_GearTab") /*gvi*/
#undef P99_GearTab /*gvi*/
const p99_gear_t P99_GearTab = P99_GEAR_INIT;
#pragma pop_macro("P99_GearTab") /*gvi*/
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P99_D17ECC")
#undef P99_D17ECC
#pragma push_macro("P99_D17ECC") /*gvi*/
#undef P99_D17ECC /*gvi*/
p99_b8_t P99_D17ECC;
#pragma pop_macro("P99_D17ECC") /*gvi*/
#pragma pop_macro("P99_D17ECC")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P99_MrkA")
#undef P99_MrkA
#pragma push_macro("P99_MrkA") /*gvi*/
#undef P99_MrkA /*gvi*/
int32_t P99_MrkA;
#pragma pop_macro("P99_MrkA") /*gvi*/
#pragma pop_macro("P99_MrkA")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P99_MrkB")
#undef P99_MrkB
#pragma push_macro("P99_MrkB") /*gvi*/
#undef P99_MrkB /*gvi*/
int32_t P99_MrkB;
#pragma pop_macro("P99_MrkB") /*gvi*/
#pragma pop_macro("P99_MrkB")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P99_Mrk2660")
#undef P99_Mrk2660
#pragma push_macro("P99_Mrk2660") /*gvi*/
#undef P99_Mrk2660 /*gvi*/
int32_t P99_Mrk2660;
#pragma pop_macro("P99_Mrk2660") /*gvi*/
#pragma pop_macro("P99_Mrk2660")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P99_Mrk2664")
#undef P99_Mrk2664
#pragma push_macro("P99_Mrk2664") /*gvi*/
#undef P99_Mrk2664 /*gvi*/
int32_t P99_Mrk2664;
#pragma pop_macro("P99_Mrk2664") /*gvi*/
#pragma pop_macro("P99_Mrk2664")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P99_Mrk270C")
#undef P99_Mrk270C
#pragma push_macro("P99_Mrk270C") /*gvi*/
#undef P99_Mrk270C /*gvi*/
int32_t P99_Mrk270C;
#pragma pop_macro("P99_Mrk270C") /*gvi*/
#pragma pop_macro("P99_Mrk270C")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P99_Mrk2710")
#undef P99_Mrk2710
#pragma push_macro("P99_Mrk2710") /*gvi*/
#undef P99_Mrk2710 /*gvi*/
int32_t P99_Mrk2710;
#pragma pop_macro("P99_Mrk2710") /*gvi*/
#pragma pop_macro("P99_Mrk2710")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P99_Mrk2750")
#undef P99_Mrk2750
#pragma push_macro("P99_Mrk2750") /*gvi*/
#undef P99_Mrk2750 /*gvi*/
int32_t P99_Mrk2750;
#pragma pop_macro("P99_Mrk2750") /*gvi*/
#pragma pop_macro("P99_Mrk2750")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P99_Mrk2760")
#undef P99_Mrk2760
#pragma push_macro("P99_Mrk2760") /*gvi*/
#undef P99_Mrk2760 /*gvi*/
float P99_Mrk2760;
#pragma pop_macro("P99_Mrk2760") /*gvi*/
#pragma pop_macro("P99_Mrk2760")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P99_Mrk2764")
#undef P99_Mrk2764
#pragma push_macro("P99_Mrk2764") /*gvi*/
#undef P99_Mrk2764 /*gvi*/
float P99_Mrk2764;
#pragma pop_macro("P99_Mrk2764") /*gvi*/
#pragma pop_macro("P99_Mrk2764")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P99_Mrk2768")
#undef P99_Mrk2768
#pragma push_macro("P99_Mrk2768") /*gvi*/
#undef P99_Mrk2768 /*gvi*/
float P99_Mrk2768;
#pragma pop_macro("P99_Mrk2768") /*gvi*/
#pragma pop_macro("P99_Mrk2768")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P99_Vis")
#undef P99_Vis
#pragma push_macro("P99_Vis") /*gvi*/
#undef P99_Vis /*gvi*/
p99_vis_t P99_Vis;
#pragma pop_macro("P99_Vis") /*gvi*/
#pragma pop_macro("P99_Vis")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P99_RoadPick")
#undef P99_RoadPick
#pragma push_macro("P99_RoadPick") /*gvi*/
#undef P99_RoadPick /*gvi*/
int16_t P99_RoadPick;
#pragma pop_macro("P99_RoadPick") /*gvi*/
#pragma pop_macro("P99_RoadPick")
#endif

static int32_t rd32(const void *p) { int32_t v; memcpy(&v, p, 4); return v; }
static void wr32(void *p, int32_t v) { memcpy(p, &v, 4); }
static int16_t rd16s(const void *p) { int16_t v; memcpy(&v, p, 2); return v; }
static int32_t iabs(int32_t v) { return v < 0 ? -v : v; }
static int32_t fround(float v) { return (int32_t)lrintf(v); }                   /* fistp */
#define CAR(i) (&P99_Cars[(i)])

void P99_InitConsts(void) { }

/* ---- 00506a07: точки мира (int x, y, z, —) → координаты радара (x, —, z), поворот на курс машины S_00D11878 ---- */
void P99_RadarXform(const int32_t *src, int32_t *dst, int32_t n) {
  uint32_t a = (uint32_t)(-CAR(S_00D11878)->heading) & 0xfff;
  float s = P43_Sin[a], c = P43_Sin[a + 0x400];
  if (MenuOptBDFA54 != 0) { s = P43_Sin[0]; c = P43_Sin[0x400]; }
  while (n-- != 0) {
    float x = (float)(src[0] / 0x5dc);
    float z = (float)(-src[2] / 0x5dc);
    dst[0] = (int32_t)(x * c + z * -s);
    dst[2] = (int32_t)(x * s + z * c);
    dst[0] = (int32_t)((float)dst[0] * P94_RadarK + P56_F573FA0);
    dst[2] = (int32_t)((float)dst[2] * P94_RadarK + P56_F573FA4);
    src += 4; dst += 4;
  }
}

/* ---- 004d6ae7: коробка передач машины car — передача (+0x142) по оборотам (+0x10c / 2048), вернуть множитель × обороты ---- */
int32_t P99_GearBox(int32_t car) {
  p99_car_t *c = CAR(car);
  int32_t gear = c->gear;
  int32_t dir = c->ff8, rev = c->f10c, r;
  if (rev < 1) {
    r = -rev / 0x800;
    gear = 0;
  } else {
    r = rev / 0x800;
    if (gear < 0) gear = 0;
    if (gear > 3) gear = 3;
    int32_t prev;
    do {
      prev = gear;
      int32_t lo = dir < 1 ? P99_GearTab[gear][0] : P99_GearTab[gear][1];
      if (r < lo) gear--;
      if (P99_GearTab[gear][2] < r) gear++;
    } while (prev != gear);
  }
  c->gear = (uint8_t)gear;
  return (dir == 0 ? P99_GearTab[gear][4] : P99_GearTab[gear][3]) * r;
}

/* ---- 004c3427: камера режиссёра — дистанция до машины cam[4] (тип 0 — по cam[3]) ---- */
void P99_CamCheckDist(int32_t *cam) {
  if (P29_Mode == 0) return;
  if (cam[4] == -1) cam[4] = 0;
  int32_t d;
  if (cam[0] == 0) d = cam[3] * cam[3];
  else {
    if (cam[0] == 2) return;
    const p99_car_t *c = CAR(cam[4]);
    int32_t dx = cam[0x13] - c->pos[0], dz = cam[0x15] - c->pos[2];
    d = dx * dx + dz * dz;
  }
  if (d < 0x35a4e901) {
    if (d < 10000 && cam[0] == 0) {
      cam[0] = 2;
      P61_CamPrepare((uint8_t *)cam);
      DIRECTOR_CAMERA *f = FindCameraForFrame(DirectorUnk6C);
      AddDirectorCamera((DIRECTOR_CAMERA *)cam, f == NULL ? DirectorUnk6C : f->id);
    }
  } else {
    cam[4] = 0; cam[0] = 0; cam[6] = 0x500; cam[0x1c] = -0x100;
    AddDirectorCamera((DIRECTOR_CAMERA *)cam, DirectorUnk6C);
  }
}

/* ---- 004c5e08: камера режиссёра — игрок ушёл далеко / машина трафика пропала ---- */
int32_t P99_CamCheckPlayer(int32_t *cam) {
  if (cam[0] == 0) return 0;
  if (cam[0] == 2) {
    if (cam[4] == 0) return 0;
    if (TrafficRecs[(cam[4] - 1) * 0x54 + 1] == 0) { cam[4] = 0; cam[0x14] = -300; return 1; }
  }
  const p99_car_t *p = P36_PadMode == 3 ? CAR(0x41) : CAR(0);
  int32_t dx = iabs(p->pos[0] - cam[0x13]);
  int32_t dz = iabs(p->pos[2] - cam[0x15]);
  int32_t d = dx < dz ? dz + dx / 2 : dx + dz / 2;
  if (d < 0x88b9) {
    if (P95_SlotAt(cam[0x13], cam[0x15]) != 0) return 0;
    cam[4] = 0; cam[0] = 2;
    return 1;
  }
  cam[4] = 0; cam[0] = 0; cam[0x14] = -300;
  return 1;
}

/* ---- 004d2b5d: видит ли коп view игрока (вблизи — P56_CopsA, в секторе — P56_CopsB) ---- */
int32_t P99_CopsNear(const int16_t *view, uint8_t *car) {
  int32_t r0 = view[0] >> 4, r1 = view[1] >> 4;
  if (UiVar00B87E38 == 0x15a || UiVar00B87E38 == 0x15b || UiVar00B87E38 == 0x1be || UiVar00B87E38 == 0x1bf)
    return P97_CopsSee(view, car);
  const uint8_t *o = (const uint8_t *)re_rd_ptr(car + 0xcd0);
  if (o == NULL) return 0;                                   /* native: связь не заполнена */
  int32_t dx = (CAR(0)->pos2[0] - rd32(o + 0x18)) >> 4;
  int32_t dz = (CAR(0)->pos2[2] - rd32(o + 0x20)) >> 4;
  int32_t d2 = dx * dx + dz * dz;
  if (d2 < r0 * r0) { P56_CopsA = 1; return 1; }
  int32_t a = P44_Atan2(dx, dz);
  int32_t df = iabs((int32_t)(((uint32_t)(rd32(car + 0xc) - a) + 0x800u) & 0xfff) - 0x800);
  if (df < view[2] / 2 && d2 < r1 * r1) { P56_CopsB = 1; return 1; }
  return 0;
}

/* ---- 0051b7a3: узел дороги под машиной car (по направлению движения) или -1 ---- */
int32_t P99_RoadAtCar(uint32_t car) {
  const p99_car_t *c = CAR(car & 0xff);
  uint32_t dir = (uint8_t)Round1024(c->heading);
  int32_t x = (c->pos[0] + 0x2ee + P62_MapC64) / 0x5dc;
  int32_t z = (P62_Map2C40 - (c->pos[2] - 0x2ee)) / 0x5dc;
  if (x < 0 || P62_MapW <= x || z < 0 || P62_MapH <= z) return -1;
  int32_t n = P62_MapN;
  if (n == 0) return -1;                                     /* оригинал упал бы на делении */
  const int16_t *t = (const int16_t *)P54_RoadA[(x / n & 1) + ((P72_Rows - 1 - z / n) & 1) * 2];
  if (t == NULL) return -1;                                  /* native: тайл не загружен */
  int16_t s = t[(z - z / n * n) * n + (x - x / n * n)];
  if (s == -1 || (s & 0xc000) != 0) return -1;
  static const uint8_t k_dir[16] = { 2, 3, 0, 1, 0, 1, 3, 7, 0xf, 0x1f, 0x3f, 0x7f, 0xff, 0, 0, 0 };   /* .data 00575e30 */
  uint32_t k = dir < 16 ? k_dir[dir] : 0;                    /* Round1024 даёт 0..4 */
  int16_t a = rd16s(&P11_00bf1c40[2 + s * 0x42]);
  if (rd16s(&P11_00c1ed80[0xa + a * 0x2c + k * 8]) == s) return a;
  return rd16s(&P11_00bf1c40[4 + s * 0x42]);
}

/* ---- 0049c99c: свободная камера — сдвиг клавишами, позиция от игрока ---- */
#ifdef RE_HOOK_BUILD
#  define P99_KEY(a) (*(uint8_t *)(uintptr_t)(a))
#else
#  define P99_KEY(a) KeyState[(a) - 0x00d04b00]
#endif
void P99_FreeCamMove(void) {
  if (P99_KEY(0x00d04bcb) != 0) P62_I137388 -= 0x200;
  else if (P99_KEY(0x00d04bcd) != 0) P62_I137388 += 0x200;
  if (P36_Pad1 != 0) P62_I13738C -= 0x200;
  else if (P36_Pad0 != 0) P62_I13738C += 0x200;
  if (P99_KEY(0x00d04bc8) != 0) P62_I137390 += 0x200;
  else if (P99_KEY(0x00d04bd0) != 0) P62_I137390 -= 0x200;
  P44_CamX = (float)CAR(0)->pos[0] + (float)P62_I137388;
  P44_CamY = -(float)CAR(0)->pos[1] - (float)P62_I13738C;
  P44_CamZ = (float)CAR(0)->pos[2] + (float)P62_I137390;
  P59_AngA = 0x400; P59_AngB = 0; P59_AngC = 0;
  InitXform_005263FE();
}

/* ---- 0049e47b: камера за игроком (матрица по углам машины, смещение (0, 60, 350)) ---- */
void P99_CamBehind(void) {
  const p99_car_t *c = CAR(0);
  P59_AngA = (uint16_t)(c->ang[0] & 0xfff);
  P59_AngB = (uint16_t)(((uint16_t)P61_Heading - (uint16_t)c->ang[1]) & 0xfff);
  P59_AngC = (uint16_t)(c->ang[2] & 0xfff);
  static const float id[9] = { 1, 0, 0, 0, 1, 0, 0, 0, 1 };
  memcpy(P44_ViewMat, id, sizeof id);
  P44_RotZ(P44_ViewMat, P59_AngC);
  P44_RotX(P44_ViewMat, (int16_t)P59_AngA);
  P44_RotY(P44_ViewMat, (int16_t)P59_AngB);
  P44_Transpose(P44_ViewMat, P44_ViewMatT);
  P44_MatPtr = P44_ViewMat;
  float v[3] = { 0.0f, 60.0f, 350.0f };
  P44_Xform(v);
  P44_CamX = (float)c->pos[0] + v[0];
  P44_CamY = (float)-c->pos[1] + v[1];
  P44_CamZ = (float)c->pos[2] + v[2];
}

/* ---- 004e9427: сброс маркера/сферы и углов игрока ---- */
void P99_MarkerReset(void) {
  P98_MrkOff = 0;
  P96_InitSphere();
  P76_Angle = 0; P99_Mrk2664 = 0; P99_Mrk2660 = 900;
  P98_MrkSrc[0] = 20.0f; P98_MrkSrc[1] = 0.0f; P98_MrkSrc[2] = 300.0f;
  P99_Mrk2760 = 0; P99_Mrk2730 = 0; P99_Mrk2764 = 0; P99_Mrk2734 = 0; P99_Mrk2768 = 0; P99_Mrk2738 = 0; P99_Mrk2750 = 0;
  P99_MrkA = 0;
  P98_MrkModel = P20_FindNameNoCase("BOX");
  if (P98_MrkModel == -1) P98_MrkModel = 5;
  CAR(0)->ang[2] = 0; CAR(0)->ang[0] = 0;
  if (P15_State == 1) {
    P53_Var2634 = P20_FindNameValue("CHOP");
    P99_MrkB = P20_FindNameValue("ROT");
    P53_Var2640 = (uint32_t)P20_FindNameNoCase("CHOP");
    P99_Mrk26B8 = 0; P81_Span = 0; P99_Mrk26B0 = 0;
    P42_AngY = 0; P42_AngZ = 0; P81_Flag = 0; P99_Mrk2710 = 0; P99_Mrk270C = 0;
  }
}

/* ---- 004a1b2d: ближайшая машина трафика впереди игрока, развёрнутая к нему (флаг +0x15 записи) ---- */
int32_t P99_TrafficAhead(void) {
  float pp[3] = { (float)CAR(0)->pos[0], 0.0f, (float)CAR(0)->pos[2] };
  int32_t cx, cy;
  P76_CellFromPos(pp, P99_Vis, &cx, &cy);
  int32_t found = -1;
  for (int32_t i = 0; i <= 0x3f; i++) {
    uint8_t *r = &TrafficRecs[i * 0x54];
    if (r[0x15] != 0) return i;
    if (r[5] == 0 && r[0xc] != 1 && r[1] == 2 && found == -1 && Get138Entry148(i) == 0) {
      const p99_car_t *c = CAR(i + 1);
      float q[3] = { (float)c->pos[0], 0.0f, (float)c->pos[2] };
      if (P76_InBox(q, P99_Vis, cx, cy) == 0) {
        int32_t d = iabs((int32_t)(((uint32_t)(CAR(0)->heading - rd32(&c->heading)) + 0x800u) & 0xfff) - 0x800);
        if (0x3ff < d) {
          int32_t qz = fround(q[2]), qx = fround(q[0]);
          P11_00ba52d0 = qx;
          int32_t a = P44_Atan2(CAR(0)->pos[0] - qx, CAR(0)->pos[2] - qz);
          int32_t e = iabs((int32_t)(((uint32_t)(rd32(&c->heading) - a) + 0x800u) & 0xfff) - 0x800);
          if (e < 0x2c9) found = i;
        }
      }
    }
  }
  if (found != -1) TrafficRecs[found * 0x54 + 0x15] = 1;
  return found;
}

/* ---- 004a6e84: цель копа — точка 00c1cd20[P97_B2B0], если игрок далеко и мало копов её уже держат ---- */
int32_t P99_CopTarget(int32_t *cop) {
  if (P97_B2B0 != -1) {
    int32_t tx = rd32(&P11_00c1cd20[P97_B2B0 * 8]), tz = rd32(&P11_00c1cd20[P97_B2B0 * 8 + 4]);
    int32_t dx = iabs(tx - cop[0x319]), dz = iabs(-tz - cop[0x31b]);
    int32_t d = dx < dz ? dz + dx / 2 : dx + dz / 2;
    if (d < 0x9e34) {
      int32_t px = iabs(CAR(0)->pos[0] - cop[0x319]), pz = iabs(CAR(0)->pos[2] - cop[0x31b]);
      int32_t pd = px < pz ? pz + px / 2 : px + pz / 2;
      if (45000 < pd) {
        int32_t act = 0, held = 0;
        const uint32_t *o = P12_0112da00;
        for (int32_t k = 0; k < 8; k++, o += 0x336) {
          if (o[0x32d] != 0) { act++; if ((int32_t)o[0] != cop[0] && o[0x332] != 0) held++; }
        }
        if (held < act >> 1) {
          cop[0x12] = tx; cop[0x13] = -tz; cop[0x332] = 1;
          return 1;
        }
      }
    }
  }
  cop[0x332] = 0;
  return 0;
}

/* ---- 004c0218: целая модель машины car (-1 — игрок): вершины/нормали/операции из модели P28_CarClean[тип] ---- */
static const uint8_t *p99_model(uint32_t ref) { return ref != 0 ? (const uint8_t *)P79_PTR(ref) : NULL; }
void P99_CarModelClean(int32_t car) {
  int32_t slot = car + 1;
  uint32_t kind = slot == 0 ? 0u : TrafficRecs[car * 0x54 + 0xc];
  if (P98_CarKind[slot] != kind || kind == 0) {
    P98_CarKind[slot] = (uint8_t)kind;
    const uint8_t *m = p99_model(P28_CarClean[kind]);
    if (m == NULL) return;                                   /* native: модели не загружены (в оригинале — сбой) */
    P44_Copy4(&P98_CarOpsA[slot * 0x1040], P79_PTR(rd32(m + 0x20)), (uint32_t)*(const uint16_t *)(m + 0x14) << 4);
    P44_Copy4(&P98_CarOpsB[slot * 0x1700], P79_PTR(rd32(m + 0x24)), (uint32_t)*(const uint16_t *)(m + 0x16) << 4);
    if (slot != 0) P44_Copy4(&P98_CarOpsC[slot * 0x9580], P79_PTR(rd32(m + 0x2c)), (uint32_t)P28_CarOpsSize[kind]);
    wr32(&P98_CarTimer[slot * 4], 0x32);
  }
}

/* ---- 004c1b6c: сброс вмятин игрока (car 0) или операций модели машины car ---- */
void P99_CarOpsReset(int32_t car) {
  if (car == 0) {
    const uint8_t *d = (const uint8_t *)re_ptr((uint32_t)P27_DentTex[0]);
    if (d == NULL) return;                                   /* native: текстуры вмятин не загружены */
    uint8_t t = d[8];
    CopyWords8000((uint32_t *)P65_Texs[t].p, (uint32_t *)D_00d17ec8);
    P12_Fn0048A46B(t, (int32_t)re_addr(D_00d17ec8));
    memset(P99_D17ECC, 0, sizeof P99_D17ECC);
  } else {
    uint32_t kind = TrafficRecs[(car - 1) * 0x54 + 0xc];
    const uint8_t *m = p99_model(P28_CarClean[kind]);
    if (m == NULL) return;
    P44_Copy4(&P98_CarOpsC[car * 0x9580], P79_PTR(rd32(m + 0x2c)), (uint32_t)P28_CarOpsSize[kind]);
  }
}

/* ===================== прочие (v1.44) ===================== */
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P99_CamKeys")
#undef P99_CamKeys
#pragma push_macro("P99_CamKeys") /*gvi*/
#undef P99_CamKeys /*gvi*/
p99_camkeys_t P99_CamKeys;
#pragma pop_macro("P99_CamKeys") /*gvi*/
#pragma pop_macro("P99_CamKeys")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P99_CamDelay")
#undef P99_CamDelay
#pragma push_macro("P99_CamDelay") /*gvi*/
#undef P99_CamDelay /*gvi*/
int32_t P99_CamDelay;
#pragma pop_macro("P99_CamDelay") /*gvi*/
#pragma pop_macro("P99_CamDelay")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P99_CamDone")
#undef P99_CamDone
#pragma push_macro("P99_CamDone") /*gvi*/
#undef P99_CamDone /*gvi*/
int32_t P99_CamDone;
#pragma pop_macro("P99_CamDone") /*gvi*/
#pragma pop_macro("P99_CamDone")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P99_CamOn")
#undef P99_CamOn
#pragma push_macro("P99_CamOn") /*gvi*/
#undef P99_CamOn /*gvi*/
int32_t P99_CamOn;
#pragma pop_macro("P99_CamOn") /*gvi*/
#pragma pop_macro("P99_CamOn")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P99_CamEnd")
#undef P99_CamEnd
#pragma push_macro("P99_CamEnd") /*gvi*/
#undef P99_CamEnd /*gvi*/
uint8_t P99_CamEnd;
#pragma pop_macro("P99_CamEnd") /*gvi*/
#pragma pop_macro("P99_CamEnd")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P99_CamIdx")
#undef P99_CamIdx
#pragma push_macro("P99_CamIdx") /*gvi*/
#undef P99_CamIdx /*gvi*/
int32_t P99_CamIdx;
#pragma pop_macro("P99_CamIdx") /*gvi*/
#pragma pop_macro("P99_CamIdx")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P99_CamStep")
#undef P99_CamStep
#pragma push_macro("P99_CamStep") /*gvi*/
#undef P99_CamStep /*gvi*/
int32_t P99_CamStep;
#pragma pop_macro("P99_CamStep") /*gvi*/
#pragma pop_macro("P99_CamStep")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P99_CamT")
#undef P99_CamT
#pragma push_macro("P99_CamT") /*gvi*/
#undef P99_CamT /*gvi*/
int32_t P99_CamT;
#pragma pop_macro("P99_CamT") /*gvi*/
#pragma pop_macro("P99_CamT")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P99_CamMax")
#undef P99_CamMax
#pragma push_macro("P99_CamMax") /*gvi*/
#undef P99_CamMax /*gvi*/
int32_t P99_CamMax;
#pragma pop_macro("P99_CamMax") /*gvi*/
#pragma pop_macro("P99_CamMax")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P99_CamLast")
#undef P99_CamLast
#pragma push_macro("P99_CamLast") /*gvi*/
#undef P99_CamLast /*gvi*/
int32_t P99_CamLast;
#pragma pop_macro("P99_CamLast") /*gvi*/
#pragma pop_macro("P99_CamLast")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P99_CamFade")
#undef P99_CamFade
#pragma push_macro("P99_CamFade") /*gvi*/
#undef P99_CamFade /*gvi*/
int32_t P99_CamFade;
#pragma pop_macro("P99_CamFade") /*gvi*/
#pragma pop_macro("P99_CamFade")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P99_CamB0")
#undef P99_CamB0
#pragma push_macro("P99_CamB0") /*gvi*/
#undef P99_CamB0 /*gvi*/
int32_t P99_CamB0;
#pragma pop_macro("P99_CamB0") /*gvi*/
#pragma pop_macro("P99_CamB0")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P99_CamSpd")
#undef P99_CamSpd
#pragma push_macro("P99_CamSpd") /*gvi*/
#undef P99_CamSpd /*gvi*/
int32_t P99_CamSpd;
#pragma pop_macro("P99_CamSpd") /*gvi*/
#pragma pop_macro("P99_CamSpd")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P99_MsgWin")
#undef P99_MsgWin
#pragma push_macro("P99_MsgWin") /*gvi*/
#undef P99_MsgWin /*gvi*/
int32_t P99_MsgWin;
#pragma pop_macro("P99_MsgWin") /*gvi*/
#pragma pop_macro("P99_MsgWin")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P99_MsgLose")
#undef P99_MsgLose
#pragma push_macro("P99_MsgLose") /*gvi*/
#undef P99_MsgLose /*gvi*/
int32_t P99_MsgLose;
#pragma pop_macro("P99_MsgLose") /*gvi*/
#pragma pop_macro("P99_MsgLose")
#endif
GAME_VAR_DEF(p99_list_t, P99_ScrNames, 0x00c81698)
GAME_VAR_DEF(void *, P99_C80880, 0x00c80880)
GAME_VAR_DEF(uint8_t *, P99_EvObj, 0x01134128)
GAME_VAR_DEF(uint8_t *, P99_EvA, 0x01134244)
GAME_VAR_DEF(uint8_t *, P99_EvB, 0x01134260)
GAME_VAR_DEF(uint8_t *, P99_EvC, 0x0113411c)
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P99_EvId")
#undef P99_EvId
#pragma push_macro("P99_EvId") /*gvi*/
#undef P99_EvId /*gvi*/
int32_t P99_EvId;
#pragma pop_macro("P99_EvId") /*gvi*/
#pragma pop_macro("P99_EvId")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P99_MenuText0")
#undef P99_MenuText0
#pragma push_macro("P99_MenuText0") /*gvi*/
#undef P99_MenuText0 /*gvi*/
int32_t P99_MenuText0;
#pragma pop_macro("P99_MenuText0") /*gvi*/
#pragma pop_macro("P99_MenuText0")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P99_MenuText1")
#undef P99_MenuText1
#pragma push_macro("P99_MenuText1") /*gvi*/
#undef P99_MenuText1 /*gvi*/
int32_t P99_MenuText1;
#pragma pop_macro("P99_MenuText1") /*gvi*/
#pragma pop_macro("P99_MenuText1")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P99_Rgb0")
#undef P99_Rgb0
#pragma push_macro("P99_Rgb0") /*gvi*/
#undef P99_Rgb0 /*gvi*/
p99_rgb_t P99_Rgb0;
#pragma pop_macro("P99_Rgb0") /*gvi*/
#pragma pop_macro("P99_Rgb0")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P99_Rgb1")
#undef P99_Rgb1
#pragma push_macro("P99_Rgb1") /*gvi*/
#undef P99_Rgb1 /*gvi*/
p99_rgb_t P99_Rgb1;
#pragma pop_macro("P99_Rgb1") /*gvi*/
#pragma pop_macro("P99_Rgb1")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P99_Rgb2")
#undef P99_Rgb2
#pragma push_macro("P99_Rgb2") /*gvi*/
#undef P99_Rgb2 /*gvi*/
p99_rgb_t P99_Rgb2;
#pragma pop_macro("P99_Rgb2") /*gvi*/
#pragma pop_macro("P99_Rgb2")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P99_Rgb3")
#undef P99_Rgb3
#pragma push_macro("P99_Rgb3") /*gvi*/
#undef P99_Rgb3 /*gvi*/
p99_rgb_t P99_Rgb3;
#pragma pop_macro("P99_Rgb3") /*gvi*/
#pragma pop_macro("P99_Rgb3")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P99_Rgb4")
#undef P99_Rgb4
#pragma push_macro("P99_Rgb4") /*gvi*/
#undef P99_Rgb4 /*gvi*/
p99_rgb_t P99_Rgb4;
#pragma pop_macro("P99_Rgb4") /*gvi*/
#pragma pop_macro("P99_Rgb4")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P99_Rgb5")
#undef P99_Rgb5
#pragma push_macro("P99_Rgb5") /*gvi*/
#undef P99_Rgb5 /*gvi*/
p99_rgb_t P99_Rgb5;
#pragma pop_macro("P99_Rgb5") /*gvi*/
#pragma pop_macro("P99_Rgb5")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P99_Rgb6")
#undef P99_Rgb6
#pragma push_macro("P99_Rgb6") /*gvi*/
#undef P99_Rgb6 /*gvi*/
p99_rgb_t P99_Rgb6;
#pragma pop_macro("P99_Rgb6") /*gvi*/
#pragma pop_macro("P99_Rgb6")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P99_Rgb7")
#undef P99_Rgb7
#pragma push_macro("P99_Rgb7") /*gvi*/
#undef P99_Rgb7 /*gvi*/
p99_rgb_t P99_Rgb7;
#pragma pop_macro("P99_Rgb7") /*gvi*/
#pragma pop_macro("P99_Rgb7")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P99_Rgb8")
#undef P99_Rgb8
#pragma push_macro("P99_Rgb8") /*gvi*/
#undef P99_Rgb8 /*gvi*/
p99_rgb_t P99_Rgb8;
#pragma pop_macro("P99_Rgb8") /*gvi*/
#pragma pop_macro("P99_Rgb8")
#endif

static float rdf(const void *p) { float v; memcpy(&v, p, 4); return v; }
static void wrf(void *p, float v) { memcpy(p, &v, 4); }
static uint16_t rd16(const void *p) { uint16_t v; memcpy(&v, p, 2); return v; }
static void wr16(void *p, uint16_t v) { memcpy(p, &v, 2); }

/* ---- 004a2e14: кресло в точке (x, y) клетки сетки P58_Grid — занять (флаг 1 записи, слот в A_01134540) ---- */
int32_t P99_ChairHit(float x, float y) {
  int32_t r = 0;
  if (P58_Grid == NULL) return 0;
  P11_00ba52d0 = fround(x); int32_t ix = P11_00ba52d0;
  P11_00ba52d0 = fround(y); int32_t iy = P11_00ba52d0;
  if (P80_Cell == 0 || P21_GridDiv == 0) return 0;          /* оригинал упал бы на делении */
  int32_t cell = (iy / P80_Cell + P80_GridH / 2) * P21_GridDiv + ix / P80_Cell + P21_GridDiv / 2;
  const p58_cell_t *c = (const p58_cell_t *)P58_Grid[cell];
  if (c == NULL) return 0;
  int32_t *e = (int32_t *)c->items;
  for (int32_t k = 0; k < c->b; k++, e += 5) {
    if (e[0] == ix && e[1] == iy) {
      int32_t s = PoolAlloc004A2C12();
      if (s != -1) {
        uint8_t *u = &A_01134540[s * 24];                    /* 01134544 + s·0x18: ячейка, номер, x, y */
        wr32(u + 4, cell); wr32(u + 8, k); wr32(u + 12, e[0]); wr32(u + 16, e[1]);
        e[2] |= 1;
        r = 1;
      }
    }
  }
  return r;
}

/* ---- 00496eb4: перекрёсток node заблокирован светофором для выбранного узла P99_RoadPick ---- */
static int16_t p99_link(int32_t n, int32_t k) { return rd16s(&P11_00c1ed80[0xa + n * 0x2c + k * 8]); }
int32_t P99_JunctionBlock(int32_t node) {
  if (P99_RoadPick == -1 || P99_RoadPick == node) return 0;
  int16_t b = rd16s(&P11_00bf1c40[4 + node * 0x42]);
  int16_t a = rd16s(&P11_00bf1c40[2 + node * 0x42]);
  int32_t j = -1, k;
  for (k = 0; k < 4; k++) if (p99_link(a, k) == P99_RoadPick) { j = a; break; }
  if (j == -1) {
    if (b == -1) return 0;
    for (k = 0; k < 4; k++) if (p99_link(b, k) == P99_RoadPick) { j = b; break; }
    if (j == -1) return 0;
  }
  if (P11_00c1ed80[2 + j * 0x2c] == 1) {
    int32_t m = 0;
    while (m < 4 && p99_link(j, m) != (int16_t)node) m++;
    if ((k == 0 && m == 3) || (k == 1 && m == 0) || (k == 2 && m == 1) || (k == 3 && m == 2)) return 0;
    if ((k & 1) == 0) { if (G00C29D80 == 1 && G00C4BDC4 < 0x127) return 1; }
    else if (G00C29D81 == 1 && G00C4BDC4 < 0x127) return 1;
  }
  return 0;
}

/* ---- 004f4d3c: сообщения скрипта (WINDOWMESSAGE / LOSETAILMESSAGE / MAXSPEEDMESSAGE) по флагам объектов P58_Objs ---- */
static int32_t p99_msg(const char *name) {
  int32_t v = P42_FindVar(name);
  if (-1 < v && P42_Vars[v].addr != 0) { DrawTextLine004FBBC5((int32_t)P42_Vars[v].addr); return 1; }
  return 0;
}
int32_t P99_ScriptMsgs(void) {
  if (G6_00B87EA0 != 0 || P62_HudOff2 != 0) return 0;
  for (int32_t i = 0; i < 10; i++) {
    uint8_t *o = P58_Objs[i];
    uint32_t f = (uint32_t)rd32(o + 0x10);
    if ((f & 1) == 0) continue;
    if ((f & 2) != 0) {
      int32_t v = P42_FindVar("WINDOWMESSAGE");
      if (P99_MsgWin != -1) MenuClick004F8ACC(P99_MsgWin + 0xf000);
      P99_MsgWin = -1;
      if (-1 < v && P42_Vars[v].addr != 0) { DrawTextLine004FBBC5((int32_t)P42_Vars[v].addr); return 1; }
    }
    f = (uint32_t)rd32(o + 0x10);
    if ((f & 4) != 0 && (f & 0x400) == 0) {
      int32_t v = P42_FindVar("LOSETAILMESSAGE");
      wr32(o + 0x10, (int32_t)(rd32(o + 0x10) & 0xfffffffbu));
      if (P99_MsgLose != -1) MenuClick004F8ACC(P99_MsgLose + 0xf000);
      P99_MsgLose = -1;
      if (-1 < v && P42_Vars[v].addr != 0) { DrawTextLine004FBBC5((int32_t)P42_Vars[v].addr); return 1; }
    }
    if ((rd32(o + 0x10) & 0x200) != 0 && p99_msg("MAXSPEEDMESSAGE")) return 1;
  }
  return 0;
}

/* ---- 00412d7d: затемнить (on = 0 — белые, иначе серые 0x40) пункты меню и подписи ---- */
void P99_MenuDim(int32_t on) {
  Ui0040C867();
  uint8_t v = on == 0 ? 0xff : 0x40;
  P99_MenuText0 = on == 0 ? 0 : (int32_t)P97_StrAddr[3];
  P99_MenuText1 = on == 0 ? 0 : (int32_t)P97_StrAddr[4];
  memset(P99_Rgb0, v, 3); memset(P99_Rgb1, v, 3); memset(P99_Rgb2, v, 3); memset(P99_Rgb3, v, 3); memset(P99_Rgb4, v, 3);
  memset(P99_Rgb5, v, 3); memset(P99_Rgb6, v, 3); memset(P99_Rgb7, v, 3); memset(P99_Rgb8, v, 3);
}

/* ---- 00514c9f: частица p окажется перед плоскостью (+0x94/+0x9c, нормаль +0x64/+0x6c) через n шагов пути ---- */
int32_t P99_PartAhead(uint8_t *p, int32_t n) {
  if ((rd32(p + 0xc) & 0x80) != 0) return 0;
  int32_t k = rd32(p + 0x34);
  int16_t a = rd16s(p + 0x5e);
  int32_t ai = a;                                            /* movsx: индекс со знаком */
#ifndef RE_HOOK_BUILD
  if (ai < 0) ai &= 0xfff;                                   /* native: не читать до начала таблицы */
#endif
  P11_00ba52d0 = fround(P43_Sin[ai]); int32_t s = P11_00ba52d0;          /* оригинал округляет sin/cos до целых */
  P11_00ba52d0 = fround(P43_Sin[ai + 0x400]); int32_t c = P11_00ba52d0;
  float x = rdf(p + 0x84), z = rdf(p + 0x8c);
  int32_t steps = n * rd32(p + 0x30);
  int32_t w = rd32(p + 0x1c);
  const uint8_t *path = (w >= 1 && w <= 4) ? (const uint8_t *)P54_Tab4[w - 1] : NULL;   /* 00c81b7c[w] = 00c81b80[w-1] */
  while (steps != 0) {
    if (rd32(p + 0x2c) < k) k %= rd32(p + 0x2c);
    if (path == NULL) return 0;                              /* native: путь не загружен */
    const uint8_t *v = path + (P12_00c821a0 * 0x14 + 0x10) * k;
    x = (float)s * rdf(v + 8) + (float)c * rdf(v) + x;
    z = ((float)c * rdf(v + 8) - (float)s * rdf(v)) + z;
    k++; steps--;
  }
  return ((rdf(p + 0x9c) - z) * rdf(p + 0x6c) + (rdf(p + 0x94) - x) * rdf(p + 0x64) < P8_00546024) ? 1 : 0;
}

/* ---- 00420854: колбэк перечисления форматов текстур DirectDraw (stdcall ret 8): DDPIXELFORMAT fmt (8 dword) → ctx ---- */
int32_t P99_DDEnumFmt(const uint32_t *fmt, uint8_t *ctx) {
  if (ctx == NULL) return 1;
  uint32_t fl = (uint32_t)rd32(ctx + 0x58c);
  if ((fmt[1] & 0x40) == 0 || (fl & 0x20) != 0) {
    if ((fmt[1] & 0x20) == 0 || (fl & 0x10) != 0) {
      if (fmt[1] == 0x400 && (fl & 0x40) == 0) { wr32(ctx + 0x58c, (int32_t)(fl | 0x44)); memcpy(ctx + 0x568, fmt, 0x20); }
    } else { wr32(ctx + 0x58c, (int32_t)(fl | 0x11)); memcpy(ctx + 0x548, fmt, 0x20); }
  } else if (fmt[3] == 0x10) {
    wr32(ctx + 0x58c, (int32_t)(fl | 2));
    memcpy(ctx + 0x528, fmt, 0x20);
    P24_RShiftR = 8 - MaskShift_00421C1D(fmt[4]);
    P24_GShiftR = 8 - MaskShift_00421C1D(fmt[5]);
    P24_BShiftR = 8 - MaskShift_00421C1D(fmt[6]);
    if (fmt[7] != 0) P55_A4219C = 8 - MaskShift_00421C1D(fmt[7]);
    if (P24_RShiftR == 5 && P24_GShiftR == 5 && P24_BShiftR == 5 && P55_A4219C == 1)
      wr32(ctx + 0x58c, rd32(ctx + 0x58c) | 0x20);
  }
  return 1;
}

/* ---- 004f638d: освободить данные скрипта миссии (список, строки, строковые переменные типа 1) ---- */
void P99_ScriptFree(void) {
  if (P77_List != NULL) {
    for (int32_t i = 0; i < P77_ListN; i++) { if (P77_List[i] != NULL) P98_DebugFree(P77_List[i]); P77_List[i] = NULL; }
    P98_DebugFree(P77_List);
    P77_List = NULL;
  }
  P58_FreeLists();
  P58_FreeNames((p58_list_t *)&P99_ScrNames);
  if (P65_Line != NULL) { P98_DebugFree(P65_Line); P65_Line = NULL; }
  for (int32_t i = 0; i < (int32_t)(sizeof P42_Vars / sizeof P42_Vars[0]) && P42_Vars[i].type != 0x7f; i++) {
    if (P42_Vars[i].type == 1) {
      if (P42_Vars[i].addr != 0) P98_DebugFree(re_ptr(P42_Vars[i].addr));
      P42_Vars[i].addr = 0;
    }
  }
  if (G6_00C80C50 != NULL) P98_DebugFree(G6_00C80C50);
  G6_00C80C50 = NULL; P77_List = NULL; P65_Line = NULL; P77_ListN = 0;
}

/* ---- 004d3444: освободить буферы карты уровня ---- */
#define P99_FREE(v) do { if ((v) != NULL) { P98_DebugFree((void *)(v)); (v) = NULL; } } while (0)
void P99_MapFree(void) {
  FreeMapBuffer400000();
  FreeMapBufs004ECE1A();
  P58_FreeList();
  FreeMapBuffer300000();
  P54_FreeRoadbits();
  P99_FREE(P46_MapBufB);
  P99_FREE(P54_MapAPtr);
#ifdef RE_HOOK_BUILD
  if (P41_Arena != 0) { P98_DebugFree(re_ptr(P41_Arena)); P41_Arena = 0; }
#else
  P41_Arena = 0;                                             /* native: буфер страниц статический (P41_RamPtr) */
#endif
  P99_FREE(P54_MapBPtr);
  P99_FREE(P62_MapBuf);
  P99_FREE(P46_MapBufA);
  P99_FREE(P20_Names);
  P99_FREE(P78_VertsA);
  P99_FREE(P78_VertsB);
  P99_FREE(P99_C80880);
}

/* ---- 0049ea37: шаг сценария камеры (ключи P99_CamKeys, сплайн P98_CamSpline) ---- */
static void p99_cam_end(void) {
  P99_CamOn = 0; P99_CamDone = 1;
  P61_V1C = (int32_t)((uint32_t)(CAR(0)->heading + P61_V18) & 0xfff);
  P99_CamSpd = P99_CamMax << 12;
}
void P99_CamScriptStep(void) {
  if (P99_CamDelay != 0) {
    P99_CamDelay--;
    if (P99_CamB0 != 0) P99_CamB0 -= 4;
    return;
  }
  if (P99_KEY(0x00d04b01) != 0 || (rd32(&P99_CamKeys[(P99_CamIdx + 2) * 0x34 + 0x28]) & 1) == 0) {
    p99_cam_end(); P99_CamEnd = 1;
    return;
  }
  while (P99_CamT == rd32(&P99_CamKeys[(P99_CamIdx + 1) * 0x34 + 0x2c])) {
    P99_CamIdx++;
    if ((rd32(&P99_CamKeys[(P99_CamIdx + 2) * 0x34 + 0x28]) & 1) == 0) { p99_cam_end(); return; }
  }
  P98_CamSpline(P99_CamT, &P99_CamKeys[P99_CamIdx * 0x34]);
  if (rd32(&P99_CamKeys[P99_CamLast * 0x34 + 0x2c]) < P99_CamT + 0x80) {
    P99_CamSpd += P99_CamStep;
    if (P99_CamMax * 0x1000 < P99_CamSpd) P99_CamSpd = P99_CamMax << 12;
  }
  P99_CamFade -= 2;
  if (P99_CamFade < 0) P99_CamFade = 0;
  P99_CamT++;
}

/* ---- 004f8862: строковая переменная скрипта (тип 1): копия s в куче, адрес — в поле +0x24 ---- */
void P99_VarSetStr(uint8_t *var, const char *s) {
  if (rd32(var + 0x20) != 1) return;
  size_t n = strlen(s);
  char *d = (char *)P98_DebugMalloc((int32_t)n + 1, "D:\\Driver\\Game\\MScript.c", 0xbc1);
  if (d == NULL) return;
  memcpy(d, s, n + 1);
  if (rd32(var + 0x24) != 0) { P98_DebugFree(re_rd_ptr(var + 0x24)); wr32(var + 0x24, 0); }
  re_wr_ptr(var + 0x24, d);
}

/* ---- 004a5338: дописать команду cmd с аргументами в буфер события ev (+0x4c длина, +0x50 адрес буфера) ---- */
#ifdef RE_HOOK_BUILD
#  define P99_CMDSZ(i)  (((const uint16_t *)(uintptr_t)0x00551b32)[i])
#  define P99_CMDFMT(i) ((const char *)(uintptr_t)((const uint32_t *)(uintptr_t)0x00551bb0)[i])
#  define P99_FMT_E  ((const char *)(uintptr_t)0x00552454)
#  define P99_FMT_14 ((const char *)(uintptr_t)0x00552458)
#  define P99_FMT_15 ((const char *)(uintptr_t)0x0055245c)
#else
static const uint16_t k_cmdsz[P99_CMD_N] = P99_CMDSZ_INIT;
static const char *const k_cmdfmt[P99_CMD_N] = P99_CMDFMT_INIT;
#  define P99_CMDSZ(i)  ((i) < P99_CMD_N ? k_cmdsz[i] : 0)
#  define P99_CMDFMT(i) ((i) < P99_CMD_N ? k_cmdfmt[i] : "")
#  define P99_FMT_E  P99_FMTE
#  define P99_FMT_14 P99_FMT14
#  define P99_FMT_15 P99_FMT15
#endif
void P99_CmdAppend(uint16_t cmd, uint8_t *ev) {
  uint32_t sz = P99_CMDSZ(cmd);
  uint8_t *w;
  if (rd32(ev + 0x50) == 0) {
    wr32(ev + 0x4c, (int32_t)(sz + 2));
    w = (uint8_t *)P98_DebugMalloc(rd32(ev + 0x4c), "D:\\Driver\\Game\\compiler.c", 0x4c3);
    if (w == NULL) P26_ErrorInLine("Not enough memory for\nnew command!");
    re_wr_ptr(ev + 0x50, w);
  } else {
    uint8_t *nb = (uint8_t *)P98_DebugMalloc(rd32(ev + 0x4c) + (int32_t)sz, "D:\\Driver\\Game\\compiler.c", 0x4cf);
    if (nb == NULL) P26_ErrorInLine("Not enough memory for\nnew command!");
    P44_Copy4(nb, re_rd_ptr(ev + 0x50), (uint32_t)rd32(ev + 0x4c));
    P98_DebugFree(re_rd_ptr(ev + 0x50));
    wr32(ev + 0x50, 0);
    re_wr_ptr(ev + 0x50, nb);
    w = nb - 2 + rd32(ev + 0x4c);
    wr32(ev + 0x4c, rd32(ev + 0x4c) + (int32_t)sz);
  }
  if (w == NULL) return;                                     /* в оригинале — запись по нулевому адресу */
  wr16(w, cmd);
  w += 2;
  if (cmd == 0xe) P68_ReadCamArgs(w, P99_FMT_E);
  else if (cmd == 0x14) P68_ReadCamArgs(w, P99_FMT_14);
  else if (cmd == 0x15) P68_ReadCamArgs(w, P99_FMT_15);
  else P68_ReadCamArgs(w, P99_CMDFMT(cmd));
  uint8_t *e = (uint8_t *)re_rd_ptr(ev + 0x50) - 2 + rd32(ev + 0x4c);
  e[0] = 0; e[1] = 0;
}

/* ---- 004a4340: новое событие (узел 0x24 + объект 0x60) в конец списка скрипта P15_ListHead ---- */
void P99_EventAdd(int32_t n) {
  uint8_t *ev = (uint8_t *)P98_DebugMalloc(0x24, "D:\\Driver\\Game\\compiler.c", 0x1cd);
  if (ev == NULL) { P26_ErrorInLine("Not enough memory for events!"); return; }
  memset(ev, 0, 0x24);
  uint8_t *last = P15_ListHead;
  if (last == NULL) { P98_DebugFree(ev); return; }          /* native: список пуст (оригинал упал бы) */
  while (rd32(last + 0x20) != 0) last = (uint8_t *)re_rd_ptr(last + 0x20);
  re_wr_ptr(last + 0x20, ev);
  if ((rd16(last) & 0x20) == 0) { wr16(last, (uint16_t)(rd16(last) | 0x10)); wr16(last + 8, rd16(last + 6)); }
  wr16(ev + 4, 1);
  wr16(ev, (uint16_t)(rd16(ev) | 8 | 0x20));
  wr16(ev + 6, (uint16_t)P99_EvId);
  wr16(ev + 8, rd16(last + 8));
  uint8_t *o = (uint8_t *)P98_DebugMalloc(0x60, "D:\\Driver\\Game\\compiler.c", 0x1ee);
  if (o == NULL) { P26_ErrorInLine("Not enough memory for\nnew model!"); return; }   /* дальше оригинал писал бы по мусору */
  memset(o, 0, 0x60);
  re_wr_ptr(ev + 0x1c, o);
  if (P99_EvObj != NULL) wr32(o + 0x50, rd32(P99_EvObj + 0x50));
  if (P99_EvA != NULL) wr16(o + 0x4a, rd16(P99_EvA + n * 2));
  if (P99_EvB != NULL) wr16(o + 0x40, rd16(P99_EvB + n * 2));
  if (P99_EvC != NULL) wrf(o + 0x44, (float)rd16(P99_EvC + n * 2));
}

/* ---- 0051358d: частица p (тип 4) — на свободное кресло клетки под ней, если частиц меньше лимита ---- */
int32_t P99_PartOnChair(uint8_t *p, int32_t n) {
  int32_t r = 0;
  if (!(G8_00C56710 < P73_C56760 && n < P73_C56760 / 4)) return 0;
  int32_t cx = (int32_t)(rdf(p + 0x84) / (float)P80_Cell + (float)(P21_GridDiv / 2));
  int32_t cz = (int32_t)(rdf(p + 0x8c) / (float)P80_Cell + (float)(P80_GridH / 2));
  const int32_t *ch = (const int32_t *)P96_PickChair(cz * P21_GridDiv + cx);
  if (ch == NULL) return 0;
  wr16(p, 3);
  wr32(p + 0x1c, 4);
  P70_SpawnPart4(p);
  wrf(p + 0x84, (float)ch[0]);
  wrf(p + 0x8c, (float)ch[1]);
  wr32(p + 0x5c, ch[3]);
  wr32(p + 0x60, ch[4]);
  wr16(p + 0x5c, (uint16_t)((rd16(p + 0x5c) - 0x800) & 0xfff));
  uint32_t u = (uint32_t)((int32_t)rd16s(p + 0x5e) - 0x800) & 0xfff;
  float fz = P43_Sin[u + 0x400] * 60.0f;                     /* _DAT_00546a74 = 60.0 */
  wrf(p + 0x84, (P43_Sin[u] * 60.0f - 1000.0f) + rdf(p + 0x84));   /* _DAT_00546130 = 1000.0 */
  wrf(p + 0x8c, (fz - 1000.0f) + rdf(p + 0x8c));
  if (P70_FindParticle(ch[0], ch[1]) == -1) {
    wrf(p + 0x84, rdf(p + 0x84) + 1000.0f);
    wrf(p + 0x8c, rdf(p + 0x8c) + 1000.0f);
    G8_00C56710++;
    r = 1;
  }
  return r;
}

/* ---- 004f568a: цель скрипта g (тип 2/7) достигнута/потеряна — состояние 0x7fff и сброс флагов объекта o ---- */
void P99_GoalCheck(int32_t t, uint8_t *g, int32_t *o) {
  int32_t busy = 0;
  if (0x2a9 < G2_00D11A5C && (P95_SndReady != 0 || 0 < P95_AmbN)) busy = 1;
  if (!(t < o[0] && (rd32(g + 4) == 2 || rd32(g + 4) == 7) && ((P97_C810A8 == 0 && P97_C81490 == 0) || !busy))) return;
  if ((rd32(g + 0x18) & 1) == 0) {
    if (rd32(g + 0x1b4) == 0 || CAR(0)->f10c <= rd32(g + 0x44)) { wr32(g + 4, 0x7fff); o[4] &= (int32_t)0xfffffffeu; }
  } else {
    const uint8_t *cnt = (const uint8_t *)re_rd_ptr(g + 0x1fc);
    if ((cnt != NULL ? rd32(cnt) : 0) < rd32(g + 0x1c) * 0x32) {
      if (rd32(g + 0x1b4) == 0 || CAR(0)->f10c <= rd32(g + 0x44)) { wr32(g + 4, 0x7fff); o[4] &= (int32_t)0xfffffdf8u; }
    } else AddClamp4095_004D2ADE(5);
  }
}

/* ---- 004a7920: проекция машины (+0xc64/+0xc6c) на путь (список +0x60: узел +0 следующий, +8/+0xc точка) ---- */
int32_t P99_PathAhead(uint8_t *car) {
  if (rd32(car + 0xcb8) == 0) return 0;
  uint8_t *n = car + 0x60;
  for (int32_t k = rd32(car + 0x14); k != 0; k--) { n = (uint8_t *)re_rd_ptr(n); if (n == NULL) return 0; }
  uint8_t *nx;
  while ((nx = (uint8_t *)re_rd_ptr(n)) != NULL) {
    int32_t dx = rd32(nx + 8) - rd32(n + 8), dz = rd32(nx + 0xc) - rd32(n + 0xc);
    int32_t ax = iabs(dx), az = iabs(dz);
    int32_t hi = ax, lo = az;
    if (ax < az) { hi = az; lo = ax; }
    int32_t len = hi + (lo * 0xd >> 5);
    if (0 < len) {
      int32_t pr = ((rd32(car + 0xc64) - rd32(n + 8)) * dx + (rd32(car + 0xc6c) - rd32(n + 0xc)) * dz) / len;
      if (pr < len) { re_wr_ptr(car + 0xc60, n); return pr; }
    }
    if (rd32(car + 0x1c) - 3 < rd32(car + 0x14)) break;
    wr32(car + 0x14, rd32(car + 0x14) + 1);
    n = nx;
  }
  wr32(car + 0xcb8, 0);
  return 0;
}

/* ---- 00526aeb: пересечение отрезков ab и cd (целые): 0 — нет, 1 — точка (ox, oy), 2 — параллельны ---- */
int32_t P99_SegCross(const int32_t *a, const int32_t *b, const int32_t *c, const int32_t *d, int32_t *ox, int32_t *oy) {
  int32_t a1 = b[1] - a[1], b1 = a[0] - b[0], c1 = b[0] * a[1] - a[0] * b[1];
  uint32_t r3 = (uint32_t)(b1 * c[1] + c1 + a1 * c[0]), r4 = (uint32_t)(b1 * d[1] + c1 + a1 * d[0]);
  if (r3 != 0 && r4 != 0 && (int32_t)(r3 ^ r4) >= 0) return 0;
  int32_t a2 = d[1] - c[1], b2 = c[0] - d[0], c2 = d[0] * c[1] - c[0] * d[1];
  uint32_t r1 = (uint32_t)(b2 * a[1] + c2 + a2 * a[0]), r2 = (uint32_t)(b2 * b[1] + c2 + a2 * b[0]);
  if (r1 != 0 && r2 != 0 && (int32_t)(r1 ^ r2) >= 0) return 0;
  int32_t den = a1 * b2 - a2 * b1;
  if (den == 0) return 2;
  int32_t off = iabs(den) / 2;
  int32_t num = b1 * c2 - b2 * c1;
  *ox = (num + (num < 0 ? -off : off)) / den;
  num = a2 * c1 - a1 * c2;
  *oy = (num + (num < 0 ? -off : off)) / den;
  return 1;
}

/* ---- 00526cd5: отсечение отрезка a→b прямоугольником box (x0, x1? см. P43_ClipT): o1 — новый конец, o0 — новое начало ---- */
int32_t P99_SegClip(const int32_t *box, const int32_t *a, const int32_t *b, int32_t *o0, int32_t *o1) {
  int32_t dx = b[0] - a[0], dy = b[1] - a[1], r = 0;
  if (dx == 0 && dy == 0) return 0;
  float t0 = 0.0f, t1 = 1.0f;
  if (P43_ClipT(dx, box[0] - a[0], &t0, &t1) != 0 && P43_ClipT(-dx, a[0] - box[2], &t0, &t1) != 0 &&
      P43_ClipT(dy, box[1] - a[1], &t0, &t1) != 0 && P43_ClipT(-dy, a[1] - box[3], &t0, &t1) != 0) {
    if (t1 < 1.0f) {
      P11_00ba52d0 = fround(t1 * (float)dx); o1[0] = a[0] + P11_00ba52d0;
      P11_00ba52d0 = fround(t1 * (float)dy); o1[1] = a[1] + P11_00ba52d0;
      r = 1;
    }
    if (0.0f < t0) {
      P11_00ba52d0 = fround(t0 * (float)dx); o0[0] = a[0] + P11_00ba52d0;
      P11_00ba52d0 = fround(t0 * (float)dy); o0[1] = a[1] + P11_00ba52d0;
      r = 1;
    }
  }
  return r;
}

/* ---- 0050f569: пункты меню (записи 0x14: x16, y16, флаги текста8, флаги8 (+5: 1 — строка языка, 2 — адрес, 4, 0x10 — конец),
        +8 текст) — тень, затем цвет: 0 — жёлтый, выбранный P17_ValA — красный ---- */
void P99_MenuItems(const int16_t *it) {
  int32_t k = 0;
  for (; (((const uint8_t *)it)[5] & 0x10) == 0; it += 10) {
    const uint8_t *b = (const uint8_t *)it;
    int32_t v = rd32(b + 8);
    if (v != -1) {
      uint32_t txt;
      if ((b[5] & 1) != 0) txt = P97_StrAddr[v];
      else if ((b[5] & 2) != 0) txt = (uint32_t)v;
      else txt = 0;
      if (txt != 0) {
        SetRGB00516EB4(0xff, 0xff, 0xff);
        P73_Text((float)it[0], (float)it[1], txt, 0, b[4] | 0x10);
        P73_Text((float)it[0] + 2.0f, (float)it[1] + 2.0f, txt, 0, b[4] | 0x10);   /* _DAT_00546050 = 2.0 */
        if (k == 0) SetRGB00516EB4(0xff, 0xff, 0x80);
        else if (k == P17_ValA || (k == P17_ValA + 1 && (b[5] & 4) == 0)) SetRGB00516EB4(0xff, 0, 0);
        else if (P8_00b5a768 == 0 || v != 0xa5) SetRGB00516EB4(0xff, 0xff, 0xff);
        else SetRGB00516EB4(0x7f, 0x7f, 0x7f);
        P73_Text((float)it[0], (float)it[1], txt, 0, b[4] | 4);
      }
    }
    k++;
  }
}
