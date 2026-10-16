#pragma once
#include <stdint.h>
#include "gvar.h"
/* v1.85: ported140 — сохранение игры, имена клавиш, цикл фронтенда, интерпретатор MLADDER, звук (WAV-сэмпл, запуск
   драйвера, строка банка), полёт маркера-вертолёта. Все cdecl. */
typedef uint8_t  p140_keystr_t[0x210];
typedef uint32_t p140_keyname_t[0x108];
typedef float    p140_f3_t[3];
#define P140_KeyStr   GAME_VAR(p140_keystr_t, P140_KeyStr, 0x0054b4b4)   /* 0x21 имя клавиши по 0x10 (KEYS.<язык>) */
#define P140_KeyName  GAME_VAR(p140_keyname_t, P140_KeyName, 0x0054b080) /* адреса имён клавиш по скан-коду */
#define P140_FrSelA   GAME_VAR(int32_t, P140_FrSelA, 0x005fe960)        /* пункт главного меню */
#define P140_FrSelB   GAME_VAR(int32_t, P140_FrSelB, 0x005fe964)        /* пункт меню выхода */
#define P140_FrQuit   GAME_VAR(int32_t, P140_FrQuit, 0x005fe968)        /* 1 — открыто меню выхода */
#define P140_B91BC0   GAME_VAR(int32_t, P140_B91BC0, 0x00b91bc0)
#define P140_B1F434   GAME_VAR(int32_t, P140_B1F434, 0x00b1f434)        /* аргумент создания буфера DirectSound */
#define P140_Mrk2644  GAME_VAR(int32_t, P140_Mrk2644, 0x00d02644)       /* 1 — маркер сбит в этом кадре */
#define P140_MrkVel   GAME_VAR(p140_f3_t, P140_MrkVel, 0x00b31ea8)      /* скорость частиц дыма маркера */
#define P140_Mrk2740  (P98_MrkF[8])     /* толчок маркера x/y/z — макросы над P98_MrkF (ported98.h) */
#define P140_Mrk2744  (P98_MrkF[9])
#define P140_Mrk2748  (P98_MrkF[10])
#ifndef RE_HOOK_BUILD
#pragma push_macro("P140_KeyStr") /*gvi*/
#undef P140_KeyStr /*gvi*/
#pragma push_macro("P140_KeyName") /*gvi*/
#undef P140_KeyName /*gvi*/
#pragma push_macro("P140_FrSelA") /*gvi*/
#undef P140_FrSelA /*gvi*/
#pragma push_macro("P140_FrSelB") /*gvi*/
#undef P140_FrSelB /*gvi*/
#pragma push_macro("P140_FrQuit") /*gvi*/
#undef P140_FrQuit /*gvi*/
extern p140_keystr_t P140_KeyStr; extern p140_keyname_t P140_KeyName; extern int32_t P140_FrSelA, P140_FrSelB, P140_FrQuit;
#pragma pop_macro("P140_FrQuit") /*gvi*/
#pragma pop_macro("P140_FrSelB") /*gvi*/
#pragma pop_macro("P140_FrSelA") /*gvi*/
#pragma pop_macro("P140_KeyName") /*gvi*/
#pragma pop_macro("P140_KeyStr") /*gvi*/
#pragma push_macro("P140_B91BC0") /*gvi*/
#undef P140_B91BC0 /*gvi*/
#pragma push_macro("P140_B1F434") /*gvi*/
#undef P140_B1F434 /*gvi*/
#pragma push_macro("P140_Mrk2644") /*gvi*/
#undef P140_Mrk2644 /*gvi*/
#pragma push_macro("P140_MrkVel") /*gvi*/
#undef P140_MrkVel /*gvi*/
extern int32_t P140_B91BC0, P140_B1F434, P140_Mrk2644; extern p140_f3_t P140_MrkVel;
#pragma pop_macro("P140_MrkVel") /*gvi*/
#pragma pop_macro("P140_Mrk2644") /*gvi*/
#pragma pop_macro("P140_B1F434") /*gvi*/
#pragma pop_macro("P140_B91BC0") /*gvi*/
#endif
void    P140_SaveGame(int32_t slot, const char *name);   /* 00405d60: SAVES\GAME<slot+1>.BIN = заголовок 8 + запись 0x38 */
void    P140_KeysLoad(void);                             /* 0040ec30: KEYS.<язык> → 0x21 имя клавиши */
void    P140_Frontend(int32_t unused);                   /* 004127f0: заставки и главный цикл меню (__fastcall у Ghidra без ECX) */
void    P140_LadderRun(void);                            /* 0041b3ab: интерпретатор записей MLADDER */
int32_t P140_SndLoadWav(int32_t n, const char *path);    /* 0048bf9a: WAV → буфер DirectSound; −1 — ошибка */
int32_t P140_SndInit(int32_t drv, int32_t arg, int32_t eax); /* 005233be: сброс таблиц звука, запуск драйвера; 1 — успех */
void    P140_BankLine(char *line);                       /* 00524bd8: строка банка сэмплов «ИМЯ /LOOP /2D /FREQ= /VOL= /PRI=» */
void    P140_MrkFly(void);                               /* 004e9bbf: полёт маркера-вертолёта за машиной игрока */
/* gvar-img v2.03 begin (tools/gen_gvar_img.py) */
#if !defined(RE_HOOK_BUILD) && !defined(RE_GVAR_PLAIN)
#undef P140_KeyStr
#define P140_KeyStr (*(p140_keystr_t *)re_gvar(0x0054b4b4u, sizeof(p140_keystr_t), (void *)&P140_KeyStr))
#undef P140_KeyName
#define P140_KeyName (*(p140_keyname_t *)re_gvar(0x0054b080u, sizeof(p140_keyname_t), (void *)&P140_KeyName))
#undef P140_FrSelA
#define P140_FrSelA (*(int32_t *)re_gvar(0x005fe960u, sizeof(int32_t), (void *)&P140_FrSelA))
#undef P140_FrSelB
#define P140_FrSelB (*(int32_t *)re_gvar(0x005fe964u, sizeof(int32_t), (void *)&P140_FrSelB))
#undef P140_FrQuit
#define P140_FrQuit (*(int32_t *)re_gvar(0x005fe968u, sizeof(int32_t), (void *)&P140_FrQuit))
#undef P140_B91BC0
#define P140_B91BC0 (*(int32_t *)re_gvar(0x00b91bc0u, sizeof(int32_t), (void *)&P140_B91BC0))
#undef P140_B1F434
#define P140_B1F434 (*(int32_t *)re_gvar(0x00b1f434u, sizeof(int32_t), (void *)&P140_B1F434))
#undef P140_Mrk2644
#define P140_Mrk2644 (*(int32_t *)re_gvar(0x00d02644u, sizeof(int32_t), (void *)&P140_Mrk2644))
#undef P140_MrkVel
#define P140_MrkVel (*(p140_f3_t *)re_gvar(0x00b31ea8u, sizeof(p140_f3_t), (void *)&P140_MrkVel))
#endif
/* gvar-img v2.03 end */
