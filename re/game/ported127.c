/* ported127.c — replay auto-camera, traffic lane change, map window, player skid sound, pedestrian spawn points,
   distant debris, street lamp lights, the pause menu, the per-frame mission script step and name entry
   (English overview; detailed Russian notes follow).  All cdecl. */
/* v1.72: ported127 — восстановлено из Game.exe. Все функции cdecl (work/rets.py: ret без операнда).
   004c582f — CreateNewAutoCamera: запись камеры 0x8c (int32 поля), точка за GetWaypointAfterFrame, тип по rand & 7
     (0 — вокруг игрока, 2 — за машиной трафика P60_NextTrafficCar, 0x11 — середина отрезка путевых точек).
   00494e01 — смена полосы машины трафика: P75_TrafficPos, клетка P54_G40/G44 × P63_Scale, проверка соседей в TrafficRecs.
   0050b957 — окно 0x37×0x37 клеток карты (P54_RoadB, +2 байта — P14_Fn0050D97A читает старшие/младшие половины),
     затем 0050b088 (не перенесена, V-строка) и таблицы P77_C7D8C0 (& 0x1e) / P77_C62E60 (P110_CellTab).
   004de381 — звук заноса игрока (голос 4) и следы шин (P117_SkidRecA по колёсам); блок 004de478..004de4fb в Ghidra
     удалён как недостижимый (локал [ebp-0xc] = 0) — не переносится.
   004f1a19 — такт точек появления P126_Spawn: анимация по P54_Tab4[вид-1] (шаг P12_00c821a0·0x14+0x10), отрисовка
     P100_DrawPartsB при draw ≠ 0; оба __ftol — (int32_t)(PartBase − P123_SideX/Z) (по ассемблеру, fsub перед __ftol).
   004ad3b5 — обломки P125_DebrisBurst у объектов списка 00cfe760 (P104_Buf760, uint32-адреса): __ftol — (int32_t)(x −
     P44_CamX) и (int32_t)(z − P44_CamZ) (по ассемблеру); .data 00546160 = 1024.0.
   004eac70 — огни фонарей: сетка P58_ListB31EC4 (ширина P78_LampHdr[2]), записи 0x28 {тип, радиус float, x, y, z, —,
     r, g, b}; __ftol — (int32_t) радиуса +4; 5 записей 00c818c0 (флаги 00c80f80).
   0050ee00 — Pause: адреса меню .data 00574710..00574ea0 (native — P127_PauseMenu в k_regions) в 00b5a730.
   004f472b — такт скрипта миссии; 004f8e0c (команда скрипта) — P146_ScriptCmd (v1.91).
   004131a0 — ввод имени (.data 0054cf80 — P127_NameMenu в k_regions, курсор 005fe97c — P127_Cursor);
     __ftol — (int32_t)(ширина / 2.0) + 0x141; возвращаемое значение — мусор eax 004133b4 (void). */
#include "ported129.h"
#include "ported127.h"
#include "carfields.h"
#include "ported146.h"
#include "p127_data.h"
#include "unported.h"
#include "engine.h"
#include "crt.h"
#include "reptr.h"
#include "cartab.h"
#include "strtab.h"
#include "globalsets.h"
#include "menustate.h"
#include "smallfuncs.h"
#include "smallfuncs2.h"
#include "uihandlers3.h"
#include "director.h"
#include "dirnodes.h"
#include "ported5.h"
#include "ported6.h"
#include "ported7.h"
#include "ported8.h"
#include "ported11.h"
#include "ported12.h"
#include "ported13.h"
#include "ported14.h"
#include "ported15.h"
#include "ported16.h"
#include "ported17.h"
#include "ported19.h"
#include "ported21.h"
#include "ported25.h"
#include "ported26.h"
#include "ported29.h"
#include "ported36.h"
#include "ported43.h"
#include "ported44.h"
#include "ported45.h"
#include "ported47.h"
#include "ported48.h"
#include "ported54.h"
#include "ported56.h"
#include "ported57.h"
#include "ported58.h"
#include "ported59.h"
#include "ported60.h"
#include "ported61.h"
#include "ported62.h"
#include "ported63.h"
#include "ported72.h"
#include "ported74.h"
#include "ported75.h"
#include "ported77.h"
#include "ported78.h"
#include "ported79.h"
#include "ported80.h"
#include "ported82.h"
#include "ported88.h"
#include "ported93.h"
#include "ported94.h"
#include "ported95.h"
#include "ported97.h"
#include "ported98.h"
#include "ported99.h"
#include "ported100.h"
#include "ported101.h"
#include "ported102.h"
#include "ported104.h"
#include "ported107.h"
#include "ported110.h"
#include "ported113.h"
#include "ported114.h"
#include "ported115.h"
#include "ported116.h"
#include "ported117.h"
#include "ported119.h"
#include "ported121.h"
#include "ported123.h"
#include "ported124.h"
#include "ported125.h"
#include "ported126.h"
#include <math.h>
#include <string.h>

