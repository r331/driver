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

static uint32_t rd32(const uint8_t *p) { uint32_t v; memcpy(&v, p, 4); return v; }
static void wr32(uint8_t *p, uint32_t v) { memcpy(p, &v, 4); }

/* strcpy(0052b100) в запись с полем имени 0x20; в native — с границей поля */
static void copy_name(uint8_t *dst, const char *src) {
#ifdef RE_HOOK_BUILD
  strcpy((char *)dst, src);
#else
  size_t n = strlen(src); if (n > 0x1f) n = 0x1f;
  memcpy(dst, src, n); dst[n] = 0;
#endif
}

/* память записи с 32-битными ссылками: в native регистрируется целиком (адреса внутри записи) */
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
int32_t P149_D3DDevCb(const void *guid, const char *desc, const char *name, const void *hw, const void *hel, void *ctx) {
  (void)desc;
  uint8_t *dd = (uint8_t *)ctx;
  if (guid == NULL || rd32((const uint8_t *)hw + 8) == 0 || dd == NULL) return 1;
  uint8_t *r = rec_alloc(0x230);
  if (r == NULL) return 1;
  memset(r, 0, 0x230);
  copy_name(r, name);
  memcpy(r + 0x30, hw, 0xfc);
  memcpy(r + 0x12c, hel, 0xfc);
  memcpy(r + 0x20, guid, 16);
  wr32(r + 0x228, 0);
  wr32(r + 0x22c, rd32(dd + 0x38));
  if (rd32(dd + 0x34) == 0) {
    re_wr_ptr(dd + 0x34, r);
  } else {
    re_wr_ptr((uint8_t *)re_rd_ptr(dd + 0x38) + 0x228, r);
  }
  re_wr_ptr(dd + 0x38, r);
  return 1;
}

/* ---- 0041fac0 ---- */
int32_t P149_DDEnumCb(const void *guid, const char *desc, const char *name, void *ctx) {
  (void)name; (void)ctx;
  uint8_t *r = rec_alloc(0x44);
  if (r == NULL) return 1;
  memset(r, 0, 0x44);
  copy_name(r, desc);
  void *dd = plat_dd_create(guid);
  if (dd == NULL) { rec_free(r); return 1; }
  void *dd4 = P39_QueryDD4(dd);
  if (dd4 == NULL) { plat_dd_release(dd); rec_free(r); return 1; }
  void *d3d = P39_QueryD3D(dd4);
  if (d3d == NULL) { plat_dd_release(dd4); plat_dd_release(dd); rec_free(r); return 1; }
  if (plat_d3d_enum_devices(d3d, P149_D3DDevCb, r) != 0) {
    plat_dd_release(d3d); plat_dd_release(dd4); plat_dd_release(dd);
    rec_free(r);
    return 1;
  }
  if (guid == NULL) wr32(r + 0x30, 1);
  else { memcpy(r + 0x20, guid, 16); wr32(r + 0x30, 0); }
  wr32(r + 0x3c, 0);
  if (P149_DDHead == 0) {
    wr32(r + 0x40, 0);
    P149_DDHead = re_addr(r);
  } else {
    wr32(r + 0x40, P149_DDTail);
    re_wr_ptr((uint8_t *)re_ptr(P149_DDTail) + 0x3c, r);
  }
  P149_DDTail = re_addr(r);
  plat_dd_release(d3d); plat_dd_release(dd4); plat_dd_release(dd);
  return 1;
}

/* строка n таблицы устройств: в native у 01270ec4 есть второй псевдоним P42_DevNames (правило v1.78) */
static void dev_mirror(int32_t n) {
#ifndef RE_HOOK_BUILD
  if (n >= 0 && n < 16) memcpy(P42_DevNames[n], (uint8_t *)&P74_DevTab[0] + (size_t)n * 0x4c + 4, 0x48);
#else
  (void)n;
#endif
}

