/* DirectSound/FMV: освобождение, сброс буферов, EAX-свойства (IKsPropertySet). */
/* ported50.c — DirectSound / FMV teardown helpers and EAX (IKsPropertySet) setup.
   All functions are cdecl (Ghidra's __thiscall label is wrong).  plat_dd_release / plat_ds_* are the
   native stand-ins for COM Release and the IDirectSoundBuffer / IKsPropertySet methods. */
#include "ported50.h"
GAME_VAR_DEF(P50_VoiceTab, P50_Voices, 0x00b1c9a0)
GAME_VAR_DEF(void *, P50_FmvA, 0x00b1c840)
GAME_VAR_DEF(void *, P50_FmvB, 0x00b1c844)
GAME_VAR_DEF(void *, P50_FmvC, 0x00b1c848)
GAME_VAR_DEF(void *, P50_FmvFlag, 0x00b1c83c)
GAME_VAR_DEF(void *, P50_Fmv834, 0x00b1c834)
GAME_VAR_DEF(void *, P50_Fmv830, 0x00b1c830)
GAME_VAR_DEF(void *, P50_Fmv82C, 0x00b1c82c)

/* GUID из .data Game.exe: 546750 (свойство 1 — слушатель EAX), 546760 (набор свойств с QuerySupport), 546370 (IID_IKsPropertySet) */
static const uint8_t g_guid_eax1[16] = { 0xc0,0x6f,0x4e,0x4a,0xc3,0x41,0xd1,0x11,0xb7,0x3a,0x44,0x45,0x53,0x54,0x00,0x00 };
static const uint8_t g_guid_eax2[16] = { 0xae,0x9b,0xa6,0x62,0x9d,0xdf,0xd1,0x11,0x99,0xa6,0x00,0xc0,0x4f,0xc9,0x9d,0x46 };
static const uint8_t g_iid_ksprop[16] = { 0x30,0xac,0xef,0x31,0x5c,0x51,0xd0,0x11,0xa9,0xaa,0x00,0xaa,0x00,0x61,0xbe,0x93 };
static const float   g_eax_minus1 = -1.0f;      /* 005511e4 */
static const int32_t g_eax_two = 2;             /* 005511e0 */

/* Release a COM-style object if present and clear the pointer (native helper, inlined in the original). */
static void rel(void **p) { if (*p != NULL) { plat_dd_release(*p); *p = NULL; } }

/* P50_FmvReleaseObjs — Game.exe 0048b568.  Releases the three FMV playback objects (A, C, B in that
   order); releasing A also clears P50_FmvFlag.  TODO(RE): unsure which DirectDraw/stream object each is. */
void P50_FmvReleaseObjs(void) {
  if (P50_FmvA != NULL) { plat_dd_release(P50_FmvA); P50_FmvA = NULL; P50_FmvFlag = NULL; }
  rel(&P50_FmvC);
  rel(&P50_FmvB);
}
/* P50_FmvStopRelease — Game.exe 0048ac0d.  Stops the FMV stream (P38_FmvStop) and releases its objects. */
void P50_FmvStopRelease(void) { P38_FmvStop(); P50_FmvReleaseObjs(); }
/* P50_FmvReleaseAll — Game.exe 0048b242.  Releases the FMV sample, the 834/830 objects and 82C.
   Quirk kept: when P38_Mms is set, P38_Mms is released *instead of* P50_Fmv82C (82C is only cleared).
   TODO(RE): unsure — 82C is probably the multimedia stream that P38_Mms was obtained from. */
void P50_FmvReleaseAll(void) {
  rel(&P38_Sample);
  rel(&P50_Fmv834);
  rel(&P50_Fmv830);
  if (P50_Fmv82C != NULL) {
    if (P38_Mms == NULL) plat_dd_release(P50_Fmv82C);
    else { plat_dd_release(P38_Mms); P38_Mms = NULL; }
    P50_Fmv82C = NULL;
  }
}
/* P50_Nop — Game.exe 0048cc5f.  Empty in the original (a stripped shutdown hook). */
void P50_Nop(void) {}
/* P50_SoundShutdown — Game.exe 0048bcc0.  Sound teardown: EAX property objects, the 3D listener,
   the primary buffer and finally the DirectSound object; all pointers end up NULL. */
