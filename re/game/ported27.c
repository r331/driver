/* Чтение кусками, палитры, отчёт об утечках, текстуры вмятин — восстановлено из Game.exe. */
/* ported27.c — level loading helpers (English overview): chunked fread with a progress counter, loading the
   level's 256-colour palettes, the DebugMalloc leak report and the car damage ("dent") textures.  All __cdecl. */
#include "ported27.h"
#include "ported4.h"
#include "ported6.h"
#include "ported12.h"
#include "ported14.h"
#include "smallfuncs.h"
#include "engine.h"
#include "crt.h"
#include "unported.h"
#include <stdio.h>
#include <string.h>
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P27_ReadBytes")
#undef P27_ReadBytes
#pragma push_macro("P27_ReadBytes") /*gvi*/
#undef P27_ReadBytes /*gvi*/
int32_t P27_ReadBytes;
#pragma pop_macro("P27_ReadBytes") /*gvi*/
#pragma pop_macro("P27_ReadBytes")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P27_ReadLimit")
#undef P27_ReadLimit
#pragma push_macro("P27_ReadLimit") /*gvi*/
#undef P27_ReadLimit /*gvi*/
int32_t P27_ReadLimit;
#pragma pop_macro("P27_ReadLimit") /*gvi*/
#pragma pop_macro("P27_ReadLimit")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P27_ProgressOn")
#undef P27_ProgressOn
#pragma push_macro("P27_ProgressOn") /*gvi*/
#undef P27_ProgressOn /*gvi*/
int32_t P27_ProgressOn;
#pragma pop_macro("P27_ProgressOn") /*gvi*/
#pragma pop_macro("P27_ProgressOn")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P27_MemAllocated")
#undef P27_MemAllocated
#pragma push_macro("P27_MemAllocated") /*gvi*/
#undef P27_MemAllocated /*gvi*/
int32_t P27_MemAllocated;
#pragma pop_macro("P27_MemAllocated") /*gvi*/
#pragma pop_macro("P27_MemAllocated")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P27_MemFreed")
#undef P27_MemFreed
#pragma push_macro("P27_MemFreed") /*gvi*/
#undef P27_MemFreed /*gvi*/
int32_t P27_MemFreed;
#pragma pop_macro("P27_MemFreed") /*gvi*/
#pragma pop_macro("P27_MemFreed")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P27_MemTab")
#undef P27_MemTab
#pragma push_macro("P27_MemTab") /*gvi*/
#undef P27_MemTab /*gvi*/
p27_memtab_t P27_MemTab;
#pragma pop_macro("P27_MemTab") /*gvi*/
#pragma pop_macro("P27_MemTab")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P27_DentTex")
#undef P27_DentTex
#pragma push_macro("P27_DentTex") /*gvi*/
#undef P27_DentTex /*gvi*/
p27_dent_t P27_DentTex;
#pragma pop_macro("P27_DentTex") /*gvi*/
#pragma pop_macro("P27_DentTex")
#endif
#define MAIN_HWND ((void *)(intptr_t)G6_00BDF9C0)

enum {
  READ_CHUNK      = 0xffff,   /* single-record reads are split into chunks of at most 64 KB - 1 */
  PAL_SLOTS       = 0x32,     /* 50 palette slots in P14_01252be0 */
  PAL_BYTES       = 0x400,    /* 256 entries x 4 bytes */
  MEMTAB_ENTRIES  = 0x1000,   /* DebugMalloc tracking table: {address, size, log string} x 4096 */
  DENT_PANELS     = 11,       /* TODO(RE): outer loop index i (name suffix 1..11) — meaning unsure */
  DENT_LEVELS     = 6         /* TODO(RE): inner index j (name prefix 0..5) — damage stage? unsure */
};

/* P27_ReadChunked — Game.exe 004d9596.  fread(dst, size, count, file); with count == 1 the read is split into
   0xffff-byte pieces.  Adds the bytes to P27_ReadBytes and, when loading progress is on (P27_ProgressOn) and
   the counter passed P27_ReadLimit, updates the loading screen (Call004D9663).  Always returns 1
   (read errors are not checked, as in the original). */
int32_t P27_ReadChunked(void *dst, int32_t size, int32_t count, void *file) {
  uint8_t *p = (uint8_t *)dst;
  if (count == 1) {
    for (; size > READ_CHUNK; size -= READ_CHUNK) {
      g_fread(p, READ_CHUNK, 1, file);
      p += READ_CHUNK;
      P27_ReadBytes += READ_CHUNK;
    }
    g_fread(p, (size_t)size, 1, file);
    P27_ReadBytes += size;
  } else {
    g_fread(p, (size_t)size, (size_t)count, file);
    P27_ReadBytes += size * count;
  }
  if (P27_ReadLimit < P27_ReadBytes && P27_ProgressOn != 0) Call004D9663();
  return 1;
}

