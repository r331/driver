/* DirectInput — восстановлено из Game.exe (Input.c). */
#include "ported34.h"
#include "engine.h"
#include <string.h>
GAME_VAR_DEF(void *, P34_Di, 0x00b31dd8)
GAME_VAR_DEF(void *, P34_Kbd, 0x00b31ddc)
GAME_VAR_DEF(void *, P34_Mouse, 0x00b31de0)
GAME_VAR_DEF(void *, P34_Joy, 0x00b31de4)
GAME_VAR_DEF(void *, P34_FfA, 0x00b31de8)
GAME_VAR_DEF(void *, P34_FfB, 0x00b31dec)
GAME_VAR_DEF(void *, P34_Event, 0x00b31df0)
GAME_VAR_DEF(int32_t, P34_Reg24, 0x00b31e24)
GAME_VAR_DEF(P34_DevArr, P34_EffA, 0x00b31cc0)
GAME_VAR_DEF(P34_DevArr, P34_EffB, 0x00b31c80)
GAME_VAR_DEF(P34_DevArr, P34_EffC, 0x00b31ce0)
GAME_VAR_DEF(P34_KeyArr, P34_Keys, 0x00d04b00)
GAME_VAR_DEF(P34_KeyArr, P34_KeysPrev, 0x00d04c00)

void P34_ReleaseInput(void) {
  if (P34_Event) { plat_event_close(P34_Event); P34_Event = NULL; }
  if (P34_Kbd) { plat_di_unacquire(P34_Kbd); plat_di_release(P34_Kbd); P34_Kbd = NULL; }
  if (P34_Mouse) { plat_di_unacquire(P34_Mouse); plat_di_release(P34_Mouse); P34_Mouse = NULL; }
  for (int i = 0; i < 8; i++) {
    if (P34_EffA[i]) { plat_di_release(P34_EffA[i]); P34_EffA[i] = NULL; }
    if (P34_EffB[i]) { plat_di_release(P34_EffB[i]); P34_EffB[i] = NULL; }
    if (P34_EffC[i]) { plat_di_unacquire(P34_EffC[i]); plat_di_release(P34_EffC[i]); P34_EffC[i] = NULL; }
  }
  P34_Joy = NULL; P34_FfA = NULL; P34_FfB = NULL;   /* de4/de8/dec только обнуляются, как в оригинале */
  if (P34_Di) { plat_di_release(P34_Di); P34_Di = NULL; }
  P34_Reg24 = 0;
}

int32_t P34_ReAcquire(int32_t dev) {
  void *d; const char *msg;
  if (dev == 0) { d = P34_Kbd; msg = "DIReAcquire: SetDataFormat failed"; }
  else if (dev == 1) { d = P34_Mouse; msg = "DIReAcquire: SetDataFormat failed"; }
  else if (dev == 2) { d = P34_Joy; msg = "DIReAcquire: SetDataFormat failed"; }
  else return 0;
  if (plat_di_set_format(d, dev) != 0) DebugLog(msg);
  return plat_di_acquire(d) == 0;
}

int32_t P34_ReadKeyboard(void) {
  memcpy(P34_KeysPrev, P34_Keys, 0x100);
  int32_t hr = plat_di_get_state(P34_Kbd, 0x100, P34_Keys);
  if (hr != 0) P34_ReAcquire(0);
  return hr == 0;
}
