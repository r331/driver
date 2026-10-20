/* Звуковые слоты, завершение подсистем, операции скрипта — восстановлено из Game.exe (cdecl). */
/* ported48.c — sound voice slots (20 slots of 0x34 bytes at 00bdc2a0, volumes in 1/100 dB, -10000..0),
   master volume / fade end, startup / shutdown of the input, sound and CD subsystems, and seven opcodes
   of the object animation script (P10_ScriptPtr = byte-code cursor, P10_ScriptCtx = the animated
   object's record; S_00D12410 is the current node of the scripted-object list, P15_ListCur).
   Sound calls go through the sound driver function table at 00bdcb00 (P48_Drv*). */
#include <stdlib.h>
#include <stdio.h>
#include "ported48.h"
#include "../platform/plat.h"
#include <string.h>
GAME_VAR_DEF(P48_F0, P48_Drv00, 0x00bdcb00)
GAME_VAR_DEF(P48_F0, P48_Drv08, 0x00bdcb08)
GAME_VAR_DEF(P48_F0, P48_Drv0C, 0x00bdcb0c)
GAME_VAR_DEF(P48_F1, P48_Drv2C, 0x00bdcb2c)
GAME_VAR_DEF(P48_F1, P48_Drv40, 0x00bdcb40)
GAME_VAR_DEF(P48_F3, P48_Drv38, 0x00bdcb38)
GAME_VAR_DEF(P48_F4, P48_Drv54, 0x00bdcb54)
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P48_VolTab")
#undef P48_VolTab
#pragma push_macro("P48_VolTab") /*gvi*/
#undef P48_VolTab /*gvi*/
P48_VolTabT P48_VolTab;
#pragma pop_macro("P48_VolTab") /*gvi*/
#pragma pop_macro("P48_VolTab")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P48_Samples")
#undef P48_Samples
#pragma push_macro("P48_Samples") /*gvi*/
#undef P48_Samples /*gvi*/
P48_SampleT P48_Samples;
#pragma pop_macro("P48_Samples") /*gvi*/
#pragma pop_macro("P48_Samples")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P48_B91D30")
#undef P48_B91D30
#pragma push_macro("P48_B91D30") /*gvi*/
#undef P48_B91D30 /*gvi*/
int32_t P48_B91D30;
#pragma pop_macro("P48_B91D30") /*gvi*/
#pragma pop_macro("P48_B91D30")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P48_GlideBuf")
#undef P48_GlideBuf
#pragma push_macro("P48_GlideBuf") /*gvi*/
#undef P48_GlideBuf /*gvi*/
P48_Buf64 P48_GlideBuf;
#pragma pop_macro("P48_GlideBuf") /*gvi*/
#pragma pop_macro("P48_GlideBuf")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P48_Pos")
#undef P48_Pos
#pragma push_macro("P48_Pos") /*gvi*/
#undef P48_Pos /*gvi*/
P48_Pos3 P48_Pos;

#pragma pop_macro("P48_Pos") /*gvi*/
#pragma pop_macro("P48_Pos")
#endif

#define SND_VOICES        0x14     /* voice slots */
#define SND_SAMPLES_MAX   0x10     /* entries of G6_00B91BC4 cleared by P48_ResetAll */
#define VOICE_PLAYING     0x01     /* P48_Slot.flags bits */
#define VOICE_VOL_DIRTY   0x08
#define VOICE_LOOPED      0x10
#define VOICE_ID_FREE     0xffff
#define VOL_MIN           (-10000) /* DirectSound DSBVOLUME_MIN (-100 dB) */
#define VOL_DEFAULT       0x7fff   /* "use the slot's default volume" */
#define SAMPLE_FREED      4        /* state byte written to P48_Samples[id * 8] after unloading */

/* P48_FreeVoice — Game.exe 00523e07.  Stops voice `slot` through the driver if it is in use and marks
   the slot free.  Nothing happens while sound is off (G6_00B91CF4 == 0 — sound system started). */
