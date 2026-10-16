#pragma once
#include "gvar.h"
#include "ported8.h"
#include "ported4.h"
/* Партия v0.44 */
#define P9_01134530 GAME_VAR(int32_t, P9_01134530, 0x01134530)
#ifndef RE_HOOK_BUILD
#pragma push_macro("P9_01134530") /*gvi*/
#undef P9_01134530 /*gvi*/
extern int32_t P9_01134530;
#pragma pop_macro("P9_01134530") /*gvi*/
#endif
#define P9_0113452c GAME_VAR(int32_t, P9_0113452c, 0x0113452c)
#ifndef RE_HOOK_BUILD
#pragma push_macro("P9_0113452c") /*gvi*/
#undef P9_0113452c /*gvi*/
extern int32_t P9_0113452c;
#pragma pop_macro("P9_0113452c") /*gvi*/
#endif
#define P9_011342e8 GAME_VAR(int32_t, P9_011342e8, 0x011342e8)
#ifndef RE_HOOK_BUILD
#pragma push_macro("P9_011342e8") /*gvi*/
#undef P9_011342e8 /*gvi*/
extern int32_t P9_011342e8;
#pragma pop_macro("P9_011342e8") /*gvi*/
#endif
#define P9_005fe9f0 GAME_VAR(int32_t, P9_005fe9f0, 0x005fe9f0)
#ifndef RE_HOOK_BUILD
#pragma push_macro("P9_005fe9f0") /*gvi*/
#undef P9_005fe9f0 /*gvi*/
extern int32_t P9_005fe9f0;
#pragma pop_macro("P9_005fe9f0") /*gvi*/
#endif
#define P9_00c55a48 GAME_VAR(int32_t, P9_00c55a48, 0x00c55a48)
#ifndef RE_HOOK_BUILD
#pragma push_macro("P9_00c55a48") /*gvi*/
#undef P9_00c55a48 /*gvi*/
extern int32_t P9_00c55a48;
#pragma pop_macro("P9_00c55a48") /*gvi*/
#endif
#define P9_00c55a4c GAME_VAR(int32_t, P9_00c55a4c, 0x00c55a4c)
#ifndef RE_HOOK_BUILD
#pragma push_macro("P9_00c55a4c") /*gvi*/
#undef P9_00c55a4c /*gvi*/
extern int32_t P9_00c55a4c;
#pragma pop_macro("P9_00c55a4c") /*gvi*/
#endif
#define P9_00c55a50 GAME_VAR(int32_t, P9_00c55a50, 0x00c55a50)
#ifndef RE_HOOK_BUILD
#pragma push_macro("P9_00c55a50") /*gvi*/
#undef P9_00c55a50 /*gvi*/
extern int32_t P9_00c55a50;
#pragma pop_macro("P9_00c55a50") /*gvi*/
#endif
#define P9_00c55a54 GAME_VAR(int32_t, P9_00c55a54, 0x00c55a54)
#ifndef RE_HOOK_BUILD
#pragma push_macro("P9_00c55a54") /*gvi*/
#undef P9_00c55a54 /*gvi*/
extern int32_t P9_00c55a54;
#pragma pop_macro("P9_00c55a54") /*gvi*/
#endif
#define P9_0054e258 GAME_VAR(int32_t, P9_0054e258, 0x0054e258)
#ifndef RE_HOOK_BUILD
#pragma push_macro("P9_0054e258") /*gvi*/
#undef P9_0054e258 /*gvi*/
extern int32_t P9_0054e258;
#pragma pop_macro("P9_0054e258") /*gvi*/
#endif
#define P9_00b31e20 GAME_VAR(int32_t, P9_00b31e20, 0x00b31e20)
#ifndef RE_HOOK_BUILD
#pragma push_macro("P9_00b31e20") /*gvi*/
#undef P9_00b31e20 /*gvi*/
extern int32_t P9_00b31e20;
#pragma pop_macro("P9_00b31e20") /*gvi*/
#endif
#define P9_00b31dfc GAME_VAR(int32_t, P9_00b31dfc, 0x00b31dfc)
#ifndef RE_HOOK_BUILD
#pragma push_macro("P9_00b31dfc") /*gvi*/
#undef P9_00b31dfc /*gvi*/
extern int32_t P9_00b31dfc;
#pragma pop_macro("P9_00b31dfc") /*gvi*/
#endif
#define P9_00b31db8 GAME_VAR(g8_bytes_t, P9_00b31db8, 0x00b31db8)
#ifndef RE_HOOK_BUILD
#pragma push_macro("P9_00b31db8") /*gvi*/
#undef P9_00b31db8 /*gvi*/
extern g8_bytes_t P9_00b31db8;
#pragma pop_macro("P9_00b31db8") /*gvi*/
#endif
#define P9_00b31d30 GAME_VAR(g8_bytes_t, P9_00b31d30, 0x00b31d30)
#ifndef RE_HOOK_BUILD
#pragma push_macro("P9_00b31d30") /*gvi*/
#undef P9_00b31d30 /*gvi*/
extern g8_bytes_t P9_00b31d30;
#pragma pop_macro("P9_00b31d30") /*gvi*/
#endif
void SelectByDifficulty_00416D17(void);
void ResetSlots_004A2B70(void);
uint32_t IsButtonActive_004E3924(uint8_t i);
/* gvar-img v2.03 begin (tools/gen_gvar_img.py) */
#if !defined(RE_HOOK_BUILD) && !defined(RE_GVAR_PLAIN)
#undef P9_01134530
#define P9_01134530 (*(int32_t *)re_gvar(0x01134530u, sizeof(int32_t), (void *)&P9_01134530))
#undef P9_0113452c
#define P9_0113452c (*(int32_t *)re_gvar(0x0113452cu, sizeof(int32_t), (void *)&P9_0113452c))
#undef P9_011342e8
#define P9_011342e8 (*(int32_t *)re_gvar(0x011342e8u, sizeof(int32_t), (void *)&P9_011342e8))
#undef P9_005fe9f0
#define P9_005fe9f0 (*(int32_t *)re_gvar(0x005fe9f0u, sizeof(int32_t), (void *)&P9_005fe9f0))
#undef P9_00c55a48
#define P9_00c55a48 (*(int32_t *)re_gvar(0x00c55a48u, sizeof(int32_t), (void *)&P9_00c55a48))
#undef P9_00c55a4c
#define P9_00c55a4c (*(int32_t *)re_gvar(0x00c55a4cu, sizeof(int32_t), (void *)&P9_00c55a4c))
#undef P9_00c55a50
#define P9_00c55a50 (*(int32_t *)re_gvar(0x00c55a50u, sizeof(int32_t), (void *)&P9_00c55a50))
#undef P9_00c55a54
#define P9_00c55a54 (*(int32_t *)re_gvar(0x00c55a54u, sizeof(int32_t), (void *)&P9_00c55a54))
#undef P9_0054e258
#define P9_0054e258 (*(int32_t *)re_gvar(0x0054e258u, sizeof(int32_t), (void *)&P9_0054e258))
#undef P9_00b31e20
#define P9_00b31e20 (*(int32_t *)re_gvar(0x00b31e20u, sizeof(int32_t), (void *)&P9_00b31e20))
#undef P9_00b31dfc
#define P9_00b31dfc (*(int32_t *)re_gvar(0x00b31dfcu, sizeof(int32_t), (void *)&P9_00b31dfc))
#undef P9_00b31db8
#define P9_00b31db8 (*(g8_bytes_t *)re_gvar(0x00b31db8u, sizeof(g8_bytes_t), (void *)&P9_00b31db8))
#undef P9_00b31d30
#define P9_00b31d30 (*(g8_bytes_t *)re_gvar(0x00b31d30u, sizeof(g8_bytes_t), (void *)&P9_00b31d30))
#endif
/* gvar-img v2.03 end */
