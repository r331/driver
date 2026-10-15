#include "ported17.h"
#include <string.h>
GAME_VAR_DEF(uint32_t, P17_SqrtArg, 0x0057a136)
GAME_VAR_DEF(uint32_t, P17_PtrA, 0x00b5a730)
GAME_VAR_DEF(uint32_t, P17_PtrB, 0x00b5a734)
GAME_VAR_DEF(int32_t, P17_ValA, 0x00575550)
GAME_VAR_DEF(int32_t, P17_ValB, 0x00575554)
GAME_VAR_DEF(int32_t, P17_Const6, 0x005f7e54)
GAME_VAR_DEF(int32_t, P17_Cond1, 0x00d11934)
GAME_VAR_DEF(int32_t, P17_Cond2, 0x00b87e38)
GAME_VAR_DEF(int32_t, P17_Src, 0x00c80ee8)
GAME_VAR_DEF(int32_t, P17_Dst, 0x0054aa44)

/* Слот: 0x2c байта, четыре int16-ячейки со смещением 0, 8, 0x10, 0x18 от 0xc1ed8a (шаг 8 байт). */
static int16_t slot_cell(int slot, int cell) {
  int16_t v; memcpy(&v, P17_SlotBase + slot * 0x2c + cell * 8, 2); return v;
}

uint8_t P17_SlotMapSide(int32_t id) {
  int16_t slot; memcpy(&slot, P17_MapBase + id * 0x42, 2);
  if (slot_cell(slot, 0) == id) return 0;
  if (slot_cell(slot, 2) == id) return 0;
  return 1;
}

uint8_t P17_SlotFindIndex(int16_t slot, int16_t id) {
  for (int i = 0; i < 4; i++) if (slot_cell(slot, i) == id) return (uint8_t)i;
  return 0xff;
}

uint32_t P17_ISqrt(uint32_t v) {
  P17_SqrtArg = v;
  if ((int32_t)v < 4) return 1;
  int e = 31; while ((v >> e) == 0) e--;
  uint32_t lo = 0, hi = v, mid = v;
  if (e > 3) { lo = 1u << ((e >> 1) & 31); hi = 1u << (((e >> 1) + 1) & 31); mid = (uint32_t)((int32_t)(hi + lo) >> 1); }
  uint32_t r;
  while (r = (uint32_t)((int32_t)mid >> 1), lo != r) {
    if (hi == r) return r - 1;
    if (v == r * r) return r;
    if ((int32_t)v < (int32_t)(r * r)) { hi = r; mid = r + lo; }
    else { mid = r + hi; lo = r; }
  }
  return r;
}

void P17_PushScreenState(void) {
  P17_PtrB = P17_PtrA;
  P17_ValB = P17_ValA;
  P17_PtrA = 0x005754d8;
  P17_ValA = 2;
  P17_Const6 = 6;
  if (P17_Cond1 != 0 && P17_Cond2 == 0) P17_Dst = 200; else P17_Dst = P17_Src;
}
