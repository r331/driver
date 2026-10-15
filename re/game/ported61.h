#pragma once
#include "gvar.h"
#include "unported.h"
#include "engine.h"
#include "dirnodes.h"
#include "ported43.h"
#include "ported44.h"
#include "ported59.h"
#include "ported60.h"
#include "smallfuncs.h"
#include <stdint.h>
/* Шаг D: 5 функций камер — подготовка рабочей камеры от машины (0049e5e7), снимок игровой камеры в запись режиссёра (004c5499),
   обратное восстановление (004c536c), нормализация записи камеры (004c6d62), запуск частицы в карте (00514261). Все cdecl.
   Запись камеры режиссёра (0x8c): +0 режим, +8/+0xc дистанция, +0x10 машина, +0x18/+0x1c угол, +0x48 флаг, +0x4c.. позиция (int),
   +0x5c.. цель, +0x6c.. смещение, +0x7c/+0x7e/+0x80 углы (u16). Машины — таблица 0xd077c0, запись 0x148 (+0xc8..0xd0 позиция, +0xe8.. углы, +0x100 курс).
   Смещения камеры от машины — таблица 18 записей по 4 float с 0x560968 (в native — P61_InitConsts). */
typedef float p61_offs_t[18 * 4];
#define P61_CamOffs   GAME_VAR(p61_offs_t, P61_CamOffs, 0x00560968)
#define P61_Heading   GAME_VAR(int16_t, P61_Heading, 0x01137322)    /* старшее слово 01137320 */
#define P61_TgtX      GAME_VAR(float, P61_TgtX, 0x01136c70)
#define P61_TgtY      GAME_VAR(float, P61_TgtY, 0x01136c74)
#define P61_TgtZ      GAME_VAR(float, P61_TgtZ, 0x01136c78)
#define P61_OffX      GAME_VAR(float, P61_OffX, 0x011373a0)
#define P61_OffY      GAME_VAR(float, P61_OffY, 0x011373a4)
#define P61_OffZ      GAME_VAR(float, P61_OffZ, 0x011373a8)
#define P61_AngB8     GAME_VAR(uint16_t, P61_AngB8, 0x011373b8)
#define P61_AngBA     GAME_VAR(uint16_t, P61_AngBA, 0x011373ba)
#define P61_AngBC     GAME_VAR(uint16_t, P61_AngBC, 0x011373bc)
#define P61_Dist8     GAME_VAR(float, P61_Dist8, 0x01137368)
#define P61_DistC     GAME_VAR(float, P61_DistC, 0x0113731c)
#define P61_V18       GAME_VAR(int32_t, P61_V18, 0x01136c58)
#define P61_V1C       GAME_VAR(int32_t, P61_V1C, 0x01137310)
#define P61_V20       GAME_VAR(int32_t, P61_V20, 0x01137318)
#define P61_V10       GAME_VAR(int32_t, P61_V10, 0x01136c48)
#define P61_V10b      GAME_VAR(int32_t, P61_V10b, 0x01136c4c)
#ifndef RE_HOOK_BUILD
extern p61_offs_t P61_CamOffs; extern int16_t P61_Heading;
extern float P61_TgtX, P61_TgtY, P61_TgtZ, P61_OffX, P61_OffY, P61_OffZ, P61_Dist8, P61_DistC;
extern uint16_t P61_AngB8, P61_AngBA, P61_AngBC;
extern int32_t P61_V18, P61_V1C, P61_V20, P61_V10, P61_V10b;
#endif
void P61_InitConsts(void);
void P61_SetupCamN(int32_t n);          /* 0049e5e7: матрица вида и положение камеры за машиной n */
void P61_StoreCamState(uint8_t *cam);   /* 004c5499: запись режиссёра <- текущее состояние камеры */
void P61_RestoreCamState(uint8_t *cam); /* 004c536c: текущее состояние камеры <- запись режиссёра */
void P61_CamPrepare(uint8_t *cam);      /* 004c6d62: расстояние/угол записи относительно машины */
void P61_SpawnPart(uint8_t *p);         /* 00514261: поиск ячейки и привязка частицы, иначе освободить слот */
