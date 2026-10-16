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
#pragma push_macro("P94_MapW") /*gvi*/
#undef P94_MapW /*gvi*/
#pragma push_macro("P94_MapH") /*gvi*/
#undef P94_MapH /*gvi*/
#pragma push_macro("P94_MapX0") /*gvi*/
#undef P94_MapX0 /*gvi*/
#pragma push_macro("P94_MapY0") /*gvi*/
#undef P94_MapY0 /*gvi*/
extern int32_t P94_MapW, P94_MapH, P94_MapX0, P94_MapY0;
#pragma pop_macro("P94_MapY0") /*gvi*/
#pragma pop_macro("P94_MapX0") /*gvi*/
#pragma pop_macro("P94_MapH") /*gvi*/
#pragma pop_macro("P94_MapW") /*gvi*/
#pragma push_macro("P94_FadeDir") /*gvi*/
#undef P94_FadeDir /*gvi*/
#pragma push_macro("P94_FadeVal") /*gvi*/
#undef P94_FadeVal /*gvi*/
#pragma push_macro("P94_FadePos") /*gvi*/
#undef P94_FadePos /*gvi*/
#pragma push_macro("P94_FadeSpeed") /*gvi*/
#undef P94_FadeSpeed /*gvi*/
extern int32_t P94_FadeDir, P94_FadeVal; extern float P94_FadePos, P94_FadeSpeed;
#pragma pop_macro("P94_FadeSpeed") /*gvi*/
#pragma pop_macro("P94_FadePos") /*gvi*/
#pragma pop_macro("P94_FadeVal") /*gvi*/
#pragma pop_macro("P94_FadeDir") /*gvi*/
#pragma push_macro("P94_IconRec") /*gvi*/
#undef P94_IconRec /*gvi*/
#pragma push_macro("P94_QuadPage") /*gvi*/
#undef P94_QuadPage /*gvi*/
#pragma push_macro("P94_Quad") /*gvi*/
#undef P94_Quad /*gvi*/
extern uint32_t P94_IconRec; extern uint8_t P94_QuadPage; extern p94_quad_t P94_Quad;
#pragma pop_macro("P94_Quad") /*gvi*/
#pragma pop_macro("P94_QuadPage") /*gvi*/
#pragma pop_macro("P94_IconRec") /*gvi*/
#pragma push_macro("P94_DirCnt") /*gvi*/
#undef P94_DirCnt /*gvi*/
#pragma push_macro("P94_DirTab") /*gvi*/
#undef P94_DirTab /*gvi*/
extern int32_t P94_DirCnt; extern p94_dirtab_t P94_DirTab;
#pragma pop_macro("P94_DirTab") /*gvi*/
#pragma pop_macro("P94_DirCnt") /*gvi*/
#pragma push_macro("P94_CurveA") /*gvi*/
#undef P94_CurveA /*gvi*/
#pragma push_macro("P94_CurveB") /*gvi*/
#undef P94_CurveB /*gvi*/
#pragma push_macro("P94_CurveC") /*gvi*/
#undef P94_CurveC /*gvi*/
extern p94_curveA_t P94_CurveA; extern p94_curveB_t P94_CurveB, P94_CurveC;
#pragma pop_macro("P94_CurveC") /*gvi*/
#pragma pop_macro("P94_CurveB") /*gvi*/
#pragma pop_macro("P94_CurveA") /*gvi*/
#pragma push_macro("P94_WobA") /*gvi*/
#undef P94_WobA /*gvi*/
#pragma push_macro("P94_WobB") /*gvi*/
#undef P94_WobB /*gvi*/
#pragma push_macro("P94_WobC") /*gvi*/
#undef P94_WobC /*gvi*/
#pragma push_macro("P94_WobK") /*gvi*/
#undef P94_WobK /*gvi*/
extern int32_t P94_WobA, P94_WobB, P94_WobC; extern float P94_WobK;
#pragma pop_macro("P94_WobK") /*gvi*/
#pragma pop_macro("P94_WobC") /*gvi*/
#pragma pop_macro("P94_WobB") /*gvi*/
#pragma pop_macro("P94_WobA") /*gvi*/
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
/* gvar-img v2.03 begin (tools/gen_gvar_img.py) */
#if !defined(RE_HOOK_BUILD) && !defined(RE_GVAR_PLAIN)
#undef P94_RadarK
#define P94_RadarK (*(float *)re_gvar(0x00b32978u, sizeof(float), (void *)&P94_RadarK))
#undef P94_MapW
#define P94_MapW (*(int32_t *)re_gvar(0x00b32a30u, sizeof(int32_t), (void *)&P94_MapW))
#undef P94_MapH
#define P94_MapH (*(int32_t *)re_gvar(0x00b52a34u, sizeof(int32_t), (void *)&P94_MapH))
#undef P94_MapX0
#define P94_MapX0 (*(int32_t *)re_gvar(0x00b32a04u, sizeof(int32_t), (void *)&P94_MapX0))
#undef P94_MapY0
#define P94_MapY0 (*(int32_t *)re_gvar(0x00b32a0cu, sizeof(int32_t), (void *)&P94_MapY0))
#undef P94_FadeDir
#define P94_FadeDir (*(int32_t *)re_gvar(0x00d048f0u, sizeof(int32_t), (void *)&P94_FadeDir))
#undef P94_FadeVal
#define P94_FadeVal (*(int32_t *)re_gvar(0x00d044d4u, sizeof(int32_t), (void *)&P94_FadeVal))
#undef P94_FadePos
#define P94_FadePos (*(float *)re_gvar(0x00d04478u, sizeof(float), (void *)&P94_FadePos))
#undef P94_FadeSpeed
#define P94_FadeSpeed (*(float *)re_gvar(0x00d04784u, sizeof(float), (void *)&P94_FadeSpeed))
#undef P94_IconRec
#define P94_IconRec (*(uint32_t *)re_gvar(0x010faf20u, sizeof(uint32_t), (void *)&P94_IconRec))
#undef P94_QuadPage
#define P94_QuadPage (*(uint8_t *)re_gvar(0x010fc9a2u, sizeof(uint8_t), (void *)&P94_QuadPage))
#undef P94_Quad
#define P94_Quad (*(p94_quad_t *)re_gvar(0x010fc9a8u, sizeof(p94_quad_t), (void *)&P94_Quad))
#undef P94_DirCnt
#define P94_DirCnt (*(int32_t *)re_gvar(0x01145a48u, sizeof(int32_t), (void *)&P94_DirCnt))
#undef P94_DirTab
#define P94_DirTab (*(p94_dirtab_t *)re_gvar(0x01142700u, sizeof(p94_dirtab_t), (void *)&P94_DirTab))
#undef P94_CurveA
#define P94_CurveA (*(p94_curveA_t *)re_gvar(0x00b2f414u, sizeof(p94_curveA_t), (void *)&P94_CurveA))
#undef P94_CurveB
#define P94_CurveB (*(p94_curveB_t *)re_gvar(0x00b2eb8cu, sizeof(p94_curveB_t), (void *)&P94_CurveB))
#undef P94_CurveC
#define P94_CurveC (*(p94_curveB_t *)re_gvar(0x00b2ea4cu, sizeof(p94_curveB_t), (void *)&P94_CurveC))
#undef P94_WobA
#define P94_WobA (*(int32_t *)re_gvar(0x00553a18u, sizeof(int32_t), (void *)&P94_WobA))
#undef P94_WobB
#define P94_WobB (*(int32_t *)re_gvar(0x00b201e0u, sizeof(int32_t), (void *)&P94_WobB))
#undef P94_WobC
#define P94_WobC (*(int32_t *)re_gvar(0x00553a1cu, sizeof(int32_t), (void *)&P94_WobC))
#undef P94_WobK
#define P94_WobK (*(float *)re_gvar(0x00b201e4u, sizeof(float), (void *)&P94_WobK))
#endif
/* gvar-img v2.03 end */
