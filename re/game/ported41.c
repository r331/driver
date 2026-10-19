/* Загрузка текстурных страниц карты — восстановлено из Game.exe (map.c, строка 0x225). */
/* ported41.c — loading of a level's texture pages (Game.exe map.c).  Each page record in the level file
   is {u16 flags, u16 tex, data}: a 16-bit page is 0x20000 bytes (256 x 256 x 2); with PAGE_PAIR the
   record holds two 8-bit (paletted) pages of 0x10000 bytes separated by two u16 words.  Pages are
   uploaded to texture memory (P40_*) and/or kept as RAM copies in one arena (P41_Arena) for code that
   reads texels directly.  Native also captures every page as a GL texture (P86_NativeCapture). */
#include "ported41.h"
#include "reptr.h"
#include "ported4.h"
#include "ported6.h"
#include "ported27.h"
#include "ported40.h"
#include "smallfuncs.h"
#include "engine.h"
#include "crt.h"
#include <string.h>
#ifndef RE_HOOK_BUILD
#include "ported86.h"
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P41_TexSel")
#undef P41_TexSel
#pragma push_macro("P41_TexSel") /*gvi*/
#undef P41_TexSel /*gvi*/
p41_texsel_t P41_TexSel;
#pragma pop_macro("P41_TexSel") /*gvi*/
#pragma pop_macro("P41_TexSel")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P41_Offset")
#undef P41_Offset
#pragma push_macro("P41_Offset") /*gvi*/
#undef P41_Offset /*gvi*/
int32_t P41_Offset;
#pragma pop_macro("P41_Offset") /*gvi*/
#pragma pop_macro("P41_Offset")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P41_Arena")
#undef P41_Arena
#pragma push_macro("P41_Arena") /*gvi*/
#undef P41_Arena /*gvi*/
uint32_t P41_Arena;
#pragma pop_macro("P41_Arena") /*gvi*/
#pragma pop_macro("P41_Arena")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P41_Flag")
#undef P41_Flag
#pragma push_macro("P41_Flag") /*gvi*/
#undef P41_Flag /*gvi*/
int32_t P41_Flag;
#pragma pop_macro("P41_Flag") /*gvi*/
#pragma pop_macro("P41_Flag")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P41_Buf0")
#undef P41_Buf0
#pragma push_macro("P41_Buf0") /*gvi*/
#undef P41_Buf0 /*gvi*/
p41_buf0_t P41_Buf0;
#pragma pop_macro("P41_Buf0") /*gvi*/
#pragma pop_macro("P41_Buf0")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P41_Buf1")
#undef P41_Buf1
#pragma push_macro("P41_Buf1") /*gvi*/
#undef P41_Buf1 /*gvi*/
p41_buf1_t P41_Buf1;
#pragma pop_macro("P41_Buf1") /*gvi*/
#pragma pop_macro("P41_Buf1")
#endif
#define MAIN_HWND41 ((void *)(intptr_t)G6_00BDF9C0)

/* page record flags (u16 before each page in the level file) */
#define PAGE_UPLOAD      0x01   /* upload to texture memory; RAM copy only if it is the city's selected page */
#define PAGE_RAM         0x02   /* keep a RAM copy (not uploaded) */
#define PAGE_UPLOAD_IF   0x04   /* upload + RAM copy if tex == S_00D1192C */
#define PAGE_RAM_IF      0x08   /* RAM copy only if tex == S_00D1192C */
#define PAGE_PAIR        0x10   /* record holds two 8-bit pages (indices i and i+1) */
#define PAGE16_BYTES     0x20000  /* one 16-bit page */
#define PAGE8_BYTES      0x10000  /* one 8-bit page */
#define INTERVIEW_MODE   4        /* D_00b87e30 value during the Undercover interview */
#define INTERVIEW_PAGE   0x11     /* extra page kept in RAM in interview mode */
/* P40_Slots[].flags values written here: bit 1 = uploaded, bit 2 = paletted (8-bit), bit 3 = second
   page of a pair — so 0 = RAM-only 16-bit, 2 = uploaded 16-bit, 4/0xc = RAM-only pair, 6/0xe = uploaded pair. */

