/* v1.96: ported151 — см. ported151.h.
   0041cede — idx ∈ [0, 00b1c0e0): 00a421cc = idx; 123 ячейки 01270c58..01271024 ← адреса функций эмуляции Glide через D3D
     (0041d8e9..0041fab9, 00421cab, метка 0041e3b0 в grDepthBufferMode, 0041ed98 — grSstWinOpen); 00a421ec, 00a421f4 ← аргументы.
     native: ячейки таблицы имён — P33_SetNativeProcAt(адрес, re_fn(функция)), ячейки с отдельными native-переменными — они же;
     функции эмуляции зарегистрированы в k_fns game/reptr.c (метка 0041e3b0 — нет, ячейка получает NULL, вызов пропускается).
   0041ed98 — повторное открытие: «WARNING: Hardware already allocated» + 0041f2a0; окно (или GetActiveWindow); при mode ≠ 0xff
     ShowWindow(MAXIMIZE), 00a421c4 = 1; devinfo = запись 00a421cc +0x48; 00420b19/QI DD4/QI D3D3; оконный: Coop 8, клиентская
     область, 00421149; полноэкранный: Coop 0x11, режим по коду (1 320x240, 3 512x384, 7 640x480, 8 800x600, 0xc 1024x768,
     0xd 1280x1024, 0xe 1600x1200), 0042101b, 0042106d; Z 004213dc; устройство 00420cfe; флаги 00a421dc из caps devinfo
     (+0x394/+0x398/+0x38c/+0x354); вьюпорт 00420d5d/00420dad; 00a421f0 = +0x588 (или 1 по 00a421ec); 004219e8, 00421521;
     размеры; дважды grBufferClear(0,0,0xffff) + grBufferSwap(0) через таблицу. Любой отказ после QI D3D3 → 0041f2a0, 0.
   00420038 — HAL (+0x320, если +0x328 ≠ 0, +0x518 = 1) или HEL (+0x41c); проверки флагов, TLVERTEX, DrawPrimitive, 256x256;
     +0x51c..+0x524; DirectDrawCreate(guid +0) → QI DD4 → Coop(NULL, 8) → GetCaps(+0x28, +0x1a4) → нет DDCAPS2 2 → QI D3D3 →
     поверхность 0x2200 → устройство (guid +0x14) → EnumTextureFormats/EnumZBufferFormats колбэком 00420854 → 8-бит (+0x58c & 7)
     или копия формата +0x528 → +0x548 и +0x588 = 1 → 00420a21; объекты освобождаются в обратном порядке.
   00425f7b — MoveWindow(0,0,ScrW,ScrH,1); 00425a50, 005283e2, grSstSelect(0); mode 0 — 0042467f(hwnd,0xff,…), mode 1 — код
     разрешения по ширине (320/512/640/800/1024/1280/1600), иначе 0; таблицы обработчиков 011effe0/01209660/011f4060 по 00bdfa18;
     grDepthBufferMode(2), 0042655a(1), grDepthBufferFunction(3), grCullMode(0); keep = 0 — масштаб 1.0, 00425b12(0,0,1), 01270c20,
     01270c30; 0125f3ec/01270c34 = −1; grAlphaTestReferenceValue(0x82), grConstantColorValue(0xbb000000), 0042626e,
     grTexCombineFunction(0,1); 01252bc0 = −1, 01251a70 = 1.
   00521f10 — WinMain: начальные значения, журнал (6 строк), 005223be/005222cf, InitWindow, config.dat (иначе строка языка 0x132 →
     00b87d0c → фатальная ошибка), 005226b5(hinst, show, 2), ускорители, таймеры, приоритет процесса, курсор, хранитель экрана,
     004d33c0 → фронтенд/игра/меню → завершение подсистем; код 0xc9 — MessageBox «The lead car went out of range!». */
