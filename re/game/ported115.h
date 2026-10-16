/* v1.60, ported115 — восстановлено из Game.exe. Все функции cdecl (ret без операнда; work/rets.py).
   00418e70 / 00510e1d / 0051084d — значок (страница P12_01145a60, uv из записи значка: [8] страница, [9],[10] u,v, [0xb],[0xc] размер)
             четырёхугольником grDrawPolygonVertexList (01270e78, по имени из P33); смешивание 0..3 (режим 3 — 4,4,0,0);
   0048d4e0 — отладочная стрелка стороны дороги (P102_RoadSide) у точки: пурпурный треугольник через P85_RasterB;
   00452327 / 00452d3e / 004527ac / 004531c5 — записи модели: плоский/градиентный треугольник и четырёхугольник через растеризатор
             01270e30 (без отсечения) / 01270d9c (P82_Edge ≠ 0) — указатели D3D-растеризатора, в native не установлены (пропуск вызова);
   0040b286 — значок (u,v,размер в текселях) с режимом смешивания по флагам 005d77c0 (4/8/0x10), без 3D — спрайт в буфер;
   00523829 — такт звука: фейд мастер-громкости, слушатель (матрица вида, позиция и скорость камеры), 20 голосов (позиция по
             указателю +0x1c, громкость/частота/запуск по флагам);
   004a3808 — такт объекта-цели (таймер +0x30, мигание, «достигнут» при расстоянии² < +0x1c до игрока);
   004e5b78 — HUD «бумаги» ELPAPEL: значок, отметки P59_Flags9, кресты/значки CROSS по числу P98_M4660. */
#pragma once
#include <stdint.h>
#include "gvar.h"
#include "ported85.h"
#define P115_RasterC GAME_VAR(p85_raster_fn, P115_RasterC, 0x01270e30)   /* D3D: без отсечения */
#define P115_RasterD GAME_VAR(p85_raster_fn, P115_RasterD, 0x01270d9c)   /* D3D: с отсечением (P82_Edge ≠ 0) */
#define P115_TgtOn   GAME_VAR(int32_t, P115_TgtOn, 0x00c80cf0)           /* цель активна (флаг 0x200 объекта) */
typedef int32_t p115_i4_t[4];
#define P115_Tgt     GAME_VAR(p115_i4_t, P115_Tgt, 0x00c80cf4)           /* копия +0x20..+0x2c объекта-цели */
#ifndef RE_HOOK_BUILD
#pragma push_macro("P115_TgtOn") /*gvi*/
#undef P115_TgtOn /*gvi*/
#pragma push_macro("P115_Tgt") /*gvi*/
#undef P115_Tgt /*gvi*/
extern p85_raster_fn P115_RasterC, P115_RasterD; extern int32_t P115_TgtOn; extern p115_i4_t P115_Tgt;
#pragma pop_macro("P115_Tgt") /*gvi*/
#pragma pop_macro("P115_TgtOn") /*gvi*/
#endif
void P115_IconAt(float x, float y, uint32_t icon, int32_t r, int32_t g, int32_t b, int32_t flip, int32_t mode);      /* 00418e70 */
void P115_IconScaled(float x, float y, float sx, float sy, uint32_t icon, int32_t r, int32_t g, int32_t b, int32_t mode); /* 00510e1d */
void P115_IconFlip(float x, float y, uint32_t icon, int32_t r, int32_t g, int32_t b, int32_t flip, int32_t mode);    /* 0051084d */
void P115_RoadArrow(const float *pos);        /* 0048d4e0 */
void P115_FlatTriC(uint32_t arg);             /* 00452327: запись 0x20 */
void P115_GouraudTriC(uint32_t arg);          /* 00452d3e: запись 0x38 */
void P115_FlatQuadC(uint32_t arg);            /* 004527ac: запись 0x24 */
void P115_GouraudQuadC(uint32_t arg);         /* 004531c5: запись 0x48 */
void P115_IconDraw(float x, float y, float sx, float sy, float u, float v, float tw, float th, int32_t page, const uint8_t *rgb); /* 0040b286 */
void P115_SndUpdate(void);                    /* 00523829 */
void P115_TargetTick(uint8_t *o);             /* 004a3808 */
void P115_PaperHud(void);                     /* 004e5b78 */
/* gvar-img v2.03 begin (tools/gen_gvar_img.py) */
#if !defined(RE_HOOK_BUILD) && !defined(RE_GVAR_PLAIN)
#undef P115_TgtOn
#define P115_TgtOn (*(int32_t *)re_gvar(0x00c80cf0u, sizeof(int32_t), (void *)&P115_TgtOn))
#undef P115_Tgt
#define P115_Tgt (*(p115_i4_t *)re_gvar(0x00c80cf4u, sizeof(p115_i4_t), (void *)&P115_Tgt))
#endif
/* gvar-img v2.03 end */
