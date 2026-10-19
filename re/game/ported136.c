/* v1.81: ported136 — см. ported136.h.
   004a1d4c — колёса машины car: скорость +0x10c / 256 (−700 при +0x108 ≠ 0; 0 при контакте +0x79 / +0x85) поворачивает
     P136_WheelRot/RotB (если 00b5a778 = 0); модель CLEAN/FAST по |скорости| < 0x1f5, у игрока колесо без флага 010de220[3−i] — DAM;
     матрица передних — RotY(+0xfc & 0xfff) × mat (Mat3MulT); в вершины модели (+0x84..+0xf8) пишутся UV-повороты cos/sin · 72;
     позиция колеса (±25 − x, −70 − y + (20 − подвеска), −z из записи модели 00d0cc60 + 0xe0) через mat, + позиция − камера,
     через 011effa0; рисование 00428b69, а при 00b87ea0 ≠ 0 и car = 0x41 — 0042b7cb (режим mode − 1). Glide: при 01270c48 ≠ 0
     grAlphaBlend(3,8,0,1,1)/grDepth(4) до и (3,8,0,2,1)/(7) после, флаг 01252b78.
   004a3d40 — переменная EVENTSCRIPT: лог, "Scripts\Events\%s" → 004d30f8; «DRIVER EVENT SCRIPT %f» = 2.0 (double) — 004a3f06,
     004a5a83 "EVENT_LIST", 004a3fa6, освобождение имён моделей 00b1ff60/00b1ff64; иначе лог ошибки. При 00d12418 = 0 — только лог.
   0040c20b — цикл игры: 7 слов 00bdfa40 сохраняются и восстанавливаются (все native-псевдонимы); режим 00549cc0×00549cc4;
     00522323; GameMode = replay ? 4 : 0; пока не выход — кадры 004d4a63 до 00b87e20 = 0, 004d4663, разбор 005f7e54 (2 — выход,
     3 — снова, 4/5 — повтор TEMP через 00405f6f/00405f2e, 6 — тренировка 0054aa44); затем сброс HUD и Scripts\Waypoint.tmp.
   0040bf50 — единичная матрица 011effa0, камера 0, 00523c99(0,0,0), рекорды, config.dat, режим 640×480, 4 обмена, окно (0,48,640,432),
     формат LFB (сбой — фатальная ошибка), FRONTEND.TSD (0040d07b — не перенесена), палитры 004079aa, 0x400 байт → 01271a80,
     шрифты F1_..F4_, звук TITLE.DSS, CD-трек 2, тики; 1 — успех.
   00501770 — карта-оверлей города (таблица 00574018 / прямоугольник 00573fa8 — копии .data): BMP 8 бит, палитра 0x400 в 012587e0
     (первый цвет обнуляется), при 00bdfaa0 ≠ 0 — перевод в 16 бит сдвигами 00bdfa80..94.
   Отступления native: модель колеса 0 — колесо пропускается; номер записи модели вне 00d0cc60 — колесо пропускается; город вне 0..6 —
     как отсутствие имени. Вызовы 0040c20b/0040bf50/00501770 из перенесённого кода остаются через V-строки (Call0040C20B, Call0040BF50,
     P77_Fn501770 — заглушки, на которые рассчитывает селфтест; --skip). */
