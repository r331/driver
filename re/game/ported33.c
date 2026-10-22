/* Per-texture-slot vertex batches (flushed as D3D triangle lists) and the glide2x.dll
   function table (Game.exe Render.c). */
/* Сброс буферов вершин по слотам и таблица функций Glide — восстановлено из Game.exe (Render.c). */
#include "ported33.h"
#include "ported32.h"
#include "ported6.h"
#include "ported31.h"
#include "unported.h"
#include <string.h>
#ifndef RE_HOOK_BUILD
#include "../platform/native/diagnostics.h"
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P33_Count")
#undef P33_Count
#pragma push_macro("P33_Count") /*gvi*/
#undef P33_Count /*gvi*/
P33_CountArr P33_Count;
#pragma pop_macro("P33_Count") /*gvi*/
#pragma pop_macro("P33_Count")
#endif
GAME_VAR_DEF(P33_VBufArr, P33_VBuf, 0x00622048)
#ifdef RE_HOOK_BUILD   /* v2.35: native — P31_DDObj2 (ported33.h) */
GAME_VAR_DEF(void *, P33_Device, 0x00a42160)
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P33_GlideOk")
#undef P33_GlideOk
#pragma push_macro("P33_GlideOk") /*gvi*/
#undef P33_GlideOk /*gvi*/
int32_t P33_GlideOk;
#pragma pop_macro("P33_GlideOk") /*gvi*/
#pragma pop_macro("P33_GlideOk")
#endif

/* A texture slot holds 4096 vertices. Flush before a complete primitive would
   cross that boundary; dropping later vertices makes nearby road tiles vanish. */
#define VB_SLOTS        0x21   /* vertex batches: 32 texture slots + 1 untextured */
#define VB_SLOT_UNTEX   0x20   /* batch drawn with texturing disabled */
#define D3DPT_TRIANGLELIST 4
#define D3DTOP_DISABLE     1

/* P33_EnsureRoom — Native: make room for `vertices` more vertices in batch `slot`, flushing all batches first
   when the slot would overflow (a primitive must not straddle a flush).  Returns 0 for an
   invalid slot/count or a corrupt counter, else 1.  Restores the bound texture after a flush. */
int P33_EnsureRoom(int32_t slot, int32_t vertices) {
  const int32_t capacity = (int32_t)(sizeof P33_VBuf[0] / sizeof(plat_vertex));
  if (slot < 0 || slot >= 33 || vertices <= 0 || vertices > capacity) return 0;
  int32_t n = P33_Count[slot];
  if (n < 0 || n > capacity || n % 3 != 0) return 0;
  if (n > capacity - vertices) {
#ifndef RE_HOOK_BUILD
    /* The SDL accessor returns the actual binding, which may differ from the
       palette cache. FlushBatches restores that cache but leaves its last texture bound. */
    void *texture = plat_stub_last_texture(NULL);
    re_diag_count(RE_DIAG_BATCH_ROLLOVER);
    re_diag_log("Vertex batch rollover: slot=%d queued=%d incoming=%d capacity=%d\n", slot, n, vertices, capacity);
#endif
    P33_FlushBatches();
#ifndef RE_HOOK_BUILD
    plat_set_texture(0, texture);
#endif
  }
  return 1;
}

/* P33_FlushBatches — Game.exe 00422ae7, cdecl.  Draw every non-empty vertex batch as a triangle list and reset its counter.  Batch 0x20 is
   drawn untextured; other slots bind their texture or palette.  The current texture handle,
   palette and slot and stage-0 COLOROP are restored afterwards. */
