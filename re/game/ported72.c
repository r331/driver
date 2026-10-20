/* Road map lookups: world (x, z) -> map cell -> quarter tile -> word/dword of the road tables
   P54_RoadA / P54_RoadB. */
#include "ported72.h"
#include "fixmath.h"

#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P72_Rows")
#undef P72_Rows
#pragma push_macro("P72_Rows") /*gvi*/
#undef P72_Rows /*gvi*/
int32_t P72_Rows;
#pragma pop_macro("P72_Rows") /*gvi*/
#pragma pop_macro("P72_Rows")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P72_Id")
#undef P72_Id
#pragma push_macro("P72_Id") /*gvi*/
#undef P72_Id /*gvi*/
uint16_t P72_Id;
#pragma pop_macro("P72_Id") /*gvi*/
#pragma pop_macro("P72_Id")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P72_Low")
#undef P72_Low
#pragma push_macro("P72_Low") /*gvi*/
#undef P72_Low /*gvi*/
int32_t P72_Low;
#pragma pop_macro("P72_Low") /*gvi*/
#pragma pop_macro("P72_Low")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P72_Dir")
#undef P72_Dir
#pragma push_macro("P72_Dir") /*gvi*/
#undef P72_Dir /*gvi*/
uint16_t P72_Dir;
#pragma pop_macro("P72_Dir") /*gvi*/
#pragma pop_macro("P72_Dir")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P72_DirTab")
#undef P72_DirTab
#pragma push_macro("P72_DirTab") /*gvi*/
#undef P72_DirTab /*gvi*/
p72_dir_t P72_DirTab;
#pragma pop_macro("P72_DirTab") /*gvi*/
#pragma pop_macro("P72_DirTab")
#endif

#define MAP_CELL_SIZE  0x5dc   /* world units per road-map cell (1500) */
#define MAP_CELL_HALF  0x2ee   /* half a cell: rounds a position to the nearest cell */
#define ROAD_ID_MASK   0x3ff   /* road id: bits 16..25 of a P54_RoadB dword */

#ifndef RE_HOOK_BUILD
/* P72_InitConsts — Native: fill the 4-entry direction table (0, 90, 180, 270 degrees in 4096 units) that lives in
   Game.exe .data. */
void P72_InitConsts(void) { P72_DirTab[0] = 0; P72_DirTab[1] = ANG_90; P72_DirTab[2] = ANG_180; P72_DirTab[3] = 0xc00 /* 270 deg */; }
#endif

/* Клетка карты → плитка и позиция в ней. 1 — клетка в карте. Деление знаковое, как idiv (отрицательный остаток < 0x5dc/2 даёт 0). */
/* tile_of — Map a world position to its road tile.
   Cell = (x + P62_MapC64 + half cell) / cell size, z the same way mirrored; the cell is split into
   P62_MapN x P62_MapN tiles; which (0..3) selects one of four table banks by the parity of the
   tile column and (flipped) row.  Division is signed like idiv (a small negative remainder gives 0).
   Out: *tx, *tz — position inside the tile, *which — bank.  Returns 1 if inside the map, else 0.
   Native: returns 0 when P62_MapN is 0 (the original divides by zero). */
static int tile_of(int32_t x, int32_t z, int32_t *tx, int32_t *tz, int32_t *which) {
  int32_t n = P62_MapN;
  int32_t cx = (int32_t)((uint32_t)x + (uint32_t)P62_MapC64 + (uint32_t)MAP_CELL_HALF) / MAP_CELL_SIZE;
  int32_t cz = (int32_t)((uint32_t)P62_Map2C40 - ((uint32_t)z - (uint32_t)MAP_CELL_HALF)) / MAP_CELL_SIZE;   /* z grows the other way in the map */
  if (cx < 0 || cx >= P54_MapB1 || cz < 0 || cz >= P54_MapB2) return 0;
  if (n == 0) return 0;                       /* в оригинале — деление на ноль */
  int32_t qx = cx / n, qz = cz / n;
  *tx = cx - qx * n;
  *tz = cz - qz * n;
  int32_t row = (int32_t)((uint32_t)P72_Rows - 1u - (uint32_t)qz);
  *which = (qx & 1) + (row & 1) * 2;
  return 1;
}

/* P72_RoadWord — Game.exe 0051b111, cdecl.  Road word (int16) at world (x, z) from bank P54_RoadA[which].
   Returns -1 outside the map, 0 if the bank is not loaded. */
int32_t P72_RoadWord(int32_t x, int32_t z) {
  int32_t tx, tz, w;
  if (!tile_of(x, z, &tx, &tz, &w)) return (int32_t)(int16_t)-1;
  const int16_t *t = (const int16_t *)P54_RoadA[w];
  if (t == NULL) return 0;
  return (int32_t)t[tz * P62_MapN + tx];
}

/* P72_RoadDword — Game.exe 0051b566, cdecl.  Road dword at world (x, z) from bank P54_RoadB[which].  Returns 0 outside the map / no bank. */
int32_t P72_RoadDword(int32_t x, int32_t z) {
  int32_t tx, tz, w;
  if (!tile_of(x, z, &tx, &tz, &w)) return 0;
  const int32_t *t = (const int32_t *)P54_RoadB[w];
  if (t == NULL) return 0;
  return t[tz * P62_MapN + tx];
}

/* P72_RoadLookup — Game.exe 0051b65a, cdecl.  Decode the road dword at world (x, z).
   Returns 1 and sets P72_Id (bits 16..25: road id), P72_Low (low 16 bits, sign-extended) and
   P72_Dir (bits 30..31 -> heading from P72_DirTab); returns 0 outside the map, without a bank or
   for an empty entry.  P72_Low is cleared first in every case.
   TODO(RE): unsure what P72_Low means (likely a node/segment index). */
int32_t P72_RoadLookup(int32_t x, int32_t z) {
  P72_Low = 0;
  int32_t tx, tz, w;
  if (!tile_of(x, z, &tx, &tz, &w)) return 0;
  const uint32_t *t = (const uint32_t *)P54_RoadB[w];
  if (t == NULL) return 0;
  uint32_t v = t[tz * P62_MapN + tx];
  if (v == 0) return 0;
  P72_Id = (uint16_t)((v >> 16) & ROAD_ID_MASK);
  P72_Low = (int32_t)(int16_t)(v & 0xffff);
  P72_Dir = P72_DirTab[v >> 30];
  return 1;
}
