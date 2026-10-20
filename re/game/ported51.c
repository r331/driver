/* ported51 — small leaf functions (Game.exe, cdecl): pitch-jittered sound, screen-space scaling, text-script line
   parsing helpers, file size, car slot init, traffic conflict test, road-node kind and heading steering. */
#include "ported51.h"
#include "crt.h"
#include "smallfuncs2.h"
#include "uihandlers3.h"
#include "globalsets.h"
#include <string.h>
#include <stddef.h>
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P51_PitchCount")
#undef P51_PitchCount
#pragma push_macro("P51_PitchCount") /*gvi*/
#undef P51_PitchCount /*gvi*/
int32_t P51_PitchCount;
#pragma pop_macro("P51_PitchCount") /*gvi*/
#pragma pop_macro("P51_PitchCount")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P51_Half")
#undef P51_Half
#pragma push_macro("P51_Half") /*gvi*/
#undef P51_Half /*gvi*/
float P51_Half;
#pragma pop_macro("P51_Half") /*gvi*/
#pragma pop_macro("P51_Half")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P51_TrafficN")
#undef P51_TrafficN
#pragma push_macro("P51_TrafficN") /*gvi*/
#undef P51_TrafficN /*gvi*/
int32_t P51_TrafficN;
#pragma pop_macro("P51_TrafficN") /*gvi*/
#pragma pop_macro("P51_TrafficN")
#endif
#include "ported12.h"
#include "carfields.h"

static inline uint32_t rd32(const uint8_t *p, int o) { uint32_t v; memcpy(&v, p + o, 4); return v; }
static inline void wr32(uint8_t *p, int o, uint32_t v) { memcpy(p + o, &v, 4); }
static inline uint16_t rd16(const uint8_t *p, int o) { uint16_t v; memcpy(&v, p + o, 2); return v; }

/* P51_PitchJitterSfx — Game.exe 004d69ed.  Countdown P51_PitchCount: -1 = off; on reaching 0 plays sound 0x16
   with pitch 16000 +- 0x1000 (random); then counts on down to -1 (so it plays exactly once). */
void P51_PitchJitterSfx(void) {
  int16_t base = 16000;
  if (P51_PitchCount != -1) {
    if (P51_PitchCount == 0) {
      uint32_t r = N14_Rand();
      base = (int16_t)(base + (int32_t)((r & 0x1fff) - 0x1000));
      UiCall00523E50(0x16, -1, (int32_t)base);
    }
    P51_PitchCount = P51_PitchCount - 1;
  }
}

/* P51_ScalePair — Game.exe 004d8487.  Maps a point in 640x480 units to the screen with a zoom about the centre:
   v' = ((v / 640|480 - 0.5) * P19_Scale + 0.5) * screen size.  Intermediates are rounded to float exactly where
   the original stores them. */
void P51_ScalePair(float *x, float *y) {
  /* x87: цепочка fld/fsub/fmul/fadd идёт в расширенной точности, в float сохраняется только результат шага */
  float a = (float)((long double)*x / (long double)P19_DivW);
  float b = (float)((long double)*y / (long double)P19_DivH);
  a = (float)((((long double)a - P51_Half) * P19_Scale) + P51_Half);
  b = (float)((((long double)b - P51_Half) * P19_Scale) + P51_Half);
  a = (float)((long double)a * (float)P19_ScrW);
  b = (float)((long double)b * (float)P19_ScrH);
  *x = a; *y = b;
}

/* P51_PrefixMatch — Game.exe 004a59f2.  After skipping leading blanks (space, CR, LF, tab), does line start with
   word?  1 / 0.  Compares from the last character backwards, like the original. */
int32_t P51_PrefixMatch(const char *line, const char *word) {
  size_t n = strlen(word);
  while (*line == ' ' || *line == '\r' || *line == '\n' || *line == '\t') line++;
  while (n != 0) {
    n--;
    if (line[n] != word[n]) return 0;
  }
  return 1;
}

/* P51_SkipToLine — Game.exe 004a5a83.  Advances line by line until a line starting with word has been passed;
   returns the start of the line after it.  Loops forever if word never occurs (as the original). */
char *P51_SkipToLine(char *p, const char *word) {
  for (;;) {
    int32_t matched = P51_PrefixMatch(p, word);
    p = SkipLine004A59C6(p);
    if (matched == 1) break;
  }
  return p;
}

/* P51_FileSize — Game.exe 004d3000.  Size of an open file: fseek(END), ftell, fseek(SET 0). */
int32_t P51_FileSize(void *file) {
  int32_t n;
  g_fseek(file, 0, 2);
  n = (int32_t)g_ftell(file);
  g_fseek(file, 0, 0);
  return n;
}

/* P51_DirFromHeading — Game.exe 004a63c6.  Road direction 0..3 (90-degree steps) of a car: its heading rounded to
   the nearest 1024 (Round1024 returns the step), low byte; flipped by 180 degrees ((dir + 2) & 3) when the car
   moves backwards (signed forward speed < 0).  TODO(RE): unsure — when not reversing the result is not masked
   with & 3 (kept literally). */
uint8_t P51_DirFromHeading(const uint8_t *obj) {
  uint32_t dir = (uint32_t)Round1024((int32_t)rd32(obj, CAR_HEADING)) & 0xff;
  if ((int32_t)rd32(obj, CAR_FWD_SPEED) < 0) dir = (dir + 2) & 3;
  return (uint8_t)dir;
}

