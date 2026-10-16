/* Партия v0.39: обработчики пунктов меню (phase 0 — пометить, 2 — вызвать), освобождение буферов, мелкие функции. */
#pragma once
#include "menugfx.h"
#include "menutab.h"
#include "gvar.h"
#include "engine.h"
#include "unported.h"
#define D_00549f8c GAME_VAR(uint8_t, D_00549f8c, 0x00549f8c)
#ifndef RE_HOOK_BUILD
extern uint8_t D_00549f8c;
#endif
#define D_00549f9c GAME_VAR(uint8_t, D_00549f9c, 0x00549f9c)
#ifndef RE_HOOK_BUILD
extern uint8_t D_00549f9c;
#endif
#define D_00549fdc GAME_VAR(uint8_t, D_00549fdc, 0x00549fdc)
#ifndef RE_HOOK_BUILD
extern uint8_t D_00549fdc;
#endif
#define D_00549fec GAME_VAR(uint8_t, D_00549fec, 0x00549fec)
#ifndef RE_HOOK_BUILD
extern uint8_t D_00549fec;
#endif
#define D_0054a144 GAME_VAR(int32_t, D_0054a144, 0x0054a144)
#ifndef RE_HOOK_BUILD
extern int32_t D_0054a144;
#endif
#define D_0054a254 MENUGFX_VAR(uint8_t, D_0054a254, 0x0054a254)
#ifndef RE_HOOK_BUILD
#endif
#define D_0054a264 MENUGFX_VAR(uint8_t, D_0054a264, 0x0054a264)
#ifndef RE_HOOK_BUILD
#endif
#define D_0054a274 MENUGFX_VAR(uint8_t, D_0054a274, 0x0054a274)
#ifndef RE_HOOK_BUILD
#endif
#define D_0054a284 MENUGFX_VAR(uint8_t, D_0054a284, 0x0054a284)
#ifndef RE_HOOK_BUILD
#endif
#define D_0054a294 MENUGFX_VAR(uint8_t, D_0054a294, 0x0054a294)
#ifndef RE_HOOK_BUILD
#endif
#define D_0054a2a4 MENUGFX_VAR(uint8_t, D_0054a2a4, 0x0054a2a4)
#ifndef RE_HOOK_BUILD
#endif
#define D_0054a2b4 MENUGFX_VAR(uint8_t, D_0054a2b4, 0x0054a2b4)
#ifndef RE_HOOK_BUILD
#endif
#define D_0054a2c4 MENUGFX_VAR(uint8_t, D_0054a2c4, 0x0054a2c4)
#ifndef RE_HOOK_BUILD
#endif
#define D_0054a2d4 MENUGFX_VAR(uint8_t, D_0054a2d4, 0x0054a2d4)
#ifndef RE_HOOK_BUILD
#endif
#define D_0054a2e4 MENUGFX_VAR(uint8_t, D_0054a2e4, 0x0054a2e4)
#ifndef RE_HOOK_BUILD
#endif
#define D_0054a2f4 MENUGFX_VAR(uint8_t, D_0054a2f4, 0x0054a2f4)
#ifndef RE_HOOK_BUILD
#endif
#define D_0054a304 MENUGFX_VAR(uint8_t, D_0054a304, 0x0054a304)
#ifndef RE_HOOK_BUILD
#endif
#define D_0054a314 MENUGFX_VAR(uint8_t, D_0054a314, 0x0054a314)
#ifndef RE_HOOK_BUILD
#endif
#define D_0054a324 MENUGFX_VAR(uint8_t, D_0054a324, 0x0054a324)
#ifndef RE_HOOK_BUILD
#endif
#define D_0054a334 MENUGFX_VAR(uint8_t, D_0054a334, 0x0054a334)
#ifndef RE_HOOK_BUILD
#endif
#define D_0054a344 MENUGFX_VAR(uint8_t, D_0054a344, 0x0054a344)
#ifndef RE_HOOK_BUILD
#endif
#define D_0054a354 MENUGFX_VAR(uint8_t, D_0054a354, 0x0054a354)
#ifndef RE_HOOK_BUILD
#endif
#define D_0054a364 MENUGFX_VAR(uint8_t, D_0054a364, 0x0054a364)
#ifndef RE_HOOK_BUILD
#endif
#define D_0054a374 MENUGFX_VAR(uint8_t, D_0054a374, 0x0054a374)
#ifndef RE_HOOK_BUILD
#endif
#define D_0054a384 MENUGFX_VAR(uint8_t, D_0054a384, 0x0054a384)
#ifndef RE_HOOK_BUILD
#endif
#define D_0054a394 MENUGFX_VAR(uint8_t, D_0054a394, 0x0054a394)
#ifndef RE_HOOK_BUILD
#endif
#define D_0054a3a4 MENUGFX_VAR(uint8_t, D_0054a3a4, 0x0054a3a4)
#ifndef RE_HOOK_BUILD
#endif
#define D_0054a3b4 MENUGFX_VAR(uint8_t, D_0054a3b4, 0x0054a3b4)
#ifndef RE_HOOK_BUILD
#endif
#define D_0054a3c4 MENUGFX_VAR(uint8_t, D_0054a3c4, 0x0054a3c4)
#ifndef RE_HOOK_BUILD
#endif
#define D_0054a3d4 MENUGFX_VAR(uint8_t, D_0054a3d4, 0x0054a3d4)
#ifndef RE_HOOK_BUILD
#endif
#define D_0054a3e4 MENUGFX_VAR(uint8_t, D_0054a3e4, 0x0054a3e4)
#ifndef RE_HOOK_BUILD
#endif
#define D_0054a3f4 MENUGFX_VAR(uint8_t, D_0054a3f4, 0x0054a3f4)
#ifndef RE_HOOK_BUILD
#endif
#define D_0054a404 MENUGFX_VAR(uint8_t, D_0054a404, 0x0054a404)
#ifndef RE_HOOK_BUILD
#endif
#define D_0054a414 MENUGFX_VAR(uint8_t, D_0054a414, 0x0054a414)
#ifndef RE_HOOK_BUILD
#endif
#define D_0054a424 MENUGFX_VAR(uint8_t, D_0054a424, 0x0054a424)
#ifndef RE_HOOK_BUILD
#endif
#define D_0054a434 MENUGFX_VAR(uint8_t, D_0054a434, 0x0054a434)
#ifndef RE_HOOK_BUILD
#endif
#define D_0054a444 MENUGFX_VAR(uint8_t, D_0054a444, 0x0054a444)
#ifndef RE_HOOK_BUILD
#endif
#define D_0054a454 MENUGFX_VAR(uint8_t, D_0054a454, 0x0054a454)
#ifndef RE_HOOK_BUILD
#endif
#define D_0054c044 GAME_VAR(uint8_t, D_0054c044, 0x0054c044)
#ifndef RE_HOOK_BUILD
extern uint8_t D_0054c044;
#endif
#define D_0054c054 GAME_VAR(uint8_t, D_0054c054, 0x0054c054)
#ifndef RE_HOOK_BUILD
extern uint8_t D_0054c054;
#endif
#define D_0054c064 GAME_VAR(uint8_t, D_0054c064, 0x0054c064)
#ifndef RE_HOOK_BUILD
extern uint8_t D_0054c064;
#endif
#define D_0054c074 GAME_VAR(uint8_t, D_0054c074, 0x0054c074)
#ifndef RE_HOOK_BUILD
extern uint8_t D_0054c074;
#endif
#define D_0054c084 GAME_VAR(uint8_t, D_0054c084, 0x0054c084)
#ifndef RE_HOOK_BUILD
extern uint8_t D_0054c084;
#endif
#define D_0054c094 GAME_VAR(uint8_t, D_0054c094, 0x0054c094)
#ifndef RE_HOOK_BUILD
extern uint8_t D_0054c094;
#endif
#define D_0054c0a4 GAME_VAR(uint8_t, D_0054c0a4, 0x0054c0a4)
#ifndef RE_HOOK_BUILD
extern uint8_t D_0054c0a4;
#endif
#define D_0054c0b4 GAME_VAR(uint8_t, D_0054c0b4, 0x0054c0b4)
#ifndef RE_HOOK_BUILD
extern uint8_t D_0054c0b4;
#endif
#define D_0054c0c4 GAME_VAR(uint8_t, D_0054c0c4, 0x0054c0c4)
#ifndef RE_HOOK_BUILD
extern uint8_t D_0054c0c4;
#endif
#define D_0054c0d4 GAME_VAR(uint8_t, D_0054c0d4, 0x0054c0d4)
#ifndef RE_HOOK_BUILD
extern uint8_t D_0054c0d4;
#endif
#define D_0054c0e4 GAME_VAR(uint8_t, D_0054c0e4, 0x0054c0e4)
#ifndef RE_HOOK_BUILD
extern uint8_t D_0054c0e4;
#endif
#define D_0054c0f4 GAME_VAR(uint8_t, D_0054c0f4, 0x0054c0f4)
#ifndef RE_HOOK_BUILD
extern uint8_t D_0054c0f4;
#endif
#define D_0054c104 GAME_VAR(uint8_t, D_0054c104, 0x0054c104)
#ifndef RE_HOOK_BUILD
extern uint8_t D_0054c104;
#endif
#define D_0054c114 GAME_VAR(uint8_t, D_0054c114, 0x0054c114)
#ifndef RE_HOOK_BUILD
extern uint8_t D_0054c114;
#endif
#define D_0054c124 GAME_VAR(uint8_t, D_0054c124, 0x0054c124)
#ifndef RE_HOOK_BUILD
extern uint8_t D_0054c124;
#endif
#define D_0054c134 GAME_VAR(uint8_t, D_0054c134, 0x0054c134)
#ifndef RE_HOOK_BUILD
extern uint8_t D_0054c134;
#endif
#define D_0054c144 GAME_VAR(uint8_t, D_0054c144, 0x0054c144)
#ifndef RE_HOOK_BUILD
extern uint8_t D_0054c144;
#endif
#define D_0054c154 GAME_VAR(uint8_t, D_0054c154, 0x0054c154)
#ifndef RE_HOOK_BUILD
extern uint8_t D_0054c154;
#endif
#define D_0054c164 GAME_VAR(uint8_t, D_0054c164, 0x0054c164)
#ifndef RE_HOOK_BUILD
extern uint8_t D_0054c164;
#endif
#define D_0054c174 GAME_VAR(uint8_t, D_0054c174, 0x0054c174)
#ifndef RE_HOOK_BUILD
extern uint8_t D_0054c174;
#endif
#define D_0054c184 GAME_VAR(uint8_t, D_0054c184, 0x0054c184)
#ifndef RE_HOOK_BUILD
extern uint8_t D_0054c184;
#endif
#define D_0054c194 GAME_VAR(uint8_t, D_0054c194, 0x0054c194)
#ifndef RE_HOOK_BUILD
extern uint8_t D_0054c194;
#endif
#define D_0054c1a4 GAME_VAR(uint8_t, D_0054c1a4, 0x0054c1a4)
#ifndef RE_HOOK_BUILD
extern uint8_t D_0054c1a4;
#endif
#define D_0054c1b4 GAME_VAR(uint8_t, D_0054c1b4, 0x0054c1b4)
#ifndef RE_HOOK_BUILD
extern uint8_t D_0054c1b4;
#endif
#define D_0054c364 GAME_VAR(uint8_t, D_0054c364, 0x0054c364)
#ifndef RE_HOOK_BUILD
extern uint8_t D_0054c364;
#endif
#define D_0054c374 GAME_VAR(uint8_t, D_0054c374, 0x0054c374)
#ifndef RE_HOOK_BUILD
extern uint8_t D_0054c374;
#endif
#define D_0054c384 GAME_VAR(uint8_t, D_0054c384, 0x0054c384)
#ifndef RE_HOOK_BUILD
extern uint8_t D_0054c384;
#endif
#define D_0054c394 GAME_VAR(uint8_t, D_0054c394, 0x0054c394)
#ifndef RE_HOOK_BUILD
extern uint8_t D_0054c394;
#endif
#define D_0054c3a4 GAME_VAR(uint8_t, D_0054c3a4, 0x0054c3a4)
#ifndef RE_HOOK_BUILD
extern uint8_t D_0054c3a4;
#endif
#define D_0054c3b4 GAME_VAR(uint8_t, D_0054c3b4, 0x0054c3b4)
#ifndef RE_HOOK_BUILD
extern uint8_t D_0054c3b4;
#endif
#define D_0054c3c4 GAME_VAR(uint8_t, D_0054c3c4, 0x0054c3c4)
#ifndef RE_HOOK_BUILD
extern uint8_t D_0054c3c4;
#endif
#define D_0054c3d4 GAME_VAR(uint8_t, D_0054c3d4, 0x0054c3d4)
#ifndef RE_HOOK_BUILD
extern uint8_t D_0054c3d4;
#endif
#define D_0054c3e4 GAME_VAR(uint8_t, D_0054c3e4, 0x0054c3e4)
#ifndef RE_HOOK_BUILD
extern uint8_t D_0054c3e4;
#endif
#define D_0054c3f4 GAME_VAR(uint8_t, D_0054c3f4, 0x0054c3f4)
#ifndef RE_HOOK_BUILD
extern uint8_t D_0054c3f4;
#endif
#define D_0054c404 GAME_VAR(uint8_t, D_0054c404, 0x0054c404)
#ifndef RE_HOOK_BUILD
extern uint8_t D_0054c404;
#endif
#define D_0054c414 GAME_VAR(uint8_t, D_0054c414, 0x0054c414)
#ifndef RE_HOOK_BUILD
extern uint8_t D_0054c414;
#endif
#define D_0054c424 GAME_VAR(uint8_t, D_0054c424, 0x0054c424)
#ifndef RE_HOOK_BUILD
extern uint8_t D_0054c424;
#endif
#define D_0054c434 GAME_VAR(uint8_t, D_0054c434, 0x0054c434)
#ifndef RE_HOOK_BUILD
extern uint8_t D_0054c434;
#endif
#define D_0054c444 GAME_VAR(uint8_t, D_0054c444, 0x0054c444)
#ifndef RE_HOOK_BUILD
extern uint8_t D_0054c444;
#endif
#define D_0054c454 GAME_VAR(uint8_t, D_0054c454, 0x0054c454)
#ifndef RE_HOOK_BUILD
extern uint8_t D_0054c454;
#endif
#define D_0054c464 GAME_VAR(uint8_t, D_0054c464, 0x0054c464)
#ifndef RE_HOOK_BUILD
extern uint8_t D_0054c464;
#endif
#define D_0054c474 GAME_VAR(uint8_t, D_0054c474, 0x0054c474)
#ifndef RE_HOOK_BUILD
extern uint8_t D_0054c474;
#endif
#define D_0054c484 GAME_VAR(uint8_t, D_0054c484, 0x0054c484)
#ifndef RE_HOOK_BUILD
extern uint8_t D_0054c484;
#endif
#define D_0054c494 GAME_VAR(uint8_t, D_0054c494, 0x0054c494)
#ifndef RE_HOOK_BUILD
extern uint8_t D_0054c494;
#endif
#define D_0054c4a4 GAME_VAR(uint8_t, D_0054c4a4, 0x0054c4a4)
#ifndef RE_HOOK_BUILD
extern uint8_t D_0054c4a4;
#endif
#define D_0054c4b4 GAME_VAR(uint8_t, D_0054c4b4, 0x0054c4b4)
#ifndef RE_HOOK_BUILD
extern uint8_t D_0054c4b4;
#endif
#define D_0054c4c4 GAME_VAR(uint8_t, D_0054c4c4, 0x0054c4c4)
#ifndef RE_HOOK_BUILD
extern uint8_t D_0054c4c4;
#endif
#define D_0054c4d4 GAME_VAR(uint8_t, D_0054c4d4, 0x0054c4d4)
#ifndef RE_HOOK_BUILD
extern uint8_t D_0054c4d4;
#endif
#define D_0054c4e4 GAME_VAR(uint8_t, D_0054c4e4, 0x0054c4e4)
#ifndef RE_HOOK_BUILD
extern uint8_t D_0054c4e4;
#endif
#define D_0054c4f4 GAME_VAR(uint8_t, D_0054c4f4, 0x0054c4f4)
#ifndef RE_HOOK_BUILD
extern uint8_t D_0054c4f4;
#endif
#define D_0054c504 GAME_VAR(uint8_t, D_0054c504, 0x0054c504)
#ifndef RE_HOOK_BUILD
extern uint8_t D_0054c504;
#endif
#define D_0054c514 GAME_VAR(uint8_t, D_0054c514, 0x0054c514)
#ifndef RE_HOOK_BUILD
extern uint8_t D_0054c514;
#endif
#define D_0054dbc4 MENUTAB_VAR(uint8_t, D_0054dbc4, 0x0054dbc4)
#define D_0054dbd4 MENUTAB_VAR(uint8_t, D_0054dbd4, 0x0054dbd4)
#define D_0054dbe4 MENUTAB_VAR(uint8_t, D_0054dbe4, 0x0054dbe4)
#define D_0054dbf4 MENUTAB_VAR(uint8_t, D_0054dbf4, 0x0054dbf4)
#define D_0054dc04 MENUTAB_VAR(uint8_t, D_0054dc04, 0x0054dc04)
#define D_0054dc14 MENUTAB_VAR(uint8_t, D_0054dc14, 0x0054dc14)
#define D_0054dc24 MENUTAB_VAR(uint8_t, D_0054dc24, 0x0054dc24)
#define D_0054dc34 MENUTAB_VAR(uint8_t, D_0054dc34, 0x0054dc34)
#define D_0054dc44 MENUTAB_VAR(uint8_t, D_0054dc44, 0x0054dc44)
#define D_0054dc54 MENUTAB_VAR(uint8_t, D_0054dc54, 0x0054dc54)
#define D_0054dc64 MENUTAB_VAR(uint8_t, D_0054dc64, 0x0054dc64)
#define D_0054dc74 MENUTAB_VAR(uint8_t, D_0054dc74, 0x0054dc74)
#define D_0054dc84 MENUTAB_VAR(uint8_t, D_0054dc84, 0x0054dc84)
#define D_0054dc94 MENUTAB_VAR(uint8_t, D_0054dc94, 0x0054dc94)
#define D_0054dca4 MENUTAB_VAR(uint8_t, D_0054dca4, 0x0054dca4)
#define D_0054dcb4 MENUTAB_VAR(uint8_t, D_0054dcb4, 0x0054dcb4)
#define D_0054dcc4 MENUTAB_VAR(uint8_t, D_0054dcc4, 0x0054dcc4)
#define D_0054dcd4 MENUTAB_VAR(uint8_t, D_0054dcd4, 0x0054dcd4)
#define D_0054dce4 MENUTAB_VAR(uint8_t, D_0054dce4, 0x0054dce4)
#define D_0054dcf4 MENUTAB_VAR(uint8_t, D_0054dcf4, 0x0054dcf4)
#define D_005d577c GAME_VAR(int32_t, D_005d577c, 0x005d577c)
#ifndef RE_HOOK_BUILD
extern int32_t D_005d577c;
#endif
#define D_005f7e4c GAME_VAR(int32_t, D_005f7e4c, 0x005f7e4c)
#ifndef RE_HOOK_BUILD
extern int32_t D_005f7e4c;
#endif
#define D_005fea98 GAME_VAR(int32_t, D_005fea98, 0x005fea98)
#ifndef RE_HOOK_BUILD
extern int32_t D_005fea98;
#endif
#define D_005fed98 GAME_VAR(void*, D_005fed98, 0x005fed98)
#ifndef RE_HOOK_BUILD
extern void* D_005fed98;
#endif
#define D_005feda0 GAME_VAR(int32_t, D_005feda0, 0x005feda0)
#ifndef RE_HOOK_BUILD
extern int32_t D_005feda0;
#endif
#define D_00b1c0d4 GAME_VAR(int32_t, G00B1C0D4, 0x00b1c0d4)   /* v2.00: один native-объект с G00B1C0D4 (uihandlers3) */
#ifndef RE_HOOK_BUILD
extern int32_t D_00b1c0d4;
#endif
#define D_00b1c0d8 GAME_VAR(int32_t, G00B1C0D8, 0x00b1c0d8)   /* v2.00: один native-объект с G00B1C0D8 */
#ifndef RE_HOOK_BUILD
extern int32_t D_00b1c0d8;
#endif
#define D_00b87e30 GAME_VAR(int32_t, D_00b87e30, 0x00b87e30)
#ifndef RE_HOOK_BUILD
extern int32_t D_00b87e30;
#endif
#define D_00b93e48 GAME_VAR(int32_t, D_00b93e48, 0x00b93e48)
#ifndef RE_HOOK_BUILD
extern int32_t D_00b93e48;
#endif
#define D_00b93e4c GAME_VAR(int32_t, D_00b93e4c, 0x00b93e4c)
#ifndef RE_HOOK_BUILD
extern int32_t D_00b93e4c;
#endif
#define D_00b93e50 GAME_VAR(int32_t, D_00b93e50, 0x00b93e50)
#ifndef RE_HOOK_BUILD
extern int32_t D_00b93e50;
#endif
#define D_00c80ca0 GAME_VAR(int32_t, D_00c80ca0, 0x00c80ca0)
#ifndef RE_HOOK_BUILD
extern int32_t D_00c80ca0;
#endif
#define D_00c81494 GAME_VAR(int32_t, D_00c81494, 0x00c81494)
#ifndef RE_HOOK_BUILD
extern int32_t D_00c81494;
#endif
#define D_00c98ed0 GAME_VAR(void*, D_00c98ed0, 0x00c98ed0)
#ifndef RE_HOOK_BUILD
extern void* D_00c98ed0;
#endif
#define D_00d00204 GAME_VAR(int32_t, D_00d00204, 0x00d00204)
#ifndef RE_HOOK_BUILD
extern int32_t D_00d00204;
#endif
#define D_00d00230 GAME_VAR(void*, D_00d00230, 0x00d00230)
#ifndef RE_HOOK_BUILD
extern void* D_00d00230;
#endif
#define D_00d1193c GAME_VAR(int32_t, D_00d1193c, 0x00d1193c)
#ifndef RE_HOOK_BUILD
extern int32_t D_00d1193c;
#endif
#define D_00d14ee0 GAME_VAR(int32_t, D_00d14ee0, 0x00d14ee0)
#ifndef RE_HOOK_BUILD
extern int32_t D_00d14ee0;
#endif
#define D_00d14ee4 GAME_VAR(int32_t, D_00d14ee4, 0x00d14ee4)
#ifndef RE_HOOK_BUILD
extern int32_t D_00d14ee4;
#endif
#define D_00d17ec8 GAME_VAR(void*, D_00d17ec8, 0x00d17ec8)
#ifndef RE_HOOK_BUILD
extern void* D_00d17ec8;
#endif
#define D_00dbb450 GAME_VAR(int32_t, D_00dbb450, 0x00dbb450)
#ifndef RE_HOOK_BUILD
extern int32_t D_00dbb450;
#endif
typedef int32_t int32_t_arr_010de120[0x4000];
#define D_010de120 GAME_VAR(int32_t_arr_010de120, D_010de120, 0x010de120)
#ifndef RE_HOOK_BUILD
extern int32_t_arr_010de120 D_010de120;
#endif
#define D_01134528 GAME_VAR(int32_t, D_01134528, 0x01134528)
#ifndef RE_HOOK_BUILD
extern int32_t D_01134528;
#endif
typedef int32_t int32_t_arr_01134554[0x4000];
#define D_01134554 GAME_VAR(int32_t_arr_01134554, D_01134554, 0x01134554)
#ifndef RE_HOOK_BUILD
extern int32_t_arr_01134554 D_01134554;
#endif
#define D_01134ea0 GAME_VAR(int32_t, D_01134ea0, 0x01134ea0)
#ifndef RE_HOOK_BUILD
extern int32_t D_01134ea0;
#endif
typedef int32_t int32_t_arr_01134ec0[0x4000];
#define D_01134ec0 GAME_VAR(int32_t_arr_01134ec0, D_01134ec0, 0x01134ec0)
#ifndef RE_HOOK_BUILD
extern int32_t_arr_01134ec0 D_01134ec0;
#endif
void MenuSlotHandler0040737A(int32_t phase);
void MenuSlotHandler00407605(int32_t phase);
void MenuSlotHandler004088AA(int32_t phase);
void MenuSlotHandler00408963(int32_t phase);
void MenuSlotHandler00408A38(int32_t phase);
void MenuSlotHandler00408AD2(int32_t phase);
void MenuSlotHandler00408B6C(int32_t phase);
void MenuSlotHandler00408C06(int32_t phase);
void MenuSlotHandler00408CDB(int32_t phase);
void MenuSlotHandler00408D75(int32_t phase);
void MenuSlotHandler00408E0F(int32_t phase);
void MenuSlotHandler00408EA9(int32_t phase);
void MenuSlotHandler00408F43(int32_t phase);
void MenuSlotHandler00408FDD(int32_t phase);
void MenuSlotHandler00409077(int32_t phase);
void MenuSlotHandler00409111(int32_t phase);
void MenuSlotHandler0040FE6F(int32_t phase);
void MenuSlotHandler0040FF29(int32_t phase);
void MenuSlotHandler0040FFE3(int32_t phase);
void MenuSlotHandler0041009D(int32_t phase);
void MenuSlotHandler00410157(int32_t phase);
void MenuSlotHandler00410211(int32_t phase);
void MenuSlotHandler004102CB(int32_t phase);
void MenuSlotHandler00410385(int32_t phase);
void MenuSlotHandler0041043F(int32_t phase);
void MenuSlotHandler004104F9(int32_t phase);
void MenuSlotHandler004105B3(int32_t phase);
void MenuSlotHandler0041066D(int32_t phase);
void MenuSlotHandler00411091(int32_t phase);
void MenuSlotHandler00411146(int32_t phase);
void MenuSlotHandler004111FB(int32_t phase);
void MenuSlotHandler004112B0(int32_t phase);
void MenuSlotHandler00411365(int32_t phase);
void MenuSlotHandler0041141A(int32_t phase);
void MenuSlotHandler004114CF(int32_t phase);
void MenuSlotHandler00411584(int32_t phase);
void MenuSlotHandler00411639(int32_t phase);
void MenuSlotHandler004116EE(int32_t phase);
void MenuSlotHandler004117A3(int32_t phase);
void MenuSlotHandler00411858(int32_t phase);
void MenuSlotHandler0041190D(int32_t phase);
void MenuSlotHandler004119C2(int32_t phase);
void MenuSlotHandler00414FE3(int32_t phase);
void MenuSlotHandler00415157(int32_t phase);
void MenuSlotHandler00415276(int32_t phase);
void MenuSlotHandler00415369(int32_t phase);
void MenuSlotHandler004153F9(int32_t phase);
void MenuSlotHandler0041549C(int32_t phase);
void MenuSlotHandler0041553B(int32_t phase);
void MenuSlotHandler004155F2(int32_t phase);
void MenuSlotHandler004156AC(int32_t phase);
void MenuSlotHandlerReset004091F3(int32_t phase);
void MenuSlotHandlerReset0040929A(int32_t phase);
void MenuSlotHandlerReset00409341(int32_t phase);
void MenuSlotHandlerReset004093E8(int32_t phase);
void MenuSlotHandlerReset0040948F(int32_t phase);
void MenuSlotHandlerReset0041576B(int32_t phase);
void MenuSlotHandlerReset00415803(int32_t phase);
void ResetEffectsState(void);
void StepIfActive0041A8AB(void);
void AllocMapBuffer300000(void);
void FreeMapBuffer300000(void);
void AllocMapBuffer400000(void);
void FreeMapBuffer400000(void);
void FreeBufferD17EC8(void);
void FreeBuffer5FED98(void);
void SetVarD1193C(int32_t v);
void CallIf424A02(int32_t a, int32_t b);
void CallIfD14EE4(void);
void LoadShort3FromPtr(const int16_t* p);
void StopTimer4086EA(void);
void InitMapState4D3426(void);
void DrainStackC200F(void);
void FillOnes4EF997(uint8_t* p);
void ReleaseSlot4A2C5B(int32_t idx);
void TickTimer4F5D67(void);
