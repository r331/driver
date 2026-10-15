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
static const uint8_t *Tbl(const uint8_t *e) {
#ifdef RE_HOOK_BUILD
  return (const uint8_t *)(uintptr_t)(uint32_t)rd32(e, 0xc);
#else
  (void)e; return P64_CurTable;
#endif
}
static uint32_t Pack(const uint8_t *p) { return PackRGB00503ECC((uint8_t *)p); }

/* 00406272 */
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
int32_t P64_SaveReplay(int32_t slot) {
  char name[32];
  snprintf(name, sizeof name, "SAVES\\REPLAY%d.BIN", slot + 1);
  void *f = g_fopen(name, "wb");
  if (f == NULL) return 0;
  g_fwrite(P59_Hdr, 1, 8, f);
  g_fwrite(P59_Rep57B6B8, 1, 0x38, f);
  if (P64_SaveChunk(f, "REPLAYDATA\\USER\\$TEMP$.CFG", 0x21474643) != 0) {
    if (P57_FileExists("REPLAYDATA\\USER\\$TEMP$.CAMS") == 0) P57_SaveDirectorIfAny("REPLAYDATA\\USER\\$TEMP$.CAMS");
    if (P64_SaveChunk(f, "REPLAYDATA\\USER\\$TEMP$.CAMS", 0x534d4143) != 0 &&
        P64_SaveChunk(f, "REPLAYDATA\\USER\\$TEMP$.PADS", 0x53444150) != 0) {
      g_fclose(f);
      return 1;
    }
  }
  g_fclose(f);
  g_remove(name);
  return 0;
}

/* 00405f6f */
int32_t P64_ReplayStart(int32_t slot, const char *name) {
  uint8_t *rep = (uint8_t *)P59_Rep57B6B8;
  memset(rep, 0, 0x38);
  if (name != NULL) { strncpy((char *)rep, name, 0x37); }   /* оригинал — strcpy без границ */
  int32_t sum = SumBytes(rep, 0x38);
  memset(P59_Hdr, 0, 8);
  P59_Hdr[1] = (uint32_t)sum;
  P59_Hdr[0] = 0x38910457u;
  return P64_SaveReplay(slot);
}

/* общий разбор для типов 1 и 7: результат важнее, при равенстве — меньшее время */
static int32_t RankScore(uint8_t *e) {
  if (rd32(e, 0x40) != 0) {
    const uint8_t *t = Tbl(e);
    for (int32_t i = 0; i < 5; i++) {
      if (t == NULL) break;
      if (rd32(t, 0x18 + i * 0x2c) != 8) return i;
      if (rd32(t, 0x10 + i * 0x2c) < rd32(e, 8)) return i;
      if (rd32(e, 8) == rd32(t, 0x10 + i * 0x2c)) {
        uint32_t a = Pack(e + 0x10), b = Pack(t + 0x14 + i * 0x2c);
        if ((int32_t)b < (int32_t)a) return i;
      }
    }
  }
  return -1;
}
/* общий разбор по времени: less=0 — берём место, если наше время меньше (iVar1 < iVar2), less=1 — если больше */
static int32_t RankTime(uint8_t *e, int less) {
  if (rd32(e, 0x40) != 0) {
    const uint8_t *t = Tbl(e);
    int32_t mine = (int32_t)Pack(e + 0x10);
    for (int32_t i = 0; i < 5; i++) {
      if (t == NULL) break;
      if (rd32(t, 0x18 + i * 0x2c) != 8) return i;
      int32_t other = (int32_t)Pack(t + 0x14 + i * 0x2c);
      if (less ? (other < mine) : (mine < other)) return i;
    }
  }
  return -1;
}

int32_t P64_RankBestFirst(uint8_t *e) { return RankScore(e); }   /* 0051cf17 */
int32_t P64_RankScoreB(uint8_t *e)    { return RankScore(e); }   /* 0051d0e0 */
int32_t P64_RankTimeMore(uint8_t *e)  { return RankTime(e, 0); } /* 0051ce94 */
int32_t P64_RankTimeB(uint8_t *e)     { return RankTime(e, 0); } /* 0051d05d */
int32_t P64_RankTimeLess(uint8_t *e)  { return RankTime(e, 1); } /* 0051cfda */

/* 0051d1a3 */
int32_t P64_RankTop(uint8_t *e) {
  if (rd32(e, 0x2c) != 8) return -1;
  const uint8_t *t = Tbl(e);
  if (t != NULL && rd32(t, 0x18) == 8) {
    int32_t a = (int32_t)Pack(e + 0x28), b = (int32_t)Pack(t + 0x14);
    if (b <= a) return -1;
  }
  return 0;
}

/* 0051cc55 */
int32_t P64_RankPlace(void *ev, int32_t type, int32_t idx) {
  uint8_t *e = (uint8_t *)ev;
  int32_t v = P42_GetHighScore(type, idx);
  if (v == 0) { wr32(e, 0xc, 0); return -1; }
#ifdef RE_HOOK_BUILD
  wr32(e, 0xc, v);
#else
  wr32(e, 0xc, v); P64_CurTable = P64_NativeTable;
#endif
  switch (type) {
  case 1: return P64_RankBestFirst(e);
  case 2: return P64_RankTimeMore(e);
  case 3: return P64_RankTimeLess(e);
  case 7: return P64_RankScoreB(e);
  case 0xb: return P64_RankTimeB(e);
  case 0xc: return P64_RankTop(e);
  default: wr32(e, 0xc, 0); return -1;
  }
}
