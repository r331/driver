#pragma once
#include "gvar.h"
#include "unported.h"
#include "ported6.h"
#include "ported8.h"
#include "ported19.h"
#include "ported12.h"
#include <stdint.h>
/* Векторная/матричная математика движка (cdecl, float), конец цикла CD-фейда, списки свободных слотов.
   Матрицы 3x3 — float[9] по строкам; кватернион — float[5] (x,y,z,—,w). Таблица синусов — 4096 + 1024 float: cos(i) = sin[i + 0x400]. */
typedef float p43_sintab_t[5120];
#define P43_Sin       GAME_VAR(p43_sintab_t, P43_Sin, 0x00b94280)
#define P43_Eps       GAME_VAR(float, P43_Eps, 0x00546aa4)          /* порог длины */
#define P43_Four       GAME_VAR(float, P43_Four, 0x005461ac)          /* 4.0 */
#define P43_FadeLen   GAME_VAR(float, P43_FadeLen, 0x00576480)
#define P43_FadeDiv   GAME_VAR(float, P43_FadeDiv, 0x0054612c)
#define P43_FadeOn    GAME_VAR(int32_t, P43_FadeOn, 0x00b91cf8)
#define P43_FadeSteps GAME_VAR(int32_t, P43_FadeSteps, 0x00b91d1c)
#define P43_FadeA     GAME_VAR(float, P43_FadeA, 0x00b91d20)
#define P43_FadeB     GAME_VAR(int32_t, P43_FadeB, 0x00b91d24)
#define P43_FadeStep  GAME_VAR(float, P43_FadeStep, 0x00b91d28)
#define P43_ScaleA    GAME_VAR(float, P43_ScaleA, 0x01251a64)
#define P43_OffX      GAME_VAR(float, P43_OffX, 0x01252b7c)
#define P43_OffY      GAME_VAR(float, P43_OffY, 0x01252b6c)
#define P43_Half      GAME_VAR(float, P43_Half, 0x0054607c)
#define P43_FreeCnt   GAME_VAR(int32_t, P43_FreeCnt, 0x00c56764)
typedef int32_t p43_freelist_t[512];
#define P43_FreeList  GAME_VAR(p43_freelist_t, P43_FreeList, 0x00c594a0)
typedef int32_t p43_anim_t[16];
#define P43_AnimTab   GAME_VAR(p43_anim_t, P43_AnimTab, 0x00c8198c)
#ifndef RE_HOOK_BUILD
extern p43_sintab_t P43_Sin; extern float P43_Eps, P43_Four, P43_FadeLen, P43_FadeDiv, P43_FadeA, P43_FadeStep, P43_ScaleA, P43_OffX, P43_OffY, P43_Half;
extern int32_t P43_FadeOn, P43_FadeSteps, P43_FadeB, P43_FreeCnt; extern p43_freelist_t P43_FreeList; extern p43_anim_t P43_AnimTab;
#endif
void   P43_CdFadeInit(void);                              /* 00524398: старт фейда CD, если CD включён и фейд ещё не идёт */
void   P43_NormalizeToOut(float x, float y, float z);     /* 00526521: нормализованный вектор -> глобал 005507d0.. */
void   P43_Normalize(float *v);                           /* 005260d7: v /= |v| (без проверки нуля) */
float *P43_Cross(float *out, const float *a, const float *b); /* 0052605d: out = a x b (out[3] не трогаем — в оригинале мусор стека) */
float  P43_Len3(const float *v);                          /* 005271f2: |v|, 0 при |v|^2 <= eps */
float  P43_Len4(const float *v);                          /* 00527255: sqrt(x²+y²+z²+v[4]²) */
void   P43_Orthonormalize(float *m);                      /* 005265e3: ортонормировать матрицу (столбцы 2, 0, 1) */
int32_t P43_PointInPoly(int32_t n, const float *pts, float x, float y); /* 0052680b: точка внутри выпуклого многоугольника, вершины шаг 4 float */
void   P43_EulerMatrix(float *m, const int16_t *ang);     /* 005261ad: матрица поворота из трёх углов (0..4095) */
int32_t P43_ClipT(int32_t d, int32_t n, float *t0, float *t1); /* 00526ed7: отсечение параметра отрезка (Лян–Барски) */
void   P43_NormalizeCopy(const float *v, float *out);     /* 00527010: out = v/|v| или 0 */
void   P43_MatToQuat(const float *m, float *q);           /* 005273a3 */
void   P43_QuatToMat(const float *q, float *m);           /* 00527429 */
void   P43_ProjectGrid(uint8_t *p);                       /* 0052647d: проекция по сетке с поправками */
void   P43_FreeSlot(uint8_t *p);                          /* 0051200f: освободить слот (бит 0x10) в список свободных */
void   P43_AnimNext(uint8_t *p);                          /* 00514073 */
void re_init_consts(void); /* ported43.c: .data-константы для native */
