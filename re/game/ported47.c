/* ported47.c — small unrelated Game.exe functions (English overview; original notes follow): a line reader,
   two wrappers, menu/title dispatch, flyby loading, debug text, replay temp files and three Glide calls
   resolved by name from the loaded Glide DLL (glide_proc).  cdecl unless noted. */
/* Мелкие функции игры — восстановлено из Game.exe (cdecl). */
#include "ported138.h"
#include "ported132.h"
#include "ported47.h"
#include "ported33.h"
#include "crt.h"
#include <stdio.h>
#include <string.h>
#include "redbg.h"
#ifdef RE_HOOK_BUILD
#  define P47_STD __attribute__((stdcall))
#else
#  define P47_STD
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P47_Slots")
#undef P47_Slots
#pragma push_macro("P47_Slots") /*gvi*/
#undef P47_Slots /*gvi*/
P47_SlotArr P47_Slots;
#pragma pop_macro("P47_Slots") /*gvi*/
#pragma pop_macro("P47_Slots")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P47_Limit")
#undef P47_Limit
#pragma push_macro("P47_Limit") /*gvi*/
#undef P47_Limit /*gvi*/
int32_t P47_Limit;
#pragma pop_macro("P47_Limit") /*gvi*/
#pragma pop_macro("P47_Limit")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P47_Flag")
#undef P47_Flag
#pragma push_macro("P47_Flag") /*gvi*/
#undef P47_Flag /*gvi*/
int32_t P47_Flag;
#pragma pop_macro("P47_Flag") /*gvi*/
#pragma pop_macro("P47_Flag")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P47_CamB")
#undef P47_CamB
#pragma push_macro("P47_CamB") /*gvi*/
#undef P47_CamB /*gvi*/
int32_t P47_CamB;
#pragma pop_macro("P47_CamB") /*gvi*/
#pragma pop_macro("P47_CamB")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P47_WinArg5")
#undef P47_WinArg5
#pragma push_macro("P47_WinArg5") /*gvi*/
#undef P47_WinArg5 /*gvi*/
int32_t P47_WinArg5;
#pragma pop_macro("P47_WinArg5") /*gvi*/
#pragma pop_macro("P47_WinArg5")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P47_SwapCnt")
#undef P47_SwapCnt
#pragma push_macro("P47_SwapCnt") /*gvi*/
#undef P47_SwapCnt /*gvi*/
int32_t P47_SwapCnt;
#pragma pop_macro("P47_SwapCnt") /*gvi*/
#pragma pop_macro("P47_SwapCnt")
#endif

/* glide_proc — local helper: address of the Glide export `name` (e.g. "_grBufferSwap@4"), or NULL. */
static void *glide_proc(const char *name) {
  for (int i = 0; i < P33_GlideCount(); i++)
    if (strcmp(P33_GlideName(i), name) == 0) return P33_GlideProc(i);
  return NULL;
}

/* P47_ReadLine — Game.exe 0041c7ad.  fgets(buf, 128, file).  Returns 0 if a line was read, -1 at end of file. */
int32_t P47_ReadLine(void *file, char *buf) {
  return g_fgets(buf, 0x80, file) == NULL ? -1 : 0;
}
/* P47_Call51B111 — Game.exe 004c6091.  Calls 0051b111(a, b), ignores its result, returns 1. */
int32_t P47_Call51B111(int32_t a, int32_t b) {
  P47_Fn51B111(a, b);
  return 1;
}
/* P47_NoFlags — Game.exe 00495886.  1 if none of bits 0x3c000000 are set in 0051b566(a, b), else 0.
   TODO(RE): unsure what those flag bits mean. */
int32_t P47_NoFlags(int32_t a, int32_t b) {
  return (P47_Fn51B566(a, b) & 0x3c000000u) == 0;
}
/* P47_ResetPick — Game.exe 004f5951.  Clears P47_Flag; if the mission result 00c810e8 is 1..4 and its slot
   in P47_Slots holds a value, clicks menu item value + 0xf000 (004f8acc) and frees the slot; caps
   P47_Limit at 50 and sets 00d118a8 (controls taken away).  TODO(RE): unsure what the slots hold. */
void P47_ResetPick(void) {
  P47_Flag = 0;
  int32_t result = P14_00c810e8;
  if (result >= 1 && result <= 4 && P47_Slots[result - 1] != -1) {
    MenuClick004F8ACC(P47_Slots[result - 1] + 0xf000);
    P47_Slots[result - 1] = -1;
  }
  if (P47_Limit > 0x32) P47_Limit = 0x32;
  G2_00D118A8 = 1;
}
/* P47_TitleDispatch — Game.exe 0040a73d.  Runs the front-end screen for menu mode 01271060: 1..5 -> 00413d70,
   6 -> 0040a3a0, 7 -> 00413d70 with option 00bdfa50 = 1 and count 00575ee4 = 0x20 temporarily (restored
   afterwards).  If the screen returns 0, plays the wait animation with item lists 0054a8c0 / 0054a8d8.
   Returns the screen's result. */
