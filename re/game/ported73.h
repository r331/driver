#pragma once
#include "gvar.h"
#include "unported.h"
#include "engine.h"
#include "ported7.h"
#include "ported11.h"
#include "ported17.h"
#include "ported19.h"
#include "ported43.h"
#include "ported60.h"
#include "ported51.h"
#include "ported56.h"
#include "ported59.h"
#include "ported66.h"
#include "ported71.h"
#include "smallfuncs.h"
#include "menustate.h"
#include "globalsets.h"
#include <stdint.h>
/* Шаг D: 3 функции. 005173d7 — вывод текста с масштабом от центра экрана (640x480 -> окно), 0051bf82 — признак стороны у записей
   таблицы дорог (0x42 байта на запись), 00511e60 — сброс таблицы частиц (64 записи по 0xb4, список свободных, радиус счёта). Все cdecl. */
typedef uint8_t p73_mask_t[16];
#define P73_Mask   GAME_VAR(p73_mask_t, P73_Mask, 0x00575e34)       /* 0,1,3,7,0xf,0x1f,0x3f,0x7f,0xff */
#define P73_C566FC GAME_VAR(int32_t, P73_C566FC, 0x00c566fc)
#define P73_C5670C GAME_VAR(int32_t, P73_C5670C, 0x00c5670c)
#define P73_C56760 GAME_VAR(int32_t, P73_C56760, 0x00c56760)        /* 1 + лимит/4 */
#define P73_D00214 GAME_VAR(int32_t, P73_D00214, 0x00d00214)        /* значение для чётных частиц */
#define P73_CF56BC GAME_VAR(int32_t, P73_CF56BC, 0x00cf56bc)        /* значение для нечётных частиц */
#ifndef RE_HOOK_BUILD
#pragma push_macro("P73_Mask") /*gvi*/
#undef P73_Mask /*gvi*/
#pragma push_macro("P73_C566FC") /*gvi*/
#undef P73_C566FC /*gvi*/
#pragma push_macro("P73_C5670C") /*gvi*/
#undef P73_C5670C /*gvi*/
#pragma push_macro("P73_C56760") /*gvi*/
#undef P73_C56760 /*gvi*/
#pragma push_macro("P73_D00214") /*gvi*/
#undef P73_D00214 /*gvi*/
#pragma push_macro("P73_CF56BC") /*gvi*/
#undef P73_CF56BC /*gvi*/
extern p73_mask_t P73_Mask; extern int32_t P73_C566FC, P73_C5670C, P73_C56760, P73_D00214, P73_CF56BC;
#pragma pop_macro("P73_CF56BC") /*gvi*/
#pragma pop_macro("P73_D00214") /*gvi*/
#pragma pop_macro("P73_C56760") /*gvi*/
#pragma pop_macro("P73_C5670C") /*gvi*/
#pragma pop_macro("P73_C566FC") /*gvi*/
#pragma pop_macro("P73_Mask") /*gvi*/
#endif
void P73_InitConsts(void);                                              /* native: таблица масок из .data */
void P73_Text(float x, float y, uint32_t txt, int32_t a, int32_t flags);/* 005173d7: позиция/масштаб от центра экрана, цвет b5a834.., строка txt, флаги -> 0040ab6f */
void P73_RoadSides(void);                                               /* 0051bf82: байт +0x3b записи: 0x82/0x83 нет битов, 0x80/0x81 все биты, 0 иначе; +1 при P17_SlotMapSide != 0 */
void P73_ParticlesReset(void);                                          /* 00511e60 (метка __fastcall ложная — ecx не читается) */
void P73_CatmullRom(const float *t, float *out, const float *p0, const float *p1, const float *p2, const float *p3); /* 0049f031: сплайн Катмулла–Рома по 4 точкам, компоненты 0,1,2,4 */
/* gvar-img v2.03 begin (tools/gen_gvar_img.py) */
#if !defined(RE_HOOK_BUILD) && !defined(RE_GVAR_PLAIN)
#undef P73_Mask
#define P73_Mask (*(p73_mask_t *)re_gvar(0x00575e34u, sizeof(p73_mask_t), (void *)&P73_Mask))
#undef P73_C566FC
#define P73_C566FC (*(int32_t *)re_gvar(0x00c566fcu, sizeof(int32_t), (void *)&P73_C566FC))
#undef P73_C5670C
#define P73_C5670C (*(int32_t *)re_gvar(0x00c5670cu, sizeof(int32_t), (void *)&P73_C5670C))
#undef P73_C56760
#define P73_C56760 (*(int32_t *)re_gvar(0x00c56760u, sizeof(int32_t), (void *)&P73_C56760))
#undef P73_D00214
#define P73_D00214 (*(int32_t *)re_gvar(0x00d00214u, sizeof(int32_t), (void *)&P73_D00214))
#undef P73_CF56BC
#define P73_CF56BC (*(int32_t *)re_gvar(0x00cf56bcu, sizeof(int32_t), (void *)&P73_CF56BC))
#endif
/* gvar-img v2.03 end */
