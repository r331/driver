#pragma once
#include <stdint.h>
#include "gvar.h"
/* v1.72: ported127 — автокамера повтора, полоса трафика, окно карты радара, звук/следы заноса игрока, такт точек
   появления, обломки вдали, огни фонарей, меню паузы (.data 00574710..00574f08 — P127_PauseMenu в k_regions),
   такт скрипта миссии, ввод имени (.data 0054cf80..0054cfd8 — P127_NameMenu в k_regions). Все функции cdecl. */
typedef uint8_t p127_pause_t[0x7f8];
typedef uint8_t p127_name_t[0x58];
typedef uint8_t p127_lamp5_t[5 * 0x28];
typedef int32_t p127_i5_t[5];
typedef float   p127_f16_t[16];
typedef uint32_t p127_u14_t[14];
typedef uint8_t p127_cur_t[4];
#define P127_PauseMenu GAME_VAR(p127_pause_t, P127_PauseMenu, 0x00574710) /* .data меню паузы (game/p127_data.h) */
#define P127_NameMenu  GAME_VAR(p127_name_t, P127_NameMenu, 0x0054cf80)   /* .data экрана ввода имени */
#define P127_Cursor    GAME_VAR(p127_cur_t, P127_Cursor, 0x005fe97c)      /* строка курсора: "_" или "" */
#define P127_NameLen   GAME_VAR(int32_t, P127_NameLen, 0x005fe980)
#define P127_BlinkT    GAME_VAR(int32_t, P127_BlinkT, 0x005fe984)
#define P127_BlinkOn   GAME_VAR(int32_t, P127_BlinkOn, 0x005fe988)
#define P127_Lamp5     GAME_VAR(p127_lamp5_t, P127_Lamp5, 0x00c818c0)     /* 5 записей фонарей 0x28 (последняя — 00c81960) */
#define P127_LampOn    GAME_VAR(p127_i5_t, P127_LampOn, 0x00c80f80)
#define P127_LampPhase GAME_VAR(int32_t, P127_LampPhase, 0x00b31ec0)
#define P127_SpawnD0   GAME_VAR(int32_t, P127_SpawnD0, 0x00c82430)      /* расстояние до первой точки появления */
#define P127_SpawnCnt  GAME_VAR(int32_t, P127_SpawnCnt, 0x00c82504)
#define P127_SpawnRst  GAME_VAR(int32_t, P127_SpawnRst, 0x00c82508)
#define P127_SpawnReq  GAME_VAR(int32_t, P127_SpawnReq, 0x00c82524)
#define P127_ScrPos    GAME_VAR(int32_t, P127_ScrPos, 0x00c80eec)       /* номер текущей команды скрипта */
#define P127_GoalX     GAME_VAR(float, P127_GoalX, 0x00c812d0)
#define P127_GoalZ     GAME_VAR(float, P127_GoalZ, 0x00c812d8)
#define P127_GoalJump  GAME_VAR(int32_t, P127_GoalJump, 0x00c81760)
#define P127_Goal      GAME_VAR(p127_f16_t, P127_Goal, 0x00c814a0)      /* +0 x, +8 z, +0x1c..+0x3c — копия состояния игрока */
#define P127_GoalSave  GAME_VAR(p127_u14_t, P127_GoalSave, 0x00c816c0)  /* копия P127_Goal (+0x38/+0x3c — P102_C816F8/FC) */
#define P127_GoalPause GAME_VAR(p127_f16_t, P127_GoalPause, 0x00c81700)
#ifndef RE_HOOK_BUILD
extern p127_pause_t P127_PauseMenu; extern p127_name_t P127_NameMenu; extern p127_cur_t P127_Cursor;
extern int32_t P127_NameLen, P127_BlinkT, P127_BlinkOn, P127_LampPhase, P127_SpawnD0, P127_SpawnCnt, P127_SpawnRst,
               P127_SpawnReq, P127_ScrPos, P127_GoalJump;
extern p127_lamp5_t P127_Lamp5; extern p127_i5_t P127_LampOn; extern float P127_GoalX, P127_GoalZ;
extern p127_f16_t P127_Goal, P127_GoalPause; extern p127_u14_t P127_GoalSave;
#endif
void P127_AutoCamera(void *cam);                          /* 004c582f: CreateNewAutoCamera (запись 0x8c) */
void P127_TrafficLane(uint8_t *t);                        /* 00494e01: смена полосы машины трафика (запись 0x54) */
void P127_MapWindow(int32_t x, int32_t y, uint32_t arg);  /* 0050b957: окно 0x37×0x37 клеток карты радара */
void P127_PlayerSkid(int32_t who);                        /* 004de381: звук заноса (голос 4) и следы шин игрока */
void P127_SpawnTick(int32_t draw);                        /* 004f1a19: движение/отрисовка точек появления */
void P127_FarDebris(void);                                /* 004ad3b5: обломки у объектов 00cfe760 при скорости > 99999 */
void P127_LampLights(void);                               /* 004eac70: огни фонарей вокруг игрока (P82_AddLight) */
void P127_Pause(void);                                    /* 0050ee00: Pause — выбор меню паузы */
void P127_ScriptTick(void);                               /* 004f472b: такт скрипта миссии */
void P127_NameEntry(char *buf, int32_t maxlen);           /* 004131a0: ввод имени, затем P58_CheatByName */
