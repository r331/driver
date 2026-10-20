/* ported75.c — traffic spawning, ambient sounds, car engine voice, object reset and a screenshot-to-texture helper
   (English overview; Russian notes per function follow).  All cdecl. */
#include "ported75.h"
#include <string.h>

#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P75_E4")
#undef P75_E4
#pragma push_macro("P75_E4") /*gvi*/
#undef P75_E4 /*gvi*/
int32_t P75_E4;
#pragma pop_macro("P75_E4") /*gvi*/
#pragma pop_macro("P75_E4")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P75_E8")
#undef P75_E8
#pragma push_macro("P75_E8") /*gvi*/
#undef P75_E8 /*gvi*/
int32_t P75_E8;
#pragma pop_macro("P75_E8") /*gvi*/
#pragma pop_macro("P75_E8")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P75_12BC")
#undef P75_12BC
#pragma push_macro("P75_12BC") /*gvi*/
#undef P75_12BC /*gvi*/
int32_t P75_12BC;
#pragma pop_macro("P75_12BC") /*gvi*/
#pragma pop_macro("P75_12BC")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P75_4288")
#undef P75_4288
#pragma push_macro("P75_4288") /*gvi*/
#undef P75_4288 /*gvi*/
int32_t P75_4288;
#pragma pop_macro("P75_4288") /*gvi*/
#pragma pop_macro("P75_4288")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P75_43D0")
#undef P75_43D0
#pragma push_macro("P75_43D0") /*gvi*/
#undef P75_43D0 /*gvi*/
int32_t P75_43D0;
#pragma pop_macro("P75_43D0") /*gvi*/
#pragma pop_macro("P75_43D0")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P75_43CC")
#undef P75_43CC
#pragma push_macro("P75_43CC") /*gvi*/
#undef P75_43CC /*gvi*/
int32_t P75_43CC;
#pragma pop_macro("P75_43CC") /*gvi*/
#pragma pop_macro("P75_43CC")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P75_Spawn")
#undef P75_Spawn
#pragma push_macro("P75_Spawn") /*gvi*/
#undef P75_Spawn /*gvi*/
p75_spawn_t P75_Spawn;
#pragma pop_macro("P75_Spawn") /*gvi*/
#pragma pop_macro("P75_Spawn")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P75_B20350")
#undef P75_B20350
#pragma push_macro("P75_B20350") /*gvi*/
#undef P75_B20350 /*gvi*/
int32_t P75_B20350;
#pragma pop_macro("P75_B20350") /*gvi*/
#pragma pop_macro("P75_B20350")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P75_B31EDC")
#undef P75_B31EDC
#pragma push_macro("P75_B31EDC") /*gvi*/
#undef P75_B31EDC /*gvi*/
int32_t P75_B31EDC;
#pragma pop_macro("P75_B31EDC") /*gvi*/
#pragma pop_macro("P75_B31EDC")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P75_D022E0")
#undef P75_D022E0
#pragma push_macro("P75_D022E0") /*gvi*/
#undef P75_D022E0 /*gvi*/
int32_t P75_D022E0;
#pragma pop_macro("P75_D022E0") /*gvi*/
#pragma pop_macro("P75_D022E0")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P75_B31ED0")
#undef P75_B31ED0
#pragma push_macro("P75_B31ED0") /*gvi*/
#undef P75_B31ED0 /*gvi*/
int32_t P75_B31ED0;
#pragma pop_macro("P75_B31ED0") /*gvi*/
#pragma pop_macro("P75_B31ED0")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P75_CF1F60")
#undef P75_CF1F60
#pragma push_macro("P75_CF1F60") /*gvi*/
#undef P75_CF1F60 /*gvi*/
uint8_t P75_CF1F60;
#pragma pop_macro("P75_CF1F60") /*gvi*/
#pragma pop_macro("P75_CF1F60")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P75_Ptr562D7C")
#undef P75_Ptr562D7C
#pragma push_macro("P75_Ptr562D7C") /*gvi*/
#undef P75_Ptr562D7C /*gvi*/
uint32_t P75_Ptr562D7C;
#pragma pop_macro("P75_Ptr562D7C") /*gvi*/
#pragma pop_macro("P75_Ptr562D7C")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P75_Page")
#undef P75_Page
#pragma push_macro("P75_Page") /*gvi*/
#undef P75_Page /*gvi*/
p75_page_t P75_Page;
#pragma pop_macro("P75_Page") /*gvi*/
#pragma pop_macro("P75_Page")
#endif

