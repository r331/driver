/* ported130.c — script weather effects: snow, rain and lightning (English overview; Russian notes follow).
   Particles live in the record pool of G2_ScriptStack: st[0] = number of live records, records of 0x34 bytes
   (13 dwords) from dword 0x65; free record numbers are popped/pushed with ScriptStackPop/Push.
   Spawning puts particles in a box in front of the camera (offset transformed by the view matrix); the step
   functions move them, project them to the screen and return a particle to the pool when it leaves the
   depth range or falls below the limit.  All functions cdecl, no arguments. */
/* v1.75: ported130 — эффекты погоды скрипта (см. ported130.h).
   004cd994 — снег: камера вне модели (P128_ModelHit) → до 100 записей из стека (ScriptStackPop004CB9BA), случайный
     сдвиг ±0x400 / ±0x400 / −0x400..0x1c00 через P44_ViewMat (P44_Xform) + камера, округление через P11_00ba52d0.
   004cc008 — дождь: то же со сдвигом ±0x200, y = 0x200 − r, z −0x400..0xc00; точка внутри модели — запись назад
     (ScriptStackPush004CB9F2); этап +0x30 = 0. Четвёртый аргумент 004cd3fb в оригинале — мусор стека (не читается).
   004cadb5 — молния: внутри модели камера или игрок → свет только обычный; счётчик P14_00d17b28 (вспышка 0x1e кадров,
     Set560388(0x1e)), затем пауза (rand + 0x200) & 0x1ff; во время вспышки 1/8 — цвет P130_LampRGB + 0x60..0x7f
     (rand в порядке b, g, r — порядок аргументов cdecl) и половина — свет P80_Save*, иначе P80_Alt* (P19_Out*, P81_Light);
     по P14_00b87e84 — базовый цвет P98_LampColor.
   004cba1d — шаг дождя: y += 0x32 (выше 0x32 — запись назад), проекция по P44_ViewMatT, z вне [50, 1536) — назад,
     этап до 2, экран = (v × 1/w × P43_ScaleA + P43_Off) − 2^20, значок rand & 0x1f.
   004cdb25 — шаг снега: случайный ветер P120_ScrD/E раз в P120_ScrSeed кадров, плавно в P120_ScrB/A каждый 4-й кадр,
     y += 10, z вне [50, 4096) — назад. */
#include "ported130.h"
#include "ported11.h"
#include "ported12.h"
#include "ported14.h"
#include "ported19.h"
#include "ported43.h"
#include "ported44.h"
#include "ported62.h"
#include "ported80.h"
#include "ported81.h"
#include "ported95.h"
#include "ported98.h"
#include "ported120.h"
#include "ported128.h"
#include "ported16.h"
#include "ported99.h"
#include "ported121.h"
#include "cartab.h"
#include "smallfuncs2.h"
#include "uihandlers3.h"
#include "unported.h"
#include <math.h>

#ifndef RE_HOOK_BUILD
#pragma push_macro("P130_LampRGB") /*gvi*/
#undef P130_LampRGB /*gvi*/
p130_rgb_t P130_LampRGB = { 0x00, 0x80, 0x80 };   /* .data 0055fc8c */
#pragma pop_macro("P130_LampRGB") /*gvi*/
#endif

/* Particle record layout (dword indices unless noted). */
enum {
  PT_POOL_FIRST = 0x65,   /* first record = G2_ScriptStack + 0x65 dwords (+0x194 bytes) */
  PT_DWORDS     = 0xd,    /* record size 0x34 bytes */
  PT_MAX        = 100,
  PT_X = 0, PT_Y = 1, PT_Z = 2,      /* world position (integer) */
  PT_PREV_SX = 4, PT_PREV_SY = 5,    /* previous screen position (streak start for rain) */
  PT_SX = 8, PT_SY = 9,              /* screen position, minus the 2^20 float-to-int bias */
  PT_OOW = 10,                       /* 1/z (truncated to int) */
  PT_STAGE_B = 0x30,                 /* byte: frames since spawn, saturating at 2 (rain) */
  PT_ICON_B  = 0x31,                 /* byte: random sprite variant 0..31 */
  PT_INDEX_B = 0x32                  /* int16: the record's own number in the pool */
};

