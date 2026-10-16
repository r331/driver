/* Партия v0.41 */
#pragma once
#include "menugfx.h"
#include "menutab.h"
#include "ported5.h"
#include "smallfuncs.h"
#include <string.h>
typedef void (*FnV1)(int32_t);
typedef void (*FnV2)(int32_t, int32_t);
typedef int32_t (*FnI1)(int32_t);
typedef uint8_t g6a_01145A60[0x400];
typedef uint8_t g6a_00549F84[0x400];
typedef uint8_t g6a_0054A25C[0x400];
typedef uint8_t g6a_0054DBCC[0x260];  /* v1.48: до конца таблицы меню 0054de2c (прежде 0x400) */
typedef uint8_t g6a_0054E56C[0x400];
typedef uint8_t g6a_0054E834[0x400];
typedef uint8_t g6a_00562B70[0x100];
typedef uint8_t *g6a_00B2F30C[256];
typedef int32_t g6a_00B91BC4[16];
typedef uint32_t g6a_00C5678C[0x200];
typedef int32_t g6a_00C594A0[0x40];
typedef uint8_t g6a_00D04A50[0x100];
#define G6_011368C4 GAME_VAR(int32_t, G6_011368C4, 0x011368c4)
#ifndef RE_HOOK_BUILD
#pragma push_macro("G6_011368C4") /*gvi*/
#undef G6_011368C4 /*gvi*/
extern int32_t G6_011368C4;
#pragma pop_macro("G6_011368C4") /*gvi*/
#endif
#define G6_01136920 GAME_VAR(int32_t, G6_01136920, 0x01136920)
#ifndef RE_HOOK_BUILD
#pragma push_macro("G6_01136920") /*gvi*/
#undef G6_01136920 /*gvi*/
extern int32_t G6_01136920;
#pragma pop_macro("G6_01136920") /*gvi*/
#endif
#define G6_01145A60 GAME_VAR(g6a_01145A60, G6_01145A60, 0x01145a60)
#ifndef RE_HOOK_BUILD
#pragma push_macro("G6_01145A60") /*gvi*/
#undef G6_01145A60 /*gvi*/
extern g6a_01145A60 G6_01145A60;
#pragma pop_macro("G6_01145A60") /*gvi*/
#endif
#define G6_0125F3F0 GAME_VAR(int32_t, G6_0125F3F0, 0x0125f3f0)
#ifndef RE_HOOK_BUILD
#pragma push_macro("G6_0125F3F0") /*gvi*/
#undef G6_0125F3F0 /*gvi*/
extern int32_t G6_0125F3F0;
#pragma pop_macro("G6_0125F3F0") /*gvi*/
#endif
#define G6_01270C28 GAME_VAR(int32_t, G6_01270C28, 0x01270c28)
#ifndef RE_HOOK_BUILD
#pragma push_macro("G6_01270C28") /*gvi*/
#undef G6_01270C28 /*gvi*/
extern int32_t G6_01270C28;
#pragma pop_macro("G6_01270C28") /*gvi*/
#endif
#define G6_01270C34 GAME_VAR(int32_t, G6_01270C34, 0x01270c34)
#ifndef RE_HOOK_BUILD
#pragma push_macro("G6_01270C34") /*gvi*/
#undef G6_01270C34 /*gvi*/
extern int32_t G6_01270C34;
#pragma pop_macro("G6_01270C34") /*gvi*/
#endif
#define G6_01270D20 GAME_VAR(FnI1, G6_01270D20, 0x01270d20)
#ifndef RE_HOOK_BUILD
extern FnI1 G6_01270D20;
#endif
#define G6_01270D28 GAME_VAR(FnV1, G6_01270D28, 0x01270d28)
#ifndef RE_HOOK_BUILD
extern FnV1 G6_01270D28;
#endif
#define G6_01270DE4 GAME_VAR(FnV1, G6_01270DE4, 0x01270de4)
#ifndef RE_HOOK_BUILD
extern FnV1 G6_01270DE4;
#endif
#define G6_00549F84 GAME_VAR(g6a_00549F84, G6_00549F84, 0x00549f84)
#ifndef RE_HOOK_BUILD
#pragma push_macro("G6_00549F84") /*gvi*/
#undef G6_00549F84 /*gvi*/
extern g6a_00549F84 G6_00549F84;
#pragma pop_macro("G6_00549F84") /*gvi*/
#endif
#define G6_0054A25C MENUGFX_VAR(g6a_0054A25C, G6_0054A25C, 0x0054a25c)
#ifndef RE_HOOK_BUILD
#endif
#define G6_0054DBCC MENUTAB_VAR(g6a_0054DBCC, G6_0054DBCC, 0x0054dbcc)
#define G6_0054E56C GAME_VAR(g6a_0054E56C, G6_0054E56C, 0x0054e56c)
#ifndef RE_HOOK_BUILD
#pragma push_macro("G6_0054E56C") /*gvi*/
#undef G6_0054E56C /*gvi*/
extern g6a_0054E56C G6_0054E56C;
#pragma pop_macro("G6_0054E56C") /*gvi*/
#endif
#define G6_0054E834 GAME_VAR(g6a_0054E834, G6_0054E834, 0x0054e834)
#ifndef RE_HOOK_BUILD
#pragma push_macro("G6_0054E834") /*gvi*/
#undef G6_0054E834 /*gvi*/
extern g6a_0054E834 G6_0054E834;
#pragma pop_macro("G6_0054E834") /*gvi*/
#endif
#define G6_0054EF2C GAME_VAR(int32_t, G6_0054EF2C, 0x0054ef2c)
#ifndef RE_HOOK_BUILD
#pragma push_macro("G6_0054EF2C") /*gvi*/
#undef G6_0054EF2C /*gvi*/
extern int32_t G6_0054EF2C;
#pragma pop_macro("G6_0054EF2C") /*gvi*/
#endif
#define G6_005624A0 GAME_VAR(int32_t, G6_005624A0, 0x005624a0)
#ifndef RE_HOOK_BUILD
#pragma push_macro("G6_005624A0") /*gvi*/
#undef G6_005624A0 /*gvi*/
extern int32_t G6_005624A0;
#pragma pop_macro("G6_005624A0") /*gvi*/
#endif
#define G6_00562B70 GAME_VAR(g6a_00562B70, G6_00562B70, 0x00562b70)
#ifndef RE_HOOK_BUILD
#pragma push_macro("G6_00562B70") /*gvi*/
#undef G6_00562B70 /*gvi*/
extern g6a_00562B70 G6_00562B70;
#pragma pop_macro("G6_00562B70") /*gvi*/
#endif
#define G6_005755C8 GAME_VAR(int32_t, G6_005755C8, 0x005755c8)
#ifndef RE_HOOK_BUILD
#pragma push_macro("G6_005755C8") /*gvi*/
#undef G6_005755C8 /*gvi*/
extern int32_t G6_005755C8;
#pragma pop_macro("G6_005755C8") /*gvi*/
#endif
#define G6_00575A70 GAME_VAR(int32_t, G6_00575A70, 0x00575a70)
#ifndef RE_HOOK_BUILD
#pragma push_macro("G6_00575A70") /*gvi*/
#undef G6_00575A70 /*gvi*/
extern int32_t G6_00575A70;
#pragma pop_macro("G6_00575A70") /*gvi*/
#endif
#define G6_00575EBC GAME_VAR(int32_t, G6_00575EBC, 0x00575ebc)
#ifndef RE_HOOK_BUILD
#pragma push_macro("G6_00575EBC") /*gvi*/
#undef G6_00575EBC /*gvi*/
extern int32_t G6_00575EBC;
#pragma pop_macro("G6_00575EBC") /*gvi*/
#endif
#define G6_00575EC0 GAME_VAR(int32_t, G6_00575EC0, 0x00575ec0)
#ifndef RE_HOOK_BUILD
#pragma push_macro("G6_00575EC0") /*gvi*/
#undef G6_00575EC0 /*gvi*/
extern int32_t G6_00575EC0;
#pragma pop_macro("G6_00575EC0") /*gvi*/
#endif
#define G6_00575EEC GAME_VAR(int32_t, G6_00575EEC, 0x00575eec)
#ifndef RE_HOOK_BUILD
#pragma push_macro("G6_00575EEC") /*gvi*/
#undef G6_00575EEC /*gvi*/
extern int32_t G6_00575EEC;
#pragma pop_macro("G6_00575EEC") /*gvi*/
#endif
#define G6_00575EF4 GAME_VAR(int32_t, G6_00575EF4, 0x00575ef4)
#ifndef RE_HOOK_BUILD
#pragma push_macro("G6_00575EF4") /*gvi*/
#undef G6_00575EF4 /*gvi*/
extern int32_t G6_00575EF4;
#pragma pop_macro("G6_00575EF4") /*gvi*/
#endif
#define G6_00575F00 GAME_VAR(int32_t, G6_00575F00, 0x00575f00)
#ifndef RE_HOOK_BUILD
#pragma push_macro("G6_00575F00") /*gvi*/
#undef G6_00575F00 /*gvi*/
extern int32_t G6_00575F00;
#pragma pop_macro("G6_00575F00") /*gvi*/
#endif
#define G6_00575F04 GAME_VAR(int32_t, G6_00575F04, 0x00575f04)
#ifndef RE_HOOK_BUILD
#pragma push_macro("G6_00575F04") /*gvi*/
#undef G6_00575F04 /*gvi*/
extern int32_t G6_00575F04;
#pragma pop_macro("G6_00575F04") /*gvi*/
#endif
#define G6_00575F20 GAME_VAR(int32_t, G6_00575F20, 0x00575f20)
#ifndef RE_HOOK_BUILD
#pragma push_macro("G6_00575F20") /*gvi*/
#undef G6_00575F20 /*gvi*/
extern int32_t G6_00575F20;
#pragma pop_macro("G6_00575F20") /*gvi*/
#endif
#define G6_00575F34 GAME_VAR(int32_t, G6_00575F34, 0x00575f34)
#ifndef RE_HOOK_BUILD
#pragma push_macro("G6_00575F34") /*gvi*/
#undef G6_00575F34 /*gvi*/
extern int32_t G6_00575F34;
#pragma pop_macro("G6_00575F34") /*gvi*/
#endif
#define G6_00575F38 GAME_VAR(int32_t, G6_00575F38, 0x00575f38)
#ifndef RE_HOOK_BUILD
#pragma push_macro("G6_00575F38") /*gvi*/
#undef G6_00575F38 /*gvi*/
extern int32_t G6_00575F38;
#pragma pop_macro("G6_00575F38") /*gvi*/
#endif
#define G6_0057B728 GAME_VAR(int32_t, G6_0057B728, 0x0057b728)
#ifndef RE_HOOK_BUILD
#pragma push_macro("G6_0057B728") /*gvi*/
#undef G6_0057B728 /*gvi*/
extern int32_t G6_0057B728;
#pragma pop_macro("G6_0057B728") /*gvi*/
#endif
#define G6_005D5788 GAME_VAR(int32_t, G6_005D5788, 0x005d5788)
#ifndef RE_HOOK_BUILD
#pragma push_macro("G6_005D5788") /*gvi*/
#undef G6_005D5788 /*gvi*/
extern int32_t G6_005D5788;
#pragma pop_macro("G6_005D5788") /*gvi*/
#endif
#define G6_005FE9BC GAME_VAR(int32_t, G6_005FE9BC, 0x005fe9bc)
#ifndef RE_HOOK_BUILD
#pragma push_macro("G6_005FE9BC") /*gvi*/
#undef G6_005FE9BC /*gvi*/
extern int32_t G6_005FE9BC;
#pragma pop_macro("G6_005FE9BC") /*gvi*/
#endif
#define G6_005FE9CC GAME_VAR(int32_t, G6_005FE9CC, 0x005fe9cc)
#ifndef RE_HOOK_BUILD
#pragma push_macro("G6_005FE9CC") /*gvi*/
#undef G6_005FE9CC /*gvi*/
extern int32_t G6_005FE9CC;
#pragma pop_macro("G6_005FE9CC") /*gvi*/
#endif
#define G6_005FEA7C GAME_VAR(int32_t, G6_005FEA7C, 0x005fea7c)
#ifndef RE_HOOK_BUILD
#pragma push_macro("G6_005FEA7C") /*gvi*/
#undef G6_005FEA7C /*gvi*/
extern int32_t G6_005FEA7C;
#pragma pop_macro("G6_005FEA7C") /*gvi*/
#endif
#define G6_005FED9C GAME_VAR(int32_t, G6_005FED9C, 0x005fed9c)
#ifndef RE_HOOK_BUILD
#pragma push_macro("G6_005FED9C") /*gvi*/
#undef G6_005FED9C /*gvi*/
extern int32_t G6_005FED9C;
#pragma pop_macro("G6_005FED9C") /*gvi*/
#endif
#define G6_00A421F0 GAME_VAR(int32_t, G6_00A421F0, 0x00a421f0)
#ifndef RE_HOOK_BUILD
#pragma push_macro("G6_00A421F0") /*gvi*/
#undef G6_00A421F0 /*gvi*/
extern int32_t G6_00A421F0;
#pragma pop_macro("G6_00A421F0") /*gvi*/
#endif
#define G6_00B1C224 GAME_VAR(int32_t, G6_00B1C224, 0x00b1c224)
#ifndef RE_HOOK_BUILD
#pragma push_macro("G6_00B1C224") /*gvi*/
#undef G6_00B1C224 /*gvi*/
extern int32_t G6_00B1C224;
#pragma pop_macro("G6_00B1C224") /*gvi*/
#endif
#define G6_00B20364 GAME_VAR(int32_t, G6_00B20364, 0x00b20364)
#ifndef RE_HOOK_BUILD
#pragma push_macro("G6_00B20364") /*gvi*/
#undef G6_00B20364 /*gvi*/
extern int32_t G6_00B20364;
#pragma pop_macro("G6_00B20364") /*gvi*/
#endif
#define G6_00B20368 GAME_VAR(int32_t, G6_00B20368, 0x00b20368)
#ifndef RE_HOOK_BUILD
#pragma push_macro("G6_00B20368") /*gvi*/
#undef G6_00B20368 /*gvi*/
extern int32_t G6_00B20368;
#pragma pop_macro("G6_00B20368") /*gvi*/
#endif
#define G6_00B2F30C GAME_VAR(g6a_00B2F30C, G6_00B2F30C, 0x00b2f30c)
#ifndef RE_HOOK_BUILD
extern g6a_00B2F30C G6_00B2F30C;
#endif
#define G6_00B31F40 GAME_VAR(int32_t, G6_00B31F40, 0x00b31f40)
#ifndef RE_HOOK_BUILD
#pragma push_macro("G6_00B31F40") /*gvi*/
#undef G6_00B31F40 /*gvi*/
extern int32_t G6_00B31F40;
#pragma pop_macro("G6_00B31F40") /*gvi*/
#endif
#define G6_00B5A778 GAME_VAR(int32_t, G6_00B5A778, 0x00b5a778)
#ifndef RE_HOOK_BUILD
#pragma push_macro("G6_00B5A778") /*gvi*/
#undef G6_00B5A778 /*gvi*/
extern int32_t G6_00B5A778;
#pragma pop_macro("G6_00B5A778") /*gvi*/
#endif
#define G6_00B5A838 GAME_VAR(uint8_t, G6_00B5A838, 0x00b5a838)
#ifndef RE_HOOK_BUILD
#pragma push_macro("G6_00B5A838") /*gvi*/
#undef G6_00B5A838 /*gvi*/
extern uint8_t G6_00B5A838;
#pragma pop_macro("G6_00B5A838") /*gvi*/
#endif
#define G6_00B5A839 GAME_VAR(uint8_t, G6_00B5A839, 0x00b5a839)
#ifndef RE_HOOK_BUILD
#pragma push_macro("G6_00B5A839") /*gvi*/
#undef G6_00B5A839 /*gvi*/
extern uint8_t G6_00B5A839;
#pragma pop_macro("G6_00B5A839") /*gvi*/
#endif
#define G6_00B5A83A GAME_VAR(uint8_t, G6_00B5A83A, 0x00b5a83a)
#ifndef RE_HOOK_BUILD
#pragma push_macro("G6_00B5A83A") /*gvi*/
#undef G6_00B5A83A /*gvi*/
extern uint8_t G6_00B5A83A;
#pragma pop_macro("G6_00B5A83A") /*gvi*/
#endif
#define G6_00B5A83C GAME_VAR(void*, G6_00B5A83C, 0x00b5a83c)
#ifndef RE_HOOK_BUILD
extern void* G6_00B5A83C;
#endif
#define G6_00B5A840 GAME_VAR(void*, G6_00B5A840, 0x00b5a840)
#ifndef RE_HOOK_BUILD
extern void* G6_00B5A840;
#endif
#define G6_00B5A8A0 GAME_VAR(int32_t, G6_00B5A8A0, 0x00b5a8a0)
#ifndef RE_HOOK_BUILD
#pragma push_macro("G6_00B5A8A0") /*gvi*/
#undef G6_00B5A8A0 /*gvi*/
extern int32_t G6_00B5A8A0;
#pragma pop_macro("G6_00B5A8A0") /*gvi*/
#endif
#define G6_00B5A8AC GAME_VAR(int32_t, G6_00B5A8AC, 0x00b5a8ac)
#ifndef RE_HOOK_BUILD
#pragma push_macro("G6_00B5A8AC") /*gvi*/
#undef G6_00B5A8AC /*gvi*/
extern int32_t G6_00B5A8AC;
#pragma pop_macro("G6_00B5A8AC") /*gvi*/
#endif
#define G6_00B5A8B0 GAME_VAR(int32_t, G6_00B5A8B0, 0x00b5a8b0)
#ifndef RE_HOOK_BUILD
#pragma push_macro("G6_00B5A8B0") /*gvi*/
#undef G6_00B5A8B0 /*gvi*/
extern int32_t G6_00B5A8B0;
#pragma pop_macro("G6_00B5A8B0") /*gvi*/
#endif
#define G6_00B87E20 GAME_VAR(int32_t, G6_00B87E20, 0x00b87e20)
#ifndef RE_HOOK_BUILD
#pragma push_macro("G6_00B87E20") /*gvi*/
#undef G6_00B87E20 /*gvi*/
extern int32_t G6_00B87E20;
#pragma pop_macro("G6_00B87E20") /*gvi*/
#endif
#define G6_00B87E50 GAME_VAR(int32_t, G6_00B87E50, 0x00b87e50)
#ifndef RE_HOOK_BUILD
#pragma push_macro("G6_00B87E50") /*gvi*/
#undef G6_00B87E50 /*gvi*/
extern int32_t G6_00B87E50;
#pragma pop_macro("G6_00B87E50") /*gvi*/
#endif
#define G6_00B87E74 GAME_VAR(int32_t, G6_00B87E74, 0x00b87e74)
#ifndef RE_HOOK_BUILD
#pragma push_macro("G6_00B87E74") /*gvi*/
#undef G6_00B87E74 /*gvi*/
extern int32_t G6_00B87E74;
#pragma pop_macro("G6_00B87E74") /*gvi*/
#endif
#define G6_00B87EA0 GAME_VAR(int32_t, G6_00B87EA0, 0x00b87ea0)
#ifndef RE_HOOK_BUILD
#pragma push_macro("G6_00B87EA0") /*gvi*/
#undef G6_00B87EA0 /*gvi*/
extern int32_t G6_00B87EA0;
#pragma pop_macro("G6_00B87EA0") /*gvi*/
#endif
#define G6_00B87EAC GAME_VAR(int32_t, G6_00B87EAC, 0x00b87eac)
#ifndef RE_HOOK_BUILD
#pragma push_macro("G6_00B87EAC") /*gvi*/
#undef G6_00B87EAC /*gvi*/
extern int32_t G6_00B87EAC;
#pragma pop_macro("G6_00B87EAC") /*gvi*/
#endif
#define G6_00B87EB0 GAME_VAR(int32_t, G6_00B87EB0, 0x00b87eb0)
#ifndef RE_HOOK_BUILD
#pragma push_macro("G6_00B87EB0") /*gvi*/
#undef G6_00B87EB0 /*gvi*/
extern int32_t G6_00B87EB0;
#pragma pop_macro("G6_00B87EB0") /*gvi*/
#endif
#define G6_00B87EEC GAME_VAR(int32_t, G6_00B87EEC, 0x00b87eec)
#ifndef RE_HOOK_BUILD
#pragma push_macro("G6_00B87EEC") /*gvi*/
#undef G6_00B87EEC /*gvi*/
extern int32_t G6_00B87EEC;
#pragma pop_macro("G6_00B87EEC") /*gvi*/
#endif
#define G6_00B87EFC GAME_VAR(int32_t, G6_00B87EFC, 0x00b87efc)
#ifndef RE_HOOK_BUILD
#pragma push_macro("G6_00B87EFC") /*gvi*/
#undef G6_00B87EFC /*gvi*/
extern int32_t G6_00B87EFC;
#pragma pop_macro("G6_00B87EFC") /*gvi*/
#endif
#define G6_00B91BC4 GAME_VAR(g6a_00B91BC4, G6_00B91BC4, 0x00b91bc4)
#ifndef RE_HOOK_BUILD
#pragma push_macro("G6_00B91BC4") /*gvi*/
#undef G6_00B91BC4 /*gvi*/
extern g6a_00B91BC4 G6_00B91BC4;
#pragma pop_macro("G6_00B91BC4") /*gvi*/
#endif
#define G6_00B91CF4 GAME_VAR(int32_t, G6_00B91CF4, 0x00b91cf4)
#ifndef RE_HOOK_BUILD
#pragma push_macro("G6_00B91CF4") /*gvi*/
#undef G6_00B91CF4 /*gvi*/
extern int32_t G6_00B91CF4;
#pragma pop_macro("G6_00B91CF4") /*gvi*/
#endif
#define G6_00B91D2C GAME_VAR(int32_t, G6_00B91D2C, 0x00b91d2c)
#ifndef RE_HOOK_BUILD
#pragma push_macro("G6_00B91D2C") /*gvi*/
#undef G6_00B91D2C /*gvi*/
extern int32_t G6_00B91D2C;
#pragma pop_macro("G6_00B91D2C") /*gvi*/
#endif
#define G6_00B91D34 GAME_VAR(int32_t, G6_00B91D34, 0x00b91d34)
#ifndef RE_HOOK_BUILD
#pragma push_macro("G6_00B91D34") /*gvi*/
#undef G6_00B91D34 /*gvi*/
extern int32_t G6_00B91D34;
#pragma pop_macro("G6_00B91D34") /*gvi*/
#endif
#define G6_00BDCB14 GAME_VAR(FnV2, G6_00BDCB14, 0x00bdcb14)
#ifndef RE_HOOK_BUILD
extern FnV2 G6_00BDCB14;
#endif
#define G6_00BDCB18 GAME_VAR(FnV1, G6_00BDCB18, 0x00bdcb18)
#ifndef RE_HOOK_BUILD
extern FnV1 G6_00BDCB18;
#endif
#define G6_00BDCB20 GAME_VAR(FnV1, G6_00BDCB20, 0x00bdcb20)
#ifndef RE_HOOK_BUILD
extern FnV1 G6_00BDCB20;
#endif
#define G6_00BDF9C0 GAME_VAR(int32_t, G6_00BDF9C0, 0x00bdf9c0)
#ifndef RE_HOOK_BUILD
#pragma push_macro("G6_00BDF9C0") /*gvi*/
#undef G6_00BDF9C0 /*gvi*/
extern int32_t G6_00BDF9C0;
#pragma pop_macro("G6_00BDF9C0") /*gvi*/
#endif
#define G6_00BDF9C4 GAME_VAR(int32_t, G6_00BDF9C4, 0x00bdf9c4)
#ifndef RE_HOOK_BUILD
#pragma push_macro("G6_00BDF9C4") /*gvi*/
#undef G6_00BDF9C4 /*gvi*/
extern int32_t G6_00BDF9C4;
#pragma pop_macro("G6_00BDF9C4") /*gvi*/
#endif
#define G6_00C557F8 GAME_VAR(int32_t, G6_00C557F8, 0x00c557f8)
#ifndef RE_HOOK_BUILD
#pragma push_macro("G6_00C557F8") /*gvi*/
#undef G6_00C557F8 /*gvi*/
extern int32_t G6_00C557F8;
#pragma pop_macro("G6_00C557F8") /*gvi*/
#endif
#define G6_00C55800 GAME_VAR(int32_t, G6_00C55800, 0x00c55800)
#ifndef RE_HOOK_BUILD
#pragma push_macro("G6_00C55800") /*gvi*/
#undef G6_00C55800 /*gvi*/
extern int32_t G6_00C55800;
#pragma pop_macro("G6_00C55800") /*gvi*/
#endif
/* v1.48: пул частиц 00c56780 (0x40 × 0xb4) в native — только A_00C56780; счётчик свободных 00c56764 — P43_FreeCnt,
   список свободных 00c594a0 — P43_FreeList (G6_/P12_ — макросы над ними) */
