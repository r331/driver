#pragma once
#include <stdint.h>
/* v2.02: ported152 — заливка строк программного экрана меню (8 бит, шаг 0x280). cdecl. */
void P152_FillRows(uint8_t *dst, int32_t width, int32_t rows, uint8_t color);   /* 005291ed */
void P152_ScreenFill(int32_t x, int32_t y, int32_t width, int32_t rows, uint8_t color);  /* обёртка 00407d56 для P65_Screen */
