/* Leaf routines: identifier parsing, PSX-style fixed-point maths (spring step, quaternion to
   matrix, curve tables), view cone test, direction table, frustum row spans, radar/map
   projection, view limits, finish fade and icon quad.  32-bit wrap-around arithmetic is kept. */
/* Пачка листовых функций — восстановлено из Game.exe (004a522a, 004e0fd4, 004dab80, 004da76a, 004da5e0, 00496569, 00490591,
   004f2f2a, 004f4c3d, 004b9835, 005061c9, 004094e3, 004e5284, 004ab95c, 00507672). */
#include "ported94.h"
#include "reptr.h"
#include "ported4.h"
#include "ported6.h"
#include "ported11.h"
#include "ported14.h"
#include "ported19.h"
#include "ported43.h"
#include "ported56.h"
#include "ported57.h"
#include "ported58.h"
#include "ported59.h"
#include "ported60.h"
#include "ported62.h"
#include "ported63.h"
#include "menustate.h"
#include "smallfuncs.h"
#include "smallfuncs2.h"
#include <string.h>

#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P94_RadarK")
#undef P94_RadarK
#pragma push_macro("P94_RadarK") /*gvi*/
#undef P94_RadarK /*gvi*/
float P94_RadarK;
#pragma pop_macro("P94_RadarK") /*gvi*/
#pragma pop_macro("P94_RadarK")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P94_MapW")
#undef P94_MapW
#pragma push_macro("P94_MapW") /*gvi*/
#undef P94_MapW /*gvi*/
int32_t P94_MapW;
#pragma pop_macro("P94_MapW") /*gvi*/
#pragma pop_macro("P94_MapW")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P94_MapH")
#undef P94_MapH
#pragma push_macro("P94_MapH") /*gvi*/
#undef P94_MapH /*gvi*/
int32_t P94_MapH;
#pragma pop_macro("P94_MapH") /*gvi*/
#pragma pop_macro("P94_MapH")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P94_MapX0")
#undef P94_MapX0
#pragma push_macro("P94_MapX0") /*gvi*/
#undef P94_MapX0 /*gvi*/
int32_t P94_MapX0;
#pragma pop_macro("P94_MapX0") /*gvi*/
#pragma pop_macro("P94_MapX0")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P94_MapY0")
#undef P94_MapY0
#pragma push_macro("P94_MapY0") /*gvi*/
#undef P94_MapY0 /*gvi*/
int32_t P94_MapY0;
#pragma pop_macro("P94_MapY0") /*gvi*/
#pragma pop_macro("P94_MapY0")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P94_FadeDir")
#undef P94_FadeDir
#pragma push_macro("P94_FadeDir") /*gvi*/
#undef P94_FadeDir /*gvi*/
int32_t P94_FadeDir;
#pragma pop_macro("P94_FadeDir") /*gvi*/
#pragma pop_macro("P94_FadeDir")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P94_FadeVal")
#undef P94_FadeVal
#pragma push_macro("P94_FadeVal") /*gvi*/
#undef P94_FadeVal /*gvi*/
int32_t P94_FadeVal;
#pragma pop_macro("P94_FadeVal") /*gvi*/
#pragma pop_macro("P94_FadeVal")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P94_FadePos")
#undef P94_FadePos
#pragma push_macro("P94_FadePos") /*gvi*/
#undef P94_FadePos /*gvi*/
float P94_FadePos;
#pragma pop_macro("P94_FadePos") /*gvi*/
#pragma pop_macro("P94_FadePos")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P94_FadeSpeed")
#undef P94_FadeSpeed
#pragma push_macro("P94_FadeSpeed") /*gvi*/
#undef P94_FadeSpeed /*gvi*/
float P94_FadeSpeed;
#pragma pop_macro("P94_FadeSpeed") /*gvi*/
#pragma pop_macro("P94_FadeSpeed")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P94_IconRec")
#undef P94_IconRec
#pragma push_macro("P94_IconRec") /*gvi*/
#undef P94_IconRec /*gvi*/
uint32_t P94_IconRec;
#pragma pop_macro("P94_IconRec") /*gvi*/
#pragma pop_macro("P94_IconRec")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P94_QuadPage")
#undef P94_QuadPage
#pragma push_macro("P94_QuadPage") /*gvi*/
#undef P94_QuadPage /*gvi*/
uint8_t P94_QuadPage;
#pragma pop_macro("P94_QuadPage") /*gvi*/
#pragma pop_macro("P94_QuadPage")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P94_Quad")
#undef P94_Quad
#pragma push_macro("P94_Quad") /*gvi*/
#undef P94_Quad /*gvi*/
p94_quad_t P94_Quad;
#pragma pop_macro("P94_Quad") /*gvi*/
#pragma pop_macro("P94_Quad")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P94_DirCnt")
#undef P94_DirCnt
#pragma push_macro("P94_DirCnt") /*gvi*/
#undef P94_DirCnt /*gvi*/
int32_t P94_DirCnt;
#pragma pop_macro("P94_DirCnt") /*gvi*/
#pragma pop_macro("P94_DirCnt")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P94_DirTab")
#undef P94_DirTab
#pragma push_macro("P94_DirTab") /*gvi*/
#undef P94_DirTab /*gvi*/
p94_dirtab_t P94_DirTab;
#pragma pop_macro("P94_DirTab") /*gvi*/
#pragma pop_macro("P94_DirTab")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P94_CurveA")
#undef P94_CurveA
#pragma push_macro("P94_CurveA") /*gvi*/
#undef P94_CurveA /*gvi*/
p94_curveA_t P94_CurveA;
#pragma pop_macro("P94_CurveA") /*gvi*/
#pragma pop_macro("P94_CurveA")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P94_CurveB")
#undef P94_CurveB
#pragma push_macro("P94_CurveB") /*gvi*/
#undef P94_CurveB /*gvi*/
p94_curveB_t P94_CurveB;
#pragma pop_macro("P94_CurveB") /*gvi*/
#pragma pop_macro("P94_CurveB")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P94_CurveC")
#undef P94_CurveC
#pragma push_macro("P94_CurveC") /*gvi*/
#undef P94_CurveC /*gvi*/
p94_curveB_t P94_CurveC;
#pragma pop_macro("P94_CurveC") /*gvi*/
#pragma pop_macro("P94_CurveC")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P94_WobB")
#undef P94_WobB
#pragma push_macro("P94_WobB") /*gvi*/
#undef P94_WobB /*gvi*/
int32_t P94_WobB;
#pragma pop_macro("P94_WobB") /*gvi*/
#pragma pop_macro("P94_WobB")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P94_WobK")
#undef P94_WobK
#pragma push_macro("P94_WobK") /*gvi*/
#undef P94_WobK /*gvi*/
float P94_WobK;
#pragma pop_macro("P94_WobK") /*gvi*/
#pragma pop_macro("P94_WobK")
#endif
#ifndef RE_HOOK_BUILD
#pragma push_macro("P94_WobA") /*gvi*/
#undef P94_WobA /*gvi*/
int32_t P94_WobA = 10;   /* 00553a18: начальное значение из .data */
#pragma pop_macro("P94_WobA") /*gvi*/
#pragma push_macro("P94_WobC") /*gvi*/
#undef P94_WobC /*gvi*/
int32_t P94_WobC = 5;    /* 00553a1c */
#pragma pop_macro("P94_WobC") /*gvi*/
#endif

