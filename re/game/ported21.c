#include "ported21.h"
#include <string.h>
GAME_VAR_DEF(int32_t, P21_GridDiv, 0x00562d38)
GAME_VAR_DEF(int32_t, P21_GridRadius, 0x00cf56b8)
GAME_VAR_DEF(int32_t, P21_GridStride, 0x00d00258)
GAME_VAR_DEF(int32_t, P21_AxisValue, 0x00b31e20)
GAME_VAR_DEF(int32_t, P21_EntryCount, 0x00575ee4)
#ifndef RE_HOOK_BUILD
uint8_t P21_AxisOut[256], P21_AxisSrc[256], P21_Entries[0x54 * 64];
#endif

int32_t P21_GridCellSet(int32_t idx, const uint8_t* map, int32_t cx, int32_t cy) {
  int32_t dx = idx % P21_GridDiv - cx;
  int32_t dy = idx / P21_GridDiv - cy;
  if ((dx < 0 ? -dx : dx) > P21_GridRadius) return 0;
  if ((dy < 0 ? -dy : dy) > P21_GridRadius) return 0;
  return map[dx + 0xf + (dy + 0xf) * P21_GridStride] != 0;
}

uint32_t P21_AddMsf(uint32_t a, uint32_t b) {
  int32_t m = (int32_t)(a & 0xff) + (int32_t)(b & 0xff);
  int32_t s = (int32_t)(a & 0xffff) / 256 + (int32_t)(b & 0xffff) / 256;
  int32_t f = (int32_t)((a >> 16) & 0xff) + (int32_t)((b >> 16) & 0xff);
  if (f > 0x4a) { s++; f -= 0x4b; }
  if (s > 0x3b) { m++; s -= 0x3c; }
  return (uint32_t)(m & 0xff) | ((uint32_t)(s & 0xffff) << 8) | ((uint32_t)(f & 0xff) << 16);
}

void P21_SetAxisByte(uint8_t kind, uint32_t slot) {
  uint8_t* out = &P21_AxisOut[slot & 0xff];
  if (kind == 0x20) *out = (P21_AxisValue < -0xe) ? 0x80 : 0;
  else if (kind == 0x21) *out = (P21_AxisValue < 0xf) ? 0 : 0x80;
  else if (kind == 0x22) *out = 0;
  else *out = P21_AxisSrc[kind];
}

int32_t P21_CountActiveEntries(int32_t owner) {
  int32_t n = 0;
  const uint8_t* e = P21_Entries;
  for (int32_t i = 0; i < P21_EntryCount; i++, e += P21_ENTRY_SIZE) {
    int32_t o; memcpy(&o, e + 0x28, 4);
    if (o == owner && (e[1] == 1 || (e[0x13] & 0x10) || (e[0x13] & 0x20) || (e[0x13] & 8))) n++;
  }
  return n;
}

uint32_t P21_MatchPrefix(const uint8_t* s, const uint8_t* prefix) {
  uint32_t len = (uint32_t)strlen((const char*)prefix);
  uint32_t left = len;
  if (!len) return 0;
  for (;;) {
    if (left == 0) {
      if ((*s > 0x5a || *s < 0x41) && *s != 0x5f) return len;
      return 0;
    }
    uint8_t x = *s++, y = *prefix++;
    left--;
    if (x != y) return 0;
  }
}

#ifndef RE_HOOK_BUILD
const char* P21_NameTable[0x23];
const char* P21_ErrorName = "Error";
#endif
const char* P21_GetNameByIndex(uint8_t idx) {
  return idx < 0x23 ? P21_NameTable[idx] : P21_ErrorName;
}