void P50_SoundShutdown(void) {
  P50_Nop();
  P49_ReleaseProps();
  rel(&P49_Listener);
  rel(&P38_DsPrimary);
  rel(&P38_Ds);
}
/* P50_ReleaseVoice — Game.exe 0048c520.  Releases the two objects (+4 then +0) of voice slot idx (P50_Voices, 0x88 bytes each). */
void P50_ReleaseVoice(int32_t idx) {
  rel(&P50_Voices[idx].b);
  rel(&P50_Voices[idx].a);
}
/* P50_ReleaseBuf — Game.exe 0048c83d.  Stops sound buffer idx (P49_Bufs) and releases its 3D interface and the buffer. No-op if empty. */
void P50_ReleaseBuf(int32_t idx) {
  if (P49_Bufs[idx].buf == NULL) return;
  plat_ds_buf_stop(P49_Bufs[idx].buf);
  rel(&P49_Bufs[idx].buf3d);
  rel(&P49_Bufs[idx].buf);
}
/* P50_ResetBuf — Game.exe 0048c8d6.  Stops sound buffer idx, rewinds it to position 0, sets volume 0
   (DirectSound volume is attenuation in 1/100 dB, so 0 = full volume) and zeroes the 3D velocity. */
void P50_ResetBuf(int32_t idx) {
  if (P49_Bufs[idx].buf == NULL) return;
  plat_ds_buf_stop(P49_Bufs[idx].buf);
  plat_ds_buf_set_position(P49_Bufs[idx].buf, 0);
  plat_ds_buf_set_volume(P49_Bufs[idx].buf, 0);
  if (P49_Bufs[idx].buf3d != NULL) plat_ds3d_set_velocity_ex(P49_Bufs[idx].buf3d, 0, 0, 0, 0);
}
/* P50_EaxSetDefault — Game.exe 0048cba4.  On property set ps: Set(EAX listener property 1, -1.0f).
   TODO(RE): unsure which EAX listener property id 1 is (environment reset?). */
void P50_EaxSetDefault(void *ps) {
  if (ps != NULL) plat_ds_prop_set(ps, g_guid_eax1, 1, &g_eax_minus1, 4);
}
/* P50_EaxEnable — Game.exe 0048cbd3.  If P49_Prop30 supports both Get and Set (KSPROPERTY_SUPPORT_GET|SET
   = 1|2) of property 0 of the second EAX set, sets it to 2.  Returns 1 on success, 0 otherwise.
   TODO(RE): unsure what value 2 selects. */
int32_t P50_EaxEnable(void) {
  uint32_t sup = 0;
  if (P49_Prop30 == NULL) return 0;
  if (plat_ds_prop_support(P49_Prop30, g_guid_eax2, 0, &sup) != 0) return 0;
  if ((sup & 3) != 3) return 0;
  return plat_ds_prop_set(P49_Prop30, g_guid_eax2, 0, &g_eax_two, 4) == 0 ? 1 : 0;
}
/* P50_CreateDummyBuf — Game.exe 0048ccdd.  Creates a tiny 3D sound buffer (flags 0x12, 0x20 bytes,
   mono 16-bit 11050 Hz) into P49_Prop2C — only needed to query IKsPropertySet from it.
   Returns 1 on success; on failure releases P49_Prop2C and returns 0. */
int32_t P50_CreateDummyBuf(void) {
  /* WAVEFORMATEX: PCM, 1 канал, 11050 Гц, 22100 байт/с, выравнивание 2, 16 бит, cbSize 0 (18 байт) */
  uint8_t wfx[18] = { 1,0, 1,0, 0x2a,0x2b,0,0, 0x54,0x56,0,0, 2,0, 16,0, 0,0 };
  if (plat_ds_create_buffer(P38_Ds, 0x12, 0x20, wfx, &P49_Prop2C) != 0) { P49_ReleaseProp2C(); return 0; }
  return 1;
}
/* P50_CreateKsProps — Game.exe 0048cc64.  Creates the dummy buffer and queries IKsPropertySet into
   P49_Prop30.  Returns 1 on success; on any failure releases the dummy buffer and returns 0. */
int32_t P50_CreateKsProps(void) {
  if (!P50_CreateDummyBuf()) { P49_ReleaseProp2C(); return 0; }
  if (plat_com_query_interface(P49_Prop2C, g_iid_ksprop, &P49_Prop30) == 0) return 1;
  P49_ReleaseProp2C();
  return 0;
}
