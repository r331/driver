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
#ifdef RE_HOOK_BUILD
#define P21_FpsLast  (*(uint32_t*)0x00b202f8)
#define P21_FpsVal   (*(uint32_t*)0x00b202f4)
#define P21_FpsCnt   (*(int32_t*)0x00b202fc)
#else
extern uint32_t P21_FpsLast, P21_FpsVal; extern int32_t P21_FpsCnt;
#endif
void P21_DrawFps(void); /* 004d53e8: FPS counter text (plat_time_ms) */
#define P21_FrameFlagA  GAME_VAR(int32_t, P21_FrameFlagA, 0x00575f38)
#define P21_FrameFlagB  GAME_VAR(int32_t, P21_FrameFlagB, 0x00575f34)
#define P21_FrameMin    GAME_VAR(int32_t, P21_FrameMin, 0x00575eec)
#define P21_FrameBase   GAME_VAR(uint32_t, P21_FrameBase, 0x00b2c3a0)
#define P21_FrameTotal  GAME_VAR(int32_t, P21_FrameTotal, 0x00b87e78)
#ifndef RE_HOOK_BUILD
extern int32_t P21_FrameFlagA, P21_FrameFlagB, P21_FrameMin, P21_FrameTotal;
extern uint32_t P21_FrameBase;
#endif
uint32_t P21_FrameTicks(void); /* 004d78f3: 20ms frame ticks, capped at 10 */
#ifdef RE_HOOK_BUILD
#define P21_Fps2Last (*(uint32_t*)0x00b20260)
#define P21_Fps2Val  (*(uint32_t*)0x00b20264)
#define P21_Fps2Cnt  (*(int32_t*)0x00b20268)
#define P21_Font8    ((const uint8_t*)0x00554414)
#else
extern uint32_t P21_Fps2Last, P21_Fps2Val; extern int32_t P21_Fps2Cnt;
extern uint8_t P21_Font8[256 * 8];
#endif
void P21_FpsToBuf(uint8_t* dst, uint8_t fg, uint8_t bg); /* 004bf910: FPS text into 8bpp buffer, 640 stride */
