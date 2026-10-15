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
   00427eea  P82_FrustumSetup3D — 6 плоскостей: ближняя 011cff80 (P77_Plane), левая, правая, дальняя, верхняя, нижняя;
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
extern float P82_FovX, P82_FovY, P82_FovXc, P82_FovYc;
extern p82_plane_t P82_PlL, P82_PlR, P82_PlF, P82_PlT, P82_PlB;
extern int32_t P82_Edge, P82_CellCX, P82_CellCY;
extern p82_grid_t P82_LightGrid;
#endif
void    P82_FrustumSetup2D(void);                          /* 00427abe */
void    P82_FrustumSetup3D(void);                          /* 00427eea */
int32_t P82_SphereVis2D(const float *p, float r);          /* 00427d5a */
int32_t P82_SphereVis3D(const float *p, float r);          /* 004283d9 */
void    P82_AddLight(const float *pos, int32_t radius, int32_t cr, int32_t cg, int32_t cb);   /* 004268ef */