/* умножение и сдвиг как у 32-битного imul/sar (с переполнением по модулю 2^32) */
/* mul — int32 multiply with 32-bit wrap-around (imul). */
static int32_t mul(int32_t a, int32_t b) { return (int32_t)((uint32_t)a * (uint32_t)b); }
/* fx — 20.12 fixed-point multiply with rounding: (a * b + 0x800) >> 12, wrap-around kept. */
static int32_t fx(int32_t a, int32_t b) { return (int32_t)((uint32_t)mul(a, b) + 0x800u) >> 12; }
#include "memrw.h"
#include "carfields.h"
#include "fixmath.h"
/* rd16 — Unaligned int16 read. */
static int16_t rd16(const uint8_t *p) { int16_t v; memcpy(&v, p, 2); return v; }
/* wrf — Store a float into a uint32 slot (bit copy). */

/* P94_ReadIdent — Game.exe 004a522a, cdecl.  Copy an identifier [A-Z0-9_] from src to dst (NUL-terminated), upper-casing src in place.
   Returns the first character after it; an identifier may not start with a digit (dst = ""). */
uint8_t *P94_ReadIdent(uint8_t *src, uint8_t *dst) {
  if (*src >= '0' && *src <= '9') { *dst = 0; return src; }   /* имя не может начинаться с цифры */
  for (; *src != 0; src++) {
    if (*src > 0x60 && *src < 0x7b) *src = (uint8_t)(*src - 0x20);   /* исходная строка тоже переводится в заглавные */
    if ((*src >= 'A' && *src <= 'Z') || (*src >= '0' && *src <= '9') || *src == '_') *dst = *src;
    else break;
    dst++;
  }
  *dst = 0;
  return src;
}

