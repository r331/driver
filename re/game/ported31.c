/* ported31 — game window, window procedure, message pump, glide2x.dll loading and DirectDraw teardown
   (WinMain.c in Game.exe), implemented on top of the plat_* layer.  Original note: */
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
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P31_DDVal0")
#undef P31_DDVal0
#pragma push_macro("P31_DDVal0") /*gvi*/
#undef P31_DDVal0 /*gvi*/
int32_t P31_DDVal0;
#pragma pop_macro("P31_DDVal0") /*gvi*/
#pragma pop_macro("P31_DDVal0")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P31_DDVal1")
#undef P31_DDVal1
#pragma push_macro("P31_DDVal1") /*gvi*/
#undef P31_DDVal1 /*gvi*/
int32_t P31_DDVal1;
#pragma pop_macro("P31_DDVal1") /*gvi*/
#pragma pop_macro("P31_DDVal1")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P31_DDVal2")
#undef P31_DDVal2
#pragma push_macro("P31_DDVal2") /*gvi*/
#undef P31_DDVal2 /*gvi*/
int32_t P31_DDVal2;
#pragma pop_macro("P31_DDVal2") /*gvi*/
#pragma pop_macro("P31_DDVal2")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P31_DDVal3")
#undef P31_DDVal3
#pragma push_macro("P31_DDVal3") /*gvi*/
#undef P31_DDVal3 /*gvi*/
int32_t P31_DDVal3;
#pragma pop_macro("P31_DDVal3") /*gvi*/
#pragma pop_macro("P31_DDVal3")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P31_DDVal4")
#undef P31_DDVal4
#pragma push_macro("P31_DDVal4") /*gvi*/
#undef P31_DDVal4 /*gvi*/
int32_t P31_DDVal4;
#pragma pop_macro("P31_DDVal4") /*gvi*/
#pragma pop_macro("P31_DDVal4")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P31_DDVal5")
#undef P31_DDVal5
#pragma push_macro("P31_DDVal5") /*gvi*/
#undef P31_DDVal5 /*gvi*/
int32_t P31_DDVal5;
#pragma pop_macro("P31_DDVal5") /*gvi*/
#pragma pop_macro("P31_DDVal5")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P31_Active")
#undef P31_Active
#pragma push_macro("P31_Active") /*gvi*/
#undef P31_Active /*gvi*/
int32_t P31_Active;
#pragma pop_macro("P31_Active") /*gvi*/
#pragma pop_macro("P31_Active")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P31_WindowMode")
#undef P31_WindowMode
#pragma push_macro("P31_WindowMode") /*gvi*/
#undef P31_WindowMode /*gvi*/
int32_t P31_WindowMode;
#pragma pop_macro("P31_WindowMode") /*gvi*/
#pragma pop_macro("P31_WindowMode")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P31_PriorityHigh")
#undef P31_PriorityHigh
#pragma push_macro("P31_PriorityHigh") /*gvi*/
#undef P31_PriorityHigh /*gvi*/
int32_t P31_PriorityHigh;
#pragma pop_macro("P31_PriorityHigh") /*gvi*/
#pragma pop_macro("P31_PriorityHigh")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P31_GlideModule")
#undef P31_GlideModule
#pragma push_macro("P31_GlideModule") /*gvi*/
#undef P31_GlideModule /*gvi*/
int32_t P31_GlideModule;
#pragma pop_macro("P31_GlideModule") /*gvi*/
#pragma pop_macro("P31_GlideModule")
#endif

/* Win32 message ids handled by P31_WndProc (file-local names; values as in <winuser.h> / <mmsystem.h>). */
#define WMSG_CREATE        0x001
#define WMSG_DESTROY       0x002
#define WMSG_MOVE          0x003
#define WMSG_ACTIVATE      0x006
#define WMSG_ACTIVATEAPP   0x01c
#define WMSG_SETCURSOR     0x020
#define WMSG_KEYDOWN       0x100
#define WMSG_KEYUP         0x101
#define WMSG_SYSKEYDOWN    0x104
#define WMSG_SYSKEYUP      0x105
#define WMSG_MCINOTIFY     0x3b9   /* MM_MCINOTIFY */
#define MCINOTIFY_SUCCESSFUL 1
#define MCINOTIFY_FAILURE    8

/* Call00522323 — Game.exe 00522323.  Pumps all pending window messages (PeekMessage loop in the original). */
void Call00522323(void) { plat_pump_messages(); }

