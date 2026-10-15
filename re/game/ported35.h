#pragma once
#include "gvar.h"
#include "../platform/plat.h"
#include "ported34.h"
#include "ported31.h"
#include "ported24.h"
#include "ported16.h"
#include "ported5.h"
#include "uihandlers3.h"
#include <stdint.h>
/* Force Feedback (Input.c) и создание DirectDraw (Render.c): 004e41d5, 004e429b, 004e3b3c, 00420b19 — над plat_di_*_effect / plat_dd_create. */
#define P35_PadX     GAME_VAR(int32_t, P35_PadX, 0x00d07790)     /* источник силы удара по X (ненулевой — есть удар) */
#define P35_FfX      GAME_VAR(int32_t, P35_FfX, 0x00b31e04)      /* текущий вектор силы */
#define P35_FfY      GAME_VAR(int32_t, P35_FfY, 0x00b31e08)
#define P35_FfPending GAME_VAR(int32_t, P35_FfPending, 0x00b31e10) /* удар ждёт отправки */
#define P35_InputMode GAME_VAR(uint8_t, P35_InputMode, 0x00562a44) /* 2 — джойстик */
#define P35_ReqBpp   GAME_VAR(int32_t, P35_ReqBpp, 0x00549ccc)    /* запрошенная глубина цвета */
#ifndef RE_HOOK_BUILD
extern int32_t P35_PadX, P35_FfX, P35_FfY, P35_FfPending, P35_ReqBpp;
extern uint8_t P35_InputMode;
#endif
int32_t P35_CreateEffectA(void *dev, int32_t slot);   /* 004e41d5: эффект «удар» в EffA[slot] (если FfA ещё нет); 1 — готово, 0 — ошибка */
int32_t P35_CreateEffectB(void *dev, int32_t slot);   /* 004e429b: перечислить эффект постоянной силы и создать «двигатель» в EffB[slot] */
void    P35_UpdateForce(void);                        /* 004e3b3c: отправить накопленные удар/двигатель в эффекты */
void   *P35_GetDirectDrawInterface(const void *guid); /* 00420b19: DirectDrawCreate + проверка режима 16/32 бит; NULL — ошибка */
