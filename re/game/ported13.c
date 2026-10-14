#include "ported13.h"
#include <string.h>
GAME_VAR_DEF(int32_t,P13_0055384c,0x0055384c)
GAME_VAR_DEF(int32_t,P13_00553850,0x00553850)
GAME_VAR_DEF(int32_t,P13_0055c974,0x0055c974)
GAME_VAR_DEF(int32_t,P13_005759a4,0x005759a4)
GAME_VAR_DEF(int32_t,P13_00575ebc,0x00575ebc)
GAME_VAR_DEF(int32_t,P13_00575ec0,0x00575ec0)
GAME_VAR_DEF(int32_t,P13_00575ee4,0x00575ee4)
GAME_VAR_DEF(int32_t,P13_00575ee8,0x00575ee8)
GAME_VAR_DEF(int32_t,P13_00575ef4,0x00575ef4)
GAME_VAR_DEF(int32_t,P13_00575f20,0x00575f20)
GAME_VAR_DEF(int32_t,P13_00575f30,0x00575f30)
GAME_VAR_DEF(int32_t,P13_00575f3c,0x00575f3c)
GAME_VAR_DEF(int32_t,P13_00575f44,0x00575f44)
GAME_VAR_DEF(int32_t,P13_00b201dc,0x00b201dc)
GAME_VAR_DEF(int32_t,P13_00b31f04,0x00b31f04)
GAME_VAR_DEF(int32_t,P13_00b87e74,0x00b87e74)
GAME_VAR_DEF(int32_t,P13_00d11880,0x00d11880)
GAME_VAR_DEF(int32_t,P13_00d118c8,0x00d118c8)
GAME_VAR_DEF(int32_t,P13_0125f3f8,0x0125f3f8)
GAME_VAR_DEF(int32_t,P13_01270c24,0x01270c24)
void P13_Fn004064B4(int32_t param_1, int32_t param_2)
{
  switch(param_1) {
  case 0:
    P13_00d11880 = 1;
    P13_00575f20 = 0;
    P13_0055384c = 0;
    P13_00553850 = 0;
    P13_00575f30 = 0;
    P13_00b201dc = 0;
    P13_00b31f04 = 0;
    P13_0055c974 = 0;
    P13_00575f44 = 0;
    P13_00575ebc = 0;
    P13_00575ec0 = 0;
    P13_00575ef4 = 0;
    P13_00b87e74 = 0;
    P13_00d118c8 = 1;
    P13_00575f3c = 0;
    P13_00575ee8 = 0;
    P13_0125f3f8 = 0x466a6000;
    P13_01270c24 = 0x466a6000;
    if (param_2 == 0) {
      P13_005759a4 = 8;
      P13_00575ee4 = 0x10;
    }
    break;
  case 1:
    P13_00d11880 = 1;
    P13_00575f20 = 1;
    P13_0055384c = 1;
    P13_00553850 = 1;
    P13_00575f30 = 0;
    P13_00b201dc = 0;
    P13_00b31f04 = 0;
    P13_0055c974 = 1;
    P13_00575f44 = 1;
    P13_00575ebc = 1;
    P13_00575ec0 = 1;
    P13_00575ef4 = 0;
    P13_00b87e74 = 0;
    P13_00d118c8 = 1;
    P13_00575f3c = 0;
    P13_00575ee8 = 0;
    P13_0125f3f8 = 0x466a6000;
    P13_01270c24 = 0x46ea6000;
    if (param_2 == 0) {
      P13_005759a4 = 0x10;
      P13_00575ee4 = 0x20;
    }
    break;
  case 2:
    P13_00d11880 = 1;
    P13_00575f20 = 1;
    P13_0055384c = 1;
    P13_00553850 = 1;
    P13_00575f30 = 1;
    P13_00b201dc = 1;
    P13_00b31f04 = 1;
    P13_0055c974 = 1;
    P13_00575f44 = 1;
    P13_00575ebc = 1;
    P13_00575ec0 = 1;
    P13_00575ef4 = 1;
    P13_00b87e74 = 0;
    P13_00d118c8 = 1;
    P13_00575f3c = 1;
    P13_00575ee8 = 1;
    P13_0125f3f8 = 0x46ea6000;
    P13_01270c24 = 0x472fc800;
    if (param_2 == 0) {
      P13_005759a4 = 0x20;
      P13_00575ee4 = 0x30;
    }
    break;
  case 3:
    P13_00d11880 = 1;
    P13_00575f20 = 1;
    P13_0055384c = 1;
    P13_00553850 = 1;
    P13_00575f30 = 1;
    P13_00b201dc = 1;
    P13_00b31f04 = 1;
    P13_0055c974 = 1;
    P13_00575f44 = 1;
    P13_00575ebc = 1;
    P13_00575ec0 = 1;
    P13_00575ef4 = 1;
    P13_00b87e74 = 1;
    P13_00d118c8 = 1;
    P13_00575f3c = 1;
    P13_00575ee8 = 1;
    P13_0125f3f8 = 0x47241000;
    P13_01270c24 = 0x472fc800;
    if (param_2 == 0) {
      P13_005759a4 = 0x40;
      P13_00575ee4 = 0x40;
    }
  }
  }

void P13_Fn00422AC0(void *dst, const void *src, uint32_t n) { memcpy(dst, src, n); }
const char *P13_Fn004F8735(int32_t code) {
  switch (code) {
  case 0: return "No errors found";
  case 2: return "Word value has been retrieved";
  case 3: return "Out of memory";
  case 4: return "End of file reached";
  case 5: return "Specified file was not found";
  case 6: return "Unexpected comma";
  case 7: return "Unexpected end of file";
  case 8: return "Unexpected end of line";
  case 9: return "Unrecognised command";
  case 10: return "End of line reached";
  case 11: return "Compilation completed successfully";
  case 12: return "Illegal parameter";
  default: return "Unknown error code";
  }
}
