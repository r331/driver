/* ported22.c — render device state for the Direct3D renderer (English overview; original notes follow).
   Game.exe drives rendering through Glide-style calls; on the Direct3D path these functions translate
   them into Direct3D render states via the platform layer (plat_set_render_state / plat_set_tex_stage).
   Each setter caches the last value and flushes pending primitives (00422ae7) before a change.
   All except Begin/EndScene are __stdcall in Game.exe (the hook build installs a thunk, platform/win32/hook.c). */
#include "ported22.h"
#include "../platform/plat.h"
#include "unported.h"
#include "flush.h"
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P22_DevReady")
#undef P22_DevReady
#pragma push_macro("P22_DevReady") /*gvi*/
#undef P22_DevReady /*gvi*/
int32_t P22_DevReady;
#pragma pop_macro("P22_DevReady") /*gvi*/
#pragma pop_macro("P22_DevReady")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P22_AlphaRef")
#undef P22_AlphaRef
#pragma push_macro("P22_AlphaRef") /*gvi*/
#undef P22_AlphaRef /*gvi*/
int32_t P22_AlphaRef;
#pragma pop_macro("P22_AlphaRef") /*gvi*/
#pragma pop_macro("P22_AlphaRef")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P22_ZFuncCur")
#undef P22_ZFuncCur
#pragma push_macro("P22_ZFuncCur") /*gvi*/
#undef P22_ZFuncCur /*gvi*/
int32_t P22_ZFuncCur;
#pragma pop_macro("P22_ZFuncCur") /*gvi*/
#pragma pop_macro("P22_ZFuncCur")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P22_AlphaFunc")
#undef P22_AlphaFunc
#pragma push_macro("P22_AlphaFunc") /*gvi*/
#undef P22_AlphaFunc /*gvi*/
int32_t P22_AlphaFunc;
#pragma pop_macro("P22_AlphaFunc") /*gvi*/
#pragma pop_macro("P22_AlphaFunc")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P22_ZWriteOff")
#undef P22_ZWriteOff
#pragma push_macro("P22_ZWriteOff") /*gvi*/
#undef P22_ZWriteOff /*gvi*/
int32_t P22_ZWriteOff;
#pragma pop_macro("P22_ZWriteOff") /*gvi*/
#pragma pop_macro("P22_ZWriteOff")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P22_AtestA")
#undef P22_AtestA
#pragma push_macro("P22_AtestA") /*gvi*/
#undef P22_AtestA /*gvi*/
int32_t P22_AtestA;
#pragma pop_macro("P22_AtestA") /*gvi*/
#pragma pop_macro("P22_AtestA")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P22_AtestB")
#undef P22_AtestB
#pragma push_macro("P22_AtestB") /*gvi*/
#undef P22_AtestB /*gvi*/
int32_t P22_AtestB;
#pragma pop_macro("P22_AtestB") /*gvi*/
#pragma pop_macro("P22_AtestB")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P22_TexOpCur")
#undef P22_TexOpCur
#pragma push_macro("P22_TexOpCur") /*gvi*/
#undef P22_TexOpCur /*gvi*/
int32_t P22_TexOpCur;
#pragma pop_macro("P22_TexOpCur") /*gvi*/
#pragma pop_macro("P22_TexOpCur")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P22_TexVarA")
#undef P22_TexVarA
#pragma push_macro("P22_TexVarA") /*gvi*/
#undef P22_TexVarA /*gvi*/
int32_t P22_TexVarA;
#pragma pop_macro("P22_TexVarA") /*gvi*/
#pragma pop_macro("P22_TexVarA")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P22_TexVarB")
#undef P22_TexVarB
#pragma push_macro("P22_TexVarB") /*gvi*/
#undef P22_TexVarB /*gvi*/
int32_t P22_TexVarB;
#pragma pop_macro("P22_TexVarB") /*gvi*/
#pragma pop_macro("P22_TexVarB")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P22_VpX")
#undef P22_VpX
#pragma push_macro("P22_VpX") /*gvi*/
#undef P22_VpX /*gvi*/
int32_t P22_VpX;
#pragma pop_macro("P22_VpX") /*gvi*/
#pragma pop_macro("P22_VpX")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P22_VpY")
#undef P22_VpY
#pragma push_macro("P22_VpY") /*gvi*/
#undef P22_VpY /*gvi*/
int32_t P22_VpY;
#pragma pop_macro("P22_VpY") /*gvi*/
#pragma pop_macro("P22_VpY")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P22_VpW")
#undef P22_VpW
#pragma push_macro("P22_VpW") /*gvi*/
#undef P22_VpW /*gvi*/
int32_t P22_VpW;
#pragma pop_macro("P22_VpW") /*gvi*/
#pragma pop_macro("P22_VpW")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P22_VpH")
#undef P22_VpH
#pragma push_macro("P22_VpH") /*gvi*/
#undef P22_VpH /*gvi*/
int32_t P22_VpH;
#pragma pop_macro("P22_VpH") /*gvi*/
#pragma pop_macro("P22_VpH")
#endif

