#pragma once
#include <stdint.h>
#include "gvar.h"
/* v1.87: ported142 — вождение копа (004a7fec), физика колёс машины (004df024), шаг физики машин (004dacee). Все cdecl.
   Записи копов 0112da00 (8 × 0xcd8) — P12_0112da00, машины — P99_Cars / P59_CarsTab, блоки состояний — P102_BlkA/B/C.
   Переменные скрипта копов 0112b278/0112b27c/0112b2b8/011340c0/011340c4 (адреса лежат в P42_Vars) в native
   регистрируются re_ptr_register при первом вызове P142_CopDrive. */
#define P142_CopNoDmg  GAME_VAR(int32_t, P142_CopNoDmg, 0x0112d9d0)   /* 1 — не суммировать повреждения копа */
#define P142_CopDmgMax GAME_VAR(int32_t, P142_CopDmgMax, 0x00575ee0)  /* .data = 7000: порог повреждений «коп выбыл» */
#define P142_B278      GAME_VAR(int32_t, P142_B278, 0x0112b278)       /* скорость копа: база */
#define P142_B27C      GAME_VAR(int32_t, P142_B27C, 0x0112b27c)       /* скорость копа: × розыск 00d11a5c */
#define P142_B2AC      GAME_VAR(int32_t, P142_B2AC, 0x0112b2ac)       /* 4-е слово цели копа (P97_B2A0..A8) */
#define P142_B2B8      GAME_VAR(int32_t, P142_B2B8, 0x0112b2b8)       /* газ копа: база */
#define P142_340C0     GAME_VAR(int32_t, P142_340C0, 0x011340c0)      /* копы подстраиваются под скорость игрока */
#define P142_340C4     GAME_VAR(int32_t, P142_340C4, 0x011340c4)      /* газ копа: × розыск */
#define P142_D07788    GAME_VAR(int32_t, P142_D07788, 0x00d07788)     /* ослабление сцепления (0x7e90 − v) */
#define P142_B87E18    GAME_VAR(int32_t, P142_B87E18, 0x00b87e18)     /* множитель тормоза игрока (fixed 4.12) */
#define P142_B2F304    GAME_VAR(int32_t, P142_B2F304, 0x00b2f304)     /* боковая сила колёс игрока за кадр */
#ifndef RE_HOOK_BUILD
extern int32_t P142_CopNoDmg, P142_CopDmgMax, P142_B278, P142_B27C, P142_B2AC, P142_B2B8, P142_340C0, P142_340C4;
extern int32_t P142_D07788, P142_B87E18, P142_B2F304;
#endif
void P142_CopDrive(uint8_t *rec);                 /* 004a7fec: обработчик 4 такта трафика — руление/газ машины копа rec[5] */
void P142_WheelPhys(uint8_t *obj, int32_t drive); /* 004df024: колёса/подвеска машины obj → силы, P94_SpringStep */
void P142_CarsStep(void);                         /* 004dacee: шаг физики всех машин (интеграция, столкновения, 4 × 2 подшага) */
