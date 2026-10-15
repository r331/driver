/* Таблицы MScript, рекорды, версия, Glide-устройства, углы вида — восстановлено из Game.exe. */
#include "ported42.h"
#include "engine.h"
#include "../platform/plat.h"
#include <string.h>
GAME_VAR_DEF(p42_cmdtab_t, P42_Cmds, 0x00563980)
GAME_VAR_DEF(p42_vartab_t, P42_Vars, 0x0056dc10)
GAME_VAR_DEF(p42_hs_t, P42_HighScores, 0x00bdfb20)
GAME_VAR_DEF(int32_t, P42_DevCount, 0x00b1c0e0)
GAME_VAR_DEF(p42_names_t, P42_DevNames, 0x01270ec4)
GAME_VAR_DEF(uint16_t, P42_AngY, 0x00d02700)
GAME_VAR_DEF(uint16_t, P42_AngX, 0x00d02702)
GAME_VAR_DEF(uint16_t, P42_AngZ, 0x00d02704)
GAME_VAR_DEF(int32_t, P42_AngBase, 0x00d02718)
GAME_VAR_DEF(int32_t, P42_CellX, 0x00ce0f2c)
GAME_VAR_DEF(int32_t, P42_CellY, 0x00ce0f30)
GAME_VAR_DEF(float, P42_CellScale, 0x0125f3e8)

int32_t P42_FindCommand(const char *name, void **out) {
  *out = NULL;
  for (p42_cmd_t *e = &P42_Cmds[0]; e->name[0] != 0; e++) {   /* ограничитель — пустое имя */
    if (strcmp(name, e->name) == 0) { *out = e; return 0; }
  }
  return 9;
}
char *P42_FindCommandById(int32_t id) {
  for (p42_cmd_t *e = &P42_Cmds[0]; e->name[0] != 0; e++)
    if (e->id == id) return e->name;
  return NULL;
}
int32_t P42_FindVar(const char *name) {
  int32_t i = 0;
  for (p42_var_t *e = &P42_Vars[0]; e->type != 0x7f; e++, i++)
    if (strcmp(e->name, name) == 0) return i;
  return -1;
}
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
void P42_FreeGlide(void) {
  if (P31_GlideModule != 0) { plat_dll_unload((void *)(intptr_t)P31_GlideModule); P31_GlideModule = 0; }
}
void P42_VersionString(char *dst) { strcpy(dst, "2.43 (D3D)"); }
int32_t P42_ActionBound(void) {
  if (Call00524473(0xf) != 0) return 1;
  int32_t v; memcpy(&v, &A_00B20330[G8_00B20344 * 4], 4);
  return v != -1;
}
int32_t P42_GetDeviceName(int32_t idx, char *dst) {
  if (D_00b1c0d4 == 0) return -1;
  if (idx < 0 || P42_DevCount <= idx) idx = 0;
  strcpy(dst, (const char *)P42_DevNames[idx]);
  return idx;
}
void P42_SetViewAngles(int32_t a, int32_t b, int32_t unused, float scale) {
  (void)unused;
  P42_AngY = (uint16_t)((int32_t)((double)(float)a * (double)scale) & 0xfff);
  int32_t y = (int32_t)((double)(float)b * (double)scale);
  P42_AngX = (uint16_t)((P42_AngBase + y) & 0xfff);
  P42_AngZ = 0;
}
int32_t P42_CellIndex(const float *p) {
  float x = (float)(((double)(float)P42_CellX + (double)p[0]) * (double)P42_CellScale);
  float y = (float)(((double)(float)P42_CellY + (double)p[2]) * (double)P42_CellScale);
  return (int32_t)x + (int32_t)y * P21_GridDiv;
}
