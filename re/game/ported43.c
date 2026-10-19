/* ported43.c — float vector/matrix helpers, the CD music fade, object slot helpers and the native
   initialisation of .data float constants (English overview; original notes follow).  All cdecl.
   P8_00546020 is the .rdata constant 1.0f and P8_00546024 is 0.0f (see re_init_consts); the code uses
   them where Game.exe loads them from memory, which keeps the generated float code identical. */
/* Векторная математика, CD-фейд, слоты — восстановлено из Game.exe (cdecl). */
#include "ported43.h"
#include "ported63.h"
#include "ported66.h"
#include "ported61.h"
#include "ported69.h"
#include "ported72.h"
#include "ported73.h"
#include "ported74.h"
#include "ported76.h"
#include "ported59.h"
#include "ported56.h"
#include "ported57.h"
#include "ported58.h"
#include "ported51.h"
#include "ported44.h"
#include "ported79.h"
#include "ported84.h"
#include "ported85.h"
#include "ported80.h"
#include <math.h>
#include <string.h>
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P43_Sin")
#undef P43_Sin
#pragma push_macro("P43_Sin") /*gvi*/
#undef P43_Sin /*gvi*/
p43_sintab_t P43_Sin;
#pragma pop_macro("P43_Sin") /*gvi*/
#pragma pop_macro("P43_Sin")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P43_Eps")
#undef P43_Eps
#pragma push_macro("P43_Eps") /*gvi*/
#undef P43_Eps /*gvi*/
float P43_Eps;
#pragma pop_macro("P43_Eps") /*gvi*/
#pragma pop_macro("P43_Eps")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P43_Four")
#undef P43_Four
#pragma push_macro("P43_Four") /*gvi*/
#undef P43_Four /*gvi*/
float P43_Four;
#pragma pop_macro("P43_Four") /*gvi*/
#pragma pop_macro("P43_Four")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P43_FadeLen")
#undef P43_FadeLen
#pragma push_macro("P43_FadeLen") /*gvi*/
#undef P43_FadeLen /*gvi*/
float P43_FadeLen;
#pragma pop_macro("P43_FadeLen") /*gvi*/
#pragma pop_macro("P43_FadeLen")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P43_FadeDiv")
#undef P43_FadeDiv
#pragma push_macro("P43_FadeDiv") /*gvi*/
#undef P43_FadeDiv /*gvi*/
float P43_FadeDiv;
#pragma pop_macro("P43_FadeDiv") /*gvi*/
#pragma pop_macro("P43_FadeDiv")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P43_FadeOn")
#undef P43_FadeOn
#pragma push_macro("P43_FadeOn") /*gvi*/
#undef P43_FadeOn /*gvi*/
int32_t P43_FadeOn;
#pragma pop_macro("P43_FadeOn") /*gvi*/
#pragma pop_macro("P43_FadeOn")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P43_FadeSteps")
#undef P43_FadeSteps
#pragma push_macro("P43_FadeSteps") /*gvi*/
#undef P43_FadeSteps /*gvi*/
int32_t P43_FadeSteps;
#pragma pop_macro("P43_FadeSteps") /*gvi*/
#pragma pop_macro("P43_FadeSteps")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P43_FadeA")
#undef P43_FadeA
#pragma push_macro("P43_FadeA") /*gvi*/
#undef P43_FadeA /*gvi*/
float P43_FadeA;
#pragma pop_macro("P43_FadeA") /*gvi*/
#pragma pop_macro("P43_FadeA")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P43_FadeB")
#undef P43_FadeB
#pragma push_macro("P43_FadeB") /*gvi*/
#undef P43_FadeB /*gvi*/
int32_t P43_FadeB;
#pragma pop_macro("P43_FadeB") /*gvi*/
#pragma pop_macro("P43_FadeB")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P43_FadeStep")
#undef P43_FadeStep
#pragma push_macro("P43_FadeStep") /*gvi*/
#undef P43_FadeStep /*gvi*/
float P43_FadeStep;
#pragma pop_macro("P43_FadeStep") /*gvi*/
#pragma pop_macro("P43_FadeStep")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P43_ScaleA")
#undef P43_ScaleA
#pragma push_macro("P43_ScaleA") /*gvi*/
#undef P43_ScaleA /*gvi*/
float P43_ScaleA;
#pragma pop_macro("P43_ScaleA") /*gvi*/
#pragma pop_macro("P43_ScaleA")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P43_OffX")
#undef P43_OffX
#pragma push_macro("P43_OffX") /*gvi*/
#undef P43_OffX /*gvi*/
float P43_OffX;
#pragma pop_macro("P43_OffX") /*gvi*/
#pragma pop_macro("P43_OffX")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P43_OffY")
#undef P43_OffY
#pragma push_macro("P43_OffY") /*gvi*/
#undef P43_OffY /*gvi*/
float P43_OffY;
#pragma pop_macro("P43_OffY") /*gvi*/
#pragma pop_macro("P43_OffY")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P43_Half")
#undef P43_Half
#pragma push_macro("P43_Half") /*gvi*/
#undef P43_Half /*gvi*/
float P43_Half;
#pragma pop_macro("P43_Half") /*gvi*/
#pragma pop_macro("P43_Half")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P43_FreeCnt")
#undef P43_FreeCnt
#pragma push_macro("P43_FreeCnt") /*gvi*/
#undef P43_FreeCnt /*gvi*/
int32_t P43_FreeCnt;
#pragma pop_macro("P43_FreeCnt") /*gvi*/
#pragma pop_macro("P43_FreeCnt")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P43_FreeList")
#undef P43_FreeList
#pragma push_macro("P43_FreeList") /*gvi*/
#undef P43_FreeList /*gvi*/
p43_freelist_t P43_FreeList;
#pragma pop_macro("P43_FreeList") /*gvi*/
#pragma pop_macro("P43_FreeList")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P43_AnimTab")
#undef P43_AnimTab
#pragma push_macro("P43_AnimTab") /*gvi*/
#undef P43_AnimTab /*gvi*/
p43_anim_t P43_AnimTab;
#pragma pop_macro("P43_AnimTab") /*gvi*/
#pragma pop_macro("P43_AnimTab")
#endif

