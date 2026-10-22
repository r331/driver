/* ported55.c — assorted Game.exe helpers (English overview; original notes follow): drawing the queued
   map-object tables, tile slot reset, save-slot name lists, a deferred-call queue, FRUSTRUM.DAT, device
   pixel-format info, whole-file loading, traffic record snapshots, joystick cycling, audio stop after a
   mission, Glide/screen setup, a language-dependent menu call and the notebook "paper" textures. */
#include <stdio.h>
#include "ported151.h"
#include "ported55.h"
#include "ported116.h"
#include "ported87.h"
#include "ported27.h"
#include "ported30.h"
#include "ported48.h"
#include "ported51.h"
#include "crt.h"
#include "aspect.h"
#ifndef RE_HOOK_BUILD
#include "../platform/plat.h"
#endif
#include <string.h>

#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P55_CntA")
#undef P55_CntA
#pragma push_macro("P55_CntA") /*gvi*/
#undef P55_CntA /*gvi*/
int32_t P55_CntA;
#pragma pop_macro("P55_CntA") /*gvi*/
#pragma pop_macro("P55_CntA")
#endif
GAME_VAR_DEF(p55_tabA_t, P55_TabA, 0x00ce0f40)
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P55_CntB")
#undef P55_CntB
#pragma push_macro("P55_CntB") /*gvi*/
#undef P55_CntB /*gvi*/
int32_t P55_CntB;
#pragma pop_macro("P55_CntB") /*gvi*/
#pragma pop_macro("P55_CntB")
#endif
GAME_VAR_DEF(p55_tabB_t, P55_TabB, 0x00d00260)
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P55_Flag38C")
#undef P55_Flag38C
#pragma push_macro("P55_Flag38C") /*gvi*/
#undef P55_Flag38C /*gvi*/
int32_t P55_Flag38C;
#pragma pop_macro("P55_Flag38C") /*gvi*/
#pragma pop_macro("P55_Flag38C")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P55_VarC0")
#undef P55_VarC0
#pragma push_macro("P55_VarC0") /*gvi*/
#undef P55_VarC0 /*gvi*/
int32_t P55_VarC0;
#pragma pop_macro("P55_VarC0") /*gvi*/
#pragma pop_macro("P55_VarC0")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P55_Var20")
#undef P55_Var20
#pragma push_macro("P55_Var20") /*gvi*/
#undef P55_Var20 /*gvi*/
int32_t P55_Var20;
#pragma pop_macro("P55_Var20") /*gvi*/
#pragma pop_macro("P55_Var20")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P55_VarD2C")
#undef P55_VarD2C
#pragma push_macro("P55_VarD2C") /*gvi*/
#undef P55_VarD2C /*gvi*/
int32_t P55_VarD2C;
#pragma pop_macro("P55_VarD2C") /*gvi*/
#pragma pop_macro("P55_VarD2C")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P55_VarD28")
#undef P55_VarD28
#pragma push_macro("P55_VarD28") /*gvi*/
#undef P55_VarD28 /*gvi*/
int32_t P55_VarD28;
#pragma pop_macro("P55_VarD28") /*gvi*/
#pragma pop_macro("P55_VarD28")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P55_VarD24")
#undef P55_VarD24
#pragma push_macro("P55_VarD24") /*gvi*/
#undef P55_VarD24 /*gvi*/
int32_t P55_VarD24;
#pragma pop_macro("P55_VarD24") /*gvi*/
#pragma pop_macro("P55_VarD24")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P55_VarD20")
#undef P55_VarD20
#pragma push_macro("P55_VarD20") /*gvi*/
#undef P55_VarD20 /*gvi*/
int32_t P55_VarD20;
#pragma pop_macro("P55_VarD20") /*gvi*/
#pragma pop_macro("P55_VarD20")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P55_VarC6")
#undef P55_VarC6
#pragma push_macro("P55_VarC6") /*gvi*/
#undef P55_VarC6 /*gvi*/
uint8_t P55_VarC6;
#pragma pop_macro("P55_VarC6") /*gvi*/
#pragma pop_macro("P55_VarC6")
#endif
GAME_VAR_DEF(const char *, P55_DefName, 0x00c55854)
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P55_FlagsC")
#undef P55_FlagsC
#pragma push_macro("P55_FlagsC") /*gvi*/
#undef P55_FlagsC /*gvi*/
p55_flags8_t P55_FlagsC;
#pragma pop_macro("P55_FlagsC") /*gvi*/
#pragma pop_macro("P55_FlagsC")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P55_PopCnt")
#undef P55_PopCnt
#pragma push_macro("P55_PopCnt") /*gvi*/
#undef P55_PopCnt /*gvi*/
int32_t P55_PopCnt;
#pragma pop_macro("P55_PopCnt") /*gvi*/
#pragma pop_macro("P55_PopCnt")
#endif
GAME_VAR_DEF(p55_pop_t, P55_PopTab, 0x00d10e80)
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P55_PopSkip")
#undef P55_PopSkip
#pragma push_macro("P55_PopSkip") /*gvi*/
#undef P55_PopSkip /*gvi*/
int32_t P55_PopSkip;
#pragma pop_macro("P55_PopSkip") /*gvi*/
#pragma pop_macro("P55_PopSkip")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P55_PopB2AC")
#undef P55_PopB2AC
#pragma push_macro("P55_PopB2AC") /*gvi*/
#undef P55_PopB2AC /*gvi*/
int32_t P55_PopB2AC;
#pragma pop_macro("P55_PopB2AC") /*gvi*/
#pragma pop_macro("P55_PopB2AC")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P55_Frustum")
#undef P55_Frustum
#pragma push_macro("P55_Frustum") /*gvi*/
#undef P55_Frustum /*gvi*/
p55_frustum_t P55_Frustum;
#pragma pop_macro("P55_Frustum") /*gvi*/
#pragma pop_macro("P55_Frustum")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P55_A4219C")
#undef P55_A4219C
#pragma push_macro("P55_A4219C") /*gvi*/
#undef P55_A4219C /*gvi*/
int32_t P55_A4219C;
#pragma pop_macro("P55_A4219C") /*gvi*/
#pragma pop_macro("P55_A4219C")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P55_A421A0")
#undef P55_A421A0
#pragma push_macro("P55_A421A0") /*gvi*/
#undef P55_A421A0 /*gvi*/
int32_t P55_A421A0;
#pragma pop_macro("P55_A421A0") /*gvi*/
#pragma pop_macro("P55_A421A0")
#endif
GAME_VAR_DEF(uint8_t *, P55_RecBase, 0x00b5a8bc)
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P55_RecCnt")
#undef P55_RecCnt
#pragma push_macro("P55_RecCnt") /*gvi*/
#undef P55_RecCnt /*gvi*/
int32_t P55_RecCnt;
#pragma pop_macro("P55_RecCnt") /*gvi*/
#pragma pop_macro("P55_RecCnt")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P55_V57B6FC")
#undef P55_V57B6FC
#pragma push_macro("P55_V57B6FC") /*gvi*/
#undef P55_V57B6FC /*gvi*/
int32_t P55_V57B6FC;
#pragma pop_macro("P55_V57B6FC") /*gvi*/
#pragma pop_macro("P55_V57B6FC")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P55_V1285428")
#undef P55_V1285428
#pragma push_macro("P55_V1285428") /*gvi*/
#undef P55_V1285428 /*gvi*/
int32_t P55_V1285428;
#pragma pop_macro("P55_V1285428") /*gvi*/
#pragma pop_macro("P55_V1285428")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P55_V1285424")
#undef P55_V1285424
#pragma push_macro("P55_V1285424") /*gvi*/
#undef P55_V1285424 /*gvi*/
int32_t P55_V1285424;
#pragma pop_macro("P55_V1285424") /*gvi*/
#pragma pop_macro("P55_V1285424")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P55_BDFA18")
#undef P55_BDFA18
#pragma push_macro("P55_BDFA18") /*gvi*/
#undef P55_BDFA18 /*gvi*/
int32_t P55_BDFA18;
#pragma pop_macro("P55_BDFA18") /*gvi*/
#pragma pop_macro("P55_BDFA18")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P55_GlideInfo")
#undef P55_GlideInfo
#pragma push_macro("P55_GlideInfo") /*gvi*/
#undef P55_GlideInfo /*gvi*/
p55_glide_t P55_GlideInfo;
#pragma pop_macro("P55_GlideInfo") /*gvi*/
#pragma pop_macro("P55_GlideInfo")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P55_B87EB8")
#undef P55_B87EB8
#pragma push_macro("P55_B87EB8") /*gvi*/
#undef P55_B87EB8 /*gvi*/
int32_t P55_B87EB8;
#pragma pop_macro("P55_B87EB8") /*gvi*/
#pragma pop_macro("P55_B87EB8")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P55_Paper0")
#undef P55_Paper0
#pragma push_macro("P55_Paper0") /*gvi*/
#undef P55_Paper0 /*gvi*/
int32_t P55_Paper0;
#pragma pop_macro("P55_Paper0") /*gvi*/
#pragma pop_macro("P55_Paper0")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P55_Paper1")
#undef P55_Paper1
#pragma push_macro("P55_Paper1") /*gvi*/
#undef P55_Paper1 /*gvi*/
int32_t P55_Paper1;
#pragma pop_macro("P55_Paper1") /*gvi*/
#pragma pop_macro("P55_Paper1")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P55_Paper2")
#undef P55_Paper2
#pragma push_macro("P55_Paper2") /*gvi*/
#undef P55_Paper2 /*gvi*/
int32_t P55_Paper2;
#pragma pop_macro("P55_Paper2") /*gvi*/
#pragma pop_macro("P55_Paper2")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P55_Lang")
#undef P55_Lang
#pragma push_macro("P55_Lang") /*gvi*/
#undef P55_Lang /*gvi*/
int32_t P55_Lang;
#pragma pop_macro("P55_Lang") /*gvi*/
#pragma pop_macro("P55_Lang")
#endif

