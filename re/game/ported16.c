/* ported16 — particle integration step, mission idle/fail timer and a HUD rectangle descriptor (Game.exe). */
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

/* Particle record (0x24 bytes) */
#define PART_SIZE   0x24
#define PART_POS    0x00   /* float[3] position */
#define PART_VEL    0x10   /* float[3] velocity per tick */
#define PART_LIFE   0x20   /* int16 ticks left; <= 0 = dead */
#define PART_FRAME  0x22   /* int16 animation frame counter: counts down, wraps to 10 */

/* P16_StepParticles — Game.exe 004b9d79.  For each of P16_ParticleCount particles at P16_ParticleBase that is
   alive: pos += vel, frame-- (reloaded with 10 when it was 0), life--. */
/* Запись 0x24 байта: pos xyz @0, vel xyz @0x10, life i16 @0x20, frame i16 @0x22 */
void P16_StepParticles(void) {
  uint8_t *p = &P16_ParticleBase;
  for (int n = P16_ParticleCount; n != 0; n--, p += PART_SIZE) {
    if (r16(p + PART_LIFE) > 0) {
      wf(p + PART_POS, rf(p + PART_POS) + rf(p + PART_VEL));
      wf(p + PART_POS + 4, rf(p + PART_POS + 4) + rf(p + PART_VEL + 4));
      wf(p + PART_POS + 8, rf(p + PART_POS + 8) + rf(p + PART_VEL + 8));
      int16_t frame = r16(p + PART_FRAME);
      w16(p + PART_FRAME, (int16_t)(frame - 1));
      if (frame == 0) w16(p + PART_FRAME, 10);
      w16(p + PART_LIFE, (int16_t)(r16(p + PART_LIFE) - 1));
    }
  }
}

/* Mission state values of P16_IdleMode (= P14_00c810c4): missionstate.h. */
#include "missionstate.h"
#define MISSION_FAILED  MSTATE_FAILED

/* P16_IdleTimer — Game.exe 004e12e4 (same function as P14_Fn004E12E4).  Flipped-car check: P16_Level is in fact
   the player's CAR_WHEELS_DOWN (00d078b0 = car 0 + 0xf0, the name is historical).  While fewer than 3 wheels touch
   the ground and neither P16_FlagA (00b5a778) nor P16_FlagB (00b87ee4) is set, P16_IdleCounter counts ticks; with
   3+ wheels down it is reset.  Past 300 ticks (6 s at 50 ticks/s; 600 when the cheat options 00bdfa58 / 00bdfa44
   are on) the mission fails: MSTATE_FAILED, reason MREASON_FAILED (2), result screen after 0x5a ticks
   (missionstate.h).  Does nothing once the mission has failed.  TODO(RE): flags A / B (pause / replay?). */
void P16_IdleTimer(void) {
  if (P16_IdleMode == MISSION_FAILED) return;
  if (P16_Level < 3) {
    if (P16_FlagA == 0 && P16_FlagB == 0) P16_IdleCounter++;
  } else {
    P16_IdleCounter = 0;
  }
  int limit = (P16_FlagC == 0 && P16_FlagD == 0) ? 300 : 600;
  if (limit < P16_IdleCounter) { P16_IdleMode = MISSION_FAILED; P16_IdleArg1 = 2; P16_IdleArg2 = 0x5a; }
}

/* P16_FillHudRect — Game.exe 0050268f.  Fills a 12-word HUD rectangle descriptor p (640x480 screen units):
   p[0] x = 16 (left, c == 0) or 624 (right, c != 0, alignment k = 2), p[1] y = 30 (d == 0) or 75, p[2] w = 165,
   p[3] h = 18, p[4] = 0, p[5] = a, p[6..8] = r, g, b of rgb (0xRRGGBB) as floats 0..255, p[9] = b,
   p[10] = alignment k (0 left / 2 right), p[11] = 1.  TODO(RE): unsure what a, b and p[4]/p[11] are. */
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
