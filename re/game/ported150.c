/* v1.95: ported150 — см. ported150.h.
   0048ac1c — DirectDrawCreate(NULL) → 00b1c814; QI IDirectDraw4 → 00b1c818; SetCooperativeLevel(hwnd, 00bdf9c8 ? 0x11 : 8);
     при 00bdf9c8 ≠ 0 SetDisplayMode 640x480 с 32, 24, 16 бит (все отказали → 0); CreateSurface (IDirectDraw 1, 0x6c:
     DDSD_CAPS, PRIMARYSURFACE 0x200) → 00b1c81c; CreateClipper(IDirectDraw4) → 00b1c824; SetClipper; SetHWnd(0, hwnd).
   0048af23 — CoCreateInstance(CLSID_AMMultiMediaStream, IID_IAMMultiMediaStream) → 00b1c82c; Initialize(READ, NOGRAPHTHREAD,
     NULL); AddMediaStream(00b1c814, MSPID_PrimaryVideo, 0); AddMediaStream(NULL, MSPID_PrimaryAudio, ADDDEFAULTRENDERER) —
     отказ только в debug.log; OpenFile(путь); 00b1c828 = поток; GetMediaStream(видео) → 00b1c830; QI IDirectDrawMediaStream
     → 00b1c834; GetFormat → 00b1c7a8; GetSurfaceDesc(экран) → 00b1c530; поверхность 0x1007 (CAPS|HEIGHT|WIDTH|PIXELFORMAT)
     w×h формата с форматом пикселей экрана, OFFSCREENPLAIN → 00b1c820; CreateSample(поверхность, {0,0,w,h}) → 00b1c838.
   0048b3e8 — CoCreateInstance(CLSID_FilterGraph, IID_IGraphBuilder) → 00b1c844; QI IMediaPosition → 00b1c848;
     MultiMediaStream → 00b1c840, Initialize(READ, NOGRAPHTHREAD, граф), только звук, OpenFile; 00b1c83c = поток;
     get_Duration → 00b1c850.
   0048a940 — n ≠ −1, 00575f48 ≠ 0, 00b87ef4 = 0; "FMVDATA\RENDER%02d.MPG" (иначе с корнем CD 004d322c); оконный режим —
     ShowWindow(MAXIMIZE)+UpdateWindow; 004264a7, 00523595; 0048ac1c → OpenVideo → MmsRun: кадры 0048b34c + сообщения +
     опрос ввода до клавиши 1 (00b87efc = 1 на время показа); 0048b32b; 0048b242; не прерван и ans ≠ −1 —
     "AUDIO\MOTEL\ANS%03d.WAV" (0048abdc) до таймера 00551134 или клавиши, 0048ac0d; 0048ae12; SetForegroundWindow;
     до 10 попыток 00425f7b (не перенесена, R-строка) через 500 мс, иначе 00522369 «Can't reallocate display hardware»;
     005233be(00b87e58, 00b87e5c, 00575f50).
   0042d384 — при непустой очереди: состояние 3,1,0,1,0 (01270c34 = 4), текстура блеска машины (байт +8 записи
     011b6140) в TMU 0, смешивание 4,4,0,0 (0125f3e4 = 3); записи 0xb8 с 0115a140: тег 0 — 01270e30/01270e08,
     иначе 01270d9c/01270dfc (по 00bdfa18), вершины +4/+0x40/+0x7c. */
#include "ported150.h"
#include "ported6.h"
#include "ported12.h"
#include "ported26.h"
#include "ported28.h"
#include "ported30.h"
#include "ported31.h"
#include "ported36.h"
#include "ported38.h"
#include "ported48.h"
#include "ported50.h"
#include "ported52.h"
#include "ported55.h"
#include "ported69.h"
#include "ported85.h"
#include "ported86.h"
#include "ported108.h"
#include "ported115.h"
#include "ported124.h"
#include "ported140.h"
#include "uihandlers.h"
#include "uihandlers3.h"
#include "smallfuncs.h"
#include "noop.h"
#include "crt.h"
#include "reptr.h"
#include "unported.h"
#include "../platform/plat.h"
#include <stdio.h>
#include <string.h>

