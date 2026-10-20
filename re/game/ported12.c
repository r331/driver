/* ported12 — batch of small Game.exe functions (cdecl); each name P12_FnXXXXXXXX carries its Game.exe address.
   Frontend menu actions, screen fades, the 1/z table, traffic / particle / texture housekeeping, camera route
   stepping, save-game naming and a few HUD helpers.  Brief comments only; most globals keep address names. */
#include "ported139.h"
#include "ported140.h"
#include "ported138.h"
#include "ported129.h"
#include "ported71.h"
#include "ported124.h"
#include "reptr.h"
#include "ported12.h"
#include "drawdist.h"
#include "ported98.h"
#include "ported118.h"
#include "ported40.h"
#include "ported43.h"
#include "ported7.h"
#include "ported127.h"
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P12_00bdfa40")
#undef P12_00bdfa40
#pragma push_macro("P12_00bdfa40") /*gvi*/
#undef P12_00bdfa40 /*gvi*/
int32_t P12_00bdfa40;
#pragma pop_macro("P12_00bdfa40") /*gvi*/
#pragma pop_macro("P12_00bdfa40")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P12_00b87ef8")
#undef P12_00b87ef8
#pragma push_macro("P12_00b87ef8") /*gvi*/
#undef P12_00b87ef8 /*gvi*/
int32_t P12_00b87ef8;
#pragma pop_macro("P12_00b87ef8") /*gvi*/
#pragma pop_macro("P12_00b87ef8")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P12_005f7e5c")
#undef P12_005f7e5c
#pragma push_macro("P12_005f7e5c") /*gvi*/
#undef P12_005f7e5c /*gvi*/
int32_t P12_005f7e5c;
#pragma pop_macro("P12_005f7e5c") /*gvi*/
#pragma pop_macro("P12_005f7e5c")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P12_005f7e60")
#undef P12_005f7e60
#pragma push_macro("P12_005f7e60") /*gvi*/
#undef P12_005f7e60 /*gvi*/
int32_t P12_005f7e60;
#pragma pop_macro("P12_005f7e60") /*gvi*/
#pragma pop_macro("P12_005f7e60")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P12_00575f50")
#undef P12_00575f50
#pragma push_macro("P12_00575f50") /*gvi*/
#undef P12_00575f50 /*gvi*/
int32_t P12_00575f50;
#pragma pop_macro("P12_00575f50") /*gvi*/
#pragma pop_macro("P12_00575f50")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P12_00b87e58")
#undef P12_00b87e58
#pragma push_macro("P12_00b87e58") /*gvi*/
#undef P12_00b87e58 /*gvi*/
int32_t P12_00b87e58;
#pragma pop_macro("P12_00b87e58") /*gvi*/
#pragma pop_macro("P12_00b87e58")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P12_00b87e5c")
#undef P12_00b87e5c
#pragma push_macro("P12_00b87e5c") /*gvi*/
#undef P12_00b87e5c /*gvi*/
int32_t P12_00b87e5c;
#pragma pop_macro("P12_00b87e5c") /*gvi*/
#pragma pop_macro("P12_00b87e5c")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P12_00b32980")
#undef P12_00b32980
#pragma push_macro("P12_00b32980") /*gvi*/
#undef P12_00b32980 /*gvi*/
float P12_00b32980;
#pragma pop_macro("P12_00b32980") /*gvi*/
#pragma pop_macro("P12_00b32980")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P12_00b3297c")
#undef P12_00b3297c
#pragma push_macro("P12_00b3297c") /*gvi*/
#undef P12_00b3297c /*gvi*/
float P12_00b3297c;
#pragma pop_macro("P12_00b3297c") /*gvi*/
#pragma pop_macro("P12_00b3297c")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P12_00546088")
#undef P12_00546088
#pragma push_macro("P12_00546088") /*gvi*/
#undef P12_00546088 /*gvi*/
float P12_00546088;
#pragma pop_macro("P12_00546088") /*gvi*/
#pragma pop_macro("P12_00546088")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P12_00546084")
#undef P12_00546084
#pragma push_macro("P12_00546084") /*gvi*/
#undef P12_00546084 /*gvi*/
float P12_00546084;
#pragma pop_macro("P12_00546084") /*gvi*/
#pragma pop_macro("P12_00546084")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P12_00ba53a0")
#undef P12_00ba53a0
#pragma push_macro("P12_00ba53a0") /*gvi*/
#undef P12_00ba53a0 /*gvi*/
p12_00ba53a0_t P12_00ba53a0;
#pragma pop_macro("P12_00ba53a0") /*gvi*/
#pragma pop_macro("P12_00ba53a0")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P12_01144340")
#undef P12_01144340
#pragma push_macro("P12_01144340") /*gvi*/
#undef P12_01144340 /*gvi*/
p12_01144340_t P12_01144340;
#pragma pop_macro("P12_01144340") /*gvi*/
#pragma pop_macro("P12_01144340")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P12_0112da00")
#undef P12_0112da00
#pragma push_macro("P12_0112da00") /*gvi*/
#undef P12_0112da00 /*gvi*/
p12_0112da00_t P12_0112da00;
#pragma pop_macro("P12_0112da00") /*gvi*/
#pragma pop_macro("P12_0112da00")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P12_00bdf980")
#undef P12_00bdf980
#pragma push_macro("P12_00bdf980") /*gvi*/
#undef P12_00bdf980 /*gvi*/
int32_t P12_00bdf980;
#pragma pop_macro("P12_00bdf980") /*gvi*/
#pragma pop_macro("P12_00bdf980")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P12_00bde728")
#undef P12_00bde728
#pragma push_macro("P12_00bde728") /*gvi*/
#undef P12_00bde728 /*gvi*/
int32_t P12_00bde728;
#pragma pop_macro("P12_00bde728") /*gvi*/
#pragma pop_macro("P12_00bde728")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P12_00bde764")
#undef P12_00bde764
#pragma push_macro("P12_00bde764") /*gvi*/
#undef P12_00bde764 /*gvi*/
int32_t P12_00bde764;
#pragma pop_macro("P12_00bde764") /*gvi*/
#pragma pop_macro("P12_00bde764")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P12_00bde760")
#undef P12_00bde760
#pragma push_macro("P12_00bde760") /*gvi*/
#undef P12_00bde760 /*gvi*/
int32_t P12_00bde760;
#pragma pop_macro("P12_00bde760") /*gvi*/
#pragma pop_macro("P12_00bde760")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P12_00b5a898")
#undef P12_00b5a898
#pragma push_macro("P12_00b5a898") /*gvi*/
#undef P12_00b5a898 /*gvi*/
int32_t P12_00b5a898;
#pragma pop_macro("P12_00b5a898") /*gvi*/
#pragma pop_macro("P12_00b5a898")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P12_0054b010")
#undef P12_0054b010
#pragma push_macro("P12_0054b010") /*gvi*/
#undef P12_0054b010 /*gvi*/
p12_0054b010_t P12_0054b010;
#pragma pop_macro("P12_0054b010") /*gvi*/
#pragma pop_macro("P12_0054b010")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P12_005fe7a8")
#undef P12_005fe7a8
#pragma push_macro("P12_005fe7a8") /*gvi*/
#undef P12_005fe7a8 /*gvi*/
p12_005fe7a8_t P12_005fe7a8;
#pragma pop_macro("P12_005fe7a8") /*gvi*/
#pragma pop_macro("P12_005fe7a8")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P12_005fe884")
#undef P12_005fe884
#pragma push_macro("P12_005fe884") /*gvi*/
#undef P12_005fe884 /*gvi*/
p12_005fe884_t P12_005fe884;
#pragma pop_macro("P12_005fe884") /*gvi*/
#pragma pop_macro("P12_005fe884")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P12_00d17b90")
#undef P12_00d17b90
#pragma push_macro("P12_00d17b90") /*gvi*/
#undef P12_00d17b90 /*gvi*/
int32_t P12_00d17b90;
#pragma pop_macro("P12_00d17b90") /*gvi*/
#pragma pop_macro("P12_00d17b90")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P12_005feb60")
#undef P12_005feb60
#pragma push_macro("P12_005feb60") /*gvi*/
#undef P12_005feb60 /*gvi*/
int32_t P12_005feb60;
#pragma pop_macro("P12_005feb60") /*gvi*/
#pragma pop_macro("P12_005feb60")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P12_005feef0")
#undef P12_005feef0
#pragma push_macro("P12_005feef0") /*gvi*/
#undef P12_005feef0 /*gvi*/
int32_t P12_005feef0;
#pragma pop_macro("P12_005feef0") /*gvi*/
#pragma pop_macro("P12_005feef0")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P12_005feef4")
#undef P12_005feef4
#pragma push_macro("P12_005feef4") /*gvi*/
#undef P12_005feef4 /*gvi*/
int32_t P12_005feef4;
#pragma pop_macro("P12_005feef4") /*gvi*/
#pragma pop_macro("P12_005feef4")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P12_005feef8")
#undef P12_005feef8
#pragma push_macro("P12_005feef8") /*gvi*/
#undef P12_005feef8 /*gvi*/
int32_t P12_005feef8;
#pragma pop_macro("P12_005feef8") /*gvi*/
#pragma pop_macro("P12_005feef8")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P12_005fee40")
#undef P12_005fee40
#pragma push_macro("P12_005fee40") /*gvi*/
#undef P12_005fee40 /*gvi*/
p12_005fee40_t P12_005fee40;
#pragma pop_macro("P12_005fee40") /*gvi*/
#pragma pop_macro("P12_005fee40")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P12_005fee60")
#undef P12_005fee60
#pragma push_macro("P12_005fee60") /*gvi*/
#undef P12_005fee60 /*gvi*/
p12_005fee60_t P12_005fee60;
#pragma pop_macro("P12_005fee60") /*gvi*/
#pragma pop_macro("P12_005fee60")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P12_01252b74")
#undef P12_01252b74
#pragma push_macro("P12_01252b74") /*gvi*/
#undef P12_01252b74 /*gvi*/
int32_t P12_01252b74;
#pragma pop_macro("P12_01252b74") /*gvi*/
#pragma pop_macro("P12_01252b74")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P12_01252aa0")
#undef P12_01252aa0
#pragma push_macro("P12_01252aa0") /*gvi*/
#undef P12_01252aa0 /*gvi*/
p12_01252aa0_t P12_01252aa0;
#pragma pop_macro("P12_01252aa0") /*gvi*/
#pragma pop_macro("P12_01252aa0")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P12_00cff9ac")
#undef P12_00cff9ac
#pragma push_macro("P12_00cff9ac") /*gvi*/
#undef P12_00cff9ac /*gvi*/
int32_t P12_00cff9ac;
#pragma pop_macro("P12_00cff9ac") /*gvi*/
#pragma pop_macro("P12_00cff9ac")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P12_00b1c3f0")
#undef P12_00b1c3f0
#pragma push_macro("P12_00b1c3f0") /*gvi*/
#undef P12_00b1c3f0 /*gvi*/
int32_t P12_00b1c3f0;
#pragma pop_macro("P12_00b1c3f0") /*gvi*/
#pragma pop_macro("P12_00b1c3f0")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P12_00b1c3dc")
#undef P12_00b1c3dc
#pragma push_macro("P12_00b1c3dc") /*gvi*/
#undef P12_00b1c3dc /*gvi*/
int32_t P12_00b1c3dc;
#pragma pop_macro("P12_00b1c3dc") /*gvi*/
#pragma pop_macro("P12_00b1c3dc")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P12_01146f20")
#undef P12_01146f20
#pragma push_macro("P12_01146f20") /*gvi*/
#undef P12_01146f20 /*gvi*/
p12_01146f20_t P12_01146f20;
#pragma pop_macro("P12_01146f20") /*gvi*/
#pragma pop_macro("P12_01146f20")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P12_00b1c3f4")
#undef P12_00b1c3f4
#pragma push_macro("P12_00b1c3f4") /*gvi*/
#undef P12_00b1c3f4 /*gvi*/
p12_00b1c3f4_t P12_00b1c3f4;
#pragma pop_macro("P12_00b1c3f4") /*gvi*/
#pragma pop_macro("P12_00b1c3f4")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P12_01145a60")
#undef P12_01145a60
#pragma push_macro("P12_01145a60") /*gvi*/
#undef P12_01145a60 /*gvi*/
p12_01145a60_t P12_01145a60;
#pragma pop_macro("P12_01145a60") /*gvi*/
#pragma pop_macro("P12_01145a60")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P12_011237b8")
#undef P12_011237b8
#pragma push_macro("P12_011237b8") /*gvi*/
#undef P12_011237b8 /*gvi*/
int32_t P12_011237b8;
#pragma pop_macro("P12_011237b8") /*gvi*/
#pragma pop_macro("P12_011237b8")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P12_0110b260")
#undef P12_0110b260
#pragma push_macro("P12_0110b260") /*gvi*/
#undef P12_0110b260 /*gvi*/
p12_0110b260_t P12_0110b260;
#pragma pop_macro("P12_0110b260") /*gvi*/
#pragma pop_macro("P12_0110b260")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P12_00574530")
#undef P12_00574530
#pragma push_macro("P12_00574530") /*gvi*/
#undef P12_00574530 /*gvi*/
p12_00574530_t P12_00574530;
#pragma pop_macro("P12_00574530") /*gvi*/
#pragma pop_macro("P12_00574530")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P12_00c7d800")
#undef P12_00c7d800
#pragma push_macro("P12_00c7d800") /*gvi*/
#undef P12_00c7d800 /*gvi*/
p12_00c7d800_t P12_00c7d800;
#pragma pop_macro("P12_00c7d800") /*gvi*/
#pragma pop_macro("P12_00c7d800")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P12_00c7d828")
#undef P12_00c7d828
#pragma push_macro("P12_00c7d828") /*gvi*/
#undef P12_00c7d828 /*gvi*/
int32_t P12_00c7d828;
#pragma pop_macro("P12_00c7d828") /*gvi*/
#pragma pop_macro("P12_00c7d828")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P12_00c7d834")
#undef P12_00c7d834
#pragma push_macro("P12_00c7d834") /*gvi*/
#undef P12_00c7d834 /*gvi*/
int32_t P12_00c7d834;
#pragma pop_macro("P12_00c7d834") /*gvi*/
#pragma pop_macro("P12_00c7d834")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P12_00c7d840")
#undef P12_00c7d840
#pragma push_macro("P12_00c7d840") /*gvi*/
#undef P12_00c7d840 /*gvi*/
int32_t P12_00c7d840;
#pragma pop_macro("P12_00c7d840") /*gvi*/
#pragma pop_macro("P12_00c7d840")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P12_00c7d84c")
#undef P12_00c7d84c
#pragma push_macro("P12_00c7d84c") /*gvi*/
#undef P12_00c7d84c /*gvi*/
int32_t P12_00c7d84c;
#pragma pop_macro("P12_00c7d84c") /*gvi*/
#pragma pop_macro("P12_00c7d84c")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P12_00c595a0")
#undef P12_00c595a0
#pragma push_macro("P12_00c595a0") /*gvi*/
#undef P12_00c595a0 /*gvi*/
int32_t P12_00c595a0;
#pragma pop_macro("P12_00c595a0") /*gvi*/
#pragma pop_macro("P12_00c595a0")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P12_00c55034")
#undef P12_00c55034
#pragma push_macro("P12_00c55034") /*gvi*/
#undef P12_00c55034 /*gvi*/
int32_t P12_00c55034;
#pragma pop_macro("P12_00c55034") /*gvi*/
#pragma pop_macro("P12_00c55034")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P12_00d044d0")
#undef P12_00d044d0
#pragma push_macro("P12_00d044d0") /*gvi*/
#undef P12_00d044d0 /*gvi*/
int32_t P12_00d044d0;
#pragma pop_macro("P12_00d044d0") /*gvi*/
#pragma pop_macro("P12_00d044d0")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P12_00c821a0")
#undef P12_00c821a0
#pragma push_macro("P12_00c821a0") /*gvi*/
#undef P12_00c821a0 /*gvi*/
int32_t P12_00c821a0;
#pragma pop_macro("P12_00c821a0") /*gvi*/
#pragma pop_macro("P12_00c821a0")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P12_00b52a38")
#undef P12_00b52a38
#pragma push_macro("P12_00b52a38") /*gvi*/
#undef P12_00b52a38 /*gvi*/
int32_t P12_00b52a38;
#pragma pop_macro("P12_00b52a38") /*gvi*/
#pragma pop_macro("P12_00b52a38")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P12_00b32970")
#undef P12_00b32970
#pragma push_macro("P12_00b32970") /*gvi*/
#undef P12_00b32970 /*gvi*/
int32_t P12_00b32970;
#pragma pop_macro("P12_00b32970") /*gvi*/
#pragma pop_macro("P12_00b32970")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P12_00b93ce0")
#undef P12_00b93ce0
#pragma push_macro("P12_00b93ce0") /*gvi*/
#undef P12_00b93ce0 /*gvi*/
int32_t P12_00b93ce0;
#pragma pop_macro("P12_00b93ce0") /*gvi*/
#pragma pop_macro("P12_00b93ce0")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P12_00576688")
#undef P12_00576688
#pragma push_macro("P12_00576688") /*gvi*/
#undef P12_00576688 /*gvi*/
p12_00576688_t P12_00576688;
#pragma pop_macro("P12_00576688") /*gvi*/
#pragma pop_macro("P12_00576688")
#endif

