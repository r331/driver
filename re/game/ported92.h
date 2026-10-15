#pragma once
#include "gvar.h"
#include "ported19.h"
#include "ported43.h"
#include "ported47.h"
#include "ported56.h"
#include "ported13.h"
#include "ported62.h"
#include "uihandlers3.h"
#include "ported44.h"
#include "ported63.h"
#include "ported79.h"
#include "ported81.h"
#include "ported83.h"
#include "ported84.h"
#include "smallfuncs2.h"
#include <stdint.h>
/* Шаг D, ported92 (веха 1, рендер мира): осевой вариант рисования модели блока карты. cdecl.
   0042982e  P92_DrawAxis(m, idx, pos, mode) — вызывается из 004ee18b/004ee4b7 вместо 00429143, если у модели нет флага 0x4000,
             угол объекта кратен 0x400 (idx ∈ {0, 0x400, 0x800, 0xc00}) и флаги модели & 0x30. Матрица — готовая запись кэша
             P84_MatCache[idx] (её каждый кадр считает 00428928 P83_LightMatrices, поэтому флаг кэша здесь не проверяется),
             позиция камеры в системе модели — XformT(pos) этой матрицей. Тип плоскости записи (флаги записи & 7, если & 8):
             0 — общая (n·(−p) − d), 1..6 — осевые: x−d, −x−d, −z−d, z−d, y−d, −y−d. Флаг модели 1 — освещение: нормали
             (+0x18 штук, +0x28) и общие плоскости — по вектору света P83_LightVec[idx/1024], осевые плоскости получают готовые
             компоненты P81_* (повёрнутые на idx: PosX/NegX/PosZ/NegZ меняются местами; ±Y — NegY/PosY). Обработчик типа записи —
             таблица режима (0 → P84_Tab0, 1 → P84_Tab1, иначе P84_Tab2), аргумент P84_Arg[тип]; невидимая запись пропускается
             шагом G2_TABLE_00550ACC[тип]. В конце P44_XformTag++. */
void P92_DrawAxis(uint32_t m, int32_t idx, const float *pos, int32_t mode);   /* 0042982e */
/* 0042a5de  P92_DrawSpin(m, idx, pos, mode) — модель с флагом 0x80 (вращающаяся текстура: колёса/вентиляторы), из 004ee18b/004ee4b7.
             Пролог как у 0042a423 (сферы света, освещённость плоскости 0 = P81_PosY, смещение, вершины/плоскости, матрица из кэша
             P84_MatCache[idx] с пересчётом по P84_MatFlag/P47_SwapCnt, зеркальная копия). Первая запись (+0x2c): цвета +0x38/+0x3c/+0x40 =
             159.0/168.0/192.0; текстурные координаты четырёх вершин (+0x18..+0x34) — квадрат в прямоугольнике текстуры G012085F4
             (байты +9 u0, +10 v0, +0xb ширина, +0xc высота; отступ r = ширина/32), повёрнутый на угол по кадру: sin = P43_Sin[(кадр&0xff)·16],
             второй = P43_Sin[((кадр&0xff)·16 + 0x6c9) & 0xfff] (индекс остаётся в 00b1c284). Затем обработчик типа записи из таблицы режима
             (0 → P84_Tab0, 1 → P84_Tab1, иначе P84_Tab2) с аргументом 0, или 3, если 00575ee8 ≠ 0. P44_XformTag++.
             G012085F4 (004ec91e по имени 00550808) — 32-битный указатель: в native вместо него родной указатель P92_SpinTex (004ec91e не
             перенесена, пока 0); при 0 координаты не пересчитываются (охранная проверка, в оригинале её нет). */
#define P92_SinIdx GAME_VAR(int32_t, P92_SinIdx, 0x00b1c284)
#ifndef RE_HOOK_BUILD
extern int32_t P92_SinIdx;
extern const uint8_t *P92_SpinTex;   /* native: прямоугольник текстуры вместо 32-битного G012085F4 (пока никто не задаёт) */
#endif
void P92_DrawSpin(uint32_t m, int32_t idx, const float *pos, int32_t mode);   /* 0042a5de */
