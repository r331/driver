#pragma once
#include "gvar.h"
#include "ported118.h"
#include "unported.h"
#include "menustate.h"
#include <stdint.h>
#include "uihandlers3.h"
#include "uihandlers2.h"
#include "uihandlers.h"
#include "smallfuncs.h"
#include "ported8.h"
#include "ported7.h"
#include "ported6.h"
#include "ported5.h"
#include "ported4.h"
#include "ported11.h"
#include "menustate.h"
#include "globalsets.h"
#include <string.h>
#include <math.h>
/* Партия v0.46 */
#define g_00b87e38 P11_00b87e38
#define g_01271060 MenuMode1271060
#define g_0057b56c Q0057B56C
#define g_00bdfa40 P12_00bdfa40
#define P12_00bdfa40 GAME_VAR(int32_t,P12_00bdfa40,0x00bdfa40)
#ifndef RE_HOOK_BUILD
#pragma push_macro("P12_00bdfa40") /*gvi*/
#undef P12_00bdfa40 /*gvi*/
extern int32_t P12_00bdfa40;
#pragma pop_macro("P12_00bdfa40") /*gvi*/
#endif
#define g_00b87ef8 P12_00b87ef8
#define P12_00b87ef8 GAME_VAR(int32_t,P12_00b87ef8,0x00b87ef8)
#ifndef RE_HOOK_BUILD
#pragma push_macro("P12_00b87ef8") /*gvi*/
#undef P12_00b87ef8 /*gvi*/
extern int32_t P12_00b87ef8;
#pragma pop_macro("P12_00b87ef8") /*gvi*/
#endif
#define g_005f7e5c P12_005f7e5c
#define P12_005f7e5c GAME_VAR(int32_t,P12_005f7e5c,0x005f7e5c)
#ifndef RE_HOOK_BUILD
#pragma push_macro("P12_005f7e5c") /*gvi*/
#undef P12_005f7e5c /*gvi*/
extern int32_t P12_005f7e5c;
#pragma pop_macro("P12_005f7e5c") /*gvi*/
#endif
#define g_005d577c MenuCounter5D577C
#define g_005f7e60 P12_005f7e60
#define P12_005f7e60 GAME_VAR(int32_t,P12_005f7e60,0x005f7e60)
#ifndef RE_HOOK_BUILD
#pragma push_macro("P12_005f7e60") /*gvi*/
#undef P12_005f7e60 /*gvi*/
extern int32_t P12_005f7e60;
#pragma pop_macro("P12_005f7e60") /*gvi*/
#endif
#define g_00b87eec G6_00B87EEC
#define g_0057b72c Q0057B72C
#define g_00575f50 P12_00575f50
#define P12_00575f50 GAME_VAR(int32_t,P12_00575f50,0x00575f50)
#ifndef RE_HOOK_BUILD
#pragma push_macro("P12_00575f50") /*gvi*/
#undef P12_00575f50 /*gvi*/
extern int32_t P12_00575f50;
#pragma pop_macro("P12_00575f50") /*gvi*/
#endif
#define g_00b87e58 P12_00b87e58
#define P12_00b87e58 GAME_VAR(int32_t,P12_00b87e58,0x00b87e58)
#ifndef RE_HOOK_BUILD
#pragma push_macro("P12_00b87e58") /*gvi*/
#undef P12_00b87e58 /*gvi*/
extern int32_t P12_00b87e58;
#pragma pop_macro("P12_00b87e58") /*gvi*/
#endif
#define g_00b87e5c P12_00b87e5c
#define P12_00b87e5c GAME_VAR(int32_t,P12_00b87e5c,0x00b87e5c)
#ifndef RE_HOOK_BUILD
#pragma push_macro("P12_00b87e5c") /*gvi*/
#undef P12_00b87e5c /*gvi*/
extern int32_t P12_00b87e5c;
#pragma pop_macro("P12_00b87e5c") /*gvi*/
#endif
#define g_005fea60 G005FEA60
#define g_00b32980 P12_00b32980
#define P12_00b32980 GAME_VAR(float,P12_00b32980,0x00b32980)
#ifndef RE_HOOK_BUILD
#pragma push_macro("P12_00b32980") /*gvi*/
#undef P12_00b32980 /*gvi*/
extern float P12_00b32980;
#pragma pop_macro("P12_00b32980") /*gvi*/
#endif
#define g_00b3297c P12_00b3297c
#define P12_00b3297c GAME_VAR(float,P12_00b3297c,0x00b3297c)
#ifndef RE_HOOK_BUILD
#pragma push_macro("P12_00b3297c") /*gvi*/
#undef P12_00b3297c /*gvi*/
extern float P12_00b3297c;
#pragma pop_macro("P12_00b3297c") /*gvi*/
#endif
#define g_00b5a778 G6_00B5A778
#define g_00546020 P8_00546020
#define g_00546054 P11_00546054
#define g_00546088 P12_00546088
#define P12_00546088 GAME_VAR(float,P12_00546088,0x00546088)
#ifndef RE_HOOK_BUILD
#pragma push_macro("P12_00546088") /*gvi*/
#undef P12_00546088 /*gvi*/
extern float P12_00546088;
#pragma pop_macro("P12_00546088") /*gvi*/
#endif
#define g_00546084 P12_00546084
#define P12_00546084 GAME_VAR(float,P12_00546084,0x00546084)
#ifndef RE_HOOK_BUILD
#pragma push_macro("P12_00546084") /*gvi*/
#undef P12_00546084 /*gvi*/
extern float P12_00546084;
#pragma pop_macro("P12_00546084") /*gvi*/
#endif
#define g_0125f3e0 P11_0125f3e0
#define g_01270c38 P11_01270c38
typedef float p12_00ba53a0_t[0xdbba];
#define g_00ba53a0 P12_00ba53a0
#define P12_00ba53a0 GAME_VAR(p12_00ba53a0_t,P12_00ba53a0,0x00ba53a0)
#ifndef RE_HOOK_BUILD
#pragma push_macro("P12_00ba53a0") /*gvi*/
#undef P12_00ba53a0 /*gvi*/
extern p12_00ba53a0_t P12_00ba53a0;
#pragma pop_macro("P12_00ba53a0") /*gvi*/
#endif
#define g_01144284 G01144284
#define g_01145934 G01145934
#define g_011426f8 G011426F8
#define g_0113a6c0 G0113A6C0
typedef uint32_t p12_01144340_t[0x100];
#define g_01144340 P12_01144340
#define P12_01144340 GAME_VAR(p12_01144340_t,P12_01144340,0x01144340)
#ifndef RE_HOOK_BUILD
#pragma push_macro("P12_01144340") /*gvi*/
#undef P12_01144340 /*gvi*/
extern p12_01144340_t P12_01144340;
#pragma pop_macro("P12_01144340") /*gvi*/
#endif
typedef uint8_t p12_011443e0_t[0x40*0x54];
#define g_011443e0 P12_011443e0
/* v1.47: таблица трафика 011443e0 — в native одна TrafficRecs (director.h); P12_011443e0, A_011443E0, P21_Entries — её имена */
#ifdef RE_HOOK_BUILD
#define P12_011443e0 GAME_VAR(p12_011443e0_t,P12_011443e0,0x011443e0)
#else
#pragma push_macro("TrafficRecs") /*gvi*/
#undef TrafficRecs /*gvi*/
extern uint8_t TrafficRecs[0x40 * 0x54];
#pragma pop_macro("TrafficRecs") /*gvi*/
#define P12_011443e0 TrafficRecs
#endif
typedef uint32_t p12_0112da00_t[8*0x336];
#define g_0112da00 P12_0112da00
#define P12_0112da00 GAME_VAR(p12_0112da00_t,P12_0112da00,0x0112da00)
#ifndef RE_HOOK_BUILD
#pragma push_macro("P12_0112da00") /*gvi*/
#undef P12_0112da00 /*gvi*/
extern p12_0112da00_t P12_0112da00;
#pragma pop_macro("P12_0112da00") /*gvi*/
#endif
/* v1.48: флаги частиц 00c5678c = A_00C56780 + 0xc (шаг 0xb4), список свободных 00c594a0 = P43_FreeList */
typedef uint32_t p12_00c5678c_t[0x40*0x2d];
typedef int32_t p12_00c594a0_t[0x40];
#ifdef RE_HOOK_BUILD
#define P12_00c5678c GAME_VAR(p12_00c5678c_t,P12_00c5678c,0x00c5678c)
#define P12_00c594a0 GAME_VAR(p12_00c594a0_t,P12_00c594a0,0x00c594a0)
#else
#pragma push_macro("A_00C56780") /*gvi*/
#undef A_00C56780 /*gvi*/
#pragma push_macro("P43_FreeList") /*gvi*/
#undef P43_FreeList /*gvi*/
extern uint8_t A_00C56780[]; extern int32_t P43_FreeList[];
#pragma pop_macro("P43_FreeList") /*gvi*/
#pragma pop_macro("A_00C56780") /*gvi*/
#define P12_00c5678c (*(p12_00c5678c_t *)(A_00C56780 + 0xc))
#define P12_00c594a0 (*(p12_00c594a0_t *)P43_FreeList)
#endif
#define g_00c5678c P12_00c5678c
#define g_00c594a0 P12_00c594a0
#define g_00bdf980 P12_00bdf980
#define P12_00bdf980 GAME_VAR(int32_t,P12_00bdf980,0x00bdf980)
#ifndef RE_HOOK_BUILD
#pragma push_macro("P12_00bdf980") /*gvi*/
#undef P12_00bdf980 /*gvi*/
extern int32_t P12_00bdf980;
#pragma pop_macro("P12_00bdf980") /*gvi*/
#endif
#define g_00bde728 P12_00bde728
#define P12_00bde728 GAME_VAR(int32_t,P12_00bde728,0x00bde728)
#ifndef RE_HOOK_BUILD
#pragma push_macro("P12_00bde728") /*gvi*/
#undef P12_00bde728 /*gvi*/
extern int32_t P12_00bde728;
#pragma pop_macro("P12_00bde728") /*gvi*/
#endif
#define g_00bde764 P12_00bde764
#define P12_00bde764 GAME_VAR(int32_t,P12_00bde764,0x00bde764)
#ifndef RE_HOOK_BUILD
#pragma push_macro("P12_00bde764") /*gvi*/
#undef P12_00bde764 /*gvi*/
extern int32_t P12_00bde764;
#pragma pop_macro("P12_00bde764") /*gvi*/
#endif
#define g_00bde760 P12_00bde760
#define P12_00bde760 GAME_VAR(int32_t,P12_00bde760,0x00bde760)
#ifndef RE_HOOK_BUILD
#pragma push_macro("P12_00bde760") /*gvi*/
#undef P12_00bde760 /*gvi*/
extern int32_t P12_00bde760;
#pragma pop_macro("P12_00bde760") /*gvi*/
#endif
#define g_00b5a898 P12_00b5a898
#define P12_00b5a898 GAME_VAR(int32_t,P12_00b5a898,0x00b5a898)
#ifndef RE_HOOK_BUILD
#pragma push_macro("P12_00b5a898") /*gvi*/
#undef P12_00b5a898 /*gvi*/
extern int32_t P12_00b5a898;
#pragma pop_macro("P12_00b5a898") /*gvi*/
#endif
typedef int32_t p12_0054b010_t[0x100];
#define g_0054b010 P12_0054b010
#define P12_0054b010 GAME_VAR(p12_0054b010_t,P12_0054b010,0x0054b010)
#ifndef RE_HOOK_BUILD
#pragma push_macro("P12_0054b010") /*gvi*/
#undef P12_0054b010 /*gvi*/
extern p12_0054b010_t P12_0054b010;
#pragma pop_macro("P12_0054b010") /*gvi*/
#endif
typedef int32_t p12_005fe7a8_t[0x40];
#define g_005fe7a8 P12_005fe7a8
#define P12_005fe7a8 GAME_VAR(p12_005fe7a8_t,P12_005fe7a8,0x005fe7a8)
#ifndef RE_HOOK_BUILD
#pragma push_macro("P12_005fe7a8") /*gvi*/
#undef P12_005fe7a8 /*gvi*/
extern p12_005fe7a8_t P12_005fe7a8;
#pragma pop_macro("P12_005fe7a8") /*gvi*/
#endif
#define g_005fe84c UiVar005FE84C
typedef int32_t p12_005fe884_t[0x40];
#define g_005fe884 P12_005fe884
#define P12_005fe884 GAME_VAR(p12_005fe884_t,P12_005fe884,0x005fe884)
#ifndef RE_HOOK_BUILD
#pragma push_macro("P12_005fe884") /*gvi*/
#undef P12_005fe884 /*gvi*/
extern p12_005fe884_t P12_005fe884;
#pragma pop_macro("P12_005fe884") /*gvi*/
#endif
#define g_005fe928 UiVar005FE928
#define g_00d17b90 P12_00d17b90
#define P12_00d17b90 GAME_VAR(int32_t,P12_00d17b90,0x00d17b90)
#ifndef RE_HOOK_BUILD
#pragma push_macro("P12_00d17b90") /*gvi*/
#undef P12_00d17b90 /*gvi*/
extern int32_t P12_00d17b90;
#pragma pop_macro("P12_00d17b90") /*gvi*/
#endif
#define g_005fea98 D_005fea98
#define g_005feb60 P12_005feb60
#define P12_005feb60 GAME_VAR(int32_t,P12_005feb60,0x005feb60)
#ifndef RE_HOOK_BUILD
#pragma push_macro("P12_005feb60") /*gvi*/
#undef P12_005feb60 /*gvi*/
extern int32_t P12_005feb60;
#pragma pop_macro("P12_005feb60") /*gvi*/
#endif
#define g_005feb48 UiVar005FEB48
#define g_005feb00 G005FEB00
#define g_005fea54 G005FEA54
#define g_005feda0 D_005feda0
#define g_005febbc P12_005febbc
#define P12_005febbc (P118_Route + 0x2c)   /* v1.63: кадры ключей маршрута камеры — поле +0x2c P118_Route 005feb90 */
#define g_005feeec P8_005feeec
#define g_005feef0 P12_005feef0
#define P12_005feef0 GAME_VAR(int32_t,P12_005feef0,0x005feef0)
#ifndef RE_HOOK_BUILD
#pragma push_macro("P12_005feef0") /*gvi*/
#undef P12_005feef0 /*gvi*/
extern int32_t P12_005feef0;
#pragma pop_macro("P12_005feef0") /*gvi*/
#endif
#define g_005feef4 P12_005feef4
#define P12_005feef4 GAME_VAR(int32_t,P12_005feef4,0x005feef4)
#ifndef RE_HOOK_BUILD
#pragma push_macro("P12_005feef4") /*gvi*/
#undef P12_005feef4 /*gvi*/
extern int32_t P12_005feef4;
#pragma pop_macro("P12_005feef4") /*gvi*/
#endif
#define g_005feef8 P12_005feef8
#define P12_005feef8 GAME_VAR(int32_t,P12_005feef8,0x005feef8)
#ifndef RE_HOOK_BUILD
#pragma push_macro("P12_005feef8") /*gvi*/
#undef P12_005feef8 /*gvi*/
extern int32_t P12_005feef8;
#pragma pop_macro("P12_005feef8") /*gvi*/
#endif
typedef int32_t p12_005fee40_t[0x10];
#define g_005fee40 P12_005fee40
#define P12_005fee40 GAME_VAR(p12_005fee40_t,P12_005fee40,0x005fee40)
#ifndef RE_HOOK_BUILD
#pragma push_macro("P12_005fee40") /*gvi*/
#undef P12_005fee40 /*gvi*/
extern p12_005fee40_t P12_005fee40;
#pragma pop_macro("P12_005fee40") /*gvi*/
#endif
typedef uint8_t p12_005fee60_t[0x200];
#define g_005fee60 P12_005fee60
#define P12_005fee60 GAME_VAR(p12_005fee60_t,P12_005fee60,0x005fee60)
#ifndef RE_HOOK_BUILD
#pragma push_macro("P12_005fee60") /*gvi*/
#undef P12_005fee60 /*gvi*/
extern p12_005fee60_t P12_005fee60;
#pragma pop_macro("P12_005fee60") /*gvi*/
#endif
#define g_01252b74 P12_01252b74
#define P12_01252b74 GAME_VAR(int32_t,P12_01252b74,0x01252b74)
#ifndef RE_HOOK_BUILD
#pragma push_macro("P12_01252b74") /*gvi*/
#undef P12_01252b74 /*gvi*/
extern int32_t P12_01252b74;
#pragma pop_macro("P12_01252b74") /*gvi*/
#endif
typedef int32_t p12_01252aa0_t[0x40];
#define g_01252aa0 P12_01252aa0
#define P12_01252aa0 GAME_VAR(p12_01252aa0_t,P12_01252aa0,0x01252aa0)
#ifndef RE_HOOK_BUILD
#pragma push_macro("P12_01252aa0") /*gvi*/
#undef P12_01252aa0 /*gvi*/
extern p12_01252aa0_t P12_01252aa0;
#pragma pop_macro("P12_01252aa0") /*gvi*/
#endif
#define g_00cff9ac P12_00cff9ac
#define P12_00cff9ac GAME_VAR(int32_t,P12_00cff9ac,0x00cff9ac)
#ifndef RE_HOOK_BUILD
#pragma push_macro("P12_00cff9ac") /*gvi*/
#undef P12_00cff9ac /*gvi*/
extern int32_t P12_00cff9ac;
#pragma pop_macro("P12_00cff9ac") /*gvi*/
#endif
#define g_00b1c3f0 P12_00b1c3f0
#define P12_00b1c3f0 GAME_VAR(int32_t,P12_00b1c3f0,0x00b1c3f0)
#ifndef RE_HOOK_BUILD
#pragma push_macro("P12_00b1c3f0") /*gvi*/
#undef P12_00b1c3f0 /*gvi*/
extern int32_t P12_00b1c3f0;
#pragma pop_macro("P12_00b1c3f0") /*gvi*/
#endif
#define g_00b1c3dc P12_00b1c3dc
#define P12_00b1c3dc GAME_VAR(int32_t,P12_00b1c3dc,0x00b1c3dc)
#ifndef RE_HOOK_BUILD
#pragma push_macro("P12_00b1c3dc") /*gvi*/
#undef P12_00b1c3dc /*gvi*/
extern int32_t P12_00b1c3dc;
#pragma pop_macro("P12_00b1c3dc") /*gvi*/
#endif
typedef uint8_t p12_01146f20_t[0x40*0x1c];
#define g_01146f20 P12_01146f20
#define P12_01146f20 GAME_VAR(p12_01146f20_t,P12_01146f20,0x01146f20)
#ifndef RE_HOOK_BUILD
#pragma push_macro("P12_01146f20") /*gvi*/
#undef P12_01146f20 /*gvi*/
extern p12_01146f20_t P12_01146f20;
#pragma pop_macro("P12_01146f20") /*gvi*/
#endif
typedef int32_t p12_00b1c3f4_t[0x40];
#define g_00b1c3f4 P12_00b1c3f4
#define P12_00b1c3f4 GAME_VAR(p12_00b1c3f4_t,P12_00b1c3f4,0x00b1c3f4)
#ifndef RE_HOOK_BUILD
#pragma push_macro("P12_00b1c3f4") /*gvi*/
#undef P12_00b1c3f4 /*gvi*/
extern p12_00b1c3f4_t P12_00b1c3f4;
#pragma pop_macro("P12_00b1c3f4") /*gvi*/
#endif
typedef uint8_t p12_01145a60_t[0x100*0x10];
#define g_01145a60 P12_01145a60
#define P12_01145a60 GAME_VAR(p12_01145a60_t,P12_01145a60,0x01145a60)
#ifndef RE_HOOK_BUILD
#pragma push_macro("P12_01145a60") /*gvi*/
#undef P12_01145a60 /*gvi*/
extern p12_01145a60_t P12_01145a60;
#pragma pop_macro("P12_01145a60") /*gvi*/
#endif
#define g_00553850 MenuVar553850
#define g_00d118c0 G8_00D118C0
#define g_011237b8 P12_011237b8
#define P12_011237b8 GAME_VAR(int32_t,P12_011237b8,0x011237b8)
#ifndef RE_HOOK_BUILD
#pragma push_macro("P12_011237b8") /*gvi*/
#undef P12_011237b8 /*gvi*/
extern int32_t P12_011237b8;
#pragma pop_macro("P12_011237b8") /*gvi*/
#endif
#define g_00bdc28c P11_00bdc28c
#define g_011173c8 S_011173C8
typedef uint8_t p12_0110b260_t[200*0x3c];
#define g_0110b260 P12_0110b260
#define P12_0110b260 GAME_VAR(p12_0110b260_t,P12_0110b260,0x0110b260)
#ifndef RE_HOOK_BUILD
#pragma push_macro("P12_0110b260") /*gvi*/
#undef P12_0110b260 /*gvi*/
extern p12_0110b260_t P12_0110b260;
#pragma pop_macro("P12_0110b260") /*gvi*/
#endif
#define g_00b5a76c S_00B5A76C
#define g_00b5a770 S_00B5A770
typedef int32_t p12_00574530_t[16];
#define g_00574530 P12_00574530
#define P12_00574530 GAME_VAR(p12_00574530_t,P12_00574530,0x00574530)
#ifndef RE_HOOK_BUILD
#pragma push_macro("P12_00574530") /*gvi*/
#undef P12_00574530 /*gvi*/
extern p12_00574530_t P12_00574530;
#pragma pop_macro("P12_00574530") /*gvi*/
#endif
typedef int32_t p12_00c7d800_t[8];
#define g_00c7d800 P12_00c7d800
#define P12_00c7d800 GAME_VAR(p12_00c7d800_t,P12_00c7d800,0x00c7d800)
#ifndef RE_HOOK_BUILD
#pragma push_macro("P12_00c7d800") /*gvi*/
#undef P12_00c7d800 /*gvi*/
extern p12_00c7d800_t P12_00c7d800;
#pragma pop_macro("P12_00c7d800") /*gvi*/
#endif
#define g_00c7d828 P12_00c7d828
#define P12_00c7d828 GAME_VAR(int32_t,P12_00c7d828,0x00c7d828)
#ifndef RE_HOOK_BUILD
#pragma push_macro("P12_00c7d828") /*gvi*/
#undef P12_00c7d828 /*gvi*/
extern int32_t P12_00c7d828;
#pragma pop_macro("P12_00c7d828") /*gvi*/
#endif
#define g_00c7d834 P12_00c7d834
#define P12_00c7d834 GAME_VAR(int32_t,P12_00c7d834,0x00c7d834)
#ifndef RE_HOOK_BUILD
#pragma push_macro("P12_00c7d834") /*gvi*/
#undef P12_00c7d834 /*gvi*/
extern int32_t P12_00c7d834;
#pragma pop_macro("P12_00c7d834") /*gvi*/
#endif
#define g_00c7d840 P12_00c7d840
#define P12_00c7d840 GAME_VAR(int32_t,P12_00c7d840,0x00c7d840)
#ifndef RE_HOOK_BUILD
#pragma push_macro("P12_00c7d840") /*gvi*/
#undef P12_00c7d840 /*gvi*/
extern int32_t P12_00c7d840;
#pragma pop_macro("P12_00c7d840") /*gvi*/
#endif
#define g_00c7d84c P12_00c7d84c
#define P12_00c7d84c GAME_VAR(int32_t,P12_00c7d84c,0x00c7d84c)
#ifndef RE_HOOK_BUILD
#pragma push_macro("P12_00c7d84c") /*gvi*/
#undef P12_00c7d84c /*gvi*/
extern int32_t P12_00c7d84c;
#pragma pop_macro("P12_00c7d84c") /*gvi*/
#endif
#define g_00c595a0 P12_00c595a0
#define P12_00c595a0 GAME_VAR(int32_t,P12_00c595a0,0x00c595a0)
#ifndef RE_HOOK_BUILD
#pragma push_macro("P12_00c595a0") /*gvi*/
#undef P12_00c595a0 /*gvi*/
extern int32_t P12_00c595a0;
#pragma pop_macro("P12_00c595a0") /*gvi*/
#endif
#define g_00c55034 P12_00c55034
#define P12_00c55034 GAME_VAR(int32_t,P12_00c55034,0x00c55034)
#ifndef RE_HOOK_BUILD
#pragma push_macro("P12_00c55034") /*gvi*/
#undef P12_00c55034 /*gvi*/
extern int32_t P12_00c55034;
#pragma pop_macro("P12_00c55034") /*gvi*/
#endif
#define g_00d11878 S_00D11878
#define g_00d044d0 P12_00d044d0
#define P12_00d044d0 GAME_VAR(int32_t,P12_00d044d0,0x00d044d0)
#ifndef RE_HOOK_BUILD
#pragma push_macro("P12_00d044d0") /*gvi*/
#undef P12_00d044d0 /*gvi*/
extern int32_t P12_00d044d0;
#pragma pop_macro("P12_00d044d0") /*gvi*/
#endif
#include "strtab.h"
#define g_00c55820 P12_00c55820
#define P12_00c55820 P97_StrAddr   /* единая таблица строк 00c55820 */
#define g_00c821a0 P12_00c821a0
#define P12_00c821a0 GAME_VAR(int32_t,P12_00c821a0,0x00c821a0)
#ifndef RE_HOOK_BUILD
#pragma push_macro("P12_00c821a0") /*gvi*/
#undef P12_00c821a0 /*gvi*/
extern int32_t P12_00c821a0;
#pragma pop_macro("P12_00c821a0") /*gvi*/
#endif
#define g_00b52a38 P12_00b52a38
#define P12_00b52a38 GAME_VAR(int32_t,P12_00b52a38,0x00b52a38)
#ifndef RE_HOOK_BUILD
#pragma push_macro("P12_00b52a38") /*gvi*/
#undef P12_00b52a38 /*gvi*/
extern int32_t P12_00b52a38;
#pragma pop_macro("P12_00b52a38") /*gvi*/
#endif
#define g_00b32970 P12_00b32970
#define P12_00b32970 GAME_VAR(int32_t,P12_00b32970,0x00b32970)
#ifndef RE_HOOK_BUILD
#pragma push_macro("P12_00b32970") /*gvi*/
#undef P12_00b32970 /*gvi*/
extern int32_t P12_00b32970;
#pragma pop_macro("P12_00b32970") /*gvi*/
#endif
#define g_00b93ce0 P12_00b93ce0
#define P12_00b93ce0 GAME_VAR(int32_t,P12_00b93ce0,0x00b93ce0)
#ifndef RE_HOOK_BUILD
#pragma push_macro("P12_00b93ce0") /*gvi*/
#undef P12_00b93ce0 /*gvi*/
extern int32_t P12_00b93ce0;
#pragma pop_macro("P12_00b93ce0") /*gvi*/
#endif
typedef int32_t p12_00576688_t[0x40*3];
#define g_00576688 P12_00576688
#define P12_00576688 GAME_VAR(p12_00576688_t,P12_00576688,0x00576688)
#ifndef RE_HOOK_BUILD
#pragma push_macro("P12_00576688") /*gvi*/
#undef P12_00576688 /*gvi*/
extern p12_00576688_t P12_00576688;
#pragma pop_macro("P12_00576688") /*gvi*/
#endif
#define g_00c808d0 P12_00c808d0
/* v1.47: 00c808d0 = P101_Hud[4] (значение полосы HUD, float) — в native макрос над P101_Hud */
#ifdef RE_HOOK_BUILD
#define P12_00c808d0 GAME_VAR(float,P12_00c808d0,0x00c808d0)
#else
#pragma push_macro("P101_Hud") /*gvi*/
#undef P101_Hud /*gvi*/
extern uint32_t P101_Hud[12];
#pragma pop_macro("P101_Hud") /*gvi*/
#define P12_00c808d0 (*(float *)(void *)((uint8_t *)P101_Hud + 0x10))
#endif
#define M12(a,b) Call0040CCB4(a,b)
int32_t P12_Wrap004046C8(void);
uint32_t P12_Fn00404F70(void);
uint32_t P12_Fn00404FAE(void);
uint32_t P12_Fn004152A7(void);
int32_t P12_Fn00407563(void);
int32_t P12_Fn0040A45B(void);
int32_t P12_Fn0040A4AD(void);
void P12_Fn004129DF(int32_t p);
int32_t P12_Fn00412A4B(void);
int32_t P12_Fn00412AB9(void);
int32_t P12_Fn00412B27(void);
int32_t P12_Fn00412B95(void);
int32_t P12_Fn00412C03(void);
int32_t P12_Fn00412C71(void);
int32_t P12_Fn00412CDF(void);
int32_t P12_Fn00412D4D(void);
int32_t P12_Fn00413596(void);
int32_t P12_Fn004136EC(void);
int32_t P12_Fn0041373A(void);
int32_t P12_Fn00413788(void);
int32_t P12_Fn004137D6(void);
int32_t P12_Fn00413973(void);
int32_t P12_Fn00413CBF(void);
void P12_Fn004183F7(uint32_t a, uint32_t b);
void P12_Fn00418433(uint32_t a, uint32_t b);
void P12_Fn0050229C(void);
void P12_Fn00526427(void);
void P12_Fn00496505(void);
void P12_Fn00491360(void);
void P12_Fn0048EBC8(void);
void P12_Fn00511FB8(void);
void P12_Fn005229F0(void);
void P12_Fn005188EC(void);
uint32_t P12_Fn0040F09C(void);
uint32_t P12_Fn004120AF(void);
uint32_t P12_Fn004124AF(void);
void P12_Fn0040C813(uint32_t a, int32_t b);
void P12_Fn0040DA56(uint32_t a);
void P12_Fn0041A8CD(void);
uint32_t P12_Fn0041AECF(void);
void P12_Fn0041AF85(void);
int32_t P12_Fn00426580(int32_t p);
void P12_Fn00425EE0(void);
void P12_Fn00489ED6(void);
void P12_Fn0048A627(void);
void P12_Fn0048A46B(int32_t p, int32_t v);
void P12_Fn004AAE34(void);
void P12_Fn004B9933(void);
void P12_Fn0050E963(void);
void P12_Fn0050C010(void);
void P12_Fn00516E76(void);
void P12_Fn004DC8EA(void);
void P12_Fn004E5982(int32_t a, int32_t b, int32_t c);
/* v1.58: буфер интерполированных кватернионов деталей 00c81ba0 (шаг 0x14, до 00c82020) */
typedef float p12_lerp_t[0x120];
#define P12_PartLerp GAME_VAR(p12_lerp_t, P12_PartLerp, 0x00c81ba0)
#ifndef RE_HOOK_BUILD
#pragma push_macro("P12_PartLerp") /*gvi*/
#undef P12_PartLerp /*gvi*/
extern p12_lerp_t P12_PartLerp;
#pragma pop_macro("P12_PartLerp") /*gvi*/
#endif
void P12_Fn004F3E78(const float *a, const float *b, float t);   /* 004f3e78: a/b — кадры пути (заголовок 0x10 + записи 0x14) */
void P12_Fn00504699(int32_t a, int32_t b);
void P12_Fn00525CB7(int32_t p);
/* gvar-img v2.03 begin (tools/gen_gvar_img.py) */
#if !defined(RE_HOOK_BUILD) && !defined(RE_GVAR_PLAIN)
#undef P12_00bdfa40
#define P12_00bdfa40 (*(int32_t *)re_gvar(0x00bdfa40u, sizeof(int32_t), (void *)&P12_00bdfa40))
#undef P12_00b87ef8
#define P12_00b87ef8 (*(int32_t *)re_gvar(0x00b87ef8u, sizeof(int32_t), (void *)&P12_00b87ef8))
#undef P12_005f7e5c
#define P12_005f7e5c (*(int32_t *)re_gvar(0x005f7e5cu, sizeof(int32_t), (void *)&P12_005f7e5c))
#undef P12_005f7e60
#define P12_005f7e60 (*(int32_t *)re_gvar(0x005f7e60u, sizeof(int32_t), (void *)&P12_005f7e60))
#undef P12_00575f50
#define P12_00575f50 (*(int32_t *)re_gvar(0x00575f50u, sizeof(int32_t), (void *)&P12_00575f50))
#undef P12_00b87e58
#define P12_00b87e58 (*(int32_t *)re_gvar(0x00b87e58u, sizeof(int32_t), (void *)&P12_00b87e58))
#undef P12_00b87e5c
#define P12_00b87e5c (*(int32_t *)re_gvar(0x00b87e5cu, sizeof(int32_t), (void *)&P12_00b87e5c))
#undef P12_00b32980
#define P12_00b32980 (*(float *)re_gvar(0x00b32980u, sizeof(float), (void *)&P12_00b32980))
#undef P12_00b3297c
#define P12_00b3297c (*(float *)re_gvar(0x00b3297cu, sizeof(float), (void *)&P12_00b3297c))
#undef P12_00546088
#define P12_00546088 (*(float *)re_gvar(0x00546088u, sizeof(float), (void *)&P12_00546088))
#undef P12_00546084
#define P12_00546084 (*(float *)re_gvar(0x00546084u, sizeof(float), (void *)&P12_00546084))
#undef P12_00ba53a0
#define P12_00ba53a0 (*(p12_00ba53a0_t *)re_gvar(0x00ba53a0u, sizeof(p12_00ba53a0_t), (void *)&P12_00ba53a0))
#undef P12_01144340
#define P12_01144340 (*(p12_01144340_t *)re_gvar(0x01144340u, sizeof(p12_01144340_t), (void *)&P12_01144340))
#undef P12_0112da00
#define P12_0112da00 (*(p12_0112da00_t *)re_gvar(0x0112da00u, sizeof(p12_0112da00_t), (void *)&P12_0112da00))
#undef P12_00bdf980
#define P12_00bdf980 (*(int32_t *)re_gvar(0x00bdf980u, sizeof(int32_t), (void *)&P12_00bdf980))
#undef P12_00bde728
#define P12_00bde728 (*(int32_t *)re_gvar(0x00bde728u, sizeof(int32_t), (void *)&P12_00bde728))
#undef P12_00bde764
#define P12_00bde764 (*(int32_t *)re_gvar(0x00bde764u, sizeof(int32_t), (void *)&P12_00bde764))
#undef P12_00bde760
#define P12_00bde760 (*(int32_t *)re_gvar(0x00bde760u, sizeof(int32_t), (void *)&P12_00bde760))
#undef P12_00b5a898
#define P12_00b5a898 (*(int32_t *)re_gvar(0x00b5a898u, sizeof(int32_t), (void *)&P12_00b5a898))
#undef P12_0054b010
#define P12_0054b010 (*(p12_0054b010_t *)re_gvar(0x0054b010u, sizeof(p12_0054b010_t), (void *)&P12_0054b010))
#undef P12_005fe7a8
#define P12_005fe7a8 (*(p12_005fe7a8_t *)re_gvar(0x005fe7a8u, sizeof(p12_005fe7a8_t), (void *)&P12_005fe7a8))
#undef P12_005fe884
#define P12_005fe884 (*(p12_005fe884_t *)re_gvar(0x005fe884u, sizeof(p12_005fe884_t), (void *)&P12_005fe884))
#undef P12_00d17b90
#define P12_00d17b90 (*(int32_t *)re_gvar(0x00d17b90u, sizeof(int32_t), (void *)&P12_00d17b90))
#undef P12_005feb60
#define P12_005feb60 (*(int32_t *)re_gvar(0x005feb60u, sizeof(int32_t), (void *)&P12_005feb60))
#undef P12_005feef0
#define P12_005feef0 (*(int32_t *)re_gvar(0x005feef0u, sizeof(int32_t), (void *)&P12_005feef0))
#undef P12_005feef4
#define P12_005feef4 (*(int32_t *)re_gvar(0x005feef4u, sizeof(int32_t), (void *)&P12_005feef4))
#undef P12_005feef8
#define P12_005feef8 (*(int32_t *)re_gvar(0x005feef8u, sizeof(int32_t), (void *)&P12_005feef8))
#undef P12_005fee40
#define P12_005fee40 (*(p12_005fee40_t *)re_gvar(0x005fee40u, sizeof(p12_005fee40_t), (void *)&P12_005fee40))
#undef P12_005fee60
#define P12_005fee60 (*(p12_005fee60_t *)re_gvar(0x005fee60u, sizeof(p12_005fee60_t), (void *)&P12_005fee60))
#undef P12_01252b74
#define P12_01252b74 (*(int32_t *)re_gvar(0x01252b74u, sizeof(int32_t), (void *)&P12_01252b74))
#undef P12_01252aa0
#define P12_01252aa0 (*(p12_01252aa0_t *)re_gvar(0x01252aa0u, sizeof(p12_01252aa0_t), (void *)&P12_01252aa0))
#undef P12_00cff9ac
#define P12_00cff9ac (*(int32_t *)re_gvar(0x00cff9acu, sizeof(int32_t), (void *)&P12_00cff9ac))
#undef P12_00b1c3f0
#define P12_00b1c3f0 (*(int32_t *)re_gvar(0x00b1c3f0u, sizeof(int32_t), (void *)&P12_00b1c3f0))
#undef P12_00b1c3dc
#define P12_00b1c3dc (*(int32_t *)re_gvar(0x00b1c3dcu, sizeof(int32_t), (void *)&P12_00b1c3dc))
#undef P12_01146f20
#define P12_01146f20 (*(p12_01146f20_t *)re_gvar(0x01146f20u, sizeof(p12_01146f20_t), (void *)&P12_01146f20))
#undef P12_00b1c3f4
#define P12_00b1c3f4 (*(p12_00b1c3f4_t *)re_gvar(0x00b1c3f4u, sizeof(p12_00b1c3f4_t), (void *)&P12_00b1c3f4))
#undef P12_01145a60
#define P12_01145a60 (*(p12_01145a60_t *)re_gvar(0x01145a60u, sizeof(p12_01145a60_t), (void *)&P12_01145a60))
#undef P12_011237b8
#define P12_011237b8 (*(int32_t *)re_gvar(0x011237b8u, sizeof(int32_t), (void *)&P12_011237b8))
#undef P12_0110b260
#define P12_0110b260 (*(p12_0110b260_t *)re_gvar(0x0110b260u, sizeof(p12_0110b260_t), (void *)&P12_0110b260))
#undef P12_00574530
#define P12_00574530 (*(p12_00574530_t *)re_gvar(0x00574530u, sizeof(p12_00574530_t), (void *)&P12_00574530))
#undef P12_00c7d800
#define P12_00c7d800 (*(p12_00c7d800_t *)re_gvar(0x00c7d800u, sizeof(p12_00c7d800_t), (void *)&P12_00c7d800))
#undef P12_00c7d828
#define P12_00c7d828 (*(int32_t *)re_gvar(0x00c7d828u, sizeof(int32_t), (void *)&P12_00c7d828))
#undef P12_00c7d834
#define P12_00c7d834 (*(int32_t *)re_gvar(0x00c7d834u, sizeof(int32_t), (void *)&P12_00c7d834))
#undef P12_00c7d840
#define P12_00c7d840 (*(int32_t *)re_gvar(0x00c7d840u, sizeof(int32_t), (void *)&P12_00c7d840))
#undef P12_00c7d84c
#define P12_00c7d84c (*(int32_t *)re_gvar(0x00c7d84cu, sizeof(int32_t), (void *)&P12_00c7d84c))
#undef P12_00c595a0
#define P12_00c595a0 (*(int32_t *)re_gvar(0x00c595a0u, sizeof(int32_t), (void *)&P12_00c595a0))
#undef P12_00c55034
#define P12_00c55034 (*(int32_t *)re_gvar(0x00c55034u, sizeof(int32_t), (void *)&P12_00c55034))
#undef P12_00d044d0
#define P12_00d044d0 (*(int32_t *)re_gvar(0x00d044d0u, sizeof(int32_t), (void *)&P12_00d044d0))
#undef P12_00c821a0
#define P12_00c821a0 (*(int32_t *)re_gvar(0x00c821a0u, sizeof(int32_t), (void *)&P12_00c821a0))
#undef P12_00b52a38
#define P12_00b52a38 (*(int32_t *)re_gvar(0x00b52a38u, sizeof(int32_t), (void *)&P12_00b52a38))
#undef P12_00b32970
#define P12_00b32970 (*(int32_t *)re_gvar(0x00b32970u, sizeof(int32_t), (void *)&P12_00b32970))
#undef P12_00b93ce0
#define P12_00b93ce0 (*(int32_t *)re_gvar(0x00b93ce0u, sizeof(int32_t), (void *)&P12_00b93ce0))
#undef P12_00576688
#define P12_00576688 (*(p12_00576688_t *)re_gvar(0x00576688u, sizeof(p12_00576688_t), (void *)&P12_00576688))
#undef P12_PartLerp
#define P12_PartLerp (*(p12_lerp_t *)re_gvar(0x00c81ba0u, sizeof(p12_lerp_t), (void *)&P12_PartLerp))
#endif
/* gvar-img v2.03 end */
