#pragma once
#include "gvar.h"
#include "ported19.h"
#include "ported53.h"
#include <stdint.h>
/* Шаг D, ported81 (веха 1): освещение уровня, cdecl.
   004cb619  P81_Light — раскладка направления света (005507d0..d8) на шесть положительных компонент:
             для каждой оси >=0 -> «плюс», иначе «минус»; значение |x|+фон(01251a68), не больше 1.0,
             противоположная компонента = фон. 0052e080 в оригинале — CRT fabs. */
#define P81_PosX  GAME_VAR(float, P81_PosX, 0x011f0050)
#define P81_NegX  GAME_VAR(float, P81_NegX, 0x01209648)
#define P81_PosY  GAME_VAR(float, P81_PosY, 0x011b6144)
#define P81_NegY  GAME_VAR(float, P81_NegY, 0x01209664)
#define P81_PosZ  GAME_VAR(float, P81_PosZ, 0x01209640)
#define P81_NegZ  GAME_VAR(float, P81_NegZ, 0x01209610)
#include "ported53.h"   /* P81_Span = P53_Mrk[5] (00d026b4) */
#define P81_Flag   GAME_VAR(int32_t, P81_Flag, 0x00d02708)
#ifndef RE_HOOK_BUILD
#pragma push_macro("P81_Flag") /*gvi*/
#undef P81_Flag /*gvi*/
extern int32_t P81_Flag;
#pragma pop_macro("P81_Flag") /*gvi*/
#pragma push_macro("P81_PosX") /*gvi*/
#undef P81_PosX /*gvi*/
#pragma push_macro("P81_NegX") /*gvi*/
#undef P81_NegX /*gvi*/
#pragma push_macro("P81_PosY") /*gvi*/
#undef P81_PosY /*gvi*/
#pragma push_macro("P81_NegY") /*gvi*/
#undef P81_NegY /*gvi*/
#pragma push_macro("P81_PosZ") /*gvi*/
#undef P81_PosZ /*gvi*/
#pragma push_macro("P81_NegZ") /*gvi*/
#undef P81_NegZ /*gvi*/
extern float P81_PosX, P81_NegX, P81_PosY, P81_NegY, P81_PosZ, P81_NegZ;
#pragma pop_macro("P81_NegZ") /*gvi*/
#pragma pop_macro("P81_PosZ") /*gvi*/
#pragma pop_macro("P81_NegY") /*gvi*/
#pragma pop_macro("P81_PosY") /*gvi*/
#pragma pop_macro("P81_NegX") /*gvi*/
#pragma pop_macro("P81_PosX") /*gvi*/
#endif
void P81_Light(void);   /* 004cb619 */
/* 004e959a  P81_Limit(int v): d = v - P53_Var26A4(float); если d < 0 и (|d| > 100 или P81_Span <= 0) — флаг 00d02708 = 0x40000000.
   Два вызова fabs/деления в начале оригинала результат не используют. cdecl. */
void P81_Limit(int32_t v);   /* 004e959a */
/* gvar-img v2.03 begin (tools/gen_gvar_img.py) */
#if !defined(RE_HOOK_BUILD) && !defined(RE_GVAR_PLAIN)
#undef P81_PosX
#define P81_PosX (*(float *)re_gvar(0x011f0050u, sizeof(float), (void *)&P81_PosX))
#undef P81_NegX
#define P81_NegX (*(float *)re_gvar(0x01209648u, sizeof(float), (void *)&P81_NegX))
#undef P81_PosY
#define P81_PosY (*(float *)re_gvar(0x011b6144u, sizeof(float), (void *)&P81_PosY))
#undef P81_NegY
#define P81_NegY (*(float *)re_gvar(0x01209664u, sizeof(float), (void *)&P81_NegY))
#undef P81_PosZ
#define P81_PosZ (*(float *)re_gvar(0x01209640u, sizeof(float), (void *)&P81_PosZ))
#undef P81_NegZ
#define P81_NegZ (*(float *)re_gvar(0x01209610u, sizeof(float), (void *)&P81_NegZ))
#undef P81_Flag
#define P81_Flag (*(int32_t *)re_gvar(0x00d02708u, sizeof(int32_t), (void *)&P81_Flag))
#endif
/* gvar-img v2.03 end */
