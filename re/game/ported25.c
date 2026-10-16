/* CD-аудио и таймеры — восстановлено из Game.exe. Переносимый код: без WinAPI. */
#include "ported25.h"
#include "ported5.h"
#include "ported21.h"
#include "ported6.h"
#include "engine.h"
#include <string.h>
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P25_CdOpen")
#undef P25_CdOpen
#pragma push_macro("P25_CdOpen") /*gvi*/
#undef P25_CdOpen /*gvi*/
int32_t P25_CdOpen;
#pragma pop_macro("P25_CdOpen") /*gvi*/
#pragma pop_macro("P25_CdOpen")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P25_CdPlaying")
#undef P25_CdPlaying
#pragma push_macro("P25_CdPlaying") /*gvi*/
#undef P25_CdPlaying /*gvi*/
int32_t P25_CdPlaying;
#pragma pop_macro("P25_CdPlaying") /*gvi*/
#pragma pop_macro("P25_CdPlaying")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P25_CdTrack")
#undef P25_CdTrack
#pragma push_macro("P25_CdTrack") /*gvi*/
#undef P25_CdTrack /*gvi*/
int32_t P25_CdTrack;
#pragma pop_macro("P25_CdTrack") /*gvi*/
#pragma pop_macro("P25_CdTrack")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P25_CdTracks")
#undef P25_CdTracks
#pragma push_macro("P25_CdTracks") /*gvi*/
#undef P25_CdTracks /*gvi*/
int32_t P25_CdTracks;
#pragma pop_macro("P25_CdTracks") /*gvi*/
#pragma pop_macro("P25_CdTracks")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P25_AuxDev")
#undef P25_AuxDev
#pragma push_macro("P25_AuxDev") /*gvi*/
#undef P25_AuxDev /*gvi*/
int32_t P25_AuxDev;
#pragma pop_macro("P25_AuxDev") /*gvi*/
#pragma pop_macro("P25_AuxDev")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P25_TimerCnt")
#undef P25_TimerCnt
#pragma push_macro("P25_TimerCnt") /*gvi*/
#undef P25_TimerCnt /*gvi*/
int32_t P25_TimerCnt;
#pragma pop_macro("P25_TimerCnt") /*gvi*/
#pragma pop_macro("P25_TimerCnt")
#endif

static uint32_t g_tocPos[21], g_tocEnd[21];   /* TOC дорожек (в оригинале пары по 8 байт с b91c20) */
static uint32_t g_curEnd;                     /* конец текущей дорожки (b91d10) */
static struct { uint32_t id; void (*cb)(void); } g_tm[4];   /* таблица таймеров (b94008) */
#define MAIN_HWND ((void *)(intptr_t)G6_00BDF9C0)

int32_t P25_GetCDTOC(void) {
  int n = plat_cd_track_count();
  if (n < 0) { DebugLog("GetCDTOC: Query # CD tracks failed"); return 0; }
  P25_CdTracks = (uint32_t)n < 0x14 ? n : 0x14;
  for (int t = 1; t <= P25_CdTracks; t++) {
    uint32_t pos = 0, len = 0;
    int r = plat_cd_track_info(t, &pos, &len);
    if (r == 1) { DebugLog("GetCDTOC: Get track position failed"); return 0; }
    g_tocPos[t] = pos;
    if (r == 2) { DebugLog("GetCDTOC: Get track length failed"); return 0; }
    g_tocEnd[t] = P21_AddMsf(pos, len);
  }
  return 1;
}
int32_t P25_InitCDAudio(void) {
  if (P25_CdOpen != 0) return 1;
  P25_AuxDev = -1;
  int r = plat_cd_open(MAIN_HWND);
  if (r == 0) { DebugLog("InitCDAudio: Open CD device failed"); return 0; }
  if (r < 0) { DebugLog("InitCDAudio: Set time format failed"); return 0; }
  P25_CdOpen = 1;
  if (P25_GetCDTOC() == 0) { plat_cd_close(); return 0; }   /* флаг «открыто» остаётся 1, как в оригинале */
  int dev = plat_aux_find_cd();
  if (dev >= 0) P25_AuxDev = dev;
  return 1;
}
void P25_CDStop(void) {
  if (P25_CdOpen != 0) { plat_cd_pause(); P25_CdPlaying = 0; }
}
void P25_CDClose(void) {
  if (P25_CdOpen == 0) return;
  if (P25_CdPlaying != 0) P25_CDStop();
  plat_cd_close();
  P25_CdOpen = 0;
}
void P25_PlayCDTrack(int32_t track) {
  if (P25_CdOpen == 0) return;
  if (track < 2 || P25_CdTracks < track) {
    DebugLog("PlayCDTrack: Invalid track number");
    Q00B87E90 = 0;
    return;
  }
  uint32_t from = g_tocPos[track];
  g_curEnd = g_tocEnd[track];
  P25_CdTrack = track;
  if (plat_cd_play_range(MAIN_HWND, from, g_curEnd)) P25_CdPlaying = 1;
  else { P25_CDClose(); Q00B87E90 = 0; }
}
void P25_CDResume(void) {
  if (P25_CdOpen != 0 && P25_CdPlaying == 0 && plat_cd_play_to(g_curEnd)) P25_CdPlaying = 1;
}
void P25_CDSetVolume(uint32_t vol) {
  if (P25_AuxDev == -1) return;
  int32_t v = (int32_t)vol;
  uint32_t c = v < 0 ? 0 : (v < 0x10000 ? (uint32_t)v : 0xffffu);
  plat_aux_set_volume(P25_AuxDev, c << 16 | c);
}

int32_t P25_TimersInit(void) {
  int r = plat_timer_period_begin(5);
  if (r == 0) P25_TimerCnt = 0; else DebugLog("<* Init Timers failed *>");
  return r == 0;
}
void P25_TimerStop(int32_t slot) {
  if (g_tm[slot].id == 0) return;
  plat_timer_kill(g_tm[slot].id);
  g_tm[slot].id = 0; g_tm[slot].cb = NULL;
  P25_TimerCnt--;
}
void P25_TimersShutdown(void) {
  for (int i = 0; i < 4; i++) P25_TimerStop(i);
  plat_timer_period_end(5);
  P25_TimerCnt = 0;
}
void P25_TimerCb(uint32_t id, uint32_t msg, uint32_t user, uint32_t a, uint32_t b) {
  (void)msg; (void)user; (void)a; (void)b;
  for (int i = 0; i < 4; i++)
    if (g_tm[i].id == id && g_tm[i].cb != NULL) { g_tm[i].cb(); return; }
}
static void timer_tramp(unsigned id) { P25_TimerCb(id, 0, 0, 0, 0); }
int32_t P25_TimerStart(uint32_t delay, uint32_t flags, void (*cb)(void)) {
  for (int i = 0; i < 4; i++) {
    if (g_tm[i].id != 0) continue;
    g_tm[i].cb = cb;
    g_tm[i].id = plat_timer_start(delay, flags, timer_tramp);
    if (g_tm[i].id != 0) return i;
  }
  return -1;
}
