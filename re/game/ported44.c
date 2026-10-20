/* Engine maths, part 2: table atan2, float 3x3 rotation matrices (Euler, axis-angle,
   look-at), quaternions and vector transforms by P44_MatPtr.  Angles are 4096 per turn.
   Quaternion layout: q[0..2] = x, y, z, q[3] unused, q[4] = w. */
/* Математика движка, часть 2 — восстановлено из Game.exe (cdecl). */
#include "ported44.h"
#include <math.h>
#include <string.h>
#include "fixmath.h"
#define ANG_270 0xc00   /* 270 degrees */
#define ATAN_TAB_N 1025 /* P44_AtanTab: atan(i / 1024) for i = 0..1024, in 4096-per-turn units */
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P44_AtanTab")
#undef P44_AtanTab
#pragma push_macro("P44_AtanTab") /*gvi*/
#undef P44_AtanTab /*gvi*/
p44_atan_t P44_AtanTab;
#pragma pop_macro("P44_AtanTab") /*gvi*/
#pragma pop_macro("P44_AtanTab")
#endif
GAME_VAR_DEF(float*, P44_MatPtr, 0x00bdc28c)
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P44_BiasX")
#undef P44_BiasX
#pragma push_macro("P44_BiasX") /*gvi*/
#undef P44_BiasX /*gvi*/
float P44_BiasX;
#pragma pop_macro("P44_BiasX") /*gvi*/
#pragma pop_macro("P44_BiasX")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P44_BiasY")
#undef P44_BiasY
#pragma push_macro("P44_BiasY") /*gvi*/
#undef P44_BiasY /*gvi*/
float P44_BiasY;
#pragma pop_macro("P44_BiasY") /*gvi*/
#pragma pop_macro("P44_BiasY")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P44_BiasZ")
#undef P44_BiasZ
#pragma push_macro("P44_BiasZ") /*gvi*/
#undef P44_BiasZ /*gvi*/
float P44_BiasZ;
#pragma pop_macro("P44_BiasZ") /*gvi*/
#pragma pop_macro("P44_BiasZ")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P44_XformTag")
#undef P44_XformTag
#pragma push_macro("P44_XformTag") /*gvi*/
#undef P44_XformTag /*gvi*/
uint32_t P44_XformTag;
#pragma pop_macro("P44_XformTag") /*gvi*/
#pragma pop_macro("P44_XformTag")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P44_CamX")
#undef P44_CamX
#pragma push_macro("P44_CamX") /*gvi*/
#undef P44_CamX /*gvi*/
float P44_CamX;
#pragma pop_macro("P44_CamX") /*gvi*/
#pragma pop_macro("P44_CamX")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P44_CamY")
#undef P44_CamY
#pragma push_macro("P44_CamY") /*gvi*/
#undef P44_CamY /*gvi*/
float P44_CamY;
#pragma pop_macro("P44_CamY") /*gvi*/
#pragma pop_macro("P44_CamY")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P44_CamZ")
#undef P44_CamZ
#pragma push_macro("P44_CamZ") /*gvi*/
#undef P44_CamZ /*gvi*/
float P44_CamZ;
#pragma pop_macro("P44_CamZ") /*gvi*/
#pragma pop_macro("P44_CamZ")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P44_ViewMat")
#undef P44_ViewMat
#pragma push_macro("P44_ViewMat") /*gvi*/
#undef P44_ViewMat /*gvi*/
p44_m9_t P44_ViewMat;
#pragma pop_macro("P44_ViewMat") /*gvi*/
#pragma pop_macro("P44_ViewMat")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P44_ViewMatT")
#undef P44_ViewMatT
#pragma push_macro("P44_ViewMatT") /*gvi*/
#undef P44_ViewMatT /*gvi*/
p44_m9_t P44_ViewMatT;
#pragma pop_macro("P44_ViewMatT") /*gvi*/
#pragma pop_macro("P44_ViewMatT")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P44_Rst_Tab")
#undef P44_Rst_Tab
#pragma push_macro("P44_Rst_Tab") /*gvi*/
#undef P44_Rst_Tab /*gvi*/
p44_rst_t P44_Rst_Tab;
#pragma pop_macro("P44_Rst_Tab") /*gvi*/
#pragma pop_macro("P44_Rst_Tab")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P44_Rst_B93CEC")
#undef P44_Rst_B93CEC
#pragma push_macro("P44_Rst_B93CEC") /*gvi*/
#undef P44_Rst_B93CEC /*gvi*/
int32_t P44_Rst_B93CEC;
#pragma pop_macro("P44_Rst_B93CEC") /*gvi*/
#pragma pop_macro("P44_Rst_B93CEC")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P44_Rst_B93DFC")
#undef P44_Rst_B93DFC
#pragma push_macro("P44_Rst_B93DFC") /*gvi*/
#undef P44_Rst_B93DFC /*gvi*/
int32_t P44_Rst_B93DFC;
#pragma pop_macro("P44_Rst_B93DFC") /*gvi*/
#pragma pop_macro("P44_Rst_B93DFC")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P44_Rst_B93E00")
#undef P44_Rst_B93E00
#pragma push_macro("P44_Rst_B93E00") /*gvi*/
#undef P44_Rst_B93E00 /*gvi*/
int32_t P44_Rst_B93E00;
#pragma pop_macro("P44_Rst_B93E00") /*gvi*/
#pragma pop_macro("P44_Rst_B93E00")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P44_Rst_B93CD0")
#undef P44_Rst_B93CD0
#pragma push_macro("P44_Rst_B93CD0") /*gvi*/
#undef P44_Rst_B93CD0 /*gvi*/
int32_t P44_Rst_B93CD0;
#pragma pop_macro("P44_Rst_B93CD0") /*gvi*/
#pragma pop_macro("P44_Rst_B93CD0")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P44_Rst_B93CD8")
#undef P44_Rst_B93CD8
#pragma push_macro("P44_Rst_B93CD8") /*gvi*/
#undef P44_Rst_B93CD8 /*gvi*/
int32_t P44_Rst_B93CD8;
#pragma pop_macro("P44_Rst_B93CD8") /*gvi*/
#pragma pop_macro("P44_Rst_B93CD8")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P44_Rst_B93CE8")
#undef P44_Rst_B93CE8
#pragma push_macro("P44_Rst_B93CE8") /*gvi*/
#undef P44_Rst_B93CE8 /*gvi*/
int32_t P44_Rst_B93CE8;
#pragma pop_macro("P44_Rst_B93CE8") /*gvi*/
#pragma pop_macro("P44_Rst_B93CE8")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P44_Rst_B93CE4")
#undef P44_Rst_B93CE4
#pragma push_macro("P44_Rst_B93CE4") /*gvi*/
#undef P44_Rst_B93CE4 /*gvi*/
int32_t P44_Rst_B93CE4;
#pragma pop_macro("P44_Rst_B93CE4") /*gvi*/
#pragma pop_macro("P44_Rst_B93CE4")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P44_Rst_B93CCC")
#undef P44_Rst_B93CCC
#pragma push_macro("P44_Rst_B93CCC") /*gvi*/
#undef P44_Rst_B93CCC /*gvi*/
int32_t P44_Rst_B93CCC;
#pragma pop_macro("P44_Rst_B93CCC") /*gvi*/
#pragma pop_macro("P44_Rst_B93CCC")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P44_Rst_B93DF4")
#undef P44_Rst_B93DF4
#pragma push_macro("P44_Rst_B93DF4") /*gvi*/
#undef P44_Rst_B93DF4 /*gvi*/
int32_t P44_Rst_B93DF4;
#pragma pop_macro("P44_Rst_B93DF4") /*gvi*/
#pragma pop_macro("P44_Rst_B93DF4")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P44_Rst_B93CF0")
#undef P44_Rst_B93CF0
#pragma push_macro("P44_Rst_B93CF0") /*gvi*/
#undef P44_Rst_B93CF0 /*gvi*/
int32_t P44_Rst_B93CF0;
#pragma pop_macro("P44_Rst_B93CF0") /*gvi*/
#pragma pop_macro("P44_Rst_B93CF0")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P44_Rst_B93CD4")
#undef P44_Rst_B93CD4
#pragma push_macro("P44_Rst_B93CD4") /*gvi*/
#undef P44_Rst_B93CD4 /*gvi*/
int32_t P44_Rst_B93CD4;
#pragma pop_macro("P44_Rst_B93CD4") /*gvi*/
#pragma pop_macro("P44_Rst_B93CD4")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P44_Rst_B93CDC")
#undef P44_Rst_B93CDC
#pragma push_macro("P44_Rst_B93CDC") /*gvi*/
#undef P44_Rst_B93CDC /*gvi*/
int32_t P44_Rst_B93CDC;
#pragma pop_macro("P44_Rst_B93CDC") /*gvi*/
#pragma pop_macro("P44_Rst_B93CDC")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P44_Rst_B31EA0")
#undef P44_Rst_B31EA0
#pragma push_macro("P44_Rst_B31EA0") /*gvi*/
#undef P44_Rst_B31EA0 /*gvi*/
int32_t P44_Rst_B31EA0;
#pragma pop_macro("P44_Rst_B31EA0") /*gvi*/
#pragma pop_macro("P44_Rst_B31EA0")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P44_Rst_B93DF8")
#undef P44_Rst_B93DF8
#pragma push_macro("P44_Rst_B93DF8") /*gvi*/
#undef P44_Rst_B93DF8 /*gvi*/
int32_t P44_Rst_B93DF8;
#pragma pop_macro("P44_Rst_B93DF8") /*gvi*/
#pragma pop_macro("P44_Rst_B93DF8")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P44_Rst_B93CE0")
#undef P44_Rst_B93CE0
#pragma push_macro("P44_Rst_B93CE0") /*gvi*/
#undef P44_Rst_B93CE0 /*gvi*/
int32_t P44_Rst_B93CE0;
#pragma pop_macro("P44_Rst_B93CE0") /*gvi*/
#pragma pop_macro("P44_Rst_B93CE0")
#endif