#include "ported151.h"
#ifndef RE_HOOK_BUILD
#include <stdio.h>
#include <stdlib.h>
#define RE_TRACE_FAIL() do { if (getenv("RE_TRACE")) fprintf(stderr, "[trace] %s: 0 at %s:%d\n", __func__, __FILE__, __LINE__); } while (0)
#else
#define RE_TRACE_FAIL() ((void)0)
#endif
#include "ported6.h"
#include "ported11.h"
#include "ported12.h"
#include "ported14.h"
#include "ported19.h"
#include "ported22.h"
#include "ported23.h"
#include "ported24.h"
#include "ported25.h"
#include "ported27.h"
#include "ported30.h"
#include "ported31.h"
#include "ported32.h"
#include "ported33.h"
#include "ported35.h"
#include "ported39.h"
#include "ported42.h"
#include "ported44.h"
#include "ported47.h"
#include "ported48.h"
#include "ported52.h"
#include "ported55.h"
#include "ported58.h"
#include "ported62.h"
#include "ported69.h"
#include "ported74.h"
#include "ported84.h"
#include "ported85.h"
#include "ported86.h"
#include "ported95.h"
#include "ported96.h"
#include "ported97.h"
#include "ported98.h"
#include "ported99.h"
#include "ported100.h"
#include "ported102.h"
#include "ported106.h"
#include "ported109.h"
#include "ported110.h"
#include "ported115.h"
#include "ported117.h"
#include "ported124.h"
#include "ported126.h"
#include "ported132.h"
#include "ported133.h"
#include "ported136.h"
#include "ported140.h"
#include "ported5.h"
#include "menustate.h"
#include "uihandlers.h"
#include "uihandlers2.h"
#include "uihandlers3.h"
#include "uihandlers4.h"
#include "smallfuncs.h"
#include "noop.h"
#include "strtab.h"
#include "smallfuncs2.h"
#include "ported7.h"
#include "reptr.h"
#include "../platform/plat.h"
#include <string.h>

#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P151_DevIdx")
#undef P151_DevIdx
#pragma push_macro("P151_DevIdx") /*gvi*/
#undef P151_DevIdx /*gvi*/
int32_t P151_DevIdx;
#pragma pop_macro("P151_DevIdx") /*gvi*/
#pragma pop_macro("P151_DevIdx")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P151_No8bit")
#undef P151_No8bit
#pragma push_macro("P151_No8bit") /*gvi*/
#undef P151_No8bit /*gvi*/
int32_t P151_No8bit;
#pragma pop_macro("P151_No8bit") /*gvi*/
#pragma pop_macro("P151_No8bit")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P151_FsFlag")
#undef P151_FsFlag
#pragma push_macro("P151_FsFlag") /*gvi*/
#undef P151_FsFlag /*gvi*/
int32_t P151_FsFlag;
#pragma pop_macro("P151_FsFlag") /*gvi*/
#pragma pop_macro("P151_FsFlag")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P151_Bpp")
#undef P151_Bpp
#pragma push_macro("P151_Bpp") /*gvi*/
#undef P151_Bpp /*gvi*/
int32_t P151_Bpp;
#pragma pop_macro("P151_Bpp") /*gvi*/
#pragma pop_macro("P151_Bpp")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P151_ErrBuf")
#undef P151_ErrBuf
#pragma push_macro("P151_ErrBuf") /*gvi*/
#undef P151_ErrBuf /*gvi*/
p151_buf_t P151_ErrBuf;
#pragma pop_macro("P151_ErrBuf") /*gvi*/
#pragma pop_macro("P151_ErrBuf")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P151_Empty10")
#undef P151_Empty10
#pragma push_macro("P151_Empty10") /*gvi*/
#undef P151_Empty10 /*gvi*/
int32_t P151_Empty10;
#pragma pop_macro("P151_Empty10") /*gvi*/
#pragma pop_macro("P151_Empty10")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P151_Empty14")
#undef P151_Empty14
#pragma push_macro("P151_Empty14") /*gvi*/
#undef P151_Empty14 /*gvi*/
int32_t P151_Empty14;
#pragma pop_macro("P151_Empty14") /*gvi*/
#pragma pop_macro("P151_Empty14")
#endif
GAME_VAR_DEF(void *, P151_Proc, 0x00bdfa1c)
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P151_PrioOn")
#undef P151_PrioOn
#pragma push_macro("P151_PrioOn") /*gvi*/
#undef P151_PrioOn /*gvi*/
int32_t P151_PrioOn;
#pragma pop_macro("P151_PrioOn") /*gvi*/
#pragma pop_macro("P151_PrioOn")
#endif

#ifdef RE_HOOK_BUILD
#  define P151_STD __attribute__((stdcall))
#  define SLOT(addr, name) (*(void **)(uintptr_t)(addr))
#else
#  define P151_STD
#  define SLOT(addr, name) glide_proc(name)
static void *glide_proc(const char *name) {
  for (int i = 0; i < P33_GlideCount(); i++)
    if (strcmp(P33_GlideName(i), name) == 0) return P33_GlideProc(i);
  return NULL;
}
#endif
static uint32_t rd32(const uint8_t *p) { uint32_t v; memcpy(&v, p, 4); return v; }
static void wr32(uint8_t *p, uint32_t v) { memcpy(p, &v, 4); }
static float __attribute__((unused)) u2f(uint32_t u) { float f; memcpy(&f, &u, 4); return f; }
static void call_i1(void *f, int32_t a) { if (f) ((void (P151_STD *)(int32_t))f)(a); }
static void call_i2(void *f, int32_t a, int32_t b) { if (f) ((void (P151_STD *)(int32_t, int32_t))f)(a, b); }
static void call_i3(void *f, int32_t a, int32_t b, int32_t c) { if (f) ((void (P151_STD *)(int32_t, int32_t, int32_t))f)(a, b, c); }

