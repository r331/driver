#include "ported56.h"
#include "ported43.h"   /* v2.09: P43_FreeCnt/P43_FreeList/A_00C56780 — объекты образа данных (пешеходы) */
#include "ported7.h"
#include "ported125.h"
#include "ported147.h"
#include "ported71.h"
#include <math.h>
#include <string.h>

#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P71_Near")
#undef P71_Near
#pragma push_macro("P71_Near") /*gvi*/
#undef P71_Near /*gvi*/
int32_t P71_Near;
#pragma pop_macro("P71_Near") /*gvi*/
#pragma pop_macro("P71_Near")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P71_NearAdd")
#undef P71_NearAdd
#pragma push_macro("P71_NearAdd") /*gvi*/
#undef P71_NearAdd /*gvi*/
int32_t P71_NearAdd;
#pragma pop_macro("P71_NearAdd") /*gvi*/
#pragma pop_macro("P71_NearAdd")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P71_Tab974")
#undef P71_Tab974
#pragma push_macro("P71_Tab974") /*gvi*/
#undef P71_Tab974 /*gvi*/
int32_t P71_Tab974;
#pragma pop_macro("P71_Tab974") /*gvi*/
#pragma pop_macro("P71_Tab974")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P71_Tab2A40")
#undef P71_Tab2A40
#pragma push_macro("P71_Tab2A40") /*gvi*/
#undef P71_Tab2A40 /*gvi*/
int32_t P71_Tab2A40;
#pragma pop_macro("P71_Tab2A40") /*gvi*/
#pragma pop_macro("P71_Tab2A40")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P71_Ptr2A08")
#undef P71_Ptr2A08
#pragma push_macro("P71_Ptr2A08") /*gvi*/
#undef P71_Ptr2A08 /*gvi*/
uint32_t P71_Ptr2A08;
#pragma pop_macro("P71_Ptr2A08") /*gvi*/
#pragma pop_macro("P71_Ptr2A08")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P71_V2A24")
#undef P71_V2A24
#pragma push_macro("P71_V2A24") /*gvi*/
#undef P71_V2A24 /*gvi*/
int32_t P71_V2A24;
#pragma pop_macro("P71_V2A24") /*gvi*/
#pragma pop_macro("P71_V2A24")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P71_V2A20")
#undef P71_V2A20
#pragma push_macro("P71_V2A20") /*gvi*/
#undef P71_V2A20 /*gvi*/
int32_t P71_V2A20;
#pragma pop_macro("P71_V2A20") /*gvi*/
#pragma pop_macro("P71_V2A20")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P71_V2A1C")
#undef P71_V2A1C
#pragma push_macro("P71_V2A1C") /*gvi*/
#undef P71_V2A1C /*gvi*/
int32_t P71_V2A1C;
#pragma pop_macro("P71_V2A1C") /*gvi*/
#pragma pop_macro("P71_V2A1C")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P71_V2A14")
#undef P71_V2A14
#pragma push_macro("P71_V2A14") /*gvi*/
#undef P71_V2A14 /*gvi*/
int32_t P71_V2A14;
#pragma pop_macro("P71_V2A14") /*gvi*/
#pragma pop_macro("P71_V2A14")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P71_S1271084")
#undef P71_S1271084
#pragma push_macro("P71_S1271084") /*gvi*/
#undef P71_S1271084 /*gvi*/
int32_t P71_S1271084;
#pragma pop_macro("P71_S1271084") /*gvi*/
#pragma pop_macro("P71_S1271084")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P71_S1271080")
#undef P71_S1271080
#pragma push_macro("P71_S1271080") /*gvi*/
#undef P71_S1271080 /*gvi*/
int32_t P71_S1271080;
#pragma pop_macro("P71_S1271080") /*gvi*/
#pragma pop_macro("P71_S1271080")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P71_S127107C")
#undef P71_S127107C
#pragma push_macro("P71_S127107C") /*gvi*/
#undef P71_S127107C /*gvi*/
int32_t P71_S127107C;
#pragma pop_macro("P71_S127107C") /*gvi*/
#pragma pop_macro("P71_S127107C")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P71_S1271074")
#undef P71_S1271074
#pragma push_macro("P71_S1271074") /*gvi*/
#undef P71_S1271074 /*gvi*/
int32_t P71_S1271074;
#pragma pop_macro("P71_S1271074") /*gvi*/
#pragma pop_macro("P71_S1271074")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P71_S127109C")
#undef P71_S127109C
#pragma push_macro("P71_S127109C") /*gvi*/
#undef P71_S127109C /*gvi*/
int32_t P71_S127109C;
#pragma pop_macro("P71_S127109C") /*gvi*/
#pragma pop_macro("P71_S127109C")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P71_S1271098")
#undef P71_S1271098
#pragma push_macro("P71_S1271098") /*gvi*/
#undef P71_S1271098 /*gvi*/
int32_t P71_S1271098;
#pragma pop_macro("P71_S1271098") /*gvi*/
#pragma pop_macro("P71_S1271098")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P71_S1271094")
#undef P71_S1271094
#pragma push_macro("P71_S1271094") /*gvi*/
#undef P71_S1271094 /*gvi*/
int32_t P71_S1271094;
#pragma pop_macro("P71_S1271094") /*gvi*/
#pragma pop_macro("P71_S1271094")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P71_S127108C")
#undef P71_S127108C
#pragma push_macro("P71_S127108C") /*gvi*/
#undef P71_S127108C /*gvi*/
int32_t P71_S127108C;
#pragma pop_macro("P71_S127108C") /*gvi*/
#pragma pop_macro("P71_S127108C")
#endif