void P48_FreeVoice(int32_t slot) {
  if (G6_00B91CF4 == 0) return;
  if (P48_Snd[slot].flags != 0) P48_Drv40(slot);
  P48_Snd[slot].flags = 0;
  P48_Snd[slot].id = VOICE_ID_FREE;
}
/* P48_SetVoiceVolume — Game.exe 00523ffd.  Sets the volume of a playing or looped voice: vol (0x7fff =
   the slot default) clamped to -10000..0 is stored in .vol; the effective value .scaled is looked up in
   P48_VolTab at index (vol + 10000) * P43_FadeLen (master volume 0..1, truncated), and the slot is
   flagged dirty (bit 3) for the driver.  Skipped when sound is off or G8_00575F40 == 0 (TODO(RE):
   unsure — "sound effects enabled").  Native: RE_HORNDBG debug print for voice 2 (horn). */
void P48_SetVoiceVolume(int32_t slot, int32_t vol) {
#ifndef RE_HOOK_BUILD
  /* v2.11: RE_HORNDBG=N — раз в N вызовов для голоса 2 (гудок): громкость, флаги слота, id */
  if (slot == 2) { static int k; const char *e = getenv("RE_HORNDBG"); if (e && (k++ % (atoi(e) > 0 ? atoi(e) : 50)) == 0)
      fprintf(stderr, "[horn] vol %d flags %x id %x snd %d en %d\n", (int)vol, (unsigned)P48_Snd[2].flags, (unsigned)P48_Snd[2].id,
              (int)G6_00B91CF4, (int)G8_00575F40); }
#endif
  if (G6_00B91CF4 == 0 || G8_00575F40 == 0) return;
  P48_Slot *s = &P48_Snd[slot];
  if ((s->flags & (VOICE_PLAYING | VOICE_LOOPED)) == 0) return;
  if (vol == VOL_DEFAULT) vol = s->defVol;
  if (vol < VOL_MIN) vol = VOL_MIN;
  if (vol > 0) vol = 0;
  s->vol = (int16_t)vol;
  float t = (float)(vol + 10000);                      /* fild + fstp float */
  int32_t idx = (int32_t)((long double)t * P43_FadeLen); /* fmul в x87, __ftol — усечение */
  s->scaled = (int16_t)(P48_VolTab[idx] & 0xffff);
  s->flags |= VOICE_VOL_DIRTY;
}
/* P48_SetMasterVolume — Game.exe 00523711.  Sets the master volume P43_FadeLen = v clamped to 0..1 (NaN
   -> 0, as the original's fcomp test) and re-applies every playing / looped voice's volume. */
void P48_SetMasterVolume(float v) {
  if (G6_00B91CF4 == 0) return;
  P43_FadeLen = v;
  if (!(P43_FadeLen >= 0.0f)) P43_FadeLen = 0.0f;       /* fcomp: C0 (меньше или NaN) */
  if (P43_FadeLen > 1.0f) P43_FadeLen = 1.0f;
  for (int32_t i = 0; i < SND_VOICES; i++)
    if ((P48_Snd[i].flags & (VOICE_PLAYING | VOICE_LOOPED)) != 0) P48_SetVoiceVolume(i, P48_Snd[i].vol);
}
/* P48_StopAll — Game.exe 005237b1.  Frees all voices, cancels a running fade and restores the master
   volume from WF00575F14 (TODO(RE): unsure — the volume option). */
void P48_StopAll(void) {
  if (G6_00B91CF4 == 0) return;
  for (int32_t i = 0; i < SND_VOICES; i++) P48_FreeVoice(i);
  P43_FadeOn = 0;
  P48_SetMasterVolume(WF00575F14);
  P43_FadeSteps = 0; P43_FadeA = 0.0f; P43_FadeB = 0; P43_FadeStep = 0.0f;
}
/* P48_FreeSample — Game.exe 00524b7e.  Frees every voice playing sample id, unloads the sample through
   the driver and marks its record (8 bytes per sample) as freed. */