/* rd32 / wr32 / rd16 / wr16 / rdf / wrf — local helpers: unaligned reads/writes at byte offset o. */
static inline uint32_t rd32(const uint8_t *p, int o) { uint32_t v; memcpy(&v, p + o, 4); return v; }
static inline void wr32(uint8_t *p, int o, uint32_t v) { memcpy(p + o, &v, 4); }
static inline int16_t rd16(const uint8_t *p, int o) { int16_t v; memcpy(&v, p + o, 2); return v; }
static inline void wr16(uint8_t *p, int o, int16_t v) { memcpy(p + o, &v, 2); }
static inline float rdf(const uint8_t *p, int o) { float v; memcpy(&v, p + o, 4); return v; }
static inline void wrf(uint8_t *p, int o, float v) { memcpy(p + o, &v, 4); }

/* P43_CdFadeInit — Game.exe 00524398.  Starts a CD-audio volume fade when CD music is on (00b91cf4) and no
   fade is running: from P43_FadeLen (1.0) towards 0 in 10 steps of FadeLen / FadeDiv. */
void P43_CdFadeInit(void) {
  if (G6_00B91CF4 != 0 && P43_FadeOn == 0) {
    P43_FadeA = P43_FadeLen;                /* копия 4 байт: mov eax,[576480] -> [b91d20] */
    P43_FadeB = 0;
    P43_FadeStep = P43_FadeLen / P43_FadeDiv;
    P43_FadeSteps = 10;
    P43_FadeOn = 1;
  }
}
/* P43_NormalizeToOut — Game.exe 00526521.  Normalises (x, y, z) into the globals 005507d0.. (P19_OutA/B/C).
   No zero check (as in Game.exe). */
