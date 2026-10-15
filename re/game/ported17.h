#pragma once
#include "gvar.h"
#include "nodetab.h"
#include <stdint.h>
/* Мелкие функции: слот-таблица 0x2c байта, целочисленный корень, переключение экрана. */
typedef uint8_t p17_slots_t[0x2c * 128];
typedef uint8_t p17_map_t[0x42 * 64 + 8];
#define P17_SlotBase    SLOTTAB_VAR(p17_slots_t, P17_SlotBase, 0x00c1ed8a)   /* v1.46: над P11_00c1ed80 */
#define P17_MapBase     NODETAB_VAR(p17_map_t, P17_MapBase, 0x00bf1c42)      /* v1.46: над P11_00bf1c40 */
#define P17_SqrtArg     GAME_VAR(uint32_t, P17_SqrtArg, 0x0057a136)
#define P17_PtrA        GAME_VAR(uint32_t, P17_PtrA, 0x00b5a730)
#define P17_PtrB        GAME_VAR(uint32_t, P17_PtrB, 0x00b5a734)
#define P17_ValA        GAME_VAR(int32_t, P17_ValA, 0x00575550)
#define P17_ValB        GAME_VAR(int32_t, P17_ValB, 0x00575554)
#define P17_Const6      GAME_VAR(int32_t, P17_Const6, 0x005f7e54)
#define P17_Cond1       GAME_VAR(int32_t, P17_Cond1, 0x00d11934)
#define P17_Cond2       GAME_VAR(int32_t, P17_Cond2, 0x00b87e38)
#define P17_Src         GAME_VAR(int32_t, P17_Src, 0x00c80ee8)
#define P17_Dst         GAME_VAR(int32_t, P17_Dst, 0x0054aa44)
#ifndef RE_HOOK_BUILD
extern uint32_t P17_SqrtArg, P17_PtrA, P17_PtrB;
extern int32_t P17_ValA, P17_ValB, P17_Const6, P17_Cond1, P17_Cond2, P17_Src, P17_Dst;
#endif
uint8_t  P17_SlotMapSide(int32_t id);                   /* 0051bcc0: 0 или 1 */
uint8_t  P17_SlotFindIndex(int16_t slot, int16_t id);   /* 0051bd09: 0..3 или 0xff */
uint32_t P17_ISqrt(uint32_t v);                         /* 00528e12 */
void     P17_PushScreenState(void);                     /* 005104ed */
