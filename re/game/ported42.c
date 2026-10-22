/* ported42 — small lookups (Game.exe, cdecl unless noted): MScript command / variable tables, high-score table
   access, D3D version string, Glide device names and DLL unload, view angles and map-cell index.
   Original note: */
/* Таблицы MScript, рекорды, версия, Glide-устройства, углы вида — восстановлено из Game.exe. */
#include "ported42.h"
#include "engine.h"
#include "../platform/plat.h"
#include <string.h>
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P42_Cmds")
#undef P42_Cmds
#pragma push_macro("P42_Cmds") /*gvi*/
#undef P42_Cmds /*gvi*/
p42_cmdtab_t P42_Cmds;
#pragma pop_macro("P42_Cmds") /*gvi*/
#pragma pop_macro("P42_Cmds")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P42_Vars")
#undef P42_Vars
#pragma push_macro("P42_Vars") /*gvi*/
#undef P42_Vars /*gvi*/
p42_vartab_t P42_Vars;
#pragma pop_macro("P42_Vars") /*gvi*/
#pragma pop_macro("P42_Vars")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P42_HighScores")
#undef P42_HighScores
#pragma push_macro("P42_HighScores") /*gvi*/
#undef P42_HighScores /*gvi*/
p42_hs_t P42_HighScores;
#pragma pop_macro("P42_HighScores") /*gvi*/
#pragma pop_macro("P42_HighScores")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P42_DevCount")
#undef P42_DevCount
#pragma push_macro("P42_DevCount") /*gvi*/
#undef P42_DevCount /*gvi*/
int32_t P42_DevCount;
#pragma pop_macro("P42_DevCount") /*gvi*/
#pragma pop_macro("P42_DevCount")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P42_DevNames")
#undef P42_DevNames
#pragma push_macro("P42_DevNames") /*gvi*/
#undef P42_DevNames /*gvi*/
p42_names_t P42_DevNames;
#pragma pop_macro("P42_DevNames") /*gvi*/
#pragma pop_macro("P42_DevNames")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P42_AngY")
#undef P42_AngY
#pragma push_macro("P42_AngY") /*gvi*/
#undef P42_AngY /*gvi*/
uint16_t P42_AngY;
#pragma pop_macro("P42_AngY") /*gvi*/
#pragma pop_macro("P42_AngY")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P42_AngX")
#undef P42_AngX
#pragma push_macro("P42_AngX") /*gvi*/
#undef P42_AngX /*gvi*/
uint16_t P42_AngX;
#pragma pop_macro("P42_AngX") /*gvi*/
#pragma pop_macro("P42_AngX")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P42_AngZ")
#undef P42_AngZ
#pragma push_macro("P42_AngZ") /*gvi*/
#undef P42_AngZ /*gvi*/
uint16_t P42_AngZ;
#pragma pop_macro("P42_AngZ") /*gvi*/
#pragma pop_macro("P42_AngZ")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P42_AngBase")
#undef P42_AngBase
#pragma push_macro("P42_AngBase") /*gvi*/
#undef P42_AngBase /*gvi*/
int32_t P42_AngBase;
#pragma pop_macro("P42_AngBase") /*gvi*/
#pragma pop_macro("P42_AngBase")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P42_CellX")
#undef P42_CellX
#pragma push_macro("P42_CellX") /*gvi*/
#undef P42_CellX /*gvi*/
int32_t P42_CellX;
#pragma pop_macro("P42_CellX") /*gvi*/
#pragma pop_macro("P42_CellX")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P42_CellY")
#undef P42_CellY
#pragma push_macro("P42_CellY") /*gvi*/
#undef P42_CellY /*gvi*/
int32_t P42_CellY;
#pragma pop_macro("P42_CellY") /*gvi*/
#pragma pop_macro("P42_CellY")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P42_CellScale")
#undef P42_CellScale
#pragma push_macro("P42_CellScale") /*gvi*/
#undef P42_CellScale /*gvi*/
float P42_CellScale;
#pragma pop_macro("P42_CellScale") /*gvi*/
#pragma pop_macro("P42_CellScale")
#endif

/* MScript variable table terminator (p42_var_t.type) and the "not found" result of P42_FindCommand. */
#define MSVAR_TYPE_END   0x7f
#define FINDCMD_NOTFOUND 9      /* TODO(RE): unsure — 9 is presumably the script parser's error code */

/* P42_FindCommand — Game.exe 004f6333.  Looks up an MScript command record by name in P42_Cmds (terminated by an
   empty name).  Out: *out = the record or NULL.  Returns 0 when found, 9 when not. */
