#include "ported16.h"
#include <string.h>
GAME_VAR_DEF(int32_t, P16_ParticleCount, 0x011171a0)
GAME_VAR_DEF(uint8_t, P16_ParticleBase, 0x0110e160)
#ifndef RE_HOOK_BUILD /* v2.21 gvar-img */
#pragma push_macro("P16_IdleMode")
#undef P16_IdleMode
int32_t P16_IdleMode;
#pragma pop_macro("P16_IdleMode")
#else
GAME_VAR_DEF(int32_t, P16_IdleMode, 0x00c810c4)
#endif
#ifndef RE_HOOK_BUILD /* v2.21 gvar-img */
#pragma push_macro("P16_FlagA")
#undef P16_FlagA
int32_t P16_FlagA;
#pragma pop_macro("P16_FlagA")
#else
GAME_VAR_DEF(int32_t, P16_FlagA, 0x00b5a778)
#endif
#ifndef RE_HOOK_BUILD /* v2.21 gvar-img */
#pragma push_macro("P16_FlagB")
#undef P16_FlagB
int32_t P16_FlagB;
#pragma pop_macro("P16_FlagB")
#else
GAME_VAR_DEF(int32_t, P16_FlagB, 0x00b87ee4)
#endif
#ifndef RE_HOOK_BUILD /* v2.21 gvar-img */
#pragma push_macro("P16_IdleCounter")
#undef P16_IdleCounter
int32_t P16_IdleCounter;
#pragma pop_macro("P16_IdleCounter")
#else
GAME_VAR_DEF(int32_t, P16_IdleCounter, 0x00d0778c)
#endif
#ifndef RE_HOOK_BUILD /* v2.21 gvar-img */
#pragma push_macro("P16_FlagC")
#undef P16_FlagC
int32_t P16_FlagC;
#pragma pop_macro("P16_FlagC")
#else
GAME_VAR_DEF(int32_t, P16_FlagC, 0x00bdfa58)
#endif
#ifndef RE_HOOK_BUILD /* v2.21 gvar-img */
#pragma push_macro("P16_FlagD")
#undef P16_FlagD
int32_t P16_FlagD;
#pragma pop_macro("P16_FlagD")
#else
GAME_VAR_DEF(int32_t, P16_FlagD, 0x00bdfa44)
#endif
#ifndef RE_HOOK_BUILD /* v2.21 gvar-img */
#pragma push_macro("P16_IdleArg1")
#undef P16_IdleArg1
int32_t P16_IdleArg1;
#pragma pop_macro("P16_IdleArg1")
#else
GAME_VAR_DEF(int32_t, P16_IdleArg1, 0x00c810e8)
#endif
#ifndef RE_HOOK_BUILD /* v2.21 gvar-img */
#pragma push_macro("P16_IdleArg2")
#undef P16_IdleArg2
int32_t P16_IdleArg2;
#pragma pop_macro("P16_IdleArg2")
#else
GAME_VAR_DEF(int32_t, P16_IdleArg2, 0x00c81100)
#endif

static float rf(const uint8_t *p) { float v; memcpy(&v, p, 4); return v; }
static void wf(uint8_t *p, float v) { memcpy(p, &v, 4); }
static int16_t r16(const uint8_t *p) { int16_t v; memcpy(&v, p, 2); return v; }
static void w16(uint8_t *p, int16_t v) { memcpy(p, &v, 2); }

/* Запись 0x24 байта: pos xyz @0, vel xyz @0x10, life i16 @0x20, frame i16 @0x22 */
void P16_StepParticles(void) {
  uint8_t *p = &P16_ParticleBase;
  for (int n = P16_ParticleCount; n != 0; n--, p += 0x24) {
    if (r16(p + 0x20) > 0) {
      wf(p, rf(p) + rf(p + 0x10));
      wf(p + 4, rf(p + 4) + rf(p + 0x14));
      wf(p + 8, rf(p + 8) + rf(p + 0x18));
      int16_t f = r16(p + 0x22);
      w16(p + 0x22, (int16_t)(f - 1));
      if (f == 0) w16(p + 0x22, 10);
      w16(p + 0x20, (int16_t)(r16(p + 0x20) - 1));
    }
  }
}

void P16_IdleTimer(void) {
  if (P16_IdleMode == 0xff0) return;
  if (P16_Level < 3) {
    if (P16_FlagA == 0 && P16_FlagB == 0) P16_IdleCounter++;
  } else {
    P16_IdleCounter = 0;
  }
  int limit = (P16_FlagC == 0 && P16_FlagD == 0) ? 300 : 600;
  if (limit < P16_IdleCounter) { P16_IdleMode = 0xff0; P16_IdleArg1 = 2; P16_IdleArg2 = 0x5a; }
}

void P16_FillHudRect(uint32_t *p, uint32_t a, uint32_t rgb, uint32_t b, int c, int d) {
  uint32_t k;
  float f;
  if (c == 0) { f = 16.0f; k = 0; } else { f = 624.0f; k = 2; }
  memcpy(&p[0], &f, 4);
  f = d == 0 ? 30.0f : 75.0f; memcpy(&p[1], &f, 4);
  f = 165.0f; memcpy(&p[2], &f, 4);
  f = 18.0f; memcpy(&p[3], &f, 4);
  p[4] = 0; p[5] = a;
  f = (float)((rgb & 0xff0000) >> 16); memcpy(&p[6], &f, 4);
  f = (float)((rgb & 0xff00) >> 8); memcpy(&p[7], &f, 4);
  f = (float)(rgb & 0xff); memcpy(&p[8], &f, 4);
  p[9] = b; p[10] = k; p[11] = 1;
}
