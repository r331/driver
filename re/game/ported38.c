/* FMV-проигрыватель и DirectSound-обёртки — восстановлено из Game.exe (Movie.c, Sound.c). */
/* ported38.c — FMV playback through DirectShow multimedia streams (Movie.c) and DirectSound setup
   wrappers (Sound.c).  plat_mms_* / plat_dd_* / plat_ds_* are the native stand-ins for the COM calls. */
#include "ported38.h"

#define MMS_STATE_STOP  0    /* IMultiMediaStream::SetState: STREAMSTATE_STOP */
#define MMS_STATE_RUN   1    /* STREAMSTATE_RUN */
#define FMV_SCREEN_W    0x280  /* 640: FMV is blitted across the full screen width */
#define FMV_SCREEN_H    0x1e0  /* 480 */
#define DDSCL_NORMAL    8    /* DirectDraw SetCooperativeLevel flag restored when the FMV ends */
GAME_VAR_DEF(void *, P38_Mms, 0x00b1c828)
GAME_VAR_DEF(void *, P38_Mms2, 0x00b1c83c)
GAME_VAR_DEF(void *, P38_Sample, 0x00b1c838)
GAME_VAR_DEF(void *, P38_Dest, 0x00b1c81c)
GAME_VAR_DEF(void *, P38_Src, 0x00b1c820)
GAME_VAR_DEF(void *, P38_Obj824, 0x00b1c824)
GAME_VAR_DEF(void *, P38_DD, 0x00b1c818)
GAME_VAR_DEF(void *, P38_Obj814, 0x00b1c814)
GAME_VAR_DEF(void *, P38_DsPrimary, 0x00b1f424)
GAME_VAR_DEF(void *, P38_Ds, 0x00b1f420)
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P38_Letter")
#undef P38_Letter
#pragma push_macro("P38_Letter") /*gvi*/
#undef P38_Letter /*gvi*/
int32_t P38_Letter;
#pragma pop_macro("P38_Letter") /*gvi*/
#pragma pop_macro("P38_Letter")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P38_TimerSlot")
#undef P38_TimerSlot
#pragma push_macro("P38_TimerSlot") /*gvi*/
#undef P38_TimerSlot /*gvi*/
int32_t P38_TimerSlot;
#pragma pop_macro("P38_TimerSlot") /*gvi*/
#pragma pop_macro("P38_TimerSlot")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P38_TimerFlag")
#undef P38_TimerFlag
#pragma push_macro("P38_TimerFlag") /*gvi*/
#undef P38_TimerFlag /*gvi*/
int32_t P38_TimerFlag;
#pragma pop_macro("P38_TimerFlag") /*gvi*/
#pragma pop_macro("P38_TimerFlag")
#endif

/* P38_MmsRun — Game.exe 0048b2fd.  Starts the FMV stream (SetState RUN).  Returns 1 on success, 0 if
   there is no stream or the call failed. */
int32_t P38_MmsRun(void) {
  if (P38_Mms != NULL && plat_mms_set_state(P38_Mms, MMS_STATE_RUN) == 0) return 1;
  return 0;
}

/* P38_MmsStop — Game.exe 0048b32b.  Stops the FMV stream (SetState STOP) if there is one. */
void P38_MmsStop(void) {
  if (P38_Mms != NULL) plat_mms_set_state(P38_Mms, MMS_STATE_STOP);
}

/* P38_UpdateFrame — Game.exe 0048b34c.  Decodes the next FMV frame (sample Update) and blits the
   stream surface to the screen surface into a letterboxed rectangle: full 640 width, height
   2 * P38_Letter, vertically centred in 480 lines.  Returns 1 if both calls succeeded, else 0. */
