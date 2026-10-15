/* Математика движка, часть 2 — восстановлено из Game.exe (cdecl). */
#include "ported44.h"
#include <math.h>
#include <string.h>
GAME_VAR_DEF(p44_atan_t, P44_AtanTab, 0x0057670c)
GAME_VAR_DEF(float*, P44_MatPtr, 0x00bdc28c)
GAME_VAR_DEF(float, P44_BiasX, 0x00ba5280)
GAME_VAR_DEF(float, P44_BiasY, 0x00ba52d4)
GAME_VAR_DEF(float, P44_BiasZ, 0x00ba5380)
GAME_VAR_DEF(uint32_t, P44_XformTag, 0x01270c20)
GAME_VAR_DEF(float, P44_CamX, 0x00b1c270)
GAME_VAR_DEF(float, P44_CamY, 0x00b1c274)
GAME_VAR_DEF(float, P44_CamZ, 0x00b1c278)
GAME_VAR_DEF(p44_m9_t, P44_ViewMat, 0x011f4080)
GAME_VAR_DEF(p44_m9_t, P44_ViewMatT, 0x011effa0)
GAME_VAR_DEF(p44_rst_t, P44_Rst_Tab, 0x0057668c)
GAME_VAR_DEF(int32_t, P44_Rst_B93CEC, 0x00b93cec)
GAME_VAR_DEF(int32_t, P44_Rst_B93DFC, 0x00b93dfc)
GAME_VAR_DEF(int32_t, P44_Rst_B93E00, 0x00b93e00)
GAME_VAR_DEF(int32_t, P44_Rst_B93CD0, 0x00b93cd0)
GAME_VAR_DEF(int32_t, P44_Rst_B93CD8, 0x00b93cd8)
GAME_VAR_DEF(int32_t, P44_Rst_B93CE8, 0x00b93ce8)
GAME_VAR_DEF(int32_t, P44_Rst_B93CE4, 0x00b93ce4)
GAME_VAR_DEF(int32_t, P44_Rst_B93CCC, 0x00b93ccc)
GAME_VAR_DEF(int32_t, P44_Rst_B93DF4, 0x00b93df4)
GAME_VAR_DEF(int32_t, P44_Rst_B93CF0, 0x00b93cf0)
GAME_VAR_DEF(int32_t, P44_Rst_B93CD4, 0x00b93cd4)
GAME_VAR_DEF(int32_t, P44_Rst_B93CDC, 0x00b93cdc)
GAME_VAR_DEF(int32_t, P44_Rst_B31EA0, 0x00b31ea0)
GAME_VAR_DEF(int32_t, P44_Rst_B93DF8, 0x00b93df8)
GAME_VAR_DEF(int32_t, P44_Rst_B93CE0, 0x00b93ce0)