/* P44_InitTables — Native: rebuild the arctangent table P44_AtanTab (identical to Game.exe .data:
   round(atan(i / 1024) * 2048 / pi) for all 1025 entries). */
void P44_InitTables(void) {
#ifndef RE_HOOK_BUILD
  /* таблица из .data Game.exe совпадает с round(atan(i/1024) * 2048 / pi) для всех 1025 записей (проверено);
     (lrint) — библиотечная функция без эмуляции x87 (fpucw.h): таблица — константа .data, не код игры */
  for (int i = 0; i < ATAN_TAB_N; i++) P44_AtanTab[i] = (int16_t)(lrint)(atan((double)i / 1024.0) * 2048.0 / 3.14159265358979323846);
#endif
}
/* P44_ResetState — Game.exe 00525900, cdecl.  Clear the police-commentary trigger state used by P102_CopTalk (00b93ccc..00b93e00, the hit
   flag 00b31ea0, 9 table entries); 00b93ce0 is set to -1. */
void P44_ResetState(void) {
  P44_Rst_B93CEC = 0; P44_Rst_B93DFC = 0; P44_Rst_B93E00 = 0; P44_Rst_B93CD0 = 0; P44_Rst_B93CD8 = 0;
  P44_Rst_B93CE8 = 0; P44_Rst_B93CE4 = 0; P44_Rst_B93CCC = 0; P44_Rst_B93DF4 = 0; P44_Rst_B93CF0 = 0;
  P44_Rst_B93CD4 = 0; P44_Rst_B93CDC = 0; P44_Rst_B31EA0 = 0; P44_Rst_B93DF8 = 0; P44_Rst_B93CE0 = -1;
  for (int i = 0; i < 9; i++) P44_Rst_Tab[i * 3] = 0;
}
/* P44_Atan2 — Game.exe 00525e7e, cdecl.  Angle of the vector (x, y), 0..4095: 0 along +y, 1024 along +x, 2048 along -y, 3072 along -x.
   Uses the octant symmetry of atan with a rounded (+/- half divisor) table index; (0, 0) -> 0. */
