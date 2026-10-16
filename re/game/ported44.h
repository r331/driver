#pragma once
#include "gvar.h"
#include "unported.h"
#include "ported8.h"
#include "ported19.h"
#include "ported43.h"
#include <stdint.h>
/* Математика движка, часть 2 (все cdecl): арктангенс по таблице, матрицы поворота, кватернионы, преобразование векторов.
   Матрицы 3x3 — float[9] по строкам; кватернион — float[5] (x,y,z,—,w); углы — 4096 на оборот (индекс в таблицу синусов). */
typedef int16_t p44_atan_t[1025];
#define P44_AtanTab   GAME_VAR(p44_atan_t, P44_AtanTab, 0x0057670c)   /* atan(i/1024) в 4096-х долях оборота */
#define P44_MatPtr    GAME_VAR(float*, P44_MatPtr, 0x00bdc28c)         /* текущая матрица для P44_Xform* */
#define P44_BiasX     GAME_VAR(float, P44_BiasX, 0x00ba5280)
#define P44_BiasY     GAME_VAR(float, P44_BiasY, 0x00ba52d4)
#define P44_BiasZ     GAME_VAR(float, P44_BiasZ, 0x00ba5380)
#define P44_XformTag  GAME_VAR(uint32_t, P44_XformTag, 0x01270c20)
#define P44_CamX      GAME_VAR(float, P44_CamX, 0x00b1c270)
#define P44_CamY      GAME_VAR(float, P44_CamY, 0x00b1c274)
#define P44_CamZ      GAME_VAR(float, P44_CamZ, 0x00b1c278)
typedef float p44_m9_t[9];
#define P44_ViewMat   GAME_VAR(p44_m9_t, P44_ViewMat, 0x011f4080)      /* right, up, forward: 3 вектора */
#define P44_ViewMatT  GAME_VAR(p44_m9_t, P44_ViewMatT, 0x011effa0)     /* транспонированная копия */
#define P44_Rst_B93CEC GAME_VAR(int32_t, P44_Rst_B93CEC, 0x00b93cec)
#define P44_Rst_B93DFC GAME_VAR(int32_t, P44_Rst_B93DFC, 0x00b93dfc)
#define P44_Rst_B93E00 GAME_VAR(int32_t, P44_Rst_B93E00, 0x00b93e00)
#define P44_Rst_B93CD0 GAME_VAR(int32_t, P44_Rst_B93CD0, 0x00b93cd0)
#define P44_Rst_B93CD8 GAME_VAR(int32_t, P44_Rst_B93CD8, 0x00b93cd8)
#define P44_Rst_B93CE8 GAME_VAR(int32_t, P44_Rst_B93CE8, 0x00b93ce8)
#define P44_Rst_B93CE4 GAME_VAR(int32_t, P44_Rst_B93CE4, 0x00b93ce4)
#define P44_Rst_B93CCC GAME_VAR(int32_t, P44_Rst_B93CCC, 0x00b93ccc)
#define P44_Rst_B93DF4 GAME_VAR(int32_t, P44_Rst_B93DF4, 0x00b93df4)
#define P44_Rst_B93CF0 GAME_VAR(int32_t, P44_Rst_B93CF0, 0x00b93cf0)
#define P44_Rst_B93CD4 GAME_VAR(int32_t, P44_Rst_B93CD4, 0x00b93cd4)
#define P44_Rst_B93CDC GAME_VAR(int32_t, P44_Rst_B93CDC, 0x00b93cdc)
#define P44_Rst_B31EA0 GAME_VAR(int32_t, P44_Rst_B31EA0, 0x00b31ea0)
#define P44_Rst_B93DF8 GAME_VAR(int32_t, P44_Rst_B93DF8, 0x00b93df8)
#define P44_Rst_B93CE0 GAME_VAR(int32_t, P44_Rst_B93CE0, 0x00b93ce0)
typedef int32_t p44_rst_t[27];
#define P44_Rst_Tab   GAME_VAR(p44_rst_t, P44_Rst_Tab, 0x0057668c)     /* 9 записей по 12 байт; обнуляется первое слово */
#ifndef RE_HOOK_BUILD
#pragma push_macro("P44_AtanTab") /*gvi*/
#undef P44_AtanTab /*gvi*/
extern p44_atan_t P44_AtanTab; extern float *P44_MatPtr;
#pragma pop_macro("P44_AtanTab") /*gvi*/
#pragma push_macro("P44_BiasX") /*gvi*/
#undef P44_BiasX /*gvi*/
#pragma push_macro("P44_BiasY") /*gvi*/
#undef P44_BiasY /*gvi*/
#pragma push_macro("P44_BiasZ") /*gvi*/
#undef P44_BiasZ /*gvi*/
#pragma push_macro("P44_CamX") /*gvi*/
#undef P44_CamX /*gvi*/
#pragma push_macro("P44_CamY") /*gvi*/
#undef P44_CamY /*gvi*/
#pragma push_macro("P44_CamZ") /*gvi*/
#undef P44_CamZ /*gvi*/
#pragma push_macro("P44_XformTag") /*gvi*/
#undef P44_XformTag /*gvi*/
extern float P44_BiasX, P44_BiasY, P44_BiasZ, P44_CamX, P44_CamY, P44_CamZ; extern uint32_t P44_XformTag;
#pragma pop_macro("P44_XformTag") /*gvi*/
#pragma pop_macro("P44_CamZ") /*gvi*/
#pragma pop_macro("P44_CamY") /*gvi*/
#pragma pop_macro("P44_CamX") /*gvi*/
#pragma pop_macro("P44_BiasZ") /*gvi*/
#pragma pop_macro("P44_BiasY") /*gvi*/
#pragma pop_macro("P44_BiasX") /*gvi*/
#pragma push_macro("P44_ViewMat") /*gvi*/
#undef P44_ViewMat /*gvi*/
#pragma push_macro("P44_ViewMatT") /*gvi*/
#undef P44_ViewMatT /*gvi*/
#pragma push_macro("P44_Rst_Tab") /*gvi*/
#undef P44_Rst_Tab /*gvi*/
extern p44_m9_t P44_ViewMat, P44_ViewMatT; extern p44_rst_t P44_Rst_Tab;
#pragma pop_macro("P44_Rst_Tab") /*gvi*/
#pragma pop_macro("P44_ViewMatT") /*gvi*/
#pragma pop_macro("P44_ViewMat") /*gvi*/
#pragma push_macro("P44_Rst_B93CEC") /*gvi*/
#undef P44_Rst_B93CEC /*gvi*/
#pragma push_macro("P44_Rst_B93DFC") /*gvi*/
#undef P44_Rst_B93DFC /*gvi*/
#pragma push_macro("P44_Rst_B93E00") /*gvi*/
#undef P44_Rst_B93E00 /*gvi*/
#pragma push_macro("P44_Rst_B93CD0") /*gvi*/
#undef P44_Rst_B93CD0 /*gvi*/
#pragma push_macro("P44_Rst_B93CD8") /*gvi*/
#undef P44_Rst_B93CD8 /*gvi*/
#pragma push_macro("P44_Rst_B93CE8") /*gvi*/
#undef P44_Rst_B93CE8 /*gvi*/
#pragma push_macro("P44_Rst_B93CE4") /*gvi*/
#undef P44_Rst_B93CE4 /*gvi*/
#pragma push_macro("P44_Rst_B93CCC") /*gvi*/
#undef P44_Rst_B93CCC /*gvi*/
extern int32_t P44_Rst_B93CEC, P44_Rst_B93DFC, P44_Rst_B93E00, P44_Rst_B93CD0, P44_Rst_B93CD8, P44_Rst_B93CE8, P44_Rst_B93CE4, P44_Rst_B93CCC,
#pragma pop_macro("P44_Rst_B93CCC") /*gvi*/
#pragma pop_macro("P44_Rst_B93CE4") /*gvi*/
#pragma pop_macro("P44_Rst_B93CE8") /*gvi*/
#pragma pop_macro("P44_Rst_B93CD8") /*gvi*/
#pragma pop_macro("P44_Rst_B93CD0") /*gvi*/
#pragma pop_macro("P44_Rst_B93E00") /*gvi*/
#pragma pop_macro("P44_Rst_B93DFC") /*gvi*/
#pragma pop_macro("P44_Rst_B93CEC") /*gvi*/
  P44_Rst_B93DF4, P44_Rst_B93CF0, P44_Rst_B93CD4, P44_Rst_B93CDC, P44_Rst_B31EA0, P44_Rst_B93DF8, P44_Rst_B93CE0;
