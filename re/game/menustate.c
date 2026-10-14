#include "menustate.h"
GAME_VAR_DEF(int32_t, MenuFlag5F7E4C, 0x005f7e4c)
GAME_VAR_DEF(int32_t, MenuState575EF0, 0x00575ef0)
void MenuFlagSet(void) { MenuFlag5F7E4C = 1; }
void MenuFlagUpdate(int mode) { if (mode == 0 || mode == 2) MenuFlag5F7E4C = 0; }
int MenuStateSetFour(void) { MenuState575EF0 = 4; return 0; }