/* ---- 0041cede ---- */
static const struct { uint32_t slot, fn; } k_d3d_tab[] = {
  { 0x01270d90u, 0x0041d9afu }, { 0x01270dc0u, 0x0041d9b6u }, { 0x01270d48u, 0x0041d9bdu }, { 0x01270da0u, 0x0041d9c4u },
  { 0x01270d38u, 0x0041d9cbu }, { 0x01270dd0u, 0x0041d9d2u }, { 0x01270dccu, 0x0041dd37u }, { 0x01270e48u, 0x0041ddbeu },
  { 0x01270d68u, 0x0041ddc5u }, { 0x01270d58u, 0x0041de1du }, { 0x01270e8cu, 0x0041de46u }, { 0x01270d24u, 0x0041dec1u },
  { 0x01270d34u, 0x0041dec8u }, { 0x01270d1cu, 0x0041e075u }, { 0x01270d2cu, 0x0041e07cu }, { 0x01270d08u, 0x0041e083u },
  { 0x01270d30u, 0x0041e08au }, { 0x01270ea0u, 0x0041e14fu }, { 0x0127101cu, 0x0041e1e4u }, { 0x01270e0cu, 0x0041e207u },
  { 0x01270ff8u, 0x0041e20eu }, { 0x01270d70u, 0x0041e215u }, { 0x01270e20u, 0x00421cabu }, { 0x01270de4u, 0x0041e28au },
  { 0x01270e80u, 0x0041e3b0u }, { 0x01270d28u, 0x0041e404u }, { 0x01270e24u, 0x0041e456u }, { 0x01270e68u, 0x0041e45bu },
  { 0x01270e00u, 0x0041e462u }, { 0x01270e4cu, 0x0041e510u }, { 0x01270ea8u, 0x0041e517u }, { 0x01270ea4u, 0x0041e51eu },
  { 0x01271024u, 0x0041e525u }, { 0x01270e78u, 0x0041e52cu }, { 0x01270e08u, 0x0041e926u }, { 0x01270da8u, 0x0041eb2eu },
  { 0x01270d40u, 0x0041eb35u }, { 0x01270dd4u, 0x0041eb3cu }, { 0x01270e58u, 0x0041eb43u }, { 0x01270d80u, 0x0041eb4au },
  { 0x01270e1cu, 0x0041eb51u }, { 0x01270e14u, 0x0041eb69u }, { 0x01270e2cu, 0x0041eb70u }, { 0x01270d44u, 0x0041eb77u },
  { 0x01270de0u, 0x0041eb7eu }, { 0x01270e04u, 0x0041eb85u }, { 0x01270e60u, 0x0041eb8cu }, { 0x01270d14u, 0x0041ec79u },
  { 0x01270eacu, 0x0041ec82u }, { 0x01271008u, 0x0041ed00u }, { 0x01270dacu, 0x0041ed07u }, { 0x01270ffcu, 0x0041ed0eu },
  { 0x01270d54u, 0x0041ed1au }, { 0x01270e74u, 0x0041ed21u }, { 0x01270e40u, 0x0041ed26u }, { 0x01270e3cu, 0x0041ed39u },
  { 0x01270d74u, 0x0041ed3eu }, { 0x01270df4u, 0x0041ed45u }, { 0x01270d60u, 0x0041ed4cu }, { 0x01271018u, 0x0041ed53u },
  { 0x01270d88u, 0x0041ed63u }, { 0x01271014u, 0x0041ed68u }, { 0x01270ff0u, 0x0041ed72u }, { 0x01270e88u, 0x0041ed7cu },
  { 0x01270dc8u, 0x0041ed83u }, { 0x01271000u, 0x0041ed8au }, { 0x01271004u, 0x0041ed91u }, { 0x01270db8u, 0x0041f47cu },
  { 0x01270e7cu, 0x0041f485u }, { 0x01270e18u, 0x0041f48cu }, { 0x01270dd8u, 0x0041f493u }, { 0x01270d04u, 0x0041f49au },
  { 0x01270d64u, 0x0041f4a1u }, { 0x01270d10u, 0x0041f56fu }, { 0x01270e90u, 0x0041f576u }, { 0x01270d7cu, 0x0041f57du },
  { 0x01270d18u, 0x0041f6a2u }, { 0x01270d6cu, 0x0041f6a9u }, { 0x01270d3cu, 0x0041f72du }, { 0x01270df8u, 0x0041f734u },
  { 0x01270db4u, 0x0041f74au }, { 0x0127100cu, 0x0041f753u }, { 0x01270e94u, 0x0041f75au }, { 0x01270d0cu, 0x0041f761u },
  { 0x01270dbcu, 0x0041f768u }, { 0x01270d5cu, 0x0041f76fu }, { 0x01270da4u, 0x0041f7e7u }, { 0x01270ddcu, 0x0041f7f0u },
  { 0x01270e70u, 0x0041f7f7u }, { 0x01270d78u, 0x0041f800u }, { 0x01270e28u, 0x0041f809u }, { 0x01270df0u, 0x0041f810u },
  { 0x01270d50u, 0x0041f817u }, { 0x01270e6cu, 0x0041f81eu }, { 0x01270dfcu, 0x0041f825u }, { 0x01270d4cu, 0x0041fa2du },
  { 0x01270e98u, 0x0041fa36u }, { 0x01270e44u, 0x0041fa40u }, { 0x01270e5cu, 0x0041fa49u }, { 0x01270de8u, 0x0041fa50u },
  { 0x01270e34u, 0x0041fa57u }, { 0x01270d98u, 0x0041fa5eu }, { 0x01270c58u, 0x0041fa6bu }, { 0x01270dc4u, 0x0041fa74u },
  { 0x01270d84u, 0x0041fa7du }, { 0x01271010u, 0x0041fa84u }, { 0x01270ff4u, 0x0041fa8bu }, { 0x01270e64u, 0x0041fa92u },
  { 0x01270e10u, 0x0041fa99u }, { 0x01270d94u, 0x0041faa2u }, { 0x01270e9cu, 0x0041faabu }, { 0x01270d8cu, 0x0041fab4u },
  { 0x01270decu, 0x0041fab9u }, { 0x01270e54u, 0x0041d8e9u }, { 0x01270eb0u, 0x0041d94au }, { 0x01270e50u, 0x0041d954u },
  { 0x01270e38u, 0x0041ed98u }, { 0x01271020u, 0x0041f2a0u }, { 0x01270d20u, 0x0041ed2du }, { 0x01270db0u, 0x0041e4b9u },
  { 0x01270e84u, 0x0041e729u }, { 0x01270e30u, 0x0041ea2au }, { 0x01270d9cu, 0x0041f929u },
};
int32_t P151_InstallD3D(int32_t idx, int32_t no8bit, int32_t full) {
  if (idx < 0 || P42_DevCount <= idx) return 0;
  P151_DevIdx = idx;
  for (size_t i = 0; i < sizeof k_d3d_tab / sizeof k_d3d_tab[0]; i++) {
#ifdef RE_HOOK_BUILD
    *(uint32_t *)(uintptr_t)k_d3d_tab[i].slot = k_d3d_tab[i].fn;
#else
    P33_SetNativeProcAt(k_d3d_tab[i].slot, (void *)re_fn(k_d3d_tab[i].fn));
#endif
  }
#ifndef RE_HOOK_BUILD
  /* ячейки, у которых в native есть отдельные переменные */
  P85_BlendFn = (p85_blend_fn)re_fn(0x0041d9d2u);  P97_GrAlpha = (p97_gr5_fn)re_fn(0x0041dd37u);
  P97_GrDepth = (p97_gr1_fn)re_fn(0x0041ddc5u);   P117_ClipFn = (p117_clip_fn)re_fn(0x0041e08au);
  P85_StateFn = (p85_state_fn)re_fn(0x0041e14fu); G6_01270DE4 = (FnV1)re_fn(0x0041e28au);
  FnPtr01270E80 = (FnVoidI)re_fn(0x0041e3b0u);    G6_01270D28 = (FnV1)re_fn(0x0041e404u);
  P95_DrawLine = (p95_line_fn)re_fn(0x0041e462u); P85_RasterA = (p85_raster_fn)re_fn(0x0041e926u);
  P98_GrD40 = (p98_gr1_fn)re_fn(0x0041eb35u);     P97_LfbLock = (p97_lfblock_fn)re_fn(0x0041eb8cu);
  FnPtr01270EAC = (FnIntII)re_fn(0x0041ec82u);    P86_TexSrc = (p86_texsrc_fn)re_fn(0x0041f76fu);
  P85_RasterB = (p85_raster_fn)re_fn(0x0041f825u); FnPtr01270E54 = (FnVoidV)re_fn(0x0041d8e9u);
  FnPtr01270EB0 = (FnVoidV)re_fn(0x0041d94au);    FnPtr01270E50 = (FnIntI)re_fn(0x0041d954u);
  FnPtr01271020 = (FnVoidV)re_fn(0x0041f2a0u);    G6_01270D20 = (FnI1)re_fn(0x0041ed2du);
  P115_RasterC = (p85_raster_fn)re_fn(0x0041ea2au); P115_RasterD = (p85_raster_fn)re_fn(0x0041f929u);
#endif
  P151_No8bit = no8bit;
  P24_Fullscreen = full;
  return 1;
}

