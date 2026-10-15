/* Загрузка текстурных страниц карты — восстановлено из Game.exe (map.c, строка 0x225). */
#include "ported41.h"
#include "ported4.h"
#include "ported6.h"
#include "ported27.h"
#include "ported40.h"
#include "smallfuncs.h"
#include "engine.h"
#include "crt.h"
#include <string.h>
GAME_VAR_DEF(p41_texsel_t, P41_TexSel, 0x00562d80)
GAME_VAR_DEF(int32_t, P41_Offset, 0x00b31ee0)
GAME_VAR_DEF(uint32_t, P41_Arena, 0x00d01260)
GAME_VAR_DEF(int32_t, P41_Flag, 0x00c82530)
GAME_VAR_DEF(p41_buf0_t, P41_Buf0, 0x00c98f00)
GAME_VAR_DEF(p41_buf1_t, P41_Buf1, 0x00ce1f60)
#define MAIN_HWND41 ((void *)(intptr_t)G6_00BDF9C0)

static uint8_t *p41_ram;
uint8_t *P41_RamPtr(void) { return p41_ram; } /* полный указатель на P41_Arena (в native адрес не влезает в 32 бита) */

/* Положить копию страницы в RAM-буфер и запомнить её адрес в слоте (005283b5 = memcpy). */
static void store_page(int32_t slot, const void *src, int32_t size) {
  P40_Slots[slot].data = P41_Arena + (uint32_t)P41_Offset;
  memcpy(p41_ram + P41_Offset, src, (size_t)size);
  P41_Offset += size;
}

void P41_LoadTexPages(void *file) {
  uint16_t flags = 0;
  int16_t tex = 0;
  int16_t tmp16;
  int32_t count = 0;
  P27_LoadPalettes(file);
  P27_ReadChunked(&count, 4, 1, file);
  P40_ResetTexMem();
  P41_Offset = 0;
  int32_t sel = P41_TexSel[D_00b87e30];
  int32_t sel2 = (D_00b87e30 == 4) ? 0x11 : -1;
  long start = g_ftell(file);
  int32_t total = 0;
  for (int32_t i = 0; i < count;) {
    g_fread(&flags, 2, 1, file);
    g_fread(&tex, 2, 1, file);
    int pair = (flags & 0x10) != 0;
    if (!pair) {
      g_fseek(file, 0x20000, 1);
    } else {
      g_fread(P41_Buf0, 0x10000, 1, file);
      g_fread(&tmp16, 2, 1, file);
      g_fread(&tmp16, 2, 1, file);
      g_fseek(file, 0x10000, 1);
    }
    if ((flags & 1) == 0) {
      if ((flags & 4) == 0 || tex != S_00D1192C) {
        if (((flags & 8) != 0 && tex == S_00D1192C) || (flags & 2) != 0) total += 0x20000;
      } else {
        total += 0x20000;
      }
    } else if (i == sel || i == sel2) {
      total += pair ? 0x10000 : 0x20000;
    }
    i += pair ? 2 : 1;
  }
  if (total != 0) {
    p41_ram = (uint8_t *)DebugMalloc(total, "D:\\Driver\\Game\\map.c", 0x225);
    P41_Arena = (uint32_t)(uintptr_t)p41_ram;
    if (p41_ram == NULL) plat_message_box(MAIN_HWND41, "Could not malloc space for RAM texture pages", "ERROR", 0);
  }
  g_fseek(file, start, 0);
  for (int32_t i = 0; i < count;) {
    int32_t idx = i, nxt = i + 1;
    P27_ReadChunked(&flags, 2, 1, file);
    P27_ReadChunked(&tex, 2, 1, file);
    int pair = (flags & 0x10) != 0;
    if (!pair) {
      P27_ReadChunked(P41_Buf0, 0x20000, 1, file);
    } else {
      P27_ReadChunked(P41_Buf0, 0x10000, 1, file);
      P27_ReadChunked(&tmp16, 2, 1, file);
      P27_ReadChunked(&tmp16, 2, 1, file);
      P27_ReadChunked(P41_Buf1, 0x10000, 1, file);
    }
    int32_t b0 = (int32_t)(uintptr_t)P41_Buf0, b1 = (int32_t)(uintptr_t)P41_Buf1;
    if ((flags & 1) == 0) {
      if ((flags & 4) == 0) {
        if (((flags & 8) != 0 && tex == S_00D1192C) || (flags & 2) != 0) {
          if (!pair) {
            P40_Slots[idx].flags = 0;
            store_page(idx, P41_Buf0, 0x20000);
          } else {
            P40_DownloadPalette(idx, b0);
            P40_DownloadPalette(nxt, b1);
            P40_Slots[idx].flags = 4;
            store_page(idx, P41_Buf0, 0x10000);
            P40_Slots[nxt].flags = 0xc;
            store_page(nxt, P41_Buf1, 0x10000);
          }
        }
      } else if (tex == S_00D1192C) {
        if (!pair) {
          P40_Slots[idx].flags = 2;
          P40_UploadSlot(idx, b0);
          store_page(idx, P41_Buf0, 0x20000);
        } else {
          P40_DownloadPalette(idx, b0);
          P40_DownloadPalette(nxt, b1);
          P40_Slots[idx].flags = 6;
          P40_Slots[nxt].flags = 0xe;
          P40_UploadSlotPair(idx, b0, b1);
          store_page(idx, P41_Buf0, 0x10000);
          store_page(nxt, P41_Buf1, 0x10000);
        }
      }
    } else if (!pair) {
      P40_Slots[idx].flags = 2;
      P40_UploadSlot(idx, b0);
      if (idx == sel || idx == sel2) {
        store_page(idx, P41_Buf0, 0x20000);
        if (idx == sel) P41_Flag = 1;
      }
    } else {
      P40_DownloadPalette(idx, b0);
      P40_DownloadPalette(nxt, b1);
      P40_Slots[idx].flags = 6;
      P40_Slots[nxt].flags = 0xe;
      P40_UploadSlotPair(idx, b0, b1);
      if (idx == sel || idx == sel2) {
        store_page(idx, P41_Buf0, 0x10000);
        if (idx == sel) P41_Flag = 0;
      }
      if (nxt == sel || nxt == sel2) {
        store_page(nxt, P41_Buf1, 0x10000);
        if (nxt == sel) P41_Flag = 0;
      }
    }
    i += pair ? 2 : 1;
  }
}
