/* ported15.c — small stateful helpers: highlight handlers of a 7-entry menu (004142a4..004145da),
   menu highlight range, model vertex scaling, integer skipping in text parsing, 16/8-bit rectangle
   copies inside 256-pixel-wide texture pages, flag clearing on a linked list, a 5x3 map grid lookup,
   and the interview (Undercover garage test) score bump.  Pointers inside game structures are 32-bit
   Game.exe addresses (re_ptr / P79_PTR translate them in native). */
#include "ported15.h"
#include "reptr.h"
#include "ported79.h"
#include <string.h>
#include "memrw.h"
#ifdef RE_HOOK_BUILD   /* v2.35: native — the image cell P53_MenuSel (ported15.h) */
GAME_VAR_DEF(int32_t, P15_MenuSel, 0x01271064)
#endif
#ifndef RE_HOOK_BUILD
p15_listcur_u P15_ListCurU;   /* v2.35: 00d12410 — P15_ListCur and S_00D12410 */
#endif
#ifndef RE_HOOK_BUILD /* v2.21 gvar-img */
#pragma push_macro("P15_State")
#undef P15_State
int32_t P15_State;
#pragma pop_macro("P15_State")
#else
GAME_VAR_DEF(int32_t, P15_State, 0x00b87e30)
#endif
#ifndef RE_HOOK_BUILD /* v2.21 gvar-img */
#pragma push_macro("P15_Flags9")
#undef P15_Flags9
P15_u8x9 P15_Flags9;
#pragma pop_macro("P15_Flags9")
#else
GAME_VAR_DEF(P15_u8x9, P15_Flags9, 0x00d04a50)
#endif
#ifndef RE_HOOK_BUILD /* v2.25 gvar-img */
#pragma push_macro("P15_Vals9")
#undef P15_Vals9
P15_i32x9 P15_Vals9;
#pragma pop_macro("P15_Vals9")
#else
GAME_VAR_DEF(P15_i32x9, P15_Vals9, 0x00d044a0)
#endif
#ifdef RE_HOOK_BUILD   /* v2.35: native — a view of P55_Paper1 (ported15.h) */
GAME_VAR_DEF(uint8_t *, P15_Limits, 0x00d0448c)
#endif

static void w32(uint8_t *p, uint32_t v) { memcpy(p, &v, 4); }
static uint32_t r32(const uint8_t *p) { uint32_t v; memcpy(&v, p, 4); return v; }
#define MENU_ITEM_SIZE    0x10   /* one entry of the P15_MenuItems array */
#define MENU_ITEM_STATE   4      /* u8: entry state; the handlers below set 3 (TODO(RE): unsure — "highlighted") */
#define MENU_ITEM_FLAGS   5      /* u8: bit 3 (MENU_FLAG_LIT) set by P15_SetHighlightRange */
#define MENU_FLAG_LIT     8
#define LIST_FLAGS        0x00   /* u16 flags of a P15_ListHead node: bit 1 = active, bit 3 = tagged-clearable */
#define LIST_TAG          0x06   /* u16 tag compared by P15_ListClearActiveByTag */
#define LIST_NEXT         0x20   /* u32 Game.exe address of the next node */
#define LIST_F_ACTIVE     2
#define LIST_F_BYTAG      8
#define MODEL_VERT_COUNT  0x14   /* u16: vertex count of a model */
#define MODEL_NORM_COUNT  0x16   /* u16: normal count */
#define MODEL_VERTS       0x20   /* arena reference of the vertex array (16 bytes per vertex: x, y, z, pad) */
#define MODEL_NORMS       0x24   /* arena reference of the normal array (16 bytes: x, y, z, w) */
#define TPAGE_PITCH16     0x200  /* bytes per row of a 256-pixel 16-bit texture page */
#define TPAGE_PITCH8      0x100  /* bytes per row of a 256-pixel 8-bit texture page */
#define INTERVIEW_STATE   4      /* P15_State value while the Undercover interview runs */
#define INTERVIEW_TASKS   9      /* manoeuvres in the interview (P15_Flags9 / P15_Vals9) */

static uint8_t *rp(const uint8_t *p) { return (uint8_t *)re_ptr((uint32_t)r32(p)); }   /* v1.42: поле-указатель = адрес Game.exe */

/* заголовок подсказки: +0 ширина u16, +2 высота u16... фактически: u16 w@0, u16 h@2, u32 text@4 */
/* Writes the hint header P15_MenuText: text address (Game.exe .data string) and the two u16 values
   a, b (TODO(RE): unsure — width/height per the note above, or x/y position). */
static void set_hint(uint32_t text_addr, uint16_t a, uint16_t b) {
  if (P15_MenuText) { w32(P15_MenuText + 4, text_addr); wr16(P15_MenuText, a); wr16(P15_MenuText + 2, b); }
}

