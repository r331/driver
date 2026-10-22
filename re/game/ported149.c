/* ported149.c — Direct3D / DirectDraw device enumeration and emulated 8-bit textures (Game\pc\DDraw.c /
   D3D.c) (English overview; original notes follow).
   P149_DDEnumAll enumerates DirectDraw drivers (callback P149_DDEnumCb), each driver's Direct3D devices
   (callback P149_D3DDevCb), then P149_BuildDevs turns them into rows of the render-device table
   (at most 4, shared with the Glide entry).  The emulated-texture functions keep 8-bit palettised texture
   pages as 16-bit DirectDraw surfaces, one node per page plus extra surfaces per palette.
   All DirectDraw / Direct3D calls go through plat_dd_* / plat_d3d_*. */
/* v1.94: ported149 — блок D3D/DirectDraw, см. ported149.h.
   0041ce90 — лог, DirectDrawEnumerateA(0041fac0, 0) ≠ 0 → 0; иначе 0041fe07 и 1, если 00b1c0e0 вырос.
   0041fac0 — колбэк (stdcall, 4 аргумента, ret 0x10): запись 0x44, strcpy(+0, desc); DirectDrawCreate(guid) → 00420c5a
     (IDirectDraw4) → 00420cac (IDirect3D3) → EnumDevices(0041fcc7, запись); ошибка на любом шаге — Release созданного и
     free записи; успех — guid (или +0x30 = 1 для основного), запись в конец списка 00a42148/00a4214c, Release трёх.
     Всегда 1 (продолжить).
   0041fcc7 — колбэк (stdcall, 6 аргументов, ret 0x18): guid ≠ NULL, hw->dcmColorModel (+8) ≠ 0, ctx ≠ NULL: запись
     0x230, strcpy(+0, name), HAL/HEL (по 0x3f слов) и guid, в конец списка устройств драйвера (+0x34/+0x38). Всегда 1.
   0041fe07 — для каждого устройства каждого драйвера при 00b1c0e0 < 4: запись 0x590, строка таблицы 01270ec0 + n·0x4c
     (тип 1, sprintf "%s" имён драйвера и устройства в +4/+0x24, адрес записи в +0x48); HAL/HEL → +0x320/+0x41c,
     GUID драйвера (если не основной) → +4 и адрес в +0, GUID устройства → +0x18 и адрес в +0x14; 00420038(строка) = 0 →
     free, иначе +0x44 = (запись +0x588 == 0), счёт +1. Записи драйверов и устройств освобождаются.
   0041d6aa — для каждого узла 00a42180 (след. +0x1c) и каждой поверхности его подсписка (+0x18): Release +0x14
     (IDirect3DTexture2; если это текущая 00a42178 — сброс) и +0x10, free; голова 0, 0054ef2c = 0054ef30 = −1.
   004225eb — узел 0x20 (memset первых 4 байт), 00422736; +0 номер, +4 вид, +0xc палитра, +0x18 = 0, в голову 00a42180;
     Lock(+0x10) → 004229fa(src, палитра, lpSurface, pitch), Unlock; 1. 0042248b — то же, но к концу подсписка узла. */
#include "ported151.h"
#include "ported149.h"
#include "ported6.h"
#include "ported32.h"
#include "ported39.h"
#include "ported42.h"
#include "ported46.h"
#include "ported74.h"
#include "ported105.h"
#include "noop.h"
#include "crt.h"
#include "reptr.h"
#include "unported.h"
#include "../platform/plat.h"
#ifndef RE_HOOK_BUILD
#include "ported86.h"
#endif
#include <stdio.h>
#include <string.h>

#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P149_DDHead")
#undef P149_DDHead
#pragma push_macro("P149_DDHead") /*gvi*/
#undef P149_DDHead /*gvi*/
uint32_t P149_DDHead;
#pragma pop_macro("P149_DDHead") /*gvi*/
#pragma pop_macro("P149_DDHead")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P149_DDTail")
#undef P149_DDTail
#pragma push_macro("P149_DDTail") /*gvi*/
#undef P149_DDTail /*gvi*/
uint32_t P149_DDTail;
#pragma pop_macro("P149_DDTail") /*gvi*/
#pragma pop_macro("P149_DDTail")
#endif

