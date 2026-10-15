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
