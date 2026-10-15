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
extern int32_t P25_CdOpen, P25_CdPlaying, P25_CdTrack, P25_CdTracks, P25_AuxDev, P25_TimerCnt;
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
