/* ported120.c — car effects (debris, exhaust smoke, sparks), lit objects, script table reset, debug info,
   an integer parser for scripts, cone recording and the mode-specific HUD texts (English overview;
   original notes follow).  All cdecl. */
/* v1.65: ported120 — восстановлено из Game.exe. Все функции cdecl (ret без операнда; work/rets.py).
   004af93c — объект B с затенением по счётчику повторов P68_Rep_ (ключ — адрес объекта) и источником света AddEntry_00426ABC;
   004cd875 — сброс таблицы записей скрипта (100 номеров, значок SNOW → G00D17B1C, P26_FxC);
   004ad6f5 — до 20 обломков у машины i (пул P95_ObjA, PoolPop004AC6D0, случайный сдвиг, P44_XformT);
   004afe3c — дым из выхлопа машины i (точка модели +0xb0, P118_SkidFx тип 2, искры игрока P96_SpawnSpark);
   004b00ad — искры двух точек модели +0xd0 машины i (таймеры 0110b040/011171c0/0110e2e0);
   004f60b7 — отладочная информация (позиция, курс, скорость игрока, пешеходы, конусы) через P96_LogLine;
   004a4d84 — разбор целого (или имени модели при mode 4) для P68_CamI0..3;
   004fbeb2 — запись конусов в файл Q00C812F0 (клавиши 00d04b3f/00d04b40);
   005032ce — HUD времени/счёта по режиму игры 01271060 (строки P97_StrAddr, sprintf → P70_ShadowText). */
#include "../platform/plat.h"
#include "ported120.h"
#include "cartab.h"
#include "globalsets.h"
#include "uihandlers3.h"
#include "unported.h"
#include "crt.h"
#include "ported6.h"
#include "ported5.h"
#include "ported7.h"
#include "ported11.h"
#include "ported13.h"
#include "ported14.h"
#include "ported15.h"
#include "ported19.h"
#include "ported26.h"
#include "ported34.h"
#include "ported43.h"
#include "ported44.h"
#include "ported56.h"
#include "ported62.h"
#include "ported65.h"
#include "ported68.h"
#include "ported69.h"
#include "ported70.h"
#include "ported71.h"
#include "ported93.h"
#include "ported94.h"
#include "ported95.h"
#include "ported96.h"
#include "ported97.h"
#include "ported98.h"
#include "ported100.h"
#include "ported101.h"
#include "ported118.h"
#include "reptr.h"
#include <stdio.h>
#include <string.h>

