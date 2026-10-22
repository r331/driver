#include "ported150.h"
#include "ported139.h"
#include "ported115.h"
#include "ported52.h"
#include "ported135.h"
#include "ported33.h"
#include "ported50.h"
#include <string.h>
#ifdef RE_HOOK_BUILD
#  define P52_STD __attribute__((stdcall))
#else
#  define P52_STD
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P52_FogOn")
#undef P52_FogOn
#pragma push_macro("P52_FogOn") /*gvi*/
#undef P52_FogOn /*gvi*/
int32_t P52_FogOn;
#pragma pop_macro("P52_FogOn") /*gvi*/
#pragma pop_macro("P52_FogOn")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P52_NoTrail")
#undef P52_NoTrail
#pragma push_macro("P52_NoTrail") /*gvi*/
#undef P52_NoTrail /*gvi*/
uint8_t P52_NoTrail;
#pragma pop_macro("P52_NoTrail") /*gvi*/
#pragma pop_macro("P52_NoTrail")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P52_MenuCnt")
#undef P52_MenuCnt
#pragma push_macro("P52_MenuCnt") /*gvi*/
#undef P52_MenuCnt /*gvi*/
int32_t P52_MenuCnt;
#pragma pop_macro("P52_MenuCnt") /*gvi*/
#pragma pop_macro("P52_MenuCnt")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P52_MenuA")
#undef P52_MenuA
#pragma push_macro("P52_MenuA") /*gvi*/
#undef P52_MenuA /*gvi*/
int32_t P52_MenuA;
#pragma pop_macro("P52_MenuA") /*gvi*/
#pragma pop_macro("P52_MenuA")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P52_MenuB")
#undef P52_MenuB
#pragma push_macro("P52_MenuB") /*gvi*/
#undef P52_MenuB /*gvi*/
int32_t P52_MenuB;
#pragma pop_macro("P52_MenuB") /*gvi*/
#pragma pop_macro("P52_MenuB")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P52_MenuC")
#undef P52_MenuC
#pragma push_macro("P52_MenuC") /*gvi*/
#undef P52_MenuC /*gvi*/
int32_t P52_MenuC;
#pragma pop_macro("P52_MenuC") /*gvi*/
#pragma pop_macro("P52_MenuC")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P52_ResetA")
#undef P52_ResetA
#pragma push_macro("P52_ResetA") /*gvi*/
#undef P52_ResetA /*gvi*/
int32_t P52_ResetA;
#pragma pop_macro("P52_ResetA") /*gvi*/
#pragma pop_macro("P52_ResetA")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P52_ResetB")
#undef P52_ResetB
#pragma push_macro("P52_ResetB") /*gvi*/
#undef P52_ResetB /*gvi*/
uint8_t P52_ResetB;
#pragma pop_macro("P52_ResetB") /*gvi*/
#pragma pop_macro("P52_ResetB")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P52_ResetC")
#undef P52_ResetC
#pragma push_macro("P52_ResetC") /*gvi*/
#undef P52_ResetC /*gvi*/
int32_t P52_ResetC;
#pragma pop_macro("P52_ResetC") /*gvi*/
#pragma pop_macro("P52_ResetC")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P52_Ones0")
#undef P52_Ones0
#pragma push_macro("P52_Ones0") /*gvi*/
#undef P52_Ones0 /*gvi*/
int32_t P52_Ones0;
#pragma pop_macro("P52_Ones0") /*gvi*/
#pragma pop_macro("P52_Ones0")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P52_Ones1")
#undef P52_Ones1
#pragma push_macro("P52_Ones1") /*gvi*/
#undef P52_Ones1 /*gvi*/
int32_t P52_Ones1;
#pragma pop_macro("P52_Ones1") /*gvi*/
#pragma pop_macro("P52_Ones1")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P52_Ones2")
#undef P52_Ones2
#pragma push_macro("P52_Ones2") /*gvi*/
#undef P52_Ones2 /*gvi*/
int32_t P52_Ones2;
#pragma pop_macro("P52_Ones2") /*gvi*/
#pragma pop_macro("P52_Ones2")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P52_Ones3")
#undef P52_Ones3
#pragma push_macro("P52_Ones3") /*gvi*/
#undef P52_Ones3 /*gvi*/
int32_t P52_Ones3;
#pragma pop_macro("P52_Ones3") /*gvi*/
#pragma pop_macro("P52_Ones3")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P52_FogTab")
#undef P52_FogTab
#pragma push_macro("P52_FogTab") /*gvi*/
#undef P52_FogTab /*gvi*/
p52_fog_t P52_FogTab;
#pragma pop_macro("P52_FogTab") /*gvi*/
#pragma pop_macro("P52_FogTab")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P52_NameTab")
#undef P52_NameTab
#pragma push_macro("P52_NameTab") /*gvi*/
#undef P52_NameTab /*gvi*/
p52_names_t P52_NameTab;
#pragma pop_macro("P52_NameTab") /*gvi*/
#pragma pop_macro("P52_NameTab")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P52_ColorTab")
#undef P52_ColorTab
#pragma push_macro("P52_ColorTab") /*gvi*/
#undef P52_ColorTab /*gvi*/
p52_colors_t P52_ColorTab;
#pragma pop_macro("P52_ColorTab") /*gvi*/
#pragma pop_macro("P52_ColorTab")
#endif

