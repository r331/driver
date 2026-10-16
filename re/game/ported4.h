/* Партия v0.39: обработчики пунктов меню (phase 0 — пометить, 2 — вызвать), освобождение буферов, мелкие функции. */
#pragma once
#include "menugfx.h"
#include "menutab.h"
#include "gvar.h"
#include "engine.h"
#include "unported.h"
#define D_00549f8c GAME_VAR(uint8_t, D_00549f8c, 0x00549f8c)
#ifndef RE_HOOK_BUILD
#pragma push_macro("D_00549f8c") /*gvi*/
#undef D_00549f8c /*gvi*/
extern uint8_t D_00549f8c;
#pragma pop_macro("D_00549f8c") /*gvi*/
#endif
#define D_00549f9c GAME_VAR(uint8_t, D_00549f9c, 0x00549f9c)
#ifndef RE_HOOK_BUILD
#pragma push_macro("D_00549f9c") /*gvi*/
#undef D_00549f9c /*gvi*/
extern uint8_t D_00549f9c;
#pragma pop_macro("D_00549f9c") /*gvi*/
#endif
#define D_00549fdc GAME_VAR(uint8_t, D_00549fdc, 0x00549fdc)
#ifndef RE_HOOK_BUILD
#pragma push_macro("D_00549fdc") /*gvi*/
#undef D_00549fdc /*gvi*/
extern uint8_t D_00549fdc;
#pragma pop_macro("D_00549fdc") /*gvi*/
#endif
#define D_00549fec GAME_VAR(uint8_t, D_00549fec, 0x00549fec)
#ifndef RE_HOOK_BUILD
#pragma push_macro("D_00549fec") /*gvi*/
#undef D_00549fec /*gvi*/
extern uint8_t D_00549fec;
#pragma pop_macro("D_00549fec") /*gvi*/
#endif
#define D_0054a144 GAME_VAR(int32_t, D_0054a144, 0x0054a144)
#ifndef RE_HOOK_BUILD
#pragma push_macro("D_0054a144") /*gvi*/
#undef D_0054a144 /*gvi*/
extern int32_t D_0054a144;
#pragma pop_macro("D_0054a144") /*gvi*/
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
#pragma push_macro("D_0054c044") /*gvi*/
#undef D_0054c044 /*gvi*/
extern uint8_t D_0054c044;
#pragma pop_macro("D_0054c044") /*gvi*/
#endif
#define D_0054c054 GAME_VAR(uint8_t, D_0054c054, 0x0054c054)
#ifndef RE_HOOK_BUILD
#pragma push_macro("D_0054c054") /*gvi*/
#undef D_0054c054 /*gvi*/
extern uint8_t D_0054c054;
#pragma pop_macro("D_0054c054") /*gvi*/
#endif
#define D_0054c064 GAME_VAR(uint8_t, D_0054c064, 0x0054c064)
#ifndef RE_HOOK_BUILD
#pragma push_macro("D_0054c064") /*gvi*/
#undef D_0054c064 /*gvi*/
extern uint8_t D_0054c064;
#pragma pop_macro("D_0054c064") /*gvi*/
#endif
#define D_0054c074 GAME_VAR(uint8_t, D_0054c074, 0x0054c074)
#ifndef RE_HOOK_BUILD
#pragma push_macro("D_0054c074") /*gvi*/
#undef D_0054c074 /*gvi*/
extern uint8_t D_0054c074;
#pragma pop_macro("D_0054c074") /*gvi*/
#endif
#define D_0054c084 GAME_VAR(uint8_t, D_0054c084, 0x0054c084)
#ifndef RE_HOOK_BUILD
#pragma push_macro("D_0054c084") /*gvi*/
#undef D_0054c084 /*gvi*/
extern uint8_t D_0054c084;
#pragma pop_macro("D_0054c084") /*gvi*/
#endif
#define D_0054c094 GAME_VAR(uint8_t, D_0054c094, 0x0054c094)
#ifndef RE_HOOK_BUILD
#pragma push_macro("D_0054c094") /*gvi*/
#undef D_0054c094 /*gvi*/
extern uint8_t D_0054c094;
#pragma pop_macro("D_0054c094") /*gvi*/
#endif
#define D_0054c0a4 GAME_VAR(uint8_t, D_0054c0a4, 0x0054c0a4)
#ifndef RE_HOOK_BUILD
#pragma push_macro("D_0054c0a4") /*gvi*/
#undef D_0054c0a4 /*gvi*/
extern uint8_t D_0054c0a4;
#pragma pop_macro("D_0054c0a4") /*gvi*/
#endif
#define D_0054c0b4 GAME_VAR(uint8_t, D_0054c0b4, 0x0054c0b4)
#ifndef RE_HOOK_BUILD
#pragma push_macro("D_0054c0b4") /*gvi*/
#undef D_0054c0b4 /*gvi*/
extern uint8_t D_0054c0b4;
#pragma pop_macro("D_0054c0b4") /*gvi*/
#endif
#define D_0054c0c4 GAME_VAR(uint8_t, D_0054c0c4, 0x0054c0c4)
#ifndef RE_HOOK_BUILD
#pragma push_macro("D_0054c0c4") /*gvi*/
#undef D_0054c0c4 /*gvi*/
extern uint8_t D_0054c0c4;
#pragma pop_macro("D_0054c0c4") /*gvi*/
#endif
#define D_0054c0d4 GAME_VAR(uint8_t, D_0054c0d4, 0x0054c0d4)
#ifndef RE_HOOK_BUILD
#pragma push_macro("D_0054c0d4") /*gvi*/
#undef D_0054c0d4 /*gvi*/
extern uint8_t D_0054c0d4;
#pragma pop_macro("D_0054c0d4") /*gvi*/
#endif
#define D_0054c0e4 GAME_VAR(uint8_t, D_0054c0e4, 0x0054c0e4)
#ifndef RE_HOOK_BUILD
#pragma push_macro("D_0054c0e4") /*gvi*/
#undef D_0054c0e4 /*gvi*/
extern uint8_t D_0054c0e4;
#pragma pop_macro("D_0054c0e4") /*gvi*/
#endif
#define D_0054c0f4 GAME_VAR(uint8_t, D_0054c0f4, 0x0054c0f4)
#ifndef RE_HOOK_BUILD
#pragma push_macro("D_0054c0f4") /*gvi*/
#undef D_0054c0f4 /*gvi*/
extern uint8_t D_0054c0f4;
#pragma pop_macro("D_0054c0f4") /*gvi*/
#endif
#define D_0054c104 GAME_VAR(uint8_t, D_0054c104, 0x0054c104)
#ifndef RE_HOOK_BUILD
#pragma push_macro("D_0054c104") /*gvi*/
#undef D_0054c104 /*gvi*/
extern uint8_t D_0054c104;
#pragma pop_macro("D_0054c104") /*gvi*/
#endif
#define D_0054c114 GAME_VAR(uint8_t, D_0054c114, 0x0054c114)
#ifndef RE_HOOK_BUILD
#pragma push_macro("D_0054c114") /*gvi*/
#undef D_0054c114 /*gvi*/
extern uint8_t D_0054c114;
#pragma pop_macro("D_0054c114") /*gvi*/
#endif
#define D_0054c124 GAME_VAR(uint8_t, D_0054c124, 0x0054c124)
#ifndef RE_HOOK_BUILD
#pragma push_macro("D_0054c124") /*gvi*/
#undef D_0054c124 /*gvi*/
extern uint8_t D_0054c124;
#pragma pop_macro("D_0054c124") /*gvi*/
#endif
#define D_0054c134 GAME_VAR(uint8_t, D_0054c134, 0x0054c134)
#ifndef RE_HOOK_BUILD
#pragma push_macro("D_0054c134") /*gvi*/
#undef D_0054c134 /*gvi*/
extern uint8_t D_0054c134;
#pragma pop_macro("D_0054c134") /*gvi*/
#endif
#define D_0054c144 GAME_VAR(uint8_t, D_0054c144, 0x0054c144)
#ifndef RE_HOOK_BUILD
#pragma push_macro("D_0054c144") /*gvi*/
#undef D_0054c144 /*gvi*/
extern uint8_t D_0054c144;
#pragma pop_macro("D_0054c144") /*gvi*/
#endif
#define D_0054c154 GAME_VAR(uint8_t, D_0054c154, 0x0054c154)
#ifndef RE_HOOK_BUILD
#pragma push_macro("D_0054c154") /*gvi*/
#undef D_0054c154 /*gvi*/
extern uint8_t D_0054c154;
#pragma pop_macro("D_0054c154") /*gvi*/
#endif
#define D_0054c164 GAME_VAR(uint8_t, D_0054c164, 0x0054c164)
#ifndef RE_HOOK_BUILD
#pragma push_macro("D_0054c164") /*gvi*/
#undef D_0054c164 /*gvi*/
extern uint8_t D_0054c164;
#pragma pop_macro("D_0054c164") /*gvi*/
#endif
#define D_0054c174 GAME_VAR(uint8_t, D_0054c174, 0x0054c174)
#ifndef RE_HOOK_BUILD
#pragma push_macro("D_0054c174") /*gvi*/
#undef D_0054c174 /*gvi*/
extern uint8_t D_0054c174;
#pragma pop_macro("D_0054c174") /*gvi*/
#endif
#define D_0054c184 GAME_VAR(uint8_t, D_0054c184, 0x0054c184)
#ifndef RE_HOOK_BUILD
#pragma push_macro("D_0054c184") /*gvi*/
#undef D_0054c184 /*gvi*/
extern uint8_t D_0054c184;
#pragma pop_macro("D_0054c184") /*gvi*/
#endif
#define D_0054c194 GAME_VAR(uint8_t, D_0054c194, 0x0054c194)
#ifndef RE_HOOK_BUILD
#pragma push_macro("D_0054c194") /*gvi*/
#undef D_0054c194 /*gvi*/
extern uint8_t D_0054c194;
#pragma pop_macro("D_0054c194") /*gvi*/
#endif
#define D_0054c1a4 GAME_VAR(uint8_t, D_0054c1a4, 0x0054c1a4)
#ifndef RE_HOOK_BUILD
#pragma push_macro("D_0054c1a4") /*gvi*/
#undef D_0054c1a4 /*gvi*/
extern uint8_t D_0054c1a4;
#pragma pop_macro("D_0054c1a4") /*gvi*/
#endif
#define D_0054c1b4 GAME_VAR(uint8_t, D_0054c1b4, 0x0054c1b4)
#ifndef RE_HOOK_BUILD
#pragma push_macro("D_0054c1b4") /*gvi*/
#undef D_0054c1b4 /*gvi*/
extern uint8_t D_0054c1b4;
#pragma pop_macro("D_0054c1b4") /*gvi*/
#endif
#define D_0054c364 GAME_VAR(uint8_t, D_0054c364, 0x0054c364)
#ifndef RE_HOOK_BUILD
#pragma push_macro("D_0054c364") /*gvi*/
#undef D_0054c364 /*gvi*/
extern uint8_t D_0054c364;
#pragma pop_macro("D_0054c364") /*gvi*/
#endif
#define D_0054c374 GAME_VAR(uint8_t, D_0054c374, 0x0054c374)
#ifndef RE_HOOK_BUILD
#pragma push_macro("D_0054c374") /*gvi*/
#undef D_0054c374 /*gvi*/
extern uint8_t D_0054c374;
#pragma pop_macro("D_0054c374") /*gvi*/
#endif
#define D_0054c384 GAME_VAR(uint8_t, D_0054c384, 0x0054c384)
#ifndef RE_HOOK_BUILD
#pragma push_macro("D_0054c384") /*gvi*/
#undef D_0054c384 /*gvi*/
extern uint8_t D_0054c384;
#pragma pop_macro("D_0054c384") /*gvi*/
#endif
#define D_0054c394 GAME_VAR(uint8_t, D_0054c394, 0x0054c394)
#ifndef RE_HOOK_BUILD
#pragma push_macro("D_0054c394") /*gvi*/
#undef D_0054c394 /*gvi*/
extern uint8_t D_0054c394;
#pragma pop_macro("D_0054c394") /*gvi*/
#endif
#define D_0054c3a4 GAME_VAR(uint8_t, D_0054c3a4, 0x0054c3a4)
#ifndef RE_HOOK_BUILD
#pragma push_macro("D_0054c3a4") /*gvi*/
#undef D_0054c3a4 /*gvi*/
extern uint8_t D_0054c3a4;
#pragma pop_macro("D_0054c3a4") /*gvi*/
#endif
#define D_0054c3b4 GAME_VAR(uint8_t, D_0054c3b4, 0x0054c3b4)
#ifndef RE_HOOK_BUILD
#pragma push_macro("D_0054c3b4") /*gvi*/
#undef D_0054c3b4 /*gvi*/
extern uint8_t D_0054c3b4;
#pragma pop_macro("D_0054c3b4") /*gvi*/
#endif
#define D_0054c3c4 GAME_VAR(uint8_t, D_0054c3c4, 0x0054c3c4)
#ifndef RE_HOOK_BUILD
#pragma push_macro("D_0054c3c4") /*gvi*/
#undef D_0054c3c4 /*gvi*/
extern uint8_t D_0054c3c4;
#pragma pop_macro("D_0054c3c4") /*gvi*/
#endif
#define D_0054c3d4 GAME_VAR(uint8_t, D_0054c3d4, 0x0054c3d4)
#ifndef RE_HOOK_BUILD
#pragma push_macro("D_0054c3d4") /*gvi*/
#undef D_0054c3d4 /*gvi*/
extern uint8_t D_0054c3d4;
#pragma pop_macro("D_0054c3d4") /*gvi*/
#endif
#define D_0054c3e4 GAME_VAR(uint8_t, D_0054c3e4, 0x0054c3e4)
#ifndef RE_HOOK_BUILD
#pragma push_macro("D_0054c3e4") /*gvi*/
#undef D_0054c3e4 /*gvi*/
extern uint8_t D_0054c3e4;
#pragma pop_macro("D_0054c3e4") /*gvi*/
#endif
#define D_0054c3f4 GAME_VAR(uint8_t, D_0054c3f4, 0x0054c3f4)
#ifndef RE_HOOK_BUILD
#pragma push_macro("D_0054c3f4") /*gvi*/
#undef D_0054c3f4 /*gvi*/
extern uint8_t D_0054c3f4;
#pragma pop_macro("D_0054c3f4") /*gvi*/
#endif
#define D_0054c404 GAME_VAR(uint8_t, D_0054c404, 0x0054c404)
#ifndef RE_HOOK_BUILD
#pragma push_macro("D_0054c404") /*gvi*/
#undef D_0054c404 /*gvi*/
extern uint8_t D_0054c404;
#pragma pop_macro("D_0054c404") /*gvi*/
#endif
#define D_0054c414 GAME_VAR(uint8_t, D_0054c414, 0x0054c414)
#ifndef RE_HOOK_BUILD
#pragma push_macro("D_0054c414") /*gvi*/
#undef D_0054c414 /*gvi*/
extern uint8_t D_0054c414;
#pragma pop_macro("D_0054c414") /*gvi*/
#endif
#define D_0054c424 GAME_VAR(uint8_t, D_0054c424, 0x0054c424)
#ifndef RE_HOOK_BUILD
#pragma push_macro("D_0054c424") /*gvi*/
#undef D_0054c424 /*gvi*/
extern uint8_t D_0054c424;
#pragma pop_macro("D_0054c424") /*gvi*/
#endif
#define D_0054c434 GAME_VAR(uint8_t, D_0054c434, 0x0054c434)
#ifndef RE_HOOK_BUILD
#pragma push_macro("D_0054c434") /*gvi*/
#undef D_0054c434 /*gvi*/
extern uint8_t D_0054c434;
#pragma pop_macro("D_0054c434") /*gvi*/
#endif
#define D_0054c444 GAME_VAR(uint8_t, D_0054c444, 0x0054c444)
#ifndef RE_HOOK_BUILD
#pragma push_macro("D_0054c444") /*gvi*/
#undef D_0054c444 /*gvi*/
extern uint8_t D_0054c444;
#pragma pop_macro("D_0054c444") /*gvi*/
#endif
#define D_0054c454 GAME_VAR(uint8_t, D_0054c454, 0x0054c454)
#ifndef RE_HOOK_BUILD
#pragma push_macro("D_0054c454") /*gvi*/
#undef D_0054c454 /*gvi*/
extern uint8_t D_0054c454;
#pragma pop_macro("D_0054c454") /*gvi*/
#endif
#define D_0054c464 GAME_VAR(uint8_t, D_0054c464, 0x0054c464)
#ifndef RE_HOOK_BUILD
#pragma push_macro("D_0054c464") /*gvi*/
#undef D_0054c464 /*gvi*/
extern uint8_t D_0054c464;
#pragma pop_macro("D_0054c464") /*gvi*/
#endif
#define D_0054c474 GAME_VAR(uint8_t, D_0054c474, 0x0054c474)
#ifndef RE_HOOK_BUILD
#pragma push_macro("D_0054c474") /*gvi*/
#undef D_0054c474 /*gvi*/
extern uint8_t D_0054c474;
#pragma pop_macro("D_0054c474") /*gvi*/
#endif
#define D_0054c484 GAME_VAR(uint8_t, D_0054c484, 0x0054c484)
#ifndef RE_HOOK_BUILD
#pragma push_macro("D_0054c484") /*gvi*/
#undef D_0054c484 /*gvi*/
extern uint8_t D_0054c484;
#pragma pop_macro("D_0054c484") /*gvi*/
#endif
#define D_0054c494 GAME_VAR(uint8_t, D_0054c494, 0x0054c494)
#ifndef RE_HOOK_BUILD
#pragma push_macro("D_0054c494") /*gvi*/
#undef D_0054c494 /*gvi*/
extern uint8_t D_0054c494;
#pragma pop_macro("D_0054c494") /*gvi*/
#endif
#define D_0054c4a4 GAME_VAR(uint8_t, D_0054c4a4, 0x0054c4a4)
#ifndef RE_HOOK_BUILD
#pragma push_macro("D_0054c4a4") /*gvi*/
#undef D_0054c4a4 /*gvi*/
extern uint8_t D_0054c4a4;
#pragma pop_macro("D_0054c4a4") /*gvi*/
#endif
#define D_0054c4b4 GAME_VAR(uint8_t, D_0054c4b4, 0x0054c4b4)
#ifndef RE_HOOK_BUILD
#pragma push_macro("D_0054c4b4") /*gvi*/
#undef D_0054c4b4 /*gvi*/
extern uint8_t D_0054c4b4;
#pragma pop_macro("D_0054c4b4") /*gvi*/
#endif
#define D_0054c4c4 GAME_VAR(uint8_t, D_0054c4c4, 0x0054c4c4)
#ifndef RE_HOOK_BUILD
#pragma push_macro("D_0054c4c4") /*gvi*/
#undef D_0054c4c4 /*gvi*/
extern uint8_t D_0054c4c4;
#pragma pop_macro("D_0054c4c4") /*gvi*/
#endif
#define D_0054c4d4 GAME_VAR(uint8_t, D_0054c4d4, 0x0054c4d4)
#ifndef RE_HOOK_BUILD
#pragma push_macro("D_0054c4d4") /*gvi*/
#undef D_0054c4d4 /*gvi*/
extern uint8_t D_0054c4d4;
#pragma pop_macro("D_0054c4d4") /*gvi*/
#endif
#define D_0054c4e4 GAME_VAR(uint8_t, D_0054c4e4, 0x0054c4e4)
#ifndef RE_HOOK_BUILD
#pragma push_macro("D_0054c4e4") /*gvi*/
#undef D_0054c4e4 /*gvi*/
extern uint8_t D_0054c4e4;
#pragma pop_macro("D_0054c4e4") /*gvi*/
#endif
#define D_0054c4f4 GAME_VAR(uint8_t, D_0054c4f4, 0x0054c4f4)
#ifndef RE_HOOK_BUILD
#pragma push_macro("D_0054c4f4") /*gvi*/
#undef D_0054c4f4 /*gvi*/
extern uint8_t D_0054c4f4;
#pragma pop_macro("D_0054c4f4") /*gvi*/
#endif
#define D_0054c504 GAME_VAR(uint8_t, D_0054c504, 0x0054c504)
#ifndef RE_HOOK_BUILD
#pragma push_macro("D_0054c504") /*gvi*/
#undef D_0054c504 /*gvi*/
extern uint8_t D_0054c504;
#pragma pop_macro("D_0054c504") /*gvi*/
#endif
#define D_0054c514 GAME_VAR(uint8_t, D_0054c514, 0x0054c514)
#ifndef RE_HOOK_BUILD
#pragma push_macro("D_0054c514") /*gvi*/
#undef D_0054c514 /*gvi*/
extern uint8_t D_0054c514;
#pragma pop_macro("D_0054c514") /*gvi*/
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
#pragma push_macro("D_005d577c") /*gvi*/
#undef D_005d577c /*gvi*/
extern int32_t D_005d577c;
#pragma pop_macro("D_005d577c") /*gvi*/
#endif
#define D_005f7e4c GAME_VAR(int32_t, D_005f7e4c, 0x005f7e4c)
#ifndef RE_HOOK_BUILD
#pragma push_macro("D_005f7e4c") /*gvi*/
#undef D_005f7e4c /*gvi*/
extern int32_t D_005f7e4c;
#pragma pop_macro("D_005f7e4c") /*gvi*/
#endif
#define D_005fea98 GAME_VAR(int32_t, D_005fea98, 0x005fea98)
#ifndef RE_HOOK_BUILD
#pragma push_macro("D_005fea98") /*gvi*/
#undef D_005fea98 /*gvi*/
extern int32_t D_005fea98;
#pragma pop_macro("D_005fea98") /*gvi*/
#endif
#define D_005fed98 GAME_VAR(void*, D_005fed98, 0x005fed98)
#ifndef RE_HOOK_BUILD
extern void* D_005fed98;
#endif
#define D_005feda0 GAME_VAR(int32_t, D_005feda0, 0x005feda0)
#ifndef RE_HOOK_BUILD
#pragma push_macro("D_005feda0") /*gvi*/
#undef D_005feda0 /*gvi*/
extern int32_t D_005feda0;
#pragma pop_macro("D_005feda0") /*gvi*/
#endif
#define D_00b1c0d4 GAME_VAR(int32_t, G00B1C0D4, 0x00b1c0d4)   /* v2.00: один native-объект с G00B1C0D4 (uihandlers3) */
#ifndef RE_HOOK_BUILD
#pragma push_macro("G00B1C0D4") /*gvi*/
#undef G00B1C0D4 /*gvi*/
extern int32_t G00B1C0D4;   /* v2.03: объявление объекта псевдонима D_00b1c0d4 */
#pragma pop_macro("G00B1C0D4") /*gvi*/
#endif
#define D_00b1c0d8 GAME_VAR(int32_t, G00B1C0D8, 0x00b1c0d8)   /* v2.00: один native-объект с G00B1C0D8 */
#ifndef RE_HOOK_BUILD
#pragma push_macro("G00B1C0D8") /*gvi*/
#undef G00B1C0D8 /*gvi*/
extern int32_t G00B1C0D8;   /* v2.03: объявление объекта псевдонима D_00b1c0d8 */
#pragma pop_macro("G00B1C0D8") /*gvi*/
#endif
#define D_00b87e30 GAME_VAR(int32_t, D_00b87e30, 0x00b87e30)
#ifndef RE_HOOK_BUILD
#pragma push_macro("D_00b87e30") /*gvi*/
#undef D_00b87e30 /*gvi*/
extern int32_t D_00b87e30;
#pragma pop_macro("D_00b87e30") /*gvi*/
#endif
#define D_00b93e48 GAME_VAR(int32_t, D_00b93e48, 0x00b93e48)
#ifndef RE_HOOK_BUILD
#pragma push_macro("D_00b93e48") /*gvi*/
#undef D_00b93e48 /*gvi*/
extern int32_t D_00b93e48;
#pragma pop_macro("D_00b93e48") /*gvi*/
#endif
#define D_00b93e4c GAME_VAR(int32_t, D_00b93e4c, 0x00b93e4c)
#ifndef RE_HOOK_BUILD
#pragma push_macro("D_00b93e4c") /*gvi*/
#undef D_00b93e4c /*gvi*/
extern int32_t D_00b93e4c;
#pragma pop_macro("D_00b93e4c") /*gvi*/
#endif
#define D_00b93e50 GAME_VAR(int32_t, D_00b93e50, 0x00b93e50)
#ifndef RE_HOOK_BUILD
#pragma push_macro("D_00b93e50") /*gvi*/
#undef D_00b93e50 /*gvi*/
extern int32_t D_00b93e50;
#pragma pop_macro("D_00b93e50") /*gvi*/
#endif
#define D_00c80ca0 GAME_VAR(int32_t, D_00c80ca0, 0x00c80ca0)
#ifndef RE_HOOK_BUILD
#pragma push_macro("D_00c80ca0") /*gvi*/
#undef D_00c80ca0 /*gvi*/
extern int32_t D_00c80ca0;
#pragma pop_macro("D_00c80ca0") /*gvi*/
#endif
#define D_00c81494 GAME_VAR(int32_t, D_00c81494, 0x00c81494)
#ifndef RE_HOOK_BUILD
#pragma push_macro("D_00c81494") /*gvi*/
#undef D_00c81494 /*gvi*/
extern int32_t D_00c81494;
#pragma pop_macro("D_00c81494") /*gvi*/
#endif
#define D_00c98ed0 GAME_VAR(void*, D_00c98ed0, 0x00c98ed0)
#ifndef RE_HOOK_BUILD
extern void* D_00c98ed0;
#endif
#define D_00d00204 GAME_VAR(int32_t, D_00d00204, 0x00d00204)
#ifndef RE_HOOK_BUILD
#pragma push_macro("D_00d00204") /*gvi*/
#undef D_00d00204 /*gvi*/
extern int32_t D_00d00204;
#pragma pop_macro("D_00d00204") /*gvi*/
#endif
#define D_00d00230 GAME_VAR(void*, D_00d00230, 0x00d00230)
#ifndef RE_HOOK_BUILD
extern void* D_00d00230;
#endif
#define D_00d1193c GAME_VAR(int32_t, D_00d1193c, 0x00d1193c)
#ifndef RE_HOOK_BUILD
#pragma push_macro("D_00d1193c") /*gvi*/
#undef D_00d1193c /*gvi*/
extern int32_t D_00d1193c;
#pragma pop_macro("D_00d1193c") /*gvi*/
#endif
#define D_00d14ee0 GAME_VAR(int32_t, D_00d14ee0, 0x00d14ee0)
#ifndef RE_HOOK_BUILD
#pragma push_macro("D_00d14ee0") /*gvi*/
#undef D_00d14ee0 /*gvi*/
extern int32_t D_00d14ee0;
#pragma pop_macro("D_00d14ee0") /*gvi*/
#endif
#define D_00d14ee4 GAME_VAR(int32_t, D_00d14ee4, 0x00d14ee4)
#ifndef RE_HOOK_BUILD
#pragma push_macro("D_00d14ee4") /*gvi*/
#undef D_00d14ee4 /*gvi*/
extern int32_t D_00d14ee4;
#pragma pop_macro("D_00d14ee4") /*gvi*/
#endif
#define D_00d17ec8 GAME_VAR(void*, D_00d17ec8, 0x00d17ec8)
#ifndef RE_HOOK_BUILD
extern void* D_00d17ec8;
#endif
#define D_00dbb450 GAME_VAR(int32_t, D_00dbb450, 0x00dbb450)
#ifndef RE_HOOK_BUILD
#pragma push_macro("D_00dbb450") /*gvi*/
#undef D_00dbb450 /*gvi*/
extern int32_t D_00dbb450;
#pragma pop_macro("D_00dbb450") /*gvi*/
#endif
typedef int32_t int32_t_arr_010de120[0x4000];
#define D_010de120 GAME_VAR(int32_t_arr_010de120, D_010de120, 0x010de120)
#ifndef RE_HOOK_BUILD
#pragma push_macro("D_010de120") /*gvi*/
#undef D_010de120 /*gvi*/
extern int32_t_arr_010de120 D_010de120;
#pragma pop_macro("D_010de120") /*gvi*/
#endif
#define D_01134528 GAME_VAR(int32_t, D_01134528, 0x01134528)
#ifndef RE_HOOK_BUILD
#pragma push_macro("D_01134528") /*gvi*/
#undef D_01134528 /*gvi*/
extern int32_t D_01134528;
#pragma pop_macro("D_01134528") /*gvi*/
#endif
typedef int32_t int32_t_arr_01134554[0x4000];
#define D_01134554 GAME_VAR(int32_t_arr_01134554, D_01134554, 0x01134554)
#ifndef RE_HOOK_BUILD
#pragma push_macro("D_01134554") /*gvi*/
#undef D_01134554 /*gvi*/
extern int32_t_arr_01134554 D_01134554;
#pragma pop_macro("D_01134554") /*gvi*/
#endif
#define D_01134ea0 GAME_VAR(int32_t, D_01134ea0, 0x01134ea0)
#ifndef RE_HOOK_BUILD
#pragma push_macro("D_01134ea0") /*gvi*/
#undef D_01134ea0 /*gvi*/
extern int32_t D_01134ea0;
#pragma pop_macro("D_01134ea0") /*gvi*/
#endif
typedef int32_t int32_t_arr_01134ec0[0x4000];
#define D_01134ec0 GAME_VAR(int32_t_arr_01134ec0, D_01134ec0, 0x01134ec0)
#ifndef RE_HOOK_BUILD
#pragma push_macro("D_01134ec0") /*gvi*/
#undef D_01134ec0 /*gvi*/
extern int32_t_arr_01134ec0 D_01134ec0;
#pragma pop_macro("D_01134ec0") /*gvi*/
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
/* gvar-img v2.03 begin (tools/gen_gvar_img.py) */
#if !defined(RE_HOOK_BUILD) && !defined(RE_GVAR_PLAIN)
#undef D_00549f8c
#define D_00549f8c (*(uint8_t *)re_gvar(0x00549f8cu, sizeof(uint8_t), (void *)&D_00549f8c))
#undef D_00549f9c
#define D_00549f9c (*(uint8_t *)re_gvar(0x00549f9cu, sizeof(uint8_t), (void *)&D_00549f9c))
#undef D_00549fdc
#define D_00549fdc (*(uint8_t *)re_gvar(0x00549fdcu, sizeof(uint8_t), (void *)&D_00549fdc))
#undef D_00549fec
#define D_00549fec (*(uint8_t *)re_gvar(0x00549fecu, sizeof(uint8_t), (void *)&D_00549fec))
#undef D_0054a144
#define D_0054a144 (*(int32_t *)re_gvar(0x0054a144u, sizeof(int32_t), (void *)&D_0054a144))
#undef D_0054c044
#define D_0054c044 (*(uint8_t *)re_gvar(0x0054c044u, sizeof(uint8_t), (void *)&D_0054c044))
#undef D_0054c054
#define D_0054c054 (*(uint8_t *)re_gvar(0x0054c054u, sizeof(uint8_t), (void *)&D_0054c054))
#undef D_0054c064
#define D_0054c064 (*(uint8_t *)re_gvar(0x0054c064u, sizeof(uint8_t), (void *)&D_0054c064))
#undef D_0054c074
#define D_0054c074 (*(uint8_t *)re_gvar(0x0054c074u, sizeof(uint8_t), (void *)&D_0054c074))
#undef D_0054c084
#define D_0054c084 (*(uint8_t *)re_gvar(0x0054c084u, sizeof(uint8_t), (void *)&D_0054c084))
#undef D_0054c094
#define D_0054c094 (*(uint8_t *)re_gvar(0x0054c094u, sizeof(uint8_t), (void *)&D_0054c094))
#undef D_0054c0a4
#define D_0054c0a4 (*(uint8_t *)re_gvar(0x0054c0a4u, sizeof(uint8_t), (void *)&D_0054c0a4))
#undef D_0054c0b4
#define D_0054c0b4 (*(uint8_t *)re_gvar(0x0054c0b4u, sizeof(uint8_t), (void *)&D_0054c0b4))
#undef D_0054c0c4
#define D_0054c0c4 (*(uint8_t *)re_gvar(0x0054c0c4u, sizeof(uint8_t), (void *)&D_0054c0c4))
#undef D_0054c0d4
#define D_0054c0d4 (*(uint8_t *)re_gvar(0x0054c0d4u, sizeof(uint8_t), (void *)&D_0054c0d4))
#undef D_0054c0e4
#define D_0054c0e4 (*(uint8_t *)re_gvar(0x0054c0e4u, sizeof(uint8_t), (void *)&D_0054c0e4))
#undef D_0054c0f4
#define D_0054c0f4 (*(uint8_t *)re_gvar(0x0054c0f4u, sizeof(uint8_t), (void *)&D_0054c0f4))
#undef D_0054c104
#define D_0054c104 (*(uint8_t *)re_gvar(0x0054c104u, sizeof(uint8_t), (void *)&D_0054c104))
#undef D_0054c114
#define D_0054c114 (*(uint8_t *)re_gvar(0x0054c114u, sizeof(uint8_t), (void *)&D_0054c114))
#undef D_0054c124
#define D_0054c124 (*(uint8_t *)re_gvar(0x0054c124u, sizeof(uint8_t), (void *)&D_0054c124))
#undef D_0054c134
#define D_0054c134 (*(uint8_t *)re_gvar(0x0054c134u, sizeof(uint8_t), (void *)&D_0054c134))
#undef D_0054c144
#define D_0054c144 (*(uint8_t *)re_gvar(0x0054c144u, sizeof(uint8_t), (void *)&D_0054c144))
#undef D_0054c154
#define D_0054c154 (*(uint8_t *)re_gvar(0x0054c154u, sizeof(uint8_t), (void *)&D_0054c154))
#undef D_0054c164
#define D_0054c164 (*(uint8_t *)re_gvar(0x0054c164u, sizeof(uint8_t), (void *)&D_0054c164))
#undef D_0054c174
#define D_0054c174 (*(uint8_t *)re_gvar(0x0054c174u, sizeof(uint8_t), (void *)&D_0054c174))
#undef D_0054c184
#define D_0054c184 (*(uint8_t *)re_gvar(0x0054c184u, sizeof(uint8_t), (void *)&D_0054c184))
#undef D_0054c194
#define D_0054c194 (*(uint8_t *)re_gvar(0x0054c194u, sizeof(uint8_t), (void *)&D_0054c194))
#undef D_0054c1a4
#define D_0054c1a4 (*(uint8_t *)re_gvar(0x0054c1a4u, sizeof(uint8_t), (void *)&D_0054c1a4))
#undef D_0054c1b4
#define D_0054c1b4 (*(uint8_t *)re_gvar(0x0054c1b4u, sizeof(uint8_t), (void *)&D_0054c1b4))
#undef D_0054c364
#define D_0054c364 (*(uint8_t *)re_gvar(0x0054c364u, sizeof(uint8_t), (void *)&D_0054c364))
#undef D_0054c374
#define D_0054c374 (*(uint8_t *)re_gvar(0x0054c374u, sizeof(uint8_t), (void *)&D_0054c374))
#undef D_0054c384
#define D_0054c384 (*(uint8_t *)re_gvar(0x0054c384u, sizeof(uint8_t), (void *)&D_0054c384))
#undef D_0054c394
#define D_0054c394 (*(uint8_t *)re_gvar(0x0054c394u, sizeof(uint8_t), (void *)&D_0054c394))
#undef D_0054c3a4
#define D_0054c3a4 (*(uint8_t *)re_gvar(0x0054c3a4u, sizeof(uint8_t), (void *)&D_0054c3a4))
#undef D_0054c3b4
#define D_0054c3b4 (*(uint8_t *)re_gvar(0x0054c3b4u, sizeof(uint8_t), (void *)&D_0054c3b4))
#undef D_0054c3c4
#define D_0054c3c4 (*(uint8_t *)re_gvar(0x0054c3c4u, sizeof(uint8_t), (void *)&D_0054c3c4))
#undef D_0054c3d4
#define D_0054c3d4 (*(uint8_t *)re_gvar(0x0054c3d4u, sizeof(uint8_t), (void *)&D_0054c3d4))
#undef D_0054c3e4
#define D_0054c3e4 (*(uint8_t *)re_gvar(0x0054c3e4u, sizeof(uint8_t), (void *)&D_0054c3e4))
#undef D_0054c3f4
#define D_0054c3f4 (*(uint8_t *)re_gvar(0x0054c3f4u, sizeof(uint8_t), (void *)&D_0054c3f4))
#undef D_0054c404
#define D_0054c404 (*(uint8_t *)re_gvar(0x0054c404u, sizeof(uint8_t), (void *)&D_0054c404))
#undef D_0054c414
#define D_0054c414 (*(uint8_t *)re_gvar(0x0054c414u, sizeof(uint8_t), (void *)&D_0054c414))
#undef D_0054c424
#define D_0054c424 (*(uint8_t *)re_gvar(0x0054c424u, sizeof(uint8_t), (void *)&D_0054c424))
#undef D_0054c434
#define D_0054c434 (*(uint8_t *)re_gvar(0x0054c434u, sizeof(uint8_t), (void *)&D_0054c434))
#undef D_0054c444
#define D_0054c444 (*(uint8_t *)re_gvar(0x0054c444u, sizeof(uint8_t), (void *)&D_0054c444))
#undef D_0054c454
#define D_0054c454 (*(uint8_t *)re_gvar(0x0054c454u, sizeof(uint8_t), (void *)&D_0054c454))
#undef D_0054c464
#define D_0054c464 (*(uint8_t *)re_gvar(0x0054c464u, sizeof(uint8_t), (void *)&D_0054c464))
#undef D_0054c474
#define D_0054c474 (*(uint8_t *)re_gvar(0x0054c474u, sizeof(uint8_t), (void *)&D_0054c474))
#undef D_0054c484
#define D_0054c484 (*(uint8_t *)re_gvar(0x0054c484u, sizeof(uint8_t), (void *)&D_0054c484))
#undef D_0054c494
#define D_0054c494 (*(uint8_t *)re_gvar(0x0054c494u, sizeof(uint8_t), (void *)&D_0054c494))
#undef D_0054c4a4
#define D_0054c4a4 (*(uint8_t *)re_gvar(0x0054c4a4u, sizeof(uint8_t), (void *)&D_0054c4a4))
#undef D_0054c4b4
#define D_0054c4b4 (*(uint8_t *)re_gvar(0x0054c4b4u, sizeof(uint8_t), (void *)&D_0054c4b4))
#undef D_0054c4c4
#define D_0054c4c4 (*(uint8_t *)re_gvar(0x0054c4c4u, sizeof(uint8_t), (void *)&D_0054c4c4))
#undef D_0054c4d4
#define D_0054c4d4 (*(uint8_t *)re_gvar(0x0054c4d4u, sizeof(uint8_t), (void *)&D_0054c4d4))
#undef D_0054c4e4
#define D_0054c4e4 (*(uint8_t *)re_gvar(0x0054c4e4u, sizeof(uint8_t), (void *)&D_0054c4e4))
#undef D_0054c4f4
#define D_0054c4f4 (*(uint8_t *)re_gvar(0x0054c4f4u, sizeof(uint8_t), (void *)&D_0054c4f4))
#undef D_0054c504
#define D_0054c504 (*(uint8_t *)re_gvar(0x0054c504u, sizeof(uint8_t), (void *)&D_0054c504))
#undef D_0054c514
#define D_0054c514 (*(uint8_t *)re_gvar(0x0054c514u, sizeof(uint8_t), (void *)&D_0054c514))
#undef D_005d577c
#define D_005d577c (*(int32_t *)re_gvar(0x005d577cu, sizeof(int32_t), (void *)&D_005d577c))
#undef D_005f7e4c
#define D_005f7e4c (*(int32_t *)re_gvar(0x005f7e4cu, sizeof(int32_t), (void *)&D_005f7e4c))
#undef D_005fea98
#define D_005fea98 (*(int32_t *)re_gvar(0x005fea98u, sizeof(int32_t), (void *)&D_005fea98))
#undef D_005feda0
#define D_005feda0 (*(int32_t *)re_gvar(0x005feda0u, sizeof(int32_t), (void *)&D_005feda0))
#undef D_00b87e30
#define D_00b87e30 (*(int32_t *)re_gvar(0x00b87e30u, sizeof(int32_t), (void *)&D_00b87e30))
#undef D_00b93e48
#define D_00b93e48 (*(int32_t *)re_gvar(0x00b93e48u, sizeof(int32_t), (void *)&D_00b93e48))
#undef D_00b93e4c
#define D_00b93e4c (*(int32_t *)re_gvar(0x00b93e4cu, sizeof(int32_t), (void *)&D_00b93e4c))
#undef D_00b93e50
#define D_00b93e50 (*(int32_t *)re_gvar(0x00b93e50u, sizeof(int32_t), (void *)&D_00b93e50))
#undef D_00c80ca0
#define D_00c80ca0 (*(int32_t *)re_gvar(0x00c80ca0u, sizeof(int32_t), (void *)&D_00c80ca0))
#undef D_00c81494
#define D_00c81494 (*(int32_t *)re_gvar(0x00c81494u, sizeof(int32_t), (void *)&D_00c81494))
#undef D_00d00204
#define D_00d00204 (*(int32_t *)re_gvar(0x00d00204u, sizeof(int32_t), (void *)&D_00d00204))
#undef D_00d1193c
#define D_00d1193c (*(int32_t *)re_gvar(0x00d1193cu, sizeof(int32_t), (void *)&D_00d1193c))
#undef D_00d14ee0
#define D_00d14ee0 (*(int32_t *)re_gvar(0x00d14ee0u, sizeof(int32_t), (void *)&D_00d14ee0))
#undef D_00d14ee4
#define D_00d14ee4 (*(int32_t *)re_gvar(0x00d14ee4u, sizeof(int32_t), (void *)&D_00d14ee4))
#undef D_00dbb450
#define D_00dbb450 (*(int32_t *)re_gvar(0x00dbb450u, sizeof(int32_t), (void *)&D_00dbb450))
#undef D_010de120
#define D_010de120 (*(int32_t_arr_010de120 *)re_gvar(0x010de120u, sizeof(int32_t_arr_010de120), (void *)&D_010de120))
#undef D_01134528
#define D_01134528 (*(int32_t *)re_gvar(0x01134528u, sizeof(int32_t), (void *)&D_01134528))
#undef D_01134554
#define D_01134554 (*(int32_t_arr_01134554 *)re_gvar(0x01134554u, sizeof(int32_t_arr_01134554), (void *)&D_01134554))
#undef D_01134ea0
#define D_01134ea0 (*(int32_t *)re_gvar(0x01134ea0u, sizeof(int32_t), (void *)&D_01134ea0))
#undef D_01134ec0
#define D_01134ec0 (*(int32_t_arr_01134ec0 *)re_gvar(0x01134ec0u, sizeof(int32_t_arr_01134ec0), (void *)&D_01134ec0))
#endif
/* gvar-img v2.03 end */
