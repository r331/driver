/* Мелкие функции, партия 2. */
#pragma once
#include "gvar.h"
#include "smallfuncs.h"
typedef struct { int32_t v; int32_t pad; } g2_pair_t[2];
typedef struct { int32_t v; int32_t pad[2]; } g2_slot_t[0x1000];
typedef int32_t g2_ints_t[0x1000];
typedef struct { float a,b,c,d,e,f,g,h,i; } g2_cam_t;
#define G2_ScriptStack GAME_VAR(int32_t*, G2_ScriptStack, 0x00d17af8)
#ifndef RE_HOOK_BUILD
extern int32_t* G2_ScriptStack;
#endif
#define G2_00D11A5C GAME_VAR(int32_t, G2_00D11A5C, 0x00d11a5c)
#ifndef RE_HOOK_BUILD
#pragma push_macro("G2_00D11A5C") /*gvi*/
#undef G2_00D11A5C /*gvi*/
extern int32_t G2_00D11A5C;
#pragma pop_macro("G2_00D11A5C") /*gvi*/
#endif
#define G2_00B20358 GAME_VAR(int32_t, G2_00B20358, 0x00b20358)
#ifndef RE_HOOK_BUILD
#pragma push_macro("G2_00B20358") /*gvi*/
#undef G2_00B20358 /*gvi*/
extern int32_t G2_00B20358;
#pragma pop_macro("G2_00B20358") /*gvi*/
#endif
#define G2_00B20354 GAME_VAR(int32_t, G2_00B20354, 0x00b20354)
#ifndef RE_HOOK_BUILD
#pragma push_macro("G2_00B20354") /*gvi*/
#undef G2_00B20354 /*gvi*/
extern int32_t G2_00B20354;
#pragma pop_macro("G2_00B20354") /*gvi*/
#endif
#define G2_00B20380 GAME_VAR(int32_t, G2_00B20380, 0x00b20380)
#ifndef RE_HOOK_BUILD
#pragma push_macro("G2_00B20380") /*gvi*/
#undef G2_00B20380 /*gvi*/
extern int32_t G2_00B20380;
#pragma pop_macro("G2_00B20380") /*gvi*/
#endif
#define G2_00B2C3A4 GAME_VAR(int32_t, G2_00B2C3A4, 0x00b2c3a4)
#ifndef RE_HOOK_BUILD
#pragma push_macro("G2_00B2C3A4") /*gvi*/
#undef G2_00B2C3A4 /*gvi*/
extern int32_t G2_00B2C3A4;
#pragma pop_macro("G2_00B2C3A4") /*gvi*/
#endif
#define G2_00B20398 GAME_VAR(int32_t, G2_00B20398, 0x00b20398)
#ifndef RE_HOOK_BUILD
#pragma push_macro("G2_00B20398") /*gvi*/
#undef G2_00B20398 /*gvi*/
extern int32_t G2_00B20398;
#pragma pop_macro("G2_00B20398") /*gvi*/
#endif
#define G2_00B20394 GAME_VAR(int32_t, G2_00B20394, 0x00b20394)
#ifndef RE_HOOK_BUILD
#pragma push_macro("G2_00B20394") /*gvi*/
#undef G2_00B20394 /*gvi*/
extern int32_t G2_00B20394;
#pragma pop_macro("G2_00B20394") /*gvi*/
#endif
#define G2_00D04654 GAME_VAR(int32_t, G2_00D04654, 0x00d04654)
#ifndef RE_HOOK_BUILD
#pragma push_macro("G2_00D04654") /*gvi*/
#undef G2_00D04654 /*gvi*/
extern int32_t G2_00D04654;
#pragma pop_macro("G2_00D04654") /*gvi*/
#endif
#define G2_01137324 GAME_VAR(int32_t, G2_01137324, 0x01137324)
#ifndef RE_HOOK_BUILD
#pragma push_macro("G2_01137324") /*gvi*/
#undef G2_01137324 /*gvi*/
extern int32_t G2_01137324;
#pragma pop_macro("G2_01137324") /*gvi*/
#endif
#define G2_00C54EC0 GAME_VAR(int32_t, G2_00C54EC0, 0x00c54ec0)
#ifndef RE_HOOK_BUILD
#pragma push_macro("G2_00C54EC0") /*gvi*/
#undef G2_00C54EC0 /*gvi*/
extern int32_t G2_00C54EC0;
#pragma pop_macro("G2_00C54EC0") /*gvi*/
#endif
#define G2_00D044C8 GAME_VAR(int32_t, G2_00D044C8, 0x00d044c8)
#ifndef RE_HOOK_BUILD
#pragma push_macro("G2_00D044C8") /*gvi*/
#undef G2_00D044C8 /*gvi*/
extern int32_t G2_00D044C8;
#pragma pop_macro("G2_00D044C8") /*gvi*/
#endif
#define G2_00D118A8 GAME_VAR(int32_t, G2_00D118A8, 0x00d118a8)
#ifndef RE_HOOK_BUILD
#pragma push_macro("G2_00D118A8") /*gvi*/
#undef G2_00D118A8 /*gvi*/
extern int32_t G2_00D118A8;
#pragma pop_macro("G2_00D118A8") /*gvi*/
#endif
#define G2_01143600 GAME_VAR(int32_t, G2_01143600, 0x01143600)
#ifndef RE_HOOK_BUILD
#pragma push_macro("G2_01143600") /*gvi*/
#undef G2_01143600 /*gvi*/
extern int32_t G2_01143600;
#pragma pop_macro("G2_01143600") /*gvi*/
#endif
#define G2_00575EE4 GAME_VAR(int32_t, G2_00575EE4, 0x00575ee4)
#ifndef RE_HOOK_BUILD
#pragma push_macro("G2_00575EE4") /*gvi*/
#undef G2_00575EE4 /*gvi*/
extern int32_t G2_00575EE4;
#pragma pop_macro("G2_00575EE4") /*gvi*/
#endif
#define G2_01134120 GAME_VAR(int32_t, G2_01134120, 0x01134120)
#ifndef RE_HOOK_BUILD
#pragma push_macro("G2_01134120") /*gvi*/
#undef G2_01134120 /*gvi*/
extern int32_t G2_01134120;
#pragma pop_macro("G2_01134120") /*gvi*/
#endif
#define G2_011F43B0 GAME_VAR(int32_t, G2_011F43B0, 0x011f43b0)
#ifndef RE_HOOK_BUILD
#pragma push_macro("G2_011F43B0") /*gvi*/
#undef G2_011F43B0 /*gvi*/
extern int32_t G2_011F43B0;
#pragma pop_macro("G2_011F43B0") /*gvi*/
#endif
#define G2_011F4064 GAME_VAR(uint8_t*, G2_011F4064, 0x011f4064)
#ifndef RE_HOOK_BUILD
extern uint8_t* G2_011F4064;
#endif
#define G2_005603BC GAME_VAR(g2_pair_t, G2_005603BC, 0x005603bc)
#ifndef RE_HOOK_BUILD
extern g2_pair_t G2_005603BC;
#endif
#define G2_00B203A0 GAME_VAR(g2_slot_t, G2_00B203A0, 0x00b203a0)
#ifndef RE_HOOK_BUILD
extern g2_slot_t G2_00B203A0;
#endif
#define G2_TABLE_00550ACC GAME_VAR(g2_ints_t, G2_TABLE_00550ACC, 0x00550acc)
#define G2_ARR_01145940 GAME_VAR(g2_ints_t, G2_ARR_01145940, 0x01145940)
#ifndef RE_HOOK_BUILD
#pragma push_macro("G2_TABLE_00550ACC") /*gvi*/
#undef G2_TABLE_00550ACC /*gvi*/
extern g2_ints_t G2_TABLE_00550ACC;
#pragma pop_macro("G2_TABLE_00550ACC") /*gvi*/
#pragma push_macro("G2_ARR_01145940") /*gvi*/
#undef G2_ARR_01145940 /*gvi*/
extern g2_ints_t G2_ARR_01145940;
#pragma pop_macro("G2_ARR_01145940") /*gvi*/
#endif
int32_t CountTrailingZeros00421C72(uint32_t v);
int32_t FillTable8_0041D954(int32_t* p);
int32_t ScriptStackPop004CB982(void);
int32_t ScriptStackPop004CB9BA(void);
void ScriptStackPush004CB9F2(int32_t v);
int32_t ScriptSkip16_004D14D8(void);
int32_t AddClamp4095_004D2ADE(int32_t d);
void FillRange004D2B16(uint16_t* p);
void ClearPair004D6D68(void);
void ClearSlots004D8C23(void);
void SetMode2_004E612A(void);
int32_t PopIndex00493E9B(void);
char* SkipLine004A59C6(char* p);
void NegateCamZ004EAF8D(void);
void AdvanceOpPtr0042F7B8(void);
typedef g2_cam_t g2_camarr_t[256];
#define G2_011F40E0 GAME_VAR(g2_camarr_t, G2_011F40E0, 0x011f40e0)
#ifndef RE_HOOK_BUILD
extern g2_camarr_t G2_011F40E0;
#endif
/* gvar-img v2.03 begin (tools/gen_gvar_img.py) */
#if !defined(RE_HOOK_BUILD) && !defined(RE_GVAR_PLAIN)
#undef G2_00D11A5C
#define G2_00D11A5C (*(int32_t *)re_gvar(0x00d11a5cu, sizeof(int32_t), (void *)&G2_00D11A5C))
#undef G2_00B20358
#define G2_00B20358 (*(int32_t *)re_gvar(0x00b20358u, sizeof(int32_t), (void *)&G2_00B20358))
#undef G2_00B20354
#define G2_00B20354 (*(int32_t *)re_gvar(0x00b20354u, sizeof(int32_t), (void *)&G2_00B20354))
#undef G2_00B20380
#define G2_00B20380 (*(int32_t *)re_gvar(0x00b20380u, sizeof(int32_t), (void *)&G2_00B20380))
#undef G2_00B2C3A4
#define G2_00B2C3A4 (*(int32_t *)re_gvar(0x00b2c3a4u, sizeof(int32_t), (void *)&G2_00B2C3A4))
#undef G2_00B20398
#define G2_00B20398 (*(int32_t *)re_gvar(0x00b20398u, sizeof(int32_t), (void *)&G2_00B20398))
#undef G2_00B20394
#define G2_00B20394 (*(int32_t *)re_gvar(0x00b20394u, sizeof(int32_t), (void *)&G2_00B20394))
#undef G2_00D04654
#define G2_00D04654 (*(int32_t *)re_gvar(0x00d04654u, sizeof(int32_t), (void *)&G2_00D04654))
#undef G2_01137324
#define G2_01137324 (*(int32_t *)re_gvar(0x01137324u, sizeof(int32_t), (void *)&G2_01137324))
#undef G2_00C54EC0
#define G2_00C54EC0 (*(int32_t *)re_gvar(0x00c54ec0u, sizeof(int32_t), (void *)&G2_00C54EC0))
#undef G2_00D044C8
#define G2_00D044C8 (*(int32_t *)re_gvar(0x00d044c8u, sizeof(int32_t), (void *)&G2_00D044C8))
#undef G2_00D118A8
#define G2_00D118A8 (*(int32_t *)re_gvar(0x00d118a8u, sizeof(int32_t), (void *)&G2_00D118A8))
#undef G2_01143600
#define G2_01143600 (*(int32_t *)re_gvar(0x01143600u, sizeof(int32_t), (void *)&G2_01143600))
#undef G2_00575EE4
#define G2_00575EE4 (*(int32_t *)re_gvar(0x00575ee4u, sizeof(int32_t), (void *)&G2_00575EE4))
#undef G2_01134120
#define G2_01134120 (*(int32_t *)re_gvar(0x01134120u, sizeof(int32_t), (void *)&G2_01134120))
#undef G2_011F43B0
#define G2_011F43B0 (*(int32_t *)re_gvar(0x011f43b0u, sizeof(int32_t), (void *)&G2_011F43B0))
#undef G2_TABLE_00550ACC
#define G2_TABLE_00550ACC (*(g2_ints_t *)re_gvar(0x00550accu, sizeof(g2_ints_t), (void *)&G2_TABLE_00550ACC))
#undef G2_ARR_01145940
#define G2_ARR_01145940 (*(g2_ints_t *)re_gvar(0x01145940u, sizeof(g2_ints_t), (void *)&G2_ARR_01145940))
#endif
/* gvar-img v2.03 end */