void P33_FlushBatches(void) {
  void *keep_handle = P32_CurHandle;
  int32_t keep_pal = G6_0054EF2C;
  int32_t keep_slot = P32_CurSlot;
  uint32_t colorop = plat_get_tex_stage(0, 1);
  for (int slot = 0; slot < VB_SLOTS; slot++) {
    if (P33_Count[slot] == 0) continue;
    if (slot == VB_SLOT_UNTEX) {            /* без текстуры: COLOROP = 1 (DISABLE), текстуры нет */
      plat_set_tex_stage(0, 1, D3DTOP_DISABLE);
      plat_set_texture(0, NULL);
    } else if (P32_Slots[slot].has_list == 0) {
      plat_set_texture(0, P32_Slots[slot].tex);
      P32_CurSlot = -1;
    } else {
      P32_SelectSlotPalette(slot);
    }
    plat_draw_prim(D3DPT_TRIANGLELIST, (const plat_vertex *)P33_VBuf[slot], P33_Count[slot]);   /* D3DPT_TRIANGLELIST, FVF 0x1c4 */
    P33_Count[slot] = 0;
  }
  P32_CurSlot = keep_slot;
  G6_0054EF2C = keep_pal;
  P32_CurHandle = keep_handle;
  plat_set_tex_stage(0, 1, colorop);
}

