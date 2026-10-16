/* Таблица адресов строк языка 00c55820 (стандарт v1.42): одна uint32-таблица на 0x15e строк, заполняет 0051763a (P98_LoadLang).
   Прежние псевдонимы P12_00c55820 / G00C55820 / P65_Str — через неё; строка — re_ptr(P97_StrAddr[i]). */
#pragma once
#include "gvar.h"
#include <stdint.h>
typedef uint32_t p97_strtab_t[0x15e];
#define P97_StrAddr   GAME_VAR(p97_strtab_t, P97_StrAddr, 0x00c55820)
#ifndef RE_HOOK_BUILD
#pragma push_macro("P97_StrAddr") /*gvi*/
#undef P97_StrAddr /*gvi*/
extern p97_strtab_t P97_StrAddr;
#pragma pop_macro("P97_StrAddr") /*gvi*/
#endif
/* gvar-img v2.03 begin (tools/gen_gvar_img.py) */
#if !defined(RE_HOOK_BUILD) && !defined(RE_GVAR_PLAIN)
#undef P97_StrAddr
#define P97_StrAddr (*(p97_strtab_t *)re_gvar(0x00c55820u, sizeof(p97_strtab_t), (void *)&P97_StrAddr))
#endif
/* gvar-img v2.03 end */
