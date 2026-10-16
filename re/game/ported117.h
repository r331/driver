/* v1.62, ported117 — восстановлено из Game.exe. Все функции cdecl (ret без операнда; work/rets.py).
   0051dd1b — запись следа колеса w машины игрока в таблицу 00b5c950 (P116_SkidRecA): углы днища P102_Corners (int), прошлые — P117_PrevCorn 00b5c858;
   0051e1b7 — то же для колеса w по float-точке (прошлые — P56_Blk16 00b5c898) в таблицу 00b6e950 (P116_SkidRecB);
             запись 0x48: [0] вкл, [2] s16 состояние (2 — продолжение), [4] поверхность (1 — модель клетки с флагом 0x4000),
             +8..+0x44 — 4 точки (x, −y−20, z, —) полосы шириной 50 поперёк направления движения; пыль/искры 004b8f4e;
   00504cad — радар: рамка 0x111111, повёрнутая по курсу текстура карты (два треугольника P85_RasterB, окно отсечения 01270d30),
             мигание цвета при 00d11a5c ≥ 0x2aa и P95_AmbN ≥ 1, затем значки (00506b4b, 00506bff, 00505b54, 005062cc, 00506fa0);
   00502fe2 — полноэкранная карта: страницы 256×256 из P99_C80880 (8 бит — 005046f7, 16 бит — 005047ab) и прямоугольники P108_MapTexRect.
   .data меню паузы 00574f08 / 00575088 / 00575370 — массивы P117_MenuA/B/C (game/p117_data.h), зарегистрированы в k_regions. */
