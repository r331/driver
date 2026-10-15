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
extern p28_evtab_t P28_EventModels; extern int32_t P28_EventCount;
extern p28_models_t P28_CarClean, P28_CarDam, P28_CarLow;
extern p28_deltas_t P28_CarDelta; extern p28_sizes_t P28_CarOpsSize; extern int32_t P28_CarShine;
extern p28_clear100_t P28_Clear100; extern p28_blk1_t P28_Dst1; extern p28_src1_t P28_Src1;
extern p28_src2_t P28_Src2; extern p28_blk2_t P28_Dst2; extern int32_t P28_DbgFlag, P28_ShineFlag, P28_BadGuyFlag;
#endif
void P28_LoadEventModels(void *file); /* 004ec58a: модели событий из файла уровня; нехватка памяти -> MessageBox «Memory Error!» */
void P28_LoadCarModels(void);         /* 004bfc30: модели машин (игрок/полиция/бандит/гражданские), дельты вмятин, размеры операций */
