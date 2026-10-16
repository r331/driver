#pragma once
#include "gvar.h"
#include "unported.h"
#include "ported4.h"
#include "ported7.h"
#include "ported21.h"
#include "ported31.h"
#include <stdint.h>
/* Таблицы MScript (команды, переменные), рекорды, версия D3D, Glide-устройства, углы вида. Все функции cdecl; P42_VersionString в оригинале stdcall (ret 4) — переходник re_hook. */
typedef struct { char name[0x100]; int32_t argc; int32_t id; int32_t size; int32_t pad; } p42_cmd_t; /* запись таблицы команд скриптов миссий (0x110) */
_Static_assert(sizeof(p42_cmd_t) == 0x110, "p42_cmd_t");
typedef struct { char name[0x20]; int32_t type; uint32_t addr; int32_t lo; int32_t hi; } p42_var_t;   /* запись таблицы переменных скрипта (0x30); addr — адрес переменной в Game.exe */
_Static_assert(sizeof(p42_var_t) == 0x30, "p42_var_t");
typedef p42_cmd_t p42_cmdtab_t[153];  /* 152 команды + пустая запись-ограничитель */
typedef p42_var_t p42_vartab_t[77];   /* 76 переменных + запись с type==0x7f */
typedef int32_t p42_hs_t[64];         /* таблицы рекордов: 2 — +0, 1 — +8, 3 — +16, 6/11 — +20, 7 — +24, 12 — +28 */
typedef uint8_t p42_names_t[16][0x4c];
#define P42_Cmds      GAME_VAR(p42_cmdtab_t, P42_Cmds, 0x00563980)
#define P42_Vars      GAME_VAR(p42_vartab_t, P42_Vars, 0x0056dc10)
#define P42_HighScores GAME_VAR(p42_hs_t, P42_HighScores, 0x00bdfb20)
#define P42_DevCount  GAME_VAR(int32_t, P42_DevCount, 0x00b1c0e0)   /* число Glide-устройств */
#define P42_DevNames  GAME_VAR(p42_names_t, P42_DevNames, 0x01270ec4)
#define P42_AngY      GAME_VAR(uint16_t, P42_AngY, 0x00d02700)
#define P42_AngX      GAME_VAR(uint16_t, P42_AngX, 0x00d02702)
#define P42_AngZ      GAME_VAR(uint16_t, P42_AngZ, 0x00d02704)
#define P42_AngBase   GAME_VAR(int32_t, P42_AngBase, 0x00d02718)
#define P42_CellX     GAME_VAR(int32_t, P42_CellX, 0x00ce0f2c)
#define P42_CellY     GAME_VAR(int32_t, P42_CellY, 0x00ce0f30)
#define P42_CellScale GAME_VAR(float, P42_CellScale, 0x0125f3e8)
#ifndef RE_HOOK_BUILD
#pragma push_macro("P42_Vars") /*gvi*/
#undef P42_Vars /*gvi*/
#pragma push_macro("P42_HighScores") /*gvi*/
#undef P42_HighScores /*gvi*/
extern p42_cmdtab_t P42_Cmds; extern p42_vartab_t P42_Vars; extern p42_hs_t P42_HighScores;
#pragma pop_macro("P42_HighScores") /*gvi*/
#pragma pop_macro("P42_Vars") /*gvi*/
#pragma push_macro("P42_DevCount") /*gvi*/
#undef P42_DevCount /*gvi*/
#pragma push_macro("P42_DevNames") /*gvi*/
#undef P42_DevNames /*gvi*/
extern int32_t P42_DevCount; extern p42_names_t P42_DevNames;
#pragma pop_macro("P42_DevNames") /*gvi*/
#pragma pop_macro("P42_DevCount") /*gvi*/
#pragma push_macro("P42_AngY") /*gvi*/
#undef P42_AngY /*gvi*/
#pragma push_macro("P42_AngX") /*gvi*/
#undef P42_AngX /*gvi*/
#pragma push_macro("P42_AngZ") /*gvi*/
#undef P42_AngZ /*gvi*/
#pragma push_macro("P42_AngBase") /*gvi*/
#undef P42_AngBase /*gvi*/
#pragma push_macro("P42_CellX") /*gvi*/
#undef P42_CellX /*gvi*/
#pragma push_macro("P42_CellY") /*gvi*/
#undef P42_CellY /*gvi*/
#pragma push_macro("P42_CellScale") /*gvi*/
#undef P42_CellScale /*gvi*/
extern uint16_t P42_AngY, P42_AngX, P42_AngZ; extern int32_t P42_AngBase, P42_CellX, P42_CellY; extern float P42_CellScale;
#pragma pop_macro("P42_CellScale") /*gvi*/
#pragma pop_macro("P42_CellY") /*gvi*/
#pragma pop_macro("P42_CellX") /*gvi*/
#pragma pop_macro("P42_AngBase") /*gvi*/
#pragma pop_macro("P42_AngZ") /*gvi*/
#pragma pop_macro("P42_AngX") /*gvi*/
#pragma pop_macro("P42_AngY") /*gvi*/
#endif
int32_t P42_FindCommand(const char *name, void **out);   /* 004f6333: запись команды по имени -> *out; 0 — нашли, 9 — нет */
char   *P42_FindCommandById(int32_t id);                 /* 004fc5ab: запись команды по id (поле +0x104) или NULL */
int32_t P42_FindVar(const char *name);                   /* 004f64dd: индекс переменной скрипта по имени или -1 */
int32_t P42_GetHighScore(int32_t table, int32_t idx);    /* 0051cd43: элемент таблицы рекордов; неверная таблица — лог и 0 */
void    P42_FreeGlide(void);                             /* 0042570c: FreeLibrary(glide2x.dll) */
void    P42_VersionString(char *dst);          /* 0041eb51: «2.43 (D3D)» */
int32_t P42_ActionBound(void);                           /* 004d6209: действие 0xf нажато или слот привязан */
int32_t P42_GetDeviceName(int32_t idx, char *dst);       /* 004245ec: имя Glide-устройства; -1 если Glide не готов */
void    P42_SetViewAngles(int32_t a, int32_t b, int32_t unused, float scale); /* 004e964a */
int32_t P42_CellIndex(const float *p);                   /* 004ece84: индекс клетки из координат x/z */
/* gvar-img v2.03 begin (tools/gen_gvar_img.py) */
#if !defined(RE_HOOK_BUILD) && !defined(RE_GVAR_PLAIN)
#undef P42_Vars
#define P42_Vars (*(p42_vartab_t *)re_gvar(0x0056dc10u, sizeof(p42_vartab_t), (void *)&P42_Vars))
#undef P42_HighScores
#define P42_HighScores (*(p42_hs_t *)re_gvar(0x00bdfb20u, sizeof(p42_hs_t), (void *)&P42_HighScores))
#undef P42_DevCount
#define P42_DevCount (*(int32_t *)re_gvar(0x00b1c0e0u, sizeof(int32_t), (void *)&P42_DevCount))
#undef P42_DevNames
#define P42_DevNames (*(p42_names_t *)re_gvar(0x01270ec4u, sizeof(p42_names_t), (void *)&P42_DevNames))
#undef P42_AngY
#define P42_AngY (*(uint16_t *)re_gvar(0x00d02700u, sizeof(uint16_t), (void *)&P42_AngY))
#undef P42_AngX
#define P42_AngX (*(uint16_t *)re_gvar(0x00d02702u, sizeof(uint16_t), (void *)&P42_AngX))
#undef P42_AngZ
#define P42_AngZ (*(uint16_t *)re_gvar(0x00d02704u, sizeof(uint16_t), (void *)&P42_AngZ))
#undef P42_AngBase
#define P42_AngBase (*(int32_t *)re_gvar(0x00d02718u, sizeof(int32_t), (void *)&P42_AngBase))
#undef P42_CellX
#define P42_CellX (*(int32_t *)re_gvar(0x00ce0f2cu, sizeof(int32_t), (void *)&P42_CellX))
#undef P42_CellY
#define P42_CellY (*(int32_t *)re_gvar(0x00ce0f30u, sizeof(int32_t), (void *)&P42_CellY))
#undef P42_CellScale
#define P42_CellScale (*(float *)re_gvar(0x0125f3e8u, sizeof(float), (void *)&P42_CellScale))
#endif
/* gvar-img v2.03 end */