#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P120_ScrA")
#undef P120_ScrA
#pragma push_macro("P120_ScrA") /*gvi*/
#undef P120_ScrA /*gvi*/
int32_t P120_ScrA;
#pragma pop_macro("P120_ScrA") /*gvi*/
#pragma pop_macro("P120_ScrA")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P120_ScrB")
#undef P120_ScrB
#pragma push_macro("P120_ScrB") /*gvi*/
#undef P120_ScrB /*gvi*/
int32_t P120_ScrB;
#pragma pop_macro("P120_ScrB") /*gvi*/
#pragma pop_macro("P120_ScrB")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P120_ScrC")
#undef P120_ScrC
#pragma push_macro("P120_ScrC") /*gvi*/
#undef P120_ScrC /*gvi*/
int32_t P120_ScrC;
#pragma pop_macro("P120_ScrC") /*gvi*/
#pragma pop_macro("P120_ScrC")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P120_ScrD")
#undef P120_ScrD
#pragma push_macro("P120_ScrD") /*gvi*/
#undef P120_ScrD /*gvi*/
int32_t P120_ScrD;
#pragma pop_macro("P120_ScrD") /*gvi*/
#pragma pop_macro("P120_ScrD")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P120_ScrE")
#undef P120_ScrE
#pragma push_macro("P120_ScrE") /*gvi*/
#undef P120_ScrE /*gvi*/
int32_t P120_ScrE;
#pragma pop_macro("P120_ScrE") /*gvi*/
#pragma pop_macro("P120_ScrE")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P120_ScrSeed")
#undef P120_ScrSeed
#pragma push_macro("P120_ScrSeed") /*gvi*/
#undef P120_ScrSeed /*gvi*/
int32_t P120_ScrSeed;
#pragma pop_macro("P120_ScrSeed") /*gvi*/
#pragma pop_macro("P120_ScrSeed")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P120_DbgOn")
#undef P120_DbgOn
#pragma push_macro("P120_DbgOn") /*gvi*/
#undef P120_DbgOn /*gvi*/
int32_t P120_DbgOn;
#pragma pop_macro("P120_DbgOn") /*gvi*/
#pragma pop_macro("P120_DbgOn")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P120_ConeN")
#undef P120_ConeN
#pragma push_macro("P120_ConeN") /*gvi*/
#undef P120_ConeN /*gvi*/
int32_t P120_ConeN;
#pragma pop_macro("P120_ConeN") /*gvi*/
#pragma pop_macro("P120_ConeN")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P120_ConeTick")
#undef P120_ConeTick
#pragma push_macro("P120_ConeTick") /*gvi*/
#undef P120_ConeTick /*gvi*/
uint16_t P120_ConeTick;
#pragma pop_macro("P120_ConeTick") /*gvi*/
#pragma pop_macro("P120_ConeTick")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P120_HudA")
#undef P120_HudA
#pragma push_macro("P120_HudA") /*gvi*/
#undef P120_HudA /*gvi*/
int32_t P120_HudA;
#pragma pop_macro("P120_HudA") /*gvi*/
#pragma pop_macro("P120_HudA")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P120_HudB")
#undef P120_HudB
#pragma push_macro("P120_HudB") /*gvi*/
#undef P120_HudB /*gvi*/
int32_t P120_HudB;
#pragma pop_macro("P120_HudB") /*gvi*/
#pragma pop_macro("P120_HudB")
#endif

#define P120_HudC   (*(int32_t *)&P56_Blk84[(0x00c8110c - 0x00c810c0) / 4])    /* 00c8110c — внутри P56_Blk84 */
#define P120_HudPtr (*(uint32_t *)&P56_Blk84[(0x00c812b8 - 0x00c810c0) / 4])   /* 00c812b8 — uint32-адрес пары int32 */

#include "memrw.h"
#include "carfields.h"
#define CAR_HEADING_I16 0xea   /* int16 heading inside CAR_ANG (carfields.h: +0xea = heading as int16) */

/* wr16 / wrf — local helpers: unaligned int16 / float writes. */
static void wr16(uint8_t *p, int16_t v) { memcpy(p, &v, 2); }
static void wrf(uint8_t *p, float v) { memcpy(p, &v, 4); }

/* carp — local helper: car record i (native: out-of-range i maps to the spare last record). */
static uint8_t *carp(int32_t i) {
#ifndef RE_HOOK_BUILD
  if (i < 0 || i >= P99_CARS_N) i = P99_CARS_N - 1;
#endif
  return (uint8_t *)&P99_Cars[i];
}
/* carmodel — local helper: per-model record m of the table 00d0cc60 (0x16c bytes each; native: zeros if out of range). */
static const uint8_t *carmodel(uint32_t m) {   /* 00d0cc60 + m*0x16c */
#ifndef RE_HOOK_BUILD
  static const uint8_t zero[0x16c];
  if ((m + 1) * 0x16c > sizeof S_00D0CC60) return zero;
#endif
  return &S_00D0CC60[m * 0x16c];
}
/* set_mat — local helper: makes car i's float matrix (01135060[i]) the current transform P44_MatPtr. */
static void set_mat(int32_t i) {   /* 00bdc28c = &01135060[i] (P44_MatPtr / P11_00bdc28c) */
#ifndef RE_HOOK_BUILD
  if (i < 0 || i >= 65) i = 0;
#endif
  P44_MatPtr = (float *)(void *)P98_CarMat[i];
}