#include "ported136.h"
#include <string.h>
#include <stdio.h>
#include "crt.h"
#include "reptr.h"
#include "cartab.h"
#include "unported.h"
#include "ported137.h"
#include "globalsets.h"
#include "menustate.h"
#include "smallfuncs.h"
#include "smallfuncs2.h"
#include "uihandlers.h"
#include "uihandlers2.h"
#include "uihandlers4.h"
#include "director.h"
#include "ported4.h"
#include "ported5.h"
#include "ported6.h"
#include "ported8.h"
#include "ported11.h"
#include "ported12.h"
#include "ported14.h"
#include "ported15.h"
#include "ported16.h"
#include "ported17.h"
#include "ported19.h"
#include "ported21.h"
#include "ported25.h"
#include "ported26.h"
#include "ported27.h"
#include "ported30.h"
#include "ported42.h"
#include "ported43.h"
#include "ported44.h"
#include "ported45.h"
#include "ported47.h"
#include "ported48.h"
#include "ported51.h"
#include "ported54.h"
#include "ported55.h"
#include "ported56.h"
#include "ported57.h"
#include "ported58.h"
#include "ported59.h"
#include "ported62.h"
#include "ported64.h"
#include "ported68.h"
#include "ported77.h"
#include "ported84.h"
#include "ported94.h"
#include "ported97.h"
#include "ported98.h"
#include "ported99.h"
#include "ported100.h"
#include "ported101.h"
#include "ported109.h"
#include "ported117.h"
#include "ported122.h"
#include "ported123.h"
#include "ported124.h"
#include "ported125.h"
#include "ported131.h"
#include "ported133.h"
#include "ported145.h"

#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P136_WheelRot")
#undef P136_WheelRot
#pragma push_macro("P136_WheelRot") /*gvi*/
#undef P136_WheelRot /*gvi*/
p136_rot_t P136_WheelRot;
#pragma pop_macro("P136_WheelRot") /*gvi*/
#pragma pop_macro("P136_WheelRot")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P136_WheelRotB")
#undef P136_WheelRotB
#pragma push_macro("P136_WheelRotB") /*gvi*/
#undef P136_WheelRotB /*gvi*/
p136_rot_t P136_WheelRotB;
#pragma pop_macro("P136_WheelRotB") /*gvi*/
#pragma pop_macro("P136_WheelRotB")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P136_EvPath")
#undef P136_EvPath
#pragma push_macro("P136_EvPath") /*gvi*/
#undef P136_EvPath /*gvi*/
p136_path_t P136_EvPath;
#pragma pop_macro("P136_EvPath") /*gvi*/
#pragma pop_macro("P136_EvPath")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P136_Pal16")
#undef P136_Pal16
#pragma push_macro("P136_Pal16") /*gvi*/
#undef P136_Pal16 /*gvi*/
p136_pal16_t P136_Pal16;
#pragma pop_macro("P136_Pal16") /*gvi*/
#pragma pop_macro("P136_Pal16")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P136_MapName")
#undef P136_MapName
#pragma push_macro("P136_MapName") /*gvi*/
#undef P136_MapName /*gvi*/
p136_path_t P136_MapName;
#pragma pop_macro("P136_MapName") /*gvi*/
#pragma pop_macro("P136_MapName")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P136_MapScroll")
#undef P136_MapScroll
#pragma push_macro("P136_MapScroll") /*gvi*/
#undef P136_MapScroll /*gvi*/
int32_t P136_MapScroll;
#pragma pop_macro("P136_MapScroll") /*gvi*/
#pragma pop_macro("P136_MapScroll")
#endif

typedef long double ld;
static void wf(uint8_t *v, uint32_t off, float f) { memcpy(v + off, &f, 4); }
static void glide_on(void) {
  if (P62_I270C48 != 0 && P62_I252B78 != 1) { if (P97_GrAlpha) P97_GrAlpha(3, 8, 0, 1, 1); if (P97_GrDepth) P97_GrDepth(4); P62_I252B78 = 1; }
}
static void glide_off(void) {
  if (P62_I270C48 != 0 && P62_I252B78 != 0) { if (P97_GrAlpha) P97_GrAlpha(3, 8, 0, 2, 1); if (P97_GrDepth) P97_GrDepth(7); P62_I252B78 = 0; }
}