GAME_VAR_DEF(p150_path_t, P150_FmvPath, 0x00b1c59c)
GAME_VAR_DEF(p150_path_t, P150_CdRoot, 0x00b1c6a0)
GAME_VAR_DEF(p150_desc_t, P150_VidFmt, 0x00b1c7a8)
GAME_VAR_DEF(p150_desc_t, P150_PrimDesc, 0x00b1c530)
GAME_VAR_DEF(int32_t, P150_FmvOff, 0x00b87ef4)

/* GUID из .data Game.exe (00546250, 00546aa8..00546b18) */
static const uint8_t k_iid_ddms[16]    = { 0xce,0x4f,0x10,0xf4, 0x70,0x9a, 0xd0,0x11, 0x8f,0xde,0x00,0xc0,0x4f,0xd9,0x18,0x9d };  /* IID_IDirectDrawMediaStream 00546aa8 */
static const uint8_t k_mspid_audio[16] = { 0x6b,0xf5,0x5f,0xa3, 0xda,0x9f, 0xd0,0x11, 0x8f,0xdf,0x00,0xc0,0x4f,0xd9,0x18,0x9d };  /* MSPID_PrimaryAudio 00546ab8 */
static const uint8_t k_mspid_video[16] = { 0x6a,0xf5,0x5f,0xa3, 0xda,0x9f, 0xd0,0x11, 0x8f,0xdf,0x00,0xc0,0x4f,0xd9,0x18,0x9d };  /* MSPID_PrimaryVideo 00546ac8 */
static const uint8_t k_clsid_amms[16]  = { 0xe5,0x7c,0xc4,0x49, 0xa4,0x9b, 0xd0,0x11, 0x82,0x12,0x00,0xc0,0x4f,0xc3,0x2c,0x45 };  /* CLSID_AMMultiMediaStream 00546ad8 */
static const uint8_t k_iid_amms[16]    = { 0x5c,0x59,0xbe,0xbe, 0x6f,0x9a, 0xd0,0x11, 0x8f,0xde,0x00,0xc0,0x4f,0xd9,0x18,0x9d };  /* IID_IAMMultiMediaStream 00546ae8 */
static const uint8_t k_iid_mpos[16]    = { 0xb2,0x68,0xa8,0x56, 0xd4,0x0a, 0xce,0x11, 0xb0,0x3a,0x00,0x20,0xaf,0x0b,0xa7,0x70 };  /* IID_IMediaPosition 00546af8 */
static const uint8_t k_clsid_graph[16] = { 0xb3,0xeb,0x36,0xe4, 0x4f,0x52, 0xce,0x11, 0x9f,0x53,0x00,0x20,0xaf,0x0b,0xa7,0x70 };  /* CLSID_FilterGraph 00546b08 */
static const uint8_t k_iid_graph[16]   = { 0xa9,0x68,0xa8,0x56, 0xd4,0x0a, 0xce,0x11, 0xb0,0x3a,0x00,0x20,0xaf,0x0b,0xa7,0x70 };  /* IID_IGraphBuilder 00546b18 */

static uint32_t rd32le(const uint8_t *p) { uint32_t v; memcpy(&v, p, 4); return v; }
static void wr32le(uint8_t *p, uint32_t v) { memcpy(p, &v, 4); }

/* ---- 0048ac1c ---- */
int32_t P150_FmvDDInit(void *hwnd) {
  P38_Obj814 = plat_dd_create(NULL);
  if (P38_Obj814 == NULL) return 0;
  P38_DD = plat_dd_query_dd4(P38_Obj814);
  if (P38_DD == NULL) return 0;
  if (plat_dd_set_cooperative(P38_DD, hwnd, P31_WindowMode == 0 ? 8u : 0x11u) != 0) return 0;   /* NORMAL / EXCLUSIVE|FULLSCREEN */
  if (P31_WindowMode != 0 && plat_dd_set_display_mode(P38_DD, 0x280, 0x1e0, 0x20) != 0 &&
      plat_dd_set_display_mode(P38_DD, 0x280, 0x1e0, 0x18) != 0 && plat_dd_set_display_mode(P38_DD, 0x280, 0x1e0, 0x10) != 0)
    return 0;
  uint8_t d[124]; memset(d, 0, sizeof d);                         /* 0x6c байт используются (DDSURFACEDESC) */
  wr32le(d, 0x6c); wr32le(d + 4, 1); wr32le(d + 0x68, 0x200);     /* DDSD_CAPS, DDSCAPS_PRIMARYSURFACE */
  P38_Dest = plat_dd_create_surface(P38_Obj814, d);
  if (P38_Dest == NULL) return 0;
  P38_Obj824 = plat_dd_create_clipper(P38_DD);
  if (P38_Obj824 == NULL) return 0;
  if (plat_dd_set_clipper(P38_Dest, P38_Obj824) != 0) return 0;
  return plat_dd_clipper_set_hwnd(P38_Obj824, hwnd) == 0 ? 1 : 0;
}

