/* SetDirectorMode — переключение режимов режиссёра повторов; восстановлено из Game.exe (004c875d). */
#include "ported29.h"
#include "ported6.h"
#include "director.h"
#include "dirnodes.h"
#include "directorstorage.h"
#include "engine.h"
#include "unported.h"
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P29_Mode")
#undef P29_Mode
#pragma push_macro("P29_Mode") /*gvi*/
#undef P29_Mode /*gvi*/
int32_t P29_Mode;
#pragma pop_macro("P29_Mode") /*gvi*/
#pragma pop_macro("P29_Mode")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P29_Param")
#undef P29_Param
#pragma push_macro("P29_Param") /*gvi*/
#undef P29_Param /*gvi*/
int32_t P29_Param;
#pragma pop_macro("P29_Param") /*gvi*/
#pragma pop_macro("P29_Param")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P29_Flag48")
#undef P29_Flag48
#pragma push_macro("P29_Flag48") /*gvi*/
#undef P29_Flag48 /*gvi*/
int32_t P29_Flag48;
#pragma pop_macro("P29_Flag48") /*gvi*/
#pragma pop_macro("P29_Flag48")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P29_FlagA4")
#undef P29_FlagA4
#pragma push_macro("P29_FlagA4") /*gvi*/
#undef P29_FlagA4 /*gvi*/
int32_t P29_FlagA4;
#pragma pop_macro("P29_FlagA4") /*gvi*/
#pragma pop_macro("P29_FlagA4")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P29_Flag74")
#undef P29_Flag74
#pragma push_macro("P29_Flag74") /*gvi*/
#undef P29_Flag74 /*gvi*/
int32_t P29_Flag74;
#pragma pop_macro("P29_Flag74") /*gvi*/
#pragma pop_macro("P29_Flag74")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P29_Flag9C")
#undef P29_Flag9C
#pragma push_macro("P29_Flag9C") /*gvi*/
#undef P29_Flag9C /*gvi*/
int32_t P29_Flag9C;
#pragma pop_macro("P29_Flag9C") /*gvi*/
#pragma pop_macro("P29_Flag9C")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P29_FlagA8")
#undef P29_FlagA8
#pragma push_macro("P29_FlagA8") /*gvi*/
#undef P29_FlagA8 /*gvi*/
int32_t P29_FlagA8;
#pragma pop_macro("P29_FlagA8") /*gvi*/
#pragma pop_macro("P29_FlagA8")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P29_FlagB0")
#undef P29_FlagB0
#pragma push_macro("P29_FlagB0") /*gvi*/
#undef P29_FlagB0 /*gvi*/
int32_t P29_FlagB0;
#pragma pop_macro("P29_FlagB0") /*gvi*/
#pragma pop_macro("P29_FlagB0")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P29_Flag98")
#undef P29_Flag98
#pragma push_macro("P29_Flag98") /*gvi*/
#undef P29_Flag98 /*gvi*/
int32_t P29_Flag98;
#pragma pop_macro("P29_Flag98") /*gvi*/
#pragma pop_macro("P29_Flag98")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P29_Flag94")
#undef P29_Flag94
#pragma push_macro("P29_Flag94") /*gvi*/
#undef P29_Flag94 /*gvi*/
int32_t P29_Flag94;
#pragma pop_macro("P29_Flag94") /*gvi*/
#pragma pop_macro("P29_Flag94")
#endif
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
