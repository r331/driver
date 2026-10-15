#pragma once
#include "gvar.h"
#include "unported.h"
#include "engine.h"
#include "ported54.h"
#include "ported62.h"
#include <stdint.h>
/* Шаг D: 3 функции чтения карты дорог по мировым координатам (x, z): клетка = (x+0x2ee+C64)/0x5dc, (C12c40-(z-0x2ee))/0x5dc;
   карта разбита на плитки MapN×MapN, четыре плитки-буфера выбираются чётностью номера плитки (как в 0051aa5b/0051aacd). Все cdecl. */
#define P72_Rows    GAME_VAR(int32_t, P72_Rows, 0x00cb8f04)     /* число рядов плиток */
#define P72_Id      GAME_VAR(uint16_t, P72_Id, 0x00c1cca6)      /* номер дороги (10 бит) из последней найденной клетки */
#define P72_Low     GAME_VAR(int32_t, P72_Low, 0x00c1cca8)      /* нижние 16 бит записи клетки со знаком */
#define P72_Dir     GAME_VAR(uint16_t, P72_Dir, 0x00c1ccb0)     /* направление из таблицы 00575e28 по старшим 2 битам */
typedef uint16_t p72_dir_t[4];
#define P72_DirTab  GAME_VAR(p72_dir_t, P72_DirTab, 0x00575e28) /* 0, 0x400, 0x800, 0xc00 */
#ifndef RE_HOOK_BUILD
extern int32_t P72_Rows, P72_Low; extern uint16_t P72_Id, P72_Dir; extern p72_dir_t P72_DirTab;
#endif
void    P72_InitConsts(void);                                   /* native: таблица направлений из .data */
int32_t P72_RoadWord(int32_t x, int32_t z);                     /* 0051b111: 16-битное значение клетки карты A (-1 вне карты); старшая половина результата в игре — мусор */
int32_t P72_RoadDword(int32_t x, int32_t z);                    /* 0051b566: 32-битное значение клетки карты B, 0 вне карты */
int32_t P72_RoadLookup(int32_t x, int32_t z);                   /* 0051b65a: как 0051b566, но при ненулевой клетке пишет 00c1cca6/a8/b0 и возвращает 1 */
