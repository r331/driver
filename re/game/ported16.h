#pragma once
#include "gvar.h"
#include <stdint.h>
/* Мелкие функции: частицы, таймер бездействия, заполнение структур. */
#define P16_VAR(type, name, addr) GAME_VAR(type, name, addr)
#define P16_ParticleCount P16_VAR(int32_t, P16_ParticleCount, 0x011171a0)
#define P16_ParticleBase  P16_VAR(uint8_t, P16_ParticleBase, 0x0110e160)
#define P16_IdleMode      P16_VAR(int32_t, P16_IdleMode, 0x00c810c4)
#define P16_Level         CARTAB_VAR(int32_t, P16_Level, 0x00d078b0)
#define P16_FlagA         P16_VAR(int32_t, P16_FlagA, 0x00b5a778)
#define P16_FlagB         P16_VAR(int32_t, P16_FlagB, 0x00b87ee4)
#define P16_IdleCounter   P16_VAR(int32_t, P16_IdleCounter, 0x00d0778c)
#define P16_FlagC         P16_VAR(int32_t, P16_FlagC, 0x00bdfa58)
#define P16_FlagD         P16_VAR(int32_t, P16_FlagD, 0x00bdfa44)
#define P16_IdleArg1      P16_VAR(int32_t, P16_IdleArg1, 0x00c810e8)
#define P16_IdleArg2      P16_VAR(int32_t, P16_IdleArg2, 0x00c81100)
#ifndef RE_HOOK_BUILD
extern int32_t P16_ParticleCount, P16_IdleMode, P16_FlagA, P16_FlagB, P16_IdleCounter, P16_FlagC, P16_FlagD, P16_IdleArg1, P16_IdleArg2;
extern uint8_t P16_ParticleBase;
#endif
void P16_StepParticles(void);                 /* 004b9d79 */
void P16_IdleTimer(void);                     /* 004e12e4 */
void P16_FillHudRect(uint32_t *p, uint32_t a, uint32_t rgb, uint32_t b, int c, int d); /* 0050268f */
/* v2.21: ячейки образа данных — один объект на адрес. Раньше эти имена были отдельными native-переменными (tools/gen_gvar_img.py
   не разбирает обёртку P15_VAR/P16_VAR), и запись через другой псевдоним (D_00b87e30, P14_00c810c4, G6_00B5A778 …) через них не была
   видна: так, интервью Undercover (ladder пишет D_00b87e30 = 4) не запускалось — P56_HudTick/P145_LevelLoad проверяли P15_State.
   Пары: P16_IdleMode = P14_00c810c4 (итог миссии: 0x8000 — успех, 0xff0 — провал), P16_IdleArg1/2 = P14_00c810e8/P14_00c81100,
   P16_FlagA = G6_00B5A778, P16_FlagB = P14_00b87ee4, P16_FlagC/D = P14_00bdfa58/P14_00bdfa44, P16_IdleCounter = P14_00d0778c. */
#if !defined(RE_HOOK_BUILD) && !defined(RE_GVAR_PLAIN)
#undef P16_IdleMode
#define P16_IdleMode (*(int32_t *)re_gvar(0x00c810c4u, sizeof(int32_t), (void *)&P16_IdleMode))
#undef P16_FlagA
#define P16_FlagA (*(int32_t *)re_gvar(0x00b5a778u, sizeof(int32_t), (void *)&P16_FlagA))
#undef P16_FlagB
#define P16_FlagB (*(int32_t *)re_gvar(0x00b87ee4u, sizeof(int32_t), (void *)&P16_FlagB))
#undef P16_IdleCounter
#define P16_IdleCounter (*(int32_t *)re_gvar(0x00d0778cu, sizeof(int32_t), (void *)&P16_IdleCounter))
#undef P16_FlagC
#define P16_FlagC (*(int32_t *)re_gvar(0x00bdfa58u, sizeof(int32_t), (void *)&P16_FlagC))
#undef P16_FlagD
#define P16_FlagD (*(int32_t *)re_gvar(0x00bdfa44u, sizeof(int32_t), (void *)&P16_FlagD))
#undef P16_IdleArg1
#define P16_IdleArg1 (*(int32_t *)re_gvar(0x00c810e8u, sizeof(int32_t), (void *)&P16_IdleArg1))
#undef P16_IdleArg2
#define P16_IdleArg2 (*(int32_t *)re_gvar(0x00c81100u, sizeof(int32_t), (void *)&P16_IdleArg2))
#endif