/* Direct3D render-state ids (D3DRENDERSTATETYPE) as passed to plat_set_render_state. */
enum { RS_ZWRITE = 14, RS_ALPHATEST = 15, RS_CULL = 22, RS_ZFUNC = 23, RS_ALPHAREF = 24, RS_ALPHAFUNC = 25 };
/* Direct3D values used below: D3DCULL_*, D3DCMP_*, texture-stage states D3DTSS_* and their values. */
enum { D3D_CULL_NONE = 1, D3D_CULL_CW = 2, D3D_CULL_CCW = 3 };
enum { D3D_CMP_LESS = 2, D3D_CMP_ALWAYS = 8 };
enum { TSS_COLOROP = 1, TSS_MAGFILTER = 16, TSS_MINFILTER = 17 };
enum { TFILTER_POINT = 1, TFILTER_LINEAR = 2 };   /* D3DTFG_ / D3DTFN_ POINT, LINEAR */
enum { TOP_DISABLE = 1, TOP_MODULATE = 4 };       /* D3DTOP_DISABLE, D3DTOP_MODULATE */

/* P22_BeginScene — Game.exe 0041e037.  BeginScene, if the device is ready (P22_DevReady). */
void P22_BeginScene(void) { if (P22_DevReady != 0) plat_scene_begin(); }
/* P22_EndScene — Game.exe 0041e056.  EndScene, if the device is ready. */
void P22_EndScene(void) { if (P22_DevReady != 0) plat_scene_end(); }
/* P22_SetAlphaRef — Game.exe 0041de1d.  Alpha-test reference = v & 0xff. */
void P22_SetAlphaRef(uint32_t v) { plat_set_render_state(RS_ALPHAREF, v & 0xff); }

/* P22_SetZFunc — Game.exe 0041e28a.  Depth compare function: Glide GR_CMP_* 0..7 -> D3DCMP_* 1..8.
   Cached in P22_ZFuncCur; out-of-range values only update the cache. */
void P22_SetZFunc(int32_t mode) {
  if (mode == P22_ZFuncCur) return;
  P22_ZFuncCur = mode;
  G6Call00422AE7();
  if (mode >= 0 && mode <= 7) plat_set_render_state(RS_ZFUNC, (uint32_t)mode + 1);   /* GR_CMP_NEVER..ALWAYS (0..7) -> D3DCMP_NEVER..ALWAYS (1..8) */
}

/* P22_SetAlphaFunc — Game.exe 0041ddc5.  Alpha-test compare function: mode 7 (always) -> D3DCMP_ALWAYS,
   anything else -> D3DCMP_LESS; the D3D value is kept in P22_AlphaFunc.
   Note: the cache of the last mode is the variable named P22_AlphaRef, not the
   reference value.  TODO(RE): rename that global once its address users are checked. */
void P22_SetAlphaFunc(int32_t mode) {
  if (mode == P22_AlphaRef) return;
  P22_AlphaRef = mode;
  G6Call00422AE7();
  P22_AlphaFunc = (mode == 7) ? D3D_CMP_ALWAYS : D3D_CMP_LESS;   /* Glide GR_CMP_ALWAYS (7) -> ALWAYS, anything else -> LESS */
  plat_set_render_state(RS_ALPHAFUNC, (uint32_t)P22_AlphaFunc);
}

