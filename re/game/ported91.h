#pragma once
#include "gvar.h"
#include "director.h"
#include "uihandlers3.h"
#include <stdint.h>
/* Шаг D, ported91: 004a66ef P91_ReleaseTraffic(car) — освобождение слота трафика у машины: признак занятости (байт +5 записи 0x54
   таблицы 011443e0 с номером из байта по указателю car+0xcd0, минус 1) = 0, car+0xcb4 = 0, счётчик 0112b284--, при нуле и
   0112b280 < 0x200 — 0112b280 = 0x200. cdecl. Указатель в car+0xcd0 — нативного размера в native, 32-битный в hook. */
#define G0112B280 GAME_VAR(int32_t, G0112B280, 0x0112b280)
#ifndef RE_HOOK_BUILD
extern int32_t G0112B280;
#endif
void P91_ReleaseTraffic(uint8_t *car);   /* 004a66ef */