#define P55_FILE_C "D:\\Driver\\Game\\file.c"
/* Language index (P55_Lang): from the PAPER_xx texture names below; 0 is the default (English) paper. */
enum { LANG_ENGLISH = 0, LANG_FRENCH = 1, LANG_GERMAN = 2, LANG_SPANISH = 3, LANG_ITALIAN = 4 };

/* P55_RunTableA — Game.exe 004ef309.  Draws every object queued in P55_TabA (by P89_DrawMap) with the view matrix.
   Native: count clamped to the table size, NULL entries skipped. */
void P55_RunTableA(void) {
  if (P55_CntA == 0) return;
  P44_MatPtr = (float *)P44_ViewMatT;
  /* Ограничение размером таблицы — защита от мусорного счётчика (в оригинале его нет). */
  int32_t n = P55_CntA;
  if (n < 0 || n > 1106) n = 1106;
  for (int32_t i = 0; i < n; i++) if (P55_TabA[i]) P87_DrawObjA((const uint8_t *)P55_TabA[i]);   /* пустой элемент — охранная проверка */
}

/* P55_RunTableB — Game.exe 004ef364.  Same for P55_TabB, with flag 00b1c38c = 2 during the loop.
   TODO(RE): unsure what flag 00b1c38c changes. */
void P55_RunTableB(void) {
  if (P55_CntB == 0) return;
  P44_MatPtr = (float *)P44_ViewMatT;
  int32_t n = P55_CntB;
  P55_Flag38C = 2;
  if (n < 0 || n > 2081) n = 2081;
  for (int32_t i = 0; i < n; i++) if (P55_TabB[i]) P87_DrawObjA((const uint8_t *)P55_TabB[i]);
  P55_Flag38C = 0;
}