#ifndef RE_HOOK_BUILD
int plat_frame_no(void);   /* v2.29: номер показанного кадра — для журналов отладки */
#endif
#ifndef RE_HOOK_BUILD
#pragma push_macro("P127_PauseMenu") /*gvi*/
#undef P127_PauseMenu /*gvi*/
p127_pause_t P127_PauseMenu = P127_PAUSE_INIT;   /* .data 00574710 */
#pragma pop_macro("P127_PauseMenu") /*gvi*/
#pragma push_macro("P127_NameMenu") /*gvi*/
#undef P127_NameMenu /*gvi*/
p127_name_t  P127_NameMenu = P127_NAME_INIT;     /* .data 0054cf80 */
#pragma pop_macro("P127_NameMenu") /*gvi*/
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P127_Cursor")
#undef P127_Cursor
#pragma push_macro("P127_Cursor") /*gvi*/
#undef P127_Cursor /*gvi*/
p127_cur_t P127_Cursor;
#pragma pop_macro("P127_Cursor") /*gvi*/
#pragma pop_macro("P127_Cursor")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P127_NameLen")
#undef P127_NameLen
#pragma push_macro("P127_NameLen") /*gvi*/
#undef P127_NameLen /*gvi*/
int32_t P127_NameLen;
#pragma pop_macro("P127_NameLen") /*gvi*/
#pragma pop_macro("P127_NameLen")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P127_BlinkT")
#undef P127_BlinkT
#pragma push_macro("P127_BlinkT") /*gvi*/
#undef P127_BlinkT /*gvi*/
int32_t P127_BlinkT;
#pragma pop_macro("P127_BlinkT") /*gvi*/
#pragma pop_macro("P127_BlinkT")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P127_BlinkOn")
#undef P127_BlinkOn
#pragma push_macro("P127_BlinkOn") /*gvi*/
#undef P127_BlinkOn /*gvi*/
int32_t P127_BlinkOn;
#pragma pop_macro("P127_BlinkOn") /*gvi*/
#pragma pop_macro("P127_BlinkOn")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P127_Lamp5")
#undef P127_Lamp5
#pragma push_macro("P127_Lamp5") /*gvi*/
#undef P127_Lamp5 /*gvi*/
p127_lamp5_t P127_Lamp5;
#pragma pop_macro("P127_Lamp5") /*gvi*/
#pragma pop_macro("P127_Lamp5")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P127_LampOn")
#undef P127_LampOn
#pragma push_macro("P127_LampOn") /*gvi*/
#undef P127_LampOn /*gvi*/
p127_i5_t P127_LampOn;
#pragma pop_macro("P127_LampOn") /*gvi*/
#pragma pop_macro("P127_LampOn")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P127_LampPhase")
#undef P127_LampPhase
#pragma push_macro("P127_LampPhase") /*gvi*/
#undef P127_LampPhase /*gvi*/
int32_t P127_LampPhase;
#pragma pop_macro("P127_LampPhase") /*gvi*/
#pragma pop_macro("P127_LampPhase")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P127_SpawnD0")
#undef P127_SpawnD0
#pragma push_macro("P127_SpawnD0") /*gvi*/
#undef P127_SpawnD0 /*gvi*/
int32_t P127_SpawnD0;
#pragma pop_macro("P127_SpawnD0") /*gvi*/
#pragma pop_macro("P127_SpawnD0")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P127_SpawnCnt")
#undef P127_SpawnCnt
#pragma push_macro("P127_SpawnCnt") /*gvi*/
#undef P127_SpawnCnt /*gvi*/
int32_t P127_SpawnCnt;
#pragma pop_macro("P127_SpawnCnt") /*gvi*/
#pragma pop_macro("P127_SpawnCnt")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P127_SpawnRst")
#undef P127_SpawnRst
#pragma push_macro("P127_SpawnRst") /*gvi*/
#undef P127_SpawnRst /*gvi*/
int32_t P127_SpawnRst;
#pragma pop_macro("P127_SpawnRst") /*gvi*/
#pragma pop_macro("P127_SpawnRst")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P127_SpawnReq")
#undef P127_SpawnReq
#pragma push_macro("P127_SpawnReq") /*gvi*/
#undef P127_SpawnReq /*gvi*/
int32_t P127_SpawnReq;
#pragma pop_macro("P127_SpawnReq") /*gvi*/
#pragma pop_macro("P127_SpawnReq")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P127_ScrPos")
#undef P127_ScrPos
#pragma push_macro("P127_ScrPos") /*gvi*/
#undef P127_ScrPos /*gvi*/
int32_t P127_ScrPos;
#pragma pop_macro("P127_ScrPos") /*gvi*/
#pragma pop_macro("P127_ScrPos")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P127_GoalX")
#undef P127_GoalX
#pragma push_macro("P127_GoalX") /*gvi*/
#undef P127_GoalX /*gvi*/
float P127_GoalX;
#pragma pop_macro("P127_GoalX") /*gvi*/
#pragma pop_macro("P127_GoalX")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P127_GoalZ")
#undef P127_GoalZ
#pragma push_macro("P127_GoalZ") /*gvi*/
#undef P127_GoalZ /*gvi*/
float P127_GoalZ;
#pragma pop_macro("P127_GoalZ") /*gvi*/
#pragma pop_macro("P127_GoalZ")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P127_GoalJump")
#undef P127_GoalJump
#pragma push_macro("P127_GoalJump") /*gvi*/
#undef P127_GoalJump /*gvi*/
int32_t P127_GoalJump;
#pragma pop_macro("P127_GoalJump") /*gvi*/
#pragma pop_macro("P127_GoalJump")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P127_Goal")
#undef P127_Goal
#pragma push_macro("P127_Goal") /*gvi*/
#undef P127_Goal /*gvi*/
p127_f16_t P127_Goal;
#pragma pop_macro("P127_Goal") /*gvi*/
#pragma pop_macro("P127_Goal")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P127_GoalSave")
#undef P127_GoalSave
#pragma push_macro("P127_GoalSave") /*gvi*/
#undef P127_GoalSave /*gvi*/
p127_u14_t P127_GoalSave;
#pragma pop_macro("P127_GoalSave") /*gvi*/
#pragma pop_macro("P127_GoalSave")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P127_GoalPause")
#undef P127_GoalPause
#pragma push_macro("P127_GoalPause") /*gvi*/
#undef P127_GoalPause /*gvi*/
p127_f16_t P127_GoalPause;
#pragma pop_macro("P127_GoalPause") /*gvi*/
#pragma pop_macro("P127_GoalPause")
#endif
#endif

