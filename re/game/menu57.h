/* v1.58: .data меню опций 0057b578..0057b658 (0xe0) в native — один массив P57_MenuTab (game/p57_data.h,
   tools/gen_p57_data.py), зарегистрированный в k_regions game/reptr.c: 0057b578 — P54_SelTab (12 × int32),
   0057b5a8 — таблица меню (11 × 0x10: адреса обработчиков +0/+4/+8 — uint32 Game.exe, вызов через re_fn; байты
   навигации +0xc..+0xf). Имена внутри — макросы MENU57_VAR без отдельных native-переменных. В hook — ячейки Game.exe. */
#pragma once
#include <stdint.h>
#define P57_MENU_ADDR 0x0057b578u
#define P57_MENU_SIZE 0xe0
#define P57_OPTTAB_ADDR 0x0057b5a8u
#ifdef RE_HOOK_BUILD
#  define MENU57_VAR(type, name, addr) (*(type *)(uintptr_t)(addr))
#else
typedef union { uint8_t b[P57_MENU_SIZE]; uint32_t u[P57_MENU_SIZE / 4]; } p57_menutab_t;
extern p57_menutab_t P57_MenuTab;
#  define MENU57_VAR(type, name, addr) (*(type *)(P57_MenuTab.b + ((uint32_t)(addr) - P57_MENU_ADDR)))
#endif
/* запись k таблицы меню опций */
#define P57_OPT_FN(k, j)  MENU57_VAR(uint32_t, P57_OptFn, P57_OPTTAB_ADDR + (uint32_t)(k) * 0x10 + (uint32_t)(j) * 4)
#define P57_OPT_NAV(k, j) MENU57_VAR(uint8_t, P57_OptNav, P57_OPTTAB_ADDR + (uint32_t)(k) * 0x10 + 0xc + (uint32_t)(j))
