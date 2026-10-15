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
extern int32_t P27_ReadBytes, P27_ReadLimit, P27_ProgressOn, P27_MemAllocated, P27_MemFreed;
extern p27_memtab_t P27_MemTab;
extern p27_dent_t P27_DentTex;
#endif
int32_t P27_ReadChunked(void *dst, int32_t size, int32_t count, void *file); /* 004d9596: fread кусками по 0xffff, счётчик, прогресс; всегда 1 */
void P27_LoadPalettes(void *file);   /* 004ec154: до 50 палитр (слот,0x400 байт) из файла уровня */
void P27_MemLeakReport(void);        /* 004d8c80: MessageBox «MEMORY FAULT» по каждому неосвобождённому блоку DebugMalloc */
void P27_LoadDentTextures(void);     /* 004c17ae: 11x6 текстур вмятин по имени «%i<код машины>%i», буфер 0x20000 */
