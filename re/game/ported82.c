#include "ported82.h"
#include "aspect.h"
#include <math.h>
#include <string.h>

#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P82_FovX")
#undef P82_FovX
#pragma push_macro("P82_FovX") /*gvi*/
#undef P82_FovX /*gvi*/
float P82_FovX;
#pragma pop_macro("P82_FovX") /*gvi*/
#pragma pop_macro("P82_FovX")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P82_FovY")
#undef P82_FovY
#pragma push_macro("P82_FovY") /*gvi*/
#undef P82_FovY /*gvi*/
float P82_FovY;
#pragma pop_macro("P82_FovY") /*gvi*/
#pragma pop_macro("P82_FovY")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P82_FovXc")
#undef P82_FovXc
#pragma push_macro("P82_FovXc") /*gvi*/
#undef P82_FovXc /*gvi*/
float P82_FovXc;
#pragma pop_macro("P82_FovXc") /*gvi*/
#pragma pop_macro("P82_FovXc")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P82_FovYc")
#undef P82_FovYc
#pragma push_macro("P82_FovYc") /*gvi*/
#undef P82_FovYc /*gvi*/
float P82_FovYc;
#pragma pop_macro("P82_FovYc") /*gvi*/
#pragma pop_macro("P82_FovYc")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P82_PlL")
#undef P82_PlL
#pragma push_macro("P82_PlL") /*gvi*/
#undef P82_PlL /*gvi*/
p82_plane_t P82_PlL;
#pragma pop_macro("P82_PlL") /*gvi*/
#pragma pop_macro("P82_PlL")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P82_PlR")
#undef P82_PlR
#pragma push_macro("P82_PlR") /*gvi*/
#undef P82_PlR /*gvi*/
p82_plane_t P82_PlR;
#pragma pop_macro("P82_PlR") /*gvi*/
#pragma pop_macro("P82_PlR")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P82_PlF")
#undef P82_PlF
#pragma push_macro("P82_PlF") /*gvi*/
#undef P82_PlF /*gvi*/
p82_plane_t P82_PlF;
#pragma pop_macro("P82_PlF") /*gvi*/
#pragma pop_macro("P82_PlF")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P82_PlT")
#undef P82_PlT
#pragma push_macro("P82_PlT") /*gvi*/
#undef P82_PlT /*gvi*/
p82_plane_t P82_PlT;
#pragma pop_macro("P82_PlT") /*gvi*/
#pragma pop_macro("P82_PlT")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P82_PlB")
#undef P82_PlB
#pragma push_macro("P82_PlB") /*gvi*/
#undef P82_PlB /*gvi*/
p82_plane_t P82_PlB;
#pragma pop_macro("P82_PlB") /*gvi*/
#pragma pop_macro("P82_PlB")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P82_Edge")
#undef P82_Edge
#pragma push_macro("P82_Edge") /*gvi*/
#undef P82_Edge /*gvi*/
int32_t P82_Edge;
#pragma pop_macro("P82_Edge") /*gvi*/
#pragma pop_macro("P82_Edge")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P82_LightGrid")
#undef P82_LightGrid
#pragma push_macro("P82_LightGrid") /*gvi*/
#undef P82_LightGrid /*gvi*/
p82_grid_t P82_LightGrid;
#pragma pop_macro("P82_LightGrid") /*gvi*/
#pragma pop_macro("P82_LightGrid")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P82_CellCX")
#undef P82_CellCX
#pragma push_macro("P82_CellCX") /*gvi*/
#undef P82_CellCX /*gvi*/
int32_t P82_CellCX;
#pragma pop_macro("P82_CellCX") /*gvi*/
#pragma pop_macro("P82_CellCX")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P82_CellCY")
#undef P82_CellCY
#pragma push_macro("P82_CellCY") /*gvi*/
#undef P82_CellCY /*gvi*/
int32_t P82_CellCY;
#pragma pop_macro("P82_CellCY") /*gvi*/
#pragma pop_macro("P82_CellCY")
#endif

typedef long double ld;

/* v' = v*ViewMat (P44_Xform) */
static void xf(float x, float y, float z, float *o) {
  float v[3] = { x, y, z };
  P44_MatPtr = P44_ViewMat;
  P44_Xform(v);
  o[0] = v[0]; o[1] = v[1]; o[2] = v[2];
}

/* d = (z+CamZ)*nz + (y+CamY)*ny + (x+CamX)*nx — суммы и произведения x87 в расширенной точности, запись во float */
static float plane_d(const float *v, const float *n, int use_y) {
  ld a = ((ld)v[2] + (ld)P44_CamZ) * (ld)n[2];
  if (use_y) a += ((ld)v[1] + (ld)P44_CamY) * (ld)n[1];
  a += ((ld)v[0] + (ld)P44_CamX) * (ld)n[0];
  return (float)a;
}

