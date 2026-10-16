/* v2.02: 005291ed — заливка прямоугольника 8-битного буфера: rows строк с шагом 0x280, в каждой ширина округляется вверх до 32 байт
   (8 слов цвета, повторённого 4 раза, за проход; ширина ≤ 0 — строки пропускаются, как в ассемблере 00529220 cmp edx,eax / jge). */
#include "ported152.h"
#include "ported65.h"
#include <string.h>

void P152_FillRows(uint8_t *dst, int32_t width, int32_t rows, uint8_t color) {
  if (dst == NULL) return;
  for (; rows > 0; rows--, dst += 0x280)
    for (int32_t x = 0; x < width; x += 0x20) memset(dst + x, color, 0x20);
}

/* 00407d56 передаёт &P65_Screen[y·0x280 + x]; в native запись ограничена буфером 640×480 (0x4b000) */
void P152_ScreenFill(int32_t x, int32_t y, int32_t width, int32_t rows, uint8_t color) {
  uint8_t *scr = (uint8_t *)P65_Screen;
#ifndef RE_HOOK_BUILD
  int32_t w32 = (width + 0x1f) & ~0x1f;
  if (x < 0 || y < 0 || rows <= 0 || width <= 0) return;
  int64_t end = (int64_t)(y + rows - 1) * 0x280 + x + w32;
  if (end > 0x4b000) { rows = (int32_t)((0x4b000 - x - w32) / 0x280) - y + 1; if (rows <= 0) return; }
#endif
  P152_FillRows(scr + (intptr_t)y * 0x280 + x, width, rows, color);
}
