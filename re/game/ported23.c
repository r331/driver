/* ported23.c — Direct3D render helpers (English overview): converting the game's vertex records to
   D3DTLVERTEX (plat_vertex), drawing lines, blend modes, the initial render states and Z clearing.
   Game vertex record: 11 dwords — [0] x, [1] y, [3] R, [4] G, [5] B (floats 0..255), [8] w (= 1/z),
   [9] u, [10] v (texture coordinates before the 1/w scale).  Render-state and blend numbers are the
   Direct3D 5 enum values. */
#include "ported23.h"
#include "ported22.h"
#include "unported.h"
#include "flush.h"
#include <math.h>
#include <string.h>
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P23_ScaleUV_A")
#undef P23_ScaleUV_A
#pragma push_macro("P23_ScaleUV_A") /*gvi*/
#undef P23_ScaleUV_A /*gvi*/
float P23_ScaleUV_A;
#pragma pop_macro("P23_ScaleUV_A") /*gvi*/
#pragma pop_macro("P23_ScaleUV_A")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P23_ScaleUV_B")
#undef P23_ScaleUV_B
#pragma push_macro("P23_ScaleUV_B") /*gvi*/
#undef P23_ScaleUV_B /*gvi*/
float P23_ScaleUV_B;
#pragma pop_macro("P23_ScaleUV_B") /*gvi*/
#pragma pop_macro("P23_ScaleUV_B")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P23_ZScale_A")
#undef P23_ZScale_A
#pragma push_macro("P23_ZScale_A") /*gvi*/
#undef P23_ZScale_A /*gvi*/
float P23_ZScale_A;
#pragma pop_macro("P23_ZScale_A") /*gvi*/
#pragma pop_macro("P23_ZScale_A")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P23_ZScale_B")
#undef P23_ZScale_B
#pragma push_macro("P23_ZScale_B") /*gvi*/
#undef P23_ZScale_B /*gvi*/
float P23_ZScale_B;
#pragma pop_macro("P23_ZScale_B") /*gvi*/
#pragma pop_macro("P23_ZScale_B")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P23_ZNum")
#undef P23_ZNum
#pragma push_macro("P23_ZNum") /*gvi*/
#undef P23_ZNum /*gvi*/
float P23_ZNum;
#pragma pop_macro("P23_ZNum") /*gvi*/
#pragma pop_macro("P23_ZNum")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P23_ZDenA")
#undef P23_ZDenA
#pragma push_macro("P23_ZDenA") /*gvi*/
#undef P23_ZDenA /*gvi*/
float P23_ZDenA;
#pragma pop_macro("P23_ZDenA") /*gvi*/
#pragma pop_macro("P23_ZDenA")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P23_ZBias")
#undef P23_ZBias
#pragma push_macro("P23_ZBias") /*gvi*/
#undef P23_ZBias /*gvi*/
float P23_ZBias;
#pragma pop_macro("P23_ZBias") /*gvi*/
#pragma pop_macro("P23_ZBias")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P23_BlendCur")
#undef P23_BlendCur
#pragma push_macro("P23_BlendCur") /*gvi*/
#undef P23_BlendCur /*gvi*/
int32_t P23_BlendCur;
#pragma pop_macro("P23_BlendCur") /*gvi*/
#pragma pop_macro("P23_BlendCur")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P23_BlendCur2")
#undef P23_BlendCur2
#pragma push_macro("P23_BlendCur2") /*gvi*/
#undef P23_BlendCur2 /*gvi*/
int32_t P23_BlendCur2;
#pragma pop_macro("P23_BlendCur2") /*gvi*/
#pragma pop_macro("P23_BlendCur2")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P23_DevCaps")
#undef P23_DevCaps
#pragma push_macro("P23_DevCaps") /*gvi*/
#undef P23_DevCaps /*gvi*/
uint32_t P23_DevCaps;
#pragma pop_macro("P23_DevCaps") /*gvi*/
#pragma pop_macro("P23_DevCaps")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P23_AlphaMode")
#undef P23_AlphaMode
#pragma push_macro("P23_AlphaMode") /*gvi*/
#undef P23_AlphaMode /*gvi*/
int32_t P23_AlphaMode;
#pragma pop_macro("P23_AlphaMode") /*gvi*/
#pragma pop_macro("P23_AlphaMode")
#endif

