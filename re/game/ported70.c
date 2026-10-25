/* ported70.c — nine small functions (English overview): spawning variants of a world object (types 4 and 2),
   finding an object near a position, decoding one RLE row of the map grid, reading a replay save
   (SAVES\REPLAYn.BIN) into the replay temp files, a colour fade step, text with a shadow, and picking the
   nearest mission target for the radar.  All cdecl. */
#include "ported70.h"
#include "ported43.h"   /* v2.09: P43_FreeCnt/P43_FreeList/A_00C56780 — объекты образа данных (пешеходы) */
#include "ported7.h"
#include <math.h>
#include <stdio.h>
#include <string.h>

static int32_t rd32(const uint8_t *p, uint32_t o) { int32_t v; memcpy(&v, p + o, 4); return v; }
static void    wr32(uint8_t *p, uint32_t o, int32_t v) { memcpy(p + o, &v, 4); }
static float   rdf(const uint8_t *p, uint32_t o) { float v; memcpy(&v, p + o, 4); return v; }

#define P70_PARTS 64
#define P70_PSIZE 0xb4
/* Object record (A_00C56780, P70_PARTS x 0xb4 bytes; pedestrian/world objects of P43, see ported43.h). */
#define OBJ_FLAGS 0x0c     /* bit 0x10 = in use (tested by P70_FindParticle) */
#define OBJ_KIND  0x38     /* result of P61_Fn5139D7 stored here.  TODO(RE): meaning unsure */
#define OBJ_POS_X 0x84     /* float world x */
#define OBJ_POS_Z 0x8c     /* float world z */
#define OBJ_F94   0x94     /* passed to P61_Fn5139D7 / P61_Fn514779.  TODO(RE): unknown sub-record */
/* Mission target record (P58_Objs[0..9]). */
#define TGT_FLAGS 0x10     /* bit 1 = active, bit 0x40 = excluded from the radar search */
#define TGT_X     0x14
#define TGT_Z     0x1c
/* Replay save chunk tags (four ASCII characters, little-endian). */
#define TAG_CFG  0x21474643   /* "CFG!" */
#define TAG_CAMS 0x534d4143   /* "CAMS" */
#define TAG_PADS 0x53444150   /* "PADS" */

/* __ftol / fistp: округление к ближайшему чётному, как fistp в режиме по умолчанию */
static int32_t Rnd(float v) { return (int32_t)lrintf(v); }

/* Common body of P70_SpawnPart4/2 (variants of 00514261 with a different type): asks P61_Fn5139D7 for a
   placement at the object's rounded (x, z); 0 -> the object is released (P43_FreeSlot), otherwise the result
   is stored at +0x38 and the object is set up by the P61 helpers with type `kind`.
   TODO(RE): what exactly P61_Fn5139D7 returns (model? road segment?) is not established. */
static void spawn_variant(uint8_t *p, int32_t kind) {
  int32_t a = Rnd(rdf(p, OBJ_POS_Z));
  int32_t b = Rnd(rdf(p, OBJ_POS_X));
  int32_t r = P61_Fn5139D7(0, b, a, p + OBJ_F94);
  if (r == 0) {
    P43_FreeSlot(p);
  } else {
    wr32(p, OBJ_KIND, r);
    P61_Fn5144D4(p, p + OBJ_POS_X);
    P61_Fn514779(p, p + OBJ_F94);
    P61_Fn514F47(p);
    P61_Fn514BC7(p, kind, 0);
  }
}

/* P70_SpawnPart4 — Game.exe 00514332: spawn_variant with type 4. */
void P70_SpawnPart4(uint8_t *p) { spawn_variant(p, 4); }
/* P70_SpawnPart2 — Game.exe 00514403: spawn_variant with type 2. */
void P70_SpawnPart2(uint8_t *p) { spawn_variant(p, 2); }

/* P70_FindParticle — Game.exe 00513905.  Returns the index (0..63) of the first in-use object (flag 0x10) whose
   rounded position is within Manhattan distance |dx| + |dz| < 100 of (x, z), or -1. */
int32_t P70_FindParticle(int32_t x, int32_t z) {
  const uint8_t *e = (const uint8_t *)A_00C56780;
  for (int32_t i = 0; i < P70_PARTS; i++, e += P70_PSIZE) {
    if ((rd32(e, OBJ_FLAGS) & 0x10) != 0) {
      int32_t dx = x - Rnd(rdf(e, OBJ_POS_X)); if (dx < 0) dx = -dx;
      int32_t dz = z - Rnd(rdf(e, OBJ_POS_Z)); if (dz < 0) dz = -dz;
      if (dx + dz < 100) return i;
    }
  }
  return -1;
}

/* P70_RowDecode — Game.exe 0051ab31.  Decodes row `row` of the RLE map grid P62_MapBuf into MapN*MapN s16 values.
   Buffer layout: dword table of row offsets at +8 (-1 = empty row), each row a run list of {s16 count, s16 value}.
   Returns 1, or 0 for an empty row (dst filled with -1).  The value count is kept in int16 as in the original. */
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