/* ported52.c — small functions: Glide 3dfx wrappers (fog table / fog mode / mipmap download, resolved by
   name from the Glide export list P33_*), the frame-step debug toggle, slot-table reset, the HUD
   dispatcher for interview / mode 5, FMV start, a coloured menu label and a menu record reload.
   All cdecl; Glide entry points are stdcall (P52_STD). */

#define GLIDE_FOG_COLOR_GREY  0xaaaaaau   /* fog colour when fog is off or already initialised */
#define GLIDE_CLEAR_DEPTH     0xffff      /* grBufferClear depth value: clear depth to the far plane */
#define GR_FOGMODE_DISABLE    0
#define GR_FOGMODE_WITH_TABLE 2           /* GR_FOG_WITH_TABLE_ON_Q in Glide 3 headers */
#define MODE_INTERVIEW        4           /* D_00b87e30 values */
#define MODE_5                5           /* TODO(RE): unsure which game mode 5 is (ghost trail shown) */

/* Address of a Glide export by its decorated name, or NULL (native: no Glide, so always NULL). */
static void *glide_proc(const char *name) {
  for (int i = 0; i < P33_GlideCount(); i++)
    if (strcmp(P33_GlideName(i), name) == 0) return P33_GlideProc(i);
  return NULL;
}
/* Float from its IEEE bit pattern (literal constants copied from the original's immediates). */
static float bits_f(uint32_t u) { float f; memcpy(&f, &u, 4); return f; }

/* P52_GlideFogSetup — Game.exe 0042626e.  Builds the Glide exponential fog table P52_FogTab (64 entries)
   and installs it.  Fog off (P52_FogOn == 0) or already set up (P26_FxD != 0): grey fog colour, density
   1.2e-4 (bits 0x38fba882).  Otherwise: black fog, density 1.0e-4 (0x38d1b717), and P26_FxD = 1.
   TODO(RE): unsure about the meaning of P26_FxD beyond "fog initialised". */
void P52_GlideFogSetup(void) {
  void (P52_STD *fogcolor)(uint32_t) = (void (P52_STD *)(uint32_t))glide_proc("_grFogColorValue@4");
  void (P52_STD *genexp)(void *, float) = (void (P52_STD *)(void *, float))glide_proc("_guFogGenerateExp@8");
  void (P52_STD *fogtable)(void *) = (void (P52_STD *)(void *))glide_proc("_grFogTable@4");
  if (P52_FogOn == 0 || P26_FxD != 0) {
    if (fogcolor) fogcolor(GLIDE_FOG_COLOR_GREY);
    if (genexp) genexp(&P52_FogTab, bits_f(0x38fba882u));
  } else {
    if (fogcolor) fogcolor(0);
    if (genexp) genexp(&P52_FogTab, bits_f(0x38d1b717u));
    P26_FxD = 1;
  }
  if (fogtable) fogtable(&P52_FogTab);
}

/* P52_GlideFogMode — Game.exe 004264bd.  Sets the Glide fog mode (table fog when P26_FxD != 0, else
   off), then clears the depth buffer; unless P52_NoTrail is set, colour writes are masked off around the
   clear so the colour buffer keeps the last frame. */
void P52_GlideFogMode(void) {
  void (P52_STD *fogmode)(int32_t) = (void (P52_STD *)(int32_t))glide_proc("_grFogMode@4");
  void (P52_STD *colormask)(int32_t, int32_t) = (void (P52_STD *)(int32_t, int32_t))glide_proc("_grColorMask@8");
  void (P52_STD *clear)(int32_t, int32_t, int32_t) = (void (P52_STD *)(int32_t, int32_t, int32_t))glide_proc("_grBufferClear@12");
  if (fogmode) fogmode(P26_FxD == 0 ? GR_FOGMODE_DISABLE : GR_FOGMODE_WITH_TABLE);
  if (P52_NoTrail == 0 && colormask) colormask(0, 0);
  if (clear) clear(0, 0, GLIDE_CLEAR_DEPTH);   /* colour 0, alpha 0, depth 0xffff */
  if (P52_NoTrail == 0 && colormask) colormask(1, 0);
}

/* P52_TexDownloadMipMap — Game.exe 0042486b.  Texture download through the active 3D API: nothing unless
   D_00b1c0d4 (TODO(RE): unsure — "3D card present"); D_00b1c0d8 == 0 -> grTexDownloadMipMap(a, b, c, d)
   (Glide), == 1 -> P52_Fn41D53C(a..e) (TODO(RE): unsure — the Direct3D path). */
void P52_TexDownloadMipMap(int32_t a, int32_t b, int32_t c, int32_t d, int32_t e) {
  if (D_00b1c0d4 == 0) return;
  if (D_00b1c0d8 == 0) {
    void (P52_STD *f)(int32_t, int32_t, int32_t, int32_t) = (void (P52_STD *)(int32_t, int32_t, int32_t, int32_t))glide_proc("_grTexDownloadMipMap@16");
    if (f) f(a, b, c, d);
  } else if (D_00b1c0d8 == 1) {
    P52_Fn41D53C(a, b, c, d, e);
  }
}

