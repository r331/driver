/* v1.58, ported113 — восстановлено из Game.exe. Все функции cdecl (ret без операнда проверен work/rets.py).
   005129e1 — отрисовка частицы-модели по пути (кадр пути P54_Tab4[тип-1]; при флаге 0x80 — интерполяция к кадру 0
              пути P54_Tab4[+4 − 1] через P12_Fn004F3E78, доля (5 − +0x40)/5), видимость SphereVis3D(800) + клетка. */
#pragma once
#include <stdint.h>
#include "gvar.h"
/* 004e969f — маркер-вертолёт 00d026a0 (P53_Mrk): mode 0 — базис из углов 00d02700/02 (матрица 00d026c0), падение/посадка,
              вращение винта 00d0270c; mode≠0 — отрисовка корпуса (00d02634) и винта (00d0263c, смещение −340/−290). */
#define P113_MrkRec   GAME_VAR(uint32_t, P113_MrkRec, 0x00c812bc)    /* адрес текущей записи скрипта (поле +0x10 — номер) */
#define P113_MrkId    GAME_VAR(int32_t, P113_MrkId, 0x00d0271c)
#define P113_MrkFall  GAME_VAR(int32_t, P113_MrkFall, 0x00d02648)
#define P113_MrkGround GAME_VAR(int32_t, P113_MrkGround, 0x00d02714)
typedef float p113_m16_t[16];
#define P113_MrkMat   GAME_VAR(p113_m16_t, P113_MrkMat, 0x00d026c0)
#ifndef RE_HOOK_BUILD
#pragma push_macro("P113_MrkRec") /*gvi*/
#undef P113_MrkRec /*gvi*/
#pragma push_macro("P113_MrkId") /*gvi*/
#undef P113_MrkId /*gvi*/
#pragma push_macro("P113_MrkFall") /*gvi*/
#undef P113_MrkFall /*gvi*/
#pragma push_macro("P113_MrkGround") /*gvi*/
#undef P113_MrkGround /*gvi*/
#pragma push_macro("P113_MrkMat") /*gvi*/
#undef P113_MrkMat /*gvi*/
extern uint32_t P113_MrkRec; extern int32_t P113_MrkId, P113_MrkFall, P113_MrkGround; extern p113_m16_t P113_MrkMat;
#pragma pop_macro("P113_MrkMat") /*gvi*/
#pragma pop_macro("P113_MrkGround") /*gvi*/
#pragma pop_macro("P113_MrkFall") /*gvi*/
#pragma pop_macro("P113_MrkId") /*gvi*/
#pragma pop_macro("P113_MrkRec") /*gvi*/
#endif
void P113_PartDraw(uint8_t *p);                                                    /* 005129e1 */
void P113_Heli(int32_t mode);
void P113_MenuOpts(void);    /* 004048dd: таблица меню опций 0057b5a8 по флагам 00bdf9e0.. (game/menu57.h) */                                                      /* 004e969f */
/* gvar-img v2.03 begin (tools/gen_gvar_img.py) */
#if !defined(RE_HOOK_BUILD) && !defined(RE_GVAR_PLAIN)
#undef P113_MrkRec
#define P113_MrkRec (*(uint32_t *)re_gvar(0x00c812bcu, sizeof(uint32_t), (void *)&P113_MrkRec))
#undef P113_MrkId
#define P113_MrkId (*(int32_t *)re_gvar(0x00d0271cu, sizeof(int32_t), (void *)&P113_MrkId))
#undef P113_MrkFall
#define P113_MrkFall (*(int32_t *)re_gvar(0x00d02648u, sizeof(int32_t), (void *)&P113_MrkFall))
#undef P113_MrkGround
#define P113_MrkGround (*(int32_t *)re_gvar(0x00d02714u, sizeof(int32_t), (void *)&P113_MrkGround))
#undef P113_MrkMat
#define P113_MrkMat (*(p113_m16_t *)re_gvar(0x00d026c0u, sizeof(p113_m16_t), (void *)&P113_MrkMat))
#endif
/* gvar-img v2.03 end */