/* ported71.c — helpers for the 64-entry pool of walking objects A_00C56780 (0xb4-byte records;
   pedestrians: the game's own debug line (P120_DebugInfo) prints P43_FreeCnt — the in-use count of this pool — as
   "Number of pedestrians active = %d/%d" against 005759a4, the "Pedestrian Density" option (0..64); all writers in
   Game.exe sit in one module 00511e60..0051564f; RE_PROBE "ped": every in-use record has type 1 and the in-use
   count always equals P43_FreeCnt.  Older "particle" / "dust" names in ported71.h/102/106/114 mean these
   pedestrians), plus the per-mode high-score setup P71_ScoreSetup.
   The map is a grid of 1500-unit cells (P71_CELL); a walker on an edge stays 350 or 550 units from the
   cell centre line depending on whether the neighbouring cell is walkable. */
#define PED_COUNT       0x40     /* records in A_00C56780 */
#define PED_SIZE        0xb4
#define PED_FLAGS       0x0c     /* u32 flags */
#define PED_HEADING     0x14     /* int32: course angle written by P71_Course */
#define PED_TURN        0x18     /* int32: |turn| still to do */
#define PED_STATE       0x1c     /* int32: 3 = TODO(RE): unsure (excluded by P71_InitNear) */
#define PED_EDGE        0x38     /* int32: cell edge / direction 1, 2, 4, 8 (see P71_EdgeA) */
#define PED_ANGLE       0x5e     /* int16: current facing */
#define PED_DIR_X       0x64     /* float: direction x */
#define PED_DIR_Z       0x6c     /* float: direction z */
#define PED_POS_X       0x84     /* float: world x */
#define PED_POS_Z       0x8c     /* float: world z */
#define PEDF_ACTIVE     0x0010   /* record in use */
#define PEDF_EXCL       0x0880   /* either bit excludes the record from P71_InitNear. TODO(RE): unsure */
#define PEDF_OPEN       0x0100   /* set by set_open: the neighbouring cell on the walker's edge is walkable */
#define PEDF_TURN_LEFT  0x1000   /* P71_Course: turn with decreasing angle */
#define PEDF_TURN_RIGHT 0x2000
#define EDGE_NEAR       0x15e    /* 350: offset from the cell line when the neighbour is blocked */
#define EDGE_FAR        0x226    /* 550: offset when it is open */
#define NEAR_RADIUS     0x2ee    /* 750: P71_InitNear distance (octagonal metric) */
/* CAR_* offsets used below: 0x40/0x48 = CAR_VEL x / z, 0xc8/0xd0 = CAR_POS_X / Z (carfields.h). */

