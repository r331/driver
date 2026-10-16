#pragma once
#include <stdint.h>
#include "gvar.h"
#include "cartab.h"
/* v1.90: ported145 — загрузка уровня 004d38b7 (вызывается из P136_GameLoop): демо-режимы 200/0xfa..0xfc (ReplayData\Demo),
   режим режиссёра, конфиг/миссия, звуковые банки master.dss/cops.dss, LEVELS\<город>.D3D, DATA\(US)LOADING.BMP, сброс
   состояния, srand(0x3039), окно отрисовки, FRUSTRUM.DAT, LoadLevel, инициализация подсистем, позиция игрока, CD-трек. cdecl. */
typedef char    p145_s24_t[0x24];
typedef int32_t p145_splash_t[0x57c];   /* 00d14f00..00d164ef: стек записей скрипта/брызг ([0] — число, записи по 0x34 от +0x1c6) */
_Static_assert(sizeof(p145_splash_t) == 0x15f0, "p145_splash_t");
#define P145_B20304   GAME_VAR(int32_t, P145_B20304, 0x00b20304)
#define P145_B20308   GAME_VAR(int32_t, P145_B20308, 0x00b20308)       /* флаг: конфиг повтора по имени P145_CfgName */
#define P145_D0FE18   GAME_VAR(uint16_t, P145_D0FE18, 0x00d0fe18)
#define P145_D10E60   GAME_VAR(uint16_t, P145_D10E60, 0x00d10e60)
#define P145_D1184C   GAME_VAR(int32_t, P145_D1184C, 0x00d1184c)
#define P145_D118C4   GAME_VAR(int32_t, P145_D118C4, 0x00d118c4)
#define P145_BankCops GAME_VAR(int32_t, P145_BankCops, 0x00d118cc)    /* результат 00524496("cops.dss", 0x8000) */
#define P145_BankMain GAME_VAR(int32_t, P145_BankMain, 0x00d118d0)    /* результат 00524496("master.dss", 0) */
#define P145_CfgName  GAME_VAR(p145_s24_t, P145_CfgName, 0x00d11900)
#define P145_Splash   GAME_VAR(p145_splash_t, P145_Splash, 0x00d14f00)
/* поля записи игрока 00d07888 (+0x54..+0x68) в таблице машин */
#define P145_D078DC   CARTAB_VAR(int32_t, P145_D078DC, 0x00d078dc)
#define P145_D078E0   CARTAB_VAR(int32_t, P145_D078E0, 0x00d078e0)
#define P145_D078E4   CARTAB_VAR(int32_t, P145_D078E4, 0x00d078e4)
#define P145_D078E8   CARTAB_VAR(int32_t, P145_D078E8, 0x00d078e8)
#define P145_D078EC   CARTAB_VAR(int32_t, P145_D078EC, 0x00d078ec)
#define P145_D078F0   CARTAB_VAR(int32_t, P145_D078F0, 0x00d078f0)
#ifndef RE_HOOK_BUILD
#pragma push_macro("P145_B20304") /*gvi*/
#undef P145_B20304 /*gvi*/
#pragma push_macro("P145_B20308") /*gvi*/
#undef P145_B20308 /*gvi*/
#pragma push_macro("P145_D1184C") /*gvi*/
#undef P145_D1184C /*gvi*/
#pragma push_macro("P145_D118C4") /*gvi*/
#undef P145_D118C4 /*gvi*/
#pragma push_macro("P145_BankCops") /*gvi*/
#undef P145_BankCops /*gvi*/
#pragma push_macro("P145_BankMain") /*gvi*/
#undef P145_BankMain /*gvi*/
extern int32_t P145_B20304, P145_B20308, P145_D1184C, P145_D118C4, P145_BankCops, P145_BankMain;
#pragma pop_macro("P145_BankMain") /*gvi*/
#pragma pop_macro("P145_BankCops") /*gvi*/
#pragma pop_macro("P145_D118C4") /*gvi*/
#pragma pop_macro("P145_D1184C") /*gvi*/
#pragma pop_macro("P145_B20308") /*gvi*/
#pragma pop_macro("P145_B20304") /*gvi*/
#pragma push_macro("P145_D0FE18") /*gvi*/
#undef P145_D0FE18 /*gvi*/
#pragma push_macro("P145_D10E60") /*gvi*/
#undef P145_D10E60 /*gvi*/
extern uint16_t P145_D0FE18, P145_D10E60;
#pragma pop_macro("P145_D10E60") /*gvi*/
#pragma pop_macro("P145_D0FE18") /*gvi*/
#pragma push_macro("P145_CfgName") /*gvi*/
#undef P145_CfgName /*gvi*/
extern p145_s24_t P145_CfgName;
#pragma pop_macro("P145_CfgName") /*gvi*/
#pragma push_macro("P145_Splash") /*gvi*/
#undef P145_Splash /*gvi*/
extern p145_splash_t P145_Splash;
#pragma pop_macro("P145_Splash") /*gvi*/
#endif
int32_t P145_LevelLoad(void);   /* 004d38b7: 1 — уровень загружен, 0 — нет конфига демо/повтора или уровня */
/* gvar-img v2.03 begin (tools/gen_gvar_img.py) */
#if !defined(RE_HOOK_BUILD) && !defined(RE_GVAR_PLAIN)
#undef P145_B20304
#define P145_B20304 (*(int32_t *)re_gvar(0x00b20304u, sizeof(int32_t), (void *)&P145_B20304))
#undef P145_B20308
#define P145_B20308 (*(int32_t *)re_gvar(0x00b20308u, sizeof(int32_t), (void *)&P145_B20308))
#undef P145_D0FE18
#define P145_D0FE18 (*(uint16_t *)re_gvar(0x00d0fe18u, sizeof(uint16_t), (void *)&P145_D0FE18))
#undef P145_D10E60
#define P145_D10E60 (*(uint16_t *)re_gvar(0x00d10e60u, sizeof(uint16_t), (void *)&P145_D10E60))
#undef P145_D1184C
#define P145_D1184C (*(int32_t *)re_gvar(0x00d1184cu, sizeof(int32_t), (void *)&P145_D1184C))
#undef P145_D118C4
#define P145_D118C4 (*(int32_t *)re_gvar(0x00d118c4u, sizeof(int32_t), (void *)&P145_D118C4))
#undef P145_BankCops
#define P145_BankCops (*(int32_t *)re_gvar(0x00d118ccu, sizeof(int32_t), (void *)&P145_BankCops))
#undef P145_BankMain
#define P145_BankMain (*(int32_t *)re_gvar(0x00d118d0u, sizeof(int32_t), (void *)&P145_BankMain))
#undef P145_CfgName
#define P145_CfgName (*(p145_s24_t *)re_gvar(0x00d11900u, sizeof(p145_s24_t), (void *)&P145_CfgName))
#undef P145_Splash
#define P145_Splash (*(p145_splash_t *)re_gvar(0x00d14f00u, sizeof(p145_splash_t), (void *)&P145_Splash))
#endif
/* gvar-img v2.03 end */
