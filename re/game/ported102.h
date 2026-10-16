/* v1.47 — восстановлено из Game.exe. Все функции cdecl (ret без операнда проверен по Game.exe).
   Фары машины 004aef57, проверка места трафика 00496372, столкновение коробок машин 00499bb2, новая машина трафика 00492b98,
   HUD миссии 00501c63, копы/погоня 004a6403, свободная камера режиссёра 004c2d73, точка пути копа 004a7aa7, снимок настроек
   CONFIG.DAT 00406875, сброс машин 004dd7ec, клетки трафика/пыли вокруг игрока 004902a8, выравнивание трафика 00493b51,
   параметры шести обломков 004aba7c, реплики копов 005259c8, цвет фонарей 004fe869, пыль на пустых клетках 0051329b,
   углы машины игрока 0051d51c, видимость на радаре 00509e64, коробка против машин 004d0439, след призрака 004e6c92,
   точка контакта коробок 0049a21d, отсечение 7 атрибутов 0042eaa6 и дальней плоскостью 5 атрибутов 0042f3f7. */
#pragma once
#include "gvar.h"
#include "reptr.h"
#include "cartab.h"
#include <stdint.h>

typedef uint32_t p102_hud_t[12];
typedef uint8_t  p102_pts_t[0xb40];      /* 240 точек по 0xc: +4 x, +8 z */
typedef int32_t  p102_i16_t[16];
typedef float    p102_m16_t[16];
typedef int32_t  p102_i4_t[4];
typedef uint8_t  p102_d68_t[0xd68];

