/* ported35.c — force feedback (Input.c) and DirectDraw creation (Render.c) (English overview; original
   notes follow).  Thin logic over plat_di_*_effect / plat_dd_create.  P35_DamageRumble is native only. */
/* Force Feedback и создание DirectDraw — восстановлено из Game.exe (Input.c, Render.c). */
#include "ported35.h"
#include "noop.h"
#include <math.h>
#ifndef RE_HOOK_BUILD
#include "ported36.h"
#include "cartab.h"
/* P35_DamageRumble — native only, no Game.exe address.  Forwards a damage hit on the player's car (record 0,
   or 0x41 when 00b87eac is set) to gamepad rumble, while the window is active, not in a replay/demo
   (00b87efc, 00b87ea0) and not on keyboard (P36_PadMode 2). */
void P35_DamageRumble(const unsigned char *car, int damage) {
  int player = G6_00B87EAC != 0 ? 0x41 : 0;
  if (car == (const unsigned char *)&P99_Cars[player] && P31_Active != 0 &&
      G6_00B87EFC == 0 && G6_00B87EA0 == 0 && P36_PadMode != 2)
    plat_gamepad_damage(damage);
}
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P35_PadX")
#undef P35_PadX
#pragma push_macro("P35_PadX") /*gvi*/
#undef P35_PadX /*gvi*/
int32_t P35_PadX;
#pragma pop_macro("P35_PadX") /*gvi*/
#pragma pop_macro("P35_PadX")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P35_FfX")
#undef P35_FfX
#pragma push_macro("P35_FfX") /*gvi*/
#undef P35_FfX /*gvi*/
int32_t P35_FfX;
#pragma pop_macro("P35_FfX") /*gvi*/
#pragma pop_macro("P35_FfX")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P35_FfY")
#undef P35_FfY
#pragma push_macro("P35_FfY") /*gvi*/
#undef P35_FfY /*gvi*/
int32_t P35_FfY;
#pragma pop_macro("P35_FfY") /*gvi*/
#pragma pop_macro("P35_FfY")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P35_FfPending")
#undef P35_FfPending
#pragma push_macro("P35_FfPending") /*gvi*/
#undef P35_FfPending /*gvi*/
int32_t P35_FfPending;
#pragma pop_macro("P35_FfPending") /*gvi*/
#pragma pop_macro("P35_FfPending")
#endif
#ifdef RE_HOOK_BUILD
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P35_ReqBpp")
#undef P35_ReqBpp
#pragma push_macro("P35_ReqBpp") /*gvi*/
#undef P35_ReqBpp /*gvi*/
int32_t P35_ReqBpp;
#pragma pop_macro("P35_ReqBpp") /*gvi*/
#pragma pop_macro("P35_ReqBpp")
#endif
#else
#pragma push_macro("P35_ReqBpp") /*gvi*/
#undef P35_ReqBpp /*gvi*/
int32_t P35_ReqBpp = 0x10;   /* v2.00: начальное значение .data 00549ccc = 16 (в native GAME_VAR_DEF без инициализатора давал 0) */
#pragma pop_macro("P35_ReqBpp") /*gvi*/
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P35_InputMode")
#undef P35_InputMode
#pragma push_macro("P35_InputMode") /*gvi*/
#undef P35_InputMode /*gvi*/
uint8_t P35_InputMode;
#pragma pop_macro("P35_InputMode") /*gvi*/
#pragma pop_macro("P35_InputMode")
#endif

/* GUID_ConstantForce {13541C20-8E33-11D0-9AD0-00A0C9A06E35} — данные игры по 00546510 */
static const uint8_t k_constant_force[16] = { 0x20,0x1c,0x54,0x13,0x33,0x8e,0xd0,0x11,0x9a,0xd0,0x00,0xa0,0xc9,0xa0,0x6e,0x35 };