/* Car object slot (0xcd8 bytes; not the 0x148 car record of carfields.h).  Only the fields set here are named. */
#define SLOT_SIZE      0xcd8
#define SLOT_ID        0x000   /* u32 id */
#define SLOT_F40       0x040   /* TODO(RE): unsure */
#define SLOT_F5C       0x05c   /* TODO(RE): unsure */
#define SLOT_FCB4      0xcb4   /* cleared by P91_ReleaseTraffic; TODO(RE): unsure (1 = active?) */
#define SLOT_FCB8      0xcb8   /* TODO(RE): unsure */
#define SLOT_FCBC      0xcbc   /* TODO(RE): unsure */
#define SLOT_OWNER     0xcd0   /* pointer to the owning traffic record's id byte (see P91_ReleaseTraffic) */
#define SLOT_SCALE     0xcd4   /* float, initialised to 1.0f (0x3f800000); TODO(RE): unsure what it scales */

/* P51_InitCarSlot — Game.exe 00491928.  Zeroes a car object slot and sets its id, owner pointer and defaults. */
void P51_InitCarSlot(uint32_t owner, uint8_t *slot, uint32_t id) {
  memset(slot, 0, SLOT_SIZE);
  wr32(slot, SLOT_ID, id);
  wr32(slot, SLOT_FCB4, 1);
  wr32(slot, SLOT_FCB8, 0);
  wr32(slot, SLOT_FCBC, 1);
  wr32(slot, SLOT_F40, 0);
  wr32(slot, SLOT_OWNER, owner);
  wr32(slot, SLOT_F5C, 0);
  wr32(slot, SLOT_SCALE, 0x3f800000);   /* 1.0f */
}

/* P51_TrafficConflict — Game.exe 0048eb25.  Scans the P51_TrafficN traffic records (0x54 bytes, P12_011443e0) for
   another active record (byte +8 set, id byte +0 != self) that conflicts with a planned move: same field +0x28
   as a and same direction (+0x24) as the low byte of b, or (byte +3 set) +0x20 == c and +0x2c == a.
   Returns 1 on conflict, 0 otherwise.  TODO(RE): unsure — +0x20 is the road node (see rd_store in
   ported103.c); +0x28/+0x2c look like the current / next road segment. */
int32_t P51_TrafficConflict(uint32_t self, int32_t a, uint32_t b, int32_t c) {
  const uint8_t *e = P12_011443e0;
  for (int32_t i = 0; i < P51_TrafficN; i++, e += 0x54) {
    if (e[8] != 0 && (uint32_t)e[0] != self) {
      if ((int32_t)rd32(e, 0x28) == a) {
        if (rd32(e, 0x24) == (b & 0xff)) return 1;
      } else if (e[3] != 0 && (int32_t)rd32(e, 0x20) == c && (int32_t)rd32(e, 0x2c) == a) {
        return 1;
      }
    }
  }
  return 0;
}

/* P51_NodeKind — Game.exe 0048f7fe.  Classifies a traffic record by the road it is on (record +0x20 indexes
   P51_Tab1ED80, 0x2c-byte entries, byte +3 = blocked):  0 = blocked road or nothing special;  1 = +0x34 == 1 or
   flag bit 0 of +0xe;  with flag bit 2: 3 when the signal byte for its axis (G00C29D80, or G00C29D81 when
   direction +0x24 is odd) is 3, else 2 unless byte +3 is set.  TODO(RE): unsure — looks like a traffic-light
   state (3 = red?). */
int32_t P51_NodeKind(const uint8_t *node) {
  if (P51_Tab1ED80[3 + (int32_t)rd32(node, 0x20) * 0x2c] != 0) return 0;
  if ((int32_t)rd32(node, 0x34) == 1) return 1;
  if ((rd16(node, 0xe) & 1) != 0) return 1;
  if ((rd16(node, 0xe) & 4) != 0) {
    uint8_t c = G00C29D80;
    if ((rd32(node, 0x24) & 1) != 0) c = G00C29D81;
    if (c == 3) return 3;
    if (node[3] == 0) return 2;
  }
  return 0;
}

/* P51_SteerHeading — Game.exe 004d0071.  Turns the int16 heading at obj+0x12 towards the angle of vec (x = vec[0],
   z = vec[2]) by at most 0x20 (~2.8 degrees) per call; snaps when closer than that.  The difference is wrapped
   to -0x800..0x7ff (half a turn). */
void P51_SteerHeading(uint8_t *obj, const int32_t *vec) {
  int32_t ang = P44_Atan2(vec[2], vec[0]);
  int16_t cur; uint16_t out;
  int32_t d, ad;   /* d = signed angle difference, ad = |d| */
  memcpy(&cur, obj + 0x12, 2);
  d = (int32_t)((((uint32_t)(ang - (int32_t)cur) + 0x800u) & 0xfff)) - 0x800;
  ad = d < 0 ? -d : d;
  if (ad < 0x20) out = (uint16_t)ang;
  else if (d < 0) out = (uint16_t)(cur - 0x20);
  else out = (uint16_t)(cur + 0x20);
  memcpy(obj + 0x12, &out, 2);
}

/* P51_SkipNumber — Game.exe 004a50f7.  Skips a number [-]digits[.digits] at *pp.  Returns 1 when the number
   ended normally, 0 on a second decimal point (left pointing at it). */
int32_t P51_SkipNumber(char **pp) {
  int seen_dot = 0;
  if (**pp == '-') (*pp)++;
  for (;;) {
    while ((uint8_t)**pp > 0x2f && (uint8_t)**pp < 0x3a) (*pp)++;   /* '0'..'9' */
    if (**pp == '.' && seen_dot) return 0;
    if (**pp != '.') return 1;
    (*pp)++;
    seen_dot = 1;
  }
}
