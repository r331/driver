#include "ported22.h"
#include "../platform/plat.h"
#include "unported.h"
GAME_VAR_DEF(int32_t, P22_DevReady, 0x00a421c0)
GAME_VAR_DEF(int32_t, P22_AlphaRef, 0x0054ef54)
GAME_VAR_DEF(int32_t, P22_ZFuncCur, 0x0054ef58)
GAME_VAR_DEF(int32_t, P22_AlphaFunc, 0x0054ef34)
GAME_VAR_DEF(int32_t, P22_ZWriteOff, 0x00a421d4)
GAME_VAR_DEF(int32_t, P22_AtestA, 0x0054ef4c)
GAME_VAR_DEF(int32_t, P22_AtestB, 0x0054ef50)
GAME_VAR_DEF(int32_t, P22_TexOpCur, 0x0054ef40)
GAME_VAR_DEF(int32_t, P22_TexVarA, 0x00a421e4)
GAME_VAR_DEF(int32_t, P22_TexVarB, 0x00a421e8)
GAME_VAR_DEF(int32_t, P22_VpX, 0x00a421ac)
GAME_VAR_DEF(int32_t, P22_VpY, 0x00a421b0)
GAME_VAR_DEF(int32_t, P22_VpW, 0x00a421b4)
GAME_VAR_DEF(int32_t, P22_VpH, 0x00a421b8)

enum { RS_ZWRITE = 14, RS_ALPHATEST = 15, RS_CULL = 22, RS_ZFUNC = 23, RS_ALPHAREF = 24, RS_ALPHAFUNC = 25 };

void P22_BeginScene(void) { if (P22_DevReady != 0) plat_scene_begin(); }
void P22_EndScene(void) { if (P22_DevReady != 0) plat_scene_end(); }
void P22_SetAlphaRef(uint32_t v) { plat_set_render_state(RS_ALPHAREF, v & 0xff); }

void P22_SetZFunc(int32_t mode) {
  if (mode == P22_ZFuncCur) return;
  P22_ZFuncCur = mode;
  G6Call00422AE7();
  if (mode >= 0 && mode <= 7) plat_set_render_state(RS_ZFUNC, (uint32_t)mode + 1);
}

void P22_SetAlphaFunc(int32_t mode) {
  if (mode == P22_AlphaRef) return;
  P22_AlphaRef = mode;
  G6Call00422AE7();
  P22_AlphaFunc = (mode == 7) ? 8 : 2;
  plat_set_render_state(RS_ALPHAFUNC, (uint32_t)P22_AlphaFunc);
}

void P22_SetZWrite(int32_t mode) {
  G6Call00422AE7();
  plat_set_render_state(RS_ZWRITE, mode == 1 ? 1 : 0);
  P22_ZWriteOff = (mode != 1);
}

void P22_SetCull(int32_t mode) {
  if (P22_DevReady == 0) return;
  if (mode == 0) plat_set_render_state(RS_CULL, 1);
  else if (mode == 1) plat_set_render_state(RS_CULL, 3);
  else if (mode == 2) plat_set_render_state(RS_CULL, 2);
}

void P22_SetAlphaTest(int32_t a, int32_t b, int32_t mode, int32_t flag) {
  (void)a; (void)b;
  if (mode == P22_AtestA && flag == P22_AtestB) return;
  P22_AtestA = mode;
  P22_AtestB = flag;
  G6Call00422AE7();
  plat_set_render_state(RS_ALPHATEST, flag == 2 ? 0 : 1);
}

void P22_SetTexFilter(int32_t a, int32_t min_linear, int32_t mag_linear) {
  (void)a;
  G6Call00422AE7();
  plat_set_tex_stage(0, 17, min_linear == 0 ? 1 : 2);
  plat_set_tex_stage(0, 16, mag_linear == 0 ? 1 : 2);
}

void P22_SetViewport(int32_t x0, int32_t y0, int32_t x1, int32_t y1) {
  if (P22_DevReady == 0) return;
  G6Call00422AE7();
  P22_VpX = x0; P22_VpY = y0; P22_VpW = x1 - x0; P22_VpH = y1 - y0;
  plat_set_viewport(P22_VpX, P22_VpY, P22_VpW, P22_VpH);
}

void P22_SetTexOp(int32_t a, int32_t b, int32_t c, int32_t d, int32_t mode) {
  (void)a; (void)b; (void)c; (void)d;
  if (P22_DevReady == 0 || mode == P22_TexOpCur) return;
  P22_TexOpCur = mode;
  G6Call00422AE7();
  if (mode == 1) {
    plat_set_tex_stage(0, 1, 4);
    P22_TexVarA = P22_TexVarB;
  } else {
    plat_set_tex_stage(0, 1, 1);
    if (P22_TexVarA != 0x20) { P22_TexVarB = P22_TexVarA; P22_TexVarA = 0x20; }
  }
}
