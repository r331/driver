/* ported61.c — camera helpers: the per-car view camera setup (P61_SetupCamN), saving / restoring the
   live camera into a director camera record (names_g1.h DCAM_*), normalising such a record before
   playback, and spawning one particle/effect object.  English summary of ported61.h. */
#include "ported61.h"
#include "carfields.h"
#include "names_g1.h"
#include <math.h>
#include <string.h>

#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P61_CamOffs")
#undef P61_CamOffs
#pragma push_macro("P61_CamOffs") /*gvi*/
#undef P61_CamOffs /*gvi*/
p61_offs_t P61_CamOffs;
#pragma pop_macro("P61_CamOffs") /*gvi*/
#pragma pop_macro("P61_CamOffs")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P61_Heading")
#undef P61_Heading
#pragma push_macro("P61_Heading") /*gvi*/
#undef P61_Heading /*gvi*/
int16_t P61_Heading;
#pragma pop_macro("P61_Heading") /*gvi*/
#pragma pop_macro("P61_Heading")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P61_TgtX")
#undef P61_TgtX
#pragma push_macro("P61_TgtX") /*gvi*/
#undef P61_TgtX /*gvi*/
float P61_TgtX;
#pragma pop_macro("P61_TgtX") /*gvi*/
#pragma pop_macro("P61_TgtX")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P61_TgtY")
#undef P61_TgtY
#pragma push_macro("P61_TgtY") /*gvi*/
#undef P61_TgtY /*gvi*/
float P61_TgtY;
#pragma pop_macro("P61_TgtY") /*gvi*/
#pragma pop_macro("P61_TgtY")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P61_TgtZ")
#undef P61_TgtZ
#pragma push_macro("P61_TgtZ") /*gvi*/
#undef P61_TgtZ /*gvi*/
float P61_TgtZ;
#pragma pop_macro("P61_TgtZ") /*gvi*/
#pragma pop_macro("P61_TgtZ")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P61_OffX")
#undef P61_OffX
#pragma push_macro("P61_OffX") /*gvi*/
#undef P61_OffX /*gvi*/
float P61_OffX;
#pragma pop_macro("P61_OffX") /*gvi*/
#pragma pop_macro("P61_OffX")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P61_OffY")
#undef P61_OffY
#pragma push_macro("P61_OffY") /*gvi*/
#undef P61_OffY /*gvi*/
float P61_OffY;
#pragma pop_macro("P61_OffY") /*gvi*/
#pragma pop_macro("P61_OffY")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P61_OffZ")
#undef P61_OffZ
#pragma push_macro("P61_OffZ") /*gvi*/
#undef P61_OffZ /*gvi*/
float P61_OffZ;
#pragma pop_macro("P61_OffZ") /*gvi*/
#pragma pop_macro("P61_OffZ")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P61_AngB8")
#undef P61_AngB8
#pragma push_macro("P61_AngB8") /*gvi*/
#undef P61_AngB8 /*gvi*/
uint16_t P61_AngB8;
#pragma pop_macro("P61_AngB8") /*gvi*/
#pragma pop_macro("P61_AngB8")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P61_AngBA")
#undef P61_AngBA
#pragma push_macro("P61_AngBA") /*gvi*/
#undef P61_AngBA /*gvi*/
uint16_t P61_AngBA;
#pragma pop_macro("P61_AngBA") /*gvi*/
#pragma pop_macro("P61_AngBA")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P61_AngBC")
#undef P61_AngBC
#pragma push_macro("P61_AngBC") /*gvi*/
#undef P61_AngBC /*gvi*/
uint16_t P61_AngBC;
#pragma pop_macro("P61_AngBC") /*gvi*/
#pragma pop_macro("P61_AngBC")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P61_Dist8")
#undef P61_Dist8
#pragma push_macro("P61_Dist8") /*gvi*/
#undef P61_Dist8 /*gvi*/
float P61_Dist8;
#pragma pop_macro("P61_Dist8") /*gvi*/
#pragma pop_macro("P61_Dist8")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P61_DistC")
#undef P61_DistC
#pragma push_macro("P61_DistC") /*gvi*/
#undef P61_DistC /*gvi*/
float P61_DistC;
#pragma pop_macro("P61_DistC") /*gvi*/
#pragma pop_macro("P61_DistC")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P61_V18")
#undef P61_V18
#pragma push_macro("P61_V18") /*gvi*/
#undef P61_V18 /*gvi*/
int32_t P61_V18;
#pragma pop_macro("P61_V18") /*gvi*/
#pragma pop_macro("P61_V18")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P61_V1C")
#undef P61_V1C
#pragma push_macro("P61_V1C") /*gvi*/
#undef P61_V1C /*gvi*/
int32_t P61_V1C;
#pragma pop_macro("P61_V1C") /*gvi*/
#pragma pop_macro("P61_V1C")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P61_V20")
#undef P61_V20
#pragma push_macro("P61_V20") /*gvi*/
#undef P61_V20 /*gvi*/
int32_t P61_V20;
#pragma pop_macro("P61_V20") /*gvi*/
#pragma pop_macro("P61_V20")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P61_V10")
#undef P61_V10
#pragma push_macro("P61_V10") /*gvi*/
#undef P61_V10 /*gvi*/
int32_t P61_V10;
#pragma pop_macro("P61_V10") /*gvi*/
#pragma pop_macro("P61_V10")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P61_V10b")
#undef P61_V10b
#pragma push_macro("P61_V10b") /*gvi*/
#undef P61_V10b /*gvi*/
int32_t P61_V10b;
#pragma pop_macro("P61_V10b") /*gvi*/
#pragma pop_macro("P61_V10b")
#endif

