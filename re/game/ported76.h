#pragma once
#include "gvar.h"
#include "unported.h"
#include "crt.h"
#include "ported6.h"
#include "ported11.h"
#include "ported12.h"
#include "ported16.h"
#include "ported21.h"
#include "ported22.h"
#include "ported23.h"
#include "ported31.h"
#include "ported33.h"
#include "ported42.h"
#include "ported54.h"
#include "ported62.h"
#include "ported74.h"
#include <stdint.h>
/* Шаг D, ported76 (все cdecl):
   - 4 отправки треугольника в буфер вершин слота текстуры (0041e926/0041f825 — формат A, 0041ea2a/0041f929 — формат B);
   - 0048a525 — пометка записей слотов (список индексов в 0125f420 + n*0x46, таблицы 01145a60 / 01146f20);
   - 00424b70 — регистрация устройства Glide («3Dfx», «Glide 2.x»);
   - 0040dbee — заливка кадра цветом (плитки 256x256 через 0040dce0, затем grBufferSwap);
   - 004a3aa7 — шаг мигания объекта (счётчик +0x30);
   - 004ecee8 / 004ee813 — клетка сетки по координатам;
   - 004e8f1e — цвет по углу (байты d02668/d02320/d02669 → 004268ef);
   - 0051caa7 — чтение таблиц рекордов из файла (заголовок 'ERCS', версия 3). */
#define P76_Angle   GAME_VAR(int32_t, P76_Angle, 0x00d02680)
#define P76_ColA    GAME_VAR(uint8_t, P76_ColA, 0x00d02668)
#define P76_ColB    GAME_VAR(uint8_t, P76_ColB, 0x00d02320)
#define P76_ColC    GAME_VAR(uint8_t, P76_ColC, 0x00d02669)
typedef uint8_t p76_obj_t[0x40];
#define P76_ColObj  GAME_VAR(p76_obj_t, P76_ColObj, 0x00d02650)
#define P76_NumSlots GAME_VAR(int32_t, P76_NumSlots, 0x00cfe6e0)
#define P76_K255    GAME_VAR(float, P76_K255, 0x00546064)
#ifndef RE_HOOK_BUILD
#pragma push_macro("P76_Angle") /*gvi*/
#undef P76_Angle /*gvi*/
#pragma push_macro("P76_NumSlots") /*gvi*/
#undef P76_NumSlots /*gvi*/
#pragma push_macro("P76_ColA") /*gvi*/
#undef P76_ColA /*gvi*/
#pragma push_macro("P76_ColB") /*gvi*/
#undef P76_ColB /*gvi*/
#pragma push_macro("P76_ColC") /*gvi*/
#undef P76_ColC /*gvi*/
#pragma push_macro("P76_ColObj") /*gvi*/
#undef P76_ColObj /*gvi*/
#pragma push_macro("P76_K255") /*gvi*/
#undef P76_K255 /*gvi*/
extern int32_t P76_Angle, P76_NumSlots; extern uint8_t P76_ColA, P76_ColB, P76_ColC; extern p76_obj_t P76_ColObj; extern float P76_K255;
#pragma pop_macro("P76_K255") /*gvi*/
#pragma pop_macro("P76_ColObj") /*gvi*/
#pragma pop_macro("P76_ColC") /*gvi*/
#pragma pop_macro("P76_ColB") /*gvi*/
#pragma pop_macro("P76_ColA") /*gvi*/
#pragma pop_macro("P76_NumSlots") /*gvi*/
#pragma pop_macro("P76_Angle") /*gvi*/
#endif
void P76_InitConsts(void);
void P76_TriA1(const int32_t *a, const int32_t *b, const int32_t *c);   /* 0041e926 */
void P76_TriB1(const int32_t *a, const int32_t *b, const int32_t *c);   /* 0041ea2a */
void P76_TriA2(const int32_t *a, const int32_t *b, const int32_t *c);   /* 0041f825 */
void P76_TriB2(const int32_t *a, const int32_t *b, const int32_t *c);   /* 0041f929 */
void P76_MarkSlots(int32_t n);                                          /* 0048a525 */
int32_t P76_GlideRegister(void);                                        /* 00424b70 */
void P76_TileFill(float v);                                             /* 0040dbee */
void P76_FlashStep(int32_t *o);                                         /* 004a3aa7 */
int32_t P76_InBox(const float *pos, const uint8_t *grid, int32_t cx, int32_t cy);   /* 004ecee8 */
void P76_CellFromPos(const float *pos, uint8_t *arg, int32_t *ox, int32_t *oy);      /* 004ee813 */
void P76_AngleColor(void);                                              /* 004e8f1e */
int32_t P76_LoadHsTables(void *f);                                      /* 0051caa7 */
/* gvar-img v2.03 begin (tools/gen_gvar_img.py) */
#if !defined(RE_HOOK_BUILD) && !defined(RE_GVAR_PLAIN)
#undef P76_Angle
#define P76_Angle (*(int32_t *)re_gvar(0x00d02680u, sizeof(int32_t), (void *)&P76_Angle))
#undef P76_ColA
#define P76_ColA (*(uint8_t *)re_gvar(0x00d02668u, sizeof(uint8_t), (void *)&P76_ColA))
#undef P76_ColB
#define P76_ColB (*(uint8_t *)re_gvar(0x00d02320u, sizeof(uint8_t), (void *)&P76_ColB))
#undef P76_ColC
#define P76_ColC (*(uint8_t *)re_gvar(0x00d02669u, sizeof(uint8_t), (void *)&P76_ColC))
#undef P76_ColObj
#define P76_ColObj (*(p76_obj_t *)re_gvar(0x00d02650u, sizeof(p76_obj_t), (void *)&P76_ColObj))
#undef P76_NumSlots
#define P76_NumSlots (*(int32_t *)re_gvar(0x00cfe6e0u, sizeof(int32_t), (void *)&P76_NumSlots))
#undef P76_K255
#define P76_K255 (*(float *)re_gvar(0x00546064u, sizeof(float), (void *)&P76_K255))
#endif
/* gvar-img v2.03 end */