void P48_FreeSample(uint32_t id) {
  for (int32_t i = 0; i < SND_VOICES; i++)
    if (P48_Snd[i].id == id) P48_FreeVoice(i);
  P48_Drv2C((int32_t)id);
  P48_Samples[id * 8] = SAMPLE_FREED;
}
/* P48_ResetAll — Game.exe 00523628.  Stops everything and unloads all G6_00B91D34 loaded samples;
   clears the 16-entry table G6_00B91BC4 and the sample count. */
void P48_ResetAll(void) {
  if (G6_00B91CF4 == 0) return;
  P48_StopAll();
  for (int32_t i = 0; i < G6_00B91D34; i++) P48_FreeSample((uint32_t)i);
  for (int32_t i = 0; i < SND_SAMPLES_MAX; i++) G6_00B91BC4[i] = 0;
  G6_00B91D34 = 0;
}
/* P48_SndShutdown — Game.exe 00523595.  Stops and unloads everything, shuts the sound driver down and
   marks the sound system off (G6_00B91CF4 = 0). */
void P48_SndShutdown(void) {
  if (G6_00B91CF4 == 0) return;
  P48_StopAll();
  P48_ResetAll();
  P48_Drv00();
  G6_00B91D34 = 0;
  P48_B91D30 = 0;
  G6_00B91CF4 = 0;
}
/* P48_SndPause — Game.exe 0052369b.  Only for a == 0: driver calls 08, 38(0, 0, 0), 54(i, 0, 0, 0) for
   every playing voice, then 0C.  TODO(RE): unsure what the driver entries 08/0C/38/54 do (the Russian
   header says "mute all playing voices"; 38/54 look like listener / voice 3D velocity resets). */
void P48_SndPause(int32_t a) {
  if (G6_00B91CF4 == 0 || a != 0) return;
  P48_Drv08();
  P48_Drv38(0, 0, 0);
  for (int32_t i = 0; i < SND_VOICES; i++)
    if ((P48_Snd[i].flags & VOICE_PLAYING) != 0) P48_Drv54(i, 0, 0, 0);
  P48_Drv0C();
}
/* P48_FadeEnd — Game.exe 005243eb.  Ends a running fade: restores the master volume and re-applies the
   volume of each playing voice (redundant with SetMasterVolume, kept as in the original). */
void P48_FadeEnd(void) {
  if (G6_00B91CF4 == 0 || P43_FadeOn == 0) return;
  P48_SetMasterVolume(WF00575F14);
  for (int32_t i = 0; i < SND_VOICES; i++)
    if ((P48_Snd[i].flags & VOICE_PLAYING) != 0) P48_SetVoiceVolume(i, P48_Snd[i].vol);
  P43_FadeOn = 0;
}
/* P48_GetVoiceVolume — Game.exe 005242e7.  Current volume of a playing voice (as u16), else 0. */
uint16_t P48_GetVoiceVolume(int32_t slot) {
  if (G6_00B91CF4 == 0 || G8_00575F40 == 0) return 0;
  return (P48_Snd[slot].flags & VOICE_PLAYING) != 0 ? (uint16_t)P48_Snd[slot].vol : 0;
}
/* P48_AnyKey — Game.exe 004d97e9.  Polls input and returns 1 if any keyboard key 0..254 is down.
   Native: advances the virtual clock first (RE_FIXED_DT) so splash-screen waits make progress. */
int32_t P48_AnyKey(void) {
  plat_vt_poll();   /* v2.08: native RE_FIXED_DT — ожидание заставки (004d…/ported126) идёт по виртуальным часам; иначе ничего */
  P36_PollInput();
  for (int32_t i = 0xfe; i >= 0; i--)
    if (P34_Keys[i] != 0) return 1;
  return 0;
}
/* P48_PosToInts — Game.exe 0041a1b5.  Copies the float position P48_Pos (01136cb4) to out[3], truncated. */
void P48_PosToInts(int32_t *out) {
  out[0] = (int32_t)P48_Pos[0];
  out[1] = (int32_t)P48_Pos[1];
  out[2] = (int32_t)P48_Pos[2];
}
/* P48_GlideCheck — Game.exe 00425f52.  Dev00424633, then returns 1 if GameCall00424661(buffer) reports
   1.  TODO(RE): unsure — presumably a Glide (3dfx) hardware query into P48_GlideBuf. */
