/* FMV-проигрыватель и DirectSound-обёртки — восстановлено из Game.exe (Movie.c, Sound.c). */
#include "ported38.h"
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
GAME_VAR_DEF(int32_t, P38_Letter, 0x00b1c7b0)
GAME_VAR_DEF(int32_t, P38_TimerSlot, 0x00551130)
GAME_VAR_DEF(int32_t, P38_TimerFlag, 0x00551134)

int32_t P38_MmsRun(void) {
  if (P38_Mms != NULL && plat_mms_set_state(P38_Mms, 1) == 0) return 1;
  return 0;
}

void P38_MmsStop(void) {
  if (P38_Mms != NULL) plat_mms_set_state(P38_Mms, 0);
}

int32_t P38_UpdateFrame(void) {
  if (P38_Sample != NULL && plat_sample_update(P38_Sample) == 0) {
    int32_t top = (int32_t)((0x1e0u - (uint32_t)P38_Letter * 2u) >> 1);
    int32_t rc[4] = { 0, top, 0x280, top + P38_Letter * 2 };
    if (plat_dd_blt_from(P38_Dest, rc, P38_Src) == 0) return 1;
  }
  return 0;
}

void P38_FmvRelease(void) {
  if (P38_Src != NULL) { plat_dd_release(P38_Src); P38_Src = NULL; }
  if (P38_Obj824 != NULL) { plat_dd_release(P38_Obj824); P38_Obj824 = NULL; }
  if (P38_Dest != NULL) {
    plat_dd_fill_all(P38_Dest, 0);
    plat_dd_release(P38_Dest); P38_Dest = NULL;
  }
  if (P38_DD != NULL) {
    plat_dd_set_cooperative(P38_DD, NULL, 8);
    plat_dd_release(P38_DD); P38_DD = NULL;
  }
  if (P38_Obj814 != NULL) { plat_dd_release(P38_Obj814); P38_Obj814 = NULL; }
}

void P38_FmvStop(void) {
  if (P38_Mms2 != NULL) plat_mms_set_state(P38_Mms2, 0);
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

void P38_SetPrimaryFormat(int32_t bits, int32_t rate) {
  if (P38_DsPrimary == NULL) return;
  P38_Wfx w = { 1, 2, (uint32_t)rate, (uint32_t)(rate * 2 * (bits / 8)), (uint16_t)((bits * 2) / 8), (uint16_t)bits, 0 };
  plat_ds_set_format(P38_DsPrimary, &w);
}

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