static int32_t p75_i32(const uint8_t *p) { int32_t v; memcpy(&v, p, 4); return v; }

/* Spacing between the spawn positions along one side of a road junction cell (0x5dc = 1500 units). */
#define SPAWN_STEP 0x5dc

/* P75_TrafficPos — Game.exe 004913cc.  Computes a traffic spawn position on side `side` (0..3) of road node
   `cls`: node record (0x24 bytes at P59_C39DC0) = 4 bytes "positions per side" + 4 (x, y) side start points;
   positions are SPAWN_STEP apart.  last == 1 -> the last position; pick & 0xff == 0xff -> a random one;
   otherwise position pick (counted from the end when rev).  Except for last == 1 the point is then jittered:
   across the side by -0x80..0x7f, or — on one-way nodes (bit 0 of byte 0x34 of the 0x42-byte node record in
   P59_BF1C48) — pushed 0x80..0xff off the side start.  Result in P54_G40 (x) / P54_G44 (y). */
/* 004913cc: таблица 00c39dc0, запись 0x24 на класс: байты +0..3 — число позиций на стороне, int +4.. — пары (x, y) начал сторон.
   Шаг между позициями 0x5dc. rev — считать с конца, last==0xff — случайная позиция, cls==1 — последняя. Результат — 01139a30 (x), 01139a2c (y);
   затем (кроме pick==1) случайный сдвиг поперёк стороны. Флаг направления — бит 0 байта 0x34 записи 0x42 таблицы 00bf1c48. */
void P75_TrafficPos(int32_t cls, int32_t side, int32_t rev, int32_t last, uint32_t pick) {
  if (cls < 0 || cls >= P59_NODES_MAX || side < 0 || side > 3) return;   /* v2.21: было cls >= 64 — у узлов ≥ 64 позиция не считалась (оставалась от прошлого вызова) */
  const uint8_t *rec = P59_C39DC0 + cls * 0x24;
  int32_t n = (int32_t)rec[side] - 1;
  int32_t off;
  if (last == 1) {
    off = n * SPAWN_STEP;
  } else if ((pick & 0xff) == 0xff) {
    int32_t r = (int32_t)Rand_004D9078();
    off = (n + 1 != 0 ? r % (n + 1) : 0) * SPAWN_STEP;
  } else {
    uint8_t p = (uint8_t)pick;
    if ((int32_t)p > n) p = (uint8_t)n;
    if (rev != 0) p = (uint8_t)(n - p);
    off = (int32_t)p * SPAWN_STEP;
  }
  int32_t x = 0, y = 0;
  switch (side) {
    case 0: x = p75_i32(rec + 4) + off;  y = p75_i32(rec + 8); break;
    case 1: x = p75_i32(rec + 12);       y = p75_i32(rec + 16) - off; break;
    case 2: x = p75_i32(rec + 20) - off; y = p75_i32(rec + 24); break;
    case 3: x = p75_i32(rec + 28);       y = p75_i32(rec + 32) + off; break;
  }
  if (last != 1) {
    int32_t j = (int32_t)(Rand_004D9078() & 0xff) - 0x80;
    int32_t flag = P59_BF1C48[0x34 + cls * 0x42] & 1;
    switch (side) {
      case 0: if (flag) x -= (int32_t)(Rand_004D9078() & 0x7f) + 0x80; else x += j; break;
      case 1: if (flag) y += 0x80 + (int32_t)(Rand_004D9078() & 0x7f); else y += j; break;
      case 2: if (flag) x += 0x80 + (int32_t)(Rand_004D9078() & 0x7f); else y += j; break;
      case 3: if (flag) y -= (int32_t)(Rand_004D9078() & 0x7f) + 0x80; else y += j; break;
    }
  }
  P54_G40 = x;
  P54_G44 = y;
}