#define RE_MEMRW_LOCAL16   /* keep the local 16-bit helpers below (hook object identity, see memrw.h) */
#include "memrw.h"
static int16_t rd16(const void *p) { int16_t v; memcpy(&v, p, 2); return v; }
static void wr16(void *p, int16_t v) { memcpy(p, &v, 2); }
static void wrf(void *p, float v) { memcpy(p, &v, 4); }
static int32_t dist8(int32_t dx, int32_t dz) { dx = iabs(dx); dz = iabs(dz); return dx < dz ? dz + dx / 2 : dx + dz / 2; }
#define P127_CAR(i)  ((uint8_t *)&P99_Cars[(i)])
#define P127_BLK(a)  (*(int32_t *)&P56_Blk84[((a) - 0x00c810c0u) / 4])   /* поля внутри P56_Blk84 */
#define P127_PM(a)   (*(uint32_t *)&P127_PauseMenu[((a) - P127_PAUSE_ADDR)])
#ifdef RE_HOOK_BUILD
#  define P127_NM32(a) (*(int32_t *)(uintptr_t)(a))
#  define P127_NM8(a)  (*(uint8_t *)(uintptr_t)(a))
#else
#  define P127_NM32(a) (*(int32_t *)&P127_NameMenu[(a) - P127_NAME_ADDR])
#  define P127_NM8(a)  (P127_NameMenu[(a) - P127_NAME_ADDR])
#endif
static uint8_t *car_or_null(int32_t i) { return (i >= 0 && i < P99_CARS_N) ? P127_CAR(i) : NULL; }
/* машина трафика i по указателю 0113a6c4; в native, если указатель не задан, — P99_Cars[1 + i] (как P102) */
static uint8_t *tcar(int32_t i) {
#ifndef RE_HOOK_BUILD
  if (P59_CarsTab == NULL) return (i + 1 >= 0 && i + 1 < P99_CARS_N) ? P127_CAR(i + 1) : P127_CAR(P99_CARS_N - 1);
#endif
  return P59_CarsTab + (uint32_t)i * 0x148;
}
/* Mission state value of 00c810c4 meaning "mission failed" (set_fail; the script loop stops on it). */
#include "missionstate.h"
#define MISSION_FAILED MSTATE_FAILED
/* 00c810c4 — флаги скрипта: несколько native-псевдонимов (P14_00c810c4, P16_IdleMode, P56_Blk84[1]) */
static void set_c4(int32_t v) {
  P14_00c810c4 = v;
#ifndef RE_HOOK_BUILD
  P16_IdleMode = v; P127_BLK(0x00c810c4u) = v;
#endif
}
static void set_fail(void) {   /* MSTATE_FAILED, reason MREASON_FAILED (2), result screen after 0x5a ticks */
  set_c4(MISSION_FAILED);
  P14_00c810e8 = 2; P14_00c81100 = 0x5a;
#ifndef RE_HOOK_BUILD
  P127_BLK(0x00c810e8u) = 2; P127_BLK(0x00c81100u) = 0x5a;
#endif
}

/* ---- 004c582f ---- */
/* P127_AutoCamera — Game.exe 004c582f (CreateNewAutoCamera).  Fills replay camera record cam (0x8c bytes) for the
   next waypoint frame with a random type (rand & 7): around the player, following a nearby cop car
   (P60_NextTrafficCar) or tripod at the middle of the waypoint segment. */
/* PS1: DoAutoDirect @ 0x0005B784 (olink9/driver1-decomp@5bb6cda, high) */
void P127_AutoCamera(void *cam) {
  int32_t *c = (int32_t *)cam;
  P14_Fn0048DB65(c, 0x8c);
  WAYPOINT_REC *w = GetWaypointAfterFrame(DirectorUnk6C);
  if (w == NULL) { P124_DebugLog("CreateNewAutoCamera: No waypoint found, function failed."); return; }
  if (DirectorUnk6C >= w->frame) { c[0] = 2; P61_CamPrepare((uint8_t *)c); return; }
  int32_t span = w->frame - DirectorUnk6C;
  c[0x11] = 1; c[4] = 0;
  switch (N14_Rand() & 7) {
  case 0: {
    c[0] = 0;
    c[6] = -(int32_t)N14_Rand() & 0xfff;
    c[2] = (int32_t)(N14_Rand() & 0x7e7) + 1000;
    c[3] = c[2];
    c[0x1c] = -(int32_t)((N14_Rand() & 0xff) + 100);
    uint32_t a = (uint32_t)(-c[6]) & 0xfff;
    float co = P43_Sin[a + 0x400];
    P11_00ba52d0 = fround(-P43_Sin[a] * (float)c[2]);
    c[0x13] = PlayerPosX + P11_00ba52d0;
    P11_00ba52d0 = fround((float)c[2] * co);
    c[0x15] = PlayerPosZ + P11_00ba52d0;
    break; }
  case 1: case 2: c[0] = 0x11; break;
  case 3: c[0x12] = 1; /* fallthrough */
  case 4: c[4] = 0; c[0] = 0x11; break;
  case 5: P60_NextTrafficCar(0); c[0] = 2; c[4] = P60_NextTrafficCar(c[4]); break;
  case 6: c[0x12] = 1; /* fallthrough */
  default: c[0] = 0x11; break;
  }
  if (DirectorUnk6C + span < DirectorLastFrame) {
    if (c[0] == 0x11) {
      c[0x13] = (w->x - w[-1].x) / 2 + w[-1].x;
      c[0x15] = (w->z - w[-1].z) / 2 + w[-1].z;
    } else if (c[0] != 0) { c[0x13] = w->x; c[0x15] = w->z; }
  } else {
    c[0] = 0; c[4] = 0;
    P124_DebugLog("Camera changed to type 0 because went beyond replay length.");
  }
  int32_t h = P100_RoadHeight(c + 0x13);
  int32_t nh = -h;
  uint8_t *car = car_or_null(c[4]);                        /* защита индекса: в оригинале нет */
  if (car != NULL) { int32_t pos[3]; memcpy(pos, car + 0xc8, 12); P100_RoadHeight(pos); }
  if (P15_State == 4) c[0x14] = nh - 200;
  else c[0x14] = (-0x46 - (int32_t)(N14_Rand() & 0x3ff)) + nh;
  if (nh < c[0x14]) c[0x14] = nh - 100;
  if (0x640 < iabs(c[0x14] + h)) c[0x14] = nh - 0x640;
  if (P95_SlotAt(c[0x13], c[0x15]) == 0 && c[0] != 0 && c[0] != 2) { c[0] = 2; c[4] = 0; }
  c[0x17] = c[0x13]; c[0x18] = c[0x14]; c[0x19] = c[0x15]; c[0x1a] = c[0x16];
}

