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

void P22_SetTexOp(int32_t a, int32_t b, int32_t c, int32_t mode, int32_t e) {
  /* v2.01: режим — 4-й аргумент grColorCombine (other, [ebp+0x14] в 0041e17b: 1 = GR_COMBINE_OTHER_TEXTURE), не 5-й (invert);
     прежний перенос брал 5-й — заставки рисовались без текстуры (и в hook) */
  (void)a; (void)b; (void)c; (void)e;
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
