#pragma once
#include <stdint.h>
#include "gvar.h"
/* v1.65: ported120 — новые переменные (вне native-таблиц) */
#define P120_ScrA     GAME_VAR(int32_t, P120_ScrA, 0x00d12420)    /* сбрасываются в 004cd875 */
#define P120_ScrB     GAME_VAR(int32_t, P120_ScrB, 0x00d14ee8)
#define P120_ScrC     GAME_VAR(int32_t, P120_ScrC, 0x00d164e8)
#define P120_ScrD     GAME_VAR(int32_t, P120_ScrD, 0x00d17ae8)
#define P120_ScrE     GAME_VAR(int32_t, P120_ScrE, 0x00d17b00)
#define P120_ScrSeed  GAME_VAR(int32_t, P120_ScrSeed, 0x00d17af0) /* rand() & 0xff */
#define P120_DbgOn    GAME_VAR(int32_t, P120_DbgOn, 0x00c8127c)   /* показ отладочной информации 004f60b7 */
#define P120_ConeN    GAME_VAR(int32_t, P120_ConeN, 0x00b31f44)   /* число записанных конусов (до 100) */
#define P120_ConeTick GAME_VAR(uint16_t, P120_ConeTick, 0x00b31f48)
#define P120_HudA     GAME_VAR(int32_t, P120_HudA, 0x00c808f8)    /* значения HUD времени/счёта 005032ce */
#define P120_HudB     GAME_VAR(int32_t, P120_HudB, 0x00c80934)
#ifndef RE_HOOK_BUILD
extern int32_t P120_ScrA, P120_ScrB, P120_ScrC, P120_ScrD, P120_ScrE, P120_ScrSeed, P120_DbgOn, P120_ConeN, P120_HudA, P120_HudB;
extern uint16_t P120_ConeTick;
#endif
void    P120_ObjBShade(uint8_t *obj, float x, float y, float z, int16_t kind, int16_t b);  /* 004af93c */
void    P120_ScriptReset(int32_t *p);                                                     /* 004cd875 */
void    P120_CarDebris(int32_t i, int32_t h);                                             /* 004ad6f5 */
void    P120_CarSmoke(int32_t i, int32_t dist);                                           /* 004afe3c */
void    P120_CarSparks(int32_t i);                                                        /* 004b00ad */
void    P120_DebugInfo(void);                                                             /* 004f60b7 */
int32_t P120_ParseCamInt(char **pp, int32_t which, int32_t mode);                        /* 004a4d84 */
void    P120_ConeRec(void);                                                               /* 004fbeb2 */
void    P120_HudTimes(void);                                                              /* 005032ce */
