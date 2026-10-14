#include "ported9.h"
#include <string.h>
GAME_VAR_DEF(int32_t, P9_01134530, 0x01134530)
GAME_VAR_DEF(int32_t, P9_0113452c, 0x0113452c)
GAME_VAR_DEF(int32_t, P9_011342e8, 0x011342e8)
GAME_VAR_DEF(int32_t, P9_005fe9f0, 0x005fe9f0)
GAME_VAR_DEF(int32_t, P9_00c55a48, 0x00c55a48)
GAME_VAR_DEF(int32_t, P9_00c55a4c, 0x00c55a4c)
GAME_VAR_DEF(int32_t, P9_00c55a50, 0x00c55a50)
GAME_VAR_DEF(int32_t, P9_00c55a54, 0x00c55a54)
GAME_VAR_DEF(int32_t, P9_0054e258, 0x0054e258)
GAME_VAR_DEF(int32_t, P9_00b31e20, 0x00b31e20)
GAME_VAR_DEF(int32_t, P9_00b31dfc, 0x00b31dfc)
GAME_VAR_DEF(g8_bytes_t, P9_00b31db8, 0x00b31db8)
GAME_VAR_DEF(g8_bytes_t, P9_00b31d30, 0x00b31d30)
void SelectByDifficulty_00416D17(void) {
  if (P9_005fe9f0 == 1) P9_0054e258 = P9_00c55a4c;
  else if (P9_005fe9f0 == 2) P9_0054e258 = P9_00c55a50;
  else if (P9_005fe9f0 == 3) P9_0054e258 = P9_00c55a54;
  else P9_0054e258 = P9_00c55a48; }
void ResetSlots_004A2B70(void) {
  P9_01134530 = 0; P9_0113452c = 0; P9_011342e8 = 0; D_01134ea0 = 0;
  memset(&A_01134540[0], 0, 0x960);
  for (int32_t i = 0; i < 100; i++) { D_01134ec0[i] = i; memcpy(&A_01134540[i*24], &i, 4); }
  D_01134528 = 0; }
uint32_t IsButtonActive_004E3924(uint8_t i) {
  if (i == 0x20) { if (P9_00b31e20 < -0xe && -0xf < P9_00b31dfc) return 1; }
  else if (i == 0x21) { if (0xe < P9_00b31e20 && P9_00b31dfc < 0xf) return 1; }
  else if (i != 0x22 && P9_00b31db8[i] != 0 && P9_00b31d30[i] == 0) return 1;
  return 0; }
