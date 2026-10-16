#pragma once
#include <stdint.h>
#include "gvar.h"
/* v1.71: ported126 — список палитр карты (LEVELS\FLAT.D3D), начальная позиция игрока/повтора погони, капли вокруг точки
   и их обход квадратом, снимок экрана PIC_####.BMP, отладочные клавиши кадра, точки появления «спаунов» у игрока,
   BMP с плавным появлением, дым при отрыве колёс, обломки у обочины. Все функции cdecl; 004e919d и 004d74e0
   в Ghidra — __fastcall, но ECX не читается (push ecx — резерв локала): native-параметр мусорный, вызывать с 0. */
typedef uint8_t p126_spawn_t[4 * 0x18];
#define P126_PicNum    GAME_VAR(int32_t, P126_PicNum, 0x005604b4)     /* .data, начальное −1: номер следующего PIC_####.BMP */
#define P126_DebugOn   GAME_VAR(int32_t, P126_DebugOn, 0x00575f4c)    /* .data, начальное 1: отладочные клавиши */
#define P126_Spawn     GAME_VAR(p126_spawn_t, P126_Spawn, 0x00c82440) /* 4 записи 0x18: +0 1, +1 вид, +2 задержка, +4 кадр, +8..+0x14 точка */
#define P126_SpawnN    GAME_VAR(int32_t, P126_SpawnN, 0x00c82528)
#define P126_SpawnSide GAME_VAR(int32_t, P126_SpawnSide, 0x00c824d4) /* 0 — вид 1 (шаг 0x28), иначе вид 2 (шаг 0x14) */
#define P126_SpawnAxis GAME_VAR(int32_t, P126_SpawnAxis, 0x00c824d8) /* 0 — разброс по X, иначе по Z */
#define P126_SpawnT    GAME_VAR(int32_t, P126_SpawnT, 0x00c8252c)
#define P126_TgtY      GAME_VAR(float, P126_TgtY, 0x00c82514)
#define P126_TgtW      GAME_VAR(float, P126_TgtW, 0x00c8251c)
#define P126_PtY       GAME_VAR(float, P126_PtY, 0x00c824b4)
#define P126_PtW       GAME_VAR(float, P126_PtW, 0x00c824bc)
#define P126_SideY     GAME_VAR(float, P126_SideY, 0x00c824c4)
#define P126_SideW     GAME_VAR(float, P126_SideW, 0x00c824cc)
#ifndef RE_HOOK_BUILD
#pragma push_macro("P126_PicNum") /*gvi*/
#undef P126_PicNum /*gvi*/
#pragma push_macro("P126_DebugOn") /*gvi*/
#undef P126_DebugOn /*gvi*/
#pragma push_macro("P126_SpawnN") /*gvi*/
#undef P126_SpawnN /*gvi*/
#pragma push_macro("P126_SpawnSide") /*gvi*/
#undef P126_SpawnSide /*gvi*/
#pragma push_macro("P126_SpawnAxis") /*gvi*/
#undef P126_SpawnAxis /*gvi*/
#pragma push_macro("P126_SpawnT") /*gvi*/
#undef P126_SpawnT /*gvi*/
extern int32_t P126_PicNum, P126_DebugOn, P126_SpawnN, P126_SpawnSide, P126_SpawnAxis, P126_SpawnT;
#pragma pop_macro("P126_SpawnT") /*gvi*/
#pragma pop_macro("P126_SpawnAxis") /*gvi*/
#pragma pop_macro("P126_SpawnSide") /*gvi*/
#pragma pop_macro("P126_SpawnN") /*gvi*/
#pragma pop_macro("P126_DebugOn") /*gvi*/
#pragma pop_macro("P126_PicNum") /*gvi*/
#pragma push_macro("P126_Spawn") /*gvi*/
#undef P126_Spawn /*gvi*/
extern p126_spawn_t P126_Spawn;
#pragma pop_macro("P126_Spawn") /*gvi*/
#pragma push_macro("P126_TgtY") /*gvi*/
#undef P126_TgtY /*gvi*/
#pragma push_macro("P126_TgtW") /*gvi*/
#undef P126_TgtW /*gvi*/
#pragma push_macro("P126_PtY") /*gvi*/
#undef P126_PtY /*gvi*/
#pragma push_macro("P126_PtW") /*gvi*/
#undef P126_PtW /*gvi*/
#pragma push_macro("P126_SideY") /*gvi*/
#undef P126_SideY /*gvi*/
#pragma push_macro("P126_SideW") /*gvi*/
#undef P126_SideW /*gvi*/
extern float P126_TgtY, P126_TgtW, P126_PtY, P126_PtW, P126_SideY, P126_SideW;
#pragma pop_macro("P126_SideW") /*gvi*/
#pragma pop_macro("P126_SideY") /*gvi*/
#pragma pop_macro("P126_PtW") /*gvi*/
#pragma pop_macro("P126_PtY") /*gvi*/
#pragma pop_macro("P126_TgtW") /*gvi*/
#pragma pop_macro("P126_TgtY") /*gvi*/
#endif
void P126_ReadMapPals(const char *name);   /* 004efafd: записи {слот, список, число} в 00b31ee8/00b31eec (map.c:0xd88) */
void P126_PlayerStart(void);               /* 004906f9: позиция/запись игрока (CHASE: ReplayData\Chase\%s.LEADER/PLAYER) */
void P126_DropsAt(const float *pos);       /* 004e9006: капли у объектов с флагом модели 0x400 в клетке pos */
void P126_DropScan(int32_t unused);        /* 004e919d: 004e9006 вокруг P76_ColObj по P76_Angle (10 / 0x1e / 0x3c) */
void P126_ScreenShot(void);                /* 004d9951: PIC_%04d.BMP (24 бита, снизу вверх) */
void P126_DebugKeys(int32_t unused);       /* 004d74e0: отладочные клавиши кадра (зум, зеркало, снимок, урон) */
void P126_SpawnInit(void);                 /* 004f1745: до 4 точек появления у игрока, точка камеры ±800 */
void P126_ShowBmpFade(const char *name, int32_t wait); /* 0040c6bb: BMP 640×480 с затемнением 0→1→0 (шаг 0.05) */
void P126_WheelSmoke(uint8_t *car);        /* 004e10e3: дым после отрыва колёс (+0x78 + 4·i) */
void P126_KerbDebris(uint8_t *car);        /* 004ad244: обломки у обочины в 10000 от машины */
/* gvar-img v2.03 begin (tools/gen_gvar_img.py) */
#if !defined(RE_HOOK_BUILD) && !defined(RE_GVAR_PLAIN)
#undef P126_PicNum
#define P126_PicNum (*(int32_t *)re_gvar(0x005604b4u, sizeof(int32_t), (void *)&P126_PicNum))
#undef P126_DebugOn
#define P126_DebugOn (*(int32_t *)re_gvar(0x00575f4cu, sizeof(int32_t), (void *)&P126_DebugOn))
#undef P126_Spawn
#define P126_Spawn (*(p126_spawn_t *)re_gvar(0x00c82440u, sizeof(p126_spawn_t), (void *)&P126_Spawn))
#undef P126_SpawnN
#define P126_SpawnN (*(int32_t *)re_gvar(0x00c82528u, sizeof(int32_t), (void *)&P126_SpawnN))
#undef P126_SpawnSide
#define P126_SpawnSide (*(int32_t *)re_gvar(0x00c824d4u, sizeof(int32_t), (void *)&P126_SpawnSide))
#undef P126_SpawnAxis
#define P126_SpawnAxis (*(int32_t *)re_gvar(0x00c824d8u, sizeof(int32_t), (void *)&P126_SpawnAxis))
#undef P126_SpawnT
#define P126_SpawnT (*(int32_t *)re_gvar(0x00c8252cu, sizeof(int32_t), (void *)&P126_SpawnT))
#undef P126_TgtY
#define P126_TgtY (*(float *)re_gvar(0x00c82514u, sizeof(float), (void *)&P126_TgtY))
#undef P126_TgtW
#define P126_TgtW (*(float *)re_gvar(0x00c8251cu, sizeof(float), (void *)&P126_TgtW))
#undef P126_PtY
#define P126_PtY (*(float *)re_gvar(0x00c824b4u, sizeof(float), (void *)&P126_PtY))
#undef P126_PtW
#define P126_PtW (*(float *)re_gvar(0x00c824bcu, sizeof(float), (void *)&P126_PtW))
#undef P126_SideY
#define P126_SideY (*(float *)re_gvar(0x00c824c4u, sizeof(float), (void *)&P126_SideY))
#undef P126_SideW
#define P126_SideW (*(float *)re_gvar(0x00c824ccu, sizeof(float), (void *)&P126_SideW))
#endif
/* gvar-img v2.03 end */