/* ---- 004a1d4c ---- */
void P136_DrawWheels(int32_t car, const float *mat, int32_t mode) {
  p99_car_t *c;
  int32_t sf, sr, mf, mr;
  float m9[16], md[16], ox, oy, oz;
  float f5, f6, r70, r6c;
  float A[8], B[8];
  if (car < 0 || car >= P99_CARS_N) return;
  c = &P99_Cars[car];
  sf = c->f10c / 256;
  sr = c->f10c / 256;
  if (c->f108 != 0) sr = -700;
  if (c->f78[0][1] != 0) sf = 0;               /* +0x79 */
  if (c->f78[3][1] != 0) sr = 0;               /* +0x85 */
  if (G6_00B5A778 == 0) {
    P136_WheelRot[car] = (int32_t)((uint32_t)(P136_WheelRot[car] + sf) & 0xfff);
    P136_WheelRotB[car] = (int32_t)((uint32_t)(P136_WheelRotB[car] + sr) & 0xfff);
  }
  mf = (sf < 0x1f5 && -0x1f5 < sf) ? P26_ModelClean : P26_ModelFast;
  mr = (sr < 0x1f5 && -0x1f5 < sr) ? P26_ModelClean : P26_ModelFast;
  memset(m9, 0, sizeof m9);
  m9[0] = 1.0f; m9[4] = 1.0f; m9[8] = 1.0f;
  P44_RotY(m9, c->ffc & 0xfff);
  memset(md, 0, sizeof md);
  Mat3MulT_005284AC(m9, mat, md);
  f5 = P43_Sin[1024 + P136_WheelRot[car]] * 72.0f;
  f6 = P43_Sin[P136_WheelRot[car]] * 72.0f;
  /* передние: +0x84,+0x88,+0x94,+0x98,+0xa4,+0xa8,+0xb4,+0xb8 (и те же +0x40) */
  A[0] = f5 - f6; A[1] = f6 + f5; A[2] = -f5 - f6; A[3] = -f6 + f5; A[4] = -f5 + f6; A[5] = -f6 - f5; A[6] = f5 + f6; A[7] = f6 - f5;
  r70 = P43_Sin[1024 + P136_WheelRotB[car]] * 72.0f;
  r6c = P43_Sin[P136_WheelRotB[car]] * 72.0f;
  B[0] = r70 - r6c; B[1] = r6c + r70; B[2] = -r70 - r6c; B[3] = -r6c + r70; B[4] = -r70 + r6c; B[5] = -r6c - r70; B[6] = r70 + r6c; B[7] = r6c - r70;
  glide_on();
  ox = (float)c->pos[0] - P44_CamX;
  oy = (float)(-c->pos[1]) - P44_CamY;
  oz = (float)c->pos[2] - P44_CamZ;
  for (uint32_t i = 0; i < 4; i++) {
    int32_t m;
    uint32_t off = (uint32_t)c->f00[2] * 0x16c + 0xe0 + i * 8;
    int16_t wx, wy, wz;
    float p[3];
    static const uint32_t vo[8] = { 0x84, 0x88, 0x94, 0x98, 0xa4, 0xa8, 0xb4, 0xb8 };
    if (car == 0 && ((const int32_t *)(const void *)P98_CarBufC)[3 - i] == 0) m = P26_ModelDam;
    else m = (i & 1) ? mr : mf;
#ifndef RE_HOOK_BUILD
    { static int k; if (getenv("RE_WHEELDBG") && k++ < 16) fprintf(stderr, "[wheel] car %d i %d m %08x hub %08x clean %08x fast %08x dam %08x off %u mode %d\n", car, i, (unsigned)m,
        (unsigned)P26_ModelHubcap, (unsigned)P26_ModelClean, (unsigned)P26_ModelFast, (unsigned)P26_ModelDam, off, mode); }
#endif
    if (m == 0 || off + 6 > sizeof(S_00D0CC60)) continue;
    memcpy(&wx, &S_00D0CC60[off], 2); memcpy(&wy, &S_00D0CC60[off + 2], 2); memcpy(&wz, &S_00D0CC60[off + 4], 2);
    p[0] = (float)((i & 2) == 0 ? 0x19 - wx : -0x19 - wx);
    p[1] = (float)((ld)(float)(-0x46 - wy) + (ld)(float)(int32_t)(0x14 - (uint32_t)c->f78[i][0]));
    p[2] = (float)(-(int32_t)wz);
    P44_MatPtr = (float *)mat;
    P44_XformT(p);
    p[0] += ox; p[1] += oy; p[2] += oz;
    P44_MatPtr = P44_ViewMatT;
    P44_Xform(p);
#ifndef RE_HOOK_BUILD
    { static int k; if (getenv("RE_WHEELDBG") && k++ < 8) fprintf(stderr, "[wheel] sin %f %f rot %d i %u w %d %d %d f78 %d p %.1f %.1f %.1f cam %.0f %.0f %.0f car %d %d %d\n", P43_Sin[256], P43_Sin[1024], (int)P136_WheelRot[car], i, wx, wy, wz, (int)c->f78[i][0], p[0], p[1], p[2],
        P44_CamX, P44_CamY, P44_CamZ, (int)c->pos[0], (int)c->pos[1], (int)c->pos[2]); }
#endif
    {
      uint8_t *mdl = (uint8_t *)P79_PTR((uint32_t)m);
      uint8_t *v = (uint8_t *)P79_PTR(*(uint32_t *)(mdl + 0x20));
      const float *t = (i & 1) ? B : A;
      for (int k = 0; k < 8; k++) { wf(v, vo[k], t[k]); wf(v, vo[k] + 0x40, t[k]); }
    }
    {
      const float *mm = (i & 1) ? mat : md;
      if (P62_HudOff1 != 0 && car == 0x41) P84_DrawModelC((uint32_t)m, mm, p, mode - 1);
      else P84_DrawModel((uint32_t)m, mm, p, mode - 1);
    }
  }
  glide_off();
}