static int32_t rd32(const uint8_t *p, uint32_t o) { int32_t v; memcpy(&v, p + o, 4); return v; }
static void    wr32(uint8_t *p, uint32_t o, int32_t v) { memcpy(p + o, &v, 4); }
static float   rdf(const uint8_t *p, uint32_t o) { float v; memcpy(&v, p + o, 4); return v; }
/* fistp в режиме по умолчанию: округление к ближайшему чётному */
static int32_t Rnd(float v) { return (int32_t)lrintf(v); }

#define P71_CELL 0x5dc

/* общая часть 005144d4/00514779: клетка (x, z) по q[0], q[2] (x87: __ftol усекает) и проходимость четырёх соседних клеток */
/* Snaps point q to its map cell (x and z cell origin in *ix, *iz; z axis is flipped) and reads the
   walkability of the four neighbours: s[0] = z - 1 cell, s[1] = z + 1, s[2] = x - 1, s[3] = x + 1
   (P47_Fn51B111 < 0 = not walkable, TODO(RE): exact meaning of its value). */
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

/* Sets (open != 0) or clears PEDF_OPEN in the walker's flags (inlined in the original). */
static void set_open(uint8_t *p, int open) {
  uint32_t f = (uint32_t)rd32(p, PED_FLAGS);
  f = open ? (f | PEDF_OPEN) : (f & 0xfffffeffu);
  wr32(p, PED_FLAGS, (int32_t)f);
}

/* 005144d4 */
/* P71_EdgeA — Game.exe 005144d4.  Places walker p (target point q, x/z at q[0]/q[2]) on the line along
   its edge PED_EDGE (1 / 2 = moving along z toward the z-1 / z+1 neighbour, 4 / 8 = along x toward
   x+1 / x-1): the coordinate across is set 350 units inside if that neighbour is blocked (flag cleared),
   550 units toward it if walkable (flag set).  Other edge values: nothing. */
void P71_EdgeA(uint8_t *p, float *q) {
  int32_t x, z; int16_t s[4];
  cell_state(q, &x, &z, s);
  switch (rd32(p, PED_EDGE)) {
  case 1:
    if (s[0] < 0) { set_open(p, 0); q[2] = (float)(z + EDGE_NEAR); } else { set_open(p, 1); q[2] = (float)(z - EDGE_FAR); }
    break;
  case 2:
    if (s[1] < 0) { set_open(p, 0); q[2] = (float)(z - EDGE_NEAR); } else { set_open(p, 1); q[2] = (float)(z + EDGE_FAR); }
    break;
  case 4:
    if (s[3] < 0) { set_open(p, 0); q[0] = (float)(x - EDGE_NEAR); } else { set_open(p, 1); q[0] = (float)(x + EDGE_FAR); }
    break;
  case 8:
    if (s[2] < 0) { set_open(p, 0); q[0] = (float)(x + EDGE_NEAR); } else { set_open(p, 1); q[0] = (float)(x - EDGE_FAR); }
    break;
  default: break;
  }
}

/* 00514779 */
/* P71_EdgeB — Game.exe 00514779.  Like P71_EdgeA but moves q to a corner point of the cell (both x and
   z set, 350 or 550 from the cell lines depending on the neighbour) and does not touch the flags.
   Note edges 4 and 8 test the x-1 / x+1 neighbours the other way round from P71_EdgeA (kept as is). */
void P71_EdgeB(uint8_t *p, float *q) {
  int32_t x, z; int16_t s[4];
  cell_state(q, &x, &z, s);
  switch (rd32(p, PED_EDGE)) {
  case 1:
    if (s[0] < 0) { q[0] = (float)(x - EDGE_NEAR); q[2] = (float)(z + EDGE_NEAR); } else { q[0] = (float)(x - EDGE_FAR); q[2] = (float)(z - EDGE_FAR); }
    break;
  case 2:
    if (s[1] < 0) { q[0] = (float)(x + EDGE_NEAR); q[2] = (float)(z - EDGE_NEAR); } else { q[0] = (float)(x + EDGE_FAR); q[2] = (float)(z + EDGE_FAR); }
    break;
  case 4:
    if (s[2] < 0) { q[0] = (float)(x + EDGE_FAR); q[2] = (float)(z - EDGE_FAR); } else { q[0] = (float)(x - EDGE_NEAR); q[2] = (float)(z - EDGE_NEAR); }
    break;
  case 8:
    if (s[3] < 0) { q[0] = (float)(x - EDGE_FAR); q[2] = (float)(z + EDGE_FAR); } else { q[0] = (float)(x + EDGE_NEAR); q[2] = (float)(z + EDGE_NEAR); }
    break;
  default: break;
  }
}