void P44_InitTables(void) {
#ifndef RE_HOOK_BUILD
  /* таблица из .data Game.exe совпадает с round(atan(i/1024) * 2048 / pi) для всех 1025 записей (проверено) */
  for (int i = 0; i < 1025; i++) P44_AtanTab[i] = (int16_t)lrint(atan((double)i / 1024.0) * 2048.0 / 3.14159265358979323846);
#endif
}
void P44_ResetState(void) {
  P44_Rst_B93CEC = 0; P44_Rst_B93DFC = 0; P44_Rst_B93E00 = 0; P44_Rst_B93CD0 = 0; P44_Rst_B93CD8 = 0;
  P44_Rst_B93CE8 = 0; P44_Rst_B93CE4 = 0; P44_Rst_B93CCC = 0; P44_Rst_B93DF4 = 0; P44_Rst_B93CF0 = 0;
  P44_Rst_B93CD4 = 0; P44_Rst_B93CDC = 0; P44_Rst_B31EA0 = 0; P44_Rst_B93DF8 = 0; P44_Rst_B93CE0 = -1;
  for (int i = 0; i < 9; i++) P44_Rst_Tab[i * 3] = 0;
}
int32_t P44_Atan2(int32_t x, int32_t y) {
  const int16_t *t = P44_AtanTab;
  if (y == 0 && x == 0) return 0;
  if (x < 0) {
    if (y < 1) {
      if (x == y || -y < -x) return 0xc00 - t[-(y * 0x400 + x / 2) / -x];
      return t[-(x * 0x400 + y / 2) / -y] + 0x800;
    }
    if (-x < y) return (0x1000 - t[-(x * 0x400 - y / 2) / y]) & 0xfff;
    return t[(y * 0x400 - x / 2) / -x] + 0xc00;
  }
  if (y < 1) {
    if (-x == y || -y < x) return t[-(y * 0x400 - x / 2) / x] + 0x400;
    return 0x800 - t[(x * 0x400 - y / 2) / -y];
  }
  if (x < y) return t[(y / 2 + x * 0x400) / y];
  return 0x400 - t[(x / 2 + y * 0x400) / x];
}
static void ident3(float *m) {
  m[0] = 1.0f; m[3] = 0; m[6] = 0; m[1] = 0; m[4] = 1.0f; m[7] = 0; m[2] = 0; m[5] = 0; m[8] = 1.0f;
}
void P44_EulerMatXYZ(float *m, const int16_t *a) { ident3(m); P44_RotX(m, a[0]); P44_RotY(m, a[1]); P44_RotZ(m, a[2]); }
void P44_EulerMatYXZ(float *m, const int16_t *a) { ident3(m); P44_RotY(m, a[1]); P44_RotX(m, a[0]); P44_RotZ(m, a[2]); }
int32_t P44_PointInQuad(int32_t x, int32_t y, const int32_t *q) {
  if ((x - q[0]) * (q[3] - q[1]) - (y - q[1]) * (q[2] - q[0]) < 0) return 0;
  if ((x - q[2]) * (q[5] - q[3]) - (y - q[3]) * (q[4] - q[2]) < 0) return 0;
  if ((x - q[4]) * (q[7] - q[5]) - (y - q[5]) * (q[6] - q[4]) < 0) return 0;
  if ((x - q[6]) * (q[1] - q[7]) - (y - q[7]) * (q[0] - q[6]) < 0) return 0;
  return 1;
}
void P44_QuatNormalize(float *q) {
  float len = (float)sqrt((double)(q[4] * q[4] + q[2] * q[2] + q[1] * q[1] + q[0] * q[0]));
  if (len == P8_00546024) { q[4] = 1.0f; q[2] = 0; q[1] = 0; q[0] = 0; return; }   /* 005272c6 */
  float k = P8_00546020 / len;
  q[0] *= k; q[1] *= k; q[2] *= k; q[4] *= k;
}
void P44_QuatMul(const float *a, const float *b, float *o) {
  float t[5];
  t[4] = ((a[4] * b[4] - a[0] * b[0]) - a[1] * b[1]) - a[2] * b[2];
  t[0] = (a[1] * b[2] + b[4] * a[0] + a[4] * b[0]) - a[2] * b[1];
  t[1] = (a[2] * b[0] + b[4] * a[1] + a[4] * b[1]) - a[0] * b[2];
  t[2] = (a[0] * b[1] + b[4] * a[2] + a[4] * b[2]) - a[1] * b[0];
  t[3] = 0.0f;                                        /* в оригинале — неинициализированный слот стека */
  for (int i = 0; i < 5; i++) o[i] = t[i];
}
void P44_EulerToQuat(const int16_t *ang, float *q) {
  const float *S = P43_Sin, *C = &P43_Sin[0x400];
  float c1 = C[ang[1] / 2], s1 = S[ang[1] / 2];
  float c0c2 = C[ang[0] / 2] * C[ang[2] / 2], c0s2 = C[ang[0] / 2] * S[ang[2] / 2];
  float s0c2 = S[ang[0] / 2] * C[ang[2] / 2], s0s2 = S[ang[0] / 2] * S[ang[2] / 2];
  q[0] = c1 * s0c2 - s1 * c0s2;
  q[1] = s1 * c0c2 + c1 * s0s2;
  q[2] = c1 * c0s2 - s1 * s0c2;
  q[4] = s1 * s0s2 + c1 * c0c2;
  P44_QuatNormalize(q);
}
void P44_AxisAngleMat(int32_t ang, const float *ax, float *m) {
  float s = P43_Sin[ang], c1 = P8_00546020 - P43_Sin[ang + 0x400];
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
void P44_Copy4(void *dst, const void *src, uint32_t n) {
  uint32_t *d = (uint32_t*)dst; const uint32_t *s = (const uint32_t*)src;
  for (uint32_t k = n >> 2; k; k--) { uint32_t v; memcpy(&v, s++, 4); memcpy(d++, &v, 4); }
  uint8_t *db = (uint8_t*)d; const uint8_t *sb = (const uint8_t*)s;
  for (uint32_t k = n & 3; k; k--) *db++ = *sb++;
}
void P44_Transpose(const float *s, float *d) {
  float t[9] = { s[0], s[3], s[6], s[1], s[4], s[7], s[2], s[5], s[8] };
  for (int i = 0; i < 9; i++) d[i] = t[i];
}
void P44_RotX(float *m, int32_t ang) {
  float s = P43_Sin[ang], c = P43_Sin[(uint32_t)(ang + 0x400) & 0xfff], ns = -s;
  float a1 = m[2] * s + m[1] * c, a4 = m[5] * s + m[4] * c, a7 = m[8] * s + m[7] * c;
  m[2] = m[2] * c + m[1] * ns; m[5] = m[5] * c + m[4] * ns; m[8] = m[8] * c + m[7] * ns;
  m[1] = a1; m[4] = a4; m[7] = a7;
}
void P44_RotY(float *m, int32_t ang) {
  float s = P43_Sin[ang], c = P43_Sin[(uint32_t)(ang + 0x400) & 0xfff], ns = -s;
  float a0 = m[2] * ns + m[0] * c, a3 = m[5] * ns + m[3] * c, a6 = m[8] * ns + m[6] * c;
  m[2] = m[2] * c + m[0] * s; m[5] = m[5] * c + m[3] * s; m[8] = m[8] * c + m[6] * s;
  m[0] = a0; m[3] = a3; m[6] = a6;
}
void P44_RotZ(float *m, int32_t ang) {
  float s = P43_Sin[ang], c = P43_Sin[(uint32_t)(ang + 0x400) & 0xfff], ns = -s;
  float a0 = m[1] * s + m[0] * c, a3 = m[4] * s + m[3] * c, a6 = m[7] * s + m[6] * c;
  m[1] = m[1] * c + m[0] * ns; m[4] = m[4] * c + m[3] * ns; m[7] = m[7] * c + m[6] * ns;
  m[0] = a0; m[3] = a3; m[6] = a6;
}
void P44_Xform(float *v) {
  const float *M = P44_MatPtr; float x = v[0], y = v[1], z = v[2];
  v[1] = z * M[7] + y * M[4] + x * M[1];
  v[0] = z * M[6] + y * M[3] + x * M[0];
  v[2] = z * M[8] + y * M[5] + x * M[2];
}
void P44_XformT(float *v) {
  const float *M = P44_MatPtr; float x = v[0], y = v[1], z = v[2];
  v[1] = z * M[5] + y * M[4] + x * M[3];
  v[0] = z * M[2] + y * M[1] + x * M[0];
  v[2] = z * M[8] + y * M[7] + x * M[6];
}
void P44_XformBias(float *v) {
  const float *M = P44_MatPtr; float x = v[3], y = v[4], z = v[5]; uint32_t tag = P44_XformTag;
  float bz = x * M[2] + P44_BiasZ, by = x * M[1] + P44_BiasY;
  v[3] = z * M[6] + P44_BiasX + y * M[3] + x * M[0];
  v[4] = z * M[7] + y * M[4] + by;
  v[5] = z * M[8] + y * M[5] + bz;
  memcpy(&v[0], &tag, 4);
}
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