/* Heap records built while enumerating (fields hold 32-bit Game.exe-style addresses, see ported149.h). */
/* DirectDraw driver record, 0x44 bytes */
#define DRV_SIZE      0x44
#define DRV_NAME      0x00   /* char[0x20]: driver description */
#define DRV_GUID      0x20   /* GUID (only for non-primary drivers) */
#define DRV_PRIMARY   0x30   /* 1 = primary display driver (enumerated with guid NULL) */
#define DRV_DEV_HEAD  0x34   /* first / last Direct3D device record of this driver */
#define DRV_DEV_TAIL  0x38
#define DRV_NEXT      0x3c   /* driver list (head P149_DDHead 00a42148, tail P149_DDTail 00a4214c) */
#define DRV_PREV      0x40
/* Direct3D device record, 0x230 bytes */
#define DEV_SIZE      0x230
#define DEV_NAME      0x00   /* char[0x20] */
#define DEV_GUID      0x20
#define DEV_HAL       0x30   /* D3DDEVICEDESC of the hardware (HAL) caps, D3DDESC_SIZE bytes */
#define DEV_HEL       0x12c  /* D3DDEVICEDESC of the software emulation (HEL) caps */
#define DEV_NEXT      0x228
#define DEV_PREV      0x22c
#define D3DDESC_SIZE  0xfc   /* sizeof(D3DDEVICEDESC) in the DirectX 6 headers */
#define D3DDESC_COLOR_MODEL 8   /* D3DDEVICEDESC.dcmColorModel: 0 = device not usable */
/* Render-device table row (P74_DevTab, 01270ec0, 0x4c bytes per device, at most 4) */
#define DEVTAB_ROW    0x4c

/* rd32 / wr32 — local helpers: unaligned 32-bit read / write. */
static uint32_t rd32(const uint8_t *p) { uint32_t v; memcpy(&v, p, 4); return v; }
static void wr32(uint8_t *p, uint32_t v) { memcpy(p, &v, 4); }

/* strcpy(0052b100) в запись с полем имени 0x20; в native — с границей поля */
/* copy_name — local helper: strcpy into a 0x20-byte name field (native: bounded to 31 characters). */
static void copy_name(uint8_t *dst, const char *src) {
#ifdef RE_HOOK_BUILD
  strcpy((char *)dst, src);
#else
  size_t n = strlen(src); if (n > 0x1f) n = 0x1f;
  memcpy(dst, src, n); dst[n] = 0;
#endif
}

/* память записи с 32-битными ссылками: в native регистрируется целиком (адреса внутри записи) */
/* rec_alloc / rec_free — local helpers: heap records that hold 32-bit references; in native the whole block
   is registered with re_ptr so addresses inside it can be translated. */
static uint8_t *rec_alloc(uint32_t size) {
  uint8_t *p = (uint8_t *)g_malloc(size);
#ifndef RE_HOOK_BUILD
  if (p != NULL) re_ptr_register_dyn(p, size);
#endif
  return p;
}
static void rec_free(void *p) {
#ifndef RE_HOOK_BUILD
  if (p != NULL) re_ptr_unregister(p);
#endif
  g_free(p);
}

/* ---- 0041fcc7 ---- */
/* P149_D3DDevCb — Game.exe 0041fcc7, stdcall (ret 0x18) in the original.  Direct3D EnumDevices callback:
   for a device with a GUID and a usable colour model, appends a device record (name, GUID, HAL and HEL
   caps) to the driver record `ctx`.  Always returns 1 (continue enumerating). */
