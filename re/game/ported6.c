/* Small front-end, sound, pool and vector helpers, each named <what><Game.exe address>.
   Menu tables are arrays of 16-byte rows whose first three bytes are the row's RGB colour;
   "Red"/"White" helpers recolour the selected row pair, "Toggle"/"Tri"/"Quality" cycle options. */
#include "ported129.h"
#include "ported43.h"   /* v2.09: P43_FreeCnt/P43_FreeList/A_00C56780 — объекты образа данных (пешеходы) */
#include "ported7.h"
#include "fpucw.h"
#include "ported6.h"
#include "ported148.h"
#include "ported137.h"
#include "ported40.h"
#include "engine.h"
#include "flush.h"
#include "carfields.h"
#include <stdio.h>
#include <stdlib.h>
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("G6_011368C4")
#undef G6_011368C4
#pragma push_macro("G6_011368C4") /*gvi*/
#undef G6_011368C4 /*gvi*/
int32_t G6_011368C4;
#pragma pop_macro("G6_011368C4") /*gvi*/
#pragma pop_macro("G6_011368C4")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("G6_01136920")
#undef G6_01136920
#pragma push_macro("G6_01136920") /*gvi*/
#undef G6_01136920 /*gvi*/
int32_t G6_01136920;
#pragma pop_macro("G6_01136920") /*gvi*/
#pragma pop_macro("G6_01136920")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("G6_01145A60")
#undef G6_01145A60
#pragma push_macro("G6_01145A60") /*gvi*/
#undef G6_01145A60 /*gvi*/
g6a_01145A60 G6_01145A60;
#pragma pop_macro("G6_01145A60") /*gvi*/
#pragma pop_macro("G6_01145A60")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("G6_0125F3F0")
#undef G6_0125F3F0
#pragma push_macro("G6_0125F3F0") /*gvi*/
#undef G6_0125F3F0 /*gvi*/
int32_t G6_0125F3F0;
#pragma pop_macro("G6_0125F3F0") /*gvi*/
#pragma pop_macro("G6_0125F3F0")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("G6_01270C28")
#undef G6_01270C28
#pragma push_macro("G6_01270C28") /*gvi*/
#undef G6_01270C28 /*gvi*/
int32_t G6_01270C28;
#pragma pop_macro("G6_01270C28") /*gvi*/
#pragma pop_macro("G6_01270C28")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("G6_01270C34")
#undef G6_01270C34
#pragma push_macro("G6_01270C34") /*gvi*/
#undef G6_01270C34 /*gvi*/
int32_t G6_01270C34;
#pragma pop_macro("G6_01270C34") /*gvi*/
#pragma pop_macro("G6_01270C34")
#endif
GAME_VAR_DEF(FnI1, G6_01270D20, 0x01270d20)
GAME_VAR_DEF(FnV1, G6_01270D28, 0x01270d28)
GAME_VAR_DEF(FnV1, G6_01270DE4, 0x01270de4)
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("G6_00549F84")
#undef G6_00549F84
#pragma push_macro("G6_00549F84") /*gvi*/
#undef G6_00549F84 /*gvi*/
g6a_00549F84 G6_00549F84;
#pragma pop_macro("G6_00549F84") /*gvi*/
#pragma pop_macro("G6_00549F84")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("G6_0054E56C")
#undef G6_0054E56C
#pragma push_macro("G6_0054E56C") /*gvi*/
#undef G6_0054E56C /*gvi*/
g6a_0054E56C G6_0054E56C;
#pragma pop_macro("G6_0054E56C") /*gvi*/
#pragma pop_macro("G6_0054E56C")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("G6_0054E834")
#undef G6_0054E834
#pragma push_macro("G6_0054E834") /*gvi*/
#undef G6_0054E834 /*gvi*/
g6a_0054E834 G6_0054E834;
#pragma pop_macro("G6_0054E834") /*gvi*/
#pragma pop_macro("G6_0054E834")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("G6_0054EF2C")
#undef G6_0054EF2C
#pragma push_macro("G6_0054EF2C") /*gvi*/
#undef G6_0054EF2C /*gvi*/
int32_t G6_0054EF2C;
#pragma pop_macro("G6_0054EF2C") /*gvi*/
#pragma pop_macro("G6_0054EF2C")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("G6_005624A0")
#undef G6_005624A0
#pragma push_macro("G6_005624A0") /*gvi*/
#undef G6_005624A0 /*gvi*/
int32_t G6_005624A0;
#pragma pop_macro("G6_005624A0") /*gvi*/
#pragma pop_macro("G6_005624A0")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("G6_00562B70")
#undef G6_00562B70
#pragma push_macro("G6_00562B70") /*gvi*/
#undef G6_00562B70 /*gvi*/
g6a_00562B70 G6_00562B70;
#pragma pop_macro("G6_00562B70") /*gvi*/
#pragma pop_macro("G6_00562B70")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("G6_005755C8")
#undef G6_005755C8
#pragma push_macro("G6_005755C8") /*gvi*/
#undef G6_005755C8 /*gvi*/
int32_t G6_005755C8;
#pragma pop_macro("G6_005755C8") /*gvi*/
#pragma pop_macro("G6_005755C8")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("G6_00575A70")
#undef G6_00575A70
#pragma push_macro("G6_00575A70") /*gvi*/
#undef G6_00575A70 /*gvi*/
int32_t G6_00575A70;
#pragma pop_macro("G6_00575A70") /*gvi*/
#pragma pop_macro("G6_00575A70")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("G6_00575EBC")
#undef G6_00575EBC
#pragma push_macro("G6_00575EBC") /*gvi*/
#undef G6_00575EBC /*gvi*/
int32_t G6_00575EBC;
#pragma pop_macro("G6_00575EBC") /*gvi*/
#pragma pop_macro("G6_00575EBC")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("G6_00575EC0")
#undef G6_00575EC0
#pragma push_macro("G6_00575EC0") /*gvi*/
#undef G6_00575EC0 /*gvi*/
int32_t G6_00575EC0;
#pragma pop_macro("G6_00575EC0") /*gvi*/
#pragma pop_macro("G6_00575EC0")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("G6_00575EEC")
#undef G6_00575EEC
#pragma push_macro("G6_00575EEC") /*gvi*/
#undef G6_00575EEC /*gvi*/
int32_t G6_00575EEC;
#pragma pop_macro("G6_00575EEC") /*gvi*/
#pragma pop_macro("G6_00575EEC")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("G6_00575EF4")
#undef G6_00575EF4
#pragma push_macro("G6_00575EF4") /*gvi*/
#undef G6_00575EF4 /*gvi*/
int32_t G6_00575EF4;
#pragma pop_macro("G6_00575EF4") /*gvi*/
#pragma pop_macro("G6_00575EF4")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("G6_00575F00")
#undef G6_00575F00
#pragma push_macro("G6_00575F00") /*gvi*/
#undef G6_00575F00 /*gvi*/
int32_t G6_00575F00;
#pragma pop_macro("G6_00575F00") /*gvi*/
#pragma pop_macro("G6_00575F00")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("G6_00575F04")
#undef G6_00575F04
#pragma push_macro("G6_00575F04") /*gvi*/
#undef G6_00575F04 /*gvi*/
int32_t G6_00575F04;
#pragma pop_macro("G6_00575F04") /*gvi*/
#pragma pop_macro("G6_00575F04")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("G6_00575F20")
#undef G6_00575F20
#pragma push_macro("G6_00575F20") /*gvi*/
#undef G6_00575F20 /*gvi*/
int32_t G6_00575F20;
#pragma pop_macro("G6_00575F20") /*gvi*/
#pragma pop_macro("G6_00575F20")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("G6_00575F34")
#undef G6_00575F34
#pragma push_macro("G6_00575F34") /*gvi*/
#undef G6_00575F34 /*gvi*/
int32_t G6_00575F34;
#pragma pop_macro("G6_00575F34") /*gvi*/
#pragma pop_macro("G6_00575F34")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("G6_00575F38")
#undef G6_00575F38
#pragma push_macro("G6_00575F38") /*gvi*/
#undef G6_00575F38 /*gvi*/
int32_t G6_00575F38;
#pragma pop_macro("G6_00575F38") /*gvi*/
#pragma pop_macro("G6_00575F38")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("G6_0057B728")
#undef G6_0057B728
#pragma push_macro("G6_0057B728") /*gvi*/
#undef G6_0057B728 /*gvi*/
int32_t G6_0057B728;
#pragma pop_macro("G6_0057B728") /*gvi*/
#pragma pop_macro("G6_0057B728")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("G6_005D5788")
#undef G6_005D5788
#pragma push_macro("G6_005D5788") /*gvi*/
#undef G6_005D5788 /*gvi*/
int32_t G6_005D5788;
#pragma pop_macro("G6_005D5788") /*gvi*/
#pragma pop_macro("G6_005D5788")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("G6_005FE9BC")
#undef G6_005FE9BC
#pragma push_macro("G6_005FE9BC") /*gvi*/
#undef G6_005FE9BC /*gvi*/
int32_t G6_005FE9BC;
#pragma pop_macro("G6_005FE9BC") /*gvi*/
#pragma pop_macro("G6_005FE9BC")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("G6_005FE9CC")
#undef G6_005FE9CC
#pragma push_macro("G6_005FE9CC") /*gvi*/
#undef G6_005FE9CC /*gvi*/
int32_t G6_005FE9CC;
#pragma pop_macro("G6_005FE9CC") /*gvi*/
#pragma pop_macro("G6_005FE9CC")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("G6_005FEA7C")
#undef G6_005FEA7C
#pragma push_macro("G6_005FEA7C") /*gvi*/
#undef G6_005FEA7C /*gvi*/
int32_t G6_005FEA7C;
#pragma pop_macro("G6_005FEA7C") /*gvi*/
#pragma pop_macro("G6_005FEA7C")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("G6_005FED9C")
#undef G6_005FED9C
#pragma push_macro("G6_005FED9C") /*gvi*/
#undef G6_005FED9C /*gvi*/
int32_t G6_005FED9C;
#pragma pop_macro("G6_005FED9C") /*gvi*/
#pragma pop_macro("G6_005FED9C")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("G6_00A421F0")
#undef G6_00A421F0
#pragma push_macro("G6_00A421F0") /*gvi*/
#undef G6_00A421F0 /*gvi*/
int32_t G6_00A421F0;
#pragma pop_macro("G6_00A421F0") /*gvi*/
#pragma pop_macro("G6_00A421F0")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("G6_00B1C224")
#undef G6_00B1C224
#pragma push_macro("G6_00B1C224") /*gvi*/
#undef G6_00B1C224 /*gvi*/
int32_t G6_00B1C224;
#pragma pop_macro("G6_00B1C224") /*gvi*/
#pragma pop_macro("G6_00B1C224")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("G6_00B20364")
#undef G6_00B20364
#pragma push_macro("G6_00B20364") /*gvi*/
#undef G6_00B20364 /*gvi*/
int32_t G6_00B20364;
#pragma pop_macro("G6_00B20364") /*gvi*/
#pragma pop_macro("G6_00B20364")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("G6_00B20368")
#undef G6_00B20368
#pragma push_macro("G6_00B20368") /*gvi*/
#undef G6_00B20368 /*gvi*/
int32_t G6_00B20368;
#pragma pop_macro("G6_00B20368") /*gvi*/
#pragma pop_macro("G6_00B20368")
#endif
GAME_VAR_DEF(g6a_00B2F30C, G6_00B2F30C, 0x00b2f30c)
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("G6_00B31F40")
#undef G6_00B31F40
#pragma push_macro("G6_00B31F40") /*gvi*/
#undef G6_00B31F40 /*gvi*/
int32_t G6_00B31F40;
#pragma pop_macro("G6_00B31F40") /*gvi*/
#pragma pop_macro("G6_00B31F40")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("G6_00B5A778")
#undef G6_00B5A778
#pragma push_macro("G6_00B5A778") /*gvi*/
#undef G6_00B5A778 /*gvi*/
int32_t G6_00B5A778;
#pragma pop_macro("G6_00B5A778") /*gvi*/
#pragma pop_macro("G6_00B5A778")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("G6_00B5A838")
#undef G6_00B5A838
#pragma push_macro("G6_00B5A838") /*gvi*/
#undef G6_00B5A838 /*gvi*/
uint8_t G6_00B5A838;
#pragma pop_macro("G6_00B5A838") /*gvi*/
#pragma pop_macro("G6_00B5A838")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("G6_00B5A839")
#undef G6_00B5A839
#pragma push_macro("G6_00B5A839") /*gvi*/
#undef G6_00B5A839 /*gvi*/
uint8_t G6_00B5A839;
#pragma pop_macro("G6_00B5A839") /*gvi*/
#pragma pop_macro("G6_00B5A839")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("G6_00B5A83A")
#undef G6_00B5A83A
#pragma push_macro("G6_00B5A83A") /*gvi*/
#undef G6_00B5A83A /*gvi*/
uint8_t G6_00B5A83A;
#pragma pop_macro("G6_00B5A83A") /*gvi*/
#pragma pop_macro("G6_00B5A83A")
#endif
GAME_VAR_DEF(void*, G6_00B5A83C, 0x00b5a83c)
GAME_VAR_DEF(void*, G6_00B5A840, 0x00b5a840)
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("G6_00B5A8A0")
#undef G6_00B5A8A0
#pragma push_macro("G6_00B5A8A0") /*gvi*/
#undef G6_00B5A8A0 /*gvi*/
int32_t G6_00B5A8A0;
#pragma pop_macro("G6_00B5A8A0") /*gvi*/
#pragma pop_macro("G6_00B5A8A0")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("G6_00B5A8AC")
#undef G6_00B5A8AC
#pragma push_macro("G6_00B5A8AC") /*gvi*/
#undef G6_00B5A8AC /*gvi*/
int32_t G6_00B5A8AC;
#pragma pop_macro("G6_00B5A8AC") /*gvi*/
#pragma pop_macro("G6_00B5A8AC")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("G6_00B5A8B0")
#undef G6_00B5A8B0
#pragma push_macro("G6_00B5A8B0") /*gvi*/
#undef G6_00B5A8B0 /*gvi*/
int32_t G6_00B5A8B0;
#pragma pop_macro("G6_00B5A8B0") /*gvi*/
#pragma pop_macro("G6_00B5A8B0")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("G6_00B87E20")
#undef G6_00B87E20
#pragma push_macro("G6_00B87E20") /*gvi*/
#undef G6_00B87E20 /*gvi*/
int32_t G6_00B87E20;
#pragma pop_macro("G6_00B87E20") /*gvi*/
#pragma pop_macro("G6_00B87E20")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("G6_00B87E50")
#undef G6_00B87E50
#pragma push_macro("G6_00B87E50") /*gvi*/
#undef G6_00B87E50 /*gvi*/
int32_t G6_00B87E50;
#pragma pop_macro("G6_00B87E50") /*gvi*/
#pragma pop_macro("G6_00B87E50")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("G6_00B87E74")
#undef G6_00B87E74
#pragma push_macro("G6_00B87E74") /*gvi*/
#undef G6_00B87E74 /*gvi*/
int32_t G6_00B87E74;
#pragma pop_macro("G6_00B87E74") /*gvi*/
#pragma pop_macro("G6_00B87E74")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("G6_00B87EA0")
#undef G6_00B87EA0
#pragma push_macro("G6_00B87EA0") /*gvi*/
#undef G6_00B87EA0 /*gvi*/
int32_t G6_00B87EA0;
#pragma pop_macro("G6_00B87EA0") /*gvi*/
#pragma pop_macro("G6_00B87EA0")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("G6_00B87EAC")
#undef G6_00B87EAC
#pragma push_macro("G6_00B87EAC") /*gvi*/
#undef G6_00B87EAC /*gvi*/
int32_t G6_00B87EAC;
#pragma pop_macro("G6_00B87EAC") /*gvi*/
#pragma pop_macro("G6_00B87EAC")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("G6_00B87EB0")
#undef G6_00B87EB0
#pragma push_macro("G6_00B87EB0") /*gvi*/
#undef G6_00B87EB0 /*gvi*/
int32_t G6_00B87EB0;
#pragma pop_macro("G6_00B87EB0") /*gvi*/
#pragma pop_macro("G6_00B87EB0")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("G6_00B87EEC")
#undef G6_00B87EEC
#pragma push_macro("G6_00B87EEC") /*gvi*/
#undef G6_00B87EEC /*gvi*/
int32_t G6_00B87EEC;
#pragma pop_macro("G6_00B87EEC") /*gvi*/
#pragma pop_macro("G6_00B87EEC")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("G6_00B87EFC")
#undef G6_00B87EFC
#pragma push_macro("G6_00B87EFC") /*gvi*/
#undef G6_00B87EFC /*gvi*/
int32_t G6_00B87EFC;
#pragma pop_macro("G6_00B87EFC") /*gvi*/
#pragma pop_macro("G6_00B87EFC")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("G6_00B91BC4")
#undef G6_00B91BC4
#pragma push_macro("G6_00B91BC4") /*gvi*/
#undef G6_00B91BC4 /*gvi*/
g6a_00B91BC4 G6_00B91BC4;
#pragma pop_macro("G6_00B91BC4") /*gvi*/
#pragma pop_macro("G6_00B91BC4")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("G6_00B91CF4")
#undef G6_00B91CF4
#pragma push_macro("G6_00B91CF4") /*gvi*/
#undef G6_00B91CF4 /*gvi*/
int32_t G6_00B91CF4;
#pragma pop_macro("G6_00B91CF4") /*gvi*/
#pragma pop_macro("G6_00B91CF4")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("G6_00B91D2C")
#undef G6_00B91D2C
#pragma push_macro("G6_00B91D2C") /*gvi*/
#undef G6_00B91D2C /*gvi*/
int32_t G6_00B91D2C;
#pragma pop_macro("G6_00B91D2C") /*gvi*/
#pragma pop_macro("G6_00B91D2C")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("G6_00B91D34")
#undef G6_00B91D34
#pragma push_macro("G6_00B91D34") /*gvi*/
#undef G6_00B91D34 /*gvi*/
int32_t G6_00B91D34;
#pragma pop_macro("G6_00B91D34") /*gvi*/
#pragma pop_macro("G6_00B91D34")
#endif
GAME_VAR_DEF(FnV2, G6_00BDCB14, 0x00bdcb14)
GAME_VAR_DEF(FnV1, G6_00BDCB18, 0x00bdcb18)
GAME_VAR_DEF(FnV1, G6_00BDCB20, 0x00bdcb20)
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("G6_00BDF9C0")
#undef G6_00BDF9C0
#pragma push_macro("G6_00BDF9C0") /*gvi*/
#undef G6_00BDF9C0 /*gvi*/
int32_t G6_00BDF9C0;
#pragma pop_macro("G6_00BDF9C0") /*gvi*/
#pragma pop_macro("G6_00BDF9C0")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("G6_00BDF9C4")
#undef G6_00BDF9C4
#pragma push_macro("G6_00BDF9C4") /*gvi*/
#undef G6_00BDF9C4 /*gvi*/
int32_t G6_00BDF9C4;
#pragma pop_macro("G6_00BDF9C4") /*gvi*/
#pragma pop_macro("G6_00BDF9C4")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("G6_00C557F8")
#undef G6_00C557F8
#pragma push_macro("G6_00C557F8") /*gvi*/
#undef G6_00C557F8 /*gvi*/
int32_t G6_00C557F8;
#pragma pop_macro("G6_00C557F8") /*gvi*/
#pragma pop_macro("G6_00C557F8")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("G6_00C55800")
#undef G6_00C55800
#pragma push_macro("G6_00C55800") /*gvi*/
#undef G6_00C55800 /*gvi*/
int32_t G6_00C55800;
#pragma pop_macro("G6_00C55800") /*gvi*/
#pragma pop_macro("G6_00C55800")
#endif
GAME_VAR_DEF(void*, G6_00C80C50, 0x00c80c50)
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("G6_00C81108")
#undef G6_00C81108
#pragma push_macro("G6_00C81108") /*gvi*/
#undef G6_00C81108 /*gvi*/
int32_t G6_00C81108;
#pragma pop_macro("G6_00C81108") /*gvi*/
#pragma pop_macro("G6_00C81108")
#endif
GAME_VAR_DEF(void*, G6_00CE0F20, 0x00ce0f20)
GAME_VAR_DEF(void*, G6_00D00208, 0x00d00208)
GAME_VAR_DEF(void*, G6_00D01268, 0x00d01268)
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("G6_00D04A50")
#undef G6_00D04A50
#pragma push_macro("G6_00D04A50") /*gvi*/
#undef G6_00D04A50 /*gvi*/
g6a_00D04A50 G6_00D04A50;
#pragma pop_macro("G6_00D04A50") /*gvi*/
#pragma pop_macro("G6_00D04A50")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("G6_00D0DDC0")
#undef G6_00D0DDC0
#pragma push_macro("G6_00D0DDC0") /*gvi*/
#undef G6_00D0DDC0 /*gvi*/
int32_t G6_00D0DDC0;
#pragma pop_macro("G6_00D0DDC0") /*gvi*/
#pragma pop_macro("G6_00D0DDC0")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("G6_00D10E40")
#undef G6_00D10E40
#pragma push_macro("G6_00D10E40") /*gvi*/
#undef G6_00D10E40 /*gvi*/
uint32_t G6_00D10E40;
#pragma pop_macro("G6_00D10E40") /*gvi*/
#pragma pop_macro("G6_00D10E40")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("G6_00D117A4")
#undef G6_00D117A4
#pragma push_macro("G6_00D117A4") /*gvi*/
#undef G6_00D117A4 /*gvi*/
int32_t G6_00D117A4;
#pragma pop_macro("G6_00D117A4") /*gvi*/
#pragma pop_macro("G6_00D117A4")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("G6_00D117A8")
#undef G6_00D117A8
#pragma push_macro("G6_00D117A8") /*gvi*/
#undef G6_00D117A8 /*gvi*/
int32_t G6_00D117A8;
#pragma pop_macro("G6_00D117A8") /*gvi*/
#pragma pop_macro("G6_00D117A8")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("G6_00D11800")
#undef G6_00D11800
#pragma push_macro("G6_00D11800") /*gvi*/
#undef G6_00D11800 /*gvi*/
uint32_t G6_00D11800;
#pragma pop_macro("G6_00D11800") /*gvi*/
#pragma pop_macro("G6_00D11800")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("G6_00D11880")
#undef G6_00D11880
#pragma push_macro("G6_00D11880") /*gvi*/
#undef G6_00D11880 /*gvi*/
int32_t G6_00D11880;
#pragma pop_macro("G6_00D11880") /*gvi*/
#pragma pop_macro("G6_00D11880")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("G6_00D11928")
#undef G6_00D11928
#pragma push_macro("G6_00D11928") /*gvi*/
#undef G6_00D11928 /*gvi*/
int32_t G6_00D11928;
#pragma pop_macro("G6_00D11928") /*gvi*/
#pragma pop_macro("G6_00D11928")
#endif
#define SND_RATE_22K 0x5622   /* 22050 Hz */
#define SND_RATE_44K 0xac44   /* 44100 Hz */