/* ---- 00494e01 ---- */
/* P127_TrafficLane — Game.exe 00494e01.  Lane change of traffic record t: new position from P75_TrafficPos, its map
   cell, and a check of the neighbouring traffic records for room. */
void P127_TrafficLane(uint8_t *t) {
  if ((t[0x13] & 9) != 0 || (Rand_004D9078() & 3) != 0) return;
  P75_TrafficPos(rd32(t + 0x28), rd32(t + 0x24), 0, 2, 0xff);
  int32_t gx = fround((float)P54_G40 * P63_Scale);
  int32_t gz = fround((float)P54_G44 * P63_Scale);
  uint8_t *car = tcar(t[0]);
  int32_t x = fround((float)(rd32(car + 200) + 0x2ee) * P63_Scale);
  int32_t z = fround((float)(rd32(car + 0xd0) - 0x2ee) * P63_Scale);
  wr32(t + 0x48, x); wr32(t + 0x4c, z);
  P11_00ba52d0 = z;
  int32_t n = P21_EntryCount;
  if (n > 0x40) n = 0x40;                                   /* защита: TrafficRecs — 0x40 записей */
  if ((rd32(t + 0x24) & 1) == 0) {
    if (iabs(x - gx) != 1) return;
    for (int32_t k = 0; k < n; k++) {
      const uint8_t *o = TrafficRecs + k * 0x54;
      if (t[0] != o[0] && rd32(t + 0x28) == rd32(o + 0x28) && rd32(o + 0x48) == gx && iabs(z - rd32(o + 0x4c)) < 5) return;
    }
    t[0x13] |= 1; wr32(t + 0x40, P54_G40);
  } else {
    if (iabs(z - gz) != 1) return;
    for (int32_t k = 0; k < n; k++) {
      const uint8_t *o = TrafficRecs + k * 0x54;
      if (t[0] != o[0] && rd32(t + 0x28) == rd32(o + 0x28) && rd32(o + 0x4c) == gz && iabs(x - rd32(o + 0x48)) < 5) return;
    }
    t[0x13] |= 1; wr32(t + 0x44, P54_G44);
  }
}

/* ---- 0050b957 ---- */
/* map_row: copies one row of the road map; P127_MapWindow — Game.exe 0050b957: builds the 0x37 x 0x37 cell window
   of the road map around (x, y) for the overhead map / radar, then the cell tables P77_C7D8C0 / P110_CellTab. */
static void map_row(int32_t sel, int32_t off, uint8_t *dst, int32_t n) {
  const uint8_t *src = (const uint8_t *)P54_RoadB[sel & 3];
  if (src == NULL || n <= 0) return;                       /* защита: карта не загружена */
  P14_Fn0050D97A((const uint32_t *)(const void *)(src + off * 4 + 2), (uint32_t *)(void *)dst, n);
}
void P127_MapWindow(int32_t x, int32_t y, uint32_t arg) {
  int32_t N = P62_MapN;
  if (N > 0) {                                              /* защита деления: в оригинале нет */
    int32_t cx = (x - 0x1b) / N, cz = (y - 0x1b) / N;
    int32_t rx = (x - 0x1b) - cx * N, rz = (y - 0x1b) - cz * N;
    uint32_t sel = (uint32_t)(((P72_Rows - 1) - cz) & 1) << 1;
    int32_t row = rz * N;
    uint8_t *dst = P77_C5FE00;
    for (int32_t i = 0; i < 0x37; i++) {
      sel = (sel & 2) | ((uint32_t)cx & 1);
      if (N - 1 < rx + 0x37) {
        int32_t a = N - rx, b = (rx + 0x37) - N;
        if (a != 0) map_row((int32_t)sel, row + rx, dst, a);
        if (b != 0) map_row((int32_t)(sel ^ 1), row, dst + a * 4, b);
        dst += (a + b) * 4;
      } else {
        map_row((int32_t)sel, row + rx, dst, 0x37);
        dst += 0x37 * 4;
      }
      if (i + rz == N - 1) { row = 0; sel ^= 2; } else row += N;
    }
  }
  P129_MapCars((int32_t *)re_ptr(arg));
  for (int32_t i = 0; i < 0x2f4 * 4; i++) {
    uint32_t v = (uint32_t)rd32(P77_C5FE00 + i * 4);
    wr32(P77_C7D8C0 + i * 4, (int32_t)(v & 0x1e));
    wr32(P77_C62E60 + i * 4, P110_CellTab[v & 63]);         /* & 63 — защита индекса */
  }
}

/* ---- 004de381 ---- */
/* skid_off: ends all four skid marks.  P127_PlayerSkid — Game.exe 004de381: tyre squeal of the player (voice 4)
   and skid marks per wheel (P117_SkidRecA); who = car index.  (A block Ghidra removed as unreachable is not ported.) */
