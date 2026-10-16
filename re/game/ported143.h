#pragma once
#include <stdint.h>
#include "gvar.h"
#include "p143_data.h"
/* v1.88: ported143 — солнце и блик (004b418d), свечение фонаря с размытием по движению (004b73f3). Все cdecl.
   .data спрайтов-вспышек 005536a8..005537c8 (SUN2 005536a8, BLANK 005536c8, CARLIGHT 005536e8 8 × 0x1c) в native — только
   P143_Fx (game/p143_data.h, tools/gen_p143_data.py) в k_regions game/reptr.c; P8_005536ac / P8_005536EC — макросы над ней.
   История экранных позиций фонарей 01105da0 (66 машин × 8 фонарей × 0x28: 4 × {int x, int y}, +0x20 int16 кадр) — P143_LampHist. */
typedef uint32_t p143_fx_t[P143_FX_WORDS];
typedef uint8_t  p143_hist_t[0x42 * 0x140];
typedef uint32_t p143_perf_t[5];
#define P143_Fx       GAME_VAR(p143_fx_t, P143_Fx, 0x005536a8)          /* .data: записи спрайтов-вспышек */
#define P143_FX8(a)   (((uint8_t *)P143_Fx)[(a) - 0x005536a8u])          /* байт таблицы по адресу Game.exe */
#define P143_LampHist GAME_VAR(p143_hist_t, P143_LampHist, 0x01105da0)  /* история позиций фонарей */
#define P143_Perf     GAME_VAR(p143_perf_t, P143_Perf, 0x0111d420)      /* GrSstPerfStats_t (grSstPerfStats): +0x10 pixelsOut */
#ifndef RE_HOOK_BUILD
#pragma push_macro("P143_Fx") /*gvi*/
#undef P143_Fx /*gvi*/
#pragma push_macro("P143_LampHist") /*gvi*/
#undef P143_LampHist /*gvi*/
#pragma push_macro("P143_Perf") /*gvi*/
#undef P143_Perf /*gvi*/
extern p143_fx_t P143_Fx; extern p143_hist_t P143_LampHist; extern p143_perf_t P143_Perf;
#pragma pop_macro("P143_Perf") /*gvi*/
#pragma pop_macro("P143_LampHist") /*gvi*/
#pragma pop_macro("P143_Fx") /*gvi*/
#endif
void P143_SunFlare(void);                 /* 004b418d: солнце (SUN2), проверка видимости (LFB/треугольники + счётчик пикселей), блик BLANK, 8 CARLIGHT, засветка */
void P143_LampGlow(const uint8_t *o);     /* 004b73f3: свечение фонаря объекта o (значок 01123208) и след размытия по истории 01105da0 */
/* gvar-img v2.03 begin (tools/gen_gvar_img.py) */
#if !defined(RE_HOOK_BUILD) && !defined(RE_GVAR_PLAIN)
#undef P143_Fx
#define P143_Fx (*(p143_fx_t *)re_gvar(0x005536a8u, sizeof(p143_fx_t), (void *)&P143_Fx))
#undef P143_LampHist
#define P143_LampHist (*(p143_hist_t *)re_gvar(0x01105da0u, sizeof(p143_hist_t), (void *)&P143_LampHist))
#undef P143_Perf
#define P143_Perf (*(p143_perf_t *)re_gvar(0x0111d420u, sizeof(p143_perf_t), (void *)&P143_Perf))
#endif
/* gvar-img v2.03 end */
