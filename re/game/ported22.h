#pragma once
#include "gvar.h"
#include <stdint.h>
/* Состояние устройства рендера (Direct3D в оригинале) через plat_*: сцена, z-функция, альфа-тест, cull, viewport, фильтры.
   Все функции кроме Begin/EndScene в оригинале __stdcall (ret N); в hook-сборке re_hook ставит переходник (platform/win32/hook.c). */
#define P22_DevReady   GAME_VAR(int32_t, P22_DevReady, 0x00a421c0)
#define P22_AlphaRef   GAME_VAR(int32_t, P22_AlphaRef, 0x0054ef54)
#define P22_ZFuncCur   GAME_VAR(int32_t, P22_ZFuncCur, 0x0054ef58)
#define P22_AlphaFunc  GAME_VAR(int32_t, P22_AlphaFunc, 0x0054ef34)
#define P22_ZWriteOff  GAME_VAR(int32_t, P22_ZWriteOff, 0x00a421d4)
#define P22_AtestA     GAME_VAR(int32_t, P22_AtestA, 0x0054ef4c)
#define P22_AtestB     GAME_VAR(int32_t, P22_AtestB, 0x0054ef50)
#define P22_TexOpCur   GAME_VAR(int32_t, P22_TexOpCur, 0x0054ef40)
#define P22_TexVarA    GAME_VAR(int32_t, P22_TexVarA, 0x00a421e4)
#define P22_TexVarB    GAME_VAR(int32_t, P22_TexVarB, 0x00a421e8)
#define P22_VpX        GAME_VAR(int32_t, P22_VpX, 0x00a421ac)
#define P22_VpY        GAME_VAR(int32_t, P22_VpY, 0x00a421b0)
#define P22_VpW        GAME_VAR(int32_t, P22_VpW, 0x00a421b4)
#define P22_VpH        GAME_VAR(int32_t, P22_VpH, 0x00a421b8)
#ifndef RE_HOOK_BUILD
#pragma push_macro("P22_DevReady") /*gvi*/
#undef P22_DevReady /*gvi*/
#pragma push_macro("P22_AlphaRef") /*gvi*/
#undef P22_AlphaRef /*gvi*/
#pragma push_macro("P22_ZFuncCur") /*gvi*/
#undef P22_ZFuncCur /*gvi*/
#pragma push_macro("P22_AlphaFunc") /*gvi*/
#undef P22_AlphaFunc /*gvi*/
#pragma push_macro("P22_ZWriteOff") /*gvi*/
#undef P22_ZWriteOff /*gvi*/
#pragma push_macro("P22_AtestA") /*gvi*/
#undef P22_AtestA /*gvi*/
#pragma push_macro("P22_AtestB") /*gvi*/
#undef P22_AtestB /*gvi*/
#pragma push_macro("P22_TexOpCur") /*gvi*/
#undef P22_TexOpCur /*gvi*/
#pragma push_macro("P22_TexVarA") /*gvi*/
#undef P22_TexVarA /*gvi*/
#pragma push_macro("P22_TexVarB") /*gvi*/
#undef P22_TexVarB /*gvi*/
#pragma push_macro("P22_VpX") /*gvi*/
#undef P22_VpX /*gvi*/
#pragma push_macro("P22_VpY") /*gvi*/
#undef P22_VpY /*gvi*/
#pragma push_macro("P22_VpW") /*gvi*/
#undef P22_VpW /*gvi*/
#pragma push_macro("P22_VpH") /*gvi*/
#undef P22_VpH /*gvi*/
extern int32_t P22_DevReady, P22_AlphaRef, P22_ZFuncCur, P22_AlphaFunc, P22_ZWriteOff, P22_AtestA, P22_AtestB, P22_TexOpCur, P22_TexVarA, P22_TexVarB, P22_VpX, P22_VpY, P22_VpW, P22_VpH;
#pragma pop_macro("P22_VpH") /*gvi*/
#pragma pop_macro("P22_VpW") /*gvi*/
#pragma pop_macro("P22_VpY") /*gvi*/
#pragma pop_macro("P22_VpX") /*gvi*/
#pragma pop_macro("P22_TexVarB") /*gvi*/
#pragma pop_macro("P22_TexVarA") /*gvi*/
#pragma pop_macro("P22_TexOpCur") /*gvi*/
#pragma pop_macro("P22_AtestB") /*gvi*/
#pragma pop_macro("P22_AtestA") /*gvi*/
#pragma pop_macro("P22_ZWriteOff") /*gvi*/
#pragma pop_macro("P22_AlphaFunc") /*gvi*/
#pragma pop_macro("P22_ZFuncCur") /*gvi*/
#pragma pop_macro("P22_AlphaRef") /*gvi*/
#pragma pop_macro("P22_DevReady") /*gvi*/
#endif
void P22_BeginScene(void);                 /* 0041e037 */
void P22_EndScene(void);                   /* 0041e056 */
void P22_SetAlphaRef(uint32_t v);          /* 0041de1d: ALPHAREF = v & 0xff */
void P22_SetZFunc(int32_t mode);           /* 0041e28a: 0..7 -> D3DCMP 1..8 */
void P22_SetAlphaFunc(int32_t mode);       /* 0041ddc5 */
void P22_SetZWrite(int32_t mode);          /* 0041e404 */
void P22_SetCull(int32_t mode);            /* 0041e215 */
void P22_SetAlphaTest(int32_t a, int32_t b, int32_t mode, int32_t flag); /* 0041dd37 */
void P22_SetTexFilter(int32_t a, int32_t min_linear, int32_t mag_linear); /* 0041f6a9 */
void P22_SetViewport(int32_t x0, int32_t y0, int32_t x1, int32_t y1);    /* 0041e08a */
void P22_SetTexOp(int32_t a, int32_t b, int32_t c, int32_t mode, int32_t e); /* 0041e14f: grColorCombine, режим — other (4-й) */
/* gvar-img v2.03 begin (tools/gen_gvar_img.py) */
#if !defined(RE_HOOK_BUILD) && !defined(RE_GVAR_PLAIN)
#undef P22_DevReady
#define P22_DevReady (*(int32_t *)re_gvar(0x00a421c0u, sizeof(int32_t), (void *)&P22_DevReady))
#undef P22_AlphaRef
#define P22_AlphaRef (*(int32_t *)re_gvar(0x0054ef54u, sizeof(int32_t), (void *)&P22_AlphaRef))
#undef P22_ZFuncCur
#define P22_ZFuncCur (*(int32_t *)re_gvar(0x0054ef58u, sizeof(int32_t), (void *)&P22_ZFuncCur))
#undef P22_AlphaFunc
#define P22_AlphaFunc (*(int32_t *)re_gvar(0x0054ef34u, sizeof(int32_t), (void *)&P22_AlphaFunc))
#undef P22_ZWriteOff
#define P22_ZWriteOff (*(int32_t *)re_gvar(0x00a421d4u, sizeof(int32_t), (void *)&P22_ZWriteOff))
#undef P22_AtestA
#define P22_AtestA (*(int32_t *)re_gvar(0x0054ef4cu, sizeof(int32_t), (void *)&P22_AtestA))
#undef P22_AtestB
#define P22_AtestB (*(int32_t *)re_gvar(0x0054ef50u, sizeof(int32_t), (void *)&P22_AtestB))
#undef P22_TexOpCur
#define P22_TexOpCur (*(int32_t *)re_gvar(0x0054ef40u, sizeof(int32_t), (void *)&P22_TexOpCur))
#undef P22_TexVarA
#define P22_TexVarA (*(int32_t *)re_gvar(0x00a421e4u, sizeof(int32_t), (void *)&P22_TexVarA))
#undef P22_TexVarB
#define P22_TexVarB (*(int32_t *)re_gvar(0x00a421e8u, sizeof(int32_t), (void *)&P22_TexVarB))
#undef P22_VpX
#define P22_VpX (*(int32_t *)re_gvar(0x00a421acu, sizeof(int32_t), (void *)&P22_VpX))
#undef P22_VpY
#define P22_VpY (*(int32_t *)re_gvar(0x00a421b0u, sizeof(int32_t), (void *)&P22_VpY))
#undef P22_VpW
#define P22_VpW (*(int32_t *)re_gvar(0x00a421b4u, sizeof(int32_t), (void *)&P22_VpW))
#undef P22_VpH
#define P22_VpH (*(int32_t *)re_gvar(0x00a421b8u, sizeof(int32_t), (void *)&P22_VpH))
#endif
/* gvar-img v2.03 end */
