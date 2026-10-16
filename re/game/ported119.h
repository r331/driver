/* v1.64, ported119 — восстановлено из Game.exe. Все функции cdecl (ret без операнда; work/rets.py).
   004c0c6f — колпак (HUBCAP), слетающий с машины игрока: draw=0 — такт (запуск P100_MarkerSpawn при большом крене, полёт
             по P98_CarBufC: +0x50/+0x90 матрицы, +0xd0 позиция, +0xe0 скорость, +0xf4 счётчик; отскок от дороги, 00b202b8 — высота),
             draw=1 — модель P26_ModelHubcap и тень значком P110_GlowIcon (4 вершины, два треугольника P85_RasterB);
   00491a56 — появление машины трафика i на узле node (или по точке при node = -1): сторона, проверки места, модель/цвет; 1/0;
   00417386 — клавиши экрана выбора машины: Esc (-1), влево/вправо — соседняя камера по таблице 005fea14 (P118_CamRoute), Enter — скорость повтора;
   0040cb9f — кадр меню по таймеру 005f7e60 (CD, звук, фоны, пункты, надписи, полосы ожидания, LFB, swap);
   004aff92 — пыль/дым из-под машины i (точка модели +0xc0, P118_SkidFx тип 2/1);
   004943dc — такт поворота записи трафика (доворот к курсу +0x30, затем новый узел и P118_TrafficTurn);
   004de86c — следы шин машины i (колёса 00d069c0, P117_SkidRecB, флаги P102_D077A0);
   0048fbcf — скорость/торможение записи трафика по типу узла и препятствию впереди (газ в машине +0xf8);
   004928c9 — стоящая машина трафика (полицейская при свободном слоте 004a6749) в (x, z) с курсом heading;
   0050230a — HUD: значения полос (повреждения, розыск, соперник), коэффициенты радара, радар/стрелки/скорость. */
#pragma once
#include <stdint.h>
#include "gvar.h"
typedef float p119_wheels_t[16];
#define P119_GroundY  GAME_VAR(int32_t, P119_GroundY, 0x00b202b8)      /* высота дороги под колпаком (−0x3c − P100_RoadHeightF) */
#define P119_Wheels   GAME_VAR(p119_wheels_t, P119_Wheels, 0x00d069c0)  /* 4 колеса × (x, y, z, —) — P101_WheelsGround */
#define P119_SelPtr   GAME_VAR(uint32_t, P119_SelPtr, 0x005fea14)       /* адрес таблицы выбора машины (.data 0054e320/28/30), по 4 байта: камера, скорость, влево, вправо */
#define P119_SelIdx   GAME_VAR(int32_t, P119_SelIdx, 0x005fea18)        /* текущая запись */
#ifndef RE_HOOK_BUILD
#pragma push_macro("P119_GroundY") /*gvi*/
#undef P119_GroundY /*gvi*/
#pragma push_macro("P119_SelIdx") /*gvi*/
#undef P119_SelIdx /*gvi*/
#pragma push_macro("P119_Wheels") /*gvi*/
#undef P119_Wheels /*gvi*/
#pragma push_macro("P119_SelPtr") /*gvi*/
#undef P119_SelPtr /*gvi*/
extern int32_t P119_GroundY, P119_SelIdx; extern p119_wheels_t P119_Wheels; extern uint32_t P119_SelPtr;
#pragma pop_macro("P119_SelPtr") /*gvi*/
#pragma pop_macro("P119_Wheels") /*gvi*/
#pragma pop_macro("P119_SelIdx") /*gvi*/
#pragma pop_macro("P119_GroundY") /*gvi*/
#endif
void    P119_Hubcap(int32_t draw);                                                      /* 004c0c6f */
int32_t P119_TrafficSpawn(int32_t i, int32_t node, int32_t lane, int32_t x, int32_t z);  /* 00491a56 */
uint8_t P119_SelByte(int32_t off);                                                      /* байт таблицы выбора машины по P119_SelPtr (native — копия .data 0054e320) */
int32_t P119_CarSelKey(int32_t row);                                                    /* 00417386 */
void    P119_MenuFrame(void);                                                           /* 0040cb9f */
void    P119_CarDust(int32_t i, int32_t kind, int32_t dist);                            /* 004aff92 */
void    P119_TrafficStep(uint8_t *rec);                                                 /* 004943dc */
void    P119_CarSkids(int32_t i);                                                       /* 004de86c */
void    P119_TrafficSpeed(uint8_t *rec, uint8_t *car);                                  /* 0048fbcf */
void    P119_TrafficParked(int32_t heading, int32_t x, int32_t z);                      /* 004928c9 */
void    P119_Hud(void);                                                                 /* 0050230a */
/* gvar-img v2.03 begin (tools/gen_gvar_img.py) */
#if !defined(RE_HOOK_BUILD) && !defined(RE_GVAR_PLAIN)
#undef P119_GroundY
#define P119_GroundY (*(int32_t *)re_gvar(0x00b202b8u, sizeof(int32_t), (void *)&P119_GroundY))
#undef P119_Wheels
#define P119_Wheels (*(p119_wheels_t *)re_gvar(0x00d069c0u, sizeof(p119_wheels_t), (void *)&P119_Wheels))
#undef P119_SelPtr
#define P119_SelPtr (*(uint32_t *)re_gvar(0x005fea14u, sizeof(uint32_t), (void *)&P119_SelPtr))
#undef P119_SelIdx
#define P119_SelIdx (*(int32_t *)re_gvar(0x005fea18u, sizeof(int32_t), (void *)&P119_SelIdx))
#endif
/* gvar-img v2.03 end */