/* 00514165 */
/* P71_Course — Game.exe 00514165.  New course for walker p from its direction vector: heading
   u = -atan2(dir) - 90 deg; the signed difference d to the current facing (wrapped to -2048..2047)
   sets the turn-direction flag (0x1000 for d < 0, else 0x2000 — never cleared here), PED_HEADING = u
   and PED_TURN = |d|. */
void P71_Course(uint8_t *p) {
  int32_t a = Rnd(rdf(p, PED_DIR_X));
  int32_t b = Rnd(rdf(p, PED_DIR_Z));
  int32_t ang = P44_Atan2(b, a);
  int32_t u = (int32_t)(((uint32_t)(-ang) - 0x400u) & 0xfffu);   /* -ang - ANG_90, wrapped */
  int16_t cur; memcpy(&cur, p + PED_ANGLE, 2);
  int32_t d = (((u - (int32_t)cur) + 0x800) & 0xfff) - 0x800;    /* shortest signed turn */
  uint32_t f = (uint32_t)rd32(p, PED_FLAGS);
  if (d < 0) { f |= PEDF_TURN_LEFT; d = -d; } else { f |= PEDF_TURN_RIGHT; }
  wr32(p, PED_FLAGS, (int32_t)f);
  wr32(p, PED_HEADING, u);
  wr32(p, PED_TURN, d);
}

/* 00515bf1 */
/* P71_InPlanes — Game.exe 00515bf1.  1 if walker p's (x, z) is inside all four half-planes q[i] =
   {nx, -, nz, d} (nx * x + nz * z <= d), else 0. */
int32_t P71_InPlanes(const uint8_t *p, const float *q) {
  float x = rdf(p, PED_POS_X), z = rdf(p, PED_POS_Z);
  for (int i = 0; i < 4; i++) {
    float s = (float)((long double)x * q[i * 4] + (long double)z * q[i * 4 + 2]);
    if (s > q[i * 4 + 3]) return 0;
  }
  return 1;
}

/* 00515cca */
/* P71_FaceCar — Game.exe 00515cca.  Direction for walker p to dodge car: h = the car's direction of
   travel (atan2 of its velocity); returns h - 90 deg if the walker is on the left/positive side of
   that line (relative angle > 0), else h + 90 deg — i.e. perpendicular, away from the car's path.
   TODO(RE): confirm "dodge" (it is the use the angles suggest). */
int32_t P71_FaceCar(const uint8_t *p, const uint8_t *car) {
  int32_t h = P44_Atan2(rd32(car, 0x40) >> 8, rd32(car, 0x48) >> 8) & 0xfff;
  float dz = rdf(p, PED_POS_Z) - (float)rd32(car, 0xd0);
  float dx = rdf(p, PED_POS_X) - (float)rd32(car, 0xc8);
  int32_t y = Rnd(dz), x = Rnd(dx);
  int32_t t = (((P44_Atan2(x, y) - h) + 0x800) & 0xfff) - 0x800;
  return (t > 0) ? ((h - 0x400) & 0xfff) : ((h + 0x400) & 0xfff);
}

/* 0051551e */
/* P71_InitNear — Game.exe 0051551e.  For every active walker (not state 3, no 0x880 flags) within 750
   units of car (octagonal distance max + min/2), calls P62_ParticleInit(walker, car) (TODO(RE): unsure
   what that starts — the reaction to an approaching car?). */