#include "memrw.h"

/* Menu action: start mode 0x105 (TODO(RE): unsure which game mode) via 0040C455(1, 0), then return to menu page 00549ae8. */
uint32_t P12_Fn00404F70(void) {
  MenuAction40CD17(); g_00b87e38 = 0x105; g_01271060 = 8;
  UiCall0040C455(1, 0); M12(0x549ae8, 0x549b00); return 0;
}
/* Menu action: play the CREDITS replay sequence (flags set around it); returns 1. */
uint32_t P12_Fn00404FAE(void) {
  MenuAction40CD17(); g_00b87ef8 = 1; g_005f7e5c = 1;
  P138_ReplayCfg("CREDITS"); UiCall0040C455(1, 1);
  g_005f7e5c = 0; g_00b87ef8 = 0; return 1;
}
/* Settings: toggle 00575f50 (TODO(RE): unsure — stereo/3D sound?), reinitialise the sound device and reload the menu sound bank. */
uint32_t P12_Fn004152A7(void) {
  g_00575f50 ^= 1;
  G6Call00523628(); Call00523595();
  Call005233BE(g_00b87e58, g_00b87e5c, g_00575f50);
  if (g_00b87eec == 0) { Call00524496(0x54ded4, 0); Call0052360D(0); }
  else { Call00524496(0x54dec8, 0); Call0052360D(5); }
  Call00414D1F(); return 0;
}
/* Settings: open the key-binding menu for the current input mode (keyboard -> B, joystick -> A). */
int32_t P12_Fn00407563(void) {
  int32_t r;
  if (g_00b87eec == 0) MenuAction40CD17();
  r = (g_0057b72c == 0) ? P139_KeyMenuB() : P139_KeyMenuA();
  if (r == 0 && g_00b87eec == 0) M12(0x549f60, 0x549f78);
  return r;
}
/* Menu actions of one shape: leave the menu, set a variable, run a sub-screen, and return to menu page (A, B) when
   it returns 0.  Each instance below is one Game.exe function (address in its name). */
