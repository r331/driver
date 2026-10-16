#pragma once
#include <stdint.h>
#include "gvar.h"
/* v1.76: ported131 — выбор пункта меню 0041b7d1, строка скрипта миссии 004f621d, старт облёта 0049e911, кадр игры
   004d4a63, брызги 004cc1a2 и капли дождя 004cbc1e (Glide, вершины p85_rv на стеке).
   Все функции cdecl (work/rets.py: ret без операнда). */
#define P131_Skip     GAME_VAR(int32_t, P131_Skip, 0x00d11930)     /* 004d4a63: 1 на время двух холостых кадров при старте */
#ifndef RE_HOOK_BUILD
extern int32_t P131_Skip;
#endif
uint32_t P131_MenuPick(uint32_t tab);   /* 0041b7d1: tab — адрес таблицы пунктов (по 8: id, значение); → значение (+4) */
int32_t  P131_ScriptLine(void);         /* 004f621d: разбор строки P65_Line токенами P65_Tok; 0/6/код ошибки */
void     P131_FlybyStart(void);         /* 0049e911: SCRIPTS\FLYBY\MISSION%d.FBD → ключи камеры P99_CamKeys */
void     P131_GameFrame(void);          /* 004d4a63: кадр игры (такты 004aaddf/004d4bfb/004d4fc5, CD-трек) */
void     P131_Splash(void);             /* 004cc1a2: 50 брызг дождя у камеры (значок SPLASH) */
void     P131_RainDraw(void);           /* 004cbc1e: капли дождя из стека скрипта (значок RFLECT) */
void     P131_MissionObj(uint32_t m, const uint8_t *obj, int32_t mode);   /* 004fef26: модель + объекты миссии (огни, дым, качание) */
#define P131_BDFAA4   GAME_VAR(int32_t, P131_BDFAA4, 0x00bdfaa4)   /* 00507925: флаг 2 — стрелка радара треугольником */
#ifndef RE_HOOK_BUILD
extern int32_t P131_BDFAA4;
#endif
void     P131_RadarArrow(int32_t i);     /* 00507925: стрелка радара к цели P58_Objs[i] */
typedef uint8_t p131_denb_t[0x1140 - 0x170];
typedef uint8_t p131_denc_t[0x1140];
#define P131_DenB     GAME_VAR(p131_denb_t, P131_DenB, 0x0055a864)  /* вмятины: хвост блока 0055a6f4 после P28_Dst2 */
#define P131_DenC     GAME_VAR(p131_denc_t, P131_DenC, 0x0055b834)  /* вмятины: третий блок */
#ifndef RE_HOOK_BUILD
extern p131_denb_t P131_DenB; extern p131_denc_t P131_DenC;
#endif
void     P131_LoadCosDen(int32_t junk);  /* 004ef9cd: .COS и .DEN уровня (junk — мусор ECX, звать с 0) */
typedef uint16_t p131_camang_t[4];
#define P131_CamAng   GAME_VAR(p131_camang_t, P131_CamAng, 0x01137380)   /* углы камеры сценария (4 × uint16) */
#define P131_AngD     GAME_VAR(uint16_t, P131_AngD, 0x00b1c26e)          /* старшее слово 00b1c26c (за P59_AngC) */
#ifndef RE_HOOK_BUILD
extern p131_camang_t P131_CamAng; extern uint16_t P131_AngD;
#endif
void     P131_CamShake(void);           /* 0049e7a8: углы, подтяжка к столкновению, дрожание камеры */
