/* ported21 — small helpers (Game.exe, cdecl): map-grid cell test, CD MSF time addition, input axis bytes,
   traffic-record count, identifier prefix match, name table lookup, on-screen clock / FPS text, 50 Hz frame
   tick counter and an 8x8-font FPS blitter. */
#include "ported21.h"
#include <string.h>
#include <stdio.h>
#include "../platform/plat.h"
#include "unported.h"
#include "ported19.h"
#include "uihandlers3.h"
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P21_GridDiv")
#undef P21_GridDiv
#pragma push_macro("P21_GridDiv") /*gvi*/
#undef P21_GridDiv /*gvi*/
int32_t P21_GridDiv;
#pragma pop_macro("P21_GridDiv") /*gvi*/
#pragma pop_macro("P21_GridDiv")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P21_GridRadius")
#undef P21_GridRadius
#pragma push_macro("P21_GridRadius") /*gvi*/
#undef P21_GridRadius /*gvi*/
int32_t P21_GridRadius;
#pragma pop_macro("P21_GridRadius") /*gvi*/
#pragma pop_macro("P21_GridRadius")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P21_GridStride")
#undef P21_GridStride
#pragma push_macro("P21_GridStride") /*gvi*/
#undef P21_GridStride /*gvi*/
int32_t P21_GridStride;
#pragma pop_macro("P21_GridStride") /*gvi*/
#pragma pop_macro("P21_GridStride")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P21_AxisValue")
#undef P21_AxisValue
#pragma push_macro("P21_AxisValue") /*gvi*/
#undef P21_AxisValue /*gvi*/
int32_t P21_AxisValue;
#pragma pop_macro("P21_AxisValue") /*gvi*/
#pragma pop_macro("P21_AxisValue")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P21_EntryCount")
#undef P21_EntryCount
#pragma push_macro("P21_EntryCount") /*gvi*/
#undef P21_EntryCount /*gvi*/
int32_t P21_EntryCount;
#pragma pop_macro("P21_EntryCount") /*gvi*/
#pragma pop_macro("P21_EntryCount")
#endif
#ifndef RE_HOOK_BUILD
uint8_t P21_AxisSrc[256];   /* v2.03: P21_AxisOut — A_00D04B00 (ported21.h) */
#endif

/* P21_GridCellSet — Game.exe 004ecfbd.  Is grid cell idx (row-major, P21_GridDiv per row) set in the visibility
   map centred on cell (cx, cy)?  0 when it is more than P21_GridRadius cells away on either axis; otherwise the
   byte map[(dx + 15) + (dy + 15) * P21_GridStride] != 0 (the map is centred at offset 15, i.e. 31 cells wide —
   presumably the 31x31 FRUSTRUM.DAT window).  idx % / is C truncation, as the original idiv. */
int32_t P21_GridCellSet(int32_t idx, const uint8_t* map, int32_t cx, int32_t cy) {
  int32_t dx = idx % P21_GridDiv - cx;
  int32_t dy = idx / P21_GridDiv - cy;
  if ((dx < 0 ? -dx : dx) > P21_GridRadius) return 0;
  if ((dy < 0 ? -dy : dy) > P21_GridRadius) return 0;
  return map[dx + 0xf + (dy + 0xf) * P21_GridStride] != 0;
}

#define MSF_FRAMES  75     /* CD frames per second */
#define MSF_SECONDS 60

/* P21_AddMsf — Game.exe 005250cb.  Adds two CD positions in MCI MSF format (byte 0 minutes, byte 1 seconds,
   byte 2 frames; 75 frames per second, 60 seconds per minute) with carry.  Seconds are taken as (v & 0xffff) / 256
   and written back as a 16-bit field, exactly as the original. */
uint32_t P21_AddMsf(uint32_t a, uint32_t b) {
  int32_t m = (int32_t)(a & 0xff) + (int32_t)(b & 0xff);                       /* minutes */
  int32_t s = (int32_t)(a & 0xffff) / 256 + (int32_t)(b & 0xffff) / 256;       /* seconds */
  int32_t f = (int32_t)((a >> 16) & 0xff) + (int32_t)((b >> 16) & 0xff);       /* frames */
  if (f > MSF_FRAMES - 1) { s++; f -= MSF_FRAMES; }
  if (s > MSF_SECONDS - 1) { m++; s -= MSF_SECONDS; }
  return (uint32_t)(m & 0xff) | ((uint32_t)(s & 0xffff) << 8) | ((uint32_t)(f & 0xff) << 16);
}

/* Pseudo key codes of P21_SetAxisByte: analog axis below / above the dead zone, and "never pressed". */
#define AXKEY_NEG   0x20   /* pressed (0x80) while P21_AxisValue < -14 */
#define AXKEY_POS   0x21   /* pressed while P21_AxisValue >= 15 */
#define AXKEY_NONE  0x22   /* always released */
#define KEY_DOWN    0x80   /* DirectInput "key down" bit */

/* P21_SetAxisByte — Game.exe 004e43b7.  Writes the state byte of input slot (low byte) in the key block
   P21_AxisOut: for kind 0x20/0x21 from the analog axis P21_AxisValue (dead zone -14..14), 0 for 0x22, otherwise
   copied from the DirectInput key state P21_AxisSrc[kind]. */
void P21_SetAxisByte(uint8_t kind, uint32_t slot) {
  uint8_t* out = &P21_AxisOut[slot & 0xff];
  if (kind == AXKEY_NEG) *out = (P21_AxisValue < -0xe) ? KEY_DOWN : 0;
  else if (kind == AXKEY_POS) *out = (P21_AxisValue < 0xf) ? 0 : KEY_DOWN;
  else if (kind == AXKEY_NONE) *out = 0;
  else *out = P21_AxisSrc[kind];
}

