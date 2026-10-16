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

static inline uint32_t rd32(const uint8_t *p, int o) { uint32_t v; memcpy(&v, p + o, 4); return v; }
static inline void wr32(uint8_t *p, int o, uint32_t v) { memcpy(p + o, &v, 4); }
static inline uint16_t rd16(const uint8_t *p, int o) { uint16_t v; memcpy(&v, p + o, 2); return v; }

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

int32_t P51_PrefixMatch(const char *line, const char *word) {
  size_t n = strlen(word);
  while (*line == ' ' || *line == '\r' || *line == '\n' || *line == '\t') line++;
  while (n != 0) {
    n--;
    if (line[n] != word[n]) return 0;
  }
  return 1;
}

char *P51_SkipToLine(char *p, const char *word) {
  for (;;) {
    int32_t r = P51_PrefixMatch(p, word);
    p = SkipLine004A59C6(p);
    if (r == 1) break;
  }
  return p;
}

int32_t P51_FileSize(void *file) {
  int32_t n;
  g_fseek(file, 0, 2);
  n = (int32_t)g_ftell(file);
  g_fseek(file, 0, 0);
  return n;
}

uint8_t P51_DirFromHeading(const uint8_t *obj) {
  uint32_t b = (uint32_t)Round1024((int32_t)rd32(obj, 0x100)) & 0xff;
  if ((int32_t)rd32(obj, 0x10c) < 0) b = (b + 2) & 3;
  return (uint8_t)b;
}

void P51_InitCarSlot(uint32_t owner, uint8_t *slot, uint32_t id) {
  memset(slot, 0, 0xcd8);
  wr32(slot, 0, id);
  wr32(slot, 0xcb4, 1);
  wr32(slot, 0xcb8, 0);
  wr32(slot, 0xcbc, 1);
  wr32(slot, 0x40, 0);
  wr32(slot, 0xcd0, owner);
  wr32(slot, 0x5c, 0);
  wr32(slot, 0xcd4, 0x3f800000);
}

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

void P51_SteerHeading(uint8_t *obj, const int32_t *vec) {
  int32_t ang = P44_Atan2(vec[2], vec[0]);
  int16_t cur; uint16_t out;
  int32_t d, ad;
  memcpy(&cur, obj + 0x12, 2);
  d = (int32_t)((((uint32_t)(ang - (int32_t)cur) + 0x800u) & 0xfff)) - 0x800;
  ad = d < 0 ? -d : d;
  if (ad < 0x20) out = (uint16_t)ang;
  else if (d < 0) out = (uint16_t)(cur - 0x20);
  else out = (uint16_t)(cur + 0x20);
  memcpy(obj + 0x12, &out, 2);
}

int32_t P51_SkipNumber(char **pp) {
  int seen_dot = 0;
  if (**pp == '-') (*pp)++;
  for (;;) {
    while ((uint8_t)**pp > 0x2f && (uint8_t)**pp < 0x3a) (*pp)++;
    if (**pp == '.' && seen_dot) return 0;
    if (**pp != '.') return 1;
    (*pp)++;
    seen_dot = 1;
  }
}
