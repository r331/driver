#pragma once
#include "gvar.h"
#include "unported.h"
#include "engine.h"
#include "ported5.h"
#include "ported6.h"
#include "ported7.h"
#include "uihandlers3.h"
#include "ported12.h"
#include "ported19.h"
#include "ported20.h"
#include "ported22.h"
#include "ported24.h"
#include "ported23.h"
#include "ported27.h"
#include "ported31.h"
#include "ported35.h"
#include "ported36.h"
#include "ported46.h"
#include "menustate.h"
#include "smallfuncs.h"
#include "noop.h"
#include <stdint.h>
/* Мелкие функции (шаг D): выбор текстур значков меню, Glide-обёртки, очистка/обмен кадров, таблицы буферов roadbits/map,
   раскладка клавиш, объекты-счётчики (00493f9a/00493e3d), QueryInterface для IDirect3DTexture2.
   Все cdecl, кроме 0041de46 (stdcall ret 0xc — переходник в re_hook). */
typedef int32_t  p54_i16_t[12];   /* v1.58: 0057b578..0057b5a8 (дальше — таблица меню 0057b5a8) */
typedef int32_t  p54_i32_t[32];
typedef uint32_t p54_out_t[0x220];
typedef uint32_t p54_keysrc_t[15];
typedef uint32_t p54_keys3_t[3];
typedef uint32_t p54_dst_t[32];
typedef uint32_t p54_src6_t[6];
typedef int32_t  p54_i4_t[4];
typedef void    *p54_p4_t[4];
#include "menu57.h"
#define P54_SelTab   MENU57_VAR(p54_i16_t, P54_SelTab, 0x0057b578)  /* какие значки в меню (-1 — конец); v1.58 — в P57_MenuTab */
#define P54_IconIdx  GAME_VAR(p54_i32_t, P54_IconIdx, 0x00549c60)   /* номер опции → индекс значка в P12_00c55820 */
#define P54_Out      GAME_VAR(p54_out_t, P54_Out, 0x00549b08)       /* выход: по 0x20 байт на строку, значок в первом слове */
#define P54_KeySrc   GAME_VAR(p54_keysrc_t, P54_KeySrc, 0x0054b7a8) /* раскладка по умолчанию (5 слов), копия [6..10], 3 слова [12..14] */
#define P54_Keys3    GAME_VAR(p54_keys3_t, P54_Keys3, 0x00d04a70)
#define P54_Dst      GAME_VAR(p54_dst_t, P54_Dst, 0x00549f80)
#define P54_Src6     GAME_VAR(p54_src6_t, P54_Src6, 0x00c55908)
#define P54_RoadId   GAME_VAR(p54_i4_t, P54_RoadId, 0x00c39da0)
#define P54_RoadA    GAME_VAR(p54_p4_t, P54_RoadA, 0x00c4bdd0)
#define P54_RoadB    GAME_VAR(p54_p4_t, P54_RoadB, 0x00c1cc80)
#define P54_Tab4     GAME_VAR(p54_p4_t, P54_Tab4, 0x00c81b80)
#define P54_MapA     GAME_VAR(int32_t, P54_MapA, 0x00b31ed4)
#define P54_MapAPtr  GAME_VAR(void *, P54_MapAPtr, 0x00b31ecc)
#define P54_MapB1    GAME_VAR(int32_t, P54_MapB1, 0x00c1ed60)
#define P54_MapB2    GAME_VAR(int32_t, P54_MapB2, 0x00c1cc68)
#define P54_MapBPtr  GAME_VAR(void *, P54_MapBPtr, 0x00b5a908)
#define P54_GridN    GAME_VAR(int32_t, P54_GridN, 0x00c98ecc)
#define P54_Cnt1E0   GAME_VAR(int32_t, P54_Cnt1E0, 0x00d001e0)
#define P54_G40      GAME_VAR(int32_t, P54_G40, 0x01139a30)
#define P54_G44      GAME_VAR(int32_t, P54_G44, 0x01139a2c)
#ifndef RE_HOOK_BUILD
#pragma push_macro("P54_IconIdx") /*gvi*/
#undef P54_IconIdx /*gvi*/
#pragma push_macro("P54_Out") /*gvi*/
#undef P54_Out /*gvi*/
extern p54_i32_t P54_IconIdx; extern p54_out_t P54_Out;
#pragma pop_macro("P54_Out") /*gvi*/
#pragma pop_macro("P54_IconIdx") /*gvi*/
#pragma push_macro("P54_KeySrc") /*gvi*/
#undef P54_KeySrc /*gvi*/
#pragma push_macro("P54_Keys3") /*gvi*/
#undef P54_Keys3 /*gvi*/
#pragma push_macro("P54_Dst") /*gvi*/
#undef P54_Dst /*gvi*/
#pragma push_macro("P54_Src6") /*gvi*/
#undef P54_Src6 /*gvi*/
extern p54_keysrc_t P54_KeySrc; extern p54_keys3_t P54_Keys3; extern p54_dst_t P54_Dst; extern p54_src6_t P54_Src6;
#pragma pop_macro("P54_Src6") /*gvi*/
#pragma pop_macro("P54_Dst") /*gvi*/
#pragma pop_macro("P54_Keys3") /*gvi*/
#pragma pop_macro("P54_KeySrc") /*gvi*/
#pragma push_macro("P54_RoadId") /*gvi*/
#undef P54_RoadId /*gvi*/
extern p54_i4_t P54_RoadId; extern p54_p4_t P54_RoadA, P54_RoadB, P54_Tab4;
#pragma pop_macro("P54_RoadId") /*gvi*/
#pragma push_macro("P54_MapA") /*gvi*/
#undef P54_MapA /*gvi*/
#pragma push_macro("P54_MapB1") /*gvi*/
#undef P54_MapB1 /*gvi*/
#pragma push_macro("P54_MapB2") /*gvi*/
#undef P54_MapB2 /*gvi*/
#pragma push_macro("P54_GridN") /*gvi*/
#undef P54_GridN /*gvi*/
#pragma push_macro("P54_Cnt1E0") /*gvi*/
#undef P54_Cnt1E0 /*gvi*/
#pragma push_macro("P54_G40") /*gvi*/
#undef P54_G40 /*gvi*/
#pragma push_macro("P54_G44") /*gvi*/
#undef P54_G44 /*gvi*/
extern int32_t P54_MapA, P54_MapB1, P54_MapB2, P54_GridN, P54_Cnt1E0, P54_G40, P54_G44;
#pragma pop_macro("P54_G44") /*gvi*/
#pragma pop_macro("P54_G40") /*gvi*/
#pragma pop_macro("P54_Cnt1E0") /*gvi*/
#pragma pop_macro("P54_GridN") /*gvi*/
#pragma pop_macro("P54_MapB2") /*gvi*/
#pragma pop_macro("P54_MapB1") /*gvi*/
#pragma pop_macro("P54_MapA") /*gvi*/
extern void *P54_MapAPtr, *P54_MapBPtr;
#endif
void    P54_MenuTexSel(void);                                  /* 0040500d: значки строк меню по P54_SelTab */
void    P54_TexSource(int32_t a, int32_t b, int32_t c, const uint8_t *d, int32_t e); /* 004248c6: Glide(4 арг.) или 0041d5e7 */
void    P54_ClearBuffers(int32_t color, int32_t b, int16_t zsel); /* 0041de46 (stdcall ret 0xc): заливка заднего буфера и Z */
void    P54_ClearSwap(int32_t n);                              /* 0040c5be: clip окна, n раз очистка+обмен буферов */
void    P54_FreeTab4(void);                                    /* 004f3c16 */
void    P54_FreeRoadbits(void);                                /* 0051aacd */
void    P54_AllocRoadbits(void);                               /* 0051aa5b */
void    P54_AllocMapBufs(void);                                /* 004ecda8 */
int32_t P54_DefaultKeys(void);                                 /* 0040748a: всегда 0 */
void    P54_InitInputMode(void);                               /* 0040724c */
void    P54_ObjTick(uint8_t *o);                               /* 00493f9a */
void    P54_ObjInit(uint8_t *o);                               /* 00493e3d */
void   *P54_GetTexture2(void *tex);                            /* 0042200c: IDirect3DTexture2 через QueryInterface */
void    P54_ReadNames(void *file, int32_t size);               /* 004ec7ac */
void    P54_ReadMapA(void *file, int32_t size);                /* 004ec280 */
void    P54_ReadMapB(void *file, int32_t size);                /* 004ec3fd */
/* gvar-img v2.03 begin (tools/gen_gvar_img.py) */
#if !defined(RE_HOOK_BUILD) && !defined(RE_GVAR_PLAIN)
#undef P54_IconIdx
#define P54_IconIdx (*(p54_i32_t *)re_gvar(0x00549c60u, sizeof(p54_i32_t), (void *)&P54_IconIdx))
#undef P54_Out
#define P54_Out (*(p54_out_t *)re_gvar(0x00549b08u, sizeof(p54_out_t), (void *)&P54_Out))
#undef P54_KeySrc
#define P54_KeySrc (*(p54_keysrc_t *)re_gvar(0x0054b7a8u, sizeof(p54_keysrc_t), (void *)&P54_KeySrc))
#undef P54_Keys3
#define P54_Keys3 (*(p54_keys3_t *)re_gvar(0x00d04a70u, sizeof(p54_keys3_t), (void *)&P54_Keys3))
#undef P54_Dst
#define P54_Dst (*(p54_dst_t *)re_gvar(0x00549f80u, sizeof(p54_dst_t), (void *)&P54_Dst))
#undef P54_Src6
#define P54_Src6 (*(p54_src6_t *)re_gvar(0x00c55908u, sizeof(p54_src6_t), (void *)&P54_Src6))
#undef P54_RoadId
#define P54_RoadId (*(p54_i4_t *)re_gvar(0x00c39da0u, sizeof(p54_i4_t), (void *)&P54_RoadId))
#undef P54_MapA
#define P54_MapA (*(int32_t *)re_gvar(0x00b31ed4u, sizeof(int32_t), (void *)&P54_MapA))
#undef P54_MapB1
#define P54_MapB1 (*(int32_t *)re_gvar(0x00c1ed60u, sizeof(int32_t), (void *)&P54_MapB1))
#undef P54_MapB2
#define P54_MapB2 (*(int32_t *)re_gvar(0x00c1cc68u, sizeof(int32_t), (void *)&P54_MapB2))
#undef P54_GridN
#define P54_GridN (*(int32_t *)re_gvar(0x00c98eccu, sizeof(int32_t), (void *)&P54_GridN))
#undef P54_Cnt1E0
#define P54_Cnt1E0 (*(int32_t *)re_gvar(0x00d001e0u, sizeof(int32_t), (void *)&P54_Cnt1E0))
#undef P54_G40
#define P54_G40 (*(int32_t *)re_gvar(0x01139a30u, sizeof(int32_t), (void *)&P54_G40))
#undef P54_G44
#define P54_G44 (*(int32_t *)re_gvar(0x01139a2cu, sizeof(int32_t), (void *)&P54_G44))
#endif
/* gvar-img v2.03 end */
