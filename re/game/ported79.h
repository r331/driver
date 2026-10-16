#pragma once
#include "gvar.h"
#include "unported.h"
#include "crt.h"
#include "engine.h"
#include "ported4.h"
#include "smallfuncs2.h"
#include <stdint.h>
/* Шаг D, ported79 (все cdecl): модели блока карты (32-байтные заголовки, 0x38 байт на модель).
   Модель в памяти — заголовок + массивы; в полях +0x1c/0x20/0x24/0x28/0x2c/0x30/0x34 лежат «ссылки» на массивы.
   В оригинале это 32-битные абсолютные адреса. Модель «ссылка» в native: смещение от начала арены карты D_00c98ed0
   (P79_OFF/P79_PTR), в hook-сборке — сам адрес (база 0). Таблица моделей 00cfe7a0 хранит такие же ссылки на модели.
   - 00427757/004275ae — перевод ссылок модели в абсолютные (+ адрес модели) и обратно; 0042754a — список записей;
   - 0042793f — радиус модели (режим 0 — с осью Y, 1 — без); 0047560b — класс вершины (оси ±1); 004757d2 — разметка записей;
   - 00475906 — поиск совпадающих вершин; 00475a3d — преобразование модели с диска в формат памяти (возвращает размер). */
#ifdef RE_HOOK_BUILD
#  define P79_MBASE ((uintptr_t)0)
#else
#  define P79_MBASE ((uintptr_t)D_00c98ed0)
#endif
#define P79_OFF(p) ((uint32_t)((uintptr_t)(p) - P79_MBASE))
#define P79_PTR(v) ((void *)(P79_MBASE + (uintptr_t)(uint32_t)(v)))
typedef uint32_t p79_tab_t[1126];
#define P79_ModelTab GAME_VAR(p79_tab_t, P79_ModelTab, 0x00cfe7a0)
#define P79_Total    GAME_VAR(int32_t, P79_Total, 0x01159d60)
#define P79_Outside  GAME_VAR(int32_t, P79_Outside, 0x0115a074)
#define P79_SumTotal GAME_VAR(int32_t, P79_SumTotal, 0x00b1c390)
#define P79_SumOut   GAME_VAR(int32_t, P79_SumOut, 0x00b1c394)
#define P79_NumAll   GAME_VAR(int32_t, P79_NumAll, 0x00b1c398)
#define P79_NumMixed GAME_VAR(int32_t, P79_NumMixed, 0x00b1c39c)
#define P79_NumNone  GAME_VAR(int32_t, P79_NumNone, 0x00b1c3a0)
#define P79_ClsHi    GAME_VAR(float, P79_ClsHi, 0x005460a0)
#define P79_ClsLo    GAME_VAR(float, P79_ClsLo, 0x005460a4)
#ifndef RE_HOOK_BUILD
#pragma push_macro("P79_ModelTab") /*gvi*/
#undef P79_ModelTab /*gvi*/
extern p79_tab_t P79_ModelTab;
#pragma pop_macro("P79_ModelTab") /*gvi*/
#pragma push_macro("P79_Total") /*gvi*/
#undef P79_Total /*gvi*/
#pragma push_macro("P79_Outside") /*gvi*/
#undef P79_Outside /*gvi*/
#pragma push_macro("P79_SumTotal") /*gvi*/
#undef P79_SumTotal /*gvi*/
#pragma push_macro("P79_SumOut") /*gvi*/
#undef P79_SumOut /*gvi*/
#pragma push_macro("P79_NumAll") /*gvi*/
#undef P79_NumAll /*gvi*/
#pragma push_macro("P79_NumMixed") /*gvi*/
#undef P79_NumMixed /*gvi*/
#pragma push_macro("P79_NumNone") /*gvi*/
#undef P79_NumNone /*gvi*/
extern int32_t P79_Total, P79_Outside, P79_SumTotal, P79_SumOut, P79_NumAll, P79_NumMixed, P79_NumNone;
#pragma pop_macro("P79_NumNone") /*gvi*/
#pragma pop_macro("P79_NumMixed") /*gvi*/
#pragma pop_macro("P79_NumAll") /*gvi*/
#pragma pop_macro("P79_SumOut") /*gvi*/
#pragma pop_macro("P79_SumTotal") /*gvi*/
#pragma pop_macro("P79_Outside") /*gvi*/
#pragma pop_macro("P79_Total") /*gvi*/
#pragma push_macro("P79_ClsHi") /*gvi*/
#undef P79_ClsHi /*gvi*/
#pragma push_macro("P79_ClsLo") /*gvi*/
#undef P79_ClsLo /*gvi*/
extern float P79_ClsHi, P79_ClsLo;
#pragma pop_macro("P79_ClsLo") /*gvi*/
#pragma pop_macro("P79_ClsHi") /*gvi*/
#endif
void    P79_InitConsts(void);
void    P79_PoolReset(void);                          /* native: пул моделей событий — 1 МБ после 4 МБ арены карты */
void   *P79_EventAlloc(int32_t size);                 /* hook: DebugMalloc; native: кусок пула (ссылки должны быть смещениями арены) */
void    P79_EventFree(void *p);                       /* hook: DebugFree; native: ничего (пул сбрасывается при новой арене) */
void    P79_ModelList(void *m, uint32_t *out);        /* 0042754a */
void    P79_Relocate(void *m);                        /* 00427757 */
void    P79_Unrelocate(void *m);                      /* 004275ae */
void    P79_Radius(void *m, int32_t mode);            /* 0042793f */
int32_t P79_VertClass(const float *v);                /* 0047560b */
void    P79_MarkRecords(void *m);                     /* 004757d2 */
int32_t P79_FindSameVerts(void *m);                   /* 00475906 */
int32_t P79_Convert(void *src, void *dst);            /* 00475a3d */
/* gvar-img v2.03 begin (tools/gen_gvar_img.py) */
#if !defined(RE_HOOK_BUILD) && !defined(RE_GVAR_PLAIN)
#undef P79_ModelTab
#define P79_ModelTab (*(p79_tab_t *)re_gvar(0x00cfe7a0u, sizeof(p79_tab_t), (void *)&P79_ModelTab))
#undef P79_Total
#define P79_Total (*(int32_t *)re_gvar(0x01159d60u, sizeof(int32_t), (void *)&P79_Total))
#undef P79_Outside
#define P79_Outside (*(int32_t *)re_gvar(0x0115a074u, sizeof(int32_t), (void *)&P79_Outside))
#undef P79_SumTotal
#define P79_SumTotal (*(int32_t *)re_gvar(0x00b1c390u, sizeof(int32_t), (void *)&P79_SumTotal))
#undef P79_SumOut
#define P79_SumOut (*(int32_t *)re_gvar(0x00b1c394u, sizeof(int32_t), (void *)&P79_SumOut))
#undef P79_NumAll
#define P79_NumAll (*(int32_t *)re_gvar(0x00b1c398u, sizeof(int32_t), (void *)&P79_NumAll))
#undef P79_NumMixed
#define P79_NumMixed (*(int32_t *)re_gvar(0x00b1c39cu, sizeof(int32_t), (void *)&P79_NumMixed))
#undef P79_NumNone
#define P79_NumNone (*(int32_t *)re_gvar(0x00b1c3a0u, sizeof(int32_t), (void *)&P79_NumNone))
#undef P79_ClsHi
#define P79_ClsHi (*(float *)re_gvar(0x005460a0u, sizeof(float), (void *)&P79_ClsHi))
#undef P79_ClsLo
#define P79_ClsLo (*(float *)re_gvar(0x005460a4u, sizeof(float), (void *)&P79_ClsLo))
#endif
/* gvar-img v2.03 end */