int32_t P48_GlideCheck(void) {
  Dev00424633();
  return GameCall00424661((intptr_t)&P48_GlideBuf) == 1;
}
/* P48_ShutdownSystems — Game.exe 004d3402.  Shuts down force feedback/effects, DirectInput, sound,
   CD audio, frees buffers and uninitialises COM (reverse of P48_StartupSystems). */
void P48_ShutdownSystems(void) {
  ResetEffectsState();
  P34_ReleaseInput();
  P48_SndShutdown();
  P25_CDClose();
  FreeBufs00516E2E();
  plat_com_uninit();
}
/* P48_StartupSystems — Game.exe 004d33c0.  Initialises COM, input, P48_Fn516DA0, audio
   (StartAudio005233A0 + Call005233BE with the three sound options) and CD audio.  Always returns 1. */
int32_t P48_StartupSystems(void) {
  plat_com_init();
  P37_InitInput();
  P48_Fn516DA0();
  StartAudio005233A0();
  Call005233BE(P12_00b87e58, P12_00b87e5c, P12_00575f50);
  P25_InitCDAudio();
  return 1;
}

/* --- операции скрипта --- */
/* Object animation script.  Each opcode handler starts with P10_ScriptPtr at its 2-byte opcode and
   advances past its operands.  Return 1 = done (continue with the next op); return 0 with the cursor
   reset to the opcode = "run me again next frame" (ramps, turns).  Fields of the animated object record
   (P10_ScriptCtx) used here: */
#define OBJ_POS        0x00   /* int32[3] position */
#define OBJ_ANGLE      0x12   /* u16 heading, 4096 = 360 deg */
#define OBJ_VEC        0x28   /* int32[3] TODO(RE): unsure — set by op 004d107e together with the speed */
#define OBJ_W40        0x40   /* u16 set by P48_OpFlags (a == 2). TODO(RE): unsure */
#define OBJ_SPEED      0x44   /* float speed, ramped by P48_OpRampDown / P48_OpRampUp */
#define OBJ_FLAGS      0x48   /* u16 flags */
#define OBJ_W4A        0x4a   /* u16 set by P48_OpSet3 unless the list node has bits 0x30. TODO(RE): unsure */
#define OBJF_KEEP      0x0004 /* the only flag P48_OpSet3 keeps */
#define OBJF_20        0x0020 /* toggled by P48_OpFlags (a == 1). TODO(RE): unsure */
#define OBJF_RAMPING   0x0040 /* set while a speed ramp or turn runs */
#define OBJF_TURNING   0x01c0 /* 0x40 | 0x80 | 0x100 set by P48_OpTurn; 0x100 = turn in progress */
#define OBJF_TURN_RUN  0x0100
static uint16_t r16(const uint8_t *p) { uint16_t v; memcpy(&v, p, 2); return v; }
static uint32_t r32(const uint8_t *p) { uint32_t v; memcpy(&v, p, 4); return v; }
static float    rf(const uint8_t *p) { float v; memcpy(&v, p, 4); return v; }
static void w16(uint8_t *p, uint16_t v) { memcpy(p, &v, 2); }
static void w32(uint8_t *p, uint32_t v) { memcpy(p, &v, 4); }
static void wf(uint8_t *p, float v) { memcpy(p, &v, 4); }
/* P48_OpSet3 — Game.exe 004d020b.  Operands: u16 w4a, int32 x, y, z.  Sets the object position (and w4a
   unless the current list node has flag bits 0x30), and clears all object flags except bit 2. */
