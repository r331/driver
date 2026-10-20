#pragma once
#include "gvar.h"
#include "ported8.h"
#include "ported11.h"
#include "ported43.h"
#include "ported77.h"
#include "ported13.h"
#include "ported14.h"
#include "ported44.h"
#include "ported60.h"
#include "ported76.h"
#include "smallfuncs2.h"
#include <stdint.h>
/* Шаг D, ported82 (веха 1): пирамида видимости камеры и сферы, все cdecl.
   Плоскость — float[4] {nx, ny, nz, d}: расстояние до плоскости = n·p − d (положительно — «внутри» для пары правая/левая/верх/низ).
   00427abe  P82_FrustumSetup2D — 4 плоскости для вида сверху (без верхней/нижней), Y в Xform не задаётся (в оригинале — мусор стека; здесь 0);
   00427eea  P82_FrustumSetup3D — 6 плоскостей: дальняя 011cff80 (P77_Plane, на z = P11_01270c24, нормаль (0,0,+1)), левая, правая,
             ближняя P82_PlF (z = 50, нормаль (0,0,−1) — к камере), верхняя, нижняя (прежняя заметка путала ближнюю и дальнюю — см. ported82.c);
   00427d5a  P82_SphereVis2D(p, r) — 0 вне, 1 частично/внутри; результат+1 как в оригинале (0/1/2), флаг «касается краёв» в P82_Edge;
   004283d9  P82_SphereVis3D(p, r) — то же для 6 плоскостей, P82_Edge = 1 если сфера пересекает боковую/верхнюю/нижнюю плоскость;
   004268ef  P82_AddLight(pos, радиус, r, g, b) — добавляет источник света (запись 0x24 в 011f40e0, максимум 20), если он в пределах сетки и виден. */