/* 004e0fd4: obj +8/+0xe/+0x14 — нормаль (int16, шаг 6), st +0x30/+0x40/+0x50 — векторы int32, +0x60 — режим */
/* P94_SpringStep — Game.exe 004e0fd4, cdecl.  One damped spring step of a body against a surface: obj int16 normal at +8/+0xe/+0x14 (stride
   6), st int32 vectors +0x30 (position), +0x40 (offset), +0x50 (velocity), +0x60 mode.
   Velocity = vel * 0x6e + (normal * (dot(normal, vel) * 0x1b8) - offset << 7) >> 12; mode 1 also
   subtracts offset / 8.  Writes the force/position copies to obj +0x68 / +0x58 (CAR_DANGVEL_PEND /
   CAR_DVEL_PEND for car records).  TODO(RE): unsure of the physical meaning of the constants. */
void P94_SpringStep(uint8_t *obj, uint8_t *st) {
  int32_t dot = mul(rd16(obj + 8), rd32(st + 0x50)) + mul(rd16(obj + 0xe), rd32(st + 0x54)) + mul(rd16(obj + 0x14), rd32(st + 0x58));
  int32_t d = mul((int32_t)((uint32_t)dot + 0x800u) >> 12, 0x1b8);
  for (int32_t i = 2; i >= 0; i--) {
    int32_t g = rd32(st + 0x40 + i * 4);
    int32_t v = mul(rd32(st + 0x50 + i * 4), 0x6e) + ((int32_t)((uint32_t)mul(rd16(obj + 8 + i * 6), d) - ((uint32_t)g << 7) + 0x800u) >> 12);
    wr32(st + 0x50 + i * 4, v);
    if (rd32(st + 0x60) == 1) wr32(st + 0x50 + i * 4, rd32(st + 0x50 + i * 4) - (g / 8));
    wr32(obj + 0x68 + i * 4, rd32(st + 0x50 + i * 4));
    wr32(obj + 0x58 + i * 4, rd32(st + 0x30 + i * 4));
  }
}

/* 004dab80: положение (>>8) и угловая скорость, повёрнутая кватернионом src+0xc..0x18 */
/* P94_PackState — Game.exe 004dab80, cdecl.  Pack a rigid-body state for replay/network: position >> 8, the angular vector (rounded >> 13)
   rotated by the quaternion src+0xc..0x18 as a quaternion product; out[7..12] = 0. */
void P94_PackState(const uint8_t *src, int32_t *out) {
  out[0] = rd32(src + 0x1c) >> 8;
  out[1] = rd32(src + 0x20) >> 8;
  out[2] = rd32(src + 0x24) >> 8;
  int32_t a = (int32_t)((uint32_t)rd32(src + 0x28) + 0x1000u) >> 13;
  int32_t b = (int32_t)((uint32_t)rd32(src + 0x2c) + 0x1000u) >> 13;
  int32_t c = (int32_t)((uint32_t)rd32(src + 0x30) + 0x1000u) >> 13;
  int32_t qx = rd32(src + 0xc), qy = rd32(src + 0x10), qz = rd32(src + 0x14), qw = rd32(src + 0x18);
  out[3] = (int32_t)((uint32_t)(-mul(qy, c) + mul(qz, b)) + 0x800u + (uint32_t)mul(qw, a)) >> 12;
  out[4] = (int32_t)((uint32_t)(mul(qx, c) - mul(qz, a)) + 0x800u + (uint32_t)mul(qw, b)) >> 12;
  out[5] = (int32_t)((uint32_t)(-mul(qx, b) + mul(qy, a)) + 0x800u + (uint32_t)mul(qw, c)) >> 12;
  out[6] = (int32_t)((uint32_t)(-mul(qx, a) - mul(qy, b) - mul(qz, c)) + 0x800u) >> 12;
  for (int i = 7; i < 13; i++) out[i] = 0;
}