/* HUD миссии (00501c63) */
#define P102_HudDmg    GAME_VAR(p102_hud_t, P102_HudDmg, 0x00c80820)    /* полоса повреждений (P16_FillHudRect) */
#define P102_HudFel    GAME_VAR(p102_hud_t, P102_HudFel, 0x00c80900)    /* полоса розыска */
#define P102_DmgVar    GAME_VAR(uint32_t, P102_DmgVar, 0x00c808f0)      /* адрес переменной скрипта DAMAGEBAR (P42_Vars + i*0x30) или 0 */
#define P102_FelVar    GAME_VAR(uint32_t, P102_FelVar, 0x00c80898)      /* FELONYBAR */
#define P102_OppVar    GAME_VAR(uint32_t, P102_OppVar, 0x00c80930)      /* OPPONENTBAR */
#define P102_MapIcon2  GAME_VAR(uint8_t *, P102_MapIcon2, 0x00c80894)   /* копия P100_RadarIcon */
#define P102_HudF4     GAME_VAR(int32_t, P102_HudF4, 0x00c808f4)
#define P102_DmgMax    GAME_VAR(int32_t, P102_DmgMax, 0x00c810a4)
#define P102_B52A3C    GAME_VAR(int32_t, P102_B52A3C, 0x00b52a3c)
/* пыль на пустых клетках (004902a8 → 0051329b) */
#define P102_DustPts   GAME_VAR(p102_pts_t, P102_DustPts, 0x01143740)
#define P102_DustN     GAME_VAR(int32_t, P102_DustN, 0x01144280)
#define P102_NbrC      GAME_VAR(int16_t, P102_NbrC, 0x00c55da0)        /* слово карты в самой клетке (соседи — P101_Nbr) */
/* углы машины игрока (0051d51c): 4 × {x, y, z, —} */
#define P102_Corners   GAME_VAR(p102_i16_t, P102_Corners, 0x00b5c910)
/* матрица призрака (004e6c92) */
#define P102_GhostMat  GAME_VAR(p102_m16_t, P102_GhostMat, 0x011360a0)
/* шесть обломков: флаг 010ff8e0 (параметры — P98_Six) */
#define P102_SixFlag   GAME_VAR(int32_t, P102_SixFlag, 0x010ff8e0)
/* сброс машин (004dd7ec) */
#define P102_D06A00    GAME_VAR(int32_t, P102_D06A00, 0x00d06a00)
#define P102_D06A04    GAME_VAR(int32_t, P102_D06A04, 0x00d06a04)
#define P102_BlkA      GAME_VAR(p102_d68_t, P102_BlkA, 0x00d06a20)
#define P102_BlkB      GAME_VAR(p102_d68_t, P102_BlkB, 0x00d0de00)
#define P102_BlkC      GAME_VAR(p102_d68_t, P102_BlkC, 0x00d0eb80)
#define P102_D0DD74    GAME_VAR(int32_t, P102_D0DD74, 0x00d0dd74)
#define P102_D0DD78    GAME_VAR(int32_t, P102_D0DD78, 0x00d0dd78)
#define P102_D0DD7C    GAME_VAR(int32_t, P102_D0DD7C, 0x00d0dd7c)
#define P102_D0DD80    GAME_VAR(int32_t, P102_D0DD80, 0x00d0dd80)
#define P102_D0DD84    GAME_VAR(int32_t, P102_D0DD84, 0x00d0dd84)
#define P102_D0DDD0    GAME_VAR(p102_i4_t, P102_D0DDD0, 0x00d0ddd0)
#define P102_D0DDE8    GAME_VAR(int32_t, P102_D0DDE8, 0x00d0dde8)
#define P102_D0DDEC    GAME_VAR(int32_t, P102_D0DDEC, 0x00d0ddec)
#define P102_D0DDF0    GAME_VAR(int32_t, P102_D0DDF0, 0x00d0ddf0)
#define P102_D077A0    GAME_VAR(p102_i4_t, P102_D077A0, 0x00d077a0)
#define P102_B2EA38    GAME_VAR(p102_i4_t, P102_B2EA38, 0x00b2ea38)
#define P102_D04D14    GAME_VAR(int32_t, P102_D04D14, 0x00d04d14)
#define P102_5624A4    GAME_VAR(int32_t, P102_5624A4, 0x005624a4)
#define P102_C816F8    GAME_VAR(int32_t, P102_C816F8, 0x00c816f8)
#define P102_C816FC    GAME_VAR(int32_t, P102_C816FC, 0x00c816fc)
/* снимок настроек (00406875) */
#define P102_57B6A8    GAME_VAR(int32_t, P102_57B6A8, 0x0057b6a8)
#define P102_57B6F8    GAME_VAR(int32_t, P102_57B6F8, 0x0057b6f8)
#define P102_BDF9E0    GAME_VAR(p102_i16_t, P102_BDF9E0, 0x00bdf9e0)   /* 11 слов */
#define P102_B5A914    GAME_VAR(int32_t, P102_B5A914, 0x00b5a914)      /* узел дороги последнего P102_RoadSide */
#define P102_HitFrame  GAME_VAR(int32_t, P102_HitFrame, 0x01144324)    /* кадр удара игрока о трафик */
#define P102_ObjBKey   GAME_VAR(int32_t, P102_ObjBKey, 0x0111d404)     /* ключ FindOrAdd_004BB11F последней отметки */
#ifndef RE_HOOK_BUILD
extern int32_t P102_B5A914, P102_HitFrame, P102_ObjBKey;
extern p102_hud_t P102_HudDmg, P102_HudFel; extern uint32_t P102_DmgVar, P102_FelVar, P102_OppVar; extern uint8_t *P102_MapIcon2;
extern int32_t P102_HudF4, P102_DmgMax, P102_B52A3C; extern p102_pts_t P102_DustPts; extern int32_t P102_DustN; extern int16_t P102_NbrC;
extern p102_i16_t P102_Corners; extern p102_m16_t P102_GhostMat; extern int32_t P102_SixFlag;
extern int32_t P102_D06A00, P102_D06A04; extern p102_d68_t P102_BlkA, P102_BlkB, P102_BlkC;
extern int32_t P102_D0DD74, P102_D0DD78, P102_D0DD7C, P102_D0DD80, P102_D0DD84, P102_D0DDE8, P102_D0DDEC, P102_D0DDF0;
extern p102_i4_t P102_D0DDD0, P102_D077A0, P102_B2EA38; extern int32_t P102_D04D14, P102_5624A4, P102_C816F8, P102_C816FC;
extern int32_t P102_57B6A8, P102_57B6F8; extern p102_i16_t P102_BDF9E0;
#endif

