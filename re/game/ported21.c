#include "ported21.h"
#include <string.h>
#include <stdio.h>
#include "../platform/plat.h"
#include "unported.h"
#include "ported19.h"
#include "uihandlers3.h"
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

#ifndef RE_HOOK_BUILD
char P21_ClockBuf[32];
#endif
void P21_DrawClock(void) {
  int h, m, s;
  if (G00B87E7C != 0) return;
  plat_local_hms(&h, &m, &s);
  snprintf(P21_ClockBuf, 32, "%02d:%02d:%02d", h, m, s);
  int32_t y = (P19_ScrH + ((P19_ScrH >> 31) & 7)) / 8 - 1;
  int32_t x = (P19_ScrW + ((P19_ScrW >> 31) & 7)) / 8 - (int32_t)strlen(P21_ClockBuf);
  Call004D94B7((uint32_t)x, (uint32_t)y);
  Call004D90F4((int32_t)(intptr_t)P21_ClockBuf);
}

#ifndef RE_HOOK_BUILD
uint32_t P21_FpsLast, P21_FpsVal; int32_t P21_FpsCnt;
#endif
void P21_DrawFps(void) {
  char buf[32];
  if (G00B87E7C != 0) return;
  P21_FpsCnt++;
  uint32_t t = plat_time_ms();
  if (t - P21_FpsLast > 1000) {
    P21_FpsVal = (uint32_t)(P21_FpsCnt * 1000) / (t - P21_FpsLast);
    P21_FpsLast = plat_time_ms();
    P21_FpsCnt = 0;
  }
  int32_t y = (P19_ScrH + ((P19_ScrH >> 31) & 7)) / 8 - 1;
  snprintf(buf, sizeof buf, "%dfps", (int)P21_FpsVal);
  Call004D94B7(0, (uint32_t)y);
  Call004D90F4((int32_t)(intptr_t)buf);
}

GAME_VAR_DEF(int32_t, P21_FrameFlagA, 0x00575f38)
GAME_VAR_DEF(int32_t, P21_FrameFlagB, 0x00575f34)
GAME_VAR_DEF(int32_t, P21_FrameMin, 0x00575eec)
GAME_VAR_DEF(uint32_t, P21_FrameBase, 0x00b2c3a0)
GAME_VAR_DEF(int32_t, P21_FrameTotal, 0x00b87e78)
uint32_t P21_FrameTicks(void) {
  uint32_t n = 0, r;
  Call00522323();
  if (P21_FrameFlagA == 0) {
    if (P21_FrameFlagB == 0) { P21_FrameTotal++; return 1; }
    while (n < (uint32_t)P21_FrameMin) n = (plat_time_ms() - P21_FrameBase) / 20;
  } else {
    while (n == 0) n = (plat_time_ms() - P21_FrameBase) / 20;
  }
  P21_FrameBase += n * 20;
  r = n < 11 ? n : 10;
  P21_FrameTotal += (int32_t)r;
  return r;
}

#ifndef RE_HOOK_BUILD
uint32_t P21_Fps2Last, P21_Fps2Val; int32_t P21_Fps2Cnt;
uint8_t P21_Font8[256 * 8];
#endif
void P21_FpsToBuf(uint8_t* dst, uint8_t fg, uint8_t bg) {
  char txt[32];
  P21_Fps2Cnt++;
  uint32_t t = plat_time_ms();
  if (t - P21_Fps2Last > 1000) {
    P21_Fps2Val = (uint32_t)(P21_Fps2Cnt * 1000) / (t - P21_Fps2Last);
    P21_Fps2Last = plat_time_ms();
    P21_Fps2Cnt = 0;
  }
  snprintf(txt, sizeof txt, "%dfps", (int)P21_Fps2Val);
  for (const uint8_t* p = (const uint8_t*)txt; *p; p++) {
    uint8_t c = *p;
    if (c > 0x60 && c < 0x7b) c = (uint8_t)(c + 0xa0);
    uint8_t* q = dst;
    for (int row = 0; row < 8; row++) {
      uint8_t bits = P21_Font8[c * 8 + row];
      for (int col = 0; col < 8; col++) {
        *q++ = (bits & 0x80) ? fg : bg;
        bits = (uint8_t)(bits << 1);
      }
      q += 0x278;
    }
    dst += 8;
  }
}