int32_t P42_FindCommand(const char *name, void **out) {
  *out = NULL;
  for (p42_cmd_t *e = &P42_Cmds[0]; e->name[0] != 0; e++) {   /* ограничитель — пустое имя */
    if (strcmp(name, e->name) == 0) { *out = e; return 0; }
  }
  return FINDCMD_NOTFOUND;
}
/* P42_FindCommandById — Game.exe 004fc5ab.  Name of the MScript command with opcode id (p42_cmd_t.id, +0x104),
   or NULL. */
char *P42_FindCommandById(int32_t id) {
  for (p42_cmd_t *e = &P42_Cmds[0]; e->name[0] != 0; e++)
    if (e->id == id) return e->name;
  return NULL;
}
/* P42_FindVar — Game.exe 004f64dd.  Index of the MScript variable named name in P42_Vars (terminated by type
   0x7f), or -1. */
int32_t P42_FindVar(const char *name) {
  int32_t i = 0;
  for (p42_var_t *e = &P42_Vars[0]; e->type != MSVAR_TYPE_END; e++, i++)
    if (strcmp(e->name, name) == 0) return i;
  return -1;
}
/* P42_GetHighScore — Game.exe 0051cd43.  Entry idx of a high-score table.  Each table is a slice of
   P42_HighScores starting at base: table 2 -> 0, 1 -> 8, 3 -> 16, 6 and 0xb -> 20, 7 -> 24, 0xc -> 28
   (TODO(RE): unsure which game modes the table ids are).  Invalid table: logs and returns 0.  idx is not
   range-checked (as in the original). */
int32_t P42_GetHighScore(int32_t table, int32_t idx) {
  int32_t base;
  switch (table) {
  case 1: base = 8; break;
  case 2: base = 0; break;
  case 3: base = 16; break;
  case 6: case 0xb: base = 20; break;
  case 7: base = 24; break;
  case 0xc: base = 28; break;
  default: DebugLog("GetHighScoreTable: Invalid table request"); return 0;
  }
  return P42_HighScores[base + idx];
}
/* P42_FreeGlide — Game.exe 0042570c.  FreeLibrary(glide2x.dll) if it is loaded; clears P31_GlideModule. */
void P42_FreeGlide(void) {
  if (P31_GlideModule != 0) { plat_dll_unload((void *)(intptr_t)P31_GlideModule); P31_GlideModule = 0; }
}
/* P42_VersionString — Game.exe 0041eb51 (stdcall, ret 4; re_hook thunk).  Copies the renderer version "2.43 (D3D)". */
void P42_VersionString(char *dst) { strcpy(dst, "2.43 (D3D)"); }
/* P42_ActionBound — Game.exe 004d6209.  1 when input action 0xf is active (Call00524473(0xf)) or the current
   bounds slot G8_00B20344 of A_00B20330 (see P46_SetBounds) is not -1; else 0. */
int32_t P42_ActionBound(void) {
  if (Call00524473(0xf) != 0) return 1;
  int32_t v; memcpy(&v, &A_00B20330[G8_00B20344 * 4], 4);
  return v != -1;
}
/* P42_GetDeviceName — Game.exe 004245ec.  Copies the name of Glide device idx (out-of-range -> 0) into dst and
   returns the index used; -1 when Glide is not initialised (D_00b1c0d4 == 0). */
int32_t P42_GetDeviceName(int32_t idx, char *dst) {
  if (D_00b1c0d4 == 0) return -1;
  if (idx < 0 || P42_DevCount <= idx) idx = 0;
  strcpy(dst, (const char *)P42_DevNames[idx]);
  return idx;
}
/* P42_SetViewAngles — Game.exe 004e964a.  View angles from two inputs scaled by scale (computed in double, as the
   original): P42_AngY = a * scale, P42_AngX = P42_AngBase + b * scale, both wrapped to 0..0xfff (4096 = 360 deg);
   P42_AngZ = 0.  The third argument is ignored. */
void P42_SetViewAngles(int32_t a, int32_t b, int32_t unused, float scale) {
  (void)unused;
  P42_AngY = (uint16_t)((int32_t)((double)(float)a * (double)scale) & 0xfff);
  int32_t y = (int32_t)((double)(float)b * (double)scale);
  P42_AngX = (uint16_t)((P42_AngBase + y) & 0xfff);
  P42_AngZ = 0;
}
/* P42_CellIndex — Game.exe 004ece84.  Map-cell index of world point p (p[0] = x, p[2] = z): cell coordinates
   ((P42_CellX + x) * P42_CellScale, (P42_CellY + z) * P42_CellScale), truncated, row-major with P21_GridDiv
   cells per row. */
int32_t P42_CellIndex(const float *p) {
  float x = (float)(((double)(float)P42_CellX + (double)p[0]) * (double)P42_CellScale);
  float y = (float)(((double)(float)P42_CellY + (double)p[2]) * (double)P42_CellScale);
  return (int32_t)x + (int32_t)y * P21_GridDiv;
}
