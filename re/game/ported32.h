#pragma once
#include "gvar.h"
#include "../platform/plat.h"
#include "ported24.h"
#include "ported6.h"   /* G6_0054EF2C — номер текущей палитры, G6_00A421F0 */
#include <stdint.h>
/* Z-буфер и палитры текстур Direct3D (Render.c) — над plat_dd_* / plat_set_texture. Функции __cdecl; 0041f57d в оригинале stdcall (ret 0xc) — переходник ставит re_hook. */
typedef struct P32_Node {   /* узел списка палитр слота */
  int32_t first;            /* +00 (в первом узле — значение для сообщения) */
  int32_t id;               /* +04 номер палитры */
  int32_t pad[3];           /* +08 */
  void *handle;             /* +14 палитра для SetTexture */
  struct P32_Node *next;    /* +18 */
} P32_Node;
#ifdef RE_HOOK_BUILD
_Static_assert(offsetof(P32_Node, handle) == 0x14 && offsetof(P32_Node, next) == 0x18, "P32_Node");
#endif
typedef struct {            /* 32 байта на слот текстуры; таблица с 0x00621c48 (поля c48…c64), 32 слота */
  void *surf;               /* +00 (c48) поверхность текстуры */
  void *tex;                /* +04 (c4c) IDirect3DTexture2 */
  void *pal;                /* +08 (c50) IDirectDrawPalette (8 бит) */
  int32_t bpp;              /* +0c (c54) */
  int32_t has_list;         /* +10 (c58) есть список палитр */
  int32_t cur_id;           /* +14 (c5c) текущий номер палитры */
  P32_Node *list;            /* +18 (c60) список узлов палитр */
  void *cur_handle;         /* +1c (c64) текущая палитра для SetTexture */
} P32_Slot;
#ifdef RE_HOOK_BUILD
_Static_assert(sizeof(P32_Slot) == 32, "P32_Slot");
#endif
typedef P32_Slot P32_SlotArr[32];
typedef uint8_t P32_PalArr[1024];
#define P32_Slots   GAME_VAR(P32_SlotArr, P32_Slots, 0x00621c48)
#define P32_PalTable GAME_VAR(P32_PalArr, P32_PalTable, 0x006017c0)   /* 256 x RGBA (PALETTEENTRY: R,G,B,flags=2) */
#define P32_DevInfo GAME_VAR(uint8_t *, P32_DevInfo, 0x00a42150)      /* описание устройства: +0x518 флаг, +0x568 DDPIXELFORMAT Z-буфера */
#define P32_CurSlot GAME_VAR(int32_t, P32_CurSlot, 0x0054ef30)
#define P32_CurHandle GAME_VAR(void *, P32_CurHandle, 0x00a42178)
typedef char P32_MsgArr[256];
#define P32_Msg     GAME_VAR(P32_MsgArr, P32_Msg, 0x00a42048)             /* буфер сообщения */
#ifndef RE_HOOK_BUILD
#pragma push_macro("P32_PalTable") /*gvi*/
#undef P32_PalTable /*gvi*/
extern P32_SlotArr P32_Slots; extern P32_PalArr P32_PalTable; extern uint8_t *P32_DevInfo;
#pragma pop_macro("P32_PalTable") /*gvi*/
#pragma push_macro("P32_CurSlot") /*gvi*/
#undef P32_CurSlot /*gvi*/
#pragma push_macro("P32_Msg") /*gvi*/
#undef P32_Msg /*gvi*/
extern int32_t P32_CurSlot; extern void *P32_CurHandle; extern P32_MsgArr P32_Msg;
#pragma pop_macro("P32_Msg") /*gvi*/
#pragma pop_macro("P32_CurSlot") /*gvi*/
#endif
int32_t P32_CreateZSurface(void *back);                /* 004213dc: Z-буфер размером с заднюю поверхность, прикрепить */
int32_t P32_CreateSlotPalette(int32_t slot);           /* 00422309: палитра 8-бит текстуры слота (создать/привязать/SetEntries) */
void    P32_SelectSlotPalette(int32_t slot);           /* 00422c55: выбрать палитру слота по P32_CurPal и поставить как текстуру */
void P32_SetPalette(int32_t a, int32_t mode, const uint8_t *rgba256); /* 0041f57d: загрузить палитру в таблицу и обновить все слоты */
/* gvar-img v2.03 begin (tools/gen_gvar_img.py) */
#if !defined(RE_HOOK_BUILD) && !defined(RE_GVAR_PLAIN)
#undef P32_PalTable
#define P32_PalTable (*(P32_PalArr *)re_gvar(0x006017c0u, sizeof(P32_PalArr), (void *)&P32_PalTable))
#undef P32_CurSlot
#define P32_CurSlot (*(int32_t *)re_gvar(0x0054ef30u, sizeof(int32_t), (void *)&P32_CurSlot))
#undef P32_Msg
#define P32_Msg (*(P32_MsgArr *)re_gvar(0x00a42048u, sizeof(P32_MsgArr), (void *)&P32_Msg))
#endif
/* gvar-img v2.03 end */