/* P31_InitWindow — Game.exe 005223dc.  Creates the game window "Driver V6.3w" (class "Driver", size from
   G6_01270C28 x G6_0125F3F0) with P31_WndProc and shows it.  Stores the handle in G6_00BDF9C0.
   Returns 1 on success, 0 on failure. */
int32_t P31_InitWindow(void *hinst, int32_t show) {
  void *h = plat_game_window_create(hinst, show, "Driver V6.3w", G6_01270C28, G6_0125F3F0, P31_WndProc);
  G6_00BDF9C0 = (int32_t)(intptr_t)h;
  return h != NULL;
}

/* Process priority while active: 1 = above normal (P31_PriorityHigh == 0), 2 = realtime; 0 = normal. */
static void set_game_priority(void) { plat_set_priority(P31_PriorityHigh == 0 ? 1 : 2); }

/* P31_WndProc — Game.exe 005224a8 (stdcall in the original, hooked since v1.95).  Window procedure.
   Activation (WM_ACTIVATEAPP / WM_ACTIVATE): sets P31_Active, notifies the renderer via 004246D1(1 = gained /
   2 = lost) and switches process priority.  WM_CREATE stores the instance handle, WM_DESTROY posts quit;
   WM_MOVE asks 004246D1(4) and closes the window when it returns 0 (TODO(RE): unsure — kept literally).
   WM_SETCURSOR hides the cursor in window mode 1.  Key messages are swallowed (input comes from DirectInput).
   MM_MCINOTIFY with success/failure marks CD audio as stopped (P25_CdPlaying = 0).  Everything else goes to
   the default window procedure. */
int32_t P31_WndProc(void *hwnd, uint32_t msg, uint32_t wp, int32_t lp) {
  if (msg < WMSG_ACTIVATEAPP + 1) {
    if (msg == WMSG_ACTIVATEAPP) {                         /* WM_ACTIVATEAPP */
      P31_Active = (int32_t)wp;
      if (wp == 0) { DrvCall004246D1(2); plat_set_priority(0); }
      else { DrvCall004246D1(1); set_game_priority(); }
    } else switch (msg) {
      case WMSG_CREATE: G6_00BDF9C4 = plat_wm_create_hinst(lp); break;   /* WM_CREATE: CREATESTRUCT.hInstance (+4) */
      case WMSG_DESTROY: plat_post_quit(0); break;        /* WM_DESTROY */
      case WMSG_MOVE: if (DrvCall004246D1(4) == 0) plat_post_close(hwnd); break; /* WM_MOVE */
      case WMSG_ACTIVATE:                      /* WM_ACTIVATE: LOWORD(wp) = state, HIWORD(wp) = minimized */
        if ((wp & 0xffff) == 0 || (wp >> 16) != 0) { P31_Active = 0; DrvCall004246D1(2); }
        else { DrvCall004246D1(1); P31_Active = 1; }
        break;
    }
  } else {
    if (msg < WMSG_SYSKEYUP + 1) {
      if (msg < WMSG_SYSKEYDOWN) {
        if (msg == WMSG_SETCURSOR) {                     /* WM_SETCURSOR */
          plat_set_cursor(P31_WindowMode == 1 ? 0 : 1);
          return 1;
        }
        if (msg < WMSG_KEYDOWN || msg > WMSG_KEYUP) return plat_def_window_proc(hwnd, msg, wp, lp);
      }
      return 0;                                /* клавиши обрабатывает DirectInput */
    }
    if (msg == WMSG_MCINOTIFY && (wp == MCINOTIFY_SUCCESSFUL || wp == MCINOTIFY_FAILURE)) P25_CdPlaying = 0; /* MM_MCINOTIFY */
  }
  return plat_def_window_proc(hwnd, msg, wp, lp);
}

/* P31_LoadGlide — Game.exe 00425730.  LoadLibrary("glide2x.dll") into P31_GlideModule; 1 if it loaded. */
int32_t P31_LoadGlide(void) {
  P31_GlideModule = (int32_t)(intptr_t)plat_dll_load("glide2x.dll");
  return P31_GlideModule != 0;
}

#define REL(v) do { if (v) { plat_dd_release(v); v = NULL; } } while (0)
/* P31_ReleaseDirectDraw — Game.exe 0041f2a0.  Ends the scene, releases every DirectDraw / Direct3D COM object
   (surfaces, Z buffer, device objects), restores the normal cooperative level if the display mode was changed,
   releases DirectDraw itself and zeroes the cached mode / handle state. */
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