/* ---- цвета строк меню (пары Select/Leave): байты RGB в таблице записей по 16 байт ---- */
/* rgb3 — Set the RGB bytes of row idx of a menu table (16-byte rows). */
static void rgb3(uint8_t *tab, int32_t idx, uint8_t r, uint8_t g, uint8_t b) {
    tab[idx * 0x10] = r; tab[idx * 0x10 + 1] = g; tab[idx * 0x10 + 2] = b;
}
/* hilite_pair — Colour rows a and b (b == -1: only a). */
static void hilite_pair(uint8_t *tab, int32_t a, int32_t b, uint8_t r, uint8_t g, uint8_t bl) {
    rgb3(tab, a, r, g, bl);
    if (b != -1) rgb3(tab, b, r, g, bl);
}
/* MenuRed0040766D — Game.exe 0040766d, cdecl.  Highlight (red) the selected row pair of menu 00549f84 unless nothing is selected (0057b728 == -1). */
void MenuRed0040766D(void) { if (G6_0057B728 != -1) hilite_pair(G6_00549F84, MenuI0057B730, MenuI0054A060, 0xff, 0, 0); }
/* MenuWhite004076E2 — Game.exe 004076e2, cdecl.  Reset the selected row pair of menu 00549f84 to white. */
void MenuWhite004076E2(void) { rgb3(G6_00549F84, MenuI0057B730, 0xff, 0xff, 0xff); if (MenuI0054A060 != -1) rgb3(G6_00549F84, MenuI0054A060, 0xff, 0xff, 0xff); }
/* MenuRed00409C85 — Game.exe 00409c85, cdecl.  Highlight the selected row pair of menu 0054a25c. */
void MenuRed00409C85(void) { if (G6_005D5788 != -1) hilite_pair(G6_0054A25C, MenuI005D578C, MenuI0054A694, 0xff, 0, 0); }
/* MenuWhite00409CFA — Game.exe 00409cfa, cdecl.  Reset the selected row pair of menu 0054a25c to white. */
void MenuWhite00409CFA(void) { hilite_pair(G6_0054A25C, MenuI005D578C, MenuI0054A694, 0xff, 0xff, 0xff); }
/* MenuRed00415904 — Game.exe 00415904, cdecl.  Highlight the selected row pair of menu 0054dbcc. */
void MenuRed00415904(void) { if (G6_005FE9CC != -1) hilite_pair(G6_0054DBCC, MenuI005FE9D0, MenuI0054DE08, 0xff, 0, 0); }
/* MenuWhite00415979 — Game.exe 00415979, cdecl.  Reset the selected row pair of menu 0054dbcc to white. */
void MenuWhite00415979(void) { hilite_pair(G6_0054DBCC, MenuI005FE9D0, MenuI0054DE08, 0xff, 0xff, 0xff); }
/* MenuRed00419D3E — Game.exe 00419d3e, cdecl.  Highlight the selected row pair of menu 0054e56c. */
void MenuRed00419D3E(void) { if (G6_005FEA7C != -1) hilite_pair(G6_0054E56C, UiVar005FEA80, UiVar0054E654, 0xff, 0, 0); }
/* MenuWhite00419DB3 — Game.exe 00419db3, cdecl.  Reset the selected row pair of menu 0054e56c to white. */
void MenuWhite00419DB3(void) { hilite_pair(G6_0054E56C, UiVar005FEA80, UiVar0054E654, 0xff, 0xff, 0xff); }
/* MenuWhite0041AF29 — Game.exe 0041af29, cdecl.  Rows i and i + 1 of menu 0054e834 to white. */
void MenuWhite0041AF29(int32_t i) { rgb3(G6_0054E834, i, 0xff, 0xff, 0xff); rgb3(G6_0054E834, i + 1, 0xff, 0xff, 0xff); }
/* MenuMark00412228 — Game.exe 00412228, cdecl.  Set the flag byte 3 on the two rows of entry 005fe84c of menu 0054c6d4. */
void MenuMark00412228(void) { WB0054C6D4[(UiVar005FE84C * 2 + 3) * 0x10] = 3; WB0054C6D4[(UiVar005FE84C * 2 + 4) * 0x10] = 3; }

