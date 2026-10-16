/* Простые сеттеры/копировальщики глобалов (авто-партия). */
#pragma once
#include "gvar.h"
#include "director.h"
#include "directorstorage.h"
#include "dirnodes.h"
#include "menuselect.h"
#include "menustate.h"
#include "noop.h"
#include "uihandlers.h"
#include "uihandlers2.h"
#include "uihandlers3.h"
#include "uihandlers4.h"
#define G0054A8E0 GAME_VAR(int32_t, G0054A8E0, 0x0054a8e0)
#ifndef RE_HOOK_BUILD
#pragma push_macro("G0054A8E0") /*gvi*/
#undef G0054A8E0 /*gvi*/
extern int32_t G0054A8E0;
#pragma pop_macro("G0054A8E0") /*gvi*/
#endif
#define G0054A8F0 GAME_VAR(int32_t, G0054A8F0, 0x0054a8f0)
#ifndef RE_HOOK_BUILD
#pragma push_macro("G0054A8F0") /*gvi*/
#undef G0054A8F0 /*gvi*/
extern int32_t G0054A8F0;
#pragma pop_macro("G0054A8F0") /*gvi*/
#endif
#define G0054A900 GAME_VAR(int32_t, G0054A900, 0x0054a900)
#ifndef RE_HOOK_BUILD
#pragma push_macro("G0054A900") /*gvi*/
#undef G0054A900 /*gvi*/
extern int32_t G0054A900;
#pragma pop_macro("G0054A900") /*gvi*/
#endif
#define G0054A910 GAME_VAR(int32_t, G0054A910, 0x0054a910)
#ifndef RE_HOOK_BUILD
#pragma push_macro("G0054A910") /*gvi*/
#undef G0054A910 /*gvi*/
extern int32_t G0054A910;
#pragma pop_macro("G0054A910") /*gvi*/
#endif
#define G0054A920 GAME_VAR(int32_t, G0054A920, 0x0054a920)
#ifndef RE_HOOK_BUILD
#pragma push_macro("G0054A920") /*gvi*/
#undef G0054A920 /*gvi*/
extern int32_t G0054A920;
#pragma pop_macro("G0054A920") /*gvi*/
#endif
#define G0054A930 GAME_VAR(int32_t, G0054A930, 0x0054a930)
#ifndef RE_HOOK_BUILD
#pragma push_macro("G0054A930") /*gvi*/
#undef G0054A930 /*gvi*/
extern int32_t G0054A930;
#pragma pop_macro("G0054A930") /*gvi*/
#endif
#define G0054A940 GAME_VAR(int32_t, G0054A940, 0x0054a940)
#ifndef RE_HOOK_BUILD
#pragma push_macro("G0054A940") /*gvi*/
#undef G0054A940 /*gvi*/
extern int32_t G0054A940;
#pragma pop_macro("G0054A940") /*gvi*/
#endif
#define G0054A950 GAME_VAR(int32_t, G0054A950, 0x0054a950)
#ifndef RE_HOOK_BUILD
#pragma push_macro("G0054A950") /*gvi*/
#undef G0054A950 /*gvi*/
extern int32_t G0054A950;
#pragma pop_macro("G0054A950") /*gvi*/
#endif
#define G0054AA24 GAME_VAR(int32_t, G0054AA24, 0x0054aa24)
#ifndef RE_HOOK_BUILD
#pragma push_macro("G0054AA24") /*gvi*/
#undef G0054AA24 /*gvi*/
extern int32_t G0054AA24;
#pragma pop_macro("G0054AA24") /*gvi*/
#endif
#define G0054AA28 GAME_VAR(int32_t, G0054AA28, 0x0054aa28)
#ifndef RE_HOOK_BUILD
#pragma push_macro("G0054AA28") /*gvi*/
#undef G0054AA28 /*gvi*/
extern int32_t G0054AA28;
#pragma pop_macro("G0054AA28") /*gvi*/
#endif
#define G0054AA2C GAME_VAR(uint8_t, G0054AA2C, 0x0054aa2c)
#ifndef RE_HOOK_BUILD
#pragma push_macro("G0054AA2C") /*gvi*/
#undef G0054AA2C /*gvi*/
extern uint8_t G0054AA2C;
#pragma pop_macro("G0054AA2C") /*gvi*/
#endif
#define G0054AA2D GAME_VAR(uint8_t, G0054AA2D, 0x0054aa2d)
#ifndef RE_HOOK_BUILD
#pragma push_macro("G0054AA2D") /*gvi*/
#undef G0054AA2D /*gvi*/
extern uint8_t G0054AA2D;
#pragma pop_macro("G0054AA2D") /*gvi*/
#endif
#define G0054AA2E GAME_VAR(uint8_t, G0054AA2E, 0x0054aa2e)
#ifndef RE_HOOK_BUILD
#pragma push_macro("G0054AA2E") /*gvi*/
#undef G0054AA2E /*gvi*/
extern uint8_t G0054AA2E;
#pragma pop_macro("G0054AA2E") /*gvi*/
#endif
#define G0054AA44 GAME_VAR(int32_t, G0054AA44, 0x0054aa44)
#ifndef RE_HOOK_BUILD
#pragma push_macro("G0054AA44") /*gvi*/
#undef G0054AA44 /*gvi*/
extern int32_t G0054AA44;
#pragma pop_macro("G0054AA44") /*gvi*/
#endif
#define G0054C6E8 GAME_VAR(int32_t, G0054C6E8, 0x0054c6e8)
#ifndef RE_HOOK_BUILD
#pragma push_macro("G0054C6E8") /*gvi*/
#undef G0054C6E8 /*gvi*/
extern int32_t G0054C6E8;
#pragma pop_macro("G0054C6E8") /*gvi*/
#endif
#define G0054C6F8 GAME_VAR(int32_t, G0054C6F8, 0x0054c6f8)
#ifndef RE_HOOK_BUILD
#pragma push_macro("G0054C6F8") /*gvi*/
#undef G0054C6F8 /*gvi*/
extern int32_t G0054C6F8;
#pragma pop_macro("G0054C6F8") /*gvi*/
#endif
#define G0054C958 GAME_VAR(int32_t, G0054C958, 0x0054c958)
#ifndef RE_HOOK_BUILD
#pragma push_macro("G0054C958") /*gvi*/
#undef G0054C958 /*gvi*/
extern int32_t G0054C958;
#pragma pop_macro("G0054C958") /*gvi*/
#endif
#define G0054C968 GAME_VAR(int32_t, G0054C968, 0x0054c968)
#ifndef RE_HOOK_BUILD
#pragma push_macro("G0054C968") /*gvi*/
#undef G0054C968 /*gvi*/
extern int32_t G0054C968;
#pragma pop_macro("G0054C968") /*gvi*/
#endif
#define G0054D100 GAME_VAR(int32_t, G0054D100, 0x0054d100)
#ifndef RE_HOOK_BUILD
#pragma push_macro("G0054D100") /*gvi*/
#undef G0054D100 /*gvi*/
extern int32_t G0054D100;
#pragma pop_macro("G0054D100") /*gvi*/
#endif
#define G0054D110 GAME_VAR(int32_t, G0054D110, 0x0054d110)
#ifndef RE_HOOK_BUILD
#pragma push_macro("G0054D110") /*gvi*/
#undef G0054D110 /*gvi*/
extern int32_t G0054D110;
#pragma pop_macro("G0054D110") /*gvi*/
#endif
#define G0054D120 GAME_VAR(int32_t, G0054D120, 0x0054d120)
#ifndef RE_HOOK_BUILD
#pragma push_macro("G0054D120") /*gvi*/
#undef G0054D120 /*gvi*/
extern int32_t G0054D120;
#pragma pop_macro("G0054D120") /*gvi*/
#endif
#define G0054D1A8 GAME_VAR(int32_t, G0054D1A8, 0x0054d1a8)
#ifndef RE_HOOK_BUILD
#pragma push_macro("G0054D1A8") /*gvi*/
#undef G0054D1A8 /*gvi*/
extern int32_t G0054D1A8;
#pragma pop_macro("G0054D1A8") /*gvi*/
#endif
#define G0054D1B8 GAME_VAR(int32_t, G0054D1B8, 0x0054d1b8)
#ifndef RE_HOOK_BUILD
#pragma push_macro("G0054D1B8") /*gvi*/
#undef G0054D1B8 /*gvi*/
extern int32_t G0054D1B8;
#pragma pop_macro("G0054D1B8") /*gvi*/
#endif
#define G0054D1C8 GAME_VAR(int32_t, G0054D1C8, 0x0054d1c8)
#ifndef RE_HOOK_BUILD
#pragma push_macro("G0054D1C8") /*gvi*/
#undef G0054D1C8 /*gvi*/
extern int32_t G0054D1C8;
#pragma pop_macro("G0054D1C8") /*gvi*/
#endif
#define G0054D1D8 GAME_VAR(int32_t, G0054D1D8, 0x0054d1d8)
#ifndef RE_HOOK_BUILD
#pragma push_macro("G0054D1D8") /*gvi*/
#undef G0054D1D8 /*gvi*/
extern int32_t G0054D1D8;
#pragma pop_macro("G0054D1D8") /*gvi*/
#endif
#define G0054D1E8 GAME_VAR(int32_t, G0054D1E8, 0x0054d1e8)
#ifndef RE_HOOK_BUILD
#pragma push_macro("G0054D1E8") /*gvi*/
#undef G0054D1E8 /*gvi*/
extern int32_t G0054D1E8;
#pragma pop_macro("G0054D1E8") /*gvi*/
#endif
#define G0054D298 GAME_VAR(int32_t, G0054D298, 0x0054d298)
#ifndef RE_HOOK_BUILD
#pragma push_macro("G0054D298") /*gvi*/
#undef G0054D298 /*gvi*/
extern int32_t G0054D298;
#pragma pop_macro("G0054D298") /*gvi*/
#endif
#define G0054D2A8 GAME_VAR(int32_t, G0054D2A8, 0x0054d2a8)
#ifndef RE_HOOK_BUILD
#pragma push_macro("G0054D2A8") /*gvi*/
#undef G0054D2A8 /*gvi*/
extern int32_t G0054D2A8;
#pragma pop_macro("G0054D2A8") /*gvi*/
#endif
#define G0054D2B8 GAME_VAR(int32_t, G0054D2B8, 0x0054d2b8)
#ifndef RE_HOOK_BUILD
#pragma push_macro("G0054D2B8") /*gvi*/
#undef G0054D2B8 /*gvi*/
extern int32_t G0054D2B8;
#pragma pop_macro("G0054D2B8") /*gvi*/
#endif
#define G0054D2C8 GAME_VAR(int32_t, G0054D2C8, 0x0054d2c8)
#ifndef RE_HOOK_BUILD
#pragma push_macro("G0054D2C8") /*gvi*/
#undef G0054D2C8 /*gvi*/
extern int32_t G0054D2C8;
#pragma pop_macro("G0054D2C8") /*gvi*/
#endif
#define G0054D2D8 GAME_VAR(int32_t, G0054D2D8, 0x0054d2d8)
#ifndef RE_HOOK_BUILD
#pragma push_macro("G0054D2D8") /*gvi*/
#undef G0054D2D8 /*gvi*/
extern int32_t G0054D2D8;
#pragma pop_macro("G0054D2D8") /*gvi*/
#endif
#define G0054D2E8 GAME_VAR(int32_t, G0054D2E8, 0x0054d2e8)
#ifndef RE_HOOK_BUILD
#pragma push_macro("G0054D2E8") /*gvi*/
#undef G0054D2E8 /*gvi*/
extern int32_t G0054D2E8;
#pragma pop_macro("G0054D2E8") /*gvi*/
#endif
#define G0054D3B0 GAME_VAR(int32_t, G0054D3B0, 0x0054d3b0)
#ifndef RE_HOOK_BUILD
#pragma push_macro("G0054D3B0") /*gvi*/
#undef G0054D3B0 /*gvi*/
extern int32_t G0054D3B0;
#pragma pop_macro("G0054D3B0") /*gvi*/
#endif
#define G0054D3C0 GAME_VAR(int32_t, G0054D3C0, 0x0054d3c0)
#ifndef RE_HOOK_BUILD
#pragma push_macro("G0054D3C0") /*gvi*/
#undef G0054D3C0 /*gvi*/
extern int32_t G0054D3C0;
#pragma pop_macro("G0054D3C0") /*gvi*/
#endif
#define G0054D3D0 GAME_VAR(int32_t, G0054D3D0, 0x0054d3d0)
#ifndef RE_HOOK_BUILD
#pragma push_macro("G0054D3D0") /*gvi*/
#undef G0054D3D0 /*gvi*/
extern int32_t G0054D3D0;
#pragma pop_macro("G0054D3D0") /*gvi*/
#endif
#define G0054D3E0 GAME_VAR(int32_t, G0054D3E0, 0x0054d3e0)
#ifndef RE_HOOK_BUILD
#pragma push_macro("G0054D3E0") /*gvi*/
#undef G0054D3E0 /*gvi*/
extern int32_t G0054D3E0;
#pragma pop_macro("G0054D3E0") /*gvi*/
#endif
#define G0054D3F0 GAME_VAR(int32_t, G0054D3F0, 0x0054d3f0)
#ifndef RE_HOOK_BUILD
#pragma push_macro("G0054D3F0") /*gvi*/
#undef G0054D3F0 /*gvi*/
extern int32_t G0054D3F0;
#pragma pop_macro("G0054D3F0") /*gvi*/
#endif
#define G0054D400 GAME_VAR(int32_t, G0054D400, 0x0054d400)
#ifndef RE_HOOK_BUILD
#pragma push_macro("G0054D400") /*gvi*/
#undef G0054D400 /*gvi*/
extern int32_t G0054D400;
#pragma pop_macro("G0054D400") /*gvi*/
#endif
#define G0054E16C GAME_VAR(int32_t, G0054E16C, 0x0054e16c)
#ifndef RE_HOOK_BUILD
#pragma push_macro("G0054E16C") /*gvi*/
#undef G0054E16C /*gvi*/
extern int32_t G0054E16C;
#pragma pop_macro("G0054E16C") /*gvi*/
#endif
#define G0054E198 GAME_VAR(int32_t, G0054E198, 0x0054e198)
#ifndef RE_HOOK_BUILD
#pragma push_macro("G0054E198") /*gvi*/
#undef G0054E198 /*gvi*/
extern int32_t G0054E198;
#pragma pop_macro("G0054E198") /*gvi*/
#endif
#define G0054E1A4 GAME_VAR(uint8_t, G0054E1A4, 0x0054e1a4)
#ifndef RE_HOOK_BUILD
#pragma push_macro("G0054E1A4") /*gvi*/
#undef G0054E1A4 /*gvi*/
extern uint8_t G0054E1A4;
#pragma pop_macro("G0054E1A4") /*gvi*/
#endif
#define G0054E1A8 GAME_VAR(int32_t, G0054E1A8, 0x0054e1a8)
#ifndef RE_HOOK_BUILD
#pragma push_macro("G0054E1A8") /*gvi*/
#undef G0054E1A8 /*gvi*/
extern int32_t G0054E1A8;
#pragma pop_macro("G0054E1A8") /*gvi*/
#endif
#define G0054E1B4 GAME_VAR(uint8_t, G0054E1B4, 0x0054e1b4)
#ifndef RE_HOOK_BUILD
#pragma push_macro("G0054E1B4") /*gvi*/
#undef G0054E1B4 /*gvi*/
extern uint8_t G0054E1B4;
#pragma pop_macro("G0054E1B4") /*gvi*/
#endif
#define G0054E1B8 GAME_VAR(int32_t, G0054E1B8, 0x0054e1b8)
#ifndef RE_HOOK_BUILD
#pragma push_macro("G0054E1B8") /*gvi*/
#undef G0054E1B8 /*gvi*/
extern int32_t G0054E1B8;
#pragma pop_macro("G0054E1B8") /*gvi*/
#endif
#define G0054E448 GAME_VAR(int32_t, G0054E448, 0x0054e448)
#ifndef RE_HOOK_BUILD
#pragma push_macro("G0054E448") /*gvi*/
#undef G0054E448 /*gvi*/
extern int32_t G0054E448;
#pragma pop_macro("G0054E448") /*gvi*/
#endif
#define G0054E458 GAME_VAR(int32_t, G0054E458, 0x0054e458)
#ifndef RE_HOOK_BUILD
#pragma push_macro("G0054E458") /*gvi*/
#undef G0054E458 /*gvi*/
extern int32_t G0054E458;
#pragma pop_macro("G0054E458") /*gvi*/
#endif
#define G0054E468 GAME_VAR(int32_t, G0054E468, 0x0054e468)
#ifndef RE_HOOK_BUILD
#pragma push_macro("G0054E468") /*gvi*/
#undef G0054E468 /*gvi*/
extern int32_t G0054E468;
#pragma pop_macro("G0054E468") /*gvi*/
#endif
#define G0054E6A8 GAME_VAR(int32_t, G0054E6A8, 0x0054e6a8)
#ifndef RE_HOOK_BUILD
#pragma push_macro("G0054E6A8") /*gvi*/
#undef G0054E6A8 /*gvi*/
extern int32_t G0054E6A8;
#pragma pop_macro("G0054E6A8") /*gvi*/
#endif
#define G0054E6B8 GAME_VAR(int32_t, G0054E6B8, 0x0054e6b8)
#ifndef RE_HOOK_BUILD
#pragma push_macro("G0054E6B8") /*gvi*/
#undef G0054E6B8 /*gvi*/
extern int32_t G0054E6B8;
#pragma pop_macro("G0054E6B8") /*gvi*/
#endif
#define G0054E6C8 GAME_VAR(int32_t, G0054E6C8, 0x0054e6c8)
#ifndef RE_HOOK_BUILD
#pragma push_macro("G0054E6C8") /*gvi*/
#undef G0054E6C8 /*gvi*/
extern int32_t G0054E6C8;
#pragma pop_macro("G0054E6C8") /*gvi*/
#endif
#define G0054E6D8 GAME_VAR(int32_t, G0054E6D8, 0x0054e6d8)
#ifndef RE_HOOK_BUILD
#pragma push_macro("G0054E6D8") /*gvi*/
#undef G0054E6D8 /*gvi*/
extern int32_t G0054E6D8;
#pragma pop_macro("G0054E6D8") /*gvi*/
#endif
#define G0054E6E8 GAME_VAR(int32_t, G0054E6E8, 0x0054e6e8)
#ifndef RE_HOOK_BUILD
#pragma push_macro("G0054E6E8") /*gvi*/
#undef G0054E6E8 /*gvi*/
extern int32_t G0054E6E8;
#pragma pop_macro("G0054E6E8") /*gvi*/
#endif
#define G00575550 GAME_VAR(int32_t, G00575550, 0x00575550)
#ifndef RE_HOOK_BUILD
#pragma push_macro("G00575550") /*gvi*/
#undef G00575550 /*gvi*/
extern int32_t G00575550;
#pragma pop_macro("G00575550") /*gvi*/
#endif
#define G00575554 GAME_VAR(int32_t, G00575554, 0x00575554)
#ifndef RE_HOOK_BUILD
#pragma push_macro("G00575554") /*gvi*/
#undef G00575554 /*gvi*/
extern int32_t G00575554;
#pragma pop_macro("G00575554") /*gvi*/
#endif
#define G005D77C0 GAME_VAR(uint8_t, G005D77C0, 0x005d77c0)
#ifndef RE_HOOK_BUILD
#pragma push_macro("G005D77C0") /*gvi*/
#undef G005D77C0 /*gvi*/
extern uint8_t G005D77C0;
#pragma pop_macro("G005D77C0") /*gvi*/
#endif
#define G005D77C1 GAME_VAR(uint8_t, G005D77C1, 0x005d77c1)
#ifndef RE_HOOK_BUILD
#pragma push_macro("G005D77C1") /*gvi*/
#undef G005D77C1 /*gvi*/
extern uint8_t G005D77C1;
#pragma pop_macro("G005D77C1") /*gvi*/
#endif
#define G005D77C4 GAME_VAR(int32_t, G005D77C4, 0x005d77c4)
#ifndef RE_HOOK_BUILD
#pragma push_macro("G005D77C4") /*gvi*/
#undef G005D77C4 /*gvi*/
extern int32_t G005D77C4;
#pragma pop_macro("G005D77C4") /*gvi*/
#endif
#define G005D77C8 GAME_VAR(int32_t, G005D77C8, 0x005d77c8)
#ifndef RE_HOOK_BUILD
#pragma push_macro("G005D77C8") /*gvi*/
#undef G005D77C8 /*gvi*/
extern int32_t G005D77C8;
#pragma pop_macro("G005D77C8") /*gvi*/
#endif
#define G005D77CC GAME_VAR(int32_t, G005D77CC, 0x005d77cc)
#ifndef RE_HOOK_BUILD
#pragma push_macro("G005D77CC") /*gvi*/
#undef G005D77CC /*gvi*/
extern int32_t G005D77CC;
#pragma pop_macro("G005D77CC") /*gvi*/
#endif
#define G005F7E54 GAME_VAR(int32_t, G005F7E54, 0x005f7e54)
#ifndef RE_HOOK_BUILD
#pragma push_macro("G005F7E54") /*gvi*/
#undef G005F7E54 /*gvi*/
extern int32_t G005F7E54;
#pragma pop_macro("G005F7E54") /*gvi*/
#endif
#define G005FE850 GAME_VAR(int32_t, G005FE850, 0x005fe850)
#ifndef RE_HOOK_BUILD
#pragma push_macro("G005FE850") /*gvi*/
#undef G005FE850 /*gvi*/
extern int32_t G005FE850;
#pragma pop_macro("G005FE850") /*gvi*/
#endif
#define G005FE92C GAME_VAR(int32_t, G005FE92C, 0x005fe92c)
#ifndef RE_HOOK_BUILD
#pragma push_macro("G005FE92C") /*gvi*/
#undef G005FE92C /*gvi*/
extern int32_t G005FE92C;
#pragma pop_macro("G005FE92C") /*gvi*/
#endif
#define G00B31E40 GAME_VAR(uint8_t, G00B31E40, 0x00b31e40)
#ifndef RE_HOOK_BUILD
#pragma push_macro("G00B31E40") /*gvi*/
#undef G00B31E40 /*gvi*/
extern uint8_t G00B31E40;
#pragma pop_macro("G00B31E40") /*gvi*/
#endif
#define G00B31E41 GAME_VAR(uint8_t, G00B31E41, 0x00b31e41)
#ifndef RE_HOOK_BUILD
#pragma push_macro("G00B31E41") /*gvi*/
#undef G00B31E41 /*gvi*/
extern uint8_t G00B31E41;
#pragma pop_macro("G00B31E41") /*gvi*/
#endif
#define G00B31E42 GAME_VAR(uint8_t, G00B31E42, 0x00b31e42)
#ifndef RE_HOOK_BUILD
#pragma push_macro("G00B31E42") /*gvi*/
#undef G00B31E42 /*gvi*/
extern uint8_t G00B31E42;
#pragma pop_macro("G00B31E42") /*gvi*/
#endif
#define G00B31E43 GAME_VAR(uint8_t, G00B31E43, 0x00b31e43)
#ifndef RE_HOOK_BUILD
#pragma push_macro("G00B31E43") /*gvi*/
#undef G00B31E43 /*gvi*/
extern uint8_t G00B31E43;
#pragma pop_macro("G00B31E43") /*gvi*/
#endif
#define G00B5A730 GAME_VAR(int32_t, G00B5A730, 0x00b5a730)
#ifndef RE_HOOK_BUILD
#pragma push_macro("G00B5A730") /*gvi*/
#undef G00B5A730 /*gvi*/
extern int32_t G00B5A730;
#pragma pop_macro("G00B5A730") /*gvi*/
#endif
#define G00B5A734 GAME_VAR(int32_t, G00B5A734, 0x00b5a734)
#ifndef RE_HOOK_BUILD
#pragma push_macro("G00B5A734") /*gvi*/
#undef G00B5A734 /*gvi*/
extern int32_t G00B5A734;
#pragma pop_macro("G00B5A734") /*gvi*/
#endif
#define G00B5A738 GAME_VAR(int32_t, G00B5A738, 0x00b5a738)
#ifndef RE_HOOK_BUILD
#pragma push_macro("G00B5A738") /*gvi*/
#undef G00B5A738 /*gvi*/
extern int32_t G00B5A738;
#pragma pop_macro("G00B5A738") /*gvi*/
#endif
#define G00B5A73C GAME_VAR(int32_t, G00B5A73C, 0x00b5a73c)
#ifndef RE_HOOK_BUILD
#pragma push_macro("G00B5A73C") /*gvi*/
#undef G00B5A73C /*gvi*/
extern int32_t G00B5A73C;
#pragma pop_macro("G00B5A73C") /*gvi*/
#endif
#define G00B5A774 GAME_VAR(int32_t, G00B5A774, 0x00b5a774)
#ifndef RE_HOOK_BUILD
#pragma push_macro("G00B5A774") /*gvi*/
#undef G00B5A774 /*gvi*/
extern int32_t G00B5A774;
#pragma pop_macro("G00B5A774") /*gvi*/
#endif
#define G00B5A8CD GAME_VAR(uint8_t, G00B5A8CD, 0x00b5a8cd)
#ifndef RE_HOOK_BUILD
#pragma push_macro("G00B5A8CD") /*gvi*/
#undef G00B5A8CD /*gvi*/
extern uint8_t G00B5A8CD;
#pragma pop_macro("G00B5A8CD") /*gvi*/
#endif
#define G00B5C858 GAME_VAR(int32_t, G00B5C858, 0x00b5c858)
#ifndef RE_HOOK_BUILD
#pragma push_macro("G00B5C858") /*gvi*/
#undef G00B5C858 /*gvi*/
extern int32_t G00B5C858;
#pragma pop_macro("G00B5C858") /*gvi*/
#endif
#define G00B5C85C GAME_VAR(int32_t, G00B5C85C, 0x00b5c85c)
#ifndef RE_HOOK_BUILD
#pragma push_macro("G00B5C85C") /*gvi*/
#undef G00B5C85C /*gvi*/
extern int32_t G00B5C85C;
#pragma pop_macro("G00B5C85C") /*gvi*/
#endif
#define G00B5C860 GAME_VAR(int32_t, G00B5C860, 0x00b5c860)
#ifndef RE_HOOK_BUILD
#pragma push_macro("G00B5C860") /*gvi*/
#undef G00B5C860 /*gvi*/
extern int32_t G00B5C860;
#pragma pop_macro("G00B5C860") /*gvi*/
#endif
#define G00B5C864 GAME_VAR(int32_t, G00B5C864, 0x00b5c864)
#ifndef RE_HOOK_BUILD
#pragma push_macro("G00B5C864") /*gvi*/
#undef G00B5C864 /*gvi*/
extern int32_t G00B5C864;
#pragma pop_macro("G00B5C864") /*gvi*/
#endif
#define G00B5C868 GAME_VAR(int32_t, G00B5C868, 0x00b5c868)
#ifndef RE_HOOK_BUILD
#pragma push_macro("G00B5C868") /*gvi*/
#undef G00B5C868 /*gvi*/
extern int32_t G00B5C868;
#pragma pop_macro("G00B5C868") /*gvi*/
#endif
#define G00B5C86C GAME_VAR(int32_t, G00B5C86C, 0x00b5c86c)
#ifndef RE_HOOK_BUILD
#pragma push_macro("G00B5C86C") /*gvi*/
#undef G00B5C86C /*gvi*/
extern int32_t G00B5C86C;
#pragma pop_macro("G00B5C86C") /*gvi*/
#endif
#define G00B5C870 GAME_VAR(int32_t, G00B5C870, 0x00b5c870)
#ifndef RE_HOOK_BUILD
#pragma push_macro("G00B5C870") /*gvi*/
#undef G00B5C870 /*gvi*/
extern int32_t G00B5C870;
#pragma pop_macro("G00B5C870") /*gvi*/
#endif
#define G00B5C874 GAME_VAR(int32_t, G00B5C874, 0x00b5c874)
#ifndef RE_HOOK_BUILD
#pragma push_macro("G00B5C874") /*gvi*/
#undef G00B5C874 /*gvi*/
extern int32_t G00B5C874;
#pragma pop_macro("G00B5C874") /*gvi*/
#endif
#define G00B5C878 GAME_VAR(int32_t, G00B5C878, 0x00b5c878)
#ifndef RE_HOOK_BUILD
#pragma push_macro("G00B5C878") /*gvi*/
#undef G00B5C878 /*gvi*/
extern int32_t G00B5C878;
#pragma pop_macro("G00B5C878") /*gvi*/
#endif
#define G00B5C87C GAME_VAR(int32_t, G00B5C87C, 0x00b5c87c)
#ifndef RE_HOOK_BUILD
#pragma push_macro("G00B5C87C") /*gvi*/
#undef G00B5C87C /*gvi*/
extern int32_t G00B5C87C;
#pragma pop_macro("G00B5C87C") /*gvi*/
#endif
#define G00B5C880 GAME_VAR(int32_t, G00B5C880, 0x00b5c880)
#ifndef RE_HOOK_BUILD
#pragma push_macro("G00B5C880") /*gvi*/
#undef G00B5C880 /*gvi*/
extern int32_t G00B5C880;
#pragma pop_macro("G00B5C880") /*gvi*/
#endif
#define G00B5C884 GAME_VAR(int32_t, G00B5C884, 0x00b5c884)
#ifndef RE_HOOK_BUILD
#pragma push_macro("G00B5C884") /*gvi*/
#undef G00B5C884 /*gvi*/
extern int32_t G00B5C884;
#pragma pop_macro("G00B5C884") /*gvi*/
#endif
#define G00B5C888 GAME_VAR(int32_t, G00B5C888, 0x00b5c888)
#ifndef RE_HOOK_BUILD
#pragma push_macro("G00B5C888") /*gvi*/
#undef G00B5C888 /*gvi*/
extern int32_t G00B5C888;
#pragma pop_macro("G00B5C888") /*gvi*/
#endif
#define G00B5C88C GAME_VAR(int32_t, G00B5C88C, 0x00b5c88c)
#ifndef RE_HOOK_BUILD
#pragma push_macro("G00B5C88C") /*gvi*/
#undef G00B5C88C /*gvi*/
extern int32_t G00B5C88C;
#pragma pop_macro("G00B5C88C") /*gvi*/
#endif
#define G00B5C890 GAME_VAR(int32_t, G00B5C890, 0x00b5c890)
#ifndef RE_HOOK_BUILD
#pragma push_macro("G00B5C890") /*gvi*/
#undef G00B5C890 /*gvi*/
extern int32_t G00B5C890;
#pragma pop_macro("G00B5C890") /*gvi*/
#endif
#define G00B5C894 GAME_VAR(int32_t, G00B5C894, 0x00b5c894)
#ifndef RE_HOOK_BUILD
#pragma push_macro("G00B5C894") /*gvi*/
#undef G00B5C894 /*gvi*/
extern int32_t G00B5C894;
#pragma pop_macro("G00B5C894") /*gvi*/
#endif
#define G00B5C910 GAME_VAR(int32_t, G00B5C910, 0x00b5c910)
#ifndef RE_HOOK_BUILD
#pragma push_macro("G00B5C910") /*gvi*/
#undef G00B5C910 /*gvi*/
extern int32_t G00B5C910;
#pragma pop_macro("G00B5C910") /*gvi*/
#endif
#define G00B5C914 GAME_VAR(int32_t, G00B5C914, 0x00b5c914)
#ifndef RE_HOOK_BUILD
#pragma push_macro("G00B5C914") /*gvi*/
#undef G00B5C914 /*gvi*/
extern int32_t G00B5C914;
#pragma pop_macro("G00B5C914") /*gvi*/
#endif
#define G00B5C918 GAME_VAR(int32_t, G00B5C918, 0x00b5c918)
#ifndef RE_HOOK_BUILD
#pragma push_macro("G00B5C918") /*gvi*/
#undef G00B5C918 /*gvi*/
extern int32_t G00B5C918;
#pragma pop_macro("G00B5C918") /*gvi*/
#endif
#define G00B5C91C GAME_VAR(int32_t, G00B5C91C, 0x00b5c91c)
#ifndef RE_HOOK_BUILD
#pragma push_macro("G00B5C91C") /*gvi*/
#undef G00B5C91C /*gvi*/
extern int32_t G00B5C91C;
#pragma pop_macro("G00B5C91C") /*gvi*/
#endif
#define G00B5C920 GAME_VAR(int32_t, G00B5C920, 0x00b5c920)
#ifndef RE_HOOK_BUILD
#pragma push_macro("G00B5C920") /*gvi*/
#undef G00B5C920 /*gvi*/
extern int32_t G00B5C920;
#pragma pop_macro("G00B5C920") /*gvi*/
#endif
#define G00B5C924 GAME_VAR(int32_t, G00B5C924, 0x00b5c924)
#ifndef RE_HOOK_BUILD
#pragma push_macro("G00B5C924") /*gvi*/
#undef G00B5C924 /*gvi*/
extern int32_t G00B5C924;
#pragma pop_macro("G00B5C924") /*gvi*/
#endif
#define G00B5C928 GAME_VAR(int32_t, G00B5C928, 0x00b5c928)
#ifndef RE_HOOK_BUILD
#pragma push_macro("G00B5C928") /*gvi*/
#undef G00B5C928 /*gvi*/
extern int32_t G00B5C928;
#pragma pop_macro("G00B5C928") /*gvi*/
#endif
#define G00B5C92C GAME_VAR(int32_t, G00B5C92C, 0x00b5c92c)
#ifndef RE_HOOK_BUILD
#pragma push_macro("G00B5C92C") /*gvi*/
#undef G00B5C92C /*gvi*/
extern int32_t G00B5C92C;
#pragma pop_macro("G00B5C92C") /*gvi*/
#endif
#define G00B5C930 GAME_VAR(int32_t, G00B5C930, 0x00b5c930)
#ifndef RE_HOOK_BUILD
#pragma push_macro("G00B5C930") /*gvi*/
#undef G00B5C930 /*gvi*/
extern int32_t G00B5C930;
#pragma pop_macro("G00B5C930") /*gvi*/
#endif
#define G00B5C934 GAME_VAR(int32_t, G00B5C934, 0x00b5c934)
#ifndef RE_HOOK_BUILD
#pragma push_macro("G00B5C934") /*gvi*/
#undef G00B5C934 /*gvi*/
extern int32_t G00B5C934;
#pragma pop_macro("G00B5C934") /*gvi*/
#endif
#define G00B5C938 GAME_VAR(int32_t, G00B5C938, 0x00b5c938)
#ifndef RE_HOOK_BUILD
#pragma push_macro("G00B5C938") /*gvi*/
#undef G00B5C938 /*gvi*/
extern int32_t G00B5C938;
#pragma pop_macro("G00B5C938") /*gvi*/
#endif
#define G00B5C93C GAME_VAR(int32_t, G00B5C93C, 0x00b5c93c)
#ifndef RE_HOOK_BUILD
#pragma push_macro("G00B5C93C") /*gvi*/
#undef G00B5C93C /*gvi*/
extern int32_t G00B5C93C;
#pragma pop_macro("G00B5C93C") /*gvi*/
#endif
#define G00B5C940 GAME_VAR(int32_t, G00B5C940, 0x00b5c940)
#ifndef RE_HOOK_BUILD
#pragma push_macro("G00B5C940") /*gvi*/
#undef G00B5C940 /*gvi*/
extern int32_t G00B5C940;
#pragma pop_macro("G00B5C940") /*gvi*/
#endif
#define G00B5C944 GAME_VAR(int32_t, G00B5C944, 0x00b5c944)
#ifndef RE_HOOK_BUILD
#pragma push_macro("G00B5C944") /*gvi*/
#undef G00B5C944 /*gvi*/
extern int32_t G00B5C944;
#pragma pop_macro("G00B5C944") /*gvi*/
#endif
#define G00B5C948 GAME_VAR(int32_t, G00B5C948, 0x00b5c948)
#ifndef RE_HOOK_BUILD
#pragma push_macro("G00B5C948") /*gvi*/
#undef G00B5C948 /*gvi*/
extern int32_t G00B5C948;
#pragma pop_macro("G00B5C948") /*gvi*/
#endif
#define G00B5C94C GAME_VAR(int32_t, G00B5C94C, 0x00b5c94c)
#ifndef RE_HOOK_BUILD
#pragma push_macro("G00B5C94C") /*gvi*/
#undef G00B5C94C /*gvi*/
extern int32_t G00B5C94C;
#pragma pop_macro("G00B5C94C") /*gvi*/
#endif
#define G00BF1C20 GAME_VAR(uint8_t, G00BF1C20, 0x00bf1c20)
#ifndef RE_HOOK_BUILD
#pragma push_macro("G00BF1C20") /*gvi*/
#undef G00BF1C20 /*gvi*/
extern uint8_t G00BF1C20;
#pragma pop_macro("G00BF1C20") /*gvi*/
#endif
#define G00C29D80 GAME_VAR(uint8_t, G00C29D80, 0x00c29d80)
#ifndef RE_HOOK_BUILD
#pragma push_macro("G00C29D80") /*gvi*/
#undef G00C29D80 /*gvi*/
extern uint8_t G00C29D80;
#pragma pop_macro("G00C29D80") /*gvi*/
#endif
#define G00C29D81 GAME_VAR(uint8_t, G00C29D81, 0x00c29d81)
#ifndef RE_HOOK_BUILD
#pragma push_macro("G00C29D81") /*gvi*/
#undef G00C29D81 /*gvi*/
extern uint8_t G00C29D81;
#pragma pop_macro("G00C29D81") /*gvi*/
#endif
#define G00C4BDC4 GAME_VAR(int32_t, G00C4BDC4, 0x00c4bdc4)
#ifndef RE_HOOK_BUILD
#pragma push_macro("G00C4BDC4") /*gvi*/
#undef G00C4BDC4 /*gvi*/
extern int32_t G00C4BDC4;
#pragma pop_macro("G00C4BDC4") /*gvi*/
#endif
#include "strtab.h"
#define G00C55820 ((int32_t)P97_StrAddr[0])   /* единая таблица строк 00c55820 */
#define G00C5582C GAME_VAR(int32_t, G00C5582C, 0x00c5582c)
#ifndef RE_HOOK_BUILD
#pragma push_macro("G00C5582C") /*gvi*/
#undef G00C5582C /*gvi*/
extern int32_t G00C5582C;
#pragma pop_macro("G00C5582C") /*gvi*/
#endif
#define G00C55830 GAME_VAR(int32_t, G00C55830, 0x00c55830)
#ifndef RE_HOOK_BUILD
#pragma push_macro("G00C55830") /*gvi*/
#undef G00C55830 /*gvi*/
extern int32_t G00C55830;
#pragma pop_macro("G00C55830") /*gvi*/
#endif
#define G00C55878 GAME_VAR(int32_t, G00C55878, 0x00c55878)
#ifndef RE_HOOK_BUILD
#pragma push_macro("G00C55878") /*gvi*/
#undef G00C55878 /*gvi*/
extern int32_t G00C55878;
#pragma pop_macro("G00C55878") /*gvi*/
#endif
#define G00C5587C GAME_VAR(int32_t, G00C5587C, 0x00c5587c)
#ifndef RE_HOOK_BUILD
#pragma push_macro("G00C5587C") /*gvi*/
#undef G00C5587C /*gvi*/
extern int32_t G00C5587C;
#pragma pop_macro("G00C5587C") /*gvi*/
#endif
#define G00C55880 GAME_VAR(int32_t, G00C55880, 0x00c55880)
#ifndef RE_HOOK_BUILD
#pragma push_macro("G00C55880") /*gvi*/
#undef G00C55880 /*gvi*/
extern int32_t G00C55880;
#pragma pop_macro("G00C55880") /*gvi*/
#endif
#define G00C55884 GAME_VAR(int32_t, G00C55884, 0x00c55884)
#ifndef RE_HOOK_BUILD
#pragma push_macro("G00C55884") /*gvi*/
#undef G00C55884 /*gvi*/
extern int32_t G00C55884;
#pragma pop_macro("G00C55884") /*gvi*/
#endif
#define G00C558B4 GAME_VAR(int32_t, G00C558B4, 0x00c558b4)
#ifndef RE_HOOK_BUILD
#pragma push_macro("G00C558B4") /*gvi*/
#undef G00C558B4 /*gvi*/
extern int32_t G00C558B4;
#pragma pop_macro("G00C558B4") /*gvi*/
#endif
#define G00C558B8 GAME_VAR(int32_t, G00C558B8, 0x00c558b8)
#ifndef RE_HOOK_BUILD
#pragma push_macro("G00C558B8") /*gvi*/
#undef G00C558B8 /*gvi*/
extern int32_t G00C558B8;
#pragma pop_macro("G00C558B8") /*gvi*/
#endif
#define G00C558BC GAME_VAR(int32_t, G00C558BC, 0x00c558bc)
#ifndef RE_HOOK_BUILD
#pragma push_macro("G00C558BC") /*gvi*/
#undef G00C558BC /*gvi*/
extern int32_t G00C558BC;
#pragma pop_macro("G00C558BC") /*gvi*/
#endif
#define G00C558C0 GAME_VAR(int32_t, G00C558C0, 0x00c558c0)
#ifndef RE_HOOK_BUILD
#pragma push_macro("G00C558C0") /*gvi*/
#undef G00C558C0 /*gvi*/
extern int32_t G00C558C0;
#pragma pop_macro("G00C558C0") /*gvi*/
#endif
#define G00C558C4 GAME_VAR(int32_t, G00C558C4, 0x00c558c4)
#ifndef RE_HOOK_BUILD
#pragma push_macro("G00C558C4") /*gvi*/
#undef G00C558C4 /*gvi*/
extern int32_t G00C558C4;
#pragma pop_macro("G00C558C4") /*gvi*/
#endif
#define G00C55984 GAME_VAR(int32_t, G00C55984, 0x00c55984)
#ifndef RE_HOOK_BUILD
#pragma push_macro("G00C55984") /*gvi*/
#undef G00C55984 /*gvi*/
extern int32_t G00C55984;
#pragma pop_macro("G00C55984") /*gvi*/
#endif
#define G00C55988 GAME_VAR(int32_t, G00C55988, 0x00c55988)
#ifndef RE_HOOK_BUILD
#pragma push_macro("G00C55988") /*gvi*/
#undef G00C55988 /*gvi*/
extern int32_t G00C55988;
#pragma pop_macro("G00C55988") /*gvi*/
#endif
#define G00C5598C GAME_VAR(int32_t, G00C5598C, 0x00c5598c)
#ifndef RE_HOOK_BUILD
#pragma push_macro("G00C5598C") /*gvi*/
#undef G00C5598C /*gvi*/
extern int32_t G00C5598C;
#pragma pop_macro("G00C5598C") /*gvi*/
#endif
#define G00C55990 GAME_VAR(int32_t, G00C55990, 0x00c55990)
#ifndef RE_HOOK_BUILD
#pragma push_macro("G00C55990") /*gvi*/
#undef G00C55990 /*gvi*/
extern int32_t G00C55990;
#pragma pop_macro("G00C55990") /*gvi*/
#endif
#define G00C55994 GAME_VAR(int32_t, G00C55994, 0x00c55994)
#ifndef RE_HOOK_BUILD
#pragma push_macro("G00C55994") /*gvi*/
#undef G00C55994 /*gvi*/
extern int32_t G00C55994;
#pragma pop_macro("G00C55994") /*gvi*/
#endif
#define G00C55998 GAME_VAR(int32_t, G00C55998, 0x00c55998)
#ifndef RE_HOOK_BUILD
#pragma push_macro("G00C55998") /*gvi*/
#undef G00C55998 /*gvi*/
extern int32_t G00C55998;
#pragma pop_macro("G00C55998") /*gvi*/
#endif
#define G00C5599C GAME_VAR(int32_t, G00C5599C, 0x00c5599c)
#ifndef RE_HOOK_BUILD
#pragma push_macro("G00C5599C") /*gvi*/
#undef G00C5599C /*gvi*/
extern int32_t G00C5599C;
#pragma pop_macro("G00C5599C") /*gvi*/
#endif
#define G00C559A0 GAME_VAR(int32_t, G00C559A0, 0x00c559a0)
#ifndef RE_HOOK_BUILD
#pragma push_macro("G00C559A0") /*gvi*/
#undef G00C559A0 /*gvi*/
extern int32_t G00C559A0;
#pragma pop_macro("G00C559A0") /*gvi*/
#endif
#define G00C559B4 GAME_VAR(int32_t, G00C559B4, 0x00c559b4)
#ifndef RE_HOOK_BUILD
#pragma push_macro("G00C559B4") /*gvi*/
#undef G00C559B4 /*gvi*/
extern int32_t G00C559B4;
#pragma pop_macro("G00C559B4") /*gvi*/
#endif
#define G00C559B8 GAME_VAR(int32_t, G00C559B8, 0x00c559b8)
#ifndef RE_HOOK_BUILD
#pragma push_macro("G00C559B8") /*gvi*/
#undef G00C559B8 /*gvi*/
extern int32_t G00C559B8;
#pragma pop_macro("G00C559B8") /*gvi*/
#endif
#define G00C559BC GAME_VAR(int32_t, G00C559BC, 0x00c559bc)
#ifndef RE_HOOK_BUILD
#pragma push_macro("G00C559BC") /*gvi*/
#undef G00C559BC /*gvi*/
extern int32_t G00C559BC;
#pragma pop_macro("G00C559BC") /*gvi*/
#endif
#define G00C559C0 GAME_VAR(int32_t, G00C559C0, 0x00c559c0)
#ifndef RE_HOOK_BUILD
#pragma push_macro("G00C559C0") /*gvi*/
#undef G00C559C0 /*gvi*/
extern int32_t G00C559C0;
#pragma pop_macro("G00C559C0") /*gvi*/
#endif
#define G00C559C4 GAME_VAR(int32_t, G00C559C4, 0x00c559c4)
#ifndef RE_HOOK_BUILD
#pragma push_macro("G00C559C4") /*gvi*/
#undef G00C559C4 /*gvi*/
extern int32_t G00C559C4;
#pragma pop_macro("G00C559C4") /*gvi*/
#endif
#define G00C559C8 GAME_VAR(int32_t, G00C559C8, 0x00c559c8)
#ifndef RE_HOOK_BUILD
#pragma push_macro("G00C559C8") /*gvi*/
#undef G00C559C8 /*gvi*/
extern int32_t G00C559C8;
#pragma pop_macro("G00C559C8") /*gvi*/
#endif
#define G00C559CC GAME_VAR(int32_t, G00C559CC, 0x00c559cc)
#ifndef RE_HOOK_BUILD
#pragma push_macro("G00C559CC") /*gvi*/
#undef G00C559CC /*gvi*/
extern int32_t G00C559CC;
#pragma pop_macro("G00C559CC") /*gvi*/
#endif
#define G00C559D0 GAME_VAR(int32_t, G00C559D0, 0x00c559d0)
#ifndef RE_HOOK_BUILD
#pragma push_macro("G00C559D0") /*gvi*/
#undef G00C559D0 /*gvi*/
extern int32_t G00C559D0;
#pragma pop_macro("G00C559D0") /*gvi*/
#endif
#define G00C559D4 GAME_VAR(int32_t, G00C559D4, 0x00c559d4)
#ifndef RE_HOOK_BUILD
#pragma push_macro("G00C559D4") /*gvi*/
#undef G00C559D4 /*gvi*/
extern int32_t G00C559D4;
#pragma pop_macro("G00C559D4") /*gvi*/
#endif
#define G00C55A5C GAME_VAR(int32_t, G00C55A5C, 0x00c55a5c)
#ifndef RE_HOOK_BUILD
#pragma push_macro("G00C55A5C") /*gvi*/
#undef G00C55A5C /*gvi*/
extern int32_t G00C55A5C;
#pragma pop_macro("G00C55A5C") /*gvi*/
#endif
#define G00C81988 GAME_VAR(int32_t, G00C81988, 0x00c81988)
#ifndef RE_HOOK_BUILD
#pragma push_macro("G00C81988") /*gvi*/
#undef G00C81988 /*gvi*/
extern int32_t G00C81988;
#pragma pop_macro("G00C81988") /*gvi*/
#endif
#define G00C8198C GAME_VAR(int32_t, G00C8198C, 0x00c8198c)
#ifndef RE_HOOK_BUILD
#pragma push_macro("G00C8198C") /*gvi*/
#undef G00C8198C /*gvi*/
extern int32_t G00C8198C;
#pragma pop_macro("G00C8198C") /*gvi*/
#endif
#define G00D12408 GAME_VAR(int32_t, G00D12408, 0x00d12408)
#ifndef RE_HOOK_BUILD
#pragma push_macro("G00D12408") /*gvi*/
#undef G00D12408 /*gvi*/
extern int32_t G00D12408;
#pragma pop_macro("G00D12408") /*gvi*/
#endif
#define G00D12418 GAME_VAR(int32_t, G00D12418, 0x00d12418)
#ifndef RE_HOOK_BUILD
#pragma push_macro("G00D12418") /*gvi*/
#undef G00D12418 /*gvi*/
extern int32_t G00D12418;
#pragma pop_macro("G00D12418") /*gvi*/
#endif
#define G00D1241C GAME_VAR(int32_t, G00D1241C, 0x00d1241c)
#ifndef RE_HOOK_BUILD
#pragma push_macro("G00D1241C") /*gvi*/
#undef G00D1241C /*gvi*/
extern int32_t G00D1241C;
#pragma pop_macro("G00D1241C") /*gvi*/
#endif
#define G00D14EEC GAME_VAR(int32_t, G00D14EEC, 0x00d14eec)
#ifndef RE_HOOK_BUILD
#pragma push_macro("G00D14EEC") /*gvi*/
#undef G00D14EEC /*gvi*/
extern int32_t G00D14EEC;
#pragma pop_macro("G00D14EEC") /*gvi*/
#endif
#define G00D14EF0 GAME_VAR(uint8_t *, G00D14EF0, 0x00d14ef0)   /* значок RFLECT (004cb857) */
#ifndef RE_HOOK_BUILD
extern uint8_t *G00D14EF0;
#endif
#define G00D14EF4 GAME_VAR(int32_t, G00D14EF4, 0x00d14ef4)
#ifndef RE_HOOK_BUILD
#pragma push_macro("G00D14EF4") /*gvi*/
#undef G00D14EF4 /*gvi*/
extern int32_t G00D14EF4;
#pragma pop_macro("G00D14EF4") /*gvi*/
#endif
#define G00D164EC GAME_VAR(uint8_t *, G00D164EC, 0x00d164ec)   /* значок SPLASH (004cb857) */
#ifndef RE_HOOK_BUILD
extern uint8_t *G00D164EC;
#endif
#define G00D164F0 GAME_VAR(uint8_t, G00D164F0, 0x00d164f0)
#ifndef RE_HOOK_BUILD
#pragma push_macro("G00D164F0") /*gvi*/
#undef G00D164F0 /*gvi*/
extern uint8_t G00D164F0;
#pragma pop_macro("G00D164F0") /*gvi*/
#endif
#define G00D17AE4 GAME_VAR(uint8_t, G00D17AE4, 0x00d17ae4)
#ifndef RE_HOOK_BUILD
#pragma push_macro("G00D17AE4") /*gvi*/
#undef G00D17AE4 /*gvi*/
extern uint8_t G00D17AE4;
#pragma pop_macro("G00D17AE4") /*gvi*/
#endif
#define G00D17B04 GAME_VAR(uint8_t, G00D17B04, 0x00d17b04)
#ifndef RE_HOOK_BUILD
#pragma push_macro("G00D17B04") /*gvi*/
#undef G00D17B04 /*gvi*/
extern uint8_t G00D17B04;
#pragma pop_macro("G00D17B04") /*gvi*/
#endif
#define G00D17B08 GAME_VAR(int32_t, G00D17B08, 0x00d17b08)
#ifndef RE_HOOK_BUILD
#pragma push_macro("G00D17B08") /*gvi*/
#undef G00D17B08 /*gvi*/
extern int32_t G00D17B08;
#pragma pop_macro("G00D17B08") /*gvi*/
#endif
#define G00D17B10 GAME_VAR(uint8_t, G00D17B10, 0x00d17b10)
#ifndef RE_HOOK_BUILD
#pragma push_macro("G00D17B10") /*gvi*/
#undef G00D17B10 /*gvi*/
extern uint8_t G00D17B10;
#pragma pop_macro("G00D17B10") /*gvi*/
#endif
#define G00D17B1C GAME_VAR(int32_t, G00D17B1C, 0x00d17b1c)
#ifndef RE_HOOK_BUILD
#pragma push_macro("G00D17B1C") /*gvi*/
#undef G00D17B1C /*gvi*/
extern int32_t G00D17B1C;
#pragma pop_macro("G00D17B1C") /*gvi*/
#endif
#define G00D17B20 GAME_VAR(uint8_t, G00D17B20, 0x00d17b20)
#ifndef RE_HOOK_BUILD
#pragma push_macro("G00D17B20") /*gvi*/
#undef G00D17B20 /*gvi*/
extern uint8_t G00D17B20;
#pragma pop_macro("G00D17B20") /*gvi*/
#endif
#define G00D17B21 GAME_VAR(uint8_t, G00D17B21, 0x00d17b21)
#ifndef RE_HOOK_BUILD
#pragma push_macro("G00D17B21") /*gvi*/
#undef G00D17B21 /*gvi*/
extern uint8_t G00D17B21;
#pragma pop_macro("G00D17B21") /*gvi*/
#endif
#define G010DE220 GAME_VAR(int32_t, G010DE220, 0x010de220)
#ifndef RE_HOOK_BUILD
#pragma push_macro("G010DE220") /*gvi*/
#undef G010DE220 /*gvi*/
extern int32_t G010DE220;
#pragma pop_macro("G010DE220") /*gvi*/
#endif
#define G010DE224 GAME_VAR(int32_t, G010DE224, 0x010de224)
#ifndef RE_HOOK_BUILD
#pragma push_macro("G010DE224") /*gvi*/
#undef G010DE224 /*gvi*/
extern int32_t G010DE224;
#pragma pop_macro("G010DE224") /*gvi*/
#endif
#define G010DE228 GAME_VAR(int32_t, G010DE228, 0x010de228)
#ifndef RE_HOOK_BUILD
#pragma push_macro("G010DE228") /*gvi*/
#undef G010DE228 /*gvi*/
extern int32_t G010DE228;
#pragma pop_macro("G010DE228") /*gvi*/
#endif
#define G010DE22C GAME_VAR(int32_t, G010DE22C, 0x010de22c)
#ifndef RE_HOOK_BUILD
#pragma push_macro("G010DE22C") /*gvi*/
#undef G010DE22C /*gvi*/
extern int32_t G010DE22C;
#pragma pop_macro("G010DE22C") /*gvi*/
#endif
#define G010FFA20 GAME_VAR(int32_t, G010FFA20, 0x010ffa20)
#ifndef RE_HOOK_BUILD
#pragma push_macro("G010FFA20") /*gvi*/
#undef G010FFA20 /*gvi*/
extern int32_t G010FFA20;
#pragma pop_macro("G010FFA20") /*gvi*/
#endif
#define G010FFB40 GAME_VAR(int32_t, G010FFB40, 0x010ffb40)
#ifndef RE_HOOK_BUILD
#pragma push_macro("G010FFB40") /*gvi*/
#undef G010FFB40 /*gvi*/
extern int32_t G010FFB40;
#pragma pop_macro("G010FFB40") /*gvi*/
#endif
#define G010FFD04 GAME_VAR(int32_t, G010FFD04, 0x010ffd04)
#ifndef RE_HOOK_BUILD
#pragma push_macro("G010FFD04") /*gvi*/
#undef G010FFD04 /*gvi*/
extern int32_t G010FFD04;
#pragma pop_macro("G010FFD04") /*gvi*/
#endif
#define G010FFD08 GAME_VAR(int32_t, G010FFD08, 0x010ffd08)
#ifndef RE_HOOK_BUILD
#pragma push_macro("G010FFD08") /*gvi*/
#undef G010FFD08 /*gvi*/
extern int32_t G010FFD08;
#pragma pop_macro("G010FFD08") /*gvi*/
#endif
#define G01105D60 GAME_VAR(int32_t, G01105D60, 0x01105d60)
#ifndef RE_HOOK_BUILD
#pragma push_macro("G01105D60") /*gvi*/
#undef G01105D60 /*gvi*/
extern int32_t G01105D60;
#pragma pop_macro("G01105D60") /*gvi*/
#endif
#define G01105D80 ICONTAB_VAR(int32_t, 6)   /* v1.56: таблица значков 01105d68 (icontab.h) */
#define G0110B24C GAME_VAR(int32_t, G0110B24C, 0x0110b24c)
#ifndef RE_HOOK_BUILD
#pragma push_macro("G0110B24C") /*gvi*/
#undef G0110B24C /*gvi*/
extern int32_t G0110B24C;
#pragma pop_macro("G0110B24C") /*gvi*/
#endif
#define G01129580 GAME_VAR(int32_t, G01129580, 0x01129580)
#ifndef RE_HOOK_BUILD
#pragma push_macro("G01129580") /*gvi*/
#undef G01129580 /*gvi*/
extern int32_t G01129580;
#pragma pop_macro("G01129580") /*gvi*/
#endif
#define G0113A6C0 GAME_VAR(int32_t, G0113A6C0, 0x0113a6c0)
#ifndef RE_HOOK_BUILD
#pragma push_macro("G0113A6C0") /*gvi*/
#undef G0113A6C0 /*gvi*/
extern int32_t G0113A6C0;
#pragma pop_macro("G0113A6C0") /*gvi*/
#endif
#define G011426F8 GAME_VAR(int32_t, G011426F8, 0x011426f8)
#ifndef RE_HOOK_BUILD
#pragma push_macro("G011426F8") /*gvi*/
#undef G011426F8 /*gvi*/
extern int32_t G011426F8;
#pragma pop_macro("G011426F8") /*gvi*/
#endif
#define G01144284 GAME_VAR(int32_t, G01144284, 0x01144284)
#ifndef RE_HOOK_BUILD
#pragma push_macro("G01144284") /*gvi*/
#undef G01144284 /*gvi*/
extern int32_t G01144284;
#pragma pop_macro("G01144284") /*gvi*/
#endif
#define G011EFFE4 GAME_VAR(int32_t, G011EFFE4, 0x011effe4)
#ifndef RE_HOOK_BUILD
#pragma push_macro("G011EFFE4") /*gvi*/
#undef G011EFFE4 /*gvi*/
extern int32_t G011EFFE4;
#pragma pop_macro("G011EFFE4") /*gvi*/
#endif
void GlobalSet0040A5C6(void);
void GlobalSet0040B0A4(void);
void GlobalSet004122C4(void);
void GlobalSet004126DF(void);
void GlobalSet0041351C(void);
void GlobalSet00413691(void);
void GlobalSet0041390C(void);
void GlobalSet00413B7C(void);
void GlobalSet0041640C(void);
void GlobalSet00416433(void);
void GlobalSet0041648A(void);
void GlobalSet00417A2E(void);
void GlobalSet00419F80(void);
void GlobalSet004964E2(void);
void GlobalSet004AADDF(void);
void GlobalSet004C09B9(void);
void GlobalSet004CA0C0(void);
void GlobalSet004CF100(void);
void GlobalSet004E38FE(void);
void GlobalSet004E3911(void);
void GlobalSet00510349(void);
void GlobalSet0051040F(void);
void GlobalSet00510550(void);
void GlobalSet00510595(void);
void GlobalSet0051065B(void);
void GlobalSet00511378(void);
void GlobalSet005113B1(void);
void GlobalSet00519DDB(void);
void GlobalSet00519DE7(void);
void GlobalSet0051BD78(void);
void GlobalSet0051D811(void);
/* gvar-img v2.03 begin (tools/gen_gvar_img.py) */
#if !defined(RE_HOOK_BUILD) && !defined(RE_GVAR_PLAIN)
#undef G0054A8E0
#define G0054A8E0 (*(int32_t *)re_gvar(0x0054a8e0u, sizeof(int32_t), (void *)&G0054A8E0))
#undef G0054A8F0
#define G0054A8F0 (*(int32_t *)re_gvar(0x0054a8f0u, sizeof(int32_t), (void *)&G0054A8F0))
#undef G0054A900
#define G0054A900 (*(int32_t *)re_gvar(0x0054a900u, sizeof(int32_t), (void *)&G0054A900))
#undef G0054A910
#define G0054A910 (*(int32_t *)re_gvar(0x0054a910u, sizeof(int32_t), (void *)&G0054A910))
#undef G0054A920
#define G0054A920 (*(int32_t *)re_gvar(0x0054a920u, sizeof(int32_t), (void *)&G0054A920))
#undef G0054A930
#define G0054A930 (*(int32_t *)re_gvar(0x0054a930u, sizeof(int32_t), (void *)&G0054A930))
#undef G0054A940
#define G0054A940 (*(int32_t *)re_gvar(0x0054a940u, sizeof(int32_t), (void *)&G0054A940))
#undef G0054A950
#define G0054A950 (*(int32_t *)re_gvar(0x0054a950u, sizeof(int32_t), (void *)&G0054A950))
#undef G0054AA24
#define G0054AA24 (*(int32_t *)re_gvar(0x0054aa24u, sizeof(int32_t), (void *)&G0054AA24))
#undef G0054AA28
#define G0054AA28 (*(int32_t *)re_gvar(0x0054aa28u, sizeof(int32_t), (void *)&G0054AA28))
#undef G0054AA2C
#define G0054AA2C (*(uint8_t *)re_gvar(0x0054aa2cu, sizeof(uint8_t), (void *)&G0054AA2C))
#undef G0054AA2D
#define G0054AA2D (*(uint8_t *)re_gvar(0x0054aa2du, sizeof(uint8_t), (void *)&G0054AA2D))
#undef G0054AA2E
#define G0054AA2E (*(uint8_t *)re_gvar(0x0054aa2eu, sizeof(uint8_t), (void *)&G0054AA2E))
#undef G0054AA44
#define G0054AA44 (*(int32_t *)re_gvar(0x0054aa44u, sizeof(int32_t), (void *)&G0054AA44))
#undef G0054C6E8
#define G0054C6E8 (*(int32_t *)re_gvar(0x0054c6e8u, sizeof(int32_t), (void *)&G0054C6E8))
#undef G0054C6F8
#define G0054C6F8 (*(int32_t *)re_gvar(0x0054c6f8u, sizeof(int32_t), (void *)&G0054C6F8))
#undef G0054C958
#define G0054C958 (*(int32_t *)re_gvar(0x0054c958u, sizeof(int32_t), (void *)&G0054C958))
#undef G0054C968
#define G0054C968 (*(int32_t *)re_gvar(0x0054c968u, sizeof(int32_t), (void *)&G0054C968))
#undef G0054D100
#define G0054D100 (*(int32_t *)re_gvar(0x0054d100u, sizeof(int32_t), (void *)&G0054D100))
#undef G0054D110
#define G0054D110 (*(int32_t *)re_gvar(0x0054d110u, sizeof(int32_t), (void *)&G0054D110))
#undef G0054D120
#define G0054D120 (*(int32_t *)re_gvar(0x0054d120u, sizeof(int32_t), (void *)&G0054D120))
#undef G0054D1A8
#define G0054D1A8 (*(int32_t *)re_gvar(0x0054d1a8u, sizeof(int32_t), (void *)&G0054D1A8))
#undef G0054D1B8
#define G0054D1B8 (*(int32_t *)re_gvar(0x0054d1b8u, sizeof(int32_t), (void *)&G0054D1B8))
#undef G0054D1C8
#define G0054D1C8 (*(int32_t *)re_gvar(0x0054d1c8u, sizeof(int32_t), (void *)&G0054D1C8))
#undef G0054D1D8
#define G0054D1D8 (*(int32_t *)re_gvar(0x0054d1d8u, sizeof(int32_t), (void *)&G0054D1D8))
#undef G0054D1E8
#define G0054D1E8 (*(int32_t *)re_gvar(0x0054d1e8u, sizeof(int32_t), (void *)&G0054D1E8))
#undef G0054D298
#define G0054D298 (*(int32_t *)re_gvar(0x0054d298u, sizeof(int32_t), (void *)&G0054D298))
#undef G0054D2A8
#define G0054D2A8 (*(int32_t *)re_gvar(0x0054d2a8u, sizeof(int32_t), (void *)&G0054D2A8))
#undef G0054D2B8
#define G0054D2B8 (*(int32_t *)re_gvar(0x0054d2b8u, sizeof(int32_t), (void *)&G0054D2B8))
#undef G0054D2C8
#define G0054D2C8 (*(int32_t *)re_gvar(0x0054d2c8u, sizeof(int32_t), (void *)&G0054D2C8))
#undef G0054D2D8
#define G0054D2D8 (*(int32_t *)re_gvar(0x0054d2d8u, sizeof(int32_t), (void *)&G0054D2D8))
#undef G0054D2E8
#define G0054D2E8 (*(int32_t *)re_gvar(0x0054d2e8u, sizeof(int32_t), (void *)&G0054D2E8))
#undef G0054D3B0
#define G0054D3B0 (*(int32_t *)re_gvar(0x0054d3b0u, sizeof(int32_t), (void *)&G0054D3B0))
#undef G0054D3C0
#define G0054D3C0 (*(int32_t *)re_gvar(0x0054d3c0u, sizeof(int32_t), (void *)&G0054D3C0))
#undef G0054D3D0
#define G0054D3D0 (*(int32_t *)re_gvar(0x0054d3d0u, sizeof(int32_t), (void *)&G0054D3D0))
#undef G0054D3E0
#define G0054D3E0 (*(int32_t *)re_gvar(0x0054d3e0u, sizeof(int32_t), (void *)&G0054D3E0))
#undef G0054D3F0
#define G0054D3F0 (*(int32_t *)re_gvar(0x0054d3f0u, sizeof(int32_t), (void *)&G0054D3F0))
#undef G0054D400
#define G0054D400 (*(int32_t *)re_gvar(0x0054d400u, sizeof(int32_t), (void *)&G0054D400))
#undef G0054E16C
#define G0054E16C (*(int32_t *)re_gvar(0x0054e16cu, sizeof(int32_t), (void *)&G0054E16C))
#undef G0054E198
#define G0054E198 (*(int32_t *)re_gvar(0x0054e198u, sizeof(int32_t), (void *)&G0054E198))
#undef G0054E1A4
#define G0054E1A4 (*(uint8_t *)re_gvar(0x0054e1a4u, sizeof(uint8_t), (void *)&G0054E1A4))
#undef G0054E1A8
#define G0054E1A8 (*(int32_t *)re_gvar(0x0054e1a8u, sizeof(int32_t), (void *)&G0054E1A8))
#undef G0054E1B4
#define G0054E1B4 (*(uint8_t *)re_gvar(0x0054e1b4u, sizeof(uint8_t), (void *)&G0054E1B4))
#undef G0054E1B8
#define G0054E1B8 (*(int32_t *)re_gvar(0x0054e1b8u, sizeof(int32_t), (void *)&G0054E1B8))
#undef G0054E448
#define G0054E448 (*(int32_t *)re_gvar(0x0054e448u, sizeof(int32_t), (void *)&G0054E448))
#undef G0054E458
#define G0054E458 (*(int32_t *)re_gvar(0x0054e458u, sizeof(int32_t), (void *)&G0054E458))
#undef G0054E468
#define G0054E468 (*(int32_t *)re_gvar(0x0054e468u, sizeof(int32_t), (void *)&G0054E468))
#undef G0054E6A8
#define G0054E6A8 (*(int32_t *)re_gvar(0x0054e6a8u, sizeof(int32_t), (void *)&G0054E6A8))
#undef G0054E6B8
#define G0054E6B8 (*(int32_t *)re_gvar(0x0054e6b8u, sizeof(int32_t), (void *)&G0054E6B8))
#undef G0054E6C8
#define G0054E6C8 (*(int32_t *)re_gvar(0x0054e6c8u, sizeof(int32_t), (void *)&G0054E6C8))
#undef G0054E6D8
#define G0054E6D8 (*(int32_t *)re_gvar(0x0054e6d8u, sizeof(int32_t), (void *)&G0054E6D8))
#undef G0054E6E8
#define G0054E6E8 (*(int32_t *)re_gvar(0x0054e6e8u, sizeof(int32_t), (void *)&G0054E6E8))
#undef G00575550
#define G00575550 (*(int32_t *)re_gvar(0x00575550u, sizeof(int32_t), (void *)&G00575550))
#undef G00575554
#define G00575554 (*(int32_t *)re_gvar(0x00575554u, sizeof(int32_t), (void *)&G00575554))
#undef G005D77C0
#define G005D77C0 (*(uint8_t *)re_gvar(0x005d77c0u, sizeof(uint8_t), (void *)&G005D77C0))
#undef G005D77C1
#define G005D77C1 (*(uint8_t *)re_gvar(0x005d77c1u, sizeof(uint8_t), (void *)&G005D77C1))
#undef G005D77C4
#define G005D77C4 (*(int32_t *)re_gvar(0x005d77c4u, sizeof(int32_t), (void *)&G005D77C4))
#undef G005D77C8
#define G005D77C8 (*(int32_t *)re_gvar(0x005d77c8u, sizeof(int32_t), (void *)&G005D77C8))
#undef G005D77CC
#define G005D77CC (*(int32_t *)re_gvar(0x005d77ccu, sizeof(int32_t), (void *)&G005D77CC))
#undef G005F7E54
#define G005F7E54 (*(int32_t *)re_gvar(0x005f7e54u, sizeof(int32_t), (void *)&G005F7E54))
#undef G005FE850
#define G005FE850 (*(int32_t *)re_gvar(0x005fe850u, sizeof(int32_t), (void *)&G005FE850))
#undef G005FE92C
#define G005FE92C (*(int32_t *)re_gvar(0x005fe92cu, sizeof(int32_t), (void *)&G005FE92C))
#undef G00B31E40
#define G00B31E40 (*(uint8_t *)re_gvar(0x00b31e40u, sizeof(uint8_t), (void *)&G00B31E40))
#undef G00B31E41
#define G00B31E41 (*(uint8_t *)re_gvar(0x00b31e41u, sizeof(uint8_t), (void *)&G00B31E41))
#undef G00B31E42
#define G00B31E42 (*(uint8_t *)re_gvar(0x00b31e42u, sizeof(uint8_t), (void *)&G00B31E42))
#undef G00B31E43
#define G00B31E43 (*(uint8_t *)re_gvar(0x00b31e43u, sizeof(uint8_t), (void *)&G00B31E43))
#undef G00B5A730
#define G00B5A730 (*(int32_t *)re_gvar(0x00b5a730u, sizeof(int32_t), (void *)&G00B5A730))
#undef G00B5A734
#define G00B5A734 (*(int32_t *)re_gvar(0x00b5a734u, sizeof(int32_t), (void *)&G00B5A734))
#undef G00B5A738
#define G00B5A738 (*(int32_t *)re_gvar(0x00b5a738u, sizeof(int32_t), (void *)&G00B5A738))
#undef G00B5A73C
#define G00B5A73C (*(int32_t *)re_gvar(0x00b5a73cu, sizeof(int32_t), (void *)&G00B5A73C))
#undef G00B5A774
#define G00B5A774 (*(int32_t *)re_gvar(0x00b5a774u, sizeof(int32_t), (void *)&G00B5A774))
#undef G00B5A8CD
#define G00B5A8CD (*(uint8_t *)re_gvar(0x00b5a8cdu, sizeof(uint8_t), (void *)&G00B5A8CD))
#undef G00B5C858
#define G00B5C858 (*(int32_t *)re_gvar(0x00b5c858u, sizeof(int32_t), (void *)&G00B5C858))
#undef G00B5C85C
#define G00B5C85C (*(int32_t *)re_gvar(0x00b5c85cu, sizeof(int32_t), (void *)&G00B5C85C))
#undef G00B5C860
#define G00B5C860 (*(int32_t *)re_gvar(0x00b5c860u, sizeof(int32_t), (void *)&G00B5C860))
#undef G00B5C864
#define G00B5C864 (*(int32_t *)re_gvar(0x00b5c864u, sizeof(int32_t), (void *)&G00B5C864))
#undef G00B5C868
#define G00B5C868 (*(int32_t *)re_gvar(0x00b5c868u, sizeof(int32_t), (void *)&G00B5C868))
#undef G00B5C86C
#define G00B5C86C (*(int32_t *)re_gvar(0x00b5c86cu, sizeof(int32_t), (void *)&G00B5C86C))
#undef G00B5C870
#define G00B5C870 (*(int32_t *)re_gvar(0x00b5c870u, sizeof(int32_t), (void *)&G00B5C870))
#undef G00B5C874
#define G00B5C874 (*(int32_t *)re_gvar(0x00b5c874u, sizeof(int32_t), (void *)&G00B5C874))
#undef G00B5C878
#define G00B5C878 (*(int32_t *)re_gvar(0x00b5c878u, sizeof(int32_t), (void *)&G00B5C878))
#undef G00B5C87C
#define G00B5C87C (*(int32_t *)re_gvar(0x00b5c87cu, sizeof(int32_t), (void *)&G00B5C87C))
#undef G00B5C880
#define G00B5C880 (*(int32_t *)re_gvar(0x00b5c880u, sizeof(int32_t), (void *)&G00B5C880))
#undef G00B5C884
#define G00B5C884 (*(int32_t *)re_gvar(0x00b5c884u, sizeof(int32_t), (void *)&G00B5C884))
#undef G00B5C888
#define G00B5C888 (*(int32_t *)re_gvar(0x00b5c888u, sizeof(int32_t), (void *)&G00B5C888))
#undef G00B5C88C
#define G00B5C88C (*(int32_t *)re_gvar(0x00b5c88cu, sizeof(int32_t), (void *)&G00B5C88C))
#undef G00B5C890
#define G00B5C890 (*(int32_t *)re_gvar(0x00b5c890u, sizeof(int32_t), (void *)&G00B5C890))
#undef G00B5C894
#define G00B5C894 (*(int32_t *)re_gvar(0x00b5c894u, sizeof(int32_t), (void *)&G00B5C894))
#undef G00B5C910
#define G00B5C910 (*(int32_t *)re_gvar(0x00b5c910u, sizeof(int32_t), (void *)&G00B5C910))
#undef G00B5C914
#define G00B5C914 (*(int32_t *)re_gvar(0x00b5c914u, sizeof(int32_t), (void *)&G00B5C914))
#undef G00B5C918
#define G00B5C918 (*(int32_t *)re_gvar(0x00b5c918u, sizeof(int32_t), (void *)&G00B5C918))
#undef G00B5C91C
#define G00B5C91C (*(int32_t *)re_gvar(0x00b5c91cu, sizeof(int32_t), (void *)&G00B5C91C))
#undef G00B5C920
#define G00B5C920 (*(int32_t *)re_gvar(0x00b5c920u, sizeof(int32_t), (void *)&G00B5C920))
#undef G00B5C924
#define G00B5C924 (*(int32_t *)re_gvar(0x00b5c924u, sizeof(int32_t), (void *)&G00B5C924))
#undef G00B5C928
#define G00B5C928 (*(int32_t *)re_gvar(0x00b5c928u, sizeof(int32_t), (void *)&G00B5C928))
#undef G00B5C92C
#define G00B5C92C (*(int32_t *)re_gvar(0x00b5c92cu, sizeof(int32_t), (void *)&G00B5C92C))
#undef G00B5C930
#define G00B5C930 (*(int32_t *)re_gvar(0x00b5c930u, sizeof(int32_t), (void *)&G00B5C930))
#undef G00B5C934
#define G00B5C934 (*(int32_t *)re_gvar(0x00b5c934u, sizeof(int32_t), (void *)&G00B5C934))
#undef G00B5C938
#define G00B5C938 (*(int32_t *)re_gvar(0x00b5c938u, sizeof(int32_t), (void *)&G00B5C938))
#undef G00B5C93C
#define G00B5C93C (*(int32_t *)re_gvar(0x00b5c93cu, sizeof(int32_t), (void *)&G00B5C93C))
#undef G00B5C940
#define G00B5C940 (*(int32_t *)re_gvar(0x00b5c940u, sizeof(int32_t), (void *)&G00B5C940))
#undef G00B5C944
#define G00B5C944 (*(int32_t *)re_gvar(0x00b5c944u, sizeof(int32_t), (void *)&G00B5C944))
#undef G00B5C948
#define G00B5C948 (*(int32_t *)re_gvar(0x00b5c948u, sizeof(int32_t), (void *)&G00B5C948))
#undef G00B5C94C
#define G00B5C94C (*(int32_t *)re_gvar(0x00b5c94cu, sizeof(int32_t), (void *)&G00B5C94C))
#undef G00BF1C20
#define G00BF1C20 (*(uint8_t *)re_gvar(0x00bf1c20u, sizeof(uint8_t), (void *)&G00BF1C20))
#undef G00C29D80
#define G00C29D80 (*(uint8_t *)re_gvar(0x00c29d80u, sizeof(uint8_t), (void *)&G00C29D80))
#undef G00C29D81
#define G00C29D81 (*(uint8_t *)re_gvar(0x00c29d81u, sizeof(uint8_t), (void *)&G00C29D81))
#undef G00C4BDC4
#define G00C4BDC4 (*(int32_t *)re_gvar(0x00c4bdc4u, sizeof(int32_t), (void *)&G00C4BDC4))
#undef G00C5582C
#define G00C5582C (*(int32_t *)re_gvar(0x00c5582cu, sizeof(int32_t), (void *)&G00C5582C))
#undef G00C55830
#define G00C55830 (*(int32_t *)re_gvar(0x00c55830u, sizeof(int32_t), (void *)&G00C55830))
#undef G00C55878
#define G00C55878 (*(int32_t *)re_gvar(0x00c55878u, sizeof(int32_t), (void *)&G00C55878))
#undef G00C5587C
#define G00C5587C (*(int32_t *)re_gvar(0x00c5587cu, sizeof(int32_t), (void *)&G00C5587C))
#undef G00C55880
#define G00C55880 (*(int32_t *)re_gvar(0x00c55880u, sizeof(int32_t), (void *)&G00C55880))
#undef G00C55884
#define G00C55884 (*(int32_t *)re_gvar(0x00c55884u, sizeof(int32_t), (void *)&G00C55884))
#undef G00C558B4
#define G00C558B4 (*(int32_t *)re_gvar(0x00c558b4u, sizeof(int32_t), (void *)&G00C558B4))
#undef G00C558B8
#define G00C558B8 (*(int32_t *)re_gvar(0x00c558b8u, sizeof(int32_t), (void *)&G00C558B8))
#undef G00C558BC
#define G00C558BC (*(int32_t *)re_gvar(0x00c558bcu, sizeof(int32_t), (void *)&G00C558BC))
#undef G00C558C0
#define G00C558C0 (*(int32_t *)re_gvar(0x00c558c0u, sizeof(int32_t), (void *)&G00C558C0))
#undef G00C558C4
#define G00C558C4 (*(int32_t *)re_gvar(0x00c558c4u, sizeof(int32_t), (void *)&G00C558C4))
#undef G00C55984
#define G00C55984 (*(int32_t *)re_gvar(0x00c55984u, sizeof(int32_t), (void *)&G00C55984))
#undef G00C55988
#define G00C55988 (*(int32_t *)re_gvar(0x00c55988u, sizeof(int32_t), (void *)&G00C55988))
#undef G00C5598C
#define G00C5598C (*(int32_t *)re_gvar(0x00c5598cu, sizeof(int32_t), (void *)&G00C5598C))
#undef G00C55990
#define G00C55990 (*(int32_t *)re_gvar(0x00c55990u, sizeof(int32_t), (void *)&G00C55990))
#undef G00C55994
#define G00C55994 (*(int32_t *)re_gvar(0x00c55994u, sizeof(int32_t), (void *)&G00C55994))
#undef G00C55998
#define G00C55998 (*(int32_t *)re_gvar(0x00c55998u, sizeof(int32_t), (void *)&G00C55998))
#undef G00C5599C
#define G00C5599C (*(int32_t *)re_gvar(0x00c5599cu, sizeof(int32_t), (void *)&G00C5599C))
#undef G00C559A0
#define G00C559A0 (*(int32_t *)re_gvar(0x00c559a0u, sizeof(int32_t), (void *)&G00C559A0))
#undef G00C559B4
#define G00C559B4 (*(int32_t *)re_gvar(0x00c559b4u, sizeof(int32_t), (void *)&G00C559B4))
#undef G00C559B8
#define G00C559B8 (*(int32_t *)re_gvar(0x00c559b8u, sizeof(int32_t), (void *)&G00C559B8))
#undef G00C559BC
#define G00C559BC (*(int32_t *)re_gvar(0x00c559bcu, sizeof(int32_t), (void *)&G00C559BC))
#undef G00C559C0
#define G00C559C0 (*(int32_t *)re_gvar(0x00c559c0u, sizeof(int32_t), (void *)&G00C559C0))
#undef G00C559C4
#define G00C559C4 (*(int32_t *)re_gvar(0x00c559c4u, sizeof(int32_t), (void *)&G00C559C4))
#undef G00C559C8
#define G00C559C8 (*(int32_t *)re_gvar(0x00c559c8u, sizeof(int32_t), (void *)&G00C559C8))
#undef G00C559CC
#define G00C559CC (*(int32_t *)re_gvar(0x00c559ccu, sizeof(int32_t), (void *)&G00C559CC))
#undef G00C559D0
#define G00C559D0 (*(int32_t *)re_gvar(0x00c559d0u, sizeof(int32_t), (void *)&G00C559D0))
#undef G00C559D4
#define G00C559D4 (*(int32_t *)re_gvar(0x00c559d4u, sizeof(int32_t), (void *)&G00C559D4))
#undef G00C55A5C
#define G00C55A5C (*(int32_t *)re_gvar(0x00c55a5cu, sizeof(int32_t), (void *)&G00C55A5C))
#undef G00C81988
#define G00C81988 (*(int32_t *)re_gvar(0x00c81988u, sizeof(int32_t), (void *)&G00C81988))
#undef G00C8198C
#define G00C8198C (*(int32_t *)re_gvar(0x00c8198cu, sizeof(int32_t), (void *)&G00C8198C))
#undef G00D12408
#define G00D12408 (*(int32_t *)re_gvar(0x00d12408u, sizeof(int32_t), (void *)&G00D12408))
#undef G00D12418
#define G00D12418 (*(int32_t *)re_gvar(0x00d12418u, sizeof(int32_t), (void *)&G00D12418))
#undef G00D1241C
#define G00D1241C (*(int32_t *)re_gvar(0x00d1241cu, sizeof(int32_t), (void *)&G00D1241C))
#undef G00D14EEC
#define G00D14EEC (*(int32_t *)re_gvar(0x00d14eecu, sizeof(int32_t), (void *)&G00D14EEC))
#undef G00D14EF4
#define G00D14EF4 (*(int32_t *)re_gvar(0x00d14ef4u, sizeof(int32_t), (void *)&G00D14EF4))
#undef G00D164F0
#define G00D164F0 (*(uint8_t *)re_gvar(0x00d164f0u, sizeof(uint8_t), (void *)&G00D164F0))
#undef G00D17AE4
#define G00D17AE4 (*(uint8_t *)re_gvar(0x00d17ae4u, sizeof(uint8_t), (void *)&G00D17AE4))
#undef G00D17B04
#define G00D17B04 (*(uint8_t *)re_gvar(0x00d17b04u, sizeof(uint8_t), (void *)&G00D17B04))
#undef G00D17B08
#define G00D17B08 (*(int32_t *)re_gvar(0x00d17b08u, sizeof(int32_t), (void *)&G00D17B08))
#undef G00D17B10
#define G00D17B10 (*(uint8_t *)re_gvar(0x00d17b10u, sizeof(uint8_t), (void *)&G00D17B10))
#undef G00D17B1C
#define G00D17B1C (*(int32_t *)re_gvar(0x00d17b1cu, sizeof(int32_t), (void *)&G00D17B1C))
#undef G00D17B20
#define G00D17B20 (*(uint8_t *)re_gvar(0x00d17b20u, sizeof(uint8_t), (void *)&G00D17B20))
#undef G00D17B21
#define G00D17B21 (*(uint8_t *)re_gvar(0x00d17b21u, sizeof(uint8_t), (void *)&G00D17B21))
#undef G010DE220
#define G010DE220 (*(int32_t *)re_gvar(0x010de220u, sizeof(int32_t), (void *)&G010DE220))
#undef G010DE224
#define G010DE224 (*(int32_t *)re_gvar(0x010de224u, sizeof(int32_t), (void *)&G010DE224))
#undef G010DE228
#define G010DE228 (*(int32_t *)re_gvar(0x010de228u, sizeof(int32_t), (void *)&G010DE228))
#undef G010DE22C
#define G010DE22C (*(int32_t *)re_gvar(0x010de22cu, sizeof(int32_t), (void *)&G010DE22C))
#undef G010FFA20
#define G010FFA20 (*(int32_t *)re_gvar(0x010ffa20u, sizeof(int32_t), (void *)&G010FFA20))
#undef G010FFB40
#define G010FFB40 (*(int32_t *)re_gvar(0x010ffb40u, sizeof(int32_t), (void *)&G010FFB40))
#undef G010FFD04
#define G010FFD04 (*(int32_t *)re_gvar(0x010ffd04u, sizeof(int32_t), (void *)&G010FFD04))
#undef G010FFD08
#define G010FFD08 (*(int32_t *)re_gvar(0x010ffd08u, sizeof(int32_t), (void *)&G010FFD08))
#undef G01105D60
#define G01105D60 (*(int32_t *)re_gvar(0x01105d60u, sizeof(int32_t), (void *)&G01105D60))
#undef G0110B24C
#define G0110B24C (*(int32_t *)re_gvar(0x0110b24cu, sizeof(int32_t), (void *)&G0110B24C))
#undef G01129580
#define G01129580 (*(int32_t *)re_gvar(0x01129580u, sizeof(int32_t), (void *)&G01129580))
#undef G0113A6C0
#define G0113A6C0 (*(int32_t *)re_gvar(0x0113a6c0u, sizeof(int32_t), (void *)&G0113A6C0))
#undef G011426F8
#define G011426F8 (*(int32_t *)re_gvar(0x011426f8u, sizeof(int32_t), (void *)&G011426F8))
#undef G01144284
#define G01144284 (*(int32_t *)re_gvar(0x01144284u, sizeof(int32_t), (void *)&G01144284))
#undef G011EFFE4
#define G011EFFE4 (*(int32_t *)re_gvar(0x011effe4u, sizeof(int32_t), (void *)&G011EFFE4))
#endif
/* gvar-img v2.03 end */
