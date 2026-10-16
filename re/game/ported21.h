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
#pragma push_macro("P21_GridDiv") /*gvi*/
#undef P21_GridDiv /*gvi*/
#pragma push_macro("P21_GridRadius") /*gvi*/
#undef P21_GridRadius /*gvi*/
#pragma push_macro("P21_GridStride") /*gvi*/
#undef P21_GridStride /*gvi*/
#pragma push_macro("P21_AxisValue") /*gvi*/
#undef P21_AxisValue /*gvi*/
#pragma push_macro("P21_EntryCount") /*gvi*/
#undef P21_EntryCount /*gvi*/
extern int32_t P21_GridDiv, P21_GridRadius, P21_GridStride, P21_AxisValue, P21_EntryCount;
#pragma pop_macro("P21_EntryCount") /*gvi*/
#pragma pop_macro("P21_AxisValue") /*gvi*/
#pragma pop_macro("P21_GridStride") /*gvi*/
#pragma pop_macro("P21_GridRadius") /*gvi*/
#pragma pop_macro("P21_GridDiv") /*gvi*/
extern uint8_t P21_AxisSrc[256];
#pragma push_macro("A_00D04B00") /*gvi*/
#undef A_00D04B00 /*gvi*/
extern uint8_t A_00D04B00[];
#pragma pop_macro("A_00D04B00") /*gvi*/
#define P21_AxisOut ((uint8_t *)re_gvar(0x00d04b00u, 0x40000u, (void *)&A_00D04B00[0]))   /* v2.03: 00d04b00 — блок клавиш */
#pragma push_macro("TrafficRecs") /*gvi*/
#undef TrafficRecs /*gvi*/
extern uint8_t TrafficRecs[0x40 * 0x54];   /* v1.47: P21_Entries — таблица трафика TrafficRecs */
#pragma pop_macro("TrafficRecs") /*gvi*/
#define P21_Entries ((uint8_t *)re_gvar(0x011443e0u, 0x40 * 0x54, (void *)TrafficRecs))   /* v2.11: через образ данных (re_gvar), иначе — отдельный native-объект */
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
#pragma push_macro("P21_FrameFlagA") /*gvi*/
#undef P21_FrameFlagA /*gvi*/
#pragma push_macro("P21_FrameFlagB") /*gvi*/
#undef P21_FrameFlagB /*gvi*/
#pragma push_macro("P21_FrameMin") /*gvi*/
#undef P21_FrameMin /*gvi*/
#pragma push_macro("P21_FrameTotal") /*gvi*/
#undef P21_FrameTotal /*gvi*/
extern int32_t P21_FrameFlagA, P21_FrameFlagB, P21_FrameMin, P21_FrameTotal;
#pragma pop_macro("P21_FrameTotal") /*gvi*/
#pragma pop_macro("P21_FrameMin") /*gvi*/
#pragma pop_macro("P21_FrameFlagB") /*gvi*/
#pragma pop_macro("P21_FrameFlagA") /*gvi*/
#pragma push_macro("P21_FrameBase") /*gvi*/
#undef P21_FrameBase /*gvi*/
extern uint32_t P21_FrameBase;
#pragma pop_macro("P21_FrameBase") /*gvi*/
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
/* gvar-img v2.03 begin (tools/gen_gvar_img.py) */
#if !defined(RE_HOOK_BUILD) && !defined(RE_GVAR_PLAIN)
#undef P21_GridDiv
#define P21_GridDiv (*(int32_t *)re_gvar(0x00562d38u, sizeof(int32_t), (void *)&P21_GridDiv))
#undef P21_GridRadius
#define P21_GridRadius (*(int32_t *)re_gvar(0x00cf56b8u, sizeof(int32_t), (void *)&P21_GridRadius))
#undef P21_GridStride
#define P21_GridStride (*(int32_t *)re_gvar(0x00d00258u, sizeof(int32_t), (void *)&P21_GridStride))
#undef P21_AxisValue
#define P21_AxisValue (*(int32_t *)re_gvar(0x00b31e20u, sizeof(int32_t), (void *)&P21_AxisValue))
#undef P21_EntryCount
#define P21_EntryCount (*(int32_t *)re_gvar(0x00575ee4u, sizeof(int32_t), (void *)&P21_EntryCount))
#undef P21_FrameFlagA
#define P21_FrameFlagA (*(int32_t *)re_gvar(0x00575f38u, sizeof(int32_t), (void *)&P21_FrameFlagA))
#undef P21_FrameFlagB
#define P21_FrameFlagB (*(int32_t *)re_gvar(0x00575f34u, sizeof(int32_t), (void *)&P21_FrameFlagB))
#undef P21_FrameMin
#define P21_FrameMin (*(int32_t *)re_gvar(0x00575eecu, sizeof(int32_t), (void *)&P21_FrameMin))
#undef P21_FrameBase
#define P21_FrameBase (*(uint32_t *)re_gvar(0x00b2c3a0u, sizeof(uint32_t), (void *)&P21_FrameBase))
#undef P21_FrameTotal
#define P21_FrameTotal (*(int32_t *)re_gvar(0x00b87e78u, sizeof(int32_t), (void *)&P21_FrameTotal))
#endif
/* gvar-img v2.03 end */
