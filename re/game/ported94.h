#pragma once
#include "gvar.h"
#include <stdint.h>
/* Шаг D, ported94 (v1.39): пачка листовых функций — разбор имени, целочисленная математика PSX (пружина, кватернион → матрица,
   кривые, конус обзора, таблица направлений), строки маски сектора, ближайший объект радара, «качание» по таблице синусов,
   координаты радара, пределы дальности, шаг затемнения финиша, прямоугольник значка. Все cdecl. */

#define P94_Heading   CARTAB_VAR(int16_t, P94_Heading, 0x00d078aa)   /* курс игрока (поле +0x22 записи 00d07888) */
#define P94_HeadingI  CARTAB_VAR(int32_t, P94_HeadingI, 0x00d078c0)  /* курс игрока, int (поле +0x38 записи 00d07888) */
#define P94_RadarK    GAME_VAR(float, P94_RadarK, 0x00b32978)      /* масштаб радара */
#define P94_MapW      GAME_VAR(int32_t, P94_MapW, 0x00b32a30)      /* ширина/высота карты в 004?? (координаты карты → экран) */
#define P94_MapH      GAME_VAR(int32_t, P94_MapH, 0x00b52a34)
#define P94_MapX0     GAME_VAR(int32_t, P94_MapX0, 0x00b32a04)
#define P94_MapY0     GAME_VAR(int32_t, P94_MapY0, 0x00b32a0c)
#define P94_FadeDir   GAME_VAR(int32_t, P94_FadeDir, 0x00d048f0)
#define P94_FadeVal   GAME_VAR(int32_t, P94_FadeVal, 0x00d044d4)
#define P94_FadePos   GAME_VAR(float, P94_FadePos, 0x00d04478)
#define P94_FadeSpeed GAME_VAR(float, P94_FadeSpeed, 0x00d04784)
#define P94_IconRec   GAME_VAR(uint32_t, P94_IconRec, 0x010faf20)  /* запись значка (16 байт, как у 004ec91e) */
#define P94_QuadPage  GAME_VAR(uint8_t, P94_QuadPage, 0x010fc9a2)
#define P94_Quad      GAME_VAR(p94_quad_t, P94_Quad, 0x010fc9a8)      /* 4 индекса, 8 float uv, 3 × 255.0f */
#define P94_DirCnt    GAME_VAR(int32_t, P94_DirCnt, 0x01145a48)
#define P94_DirTab    GAME_VAR(p94_dirtab_t, P94_DirTab, 0x01142700)  /* {dx, dz, dx + dz·ширина карты, —} */
#define P94_CurveA    GAME_VAR(p94_curveA_t, P94_CurveA, 0x00b2f414)
#define P94_CurveB    GAME_VAR(p94_curveB_t, P94_CurveB, 0x00b2eb8c)
#define P94_CurveC    GAME_VAR(p94_curveB_t, P94_CurveC, 0x00b2ea4c)
#define P94_WobA      GAME_VAR(int32_t, P94_WobA, 0x00553a18)        /* .data, начальное 10 */
#define P94_WobB      GAME_VAR(int32_t, P94_WobB, 0x00b201e0)
#define P94_WobC      GAME_VAR(int32_t, P94_WobC, 0x00553a1c)        /* .data, начальное 5 */
#define P94_WobK      GAME_VAR(float, P94_WobK, 0x00b201e4)
typedef uint32_t p94_quad_t[15];
typedef int32_t p94_dirtab_t[128][4];
typedef int16_t p94_curveA_t[0x1004];
typedef int16_t p94_curveB_t[0xa0];
#ifndef RE_HOOK_BUILD
 extern float P94_RadarK;
extern int32_t P94_MapW, P94_MapH, P94_MapX0, P94_MapY0;
extern int32_t P94_FadeDir, P94_FadeVal; extern float P94_FadePos, P94_FadeSpeed;
extern uint32_t P94_IconRec; extern uint8_t P94_QuadPage; extern p94_quad_t P94_Quad;
extern int32_t P94_DirCnt; extern p94_dirtab_t P94_DirTab;
extern p94_curveA_t P94_CurveA; extern p94_curveB_t P94_CurveB, P94_CurveC;
extern int32_t P94_WobA, P94_WobB, P94_WobC; extern float P94_WobK;
#endif

uint8_t *P94_ReadIdent(uint8_t *src, uint8_t *dst);              /* 004a522a: имя [A-Z0-9_] (строчные → заглавные) в dst; возвращает конец */
void     P94_SpringStep(uint8_t *obj, uint8_t *st);              /* 004e0fd4 */
void     P94_PackState(const uint8_t *src, int32_t *out);        /* 004dab80 */
void     P94_QuatToMat(const int32_t *q, int16_t *m);            /* 004da76a: кватернион (1.12) → матрица 3×3 int16 */
void     P94_InitCurves(void);                                   /* 004da5e0 */
int32_t  P94_InViewCone(const uint8_t *car);                     /* 00496569 */
void     P94_BuildDirTab(void);                                  /* 00490591 */
void     P94_RowSpans(int16_t *out, const uint8_t *grid);        /* 004f2f2a: маска 31×31 → строки (первая строка, число, начало, длина) */
int32_t  P94_NearestObjDist(void);                               /* 004f4c3d */
void     P94_Wobble(float *out, int32_t step);                   /* 004b9835 */
void     P94_RadarXY(float x, float z, float *ox, float *oy);    /* 005061c9 */
void     P94_ClampView(void);                                    /* 004094e3 */
void     P94_FadeStep(void);                                     /* 004e5284 */
void     P94_IconQuad(void);                                     /* 004ab95c */
void     P94_MapToScreen(float *x, float *y);                    /* 00507672 */