/* ---- 0041ed98 ---- */
int32_t P151_WinOpen(int32_t hwnd, int32_t mode, int32_t a2, int32_t a3, int32_t a4, int32_t a5, int32_t a6) {
  (void)a2; (void)a3; (void)a4; (void)a5; (void)a6;
  int32_t w = 0, h = 0;
  if (P22_DevReady != 0) { NoopFn0042243f(); P31_ReleaseDirectDraw(); }   /* «WARNING: Hardware already allocated... freeing first» */
  P24_Hwnd = (void *)(intptr_t)hwnd;
  if (hwnd == 0) P24_Hwnd = plat_window_active();
  if (mode != 0xff) plat_window_maximize(P24_Hwnd);
  P24_RestoreMode = mode != 0xff;
  P32_DevInfo = (uint8_t *)re_rd_ptr((uint8_t *)&P74_DevTab[0] + (size_t)P151_DevIdx * 0x4c + 0x48);
  uint8_t *dv = P32_DevInfo;
  P31_DDObj0 = P35_GetDirectDrawInterface(re_rd_ptr(dv));
  if (P31_DDObj0 == NULL) { P31_ReleaseDirectDraw(); { RE_TRACE_FAIL(); return 0; } }
  P24_DD = P39_QueryDD4(P31_DDObj0);
  if (P24_DD == NULL) { RE_TRACE_FAIL(); return 0; }
  P31_DDObj1 = P39_QueryD3D(P24_DD);
  if (P31_DDObj1 == NULL) { RE_TRACE_FAIL(); return 0; }
  if (P24_RestoreMode == 0) {
    if (plat_dd_set_cooperative(P24_DD, P24_Hwnd, 8) != 0) { P31_ReleaseDirectDraw(); { RE_TRACE_FAIL(); return 0; } }
    int32_t rc[4]; plat_window_client_rect(P24_Hwnd, rc);
    w = rc[2]; h = rc[3];
    if (P39_CreateFrontBack(w, h) == 0) { P31_ReleaseDirectDraw(); { RE_TRACE_FAIL(); return 0; } }
  } else {
    if (plat_dd_set_cooperative(P24_DD, P24_Hwnd, 0x11) != 0) { P31_ReleaseDirectDraw(); { RE_TRACE_FAIL(); return 0; } }
    switch (mode) {
    case 1: w = 0x140; h = 0xf0; break;
    case 3: w = 0x200; h = 0x180; break;
    case 7: w = 0x280; h = 0x1e0; break;
    case 8: w = 800; h = 600; break;
    case 0xc: w = 0x400; h = 0x300; break;
    case 0xd: w = 0x500; h = 0x400; break;
    case 0xe: w = 0x640; h = 0x4b0; break;
    default: P31_ReleaseDirectDraw(); { RE_TRACE_FAIL(); return 0; }
    }
    if (P24_SetDisplayMode(P24_DD, w, h) == 0) { P31_ReleaseDirectDraw(); { RE_TRACE_FAIL(); return 0; } }
    if (P24_CreatePrimarySurface() == 0) { P31_ReleaseDirectDraw(); { RE_TRACE_FAIL(); return 0; } }
  }
  if (P32_CreateZSurface(P24_Back) == 0) { P31_ReleaseDirectDraw(); { RE_TRACE_FAIL(); return 0; } }
  void *dev = P24_CreateDevice(P31_DDObj1, re_rd_ptr(dv + 0x14), P24_Back);
  P31_DDObj2 = dev;
#ifndef RE_HOOK_BUILD
  P33_Device = dev;
#endif
  if (dev == NULL) { P31_ReleaseDirectDraw(); { RE_TRACE_FAIL(); return 0; } }
  uint32_t c18 = rd32(dv + 0x394), cc = rd32(dv + 0x398);
  uint32_t caps = (cc & 0x10) != 0;
  if (cc & 8) caps |= 2;
  if (cc & 2) caps |= 4;
  if (c18 & 0x100) caps |= 0x20;
  uint32_t v = caps | 8;
  if ((rd32(dv + 0x38c) & 0x40000) != 0 && (rd32(dv + 0x354) & 0x40000) != 0) v = caps | 0x18;
  P23_DevCaps = v;
  P31_DDObj3 = P24_CreateViewport(P31_DDObj1);
  if (P31_DDObj3 == NULL) { P31_ReleaseDirectDraw(); { RE_TRACE_FAIL(); return 0; } }
  if (P24_AddViewport(P31_DDObj2, P31_DDObj3, w, h) == 0) { P31_ReleaseDirectDraw(); { RE_TRACE_FAIL(); return 0; } }
  if (P151_No8bit == 0) G6_00A421F0 = (int32_t)rd32(dv + 0x588);
  else { G6_00A421F0 = 1; NoopFn0042243f(); }                            /* «User requested no 8bit support» */
  if (P109_EmulInit() == 0) { P31_ReleaseDirectDraw(); { RE_TRACE_FAIL(); return 0; } }
  P23_InitRenderStates();
  P22_VpX = 0; P22_VpY = 0; P22_VpW = w; P22_VpH = h;
  P24_ModeW = w; P24_ModeH = h; P22_DevReady = 1;
#ifndef RE_HOOK_BUILD
  P31_DDVal0 = 0; P31_DDVal1 = 0; P31_DDVal2 = w; P31_DDVal3 = h; P31_DDVal4 = 1;
  G00A421A4 = w; G00A421A8 = h;
#endif
  for (int k = 0; k < 2; k++) {
    call_i3(SLOT(0x01270e8cu, "_grBufferClear@12"), 0, 0, 0xffff);
    call_i1(SLOT(0x01270d34u, "_grBufferSwap@4"), 0);
  }
  return 1;
}

