#pragma once
#include "gvar.h"
#include "ported8.h"
#include "ported4.h"
/* Партия v0.44 */
#define P9_01134530 GAME_VAR(int32_t, P9_01134530, 0x01134530)
#ifndef RE_HOOK_BUILD
extern int32_t P9_01134530;
#endif
#define P9_0113452c GAME_VAR(int32_t, P9_0113452c, 0x0113452c)
#ifndef RE_HOOK_BUILD
extern int32_t P9_0113452c;
#endif
#define P9_011342e8 GAME_VAR(int32_t, P9_011342e8, 0x011342e8)
#ifndef RE_HOOK_BUILD
extern int32_t P9_011342e8;
#endif
#define P9_005fe9f0 GAME_VAR(int32_t, P9_005fe9f0, 0x005fe9f0)
#ifndef RE_HOOK_BUILD
extern int32_t P9_005fe9f0;
#endif
#define P9_00c55a48 GAME_VAR(int32_t, P9_00c55a48, 0x00c55a48)
#ifndef RE_HOOK_BUILD
extern int32_t P9_00c55a48;
#endif
#define P9_00c55a4c GAME_VAR(int32_t, P9_00c55a4c, 0x00c55a4c)
#ifndef RE_HOOK_BUILD
extern int32_t P9_00c55a4c;
#endif
#define P9_00c55a50 GAME_VAR(int32_t, P9_00c55a50, 0x00c55a50)
#ifndef RE_HOOK_BUILD
extern int32_t P9_00c55a50;
#endif
#define P9_00c55a54 GAME_VAR(int32_t, P9_00c55a54, 0x00c55a54)
#ifndef RE_HOOK_BUILD
extern int32_t P9_00c55a54;
#endif
#define P9_0054e258 GAME_VAR(int32_t, P9_0054e258, 0x0054e258)
#ifndef RE_HOOK_BUILD
extern int32_t P9_0054e258;
#endif
#define P9_00b31e20 GAME_VAR(int32_t, P9_00b31e20, 0x00b31e20)
#ifndef RE_HOOK_BUILD
extern int32_t P9_00b31e20;
#endif
#define P9_00b31dfc GAME_VAR(int32_t, P9_00b31dfc, 0x00b31dfc)
#ifndef RE_HOOK_BUILD
extern int32_t P9_00b31dfc;
#endif
#define P9_00b31db8 GAME_VAR(g8_bytes_t, P9_00b31db8, 0x00b31db8)
#ifndef RE_HOOK_BUILD
extern g8_bytes_t P9_00b31db8;
#endif
#define P9_00b31d30 GAME_VAR(g8_bytes_t, P9_00b31d30, 0x00b31d30)
#ifndef RE_HOOK_BUILD
extern g8_bytes_t P9_00b31d30;
#endif
void SelectByDifficulty_00416D17(void);
void ResetSlots_004A2B70(void);
uint32_t IsButtonActive_004E3924(uint8_t i);
