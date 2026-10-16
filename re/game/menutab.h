/* v1.48: .data экрана настроек 0054db58..0054de94 (0x33c) в native — один массив P103_MenuDB58 (game/p100_data.h,
   tools/gen_p100_data.py), зарегистрированный в k_regions game/reptr.c; имена внутри (D_0054dbc4, MenuB0054DBC4,
   G6_0054DBCC, MenuI0054DE08 и новые) — макросы MENUTAB_VAR без отдельных native-переменных. В hook — ячейки Game.exe. */
#pragma once
#include <stdint.h>
#define P103_MENUDB58_ADDR 0x0054db58u
#define P103_MENUDB58_SIZE 0x33c
#ifdef RE_HOOK_BUILD
#  define MENUTAB_VAR(type, name, addr) (*(type *)(uintptr_t)(addr))
#else
typedef union { uint8_t b[P103_MENUDB58_SIZE]; uint32_t u[P103_MENUDB58_SIZE / 4]; } p103_menutab_t;
extern p103_menutab_t P103_MenuTab;
#  define P103_MenuDB58 (P103_MenuTab.b)
#  define MENUTAB_VAR(type, name, addr) (*(type *)(P103_MenuTab.b + ((uint32_t)(addr) - P103_MENUDB58_ADDR)))
#endif
