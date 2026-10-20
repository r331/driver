/* Z-буфер и палитры текстур Direct3D — восстановлено из Game.exe (Render.c). */
/* ported32.c — Direct3D Z-buffer creation and 8-bit texture palettes (English overview).
   32 texture slots P32_Slots (00621c48, 32 bytes each); an 8-bit slot owns a DirectDraw palette and a list
   of alternative palettes (P32_Node) selected by palette number G6_0054EF2C.  All DirectDraw/Direct3D work
   goes through plat_dd_* / plat_set_texture. */
#include "ported32.h"
#include "noop.h"
#include "unported.h"
#include "flush.h"
#include <stdio.h>
#include <string.h>
GAME_VAR_DEF(P32_SlotArr, P32_Slots, 0x00621c48)
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P32_PalTable")
#undef P32_PalTable
#pragma push_macro("P32_PalTable") /*gvi*/
#undef P32_PalTable /*gvi*/
P32_PalArr P32_PalTable;
#pragma pop_macro("P32_PalTable") /*gvi*/
#pragma pop_macro("P32_PalTable")
#endif
GAME_VAR_DEF(uint8_t *, P32_DevInfo, 0x00a42150)
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P32_CurSlot")
#undef P32_CurSlot
#pragma push_macro("P32_CurSlot") /*gvi*/
#undef P32_CurSlot /*gvi*/
int32_t P32_CurSlot;
#pragma pop_macro("P32_CurSlot") /*gvi*/
#pragma pop_macro("P32_CurSlot")
#endif
GAME_VAR_DEF(void *, P32_CurHandle, 0x00a42178)
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P32_Msg")
#undef P32_Msg
#pragma push_macro("P32_Msg") /*gvi*/
#undef P32_Msg /*gvi*/
P32_MsgArr P32_Msg;
#pragma pop_macro("P32_Msg") /*gvi*/
#pragma pop_macro("P32_Msg")
#endif

/* DDSURFACEDESC fields (dword indices into d[]) and flag values used below (standard DirectDraw values). */
enum {
  DDSD_SIZE_BYTES  = 0x7c,      /* sizeof(DDSURFACEDESC) */
  DDSD_ZBUF_FLAGS  = 0x1007,    /* DDSD_CAPS | DDSD_HEIGHT | DDSD_WIDTH | DDSD_PIXELFORMAT */
  DDPAL_FLAGS_8BIT = 0x44       /* DDPCAPS_8BIT | DDPCAPS_ALLOW256 */
};

/* P32_CreateZSurface — Game.exe 004213dc, cdecl.  Creates a Z-buffer surface as large as the back buffer
   `back`, with the Z pixel format of the selected device (P32_DevInfo + 0x568) and attaches it to P24_Back.
   ddsCaps: 0x24000 (ZBUFFER | VIDEOMEMORY) when device flag +0x518 is set, else 0x20800 (ZBUFFER | SYSTEMMEMORY).
   TODO(RE): exact meaning of device flag +0x518 (hardware device?) unsure.
   Returns 1 on success (P24_ZSurf set), 0 on failure. */
int32_t P32_CreateZSurface(void *back) {
  uint32_t d[31];                            /* DDSURFACEDESC (0x7c bytes) */
  int32_t w = 0, h = 0;
  plat_dd_get_surface_size(back, &w, &h);    /* GetSurfaceDesc: высота +8, ширина +0xc */
  memset(d, 0, sizeof d);
  d[0] = DDSD_SIZE_BYTES; d[1] = DDSD_ZBUF_FLAGS;   /* CAPS|HEIGHT|WIDTH|PIXELFORMAT */
  d[2] = (uint32_t)h; d[3] = (uint32_t)w;
  memcpy(&d[18], P32_DevInfo + 0x568, 32);   /* DDPIXELFORMAT Z-буфера (+0x48) */
  int32_t flag; memcpy(&flag, P32_DevInfo + 0x518, 4);
  d[26] = (flag != 0) ? 0x24000 : 0x20800;   /* ddsCaps */
  P24_ZSurf = P24_CreateSurface(P24_DD, d);
  if (P24_ZSurf == NULL) return 0;
  return P24_AttachSurface(P24_Back, P24_ZSurf) != 0;
}

/* P32_CreateSlotPalette — Game.exe 00422309, cdecl.  For an 8-bit texture slot: creates its DirectDraw palette
   from P32_PalTable if it has none, attaches it to the slot surface, loads all 256 entries and tells the
   platform texture cache the palette changed.  Does nothing (returns 1) for non-8-bit slots or when
   G6_00A421F0 != 0 (TODO(RE): flag meaning unsure — palettes disabled?).  Returns 0 on a DirectDraw error. */
int32_t P32_CreateSlotPalette(int32_t slot) {
  P32_Slot *s = &P32_Slots[slot];
  if (G6_00A421F0 != 0) return 1;
  if (s->bpp != 8) return 1;
  if (s->pal == NULL) {
    s->pal = plat_dd_create_palette(P24_DD, DDPAL_FLAGS_8BIT, P32_PalTable);   /* 8BIT|ALLOW256 */
    if (s->pal == NULL) return 0;
  }
  if (plat_dd_surface_set_palette(s->surf, s->pal) != 0) return 0;
  if (plat_dd_palette_set_entries(s->pal, 0, 0, 0x100, P32_PalTable) != 0) return 0;
  plat_tex_palette_changed(s->tex, 0, 0x100);
  return 1;
}

/* P32_SelectSlotPalette — Game.exe 00422c55, cdecl.  Makes slot the current texture: when the slot's cached
   palette number differs from the wanted one (G6_0054EF2C), searches the slot's palette list for it; if it is
   missing, formats "Palette %d not found" into P32_Msg (the original's debug print is a no-op) and falls back
   to the first node.  Then binds the handle as texture stage 0.
   Side effects: P32_CurSlot, P32_CurHandle, slot cur_id/cur_handle. */
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

/* P32_SetPalette — Game.exe 0041f57d (stdcall in the original, ret 0xc; the hook adapter converts).
   In:  a — unused; mode — only 2 does anything; rgba — 256 entries of 4 bytes.
   Swaps bytes 0 and 2 of each entry (input presumably B,G,R,x -> PALETTEENTRY R,G,B,flags) with flags = 2
   (TODO(RE): meaning of flags value 2 unsure),
   stores it in P32_PalTable, sets render state 0x32 to 0 and reloads the palette of every slot that has one. */
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
