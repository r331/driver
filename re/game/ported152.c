/* v2.02: 005291ed — заливка прямоугольника 8-битного буфера: rows строк с шагом 0x280, в каждой ширина округляется вверх до 32 байт
   (8 слов цвета, повторённого 4 раза, за проход; ширина ≤ 0 — строки пропускаются, как в ассемблере 00529220 cmp edx,eax / jge). */
/* ported152.c — rectangle fill of the 8-bit software menu screen (P65_Screen, 640 bytes per row).
   (English overview; the Russian note above is the original porting note.) */
#include "ported152.h"
#include "ported65.h"
#include <string.h>

#define SCREEN_PITCH   0x280    /* bytes per row of the 8-bit screen buffer (640 pixels) */
#define SCREEN_BYTES   0x4b000  /* 640 x 480 bytes: size of P65_Screen */
#define FILL_CHUNK     0x20     /* the original stores 32 bytes per inner iteration (8 dwords) */

/* P152_FillRows — Game.exe 005291ed, cdecl.  Fills `rows` rows of an 8-bit buffer with `color`,
   starting at dst, stepping SCREEN_PITCH bytes per row.  Each row's width is rounded UP to a multiple
   of 32 bytes (the original writes 8 dwords per pass), so it may write up to 31 bytes past `width`.
   width <= 0 writes nothing.  Native: dst == NULL is ignored. */
void P152_FillRows(uint8_t *dst, int32_t width, int32_t rows, uint8_t color) {
  if (dst == NULL) return;
  for (; rows > 0; rows--, dst += SCREEN_PITCH)
    for (int32_t x = 0; x < width; x += FILL_CHUNK) memset(dst + x, color, FILL_CHUNK);
}

/* P152_ScreenFill — native wrapper for the caller at Game.exe 00407d56 (no own Game.exe address):
   fills a width x rows rectangle of P65_Screen at (x, y) with `color` via P152_FillRows.
   Native: clips the fill to the 640x480 buffer (rejects negative x/y and empty sizes, trims rows so
   the 32-byte-rounded last row stays inside SCREEN_BYTES); the hook build passes it through unchanged.
   00407d56 передаёт &P65_Screen[y·0x280 + x]; в native запись ограничена буфером 640×480 (0x4b000) */
void P152_ScreenFill(int32_t x, int32_t y, int32_t width, int32_t rows, uint8_t color) {
  uint8_t *scr = (uint8_t *)P65_Screen;
#ifndef RE_HOOK_BUILD
  int32_t w32 = (width + 0x1f) & ~0x1f;   /* row width as actually written (rounded up to 32) */
  if (x < 0 || y < 0 || rows <= 0 || width <= 0) return;
  int64_t end = (int64_t)(y + rows - 1) * SCREEN_PITCH + x + w32;
  if (end > SCREEN_BYTES) { rows = (int32_t)((SCREEN_BYTES - x - w32) / SCREEN_PITCH) - y + 1; if (rows <= 0) return; }
#endif
  P152_FillRows(scr + (intptr_t)y * SCREEN_PITCH + x, width, rows, color);
}
