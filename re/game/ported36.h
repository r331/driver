#pragma once
#include "gvar.h"
#include "../platform/plat.h"
#include "ported34.h"
#include "ported35.h"
#include "ported19.h"
#include "ported21.h"
#include "ported9.h"
#include "ported6.h"
#include "ported5.h"
#include "ported31.h"
#include "uihandlers3.h"
#include <stdint.h>
/* DirectInput, шаг C (Input.c): захват устройства по номеру (004e3ffe), выбор джойстика (004e3769),
   кнопки геймпада в битовую маску (004e39ac), опрос джойстика и раскладки клавиш (004e3391). Все — cdecl. */
typedef int32_t P36_IntArr[8];
typedef uint8_t P36_Bytes80[0x50];
#define P36_JoyCount   GAME_VAR(int32_t, P36_JoyCount, 0x00b31e14)    /* число найденных джойстиков */
#define P36_JoyAxisCap GAME_VAR(P36_IntArr, P36_JoyAxisCap, 0x00b31d64) /* таблица по номеру джойстика → e28 */
#define P36_JoyAux     GAME_VAR(P36_IntArr, P36_JoyAux, 0x00b31ca0)     /* таблица по номеру джойстика → e2c */
#define P36_JoyFlag    GAME_VAR(int32_t, P36_JoyFlag, 0x00b31e28)
#define P36_JoyX       GAME_VAR(int32_t, P36_JoyX, 0x00b31e1c)          /* ось X (lX), Y — P21_AxisValue (b31e20) */
#define P36_PrevJoyX   GAME_VAR(int32_t, P36_PrevJoyX, 0x00b31df8)      /* ось X прошлого опроса; Y — P9_00b31dfc */
#define P36_PrevFlag   GAME_VAR(int32_t, P36_PrevFlag, 0x00b31e30)
#define P36_PrevAux    GAME_VAR(int32_t, P36_PrevAux, 0x00b31e34)
#define P36_JoyState   GAME_VAR(P36_Bytes80, P36_JoyState, 0x00b31d88)  /* DIJOYSTATE (0x50 байт) */
#define P36_JoyPrev    GAME_VAR(P36_Bytes80, P36_JoyPrev, 0x00b31d00)
#define P36_JoyPresent GAME_VAR(int32_t, P36_JoyPresent, 0x00562a48)
#define P36_KeyCfg     GAME_VAR(P36_Bytes80, P36_KeyCfg, 0x00d04d00)    /* раскладка: [4..5] влево/вправо, [6..0x11] для P19_Keys1 */
#define P36_PadMode    GAME_VAR(uint8_t, P36_PadMode, 0x00c4d70c)       /* 2 — геймпад-режим меню */
#define P36_Pad0       GAME_VAR(uint8_t, P36_Pad0, 0x00d11939)
#define P36_Pad1       GAME_VAR(uint8_t, P36_Pad1, 0x00d11884)
#define P36_Pad2       GAME_VAR(uint8_t, P36_Pad2, 0x01136acc)
#define P36_Pad3       GAME_VAR(uint8_t, P36_Pad3, 0x01137370)
#define P36_Pad4       GAME_VAR(uint8_t, P36_Pad4, 0x01136c50)
#define P36_Pad5       GAME_VAR(uint8_t, P36_Pad5, 0x0113735c)
#ifndef RE_HOOK_BUILD
#pragma push_macro("P36_JoyCount") /*gvi*/
#undef P36_JoyCount /*gvi*/
#pragma push_macro("P36_JoyFlag") /*gvi*/
#undef P36_JoyFlag /*gvi*/
#pragma push_macro("P36_JoyX") /*gvi*/
#undef P36_JoyX /*gvi*/
#pragma push_macro("P36_PrevJoyX") /*gvi*/
#undef P36_PrevJoyX /*gvi*/
#pragma push_macro("P36_PrevFlag") /*gvi*/
#undef P36_PrevFlag /*gvi*/
#pragma push_macro("P36_PrevAux") /*gvi*/
#undef P36_PrevAux /*gvi*/
#pragma push_macro("P36_JoyPresent") /*gvi*/
#undef P36_JoyPresent /*gvi*/
extern int32_t P36_JoyCount, P36_JoyFlag, P36_JoyX, P36_PrevJoyX, P36_PrevFlag, P36_PrevAux, P36_JoyPresent;
#pragma pop_macro("P36_JoyPresent") /*gvi*/
#pragma pop_macro("P36_PrevAux") /*gvi*/
#pragma pop_macro("P36_PrevFlag") /*gvi*/
#pragma pop_macro("P36_PrevJoyX") /*gvi*/
#pragma pop_macro("P36_JoyX") /*gvi*/
#pragma pop_macro("P36_JoyFlag") /*gvi*/
#pragma pop_macro("P36_JoyCount") /*gvi*/
#pragma push_macro("P36_JoyAxisCap") /*gvi*/
#undef P36_JoyAxisCap /*gvi*/
#pragma push_macro("P36_JoyAux") /*gvi*/
#undef P36_JoyAux /*gvi*/
#pragma push_macro("P36_JoyState") /*gvi*/
#undef P36_JoyState /*gvi*/
#pragma push_macro("P36_JoyPrev") /*gvi*/
#undef P36_JoyPrev /*gvi*/
#pragma push_macro("P36_KeyCfg") /*gvi*/
#undef P36_KeyCfg /*gvi*/
extern P36_IntArr P36_JoyAxisCap, P36_JoyAux; extern P36_Bytes80 P36_JoyState, P36_JoyPrev, P36_KeyCfg;
#pragma pop_macro("P36_KeyCfg") /*gvi*/
#pragma pop_macro("P36_JoyPrev") /*gvi*/
#pragma pop_macro("P36_JoyState") /*gvi*/
#pragma pop_macro("P36_JoyAux") /*gvi*/
#pragma pop_macro("P36_JoyAxisCap") /*gvi*/
#pragma push_macro("P36_PadMode") /*gvi*/
#undef P36_PadMode /*gvi*/
#pragma push_macro("P36_Pad0") /*gvi*/
#undef P36_Pad0 /*gvi*/
#pragma push_macro("P36_Pad1") /*gvi*/
#undef P36_Pad1 /*gvi*/
#pragma push_macro("P36_Pad2") /*gvi*/
#undef P36_Pad2 /*gvi*/
#pragma push_macro("P36_Pad3") /*gvi*/
#undef P36_Pad3 /*gvi*/
#pragma push_macro("P36_Pad4") /*gvi*/
#undef P36_Pad4 /*gvi*/
#pragma push_macro("P36_Pad5") /*gvi*/
#undef P36_Pad5 /*gvi*/
extern uint8_t P36_PadMode, P36_Pad0, P36_Pad1, P36_Pad2, P36_Pad3, P36_Pad4, P36_Pad5;
#pragma pop_macro("P36_Pad5") /*gvi*/
#pragma pop_macro("P36_Pad4") /*gvi*/
#pragma pop_macro("P36_Pad3") /*gvi*/
#pragma pop_macro("P36_Pad2") /*gvi*/
#pragma pop_macro("P36_Pad1") /*gvi*/
#pragma pop_macro("P36_Pad0") /*gvi*/
#pragma pop_macro("P36_PadMode") /*gvi*/
#endif
int32_t P36_AcquireDevice(int32_t dev);      /* 004e3ffe: Acquire клавиатуры (0) / мыши (1) / джойстика (2); 1 — успех, иначе 0 */
int32_t P36_SelectJoystick(int32_t idx);     /* 004e3769: выбрать джойстик по номеру; вне 0..JoyCount-1 — сброс; 1 — выбран */
void    P36_GetPadButtons(uint32_t *out);    /* 004e39ac: сбросить флаги геймпада, собрать маску кнопок 8/4/2/1/0x10/0x20/0x40/0x80/0x100 */
int32_t P36_PollInput(void);                 /* 004e3391: опрос клавиатуры/джойстика, перенос осей в P34_Keys; 1 — успех */
/* gvar-img v2.03 begin (tools/gen_gvar_img.py) */
#if !defined(RE_HOOK_BUILD) && !defined(RE_GVAR_PLAIN)
#undef P36_JoyCount
#define P36_JoyCount (*(int32_t *)re_gvar(0x00b31e14u, sizeof(int32_t), (void *)&P36_JoyCount))
#undef P36_JoyAxisCap
#define P36_JoyAxisCap (*(P36_IntArr *)re_gvar(0x00b31d64u, sizeof(P36_IntArr), (void *)&P36_JoyAxisCap))
#undef P36_JoyAux
#define P36_JoyAux (*(P36_IntArr *)re_gvar(0x00b31ca0u, sizeof(P36_IntArr), (void *)&P36_JoyAux))
#undef P36_JoyFlag
#define P36_JoyFlag (*(int32_t *)re_gvar(0x00b31e28u, sizeof(int32_t), (void *)&P36_JoyFlag))
#undef P36_JoyX
#define P36_JoyX (*(int32_t *)re_gvar(0x00b31e1cu, sizeof(int32_t), (void *)&P36_JoyX))
#undef P36_PrevJoyX
#define P36_PrevJoyX (*(int32_t *)re_gvar(0x00b31df8u, sizeof(int32_t), (void *)&P36_PrevJoyX))
#undef P36_PrevFlag
#define P36_PrevFlag (*(int32_t *)re_gvar(0x00b31e30u, sizeof(int32_t), (void *)&P36_PrevFlag))
#undef P36_PrevAux
#define P36_PrevAux (*(int32_t *)re_gvar(0x00b31e34u, sizeof(int32_t), (void *)&P36_PrevAux))
#undef P36_JoyState
#define P36_JoyState (*(P36_Bytes80 *)re_gvar(0x00b31d88u, sizeof(P36_Bytes80), (void *)&P36_JoyState))
#undef P36_JoyPrev
#define P36_JoyPrev (*(P36_Bytes80 *)re_gvar(0x00b31d00u, sizeof(P36_Bytes80), (void *)&P36_JoyPrev))
#undef P36_JoyPresent
#define P36_JoyPresent (*(int32_t *)re_gvar(0x00562a48u, sizeof(int32_t), (void *)&P36_JoyPresent))
#undef P36_KeyCfg
#define P36_KeyCfg (*(P36_Bytes80 *)re_gvar(0x00d04d00u, sizeof(P36_Bytes80), (void *)&P36_KeyCfg))
#undef P36_PadMode
#define P36_PadMode (*(uint8_t *)re_gvar(0x00c4d70cu, sizeof(uint8_t), (void *)&P36_PadMode))
#undef P36_Pad0
#define P36_Pad0 (*(uint8_t *)re_gvar(0x00d11939u, sizeof(uint8_t), (void *)&P36_Pad0))
#undef P36_Pad1
#define P36_Pad1 (*(uint8_t *)re_gvar(0x00d11884u, sizeof(uint8_t), (void *)&P36_Pad1))
#undef P36_Pad2
#define P36_Pad2 (*(uint8_t *)re_gvar(0x01136accu, sizeof(uint8_t), (void *)&P36_Pad2))
#undef P36_Pad3
#define P36_Pad3 (*(uint8_t *)re_gvar(0x01137370u, sizeof(uint8_t), (void *)&P36_Pad3))
#undef P36_Pad4
#define P36_Pad4 (*(uint8_t *)re_gvar(0x01136c50u, sizeof(uint8_t), (void *)&P36_Pad4))
#undef P36_Pad5
#define P36_Pad5 (*(uint8_t *)re_gvar(0x0113735cu, sizeof(uint8_t), (void *)&P36_Pad5))
#endif
/* gvar-img v2.03 end */
