#pragma once
#include "gvar.h"
#include <stdint.h>
/* Проверки уникальности кнопок, плавное изменение значения, разбор строки, экранные масштабы. */
#ifdef RE_HOOK_BUILD
#define P19_Keys1 ((uint8_t*)0x00d04a70)   /* 12 байт, порядок 0..4,6,7,5,8..11 */
#define P19_Keys2 ((uint8_t*)0x0054b7c4)   /* 14 байт */
#endif
#define P19_Cur        GAME_VAR(float, P19_Cur, 0x005fea58)
#define P19_Target     GAME_VAR(float, P19_Target, 0x005fea5c)
#define P19_Active     GAME_VAR(int32_t, P19_Active, 0x005fea60)
#define P19_Out68      GAME_VAR(float, P19_Out68, 0x01251a68)
#define P19_OutA       GAME_VAR(float, P19_OutA, 0x005507d0)
#define P19_OutB       GAME_VAR(float, P19_OutB, 0x005507d4)
#define P19_OutC       GAME_VAR(float, P19_OutC, 0x005507d8)
#define P19_Step       GAME_VAR(float, P19_Step, 0x00546070)
#define P19_ScrW       GAME_VAR(int32_t, P19_ScrW, 0x01270c28)
#define P19_ScrH       GAME_VAR(int32_t, P19_ScrH, 0x0125f3f0)
#define P19_Scale      GAME_VAR(float, P19_Scale, 0x0125f3e0)
#define P19_DivW       GAME_VAR(float, P19_DivW, 0x00546060)
#define P19_DivH       GAME_VAR(float, P19_DivH, 0x0054605c)
#define P19_DivC       GAME_VAR(float, P19_DivC, 0x00546050)
#define P19_Level      GAME_VAR(int32_t, P19_Level, 0x00575ef0)
#define P19_Sel        GAME_VAR(int32_t, P19_Sel, 0x005fe9e0)
#define P19_PtrA       GAME_VAR(uint32_t, P19_PtrA, 0x0054df9c)
#define P19_Wd         GAME_VAR(uint16_t, P19_Wd, 0x0054df98)
#define P19_Ht         GAME_VAR(uint16_t, P19_Ht, 0x0054df9a)
#define P19_F1         GAME_VAR(int32_t, P19_F1, 0x0054dfe4)
#define P19_F2         GAME_VAR(int32_t, P19_F2, 0x0054dff4)
#define P19_F3         GAME_VAR(int32_t, P19_F3, 0x0054e004)
#define P19_Cond       GAME_VAR(int32_t, P19_Cond, 0x00b87e38)
#ifndef RE_HOOK_BUILD
extern uint8_t P19_Keys1[16], P19_Keys2[16];
#pragma push_macro("P19_Cur") /*gvi*/
#undef P19_Cur /*gvi*/
#pragma push_macro("P19_Target") /*gvi*/
#undef P19_Target /*gvi*/
#pragma push_macro("P19_Out68") /*gvi*/
#undef P19_Out68 /*gvi*/
#pragma push_macro("P19_OutA") /*gvi*/
#undef P19_OutA /*gvi*/
#pragma push_macro("P19_OutB") /*gvi*/
#undef P19_OutB /*gvi*/
#pragma push_macro("P19_OutC") /*gvi*/
#undef P19_OutC /*gvi*/
#pragma push_macro("P19_Step") /*gvi*/
#undef P19_Step /*gvi*/
#pragma push_macro("P19_Scale") /*gvi*/
#undef P19_Scale /*gvi*/
#pragma push_macro("P19_DivW") /*gvi*/
#undef P19_DivW /*gvi*/
#pragma push_macro("P19_DivH") /*gvi*/
#undef P19_DivH /*gvi*/
#pragma push_macro("P19_DivC") /*gvi*/
#undef P19_DivC /*gvi*/
extern float P19_Cur, P19_Target, P19_Out68, P19_OutA, P19_OutB, P19_OutC, P19_Step, P19_Scale, P19_DivW, P19_DivH, P19_DivC;
#pragma pop_macro("P19_DivC") /*gvi*/
#pragma pop_macro("P19_DivH") /*gvi*/
#pragma pop_macro("P19_DivW") /*gvi*/
#pragma pop_macro("P19_Scale") /*gvi*/
#pragma pop_macro("P19_Step") /*gvi*/
#pragma pop_macro("P19_OutC") /*gvi*/
#pragma pop_macro("P19_OutB") /*gvi*/
#pragma pop_macro("P19_OutA") /*gvi*/
#pragma pop_macro("P19_Out68") /*gvi*/
#pragma pop_macro("P19_Target") /*gvi*/
#pragma pop_macro("P19_Cur") /*gvi*/
#pragma push_macro("P19_Active") /*gvi*/
#undef P19_Active /*gvi*/
#pragma push_macro("P19_ScrW") /*gvi*/
#undef P19_ScrW /*gvi*/
#pragma push_macro("P19_ScrH") /*gvi*/
#undef P19_ScrH /*gvi*/
#pragma push_macro("P19_Level") /*gvi*/
#undef P19_Level /*gvi*/
#pragma push_macro("P19_Sel") /*gvi*/
#undef P19_Sel /*gvi*/
#pragma push_macro("P19_F1") /*gvi*/
#undef P19_F1 /*gvi*/
#pragma push_macro("P19_F2") /*gvi*/
#undef P19_F2 /*gvi*/
#pragma push_macro("P19_F3") /*gvi*/
#undef P19_F3 /*gvi*/
#pragma push_macro("P19_Cond") /*gvi*/
#undef P19_Cond /*gvi*/
extern int32_t P19_Active, P19_ScrW, P19_ScrH, P19_Level, P19_Sel, P19_F1, P19_F2, P19_F3, P19_Cond;
#pragma pop_macro("P19_Cond") /*gvi*/
#pragma pop_macro("P19_F3") /*gvi*/
#pragma pop_macro("P19_F2") /*gvi*/
#pragma pop_macro("P19_F1") /*gvi*/
#pragma pop_macro("P19_Sel") /*gvi*/
#pragma pop_macro("P19_Level") /*gvi*/
#pragma pop_macro("P19_ScrH") /*gvi*/
#pragma pop_macro("P19_ScrW") /*gvi*/
#pragma pop_macro("P19_Active") /*gvi*/
#pragma push_macro("P19_PtrA") /*gvi*/
#undef P19_PtrA /*gvi*/
extern uint32_t P19_PtrA;
#pragma pop_macro("P19_PtrA") /*gvi*/
#pragma push_macro("P19_Wd") /*gvi*/
#undef P19_Wd /*gvi*/
#pragma push_macro("P19_Ht") /*gvi*/
#undef P19_Ht /*gvi*/
extern uint16_t P19_Wd, P19_Ht;
#pragma pop_macro("P19_Ht") /*gvi*/
#pragma pop_macro("P19_Wd") /*gvi*/
#endif
int32_t P19_KeysUnique12(void);       /* 004107b9: 1 если все (кроме '"') различны */
int32_t P19_KeysUnique14(void);       /* 00411b09 */
void    P19_FadeStep(void);           /* 004184f5 */
int     P19_TakeToken(char* s, char* out); /* 0041c7da: 1 если токен пуст */
void    P19_Sel2(int32_t a);          /* 00416084 */
void    P19_Sel3(int32_t a);          /* 004160e9 */
void    P19_Sel4(int32_t a);          /* 0041614e */
float   P19_ScaleX(float v);          /* 005174c6 */
float   P19_ScaleY(float v);          /* 00517512 */
/* gvar-img v2.03 begin (tools/gen_gvar_img.py) */
#if !defined(RE_HOOK_BUILD) && !defined(RE_GVAR_PLAIN)
#undef P19_Cur
#define P19_Cur (*(float *)re_gvar(0x005fea58u, sizeof(float), (void *)&P19_Cur))
#undef P19_Target
#define P19_Target (*(float *)re_gvar(0x005fea5cu, sizeof(float), (void *)&P19_Target))
#undef P19_Active
#define P19_Active (*(int32_t *)re_gvar(0x005fea60u, sizeof(int32_t), (void *)&P19_Active))
#undef P19_Out68
#define P19_Out68 (*(float *)re_gvar(0x01251a68u, sizeof(float), (void *)&P19_Out68))
#undef P19_OutA
#define P19_OutA (*(float *)re_gvar(0x005507d0u, sizeof(float), (void *)&P19_OutA))
#undef P19_OutB
#define P19_OutB (*(float *)re_gvar(0x005507d4u, sizeof(float), (void *)&P19_OutB))
#undef P19_OutC
#define P19_OutC (*(float *)re_gvar(0x005507d8u, sizeof(float), (void *)&P19_OutC))
#undef P19_Step
#define P19_Step (*(float *)re_gvar(0x00546070u, sizeof(float), (void *)&P19_Step))
#undef P19_ScrW
#define P19_ScrW (*(int32_t *)re_gvar(0x01270c28u, sizeof(int32_t), (void *)&P19_ScrW))
#undef P19_ScrH
#define P19_ScrH (*(int32_t *)re_gvar(0x0125f3f0u, sizeof(int32_t), (void *)&P19_ScrH))
#undef P19_Scale
#define P19_Scale (*(float *)re_gvar(0x0125f3e0u, sizeof(float), (void *)&P19_Scale))
#undef P19_DivW
#define P19_DivW (*(float *)re_gvar(0x00546060u, sizeof(float), (void *)&P19_DivW))
#undef P19_DivH
#define P19_DivH (*(float *)re_gvar(0x0054605cu, sizeof(float), (void *)&P19_DivH))
#undef P19_DivC
#define P19_DivC (*(float *)re_gvar(0x00546050u, sizeof(float), (void *)&P19_DivC))
#undef P19_Level
#define P19_Level (*(int32_t *)re_gvar(0x00575ef0u, sizeof(int32_t), (void *)&P19_Level))
#undef P19_Sel
#define P19_Sel (*(int32_t *)re_gvar(0x005fe9e0u, sizeof(int32_t), (void *)&P19_Sel))
#undef P19_PtrA
#define P19_PtrA (*(uint32_t *)re_gvar(0x0054df9cu, sizeof(uint32_t), (void *)&P19_PtrA))
#undef P19_Wd
#define P19_Wd (*(uint16_t *)re_gvar(0x0054df98u, sizeof(uint16_t), (void *)&P19_Wd))
#undef P19_Ht
#define P19_Ht (*(uint16_t *)re_gvar(0x0054df9au, sizeof(uint16_t), (void *)&P19_Ht))
#undef P19_F1
#define P19_F1 (*(int32_t *)re_gvar(0x0054dfe4u, sizeof(int32_t), (void *)&P19_F1))
#undef P19_F2
#define P19_F2 (*(int32_t *)re_gvar(0x0054dff4u, sizeof(int32_t), (void *)&P19_F2))
#undef P19_F3
#define P19_F3 (*(int32_t *)re_gvar(0x0054e004u, sizeof(int32_t), (void *)&P19_F3))
#undef P19_Cond
#define P19_Cond (*(int32_t *)re_gvar(0x00b87e38u, sizeof(int32_t), (void *)&P19_Cond))
#endif
/* gvar-img v2.03 end */
