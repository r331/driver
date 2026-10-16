#include "ported150.h"
#include "ported139.h"
#include "ported115.h"
#include "ported52.h"
#include "ported135.h"
#include "ported33.h"
#include <string.h>
#ifdef RE_HOOK_BUILD
#  define P52_STD __attribute__((stdcall))
#else
#  define P52_STD
#endif
GAME_VAR_DEF(int32_t, P52_FogOn, 0x00b87e88)
GAME_VAR_DEF(uint8_t, P52_NoTrail, 0x0056002c)
GAME_VAR_DEF(int32_t, P52_MenuCnt, 0x00b5a750)
GAME_VAR_DEF(int32_t, P52_MenuA, 0x00b5a754)
GAME_VAR_DEF(int32_t, P52_MenuB, 0x00b5a758)
GAME_VAR_DEF(int32_t, P52_MenuC, 0x00b5a75c)
GAME_VAR_DEF(int32_t, P52_ResetA, 0x00b5a8a8)
GAME_VAR_DEF(uint8_t, P52_ResetB, 0x01137354)
GAME_VAR_DEF(int32_t, P52_ResetC, 0x011237b8)
GAME_VAR_DEF(int32_t, P52_Ones0, 0x010ffa30)
GAME_VAR_DEF(int32_t, P52_Ones1, 0x010ffa34)
GAME_VAR_DEF(int32_t, P52_Ones2, 0x010ffa38)
GAME_VAR_DEF(int32_t, P52_Ones3, 0x010ffa3c)
GAME_VAR_DEF(p52_fog_t, P52_FogTab, 0x01252b80)
GAME_VAR_DEF(p52_names_t, P52_NameTab, 0x00b5a6a8)
GAME_VAR_DEF(p52_colors_t, P52_ColorTab, 0x00552e0c)

static void *glide_proc(const char *name) {
  for (int i = 0; i < P33_GlideCount(); i++)
    if (strcmp(P33_GlideName(i), name) == 0) return P33_GlideProc(i);
  return NULL;
}
static float bits_f(uint32_t u) { float f; memcpy(&f, &u, 4); return f; }

void P52_GlideFogSetup(void) {
  void (P52_STD *fogcolor)(uint32_t) = (void (P52_STD *)(uint32_t))glide_proc("_grFogColorValue@4");
  void (P52_STD *genexp)(void *, float) = (void (P52_STD *)(void *, float))glide_proc("_guFogGenerateExp@8");
  void (P52_STD *fogtable)(void *) = (void (P52_STD *)(void *))glide_proc("_grFogTable@4");
  if (P52_FogOn == 0 || P26_FxD != 0) {
    if (fogcolor) fogcolor(0xaaaaaau);
    if (genexp) genexp(&P52_FogTab, bits_f(0x38fba882u));
  } else {
    if (fogcolor) fogcolor(0);
    if (genexp) genexp(&P52_FogTab, bits_f(0x38d1b717u));
    P26_FxD = 1;
  }
  if (fogtable) fogtable(&P52_FogTab);
}

void P52_GlideFogMode(void) {
  void (P52_STD *fogmode)(int32_t) = (void (P52_STD *)(int32_t))glide_proc("_grFogMode@4");
  void (P52_STD *colormask)(int32_t, int32_t) = (void (P52_STD *)(int32_t, int32_t))glide_proc("_grColorMask@8");
  void (P52_STD *clear)(int32_t, int32_t, int32_t) = (void (P52_STD *)(int32_t, int32_t, int32_t))glide_proc("_grBufferClear@12");
  if (fogmode) fogmode(P26_FxD == 0 ? 0 : 2);
  if (P52_NoTrail == 0 && colormask) colormask(0, 0);
  if (clear) clear(0, 0, 0xffff);
  if (P52_NoTrail == 0 && colormask) colormask(1, 0);
}

void P52_TexDownloadMipMap(int32_t a, int32_t b, int32_t c, int32_t d, int32_t e) {
  if (D_00b1c0d4 == 0) return;
  if (D_00b1c0d8 == 0) {
    void (P52_STD *f)(int32_t, int32_t, int32_t, int32_t) = (void (P52_STD *)(int32_t, int32_t, int32_t, int32_t))glide_proc("_grTexDownloadMipMap@16");
    if (f) f(a, b, c, d);
  } else if (D_00b1c0d8 == 1) {
    P52_Fn41D53C(a, b, c, d, e);
  }
}

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

void P52_HudDispatch(void) {
  if (D_00b87e30 == 4) {
    if (P11_00b87e38 == 0xc9) P135_GhostTrail();
    if (D_00b87e30 == 4) { P52_Fn4E5A1A(); P115_PaperHud(); }
    if (P12_00d044d0 != 0) DrawTextLine004FBBC5(0x00d04680);
  } else if (D_00b87e30 == 5 && G6_00B87EA0 != 0) {
    P135_GhostTrail();
  }
}

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

int32_t P52_FmvStart(const char *a) {
  Chain0048AC0D();
  if (P150_OpenAudio(a) != 0 && P52_Fn48B5E3() != 0) return 1;
  Chain0048AC0D();
  return 0;
}

void P52_DrawLabel(int32_t a, int32_t b, int32_t c) {
  int32_t top = 0x60 - (int32_t)ScanSlot_0040AAE2(0);
  if (b < top) return;
  SetRGB00516EB4(P52_ColorTab[c * 4], P52_ColorTab[c * 4 + 1], P52_ColorTab[c * 4 + 2]);
  P52_Fn5173D7(bits_f(0x43f00000u), (float)b, a, 0, 1);
}

void P52_MenuReload(void) {
  P52_MenuA = 0; P52_MenuB = 0; P52_MenuC = 0;
  if (GameMode == 0) P139_ReplayEnd();
  if (P52_Fn405F6F(P52_MenuCnt, (uint8_t *)P52_NameTab + P52_MenuCnt * 0x11) == 0) GlobalSet00511378();
  Call00510784();
}
