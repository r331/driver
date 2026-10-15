#include "ported23.h"
#include "ported22.h"
#include "unported.h"
#include "flush.h"
#include <math.h>
#include <string.h>
GAME_VAR_DEF(float, P23_ScaleUV_A, 0x0054ef60)
GAME_VAR_DEF(float, P23_ScaleUV_B, 0x0054ef6c)
GAME_VAR_DEF(float, P23_ZScale_A, 0x0054ef64)
GAME_VAR_DEF(float, P23_ZScale_B, 0x0054ef68)
GAME_VAR_DEF(float, P23_ZNum, 0x0054ef3c)
GAME_VAR_DEF(float, P23_ZDenA, 0x0054ef38)
GAME_VAR_DEF(float, P23_ZBias, 0x00a4217c)
GAME_VAR_DEF(int32_t, P23_BlendCur, 0x0054ef44)
GAME_VAR_DEF(int32_t, P23_BlendCur2, 0x0054ef48)
GAME_VAR_DEF(uint32_t, P23_DevCaps, 0x00a421dc)
GAME_VAR_DEF(int32_t, P23_AlphaMode, 0x00a421e0)

enum { RS_ZENABLE = 7, RS_ALPHATEST_EN = 15, RS_SRCBLEND = 19, RS_DESTBLEND = 20, RS_ALPHABLEND_EN = 27, RS_ALPHAFUNC = 25 };
enum { TSS_COLOROP = 1, TSS_COLORARG1 = 2, TSS_COLORARG2 = 3, TSS_ALPHAOP = 4, TSS_ALPHAARG1 = 5 };

static float f32(int32_t bits) { float f; memcpy(&f, &bits, 4); return f; }
static uint32_t pack_rgb(const int32_t *in) {
  /* fistp: округление к ближайшему чётному (режим FPU по умолчанию) */
  return ((uint32_t)lrintf(f32(in[3])) << 16) | (uint32_t)lrintf(f32(in[5])) | ((uint32_t)lrintf(f32(in[4])) << 8);
}
static void conv(const int32_t *in, plat_vertex *out, float uvscale, int variant_b) {
  float w = f32(in[8]);
  float k = uvscale / w;
  out->x = f32(in[0]); out->y = f32(in[1]);
  out->rhw = w;
  out->color = pack_rgb(in);
  out->specular = 0;
  if (P23_ZBias == 0.0f) out->z = 1.0f - w * (variant_b ? P23_ZScale_B : P23_ZScale_A);
  else if (variant_b) out->z = 1.0f - P23_ZNum / (w + P23_ZBias);
  else { float t = P23_ZDenA / w + P23_ZBias; out->z = 1.0f - P23_ZNum / t; }
  out->u = f32(in[9]) * k;
  out->v = f32(in[10]) * k;
}
void P23_ConvVertexA(const int32_t *in, plat_vertex *out) { conv(in, out, P23_ScaleUV_A, 0); }
void P23_ConvVertexB(const int32_t *in, plat_vertex *out) { conv(in, out, P23_ScaleUV_B, 1); }

void P23_DrawLineA(const int32_t *a, const int32_t *b) {
  plat_vertex v[2];
  if (P22_DevReady == 0) return;
  P23_ConvVertexA(a, &v[0]); P23_ConvVertexA(b, &v[1]);
  plat_draw_lines(v, 2);
}
void P23_DrawLineB(const int32_t *a, const int32_t *b) {
  plat_vertex v[2];
  if (P22_DevReady == 0) return;
  P23_ConvVertexB(a, &v[0]); P23_ConvVertexB(b, &v[1]);
  plat_draw_lines(v, 2);
}

