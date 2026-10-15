#pragma once
#include "gvar.h"
#include "unported.h"
#include "engine.h"
#include "crt.h"
#include "uihandlers3.h"
#include "ported12.h"
#include "ported26.h"
#include "ported27.h"
#include "ported42.h"
#include "ported51.h"
#include "ported52.h"
#include "ported54.h"
#include "ported11.h"
#include "ported19.h"
#include "ported43.h"
#include "ported58.h"
#include "ported59.h"
#include "ported60.h"
#include "ported61.h"
#include <stdint.h>
/* Шаг D: 17 мелких функций — установка начальных значений (камера, рендер), поиск и проверки по таблицам машин/трафика,
   рекорды, загрузка карты, страницы текстур. Все cdecl. Указатели-аргументы — на структуры игры (доступ по смещениям). */
#define P62_C82434   GAME_VAR(int32_t, P62_C82434, 0x00c82434)
#define P62_C82500   GAME_VAR(int32_t, P62_C82500, 0x00c82500)
#define P62_F136C54  GAME_VAR(float, P62_F136C54, 0x01136c54)
#define P62_I137388  GAME_VAR(int32_t, P62_I137388, 0x01137388)
#define P62_I13738C  GAME_VAR(int32_t, P62_I13738C, 0x0113738c)
#define P62_I137390  GAME_VAR(int32_t, P62_I137390, 0x01137390)
#define P62_F252A94  GAME_VAR(float, P62_F252A94, 0x01252a94)
#define P62_F25F3F4  GAME_VAR(float, P62_F25F3F4, 0x0125f3f4)
#define P62_F25F404  GAME_VAR(float, P62_F25F404, 0x0125f404)
#define P62_I270C44  GAME_VAR(int32_t, P62_I270C44, 0x01270c44)
#define P62_I252A80  GAME_VAR(int32_t, P62_I252A80, 0x01252a80)
#define P62_I252B78  GAME_VAR(int32_t, P62_I252B78, 0x01252b78)
#define P62_I270C48  GAME_VAR(int32_t, P62_I270C48, 0x01270c48)
#define P62_I252B68  GAME_VAR(int32_t, P62_I252B68, 0x01252b68)
#define P62_B25F400  GAME_VAR(uint8_t, P62_B25F400, 0x0125f400)
#define P62_I14428C  GAME_VAR(int32_t, P62_I14428C, 0x0114428c)
#define P62_Max      GAME_VAR(int32_t, P62_Max, 0x0112b25c)
#define P62_MapN     GAME_VAR(int32_t, P62_MapN, 0x00c1cc70)
#define P62_ModelNames GAME_VAR(const char *, P62_ModelNames, 0x00b1ff60)
#define P62_ModelCount GAME_VAR(int32_t, P62_ModelCount, 0x01134124)
#define P62_NoErr    GAME_VAR(int32_t, P62_NoErr, 0x00bdf9c8)
#define P62_Spd      CARTAB_VAR(int32_t, P62_Spd, 0x00d078d0)
#define P62_Unit     GAME_VAR(const char *, P62_Unit, 0x00c55ccc)
#define P62_Blink    GAME_VAR(int32_t, P62_Blink, 0x00c8092c)
#define P62_HudOff1  GAME_VAR(int32_t, P62_HudOff1, 0x00b87ea0)
#define P62_HudOff2  GAME_VAR(int32_t, P62_HudOff2, 0x00b87e98)
#define P62_Frame    GAME_VAR(int32_t, P62_Frame, 0x00d118c0)
#define P62_Alt      GAME_VAR(int32_t, P62_Alt, 0x00b5a830)
#define P62_Menu1271060 GAME_VAR(int32_t, P62_Menu1271060, 0x01271060)
#define P62_Menu1271064 GAME_VAR(int32_t, P62_Menu1271064, 0x01271064)
#define P62_BusyA    GAME_VAR(int32_t, P62_BusyA, 0x00bdfa44)
#define P62_BusyB    GAME_VAR(int32_t, P62_BusyB, 0x00bdfa48)
#define P62_BusyC    GAME_VAR(int32_t, P62_BusyC, 0x00bdfa4c)
#define P62_BusyD    GAME_VAR(int32_t, P62_BusyD, 0x00bdfa50)
#define P62_BusyE    GAME_VAR(int32_t, P62_BusyE, 0x00bdfa58)
#define P62_MapW     GAME_VAR(int32_t, P62_MapW, 0x00c1ed60)
#define P62_MapH     GAME_VAR(int32_t, P62_MapH, 0x00c1cc68)
#define P62_Map1C10  GAME_VAR(int32_t, P62_Map1C10, 0x00bf1c10)
#define P62_Map1C24  GAME_VAR(int32_t, P62_Map1C24, 0x00bf1c24)
#define P62_MapC64   GAME_VAR(int32_t, P62_MapC64, 0x00c1cc64)
#define P62_Map2C40  GAME_VAR(int32_t, P62_Map2C40, 0x00c12c40)
#define P62_Map1C0C  GAME_VAR(int32_t, P62_Map1C0C, 0x00bf1c0c)
#define P62_MapCC90  GAME_VAR(int32_t, P62_MapCC90, 0x00c1cc90)
#define P62_MapBuf   GAME_VAR(uint8_t *, P62_MapBuf, 0x00b5a900)
typedef uint16_t p62_page_t[0x100 * 0x100];
#define P62_Page     GAME_VAR(p62_page_t, P62_Page, 0x00b32a34)
typedef uint8_t p62_hs1_t[0x2c * 0x28];
typedef uint8_t p62_hs2_t[0x2c * 0x14];
typedef uint8_t p62_hs3_t[0x2c * 4];
#define P62_Hs1      GAME_VAR(p62_hs1_t, P62_Hs1, 0x00b5b378)
#define P62_Hs2      GAME_VAR(p62_hs1_t, P62_Hs2, 0x00b5ba58)
#define P62_Hs3      GAME_VAR(p62_hs2_t, P62_Hs3, 0x00b5b008)
#define P62_Hs4      GAME_VAR(p62_hs2_t, P62_Hs4, 0x00b5ac98)
#define P62_Hs5      GAME_VAR(p62_hs2_t, P62_Hs5, 0x00b5a928)
#define P62_Hs6      GAME_VAR(p62_hs3_t, P62_Hs6, 0x00b5c138)
#ifndef RE_HOOK_BUILD
extern int32_t P62_I14428C, P62_C82434, P62_C82500, P62_I137388, P62_I13738C, P62_I137390, P62_I270C44, P62_I252A80, P62_I252B78,
  P62_I270C48, P62_I252B68, P62_Max, P62_MapN, P62_ModelCount, P62_NoErr,
  P62_Blink, P62_HudOff1, P62_HudOff2, P62_Frame, P62_Alt, P62_Menu1271060, P62_Menu1271064, P62_BusyA, P62_BusyB, P62_BusyC,
  P62_BusyD, P62_BusyE, P62_MapW, P62_MapH, P62_Map1C10, P62_Map1C24, P62_MapC64, P62_Map2C40, P62_Map1C0C, P62_MapCC90;