int32_t P149_D3DDevCb(const void *guid, const char *desc, const char *name, const void *hw, const void *hel, void *ctx) {
  (void)desc;
  uint8_t *drv = (uint8_t *)ctx;
  if (guid == NULL || rd32((const uint8_t *)hw + D3DDESC_COLOR_MODEL) == 0 || drv == NULL) return 1;
  uint8_t *dev = rec_alloc(DEV_SIZE);
  if (dev == NULL) return 1;
  memset(dev, 0, DEV_SIZE);
  copy_name(dev, name);
  memcpy(dev + DEV_HAL, hw, D3DDESC_SIZE);
  memcpy(dev + DEV_HEL, hel, D3DDESC_SIZE);
  memcpy(dev + DEV_GUID, guid, 16);
  wr32(dev + DEV_NEXT, 0);
  wr32(dev + DEV_PREV, rd32(drv + DRV_DEV_TAIL));
  if (rd32(drv + DRV_DEV_HEAD) == 0) {
    re_wr_ptr(drv + DRV_DEV_HEAD, dev);
  } else {
    re_wr_ptr((uint8_t *)re_rd_ptr(drv + DRV_DEV_TAIL) + DEV_NEXT, dev);
  }
  re_wr_ptr(drv + DRV_DEV_TAIL, dev);
  return 1;
}

/* ---- 0041fac0 ---- */
/* P149_DDEnumCb — Game.exe 0041fac0, stdcall (ret 0x10) in the original.  DirectDrawEnumerate callback:
   creates the driver, gets IDirectDraw4 and IDirect3D3, enumerates its devices into a new driver record and
   appends it to the driver list.  On any failure the objects and the record are released.  Always 1. */
int32_t P149_DDEnumCb(const void *guid, const char *desc, const char *name, void *ctx) {
  (void)name; (void)ctx;
  uint8_t *drv = rec_alloc(DRV_SIZE);
  if (drv == NULL) return 1;
  memset(drv, 0, DRV_SIZE);
  copy_name(drv, desc);
  void *dd = plat_dd_create(guid);
  if (dd == NULL) { rec_free(drv); return 1; }
  void *dd4 = P39_QueryDD4(dd);
  if (dd4 == NULL) { plat_dd_release(dd); rec_free(drv); return 1; }
  void *d3d = P39_QueryD3D(dd4);
  if (d3d == NULL) { plat_dd_release(dd4); plat_dd_release(dd); rec_free(drv); return 1; }
  if (plat_d3d_enum_devices(d3d, P149_D3DDevCb, drv) != 0) {
    plat_dd_release(d3d); plat_dd_release(dd4); plat_dd_release(dd);
    rec_free(drv);
    return 1;
  }
  if (guid == NULL) wr32(drv + DRV_PRIMARY, 1);
  else { memcpy(drv + DRV_GUID, guid, 16); wr32(drv + DRV_PRIMARY, 0); }
  wr32(drv + DRV_NEXT, 0);
  if (P149_DDHead == 0) {
    wr32(drv + DRV_PREV, 0);
    P149_DDHead = re_addr(drv);
  } else {
    wr32(drv + DRV_PREV, P149_DDTail);
    re_wr_ptr((uint8_t *)re_ptr(P149_DDTail) + DRV_NEXT, drv);
  }
  P149_DDTail = re_addr(drv);
  plat_dd_release(d3d); plat_dd_release(dd4); plat_dd_release(dd);
  return 1;
}

/* строка n таблицы устройств: в native у 01270ec4 есть второй псевдоним P42_DevNames (правило v1.78) */
/* dev_mirror — native helper: copies device-table row n into its second native alias P42_DevNames
   (01270ec4, rule v1.78); nothing in the hook build. */
static void dev_mirror(int32_t n) {
#ifndef RE_HOOK_BUILD
  if (n >= 0 && n < 16) memcpy(P42_DevNames[n], (uint8_t *)&P74_DevTab[0] + (size_t)n * 0x4c + 4, 0x48);
#else
  (void)n;
#endif
}

/* ---- 0041fe07 ---- */
/* P149_BuildDevs — Game.exe 0041fe07.  For every device of every driver while fewer than 4 devices are
   listed: fills a device-table row (type 1, "driver" / "device" names, pointer to a 0x590-byte info record
   with HAL/HEL caps at +0x320/+0x41c and the driver/device GUIDs with pointers to them).  If the device
   check P151_CheckDev rejects it the info record is freed; otherwise row +0x44 = (info +0x588 == 0) and the
   count grows.  Frees all driver and device records afterwards.
   TODO(RE): unsure what info +0x588 / row +0x44 mean. */
