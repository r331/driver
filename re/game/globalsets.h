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
extern int32_t G0054A8E0;
#endif
#define G0054A8F0 GAME_VAR(int32_t, G0054A8F0, 0x0054a8f0)
#ifndef RE_HOOK_BUILD
extern int32_t G0054A8F0;
#endif
#define G0054A900 GAME_VAR(int32_t, G0054A900, 0x0054a900)
#ifndef RE_HOOK_BUILD
extern int32_t G0054A900;
#endif
#define G0054A910 GAME_VAR(int32_t, G0054A910, 0x0054a910)
#ifndef RE_HOOK_BUILD
extern int32_t G0054A910;
#endif
#define G0054A920 GAME_VAR(int32_t, G0054A920, 0x0054a920)
#ifndef RE_HOOK_BUILD
extern int32_t G0054A920;
#endif
#define G0054A930 GAME_VAR(int32_t, G0054A930, 0x0054a930)
#ifndef RE_HOOK_BUILD
extern int32_t G0054A930;
#endif
#define G0054A940 GAME_VAR(int32_t, G0054A940, 0x0054a940)
#ifndef RE_HOOK_BUILD
extern int32_t G0054A940;
#endif
#define G0054A950 GAME_VAR(int32_t, G0054A950, 0x0054a950)
#ifndef RE_HOOK_BUILD
extern int32_t G0054A950;
#endif
#define G0054AA24 GAME_VAR(int32_t, G0054AA24, 0x0054aa24)
#ifndef RE_HOOK_BUILD
extern int32_t G0054AA24;
#endif
#define G0054AA28 GAME_VAR(int32_t, G0054AA28, 0x0054aa28)
#ifndef RE_HOOK_BUILD
extern int32_t G0054AA28;
#endif
#define G0054AA2C GAME_VAR(uint8_t, G0054AA2C, 0x0054aa2c)
#ifndef RE_HOOK_BUILD
extern uint8_t G0054AA2C;
#endif
#define G0054AA2D GAME_VAR(uint8_t, G0054AA2D, 0x0054aa2d)
#ifndef RE_HOOK_BUILD
extern uint8_t G0054AA2D;
#endif
#define G0054AA2E GAME_VAR(uint8_t, G0054AA2E, 0x0054aa2e)
#ifndef RE_HOOK_BUILD
extern uint8_t G0054AA2E;
#endif
#define G0054AA44 GAME_VAR(int32_t, G0054AA44, 0x0054aa44)
#ifndef RE_HOOK_BUILD
extern int32_t G0054AA44;
#endif
#define G0054C6E8 GAME_VAR(int32_t, G0054C6E8, 0x0054c6e8)
#ifndef RE_HOOK_BUILD
extern int32_t G0054C6E8;
#endif
#define G0054C6F8 GAME_VAR(int32_t, G0054C6F8, 0x0054c6f8)
#ifndef RE_HOOK_BUILD
extern int32_t G0054C6F8;
#endif
#define G0054C958 GAME_VAR(int32_t, G0054C958, 0x0054c958)
#ifndef RE_HOOK_BUILD
extern int32_t G0054C958;
#endif
#define G0054C968 GAME_VAR(int32_t, G0054C968, 0x0054c968)
#ifndef RE_HOOK_BUILD
extern int32_t G0054C968;
#endif
#define G0054D100 GAME_VAR(int32_t, G0054D100, 0x0054d100)
#ifndef RE_HOOK_BUILD
extern int32_t G0054D100;
#endif
#define G0054D110 GAME_VAR(int32_t, G0054D110, 0x0054d110)
#ifndef RE_HOOK_BUILD
extern int32_t G0054D110;
#endif
#define G0054D120 GAME_VAR(int32_t, G0054D120, 0x0054d120)
#ifndef RE_HOOK_BUILD
extern int32_t G0054D120;
#endif
#define G0054D1A8 GAME_VAR(int32_t, G0054D1A8, 0x0054d1a8)
#ifndef RE_HOOK_BUILD
extern int32_t G0054D1A8;
#endif
#define G0054D1B8 GAME_VAR(int32_t, G0054D1B8, 0x0054d1b8)
#ifndef RE_HOOK_BUILD
extern int32_t G0054D1B8;
#endif
#define G0054D1C8 GAME_VAR(int32_t, G0054D1C8, 0x0054d1c8)
#ifndef RE_HOOK_BUILD
extern int32_t G0054D1C8;
#endif
#define G0054D1D8 GAME_VAR(int32_t, G0054D1D8, 0x0054d1d8)
#ifndef RE_HOOK_BUILD
extern int32_t G0054D1D8;
#endif
#define G0054D1E8 GAME_VAR(int32_t, G0054D1E8, 0x0054d1e8)
#ifndef RE_HOOK_BUILD
extern int32_t G0054D1E8;
#endif
#define G0054D298 GAME_VAR(int32_t, G0054D298, 0x0054d298)
#ifndef RE_HOOK_BUILD
extern int32_t G0054D298;
#endif
#define G0054D2A8 GAME_VAR(int32_t, G0054D2A8, 0x0054d2a8)
#ifndef RE_HOOK_BUILD
extern int32_t G0054D2A8;
#endif
#define G0054D2B8 GAME_VAR(int32_t, G0054D2B8, 0x0054d2b8)
#ifndef RE_HOOK_BUILD
extern int32_t G0054D2B8;
#endif
#define G0054D2C8 GAME_VAR(int32_t, G0054D2C8, 0x0054d2c8)
#ifndef RE_HOOK_BUILD
extern int32_t G0054D2C8;
#endif
#define G0054D2D8 GAME_VAR(int32_t, G0054D2D8, 0x0054d2d8)
#ifndef RE_HOOK_BUILD
extern int32_t G0054D2D8;
#endif
#define G0054D2E8 GAME_VAR(int32_t, G0054D2E8, 0x0054d2e8)
#ifndef RE_HOOK_BUILD
extern int32_t G0054D2E8;
#endif
#define G0054D3B0 GAME_VAR(int32_t, G0054D3B0, 0x0054d3b0)
#ifndef RE_HOOK_BUILD
extern int32_t G0054D3B0;
#endif
#define G0054D3C0 GAME_VAR(int32_t, G0054D3C0, 0x0054d3c0)
#ifndef RE_HOOK_BUILD
extern int32_t G0054D3C0;
#endif
#define G0054D3D0 GAME_VAR(int32_t, G0054D3D0, 0x0054d3d0)
#ifndef RE_HOOK_BUILD
extern int32_t G0054D3D0;
#endif
#define G0054D3E0 GAME_VAR(int32_t, G0054D3E0, 0x0054d3e0)
#ifndef RE_HOOK_BUILD
extern int32_t G0054D3E0;
#endif
#define G0054D3F0 GAME_VAR(int32_t, G0054D3F0, 0x0054d3f0)
#ifndef RE_HOOK_BUILD
extern int32_t G0054D3F0;
#endif
#define G0054D400 GAME_VAR(int32_t, G0054D400, 0x0054d400)
#ifndef RE_HOOK_BUILD
extern int32_t G0054D400;
#endif
#define G0054E16C GAME_VAR(int32_t, G0054E16C, 0x0054e16c)
#ifndef RE_HOOK_BUILD
extern int32_t G0054E16C;
#endif
#define G0054E198 GAME_VAR(int32_t, G0054E198, 0x0054e198)
#ifndef RE_HOOK_BUILD
extern int32_t G0054E198;
#endif
#define G0054E1A4 GAME_VAR(uint8_t, G0054E1A4, 0x0054e1a4)
#ifndef RE_HOOK_BUILD
extern uint8_t G0054E1A4;
#endif
#define G0054E1A8 GAME_VAR(int32_t, G0054E1A8, 0x0054e1a8)
#ifndef RE_HOOK_BUILD
extern int32_t G0054E1A8;
#endif
#define G0054E1B4 GAME_VAR(uint8_t, G0054E1B4, 0x0054e1b4)
#ifndef RE_HOOK_BUILD
extern uint8_t G0054E1B4;
#endif
#define G0054E1B8 GAME_VAR(int32_t, G0054E1B8, 0x0054e1b8)
#ifndef RE_HOOK_BUILD
extern int32_t G0054E1B8;
#endif
#define G0054E448 GAME_VAR(int32_t, G0054E448, 0x0054e448)
#ifndef RE_HOOK_BUILD
extern int32_t G0054E448;
#endif
#define G0054E458 GAME_VAR(int32_t, G0054E458, 0x0054e458)
#ifndef RE_HOOK_BUILD
extern int32_t G0054E458;
#endif
#define G0054E468 GAME_VAR(int32_t, G0054E468, 0x0054e468)
#ifndef RE_HOOK_BUILD
extern int32_t G0054E468;
#endif
#define G0054E6A8 GAME_VAR(int32_t, G0054E6A8, 0x0054e6a8)
#ifndef RE_HOOK_BUILD
extern int32_t G0054E6A8;
#endif
#define G0054E6B8 GAME_VAR(int32_t, G0054E6B8, 0x0054e6b8)
#ifndef RE_HOOK_BUILD
extern int32_t G0054E6B8;
#endif
#define G0054E6C8 GAME_VAR(int32_t, G0054E6C8, 0x0054e6c8)
#ifndef RE_HOOK_BUILD
extern int32_t G0054E6C8;
#endif
#define G0054E6D8 GAME_VAR(int32_t, G0054E6D8, 0x0054e6d8)
#ifndef RE_HOOK_BUILD
extern int32_t G0054E6D8;
#endif
#define G0054E6E8 GAME_VAR(int32_t, G0054E6E8, 0x0054e6e8)
#ifndef RE_HOOK_BUILD
extern int32_t G0054E6E8;
#endif
#define G00575550 GAME_VAR(int32_t, G00575550, 0x00575550)
#ifndef RE_HOOK_BUILD
extern int32_t G00575550;
#endif
#define G00575554 GAME_VAR(int32_t, G00575554, 0x00575554)
#ifndef RE_HOOK_BUILD
extern int32_t G00575554;
#endif
#define G005D77C0 GAME_VAR(uint8_t, G005D77C0, 0x005d77c0)
#ifndef RE_HOOK_BUILD
extern uint8_t G005D77C0;
#endif
#define G005D77C1 GAME_VAR(uint8_t, G005D77C1, 0x005d77c1)
#ifndef RE_HOOK_BUILD
extern uint8_t G005D77C1;
#endif
#define G005D77C4 GAME_VAR(int32_t, G005D77C4, 0x005d77c4)
#ifndef RE_HOOK_BUILD
extern int32_t G005D77C4;
#endif
#define G005D77C8 GAME_VAR(int32_t, G005D77C8, 0x005d77c8)
#ifndef RE_HOOK_BUILD
extern int32_t G005D77C8;
#endif
#define G005D77CC GAME_VAR(int32_t, G005D77CC, 0x005d77cc)
#ifndef RE_HOOK_BUILD
extern int32_t G005D77CC;
#endif
#define G005F7E54 GAME_VAR(int32_t, G005F7E54, 0x005f7e54)
#ifndef RE_HOOK_BUILD
extern int32_t G005F7E54;
#endif
#define G005FE850 GAME_VAR(int32_t, G005FE850, 0x005fe850)
#ifndef RE_HOOK_BUILD
extern int32_t G005FE850;
#endif
#define G005FE92C GAME_VAR(int32_t, G005FE92C, 0x005fe92c)
#ifndef RE_HOOK_BUILD
extern int32_t G005FE92C;
#endif
#define G00B31E40 GAME_VAR(uint8_t, G00B31E40, 0x00b31e40)
#ifndef RE_HOOK_BUILD
extern uint8_t G00B31E40;
#endif
#define G00B31E41 GAME_VAR(uint8_t, G00B31E41, 0x00b31e41)
#ifndef RE_HOOK_BUILD
extern uint8_t G00B31E41;
#endif
#define G00B31E42 GAME_VAR(uint8_t, G00B31E42, 0x00b31e42)
#ifndef RE_HOOK_BUILD
extern uint8_t G00B31E42;
#endif
#define G00B31E43 GAME_VAR(uint8_t, G00B31E43, 0x00b31e43)
#ifndef RE_HOOK_BUILD
extern uint8_t G00B31E43;
#endif
#define G00B5A730 GAME_VAR(int32_t, G00B5A730, 0x00b5a730)
#ifndef RE_HOOK_BUILD
extern int32_t G00B5A730;
#endif
#define G00B5A734 GAME_VAR(int32_t, G00B5A734, 0x00b5a734)
#ifndef RE_HOOK_BUILD
extern int32_t G00B5A734;
#endif
#define G00B5A738 GAME_VAR(int32_t, G00B5A738, 0x00b5a738)
#ifndef RE_HOOK_BUILD
extern int32_t G00B5A738;
#endif
#define G00B5A73C GAME_VAR(int32_t, G00B5A73C, 0x00b5a73c)
#ifndef RE_HOOK_BUILD
extern int32_t G00B5A73C;
#endif
#define G00B5A774 GAME_VAR(int32_t, G00B5A774, 0x00b5a774)
#ifndef RE_HOOK_BUILD
extern int32_t G00B5A774;
#endif
#define G00B5A8CD GAME_VAR(uint8_t, G00B5A8CD, 0x00b5a8cd)
#ifndef RE_HOOK_BUILD
extern uint8_t G00B5A8CD;
#endif
#define G00B5C858 GAME_VAR(int32_t, G00B5C858, 0x00b5c858)
#ifndef RE_HOOK_BUILD
extern int32_t G00B5C858;
#endif
#define G00B5C85C GAME_VAR(int32_t, G00B5C85C, 0x00b5c85c)
#ifndef RE_HOOK_BUILD
extern int32_t G00B5C85C;
#endif
#define G00B5C860 GAME_VAR(int32_t, G00B5C860, 0x00b5c860)
#ifndef RE_HOOK_BUILD
extern int32_t G00B5C860;
#endif
#define G00B5C864 GAME_VAR(int32_t, G00B5C864, 0x00b5c864)
#ifndef RE_HOOK_BUILD
extern int32_t G00B5C864;
#endif
#define G00B5C868 GAME_VAR(int32_t, G00B5C868, 0x00b5c868)
#ifndef RE_HOOK_BUILD
extern int32_t G00B5C868;
#endif
#define G00B5C86C GAME_VAR(int32_t, G00B5C86C, 0x00b5c86c)
#ifndef RE_HOOK_BUILD
extern int32_t G00B5C86C;
#endif
#define G00B5C870 GAME_VAR(int32_t, G00B5C870, 0x00b5c870)
#ifndef RE_HOOK_BUILD
extern int32_t G00B5C870;
#endif
#define G00B5C874 GAME_VAR(int32_t, G00B5C874, 0x00b5c874)
#ifndef RE_HOOK_BUILD
extern int32_t G00B5C874;
#endif
#define G00B5C878 GAME_VAR(int32_t, G00B5C878, 0x00b5c878)
#ifndef RE_HOOK_BUILD
extern int32_t G00B5C878;
#endif
#define G00B5C87C GAME_VAR(int32_t, G00B5C87C, 0x00b5c87c)
#ifndef RE_HOOK_BUILD
extern int32_t G00B5C87C;
#endif
#define G00B5C880 GAME_VAR(int32_t, G00B5C880, 0x00b5c880)
#ifndef RE_HOOK_BUILD
extern int32_t G00B5C880;
#endif
#define G00B5C884 GAME_VAR(int32_t, G00B5C884, 0x00b5c884)
#ifndef RE_HOOK_BUILD
extern int32_t G00B5C884;
#endif
#define G00B5C888 GAME_VAR(int32_t, G00B5C888, 0x00b5c888)
#ifndef RE_HOOK_BUILD
extern int32_t G00B5C888;
#endif
#define G00B5C88C GAME_VAR(int32_t, G00B5C88C, 0x00b5c88c)
#ifndef RE_HOOK_BUILD
extern int32_t G00B5C88C;
#endif
#define G00B5C890 GAME_VAR(int32_t, G00B5C890, 0x00b5c890)
#ifndef RE_HOOK_BUILD
extern int32_t G00B5C890;
#endif
#define G00B5C894 GAME_VAR(int32_t, G00B5C894, 0x00b5c894)
#ifndef RE_HOOK_BUILD
extern int32_t G00B5C894;
#endif
#define G00B5C910 GAME_VAR(int32_t, G00B5C910, 0x00b5c910)
#ifndef RE_HOOK_BUILD
extern int32_t G00B5C910;
#endif
#define G00B5C914 GAME_VAR(int32_t, G00B5C914, 0x00b5c914)
#ifndef RE_HOOK_BUILD
extern int32_t G00B5C914;
#endif
#define G00B5C918 GAME_VAR(int32_t, G00B5C918, 0x00b5c918)
#ifndef RE_HOOK_BUILD
extern int32_t G00B5C918;
#endif
#define G00B5C91C GAME_VAR(int32_t, G00B5C91C, 0x00b5c91c)
#ifndef RE_HOOK_BUILD
extern int32_t G00B5C91C;
#endif
#define G00B5C920 GAME_VAR(int32_t, G00B5C920, 0x00b5c920)
#ifndef RE_HOOK_BUILD
extern int32_t G00B5C920;
#endif
#define G00B5C924 GAME_VAR(int32_t, G00B5C924, 0x00b5c924)
#ifndef RE_HOOK_BUILD
extern int32_t G00B5C924;
#endif
#define G00B5C928 GAME_VAR(int32_t, G00B5C928, 0x00b5c928)
#ifndef RE_HOOK_BUILD
extern int32_t G00B5C928;
#endif
#define G00B5C92C GAME_VAR(int32_t, G00B5C92C, 0x00b5c92c)
#ifndef RE_HOOK_BUILD
extern int32_t G00B5C92C;
#endif
#define G00B5C930 GAME_VAR(int32_t, G00B5C930, 0x00b5c930)
#ifndef RE_HOOK_BUILD
extern int32_t G00B5C930;
#endif
#define G00B5C934 GAME_VAR(int32_t, G00B5C934, 0x00b5c934)
#ifndef RE_HOOK_BUILD
extern int32_t G00B5C934;
#endif
#define G00B5C938 GAME_VAR(int32_t, G00B5C938, 0x00b5c938)
#ifndef RE_HOOK_BUILD
extern int32_t G00B5C938;
#endif
#define G00B5C93C GAME_VAR(int32_t, G00B5C93C, 0x00b5c93c)
#ifndef RE_HOOK_BUILD
extern int32_t G00B5C93C;
#endif
#define G00B5C940 GAME_VAR(int32_t, G00B5C940, 0x00b5c940)
#ifndef RE_HOOK_BUILD
extern int32_t G00B5C940;
#endif
#define G00B5C944 GAME_VAR(int32_t, G00B5C944, 0x00b5c944)
#ifndef RE_HOOK_BUILD
extern int32_t G00B5C944;
#endif
#define G00B5C948 GAME_VAR(int32_t, G00B5C948, 0x00b5c948)
#ifndef RE_HOOK_BUILD
extern int32_t G00B5C948;
#endif
#define G00B5C94C GAME_VAR(int32_t, G00B5C94C, 0x00b5c94c)
#ifndef RE_HOOK_BUILD
extern int32_t G00B5C94C;
#endif
#define G00BF1C20 GAME_VAR(uint8_t, G00BF1C20, 0x00bf1c20)
#ifndef RE_HOOK_BUILD
extern uint8_t G00BF1C20;
#endif
#define G00C29D80 GAME_VAR(uint8_t, G00C29D80, 0x00c29d80)
#ifndef RE_HOOK_BUILD
extern uint8_t G00C29D80;
#endif
#define G00C29D81 GAME_VAR(uint8_t, G00C29D81, 0x00c29d81)
#ifndef RE_HOOK_BUILD
extern uint8_t G00C29D81;
#endif
#define G00C4BDC4 GAME_VAR(int32_t, G00C4BDC4, 0x00c4bdc4)
#ifndef RE_HOOK_BUILD
extern int32_t G00C4BDC4;
#endif
#include "strtab.h"
#define G00C55820 ((int32_t)P97_StrAddr[0])   /* единая таблица строк 00c55820 */
#define G00C5582C GAME_VAR(int32_t, G00C5582C, 0x00c5582c)
#ifndef RE_HOOK_BUILD
extern int32_t G00C5582C;
#endif
#define G00C55830 GAME_VAR(int32_t, G00C55830, 0x00c55830)
#ifndef RE_HOOK_BUILD
extern int32_t G00C55830;
#endif
#define G00C55878 GAME_VAR(int32_t, G00C55878, 0x00c55878)
#ifndef RE_HOOK_BUILD
extern int32_t G00C55878;
#endif
#define G00C5587C GAME_VAR(int32_t, G00C5587C, 0x00c5587c)
#ifndef RE_HOOK_BUILD
extern int32_t G00C5587C;
#endif
#define G00C55880 GAME_VAR(int32_t, G00C55880, 0x00c55880)
#ifndef RE_HOOK_BUILD
extern int32_t G00C55880;
#endif
#define G00C55884 GAME_VAR(int32_t, G00C55884, 0x00c55884)
#ifndef RE_HOOK_BUILD
extern int32_t G00C55884;
#endif
#define G00C558B4 GAME_VAR(int32_t, G00C558B4, 0x00c558b4)
#ifndef RE_HOOK_BUILD
extern int32_t G00C558B4;
#endif
#define G00C558B8 GAME_VAR(int32_t, G00C558B8, 0x00c558b8)
#ifndef RE_HOOK_BUILD
extern int32_t G00C558B8;
#endif
#define G00C558BC GAME_VAR(int32_t, G00C558BC, 0x00c558bc)
#ifndef RE_HOOK_BUILD
extern int32_t G00C558BC;
#endif
#define G00C558C0 GAME_VAR(int32_t, G00C558C0, 0x00c558c0)
#ifndef RE_HOOK_BUILD
extern int32_t G00C558C0;
#endif
#define G00C558C4 GAME_VAR(int32_t, G00C558C4, 0x00c558c4)
#ifndef RE_HOOK_BUILD
extern int32_t G00C558C4;
#endif
#define G00C55984 GAME_VAR(int32_t, G00C55984, 0x00c55984)
#ifndef RE_HOOK_BUILD
extern int32_t G00C55984;
#endif
#define G00C55988 GAME_VAR(int32_t, G00C55988, 0x00c55988)
#ifndef RE_HOOK_BUILD
extern int32_t G00C55988;
#endif
#define G00C5598C GAME_VAR(int32_t, G00C5598C, 0x00c5598c)
#ifndef RE_HOOK_BUILD
extern int32_t G00C5598C;
#endif
#define G00C55990 GAME_VAR(int32_t, G00C55990, 0x00c55990)
#ifndef RE_HOOK_BUILD
extern int32_t G00C55990;
#endif
#define G00C55994 GAME_VAR(int32_t, G00C55994, 0x00c55994)
#ifndef RE_HOOK_BUILD
extern int32_t G00C55994;
#endif
#define G00C55998 GAME_VAR(int32_t, G00C55998, 0x00c55998)
#ifndef RE_HOOK_BUILD
extern int32_t G00C55998;
#endif
#define G00C5599C GAME_VAR(int32_t, G00C5599C, 0x00c5599c)
#ifndef RE_HOOK_BUILD
extern int32_t G00C5599C;
#endif
#define G00C559A0 GAME_VAR(int32_t, G00C559A0, 0x00c559a0)
#ifndef RE_HOOK_BUILD
extern int32_t G00C559A0;
#endif
#define G00C559B4 GAME_VAR(int32_t, G00C559B4, 0x00c559b4)
#ifndef RE_HOOK_BUILD
extern int32_t G00C559B4;
#endif
#define G00C559B8 GAME_VAR(int32_t, G00C559B8, 0x00c559b8)
#ifndef RE_HOOK_BUILD
extern int32_t G00C559B8;
#endif
#define G00C559BC GAME_VAR(int32_t, G00C559BC, 0x00c559bc)
#ifndef RE_HOOK_BUILD
extern int32_t G00C559BC;
#endif
#define G00C559C0 GAME_VAR(int32_t, G00C559C0, 0x00c559c0)
#ifndef RE_HOOK_BUILD
extern int32_t G00C559C0;
#endif
#define G00C559C4 GAME_VAR(int32_t, G00C559C4, 0x00c559c4)
#ifndef RE_HOOK_BUILD
extern int32_t G00C559C4;
#endif
#define G00C559C8 GAME_VAR(int32_t, G00C559C8, 0x00c559c8)
#ifndef RE_HOOK_BUILD
extern int32_t G00C559C8;
#endif
#define G00C559CC GAME_VAR(int32_t, G00C559CC, 0x00c559cc)
#ifndef RE_HOOK_BUILD
extern int32_t G00C559CC;
#endif
#define G00C559D0 GAME_VAR(int32_t, G00C559D0, 0x00c559d0)
#ifndef RE_HOOK_BUILD
extern int32_t G00C559D0;
#endif
#define G00C559D4 GAME_VAR(int32_t, G00C559D4, 0x00c559d4)
#ifndef RE_HOOK_BUILD
extern int32_t G00C559D4;
#endif
#define G00C55A5C GAME_VAR(int32_t, G00C55A5C, 0x00c55a5c)
#ifndef RE_HOOK_BUILD
extern int32_t G00C55A5C;
#endif
#define G00C81988 GAME_VAR(int32_t, G00C81988, 0x00c81988)
#ifndef RE_HOOK_BUILD
extern int32_t G00C81988;
#endif
#define G00C8198C GAME_VAR(int32_t, G00C8198C, 0x00c8198c)
#ifndef RE_HOOK_BUILD
extern int32_t G00C8198C;
#endif
#define G00D12408 GAME_VAR(int32_t, G00D12408, 0x00d12408)
#ifndef RE_HOOK_BUILD
extern int32_t G00D12408;
#endif
#define G00D12418 GAME_VAR(int32_t, G00D12418, 0x00d12418)
#ifndef RE_HOOK_BUILD
extern int32_t G00D12418;
#endif
#define G00D1241C GAME_VAR(int32_t, G00D1241C, 0x00d1241c)
#ifndef RE_HOOK_BUILD
extern int32_t G00D1241C;
#endif
#define G00D14EEC GAME_VAR(int32_t, G00D14EEC, 0x00d14eec)
#ifndef RE_HOOK_BUILD
extern int32_t G00D14EEC;
#endif
#define G00D14EF0 GAME_VAR(uint8_t *, G00D14EF0, 0x00d14ef0)   /* значок RFLECT (004cb857) */
#ifndef RE_HOOK_BUILD
extern uint8_t *G00D14EF0;
#endif
#define G00D14EF4 GAME_VAR(int32_t, G00D14EF4, 0x00d14ef4)
#ifndef RE_HOOK_BUILD
extern int32_t G00D14EF4;
#endif
#define G00D164EC GAME_VAR(uint8_t *, G00D164EC, 0x00d164ec)   /* значок SPLASH (004cb857) */
#ifndef RE_HOOK_BUILD
extern uint8_t *G00D164EC;
#endif
#define G00D164F0 GAME_VAR(uint8_t, G00D164F0, 0x00d164f0)
#ifndef RE_HOOK_BUILD
extern uint8_t G00D164F0;
#endif
#define G00D17AE4 GAME_VAR(uint8_t, G00D17AE4, 0x00d17ae4)
#ifndef RE_HOOK_BUILD
extern uint8_t G00D17AE4;
#endif
#define G00D17B04 GAME_VAR(uint8_t, G00D17B04, 0x00d17b04)
#ifndef RE_HOOK_BUILD
extern uint8_t G00D17B04;
#endif
#define G00D17B08 GAME_VAR(int32_t, G00D17B08, 0x00d17b08)
#ifndef RE_HOOK_BUILD
extern int32_t G00D17B08;
#endif
#define G00D17B10 GAME_VAR(uint8_t, G00D17B10, 0x00d17b10)
#ifndef RE_HOOK_BUILD
extern uint8_t G00D17B10;
#endif
#define G00D17B1C GAME_VAR(int32_t, G00D17B1C, 0x00d17b1c)
#ifndef RE_HOOK_BUILD
extern int32_t G00D17B1C;
#endif
#define G00D17B20 GAME_VAR(uint8_t, G00D17B20, 0x00d17b20)
#ifndef RE_HOOK_BUILD
extern uint8_t G00D17B20;
#endif
#define G00D17B21 GAME_VAR(uint8_t, G00D17B21, 0x00d17b21)
#ifndef RE_HOOK_BUILD
extern uint8_t G00D17B21;
#endif
#define G010DE220 GAME_VAR(int32_t, G010DE220, 0x010de220)
#ifndef RE_HOOK_BUILD
extern int32_t G010DE220;
#endif
#define G010DE224 GAME_VAR(int32_t, G010DE224, 0x010de224)
#ifndef RE_HOOK_BUILD
extern int32_t G010DE224;
#endif
#define G010DE228 GAME_VAR(int32_t, G010DE228, 0x010de228)
#ifndef RE_HOOK_BUILD
extern int32_t G010DE228;
#endif
#define G010DE22C GAME_VAR(int32_t, G010DE22C, 0x010de22c)
#ifndef RE_HOOK_BUILD
extern int32_t G010DE22C;
#endif
#define G010FFA20 GAME_VAR(int32_t, G010FFA20, 0x010ffa20)
#ifndef RE_HOOK_BUILD
extern int32_t G010FFA20;
#endif
#define G010FFB40 GAME_VAR(int32_t, G010FFB40, 0x010ffb40)
#ifndef RE_HOOK_BUILD
extern int32_t G010FFB40;
#endif
#define G010FFD04 GAME_VAR(int32_t, G010FFD04, 0x010ffd04)
#ifndef RE_HOOK_BUILD
extern int32_t G010FFD04;
#endif
#define G010FFD08 GAME_VAR(int32_t, G010FFD08, 0x010ffd08)
#ifndef RE_HOOK_BUILD
extern int32_t G010FFD08;
#endif
#define G01105D60 GAME_VAR(int32_t, G01105D60, 0x01105d60)
#ifndef RE_HOOK_BUILD
extern int32_t G01105D60;
#endif
#define G01105D80 GAME_VAR(int32_t, G01105D80, 0x01105d80)
#ifndef RE_HOOK_BUILD
extern int32_t G01105D80;
#endif
#define G0110B24C GAME_VAR(int32_t, G0110B24C, 0x0110b24c)
#ifndef RE_HOOK_BUILD
extern int32_t G0110B24C;
#endif
#define G01129580 GAME_VAR(int32_t, G01129580, 0x01129580)
#ifndef RE_HOOK_BUILD
extern int32_t G01129580;
#endif
#define G0113A6C0 GAME_VAR(int32_t, G0113A6C0, 0x0113a6c0)
#ifndef RE_HOOK_BUILD
extern int32_t G0113A6C0;
#endif
#define G011426F8 GAME_VAR(int32_t, G011426F8, 0x011426f8)
#ifndef RE_HOOK_BUILD
extern int32_t G011426F8;
#endif
#define G01144284 GAME_VAR(int32_t, G01144284, 0x01144284)
#ifndef RE_HOOK_BUILD
extern int32_t G01144284;
#endif
#define G011EFFE4 GAME_VAR(int32_t, G011EFFE4, 0x011effe4)
#ifndef RE_HOOK_BUILD
extern int32_t G011EFFE4;
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
