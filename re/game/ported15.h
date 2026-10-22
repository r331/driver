#pragma once
#include "gvar.h"
#include <stdint.h>
/* Функции с простым состоянием (меню-обработчики, копирование прямоугольников, списки). Указатели
   в игровых структурах — 32-битные (хук-сборка 32-бит); в native эти функции не вызываются. */
#define P15_VAR(type, name, addr) \
  GAME_VAR(type, name, addr)
#define P15_MenuText     P15_VAR(uint8_t *, P15_MenuText, 0x005fe9b0)
#define P15_MenuItems    P15_VAR(uint8_t *, P15_MenuItems, 0x005fe9b8)
#define P15_MenuMode     P15_VAR(int32_t, P15_MenuMode, 0x005fe9bc)
#define P15_MenuSel      P15_VAR(int32_t, P15_MenuSel, 0x01271064)
#define P15_ListHead     P15_VAR(uint8_t *, P15_ListHead, 0x00d12408)
#define P15_ListCur      P15_VAR(uint8_t *, P15_ListCur, 0x00d12410)
#define P15_State        P15_VAR(int32_t, P15_State, 0x00b87e30)
#define P15_Flags9       P15_VAR(P15_u8x9, P15_Flags9, 0x00d04a50)
#define P15_Vals9        P15_VAR(P15_i32x9, P15_Vals9, 0x00d044a0)
#define P15_Limits       P15_VAR(uint8_t *, P15_Limits, 0x00d0448c)
typedef uint8_t P15_u8x9[9];
typedef int32_t P15_i32x9[9];
#ifndef RE_HOOK_BUILD
extern int32_t P15_State;
extern P15_u8x9 P15_Flags9; extern P15_i32x9 P15_Vals9;
#endif
void P15_MenuMiami(void);      /* 004142a4 */
void P15_MenuItem2(void);      /* 004142fc */
void P15_MenuItem3(void);      /* 004143b6 */
void P15_MenuItem4(void);      /* 0041440e */
void P15_MenuItem5(void);      /* 004144c8 */
void P15_MenuItem6(void);      /* 00414520 */
void P15_MenuItem7(void);      /* 004145da */
void P15_SetHighlightRange(int32_t from, int32_t to); /* 004148b9 */
void P15_ScaleVertices(uint8_t *obj, float sx, float sy, float sz); /* 00427a08 */
void P15_ScaleNormalW(uint8_t *obj, float s);  /* 00427a71 */
void P15_SkipInteger(char **p);                /* 004a50a2 */
void P15_BlitRect16(uint8_t *src, int sx, int sy, uint32_t w, int h, uint8_t *dst, int dx, int dy); /* 004c16d9 */
void P15_BlitRect8(uint8_t *src, int sx, int sy, uint32_t w, int h, uint8_t *dst, int dx, int dy);  /* 004c1749 */
void P15_ListClearActiveByTag(uint32_t tag);   /* 004cff20 */
void P15_ListClearAllActive(void);             /* 004d0021 */
int32_t P15_GridCell(int32_t x, int32_t y);    /* 004e58ba */
void P15_RaiseLimits(void);                    /* 004e5f5b */
/* v2.21: ячейки образа данных — один объект на адрес. Раньше эти имена были отдельными native-переменными (tools/gen_gvar_img.py
   не разбирает обёртку P15_VAR/P16_VAR), и запись через другой псевдоним (D_00b87e30, P14_00c810c4, G6_00B5A778 …) через них не была
   видна: так, интервью Undercover (ladder пишет D_00b87e30 = 4) не запускалось — P56_HudTick/P145_LevelLoad проверяли P15_State.
   Пары: P15_State = D_00b87e30 (режим: 4 — интервью), P15_Flags9 = G6_00D04A50/P59_Flags9. */