typedef float p82_plane_t[4];
typedef uint8_t p82_grid_t[0x2000];
#define P82_FovX   GAME_VAR(float, P82_FovX, 0x00b959ec)
#define P82_FovY   GAME_VAR(float, P82_FovY, 0x00b949ec)
#define P82_FovXc  GAME_VAR(float, P82_FovXc, 0x011f40c0)
#define P82_FovYc  GAME_VAR(float, P82_FovYc, 0x01209644)
#define P82_PlL    GAME_VAR(p82_plane_t, P82_PlL, 0x01209670)
#define P82_PlR    GAME_VAR(p82_plane_t, P82_PlR, 0x01209600)
#define P82_PlF    GAME_VAR(p82_plane_t, P82_PlF, 0x01209630)
#define P82_PlT    GAME_VAR(p82_plane_t, P82_PlT, 0x01209650)
#define P82_PlB    GAME_VAR(p82_plane_t, P82_PlB, 0x0124b6c0)
#define P82_Edge   GAME_VAR(int32_t, P82_Edge, 0x01270c2c)
#define P82_LightGrid GAME_VAR(p82_grid_t, P82_LightGrid, 0x00cf2fa0)
#define P82_CellCX GAME_VAR(int32_t, P82_CellCX, 0x00c97a00)
#define P82_CellCY GAME_VAR(int32_t, P82_CellCY, 0x00c97a04)
#ifndef RE_HOOK_BUILD
#pragma push_macro("P82_FovX") /*gvi*/
#undef P82_FovX /*gvi*/
#pragma push_macro("P82_FovY") /*gvi*/
#undef P82_FovY /*gvi*/
#pragma push_macro("P82_FovXc") /*gvi*/
#undef P82_FovXc /*gvi*/
#pragma push_macro("P82_FovYc") /*gvi*/
#undef P82_FovYc /*gvi*/
extern float P82_FovX, P82_FovY, P82_FovXc, P82_FovYc;
#pragma pop_macro("P82_FovYc") /*gvi*/
#pragma pop_macro("P82_FovXc") /*gvi*/
#pragma pop_macro("P82_FovY") /*gvi*/
#pragma pop_macro("P82_FovX") /*gvi*/
#pragma push_macro("P82_PlL") /*gvi*/
#undef P82_PlL /*gvi*/
#pragma push_macro("P82_PlR") /*gvi*/
#undef P82_PlR /*gvi*/
#pragma push_macro("P82_PlF") /*gvi*/
#undef P82_PlF /*gvi*/
#pragma push_macro("P82_PlT") /*gvi*/
#undef P82_PlT /*gvi*/
#pragma push_macro("P82_PlB") /*gvi*/
#undef P82_PlB /*gvi*/
extern p82_plane_t P82_PlL, P82_PlR, P82_PlF, P82_PlT, P82_PlB;
#pragma pop_macro("P82_PlB") /*gvi*/
#pragma pop_macro("P82_PlT") /*gvi*/
#pragma pop_macro("P82_PlF") /*gvi*/
#pragma pop_macro("P82_PlR") /*gvi*/
#pragma pop_macro("P82_PlL") /*gvi*/
#pragma push_macro("P82_Edge") /*gvi*/
#undef P82_Edge /*gvi*/
#pragma push_macro("P82_CellCX") /*gvi*/
#undef P82_CellCX /*gvi*/
#pragma push_macro("P82_CellCY") /*gvi*/
#undef P82_CellCY /*gvi*/
extern int32_t P82_Edge, P82_CellCX, P82_CellCY;
#pragma pop_macro("P82_CellCY") /*gvi*/
#pragma pop_macro("P82_CellCX") /*gvi*/
#pragma pop_macro("P82_Edge") /*gvi*/
#pragma push_macro("P82_LightGrid") /*gvi*/
#undef P82_LightGrid /*gvi*/
extern p82_grid_t P82_LightGrid;
#pragma pop_macro("P82_LightGrid") /*gvi*/
#endif
void    P82_FrustumSetup2D(void);                          /* 00427abe */
void    P82_FrustumSetup3D(void);                          /* 00427eea */
int32_t P82_SphereVis2D(const float *p, float r);          /* 00427d5a */
int32_t P82_SphereVis3D(const float *p, float r);          /* 004283d9 */
void    P82_AddLight(const float *pos, int32_t radius, int32_t cr, int32_t cg, int32_t cb);   /* 004268ef */
/* gvar-img v2.03 begin (tools/gen_gvar_img.py) */
#if !defined(RE_HOOK_BUILD) && !defined(RE_GVAR_PLAIN)
#undef P82_FovX
#define P82_FovX (*(float *)re_gvar(0x00b959ecu, sizeof(float), (void *)&P82_FovX))
#undef P82_FovY
#define P82_FovY (*(float *)re_gvar(0x00b949ecu, sizeof(float), (void *)&P82_FovY))
#undef P82_FovXc
#define P82_FovXc (*(float *)re_gvar(0x011f40c0u, sizeof(float), (void *)&P82_FovXc))
#undef P82_FovYc
#define P82_FovYc (*(float *)re_gvar(0x01209644u, sizeof(float), (void *)&P82_FovYc))
#undef P82_PlL
#define P82_PlL (*(p82_plane_t *)re_gvar(0x01209670u, sizeof(p82_plane_t), (void *)&P82_PlL))
#undef P82_PlR
#define P82_PlR (*(p82_plane_t *)re_gvar(0x01209600u, sizeof(p82_plane_t), (void *)&P82_PlR))
#undef P82_PlF
#define P82_PlF (*(p82_plane_t *)re_gvar(0x01209630u, sizeof(p82_plane_t), (void *)&P82_PlF))
#undef P82_PlT
#define P82_PlT (*(p82_plane_t *)re_gvar(0x01209650u, sizeof(p82_plane_t), (void *)&P82_PlT))
#undef P82_PlB
#define P82_PlB (*(p82_plane_t *)re_gvar(0x0124b6c0u, sizeof(p82_plane_t), (void *)&P82_PlB))
#undef P82_Edge
#define P82_Edge (*(int32_t *)re_gvar(0x01270c2cu, sizeof(int32_t), (void *)&P82_Edge))
#undef P82_LightGrid
#define P82_LightGrid (*(p82_grid_t *)re_gvar(0x00cf2fa0u, sizeof(p82_grid_t), (void *)&P82_LightGrid))
#undef P82_CellCX
#define P82_CellCX (*(int32_t *)re_gvar(0x00c97a00u, sizeof(int32_t), (void *)&P82_CellCX))
#undef P82_CellCY
#define P82_CellCY (*(int32_t *)re_gvar(0x00c97a04u, sizeof(int32_t), (void *)&P82_CellCY))
#endif
/* gvar-img v2.03 end */