/* P94_QuatToMat — Game.exe 004da76a, cdecl.  Quaternion (x, y, z, w in 1.12) -> 3x3 int16 rotation matrix (4096 = 1.0); products rounded >> 11
   (i.e. 2*q*q in 20.12). */
/* PS1: LongQuaternion2Matrix @ 0x0001B380 (olink9/driver1-decomp@5bb6cda, high) */
void P94_QuatToMat(const int32_t *q, int16_t *m) {
  #define QQ(a, b) ((int16_t)((int32_t)((uint32_t)mul(q[a], q[b]) + 0x400u) >> 11))
  int16_t yy = QQ(1, 1), zz = QQ(2, 2), xx = QQ(0, 0);
  int16_t zw = QQ(2, 3), xy = QQ(0, 1), xz = QQ(0, 2), yw = QQ(1, 3), xw = QQ(0, 3), yz = QQ(1, 2);
  #undef QQ
  m[0] = (int16_t)(0x1000 - (int16_t)(yy + zz));
  m[1] = (int16_t)(xy - zw);
  m[2] = (int16_t)(xz + yw);
  m[3] = (int16_t)(xy + zw);
  m[4] = (int16_t)(0x1000 - (int16_t)(xx + zz));
  m[5] = (int16_t)(yz - xw);
  m[6] = (int16_t)(xz - yw);
  m[7] = (int16_t)(yz + xw);
  m[8] = (int16_t)(0x1000 - (int16_t)(xx + yy));
}

/* P94_InitCurves — Game.exe 004da5e0, cdecl.  Build three lookup curves: P94_CurveA[i] = (i/4096)^6 (0..0x1003), and for 160 angle steps
   P94_CurveB (a modulated sine) and P94_CurveC = CurveB^5.  TODO(RE): unsure what uses them. */
void P94_InitCurves(void) {
  for (int32_t i = 0; i < 0x1004; i++) {
    int32_t t = fx(i, i);
    t = fx(i, t);
    P94_CurveA[i] = (int16_t)fx(t, t);
  }
  for (int32_t i = 0x9f; i >= 0; i--) {
    int32_t k = i << 5;
    int32_t s = P59_Sin[(k << 1) & 0xfff];
    int32_t v = mul(fx(s, s), 0x428);
    v = ((int32_t)((uint32_t)v + 0x800u) >> 12) + 0x1000;
    int32_t c = ((int32_t)((uint32_t)mul(P59_Sin[((k << 3) + 0x400) & 0xfff], 0x51) + 0x800u) >> 12) + 0xfae;
    v = fx(v, c);
    P94_CurveB[i] = (int16_t)fx(v, P59_Sin[k & 0xfff]);
    int32_t b = P94_CurveB[i];
    int32_t b2 = fx(b, b);
    P94_CurveC[i] = (int16_t)fx(b, fx(b2, b2));
  }
}

/* 00496569: машина впереди игрока в секторе ±60° (по курсу P94_HeadingI) и ближе 5000 по осям */
/* P94_InViewCone — Game.exe 00496569, cdecl.  1 if `car` is in front of the player within +-60 degrees of heading P94_HeadingI, within 5000 on
   both axes and inside three half-planes (front and the two cone sides); else 0. */
