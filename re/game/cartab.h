/* v1.44: единая таблица игроков/машин 00d077c0 (66 записей по 0x148 байт: 0 — игрок, 1..64 — машины, 0x41 — запасная 00d0cb08).
   Адрес 00d07888 (позиция игрока) — поле +0xc8 записи 0. Все прежние native-переменные внутри таблицы (P56_Objs, P60_Cars,
   ObjPosTable, P59_PosX/Y/Z, PlayerPosX/Z, P94_Heading, P16_Level, P62_Spd, P59_CarRecs, P88_ObjX/Z…) — макросы CARTAB_VAR
   над одним массивом P99_Cars; в hook-сборке — ячейки Game.exe как раньше. Полей-указателей в известной части записи нет;
   если найдутся — только uint32_t-адреса (стандарт v1.42, re_ptr). */
#pragma once
#include <stdint.h>
#include <stddef.h>

#pragma pack(push, 1)
typedef struct {
  uint8_t  f00[4];        /* +0x00 флаги (байт 0 — состояние) */
  int16_t  mat[9];        /* +0x04 матрица ориентации 3×3 (fixed 4.12) */
  uint8_t  f16[2];
  int32_t  pos2[3];       /* +0x18 позиция (x, y, z) — копия для коллизий */
  uint8_t  f24[0x1c];
  int32_t  f40[0xe];      /* +0x40..+0x74 скорости/силы (сбрасываются при старте); +0x40 velocity, +0x4c angular velocity,
                             +0x58 force, +0x68 torque — see carfields.h */
  uint8_t  f78[4][4];     /* +0x78 колёса: 4 × 4 байта (+0 — контакт) */
  uint8_t  f88[0x40];
  int32_t  pos[3];        /* +0xc8 позиция x, y, z (00d07888 для игрока) */
  uint8_t  fd4[0x14];
  int16_t  ang[3];        /* +0xe8 углы (+0xea — курс) */
  uint8_t  fee[2];
  int32_t  ff0;           /* +0xf0 */
  int32_t  ff4;
  int32_t  ff8;           /* +0xf8 газ/направление (знак) */
  int32_t  ffc;           /* +0xfc */
  int32_t  heading;       /* +0x100 курс int (0..0xfff) */
  int32_t  f104;
  int32_t  f108;
  int32_t  f10c;          /* +0x10c обороты/скорость (fixed <<12) */
  int32_t  speed;         /* +0x110 скорость */
  int32_t  f114, f118;
  int32_t  damage[3];     /* +0x11c..+0x124 — first three of the six damage zones +0x11c..+0x130 (P142_CopDrive sums
                             them, ported106.c reads damage[side]); see carfields.h CAR_DAMAGE.  Called vel[3] before
                             2026-10 (it never held a velocity). */
  int32_t  f128, f12c, f130, f134, f138;
  uint16_t f13c;
  uint8_t  f13e[2];
  uint8_t  f140, f141;
  uint8_t  gear;          /* +0x142 передача (0..3) */
  uint8_t  f143;
  int16_t  f144, f146;
} p99_car_t;
#pragma pack(pop)
_Static_assert(sizeof(p99_car_t) == 0x148, "p99_car_t");
_Static_assert(offsetof(p99_car_t, pos) == 0xc8 && offsetof(p99_car_t, heading) == 0x100 && offsetof(p99_car_t, gear) == 0x142, "p99_car_t layout");
_Static_assert(offsetof(p99_car_t, ang) == 0xe8 && offsetof(p99_car_t, ff8) == 0xf8 && offsetof(p99_car_t, f10c) == 0x10c, "p99_car_t layout2");
_Static_assert(offsetof(p99_car_t, pos2) == 0x18 && offsetof(p99_car_t, f78) == 0x78 && offsetof(p99_car_t, damage) == 0x11c, "p99_car_t layout3");
#define P99_CARS_N    66
#define P99_CARS_ADDR 0x00d077c0u
typedef p99_car_t p99_cars_t[P99_CARS_N];

#ifdef RE_HOOK_BUILD
#  define P99_Cars (*(p99_cars_t *)(uintptr_t)P99_CARS_ADDR)
#  define CARTAB_VAR(type, name, addr) (*(type *)(uintptr_t)(addr))
#else
extern p99_cars_t P99_Cars;
#  define CARTAB_VAR(type, name, addr) (*(type *)((uint8_t *)P99_Cars + ((uint32_t)(addr) - P99_CARS_ADDR)))
#endif
#define P99_Car(i)    (P99_Cars[(i)])        /* запись i (0 — игрок, 00d077c0 + i*0x148) */