/* ---- 0048af23 OpenVideo ---- */
int32_t P150_OpenVideo(const char *path) {
  if (plat_com_create(k_clsid_amms, k_iid_amms, &P50_Fmv82C) != 0) return 0;
  if (plat_mms_initialize(P50_Fmv82C, 0, 1, NULL) != 0) return 0;              /* STREAMTYPE_READ, AMMSF_NOGRAPHTHREAD */
  if (plat_mms_add_stream(P50_Fmv82C, P38_Obj814, k_mspid_video, 0) != 0) return 0;
  if (plat_mms_add_stream(P50_Fmv82C, NULL, k_mspid_audio, 1) != 0)           /* AMMSF_ADDDEFAULTRENDERER */
    P124_DebugLog("OpenVideo: Audio initialisation error");
  if (plat_mms_open_file(P50_Fmv82C, path, 0) != 0) return 0;
  P38_Mms = P50_Fmv82C;
  if (plat_mms_get_stream(P50_Fmv82C, k_mspid_video, &P50_Fmv830) != 0) return 0;
  if (plat_com_query_interface(P50_Fmv830, k_iid_ddms, &P50_Fmv834) != 0) return 0;
  memset(P150_VidFmt, 0, sizeof(p150_desc_t)); wr32le(P150_VidFmt, 0x6c);
  if (plat_ddms_get_format(P50_Fmv834, P150_VidFmt) != 0) return 0;
  P38_Letter = (int32_t)rd32le(P150_VidFmt + 8);                              /* 00b1c7b0 — тот же адрес (native: копия) */
  memset(P150_PrimDesc, 0, sizeof(p150_desc_t)); wr32le(P150_PrimDesc, 0x6c);
  if (plat_dd_get_surface_desc(P38_Dest, P150_PrimDesc) != 0) return 0;
  uint32_t h = rd32le(P150_VidFmt + 8), w = rd32le(P150_VidFmt + 0xc);
  uint8_t d[124]; memset(d, 0, sizeof d);
  wr32le(d, 0x6c); wr32le(d + 4, 0x1007); wr32le(d + 8, h); wr32le(d + 0xc, w);
  memcpy(d + 0x48, P150_PrimDesc + 0x48, 0x20);                              /* DDPIXELFORMAT экрана */
  wr32le(d + 0x68, 0x40);                                                     /* DDSCAPS_OFFSCREENPLAIN */
  P38_Src = plat_dd_create_surface(P38_Obj814, d);
  if (P38_Src == NULL) return 0;
  int32_t rc[4] = { 0, 0, (int32_t)w, (int32_t)h };
  return plat_ddms_create_sample(P50_Fmv834, P38_Src, rc, 0, &P38_Sample) == 0 ? 1 : 0;
}

/* ---- 0048b3e8 ---- */
int32_t P150_OpenAudio(const char *path) {
  if (plat_com_create(k_clsid_graph, k_iid_graph, &P50_FmvB) != 0) return 0;
  if (plat_com_query_interface(P50_FmvB, k_iid_mpos, &P50_FmvC) != 0) return 0;
  if (plat_com_create(k_clsid_amms, k_iid_amms, &P50_FmvA) != 0) return 0;
  if (plat_mms_initialize(P50_FmvA, 0, 1, P50_FmvB) != 0) return 0;
  if (plat_mms_add_stream(P50_FmvA, NULL, k_mspid_audio, 1) != 0) return 0;
  if (plat_mms_open_file(P50_FmvA, path, 0) != 0) return 0;
  P38_Mms2 = P50_FmvA; P50_FmvFlag = P50_FmvA;                                /* 00b1c83c (два имени) */
  return plat_media_get_duration(P50_FmvC, &P108_FmvLen) == 0 ? 1 : 0;
}

