/* v1.93: ported148 — блок DirectSound (Game\eax\directsound.c), см. ported148.h.
   0048ba20 — DirectSoundEnumerateA(0048cdab, 0) → plat_ds_enumerate.
   0048cdab — колбэк (stdcall, 4 аргумента, ret 0x10): не больше 8 драйверов (иначе 0 — стоп); DirectSoundCreate(guid),
     GetCaps (DSCAPS 0x60 байт), Release; ошибка создания/GetCaps — 1 (дальше); guid ≠ NULL и DSCAPS_EMULDRIVER (0x20) — 1
     без записи; запись 00bdcb60 + n·0x34: адрес GUID (+4) или 0 и нулевой GUID, имя (< 0x20 — strcpy, иначе 0x1c + "...").
   0048ba31 — режим 1: 00b1f434 = 1, EAX = 1; 2: 1/0; иначе 0/1. DirectSoundCreate(драйвер), SetCooperativeLevel(hwnd, 3),
     CreateSoundBuffer(0x14, 0x11 PRIMARY|CTRL3D), QI(IID_IDirectSound3DListener 00546320), Play(0,0,LOOPING);
     любая ошибка — 0048bcc0 (P50_SoundShutdown), 0. Успех: 0048cc64 = 0 → 0048ccaf; EAX → 0048cbd3; 0048bbd5; 1.
   0048c192 — 0048c43c(образ, fmt, data, size); soft = 0: флаги 0xb2 (STATIC|CTRL3D|CTRLFREQUENCY|CTRLVOLUME), иначе/при
     отказе — 0xba (+LOCSOFTWARE); буфер заливается 0048c47e, при отказе заливки — Release.
   0048c2a3 — DuplicateSoundBuffer(голос n → P49_Bufs[voice]); DSERR_BUFFERLOST 0x88780096 → 0048c520(n), 0048bf9a(n, имя
     +8) = 0 → 0048c83d(voice), 0; иначе повтор. Успех: SetCurrentPosition(0), QI(IID_IDirectSound3DBuffer 00546330) → +4.
   0048c3e7 — 0048c43c(образ, NULL, data, size), Restore (≥ 0), заливка.
   0048c47e — Lock(0, size, …, 0) ≥ 0: копия в две части (0052b650 = memcpy), Unlock; 1.
   0048cad6 — QI(IID_IKsPropertySet 00546370), QuerySupport(00546740, 0) и (00546750, 0) — маска 3, иначе Release, NULL. */
#include "ported148.h"
#include "ported38.h"
#include "ported49.h"
#include "ported50.h"
#include "ported97.h"
#include "ported100.h"
#include "ported140.h"
#include "ported6.h"
#include "reptr.h"
#include "../platform/plat.h"
#include <string.h>

GAME_VAR_DEF(p148_drvtab_t, P148_Drv, 0x00bdcb60)
#ifndef RE_HOOK_BUILD
#pragma push_macro("P148_EaxOn") /*gvi*/
#undef P148_EaxOn /*gvi*/
int32_t P148_EaxOn = 1;                     /* .data 005511e8 */
#pragma pop_macro("P148_EaxOn") /*gvi*/
#endif

static const uint8_t g_iid_l3d[16]   = { 0x84,0xfa,0x9a,0x27,0x81,0x49,0xce,0x11,0xa5,0x21,0x00,0x20,0xaf,0x0b,0xe5,0x60 };  /* 00546320 */
static const uint8_t g_iid_b3d[16]   = { 0x86,0xfa,0x9a,0x27,0x81,0x49,0xce,0x11,0xa5,0x21,0x00,0x20,0xaf,0x0b,0xe5,0x60 };  /* 00546330 */
static const uint8_t g_iid_ksprop[16] = { 0x30,0xac,0xef,0x31,0x5c,0x51,0xd0,0x11,0xa9,0xaa,0x00,0xaa,0x00,0x61,0xbe,0x93 }; /* 00546370 */
static const uint8_t g_guid_eaxa[16] = { 0xc1,0x6f,0x4e,0x4a,0x41,0xc3,0xd1,0x11,0xb7,0x3a,0x44,0x45,0x53,0x54,0x00,0x00 };  /* 00546740 */
static const uint8_t g_guid_eaxb[16] = { 0xc0,0x6f,0x4e,0x4a,0x41,0xc3,0xd1,0x11,0xb7,0x3a,0x44,0x45,0x53,0x54,0x00,0x00 };  /* 00546750 */

/* ---- 0048cdab ---- */
int32_t P148_EnumCb(const void *guid, const char *desc, const char *module, void *ctx) {
  (void)module; (void)ctx;
  int32_t n = G6_00B91D2C;
  if (n >= 8) return 0;
  void *ds = NULL; uint32_t caps = 0;
  if (plat_ds_create(guid, &ds) != 0) return 1;
  int32_t hr = plat_ds_get_caps_flags(ds, &caps);
  plat_dd_release(ds);
  if (hr != 0) return 1;
  p148_drv_t *e = &P148_Drv[n];
  if (guid == NULL) {
    memset(e->guid, 0, 16);
    e->guid_ptr = 0;
  } else {
    if ((caps & 0x20) != 0) return 1;
    memcpy(e->guid, guid, 16);
    e->guid_ptr = re_addr(e->guid);
  }
  if ((int32_t)strlen(desc) < 0x20) strcpy(e->name, desc);
  else { strncpy(e->name, desc, 0x1c); e->name[0x1c] = '.'; e->name[0x1d] = '.'; e->name[0x1e] = '.'; e->name[0x1f] = 0; }
  G6_00B91D2C = n + 1;
  return 1;
}

