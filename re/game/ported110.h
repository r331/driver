/* v1.55 — восстановлено из Game.exe. Все функции cdecl (ret без операнда проверен по Game.exe).
   0050bd09 — отладочная сетка радара 55×55 (типы клеток — .data 00574574, в native — p110_data.h), 00502787 — полоса-индикатор с подписью,
   004aa4ea — значок в прямоугольнике 640×480, 004b53de / 004b8871 / 004b82b2 — светящиеся значки 40×40 в мире (значок 01123208),
   004cdda6 — спрайты из стека скрипта, 0041938a — значок с цветом и смешиванием, 00418675 — выбор пункта меню (обработчики — re_fn),
   00425b12 — окно 3D-вида со сдвигом (x, y) и масштабом 0125f3e0, 004e8595 — кольца дыма из сферы P96_Sphere (значок SMOKE P108_SmokeIcon). */
#pragma once
#include <stdint.h>
#include "gvar.h"

#define P110_GlowIcon GAME_VAR(uint32_t, P110_GlowIcon, 0x01123208)   /* адрес записи значка свечения */
#define P110_SelCnt   GAME_VAR(int32_t, P110_SelCnt, 0x005fea68)      /* счётчик автоповтора выбора */
#define P110_SelRep   GAME_VAR(int32_t, P110_SelRep, 0x0054e52c)      /* период автоповтора (.data: 10) */
#define P110_IconKX   GAME_VAR(float, P110_IconKX, 0x0054e520)        /* .data 1.0 */
#define P110_IconKY   GAME_VAR(float, P110_IconKY, 0x0054e524)        /* .data 1.0 */
#define P110_ClipX0   GAME_VAR(float, P110_ClipX0, 0x01252a84)     /* окно отсечения 3D-вида */
#define P110_ClipX1   GAME_VAR(float, P110_ClipX1, 0x01252a88)
#define P110_ClipY0   GAME_VAR(float, P110_ClipY0, 0x01252a8c)
#define P110_ClipY1   GAME_VAR(float, P110_ClipY1, 0x01252a90)
#define P110_FullClip GAME_VAR(int32_t, P110_FullClip, 0x00bdfa10)   /* ≠ 0 — окно на весь экран */
typedef int32_t p110_celltab_t[64];
#define P110_CellTab  GAME_VAR(p110_celltab_t, P110_CellTab, 0x00574574)
#ifndef RE_HOOK_BUILD
#pragma push_macro("P110_ClipX0") /*gvi*/
#undef P110_ClipX0 /*gvi*/
#pragma push_macro("P110_ClipX1") /*gvi*/
#undef P110_ClipX1 /*gvi*/
#pragma push_macro("P110_ClipY0") /*gvi*/
#undef P110_ClipY0 /*gvi*/
#pragma push_macro("P110_ClipY1") /*gvi*/
#undef P110_ClipY1 /*gvi*/
#pragma push_macro("P110_FullClip") /*gvi*/
#undef P110_FullClip /*gvi*/
extern float P110_ClipX0, P110_ClipX1, P110_ClipY0, P110_ClipY1; extern int32_t P110_FullClip;
#pragma pop_macro("P110_FullClip") /*gvi*/
#pragma pop_macro("P110_ClipY1") /*gvi*/
#pragma pop_macro("P110_ClipY0") /*gvi*/
#pragma pop_macro("P110_ClipX1") /*gvi*/
#pragma pop_macro("P110_ClipX0") /*gvi*/
#pragma push_macro("P110_GlowIcon") /*gvi*/
#undef P110_GlowIcon /*gvi*/
#pragma push_macro("P110_SelCnt") /*gvi*/
#undef P110_SelCnt /*gvi*/
#pragma push_macro("P110_SelRep") /*gvi*/
#undef P110_SelRep /*gvi*/
#pragma push_macro("P110_IconKX") /*gvi*/
#undef P110_IconKX /*gvi*/
#pragma push_macro("P110_IconKY") /*gvi*/
#undef P110_IconKY /*gvi*/
#pragma push_macro("P110_CellTab") /*gvi*/
#undef P110_CellTab /*gvi*/
extern uint32_t P110_GlowIcon; extern int32_t P110_SelCnt, P110_SelRep; extern float P110_IconKX, P110_IconKY; extern p110_celltab_t P110_CellTab;
#pragma pop_macro("P110_CellTab") /*gvi*/
#pragma pop_macro("P110_IconKY") /*gvi*/
#pragma pop_macro("P110_IconKX") /*gvi*/
#pragma pop_macro("P110_SelRep") /*gvi*/
#pragma pop_macro("P110_SelCnt") /*gvi*/
#pragma pop_macro("P110_GlowIcon") /*gvi*/
#endif

