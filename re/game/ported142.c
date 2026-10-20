#include <stdlib.h>
#include <stdio.h>
#include <math.h>
/* ported142.c — car physics and cop driving (English overview; the original Russian notes follow).
   004a7fec P142_CopDrive  — police AI: target speed/steering -> throttle/steering of the cop car.
   004df024 P142_WheelPhys — ground contact, suspension and tyre forces of one car.
   004dacee P142_CarsStep  — physics step of all active cars: integration and car-car collisions.
   Car record fields are named in carfields.h, fixed-point/angle constants in fixmath.h.
   Arithmetic is kept 32-bit-wrapping exactly as in Game.exe: W(expr) evaluates in int64 and wraps to
   int32, L(x) widens; dv(v, sh) is signed division by 2^sh rounding toward zero (MSVC idiom).

   v1.87: ported142 — см. ported142.h.
   004a7fec — коп rec[5] (запись 0112da00 + (n−1)·0xcd8, машина 0113a6c4 + rec[0]·0x148): при 0112b268 == 0 или 00c824a0 — газ 0;
     выбывший коп (+0xcc4 == 1) — газ 0, таймер +0xcd4 −= 0.01; сумма повреждений +0x11c..+0x130 (если 0112d9d0 == 0) > 00575ee0 —
     выбыл; иначе счётчики застревания (+0x30, +0x58 ≥ 0xc9 — выбыл), разворот (+0x38 = 0x16), расстояние 004a7f0e, цель —
     упреждение игрока (12000) или точка пути 004a7aa7, сглаживание по истории +0xc74..+0xcb0, выбор режима руления 0..3
     (таблица 00552770 по 00b87e2c), газ ±(00b87e2c+8)·0x400·(0112b2b8 + 00d11a5c·011340c4 >> 12), руль ±200 к +0xfc;
     каждый 8-й кадр (00d118c0 % 8 == n−1) — 004a742a и курс по пути 004daac7.
   004df024 — состояние 0x64 байта на стеке (+0x14 позиция, +0x20 скорость, +0x30 сила, +0x40 угл. скорость, +0x50 момент,
     +0x60 флаг) — в native массив st[25]; маркер 00d02630: отталкивание от 00d02650/58 (ftol), при 00d02644 — повреждения 0xfff;
     контакт 12 (4 при +0xc > 0x800) точек кузова модели 00d0cc60 + тип·0x16c (+0x104) с землёй 004dd262, затем 4 колеса (+0xe0):
     подвеска, боковая сила (таблица синусов 00576f10), газ/тормоз/ручник, звук удара колеса игрока (00b2ea38), 004e0fd4.
   004dacee — 004defd1 (004df024 для всех), 004deb99; интеграция скорости/вращения (кватернион +0x30..+0x3c) и 004da8d9;
     4 × 2 подшага: 004dab80 → 00d0de00/00d0eb80, попарные столкновения 00499bb2 (|d| ≤ 0x4b0) с импульсами и повреждениями
     0049aa14, искры/дым 004b955c/004b8d49, звук 00523cda, 0048f899; полушаг 00d06a20 и шаг (>>4); курс +0x100, углы +0xe8..+0xec,
     копии позиции/скорости, точки колёс +0x88 (004dd262).
   Отступления native: 004a7fec — rec[5] вне 1..8 или машина вне таблицы — выход; деление на 0 (в оригинале исключение) — 0;
     неинициализированные в оригинале 2-е/4-е слова цели (ветка 0x333) — 0. 004df024/004dacee — байт 011443e5/011443e2 записи
     трафика для объекта 0 (в оригинале чтение перед таблицей) — 0; тип модели вне 00d0cc60 (0x4000) — точки (0, 0, 0);
     деление на 0 в 004df024 (сумма квадратов/знаменатель) — 0. */
#include "ported142.h"
#include "carfields.h"
#include "fixmath.h"
#include "cartab.h"
#include "director.h"
#include "directorstorage.h"
#include "reptr.h"
#ifndef RE_HOOK_BUILD
#include "../platform/native/reprobe.h"
#endif
#include "ported4.h"
#include "ported6.h"
#include "ported7.h"
#include "ported8.h"
#include "ported12.h"
#include "ported14.h"
#include "ported17.h"
#include "ported35.h"
#include "ported44.h"
#include "ported46.h"
#include "ported48.h"
#include "ported56.h"
#include "ported58.h"
#include "ported59.h"
#include "ported100.h"
#include "ported62.h"
#include "ported74.h"
#include "ported76.h"
#include "ported88.h"
#include "ported94.h"
#include "ported95.h"
#include "ported97.h"
#include "ported98.h"
#include "ported99.h"
#include "ported102.h"
#include "ported103.h"
#include "ported107.h"
#include "ported112.h"
#include "ported114.h"
#include "ported125.h"
#include "ported128.h"
#include "ported140.h"
#include "smallfuncs.h"
#include "smallfuncs2.h"
#include "menustate.h"
#include "uihandlers3.h"
#include "uihandlers4.h"
#include "widgets.h"
#include <string.h>

#ifndef RE_HOOK_BUILD
int plat_frame_no(void);   /* v2.29: номер показанного кадра — для журналов отладки */
#endif
#ifndef RE_HOOK_BUILD
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P142_CopNoDmg")
#undef P142_CopNoDmg
#pragma push_macro("P142_CopNoDmg") /*gvi*/
#undef P142_CopNoDmg /*gvi*/
int32_t P142_CopNoDmg;
#pragma pop_macro("P142_CopNoDmg") /*gvi*/
#pragma pop_macro("P142_CopNoDmg")
#endif
#pragma push_macro("P142_CopDmgMax") /*gvi*/
#undef P142_CopDmgMax /*gvi*/
int32_t P142_CopDmgMax = 7000;                    /* .data 00575ee0 */
#pragma pop_macro("P142_CopDmgMax") /*gvi*/
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P142_B278")
#undef P142_B278
#pragma push_macro("P142_B278") /*gvi*/
#undef P142_B278 /*gvi*/
int32_t P142_B278;
#pragma pop_macro("P142_B278") /*gvi*/
#pragma pop_macro("P142_B278")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P142_B27C")
#undef P142_B27C
#pragma push_macro("P142_B27C") /*gvi*/
#undef P142_B27C /*gvi*/
int32_t P142_B27C;
#pragma pop_macro("P142_B27C") /*gvi*/
#pragma pop_macro("P142_B27C")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P142_B2AC")
#undef P142_B2AC
#pragma push_macro("P142_B2AC") /*gvi*/
#undef P142_B2AC /*gvi*/
int32_t P142_B2AC;
#pragma pop_macro("P142_B2AC") /*gvi*/
#pragma pop_macro("P142_B2AC")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P142_B2B8")
#undef P142_B2B8
#pragma push_macro("P142_B2B8") /*gvi*/
#undef P142_B2B8 /*gvi*/
int32_t P142_B2B8;
#pragma pop_macro("P142_B2B8") /*gvi*/
#pragma pop_macro("P142_B2B8")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P142_340C0")
#undef P142_340C0
#pragma push_macro("P142_340C0") /*gvi*/
#undef P142_340C0 /*gvi*/
int32_t P142_340C0;
#pragma pop_macro("P142_340C0") /*gvi*/
#pragma pop_macro("P142_340C0")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P142_340C4")
#undef P142_340C4
#pragma push_macro("P142_340C4") /*gvi*/
#undef P142_340C4 /*gvi*/
int32_t P142_340C4;
#pragma pop_macro("P142_340C4") /*gvi*/
#pragma pop_macro("P142_340C4")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P142_D07788")
#undef P142_D07788
#pragma push_macro("P142_D07788") /*gvi*/
#undef P142_D07788 /*gvi*/
int32_t P142_D07788;
#pragma pop_macro("P142_D07788") /*gvi*/
#pragma pop_macro("P142_D07788")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P142_B87E18")
#undef P142_B87E18
#pragma push_macro("P142_B87E18") /*gvi*/
#undef P142_B87E18 /*gvi*/
int32_t P142_B87E18;
#pragma pop_macro("P142_B87E18") /*gvi*/
#pragma pop_macro("P142_B87E18")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P142_B2F304")
#undef P142_B2F304
#pragma push_macro("P142_B2F304") /*gvi*/
#undef P142_B2F304 /*gvi*/
int32_t P142_B2F304;
#pragma pop_macro("P142_B2F304") /*gvi*/
#pragma pop_macro("P142_B2F304")
#endif
#endif

/* 32-битная арифметика оригинала: выражение в int64, затем по модулю 2^32 */
#define W(x)  ((int32_t)(uint32_t)(int64_t)(x))
#define L(x)  ((int64_t)(x))
static int32_t dv(int32_t v, int sh) { return (int32_t)((uint32_t)v + ((uint32_t)(v >> 31) & ((1u << sh) - 1u))) >> sh; }  /* v / 2^sh к нулю */
#define RE_MEMRW_LOCAL16   /* keep the local 16-bit helpers below (hook object identity, see memrw.h) */
#include "memrw.h"
static void add32(uint8_t *p, int32_t v) { wr32(p, W(L(rd32(p)) + v)); }
static int32_t rd16(const uint8_t *p) { int16_t v; memcpy(&v, p, 2); return v; }
static void wr16(uint8_t *p, int32_t v) { int16_t s = (int16_t)v; memcpy(p, &s, 2); }
static int32_t sn(uint32_t a) { return P59_Sin[a & 0xfff]; }
static int32_t iabs32(int32_t v) { return v < 0 ? -v : v; }
static uint32_t oaddr(const uint8_t *o) { return re_addr(o); }
static const uint8_t *cars_base(void) { return (const uint8_t *)&P99_Cars[0]; }
static int is_player(const uint8_t *o) { return o == cars_base(); }
static int is_cur(const uint8_t *o) { return o == cars_base() + (size_t)S_00D11878 * sizeof(p99_car_t); }
static uint8_t traffic_b(int32_t obj_id, int off) {     /* (&011443e0 + off)[(id − 1)·0x54] */
  int32_t i = obj_id - 1;
  if (i < 0 || (uint32_t)(i * 0x54 + off) >= sizeof TrafficRecs) return 0;
  return TrafficRecs[i * 0x54 + off];
}
static const uint8_t *model_pt(uint32_t type, int32_t idx) {   /* 00d0cc60 + тип·0x16c + idx·4 */
  static const int16_t zero3[3] = { 0, 0, 0 };
  uint32_t off = type * 0x16cu + (uint32_t)idx * 4u;
  if (off + 6u > sizeof S_00D0CC60) return (const uint8_t *)zero3;
  return &S_00D0CC60[off];
}
static void load_pt(const uint8_t *p) { int16_t s[3]; memcpy(s, p, 6); LoadShort3FromPtr(s); }

/* ---------------- 004a7fec ---------------- */

/* Cop AI record: P12_0112da00 holds 8 records of 0x336 int32 (0xcd8 bytes), one per cop slot 1..8
   (Game.exe 0112da00 + (n-1) * 0xcd8).  Indices below are int32 indices into one record; only the
   ones whose use is clear are named, the rest stay numeric. */
enum {
  COP_HEADING      = 0x003,   /* copy of the car heading (car + CAR_HEADING) */
  COP_TGT_STEER    = 0x008,   /* steering the AI wants (copied towards car + CAR_STEER, max 200 per frame) */
  COP_TGT_SPEED    = 0x009,   /* forward speed the AI wants (same units as CAR_FWD_SPEED >> 12); < 0 = reverse */
  COP_SPEED        = 0x00a,   /* copy of car + CAR_SPEED */
  COP_REPLAN_T     = 0x00b,   /* frames until the path is considered stale (decremented every frame) */
  COP_STUCK_N      = 0x00c,   /* frames spent nearly stopped while wanting to move */
  COP_UNSTICK_N    = 0x00d,   /* unstick manoeuvre counter 1..8 (picks the steering side) */
  COP_UNSTICK_T    = 0x00e,   /* frames left of the current unstick manoeuvre (starts at 0x16) */
  COP_F0F          = 0x00f,   /* TODO(RE): unsure — counts down to 0, cleared when the path heading is applied */
  COP_DAMAGE       = 0x010,   /* sum of the car's six damage zones (0 when P142_CopNoDmg) */
  COP_PLAYER_X     = 0x012,   /* player position snapshot (x, z) when the cop is close */
  COP_PLAYER_Z     = 0x013,
  COP_PLAYER_CX    = 0x014,   /* ... and the map cell of that snapshot (cell = 0x5dc units) */
  COP_PLAYER_CZ    = 0x015,
  COP_FEW_WHEELS_N = 0x016,   /* frames with fewer than 3 wheels on the ground (>= 0xc9 retires the cop) */
  COP_HALF_ACCEL   = 0x017,   /* TODO(RE): unsure — non-zero halves the acceleration limit */
  COP_PATH         = 0x018,   /* path-finder data starts here (P114_PathDraw / P99_PathAhead / P102_CopPathPoint) */
  COP_PATH_HEADING = 0x01f,   /* int16 at this index: heading of the path start, applied on a fresh path */
  COP_POS_X        = 0x319,   /* copies of the car position */
  COP_POS_Z        = 0x31b,
  COP_TGT_HIST     = 0x31d,   /* 4 x 4 int32: last four target points, newest first (used to smooth the target) */
  COP_ON_PATH      = 0x32e,   /* 1 while following the path-finder route instead of chasing directly */
  COP_PATH_SNAP    = 0x32f,   /* 1 = a new route was planned: snap the heading to COP_PATH_HEADING */
  COP_RETIRED      = 0x331,   /* 1 = cop is out of the chase (wrecked / stuck / flipped) */
  COP_CLOSE        = 0x333,   /* 1 = close to the player's lead point: chase it directly */
  COP_FADE_T       = 0x335,   /* float: timer of a retired cop, counts down by 0.01 per frame */
};
#define COP_REC_INTS     0x336
#define COP_SLOTS        8
#define COP_LEAD_RANGE   12000   /* within this distance the cop aims at where the player will be, not where he is */
#define COP_CLOSE_RANGE  2000    /* always "close" below this distance ... */
#define COP_CLOSE_RANGE2 0x20d0  /* ... and below this one when not following a route */
#define COP_ROUTE_DRIFT  0xd49   /* off-route distance that drops the route */
#define MAP_CELL         0x5dc   /* road-map cell size in world units (see ported72.c) */
#define MAP_CELL_HALF    0x2ee
#define STEER_RATE_MAX   200     /* steering may change at most this much per frame */

