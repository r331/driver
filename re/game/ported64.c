#include "ported64.h"
#include <stdio.h>
#include <string.h>

#ifndef RE_HOOK_BUILD
const uint8_t *P64_NativeTable = NULL;
const uint8_t *P64_CurTable = NULL;
#endif

static int32_t rd32(const uint8_t *p, uint32_t o) { int32_t v; memcpy(&v, p + o, 4); return v; }
static void    wr32(uint8_t *p, uint32_t o, int32_t v) { memcpy(p + o, &v, 4); }
/* таблица рекордов записи: в hook — настоящий 32-битный указатель из поля +0xc */
/* Replay save file (SAVES\REPLAYn.BIN): 8-byte header {magic, byte sum of the 0x38-byte name block}, the name
   block, then three chunks [tag][size][file data].  Tags are little-endian ASCII. */
#define REPLAY_MAGIC   0x38910457u
#define REPLAY_NAMELEN 0x38
#define CHUNK_CFG      0x21474643u   /* "CFG!" */
#define CHUNK_CAMS     0x534d4143u   /* "CAMS" */
#define CHUNK_PADS     0x53444150u   /* "PADS" */

/* High-score ranking: event result e and table entries t (5 places of 0x2c bytes each). */
#define EV_SCORE       0x08   /* int32 result compared by RankScore */
#define EV_TABLE       0x0c   /* 32-bit pointer to the high-score table (hook) / slot for it (native) */
#define EV_TIME        0x10   /* packed time (PackRGB00503ECC) */
#define EV_TOP_TIME    0x28   /* packed time used by P64_RankTop */
#define EV_TOP_STATE   0x2c   /* must be 8 for P64_RankTop */
#define EV_VALID       0x40   /* non-zero: the result can be ranked */
#define HS_PLACES      5
#define HS_ENTRY       0x2c
#define HS_SCORE       0x10
#define HS_TIME        0x14
#define HS_STATE       0x18
#define HS_USED        8      /* TODO(RE): unsure — state value of a filled place; anything else = free place */

/* Table of a ranking entry: in hook the real 32-bit pointer from field +0xc, in native P64_CurTable. */
static const uint8_t *Tbl(const uint8_t *e) {
#ifdef RE_HOOK_BUILD
  return (const uint8_t *)(uintptr_t)(uint32_t)rd32(e, EV_TABLE);
#else
  (void)e; return P64_CurTable;
#endif
}
static uint32_t Pack(const uint8_t *p) { return PackRGB00503ECC((uint8_t *)p); }

/* 00406272 */
/* P64_SaveChunk — Game.exe 00406272.  Appends the whole file name to the open file as [tag][size][data].
   Returns 1 on success, 0 if name cannot be opened or the buffer cannot be allocated. */
int32_t P64_SaveChunk(void *file, const char *name, uint32_t tag) {
  void *f = g_fopen(name, "rb");
  if (f == NULL) return 0;
  g_fseek(f, 0, 2);
  int32_t size = (int32_t)g_ftell(f);
  g_fseek(f, 0, 0);
  uint8_t *buf = (uint8_t *)DebugMalloc(size, "D:\\Driver\\Game\\frontend\\config.c", 0x237);
  if (buf == NULL) { g_fclose(f); return 0; }
  g_fread(buf, 1, (size_t)size, f);
  g_fclose(f);
  g_fwrite(&tag, 1, 4, file);
  g_fwrite(&size, 1, 4, file);
  g_fwrite(buf, 1, (size_t)size, file);
  DebugFree(buf);
  return 1;
}

/* 00406096 */
/* P64_SaveReplay — Game.exe 00406096.  Writes SAVES\REPLAY<slot+1>.BIN: header P59_Hdr, name block
   P59_Rep57B6B8, then the CFG!, CAMS and PADS chunks from REPLAYDATA\USER\$TEMP$.* (the CAMS file is saved
   from the director first if it does not exist).  On any failure the partial file is removed.  1 / 0. */
int32_t P64_SaveReplay(int32_t slot) {
  char name[32];
  snprintf(name, sizeof name, "SAVES\\REPLAY%d.BIN", slot + 1);
  void *f = g_fopen(name, "wb");
  if (f == NULL) return 0;
  g_fwrite(P59_Hdr, 1, 8, f);
  g_fwrite(P59_Rep57B6B8, 1, 0x38, f);
  if (P64_SaveChunk(f, "REPLAYDATA\\USER\\$TEMP$.CFG", CHUNK_CFG) != 0) {
    if (P57_FileExists("REPLAYDATA\\USER\\$TEMP$.CAMS") == 0) P57_SaveDirectorIfAny("REPLAYDATA\\USER\\$TEMP$.CAMS");
    if (P64_SaveChunk(f, "REPLAYDATA\\USER\\$TEMP$.CAMS", CHUNK_CAMS) != 0 &&
        P64_SaveChunk(f, "REPLAYDATA\\USER\\$TEMP$.PADS", CHUNK_PADS) != 0) {
      g_fclose(f);
      return 1;
    }
  }
  g_fclose(f);
  g_remove(name);
  return 0;
}

/* 00405f6f */
/* P64_ReplayStart — Game.exe 00405f6f.  Sets the replay name block (0x38 bytes, name or empty), its byte sum
   and the magic into the header, then saves the replay to slot (P64_SaveReplay).  Returns its result. */
