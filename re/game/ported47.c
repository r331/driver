/* Мелкие функции игры — восстановлено из Game.exe (cdecl). */
#include "ported132.h"
#include "ported47.h"
#include "ported33.h"
#include "crt.h"
#include <stdio.h>
#include <string.h>
#ifdef RE_HOOK_BUILD
#  define P47_STD __attribute__((stdcall))
#else
#  define P47_STD
#endif
GAME_VAR_DEF(P47_SlotArr, P47_Slots, 0x00c80f60)
GAME_VAR_DEF(int32_t, P47_Limit, 0x00c810cc)
GAME_VAR_DEF(int32_t, P47_Flag, 0x0112b268)
GAME_VAR_DEF(int32_t, P47_CamB, 0x00b5a8a4)
GAME_VAR_DEF(int32_t, P47_WinArg5, 0x00b1c0dc)
GAME_VAR_DEF(int32_t, P47_SwapCnt, 0x01270c30)

static void *glide_proc(const char *name) {
  for (int i = 0; i < P33_GlideCount(); i++)
    if (strcmp(P33_GlideName(i), name) == 0) return P33_GlideProc(i);
  return NULL;
}

int32_t P47_ReadLine(void *file, char *buf) {
  return g_fgets(buf, 0x80, file) == NULL ? -1 : 0;
}
int32_t P47_Call51B111(int32_t a, int32_t b) {
  P47_Fn51B111(a, b);
  return 1;
}
int32_t P47_NoFlags(int32_t a, int32_t b) {
  return (P47_Fn51B566(a, b) & 0x3c000000u) == 0;
}
void P47_ResetPick(void) {
  P47_Flag = 0;
  int32_t sel = P14_00c810e8;
  if (sel >= 1 && sel <= 4 && P47_Slots[sel - 1] != -1) {
    MenuClick004F8ACC(P47_Slots[sel - 1] + 0xf000);
    P47_Slots[sel - 1] = -1;
  }
  if (P47_Limit > 0x32) P47_Limit = 0x32;
  G2_00D118A8 = 1;
}
int32_t P47_TitleDispatch(void) {
  int32_t r = 0;
  MenuAction40CD17();
  int32_t keepOpt = MenuOptBDFA50, keepCnt = G2_00575EE4;
  switch (P11_01271060) {
    case 1: case 2: case 3: case 4: case 5:
      r = R12_413D70();
      break;
    case 6:
      r = P47_Fn40A3A0();
      break;
    case 7:
      MenuOptBDFA50 = 1;
      G2_00575EE4 = 0x20;
      P47_Fn405BFA();
      r = R12_413D70();
      G2_00575EE4 = keepCnt;
      MenuOptBDFA50 = keepOpt;
      P47_Fn405BFA();
      break;
    default:
      break;
  }
  if (r == 0) P45_Wait(0x0054a8c0u, 0x0054a8d8u);
  return r;
}
void P47_LoadFlyby(int32_t n) {
  char name[32];
  snprintf(name, sizeof name, "SCRIPTS\\FLYBY\\FLAT%d.FBD", (int)n);
  if (P132_LoadFlyby(name) == 0) P30_FatalError("Files missing, please reinstall");
}
void P47_CameraModeText(void) {
  char text[32];
  snprintf(text, sizeof text, "CameraMode: %d, %d, %d", (int)G2_01137324, (int)G6_00B5A8A0, (int)P47_CamB);
  CursorSet004D94B7(0, 0);
  P47_Fn4D90F4(text);
}
void P47_DirText(int32_t a) {
  static const char *const names[4] = { "NORTH", "EAST", "SOUTH", "WEST" };
  char text[64];
  uint8_t i = (uint8_t)Round1024(a);
  snprintf(text, sizeof text, "Dir: %s\n", i < 4 ? names[i] : "");
  P47_Fn4D90F4(text);
}
int32_t P47_PrepareTemp(int32_t a) {
  if (P47_Fn405FDB(a, 0) == 0) return 0;
  if (P47_Fn406199(a) == 0) return 0;
  P47_Fn517D58("$TEMP$");
  return 1;
}
int32_t P47_GlideWinOpen(int32_t a1, int32_t a2, int32_t a3, int32_t a4, int32_t a5, int32_t a6, int32_t a7) {
  if (D_00b1c0d4 == 0) return 0;
  P47_WinArg5 = a5;
  int32_t (P47_STD *f)(int32_t, int32_t, int32_t, int32_t, int32_t, int32_t, int32_t) =
      (int32_t (P47_STD *)(int32_t, int32_t, int32_t, int32_t, int32_t, int32_t, int32_t))glide_proc("_grSstWinOpen@28");
  return f != NULL ? f(a1, a2, a3, a4, a5, a6, a7) : 0;
}
void P47_GlideSwap(void) {
  void (P47_STD *f)(int32_t) = (void (P47_STD *)(int32_t))glide_proc("_grBufferSwap@4");
  if (f != NULL) f(0);
  if (P11_01270c38 != 0) {
    Call00425B12(0, 0, 1);
    P11_01270c38--;
  }
  P47_SwapCnt++;
}
void P47_TexTable(int32_t a, int32_t b, int32_t c, int32_t d) {
  if (D_00b1c0d4 == 0) return;
  if (D_00b1c0d8 == 0) {
    void (P47_STD *f)(int32_t, int32_t, int32_t) = (void (P47_STD *)(int32_t, int32_t, int32_t))glide_proc("_grTexDownloadTable@12");
    if (f != NULL) f(a, b, c);
  } else if (D_00b1c0d8 == 1) {
    Dispatch0041D50E(a, b, c, d);
  }
}
