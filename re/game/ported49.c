/* ported49.c — thin DirectSound 3D wrappers from Sound.c (English overview; original notes follow).
   Every function checks that the COM object exists, then forwards one call to the platform DirectSound
   layer (plat_ds_*, plat_ds3d_*).  Objects: the 3D listener P49_Listener (00b1f428), the sound buffer
   table P49_Bufs (00b1c900, 64 pairs {buffer, 3D buffer}) and two property objects at 00b1f42c/00b1f430.
   All are cdecl in Game.exe (Ghidra's __thiscall label is wrong — checked in the disassembly). */
/* DirectSound 3D-обёртки (Sound.c): слушатель, звуковые буферы и 3D-буферы. */
#include "ported49.h"
GAME_VAR_DEF(void *, P49_Listener, 0x00b1f428)
GAME_VAR_DEF(void *, P49_Prop2C, 0x00b1f42c)
GAME_VAR_DEF(void *, P49_Prop30, 0x00b1f430)
GAME_VAR_DEF(P49_PairTab, P49_Bufs, 0x00b1c900)

/* P49_Commit — Game.exe 0048bd40.  Applies deferred 3D listener/buffer settings (CommitDeferredSettings). */
void P49_Commit(void) { if (P49_Listener != NULL) plat_ds_listener_commit(P49_Listener); }
/* P49_ListenerPos — Game.exe 0048c74b.  Sets the 3D listener position (world units as floats). */
void P49_ListenerPos(float x, float y, float z) { if (P49_Listener != NULL) plat_ds_listener_set_position(P49_Listener, x, y, z); }
/* P49_ListenerOrient — Game.exe 0048c77e.  Sets the listener orientation: front vector (fx, fy, fz) and
   up vector (ux, uy, uz). */
void P49_ListenerOrient(float fx, float fy, float fz, float ux, float uy, float uz) {
  if (P49_Listener != NULL) { float v[6] = { fx, fy, fz, ux, uy, uz }; plat_ds_listener_set_orientation(P49_Listener, v); }
}
/* P49_ListenerVel — Game.exe 0048c7bd.  Sets the listener velocity (used for Doppler). */
void P49_ListenerVel(float x, float y, float z) { if (P49_Listener != NULL) plat_ds_listener_set_velocity(P49_Listener, x, y, z); }

/* P49_SetVolume — Game.exe 0048c97c.  Sets buffer idx volume (DirectSound hundredths of a dB, 0 = full). */
void P49_SetVolume(int32_t idx, int32_t vol) { if (P49_Bufs[idx].buf != NULL) plat_ds_buf_set_volume(P49_Bufs[idx].buf, vol); }
/* P49_SetFreq — Game.exe 0048c9b2.  Sets buffer idx playback frequency in Hz. */
void P49_SetFreq(int32_t idx, uint32_t hz) { if (P49_Bufs[idx].buf != NULL) plat_ds_buf_set_frequency(P49_Bufs[idx].buf, hz); }
/* P49_GetStatus — Game.exe 0048caa0.  Reads buffer idx status flags (DSBSTATUS_*) into *status;
   leaves *status untouched when the buffer does not exist. */
void P49_GetStatus(int32_t idx, uint32_t *status) { if (P49_Bufs[idx].buf != NULL) plat_ds_buf_get_status(P49_Bufs[idx].buf, status); }
/* P49_SetMode3D — Game.exe 0048ca68.  Sets the 3D processing mode of buffer idx (DS3DMODE_*). */
void P49_SetMode3D(int32_t idx, uint32_t mode) { if (P49_Bufs[idx].buf3d != NULL) plat_ds3d_set_mode(P49_Bufs[idx].buf3d, mode); }
/* P49_SetPos3D — Game.exe 0048c9e8.  Sets the 3D position of sound source idx. */
void P49_SetPos3D(int32_t idx, float x, float y, float z) { if (P49_Bufs[idx].buf3d != NULL) plat_ds3d_set_position(P49_Bufs[idx].buf3d, x, y, z); }
/* P49_SetVel3D — Game.exe 0048ca28.  Sets the 3D velocity of sound source idx. */
void P49_SetVel3D(int32_t idx, float x, float y, float z) { if (P49_Bufs[idx].buf3d != NULL) plat_ds3d_set_velocity(P49_Bufs[idx].buf3d, x, y, z); }
/* P49_Play — Game.exe 0048c7f0.  Starts buffer idx (flags: DSBPLAY_*, e.g. looping).
   Returns 1 on success, 0 if the buffer is missing or Play failed. */
int32_t P49_Play(int32_t idx, uint32_t flags) {
  if (P49_Bufs[idx].buf == NULL) return 0;
  return plat_ds_buf_play(P49_Bufs[idx].buf, flags) == 0 ? 1 : 0;
}

/* P49_ReleaseProp2C — Game.exe 0048cd82.  Releases the COM object at 00b1f42c and clears the pointer.
   TODO(RE): unsure what object this is (named "Prop" after its position next to the listener). */
void P49_ReleaseProp2C(void) {
  if (P49_Prop2C != NULL) { plat_dd_release(P49_Prop2C); P49_Prop2C = NULL; }
}
/* P49_ReleaseProps — Game.exe 0048ccaf.  Releases the object at 00b1f430, then the one at 00b1f42c. */
void P49_ReleaseProps(void) {
  if (P49_Prop30 != NULL) { plat_dd_release(P49_Prop30); P49_Prop30 = NULL; }
  P49_ReleaseProp2C();
}