/* P21_CountActiveEntries — Game.exe 0049509a.  Number of traffic records (0x54 bytes) whose field +0x28 equals
   owner and that are active: byte +1 == 1, or any of flags 0x08 / 0x10 / 0x20 in byte +0x13.
   TODO(RE): unsure what +0x28 and the flags mean (the same +0x28 appears in P51_TrafficConflict). */
int32_t P21_CountActiveEntries(int32_t owner) {
  int32_t n = 0;
  const uint8_t* e = P21_Entries;
  for (int32_t i = 0; i < P21_EntryCount; i++, e += P21_ENTRY_SIZE) {
    int32_t o; memcpy(&o, e + 0x28, 4);
    if (o == owner && (e[1] == 1 || (e[0x13] & 0x10) || (e[0x13] & 0x20) || (e[0x13] & 8))) n++;
  }
  return n;
}

/* P21_MatchPrefix — Game.exe 004a519a.  Does s start with the whole word prefix?  Returns strlen(prefix) when it
   does and the next character of s is not 'A'..'Z' or '_' (word boundary; lowercase letters and digits do not
   stop a match, as in the original), else 0.  Empty prefix -> 0. */
uint32_t P21_MatchPrefix(const uint8_t* s, const uint8_t* prefix) {
  uint32_t len = (uint32_t)strlen((const char*)prefix);
  uint32_t left = len;
  if (!len) return 0;
  for (;;) {
    if (left == 0) {
      if ((*s > 0x5a || *s < 0x41) && *s != 0x5f) return len;   /* not 'A'..'Z' and not '_' */
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
/* P21_GetNameByIndex — Game.exe 0040f14a.  Entry idx of a 0x23-name table (0054b410), or "Error" when out of
   range.  TODO(RE): unsure what the names are. */
const char* P21_GetNameByIndex(uint8_t idx) {
  return idx < 0x23 ? P21_NameTable[idx] : P21_ErrorName;
}

#ifndef RE_HOOK_BUILD
char P21_ClockBuf[32];
#endif
/* P21_DrawClock — Game.exe 004d986e.  Prints the local time HH:MM:SS right-aligned on the bottom text row (8x8
   character cells: rows = ScrH / 8, cols = ScrW / 8) unless G00B87E7C is set.  The "+ ((v >> 31) & 7)" terms are
   the compiler's signed-division-by-8 rounding, kept literally. */
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
/* P21_DrawFps — Game.exe 004d53e8.  Frame counter: every call counts a frame; once more than 1000 ms passed
   the rate frames * 1000 / elapsed is latched.  Prints "<n>fps" at the bottom-left text cell unless G00B87E7C. */
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

#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P21_FrameFlagA")
#undef P21_FrameFlagA
#pragma push_macro("P21_FrameFlagA") /*gvi*/
#undef P21_FrameFlagA /*gvi*/
int32_t P21_FrameFlagA;
#pragma pop_macro("P21_FrameFlagA") /*gvi*/
#pragma pop_macro("P21_FrameFlagA")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P21_FrameFlagB")
#undef P21_FrameFlagB
#pragma push_macro("P21_FrameFlagB") /*gvi*/
#undef P21_FrameFlagB /*gvi*/
int32_t P21_FrameFlagB;
#pragma pop_macro("P21_FrameFlagB") /*gvi*/
#pragma pop_macro("P21_FrameFlagB")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P21_FrameMin")
#undef P21_FrameMin
#pragma push_macro("P21_FrameMin") /*gvi*/
#undef P21_FrameMin /*gvi*/
int32_t P21_FrameMin;
#pragma pop_macro("P21_FrameMin") /*gvi*/
#pragma pop_macro("P21_FrameMin")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P21_FrameBase")
#undef P21_FrameBase
#pragma push_macro("P21_FrameBase") /*gvi*/
#undef P21_FrameBase /*gvi*/
uint32_t P21_FrameBase;
#pragma pop_macro("P21_FrameBase") /*gvi*/
#pragma pop_macro("P21_FrameBase")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P21_FrameTotal")
#undef P21_FrameTotal
#pragma push_macro("P21_FrameTotal") /*gvi*/
#undef P21_FrameTotal /*gvi*/
int32_t P21_FrameTotal;
#pragma pop_macro("P21_FrameTotal") /*gvi*/
#pragma pop_macro("P21_FrameTotal")
#endif
/* P21_FrameTicks — Game.exe 004d78f3.  Game-logic tick count for this frame at 50 Hz (20 ms per tick).
   Pumps window messages first.  With both flags clear: counts the frame and returns 1 (one tick per frame).
   With P21_FrameFlagB: waits until at least P21_FrameMin ticks elapsed; with P21_FrameFlagA: until at least 1.
   The base time advances by whole ticks; the result is capped at 10 and added to P21_FrameTotal.
   TODO(RE): unsure what the two flags select (frame lock modes?). */
uint32_t P21_FrameTicks(void) {
  uint32_t n = 0, r;   /* n = elapsed ticks, r = ticks returned (capped) */
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
/* P21_FpsToBuf — Game.exe 004bf910.  Same frame-rate counter as P21_DrawFps (own
   state), rendered with the 8x8 font P21_Font8 directly into an 8-bit buffer: fg / bg colour per pixel, 8 rows
   per glyph, row pitch 0x280 = 640 bytes (8 written + 0x278 skipped).  Lowercase 'a'..'z' are mapped to glyphs
   0x01..0x1a (c + 0xa0 wraps in a byte; the font keeps lowercase letters there). */
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
