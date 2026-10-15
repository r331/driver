#include "ported24.h"
#include "ported22.h"
#include "unported.h"
#include <string.h>
GAME_VAR_DEF(void *, P24_DD, 0x00a42158)
GAME_VAR_DEF(void *, P24_Primary, 0x00a42168)
GAME_VAR_DEF(void *, P24_Back, 0x00a4216c)
GAME_VAR_DEF(void *, P24_ZSurf, 0x00a42170)
GAME_VAR_DEF(void *, P24_Hwnd, 0x00a421bc)
GAME_VAR_DEF(int32_t, P24_Fullscreen, 0x00a421f4)
GAME_VAR_DEF(int32_t, P24_Bpp, 0x0054ef28)
GAME_VAR_DEF(int32_t, P24_RShiftR, 0x00a42184)
GAME_VAR_DEF(int32_t, P24_RShiftL, 0x00a42188)
GAME_VAR_DEF(int32_t, P24_GShiftR, 0x00a4218c)
GAME_VAR_DEF(int32_t, P24_GShiftL, 0x00a42190)
GAME_VAR_DEF(int32_t, P24_BShiftR, 0x00a42194)
GAME_VAR_DEF(int32_t, P24_BShiftL, 0x00a42198)
GAME_VAR_DEF(int32_t, P24_RestoreMode, 0x00a421c4)
GAME_VAR_DEF(int32_t, P24_ModeW, 0x00a421a4)
GAME_VAR_DEF(int32_t, P24_ModeH, 0x00a421a8)

enum { DDERR_SURFACELOST = (int32_t)0x887601C2, DDERR_WRONGMODE_ = (int32_t)0x8876024B };   /* -0x7789fe3e, -0x7789fdb5 в оригинале */

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

void P24_RestoreSurfaces(void) {
  void *s[3] = { P24_Primary, P24_Back, P24_ZSurf };
  for (int i = 0; i < 3; i++) {
    if (s[i] == NULL) continue;
    if (plat_dd_is_lost(s[i]) != 0 && plat_dd_restore(s[i]) == DDERR_WRONGMODE_) P24_RestoreDisplay();
  }
}
void P24_RestoreDisplay(void) {
  if (P24_RestoreMode == 0) return;
  plat_window_maximize(P24_Hwnd);
  P24_SetDisplayMode(P24_DD, P24_ModeW, P24_ModeH);
}
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