/* P22_SetZWrite — Game.exe 0041e404.  Depth writes on for mode 1, off otherwise (P22_ZWriteOff = 1 when off). */
void P22_SetZWrite(int32_t mode) {
  G6Call00422AE7();
  plat_set_render_state(RS_ZWRITE, mode == 1 ? 1 : 0);
  P22_ZWriteOff = (mode != 1);
}

/* P22_SetCull — Game.exe 0041e215.  Glide cull mode 0 / 1 / 2 (disable / negative / positive) ->
   D3DCULL_NONE / CCW / CW.  Other values are ignored. */
void P22_SetCull(int32_t mode) {
  if (P22_DevReady == 0) return;
  if (mode == 0) plat_set_render_state(RS_CULL, D3D_CULL_NONE);        /* GR_CULL_DISABLE */
  else if (mode == 1) plat_set_render_state(RS_CULL, D3D_CULL_CCW);   /* GR_CULL_NEGATIVE */
  else if (mode == 2) plat_set_render_state(RS_CULL, D3D_CULL_CW);    /* GR_CULL_POSITIVE */
}

/* P22_SetAlphaTest — Game.exe 0041dd37.  Mirrors a Glide alpha-combine call: alpha testing is off when
   flag == 2, on otherwise.  a and b are ignored; (mode, flag) is cached in P22_AtestA/B.
   TODO(RE): unsure which Glide call/arguments a, b, mode, flag correspond to. */
void P22_SetAlphaTest(int32_t a, int32_t b, int32_t mode, int32_t flag) {
  (void)a; (void)b;
  if (mode == P22_AtestA && flag == P22_AtestB) return;
  P22_AtestA = mode;
  P22_AtestB = flag;
  G6Call00422AE7();
  plat_set_render_state(RS_ALPHATEST, flag == 2 ? 0 : 1);
}

/* P22_SetTexFilter — Game.exe 0041f6a9.  Texture min/mag filter: 0 = point, non-zero = linear (stage 0).
   The first argument (Glide TMU) is ignored. */
void P22_SetTexFilter(int32_t a, int32_t min_linear, int32_t mag_linear) {
  (void)a;
  G6Call00422AE7();
  plat_set_tex_stage(0, TSS_MINFILTER, min_linear == 0 ? TFILTER_POINT : TFILTER_LINEAR);
  plat_set_tex_stage(0, TSS_MAGFILTER, mag_linear == 0 ? TFILTER_POINT : TFILTER_LINEAR);
}

/* P22_SetViewport — Game.exe 0041e08a.  Viewport from corners (x0, y0)-(x1, y1); stored in P22_Vp*. */
void P22_SetViewport(int32_t x0, int32_t y0, int32_t x1, int32_t y1) {
  if (P22_DevReady == 0) return;
  G6Call00422AE7();
  P22_VpX = x0; P22_VpY = y0; P22_VpW = x1 - x0; P22_VpH = y1 - y0;
  plat_set_viewport(P22_VpX, P22_VpY, P22_VpW, P22_VpH);
}

/* P22_SetTexOp — Game.exe 0041e14f.  Mirrors grColorCombine: `mode` is its 4th argument ("other");
   1 = GR_COMBINE_OTHER_TEXTURE -> stage-0 colour op MODULATE (textured), anything else -> DISABLE.
   Also swaps P22_TexVarA with a saved value (0x20 while untextured).  TODO(RE): unsure what TexVarA is. */
void P22_SetTexOp(int32_t a, int32_t b, int32_t c, int32_t mode, int32_t e) {
  /* v2.01: режим — 4-й аргумент grColorCombine (other, [ebp+0x14] в 0041e17b: 1 = GR_COMBINE_OTHER_TEXTURE), не 5-й (invert);
     прежний перенос брал 5-й — заставки рисовались без текстуры (и в hook) */
  (void)a; (void)b; (void)c; (void)e;
  if (P22_DevReady == 0 || mode == P22_TexOpCur) return;
  P22_TexOpCur = mode;
  G6Call00422AE7();
  if (mode == 1) {
    plat_set_tex_stage(0, TSS_COLOROP, TOP_MODULATE);
    P22_TexVarA = P22_TexVarB;
  } else {
    plat_set_tex_stage(0, TSS_COLOROP, TOP_DISABLE);
    if (P22_TexVarA != 0x20) { P22_TexVarB = P22_TexVarA; P22_TexVarA = 0x20; }
  }
}
