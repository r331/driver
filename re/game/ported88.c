/* Положение камеры в сетке блоков карты и подгрузка соседей — восстановлено из Game.exe (004edd08, 004edaa2). */
#include "ported88.h"
#include <string.h>

GAME_VAR_DEF(p88_cell_t, P88_CellA, 0x00c97a00)
GAME_VAR_DEF(p88_cell_t, P88_CellB, 0x00cff9a0)
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P88_Mode575")
#undef P88_Mode575
#pragma push_macro("P88_Mode575") /*gvi*/
#undef P88_Mode575 /*gvi*/
int32_t P88_Mode575;
#pragma pop_macro("P88_Mode575") /*gvi*/
#pragma pop_macro("P88_Mode575")
#endif

/* заполнить описатель по координатам блока карты */
static void fill(p88_cell_t *c, int32_t x, int32_t y) {
  int32_t n = P54_GridN, div = P21_GridDiv;
  c->x = x; c->y = y;
  c->idx = x + y * div;
  c->cx = x / n; c->cy = y / n;
  c->prev = c->cell;
  c->cell = c->cx + c->cy * (div / n);
  c->px = (uint8_t)(c->cx & 1); c->py = (uint8_t)(c->cy & 1);
  c->pc = (uint8_t)(c->px + c->py * 2);
  c->rx = x - c->cx * n; c->ry = y - c->cy * n;
}

/* выбор соседних блоков по описателю (логика 004edaa2); возвращает число 0..3, lump[i] — номер блока, slot[i] — слот */
int32_t P88_PickTiles(const p88_cell_t *b, int32_t *lump, int32_t *slot) {
  int32_t dx[3], dy[3], n = 0, fa = 0, fb = 0;
  int32_t gn = P54_GridN, row;
  if (gn <= 0) return 0;                                /* охранная проверка — в оригинале деления на ноль не избегают */
  row = P21_GridDiv / gn;
  if (b->rx < 0x14) { if (b->cx != 0) { dx[n] = -1; dy[n] = 0; n++; fa = 1; } }
  else if (b->rx > gn - 0x14 && b->cx < row) { dx[n] = 1; dy[n] = 0; n++; fa = 2; }
  if (b->ry < 0x14) { if (b->cy != 0) { dx[n] = 0; dy[n] = -1; n++; fb = 1; } }
  else if (b->ry > gn - 0x14 && b->cy != 0) { dx[n] = 0; dy[n] = 1; n++; fb = 2; }   /* sic: cy != 0, как в оригинале */
  if (n == 2) {
    if (fb == 1) { dx[2] = fa == 1 ? -1 : 1; dy[2] = -1; }
    else         { dx[2] = fa == 1 ? -1 : 1; dy[2] = 1; }
    n = 3;
  }
  for (int i = 0; i < n; i++) {
    lump[i] = b->cell + dx[i] + dy[i] * row;
    slot[i] = ((b->cx + dx[i]) & 1) + ((b->cy + dy[i]) & 1) * 2;
  }
  return n;
}

/* 004edaa2 */
void P88_StreamTiles(void) {
  int32_t lump[3], slot[3], n = P88_PickTiles(&P88_CellB, lump, slot);
  for (int i = 0; i < n; i++)
    if (lump[i] != P87_SlotLumpA[0] && lump[i] != P87_SlotLumpA[1] && lump[i] != P87_SlotLumpA[2] && lump[i] != P87_SlotLumpA[3])
      P87_LoadTile(lump[i], slot[i]);
}

/* 004edd08 */
void P88_CellUpdate(int32_t mode) {
  if (mode != 0) { P12_Fn00489ED6(); return; }
  if (P54_GridN <= 0 || P21_GridDiv <= 0) return;      /* охранная проверка */
  {
    float fx = (P44_CamX + (float)P42_CellX) * P42_CellScale;
    float fy = (P44_CamZ + (float)P42_CellY) * P42_CellScale;
    fill(&P88_CellA, (int32_t)fx, (int32_t)fy);
  }
  if (G6_00B87EEC != 0) {
    P88_CellB = P88_CellA;
  } else {
    float fx, fy;
    if (P14_00b87ee4 != 0) {
      fx = (P44_CamX + (float)P42_CellX) * P42_CellScale;
      fy = (P44_CamZ + (float)P42_CellY) * P42_CellScale;
    } else if ((G6_00B87EAC != 0 || G6_00B87EB0 != 0) && !(G6_00B87EA0 != 0 && P88_Mode575 == 2)) {
      float tx = (float)(P88_ObjX + P42_CellX), ty = (float)(P88_ObjZ + P42_CellY);
      fx = tx * P42_CellScale; fy = ty * P42_CellScale;
    } else {
      float tx = (float)(P59_PosX + P42_CellX), ty = (float)(P59_PosZ + P42_CellY);
      fx = tx * P42_CellScale; fy = ty * P42_CellScale;
    }
    fill(&P88_CellB, (int32_t)fx, (int32_t)fy);
  }
  P12_00cff9ac = P88_CellB.cell;                       /* в native 00cff9ac — отдельная переменная P12 */
  P88_StreamTiles();
}