/* P55_ResetSel — Game.exe 004ee129.  Forgets the 6 resident-tile indices (-1) and reloads the current tile
   (004ed5f8) and its neighbours (004edaa2) — used after a teleport (script command 0x8e). */
void P55_ResetSel(void) {
  P55_VarC0 = -1; P55_Var20 = -1;
  P55_VarD2C = -1; P55_VarD28 = -1; P55_VarD24 = -1; P55_VarD20 = -1;
  P55_Fn4ED5F8(P12_00cff9ac, (int32_t)P55_VarC6);
  P55_Fn4EDAA2();
}

/* Общий разбор «имя слота i или имя по умолчанию». Копия ограничена размером записи (stride-1 символ + 0). */
/* p55_names — local helper: for save slots 0..7 copies the slot name (00405e79 or 00405fdb) or the default name
   into `names` (stride bytes each, NUL padded) and sets flags[i] = slot used. */
static void p55_names(uint8_t *names, int stride, int32_t *flags, int bufsz, int use405fdb) {
  uint8_t buf[32];
  for (int32_t i = 0; i < 8; i++) {
    memset(buf, 0, sizeof buf);
    int32_t found = use405fdb ? P55_Fn405FDB(i, buf) : P55_Fn405E79(i, buf);
    uint8_t *dst = names + i * stride;
    const char *src = found == 0 ? P55_DefName : (const char *)buf;
    (void)bufsz;
    if (src == NULL) src = "";
    size_t n = strnlen(src, (size_t)(stride - 1));
    memcpy(dst, src, n);
    memset(dst + n, 0, (size_t)stride - n);
    flags[i] = found != 0;
  }
}