enum { RS_ZENABLE = 7, RS_ALPHATEST_EN = 15, RS_SRCBLEND = 19, RS_DESTBLEND = 20, RS_ALPHABLEND_EN = 27, RS_ALPHAFUNC = 25 };
enum { TSS_COLOROP = 1, TSS_COLORARG1 = 2, TSS_COLORARG2 = 3, TSS_ALPHAOP = 4, TSS_ALPHAARG1 = 5 };
/* D3DBLEND factors. */
enum { BLEND_ZERO = 1, BLEND_ONE = 2, BLEND_INVSRCCOLOR = 4, BLEND_SRCALPHA = 5, BLEND_DESTCOLOR = 9 };

static float f32(int32_t bits) { float f; memcpy(&f, &bits, 4); return f; }
/* D3DCOLOR 0x00RRGGBB from the float colour fields, rounded like fistp. */
static uint32_t pack_rgb(const int32_t *in) {
  /* fistp: округление к ближайшему чётному (режим FPU по умолчанию) */
  return ((uint32_t)lrintf(f32(in[3])) << 16) | (uint32_t)lrintf(f32(in[5])) | ((uint32_t)lrintf(f32(in[4])) << 8);
}
#ifndef RE_HOOK_BUILD
static int sky_depth;
int P23_SetSkyDepth(int enabled) {
  int previous = sky_depth;
  sky_depth = enabled != 0;
  return previous;
}
#endif

/* Converts game vertex `in` to a TLVERTEX.  rhw = w; u, v are scaled by uvscale / w; depth z = 1 - w * scale
   when P23_ZBias == 0, else a biased hyperbolic mapping (variant A: 1 - ZNum / (ZDenA / w + ZBias),
   variant B: 1 - ZNum / (w + ZBias)).  Native: while the sky pass is active (P23_SetSkyDepth) z = 1 (far).
   TODO(RE): why the game keeps two variants (A/B with separate scales) is not established. */
static void conv(const int32_t *in, plat_vertex *out, float uvscale, int variant_b) {
  float w = f32(in[8]);
  float k = uvscale / w;
  out->x = f32(in[0]); out->y = f32(in[1]);
  out->rhw = w;
  out->color = pack_rgb(in);
  out->specular = 0;
#ifndef RE_HOOK_BUILD
  if (sky_depth) out->z = 1.0f;
  else
#endif
  if (P23_ZBias == 0.0f) out->z = 1.0f - w * (variant_b ? P23_ZScale_B : P23_ZScale_A);
  else if (variant_b) out->z = 1.0f - P23_ZNum / (w + P23_ZBias);
  else { float t = P23_ZDenA / w + P23_ZBias; out->z = 1.0f - P23_ZNum / t; }
  out->u = f32(in[9]) * k;
  out->v = f32(in[10]) * k;
}
/* P23_ConvVertexA — Game.exe 00421cfe; P23_ConvVertexB — Game.exe 00421db8 (see conv above). */
void P23_ConvVertexA(const int32_t *in, plat_vertex *out) { conv(in, out, P23_ScaleUV_A, 0); }
void P23_ConvVertexB(const int32_t *in, plat_vertex *out) { conv(in, out, P23_ScaleUV_B, 1); }

/* P23_DrawLineA — Game.exe 0041e462; P23_DrawLineB — Game.exe 0041e4b9: a 2-point line from two game
   vertices (variant A / B conversion), skipped while the device is not ready. */
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

