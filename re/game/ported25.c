/* CD-аудио и таймеры — восстановлено из Game.exe. Переносимый код: без WinAPI. */
/* ported25.c — CD audio (MCI in the original: InitCDAudio / GetCDTOC / PlayCDTrack ...) and the
   game's multimedia timers, written over the portable plat_cd_* / plat_aux_* / plat_timer_* layer
   (native: CD emulation from music files, see plat_cdaudio.c).  All functions cdecl.
   Track positions are MCI MSF values (P21_AddMsf adds them); track 1 is the data track, so music
   tracks are 2..P25_CdTracks. */
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
#define CD_MAX_TRACKS   0x14   /* TOC holds at most 20 tracks (array index 1..20) */
#define CD_FIRST_MUSIC  2      /* track 1 is the game's data track */
#define TIMER_SLOTS     4      /* entries of the timer table g_tm (b94008) */
#define TIMER_RES_MS    5      /* timeBeginPeriod / timeEndPeriod resolution, ms */

/* P25_GetCDTOC — Game.exe 00524f97.  Reads the CD table of contents: track count (clamped to 20) into
   P25_CdTracks, and for each track its start (g_tocPos) and end = start + length (g_tocEnd).
   Returns 1 on success; logs and returns 0 on the first failing query. */
int32_t P25_GetCDTOC(void) {
  int n = plat_cd_track_count();
  if (n < 0) { DebugLog("GetCDTOC: Query # CD tracks failed"); return 0; }
  P25_CdTracks = (uint32_t)n < CD_MAX_TRACKS ? n : CD_MAX_TRACKS;
  for (int t = 1; t <= P25_CdTracks; t++) {
    uint32_t pos = 0, len = 0;
    int r = plat_cd_track_info(t, &pos, &len);   /* 0 ok, 1 position failed, 2 length failed (pos valid) */
    if (r == 1) { DebugLog("GetCDTOC: Get track position failed"); return 0; }
    g_tocPos[t] = pos;
    if (r == 2) { DebugLog("GetCDTOC: Get track length failed"); return 0; }
    g_tocEnd[t] = P21_AddMsf(pos, len);
  }
  return 1;
}
/* P25_InitCDAudio — Game.exe 00524611.  Opens the CD device (MSF time format) once and reads the TOC;
   also looks up the CD aux device for volume control (P25_AuxDev, -1 = none).
   Returns 1 if open (or already open), 0 on failure.  Quirk: if the TOC read fails the device is closed
   but P25_CdOpen stays 1, as in the original. */
int32_t P25_InitCDAudio(void) {
  if (P25_CdOpen != 0) return 1;
  P25_AuxDev = -1;
  int r = plat_cd_open(MAIN_HWND);   /* 1 ok, 0 open failed, < 0 set-time-format failed */
  if (r == 0) { DebugLog("InitCDAudio: Open CD device failed"); return 0; }
  if (r < 0) { DebugLog("InitCDAudio: Set time format failed"); return 0; }
  P25_CdOpen = 1;
  if (P25_GetCDTOC() == 0) { RE_LOGW(audio, "CD-audio: оглавление диска не прочитано"); plat_cd_close(); return 0; }   /* флаг «открыто» остаётся 1, как в оригинале */
  int dev = plat_aux_find_cd();
  if (dev >= 0) P25_AuxDev = dev;
  RE_LOGI(audio, "CD-audio открыт: дорожек %d, aux-устройство %d", (int)P25_CdTracks, dev);
  return 1;
}
/* P25_CDStop — Game.exe 00524873 (identical copy at 005248a0).  Stops CD playback (MCI_STOP; the
   position is kept, so P25_CDResume continues from it) and clears P25_CdPlaying. */
void P25_CDStop(void) {
  if (P25_CdOpen != 0) { plat_cd_pause(); P25_CdPlaying = 0; }
}
/* P25_CDClose — Game.exe 00524763.  Stops playback if running and closes the CD device. */
void P25_CDClose(void) {
  if (P25_CdOpen == 0) return;
  if (P25_CdPlaying != 0) P25_CDStop();
  plat_cd_close();
  P25_CdOpen = 0;
}
/* P25_PlayCDTrack — Game.exe 0052479e.  Plays one whole track (from its TOC start to its end; the end
   is remembered in g_curEnd for P25_CDResume).  An invalid track (< 2 or > count) logs and clears
   Q00B87E90; a failed play closes the device and clears Q00B87E90 too.
   Q00B87E90 is the "Music" On/Off entry of the Sound menu 0054dd10 (ToggleOpt0041542A, RE_PROBE menu walk). */
