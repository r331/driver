#pragma once
#include "gvar.h"
#include "../platform/plat.h"
#include <stdint.h>
/* CD-аудио (InitCDAudio/PlayCDTrack/GetCDTOC и др.) и мультимедиа-таймеры игры — над plat_cd_* / plat_timer_*. Все функции __cdecl,
   кроме колбэка таймера (stdcall, ret 0x14; в hook-сборке через переходник). */
#define P25_CdOpen    GAME_VAR(int32_t, P25_CdOpen, 0x00b91cfc)     /* устройство открыто */
#define P25_CdPlaying GAME_VAR(int32_t, P25_CdPlaying, 0x00b91d38)  /* идёт воспроизведение */
#define P25_CdTrack   GAME_VAR(int32_t, P25_CdTrack, 0x00b91d3c)    /* текущая дорожка */
#define P25_CdTracks  GAME_VAR(int32_t, P25_CdTracks, 0x00b91d18)   /* число дорожек (<= 20) */
#define P25_AuxDev    GAME_VAR(int32_t, P25_AuxDev, 0x0057647c)     /* aux-устройство CD или -1 */
#define P25_TimerCnt  GAME_VAR(int32_t, P25_TimerCnt, 0x00b94028)   /* счётчик таймеров */
#ifndef RE_HOOK_BUILD
#pragma push_macro("P25_CdOpen") /*gvi*/
#undef P25_CdOpen /*gvi*/
#pragma push_macro("P25_CdPlaying") /*gvi*/
#undef P25_CdPlaying /*gvi*/
#pragma push_macro("P25_CdTrack") /*gvi*/
#undef P25_CdTrack /*gvi*/
#pragma push_macro("P25_CdTracks") /*gvi*/
#undef P25_CdTracks /*gvi*/
#pragma push_macro("P25_AuxDev") /*gvi*/
#undef P25_AuxDev /*gvi*/
#pragma push_macro("P25_TimerCnt") /*gvi*/
#undef P25_TimerCnt /*gvi*/
extern int32_t P25_CdOpen, P25_CdPlaying, P25_CdTrack, P25_CdTracks, P25_AuxDev, P25_TimerCnt;
#pragma pop_macro("P25_TimerCnt") /*gvi*/
#pragma pop_macro("P25_AuxDev") /*gvi*/
#pragma pop_macro("P25_CdTracks") /*gvi*/
#pragma pop_macro("P25_CdTrack") /*gvi*/
#pragma pop_macro("P25_CdPlaying") /*gvi*/
#pragma pop_macro("P25_CdOpen") /*gvi*/
#endif
int32_t  P25_GetCDTOC(void);                         /* 00524f97 */
int32_t  P25_InitCDAudio(void);                      /* 00524611 */
void     P25_CDClose(void);                          /* 00524763 */
void     P25_PlayCDTrack(int32_t track);             /* 0052479e */
void     P25_CDStop(void);                           /* 00524873 (дубль 005248a0) */
void     P25_CDResume(void);                         /* 005248cd */
void     P25_CDSetVolume(uint32_t vol);              /* 00524917 */
int32_t  P25_TimersInit(void);                       /* 005281b0 */
void     P25_TimersShutdown(void);                   /* 005281e1 */
int32_t  P25_TimerStart(uint32_t delay, uint32_t flags, void (*cb)(void)); /* 00528221 */
void     P25_TimerStop(int32_t slot);                /* 00528293 */
void     P25_TimerCb(uint32_t id, uint32_t msg, uint32_t user, uint32_t a, uint32_t b); /* 005282e1, stdcall */
/* gvar-img v2.03 begin (tools/gen_gvar_img.py) */
#if !defined(RE_HOOK_BUILD) && !defined(RE_GVAR_PLAIN)
#undef P25_CdOpen
#define P25_CdOpen (*(int32_t *)re_gvar(0x00b91cfcu, sizeof(int32_t), (void *)&P25_CdOpen))
#undef P25_CdPlaying
#define P25_CdPlaying (*(int32_t *)re_gvar(0x00b91d38u, sizeof(int32_t), (void *)&P25_CdPlaying))
#undef P25_CdTrack
#define P25_CdTrack (*(int32_t *)re_gvar(0x00b91d3cu, sizeof(int32_t), (void *)&P25_CdTrack))
#undef P25_CdTracks
#define P25_CdTracks (*(int32_t *)re_gvar(0x00b91d18u, sizeof(int32_t), (void *)&P25_CdTracks))
#undef P25_AuxDev
#define P25_AuxDev (*(int32_t *)re_gvar(0x0057647cu, sizeof(int32_t), (void *)&P25_AuxDev))
#undef P25_TimerCnt
#define P25_TimerCnt (*(int32_t *)re_gvar(0x00b94028u, sizeof(int32_t), (void *)&P25_TimerCnt))
#endif
/* gvar-img v2.03 end */
