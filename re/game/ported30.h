#pragma once
#include "gvar.h"
#include "../platform/plat.h"
#include <stdint.h>
/* Аварийные пути и инициализация окна (WinMain.c): фатальная ошибка, обработчик исключений, выход — над plat_*. Все __cdecl. */
#define P30_ScreensaverSaved GAME_VAR(int32_t, P30_ScreensaverSaved, 0x00b87e0c)  /* состояние хранителя экрана до запуска */
#ifndef RE_HOOK_BUILD
#pragma push_macro("P30_ScreensaverSaved") /*gvi*/
#undef P30_ScreensaverSaved /*gvi*/
extern int32_t P30_ScreensaverSaved;
#pragma pop_macro("P30_ScreensaverSaved") /*gvi*/
#endif
void P30_FatalError(const char *msg);  /* 00522369: остановить подсистемы, MessageBox «ERROR», отчёт об утечках, выход */
void P30_CrashHandler(void);           /* 00522759: тело обработчика аварий (в оригинале UnhandledExceptionFilter) */
void P30_CrashInstall(void);           /* 0052273c */
void P30_CrashRemove(void);            /* 0052274c */
void P30_InitWindowGlobals(void);      /* 005223be: hwnd = hinstance = 0, сброс слотов */
void P30_Exit(int32_t code);           /* 0052e400: exit(code) */
/* gvar-img v2.03 begin (tools/gen_gvar_img.py) */
#if !defined(RE_HOOK_BUILD) && !defined(RE_GVAR_PLAIN)
#undef P30_ScreensaverSaved
#define P30_ScreensaverSaved (*(int32_t *)re_gvar(0x00b87e0cu, sizeof(int32_t), (void *)&P30_ScreensaverSaved))
#endif
/* gvar-img v2.03 end */