/* Round to int with the FPU's default rounding and keep the result in P11_00ba52d0, as the original's
   __ftol helper does. */
static int32_t rnd(float v) { P11_00ba52d0 = (int32_t)lrintf(v); return P11_00ba52d0; }

/* Address of particle record idx (native: NULL when the pool is missing or idx is out of range). */
static int32_t *rec_at(int32_t idx) {
  int32_t *st = G2_ScriptStack;
#ifndef RE_HOOK_BUILD
  if (st == NULL || idx < 0 || idx >= 100) return NULL;
#endif
  return st + PT_POOL_FIRST + idx * PT_DWORDS;
}

/* Stores the rounded position v and the record number idx into record r. */
static void put_xyz(int32_t *r, const float *v, int32_t idx) {
  r[0] = rnd(v[0]); r[1] = rnd(v[1]); r[2] = rnd(v[2]);
  *(int16_t *)(void *)((uint8_t *)r + PT_INDEX_B) = (int16_t)idx;
}

/* P130_SnowSpawn — Game.exe 004cd994.  Unless the camera is inside a model (P128_ModelHit, e.g. a tunnel)
   or P16_FlagA is set, takes up to 100 free records and places snowflakes at random offsets
   x, y in -0x400..0x3ff, z in -0x400..0x1bff in camera space (z = forward), transformed to world space. */
/* ---- 004cd994 ---- */
void P130_SnowSpawn(void) {
  if (P16_FlagA != 0) return;
  if (P128_ModelHit(P44_CamX, P44_CamY, P44_CamZ, P121_CamW) != 0) return;
  P44_MatPtr = (float *)P44_ViewMat;
  for (int32_t n = 100; n != 0; n--) {
    int32_t idx = ScriptStackPop004CB9BA();
    if (idx < 0) break;
    int32_t *r = rec_at(idx);
    float v[3];
    v[0] = (float)(int32_t)((N14_Rand() & 0x7ff) - 0x400);
    v[1] = (float)(int32_t)((N14_Rand() & 0x7ff) - 0x400);
    v[2] = (float)(int32_t)((N14_Rand() & 0x1fff) - 0x400);
    P44_Xform(v);
    v[0] += P44_CamX; v[1] += P44_CamY; v[2] += P44_CamZ;
#ifndef RE_HOOK_BUILD
    if (r == NULL) continue;
#endif
    put_xyz(r, v, idx);
  }
}

/* P130_RainSpawn — Game.exe 004cc008.  Like the snow spawn with a smaller box (x -0x200..0x1ff,
   y 0x200 - (0..0x3ff), z -0x400..0xbff); a drop that would start inside a model goes straight back to the
   pool.  Stage byte = 0.  (The original passes stack garbage as a 4th argument to 004cd3fb — not read.)
   TODO(RE): it pops with ScriptStackPop004CB982, snow with ...004CB9BA — difference unsure. */
/* ---- 004cc008 ---- */
void P130_RainSpawn(void) {
  if (P16_FlagA != 0) return;
  P44_MatPtr = (float *)P44_ViewMat;
  for (int32_t n = 100; n != 0; n--) {
    int32_t idx = ScriptStackPop004CB982();
    if (idx < 0) break;
    int32_t *r = rec_at(idx);
    float v[3];
    v[0] = (float)(int32_t)((N14_Rand() & 0x3ff) - 0x200);
    v[1] = (float)(int32_t)(0x200 - (N14_Rand() & 0x3ff));
    v[2] = (float)(int32_t)((N14_Rand() & 0xfff) - 0x400);
    P44_Xform(v);
    v[0] += P44_CamX; v[1] += P44_CamY; v[2] += P44_CamZ;
    if (P128_ModelHit(v[0], v[1], v[2], 0) == 0) {
#ifndef RE_HOOK_BUILD
      if (r == NULL) continue;
#endif
      put_xyz(r, v, idx);
      *((uint8_t *)r + PT_STAGE_B) = 0;
    } else {
      ScriptStackPush004CB9F2(idx);
    }
  }
}

/* Restores the normal scene light (P80_Alt* -> light outputs) and recomputes lighting. */
static void light_alt(void) {
  P19_OutA = P80_Alt0; P19_OutB = P80_Alt1; P19_OutC = P80_Alt2; P80_Dir3 = P80_Alt3; P19_Out68 = P80_AltW;
  P81_Light();
}