static uint8_t *p41_ram;
uint8_t *P41_RamPtr(void) { return p41_ram; } /* полный указатель на P41_Arena (в native адрес не влезает в 32 бита) */

/* Append a RAM copy of a page to the arena and record its (32-bit) arena address in the slot.
   Положить копию страницы в RAM-буфер и запомнить её адрес в слоте (005283b5 = memcpy). */
static void store_page(int32_t slot, const void *src, int32_t size) {
  P40_Slots[slot].data = P41_Arena + (uint32_t)P41_Offset;
  memcpy(p41_ram + P41_Offset, src, (size_t)size);
  P41_Offset += size;
}

/* P41_LoadTexPages — Game.exe 004eb975.  Loads all texture pages of the open level file:
   palettes first (P27_LoadPalettes), then the page count, and two passes over the page records:
     pass 1 (plain fread/fseek) sums the size of all RAM copies that will be needed;
     pass 2 (P27_ReadChunked) reads every page, uploads it and/or stores a RAM copy per its flags.
   Which upload page is also kept in RAM: sel = P41_TexSel[D_00b87e30] (per game mode / city), plus page
   0x11 in interview mode.  P41_Flag records whether sel was a 16-bit (1) or 8-bit (0) page.
   Side effects: P40 slot table, P41_Arena / P41_Offset, P41_Buf0/1 scratch; message box if the arena
   cannot be allocated (the load then continues — as in the original). */