static int sgn(float f) { uint32_t u; memcpy(&u, &f, 4); return (int)(u >> 31); }


/* v2.15 Hor+: боковые плоскости для расширенного кадра — угол re_aspect_half_angle(S) (запас оригинала сохранён), точки ±(320 + S);
   верх/низ — как в оригинале (P82_FovXc/FovYc). S = 0 — ровно оригинальные значения. */
static void side_fov(float *c, float *s, float *hw) {
  *c = P82_FovXc; *s = P82_FovYc; *hw = 320.0f;
#ifndef RE_HOOK_BUILD
  int S = re_view_extra();
  if (S > 0) { double th = re_aspect_half_angle(S); *c = (float)cos(th); *s = (float)sin(th); *hw = (float)(320 + S); }
#endif
}

/* 00427abe */
void P82_FrustumSetup2D(void) {
  float v[3];
  P82_FovXc = P82_FovX;
  P82_FovYc = P82_FovY;
  float sc_, ss_, hw_; side_fov(&sc_, &ss_, &hw_);
  xf(-sc_, 0.0f, -ss_, v);
  P82_PlL[0] = v[0]; P82_PlL[1] = 0.0f; P82_PlL[2] = v[2];
  xf(sc_, 0.0f, -ss_, v);
  P82_PlR[0] = v[0]; P82_PlR[1] = 0.0f; P82_PlR[2] = v[2];
  xf(0.0f, 0.0f, -1.0f, v);
  P82_PlF[0] = v[0]; P82_PlF[1] = 0.0f; P82_PlF[2] = v[2];
  P77_Plane[0] = -v[0]; P77_Plane[1] = 0.0f; P77_Plane[2] = -v[2];
  xf(0.0f, 0.0f, 50.0f, v);
  P82_PlF[3] = (float)(((ld)v[2] + (ld)P44_CamZ) * (ld)P82_PlF[2] + ((ld)v[0] + (ld)P44_CamX) * (ld)P82_PlF[0]);
  xf(0.0f, 0.0f, P11_01270c24, v);
  P77_Plane[3] = (float)(((ld)v[2] + (ld)P44_CamZ) * (ld)P77_Plane[2] + ((ld)v[0] + (ld)P44_CamX) * (ld)P77_Plane[0]);
  xf(-hw_, 0.0f, P43_ScaleA, v);
  P82_PlL[3] = plane_d(v, P82_PlL, 1);
  xf(hw_, 0.0f, P43_ScaleA, v);
  P82_PlR[3] = plane_d(v, P82_PlR, 1);
}

/* 00427eea */
void P82_FrustumSetup3D(void) {
  float v[3];
  P82_FovXc = P82_FovX;
  P82_FovYc = P82_FovY;
  xf(0.0f, -P82_FovXc, -P82_FovYc, v);
  memcpy(P82_PlT, v, 12);
  xf(0.0f, P82_FovXc, -P82_FovYc, v);
  memcpy(P82_PlB, v, 12);
  float sc_, ss_, hw_; side_fov(&sc_, &ss_, &hw_);
  xf(-sc_, 0.0f, -ss_, v);
  memcpy(P82_PlL, v, 12);
  xf(sc_, 0.0f, -ss_, v);
  memcpy(P82_PlR, v, 12);
  xf(0.0f, 0.0f, -1.0f, v);
  memcpy(P82_PlF, v, 12);
  P77_Plane[0] = -v[0]; P77_Plane[1] = -v[1]; P77_Plane[2] = -v[2];
  xf(0.0f, 0.0f, 50.0f, v);
  P82_PlF[3] = plane_d(v, P82_PlF, 1);
  xf(0.0f, 0.0f, P11_01270c24, v);
  P77_Plane[3] = plane_d(v, P77_Plane, 1);
  xf(-hw_, 0.0f, P43_ScaleA, v);
  P82_PlL[3] = plane_d(v, P82_PlL, 1);
  xf(hw_, 0.0f, P43_ScaleA, v);
  P82_PlR[3] = plane_d(v, P82_PlR, 1);
  xf(0.0f, -240.0f, P43_ScaleA, v);
  P82_PlT[3] = plane_d(v, P82_PlT, 1);
  xf(0.0f, 240.0f, P43_ScaleA, v);
  P82_PlB[3] = plane_d(v, P82_PlB, 1);
}

