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
extern int32_t P22_DevReady, P22_AlphaRef, P22_ZFuncCur, P22_AlphaFunc, P22_ZWriteOff, P22_AtestA, P22_AtestB, P22_TexOpCur, P22_TexVarA, P22_TexVarB, P22_VpX, P22_VpY, P22_VpW, P22_VpH;
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
void P22_SetTexOp(int32_t a, int32_t b, int32_t c, int32_t d, int32_t mode); /* 0041e14f */
