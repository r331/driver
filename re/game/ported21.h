#pragma once
#include "gvar.h"
#include <stdint.h>
/* Мелкие функции: проверка клетки карты, сложение MSF-времени, оси ввода, счётчик записей, сравнение префикса. */
#define P21_GridDiv    GAME_VAR(int32_t, P21_GridDiv, 0x00562d38)
#define P21_GridRadius GAME_VAR(int32_t, P21_GridRadius, 0x00cf56b8)
#define P21_GridStride GAME_VAR(int32_t, P21_GridStride, 0x00d00258)
#define P21_AxisValue  GAME_VAR(int32_t, P21_AxisValue, 0x00b31e20)
#define P21_EntryCount GAME_VAR(int32_t, P21_EntryCount, 0x00575ee4)
#ifdef RE_HOOK_BUILD
#define P21_AxisOut   ((uint8_t*)0x00d04b00)
#define P21_AxisSrc   ((uint8_t*)0x00b31db8)
#define P21_Entries   ((uint8_t*)0x011443e0)
#else
extern int32_t P21_GridDiv, P21_GridRadius, P21_GridStride, P21_AxisValue, P21_EntryCount;
extern uint8_t P21_AxisOut[256], P21_AxisSrc[256], P21_Entries[0x54 * 64];
#endif
#define P21_ENTRY_SIZE 0x54
int32_t  P21_GridCellSet(int32_t idx, const uint8_t* map, int32_t cx, int32_t cy); /* 004ecfbd */
uint32_t P21_AddMsf(uint32_t a, uint32_t b);                                       /* 005250cb */
void     P21_SetAxisByte(uint8_t kind, uint32_t slot);                             /* 004e43b7 */
int32_t  P21_CountActiveEntries(int32_t owner);                                    /* 0049509a */
uint32_t P21_MatchPrefix(const uint8_t* s, const uint8_t* prefix);                 /* 004a519a */
#ifdef RE_HOOK_BUILD
#define P21_NameTable ((const char**)0x0054b410)
#define P21_ErrorName ((const char*)0x0054b6a4)
#else
extern const char* P21_NameTable[0x23];
extern const char* P21_ErrorName;
#endif
const char* P21_GetNameByIndex(uint8_t idx); /* 0040f14a */
#ifdef RE_HOOK_BUILD
#define P21_ClockBuf ((char*)0x00b20384)
#else
extern char P21_ClockBuf[32];
#endif
void P21_DrawClock(void); /* 004d986e: HH:MM:SS clock, uses plat_local_hms */
