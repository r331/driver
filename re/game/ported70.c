#include "ported70.h"
#include <math.h>
#include <stdio.h>
#include <string.h>

static int32_t rd32(const uint8_t *p, uint32_t o) { int32_t v; memcpy(&v, p + o, 4); return v; }
static void    wr32(uint8_t *p, uint32_t o, int32_t v) { memcpy(p + o, &v, 4); }
static float   rdf(const uint8_t *p, uint32_t o) { float v; memcpy(&v, p + o, 4); return v; }

#define P70_PARTS 64
#define P70_PSIZE 0xb4

/* __ftol / fistp: округление к ближайшему чётному, как fistp в режиме по умолчанию */
static int32_t Rnd(float v) { return (int32_t)lrintf(v); }

static void spawn_variant(uint8_t *p, int32_t kind) {
  int32_t a = Rnd(rdf(p, 0x8c));
  int32_t b = Rnd(rdf(p, 0x84));
  int32_t r = P61_Fn5139D7(0, b, a, p + 0x94);
  if (r == 0) {
    P43_FreeSlot(p);
  } else {
    wr32(p, 0x38, r);
    P61_Fn5144D4(p, p + 0x84);
    P61_Fn514779(p, p + 0x94);
    P61_Fn514F47(p);
    P61_Fn514BC7(p, kind, 0);
  }
}

/* 00514332 */
void P70_SpawnPart4(uint8_t *p) { spawn_variant(p, 4); }
/* 00514403 */
void P70_SpawnPart2(uint8_t *p) { spawn_variant(p, 2); }

/* 00513905 */
int32_t P70_FindParticle(int32_t x, int32_t z) {
  const uint8_t *e = (const uint8_t *)A_00C56780;
  for (int32_t i = 0; i < P70_PARTS; i++, e += P70_PSIZE) {
    if ((rd32(e, 0xc) & 0x10) != 0) {
      int32_t dx = x - Rnd(rdf(e, 0x84)); if (dx < 0) dx = -dx;
      int32_t dz = z - Rnd(rdf(e, 0x8c)); if (dz < 0) dz = -dz;
      if (dx + dz < 100) return i;
    }
  }
  return -1;
}

/* 0051ab31 */
int32_t P70_RowDecode(int32_t row, int16_t *dst) {
  const uint8_t *base = (const uint8_t *)P62_MapBuf;
  int16_t n = (int16_t)((int16_t)P62_MapN * (int16_t)P62_MapN);
  int32_t off = rd32(base, 8 + (uint32_t)row * 4);
  if (off == -1) {
    for (; n != 0; n--) *dst++ = -1;
    return 0;
  }
  const uint8_t *s = base + off;
  while (n != 0) {
    int16_t cnt, val;
    memcpy(&cnt, s, 2); memcpy(&val, s + 2, 2);
    n = (int16_t)(n - cnt);
    s += 4;
    for (; cnt != 0; cnt--) *dst++ = val;
  }
  return 1;
}

/* 00406369 */
int32_t P70_ReadChunk(void *f, const char *name, int32_t tag) {
  int32_t got = 0, size = 0;
  g_fread(&got, 1, 4, f);
  if (tag != got) return 0;
  g_fread(&size, 1, 4, f);
  uint8_t *buf = (uint8_t *)DebugMalloc(size, "D:\\Driver\\Game\\frontend\\config.c", 0x254);
  if (buf == NULL) return 0;
  g_fread(buf, 1, (size_t)size, f);
  void *out = g_fopen(name, "wb");
  if (out != NULL) {
    g_fwrite(buf, 1, (size_t)size, out);
    g_fclose(out);
    DebugFree(buf);
    return 1;
  }
  DebugFree(buf);
  return 0;
}

/* 00406199 */
int32_t P70_LoadReplay(int32_t slot) {
  char name[32];
  snprintf(name, sizeof name, "SAVES\\REPLAY%d.BIN", slot + 1);
  void *f = g_fopen(name, "rb");
  if (f == NULL) return 0;
  g_fread(P59_Hdr, 1, 8, f);
  g_fread(P59_Rep57B6B8, 1, 0x38, f);
  if (P70_ReadChunk(f, "REPLAYDATA\\USER\\$TEMP$.CFG", 0x21474643) != 0 &&
      P70_ReadChunk(f, "REPLAYDATA\\USER\\$TEMP$.CAMS", 0x534d4143) != 0 &&
      P70_ReadChunk(f, "REPLAYDATA\\USER\\$TEMP$.PADS", 0x53444150) != 0) {
    g_fclose(f);
    return 1;
  }
  g_fclose(f);
  return 0;
}

/* 005170ab */
int32_t P70_FadeColor(void) {
  int32_t more = G6_00C55800 != G6_00C557F8;
  if (more && G6_00C557F8 == 0) return 0;   /* оригинал делит на ноль */
  if (more) {
    S_00B5A834 = (uint8_t)(S_00B5A834 + (int8_t)(((int32_t)(G6_00B5A838 - S_00B5A834) * G6_00C55800) / G6_00C557F8));
    S_00B5A835 = (uint8_t)(S_00B5A835 + (int8_t)(((int32_t)(G6_00B5A839 - S_00B5A835) * G6_00C55800) / G6_00C557F8));
    S_00B5A836 = (uint8_t)(S_00B5A836 + (int8_t)(((int32_t)(G6_00B5A83A - S_00B5A836) * G6_00C55800) / G6_00C557F8));
    G6_00C55800 = G6_00C55800 + 1;
  } else {
    G6Call00516EB4(G6_00B5A838, G6_00B5A839, G6_00B5A83A);
  }
  return !more;
}

/* 0051755e */
void P70_ShadowText(int32_t x, int32_t y, uint32_t txt, int32_t a, uint32_t flags, uint8_t r, uint8_t g, uint8_t b) {
  int32_t d = (a == 0) ? 2 : 3;
  G6Call00516EB4(0xff, 0xff, 0xff);
  P66_Draw5173D7((float)x, (float)y, (int32_t)txt, a, (int32_t)(flags | 0x10));
  P66_Draw5173D7((float)(x + d), (float)(y + d), (int32_t)txt, a, (int32_t)(flags | 0x10));
  G6Call00516EB4(r, g, b);
  P66_Draw5173D7((float)x, (float)y, (int32_t)txt, a, (int32_t)(flags | 4));
}

/* общий поиск: x87 считает сумму квадратов в расширенной точности и округляет до float один раз */
static int32_t nearest_obj(void) {
  int32_t best = -1;
  float bd = 0;
  for (int32_t i = 0; i < 10; i++) {
    const uint8_t *o = P58_Objs[i];
    uint32_t fl = (uint32_t)rd32(o, 0x10);
    if ((fl & 1) != 0 && (fl & 0x40) == 0) {
      float dz = (float)(rd32(o, 0x1c) - P59_PosZ);
      float dx = (float)(rd32(o, 0x14) - P59_PosX);
      float d = (float)((long double)dx * dx + (long double)dz * dz);
      if (best == -1 || d < bd) { best = i; bd = d; }
    }
  }
  return best;
}

/* 005062cc */
void P70_RadarNearest(void) { int32_t i = nearest_obj(); if (i != -1) P70_Fn5063A4(i); }
/* 0050784d */
void P70_RadarNearestB(void) { int32_t i = nearest_obj(); if (i != -1) P70_Fn507925(i); }