static const int32_t k_552770[6] = { 290, 300, 310, 340, 380, 420 };   /* .data 00552770: cop cruise speed by difficulty (+3 when 01129584 is set) */
static uint8_t *cop_car(uint32_t i) {
#ifndef RE_HOOK_BUILD
  if (P59_CarsTab == NULL) { uint32_t k = i + 1; return (k < P99_CARS_N) ? (uint8_t *)&P99_Cars[k] : NULL; }
#endif
  return P59_CarsTab + i * 0x148u;
}
static int32_t cop_f(int32_t *c, int i) { return c[i]; }

/* P142_CopDrive — Game.exe 004a7fec, cdecl.
   One AI step for a police car: decides target speed and steering and writes throttle/steering
   into the car record.  Called once per frame per active cop.
   In:  rec — the cop's traffic record (0x54 bytes): rec[0] = car index in P59_CarsTab,
        rec[5] = cop slot 1..8 (selects the cop AI record in P12_0112da00).
   Out: car + CAR_THROTTLE, car + CAR_STEER, car[CAR_AI_DRIVEN]; the cop AI record (see enum above);
        the shared chase target P97_B2A0/B2A4/B2A8 (+ P142_B2AC) and P97_129584.
   Steps: idle when the chase is off; retire the cop on heavy damage or when it stays flipped;
        run an "unstick" reverse manoeuvre when stuck; aim at the player's lead point (or a
        path-finder route when far); smooth the target over the last 4 frames; choose one of
        four steering modes; limit throttle by speed error and steering change by STEER_RATE_MAX;
        every 8th frame (staggered by slot) re-plan the route.
   Native deviations (see file header): slot out of 1..8 or car missing -> return; divisions by zero
   (an exception in the original) give 0. */