/* P52_MenuStepToggle — Game.exe 00510084.  Cycles the frame-step state P21_FrameFlagB / FlagA / FrameMin
   on each call: off -> on with FrameMin 1 -> FrameMin 2..5 -> FlagA = 1 -> off.  Then sets
   MenuVar575EF8 = 4 and refreshes the menu (Call0050FBF4).  TODO(RE): unsure what the frame flags
   control (a frame-rate limiter option?). */
void P52_MenuStepToggle(void) {
  if (P21_FrameFlagB == 0) {
    P21_FrameFlagB = 1; P21_FrameFlagA = 0; P21_FrameMin = 1;
  } else if (P21_FrameFlagA == 1) {
    P21_FrameFlagA = 0; P21_FrameFlagB = 0;
  } else if (P21_FrameMin == 5) {
    P21_FrameFlagA = 1;
  } else {
    P21_FrameMin = P21_FrameMin + 1;
  }
  MenuVar575EF8 = 4;
  Call0050FBF4();
}

/* P52_HudDispatch — Game.exe 004e59b9.  Per-frame extra HUD by game mode: interview (4) — ghost trail
   when P11_00b87e38 == 0xc9, the interview HUD (P52_Fn4E5A1A + paper bars P115_PaperHud) and, when
   P12_00d044d0 is set, the text line at 00d04680; mode 5 — ghost trail if G6_00B87EA0.  The second
   D_00b87e30 == 4 test is redundant but kept (it is in the original). */
void P52_HudDispatch(void) {
  if (D_00b87e30 == MODE_INTERVIEW) {
    if (P11_00b87e38 == 0xc9) P135_GhostTrail();
    if (D_00b87e30 == MODE_INTERVIEW) { P52_Fn4E5A1A(); P115_PaperHud(); }
    if (P12_00d044d0 != 0) DrawTextLine004FBBC5(0x00d04680);
  } else if (D_00b87e30 == MODE_5 && G6_00B87EA0 != 0) {
    P135_GhostTrail();
  }
}

/* P52_ResetSlots — Game.exe 004aad65.  Clears three counters, runs the table-reset routines of the
   004ab0df..004aba7c group and P12_Fn005229F0 in the original order, then sets four flags to 1.
   TODO(RE): unsure what the reset tables hold (called at level start). */
void P52_ResetSlots(void) {
  P52_ResetA = 0; P52_ResetB = 0; P52_ResetC = 0;
  P52_Fn4ABD69();
  InitSlotsTable_004AB0DF();
  P52_Fn4AB127();
  P52_Fn4AB500();
  ResetSlots_004AB712();
  Clear110E180();
  P52_Fn4AB808();
  P52_Fn4AB95C();
  P12_Fn005229F0();
  P52_Fn4ABA7C();
  P52_Ones0 = 1; P52_Ones1 = 1; P52_Ones2 = 1; P52_Ones3 = 1;
}

/* P52_FmvStart — Game.exe 0048abdc.  Stops any FMV (P50_FmvStopRelease), opens the movie
   file a (P150_OpenAudio) and starts it (P52_Fn48B5E3).  Returns 1 on success; on failure stops again
   and returns 0. */
int32_t P52_FmvStart(const char *a) {
  P50_FmvStopRelease();
  if (P150_OpenAudio(a) != 0 && P52_Fn48B5E3() != 0) return 1;
  P50_FmvStopRelease();
  return 0;
}

/* P52_DrawLabel — Game.exe 004a9e0a.  Draws menu text a at x = 480.0, y = b in colour c (RGB from
   P52_ColorTab, 4 bytes per colour), unless b is above the top limit 0x60 - ScanSlot_0040AAE2(0).
   P52_Fn5173D7 is P73_Text. */
void P52_DrawLabel(int32_t a, int32_t b, int32_t c) {
  int32_t top = 0x60 - (int32_t)ScanSlot_0040AAE2(0);
  if (b < top) return;
  SetRGB00516EB4(P52_ColorTab[c * 4], P52_ColorTab[c * 4 + 1], P52_ColorTab[c * 4 + 2]);
  P52_Fn5173D7(bits_f(0x43f00000u), (float)b, a, 0, 1);
}

/* P52_MenuReload — Game.exe 00510728.  Clears three menu counters, ends a running replay when GameMode
   is 0, reloads menu record P52_MenuCnt (name table P52_NameTab, 0x11 bytes per entry; on failure
   GlobalSet00511378) and calls Call00510784. */
void P52_MenuReload(void) {
  P52_MenuA = 0; P52_MenuB = 0; P52_MenuC = 0;
  if (GameMode == 0) P139_ReplayEnd();
  if (P52_Fn405F6F(P52_MenuCnt, (uint8_t *)P52_NameTab + P52_MenuCnt * 0x11) == 0) GlobalSet00511378();
  Call00510784();
}
