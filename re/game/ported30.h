#pragma once
#include "gvar.h"
#include "../platform/plat.h"
#include <stdint.h>
/* Аварийные пути и инициализация окна (WinMain.c): фатальная ошибка, обработчик исключений, выход — над plat_*. Все __cdecl. */
#define P30_ScreensaverSaved GAME_VAR(int32_t, P30_ScreensaverSaved, 0x00b87e0c)  /* состояние хранителя экрана до запуска */
#ifndef RE_HOOK_BUILD
extern int32_t P30_ScreensaverSaved;
#endif
void P30_FatalError(const char *msg);  /* 00522369: остановить подсистемы, MessageBox «ERROR», отчёт об утечках, выход */
void P30_CrashHandler(void);           /* 00522759: тело обработчика аварий (в оригинале UnhandledExceptionFilter) */
void P30_CrashInstall(void);           /* 0052273c */
void P30_CrashRemove(void);            /* 0052274c */
void P30_InitWindowGlobals(void);      /* 005223be: hwnd = hinstance = 0, сброс слотов */
void P30_Exit(int32_t code);           /* 0052e400: exit(code) */