void P149_BuildDevs(void) {
  uint8_t *drv = (uint8_t *)re_ptr(P149_DDHead);
  while (drv != NULL) {
    uint8_t *drv_next = (uint8_t *)re_rd_ptr(drv + DRV_NEXT);
    uint8_t *dev = (uint8_t *)re_rd_ptr(drv + DRV_DEV_HEAD);
    while (dev != NULL) {
      uint8_t *dev_next = (uint8_t *)re_rd_ptr(dev + DEV_NEXT);
      if (P42_DevCount < 4) {
        int32_t n = P42_DevCount;
        uint8_t *info = rec_alloc(0x590);
        memset(info, 0, 0x590);
        uint8_t *row = (uint8_t *)&P74_DevTab[0] + (size_t)n * DEVTAB_ROW;
        memset(row, 0, DEVTAB_ROW);
        sprintf((char *)row + 4, "%s", (const char *)drv);
        sprintf((char *)row + 0x24, "%s", (const char *)dev);
        wr32(row, 1);
        re_wr_ptr(row + 0x48, info);
        memcpy(info + 0x320, dev + DEV_HAL, D3DDESC_SIZE);
        memcpy(info + 0x41c, dev + DEV_HEL, D3DDESC_SIZE);
        wr32(info, 0);
        if (rd32(drv + DRV_PRIMARY) == 0) {
          memcpy(info + 4, drv + DRV_GUID, 16);
          re_wr_ptr(info, info + 4);
        }
        memcpy(info + 0x18, dev + DEV_GUID, 16);
        re_wr_ptr(info + 0x14, info + 0x18);
        dev_mirror(n);
        if (P151_CheckDev(row) == 0) {
          rec_free(info);
        } else {
          wr32(row + 0x44, rd32(info + 0x588) == 0 ? 1u : 0u);
          dev_mirror(n);
          P42_DevCount = n + 1;
        }
      }
      rec_free(dev);
      dev = dev_next;
    }
    rec_free(drv);
    drv = drv_next;
  }
}

/* ---- 0041ce90 ---- */
/* P149_DDEnumAll — Game.exe 0041ce90.  Enumerates drivers and builds the device table.  Returns 1 if any device
   was added, 0 if none or DirectDrawEnumerate failed. */
int32_t P149_DDEnumAll(void) {
  NoopFn0042243f();
  int32_t hr = plat_dd_enumerate(P149_DDEnumCb, NULL);
  int32_t old_count = P42_DevCount;
  if (hr != 0) return 0;
  P149_BuildDevs();
  return P42_DevCount != old_count ? 1 : 0;
}

/* Release IDirect3DTexture2 / поверхности узла (+0x14 / +0x10) */
/* emul_release — local helper: releases a node's texture (+0x14, IDirect3DTexture2; clears it if current)
   and surface (+0x10). */
static void emul_release(uint8_t *n) {
  void *tex = re_rd_ptr(n + 0x14);
  if (rd32(n + 0x14) != 0) {
    if (P32_CurHandle == tex) P32_CurHandle = NULL;
    plat_dd_release(tex);
    wr32(n + 0x14, 0);
  }
  if (rd32(n + 0x10) != 0) {
    plat_dd_release(re_rd_ptr(n + 0x10));
    wr32(n + 0x10, 0);
  }
}

/* ---- 0041d6aa ---- */
/* P149_EmulFreeAll — Game.exe 0041d6aa.  Frees every emulated texture node and all its extra surfaces
   (list +0x18), resets the list head and the current texture slots (0054ef2c, 0054ef30) to -1. */
void P149_EmulFreeAll(void) {
  P46_TexNode *n = P46_TexHead;
  while (n != NULL) {
    NoopFn0042243f();                      /* «Releasing emulated texture set» */
    P46_TexNode *next = n->next;
    uint8_t *sub = (uint8_t *)re_rd_ptr((uint8_t *)n + 0x18);
    while (sub != NULL) {
      NoopFn0042243f();                    /* «Releasing emulated texture» */
      uint8_t *sub_next = (uint8_t *)re_rd_ptr(sub + 0x18);
      emul_release(sub);
      rec_free(sub);
      sub = sub_next;
    }
    emul_release((uint8_t *)n);
    rec_free(n);
    n = next;
  }
  P46_TexHead = NULL;
  G6_0054EF2C = -1;
  P32_CurSlot = -1;
}