void P43_NormalizeToOut(float x, float y, float z) {
  float len = (float)sqrt((double)(z * z + y * y + x * x));
  float inv_len = P8_00546020 / len;
  P19_OutA = x * inv_len; P19_OutB = y * inv_len; P19_OutC = z * inv_len;
}
/* P43_Normalize — Game.exe 005260d7.  v /= |v| in place, no zero check. */
void P43_Normalize(float *v) {
  float len = (float)sqrt((double)(v[2] * v[2] + v[1] * v[1] + v[0] * v[0]));
  float inv_len = P8_00546020 / len;
  v[0] = inv_len * v[0]; v[1] = inv_len * v[1]; v[2] = inv_len * v[2];
}
/* P43_Cross — Game.exe 0052605d.  o = a x b; returns o.  o[3] is left alone (stack garbage in the original). */
float *P43_Cross(float *o, const float *a, const float *b) {
  float x = a[1] * b[2] - a[2] * b[1];
  float y = a[2] * b[0] - a[0] * b[2];
  float z = a[0] * b[1] - a[1] * b[0];
  o[0] = x; o[1] = y; o[2] = z;
  return o;
}
/* P43_Len3 — Game.exe 005271f2.  |v| of a 3-vector, 0 when |v|^2 <= P43_Eps (1e-4). */
float P43_Len3(const float *v) {
  float len_sq = v[2] * v[2] + v[1] * v[1] + v[0] * v[0];
  return (len_sq <= P43_Eps) ? 0.0f : (float)sqrt((double)len_sq);
}
/* P43_Len4 — Game.exe 00527255.  sqrt(v0^2 + v1^2 + v2^2 + v4^2) (index 4, not 3 — the quaternion layout
   {x, y, z, pad, w}), 0 when the square is <= P43_Eps. */
float P43_Len4(const float *v) {
  float len_sq = v[2] * v[2] + v[1] * v[1] + v[0] * v[0] + v[4] * v[4];
  return (len_sq <= P43_Eps) ? 0.0f : (float)sqrt((double)len_sq);
}
/* P43_Orthonormalize — Game.exe 005265e3.  Re-orthonormalises a 3x3 matrix in place: normalises column 2,
   column 0 = normalize(col1 x col2), column 1 = normalize(col2 x col0). */
void P43_Orthonormalize(float *m) {
  float col_z[3] = { m[2], m[5], m[8] };
  P43_Normalize(col_z);
  m[2] = col_z[0]; m[5] = col_z[1]; m[8] = col_z[2];
  float col_y_old[3] = { m[1], m[4], m[7] }, col_x[4];
  P43_Cross(col_x, col_y_old, col_z);
  P43_Normalize(col_x);
  m[0] = col_x[0]; m[3] = col_x[1]; m[6] = col_x[2];
  float col_y[4];
  P43_Cross(col_y, col_z, col_x);
  P43_Normalize(col_y);
  m[1] = col_y[0]; m[4] = col_y[1]; m[7] = col_y[2];
}
/* P43_PointInPoly — Game.exe 0052680b.  1 if (x, y) is inside the convex polygon of n vertices (stride 4 floats),
   i.e. on the same side of every edge as the polygon's winding.  Quirk kept: the winding is computed from
   the first three vertices on every iteration. */
int32_t P43_PointInPoly(int32_t n, const float *p, float x, float y) {
  for (int32_t i = 0; i < n; i++) {
    int32_t j = (i + 1) % n;
    float orient = (p[1] - p[9]) * (p[0] - p[4]) - (p[0] - p[8]) * (p[1] - p[5]);
    float side = (y - p[i * 4 + 1]) * (p[i * 4] - p[j * 4]) + (x - p[i * 4]) * (p[j * 4 + 1] - p[i * 4 + 1]);
    if (orient < P8_00546024) { if (side < P8_00546024) return 0; }
    else if (P8_00546024 < side) return 0;
  }
  return 1;
}
/* P43_EulerMatrix — Game.exe 005261ad.  3x3 rotation matrix from three angles ang[0..2] (4096 = 360 deg),
   sin/cos from P43_Sin (cos = sin table + 0x400).  TODO(RE): axis order not verified (looks like X*Y*Z). */