/* ---- 004af93c ---- */
/* P120_ObjBShade — Game.exe 004af93c.  At night (00b87e84) adds a "B" object with a light: brightness 255,
   reduced by 64 per repeat of the same object in the repeat table P68_Rep_ plus random flicker (objects
   repeated more than twice are skipped), and a point light of radius 2000 at the object.
   TODO(RE): unsure which objects are "B" objects (street lights?). */
void P120_ObjBShade(uint8_t *obj, float x, float y, float z, int16_t kind, int16_t b) {
  int16_t shade = 0xff;
  if (P14_00b87e84 == 0) return;
  int32_t key = (int32_t)re_addr(obj);
  for (int k = 0; k < 4; k++) {
    if (P68_Rep_[k].key == key) {
      if (P68_Rep_[k].cnt > 2) return;
      if (G6_00B5A778 == 0) shade = (int16_t)(shade - (int16_t)(P68_Rep_[k].cnt * 0x40 + (N14_Rand() & 0x7f)));
      else shade = (int16_t)(0xff - P68_Rep_[k].cnt * 0x40);
      break;
    }
  }
  float pos[3];
  pos[0] = rdf(obj + 8); pos[1] = y + rdf(obj + 0xc); pos[2] = rdf(obj + 0x10);
  P101_AddObjB(obj, x, y, z, kind, b, shade);
  AddEntry_00426ABC((const uint32_t *)(void *)pos, 2000, shade, shade, shade);
}

/* ---- 004cd875 ---- */
/* P120_ScriptReset — Game.exe 004cd875.  Resets the script record table p (100 numbered entries, 0x34 bytes
   each from +0x1c4), the script counters and a random seed; looks up the "SNOW" icon (no icon -> snow off)
   and shrinks its UV rectangle by one texel on each side (avoids bleeding). */
void P120_ScriptReset(int32_t *p) {
  P120_ScrC = 0; P120_ScrB = 0; P120_ScrA = 0; P120_ScrD = 0; P120_ScrE = 0;
  P120_ScrSeed = (int32_t)(N14_Rand() & 0xff);
  for (int32_t i = 0; i < 100; i++) {
    p[i + 1] = i;
    wr16((uint8_t *)p + i * 0x34 + 0x1c6, (int16_t)i);
  }
  p[0] = 0;
  uint8_t *ic = P93_FindIcon("SNOW");
  G00D17B1C = (int32_t)re_addr(ic);
  if (ic == NULL) { P26_FxC = 0; return; }
  ic[9]++; ic[10]++;
  ic[0xb] = (uint8_t)(ic[0xb] + ic[9] - 1);
  ic[0xc] = (uint8_t)(ic[0xc] + ic[10] - 1);
}

/* ---- 004ad6f5 ---- */
/* P120_CarDebris — Game.exe 004ad6f5.  Spawns up to 20 debris objects (pool P95_ObjA, see P123_ObjAFall)
   scattered randomly around car i at height h.  Native: y of the random offset is 0 (uninitialised in
   Game.exe), out-of-pool slots are skipped. */
void P120_CarDebris(int32_t i, int32_t height) {
  set_mat(i);
  const uint8_t *car = carp(i);
  int32_t left = 0x14;
  while (left != 0) {
    left--;
    int32_t slot = PoolPop004AC6D0();
    if (slot < 0) break;
#ifndef RE_HOOK_BUILD
    if (slot >= 200) continue;
#endif
    float pos[3];
    pos[0] = (float)(int32_t)((N14_Rand() & 0x1ff) - 0x100);
    pos[2] = (float)(int32_t)((N14_Rand() & 0x3ff) - 0x200);
    pos[1] = 0.0f;   /* в оригинале local_18 до XformT не задан (мусор стека) */
    P44_XformT(pos);
    pos[0] += (float)rd32(car + CAR_POS_X);
    pos[1] = (float)-height;
    pos[2] += (float)rd32(car + CAR_POS_Z);
    uint8_t *obj = &P95_ObjA[slot * 0x78];
    wrf(obj, pos[0]); wrf(obj + 4, pos[1]); wrf(obj + 8, pos[2]);
    wr32(obj + 0xc, 0);   /* local_10 — мусор стека в оригинале */
    wr32(obj + 0x68, 0x8002);
    wr32(obj + 0x58, 200);
    wrf(obj + 0x5c, (float)((N14_Rand() & 0xf) + 10));
    wr32(obj + 0x50, 100); wr32(obj + 0x54, 400); wr32(obj + 0x60, 10);
    wr16(obj + 0x64, 100);
  }
}

