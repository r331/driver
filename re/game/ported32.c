/* Z-буфер и палитры текстур Direct3D — восстановлено из Game.exe (Render.c). */
#include "ported32.h"
#include "noop.h"
#include "unported.h"
#include <stdio.h>
#include <string.h>
GAME_VAR_DEF(P32_SlotArr, P32_Slots, 0x00621c48)
GAME_VAR_DEF(P32_PalArr, P32_PalTable, 0x006017c0)
GAME_VAR_DEF(uint8_t *, P32_DevInfo, 0x00a42150)
GAME_VAR_DEF(int32_t, P32_CurSlot, 0x0054ef30)
GAME_VAR_DEF(void *, P32_CurHandle, 0x00a42178)
GAME_VAR_DEF(P32_MsgArr, P32_Msg, 0x00a42048)

int32_t P32_CreateZSurface(void *back) {
  uint32_t d[31];
  int32_t w = 0, h = 0;
  plat_dd_get_surface_size(back, &w, &h);    /* GetSurfaceDesc: высота +8, ширина +0xc */
  memset(d, 0, sizeof d);
  d[0] = 0x7c; d[1] = 0x1007;                /* CAPS|HEIGHT|WIDTH|PIXELFORMAT */
  d[2] = (uint32_t)h; d[3] = (uint32_t)w;
  memcpy(&d[18], P32_DevInfo + 0x568, 32);   /* DDPIXELFORMAT Z-буфера (+0x48) */
  int32_t flag; memcpy(&flag, P32_DevInfo + 0x518, 4);
  d[26] = (flag != 0) ? 0x24000 : 0x20800;   /* ddsCaps */
  P24_ZSurf = P24_CreateSurface(P24_DD, d);
  if (P24_ZSurf == NULL) return 0;
  return P24_AttachSurface(P24_Back, P24_ZSurf) != 0;
}

int32_t P32_CreateSlotPalette(int32_t slot) {
  P32_Slot *s = &P32_Slots[slot];
  if (G6_00A421F0 != 0) return 1;
  if (s->bpp != 8) return 1;
  if (s->pal == NULL) {
    s->pal = plat_dd_create_palette(P24_DD, 0x44, P32_PalTable);   /* 8BIT|ALLOW256 */
    if (s->pal == NULL) return 0;
  }
  if (plat_dd_surface_set_palette(s->surf, s->pal) != 0) return 0;
  if (plat_dd_palette_set_entries(s->pal, 0, 0, 0x100, P32_PalTable) != 0) return 0;
  plat_tex_palette_changed(s->tex, 0, 0x100);
  return 1;
}

void P32_SelectSlotPalette(int32_t slot) {
  P32_Slot *s = &P32_Slots[slot];
  P32_CurSlot = slot;
  if (s->cur_id != G6_0054EF2C) {
    s->cur_handle = NULL;
    P32_Node *head = s->list;
    for (P32_Node *n = head; n != NULL; n = n->next) {
      if (n->id == G6_0054EF2C) { s->cur_handle = n->handle; break; }
    }
    if (s->cur_handle == NULL) {
      snprintf(P32_Msg, sizeof P32_Msg, "Palette %d not found (%d)", (int)G6_0054EF2C, (int)head->first);
      NoopFn0042243f();
      s->cur_handle = head->handle;
    }
    s->cur_id = G6_0054EF2C;
  }
  plat_set_texture(0, s->cur_handle);
  P32_CurHandle = s->cur_handle;
}

void P32_SetPalette(int32_t a, int32_t mode, const uint8_t *rgba) {
  (void)a;
  G6Call00422AE7();
  if (mode != 2) return;
  for (int i = 0; i < 256; i++) {
    P32_PalTable[i * 4 + 0] = rgba[i * 4 + 2];
    P32_PalTable[i * 4 + 1] = rgba[i * 4 + 1];
    P32_PalTable[i * 4 + 2] = rgba[i * 4 + 0];
    P32_PalTable[i * 4 + 3] = 2;
  }
  plat_set_render_state(0x32, 0);
  for (int i = 0; i < 32; i++) {
    P32_Slot *s = &P32_Slots[i];
    if (s->pal == NULL) continue;
    plat_dd_palette_set_entries(s->pal, 0, 0, 0x100, P32_PalTable);
    plat_tex_palette_changed(s->tex, 0, 0x100);
  }
}
