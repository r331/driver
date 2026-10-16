#pragma once
#include "gvar.h"
#include "unported.h"
#include "ported6.h"
#include "ported21.h"
#include "ported44.h"
#include "ported47.h"
#include "ported54.h"
#include "ported76.h"
#include "ported79.h"
#include "ported80.h"
#include "ported62.h"
#include "ported70.h"
#include "ported83.h"
#include "ported84.h"
#include <stdint.h>
/* Шаг D, ported87 (веха 1: город из LEV): блок карты в слоты и рисование объектов карты. cdecl.
   004ed5f8  P87_LoadTile(lump, slot) — загрузить блок (плитку) карты №lump в один из четырёх слотов 0..3:
             • узлы списков {u16 номер объекта, u16 следующий} → 8-байтные записи (int32, int32) массива 00ce0f20 (слот·0x5000 узлов);
               номера ≥ Cnt1E0 (объекты блока) сдвигаются на слот·0x2000, «следующий» — на слот·0x5000, 0xffff → −1;
             • сетка голов списков N×N (N = P54_GridN) в 00d01268 (слот·N·N int32): режимы 0 (пусто), 1 (u16 на клетку), 2 (битовая маска + u16);
             • объекты блока (запись 0x14 на диске → 0x20 в памяти: [0] метка кадра, [4] номер модели&0x7fff, [8,0xc,0x10] x,y,z (float),
               [0x18] угол (индекс EulerTab), [0x1c] 1 — если бит 0x8000) в 00d00208 с номера Cnt1E0 + слот·0x2000;
             • 00c39da0[слот] = lump; карты дорог 0051ab31/0051ac05 для плитки (с отражением ряда).
   004ee4b7  P87_DrawObjB(obj) / 004ee18b P87_DrawObjA(obj) — нарисовать объект карты (запись 0x20 байт): видимость модели P83_BoxVis(pos, радиус),
             регистрация в списке 00562d7c (каждый 16-й), позиция − камера → вид (P44_Xform), затем P84_DrawModelIdx (режим 0/1/2 по видимости
             и высоте модели); особые случаи — флаг 4 (004fef26), 0x80 (0042a5de, только A), «сжатые» модели 0042a423 (только B) и осевые 0042982e. */
#define P87_CntA   GAME_VAR(int32_t, P87_CntA, 0x00b31edc)
#define P87_CntB   GAME_VAR(int32_t, P87_CntB, 0x00d022e0)
#define P87_ListPtr GAME_VAR(void **, P87_ListPtr, 0x00562d7c)
typedef int32_t p87_lumps_t[4];
#define P87_SlotLumpA GAME_VAR(p87_lumps_t, P87_SlotLumpA, 0x00d00220)
#define P87_SlotLump GAME_VAR(p87_lumps_t, P87_SlotLump, 0x00c39da0)   /* номер блока в слоте */
#ifndef RE_HOOK_BUILD
#pragma push_macro("P87_CntA") /*gvi*/
#undef P87_CntA /*gvi*/
#pragma push_macro("P87_CntB") /*gvi*/
#undef P87_CntB /*gvi*/
extern int32_t P87_CntA, P87_CntB;
#pragma pop_macro("P87_CntB") /*gvi*/
#pragma pop_macro("P87_CntA") /*gvi*/
extern void **P87_ListPtr;
#pragma push_macro("P87_SlotLump") /*gvi*/
#undef P87_SlotLump /*gvi*/
#pragma push_macro("P87_SlotLumpA") /*gvi*/
#undef P87_SlotLumpA /*gvi*/
extern p87_lumps_t P87_SlotLump, P87_SlotLumpA;
#pragma pop_macro("P87_SlotLumpA") /*gvi*/
#pragma pop_macro("P87_SlotLump") /*gvi*/
#endif
void P87_LoadTile(int32_t lump, int32_t slot);   /* 004ed5f8 */
void P87_DrawObjA(const uint8_t *obj);           /* 004ee18b */
void P87_DrawObjB(const uint8_t *obj);           /* 004ee4b7 */
/* Не из оригинала (упрощённый вариант 004ee8f4 без маски видимости): нарисовать объекты клеток квадрата радиуса r вокруг клетки (cx, cy)
   — по спискам плиток, загруженных в слоты; метка кадра = P44_XformTag. Возвращает число нарисованных объектов. */
int32_t P87_DrawCells(int32_t cx, int32_t cy, int32_t r);
/* gvar-img v2.03 begin (tools/gen_gvar_img.py) */
#if !defined(RE_HOOK_BUILD) && !defined(RE_GVAR_PLAIN)
#undef P87_CntA
#define P87_CntA (*(int32_t *)re_gvar(0x00b31edcu, sizeof(int32_t), (void *)&P87_CntA))
#undef P87_CntB
#define P87_CntB (*(int32_t *)re_gvar(0x00d022e0u, sizeof(int32_t), (void *)&P87_CntB))
#undef P87_SlotLumpA
#define P87_SlotLumpA (*(p87_lumps_t *)re_gvar(0x00d00220u, sizeof(p87_lumps_t), (void *)&P87_SlotLumpA))
#undef P87_SlotLump
#define P87_SlotLump (*(p87_lumps_t *)re_gvar(0x00c39da0u, sizeof(p87_lumps_t), (void *)&P87_SlotLump))
#endif
/* gvar-img v2.03 end */