#define MENUWRAP(NAME, CALLEE, SETV, A, B) \
  int32_t NAME(void) { int32_t r; MenuAction40CD17(); SETV; r = CALLEE(); if (r == 0) M12(A, B); return r; }
MENUWRAP(P12_Fn0040A45B, R12_413D70, g_01271060 = 6, 0x54a818, 0x54a830)
MENUWRAP(P12_Fn0040A4AD, R12_413D70, g_01271060 = 0xb, 0x54a818, 0x54a830)
MENUWRAP(P12_Fn00412A4B, R12_413B00, (void)0, 0x54cb98, 0x54cc50)
MENUWRAP(P12_Fn00412AB9, R12_4134A0, (void)0, 0x54cb98, 0x54cc50)
MENUWRAP(P12_Fn00412B27, R12_413890, (void)0, 0x54cb98, 0x54cc50)
MENUWRAP(P12_Fn00412B95, R12_416390, (void)0, 0x54cb98, 0x54cc50)
MENUWRAP(P12_Fn00412C03, R12_40A540, (void)0, 0x54cb98, 0x54cc50)
MENUWRAP(P12_Fn00412C71, R12_404850, (void)0, 0x54cb98, 0x54cc50)
MENUWRAP(P12_Fn00412CDF, R12_415EC0, (void)0, 0x54cb98, 0x54cc50)
MENUWRAP(P12_Fn00412D4D, R12_413610, (void)0, 0x54cb98, 0x54cc50)
MENUWRAP(P12_Fn00413596, R12_411FD0, (void)0, 0x54d0e0, 0x54d0f8)
MENUWRAP(P12_Fn004136EC, R12_408770, (void)0, 0x54d188, 0x54d1a0)
MENUWRAP(P12_Fn0041373A, R12_414C30, (void)0, 0x54d188, 0x54d1a0)
MENUWRAP(P12_Fn00413788, R12_407160, (void)0, 0x54d188, 0x54d1a0)
MENUWRAP(P12_Fn004137D6, R12_40E870, (void)0, 0x54d188, 0x54d1a0)
MENUWRAP(P12_Fn00413973, R12_4123D0, (void)0, 0x54d278, 0x54d290)
MENUWRAP(P12_Fn00413CBF, R12_40F2D0, (void)0, 0x54d390, 0x54d3a8)