/* ---- 004a3d40 ---- */
static const char *var_str(int32_t i) {
#ifdef RE_HOOK_BUILD
  return (const char *)(uintptr_t)P42_Vars[i].addr;
#else
  /* v2.07: строку пишут два setter-а — P59_VarSetString (004f8a2d, в native — P59_VarStr) и P99_VarSetStr (EVENTSCRIPT ← .DES
     в P138_LoadMission: re_wr_ptr в поле +0x24 записи); в Game.exe это одно поле. Читаем оба. */
  if (P59_VarStr[i] != NULL) return P59_VarStr[i];
  return P42_Vars[i].addr != 0 ? (const char *)re_rd_ptr((uint8_t *)&P42_Vars[i] + 0x24) : NULL;
#endif
}
void P136_CompileEvents(void) {
  int32_t v = P42_FindVar("EVENTSCRIPT");
  const char *nm;
  char *buf;
  float ver = 0;
  int32_t r;
  if (v == -1) return;
  nm = var_str(v);
  snprintf(P136_EvPath, sizeof(P136_EvPath), "\nAttempting to compile event script \"Scripts\\Events\\%s\".", nm ? nm : "(null)");
  P124_DebugLog(P136_EvPath);
  snprintf(P136_EvPath, sizeof(P136_EvPath), "Scripts\\Events\\%s", nm ? nm : "(null)");
  P62_ModelCount = 0;
  if (P28_EventCount == 0) return;
  buf = (char *)P55_LoadFile(P136_EvPath);
  if (buf == NULL) { P124_DebugLog("Unable to open script file!  Operation failed."); return; }
  r = g_sscanf(buf, "DRIVER EVENT SCRIPT %f", &ver);
  if (r == 0 || r == -1) {
    P124_DebugLog("This is not a legal Driver Event Script.  Operation failed.");
    P98_DebugFree(buf);
  } else if ((double)ver == 2.0) {
    char *p = (char *)P59_ModelNames(buf);
    p = P51_SkipToLine(p, "EVENT_LIST");
    P123_EventsChunk(p);
    if (P62_ModelNames != NULL) P98_DebugFree((void *)P62_ModelNames);
    P62_ModelNames = NULL;
    P125_ModelNamesSize = 0;
    P98_DebugFree(buf);
    P124_DebugLog("Script file compiled successfully.  Operation complete.\n");
  } else {
    P124_DebugLog("Script file is not version 2.0!  Operation failed.");
    P98_DebugFree(buf);
  }
}

