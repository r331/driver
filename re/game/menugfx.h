/* v1.49: .data экрана графики 0054a170..0054a6f8 (0x588, вместе со строками SLIDER/SLIDEBOX) в native — один массив P104_MenuGfx (game/p104_data.h,
   tools/gen_p104_data.py), зарегистрированный в k_regions game/reptr.c; имена внутри (D_0054a254.., MenuB0054A254..,
   G6_0054A25C, P55_A680..A690, MenuI0054A694) — макросы MENUGFX_VAR без отдельных native-переменных. В hook — ячейки Game.exe. */
#pragma once
#include <stdint.h>
#define P104_MENUGFX_ADDR0 0x0054a170u
#define P104_MENUGFX_SIZE0 0x588
#ifdef RE_HOOK_BUILD
#  define MENUGFX_VAR(type, name, addr) (*(type *)(uintptr_t)(addr))
#else
typedef union { uint8_t b[P104_MENUGFX_SIZE0]; uint32_t u[P104_MENUGFX_SIZE0 / 4]; } p104_menugfx_t;
extern p104_menugfx_t P104_MenuGfx;
#  define MENUGFX_VAR(type, name, addr) (*(type *)(P104_MenuGfx.b + ((uint32_t)(addr) - P104_MENUGFX_ADDR0)))
#endif