int32_t P94_InViewCone(const uint8_t *car) {
  uint32_t da = (uint32_t)(P94_HeadingI - rd32(car + CAR_HEADING)) & ANG_MASK;
  if (da < 0x69c || da > 0x964) return 0;
  int32_t dx = rd32(car + CAR_POS_X) - P59_PosX, dz = rd32(car + CAR_POS_Z) - P59_PosZ;
  if (dx < -5000 || dx > 5000 || dz < -5000 || dz > 5000) return 0;
  int32_t h = P94_HeadingI;
  if (mul(dx, P59_Sin[h & 0xfff]) + mul(dz, P59_Sin[(h + 0x400) & 0xfff]) < -0x384000) return 0;
  if (mul(dx, P59_Sin[(h + 0x3ce) & 0xfff]) + mul(dz, P59_Sin[(h + 0x7ce) & 0xfff]) < -0x258000) return 0;
  if (mul(dx, P59_Sin[(h - 0x3ce) & 0xfff]) + mul(dz, P59_Sin[(h + 0x32) & 0xfff]) < -0x258000) return 0;
  return 1;
}

/* 00490591: различные смещения клетки (sin·23/4096, cos·23/4096) по 128 направлениям */
/* P94_BuildDirTab — Game.exe 00490591, cdecl.  Build the distinct map-cell offsets (sin * 23 / 4096, cos * 23 / 4096) of 128 headings into
   P94_DirTab {dx, dz, dx + dz * map width}; P94_DirCnt = count. */
void P94_BuildDirTab(void) {
  int32_t tmp[240 * 2];
  P94_DirCnt = 0;
  for (uint32_t a = 0; (int32_t)a < 0x1000; a += 0x20) {
    int32_t x = mul(P59_Sin[a & 0xfff], 0x17) / 4096;
    int32_t z = mul(P59_Sin[(a + 0x400) & 0xfff], 0x17) / 4096;
    int32_t i = 0;
    while (i < P94_DirCnt && (x != tmp[i * 2] || z != tmp[i * 2 + 1])) i++;
    if (i == P94_DirCnt) { tmp[P94_DirCnt * 2] = x; tmp[P94_DirCnt * 2 + 1] = z; P94_DirCnt++; }
  }
  for (int32_t i = 0; i < P94_DirCnt; i++) {
    P94_DirTab[i][0] = tmp[i * 2];
    P94_DirTab[i][1] = tmp[i * 2 + 1];
    P94_DirTab[i][2] = tmp[i * 2] + mul(tmp[i * 2 + 1], P62_MapW);
  }
}

/* 004f2f2a: формат строк FRUSTRUM.DAT: out[0] — первая непустая строка (−1), out[1] — число непустых строк,
   out[2+2r] — первый ненулевой столбец строки r (−1), out[3+2r] — число ненулевых клеток от него до конца строки */
/* P94_RowSpans — Game.exe 004f2f2a, cdecl.  Convert the 31x31 FRUSTRUM.DAT mask into row spans: out[0] first non-empty row (-1), out[1]
   number of non-empty rows, then per row {first set column (-1), set cells from there to the end}. */
void P94_RowSpans(int16_t *out, const uint8_t *grid) {
  out[1] = 0; out[0] = -1;
  int16_t *p = out;
  for (int32_t r = 0; r < 0x1f; r++) {
    const uint8_t *row = grid + r * 0x1f;
    int16_t *s = p + 2;
    *s = -1; p[3] = 0;
    for (int32_t c = 0; c < 0x1f; c++) {
      if (row[c] != 0) {
        if (out[0] == -1) out[0] = (int16_t)r;
        out[1]++;
        *s = (int16_t)c;
        while (c < 0x1f) { if (row[c++] != 0) p[3]++; }
      }
    }
    p = s;
  }
}

/* 004f4c3d: октагональное расстояние от игрока до ближайшего активного объекта радара (10 записей по 0x34) */
/* P94_NearestObjDist — Game.exe 004f4c3d, cdecl.  Octagonal distance (max + min/2) from the player to the nearest active of the 10 radar
   objects (P58_Objs, flag bit 0); 0x7fffffff if none. */