/* ---- 00420038 ---- */
int32_t P151_CheckDev(uint8_t *rec) {
  uint8_t *dv = (uint8_t *)re_rd_ptr(rec + 0x48);
  NoopFn0042243f(); NoopFn0042243f();                 /* «Checking 3D device:», имя записи */
  uint8_t *d = dv + 0x320;
  if (rd32(dv + 0x328) == 0) { d = dv + 0x41c; wr32(dv + 0x518, 0); }
  else wr32(dv + 0x518, 1);
  uint32_t f1 = rd32(d + 4), f3 = rd32(d + 0xc);
  if ((f1 & 1) == 0 || (f1 & 2) == 0) { NoopFn0042243f(); return 0; }        /* Get device info failed */
  if (rd32(d + 8) != 2) { NoopFn0042243f(); return 0; }                      /* software renderer */
  if ((f3 & 1) == 0) { NoopFn0042243f(); return 0; }                          /* TLVERTEX */
  if ((f3 & 0x400) == 0) { NoopFn0042243f(); return 0; }                      /* DrawPrimitive */
  if (!(rd32(d + 0xac) < 0x101 && rd32(d + 0xb0) < 0x101 && 0xff < rd32(d + 0xb4) && 0xff < rd32(d + 0xb8))) {
    NoopFn0042243f(); return 0; }                                             /* 256x256 */
  wr32(dv + 0x51c, 0); wr32(dv + 0x520, 0x1000); wr32(dv + 0x524, 0x10);
  void *dd = plat_dd_create(re_rd_ptr(dv));
  if (dd == NULL) { NoopFn0042243f(); return 0; }
  void *dd4 = P39_QueryDD4(dd), *d3d = NULL, *prim = NULL, *dev = NULL;
  int32_t ok = 0;
  if (dd4 == NULL) { NoopFn0042243f(); goto out; }
  if (plat_dd_set_cooperative(dd4, NULL, 8) != 0) { NoopFn0042243f(); goto out; }
  memset(dv + 0x28, 0, 0x17c); memset(dv + 0x1a4, 0, 0x17c);
  wr32(dv + 0x28, 0x17c); wr32(dv + 0x1a4, 0x17c);
  if (plat_dd_get_caps(dd4, dv + 0x28, dv + 0x1a4) != 0) { NoopFn0042243f(); goto out; }
  if (((rd32(dv + 0x30) | rd32(dv + 0x1ac)) & 2) != 0) { NoopFn0042243f(); goto out; }   /* Can't load textures during rendering */
  d3d = P39_QueryD3D(dd4);
  if (d3d == NULL) { NoopFn0042243f(); goto out; }
  { uint32_t sd[31]; memset(sd, 0, sizeof sd); sd[0] = 0x7c; sd[1] = 1; sd[26] = 0x2200;
    prim = P24_CreateSurface(dd4, sd); }
  if (prim == NULL) { NoopFn0042243f(); goto out; }
  dev = P24_CreateDevice(d3d, re_rd_ptr(dv + 0x14), prim);
  if (dev == NULL) { NoopFn0042243f(); goto out; }
  if (plat_d3d_enum_tex_formats(dev, P99_DDEnumFmt, dv) != 0) { NoopFn0042243f(); goto out; }
  if (plat_d3d_enum_zbuffer(d3d, re_rd_ptr(dv + 0x14), P99_DDEnumFmt, dv) != 0) { NoopFn0042243f(); goto out; }
  if ((rd32(dv + 0x58c) & 7) == 7) { wr32(dv + 0x588, 0); NoopFn0042243f(); }      /* Card OK. */
  else { NoopFn0042243f(); wr32(dv + 0x588, 1); memcpy(dv + 0x548, dv + 0x528, 0x20); }   /* No 8bit texture support */
  ok = P106_CanDevTex(dv, dd4) != 0;
  if (ok) NoopFn0042243f();                                                   /* 3D device OK */
out:
  if (dev) plat_dd_release(dev);
  if (prim) plat_dd_release(prim);
  if (d3d) plat_dd_release(d3d);
  if (dd4) plat_dd_release(dd4);
  plat_dd_release(dd);
  return ok;
}

