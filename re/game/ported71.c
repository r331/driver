#include "ported71.h"
#include <math.h>
#include <string.h>

GAME_VAR_DEF(int32_t, P71_Near, 0x00c59480)
GAME_VAR_DEF(int32_t, P71_NearAdd, 0x00c56708)
GAME_VAR_DEF(int32_t, P71_Tab974, 0x00b32974)
GAME_VAR_DEF(int32_t, P71_Tab2A40, 0x00b52a40)
GAME_VAR_DEF(uint32_t, P71_Ptr2A08, 0x00b32a08)
GAME_VAR_DEF(int32_t, P71_V2A24, 0x00b32a24)
GAME_VAR_DEF(int32_t, P71_V2A20, 0x00b32a20)
GAME_VAR_DEF(int32_t, P71_V2A1C, 0x00b32a1c)
GAME_VAR_DEF(int32_t, P71_V2A14, 0x00b32a14)
GAME_VAR_DEF(int32_t, P71_S1271084, 0x01271084)
GAME_VAR_DEF(int32_t, P71_S1271080, 0x01271080)
GAME_VAR_DEF(int32_t, P71_S127107C, 0x0127107c)
GAME_VAR_DEF(int32_t, P71_S1271074, 0x01271074)
GAME_VAR_DEF(int32_t, P71_S127109C, 0x0127109c)
GAME_VAR_DEF(int32_t, P71_S1271098, 0x01271098)
GAME_VAR_DEF(int32_t, P71_S1271094, 0x01271094)
GAME_VAR_DEF(int32_t, P71_S127108C, 0x0127108c)

static int32_t rd32(const uint8_t *p, uint32_t o) { int32_t v; memcpy(&v, p + o, 4); return v; }
static void    wr32(uint8_t *p, uint32_t o, int32_t v) { memcpy(p + o, &v, 4); }
static float   rdf(const uint8_t *p, uint32_t o) { float v; memcpy(&v, p + o, 4); return v; }
/* fistp в режиме по умолчанию: округление к ближайшему чётному */
static int32_t Rnd(float v) { return (int32_t)lrintf(v); }

#define P71_CELL 0x5dc

/* общая часть 005144d4/00514779: клетка (x, z) по q[0], q[2] (x87: __ftol усекает) и проходимость четырёх соседних клеток */
static void cell_state(const float *q, int32_t *ix, int32_t *iz, int16_t s[4]) {
  int32_t cx = (int32_t)(((long double)q[0] + 750.0f + (float)P62_MapC64) / 1500.0f);
  int32_t cz = (int32_t)((-((long double)q[2] - 750.0f) + (float)P62_Map2C40) / 1500.0f);
  int32_t x = (int32_t)((uint32_t)cx * P71_CELL - (uint32_t)P62_MapC64);
  int32_t z = -(int32_t)((uint32_t)cz * P71_CELL - (uint32_t)P62_Map2C40);
  s[0] = (int16_t)P47_Fn51B111(x, z - P71_CELL);
  s[1] = (int16_t)P47_Fn51B111(x, z + P71_CELL);
  s[2] = (int16_t)P47_Fn51B111(x - P71_CELL, z);
  s[3] = (int16_t)P47_Fn51B111(x + P71_CELL, z);
  *ix = x; *iz = z;
}

static void set_open(uint8_t *p, int open) {
  uint32_t f = (uint32_t)rd32(p, 0xc);
  f = open ? (f | 0x100u) : (f & 0xfffffeffu);
  wr32(p, 0xc, (int32_t)f);
}

/* 005144d4 */
void P71_EdgeA(uint8_t *p, float *q) {
  int32_t x, z; int16_t s[4];
  cell_state(q, &x, &z, s);
  switch (rd32(p, 0x38)) {
  case 1:
    if (s[0] < 0) { set_open(p, 0); q[2] = (float)(z + 0x15e); } else { set_open(p, 1); q[2] = (float)(z - 0x226); }
    break;
  case 2:
    if (s[1] < 0) { set_open(p, 0); q[2] = (float)(z - 0x15e); } else { set_open(p, 1); q[2] = (float)(z + 0x226); }
    break;
  case 4:
    if (s[3] < 0) { set_open(p, 0); q[0] = (float)(x - 0x15e); } else { set_open(p, 1); q[0] = (float)(x + 0x226); }
    break;
  case 8:
    if (s[2] < 0) { set_open(p, 0); q[0] = (float)(x + 0x15e); } else { set_open(p, 1); q[0] = (float)(x - 0x226); }
    break;
  default: break;
  }
}

/* 00514779 */
void P71_EdgeB(uint8_t *p, float *q) {
  int32_t x, z; int16_t s[4];
  cell_state(q, &x, &z, s);
  switch (rd32(p, 0x38)) {
  case 1:
    if (s[0] < 0) { q[0] = (float)(x - 0x15e); q[2] = (float)(z + 0x15e); } else { q[0] = (float)(x - 0x226); q[2] = (float)(z - 0x226); }
    break;
  case 2:
    if (s[1] < 0) { q[0] = (float)(x + 0x15e); q[2] = (float)(z - 0x15e); } else { q[0] = (float)(x + 0x226); q[2] = (float)(z + 0x226); }
    break;
  case 4:
    if (s[2] < 0) { q[0] = (float)(x + 0x226); q[2] = (float)(z - 0x226); } else { q[0] = (float)(x - 0x15e); q[2] = (float)(z - 0x15e); }
    break;
  case 8:
    if (s[3] < 0) { q[0] = (float)(x - 0x226); q[2] = (float)(z + 0x226); } else { q[0] = (float)(x + 0x15e); q[2] = (float)(z + 0x15e); }
    break;
  default: break;
  }
}

