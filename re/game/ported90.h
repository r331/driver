#pragma once
#include "gvar.h"
#include "ported44.h"
#include "ported47.h"
#include "ported56.h"
#include "ported63.h"
#include "ported79.h"
#include "ported81.h"
#include "ported84.h"
#include "smallfuncs2.h"
#include <stdint.h>
/* Шаг D, ported90 (веха 1: город из LEV): рисование однозаписной модели блока карты (плоские куски земли/дорог). cdecl.
   0042a423  P90_DrawSingle(m, idx, pos, mode) — короткий вариант 00429143 для моделей из одной записи (004ee4b7 зовёт её, если у модели
             флаги 0x2400 без 0x4000 и +0x16 == 1): сферы света (00426b34) или их сброс, освещённость плоскости 0 = P81_PosY (011b6144,
             свет сверху), смещение = pos (X со знаком зеркала), вершины/плоскости модели (+0x20/+0x24), матрица ViewMat×EulerTab[idx]
             из кэша P84_MatCache (пересчёт, если P84_MatFlag[idx] ≠ P47_SwapCnt), в зеркальном режиме — копия с −[0], −[3], −[6];
             затем обработчик типа первой записи (+0x2c) из таблицы режима (0 → P84_Tab0, 1 → P84_Tab1, иначе P84_Tab2) с аргументом 0,
             без отсечения по плоскостям; P44_XformTag++. */
void P90_DrawSingle(uint32_t m, int32_t idx, float *pos, int32_t mode);   /* 0042a423 */