/* P35_CreateEffectA — Game.exe 004e41d5.  Creates the "hit" effect (constant force, GUID at 00546510) in
   P34_EffA[slot] unless one exists already.  Returns 1 on success, 0 on failure. */
int32_t P35_CreateEffectA(void *dev, int32_t slot) {
  if (P34_FfA == NULL) {
    if (plat_di_create_effect(dev, 0, k_constant_force, &P34_EffA[slot]) != 0) return 0;
  }
  return 1;
}

/* P35_CreateEffectB — Game.exe 004e429b.  Enumerates the device's constant-force effect and creates the
   "engine" effect in P34_EffB[slot] unless one exists.  Returns 1 / 0. */
int32_t P35_CreateEffectB(void *dev, int32_t slot) {
  if (P34_FfB == NULL) {
    uint8_t guid[16];
    if (plat_di_enum_effect(dev, guid) != 0) return 0;
    if (plat_di_create_effect(dev, 1, guid, &P34_EffB[slot]) != 0) return 0;
  }
  return 1;
}

/* P35_UpdateForce — Game.exe 004e3b3c.  Sends pending forces: a pad hit (P35_PadX) is latched into the
   force vector; with force feedback on (00b87ef0) and a joystick (input mode 2) the hit effect gets direction
   (FfX, FfY) and magnitude sqrt(FfX^2 + FfY^2) (truncated like __ftol), and the engine effect gets level
   00b31e00 when 00b31e0c flags a change.  Clears the pending state. */
void P35_UpdateForce(void) {
  if (P35_PadX != 0 && P16_FlagA == 0) {
    P35_FfX = P35_PadX;
    P35_FfPending = 1;
  }
  if (Q00B87EF0 != 0 && P35_InputMode == 2) {
    if (P34_FfA != NULL && P35_FfPending != 0) {
      uint32_t len_sq = (uint32_t)P35_FfX * (uint32_t)P35_FfX + (uint32_t)P35_FfY * (uint32_t)P35_FfY;
      int32_t magnitude = (int32_t)sqrt((double)(int32_t)len_sq);   /* __ftol: усечение */
      plat_di_set_effect(P34_FfA, 0, P35_FfX, P35_FfY, magnitude);
      P35_FfPending = 0; P35_FfX = 0; P35_FfY = 0;
    }
    if (P34_FfB != NULL && G00B31E0C != 0) {
      plat_di_set_effect(P34_FfB, 1, 0, 0, G00B31E00);
      G00B31E0C = 0;
    }
  }
}

/* P35_GetDirectDrawInterface — Game.exe 00420b19.  DirectDrawCreate for `guid`, stores the object in
   P31_DDObj0, and checks the desktop is an RGB mode (DDPF_RGB 0x40) and that the requested depth
   (00549ccc) is 16 or 32 bits; otherwise shows "please switch to a 16/32bit display mode".
   Returns the object, or NULL on failure.  Side effect: P24_Bpp = requested depth. */
void *P35_GetDirectDrawInterface(const void *guid) {
  NoopFn0042243f();   /* лог «GetDirectDrawInterface()» (в релизе — пусто) */
  void *dd = plat_dd_create(guid);
  if (dd != NULL) P31_DDObj0 = dd;
  if (dd == NULL) { NoopFn0042243f(); return NULL; }
  uint32_t pixfmt_flags = 0;
  if (plat_dd_get_display_flags(dd, &pixfmt_flags) != 0) { NoopFn0042243f(); return NULL; }
  if ((pixfmt_flags & 0x40) == 0) {   /* DDPF_RGB */
    plat_message_box(P24_Hwnd, "To run, please switch to a\n16/32bit display mode.", "Sorry!", 0x10);
    return NULL;
  }
  P24_Bpp = P35_ReqBpp;
  if (P35_ReqBpp != 0x10 && P35_ReqBpp != 0x20) {
    plat_message_box(P24_Hwnd, "To run, please switch to a\n16/32bit display mode.", "Sorry!", 0x10);
    return NULL;
  }
  return dd;
}
