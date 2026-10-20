/* Fatal error / crash handler / process exit (Game.exe WinMain.c). */
/* Фатальная ошибка, обработчик аварий, выход — восстановлено из Game.exe (WinMain.c). */
#include "ported30.h"
#include "ported6.h"
#include "ported9.h"
#include "ported25.h"
#include "ported27.h"
#include "uihandlers2.h"
#include "unported.h"
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P30_ScreensaverSaved")
#undef P30_ScreensaverSaved
#pragma push_macro("P30_ScreensaverSaved") /*gvi*/
#undef P30_ScreensaverSaved /*gvi*/
int32_t P30_ScreensaverSaved;
#pragma pop_macro("P30_ScreensaverSaved") /*gvi*/
#pragma pop_macro("P30_ScreensaverSaved")
#endif
#define MAIN_HWND ((void *)(intptr_t)G6_00BDF9C0)

/* P30_FatalError — Game.exe 00522369, cdecl.  Shut everything down and quit after a fatal error.
   Stops timers, shuts down DirectInput/COM (004d3402), front-end and sound (004264a7,
   004246f0), removes the crash handler, shows msg in an "ERROR" message box, writes the memory
   leak report, restores the saved screensaver setting and exits with code 0.  Does not return. */
void P30_FatalError(const char *msg) {
  P25_TimersShutdown();
  Call004D3402();                       /* DirectInput/COM выключение */
  Ui004264A7();
  Call004246F0();
  plat_set_crash_handler(NULL);
  plat_message_box(MAIN_HWND, msg, "ERROR", 0);
  P27_MemLeakReport();
  plat_screensaver_set(P30_ScreensaverSaved);
  P30_Exit(0);
}
/* P30_CrashHandler — Unhandled-exception handler installed by P30_CrashInstall.
   Removes itself, stops timers, front end and sound (00523595 too), then shows
   "Application Error" (MB_ICONERROR = 0x10).  The process is left to the OS afterwards. */
void P30_CrashHandler(void) {
  plat_set_crash_handler(NULL);
  P25_TimersShutdown();
  Ui004264A7();
  Call004246F0();
  Call00523595();
  plat_message_box(NULL, "Application Error\nClick OK to close.", "Driver Exception Handler", 0x10);
}
/* P30_CrashInstall — Game.exe 0052273c, cdecl.  Install P30_CrashHandler as the unhandled-exception handler. */
void P30_CrashInstall(void) { plat_set_crash_handler(P30_CrashHandler); }
/* P30_CrashRemove — Game.exe 0052274c, cdecl.  Remove the unhandled-exception handler. */
void P30_CrashRemove(void) { plat_set_crash_handler(NULL); }
/* P30_InitWindowGlobals — Clear the main window handle (00bdf9c0) and 00bdf9c4, then reset the slot table (004a2b70).
   TODO(RE): unsure what 00bdf9c4 holds. */
void P30_InitWindowGlobals(void) {
  G6_00BDF9C0 = 0;
  G6_00BDF9C4 = 0;
  ResetSlots_004A2B70();
}
/* P30_Exit — Game.exe 0052e400, cdecl.  Terminate the process with the given exit code (the CRT exit()). */
void P30_Exit(int32_t code) { plat_exit(code); }
