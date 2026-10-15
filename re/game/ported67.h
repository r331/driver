#pragma once
#include "gvar.h"
#include "unported.h"
#include "engine.h"
#include "ported6.h"
#include "ported12.h"
#include "ported19.h"
#include "ported31.h"
#include "ported36.h"
#include "ported48.h"
#include "ported57.h"
#include "ported58.h"
#include "ported65.h"
#include "globalsets.h"
#include "smallfuncs.h"
#include "menustate.h"
#include "uihandlers.h"
#include <stdint.h>
/* Шаг D: 7 функций — таблица пулов 30 записей, рисование по центру экрана, значки REFLEC/GT, шаг частицы, три экрана меню.
   Все cdecl (метки __fastcall/__thiscall у 00415ec0 и 00415188 ложные — ecx не читается). */
typedef struct { int16_t a; int16_t used; uint32_t item; uint8_t rest[0x20]; } P67_Ent;  /* запись 0x28 байт: +0 номер, +2 занята, +4 значение */
_Static_assert(sizeof(P67_Ent) == 0x28, "P67_Ent");
_Static_assert(__builtin_offsetof(P67_Ent, item) == 4, "P67_Ent.item");
typedef P67_Ent P67_EntArr[30];
typedef uint32_t P67_ItemArr[30];
#define P67_Ents    GAME_VAR(P67_EntArr, P67_Ents, 0x01123300)
#define P67_Items   GAME_VAR(P67_ItemArr, P67_Items, 0x010ffb60)
#define P67_ItemCnt GAME_VAR(int32_t, P67_ItemCnt, 0x0110b024)
#define P67_Cur     GAME_VAR(int32_t, P67_Cur, 0x00d11924)
#define P67_Sel2C   GAME_VAR(int32_t, P67_Sel2C, 0x005fea2c)     /* выбранный пункт экрана 00417970 */
#define P67_Res51C  GAME_VAR(int32_t, P67_Res51C, 0x0054e51c)
#define P67_Tbl100  GAME_VAR(uint32_t, P67_Tbl100, 0x0054e100)   /* адрес таблицы пунктов (читается из .data игры) */
#ifndef RE_HOOK_BUILD
extern P67_EntArr P67_Ents; extern P67_ItemArr P67_Items;
extern int32_t P67_ItemCnt, P67_Cur, P67_Sel2C, P67_Res51C; extern uint32_t P67_Tbl100;
#endif
void    P67_CompactPool(void);                         /* 004bb060: свободные записи берут значения из пула, пул очищается */
void    P67_CenterDraw(float x, float y, float z, uint32_t p4);  /* 00516fbe: позиция (масштабирование от центра экрана), цвет, значения, 0040abac */
void    P67_ObjStep(void *obj);                        /* 00513fbc: шаг частицы/объекта (поля +0xc флаги, +0x38, +0x5c, +0x60) */
void    P67_Logo(int32_t which, int32_t y);            /* 004a9e88: значок «GT» (which==1) или REFLEC по центру (x=480-w/2) */
void    P67_DrawIcon(int32_t x, int32_t y, int32_t unused, const char *name);  /* 0040cfdf: рисует значок по имени (четвёртый аргумент) */
int32_t P67_Menu415EC0(void);                          /* 00415ec0: экран с таблицей 0054e0b0/значение из 0054e100 */
int32_t P67_Menu417970(void);                          /* 00417970: экран с таблицей 0054e480 */
int32_t P67_Menu415188(void);                          /* 00415188: смена режима звука/музыки (0→1→2→0) */
