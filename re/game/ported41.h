#pragma once
#include "gvar.h"
#include "ported40.h"
#include <stdint.h>
/* Загрузка текстурных страниц карты из файла уровня (map.c). __cdecl. Убрана из unported: 004eb975. */
typedef int32_t p41_texsel_t[8];
#define P41_TexSel   GAME_VAR(p41_texsel_t, P41_TexSel, 0x00562d80)  /* номер слота текстуры «по умолчанию» для города (индекс — 00b87e30) */
#define P41_Offset   GAME_VAR(int32_t, P41_Offset, 0x00b31ee0)      /* заполненный объём буфера страниц в RAM */
#define P41_Arena    GAME_VAR(uint32_t, P41_Arena, 0x00d01260)      /* буфер страниц в RAM */
#define P41_Flag     GAME_VAR(int32_t, P41_Flag, 0x00c82530)
typedef uint8_t p41_buf0_t[0x20000];
typedef uint8_t p41_buf1_t[0x10000];
#define P41_Buf0     GAME_VAR(p41_buf0_t, P41_Buf0, 0x00c98f00)
#define P41_Buf1     GAME_VAR(p41_buf1_t, P41_Buf1, 0x00ce1f60)
#ifndef RE_HOOK_BUILD
extern p41_texsel_t P41_TexSel; extern int32_t P41_Offset; extern uint32_t P41_Arena; extern int32_t P41_Flag;
extern p41_buf0_t P41_Buf0; extern p41_buf1_t P41_Buf1;
#endif
void P41_LoadTexPages(void *file); /* 004eb975: палитры, затем два прохода по страницам текстур (0x20000 или пара 0x10000) */