static void skid_off(void) { for (int i = 0; i < 4; i++) P102_D0DDD0[i] = -1; }
void P127_PlayerSkid(int32_t who) {
  if (G6_00B5A778 != 0) return;
  P102_D0DD78 = 0;
  if (who != 0) return;
  uint8_t *car = P127_CAR(0);
  int32_t v114 = rd32(car + 0x114);
  int32_t vol;
  if (rd32(car + 0xf0) == 0 || (rd32(car + 0x108) == 0 && iabs(rd32(car + 0x118)) < 0x3a99)) vol = 0;
  else {
    P102_D0DDF0 = 1; P102_D0DD78 = 1;
    vol = (rd32(car + 0x108) == 0) ? (iabs(rd32(car + 0x118)) - 15000) / 2 + 1 : 10000;
  }
  if (G6_00B87EA0 == 0) { P126_WheelSmoke(car); P121_WheelDust(); }
  if (15000 < iabs(v114)) { P102_D0DDF0 = 0; P102_D0DD78 = 1; }
  if (vol == 0) P48_SetVoiceVolume(4, -10000);
  else if ((car[0x7e] == 0 || car[0x86] == 0) && P26_FxA == 0 && P26_FxC == 0) {
    if (10000 < vol) vol = 10000;
    P56_SetVoicePos(4, (float)rd32(car + 0xc8), (float)-rd32(car + 0xcc), (float)rd32(car + 0xd0));
    SoundSetPos00523F8A(4, -1);
    P48_SetVoiceVolume(4, vol - 10000);
  } else P48_SetVoiceVolume(4, -10000);
  if (P102_D0DD78 == 0) { GlobalSet0051D811(); skid_off(); return; }
  if (P72_RoadLookup(rd32(car + 0xc8), rd32(car + 0xd0)) == 0) { skid_off(); return; }
  uint32_t m = (P72_Id < 1126u) ? P79_ModelTab[P72_Id] : 0;
  if (m == 0 || (rd16((uint8_t *)P79_PTR(m) + 2) & 0x80) != 0) { skid_off(); return; }
  static const int16_t offs[4] = { 0x78, 0x7c, 0x80, 0x84 };
  for (int w = 0; w < 4; w += 2) {
    if (car[offs[w]] == 0) P102_D0DDD0[w] = -1;
    else { P102_D0DD80 = P102_D0DDD0[w] != -1; P117_SkidRecA(w); P102_D0DDD0[w] = 1; }
  }
  if (P102_D0DDF0 == 0) {
    for (int w = 1; w < 4; w += 2) {
      if (car[offs[w]] == 0) P102_D0DDD0[w] = -1;
      else { P102_D0DD80 = P102_D0DDD0[w] != -1; P117_SkidRecA(w); P102_D0DDD0[w] = 1; }
    }
  } else { P102_D0DDD0[1] = -1; P102_D0DDD0[3] = -1; }
  GlobalSet0051D811();
}

/* ---- 004f1a19 ---- */
/* P127_SpawnTick — Game.exe 004f1a19.  Steps the pedestrian spawn points P126_Spawn: advances their motion-capture
   animation (P54_Tab4[kind - 1], frame stride nodes * 0x14 + 0x10) and draws them (P100_DrawPartsB) when draw != 0. */
void P127_SpawnTick(int32_t draw) {
  if (P127_SpawnRst != 0) {
    P43_ScaleA = 384.0f;
    P61_V20 = 0;
    P61_V1C = ((int32_t)P94_Heading + 0x800) & 0xfff;
    P61_OffY = -256.0f;
    P59_Mode1137324 = 0;
#ifndef RE_HOOK_BUILD
    G2_01137324 = 0;
#endif
    P127_SpawnRst = 0;
    return;
  }
  if (P98_C824A0 == 0) {
    if (P127_SpawnReq == 0 || draw != 0) return;
    P126_SpawnInit();
    P127_SpawnReq = 0;
  }
  if (draw != 0) P12_Fn00426580(0xe);
  int32_t busy = 0;
  uint8_t *r = P126_Spawn;
  int32_t cnt = P126_SpawnN; if (cnt > 4) cnt = 4;          /* защита: 4 записи */
  for (int32_t i = 0; i < cnt; i++, r += 0x18) {
    P100_PartFlags = i;
    if (r[0] == 0 || rd16(r + 2) != 0) {
      if (r[0] != 0 && draw == 0) { wr16(r + 2, (int16_t)(rd16(r + 2) - 1)); busy = 1; }
      continue;
    }
    P100_PartBase[0] = rdf(r + 8); P100_PartBase[2] = rdf(r + 0x10);
    int32_t h = P100_RoadHeightF(P100_PartBase);
    P100_PartBase[1] = (float)(-0xe0 - h);
    int32_t dx = (int32_t)(P100_PartBase[0] - P123_SideX), dz = (int32_t)(P100_PartBase[2] - P123_SideZ);
    uint32_t ang = (uint32_t)P44_Atan2(dx, dz) & 0xfff;
    int32_t d = dist8(dx, dz);
    if (i == 0) P127_SpawnD0 = d;
    if (d < 0x32) { r[0] = 0; continue; }
    busy = 1;
    float cs = P43_Sin[ang + 0x400], sn = P43_Sin[ang];
    int32_t n = (r[1] < 16) ? P43_AnimTab[r[1]] : 0;
    const uint8_t *base = (r[1] >= 1 && r[1] <= 4) ? (const uint8_t *)P54_Tab4[r[1] - 1] : NULL;
    if (base == NULL || n <= 0) continue;                  /* защита: нет анимации */
    int32_t stride = P12_00c821a0 * 0x14 + 0x10;
    const uint8_t *f = base + stride * rd32(r + 4);
    float a0 = rdf(f), a1 = rdf(f + 4), a2 = rdf(f + 8);
    P100_PartBase[0] = a2 * sn + a0 * cs + P100_PartBase[0];
    P100_PartBase[1] = P100_PartBase[1] + a1;
    P100_PartBase[2] = (a2 * cs - a0 * sn) + P100_PartBase[2];
    P11_00ba52d0 = fround(P100_PartBase[0] - P44_CamX);
    int32_t ex = P11_00ba52d0;
    P11_00ba52d0 = fround(P100_PartBase[2] - P44_CamZ);
    if (dist8(ex, P11_00ba52d0) >= 0x3a99 && draw != 0) continue;
    P100_PartMode = P82_SphereVis3D(P100_PartBase, 800.0f);
    if (P100_PartMode != 0) {
      int16_t e[3] = { 0x800, (int16_t)ang, 0 };
      float q[8] = { 0 }, zero[3] = { 0, 0, 0 };
      P44_EulerToQuat(e, q);
      P100_PartModel = P100_PartModelA;
      if (draw != 0) {
        P100_DrawPartsB((const float *)(const void *)(f + 0x10), P100_PartNodes, q, zero);
      }
    }
    int32_t k0 = rd32(r + 4);
    for (int32_t k = k0; k < k0 + 2; k++) {
      const uint8_t *g = base + stride * (k < n ? k : k % n);
      if (G6_00B5A778 == 0 && draw == 0) {
        wrf(r + 8, sn * rdf(g + 8) + cs * rdf(g) + rdf(r + 8));
        wrf(r + 0x10, (cs * rdf(g + 8) - sn * rdf(g)) + rdf(r + 0x10));
      }
    }
    if (G6_00B5A778 == 0 && draw == 0) wr32(r + 4, (rd32(r + 4) + 2) % n);
  }
  if (busy == 0 && draw == 0 && --P126_SpawnT == 0) {
    if (P127_SpawnCnt < 2) P127_SpawnRst = 1;
    P98_C824A0 = 0;
    P127_SpawnCnt = 0;
  }
}