/* 00514165 */
void P71_Course(uint8_t *p) {
  int32_t a = Rnd(rdf(p, 0x64));
  int32_t b = Rnd(rdf(p, 0x6c));
  int32_t ang = P44_Atan2(b, a);
  int32_t u = (int32_t)(((uint32_t)(-ang) - 0x400u) & 0xfffu);
  int16_t cur; memcpy(&cur, p + 0x5e, 2);
  int32_t d = (((u - (int32_t)cur) + 0x800) & 0xfff) - 0x800;
  uint32_t f = (uint32_t)rd32(p, 0xc);
  if (d < 0) { f |= 0x1000u; d = -d; } else { f |= 0x2000u; }
  wr32(p, 0xc, (int32_t)f);
  wr32(p, 0x14, u);
  wr32(p, 0x18, d);
}

/* 00515bf1 */
int32_t P71_InPlanes(const uint8_t *p, const float *q) {
  float x = rdf(p, 0x84), z = rdf(p, 0x8c);
  for (int i = 0; i < 4; i++) {
    float s = (float)((long double)x * q[i * 4] + (long double)z * q[i * 4 + 2]);
    if (s > q[i * 4 + 3]) return 0;
  }
  return 1;
}

/* 00515cca */
int32_t P71_FaceCar(const uint8_t *p, const uint8_t *car) {
  int32_t h = P44_Atan2(rd32(car, 0x40) >> 8, rd32(car, 0x48) >> 8) & 0xfff;
  float dz = rdf(p, 0x8c) - (float)rd32(car, 0xd0);
  float dx = rdf(p, 0x84) - (float)rd32(car, 0xc8);
  int32_t y = Rnd(dz), x = Rnd(dx);
  int32_t t = (((P44_Atan2(x, y) - h) + 0x800) & 0xfff) - 0x800;
  return (t > 0) ? ((h - 0x400) & 0xfff) : ((h + 0x400) & 0xfff);
}

/* 0051551e */
void P71_InitNear(uint8_t *car) {
  uint8_t *e = (uint8_t *)A_00C56780;
  for (int32_t i = 0; i < 0x40; i++, e += 0xb4) {
    uint32_t f = (uint32_t)rd32(e, 0xc);
    if ((f & 0x10) != 0 && rd32(e, 0x1c) != 3 && (f & 0x880) == 0) {
      int32_t dx = Rnd(rdf(e, 0x84)) - rd32(car, 0xc8); if (dx < 0) dx = -dx;
      int32_t dz = Rnd(rdf(e, 0x8c)) - rd32(car, 0xd0); if (dz < 0) dz = -dz;
      int32_t d = (dx < dz) ? dz + dx / 2 : dx + dz / 2;
      if (d <= 0x2ee) P62_ParticleInit(e, car);
    }
  }
}

/* 0051380b */
int32_t P71_CountNear(int32_t x, int32_t z) {
  const uint8_t *e = (const uint8_t *)A_00C56780;
  int32_t n = 0;
  for (int32_t i = 0; i < 0x40; i++, e += 0xb4) {
    if ((rd32(e, 0xc) & 0x10) != 0) {
      int32_t dx = Rnd(rdf(e, 0x84)) - x;
      int32_t dz = Rnd(rdf(e, 0x8c)) - z;
      int32_t d2 = (int32_t)((uint32_t)dx * (uint32_t)dx + (uint32_t)dz * (uint32_t)dz);
      if (d2 < P71_Near + P71_NearAdd) n++;
    }
  }
  if (n == 0) P71_NearAdd = (int32_t)((Rand_004D9078() & 3u) * P71_CELL);
  return n;
}

/* 00503c03 */
void P71_ScoreSetup(void) {
  P71_Tab974 = 0; P71_Tab2A40 = 0; P71_Ptr2A08 = 0;
  P71_V2A24 = 0; P71_V2A20 = 0; P71_V2A1C = 0; P71_V2A14 = 0;
  P8_012710a0 = 0; P69_ScoreCpy = 0;
  P71_S1271084 = 0; P71_S1271080 = 0; P71_S127107C = 0; P71_S1271074 = 0;
  P71_S127109C = 0; P71_S1271098 = 0; P71_S1271094 = 0; P71_S127108C = 0;
  int32_t mode = P62_Menu1271060, sel = P62_Menu1271064, r;
  switch (mode) {
  case 1:
    P8_012710a0 = 1;
    r = P42_GetHighScore(mode, sel); if (r != 0) P71_Tab2A40 = r;
    break;
  case 2: case 3: case 7:
    r = P42_GetHighScore(mode, sel); if (r != 0) P71_Tab2A40 = r;
    break;
  case 6: case 11:
    r = P42_GetHighScore(mode, sel); if (r != 0) P71_Tab2A40 = r;
    r = P42_GetHighScore(0xc, sel); if (r != 0) P71_Tab974 = r;
    P71_Ptr2A08 = 0x01271088u;
    break;
  default: break;
  }
}
