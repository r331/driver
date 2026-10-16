/* Объявление глобалов и функций игры для двух целей сборки.
   RE_HOOK_BUILD: глобал = ячейка оригинального Game.exe по адресу, ещё не перенесённая функция = вызов по адресу.
   Нативная сборка: обычные C-переменные и функции (определяются в game/ (.c) или platform/). */
#pragma once
#include <stdint.h>
#include <stddef.h>
#ifdef RE_HOOK_BUILD
#  define GAME_VAR(type, name, addr)          (*(type*)(uintptr_t)(addr))
#  define GAME_VAR_DEF(type, name, addr)      /* живёт в Game.exe */
#else
#  define GAME_VAR(type, name, addr)          name
/* v2.03 (блокеры 3/4): в игре (re_ptr_set_image) переменная с адресом в .rdata+.data Game.exe 00546000..0057c000 живёт в образе
   этих секций (game/data_image.c): один объект на адрес — запись через любой псевдоним видна всем и re_ptr(адрес) (таблицы меню),
   начальные значения — из Game.exe. Переопределения NAME → re_gvar(...) — в конце заголовков (tools/gen_gvar_img.py).
   Вне игры (selftest/ctest) образа нет — обычные native-объекты. */
extern uint8_t *re_gvar_img; extern uint32_t re_gvar_img_size;
static inline void *re_gvar(uint32_t a, size_t sz, void *nat) {
  uint32_t o = a - 0x00546000u;
  return (re_gvar_img != NULL && a >= 0x00546000u && o + sz <= re_gvar_img_size) ? (void *)(re_gvar_img + o) : nat;
}
#  define GAME_VAR_DEF(type, name, addr)      type name;
#endif
#include "cartab.h"
#include "icontab.h"
