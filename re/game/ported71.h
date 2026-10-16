#pragma once
#include "gvar.h"
#include "unported.h"
#include "engine.h"
#include "crt.h"
#include "ported7.h"
#include "ported8.h"
#include "ported42.h"
#include "ported44.h"
#include "ported62.h"
#include "ported69.h"
#include <stdint.h>
/* Шаг D: 8 функций частиц/радара — выбор края карты для частицы (два варианта), курс частицы, проверка четырёх полуплоскостей,
   курс «лицом к машине», поиск частиц рядом с машиной, счёт частиц в круге, сброс данных таблицы рекордов. Все cdecl.
   Частица — запись 0xb4 в 64-элементной таблице 00c56780 (+0xc флаги, +0x38 край 1/2/4/8, +0x84/+0x8c позиция float).
   Размер клетки карты 0x5dc (1500). */
#define P71_Near      GAME_VAR(int32_t, P71_Near, 0x00c59480)   /* радиус счёта частиц (квадрат) */
#define P71_NearAdd   GAME_VAR(int32_t, P71_NearAdd, 0x00c56708)/* случайная добавка 0/1500/3000/4500 */
#define P71_Tab974    GAME_VAR(int32_t, P71_Tab974, 0x00b32974)
#define P71_Tab2A40   GAME_VAR(int32_t, P71_Tab2A40, 0x00b52a40)
#define P71_Ptr2A08   GAME_VAR(uint32_t, P71_Ptr2A08, 0x00b32a08)  /* 32-битный адрес 01271088 или 0 */
#define P71_V2A24     GAME_VAR(int32_t, P71_V2A24, 0x00b32a24)
#define P71_V2A20     GAME_VAR(int32_t, P71_V2A20, 0x00b32a20)
#define P71_V2A1C     GAME_VAR(int32_t, P71_V2A1C, 0x00b32a1c)
#define P71_V2A14     GAME_VAR(int32_t, P71_V2A14, 0x00b32a14)
#define P71_S1271084  GAME_VAR(int32_t, P71_S1271084, 0x01271084)
#define P71_S1271080  GAME_VAR(int32_t, P71_S1271080, 0x01271080)
#define P71_S127107C  GAME_VAR(int32_t, P71_S127107C, 0x0127107c)
#define P71_S1271074  GAME_VAR(int32_t, P71_S1271074, 0x01271074)
#define P71_S127109C  GAME_VAR(int32_t, P71_S127109C, 0x0127109c)
#define P71_S1271098  GAME_VAR(int32_t, P71_S1271098, 0x01271098)
#define P71_S1271094  GAME_VAR(int32_t, P71_S1271094, 0x01271094)
#define P71_S127108C  GAME_VAR(int32_t, P71_S127108C, 0x0127108c)
#ifndef RE_HOOK_BUILD
#pragma push_macro("P71_Near") /*gvi*/
#undef P71_Near /*gvi*/
#pragma push_macro("P71_NearAdd") /*gvi*/
#undef P71_NearAdd /*gvi*/
#pragma push_macro("P71_Tab974") /*gvi*/
#undef P71_Tab974 /*gvi*/
#pragma push_macro("P71_Tab2A40") /*gvi*/
#undef P71_Tab2A40 /*gvi*/
#pragma push_macro("P71_V2A24") /*gvi*/
#undef P71_V2A24 /*gvi*/
#pragma push_macro("P71_V2A20") /*gvi*/
#undef P71_V2A20 /*gvi*/
#pragma push_macro("P71_V2A1C") /*gvi*/
#undef P71_V2A1C /*gvi*/
#pragma push_macro("P71_V2A14") /*gvi*/
#undef P71_V2A14 /*gvi*/
#pragma push_macro("P71_S1271084") /*gvi*/
#undef P71_S1271084 /*gvi*/
#pragma push_macro("P71_S1271080") /*gvi*/
#undef P71_S1271080 /*gvi*/
extern int32_t P71_Near, P71_NearAdd, P71_Tab974, P71_Tab2A40, P71_V2A24, P71_V2A20, P71_V2A1C, P71_V2A14, P71_S1271084, P71_S1271080,
#pragma pop_macro("P71_S1271080") /*gvi*/
#pragma pop_macro("P71_S1271084") /*gvi*/
#pragma pop_macro("P71_V2A14") /*gvi*/
#pragma pop_macro("P71_V2A1C") /*gvi*/
#pragma pop_macro("P71_V2A20") /*gvi*/
#pragma pop_macro("P71_V2A24") /*gvi*/
#pragma pop_macro("P71_Tab2A40") /*gvi*/
#pragma pop_macro("P71_Tab974") /*gvi*/
#pragma pop_macro("P71_NearAdd") /*gvi*/
#pragma pop_macro("P71_Near") /*gvi*/
    P71_S127107C, P71_S1271074, P71_S127109C, P71_S1271098, P71_S1271094, P71_S127108C;
