#pragma once
#include "gvar.h"
#include "unported.h"
#include "engine.h"
#include "ported5.h"
#include "ported7.h"
#include "ported12.h"
#include "ported19.h"
#include "ported27.h"
#include "ported31.h"
#include "ported32.h"
#include "ported36.h"
#include "ported45.h"
#include "smallfuncs.h"
#include "uihandlers.h"
#include "menustate.h"
#include "director.h"
#include "directorstorage.h"
#include <stdint.h>
/* Шаг D: 26 мелких функций — циклы экранов меню (одна и та же схема: подготовка, 0040c8a0, 0040ccb4, опрос 0040c8f1),
   файлы рекордов SAVES\SCORES.HI, сохранение/загрузка режиссёра, запись блока в файл, пропуск блока карты, сброс слотов
   текстур и пересчёт координат. Все cdecl (Ghidra-метка __fastcall у циклов меню ложная: ECX не используется). */
#define P57_S5D5794 GAME_VAR(int32_t, P57_S5D5794, 0x005d5794)
#define P57_S5D5774 GAME_VAR(int32_t, P57_S5D5774, 0x005d5774)
#define P57_S5FE4EC GAME_VAR(int32_t, P57_S5FE4EC, 0x005fe4ec)
#define P57_S5FE990 GAME_VAR(int32_t, P57_S5FE990, 0x005fe990)
#define P57_S5FE9A0 GAME_VAR(int32_t, P57_S5FE9A0, 0x005fe9a0)
#define P57_S5D579C GAME_VAR(int32_t, P57_S5D579C, 0x005d579c)
#define P57_S5FE6B8 GAME_VAR(int32_t, P57_S5FE6B8, 0x005fe6b8)
#define P57_S5FE998 GAME_VAR(int32_t, P57_S5FE998, 0x005fe998)
#define P57_S5FE9A8 GAME_VAR(int32_t, P57_S5FE9A8, 0x005fe9a8)
#define P57_S5FE9E8 GAME_VAR(int32_t, P57_S5FE9E8, 0x005fe9e8)
#define P57_S57B568 GAME_VAR(int32_t, P57_S57B568, 0x0057b568)
#define P57_S5FE848 GAME_VAR(int32_t, P57_S5FE848, 0x005fe848)
#define P57_S5FE924 GAME_VAR(int32_t, P57_S5FE924, 0x005fe924)
#define P57_ScrW GAME_VAR(int32_t, P57_ScrW, 0x00c80890)
#define P57_Div1500 GAME_VAR(float, P57_Div1500, 0x005469c4)
#ifndef RE_HOOK_BUILD
extern int32_t P57_S5D5794, P57_S5D5774, P57_S5FE4EC, P57_S5FE990, P57_S5FE9A0, P57_S5D579C, P57_S5FE6B8, P57_S5FE998,
    P57_S5FE9A8, P57_S5FE9E8, P57_S57B568, P57_S5FE848, P57_S5FE924, P57_ScrW;
extern float P57_Div1500;
#endif
void    P57_InitConsts(void);
void    P57_MenuDone(void);                         /* 0040cd17: 6 тиков ожидания перед возвратом из экрана */
int32_t P57_Menu40A3A0(void);                       /* 0040a3a0 */
int32_t P57_Menu4082A0(void);                       /* 004082a0 */
int32_t P57_Menu40E870(void);                       /* 0040e870 */
int32_t P57_Menu4134A0(void);                       /* 004134a0 */
int32_t P57_Menu413890(void);                       /* 00413890 */
int32_t P57_Menu40A540(void);                       /* 0040a540 */
int32_t P57_Menu40F2D0(void);                       /* 0040f2d0 */
int32_t P57_Menu413610(void);                       /* 00413610 */
int32_t P57_Menu413B00(void);                       /* 00413b00 */
int32_t P57_Menu416390(void);                       /* 00416390 */
int32_t P57_Menu4045E0(void);                       /* 004045e0 */
int32_t P57_Menu404850(void);                       /* 00404850 */
int32_t P57_Menu411FD0(void);                       /* 00411fd0 */
int32_t P57_Menu4123D0(void);                       /* 004123d0 */
int32_t SaveDirector(const char *name);             /* 004c92c0 */
int32_t LoadDirector(const char *name);             /* 004c9310 */
void    P57_SaveDirectorIfAny(const char *name);    /* 004c93b1 */
void    P57_LoadScores(void);                       /* 00406439 */
void    P57_SaveScores(void);                       /* 00406479 */
int32_t P57_FileExists(const char *name);           /* 00406b51 */
int32_t P57_WriteFile(const char *name, const void *buf, int32_t size); /* 004d30a3 */
void    P57_SkipBlock(void *file, int32_t size);    /* 004ec2ec */
void    P57_ResetTexNodes(void);                    /* 00421a39 */
void    P57_ScreenToView(float *x, float *y);       /* 005075f6 */
