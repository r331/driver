#pragma once
#include <stdint.h>
#include "gvar.h"
/* v1.81: ported136 — колёса машины, компиляция скрипта событий, цикл игры, инициализация фронтенда, карта-оверлей. Все cdecl. */
typedef int32_t p136_rot_t[66];
typedef uint8_t p136_pal_t[0x400];
typedef char    p136_path_t[0x100];
typedef uint32_t p136_pal16_t[256];
#define P136_WheelRot  GAME_VAR(p136_rot_t, P136_WheelRot, 0x00b1fce0)   /* угол качения передних колёс (0..0xfff) по машинам */
#define P136_WheelRotB GAME_VAR(p136_rot_t, P136_WheelRotB, 0x00b1fde8)  /* то же для задних */
#define P136_EvPath    GAME_VAR(p136_path_t, P136_EvPath, 0x01134140)    /* строка sprintf 004a3d40 */
#define P136_TsdPalA   GAME_VAR(p136_pal_t, P136_TsdPalA, 0x012533e0)    /* палитры FRONTEND.TSD (B,G,R,X) */
#define P136_TsdPalB   GAME_VAR(p136_pal_t, P136_TsdPalB, 0x012537e0)
#define P136_Pal16     GAME_VAR(p136_pal16_t, P136_Pal16, 0x01271680)    /* 16-битная палитра из P136_TsdPalA */
#define P136_MapName   GAME_VAR(p136_path_t, P136_MapName, 0x00c80fa0)   /* имя карты-оверлея, если задано (иначе по городу) */
#define P136_MapScroll GAME_VAR(int32_t, P136_MapScroll, 0x00c80884)
#define P136_MapPal    GAME_VAR(p136_pal_t, P136_MapPal, 0x012587e0)     /* палитра .MAP (B,G,R,X) */
#define P136_MapPalOn  GAME_VAR(int32_t, P136_MapPalOn, 0x01252afc)
#ifndef RE_HOOK_BUILD
extern p136_rot_t P136_WheelRot, P136_WheelRotB; extern p136_path_t P136_EvPath, P136_MapName; extern p136_pal_t P136_TsdPalA, P136_TsdPalB, P136_MapPal;
extern p136_pal16_t P136_Pal16; extern int32_t P136_MapScroll, P136_MapPalOn;
#endif
void    P136_DrawWheels(int32_t car, const float *mat, int32_t mode);   /* 004a1d4c */
void    P136_CompileEvents(void);                                       /* 004a3d40 */
void    P136_GameLoop(int32_t replay);                                  /* 0040c20b */
int32_t P136_FrontInit(void);                                           /* 0040bf50 */
void    P136_OverlayMap(void);                                          /* 00501770 */