/* ---- 004afe3c ---- */
/* P120_CarSmoke — Game.exe 004afe3c.  Exhaust smoke for car i at the model's exhaust point (+0xb0, moved by
   damage zone 3), blowing backwards (5 units along the car's z), at view distance `dist`; also sparks
   for the player when P62_BusyA is set.  Skipped while paused. */
void P120_CarSmoke(int32_t i, int32_t dist) {
  if (G6_00B5A778 != 0) return;
  const uint8_t *car = carp(i);
  const uint8_t *model = carmodel(car[CAR_MODEL]);
  float pos[4], vel[4];
  pos[0] = rdf(model + 0xb0); pos[1] = rdf(model + 0xb4);
  pos[2] = rdf(model + 0xb8) - (float)(rd32(car + CAR_DAMAGE + 3 * 4) >> 6);
  pos[3] = rdf(model + 0xbc);
  set_mat(i);
  P44_XformT(pos);
  pos[0] += (float)rd32(car + CAR_POS_X);
  pos[1] -= (float)rd32(car + CAR_POS_Y);
  pos[2] += (float)rd32(car + CAR_POS_Z);
  vel[0] = 0.0f; vel[1] = 0.0f; vel[2] = 5.0f; vel[3] = 0.0f;
  P44_XformT(vel);
  P118_SkidFx(pos, 0x14, 0x32, 2, dist, vel, 1);
  if (i == 0 && P62_BusyA != 0) P96_SpawnSpark(pos, 0x32, 200, (int16_t)((N14_Rand() & 3) + 8));
}

/* ---- 004b00ad ---- */
/* P120_CarSparks — Game.exe 004b00ad.  Sparks at the two model points +0xd0 of car i, each with its own
   random timer, size and x jitter (tables 0110b040 / 011171c0 / 0110e2e0).  Skipped while paused.
   TODO(RE): unsure what the model point +0xd0 is (exhaust again, for backfire?). */
void P120_CarSparks(int32_t i) {
  if (G6_00B5A778 != 0) return;
#ifndef RE_HOOK_BUILD
  if (i < 0 || i >= 0x41) return;
#endif
  const uint8_t *car = carp(i);
  const uint8_t *model = carmodel(car[CAR_MODEL]);
  for (int32_t k = 1; k >= 0; k--) {
    uint8_t *timer = &A_0110B040[i * 8 + k * 4], *size = &A_011171C0[i * 8 + k * 4], *jitter = &A_0110E2E0[i * 8 + k * 4];
    float pos[4];
    pos[1] = rdf(model + 0xd4); pos[2] = rdf(model + 0xd8); pos[3] = rdf(model + 0xdc);
    pos[0] = rdf(model + 0xd0) + (float)rd32(jitter);
    wr32(timer, rd32(timer) - 1);
    if (rd32(timer) < 1) {
      wr32(timer, (int32_t)(N14_Rand() & 7));
      wr32(size, (int32_t)((N14_Rand() & 3) + 8));
      wr32(jitter, (int32_t)((N14_Rand() & 0x3f) - 0x20));
    }
    set_mat(i);
    P44_XformT(pos);
    pos[0] += (float)rd32(car + CAR_POS_X);
    pos[1] -= (float)rd32(car + CAR_POS_Y);
    pos[2] += (float)rd32(car + CAR_POS_Z);
    P96_SpawnSpark(pos, 0x32, 200, (int16_t)rd32(size));
  }
}

/* ---- 004f60b7 ---- */
/* P120_DebugInfo — Game.exe 004f60b7.  On-screen debug block: player position, heading, speed, active
   pedestrians and recorded cones (when 00b87e7c is clear and debug info is on). */
