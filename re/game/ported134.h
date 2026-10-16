#pragma once
#include <stdint.h>
#include "gvar.h"
/* v1.79: ported134 — столкновение камеры со зданиями 0049cad4, камера за машиной 0049d84a, камера на цель 0049e16c,
   камера ролика точки появления 004f0f90, удержание машины трафика 00494620 (обработчик 5 .data 00551308).
   Все функции cdecl (work/rets.py: ret без операнда). */
typedef float p134_v3_t[3];
#define P134_Cine0   GAME_VAR(p134_v3_t, P134_Cine0, 0x00c82420)   /* 004f0f90: начальная точка камеры ролика (x, y, z) */
#define P134_Cine1   GAME_VAR(p134_v3_t, P134_Cine1, 0x00c824f0)   /* 004f0f90: конечная точка камеры ролика */
#define P134_ScaleB  GAME_VAR(float, P134_ScaleB, 0x00c82520)      /* 004f0f90: масштаб 01251a64 в начале ролика */
#define P134_ScaleE  GAME_VAR(float, P134_ScaleE, 0x00c824dc)      /* 004f0f90: масштаб в конце ролика */
#ifndef RE_HOOK_BUILD
#pragma push_macro("P134_Cine0") /*gvi*/
#undef P134_Cine0 /*gvi*/
#pragma push_macro("P134_Cine1") /*gvi*/
#undef P134_Cine1 /*gvi*/
extern p134_v3_t P134_Cine0, P134_Cine1;
#pragma pop_macro("P134_Cine1") /*gvi*/
#pragma pop_macro("P134_Cine0") /*gvi*/
#pragma push_macro("P134_ScaleB") /*gvi*/
#undef P134_ScaleB /*gvi*/
#pragma push_macro("P134_ScaleE") /*gvi*/
#undef P134_ScaleE /*gvi*/
extern float P134_ScaleB, P134_ScaleE;
#pragma pop_macro("P134_ScaleE") /*gvi*/
#pragma pop_macro("P134_ScaleB") /*gvi*/
#endif
int32_t P134_CamCollide(int32_t ground); /* 0049cad4: выталкивание камеры из коробок моделей клетки; 1 — было касание */
void    P134_CamChase(int32_t car);      /* 0049d84a: камера за машиной car (поворот 01136c58, дистанция 01137368) */
void    P134_CamTarget(int32_t car);     /* 0049e16c: камера в 01136c70 смотрит на машину car (−1 — углы 011373b8) */
void    P134_CamCine(void);              /* 004f0f90: камера ролика точки появления (00c824a0) */
void    P134_TrafficHold(uint8_t *rec);  /* 00494620: запись трафика — счётчик +0xb, иначе переход в тип 2 */
/* gvar-img v2.03 begin (tools/gen_gvar_img.py) */
#if !defined(RE_HOOK_BUILD) && !defined(RE_GVAR_PLAIN)
#undef P134_Cine0
#define P134_Cine0 (*(p134_v3_t *)re_gvar(0x00c82420u, sizeof(p134_v3_t), (void *)&P134_Cine0))
#undef P134_Cine1
#define P134_Cine1 (*(p134_v3_t *)re_gvar(0x00c824f0u, sizeof(p134_v3_t), (void *)&P134_Cine1))
#undef P134_ScaleB
#define P134_ScaleB (*(float *)re_gvar(0x00c82520u, sizeof(float), (void *)&P134_ScaleB))
#undef P134_ScaleE
#define P134_ScaleE (*(float *)re_gvar(0x00c824dcu, sizeof(float), (void *)&P134_ScaleE))
#endif
/* gvar-img v2.03 end */
