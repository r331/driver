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
#pragma push_macro("P41_TexSel") /*gvi*/
#undef P41_TexSel /*gvi*/
#pragma push_macro("P41_Offset") /*gvi*/
#undef P41_Offset /*gvi*/
#pragma push_macro("P41_Arena") /*gvi*/
#undef P41_Arena /*gvi*/
#pragma push_macro("P41_Flag") /*gvi*/
#undef P41_Flag /*gvi*/
extern p41_texsel_t P41_TexSel; extern int32_t P41_Offset; extern uint32_t P41_Arena; extern int32_t P41_Flag;
#pragma pop_macro("P41_Flag") /*gvi*/
#pragma pop_macro("P41_Arena") /*gvi*/
#pragma pop_macro("P41_Offset") /*gvi*/
#pragma pop_macro("P41_TexSel") /*gvi*/
#pragma push_macro("P41_Buf0") /*gvi*/
#undef P41_Buf0 /*gvi*/
#pragma push_macro("P41_Buf1") /*gvi*/
#undef P41_Buf1 /*gvi*/
extern p41_buf0_t P41_Buf0; extern p41_buf1_t P41_Buf1;
#pragma pop_macro("P41_Buf1") /*gvi*/
#pragma pop_macro("P41_Buf0") /*gvi*/
#endif
void P41_LoadTexPages(void *file); /* 004eb975: палитры, затем два прохода по страницам текстур (0x20000 или пара 0x10000) */
uint8_t *P41_RamPtr(void); /* полный указатель на буфер страниц (native: P41_Arena его не вмещает) */
/* gvar-img v2.03 begin (tools/gen_gvar_img.py) */
#if !defined(RE_HOOK_BUILD) && !defined(RE_GVAR_PLAIN)
#undef P41_TexSel
#define P41_TexSel (*(p41_texsel_t *)re_gvar(0x00562d80u, sizeof(p41_texsel_t), (void *)&P41_TexSel))
#undef P41_Offset
#define P41_Offset (*(int32_t *)re_gvar(0x00b31ee0u, sizeof(int32_t), (void *)&P41_Offset))
#undef P41_Arena
#define P41_Arena (*(uint32_t *)re_gvar(0x00d01260u, sizeof(uint32_t), (void *)&P41_Arena))
#undef P41_Flag
#define P41_Flag (*(int32_t *)re_gvar(0x00c82530u, sizeof(int32_t), (void *)&P41_Flag))
#undef P41_Buf0
#define P41_Buf0 (*(p41_buf0_t *)re_gvar(0x00c98f00u, sizeof(p41_buf0_t), (void *)&P41_Buf0))
#undef P41_Buf1
#define P41_Buf1 (*(p41_buf1_t *)re_gvar(0x00ce1f60u, sizeof(p41_buf1_t), (void *)&P41_Buf1))
#endif
/* gvar-img v2.03 end */
