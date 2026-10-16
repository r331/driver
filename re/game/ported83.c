#include "ported83.h"
#include <string.h>

#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P83_LightVec")
#undef P83_LightVec
#pragma push_macro("P83_LightVec") /*gvi*/
#undef P83_LightVec /*gvi*/
p83_v16_t P83_LightVec;
#pragma pop_macro("P83_LightVec") /*gvi*/
#pragma pop_macro("P83_LightVec")
#endif

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