int32_t P94_NearestObjDist(void) {
  int32_t best = 0x7fffffff;
  for (int i = 0; i < 10; i++) {
    const uint8_t *o = P58_Objs[i];
    if ((rd32(o + 0x10) & 1) == 0) continue;
    int32_t dx = rd32(o + 0x14) - P59_PosX, dz = rd32(o + 0x1c) - P59_PosZ;
    int32_t ax = dx < 0 ? -dx : dx, az = dz < 0 ? -dz : dz, d;
    if (ax < az) d = az + ax / 2;
    else d = ax + az / 2;
    if (d < best) best = d;
  }
  return best;
}

/* 004b9835: смещение «качания» по трём фазам таблицы синусов */
/* P94_Wobble — Game.exe 004b9835, cdecl.  Camera wobble offset from three sine phases (advanced by 3, 5, 7 when step != 0): x/z sums of two
   cos/sin terms scaled by 10 * sin(phase C); y = 0. */
void P94_Wobble(float *out, int32_t step) {
  if (step != 0) {
    P94_WobA = (P94_WobA + 3) & 0xfff;
    P94_WobB = (P94_WobB + 5) & 0xfff;
    P94_WobC = (P94_WobC + 7) & 0xfff;
  }
  float a = P43_Sin[P94_WobA], b = P43_Sin[P94_WobB];
  P94_WobK = P43_Sin[P94_WobC] * 10.0f;                 /* 0054612c = 10.0 */
  out[0] = P94_WobK * (P43_Sin[(P94_WobA + 0x400) & 0xfff] + P43_Sin[(P94_WobB + 0x400) & 0xfff]);
  out[1] = 0.0f;
  out[2] = -P94_WobK * (a + b);
}

/* 005061c9: мировые x,z → экран радара (поворот по курсу игрока, если не включён «север вверху» 00bdfa54) */
/* P94_RadarXY — Game.exe 005061c9, cdecl.  World (x, z) -> radar screen position: relative to the player (half-cell bias 750 cancels out
   except for rounding), rotated by the player heading unless "north up" (00bdfa54) is set, scaled
   by P63_Scale * P94_RadarK around the radar centre. */
void P94_RadarXY(float x, float z, float *ox, float *oy) {
  uint32_t i = (uint32_t)(-(int32_t)P94_Heading) & 0xfff;
  float s = P43_Sin[i], c = P43_Sin[i + 0x400];
  if (MenuOptBDFA54 != 0) { s = P43_Sin[0]; c = P43_Sin[0x400]; }
  float dx = (x + 750.0f) - ((float)P59_PosX + 750.0f);          /* 00546a34 = 750.0 */
  float dz = (-z - 750.0f) - ((float)-P59_PosZ - 750.0f);
  float y = (dz * c + dx * s) * P63_Scale * P94_RadarK + P56_F573FA4;
  *ox = (dx * c - dz * s) * P63_Scale * P94_RadarK + P56_F573FA0;
  *oy = y;
}

/* 004094e3: пределы числа частиц (0..64) и дальностей прорисовки (15000..45000, 15000..42000) */
/* P94_ClampView — Game.exe 004094e3, cdecl.  Clamp the particle limit to 0..64 and the far distances 01270c24 to 15000..45000 and 0125f3f8
   to 15000..42000 (the detail preset ranges). */
void P94_ClampView(void) {
  int32_t n = P60_PartLimit < 0x41 ? P60_PartLimit : 0x40;
  P60_PartLimit = n < 0 ? 0 : n;
  float f = P11_01270c24 <= 45000.0f ? P11_01270c24 : 45000.0f;
  P11_01270c24 = 15000.0f <= f ? f : 15000.0f;
  f = P11_0125f3f8 <= 42000.0f ? P11_0125f3f8 : 42000.0f;
  P11_0125f3f8 = 15000.0f <= f ? f : 15000.0f;
}

/* 004e5284: мигание (0..255 шагом 12) и проезд камеры финиша, затем переход в состояние 3 */
/* P94_FadeStep — Game.exe 004e5284, cdecl.  Finish-line effect in the interview city (state 4, 00d04654 == 1): flash value 0..255 in steps
   of 12 while the camera position P94_FadePos passes 3072..4096, then end the sequence
   (00d118a8 = 1, 00d04654 = 3). */
