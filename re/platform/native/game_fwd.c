/* v2.01: слабые заглушки unported.h (platform/native/stubs.c), у которых есть перенос, но которые оставлены V-строками
   ради selftest (tests рассчитывают на пустую заглушку): в игре (re_selftest_on = 0) — вызов перенесённой функции. */
#include <stdint.h>
extern int re_selftest_on;
int32_t P136_FrontInit(void); void P136_GameLoop(int32_t replay);
void Call0040BF50(void) { if (!re_selftest_on) (void)P136_FrontInit(); }
void Call0040C20B(int32_t a0) { if (!re_selftest_on) P136_GameLoop(a0); }
/* 0040cfdf: значок по имени (фон меню BKGRND*) — перенесено как P67_DrawIcon, связи не было (другое имя заглушки) */
void P67_DrawIcon(int32_t x, int32_t y, int32_t unused, const char *name);
void P58_Fn40CFDF(int32_t x, int32_t y, uint32_t tbl, const char *name, int32_t a4) {
  (void)a4; if (!re_selftest_on) P67_DrawIcon(x, y, (int32_t)tbl, name); }
/* v2.02: 004ec91e (поиск значка по имени) — заглушки LoadIconByName/Call004EC91E (в --skip ради selftest) в игре зовут P93_FindIcon;
   результат — 32-битный адрес записи значка (re_addr), как в Game.exe */
#include "../../game/reptr.h"
uint8_t *P93_FindIcon(const char *name);
uint32_t LoadIconByName(const char *name) { return re_selftest_on ? 0u : re_addr(P93_FindIcon(name)); }
int32_t Call004EC91E(const char *a0) { return re_selftest_on ? 0 : (int32_t)re_addr(P93_FindIcon(a0)); }