/* P130_Lightning — Game.exe 004cadb5.  Lightning state machine on P14_00d17afc (1 = storm flash period)
   and the frame counter P14_00d17b28:
   - quiet period: count down, then start a 0x1e-frame flash period (Set560388(0x1e) — TODO(RE): presumably
     the thunder sound);
   - flash period: on 1 frame in 8 (rand & 7 == 1) the lamp colour becomes P130_LampRGB + 0x60..0x7f per
     channel and, half the time, the bright light P80_Save* is applied; otherwise normal light;
     at its end a new quiet period of (rand + 0x200) & 0x1ff frames.
   With the camera or the player car inside a model only the normal light is used.  At night
   (P14_00b87e84) the base lamp colour is restored on frames without a flash.
   The three rand calls are in b, g, r order — the original evaluates cdecl arguments right to left. */
/* ---- 004cadb5 ---- */
void P130_Lightning(void) {
  int32_t base = 1;
  if (P16_FlagA != 0) return;
  float px = (float)P99_Cars[0].pos[0], py = (float)P99_Cars[0].pos[1], pz = (float)P99_Cars[0].pos[2];
  int32_t inside = (P128_ModelHit(P44_CamX, P44_CamY, P44_CamZ, P121_CamW) != 0 || P128_ModelHit(px, py, pz, 0) != 0);
  if (P14_00d17afc == 0) {
    if (P14_00d17b28 == 0) { P14_00d17afc = 1; P14_00d17b28 = 0x1e; Set560388(0x1e); }
    else P14_00d17b28--;
    return;
  }
  if (P14_00d17b28 == 0) {
    if (!inside) light_alt();
    P14_00d17afc = 0;
    P14_00d17b28 = (int32_t)((N14_Rand() + 0x200u) & 0x1ffu);
  } else {
    P14_00d17b28--;
    if (inside) light_alt();
    else if ((N14_Rand() & 7) == 1) {
      uint32_t b = (uint32_t)P130_LampRGB[2] + 0x60 + (N14_Rand() & 0x1f);
      uint32_t g = (uint32_t)P130_LampRGB[1] + 0x60 + (N14_Rand() & 0x1f);
      uint32_t r = (uint32_t)P130_LampRGB[0] + 0x60 + (N14_Rand() & 0x1f);
      P98_LampColor((uint8_t)r, (uint8_t)g, (uint8_t)b);
      base = 0;
      if (N14_Rand() & 1) {
        P19_OutA = P80_Save0; P19_OutB = P80_Save1; P19_OutC = P80_Save2; P80_Dir3 = P80_Save3; P19_Out68 = P80_SaveW;
        P81_Light();
      }
    } else light_alt();
  }
  if (base && P14_00b87e84 != 0) P98_LampColor(P130_LampRGB[0], P130_LampRGB[1], P130_LampRGB[2]);
}

/* общий шаг проекции частицы; 0 — запись возвращена в стек
   Projects particle r: camera-space depth outside [50, zfar) -> record back to the pool, return 0;
   else screen x/y (with the 2^20 bias subtracted) and 1/z are stored, return 1. */
static int32_t project(int32_t *r, float zfar) {
  float v[3] = { (float)r[0] - P44_CamX, (float)r[1] - P44_CamY, (float)r[2] - P44_CamZ };
  P44_Xform(v);
  if (v[2] < 50.0f || zfar <= v[2]) { ScriptStackPush004CB9F2((int32_t)*(int16_t *)(void *)((uint8_t *)r + PT_INDEX_B)); return 0; }
  long zi = lrintf(v[2]);
  float oow = 0.0f;
#ifndef RE_HOOK_BUILD
  if (zi >= 0 && zi < (long)(RE_OOW_N))
#endif
    oow = RE_OOW(zi);
  float k = P43_ScaleA * oow;
  r[PT_SX] = (int32_t)((v[0] * k + P43_OffX) - 1048576.0f);
  r[PT_SY] = (int32_t)((v[1] * k + P43_OffY) - 1048576.0f);
  r[PT_OOW] = (int32_t)oow;
  return 1;
}

