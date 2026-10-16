#pragma once
#include "gvar.h"
#include <stdint.h>
#define P18_Flag0057A0E6 GAME_VAR(uint16_t, P18_Flag0057A0E6, 0x0057a0e6)
#ifndef RE_HOOK_BUILD
#pragma push_macro("P18_Flag0057A0E6") /*gvi*/
#undef P18_Flag0057A0E6 /*gvi*/
extern uint16_t P18_Flag0057A0E6;
#pragma pop_macro("P18_Flag0057A0E6") /*gvi*/
#endif
void P18_ClearFlag(void); /* 0052840c: обнуляет 16-бит слово */
/* gvar-img v2.03 begin (tools/gen_gvar_img.py) */
#if !defined(RE_HOOK_BUILD) && !defined(RE_GVAR_PLAIN)
#undef P18_Flag0057A0E6
#define P18_Flag0057A0E6 (*(uint16_t *)re_gvar(0x0057a0e6u, sizeof(uint16_t), (void *)&P18_Flag0057A0E6))
#endif
/* gvar-img v2.03 end */
