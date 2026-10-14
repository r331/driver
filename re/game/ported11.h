#pragma once
#include "gvar.h"
#include "unported.h"
#include "menustate.h"
#include "ported10.h"
#include <stdint.h>
#include <string.h>
#include <math.h>
/* Партия v0.45 */
typedef int16_t p11_s16arr[0x8000];
typedef uint32_t p11_u32arr[0x400];
#ifdef RE_HOOK_BUILD
#  define ADDR(x) ((uint32_t)(uintptr_t)&(x))
#else
#  define ADDR(x) ((uint32_t)(uintptr_t)&(x))
#endif
#define P11_00b87e7c GAME_VAR(int32_t, P11_00b87e7c, 0x00b87e7c)
#ifndef RE_HOOK_BUILD
extern int32_t P11_00b87e7c;
#endif
#define P11_005c6760 GAME_VAR(int32_t, P11_005c6760, 0x005c6760)
#ifndef RE_HOOK_BUILD
extern int32_t P11_005c6760;
#endif
#define P11_01271060 GAME_VAR(int32_t, P11_01271060, 0x01271060)
#ifndef RE_HOOK_BUILD
extern int32_t P11_01271060;
#endif
#define P11_00b87e38 GAME_VAR(int32_t, P11_00b87e38, 0x00b87e38)
#ifndef RE_HOOK_BUILD
extern int32_t P11_00b87e38;
#endif
#define P11_00b20360 GAME_VAR(int32_t, P11_00b20360, 0x00b20360)
#ifndef RE_HOOK_BUILD
extern int32_t P11_00b20360;
#endif
#define P11_00c81494 GAME_VAR(int32_t, P11_00c81494, 0x00c81494)
#ifndef RE_HOOK_BUILD
extern int32_t P11_00c81494;
#endif
#define P11_00ba52d0 GAME_VAR(int32_t, P11_00ba52d0, 0x00ba52d0)
#ifndef RE_HOOK_BUILD
extern int32_t P11_00ba52d0;
#endif
#define P11_00b31efc GAME_VAR(int32_t, P11_00b31efc, 0x00b31efc)
#ifndef RE_HOOK_BUILD
extern int32_t P11_00b31efc;
#endif
#define P11_00c823d0 GAME_VAR(int32_t, P11_00c823d0, 0x00c823d0)
#ifndef RE_HOOK_BUILD
extern int32_t P11_00c823d0;
#endif
#define P11_00d11934 GAME_VAR(int32_t, P11_00d11934, 0x00d11934)
#ifndef RE_HOOK_BUILD
extern int32_t P11_00d11934;
#endif
#define P11_00b5a734 GAME_VAR(int32_t, P11_00b5a734, 0x00b5a734)
#ifndef RE_HOOK_BUILD
extern int32_t P11_00b5a734;
#endif
#define P11_00b5a730 GAME_VAR(int32_t, P11_00b5a730, 0x00b5a730)
#ifndef RE_HOOK_BUILD
extern int32_t P11_00b5a730;
#endif
#define P11_00575554 GAME_VAR(int32_t, P11_00575554, 0x00575554)
#ifndef RE_HOOK_BUILD
extern int32_t P11_00575554;
#endif
#define P11_00575550 GAME_VAR(int32_t, P11_00575550, 0x00575550)
#ifndef RE_HOOK_BUILD
extern int32_t P11_00575550;
#endif
#define P11_00bdc28c GAME_VAR(int32_t, P11_00bdc28c, 0x00bdc28c)
#ifndef RE_HOOK_BUILD
extern int32_t P11_00bdc28c;
#endif
#define P11_005507d0 GAME_VAR(int32_t, P11_005507d0, 0x005507d0)
#ifndef RE_HOOK_BUILD
extern int32_t P11_005507d0;
#endif
#define P11_005507d4 GAME_VAR(int32_t, P11_005507d4, 0x005507d4)
#ifndef RE_HOOK_BUILD
extern int32_t P11_005507d4;
#endif
#define P11_005507d8 GAME_VAR(int32_t, P11_005507d8, 0x005507d8)
#ifndef RE_HOOK_BUILD
extern int32_t P11_005507d8;
#endif
#define P11_00b5a8e8 GAME_VAR(int32_t, P11_00b5a8e8, 0x00b5a8e8)
#ifndef RE_HOOK_BUILD
extern int32_t P11_00b5a8e8;
#endif
#define P11_00b5a8ec GAME_VAR(int32_t, P11_00b5a8ec, 0x00b5a8ec)
#ifndef RE_HOOK_BUILD
extern int32_t P11_00b5a8ec;
#endif
#define P11_01270c38 GAME_VAR(int32_t, P11_01270c38, 0x01270c38)
#ifndef RE_HOOK_BUILD
extern int32_t P11_01270c38;
#endif
#define P11_00575ef8 GAME_VAR(int32_t, P11_00575ef8, 0x00575ef8)
#ifndef RE_HOOK_BUILD
extern int32_t P11_00575ef8;
#endif
#define P11_01270c24 GAME_VAR(float, P11_01270c24, 0x01270c24)
#ifndef RE_HOOK_BUILD
extern float P11_01270c24;
#endif
#define P11_01270c28 GAME_VAR(float, P11_01270c28, 0x01270c28)
#ifndef RE_HOOK_BUILD
extern float P11_01270c28;
#endif
#define P11_0125f3e0 GAME_VAR(float, P11_0125f3e0, 0x0125f3e0)
#ifndef RE_HOOK_BUILD
extern float P11_0125f3e0;
#endif
#define P11_0125f3f8 GAME_VAR(float, P11_0125f3f8, 0x0125f3f8)
#ifndef RE_HOOK_BUILD
extern float P11_0125f3f8;
#endif
#define P11_00546028 GAME_VAR(float, P11_00546028, 0x00546028)
#ifndef RE_HOOK_BUILD
extern float P11_00546028;
#endif
#define P11_0054602c GAME_VAR(float, P11_0054602c, 0x0054602c)
#ifndef RE_HOOK_BUILD
extern float P11_0054602c;
#endif
#define P11_0054604c GAME_VAR(float, P11_0054604c, 0x0054604c)
#ifndef RE_HOOK_BUILD
extern float P11_0054604c;
#endif
#define P11_00546054 GAME_VAR(float, P11_00546054, 0x00546054)
#ifndef RE_HOOK_BUILD
extern float P11_00546054;
#endif
#define P11_00546080 GAME_VAR(float, P11_00546080, 0x00546080)
#ifndef RE_HOOK_BUILD
extern float P11_00546080;
#endif
#define P11_00c1ed8a GAME_VAR(p11_s16arr, P11_00c1ed8a, 0x00c1ed8a)
#ifndef RE_HOOK_BUILD
extern p11_s16arr P11_00c1ed8a;
#endif
#define P11_00572b40 GAME_VAR(p11_u32arr, P11_00572b40, 0x00572b40)
#ifndef RE_HOOK_BUILD
extern p11_u32arr P11_00572b40;
#endif
#define P11_0057b740 GAME_VAR(uint8_t, P11_0057b740, 0x0057b740)
#ifndef RE_HOOK_BUILD
extern uint8_t P11_0057b740;
#endif
#define P11_005d592e GAME_VAR(uint8_t, P11_005d592e, 0x005d592e)
#ifndef RE_HOOK_BUILD
extern uint8_t P11_005d592e;
#endif
#define P11_005d57ae GAME_VAR(uint8_t, P11_005d57ae, 0x005d57ae)
#ifndef RE_HOOK_BUILD
extern uint8_t P11_005d57ae;
#endif
#define P11_0125f420 GAME_VAR(uint8_t, P11_0125f420, 0x0125f420)
#ifndef RE_HOOK_BUILD
extern uint8_t P11_0125f420;
#endif
#define P11_00bf1c40 GAME_VAR(uint8_t, P11_00bf1c40, 0x00bf1c40)
#ifndef RE_HOOK_BUILD
extern uint8_t P11_00bf1c40;
#endif
#define P11_00c1ed80 GAME_VAR(uint8_t, P11_00c1ed80, 0x00c1ed80)
#ifndef RE_HOOK_BUILD
extern uint8_t P11_00c1ed80;
#endif
#define P11_00c12c60 GAME_VAR(uint8_t, P11_00c12c60, 0x00c12c60)
#ifndef RE_HOOK_BUILD
extern uint8_t P11_00c12c60;
#endif
#define P11_00c1cd20 GAME_VAR(uint8_t, P11_00c1cd20, 0x00c1cd20)
#ifndef RE_HOOK_BUILD
extern uint8_t P11_00c1cd20;
#endif
#define P11_00c80c60 GAME_VAR(uint8_t, P11_00c80c60, 0x00c80c60)
#ifndef RE_HOOK_BUILD
extern uint8_t P11_00c80c60;
#endif
#define P11_00552e18 GAME_VAR(uint8_t, P11_00552e18, 0x00552e18)
#ifndef RE_HOOK_BUILD
extern uint8_t P11_00552e18;
#endif
#define P11_00579710 GAME_VAR(uint8_t, P11_00579710, 0x00579710)
#ifndef RE_HOOK_BUILD
extern uint8_t P11_00579710;
#endif
#define P11_00b94280 GAME_VAR(uint8_t, P11_00b94280, 0x00b94280)
#ifndef RE_HOOK_BUILD
extern uint8_t P11_00b94280;
#endif
#define P11_00b98280 GAME_VAR(uint8_t, P11_00b98280, 0x00b98280)
#ifndef RE_HOOK_BUILD
extern uint8_t P11_00b98280;
#endif
#define P11_011f4080 GAME_VAR(uint8_t, P11_011f4080, 0x011f4080)
#ifndef RE_HOOK_BUILD
extern uint8_t P11_011f4080;
#endif
#define P11_00b1c268 GAME_VAR(uint8_t, P11_00b1c268, 0x00b1c268)
#ifndef RE_HOOK_BUILD
extern uint8_t P11_00b1c268;
#endif
#define P11_011effa0 GAME_VAR(uint8_t, P11_011effa0, 0x011effa0)
#ifndef RE_HOOK_BUILD
extern uint8_t P11_011effa0;
#endif
#define P11_00575370 GAME_VAR(uint8_t, P11_00575370, 0x00575370)
#ifndef RE_HOOK_BUILD
extern uint8_t P11_00575370;
#endif
#define P11_00574f08 GAME_VAR(uint8_t, P11_00574f08, 0x00574f08)
#ifndef RE_HOOK_BUILD
extern uint8_t P11_00574f08;
#endif
#define P11_00575088 GAME_VAR(uint8_t, P11_00575088, 0x00575088)
#ifndef RE_HOOK_BUILD
extern uint8_t P11_00575088;
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
void ReadBlocks_004EB7CF(uint32_t f);
void ReadTable_004EC466(uint32_t f);
void ReadTable_004EC49A(uint32_t f);
void ReadTable_004EC522(uint32_t f);
void ReadTable_004EC556(uint32_t f);
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