/* P15_MenuMiami .. P15_MenuItem7 — Game.exe 004142a4, 004142fc, 004143b6, 0041440e, 004144c8, 00414520,
   004145da.  Selection handlers of one 7-entry menu (the first is named after Miami, the first city):
   each sets its hint text (strings at 0054da1c..0054da38) and marks one entry (state byte = 3) and
   P15_MenuSel.  Entries 2, 4 and 6 depend on P15_MenuMode: mode 1 selects the entry itself, modes 0 and 2
   fall back to the entry one step earlier, any other mode only sets the hint.
   (Entry k is P15_MenuItems[k * 0x10 + 4], P15_MenuSel = k - 1.)  TODO(RE): unsure which menu this is
   and what the modes mean. */
void P15_MenuMiami(void) {
  set_hint(0x0054da1c, 0x147, 0xb6);
  P15_MenuItems[0x24] = 3; P15_MenuSel = 1;
}
void P15_MenuItem2(void) {
  set_hint(0x0054da24, 0x148, 0x9a);
  if (P15_MenuMode != 0) {
    if (P15_MenuMode == 1) { P15_MenuItems[0x34] = 3; P15_MenuSel = 2; return; }
    if (P15_MenuMode != 2) return;
  }
  P15_MenuItems[0x24] = 3; P15_MenuSel = 1;
}
void P15_MenuItem3(void) {
  set_hint(0x0054da28, 0x148, 0x9a);
  P15_MenuItems[0x44] = 3; P15_MenuSel = 3;
}
void P15_MenuItem4(void) {
  set_hint(0x0054da2c, 0x148, 200);
  if (P15_MenuMode != 0) {
    if (P15_MenuMode == 1) { P15_MenuItems[0x54] = 3; P15_MenuSel = 4; return; }
    if (P15_MenuMode != 2) return;
  }
  P15_MenuItems[0x34] = 3; P15_MenuSel = 2;
}
void P15_MenuItem5(void) {
  set_hint(0x0054da30, 0x148, 200);
  P15_MenuItems[100] = 3; P15_MenuSel = 5;
}
void P15_MenuItem6(void) {
  set_hint(0x0054da34, 0x147, 0x8a);
  if (P15_MenuMode != 0) {
    if (P15_MenuMode == 1) { P15_MenuItems[0x74] = 3; P15_MenuSel = 6; return; }
    if (P15_MenuMode != 2) return;
  }
  P15_MenuItems[0x44] = 3; P15_MenuSel = 3;
}
void P15_MenuItem7(void) {
  set_hint(0x0054da38, 0x147, 0x8a);
  P15_MenuItems[0x84] = 3; P15_MenuSel = 7;
}
/* P15_SetHighlightRange — Game.exe 004148b9.  Clears flag bit 3 of menu entries 0..from-1 and sets it on
   entries from..to (inclusive); entries after `to` are left alone. */
void P15_SetHighlightRange(int32_t from, int32_t to) {
  for (int32_t i = 0; i < from; i++) P15_MenuItems[MENU_ITEM_FLAGS + i * MENU_ITEM_SIZE] &= 0xf7;   /* ~MENU_FLAG_LIT */
  for (int32_t i = from; i <= to; i++) P15_MenuItems[MENU_ITEM_FLAGS + i * MENU_ITEM_SIZE] |= MENU_FLAG_LIT;
}
/* v2.04: поля модели +0x20/+0x24 — ссылки арены карты (P79_PTR: в native смещение от D_00c98ed0, в hook — адрес),
   а не адреса re_ptr: прежнее re_ptr(смещение) давало NULL/чужую память → SIGSEGV в P101_SkyInit при загрузке уровня. */
/* Model field holding a map-arena reference -> pointer (NULL for 0). */
static uint8_t *mp(const uint8_t *p) { uint32_t v = r32(p); return v != 0 ? (uint8_t *)P79_PTR(v) : NULL; }
/* P15_ScaleVertices — Game.exe 00427a08.  Multiplies x, y, z of every vertex of model obj by sx, sy, sz
   in place. */
void P15_ScaleVertices(uint8_t *obj, float sx, float sy, float sz) {
  uint8_t *v = mp(obj + MODEL_VERTS);
  if (v == NULL) return;
  for (int i = 0; i < (int)rdu16(obj + MODEL_VERT_COUNT); i++, v += 16) {
    wrf(v, sx * rdf(v)); wrf(v + 4, sy * rdf(v + 4)); wrf(v + 8, sz * rdf(v + 8));
  }
}
/* P15_ScaleNormalW — Game.exe 00427a71.  Multiplies the 4th float (+12) of every entry of the model's
   normal/plane array by s — for a plane (nx, ny, nz, d) that is the distance term, matching a scaled
   model.  TODO(RE): unsure the array holds planes rather than plain normals. */
