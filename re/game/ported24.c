/* ported24.c — DirectDraw / Direct3D initialisation wrappers (English overview).  Thin cdecl wrappers over
   plat_dd_* / plat_d3d_*: surfaces, device, viewport, display mode, clipper, lost-surface recovery and the
   back-buffer clear.  COM objects are kept as void* (32-bit Game.exe pointers in the hook build).
   Wrappers that return int32_t return 1 on success (DD_OK) and 0 on failure. */
#include "ported24.h"
#include "ported22.h"
#include "unported.h"
#include <string.h>
GAME_VAR_DEF(void *, P24_DD, 0x00a42158)
GAME_VAR_DEF(void *, P24_Primary, 0x00a42168)
GAME_VAR_DEF(void *, P24_Back, 0x00a4216c)
GAME_VAR_DEF(void *, P24_ZSurf, 0x00a42170)
GAME_VAR_DEF(void *, P24_Hwnd, 0x00a421bc)
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P24_Fullscreen")
#undef P24_Fullscreen
#pragma push_macro("P24_Fullscreen") /*gvi*/
#undef P24_Fullscreen /*gvi*/
int32_t P24_Fullscreen;
#pragma pop_macro("P24_Fullscreen") /*gvi*/
#pragma pop_macro("P24_Fullscreen")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P24_Bpp")
#undef P24_Bpp
#pragma push_macro("P24_Bpp") /*gvi*/
#undef P24_Bpp /*gvi*/
int32_t P24_Bpp;
#pragma pop_macro("P24_Bpp") /*gvi*/
#pragma pop_macro("P24_Bpp")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P24_RShiftR")
#undef P24_RShiftR
#pragma push_macro("P24_RShiftR") /*gvi*/
#undef P24_RShiftR /*gvi*/
int32_t P24_RShiftR;
#pragma pop_macro("P24_RShiftR") /*gvi*/
#pragma pop_macro("P24_RShiftR")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P24_RShiftL")
#undef P24_RShiftL
#pragma push_macro("P24_RShiftL") /*gvi*/
#undef P24_RShiftL /*gvi*/
int32_t P24_RShiftL;
#pragma pop_macro("P24_RShiftL") /*gvi*/
#pragma pop_macro("P24_RShiftL")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P24_GShiftR")
#undef P24_GShiftR
#pragma push_macro("P24_GShiftR") /*gvi*/
#undef P24_GShiftR /*gvi*/
int32_t P24_GShiftR;
#pragma pop_macro("P24_GShiftR") /*gvi*/
#pragma pop_macro("P24_GShiftR")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P24_GShiftL")
#undef P24_GShiftL
#pragma push_macro("P24_GShiftL") /*gvi*/
#undef P24_GShiftL /*gvi*/
int32_t P24_GShiftL;
#pragma pop_macro("P24_GShiftL") /*gvi*/
#pragma pop_macro("P24_GShiftL")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P24_BShiftR")
#undef P24_BShiftR
#pragma push_macro("P24_BShiftR") /*gvi*/
#undef P24_BShiftR /*gvi*/
int32_t P24_BShiftR;
#pragma pop_macro("P24_BShiftR") /*gvi*/
#pragma pop_macro("P24_BShiftR")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P24_BShiftL")
#undef P24_BShiftL
#pragma push_macro("P24_BShiftL") /*gvi*/
#undef P24_BShiftL /*gvi*/
int32_t P24_BShiftL;
#pragma pop_macro("P24_BShiftL") /*gvi*/
#pragma pop_macro("P24_BShiftL")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P24_RestoreMode")
#undef P24_RestoreMode
#pragma push_macro("P24_RestoreMode") /*gvi*/
#undef P24_RestoreMode /*gvi*/
int32_t P24_RestoreMode;
#pragma pop_macro("P24_RestoreMode") /*gvi*/
#pragma pop_macro("P24_RestoreMode")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P24_ModeW")
#undef P24_ModeW
#pragma push_macro("P24_ModeW") /*gvi*/
#undef P24_ModeW /*gvi*/
int32_t P24_ModeW;
#pragma pop_macro("P24_ModeW") /*gvi*/
#pragma pop_macro("P24_ModeW")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P24_ModeH")
#undef P24_ModeH
#pragma push_macro("P24_ModeH") /*gvi*/
#undef P24_ModeH /*gvi*/
int32_t P24_ModeH;
#pragma pop_macro("P24_ModeH") /*gvi*/
#pragma pop_macro("P24_ModeH")
#endif

enum { DDERR_SURFACELOST = (int32_t)0x887601C2, DDERR_WRONGMODE_ = (int32_t)0x8876024B };   /* -0x7789fe3e, -0x7789fdb5 в оригинале */

/* P24_CreateSurface — 00420c10: IDirectDraw::CreateSurface(desc) -> surface or NULL.
   P24_CreateDevice — 00420cfe: IDirect3D2::CreateDevice(iid, surf) -> device or NULL (NULL d3d -> NULL).
   P24_CreateViewport — 00420d5d: IDirect3D2::CreateViewport -> viewport or NULL.
   P24_AddViewport — 00420dad: adds vp to dev and sets its rectangle to w x h.
   P24_SetDisplayMode — 0042101b: w x h at P24_Bpp bits per pixel.
   P24_CreateClipper — 00421250, P24_SetClipper — 00421298, P24_AttachSurface — 004214dd: as named. */
