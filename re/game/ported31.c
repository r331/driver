/* Окно игры и цикл сообщений — восстановлено из Game.exe (WinMain.c). */
#include "ported31.h"
#include "ported6.h"
#include "ported25.h"
#include "ported22.h"
#include "unported.h"
GAME_VAR_DEF(void *, P31_DDObj0, 0x00a42154)
GAME_VAR_DEF(void *, P31_DDObj1, 0x00a4215c)
GAME_VAR_DEF(void *, P31_DDObj2, 0x00a42160)
GAME_VAR_DEF(void *, P31_DDObj3, 0x00a42164)
GAME_VAR_DEF(void *, P31_DDObj4, 0x00a42174)
GAME_VAR_DEF(int32_t, P31_DDVal0, 0x00a421ac)
GAME_VAR_DEF(int32_t, P31_DDVal1, 0x00a421b0)
GAME_VAR_DEF(int32_t, P31_DDVal2, 0x00a421b4)
GAME_VAR_DEF(int32_t, P31_DDVal3, 0x00a421b8)
GAME_VAR_DEF(int32_t, P31_DDVal4, 0x00a421c0)
GAME_VAR_DEF(int32_t, P31_DDVal5, 0x00a421c8)
GAME_VAR_DEF(int32_t, P31_Active, 0x00bdf9cc)
GAME_VAR_DEF(int32_t, P31_WindowMode, 0x00bdf9c8)
GAME_VAR_DEF(int32_t, P31_PriorityHigh, 0x00b87e8c)
GAME_VAR_DEF(int32_t, P31_GlideModule, 0x00b1c0e8)

void Call00522323(void) { plat_pump_messages(); }

int32_t P31_InitWindow(void *hinst, int32_t show) {
  void *h = plat_game_window_create(hinst, show, "Driver V6.3w", G6_01270C28, G6_0125F3F0, P31_WndProc);
  G6_00BDF9C0 = (int32_t)(intptr_t)h;
  return h != NULL;
}

static void set_game_priority(void) { plat_set_priority(P31_PriorityHigh == 0 ? 1 : 2); }

int32_t P31_WndProc(void *hwnd, uint32_t msg, uint32_t wp, int32_t lp) {
  if (msg < 0x1d) {
    if (msg == 0x1c) {                         /* WM_ACTIVATEAPP */
      P31_Active = (int32_t)wp;
      if (wp == 0) { DrvCall004246D1(2); plat_set_priority(0); }
      else { DrvCall004246D1(1); set_game_priority(); }
    } else switch (msg) {
      case 1: G6_00BDF9C4 = lp; break;         /* WM_CREATE: hInstance */
      case 2: plat_post_quit(0); break;        /* WM_DESTROY */
      case 3: if (DrvCall004246D1(4) == 0) plat_post_close(hwnd); break; /* WM_MOVE */
      case 6:                                  /* WM_ACTIVATE */
        if ((wp & 0xffff) == 0 || (wp >> 16) != 0) { P31_Active = 0; DrvCall004246D1(2); }
        else { DrvCall004246D1(1); P31_Active = 1; }
        break;
    }
  } else {
    if (msg < 0x106) {
      if (msg < 0x104) {
        if (msg == 0x20) {                     /* WM_SETCURSOR */
          plat_set_cursor(P31_WindowMode == 1 ? 0 : 1);
          return 1;
        }
        if (msg < 0x100 || msg > 0x101) return plat_def_window_proc(hwnd, msg, wp, lp);
      }
      return 0;                                /* клавиши обрабатывает DirectInput */
    }
    if (msg == 0x3b9 && (wp == 1 || wp == 8)) P25_CdPlaying = 0; /* MM_MCINOTIFY */
  }
  return plat_def_window_proc(hwnd, msg, wp, lp);
}

int32_t P31_LoadGlide(void) {
  P31_GlideModule = (int32_t)(intptr_t)plat_dll_load("glide2x.dll");
  return P31_GlideModule != 0;
}

#define REL(v) do { if (v) { plat_dd_release(v); v = NULL; } } while (0)
void P31_ReleaseDirectDraw(void) {
  P22_EndScene();
  Call00421A39();
  REL(P31_DDObj3); REL(P31_DDObj2); REL(P31_DDObj4); REL(P24_ZSurf);
  REL(P24_Back); REL(P24_Primary); REL(P31_DDObj1);
  if (P24_DD) {
    if (P24_RestoreMode != 0) plat_dd_set_cooperative(P24_DD, P24_Hwnd, 8);  /* DDSCL_NORMAL */
    plat_dd_release(P24_DD); P24_DD = NULL;
  }
  REL(P31_DDObj0);
  P24_ModeW = 0; P24_ModeH = 0; P31_DDVal0 = 0; P31_DDVal1 = 0; P31_DDVal2 = 0; P31_DDVal3 = 0;
  P24_Hwnd = NULL; P31_DDVal4 = 0; P24_RestoreMode = 0; P31_DDVal5 = 0;
}