#if !defined(RE_HOOK_BUILD) && !defined(RE_GVAR_PLAIN)
#undef P15_State
#define P15_State (*(int32_t *)re_gvar(0x00b87e30u, sizeof(int32_t), (void *)&P15_State))
#undef P15_Flags9
#define P15_Flags9 (*(P15_u8x9 *)re_gvar(0x00d04a50u, sizeof(P15_u8x9), (void *)&P15_Flags9))
/* v2.25: полосы «бумаги» интервью 00d044a0 (P114_PaperMark читает их же) — тоже ячейка образа */
#undef P15_Vals9
#define P15_Vals9 (*(P15_i32x9 *)re_gvar(0x00d044a0u, sizeof(P15_i32x9), (void *)&P15_Vals9))
#endif
/* v2.35: split aliases merged — one object per Game.exe address (native only; the hook build keeps the plain GAME_VAR above).
   005fe9b0 / 005fe9b8: 32-bit addresses in the data-image cells P58_S5FE9B0 / P58_S5FE9B8 (P100_MenuSetup writes them);
     P15_MenuText / P15_MenuItems are read-only views through re_ptr.
   005fe9bc: P15_MenuMode is the image cell G6_005FE9BC.
   00d12408: head of the event-script list — the image cell G00D12408 holds the 32-bit address of the first node (ported122,
     command 0x7a, appends to it); P15_ListHead is a read-only view, P15_SetListHead writes the cell.  Before v2.35 the native
     P15_ListHead was a separate, always NULL object: 004f5012 (P98_ScriptRange), 004f4f10, 004d0102 (free), 004a4340 and the
     script walks of ported97/112 saw an empty list.
   01271064: P15_MenuSel is the image cell P53_MenuSel / P62_Menu1271064 (the highlight handlers 004142a4..004145da set the
     selected row there; before v2.35 they wrote a separate native object nobody read).
   00d0448c: 32-bit address of the LINE badge in the image cell P55_Paper1 (v2.25 read it directly); P15_Limits is a view.
   00d12410: current node — one native pointer, P15_ListCur (uint8_t *) and S_00D12410 (uint16_t *) are two members of the
     union P15_ListCurU. */
#ifndef RE_HOOK_BUILD
#include "reptr.h"
#pragma push_macro("P58_S5FE9B0")
#undef P58_S5FE9B0
#pragma push_macro("P58_S5FE9B8")
#undef P58_S5FE9B8
#pragma push_macro("G6_005FE9BC")
#undef G6_005FE9BC
#pragma push_macro("G00D12408")
#undef G00D12408
#pragma push_macro("P55_Paper1")
#undef P55_Paper1
#pragma push_macro("P53_MenuSel")
#undef P53_MenuSel
extern uint32_t P58_S5FE9B0, P58_S5FE9B8; extern int32_t G6_005FE9BC; extern int32_t G00D12408; extern int32_t P55_Paper1;
extern int32_t P53_MenuSel;
#pragma pop_macro("P53_MenuSel")
#pragma pop_macro("P55_Paper1")
#pragma pop_macro("G00D12408")
#pragma pop_macro("G6_005FE9BC")
#pragma pop_macro("P58_S5FE9B8")
#pragma pop_macro("P58_S5FE9B0")
typedef union { uint8_t *b; uint16_t *w; } p15_listcur_u;
extern p15_listcur_u P15_ListCurU;
#define P15_CELL(type, addr, fb) (*(type *)re_gvar(addr, sizeof(type), (void *)&fb))
#undef P15_MenuText
#define P15_MenuText  ((uint8_t *)re_ptr(P15_CELL(uint32_t, 0x005fe9b0u, P58_S5FE9B0)))
#undef P15_MenuItems
#define P15_MenuItems ((uint8_t *)re_ptr(P15_CELL(uint32_t, 0x005fe9b8u, P58_S5FE9B8)))
#undef P15_MenuMode
#define P15_MenuMode  P15_CELL(int32_t, 0x005fe9bcu, G6_005FE9BC)
#undef P15_ListHead
#define P15_ListHead  ((uint8_t *)re_ptr((uint32_t)P15_CELL(int32_t, 0x00d12408u, G00D12408)))
#define P15_SetListHead(p) (P15_CELL(int32_t, 0x00d12408u, G00D12408) = (int32_t)re_addr(p))
#undef P15_ListCur
#define P15_ListCur   (P15_ListCurU.b)
#undef P15_MenuSel
#define P15_MenuSel   P15_CELL(int32_t, 0x01271064u, P53_MenuSel)
#undef P15_Limits
#define P15_Limits    ((uint8_t *)re_ptr(P15_CELL(uint32_t, 0x00d0448cu, P55_Paper1)))
#else
#define P15_SetListHead(p) (P15_ListHead = (p))
#endif