static int32_t rd32(const uint8_t *p, uint32_t o) { int32_t v; memcpy(&v, p + o, 4); return v; }
static void    wr32(uint8_t *p, uint32_t o, int32_t v) { memcpy(p + o, &v, 4); }
static uint16_t rd16(const uint8_t *p, uint32_t o) { uint16_t v; memcpy(&v, p + o, 2); return v; }
static void    wr16(uint8_t *p, uint32_t o, uint16_t v) { memcpy(p + o, &v, 2); }
#define DCAM_MODE_CAR     2      /* DCAM_MODE: camera attached to a car */
#define DCAM_MODE_KEEP48  0x11   /* DCAM_MODE that keeps DCAM_FLAG48 */
#define DCAM_MAX_DIST     15000  /* P61_CamPrepare caps the target distance */
/* Car record n of the car table P60_Cars (0x148 bytes, field offsets in carfields.h). */
static const uint8_t *Car(int32_t n) { return (const uint8_t *)P60_Cars + (uint32_t)n * 0x148; }

/* fistp: округление к ближайшему чётному, как x87 по умолчанию */
static int32_t Round(float f) { return (int32_t)lrintf(f); }

/* Смещения камеры от машины (18 записей по 4 float) — из .data Game.exe, прочитано по адресу 0x560968. */
/* P61_InitConsts — native only.  Fills P61_CamOffs with the .data table at 00560968: 18 camera offsets
   {x, y, z, 0} from the player car, one per car model (indexed by S_00D1192C in P61_SetupCamN). */
void P61_InitConsts(void) {
#ifndef RE_HOOK_BUILD
  static const float t[18 * 4] = {
    0, -100, 95, 0,  0, -105, 135, 0,  0, -80, 120, 0,  0, -90, 120, 0,  0, -90, 80, 0,  0, -85, 115, 0,
    0, -95, 115, 0,  0, -80, 125, 0,  0, -90, 110, 0,  0, -85, 120, 0,  0, -75, 130, 0,  0, -90, 115, 0,
    0, -95, 90, 0,  0, -90, 110, 0,  0, -90, 100, 0,  0, -90, 125, 0,  0, -95, 47, 0,  0, -90, 120, 0 };
  memcpy(P61_CamOffs, t, sizeof t);
#endif
}

/* 0049e5e7: углы камеры из углов машины n, матрица вида (поворот Z, X, Y) и транспонат; положение = машина + смещение,
   повёрнутое матрицей (для машины 0 — из таблицы по номеру 00d1192c, иначе 5, -115, 150). */
/* P61_SetupCamN — Game.exe 0049e5e7.  Builds the view camera attached to car n: angles from the car's
   Euler angles (pitch, P61_Heading - heading, roll; masked to 0..0xfff), view matrix
   = RotZ * RotX * RotY of identity and its transpose (P44_ViewMat / P44_ViewMatT, P44_MatPtr = view);
   position = car position (y negated: car y grows downward) + the offset rotated by that matrix.
   Offset: player (n == 0) from P61_CamOffs[S_00D1192C], other cars a fixed (5, -115, 150).
   TODO(RE): unsure that S_00D1192C is the player's car model (it is the index of the 18-entry table). */
