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
extern p123_glowcars_t P123_GlowCars;
extern int32_t P123_GlowN, P123_TgtMode, P123_TgtDist;
extern uint8_t *P123_EvObjCur, P123_SideB;
extern float P123_TgtX, P123_TgtZ, P123_PtX, P123_PtZ, P123_SideX, P123_SideZ;
#endif
void     P123_ObjAFall(uint8_t *o);          /* 004b9e9f: объект A (0x78) — шаг с гравитацией 6, отскок/исчезновение на дороге, время жизни */
void     P123_ObjShadows(void);              /* 00502e76: пятна под 10 объектами P58_Objs в видимых клетках */
void     P123_CarGlows(void);                /* 004b3fb1: пятна фар машин из очереди P123_GlowCars, яркость по P14_00d17b18 */
void     P123_CamAtCar(int32_t car);         /* 0049df91: камера над машиной car (−400) и углы на неё */
void     P123_SideDist(void);                /* 004f154e: ближняя к цели боковая точка игрока (±200) и расстояние до цели */
uint32_t P123_EvLine(uint32_t text, uint32_t ev);  /* 004a45eb: одна строка блока событий; возвращает адрес начала слова */
void     P123_EventsChunk(char *p);          /* 004a3fa6: блоки EVENT_START/MULTIEVENT_START до CHUNK_END */
