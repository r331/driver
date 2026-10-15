/* Реестр «адрес Game.exe ↔ native-объект» (v1.42). См. reptr.h. */
#include "reptr.h"
#ifdef RE_HOOK_BUILD
void    *re_ptr(uint32_t addr) { return (void *)(uintptr_t)addr; }
uint32_t re_addr(const void *p) { return (uint32_t)(uintptr_t)p; }
void     re_ptr_register(uint32_t addr, void *native, uint32_t size) { (void)addr; (void)native; (void)size; }
uint32_t re_ptr_register_dyn(void *native, uint32_t size) { (void)size; return (uint32_t)(uintptr_t)native; }
void     re_ptr_unregister(const void *native) { (void)native; }
re_fn_t  re_fn(uint32_t addr) { return (re_fn_t)(uintptr_t)addr; }
uint32_t re_fn_addr(re_fn_t fn) { return (uint32_t)(uintptr_t)fn; }
void     re_fn_register(uint32_t addr, re_fn_t fn) { (void)addr; (void)fn; }
#else
#include "ported26.h"
#include "ported38.h"
#include "ported49.h"
#include "ported50.h"
#include "ported62.h"
#include "ported95.h"
#include "ported96.h"
#include "ported97.h"
#include "ported98.h"
#include "noop.h"
#include <string.h>

typedef struct { uint32_t addr; uint8_t *p; uint32_t size; } re_region_t;
typedef struct { uint32_t addr; re_fn_t fn; } re_fnent_t;

/* статические области: GAME_VAR-массивы, на которые в таблицах игры лежат адреса */
static const re_region_t k_regions[] = {
  { 0x010f5160u, P95_ObjA, sizeof P95_ObjA },
  { 0x0110e500u, P95_ObjB, sizeof P95_ObjB },
  { 0x011237c0u, P95_ObjC, sizeof P95_ObjC },
  { 0x00b5b378u, P62_Hs1, sizeof P62_Hs1 },
  { 0x00b5ba58u, P62_Hs2, sizeof P62_Hs2 },
  { 0x00b5b008u, P62_Hs3, sizeof P62_Hs3 },
  { 0x00b5ac98u, P62_Hs4, sizeof P62_Hs4 },
  { 0x00b5a928u, P62_Hs5, sizeof P62_Hs5 },
  { 0x00b5c138u, P62_Hs6, sizeof P62_Hs6 },
  { 0x00d0fe40u, (uint8_t *)P96_LogBuf, sizeof P96_LogBuf },
  { 0x005fe4e4u, (uint8_t *)P97_FpsTxtA, sizeof P97_FpsTxtA },
  { 0x005fea74u, (uint8_t *)P97_FpsTxtB, sizeof P97_FpsTxtB },
  { 0x00c80c60u, (uint8_t *)P97_MsgBuf, sizeof P97_MsgBuf },
  { 0x005755ecu, (uint8_t *)P97_Str8bit, sizeof P97_Str8bit },
  { 0x005755f4u, (uint8_t *)P97_Str16bit, sizeof P97_Str16bit },
  { 0x005755fcu, (uint8_t *)P97_Str22k, sizeof P97_Str22k },
  { 0x00575608u, (uint8_t *)P97_Str44k, sizeof P97_Str44k },
  { 0x005532ccu, P98_FaceBlk, sizeof P98_FaceBlk },              /* имена лиц титров (00552e1c → сюда) */
};
/* таблица функций: адрес Game.exe → перенесённая native-функция */
static const re_fnent_t k_fns[] = {
  { 0x0048bcc0u, (re_fn_t)P50_SoundShutdown }, { 0x0048bd3bu, (re_fn_t)NoopFn0048bd3b },
  { 0x0048bd40u, (re_fn_t)P49_Commit },        { 0x0048bd65u, (re_fn_t)P26_WaveSetVolume },
  { 0x0048bdccu, (re_fn_t)P38_SetPrimaryFormat }, { 0x0048be68u, (re_fn_t)P38_SetSpeakerConfig },
  { 0x0048c520u, (re_fn_t)P50_ReleaseVoice },  { 0x0048c74bu, (re_fn_t)P49_ListenerPos },
  { 0x0048c77eu, (re_fn_t)P49_ListenerOrient }, { 0x0048c7bdu, (re_fn_t)P49_ListenerVel },
  { 0x0048c7f0u, (re_fn_t)P49_Play },          { 0x0048c83du, (re_fn_t)P50_ReleaseBuf },
  { 0x0048c8d6u, (re_fn_t)P50_ResetBuf },      { 0x0048c97cu, (re_fn_t)P49_SetVolume },
  { 0x0048c9b2u, (re_fn_t)P49_SetFreq },       { 0x0048c9e8u, (re_fn_t)P49_SetPos3D },
  { 0x0048ca28u, (re_fn_t)P49_SetVel3D },      { 0x0048ca68u, (re_fn_t)P49_SetMode3D },
  { 0x0048caa0u, (re_fn_t)P49_GetStatus },
};
#define RE_DYN_MAX 4096
#define RE_FN_MAX 512
static re_region_t g_dyn[RE_DYN_MAX];
static uint32_t g_ndyn, g_next_syn = 0x80000000u;
static re_fnent_t g_fns[RE_FN_MAX];
static uint32_t g_nfns;

