/* Фатальная ошибка, обработчик аварий, выход — восстановлено из Game.exe (WinMain.c). */
#include "ported30.h"
#include "ported6.h"
#include "ported9.h"
#include "ported25.h"
#include "ported27.h"
#include "uihandlers2.h"
#include "unported.h"
GAME_VAR_DEF(int32_t, P30_ScreensaverSaved, 0x00b87e0c)
#define MAIN_HWND ((void *)(intptr_t)G6_00BDF9C0)

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
void P30_CrashHandler(void) {
  plat_set_crash_handler(NULL);
  P25_TimersShutdown();
  Ui004264A7();
  Call004246F0();
  Call00523595();
  plat_message_box(NULL, "Application Error\nClick OK to close.", "Driver Exception Handler", 0x10);
}
void P30_CrashInstall(void) { plat_set_crash_handler(P30_CrashHandler); }
void P30_CrashRemove(void) { plat_set_crash_handler(NULL); }
void P30_InitWindowGlobals(void) {
  G6_00BDF9C0 = 0;
  G6_00BDF9C4 = 0;
  ResetSlots_004A2B70();
}
void P30_Exit(int32_t code) { plat_exit(code); }