/* общая часть 0042248b/004225eb: Lock(+0x10), 004229fa(src, pal, lpSurface, pitch), Unlock */
/* emul_upload — local helper (shared tail of 0042248b / 004225eb): locks the surface, converts the 8-bit
   page src through palette pal into it (P74_Conv8to16, using lpSurface and lPitch of the DDSURFACEDESC2,
   dwSize 0x7c), unlocks.  Native: also attaches the HD texture-pack image for (page, palette slot).
   Returns 1, or 0 if Lock failed. */
static int32_t emul_upload(uint8_t *o, int32_t src, int32_t pal) {
  uint32_t desc[31];
  memset(desc, 0, sizeof desc);
  desc[0] = 0x7c;
  void *surf = re_rd_ptr(o + 0x10);
  if (plat_dd_lock(surf, desc) != 0) { NoopFn0042243f(); return 0; }   /* «Lock emultexture8() failed» */
#ifndef RE_HOOK_BUILD
  if (re_ptr(desc[9]) != NULL && re_ptr((uint32_t)src) != NULL && re_ptr((uint32_t)pal) != NULL)
#endif
  P74_Conv8to16((const uint8_t *)re_ptr((uint32_t)src), (const uint8_t *)re_ptr((uint32_t)pal),
                (uint16_t *)re_ptr(desc[9]), (int32_t)desc[4]);
  plat_dd_unlock(surf);
#ifndef RE_HOOK_BUILD
  P86_GameAttachEmul8(surf, (int32_t)rd32(o), (int32_t)rd32(o + 4));   /* v2.18: HD-пак — пара (страница = handle, слот палитры = +4) */
#endif
  return 1;
}

/* ---- 0042248b ---- */
/* P149_EmulAddSub — Game.exe 0042248b.  Adds another surface (same page handle, another palette `pal`, kind)
   at the end of node's surface list and uploads it.  Returns 1 on success, 0 on failure. */
int32_t P149_EmulAddSub(void *node, int32_t src, int32_t kind, int32_t pal) {
  uint8_t *last = (uint8_t *)node;
  for (uint8_t *nxt; (nxt = (uint8_t *)re_rd_ptr(last + 0x18)) != NULL; ) last = nxt;
  uint8_t *sub = rec_alloc(0x20);
  if (sub == NULL) { NoopFn0042243f(); return 0; }   /* «Out of memory» */
  memset(sub, 0, 0x20);
  if (P105_EmulSurface(sub) == 0) { NoopFn0042243f(); rec_free(sub); return 0; }   /* «CreateEmulatedTexture() failed» */
  memcpy(sub, last, 4);
  wr32(sub + 4, (uint32_t)kind);
  wr32(sub + 0xc, (uint32_t)pal);
  wr32(sub + 0x18, 0);
  wr32(sub + 0x1c, 0);
  re_wr_ptr(last + 0x18, sub);
  return emul_upload(sub, src, pal);
}

/* ---- 004225eb ---- */
/* P149_EmulNew — Game.exe 004225eb.  New emulated texture node for page `handle` (kind, palette pal) at the head
   of P46_TexHead, creates its surface and uploads it.  Returns 1 on success, 0 on failure. */
int32_t P149_EmulNew(int32_t handle, int32_t src, int32_t kind, int32_t pal) {
#ifdef RE_HOOK_BUILD
  P46_TexNode *n = (P46_TexNode *)g_malloc(0x20);
#else
  P46_TexNode *n = (P46_TexNode *)rec_alloc((uint32_t)sizeof(P46_TexNode));   /* next — родной указатель */
#endif
  if (n == NULL) { NoopFn0042243f(); return 0; }
  memset(n, 0, sizeof *n);
  uint8_t *o = (uint8_t *)n;
  if (P105_EmulSurface(o) == 0) { NoopFn0042243f(); rec_free(n); return 0; }
  n->handle = handle;
  wr32(o + 4, (uint32_t)kind);
  wr32(o + 0xc, (uint32_t)pal);
  wr32(o + 0x18, 0);
  n->next = P46_TexHead;
  P46_TexHead = n;
  return emul_upload(o, src, pal);
}
