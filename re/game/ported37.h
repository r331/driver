#pragma once
#include "gvar.h"
#include "../platform/plat.h"
#include "ported34.h"
#include "ported35.h"
#include "ported36.h"
#include "ported6.h"
#include <stdint.h>
/* DirectInput, шаг C (Input.c): инициализация ввода (004e2ee0) и колбэк перечисления джойстиков (004e3cdf) над plat_di_create/…/plat_di_enum_joysticks. */
#define P37_MouseShared GAME_VAR(int32_t, P37_MouseShared, 0x00575f28)  /* ненулевой — мышь в неэксклюзивном режиме (флаги 5, иначе 6) */
#ifndef RE_HOOK_BUILD
extern int32_t P37_MouseShared;
#endif
int32_t P37_JoyEnumCb(const void *inst, void *di);   /* 004e3cdf: настроить найденный джойстик (оси ±31, мёртвая зона 3, FF-эффекты) и записать в таблицы; 1 — продолжать, 0 — таблица (8) полна */
int32_t P37_InitInput(void);                          /* 004e2ee0: создать DirectInput, клавиатуру, мышь (событие + буфер 32) и джойстики; 1 — успех, 0 — ошибка (всё освобождено) */
