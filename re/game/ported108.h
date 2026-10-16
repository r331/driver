/* v1.53 — восстановлено из Game.exe. Все функции cdecl (ret без операнда проверен по Game.exe; метки __fastcall у 00518ab4/0048b5e3 ложные —
   push ecx резервирует локальную).
   00518ab4 — такт воспроизведения записи (машина 0x41), 0042205e / 00421e6c — эмулируемые текстуры слота 16/8 бит (256×256),
   0048b5e3 — запуск второго потока FMV и таймера по длительности, 00504a0a — треугольник-стрелка радара, 00505e2b — машина трафика на радаре,
   004b1993 / 004b1ea0 — квадраты дыма (значок SMOKE 01105d88), 004b4b27 — повёрнутый спрайт записи .data (BLANK 005536c8),
   00503f76 — фигура радара из .data (вершины/индексы 00573f08…), 004d7c46 / 004d7deb — однотонный прямоугольник (смешивание 0/3),
   00507eea — текстурный прямоугольник карты радара (grDrawPolygonVertexList). */
#pragma once
#include "gvar.h"
#include "reptr.h"
#include <stdint.h>

#define P108_FmvLen    GAME_VAR(double, P108_FmvLen, 0x00b1c850)       /* длительность FMV, с (таймер: (len+1)·1000 мс) */
#define P108_SmokeIcon ICONTAB_VAR(uint32_t, 8)  /* адрес записи значка SMOKE (004ec91e) */
#ifndef RE_HOOK_BUILD
extern double P108_FmvLen;
#endif

void    P108_ReplayStep(void);                                                   /* 00518ab4 */
int32_t P108_EmulTex16(int32_t slot);                                            /* 0042205e */
int32_t P108_EmulTex8(int32_t slot);                                             /* 00421e6c: слоты slot, slot+1 */
int32_t P108_FmvStart(void);                                                     /* 0048b5e3 */
void    P108_RadarArrow(int32_t x, int32_t red);                                 /* 00504a0a */
void    P108_RadarCar(float x, float z, int32_t i);                              /* 00505e2b: i — запись TrafficRecs */
void    P108_SmokeA(const uint8_t *o);                                           /* 004b1993 */
void    P108_SmokeB(const uint8_t *o);                                           /* 004b1ea0 */
void    P108_Sprite(uint32_t rec, float oow, uint32_t ang);                      /* 004b4b27: rec — адрес записи .data */
void    P108_RadarShape(uint32_t shape, const int32_t *pos, const int32_t *ofs, const int32_t *scr); /* 00503f76 */
void    P108_FillRect(float x, float y, float w, float h, uint32_t rgb);         /* 004d7c46: смешивание 0 */
void    P108_FillRectB(float x, float y, float w, float h, uint32_t rgb);        /* 004d7deb: смешивание 3 */
void    P108_MapTexRect(float x, float y, float w, float h, float u0, float v0, float u1, float v1, int32_t tex); /* 00507eea */