/* P55_NamesA / P55_NamesB / P55_NamesC / P55_NamesD — Game.exe 0041219e / 004125b9 / 0041afca / 00510784.
   Fill four menus' name lists (16- or 17-byte entries) from the two slot-name sources.
   TODO(RE): unsure which save types 00405e79 / 00405fdb read (replays vs saved games?). */
void P55_NamesA(void) { p55_names((uint8_t *)P12_005fe7a8 + 0x20, 0x10, P12_005fe7a8, 20, 0); }
void P55_NamesB(void) { p55_names((uint8_t *)P12_005fe884 + 0x20, 0x10, P12_005fe884, 32, 1); }
void P55_NamesC(void) { p55_names((uint8_t *)P12_005fee60, 0x11, P12_005fee40, 20, 0); }
void P55_NamesD(void) { p55_names((uint8_t *)P52_NameTab, 0x11, P55_FlagsC, 16, 1); }

/* P55_PopDeferred — Game.exe 004d9237.  Runs the queued deferred calls (LIFO): restores colour/position
   (00b2c3a8, 00d117a4/a8) and calls 004d92d2(id) unless skipping; then clears the position. */
void P55_PopDeferred(void) {
  while (P55_PopCnt != 0) {
    P55_PopCnt = P55_PopCnt - 1;
    uint32_t i = (uint32_t)P55_PopCnt;
    if (i >= 146) { P55_PopCnt = 0; break; }   /* защита от мусорного счётчика */
    WH00B2C3A8 = P55_PopTab[i].w;
    G6_00D117A4 = (int32_t)P55_PopTab[i].x;
    G6_00D117A8 = (int32_t)P55_PopTab[i].y;
    if (P55_PopSkip == 0) P55_Fn4D92D2(P55_PopTab[i].id);
  }
  G6_00D117A8 = 0;
  G6_00D117A4 = 0;
  P55_PopB2AC = 0;
}

/* P55_LoadFrustum — Game.exe 004eb3c0.  Loads FRUSTRUM.DAT: a count word, then 256 heading sectors of 0x80 bytes
   (visible 31x31 cell rows per sector, see aspect.c).  Returns 0, or -1 if the file is missing. */
int32_t P55_LoadFrustum(void) {
  void *f = g_fopen("FRUSTRUM.DAT", "rb");
  if (f == NULL) return -1;
  int32_t n;
  P27_ReadChunked(&n, 4, 1, f);
  for (n = 0; n < 0x100; n++) P27_ReadChunked(P55_Frustum + n * 0x80, 1, 0x80, f);
  g_fclose(f);
  return 0;
}

/* P55_FillDevInfo — Game.exe 0041d819.  Fills the 11-word pixel-format description of the D3D device
   (channel shifts, masks, caps, a pointer to 00601bc0). */
void P55_FillDevInfo(uint32_t *out) {
  out[0] = (uint32_t)P24_RShiftR; out[1] = (uint32_t)P24_RShiftL;
  out[2] = (uint32_t)P24_GShiftR; out[3] = (uint32_t)P24_GShiftL;
  out[4] = (uint32_t)P24_BShiftR; out[5] = (uint32_t)P24_BShiftL;
  out[6] = (uint32_t)P55_A4219C;  out[7] = (uint32_t)P55_A421A0;
  out[8] = (uint32_t)G6_00A421F0;
  out[10] = 0x00601bc0u;
  out[9] = P23_DevCaps;
}

/* P55_GlideDevInfo — Game.exe 00424974.  Same for Glide (fixed RGB555) or, on the D3D path, P55_FillDevInfo. */
void P55_GlideDevInfo(uint32_t *out) {
  if (D_00b1c0d4 == 0) return;
  if (D_00b1c0d8 == 0) {
    out[0] = 3; out[1] = 10; out[2] = 3; out[3] = 5; out[4] = 3; out[5] = 0;   /* 8-bit r,g,b -> RGB555: >>3 then <<10 / <<5 / <<0 */
    out[8] = 0; out[9] = 0xffffffffu; out[10] = 0;
  } else if (D_00b1c0d8 == 1) {
    P55_FillDevInfo(out);
  }
}

