/* Перехват функций оригинального Game.exe: JMP rel32 на нашу реализацию. */
#pragma once
#include <windows.h>
#include <stdint.h>
#define GAME_BASE 0x00400000u
#define GADDR(a)  ((void*)(uintptr_t)(a))
/* Глобальная переменная Game.exe по абсолютному адресу */
#define GVAR(type, addr) (*(type*)(uintptr_t)(addr))
/* Вызов оригинальной (ещё не перенесённой) функции */
#define GFUNC(ret, addr, args) ((ret (__cdecl*) args)(uintptr_t)(addr))
void re_log(const char *fmt, ...);
int  re_hook(uintptr_t addr, void *impl, const char *name);
void re_install_all(void);
