#pragma once
#include <stdint.h>
#include "gvar.h"
/* v1.83: ported138 — тень машины, загрузка миссии, повторы (CFG/PADS/LEADER/PINGS), конец записи трейла. Все cdecl. */
typedef char p138_s40_t[0x40];
typedef char p138_s100_t[0x100];
#define P138_B5A8CC   GAME_VAR(int32_t, P138_B5A8CC, 0x00b5a8cc)        /* стартовое значение из CFG (+8) при типе 2 */
#define P138_C80954   GAME_VAR(int32_t, P138_C80954, 0x00c80954)
#define P138_C80F40   GAME_VAR(int32_t, P138_C80F40, 0x00c80f40)
#define P138_C80F7C   GAME_VAR(int32_t, P138_C80F7C, 0x00c80f7c)
#define P138_C8168C   GAME_VAR(int32_t, P138_C8168C, 0x00c8168c)
#define P138_LevBuf   GAME_VAR(p138_s100_t, P138_LevBuf, 0x00c81780)    /* имя .LEV для уровня без миссии (P77_LevelName) */
#define P138_PadsPath GAME_VAR(p138_s40_t, P138_PadsPath, 0x00c4d680)   /* ReplayData\User\%s.PADS */
#define P138_CfgName  GAME_VAR(p138_s40_t, P138_CfgName, 0x00c4d6c0)    /* имя повтора (strcpy) */
#define P138_CamsPath GAME_VAR(p138_s40_t, P138_CamsPath, 0x00c4d7c0)   /* ReplayData\User\%s.CAMS */
#ifndef RE_HOOK_BUILD
#pragma push_macro("P138_B5A8CC") /*gvi*/
#undef P138_B5A8CC /*gvi*/
#pragma push_macro("P138_C80954") /*gvi*/
#undef P138_C80954 /*gvi*/
#pragma push_macro("P138_C80F40") /*gvi*/
#undef P138_C80F40 /*gvi*/
#pragma push_macro("P138_C80F7C") /*gvi*/
#undef P138_C80F7C /*gvi*/
#pragma push_macro("P138_C8168C") /*gvi*/
#undef P138_C8168C /*gvi*/
extern int32_t P138_B5A8CC, P138_C80954, P138_C80F40, P138_C80F7C, P138_C8168C;
#pragma pop_macro("P138_C8168C") /*gvi*/
#pragma pop_macro("P138_C80F7C") /*gvi*/
#pragma pop_macro("P138_C80F40") /*gvi*/
#pragma pop_macro("P138_C80954") /*gvi*/
#pragma pop_macro("P138_B5A8CC") /*gvi*/
#pragma push_macro("P138_LevBuf") /*gvi*/
#undef P138_LevBuf /*gvi*/
#pragma push_macro("P138_PadsPath") /*gvi*/
#undef P138_PadsPath /*gvi*/
#pragma push_macro("P138_CfgName") /*gvi*/
#undef P138_CfgName /*gvi*/
#pragma push_macro("P138_CamsPath") /*gvi*/
#undef P138_CamsPath /*gvi*/
extern p138_s100_t P138_LevBuf; extern p138_s40_t P138_PadsPath, P138_CfgName, P138_CamsPath;
#pragma pop_macro("P138_CamsPath") /*gvi*/
#pragma pop_macro("P138_CfgName") /*gvi*/
#pragma pop_macro("P138_PadsPath") /*gvi*/
#pragma pop_macro("P138_LevBuf") /*gvi*/
#endif
void    P138_CarShadow(int32_t car);            /* 00520278: тень машины (квадрат или сетка по рельефу) */
int32_t P138_LoadMission(int32_t n);            /* 004f4180: 1 — успех */
int32_t P138_ReplayCfg(const char *name);       /* 00517d58: ReplayData\User|Demo\name.CFG; 1 — успех */
void    P138_ReplayLoad(void);                  /* 005181da: PADS/LEADER/PINGS погони + PADS игрока */
void    P138_ReplayInit(void);                  /* 0051879f: буфер записи, LEADER погони */
void    P138_LoadPads(void);                    /* 00518bbc: PADS игрока из P138_PadsPath */
void    P138_TrailEnd(void);                    /* 004fbfad: метка конца TRAIL.DAT, последний конус в лог */
void    P138_Blk84Clear(void);                 /* memset(00c810c0, 0, 0x210) + native-псевдонимы внутри (v1.84: общая с 004f4596) */
/* gvar-img v2.03 begin (tools/gen_gvar_img.py) */
#if !defined(RE_HOOK_BUILD) && !defined(RE_GVAR_PLAIN)
#undef P138_B5A8CC
#define P138_B5A8CC (*(int32_t *)re_gvar(0x00b5a8ccu, sizeof(int32_t), (void *)&P138_B5A8CC))
#undef P138_C80954
#define P138_C80954 (*(int32_t *)re_gvar(0x00c80954u, sizeof(int32_t), (void *)&P138_C80954))
#undef P138_C80F40
#define P138_C80F40 (*(int32_t *)re_gvar(0x00c80f40u, sizeof(int32_t), (void *)&P138_C80F40))
#undef P138_C80F7C
#define P138_C80F7C (*(int32_t *)re_gvar(0x00c80f7cu, sizeof(int32_t), (void *)&P138_C80F7C))
#undef P138_C8168C
#define P138_C8168C (*(int32_t *)re_gvar(0x00c8168cu, sizeof(int32_t), (void *)&P138_C8168C))
#undef P138_LevBuf
#define P138_LevBuf (*(p138_s100_t *)re_gvar(0x00c81780u, sizeof(p138_s100_t), (void *)&P138_LevBuf))
#undef P138_PadsPath
#define P138_PadsPath (*(p138_s40_t *)re_gvar(0x00c4d680u, sizeof(p138_s40_t), (void *)&P138_PadsPath))
#undef P138_CfgName
#define P138_CfgName (*(p138_s40_t *)re_gvar(0x00c4d6c0u, sizeof(p138_s40_t), (void *)&P138_CfgName))
#undef P138_CamsPath
#define P138_CamsPath (*(p138_s40_t *)re_gvar(0x00c4d7c0u, sizeof(p138_s40_t), (void *)&P138_CamsPath))
#endif
/* gvar-img v2.03 end */
