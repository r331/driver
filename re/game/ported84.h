#pragma once
#include "gvar.h"
#include "ported19.h"
#include "ported44.h"
#include "ported47.h"
#include "ported56.h"
#include "ported59.h"
#include "ported63.h"
#include "ported79.h"
#include "smallfuncs2.h"
#include <stdint.h>
/* Шаг D, ported84 (веха 1, рендер мира): рисование модели блока карты — обход записей модели с отсечением по плоскостям и освещением.
   Обе cdecl(модель, матрица или номер, позиция, режим):
   00428b69  P84_DrawModel(m, mat, pos, mode) — матрица модели mat — float[9] (или, если в модели флаг 0x4000, берётся из таблицы поворотов
             EulerTab по углу −P59_AngB & 0xfff);
   00429143  P84_DrawModelIdx(m, idx, pos, mode) — то же, но матрица — запись idx таблицы EulerTab (по 0x40 байт); произведение ViewMat×M
             кэшируется в P84_MatCache[idx], пока флаг P84_MatFlag[idx] равен P47_SwapCnt.
   m — «ссылка» (в native — смещение от арены карты, P79_PTR). Заголовок модели: +2 u16 флаги (1 — свет, 0x4000 — угол из P59_AngB),
   +0x16 u16 число записей, +0x18 u16 число нормалей, +0x20 ссылка на вершины, +0x24 плоскости (float[4]: n, d), +0x28 нормали (float[4]),
   +0x2c записи: [0] тип, [1] флаги (8 — есть плоскость), [4] i32 номер плоскости; шаг записи — G2_TABLE_00550ACC[тип].
   Запись зовёт обработчик типа: таблица из трёх (режим 0/1/другой: P84_Tab0/1/2) по 56 указателей, аргумент — байт P84_Arg[тип].
   Видимость плоскости (n·(−поза) − d < 0 → лицом) кэшируется в P84_Vis[номер]; освещение плоскости (P84_LightIn) считается, если P84_Lit[тип].
   В native обработчики регистрирует P84_Handlers (пустые не вызываются); в hook таблицы — из образа Game.exe. */
