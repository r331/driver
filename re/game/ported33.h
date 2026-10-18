#pragma once
#include "gvar.h"
#include "../platform/plat.h"
#include <stdint.h>
/* Рендер, шаг C: сброс накопленных по слотам текстур списков треугольников (00422ae7) и загрузка таблицы функций Glide (00424c40).
   Обе функции __cdecl без аргументов. */
typedef int32_t P33_CountArr[33];
typedef uint8_t P33_VBufArr[33][0x20000] __attribute__((aligned(16)));
#define P33_Count   GAME_VAR(P33_CountArr, P33_Count, 0x00621bc0)   /* число вершин в буфере слота (слот 32 — без текстуры) */
#define P33_VBuf    GAME_VAR(P33_VBufArr, P33_VBuf, 0x00622048)     /* буферы вершин (32 байта = plat_vertex) по 0x20000 на слот */
#define P33_Device  GAME_VAR(void *, P33_Device, 0x00a42160)
#define P33_GlideOk GAME_VAR(int32_t, P33_GlideOk, 0x00b1c0ec)
#ifndef RE_HOOK_BUILD
#pragma push_macro("P33_Count") /*gvi*/
#undef P33_Count /*gvi*/
#pragma push_macro("P33_GlideOk") /*gvi*/
#undef P33_GlideOk /*gvi*/
extern P33_CountArr P33_Count; extern P33_VBufArr P33_VBuf; extern void *P33_Device; extern int32_t P33_GlideOk;
#pragma pop_macro("P33_GlideOk") /*gvi*/
#pragma pop_macro("P33_Count") /*gvi*/
#endif
int     P33_EnsureRoom(int32_t slot, int32_t vertices); /* reserve a complete primitive, flushing full batches first */
void    P33_FlushBatches(void);   /* 00422ae7: нарисовать и обнулить все непустые буферы слотов, состояние текстуры/COLOROP восстановить */
int32_t P33_LoadGlideProcs(void); /* 00424c40: 119 функций glide2x.dll по именам → указатели игры; возвращает P33_GlideOk != 0 */
void   *P33_GlideProc(int index); /* native: указатель из таблицы по номеру (в hook — читает ячейку Game.exe); NULL вне диапазона */
int     P33_GlideCount(void);     /* 119 */
const char *P33_GlideName(int index);
#ifndef RE_HOOK_BUILD
int     P33_SetNativeProc(const char *name, void *proc); /* native: подставить родную реализацию функции Glide по имени; 0 — имени нет в таблице */
int     P33_SetNativeProcAt(uint32_t addr, void *proc);   /* v1.96: то же по адресу ячейки Game.exe */
#endif
/* gvar-img v2.03 begin (tools/gen_gvar_img.py) */
#if !defined(RE_HOOK_BUILD) && !defined(RE_GVAR_PLAIN)
#undef P33_Count
#define P33_Count (*(P33_CountArr *)re_gvar(0x00621bc0u, sizeof(P33_CountArr), (void *)&P33_Count))
#undef P33_GlideOk
#define P33_GlideOk (*(int32_t *)re_gvar(0x00b1c0ecu, sizeof(int32_t), (void *)&P33_GlideOk))
#endif
/* gvar-img v2.03 end */
