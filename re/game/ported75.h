#pragma once
#include "gvar.h"
#include "unported.h"
#include "engine.h"
#include "crt.h"
#include "globalsets.h"
#include "smallfuncs.h"
#include "smallfuncs2.h"
#include "ported6.h"
#include "ported7.h"
#include "ported12.h"
#include "ported16.h"
#include "ported41.h"
#include "ported48.h"
#include "ported51.h"
#include "ported54.h"
#include "ported55.h"
#include "ported56.h"
#include "ported59.h"
#include "ported62.h"
#include "ported60.h"
#include "widgets.h"
#include "director.h"
#include <stdint.h>
/* Шаг D: 8 функций (все cdecl) — трафик (позиция появления, одно появление, пополнение), звук фона (случайные звуки),
   звук машины игрока, сброс объектов, перенос картинки 640x480 в страницу 256x256 (15 бит).
   Запись таблицы появления 01139a60: 12 байт: +0 int16 узел (-1 — любой), +2 байт, +4/+8 int. */
typedef uint8_t p75_spawn_t[12 * 256];
typedef uint16_t p75_page_t[0x10000];
#define P75_E4      GAME_VAR(int32_t, P75_E4, 0x011426e4)
#define P75_E8      GAME_VAR(int32_t, P75_E8, 0x011426e8)
#define P75_12BC    GAME_VAR(int32_t, P75_12BC, 0x005512bc)
#define P75_4288    GAME_VAR(int32_t, P75_4288, 0x01144288)
#define P75_43D0    GAME_VAR(int32_t, P75_43D0, 0x011443d0)
#define P75_43CC    GAME_VAR(int32_t, P75_43CC, 0x011443cc)
#define P75_Spawn   GAME_VAR(p75_spawn_t, P75_Spawn, 0x01139a60)
#define P75_B20350  GAME_VAR(int32_t, P75_B20350, 0x00b20350)
#define P75_B31EDC  GAME_VAR(int32_t, P75_B31EDC, 0x00b31edc)
#define P75_D022E0  GAME_VAR(int32_t, P75_D022E0, 0x00d022e0)
#define P75_B31ED0  GAME_VAR(int32_t, P75_B31ED0, 0x00b31ed0)
#define P75_CF1F60  GAME_VAR(uint8_t, P75_CF1F60, 0x00cf1f60)
#define P75_Ptr562D7C GAME_VAR(uint32_t, P75_Ptr562D7C, 0x00562d7c)
#define P75_Page    GAME_VAR(p75_page_t, P75_Page, 0x005d7e40)
#ifndef RE_HOOK_BUILD
extern int32_t P75_E4, P75_E8, P75_12BC, P75_4288, P75_43D0, P75_43CC, P75_B20350, P75_B31EDC, P75_D022E0, P75_B31ED0;
extern p75_spawn_t P75_Spawn; extern uint8_t P75_CF1F60; extern uint32_t P75_Ptr562D7C; extern p75_page_t P75_Page;
#endif
void    P75_TrafficPos(int32_t cls, int32_t side, int32_t rev, int32_t last, uint32_t pick); /* 004913cc: положение появления машины на стороне side класса cls -> 01139a30/01139a2c */
void    P75_TrafficSpawn(void);                                       /* 00492e42: одно появление трафика (или запись из повтора) */
void    P75_TrafficFill(void);                                        /* 0049512b: пополнение трафика до нужного числа / чтение повтора */
void    P75_BgSound(void);                                            /* 004d6c5a: случайные фоновые звуки */
void    P75_CarSound(void);                                           /* 004d6dac: звук при смене клетки карты под игроком */
void    P75_ResetObjs(void);                                          /* 004ee065: сброс выбора и объектов */
void    P75_CarVoice(int32_t car, int32_t slot, int32_t slot2);       /* 004d68da: положение и высота звука двигателя машины */
uint8_t *P75_BmpToPage(const uint8_t *src, int32_t x0, int32_t y0);   /* 0040dae1: кусок 256x256 из BGRA 640x480 в RGB555 -> 005d7e40 */