/* ---- переключатели «вкл/альт» и циклы ---- */
/* dual_toggle — Cycle an option pair off -> on -> on+alt -> off. */
static void dual_toggle(int32_t *on, int32_t *alt) {
    if (*on == 0) { *on = 1; *alt = 0; }
    else { if (*alt != 0) *on = 0; *alt = (*alt == 0); }
}
/* tri_state — Cycle option 00575f34/00575f38/00575eec: off -> on level 1..5 -> alt -> off. */
static void tri_state(void) {
    if (G6_00575F34 == 0) { G6_00575F34 = 1; G6_00575F38 = 0; G6_00575EEC = 1; }
    else if (G6_00575F38 == 1) { G6_00575F38 = 0; G6_00575F34 = 0; }
    else if (G6_00575EEC == 5) { G6_00575F38 = 1; }
    else { G6_00575EEC = G6_00575EEC + 1; }
}
/* MenuToggle00408994 — Game.exe 00408994, cdecl.  Toggle detail option "Shadows" (Detail menu entry 1) 00d11880/00575f20, set the detail preset index to 4 (custom, inferred) and redraw. */
int32_t MenuToggle00408994(void) { dual_toggle(&G6_00D11880, &G6_00575F20); G00575EF8 = 4; MenuRedraw(); return 0; }
/* MenuToggle00408C37 — Game.exe 00408c37, cdecl.  Toggle detail option "Tyre Tracks" (entry 9) 00575ec0/00575ebc, preset index 4 (custom, inferred), redraw. */
int32_t MenuToggle00408C37(void) { dual_toggle(&G6_00575EC0, &G6_00575EBC); G00575EF8 = 4; MenuRedraw(); return 0; }
/* MenuToggle00409142 — Game.exe 00409142, cdecl.  Toggle detail option "Real Time Lights" (entry 10) 00575ef4/00b87e74, preset index 4 (custom, inferred), redraw.  Labels from the Detail menu 0054a470 text order (RE_PROBE walk; inferred). */
int32_t MenuToggle00409142(void) { dual_toggle(&G6_00575EF4, &G6_00B87E74); G00575EF8 = 4; MenuRedraw(); return 0; }
/* MenuToggle0050FE26 — Game.exe 0050fe26, cdecl.  In-game variant of MenuToggle00408994 (redraws via 0050fbf4). */
int32_t MenuToggle0050FE26(void) { dual_toggle(&G6_00D11880, &G6_00575F20); G00575EF8 = 4; Call0050FBF4(); return 0; }
/* MenuToggle0050FEE5 — Game.exe 0050fee5, cdecl.  In-game variant of MenuToggle00408C37. */
int32_t MenuToggle0050FEE5(void) { dual_toggle(&G6_00575EC0, &G6_00575EBC); G00575EF8 = 4; Call0050FBF4(); return 0; }
/* MenuToggle00510028 — Game.exe 00510028, cdecl.  In-game variant of MenuToggle00409142. */
int32_t MenuToggle00510028(void) { dual_toggle(&G6_00575EF4, &G6_00B87E74); G00575EF8 = 4; Call0050FBF4(); return 0; }
/* MenuTri0040E9B5 — Game.exe 0040e9b5, cdecl.  tri_state option = "Max frame rate" (Gameplay menu 0054ad60 entry 2, RE_PROBE walk), redraw 0040ea70. */
int32_t MenuTri0040E9B5(void) { tri_state(); Call0040EA70(); return 0; }
/* MenuTri00419C8C — Game.exe 00419c8c, cdecl.  tri_state option, redraw 00419b35. */
int32_t MenuTri00419C8C(void) { tri_state(); Call00419B35(); return 0; }
/* MenuQuality004088DB — Game.exe 004088db, cdecl.  Cycle the detail preset 00575ef8 through 0..3, apply it (P13_Fn004064B4 with limits) and redraw. */
int32_t MenuQuality004088DB(void) {
    G00575EF8 = G00575EF8 + 1; if (3 < G00575EF8) G00575EF8 = 0;
    G6Call004064B4(G00575EF8, 0); G6Call004094E3(); MenuRedraw(); return 0;
}
/* MenuQuality0050FA70 — Game.exe 0050fa70, cdecl.  In-game variant: cycle and apply the preset keeping the count limits. */
int32_t MenuQuality0050FA70(void) {
    G00575EF8 = G00575EF8 + 1; if (3 < G00575EF8) G00575EF8 = 0;
    G6Call004064B4(G00575EF8, 1); G6Call0050FAB0(); Call0050FBF4(); return 0;
}

