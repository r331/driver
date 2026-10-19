/* DirectInput — восстановлено из Game.exe (Input.c). */
/* ported34.c — DirectInput shutdown, device re-acquire and keyboard polling (Game.exe Input.c).
   Device objects live at 00b31dd8..00b31df0 (IDirectInput, keyboard, mouse, joystick, two force-feedback
   slots, notification event); P34_EffA/B/C are three arrays of 8 effect/device objects.  In native the
   plat_di_* calls are the SDL replacements for the COM methods. */
#include "ported34.h"
#include "engine.h"
#include <string.h>

/* Device index used by P34_ReAcquire (and the SetDataFormat call behind it). */
enum { DI_DEV_KEYBOARD = 0, DI_DEV_MOUSE = 1, DI_DEV_JOYSTICK = 2 };
#define DI_EFFECT_SLOTS  8       /* entries in each of P34_EffA / P34_EffB / P34_EffC */
#define DI_KEY_COUNT     0x100   /* DirectInput keyboard state: 256 bytes, one per DIK_ scan code */
GAME_VAR_DEF(void *, P34_Di, 0x00b31dd8)
GAME_VAR_DEF(void *, P34_Kbd, 0x00b31ddc)
GAME_VAR_DEF(void *, P34_Mouse, 0x00b31de0)
GAME_VAR_DEF(void *, P34_Joy, 0x00b31de4)
GAME_VAR_DEF(void *, P34_FfA, 0x00b31de8)
GAME_VAR_DEF(void *, P34_FfB, 0x00b31dec)
GAME_VAR_DEF(void *, P34_Event, 0x00b31df0)
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P34_Reg24")
#undef P34_Reg24
#pragma push_macro("P34_Reg24") /*gvi*/
#undef P34_Reg24 /*gvi*/
int32_t P34_Reg24;
#pragma pop_macro("P34_Reg24") /*gvi*/
#pragma pop_macro("P34_Reg24")
#endif
GAME_VAR_DEF(P34_DevArr, P34_EffA, 0x00b31cc0)
GAME_VAR_DEF(P34_DevArr, P34_EffB, 0x00b31c80)
GAME_VAR_DEF(P34_DevArr, P34_EffC, 0x00b31ce0)
#ifdef RE_HOOK_BUILD   /* v2.03: в native — псевдонимы над A_00D04B00 (ported34.h) */
GAME_VAR_DEF(P34_KeyArr, P34_Keys, 0x00d04b00)
GAME_VAR_DEF(P34_KeyArr, P34_KeysPrev, 0x00d04c00)
#endif

/* P34_ReleaseInput — Game.exe 004e31d5, cdecl.  Releases every DirectInput object: closes the event,
   unacquires + releases keyboard and mouse, releases all effect slots (C slots are also unacquired),
   then IDirectInput itself.  Side effects: all P34_* device pointers and P34_Reg24 set to 0/NULL.
   Joystick and force-feedback pointers are only cleared, not released (as in the original). */
void P34_ReleaseInput(void) {
  if (P34_Event) { plat_event_close(P34_Event); P34_Event = NULL; }
  if (P34_Kbd) { plat_di_unacquire(P34_Kbd); plat_di_release(P34_Kbd); P34_Kbd = NULL; }
  if (P34_Mouse) { plat_di_unacquire(P34_Mouse); plat_di_release(P34_Mouse); P34_Mouse = NULL; }
  for (int i = 0; i < DI_EFFECT_SLOTS; i++) {
    if (P34_EffA[i]) { plat_di_release(P34_EffA[i]); P34_EffA[i] = NULL; }
    if (P34_EffB[i]) { plat_di_release(P34_EffB[i]); P34_EffB[i] = NULL; }
    if (P34_EffC[i]) { plat_di_unacquire(P34_EffC[i]); plat_di_release(P34_EffC[i]); P34_EffC[i] = NULL; }
  }
  P34_Joy = NULL; P34_FfA = NULL; P34_FfB = NULL;   /* de4/de8/dec только обнуляются, как в оригинале */
  if (P34_Di) { plat_di_release(P34_Di); P34_Di = NULL; }
  P34_Reg24 = 0;
}

/* P34_ReAcquire — Game.exe 004e4076 ("DIReAcquire"), cdecl.  dev: DI_DEV_KEYBOARD / MOUSE / JOYSTICK.
   Re-applies the device's data format (logs on failure — the original uses the same message for all
   three devices) and acquires it again.  Returns 1 if Acquire succeeded, 0 otherwise or for an unknown dev. */
int32_t P34_ReAcquire(int32_t dev) {
  void *d; const char *msg;
  if (dev == DI_DEV_KEYBOARD) { d = P34_Kbd; msg = "DIReAcquire: SetDataFormat failed"; }
  else if (dev == DI_DEV_MOUSE) { d = P34_Mouse; msg = "DIReAcquire: SetDataFormat failed"; }
  else if (dev == DI_DEV_JOYSTICK) { d = P34_Joy; msg = "DIReAcquire: SetDataFormat failed"; }
  else return 0;
  if (plat_di_set_format(d, dev) != 0) DebugLog(msg);
  return plat_di_acquire(d) == 0;
}

/* P34_ReadKeyboard — Game.exe 004e417f, cdecl.  Polls the keyboard once per frame: the previous
   state is saved to P34_KeysPrev (so "pressed this frame" = Keys[k] && !KeysPrev[k]), then
   GetDeviceState fills P34_Keys (256 bytes).  On failure the keyboard is re-acquired; this frame's
   state is then whatever GetDeviceState left.  Returns 1 on success, 0 on failure. */
int32_t P34_ReadKeyboard(void) {
  memcpy(P34_KeysPrev, P34_Keys, DI_KEY_COUNT);
  int32_t hr = plat_di_get_state(P34_Kbd, DI_KEY_COUNT, P34_Keys);
  if (hr != 0) P34_ReAcquire(DI_DEV_KEYBOARD);
  return hr == 0;
}