int32_t P44_Atan2(int32_t x, int32_t y) {
  const int16_t *t = P44_AtanTab;
  if (y == 0 && x == 0) return 0;
  if (x < 0) {
    if (y < 1) {
      if (x == y || -y < -x) return ANG_270 - t[-(y * 0x400 + x / 2) / -x];
      return t[-(x * 0x400 + y / 2) / -y] + ANG_180;
    }
    if (-x < y) return (ANG_FULL - t[-(x * 0x400 - y / 2) / y]) & ANG_MASK;
    return t[(y * 0x400 - x / 2) / -x] + ANG_270;
  }
  if (y < 1) {
    if (-x == y || -y < x) return t[-(y * 0x400 - x / 2) / x] + ANG_90;
    return ANG_180 - t[(x * 0x400 - y / 2) / -y];
  }
  if (x < y) return t[(y / 2 + x * 0x400) / y];
  return ANG_90 - t[(x / 2 + y * 0x400) / x];
}
/* ident3 — Set the 3x3 float matrix m to identity. */
static void ident3(float *m) {
  m[0] = 1.0f; m[3] = 0; m[6] = 0; m[1] = 0; m[4] = 1.0f; m[7] = 0; m[2] = 0; m[5] = 0; m[8] = 1.0f;
}
/* P44_EulerMatXYZ — Game.exe 005262cc, cdecl.  m = identity rotated by a[0] about X, then a[1] about Y, then a[2] about Z. */
void P44_EulerMatXYZ(float *m, const int16_t *a) { ident3(m); P44_RotX(m, a[0]); P44_RotY(m, a[1]); P44_RotZ(m, a[2]); }
/* P44_EulerMatYXZ — Game.exe 00526365, cdecl.  As P44_EulerMatXYZ in the order Y, X, Z. */
void P44_EulerMatYXZ(float *m, const int16_t *a) { ident3(m); P44_RotY(m, a[1]); P44_RotX(m, a[0]); P44_RotZ(m, a[2]); }
/* P44_PointInQuad — Game.exe 00526940, cdecl.  1 if (x, y) is on the inner (non-negative cross product) side of all four edges of the quad
   q = {x0, y0, .. x3, y3}; 0 otherwise.  int32 arithmetic. */
