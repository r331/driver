#pragma once
#include "gvar.h"
#include "ported6.h"
#include "ported12.h"
#include "ported14.h"
#include "ported21.h"
#include "ported42.h"
#include "ported44.h"
#include "ported54.h"
#include "ported59.h"
#include "ported87.h"
#include <stdint.h>
/* Шаг D, ported88 (веха 1): положение камеры в сетке блоков карты и подгрузка соседних блоков. cdecl.
   004edd08  P88_CellUpdate(mode) — mode 0: пересчитать два описателя положения (по 0x28 байт): A (00c97a00, камера: (CamX+CellX)·scale, (CamZ+CellY)·scale
             через __ftol) и B (00cff9a0, «источник загрузки»: при 00b87eec≠0 копия A; иначе по флагам — камера, объект 00d0cbd0/d8 или игрок 00d07888/90),
             затем подгрузить блоки 004edaa2; mode≠0: только отметить занятые клетки (00489ed6).
   004edaa2  P88_StreamTiles() — по положению B: если камера ближе 20 единиц к краю блока (rx/ry), загрузить 1–3 соседних блока (боковые и угловой)
             в слоты (индекс слота = чётность cx/cy), если их ещё нет в 00d00220..2c (P87_LoadTile).
   Поля описателя: x, y, idx=x+y·GridDiv, cell=cx+cy·(GridDiv/N), cx=x/N, cy=y/N, rx=x−cx·N, ry=y−cy·N, prev (прежний cell), чётности cx&1, cy&1, их сумма. */
typedef struct { int32_t x, y, idx, cell, cx, cy, rx, ry, prev; uint8_t px, py, pc, pad; } p88_cell_t;
_Static_assert(sizeof(p88_cell_t) == 0x28, "p88_cell_t");
#define P88_CellA   GAME_VAR(p88_cell_t, P88_CellA, 0x00c97a00)
#define P88_CellB   GAME_VAR(p88_cell_t, P88_CellB, 0x00cff9a0)
#define P88_ObjX    CARTAB_VAR(int32_t, P88_ObjX, 0x00d0cbd0)
#define P88_ObjZ    CARTAB_VAR(int32_t, P88_ObjZ, 0x00d0cbd8)
#define P88_Mode575 GAME_VAR(int32_t, P88_Mode575, 0x00575efc)
#ifndef RE_HOOK_BUILD
extern p88_cell_t P88_CellA, P88_CellB;
extern int32_t P88_Mode575;
#endif
void P88_CellUpdate(int32_t mode);   /* 004edd08 */
void P88_StreamTiles(void);          /* 004edaa2 */
/* не из оригинала: выбор соседних блоков (логика 004edaa2) для проверки; возвращает число блоков 0..3 */
int32_t P88_PickTiles(const p88_cell_t *b, int32_t *lump, int32_t *slot);