/* P75_TrafficSpawn — Game.exe 00492e42.  One traffic car spawn: pops a free car slot; while fewer than
   G0113A6C0 slots have been collected they are only queued (P12_01144340), afterwards the queue is
   processed (P75_Fn4958B7) first.  Picks a random entry of the spawn table P75_Spawn (12 bytes: s16 node
   (-1 = side from byte 2), +4/+8 ints) and places the car with P75_Fn491A56; counts successes in P75_E8 and
   records the spawn when recording a replay.  Replay playback: the slot is not chosen (0, see note). */
/* 00492e42: одно появление машины трафика. Номер слота берётся со стека свободных (0113a6c4-таблица — PopIndex00493E9B);
   пока набрано меньше 0113a6c0 — только запоминается в очереди 01144340, потом очередь разбирается 004958b7.
   Запись таблицы появления выбирается случайно. В режиме повтора (00b87eb0 != 0) слот в оригинале не задан — берётся 0. */
void P75_TrafficSpawn(void) {
  if (P75_43CC == 0) return;
  int32_t car = 0;
  if (G8_00B87EB0 == 0) {
    if (G01144284 < G0113A6C0) {
      car = PopIndex00493E9B();
      if (car == -1) return;
      if (G01144284 >= 0 && G01144284 < 0x100) P12_01144340[G01144284] = (uint32_t)car;
      G01144284 = G01144284 + 1;
      return;
    }
    if (G01144284 != 0) P75_Fn4958B7();
    car = PopIndex00493E9B();
    if (car == -1) return;
  }
  int32_t k = (int32_t)Rand_004D9078() % P75_43CC;
  if (k < 0 || k >= 256) k = 0;
  const uint8_t *e = P75_Spawn + k * 12;
  int16_t node; memcpy(&node, e, 2);
  int32_t v4 = p75_i32(e + 4), v8 = p75_i32(e + 8);
  int32_t ok;
  if (node == -1) ok = P75_Fn491A56(car, -1, e[2] & 3, v4, v8);
  else            ok = P75_Fn491A56(car, node, (int32_t)(Rand_004D9078() & 1), v4, v8);
  if (ok != 0) P75_E8 = P75_E8 + 1;
  if (G8_00B87EAC != 0 && ok != 0) P55_SaveRec(car);
}

/* P75_TrafficFill — Game.exe 0049512b.  Tops up traffic: wanted count = P51_TrafficN (0x14 while recording
   a replay); when fewer cars are active (P75_4288) spawns min(wanted, P75_43D0) times.  In replay playback it
   instead reads spawn records until the end marker (-1). */
/* 0049512b: пополнение трафика: нужное число — 00575ee4 (или 0x14 при записи повтора 00b87eac); при игре — до этого числа или
   до 011443d0 появлений за вызов; при воспроизведении повтора читаются записи 0051990a до конца (-1). */
void P75_TrafficFill(void) {
  if (P75_E4 != 0) return;
  if (G8_00B87EB0 == 0) {
    P75_12BC = (G8_00B87EAC == 0) ? P51_TrafficN : 0x14;   /* 20 cars while recording a replay */
    if (P75_4288 < P75_12BC) {
      int32_t n = (P75_12BC < P75_43D0) ? P75_12BC : P75_43D0;
      for (int32_t i = 0; i < n; i++) P75_TrafficSpawn();
    }
  } else {
    int32_t r = 0;
    if (P16_IdleMode != 0xff0 && P16_IdleMode != 0x7fff) {
      while (r != -1) {
        r = P56_ReplayRead();
        if (r != -1) P75_E8 = P75_E8 + 1;
      }
    }
  }
}