/* сгенерировано tools/gen_glide.py из Game.exe: имя экспорта glide2x.dll → адрес указателя */
static const struct { const char *name; uint32_t addr; } P33_GlideTab[] = {
  { "_grAADrawLine@8", 0x01270d90 },
  { "_grAADrawPoint@4", 0x01270dc0 },
  { "_grAADrawPolygon@12", 0x01270d48 },
  { "_grAADrawPolygonVertexList@8", 0x01270da0 },
  { "_grAADrawTriangle@24", 0x01270d38 },
  { "_grAlphaBlendFunction@16", 0x01270dd0 },
  { "_grAlphaCombine@20", 0x01270dcc },
  { "_grAlphaControlsITRGBLighting@4", 0x01270e48 },
  { "_grAlphaTestFunction@4", 0x01270d68 },
  { "_grAlphaTestReferenceValue@4", 0x01270d58 },
  { "_grBufferClear@12", 0x01270e8c },
  { "_grBufferNumPending@0", 0x01270d24 },
  { "_grBufferSwap@4", 0x01270d34 },
  { "_grCheckForRoom@4", 0x01270d1c },
  { "_grChromakeyMode@4", 0x01270d2c },
  { "_grChromakeyValue@4", 0x01270d08 },
  { "_grClipWindow@16", 0x01270d30 },
  { "_grColorCombine@20", 0x01270ea0 },
  { "_grColorMask@8", 0x0127101c },
  { "_grConstantColorValue4@16", 0x01270e0c },
  { "_grConstantColorValue@4", 0x01270ff8 },
  { "_grCullMode@4", 0x01270d70 },
  { "_grDepthBiasLevel@4", 0x01270e20 },
  { "_grDepthBufferFunction@4", 0x01270de4 },
  { "_grDepthBufferMode@4", 0x01270e80 },
  { "_grDepthMask@4", 0x01270d28 },
  { "_grDisableAllEffects@0", 0x01270e24 },
  { "_grDitherMode@4", 0x01270e68 },
  { "_grDrawLine@8", 0x01270e00 },
  { "_grDrawPlanarPolygon@12", 0x01270e4c },
  { "_grDrawPlanarPolygonVertexList@8", 0x01270ea8 },
  { "_grDrawPoint@4", 0x01270ea4 },
  { "_grDrawPolygon@12", 0x01271024 },
  { "_grDrawPolygonVertexList@8", 0x01270e78 },
  { "_grDrawTriangle@12", 0x01270e08 },
  { "_grFogColorValue@4", 0x01270da8 },
  { "_grFogMode@4", 0x01270d40 },
  { "_grFogTable@4", 0x01270dd4 },
  { "_grGammaCorrectionValue@4", 0x01270e58 },
  { "_grGlideGetState@4", 0x01270d80 },
  { "_grGlideGetVersion@4", 0x01270e1c },
  { "_grGlideSetState@4", 0x01270e14 },
  { "_grGlideShamelessPlug@4", 0x01270e2c },
  { "_grHints@8", 0x01270d44 },
  { "_grLfbConstantAlpha@4", 0x01270de0 },
  { "_grLfbConstantDepth@4", 0x01270e04 },
  { "_grLfbLock@24", 0x01270e60 },
  { "_grLfbReadRegion@28", 0x01270d14 },
  { "_grLfbUnlock@8", 0x01270eac },
  { "_grLfbWriteColorFormat@4", 0x01271008 },
  { "_grLfbWriteColorSwizzle@8", 0x01270dac },
  { "_grLfbWriteRegion@32", 0x01270ffc },
  { "_grRenderBuffer@4", 0x01270d54 },
  { "_grResetTriStats@0", 0x01270e74 },
  { "_grSplash@20", 0x01270e40 },
  { "_grSstIdle@0", 0x01270e3c },
  { "_grSstIsBusy@0", 0x01270d74 },
  { "_grSstOrigin@4", 0x01270df4 },
  { "_grSstPerfStats@4", 0x01270d60 },
  { "_grSstQueryBoards@4", 0x01271018 },
  { "_grSstResetPerfStats@0", 0x01270d88 },
  { "_grSstScreenHeight@0", 0x01271014 },
  { "_grSstScreenWidth@0", 0x01270ff0 },
  { "_grSstSelect@4", 0x01270e88 },
  { "_grSstStatus@0", 0x01270dc8 },
  { "_grSstVRetraceOn@0", 0x01271000 },
  { "_grSstVideoLine@0", 0x01271004 },
  { "_grTexCalcMemRequired@16", 0x01270db8 },
  { "_grTexClampMode@12", 0x01270e7c },
  { "_grTexCombine@28", 0x01270e18 },
  { "_grTexCombineFunction@8", 0x01270dd8 },
  { "_grTexDetailControl@16", 0x01270d04 },
  { "_grTexDownloadMipMap@16", 0x01270d64 },
  { "_grTexDownloadMipMapLevel@32", 0x01270d10 },
  { "_grTexDownloadMipMapLevelPartial@40", 0x01270e90 },
  { "_grTexDownloadTable@12", 0x01270d7c },
  { "_grTexDownloadTablePartial@20", 0x01270d18 },
  { "_grTexFilterMode@12", 0x01270d6c },
  { "_grTexLodBiasValue@8", 0x01270d3c },
  { "_grTexMaxAddress@4", 0x01270df8 },
  { "_grTexMinAddress@4", 0x01270db4 },
  { "_grTexMipMapMode@12", 0x0127100c },
  { "_grTexMultibase@8", 0x01270e94 },
  { "_grTexMultibaseAddress@20", 0x01270d0c },
  { "_grTexNCCTable@8", 0x01270dbc },
  { "_grTexSource@16", 0x01270d5c },
  { "_grTexTextureMemRequired@8", 0x01270da4 },
  { "_grTriStats@8", 0x01270ddc },
  { "_gu3dfGetInfo@8", 0x01270e70 },
  { "_gu3dfLoad@8", 0x01270d78 },
  { "_guAADrawTriangleWithClip@12", 0x01270e28 },
  { "_guAlphaSource@4", 0x01270df0 },
  { "_guColorCombineFunction@4", 0x01270d50 },
  { "_guDrawPolygonVertexListWithClip@8", 0x01270e6c },
  { "_guDrawTriangleWithClip@12", 0x01270dfc },
  { "_guEncodeRLE16@16", 0x01270d4c },
  { "_guEndianSwapBytes@4", 0x01270e98 },
  { "_guEndianSwapWords@4", 0x01270e44 },
  { "_guFogGenerateExp2@8", 0x01270e5c },
  { "_guFogGenerateExp@8", 0x01270de8 },
  { "_guFogGenerateLinear@12", 0x01270e34 },
  { "_guFogTableIndexToW@4", 0x01270d98 },
  { "_guTexAllocateMemory@60", 0x01270c58 },
  { "_guTexChangeAttributes@48", 0x01270dc4 },
  { "_guTexCombineFunction@8", 0x01270d84 },
  { "_guTexCreateColorMipMap@0", 0x01271010 },
  { "_guTexDownloadMipMap@12", 0x01270ff4 },
  { "_guTexDownloadMipMapLevel@12", 0x01270e64 },
  { "_guTexGetCurrentMipMap@4", 0x01270e10 },
  { "_guTexGetMipMapInfo@4", 0x01270d94 },
  { "_guTexMemQueryAvail@4", 0x01270e9c },
  { "_guTexMemReset@0", 0x01270d8c },
  { "_guTexSource@4", 0x01270dec },
  { "_grGlideInit@0", 0x01270e54 },
  { "_grGlideShutdown@0", 0x01270eb0 },
  { "_grSstQueryHardware@4", 0x01270e50 },
  { "_grSstWinOpen@28", 0x01270e38 },
  { "_grSstWinClose@0", 0x01271020 },
  { "_grSstControl@4", 0x01270d20 },
};
static const uint32_t P33_GlideZero[] __attribute__((unused)) = { 0x01270db0, 0x01270e84, 0x01270e30, 0x01270d9c };