void P43_EulerMatrix(float *m, const int16_t *ang) {
  const float *cos_tab = &P43_Sin[0x400];                 /* cos */
  float c0 = cos_tab[ang[0]], s0 = P43_Sin[ang[0]];
  float c1 = cos_tab[ang[1]], s1 = P43_Sin[ang[1]];
  float c2 = cos_tab[ang[2]], s2 = P43_Sin[ang[2]];
  m[0] = c1 * c2;
  m[1] = -s2 * c1;
  m[2] = s1;
  m[3] = c0 * s2 + s0 * s1 * c2;
  m[4] = c0 * c2 + -s2 * s0 * s1;
  m[5] = -s0 * c1;
  m[6] = s0 * s2 + -s1 * c0 * c2;
  m[7] = s0 * c2 + -s2 * -s1 * c0;
  m[8] = c0 * c1;
}
/* P43_ClipT — Game.exe 00526ed7.  One Liang-Barsky clipping step: with denominator d and numerator n,
   narrows the segment parameter range [*t0, *t1].  Returns 0 if the segment is rejected, else 1. */
int32_t P43_ClipT(int32_t d, int32_t n, float *t0, float *t1) {
  if (d < 1) {
    if (d < 0) {
      float t = (float)n / (float)d;
      if (t < *t0) return 0;
      if (t < *t1) *t1 = t;
    } else if (0 < n) return 0;
  } else {
    float t = (float)n / (float)d;
    if (*t1 < t) return 0;
    if (*t0 < t) *t0 = t;
  }
  return 1;
}
/* P43_NormalizeCopy — Game.exe 00527010.  o = v / |v|, or the zero vector if |v| == 0. */
void P43_NormalizeCopy(const float *v, float *o) {
  float len = (float)sqrt((double)(v[2] * v[2] + v[1] * v[1] + v[0] * v[0]));
  if (len == P8_00546024) { o[0] = 0.0f; o[1] = 0.0f; o[2] = 0.0f; }
  else { float inv_len = P8_00546020 / len; o[0] = inv_len * v[0]; o[1] = inv_len * v[1]; o[2] = inv_len * v[2]; }
}
/* P43_MatToQuat — Game.exe 005273a3.  Rotation matrix -> quaternion {x, y, z, -, w} (w = sqrt(trace + 1) / 2).
   Assumes trace > -1 (no branch for the other cases, as in Game.exe). */
void P43_MatToQuat(const float *m, float *q) {
  q[4] = (float)sqrt((double)((m[0] + m[4] + m[8] + P8_00546020) / P43_Four));
  float w4 = q[4] * P43_Four;
  q[0] = (m[7] - m[5]) / w4;
  q[1] = (m[2] - m[6]) / w4;
  q[2] = (m[3] - m[1]) / w4;
}
/* P43_QuatToMat — Game.exe 00527429.  Quaternion {x, y, z, -, w} -> 3x3 rotation matrix (2*a*b written as a*b + a*b). */
void P43_QuatToMat(const float *q, float *m) {
  float xx = q[0] * q[0] + q[0] * q[0], yy = q[1] * q[1] + q[1] * q[1], zz = q[2] * q[2] + q[2] * q[2];
  float xy = q[0] * q[1] + q[0] * q[1], yz = q[1] * q[2] + q[1] * q[2], zx = q[2] * q[0] + q[2] * q[0];
  float wx = q[4] * q[0] + q[4] * q[0], wy = q[4] * q[1] + q[4] * q[1], wz = q[4] * q[2] + q[4] * q[2];
  m[0] = (P8_00546020 - yy) - zz;
  m[1] = xy - wz;
  m[2] = zx + wy;
  m[3] = xy + wz;
  m[4] = (P8_00546020 - zz) - xx;
  m[5] = yz - wx;
  m[6] = zx - wy;
  m[7] = yz + wx;
  m[8] = (P8_00546020 - xx) - yy;
}
/* P43_ProjectGrid — Game.exe 0052647d.  Projects a cached vertex p in place: 1/z from the reciprocal table by
   rounded z (+0x14) into +4, keeps camera x/y in +0x18/+0x1c, screen x/y = x/y * (oow * P43_ScaleA) + Off - P43_Half.
   P110_ViewSetup adds P43_Half (2^20) into OffX/OffY, so it cancels here; adding and removing 2^20 rounds the
   float to 1/8 pixel (the usual Glide vertex-snapping trick) — likely the purpose, not verified. */
