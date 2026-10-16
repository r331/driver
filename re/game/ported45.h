#pragma once
#include "gvar.h"
#include "unported.h"
#include "uihandlers.h"
#include "ported5.h"
#include "ported6.h"
#include "ported31.h"
#include "ported36.h"
#include "smallfuncs.h"
#include <stdint.h>
/* Переключение вариантов меню, ожидание-прокрутка и цвет кнопки по уровню. */
#define P45_Mode      GAME_VAR(int32_t, P45_Mode, 0x00b87e38)   /* код текущего пункта (0x2e..0x31 / 0x92..0x95) */
/* 005f7e64 — P58_ItemList (родной указатель; P45_Wait переводит адрес через re_ptr) */
#define P45_PtrA      GAME_VAR(uint32_t, P45_PtrA, 0x005f7e40)
#define P45_Busy      GAME_VAR(int32_t, P45_Busy, 0x005f7e44)
#define P45_Step      GAME_VAR(int32_t, P45_Step, 0x005f7e48)
#define P45_Pick      GAME_VAR(int32_t, P45_Pick, 0x005fed9c)
#define P45_Color     GAME_VAR(uint32_t, P45_Color, 0x0054e4d8)
#define P45_Col0      GAME_VAR(uint32_t, P45_Col0, 0x00c55a6c)
#define P45_Col1      GAME_VAR(uint32_t, P45_Col1, 0x00c55a5c)
#define P45_Col2      GAME_VAR(uint32_t, P45_Col2, 0x00c55a60)
#define P45_Col3      GAME_VAR(uint32_t, P45_Col3, 0x00c55a64)
#define P45_Col4      GAME_VAR(uint32_t, P45_Col4, 0x00c55a68)
#ifndef RE_HOOK_BUILD
#pragma push_macro("P45_Mode") /*gvi*/
#undef P45_Mode /*gvi*/
#pragma push_macro("P45_Busy") /*gvi*/
#undef P45_Busy /*gvi*/
#pragma push_macro("P45_Step") /*gvi*/
#undef P45_Step /*gvi*/
#pragma push_macro("P45_Pick") /*gvi*/
#undef P45_Pick /*gvi*/
extern int32_t P45_Mode, P45_Busy, P45_Step, P45_Pick;
#pragma pop_macro("P45_Pick") /*gvi*/
#pragma pop_macro("P45_Step") /*gvi*/
#pragma pop_macro("P45_Busy") /*gvi*/
#pragma pop_macro("P45_Mode") /*gvi*/
#pragma push_macro("P45_PtrA") /*gvi*/
#undef P45_PtrA /*gvi*/
#pragma push_macro("P45_Color") /*gvi*/
#undef P45_Color /*gvi*/
#pragma push_macro("P45_Col0") /*gvi*/
#undef P45_Col0 /*gvi*/
#pragma push_macro("P45_Col1") /*gvi*/
#undef P45_Col1 /*gvi*/
#pragma push_macro("P45_Col2") /*gvi*/
#undef P45_Col2 /*gvi*/
#pragma push_macro("P45_Col3") /*gvi*/
#undef P45_Col3 /*gvi*/
#pragma push_macro("P45_Col4") /*gvi*/
#undef P45_Col4 /*gvi*/
extern uint32_t P45_PtrA, P45_Color, P45_Col0, P45_Col1, P45_Col2, P45_Col3, P45_Col4;
#pragma pop_macro("P45_Col4") /*gvi*/
#pragma pop_macro("P45_Col3") /*gvi*/
#pragma pop_macro("P45_Col2") /*gvi*/
#pragma pop_macro("P45_Col1") /*gvi*/
#pragma pop_macro("P45_Col0") /*gvi*/
#pragma pop_macro("P45_Color") /*gvi*/
#pragma pop_macro("P45_PtrA") /*gvi*/
#endif
int32_t P45_ModeA(void);                     /* 0040834f: код пункта -> вариант A (0x2e..0x31), перерисовка; 1 */
int32_t P45_ModeB(void);                     /* 00408458: код пункта -> вариант B (0x92..0x95), перерисовка; 1 */
void    P45_Wait(uint32_t a, uint32_t b);    /* 0040ccb4: 6 раз: сообщения, ввод, шаг 5..0 (0040cb9f) */
void    P45_PickColor(void);                 /* 00417cbb: цвет по выбранному 0..4, чёрный фон, ярко-жёлтая вспышка */
/* gvar-img v2.03 begin (tools/gen_gvar_img.py) */
#if !defined(RE_HOOK_BUILD) && !defined(RE_GVAR_PLAIN)
#undef P45_Mode
#define P45_Mode (*(int32_t *)re_gvar(0x00b87e38u, sizeof(int32_t), (void *)&P45_Mode))
#undef P45_PtrA
#define P45_PtrA (*(uint32_t *)re_gvar(0x005f7e40u, sizeof(uint32_t), (void *)&P45_PtrA))
#undef P45_Busy
#define P45_Busy (*(int32_t *)re_gvar(0x005f7e44u, sizeof(int32_t), (void *)&P45_Busy))
#undef P45_Step
#define P45_Step (*(int32_t *)re_gvar(0x005f7e48u, sizeof(int32_t), (void *)&P45_Step))
#undef P45_Pick
#define P45_Pick (*(int32_t *)re_gvar(0x005fed9cu, sizeof(int32_t), (void *)&P45_Pick))
#undef P45_Color
#define P45_Color (*(uint32_t *)re_gvar(0x0054e4d8u, sizeof(uint32_t), (void *)&P45_Color))
#undef P45_Col0
#define P45_Col0 (*(uint32_t *)re_gvar(0x00c55a6cu, sizeof(uint32_t), (void *)&P45_Col0))
#undef P45_Col1
#define P45_Col1 (*(uint32_t *)re_gvar(0x00c55a5cu, sizeof(uint32_t), (void *)&P45_Col1))
#undef P45_Col2
#define P45_Col2 (*(uint32_t *)re_gvar(0x00c55a60u, sizeof(uint32_t), (void *)&P45_Col2))
#undef P45_Col3
#define P45_Col3 (*(uint32_t *)re_gvar(0x00c55a64u, sizeof(uint32_t), (void *)&P45_Col3))
#undef P45_Col4
#define P45_Col4 (*(uint32_t *)re_gvar(0x00c55a68u, sizeof(uint32_t), (void *)&P45_Col4))
#endif
/* gvar-img v2.03 end */