/* ---- звуковые параметры (через указатели на функции драйвера звука) ---- */
/* SoundSetFormat005235D3 — Game.exe 005235d3, cdecl.  Sound driver: set output format (bits a, rate b) when sound is initialised. */
void SoundSetFormat005235D3(int32_t a, int32_t b) { if (G6_00B91CF4 != 0) G6_00BDCB14(a, b); }
/* SoundSetVolA005235F2 — Game.exe 005235f2, cdecl.  Sound driver call 00bdcb18(a) when sound is initialised.  TODO(RE): unsure (channel count/volume). */
void SoundSetVolA005235F2(int32_t a) { if (G6_00B91CF4 != 0) G6_00BDCB18(a); }
/* SoundSetVolB0052360D — Game.exe 0052360d, cdecl.  Sound driver call 00bdcb20(a) when sound is initialised.  TODO(RE): unsure. */
void SoundSetVolB0052360D(int32_t a) { if (G6_00B91CF4 != 0) G6_00BDCB20(a); }
/* MenuBits0041556C — Game.exe 0041556c, cdecl.  Toggle 8/16-bit sound output and apply it. */
int32_t MenuBits0041556C(void) {
    G6_00575F00 = (G6_00575F00 == 8) ? 0x10 : 8;
    SoundSetFormat005235D3(G6_00575F00, G6_00575F04); Call00414D1F(); return 0;
}
/* MenuRate00415623 — Game.exe 00415623, cdecl.  Toggle the 22050/44100 Hz sound output rate and apply it. */
int32_t MenuRate00415623(void) {
    G6_00575F04 = (G6_00575F04 == SND_RATE_22K) ? SND_RATE_44K : SND_RATE_22K;
    SoundSetFormat005235D3(G6_00575F00, G6_00575F04); Call00414D1F(); return 0;
}
/* MenuSoundCh004156DD — Game.exe 004156dd, cdecl.  Cycle 00b87e50 through 0..4 and pass it to the driver (SoundSetVolA). */
int32_t MenuSoundCh004156DD(void) {
    G6_00B87E50 = G6_00B87E50 + 1; if (G6_00B87E50 == 5) G6_00B87E50 = 0;
    SoundSetVolA005235F2(G6_00B87E50); Call00414D1F(); return 0;
}
/* MenuBits0050F8F2 — Game.exe 0050f8f2, cdecl.  In-game variant of MenuBits0041556C. */
void MenuBits0050F8F2(void) {
    G6_00575F00 = (G6_00575F00 == 8) ? 0x10 : 8;
    SoundSetFormat005235D3(G6_00575F00, G6_00575F04); Call0050F7B2();
}
/* MenuRate0050F930 — Game.exe 0050f930, cdecl.  In-game variant of MenuRate00415623. */
void MenuRate0050F930(void) {
    G6_00575F04 = (G6_00575F04 == SND_RATE_22K) ? SND_RATE_44K : SND_RATE_22K;
    SoundSetFormat005235D3(G6_00575F00, G6_00575F04); Call0050F7B2();
}
/* MenuSoundCh0050F971 — Game.exe 0050f971, cdecl.  In-game variant of MenuSoundCh004156DD. */
void MenuSoundCh0050F971(void) {
    G6_00B87E50 = G6_00B87E50 + 1; if (G6_00B87E50 == 5) G6_00B87E50 = 0;
    SoundSetVolA005235F2(G6_00B87E50); Call0050F7B2();
}
/* MenuSound0050F781 — Game.exe 0050f781, cdecl.  Toggle sound effects (00575f40): stop all, or restart and reload. */
void MenuSound0050F781(void) {
    G00575F40 = G00575F40 ^ 1;
    if (G00575F40 == 0) G6Call004D5FFC(); else { G6Call004D5CE0(); G6Call00524398(); }
    Call0050F7B2();
}
/* MenuMusic0050F8A2 — Game.exe 0050f8a2, cdecl.  Toggle CD music (00b87e90); turning it off stops the CD. */
void MenuMusic0050F8A2(void) {
    Q00B87E90 = Q00B87E90 ^ 1;
    if (Q00B87E90 == 0) { Call00524873(); Call00524763(); }
    Call0050F7B2();
}
/* MenuMusic0050F8CC — Game.exe 0050f8cc, cdecl.  Toggle 00b87e94 and pass it to 0052369b.  00b87e94 = "Doppler Effect" option (Sound menu entry 5 calls ToggleOpt004154CD on the same word). */
void MenuMusic0050F8CC(void) { Q00B87E94 = Q00B87E94 ^ 1; Call0052369B(Q00B87E94); Call0050F7B2(); }