/* ---- 0040c20b ---- */
static void set_e54(int32_t v) { G005F7E54 = v; P17_Const6 = v; P8_005f7e54 = v; }
static void set_e38(int32_t v) { P11_00b87e38 = v; P17_Cond2 = v; P19_Cond = v; P45_Mode = v; UiVar00B87E38 = v; }
static void set_aa44(int32_t v) { G0054AA44 = v; P17_Dst = v; }
static void set_hud1(int32_t v) { G6_00B87EA0 = v; P62_HudOff1 = v; }
static void set_a778(int32_t v) { G6_00B5A778 = v; P16_FlagA = v; }
static void opt_save(int32_t *s) {
  s[0] = P12_00bdfa40; s[1] = MenuOptBDFA44; s[2] = MenuOptBDFA48; s[3] = MenuOptBDFA4C; s[4] = MenuOptBDFA50; s[5] = MenuOptBDFA54; s[6] = MenuOptBDFA58;
}
static void opt_restore(const int32_t *s) {
  P12_00bdfa40 = s[0];
  MenuOptBDFA44 = s[1]; P14_00bdfa44 = s[1]; P62_BusyA = s[1]; G00BDFA44 = s[1]; P16_FlagD = s[1];
  MenuOptBDFA48 = s[2]; P62_BusyB = s[2]; G00BDFA48 = s[2];
  MenuOptBDFA4C = s[3]; P62_BusyC = s[3]; G00BDFA4C = s[3];
  MenuOptBDFA50 = s[4]; P62_BusyD = s[4]; G00BDFA50 = s[4];
  MenuOptBDFA54 = s[5]; G00BDFA54 = s[5];
  MenuOptBDFA58 = s[6]; P14_00bdfa58 = s[6]; P62_BusyE = s[6]; G00BDFA58 = s[6]; P16_FlagC = s[6];
}
/* How a level ended: G005F7E54 (005f7e54), set by the pause/result menus. */
enum {
  LEVEL_END_QUIT     = 2,   /* back to the front end */
  LEVEL_END_RESTART  = 3,   /* play the level again */
  LEVEL_END_REPLAY   = 4,   /* 4 / 5: save the TEMP replay and watch it (GameMode 4 / 5) */
  LEVEL_END_REPLAY2  = 5,
  LEVEL_END_TRAINING = 6    /* start the training script number G0054AA44 */
};

/* P136_GameLoop — Game.exe 0040c20b, cdecl.  Runs levels until the player leaves the game screen.
   In:  replay — non-zero to start in replay mode (GameMode 4) instead of normal play (GameMode 0).
   Saves the 7 option words of 00bdfa40 and restores them at the end,
   loads a level (P145_LevelLoad), runs P131_GameFrame until the level ends (G6_00B87E20 == 0),
   then acts on the end code (enum above).  Afterwards clears HUD/effect flags, deletes
   Scripts\Waypoint.tmp, reloads and saves config.dat.  Errors are written to debug.log. */
