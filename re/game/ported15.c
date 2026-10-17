#include "ported15.h"
#include "reptr.h"
#include "ported79.h"
#include <string.h>
GAME_VAR_DEF(uint8_t *, P15_MenuText, 0x005fe9b0)
GAME_VAR_DEF(uint8_t *, P15_MenuItems, 0x005fe9b8)
GAME_VAR_DEF(int32_t, P15_MenuMode, 0x005fe9bc)
GAME_VAR_DEF(int32_t, P15_MenuSel, 0x01271064)
GAME_VAR_DEF(uint8_t *, P15_ListHead, 0x00d12408)
GAME_VAR_DEF(uint8_t *, P15_ListCur, 0x00d12410)
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
GAME_VAR_DEF(P15_i32x9, P15_Vals9, 0x00d044a0)
GAME_VAR_DEF(uint8_t *, P15_Limits, 0x00d0448c)

static uint16_t r16(const uint8_t *p) { uint16_t v; memcpy(&v, p, 2); return v; }
static void w16(uint8_t *p, uint16_t v) { memcpy(p, &v, 2); }
static void w32(uint8_t *p, uint32_t v) { memcpy(p, &v, 4); }
static uint32_t r32(const uint8_t *p) { uint32_t v; memcpy(&v, p, 4); return v; }
static float rf(const uint8_t *p) { float v; memcpy(&v, p, 4); return v; }
static void wf(uint8_t *p, float v) { memcpy(p, &v, 4); }
static uint8_t *rp(const uint8_t *p) { return (uint8_t *)re_ptr((uint32_t)r32(p)); }   /* v1.42: поле-указатель = адрес Game.exe */

/* заголовок подсказки: +0 ширина u16, +2 высота u16... фактически: u16 w@0, u16 h@2, u32 text@4 */
static void set_hint(uint32_t text_addr, uint16_t a, uint16_t b) {
  if (P15_MenuText) { w32(P15_MenuText + 4, text_addr); w16(P15_MenuText, a); w16(P15_MenuText + 2, b); }
}

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
void P15_SetHighlightRange(int32_t from, int32_t to) {
  for (int32_t i = 0; i < from; i++) P15_MenuItems[5 + i * 0x10] &= 0xf7;
  for (int32_t i = from; i <= to; i++) P15_MenuItems[5 + i * 0x10] |= 8;
}
/* v2.04: поля модели +0x20/+0x24 — ссылки арены карты (P79_PTR: в native смещение от D_00c98ed0, в hook — адрес),
   а не адреса re_ptr: прежнее re_ptr(смещение) давало NULL/чужую память → SIGSEGV в P101_SkyInit при загрузке уровня. */
static uint8_t *mp(const uint8_t *p) { uint32_t v = r32(p); return v != 0 ? (uint8_t *)P79_PTR(v) : NULL; }
void P15_ScaleVertices(uint8_t *obj, float sx, float sy, float sz) {
  uint8_t *v = mp(obj + 0x20);
  if (v == NULL) return;
  for (int i = 0; i < (int)r16(obj + 0x14); i++, v += 16) {
    wf(v, sx * rf(v)); wf(v + 4, sy * rf(v + 4)); wf(v + 8, sz * rf(v + 8));
  }
}
void P15_ScaleNormalW(uint8_t *obj, float s) {
  uint8_t *v = mp(obj + 0x24);
  if (v == NULL) return;
  for (int i = 0; i < (int)r16(obj + 0x16); i++, v += 16) wf(v + 12, s * rf(v + 12));
}
void P15_SkipInteger(char **p) {
  if (**p == '-') (*p)++;
  while ((uint8_t)**p > 0x2f && (uint8_t)**p < 0x3a) (*p)++;
}
void P15_BlitRect16(uint8_t *src, int sx, int sy, uint32_t w, int h, uint8_t *dst, int dx, int dy) {
  const uint8_t *s = src + sy * 0x200 + sx * 2;
  uint8_t *d = dst + dy * 0x200 + dx * 2;
  do {
    memcpy(d, s, (size_t)w * 2);
    s += 0x200; d += 0x200; h--;
  } while (h != 0);
}
void P15_BlitRect8(uint8_t *src, int sx, int sy, uint32_t w, int h, uint8_t *dst, int dx, int dy) {
  const uint8_t *s = src + sy * 0x100 + sx;
  uint8_t *d = dst + dy * 0x100 + dx;
  do {
    memcpy(d, s, w);
    s += 0x100; d += 0x100; h--;
  } while (h != 0);
}
void P15_ListClearActiveByTag(uint32_t tag) {
  for (uint8_t *n = P15_ListHead; n; n = rp(n + 0x20)) {
    uint16_t f = r16(n);
    if ((f & 2) && (f & 8) && r16(n + 6) == tag) w16(n, f & 0xfffd);
  }
}
void P15_ListClearAllActive(void) {
  for (P15_ListCur = P15_ListHead; P15_ListCur; P15_ListCur = rp(P15_ListCur + 0x20)) {
    uint16_t f = r16(P15_ListCur);
    if (f & 2) w16(P15_ListCur, f & 0xfffd);
  }
}
int32_t P15_GridCell(int32_t x, int32_t y) {
  int32_t r = 0;
  if (y < -0x28db) {
    if (y < -0x3493) { if (y < -0x404b) r = (y < -0x4c03) ? 12 : 9; else r = 6; }
    else r = 3;
  }
  if (x < -0x1d1c) r += (x < -0x34d5) ? 2 : 1;
  return r;
}
void P15_RaiseLimits(void) {
  if (P15_State == 4) {
    for (int i = 0; i < 9; i++) {
      if (P15_Flags9[i]) {
        uint8_t lim = P15_Limits[0xb];
        P15_Vals9[i] += 3;
        if ((int32_t)lim < P15_Vals9[i]) P15_Vals9[i] = lim;
      }
    }
  }
}
