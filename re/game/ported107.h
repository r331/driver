/* v1.52 — восстановлено из Game.exe. Все функции cdecl (ret без операнда проверен по Game.exe).
   00490f3a — огни/следы машины трафика, 004221bf — освобождение слота текстуры D3D, 004262ce — линия Glide в координатах 640×480,
   004ca98d — надписи отсчёта/финиша (модели P69_*), 004a9f45 / 004aa217 — прямоугольник (однотонный / градиент) через grDrawPolygonVertexList,
   00506fa0 — стрелка компаса радара, 004b5049 — спрайт огня машины (.data CARLIGHT 005536e8, вершины 00b1ffd0..), 0050f304 — навигация по меню,
   004ddaca — ввод машины (руль/газ/тормоз), 004958b7 — ряд трафика вдоль дороги. */
#pragma once
#include "gvar.h"
#include "reptr.h"
#include <stdint.h>

typedef float p107_vblk_t[0x80];   /* GrVertex-ы 00b1ffd0..00b201d0 (004b5049) */
#define P107_SprV   GAME_VAR(p107_vblk_t, P107_SprV, 0x00b1ffd0)
#define P107_DDE6   GAME_VAR(uint8_t, P107_DDE6, 0x00d0dde6)       /* ручник-переключатель режима 10 (004ddaca) */
#define P107_HornVol GAME_VAR(int32_t, P107_HornVol, 0x005603cc)   /* громкость голоса 2 (.data: -10000) */
#define P107_SteerK GAME_VAR(int32_t, P107_SteerK, 0x00b87e1c)     /* множитель газа игрока (fixed 12) */
#define P107_NavWait GAME_VAR(int32_t, P107_NavWait, 0x005755bc)   /* задержка ввода меню (.data: 10) */
#define P107_NavRep GAME_VAR(int32_t, P107_NavRep, 0x005755c4)     /* период автоповтора (.data: 10) */
#define P107_NavCnt GAME_VAR(int32_t, P107_NavCnt, 0x00b5a780)     /* счётчик автоповтора */
#ifndef RE_HOOK_BUILD
extern p107_vblk_t P107_SprV; extern uint8_t P107_DDE6;
extern int32_t P107_HornVol, P107_SteerK, P107_NavWait, P107_NavRep, P107_NavCnt;
#endif

void    P107_TrafficLights(int32_t n, uint8_t *rec);                          /* 00490f3a: n — номер+1, rec — запись TrafficRecs */
void    P107_TexRelease(int32_t i);                                           /* 004221bf */
void    P107_Line(float x0, float y0, float x1, float y1, uint32_t rgb);      /* 004262ce */
void    P107_CountModel(int32_t kind, int32_t t);                             /* 004ca98d */
void    P107_Rect(int32_t x, int32_t y, int32_t w, int32_t h, uint32_t rgb);  /* 004a9f45: rgb — адрес 3 байт */
void    P107_RectGrad(int32_t x, int32_t y, int32_t w, int32_t h, uint32_t top, uint32_t bot); /* 004aa217 */
void    P107_Compass(void);                                                   /* 00506fa0 */
void    P107_CarLight(uint32_t rec, float k);                                 /* 004b5049: rec — адрес записи 0x1c (.data 005536e8) */
int32_t P107_MenuNav(uint32_t tab, int32_t pos);                              /* 0050f304: tab — адрес пунктов по 0x14 */
void    P107_CarInput(int32_t car, uint32_t keys);                            /* 004ddaca */
int32_t P107_TrafficRow(void);                                                /* 004958b7 */
