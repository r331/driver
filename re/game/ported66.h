#pragma once
#include "gvar.h"
#include "unported.h"
#include "engine.h"
#include "ported5.h"
#include "ported6.h"
#include "ported7.h"
#include "ported12.h"
#include "ported15.h"
#include "ported19.h"
#include "ported21.h"
#include "ported25.h"
#include "ported31.h"
#include "ported47.h"
#include "ported52.h"
#include "ported59.h"
#include "ported29.h"
#include "director.h"
#include "dirnodes.h"
#include "smallfuncs.h"
#include "uihandlers2.h"
#include "uihandlers3.h"
#include <stdint.h>
/* Шаг D: 3 функции кадра экрана меню (все cdecl; Ghidra-метка __fastcall у 004188b0 ложная — ecx не читается).
   0041846c — один кадр экрана: подготовка (004188b0), рисование таблицы текстовых пунктов (0041897c), необязательный обратный вызов.
   Таблица пунктов: записи по 16 байт, конец — запись с нулевым полем +8 (текст, 32-битный адрес). */
#define P66_Nest      GAME_VAR(int32_t, P66_Nest, 0x005fea50)       /* счётчик вложенности кадра (после кадра = число тиков) */
#define P66_LoadFlag  GAME_VAR(int32_t, P66_LoadFlag, 0x005fea64)
#define P66_Scene     GAME_VAR(uint32_t, P66_Scene, 0x00cf2f84)     /* 32-битный адрес 0xcb8f20 */
#define P66_C255      GAME_VAR(float, P66_C255, 0x00546064)         /* 255.0 */
#define P66_C128      GAME_VAR(float, P66_C128, 0x00546074)         /* 128.0 */
#define P66_C2        GAME_VAR(float, P66_C2, 0x00546050)           /* 2.0 — сдвиг тени */
#ifndef RE_HOOK_BUILD
#pragma push_macro("P66_Nest") /*gvi*/
#undef P66_Nest /*gvi*/
#pragma push_macro("P66_LoadFlag") /*gvi*/
#undef P66_LoadFlag /*gvi*/
extern int32_t P66_Nest, P66_LoadFlag;
#pragma pop_macro("P66_LoadFlag") /*gvi*/
#pragma pop_macro("P66_Nest") /*gvi*/
#pragma push_macro("P66_Scene") /*gvi*/
#undef P66_Scene /*gvi*/
extern uint32_t P66_Scene;
#pragma pop_macro("P66_Scene") /*gvi*/
#pragma push_macro("P66_C255") /*gvi*/
#undef P66_C255 /*gvi*/
#pragma push_macro("P66_C128") /*gvi*/
#undef P66_C128 /*gvi*/
#pragma push_macro("P66_C2") /*gvi*/
#undef P66_C2 /*gvi*/
extern float P66_C255, P66_C128, P66_C2;
#pragma pop_macro("P66_C2") /*gvi*/
#pragma pop_macro("P66_C128") /*gvi*/
#pragma pop_macro("P66_C255") /*gvi*/
#endif
void P66_InitConsts(void);
void P66_FrameBegin(void);                      /* 004188b0: сцена, CD-трек 3, звук, режим 00426580(4..7 | 1), карты 0/1, 0x18 */
void P66_DrawTable(const void *tbl);            /* 0041897c: рисует пункты (текст или текст с тенью) */
void P66_ScreenFrame(uint32_t tbl, uint32_t cb);/* 0041846c: кадр экрана; tbl — таблица пунктов, cb — функция без аргументов */
void P66_DirSwitch(void);                    /* 004c862f: действие по режиму режиссёра (P29_Mode-1), затем DrawCornerIndicator */
/* gvar-img v2.03 begin (tools/gen_gvar_img.py) */
#if !defined(RE_HOOK_BUILD) && !defined(RE_GVAR_PLAIN)
#undef P66_Nest
#define P66_Nest (*(int32_t *)re_gvar(0x005fea50u, sizeof(int32_t), (void *)&P66_Nest))
#undef P66_LoadFlag
#define P66_LoadFlag (*(int32_t *)re_gvar(0x005fea64u, sizeof(int32_t), (void *)&P66_LoadFlag))
#undef P66_Scene
#define P66_Scene (*(uint32_t *)re_gvar(0x00cf2f84u, sizeof(uint32_t), (void *)&P66_Scene))
#undef P66_C255
#define P66_C255 (*(float *)re_gvar(0x00546064u, sizeof(float), (void *)&P66_C255))
#undef P66_C128
#define P66_C128 (*(float *)re_gvar(0x00546074u, sizeof(float), (void *)&P66_C128))
#undef P66_C2
#define P66_C2 (*(float *)re_gvar(0x00546050u, sizeof(float), (void *)&P66_C2))
#endif
/* gvar-img v2.03 end */
