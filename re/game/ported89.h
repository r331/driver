#pragma once
#include "gvar.h"
#include "ported4.h"
#include "ported6.h"
#include "ported12.h"
#include "ported14.h"
#include "ported21.h"
#include "ported26.h"
#include "ported33.h"
#include "ported43.h"
#include "ported44.h"
#include "ported46.h"
#include "ported47.h"
#include "ported54.h"
#include "ported55.h"
#include "ported59.h"
#include "ported62.h"
#include "ported69.h"
#include "ported80.h"
#include "ported83.h"
#include "ported85.h"
#include "ported87.h"
#include "ported88.h"
#include "smallfuncs.h"
#include <stdint.h>
/* Шаг D, ported89 (веха 1: город из LEV): маска видимости клеток и главный обход клеток карты. cdecl.
   004ef997  P89_Fill1(out) — D_00d00204 единиц подряд в out;
   004ef793  P89_VisMask(blk, sub, out) — развернуть маску видимости: из блока видимости P46_MapBufA (+0x10+blk·4 — смещение таблицы блока,
             в ней +sub·4 & 0x3fffffff — смещение потока) в D_00d00204 байт 0/1: поток из пар {число полных байтов «все 8 единиц»,
             число байтов с битами (младший бит первым)}; без данных (P46_MapBufA == NULL) или пустого потока — все единицы. Число клеток
             округляется до +1, если не кратно 8 (как в оригинале: может записать на один байт больше);
   004ee8f4  P89_DrawMap(mode) — обход клеток вокруг камеры: маска видимости (в 00cf2fa0), затем при mode≠0 — по строкам сектора
             00cb8f20+(угол/16)·0x80 (FRUSTRUM.DAT: {первая строка, число строк, пары {сдвиг, длина}}) объекты клеток раскладываются по классам
             модели 00c98a40: 1 и 5 (если 00575ee8) — сразу 004ee4b7; 2 → таблица 00ce0f40; 3 → тени 00c97a40; 4 → 00cf1f80; 6 → 00d00260;
             7 → 00cff9e0. Затем рисуются классы 7 (режим 0x13), 4 (альфа-тест 4) и тени 3 (смещение по высоте −4.0, альфа-тест 7).
             Метка кадра в объекте = P47_SwapCnt. */
typedef void *p89_list4_t[0x400];
typedef void *p89_list2_t[0x200];
#define P89_CntShadow GAME_VAR(int32_t, P89_CntShadow, 0x00cfe6e4)
#define P89_CntFour   GAME_VAR(int32_t, P89_CntFour, 0x00ce0f24)
#define P89_CntSeven  GAME_VAR(int32_t, P89_CntSeven, 0x00d00218)
#define P89_ListShadow GAME_VAR(p89_list4_t, P89_ListShadow, 0x00c97a40)
#define P89_ListFour   GAME_VAR(p89_list4_t, P89_ListFour, 0x00cf1f80)
#define P89_ListSeven  GAME_VAR(p89_list2_t, P89_ListSeven, 0x00cff9e0)
#ifndef RE_HOOK_BUILD
#pragma push_macro("P89_CntShadow") /*gvi*/
#undef P89_CntShadow /*gvi*/
#pragma push_macro("P89_CntFour") /*gvi*/
#undef P89_CntFour /*gvi*/
#pragma push_macro("P89_CntSeven") /*gvi*/
#undef P89_CntSeven /*gvi*/
extern int32_t P89_CntShadow, P89_CntFour, P89_CntSeven;
#pragma pop_macro("P89_CntSeven") /*gvi*/
#pragma pop_macro("P89_CntFour") /*gvi*/
#pragma pop_macro("P89_CntShadow") /*gvi*/
extern p89_list4_t P89_ListShadow, P89_ListFour;
extern p89_list2_t P89_ListSeven;
#endif
void P89_Fill1(uint8_t *out);                                   /* 004ef997 */
void P89_VisMask(int32_t blk, int32_t sub, uint8_t *out);       /* 004ef793 */
void P89_DrawMap(int32_t mode);                                 /* 004ee8f4 */
/* gvar-img v2.03 begin (tools/gen_gvar_img.py) */
#if !defined(RE_HOOK_BUILD) && !defined(RE_GVAR_PLAIN)
#undef P89_CntShadow
#define P89_CntShadow (*(int32_t *)re_gvar(0x00cfe6e4u, sizeof(int32_t), (void *)&P89_CntShadow))
#undef P89_CntFour
#define P89_CntFour (*(int32_t *)re_gvar(0x00ce0f24u, sizeof(int32_t), (void *)&P89_CntFour))
#undef P89_CntSeven
#define P89_CntSeven (*(int32_t *)re_gvar(0x00d00218u, sizeof(int32_t), (void *)&P89_CntSeven))
#endif
/* gvar-img v2.03 end */
