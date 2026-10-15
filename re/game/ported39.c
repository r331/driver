/* Поверхности DirectDraw: Lock/Unlock, формат пикселей, Present — восстановлено из Game.exe. */
#include "ported39.h"
#include "noop.h"
#include "ported7.h"
#include "smallfuncs2.h"
#include <string.h>
GAME_VAR_DEF(int32_t, P39_Locked, 0x00a421d0)
#ifndef RE_HOOK_BUILD
uint8_t P39_Dummy[64];
#endif

#define DDERR_SURFACELOST_HR ((int32_t)0x887601C2)

int32_t P39_LockSurface(int32_t a0, int32_t which, int32_t a2, int32_t a3, int32_t a4, P39_SurfInfo *out) {
  (void)a0; (void)a2; (void)a3; (void)a4;
  if (P22_DevReady == 0) return 0;
  P33_FlushBatches();
  P22_EndScene();
  uint32_t desc[31];
  memset(desc, 0, sizeof desc);
  desc[0] = 0x7c;
  int32_t hr;
  if (which == 0) hr = plat_dd_lock(P24_Primary, desc);
  else if (which == 1) hr = plat_dd_lock(P24_Back, desc);
  else return 0;
  uint32_t ptr; int32_t pitch;
  if (hr == 0) {
    P39_Locked = 1;
    ptr = desc[9]; pitch = (int32_t)desc[4];
  } else {
    ptr = (uint32_t)(uintptr_t)&P39_Dummy; pitch = 0;
  }
  out->ptr = ptr;
  out->pitch = pitch;
  out->one = 1;
  out->zero = 0;
  return 1;
}

int32_t P39_UnlockSurface(int32_t a0, int32_t which) {
  (void)a0;
  if (P22_DevReady == 0) return 0;
  if (P39_Locked != 0) {
    if (which == 0) plat_dd_unlock(P24_Primary);
    else if (which == 1) plat_dd_unlock(P24_Back);
    else return 0;
    P39_Locked = 0;
  }
  P22_BeginScene();
  return 1;
}

int32_t P39_GetSurfaceFormat(int32_t which, P39_SurfInfo *out) {
  if (P39_LockSurface(0, which, 0, 0, 0, out) != 1) return 0;
  uint32_t pf[8];
  memset(pf, 0, sizeof pf);
  pf[0] = 0x20;
  int32_t hr;
  if (which == 0) hr = plat_dd_get_pixel_format(P24_Primary, pf);
  else if (which == 1) hr = plat_dd_get_pixel_format(P24_Back, pf);
  else hr = -1;   /* неверный индекс поверхности */
  if (hr != 0) {
    P39_UnlockSurface(0, which);
    return 0;
  }
  out->bpp = (uint8_t)pf[3];
  out->r_loss = (uint8_t)MaskShift_00421C1D(pf[4]);
  out->r_shift = (uint8_t)CountTrailingZeros00421C72(pf[4]);
  out->g_loss = (uint8_t)MaskShift_00421C1D(pf[5]);
  out->g_shift = (uint8_t)CountTrailingZeros00421C72(pf[5]);
  out->b_loss = (uint8_t)MaskShift_00421C1D(pf[6]);
  out->b_shift = (uint8_t)CountTrailingZeros00421C72(pf[6]);
  return 1;
}

void P39_Present(int32_t wait) {
  if (P22_DevReady == 0) return;
  P33_FlushBatches();
  P22_EndScene();
  int32_t hr;
  if (P24_RestoreMode == 0) {
    int32_t rc[4], dst[4];
    plat_window_client_rect(P24_Hwnd, rc);
    int32_t right = rc[2], bottom = rc[3];
    dst[0] = rc[0]; dst[1] = rc[1]; dst[2] = right; dst[3] = bottom;
    if (P24_ModeW < right) {
      rc[2] = P24_ModeW;
      dst[0] = (right - P24_ModeW) / 2;
      dst[2] = dst[0] + P24_ModeW;
    }
    if (P24_ModeH < bottom) {
      rc[3] = P24_ModeH;
      dst[1] = (bottom - P24_ModeH) / 2;
      dst[3] = dst[1] + P24_ModeH;
    }
    plat_client_to_screen(P24_Hwnd, dst);
    plat_client_to_screen(P24_Hwnd, dst + 2);
    plat_dd_clipper_set_hwnd(P31_DDObj4, P24_Hwnd);
    hr = plat_dd_blt_rect(P24_Primary, dst, P24_Back, rc);
    if (hr != 0) P24_RestoreSurfaces();
  } else {
    hr = plat_dd_flip(P24_Primary, wait == 0 ? 9u : 1u);
    if (hr == DDERR_SURFACELOST_HR) P24_RestoreSurfaces();
  }
  P22_BeginScene();
}

void *P39_QueryDD4(void *dd) {
  NoopFn0042243f();
  if (dd == NULL) return NULL;
  void *r = plat_dd_query_dd4(dd);
  if (r == NULL) NoopFn0042243f();
  return r;
}

void *P39_QueryD3D(void *dd) {
  NoopFn0042243f();
  if (dd == NULL) return NULL;
  void *r = plat_dd_query_d3d(dd);
  if (r == NULL) NoopFn0042243f();
  return r;
}

int32_t P39_CreateFrontBack(int32_t w, int32_t h) {
  uint32_t d[31];
  memset(d, 0, sizeof d);
  d[0] = 0x7c; d[1] = 1; d[26] = 0x200;
  P24_Primary = P24_CreateSurface(P24_DD, d);
  if (P24_Primary == NULL) return 0;
  memset(d, 0, sizeof d);
  d[0] = 0x7c; d[1] = 7; d[3] = (uint32_t)w; d[2] = (uint32_t)h;
  int32_t flag;
  memcpy(&flag, P32_DevInfo + 0x518, 4);
  d[26] = flag == 0 ? 0x2840u : 0x6040u;
  P24_Back = P24_CreateSurface(P24_DD, d);
  if (P24_Back == NULL) return 0;
  P31_DDObj4 = P24_CreateClipper(P24_DD);
  if (P31_DDObj4 == NULL) return 0;
  return P24_SetClipper(P24_Primary, P31_DDObj4) != 0 ? 1 : 0;
}