int32_t P44_PointInQuad(int32_t x, int32_t y, const int32_t *q) {
  if ((x - q[0]) * (q[3] - q[1]) - (y - q[1]) * (q[2] - q[0]) < 0) return 0;
  if ((x - q[2]) * (q[5] - q[3]) - (y - q[3]) * (q[4] - q[2]) < 0) return 0;
  if ((x - q[4]) * (q[7] - q[5]) - (y - q[5]) * (q[6] - q[4]) < 0) return 0;
  if ((x - q[6]) * (q[1] - q[7]) - (y - q[7]) * (q[0] - q[6]) < 0) return 0;
  return 1;
}
/* P44_QuatNormalize — Game.exe 005272f2, cdecl.  Normalise quaternion q; a zero-length one (== .data 0.0) becomes identity (w = 1). */
void P44_QuatNormalize(float *q) {
  float len = (float)sqrt((double)(q[4] * q[4] + q[2] * q[2] + q[1] * q[1] + q[0] * q[0]));
  if (len == P8_00546024) { q[4] = 1.0f; q[2] = 0; q[1] = 0; q[0] = 0; return; }   /* 005272c6 */
  float k = P8_00546020 / len;
  q[0] *= k; q[1] *= k; q[2] *= k; q[4] *= k;
}
/* P44_QuatMul — Game.exe 00527544, cdecl.  o = a * b (Hamilton product).  Native writes 0 to the unused slot o[3] (the original copied an
   uninitialised stack slot).  o may alias a or b. */