void     P102_CarLights(int32_t car, int32_t side);                                         /* 004aef57 */
int32_t  P102_TrafficRoom(int32_t x, int32_t z, int32_t owner, uint32_t flags);             /* 00496372 */
int32_t  P102_CarsHit(const uint8_t *a, const uint8_t *b, int32_t *depth, int32_t *p, int32_t *n, int32_t *q);  /* 00499bb2 */
int32_t  P102_TrafficAdd(int32_t x, int32_t y, int32_t z, int32_t heading, int32_t parked);  /* 00492b98 */
void     P102_HudInit(void);                                                                /* 00501c63 */
void     P102_CopsTick(void);                                                               /* 004a6403 */
void     P102_DirFreeCam(uint32_t keys);                                                    /* 004c2d73 */
void     P102_CopPathPoint(uint8_t *cop, int32_t dist, int32_t *out);                       /* 004a7aa7 */
void     P102_ConfigSnap(uint32_t *cfg);                                                    /* 00406875 */
void     P102_ResetCars(void);                                                              /* 004dd7ec */
void     P102_ScanCells(void);                                                              /* 004902a8 */
int32_t  P102_TrafficAlign(uint8_t *rec, int32_t a, int32_t b, int8_t mode);                /* 00493b51 */
void     P102_SixInit(void);                                                                /* 004aba7c */
void     P102_CopTalk(uint32_t keys);                                                       /* 005259c8 */
void     P102_LampColor(int32_t on);                                                        /* 004fe869 */
void     P102_SpawnDust(void);                                                              /* 0051329b */
void     P102_PlayerCorners(void);                                                          /* 0051d51c */
int32_t  P102_RadarClear(const int32_t *pos, int32_t dx, int32_t dz);                       /* 00509e64 */
uint8_t *P102_BoxAnyCar(int32_t x, int32_t z, int32_t ang, int32_t half, int32_t len);       /* 004d0439 */
void     P102_GhostTrail(void);                                                             /* 004e6c92 */
void     P102_BoxContact(const int32_t *box, int32_t *out);                                  /* 0049a21d */
void     P102_ClipNear7(const uint8_t *a, const uint8_t *b, float ua0, float ua1, float ua2, float ua3, float ua4, float ua5, float ua6,
                        float ub0, float ub1, float ub2, float ub3, float ub4, float ub5, float ub6);   /* 0042eaa6 */
void     P102_ClipFar5(const uint8_t *a, const uint8_t *b, float ua0, float ua1, float ua2, float ua3, float ua4,
                       float ub0, float ub1, float ub2, float ub3, float ub4);                          /* 0042f3f7 */
int32_t  P102_RoadSide(float x, float z);                                                   /* 0051a750 */
void     P102_CarsCollide(int32_t a, int32_t b, int32_t force);                               /* 0048f899 */
void     P102_CarPlanes(const uint8_t *car, float *out, int32_t dist);                        /* 005158cf */
int32_t  P102_TrafficAhead(uint8_t *rec, int32_t dist, int32_t parked);                       /* 0049521e */
void     P102_DirMenuNodes(void);                                                           /* 004c4ef9 */
void     P102_ObjMark(const uint8_t *obj, float x, float y, float z, int16_t kind);          /* 004af2fd */
void     P102_CarTracks(int32_t car, const int16_t *phase, float speed);                      /* 004af619 */