/* ---- запись состояния кнопок меню: байт состояния в записи, смещение зависит от режима ---- */
/* btn_state — Mark a button record byte of 005fe9b8 as 2 when p == 0; the offset depends on mode 005fe9bc (1: off1, 0/2: off2). */
static void btn_state(int32_t p, int off1, int off2) {
    if (p != 0) return;
    if (G6_005FE9BC != 0) {
        if (G6_005FE9BC == 1) { UiPtr005FE9B8[off1] = 2; return; }
        if (G6_005FE9BC != 2) return;
    }
    UiPtr005FE9B8[off2] = 2;
}
/* MenuBtn00414264 — Game.exe 00414264, cdecl.  btn_state for button 1. */
void MenuBtn00414264(int32_t p) { btn_state(p, 0x14, 0x14); }
/* MenuBtn00414376 — Game.exe 00414376, cdecl.  btn_state for button 2. */
void MenuBtn00414376(int32_t p) { btn_state(p, 0x34, 0x24); }
/* MenuBtn00414488 — Game.exe 00414488, cdecl.  btn_state for button 3. */
void MenuBtn00414488(int32_t p) { btn_state(p, 0x54, 0x34); }
/* MenuBtn0041459A — Game.exe 0041459a, cdecl.  btn_state for button 4. */
void MenuBtn0041459A(int32_t p) { btn_state(p, 0x74, 0x44); }