void *re_ptr(uint32_t addr) {
  if (addr == 0) return NULL;
  for (uint32_t i = 0; i < g_ndyn; i++)
    if (addr >= g_dyn[i].addr && addr - g_dyn[i].addr < g_dyn[i].size) return g_dyn[i].p + (addr - g_dyn[i].addr);
  for (size_t i = 0; i < sizeof k_regions / sizeof k_regions[0]; i++)
    if (addr >= k_regions[i].addr && addr - k_regions[i].addr < k_regions[i].size) return k_regions[i].p + (addr - k_regions[i].addr);
  return NULL;
}
uint32_t re_addr(const void *pv) {
  const uint8_t *p = (const uint8_t *)pv;
  if (p == NULL) return 0;
  for (uint32_t i = 0; i < g_ndyn; i++)
    if (p >= g_dyn[i].p && p < g_dyn[i].p + g_dyn[i].size) return g_dyn[i].addr + (uint32_t)(p - g_dyn[i].p);
  for (size_t i = 0; i < sizeof k_regions / sizeof k_regions[0]; i++)
    if (p >= k_regions[i].p && p < k_regions[i].p + k_regions[i].size) return k_regions[i].addr + (uint32_t)(p - k_regions[i].p);
  return re_ptr_register_dyn((void *)(uintptr_t)p, 1);
}
void re_ptr_register(uint32_t addr, void *native, uint32_t size) {
  if (native == NULL || size == 0) return;
  for (uint32_t i = 0; i < g_ndyn; i++)
    if (g_dyn[i].p == native) { g_dyn[i].addr = addr; g_dyn[i].size = size; return; }
  if (g_ndyn < RE_DYN_MAX) { g_dyn[g_ndyn].addr = addr; g_dyn[g_ndyn].p = (uint8_t *)native; g_dyn[g_ndyn].size = size; g_ndyn++; }
}
uint32_t re_ptr_register_dyn(void *native, uint32_t size) {
  if (native == NULL || g_ndyn >= RE_DYN_MAX) return 0;
  uint32_t a = g_next_syn;
  g_next_syn += (size + 0xfu) & ~0xfu;
  re_ptr_register(a, native, size);
  return a;
}
void re_ptr_unregister(const void *native) {
  for (uint32_t i = 0; i < g_ndyn; i++)
    if (g_dyn[i].p == native) { g_dyn[i] = g_dyn[--g_ndyn]; return; }
}
re_fn_t re_fn(uint32_t addr) {
  if (addr == 0) return NULL;
  for (uint32_t i = 0; i < g_nfns; i++) if (g_fns[i].addr == addr) return g_fns[i].fn;
  for (size_t i = 0; i < sizeof k_fns / sizeof k_fns[0]; i++) if (k_fns[i].addr == addr) return k_fns[i].fn;
  return NULL;
}
uint32_t re_fn_addr(re_fn_t fn) {
  if (fn == NULL) return 0;
  for (uint32_t i = 0; i < g_nfns; i++) if (g_fns[i].fn == fn) return g_fns[i].addr;
  for (size_t i = 0; i < sizeof k_fns / sizeof k_fns[0]; i++) if (k_fns[i].fn == fn) return k_fns[i].addr;
  return 0;
}
void re_fn_register(uint32_t addr, re_fn_t fn) {
  for (uint32_t i = 0; i < g_nfns; i++) if (g_fns[i].addr == addr) { g_fns[i].fn = fn; return; }
  if (g_nfns < RE_FN_MAX) { g_fns[g_nfns].addr = addr; g_fns[g_nfns].fn = fn; g_nfns++; }
}
#endif
