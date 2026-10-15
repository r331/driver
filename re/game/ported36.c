/* DirectInput: джойстик и геймпад — восстановлено из Game.exe (Input.c). */
#include "ported36.h"
#include <string.h>
GAME_VAR_DEF(int32_t, P36_JoyCount, 0x00b31e14)
GAME_VAR_DEF(P36_IntArr, P36_JoyAxisCap, 0x00b31d64)
GAME_VAR_DEF(P36_IntArr, P36_JoyAux, 0x00b31ca0)
GAME_VAR_DEF(int32_t, P36_JoyFlag, 0x00b31e28)
GAME_VAR_DEF(int32_t, P36_JoyX, 0x00b31e1c)
GAME_VAR_DEF(int32_t, P36_PrevJoyX, 0x00b31df8)
GAME_VAR_DEF(int32_t, P36_PrevFlag, 0x00b31e30)
GAME_VAR_DEF(int32_t, P36_PrevAux, 0x00b31e34)
GAME_VAR_DEF(P36_Bytes80, P36_JoyState, 0x00b31d88)
GAME_VAR_DEF(P36_Bytes80, P36_JoyPrev, 0x00b31d00)
GAME_VAR_DEF(int32_t, P36_JoyPresent, 0x00562a48)
GAME_VAR_DEF(P36_Bytes80, P36_KeyCfg, 0x00d04d00)
GAME_VAR_DEF(uint8_t, P36_PadMode, 0x00c4d70c)
GAME_VAR_DEF(uint8_t, P36_Pad0, 0x00d11939)
GAME_VAR_DEF(uint8_t, P36_Pad1, 0x00d11884)
GAME_VAR_DEF(uint8_t, P36_Pad2, 0x01136acc)
GAME_VAR_DEF(uint8_t, P36_Pad3, 0x01137370)
GAME_VAR_DEF(uint8_t, P36_Pad4, 0x01136c50)
GAME_VAR_DEF(uint8_t, P36_Pad5, 0x0113735c)

int32_t P36_AcquireDevice(int32_t dev) {
  void *d;
  if (dev == 0) d = P34_Kbd;
  else if (dev == 1) d = P34_Mouse;
  else if (dev == 2) d = P34_Joy;
  else return 0;
  return plat_di_acquire(d) == 0;
}

int32_t P36_SelectJoystick(int32_t idx) {
  if (idx < 0 || idx >= P36_JoyCount) {
    P34_Reg24 = 0; P36_JoyFlag = 0; Q00B31E2C = 0;
    P34_Joy = NULL; P34_FfA = NULL; P34_FfB = NULL; G00B31E18 = 0;
    return 0;
  }
  P34_Reg24 = 1;
  P36_JoyFlag = P36_JoyAxisCap[idx];
  Q00B31E2C = P36_JoyAux[idx];
  P34_Joy = P34_EffC[idx];     /* устройства джойстиков лежат в b31ce0, эффекты — b31cc0 / b31c80 */
  P34_FfA = P34_EffA[idx];
  P34_FfB = P34_EffB[idx];
  G00B31E18 = idx;
  return 1;
}

void P36_GetPadButtons(uint32_t *out) {
  *out = 0;
  P36_Pad0 = 0; P36_Pad1 = 0; P36_Pad2 = 0; P36_Pad3 = 0; P36_Pad4 = 0; P36_Pad5 = 0;
  if (P36_PadMode == 2) return;
  static const uint8_t cfg[9] = { 4, 5, 6, 7, 8, 9, 10, 14, 15 };      /* индексы в P36_KeyCfg */
  static const uint32_t bit[9] = { 8, 4, 2, 1, 0x10, 0x20, 0x40, 0x80, 0x100 };
  for (int i = 0; i < 9; i++)
    if (P34_Keys[P36_KeyCfg[cfg[i]]] != 0) *out |= bit[i];
}

int32_t P36_PollInput(void) {
  if (P31_Active == 0) return 0;
  P35_UpdateForce();
  if (P35_InputMode == 0) {
    P36_PrevFlag = 0; P36_JoyX = 0; P21_AxisValue = 0;
    return P34_ReadKeyboard();
  }
  if (P35_InputMode != 2) return 0;
  if (P36_JoyPresent == 0) { P35_InputMode = 0; return 0; }
  memcpy(P36_JoyPrev, P36_JoyState, 0x50);
  P36_PrevJoyX = P36_JoyX; P9_00b31dfc = P21_AxisValue;
  P36_PrevFlag = P36_JoyFlag; P36_PrevAux = Q00B31E2C;
  P34_ReadKeyboard();
  if (G6_00B87EFC == 0 && P36_PadMode == 2) return 1;
  int32_t hr = plat_di_poll(P34_Joy);
  if (hr != 0 && hr != 1) { P34_ReAcquire(2); return 0; }
  if (plat_di_get_state(P34_Joy, 0x50, P36_JoyState) != 0) { P34_ReAcquire(2); return 0; }
  int32_t lx, ly; memcpy(&lx, P36_JoyState, 4); memcpy(&ly, P36_JoyState + 4, 4);
  P36_JoyX = lx; P21_AxisValue = ly;
  if (G6_00B87EFC == 0) {
    P34_Keys[P36_KeyCfg[4]] = (lx < -8) ? (uint8_t)(P34_Keys[P36_KeyCfg[4]] | 0x80) : 0;
    if (P36_JoyX < 9) P34_Keys[P36_KeyCfg[5]] = 0;
    else P34_Keys[P36_KeyCfg[5]] |= 0x80;
    static const uint8_t src[12] = { 0, 1, 2, 3, 4, 6, 7, 5, 8, 9, 10, 11 };   /* порядок P19_Keys1: 0..4,6,7,5,8..11 */
    for (int i = 0; i < 12; i++) P21_SetAxisByte(P19_Keys1[src[i]], P36_KeyCfg[6 + i]);
    if (P36_PrevFlag != 0) {
      if (P36_JoyX > 0x1b) P34_Keys[P36_KeyCfg[8]] |= 0x80;
      if (P36_JoyX < -0x1b) P34_Keys[P36_KeyCfg[8]] |= 0x80;
    }
  } else if (Q00B87F00 == 0) {
    if (IsButtonActive_004E3924(0)) P34_Keys[0x1c] |= 0x80;
    if (IsButtonActive_004E3924(1)) P34_Keys[0x01] |= 0x80;
    if (P36_JoyX < -8) P34_Keys[0xcb] |= 0x80;
    if (P36_JoyX > 8) P34_Keys[0xcd] |= 0x80;
    if (P21_AxisValue < -8) P34_Keys[0xc8] |= 0x80;
    if (P21_AxisValue > 8) P34_Keys[0xd0] |= 0x80;
  }
  return 1;
}
