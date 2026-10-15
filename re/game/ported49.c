/* DirectSound 3D-обёртки (Sound.c): слушатель, звуковые буферы и 3D-буферы. */
#include "ported49.h"
GAME_VAR_DEF(void *, P49_Listener, 0x00b1f428)
GAME_VAR_DEF(void *, P49_Prop2C, 0x00b1f42c)
GAME_VAR_DEF(void *, P49_Prop30, 0x00b1f430)
GAME_VAR_DEF(P49_PairTab, P49_Bufs, 0x00b1c900)

void P49_Commit(void) { if (P49_Listener != NULL) plat_ds_listener_commit(P49_Listener); }
void P49_ListenerPos(float x, float y, float z) { if (P49_Listener != NULL) plat_ds_listener_set_position(P49_Listener, x, y, z); }
void P49_ListenerOrient(float fx, float fy, float fz, float ux, float uy, float uz) {
  if (P49_Listener != NULL) { float v[6] = { fx, fy, fz, ux, uy, uz }; plat_ds_listener_set_orientation(P49_Listener, v); }
}
void P49_ListenerVel(float x, float y, float z) { if (P49_Listener != NULL) plat_ds_listener_set_velocity(P49_Listener, x, y, z); }

void P49_SetVolume(int32_t idx, int32_t vol) { if (P49_Bufs[idx].buf != NULL) plat_ds_buf_set_volume(P49_Bufs[idx].buf, vol); }
void P49_SetFreq(int32_t idx, uint32_t hz) { if (P49_Bufs[idx].buf != NULL) plat_ds_buf_set_frequency(P49_Bufs[idx].buf, hz); }
void P49_GetStatus(int32_t idx, uint32_t *status) { if (P49_Bufs[idx].buf != NULL) plat_ds_buf_get_status(P49_Bufs[idx].buf, status); }
void P49_SetMode3D(int32_t idx, uint32_t mode) { if (P49_Bufs[idx].buf3d != NULL) plat_ds3d_set_mode(P49_Bufs[idx].buf3d, mode); }
void P49_SetPos3D(int32_t idx, float x, float y, float z) { if (P49_Bufs[idx].buf3d != NULL) plat_ds3d_set_position(P49_Bufs[idx].buf3d, x, y, z); }
void P49_SetVel3D(int32_t idx, float x, float y, float z) { if (P49_Bufs[idx].buf3d != NULL) plat_ds3d_set_velocity(P49_Bufs[idx].buf3d, x, y, z); }
int32_t P49_Play(int32_t idx, uint32_t flags) {
  if (P49_Bufs[idx].buf == NULL) return 0;
  return plat_ds_buf_play(P49_Bufs[idx].buf, flags) == 0 ? 1 : 0;
}

void P49_ReleaseProp2C(void) {
  if (P49_Prop2C != NULL) { plat_dd_release(P49_Prop2C); P49_Prop2C = NULL; }
}
void P49_ReleaseProps(void) {
  if (P49_Prop30 != NULL) { plat_dd_release(P49_Prop30); P49_Prop30 = NULL; }
  P49_ReleaseProp2C();
}