int32_t P48_OpSet3(void) {
  P10_ScriptPtr += 2;
  if ((*S_00D12410 & 0x30) == 0) w16(P10_ScriptCtx + OBJ_W4A, r16(P10_ScriptPtr));
  P10_ScriptPtr += 2;
  w32(P10_ScriptCtx + OBJ_POS + 0, r32(P10_ScriptPtr)); P10_ScriptPtr += 4;
  w32(P10_ScriptCtx + OBJ_POS + 4, r32(P10_ScriptPtr)); P10_ScriptPtr += 4;
  w32(P10_ScriptCtx + OBJ_POS + 8, r32(P10_ScriptPtr)); P10_ScriptPtr += 4;
  w16(P10_ScriptCtx + OBJ_FLAGS, (uint16_t)(r16(P10_ScriptCtx + OBJ_FLAGS) & OBJF_KEEP));
  return 1;
}
/* P48_OpSet4 — Game.exe 004d107e.  Operands: 4 dwords copied to the speed (+0x44) and the vector +0x28..+0x30. */
int32_t P48_OpSet4(void) {
  P10_ScriptPtr += 2;
  w32(P10_ScriptCtx + OBJ_SPEED, r32(P10_ScriptPtr)); P10_ScriptPtr += 4;
  w32(P10_ScriptCtx + OBJ_VEC + 0, r32(P10_ScriptPtr)); P10_ScriptPtr += 4;
  w32(P10_ScriptCtx + OBJ_VEC + 4, r32(P10_ScriptPtr)); P10_ScriptPtr += 4;
  w32(P10_ScriptCtx + OBJ_VEC + 8, r32(P10_ScriptPtr)); P10_ScriptPtr += 4;
  return 1;
}
/* P48_OpRampDown — Game.exe 004d116c.  Operands: float limit, float step.  Each frame speed -= step;
   finishes (speed = limit, return 1) once speed <= limit (or NaN), else repeats next frame. */
int32_t P48_OpRampDown(void) {
  uint8_t *orig = P10_ScriptPtr, *c = P10_ScriptCtx;
  w16(c + OBJ_FLAGS, (uint16_t)(r16(c + OBJ_FLAGS) | OBJF_RAMPING));
  P10_ScriptPtr += 2; float limit = rf(P10_ScriptPtr);
  P10_ScriptPtr += 4; float step = rf(P10_ScriptPtr);
  P10_ScriptPtr += 4;
  wf(c + OBJ_SPEED, rf(c + OBJ_SPEED) - step);
  if (!(rf(c + OBJ_SPEED) > limit)) { wf(c + OBJ_SPEED, limit); return 1; }   /* fcomp: C0|C3 (<=, NaN) */
  P10_ScriptPtr = orig;
  return 0;
}
/* P48_OpRampUp — Game.exe 004d121b.  Operands: float limit, float step.  Each frame speed += step;
   finishes (speed = limit) once speed >= limit. */
int32_t P48_OpRampUp(void) {
  uint8_t *orig = P10_ScriptPtr, *c = P10_ScriptCtx;
  w16(c + OBJ_FLAGS, (uint16_t)(r16(c + OBJ_FLAGS) | OBJF_RAMPING));
  P10_ScriptPtr += 2; float limit = rf(P10_ScriptPtr);
  P10_ScriptPtr += 4; float step = rf(P10_ScriptPtr);
  P10_ScriptPtr += 4;
  wf(c + OBJ_SPEED, step + rf(c + OBJ_SPEED));
  if (rf(c + OBJ_SPEED) >= limit) { wf(c + OBJ_SPEED, limit); return 1; }
  P10_ScriptPtr = orig;
  return 0;
}
/* P48_OpFlags — Game.exe 004d142c.  Operands: int16 a, int16 b.  a == 1: set (b != 0) or clear flag 0x20;
   a == 2: word +0x40 = b; other a: nothing. */
