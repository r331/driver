#pragma once
#include "gvar.h"
#include "../platform/plat.h"
#include <stdint.h>
/* DirectInput, шаг C (Input.c): освобождение устройств (004e31d5), повторный захват (DIReAcquire 004e4076), опрос клавиатуры (004e417f). Все — void/int cdecl. */
typedef uint8_t P34_KeyArr[0x100];
typedef void *P34_DevArr[8];
#define P34_Di       GAME_VAR(void *, P34_Di, 0x00b31dd8)      /* IDirectInput */
#define P34_Kbd      GAME_VAR(void *, P34_Kbd, 0x00b31ddc)     /* клавиатура */
#define P34_Mouse    GAME_VAR(void *, P34_Mouse, 0x00b31de0)   /* мышь */
#define P34_Joy      GAME_VAR(void *, P34_Joy, 0x00b31de4)     /* джойстик */
#define P34_FfA      GAME_VAR(void *, P34_FfA, 0x00b31de8)     /* force feedback: счётчик/объект */
#define P34_FfB      GAME_VAR(void *, P34_FfB, 0x00b31dec)
#define P34_Event    GAME_VAR(void *, P34_Event, 0x00b31df0)   /* событие мыши */
#define P34_Reg24    GAME_VAR(int32_t, P34_Reg24, 0x00b31e24)
#define P34_EffA     GAME_VAR(P34_DevArr, P34_EffA, 0x00b31cc0) /* эффекты (Release) */
#define P34_EffB     GAME_VAR(P34_DevArr, P34_EffB, 0x00b31c80)
#define P34_EffC     GAME_VAR(P34_DevArr, P34_EffC, 0x00b31ce0) /* эффекты (Unacquire + Release) */
#define P34_Keys     GAME_VAR(P34_KeyArr, P34_Keys, 0x00d04b00)     /* состояние клавиатуры (GetDeviceState) */
#define P34_KeysPrev GAME_VAR(P34_KeyArr, P34_KeysPrev, 0x00d04c00) /* предыдущее */
#ifndef RE_HOOK_BUILD
extern void *P34_Di, *P34_Kbd, *P34_Mouse, *P34_Joy, *P34_FfA, *P34_FfB, *P34_Event;
#pragma push_macro("P34_Reg24") /*gvi*/
#undef P34_Reg24 /*gvi*/
extern int32_t P34_Reg24; extern P34_DevArr P34_EffA, P34_EffB, P34_EffC;
#pragma pop_macro("P34_Reg24") /*gvi*/
/* v2.03: 00d04b00/00d04c00 — один блок A_00D04B00 (ported7.c): его читают IsFlagSetNotMasked_004E383A (нажатие = [i] && ![0x100+i]),
   AnyKeyHeld_004E3871, KeyState (dirnodes/ported107/110), P21_AxisOut. Прежде P34_Keys/P34_KeysPrev — отдельные объекты, и меню клавиш не видело */
#pragma push_macro("A_00D04B00") /*gvi*/
#undef A_00D04B00 /*gvi*/
extern uint8_t A_00D04B00[];
#pragma pop_macro("A_00D04B00") /*gvi*/
#undef P34_Keys
#undef P34_KeysPrev
#define P34_Keys     (*(P34_KeyArr *)re_gvar(0x00d04b00u, 0x40000u, (void *)&A_00D04B00[0]))       /* то же, что A_00D04B00 (gvar.h) */
#define P34_KeysPrev (*(P34_KeyArr *)((uint8_t *)re_gvar(0x00d04b00u, 0x40000u, (void *)&A_00D04B00[0]) + 0x100))
#endif
void    P34_ReleaseInput(void);       /* 004e31d5: закрыть событие, отпустить клавиатуру/мышь/эффекты/IDirectInput, обнулить */
int32_t P34_ReAcquire(int32_t dev);   /* 004e4076 (DIReAcquire): 0 клавиатура, 1 мышь, 2 джойстик; SetDataFormat + Acquire; 1 — удалось, иначе 0 */
int32_t P34_ReadKeyboard(void);       /* 004e417f: копия состояния в «предыдущее», GetDeviceState(0x100); при ошибке ReAcquire(0); 1 — успех */
/* gvar-img v2.03 begin (tools/gen_gvar_img.py) */
#if !defined(RE_HOOK_BUILD) && !defined(RE_GVAR_PLAIN)
#undef P34_Reg24
#define P34_Reg24 (*(int32_t *)re_gvar(0x00b31e24u, sizeof(int32_t), (void *)&P34_Reg24))
#endif
/* gvar-img v2.03 end */
