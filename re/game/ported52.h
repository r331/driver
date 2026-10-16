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
#pragma push_macro("P52_FogOn") /*gvi*/
#undef P52_FogOn /*gvi*/
#pragma push_macro("P52_MenuCnt") /*gvi*/
#undef P52_MenuCnt /*gvi*/
#pragma push_macro("P52_MenuA") /*gvi*/
#undef P52_MenuA /*gvi*/
#pragma push_macro("P52_MenuB") /*gvi*/
#undef P52_MenuB /*gvi*/
#pragma push_macro("P52_MenuC") /*gvi*/
#undef P52_MenuC /*gvi*/
#pragma push_macro("P52_ResetA") /*gvi*/
#undef P52_ResetA /*gvi*/
#pragma push_macro("P52_ResetC") /*gvi*/
#undef P52_ResetC /*gvi*/
#pragma push_macro("P52_Ones0") /*gvi*/
#undef P52_Ones0 /*gvi*/
#pragma push_macro("P52_Ones1") /*gvi*/
#undef P52_Ones1 /*gvi*/
#pragma push_macro("P52_Ones2") /*gvi*/
#undef P52_Ones2 /*gvi*/
#pragma push_macro("P52_Ones3") /*gvi*/
#undef P52_Ones3 /*gvi*/
extern int32_t P52_FogOn, P52_MenuCnt, P52_MenuA, P52_MenuB, P52_MenuC, P52_ResetA, P52_ResetC, P52_Ones0, P52_Ones1, P52_Ones2, P52_Ones3;
#pragma pop_macro("P52_Ones3") /*gvi*/
#pragma pop_macro("P52_Ones2") /*gvi*/
#pragma pop_macro("P52_Ones1") /*gvi*/
#pragma pop_macro("P52_Ones0") /*gvi*/
#pragma pop_macro("P52_ResetC") /*gvi*/
#pragma pop_macro("P52_ResetA") /*gvi*/
#pragma pop_macro("P52_MenuC") /*gvi*/
#pragma pop_macro("P52_MenuB") /*gvi*/
#pragma pop_macro("P52_MenuA") /*gvi*/
#pragma pop_macro("P52_MenuCnt") /*gvi*/
#pragma pop_macro("P52_FogOn") /*gvi*/
#pragma push_macro("P52_NoTrail") /*gvi*/
#undef P52_NoTrail /*gvi*/
#pragma push_macro("P52_ResetB") /*gvi*/
#undef P52_ResetB /*gvi*/
extern uint8_t P52_NoTrail, P52_ResetB;
#pragma pop_macro("P52_ResetB") /*gvi*/
#pragma pop_macro("P52_NoTrail") /*gvi*/
#pragma push_macro("P52_FogTab") /*gvi*/
#undef P52_FogTab /*gvi*/
#pragma push_macro("P52_NameTab") /*gvi*/
#undef P52_NameTab /*gvi*/
#pragma push_macro("P52_ColorTab") /*gvi*/
#undef P52_ColorTab /*gvi*/
extern p52_fog_t P52_FogTab; extern p52_names_t P52_NameTab; extern p52_colors_t P52_ColorTab;
#pragma pop_macro("P52_ColorTab") /*gvi*/
#pragma pop_macro("P52_NameTab") /*gvi*/
#pragma pop_macro("P52_FogTab") /*gvi*/
#endif
void    P52_GlideFogSetup(void);                  /* 0042626e: цвет тумана 0xaaaaaa или 0, таблица exp-тумана, grFogTable */
void    P52_GlideFogMode(void);                   /* 004264bd: grFogMode(0|2), очистка буфера с маской цвета */
void    P52_TexDownloadMipMap(int32_t a, int32_t b, int32_t c, int32_t d, int32_t e); /* 0042486b: Glide (режим 0) или 0041d53c (режим 1) */
void    P52_MenuStepToggle(void);                 /* 00510084: цикл флагов кадра (575f34/38/eec), затем 0050fbf4 */
void    P52_HudDispatch(void);                    /* 004e59b9: по режиму 4/5 вызвать отрисовку HUD */
void    P52_ResetSlots(void);                     /* 004aad65: сброс таблиц слотов, четыре флага = 1 */
int32_t P52_FmvStart(const char *a);                  /* 0048abdc: остановить, открыть, запустить; 1 — успех */
void    P52_DrawLabel(int32_t a, int32_t b, int32_t c); /* 004a9e0a: цвет из таблицы 00552e0c, текст по высоте */
void    P52_MenuReload(void);                     /* 00510728: сброс счётчиков, перечитать запись меню, 00510784 */
/* gvar-img v2.03 begin (tools/gen_gvar_img.py) */
#if !defined(RE_HOOK_BUILD) && !defined(RE_GVAR_PLAIN)
#undef P52_FogOn
#define P52_FogOn (*(int32_t *)re_gvar(0x00b87e88u, sizeof(int32_t), (void *)&P52_FogOn))
#undef P52_NoTrail
#define P52_NoTrail (*(uint8_t *)re_gvar(0x0056002cu, sizeof(uint8_t), (void *)&P52_NoTrail))
#undef P52_MenuCnt
#define P52_MenuCnt (*(int32_t *)re_gvar(0x00b5a750u, sizeof(int32_t), (void *)&P52_MenuCnt))
#undef P52_MenuA
#define P52_MenuA (*(int32_t *)re_gvar(0x00b5a754u, sizeof(int32_t), (void *)&P52_MenuA))
#undef P52_MenuB
#define P52_MenuB (*(int32_t *)re_gvar(0x00b5a758u, sizeof(int32_t), (void *)&P52_MenuB))
#undef P52_MenuC
#define P52_MenuC (*(int32_t *)re_gvar(0x00b5a75cu, sizeof(int32_t), (void *)&P52_MenuC))
#undef P52_ResetA
#define P52_ResetA (*(int32_t *)re_gvar(0x00b5a8a8u, sizeof(int32_t), (void *)&P52_ResetA))
#undef P52_ResetB
#define P52_ResetB (*(uint8_t *)re_gvar(0x01137354u, sizeof(uint8_t), (void *)&P52_ResetB))
#undef P52_ResetC
#define P52_ResetC (*(int32_t *)re_gvar(0x011237b8u, sizeof(int32_t), (void *)&P52_ResetC))
#undef P52_Ones0
#define P52_Ones0 (*(int32_t *)re_gvar(0x010ffa30u, sizeof(int32_t), (void *)&P52_Ones0))
#undef P52_Ones1
#define P52_Ones1 (*(int32_t *)re_gvar(0x010ffa34u, sizeof(int32_t), (void *)&P52_Ones1))
#undef P52_Ones2
#define P52_Ones2 (*(int32_t *)re_gvar(0x010ffa38u, sizeof(int32_t), (void *)&P52_Ones2))
#undef P52_Ones3
#define P52_Ones3 (*(int32_t *)re_gvar(0x010ffa3cu, sizeof(int32_t), (void *)&P52_Ones3))
#undef P52_FogTab
#define P52_FogTab (*(p52_fog_t *)re_gvar(0x01252b80u, sizeof(p52_fog_t), (void *)&P52_FogTab))
#undef P52_NameTab
#define P52_NameTab (*(p52_names_t *)re_gvar(0x00b5a6a8u, sizeof(p52_names_t), (void *)&P52_NameTab))
#undef P52_ColorTab
#define P52_ColorTab (*(p52_colors_t *)re_gvar(0x00552e0cu, sizeof(p52_colors_t), (void *)&P52_ColorTab))
#endif
/* gvar-img v2.03 end */