void P44_QuatMul(const float *a, const float *b, float *o) {
  float t[5];
  t[4] = ((a[4] * b[4] - a[0] * b[0]) - a[1] * b[1]) - a[2] * b[2];
  t[0] = (a[1] * b[2] + b[4] * a[0] + a[4] * b[0]) - a[2] * b[1];
  t[1] = (a[2] * b[0] + b[4] * a[1] + a[4] * b[1]) - a[0] * b[2];
  t[2] = (a[0] * b[1] + b[4] * a[2] + a[4] * b[2]) - a[1] * b[0];
  t[3] = 0.0f;                                        /* в оригинале — неинициализированный слот стека */
  for (int i = 0; i < 5; i++) o[i] = t[i];
}
/* P44_EulerToQuat — Game.exe 0052763b, cdecl.  Quaternion from Euler angles ang[0..2] (half angles via the sine table), then normalised. */
void P44_EulerToQuat(const int16_t *ang, float *q) {
  const float *S = P43_Sin, *C = &P43_Sin[ANG_90];   /* cos(a) = sin(a + 90 deg) */
  float c1 = C[ang[1] / 2], s1 = S[ang[1] / 2];
  float c0c2 = C[ang[0] / 2] * C[ang[2] / 2], c0s2 = C[ang[0] / 2] * S[ang[2] / 2];
  float s0c2 = S[ang[0] / 2] * C[ang[2] / 2], s0s2 = S[ang[0] / 2] * S[ang[2] / 2];
  q[0] = c1 * s0c2 - s1 * c0s2;
  q[1] = s1 * c0c2 + c1 * s0s2;
  q[2] = c1 * c0s2 - s1 * s0c2;
  q[4] = s1 * s0s2 + c1 * c0c2;
  P44_QuatNormalize(q);
}
/* P44_AxisAngleMat — Game.exe 00527746, cdecl.  Rotation matrix for angle `ang` about the unit axis ax (Rodrigues form, 1 - cos as c1). */
void P44_AxisAngleMat(int32_t ang, const float *ax, float *m) {
  float s = P43_Sin[ang], c1 = P8_00546020 - P43_Sin[ang + ANG_90];
  float x = ax[0], y = ax[1], z = ax[2];
  m[0] = P8_00546020 - (y * y + z * z) * c1;
  m[1] = c1 * x * y + s * z;
  m[2] = c1 * x * z + -(s * y);
  m[3] = c1 * x * y + -(s * z);
  m[4] = P8_00546020 - (x * x + z * z) * c1;
  m[5] = c1 * y * z + s * x;
  m[6] = c1 * x * z + s * y;
  m[7] = c1 * y * z + -(s * x);
  m[8] = P8_00546020 - (x * x + y * y) * c1;
}
/* P44_Copy4 — Game.exe 005283b5, cdecl.  memcpy by 4-byte words then the remaining bytes (unaligned-safe). */
void P44_Copy4(void *dst, const void *src, uint32_t n) {
  uint32_t *d = (uint32_t*)dst; const uint32_t *s = (const uint32_t*)src;
  for (uint32_t k = n >> 2; k; k--) { uint32_t v; memcpy(&v, s++, 4); memcpy(d++, &v, 4); }
  uint8_t *db = (uint8_t*)d; const uint8_t *sb = (const uint8_t*)s;
  for (uint32_t k = n & 3; k; k--) *db++ = *sb++;
}
/* P44_Transpose — Game.exe 00528461, cdecl.  d = transpose(s) (3x3, s and d may alias). */
void P44_Transpose(const float *s, float *d) {
  float t[9] = { s[0], s[3], s[6], s[1], s[4], s[7], s[2], s[5], s[8] };
  for (int i = 0; i < 9; i++) d[i] = t[i];
}
/* P44_RotX — Game.exe 00528688, cdecl.  m = m * RotX(ang) (columns 1 and 2 mixed). */
void P44_RotX(float *m, int32_t ang) {
  float s = P43_Sin[ang], c = P43_Sin[(uint32_t)(ang + ANG_90) & ANG_MASK], ns = -s;
  float a1 = m[2] * s + m[1] * c, a4 = m[5] * s + m[4] * c, a7 = m[8] * s + m[7] * c;
  m[2] = m[2] * c + m[1] * ns; m[5] = m[5] * c + m[4] * ns; m[8] = m[8] * c + m[7] * ns;
  m[1] = a1; m[4] = a4; m[7] = a7;
}
/* P44_RotY — Game.exe 00528788, cdecl.  m = m * RotY(ang) (columns 0 and 2 mixed). */
void P44_RotY(float *m, int32_t ang) {
  float s = P43_Sin[ang], c = P43_Sin[(uint32_t)(ang + ANG_90) & ANG_MASK], ns = -s;
  float a0 = m[2] * ns + m[0] * c, a3 = m[5] * ns + m[3] * c, a6 = m[8] * ns + m[6] * c;
  m[2] = m[2] * c + m[0] * s; m[5] = m[5] * c + m[3] * s; m[8] = m[8] * c + m[6] * s;
  m[0] = a0; m[3] = a3; m[6] = a6;
}
/* P44_RotZ — Game.exe 00528885, cdecl.  m = m * RotZ(ang) (columns 0 and 1 mixed). */
void P44_RotZ(float *m, int32_t ang) {
  float s = P43_Sin[ang], c = P43_Sin[(uint32_t)(ang + ANG_90) & ANG_MASK], ns = -s;
  float a0 = m[1] * s + m[0] * c, a3 = m[4] * s + m[3] * c, a6 = m[7] * s + m[6] * c;
  m[1] = m[1] * c + m[0] * ns; m[4] = m[4] * c + m[3] * ns; m[7] = m[7] * c + m[6] * ns;
  m[0] = a0; m[3] = a3; m[6] = a6;
}
/* P44_Xform — Game.exe 00528982, cdecl.  v = v * M (row vector times P44_MatPtr), in place. */
void P44_Xform(float *v) {
  const float *M = P44_MatPtr; float x = v[0], y = v[1], z = v[2];
  v[1] = z * M[7] + y * M[4] + x * M[1];
  v[0] = z * M[6] + y * M[3] + x * M[0];
  v[2] = z * M[8] + y * M[5] + x * M[2];
}
/* P44_XformT — Game.exe 005289e2, cdecl.  v = M * v (transpose of P44_Xform), in place. */
void P44_XformT(float *v) {
  const float *M = P44_MatPtr; float x = v[0], y = v[1], z = v[2];
  v[1] = z * M[5] + y * M[4] + x * M[3];
  v[0] = z * M[2] + y * M[1] + x * M[0];
  v[2] = z * M[8] + y * M[7] + x * M[6];
}
/* P44_XformBias — Game.exe 00528a42, cdecl.  Transform the point at v[3..5] by P44_MatPtr and add the bias P44_BiasX/Y/Z, in place; the
   tag P44_XformTag is stored in v[0] (vertex header).  Operation order kept as the original. */
