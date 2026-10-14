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
extern float P19_Cur, P19_Target, P19_Out68, P19_OutA, P19_OutB, P19_OutC, P19_Step, P19_Scale, P19_DivW, P19_DivH, P19_DivC;
extern int32_t P19_Active, P19_ScrW, P19_ScrH, P19_Level, P19_Sel, P19_F1, P19_F2, P19_F3, P19_Cond;
extern uint32_t P19_PtrA;
extern uint16_t P19_Wd, P19_Ht;
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
