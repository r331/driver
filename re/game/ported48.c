/* Звуковые слоты, завершение подсистем, операции скрипта — восстановлено из Game.exe (cdecl). */
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

void P48_FreeVoice(int32_t slot) {
  if (G6_00B91CF4 == 0) return;
  if (P48_Snd[slot].flags != 0) P48_Drv40(slot);
  P48_Snd[slot].flags = 0;
  P48_Snd[slot].id = 0xffff;
}
void P48_SetVoiceVolume(int32_t slot, int32_t vol) {
  if (G6_00B91CF4 == 0 || G8_00575F40 == 0) return;
  P48_Slot *s = &P48_Snd[slot];
  if ((s->flags & 0x11) == 0) return;
  if (vol == 0x7fff) vol = s->defVol;
  if (vol < -10000) vol = -10000;
  if (vol > 0) vol = 0;
  s->vol = (int16_t)vol;
  float t = (float)(vol + 10000);                      /* fild + fstp float */
  int32_t idx = (int32_t)((long double)t * P43_FadeLen); /* fmul в x87, __ftol — усечение */
  s->scaled = (int16_t)(P48_VolTab[idx] & 0xffff);
  s->flags |= 8;
}
void P48_SetMasterVolume(float v) {
  if (G6_00B91CF4 == 0) return;
  P43_FadeLen = v;
  if (!(P43_FadeLen >= 0.0f)) P43_FadeLen = 0.0f;       /* fcomp: C0 (меньше или NaN) */
  if (P43_FadeLen > 1.0f) P43_FadeLen = 1.0f;
  for (int32_t i = 0; i < 0x14; i++)
    if ((P48_Snd[i].flags & 0x11) != 0) P48_SetVoiceVolume(i, P48_Snd[i].vol);
}
void P48_StopAll(void) {
  if (G6_00B91CF4 == 0) return;
  for (int32_t i = 0; i < 0x14; i++) P48_FreeVoice(i);
  P43_FadeOn = 0;
  P48_SetMasterVolume(WF00575F14);
  P43_FadeSteps = 0; P43_FadeA = 0.0f; P43_FadeB = 0; P43_FadeStep = 0.0f;
}
void P48_FreeSample(uint32_t id) {
  for (int32_t i = 0; i < 0x14; i++)
    if (P48_Snd[i].id == id) P48_FreeVoice(i);
  P48_Drv2C((int32_t)id);
  P48_Samples[id * 8] = 4;
}
void P48_ResetAll(void) {
  if (G6_00B91CF4 == 0) return;
  P48_StopAll();
  for (int32_t i = 0; i < G6_00B91D34; i++) P48_FreeSample((uint32_t)i);
  for (int32_t i = 0; i < 0x10; i++) G6_00B91BC4[i] = 0;
  G6_00B91D34 = 0;
}
void P48_SndShutdown(void) {
  if (G6_00B91CF4 == 0) return;
  P48_StopAll();
  P48_ResetAll();
  P48_Drv00();
  G6_00B91D34 = 0;
  P48_B91D30 = 0;
  G6_00B91CF4 = 0;
}
void P48_SndPause(int32_t a) {
  if (G6_00B91CF4 == 0 || a != 0) return;
  P48_Drv08();
  P48_Drv38(0, 0, 0);
  for (int32_t i = 0; i < 0x14; i++)
    if ((P48_Snd[i].flags & 1) != 0) P48_Drv54(i, 0, 0, 0);
  P48_Drv0C();
}
void P48_FadeEnd(void) {
  if (G6_00B91CF4 == 0 || P43_FadeOn == 0) return;
  P48_SetMasterVolume(WF00575F14);
  for (int32_t i = 0; i < 0x14; i++)
    if ((P48_Snd[i].flags & 1) != 0) P48_SetVoiceVolume(i, P48_Snd[i].vol);
  P43_FadeOn = 0;
}
uint16_t P48_GetVoiceVolume(int32_t slot) {
  if (G6_00B91CF4 == 0 || G8_00575F40 == 0) return 0;
  return (P48_Snd[slot].flags & 1) != 0 ? (uint16_t)P48_Snd[slot].vol : 0;
}
int32_t P48_AnyKey(void) {
  P36_PollInput();
  for (int32_t i = 0xfe; i >= 0; i--)
    if (P34_Keys[i] != 0) return 1;
  return 0;
}
void P48_PosToInts(int32_t *out) {
  out[0] = (int32_t)P48_Pos[0];
  out[1] = (int32_t)P48_Pos[1];
  out[2] = (int32_t)P48_Pos[2];
}
int32_t P48_GlideCheck(void) {
  Dev00424633();
  return GameCall00424661((intptr_t)&P48_GlideBuf) == 1;
}
void P48_ShutdownSystems(void) {
  ResetEffectsState();
  P34_ReleaseInput();
  P48_SndShutdown();
  P25_CDClose();
  FreeBufs00516E2E();
  plat_com_uninit();
}
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
static uint16_t r16(const uint8_t *p) { uint16_t v; memcpy(&v, p, 2); return v; }
static uint32_t r32(const uint8_t *p) { uint32_t v; memcpy(&v, p, 4); return v; }
static float    rf(const uint8_t *p) { float v; memcpy(&v, p, 4); return v; }
static void w16(uint8_t *p, uint16_t v) { memcpy(p, &v, 2); }
static void w32(uint8_t *p, uint32_t v) { memcpy(p, &v, 4); }
static void wf(uint8_t *p, float v) { memcpy(p, &v, 4); }
int32_t P48_OpSet3(void) {
  P10_ScriptPtr += 2;
  if ((*S_00D12410 & 0x30) == 0) w16(P10_ScriptCtx + 0x4a, r16(P10_ScriptPtr));
  P10_ScriptPtr += 2;
  w32(P10_ScriptCtx + 0, r32(P10_ScriptPtr)); P10_ScriptPtr += 4;
  w32(P10_ScriptCtx + 4, r32(P10_ScriptPtr)); P10_ScriptPtr += 4;
  w32(P10_ScriptCtx + 8, r32(P10_ScriptPtr)); P10_ScriptPtr += 4;
  w16(P10_ScriptCtx + 0x48, (uint16_t)(r16(P10_ScriptCtx + 0x48) & 4));
  return 1;
}
int32_t P48_OpSet4(void) {
  P10_ScriptPtr += 2;
  w32(P10_ScriptCtx + 0x44, r32(P10_ScriptPtr)); P10_ScriptPtr += 4;
  w32(P10_ScriptCtx + 0x28, r32(P10_ScriptPtr)); P10_ScriptPtr += 4;
  w32(P10_ScriptCtx + 0x2c, r32(P10_ScriptPtr)); P10_ScriptPtr += 4;
  w32(P10_ScriptCtx + 0x30, r32(P10_ScriptPtr)); P10_ScriptPtr += 4;
  return 1;
}
int32_t P48_OpRampDown(void) {
  uint8_t *orig = P10_ScriptPtr, *c = P10_ScriptCtx;
  w16(c + 0x48, (uint16_t)(r16(c + 0x48) | 0x40));
  P10_ScriptPtr += 2; float limit = rf(P10_ScriptPtr);
  P10_ScriptPtr += 4; float step = rf(P10_ScriptPtr);
  P10_ScriptPtr += 4;
  wf(c + 0x44, rf(c + 0x44) - step);
  if (!(rf(c + 0x44) > limit)) { wf(c + 0x44, limit); return 1; }   /* fcomp: C0|C3 (<=, NaN) */
  P10_ScriptPtr = orig;
  return 0;
}
int32_t P48_OpRampUp(void) {
  uint8_t *orig = P10_ScriptPtr, *c = P10_ScriptCtx;
  w16(c + 0x48, (uint16_t)(r16(c + 0x48) | 0x40));
  P10_ScriptPtr += 2; float limit = rf(P10_ScriptPtr);
  P10_ScriptPtr += 4; float step = rf(P10_ScriptPtr);
  P10_ScriptPtr += 4;
  wf(c + 0x44, step + rf(c + 0x44));
  if (rf(c + 0x44) >= limit) { wf(c + 0x44, limit); return 1; }
  P10_ScriptPtr = orig;
  return 0;
}
int32_t P48_OpFlags(void) {
  uint8_t *c;
  P10_ScriptPtr += 2; int16_t a = (int16_t)r16(P10_ScriptPtr);
  P10_ScriptPtr += 2; int16_t b = (int16_t)r16(P10_ScriptPtr);
  P10_ScriptPtr += 2;
  c = P10_ScriptCtx;
  if (a == 1) {
    if (b != 0) w16(c + 0x48, (uint16_t)(r16(c + 0x48) | 0x20));
    else        w16(c + 0x48, (uint16_t)(r16(c + 0x48) & 0xffdf));
  } else if (a == 2) {
    w16(c + 0x40, (uint16_t)b);
  }
  return 1;
}
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
int32_t P48_OpTurn(void) {
  uint8_t *orig = P10_ScriptPtr, *c = P10_ScriptCtx;
  P10_ScriptPtr += 2; float arg = rf(P10_ScriptPtr);
  P10_ScriptPtr += 4; uint16_t dir = r16(P10_ScriptPtr);
  P10_ScriptPtr += 2;
  long double q = ((long double)1024.0f * rf(c + 0x44)) / (((long double)arg * 3.14159274f) / 2.0f);
  uint16_t step = (uint16_t)(int32_t)q;
  uint16_t lim;
  if ((r16(c + 0x48) & 0x100) == 0) w16(c + 0x12, (uint16_t)((dir & 3) << 10));
  w16(c + 0x48, (uint16_t)(r16(c + 0x48) | 0x1c0));
  if (dir < 4) {
    w16(c + 0x12, (uint16_t)(r16(c + 0x12) + step));
    lim = (uint16_t)((((dir & 3) + 1) << 10) - (int16_t)r16(c + 0x12));
  } else {
    w16(c + 0x12, (uint16_t)(r16(c + 0x12) + (0x1000 - step)));
    w16(c + 0x12, (uint16_t)(r16(c + 0x12) & 0xfff));
    lim = (uint16_t)((int16_t)r16(c + 0x12) - (((dir + 3) & 3) << 10));
  }
  if (lim < step) { w16(c + 0x48, (uint16_t)(r16(c + 0x48) & 0xfebf)); return 1; }
  P10_ScriptPtr = orig;
  return 0;
}
