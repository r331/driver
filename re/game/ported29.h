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
#pragma push_macro("P29_Mode") /*gvi*/
#undef P29_Mode /*gvi*/
#pragma push_macro("P29_Param") /*gvi*/
#undef P29_Param /*gvi*/
#pragma push_macro("P29_Flag48") /*gvi*/
#undef P29_Flag48 /*gvi*/
#pragma push_macro("P29_FlagA4") /*gvi*/
#undef P29_FlagA4 /*gvi*/
#pragma push_macro("P29_Flag74") /*gvi*/
#undef P29_Flag74 /*gvi*/
#pragma push_macro("P29_Flag9C") /*gvi*/
#undef P29_Flag9C /*gvi*/
#pragma push_macro("P29_FlagA8") /*gvi*/
#undef P29_FlagA8 /*gvi*/
#pragma push_macro("P29_FlagB0") /*gvi*/
#undef P29_FlagB0 /*gvi*/
#pragma push_macro("P29_Flag98") /*gvi*/
#undef P29_Flag98 /*gvi*/
#pragma push_macro("P29_Flag94") /*gvi*/
#undef P29_Flag94 /*gvi*/
extern int32_t P29_Mode, P29_Param, P29_Flag48, P29_FlagA4, P29_Flag74, P29_Flag9C, P29_FlagA8, P29_FlagB0, P29_Flag98, P29_Flag94;
#pragma pop_macro("P29_Flag94") /*gvi*/
#pragma pop_macro("P29_Flag98") /*gvi*/
#pragma pop_macro("P29_FlagB0") /*gvi*/
#pragma pop_macro("P29_FlagA8") /*gvi*/
#pragma pop_macro("P29_Flag9C") /*gvi*/
#pragma pop_macro("P29_Flag74") /*gvi*/
#pragma pop_macro("P29_FlagA4") /*gvi*/
#pragma pop_macro("P29_Flag48") /*gvi*/
#pragma pop_macro("P29_Param") /*gvi*/
#pragma pop_macro("P29_Mode") /*gvi*/
#endif
int32_t SetDirectorMode(int32_t mode, int32_t sub, int32_t param); /* 004c875d: переключить режим, вернуть прежний; mode>15 — запись в лог */
/* gvar-img v2.03 begin (tools/gen_gvar_img.py) */
#if !defined(RE_HOOK_BUILD) && !defined(RE_GVAR_PLAIN)
#undef P29_Mode
#define P29_Mode (*(int32_t *)re_gvar(0x00d17bbcu, sizeof(int32_t), (void *)&P29_Mode))
#undef P29_Param
#define P29_Param (*(int32_t *)re_gvar(0x00d17bc0u, sizeof(int32_t), (void *)&P29_Param))
#undef P29_Flag48
#define P29_Flag48 (*(int32_t *)re_gvar(0x00d17d48u, sizeof(int32_t), (void *)&P29_Flag48))
#undef P29_FlagA4
#define P29_FlagA4 (*(int32_t *)re_gvar(0x00d17ba4u, sizeof(int32_t), (void *)&P29_FlagA4))
#undef P29_Flag74
#define P29_Flag74 (*(int32_t *)re_gvar(0x00d17b74u, sizeof(int32_t), (void *)&P29_Flag74))
#undef P29_Flag9C
#define P29_Flag9C (*(int32_t *)re_gvar(0x00d17b9cu, sizeof(int32_t), (void *)&P29_Flag9C))
#undef P29_FlagA8
#define P29_FlagA8 (*(int32_t *)re_gvar(0x00d17ba8u, sizeof(int32_t), (void *)&P29_FlagA8))
#undef P29_FlagB0
#define P29_FlagB0 (*(int32_t *)re_gvar(0x00d17bb0u, sizeof(int32_t), (void *)&P29_FlagB0))
#undef P29_Flag98
#define P29_Flag98 (*(int32_t *)re_gvar(0x00d17b98u, sizeof(int32_t), (void *)&P29_Flag98))
#undef P29_Flag94
#define P29_Flag94 (*(int32_t *)re_gvar(0x00d17b94u, sizeof(int32_t), (void *)&P29_Flag94))
#endif
/* gvar-img v2.03 end */