/* ---- затухание и листание ---- */
/* SetFade0051707A — Game.exe 0051707a, cdecl.  Start a fade to colour (r, g, b) over d ticks. */
void SetFade0051707A(uint8_t r, uint8_t g, uint8_t b, int32_t d) {
    G6_00B5A838 = r; G6_00B5A839 = g; G6_00B5A83A = b; G6_00C557F8 = d; G6_00C55800 = 0;
}
/* MenuPageNext00417F59 — Game.exe 00417f59, cdecl.  Next of 5 pages (wrapping) with a fade to black. */
void MenuPageNext00417F59(void) {
    SetFade0051707A(0, 0, 0, 0x32); G6_005FED9C = G6_005FED9C + 1; if (4 < G6_005FED9C) G6_005FED9C = 0;
    G6Call00418119(G6_005FED9C); G6Call00417CBB(); G005FEA54 = 1;
}
/* MenuPagePrev00417FAC — Game.exe 00417fac, cdecl.  Previous of 5 pages (wrapping) with a fade to black. */
void MenuPagePrev00417FAC(void) {
    SetFade0051707A(0, 0, 0, 0x32); G6_005FED9C = G6_005FED9C - 1; if (G6_005FED9C < 0) G6_005FED9C = 4;
    G6Call00418119(G6_005FED9C); G6Call00417CBB(); G005FEA54 = 1;
}

/* ---- пулы индексов ---- */
/* PoolAlloc004A2C12 — Game.exe 004a2c12, cdecl.  Take an index from the free list 01134ec0 (100 entries) and mark it used; -1 if empty. */
int32_t PoolAlloc004A2C12(void) {
    int32_t i;
    if (D_01134528 < 100) { i = D_01134ec0[D_01134528]; D_01134528 = D_01134528 + 1; D_01134554[i * 6] = 1; }
    else i = -1;
    return i;
}
/* PoolNext004AC671 — Game.exe 004ac671, cdecl.  Next index of list 010faf40 (200 entries) when 00553850 is enabled; -1 otherwise. */
int32_t PoolNext004AC671(void) {
    int32_t i;
    if (G00553850 == 0 || 199 < S_011173C8) i = -1;
    else { i = (int32_t)S_010FAF40[S_011173C8]; S_011173C8 = S_011173C8 + 1; }
    return i;
}
/* PoolAlloc0051210C — Game.exe 0051210c, cdecl.  Take one of the 64 object slots (00c594a0 free list; 0xb4-byte records at 00c56780) and initialise it; -1 if none. */
int32_t PoolAlloc0051210C(void) {
    int32_t i;
    if (G6_00C56764 < 0x40) { i = G6_00C594A0[G6_00C56764]; G6_00C56764 = G6_00C56764 + 1; G6_00C5678C[i * 0x2d] = 0x10; G6_00C5678C[i * 0x2d + 8] = 0; G6_00C5678C[i * 0x2d + 0x12] = 0; }
    else i = -1;
    return i;
}

/* ---- обёртки с вызовами ---- */
/* ShutdownAudio004183A3 — Game.exe 004183a3, cdecl.  Leave the game screen: stop CD, sound and the level (P137_LevelEnd), clear the flat-map and menu-input flags. */
void ShutdownAudio004183A3(void) {
    if (Q00B87E90 != 0) { Call00524873(); Call00524763(); }
    G6Call00523628(); G6Call0041A16C(); P137_LevelEnd();
    G6_00B87EEC = 0; G6_00B87EFC = 0; G6Call0040C5BE(4);
}
/* MenuBack005103EC — Game.exe 005103ec, cdecl.  Pause menu "quit": level end code 2 (back to the front end) and stop the game loop. */
void MenuBack005103EC(void) { G005F7E54 = 2; G6_00B87E20 = 0; G6Call0050E940(0); }
/* v2.10: ячейка 01270e80 (grDepthBufferMode, метка 0041e3b0 — нет в k_fns) в native = NULL, как в остальных местах — проверка;
   без неё Esc (пауза-меню, P116_PauseMenu → 0051080e) падал переходом по нулевому адресу */
/* SoundMenuIn00419814 — Game.exe 00419814, cdecl.  Before drawing a menu: depth buffer mode 2, render mode 0054e540, depth function 3 (native: NULL Glide cells skipped). */
void SoundMenuIn00419814(void) { if (FnPtr01270E80) FnPtr01270E80(2); Call0042655A(G0054E540); if (G6_01270DE4) G6_01270DE4(3); }
/* SoundMenuOut0051082A — Game.exe 0051082a, cdecl.  Restore the render mode saved by SoundMenuSave0051080E. */
void SoundMenuOut0051082A(void) { if (FnPtr01270E80) FnPtr01270E80(2); Call0042655A(G6_005755C8); if (G6_01270DE4) G6_01270DE4(3); }
/* SoundMenuSave0051080E — Game.exe 0051080e, cdecl.  Save the current render mode and disable depth buffering. */
void SoundMenuSave0051080E(void) { G6_005755C8 = Call0042655A(0); if (FnPtr01270E80) FnPtr01270E80(0); }
/* DrvCall004246D1 — Game.exe 004246d1, cdecl.  Glide cell 01270d20(a) when 00b1c0d4 is set, else 1. */
int32_t DrvCall004246D1(int32_t a) { return G00B1C0D4 == 0 ? 1 : G6_01270D20(a); }
/* DrvSetMode0042655A — Game.exe 0042655a, cdecl.  Set render mode a through Glide cell 01270d28; returns the previous mode. */
int32_t DrvSetMode0042655A(int32_t a) { int32_t old = G6_00B1C224; G6_00B1C224 = a; G6_01270D28(a); return old; }
/* StartAudio005233A0 — Game.exe 005233a0, cdecl.  Enumerate sound drivers once if sound is not running and none were found yet. */
void StartAudio005233A0(void) { if (G6_00B91CF4 == 0 && G6_00B91D2C == 0) P148_SndEnum(); }
/* NoopFn00528455 — Game.exe 00528455, cdecl.  finit; fldcw 0057a0e2 — back to the round-to-nearest x87 control word at
   shutdown (004264a7).  The name is kept (fn_table/install.c); v2.34: it was empty, see fpucw.h. */
