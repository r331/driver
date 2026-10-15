/* Чтение кусками, палитры, отчёт об утечках, текстуры вмятин — восстановлено из Game.exe. */
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
GAME_VAR_DEF(int32_t, P27_ReadBytes, 0x00d117e8)
GAME_VAR_DEF(int32_t, P27_ReadLimit, 0x00d117f0)
GAME_VAR_DEF(int32_t, P27_ProgressOn, 0x00b2c3b8)
GAME_VAR_DEF(int32_t, P27_MemAllocated, 0x00b20380)
GAME_VAR_DEF(int32_t, P27_MemFreed, 0x00b20398)
GAME_VAR_DEF(p27_memtab_t, P27_MemTab, 0x00b203a0)
GAME_VAR_DEF(p27_dent_t, P27_DentTex, 0x00d17d60)
#define MAIN_HWND ((void *)(intptr_t)G6_00BDF9C0)

int32_t P27_ReadChunked(void *dst, int32_t size, int32_t count, void *file) {
  uint8_t *p = (uint8_t *)dst;
  if (count == 1) {
    for (; size > 0xffff; size -= 0xffff) {
      g_fread(p, 0xffff, 1, file);
      p += 0xffff;
      P27_ReadBytes += 0xffff;
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

void P27_LoadPalettes(void *file) {
  char msg[256];
  int16_t n, slot;
  for (int i = 0; i < 0x32; i++) P12_01252aa0[i] = 0;
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
      g_fseek(file, 0x400, 1);
    } else {
      P27_ReadChunked(&P14_01252be0[slot * 0x400], 0x400, 1, file);
      P12_01252aa0[slot] = 1;
    }
  }
}

void P27_MemLeakReport(void) {
  char msg[256];
  if (P27_MemAllocated == P27_MemFreed) return;
  for (int i = 0; i < 0x1000; i++) {
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

static const char *const k_dent_fmt[18] = {
  "%iBD%i", "%iTRUCK%i", "%iRED%i", "%iFAR%i", "%iCAM%i", "%iMER%i", "%iNOV%i", "%iCAD%i", "%iPON%i",
  "%iCHE%i", "%iPOL%i", "%iGP%i", "%iTLT%i", "%iTAX%i", "%iCA%i", "%iJAG%i", "%iFER%i", "%iTHU%i" };
void P27_LoadDentTextures(void) {
  char name[32];
  for (int i = 0; i < 11; i++) {
    for (int j = 0; j < 6; j++) {
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
