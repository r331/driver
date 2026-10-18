#pragma once
#include "gvar.h"
#include "../platform/plat.h"
#include <stdint.h>
/* Рендер, шаг C: конвертация вершин игры -> TLVERTEX (plat_vertex), линии, режимы смешивания, начальные render-state, очистка Z.
   Вход вершины игры — 11 dword (44 байта): [0]x [1]y [3]R [4]G [5]B (float 0..255) [8]w [9]u [10]v. */
#ifndef RE_HOOK_BUILD
/* Sky vertices use the far depth while retaining their original rhw and UVs.
   Returns the previous setting so the sky pass can restore it. */
int P23_SetSkyDepth(int enabled);
#endif
#define P23_ScaleUV_A   GAME_VAR(float, P23_ScaleUV_A, 0x0054ef60)
#define P23_ScaleUV_B   GAME_VAR(float, P23_ScaleUV_B, 0x0054ef6c)
#define P23_ZScale_A    GAME_VAR(float, P23_ZScale_A, 0x0054ef64)
#define P23_ZScale_B    GAME_VAR(float, P23_ZScale_B, 0x0054ef68)
#define P23_ZNum        GAME_VAR(float, P23_ZNum, 0x0054ef3c)
#define P23_ZDenA       GAME_VAR(float, P23_ZDenA, 0x0054ef38)
#define P23_ZBias       GAME_VAR(float, P23_ZBias, 0x00a4217c)
#define P23_BlendCur    GAME_VAR(int32_t, P23_BlendCur, 0x0054ef44)
#define P23_BlendCur2   GAME_VAR(int32_t, P23_BlendCur2, 0x0054ef48)
#define P23_DevCaps     GAME_VAR(uint32_t, P23_DevCaps, 0x00a421dc)
#define P23_AlphaMode   GAME_VAR(int32_t, P23_AlphaMode, 0x00a421e0)
#ifndef RE_HOOK_BUILD
#pragma push_macro("P23_ScaleUV_A") /*gvi*/
#undef P23_ScaleUV_A /*gvi*/
#pragma push_macro("P23_ScaleUV_B") /*gvi*/
#undef P23_ScaleUV_B /*gvi*/
#pragma push_macro("P23_ZScale_A") /*gvi*/
#undef P23_ZScale_A /*gvi*/
#pragma push_macro("P23_ZScale_B") /*gvi*/
#undef P23_ZScale_B /*gvi*/
#pragma push_macro("P23_ZNum") /*gvi*/
#undef P23_ZNum /*gvi*/
#pragma push_macro("P23_ZDenA") /*gvi*/
#undef P23_ZDenA /*gvi*/
#pragma push_macro("P23_ZBias") /*gvi*/
#undef P23_ZBias /*gvi*/
extern float P23_ScaleUV_A, P23_ScaleUV_B, P23_ZScale_A, P23_ZScale_B, P23_ZNum, P23_ZDenA, P23_ZBias;
#pragma pop_macro("P23_ZBias") /*gvi*/
#pragma pop_macro("P23_ZDenA") /*gvi*/
#pragma pop_macro("P23_ZNum") /*gvi*/
#pragma pop_macro("P23_ZScale_B") /*gvi*/
#pragma pop_macro("P23_ZScale_A") /*gvi*/
#pragma pop_macro("P23_ScaleUV_B") /*gvi*/
#pragma pop_macro("P23_ScaleUV_A") /*gvi*/
#pragma push_macro("P23_BlendCur") /*gvi*/
#undef P23_BlendCur /*gvi*/
#pragma push_macro("P23_BlendCur2") /*gvi*/
#undef P23_BlendCur2 /*gvi*/
#pragma push_macro("P23_AlphaMode") /*gvi*/
#undef P23_AlphaMode /*gvi*/
extern int32_t P23_BlendCur, P23_BlendCur2, P23_AlphaMode;
#pragma pop_macro("P23_AlphaMode") /*gvi*/
#pragma pop_macro("P23_BlendCur2") /*gvi*/
#pragma pop_macro("P23_BlendCur") /*gvi*/
#pragma push_macro("P23_DevCaps") /*gvi*/
#undef P23_DevCaps /*gvi*/
extern uint32_t P23_DevCaps;
#pragma pop_macro("P23_DevCaps") /*gvi*/
#endif
void P23_ConvVertexA(const int32_t *in, plat_vertex *out);   /* 00421cfe */
void P23_ConvVertexB(const int32_t *in, plat_vertex *out);   /* 00421db8 */
void P23_DrawLineA(const int32_t *a, const int32_t *b);      /* 0041e462 */
void P23_DrawLineB(const int32_t *a, const int32_t *b);      /* 0041e4b9 */
void P23_SetBlendMode(int32_t mode, int32_t sub);            /* 0041d9d2 */
void P23_InitRenderStates(void);                             /* 00421521 */
int32_t P23_ClearZ(void *viewport, uint32_t zbits);          /* 00420e93 */
/* gvar-img v2.03 begin (tools/gen_gvar_img.py) */
#if !defined(RE_HOOK_BUILD) && !defined(RE_GVAR_PLAIN)
#undef P23_ScaleUV_A
#define P23_ScaleUV_A (*(float *)re_gvar(0x0054ef60u, sizeof(float), (void *)&P23_ScaleUV_A))
#undef P23_ScaleUV_B
#define P23_ScaleUV_B (*(float *)re_gvar(0x0054ef6cu, sizeof(float), (void *)&P23_ScaleUV_B))
#undef P23_ZScale_A
#define P23_ZScale_A (*(float *)re_gvar(0x0054ef64u, sizeof(float), (void *)&P23_ZScale_A))
#undef P23_ZScale_B
#define P23_ZScale_B (*(float *)re_gvar(0x0054ef68u, sizeof(float), (void *)&P23_ZScale_B))
#undef P23_ZNum
#define P23_ZNum (*(float *)re_gvar(0x0054ef3cu, sizeof(float), (void *)&P23_ZNum))
#undef P23_ZDenA
#define P23_ZDenA (*(float *)re_gvar(0x0054ef38u, sizeof(float), (void *)&P23_ZDenA))
#undef P23_ZBias
#define P23_ZBias (*(float *)re_gvar(0x00a4217cu, sizeof(float), (void *)&P23_ZBias))
#undef P23_BlendCur
#define P23_BlendCur (*(int32_t *)re_gvar(0x0054ef44u, sizeof(int32_t), (void *)&P23_BlendCur))
#undef P23_BlendCur2
#define P23_BlendCur2 (*(int32_t *)re_gvar(0x0054ef48u, sizeof(int32_t), (void *)&P23_BlendCur2))
#undef P23_DevCaps
#define P23_DevCaps (*(uint32_t *)re_gvar(0x00a421dcu, sizeof(uint32_t), (void *)&P23_DevCaps))
#undef P23_AlphaMode
#define P23_AlphaMode (*(int32_t *)re_gvar(0x00a421e0u, sizeof(int32_t), (void *)&P23_AlphaMode))
#endif
/* gvar-img v2.03 end */