void P120_DebugInfo(void) {
  char b[64];
  if (P11_00b87e7c != 0 || P120_DbgOn == 0) return;
  const uint8_t *car = carp(0);
  int32_t y = P19_ScrH / 8 - 9;
  CursorSet004D94B7(0, y);
  P96_LogLine("--- Debug Information ---");
  snprintf(b, sizeof b, "Player car X position = %d", rd32(car + CAR_POS_X)); P96_LogLine(b);
  snprintf(b, sizeof b, "Player car Y position = %d", rd32(car + CAR_POS_Y)); P96_LogLine(b);
  snprintf(b, sizeof b, "Player car Z position = %d", rd32(car + CAR_POS_Z)); P96_LogLine(b);
  int16_t rot_y; memcpy(&rot_y, car + CAR_HEADING_I16, 2);
  snprintf(b, sizeof b, "Player car Y rotation = %d (Curr %d)", (int)rot_y, G00BDF984); P96_LogLine(b);
  snprintf(b, sizeof b, "Player car speed = %d", rd32(car + CAR_FWD_SPEED)); P96_LogLine(b);
  snprintf(b, sizeof b, "Number of pedestrians active = %d/%d", P43_FreeCnt, P13_005759a4); P96_LogLine(b);
  if (P120_ConeN > 0) { snprintf(b, sizeof b, "Number of cones recorded = %d", P120_ConeN); P96_LogLine(b); }
}

/* ---- 004a4d84 ---- */
/* P120_ParseCamInt — Game.exe 004a4d84.  Parses an optionally negative unsigned integer (or, with mode 4, a
   model name) at *pp into P68_CamI0..3 (`which`), advancing *pp.  Returns 1, or 0 after reporting an error. */
int32_t P120_ParseCamInt(char **pp, int32_t which, int32_t mode) {
  char neg = **pp;
  if (neg == '-') (*pp)++;
  uint32_t u = 0;
  uint16_t val;
  int32_t nconv = g_sscanf(*pp, "%u", &u);
  val = (uint16_t)u;
  P15_SkipInteger(pp);
  if ((nconv == 0 || nconv == -1) && (int16_t)mode == 4) {
    uint8_t name[256];
    *pp = (char *)P94_ReadIdent((uint8_t *)*pp, name);
    if (P62_ModelLookup((const char *)name, &val) == 0) {
      P26_ErrorInLine("Model number must be an unsigned integer or name");
      return 0;
    }
  } else if (nconv == 0 || nconv == -1) {
    P26_ErrorInLine("Expecting integer value.");
    return 0;
  }
  if (neg == '-') val = (uint16_t)-val;
  switch (which) {
  case 0: P68_CamI0 = val; break;
  case 1: P68_CamI1 = val; break;
  case 2: P68_CamI2 = val; break;
  case 3: P68_CamI3 = val; break;
  }
  return 1;
}

/* ---- 004fbeb2 ---- */
/* P120_ConeRec — Game.exe 004fbeb2.  Development tool: keys 0x3f / 0x40 start / stop recording; while on, every
   P95_B87E40+1 ticks writes the player's x, road height, z to the cone file (max 100 cones).
   Native: the file is never opened, only the count advances. */
void P120_ConeRec(void) {
  if (P34_Keys[0x3f] != 0) P95_B87ED8 = 1;
  if (P34_Keys[0x40] != 0) P95_B87ED8 = 0;
  if (P95_B87ED8 == 0 || P120_ConeN == 100) return;
  uint16_t t = (uint16_t)(P120_ConeTick + 1);
  if (P120_ConeTick == 0) {
    const uint8_t *car = carp(0);
    int32_t pos[3] = { rd32(car + CAR_POS_X), 0, rd32(car + CAR_POS_Z) };
    P120_ConeTick = t;
    int32_t height = -P100_RoadHeight(pos);
#ifdef RE_HOOK_BUILD
    void *f = (void *)(uintptr_t)(uint32_t)Q00C812F0;
#else
    void *f = NULL;   /* в native файл 00c812f0 не открывается (Call0052ADB0 — заглушка) */
#endif
    if (f != NULL) { g_fwrite(&pos[0], 1, 4, f); g_fwrite(&height, 1, 4, f); g_fwrite(&pos[2], 1, 4, f); }
    P120_ConeN++;
  } else {
    P120_ConeTick = t;
    if (P95_B87E40 < (int32_t)t) P120_ConeTick = 0;
  }
}

