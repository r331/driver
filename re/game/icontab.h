/* v1.56: таблица значков 01105d68 (9 × uint32 — адреса записей значков 004ec91e, индекс — байт +0x3a обломка, 004b05ea).
   Имена внутри неё — макросы ICONTAB_VAR без отдельных native-переменных: [2..5] JLITTER1..4 (004abd69),
   [6] G01105D80, [7] P95_PoolIcon (CARPOOL6), [8] P108_SmokeIcon (SMOKE). В hook — ячейки Game.exe. */
#pragma once
#include <stdint.h>
#define P111_ICONTAB_ADDR 0x01105d68u
#define P111_ICONTAB_N 9
typedef uint32_t p111_icontab_t[P111_ICONTAB_N];
#ifdef RE_HOOK_BUILD
#  define P111_IconTab (*(p111_icontab_t *)(uintptr_t)P111_ICONTAB_ADDR)
#else
extern p111_icontab_t P111_IconTab;
#endif
#define ICONTAB_VAR(type, idx) (*(type *)&P111_IconTab[(idx)])