int32_t P38_UpdateFrame(void) {
  if (P38_Sample != NULL && plat_sample_update(P38_Sample) == 0) {
    int32_t top = (int32_t)((FMV_SCREEN_H - (uint32_t)P38_Letter * 2u) >> 1);   /* unsigned, as in the original */
    int32_t rc[4] = { 0, top, FMV_SCREEN_W, top + P38_Letter * 2 };              /* RECT left, top, right, bottom */
    if (plat_dd_blt_from(P38_Dest, rc, P38_Src) == 0) return 1;
  }
  return 0;
}

/* P38_FmvRelease — Game.exe 0048ae12.  Releases the FMV surfaces and DirectDraw object: stream surface,
   824, the screen surface (filled black first), the DirectDraw object (cooperative level reset to
   DDSCL_NORMAL first), then 814.  All pointers end up NULL.  TODO(RE): unsure what P38_Obj824/814 are. */
void P38_FmvRelease(void) {
  if (P38_Src != NULL) { plat_dd_release(P38_Src); P38_Src = NULL; }
  if (P38_Obj824 != NULL) { plat_dd_release(P38_Obj824); P38_Obj824 = NULL; }
  if (P38_Dest != NULL) {
    plat_dd_fill_all(P38_Dest, 0);
    plat_dd_release(P38_Dest); P38_Dest = NULL;
  }
  if (P38_DD != NULL) {
    plat_dd_set_cooperative(P38_DD, NULL, DDSCL_NORMAL);
    plat_dd_release(P38_DD); P38_DD = NULL;
  }
  if (P38_Obj814 != NULL) { plat_dd_release(P38_Obj814); P38_Obj814 = NULL; }
}

/* P38_FmvStop — Game.exe 0048b65d.  Stops the second (audio) stream, frees the FMV timer slot
   (P25_TimerStop, slot -1 = none) and sets P38_TimerFlag = 1.  TODO(RE): unsure — the flag probably
   tells the playback loop that the movie is over. */
void P38_FmvStop(void) {
  if (P38_Mms2 != NULL) plat_mms_set_state(P38_Mms2, MMS_STATE_STOP);
  if (P38_TimerSlot != -1) {
    P25_TimerStop(P38_TimerSlot);
    P38_TimerSlot = -1;
  }
  P38_TimerFlag = 1;
}

typedef struct {   /* WAVEFORMATEX */
  uint16_t tag, channels; uint32_t rate, avg; uint16_t align, bits, cb;
} __attribute__((packed)) P38_Wfx;
_Static_assert(sizeof(P38_Wfx) == 18, "P38_Wfx");

/* P38_SetPrimaryFormat — Game.exe 0048bdcc.  Sets the primary DirectSound buffer to stereo PCM with
   the given bits per sample and sample rate (avg bytes/s and block align derived for 2 channels). */
void P38_SetPrimaryFormat(int32_t bits, int32_t rate) {
  if (P38_DsPrimary == NULL) return;
  P38_Wfx w = { 1 /* WAVE_FORMAT_PCM */, 2 /* channels */, (uint32_t)rate, (uint32_t)(rate * 2 * (bits / 8)), (uint16_t)((bits * 2) / 8), (uint16_t)bits, 0 };
  plat_ds_set_format(P38_DsPrimary, &w);
}

/* P38_SetSpeakerConfig — Game.exe 0048be68.  Maps the game's speaker option to a DSSPEAKER_* value and
   applies it: 1 -> 3 (mono), 2 -> 2 (headphone), 3 -> 1 (direct out), 4 -> 5 (surround), else 4 (stereo).
   (DSSPEAKER_ values from dsound.h; which menu entry is which mode is TODO(RE): unsure.) */
void P38_SetSpeakerConfig(int32_t mode) {
  if (P38_Ds == NULL) return;
  uint32_t cfg;
  switch (mode) {
    case 1: cfg = 3; break;
    case 2: cfg = 2; break;
    case 3: cfg = 1; break;
    case 4: cfg = 5; break;
    default: cfg = 4;
  }
  plat_ds_set_speaker_config(P38_Ds, cfg);
}