#ifdef RE_HOOK_BUILD
#define G6_00C56764 GAME_VAR(int32_t, G6_00C56764, 0x00c56764)
#define G6_00C5678C GAME_VAR(g6a_00C5678C, G6_00C5678C, 0x00c5678c)
#define G6_00C594A0 GAME_VAR(g6a_00C594A0, G6_00C594A0, 0x00c594a0)
#else
#pragma push_macro("A_00C56780") /*gvi*/
#undef A_00C56780 /*gvi*/
#pragma push_macro("P43_FreeCnt") /*gvi*/
#undef P43_FreeCnt /*gvi*/
#pragma push_macro("P43_FreeList") /*gvi*/
#undef P43_FreeList /*gvi*/
extern uint8_t A_00C56780[]; extern int32_t P43_FreeCnt; extern int32_t P43_FreeList[];
#pragma pop_macro("P43_FreeList") /*gvi*/
#pragma pop_macro("P43_FreeCnt") /*gvi*/
#pragma pop_macro("A_00C56780") /*gvi*/
#define G6_00C56764 P43_FreeCnt
#define G6_00C5678C (*(g6a_00C5678C *)(A_00C56780 + 0xc))
#define G6_00C594A0 (*(g6a_00C594A0 *)P43_FreeList)
#endif
#define G6_00C80C50 GAME_VAR(void*, G6_00C80C50, 0x00c80c50)
#ifndef RE_HOOK_BUILD
extern void* G6_00C80C50;
#endif
#define G6_00C81108 GAME_VAR(int32_t, G6_00C81108, 0x00c81108)
#ifndef RE_HOOK_BUILD
#pragma push_macro("G6_00C81108") /*gvi*/
#undef G6_00C81108 /*gvi*/
extern int32_t G6_00C81108;
#pragma pop_macro("G6_00C81108") /*gvi*/
#endif
#define G6_00CE0F20 GAME_VAR(void*, G6_00CE0F20, 0x00ce0f20)
#ifndef RE_HOOK_BUILD
extern void* G6_00CE0F20;
#endif
#define G6_00D00208 GAME_VAR(void*, G6_00D00208, 0x00d00208)
#ifndef RE_HOOK_BUILD
extern void* G6_00D00208;
#endif
#define G6_00D01268 GAME_VAR(void*, G6_00D01268, 0x00d01268)
#ifndef RE_HOOK_BUILD
extern void* G6_00D01268;
#endif
#define G6_00D04A50 GAME_VAR(g6a_00D04A50, G6_00D04A50, 0x00d04a50)
#ifndef RE_HOOK_BUILD
#pragma push_macro("G6_00D04A50") /*gvi*/
#undef G6_00D04A50 /*gvi*/
extern g6a_00D04A50 G6_00D04A50;
#pragma pop_macro("G6_00D04A50") /*gvi*/
#endif
#define G6_00D0DDC0 GAME_VAR(int32_t, G6_00D0DDC0, 0x00d0ddc0)
#ifndef RE_HOOK_BUILD
#pragma push_macro("G6_00D0DDC0") /*gvi*/
#undef G6_00D0DDC0 /*gvi*/
extern int32_t G6_00D0DDC0;
#pragma pop_macro("G6_00D0DDC0") /*gvi*/
#endif
#define G6_00D10E40 GAME_VAR(uint32_t, G6_00D10E40, 0x00d10e40)
#ifndef RE_HOOK_BUILD
#pragma push_macro("G6_00D10E40") /*gvi*/
#undef G6_00D10E40 /*gvi*/
extern uint32_t G6_00D10E40;
#pragma pop_macro("G6_00D10E40") /*gvi*/
#endif
#define G6_00D117A4 GAME_VAR(int32_t, G6_00D117A4, 0x00d117a4)
#ifndef RE_HOOK_BUILD
#pragma push_macro("G6_00D117A4") /*gvi*/
#undef G6_00D117A4 /*gvi*/
extern int32_t G6_00D117A4;
#pragma pop_macro("G6_00D117A4") /*gvi*/
#endif
#define G6_00D117A8 GAME_VAR(int32_t, G6_00D117A8, 0x00d117a8)
#ifndef RE_HOOK_BUILD
#pragma push_macro("G6_00D117A8") /*gvi*/
#undef G6_00D117A8 /*gvi*/
extern int32_t G6_00D117A8;
#pragma pop_macro("G6_00D117A8") /*gvi*/
#endif
#define G6_00D11800 GAME_VAR(uint32_t, G6_00D11800, 0x00d11800)
#ifndef RE_HOOK_BUILD
#pragma push_macro("G6_00D11800") /*gvi*/
#undef G6_00D11800 /*gvi*/
extern uint32_t G6_00D11800;
#pragma pop_macro("G6_00D11800") /*gvi*/
#endif
#define G6_00D11880 GAME_VAR(int32_t, G6_00D11880, 0x00d11880)
#ifndef RE_HOOK_BUILD
#pragma push_macro("G6_00D11880") /*gvi*/
#undef G6_00D11880 /*gvi*/
extern int32_t G6_00D11880;
#pragma pop_macro("G6_00D11880") /*gvi*/
#endif
#define G6_00D11928 GAME_VAR(int32_t, G6_00D11928, 0x00d11928)
#ifndef RE_HOOK_BUILD
#pragma push_macro("G6_00D11928") /*gvi*/
#undef G6_00D11928 /*gvi*/
extern int32_t G6_00D11928;
#pragma pop_macro("G6_00D11928") /*gvi*/
#endif
void MenuRed0040766D(void);
void MenuWhite004076E2(void);
void MenuRed00409C85(void);
void MenuWhite00409CFA(void);
void MenuRed00415904(void);
void MenuWhite00415979(void);
void MenuRed00419D3E(void);
void MenuWhite00419DB3(void);
void MenuWhite0041AF29(int32_t i);
void MenuMark00412228(void);
int32_t MenuToggle00408994(void);
int32_t MenuToggle00408C37(void);
int32_t MenuToggle00409142(void);
int32_t MenuToggle0050FE26(void);
int32_t MenuToggle0050FEE5(void);
int32_t MenuToggle00510028(void);
int32_t MenuTri0040E9B5(void);
int32_t MenuTri00419C8C(void);
int32_t MenuQuality004088DB(void);
int32_t MenuQuality0050FA70(void);
void SoundSetFormat005235D3(int32_t a, int32_t b);
void SoundSetVolA005235F2(int32_t a);
void SoundSetVolB0052360D(int32_t a);
int32_t MenuBits0041556C(void);
int32_t MenuRate00415623(void);
int32_t MenuSoundCh004156DD(void);
void MenuBits0050F8F2(void);
void MenuRate0050F930(void);
void MenuSoundCh0050F971(void);
void MenuSound0050F781(void);
void MenuMusic0050F8A2(void);
void MenuMusic0050F8CC(void);
int32_t MenuAnyFlag00413DF3(void);
void MenuBtn00414264(int32_t p);
void MenuBtn00414376(int32_t p);
void MenuBtn00414488(int32_t p);
void MenuBtn0041459A(int32_t p);
void SetFade0051707A(uint8_t r, uint8_t g, uint8_t b, int32_t d);
void MenuPageNext00417F59(void);
void MenuPagePrev00417FAC(void);
int32_t PoolAlloc004A2C12(void);
int32_t PoolNext004AC671(void);
int32_t PoolAlloc0051210C(void);
void ShutdownAudio004183A3(void);
void MenuBack005103EC(void);
void SoundMenuIn00419814(void);
void SoundMenuOut0051082A(void);
void SoundMenuSave0051080E(void);
int32_t DrvCall004246D1(int32_t a);
int32_t DrvSetMode0042655A(int32_t a);
void ClearHandles005223BE(void);
void StartAudio005233A0(void);
void NoopFn00528455(void);
void InitSubsys004BA443(void);
void Fwd004D2D9F(int32_t a, int32_t b, int32_t c, int32_t d);
void Reset004D600B(void);
void MenuAddItem004DC8B0(uint8_t *item, int32_t flag);
int32_t StepToward004E60C1(int32_t i);
uint32_t AngleToDir00514103(uint32_t a);
void ObjInit00514C43(uint8_t *o, uint16_t a, uint32_t b, uint32_t flags);
int32_t TypeIsKnown00514F0A(const int16_t *p);
void VecAdd3_00526F7E(float *a, const float *b);
void VecNeg4_00527123(float *a);
void VecAdd4_0052715E(const float *a, const float *b, float *r);
void VecSub4_005271A8(const float *a, const float *b, float *r);
void MatIdentity3_0052614F(float *m);
void CreditsTick005193D4(void);
int32_t CreditsNext00519D2C(void);
int32_t CreditsPrev00519D70(void);
void ResetPalette00519DF3(void);
void MenuClick004F8ACC(int32_t a);
void DrawTextLine004FBBC5(int32_t t);
void FreeBuf004FC57B(void);
void FreeMapBufs004ECE1A(void);
void FreeBufs00516E2E(void);
void Update005012A3(void);
void ActorStep00494678(uint8_t *p);
int32_t StartFlyby004A05C0(void);
void Dispatch0048A68E(int32_t i);
void Dispatch0041D50E(int32_t a, int32_t b, int32_t c, int32_t d);
int32_t Fwd0042482B(int32_t a, int32_t b, int32_t c, int32_t d);
int32_t SoundGetPos005242A7(int32_t i);
void SoundSetPos00523F8A(int32_t i, int32_t v);
void SoundPlay00523E50(uint32_t id, int32_t b, int32_t c);
void Mask004D9028(uint32_t a, uint32_t b);
void CursorWrap004D9478(void);
void CursorSet004D94B7(int32_t a, int32_t b);
/* gvar-img v2.03 begin (tools/gen_gvar_img.py) */
#if !defined(RE_HOOK_BUILD) && !defined(RE_GVAR_PLAIN)
#undef G6_011368C4
#define G6_011368C4 (*(int32_t *)re_gvar(0x011368c4u, sizeof(int32_t), (void *)&G6_011368C4))
#undef G6_01136920
#define G6_01136920 (*(int32_t *)re_gvar(0x01136920u, sizeof(int32_t), (void *)&G6_01136920))
#undef G6_01145A60
#define G6_01145A60 (*(g6a_01145A60 *)re_gvar(0x01145a60u, sizeof(g6a_01145A60), (void *)&G6_01145A60))
#undef G6_0125F3F0
#define G6_0125F3F0 (*(int32_t *)re_gvar(0x0125f3f0u, sizeof(int32_t), (void *)&G6_0125F3F0))
#undef G6_01270C28
#define G6_01270C28 (*(int32_t *)re_gvar(0x01270c28u, sizeof(int32_t), (void *)&G6_01270C28))
#undef G6_01270C34
#define G6_01270C34 (*(int32_t *)re_gvar(0x01270c34u, sizeof(int32_t), (void *)&G6_01270C34))
#undef G6_00549F84
#define G6_00549F84 (*(g6a_00549F84 *)re_gvar(0x00549f84u, sizeof(g6a_00549F84), (void *)&G6_00549F84))
#undef G6_0054E56C
#define G6_0054E56C (*(g6a_0054E56C *)re_gvar(0x0054e56cu, sizeof(g6a_0054E56C), (void *)&G6_0054E56C))
#undef G6_0054E834
#define G6_0054E834 (*(g6a_0054E834 *)re_gvar(0x0054e834u, sizeof(g6a_0054E834), (void *)&G6_0054E834))
#undef G6_0054EF2C
#define G6_0054EF2C (*(int32_t *)re_gvar(0x0054ef2cu, sizeof(int32_t), (void *)&G6_0054EF2C))
#undef G6_005624A0
#define G6_005624A0 (*(int32_t *)re_gvar(0x005624a0u, sizeof(int32_t), (void *)&G6_005624A0))
#undef G6_00562B70
#define G6_00562B70 (*(g6a_00562B70 *)re_gvar(0x00562b70u, sizeof(g6a_00562B70), (void *)&G6_00562B70))
#undef G6_005755C8
#define G6_005755C8 (*(int32_t *)re_gvar(0x005755c8u, sizeof(int32_t), (void *)&G6_005755C8))
#undef G6_00575A70
#define G6_00575A70 (*(int32_t *)re_gvar(0x00575a70u, sizeof(int32_t), (void *)&G6_00575A70))
#undef G6_00575EBC
#define G6_00575EBC (*(int32_t *)re_gvar(0x00575ebcu, sizeof(int32_t), (void *)&G6_00575EBC))
#undef G6_00575EC0
#define G6_00575EC0 (*(int32_t *)re_gvar(0x00575ec0u, sizeof(int32_t), (void *)&G6_00575EC0))
#undef G6_00575EEC
#define G6_00575EEC (*(int32_t *)re_gvar(0x00575eecu, sizeof(int32_t), (void *)&G6_00575EEC))
#undef G6_00575EF4
#define G6_00575EF4 (*(int32_t *)re_gvar(0x00575ef4u, sizeof(int32_t), (void *)&G6_00575EF4))
#undef G6_00575F00
#define G6_00575F00 (*(int32_t *)re_gvar(0x00575f00u, sizeof(int32_t), (void *)&G6_00575F00))
#undef G6_00575F04
#define G6_00575F04 (*(int32_t *)re_gvar(0x00575f04u, sizeof(int32_t), (void *)&G6_00575F04))
#undef G6_00575F20
#define G6_00575F20 (*(int32_t *)re_gvar(0x00575f20u, sizeof(int32_t), (void *)&G6_00575F20))
#undef G6_00575F34
#define G6_00575F34 (*(int32_t *)re_gvar(0x00575f34u, sizeof(int32_t), (void *)&G6_00575F34))
#undef G6_00575F38
#define G6_00575F38 (*(int32_t *)re_gvar(0x00575f38u, sizeof(int32_t), (void *)&G6_00575F38))
#undef G6_0057B728
#define G6_0057B728 (*(int32_t *)re_gvar(0x0057b728u, sizeof(int32_t), (void *)&G6_0057B728))
#undef G6_005D5788
#define G6_005D5788 (*(int32_t *)re_gvar(0x005d5788u, sizeof(int32_t), (void *)&G6_005D5788))
#undef G6_005FE9BC
#define G6_005FE9BC (*(int32_t *)re_gvar(0x005fe9bcu, sizeof(int32_t), (void *)&G6_005FE9BC))
#undef G6_005FE9CC
#define G6_005FE9CC (*(int32_t *)re_gvar(0x005fe9ccu, sizeof(int32_t), (void *)&G6_005FE9CC))
#undef G6_005FEA7C
#define G6_005FEA7C (*(int32_t *)re_gvar(0x005fea7cu, sizeof(int32_t), (void *)&G6_005FEA7C))
#undef G6_005FED9C
#define G6_005FED9C (*(int32_t *)re_gvar(0x005fed9cu, sizeof(int32_t), (void *)&G6_005FED9C))
#undef G6_00A421F0
#define G6_00A421F0 (*(int32_t *)re_gvar(0x00a421f0u, sizeof(int32_t), (void *)&G6_00A421F0))
#undef G6_00B1C224
#define G6_00B1C224 (*(int32_t *)re_gvar(0x00b1c224u, sizeof(int32_t), (void *)&G6_00B1C224))
#undef G6_00B20364
#define G6_00B20364 (*(int32_t *)re_gvar(0x00b20364u, sizeof(int32_t), (void *)&G6_00B20364))
#undef G6_00B20368
#define G6_00B20368 (*(int32_t *)re_gvar(0x00b20368u, sizeof(int32_t), (void *)&G6_00B20368))
#undef G6_00B31F40
#define G6_00B31F40 (*(int32_t *)re_gvar(0x00b31f40u, sizeof(int32_t), (void *)&G6_00B31F40))
#undef G6_00B5A778
#define G6_00B5A778 (*(int32_t *)re_gvar(0x00b5a778u, sizeof(int32_t), (void *)&G6_00B5A778))
#undef G6_00B5A838
#define G6_00B5A838 (*(uint8_t *)re_gvar(0x00b5a838u, sizeof(uint8_t), (void *)&G6_00B5A838))
#undef G6_00B5A839
#define G6_00B5A839 (*(uint8_t *)re_gvar(0x00b5a839u, sizeof(uint8_t), (void *)&G6_00B5A839))
#undef G6_00B5A83A
#define G6_00B5A83A (*(uint8_t *)re_gvar(0x00b5a83au, sizeof(uint8_t), (void *)&G6_00B5A83A))
#undef G6_00B5A8A0
#define G6_00B5A8A0 (*(int32_t *)re_gvar(0x00b5a8a0u, sizeof(int32_t), (void *)&G6_00B5A8A0))
#undef G6_00B5A8AC
#define G6_00B5A8AC (*(int32_t *)re_gvar(0x00b5a8acu, sizeof(int32_t), (void *)&G6_00B5A8AC))
#undef G6_00B5A8B0
#define G6_00B5A8B0 (*(int32_t *)re_gvar(0x00b5a8b0u, sizeof(int32_t), (void *)&G6_00B5A8B0))
#undef G6_00B87E20
#define G6_00B87E20 (*(int32_t *)re_gvar(0x00b87e20u, sizeof(int32_t), (void *)&G6_00B87E20))
#undef G6_00B87E50
#define G6_00B87E50 (*(int32_t *)re_gvar(0x00b87e50u, sizeof(int32_t), (void *)&G6_00B87E50))
#undef G6_00B87E74
#define G6_00B87E74 (*(int32_t *)re_gvar(0x00b87e74u, sizeof(int32_t), (void *)&G6_00B87E74))
#undef G6_00B87EA0
#define G6_00B87EA0 (*(int32_t *)re_gvar(0x00b87ea0u, sizeof(int32_t), (void *)&G6_00B87EA0))
#undef G6_00B87EAC
#define G6_00B87EAC (*(int32_t *)re_gvar(0x00b87eacu, sizeof(int32_t), (void *)&G6_00B87EAC))
#undef G6_00B87EB0
#define G6_00B87EB0 (*(int32_t *)re_gvar(0x00b87eb0u, sizeof(int32_t), (void *)&G6_00B87EB0))
#undef G6_00B87EEC
#define G6_00B87EEC (*(int32_t *)re_gvar(0x00b87eecu, sizeof(int32_t), (void *)&G6_00B87EEC))
#undef G6_00B87EFC
#define G6_00B87EFC (*(int32_t *)re_gvar(0x00b87efcu, sizeof(int32_t), (void *)&G6_00B87EFC))
#undef G6_00B91BC4
#define G6_00B91BC4 (*(g6a_00B91BC4 *)re_gvar(0x00b91bc4u, sizeof(g6a_00B91BC4), (void *)&G6_00B91BC4))
#undef G6_00B91CF4
#define G6_00B91CF4 (*(int32_t *)re_gvar(0x00b91cf4u, sizeof(int32_t), (void *)&G6_00B91CF4))
#undef G6_00B91D2C
#define G6_00B91D2C (*(int32_t *)re_gvar(0x00b91d2cu, sizeof(int32_t), (void *)&G6_00B91D2C))
#undef G6_00B91D34
#define G6_00B91D34 (*(int32_t *)re_gvar(0x00b91d34u, sizeof(int32_t), (void *)&G6_00B91D34))
#undef G6_00BDF9C0
#define G6_00BDF9C0 (*(int32_t *)re_gvar(0x00bdf9c0u, sizeof(int32_t), (void *)&G6_00BDF9C0))
#undef G6_00BDF9C4
#define G6_00BDF9C4 (*(int32_t *)re_gvar(0x00bdf9c4u, sizeof(int32_t), (void *)&G6_00BDF9C4))
#undef G6_00C557F8
#define G6_00C557F8 (*(int32_t *)re_gvar(0x00c557f8u, sizeof(int32_t), (void *)&G6_00C557F8))
#undef G6_00C55800
#define G6_00C55800 (*(int32_t *)re_gvar(0x00c55800u, sizeof(int32_t), (void *)&G6_00C55800))
#undef G6_00C81108
#define G6_00C81108 (*(int32_t *)re_gvar(0x00c81108u, sizeof(int32_t), (void *)&G6_00C81108))
#undef G6_00D04A50
#define G6_00D04A50 (*(g6a_00D04A50 *)re_gvar(0x00d04a50u, sizeof(g6a_00D04A50), (void *)&G6_00D04A50))
#undef G6_00D0DDC0
#define G6_00D0DDC0 (*(int32_t *)re_gvar(0x00d0ddc0u, sizeof(int32_t), (void *)&G6_00D0DDC0))
#undef G6_00D10E40
#define G6_00D10E40 (*(uint32_t *)re_gvar(0x00d10e40u, sizeof(uint32_t), (void *)&G6_00D10E40))
#undef G6_00D117A4
#define G6_00D117A4 (*(int32_t *)re_gvar(0x00d117a4u, sizeof(int32_t), (void *)&G6_00D117A4))
#undef G6_00D117A8
#define G6_00D117A8 (*(int32_t *)re_gvar(0x00d117a8u, sizeof(int32_t), (void *)&G6_00D117A8))
#undef G6_00D11800
#define G6_00D11800 (*(uint32_t *)re_gvar(0x00d11800u, sizeof(uint32_t), (void *)&G6_00D11800))
#undef G6_00D11880
#define G6_00D11880 (*(int32_t *)re_gvar(0x00d11880u, sizeof(int32_t), (void *)&G6_00D11880))
#undef G6_00D11928
#define G6_00D11928 (*(int32_t *)re_gvar(0x00d11928u, sizeof(int32_t), (void *)&G6_00D11928))
#endif
/* gvar-img v2.03 end */