#ifndef RE_HOOK_BUILD
static void *g_glide_native[sizeof P33_GlideTab / sizeof P33_GlideTab[0]];
#endif
/* P33_GlideCount — Number of glide2x.dll functions in the table (119). */
int P33_GlideCount(void) { return (int)(sizeof P33_GlideTab / sizeof P33_GlideTab[0]); }
/* P33_GlideName — Export name of Glide function i, or NULL. */
const char *P33_GlideName(int i) { return (i >= 0 && i < P33_GlideCount()) ? P33_GlideTab[i].name : NULL; }
/* P33_GlideProc — Pointer of Glide function i (hook: read from the Game.exe cell; native: the local table). */
void *P33_GlideProc(int i) {
  if (i < 0 || i >= P33_GlideCount()) return NULL;
#ifdef RE_HOOK_BUILD
  return *(void **)(uintptr_t)P33_GlideTab[i].addr;
#else
  return g_glide_native[i];
#endif
}

#ifndef RE_HOOK_BUILD
/* P33_SetNativeProc — Native: install a native implementation for the Glide export `name`.  Returns 0 if unknown. */
int P33_SetNativeProc(const char *name, void *proc) {
  for (int i = 0; i < P33_GlideCount(); i++)
    if (strcmp(P33_GlideTab[i].name, name) == 0) { g_glide_native[i] = proc; return 1; }
  return 0;
}
/* v1.96: то же по адресу ячейки Game.exe (0041cede пишет таблицу по адресам); 0 — ячейки нет в таблице имён */
/* P33_SetNativeProcAt — Native: as P33_SetNativeProc, keyed by the Game.exe cell address. */
int P33_SetNativeProcAt(uint32_t addr, void *proc) {
  for (int i = 0; i < P33_GlideCount(); i++)
    if (P33_GlideTab[i].addr == addr) { g_glide_native[i] = proc; return 1; }
  return 0;
}
#endif

/* P33_LoadGlideProcs — Game.exe 00424c40, cdecl.  Resolve all glide2x.dll exports from P31_GlideModule into the function table (hook: also
   zeroes the four unused cells).  Returns 0 if Glide is not available (P33_GlideOk == 0). */
int32_t P33_LoadGlideProcs(void) {
  if (P33_GlideOk == 0) return 0;
  void *mod = (void *)(intptr_t)P31_GlideModule;
  for (int i = 0; i < P33_GlideCount(); i++) {
    void *p = plat_dll_proc(mod, P33_GlideTab[i].name);
#ifdef RE_HOOK_BUILD
    *(void **)(uintptr_t)P33_GlideTab[i].addr = p;
#else
    g_glide_native[i] = p;
#endif
  }
#ifdef RE_HOOK_BUILD
  for (unsigned i = 0; i < sizeof P33_GlideZero / sizeof P33_GlideZero[0]; i++) *(uint32_t *)(uintptr_t)P33_GlideZero[i] = 0;
#endif
  return 1;
}