#endif
void    P44_InitTables(void);                                /* native: заполняет таблицу арктангенса (в игре она в .data) */
void    P44_ResetState(void);                                /* 00525900: сброс 15 глобалов и 9 слов таблицы 0057668c */
int32_t P44_Atan2(int32_t x, int32_t y);                     /* 00525e7e: угол 0..0xfff (4096/оборот) по таблице; 0 при x=y=0 */
void    P44_EulerMatXYZ(float *m, const int16_t *ang);       /* 005262cc: единичная матрица * RotX(a0) * RotY(a1) * RotZ(a2) */
void    P44_EulerMatYXZ(float *m, const int16_t *ang);       /* 00526365: порядок Y, X, Z */
int32_t P44_PointInQuad(int32_t x, int32_t y, const int32_t *q); /* 00526940: точка внутри выпуклого 4-угольника (int x,y *4) */
void    P44_QuatNormalize(float *q);                         /* 005272f2: q/|q|; нулевой -> единичный */
void    P44_QuatMul(const float *a, const float *b, float *o);/* 00527544: o = a*b (5 слов, o[3] = мусор стека) */
void    P44_EulerToQuat(const int16_t *ang, float *q);       /* 0052763b */
void    P44_AxisAngleMat(int32_t ang, const float *axis, float *m); /* 00527746: поворот вокруг оси на ang (индекс sin) */
void    P44_Copy4(void *dst, const void *src, uint32_t n);   /* 005283b5: копия n байт (dword-ами, затем хвост) */
void    P44_Transpose(const float *src, float *dst);         /* 00528461: транспонирование 3x3 */
void    P44_RotX(float *m, int32_t ang);                     /* 00528688: поворот столбцов 1,2 */
void    P44_RotY(float *m, int32_t ang);                     /* 00528788: столбцы 0,2 */
void    P44_RotZ(float *m, int32_t ang);                     /* 00528885: столбцы 0,1 */
void    P44_Xform(float *v);                                 /* 00528982: v = M^T... v' = v*M (M = *P44_MatPtr) */
void    P44_XformT(float *v);                                /* 005289e2: то же с транспонированной M */
void    P44_XformBias(float *v);                             /* 00528a42: v[3..5] = v[3..5]*M + BiasXYZ; v[0] = XformTag */
void    P44_LookAt(const float *eye, const float *up);       /* 005266ed: матрица вида в 011f4080, транспонат в 011effa0 */
/* gvar-img v2.03 begin (tools/gen_gvar_img.py) */
#if !defined(RE_HOOK_BUILD) && !defined(RE_GVAR_PLAIN)
#undef P44_AtanTab
#define P44_AtanTab (*(p44_atan_t *)re_gvar(0x0057670cu, sizeof(p44_atan_t), (void *)&P44_AtanTab))
#undef P44_BiasX
#define P44_BiasX (*(float *)re_gvar(0x00ba5280u, sizeof(float), (void *)&P44_BiasX))
#undef P44_BiasY
#define P44_BiasY (*(float *)re_gvar(0x00ba52d4u, sizeof(float), (void *)&P44_BiasY))
#undef P44_BiasZ
#define P44_BiasZ (*(float *)re_gvar(0x00ba5380u, sizeof(float), (void *)&P44_BiasZ))
#undef P44_XformTag
#define P44_XformTag (*(uint32_t *)re_gvar(0x01270c20u, sizeof(uint32_t), (void *)&P44_XformTag))
#undef P44_CamX
#define P44_CamX (*(float *)re_gvar(0x00b1c270u, sizeof(float), (void *)&P44_CamX))
#undef P44_CamY
#define P44_CamY (*(float *)re_gvar(0x00b1c274u, sizeof(float), (void *)&P44_CamY))
#undef P44_CamZ
#define P44_CamZ (*(float *)re_gvar(0x00b1c278u, sizeof(float), (void *)&P44_CamZ))
#undef P44_ViewMat
#define P44_ViewMat (*(p44_m9_t *)re_gvar(0x011f4080u, sizeof(p44_m9_t), (void *)&P44_ViewMat))
#undef P44_ViewMatT
#define P44_ViewMatT (*(p44_m9_t *)re_gvar(0x011effa0u, sizeof(p44_m9_t), (void *)&P44_ViewMatT))
#undef P44_Rst_B93CEC
#define P44_Rst_B93CEC (*(int32_t *)re_gvar(0x00b93cecu, sizeof(int32_t), (void *)&P44_Rst_B93CEC))
#undef P44_Rst_B93DFC
#define P44_Rst_B93DFC (*(int32_t *)re_gvar(0x00b93dfcu, sizeof(int32_t), (void *)&P44_Rst_B93DFC))
#undef P44_Rst_B93E00
#define P44_Rst_B93E00 (*(int32_t *)re_gvar(0x00b93e00u, sizeof(int32_t), (void *)&P44_Rst_B93E00))
#undef P44_Rst_B93CD0
#define P44_Rst_B93CD0 (*(int32_t *)re_gvar(0x00b93cd0u, sizeof(int32_t), (void *)&P44_Rst_B93CD0))
#undef P44_Rst_B93CD8
#define P44_Rst_B93CD8 (*(int32_t *)re_gvar(0x00b93cd8u, sizeof(int32_t), (void *)&P44_Rst_B93CD8))
#undef P44_Rst_B93CE8
#define P44_Rst_B93CE8 (*(int32_t *)re_gvar(0x00b93ce8u, sizeof(int32_t), (void *)&P44_Rst_B93CE8))
#undef P44_Rst_B93CE4
#define P44_Rst_B93CE4 (*(int32_t *)re_gvar(0x00b93ce4u, sizeof(int32_t), (void *)&P44_Rst_B93CE4))
#undef P44_Rst_B93CCC
#define P44_Rst_B93CCC (*(int32_t *)re_gvar(0x00b93cccu, sizeof(int32_t), (void *)&P44_Rst_B93CCC))
#undef P44_Rst_B93DF4
#define P44_Rst_B93DF4 (*(int32_t *)re_gvar(0x00b93df4u, sizeof(int32_t), (void *)&P44_Rst_B93DF4))
#undef P44_Rst_B93CF0
#define P44_Rst_B93CF0 (*(int32_t *)re_gvar(0x00b93cf0u, sizeof(int32_t), (void *)&P44_Rst_B93CF0))
#undef P44_Rst_B93CD4
#define P44_Rst_B93CD4 (*(int32_t *)re_gvar(0x00b93cd4u, sizeof(int32_t), (void *)&P44_Rst_B93CD4))
#undef P44_Rst_B93CDC
#define P44_Rst_B93CDC (*(int32_t *)re_gvar(0x00b93cdcu, sizeof(int32_t), (void *)&P44_Rst_B93CDC))
#undef P44_Rst_B31EA0
#define P44_Rst_B31EA0 (*(int32_t *)re_gvar(0x00b31ea0u, sizeof(int32_t), (void *)&P44_Rst_B31EA0))
#undef P44_Rst_B93DF8
#define P44_Rst_B93DF8 (*(int32_t *)re_gvar(0x00b93df8u, sizeof(int32_t), (void *)&P44_Rst_B93DF8))
#undef P44_Rst_B93CE0
#define P44_Rst_B93CE0 (*(int32_t *)re_gvar(0x00b93ce0u, sizeof(int32_t), (void *)&P44_Rst_B93CE0))
#undef P44_Rst_Tab
#define P44_Rst_Tab (*(p44_rst_t *)re_gvar(0x0057668cu, sizeof(p44_rst_t), (void *)&P44_Rst_Tab))
#endif
/* gvar-img v2.03 end */
