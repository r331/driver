#include "ported72.h"

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

#ifndef RE_HOOK_BUILD
void P72_InitConsts(void) { P72_DirTab[0] = 0; P72_DirTab[1] = 0x400; P72_DirTab[2] = 0x800; P72_DirTab[3] = 0xc00; }
#endif

/* Клетка карты → плитка и позиция в ней. 1 — клетка в карте. Деление знаковое, как idiv (отрицательный остаток < 0x5dc/2 даёт 0). */
static int tile_of(int32_t x, int32_t z, int32_t *tx, int32_t *tz, int32_t *which) {
  int32_t n = P62_MapN;
  int32_t cx = (int32_t)((uint32_t)x + (uint32_t)P62_MapC64 + 0x2eeu) / 0x5dc;
  int32_t cz = (int32_t)((uint32_t)P62_Map2C40 - ((uint32_t)z - 0x2eeu)) / 0x5dc;
  if (cx < 0 || cx >= P54_MapB1 || cz < 0 || cz >= P54_MapB2) return 0;
  if (n == 0) return 0;                       /* в оригинале — деление на ноль */
  int32_t qx = cx / n, qz = cz / n;
  *tx = cx - qx * n;
  *tz = cz - qz * n;
  int32_t row = (int32_t)((uint32_t)P72_Rows - 1u - (uint32_t)qz);
  *which = (qx & 1) + (row & 1) * 2;
  return 1;
}

/* 0051b111 */
int32_t P72_RoadWord(int32_t x, int32_t z) {
  int32_t tx, tz, w;
  if (!tile_of(x, z, &tx, &tz, &w)) return (int32_t)(int16_t)-1;
  const int16_t *t = (const int16_t *)P54_RoadA[w];
  if (t == NULL) return 0;
  return (int32_t)t[tz * P62_MapN + tx];
}

/* 0051b566 */
int32_t P72_RoadDword(int32_t x, int32_t z) {
  int32_t tx, tz, w;
  if (!tile_of(x, z, &tx, &tz, &w)) return 0;
  const int32_t *t = (const int32_t *)P54_RoadB[w];
  if (t == NULL) return 0;
  return t[tz * P62_MapN + tx];
}

/* 0051b65a */
int32_t P72_RoadLookup(int32_t x, int32_t z) {
  P72_Low = 0;
  int32_t tx, tz, w;
  if (!tile_of(x, z, &tx, &tz, &w)) return 0;
  const uint32_t *t = (const uint32_t *)P54_RoadB[w];
  if (t == NULL) return 0;
  uint32_t v = t[tz * P62_MapN + tx];
  if (v == 0) return 0;
  P72_Id = (uint16_t)((v >> 16) & 0x3ff);
  P72_Low = (int32_t)(int16_t)(v & 0xffff);
  P72_Dir = P72_DirTab[v >> 30];
  return 1;
}
