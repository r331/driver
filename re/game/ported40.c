/* Память текстур Glide: сброс, загрузка слотов, палитры — восстановлено из Game.exe. */
#include "reptr.h"
#include "ported40.h"
#include "ported6.h"
#include "ported7.h"
#include "ported58.h"
#include "ported14.h"
#include "unported.h"
#include <string.h>
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P40_00b1c3e0")
#undef P40_00b1c3e0
#pragma push_macro("P40_00b1c3e0") /*gvi*/
#undef P40_00b1c3e0 /*gvi*/
p40_00b1c3e0_t P40_00b1c3e0;
#pragma pop_macro("P40_00b1c3e0") /*gvi*/
#pragma pop_macro("P40_00b1c3e0")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P40_ListPtr")
#undef P40_ListPtr
#pragma push_macro("P40_ListPtr") /*gvi*/
#undef P40_ListPtr /*gvi*/
uint32_t P40_ListPtr;
#pragma pop_macro("P40_ListPtr") /*gvi*/
#pragma pop_macro("P40_ListPtr")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P40_ListCount")
#undef P40_ListCount
#pragma push_macro("P40_ListCount") /*gvi*/
#undef P40_ListCount /*gvi*/
int32_t P40_ListCount;
#pragma pop_macro("P40_ListCount") /*gvi*/
#pragma pop_macro("P40_ListCount")
#endif
#ifdef RE_HOOK_BUILD
#define P40_STD __attribute__((stdcall))
#else
#define P40_STD
#endif

static int32_t find_free_even(void) { /* 0048a4e6 (FindFreeEven_0048A4E6 в ported7 читает свой экземпляр таблицы) */
  for (int32_t i = 0; i <= 0x3f; i += 2) if ((P40_Blocks[i].flags & 7) == 0) return i;
  return -1;
}

static uint32_t glide_addr(const char *name) {
  for (int i = 0; i < P33_GlideCount(); i++) {
    if (strcmp(P33_GlideName(i), name) == 0) {
      uint32_t (P40_STD *f)(uint32_t) = (uint32_t (P40_STD *)(uint32_t))P33_GlideProc(i);
      return f != NULL ? f(0) : 0;
    }
  }
  return 0;
}

void P40_ResetTexMem(void) {
  memset(P40_Blocks, 0, 0x700);
  memset(P40_00b1c3e0, 0, 0x10);
  memset(P40_Slots, 0, 0x1000);
  P12_00b1c3dc = 0;
  P12_00b1c3f0 = -1;
  for (int i = 0; i < 0x100; i++) {
    P40_Slots[i].flags = 0;
    P40_Slots[i].block = 0xff;
    P40_Slots[i].data = 0;
    P40_Slots[i].texaddr = 0;
    P40_Slots[i].info = re_addr(&P40_Blocks[0].info[0]);
  }
  uint32_t a = glide_addr("_grTexMinAddress@4");
  uint32_t max = glide_addr("_grTexMaxAddress@4");
  for (int i = 0; i < 0x40; i++) {
    P40_Block *b = &P40_Blocks[i];
    b->flags = 0;
    b->addr = a;
    b->slot = 0xff;
    b->info[0] = 0;
    b->info[1] = 0;
    b->info[2] = 3;
    b->info[4] = 0;
    b->info[3] = 5;
    if (max <= a) b->flags = 1;
    a += 0x10000;
  }
  for (int i = 0; i < 4; i++) P40_00b1c3e0[i] = -1;
}

/* занять блок b под слот s (одна половина), начальные поля GrTexInfo; format — 0xb (8bpp с альфой?) или 5 */
static void fill_block(int b, int s, int32_t data, int32_t format, uint8_t extra) {
  P40_Block *t = &P40_Blocks[b];
  if (t->slot != 0xff) P40_Slots[t->slot].block = 0xff;
  t->info[0] = 0;
  t->info[1] = 0;
  t->info[2] = 3;
  t->info[4] = data;
  t->info[3] = format;
  t->slot = (uint8_t)s;
  t->flags = (uint8_t)(t->flags | extra | 2);
}

void P40_UploadSlot(int32_t slot, int32_t data) {
  uint8_t extra = 0;
  if (P40_Slots[slot].block != 0xff) return;
  int32_t b = find_free_even();
  if (b == -1) return;
  if ((P40_Slots[slot].flags & 2) != 0) extra = 4;
  if (data == 0) data = (int32_t)P40_Slots[slot].data;
  fill_block(b, slot, data, 0xb, extra);
  Call0042486B(0, P40_Blocks[b].addr, 3, re_addr(&P40_Blocks[b].info[0]), slot);
  P40_Slots[slot].block = (uint8_t)b;
  P40_Slots[slot].texaddr = P40_Blocks[b].addr;
  P40_Slots[slot].info = re_addr(&P40_Blocks[b].info[0]);
  b++;
  /* вторая половина пары: данные — исходные данные слота, загрузки в Glide нет */
  fill_block(b, slot, (int32_t)P40_Slots[slot].data, 0xb, extra);
}

void P40_UploadSlotPair(int32_t slot, int32_t data0, int32_t data1) {
  uint8_t extra = 0;
  if ((P40_Slots[slot].flags & 8) != 0) {
    if ((P40_Slots[slot].flags & 2) != 0) extra = 4;
    slot--;
  }
  if (P40_Slots[slot].block != 0xff) return;
  int32_t b = find_free_even();
  if (b == -1) return;
  if ((P40_Slots[slot].flags & 2) != 0) extra = 4;
  for (int half = 0; half < 2; half++) {
    int32_t data = half == 0 ? data0 : data1;
    if (data == 0) data = (int32_t)P40_Slots[slot].data;
    fill_block(b, slot, data, 5, extra);
    Call0042486B(0, P40_Blocks[b].addr, 3, re_addr(&P40_Blocks[b].info[0]), slot);
    P40_Slots[slot].block = (uint8_t)b;
    P40_Slots[slot].texaddr = P40_Blocks[b].addr;
    P40_Slots[slot].info = re_addr(&P40_Blocks[b].info[0]);
    b++;
    slot++;
  }
}

/* v2.04: таблица 00b31ee8 читается как P58_Tab4EFC03/P58_Cnt4EFC03 (p58_rec_t: в hook — та же 12-байтная запись,
   в native — родные указатели, которые пишет P126_ReadMapPals); прежнее чтение uint32 P40_ListPtr как указателя в native
   давало SIGSEGV (псевдоним в образе данных = 0 при ненулевом счётчике). Адрес палитры — re_addr (в hook тождество). */
void P40_DownloadPalette(int32_t slot, int32_t palette) {
  const p58_rec_t *rec = P58_Tab4EFC03;
  int32_t n = rec != NULL ? P58_Cnt4EFC03 : 0;
  for (int i = 0; i < n; i++, rec++) {
    if (rec->a != slot) continue;
    const int32_t *list = (const int32_t *)rec->p;
    for (int j = 0; list != NULL && j < rec->c; j++, list++) {
#ifndef RE_HOOK_BUILD
      if ((uint32_t)*list >= 64u) continue;   /* защита: слот палитры вне таблицы 01252be0 */
#endif
      Fwd0042482B(slot, palette, *list, (int32_t)re_addr(&P14_01252be0[*list * 0x400]));
    }
    return;
  }
  Fwd0042482B(slot, palette, 1, (int32_t)re_addr(&P14_01252be0[0x400]));
}
