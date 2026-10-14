#pragma once
#include "gvar.h"
#include <stdint.h>
/* Поиск в таблице строк (последовательные C-строки). */
#define P20_Names  GAME_VAR(char*, P20_Names, 0x00b31ed8)
#define P20_Count  GAME_VAR(int32_t, P20_Count, 0x00cf2f8c)
#ifdef RE_HOOK_BUILD
#define P20_Values ((int32_t*)0x00cfe7a0)
#else
extern int32_t P20_Values[4096];
extern char* P20_Names; extern int32_t P20_Count;
#endif
int32_t P20_FindNameNoCase(const char* s); /* 004ec837: индекс или -1 */
int32_t P20_FindNameValue(const char* s);  /* 004ec8a8: значение или 0 */