typedef void (*p84_handler_t)(uint32_t arg);
typedef float p84_m16_t[16];
#define P84_Mirror   GAME_VAR(uint8_t, P84_Mirror, 0x00bdc288)            /* зеркальный режим: ось X отражается */
#define P84_Tab0     GAME_VAR(const uintptr_t *, P84_Tab0, 0x011effe0)    /* таблица обработчиков режима 0 */
#define P84_Tab1     GAME_VAR(const uintptr_t *, P84_Tab1, 0x01209660)    /* режим 1 */
#define P84_Tab2     GAME_VAR(const uintptr_t *, P84_Tab2, 0x011f4060)    /* остальные режимы */
#define P84_VertRef  GAME_VAR(uint32_t, P84_VertRef, 0x01209614)          /* ссылка на вершины текущей модели */
#define P84_Planes   GAME_VAR(float *, P84_Planes, 0x012085f0)            /* плоскости текущей модели */
typedef float p84_light_t[4096];
typedef uint8_t p84_vis_t[4096];
typedef float p84_nlight_t[8192];
typedef p84_m16_t p84_mats_t[4096];
typedef int32_t p84_flags_t[4096];
typedef uint8_t p84_b56_t[56];
#define P84_LightIn  GAME_VAR(p84_light_t, P84_LightIn, 0x012043c0)       /* освещённость плоскостей */
#define P84_Vis      GAME_VAR(p84_vis_t, P84_Vis, 0x01208600)             /* плоскость обращена к камере */
#define P84_NormLight GAME_VAR(p84_nlight_t, P84_NormLight, 0x012496c0)   /* освещённость нормалей */
#define P84_MatCache GAME_VAR(p84_mats_t, P84_MatCache, 0x01209680)       /* ViewMat × EulerTab[i]; 1024·k — матрицы света P83 */
#define P84_MatFlag  GAME_VAR(p84_flags_t, P84_MatFlag, 0x011f0060)
#define P84_Arg      GAME_VAR(p84_b56_t, P84_Arg, 0x00550cc4)             /* аргумент обработчика по типу записи */
#define P84_Lit      GAME_VAR(p84_b56_t, P84_Lit, 0x00550c8c)             /* нужно ли считать освещение плоскости */
#ifndef RE_HOOK_BUILD
#pragma push_macro("P84_Mirror") /*gvi*/
#undef P84_Mirror /*gvi*/
extern uint8_t P84_Mirror;
#pragma pop_macro("P84_Mirror") /*gvi*/
extern const uintptr_t *P84_Tab0, *P84_Tab1, *P84_Tab2;
#pragma push_macro("P84_VertRef") /*gvi*/
#undef P84_VertRef /*gvi*/
extern uint32_t P84_VertRef;
#pragma pop_macro("P84_VertRef") /*gvi*/
extern float *P84_Planes;
#pragma push_macro("P84_LightIn") /*gvi*/
#undef P84_LightIn /*gvi*/
extern p84_light_t P84_LightIn;
#pragma pop_macro("P84_LightIn") /*gvi*/
#pragma push_macro("P84_Vis") /*gvi*/
#undef P84_Vis /*gvi*/
extern p84_vis_t P84_Vis;
#pragma pop_macro("P84_Vis") /*gvi*/
#pragma push_macro("P84_NormLight") /*gvi*/
#undef P84_NormLight /*gvi*/
extern p84_nlight_t P84_NormLight;
#pragma pop_macro("P84_NormLight") /*gvi*/
#pragma push_macro("P84_MatCache") /*gvi*/
#undef P84_MatCache /*gvi*/
extern p84_mats_t P84_MatCache;
#pragma pop_macro("P84_MatCache") /*gvi*/
#pragma push_macro("P84_MatFlag") /*gvi*/
#undef P84_MatFlag /*gvi*/
extern p84_flags_t P84_MatFlag;
#pragma pop_macro("P84_MatFlag") /*gvi*/
#pragma push_macro("P84_Arg") /*gvi*/
#undef P84_Arg /*gvi*/
#pragma push_macro("P84_Lit") /*gvi*/
#undef P84_Lit /*gvi*/
extern p84_b56_t P84_Arg, P84_Lit;
#pragma pop_macro("P84_Lit") /*gvi*/
#pragma pop_macro("P84_Arg") /*gvi*/
/* native: 6 таблиц обработчиков [набор*3 + режим][56], набор 0 — 0055082c.., набор 1 — 00550cfc.. */
extern uintptr_t P84_Handlers[6][56];
void P84_SelectTables(int32_t alt);                 /* как в инициализации рендера: P55_BDFA18 == 0 → набор 0, иначе 1 */
#endif
void P84_InitConsts(void);
void P84_DrawModel(uint32_t m, const float *mat, const float *pos, int32_t mode);          /* 00428b69 */
void P84_DrawModelIdx(uint32_t m, int32_t idx, const float *pos, int32_t mode);            /* 00429143 */
/* v1.81: варианты 00428b69. */
void P84_DrawModelC(uint32_t m, const float *mat, const float *pos, int32_t mode);         /* 0042b7cb: аргумент обработчика 2/3, свет плоскости 0.01 */
void P84_DrawCar(uint32_t m, const float *mat, const float *pos, int32_t mode, int32_t car, int32_t shine, int32_t a7, float shk); /* 0042a9f1 */
#define P84_TexFiltOn GAME_VAR(int32_t, P84_TexFiltOn, 0x01252bc0)   /* v1.81: кэш grTexFilterMode(0,1,1) */
#define P84_ShineK    GAME_VAR(float, P84_ShineK, 0x01159d58)        /* v1.81: сила блика (param_8·50 / 100) */
typedef uint8_t p84_uv_t[0x200];
#define P84_ShineUV   GAME_VAR(p84_uv_t, P84_ShineUV, 0x01159d80)    /* v1.81: UV блика по нормалям (u8 пары, до 256) */
#ifndef RE_HOOK_BUILD
#pragma push_macro("P84_TexFiltOn") /*gvi*/
#undef P84_TexFiltOn /*gvi*/
#pragma push_macro("P84_ShineK") /*gvi*/
#undef P84_ShineK /*gvi*/
#pragma push_macro("P84_ShineUV") /*gvi*/
#undef P84_ShineUV /*gvi*/
extern int32_t P84_TexFiltOn; extern float P84_ShineK; extern p84_uv_t P84_ShineUV;
#pragma pop_macro("P84_ShineUV") /*gvi*/
#pragma pop_macro("P84_ShineK") /*gvi*/
#pragma pop_macro("P84_TexFiltOn") /*gvi*/
#endif
/* gvar-img v2.03 begin (tools/gen_gvar_img.py) */
#if !defined(RE_HOOK_BUILD) && !defined(RE_GVAR_PLAIN)
#undef P84_Mirror
#define P84_Mirror (*(uint8_t *)re_gvar(0x00bdc288u, sizeof(uint8_t), (void *)&P84_Mirror))
#undef P84_VertRef
#define P84_VertRef (*(uint32_t *)re_gvar(0x01209614u, sizeof(uint32_t), (void *)&P84_VertRef))
#undef P84_LightIn
#define P84_LightIn (*(p84_light_t *)re_gvar(0x012043c0u, sizeof(p84_light_t), (void *)&P84_LightIn))
#undef P84_Vis
#define P84_Vis (*(p84_vis_t *)re_gvar(0x01208600u, sizeof(p84_vis_t), (void *)&P84_Vis))
#undef P84_NormLight
#define P84_NormLight (*(p84_nlight_t *)re_gvar(0x012496c0u, sizeof(p84_nlight_t), (void *)&P84_NormLight))
#undef P84_MatCache
#define P84_MatCache (*(p84_mats_t *)re_gvar(0x01209680u, sizeof(p84_mats_t), (void *)&P84_MatCache))
#undef P84_MatFlag
#define P84_MatFlag (*(p84_flags_t *)re_gvar(0x011f0060u, sizeof(p84_flags_t), (void *)&P84_MatFlag))
#undef P84_Arg
#define P84_Arg (*(p84_b56_t *)re_gvar(0x00550cc4u, sizeof(p84_b56_t), (void *)&P84_Arg))
#undef P84_Lit
#define P84_Lit (*(p84_b56_t *)re_gvar(0x00550c8cu, sizeof(p84_b56_t), (void *)&P84_Lit))
#undef P84_TexFiltOn
#define P84_TexFiltOn (*(int32_t *)re_gvar(0x01252bc0u, sizeof(int32_t), (void *)&P84_TexFiltOn))
#undef P84_ShineK
#define P84_ShineK (*(float *)re_gvar(0x01159d58u, sizeof(float), (void *)&P84_ShineK))
#undef P84_ShineUV
#define P84_ShineUV (*(p84_uv_t *)re_gvar(0x01159d80u, sizeof(p84_uv_t), (void *)&P84_ShineUV))
#endif
/* gvar-img v2.03 end */
