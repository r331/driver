/* dik.h — DirectInput keyboard scan codes (DIK_*, values as in dinput.h) and the key-configuration action
 * indices (KEYCFG_*) used by the game and the SDL input layer.  The game reads its keyboard state as 256
 * bytes, one per scan code (P34_Keys; bit 0x80 = pressed).  Only the codes the code actually uses are
 * listed.  Plain integer constants: using them never changes the generated code.
 * Never include this together with the real <dinput.h> (same names). */
#pragma once

#define DIK_ESCAPE      0x01
#define DIK_BACK        0x0e   /* Backspace */
#define DIK_RETURN      0x1c
#define DIK_LSHIFT      0x2a
#define DIK_PERIOD      0x34
#define DIK_RSHIFT      0x36
#define DIK_SPACE       0x39
#define DIK_CAPITAL     0x3a   /* Caps Lock */
#define DIK_NUMPADENTER 0x9c
#define DIK_UP          0xc8
#define DIK_LEFT        0xcb
#define DIK_RIGHT       0xcd
#define DIK_DOWN        0xd0

/* ---- Indices into the key configuration P36_KeyCfg (DIK code per action) ----
   The actions are the "Key Redefine:" list of lang.eng (ids 67..78), but the slot order is the game's own:
   4..10 from P36_GetPadButtons / P107_CarInput (14 = Cruise Control: pad bit 0x80 makes P107_CarInput hold
   the current speed); 13 look behind, 15 horn as before.  11 / 12 are the remaining Look Left / Look Right —
   inferred (not checked which is which).  0..3: TODO(RE) (not driving controls). */
enum {
  KEYCFG_LEFT = 4, KEYCFG_RIGHT = 5, KEYCFG_GAS = 6, KEYCFG_BRAKE = 7,
  KEYCFG_HARDTURN = 8, KEYCFG_HANDBRAKE = 9, KEYCFG_BURNOUT = 10,
  KEYCFG_LOOKLEFT = 11, KEYCFG_LOOKRIGHT = 12,
  KEYCFG_LOOKBACK = 13, KEYCFG_CRUISE = 14, KEYCFG_HORN = 15
};
