/* ported83 — world renderer helpers (Game.exe, cdecl): bounding-sphere frustum test against the six view planes
   and the four cached light-space matrices.  Plane math is done in x87 extended precision and rounded to float
   per plane, exactly as the original (fmul/fadd chain then fstp). */
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

/* Signed distance of point p to plane n (n[0..2] normal, n[3] offset): n.p - d in long double, then rounded to
   float (the original's fstp).  Order of additions matters for bit-exactness. */
/* n·p − d: (n0*x + n1*y) + n2*z в расширенной точности, затем fstp во float */
static float pdist(const float *n, const float *p) {
  ld a = (ld)n[0] * (ld)p[0];
  a += (ld)n[1] * (ld)p[1];
  a += (ld)n[2] * (ld)p[2];
  a -= (ld)n[3];
  return (float)a;
}
/* Sign bit of f (1 for negative, including -0.0f), read from the bit pattern like the original's test. */
static int neg(float f) { uint32_t u; memcpy(&u, &f, 4); return (int)(u >> 31); }
/* The sphere touches the plane: d >= 0 (sign bit clear) or -r < d. */
/* плоскость пересекается: d >= 0 (знаковый бит снят) или −r < d */
static int touch(float d, float nr) { return neg(d) == 0 || nr < d; }

/* 00428672 */
/* P83_BoxVis — Game.exe 00428672, cdecl.  Frustum test of a bounding sphere (centre p[0..2], radius r).
   Plane order: left, right, far, near (only when the far test did not decide), top, bottom.
   Returns 0 = outside (culled), 1 = inside, 2 = straddles the far plane, 3 = straddles the near plane
   (res + 1, res = 1 far / 2 near).  TODO(RE): unsure which of P82_PlF / P77_Plane is near and which far —
   the header comment calls the P77 one "near".
   Side effect: P82_Edge = 1 when the sphere crosses a side/top/bottom plane (the caller must clip), or always
   when P60_Var1373C0 is set (forced clipping). */
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
/* P83_LightMatrices — Game.exe 00428928, cdecl.  Copies the four light directions (P19_OutA/B/C, P80_Dir3) into
   each of the four 16-float slots of P83_LightVec, then for k = 0..3: matrix k = ViewMat x EulerTab[k * 0x10000]
   (Mat3Mul 0052859A), stamps its cache flag with the current swap counter P47_SwapCnt (valid this frame),
   sets P44_MatPtr to the Euler table block and transforms light vector k with it (P44_Xform). */
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
