/* v1.56, ported111 — функции, разблокированные рефакторингом v1.56:
   004abd69 — загрузка значков эффектов (DEBRIS, SPARK, SMOKE, …, COPFLARE; поля +9..+0xc правятся на 1 — края текстуры),
   004b05ea — обломок/лист значком из таблицы значков 01105d68 (icontab.h) по байту +0x3a, режим 1 — тень на дороге,
   004b6deb — вспышка значком 0111a3e0 с цветом из .data 00553870 (game/p111_data.h, tools/gen_p111_data.py),
   004cf2cf — такт текущей записи скрипта: опкоды по таблице .data 0055fcac — в native адреса и re_fn (k_fns в game/reptr.c). */
#pragma once
#include <stdint.h>
#include "gvar.h"
#define P111_SparkIcon GAME_VAR(uint32_t, P111_SparkIcon, 0x010ffbe0)   /* SPARK */
#define P111_LeafIcon  GAME_VAR(uint32_t, P111_LeafIcon, 0x0110e140)    /* YLEAF (обломок с +0x3a == 1) */
#define P111_Ic0110B020 GAME_VAR(uint32_t, P111_Ic0110B020, 0x0110b020) /* = CARLYT */
#define P111_Ic0111D400 GAME_VAR(uint32_t, P111_Ic0111D400, 0x0111d400) /* = LIGHT */
#define P111_CopFlare  GAME_VAR(uint32_t, P111_CopFlare, 0x0111a3e4)    /* COPFLARE */
#ifndef RE_HOOK_BUILD
#pragma push_macro("P111_SparkIcon") /*gvi*/
#undef P111_SparkIcon /*gvi*/
#pragma push_macro("P111_LeafIcon") /*gvi*/
#undef P111_LeafIcon /*gvi*/
#pragma push_macro("P111_Ic0110B020") /*gvi*/
#undef P111_Ic0110B020 /*gvi*/
#pragma push_macro("P111_Ic0111D400") /*gvi*/
#undef P111_Ic0111D400 /*gvi*/
#pragma push_macro("P111_CopFlare") /*gvi*/
#undef P111_CopFlare /*gvi*/
extern uint32_t P111_SparkIcon, P111_LeafIcon, P111_Ic0110B020, P111_Ic0111D400, P111_CopFlare;
#pragma pop_macro("P111_CopFlare") /*gvi*/
#pragma pop_macro("P111_Ic0111D400") /*gvi*/
#pragma pop_macro("P111_Ic0110B020") /*gvi*/
#pragma pop_macro("P111_LeafIcon") /*gvi*/
#pragma pop_macro("P111_SparkIcon") /*gvi*/
#endif
void    P111_IconsInit(void);                          /* 004abd69 */
void    P111_DebrisIcon(const float *o, int32_t shadow); /* 004b05ea */
void    P111_Flare(const float *p);                    /* 004b6deb */
void    P111_ScriptTick(void);                         /* 004cf2cf */
#define P111_OPS_N 33
extern const uint32_t P111_OpAddr[P111_OPS_N];         /* .data 0055fcac → цели переходов (адреса функций) */
/* gvar-img v2.03 begin (tools/gen_gvar_img.py) */
#if !defined(RE_HOOK_BUILD) && !defined(RE_GVAR_PLAIN)
#undef P111_SparkIcon
#define P111_SparkIcon (*(uint32_t *)re_gvar(0x010ffbe0u, sizeof(uint32_t), (void *)&P111_SparkIcon))
#undef P111_LeafIcon
#define P111_LeafIcon (*(uint32_t *)re_gvar(0x0110e140u, sizeof(uint32_t), (void *)&P111_LeafIcon))
#undef P111_Ic0110B020
#define P111_Ic0110B020 (*(uint32_t *)re_gvar(0x0110b020u, sizeof(uint32_t), (void *)&P111_Ic0110B020))
#undef P111_Ic0111D400
#define P111_Ic0111D400 (*(uint32_t *)re_gvar(0x0111d400u, sizeof(uint32_t), (void *)&P111_Ic0111D400))
#undef P111_CopFlare
#define P111_CopFlare (*(uint32_t *)re_gvar(0x0111a3e4u, sizeof(uint32_t), (void *)&P111_CopFlare))
#endif
/* gvar-img v2.03 end */
