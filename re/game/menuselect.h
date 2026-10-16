/* Menu select/leave handlers: переключение подсветки пунктов меню. */
#pragma once
#include "menugfx.h"
#include "menutab.h"
#include "menustate.h"
#include "gvar.h"
#define MenuB00549F8C GAME_VAR(uint8_t, MenuB00549F8C, 0x00549f8c)
#define MenuB00549F9C GAME_VAR(uint8_t, MenuB00549F9C, 0x00549f9c)
#define MenuB00549FBC GAME_VAR(uint8_t, MenuB00549FBC, 0x00549fbc)
#define MenuB00549FCC GAME_VAR(uint8_t, MenuB00549FCC, 0x00549fcc)
#define MenuB00549FDC GAME_VAR(uint8_t, MenuB00549FDC, 0x00549fdc)
#define MenuB00549FEC GAME_VAR(uint8_t, MenuB00549FEC, 0x00549fec)
#define MenuI0054A060 GAME_VAR(int32_t, MenuI0054A060, 0x0054a060)
#define MenuB0054A254 MENUGFX_VAR(uint8_t, MenuB0054A254, 0x0054a254)
#define MenuB0054A264 MENUGFX_VAR(uint8_t, MenuB0054A264, 0x0054a264)
#define MenuB0054A274 MENUGFX_VAR(uint8_t, MenuB0054A274, 0x0054a274)
#define MenuB0054A284 MENUGFX_VAR(uint8_t, MenuB0054A284, 0x0054a284)
#define MenuB0054A294 MENUGFX_VAR(uint8_t, MenuB0054A294, 0x0054a294)
#define MenuB0054A2A4 MENUGFX_VAR(uint8_t, MenuB0054A2A4, 0x0054a2a4)
#define MenuB0054A2B4 MENUGFX_VAR(uint8_t, MenuB0054A2B4, 0x0054a2b4)
#define MenuB0054A2C4 MENUGFX_VAR(uint8_t, MenuB0054A2C4, 0x0054a2c4)
#define MenuB0054A2D4 MENUGFX_VAR(uint8_t, MenuB0054A2D4, 0x0054a2d4)
#define MenuB0054A2E4 MENUGFX_VAR(uint8_t, MenuB0054A2E4, 0x0054a2e4)
#define MenuB0054A2F4 MENUGFX_VAR(uint8_t, MenuB0054A2F4, 0x0054a2f4)
#define MenuB0054A304 MENUGFX_VAR(uint8_t, MenuB0054A304, 0x0054a304)
#define MenuB0054A314 MENUGFX_VAR(uint8_t, MenuB0054A314, 0x0054a314)
#define MenuB0054A324 MENUGFX_VAR(uint8_t, MenuB0054A324, 0x0054a324)
#define MenuB0054A334 MENUGFX_VAR(uint8_t, MenuB0054A334, 0x0054a334)
#define MenuB0054A344 MENUGFX_VAR(uint8_t, MenuB0054A344, 0x0054a344)
#define MenuB0054A354 MENUGFX_VAR(uint8_t, MenuB0054A354, 0x0054a354)
#define MenuB0054A364 MENUGFX_VAR(uint8_t, MenuB0054A364, 0x0054a364)
#define MenuB0054A374 MENUGFX_VAR(uint8_t, MenuB0054A374, 0x0054a374)
#define MenuB0054A384 MENUGFX_VAR(uint8_t, MenuB0054A384, 0x0054a384)
#define MenuB0054A394 MENUGFX_VAR(uint8_t, MenuB0054A394, 0x0054a394)
#define MenuB0054A3A4 MENUGFX_VAR(uint8_t, MenuB0054A3A4, 0x0054a3a4)
#define MenuB0054A3B4 MENUGFX_VAR(uint8_t, MenuB0054A3B4, 0x0054a3b4)
#define MenuB0054A3C4 MENUGFX_VAR(uint8_t, MenuB0054A3C4, 0x0054a3c4)
#define MenuB0054A3D4 MENUGFX_VAR(uint8_t, MenuB0054A3D4, 0x0054a3d4)
#define MenuB0054A3E4 MENUGFX_VAR(uint8_t, MenuB0054A3E4, 0x0054a3e4)
#define MenuB0054A3F4 MENUGFX_VAR(uint8_t, MenuB0054A3F4, 0x0054a3f4)
#define MenuB0054A404 MENUGFX_VAR(uint8_t, MenuB0054A404, 0x0054a404)
#define MenuB0054A414 MENUGFX_VAR(uint8_t, MenuB0054A414, 0x0054a414)
#define MenuB0054A424 MENUGFX_VAR(uint8_t, MenuB0054A424, 0x0054a424)
#define MenuB0054A434 MENUGFX_VAR(uint8_t, MenuB0054A434, 0x0054a434)
#define MenuB0054A444 MENUGFX_VAR(uint8_t, MenuB0054A444, 0x0054a444)
#define MenuB0054A454 MENUGFX_VAR(uint8_t, MenuB0054A454, 0x0054a454)
#define MenuI0054A694 MENUGFX_VAR(int32_t, MenuI0054A694, 0x0054a694)
#define MenuB0054C044 GAME_VAR(uint8_t, MenuB0054C044, 0x0054c044)
#define MenuB0054C054 GAME_VAR(uint8_t, MenuB0054C054, 0x0054c054)
#define MenuB0054C064 GAME_VAR(uint8_t, MenuB0054C064, 0x0054c064)
#define MenuB0054C074 GAME_VAR(uint8_t, MenuB0054C074, 0x0054c074)
#define MenuB0054C084 GAME_VAR(uint8_t, MenuB0054C084, 0x0054c084)
#define MenuB0054C094 GAME_VAR(uint8_t, MenuB0054C094, 0x0054c094)
#define MenuB0054C0A4 GAME_VAR(uint8_t, MenuB0054C0A4, 0x0054c0a4)
#define MenuB0054C0B4 GAME_VAR(uint8_t, MenuB0054C0B4, 0x0054c0b4)
#define MenuB0054C0C4 GAME_VAR(uint8_t, MenuB0054C0C4, 0x0054c0c4)
#define MenuB0054C0D4 GAME_VAR(uint8_t, MenuB0054C0D4, 0x0054c0d4)
#define MenuB0054C0E4 GAME_VAR(uint8_t, MenuB0054C0E4, 0x0054c0e4)
#define MenuB0054C0F4 GAME_VAR(uint8_t, MenuB0054C0F4, 0x0054c0f4)
#define MenuB0054C104 GAME_VAR(uint8_t, MenuB0054C104, 0x0054c104)
#define MenuB0054C114 GAME_VAR(uint8_t, MenuB0054C114, 0x0054c114)
#define MenuB0054C124 GAME_VAR(uint8_t, MenuB0054C124, 0x0054c124)
#define MenuB0054C134 GAME_VAR(uint8_t, MenuB0054C134, 0x0054c134)
#define MenuB0054C144 GAME_VAR(uint8_t, MenuB0054C144, 0x0054c144)
#define MenuB0054C154 GAME_VAR(uint8_t, MenuB0054C154, 0x0054c154)
#define MenuB0054C164 GAME_VAR(uint8_t, MenuB0054C164, 0x0054c164)
#define MenuB0054C174 GAME_VAR(uint8_t, MenuB0054C174, 0x0054c174)
#define MenuB0054C184 GAME_VAR(uint8_t, MenuB0054C184, 0x0054c184)
#define MenuB0054C194 GAME_VAR(uint8_t, MenuB0054C194, 0x0054c194)
#define MenuB0054C1A4 GAME_VAR(uint8_t, MenuB0054C1A4, 0x0054c1a4)
#define MenuB0054C1B4 GAME_VAR(uint8_t, MenuB0054C1B4, 0x0054c1b4)
#define MenuB0054C364 GAME_VAR(uint8_t, MenuB0054C364, 0x0054c364)
#define MenuB0054C374 GAME_VAR(uint8_t, MenuB0054C374, 0x0054c374)
#define MenuB0054C384 GAME_VAR(uint8_t, MenuB0054C384, 0x0054c384)
#define MenuB0054C394 GAME_VAR(uint8_t, MenuB0054C394, 0x0054c394)
#define MenuB0054C3A4 GAME_VAR(uint8_t, MenuB0054C3A4, 0x0054c3a4)
#define MenuB0054C3B4 GAME_VAR(uint8_t, MenuB0054C3B4, 0x0054c3b4)
#define MenuB0054C3C4 GAME_VAR(uint8_t, MenuB0054C3C4, 0x0054c3c4)
#define MenuB0054C3D4 GAME_VAR(uint8_t, MenuB0054C3D4, 0x0054c3d4)
#define MenuB0054C3E4 GAME_VAR(uint8_t, MenuB0054C3E4, 0x0054c3e4)
#define MenuB0054C3F4 GAME_VAR(uint8_t, MenuB0054C3F4, 0x0054c3f4)
#define MenuB0054C404 GAME_VAR(uint8_t, MenuB0054C404, 0x0054c404)
#define MenuB0054C414 GAME_VAR(uint8_t, MenuB0054C414, 0x0054c414)
#define MenuB0054C424 GAME_VAR(uint8_t, MenuB0054C424, 0x0054c424)
#define MenuB0054C434 GAME_VAR(uint8_t, MenuB0054C434, 0x0054c434)
#define MenuB0054C444 GAME_VAR(uint8_t, MenuB0054C444, 0x0054c444)
#define MenuB0054C454 GAME_VAR(uint8_t, MenuB0054C454, 0x0054c454)
#define MenuB0054C464 GAME_VAR(uint8_t, MenuB0054C464, 0x0054c464)
#define MenuB0054C474 GAME_VAR(uint8_t, MenuB0054C474, 0x0054c474)
#define MenuB0054C484 GAME_VAR(uint8_t, MenuB0054C484, 0x0054c484)
#define MenuB0054C494 GAME_VAR(uint8_t, MenuB0054C494, 0x0054c494)
#define MenuB0054C4A4 GAME_VAR(uint8_t, MenuB0054C4A4, 0x0054c4a4)
#define MenuB0054C4B4 GAME_VAR(uint8_t, MenuB0054C4B4, 0x0054c4b4)
#define MenuB0054C4C4 GAME_VAR(uint8_t, MenuB0054C4C4, 0x0054c4c4)
#define MenuB0054C4D4 GAME_VAR(uint8_t, MenuB0054C4D4, 0x0054c4d4)
#define MenuB0054C4E4 GAME_VAR(uint8_t, MenuB0054C4E4, 0x0054c4e4)
#define MenuB0054C4F4 GAME_VAR(uint8_t, MenuB0054C4F4, 0x0054c4f4)
#define MenuB0054C504 GAME_VAR(uint8_t, MenuB0054C504, 0x0054c504)
#define MenuB0054C514 GAME_VAR(uint8_t, MenuB0054C514, 0x0054c514)
#define MenuB0054D1B4 GAME_VAR(uint8_t, MenuB0054D1B4, 0x0054d1b4)
#define MenuB0054D1C4 GAME_VAR(uint8_t, MenuB0054D1C4, 0x0054d1c4)
#define MenuB0054D1D4 GAME_VAR(uint8_t, MenuB0054D1D4, 0x0054d1d4)
#define MenuB0054D1E4 GAME_VAR(uint8_t, MenuB0054D1E4, 0x0054d1e4)
#define MenuB0054D2A4 GAME_VAR(uint8_t, MenuB0054D2A4, 0x0054d2a4)
#define MenuB0054D2B4 GAME_VAR(uint8_t, MenuB0054D2B4, 0x0054d2b4)
#define MenuB0054D2C4 GAME_VAR(uint8_t, MenuB0054D2C4, 0x0054d2c4)
#define MenuB0054D2D4 GAME_VAR(uint8_t, MenuB0054D2D4, 0x0054d2d4)
#define MenuB0054D2E4 GAME_VAR(uint8_t, MenuB0054D2E4, 0x0054d2e4)
#define MenuB0054D3BC GAME_VAR(uint8_t, MenuB0054D3BC, 0x0054d3bc)
#define MenuB0054D3CC GAME_VAR(uint8_t, MenuB0054D3CC, 0x0054d3cc)
#define MenuB0054D3DC GAME_VAR(uint8_t, MenuB0054D3DC, 0x0054d3dc)
#define MenuB0054D3EC GAME_VAR(uint8_t, MenuB0054D3EC, 0x0054d3ec)
#define MenuB0054D3FC GAME_VAR(uint8_t, MenuB0054D3FC, 0x0054d3fc)
#define MenuB0054DBC4 MENUTAB_VAR(uint8_t, MenuB0054DBC4, 0x0054dbc4)
#define MenuB0054DBD4 MENUTAB_VAR(uint8_t, MenuB0054DBD4, 0x0054dbd4)
#define MenuB0054DBE4 MENUTAB_VAR(uint8_t, MenuB0054DBE4, 0x0054dbe4)
#define MenuB0054DBF4 MENUTAB_VAR(uint8_t, MenuB0054DBF4, 0x0054dbf4)
#define MenuB0054DC04 MENUTAB_VAR(uint8_t, MenuB0054DC04, 0x0054dc04)
#define MenuB0054DC14 MENUTAB_VAR(uint8_t, MenuB0054DC14, 0x0054dc14)
#define MenuB0054DC24 MENUTAB_VAR(uint8_t, MenuB0054DC24, 0x0054dc24)
#define MenuB0054DC34 MENUTAB_VAR(uint8_t, MenuB0054DC34, 0x0054dc34)
#define MenuB0054DC44 MENUTAB_VAR(uint8_t, MenuB0054DC44, 0x0054dc44)
#define MenuB0054DC54 MENUTAB_VAR(uint8_t, MenuB0054DC54, 0x0054dc54)
#define MenuB0054DC64 MENUTAB_VAR(uint8_t, MenuB0054DC64, 0x0054dc64)
#define MenuB0054DC74 MENUTAB_VAR(uint8_t, MenuB0054DC74, 0x0054dc74)
#define MenuB0054DC84 MENUTAB_VAR(uint8_t, MenuB0054DC84, 0x0054dc84)
#define MenuB0054DC94 MENUTAB_VAR(uint8_t, MenuB0054DC94, 0x0054dc94)
#define MenuB0054DCA4 MENUTAB_VAR(uint8_t, MenuB0054DCA4, 0x0054dca4)
#define MenuB0054DCB4 MENUTAB_VAR(uint8_t, MenuB0054DCB4, 0x0054dcb4)
#define MenuB0054DCC4 MENUTAB_VAR(uint8_t, MenuB0054DCC4, 0x0054dcc4)
#define MenuB0054DCD4 MENUTAB_VAR(uint8_t, MenuB0054DCD4, 0x0054dcd4)
#define MenuB0054DCE4 MENUTAB_VAR(uint8_t, MenuB0054DCE4, 0x0054dce4)
#define MenuB0054DCF4 MENUTAB_VAR(uint8_t, MenuB0054DCF4, 0x0054dcf4)
#define MenuI0054DE08 MENUTAB_VAR(int32_t, MenuI0054DE08, 0x0054de08)
#define MenuB0054DFD4 GAME_VAR(uint8_t, MenuB0054DFD4, 0x0054dfd4)
#define MenuB0054DFE4 GAME_VAR(uint8_t, MenuB0054DFE4, 0x0054dfe4)
#define MenuB0054DFF4 GAME_VAR(uint8_t, MenuB0054DFF4, 0x0054dff4)
#define MenuB0054E004 GAME_VAR(uint8_t, MenuB0054E004, 0x0054e004)
#define MenuB0054E1A4 GAME_VAR(uint8_t, MenuB0054E1A4, 0x0054e1a4)
#define MenuB0054E1B4 GAME_VAR(uint8_t, MenuB0054E1B4, 0x0054e1b4)
#define MenuI0057B730 GAME_VAR(int32_t, MenuI0057B730, 0x0057b730)
#define MenuI005D578C GAME_VAR(int32_t, MenuI005D578C, 0x005d578c)
#define MenuI005FE770 GAME_VAR(int32_t, MenuI005FE770, 0x005fe770)
#define MenuI005FE774 GAME_VAR(int32_t, MenuI005FE774, 0x005fe774)
#define MenuI005FE798 GAME_VAR(int32_t, MenuI005FE798, 0x005fe798)
#define MenuI005FE79C GAME_VAR(int32_t, MenuI005FE79C, 0x005fe79c)
#define MenuI005FE9D0 GAME_VAR(int32_t, MenuI005FE9D0, 0x005fe9d0)
#ifndef RE_HOOK_BUILD
#pragma push_macro("MenuB00549F8C") /*gvi*/
#undef MenuB00549F8C /*gvi*/
extern uint8_t MenuB00549F8C;
#pragma pop_macro("MenuB00549F8C") /*gvi*/
#pragma push_macro("MenuB00549F9C") /*gvi*/
#undef MenuB00549F9C /*gvi*/
extern uint8_t MenuB00549F9C;
#pragma pop_macro("MenuB00549F9C") /*gvi*/
#pragma push_macro("MenuB00549FBC") /*gvi*/
#undef MenuB00549FBC /*gvi*/
extern uint8_t MenuB00549FBC;
#pragma pop_macro("MenuB00549FBC") /*gvi*/
#pragma push_macro("MenuB00549FCC") /*gvi*/
#undef MenuB00549FCC /*gvi*/
extern uint8_t MenuB00549FCC;
#pragma pop_macro("MenuB00549FCC") /*gvi*/
#pragma push_macro("MenuB00549FDC") /*gvi*/
#undef MenuB00549FDC /*gvi*/
extern uint8_t MenuB00549FDC;
#pragma pop_macro("MenuB00549FDC") /*gvi*/
#pragma push_macro("MenuB00549FEC") /*gvi*/
#undef MenuB00549FEC /*gvi*/
extern uint8_t MenuB00549FEC;
#pragma pop_macro("MenuB00549FEC") /*gvi*/
#pragma push_macro("MenuI0054A060") /*gvi*/
#undef MenuI0054A060 /*gvi*/
extern int32_t MenuI0054A060;
#pragma pop_macro("MenuI0054A060") /*gvi*/
#pragma push_macro("MenuB0054C044") /*gvi*/
#undef MenuB0054C044 /*gvi*/
extern uint8_t MenuB0054C044;
#pragma pop_macro("MenuB0054C044") /*gvi*/
#pragma push_macro("MenuB0054C054") /*gvi*/
#undef MenuB0054C054 /*gvi*/
extern uint8_t MenuB0054C054;
#pragma pop_macro("MenuB0054C054") /*gvi*/
#pragma push_macro("MenuB0054C064") /*gvi*/
#undef MenuB0054C064 /*gvi*/
extern uint8_t MenuB0054C064;
#pragma pop_macro("MenuB0054C064") /*gvi*/
#pragma push_macro("MenuB0054C074") /*gvi*/
#undef MenuB0054C074 /*gvi*/
extern uint8_t MenuB0054C074;
#pragma pop_macro("MenuB0054C074") /*gvi*/
#pragma push_macro("MenuB0054C084") /*gvi*/
#undef MenuB0054C084 /*gvi*/
extern uint8_t MenuB0054C084;
#pragma pop_macro("MenuB0054C084") /*gvi*/
#pragma push_macro("MenuB0054C094") /*gvi*/
#undef MenuB0054C094 /*gvi*/
extern uint8_t MenuB0054C094;
#pragma pop_macro("MenuB0054C094") /*gvi*/
#pragma push_macro("MenuB0054C0A4") /*gvi*/
#undef MenuB0054C0A4 /*gvi*/
extern uint8_t MenuB0054C0A4;
#pragma pop_macro("MenuB0054C0A4") /*gvi*/
#pragma push_macro("MenuB0054C0B4") /*gvi*/
#undef MenuB0054C0B4 /*gvi*/
extern uint8_t MenuB0054C0B4;
#pragma pop_macro("MenuB0054C0B4") /*gvi*/
#pragma push_macro("MenuB0054C0C4") /*gvi*/
#undef MenuB0054C0C4 /*gvi*/
extern uint8_t MenuB0054C0C4;
#pragma pop_macro("MenuB0054C0C4") /*gvi*/
#pragma push_macro("MenuB0054C0D4") /*gvi*/
#undef MenuB0054C0D4 /*gvi*/
extern uint8_t MenuB0054C0D4;
#pragma pop_macro("MenuB0054C0D4") /*gvi*/
#pragma push_macro("MenuB0054C0E4") /*gvi*/
#undef MenuB0054C0E4 /*gvi*/
extern uint8_t MenuB0054C0E4;
#pragma pop_macro("MenuB0054C0E4") /*gvi*/
#pragma push_macro("MenuB0054C0F4") /*gvi*/
#undef MenuB0054C0F4 /*gvi*/
extern uint8_t MenuB0054C0F4;
#pragma pop_macro("MenuB0054C0F4") /*gvi*/
#pragma push_macro("MenuB0054C104") /*gvi*/
#undef MenuB0054C104 /*gvi*/
extern uint8_t MenuB0054C104;
#pragma pop_macro("MenuB0054C104") /*gvi*/
#pragma push_macro("MenuB0054C114") /*gvi*/
#undef MenuB0054C114 /*gvi*/
extern uint8_t MenuB0054C114;
#pragma pop_macro("MenuB0054C114") /*gvi*/
#pragma push_macro("MenuB0054C124") /*gvi*/
#undef MenuB0054C124 /*gvi*/
extern uint8_t MenuB0054C124;
#pragma pop_macro("MenuB0054C124") /*gvi*/
#pragma push_macro("MenuB0054C134") /*gvi*/
#undef MenuB0054C134 /*gvi*/
extern uint8_t MenuB0054C134;
#pragma pop_macro("MenuB0054C134") /*gvi*/
#pragma push_macro("MenuB0054C144") /*gvi*/
#undef MenuB0054C144 /*gvi*/
extern uint8_t MenuB0054C144;
#pragma pop_macro("MenuB0054C144") /*gvi*/
#pragma push_macro("MenuB0054C154") /*gvi*/
#undef MenuB0054C154 /*gvi*/
extern uint8_t MenuB0054C154;
#pragma pop_macro("MenuB0054C154") /*gvi*/
#pragma push_macro("MenuB0054C164") /*gvi*/
#undef MenuB0054C164 /*gvi*/
extern uint8_t MenuB0054C164;
#pragma pop_macro("MenuB0054C164") /*gvi*/
#pragma push_macro("MenuB0054C174") /*gvi*/
#undef MenuB0054C174 /*gvi*/
extern uint8_t MenuB0054C174;
#pragma pop_macro("MenuB0054C174") /*gvi*/
#pragma push_macro("MenuB0054C184") /*gvi*/
#undef MenuB0054C184 /*gvi*/
extern uint8_t MenuB0054C184;
#pragma pop_macro("MenuB0054C184") /*gvi*/
#pragma push_macro("MenuB0054C194") /*gvi*/
#undef MenuB0054C194 /*gvi*/
extern uint8_t MenuB0054C194;
#pragma pop_macro("MenuB0054C194") /*gvi*/
#pragma push_macro("MenuB0054C1A4") /*gvi*/
#undef MenuB0054C1A4 /*gvi*/
extern uint8_t MenuB0054C1A4;
#pragma pop_macro("MenuB0054C1A4") /*gvi*/
#pragma push_macro("MenuB0054C1B4") /*gvi*/
#undef MenuB0054C1B4 /*gvi*/
extern uint8_t MenuB0054C1B4;
#pragma pop_macro("MenuB0054C1B4") /*gvi*/
#pragma push_macro("MenuB0054C364") /*gvi*/
#undef MenuB0054C364 /*gvi*/
extern uint8_t MenuB0054C364;
#pragma pop_macro("MenuB0054C364") /*gvi*/
#pragma push_macro("MenuB0054C374") /*gvi*/
#undef MenuB0054C374 /*gvi*/
extern uint8_t MenuB0054C374;
#pragma pop_macro("MenuB0054C374") /*gvi*/
#pragma push_macro("MenuB0054C384") /*gvi*/
#undef MenuB0054C384 /*gvi*/
extern uint8_t MenuB0054C384;
#pragma pop_macro("MenuB0054C384") /*gvi*/
#pragma push_macro("MenuB0054C394") /*gvi*/
#undef MenuB0054C394 /*gvi*/
extern uint8_t MenuB0054C394;
#pragma pop_macro("MenuB0054C394") /*gvi*/
#pragma push_macro("MenuB0054C3A4") /*gvi*/
#undef MenuB0054C3A4 /*gvi*/
extern uint8_t MenuB0054C3A4;
#pragma pop_macro("MenuB0054C3A4") /*gvi*/
#pragma push_macro("MenuB0054C3B4") /*gvi*/
#undef MenuB0054C3B4 /*gvi*/
extern uint8_t MenuB0054C3B4;
#pragma pop_macro("MenuB0054C3B4") /*gvi*/
#pragma push_macro("MenuB0054C3C4") /*gvi*/
#undef MenuB0054C3C4 /*gvi*/
extern uint8_t MenuB0054C3C4;
#pragma pop_macro("MenuB0054C3C4") /*gvi*/
#pragma push_macro("MenuB0054C3D4") /*gvi*/
#undef MenuB0054C3D4 /*gvi*/
extern uint8_t MenuB0054C3D4;
#pragma pop_macro("MenuB0054C3D4") /*gvi*/
#pragma push_macro("MenuB0054C3E4") /*gvi*/
#undef MenuB0054C3E4 /*gvi*/
extern uint8_t MenuB0054C3E4;
#pragma pop_macro("MenuB0054C3E4") /*gvi*/
#pragma push_macro("MenuB0054C3F4") /*gvi*/
#undef MenuB0054C3F4 /*gvi*/
extern uint8_t MenuB0054C3F4;
#pragma pop_macro("MenuB0054C3F4") /*gvi*/
#pragma push_macro("MenuB0054C404") /*gvi*/
#undef MenuB0054C404 /*gvi*/
extern uint8_t MenuB0054C404;
#pragma pop_macro("MenuB0054C404") /*gvi*/
#pragma push_macro("MenuB0054C414") /*gvi*/
#undef MenuB0054C414 /*gvi*/
extern uint8_t MenuB0054C414;
#pragma pop_macro("MenuB0054C414") /*gvi*/
#pragma push_macro("MenuB0054C424") /*gvi*/
#undef MenuB0054C424 /*gvi*/
extern uint8_t MenuB0054C424;
#pragma pop_macro("MenuB0054C424") /*gvi*/
#pragma push_macro("MenuB0054C434") /*gvi*/
#undef MenuB0054C434 /*gvi*/
extern uint8_t MenuB0054C434;
#pragma pop_macro("MenuB0054C434") /*gvi*/
#pragma push_macro("MenuB0054C444") /*gvi*/
#undef MenuB0054C444 /*gvi*/
extern uint8_t MenuB0054C444;
#pragma pop_macro("MenuB0054C444") /*gvi*/
#pragma push_macro("MenuB0054C454") /*gvi*/
#undef MenuB0054C454 /*gvi*/
extern uint8_t MenuB0054C454;
#pragma pop_macro("MenuB0054C454") /*gvi*/
#pragma push_macro("MenuB0054C464") /*gvi*/
#undef MenuB0054C464 /*gvi*/
extern uint8_t MenuB0054C464;
#pragma pop_macro("MenuB0054C464") /*gvi*/
#pragma push_macro("MenuB0054C474") /*gvi*/
#undef MenuB0054C474 /*gvi*/
extern uint8_t MenuB0054C474;
#pragma pop_macro("MenuB0054C474") /*gvi*/
#pragma push_macro("MenuB0054C484") /*gvi*/
#undef MenuB0054C484 /*gvi*/
extern uint8_t MenuB0054C484;
#pragma pop_macro("MenuB0054C484") /*gvi*/
#pragma push_macro("MenuB0054C494") /*gvi*/
#undef MenuB0054C494 /*gvi*/
extern uint8_t MenuB0054C494;
#pragma pop_macro("MenuB0054C494") /*gvi*/
#pragma push_macro("MenuB0054C4A4") /*gvi*/
#undef MenuB0054C4A4 /*gvi*/
extern uint8_t MenuB0054C4A4;
#pragma pop_macro("MenuB0054C4A4") /*gvi*/
#pragma push_macro("MenuB0054C4B4") /*gvi*/
#undef MenuB0054C4B4 /*gvi*/
extern uint8_t MenuB0054C4B4;
#pragma pop_macro("MenuB0054C4B4") /*gvi*/
#pragma push_macro("MenuB0054C4C4") /*gvi*/
#undef MenuB0054C4C4 /*gvi*/
extern uint8_t MenuB0054C4C4;
#pragma pop_macro("MenuB0054C4C4") /*gvi*/
#pragma push_macro("MenuB0054C4D4") /*gvi*/
#undef MenuB0054C4D4 /*gvi*/
extern uint8_t MenuB0054C4D4;
#pragma pop_macro("MenuB0054C4D4") /*gvi*/
#pragma push_macro("MenuB0054C4E4") /*gvi*/
#undef MenuB0054C4E4 /*gvi*/
extern uint8_t MenuB0054C4E4;
#pragma pop_macro("MenuB0054C4E4") /*gvi*/
#pragma push_macro("MenuB0054C4F4") /*gvi*/
#undef MenuB0054C4F4 /*gvi*/
extern uint8_t MenuB0054C4F4;
#pragma pop_macro("MenuB0054C4F4") /*gvi*/
#pragma push_macro("MenuB0054C504") /*gvi*/
#undef MenuB0054C504 /*gvi*/
extern uint8_t MenuB0054C504;
#pragma pop_macro("MenuB0054C504") /*gvi*/
#pragma push_macro("MenuB0054C514") /*gvi*/
#undef MenuB0054C514 /*gvi*/
extern uint8_t MenuB0054C514;
#pragma pop_macro("MenuB0054C514") /*gvi*/
#pragma push_macro("MenuB0054D1B4") /*gvi*/
#undef MenuB0054D1B4 /*gvi*/
extern uint8_t MenuB0054D1B4;
#pragma pop_macro("MenuB0054D1B4") /*gvi*/
#pragma push_macro("MenuB0054D1C4") /*gvi*/
#undef MenuB0054D1C4 /*gvi*/
extern uint8_t MenuB0054D1C4;
#pragma pop_macro("MenuB0054D1C4") /*gvi*/
#pragma push_macro("MenuB0054D1D4") /*gvi*/
#undef MenuB0054D1D4 /*gvi*/
extern uint8_t MenuB0054D1D4;
#pragma pop_macro("MenuB0054D1D4") /*gvi*/
#pragma push_macro("MenuB0054D1E4") /*gvi*/
#undef MenuB0054D1E4 /*gvi*/
extern uint8_t MenuB0054D1E4;
#pragma pop_macro("MenuB0054D1E4") /*gvi*/
#pragma push_macro("MenuB0054D2A4") /*gvi*/
#undef MenuB0054D2A4 /*gvi*/
extern uint8_t MenuB0054D2A4;
#pragma pop_macro("MenuB0054D2A4") /*gvi*/
#pragma push_macro("MenuB0054D2B4") /*gvi*/
#undef MenuB0054D2B4 /*gvi*/
extern uint8_t MenuB0054D2B4;
#pragma pop_macro("MenuB0054D2B4") /*gvi*/
#pragma push_macro("MenuB0054D2C4") /*gvi*/
#undef MenuB0054D2C4 /*gvi*/
extern uint8_t MenuB0054D2C4;
#pragma pop_macro("MenuB0054D2C4") /*gvi*/
#pragma push_macro("MenuB0054D2D4") /*gvi*/
#undef MenuB0054D2D4 /*gvi*/
extern uint8_t MenuB0054D2D4;
#pragma pop_macro("MenuB0054D2D4") /*gvi*/
#pragma push_macro("MenuB0054D2E4") /*gvi*/
#undef MenuB0054D2E4 /*gvi*/
extern uint8_t MenuB0054D2E4;
#pragma pop_macro("MenuB0054D2E4") /*gvi*/
#pragma push_macro("MenuB0054D3BC") /*gvi*/
#undef MenuB0054D3BC /*gvi*/
extern uint8_t MenuB0054D3BC;
#pragma pop_macro("MenuB0054D3BC") /*gvi*/
#pragma push_macro("MenuB0054D3CC") /*gvi*/
#undef MenuB0054D3CC /*gvi*/
extern uint8_t MenuB0054D3CC;
#pragma pop_macro("MenuB0054D3CC") /*gvi*/
#pragma push_macro("MenuB0054D3DC") /*gvi*/
#undef MenuB0054D3DC /*gvi*/
extern uint8_t MenuB0054D3DC;
#pragma pop_macro("MenuB0054D3DC") /*gvi*/
#pragma push_macro("MenuB0054D3EC") /*gvi*/
#undef MenuB0054D3EC /*gvi*/
extern uint8_t MenuB0054D3EC;
#pragma pop_macro("MenuB0054D3EC") /*gvi*/
#pragma push_macro("MenuB0054D3FC") /*gvi*/
#undef MenuB0054D3FC /*gvi*/
extern uint8_t MenuB0054D3FC;
#pragma pop_macro("MenuB0054D3FC") /*gvi*/
#pragma push_macro("MenuB0054DFD4") /*gvi*/
#undef MenuB0054DFD4 /*gvi*/
extern uint8_t MenuB0054DFD4;
#pragma pop_macro("MenuB0054DFD4") /*gvi*/
#pragma push_macro("MenuB0054DFE4") /*gvi*/
#undef MenuB0054DFE4 /*gvi*/
extern uint8_t MenuB0054DFE4;
#pragma pop_macro("MenuB0054DFE4") /*gvi*/
#pragma push_macro("MenuB0054DFF4") /*gvi*/
#undef MenuB0054DFF4 /*gvi*/
extern uint8_t MenuB0054DFF4;
#pragma pop_macro("MenuB0054DFF4") /*gvi*/
#pragma push_macro("MenuB0054E004") /*gvi*/
#undef MenuB0054E004 /*gvi*/
extern uint8_t MenuB0054E004;
#pragma pop_macro("MenuB0054E004") /*gvi*/
#pragma push_macro("MenuB0054E1A4") /*gvi*/
#undef MenuB0054E1A4 /*gvi*/
extern uint8_t MenuB0054E1A4;
#pragma pop_macro("MenuB0054E1A4") /*gvi*/
#pragma push_macro("MenuB0054E1B4") /*gvi*/
#undef MenuB0054E1B4 /*gvi*/
extern uint8_t MenuB0054E1B4;
#pragma pop_macro("MenuB0054E1B4") /*gvi*/
#pragma push_macro("MenuI0057B730") /*gvi*/
#undef MenuI0057B730 /*gvi*/
extern int32_t MenuI0057B730;
#pragma pop_macro("MenuI0057B730") /*gvi*/
#pragma push_macro("MenuI005D578C") /*gvi*/
#undef MenuI005D578C /*gvi*/
extern int32_t MenuI005D578C;
#pragma pop_macro("MenuI005D578C") /*gvi*/
#pragma push_macro("MenuI005FE770") /*gvi*/
#undef MenuI005FE770 /*gvi*/
extern int32_t MenuI005FE770;
#pragma pop_macro("MenuI005FE770") /*gvi*/
#pragma push_macro("MenuI005FE774") /*gvi*/
#undef MenuI005FE774 /*gvi*/
extern int32_t MenuI005FE774;
#pragma pop_macro("MenuI005FE774") /*gvi*/
#pragma push_macro("MenuI005FE798") /*gvi*/
#undef MenuI005FE798 /*gvi*/
extern int32_t MenuI005FE798;
#pragma pop_macro("MenuI005FE798") /*gvi*/
#pragma push_macro("MenuI005FE79C") /*gvi*/
#undef MenuI005FE79C /*gvi*/
extern int32_t MenuI005FE79C;
#pragma pop_macro("MenuI005FE79C") /*gvi*/
#pragma push_macro("MenuI005FE9D0") /*gvi*/
#undef MenuI005FE9D0 /*gvi*/
extern int32_t MenuI005FE9D0;
#pragma pop_macro("MenuI005FE9D0") /*gvi*/
#endif
void MenuSelect00407334(int32_t mode); /* 00407334 */
void MenuSelect00407421(int32_t mode); /* 00407421 */
void MenuSelect004074FA(int32_t mode); /* 004074fa */
void MenuSelect004075BF(int32_t mode); /* 004075bf */
void MenuSelect00408864(int32_t mode); /* 00408864 */
void MenuSelect0040891D(int32_t mode); /* 0040891d */
void MenuSelect004089F2(int32_t mode); /* 004089f2 */
void MenuSelect00408A8C(int32_t mode); /* 00408a8c */
void MenuSelect00408B26(int32_t mode); /* 00408b26 */
void MenuSelect00408BC0(int32_t mode); /* 00408bc0 */
void MenuSelect00408C95(int32_t mode); /* 00408c95 */
void MenuSelect00408D2F(int32_t mode); /* 00408d2f */
void MenuSelect00408DC9(int32_t mode); /* 00408dc9 */
void MenuSelect00408E63(int32_t mode); /* 00408e63 */
void MenuSelect00408EFD(int32_t mode); /* 00408efd */
void MenuSelect00408F97(int32_t mode); /* 00408f97 */
void MenuSelect00409031(int32_t mode); /* 00409031 */
void MenuSelect004090CB(int32_t mode); /* 004090cb */
void MenuSelect004091A0(int32_t mode); /* 004091a0 */
void MenuSelect00409247(int32_t mode); /* 00409247 */
void MenuSelect004092EE(int32_t mode); /* 004092ee */
void MenuSelect00409395(int32_t mode); /* 00409395 */
void MenuSelect0040943C(int32_t mode); /* 0040943c */
void MenuLeave0040E8FF(int32_t mode); /* 0040e8ff */
void MenuLeave0040E957(int32_t mode); /* 0040e957 */
void MenuLeave0040E99C(int32_t mode); /* 0040e99c */
void MenuLeave0040EA3E(int32_t mode); /* 0040ea3e */
void MenuSelect0040FE29(int32_t mode); /* 0040fe29 */
void MenuSelect0040FEE3(int32_t mode); /* 0040fee3 */
void MenuSelect0040FF9D(int32_t mode); /* 0040ff9d */
void MenuSelect00410057(int32_t mode); /* 00410057 */
void MenuSelect00410111(int32_t mode); /* 00410111 */
void MenuSelect004101CB(int32_t mode); /* 004101cb */
void MenuSelect00410285(int32_t mode); /* 00410285 */
void MenuSelect0041033F(int32_t mode); /* 0041033f */
void MenuSelect004103F9(int32_t mode); /* 004103f9 */
void MenuSelect004104B3(int32_t mode); /* 004104b3 */
void MenuSelect0041056D(int32_t mode); /* 0041056d */
void MenuSelect00410627(int32_t mode); /* 00410627 */
void MenuSelect0041104B(int32_t mode); /* 0041104b */
void MenuSelect00411100(int32_t mode); /* 00411100 */
void MenuSelect004111B5(int32_t mode); /* 004111b5 */
void MenuSelect0041126A(int32_t mode); /* 0041126a */
void MenuSelect0041131F(int32_t mode); /* 0041131f */
void MenuSelect004113D4(int32_t mode); /* 004113d4 */
void MenuSelect00411489(int32_t mode); /* 00411489 */
void MenuSelect0041153E(int32_t mode); /* 0041153e */
void MenuSelect004115F3(int32_t mode); /* 004115f3 */
void MenuSelect004116A8(int32_t mode); /* 004116a8 */
void MenuSelect0041175D(int32_t mode); /* 0041175d */
void MenuSelect00411812(int32_t mode); /* 00411812 */
void MenuSelect004118C7(int32_t mode); /* 004118c7 */
void MenuSelect0041197C(int32_t mode); /* 0041197c */
void MenuLeave004136DA(int32_t mode); /* 004136da */
void MenuLeave00413728(int32_t mode); /* 00413728 */
void MenuLeave00413776(int32_t mode); /* 00413776 */
void MenuLeave004137C4(int32_t mode); /* 004137c4 */
void MenuLeave00413961(int32_t mode); /* 00413961 */
void MenuLeave004139AF(int32_t mode); /* 004139af */
void MenuLeave004139E6(int32_t mode); /* 004139e6 */
void MenuLeave00413A1D(int32_t mode); /* 00413a1d */
void MenuLeave00413A54(int32_t mode); /* 00413a54 */
void MenuLeave00413BE5(int32_t mode); /* 00413be5 */
void MenuLeave00413C17(int32_t mode); /* 00413c17 */
void MenuLeave00413C49(int32_t mode); /* 00413c49 */
void MenuLeave00413C7B(int32_t mode); /* 00413c7b */
void MenuLeave00413CAD(int32_t mode); /* 00413cad */
void MenuSelect00414F9D(int32_t mode); /* 00414f9d */
void MenuSelect00415111(int32_t mode); /* 00415111 */
void MenuSelect00415230(int32_t mode); /* 00415230 */
void MenuSelect00415323(int32_t mode); /* 00415323 */
void MenuSelect004153B3(int32_t mode); /* 004153b3 */
void MenuSelect00415456(int32_t mode); /* 00415456 */
void MenuSelect004154F5(int32_t mode); /* 004154f5 */
void MenuSelect004155AC(int32_t mode); /* 004155ac */
void MenuSelect00415666(int32_t mode); /* 00415666 */
void MenuSelect00415718(int32_t mode); /* 00415718 */
void MenuSelect004157B0(int32_t mode); /* 004157b0 */
void MenuLeave00416072(int32_t mode); /* 00416072 */
void MenuLeave004160D7(int32_t mode); /* 004160d7 */
void MenuLeave0041613C(int32_t mode); /* 0041613c */
void MenuLeave004161A1(int32_t mode); /* 004161a1 */
void MenuLeave00416449(int32_t mode); /* 00416449 */
void MenuLeave004164A0(int32_t mode); /* 004164a0 */
/* gvar-img v2.03 begin (tools/gen_gvar_img.py) */
#if !defined(RE_HOOK_BUILD) && !defined(RE_GVAR_PLAIN)
#undef MenuB00549F8C
#define MenuB00549F8C (*(uint8_t *)re_gvar(0x00549f8cu, sizeof(uint8_t), (void *)&MenuB00549F8C))
#undef MenuB00549F9C
#define MenuB00549F9C (*(uint8_t *)re_gvar(0x00549f9cu, sizeof(uint8_t), (void *)&MenuB00549F9C))
#undef MenuB00549FBC
#define MenuB00549FBC (*(uint8_t *)re_gvar(0x00549fbcu, sizeof(uint8_t), (void *)&MenuB00549FBC))
#undef MenuB00549FCC
#define MenuB00549FCC (*(uint8_t *)re_gvar(0x00549fccu, sizeof(uint8_t), (void *)&MenuB00549FCC))
#undef MenuB00549FDC
#define MenuB00549FDC (*(uint8_t *)re_gvar(0x00549fdcu, sizeof(uint8_t), (void *)&MenuB00549FDC))
#undef MenuB00549FEC
#define MenuB00549FEC (*(uint8_t *)re_gvar(0x00549fecu, sizeof(uint8_t), (void *)&MenuB00549FEC))
#undef MenuI0054A060
#define MenuI0054A060 (*(int32_t *)re_gvar(0x0054a060u, sizeof(int32_t), (void *)&MenuI0054A060))
#undef MenuB0054C044
#define MenuB0054C044 (*(uint8_t *)re_gvar(0x0054c044u, sizeof(uint8_t), (void *)&MenuB0054C044))
#undef MenuB0054C054
#define MenuB0054C054 (*(uint8_t *)re_gvar(0x0054c054u, sizeof(uint8_t), (void *)&MenuB0054C054))
#undef MenuB0054C064
#define MenuB0054C064 (*(uint8_t *)re_gvar(0x0054c064u, sizeof(uint8_t), (void *)&MenuB0054C064))
#undef MenuB0054C074
#define MenuB0054C074 (*(uint8_t *)re_gvar(0x0054c074u, sizeof(uint8_t), (void *)&MenuB0054C074))
#undef MenuB0054C084
#define MenuB0054C084 (*(uint8_t *)re_gvar(0x0054c084u, sizeof(uint8_t), (void *)&MenuB0054C084))
#undef MenuB0054C094
#define MenuB0054C094 (*(uint8_t *)re_gvar(0x0054c094u, sizeof(uint8_t), (void *)&MenuB0054C094))
#undef MenuB0054C0A4
#define MenuB0054C0A4 (*(uint8_t *)re_gvar(0x0054c0a4u, sizeof(uint8_t), (void *)&MenuB0054C0A4))
#undef MenuB0054C0B4
#define MenuB0054C0B4 (*(uint8_t *)re_gvar(0x0054c0b4u, sizeof(uint8_t), (void *)&MenuB0054C0B4))
#undef MenuB0054C0C4
#define MenuB0054C0C4 (*(uint8_t *)re_gvar(0x0054c0c4u, sizeof(uint8_t), (void *)&MenuB0054C0C4))
#undef MenuB0054C0D4
#define MenuB0054C0D4 (*(uint8_t *)re_gvar(0x0054c0d4u, sizeof(uint8_t), (void *)&MenuB0054C0D4))
#undef MenuB0054C0E4
#define MenuB0054C0E4 (*(uint8_t *)re_gvar(0x0054c0e4u, sizeof(uint8_t), (void *)&MenuB0054C0E4))
#undef MenuB0054C0F4
#define MenuB0054C0F4 (*(uint8_t *)re_gvar(0x0054c0f4u, sizeof(uint8_t), (void *)&MenuB0054C0F4))
#undef MenuB0054C104
#define MenuB0054C104 (*(uint8_t *)re_gvar(0x0054c104u, sizeof(uint8_t), (void *)&MenuB0054C104))
#undef MenuB0054C114
#define MenuB0054C114 (*(uint8_t *)re_gvar(0x0054c114u, sizeof(uint8_t), (void *)&MenuB0054C114))
#undef MenuB0054C124
#define MenuB0054C124 (*(uint8_t *)re_gvar(0x0054c124u, sizeof(uint8_t), (void *)&MenuB0054C124))
#undef MenuB0054C134
#define MenuB0054C134 (*(uint8_t *)re_gvar(0x0054c134u, sizeof(uint8_t), (void *)&MenuB0054C134))
#undef MenuB0054C144
#define MenuB0054C144 (*(uint8_t *)re_gvar(0x0054c144u, sizeof(uint8_t), (void *)&MenuB0054C144))
#undef MenuB0054C154
#define MenuB0054C154 (*(uint8_t *)re_gvar(0x0054c154u, sizeof(uint8_t), (void *)&MenuB0054C154))
#undef MenuB0054C164
#define MenuB0054C164 (*(uint8_t *)re_gvar(0x0054c164u, sizeof(uint8_t), (void *)&MenuB0054C164))
#undef MenuB0054C174
#define MenuB0054C174 (*(uint8_t *)re_gvar(0x0054c174u, sizeof(uint8_t), (void *)&MenuB0054C174))
#undef MenuB0054C184
#define MenuB0054C184 (*(uint8_t *)re_gvar(0x0054c184u, sizeof(uint8_t), (void *)&MenuB0054C184))
#undef MenuB0054C194
#define MenuB0054C194 (*(uint8_t *)re_gvar(0x0054c194u, sizeof(uint8_t), (void *)&MenuB0054C194))
#undef MenuB0054C1A4
#define MenuB0054C1A4 (*(uint8_t *)re_gvar(0x0054c1a4u, sizeof(uint8_t), (void *)&MenuB0054C1A4))
#undef MenuB0054C1B4
#define MenuB0054C1B4 (*(uint8_t *)re_gvar(0x0054c1b4u, sizeof(uint8_t), (void *)&MenuB0054C1B4))
#undef MenuB0054C364
#define MenuB0054C364 (*(uint8_t *)re_gvar(0x0054c364u, sizeof(uint8_t), (void *)&MenuB0054C364))
#undef MenuB0054C374
#define MenuB0054C374 (*(uint8_t *)re_gvar(0x0054c374u, sizeof(uint8_t), (void *)&MenuB0054C374))
#undef MenuB0054C384
#define MenuB0054C384 (*(uint8_t *)re_gvar(0x0054c384u, sizeof(uint8_t), (void *)&MenuB0054C384))
#undef MenuB0054C394
#define MenuB0054C394 (*(uint8_t *)re_gvar(0x0054c394u, sizeof(uint8_t), (void *)&MenuB0054C394))
#undef MenuB0054C3A4
#define MenuB0054C3A4 (*(uint8_t *)re_gvar(0x0054c3a4u, sizeof(uint8_t), (void *)&MenuB0054C3A4))
#undef MenuB0054C3B4
#define MenuB0054C3B4 (*(uint8_t *)re_gvar(0x0054c3b4u, sizeof(uint8_t), (void *)&MenuB0054C3B4))
#undef MenuB0054C3C4
#define MenuB0054C3C4 (*(uint8_t *)re_gvar(0x0054c3c4u, sizeof(uint8_t), (void *)&MenuB0054C3C4))
#undef MenuB0054C3D4
#define MenuB0054C3D4 (*(uint8_t *)re_gvar(0x0054c3d4u, sizeof(uint8_t), (void *)&MenuB0054C3D4))
#undef MenuB0054C3E4
#define MenuB0054C3E4 (*(uint8_t *)re_gvar(0x0054c3e4u, sizeof(uint8_t), (void *)&MenuB0054C3E4))
#undef MenuB0054C3F4
#define MenuB0054C3F4 (*(uint8_t *)re_gvar(0x0054c3f4u, sizeof(uint8_t), (void *)&MenuB0054C3F4))
#undef MenuB0054C404
#define MenuB0054C404 (*(uint8_t *)re_gvar(0x0054c404u, sizeof(uint8_t), (void *)&MenuB0054C404))
#undef MenuB0054C414
#define MenuB0054C414 (*(uint8_t *)re_gvar(0x0054c414u, sizeof(uint8_t), (void *)&MenuB0054C414))
#undef MenuB0054C424
#define MenuB0054C424 (*(uint8_t *)re_gvar(0x0054c424u, sizeof(uint8_t), (void *)&MenuB0054C424))
#undef MenuB0054C434
#define MenuB0054C434 (*(uint8_t *)re_gvar(0x0054c434u, sizeof(uint8_t), (void *)&MenuB0054C434))
#undef MenuB0054C444
#define MenuB0054C444 (*(uint8_t *)re_gvar(0x0054c444u, sizeof(uint8_t), (void *)&MenuB0054C444))
#undef MenuB0054C454
#define MenuB0054C454 (*(uint8_t *)re_gvar(0x0054c454u, sizeof(uint8_t), (void *)&MenuB0054C454))
#undef MenuB0054C464
#define MenuB0054C464 (*(uint8_t *)re_gvar(0x0054c464u, sizeof(uint8_t), (void *)&MenuB0054C464))
#undef MenuB0054C474
#define MenuB0054C474 (*(uint8_t *)re_gvar(0x0054c474u, sizeof(uint8_t), (void *)&MenuB0054C474))
#undef MenuB0054C484
#define MenuB0054C484 (*(uint8_t *)re_gvar(0x0054c484u, sizeof(uint8_t), (void *)&MenuB0054C484))
#undef MenuB0054C494
#define MenuB0054C494 (*(uint8_t *)re_gvar(0x0054c494u, sizeof(uint8_t), (void *)&MenuB0054C494))
#undef MenuB0054C4A4
#define MenuB0054C4A4 (*(uint8_t *)re_gvar(0x0054c4a4u, sizeof(uint8_t), (void *)&MenuB0054C4A4))
#undef MenuB0054C4B4
#define MenuB0054C4B4 (*(uint8_t *)re_gvar(0x0054c4b4u, sizeof(uint8_t), (void *)&MenuB0054C4B4))
#undef MenuB0054C4C4
#define MenuB0054C4C4 (*(uint8_t *)re_gvar(0x0054c4c4u, sizeof(uint8_t), (void *)&MenuB0054C4C4))
#undef MenuB0054C4D4
#define MenuB0054C4D4 (*(uint8_t *)re_gvar(0x0054c4d4u, sizeof(uint8_t), (void *)&MenuB0054C4D4))
#undef MenuB0054C4E4
#define MenuB0054C4E4 (*(uint8_t *)re_gvar(0x0054c4e4u, sizeof(uint8_t), (void *)&MenuB0054C4E4))
#undef MenuB0054C4F4
#define MenuB0054C4F4 (*(uint8_t *)re_gvar(0x0054c4f4u, sizeof(uint8_t), (void *)&MenuB0054C4F4))
#undef MenuB0054C504
#define MenuB0054C504 (*(uint8_t *)re_gvar(0x0054c504u, sizeof(uint8_t), (void *)&MenuB0054C504))
#undef MenuB0054C514
#define MenuB0054C514 (*(uint8_t *)re_gvar(0x0054c514u, sizeof(uint8_t), (void *)&MenuB0054C514))
#undef MenuB0054D1B4
#define MenuB0054D1B4 (*(uint8_t *)re_gvar(0x0054d1b4u, sizeof(uint8_t), (void *)&MenuB0054D1B4))
#undef MenuB0054D1C4
#define MenuB0054D1C4 (*(uint8_t *)re_gvar(0x0054d1c4u, sizeof(uint8_t), (void *)&MenuB0054D1C4))
#undef MenuB0054D1D4
#define MenuB0054D1D4 (*(uint8_t *)re_gvar(0x0054d1d4u, sizeof(uint8_t), (void *)&MenuB0054D1D4))
#undef MenuB0054D1E4
#define MenuB0054D1E4 (*(uint8_t *)re_gvar(0x0054d1e4u, sizeof(uint8_t), (void *)&MenuB0054D1E4))
#undef MenuB0054D2A4
#define MenuB0054D2A4 (*(uint8_t *)re_gvar(0x0054d2a4u, sizeof(uint8_t), (void *)&MenuB0054D2A4))
#undef MenuB0054D2B4
#define MenuB0054D2B4 (*(uint8_t *)re_gvar(0x0054d2b4u, sizeof(uint8_t), (void *)&MenuB0054D2B4))
#undef MenuB0054D2C4
#define MenuB0054D2C4 (*(uint8_t *)re_gvar(0x0054d2c4u, sizeof(uint8_t), (void *)&MenuB0054D2C4))
#undef MenuB0054D2D4
#define MenuB0054D2D4 (*(uint8_t *)re_gvar(0x0054d2d4u, sizeof(uint8_t), (void *)&MenuB0054D2D4))
#undef MenuB0054D2E4
#define MenuB0054D2E4 (*(uint8_t *)re_gvar(0x0054d2e4u, sizeof(uint8_t), (void *)&MenuB0054D2E4))
#undef MenuB0054D3BC
#define MenuB0054D3BC (*(uint8_t *)re_gvar(0x0054d3bcu, sizeof(uint8_t), (void *)&MenuB0054D3BC))
#undef MenuB0054D3CC
#define MenuB0054D3CC (*(uint8_t *)re_gvar(0x0054d3ccu, sizeof(uint8_t), (void *)&MenuB0054D3CC))
#undef MenuB0054D3DC
#define MenuB0054D3DC (*(uint8_t *)re_gvar(0x0054d3dcu, sizeof(uint8_t), (void *)&MenuB0054D3DC))
#undef MenuB0054D3EC
#define MenuB0054D3EC (*(uint8_t *)re_gvar(0x0054d3ecu, sizeof(uint8_t), (void *)&MenuB0054D3EC))
#undef MenuB0054D3FC
#define MenuB0054D3FC (*(uint8_t *)re_gvar(0x0054d3fcu, sizeof(uint8_t), (void *)&MenuB0054D3FC))
#undef MenuB0054DFD4
#define MenuB0054DFD4 (*(uint8_t *)re_gvar(0x0054dfd4u, sizeof(uint8_t), (void *)&MenuB0054DFD4))
#undef MenuB0054DFE4
#define MenuB0054DFE4 (*(uint8_t *)re_gvar(0x0054dfe4u, sizeof(uint8_t), (void *)&MenuB0054DFE4))
#undef MenuB0054DFF4
#define MenuB0054DFF4 (*(uint8_t *)re_gvar(0x0054dff4u, sizeof(uint8_t), (void *)&MenuB0054DFF4))
#undef MenuB0054E004
#define MenuB0054E004 (*(uint8_t *)re_gvar(0x0054e004u, sizeof(uint8_t), (void *)&MenuB0054E004))
#undef MenuB0054E1A4
#define MenuB0054E1A4 (*(uint8_t *)re_gvar(0x0054e1a4u, sizeof(uint8_t), (void *)&MenuB0054E1A4))
#undef MenuB0054E1B4
#define MenuB0054E1B4 (*(uint8_t *)re_gvar(0x0054e1b4u, sizeof(uint8_t), (void *)&MenuB0054E1B4))
#undef MenuI0057B730
#define MenuI0057B730 (*(int32_t *)re_gvar(0x0057b730u, sizeof(int32_t), (void *)&MenuI0057B730))
#undef MenuI005D578C
#define MenuI005D578C (*(int32_t *)re_gvar(0x005d578cu, sizeof(int32_t), (void *)&MenuI005D578C))
#undef MenuI005FE770
#define MenuI005FE770 (*(int32_t *)re_gvar(0x005fe770u, sizeof(int32_t), (void *)&MenuI005FE770))
#undef MenuI005FE774
#define MenuI005FE774 (*(int32_t *)re_gvar(0x005fe774u, sizeof(int32_t), (void *)&MenuI005FE774))
#undef MenuI005FE798
#define MenuI005FE798 (*(int32_t *)re_gvar(0x005fe798u, sizeof(int32_t), (void *)&MenuI005FE798))
#undef MenuI005FE79C
#define MenuI005FE79C (*(int32_t *)re_gvar(0x005fe79cu, sizeof(int32_t), (void *)&MenuI005FE79C))
#undef MenuI005FE9D0
#define MenuI005FE9D0 (*(int32_t *)re_gvar(0x005fe9d0u, sizeof(int32_t), (void *)&MenuI005FE9D0))
#endif
/* gvar-img v2.03 end */
