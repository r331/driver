/* v1.49 — восстановлено из Game.exe. Все функции cdecl (ret без операнда проверен по Game.exe; метка __fastcall у 004ab127
   ложная — push ecx резервирует локальную). Экран графики 00409622 (.data меню 0054a170..0054a6f8 — одна таблица
   P104_MenuGfx, game/menugfx.h), сброс миссии 004e4bdc, старт поворота трафика 0049565b, таблицы обломков 004ab127,
   текстура вмятин / операции модели машины по повреждениям 004c1c23. */
#pragma once
#include "gvar.h"
#include "reptr.h"
#include "cartab.h"
#include "menugfx.h"
#include <stdint.h>

typedef float    p104_deb_t[256 * 12];     /* 256 записей по 0x30: три вектора (x,y,z,pad) */
typedef uint32_t p104_buf760_t[16];
#define P104_DebB    GAME_VAR(p104_deb_t, P104_DebB, 0x010ffd20)     /* обломки: вершины ±7 */
#define P104_DebA    GAME_VAR(p104_deb_t, P104_DebA, 0x01102d20)     /* обломки: вершины ±10 */
#define P104_DebC    GAME_VAR(p104_deb_t, P104_DebC, 0x0111a400)     /* обломки: треугольник 35/40/30 */
#define P104_Buf760  GAME_VAR(p104_buf760_t, P104_Buf760, 0x00cfe760) /* буфер, на который указывает 00562d7c */
#define P104_12B26C  GAME_VAR(int32_t, P104_12B26C, 0x0112b26c)
#define P104_139A28  GAME_VAR(int32_t, P104_139A28, 0x01139a28)
#ifndef RE_HOOK_BUILD
extern p104_deb_t P104_DebA, P104_DebB, P104_DebC; extern p104_buf760_t P104_Buf760;
extern int32_t P104_12B26C, P104_139A28;
#endif

void     P104_GfxMenuInit(void);            /* 00409622 */
void     P104_MissionInit(void);            /* 004e4bdc */
int32_t  P104_TrafficTurn(uint32_t dir);    /* 0049565b */
void     P104_DebrisTabs(void);             /* 004ab127 */
void     P104_CarDents(int32_t car);        /* 004c1c23 */