/* P70_ReadChunk — Game.exe 00406369.  Reads a chunk [u32 tag][u32 size][data] from the replay file f and writes the
   data to the file `name`.  Returns 1 on success, 0 if the tag differs, malloc fails or `name` cannot be created. */
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

/* P70_LoadReplay — Game.exe 00406199.  Opens SAVES\REPLAY<slot+1>.BIN, reads the 8-byte header into P59_Hdr and 0x38
   bytes into P59_Rep57B6B8, then extracts the CFG, CAMS and PADS chunks into REPLAYDATA\USER\$TEMP$.*.
   Returns 1 when all three chunks were written. */
int32_t P70_LoadReplay(int32_t slot) {
  char name[32];
  snprintf(name, sizeof name, "SAVES\\REPLAY%d.BIN", slot + 1);
  void *f = g_fopen(name, "rb");
  if (f == NULL) { RE_LOGW(save, "повтор: %s не открыт", name); return 0; }
  g_fread(P59_Hdr, 1, 8, f);
  g_fread(P59_Rep57B6B8, 1, 0x38, f);
  if (P70_ReadChunk(f, "REPLAYDATA\\USER\\$TEMP$.CFG", TAG_CFG) != 0 &&
      P70_ReadChunk(f, "REPLAYDATA\\USER\\$TEMP$.CAMS", TAG_CAMS) != 0 &&
      P70_ReadChunk(f, "REPLAYDATA\\USER\\$TEMP$.PADS", TAG_PADS) != 0) {
    g_fclose(f);
    RE_LOGI(save, "повтор загружен: %s (слот %d)", name, (int)slot + 1);
    return 1;
  }
  g_fclose(f);
  RE_LOGW(save, "повтор: %s повреждён — не все части CFG/CAMS/PADS", name);
  return 0;
}

/* P70_FadeColor — Game.exe 005170ab.  One step of a colour fade: current RGB S_00B5A834..836 moves toward the target
   G6_00B5A838..83A by (target - current) * step / steps, step = G6_00C55800 (incremented), steps = G6_00C557F8.
   Note: applied to the already-moved colour each frame, so the fade is not linear (kept as in the original,
   including the int8 truncation of the delta).  When step == steps, sets the target colour (G6Call00516EB4)
   and returns 1 (done); otherwise 0. */
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

/* P70_ShadowText — Game.exe 0051755e.  Draws text txt (P66_Draw5173D7) in white at (x, y) and at (x + d, y + d) with
   flag 0x10 (d = 2, or 3 when a != 0), then again at (x, y) in colour (r, g, b) with flag 4.
   TODO(RE): meaning of a and of the draw flags 0x10 / 4 unsure. */
void P70_ShadowText(int32_t x, int32_t y, uint32_t txt, int32_t a, uint32_t flags, uint8_t r, uint8_t g, uint8_t b) {
  int32_t d = (a == 0) ? 2 : 3;
  G6Call00516EB4(0xff, 0xff, 0xff);
  P66_Draw5173D7((float)x, (float)y, (int32_t)txt, a, (int32_t)(flags | 0x10));
  P66_Draw5173D7((float)(x + d), (float)(y + d), (int32_t)txt, a, (int32_t)(flags | 0x10));
  G6Call00516EB4(r, g, b);
  P66_Draw5173D7((float)x, (float)y, (int32_t)txt, a, (int32_t)(flags | 4));
}

/* общий поиск: x87 считает сумму квадратов в расширенной точности и округляет до float один раз */
/* Index of the nearest active mission target (flag 1, without 0x40) to the player position P59_PosX/Z by
   squared distance, or -1.  Ties keep the lower index. */
static int32_t nearest_obj(void) {
  int32_t best = -1;
  float bd = 0;
  for (int32_t i = 0; i < 10; i++) {
    const uint8_t *o = P58_Objs[i];
    uint32_t fl = (uint32_t)rd32(o, TGT_FLAGS);
    if ((fl & 1) != 0 && (fl & 0x40) == 0) {
      float dz = (float)(rd32(o, TGT_Z) - P59_PosZ);
      float dx = (float)(rd32(o, TGT_X) - P59_PosX);
      float d = (float)((long double)dx * dx + (long double)dz * dz);
      if (best == -1 || d < bd) { best = i; bd = d; }
    }
  }
  return best;
}

/* P70_RadarNearest — Game.exe 005062cc: radar arrow (005063a4 = P135_RadarLine) toward the nearest target. */
void P70_RadarNearest(void) { int32_t i = nearest_obj(); if (i != -1) P70_Fn5063A4(i); }
/* P70_RadarNearestB — Game.exe 0050784d: nearest target -> P70_Fn507925.  TODO(RE): what 00507925 does with it. */
void P70_RadarNearestB(void) { int32_t i = nearest_obj(); if (i != -1) P70_Fn507925(i); }
