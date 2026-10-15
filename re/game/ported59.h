#pragma once
#include "gvar.h"
#include "unported.h"
#include "engine.h"
#include "crt.h"
#include "ported12.h"
#include "ported42.h"
#include "ported44.h"
#include "ported51.h"
#include "ported56.h"
#include "ported58.h"
#include "ported6.h"
#include "smallfuncs2.h"
#include "uihandlers2.h"
#include "uihandlers3.h"
#include <stdint.h>
/* Шаг D: 13 функций — камера 0049c910, события скрипта (строки/значения по таблице переменных MScript), трафик (0048ed6f/0048eca3),
   ячейка карты 00491650, список моделей 004a3f06, подбор 004a6dcd, подбор предмета 004e5ea2, скорость/направление объекта 004daac7,
   проверка REPLAYn.BIN 00405fdb, горячие клавиши меню 00417d56, чтение блока из файла 0040d4b3. Все cdecl.
   Таблица синусов (0x576f10) для native берётся из sintab_data.h (P59_InitConsts). */
typedef uint8_t p59_u8x64k_t[0x148 * 64];
typedef uint8_t p59_tab_bf1c48_t[0x42 * 64];
typedef uint8_t p59_tab_c39dc0_t[0x24 * 64];
typedef int32_t p59_i32x18_t[18];
typedef uint8_t p59_u8x9_t[9];
typedef uint8_t p59_u8x64_t[64];
typedef int16_t p59_sin_t[4096];
#define P59_CamF1       GAME_VAR(float, P59_CamF1, 0x01270c24)
#define P59_CamLim      GAME_VAR(float, P59_CamLim, 0x005460e8)      /* 2000.0 */
#define P59_PosX        GAME_VAR(int32_t, P59_PosX, 0x00d07888)
#define P59_PosY        GAME_VAR(int32_t, P59_PosY, 0x00d0788c)
#define P59_PosZ        GAME_VAR(int32_t, P59_PosZ, 0x00d07890)
#define P59_VX          GAME_VAR(float, P59_VX, 0x00b1c270)
#define P59_VY          GAME_VAR(float, P59_VY, 0x00b1c274)
#define P59_VZ          GAME_VAR(float, P59_VZ, 0x00b1c278)
#define P59_AngA        GAME_VAR(uint16_t, P59_AngA, 0x00b1c268)
#define P59_AngB        GAME_VAR(uint16_t, P59_AngB, 0x00b1c26a)
#define P59_AngC        GAME_VAR(uint16_t, P59_AngC, 0x00b1c26c)
#define P59_Mode1137324 GAME_VAR(uint8_t, P59_Mode1137324, 0x01137324)
#define P59_CarsTab     GAME_VAR(uint8_t *, P59_CarsTab, 0x0113a6c4)  /* таблица машин, запись 0x148 */
#define P59_C39DC0      GAME_VAR(p59_tab_c39dc0_t, P59_C39DC0, 0x00c39dc0) /* запись 0x24: байты +0..3 — длины, int +4/+0x10/+0x14/+0x20 — границы */
#define P59_BF1C48      GAME_VAR(p59_tab_bf1c48_t, P59_BF1C48, 0x00bf1c48) /* запись 0x42: int16 в начале */
#define P59_ModelCount  GAME_VAR(int32_t, P59_ModelCount, 0x01134120)
#define P59_Flags9      GAME_VAR(p59_u8x9_t, P59_Flags9, 0x00d04a50)
#define P59_Picked      GAME_VAR(int8_t, P59_Picked, 0x00d04650)
#define P59_S4654       GAME_VAR(int32_t, P59_S4654, 0x00d04654)
#define P59_S44CC       GAME_VAR(int32_t, P59_S44CC, 0x00d044cc)
#define P59_S4790       GAME_VAR(int32_t, P59_S4790, 0x00d04790)
#define P59_S3904       GAME_VAR(int32_t, P59_S3904, 0x00d03904)
#define P59_PickTab     GAME_VAR(p59_i32x18_t, P59_PickTab, 0x00562ae0) /* пары (текст, звук) для 9 предметов */
#define P59_NearN       GAME_VAR(int32_t, P59_NearN, 0x00c7d7e0)
#define P59_NearList    GAME_VAR(p59_u8x64_t, P59_NearList, 0x00c7d860)
#define P59_CarRecs     GAME_VAR(p59_u8x64k_t, P59_CarRecs, 0x00d07908)
#define P59_Sin         GAME_VAR(p59_sin_t, P59_Sin, 0x00576f10)
typedef uint8_t p59_rep_t[0x38];
typedef uint32_t p59_hdr_t[2];
#define P59_Hdr         GAME_VAR(p59_hdr_t, P59_Hdr, 0x0057b6f0)
#define P59_One         GAME_VAR(float, P59_One, 0x00546020)
#define P59_Rep57B6B8   GAME_VAR(p59_rep_t, P59_Rep57B6B8, 0x0057b6b8)
#define P59_NoKeyFlag   GAME_VAR(int32_t, P59_NoKeyFlag, 0x005feda0)
#define P59_MenuLock    GAME_VAR(int32_t, P59_MenuLock, 0x005fea54)
#ifndef RE_HOOK_BUILD
extern float P59_CamF1, P59_CamLim, P59_VX, P59_VY, P59_VZ; extern int32_t P59_PosX, P59_PosY, P59_PosZ;
extern uint16_t P59_AngA, P59_AngB, P59_AngC; extern uint8_t P59_Mode1137324, *P59_CarsTab;
extern p59_tab_c39dc0_t P59_C39DC0; extern p59_tab_bf1c48_t P59_BF1C48; extern int32_t P59_ModelCount;
extern p59_u8x9_t P59_Flags9; extern int8_t P59_Picked; extern int32_t P59_S4654, P59_S44CC, P59_S4790, P59_S3904;
extern p59_i32x18_t P59_PickTab; extern int32_t P59_NearN; extern p59_u8x64_t P59_NearList; extern p59_u8x64k_t P59_CarRecs;
extern p59_sin_t P59_Sin; extern p59_hdr_t P59_Hdr; extern p59_rep_t P59_Rep57B6B8; extern float P59_One;
extern int32_t P59_NoKeyFlag, P59_MenuLock;
extern char *P59_VarStr[77]; /* native: буферы строковых переменных MScript (в Game.exe указатель лежит в записи таблицы) */
#endif
void    P59_InitConsts(void);                                /* native: таблица синусов и константы */
void    P59_SetupCamera(void);                               /* 0049c910 */
void    P59_VarSetString(int32_t idx, const char *s);        /* 004f8a2d: копия строки в переменную типа 1 */
void    P59_VarsInit(void);                                  /* 004f892a: начальные значения переменных скрипта */
int32_t P59_TrafficCheck(const uint8_t *r, int32_t flag);    /* 0048ed6f: запись трафика r (0x34 байта) */
int32_t P59_TrafficFind(uint32_t self, int32_t a, uint32_t b); /* 0048eca3 */
uint32_t P59_CellLeft(const uint8_t *r);                     /* 00491650 */
const char *P59_ModelNames(const char *text);                /* 004a3f06 */
int32_t P59_NearCars(const int32_t *self);                   /* 004a6dcd */
int32_t P59_PickUp(int32_t i);                               /* 004e5ea2 */
void    P59_ObjDir(uint8_t *o, int32_t mode);                /* 004daac7 */
int32_t P59_ReplayCheck(int32_t slot, void *out);            /* 00405fdb */
int32_t P59_MenuKeys(void);                                  /* 00417d56 */
void   *P59_ReadBlock(void *file, float scale, int32_t *hdr); /* 0040d4b3 */