int32_t P47_TitleDispatch(void) {
  int32_t res = 0;
  MenuAction40CD17();
  int32_t keepOpt = MenuOptBDFA50, keepCnt = G2_00575EE4;
  switch (P11_01271060) {
    case 1: case 2: case 3: case 4: case 5:
      res = R12_413D70();
      break;
    case 6:
      res = P47_Fn40A3A0();
      break;
    case 7:
      MenuOptBDFA50 = 1;
      G2_00575EE4 = 0x20;
      P47_Fn405BFA();
      res = R12_413D70();
      G2_00575EE4 = keepCnt;
      MenuOptBDFA50 = keepOpt;
      P47_Fn405BFA();
      break;
    default:
      break;
  }
  if (res == 0) P45_Wait(0x0054a8c0u, 0x0054a8d8u);
  return res;
}
/* P47_LoadFlyby — Game.exe 0041a130.  Loads SCRIPTS\FLYBY\FLATn.FBD; a missing file is a fatal error
   ("Files missing, please reinstall"). */
void P47_LoadFlyby(int32_t n) {
  char name[32];
  snprintf(name, sizeof name, "SCRIPTS\\FLYBY\\FLAT%d.FBD", (int)n);
  if (P132_LoadFlyby(name) == 0) P30_FatalError("Files missing, please reinstall");
}
/* P47_CameraModeText — Game.exe 004d9908.  Debug text "CameraMode: a, b, c" at the top-left
   (01137324, 00b5a8a0, P47_CamB). */
void P47_CameraModeText(void) {
  char text[32];
  snprintf(text, sizeof text, "CameraMode: %d, %d, %d", (int)G2_01137324, (int)G6_00B5A8A0, (int)P47_CamB);
  CursorSet004D94B7(0, 0);
  P47_Fn4D90F4(text);
}
/* P47_DirText — Game.exe 004d9827.  Debug text "Dir: NORTH|EAST|SOUTH|WEST" for heading `angle`
   (Round1024 gives the quadrant 0..3). */
void P47_DirText(int32_t angle) {
  static const char *const names[4] = { "NORTH", "EAST", "SOUTH", "WEST" };
  char text[64];
  uint8_t quadrant = (uint8_t)Round1024(angle);
  snprintf(text, sizeof text, "Dir: %s\n", quadrant < 4 ? names[quadrant] : "");
  P47_Fn4D90F4(text);
}
/* P47_PrepareTemp — Game.exe 00405f2e.  Prepares replay a (00405fdb(a, 0), 00406199(a)) and selects the
   "$TEMP$" replay config.  Returns 1 on success, 0 if a step failed. */
int32_t P47_PrepareTemp(int32_t a) {
  if (P47_Fn405FDB(a, 0) == 0) return 0;
  if (P47_Fn406199(a) == 0) return 0;
  P138_ReplayCfg("$TEMP$");
  return 1;
}
/* P47_GlideWinOpen — Game.exe 0042467f, stdcall in the hook build.  grSstWinOpen with the 7 arguments when
   Glide is in use (00b1c0d4); remembers the 5th argument in P47_WinArg5 — in the Glide 2 signature
   (hWnd, resolution, refresh, colour format, origin, colour buffers, aux buffers) that is likely the
   origin location.  TODO(RE): confirm against the Glide version the game links.
   Returns grSstWinOpen's result, 0 without Glide. */
int32_t P47_GlideWinOpen(int32_t a1, int32_t a2, int32_t a3, int32_t a4, int32_t a5, int32_t a6, int32_t a7) {
  if (D_00b1c0d4 == 0) return 0;
  P47_WinArg5 = a5;
  int32_t (P47_STD *f)(int32_t, int32_t, int32_t, int32_t, int32_t, int32_t, int32_t) =
      (int32_t (P47_STD *)(int32_t, int32_t, int32_t, int32_t, int32_t, int32_t, int32_t))glide_proc("_grSstWinOpen@28");
  return f != NULL ? f(a1, a2, a3, a4, a5, a6, a7) : 0;
}
/* P47_GlideSwap — Game.exe 0042651a.  grBufferSwap(0) (no vsync wait); while 01270c38 counts down, re-runs
   the view setup 00425b12(0, 0, 1) once per swap; counts swaps in P47_SwapCnt. */
void P47_GlideSwap(void) {
  RE_DBG(2);
  void (P47_STD *f)(int32_t) = (void (P47_STD *)(int32_t))glide_proc("_grBufferSwap@4");
  if (f != NULL) f(0);
  if (P11_01270c38 != 0) {
    Call00425B12(0, 0, 1);
    P11_01270c38--;
  }
  P47_SwapCnt++;
}
/* P47_TexTable — Game.exe 00424921.  Downloads a texture palette/table: grTexDownloadTable(tmu, type, data)
   on the Glide path (00b1c0d8 == 0), or the other renderer's handler 0041d50e (00b1c0d8 == 1).
   TODO(RE): argument names follow the Glide 2 grTexDownloadTable signature; the 4th is only used by 0041d50e. */
void P47_TexTable(int32_t tmu, int32_t table_type, int32_t data, int32_t d4) {
  if (D_00b1c0d4 == 0) return;
  if (D_00b1c0d8 == 0) {
    void (P47_STD *f)(int32_t, int32_t, int32_t) = (void (P47_STD *)(int32_t, int32_t, int32_t))glide_proc("_grTexDownloadTable@12");
    if (f != NULL) f(tmu, table_type, data);
  } else if (D_00b1c0d8 == 1) {
    Dispatch0041D50E(tmu, table_type, data, d4);
  }
}

