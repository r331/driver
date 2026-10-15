#pragma once
#include "gvar.h"
#include "unported.h"
#include "ported4.h"
#include "ported5.h"
#include "ported6.h"
#include "ported7.h"
#include "ported8.h"
#include "ported11.h"
#include "ported12.h"
#include "ported21.h"
#include "ported26.h"
#include "smallfuncs.h"
#include "globalsets.h"
#include "uihandlers3.h"
#include <stdint.h>
/* Мелкие функции (шаг D): обёртки Glide (туман, загрузка мипмапа), переключатель меню, сброс слотов, диспетчер HUD,
   запуск FMV, подсветка строки. Все cdecl. Зависящие от .data таблицы (цвета 00552e0c) в native пустые до init. */
#define P52_FogOn   GAME_VAR(int32_t, P52_FogOn, 0x00b87e88)    /* нужен ли туман */
#define P52_NoTrail GAME_VAR(uint8_t, P52_NoTrail, 0x0056002c)  /* 0 — маска цвета Glide включается вокруг очистки */
#define P52_MenuCnt GAME_VAR(int32_t, P52_MenuCnt, 0x00b5a750)
#define P52_MenuA   GAME_VAR(int32_t, P52_MenuA, 0x00b5a754)
#define P52_MenuB   GAME_VAR(int32_t, P52_MenuB, 0x00b5a758)
#define P52_MenuC   GAME_VAR(int32_t, P52_MenuC, 0x00b5a75c)
#define P52_ResetA  GAME_VAR(int32_t, P52_ResetA, 0x00b5a8a8)
#define P52_ResetB  GAME_VAR(uint8_t, P52_ResetB, 0x01137354)
#define P52_ResetC  GAME_VAR(int32_t, P52_ResetC, 0x011237b8)
#define P52_Ones0   GAME_VAR(int32_t, P52_Ones0, 0x010ffa30)
#define P52_Ones1   GAME_VAR(int32_t, P52_Ones1, 0x010ffa34)
#define P52_Ones2   GAME_VAR(int32_t, P52_Ones2, 0x010ffa38)
#define P52_Ones3   GAME_VAR(int32_t, P52_Ones3, 0x010ffa3c)
typedef uint8_t p52_fog_t[64];
typedef uint8_t p52_names_t[0x11 * 16];
typedef uint8_t p52_colors_t[4 * 32];
#define P52_FogTab   GAME_VAR(p52_fog_t, P52_FogTab, 0x01252b80)      /* GrFog_t[64] */
#define P52_NameTab  GAME_VAR(p52_names_t, P52_NameTab, 0x00b5a6a8)   /* записи по 0x11 байт */
#define P52_ColorTab GAME_VAR(p52_colors_t, P52_ColorTab, 0x00552e0c) /* RGB + 1 байт, по 4 на запись */
#ifndef RE_HOOK_BUILD
extern int32_t P52_FogOn, P52_MenuCnt, P52_MenuA, P52_MenuB, P52_MenuC, P52_ResetA, P52_ResetC, P52_Ones0, P52_Ones1, P52_Ones2, P52_Ones3;
extern uint8_t P52_NoTrail, P52_ResetB;
extern p52_fog_t P52_FogTab; extern p52_names_t P52_NameTab; extern p52_colors_t P52_ColorTab;
#endif
void    P52_GlideFogSetup(void);                  /* 0042626e: цвет тумана 0xaaaaaa или 0, таблица exp-тумана, grFogTable */
void    P52_GlideFogMode(void);                   /* 004264bd: grFogMode(0|2), очистка буфера с маской цвета */
void    P52_TexDownloadMipMap(int32_t a, int32_t b, int32_t c, int32_t d, int32_t e); /* 0042486b: Glide (режим 0) или 0041d53c (режим 1) */
void    P52_MenuStepToggle(void);                 /* 00510084: цикл флагов кадра (575f34/38/eec), затем 0050fbf4 */
void    P52_HudDispatch(void);                    /* 004e59b9: по режиму 4/5 вызвать отрисовку HUD */
void    P52_ResetSlots(void);                     /* 004aad65: сброс таблиц слотов, четыре флага = 1 */
int32_t P52_FmvStart(int32_t a);                  /* 0048abdc: остановить, открыть, запустить; 1 — успех */
void    P52_DrawLabel(int32_t a, int32_t b, int32_t c); /* 004a9e0a: цвет из таблицы 00552e0c, текст по высоте */
void    P52_MenuReload(void);                     /* 00510728: сброс счётчиков, перечитать запись меню, 00510784 */
