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
#  define GAME_VAR_DEF(type, name, addr)      type name;
#endif
#include "cartab.h"
#include "icontab.h"
