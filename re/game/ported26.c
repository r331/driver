/* Мелкие обёртки над plat_* (сообщения, UTC-время, громкость wave, тики) — восстановлено из Game.exe. */
/* ported26.c — small wrappers around WinAPI calls, now plat_* (English overview): message boxes, UTC time
   in the debug log, waveOut volume, looking up wheel models in the level data, a random choice of level
   atmosphere flags from timeGetTime, and finding the CD drive.  All __cdecl. */
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
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P26_FxA")
#undef P26_FxA
#pragma push_macro("P26_FxA") /*gvi*/
#undef P26_FxA /*gvi*/
int32_t P26_FxA;
#pragma pop_macro("P26_FxA") /*gvi*/
#pragma pop_macro("P26_FxA")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P26_FxB")
#undef P26_FxB
#pragma push_macro("P26_FxB") /*gvi*/
#undef P26_FxB /*gvi*/
int32_t P26_FxB;
#pragma pop_macro("P26_FxB") /*gvi*/
#pragma pop_macro("P26_FxB")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P26_FxC")
#undef P26_FxC
#pragma push_macro("P26_FxC") /*gvi*/
#undef P26_FxC /*gvi*/
int32_t P26_FxC;
#pragma pop_macro("P26_FxC") /*gvi*/
#pragma pop_macro("P26_FxC")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P26_FxD")
#undef P26_FxD
#pragma push_macro("P26_FxD") /*gvi*/
#undef P26_FxD /*gvi*/
uint8_t P26_FxD;
#pragma pop_macro("P26_FxD") /*gvi*/
#pragma pop_macro("P26_FxD")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P26_ModelHubcap")
#undef P26_ModelHubcap
#pragma push_macro("P26_ModelHubcap") /*gvi*/
#undef P26_ModelHubcap /*gvi*/
int32_t P26_ModelHubcap;
#pragma pop_macro("P26_ModelHubcap") /*gvi*/
#pragma pop_macro("P26_ModelHubcap")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P26_ModelClean")
#undef P26_ModelClean
#pragma push_macro("P26_ModelClean") /*gvi*/
#undef P26_ModelClean /*gvi*/
int32_t P26_ModelClean;
#pragma pop_macro("P26_ModelClean") /*gvi*/
#pragma pop_macro("P26_ModelClean")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P26_ModelFast")
#undef P26_ModelFast
#pragma push_macro("P26_ModelFast") /*gvi*/
#undef P26_ModelFast /*gvi*/
int32_t P26_ModelFast;
#pragma pop_macro("P26_ModelFast") /*gvi*/
#pragma pop_macro("P26_ModelFast")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P26_ModelDam")
#undef P26_ModelDam
#pragma push_macro("P26_ModelDam") /*gvi*/
#undef P26_ModelDam /*gvi*/
int32_t P26_ModelDam;
#pragma pop_macro("P26_ModelDam") /*gvi*/
#pragma pop_macro("P26_ModelDam")
#endif
#define MAIN_HWND ((void *)(intptr_t)G6_00BDF9C0)

/* P26_WaveSetVolume — Game.exe 0048bd65.  Clamps vol to 0..0xffff and sets the same value for the left
   (low word) and right (high word) channel of the wave output. */
void P26_WaveSetVolume(uint32_t vol) {
  int32_t v = (int32_t)vol;
  uint32_t c = v < 0 ? 0 : (v < 0x10000 ? (uint32_t)v : 0xffffu);
  plat_wave_set_volume(c << 16 | c);
}
/* P26_ErrorInLine — Game.exe 004a5ac3.  Warning message box (MB_ICONEXCLAMATION = 0x30) with text msg and the
   title "Error in line N", N = current line of the text file being parsed (G2_01134120). */
void P26_ErrorInLine(const char *msg) {
  char t[52];
  snprintf(t, sizeof t, "Error in line %u", (unsigned)G2_01134120);
  plat_message_box(MAIN_HWND, msg, t, 0x30);
}
/* P26_LogTime — Game.exe 004bf35d.  Writes "label (h:mm.ss)" with the current UTC time to debug.log. */
void P26_LogTime(const char *label) {
  char b[256]; int h, m, s;
  plat_utc_hms(&h, &m, &s);
  snprintf(b, sizeof b, "%s (%d:%02d.%02d)", label, h, m, s);
  DebugLog(b);
}
/* Looks up a model by name in the level's name table; shows msg in an error box when it is missing.
   Returns the model value (0 = not found). */
static int32_t find_model(const char *name, const char *msg) {
  int32_t r = P20_FindNameValue(name);
  if (r == 0) plat_message_box(MAIN_HWND, msg, "ERROR IN _LEVEL_ DATA", 0);
  return r;
}
/* P26_FindWheelModels — Game.exe 004d7b73.  Finds the four wheel models of the level (HUBCAP, CLEANWHEEL,
   FASTWHEEL, DAMWHEEL) and stores them in P26_Model*; a missing one gives an error box but continues with 0. */
void P26_FindWheelModels(void) {
  P26_ModelHubcap = find_model("HUBCAP", "Could not find hubcap model.\nThis is NOT a code bug.  Change name in LEV file.");
  P26_ModelClean = find_model("CLEANWHEEL", "Could not find clean wheel model.\nThis is NOT a code bug.  Change name in LEV file.");
  P26_ModelFast = find_model("FASTWHEEL", "Could not find fast wheel model.\nThis is NOT a code bug.  Change name in LEV file.");
  P26_ModelDam = find_model("DAMWHEEL", "Could not find damaged wheel model.\nThis is NOT a code bug.  Change name in LEV file.");
}
/* Таблица 0056ebd0: 4 строки по 16 байт — {int a, int b, int c, byte d (+3 байта)}; только чтение. */
/* P26_RandomFx atmosphere flags.  TODO(RE): exact meanings unconfirmed.  Usage elsewhere:
   P26_FxA picks the sky variant together with the night flag P14_00b87e84 and disables skid marks
   (ported101/106/117) — presumably rain / wet roads; P26_FxB can only be set together with FxA;
   P26_FxC only by day, P26_FxD only at night (lamps in ported101). */
static const int32_t k_fx[4][4] = { {1,1,0,0}, {1,1,0,1}, {1,1,0,0}, {1,1,1,1} };
/* P26_RandomFx — Game.exe 004fc5e1.  Picks the atmosphere flags P26_FxA..FxD for a level from the low bits of
   timeGetTime (bit 0 -> FxA, bit 1 -> FxB, bit 2 -> FxC, bit 3 -> FxD), each allowed only if row `set`
   (0..3, out of range -> 0) of the table k_fx enables it and the exclusions above hold. */
void P26_RandomFx(int32_t set) {
  if (set < 0 || set > 3) set = 0;
  uint32_t t = plat_time_ms();
  P26_FxA = 0; P26_FxB = 0; P26_FxD = 0; P26_FxC = 0;
  if ((t & 1) != 0 && (P26_FxA = k_fx[set][0]) != 0 && (t & 2) != 0) P26_FxB = k_fx[set][1];
  if ((t & 4) != 0 && P26_FxA == 0 && P14_00b87e84 == 0) P26_FxC = k_fx[set][2];
  if ((t & 8) != 0 && P26_FxA == 0 && P26_FxC == 0 && P14_00b87e84 != 0) P26_FxD = (uint8_t)k_fx[set][3];
}
/* P26_FindCdDrive — Game.exe 004d322c.  Tries every CD-ROM root ("D:\" ...) for file; on the first hit copies
   the root to out and returns 1, else returns 0. */
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