void P41_LoadTexPages(void *file) {
  uint16_t flags = 0;
  int16_t tex = 0;
  int16_t tmp16;
  int32_t count = 0;
  P27_LoadPalettes(file);
#ifndef RE_HOOK_BUILD
  P86_NativeReset();
#endif
  P27_ReadChunked(&count, 4, 1, file);
  P40_ResetTexMem();
  P41_Offset = 0;
  int32_t sel = P41_TexSel[D_00b87e30];
  int32_t sel2 = (D_00b87e30 == INTERVIEW_MODE) ? INTERVIEW_PAGE : -1;
  long start = g_ftell(file);
  int32_t total = 0;
  /* pass 1: size of the RAM arena (a pair counts as 0x20000 in the first two cases, one 8-bit page if selected) */
  for (int32_t i = 0; i < count;) {
    g_fread(&flags, 2, 1, file);
    g_fread(&tex, 2, 1, file);
    int pair = (flags & PAGE_PAIR) != 0;
    if (!pair) {
      g_fseek(file, PAGE16_BYTES, 1);   /* SEEK_CUR */
    } else {
      g_fread(P41_Buf0, PAGE8_BYTES, 1, file);
      g_fread(&tmp16, 2, 1, file);
      g_fread(&tmp16, 2, 1, file);
      g_fseek(file, PAGE8_BYTES, 1);
    }
    if ((flags & PAGE_UPLOAD) == 0) {
      if ((flags & PAGE_UPLOAD_IF) == 0 || tex != S_00D1192C) {
        if (((flags & PAGE_RAM_IF) != 0 && tex == S_00D1192C) || (flags & PAGE_RAM) != 0) total += PAGE16_BYTES;
      } else {
        total += PAGE16_BYTES;
      }
    } else if (i == sel || i == sel2) {
      total += pair ? PAGE8_BYTES : PAGE16_BYTES;
    }
    i += pair ? 2 : 1;
  }
  if (total != 0) {
    p41_ram = (uint8_t *)DebugMalloc(total, "D:\\Driver\\Game\\map.c", 0x225);
#ifdef RE_HOOK_BUILD
    P41_Arena = (uint32_t)(uintptr_t)p41_ram;
#else
    P41_Arena = p41_ram != NULL ? re_ptr_register_dyn(p41_ram, (uint32_t)total) : 0;   /* v2.04: адрес арены — синтетический (re_ptr) */
#endif
    if (p41_ram == NULL) plat_message_box(MAIN_HWND41, "Could not malloc space for RAM texture pages", "ERROR", 0);
  }
  g_fseek(file, start, 0);   /* SEEK_SET: back to the first page record */
  /* pass 2: read, upload, keep RAM copies */
  for (int32_t i = 0; i < count;) {
    int32_t idx = i, nxt = i + 1;
    P27_ReadChunked(&flags, 2, 1, file);
    P27_ReadChunked(&tex, 2, 1, file);
    int pair = (flags & PAGE_PAIR) != 0;
    if (!pair) {
      P27_ReadChunked(P41_Buf0, PAGE16_BYTES, 1, file);
    } else {
      P27_ReadChunked(P41_Buf0, PAGE8_BYTES, 1, file);
      P27_ReadChunked(&tmp16, 2, 1, file);
      P27_ReadChunked(&tmp16, 2, 1, file);
      P27_ReadChunked(P41_Buf1, PAGE8_BYTES, 1, file);
    }
#ifndef RE_HOOK_BUILD
    P86_NativeCapture(idx, pair, P41_Buf0, P41_Buf1);   /* native: страница → текстура GL */
#endif
    int32_t b0 = (int32_t)re_addr(P41_Buf0), b1 = (int32_t)re_addr(P41_Buf1);   /* v2.04: re_addr вместо усечения указателя */
    if ((flags & PAGE_UPLOAD) == 0) {
      if ((flags & PAGE_UPLOAD_IF) == 0) {
        /* RAM-only page.  Quirk kept: a PAGE_UPLOAD_IF page whose tex does not match is skipped here
           although pass 1 may have counted it (via PAGE_RAM / PAGE_RAM_IF). */
        if (((flags & PAGE_RAM_IF) != 0 && tex == S_00D1192C) || (flags & PAGE_RAM) != 0) {
          if (!pair) {
            P40_Slots[idx].flags = 0;
            store_page(idx, P41_Buf0, PAGE16_BYTES);
          } else {
            P40_DownloadPalette(idx, b0);
            P40_DownloadPalette(nxt, b1);
            P40_Slots[idx].flags = 4;
            store_page(idx, P41_Buf0, PAGE8_BYTES);
            P40_Slots[nxt].flags = 0xc;
            store_page(nxt, P41_Buf1, PAGE8_BYTES);
          }
        }
      } else if (tex == S_00D1192C) {
        if (!pair) {
          P40_Slots[idx].flags = 2;
          P40_UploadSlot(idx, b0);
          store_page(idx, P41_Buf0, PAGE16_BYTES);
        } else {
          P40_DownloadPalette(idx, b0);
          P40_DownloadPalette(nxt, b1);
          P40_Slots[idx].flags = 6;
          P40_Slots[nxt].flags = 0xe;
          P40_UploadSlotPair(idx, b0, b1);
          store_page(idx, P41_Buf0, PAGE8_BYTES);
          store_page(nxt, P41_Buf1, PAGE8_BYTES);
        }
      }
    } else if (!pair) {
      P40_Slots[idx].flags = 2;
      P40_UploadSlot(idx, b0);
      if (idx == sel || idx == sel2) {
        store_page(idx, P41_Buf0, PAGE16_BYTES);
        if (idx == sel) P41_Flag = 1;
      }
    } else {
      P40_DownloadPalette(idx, b0);
      P40_DownloadPalette(nxt, b1);
      P40_Slots[idx].flags = 6;
      P40_Slots[nxt].flags = 0xe;
      P40_UploadSlotPair(idx, b0, b1);
      if (idx == sel || idx == sel2) {
        store_page(idx, P41_Buf0, PAGE8_BYTES);
        if (idx == sel) P41_Flag = 0;
      }
      if (nxt == sel || nxt == sel2) {
        store_page(nxt, P41_Buf1, PAGE8_BYTES);
        if (nxt == sel) P41_Flag = 0;
      }
    }
    i += pair ? 2 : 1;
  }
#ifndef RE_HOOK_BUILD
  P86_NativeCaptureEnd();   /* v2.17: итог HD-пака */
#endif
}
