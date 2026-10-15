/* Векторная математика, CD-фейд, слоты — восстановлено из Game.exe (cdecl). */
#include "ported43.h"
#include "ported56.h"
#include "ported57.h"
#include "ported58.h"
#include "ported51.h"
#include "ported44.h"
#include <math.h>
#include <string.h>
GAME_VAR_DEF(p43_sintab_t, P43_Sin, 0x00b94280)
GAME_VAR_DEF(float, P43_Eps, 0x00546aa4)
GAME_VAR_DEF(float, P43_Four, 0x005461ac)
GAME_VAR_DEF(float, P43_FadeLen, 0x00576480)
GAME_VAR_DEF(float, P43_FadeDiv, 0x0054612c)
GAME_VAR_DEF(int32_t, P43_FadeOn, 0x00b91cf8)
GAME_VAR_DEF(int32_t, P43_FadeSteps, 0x00b91d1c)
GAME_VAR_DEF(float, P43_FadeA, 0x00b91d20)
GAME_VAR_DEF(int32_t, P43_FadeB, 0x00b91d24)
GAME_VAR_DEF(float, P43_FadeStep, 0x00b91d28)
GAME_VAR_DEF(float, P43_ScaleA, 0x01251a64)
GAME_VAR_DEF(float, P43_OffX, 0x01252b7c)
GAME_VAR_DEF(float, P43_OffY, 0x01252b6c)
GAME_VAR_DEF(float, P43_Half, 0x0054607c)
GAME_VAR_DEF(int32_t, P43_FreeCnt, 0x00c56764)
GAME_VAR_DEF(p43_freelist_t, P43_FreeList, 0x00c594a0)
GAME_VAR_DEF(p43_anim_t, P43_AnimTab, 0x00c8198c)

static inline uint32_t rd32(const uint8_t *p, int o) { uint32_t v; memcpy(&v, p + o, 4); return v; }
static inline void wr32(uint8_t *p, int o, uint32_t v) { memcpy(p + o, &v, 4); }
static inline int16_t rd16(const uint8_t *p, int o) { int16_t v; memcpy(&v, p + o, 2); return v; }
static inline void wr16(uint8_t *p, int o, int16_t v) { memcpy(p + o, &v, 2); }
static inline float rdf(const uint8_t *p, int o) { float v; memcpy(&v, p + o, 4); return v; }
static inline void wrf(uint8_t *p, int o, float v) { memcpy(p + o, &v, 4); }

void P43_CdFadeInit(void) {
  if (G6_00B91CF4 != 0 && P43_FadeOn == 0) {
    P43_FadeA = P43_FadeLen;                /* копия 4 байт: mov eax,[576480] -> [b91d20] */
    P43_FadeB = 0;
    P43_FadeStep = P43_FadeLen / P43_FadeDiv;
    P43_FadeSteps = 10;
    P43_FadeOn = 1;
  }
}
void P43_NormalizeToOut(float x, float y, float z) {
  float len = (float)sqrt((double)(z * z + y * y + x * x));
  float k = P8_00546020 / len;
  P19_OutA = x * k; P19_OutB = y * k; P19_OutC = z * k;
}
void P43_Normalize(float *v) {
  float len = (float)sqrt((double)(v[2] * v[2] + v[1] * v[1] + v[0] * v[0]));
  float k = P8_00546020 / len;
  v[0] = k * v[0]; v[1] = k * v[1]; v[2] = k * v[2];
}
float *P43_Cross(float *o, const float *a, const float *b) {
  float x = a[1] * b[2] - a[2] * b[1];
  float y = a[2] * b[0] - a[0] * b[2];
  float z = a[0] * b[1] - a[1] * b[0];
  o[0] = x; o[1] = y; o[2] = z;
  return o;
}
float P43_Len3(const float *v) {
  float s = v[2] * v[2] + v[1] * v[1] + v[0] * v[0];
  return (s <= P43_Eps) ? 0.0f : (float)sqrt((double)s);
}
float P43_Len4(const float *v) {
  float s = v[2] * v[2] + v[1] * v[1] + v[0] * v[0] + v[4] * v[4];
  return (s <= P43_Eps) ? 0.0f : (float)sqrt((double)s);
}
void P43_Orthonormalize(float *m) {
  float z[3] = { m[2], m[5], m[8] };
  P43_Normalize(z);
  m[2] = z[0]; m[5] = z[1]; m[8] = z[2];
  float y0[3] = { m[1], m[4], m[7] }, x[4];
  P43_Cross(x, y0, z);
  P43_Normalize(x);
  m[0] = x[0]; m[3] = x[1]; m[6] = x[2];
  float y[4];
  P43_Cross(y, z, x);
  P43_Normalize(y);
  m[1] = y[0]; m[4] = y[1]; m[7] = y[2];
}
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
void P43_EulerMatrix(float *m, const int16_t *ang) {
  const float *cs = &P43_Sin[0x400];                 /* cos */
  float c0 = cs[ang[0]], s0 = P43_Sin[ang[0]];
  float c1 = cs[ang[1]], s1 = P43_Sin[ang[1]];
  float c2 = cs[ang[2]], s2 = P43_Sin[ang[2]];
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
void P43_NormalizeCopy(const float *v, float *o) {
  float len = (float)sqrt((double)(v[2] * v[2] + v[1] * v[1] + v[0] * v[0]));
  if (len == P8_00546024) { o[0] = 0.0f; o[1] = 0.0f; o[2] = 0.0f; }
  else { float k = P8_00546020 / len; o[0] = k * v[0]; o[1] = k * v[1]; o[2] = k * v[2]; }
}
void P43_MatToQuat(const float *m, float *q) {
  q[4] = (float)sqrt((double)((m[0] + m[4] + m[8] + P8_00546020) / P43_Four));
  float f = q[4] * P43_Four;
  q[0] = (m[7] - m[5]) / f;
  q[1] = (m[2] - m[6]) / f;
  q[2] = (m[3] - m[1]) / f;
}
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
void P43_ProjectGrid(uint8_t *p) {
  int32_t idx = (int32_t)lrintf(rdf(p, 0x14));
  wrf(p, 4, ((const float *)&P12_00ba53a0[0])[idx]);
  float k = P43_ScaleA * rdf(p, 4);
  wr32(p, 0x18, rd32(p, 0xc));
  wr32(p, 0x1c, rd32(p, 0x10));
  wrf(p, 0xc, k * rdf(p, 0xc));
  wrf(p, 0x10, k * rdf(p, 0x10));
  wrf(p, 0xc, (P43_OffX + rdf(p, 0xc)) - P43_Half);
  wrf(p, 0x10, (P43_OffY + rdf(p, 0x10)) - P43_Half);
}
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
void re_init_consts(void) {
#ifndef RE_HOOK_BUILD
  P8_00546020 = 1.0f; P8_00546024 = 0.0f;
  P43_Eps = 9.999999747378752e-05f; P43_Four = 4.0f; P43_FadeLen = 1.0f; P43_FadeDiv = 10.0f; P43_Half = 1048576.0f;
  P44_InitTables();
  P51_Half = 0.5f; P19_DivW = 640.0f; P19_DivH = 480.0f;
  P56_InitConsts();
  P57_InitConsts();
  P58_InitConsts();
#endif
}