int32_t P64_ReplayStart(int32_t slot, const char *name) {
  uint8_t *rep = (uint8_t *)P59_Rep57B6B8;
  memset(rep, 0, REPLAY_NAMELEN);
  if (name != NULL) { strncpy((char *)rep, name, REPLAY_NAMELEN - 1); }   /* оригинал — strcpy без границ */
  int32_t sum = SumBytes(rep, REPLAY_NAMELEN);
  memset(P59_Hdr, 0, 8);
  P59_Hdr[1] = (uint32_t)sum;
  P59_Hdr[0] = REPLAY_MAGIC;
  return P64_SaveReplay(slot);
}

/* Place (0..4) the result e would take in its table, or -1.  e takes place i when it is free, holds a lower
   score, or holds an equal score and a packed value (signed) smaller than ours (TODO(RE): unsure what the packed
   value is — the original note calls it the time).  Types 1 and 7. */
/* общий разбор для типов 1 и 7: результат важнее, при равенстве — меньшее время */
static int32_t RankScore(uint8_t *e) {
  if (rd32(e, EV_VALID) != 0) {
    const uint8_t *t = Tbl(e);
    for (int32_t i = 0; i < HS_PLACES; i++) {
      if (t == NULL) break;
      if (rd32(t, HS_STATE + i * HS_ENTRY) != HS_USED) return i;
      if (rd32(t, HS_SCORE + i * HS_ENTRY) < rd32(e, EV_SCORE)) return i;
      if (rd32(e, EV_SCORE) == rd32(t, HS_SCORE + i * HS_ENTRY)) {
        uint32_t a = Pack(e + EV_TIME), b = Pack(t + HS_TIME + i * HS_ENTRY);
        if ((int32_t)b < (int32_t)a) return i;
      }
    }
  }
  return -1;
}
/* Place by time only: less = 0 — we take the place when our time is smaller, less = 1 — when it is larger.
   A free place is always taken.  -1 when the result is not valid or does not place. */
/* общий разбор по времени: less=0 — берём место, если наше время меньше (iVar1 < iVar2), less=1 — если больше */
static int32_t RankTime(uint8_t *e, int less) {
  if (rd32(e, EV_VALID) != 0) {
    const uint8_t *t = Tbl(e);
    int32_t mine = (int32_t)Pack(e + EV_TIME);
    for (int32_t i = 0; i < HS_PLACES; i++) {
      if (t == NULL) break;
      if (rd32(t, HS_STATE + i * HS_ENTRY) != HS_USED) return i;
      int32_t other = (int32_t)Pack(t + HS_TIME + i * HS_ENTRY);
      if (less ? (other < mine) : (mine < other)) return i;
    }
  }
  return -1;
}

/* Per-type ranking entry points (Game.exe addresses on the right); see RankScore / RankTime. */
int32_t P64_RankBestFirst(uint8_t *e) { return RankScore(e); }   /* 0051cf17 */
int32_t P64_RankScoreB(uint8_t *e)    { return RankScore(e); }   /* 0051d0e0 */
int32_t P64_RankTimeMore(uint8_t *e)  { return RankTime(e, 0); } /* 0051ce94 */
int32_t P64_RankTimeB(uint8_t *e)     { return RankTime(e, 0); } /* 0051d05d */
int32_t P64_RankTimeLess(uint8_t *e)  { return RankTime(e, 1); } /* 0051cfda */

/* 0051d1a3 */
/* P64_RankTop — Game.exe 0051d1a3.  Type 0xc: single best-time record.  0 when e's time (+0x28, state +0x2c must
   be 8) beats the stored place 0 (or place 0 is free), else -1. */
int32_t P64_RankTop(uint8_t *e) {
  if (rd32(e, EV_TOP_STATE) != HS_USED) return -1;
  const uint8_t *t = Tbl(e);
  if (t != NULL && rd32(t, HS_STATE) == HS_USED) {
    int32_t a = (int32_t)Pack(e + EV_TOP_TIME), b = (int32_t)Pack(t + HS_TIME);
    if (b <= a) return -1;
  }
  return 0;
}

/* 0051cc55 */
/* P64_RankPlace — Game.exe 0051cc55.  High-score place of result ev in table (type, idx) (P42_GetHighScore):
   stores the table in ev+0xc (native: also points P64_CurTable at P64_NativeTable) and dispatches by type.
   Returns the place 0..4 or -1 (no table / unknown type: ev+0xc cleared). */
int32_t P64_RankPlace(void *ev, int32_t type, int32_t idx) {
  uint8_t *e = (uint8_t *)ev;
  int32_t v = P42_GetHighScore(type, idx);
  if (v == 0) { wr32(e, EV_TABLE, 0); return -1; }
#ifdef RE_HOOK_BUILD
  wr32(e, EV_TABLE, v);
#else
  wr32(e, EV_TABLE, v); P64_CurTable = P64_NativeTable;
#endif
  switch (type) {
  case 1: return P64_RankBestFirst(e);
  case 2: return P64_RankTimeMore(e);
  case 3: return P64_RankTimeLess(e);
  case 7: return P64_RankScoreB(e);
  case 0xb: return P64_RankTimeB(e);
  case 0xc: return P64_RankTop(e);
  default: wr32(e, EV_TABLE, 0); return -1;
  }
}
