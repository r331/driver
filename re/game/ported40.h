#pragma once
#include "gvar.h"
#include "ported12.h"
#include "ported14.h"
#include "ported33.h"
#include <stdint.h>
/* Память текстур Glide (3Dfx): таблица слотов текстур игры (0x100 по 0x10 байт, 01145a60) и таблица блоков памяти
   карты (0x40 по 0x1c байт, 01146f20; блок 0x10000, чётный+нечётный — пара для текстуры 256x256 в 2 частях).
   Все функции __cdecl. Адреса в таблицах — 32-битные (как в Game.exe). Убраны из unported: 00489d20, 0048a239, 00489f50. */
#pragma pack(push, 1)
typedef struct {
  uint8_t  flags;     /* +0: признаки; бит1 (2) — влияет на extra=4, бит3 (8) — вторая часть пары */
  uint8_t  block;     /* +1: номер блока памяти текстур или 0xff */
  uint8_t  pad[2];
  uint32_t data;      /* +4: исходные данные */
  uint32_t texaddr;   /* +8: адрес в памяти текстур */
  uint32_t info;      /* +0xc: указатель на GrTexInfo блока */
} P40_Slot;
typedef struct {
  uint8_t  flags;     /* +0: бит0 — за пределами памяти текстур, бит1 — занят, бит2 — флаг из слота */
  uint8_t  slot;      /* +1: номер слота текстуры или 0xff */
  uint8_t  pad[2];
  uint32_t addr;      /* +4: адрес в памяти текстур */
  int32_t  info[5];   /* +8: GrTexInfo: smallLod, largeLod, aspect, format, data */
} P40_Block;
#pragma pack(pop)
_Static_assert(sizeof(P40_Slot) == 0x10, "P40_Slot");
_Static_assert(sizeof(P40_Block) == 0x1c, "P40_Block");
typedef int32_t p40_00b1c3e0_t[4];
#define P40_00b1c3e0 GAME_VAR(p40_00b1c3e0_t, P40_00b1c3e0, 0x00b1c3e0)
#ifndef RE_HOOK_BUILD
#pragma push_macro("P40_00b1c3e0") /*gvi*/
#undef P40_00b1c3e0 /*gvi*/
extern p40_00b1c3e0_t P40_00b1c3e0;
#pragma pop_macro("P40_00b1c3e0") /*gvi*/
#endif
#define P40_ListPtr   GAME_VAR(uint32_t, P40_ListPtr, 0x00b31ee8)   /* записи по 12 байт: слот, указатель на список палитр, число */
#define P40_ListCount GAME_VAR(int32_t, P40_ListCount, 0x00b31eec)
#ifndef RE_HOOK_BUILD
#pragma push_macro("P40_ListPtr") /*gvi*/
#undef P40_ListPtr /*gvi*/
#pragma push_macro("P40_ListCount") /*gvi*/
#undef P40_ListCount /*gvi*/
extern uint32_t P40_ListPtr; extern int32_t P40_ListCount;
#pragma pop_macro("P40_ListCount") /*gvi*/
#pragma pop_macro("P40_ListPtr") /*gvi*/
#endif
#define P40_Slots  ((P40_Slot *)(void *)P12_01145a60)
#define P40_Blocks ((P40_Block *)(void *)P12_01146f20)
void P40_ResetTexMem(void);                       /* 00489d20: сброс таблиц слотов и блоков; границы памяти из grTexMin/MaxAddress */
void P40_UploadSlot(int32_t slot, int32_t data);  /* 0048a239: загрузить 16-битную (ARGB_1555) страницу слота в свободную пару блоков (data=0 → данные слота) */
void P40_UploadSlotPair(int32_t slot, int32_t data0, int32_t data1); /* 00489f50: то же для пары слотов (двойной) */
void P40_DownloadPalette(int32_t slot, int32_t palette); /* 004efc7c: отправить палитру в Glide по записи списка палитр слота */
/* gvar-img v2.03 begin (tools/gen_gvar_img.py) */
#if !defined(RE_HOOK_BUILD) && !defined(RE_GVAR_PLAIN)
#undef P40_00b1c3e0
#define P40_00b1c3e0 (*(p40_00b1c3e0_t *)re_gvar(0x00b1c3e0u, sizeof(p40_00b1c3e0_t), (void *)&P40_00b1c3e0))
#undef P40_ListPtr
#define P40_ListPtr (*(uint32_t *)re_gvar(0x00b31ee8u, sizeof(uint32_t), (void *)&P40_ListPtr))
#undef P40_ListCount
#define P40_ListCount (*(int32_t *)re_gvar(0x00b31eecu, sizeof(int32_t), (void *)&P40_ListCount))
#endif
/* gvar-img v2.03 end */