void P43_ProjectGrid(uint8_t *p) {
  int32_t zi = (int32_t)lrintf(rdf(p, 0x14));
  wrf(p, 4, RE_OOW(zi));
  float scale = P43_ScaleA * rdf(p, 4);
  wr32(p, 0x18, rd32(p, 0xc));
  wr32(p, 0x1c, rd32(p, 0x10));
  wrf(p, 0xc, scale * rdf(p, 0xc));
  wrf(p, 0x10, scale * rdf(p, 0x10));
  wrf(p, 0xc, (P43_OffX + rdf(p, 0xc)) - P43_Half);
  wrf(p, 0x10, (P43_OffY + rdf(p, 0x10)) - P43_Half);
}
/* P43_FreeSlot — Game.exe 0051200f.  If object slot p is in use (flag 0x10 at +0xc) and the free list has room,
   clears its state fields and pushes its id (+2) onto P43_FreeList. */
void P43_FreeSlot(uint8_t *p) {
  if (0 < P43_FreeCnt && (rd32(p, 0xc) & 0x10) != 0) {
    wr32(p, 0xc, 0); wr32(p, 0x40, 0); wr32(p, 0x1c, 0);
    wr16(p, 4, 0);
    wr32(p, 0x24, 0); wr32(p, 0x20, 0);
    wr16(p, 0x60, 0); wr16(p, 0x5e, 0); wr16(p, 0x5c, 0);
    P43_FreeCnt--;
    P43_FreeList[P43_FreeCnt] = (int32_t)rd16(p, 2);
  }
}
/* P43_AnimNext — Game.exe 00514073.  Clears flags 0x3000 of object p; when its animation time ran out
   (+0x2c <= +0x34 + +0x30) restarts it with animation 2 for type 2 objects or 1 otherwise (length from
   P43_AnimTab) and zeroes the counters.  TODO(RE): unsure what object type 2 is. */
void P43_AnimNext(uint8_t *p) {
  wr32(p, 0xc, rd32(p, 0xc) & 0xffffcfffu);
  if ((int32_t)rd32(p, 0x2c) <= (int32_t)rd32(p, 0x34) + (int32_t)rd32(p, 0x30)) {
    if (rd16(p, 0) == 2) { wr16(p, 0x1c, 2); wr16(p, 0x1e, 0); }
    else                 { wr16(p, 0x1c, 1); wr16(p, 0x1e, 0); }
    wr16(p, 0x20, 0); wr16(p, 0x22, 0);
    wr32(p, 0x2c, (uint32_t)P43_AnimTab[(int32_t)rd32(p, 0x1c)]);
    wr16(p, 0x30, 1); wr16(p, 0x32, 0);
    wr16(p, 0x50, 0); wr16(p, 0x52, 0);
    wr16(p, 0x34, 0); wr16(p, 0x36, 0);
  }
}

/* Начальные значения float-констант из .data Game.exe (в hook-сборке они живут в самой игре). Значения прочитаны из Game.exe по адресам. */
/* re_init_consts — native only.  Sets the .data/.rdata float constants and tables that Game.exe has
   preset in its image (values read from Game.exe), then calls every module's *_InitConsts.
   In the hook build the game's own values are used and this does nothing. */
void re_init_consts(void) {
#ifndef RE_HOOK_BUILD
  P8_00546020 = 1.0f; P8_00546024 = 0.0f;
  P43_Eps = 9.999999747378752e-05f; P43_Four = 4.0f; P43_FadeLen = 1.0f; P43_FadeDiv = 10.0f; P43_Half = 1048576.0f;
  P44_InitTables();
  P51_Half = 0.5f; P19_DivW = 640.0f; P19_DivH = 480.0f;
  P56_InitConsts();
  P57_InitConsts();
  P58_InitConsts();
  P79_InitConsts();
  P84_InitConsts();
  P85_InitConsts();
  P80_InitConsts();
  P59_InitConsts();
  P61_InitConsts();
  P63_InitConsts();
  P66_InitConsts();
  P69_InitConsts();
  P72_InitConsts();
  P73_InitConsts();
  P76_InitConsts();
  P74_InitConsts();
#endif
}