#pragma push_macro("P71_Ptr2A08") /*gvi*/
#undef P71_Ptr2A08 /*gvi*/
extern uint32_t P71_Ptr2A08;
#pragma pop_macro("P71_Ptr2A08") /*gvi*/
#endif
void    P71_EdgeA(uint8_t *p, float *q);                    /* 005144d4: по краю p+0x38 сдвинуть q[0]/q[2] за клетку; флаг 0x100 по проходимости соседней клетки */
void    P71_EdgeB(uint8_t *p, float *q);                    /* 00514779: то же, но только позиция q[0]/q[2] */
void    P71_Course(uint8_t *p);                             /* 00514165: курс частицы к началу координат: p+0x14 угол, p+0x18 модуль разности, флаг 0x1000/0x2000 */
int32_t P71_InPlanes(const uint8_t *p, const float *q);     /* 00515bf1: 1, если позиция частицы (x,z) за 4 полуплоскостями q[0..15] */
int32_t P71_FaceCar(const uint8_t *p, const uint8_t *car);  /* 00515cca: курс частицы относительно машины ±0x400 */
void    P71_InitNear(uint8_t *car);                         /* 0051551e: инициализировать частицы рядом с машиной (дистанция < 0x2ef) */
int32_t P71_CountNear(int32_t x, int32_t z);                /* 0051380b: сколько частиц в круге; 0 — выбрать новую случайную добавку */
void    P71_ScoreSetup(void);                               /* 00503c03: сброс данных таблицы рекордов экрана и выбор таблиц по режиму 01271060 */
/* gvar-img v2.03 begin (tools/gen_gvar_img.py) */
#if !defined(RE_HOOK_BUILD) && !defined(RE_GVAR_PLAIN)
#undef P71_Near
#define P71_Near (*(int32_t *)re_gvar(0x00c59480u, sizeof(int32_t), (void *)&P71_Near))
#undef P71_NearAdd
#define P71_NearAdd (*(int32_t *)re_gvar(0x00c56708u, sizeof(int32_t), (void *)&P71_NearAdd))
#undef P71_Tab974
#define P71_Tab974 (*(int32_t *)re_gvar(0x00b32974u, sizeof(int32_t), (void *)&P71_Tab974))
#undef P71_Tab2A40
#define P71_Tab2A40 (*(int32_t *)re_gvar(0x00b52a40u, sizeof(int32_t), (void *)&P71_Tab2A40))
#undef P71_Ptr2A08
#define P71_Ptr2A08 (*(uint32_t *)re_gvar(0x00b32a08u, sizeof(uint32_t), (void *)&P71_Ptr2A08))
#undef P71_V2A24
#define P71_V2A24 (*(int32_t *)re_gvar(0x00b32a24u, sizeof(int32_t), (void *)&P71_V2A24))
#undef P71_V2A20
#define P71_V2A20 (*(int32_t *)re_gvar(0x00b32a20u, sizeof(int32_t), (void *)&P71_V2A20))
#undef P71_V2A1C
#define P71_V2A1C (*(int32_t *)re_gvar(0x00b32a1cu, sizeof(int32_t), (void *)&P71_V2A1C))
#undef P71_V2A14
#define P71_V2A14 (*(int32_t *)re_gvar(0x00b32a14u, sizeof(int32_t), (void *)&P71_V2A14))
#undef P71_S1271084
#define P71_S1271084 (*(int32_t *)re_gvar(0x01271084u, sizeof(int32_t), (void *)&P71_S1271084))
#undef P71_S1271080
#define P71_S1271080 (*(int32_t *)re_gvar(0x01271080u, sizeof(int32_t), (void *)&P71_S1271080))
#undef P71_S127107C
#define P71_S127107C (*(int32_t *)re_gvar(0x0127107cu, sizeof(int32_t), (void *)&P71_S127107C))
#undef P71_S1271074
#define P71_S1271074 (*(int32_t *)re_gvar(0x01271074u, sizeof(int32_t), (void *)&P71_S1271074))
#undef P71_S127109C
#define P71_S127109C (*(int32_t *)re_gvar(0x0127109cu, sizeof(int32_t), (void *)&P71_S127109C))
#undef P71_S1271098
#define P71_S1271098 (*(int32_t *)re_gvar(0x01271098u, sizeof(int32_t), (void *)&P71_S1271098))
#undef P71_S1271094
#define P71_S1271094 (*(int32_t *)re_gvar(0x01271094u, sizeof(int32_t), (void *)&P71_S1271094))
#undef P71_S127108C
#define P71_S127108C (*(int32_t *)re_gvar(0x0127108cu, sizeof(int32_t), (void *)&P71_S127108C))
#endif
/* gvar-img v2.03 end */