void NoopFn00528455(void) {
#if defined(RE_HOOK_BUILD) && (defined(__i386__) || defined(__x86_64__))
  __asm__ volatile("fninit\n\tfldcw %0" : : "m"(G8_0057A0E2_u16));
#endif
  re_fpu_load_cw(0);
}
/* InitSubsys004BA443 — Game.exe 004ba443, cdecl.  Run three initialisers (004ba457, 004ba57a, 004ba64d). */
void InitSubsys004BA443(void) { G6Call004BA457(); G6Call004BA57A(); G6Call004BA64D(); }
/* Fwd004D2D9F — Game.exe 004d2d9f, cdecl.  004d614a(a, b, c, d) when 00575f08 is set. */
void Fwd004D2D9F(int32_t a, int32_t b, int32_t c, int32_t d) { if (G00575F08 != 0) G6Call004D614A(a, b, c, d); }
/* Reset004D600B — Game.exe 004d600b, cdecl.  Stop sound and clear the track queue counters 00b20368/00b20364. */
void Reset004D600B(void) { G6Call004D5FFC(); G6Call00523628(); G6_00B20368 = 0; G6_00B20364 = 0; }
/* 004dc8b0 — despite the historical name this is not a menu function: it appends a car record to the
   active physics list G6_00B2F30C[G6_00D0DDC0++] (walked by P142_CarsStep) and sets item[3] = flag != 0.
   The name is kept because hook/native tables refer to it. */
void MenuAddItem004DC8B0(uint8_t *item, int32_t flag) {
    item[3] = (flag == 0) ? 0 : 1; G6_00B2F30C[G6_00D0DDC0] = item; G6_00D0DDC0 = G6_00D0DDC0 + 1;
}
/* StepToward004E60C1 — Game.exe 004e60c1, cdecl.  Raise byte i of 00d04a50 by 0x13 towards its target 00562b70[i]; 1 while still rising. */
int32_t StepToward004E60C1(int32_t i) {
    if (G6_00D04A50[i] < G6_00562B70[i]) {
        G6_00D04A50[i] = (uint8_t)(G6_00D04A50[i] + 0x13);
        if (G6_00562B70[i] < G6_00D04A50[i]) G6_00D04A50[i] = G6_00562B70[i];
        return 1;
    }
    return 0;
}
/* AngleToDir00514103 — Game.exe 00514103, cdecl.  Heading (4096/turn) -> direction bit of its 90-degree sector centred on 0 / 90 / 180 / 270 deg: 4 / 2 / 8 / 1. */
uint32_t AngleToDir00514103(uint32_t a) {
    a &= 0xfff;
    if (a < 0x200) return 4;
    if (a < 0x600) return 2;
    if (a < 0xa00) return 8;
    if (a < 0xe00) return 1;
    if (a < 0x1000) return 4;
    return 0;
}
/* ObjInit00514C43 — Game.exe 00514c43, cdecl.  Object state o: +4 = a, +0x24 = b, +0x40 = 0, +0xc = flags | 0x400. */
void ObjInit00514C43(uint8_t *o, uint16_t a, uint32_t b, uint32_t flags) {
    uint32_t z = 0, f = flags | 0x400;
    memcpy(o + 4, &a, 2); memcpy(o + 0x24, &b, 4); memcpy(o + 0x40, &z, 4); memcpy(o + 0xc, &f, 4);
}
/* TypeIsKnown00514F0A — Game.exe 00514f0a, cdecl.  1 if *p is 1, 2 or 3, else -1. */
int32_t TypeIsKnown00514F0A(const int16_t *p) { return (*p == 1 || *p == 2 || *p == 3) ? 1 : -1; }

/* ---- векторы (x,y,z, w = индекс 4 в float-массиве игры) ---- */
/* VecAdd3_00526F7E — Game.exe 00526f7e, cdecl.  a += b (3 components). */
void VecAdd3_00526F7E(float *a, const float *b) { a[0] += b[0]; a[1] += b[1]; a[2] += b[2]; }
/* VecNeg4_00527123 — Game.exe 00527123, cdecl.  a = -a (components 0, 1, 2, 4). */
void VecNeg4_00527123(float *a) { a[4] = -a[4]; a[0] = -a[0]; a[1] = -a[1]; a[2] = -a[2]; }
/* VecAdd4_0052715E — Game.exe 0052715e, cdecl.  r = a + b (components 0, 1, 2, 4). */
void VecAdd4_0052715E(const float *a, const float *b, float *r) { r[4] = a[4] + b[4]; r[0] = a[0] + b[0]; r[1] = a[1] + b[1]; r[2] = a[2] + b[2]; }
/* VecSub4_005271A8 — Game.exe 005271a8, cdecl.  r = a - b (components 0, 1, 2, 4). */
void VecSub4_005271A8(const float *a, const float *b, float *r) { r[4] = a[4] - b[4]; r[0] = a[0] - b[0]; r[1] = a[1] - b[1]; r[2] = a[2] - b[2]; }
/* MatIdentity3_0052614F — Game.exe 0052614f, cdecl.  3x3 identity. */
void MatIdentity3_0052614F(float *m) { for (int i = 0; i < 9; i++) m[i] = (i % 4 == 0) ? 1.0f : 0.0f; }