/* P55_LoadFile / P55_LoadFileSize — Game.exe 004d30f8 / 004d318e.  Read a whole file into a DebugMalloc buffer
   (and return its size).  NULL if missing, empty or unreadable. */
void *P55_LoadFile(const char *name) {
  void *f = g_fopen(name, "rb");
  if (f == NULL) return NULL;
  int32_t size = P51_FileSize(f);
  if (size != 0) {
    void *buf = DebugMalloc(size, P55_FILE_C, 0x86);
    if (buf != NULL && (P27_ReadChunked(buf, size, 1, f) & 0xff) != 0) { g_fclose(f); return buf; }
  }
  g_fclose(f);
  return NULL;
}

void *P55_LoadFileSize(const char *name, int32_t *size) {
  void *f = g_fopen(name, "rb");
  if (f == NULL) return NULL;
  *size = P51_FileSize(f);
  if (*size != 0) {
    void *buf = DebugMalloc(*size, P55_FILE_C, 0xb1);
    if (buf != NULL && (P27_ReadChunked(buf, *size, 1, f) & 0xff) != 0) { g_fclose(f); return buf; }
  }
  g_fclose(f);
  return NULL;
}

/* P55_SaveRec — Game.exe 00519873.  Appends a 0x1a4-byte snapshot {frame, idx, traffic record idx (0x54),
   car record idx (0x148)} to the buffer at 00b5a8bc (max 0x800).  TODO(RE): unsure who reads these (debug?). */
void P55_SaveRec(int32_t idx) {
  if (P55_RecBase == NULL || P55_RecCnt >= 0x800) return;
  uint8_t *rec = P55_RecBase + (size_t)P55_RecCnt * 0x1a4;
  uint32_t frame = (uint32_t)G8_00D118C0, idx_u = (uint32_t)idx;
  memcpy(rec, &frame, 4);
  memcpy(rec + 4, &idx_u, 4);
  memcpy(rec + 8, (uint8_t *)TrafficRecs + (size_t)idx * 0x54, 0x54);
  memcpy(rec + 0x5c, G0113A6C4 + (size_t)idx * 0x148, 0x148);
  P55_RecCnt = P55_RecCnt + 1;
}

/* P55_NextPad — Game.exe 004073ab.  Selects the next joystick (with its key config) or, past the last one,
   the default keyboard layout; re-applies controls (004072be).  Returns 0. */
int32_t P55_NextPad(void) {
  int32_t pad = Q0057B72C;
  Q0057B72C = pad + 1;
  if (P36_SelectJoystick(pad) == 0) {
    Q0057B72C = 0;
    memcpy(P36_KeyCfg, (uint8_t *)P54_KeySrc + 24, 20);
  } else {
    memcpy(P36_KeyCfg, (uint8_t *)P54_KeySrc, 20);
    if (Q00B87EF0 != 0) Q00B87EF0 = Q00B31E2C;
  }
  Call004072BE();
  return 0;
}

/* P55_StopAudio — Game.exe 0050f289.  Unpauses and, outside the replay director, stops the level's sounds
   and CD music (different calls depending on whether the level loop is still running). */
void P55_StopAudio(void) {
  G6_00B5A778 = 0;
  G6_00B87EFC = 0;
  if (P29_Mode != 0) return;
  G00B5A730 = 0;
  if (G6_00B87E20 == 0) {
    Call005237B1();
    if (Q00B87E90 != 0) { Call00524873(); Call00524763(); }
  } else {
    Call005243EB();
    if (Q00B87E90 != 0) P55_Fn5248CD();
  }
  if (P55_B87EB8 != 0 && GameMode == 0) P47_Fn405BFA();
}

#ifndef RE_HOOK_BUILD
#include <stdlib.h>
#define TRACE_GI(...) do { if (getenv("RE_TRACE")) { fprintf(stderr, "[trace] GlideInit: " __VA_ARGS__); fputc('\n', stderr); } } while (0)
#else
#define TRACE_GI(...) ((void)0)
#endif
/* P55_GlideInit — Game.exe 005226b5.  Selects the render device, checks Glide, sets fullscreen/window
   (mode 1 = fullscreen), reopens the device (success -> 00b87e20 = 1) and refreshes the pixel-format info.
   The first two arguments are unused.  Native: RE_TRACE prints the steps. */