/* ---- 00425f7b ---- */
int32_t P151_Reopen(int32_t hwnd, int32_t mode, int32_t keep) {
  plat_window_move((void *)(intptr_t)hwnd, 0, 0, P19_ScrW, P19_ScrH, 1);
  int32_t fs = P151_FsFlag != 0;
  P62_InitRenderConsts();
  InitFpuCw_005283E2();
  call_i1(SLOT(0x01270e88u, "_grSstSelect@4"), 0);
  if (mode == 0) {
    if (P47_GlideWinOpen(hwnd, 0xff, 0, 0, fs, 2, 1) == 0) { RE_TRACE_FAIL(); return 0; }
  } else if (mode == 1) {
    int32_t res;
    switch (P19_ScrW) {
    case 0x140: res = 1; break;
    case 0x200: res = 3; break;
    case 0x280: res = 7; break;
    case 800: res = 8; break;
    case 0x400: res = 0xc; break;
    case 0x500: res = 0xd; break;
    case 0x640: res = 0xe; break;
    default: { RE_TRACE_FAIL(); return 0; }
    }
    if (P47_GlideWinOpen(hwnd, res, 0, 0, fs, 2, 1) == 0) { RE_TRACE_FAIL(); return 0; }
  }
#ifdef RE_HOOK_BUILD
  *(uint32_t *)(uintptr_t)0x011effe0u = P55_BDFA18 == 0 ? 0x0055082cu : 0x00550cfcu;
  *(uint32_t *)(uintptr_t)0x01209660u = P55_BDFA18 == 0 ? 0x0055090cu : 0x00550ddcu;
  *(uint32_t *)(uintptr_t)0x011f4060u = P55_BDFA18 == 0 ? 0x005509ecu : 0x00550ebcu;
  call_i1(SLOT(0x01270e80u, "_grDepthBufferMode@4"), 2);
#else
  P84_SelectTables(P55_BDFA18 != 0);
  call_i1((void *)FnPtr01270E80, 2);
#endif
  DrvSetMode0042655A(1);
#ifdef RE_HOOK_BUILD
  call_i1(SLOT(0x01270de4u, "_grDepthBufferFunction@4"), 3);
#else
  call_i1((void *)G6_01270DE4, 3);
#endif
  call_i1(SLOT(0x01270d70u, "_grCullMode@4"), 0);
  if (keep == 0) {
    P19_Scale = 1.0f;
#ifndef RE_HOOK_BUILD
    P11_0125f3e0 = 1.0f;
#endif
    P110_ViewSetup(0, 0, 1);
    P44_XformTag = 0x1ab6dc4;
    P47_SwapCnt = 0x9c8;
  }
  P86_CurTex = -1;
  P85_StateDirty = -1;
#ifndef RE_HOOK_BUILD
  G6_01270C34 = -1;
#endif
  call_i1(SLOT(0x01270d58u, "_grAlphaTestReferenceValue@4"), 0x82);
  call_i1(SLOT(0x01270ff8u, "_grConstantColorValue@4"), (int32_t)0xbb000000u);
  P52_GlideFogSetup();
  call_i2(SLOT(0x01270dd8u, "_grTexCombineFunction@8"), 0, 1);
  P84_TexFiltOn = -1;
  UiVar01251A70 = 1;
  return 1;
}

