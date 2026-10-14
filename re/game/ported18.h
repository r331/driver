#pragma once
#include "gvar.h"
#include <stdint.h>
#define P18_Flag0057A0E6 GAME_VAR(uint16_t, P18_Flag0057A0E6, 0x0057a0e6)
#ifndef RE_HOOK_BUILD
extern uint16_t P18_Flag0057A0E6;
#endif
void P18_ClearFlag(void); /* 0052840c: обнуляет 16-бит слово */