/* P75_BgSound — Game.exe 004d6c5a.  Random ambient sounds: every ~500..870 frames (random) plays one of the
   ambient ids 4, 6, 7, 8 (+0xf000 = ambient sound id space), chosen by frame & 3, if that one has not played
   for more than 0x8ca (2250) frames; the next delay is random. */
/* 004d6c5a: случайные фоновые звуки раз в ~500+ кадров. Таблица 00560398: (идентификатор, кадр последнего запуска) × 4 —
   идентификаторы 4, 6, 7, 8 (+0xf000 — запуск как у звука окружения). */
void P75_BgSound(void) {
  static const int32_t ids[4] = { 4, 6, 7, 8 };
  int32_t played = 0;
  if (WI00B20348 == 0) {
    uint32_t r = Rand_004D9078();
    WI00B20348 = 1;
    P75_B20350 = (int32_t)(r & 7) * 0x32 + 500 + (int32_t)(r & 0xf);
  } else {
    P75_B20350 = P75_B20350 - 1;
    if (P75_B20350 < 1) {
      int32_t i = P62_Frame & 3;
      if (P62_Frame - WA0056039C[i * 2] > 0x8ca) {
        UiCall00523E50(ids[i] + 0xf000, 0xf, -1);
        played = 1;
        WA0056039C[i * 2] = P62_Frame;
      }
      uint32_t r = Rand_004D9078();
      if (played) P75_B20350 = (int32_t)(r & 0xf) * 0x32 + 500 + (int32_t)(r & 0x1f);
      else        P75_B20350 = (int32_t)(r & 7) * 0x32 + (int32_t)(r & 0xf);
    }
  }
}

/* P75_CarSound — Game.exe 004d6dac.  When the player's map cell (car field +0x138 >> 3) changes, plays ambient
   track 1 or 2 (+0xf000) if enough random time (~350+ frames) has passed; when the cell does not change while
   P62_Spd > 30 for 1000 frames, plays track 0xf000.  TODO(RE): +0x138 is CAR_DAMAGE_SUM in carfields.h —
   which is right here is unsure (Get138 is not ported). */
/* 004d6dac: при смене клетки карты под игроком (поле +0x138 первой машины >> 3) запускается звук (1 или 2 + 0xf000)
   не чаще, чем через случайные ~350+ кадров; стоя на месте (скорость > 30) 1000 кадров подряд — звук 0xf000. */
void P75_CarSound(void) {
  int32_t v = Get138(P60_Cars);
  if ((v >> 3) == G2_00B20358) {
    if (P62_Spd > 0x1e) {
      G2_00B20354 = G2_00B20354 + 1;
      if (G2_00B20354 == 1000) { TryStartTrack_004D611B(0xf000); G2_00B20354 = 0; }
    }
  } else {
    G2_00B20354 = 0;
    int32_t i = (P62_Frame & 4) >> 2;
    if (P75_B20350 < P62_Frame - G2_005603BC[i].v) {
      TryStartTrack_004D611B((uint32_t)(i + 1 + 0xf000));
      G2_005603BC[i].v = P62_Frame;
    }
    uint32_t r = Rand_004D9078();
    P75_B20350 = (int32_t)(r & 3) * 0x32 + 0x15e + (int32_t)(r & 0x1f);
  }
  G2_00B20358 = v >> 3;
}

/* P75_ResetObjs — Game.exe 004ee065.  Resets the object/selection state: pointer 00562d7c = buffer 00cfe760,
   counters, 0x1200 bytes of 1 at S_00BDCD00, selection reset (-1 in several selection vars) and
   P55_Fn4EDAA2.  TODO(RE): which objects these are (map objects? pedestrians?) is not established. */
/* 004ee065: сброс выбора/объектов: указатель 00562d7c на буфер 00cfe760, счётчики, 0x1200 байт значений 1 в 00bdcd00,
   затем сброс выбора (P55_ResetSel: -1 в 00cff9c0/00c97a20/00d0022c.. и два вызова) и 00401c67 (= P55_Fn4EDAA2 внутри). */
