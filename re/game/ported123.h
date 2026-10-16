#pragma once
#include <stdint.h>
#include "gvar.h"
/* v1.68: ported123 — новые переменные (вне native-таблиц) */
typedef int32_t p123_glowcars_t[65];
#define P123_GlowN     GAME_VAR(int32_t, P123_GlowN, 0x0112320c)          /* число машин в очереди пятен фар (004b3fb1) */
#define P123_GlowCars  GAME_VAR(p123_glowcars_t, P123_GlowCars, 0x010ffc00) /* номера машин очереди пятен фар (в оригинале без границы) */
#define P123_EvObjCur  GAME_VAR(uint8_t *, P123_EvObjCur, 0x00b1ff68)    /* последний объект 0x60 текущего события (004a45eb) */
#define P123_TgtX      GAME_VAR(float, P123_TgtX, 0x00c82510)
#define P123_TgtZ      GAME_VAR(float, P123_TgtZ, 0x00c82518)
#define P123_PtX       GAME_VAR(float, P123_PtX, 0x00c824b0)
#define P123_PtZ       GAME_VAR(float, P123_PtZ, 0x00c824b8)
#define P123_SideX     GAME_VAR(float, P123_SideX, 0x00c824c0)
#define P123_SideZ     GAME_VAR(float, P123_SideZ, 0x00c824c8)
#define P123_TgtMode   GAME_VAR(int32_t, P123_TgtMode, 0x00c824d0)
#define P123_TgtDist   GAME_VAR(int32_t, P123_TgtDist, 0x00c823dc)
#define P123_SideB     GAME_VAR(uint8_t, P123_SideB, 0x00b31ef8)
#ifndef RE_HOOK_BUILD
#pragma push_macro("P123_GlowCars") /*gvi*/
#undef P123_GlowCars /*gvi*/
extern p123_glowcars_t P123_GlowCars;
#pragma pop_macro("P123_GlowCars") /*gvi*/
#pragma push_macro("P123_GlowN") /*gvi*/
#undef P123_GlowN /*gvi*/
#pragma push_macro("P123_TgtMode") /*gvi*/
#undef P123_TgtMode /*gvi*/
#pragma push_macro("P123_TgtDist") /*gvi*/
#undef P123_TgtDist /*gvi*/
extern int32_t P123_GlowN, P123_TgtMode, P123_TgtDist;
#pragma pop_macro("P123_TgtDist") /*gvi*/
#pragma pop_macro("P123_TgtMode") /*gvi*/
#pragma pop_macro("P123_GlowN") /*gvi*/
#pragma push_macro("P123_SideB") /*gvi*/
#undef P123_SideB /*gvi*/
extern uint8_t *P123_EvObjCur, P123_SideB;
#pragma pop_macro("P123_SideB") /*gvi*/
#pragma push_macro("P123_TgtX") /*gvi*/
#undef P123_TgtX /*gvi*/
#pragma push_macro("P123_TgtZ") /*gvi*/
#undef P123_TgtZ /*gvi*/
#pragma push_macro("P123_PtX") /*gvi*/
#undef P123_PtX /*gvi*/
#pragma push_macro("P123_PtZ") /*gvi*/
#undef P123_PtZ /*gvi*/
#pragma push_macro("P123_SideX") /*gvi*/
#undef P123_SideX /*gvi*/
#pragma push_macro("P123_SideZ") /*gvi*/
#undef P123_SideZ /*gvi*/
extern float P123_TgtX, P123_TgtZ, P123_PtX, P123_PtZ, P123_SideX, P123_SideZ;
#pragma pop_macro("P123_SideZ") /*gvi*/
#pragma pop_macro("P123_SideX") /*gvi*/
#pragma pop_macro("P123_PtZ") /*gvi*/
#pragma pop_macro("P123_PtX") /*gvi*/
#pragma pop_macro("P123_TgtZ") /*gvi*/
#pragma pop_macro("P123_TgtX") /*gvi*/
#endif
void     P123_ObjAFall(uint8_t *o);          /* 004b9e9f: объект A (0x78) — шаг с гравитацией 6, отскок/исчезновение на дороге, время жизни */
void     P123_ObjShadows(void);              /* 00502e76: пятна под 10 объектами P58_Objs в видимых клетках */
void     P123_CarGlows(void);                /* 004b3fb1: пятна фар машин из очереди P123_GlowCars, яркость по P14_00d17b18 */
void     P123_CamAtCar(int32_t car);         /* 0049df91: камера над машиной car (−400) и углы на неё */
void     P123_SideDist(void);                /* 004f154e: ближняя к цели боковая точка игрока (±200) и расстояние до цели */
uint32_t P123_EvLine(uint32_t text, uint32_t ev);  /* 004a45eb: одна строка блока событий; возвращает адрес начала слова */
void     P123_EventsChunk(char *p);          /* 004a3fa6: блоки EVENT_START/MULTIEVENT_START до CHUNK_END */
/* gvar-img v2.03 begin (tools/gen_gvar_img.py) */
#if !defined(RE_HOOK_BUILD) && !defined(RE_GVAR_PLAIN)
#undef P123_GlowN
#define P123_GlowN (*(int32_t *)re_gvar(0x0112320cu, sizeof(int32_t), (void *)&P123_GlowN))
#undef P123_GlowCars
#define P123_GlowCars (*(p123_glowcars_t *)re_gvar(0x010ffc00u, sizeof(p123_glowcars_t), (void *)&P123_GlowCars))
#undef P123_TgtX
#define P123_TgtX (*(float *)re_gvar(0x00c82510u, sizeof(float), (void *)&P123_TgtX))
#undef P123_TgtZ
#define P123_TgtZ (*(float *)re_gvar(0x00c82518u, sizeof(float), (void *)&P123_TgtZ))
#undef P123_PtX
#define P123_PtX (*(float *)re_gvar(0x00c824b0u, sizeof(float), (void *)&P123_PtX))
#undef P123_PtZ
#define P123_PtZ (*(float *)re_gvar(0x00c824b8u, sizeof(float), (void *)&P123_PtZ))
#undef P123_SideX
#define P123_SideX (*(float *)re_gvar(0x00c824c0u, sizeof(float), (void *)&P123_SideX))
#undef P123_SideZ
#define P123_SideZ (*(float *)re_gvar(0x00c824c8u, sizeof(float), (void *)&P123_SideZ))
#undef P123_TgtMode
#define P123_TgtMode (*(int32_t *)re_gvar(0x00c824d0u, sizeof(int32_t), (void *)&P123_TgtMode))
#undef P123_TgtDist
#define P123_TgtDist (*(int32_t *)re_gvar(0x00c823dcu, sizeof(int32_t), (void *)&P123_TgtDist))
#undef P123_SideB
#define P123_SideB (*(uint8_t *)re_gvar(0x00b31ef8u, sizeof(uint8_t), (void *)&P123_SideB))
#endif
/* gvar-img v2.03 end */
