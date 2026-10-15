/* SetDirectorMode — переключение режимов режиссёра повторов; восстановлено из Game.exe (004c875d). */
#include "ported29.h"
#include "ported6.h"
#include "director.h"
#include "dirnodes.h"
#include "directorstorage.h"
#include "engine.h"
#include "unported.h"
GAME_VAR_DEF(int32_t, P29_Mode, 0x00d17bbc)
GAME_VAR_DEF(int32_t, P29_Param, 0x00d17bc0)
GAME_VAR_DEF(int32_t, P29_Flag48, 0x00d17d48)
GAME_VAR_DEF(int32_t, P29_FlagA4, 0x00d17ba4)
GAME_VAR_DEF(int32_t, P29_Flag74, 0x00d17b74)
GAME_VAR_DEF(int32_t, P29_Flag9C, 0x00d17b9c)
GAME_VAR_DEF(int32_t, P29_FlagA8, 0x00d17ba8)
GAME_VAR_DEF(int32_t, P29_FlagB0, 0x00d17bb0)
GAME_VAR_DEF(int32_t, P29_Flag98, 0x00d17b98)
GAME_VAR_DEF(int32_t, P29_Flag94, 0x00d17b94)
/* До конца повтора ещё есть кадры (индекс текущего < последний-1). */
static int has_frames(void) { return DirectorUnk6C < DirectorLastFrame - 1; }
int32_t SetDirectorMode(int32_t mode, int32_t sub, int32_t param) {
  int32_t prev = P29_Mode;
  P29_Flag48 = 0; P29_FlagA4 = 0; P29_Flag74 = 0;
  P29_Param = param;
  G6_00B87EFC = 0;
  DirUseDI = 1;
  P29_Flag9C = 0;
  if (mode == 1) G6Call00524398();
  Call0052E180(plat_time_ms());           /* srand(timeGetTime()) */
  switch (mode) {
  case 0:
    FreeDirectorData();
    P29_FlagA8 = 0; P29_Mode = mode; DirNodeTable = NULL; P29_FlagB0 = 0; DirIndicatorOn = 0; P29_Flag98 = 0;
    if (sub != 1) { G6Call0050E940(0); G6_00B87EFC = 0; Call005243EB(); }
    break;
  case 1: case 0xc:
    G6Call0050E940(1);
    P29_Mode = mode; DirNodeTable = (DIR_NODE *)DirTableA; P29_FlagA8 = 1; P29_FlagB0 = 1; DirIndicatorOn = 0; P29_Flag98 = 0;
    DirectorUnk7C = (sub == -1) ? 1 : sub;
    G6_00B87EFC = 1;
    break;
  case 2:
    G6Call0050E940(1);
    P29_Mode = mode; DirNodeTable = NULL; P29_FlagA8 = 0; P29_FlagB0 = 1; DirIndicatorOn = 0; P29_Flag98 = 1;
    G6_00B87EFC = 1;
    break;
  case 3:
    if (has_frames()) {
      G6Call0050E940(0);
      P29_FlagA8 = 0; P29_Mode = mode; DirNodeTable = (DIR_NODE *)DirTableB; P29_FlagB0 = 1; DirIndicatorOn = 0;
      DirectorUnk7C = 0x1b; P29_Flag98 = 0;
      if (DirectorBuffer == NULL) LoadWaypoints();
      G6_00B87EFC = 0; Call005243EB();
    } else SetDirectorMode(1, 2, 0);
    break;
  case 4:
    if (has_frames()) {
      G6Call0050E940(0);
      P29_FlagA8 = 0; P29_Mode = mode; DirNodeTable = (DIR_NODE *)DirTableB; P29_FlagB0 = 1; DirIndicatorOn = 0;
      DirectorUnk7C = 0x1b; P29_Flag98 = 0;
      G6_00B87EFC = 0; Call005243EB();
    } else SetDirectorMode(1, 1, 0);
    break;
  case 5:
    if (has_frames()) {
      G6Call0050E940(0);
      P29_FlagA8 = 1; P29_Mode = mode; P29_FlagB0 = 1; DirIndicatorOn = 0; P29_Flag98 = 0;
    } else SetDirectorMode(1, 4, 0);
    G6_00B87EFC = 0;
    break;
  case 6:
    if (has_frames()) {
      G6Call0050E940(0);
      P29_FlagA8 = 0; P29_Mode = mode; DirNodeTable = (DIR_NODE *)DirTableB; P29_FlagB0 = 1; DirIndicatorOn = 0;
      DirectorUnk7C = 0x1b; P29_Flag98 = 0; G6_00B87EFC = 0;
    }
    break;
  case 7:
    G6Call0050E940(0);
    P29_FlagA8 = 0; P29_Mode = mode; DirNodeTable = NULL; P29_FlagB0 = 0; DirIndicatorOn = 1; DirectorUnk84 = 0; P29_Flag98 = 0;
    G6_00B87EFC = 0; Call005243EB();
    break;
  case 8: case 10: case 9:
    G6Call0050E940(1);
    P29_Mode = mode; DirNodeTable = (DIR_NODE *)DirTableA; P29_FlagA8 = 1; P29_FlagB0 = 1; DirIndicatorOn = 0;
    P29_Flag9C = 1; DirUseDI = 0; P29_FlagA4 = 1; P29_Flag94 = 1; G6_00B87EFC = 1;
    P29_Flag98 = (mode == 9) ? 0 : 1;
    break;
  case 0xb: case 0xd:
    if (has_frames()) {
      G6Call0050E940(0);
      P29_FlagA8 = 0; P29_Mode = mode; DirNodeTable = NULL; P29_FlagB0 = 0; DirIndicatorOn = 0;
      DirectorUnk7C = 0; P29_Flag98 = 0;
      if (DirectorBuffer == NULL) LoadWaypoints();
      G6_00B87EFC = 0; Call005243EB();
    } else { SetDirectorMode(0, 0, 0); G6Call0050E940(1); }
    break;
  case 0xe:
    G6Call0050E940(0);
    P29_FlagA8 = 0; P29_Mode = mode; DirNodeTable = NULL; P29_FlagB0 = 0; DirIndicatorOn = 0; DirectorUnk84 = 4; P29_Flag98 = 0;
    G6_00B87EFC = 0; Call005243EB();
    break;
  case 0xf:
    G6Call0050E940(0);
    P29_FlagA8 = 0; P29_Mode = mode; DirNodeTable = NULL; P29_FlagB0 = 0; DirIndicatorOn = 1; DirectorUnk84 = 2; P29_Flag98 = 0;
    G6_00B87EFC = 0; Call005243EB();
    break;
  default:
    DebugLog("SetDirectorMode: Illegal mode identifier provided, function failed.\n");
  }
  return prev;
}
