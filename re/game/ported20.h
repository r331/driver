#pragma once
#include "gvar.h"
#include <stdint.h>
/* Поиск в таблице строк (последовательные C-строки). */
#define P20_Names  GAME_VAR(char*, P20_Names, 0x00b31ed8)
#define P20_Count  GAME_VAR(int32_t, P20_Count, 0x00cf2f8c)
#ifdef RE_HOOK_BUILD
#define P20_Values ((int32_t*)0x00cfe7a0)
#else
/* v2.04: 00cfe7a0 — это таблица моделей P79_ModelTab (в игре — образ данных); отдельный native-массив P20_Values
   оставался нулевым, и 004ec8a8 не находил ни одной модели («Could not find hubcap/clean player car model»). */
#include "ported79.h"
#define P20_Values ((int32_t *)&P79_ModelTab[0])
#pragma push_macro("P20_Count") /*gvi*/
#undef P20_Count /*gvi*/
extern char* P20_Names; extern int32_t P20_Count;
#pragma pop_macro("P20_Count") /*gvi*/
#endif
int32_t P20_FindNameNoCase(const char* s); /* 004ec837: индекс или -1 */
int32_t P20_FindNameValue(const char* s);  /* 004ec8a8: значение или 0 */
/* gvar-img v2.03 begin (tools/gen_gvar_img.py) */
#if !defined(RE_HOOK_BUILD) && !defined(RE_GVAR_PLAIN)
#undef P20_Count
#define P20_Count (*(int32_t *)re_gvar(0x00cf2f8cu, sizeof(int32_t), (void *)&P20_Count))
#endif
/* gvar-img v2.03 end */
