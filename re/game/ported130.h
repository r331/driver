#pragma once
#include <stdint.h>
#include "gvar.h"
/* v1.75: ported130 — погодные/световые эффекты скрипта над стеком записей G2_ScriptStack ([0] — число, записи по 0x34
   с +0x194: x, y, z, -, sx, sy, -, -, экр.x, экр.y, 1/w, -, [+0x30] этап, [+0x31] значок, [+0x32] номер).
   Все функции cdecl без аргументов (work/rets.py: ret без операнда). */
typedef uint8_t p130_rgb_t[3];
#define P130_LampRGB  GAME_VAR(p130_rgb_t, P130_LampRGB, 0x0055fc8c)   /* .data, начальное {0x00, 0x80, 0x80}: базовый цвет молнии */
#ifndef RE_HOOK_BUILD
extern p130_rgb_t P130_LampRGB;
#endif
void P130_SnowSpawn(void);   /* 004cd994 */
void P130_RainSpawn(void);   /* 004cc008 */
void P130_Lightning(void);   /* 004cadb5 */
void P130_RainStep(void);    /* 004cba1d */
void P130_SnowStep(void);    /* 004cdb25 */