void P94_FadeStep(void) {
  if (G2_00D04654 != 1 || G6_00B5A778 != 0 || D_00b87e30 != 4) return;
  if (P94_FadeDir == 0) {
    if (3072.0f < P94_FadePos && P94_FadePos < 4096.0f) { P94_FadeDir = 0xc; P94_FadeVal = 0; }
  } else {
    P94_FadeVal += P94_FadeDir;
    if (P94_FadeVal < 0) {
      P94_FadeVal = 0;
      P94_FadeDir = -P94_FadeDir;
      if (4095.0f < P94_FadePos) P94_FadeDir = 0;
    }
    if (P94_FadeVal > 0xff) { P94_FadeVal = 0xff; P94_FadeDir = -P94_FadeDir; }
  }
  if (4096.0f <= P94_FadePos) {
    P14_00d118a8 = 1;
    G2_00D04654 = 3;
    G2_00D044C8 = 0;
    P59_Mode1137324 = 0;
  } else P94_FadePos += P94_FadeSpeed;
}

/* 004ab95c: четырёхугольник значка из записи P94_IconRec (+8 страница, +9 u, +10 v, +0xb ширина, +0xc высота) */
/* P94_IconQuad — Game.exe 004ab95c, cdecl.  Build the screen quad of icon record P94_IconRec (+8 page, +9 u, +0xa v, +0xb width, +0xc
   height): corner indices, UV floats and colour 255, 255, 255.  Native: skipped while the record
   is not set. */
void P94_IconQuad(void) {
  const uint8_t *r = (const uint8_t *)re_ptr(P94_IconRec);
  if (r == NULL) return;                                /* охранная проверка: в native запись ставит ещё не перенесённый код */
  P94_Quad[0] = 0; P94_Quad[1] = 1; P94_Quad[2] = 2; P94_Quad[3] = 3;
  P94_QuadPage = r[8];
  wrf(&P94_Quad[4], (float)(r[9] + 1));
  wrf(&P94_Quad[5], (float)r[0xc]);
  wrf(&P94_Quad[6], (float)r[0xb]);
  wrf(&P94_Quad[7], (float)r[0xc]);
  wrf(&P94_Quad[8], (float)r[0xb]);
  wrf(&P94_Quad[9], (float)(r[10] + 1));
  wrf(&P94_Quad[10], (float)(r[9] + 1));
  wrf(&P94_Quad[11], (float)(r[10] + 1));
  P94_Quad[12] = 0x437f0000u; P94_Quad[13] = 0x437f0000u; P94_Quad[14] = 0x437f0000u;   /* 255.0f */
}

/* 00507672: координаты карты → экран с учётом ориентации карты (D_00b87e30: 1 — отражение, 0/3 — поворот на 90°) */
/* P94_MapToScreen — Game.exe 00507672, cdecl.  Map (x, y) -> screen: flip (orientation 1) or rotate by 90 degrees (orientations 0 / 3) around the
   map centre, then scale from the map window (P94_MapX0/Y0, W/H; 640x480 reference) by the view
   scale 0125f3e0 to the current resolution. */
void P94_MapToScreen(float *x, float *y) {
  float u, v;
  if (D_00b87e30 == 1) {
    u = (float)P57_ScrW * 0.5f + -(*x - (float)P57_ScrW * 0.5f);
    v = (float)S_00C808A0 * 0.5f + -(*y - (float)S_00C808A0 * 0.5f);
  } else if (D_00b87e30 != 0 && D_00b87e30 != 3) {
    u = *x; v = *y;
  } else {
    *x = *x - (float)P57_ScrW * 0.5f;
    *y = *y - (float)S_00C808A0 * 0.5f;
    u = (float)S_00C808A0 * 0.5f + -*y;
    v = (float)P57_ScrW * 0.5f + *x;
  }
  float ny = (((480.0f / (float)P94_MapH) * (v - (float)P94_MapY0)) / 480.0f - 0.5f) * P11_0125f3e0 + 0.5f;
  float h = (float)P19_ScrH;
  *x = ((((640.0f / (float)P94_MapW) * (u - (float)P94_MapX0)) / 640.0f - 0.5f) * P11_0125f3e0 + 0.5f) * (float)P19_ScrW;
  *y = ny * h;
}