/* P23_SetBlendMode — Game.exe 0041d9d2.  Sets the alpha-blend render states for (mode, sub); repeated calls
   with the same pair do nothing.  Flushes queued geometry first (G6Call00422AE7) and undoes the
   texture-alpha trick of a previous call (P23_AlphaMode).
     mode 2           — (src DESTCOLOR, dst ONE); falls back to mode 4 without device cap 0x20;
     mode 4, sub 0    — blending off; sub 4 — (ONE, ONE) if cap 4, else off;
     mode 0, sub 5    — (ZERO, SRCALPHA) without cap 8; with cap 8 colour arg = diffuse, alpha function 2
                        and (ZERO, INVSRCCOLOR); blending off without cap 1;
     mode 0, other    — (ZERO, ONE) without cap 2, else (ZERO, INVSRCCOLOR).
   TODO(RE): the P23_DevCaps bits (1, 2, 4, 8, 0x20) are the game's own blend-support flags; how they are
   derived from the D3D device caps is not established, and the "mode/sub" meanings are unconfirmed. */
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
      plat_set_render_state(RS_SRCBLEND, BLEND_DESTCOLOR); plat_set_render_state(RS_DESTBLEND, BLEND_ONE);
      plat_set_render_state(RS_ALPHABLEND_EN, 1); plat_set_render_state(RS_ALPHATEST_EN, 1);
    }
  }
  if (mode == 4) {
    if (sub == 0) plat_set_render_state(RS_ALPHABLEND_EN, 0);
    else if (sub == 4) {
      if ((P23_DevCaps & 4) == 0) plat_set_render_state(RS_ALPHABLEND_EN, 0);
      else {
        plat_set_render_state(RS_SRCBLEND, BLEND_ONE); plat_set_render_state(RS_DESTBLEND, BLEND_ONE);
        plat_set_render_state(RS_ALPHABLEND_EN, 1); plat_set_render_state(RS_ALPHATEST_EN, 1);
      }
    }
  } else if (mode == 0) {
    if (sub == 5) {
      if ((P23_DevCaps & 1) == 0) plat_set_render_state(RS_ALPHABLEND_EN, 0);
      else {
        if ((P23_DevCaps & 8) == 0) { plat_set_render_state(RS_SRCBLEND, BLEND_ZERO); plat_set_render_state(RS_DESTBLEND, BLEND_SRCALPHA); }
        else {
          plat_set_tex_stage(0, TSS_COLORARG1, 0);
          plat_set_render_state(RS_ALPHAFUNC, 2);
          P23_AlphaMode = 1;
          plat_set_render_state(RS_SRCBLEND, BLEND_ZERO); plat_set_render_state(RS_DESTBLEND, BLEND_INVSRCCOLOR);
        }
        plat_set_render_state(RS_ALPHABLEND_EN, 1); plat_set_render_state(RS_ALPHATEST_EN, 1);
      }
    } else if ((P23_DevCaps & 2) == 0) {
      plat_set_render_state(RS_SRCBLEND, BLEND_ZERO); plat_set_render_state(RS_DESTBLEND, BLEND_ONE);
      plat_set_render_state(RS_ALPHABLEND_EN, 1); plat_set_render_state(RS_ALPHATEST_EN, 1);
    } else {
      plat_set_render_state(RS_SRCBLEND, BLEND_ZERO); plat_set_render_state(RS_DESTBLEND, BLEND_INVSRCCOLOR);
      plat_set_render_state(RS_ALPHABLEND_EN, 1); plat_set_render_state(RS_ALPHATEST_EN, 1);
    }
  }
}

/* P23_InitRenderStates — Game.exe 00421521.  Begins the scene, selects the viewport and sets the initial
   render states: ZENABLE 1, ZWRITEENABLE 1, ZFUNC LESSEQUAL, SHADEMODE GOURAUD, TEXTUREMAG/MIN NEAREST,
   ALPHABLEND off, FILLMODE SOLID, DITHER on, SPECULAR off, ANTIALIAS off, CULLMODE NONE, ALPHAREF 0,
   SUBPIXEL on; stage 0 = texture * diffuse colour, texture alpha; stage 1 disabled. */
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

/* P23_ClearZ — Game.exe 00420e93.  Clears the depth of the viewport rectangle to the float whose bits are
   zbits.  Returns 0 when there is no viewport, else 1. */
int32_t P23_ClearZ(void *viewport, uint32_t zbits) {
  float z; memcpy(&z, &zbits, 4);
  if (viewport == NULL) return 0;
  plat_clear_depth(viewport, P22_VpX, P22_VpY, P22_VpW, P22_VpH, z);
  return 1;
}
