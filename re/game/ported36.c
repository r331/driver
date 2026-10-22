/* DirectInput joystick / gamepad and the driving pad bit mask (Game.exe Input.c). */
/* DirectInput: джойстик и геймпад — восстановлено из Game.exe (Input.c). */
#include <stdlib.h>
#include "ported36.h"
#include "dik.h"
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

/* DIK_* scan codes and KEYCFG_* action indices: dik.h. */
/* Driving pad bits returned by P36_GetPadButtons (low four: meaning from the v2.14 native key block). */
#define PAD_BRAKE     0x01   /* brake / reverse */
#define PAD_GAS       0x02
#define PAD_RIGHT     0x04
#define PAD_LEFT      0x08
#define PAD_HARDTURN  0x10   /* key cfg[8]  "Fast Steer" (names of the key cfg slots: lang.eng 67..78, see dik.h) */
#define PAD_HANDBRAKE 0x20
#define PAD_BURNOUT   0x40   /* key cfg[10] "Burn Out" -> CAR_BURNOUT */
#define PAD_CRUISE    0x80   /* key cfg[14] "Cruise Control" (lang.eng key list; P107_CarInput holds the speed) */
#define PAD_HORN      0x100  /* key cfg[15] */
#define JOY_STATE_SIZE 0x50  /* sizeof(DIJOYSTATE) */
#define JOY_DEADZONE   8     /* |axis| <= 8 counts as centred */
enum { DEV_KEYBOARD = 0, DEV_MOUSE = 1, DEV_JOYSTICK = 2 };

/* P36_AcquireDevice — Game.exe 004e3ffe, cdecl.  Acquire DirectInput device dev (0 keyboard, 1 mouse, 2 joystick).  Returns 1 on success. */
int32_t P36_AcquireDevice(int32_t dev) {
  void *d;
  if (dev == DEV_KEYBOARD) d = P34_Kbd;
  else if (dev == DEV_MOUSE) d = P34_Mouse;
  else if (dev == DEV_JOYSTICK) d = P34_Joy;
  else return 0;
  return plat_di_acquire(d) == 0;
}

/* P36_SelectJoystick — Game.exe 004e3769, cdecl.  Make joystick idx the active one (device, force-feedback effects, axis capability flags).
   Returns 1; for an index outside 0..P36_JoyCount-1 clears the selection and returns 0. */
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

/* P36_GetPadButtons — Game.exe 004e39ac, cdecl.  Read the driving controls into *out as a bit mask (PAD_* above) from the configured keys
   P36_KeyCfg[4..10, 14, 15].  Returns 0 in pad mode 2.  Clears P36_Pad0..5.
   Native (v2.14, not in Game.exe): arrow keys and Space also drive unless RE_ARROWKEYS=0. */
void P36_GetPadButtons(uint32_t *out) {
  *out = 0;
  P36_Pad0 = 0; P36_Pad1 = 0; P36_Pad2 = 0; P36_Pad3 = 0; P36_Pad4 = 0; P36_Pad5 = 0;
  if (P36_PadMode == 2) return;
  static const uint8_t cfg[9] = { 4, 5, 6, 7, 8, 9, 10, 14, 15 };      /* индексы в P36_KeyCfg */
  static const uint32_t bit[9] = { PAD_LEFT, PAD_RIGHT, PAD_GAS, PAD_BRAKE, PAD_HARDTURN, PAD_HANDBRAKE, PAD_BURNOUT, PAD_CRUISE, PAD_HORN };
  for (int i = 0; i < 9; i++)
    if (P34_Keys[P36_KeyCfg[cfg[i]]] != 0) *out |= bit[i];
#ifndef RE_HOOK_BUILD
  /* v2.14 (только native, не в Game.exe): удобные клавиши езды в дополнение к настроенным — ↑ газ (бит 2, KeyCfg[6]),
     ↓ тормоз/назад (1, [7]), ← руль влево (8, [4]), → вправо (4, [5]), пробел — ручник (0x20, [9]).
     Меню не затронуты: P36_GetPadButtons зовётся только из такта езды (P132, 004d4bfb), меню читают стрелки P34_Keys
     напрямую (P107_MenuNav, P110, P114). RE_ARROWKEYS=0 — отключить. */
  {
    static int on = -1;
    if (on < 0) { const char *e = getenv("RE_ARROWKEYS"); on = !(e && *e == '0'); }
    if (on) {
      if (P34_Keys[DIK_UP] != 0) *out |= PAD_GAS;
      if (P34_Keys[DIK_DOWN] != 0) *out |= PAD_BRAKE;
      if (P34_Keys[DIK_LEFT] != 0) *out |= PAD_LEFT;
      if (P34_Keys[DIK_RIGHT] != 0) *out |= PAD_RIGHT;
      if (P34_Keys[DIK_SPACE] != 0) *out |= PAD_HANDBRAKE;
    }
  }
#endif
}

