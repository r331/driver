/* DirectInput: джойстик и геймпад — восстановлено из Game.exe (Input.c). */
#include "ported36.h"
#include <string.h>
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P36_JoyCount")
#undef P36_JoyCount
#pragma push_macro("P36_JoyCount") /*gvi*/
#undef P36_JoyCount /*gvi*/
int32_t P36_JoyCount;
#pragma pop_macro("P36_JoyCount") /*gvi*/
#pragma pop_macro("P36_JoyCount")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P36_JoyAxisCap")
#undef P36_JoyAxisCap
#pragma push_macro("P36_JoyAxisCap") /*gvi*/
#undef P36_JoyAxisCap /*gvi*/
P36_IntArr P36_JoyAxisCap;
#pragma pop_macro("P36_JoyAxisCap") /*gvi*/
#pragma pop_macro("P36_JoyAxisCap")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P36_JoyAux")
#undef P36_JoyAux
#pragma push_macro("P36_JoyAux") /*gvi*/
#undef P36_JoyAux /*gvi*/
P36_IntArr P36_JoyAux;
#pragma pop_macro("P36_JoyAux") /*gvi*/
#pragma pop_macro("P36_JoyAux")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P36_JoyFlag")
#undef P36_JoyFlag
#pragma push_macro("P36_JoyFlag") /*gvi*/
#undef P36_JoyFlag /*gvi*/
int32_t P36_JoyFlag;
#pragma pop_macro("P36_JoyFlag") /*gvi*/
#pragma pop_macro("P36_JoyFlag")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P36_JoyX")
#undef P36_JoyX
#pragma push_macro("P36_JoyX") /*gvi*/
#undef P36_JoyX /*gvi*/
int32_t P36_JoyX;
#pragma pop_macro("P36_JoyX") /*gvi*/
#pragma pop_macro("P36_JoyX")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P36_PrevJoyX")
#undef P36_PrevJoyX
#pragma push_macro("P36_PrevJoyX") /*gvi*/
#undef P36_PrevJoyX /*gvi*/
int32_t P36_PrevJoyX;
#pragma pop_macro("P36_PrevJoyX") /*gvi*/
#pragma pop_macro("P36_PrevJoyX")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P36_PrevFlag")
#undef P36_PrevFlag
#pragma push_macro("P36_PrevFlag") /*gvi*/
#undef P36_PrevFlag /*gvi*/
int32_t P36_PrevFlag;
#pragma pop_macro("P36_PrevFlag") /*gvi*/
#pragma pop_macro("P36_PrevFlag")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P36_PrevAux")
#undef P36_PrevAux
#pragma push_macro("P36_PrevAux") /*gvi*/
#undef P36_PrevAux /*gvi*/
int32_t P36_PrevAux;
#pragma pop_macro("P36_PrevAux") /*gvi*/
#pragma pop_macro("P36_PrevAux")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P36_JoyState")
#undef P36_JoyState
#pragma push_macro("P36_JoyState") /*gvi*/
#undef P36_JoyState /*gvi*/
P36_Bytes80 P36_JoyState;
#pragma pop_macro("P36_JoyState") /*gvi*/
#pragma pop_macro("P36_JoyState")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P36_JoyPrev")
#undef P36_JoyPrev
#pragma push_macro("P36_JoyPrev") /*gvi*/
#undef P36_JoyPrev /*gvi*/
P36_Bytes80 P36_JoyPrev;
#pragma pop_macro("P36_JoyPrev") /*gvi*/
#pragma pop_macro("P36_JoyPrev")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P36_JoyPresent")
#undef P36_JoyPresent
#pragma push_macro("P36_JoyPresent") /*gvi*/
#undef P36_JoyPresent /*gvi*/
int32_t P36_JoyPresent;
#pragma pop_macro("P36_JoyPresent") /*gvi*/
#pragma pop_macro("P36_JoyPresent")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P36_KeyCfg")
#undef P36_KeyCfg
#pragma push_macro("P36_KeyCfg") /*gvi*/
#undef P36_KeyCfg /*gvi*/
P36_Bytes80 P36_KeyCfg;
#pragma pop_macro("P36_KeyCfg") /*gvi*/
#pragma pop_macro("P36_KeyCfg")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P36_PadMode")
#undef P36_PadMode
#pragma push_macro("P36_PadMode") /*gvi*/
#undef P36_PadMode /*gvi*/
uint8_t P36_PadMode;
#pragma pop_macro("P36_PadMode") /*gvi*/
#pragma pop_macro("P36_PadMode")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P36_Pad0")
#undef P36_Pad0
#pragma push_macro("P36_Pad0") /*gvi*/
#undef P36_Pad0 /*gvi*/
uint8_t P36_Pad0;
#pragma pop_macro("P36_Pad0") /*gvi*/
#pragma pop_macro("P36_Pad0")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P36_Pad1")
#undef P36_Pad1
#pragma push_macro("P36_Pad1") /*gvi*/
#undef P36_Pad1 /*gvi*/
uint8_t P36_Pad1;
#pragma pop_macro("P36_Pad1") /*gvi*/
#pragma pop_macro("P36_Pad1")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P36_Pad2")
#undef P36_Pad2
#pragma push_macro("P36_Pad2") /*gvi*/
#undef P36_Pad2 /*gvi*/
uint8_t P36_Pad2;
#pragma pop_macro("P36_Pad2") /*gvi*/
#pragma pop_macro("P36_Pad2")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P36_Pad3")
#undef P36_Pad3
#pragma push_macro("P36_Pad3") /*gvi*/
#undef P36_Pad3 /*gvi*/
uint8_t P36_Pad3;
#pragma pop_macro("P36_Pad3") /*gvi*/
#pragma pop_macro("P36_Pad3")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P36_Pad4")
#undef P36_Pad4
#pragma push_macro("P36_Pad4") /*gvi*/
#undef P36_Pad4 /*gvi*/
uint8_t P36_Pad4;
#pragma pop_macro("P36_Pad4") /*gvi*/
#pragma pop_macro("P36_Pad4")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P36_Pad5")
#undef P36_Pad5
#pragma push_macro("P36_Pad5") /*gvi*/
#undef P36_Pad5 /*gvi*/
uint8_t P36_Pad5;
#pragma pop_macro("P36_Pad5") /*gvi*/
#pragma pop_macro("P36_Pad5")
#endif

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
