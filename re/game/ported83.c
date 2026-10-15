#include "ported83.h"
#include <string.h>

GAME_VAR_DEF(p83_v16_t, P83_LightVec, 0x01249680)
GAME_VAR_DEF(p83_m9_t, P83_Mat0, 0x01209680)
GAME_VAR_DEF(p83_m9_t, P83_Mat1, 0x01219680)
GAME_VAR_DEF(p83_m9_t, P83_Mat2, 0x01229680)
GAME_VAR_DEF(p83_m9_t, P83_Mat3, 0x01239680)
GAME_VAR_DEF(int32_t, P83_Flag0, 0x011f0060)
GAME_VAR_DEF(int32_t, P83_Flag1, 0x011f1060)
GAME_VAR_DEF(int32_t, P83_Flag2, 0x011f2060)
GAME_VAR_DEF(int32_t, P83_Flag3, 0x011f3060)

typedef long double ld;

/* n·p − d: (n0*x + n1*y) + n2*z в расширенной точности, затем fstp во float */
static float pdist(const float *n, const float *p) {
  ld a = (ld)n[0] * (ld)p[0];
  a += (ld)n[1] * (ld)p[1];
  a += (ld)n[2] * (ld)p[2];
  a -= (ld)n[3];
  return (float)a;
}
static int neg(float f) { uint32_t u; memcpy(&u, &f, 4); return (int)(u >> 31); }
/* плоскость пересекается: d >= 0 (знаковый бит снят) или −r < d */
static int touch(float d, float nr) { return neg(d) == 0 || nr < d; }

/* 00428672 */
int32_t P83_BoxVis(const float *p, float r) {
  int32_t res = 0;
  float nr = -r;
  float d;
  P82_Edge = 0;
  d = pdist(P82_PlL, p);
  if (!(d < r)) return 0;
  if (touch(d, nr)) P82_Edge = 1;
  d = pdist(P82_PlR, p);
  if (!(d < r)) return 0;
  if (touch(d, nr)) P82_Edge = 1;
  d = pdist(P82_PlF, p);
  if (neg(d) == 0) { d = (float)((ld)d - (ld)r); res = 1; }
  else if (neg((float)((ld)r + (ld)d)) == 0) res = 1;
  if (neg(d) == 0) return 0;
  if (res == 0) {
    d = pdist(P77_Plane, p);
    if (!(d <= r)) return 0;
    if (d > nr) res = 2;
  }
  d = pdist(P82_PlT, p);
  if (!(d < r)) return 0;
  if (touch(d, nr)) P82_Edge = 1;
  d = pdist(P82_PlB, p);
  if (!(d < r)) return 0;
  if (touch(d, nr)) P82_Edge = 1;
  if ((uint8_t)P60_Var1373C0 != 0) P82_Edge = 1;
  return res + 1;
}

/* 00428928 */
void P83_LightMatrices(void) {
  float *mat[4] = { P83_Mat0, P83_Mat1, P83_Mat2, P83_Mat3 };
  int32_t *flag[4] = { &P83_Flag0, &P83_Flag1, &P83_Flag2, &P83_Flag3 };
  float dir[4] = { P19_OutA, P19_OutB, P19_OutC, P80_Dir3 };
  for (int k = 0; k < 4; k++) memcpy(&P83_LightVec[k * 4], dir, 16);
  for (int k = 0; k < 4; k++) {
    float *m = (float *)(P56_EulerTab + (size_t)k * 0x10000);
    Mat3Mul_0052859A(P44_ViewMat, m, mat[k]);
    *flag[k] = P47_SwapCnt;
    P44_MatPtr = m;
    P44_Xform(&P83_LightVec[k * 4]);
  }
}