/* ---- 00521f10 ---- */
static void lang_fatal(void) {
  P58_LangStrings();
  const char *s = (const char *)re_ptr(P97_StrAddr[0x132]);
  size_t n = s ? strlen(s) : 0;
  if (n >= sizeof P151_ErrBuf) n = sizeof P151_ErrBuf - 1;   /* в оригинале strcpy без границы */
  if (n) memcpy(P151_ErrBuf, s, n);
  P151_ErrBuf[n] = 0;
  FreeBufs00516E2E();
  ResetDirector_00522306();
  P30_FatalError(P151_ErrBuf);
}
static void set_b87eb8(int32_t v) { P55_B87EB8 = v;
#ifndef RE_HOOK_BUILD
  P58_CfgOn = v;
#endif
}
int32_t P151_WinMain(int32_t hinst, int32_t prev, int32_t cmd, int32_t show) {
  (void)prev; (void)cmd;
  set_b87eb8(1);
  P55_Lang = 0;
#ifndef RE_HOOK_BUILD
  P58_LangNo = 0;
#endif
  memset(&P102_BDF9E0, 0, 0x2c);
  P12_00bdfa40 = 0; MenuOptBDFA44 = 0; MenuOptBDFA48 = 0; MenuOptBDFA4C = 0; MenuOptBDFA50 = 0; MenuOptBDFA54 = 0; MenuOptBDFA58 = 0;
#ifndef RE_HOOK_BUILD
  P14_00bdfa44 = 0; P62_BusyA = 0; G00BDFA44 = 0; P62_BusyB = 0; G00BDFA48 = 0; P62_BusyC = 0; G00BDFA4C = 0;
  P62_BusyD = 0; G00BDFA50 = 0; G00BDFA54 = 0; P14_00bdfa58 = 0; P62_BusyE = 0; G00BDFA58 = 0;
#endif
  G6_00B87E20 = 0;
  ClearSlots004D8C23();
  P19_ScrW = 0x280; P19_ScrH = 0x1e0;
#ifndef RE_HOOK_BUILD
  G6_01270C28 = 0x280; P11_01270c28 = u2f(0x280); G6_0125F3F0 = 0x1e0;
#endif
  P151_Bpp = 0x10;
  P124_DebugLog("Driver - Log File -");
  P124_DebugLog("Driver (c)1998-1999 Reflections Interactive");
  P124_DebugLog((const char *)&P151_Empty10);
  P124_DebugLog("Mucho respectomondo to Driver PC coder(s): ");
  P124_DebugLog("Dirty Wayne, Evil Russ, Gentleman Jim, Guru Naif, Hodgy Hax, Steve Royston, Slurpy Chris.");
  P124_DebugLog((const char *)&P151_Empty14);
  ClearHandles005223BE();
  P96_ResetDirector();
  if (P31_InitWindow((void *)(intptr_t)hinst, show) == 0) P30_FatalError("[WinMain] InitWindow failed");
  P55_PopSkip = 1;
  set_b87eb8(1);
  Q00B87E90 = 0;
  P98_Range[8] = 0;                                   /* 00b87e80 */
  P95_BDF9D0 = 4;
  P95_575F1C = 0;
#ifdef RE_HOOK_BUILD
  if (P133_LoadConfig() == 0) lang_fatal();
#else
  /* v2.00: config.dat пишет Driver Configuration (setup); в native его может не быть — настройки по умолчанию
     (P133_LoadConfig уже вызвал P95_DefaultOptions) и запись config.dat (00405bfa) вместо фатальной ошибки */
  if (P133_LoadConfig() == 0) { P124_DebugLog("[native] config.dat: settings by default"); P58_SaveConfig(); }
#endif
  P55_GlideInit(hinst, show, 2);
  if (G6_00B87E20 == 0) lang_fatal();
  plat_load_accelerators((void *)(intptr_t)G6_00BDF9C4, "ACCELERATOR");
  if (P25_TimersInit() == 0) { ResetDirector_00522306(); P30_FatalError("[WinMain] Failed to initialise timers."); }
  P151_Proc = plat_current_process();
  if (P151_PrioOn != 0 && P151_Proc != NULL) plat_set_priority(P31_PriorityHigh == 0 ? 1 : 2);   /* 0x80 / 0x100 */
  void *cur = plat_cursor_set(NULL);
  P30_ScreensaverSaved = plat_screensaver_get();
  plat_screensaver_set(0);
  if (P48_StartupSystems() == 0) {
    Ui004264A7(); P69_FreeDevices(); P27_MemLeakReport();
    plat_cursor_set(cur);
    ResetDirector_00522306();
  } else {
    P30_CrashInstall();
    if (P55_B87EB8 == 0) {
      if (G6_00B87EEC == 0) { G6_00B87E20 = 1; P136_GameLoop(0); }
      else P132_MenuLoop(0);
    } else {
      P11_00b87e7c = 1;
#ifndef RE_HOOK_BUILD
      G00B87E7C = 1;
#endif
      P126_DebugOn = 0;
      P140_Frontend(0);
    }
    Call00522323();
    P25_TimersShutdown();
    plat_set_priority(0);                              /* 0x20 */
    P30_CrashRemove();
    P48_ShutdownSystems();
    Ui004264A7(); P69_FreeDevices(); P27_MemLeakReport();
    plat_cursor_set(cur);
    ResetDirector_00522306();
    if (P100_B87E24 == 0xc9) plat_message_box((void *)(intptr_t)G6_00BDF9C0, "The lead car went out of range!", "Exit!", 0);
    plat_screensaver_set(P30_ScreensaverSaved);
  }
  return P100_B87E24;
}
