#include "ported82.h"
#include <string.h>

GAME_VAR_DEF(float, P82_FovX, 0x00b959ec)
GAME_VAR_DEF(float, P82_FovY, 0x00b949ec)
GAME_VAR_DEF(float, P82_FovXc, 0x011f40c0)
GAME_VAR_DEF(float, P82_FovYc, 0x01209644)
GAME_VAR_DEF(p82_plane_t, P82_PlL, 0x01209670)
GAME_VAR_DEF(p82_plane_t, P82_PlR, 0x01209600)
GAME_VAR_DEF(p82_plane_t, P82_PlF, 0x01209630)
GAME_VAR_DEF(p82_plane_t, P82_PlT, 0x01209650)
GAME_VAR_DEF(p82_plane_t, P82_PlB, 0x0124b6c0)
GAME_VAR_DEF(int32_t, P82_Edge, 0x01270c2c)
GAME_VAR_DEF(p82_grid_t, P82_LightGrid, 0x00cf2fa0)
GAME_VAR_DEF(int32_t, P82_CellCX, 0x00c97a00)
GAME_VAR_DEF(int32_t, P82_CellCY, 0x00c97a04)

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

/* 00427abe */
void P82_FrustumSetup2D(void) {
  float v[3];
  P82_FovXc = P82_FovX;
  P82_FovYc = P82_FovY;
  xf(-P82_FovXc, 0.0f, -P82_FovYc, v);
  P82_PlL[0] = v[0]; P82_PlL[1] = 0.0f; P82_PlL[2] = v[2];
  xf(P82_FovXc, 0.0f, -P82_FovYc, v);
  P82_PlR[0] = v[0]; P82_PlR[1] = 0.0f; P82_PlR[2] = v[2];
  xf(0.0f, 0.0f, -1.0f, v);
  P82_PlF[0] = v[0]; P82_PlF[1] = 0.0f; P82_PlF[2] = v[2];
  P77_Plane[0] = -v[0]; P77_Plane[1] = 0.0f; P77_Plane[2] = -v[2];
  xf(0.0f, 0.0f, 50.0f, v);
  P82_PlF[3] = (float)(((ld)v[2] + (ld)P44_CamZ) * (ld)P82_PlF[2] + ((ld)v[0] + (ld)P44_CamX) * (ld)P82_PlF[0]);
  xf(0.0f, 0.0f, P11_01270c24, v);
  P77_Plane[3] = (float)(((ld)v[2] + (ld)P44_CamZ) * (ld)P77_Plane[2] + ((ld)v[0] + (ld)P44_CamX) * (ld)P77_Plane[0]);
  xf(-320.0f, 0.0f, P43_ScaleA, v);
  P82_PlL[3] = plane_d(v, P82_PlL, 1);
  xf(320.0f, 0.0f, P43_ScaleA, v);
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
  xf(-P82_FovXc, 0.0f, -P82_FovYc, v);
  memcpy(P82_PlL, v, 12);
  xf(P82_FovXc, 0.0f, -P82_FovYc, v);
  memcpy(P82_PlR, v, 12);
  xf(0.0f, 0.0f, -1.0f, v);
  memcpy(P82_PlF, v, 12);
  P77_Plane[0] = -v[0]; P77_Plane[1] = -v[1]; P77_Plane[2] = -v[2];
  xf(0.0f, 0.0f, 50.0f, v);
  P82_PlF[3] = plane_d(v, P82_PlF, 1);
  xf(0.0f, 0.0f, P11_01270c24, v);
  P77_Plane[3] = plane_d(v, P77_Plane, 1);
  xf(-320.0f, 0.0f, P43_ScaleA, v);
  P82_PlL[3] = plane_d(v, P82_PlL, 1);
  xf(320.0f, 0.0f, P43_ScaleA, v);
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
