#pragma once
#include "gvar.h"
#include "unported.h"
#include "crt.h"
#include "engine.h"
#include "ported4.h"
#include "ported27.h"
#include "ported58.h"
#include "smallfuncs.h"
#include <stdint.h>
/* Шаг D, ported78 (все cdecl): загрузчики блоков файла уровня.
   - 004eb811 — блок 4: вершины 0x2c байта → записи по 0x40 (w = 1.0f), два массива одного размера;
   - 004eafe0 — блок 0x13: фонари («GLMP», сетка w*h из пар {число, массив по 0x28 байт}); 004eafcf — обёртка без результата;
   - 004a31fc — добавить список кресел в ячейку сетки; 004a2f77 — блок 0x14: кресла («Chair lump», версия 2). */
typedef int32_t p78_hdr_t[5];
#define P78_VertCount GAME_VAR(int32_t, P78_VertCount, 0x00d00200)
#define P78_VertsA    GAME_VAR(void *, P78_VertsA, 0x00d0020c)
#define P78_VertsB    GAME_VAR(void *, P78_VertsB, 0x00c97a2c)
#define P78_LampHdr   GAME_VAR(p78_hdr_t, P78_LampHdr, 0x00d02300)
#ifndef RE_HOOK_BUILD
extern int32_t P78_VertCount; extern void *P78_VertsA, *P78_VertsB; extern p78_hdr_t P78_LampHdr;
#endif
void    P78_LoadVerts(void *f, int32_t size);       /* 004eb811 */
int32_t P78_LoadLamps(void *f);                      /* 004eafe0 */
void    P78_LoadLampsBlock(void *f);                 /* 004eafcf */
int32_t P78_ChairAdd(const p58_cell_t *rec);         /* 004a31fc: rec = {индекс ячейки, число, буфер} */
void    P78_LoadChairs(void *f, int32_t size);       /* 004a2f77 */
