#pragma once
#include "gvar.h"
#include "unported.h"
#include "engine.h"
#include "director.h"
#include "dirnodes.h"
#include "ported7.h"
#include "ported14.h"
#include "ported29.h"
#include "ported43.h"
#include "ported44.h"
#include "ported59.h"
#include <stdint.h>
/* Шаг D: 7 функций — команды камер режиссёра (AddCamera 004c459f, ChangeCamera 004c483e, AddTripodCamera 004c4b3a,
   ChangeTripodCamera 004c4cee), ближайшая машина трафика 004c5c5d, обновление объекта 004a399a, запуск частицы 0051378b. Все cdecl.
   Поля рабочей камеры DirectorCam (0xd17bc4): +0 режим (2, 0x10, 0x11), +0x10 индекс машины, +0x18/+0x1c угол, +0x20 наклон,
   +0x48 флаг, +0x4c..0x54 позиция, +0x5c..0x64 цель, +0x7c/+0x7e — 16-битные копии углов. Машины — таблица 0xd077c0, запись 0x148. */
typedef uint8_t p60_cars_t[0x148 * 65];
#define P60_Cars      GAME_VAR(p60_cars_t, P60_Cars, 0x00d077c0)
#define P60_Var1373C0 GAME_VAR(int32_t, P60_Var1373C0, 0x011373c0)
#define P60_PartLimit GAME_VAR(int32_t, P60_PartLimit, 0x005759a4)
#ifndef RE_HOOK_BUILD
extern p60_cars_t P60_Cars; extern int32_t P60_Var1373C0, P60_PartLimit;
#endif
int32_t P60_NextTrafficCar(int32_t from);   /* 004c5c5d: номер ближайшей (в пределах 0x35a4e900 по квадрату) машины трафика после from, 0 — нет */
void    AddTripodCamera(int32_t cmd);       /* 004c4b3a */
void    ChangeTripodCamera(int32_t cmd);    /* 004c4cee */
void    AddCamera(int32_t id);              /* 004c459f */
void    ChangeCamera(int32_t id);           /* 004c483e */
void    P60_ObjUpdate(uint8_t *o);          /* 004a399a */
int32_t P60_SpawnParticle(uint8_t *p, int32_t flag); /* 0051378b */
