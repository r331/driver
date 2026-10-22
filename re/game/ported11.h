#pragma once
#include "gvar.h"
#include "nodetab.h"
#include "unported.h"
#include "menustate.h"
#include "ported10.h"
#include "ported117.h"
#include <stdint.h>
#include <string.h>
#include <math.h>
/* Партия v0.45 */
typedef int16_t p11_s16arr[0x8000];
typedef uint32_t p11_u32arr[0x400];
#ifdef RE_HOOK_BUILD
#  define ADDR(x) ((uint32_t)(uintptr_t)&(x))
#else
#  include "reptr.h"
#  define ADDR(x) re_addr(&(x))   /* v2.04: адрес Game.exe (образ данных/реестр), а не усечённый 64-битный указатель */
#endif
#define P11_00b87e7c GAME_VAR(int32_t, P11_00b87e7c, 0x00b87e7c)
#ifndef RE_HOOK_BUILD
#pragma push_macro("P11_00b87e7c") /*gvi*/
#undef P11_00b87e7c /*gvi*/
extern int32_t P11_00b87e7c;
#pragma pop_macro("P11_00b87e7c") /*gvi*/
#endif
#define P11_005c6760 GAME_VAR(int32_t, P11_005c6760, 0x005c6760)
#ifndef RE_HOOK_BUILD
#pragma push_macro("P11_005c6760") /*gvi*/
#undef P11_005c6760 /*gvi*/
extern int32_t P11_005c6760;
#pragma pop_macro("P11_005c6760") /*gvi*/
#endif
#define P11_01271060 GAME_VAR(int32_t, P11_01271060, 0x01271060)
#ifndef RE_HOOK_BUILD
#pragma push_macro("P11_01271060") /*gvi*/
#undef P11_01271060 /*gvi*/
extern int32_t P11_01271060;
#pragma pop_macro("P11_01271060") /*gvi*/
#endif
#define P11_00b87e38 GAME_VAR(int32_t, P11_00b87e38, 0x00b87e38)
#ifndef RE_HOOK_BUILD
#pragma push_macro("P11_00b87e38") /*gvi*/
#undef P11_00b87e38 /*gvi*/
extern int32_t P11_00b87e38;
#pragma pop_macro("P11_00b87e38") /*gvi*/
#endif
#define P11_00b20360 GAME_VAR(int32_t, P11_00b20360, 0x00b20360)
#ifndef RE_HOOK_BUILD
#pragma push_macro("P11_00b20360") /*gvi*/
#undef P11_00b20360 /*gvi*/
extern int32_t P11_00b20360;
#pragma pop_macro("P11_00b20360") /*gvi*/
#endif
#define P11_00c81494 GAME_VAR(int32_t, P11_00c81494, 0x00c81494)
#ifndef RE_HOOK_BUILD
#pragma push_macro("P11_00c81494") /*gvi*/
#undef P11_00c81494 /*gvi*/
extern int32_t P11_00c81494;
#pragma pop_macro("P11_00c81494") /*gvi*/
#endif
#define P11_00ba52d0 GAME_VAR(int32_t, P11_00ba52d0, 0x00ba52d0)
#ifndef RE_HOOK_BUILD
#pragma push_macro("P11_00ba52d0") /*gvi*/
#undef P11_00ba52d0 /*gvi*/
extern int32_t P11_00ba52d0;
#pragma pop_macro("P11_00ba52d0") /*gvi*/
#endif
#define P11_00b31efc GAME_VAR(int32_t, P11_00b31efc, 0x00b31efc)
#ifndef RE_HOOK_BUILD
#pragma push_macro("P11_00b31efc") /*gvi*/
#undef P11_00b31efc /*gvi*/
extern int32_t P11_00b31efc;
#pragma pop_macro("P11_00b31efc") /*gvi*/
#endif
#define P11_00c823d0 GAME_VAR(int32_t, P11_00c823d0, 0x00c823d0)
#ifndef RE_HOOK_BUILD
#pragma push_macro("P11_00c823d0") /*gvi*/
#undef P11_00c823d0 /*gvi*/
extern int32_t P11_00c823d0;
#pragma pop_macro("P11_00c823d0") /*gvi*/
#endif
#define P11_00d11934 GAME_VAR(int32_t, P11_00d11934, 0x00d11934)
#ifndef RE_HOOK_BUILD
#pragma push_macro("P11_00d11934") /*gvi*/
#undef P11_00d11934 /*gvi*/
extern int32_t P11_00d11934;
#pragma pop_macro("P11_00d11934") /*gvi*/
#endif
#define P11_00b5a734 GAME_VAR(int32_t, P11_00b5a734, 0x00b5a734)
#ifndef RE_HOOK_BUILD
#pragma push_macro("P11_00b5a734") /*gvi*/
#undef P11_00b5a734 /*gvi*/
extern int32_t P11_00b5a734;
#pragma pop_macro("P11_00b5a734") /*gvi*/
#endif
#define P11_00b5a730 GAME_VAR(int32_t, P11_00b5a730, 0x00b5a730)
#ifndef RE_HOOK_BUILD
#pragma push_macro("P11_00b5a730") /*gvi*/
#undef P11_00b5a730 /*gvi*/
extern int32_t P11_00b5a730;
#pragma pop_macro("P11_00b5a730") /*gvi*/
#endif
#define P11_00575554 GAME_VAR(int32_t, P11_00575554, 0x00575554)
#ifndef RE_HOOK_BUILD
#pragma push_macro("P11_00575554") /*gvi*/
#undef P11_00575554 /*gvi*/
extern int32_t P11_00575554;
#pragma pop_macro("P11_00575554") /*gvi*/
#endif
#define P11_00575550 GAME_VAR(int32_t, P11_00575550, 0x00575550)
#ifndef RE_HOOK_BUILD
#pragma push_macro("P11_00575550") /*gvi*/
#undef P11_00575550 /*gvi*/
extern int32_t P11_00575550;
#pragma pop_macro("P11_00575550") /*gvi*/
#endif
#define P11_00bdc28c GAME_VAR(int32_t, P11_00bdc28c, 0x00bdc28c)
#ifndef RE_HOOK_BUILD
#pragma push_macro("P11_00bdc28c") /*gvi*/
#undef P11_00bdc28c /*gvi*/
extern int32_t P11_00bdc28c;
#pragma pop_macro("P11_00bdc28c") /*gvi*/
#endif
#define P11_005507d0 GAME_VAR(int32_t, P11_005507d0, 0x005507d0)
#ifndef RE_HOOK_BUILD
#pragma push_macro("P11_005507d0") /*gvi*/
#undef P11_005507d0 /*gvi*/
extern int32_t P11_005507d0;
#pragma pop_macro("P11_005507d0") /*gvi*/
#endif
#define P11_005507d4 GAME_VAR(int32_t, P11_005507d4, 0x005507d4)
#ifndef RE_HOOK_BUILD
#pragma push_macro("P11_005507d4") /*gvi*/
#undef P11_005507d4 /*gvi*/
extern int32_t P11_005507d4;
#pragma pop_macro("P11_005507d4") /*gvi*/
#endif
#define P11_005507d8 GAME_VAR(int32_t, P11_005507d8, 0x005507d8)
#ifndef RE_HOOK_BUILD
#pragma push_macro("P11_005507d8") /*gvi*/
#undef P11_005507d8 /*gvi*/
extern int32_t P11_005507d8;
#pragma pop_macro("P11_005507d8") /*gvi*/
#endif
#define P11_00b5a8e8 GAME_VAR(int32_t, P11_00b5a8e8, 0x00b5a8e8)
#ifndef RE_HOOK_BUILD
#pragma push_macro("P11_00b5a8e8") /*gvi*/
#undef P11_00b5a8e8 /*gvi*/
extern int32_t P11_00b5a8e8;
#pragma pop_macro("P11_00b5a8e8") /*gvi*/
#endif
#define P11_00b5a8ec GAME_VAR(int32_t, P11_00b5a8ec, 0x00b5a8ec)
#ifndef RE_HOOK_BUILD
#pragma push_macro("P11_00b5a8ec") /*gvi*/
#undef P11_00b5a8ec /*gvi*/
extern int32_t P11_00b5a8ec;
#pragma pop_macro("P11_00b5a8ec") /*gvi*/
#endif
#define P11_01270c38 GAME_VAR(int32_t, P11_01270c38, 0x01270c38)
#ifndef RE_HOOK_BUILD
#pragma push_macro("P11_01270c38") /*gvi*/
#undef P11_01270c38 /*gvi*/
extern int32_t P11_01270c38;
#pragma pop_macro("P11_01270c38") /*gvi*/
#endif
#define P11_00575ef8 GAME_VAR(int32_t, P11_00575ef8, 0x00575ef8)
#ifndef RE_HOOK_BUILD
#pragma push_macro("P11_00575ef8") /*gvi*/
#undef P11_00575ef8 /*gvi*/
extern int32_t P11_00575ef8;
#pragma pop_macro("P11_00575ef8") /*gvi*/
#endif
#define P11_01270c24 GAME_VAR(float, P11_01270c24, 0x01270c24)
#ifndef RE_HOOK_BUILD
#pragma push_macro("P11_01270c24") /*gvi*/
#undef P11_01270c24 /*gvi*/
extern float P11_01270c24;
#pragma pop_macro("P11_01270c24") /*gvi*/
#endif
#define P11_01270c28 GAME_VAR(float, P11_01270c28, 0x01270c28)
#ifndef RE_HOOK_BUILD
#pragma push_macro("P11_01270c28") /*gvi*/
#undef P11_01270c28 /*gvi*/
extern float P11_01270c28;
#pragma pop_macro("P11_01270c28") /*gvi*/
#endif
#define P11_0125f3e0 GAME_VAR(float, P11_0125f3e0, 0x0125f3e0)
#ifndef RE_HOOK_BUILD
#pragma push_macro("P11_0125f3e0") /*gvi*/
#undef P11_0125f3e0 /*gvi*/
extern float P11_0125f3e0;
#pragma pop_macro("P11_0125f3e0") /*gvi*/
#endif
#define P11_0125f3f8 GAME_VAR(float, P11_0125f3f8, 0x0125f3f8)
#ifndef RE_HOOK_BUILD
#pragma push_macro("P11_0125f3f8") /*gvi*/
#undef P11_0125f3f8 /*gvi*/
extern float P11_0125f3f8;
#pragma pop_macro("P11_0125f3f8") /*gvi*/
#endif
#define P11_00546028 GAME_VAR(float, P11_00546028, 0x00546028)
#ifndef RE_HOOK_BUILD
#pragma push_macro("P11_00546028") /*gvi*/
#undef P11_00546028 /*gvi*/
extern float P11_00546028;
#pragma pop_macro("P11_00546028") /*gvi*/
#endif
#define P11_0054602c GAME_VAR(float, P11_0054602c, 0x0054602c)
#ifndef RE_HOOK_BUILD
#pragma push_macro("P11_0054602c") /*gvi*/
#undef P11_0054602c /*gvi*/
extern float P11_0054602c;
#pragma pop_macro("P11_0054602c") /*gvi*/
#endif
#define P11_0054604c GAME_VAR(float, P11_0054604c, 0x0054604c)
#ifndef RE_HOOK_BUILD
#pragma push_macro("P11_0054604c") /*gvi*/
#undef P11_0054604c /*gvi*/
extern float P11_0054604c;
#pragma pop_macro("P11_0054604c") /*gvi*/
#endif
#define P11_00546054 GAME_VAR(float, P11_00546054, 0x00546054)
#ifndef RE_HOOK_BUILD
#pragma push_macro("P11_00546054") /*gvi*/
#undef P11_00546054 /*gvi*/
extern float P11_00546054;
#pragma pop_macro("P11_00546054") /*gvi*/
#endif
#define P11_00546080 GAME_VAR(float, P11_00546080, 0x00546080)
#ifndef RE_HOOK_BUILD
#pragma push_macro("P11_00546080") /*gvi*/
#undef P11_00546080 /*gvi*/
extern float P11_00546080;
#pragma pop_macro("P11_00546080") /*gvi*/
#endif
#define P11_00c1ed8a SLOTTAB_VAR(p11_s16arr, P11_00c1ed8a, 0x00c1ed8a)   /* v1.46: над P11_00c1ed80 */
#ifndef RE_HOOK_BUILD
#endif
#define P11_00572b40 GAME_VAR(p11_u32arr, P11_00572b40, 0x00572b40)
#ifndef RE_HOOK_BUILD
#pragma push_macro("P11_00572b40") /*gvi*/
#undef P11_00572b40 /*gvi*/
extern p11_u32arr P11_00572b40;
#pragma pop_macro("P11_00572b40") /*gvi*/
#endif
#define P11_0057b740 GAME_VAR(uint8_t, P11_0057b740, 0x0057b740)
#ifndef RE_HOOK_BUILD
#pragma push_macro("P11_0057b740") /*gvi*/
#undef P11_0057b740 /*gvi*/
extern uint8_t P11_0057b740;
#pragma pop_macro("P11_0057b740") /*gvi*/
#endif
#define P11_005d592e GAME_VAR(uint8_t, P11_005d592e, 0x005d592e)
#ifndef RE_HOOK_BUILD
#pragma push_macro("P11_005d592e") /*gvi*/
#undef P11_005d592e /*gvi*/
extern uint8_t P11_005d592e;
#pragma pop_macro("P11_005d592e") /*gvi*/
#endif
#define P11_005d57ae GAME_VAR(uint8_t, P11_005d57ae, 0x005d57ae)
#ifndef RE_HOOK_BUILD
#pragma push_macro("P11_005d57ae") /*gvi*/
#undef P11_005d57ae /*gvi*/
extern uint8_t P11_005d57ae;
#pragma pop_macro("P11_005d57ae") /*gvi*/
#endif
typedef uint8_t p11_big_t[0x40000];   /* таблицы уровня (ReadTable_*): в native нужен реальный объём, счётчик ограничен */
typedef uint8_t p11_slots_t[0x400 * 0x46];   /* 0x400 записей по 0x46 байт: первые 0x40 — список индексов (0xff — конец) */
#define P11_0125f420 GAME_VAR(p11_slots_t, P11_0125f420, 0x0125f420)
#ifndef RE_HOOK_BUILD
#pragma push_macro("P11_0125f420") /*gvi*/
#undef P11_0125f420 /*gvi*/
extern p11_slots_t P11_0125f420;
#pragma pop_macro("P11_0125f420") /*gvi*/
#endif
#define P11_00bf1c40 GAME_VAR(p11_big_t, P11_00bf1c40, 0x00bf1c40)
#ifndef RE_HOOK_BUILD
#pragma push_macro("P11_00bf1c40") /*gvi*/
#undef P11_00bf1c40 /*gvi*/
extern p11_big_t P11_00bf1c40;
#pragma pop_macro("P11_00bf1c40") /*gvi*/
#endif
#define P11_00c1ed80 GAME_VAR(p11_big_t, P11_00c1ed80, 0x00c1ed80)
#ifndef RE_HOOK_BUILD
#pragma push_macro("P11_00c1ed80") /*gvi*/
#undef P11_00c1ed80 /*gvi*/
extern p11_big_t P11_00c1ed80;
#pragma pop_macro("P11_00c1ed80") /*gvi*/
#endif
#define P11_00c12c60 GAME_VAR(p11_big_t, P11_00c12c60, 0x00c12c60)
#ifndef RE_HOOK_BUILD
#pragma push_macro("P11_00c12c60") /*gvi*/
#undef P11_00c12c60 /*gvi*/
extern p11_big_t P11_00c12c60;
#pragma pop_macro("P11_00c12c60") /*gvi*/
#endif
#define P11_00c1cd20 GAME_VAR(p11_big_t, P11_00c1cd20, 0x00c1cd20)
#ifndef RE_HOOK_BUILD
#pragma push_macro("P11_00c1cd20") /*gvi*/
#undef P11_00c1cd20 /*gvi*/
extern p11_big_t P11_00c1cd20;
#pragma pop_macro("P11_00c1cd20") /*gvi*/
#endif
#define P11_00c80c60 GAME_VAR(uint8_t, P11_00c80c60, 0x00c80c60)
#ifndef RE_HOOK_BUILD
#pragma push_macro("P11_00c80c60") /*gvi*/
#undef P11_00c80c60 /*gvi*/
extern uint8_t P11_00c80c60;
#pragma pop_macro("P11_00c80c60") /*gvi*/
#endif
#define P11_00552e18 GAME_VAR(uint8_t, P11_00552e18, 0x00552e18)
#ifndef RE_HOOK_BUILD
#pragma push_macro("P11_00552e18") /*gvi*/
#undef P11_00552e18 /*gvi*/
extern uint8_t P11_00552e18;
#pragma pop_macro("P11_00552e18") /*gvi*/
#endif
#define P11_00579710 GAME_VAR(uint8_t, P11_00579710, 0x00579710)
#ifndef RE_HOOK_BUILD
#pragma push_macro("P11_00579710") /*gvi*/
#undef P11_00579710 /*gvi*/
extern uint8_t P11_00579710;
#pragma pop_macro("P11_00579710") /*gvi*/
#endif
#define P11_00b94280 GAME_VAR(uint8_t, P11_00b94280, 0x00b94280)
#ifndef RE_HOOK_BUILD
#pragma push_macro("P11_00b94280") /*gvi*/
#undef P11_00b94280 /*gvi*/
extern uint8_t P11_00b94280;
#pragma pop_macro("P11_00b94280") /*gvi*/
#endif
#define P11_00b98280 GAME_VAR(uint8_t, P11_00b98280, 0x00b98280)
#ifndef RE_HOOK_BUILD
#pragma push_macro("P11_00b98280") /*gvi*/
#undef P11_00b98280 /*gvi*/
extern uint8_t P11_00b98280;
#pragma pop_macro("P11_00b98280") /*gvi*/
#endif
#define P11_011f4080 GAME_VAR(uint8_t, P11_011f4080, 0x011f4080)
#ifndef RE_HOOK_BUILD
#pragma push_macro("P11_011f4080") /*gvi*/
#undef P11_011f4080 /*gvi*/
extern uint8_t P11_011f4080;
#pragma pop_macro("P11_011f4080") /*gvi*/
#endif
#define P11_00b1c268 GAME_VAR(uint8_t, P11_00b1c268, 0x00b1c268)
#ifndef RE_HOOK_BUILD
#pragma push_macro("P11_00b1c268") /*gvi*/
#undef P11_00b1c268 /*gvi*/
extern uint8_t P11_00b1c268;
#pragma pop_macro("P11_00b1c268") /*gvi*/
#endif
#define P11_011effa0 GAME_VAR(uint8_t, P11_011effa0, 0x011effa0)
#ifndef RE_HOOK_BUILD
#pragma push_macro("P11_011effa0") /*gvi*/
#undef P11_011effa0 /*gvi*/
extern uint8_t P11_011effa0;
#pragma pop_macro("P11_011effa0") /*gvi*/
#endif
#define P11_00575370 (P117_MenuC[0])   /* v1.62: .data меню (game/p117_data.h) */
#ifndef RE_HOOK_BUILD