#pragma once
#include <stdint.h>
#include "gvar.h"
typedef uint8_t p117_menuA_t[0x140];
typedef uint8_t p117_menuB_t[0x2a8];
typedef uint8_t p117_menuC_t[0x168];
typedef int32_t p117_i4_t[4];
typedef uint32_t p117_u4_t[4];
typedef int32_t p117_i16_t[16];
#ifdef RE_HOOK_BUILD
typedef void (__attribute__((stdcall)) *p117_clip_fn)(int32_t x0, int32_t y0, int32_t x1, int32_t y1);
#else
typedef void (*p117_clip_fn)(int32_t x0, int32_t y0, int32_t x1, int32_t y1);
#endif
#define P117_MenuA     GAME_VAR(p117_menuA_t, P117_MenuA, 0x00574f08)   /* меню звука (P11_00574f08, P97_SndMenu = +0x30) */
#define P117_MenuB     GAME_VAR(p117_menuB_t, P117_MenuB, 0x00575088)   /* меню управления (P11_00575088) */
#define P117_MenuC     GAME_VAR(p117_menuC_t, P117_MenuC, 0x00575370)   /* ввод имени (P11_00575370) */
#define P117_PrevCorn  GAME_VAR(p117_i16_t, P117_PrevCorn, 0x00b5c858) /* прошлые углы днища (копия P102_Corners, 0051d811); G00B5C858.. — псевдонимы */
#define P117_SkidStA   GAME_VAR(p117_i4_t, P117_SkidStA, 0x00b5c8f4)   /* след колеса идёт (1) — таблица A */
#define P117_SkidLastA GAME_VAR(p117_u4_t, P117_SkidLastA, 0x00b5c844) /* адрес последней записи следа колеса — таблица A */
#define P117_SkidStB   GAME_VAR(p117_i4_t, P117_SkidStB, 0x00b5c824)
#define P117_SkidLastB GAME_VAR(p117_u4_t, P117_SkidLastB, 0x00b5c834)
#define P117_ClipFn    GAME_VAR(p117_clip_fn, P117_ClipFn, 0x01270d30) /* окно отсечения (обёртка grClipWindow) */
#ifndef RE_HOOK_BUILD
#pragma push_macro("P117_MenuA") /*gvi*/
#undef P117_MenuA /*gvi*/
#pragma push_macro("P117_MenuB") /*gvi*/
#undef P117_MenuB /*gvi*/
#pragma push_macro("P117_MenuC") /*gvi*/
#undef P117_MenuC /*gvi*/
#pragma push_macro("P117_PrevCorn") /*gvi*/
#undef P117_PrevCorn /*gvi*/
extern p117_menuA_t P117_MenuA; extern p117_menuB_t P117_MenuB; extern p117_menuC_t P117_MenuC; extern p117_i16_t P117_PrevCorn;
#pragma pop_macro("P117_PrevCorn") /*gvi*/
#pragma pop_macro("P117_MenuC") /*gvi*/
#pragma pop_macro("P117_MenuB") /*gvi*/
#pragma pop_macro("P117_MenuA") /*gvi*/
#pragma push_macro("P117_SkidStA") /*gvi*/
#undef P117_SkidStA /*gvi*/
#pragma push_macro("P117_SkidStB") /*gvi*/
#undef P117_SkidStB /*gvi*/
#pragma push_macro("P117_SkidLastA") /*gvi*/
#undef P117_SkidLastA /*gvi*/
#pragma push_macro("P117_SkidLastB") /*gvi*/
#undef P117_SkidLastB /*gvi*/
extern p117_i4_t P117_SkidStA, P117_SkidStB; extern p117_u4_t P117_SkidLastA, P117_SkidLastB; extern p117_clip_fn P117_ClipFn;
#pragma pop_macro("P117_SkidLastB") /*gvi*/
#pragma pop_macro("P117_SkidLastA") /*gvi*/
#pragma pop_macro("P117_SkidStB") /*gvi*/
#pragma pop_macro("P117_SkidStA") /*gvi*/
#endif
void P117_SkidRecA(int32_t w);                      /* 0051dd1b */
void P117_SkidRecB(int32_t w, const float *pos);    /* 0051e1b7 */
void P117_Radar(void);                              /* 00504cad */
void P117_FullMap(void);                            /* 00502fe2 */
void P117_TextList(void);                           /* 0040ce31: надписи меню из списка P45_PtrA */
/* gvar-img v2.03 begin (tools/gen_gvar_img.py) */
#if !defined(RE_HOOK_BUILD) && !defined(RE_GVAR_PLAIN)
#undef P117_MenuA
#define P117_MenuA (*(p117_menuA_t *)re_gvar(0x00574f08u, sizeof(p117_menuA_t), (void *)&P117_MenuA))
#undef P117_MenuB
#define P117_MenuB (*(p117_menuB_t *)re_gvar(0x00575088u, sizeof(p117_menuB_t), (void *)&P117_MenuB))
#undef P117_MenuC
#define P117_MenuC (*(p117_menuC_t *)re_gvar(0x00575370u, sizeof(p117_menuC_t), (void *)&P117_MenuC))
#undef P117_PrevCorn
#define P117_PrevCorn (*(p117_i16_t *)re_gvar(0x00b5c858u, sizeof(p117_i16_t), (void *)&P117_PrevCorn))
#undef P117_SkidStA
#define P117_SkidStA (*(p117_i4_t *)re_gvar(0x00b5c8f4u, sizeof(p117_i4_t), (void *)&P117_SkidStA))
#undef P117_SkidLastA
#define P117_SkidLastA (*(p117_u4_t *)re_gvar(0x00b5c844u, sizeof(p117_u4_t), (void *)&P117_SkidLastA))
#undef P117_SkidStB
#define P117_SkidStB (*(p117_i4_t *)re_gvar(0x00b5c824u, sizeof(p117_i4_t), (void *)&P117_SkidStB))
#undef P117_SkidLastB
#define P117_SkidLastB (*(p117_u4_t *)re_gvar(0x00b5c834u, sizeof(p117_u4_t), (void *)&P117_SkidLastB))
#endif
/* gvar-img v2.03 end */