void P44_XformBias(float *v) {
  const float *M = P44_MatPtr; float x = v[3], y = v[4], z = v[5]; uint32_t tag = P44_XformTag;
  float bz = x * M[2] + P44_BiasZ, by = x * M[1] + P44_BiasY;
  v[3] = z * M[6] + P44_BiasX + y * M[3] + x * M[0];
  v[4] = z * M[7] + y * M[4] + by;
  v[5] = z * M[8] + y * M[5] + bz;
  memcpy(&v[0], &tag, 4);
}
/* P44_LookAt — Game.exe 005266ed, cdecl.  Build the view matrix P44_ViewMat looking from the camera (P44_CamX/Y/Z) to `eye`:
   row 2 = forward, row 0 = normalize(forward x up), row 1 = forward x right; also writes the
   transpose to P44_ViewMatT.  Note the parameter named eye is actually the target point. */
void P44_LookAt(const float *eye, const float *up) {
  float d[3] = { eye[0] - P44_CamX, eye[1] - P44_CamY, eye[2] - P44_CamZ };
  float t[4], r[4], u[4];
  P43_Normalize(d);
  P44_ViewMat[6] = d[0]; P44_ViewMat[7] = d[1]; P44_ViewMat[8] = d[2];
  P43_Cross(t, d, up);
  r[0] = t[0]; r[1] = t[1]; r[2] = t[2];
  P43_Normalize(r);
  P44_ViewMat[0] = r[0]; P44_ViewMat[1] = r[1]; P44_ViewMat[2] = r[2];
  P43_Cross(u, d, r);
  P44_ViewMat[3] = u[0]; P44_ViewMat[4] = u[1]; P44_ViewMat[5] = u[2];
  P44_Transpose(P44_ViewMat, P44_ViewMatT);
}