static int32_t key_pressed(void) {
  Call00522323();
  P36_PollInput();
  return IsFlagSetNotMasked_004E383A(1) != 0;
}

/* ---- 0048a940 ---- */
void P150_PlayFmv(int32_t hwnd_i, int32_t n, int32_t ans) {
  void *hwnd = (void *)(intptr_t)hwnd_i;
  char name[0x104];
  int32_t broken = 0;
  if (n == -1 || G00575F48 == 0 || P150_FmvOff != 0) return;
  snprintf(name, sizeof name, "FMVDATA\\RENDER%02d.MPG", n);
  strcpy(P150_FmvPath, name);
  void *f = g_fopen(name, "rb");
  if (f == NULL) {
    if (P26_FindCdDrive(name, P150_CdRoot) == 0) return;
    snprintf(P150_FmvPath, sizeof(p150_path_t), "%s%s", P150_CdRoot, name);
    f = g_fopen(P150_FmvPath, "rb");
    if (f == NULL) return;
  }
  g_fclose(f);
  if (P31_WindowMode != 0) { plat_window_maximize(hwnd); plat_window_update(hwnd); }
  Ui004264A7();
  P48_SndShutdown();
  if (P150_FmvDDInit(hwnd) != 0) {
    if (P150_OpenVideo(P150_FmvPath) != 0) {
      int32_t save = G6_00B87EFC;
      if (P38_MmsRun() != 0) {
        G6_00B87EFC = 1;
        for (;;) {
          if (P38_UpdateFrame() == 0) break;
          if (key_pressed()) { broken = 1; break; }
        }
      }
      G6_00B87EFC = save;
      P38_MmsStop();
    }
    P50_FmvReleaseAll();
    if (broken == 0 && ans != -1) {
      snprintf(name, sizeof name, "AUDIO\\MOTEL\\ANS%03d.WAV", ans);
      P52_FmvStart(name);
      for (;;) {
        if (P38_TimerFlag != 0 || G00551134 != 0) break;                     /* 00551134 (два имени) */
        if (key_pressed()) break;
      }
      Chain0048AC0D();
    }
  }
  P38_FmvRelease();
  plat_window_foreground(hwnd);
  Call00522323();
  int32_t tries = 10;
  while (tries > 0 && P150_Fn425F7B(G6_00BDF9C0, P31_WindowMode, 0) == 0) {
    plat_sleep_ms(500);
    Call00522323();
    tries--;
  }
  if (tries == 0) P30_FatalError("Can't reallocate display hardware");
  P140_SndInit(P12_00b87e58, P12_00b87e5c, P12_00575f50);
}

/* ---- 0042d384 ---- */
void P150_FlushTris(void) {
  if (G01159D74 == 0) return;
  if (P85_StateDirty != 4) {
    if (P85_StateFn) P85_StateFn(3, 1, 0, 1, 0);
    P85_StateDirty = 4; G6_01270C34 = 4;                                       /* 01270c34 (два имени) */
  }
  const uint8_t *ic = (const uint8_t *)re_ptr((uint32_t)P28_CarShine);
  if (ic != NULL && ic[8] != (uint32_t)P86_CurTex) {
    P86_CurTex = ic[8];
    if (P86_TexSrc) P86_TexSrc(0, rd32le(&g_01145a60[ic[8] * 0x10 + 8]), 3, rd32le(&g_01145a60[ic[8] * 0x10 + 0xc]));
  }
  if (P85_BlendCur != 3) {
    if (P85_BlendFn) P85_BlendFn(4, 4, 0, 0);
    P85_BlendCur = 3; P69_BlendOn = 3;                                         /* 0125f3e4 (два имени) */
  }
  G0115A13C = G0115A140;
  for (int32_t i = 0; i < G01159D74; i++) {
    const uint8_t *q = G0115A13C;
    const p85_rv *a = (const p85_rv *)(const void *)(q + 4), *b = (const p85_rv *)(const void *)(q + 0x40),
                 *c = (const p85_rv *)(const void *)(q + 0x7c);
    p85_raster_fn fn;
    if (P55_BDFA18 == 0) fn = rd32le(q) == 0 ? P115_RasterC : P115_RasterD;
    else                 fn = rd32le(q) == 0 ? P85_RasterA : P85_RasterB;
    if (fn) fn(a, b, c);
    G0115A13C = G0115A13C + 0xb8;
  }
}