void P136_GameLoop(int32_t replay) {
  int32_t sv[7], done = 0;
  opt_save(sv);
  if (P68_ModeW != P19_ScrW || P68_ModeH != P19_ScrH) P55_SetScreen(P68_ModeW, P68_ModeH);
  Call00522323();
  GameMode = replay ? 4 : 0;
  P58_CfgLock = replay != 0;
  set_aa44(-1);
  while (done == 0) {
    set_e54(1);
    G6_00B87E20 = 1;
    set_a778(0);
    P145_LevelLoad();
    if (GameMode == 4 || GameMode == 5) P100_RecStop = 1;
    while (G6_00B87E20 != 0) {
      if (UiVar01251A70 != 0) P131_GameFrame();
      Call00522323();
    }
    P137_LevelEnd();
    GameMode = G005F7E54;
    switch (G005F7E54) {
    case LEVEL_END_QUIT: done = 1; break;
    case LEVEL_END_RESTART: GameMode = 0; break;
    case LEVEL_END_REPLAY: case LEVEL_END_REPLAY2:
      if (P64_ReplayStart(8, "TEMP") == 0) { P124_DebugLog("ERROR: Can't save replay"); done = 1; }
      else if (P47_PrepareTemp(8) == 0) { P124_DebugLog("ERROR: Can't load replay"); done = 1; }
      break;
    case LEVEL_END_TRAINING:
      if (G0054AA44 == -1) { P124_DebugLog("ERROR: Missing training script number"); done = 1; }
      else { GameMode = 0; set_e38(G0054AA44); }
      break;
    default: done = 1;
    }
  }
  P62_HudOff2 = 0;
  set_hud1(0);
  P14_00b87e84 = 0;
  P26_FxA = 0;
  P26_FxC = 0;
  g_remove("Scripts\\Waypoint.tmp");
  opt_restore(sv);
  P58_CfgLock = 0;
  P133_LoadConfig();
  P58_SaveConfig();
}

/* ---- 0040bf50 ---- */
int32_t P136_FrontInit(void) {
  static const float id[9] = { 1, 0, 0, 0, 1, 0, 0, 0, 1 };
  memcpy(P44_ViewMatT, id, sizeof id);
  P44_CamX = 0; P59_VX = 0; P44_CamY = 0; P59_VY = 0; P44_CamZ = 0; P59_VZ = 0;
  PushVec3_00523C99(0, 0, 0);
  P57_LoadScores();
  P133_LoadConfig();
  if (P19_ScrW != 0x280 || P19_ScrH != 0x1e0) P55_SetScreen(0x280, 0x1e0);
  P54_ClearSwap(4);
  if (P117_ClipFn) P117_ClipFn(0, 0x30, 0x280, 0x1b0);
  if (P100_LfbFormat() == 0) P30_FatalError("Failed to allocate display");
  G6_00B87EFC = 1;
  P56_F7E58 = 1;
  if (P137_LoadTsd("DATA\\FRONTEND.TSD") == 0) return 0;
  P125_BlendTable(P136_TsdPalB, P100_Pal32, 0x71, 0xff);
  P125_BlendTable(P136_TsdPalA, P136_Pal16, 0x71, 0xff);
  _Static_assert(sizeof(P101_PalLfb) == 0x400 && sizeof(P136_Pal16) == 0x400, "pal16");
  memcpy(P101_PalLfb, P136_Pal16, sizeof(P101_PalLfb));   /* 00407c27: 0x400 байт 01271680 → 01271a80 */
  P122_FontIcons(re_addr("F1_"), 0, -3, 8, 2);
  P122_FontIcons(re_addr("F2_"), 1, -2, 8, 2);
  P122_FontIcons(re_addr("F3_"), 2, -2, 6, 2);
  P122_FontIcons(re_addr("F4_"), 3, -2, 6, 2);
  P56_AA30 = 0;
  P45_Busy = 0;
  P48_ResetAll();
  P77_LoadBank("TITLE.DSS", 0);
  SoundSetVolB0052360D(0);
  if (Q00B87E90 != 0) { P25_InitCDAudio(); P25_PlayCDTrack(2); }
  P21_FrameTicks();
  P12_005f7e60 = 1;
  return 1;
}

/* ---- 00501770 ---- */
static const char *const k_maps[7] = { "MIAMI_00.MAP", "FRISCO_00.MAP", "LA_00.MAP", "NY_00.MAP", "LEVEL4.MAP", "LEVEL5.MAPLEVEL6.MAP", NULL };
static const int32_t k_rect[7][4] = { { 163, 172, 957, 661 }, { 134, 288, 1066, 994 }, { 175, 401, 784, 734 }, { 142, 190, 831, 645 },
                                      { -1, -1, -1, -1 }, { -1, -1, -1, -1 }, { -1, -1, -1, -1 } };