extern float P62_F136C54, P62_F252A94, P62_F25F3F4, P62_F25F404;
extern uint8_t P62_B25F400, *P62_MapBuf;
extern const char *P62_ModelNames, *P62_Unit;
extern p62_page_t P62_Page;
extern p62_hs1_t P62_Hs1, P62_Hs2; extern p62_hs2_t P62_Hs3, P62_Hs4, P62_Hs5; extern p62_hs3_t P62_Hs6;
#endif
void    P62_InitCamDefaults(void);                          /* 0049c850: камера по умолчанию (расстояния, смещение, углы) */
void    P62_InitRenderConsts(void);                         /* 00425a50: константы 3D-рендера для размера экрана */
int32_t P62_HeadingDelta(const uint8_t *id, uint32_t want); /* 0049431d: доворот машины к курсу; вернуть |разность| */
int32_t P62_FarFromPlayer(int32_t id, int32_t dist);        /* 00492398: запись трафика id дальше dist от игрока */
void    P62_QueueTri(const uint32_t *a, const uint32_t *b, const uint32_t *c, uint32_t tag); /* 0042d2c9: три вершины в очередь */
int32_t P62_MapRow(int32_t idx, int32_t *dst);              /* 0051ac05: распаковать строку карты (RLE) */
int32_t P62_ModelLookup(const char *name, uint16_t *out);   /* 004a58ad: id модели по имени */
int32_t P62_FindFreeTrafficSlot(void);                      /* 004a6749: первый свободный слот трафика 1..8, иначе −1 */
void    P62_SpawnTrafficCar(int32_t n);                     /* 0049199a: создать машину трафика для записи n */
void    P62_DownloadPage(uint32_t h, const uint16_t *bmp, int32_t x, int32_t y, int32_t w, int32_t hh, int32_t stride); /* 005047ab */
int32_t P62_SaveScores(void *file);                         /* 0051cb98: запись таблиц рекордов в файл */
int32_t P62_ScoreTable(int32_t *idx, int32_t alt);          /* 0051cdec: найти строку рекорда */
int32_t P62_MenuBusy(void);                                 /* 00413df3: 1 — идёт переход/ролик */
void    P62_SpeedText(void);                                /* 005025dc: скорость на экране */
void    P62_LoadMapHeader(void *file, int32_t size);        /* 004ec336: размеры карты и буфер данных */
void    P62_ParticleSet(uint8_t *p, int32_t kind, int32_t a, uint32_t flags, int32_t b); /* 00514c72 */
void    P62_ParticleInit(uint8_t *p, void *car);            /* 00515813 */
