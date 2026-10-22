/* ported88.c — where the camera is in the grid of map tiles, and streaming of neighbouring tiles
   (English overview; original notes follow).
   A p88_cell_t describes one position: x, y in grid units, the tile it falls in (cx, cy = x/N, y/N with
   N = P54_GridN), the offset inside that tile (rx, ry), linear indices and the tile parities that pick one
   of the 4 tile slots.  P88_CellA follows the camera; P88_CellB is the "streaming source" (camera, a
   tracked object, or the player's car).  When B comes within P88_EDGE_MARGIN of a tile edge, up to three
   neighbouring tiles (side, other side and the corner between them) are loaded. */
/* Положение камеры в сетке блоков карты и подгрузка соседей — восстановлено из Game.exe (004edd08, 004edaa2). */
#include "ported88.h"
#include <string.h>
#include "ported55.h"

/* Distance from a tile edge (in the same grid units as rx/ry) below which the neighbouring tile is streamed in. */
#define P88_EDGE_MARGIN 0x14
#ifndef RE_HOOK_BUILD
int P88_TeleportReload;   /* v2.29: отладка переноса */
#endif

#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P88_CellA")
#undef P88_CellA
#pragma push_macro("P88_CellA") /*gvi*/
#undef P88_CellA /*gvi*/
p88_cell_t P88_CellA;
#pragma pop_macro("P88_CellA") /*gvi*/
#pragma pop_macro("P88_CellA")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P88_CellB")
#undef P88_CellB
#pragma push_macro("P88_CellB") /*gvi*/
#undef P88_CellB /*gvi*/
p88_cell_t P88_CellB;
#pragma pop_macro("P88_CellB") /*gvi*/
#pragma pop_macro("P88_CellB")
#endif
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
/* fill — local helper: fills descriptor c for grid position (x, y); keeps the previous tile number in prev. */
static void fill(p88_cell_t *c, int32_t x, int32_t y) {
  int32_t tile_n = P54_GridN, grid_div = P21_GridDiv;
  c->x = x; c->y = y;
  c->idx = x + y * grid_div;
  c->cx = x / tile_n; c->cy = y / tile_n;
  c->prev = c->cell;
  c->cell = c->cx + c->cy * (grid_div / tile_n);
  c->px = (uint8_t)(c->cx & 1); c->py = (uint8_t)(c->cy & 1);
  c->pc = (uint8_t)(c->px + c->py * 2);
  c->rx = x - c->cx * tile_n; c->ry = y - c->cy * tile_n;
}

/* выбор соседних блоков по описателю (логика 004edaa2); возвращает число 0..3, lump[i] — номер блока, slot[i] — слот */
/* P88_PickTiles — native helper, no Game.exe address (the selection logic of 004edaa2, split out for the
   selftest).  Picks the neighbouring tiles that position b needs: a side neighbour when rx or ry is within
   P88_EDGE_MARGIN of a tile edge, and the diagonal one when both are.
   Out: lump[i] — tile (lump) number, slot[i] — slot 0..3 from the tile's x/y parity.  Returns the count 0..3.
   side_x / side_y: 0 = none, 1 = towards lower x/y, 2 = towards higher x/y.
   Quirk kept: the "higher y" case tests cy != 0 instead of an upper bound, as Game.exe does. */
int32_t P88_PickTiles(const p88_cell_t *b, int32_t *lump, int32_t *slot) {
  int32_t dx[3], dy[3], n = 0, side_x = 0, side_y = 0;
  int32_t tile_n = P54_GridN, tiles_per_row;
  if (tile_n <= 0) return 0;                                /* охранная проверка — в оригинале деления на ноль не избегают */
  tiles_per_row = P21_GridDiv / tile_n;
  if (b->rx < P88_EDGE_MARGIN) { if (b->cx != 0) { dx[n] = -1; dy[n] = 0; n++; side_x = 1; } }
  else if (b->rx > tile_n - P88_EDGE_MARGIN && b->cx < tiles_per_row) { dx[n] = 1; dy[n] = 0; n++; side_x = 2; }
  if (b->ry < P88_EDGE_MARGIN) { if (b->cy != 0) { dx[n] = 0; dy[n] = -1; n++; side_y = 1; } }
  else if (b->ry > tile_n - P88_EDGE_MARGIN && b->cy != 0) { dx[n] = 0; dy[n] = 1; n++; side_y = 2; }   /* sic: cy != 0, как в оригинале */
  if (n == 2) {
    if (side_y == 1) { dx[2] = side_x == 1 ? -1 : 1; dy[2] = -1; }
    else         { dx[2] = side_x == 1 ? -1 : 1; dy[2] = 1; }
    n = 3;
  }
  for (int i = 0; i < n; i++) {
    lump[i] = b->cell + dx[i] + dy[i] * tiles_per_row;
    slot[i] = ((b->cx + dx[i]) & 1) + ((b->cy + dy[i]) & 1) * 2;
  }
  return n;
}

/* 004edaa2 */
/* P88_StreamTiles — Game.exe 004edaa2, cdecl.  Loads (P87_LoadTile) each neighbouring tile of P88_CellB
   that is not already in one of the 4 slots (P87_SlotLumpA, 00d00220..2c). */
void P88_StreamTiles(void) {
  int32_t lump[3], slot[3], n = P88_PickTiles(&P88_CellB, lump, slot);
  for (int i = 0; i < n; i++)
    if (lump[i] != P87_SlotLumpA[0] && lump[i] != P87_SlotLumpA[1] && lump[i] != P87_SlotLumpA[2] && lump[i] != P87_SlotLumpA[3])
      P87_LoadTile(lump[i], slot[i]);
}

/* 004edd08 */
/* P88_CellUpdate — Game.exe 004edd08, cdecl.
   mode != 0: only marks occupied cells (00489ed6) and returns.
   mode == 0: recomputes P88_CellA from the camera ((CamX + CellX) * CellScale, truncated like __ftol) and
   P88_CellB from the streaming source: a copy of A when 00b87eec is set; otherwise the camera during a
   scripted camera (00b87ee4), the object at 00d0cbd0/d8 when 00b87eac/00b87eb0 are set (except in mode 2
   of 00575efc with 00b87ea0), or the player's car.  Stores B's tile in 00cff9ac and streams neighbours.
   Side effects: P88_CellA/B, P12_00cff9ac, tile loads.  Native: P88_TeleportReload (debug teleport) reloads
   all tiles around the new place instead. */
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
#ifndef RE_HOOK_BUILD
  if (P88_TeleportReload) {   /* v2.29: после отладочного переноса машины (RE_TELEPORT/RE_AUTOTARGET) — блоки вокруг нового места,
                                 как команда скрипта 0x8e (004ee129: слоты сброшены, текущий блок + соседи); в игре без отладки не ставится */
    P88_TeleportReload = 0; P55_ResetSel(); return;
  }
#endif
  P88_StreamTiles();
}