void P61_SetupCamN(int32_t n) {
  const uint8_t *car = Car(n);
  P59_AngA = rd16(car, CAR_ANG) & 0xfff;
  P59_AngB = (uint16_t)(((int16_t)P61_Heading - (int16_t)rd16(car, CAR_ANG + 2)) & 0xfff);
  P59_AngC = rd16(car, CAR_ANG + 4) & 0xfff;
  float *m = P44_ViewMat;
  for (int i = 0; i < 9; i++) m[i] = 0.0f;
  m[0] = m[4] = m[8] = 1.0f;
  P44_RotZ(m, (int32_t)P59_AngC);
  P44_RotX(m, (int32_t)(int16_t)P59_AngA);
  P44_RotY(m, (int32_t)(int16_t)P59_AngB);
  P44_Transpose(m, P44_ViewMatT);
  P44_MatPtr = m;
  float v[4];
  if (n == 0) {
    int32_t k = S_00D1192C * 4;
    v[0] = P61_CamOffs[k]; v[1] = P61_CamOffs[k + 1]; v[2] = P61_CamOffs[k + 2]; v[3] = P61_CamOffs[k + 3];
  } else {
    v[0] = 5.0f; v[1] = -115.0f; v[2] = 150.0f; v[3] = 0.0f;
  }
  P44_Xform(v);
  P44_CamX = (float)rd32(car, CAR_POS_X) + v[0];
  P44_CamY = (float)(-rd32(car, CAR_POS_Y)) + v[1];
  P44_CamZ = (float)rd32(car, CAR_POS_Z) + v[2];
}

/* P61_StoreCamState — Game.exe 004c5499.  Snapshot of the live camera into director record c: target,
   offset, angles, position, distances (floats rounded with x87 round-to-nearest-even), the integer
   state P61_V*, the camera mode, and the P60_Var1373C0 byte (cleared again unless mode 0x11). */
void P61_StoreCamState(uint8_t *c) {
  wr32(c, DCAM_TARGET, Round(P61_TgtX)); wr32(c, DCAM_TARGET + 4, Round(P61_TgtY)); wr32(c, DCAM_TARGET + 8, Round(P61_TgtZ));
  wr32(c, DCAM_OFFSET, Round(P61_OffX)); wr32(c, DCAM_OFFSET + 4, Round(P61_OffY)); wr32(c, DCAM_OFFSET + 8, Round(P61_OffZ));
  wr16(c, DCAM_ANGLES, P61_AngB8); wr16(c, DCAM_ANGLES + 2, P61_AngBA); wr16(c, DCAM_ANGLES + 4, P61_AngBC);
  wr32(c, DCAM_POS, Round(P44_CamX)); wr32(c, DCAM_POS + 4, Round(P44_CamY)); wr32(c, DCAM_POS + 8, Round(P44_CamZ));
  wr32(c, DCAM_DIST, Round(P61_Dist8)); wr32(c, DCAM_DIST_C, Round(P61_DistC));
  wr32(c, DCAM_ANG_REL, P61_V18); wr32(c, DCAM_ANG_ABS, P61_V1C); wr32(c, DCAM_V20, P61_V20); wr32(c, DCAM_CAR, P61_V10);
  wr32(c, DCAM_MODE, (int32_t)(uint32_t)P59_Mode1137324);
  wr32(c, DCAM_FLAG48, (int32_t)(uint32_t)(uint8_t)P60_Var1373C0);
  if (rd32(c, DCAM_MODE) != DCAM_MODE_KEEP48) wr32(c, DCAM_FLAG48, 0);
}

/* P61_RestoreCamState — Game.exe 004c536c.  Inverse of P61_StoreCamState: loads the live camera from
   record c (clearing the record's DCAM_FLAG48 first unless mode 0x11); in car mode (2) also rebuilds
   the car camera for car DCAM_CAR (P61_V10b = that car). */
void P61_RestoreCamState(uint8_t *c) {
  P44_CamX = (float)rd32(c, DCAM_POS); P44_CamY = (float)rd32(c, DCAM_POS + 4); P44_CamZ = (float)rd32(c, DCAM_POS + 8);
  P61_OffX = (float)rd32(c, DCAM_OFFSET); P61_OffY = (float)rd32(c, DCAM_OFFSET + 4); P61_OffZ = (float)rd32(c, DCAM_OFFSET + 8);
  P61_TgtX = (float)rd32(c, DCAM_TARGET); P61_TgtY = (float)rd32(c, DCAM_TARGET + 4); P61_TgtZ = (float)rd32(c, DCAM_TARGET + 8);
  P61_AngB8 = rd16(c, DCAM_ANGLES); P61_AngBA = rd16(c, DCAM_ANGLES + 2); P61_AngBC = rd16(c, DCAM_ANGLES + 4);
  P61_Dist8 = (float)rd32(c, DCAM_DIST); P61_DistC = (float)rd32(c, DCAM_DIST_C);
  P61_V18 = rd32(c, DCAM_ANG_REL); P61_V1C = rd32(c, DCAM_ANG_ABS); P61_V20 = rd32(c, DCAM_V20); P61_V10 = rd32(c, DCAM_CAR);
  P59_Mode1137324 = (uint8_t)rd32(c, DCAM_MODE);
  if (rd32(c, DCAM_MODE) != DCAM_MODE_KEEP48) wr32(c, DCAM_FLAG48, 0);
  *(uint8_t *)&P60_Var1373C0 = (uint8_t)rd32(c, DCAM_FLAG48);
  if (rd32(c, DCAM_MODE) == DCAM_MODE_CAR) {
    P61_V10b = rd32(c, DCAM_CAR);
    P61_SetupCamN(rd32(c, DCAM_CAR));
  }
}