/* P27_LoadPalettes — Game.exe 004ec154.  Reads the palette block of a level file: s16 count, then per palette
   s16 slot + 0x400 bytes.  Valid slots (0..49) go to P14_01252be0[slot * 0x400] and are marked in
   P12_01252aa0; an invalid slot is logged, reported in a message box and its data skipped. */
void P27_LoadPalettes(void *file) {
  char msg[256];
  int16_t n, slot;
  for (int i = 0; i < PAL_SLOTS; i++) P12_01252aa0[i] = 0;
  P27_ReadChunked(&n, 2, 1, file);
  int cnt = n;
  while (cnt != 0) {
    cnt--;
    P27_ReadChunked(&slot, 2, 1, file);
    if (slot < 0 || slot > 0x31) {
      snprintf(msg, sizeof msg, "Illegal palette slot load access (%d).", (int)slot);
      DebugLog(msg);
      snprintf(msg, sizeof msg, "Tried to store palette to slot %d", (int)slot);
      plat_message_box(MAIN_HWND, msg, "Error", 0);
      g_fseek(file, PAL_BYTES, 1);   /* SEEK_CUR: skip this palette */
    } else {
      P27_ReadChunked(&P14_01252be0[slot * PAL_BYTES], PAL_BYTES, 1, file);
      P12_01252aa0[slot] = 1;
    }
  }
}

/* P27_MemLeakReport — Game.exe 004d8c80.  When the DebugMalloc counters P27_MemAllocated / P27_MemFreed differ,
   shows a "MEMORY FAULT" message box for every block still in P27_MemTab (with its log string, if any) and
   frees the block and the string. */
void P27_MemLeakReport(void) {
  char msg[256];
  if (P27_MemAllocated == P27_MemFreed) return;
  for (int i = 0; i < MEMTAB_ENTRIES; i++) {
    uint32_t *e = &P27_MemTab[i * 3];
    if (e[0] == 0) continue;
    if (e[2] == 0) {
      snprintf(msg, sizeof msg, "%d bytes of memory were not released from address $%x!\nThis is due to poor use of malloc / free - resolve immediately!", (int)e[1], (unsigned)e[0]);
    } else {
      snprintf(msg, sizeof msg, "%d bytes of memory were not released from address $%x!\nThis is due to poor use of malloc / free - resolve immediately!\nMemory Log: %s", (int)e[1], (unsigned)e[0], (const char *)(uintptr_t)e[2]);
      CrtFree_0052CB70(e[2]);
      e[2] = 0;
    }
    plat_message_box(MAIN_HWND, msg, "MEMORY FAULT", 0x30);
    CrtFree_0052CB70(e[0]);
    e[0] = 0;
  }
}

/* Dent texture name formats, indexed by the player car model S_00D1192C (0..17; out of range -> "BD").
   The middle part is the car's texture code (POL = police, TAX = taxi; the rest are model abbreviations). */

static const char *const k_dent_fmt[18] = {
  "%iBD%i", "%iTRUCK%i", "%iRED%i", "%iFAR%i", "%iCAM%i", "%iMER%i", "%iNOV%i", "%iCAD%i", "%iPON%i",
  "%iCHE%i", "%iPOL%i", "%iGP%i", "%iTLT%i", "%iTAX%i", "%iCA%i", "%iJAG%i", "%iFER%i", "%iTHU%i" };
/* P27_LoadDentTextures — Game.exe 004c17ae.  Loads 11 x 6 damage texture pages named "<j><CAR><i+1>" for the
   current car model into P27_DentTex[i * 6 + j], allocates the 128 KB scratch texture page D_00d17ec8
   used to compose the damaged texture (freeing an old one), then calls Call004C1B6C(0).
   TODO(RE): Call004C1B6C — presumably resets the damage state of the texture; unsure. */
void P27_LoadDentTextures(void) {
  char name[32];
  for (int i = 0; i < DENT_PANELS; i++) {
    for (int j = 0; j < DENT_LEVELS; j++) {
      int32_t car = S_00D1192C;
      const char *fmt = (car >= 0 && car < 18) ? k_dent_fmt[car] : "%iBD%i";
      snprintf(name, sizeof name, fmt, j, i + 1);
      P27_DentTex[i * 6 + j] = Call004EC91E(name);
    }
  }
  if (D_00d17ec8 != NULL) { DebugFree(D_00d17ec8); D_00d17ec8 = NULL; }
  D_00d17ec8 = DebugMalloc(0x20000, "D:\\Driver\\Game\\denting.c", 0x500);
  if (D_00d17ec8 == NULL) plat_message_box(MAIN_HWND, "Could not malloc space for temporary damage tpage", "ERROR", 0);
  Call004C1B6C(0);
}