/* ---- 0048ba20 ---- */
void P148_SndEnum(void) { plat_ds_enumerate(P148_EnumCb, NULL); }

/* ---- 0048ba31 ---- */
int32_t P148_SndOpen(int32_t drv, int32_t mode, int32_t hwnd) {
  if (drv < 0 || G6_00B91D2C <= drv) return 0;
  if (mode == 1) { P140_B1F434 = 1; P148_EaxOn = 1; }
  else if (mode == 2) { P140_B1F434 = 1; P148_EaxOn = 0; }
  else { P140_B1F434 = 0; P148_EaxOn = 1; }
  uint32_t g = P148_Drv[drv].guid_ptr;
  if (plat_ds_create(g != 0 ? re_ptr(g) : NULL, &P38_Ds) != 0 ||
      plat_ds_set_coop(P38_Ds, (void *)(intptr_t)hwnd, 3) != 0 ||
      plat_ds_create_buffer(P38_Ds, 0x11, 0, NULL, &P38_DsPrimary) != 0 ||
      plat_com_query_interface(P38_DsPrimary, g_iid_l3d, &P49_Listener) != 0 ||
      plat_ds_buf_play(P38_DsPrimary, 1) != 0) {
    P50_SoundShutdown();
    return 0;
  }
  if (P50_CreateKsProps() == 0) P49_ReleaseProps();
  if (P148_EaxOn != 0) P50_EaxEnable();
  P97_SndDrvInit();
  return 1;
}

/* ---- 0048c47e ---- */
int32_t P148_Fill(void *buf, const void *data, uint32_t size) {
  void *p1, *p2; uint32_t n1, n2;
  if (buf == NULL || data == NULL || size == 0) return 0;
  if (plat_ds_buf_lock(buf, size, &p1, &n1, &p2, &n2) < 0) return 0;
  memcpy(p1, data, n1);
  if (n2 != 0) memcpy(p2, (const uint8_t *)data + n1, n2);
  plat_ds_buf_unlock(buf, p1, n1, p2, n2);
  return 1;
}

/* ---- 0048c192 ---- */
void *P148_BufFromWav(void *ds, const void *wav, int32_t soft) {
  const void *fmt = NULL, *data = NULL; uint32_t size = 0; void *b = NULL;
  if (P100_RiffFromRes((void *)wav, &fmt, &data, &size) == 0) return NULL;
  if (soft == 0) {
    if (plat_ds_create_buffer(ds, 0xb2, size, fmt, &b) == 0) {
      if (P148_Fill(b, data, size) != 0) return b;
      plat_dd_release(b);
      b = NULL;
    }
  }
  if (plat_ds_create_buffer(ds, 0xba, size, fmt, &b) == 0) {
    if (P148_Fill(b, data, size) != 0) return b;
    plat_dd_release(b);
  }
  return NULL;
}

/* ---- 0048c2a3 ---- */
int32_t P148_DupVoice(int32_t n, int32_t voice) {
  P50_Voice *v = &P50_Voices[n];
  P49_Pair *p = &P49_Bufs[voice];
  if (v->a == NULL) return 0;
  int32_t hr = plat_ds_duplicate(P38_Ds, v->a, &p->buf);
  if ((uint32_t)hr == 0x88780096u) {           /* DSERR_BUFFERLOST */
    P50_ReleaseVoice(n);
    if (P140_SndLoadWav(n, (const char *)v->rest) == 0) { P50_ReleaseBuf(voice); return 0; }
    hr = plat_ds_duplicate(P38_Ds, v->a, &p->buf);
  }
  if (hr != 0) { P50_ReleaseBuf(voice); return 0; }
  plat_ds_buf_set_position(p->buf, 0);
  if (plat_com_query_interface(p->buf, g_iid_b3d, &p->buf3d) != 0) { P50_ReleaseBuf(voice); return 0; }
  return 1;
}

/* ---- 0048c3e7 ---- */
int32_t P148_Refill(void *buf, const void *wav) {
  const void *data = NULL; uint32_t size = 0;
  if (P100_RiffFromRes((void *)wav, NULL, &data, &size) == 0) return 0;
  if (plat_ds_buf_restore(buf) < 0) return 0;
  return P148_Fill(buf, data, size) != 0;
}

/* ---- 0048cad6 ---- */
void *P148_KsProps(void *buf) {
  void *ps = NULL; uint32_t sup = 0;
  if (plat_com_query_interface(buf, g_iid_ksprop, &ps) != 0) return NULL;
  if (plat_ds_prop_support(ps, g_guid_eaxa, 0, &sup) != 0 || (sup & 3) != 3 ||
      plat_ds_prop_support(ps, g_guid_eaxb, 0, &sup) != 0 || (sup & 3) != 3) {
    plat_dd_release(ps);
    return NULL;
  }
  return ps;
}