void *P24_CreateSurface(void *dd, const void *desc) { return plat_dd_create_surface(dd, desc); }
void *P24_CreateDevice(void *d3d, const void *iid, void *surf) {
  if (d3d == NULL) return NULL;
  return plat_d3d_create_device(d3d, iid, surf);
}
void *P24_CreateViewport(void *d3d) {
  if (d3d == NULL) return NULL;
  return plat_d3d_create_viewport(d3d);
}
int32_t P24_AddViewport(void *dev, void *vp, int32_t w, int32_t h) {
  if (dev == NULL || vp == NULL) return 0;
  if (plat_d3d_add_viewport(dev, vp) != 0) return 0;
  return plat_d3d_set_viewport_rect(vp, w, h) == 0;
}
int32_t P24_SetDisplayMode(void *dd, int32_t w, int32_t h) { return plat_dd_set_display_mode(dd, w, h, P24_Bpp) == 0; }
void *P24_CreateClipper(void *dd) { return plat_dd_create_clipper(dd); }
int32_t P24_SetClipper(void *surf, void *clipper) { return plat_dd_set_clipper(surf, clipper) == 0; }
int32_t P24_AttachSurface(void *surf, void *attached) { return plat_dd_attach_surface(surf, attached) == 0; }

/* P24_RestoreSurfaces — Game.exe 004212dc.  Restores the primary, back and Z surfaces if they were lost
   (e.g. after Alt+Tab); DDERR_WRONGMODE from Restore means the display mode changed, so it is set again
   (P24_RestoreDisplay). */
void P24_RestoreSurfaces(void) {
  void *s[3] = { P24_Primary, P24_Back, P24_ZSurf };
  for (int i = 0; i < 3; i++) {
    if (s[i] == NULL) continue;
    if (plat_dd_is_lost(s[i]) != 0 && plat_dd_restore(s[i]) == DDERR_WRONGMODE_) P24_RestoreDisplay();
  }
}
/* P24_RestoreDisplay — Game.exe 004213a4.  When P24_RestoreMode is set (TODO(RE): presumably fullscreen), maximises the window
   and sets the display mode P24_ModeW x P24_ModeH again. */
void P24_RestoreDisplay(void) {
  if (P24_RestoreMode == 0) return;
  plat_window_maximize(P24_Hwnd);
  P24_SetDisplayMode(P24_DD, P24_ModeW, P24_ModeH);
}
/* P24_FillBackbuffer — Game.exe 00420ef6.  Clears the viewport rectangle (P22_Vp*) of surf to colour rgb
   (0xRRGGBB), packed into the surface pixel format with the per-channel shifts P24_[RGB]Shift[RL]
   (shift right drops the low bits, shift left places the channel).  Retries up to 100 times, restoring
   surfaces on DDERR_SURFACELOST.  Always returns 1. */
int32_t P24_FillBackbuffer(void *surf, uint32_t rgb) {
  uint32_t r = ((rgb & 0xff0000) >> 16) >> (P24_RShiftR & 0x1f);
  uint32_t g = ((rgb & 0xff00) >> 8) >> (P24_GShiftR & 0x1f);
  uint32_t b = (rgb & 0xff) >> (P24_BShiftR & 0x1f);
  uint32_t px = (r << (P24_RShiftL & 0x1f)) | (g << (P24_GShiftL & 0x1f)) | (b << (P24_BShiftL & 0x1f));
  for (int i = 0; i < 100; i++) {
    int32_t hr = plat_dd_fill_rect(surf, P22_VpX, P22_VpY, P22_VpX + P22_VpW, P22_VpY + P22_VpH, px);
    if (hr == 0) break;
    if (hr == DDERR_SURFACELOST) P24_RestoreSurfaces();
  }
  return 1;
}
/* P24_CreatePrimarySurface — Game.exe 0042106d.  Creates the flipping primary surface with 1 back buffer
   (2 in fullscreen; TODO(RE): the condition reads "P24_Fullscreen == 0 -> 1", so check the flag's sense) and
   gets the attached back buffer P24_Back.  Returns 1 on success, 0 on failure (primary released). */
int32_t P24_CreatePrimarySurface(void) {
  uint32_t d[31]; memset(d, 0, sizeof d);
  d[0] = 0x7c; d[1] = 0x21;                 /* dwSize, DDSD_CAPS|DDSD_BACKBUFFERCOUNT */
  d[5] = (P24_Fullscreen == 0) ? 1 : 2;     /* dwBackBufferCount */
  d[26] = 0x2218;                           /* ddsCaps: PRIMARYSURFACE|COMPLEX|FLIP|3DDEVICE */
  P24_Primary = P24_CreateSurface(P24_DD, d);
  if (P24_Primary == NULL) return 0;
  P24_Back = plat_dd_get_attached(P24_Primary, 4);   /* DDSCAPS_BACKBUFFER */
  if (P24_Back == NULL) { plat_dd_release(P24_Primary); return 0; }
  return 1;
}