void P23_SetBlendMode(int32_t mode, int32_t sub) {
  if (mode == P23_BlendCur && sub == P23_BlendCur2) return;
  P23_BlendCur = mode; P23_BlendCur2 = sub;
  G6Call00422AE7();
  if (P23_AlphaMode != 0) {
    plat_set_render_state(RS_ALPHAFUNC, (uint32_t)P22_AlphaFunc);
    plat_set_tex_stage(0, TSS_COLORARG1, 2);
    P23_AlphaMode = 0;
  }
  if (mode == 2) {
    if ((P23_DevCaps & 0x20) == 0) mode = 4;
    else {
      plat_set_render_state(RS_SRCBLEND, 9); plat_set_render_state(RS_DESTBLEND, 2);
      plat_set_render_state(RS_ALPHABLEND_EN, 1); plat_set_render_state(RS_ALPHATEST_EN, 1);
    }
  }
  if (mode == 4) {
    if (sub == 0) plat_set_render_state(RS_ALPHABLEND_EN, 0);
    else if (sub == 4) {
      if ((P23_DevCaps & 4) == 0) plat_set_render_state(RS_ALPHABLEND_EN, 0);
      else {
        plat_set_render_state(RS_SRCBLEND, 2); plat_set_render_state(RS_DESTBLEND, 2);
        plat_set_render_state(RS_ALPHABLEND_EN, 1); plat_set_render_state(RS_ALPHATEST_EN, 1);
      }
    }
  } else if (mode == 0) {
    if (sub == 5) {
      if ((P23_DevCaps & 1) == 0) plat_set_render_state(RS_ALPHABLEND_EN, 0);
      else {
        if ((P23_DevCaps & 8) == 0) { plat_set_render_state(RS_SRCBLEND, 1); plat_set_render_state(RS_DESTBLEND, 5); }
        else {
          plat_set_tex_stage(0, TSS_COLORARG1, 0);
          plat_set_render_state(RS_ALPHAFUNC, 2);
          P23_AlphaMode = 1;
          plat_set_render_state(RS_SRCBLEND, 1); plat_set_render_state(RS_DESTBLEND, 4);
        }
        plat_set_render_state(RS_ALPHABLEND_EN, 1); plat_set_render_state(RS_ALPHATEST_EN, 1);
      }
    } else if ((P23_DevCaps & 2) == 0) {
      plat_set_render_state(RS_SRCBLEND, 1); plat_set_render_state(RS_DESTBLEND, 2);
      plat_set_render_state(RS_ALPHABLEND_EN, 1); plat_set_render_state(RS_ALPHATEST_EN, 1);
    } else {
      plat_set_render_state(RS_SRCBLEND, 1); plat_set_render_state(RS_DESTBLEND, 4);
      plat_set_render_state(RS_ALPHABLEND_EN, 1); plat_set_render_state(RS_ALPHATEST_EN, 1);
    }
  }
}

void P23_InitRenderStates(void) {
  P22_BeginScene();
  plat_set_current_viewport();
  static const uint8_t rs[][2] = { {7,1},{14,1},{23,4},{9,2},{17,1},{18,1},{27,0},{8,3},{26,1},{29,0},{2,0},{22,1},{24,0},{31,1} };
  for (unsigned i = 0; i < sizeof rs / sizeof rs[0]; i++) plat_set_render_state(rs[i][0], rs[i][1]);
  plat_set_tex_stage(0, TSS_COLOROP, 4);
  plat_set_tex_stage(0, TSS_COLORARG1, 2);
  plat_set_tex_stage(0, TSS_COLORARG2, 0);
  plat_set_tex_stage(0, TSS_ALPHAOP, 2);
  plat_set_tex_stage(0, TSS_ALPHAARG1, 2);
  plat_set_tex_stage(1, TSS_COLOROP, 1);
}

int32_t P23_ClearZ(void *viewport, uint32_t zbits) {
  float z; memcpy(&z, &zbits, 4);
  if (viewport == NULL) return 0;
  plat_clear_depth(viewport, P22_VpX, P22_VpY, P22_VpW, P22_VpH, z);
  return 1;
}
