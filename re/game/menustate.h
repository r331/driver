/* MenuState — мелкие переключатели состояния меню. */
#pragma once
#include "gvar.h"
#define MenuFlag5F7E4C GAME_VAR(int32_t, MenuFlag5F7E4C, 0x005f7e4c)
#define MenuState575EF0 GAME_VAR(int32_t, MenuState575EF0, 0x00575ef0)
#ifndef RE_HOOK_BUILD
extern int32_t MenuFlag5F7E4C, MenuState575EF0;
#endif
void MenuFlagSet(void);              /* 00404687 */
void MenuFlagUpdate(int mode);       /* 00404696: 0 и 2 сбрасывают флаг */
int MenuStateSetFour(void);          /* 00404f5f */
