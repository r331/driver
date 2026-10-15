/* Мелкие обёртки над plat_* (сообщения, UTC-время, громкость wave, тики) — восстановлено из Game.exe. */
#include "ported26.h"
#include "ported5.h"
#include "ported6.h"
#include "ported14.h"
#include "ported20.h"
#include "smallfuncs.h"
#include "smallfuncs2.h"
#include "engine.h"
#include <stdio.h>
#include <string.h>
GAME_VAR_DEF(int32_t, P26_FxA, 0x00b202e0)
GAME_VAR_DEF(int32_t, P26_FxB, 0x00b202d4)
GAME_VAR_DEF(int32_t, P26_FxC, 0x00b202e4)
GAME_VAR_DEF(uint8_t, P26_FxD, 0x00b20300)
GAME_VAR_DEF(int32_t, P26_ModelHubcap, 0x00d11820)
GAME_VAR_DEF(int32_t, P26_ModelClean, 0x00d117f4)
GAME_VAR_DEF(int32_t, P26_ModelFast, 0x00d117e0)
GAME_VAR_DEF(int32_t, P26_ModelDam, 0x00d117a0)
#define MAIN_HWND ((void *)(intptr_t)G6_00BDF9C0)

void P26_WaveSetVolume(uint32_t vol) {
  int32_t v = (int32_t)vol;
  uint32_t c = v < 0 ? 0 : (v < 0x10000 ? (uint32_t)v : 0xffffu);
  plat_wave_set_volume(c << 16 | c);
}
void P26_ErrorInLine(const char *msg) {
  char t[52];
  snprintf(t, sizeof t, "Error in line %u", (unsigned)G2_01134120);
  plat_message_box(MAIN_HWND, msg, t, 0x30);
}
void P26_LogTime(const char *label) {
  char b[256]; int h, m, s;
  plat_utc_hms(&h, &m, &s);
  snprintf(b, sizeof b, "%s (%d:%02d.%02d)", label, h, m, s);
  DebugLog(b);
}
static int32_t find_model(const char *name, const char *msg) {
  int32_t r = P20_FindNameValue(name);
  if (r == 0) plat_message_box(MAIN_HWND, msg, "ERROR IN _LEVEL_ DATA", 0);
  return r;
}
void P26_FindWheelModels(void) {
  P26_ModelHubcap = find_model("HUBCAP", "Could not find hubcap model.\nThis is NOT a code bug.  Change name in LEV file.");
  P26_ModelClean = find_model("CLEANWHEEL", "Could not find clean wheel model.\nThis is NOT a code bug.  Change name in LEV file.");
  P26_ModelFast = find_model("FASTWHEEL", "Could not find fast wheel model.\nThis is NOT a code bug.  Change name in LEV file.");
  P26_ModelDam = find_model("DAMWHEEL", "Could not find damaged wheel model.\nThis is NOT a code bug.  Change name in LEV file.");
}
/* Таблица 0056ebd0: 4 строки по 16 байт — {int a, int b, int c, byte d (+3 байта)}; только чтение. */
static const int32_t k_fx[4][4] = { {1,1,0,0}, {1,1,0,1}, {1,1,0,0}, {1,1,1,1} };
void P26_RandomFx(int32_t set) {
  if (set < 0 || set > 3) set = 0;
  uint32_t t = plat_time_ms();
  P26_FxA = 0; P26_FxB = 0; P26_FxD = 0; P26_FxC = 0;
  if ((t & 1) != 0 && (P26_FxA = k_fx[set][0]) != 0 && (t & 2) != 0) P26_FxB = k_fx[set][1];
  if ((t & 4) != 0 && P26_FxA == 0 && P14_00b87e84 == 0) P26_FxC = k_fx[set][2];
  if ((t & 8) != 0 && P26_FxA == 0 && P26_FxC == 0 && P14_00b87e84 != 0) P26_FxD = (uint8_t)k_fx[set][3];
}
int32_t P26_FindCdDrive(const char *file, char *out) {
  char roots[1024], path[1100];
  if (plat_cd_roots(roots, sizeof roots) == 0) return 0;
  for (const char *r = roots; *r; r += strlen(r) + 1) {
    snprintf(path, sizeof path, "%s%s", r, file);
    FILE *f = (FILE *)plat_file_open(path, "rb");
    if (f != NULL) { fclose(f); strcpy(out, r); return 1; }
  }
  return 0;
}
