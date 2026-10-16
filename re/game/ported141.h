#pragma once
#include <stdint.h>
#include "gvar.h"
/* v1.86: ported141 — строка MLADDER (0041b8ac), экран рекордов (0040f3de). Все cdecl.
   .data экрана рекордов 0054bd10..0054bee0 в native — только P141_HsMenu (game/p141_data.h, tools/gen_p141_data.py;
   MenuByte54BE5C/7C — макросы над ней), строки 0054bf1c..0054bf90 — P141_HsStr; обе в k_regions. */
typedef uint8_t p141_hsmenu_t[0x1d0];
typedef uint8_t p141_hsstr_t[0x74];
#define P141_HsMenu   GAME_VAR(p141_hsmenu_t, P141_HsMenu, 0x0054bd10)   /* таблица экрана рекордов, записи 0x10 */
#define P141_HsStr    GAME_VAR(p141_hsstr_t, P141_HsStr, 0x0054bf1c)     /* «1:».. «5:», «/», форматы, «-» */
#define P141_HSM8(a)  (P141_HsMenu[(a) - 0x0054bd10u])                   /* байт таблицы по адресу Game.exe */
#define P141_LadI     GAME_VAR(int32_t, P141_LadI, 0x0060038c)           /* счётчик цикла 0041b8ac */
#define P141_LadDepth GAME_VAR(int32_t, P141_LadDepth, 0x0060039c)       /* глубина ROOM/IF */
#define P141_LadRooms GAME_VAR(int32_t, P141_LadRooms, 0x006003a0)       /* открытые ROOM */
#define P141_LadVal   GAME_VAR(int32_t, P141_LadVal, 0x00600368)         /* последний номер MISSION/JOKE/CARSELECT */
#ifndef RE_HOOK_BUILD
#pragma push_macro("P141_HsMenu") /*gvi*/
#undef P141_HsMenu /*gvi*/
#pragma push_macro("P141_HsStr") /*gvi*/
#undef P141_HsStr /*gvi*/
extern p141_hsmenu_t P141_HsMenu; extern p141_hsstr_t P141_HsStr;
#pragma pop_macro("P141_HsStr") /*gvi*/
#pragma pop_macro("P141_HsMenu") /*gvi*/
#pragma push_macro("P141_LadI") /*gvi*/
#undef P141_LadI /*gvi*/
#pragma push_macro("P141_LadDepth") /*gvi*/
#undef P141_LadDepth /*gvi*/
#pragma push_macro("P141_LadRooms") /*gvi*/
#undef P141_LadRooms /*gvi*/
#pragma push_macro("P141_LadVal") /*gvi*/
#undef P141_LadVal /*gvi*/
extern int32_t P141_LadI, P141_LadDepth, P141_LadRooms, P141_LadVal;
#pragma pop_macro("P141_LadVal") /*gvi*/
#pragma pop_macro("P141_LadRooms") /*gvi*/
#pragma pop_macro("P141_LadDepth") /*gvi*/
#pragma pop_macro("P141_LadI") /*gvi*/
#endif
int32_t P141_LadderLine(char *line);   /* 0041b8ac: строка DATA\MLADDER.DML → записи P139_Ladder; 0 — ошибка (в debug.log) */
void    P141_HsSetup(void);            /* 0040f3de: заполнение экрана рекордов по 0054bf18 (таблица) и 005fe6bc (уровень) */
/* gvar-img v2.03 begin (tools/gen_gvar_img.py) */
#if !defined(RE_HOOK_BUILD) && !defined(RE_GVAR_PLAIN)
#undef P141_HsMenu
#define P141_HsMenu (*(p141_hsmenu_t *)re_gvar(0x0054bd10u, sizeof(p141_hsmenu_t), (void *)&P141_HsMenu))
#undef P141_HsStr
#define P141_HsStr (*(p141_hsstr_t *)re_gvar(0x0054bf1cu, sizeof(p141_hsstr_t), (void *)&P141_HsStr))
#undef P141_LadI
#define P141_LadI (*(int32_t *)re_gvar(0x0060038cu, sizeof(int32_t), (void *)&P141_LadI))
#undef P141_LadDepth
#define P141_LadDepth (*(int32_t *)re_gvar(0x0060039cu, sizeof(int32_t), (void *)&P141_LadDepth))
#undef P141_LadRooms
#define P141_LadRooms (*(int32_t *)re_gvar(0x006003a0u, sizeof(int32_t), (void *)&P141_LadRooms))
#undef P141_LadVal
#define P141_LadVal (*(int32_t *)re_gvar(0x00600368u, sizeof(int32_t), (void *)&P141_LadVal))
#endif
/* gvar-img v2.03 end */