/* ---- 004ad3b5 ---- */
/* P127_FarDebris — Game.exe 004ad3b5.  Debris bursts (P125_DebrisBurst) at the objects listed in 00cfe760
   (P104_Buf760, Game.exe addresses), relative to the camera. */
/* PS1: AddGroundDebris @ 0x000426B4 (olink9/driver1-decomp@5bb6cda, high) */
void P127_FarDebris(void) {
  int32_t sp = rd32(P127_CAR(0) + 0x10c);
  if (P13_00553850 == 0 || P62_HudOff2 != 0 || !(99999 < sp || sp < -99999)) return;
  for (int32_t i = 0; ; i++) {
    P75_Ptr562D7C = 0x00cfe760u + (uint32_t)i * 4;
    if (i >= 0x10 || P104_Buf760[i] == 0) return;
    const uint8_t *o = (const uint8_t *)re_ptr(P104_Buf760[i]);
    if (o == NULL) return;                                   /* защита */
    int32_t mi = rd32(o + 4);
    uint32_t m = (mi >= 0 && mi < 1126) ? P79_ModelTab[mi] : 0;
    int32_t dx = iabs((int32_t)(rdf(o + 8) - P44_CamX)), dz = iabs((int32_t)(rdf(o + 0x10) - P44_CamZ));
    if (15000 < dx || 15000 < dz) return;
    if (dx < 12000 && dz < 12000) return;
    if (0x50 < S_010FFA24) return;
    float pos[3];
    uint32_t r1 = N14_Rand();
    pos[0] = (rdf(o + 8) - 1024.0f) + (float)(r1 & 0x7ff);          /* .data 00546160 = 1024.0 */
    pos[2] = (rdf(o + 0x10) - 1024.0f) + (float)(N14_Rand() & 0x7ff);
    int32_t z = fround(pos[2]);
    P11_00ba52d0 = fround(pos[0]);
    P72_RoadLookup(P11_00ba52d0, z);
    pos[1] = (float)(-P72_Low);
    int32_t kind = (m != 0 && (rd32((uint8_t *)P79_PTR(m) + 8) & 0x2000) != 0) ? 1 : (int32_t)(N14_Rand() & 3) + 2;
    P125_DebrisBurst(pos, (int32_t)(r1 & 3) + 1, kind);
  }
}

/* ---- 004eac70 ---- */
/* lamp_light: adds one lamp record as a point light.  P127_LampLights — Game.exe 004eac70: street lamp lights from
   the lamp grid (P58_ListB31EC4, width P78_LampHdr[2]; records 0x28 = {type, radius float, x, y, z, -, r, g, b}) plus
   the 5 script lamps at 00c818c0 (enable flags 00c80f80). */
static void lamp_light(const uint8_t *r) {
  P82_AddLight((const float *)(const void *)(r + 8), (int32_t)rdf(r + 4), rd32(r + 0x18), rd32(r + 0x1c), rd32(r + 0x20));
}
void P127_LampLights(void) {
  if (P58_ListB31EC4 == NULL || P14_00b87e84 == 0) return;
  if (G6_00B5A778 == 0) P127_LampPhase++;
  P127_LampPhase &= 0xf;
  int32_t cell = P80_Cell;
  if (cell == 0) return;                                    /* защита деления */
  int32_t cx = PlayerPosX / cell + P80_HalfW, cz = PlayerPosZ / cell + P80_HalfH;
  int32_t n = (P13_00b87e74 == 0) ? 0xd : 0x15;
  cx -= (n == 0xd) ? 6 : 10; cz -= (n == 0xd) ? 6 : 10;
  for (int32_t row = 0; row < n; row++, cz++) {
    int32_t idx = cz * P78_LampHdr[2] + cx;
    for (int32_t col = 0; col < n; col++, idx++) {
#ifndef RE_HOOK_BUILD
      if (idx < 0 || idx >= P58_CntB31EBC) continue;        /* защита: вне сетки */
#endif
      const p58_slot_t *s = &P58_ListB31EC4[idx];
      if (s->p == NULL) continue;
      const uint8_t *r = (const uint8_t *)s->p;
      for (int32_t k = s->a; k != 0; k--, r += 0x28) {
        int32_t t = rd32(r);
        if (t == 1) { if (G6_00B5A778 == 0 && (N14_Rand() & 3) == 0) continue; }
        else if (t == 2 && P127_LampPhase <= 0x1ff) continue;
        lamp_light(r);
      }
    }
  }
  for (int32_t i = 4; i >= 0; i--) {
    const uint8_t *r = P127_Lamp5 + i * 0x28;
    if (P127_LampOn[i] == 0) continue;
    P11_00ba52d0 = fround(rdf(r + 8));
    int32_t dx = P11_00ba52d0 - PlayerPosX;
    P11_00ba52d0 = fround(rdf(r + 0x10));
    int32_t dz = P11_00ba52d0 - PlayerPosZ;
    if (899999999 < (int32_t)((uint32_t)dx * (uint32_t)dx + (uint32_t)dz * (uint32_t)dz)) continue;
    int32_t t = rd32(r);
    if (t == 1) { if (G6_00B5A778 == 0 && (N14_Rand() & 3) == 0) continue; }
    else if (t == 2 && P127_LampPhase <= 7) continue;
    lamp_light(r);
  }
}