/* ---- 005032ce ---- */
static char p120_buf[32];
/* S / T / tab / hms — local helpers of the HUD texts: string address idx, shadowed text, record table at a
   Game.exe address, and "%02d:%02d:%02d" of a record when it is filled (+st == 8). */
static uint32_t S(int32_t idx) { return P97_StrAddr[idx]; }   /* адрес строки 00c55820 + idx*4 */
static void T(int32_t x, int32_t y, uint32_t s, int32_t a, int32_t f, uint8_t r, uint8_t g, uint8_t b) { P70_ShadowText(x, y, s, a, (uint32_t)f, r, g, b); }
#define BUF (re_addr(p120_buf))   /* v2.04: re_addr вместо усечения указателя */
#define PR(...) snprintf(p120_buf, sizeof p120_buf, __VA_ARGS__)
static const uint8_t *tab(int32_t a) { return (const uint8_t *)re_ptr((uint32_t)a); }
static int hms(const uint8_t *t, uint32_t st, uint32_t o) { return t != NULL && rd32(t + st) == 8 && (PR("%02d:%02d:%02d", rd32(t + o + 8), rd32(t + o + 4), rd32(t + o)), 1); }
#ifndef RE_HOOK_BUILD
static void P120_HudTimesBody(void);
#endif
/* P120_HudTimes — Game.exe 005032ce.  Native wrapper: anchors these HUD texts to the right edge (Hor+), then
   draws them (P120_HudTimesBody); the hook build has the body directly. */
void P120_HudTimes(void) {
#ifndef RE_HOOK_BUILD
  plat_hud_anchor(1);   /* v2.15: счётчики/время режимов (x 470..570 в 640-кадре) — к правому краю */
  P120_HudTimesBody();
  plat_hud_anchor(0);
}
/* P120_HudTimesBody — body of 005032ce.  Draws the counters / times of the current game mode (01271060):
   1 and 2 — count / total and best values, 3 — best time, 6 / 0xb — count, current and best times plus
   two more records on the left, 7 — money ("$%d") and the best.
   Modes: 1 Trail Blazer, 2 Cross Town Checkpoint, 3 Survival, 7 Carnage, 0xb Dirt Track (P141_HsSetup);
   6 = Dirt Track Practice (menu 0054a870 "Practice"; 0xb = "Time Trial"). */
