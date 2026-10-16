#pragma once
#include "gvar.h"
#include <stdint.h>
/* v1.96: ported151 — последние платформенные функции: таблица D3D-эмуляции Glide (0041cede), открытие окна/DirectDraw
   (0041ed98, grSstWinOpen эмуляции), проверка 3D-устройства (00420038), переоткрытие Glide с MoveWindow (00425f7b), WinMain (00521f10). */
typedef char p151_buf_t[0x100];
#define P151_DevIdx  GAME_VAR(int32_t, P151_DevIdx, 0x00a421cc)    /* номер выбранного устройства D3D (запись P74_DevTab) */
#define P151_No8bit  GAME_VAR(int32_t, P151_No8bit, 0x00a421ec)    /* «User requested no 8bit support» */
#define P151_FsFlag  GAME_VAR(int32_t, P151_FsFlag, 0x00b87ed4)    /* ≠ 0 — аргумент 5 grSstWinOpen (00425f7b) */
#define P151_Bpp     GAME_VAR(int32_t, P151_Bpp, 0x0125f3fc)       /* 16 (WinMain) */
#define P151_ErrBuf  GAME_VAR(p151_buf_t, P151_ErrBuf, 0x00b87d0c) /* текст фатальной ошибки языка/конфигурации */
#define P151_Empty10 GAME_VAR(int32_t, P151_Empty10, 0x00b87f10)   /* .bss: пустые строки журнала */
#define P151_Empty14 GAME_VAR(int32_t, P151_Empty14, 0x00b87f14)
#define P151_Proc    GAME_VAR(void *, P151_Proc, 0x00bdfa1c)       /* GetCurrentProcess */
#define P151_PrioOn  GAME_VAR(int32_t, P151_PrioOn, 0x00575f2c)    /* .data: менять приоритет процесса */
#ifndef RE_HOOK_BUILD
#pragma push_macro("P151_DevIdx") /*gvi*/
#undef P151_DevIdx /*gvi*/
#pragma push_macro("P151_No8bit") /*gvi*/
#undef P151_No8bit /*gvi*/
#pragma push_macro("P151_FsFlag") /*gvi*/
#undef P151_FsFlag /*gvi*/
#pragma push_macro("P151_Bpp") /*gvi*/
#undef P151_Bpp /*gvi*/
#pragma push_macro("P151_Empty10") /*gvi*/
#undef P151_Empty10 /*gvi*/
#pragma push_macro("P151_Empty14") /*gvi*/
#undef P151_Empty14 /*gvi*/
#pragma push_macro("P151_PrioOn") /*gvi*/
#undef P151_PrioOn /*gvi*/
extern int32_t P151_DevIdx, P151_No8bit, P151_FsFlag, P151_Bpp, P151_Empty10, P151_Empty14, P151_PrioOn;
#pragma pop_macro("P151_PrioOn") /*gvi*/
#pragma pop_macro("P151_Empty14") /*gvi*/
#pragma pop_macro("P151_Empty10") /*gvi*/
#pragma pop_macro("P151_Bpp") /*gvi*/
#pragma pop_macro("P151_FsFlag") /*gvi*/
#pragma pop_macro("P151_No8bit") /*gvi*/
#pragma pop_macro("P151_DevIdx") /*gvi*/
#pragma push_macro("P151_ErrBuf") /*gvi*/
#undef P151_ErrBuf /*gvi*/
extern p151_buf_t P151_ErrBuf; extern void *P151_Proc;
#pragma pop_macro("P151_ErrBuf") /*gvi*/
#endif
int32_t P151_InstallD3D(int32_t idx, int32_t no8bit, int32_t full);   /* 0041cede: 123 ячейки таблицы Glide → функции D3D-эмуляции; 0 — idx вне [0, P42_DevCount) */
int32_t P151_WinOpen(int32_t hwnd, int32_t mode, int32_t a2, int32_t a3, int32_t a4, int32_t a5, int32_t a6); /* 0041ed98 (stdcall ret 0x1c, grSstWinOpen): 1 — устройство готово */
int32_t P151_CheckDev(uint8_t *rec);                                  /* 00420038: проверка устройства записи 0x4c (devinfo — +0x48); 1 — годно */
int32_t P151_Reopen(int32_t hwnd, int32_t mode, int32_t keep);        /* 00425f7b: MoveWindow, grSstWinOpen по ширине экрана, таблицы и состояния */
int32_t P151_WinMain(int32_t hinst, int32_t prev, int32_t cmd, int32_t show); /* 00521f10 (stdcall ret 0x10) → код выхода 00b87e24 */
/* gvar-img v2.03 begin (tools/gen_gvar_img.py) */
#if !defined(RE_HOOK_BUILD) && !defined(RE_GVAR_PLAIN)
#undef P151_DevIdx
#define P151_DevIdx (*(int32_t *)re_gvar(0x00a421ccu, sizeof(int32_t), (void *)&P151_DevIdx))
#undef P151_No8bit
#define P151_No8bit (*(int32_t *)re_gvar(0x00a421ecu, sizeof(int32_t), (void *)&P151_No8bit))
#undef P151_FsFlag
#define P151_FsFlag (*(int32_t *)re_gvar(0x00b87ed4u, sizeof(int32_t), (void *)&P151_FsFlag))
#undef P151_Bpp
#define P151_Bpp (*(int32_t *)re_gvar(0x0125f3fcu, sizeof(int32_t), (void *)&P151_Bpp))
#undef P151_ErrBuf
#define P151_ErrBuf (*(p151_buf_t *)re_gvar(0x00b87d0cu, sizeof(p151_buf_t), (void *)&P151_ErrBuf))
#undef P151_Empty10
#define P151_Empty10 (*(int32_t *)re_gvar(0x00b87f10u, sizeof(int32_t), (void *)&P151_Empty10))
#undef P151_Empty14
#define P151_Empty14 (*(int32_t *)re_gvar(0x00b87f14u, sizeof(int32_t), (void *)&P151_Empty14))
#undef P151_PrioOn
#define P151_PrioOn (*(int32_t *)re_gvar(0x00575f2cu, sizeof(int32_t), (void *)&P151_PrioOn))
#endif
/* gvar-img v2.03 end */