void    P110_RadarGrid(void);                                                              /* 0050bd09 */
void    P110_Gauge(uint8_t *p);                                                            /* 00502787 */
void    P110_IconRect(int32_t x, int32_t y, int32_t w, int32_t h, void *icon, int32_t page);  /* 004aa4ea */
void    P110_GlowA(const uint8_t *p);                                                      /* 004b53de */
void    P110_GlowB(const uint8_t *p);                                                      /* 004b8871 */
void    P110_GlowC(const uint8_t *p);                                                      /* 004b82b2 */
void    P110_ScriptSprites(void);                                                          /* 004cdda6 */
void    P110_IconQuad(float x, float y, float sx, float sy, const uint8_t *ic, uint32_t r, uint32_t g, uint32_t b, uint32_t mode); /* 0041938a */
int32_t P110_MenuSel(uint32_t tbl, int32_t cur);                                           /* 00418675 */
void    P110_ViewSetup(int32_t x, int32_t y, int32_t mode);                                  /* 00425b12 */
void    P110_SmokeRing(float sc, const float *pos, int32_t ang, uint32_t r, uint32_t g, uint32_t b, int32_t flat, int32_t tex); /* 004e8595 */
/* gvar-img v2.03 begin (tools/gen_gvar_img.py) */
#if !defined(RE_HOOK_BUILD) && !defined(RE_GVAR_PLAIN)
#undef P110_GlowIcon
#define P110_GlowIcon (*(uint32_t *)re_gvar(0x01123208u, sizeof(uint32_t), (void *)&P110_GlowIcon))
#undef P110_SelCnt
#define P110_SelCnt (*(int32_t *)re_gvar(0x005fea68u, sizeof(int32_t), (void *)&P110_SelCnt))
#undef P110_SelRep
#define P110_SelRep (*(int32_t *)re_gvar(0x0054e52cu, sizeof(int32_t), (void *)&P110_SelRep))
#undef P110_IconKX
#define P110_IconKX (*(float *)re_gvar(0x0054e520u, sizeof(float), (void *)&P110_IconKX))
#undef P110_IconKY
#define P110_IconKY (*(float *)re_gvar(0x0054e524u, sizeof(float), (void *)&P110_IconKY))
#undef P110_ClipX0
#define P110_ClipX0 (*(float *)re_gvar(0x01252a84u, sizeof(float), (void *)&P110_ClipX0))
#undef P110_ClipX1
#define P110_ClipX1 (*(float *)re_gvar(0x01252a88u, sizeof(float), (void *)&P110_ClipX1))
#undef P110_ClipY0
#define P110_ClipY0 (*(float *)re_gvar(0x01252a8cu, sizeof(float), (void *)&P110_ClipY0))
#undef P110_ClipY1
#define P110_ClipY1 (*(float *)re_gvar(0x01252a90u, sizeof(float), (void *)&P110_ClipY1))
#undef P110_FullClip
#define P110_FullClip (*(int32_t *)re_gvar(0x00bdfa10u, sizeof(int32_t), (void *)&P110_FullClip))
#undef P110_CellTab
#define P110_CellTab (*(p110_celltab_t *)re_gvar(0x00574574u, sizeof(p110_celltab_t), (void *)&P110_CellTab))
#endif
/* gvar-img v2.03 end */