void P71_InitNear(uint8_t *car) {
  uint8_t *e = (uint8_t *)A_00C56780;
  for (int32_t i = 0; i < PED_COUNT; i++, e += PED_SIZE) {
    uint32_t f = (uint32_t)rd32(e, PED_FLAGS);
    if ((f & PEDF_ACTIVE) != 0 && rd32(e, PED_STATE) != 3 && (f & PEDF_EXCL) == 0) {
      int32_t dx = Rnd(rdf(e, PED_POS_X)) - rd32(car, 0xc8); if (dx < 0) dx = -dx;
      int32_t dz = Rnd(rdf(e, PED_POS_Z)) - rd32(car, 0xd0); if (dz < 0) dz = -dz;
      int32_t d = (dx < dz) ? dz + dx / 2 : dx + dz / 2;
      if (d <= NEAR_RADIUS) P62_ParticleInit(e, car);
    }
  }
}

/* 0051380b */
/* P71_CountNear — Game.exe 0051380b.  Number of active walkers whose squared distance to (x, z) is below
   P71_Near + P71_NearAdd (32-bit wrapping arithmetic as in the original).  When none is found the
   random extra radius P71_NearAdd is re-rolled to 0 / 1500 / 3000 / 4500. */
int32_t P71_CountNear(int32_t x, int32_t z) {
  const uint8_t *e = (const uint8_t *)A_00C56780;
  int32_t n = 0;
  for (int32_t i = 0; i < PED_COUNT; i++, e += PED_SIZE) {
    if ((rd32(e, PED_FLAGS) & PEDF_ACTIVE) != 0) {
      int32_t dx = Rnd(rdf(e, PED_POS_X)) - x;
      int32_t dz = Rnd(rdf(e, PED_POS_Z)) - z;
      int32_t d2 = (int32_t)((uint32_t)dx * (uint32_t)dx + (uint32_t)dz * (uint32_t)dz);
      if (d2 < P71_Near + P71_NearAdd) n++;
    }
  }
  if (n == 0) P71_NearAdd = (int32_t)((Rand_004D9078() & 3u) * P71_CELL);
  return n;
}

/* 00503c03 */
/* P71_ScoreSetup — Game.exe 00503c03.  Resets the score / record words of the current run, then loads
   the high score to beat for the selected game mode P62_Menu1271060 and entry P62_Menu1271064 into
   P71_Tab2A40: modes 1 (also sets P8_012710a0), 2, 3, 7; modes 6 and 11 additionally load table 0xc's
   record into P71_Tab974 and point P71_Ptr2A08 at 01271088.  A zero result leaves the field 0.
   Modes = high-score table ids (see P141_HsSetup): 1 Trail Blazer, 2 Cross Town Checkpoint, 3 Survival,
   7 Carnage, 0xb Dirt Track Time Trial (0xc its best lap), 6 Dirt Track Practice (menu 0054a870; loads table 0xc
   for the best lap only).  Driving Games menu 0054a968: 4 Pursuit, 5 Getaway, 2, 1, 3, 6, 7 (RE_PROBE menu walk). */
void P71_ScoreSetup(void) {
  P71_Tab974 = 0; P71_Tab2A40 = 0; P71_Ptr2A08 = 0;
  P71_V2A24 = 0; P71_V2A20 = 0; P71_V2A1C = 0; P71_V2A14 = 0;
  P8_012710a0 = 0; P69_ScoreCpy = 0;
  P71_S1271084 = 0; P71_S1271080 = 0; P71_S127107C = 0; P71_S1271074 = 0;
  P71_S127109C = 0; P71_S1271098 = 0; P71_S1271094 = 0; P71_S127108C = 0;
#ifndef RE_HOOK_BUILD
  /* v1.92: native-псевдонимы тех же слов (00b32a10 — P147_Rec2A10, 01271070.. — P125_MrkSave/P56_Blk11, 012710a0 — P56_Blk11[16]) */
  P147_Rec2A10[1] = 0; P147_Rec2A10[3] = 0; P147_Rec2A10[4] = 0; P147_Rec2A10[5] = 0;
  P125_MrkSave[1] = 0; P125_MrkSave[3] = 0; P125_MrkSave[4] = 0; P125_MrkSave[5] = 0;
  P56_Blk11[5] = 0; P56_Blk11[7] = 0; P56_Blk11[8] = 0; P56_Blk11[9] = 0;
  P56_Blk11[11] = 0; P56_Blk11[13] = 0; P56_Blk11[14] = 0; P56_Blk11[15] = 0; P56_Blk11[16] = 0;
#endif
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