/* ---- 0041fe07 ---- */
void P149_BuildDevs(void) {
  uint8_t *dd = (uint8_t *)re_ptr(P149_DDHead);
  while (dd != NULL) {
    uint8_t *ddn = (uint8_t *)re_rd_ptr(dd + 0x3c);
    uint8_t *dv = (uint8_t *)re_rd_ptr(dd + 0x34);
    while (dv != NULL) {
      uint8_t *dvn = (uint8_t *)re_rd_ptr(dv + 0x228);
      if (P42_DevCount < 4) {
        int32_t n = P42_DevCount;
        uint8_t *r = rec_alloc(0x590);
        memset(r, 0, 0x590);
        uint8_t *e = (uint8_t *)&P74_DevTab[0] + (size_t)n * 0x4c;
        memset(e, 0, 0x4c);
        sprintf((char *)e + 4, "%s", (const char *)dd);
        sprintf((char *)e + 0x24, "%s", (const char *)dv);
        wr32(e, 1);
        re_wr_ptr(e + 0x48, r);
        memcpy(r + 0x320, dv + 0x30, 0xfc);
        memcpy(r + 0x41c, dv + 0x12c, 0xfc);
        wr32(r, 0);
        if (rd32(dd + 0x30) == 0) {
          memcpy(r + 4, dd + 0x20, 16);
          re_wr_ptr(r, r + 4);
        }
        memcpy(r + 0x18, dv + 0x20, 16);
        re_wr_ptr(r + 0x14, r + 0x18);
        dev_mirror(n);
        if (P151_CheckDev(e) == 0) {
          rec_free(r);
        } else {
          wr32(e + 0x44, rd32(r + 0x588) == 0 ? 1u : 0u);
          dev_mirror(n);
          P42_DevCount = n + 1;
        }
      }
      rec_free(dv);
      dv = dvn;
    }
    rec_free(dd);
    dd = ddn;
  }
}

/* ---- 0041ce90 ---- */
int32_t P149_DDEnumAll(void) {
  NoopFn0042243f();
  int32_t hr = plat_dd_enumerate(P149_DDEnumCb, NULL);
  int32_t old = P42_DevCount;
  if (hr != 0) return 0;
  P149_BuildDevs();
  return P42_DevCount != old ? 1 : 0;
}

/* Release IDirect3DTexture2 / поверхности узла (+0x14 / +0x10) */
static void emul_release(uint8_t *n) {
  void *t = re_rd_ptr(n + 0x14);
  if (rd32(n + 0x14) != 0) {
    if (P32_CurHandle == t) P32_CurHandle = NULL;
    plat_dd_release(t);
    wr32(n + 0x14, 0);
  }
  if (rd32(n + 0x10) != 0) {
    plat_dd_release(re_rd_ptr(n + 0x10));
    wr32(n + 0x10, 0);
  }
}

/* ---- 0041d6aa ---- */
void P149_EmulFreeAll(void) {
  P46_TexNode *n = P46_TexHead;
  while (n != NULL) {
    NoopFn0042243f();                      /* «Releasing emulated texture set» */
    P46_TexNode *next = n->next;
    uint8_t *s = (uint8_t *)re_rd_ptr((uint8_t *)n + 0x18);
    while (s != NULL) {
      NoopFn0042243f();                    /* «Releasing emulated texture» */
      uint8_t *sn = (uint8_t *)re_rd_ptr(s + 0x18);
      emul_release(s);
      rec_free(s);
      s = sn;
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
static int32_t emul_upload(uint8_t *o, int32_t src, int32_t pal) {
  uint32_t d[31];
  memset(d, 0, sizeof d);
  d[0] = 0x7c;
  void *s = re_rd_ptr(o + 0x10);
  if (plat_dd_lock(s, d) != 0) { NoopFn0042243f(); return 0; }   /* «Lock emultexture8() failed» */
#ifndef RE_HOOK_BUILD
  if (re_ptr(d[9]) != NULL && re_ptr((uint32_t)src) != NULL && re_ptr((uint32_t)pal) != NULL)
#endif
  P74_Conv8to16((const uint8_t *)re_ptr((uint32_t)src), (const uint8_t *)re_ptr((uint32_t)pal),
                (uint16_t *)re_ptr(d[9]), (int32_t)d[4]);
  plat_dd_unlock(s);
#ifndef RE_HOOK_BUILD
  P86_GameAttachEmul8(s, (int32_t)rd32(o), (int32_t)rd32(o + 4));   /* v2.18: HD-пак — пара (страница = handle, слот палитры = +4) */
#endif
  return 1;
}

/* ---- 0042248b ---- */
int32_t P149_EmulAddSub(void *node, int32_t src, int32_t kind, int32_t pal) {
  uint8_t *p = (uint8_t *)node;
  for (uint8_t *q; (q = (uint8_t *)re_rd_ptr(p + 0x18)) != NULL; ) p = q;
  uint8_t *o = rec_alloc(0x20);
  if (o == NULL) { NoopFn0042243f(); return 0; }   /* «Out of memory» */
  memset(o, 0, 0x20);
  if (P105_EmulSurface(o) == 0) { NoopFn0042243f(); rec_free(o); return 0; }   /* «CreateEmulatedTexture() failed» */
  memcpy(o, p, 4);
  wr32(o + 4, (uint32_t)kind);
  wr32(o + 0xc, (uint32_t)pal);
  wr32(o + 0x18, 0);
  wr32(o + 0x1c, 0);
  re_wr_ptr(p + 0x18, o);
  return emul_upload(o, src, pal);
}

/* ---- 004225eb ---- */
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
