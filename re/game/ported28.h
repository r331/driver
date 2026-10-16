#pragma once
#include "gvar.h"
#include "../platform/plat.h"
#include <stdint.h>
/* Загрузка моделей: события (map.c) и машины уровня. Все __cdecl. Значения-«указатели» на модели
   хранятся 32-битными (как в Game.exe); разыменовываются только в hook-сборке. */
typedef uint32_t p28_evtab_t[0x270];   /* адреса моделей событий (стандарт v1.42: re_ptr/re_addr) */
#define P28_EventModels GAME_VAR(p28_evtab_t, P28_EventModels, 0x00d11a60)
#define P28_EventCount  GAME_VAR(int32_t, P28_EventCount, 0x00d12418)
typedef uint32_t p28_models_t[12];   /* v1.44: ссылки на модели (uint32: hook — адрес Game.exe, native — ссылка арены P79_PTR) */
#define P28_CarClean GAME_VAR(p28_models_t, P28_CarClean, 0x010ddfe0)
#define P28_CarDam   GAME_VAR(p28_models_t, P28_CarDam, 0x010de020)
#define P28_CarLow   GAME_VAR(p28_models_t, P28_CarLow, 0x010de080)
typedef float p28_deltas_t[12][0x410];
#define P28_CarDelta GAME_VAR(p28_deltas_t, P28_CarDelta, 0x010de320)
typedef int32_t p28_sizes_t[12];
#define P28_CarOpsSize GAME_VAR(p28_sizes_t, P28_CarOpsSize, 0x00e00680)
#define P28_CarShine GAME_VAR(int32_t, P28_CarShine, 0x011b6140)
typedef uint8_t p28_clear100_t[0x100];
#define P28_Clear100 GAME_VAR(p28_clear100_t, P28_Clear100, 0x010de120)
typedef uint8_t p28_blk1_t[0x1e0];
typedef uint8_t p28_src1_t[18 * 0x1e0];
typedef uint8_t p28_src2_t[18 * 0x170];
typedef uint8_t p28_blk2_t[0x170];
#define P28_Dst1 GAME_VAR(p28_blk1_t, P28_Dst1, 0x00559074)  /* 6 блоков по 0x50 */
#define P28_Src1 GAME_VAR(p28_src1_t, P28_Src1, 0x005554d4)
#define P28_Src2 GAME_VAR(p28_src2_t, P28_Src2, 0x00557694)
#define P28_Dst2 GAME_VAR(p28_blk2_t, P28_Dst2, 0x0055a6f4)
#define P28_DbgFlag GAME_VAR(int32_t, P28_DbgFlag, 0x00dbb450)
#define P28_ShineFlag GAME_VAR(int32_t, P28_ShineFlag, 0x0055c974)
#define P28_BadGuyFlag GAME_VAR(int32_t, P28_BadGuyFlag, 0x00b87f04)
#ifndef RE_HOOK_BUILD
#pragma push_macro("P28_EventModels") /*gvi*/
#undef P28_EventModels /*gvi*/
#pragma push_macro("P28_EventCount") /*gvi*/
#undef P28_EventCount /*gvi*/
extern p28_evtab_t P28_EventModels; extern int32_t P28_EventCount;
#pragma pop_macro("P28_EventCount") /*gvi*/
#pragma pop_macro("P28_EventModels") /*gvi*/
#pragma push_macro("P28_CarClean") /*gvi*/
#undef P28_CarClean /*gvi*/
#pragma push_macro("P28_CarDam") /*gvi*/
#undef P28_CarDam /*gvi*/
#pragma push_macro("P28_CarLow") /*gvi*/
#undef P28_CarLow /*gvi*/
extern p28_models_t P28_CarClean, P28_CarDam, P28_CarLow;
#pragma pop_macro("P28_CarLow") /*gvi*/
#pragma pop_macro("P28_CarDam") /*gvi*/
#pragma pop_macro("P28_CarClean") /*gvi*/
#pragma push_macro("P28_CarDelta") /*gvi*/
#undef P28_CarDelta /*gvi*/
#pragma push_macro("P28_CarOpsSize") /*gvi*/
#undef P28_CarOpsSize /*gvi*/
#pragma push_macro("P28_CarShine") /*gvi*/
#undef P28_CarShine /*gvi*/
extern p28_deltas_t P28_CarDelta; extern p28_sizes_t P28_CarOpsSize; extern int32_t P28_CarShine;
#pragma pop_macro("P28_CarShine") /*gvi*/
#pragma pop_macro("P28_CarOpsSize") /*gvi*/
#pragma pop_macro("P28_CarDelta") /*gvi*/
#pragma push_macro("P28_Clear100") /*gvi*/
#undef P28_Clear100 /*gvi*/
#pragma push_macro("P28_Dst1") /*gvi*/
#undef P28_Dst1 /*gvi*/
#pragma push_macro("P28_Src1") /*gvi*/
#undef P28_Src1 /*gvi*/
extern p28_clear100_t P28_Clear100; extern p28_blk1_t P28_Dst1; extern p28_src1_t P28_Src1;
#pragma pop_macro("P28_Src1") /*gvi*/
#pragma pop_macro("P28_Dst1") /*gvi*/
#pragma pop_macro("P28_Clear100") /*gvi*/
#pragma push_macro("P28_Src2") /*gvi*/
#undef P28_Src2 /*gvi*/
#pragma push_macro("P28_Dst2") /*gvi*/
#undef P28_Dst2 /*gvi*/
#pragma push_macro("P28_DbgFlag") /*gvi*/
#undef P28_DbgFlag /*gvi*/
#pragma push_macro("P28_ShineFlag") /*gvi*/
#undef P28_ShineFlag /*gvi*/
#pragma push_macro("P28_BadGuyFlag") /*gvi*/
#undef P28_BadGuyFlag /*gvi*/
extern p28_src2_t P28_Src2; extern p28_blk2_t P28_Dst2; extern int32_t P28_DbgFlag, P28_ShineFlag, P28_BadGuyFlag;
#pragma pop_macro("P28_BadGuyFlag") /*gvi*/
#pragma pop_macro("P28_ShineFlag") /*gvi*/
#pragma pop_macro("P28_DbgFlag") /*gvi*/
#pragma pop_macro("P28_Dst2") /*gvi*/
#pragma pop_macro("P28_Src2") /*gvi*/
#endif
void P28_LoadEventModels(void *file); /* 004ec58a: модели событий из файла уровня; нехватка памяти -> MessageBox «Memory Error!» */
void P28_LoadCarModels(void);         /* 004bfc30: модели машин (игрок/полиция/бандит/гражданские), дельты вмятин, размеры операций */
/* gvar-img v2.03 begin (tools/gen_gvar_img.py) */
#if !defined(RE_HOOK_BUILD) && !defined(RE_GVAR_PLAIN)
#undef P28_EventModels
#define P28_EventModels (*(p28_evtab_t *)re_gvar(0x00d11a60u, sizeof(p28_evtab_t), (void *)&P28_EventModels))
#undef P28_EventCount
#define P28_EventCount (*(int32_t *)re_gvar(0x00d12418u, sizeof(int32_t), (void *)&P28_EventCount))
#undef P28_CarClean
#define P28_CarClean (*(p28_models_t *)re_gvar(0x010ddfe0u, sizeof(p28_models_t), (void *)&P28_CarClean))
#undef P28_CarDam
#define P28_CarDam (*(p28_models_t *)re_gvar(0x010de020u, sizeof(p28_models_t), (void *)&P28_CarDam))
#undef P28_CarLow
#define P28_CarLow (*(p28_models_t *)re_gvar(0x010de080u, sizeof(p28_models_t), (void *)&P28_CarLow))
#undef P28_CarDelta
#define P28_CarDelta (*(p28_deltas_t *)re_gvar(0x010de320u, sizeof(p28_deltas_t), (void *)&P28_CarDelta))
#undef P28_CarOpsSize
#define P28_CarOpsSize (*(p28_sizes_t *)re_gvar(0x00e00680u, sizeof(p28_sizes_t), (void *)&P28_CarOpsSize))
#undef P28_CarShine
#define P28_CarShine (*(int32_t *)re_gvar(0x011b6140u, sizeof(int32_t), (void *)&P28_CarShine))
#undef P28_Clear100
#define P28_Clear100 (*(p28_clear100_t *)re_gvar(0x010de120u, sizeof(p28_clear100_t), (void *)&P28_Clear100))
#undef P28_Dst1
#define P28_Dst1 (*(p28_blk1_t *)re_gvar(0x00559074u, sizeof(p28_blk1_t), (void *)&P28_Dst1))
#undef P28_Src1
#define P28_Src1 (*(p28_src1_t *)re_gvar(0x005554d4u, sizeof(p28_src1_t), (void *)&P28_Src1))
#undef P28_Src2
#define P28_Src2 (*(p28_src2_t *)re_gvar(0x00557694u, sizeof(p28_src2_t), (void *)&P28_Src2))
#undef P28_Dst2
#define P28_Dst2 (*(p28_blk2_t *)re_gvar(0x0055a6f4u, sizeof(p28_blk2_t), (void *)&P28_Dst2))
#undef P28_DbgFlag
#define P28_DbgFlag (*(int32_t *)re_gvar(0x00dbb450u, sizeof(int32_t), (void *)&P28_DbgFlag))
#undef P28_ShineFlag
#define P28_ShineFlag (*(int32_t *)re_gvar(0x0055c974u, sizeof(int32_t), (void *)&P28_ShineFlag))
#undef P28_BadGuyFlag
#define P28_BadGuyFlag (*(int32_t *)re_gvar(0x00b87f04u, sizeof(int32_t), (void *)&P28_BadGuyFlag))
#endif
/* gvar-img v2.03 end */
