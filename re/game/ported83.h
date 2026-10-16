#pragma once
#include "gvar.h"
#include "ported8.h"
#include "ported19.h"
#include "ported44.h"
#include "ported47.h"
#include "ported56.h"
#include "ported60.h"
#include "ported77.h"
#include "ported80.h"
#include "ported82.h"
#include "ported84.h"
#include <stdint.h>
/* Шаг D, ported83 (веха 1, рендер мира), обе cdecl:
   00428672  P83_BoxVis(p, r) — как P82_SphereVis3D, но порядок плоскостей иной (левая, правая, дальняя, ближняя при res==0, верхняя, нижняя),
             скалярное произведение считается x,y,z, результат каждой плоскости — float; 0 вне, 1 внутри, 2 касается ближней плоскости;
   00428928  P83_LightMatrices — 4 направления света (005507d0..dc) копируются в 01249680/90/a0/b0, затем для k=0..3:
             Mat3Mul(ViewMat, EulerTab+k*0x10000 → матрица 01209680+k*0x10000), флаг 011f0060+k*0x1000 = SwapCnt,
             MatPtr = EulerTab+k*0x10000, Xform(вектор k). */
typedef float p83_m9_t[9];
typedef float p83_v16_t[16];
#define P83_LightVec  GAME_VAR(p83_v16_t, P83_LightVec, 0x01249680)    /* 4 вектора по 4 float подряд */
#ifdef RE_HOOK_BUILD
#define P83_Mat0      GAME_VAR(p83_m9_t, P83_Mat0, 0x01209680)
#define P83_Mat1      GAME_VAR(p83_m9_t, P83_Mat1, 0x01219680)
#define P83_Mat2      GAME_VAR(p83_m9_t, P83_Mat2, 0x01229680)
#define P83_Mat3      GAME_VAR(p83_m9_t, P83_Mat3, 0x01239680)
#define P83_Flag0     GAME_VAR(int32_t, P83_Flag0, 0x011f0060)
#define P83_Flag1     GAME_VAR(int32_t, P83_Flag1, 0x011f1060)
#define P83_Flag2     GAME_VAR(int32_t, P83_Flag2, 0x011f2060)
#define P83_Flag3     GAME_VAR(int32_t, P83_Flag3, 0x011f3060)
#else
/* в native матрицы и флаги света — записи 0/1024/2048/3072 кэша матриц ported84 */
#define P83_Mat0      (P84_MatCache[0])
#define P83_Mat1      (P84_MatCache[1024])
#define P83_Mat2      (P84_MatCache[2048])
#define P83_Mat3      (P84_MatCache[3072])
#define P83_Flag0     (P84_MatFlag[0])
#define P83_Flag1     (P84_MatFlag[1024])
#define P83_Flag2     (P84_MatFlag[2048])
#define P83_Flag3     (P84_MatFlag[3072])
#endif
#ifndef RE_HOOK_BUILD
#pragma push_macro("P83_LightVec") /*gvi*/
#undef P83_LightVec /*gvi*/
extern p83_v16_t P83_LightVec;
#pragma pop_macro("P83_LightVec") /*gvi*/
#endif
int32_t P83_BoxVis(const float *p, float r);       /* 00428672 */
void    P83_LightMatrices(void);                   /* 00428928 */
/* gvar-img v2.03 begin (tools/gen_gvar_img.py) */
#if !defined(RE_HOOK_BUILD) && !defined(RE_GVAR_PLAIN)
#undef P83_LightVec
#define P83_LightVec (*(p83_v16_t *)re_gvar(0x01249680u, sizeof(p83_v16_t), (void *)&P83_LightVec))
#endif
/* gvar-img v2.03 end */