/* P130_RainStep — Game.exe 004cba1d.  Moves every live drop down by 0x32 (y grows downward); a drop past
   y 0x32 (TODO(RE): what the 0x32 limit corresponds to is unsure) or outside depth [50, 1536) returns to the pool.
   Keeps the previous screen position in PT_PREV_SX/SY (the streak), projects with P44_ViewMatT, advances
   the stage byte up to 2 and picks a random sprite variant. */
/* ---- 004cba1d ---- */
void P130_RainStep(void) {
  int32_t *st = G2_ScriptStack;
  if (P16_FlagA != 0) return;
#ifndef RE_HOOK_BUILD
  if (st == NULL) return;
#endif
  if (st[0] == 0) return;
  P44_MatPtr = (float *)P44_ViewMatT;
  int32_t *r = st + PT_POOL_FIRST;
  for (int32_t n = st[0]; n != 0; n--, r += PT_DWORDS) {
    r[1] += 0x32;
    if (r[1] >= 0x33) { ScriptStackPush004CB9F2((int32_t)*(int16_t *)(void *)((uint8_t *)r + PT_INDEX_B)); continue; }
    float sx = (float)r[PT_SX], sy = (float)r[PT_SY];
    float v[3] = { (float)r[0] - P44_CamX, (float)r[1] - P44_CamY, (float)r[2] - P44_CamZ };
    P44_Xform(v);
    if (v[2] < 50.0f || 1536.0f <= v[2]) { ScriptStackPush004CB9F2((int32_t)*(int16_t *)(void *)((uint8_t *)r + PT_INDEX_B)); continue; }
    uint8_t *b = (uint8_t *)r;
    if (b[PT_STAGE_B] != 2) b[PT_STAGE_B]++;
    r[PT_PREV_SX] = rnd(sx); r[PT_PREV_SY] = rnd(sy);
    long zi = lrintf(v[2]);
    float oow = 0.0f;
#ifndef RE_HOOK_BUILD
    if (zi >= 0 && zi < (long)(RE_OOW_N))
#endif
      oow = RE_OOW(zi);
    float k = P43_ScaleA * oow;
    r[PT_SX] = (int32_t)((v[0] * k + P43_OffX) - 1048576.0f);
    r[PT_SY] = (int32_t)((v[1] * k + P43_OffY) - 1048576.0f);
    r[PT_OOW] = (int32_t)oow;
    b[PT_ICON_B] = (uint8_t)(N14_Rand() & 0x1f);
  }
}

/* P130_SnowStep — Game.exe 004cdb25.  Wind: every P120_ScrSeed (random 0..255) frames picks a new random
   target drift P120_ScrD/E in -8..7; every 4th frame the current drift P120_ScrB/A moves one step toward it.
   Each flake moves by the drift in x/z and 10 down in y; past y 0x32 or outside depth [50, 4096) it returns
   to the pool. */
/* ---- 004cdb25 ---- */
void P130_SnowStep(void) {
  if (P16_FlagA != 0) return;
  P120_ScrC++;
  if (P120_ScrSeed < P120_ScrC) {
    P120_ScrSeed = (int32_t)(N14_Rand() & 0xff);
    P120_ScrC = 0;
    P120_ScrD = (int32_t)(N14_Rand() & 0xf) - 8;
    P120_ScrE = (int32_t)(N14_Rand() & 0xf) - 8;
  }
  if ((P62_Frame & 3) == 0) {
    if (P120_ScrB < P120_ScrD) P120_ScrB++; else if (P120_ScrD < P120_ScrB) P120_ScrB--;
    if (P120_ScrA < P120_ScrE) P120_ScrA++; else if (P120_ScrE < P120_ScrA) P120_ScrA--;
  }
  int32_t *st = G2_ScriptStack;
#ifndef RE_HOOK_BUILD
  if (st == NULL) return;
#endif
  if (st[0] == 0) return;
  P44_MatPtr = (float *)P44_ViewMatT;
  int32_t *r = st + PT_POOL_FIRST;
  for (int32_t n = st[0]; n != 0; n--, r += PT_DWORDS) {
    r[0] += P120_ScrB; r[1] += 10; r[2] += P120_ScrA;
    if (r[1] >= 0x33) { ScriptStackPush004CB9F2((int32_t)*(int16_t *)(void *)((uint8_t *)r + PT_INDEX_B)); continue; }
    project(r, 4096.0f);
  }
}
