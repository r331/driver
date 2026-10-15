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
extern int32_t P26_FxA, P26_FxB, P26_FxC, P26_ModelHubcap, P26_ModelClean, P26_ModelFast, P26_ModelDam;
extern uint8_t P26_FxD;
#endif
void P26_WaveSetVolume(uint32_t vol);       /* 0048bd65 */
void P26_ErrorInLine(const char *msg);      /* 004a5ac3 */
void P26_LogTime(const char *label);        /* 004bf35d: «label (h:mm.ss)» UTC в лог */
void P26_FindWheelModels(void);             /* 004d7b73 */
void P26_RandomFx(int32_t set);             /* 004fc5e1: выбор эффектов по биту timeGetTime */
int32_t P26_FindCdDrive(const char *file, char *out); /* 004d322c: корень привода с файлом file → out, 1/0 */