#endif
#define P11_00574f08 (P117_MenuA[0])   /* v1.62: .data меню (game/p117_data.h) */
#ifndef RE_HOOK_BUILD

#endif
#define P11_00575088 (P117_MenuB[0])   /* v1.62: .data меню (game/p117_data.h) */
#ifndef RE_HOOK_BUILD

#endif
void SndHelper_00407D97(uint8_t a, uint8_t b);
void SndHelper_00407D56(int32_t x, int32_t y, uint32_t p3, uint32_t p4, uint32_t p5);
void CopySlots_0040AA82(uint32_t n);
uint32_t MenuAction_0041645B(void);
uint32_t MenuAction_004164B2(void);
uint32_t GetRect_0048F34C(int32_t i);
void DrawFrame_004A9DDC(int32_t x, int32_t y, int32_t w, int32_t h);
uint32_t ScriptReadShort3_004D02C6(void);
uint32_t ScriptReadVec3_004D033F(void);
void TryStartTrack_004D611B(uint32_t a);
void DrawBanner_004F5D98(void);
void ReadBlocks_004EB7CF(void *f);
void ReadTable_004EC466(void *f);
void ReadTable_004EC49A(void *f);
void ReadTable_004EC522(void *f);
void ReadTable_004EC556(void *f);
void FreeBuffer_004F30E6(void);
void ResolveTable_004FE830(void);
void BackOrDirector_005103C4(void);
void SwitchPanel_005104B9(void);
void SwitchPanel_0051066A(void);
void SwitchPanel_0051069E(void);
void ResetDirector_00522306(void);
void InitChannels_0052436A(void);
void LoadFsin_00525E50(void);
void InitXform_005263FE(void);
void InitVec_00526582(void);
void RoundSet_004BF400(float a, float b);
void StepUp_0051010C(void);
void StepDown_00510145(void);
void StepUp_0051017E(void);
void StepDown_005101B7(void);
void Zoom_00425E9E(void);
/* gvar-img v2.03 begin (tools/gen_gvar_img.py) */
#if !defined(RE_HOOK_BUILD) && !defined(RE_GVAR_PLAIN)
#undef P11_00b87e7c
#define P11_00b87e7c (*(int32_t *)re_gvar(0x00b87e7cu, sizeof(int32_t), (void *)&P11_00b87e7c))
#undef P11_005c6760
#define P11_005c6760 (*(int32_t *)re_gvar(0x005c6760u, sizeof(int32_t), (void *)&P11_005c6760))
#undef P11_01271060
#define P11_01271060 (*(int32_t *)re_gvar(0x01271060u, sizeof(int32_t), (void *)&P11_01271060))
#undef P11_00b87e38
#define P11_00b87e38 (*(int32_t *)re_gvar(0x00b87e38u, sizeof(int32_t), (void *)&P11_00b87e38))
#undef P11_00b20360
#define P11_00b20360 (*(int32_t *)re_gvar(0x00b20360u, sizeof(int32_t), (void *)&P11_00b20360))
#undef P11_00c81494
#define P11_00c81494 (*(int32_t *)re_gvar(0x00c81494u, sizeof(int32_t), (void *)&P11_00c81494))
#undef P11_00ba52d0
#define P11_00ba52d0 (*(int32_t *)re_gvar(0x00ba52d0u, sizeof(int32_t), (void *)&P11_00ba52d0))
#undef P11_00b31efc
#define P11_00b31efc (*(int32_t *)re_gvar(0x00b31efcu, sizeof(int32_t), (void *)&P11_00b31efc))
#undef P11_00c823d0
#define P11_00c823d0 (*(int32_t *)re_gvar(0x00c823d0u, sizeof(int32_t), (void *)&P11_00c823d0))
#undef P11_00d11934
#define P11_00d11934 (*(int32_t *)re_gvar(0x00d11934u, sizeof(int32_t), (void *)&P11_00d11934))
#undef P11_00b5a734
#define P11_00b5a734 (*(int32_t *)re_gvar(0x00b5a734u, sizeof(int32_t), (void *)&P11_00b5a734))
#undef P11_00b5a730
#define P11_00b5a730 (*(int32_t *)re_gvar(0x00b5a730u, sizeof(int32_t), (void *)&P11_00b5a730))
#undef P11_00575554
#define P11_00575554 (*(int32_t *)re_gvar(0x00575554u, sizeof(int32_t), (void *)&P11_00575554))
#undef P11_00575550
#define P11_00575550 (*(int32_t *)re_gvar(0x00575550u, sizeof(int32_t), (void *)&P11_00575550))
#undef P11_00bdc28c
#define P11_00bdc28c (*(int32_t *)re_gvar(0x00bdc28cu, sizeof(int32_t), (void *)&P11_00bdc28c))
#undef P11_005507d0
#define P11_005507d0 (*(int32_t *)re_gvar(0x005507d0u, sizeof(int32_t), (void *)&P11_005507d0))
#undef P11_005507d4
#define P11_005507d4 (*(int32_t *)re_gvar(0x005507d4u, sizeof(int32_t), (void *)&P11_005507d4))
#undef P11_005507d8
#define P11_005507d8 (*(int32_t *)re_gvar(0x005507d8u, sizeof(int32_t), (void *)&P11_005507d8))
#undef P11_00b5a8e8
#define P11_00b5a8e8 (*(int32_t *)re_gvar(0x00b5a8e8u, sizeof(int32_t), (void *)&P11_00b5a8e8))
#undef P11_00b5a8ec
#define P11_00b5a8ec (*(int32_t *)re_gvar(0x00b5a8ecu, sizeof(int32_t), (void *)&P11_00b5a8ec))
#undef P11_01270c38
#define P11_01270c38 (*(int32_t *)re_gvar(0x01270c38u, sizeof(int32_t), (void *)&P11_01270c38))
#undef P11_00575ef8
#define P11_00575ef8 (*(int32_t *)re_gvar(0x00575ef8u, sizeof(int32_t), (void *)&P11_00575ef8))
#undef P11_01270c24
#define P11_01270c24 (*(float *)re_gvar(0x01270c24u, sizeof(float), (void *)&P11_01270c24))
#undef P11_01270c28
#define P11_01270c28 (*(float *)re_gvar(0x01270c28u, sizeof(float), (void *)&P11_01270c28))
#undef P11_0125f3e0
#define P11_0125f3e0 (*(float *)re_gvar(0x0125f3e0u, sizeof(float), (void *)&P11_0125f3e0))
#undef P11_0125f3f8
#define P11_0125f3f8 (*(float *)re_gvar(0x0125f3f8u, sizeof(float), (void *)&P11_0125f3f8))
#undef P11_00546028
#define P11_00546028 (*(float *)re_gvar(0x00546028u, sizeof(float), (void *)&P11_00546028))
#undef P11_0054602c
#define P11_0054602c (*(float *)re_gvar(0x0054602cu, sizeof(float), (void *)&P11_0054602c))
#undef P11_0054604c
#define P11_0054604c (*(float *)re_gvar(0x0054604cu, sizeof(float), (void *)&P11_0054604c))
#undef P11_00546054
#define P11_00546054 (*(float *)re_gvar(0x00546054u, sizeof(float), (void *)&P11_00546054))
#undef P11_00546080
#define P11_00546080 (*(float *)re_gvar(0x00546080u, sizeof(float), (void *)&P11_00546080))
#undef P11_00572b40
#define P11_00572b40 (*(p11_u32arr *)re_gvar(0x00572b40u, sizeof(p11_u32arr), (void *)&P11_00572b40))
#undef P11_0057b740
#define P11_0057b740 (*(uint8_t *)re_gvar(0x0057b740u, sizeof(uint8_t), (void *)&P11_0057b740))
#undef P11_005d592e
#define P11_005d592e (*(uint8_t *)re_gvar(0x005d592eu, sizeof(uint8_t), (void *)&P11_005d592e))
#undef P11_005d57ae
#define P11_005d57ae (*(uint8_t *)re_gvar(0x005d57aeu, sizeof(uint8_t), (void *)&P11_005d57ae))
#undef P11_0125f420
#define P11_0125f420 (*(p11_slots_t *)re_gvar(0x0125f420u, sizeof(p11_slots_t), (void *)&P11_0125f420))
#undef P11_00bf1c40
#define P11_00bf1c40 (*(p11_big_t *)re_gvar(0x00bf1c40u, sizeof(p11_big_t), (void *)&P11_00bf1c40))
#undef P11_00c1ed80
#define P11_00c1ed80 (*(p11_big_t *)re_gvar(0x00c1ed80u, sizeof(p11_big_t), (void *)&P11_00c1ed80))
#undef P11_00c12c60
#define P11_00c12c60 (*(p11_big_t *)re_gvar(0x00c12c60u, sizeof(p11_big_t), (void *)&P11_00c12c60))
#undef P11_00c1cd20
#define P11_00c1cd20 (*(p11_big_t *)re_gvar(0x00c1cd20u, sizeof(p11_big_t), (void *)&P11_00c1cd20))
#undef P11_00c80c60
#define P11_00c80c60 (*(uint8_t *)re_gvar(0x00c80c60u, sizeof(uint8_t), (void *)&P11_00c80c60))
#undef P11_00552e18
#define P11_00552e18 (*(uint8_t *)re_gvar(0x00552e18u, sizeof(uint8_t), (void *)&P11_00552e18))
#undef P11_00579710
#define P11_00579710 (*(uint8_t *)re_gvar(0x00579710u, sizeof(uint8_t), (void *)&P11_00579710))
#undef P11_00b94280
#define P11_00b94280 (*(uint8_t *)re_gvar(0x00b94280u, sizeof(uint8_t), (void *)&P11_00b94280))
#undef P11_00b98280
#define P11_00b98280 (*(uint8_t *)re_gvar(0x00b98280u, sizeof(uint8_t), (void *)&P11_00b98280))
#undef P11_011f4080
#define P11_011f4080 (*(uint8_t *)re_gvar(0x011f4080u, sizeof(uint8_t), (void *)&P11_011f4080))
#undef P11_00b1c268
#define P11_00b1c268 (*(uint8_t *)re_gvar(0x00b1c268u, sizeof(uint8_t), (void *)&P11_00b1c268))
#undef P11_011effa0
#define P11_011effa0 (*(uint8_t *)re_gvar(0x011effa0u, sizeof(uint8_t), (void *)&P11_011effa0))
#endif
/* gvar-img v2.03 end */
/* v2.35: 00bdc28c — one object: the native pointer P44_MatPtr (current transform for P44_Xform*); P11_00bdc28c is a
   read-only view (its 32-bit address).  The image cell is no longer used. */
#if !defined(RE_HOOK_BUILD) && !defined(RE_GVAR_PLAIN)
#include "reptr.h"
extern float *P44_MatPtr;
#undef P11_00bdc28c
#define P11_00bdc28c ((int32_t)re_addr_known(P44_MatPtr))
#endif
