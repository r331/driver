/* v1.63, ported118 — восстановлено из Game.exe. Все функции cdecl (ret без операнда; work/rets.py).
   0041a1f9 — маршрут камеры меню: из камеры G005FEB00 в камеру p по ключам P99_CamKeys (запись 0x34: +0 xyzw, +0x10 кватернион,
             +0x24 масштаб, +0x2c кадр); таблица .data 0054e774 (P118_RouteTab, game/p118_data.h): 17 пар соседних камер,
             +0x24 + 3p — флаг прямого перехода, первый и последний ключ камеры p; результат — ключи в P118_Route 005feb90
             (P12_005febbc = +0x2c), число ключей UiVar005FEB48; шагает 0041a8cd (P12_Fn0041A8CD → P98_CamSpline);
   004932d5 — выбор поворота машины трафика на перекрёстке (слот P101_RdNode, соседи +0xa+8i, полосы P59_C39DC0), 0/1;
   0048dddb — проверка «впереди машина/препятствие» для записи трафика (прямоугольник по курсу — P96_RotTab, иначе полосы по синусам);
   004b8f4e — пыль/искры/дым следа: запись 0x78 P95_ObjA из пула 004ac6d0 (тип 1/2/иное). */
#pragma once
#include <stdint.h>
#include "gvar.h"
typedef uint8_t p118_routetab_t[0x58];
typedef uint8_t p118_route_t[0x830];   /* 005feb90..005ff3c0: ключи маршрута по 0x34 (покрывает прежний P12_005febbc 0x800 от +0x2c) */
#define P118_RouteTab  GAME_VAR(p118_routetab_t, P118_RouteTab, 0x0054e774)  /* .data: пары камер, по 3 байта на камеру с +0x24 */
#define P118_Route     GAME_VAR(p118_route_t, P118_Route, 0x005feb90)        /* ключи маршрута 0x34; 005febc4/005febf8/005fec2c/005fec60 — ключи 1..4 */
#define P118_RouteTo   GAME_VAR(int32_t, P118_RouteTo, 0x005feae0)           /* камера назначения */
#define P118_RouteKey  GAME_VAR(int32_t, P118_RouteKey, 0x005feae4)          /* последний ключ при прямом переходе */
#define P118_RouteMax  GAME_VAR(int32_t, P118_RouteMax, 0x005feae8)          /* число ключей кольца камер (0x19/10/0xf) */
#ifndef RE_HOOK_BUILD
#pragma push_macro("P118_RouteTab") /*gvi*/
#undef P118_RouteTab /*gvi*/
#pragma push_macro("P118_Route") /*gvi*/
#undef P118_Route /*gvi*/
#pragma push_macro("P118_RouteTo") /*gvi*/
#undef P118_RouteTo /*gvi*/
#pragma push_macro("P118_RouteKey") /*gvi*/
#undef P118_RouteKey /*gvi*/
#pragma push_macro("P118_RouteMax") /*gvi*/
#undef P118_RouteMax /*gvi*/
extern p118_routetab_t P118_RouteTab; extern p118_route_t P118_Route; extern int32_t P118_RouteTo, P118_RouteKey, P118_RouteMax;
#pragma pop_macro("P118_RouteMax") /*gvi*/
#pragma pop_macro("P118_RouteKey") /*gvi*/
#pragma pop_macro("P118_RouteTo") /*gvi*/
#pragma pop_macro("P118_Route") /*gvi*/
#pragma pop_macro("P118_RouteTab") /*gvi*/
#endif
void    P118_CamRoute(uint32_t cam);                                   /* 0041a1f9 */
int32_t P118_TrafficTurn(uint8_t *rec);                                /* 004932d5 */
int32_t P118_TrafficBlocked(uint8_t *rec);                             /* 0048dddb */
void    P118_SkidFx(const float *pos, int32_t a, int32_t b, int32_t type, int32_t dist, const float *vel, int32_t spark); /* 004b8f4e */
/* gvar-img v2.03 begin (tools/gen_gvar_img.py) */
#if !defined(RE_HOOK_BUILD) && !defined(RE_GVAR_PLAIN)
#undef P118_RouteTab
#define P118_RouteTab (*(p118_routetab_t *)re_gvar(0x0054e774u, sizeof(p118_routetab_t), (void *)&P118_RouteTab))
#undef P118_Route
#define P118_Route (*(p118_route_t *)re_gvar(0x005feb90u, sizeof(p118_route_t), (void *)&P118_Route))
#undef P118_RouteTo
#define P118_RouteTo (*(int32_t *)re_gvar(0x005feae0u, sizeof(int32_t), (void *)&P118_RouteTo))
#undef P118_RouteKey
#define P118_RouteKey (*(int32_t *)re_gvar(0x005feae4u, sizeof(int32_t), (void *)&P118_RouteKey))
#undef P118_RouteMax
#define P118_RouteMax (*(int32_t *)re_gvar(0x005feae8u, sizeof(int32_t), (void *)&P118_RouteMax))
#endif
/* gvar-img v2.03 end */