/* P36_PollInput — Game.exe 004e3391, cdecl.  Poll input once per frame.  Input mode 0: keyboard only.  Mode 2: keyboard plus joystick;
   keeps the previous joystick state, polls and reads DIJOYSTATE (re-acquiring on error).
   While driving (00b87efc == 0) the stick X sets the steering keys, buttons are copied to the
   configured key bytes (order 0..4, 6, 7, 5, 8..11) and, with P36_PrevFlag, a hard stick
   (|x| > 0x1b) also presses key cfg[8] (hard turn); in menus (00b87f00 == 0) buttons 0/1 and the stick
   press Return/Escape/arrows.  Returns 1 if input was read, 0 if inactive / no joystick /
   device lost. */
int32_t P36_PollInput(void) {
  if (P31_Active == 0) return 0;
  P35_UpdateForce();
  if (P35_InputMode == 0) {
    P36_PrevFlag = 0; P36_JoyX = 0; P21_AxisValue = 0;
    return P34_ReadKeyboard();
  }
  if (P35_InputMode != 2) return 0;
  if (P36_JoyPresent == 0) { P35_InputMode = 0; return 0; }
  memcpy(P36_JoyPrev, P36_JoyState, JOY_STATE_SIZE);
  P36_PrevJoyX = P36_JoyX; P9_00b31dfc = P21_AxisValue;
  P36_PrevFlag = P36_JoyFlag; P36_PrevAux = Q00B31E2C;
  P34_ReadKeyboard();
  if (G6_00B87EFC == 0 && P36_PadMode == 2) return 1;
  int32_t hr = plat_di_poll(P34_Joy);
  if (hr != 0 && hr != 1) { P34_ReAcquire(DEV_JOYSTICK); return 0; }   /* DI_OK / DI_NOEFFECT are fine */
  if (plat_di_get_state(P34_Joy, JOY_STATE_SIZE, P36_JoyState) != 0) { P34_ReAcquire(DEV_JOYSTICK); return 0; }
  int32_t lx, ly; memcpy(&lx, P36_JoyState, 4); memcpy(&ly, P36_JoyState + 4, 4);
  P36_JoyX = lx; P21_AxisValue = ly;
  if (G6_00B87EFC == 0) {                 /* driving: stick -> configured steering keys, buttons -> key bytes */
    P34_Keys[P36_KeyCfg[KEYCFG_LEFT]] = (lx < -JOY_DEADZONE) ? (uint8_t)(P34_Keys[P36_KeyCfg[KEYCFG_LEFT]] | 0x80) : 0;
    if (P36_JoyX < JOY_DEADZONE + 1) P34_Keys[P36_KeyCfg[KEYCFG_RIGHT]] = 0;
    else P34_Keys[P36_KeyCfg[KEYCFG_RIGHT]] |= 0x80;
    static const uint8_t src[12] = { 0, 1, 2, 3, 4, 6, 7, 5, 8, 9, 10, 11 };   /* порядок P19_Keys1: 0..4,6,7,5,8..11 */
    for (int i = 0; i < 12; i++) P21_SetAxisByte(P19_Keys1[src[i]], P36_KeyCfg[6 + i]);   /* P19_Keys1 bytes -> key cfg 6..17 */
    if (P36_PrevFlag != 0) {
      if (P36_JoyX > 0x1b) P34_Keys[P36_KeyCfg[KEYCFG_HARDTURN]] |= 0x80;
      if (P36_JoyX < -0x1b) P34_Keys[P36_KeyCfg[KEYCFG_HARDTURN]] |= 0x80;
    }
  } else if (Q00B87F00 == 0) {             /* menus: buttons 0/1 -> Return/Escape, stick -> arrow keys */
    if (IsButtonActive_004E3924(0)) P34_Keys[DIK_RETURN] |= 0x80;
    if (IsButtonActive_004E3924(1)) P34_Keys[DIK_ESCAPE] |= 0x80;
    if (P36_JoyX < -JOY_DEADZONE) P34_Keys[DIK_LEFT] |= 0x80;
    if (P36_JoyX > JOY_DEADZONE) P34_Keys[DIK_RIGHT] |= 0x80;
    if (P21_AxisValue < -JOY_DEADZONE) P34_Keys[DIK_UP] |= 0x80;
    if (P21_AxisValue > JOY_DEADZONE) P34_Keys[DIK_DOWN] |= 0x80;
  }
  return 1;
}