void P55_GlideInit(int32_t a, int32_t b, int32_t mode) {
  (void)a; (void)b;
  P55_Fn424530(P55_V57B6FC, P55_V1285428, P55_V1285424);
  TRACE_GI("devsel idx=%d devcount=%d ok=%d kind_d3d=%d", (int)P55_V57B6FC, (int)P42_DevCount, (int)G00B1C0D8, (int)G00B1C0D8);
  if (P48_GlideCheck() == 0) { TRACE_GI("GlideCheck=0"); return; }
  P55_BDFA18 = P55_Fn4245E2() == 0;
  P31_WindowMode = mode != 1;
  if (P151_Reopen(G6_00BDF9C0, P31_WindowMode, 0) != 0) G6_00B87E20 = 1;
  TRACE_GI("Reopen -> b87e20=%d", (int)G6_00B87E20);
  P55_GlideDevInfo(P55_GlideInfo);
}

/* P55_SetScreen — Game.exe 0040c533.  Switches the game resolution to w x h by reopening the device; on failure
   restores the previous one (and dies with "Can't allocate 3D hardware" if that fails too).  Returns 1.
   Native (v2.26): with game_res = native the game always runs at 640x480 (see re_game_screen). */
int32_t P55_SetScreen(int32_t w, int32_t h) {
#ifndef RE_HOOK_BUILD
  {   /* v2.26: native — кадр игры всегда 640×480 (вывод в разрешении окна, Hor+); game_res = original — режим как есть */
    int32_t w0 = w, h0 = h;
    if (re_game_screen(plat_game_res_native(), &w, &h)) {
      static int n; if (n++ < 4) plat_log("[gfx] режим игры %dx%d → кадр игры 640x480 (вывод — в разрешении окна; game_res = original в driver.cfg — как в оригинале)\n", (int)w0, (int)h0);
      if (P19_ScrW == w && P19_ScrH == h) return 1;   /* уже 640×480 — переоткрывать устройство незачем (как при совпадении у вызывающих) */
    }
  }
#endif
  int32_t oldW = P19_ScrW, oldH = P19_ScrH;
  P55_Fn4264A7();
  P19_ScrW = w; P19_ScrH = h;
  if (P151_Reopen(G6_00BDF9C0, P31_WindowMode, 0) == 0) {
    P19_ScrH = oldH; P19_ScrW = oldW;
    if (P151_Reopen(G6_00BDF9C0, P31_WindowMode, 0) == 0)
      P30_FatalError("FATAL: Can't allocate 3D hardware");
  }
  return 1;
}

/* P55_MenuLangCall — Game.exe 00409d66.  Maps the menu item 005d578c (0x1c..0x20) to a language 0..4 and calls
   00417651 (P116_Sliders5) with five float settings and that language.  TODO(RE): unsure what this screen is. */
void P55_MenuLangCall(void) {
  int32_t lang = -1;
  if (MenuI005D578C == 0x1c) lang = 0;
  if (MenuI005D578C == 0x1d) lang = 1;
  if (MenuI005D578C == 0x1e) lang = 2;
  if (MenuI005D578C == 0x1f) lang = 3;
  if (MenuI005D578C == 0x20) lang = 4;
  P116_Sliders5(p116_f(P55_A680), p116_f(P55_A688), p116_f(P55_A68C), p116_f(P55_A684), p116_f(P55_A690), lang);
}

/* P55_LoadPaper — Game.exe 004e6175.  Looks up the ELPAPEL / LINE / CROSS textures and, for non-English
   languages, replaces the paper with PAPER_FR / GE / SP / IT; clears 9 words at 00d04a50. */
void P55_LoadPaper(void) {
  P55_Paper0 = Call004EC91E("ELPAPEL");
  P55_Paper1 = Call004EC91E("LINE");
  P55_Paper2 = Call004EC91E("CROSS");
  switch (P55_Lang) {
  case LANG_FRENCH: P55_Fn4E7450(P55_Paper0, "PAPER_FR"); break;
  case LANG_GERMAN: P55_Fn4E7450(P55_Paper0, "PAPER_GE"); break;
  case LANG_SPANISH: P55_Fn4E7450(P55_Paper0, "PAPER_SP"); break;
  case LANG_ITALIAN: P55_Fn4E7450(P55_Paper0, "PAPER_IT"); break;
  }
  memset(G6_00D04A50, 0, 9 * 4);
}