/* Menu action: 00408600(p); p == -1 returns to menu page 0054cb98. */
void P12_Fn004129DF(int32_t p) {
  MenuAction40CD17(); UiCall00408600(p);
  if (p == -1) M12(0x54cb98, 0x54cc50);
}
/* Fade the motel / frontend screen in (target 1.0f) and run frames until the fade ends. */
void P12_Fn004183F7(uint32_t a, uint32_t b) {
  Call004184DE(0x3f800000u);
  while (g_005fea60 != 0) { Call00522323(); Call004E3391(); UiCall004184F5(); Call0041846C(a, b); }
}
/* Fade out (target 0) and run frames until the fade ends. */
void P12_Fn00418433(uint32_t a, uint32_t b) {
  Call004184DE(0);
  while (g_005fea60 != 0) { Call00522323(); Call004E3391(); UiCall004184F5(); Call0041846C(a, b); }
}
/* Advances one of two fade timers (replay / live) by a step; wraps to -1 at the end value. */
void P12_Fn0050229C(void) {
  if (g_00b5a778 == 0) {
    g_00b32980 = g_00b32980 + g_00546054;
    if (g_00546020 <= g_00b32980) g_00b32980 = -1.0f;
  } else {
    g_00b3297c = g_00b3297c + g_00546054;
    if (g_00546020 <= g_00b3297c) g_00b3297c = -1.0f;
  }
}
#ifndef RE_HOOK_BUILD
int32_t re_oow_n = 0xdbba;
/* native: 1/z for integer depth i — table P12_Fn00526427 below, extended past it (draw_distance > 1). */
float re_oow_get(int32_t i) {
  if (i >= 0 && i < 0xdbba) return g_00ba53a0[i];
  return re_dd_oow(g_0125f3e0, i);       /* v2.19: продолжение таблицы (как в 00526427: k / z); z < 0 — 0 */
}
#endif
/* Fills the 1/z table: entry i = k / i (k = g_0125f3e0), entry 0 = 0. */
void P12_Fn00526427(void) {
  for (int32_t i = 0; i < 0xdbba; i++) {
    if (i == 0) g_00ba53a0[0] = 0;
    else g_00ba53a0[i] = g_0125f3e0 / (float)i;
  }
}
/* Ends all pending traffic turn events (see P104_TrafficTurn) and clears their state. */
void P12_Fn00496505(void) {
  for (int32_t i = 0; i < g_01144284; i++) Call00493ECE((int32_t)g_01144340[i]);
  g_01145934 = 0; g_011426f8 = -1; g_01144284 = 0; g_0113a6c0 = 0;
}
/* Static-object collisions for every active traffic car that is moving (state byte 2 == 1) or has a car slot. */
void P12_Fn00491360(void) {
  for (int32_t i = 0; i < 0x40; i++) {
    const uint8_t *p = &g_011443e0[i * 0x54];
    if (p[1] != 0 && (p[2] == 1 || p[5] != 0)) P129_CarObjects(p[0] + 1);
  }
}
/* For each of the 8 car slots that is active and flagged, re-initialises the nearby-traffic data of its car. */
void P12_Fn0048EBC8(void) {
  for (int32_t i = 0; i < 8; i++) {
    const uint32_t *p = &g_0112da00[i * 0x336];
    if (p[0x32d] != 0 && p[0x333] != 0 && p[0x331] == 0) {
      /* +0xcd0 stores a Game.exe car address, not a native pointer. */
      uint8_t *car = (uint8_t *)re_ptr(p[0x334]);
      if (car != NULL) P71_InitNear(car);
    }
  }
}
/* v1.48: исправлено — шаг записи частицы 0xb4 (флаги +0xc — uint32), прежде брался шаг 0x5a; освобождение — P43_FreeSlot */
void P12_Fn00511FB8(void) {
  for (int32_t i = 0; i < 0x40; i++)
    if ((g_00c5678c[i * 0x2d] & 0x10) != 0)
      P43_FreeSlot((uint8_t *)A_00C56780 + g_00c594a0[i] * 0xb4);
}
/* Clears the key-repeat history and three input buffers. */
void P12_Fn005229F0(void) {
  g_00bdf980 = 0; g_00bde728 = 0; g_00bde764 = 0; g_00bde760 = 0;
  Call0048DB65(0x00bde740, 0x20); Call0048DB65(0x00bde680, 0xa8); Call0048DB65(0x00bde780, 0x1200);
}
/* Snapshots the car records (0x148) and three 0x34-byte traffic tables for the replay, then 005186CE. */
void P12_Fn005188EC(void) {
  Call005283B5(0x00c54d20, 0x00d077c0, 0x148);
  Call005283B5(0x00c4da60, 0x00d06a20, 0x34);
  Call005283B5(0x00c4da00, 0x00d0de00, 0x34);
  Call005283B5(0x00c4d9c0, 0x00d0eb80, 0x34);
  g_00b5a898 = 0; Call005186CE();
}
/* First key (DirectInput scan code) that is bindable (table 0054b010) and currently down, else 0. */
uint32_t P12_Fn0040F09C(void) {
  for (uint32_t i = 0; i < 0x100; i++)
    if (g_0054b010[i] != 0 && IsKeyDown((int)(i & 0xff)) != 0) return i;
  return 0;
}
/* Load-game menu: loads the selected slot if it is used (1 on success), else plays the error sound. */
uint32_t P12_Fn004120AF(void) {
  if (g_005fe7a8[g_005fe84c] != 0) {
    if (R12_405CB4(g_005fe84c) != 0) { UiCall0040C480(1); return 1; }
    Call004122C4();
  }
  return 0;
}
/* Load-replay menu: loads the selected replay and starts it (1), else plays the error sound. */
uint32_t P12_Fn004124AF(void) {
  if (g_005fe884[g_005fe928] != 0) {
    if (R12_405F2E(g_005fe928) != 0) {
      MenuAction40CD17(); g_00d17b90 = 1; UiCall0040C455(1, 1); g_00d17b90 = 0; return 1;
    }
    Call004126DF();
  }
  return 0;
}
/* Shows the BMP named at Game.exe address a and waits for a key, or until b ticks passed. */
void P12_Fn0040C813(uint32_t a, int32_t b) {
  P124_ShowBmp((const char *)re_ptr(a), 0);
  while (R12_4D97E9() != 0) {}
  Call004086B4();
  do { if (b <= g_005d577c) break; } while (R12_4D97E9() == 0);
  Call004086EA(); Call004D78F3(0); g_005f7e60 = 1;
}
/* Uploads a 640x480 image as 3 x 2 texture tiles of 256 x 256. */
void P12_Fn0040DA56(uint32_t a) {
  int32_t n = 0;
  P40_ResetTexMem();
  for (int32_t y = 0; y < 0x1e0; y += 0x100)
    for (int32_t x = 0; x < 0x280; x += 0x100) {
      uint32_t v = R12_40DAE1(a, x, y);
      P40_UploadSlot(n, (int32_t)v); n++;
    }
}
/* Advances the motel camera route by one node when the current spline segment is done; finishes at the last node. */
void P12_Fn0041A8CD(void) {
  if (g_005fea98 == rd32(&g_005febbc[(g_005feb60 + 1) * 0x34]) &&
      (g_005feb60 = g_005feb60 + 1, g_005feb60 == g_005feb48 - 1)) {
    P118_CamRoute((uint32_t)g_005feb00); g_005fea54 = 0; g_005feda0 = 0;
  } else {
    P98_CamSpline(g_005fea98, &P118_Route[(uint32_t)g_005feb60 * 0x34]);   /* v1.63: в прежнем переносе шаг ошибочно 0xd байт */
  }
}
/* Save-game menu: starts editing the name of the selected slot (cursor at its end). */
uint32_t P12_Fn0041AECF(void) {
  UiCall0041AF29(g_005feeec * 2 + 1);
  g_005feef0 = 1;
  if (g_005fee40[g_005feeec] == 0) g_005feef8 = 0;
  else g_005feef8 = (int32_t)strlen((const char *)&g_005fee60[g_005feeec * 0x11]);
  return 0;
}
/* Save-game menu: ends name editing and saves the game to the selected slot. */
void P12_Fn0041AF85(void) {
  g_005feef0 = 0; g_005feef4 = 0; g_005feef8 = 0;
  P140_SaveGame(g_005feeec, (const char *)P12_005fee60 + g_005feeec * 0x11);
  Call0041AFCA();
}
/* Selects palette p for 8-bit textures (uploads it if not current; -1 = none); returns the previous one. */
int32_t P12_Fn00426580(int32_t p) {
  int32_t old = g_01252b74;
  if (p == -1) g_01252b74 = -1;
  else if (p != g_01252b74 && g_01252aa0[p] != 0) {
    Call00424921(0, 2, 0x01252be0u + (uint32_t)p * 0x400, p);
    g_01252b74 = p;
  }
  return old;
}
/* Fade-in step of the 1/z scale g_0125f3e0 (snaps to 1.0 near the end) and refreshes the table. */
void P12_Fn00425EE0(void) {
  if (g_0125f3e0 < g_00546020) {
    g_0125f3e0 = g_0125f3e0 + g_00546054;
    if (g_00546088 < g_0125f3e0 && g_0125f3e0 < g_00546084) g_0125f3e0 = 1.0f;
    Call00425B12(0, 0, 1);
    g_01270c38 = 2;
  }
}
/* When the texture set changed, marks all palette slots dirty and reloads the textures that need it. */
void P12_Fn00489ED6(void) {
  if (g_00cff9ac != g_00b1c3f0) {
    g_00b1c3dc = 0;
    for (int32_t i = 0; i < 0x40; i++) g_01146f20[i * 0x1c] &= 0xfd;
    Call0048A525(g_00cff9ac);
    if (g_00b1c3dc != 0) P12_Fn0048A627();
  }
  g_00b1c3f0 = g_00cff9ac;
}
/* Reloads the queued texture pages and clears the queue. */
void P12_Fn0048A627(void) {
  for (int32_t i = 0; i < g_00b1c3dc; i++) {
    int32_t k = g_00b1c3f4[i];
    g_01145a60[k * 0x10] &= 0xef;
    Call0048A68E(k);
  }
  g_00b1c3dc = 0;
}
/* Re-uploads texture page p from data address v (see P104_CarDents). */
void P12_Fn0048A46B(int32_t p, int32_t v) {
  if (g_01145a60[p * 0x10 + 1] != 0xff) {
    uint32_t u = g_01145a60[p * 0x10 + 1];
    wr32(&g_01145a60[p * 0x10 + 4], v);
    wr32(&g_01146f20[u * 0x1c + 0x18], v);
    Call004248C6(0, rd32(&g_01146f20[u * 0x1c + 4]), 3, 0x01146f28u + u * 0x1c, p);
  }
}
/* Debris pass: 004B998B for each of the 200 debris records with flag 0x2, when debris is active. */
void P12_Fn004B9933(void) {
  if (g_011173c8 != 0) {
    for (int32_t i = 0; i < 200; i++) {
      uint16_t f; memcpy(&f, &g_0110b260[i * 0x3c + 0x22], 2);
      if ((f & 2) != 0) Call004B998B(0x0110b260u + (uint32_t)i * 0x3c);
    }
  }
}
/* Per-tick effects update (not during replays): particles, debris, every other tick the effect lists; 16-step counter. */
void P12_Fn004AAE34(void) {
  if (g_00b5a778 == 0) {
    if (g_00553850 != 0) Call004C0C6F(0);
    if ((g_00d118c0 & 1) == 0) {
      g_00bdc28c = 0x011effa0;
      Call004BA31B(); Call004B9AEC(); Call004B9D79(); P12_Fn004B9933();
      g_011237b8 = (g_011237b8 + 1) & 0xf;
      Call004911D9();
    }
  }
}
/* Pause handling: toggles between paused and running when the pause request changed. */
void P12_Fn0050E963(void) {
  if (g_00b5a76c == 0) {
    if (g_00b5a778 != 0 || g_00b5a770 != 0) Call0050F289();
  } else if (g_00b5a778 == 0 || g_00b5a770 != 0) P127_Pause();
  g_00b5a770 = 0;
}
/* Initialises the radar grid neighbour offsets (8 directions, 55 cells per row) and its list heads. */
void P12_Fn0050C010(void) {
  for (int32_t i = 0; i < 8; i++) g_00c7d800[i] = g_00574530[i * 2] + g_00574530[i * 2 + 1] * 0x37;
  g_00c7d828 = 0x00c7d82c; g_00c7d834 = 0x00c7d838; g_00c7d840 = 0x00c7d844;
  g_00c7d84c = 0; g_00c595a0 = 0;
}
/* Loads the FONT and BIG fonts. */
void P12_Fn00516E76(void) {
  g_00c55034 = R12_40A8B0(re_addr("FONT"), 0, -1, 5, 0x18)   /* .data 00575a28 "FONT" */;
  R12_40A8B0(re_addr("BIG"), 1, -1, 5, 0x18)      /* .data 00575a30 "BIG" */;
  CopySlots_0040AA82(1);
}
/* Re-syncs the body state of the current player car record (004DAA36). */
void P12_Fn004DC8EA(void) {
  Call004DAA36(0x00d077c0u + (uint32_t)g_00d11878 * 0x52, 0x00d077d8u + (uint32_t)g_00d11878 * 0x52);
}
/* Shows HUD message string a for b ticks (c != 0: only if no message is showing). */
void P12_Fn004E5982(int32_t a, int32_t b, int32_t c) {
  if (c == 0 || g_00d044d0 == 0) { Call0052A910(0x00d04680, g_00c55820[a], 0); g_00d044d0 = b; }
}
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P12_PartLerp")
#undef P12_PartLerp
#pragma push_macro("P12_PartLerp") /*gvi*/
#undef P12_PartLerp /*gvi*/
p12_lerp_t P12_PartLerp;
#pragma pop_macro("P12_PartLerp") /*gvi*/
#pragma pop_macro("P12_PartLerp")
#endif
/* Interpolates the per-part records (0x14 bytes, 4 floats after a 0x10 header) of a and b at t into P12_PartLerp. */
void P12_Fn004F3E78(const float *a, const float *b, float t) {
  const uint8_t *pa = (const uint8_t *)a + 0x10, *pb = (const uint8_t *)b + 0x10;
  int32_t n = g_00c821a0;
#ifndef RE_HOOK_BUILD
  if (a == NULL || b == NULL) return;
  if (n > (int32_t)(sizeof(p12_lerp_t) / 0x14)) n = (int32_t)(sizeof(p12_lerp_t) / 0x14);
#endif
  for (int32_t i = 0; i < n; i++) {
    Lerp4_00527885((const float *)pa, (const float *)pb, t, (float *)((uint8_t *)P12_PartLerp + i * 0x14));
    pa += 0x14; pb += 0x14;
  }
}
/* Copies 128 rows of 0x100 bytes from a to b with the two buffers' pitches. */
void P12_Fn00504699(int32_t a, int32_t b) {
  for (int32_t i = 0; i < 0x80; i++) {
    Call005283B5((uint32_t)b, a, 0x100);
    a = a + 0x100 + g_00b52a38 * 2; b = b + 0x100 + g_00b32970 * 2;
  }
}
/* Plays one-shot speech/sample p of table 00576688 at most every 500 frames, adding its score value. */
void P12_Fn00525CB7(int32_t p) {
  if (g_00b93ce0 != p && 500 < g_00d118c0 - g_00576688[p * 3 + 1]) {
    Call004D6190(g_00576688[p * 3] + 0xf000);
    g_00576688[p * 3 + 1] = g_00d118c0;
    g_00c808d0 = g_00c808d0 + (float)g_00576688[p * 3 + 2];
    g_00b93ce0 = p;
  }
}
