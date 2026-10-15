/* hook-вариант: CD-аудио (MCI cdaudio) и таймеры — прямой вызов winmm, как делал Game.exe */
#include <windows.h>
#include <mmsystem.h>
#include <string.h>
#include "../plat.h"
static UINT g_dev;
static void (*g_tcb)(unsigned);
int plat_cd_open(void *hwnd) {
  (void)hwnd;
  MCI_OPEN_PARMSA op; memset(&op, 0, sizeof op); op.lpstrDeviceType = "cdaudio";
  if (mciSendCommandA(0, MCI_OPEN, MCI_OPEN_TYPE, (DWORD_PTR)&op) != 0) return 0;
  g_dev = op.wDeviceID;
  MCI_SET_PARMS sp; memset(&sp, 0, sizeof sp); sp.dwTimeFormat = MCI_FORMAT_TMSF;
  if (mciSendCommandA(g_dev, MCI_SET, MCI_SET_TIME_FORMAT, (DWORD_PTR)&sp) != 0) { mciSendCommandA(g_dev, MCI_CLOSE, 0, 0); return -1; }
  return 1;
}
void plat_cd_close(void) { mciSendCommandA(g_dev, MCI_CLOSE, 0, 0); }
int plat_cd_track_count(void) {
  MCI_STATUS_PARMS st; memset(&st, 0, sizeof st); st.dwItem = MCI_STATUS_NUMBER_OF_TRACKS;
  if (mciSendCommandA(g_dev, MCI_STATUS, MCI_STATUS_ITEM, (DWORD_PTR)&st) != 0) return -1;
  return (int)st.dwReturn;
}
int plat_cd_track_info(int track, uint32_t *pos, uint32_t *len) {
  MCI_STATUS_PARMS st; memset(&st, 0, sizeof st);
  st.dwItem = MCI_STATUS_POSITION; st.dwTrack = (DWORD)track;
  if (mciSendCommandA(g_dev, MCI_STATUS, MCI_STATUS_ITEM | MCI_TRACK, (DWORD_PTR)&st) != 0) return 1;
  *pos = (uint32_t)st.dwReturn;
  st.dwItem = MCI_STATUS_LENGTH; st.dwTrack = (DWORD)track;
  if (mciSendCommandA(g_dev, MCI_STATUS, MCI_STATUS_ITEM | MCI_TRACK, (DWORD_PTR)&st) != 0) return 2;
  *len = (uint32_t)st.dwReturn;
  return 0;
}
int plat_cd_play_range(void *hwnd, uint32_t from, uint32_t to) {
  MCI_PLAY_PARMS pp; memset(&pp, 0, sizeof pp); pp.dwCallback = (DWORD_PTR)hwnd; pp.dwFrom = from; pp.dwTo = to;
  return mciSendCommandA(g_dev, MCI_PLAY, MCI_NOTIFY | MCI_FROM | MCI_TO, (DWORD_PTR)&pp) == 0;
}
int plat_cd_play_to(uint32_t to) {
  MCI_PLAY_PARMS pp; memset(&pp, 0, sizeof pp); pp.dwTo = to;
  return mciSendCommandA(g_dev, MCI_PLAY, MCI_TO, (DWORD_PTR)&pp) == 0;
}
void plat_cd_pause(void) { mciSendCommandA(g_dev, MCI_STOP, 0, 0); }
int plat_aux_find_cd(void) {
  UINT n = auxGetNumDevs();
  for (UINT i = 0; (int)i < (int)n; i++) {
    AUXCAPSA caps; memset(&caps, 0, sizeof caps);
    auxGetDevCapsA(i, &caps, sizeof caps);
    if (caps.wTechnology == 1 /* AUXCAPS_CDAUDIO */) return (int)i;
  }
  return -1;
}
void plat_aux_set_volume(int dev, uint32_t lr) { auxSetVolume((UINT)dev, lr); }
int plat_timer_period_begin(unsigned ms) { return timeBeginPeriod(ms) != 0; }
void plat_timer_period_end(unsigned ms) { timeEndPeriod(ms); }
static void CALLBACK tramp(UINT id, UINT m, DWORD_PTR u, DWORD_PTR a, DWORD_PTR b) { (void)m; (void)u; (void)a; (void)b; if (g_tcb) g_tcb(id); }
unsigned plat_timer_start(unsigned delay, unsigned flags, void (*cb)(unsigned)) {
  g_tcb = cb;
  return (unsigned)timeSetEvent(delay, 5, tramp, 0, flags);
}
void plat_timer_kill(unsigned id) { timeKillEvent(id); }
void plat_cd_stub_set(int n, int aux) { (void)n; (void)aux; }
int plat_cd_stub_state(uint32_t *f, uint32_t *t, uint32_t *v) { *f = *t = *v = 0; return 0; }