int32_t P48_OpFlags(void) {
  uint8_t *c;
  P10_ScriptPtr += 2; int16_t a = (int16_t)r16(P10_ScriptPtr);
  P10_ScriptPtr += 2; int16_t b = (int16_t)r16(P10_ScriptPtr);
  P10_ScriptPtr += 2;
  c = P10_ScriptCtx;
  if (a == 1) {
    if (b != 0) w16(c + OBJ_FLAGS, (uint16_t)(r16(c + OBJ_FLAGS) | OBJF_20));
    else        w16(c + OBJ_FLAGS, (uint16_t)(r16(c + OBJ_FLAGS) & 0xffdf));
  } else if (a == 2) {
    w16(c + OBJ_W40, (uint16_t)b);
  }
  return 1;
}
/* P48_OpRepeat — Game.exe 004d1672.  Operands: u16 init, u16 counter (modified in place), u16 back.
   While counter != 0: decrement it and jump back `back` bytes measured from the `back` operand;
   when it reaches 0: reload counter = init and fall through to the next op.  (Self-modifying loop
   counter in the script data, as in the original.) */
int32_t P48_OpRepeat(void) {
  P10_ScriptPtr += 2; uint16_t init = r16(P10_ScriptPtr);
  P10_ScriptPtr += 2; uint16_t cnt = r16(P10_ScriptPtr);
  if (cnt != 0) {
    w16(P10_ScriptPtr, (uint16_t)(cnt - 1));
    P10_ScriptPtr += 2;
    P10_ScriptPtr -= r16(P10_ScriptPtr);
  } else {
    w16(P10_ScriptPtr, init);
    P10_ScriptPtr += 2; P10_ScriptPtr += 2;
  }
  return 1;
}
/* P48_OpTurn — Game.exe 004d0d7c.  Operands: float radius, u16 dir.  A quarter turn along an arc:
   per frame the heading advances by step = 1024 * speed / (radius * pi / 2) (a quarter circle of the
   given radius covered at the current speed, in 4096-per-turn units).  On the first frame (flag 0x100
   clear) the heading is snapped to quadrant (dir & 3) * 90 deg.  dir 0..3 turns with increasing
   heading toward quadrant dir + 1; dir >= 4 turns the other way toward quadrant (dir + 3) & 3.
   Finishes (clears 0x100 and 0x40, return 1) when the remaining angle is less than one step; the
   heading is NOT snapped to the target at the end (as in the original). */
int32_t P48_OpTurn(void) {
  uint8_t *orig = P10_ScriptPtr, *c = P10_ScriptCtx;
  P10_ScriptPtr += 2; float arg = rf(P10_ScriptPtr);
  P10_ScriptPtr += 4; uint16_t dir = r16(P10_ScriptPtr);
  P10_ScriptPtr += 2;
  long double q = ((long double)1024.0f * rf(c + OBJ_SPEED)) / (((long double)arg * 3.14159274f) / 2.0f);
  uint16_t step = (uint16_t)(int32_t)q;
  uint16_t lim;                              /* angle still to turn */
  if ((r16(c + OBJ_FLAGS) & OBJF_TURN_RUN) == 0) w16(c + OBJ_ANGLE, (uint16_t)((dir & 3) << 10));
  w16(c + OBJ_FLAGS, (uint16_t)(r16(c + OBJ_FLAGS) | OBJF_TURNING));
  if (dir < 4) {
    w16(c + OBJ_ANGLE, (uint16_t)(r16(c + OBJ_ANGLE) + step));
    lim = (uint16_t)((((dir & 3) + 1) << 10) - (int16_t)r16(c + OBJ_ANGLE));
  } else {
    w16(c + OBJ_ANGLE, (uint16_t)(r16(c + OBJ_ANGLE) + (0x1000 - step)));   /* ANG_FULL - step */
    w16(c + OBJ_ANGLE, (uint16_t)(r16(c + OBJ_ANGLE) & 0xfff));
    lim = (uint16_t)((int16_t)r16(c + OBJ_ANGLE) - (((dir + 3) & 3) << 10));
  }
  if (lim < step) { w16(c + OBJ_FLAGS, (uint16_t)(r16(c + OBJ_FLAGS) & 0xfebf)); return 1; }   /* ~(0x100 | 0x40) */
  P10_ScriptPtr = orig;
  return 0;
}