void P75_ResetObjs(void) {
  P75_Ptr562D7C = 0x00cfe760u;
  P75_B31EDC = 0;
  P75_D022E0 = 0;
  P41_Offset = 0;
  P75_CF1F60 = 1;
  P75_B31ED0 = 0;
  P55_VarC0 = -1;
  P55_Var20 = -1;
  memset(S_00BDCD00, 1, 0x1200);
  P75_Fn4EDD08(0);
  P75_Fn4EDD08(1);
  P55_VarD2C = -1; P55_VarD28 = -1; P55_VarD24 = -1; P55_VarD20 = -1;
  P55_Fn4ED5F8(P12_00cff9ac, (int32_t)P55_VarC6);
  P55_Fn4EDAA2();
}

/* P75_CarVoice — Game.exe 004d68da.  Puts sound voice `slot` at the position of car `car` (record 0x148 bytes
   from ObjPosTable; y negated for the sound system) with pitch from the int16 fields +0x7c / +0x7e:
   ((a >> 2) + 1000 - (b >> 7)) * 0x5622 / 4096 (0x5622 = 22050 Hz); voice slot2 (if not -1) gets the same
   position and volume b - 10000.  TODO(RE): +0x7c/+0x7e presumably engine revs / load. */
/* 004d68da: положение (x, -y, z) машины car из таблицы 00d07888 (запись 0x148) -> голос slot; высота голоса slot — по полям
   +0x7c/+0x7e (((a>>2)+1000-(b>>7))*0x5622/4096); голос slot2 (если не -1) — то же положение и громкость b-10000. */
void P75_CarVoice(int32_t car, int32_t slot, int32_t slot2) {
  const uint8_t *r = (const uint8_t *)ObjPosTable + (size_t)car * 0x148;
  int16_t a, b;
  memcpy(&a, r + 0x7c, 2); memcpy(&b, r + 0x7e, 2);
  int32_t x = p75_i32(r), y = p75_i32(r + 4), z = p75_i32(r + 8);
  P56_SetVoicePos(slot, (float)x, (float)(int32_t)(0u - (uint32_t)y), (float)z);
  int32_t v = ((((int32_t)a >> 2) + 1000) - ((int32_t)b >> 7)) * 0x5622;
  SoundSetPos00523F8A(slot, v / 4096);
  if (slot2 != -1) {
    P56_SetVoicePos(slot2, (float)x, (float)(int32_t)(0u - (uint32_t)y), (float)z);
    P48_SetVoiceVolume(slot2, (int32_t)b - 10000);
  }
}

/* P75_BmpToPage — Game.exe 0040dae1.  Cuts a 256x256 block at (x0, y0) from a 640x480 32-bit picture into the
   16-bit texture page P75_Page as RGB555 (byte 0 -> bits 10..14, byte 1 -> 5..9, byte 2 -> 0..4); pixels past
   the picture edge are left unchanged.  Returns P75_Page. */
/* 0040dae1: из картинки src (BGRA, 640 в строке, 480 строк) вырезать 256x256 с угла (x0, y0) в RGB555 (5 бит каналов:
   R<<10 | G<<5 | B, где байты +0, +1, +2) -> 005d7e40; вне картинки пиксели не трогаются. Возвращает 005d7e40. */
uint8_t *P75_BmpToPage(const uint8_t *src, int32_t x0, int32_t y0) {
  for (int32_t y = 0; y < 0x100; y++) {
    if (y0 + y >= 0x1e0) continue;
    for (int32_t x = 0; x < 0x100; x++) {
      if (x0 + x >= 0x280) continue;
      const uint8_t *p = src + ((size_t)(y0 + y) * 0x280 + (size_t)(x0 + x)) * 4;
      P75_Page[y * 0x100 + x] = (uint16_t)(((p[0] >> 3) << 10) | ((p[1] >> 3) << 5) | (p[2] >> 3));
    }
  }
  return (uint8_t *)P75_Page;
}
