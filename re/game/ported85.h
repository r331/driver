#pragma once
#include "gvar.h"
#include "ported12.h"
#include "ported43.h"
#include "ported44.h"
#include "ported55.h"
#include "ported69.h"
#include "ported79.h"
#include "ported82.h"
#include "ported84.h"
#include "smallfuncs2.h"
#include <stdint.h>
/* Шаг D, ported85 (веха 1, рендер мира): проекция вершины модели и первые обработчики типов записи (плоские треугольник/четырёхугольник).
   Кэш вершин 011cffa0 — записи по 32 байта (индекс вершины модели): [0] метка (= P44_XformTag, «уже спроецирована в этом кадре»),
   [4] oow = P12_00ba53a0[round(z)], [0xc,0x10,0x14] — до проекции x,y,z модели, после — экранные x,y и глубина z, [0x18,0x1c] — x,y в пространстве камеры.
   Растеризатор получает три вершины в формате Glide GrVertex (64 байта, 00b1c290/00b1c2d0/00b1c310): x,y,z,r,g,b,ooz,a,oow,tmu…
   Растеризатор, смена смешивания и общее состояние — указатели на stdcall-функции игры (Glide-обёртки); в native их заменяют P85_Native*.
   00528ac8  P85_Project(v)   — cdecl(запись кэша): ViewMat·(x,y,z)+смещение камеры, oow, экранные x,y (как x87 с 24-битной точностью: сумма с P43_OffX
             держит 1/8 пикселя); возвращает в P85_ZI целое z (fist), в P85_Tmp — промежуточный экранный x.
   0042f7d9  P85_FlatTri(a)   — запись типа 0/32 (32 байта: [8,0xc,0x10] индексы вершин, [0x14..0x1c] цвет r,g,b), a — режим смешивания;
   0042fc29  P85_FlatQuad(a)  — запись типа 1/33 (36 байт: 4 индекса [8..0x14], цвет [0x18..0x20]); два треугольника (v0,v2,v1) и (v0,v2,v3).
   Отсечение при P82_Edge≠0: все вершины слева/сверху за краем (знаковый бит) → пропуск. Курсор записей G2_011F4064 сдвигается на размер записи. */
typedef struct { uint32_t stamp; float oow; uint32_t pad8; float x, y, z, vx, vy; } p85_vtx;
_Static_assert(sizeof(p85_vtx) == 32, "p85_vtx");
typedef struct { float x, y, z, r, g, b, ooz, a, oow; float tmu[7]; } p85_rv;
_Static_assert(sizeof(p85_rv) == 64, "p85_rv");
#ifdef RE_HOOK_BUILD
#  define P85_STD __attribute__((stdcall))
#else
#  define P85_STD
#endif
typedef void (P85_STD *p85_raster_fn)(const p85_rv *a, const p85_rv *b, const p85_rv *c);
typedef void (P85_STD *p85_blend_fn)(int32_t a, int32_t b, int32_t c, int32_t d);
typedef void (P85_STD *p85_state_fn)(int32_t a, int32_t b, int32_t c, int32_t d, int32_t e);
typedef p85_vtx p85_vcache_t[0x2000];
typedef p85_rv p85_rv3_t[3];
#define P85_VCache  GAME_VAR(p85_vcache_t, P85_VCache, 0x011cffa0)
#define P85_RV      GAME_VAR(p85_rv3_t, P85_RV, 0x00b1c290)
#define P85_RasterA GAME_VAR(p85_raster_fn, P85_RasterA, 0x01270e08)     /* без отсечения по краям */
#define P85_RasterB GAME_VAR(p85_raster_fn, P85_RasterB, 0x01270dfc)     /* с отсечением (P82_Edge ≠ 0) */
#define P85_BlendFn GAME_VAR(p85_blend_fn, P85_BlendFn, 0x01270dd0)
#define P85_StateFn GAME_VAR(p85_state_fn, P85_StateFn, 0x01270ea0)
#define P85_StateDirty GAME_VAR(int32_t, P85_StateDirty, 0x01270c34)
#define P85_BlendForce GAME_VAR(int32_t, P85_BlendForce, 0x00b1c38c)
#define P85_BlendCur GAME_VAR(uint8_t, P85_BlendCur, 0x0125f3e4)
#define P85_Clip    GAME_VAR(uint32_t, P85_Clip, 0x01147620)
typedef uint32_t p85_d_t[3];
#define P85_D       GAME_VAR(p85_d_t, P85_D, 0x01159d5c)    /* x−639 / y−479 (поля 5c, 64, 68; 6c — четвёртая вершина) */
#define P85_D3      GAME_VAR(uint32_t, P85_D3, 0x01159d6c)
#define P85_MaxX    GAME_VAR(float, P85_MaxX, 0x00550820)
#define P85_MaxY    GAME_VAR(float, P85_MaxY, 0x00550824)
#define P85_Tmp     GAME_VAR(float, P85_Tmp, 0x0057a10e)
#define P85_ZI      GAME_VAR(int32_t, P85_ZI, 0x0057a132)
#ifndef RE_HOOK_BUILD
extern p85_vcache_t P85_VCache;
extern p85_rv3_t P85_RV;
extern p85_raster_fn P85_RasterA, P85_RasterB;
extern p85_blend_fn P85_BlendFn;
extern p85_state_fn P85_StateFn;
extern int32_t P85_StateDirty, P85_BlendForce;
extern uint8_t P85_BlendCur;
extern uint32_t P85_Clip, P85_D3;
extern p85_d_t P85_D;
extern float P85_MaxX, P85_MaxY, P85_Tmp;
extern int32_t P85_ZI;
/* native: регистрирует в таблицах P84_Handlers обработчики 0/1/32/33 (остальные типы — пропуск записи) и ставит растеризатор на plat_draw_tris */
void P85_RegisterNative(void);
void P85_SkipRecord(uint32_t arg);
extern int32_t P85_Tris;      /* число переданных растеризатору треугольников */
extern int32_t P85_TrisBy[4]; /* то же по режимам смешивания 0..3 (native) */
extern uint8_t P85_LastBlend; /* последний режим смешивания, переданный P85_BlendFn (native) */
#endif
void P85_InitConsts(void);
void P85_Project(p85_vtx *v);          /* 00528ac8 */
void P85_FlatTri(uint32_t arg);        /* 0042f7d9 */
void P85_FlatQuad(uint32_t arg);       /* 0042fc29 */
void P85_LitTri(uint32_t arg);         /* 00432186: типы 16/48 — как P85_FlatTri, но цвет × освещённость плоскости P84_LightIn[запись+4] */
void P85_LitQuad(uint32_t arg);        /* 00432601: типы 17/49 */
p85_vtx *P85_Prep(int32_t idx);                 /* спроецировать вершину модели в кэш (если ещё не в этом кадре) */
void P85_CallState(void);                      /* общее состояние растеризатора «без текстуры» */
void P85_SetBlend(uint8_t m);                  /* смена режима смешивания (с учётом принудительного 00b1c38c) */
void P85_CallRaster(void);                     /* три вершины P85_RV → растеризатор (с отсечением при P82_Edge) */
int  P85_EdgeReject(const p85_vtx *const *vs, int n); /* 1 — все вершины за краем экрана */
void P85_PutVtx(p85_rv *r, const p85_vtx *v);  /* x, y, oow вершины → вершина растеризатора */
