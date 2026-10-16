#pragma once
#include <stdint.h>
#include "gvar.h"
/* v1.77: ported132 — цикл экрана меню 00417b80, такт логики кадра 004d4bfb, отрисовка кадра 004d4fc5, дым 004b9287,
   огни сцены 004ca135, загрузка облёта .FBD 0049f20a. Все функции cdecl (work/rets.py: ret без операнда). */
#define P132_B87EC8   GAME_VAR(int32_t, P132_B87EC8, 0x00b87ec8)   /* 004d4fc5: запрос снимка экрана 004d9951 */
#ifndef RE_HOOK_BUILD
#pragma push_macro("P132_B87EC8") /*gvi*/
#undef P132_B87EC8 /*gvi*/
extern int32_t P132_B87EC8;
#pragma pop_macro("P132_B87EC8") /*gvi*/
#endif
int32_t P132_MenuLoop(uint32_t tab);    /* 00417b80: цикл экрана меню (tab → 005fea48), → P67_Res51C */
void    P132_GameLogic(void);           /* 004d4bfb: такт логики кадра игры */
void    P132_GameDraw(void);            /* 004d4fc5: отрисовка кадра игры, отладочные строки погони */
void    P132_Smoke(const float *pos, const float *vel, int32_t a, int32_t b, int32_t step, int32_t c, int32_t mode,
                   float f, int32_t jitter);   /* 004b9287: дым — запись пула P95_ObjA (кадры с нечётным P62_Frame) */
void    P132_Lights(void);              /* 004ca135: молния, фары игрока, мигалки, огни трафика и записей 012083c0 */
int32_t P132_LoadFlyby(const char *name);   /* 0049f20a: текстовый .FBD → ключи P99_CamKeys, P99_CamLast; 1 — успех */
/* gvar-img v2.03 begin (tools/gen_gvar_img.py) */
#if !defined(RE_HOOK_BUILD) && !defined(RE_GVAR_PLAIN)
#undef P132_B87EC8
#define P132_B87EC8 (*(int32_t *)re_gvar(0x00b87ec8u, sizeof(int32_t), (void *)&P132_B87EC8))
#endif
/* gvar-img v2.03 end */