#ifndef RE_HOOK_BUILD
static void cop_drive_body(uint8_t *rec);
/* RE_COPTRACE=N — native debug: every N frames one line per driven cop (slot, car, AI record fields, throttle). */
void P142_CopDrive(uint8_t *rec) {
  cop_drive_body(rec);
  static int every = -2; if (every == -2) { const char *e = getenv("RE_COPTRACE"); every = e ? (atoi(e) > 0 ? atoi(e) : 10) : 0; }
  if (every <= 0 || P62_Frame % every != 0) return;
  int32_t slot = (int32_t)rec[5] - 1;
  if (slot < 0 || slot >= COP_SLOTS) { fprintf(stderr, "[coptr] f=%d rec car=%d slot %d — нет слота\n", (int)P62_Frame, rec[0], slot + 1); return; }
  const int32_t *cop = (const int32_t *)(const void *)&P12_0112da00[slot * COP_REC_INTS];
  const uint8_t *car = cop_car(rec[0]);
  fprintf(stderr, "[coptr] f=%d slot %d car %d st %d b268 %d c24a0 %d ret %d close %d path %d tsp %d tst %d stuck %d unst %d dmg %d pos %d %d spd %d fwd %d thr %d steer %d ai %d wheels %d pl %d %d\n",
          (int)P62_Frame, slot + 1, rec[0], rec[1], (int)P56_B268, (int)P98_C824A0, cop[COP_RETIRED], cop[COP_CLOSE], cop[COP_ON_PATH],
          cop[COP_TGT_SPEED], cop[COP_TGT_STEER], cop[COP_STUCK_N], cop[COP_UNSTICK_T], cop[COP_DAMAGE],
          car ? rd32(car + CAR_POS_X) : 0, car ? rd32(car + CAR_POS_Z) : 0, car ? rd32(car + CAR_SPEED) : 0, car ? rd32(car + CAR_FWD_SPEED) : 0,
          car ? rd32(car + CAR_THROTTLE) : 0, car ? rd32(car + CAR_STEER) : 0, car ? car[CAR_AI_DRIVEN] : 0, car ? rd32(car + CAR_WHEELS_DOWN) : 0,
          (int)PlayerPosX, (int)PlayerPosZ);
}
static void cop_drive_body(uint8_t *rec) {
#else
void P142_CopDrive(uint8_t *rec) {
#endif
#ifndef RE_HOOK_BUILD
  static int reg;
  if (!reg) {
    reg = 1;
    re_ptr_register(0x0112b278u, &P142_B278, 4); re_ptr_register(0x0112b27cu, &P142_B27C, 4);
    re_ptr_register(0x0112b2b8u, &P142_B2B8, 4); re_ptr_register(0x011340c0u, &P142_340C0, 4);
    re_ptr_register(0x011340c4u, &P142_340C4, 4);
  }
#endif
  int32_t slot = (int32_t)rec[5] - 1;
  if (slot < 0 || slot >= COP_SLOTS) return;
  int32_t *cop = (int32_t *)(void *)&P12_0112da00[slot * COP_REC_INTS];
  uint8_t *car = cop_car(rec[0]);
  if (car == NULL) return;
  /* Chase not running (P56_B268 == 0) or game paused/frozen (00c824a0): just release the throttle. */
  if (P56_B268 == 0 || P98_C824A0 != 0) { wr32(car + CAR_THROTTLE, 0); return; }
  if (cop[COP_RETIRED] == 1) {
    float f;
    wr32(car + CAR_THROTTLE, 0);
    memcpy(&f, &cop[COP_FADE_T], 4);
    if (0.01f < f) { f = f - 0.01f; memcpy(&cop[COP_FADE_T], &f, 4); }
    return;
  }
  /* Total damage; a cop beyond P142_CopDmgMax (7000) drops out. */
  if (P142_CopNoDmg == 0) {
    cop[COP_DAMAGE] = 0;
    for (int i = 0; i < CAR_DAMAGE_N; i++) cop[COP_DAMAGE] = W(L(cop[COP_DAMAGE]) + rd32(car + CAR_DAMAGE + i * 4));
  } else cop[COP_DAMAGE] = 0;
  if (P142_CopDmgMax < cop[COP_DAMAGE]) { cop[COP_RETIRED] = 1; wr32(car + CAR_THROTTLE, 0); return; }
  cop[COP_RETIRED] = 0;
  cop[COP_POS_X] = rd32(car + CAR_POS_X);
  cop[COP_POS_Z] = rd32(car + CAR_POS_Z);
  cop[COP_SPEED] = rd32(car + CAR_SPEED);
  cop[COP_HEADING] = rd32(car + CAR_HEADING);
  int32_t fwd_speed = W(L(rd32(car + CAR_FWD_SPEED)) + FX_HALF) >> FX_SHIFT;   /* 20.12 -> integer, rounded */
  int32_t pos_x = rd32(car + CAR_POS_X), pos_z = rd32(car + CAR_POS_Z);
  /* Player velocity relative to this cop (00d07800 / 00d07808); P74_Dist adds it (>> 8) to the
     player position, i.e. measures the distance to where the player is heading. */
  int32_t rel_vx = W(L(P99_Cars[0].f40[0]) - rd32(car + CAR_VEL + 0));
  int32_t rel_vz = W(L(P99_Cars[0].f40[2]) - rd32(car + CAR_VEL + 8));
  /* Car's local X (right) axis in the ground plane: matrix elements [0] and [6]. */
  int32_t right_x = rd16(car + CAR_MAT + 0), right_z = rd16(car + CAR_MAT + 12);
  int32_t have_target = 0;
  int32_t pt[4] = { 0, 0, 0, 0 };   /* target point x, y, z, w (y/w are not used for steering) */
  P97_129584 = 0;
  /* Stuck detection: nearly stopped while asking for speed. */
  if (rd32(car + CAR_SPEED) < 5 && cop[COP_TGT_SPEED] != 0) cop[COP_STUCK_N]++; else cop[COP_STUCK_N] = 0;
  if (rd32(car + CAR_WHEELS_DOWN) < 3) cop[COP_FEW_WHEELS_N]++; else cop[COP_FEW_WHEELS_N] = 0;
  if (cop[COP_FEW_WHEELS_N] >= 0xc9) { cop[COP_RETIRED] = 1; return; }   /* on its side/roof for 200 frames */
  if (10 < cop[COP_STUCK_N] && cop[COP_UNSTICK_T] == 0) {
    /* Start a 0x16-frame unstick manoeuvre: flip the speed sign, steer to a side picked by the counter
       (((n * 5) >> 1) & 3) * 2 - 3 gives -3, -1, 1 or 3, times 0x80. */
    cop[COP_UNSTICK_T] = 0x16;
    cop[COP_UNSTICK_N] = (cop[COP_UNSTICK_N] & 7) + 1;
    cop[COP_TGT_SPEED] = (cop[COP_TGT_SPEED] >= 0) ? -300 : 300;
    cop[COP_TGT_STEER] = ((((cop[COP_UNSTICK_N] * 5) >> 1) & 3) * 2 - 3) * 0x80;
    cop[COP_STUCK_N] = 0;
  }
  int32_t dist_lead = P74_Dist(pos_x, pos_z, rel_vx, rel_vz);
  cop[COP_CLOSE] = (dist_lead < COP_CLOSE_RANGE || (cop[COP_ON_PATH] == 0 && dist_lead < COP_CLOSE_RANGE2)) ? 1 : 0;
  if (cop[COP_UNSTICK_T] < 1) {
    if (dist_lead < COP_LEAD_RANGE) {
      /* Intercept: t = time of closest approach along the relative velocity,
         t = -(dp . dv) / (|dv|^2 + 1), clamped to 0..60 (x1.5 when not at maximum wanted level). */
      int32_t rvx = W(L(rel_vx) + FX_HALF) >> FX_SHIFT, rvz = W(L(rel_vz) + FX_HALF) >> FX_SHIFT;
      int32_t den = W(L(rvx) * rvx + 1 + L(rvz) * rvz);
      int32_t num = W(-L(W(L(PlayerPosX) - pos_x)) * rvx - L(W(L(PlayerPosZ) - pos_z)) * rvz);
      int32_t t = den ? (int32_t)(L(num) / den) : 0;
      if (P112_Wanted == 0) t = dv(W(L(t) * 3), 2);
      int32_t lead_t = t < 0 ? 0 : (t < 0x3d ? t : 0x3c);
      /* Aim offset from the player: 1/16 of a unit behind him (minus his forward axis, matrix [2]/[8] —
         the same axis P142_CarsStep takes the heading from) normally; 1/32 to his side (his X axis,
         matrix [0]/[6]) at maximum wanted level. */
      int32_t off_x, off_z;
      if (P112_Wanted == 0) { off_x = -dv(P99_Cars[0].mat[2], 4); off_z = -dv(P99_Cars[0].mat[8], 4); }
      else { off_x = dv(P99_Cars[0].mat[0], 5); off_z = dv(P99_Cars[0].mat[6], 5); }
      P97_B2A8 = W(L(PlayerPosZ) + (W(L(P99_Cars[0].f40[2]) * lead_t + FX_HALF) >> FX_SHIFT) + off_z);
      P97_B2A0 = W(L(PlayerPosX) + (W(L(P99_Cars[0].f40[0]) * lead_t + FX_HALF) >> FX_SHIFT) + off_x);
    } else { P97_B2A0 = PlayerPosX; P97_B2A8 = PlayerPosZ; }
    if (cop[COP_CLOSE] == 0) {
      /* Far: follow the route while it stays within COP_ROUTE_DRIFT of the car's lateral axis. */
      if (cop[COP_ON_PATH] != 0) {
        P114_PathDraw((uint8_t *)(cop + COP_PATH), 0);
        int32_t ahead = P99_PathAhead((uint8_t *)cop);
        P102_CopPathPoint((uint8_t *)cop, ahead, pt);
        int32_t off = W(L(W(L(pt[0]) - pos_x)) * right_x + L(W(L(pt[2]) - pos_z)) * right_z) >> FX_SHIFT;
        if (off < 0) off = -off;
        if (off < COP_ROUTE_DRIFT) {
          /* look further ahead the faster we go: ahead + speed * 10 + 1000 */
          if (cop[COP_ON_PATH] != 0) { P102_CopPathPoint((uint8_t *)cop, W(L(ahead) + L(rd32(car + CAR_SPEED)) * 10 + 1000), pt); have_target = 1; }
        } else cop[COP_ON_PATH] = 0;
      }
    } else {
      /* Close: chase the lead point directly and remember where the player was (for re-planning). */
      pt[0] = P97_B2A0; pt[2] = P97_B2A8;
      cop[COP_ON_PATH] = 0;
      cop[COP_PLAYER_X] = PlayerPosX; cop[COP_PLAYER_Z] = PlayerPosZ;
      int32_t cz = W(L(P62_Map2C40) - (L(cop[COP_PLAYER_Z]) - MAP_CELL_HALF));
      cop[COP_PLAYER_CX] = W(L(cop[COP_PLAYER_X]) + MAP_CELL_HALF + P62_MapC64) / MAP_CELL;
      cop[COP_PLAYER_CZ] = cz / MAP_CELL;
      have_target = 1;
    }
  } else cop[COP_UNSTICK_T]--;
  if (have_target == 0) { pt[0] = P97_B2A0; pt[1] = P97_B2A4; pt[2] = P97_B2A8; pt[3] = P142_B2AC; }
  /* Smooth: target = (2 * previous - the one 3 frames ago + current) / 2 (x and z only), then push
     the new point into the 4-deep history. */
  pt[0] = W(L(cop[COP_TGT_HIST + 4]) * 2 - cop[COP_TGT_HIST + 12] + pt[0]) >> 1;
  pt[2] = W(L(cop[COP_TGT_HIST + 6]) * 2 - cop[COP_TGT_HIST + 14] + pt[2]) >> 1;
  for (int i = 0; i < 4; i++) {
    cop[COP_TGT_HIST + 12 + i] = cop[COP_TGT_HIST + 8 + i]; cop[COP_TGT_HIST + 8 + i] = cop[COP_TGT_HIST + 4 + i];
    cop[COP_TGT_HIST + 4 + i] = cop[COP_TGT_HIST + i]; cop[COP_TGT_HIST + i] = pt[i];
  }
  if (G6_005624A0 == 0) have_target = 0;   /* cop steering globally disabled (.data flag 005624a0, normally 1) */
  if (have_target == 0) {
    if (cop[COP_UNSTICK_T] < 1) { cop[COP_TGT_SPEED] = 0; cop[COP_TGT_STEER] = 0; }
  } else {
    /* Target in the car's frame: lat = offset along the right axis (corrected by the sideways
       velocity / 0xc6), fwd = distance ahead. */
    int32_t lat_vel = W(L(right_x) * rd32(car + CAR_VEL + 0) + FX_HALF + L(right_z) * rd32(car + CAR_VEL + 8)) >> FX_SHIFT;
    int32_t to_x = W(L(pt[0]) - pos_x), to_z = W(L(pt[2]) - pos_z);
    int32_t fwd = W(-L(to_x) * right_z + L(to_z) * right_x) >> FX_SHIFT;
    int32_t lat = (W(L(to_x) * right_x + L(to_z) * right_z) >> FX_SHIFT) - lat_vel / 0xc6;
    enum { STEER_AHEAD, STEER_BACK_OFF, STEER_TURN_NEG, STEER_TURN_POS } mode;
    if (lat < 1) {
      if (W(L(lat) * -2) < fwd) mode = STEER_AHEAD;                                   /* within ~27 deg of dead ahead */
      else mode = (-lat < W(L(fwd) * 4) && cop[COP_CLOSE] != 0) ? STEER_BACK_OFF : STEER_TURN_NEG;
    } else {
      if (W(L(lat) * 2) < fwd) mode = STEER_AHEAD;
      else mode = (lat < W(L(fwd) * 4) && cop[COP_CLOSE] != 0) ? STEER_BACK_OFF : STEER_TURN_POS;
    }
    uint32_t lat_raw = (uint32_t)(lat + lat_vel / 0xc6);
    car[CAR_AI_DRIVEN] = (uint8_t)(0 < (int32_t)((uint32_t)cop[COP_TGT_SPEED] ^ (uint32_t)fwd_speed));
    int32_t same_sign = (int32_t)(lat_raw ^ (uint32_t)fwd_speed) >= 0;   /* steer flips when reversing */
    switch (mode) {
    case STEER_AHEAD: {
      /* Cruise speed by difficulty, scaled by (P142_B278 + felony * P142_B27C) in 20.12. */
      int32_t di = WI00B87E2C;
      int32_t ti = (P97_129584 == 0) ? di : di + 3;
      cop[COP_TGT_SPEED] = (ti >= 0 && ti < 6) ? k_552770[ti] : 0;
      cop[COP_TGT_SPEED] = W(L(cop[COP_TGT_SPEED]) * W(L(P142_B278) + (W(L(G2_00D11A5C) * P142_B27C) >> FX_SHIFT))) >> FX_SHIFT;
      if (P142_340C0 != 0 && cop[COP_CLOSE] != 0) {
        /* Close in: match the player's speed + 10 below 4000 units, blend towards cruise speed up to 8000. */
        if (dist_lead < 0xfa1) cop[COP_TGT_SPEED] = P62_Spd + 10;
        else cop[COP_TGT_SPEED] = W(L(P62_Spd) + 10 + W(L(W(L(cop[COP_TGT_SPEED]) - (P62_Spd + 10))) * (dist_lead - 4000)) / 4000);
      }
      cop[COP_TGT_STEER] = fwd ? W(L(lat_raw) * 0x200) / fwd : 0;   /* steer ~ lateral / forward (atan-like) */
      break;
    }
    case STEER_BACK_OFF:   /* target beside us and close: reverse slowly with half lock */
      cop[COP_TGT_SPEED] = -100;
      cop[COP_TGT_STEER] = same_sign ? 0x11c : -0x11c;
      break;
    default:               /* STEER_TURN_NEG / STEER_TURN_POS: full lock at low speed (reverse during a close max-wanted chase) */
      cop[COP_TGT_SPEED] = (P112_Wanted == 0 || cop[COP_CLOSE] == 0 || cop[COP_TGT_SPEED] >= 0) ? 0x6e : -0x6e;
      cop[COP_TGT_STEER] = same_sign ? 0x200 : -0x200;
      break;
    }
    car[CAR_AI_DRIVEN] = 1;   /* quirk kept from the original: the value computed above is always overwritten */
  }
  if (cop[COP_F0F] != 0) cop[COP_F0F]--;
  /* Near the player (not at max wanted): ease off towards player speed - 20 (at least 20). */
  if (dist_lead < 0x1000 && 0 < cop[COP_TGT_SPEED] && P112_Wanted == 0) {
    int32_t slow = P62_Spd - 0x14;
    if (slow < 0x14) slow = 0x14;
    cop[COP_TGT_SPEED] = W(L(dist_lead) * cop[COP_TGT_SPEED] + FX_HALF + L(0x1000 - dist_lead) * slow) >> FX_SHIFT;
  }
  /* Throttle: proportional to the speed error, saturating at +-50; the limit grows with difficulty
     and felony ((P142_B2B8 + felony * P142_340C4) in 20.12). */
  int32_t speed_err = W(L(cop[COP_TGT_SPEED]) - fwd_speed);
  int32_t accel = (WI00B87E2C + 8) * 0x400;
  if (P97_129584 != 0) accel += (WI00B87E2C + 4) * 0x400;
  accel = W(L(accel) * W(L(P142_B2B8) + (W(L(G2_00D11A5C) * P142_340C4) >> FX_SHIFT))) >> FX_SHIFT;
  if (cop[COP_HALF_ACCEL] != 0) accel = accel / 2;
  int32_t throttle;
  if (speed_err < -0x32) throttle = -accel;
  else if (speed_err < 0x33) throttle = W(L(speed_err) * accel) / 0x32;
  else throttle = accel;
  if (rd32(car + CAR_SPEED) < 0x30) throttle = W(L(throttle) * (rd32(car + CAR_SPEED) + 0x50)) >> 7;   /* gentler from standstill */
  if (car[CAR_AI_DRIVEN] == 1) throttle >>= 1;
  wr32(car + CAR_THROTTLE, throttle);
  int32_t steer_step = W(L(cop[COP_TGT_STEER]) - rd32(car + CAR_STEER));
  if (steer_step < -STEER_RATE_MAX) steer_step = -STEER_RATE_MAX; else if (STEER_RATE_MAX < steer_step) steer_step = STEER_RATE_MAX;
  add32(car + CAR_STEER, steer_step);
  cop[COP_REPLAN_T]--;
  /* Route planning is spread over 8 frames: slot n re-plans when frame % 8 == n. */
  if (P62_Frame % 8 == slot) {
    if (cop[COP_REPLAN_T] < 0) cop[COP_ON_PATH] = 0;
    P128_CopReplan((uint8_t *)cop);
    if (cop[COP_ON_PATH] != 0 && cop_f(cop, COP_PATH_SNAP) == 1) {
      wr32(car + CAR_HEADING, rd16((const uint8_t *)(cop + COP_PATH_HEADING)));
      P59_ObjDir(car, 0);
      cop[COP_PATH_SNAP] = 0;
      cop[COP_F0F] = 0;
    }
  }
}

/* ---------------- 004df024 ---------------- */
static int drv_test(const uint8_t *o) {    /* 00575f24 / 0x41 / 00b87ea0 / 00575efc */
  if (G00575F24 == 0) return o[0] == 0x41 && (G6_00B87EA0 == 0 || P88_Mode575 != 2);
  return o[0] == 0 || o[0] == 0x41;
}
/* Surface traction for this car: models of type 1 always get full grip (FX_ONE); the player and the
   spare record get the surface value scaled by (0x7e90 - P142_D07788) / 0x8000; traffic keeps it. */
static int32_t traction(const uint8_t *o, int32_t v) {
  if (o[CAR_MODEL] == 1) return FX_ONE;
  if (o[CAR_ID] == 0 || 0x40 < o[CAR_ID]) return W(L(v) * (0x7e90 - P142_D07788)) >> 15;
  return v;
}

/* Physics state built on the stack by 004df024 (0x64 bytes = 25 int32) and handed to P94_SpringStep.
   Byte offsets in the original: +0x14 position, +0x20 velocity, +0x30 force, +0x40 angular velocity,
   +0x50 torque, +0x60 "pushed up out of the ground" flag. */
enum {
  ST_POS = 5,        /* int32[3] position (copy of CAR_POS2) */
  ST_VEL = 8,        /* int32[3] linear velocity (CAR_VEL) */
  ST_FORCE = 12,     /* int32[3] accumulated force; starts as marker push + gravity */
  ST_ANGVEL = 16,    /* int32[3] angular velocity (CAR_ANGVEL) */
  ST_TORQUE = 20,    /* int32[3] accumulated torque (starts from CAR_DANGVEL_PEND) */
  ST_LIFTED = 24,    /* 1 = the body was lifted out of the ground this step */
  ST_INTS = 25
};
#define GRAVITY_FORCE   0x2aaa   /* constant downward force added every step */
#define SUSP_MAX        0x3c     /* suspension travel limit */
#define SUSP_SPRING     0x14a    /* spring force per unit of compression */
#define SUSP_DAMP       200      /* damping per unit of the previous step's compression */
#define LAT_FORCE_MAX   18000    /* clamp of the tyre lateral force */

/* P142_WheelPhys — Game.exe 004df024, cdecl.
   Contact and tyre forces for one car for one physics step.
   In:  obj   — car record (see carfields.h);
        drive — non-zero when the controls may lock the wheels (passed by 004defd1; TODO(RE): exact meaning).
   Out: force/torque accumulated into the stack state and committed by P94_SpringStep (CAR_DVEL_PEND,
        CAR_DANGVEL_PEND); CAR_SPEED, CAR_FWD_SPEED, CAR_SLIP_FRONT/REAR, CAR_WHEELS_DOWN, per-wheel
        compression/locked/surface bytes, ground points CAR_GROUND_PT, P35_PadX (player force feedback).
   Side effects: smoke/debris bursts and impact sounds on hard body contacts, wheel-bump sound for
        the player, the "marker" push/wreck of 00d02630 (debug/scripted explosion: P98_MrkOff).
   Steps: (1) body points (12, or 4 when upright) against the ground: penetration impulses;
        (2) lift the body out of the ground; (3) per-wheel grip factors from throttle, handbrake,
        difficulty; (4) 4 wheels: suspension spring/damper + lateral tyre force + drive force,
        applied at the wheel position (force and r x F torque); (5) forward speed and FFB.
   Native deviations (see file header): traffic byte for object 0 reads 0; model type outside the
   00d0cc60 table gives zero points; divisions by zero give 0. */
void P142_WheelPhys(uint8_t *obj, int32_t drive) {
  int32_t st[ST_INTS];
  memset(st, 0, sizeof st);
  int32_t push_x = 0, push_y = 0, push_z = 0;
  uint32_t type = obj[CAR_MODEL];
  for (int i = 2; i >= 0; i--) {
    /* re-derive the <<4 position from the integer one, keeping its 4 fractional bits */
    int32_t v = (rd32(obj + CAR_POS_HI + i * 4) & 0xf) + W(L(rd32(obj + CAR_POS2 + i * 4)) * 0x10);
    wr32(obj + CAR_POS_HI + i * 4, v);
    st[ST_VEL + i] = rd32(obj + CAR_VEL + i * 4);
    st[ST_POS + i] = rd32(obj + CAR_POS2 + i * 4);
    st[ST_ANGVEL + i] = rd32(obj + CAR_ANGVEL + i * 4);
    st[ST_TORQUE + i] = rd32(obj + CAR_DANGVEL_PEND + i * 4);
  }
  /* Marker (00d02630): a radial push away from point 00d02650/58 (float x, z) for non-player cars within
     10000 units, strength ~ 1 / distance^2; with 00d02644 set the car is also wrecked. */
  if (P98_MrkOff != 0 && obj[CAR_ID] != 0) {
    float mx, mz;
    memcpy(&mx, &P76_ColObj[0], 4); memcpy(&mz, &P76_ColObj[8], 4);   /* 00d02650 / 00d02658 */
    int32_t ox = W(L(rd32(obj + CAR_POS_X)) - (int32_t)mx);
    int32_t oz = W(L(rd32(obj + CAR_POS_Z)) - (int32_t)mz);
    if (ox < 10000 && -10000 < ox && oz < 10000 && -10000 < oz) {
      int32_t d2 = W(L(ox) * ox + L(oz) * oz);
      if (d2 != 0) {
        push_x = W(L((int32_t)(0x7530000LL / d2)) * ox);
        push_y = (int32_t)(-0xd052140LL / d2);
        push_z = W(L((int32_t)(0x7530000LL / d2)) * oz);
      }
    }
    if (P140_Mrk2644 != 0) {
      for (int i = 0; i < CAR_DAMAGE_N; i++) wr32(obj + CAR_DAMAGE + i * 4, 0xfff);
      wr32(obj + CAR_DAMAGE_SUM, 0x5ffa);   /* 6 * 0xfff */
      AddUnique_004C1F9B((int32_t)obj[CAR_ID] - 1);
      uint8_t b = traffic_b(obj[CAR_ID], 5);
      if (b != 0 && b <= 8) P12_0112da00[(b - 1) * 0x336 + 0x331] = 1;   /* native: only 8 records; retire that cop (COP_RETIRED) */
    }
  }
  st[ST_FORCE + 0] = push_x; st[ST_FORCE + 1] = W(L(push_y) - GRAVITY_FORCE); st[ST_FORCE + 2] = push_z;
  /* Speed magnitude: octagonal approximation of |(vx, vz)|, i.e. max + min / 2. */
  int32_t avx = iabs32(W(L(st[ST_VEL + 0]) + FX_HALF) >> FX_SHIFT), avz = iabs32(W(L(st[ST_VEL + 2]) + FX_HALF) >> FX_SHIFT);
  int32_t speed = (avx < avz) ? avz + avx / 2 : avx + avz / 2;
  wr32(obj + CAR_SPEED, speed);
  /* Load the car's matrix and position into the transform used by RotVec_005279CB (model -> world). */
  { int16_t m[9]; memcpy(m, obj + CAR_MAT, 18); CopyShort9_005278FB(m); }
  CopyVec3_0052797A((uint32_t *)(void *)&st[ST_POS]);
  /* (1) Body contact points vs ground. */
  int32_t max_pen = 0;
  int32_t n_pts = (0x800 < rd16(obj + CAR_MAT_YY)) ? 4 : 0xc;   /* upright: 4 points are enough */
  for (int32_t i = n_pts - 1; i >= 0; i--) {
    int32_t wp[4] = { 0 }, nrm[4] = { 0 }, gnd[4] = { 0 };   /* world point, ground normal, ground point */
    load_pt(model_pt(type, 0x41 + i * 2));
    RotVec_005279CB(wp);
    int32_t rx = W(L(wp[0]) - st[ST_POS + 0]), ry = W(L(wp[1]) - st[ST_POS + 1]), rz = W(L(wp[2]) - st[ST_POS + 2]);   /* lever arm */
    int32_t grip = traction(obj, P103_GroundAt(wp, nrm, gnd));
    (void)grip;
    if (i < 4) {
      wr32(obj + CAR_GROUND_PT + i * CAR_GROUND_PT_SIZE + 0, gnd[0]);
      wr32(obj + CAR_GROUND_PT + i * CAR_GROUND_PT_SIZE + 4, gnd[1]);
      wr32(obj + CAR_GROUND_PT + i * CAR_GROUND_PT_SIZE + 8, gnd[2]);
    }
    int32_t pen = W(L(gnd[1]) - wp[1]);   /* > 0: point is below the ground */
    if (0 < pen) {
      int32_t pv[3], imp[3];
      if (max_pen < pen) max_pen = pen;
      /* velocity of the contact point: v + w x r */
      pv[0] = (W(L(st[ST_ANGVEL + 1]) * rz - L(st[ST_ANGVEL + 2]) * ry + FX_HALF) >> FX_SHIFT) + st[ST_VEL + 0];
      pv[1] = (W(L(st[ST_ANGVEL + 2]) * rx - L(st[ST_ANGVEL + 0]) * rz + FX_HALF) >> FX_SHIFT) + st[ST_VEL + 1];
      pv[2] = (W(L(st[ST_ANGVEL + 0]) * ry - L(st[ST_ANGVEL + 1]) * rx + FX_HALF) >> FX_SHIFT) + st[ST_VEL + 2];
      /* effective mass term: 1 + 0x6e * |r x n|^2 (in 20.12), from |r|^2 - (r . n)^2 */
      int32_t r_n = W(L(rx) * nrm[0] + L(ry) * nrm[1] + FX_HALF + L(rz) * nrm[2]) >> FX_SHIFT;
      int32_t r_perp2 = W(L(rx) * rx + L(ry) * ry + L(rz) * rz - L(r_n) * r_n);
      int32_t inv_mass = (W(L(r_perp2) * 0x6e + FX_HALF) >> FX_SHIFT) + FX_ONE;
      int32_t v_n = W(L(pv[0]) * nrm[0] + L(pv[1]) * nrm[1] + FX_HALF + L(pv[2]) * nrm[2]) >> FX_SHIFT;
      int32_t j_n = W(L(inv_mass ? v_n / inv_mass : 0) * -0x800);   /* normal impulse */
      static const int32_t k_5624b0[3] = { 0x5a0000, 0x21c0000, 0x5a0000 };   /* .data 005624b0: friction clamp x, y, z */
      for (int j = 2; j >= 0; j--) {
        int32_t fr = W(L(pv[j]) * 0x60);
        if (k_5624b0[j] < fr) fr = k_5624b0[j];
        else if (fr < -k_5624b0[j]) fr = -k_5624b0[j];
        imp[j] = W(L(j_n) * nrm[j] - fr + FX_HALF) >> FX_SHIFT;
      }
      if (20000 < j_n) {   /* hard hit: smoke (day) / debris (night, 00b87e84), crash sound above 30000 */
        if (P14_00b87e84 == 0) { int32_t v[4] = { 0, 0x28, 0, 0 }; P125_SmokePuffs(gnd, v, 10, 0, obj[CAR_MODEL]); }
        else { int32_t v[4] = { 0, 0x32, 0, 0 }; P125_ObjABurst(gnd, v, 0xf, 1); }
        if ((is_player(obj) || 0xd0cb07u < oaddr(obj)) && 30000 < j_n) P97_SndStart(3, 3, (float)gnd[0], (float)gnd[1], (float)gnd[2]);
      }
      /* force += imp; torque += r x imp (component-wise, original order kept) */
      st[ST_TORQUE + 2] = W(L(st[ST_TORQUE + 2]) - (W(L(ry) * imp[0] + FX_HALF) >> FX_SHIFT));
      st[ST_TORQUE + 1] = W(L(st[ST_TORQUE + 1]) + (W(L(rz) * imp[0] + FX_HALF) >> FX_SHIFT));
      st[ST_FORCE + 0] = W(L(st[ST_FORCE + 0]) + imp[0]);
      st[ST_TORQUE + 0] = W(L(st[ST_TORQUE + 0]) - (W(L(rz) * imp[1] + FX_HALF) >> FX_SHIFT));
      st[ST_TORQUE + 2] = W(L(st[ST_TORQUE + 2]) + (W(L(rx) * imp[1] + FX_HALF) >> FX_SHIFT));
      st[ST_FORCE + 1] = W(L(st[ST_FORCE + 1]) + imp[1]);
      st[ST_TORQUE + 1] = W(L(st[ST_TORQUE + 1]) - (W(L(rx) * imp[2] + FX_HALF) >> FX_SHIFT));
      st[ST_TORQUE + 0] = W(L(st[ST_TORQUE + 0]) + (W(L(ry) * imp[2] + FX_HALF) >> FX_SHIFT));
      st[ST_FORCE + 2] = W(L(st[ST_FORCE + 2]) + imp[2]);
    }
  }
  /* (2) Lift the body by the deepest penetration; kill vertical velocity on a big correction. */
  if (max_pen != 0) {
    st[ST_POS + 1] = W(L(st[ST_POS + 1]) + max_pen);
    add32(obj + CAR_POS_HI + 4, W(L(max_pen) * 0x10));
    add32(obj + CAR_POS_Y, max_pen);
    CopyVec3_0052797A((uint32_t *)(void *)&st[ST_POS]);
    st[ST_LIFTED] = 1;
    if (0x78 < max_pen) wr32(obj + CAR_VEL + 4, 0);
  }
  /* (3) Tyre parameters. slip_k: lateral stiffness, falls with speed (0xce4 max). */
  int32_t slip_k = ((speed < 0x20) ? speed * -0x48 + FX_ONE : 0x720 - speed) - 400;
  int32_t h = rd32(obj + CAR_HEADING);
  int32_t sin_h = sn((uint32_t)h), cos_h = sn((uint32_t)h + 0x400u);
  int32_t drag_x = W(L(st[ST_VEL + 0]) * -0xc), drag_y = W(L(st[ST_VEL + 1]) * -0xc), drag_z = W(L(st[ST_VEL + 2]) * -0xc);
  int32_t steer = rd32(obj + CAR_STEER);
  int32_t sin_hs = sn((uint32_t)h + (uint32_t)steer), cos_hs = sn((uint32_t)h + 0x400u + (uint32_t)steer);   /* front wheel direction */
  if (0xce4 < slip_k) slip_k = 0xce4;
  /* grip_f: front grip (braking/reverse 0x5ad, coasting 0x3a9, accelerating 0x334); rear grip = 0x780 - front. */
  int32_t grip_f = (rd32(obj + CAR_THROTTLE) < 0) ? 0x5ad : (rd32(obj + CAR_THROTTLE) < 1 ? 0x3a9 : 0x334);
  if (drv_test(obj) && rd32(obj + CAR_BURNOUT) == 0 && 0 < rd32(obj + CAR_FWD_SPEED)) {
    int32_t extra = (int8_t)obj[CAR_STEER_HOLD];
    if (0 < extra) { if (0x1a < extra) extra = 0x1a; grip_f += extra * 0x16; }
  }
  {
    /* hard braking above 0xf000 forward speed (20.12, ~15 units) locks all four wheels */
    uint8_t v = (rd32(obj + CAR_THROTTLE) < 0 && 0xf000 < rd32(obj + CAR_FWD_SPEED) && drive != 0) ? 1 : 0;
    obj[CAR_WHEEL + 3 * CAR_WHEEL_SIZE + WHEEL_LOCKED] = v; obj[CAR_WHEEL + 2 * CAR_WHEEL_SIZE + WHEEL_LOCKED] = v;
    obj[CAR_WHEEL + 1 * CAR_WHEEL_SIZE + WHEEL_LOCKED] = v; obj[CAR_WHEEL + 0 * CAR_WHEEL_SIZE + WHEEL_LOCKED] = v;
  }
  if (rd32(obj + CAR_HANDBRAKE) == 0) {
    if (rd32(obj + CAR_BURNOUT) != 0) grip_f += 600;
  } else {
    /* handbrake: no positive throttle, rear wheels locked, front grip shifted */
    if (rd32(obj + CAR_THROTTLE) >= 0) wr32(obj + CAR_THROTTLE, 0);
    grip_f += (rd32(obj + CAR_FWD_SPEED) < 1) ? -0x177 : 0x290;
    obj[CAR_WHEEL + 1 * CAR_WHEEL_SIZE + WHEEL_LOCKED] = 1; obj[CAR_WHEEL + 3 * CAR_WHEEL_SIZE + WHEEL_LOCKED] = 1;
    wr32(obj + CAR_BURNOUT, 0);
  }
  if (rd32(obj + CAR_FWD_SPEED) < 0 && rd32(obj + CAR_THROTTLE) >= 0 && rd32(obj + CAR_HANDBRAKE) == 0) grip_f -= 400;
  int32_t grip_r = 0x780 - grip_f;
  if (rd32(obj + CAR_BURNOUT) != 0) {
    wr32(obj + CAR_THROTTLE, MenuOptBDFA44 == 0 ? 0x1b58 : 0x36b0);
    if (0xf < obj[CAR_MODEL]) wr32(obj + CAR_THROTTLE, (int32_t)((uint32_t)rd32(obj + CAR_THROTTLE) << 1));
    if (obj[CAR_ID] == 0) wr32(obj + CAR_THROTTLE, dv(W(L(rd32(obj + CAR_THROTTLE)) * P107_SteerK), 12));
  }
  if (rd32(obj + CAR_THROTTLE) < 0 && 0xf000 < rd32(obj + CAR_FWD_SPEED) && drive != 0) {
    /* locked wheels: x1.25 grip (player additionally scaled by P142_B87E18 / 4096) */
    grip_f = dv(grip_f * 10, 3); grip_r = dv(grip_r * 10, 3);
    if (obj[CAR_ID] == 0) { grip_f = dv(W(L(grip_f) * P142_B87E18), 12); grip_r = dv(W(L(grip_r) * P142_B87E18), 12); }
  } else if (drv_test(obj) == 0) {
    if (drive != 0 && obj[CAR_WHEEL + WHEEL_SURFACE] != 0) grip_f = dv(grip_f * 0x24, 5);
  } else {
    grip_f = dv(grip_f * (obj[CAR_WHEEL + WHEEL_SURFACE] == 0 ? 0x23 : 0x27), 5);
  }
  if (obj[CAR_AI_DRIVEN] == 1) {
    int32_t m = WI00B87E2C == 0 ? 0x2d : (WI00B87E2C == 1 ? 0x37 : 0x44);   /* cops: grip by difficulty (x1.4 / x1.7 / x2.1) */
    grip_f = dv(grip_f * m, 5); grip_r = dv(grip_r * m, 5);
  } else if (!is_player(obj) && obj[CAR_ID] != 0x41) {
    grip_f = dv(grip_f * 0x1d, 5); grip_r = dv(grip_r * 0x1d, 5);   /* traffic: x0.9 */
  }
  /* (4) Wheels: i even = front (steered), i odd = rear. */
  int32_t slip_front = 0, slip_rear = 0;
  wr32(obj + CAR_WHEELS_DOWN, 0);
  for (int32_t i = 3; i >= 0; i--) {
    uint8_t *w = obj + i * CAR_WHEEL_SIZE + CAR_WHEEL;
    int32_t wp[4] = { 0 }, nrm[4] = { 0 }, gnd[4] = { 0 };
    load_pt(model_pt(type, 0x38 + i * 2));
    RotVec_005279CB(wp);
    int32_t grip = P103_GroundAt(wp, nrm, gnd);
    int32_t gnd_y = gnd[1];
    if (is_player(obj)) {
      /* bump sound when the ground under this wheel jumps by more than 0x10 since last step */
      if (0x10 < W(L(gnd[1]) - P102_B2EA38[i])) {
        int quiet = P59_Mode1137324 == 2;
        if (P97_SndStart(0x1d, 0x10, (float)gnd[0], (float)-gnd[1], (float)gnd[2]) != -1) {
          SoundSetPos00523F8A(0x10, 5000);
          P48_SetVoiceVolume(0x10, quiet ? 0 : -7000);
        }
      }
      P102_B2EA38[i] = gnd_y;
    }
    grip = traction(obj, grip);
    if (!is_cur(obj) && oaddr(obj) < 0xd0cb08u && traffic_b(obj[CAR_ID], 2) != 1 && obj[CAR_MODEL] != 1) {
      /* simplified traffic: flat ground, fixed grip */
      nrm[0] = 0; nrm[1] = FX_ONE; nrm[2] = 0; grip = 0x2800;
    }
    w[WHEEL_SURFACE] = (uint8_t)P56_B2EA48;
    uint32_t prev_comp = w[WHEEL_COMPRESS];
    int32_t comp = W(L(gnd[1]) + 0x14 - wp[1]);
    if (obj[CAR_ID] == 0) P142_B2F304 = 0;
    if (comp < 0) comp = 0;
    if (obj[CAR_ID] == 0) { if (0x78 < comp || 0x30 < comp) ReturnZero004E3B19(); }   /* FFB jolt hook (no-op in this build) */
    if (SUSP_MAX < comp) comp = SUSP_MAX;
    if (comp == 0 && prev_comp == 0) { w[WHEEL_COMPRESS] = 0; continue; }   /* wheel in the air */
    int32_t spring = comp * SUSP_SPRING + (int32_t)prev_comp * -SUSP_DAMP;
    wp[0] = W(L(wp[0]) - st[ST_POS + 0]); wp[1] = W(L(wp[1]) - st[ST_POS + 1]); wp[2] = W(L(wp[2]) - st[ST_POS + 2]);   /* lever arm */
    int32_t pv_x = (W(L(st[ST_ANGVEL + 1]) * wp[2] - L(st[ST_ANGVEL + 2]) * wp[1] + FX_HALF) >> FX_SHIFT) + st[ST_VEL + 0];
    int32_t pv_z = (W(L(st[ST_ANGVEL + 0]) * wp[1] - L(st[ST_ANGVEL + 1]) * wp[0] + FX_HALF) >> FX_SHIFT) + st[ST_VEL + 2];
    /* lateral axis of the wheel (dir_x, dir_z): from the (steered) heading, or along the contact
       velocity when the wheel is locked (a locked wheel slides where it is going) */
    int32_t fz = 0, fx = 0, dir_x, dir_z;
    if (w[WHEEL_LOCKED] == 0) {
      if ((i & 1) == 0) { dir_x = cos_hs; dir_z = -sin_hs; } else { dir_x = cos_h; dir_z = -sin_h; }
    } else {
      uint32_t a = (uint32_t)P44_Atan2(dv(pv_x, 6), dv(pv_z, 6));
      dir_z = sn(((a & ANG_MASK) + ANG_90) & ANG_MASK);
      dir_x = sn(a & ANG_MASK);
    }
    int32_t lat_v = W(L(dv(pv_x, 6)) * dv(dir_x, 6) + L(dv(pv_z, 6)) * dv(dir_z, 6));   /* sideways speed of the contact */
    int32_t slip = iabs32(W(L(dv(slip_k, 6)) * dv(lat_v, 6)));
    int32_t lat_f;
    if (lat_v < 0x11941) {
      if (lat_v < -72000) lat_f = -LAT_FORCE_MAX;
      else {
        lat_f = W(L(slip_k) * lat_v + FX_HALF) >> FX_SHIFT;
        if (0x4650 < lat_f) lat_f = LAT_FORCE_MAX; else if (lat_f < -LAT_FORCE_MAX) lat_f = -LAT_FORCE_MAX;
      }
    } else lat_f = LAT_FORCE_MAX;
    int32_t throttle = rd32(obj + CAR_THROTTLE);
    if ((i & 1) == 0) {
      /* front wheel */
      int32_t t = W(L(grip_f) * lat_f + FX_HALF);
      lat_f = t >> FX_SHIFT;
      if (w[WHEEL_LOCKED] == 0) {
        if (obj[CAR_AI_DRIVEN] == 1) {   /* cops: front-wheel drive too */
          fx = W(L(sin_hs) * throttle + FX_HALF) >> FX_SHIFT;
          fz = W(L(cos_hs) * throttle + FX_HALF) >> FX_SHIFT;
          if (obj[CAR_ID] == 0) P142_B2F304 = W(L(P142_B2F304) + lat_f);
        } else if (obj[CAR_ID] == 0) P142_B2F304 = W(L(P142_B2F304) + L(lat_f) * -2);
      } else {
        /* locked front wheel: 3/4 of the force, projected back onto the steered direction */
        lat_f = ((t >> 13) + lat_f) >> 1;
        int32_t q = W(L(W(L(-lat_f) * dir_x + FX_HALF) >> FX_SHIFT) * cos_hs - L(W(L(-lat_f) * dir_z + FX_HALF) >> FX_SHIFT) * sin_hs + 0x400) >> 11;
        fx = W(L(q) * cos_hs + FX_HALF) >> FX_SHIFT;
        fz = W(L(-q) * sin_hs + FX_HALF) >> FX_SHIFT;
        if (obj[CAR_ID] == 0) P142_B2F304 = W(L(P142_B2F304) + q);
      }
      if (slip_front < slip) slip_front = slip;
    } else {
      /* rear wheel: driven */
      if (w[WHEEL_LOCKED] == 0) {
        lat_f = W(L(grip_r) * lat_f + FX_HALF) >> FX_SHIFT;
        int is_drv = obj[CAR_ID] == 0 || (obj[CAR_ID] == 0x41 && G6_00B87EA0 != 0 && P88_Mode575 == 2);
        if ((obj[CAR_ID] == 0 || obj[CAR_ID] == 0x41) &&
            ((is_drv && W(L(lat_f) * (int8_t)obj[CAR_STEER_DIR]) < 0) || 0 < W(L(lat_f) * rd32(obj + CAR_STEER)))) obj[CAR_STEER_HOLD] = 0xff;
        fx = W(L(-dir_z) * throttle + FX_HALF) >> FX_SHIFT;
        fz = W(L(dir_x) * throttle + FX_HALF) >> FX_SHIFT;
      } else lat_f = W(L(grip_f) * lat_f + 0x2000) >> 14;   /* locked rear wheel: quarter grip (uses grip_f, as in the original) */
      if (slip_rear < slip) slip_rear = slip;
    }
    /* total wheel force = (drive + spring * normal - lateral * dir + drag) * (grip + 500) / 4096 */
    int32_t fy = W(L(spring) * nrm[1] + FX_HALF + drag_y) >> FX_SHIFT;
    fx = W(L(W(L(fx) + (W(L(spring) * nrm[0] - L(lat_f) * dir_x + FX_HALF + drag_x) >> FX_SHIFT))) * (grip + 500)) >> FX_SHIFT;
    fz = W(L(W(L(fz) + (W(L(spring) * nrm[2] - L(lat_f) * dir_z + FX_HALF + drag_z) >> FX_SHIFT))) * (grip + 500)) >> FX_SHIFT;
    if (rd16(obj + CAR_MAT_YY) < 0x800) {
      /* tilted more than 60 degrees: fade horizontal forces by 1 - (1 - up_y)^2 */
      int32_t t = FX_ONE - rd16(obj + CAR_MAT_YY);
      int32_t fade = (t < 0x1001) ? FX_ONE - (W(L(t) * t + FX_HALF) >> FX_SHIFT) : 0;
      fx = W(L(fx) * fade + FX_HALF) >> FX_SHIFT;
      fz = W(L(fz) * fade + FX_HALF) >> FX_SHIFT;
    }
    /* shorten the vertical lever arm (less body roll): cops by difficulty, others x5/16 */
    if (obj[CAR_AI_DRIVEN] == 1) wp[1] = dv(W(L(wp[1]) * (WI00B87E2C == 2 ? 7 : 8)), 5);
    else wp[1] = dv(W(L(wp[1]) * 5), 4);
    if (P98_MrkOff == 0 || obj[CAR_ID] != 0) {
      /* force += f; torque += r x f */
      st[ST_TORQUE + 2] = W(L(st[ST_TORQUE + 2]) - (W(L(wp[1]) * fx + FX_HALF) >> FX_SHIFT));
      st[ST_TORQUE + 1] = W(L(st[ST_TORQUE + 1]) + (W(L(wp[2]) * fx + FX_HALF) >> FX_SHIFT));
      st[ST_FORCE + 0] = W(L(st[ST_FORCE + 0]) + fx);
      st[ST_TORQUE + 0] = W(L(st[ST_TORQUE + 0]) - (W(L(wp[2]) * fy + FX_HALF) >> FX_SHIFT));
      st[ST_TORQUE + 2] = W(L(st[ST_TORQUE + 2]) + (W(L(wp[0]) * fy + FX_HALF) >> FX_SHIFT));
      st[ST_FORCE + 1] = W(L(st[ST_FORCE + 1]) + fy);
      st[ST_TORQUE + 1] = W(L(st[ST_TORQUE + 1]) - (W(L(wp[0]) * fz + FX_HALF) >> FX_SHIFT));
      st[ST_TORQUE + 0] = W(L(st[ST_TORQUE + 0]) + (W(L(wp[1]) * fz + FX_HALF) >> FX_SHIFT));
      st[ST_FORCE + 2] = W(L(st[ST_FORCE + 2]) + fz);
    } else {
      /* player during the marker effect: only a fixed upward kick (stronger at the front) */
      int32_t up = ((i & 1) == 0) ? 0x23000 : 0xb000;
      st[ST_TORQUE + 0] = W(L(st[ST_TORQUE + 0]) - (W(L(wp[2]) * up + FX_HALF) >> FX_SHIFT));
      st[ST_TORQUE + 2] = W(L(st[ST_TORQUE + 2]) + (W(L(wp[0]) * up + FX_HALF) >> FX_SHIFT));
      st[ST_FORCE + 1] = W(L(st[ST_FORCE + 1]) + up);
    }
    w[WHEEL_COMPRESS] = (uint8_t)comp;
    add32(obj + CAR_WHEELS_DOWN, 1);
  }
  /* (5) Forward speed: both rear wheels in the air -> from the throttle alone (free-spinning wheels),
     otherwise the velocity projected on the heading. */
  if (obj[CAR_WHEEL + 1 * CAR_WHEEL_SIZE + WHEEL_COMPRESS] == 0 && obj[CAR_WHEEL + 3 * CAR_WHEEL_SIZE + WHEEL_COMPRESS] == 0) {
    int32_t t = rd32(obj + CAR_THROTTLE);
    wr32(obj + CAR_FWD_SPEED, t < 1 ? (t >= 0 ? 0 : (int32_t)0xffed4000u) : 0x1a4000);
  } else {
    wr32(obj + CAR_FWD_SPEED, W(L(dv(st[ST_VEL + 0], 6)) * dv(sin_h, 6) + L(dv(st[ST_VEL + 2], 6)) * dv(cos_h, 6)));
  }
  wr32(obj + CAR_SLIP_FRONT, slip_front);
  wr32(obj + CAR_SLIP_REAR, slip_rear);
  P94_SpringStep(obj, (uint8_t *)st);
  obj[CAR_OVERLAP] = 0; obj[CAR_OVERLAP + 1] = 0;
  if (obj[CAR_ID] == 0) P35_PadX = dv(W(L(P35_PadX) * 3 + P142_B2F304), 2);   /* force-feedback X: smoothed steering load */
}

/* ---------------- 004dacee ---------------- */
static uint8_t *blk(p102_d68_t b, int32_t i) { return &b[i * 0x34]; }   /* i-th 0x34-byte (13 int32) body-state slot */
/* clamp an angular-velocity component to +-0x1000000 */
static void clamp24(uint8_t *p) {
  int32_t v = rd32(p);
  if (0x1000000 < v) wr32(p, 0x1000000); else if (v < -0x1000000) wr32(p, -0x1000000);
}
/* Collision impulse on body-state slot r (P102_BlkB/BlkC, 13 int32: +0x1c velocity, +0x28 angular velocity):
   velocity += sign * g; angular velocity += k * (r x g) with the cross product order picked by sign
   (sign < 0: g x arm, i.e. -(arm x g)). */
static void impulse(uint8_t *r, const int32_t *g, const int32_t *arm, int32_t k, int32_t sign) {
  for (int m = 0; m < 3; m++) add32(r + 0x1c + m * 4, sign * g[m]);
  int32_t t0, t1, t2;
  if (sign < 0) {   /* a: (g × arm) */
    t0 = W(L(g[1]) * arm[2] - L(g[2]) * arm[1] + 0x800) >> 12;
    t1 = W(L(g[2]) * arm[0] - L(g[0]) * arm[2] + 0x800) >> 12;
    t2 = W(L(g[0]) * arm[1] - L(g[1]) * arm[0] + 0x800) >> 12;
  } else {          /* b: (arm × g) */
    t0 = W(L(arm[1]) * g[2] - L(arm[2]) * g[1] + 0x800) >> 12;
    t1 = W(L(arm[2]) * g[0] - L(arm[0]) * g[2] + 0x800) >> 12;
    t2 = W(L(arm[0]) * g[1] - L(arm[1]) * g[0] + 0x800) >> 12;
  }
  add32(r + 0x28, W(L(t0) * k)); add32(r + 0x2c, W(L(t1) * k)); add32(r + 0x30, W(L(t2) * k));
}
/* Velocity of a body point: o = v + w x arm, for a 13-int32 body state p (+0x1c velocity, +0x28 angular velocity). */
static void body_pt(const uint8_t *p, const int32_t *arm, int32_t *o) {   /* p: состояние (+0x1c позиция, +0x28 угл. скорость) */
  o[0] = (W(L(rd32(p + 0x2c)) * arm[2] - L(rd32(p + 0x30)) * arm[1] + 0x800) >> 12) + rd32(p + 0x1c);
  o[1] = (W(L(rd32(p + 0x30)) * arm[0] - L(rd32(p + 0x28)) * arm[2] + 0x800) >> 12) + rd32(p + 0x20);
  o[2] = (W(L(rd32(p + 0x28)) * arm[1] - L(rd32(p + 0x2c)) * arm[0] + 0x800) >> 12) + rd32(p + 0x24);
}

/* P142_CarsStep — Game.exe 004dacee, cdecl, no arguments.
   One physics step for every car in the active-car list G6_00B2F30C[0..n) (n = G6_00D0DDC0).
   Steps: (1) broad phase P103_CarsOverlap marks cars whose boxes overlap (CAR_OVERLAP);
        (2) per car: apply half of the last force/torque to velocity/angular velocity, stop very slow
            cars, clamp spin; cars not overlapping are integrated directly (position += vel >> 9,
            quaternion += 0.5 * w * q);
        (3) overlapping cars: 4 passes x 2 half-steps (midpoint method) with pairwise narrow phase
            P102_CarsHit (only pairs closer than 0x4b0 on every axis): damage, sparks/smoke/sound on
            hard hits, and equal-and-opposite impulses (mission/chase targets and cops are weighted);
        (4) per car: heading from the matrix, Euler angles for cars that need them, copy position to
            CAR_POS, integer velocity, ground points under the wheels.
   The native-only blocks under #ifndef RE_HOOK_BUILD at the top are debug helpers driven by
   environment variables (RE_CARDBG log line, RE_TELEPORT, RE_AUTOTARGET, RE_AUTORAM); they do not run
   unless the variable is set.  RE_CARDBG output is the reference for the deterministic regression run,
   so its format must not change. */
void P142_CarsStep(void) {
  int32_t n = G6_00D0DDC0;
#ifndef RE_HOOK_BUILD
  { static int k; if (getenv("RE_CARDBG") && (k++ % atoi(getenv("RE_CARDBG"))) == 0) { uint8_t *c = (uint8_t *)&P99_Cars[0];
    fprintf(stderr, "[car] n %d o0 %s 13c %d 110 %d pos %d %d %d p24 %d %d %d v %d %d %d f8 %d fc %d 104 %d 108 %d 10c %d o3 %d\n", n, (n > 0 && G6_00B2F30C[0] == c) ? "car0" : "?",
      rd16(c + 0x13c), rd32(c + 0x110), rd32(c + 0x18), rd32(c + 0x1c), rd32(c + 0x20), rd32(c + 0x24), rd32(c + 0x28), rd32(c + 0x2c), rd32(c + 0x40), rd32(c + 0x44), rd32(c + 0x48),
      rd32(c + 0xf8), rd32(c + 0xfc), rd32(c + 0x104), rd32(c + 0x108), rd32(c + 0x10c), c[3]); } }
  re_probe_step();   /* RE_PROBE (reprobe.h): read-only, returns at once when unset */
  { /* v2.21: RE_TELEPORT="кадр:x:z;кадр:x:z…" (v2.25: до 64 точек) — отладка прохождения миссий (как RE_COPNEAR): на кадре P62_Frame машина игрока
       переносится в (x, z): позиция +0x18/+0xc8 и fixed ×16 +0x24, скорости +0x40..+0x74 обнуляются, высота и курс прежние */
    static int tn = -1; static int32_t tf[64], tx[64], tz[64];   /* v2.25: до 64 точек (обход клеток интервью) */
    if (tn < 0) { tn = 0; const char *e = getenv("RE_TELEPORT");
      while (e && *e && tn < 64) { int32_t f, x, z;
        if (sscanf(e, "%d:%d:%d", &f, &x, &z) != 3) break;
        tf[tn] = f; tx[tn] = x; tz[tn] = z; tn++; e = strchr(e, ';'); if (e) e++; } }
    for (int t = 0; t < tn; t++) if ((int32_t)P62_Frame == tf[t]) {
      uint8_t *c = (uint8_t *)&P99_Cars[0];
      wr32(c + 0x18, tx[t]); wr32(c + 0x20, tz[t]); wr32(c + 0x24, tx[t] * 16); wr32(c + 0x2c, tz[t] * 16);
      P99_Cars[0].pos[0] = tx[t]; P99_Cars[0].pos[2] = tz[t];
      for (int m = 0x40; m < 0x78; m += 4) wr32(c + m, 0);
      P88_TeleportReload = 1;   /* v2.29: блоки карты вокруг нового места */
      fprintf(stderr, "[teleport] кадр %d → %d %d\n", (int)P62_Frame, (int)tx[t], (int)tz[t]);
    }
  }
  { /* v2.29: RE_AUTOTARGET=N[:D] — отладка прохождения кампании: с кадра P62_Frame N (каждой миссии) машина игрока переносится
       к включённой цели скрипта миссии (00c80ce0 + i·0x34: +0x10 флаги, 1 — включена, 8 — цель-событие; +0 радиус, +0x14 x, +0x1c z),
       если цель включена не меньше D кадров (по умолчанию 150) и игрок дальше трети радиуса. Засчитывает цель игра сама
       (P115_TargetTick/скрипт), перенос только заменяет езду; цели-события (машина) не трогаются — только журнал. */
    static int on = -1; static int32_t from = 0, delay = 150, seen[10], since[10];
    if (on < 0) { const char *e = getenv("RE_AUTOTARGET"); on = e != NULL; if (e) { from = atoi(e); const char *c = strchr(e, ':'); if (c) delay = atoi(c + 1); } }
    if (on && (int32_t)P62_Frame >= from && P99_Cars[0].pos[0] | P99_Cars[0].pos[2] &&
        !(getenv("RE_AUTORAM") && (P58_SB87EB0 | G6_00B87EB0 | G6_00B87EAC) != 0)) {   /* v2.30: в погоне — RE_AUTORAM */
      uint8_t *c = (uint8_t *)&P99_Cars[0];
      for (int i = 0; i < 10; i++) {
        const uint8_t *o = P58_Objs[i];
        int32_t fl = (int32_t)rd32(o + 0x10), rad = (int32_t)rd32(o), x = (int32_t)rd32(o + 0x14), z = (int32_t)rd32(o + 0x1c);
        int32_t key = (fl & 9) == 1 ? (x ^ (z << 1) ^ rad) | 1 : 0;
        if (key != seen[i] || (int32_t)P62_Frame < since[i]) { seen[i] = key; since[i] = (int32_t)P62_Frame;
          if (fl & 1) fprintf(stderr, "[autotarget] кадр %d: цель %d флаги %x радиус %d (%d, %d)%s\n", (int)P62_Frame, i, (unsigned)fl, (int)rad,
                              (int)x, (int)z, (fl & 8) ? " — событие, не переносим" : ""); }
        if (key == 0 || (int32_t)P62_Frame - since[i] < delay) continue;
        double dx = (double)x - (int32_t)rd32(c + 0x18), dz = (double)z - (int32_t)rd32(c + 0x20);
        if (dx * dx + dz * dz <= ((double)rad / 3) * ((double)rad / 3)) continue;
        wr32(c + 0x18, x); wr32(c + 0x20, z); wr32(c + 0x24, x * 16); wr32(c + 0x2c, z * 16);
        P99_Cars[0].pos[0] = x; P99_Cars[0].pos[2] = z;
        for (int m = 0x40; m < 0x78; m += 4) wr32(c + m, 0);
        P88_TeleportReload = 1;
        fprintf(stderr, "[autotarget] w=%d кадр %d → цель %d (%d, %d), было в %.0f\n", plat_frame_no(), (int)P62_Frame, i, (int)x, (int)z, sqrt(dx * dx + dz * dz));
        break;
      }
    }
  }
  { /* v2.30: RE_AUTORAM=N[:P[:B]] — отладка кампании, погоня/таран: в режиме погони (00b87eb0/00b87eac — цель в слоте 0x41,
       «You lost your target» по удалению, 004d4f5c) с кадра N каждые P кадров (по умолчанию 60) машина игрока ставится в B единиц
       (по умолчанию 900) позади цели по её скорости/курсу, с её ориентацией и скоростью цели + разгон к ней — удар засчитывает
       физика и скрипт игры; без режима погони — ничего (журнал раз в 100 кадров). Только native, только при переменной. */
    static int on = -1; static int32_t from = 0, per = 60, back = 900, ptx, ptz, pfr = -9, ppx, ppz, sgn = 1, tpf = -1, lpx, lpz; static double vk = 8192.0, close = 8.0; static int ycopy = 1; static double far = 3000.0;
    static double svx, svz;   /* скорость цели по смещению (ед. позиции/кадр), сглаженная */
    if (on < 0) { const char *e = getenv("RE_AUTORAM"); on = e != NULL;
      if (e) { from = atoi(e); const char *c = strchr(e, ':'); if (c) { per = atoi(c + 1); c = strchr(c + 1, ':'); if (c) back = atoi(c + 1); } }
      if (per < 1) per = 60;
      const char *g = getenv("RE_AUTORAM_SIGN"); if (g) sgn = atoi(g); const char *fz = getenv("RE_AUTORAM_FAR"); if (fz) far = atof(fz);
      const char *vz = getenv("RE_AUTORAM_VK"); if (vz) vk = atof(vz);
      const char *cl = getenv("RE_AUTORAM_CLOSE"); if (cl) close = atof(cl);
      const char *yc = getenv("RE_AUTORAM_Y"); if (yc) ycopy = atoi(yc); }
    int32_t chase = (P58_SB87EB0 | G6_00B87EB0 | G6_00B87EAC) != 0;
    if (on && (int32_t)P62_Frame >= from && P99_Cars[0].pos[0] | P99_Cars[0].pos[2]) {
      uint8_t *c = (uint8_t *)&P99_Cars[0], *t = (uint8_t *)&P99_Cars[0x41];
      int32_t tx = P99_Cars[0x41].pos[0], tz = P99_Cars[0x41].pos[2];
      { /* v2.31: цель — как 004f5012 (P98_ScriptRange): объект скрипта k (флаги 1|8, порог 00b87e60[k]) → узел списка 00d12408
           (32-битный адрес в ячейке образа G00D12408 — его пишет 0x7a/ported122; native P15_ListHead — расщеплённый псевдоним, пуст; флаг 8, +6 = объект+0xc) → +0x1c — позиция цели (float x, z); слот 0x41 — запасной вариант (RE_AUTORAM_SLOT=1 — только слот) */
        static int slot = -1; if (slot < 0) { const char *sl = getenv("RE_AUTORAM_SLOT"); slot = sl ? atoi(sl) : 0; }
        int found = 0;
        for (int32_t pass = 0, k = 0; !slot && !found && P97_ScrObjOn && pass < 2; k = (k + 1) % 10, pass += k == 0) {
          /* проход 0 — как 004f5012 (порог, флаги 1|8); проход 1 — любой включённый объект (флаг 1) с узлом в списке (цель-событие) */
          const uint8_t *o = P58_Objs[k]; uint32_t f = (uint32_t)rd32(o + 0x10);
          if (pass == 0 ? (P98_Range[k] == 0 || (f & 1) == 0 || (f & 8) == 0) : (f & 1) == 0) continue;
          for (uint8_t *nd = (uint8_t *)re_ptr((uint32_t)G00D12408); nd != NULL; nd = (uint8_t *)re_rd_ptr(nd + 0x20)) {
            if ((rd16(nd) & 8) != 0 && (uint32_t)rd16(nd + 6) == (uint32_t)rd32(o + 0xc)) {
              const uint8_t *tc = (const uint8_t *)re_rd_ptr(nd + 0x1c);
              if (tc != NULL) { float fx, fz; memcpy(&fx, tc, 4); memcpy(&fz, tc + 8, 4); tx = (int32_t)lrintf(fx); tz = (int32_t)lrintf(fz); found = 1;
                if (((int32_t)P62_Frame % 100) == 0) fprintf(stderr, "[autoram] кадр %d: цель по списку 00d12408 — объект %d (проход %d, флаги %x), порог %d, (%d, %d)\n", (int)P62_Frame, (int)k, (int)pass, (unsigned)f, (int)P98_Range[k], (int)tx, (int)tz); }
              break;
            }
          }
        }
        if (found && !chase) chase = 1;
        if (!found && !slot && ((int32_t)P62_Frame % 500) == 0) {
          int nn = 0; for (uint8_t *nd = (uint8_t *)re_ptr((uint32_t)G00D12408); nd != NULL && nn < 1000; nd = (uint8_t *)re_rd_ptr(nd + 0x20)) nn++;
          fprintf(stderr, "[autoram] кадр %d: по списку 00d12408 цели нет (объекты скрипта %d, узлов %d; пороги", (int)P62_Frame, (int)P97_ScrObjOn, nn);
          for (int k = 0; k < 10; k++) fprintf(stderr, " %d/%x", (int)P98_Range[k], (unsigned)rd32(P58_Objs[k] + 0x10));
          fprintf(stderr, ") — слот 0x41\n");
        }
      }
      double dx = (double)tx - P99_Cars[0].pos[0], dz = (double)tz - P99_Cars[0].pos[2], d = sqrt(dx * dx + dz * dz);
      if (((int32_t)P62_Frame % 100) == 0)
        fprintf(stderr, "[autoram] кадр %d: погоня %d (eb0 %d eac %d), цель 0x41 (%d, %d) скорость %d, до цели %.0f, урон цели %d\n", (int)P62_Frame,
                (int)chase, (int)(P58_SB87EB0 | G6_00B87EB0), (int)G6_00B87EAC, (int)tx, (int)tz, (int)P99_Cars[0x41].speed, d, (int)P99_Cars[0x41].f13c);
      (void)t;
      if ((int32_t)P62_Frame == pfr + 1) { svx = svx * 0.8 + 0.2 * (tx - ptx); svz = svz * 0.8 + 0.2 * (tz - ptz); }
      else { svx = 0; svz = 0; }
      ptx = tx; ptz = tz; pfr = (int32_t)P62_Frame;
      if (chase && (tx | tz)) {   /* руление штатными клавишами: к цели, газ; ближе 1500 и не в лоб — полный газ */
        extern void plat_auto_key(int dik);
        double want = atan2(dx, dz) * 4096.0 / 6.283185307179586; int32_t h = P99_Cars[0].heading & 0xfff;
        int32_t diff = ((int32_t)want - h) & 0xfff; if (diff > 0x800) diff -= 0x1000;
        if (sgn < 0) diff = -diff;
        if (diff > 60) plat_auto_key(0xcd); else if (diff < -60) plat_auto_key(0xcb);   /* RIGHT / LEFT */
        if ((diff > 0x600 || diff < -0x600) && d < 2000.0) plat_auto_key(0xd0); else plat_auto_key(0xc8);   /* задний / газ */
        if (tpf > 0 && (int32_t)P62_Frame - tpf <= 6) {   /* калибровка: смещение игрока после переноса */
          fprintf(stderr, "[autoram] +%d: игрок шаг (%d, %d), цель шаг (%.0f, %.0f)\n", (int)P62_Frame - tpf, (int)(P99_Cars[0].pos[0] - lpx),
                  (int)(P99_Cars[0].pos[2] - lpz), svx, svz); }
        lpx = P99_Cars[0].pos[0]; lpz = P99_Cars[0].pos[2];
        if (((int32_t)P62_Frame % 50) == 0) {
          double pvx = P99_Cars[0].pos[0] - ppx, pvz = P99_Cars[0].pos[2] - ppz;
          fprintf(stderr, "[autoram] кадр %d: курс %d, к цели %d, разн %d, движение игрока %.0f° (%.0f, %.0f)/50к\n", (int)P62_Frame, (int)h,
                  (int)want & 0xfff, (int)diff, atan2(pvx, pvz) * 4096.0 / 6.283185307179586, pvx, pvz);
          ppx = P99_Cars[0].pos[0]; ppz = P99_Cars[0].pos[2];
        }
      }
      if (chase && (tx | tz) && ((int32_t)P62_Frame - from) % per == 0 && d > far) {
        double vx = svx, vz = svz, v = sqrt(vx * vx + vz * vz);
        if (v < 1.0) { int32_t h = P99_Cars[0x41].heading & 0xfff; vx = P59_Sin[h]; vz = P59_Sin[(h + 0x400) & 0xfff]; v = sqrt(vx * vx + vz * vz); }
        if (v > 0.0) {
          double ux = vx / v, uz = vz / v;
          int32_t nx = tx - (int32_t)(ux * back), nz = tz - (int32_t)(uz * back);
          P99_Cars[0].pos[0] = nx; P99_Cars[0].pos[2] = nz;
          if (ycopy) {   /* высота: дорога под новым местом − смещение модели (как 004b9b1b для машин трафика) */
            uint32_t mi = P99_Cars[0].f00[2]; int32_t off = 0;
            if ((mi + 1) * 0x16c <= sizeof S_00D0CC60) off = (int16_t)(S_00D0CC60[mi * 0x16c + 0xe2] | (S_00D0CC60[mi * 0x16c + 0xe3] << 8));
            P99_Cars[0].pos[1] = P100_RoadHeight(P99_Cars[0].pos) - off;
          }
          for (int m = 0x40; m < 0x78; m += 4) wr32(c + m, 0);
          /* курс по направлению движения цели; 004daac7 (P59_ObjDir): позиция 1/16, кватернион из курса, матрица */
          P99_Cars[0].heading = (int32_t)(atan2(ux, uz) * 4096.0 / 6.283185307179586) & 0xfff;
          P99_Cars[0].ang[1] = (int16_t)P99_Cars[0].heading;
          P59_ObjDir(c, 1);
          wr32(c + 0x18, nx); wr32(c + 0x1c, P99_Cars[0].pos[1]); wr32(c + 0x20, nz);
          /* скорость: смещение/кадр → +0x40 (x16 << 9 = 8192 на ед./кадр), +15 ед./кадр сближения */
          wr32(c + 0x40, (int32_t)((svx + ux * close) * vk)); wr32(c + 0x48, (int32_t)((svz + uz * close) * vk));
          P88_TeleportReload = 1; tpf = (int32_t)P62_Frame;
          fprintf(stderr, "[autoram] w=%d кадр %d → позади цели (%d, %d), было до цели %.0f; y игрока %d/%d, y цели %d/%d\n", plat_frame_no(), (int)P62_Frame,
                  (int)nx, (int)nz, d, (int)P99_Cars[0].pos[1], (int)rd32(c + 0x1c), (int)P99_Cars[0x41].pos[1], (int)rd32(t + 0x1c));
        }
      }
    }
  }
#endif
  if (n > (int32_t)(sizeof P102_BlkA / 0x34)) n = (int32_t)(sizeof P102_BlkA / 0x34);
  if (P102_D0DD7C != 0) P102_D0DD7C--;   /* cool-down of the "rammed a target" counter below */
  P46_UpdateObjects();
  P103_CarsOverlap();
  /* (2) Apply forces, then integrate cars that are not in contact with another car. */
  for (int32_t i = 0; i < n; i++) {
    uint8_t *o = G6_00B2F30C[i];
    if (o == NULL) continue;
    for (int m = 0; m < 3; m++) {
      wr32(o + CAR_DVEL_PEND + m * 4, rd32(o + CAR_DVEL_PEND + m * 4) >> 1);
      add32(o + CAR_VEL + m * 4, rd32(o + CAR_DVEL_PEND + m * 4));
    }
    for (int m = 0; m < 3; m++) {
      wr32(o + CAR_DANGVEL_PEND + m * 4, rd32(o + CAR_DANGVEL_PEND + m * 4) >> 1);
      add32(o + CAR_ANGVEL + m * 4, rd32(o + CAR_DANGVEL_PEND + m * 4));
    }
    wr32(o + CAR_DANGVEL_PEND + 0, 0); wr32(o + CAR_DANGVEL_PEND + 4, 0); wr32(o + CAR_DANGVEL_PEND + 8, 0);
    if (rd32(o + CAR_SPEED) == 0) {
      /* at rest: drop residual velocity below 1000 (sum of |components|), otherwise wake up */
      int32_t s = W(L(iabs32(rd32(o + CAR_VEL + 0))) + iabs32(rd32(o + CAR_VEL + 4)) + iabs32(rd32(o + CAR_VEL + 8)));
      if (s < 1000) { wr32(o + CAR_VEL + 0, 0); wr32(o + CAR_VEL + 4, 0); wr32(o + CAR_VEL + 8, 0); }
      else wr32(o + CAR_SPEED, 1);
    }
    clamp24(o + CAR_ANGVEL + 0); clamp24(o + CAR_ANGVEL + 4); clamp24(o + CAR_ANGVEL + 8);
    if (G6_00B87EAC != 0 || G6_00B87EB0 != 0) wr16(o + CAR_OVERLAP, 1);   /* chase modes: always the precise path */
    if (G6_00B87EA0 != 0) wr16(o + CAR_OVERLAP, 0);                     /* director/replay camera mode: never */
    if (rd16(o + CAR_OVERLAP) == 0) {
      /* position (<<4) += velocity >> 9 */
      add32(o + CAR_POS_HI + 0, rd32(o + CAR_VEL + 0) >> 9);
      add32(o + CAR_POS_HI + 4, rd32(o + CAR_VEL + 4) >> 9);
      add32(o + CAR_POS_HI + 8, rd32(o + CAR_VEL + 8) >> 9);
      /* quaternion += (w, 0) * q / 2, with w rounded to >> 13 */
      int32_t wx = W(L(rd32(o + CAR_ANGVEL + 0)) + 0x1000) >> 13, wy = W(L(rd32(o + CAR_ANGVEL + 4)) + 0x1000) >> 13, wz = W(L(rd32(o + CAR_ANGVEL + 8)) + 0x1000) >> 13;
      int32_t qx = rd32(o + CAR_QUAT + 0), qy = rd32(o + CAR_QUAT + 4), qz = rd32(o + CAR_QUAT + 8), qw = rd32(o + CAR_QUAT + 12);
      int32_t dqx = W(-L(qy) * wz + L(qz) * wy + FX_HALF + L(qw) * wx);
      int32_t dqy = W(L(qx) * wz - L(qz) * wx + FX_HALF + L(qw) * wy);
      int32_t dqz = W(-L(qx) * wy + L(qy) * wx + FX_HALF + L(qw) * wz);
      int32_t dqw = W(-L(qx) * wx - L(qy) * wy - L(qz) * wz + FX_HALF);
      add32(o + CAR_QUAT + 0, dqx >> 13); add32(o + CAR_QUAT + 4, dqy >> 13); add32(o + CAR_QUAT + 8, dqz >> 13); add32(o + CAR_QUAT + 12, dqw >> 13);
      P56_ObjSync((int32_t *)(void *)(o + CAR_BODY), o);   /* body state -> matrix / integer position */
    }
  }
  /* (3) Cars in contact: 4 passes, each a midpoint step (s = 0: derivative at the start -> P102_BlkB,
     half step into P102_BlkA; s = 1: derivative at the half step -> P102_BlkC, full step from
     (BlkB + BlkC) >> 4).  Pair impulses are added to the derivative slots. */
  for (int32_t pass = 0; pass < 4; pass++) {
    for (int32_t s = 0; s < 2; s++) {
      for (int32_t i = 0; i < n; i++) {
        uint8_t *a = G6_00B2F30C[i];
        if (a == NULL || rd16(a + CAR_OVERLAP) == 0) continue;
        uint8_t *pa = (s == 0) ? a + CAR_BODY : blk(P102_BlkA, i);
        uint8_t *bb = (s == 0) ? P102_BlkB : P102_BlkC;
        P94_PackState(pa, (int32_t *)(void *)(bb + i * 0x34));
        if (P95_B87E14 != 0 || G6_00B87EA0 != 0) continue;   /* collisions off (cutscene / director) */
        for (int32_t j = 0; j < i; j++) {
          uint8_t *b = G6_00B2F30C[j];
          if (b == NULL) continue;
          uint8_t *pb = (0 < s) ? blk(P102_BlkA, j) : b + CAR_BODY;
          if (rd16(b + CAR_OVERLAP) == 0 || (rd32(b + CAR_SPEED) == 0 && rd32(a + CAR_SPEED) == 0)) continue;
          int32_t ap[3] = { rd32(a + CAR_POS2 + 0), rd32(a + CAR_POS2 + 4), rd32(a + CAR_POS2 + 8) };
          int32_t bp[3] = { rd32(b + CAR_POS2 + 0), rd32(b + CAR_POS2 + 4), rd32(b + CAR_POS2 + 8) };
          int32_t dd[3] = { W(L(bp[0]) - ap[0]), W(L(bp[1]) - ap[1]), W(L(bp[2]) - ap[2]) };
          if (!(dd[0] < 0x4b1 && -0x4b1 < dd[0] && dd[1] < 0x4b1 && -0x4b1 < dd[1] && dd[2] < 0x4b1 && -0x4b1 < dd[2])) continue;
          int32_t depth = 0, hit[4] = { 0 }, nv[4] = { 0 }, q[4] = { 0 };   /* penetration, contact point, normal */
          if (P102_CarsHit(a, b, &depth, hit, nv, q) == 0) continue;
          int32_t j_mag = (int32_t)((uint32_t)depth << 15);
          hit[1] = W(L(hit[1]) + 0x46);
          int32_t ea[3] = { W(L(hit[0]) - ap[0]), W(L(hit[1]) - ap[1]), W(L(hit[2]) - ap[2]) };   /* lever arms */
          int32_t eb[3] = { W(L(hit[0]) - bp[0]), W(L(hit[1]) - bp[1]), W(L(hit[2]) - bp[2]) };
          if (j == 0 || 0x40 < j) eb[1] -= 0x32;
          int32_t vb[3], va[3], r[3];
          body_pt(pb, eb, vb);
          body_pt(pa, ea, va);
          for (int m = 0; m < 3; m++) r[m] = W(L(va[m]) - vb[m]);
          /* closing speed along the normal */
          int32_t closing = W(L(dv(r[0], 8)) * dv(nv[0], 5) + L(dv(r[1], 8)) * dv(nv[1], 5) + L(dv(r[2], 8)) * dv(nv[2], 5));
          if (0 < closing && s == 0) {
            if (a[CAR_AI_DRIVEN] != 1 || b[CAR_AI_DRIVEN] != 1) {   /* cop-on-cop hits do no damage */
              /* G00BDFA50 / G00BDFA58: player / model-1 cars invulnerable (cheat or mode flags; TODO(RE): which).
                 Quirk kept: the second test checks a[CAR_MODEL], not b[CAR_MODEL]. */
              if ((G00BDFA50 == 0 || a[CAR_ID] != 0) && (G00BDFA58 == 0 || a[CAR_MODEL] != 1) && P103_CarDamage(a, ea, closing) != 0) a[CAR_DAMAGED] = 1;
              if ((G00BDFA50 == 0 || b[CAR_ID] != 0) && (G00BDFA58 == 0 || a[CAR_MODEL] != 1) && P103_CarDamage(b, eb, closing) != 0) b[CAR_DAMAGED] = 1;
            }
            if (0x5000 < closing) {   /* hard hit: debris, smoke, crash sound, FFB */
              const uint8_t *src = (a[CAR_ID] == 0 || 0x40 < a[CAR_ID]) ? a : b;
              int32_t v[4];
              v[0] = dv(rd32(src + CAR_VEL + 0), 12); v[2] = dv(rd32(src + CAR_VEL + 8), 12); v[1] = -17; v[3] = 0;
              hit[0] = W(L(hit[0]) - q[0]); hit[2] = W(L(hit[2]) - q[2]);
              hit[1] = W(-(L(W(L(hit[1]) - 0x46)) - q[1]));
              P125_ObjABurst(hit, v, 6, 1);
              hit[1] = -hit[1];
              if (a[CAR_ID] == 0 || b[CAR_ID] == 0) {
                if (P62_HudOff2 != 0) P44_Rst_B31EA0 = 1;
                ReturnZero004E3B19();
              }
              P125_SmokePuffs(hit, v, 2, 1, a[CAR_MODEL]);
              P125_SmokePuffs(hit, v, 4, 0, a[CAR_MODEL]);
              P125_SmokePuffs(hit, v, 2, 1, b[CAR_MODEL]);
              P125_SmokePuffs(hit, v, 4, 0, b[CAR_MODEL]);
              P97_SndStart(3, 3, (float)hit[0], (float)hit[1], (float)hit[2]);
            }
          }
          /* impulse magnitude: penetration + 9/4 closing speed, capped */
          j_mag = W(L(j_mag) + dv(W(L(closing) * 9), 2));
          if (0x190000 < j_mag) j_mag = 0x190000;
          {
            int32_t kk = j_mag >> 3;
            for (int m = 0; m < 3; m++) nv[m] = W(L(nv[m] >> 3) * kk) >> 6;
          }
          /* apply_b/apply_a: whether each side receives the impulse; spin: angular factor.
             In chase/target modes the target (slot > 0x40, or player/model-1 under the flags above)
             is immovable for the other side and the spin factor drops. */
          int32_t apply_b = 1, apply_a = 1, spin = 0x37;
          if (G6_00B87EB0 != 0 || G6_00B87EAC != 0 || G00BDFA50 != 0 || G00BDFA58 != 0) {
            if (0x40 < b[CAR_ID] || (G00BDFA50 != 0 && b[CAR_ID] == 0) || (G00BDFA58 != 0 && b[CAR_MODEL] == 1)) {
              spin = 0x1b;
              if (a[CAR_ID] == 0 && P102_D0DD7C == 0 && 8000 < closing) { P102_D0DD7C = 0x32; P95_BDFA0C++; }   /* player rammed the target */
              apply_b = 0;
            }
            if (0x40 < a[CAR_ID] || (G00BDFA50 != 0 && a[CAR_ID] == 0) || (G00BDFA58 != 0 && a[CAR_MODEL] == 1)) {
              spin >>= 1;
              if (b[CAR_ID] == 0 && P102_D0DD7C == 0 && 8000 < closing) { P102_D0DD7C = 0x32; P95_BDFA0C++; }
              apply_a = 0;
            }
          }
          int32_t g[3];
          if (apply_a != 0) {
            for (int m = 0; m < 3; m++) {
              if (a[CAR_AI_DRIVEN] == 1 && b[CAR_AI_DRIVEN] != 1 && b[CAR_ID] != 0) g[m] = dv(W(L(nv[m]) * (7 - WI00B87E2C)), 3);   /* cop hit by traffic: lighter push on harder difficulty */
              else if (a[CAR_MODEL] == 6 && b[CAR_MODEL] != 6) g[m] = (int32_t)((uint32_t)nv[m] << 1) / 3;   /* model 6 is heavier: 2/3 */
              else g[m] = nv[m];
            }
            impulse(bb + i * 0x34, g, ea, spin, -1);
          }
          if (apply_b != 0) {
            for (int m = 0; m < 3; m++) {
              if (a[CAR_AI_DRIVEN] == 1 || b[CAR_AI_DRIVEN] != 1 || a[CAR_ID] == 0) {
                if (a[CAR_MODEL] == 6 || b[CAR_MODEL] != 6) g[m] = nv[m];
                else g[m] = (int32_t)((uint32_t)nv[m] << 1) / 3;
              } else g[m] = dv(W(L(nv[m]) * (7 - WI00B87E2C)), 3);
            }
            impulse(bb + j * 0x34, g, eb, spin, 1);
          }
          P102_CarsCollide(a[CAR_ID], b[CAR_ID], closing);
        }
      }
      /* advance overlapping cars: half step (s = 0) or full step from both derivatives (s = 1) */
      for (int32_t i = 0; i < n; i++) {
        uint8_t *o = G6_00B2F30C[i];
        if (o == NULL || rd16(o + CAR_OVERLAP) == 0) continue;
        uint8_t *p = o + CAR_BODY, *t = blk(P102_BlkA, i), *rb = blk(P102_BlkB, i), *rc = blk(P102_BlkC, i);
        if (s == 0) {
          for (int m = CAR_BODY_INTS - 1; m >= 0; m--) wr32(t + m * 4, W(L(rd32(p + m * 4)) + (rd32(rb + m * 4) >> 3)));
          P56_ObjSync((int32_t *)(void *)t, o);
        } else {
          for (int m = CAR_BODY_INTS - 1; m >= 0; m--) add32(p + m * 4, W(L(rd32(rb + m * 4)) + rd32(rc + m * 4)) >> 4);
          P56_ObjSync((int32_t *)(void *)p, o);
        }
      }
    }
  }
  /* (4) Derived values for the rest of the game. */
  for (int32_t i = 0; i < n; i++) {
    uint8_t *o = G6_00B2F30C[i];
    if (o == NULL) continue;
    uint32_t type = o[CAR_MODEL];
    /* damage-model update is spread over 4 frames (every frame in director mode) */
    if (o[CAR_DAMAGED] != 0 && (G6_00B87EA0 != 0 || ((uint32_t)(P62_Frame + i) & 3u) == 0)) {
      AddUnique_004C1F9B((int32_t)o[CAR_ID] - 1);
      o[CAR_DAMAGED] = 0;
    }
    /* heading = atan2 of the forward axis (matrix elements [2] and [8]) */
    wr32(o + CAR_HEADING, (int32_t)((uint32_t)P44_Atan2(rd16(o + CAR_MAT + 4), rd16(o + CAR_MAT + 16)) & 0xfffu));
    if (traffic_b(o[CAR_ID], 5) != 0 || is_cur(o) || 0xd0cb07u < oaddr(o)) {   /* cops, current car, spare: Euler angles */
      uint32_t r = P17_ISqrt((uint32_t)W(L(rd16(o + CAR_MAT + 6)) * rd16(o + CAR_MAT + 6) + L(rd16(o + CAR_MAT_YY)) * rd16(o + CAR_MAT_YY)));
      wr16(o + CAR_ANG + 0, (int32_t)((uint32_t)P44_Atan2(-rd16(o + CAR_MAT + 10), (int32_t)r) & 0xfffu));
      wr16(o + CAR_ANG + 2, rd32(o + CAR_HEADING));
      wr16(o + CAR_ANG + 4, (int32_t)((uint32_t)P44_Atan2(rd16(o + CAR_MAT + 6), rd16(o + CAR_MAT_YY)) & 0xfffu));
    }
    wr32(o + CAR_POS_X, rd32(o + CAR_POS2 + 0)); wr32(o + CAR_POS_Y, rd32(o + CAR_POS2 + 4)); wr32(o + CAR_POS_Z, rd32(o + CAR_POS2 + 8));
    wr32(o + CAR_VEL_INT + 0, W(L(rd32(o + CAR_VEL + 0)) + FX_HALF) >> FX_SHIFT);
    wr32(o + CAR_VEL_INT + 4, W(L(rd32(o + CAR_VEL + 4)) + FX_HALF) >> FX_SHIFT);
    wr32(o + CAR_VEL_INT + 8, W(L(rd32(o + CAR_VEL + 8)) + FX_HALF) >> FX_SHIFT);
    { int16_t m[9]; memcpy(m, o + CAR_MAT, 18); CopyShort9_005278FB(m); }
    { uint32_t v[3]; memcpy(v, o + CAR_POS2, 12); CopyVec3_0052797A(v); }
    P102_D0DD74 = 0;
    for (int32_t w = 0; w < 4; w++) {
      int32_t pp[4] = { 0 }, nn[4] = { 0 }, gg[4] = { 0 };
      load_pt(model_pt(type, 0x41 + w * 2));
      RotVec_005279CB(pp);
      (void)P103_GroundAt(pp, nn, gg);
      wr32(o + CAR_GROUND_PT + w * CAR_GROUND_PT_SIZE + 0, gg[0]);
      wr32(o + CAR_GROUND_PT + w * CAR_GROUND_PT_SIZE + 4, gg[1]);
      wr32(o + CAR_GROUND_PT + w * CAR_GROUND_PT_SIZE + 8, gg[2]);
    }
    wr32(o + CAR_F0F4, P102_D0DD74);
  }
}