/* расстояние до плоскости (n·p − d), расширенная точность */
static ld dist(const float *n, const float *p, int use_y) {
  ld a = (ld)n[2] * (ld)p[2];
  if (use_y) a += (ld)n[1] * (ld)p[1];
  a += (ld)n[0] * (ld)p[0];
  return a - (ld)n[3];
}

/* 00427d5a */
int32_t P82_SphereVis2D(const float *p, float r) {
  int32_t res = 0;
  float zero = P8_00546024;
  P44_MatPtr = P44_ViewMat;
  P82_Edge = 0;
  if (dist(P77_Plane, p, 0) < (ld)r) {
    ld d = dist(P82_PlL, p, 0);
    if (d < (ld)r) {
      if ((d < (ld)zero && -(ld)r <= d) || (ld)zero <= d) P82_Edge = 1;
      d = dist(P82_PlR, p, 0);
      if (d < (ld)r) {
        if ((d < (ld)zero && -(ld)r < d) || (ld)zero < d) P82_Edge = 1;
        d = dist(P82_PlF, p, 0);
        if (d < (ld)zero) { if ((ld)zero <= (ld)r + d) res = 1; }
        else res = 1;
        P44_MatPtr = P44_ViewMat;
        return res + 1;
      }
    }
  }
  return 0;
}

/* «пересекает плоскость»: расстояние >= 0 или −r < d < 0 */
static int touches(ld d, float r) {
  float f = (float)d;
  return sgn(f) == 0 || (-(ld)r < (ld)f);
}

/* 004283d9 */
int32_t P82_SphereVis3D(const float *p, float r) {
  int32_t res = 0;
  P82_Edge = 0;
  if (dist(P77_Plane, p, 1) < (ld)r) {
    ld d = dist(P82_PlL, p, 1);
    if (d < (ld)r) {
      if (touches(d, r)) P82_Edge = 1;
      d = dist(P82_PlR, p, 1);
      if (d < (ld)r) {
        if (touches(d, r)) P82_Edge = 1;
        float f = (float)dist(P82_PlF, p, 1);
        if (sgn(f) == 0) { f = (float)((ld)f - (ld)r); res = 1; }
        else if (sgn((float)((ld)r + (ld)f)) == 0) res = 1;
        if (sgn(f) != 0) {
          d = dist(P82_PlT, p, 1);
          if (d < (ld)r) {
            if (touches(d, r)) P82_Edge = 1;
            d = dist(P82_PlB, p, 1);
            if (d < (ld)r) {
              if (touches(d, r)) P82_Edge = 1;
              if ((uint8_t)P60_Var1373C0 != 0) P82_Edge = 1;
              return res + 1;
            }
          }
        }
      }
    }
  }
  return 0;
}

/* 004268ef */
void P82_AddLight(const float *pos, int32_t radius, int32_t cr, int32_t cg, int32_t cb) {
  if (G2_011F43B0 == 0x14) return;
  if (!P76_InBox(pos, P82_LightGrid, P82_CellCX, P82_CellCY)) return;
  int32_t vis = P82_SphereVis3D(pos, (float)radius);
  float q[3];
  if (vis == 0 && P13_00b31f04 == 1) {
    q[0] = (float)((ld)P44_CamX - (ld)pos[0]); q[1] = (float)((ld)P44_CamY - (ld)pos[1]); q[2] = (float)((ld)P44_CamZ - (ld)pos[2]);
    q[0] = (float)((ld)q[0] + (ld)P44_CamX); q[1] = (float)((ld)q[1] + (ld)P44_CamY); q[2] = (float)((ld)q[2] + (ld)P44_CamZ);
    vis = P82_SphereVis3D(q, (float)radius);
  }
  if (vis == 0) return;
  q[0] = (float)((ld)pos[0] - (ld)P44_CamX); q[1] = (float)((ld)pos[1] - (ld)P44_CamY); q[2] = (float)((ld)pos[2] - (ld)P44_CamZ);
  P44_MatPtr = P44_ViewMatT;
  P44_Xform(q);
  uint8_t *e = (uint8_t *)G2_011F40E0 + (size_t)G2_011F43B0 * 0x24;
  G2_011F43B0++;
  memcpy(e, q, 12);
  memcpy(e + 0xc, &radius, 4);
  float r2 = (float)(radius * radius);
  memcpy(e + 0x1c, &r2, 4);
  float inv = (float)((ld)P8_00546020 / (ld)r2);
  memcpy(e + 0x20, &inv, 4);
  int32_t k = P14_00d17b18;
  float f;
  f = (float)((cr * k) >> 8); memcpy(e + 0x10, &f, 4);
  f = (float)((cg * k) >> 8); memcpy(e + 0x14, &f, 4);
  f = (float)((cb * k) >> 8); memcpy(e + 0x18, &f, 4);
}