/* ---- 0050ee00 ---- */
/* set_menu: current menu page 00b5a730 (all aliases); mode10_menu: page for game mode 10.
   P127_Pause — Game.exe 0050ee00: pause menu handling; picks the menu page (.data 00574710..00574ea0, native
   P127_PauseMenu) by game state and handles mission failure. */
static void set_menu(uint32_t a) {   /* 00b5a730 — во все псевдонимы */
  P17_PtrA = a;
#ifndef RE_HOOK_BUILD
  G00B5A730 = (int32_t)a; P11_00b5a730 = (int32_t)a; P8_00b5a730 = (int32_t)a;
#endif
}
static uint32_t mode10_menu(void) {
  if (P11_00b87e38 == P17_Src) return (P43_AnimTab[0] == -1) ? 0x00574ce0u : 0x00574db0u;
  return (P43_AnimTab[0] == -1) ? 0x00574d48u : 0x00574e28u;
}
void P127_Pause(void) {
  if (DirIndicatorOn != 0) {
    FreeCameraList(); FreeDirectorBuffer();
    G005F7E54 = 1;
#ifndef RE_HOOK_BUILD
    P17_Const6 = 1; P8_005f7e54 = 1;
#endif
    G6_00B87E20 = 0;
    return;
  }
  G6_00B5A778 = 1;
#ifndef RE_HOOK_BUILD
  P16_FlagA = 1;
#endif
  G6_00B87EFC = 1; G00B5A774 = 0;
  if (P29_Mode != 0) return;
  P8_00b5a768 = 0;
  if (P11_00d11934 == 0 && (GameMode == 4 || GameMode == 5)) {
    memcpy(P56_Blk84, P56_Save84, sizeof P56_Blk84);
    memcpy(P56_Blk11, P56_Save11, sizeof P56_Blk11);
#ifndef RE_HOOK_BUILD
    P14_00c810c4 = P127_BLK(0x00c810c4u); P16_IdleMode = P14_00c810c4;
    MenuMode1271060 = (int32_t)P56_Blk11[0]; P11_01271060 = MenuMode1271060; P62_Menu1271060 = MenuMode1271060;
    G01271060 = MenuMode1271060;
#endif
    if (GameMode == 5) P8_00b5a768 = 1;
  }
  P43_CdFadeInit();
  if (Q00B87E90 != 0) P25_CDStop();
  P107_NavWait = 10;
  P116_MBar = re_addr(P93_FindIcon("SLIDERB+"));
  P116_MSlider = re_addr(P93_FindIcon("SLIDERBR"));
  P17_PtrB = 0;
#ifndef RE_HOOK_BUILD
  G00B5A734 = 0; P11_00b5a734 = 0; P8_00b5a734 = 0;
#endif
  P17_ValA = 1;
#ifndef RE_HOOK_BUILD
  G00575550 = 1; P11_00575550 = 1; P8_00575550 = 1;
#endif
  int32_t mode = MenuMode1271060;
  if (P14_00c810c4 == MISSION_FAILED) {
    if (mode == 1) { P8_012710a0 = 1; set_c4(0x8000); }
    else if (mode == 3 || mode == 7) {
      const int32_t *src = (const int32_t *)re_ptr(P113_MrkRec);
      if (src != NULL) memcpy(P125_MrkSave, src, 6 * 4);
      P8_012710a0 = 1; set_c4(0x8000);
    }
  }
  if (P12_00d17b90 != 0) { set_menu(0x00574ea0u); P8_00b5a764 = 1; return; }
  if (P14_00c810c4 == MISSION_FAILED) {
    switch (mode) {
    case 6: set_menu(0x00574c90u); break;
    case 9: set_menu(P127_BLK(0x00c81280u) == 0 ? 0x00574a40u : 0x00574ad0u); break;
    case 10: set_menu(mode10_menu()); break;
    default: set_menu(0x00574b60u); break;
    }
    P8_00b5a764 = 1;
  } else if ((P14_00c810c4 & 0x8000) == 0) {
    if (P62_HudOff2 == 0 || P11_00d11934 != 0 || P11_00b87e38 != 0) {
      switch (mode) {
      case 0: case 1: case 2: case 3: case 4: case 5: case 7: case 8: case 9: set_menu(0x00574710u); break;
      case 6: case 0xb: set_menu(0x005747d8u); break;
      case 10: set_menu(0x00574868u); break;
      default: P124_DebugLog("Pause: Invalid game type, defaulting..."); set_menu(0x00574710u); break;
      }
    } else set_menu(0x005748f8u);
    P8_00b5a764 = 0;
  } else {
    switch (mode) {
    case 0: case 9:
      set_menu(0x005749b0u);
      if (GameMode == 0) memcpy(P127_GoalPause, P127_Goal, sizeof P127_GoalPause);
      break;
    case 1: case 2: case 3: case 4: case 5: case 7: case 0xb: {
      int32_t idx = 0;
      if (P62_ScoreTable(&idx, 1) == 0 && P62_ScoreTable(&idx, 0) == 0) set_menu(0x00574b60u);
      else set_menu(0x00574bf0u);
      break; }
    case 6: set_menu(0x00574b60u); break;
    case 10: set_menu(mode10_menu()); break;
    default: P124_DebugLog("Pause: Invalid game type, defaulting..."); set_menu(0x00574b60u); break;
    }
    P8_00b5a764 = 1;
  }
}

/* ---- 004f472b ---- */
/* P127_ScriptTick — Game.exe 004f472b.  Per-frame mission script step: copies the player damage, heading and 00d11a5c into
   the script goal record, updates script objects, keeps the replay goal position, then runs script commands
   (P146_ScriptCmd) from P127_ScrPos until one returns 0xd (wait) or the mission fails; afterwards target, timer,
   goal and chase steps, and failure when the damage exceeds the limit (flag 4 of 00c810d8). */
