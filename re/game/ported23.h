#pragma once
#include "gvar.h"
#include "../platform/plat.h"
#include <stdint.h>
/* Рендер, шаг C: конвертация вершин игры -> TLVERTEX (plat_vertex), линии, режимы смешивания, начальные render-state, очистка Z.
   Вход вершины игры — 11 dword (44 байта): [0]x [1]y [3]R [4]G [5]B (float 0..255) [8]w [9]u [10]v. */
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
extern float P23_ScaleUV_A, P23_ScaleUV_B, P23_ZScale_A, P23_ZScale_B, P23_ZNum, P23_ZDenA, P23_ZBias;
extern int32_t P23_BlendCur, P23_BlendCur2, P23_AlphaMode;
extern uint32_t P23_DevCaps;
#endif
void P23_ConvVertexA(const int32_t *in, plat_vertex *out);   /* 00421cfe */
void P23_ConvVertexB(const int32_t *in, plat_vertex *out);   /* 00421db8 */
void P23_DrawLineA(const int32_t *a, const int32_t *b);      /* 0041e462 */
void P23_DrawLineB(const int32_t *a, const int32_t *b);      /* 0041e4b9 */
void P23_SetBlendMode(int32_t mode, int32_t sub);            /* 0041d9d2 */
void P23_InitRenderStates(void);                             /* 00421521 */
int32_t P23_ClearZ(void *viewport, uint32_t zbits);          /* 00420e93 */
