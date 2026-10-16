#pragma once
#include "gvar.h"
#include "unported.h"
#include "engine.h"
#include "crt.h"
#include "director.h"
#include "globalsets.h"
#include "smallfuncs2.h"
#include <stddef.h>
#include "uihandlers3.h"
#include "ported6.h"
#include "ported7.h"
#include "ported8.h"
#include "ported13.h"
#include "ported21.h"
#include "ported24.h"
#include "ported26.h"
#include "ported33.h"
#include "ported36.h"
#include "ported42.h"
#include "ported47.h"
#include "ported51.h"
#include "ported55.h"
#include "ported59.h"
#include "ported62.h"
#include "ported68.h"
#include "ported69.h"
#include <stdint.h>
/* Шаг D: 10 функций (все cdecl) — освобождение записи трафика, сдвиг строк, сброс счётчиков HUD, 8-бит текстура -> 16 бит,
   выбор Glide-устройства, оценка расстояния, разбор чисел скрипта, значок SKID, опрос клавиш. */
typedef uint8_t p74_dist_t[65];
typedef uint8_t p74_keys_t[256];
typedef int32_t p74_dev_t[16 * 19];                  /* 16 записей по 0x4c байт; +0 — тип устройства (0 Glide, 1 D3D) */
typedef uint8_t p74_cars_t[16 * 0xcd8];
typedef int32_t p74_i5_t[5];
typedef int32_t p74_i4_t[4];
typedef int32_t p74_rows_t[0x1000];
typedef int32_t p74_rowtab_t[16 * 3];
#define P74_DistTab  GAME_VAR(p74_dist_t, P74_DistTab, 0x0055272c)
#define P74_KeyA     GAME_VAR(p74_keys_t, P74_KeyA, 0x0054ae10)
#define P74_KeyB     GAME_VAR(p74_keys_t, P74_KeyB, 0x0054af10)
#define P74_DevTab   GAME_VAR(p74_dev_t, P74_DevTab, 0x01270ec0)
#define P74_Cars     GAME_VAR(p74_cars_t, P74_Cars, 0x0112e6b4)
#define P74_C4DA58   GAME_VAR(int32_t, P74_C4DA58, 0x00c4da58)
#define P74_B5A858   GAME_VAR(p74_i5_t, P74_B5A858, 0x00b5a858)
#define P74_B5A86C   GAME_VAR(p74_i5_t, P74_B5A86C, 0x00b5a86c)
#define P74_B5A880   GAME_VAR(p74_i5_t, P74_B5A880, 0x00b5a880)
#define P74_C4D7A0   GAME_VAR(p74_i5_t, P74_C4D7A0, 0x00c4d7a0)
#define P74_B5A89C   GAME_VAR(int32_t, P74_B5A89C, 0x00b5a89c)
#define P74_B5A894   GAME_VAR(uint8_t, P74_B5A894, 0x00b5a894)
#define P74_C4D668   GAME_VAR(int32_t, P74_C4D668, 0x00c4d668)
#define P74_C4BDE0   GAME_VAR(int32_t, P74_C4BDE0, 0x00c4bde0)
#define P74_C54D08   GAME_VAR(int32_t, P74_C54D08, 0x00c54d08)
#define P74_SkidA    GAME_VAR(p74_i4_t, P74_SkidA, 0x00bdfae0)
#define P74_SkidB    GAME_VAR(p74_i4_t, P74_SkidB, 0x00bdfb10)
#define P74_SkidC    GAME_VAR(p74_i4_t, P74_SkidC, 0x00bdfab0)
#define P74_SkidD    GAME_VAR(p74_i4_t, P74_SkidD, 0x00bdfb00)
#define P74_Skid     GAME_VAR(uint8_t *, P74_Skid, 0x00b5c90c)
#define P74_Rows     GAME_VAR(p74_rows_t, P74_Rows, 0x012577e0)   /* массив значений; индексы строк берутся из таблицы */
#define P74_RowTab   GAME_VAR(p74_rowtab_t, P74_RowTab, 0x00572a80) /* 16 записей по 12 байт: начало, конец, маска кадров */
#ifndef RE_HOOK_BUILD
#pragma push_macro("P74_DistTab") /*gvi*/
#undef P74_DistTab /*gvi*/
#pragma push_macro("P74_KeyA") /*gvi*/
#undef P74_KeyA /*gvi*/
#pragma push_macro("P74_KeyB") /*gvi*/
#undef P74_KeyB /*gvi*/
extern p74_dist_t P74_DistTab; extern p74_keys_t P74_KeyA, P74_KeyB;
#pragma pop_macro("P74_KeyB") /*gvi*/
#pragma pop_macro("P74_KeyA") /*gvi*/
#pragma pop_macro("P74_DistTab") /*gvi*/
#pragma push_macro("P74_DevTab") /*gvi*/
#undef P74_DevTab /*gvi*/
#pragma push_macro("P74_Cars") /*gvi*/
#undef P74_Cars /*gvi*/
#pragma push_macro("P74_C4DA58") /*gvi*/
#undef P74_C4DA58 /*gvi*/
#pragma push_macro("P74_B5A89C") /*gvi*/
#undef P74_B5A89C /*gvi*/
#pragma push_macro("P74_C4D668") /*gvi*/
#undef P74_C4D668 /*gvi*/
#pragma push_macro("P74_C4BDE0") /*gvi*/
#undef P74_C4BDE0 /*gvi*/
#pragma push_macro("P74_C54D08") /*gvi*/
#undef P74_C54D08 /*gvi*/
extern p74_dev_t P74_DevTab; extern p74_cars_t P74_Cars; extern int32_t P74_C4DA58, P74_B5A89C, P74_C4D668, P74_C4BDE0, P74_C54D08;
#pragma pop_macro("P74_C54D08") /*gvi*/
#pragma pop_macro("P74_C4BDE0") /*gvi*/
#pragma pop_macro("P74_C4D668") /*gvi*/
#pragma pop_macro("P74_B5A89C") /*gvi*/
#pragma pop_macro("P74_C4DA58") /*gvi*/
#pragma pop_macro("P74_Cars") /*gvi*/
#pragma pop_macro("P74_DevTab") /*gvi*/
#pragma push_macro("P74_B5A858") /*gvi*/
#undef P74_B5A858 /*gvi*/
#pragma push_macro("P74_B5A86C") /*gvi*/
#undef P74_B5A86C /*gvi*/
#pragma push_macro("P74_B5A880") /*gvi*/
#undef P74_B5A880 /*gvi*/
#pragma push_macro("P74_C4D7A0") /*gvi*/
#undef P74_C4D7A0 /*gvi*/
#pragma push_macro("P74_B5A894") /*gvi*/
#undef P74_B5A894 /*gvi*/
extern p74_i5_t P74_B5A858, P74_B5A86C, P74_B5A880, P74_C4D7A0; extern uint8_t P74_B5A894;
#pragma pop_macro("P74_B5A894") /*gvi*/
#pragma pop_macro("P74_C4D7A0") /*gvi*/
#pragma pop_macro("P74_B5A880") /*gvi*/
#pragma pop_macro("P74_B5A86C") /*gvi*/
#pragma pop_macro("P74_B5A858") /*gvi*/
#pragma push_macro("P74_SkidA") /*gvi*/
#undef P74_SkidA /*gvi*/
#pragma push_macro("P74_SkidB") /*gvi*/
#undef P74_SkidB /*gvi*/
#pragma push_macro("P74_SkidC") /*gvi*/
#undef P74_SkidC /*gvi*/
#pragma push_macro("P74_SkidD") /*gvi*/
#undef P74_SkidD /*gvi*/
extern p74_i4_t P74_SkidA, P74_SkidB, P74_SkidC, P74_SkidD; extern uint8_t *P74_Skid;
#pragma pop_macro("P74_SkidD") /*gvi*/
#pragma pop_macro("P74_SkidC") /*gvi*/
#pragma pop_macro("P74_SkidB") /*gvi*/
#pragma pop_macro("P74_SkidA") /*gvi*/
#pragma push_macro("P74_Rows") /*gvi*/
#undef P74_Rows /*gvi*/
#pragma push_macro("P74_RowTab") /*gvi*/
#undef P74_RowTab /*gvi*/
extern p74_rows_t P74_Rows; extern p74_rowtab_t P74_RowTab;
#pragma pop_macro("P74_RowTab") /*gvi*/
#pragma pop_macro("P74_Rows") /*gvi*/
#endif
void    P74_InitConsts(void);                                         /* native: таблицы из .data (p74_data.h) */
void    P74_FreeTraffic(int32_t i);                                   /* 00493ece: освободить запись трафика i (0x54 байта) */
void    P74_ShiftRows(void);                                          /* 004ffad8: циклический сдвиг строк массива 012577e0 по таблице 00572a80 */
void    P74_ResetHud(void);                                           /* 005186ce: сброс счётчиков (кадр+1, массивы по 5) */
void    P74_Conv8to16(const uint8_t *src, const uint8_t *pal, uint16_t *dst, int32_t pitch); /* 004229fa: 256x256 индексов -> 16 бит */
void    P74_DevSelect(int32_t idx, int32_t a, int32_t b);             /* 00424530: выбрать устройство Glide/D3D */
int32_t P74_Dist(int32_t x, int32_t z, int32_t ox, int32_t oz);       /* 004a7f0e: приближённое расстояние до игрока по таблице 0055272c */
int32_t P74_ParseFloat(char *s, int32_t idx);                         /* 004a4f7d: число с плавающей точкой -> слово камеры idx (0..3) */
char   *P74_ParseShorts(char *s, uint16_t *out, int32_t n);           /* 004a5afb: n коротких чисел через запятую; дальше — SkipLine004A59C6 (указатель после конца строки), NULL при ошибке */
void    P74_SkidInit(void);                                           /* 0051d440: значок SKID и сброс таблиц */
int32_t P74_KeyScan(void);                                            /* 0040efd5: клавиша по таблице раскладки (-3 Esc, -2 Enter, -1 Backspace) */
/* gvar-img v2.03 begin (tools/gen_gvar_img.py) */
#if !defined(RE_HOOK_BUILD) && !defined(RE_GVAR_PLAIN)
#undef P74_DistTab
#define P74_DistTab (*(p74_dist_t *)re_gvar(0x0055272cu, sizeof(p74_dist_t), (void *)&P74_DistTab))
#undef P74_KeyA
#define P74_KeyA (*(p74_keys_t *)re_gvar(0x0054ae10u, sizeof(p74_keys_t), (void *)&P74_KeyA))
#undef P74_KeyB
#define P74_KeyB (*(p74_keys_t *)re_gvar(0x0054af10u, sizeof(p74_keys_t), (void *)&P74_KeyB))
#undef P74_DevTab
#define P74_DevTab (*(p74_dev_t *)re_gvar(0x01270ec0u, sizeof(p74_dev_t), (void *)&P74_DevTab))
#undef P74_Cars
#define P74_Cars (*(p74_cars_t *)re_gvar(0x0112e6b4u, sizeof(p74_cars_t), (void *)&P74_Cars))
#undef P74_C4DA58
#define P74_C4DA58 (*(int32_t *)re_gvar(0x00c4da58u, sizeof(int32_t), (void *)&P74_C4DA58))
#undef P74_B5A858
#define P74_B5A858 (*(p74_i5_t *)re_gvar(0x00b5a858u, sizeof(p74_i5_t), (void *)&P74_B5A858))
#undef P74_B5A86C
#define P74_B5A86C (*(p74_i5_t *)re_gvar(0x00b5a86cu, sizeof(p74_i5_t), (void *)&P74_B5A86C))
#undef P74_B5A880
#define P74_B5A880 (*(p74_i5_t *)re_gvar(0x00b5a880u, sizeof(p74_i5_t), (void *)&P74_B5A880))
#undef P74_C4D7A0
#define P74_C4D7A0 (*(p74_i5_t *)re_gvar(0x00c4d7a0u, sizeof(p74_i5_t), (void *)&P74_C4D7A0))
#undef P74_B5A89C
#define P74_B5A89C (*(int32_t *)re_gvar(0x00b5a89cu, sizeof(int32_t), (void *)&P74_B5A89C))
#undef P74_B5A894
#define P74_B5A894 (*(uint8_t *)re_gvar(0x00b5a894u, sizeof(uint8_t), (void *)&P74_B5A894))
#undef P74_C4D668
#define P74_C4D668 (*(int32_t *)re_gvar(0x00c4d668u, sizeof(int32_t), (void *)&P74_C4D668))
#undef P74_C4BDE0
#define P74_C4BDE0 (*(int32_t *)re_gvar(0x00c4bde0u, sizeof(int32_t), (void *)&P74_C4BDE0))
#undef P74_C54D08
#define P74_C54D08 (*(int32_t *)re_gvar(0x00c54d08u, sizeof(int32_t), (void *)&P74_C54D08))
#undef P74_SkidA
#define P74_SkidA (*(p74_i4_t *)re_gvar(0x00bdfae0u, sizeof(p74_i4_t), (void *)&P74_SkidA))
#undef P74_SkidB
#define P74_SkidB (*(p74_i4_t *)re_gvar(0x00bdfb10u, sizeof(p74_i4_t), (void *)&P74_SkidB))
#undef P74_SkidC
#define P74_SkidC (*(p74_i4_t *)re_gvar(0x00bdfab0u, sizeof(p74_i4_t), (void *)&P74_SkidC))
#undef P74_SkidD
#define P74_SkidD (*(p74_i4_t *)re_gvar(0x00bdfb00u, sizeof(p74_i4_t), (void *)&P74_SkidD))
#undef P74_Rows
#define P74_Rows (*(p74_rows_t *)re_gvar(0x012577e0u, sizeof(p74_rows_t), (void *)&P74_Rows))
#undef P74_RowTab
#define P74_RowTab (*(p74_rowtab_t *)re_gvar(0x00572a80u, sizeof(p74_rowtab_t), (void *)&P74_RowTab))
#endif
/* gvar-img v2.03 end */
