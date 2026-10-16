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
#pragma push_macro("P17_SqrtArg") /*gvi*/
#undef P17_SqrtArg /*gvi*/
#pragma push_macro("P17_PtrA") /*gvi*/
#undef P17_PtrA /*gvi*/
#pragma push_macro("P17_PtrB") /*gvi*/
#undef P17_PtrB /*gvi*/
extern uint32_t P17_SqrtArg, P17_PtrA, P17_PtrB;
#pragma pop_macro("P17_PtrB") /*gvi*/
#pragma pop_macro("P17_PtrA") /*gvi*/
#pragma pop_macro("P17_SqrtArg") /*gvi*/
#pragma push_macro("P17_ValA") /*gvi*/
#undef P17_ValA /*gvi*/
#pragma push_macro("P17_ValB") /*gvi*/
#undef P17_ValB /*gvi*/
#pragma push_macro("P17_Const6") /*gvi*/
#undef P17_Const6 /*gvi*/
#pragma push_macro("P17_Cond1") /*gvi*/
#undef P17_Cond1 /*gvi*/
#pragma push_macro("P17_Cond2") /*gvi*/
#undef P17_Cond2 /*gvi*/
#pragma push_macro("P17_Src") /*gvi*/
#undef P17_Src /*gvi*/
#pragma push_macro("P17_Dst") /*gvi*/
#undef P17_Dst /*gvi*/
extern int32_t P17_ValA, P17_ValB, P17_Const6, P17_Cond1, P17_Cond2, P17_Src, P17_Dst;
#pragma pop_macro("P17_Dst") /*gvi*/
#pragma pop_macro("P17_Src") /*gvi*/
#pragma pop_macro("P17_Cond2") /*gvi*/
#pragma pop_macro("P17_Cond1") /*gvi*/
#pragma pop_macro("P17_Const6") /*gvi*/
#pragma pop_macro("P17_ValB") /*gvi*/
#pragma pop_macro("P17_ValA") /*gvi*/
#endif
uint8_t  P17_SlotMapSide(int32_t id);                   /* 0051bcc0: 0 или 1 */
uint8_t  P17_SlotFindIndex(int16_t slot, int16_t id);   /* 0051bd09: 0..3 или 0xff */
uint32_t P17_ISqrt(uint32_t v);                         /* 00528e12 */
void     P17_PushScreenState(void);                     /* 005104ed */
/* gvar-img v2.03 begin (tools/gen_gvar_img.py) */
#if !defined(RE_HOOK_BUILD) && !defined(RE_GVAR_PLAIN)
#undef P17_SqrtArg
#define P17_SqrtArg (*(uint32_t *)re_gvar(0x0057a136u, sizeof(uint32_t), (void *)&P17_SqrtArg))
#undef P17_PtrA
#define P17_PtrA (*(uint32_t *)re_gvar(0x00b5a730u, sizeof(uint32_t), (void *)&P17_PtrA))
#undef P17_PtrB
#define P17_PtrB (*(uint32_t *)re_gvar(0x00b5a734u, sizeof(uint32_t), (void *)&P17_PtrB))
#undef P17_ValA
#define P17_ValA (*(int32_t *)re_gvar(0x00575550u, sizeof(int32_t), (void *)&P17_ValA))
#undef P17_ValB
#define P17_ValB (*(int32_t *)re_gvar(0x00575554u, sizeof(int32_t), (void *)&P17_ValB))
#undef P17_Const6
#define P17_Const6 (*(int32_t *)re_gvar(0x005f7e54u, sizeof(int32_t), (void *)&P17_Const6))
#undef P17_Cond1
#define P17_Cond1 (*(int32_t *)re_gvar(0x00d11934u, sizeof(int32_t), (void *)&P17_Cond1))
#undef P17_Cond2
#define P17_Cond2 (*(int32_t *)re_gvar(0x00b87e38u, sizeof(int32_t), (void *)&P17_Cond2))
#undef P17_Src
#define P17_Src (*(int32_t *)re_gvar(0x00c80ee8u, sizeof(int32_t), (void *)&P17_Src))
#undef P17_Dst
#define P17_Dst (*(int32_t *)re_gvar(0x0054aa44u, sizeof(int32_t), (void *)&P17_Dst))
#endif
/* gvar-img v2.03 end */