/* ---- титры, звук, буферы ---- */
/* CreditsTick005193D4 — Game.exe 005193d4, cdecl.  Credits: advance to the next page every 0x1c2 ticks. */
void CreditsTick005193D4(void) {
    if (G6_00B5A8AC == 0) { G6_00B5A8AC = 0x1c2; G6_00575A70 = G6_00575A70 + 1; }
    G6_00B5A8AC = G6_00B5A8AC - 1;
}
/* CreditsNext00519D2C — Game.exe 00519d2c, cdecl.  Credits: show the next page if there is one; returns 1 if it moved. */
int32_t CreditsNext00519D2C(void) {
    int32_t r = G6_00575A70 < G6_00B5A8B0 - 1;
    if (r) { G6Call00519D22(G6_00575A70 + 1); G6_005624A0 = 0xf; G6_00D11928 = 0xb4; }
    return r;
}
/* CreditsPrev00519D70 — Game.exe 00519d70, cdecl.  Credits: restart the current page (early in it) or go back one; returns 1. */
int32_t CreditsPrev00519D70(void) {
    if (G6_00575A70 == 0) { G6_00B5A8A0 = 0; G6Call00519D22(0); }
    else if (G6_00B5A8AC < 0x1b4) G6Call00519D22(G6_00575A70);
    else G6Call00519D22(G6_00575A70 - 1);
    G6_005624A0 = 0xf; G6_00D11928 = 0xb4; return 1;
}
/* ResetPalette00519DF3 — Game.exe 00519df3, cdecl.  Draw element 0x18, colour white, invalidate 01270c34. */
void ResetPalette00519DF3(void) { G6Call00426580(0x18); G6Call00516EB4(0xff, 0xff, 0xff); G6_01270C34 = -1; }
/* MenuClick004F8ACC — Game.exe 004f8acc, cdecl.  Play menu click sound a alternating between voices 0xd and 0xe. */
void MenuClick004F8ACC(int32_t a) {
    if (G6_00B31F40 == 0) UiCall00523E50(a, 0xd, -1); else UiCall00523E50(a, 0xe, -1);
    G6_00B31F40 = ~G6_00B31F40;
}
/* DrawTextLine004FBBC5 — Game.exe 004fbbc5, cdecl.  Draw text t centred on screen (320, 240) in white unless paused. */
void DrawTextLine004FBBC5(int32_t t) { if (G6_00B5A778 == 0) DrawSprite(0x140, 0xf0, (uint32_t)t, 0, 1, 0xff, 0xff, 0xff); }
/* FreeBuf004FC57B — Game.exe 004fc57b, cdecl.  Free the buffer 00c80c50 and clear its size 00c81108. */
void FreeBuf004FC57B(void) { if (G6_00C80C50 != 0) DebugFree(G6_00C80C50); G6_00C80C50 = 0; G6_00C81108 = 0; }
/* FreeMapBufs004ECE1A — Game.exe 004ece1a, cdecl.  Free the map buffers 00d01268, 00d00208, 00ce0f20. */
void FreeMapBufs004ECE1A(void) {
    if (G6_00D01268 != 0) { DebugFree(G6_00D01268); G6_00D01268 = 0; }
    if (G6_00D00208 != 0) { DebugFree(G6_00D00208); G6_00D00208 = 0; }
    if (G6_00CE0F20 != 0) { DebugFree(G6_00CE0F20); G6_00CE0F20 = 0; }
}
/* FreeBufs00516E2E — Game.exe 00516e2e, cdecl.  Free the buffers 00b5a840 and 00b5a83c. */
void FreeBufs00516E2E(void) {
    if (G6_00B5A840 != 0) { DebugFree(G6_00B5A840); G6_00B5A840 = 0; }
    if (G6_00B5A83C != 0) { DebugFree(G6_00B5A83C); G6_00B5A83C = 0; }
}
/* Update005012A3 — Game.exe 005012a3, cdecl.  Per-frame car objects for the player (and the chase target 0x41 in chase modes), then 00491360 outside training. */
void Update005012A3(void) {
    P129_CarObjects(0);
    if (G6_00B87EAC != 0 || G6_00B87EB0 != 0) P129_CarObjects(0x41);
    if (G6_00B87EA0 == 0) G6Call00491360();
}
/* ActorStep00494678 — Game.exe 00494678, cdecl.  Traffic state TRF_ACTOR: while the countdown p[0xb] runs, steer the car hard (CAR_STEER = 0x23f); then switch the record to TRF_DRIVE with sub-state 1. */
void ActorStep00494678(uint8_t *p) {
    if (p[0xb] == 0) { p[1] = 2; p[2] = 1; }
    else {
        uint32_t v = 0x23f;
        memcpy(G0113A6C4 + (uint32_t)p[0] * 0x148 + CAR_STEER, &v, 4);   /* car record of this traffic slot */
        p[0xb] = (uint8_t)(p[0xb] - 1);
    }
}
/* StartFlyby004A05C0 — Game.exe 004a05c0, cdecl.  In menu mode 7 start the fly-by camera and return 0; else -1. */
int32_t StartFlyby004A05C0(void) {
    G6_01136920 = 0;
    if (G01271060 == 7) { G6_01136920 = 1; G6_011368C4 = 0; G6Call004A05FA(); return 0; }
    return -1;
}
/* Dispatch0048A68E — Game.exe 0048a68e, cdecl.  Upload texture slot i (single or pair, by flag 4 of 01145a60). */
void Dispatch0048A68E(int32_t i) {
    if ((P12_01145a60[i * 0x10] & 4) == 0) P40_UploadSlot(i, 0); else P40_UploadSlotPair(i, 0, 0);
}
/* Dispatch0041D50E — Game.exe 0041d50e, cdecl.  Flush batches, set palette d, and (without 8-bit emulation) call 0041f57d(a, b, c). */
void Dispatch0041D50E(int32_t a, int32_t b, int32_t c, int32_t d) {
    G6Call00422AE7(); G6_0054EF2C = d; if (G6_00A421F0 == 0) G6Call0041F57D(a, b, c);
}
/* Fwd0042482B — Game.exe 0042482b, cdecl.  0041d63b(a, b, c, d) when 00b1c0d8 == 1, else 1. */
int32_t Fwd0042482B(int32_t a, int32_t b, int32_t c, int32_t d) {
    return G00B1C0D8 == 1 ? G6Call0041D63B(a, b, c, d) : 1;
}
/* SoundGetPos005242A7 — Game.exe 005242a7, cdecl.  Position/parameter word (+0x28) of sound channel i, 0 if idle or sound off. */
int32_t SoundGetPos005242A7(int32_t i) {
    uint32_t v;
    if (G6_00B91CF4 == 0 || G00575F40 == 0) return 0;
    if ((S_00BDC2A0[i * 0x34] & 1) == 0) return 0;
    memcpy(&v, &S_00BDC2A0[i * 0x34 + 0x28], 4); return (int32_t)v;
}
/* SoundSetPos00523F8A — Game.exe 00523f8a, cdecl.  Set channel i's word +0x28 to v (-1 = its default at +0x24) and flag it for update (4). */
void SoundSetPos00523F8A(int32_t i, int32_t v) {
    if (G6_00B91CF4 != 0 && G00575F40 != 0 && (S_00BDC2A0[i * 0x34] & 0x11) != 0) {
        if (v == -1) memcpy(&v, &S_00BDC2A0[i * 0x34 + 0x24], 4);
        memcpy(&S_00BDC2A0[i * 0x34 + 0x28], &v, 4);
        S_00BDC2A0[i * 0x34] |= 4;
    }
}
/* SoundPlay00523E50 — Game.exe 00523e50, cdecl.  Play sample id on voice b with parameter c.  Ids above 0xfff are bank-relative: low byte + first
   sample of bank id >> 12 (see P77_LoadBank).  Native: RE_IVDBG logs bank plays. */
void SoundPlay00523E50(uint32_t id, int32_t b, int32_t c) {
    int32_t h;
    if (G6_00B91CF4 != 0 && G00575F40 != 0) {
        uint32_t id0 = id; (void)id0;
        if (0xfff < (int32_t)id) id = (id & 0xff) + (uint32_t)G6_00B91BC4[(int32_t)id >> 12];
        h = -2;
        if ((int32_t)id < G6_00B91D34 && (h = G6Call00523CDA(id, b, 0, 0, 0)) != -1) SoundSetPos00523F8A(h, c);
#ifndef RE_HOOK_BUILD
        { static int dbg = -1; if (dbg < 0) dbg = getenv("RE_IVDBG") != NULL;
          if (dbg && id0 > 0xfff) fprintf(stderr, "[iv] play %04x -> sample %d (of %d) voice %d h %d\n", (unsigned)id0, (int)id, (int)G6_00B91D34, (int)b, (int)h); }
#endif
    }
}
/* Mask004D9028 — Game.exe 004d9028, cdecl.  Seed the random generators (Rand_004D9078): LCG state a | 1, xorshift state (b & 0x7ff) | 1 (0 stays 0). */
void Mask004D9028(uint32_t a, uint32_t b) {
    G6_00D10E40 = a == 0 ? 0 : (a | 1);
    G6_00D11800 = b == 0 ? 0 : ((b & 0x7ff) | 1);
}
/* CursorWrap004D9478 — Game.exe 004d9478, cdecl.  Text cursor: next line (8-pixel rows), wrapping at the screen bottom. */
void CursorWrap004D9478(void) {
    G6_00D117A4 = 0; G6_00D117A8 = G6_00D117A8 + 1;
    if ((G6_0125F3F0 - 8) / 8 < G6_00D117A8) G6_00D117A8 = 0;
}
/* CursorSet004D94B7 — Game.exe 004d94b7, cdecl.  Text cursor to column a, row b in 8-pixel cells; negative current values count from the right/bottom. */
void CursorSet004D94B7(int32_t a, int32_t b) {
    if (G6_00D117A4 < 0) G6_00D117A4 = G6_01270C28 / 8 - a; else G6_00D117A4 = a;
    if (G6_00D117A8 < 0) G6_00D117A8 = G6_0125F3F0 / 8 - b; else G6_00D117A8 = b;
}
