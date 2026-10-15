#pragma once
#include "gvar.h"
#include "../platform/plat.h"
#include <stdint.h>
/* Переключатель режимов режиссёра повторов (Director.c). __cdecl. */
#define P29_Mode      GAME_VAR(int32_t, P29_Mode,      0x00d17bbc)  /* текущий режим 0..15 */
#define P29_Param     GAME_VAR(int32_t, P29_Param,     0x00d17bc0)
#define P29_Flag48    GAME_VAR(int32_t, P29_Flag48,    0x00d17d48)
#define P29_FlagA4    GAME_VAR(int32_t, P29_FlagA4,    0x00d17ba4)
#define P29_Flag74    GAME_VAR(int32_t, P29_Flag74,    0x00d17b74)
#define P29_Flag9C    GAME_VAR(int32_t, P29_Flag9C,    0x00d17b9c)
#define P29_FlagA8    GAME_VAR(int32_t, P29_FlagA8,    0x00d17ba8)
#define P29_FlagB0    GAME_VAR(int32_t, P29_FlagB0,    0x00d17bb0)
#define P29_Flag98    GAME_VAR(int32_t, P29_Flag98,    0x00d17b98)
#define P29_Flag94    GAME_VAR(int32_t, P29_Flag94,    0x00d17b94)
#ifndef RE_HOOK_BUILD
extern int32_t P29_Mode, P29_Param, P29_Flag48, P29_FlagA4, P29_Flag74, P29_Flag9C, P29_FlagA8, P29_FlagB0, P29_Flag98, P29_Flag94;
#endif
int32_t SetDirectorMode(int32_t mode, int32_t sub, int32_t param); /* 004c875d: переключить режим, вернуть прежний; mode>15 — запись в лог */