static void P120_HudTimesBody(void) {
#endif
  const uint8_t *ta = tab(P71_Tab2A40);
  switch (MenuMode1271060) {
  case 1:
    T(0x1d6, 10, S(0xd7), 0, 0, 0xff, 0xff, 0x80);
    PR("%d", P120_HudC); T(0x23a, 0x19, BUF, 1, 2, 0xff, 0xff, 0xff);
    PR("/%d", G6_00C81108); T(0x23a, 0x32, BUF, 0, 0, 0xff, 0xff, 0xff);
    T(0x1d6, 0x50, S(0xd9), 0, 0, 0xff, 0xff, 0x80);
    PR("%s:", P65_STR(0xd8)); T(0x1d6, 0x69, BUF, 0, 0, 0xff, 0xff, 0x80);
    PR("-");
    if (ta != NULL && rd32(ta + 0x18) == 8) PR("%d", rd32(ta + 0x10));
    T(0x21c, 0x69, BUF, 0, 0, 0xff, 0xff, 0x80);
    PR("%s:", P65_STR(0xda)); T(0x1d6, 0x82, BUF, 0, 0, 0xff, 0xff, 0x80);
    PR("--:--:--"); hms(ta, 0x18, 0x20);
    T(0x21c, 0x82, BUF, 0, 0, 0xff, 0xff, 0x80);
    break;
  case 2: {
    const int32_t *pr = (const int32_t *)re_ptr(P120_HudPtr);
    T(0x226, 10, S(0xde), 0, 1, 0xff, 0xff, 0x80);
    PR("%d", pr != NULL ? pr[1] : 0); T(0x226, 0x1e, BUF, 1, 2, 0xff, 0xff, 0xff);
    PR("/%d", pr != NULL ? pr[0] : 0); T(0x226, 0x37, BUF, 0, 0, 0xff, 0xff, 0xff);
    PR("%s: --:--:--", P65_STR(0xd9));
    if (ta != NULL && rd32(ta + 0x18) == 8) PR("%s: %02d:%02d:%02d", P65_STR(0xd9), rd32(ta + 0x28), rd32(ta + 0x24), rd32(ta + 0x20));
    T(0x226, 0x50, BUF, 0, 1, 0xff, 0xff, 0x80);
    break; }
  case 3:
    PR("%s: --:--:--", P65_STR(0xd9));
    if (ta != NULL && rd32(ta + 0x18) == 8) PR("%s: %02d:%02d:%02d", P65_STR(0xd9), rd32(ta + 0x28), rd32(ta + 0x24), rd32(ta + 0x20));
    T(0x1d6, 10, BUF, 0, 0, 0xff, 0xff, 0x80);
    break;
  case 6: case 0xb: {
    T(0x1d6, 10, S(0xdf), 0, 0, 0xff, 0xff, 0x80);
    PR("%d", P120_HudB); T(0x226, 0x1e, BUF, 1, 2, 0xff, 0xff, 0xff);
    if (MenuMode1271060 == 6) PR("/%c", 0x7f); else PR("/%d", P120_HudA);
    T(0x226, 0x37, BUF, 0, 0, 0xff, 0xff, 0xff);
    PR("%s:", P65_STR(0xdb)); T(0x1d6, 0x50, BUF, 0, 0, 0xff, 0xff, 0x80);
    if (P71_V2A14 == 8) PR("%02d:%02d:%02d", P71_V2A24, P71_V2A20, P71_V2A1C); else PR("--:--:--");
    T(0x21c, 0x50, BUF, 0, 0, 0xff, 0xff, 0x80);
    PR("%s:", P65_STR(0xd9)); T(0x1d6, 0x69, BUF, 0, 0, 0xff, 0xff, 0x80);
    PR("--:--:--"); hms(tab((int32_t)P71_Ptr2A08), 4, 0xc);
    T(0x21c, 0x69, BUF, 0, 0, 0xff, 0xff, 0x80);
    T(0x10, 0x37, S(0xd6), 0, 0, 0xff, 0xff, 0x80);
    PR("%s:", P65_STR(0xdc)); T(0x10, 0x50, BUF, 0, 0, 0xff, 0xff, 0x80);
    PR("--:--:--"); hms(tab(P71_Tab974), 0x18, 0x20);
    T(0x56, 0x50, BUF, 0, 0, 0xff, 0xff, 0x80);
    PR("%s:", P65_STR(0xdd)); T(0x10, 0x69, BUF, 0, 0, 0xff, 0xff, 0x80);
    PR("--:--:--"); hms(ta, 0x18, 0x20);
    T(0x56, 0x69, BUF, 0, 0, 0xff, 0xff, 0x80);
    break; }
  case 7:
    PR("%s:", P65_STR(0xe1)); T(0x217, 0x50, BUF, 0, 2, 0xff, 0xff, 0x80);
    PR("$%d", P69_Score); T(0x221, 0x50, BUF, 0, 0, 0xff, 0xff, 0xff);
    T(0x10, 0x37, S(0xd6), 0, 0, 0xff, 0xff, 0x80);
    PR("%s:", P65_STR(0xe1)); T(0x10, 0x50, BUF, 0, 0, 0xff, 0xff, 0x80);
    PR("$-");
    if (ta != NULL && rd32(ta + 0x18) == 8) PR("$%d", rd32(ta + 0x10));
    T(0x78, 0x50, BUF, 0, 0, 0xff, 0xff, 0x80);
    break;
  }
}