/* P61_CamPrepare — Game.exe 004c6d62.  Normalises director record c before use:
     car -1 -> 0; DCAM_FLAG48 = 0;
     mode 2 (car): relative angle 180 deg, distance 0x500, offset y -0x100;
     other non-zero modes: distance = horizontal distance target - car (capped at 15000), position =
       target, offset y = target y + car y, relative angle = atan2 of (target - car) minus the car
       heading, then the height clamp (ClampCameraHeight);
     non-zero modes: absolute angle = car heading + relative angle.
   Finally DCAM_DIST_C = DCAM_DIST and the mode is reset to 0.  (Mode 0 records only get the last step.) */
void P61_CamPrepare(uint8_t *c) {
  if (rd32(c, DCAM_CAR) == -1) wr32(c, DCAM_CAR, 0);
  const uint8_t *car = Car(rd32(c, DCAM_CAR));
  wr32(c, DCAM_FLAG48, 0);
  if (rd32(c, DCAM_MODE) != 0) {
    if (rd32(c, DCAM_MODE) == DCAM_MODE_CAR) {
      wr32(c, DCAM_ANG_REL, 0x800); wr32(c, DCAM_DIST, 0x500); wr32(c, DCAM_OFFSET + 4, -0x100);   /* 0x800 = ANG_180 */
    } else {
      float fx = (float)(rd32(c, DCAM_TARGET) - rd32(car, CAR_POS_X));
      int32_t y = rd32(c, DCAM_TARGET + 4), carY = rd32(car, CAR_POS_Y);
      float fz = (float)(rd32(c, DCAM_TARGET + 8) - rd32(car, CAR_POS_Z));
      int32_t d = Round((float)sqrt((double)fz * fz + (double)fx * fx));
      int32_t lim = d > DCAM_MAX_DIST ? DCAM_MAX_DIST : d;
      wr32(c, DCAM_DIST, lim);
      wr32(c, DCAM_POS, rd32(c, DCAM_TARGET)); wr32(c, DCAM_POS + 4, rd32(c, DCAM_TARGET + 4)); wr32(c, DCAM_POS + 8, rd32(c, DCAM_TARGET + 8)); wr32(c, DCAM_POS + 0xc, rd32(c, DCAM_TARGET + 0xc));
      wr32(c, DCAM_OFFSET + 4, Round((float)(y + carY)));
      int32_t rz = Round(fz), rx = Round(fx);
      wr32(c, DCAM_ANG_REL, (P44_Atan2(rx, rz) - rd32(car, CAR_HEADING)) & 0xfff);
      ClampCameraHeight((int32_t *)c);
    }
    wr32(c, DCAM_ANG_ABS, (rd32(car, CAR_HEADING) + rd32(c, DCAM_ANG_REL)) & 0xfff);
  }
  wr32(c, DCAM_DIST_C, rd32(c, DCAM_DIST));
  wr32(c, DCAM_MODE, 0);
}

/* P61_SpawnPart — Game.exe 00514261.  Starts the effect object p (pool record of ported43, 0xb4 bytes):
   P61_Fn5139D7(0, round(p+0x84), round(p+0x8c), p+0x94) returns a handle (0 = failed -> the slot is
   freed); on success the handle goes to +0x38 and four set-up routines run in the original order.
   TODO(RE): unsure what the floats at +0x84 / +0x8c and the block at +0x94 are (position x / z?). */
void P61_SpawnPart(uint8_t *p) {
  int32_t a = Round(*(float *)(p + 0x8c));
  int32_t b = Round(*(float *)(p + 0x84));
  int32_t r = P61_Fn5139D7(0, b, a, p + 0x94);
  if (r == 0) {
    P43_FreeSlot(p);
  } else {
    wr32(p, 0x38, r);
    P61_Fn5144D4(p, p + 0x84);
    P61_Fn514779(p, p + 0x94);
    P61_Fn514F47(p);
    P61_Fn514BC7(p, 1, 0);
  }
}