static void goal_u(int i, int32_t v) { memcpy(&P127_Goal[i], &v, 4); }
void P127_ScriptTick(void) {
  if (P97_ScrObjOn == 0) return;
  const uint8_t *me = P127_CAR(0);
  for (int i = 0; i < 6; i++) goal_u(7 + i, rd32(me + CAR_DAMAGE + 4 * i));
  goal_u(13, rd32(me + CAR_DAMAGE_SUM));
  goal_u(15, rd32(me + CAR_HEADING));
  goal_u(14, P14_00d11a5c);
  P97_ObjsFromScript();
  if (P14_00d14ee4 != 0) P14_Fn004CAC86();
  if (P14_00c810c4 != MISSION_FAILED) P98_ScriptRange();
  if (G6_00B87EB0 == 0) {
    P127_Goal[0] = (float)PlayerPosX; P127_Goal[2] = (float)PlayerPosZ;
  } else if (P75_E4 == 0) {
    memcpy(P127_GoalSave, P127_Goal, sizeof P127_GoalSave);
    memcpy(&P102_C816F8, &P127_Goal[14], 4); memcpy(&P102_C816FC, &P127_Goal[15], 4);
    if (P127_GoalJump != 0) { P127_GoalJump = 0; P127_GoalX = (float)PlayerPosX; P127_GoalZ = (float)PlayerPosZ; }
    P11_00ba52d0 = fround(P127_GoalX);
    int32_t dx = P11_00ba52d0 - P88_ObjX;
    P11_00ba52d0 = fround(P127_GoalZ);
    int32_t dz = P11_00ba52d0 - P88_ObjZ;
    if (4000000 < (int32_t)((uint32_t)dx * (uint32_t)dx + (uint32_t)dz * (uint32_t)dz)) {
      P127_Goal[0] = P127_GoalX; P127_Goal[2] = P127_GoalZ; P127_GoalJump = 1;
    }
  }
  if (P77_List == NULL || P77_ListN == 0 || G6_00B5A778 != 0) {
    if (P14_00c810c4 == MISSION_FAILED) P47_ResetPick();
    else if (P102_DmgMax < G00BDF984) { set_fail(); P47_Limit = 0; }
    return;
  }
  while (P127_ScrPos < P77_ListN && P14_00c810c4 != MISSION_FAILED) {
    int32_t pos = P127_ScrPos;
#ifndef RE_HOOK_BUILD
    { /* v2.29: RE_MISSDBG=1 — журнал команд скрипта миссии (номер, код, первый аргумент) при смене номера */
      static int dbg = -1; static int32_t last = -1; if (dbg < 0) dbg = getenv("RE_MISSDBG") != NULL;
      if (dbg && pos != last) { const int32_t *q = (const int32_t *)P77_List[pos];
        fprintf(stderr, "[mis] w=%d f=%d cmd#%d код 0x%02x a1=%d c4=%x\n", plat_frame_no(), (int)P62_Frame, (int)pos, q ? (int)q[0] : -1, q ? (int)q[1] : 0, (unsigned)P14_00c810c4); last = pos; } }
#endif
    int32_t r = P146_ScriptCmd(P77_List[pos]);
    if (r == 0xd) break;
#ifndef RE_HOOK_BUILD
    if (P127_ScrPos == pos) break;                         /* защита: заглушка 004f8e0c не двигает позицию */
#endif
  }
  if (P14_00c810c4 != MISSION_FAILED) {
    P115_TargetTick((uint8_t *)re_ptr((uint32_t)P127_BLK(0x00c812b8u)));
    P114_Timer((int32_t *)re_ptr(P113_MrkRec));
    P101_GoalTick((uint8_t *)P56_Blk84);
    if ((P14_00c810c4 & 0x8000) != 0) P56_ChaseTick();
    if (P99_CamDelay != 0) P99_CamDelay--;
    if ((P127_BLK(0x00c810d8u) & 4) != 0 && P102_DmgMax < G00BDF984) set_fail();
    if (P14_00c810c4 == MISSION_FAILED) P47_Limit = 0;
  }
  if (P14_00c810c4 == MISSION_FAILED) P47_ResetPick();
  TickTimer4F5D67();
}

/* ---- 004131a0 ---- */
/* P127_NameEntry — Game.exe 004131a0.  Name entry screen editing buf (max maxlen characters) with the cursor
   P127_Cursor; the original returns garbage in eax (void here). */
void P127_NameEntry(char *buf, int32_t maxlen) {
  int run = 1;
  P127_NM32(0x0054cfa0u) = (int32_t)P97_StrAddr[0x78];      /* 00c55a00 */
  P127_NM32(0x0054cfb0u) = (int32_t)re_addr(buf);
  P127_NM32(0x0054cfc0u) = (int32_t)re_addr(P127_Cursor);
  buf[0] = 0;
  P127_NameLen = 0;
  P45_Wait(0x0054cf80u, 0x0054cf98u);
  while (run) {
    Call00522323();
    P36_PollInput();
    int32_t k = P74_KeyScan();
    switch (k) {
    case 0: break;
    case -3: Ui0040C867(); run = 0; break;
    case -2: if (P127_NameLen != 0) { Ui0040C867(); run = 0; } break;
    case -1: if (0 < P127_NameLen) { Ui0040C867(); P127_NameLen--; buf[P127_NameLen] = 0; } break;
    default:
      if (P127_NameLen < maxlen) { Ui0040C867(); buf[P127_NameLen] = (char)k; P127_NameLen++; buf[P127_NameLen] = 0; }
      break;
    }
    if (--P127_BlinkT < 0) {
      P127_BlinkT = 10;
      P127_BlinkOn ^= 1;
      P127_Cursor[0] = (P127_BlinkOn == 0) ? 0 : 0x5f;
    }
    MenuSetByte5D77C1(P127_NM8(0x0054cfbcu));
    float w = P95_TextWidthCur((const uint8_t *)buf);
    P127_NM32(0x0054cfb8u) = (int32_t)(w / P19_DivC) + 0x141;
    P119_MenuFrame();
  }
  P57_MenuDone();
  if (buf[0] == 0) {
    const char *def = (const char *)re_ptr(P97_StrAddr[0x133]);   /* 00c55cec */
    if (def != NULL) strcpy(buf, def);
  }
  P58_CheatByName(buf);
}
