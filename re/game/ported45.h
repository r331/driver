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
#define P45_PtrB      GAME_VAR(uint32_t, P45_PtrB, 0x005f7e64)
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
extern int32_t P45_Mode, P45_Busy, P45_Step, P45_Pick;
extern uint32_t P45_PtrB, P45_PtrA, P45_Color, P45_Col0, P45_Col1, P45_Col2, P45_Col3, P45_Col4;
#endif
int32_t P45_ModeA(void);                     /* 0040834f: код пункта -> вариант A (0x2e..0x31), перерисовка; 1 */
int32_t P45_ModeB(void);                     /* 00408458: код пункта -> вариант B (0x92..0x95), перерисовка; 1 */
void    P45_Wait(uint32_t a, uint32_t b);    /* 0040ccb4: 6 раз: сообщения, ввод, шаг 5..0 (0040cb9f) */
void    P45_PickColor(void);                 /* 00417cbb: цвет по выбранному 0..4, чёрный фон, ярко-жёлтая вспышка */
