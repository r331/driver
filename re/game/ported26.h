#pragma once
#include "gvar.h"
#include "../platform/plat.h"
#include <stdint.h>
/* Мелкие функции с WinAPI-вызовами (MessageBoxA, GetSystemTime, waveOutSetVolume, timeGetTime) — над plat_*. Все __cdecl. */
#define P26_FxA   GAME_VAR(int32_t, P26_FxA, 0x00b202e0)
#define P26_FxB   GAME_VAR(int32_t, P26_FxB, 0x00b202d4)
#define P26_FxC   GAME_VAR(int32_t, P26_FxC, 0x00b202e4)
#define P26_FxD   GAME_VAR(uint8_t, P26_FxD, 0x00b20300)
#define P26_ModelHubcap GAME_VAR(int32_t, P26_ModelHubcap, 0x00d11820)
#define P26_ModelClean  GAME_VAR(int32_t, P26_ModelClean, 0x00d117f4)
#define P26_ModelFast   GAME_VAR(int32_t, P26_ModelFast, 0x00d117e0)
#define P26_ModelDam    GAME_VAR(int32_t, P26_ModelDam, 0x00d117a0)
#ifndef RE_HOOK_BUILD
#pragma push_macro("P26_FxA") /*gvi*/
#undef P26_FxA /*gvi*/
#pragma push_macro("P26_FxB") /*gvi*/
#undef P26_FxB /*gvi*/
#pragma push_macro("P26_FxC") /*gvi*/
#undef P26_FxC /*gvi*/
#pragma push_macro("P26_ModelHubcap") /*gvi*/
#undef P26_ModelHubcap /*gvi*/
#pragma push_macro("P26_ModelClean") /*gvi*/
#undef P26_ModelClean /*gvi*/
#pragma push_macro("P26_ModelFast") /*gvi*/
#undef P26_ModelFast /*gvi*/
#pragma push_macro("P26_ModelDam") /*gvi*/
#undef P26_ModelDam /*gvi*/
extern int32_t P26_FxA, P26_FxB, P26_FxC, P26_ModelHubcap, P26_ModelClean, P26_ModelFast, P26_ModelDam;
#pragma pop_macro("P26_ModelDam") /*gvi*/
#pragma pop_macro("P26_ModelFast") /*gvi*/
#pragma pop_macro("P26_ModelClean") /*gvi*/
#pragma pop_macro("P26_ModelHubcap") /*gvi*/
#pragma pop_macro("P26_FxC") /*gvi*/
#pragma pop_macro("P26_FxB") /*gvi*/
#pragma pop_macro("P26_FxA") /*gvi*/
#pragma push_macro("P26_FxD") /*gvi*/
#undef P26_FxD /*gvi*/
extern uint8_t P26_FxD;
#pragma pop_macro("P26_FxD") /*gvi*/
#endif
void P26_WaveSetVolume(uint32_t vol);       /* 0048bd65 */
void P26_ErrorInLine(const char *msg);      /* 004a5ac3 */
void P26_LogTime(const char *label);        /* 004bf35d: «label (h:mm.ss)» UTC в лог */
void P26_FindWheelModels(void);             /* 004d7b73 */
void P26_RandomFx(int32_t set);             /* 004fc5e1: выбор эффектов по биту timeGetTime */
int32_t P26_FindCdDrive(const char *file, char *out); /* 004d322c: корень привода с файлом file → out, 1/0 */
/* gvar-img v2.03 begin (tools/gen_gvar_img.py) */
#if !defined(RE_HOOK_BUILD) && !defined(RE_GVAR_PLAIN)
#undef P26_FxA
#define P26_FxA (*(int32_t *)re_gvar(0x00b202e0u, sizeof(int32_t), (void *)&P26_FxA))
#undef P26_FxB
#define P26_FxB (*(int32_t *)re_gvar(0x00b202d4u, sizeof(int32_t), (void *)&P26_FxB))
#undef P26_FxC
#define P26_FxC (*(int32_t *)re_gvar(0x00b202e4u, sizeof(int32_t), (void *)&P26_FxC))
#undef P26_FxD
#define P26_FxD (*(uint8_t *)re_gvar(0x00b20300u, sizeof(uint8_t), (void *)&P26_FxD))
#undef P26_ModelHubcap
#define P26_ModelHubcap (*(int32_t *)re_gvar(0x00d11820u, sizeof(int32_t), (void *)&P26_ModelHubcap))
#undef P26_ModelClean
#define P26_ModelClean (*(int32_t *)re_gvar(0x00d117f4u, sizeof(int32_t), (void *)&P26_ModelClean))
#undef P26_ModelFast
#define P26_ModelFast (*(int32_t *)re_gvar(0x00d117e0u, sizeof(int32_t), (void *)&P26_ModelFast))
#undef P26_ModelDam
#define P26_ModelDam (*(int32_t *)re_gvar(0x00d117a0u, sizeof(int32_t), (void *)&P26_ModelDam))
#endif
/* gvar-img v2.03 end */
