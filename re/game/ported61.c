#include "ported61.h"
#include <math.h>
#include <string.h>

GAME_VAR_DEF(p61_offs_t, P61_CamOffs, 0x00560968)
GAME_VAR_DEF(int16_t, P61_Heading, 0x01137322)
GAME_VAR_DEF(float, P61_TgtX, 0x01136c70)
GAME_VAR_DEF(float, P61_TgtY, 0x01136c74)
GAME_VAR_DEF(float, P61_TgtZ, 0x01136c78)
GAME_VAR_DEF(float, P61_OffX, 0x011373a0)
GAME_VAR_DEF(float, P61_OffY, 0x011373a4)
GAME_VAR_DEF(float, P61_OffZ, 0x011373a8)
GAME_VAR_DEF(uint16_t, P61_AngB8, 0x011373b8)
GAME_VAR_DEF(uint16_t, P61_AngBA, 0x011373ba)
GAME_VAR_DEF(uint16_t, P61_AngBC, 0x011373bc)
GAME_VAR_DEF(float, P61_Dist8, 0x01137368)
GAME_VAR_DEF(float, P61_DistC, 0x0113731c)
GAME_VAR_DEF(int32_t, P61_V18, 0x01136c58)
GAME_VAR_DEF(int32_t, P61_V1C, 0x01137310)
GAME_VAR_DEF(int32_t, P61_V20, 0x01137318)
GAME_VAR_DEF(int32_t, P61_V10, 0x01136c48)
GAME_VAR_DEF(int32_t, P61_V10b, 0x01136c4c)

static int32_t rd32(const uint8_t *p, uint32_t o) { int32_t v; memcpy(&v, p + o, 4); return v; }
static void    wr32(uint8_t *p, uint32_t o, int32_t v) { memcpy(p + o, &v, 4); }
static uint16_t rd16(const uint8_t *p, uint32_t o) { uint16_t v; memcpy(&v, p + o, 2); return v; }
static void    wr16(uint8_t *p, uint32_t o, uint16_t v) { memcpy(p + o, &v, 2); }
static const uint8_t *Car(int32_t n) { return (const uint8_t *)P60_Cars + (uint32_t)n * 0x148; }

/* fistp: округление к ближайшему чётному, как x87 по умолчанию */
static int32_t Round(float f) { return (int32_t)lrintf(f); }

/* Смещения камеры от машины (18 записей по 4 float) — из .data Game.exe, прочитано по адресу 0x560968. */
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
void P61_SetupCamN(int32_t n) {
  const uint8_t *car = Car(n);
  P59_AngA = rd16(car, 0xe8) & 0xfff;
  P59_AngB = (uint16_t)(((int16_t)P61_Heading - (int16_t)rd16(car, 0xea)) & 0xfff);
  P59_AngC = rd16(car, 0xec) & 0xfff;
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
  P44_CamX = (float)rd32(car, 0xc8) + v[0];
  P44_CamY = (float)(-rd32(car, 0xcc)) + v[1];
  P44_CamZ = (float)rd32(car, 0xd0) + v[2];
}

void P61_StoreCamState(uint8_t *c) {
  wr32(c, 0x5c, Round(P61_TgtX)); wr32(c, 0x60, Round(P61_TgtY)); wr32(c, 0x64, Round(P61_TgtZ));
  wr32(c, 0x6c, Round(P61_OffX)); wr32(c, 0x70, Round(P61_OffY)); wr32(c, 0x74, Round(P61_OffZ));
  wr16(c, 0x7c, P61_AngB8); wr16(c, 0x7e, P61_AngBA); wr16(c, 0x80, P61_AngBC);
  wr32(c, 0x4c, Round(P44_CamX)); wr32(c, 0x50, Round(P44_CamY)); wr32(c, 0x54, Round(P44_CamZ));
  wr32(c, 8, Round(P61_Dist8)); wr32(c, 0xc, Round(P61_DistC));
  wr32(c, 0x18, P61_V18); wr32(c, 0x1c, P61_V1C); wr32(c, 0x20, P61_V20); wr32(c, 0x10, P61_V10);
  wr32(c, 0, (int32_t)(uint32_t)P59_Mode1137324);
  wr32(c, 0x48, (int32_t)(uint32_t)(uint8_t)P60_Var1373C0);
  if (rd32(c, 0) != 0x11) wr32(c, 0x48, 0);
}

void P61_RestoreCamState(uint8_t *c) {
  P44_CamX = (float)rd32(c, 0x4c); P44_CamY = (float)rd32(c, 0x50); P44_CamZ = (float)rd32(c, 0x54);
  P61_OffX = (float)rd32(c, 0x6c); P61_OffY = (float)rd32(c, 0x70); P61_OffZ = (float)rd32(c, 0x74);
  P61_TgtX = (float)rd32(c, 0x5c); P61_TgtY = (float)rd32(c, 0x60); P61_TgtZ = (float)rd32(c, 0x64);
  P61_AngB8 = rd16(c, 0x7c); P61_AngBA = rd16(c, 0x7e); P61_AngBC = rd16(c, 0x80);
  P61_Dist8 = (float)rd32(c, 8); P61_DistC = (float)rd32(c, 0xc);
  P61_V18 = rd32(c, 0x18); P61_V1C = rd32(c, 0x1c); P61_V20 = rd32(c, 0x20); P61_V10 = rd32(c, 0x10);
  P59_Mode1137324 = (uint8_t)rd32(c, 0);
  if (rd32(c, 0) != 0x11) wr32(c, 0x48, 0);
  *(uint8_t *)&P60_Var1373C0 = (uint8_t)rd32(c, 0x48);
  if (rd32(c, 0) == 2) {
    P61_V10b = rd32(c, 0x10);
    P61_SetupCamN(rd32(c, 0x10));
  }
}

void P61_CamPrepare(uint8_t *c) {
  if (rd32(c, 0x10) == -1) wr32(c, 0x10, 0);
  const uint8_t *car = Car(rd32(c, 0x10));
  wr32(c, 0x48, 0);
  if (rd32(c, 0) != 0) {
    if (rd32(c, 0) == 2) {
      wr32(c, 0x18, 0x800); wr32(c, 8, 0x500); wr32(c, 0x70, -0x100);
    } else {
      float fx = (float)(rd32(c, 0x5c) - rd32(car, 0xc8));
      int32_t y = rd32(c, 0x60), carY = rd32(car, 0xcc);
      float fz = (float)(rd32(c, 0x64) - rd32(car, 0xd0));
      int32_t d = Round((float)sqrt((double)fz * fz + (double)fx * fx));
      int32_t lim = d > 15000 ? 15000 : d;
      wr32(c, 8, lim);
      wr32(c, 0x4c, rd32(c, 0x5c)); wr32(c, 0x50, rd32(c, 0x60)); wr32(c, 0x54, rd32(c, 0x64)); wr32(c, 0x58, rd32(c, 0x68));
      wr32(c, 0x70, Round((float)(y + carY)));
      int32_t rz = Round(fz), rx = Round(fx);
      wr32(c, 0x18, (P44_Atan2(rx, rz) - rd32(car, 0x100)) & 0xfff);
      ClampCameraHeight((int32_t *)c);
    }
    wr32(c, 0x1c, (rd32(car, 0x100) + rd32(c, 0x18)) & 0xfff);
  }
  wr32(c, 0xc, rd32(c, 8));
  wr32(c, 0, 0);
}

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
