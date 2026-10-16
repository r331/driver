#pragma once
#include "gvar.h"
#include "../platform/plat.h"
#include <stdint.h>
/* Загрузка/память: чтение кусками, палитры, отчёт об утечках, текстуры вмятин. Все __cdecl. */
#define P27_ReadBytes    GAME_VAR(int32_t, P27_ReadBytes, 0x00d117e8)
#define P27_ReadLimit    GAME_VAR(int32_t, P27_ReadLimit, 0x00d117f0)
#define P27_ProgressOn   GAME_VAR(int32_t, P27_ProgressOn, 0x00b2c3b8)
#define P27_MemAllocated GAME_VAR(int32_t, P27_MemAllocated, 0x00b20380)
#define P27_MemFreed     GAME_VAR(int32_t, P27_MemFreed, 0x00b20398)
typedef uint32_t p27_memtab_t[0x1000 * 3];  /* {адрес, размер, строка журнала} по 12 байт */
#define P27_MemTab       GAME_VAR(p27_memtab_t, P27_MemTab, 0x00b203a0)
typedef int32_t p27_dent_t[66];
#define P27_DentTex      GAME_VAR(p27_dent_t, P27_DentTex, 0x00d17d60)
#ifndef RE_HOOK_BUILD
#pragma push_macro("P27_ReadBytes") /*gvi*/
#undef P27_ReadBytes /*gvi*/
#pragma push_macro("P27_ReadLimit") /*gvi*/
#undef P27_ReadLimit /*gvi*/
#pragma push_macro("P27_ProgressOn") /*gvi*/
#undef P27_ProgressOn /*gvi*/
#pragma push_macro("P27_MemAllocated") /*gvi*/
#undef P27_MemAllocated /*gvi*/
#pragma push_macro("P27_MemFreed") /*gvi*/
#undef P27_MemFreed /*gvi*/
extern int32_t P27_ReadBytes, P27_ReadLimit, P27_ProgressOn, P27_MemAllocated, P27_MemFreed;
#pragma pop_macro("P27_MemFreed") /*gvi*/
#pragma pop_macro("P27_MemAllocated") /*gvi*/
#pragma pop_macro("P27_ProgressOn") /*gvi*/
#pragma pop_macro("P27_ReadLimit") /*gvi*/
#pragma pop_macro("P27_ReadBytes") /*gvi*/
#pragma push_macro("P27_MemTab") /*gvi*/
#undef P27_MemTab /*gvi*/
extern p27_memtab_t P27_MemTab;
#pragma pop_macro("P27_MemTab") /*gvi*/
#pragma push_macro("P27_DentTex") /*gvi*/
#undef P27_DentTex /*gvi*/
extern p27_dent_t P27_DentTex;
#pragma pop_macro("P27_DentTex") /*gvi*/
#endif
int32_t P27_ReadChunked(void *dst, int32_t size, int32_t count, void *file); /* 004d9596: fread кусками по 0xffff, счётчик, прогресс; всегда 1 */
void P27_LoadPalettes(void *file);   /* 004ec154: до 50 палитр (слот,0x400 байт) из файла уровня */
void P27_MemLeakReport(void);        /* 004d8c80: MessageBox «MEMORY FAULT» по каждому неосвобождённому блоку DebugMalloc */
void P27_LoadDentTextures(void);     /* 004c17ae: 11x6 текстур вмятин по имени «%i<код машины>%i», буфер 0x20000 */
/* gvar-img v2.03 begin (tools/gen_gvar_img.py) */
#if !defined(RE_HOOK_BUILD) && !defined(RE_GVAR_PLAIN)
#undef P27_ReadBytes
#define P27_ReadBytes (*(int32_t *)re_gvar(0x00d117e8u, sizeof(int32_t), (void *)&P27_ReadBytes))
#undef P27_ReadLimit
#define P27_ReadLimit (*(int32_t *)re_gvar(0x00d117f0u, sizeof(int32_t), (void *)&P27_ReadLimit))
#undef P27_ProgressOn
#define P27_ProgressOn (*(int32_t *)re_gvar(0x00b2c3b8u, sizeof(int32_t), (void *)&P27_ProgressOn))
#undef P27_MemAllocated
#define P27_MemAllocated (*(int32_t *)re_gvar(0x00b20380u, sizeof(int32_t), (void *)&P27_MemAllocated))
#undef P27_MemFreed
#define P27_MemFreed (*(int32_t *)re_gvar(0x00b20398u, sizeof(int32_t), (void *)&P27_MemFreed))
#undef P27_MemTab
#define P27_MemTab (*(p27_memtab_t *)re_gvar(0x00b203a0u, sizeof(p27_memtab_t), (void *)&P27_MemTab))
#undef P27_DentTex
#define P27_DentTex (*(p27_dent_t *)re_gvar(0x00d17d60u, sizeof(p27_dent_t), (void *)&P27_DentTex))
#endif
/* gvar-img v2.03 end */
