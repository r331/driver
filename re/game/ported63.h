#pragma once
#include "gvar.h"
#include "unported.h"
#include "engine.h"
#include "ported6.h"
#include "ported11.h"
#include "ported58.h"
#include "ported59.h"
#include "director.h"
#include "ported14.h"
#include "ported19.h"
#include "ported56.h"
#include "ported8.h"
#include "ported51.h"
#include "smallfuncs2.h"
#include <stdint.h>
/* Шаг D: 10 функций — поиск и подсчёт записей трафика по узлам (таблица 0x011443e0, запись 0x54 байта),
   ближайшая запись, проверка въезда на узел, скорость машины по дистанции, четыре полуплоскости, сферы камеры, сплайны. Все cdecl. */
#define P63_Scale   GAME_VAR(float, P63_Scale, 0x00c1cc74)
#define P63_Near    GAME_VAR(int32_t, P63_Near, 0x011443c8)
typedef int32_t p63_i32x64_t[0x100];
#define P63_Dist    GAME_VAR(p63_i32x64_t, P63_Dist, 0x0113a5c0)
#define P63_Ids     GAME_VAR(p63_i32x64_t, P63_Ids, 0x01143620)
#define P63_Cnt0    GAME_VAR(int32_t, P63_Cnt0, 0x01139a40)
#define P63_Cnt1    GAME_VAR(int32_t, P63_Cnt1, 0x01139a44)
#define P63_Cnt2    GAME_VAR(int32_t, P63_Cnt2, 0x01139a48)
#define P63_Cnt3    GAME_VAR(int32_t, P63_Cnt3, 0x01139a4c)
typedef int32_t p63_i32x4_t[4];
#define P63_LimA    GAME_VAR(p63_i32x4_t, P63_LimA, 0x005512c0)
#define P63_LimB    GAME_VAR(p63_i32x4_t, P63_LimB, 0x005512d0)
#define P63_SphN    GAME_VAR(int32_t, P63_SphN, 0x01209618)
typedef int32_t p63_hits_t[0x100];
#define P63_Hits    GAME_VAR(p63_hits_t, P63_Hits, 0x011f0000)
#ifndef RE_HOOK_BUILD
extern float P63_Scale;
extern int32_t P63_Near, P63_Cnt0, P63_Cnt1, P63_Cnt2, P63_Cnt3, P63_SphN;
extern p63_i32x64_t P63_Dist, P63_Ids;
extern p63_i32x4_t P63_LimA, P63_LimB;
extern p63_hits_t P63_Hits;
#endif
void    P63_InitConsts(void);
int32_t P63_NearOnNode(uint32_t self, int32_t node, int32_t dir, int32_t alt); /* 0048ea2c: записи на узле → P63_Dist/P63_Ids */
int32_t P63_CountByNode(int32_t a, int32_t b, int32_t c, int32_t d);           /* 0048f3b4: сколько активных записей на каждом из 4 узлов */
void    P63_NearestAdd(int32_t x, int32_t z);                                  /* 0048f4ad: ближайшее манхэттенское расстояние до записей */
int32_t P63_NearestRec(void);                                                  /* 0048f5d8: индекс ближайшей активной записи к игроку */
int32_t P63_CanEnter(const uint8_t *rec);                                      /* 0048f1c6: можно ли записи трафика въехать на узел */
int32_t P63_CarSpeed(uint8_t *rec);                                            /* 004901c0: ограничение скорости записи (+0x3c) */
int32_t P63_InPlanes(const uint8_t *obj, const float *planes);                 /* 004966fd: точка (+0xc8,+0xd0) внутри четырёх полуплоскостей */
void    P63_SphereHits(const float *p, const uint8_t *obj);                    /* 00426b34: сферы, задетые точкой → P63_Hits */
void    P63_CatmullRom(const float *t, float *out, const float *p0, const float *p1, const float *p2, const float *p3); /* 0049ef12 */
void    P63_Hermite(int32_t t, float *out, int32_t a, int32_t b, int32_t c, int32_t d);       /* 0049ed20 */
