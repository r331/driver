#pragma once
#include <stdint.h>
#include "gvar.h"
/* v1.92: ported147 — разбор команды скрипта миссии 004f68a1 (MScript: токены строки P65_Line → запись в P77_List
   или прямые флаги/переменные; вызывается из P131_ScriptLine) и 00503ddf (команда 0x74: запись очков по записи
   скрипта 00c812bc → 00b32a10 / 01271070 / *00b32a08; найдена только через thunk 00401c62). cdecl. */
typedef int32_t p147_rec6_t[6];        /* 00b32a10..00b32a27: текущая запись таблицы рекордов (6 слов, +4 — тип 8) */
_Static_assert(sizeof(p147_rec6_t) == 0x18, "p147_rec6_t");
typedef char    p147_chase_t[0x40];    /* 00c80f00..00c80f3f: имя погони для replaydata\Chase\%s%d.leader (команда 0x3d) */
_Static_assert(sizeof(p147_chase_t) == 0x40, "p147_chase_t");
#define P147_Rec2A10   GAME_VAR(p147_rec6_t, P147_Rec2A10, 0x00b32a10)   /* P71_V2A14/1C/20/24 — псевдонимы слов 1/3/4/5 */
#define P147_ChaseName GAME_VAR(p147_chase_t, P147_ChaseName, 0x00c80f00)
#ifndef RE_HOOK_BUILD
extern p147_rec6_t P147_Rec2A10; extern p147_chase_t P147_ChaseName;
#endif
int32_t P147_ParseCmd(void *cmd);   /* 004f68a1: cmd — запись p42_cmd_t; 0xb — продолжить строку, 0 — строка закончена, иначе код ошибки (9/0xc/…) */
int32_t P147_ScoreRec(void);        /* 00503ddf: 1 — запись *00b32a08 обновлена (P14_Fn00503E83 ≠ 0), иначе 0 */
