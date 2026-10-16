/* v1.59, ported114 — восстановлено из Game.exe. Все функции cdecl (ret без операнда проверен work/rets.py). */
#pragma once
#include <stdint.h>
#include "gvar.h"
#define P114_Black   GAME_VAR(p114_rgb_t, P114_Black, 0x00b1ffc0)    /* цвет 3 байта (BSS, чёрный) для рамок титров */
typedef uint8_t p114_rgb_t[4];
#define P114_BlinkCnt GAME_VAR(int32_t, P114_BlinkCnt, 0x005f7e68)  /* мигание выбранного пункта меню */
#define P114_BlinkOn  GAME_VAR(int32_t, P114_BlinkOn, 0x005f7e6c)
#define P114_RepCnt   GAME_VAR(int32_t, P114_RepCnt, 0x005f7e70)    /* автоповтор джойстика */
#define P114_RepDelay GAME_VAR(int32_t, P114_RepDelay, 0x0054aa48)  /* .data 10 */
#ifndef RE_HOOK_BUILD
extern p114_rgb_t P114_Black; extern int32_t P114_BlinkCnt, P114_BlinkOn, P114_RepCnt, P114_RepDelay;
#endif
void P114_TexDownloadMip(int32_t tmu, int32_t addr, int32_t evenOdd, int32_t info, int32_t handle); /* 0041d53c */
void P114_PaperMark(int32_t idx);            /* 004e5fd7: отметка пункта «бумаги» (крест линиями или полоса LINE) */
void P114_CreditsDraw(void);                 /* 004a995c: кадр титров */
void P114_PartModels(void);                  /* 005128b7: частицы-модели по 5 текстурам */
void P114_Timer(int32_t *t);                 /* 004f5afe: таймер скрипта (кадры → мин/сек/сотые) */
void P114_ColorFlash(void);                  /* 004e8bd0: кольца дыма + цветная вспышка на весь экран */
void P114_PathDraw(uint8_t *node, int32_t mode); /* 0050cfeb: отладочный путь копа (узлы по 0x20) */
void P114_DebrisAll(void);                   /* 004b3e55: все обломки P97_Debris (флаг 2) значками, затем тени при 00d11880 */
void P114_DrawSpr(float x, float y, float sx, float sy, void *ic, int32_t r, int32_t g, int32_t b, int32_t blend); /* 004d8511 */
void P114_CamFadeFrame(void);                /* 0049f474: затемнение кадра камеры режиссёра (две полосы), смена кадра, окно 3D по высоте */
void P114_RadarMarks(void);                  /* 005073f1: значки игрока и целей P58_Objs на карте */
int32_t P114_MenuStep(uint32_t tbl, int32_t *cur);  /* 0040c8f1: шаг меню по таблице пунктов 0x10 (три обработчика + переходы), -1 — выход */