void P15_ScaleNormalW(uint8_t *obj, float s) {
  uint8_t *v = mp(obj + MODEL_NORMS);
  if (v == NULL) return;
  for (int i = 0; i < (int)rdu16(obj + MODEL_NORM_COUNT); i++, v += 16) wrf(v + 12, s * rdf(v + 12));
}
/* P15_SkipInteger — Game.exe 004a50a2.  Advances *p past an optional '-' and the following digits. */
void P15_SkipInteger(char **p) {
  if (**p == '-') (*p)++;
  while ((uint8_t)**p > 0x2f && (uint8_t)**p < 0x3a) (*p)++;   /* '0'..'9' */
}
/* P15_BlitRect16 — Game.exe 004c16d9.  Copies a w x h rectangle of 16-bit pixels from (sx, sy) of page
   src to (dx, dy) of page dst; both pages are 256 pixels wide.  Like the original's do/while, h == 0
   is treated as "at least one row" (and then runs on until h wraps). */
void P15_BlitRect16(uint8_t *src, int sx, int sy, uint32_t w, int h, uint8_t *dst, int dx, int dy) {
  const uint8_t *s = src + sy * TPAGE_PITCH16 + sx * 2;
  uint8_t *d = dst + dy * TPAGE_PITCH16 + dx * 2;
  do {
    memcpy(d, s, (size_t)w * 2);
    s += TPAGE_PITCH16; d += TPAGE_PITCH16; h--;
  } while (h != 0);
}
/* P15_BlitRect8 — Game.exe 004c1749.  Same as P15_BlitRect16 for 8-bit pages (256 bytes per row). */
void P15_BlitRect8(uint8_t *src, int sx, int sy, uint32_t w, int h, uint8_t *dst, int dx, int dy) {
  const uint8_t *s = src + sy * TPAGE_PITCH8 + sx;
  uint8_t *d = dst + dy * TPAGE_PITCH8 + dx;
  do {
    memcpy(d, s, w);
    s += TPAGE_PITCH8; d += TPAGE_PITCH8; h--;
  } while (h != 0);
}
/* P15_ListClearActiveByTag — Game.exe 004cff20.  Walks the list P15_ListHead and clears the active bit
   (bit 1) of every node that is active, has bit 3 set and carries tag `tag`.  TODO(RE): unsure what the
   list holds (the project notes call 00d12408 a split data-image alias that is empty in native). */
void P15_ListClearActiveByTag(uint32_t tag) {
  for (uint8_t *n = P15_ListHead; n; n = rp(n + LIST_NEXT)) {
    uint16_t f = rdu16(n + LIST_FLAGS);
    if ((f & LIST_F_ACTIVE) && (f & LIST_F_BYTAG) && rdu16(n + LIST_TAG) == tag) wr16(n, f & 0xfffd);
  }
}
/* P15_ListClearAllActive — Game.exe 004d0021.  Clears the active bit of every node of P15_ListHead; the
   walk uses the global cursor P15_ListCur (left NULL at the end), as the original does. */
void P15_ListClearAllActive(void) {
  for (P15_ListCur = P15_ListHead; P15_ListCur; P15_ListCur = rp(P15_ListCur + LIST_NEXT)) {
    uint16_t f = rdu16(P15_ListCur + LIST_FLAGS);
    if (f & LIST_F_ACTIVE) wr16(P15_ListCur, f & 0xfffd);
  }
}
/* P15_GridCell — Game.exe 004e58ba.  Maps a world position to one of 15 cells of a 3 (x) by 5 (y) grid:
   row = 0..4 by y thresholds -0x28db, -0x3493, -0x404b, -0x4c03 (smaller y = higher row), column = 0..2
   by x thresholds -0x1d1c, -0x34d5; returns row * 3 + column.  TODO(RE): unsure what the grid is for
   (which map, which coordinate pair). */
int32_t P15_GridCell(int32_t x, int32_t y) {
  int32_t r = 0;
  if (y < -0x28db) {
    if (y < -0x3493) { if (y < -0x404b) r = (y < -0x4c03) ? 12 : 9; else r = 6; }
    else r = 3;
  }
  if (x < -0x1d1c) r += (x < -0x34d5) ? 2 : 1;
  return r;
}
/* P15_RaiseLimits — Game.exe 004e5f5b.  During the interview (P15_State == 4): for each of the 9 tasks
   whose flag is set, raises its value by 3, capped at byte +0xb of the LINE badge record whose address
   is stored at 00d0448c.  (P15_Vals9 are the interview "paper" bars, also read by P114_PaperMark.) */
void P15_RaiseLimits(void) {
  if (P15_State == INTERVIEW_STATE) {
    for (int i = 0; i < INTERVIEW_TASKS; i++) {
      if (P15_Flags9[i]) {
#ifndef RE_HOOK_BUILD
        /* v2.25: 00d0448c — 32-битный адрес значка LINE (P55_LoadPaper пишет его в ячейку образа P55_Paper1), а не native-указатель:
           отдельный объект P15_Limits был NULL → SIGSEGV на первом засчитанном манёвре интервью */
        const uint8_t *limp = P15_Limits;   /* v2.35: a view of the image cell P55_Paper1 (ported15.h) */
        if (limp == NULL) continue;
        uint8_t lim = limp[0xb];
#else
        uint8_t lim = P15_Limits[0xb];
#endif
        P15_Vals9[i] += 3;
        if ((int32_t)lim < P15_Vals9[i]) P15_Vals9[i] = lim;
      }
    }
  }
}