void P25_PlayCDTrack(int32_t track) {
  if (P25_CdOpen == 0) return;
  if (track < CD_FIRST_MUSIC || P25_CdTracks < track) {
    DebugLog("PlayCDTrack: Invalid track number");
    Q00B87E90 = 0;
    return;
  }
  uint32_t from = g_tocPos[track];
  g_curEnd = g_tocEnd[track];
  P25_CdTrack = track;
  RE_LOGI(audio, "музыка: CD-трек %d (из %d)", (int)track, (int)P25_CdTracks);
  if (plat_cd_play_range(MAIN_HWND, from, g_curEnd)) P25_CdPlaying = 1;
  else { RE_LOGW(audio, "музыка: CD-трек %d не запущен — CD-audio закрыт, музыка выключена", (int)track); P25_CDClose(); Q00B87E90 = 0; }
}
/* P25_CDResume — Game.exe 005248cd.  Resumes a paused track: plays from the current position to g_curEnd. */
void P25_CDResume(void) {
  if (P25_CdOpen != 0 && P25_CdPlaying == 0 && plat_cd_play_to(g_curEnd)) P25_CdPlaying = 1;
}
/* P25_CDSetVolume — Game.exe 00524917.  Sets the CD aux volume: vol clamped (as signed) to 0..0xffff,
   written to both channels (auxSetVolume packs left in the low word, right in the high word). */
void P25_CDSetVolume(uint32_t vol) {
  if (P25_AuxDev == -1) return;
  int32_t v = (int32_t)vol;
  uint32_t c = v < 0 ? 0 : (v < 0x10000 ? (uint32_t)v : 0xffffu);
  plat_aux_set_volume(P25_AuxDev, c << 16 | c);
}

/* P25_TimersInit — Game.exe 005281b0.  Sets the multimedia timer resolution to 5 ms and zeroes the
   active-timer count.  Returns 1 on success, 0 (and logs) on failure. */
int32_t P25_TimersInit(void) {
  int r = plat_timer_period_begin(TIMER_RES_MS);
  if (r == 0) P25_TimerCnt = 0; else DebugLog("<* Init Timers failed *>");
  return r == 0;
}
/* P25_TimerStop — Game.exe 00528293.  Kills the timer in table slot `slot` (if any), clears the slot
   and decrements P25_TimerCnt.  Game.exe itself never increments P25_TimerCnt (00b94028): its only accesses are
   the zeroing in 005281b0 / 005281e1 and this decrement (objdump xref), so the counter is dead in the original
   too — kept as is. */
void P25_TimerStop(int32_t slot) {
  if (g_tm[slot].id == 0) return;
  plat_timer_kill(g_tm[slot].id);
  g_tm[slot].id = 0; g_tm[slot].cb = NULL;
  P25_TimerCnt--;
}
/* P25_TimersShutdown — Game.exe 005281e1.  Stops all timer slots, restores the timer resolution and
   zeroes the count. */
void P25_TimersShutdown(void) {
  for (int i = 0; i < TIMER_SLOTS; i++) P25_TimerStop(i);
  plat_timer_period_end(TIMER_RES_MS);
  P25_TimerCnt = 0;
}
/* P25_TimerCb — Game.exe 005282e1.  timeSetEvent callback (TIMECALLBACK signature): finds the slot
   whose timer id matches and calls its callback.  Runs on the timer thread in the original. */
void P25_TimerCb(uint32_t id, uint32_t msg, uint32_t user, uint32_t a, uint32_t b) {
  (void)msg; (void)user; (void)a; (void)b;
  for (int i = 0; i < TIMER_SLOTS; i++)
    if (g_tm[i].id == id && g_tm[i].cb != NULL) { g_tm[i].cb(); return; }
}
/* Native adapter: plat_timer_start callback signature -> P25_TimerCb. */
static void timer_tramp(unsigned id) { P25_TimerCb(id, 0, 0, 0, 0); }
/* P25_TimerStart — Game.exe 00528221.  Starts a multimedia timer (delay ms, timeSetEvent flags) calling
   cb, in the first free slot.  Returns the slot index, or -1 if none is free.  Quirk kept: if starting
   fails, cb stays stored in that (still free) slot and the next slot is tried.
   TODO(RE): P25_TimerCnt is decremented by P25_TimerStop but never incremented here — check the
   original for the matching increment. */
int32_t P25_TimerStart(uint32_t delay, uint32_t flags, void (*cb)(void)) {
  for (int i = 0; i < TIMER_SLOTS; i++) {
    if (g_tm[i].id != 0) continue;
    g_tm[i].cb = cb;
    g_tm[i].id = plat_timer_start(delay, flags, timer_tramp);
    if (g_tm[i].id != 0) return i;
  }
  return -1;
}