static void map_none(void) { S_00C808A0 = 0; P57_ScrW = 0; P136_MapScroll = 0; P109_C8089C = 0; }
static uint32_t rd32(const uint8_t *p) { uint32_t v; memcpy(&v, p, 4); return v; }
void P136_OverlayMap(void) {
  int32_t city = D_00b87e30;
  const char *nm = (city >= 0 && city < 7) ? k_maps[city] : NULL;
  void *f;
  uint8_t hdr[0xe], inf[0x28];
  if (P99_C80880 != NULL) { P98_DebugFree(P99_C80880); P99_C80880 = NULL; }
  if (nm == NULL) { P99_C80880 = NULL; map_none(); return; }
  f = P136_MapName[0] == 0 ? g_fopen(nm, "rb") : g_fopen(P136_MapName, "rb");
  if (f == NULL) map_none();
  else {
    int32_t w, h, bpp;
    P27_ReadChunked(hdr, 0xe, 1, f);
    P27_ReadChunked(inf, 0x28, 1, f);
    P27_ReadChunked(P136_MapPal, 4, 0x100, f);
    P136_MapPalOn = 1;
    P136_MapPal[0] = 0; P136_MapPal[1] = 0; P136_MapPal[2] = 0;
    w = (int32_t)rd32(inf + 4); h = (int32_t)rd32(inf + 8); bpp = inf[0xe] | inf[0xf] << 8;
    P57_ScrW = w; S_00C808A0 = h; P109_C8089C = 1; P136_MapScroll = 0;
    if (P100_Radar16 == 0) {
      P99_C80880 = P98_DebugMalloc(w * h, "D:\\Driver\\Game\\overlay.c", 0x1d0);
      if (P99_C80880 == NULL || bpp != 8) map_none();
      else P27_ReadChunked(P99_C80880, S_00C808A0, P57_ScrW, f);
    } else {
      int ok = 0;
      uint8_t *tmp;
      if (bpp == 8 && (P99_C80880 = P98_DebugMalloc(w * h * 2, "D:\\Driver\\Game\\overlay.c", 0x1a6)) != NULL &&
          (tmp = (uint8_t *)P98_DebugMalloc(P57_ScrW * S_00C808A0, "D:\\Driver\\Game\\overlay.c", 0x1a9)) != NULL) {
        uint16_t lut[256];
        uint16_t *dst = (uint16_t *)P99_C80880;
        const uint32_t *gi = P55_GlideInfo;
        P27_ReadChunked(tmp, S_00C808A0, P57_ScrW, f);
        for (int i = 0; i < 0x100; i++) {
          int32_t r = P136_MapPal[i * 4 + 2] >> (gi[0] & 0x1f), g = P136_MapPal[i * 4 + 1] >> (gi[2] & 0x1f), b = P136_MapPal[i * 4] >> (gi[4] & 0x1f);
          lut[i] = (uint16_t)(r << (gi[1] & 0x1f) | g << (gi[3] & 0x1f) | b << (gi[5] & 0x1f));
        }
        for (int32_t y = 0; y < S_00C808A0; y++)
          for (int32_t x = 0; x < P57_ScrW; x++) dst[y * P57_ScrW + x] = lut[tmp[y * P57_ScrW + x]];
        P98_DebugFree(tmp);
        ok = 1;
      }
      if (!ok) map_none();
    }
    g_fclose(f);
  }
  if (k_rect[city][0] == -1) { P94_MapX0 = 0; P94_MapY0 = 0; P94_MapW = P57_ScrW; P94_MapH = S_00C808A0; }
  else {
    P94_MapX0 = k_rect[city][0]; P94_MapY0 = k_rect[city][1];
    P94_MapW = k_rect[city][2] - k_rect[city][0]; P94_MapH = k_rect[city][3] - k_rect[city][1];
  }
}
