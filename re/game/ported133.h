#pragma once
#include <stdint.h>
#include "gvar.h"
/* v1.78: ported133 — загрузка config.dat 004055e8, кадр камеры 0049f6c7, модели событий 004cf84c, зеркало заднего вида
   004f2360, такт трафика 004967d2. Все функции cdecl (work/rets.py: ret без операнда). */
#define P133_1137320  GAME_VAR(int32_t, P133_1137320, 0x01137320)   /* 0049f6c7: ← 01137364 (P98_FreeTurn), старшее слово — P61_Heading */
#ifndef RE_HOOK_BUILD
#pragma push_macro("P133_1137320") /*gvi*/
#undef P133_1137320 /*gvi*/
extern int32_t P133_1137320;
#pragma pop_macro("P133_1137320") /*gvi*/
#endif
int32_t P133_LoadConfig(void);          /* 004055e8: config.dat (подпись 0x93587031, сумма 0x10c байт) → настройки; 1 — успех */
void    P133_CamUpdate(int32_t lock);   /* 0049f6c7: режим камеры 01137324, сброс при уходе от игрока */
void    P133_EventModels(void);         /* 004cf84c: модели объектов событий G00D12408 (+дым у моделей 3 в уровне 0) */
void    P133_MirrorDraw(void);          /* 004f2360: зеркало заднего вида — сцена с развёрнутой машиной в окне 4/11 × 2/15 */
void    P133_TrafficTick(void);         /* 004967d2: такт записей трафика 011443e0 (обработчик по типу из .data 00551308) */
/* gvar-img v2.03 begin (tools/gen_gvar_img.py) */
#if !defined(RE_HOOK_BUILD) && !defined(RE_GVAR_PLAIN)
#undef P133_1137320
#define P133_1137320 (*(int32_t *)re_gvar(0x01137320u, sizeof(int32_t), (void *)&P133_1137320))
#endif
/* gvar-img v2.03 end */
