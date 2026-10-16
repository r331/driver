#pragma once
#include <stdint.h>
#include "gvar.h"
/* v1.82: ported137 — конец уровня, загрузка motion capture (.MCD), загрузчик FRONTEND.TSD, отрисовка машины. Все cdecl. */
typedef int32_t p137_i5_t[5];
typedef float   p137_f4_t[4];
#define P137_McdSkipA  GAME_VAR(p137_i5_t, P137_McdSkipA, 0x00b31f10)   /* число пропускаемых кадров в начале .MCD по типу */
#define P137_McdSkipB  GAME_VAR(p137_i5_t, P137_McdSkipB, 0x00b31f24)   /* число пропускаемых кадров в конце .MCD по типу */
#define P137_PathDist  GAME_VAR(p137_f4_t, P137_PathDist, 0x00c823c0)   /* длина суммарного смещения пути .MCD по типу */
#define P137_PedHeadA  GAME_VAR(int32_t, P137_PedHeadA, 0x00cf56b4)     /* PED3HEAD − PED3BASE (номер модели) */
#define P137_PedHeadB  GAME_VAR(int32_t, P137_PedHeadB, 0x00d00210)     /* PED1HEAD/PED4HEAD − PED1BASE/PED4BASE */
#ifndef RE_HOOK_BUILD
extern p137_i5_t P137_McdSkipA, P137_McdSkipB; extern p137_f4_t P137_PathDist; extern int32_t P137_PedHeadA, P137_PedHeadB;
#endif
void    P137_LevelEnd(void);                                                        /* 004d4663 */
int32_t P137_LoadMcd(const char *name, void *dst, int32_t skip_a, int32_t skip_b);  /* 004f3490: число кадров */
int32_t P137_MotionInit(void);                                                      /* 004f388e: 1 — успех */
int32_t P137_LoadTsd(const char *name);                                             /* 0040d07b: 1 — успех */
void    P137_DrawCar(int32_t car, int32_t rec);                                     /* 004a1037 */
