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
extern int32_t G2_00D11A5C;
#endif
#define G2_00B20358 GAME_VAR(int32_t, G2_00B20358, 0x00b20358)
#ifndef RE_HOOK_BUILD
extern int32_t G2_00B20358;
#endif
#define G2_00B20354 GAME_VAR(int32_t, G2_00B20354, 0x00b20354)
#ifndef RE_HOOK_BUILD
extern int32_t G2_00B20354;
#endif
#define G2_00B20380 GAME_VAR(int32_t, G2_00B20380, 0x00b20380)
#ifndef RE_HOOK_BUILD
extern int32_t G2_00B20380;
#endif
#define G2_00B2C3A4 GAME_VAR(int32_t, G2_00B2C3A4, 0x00b2c3a4)
#ifndef RE_HOOK_BUILD
extern int32_t G2_00B2C3A4;
#endif
#define G2_00B20398 GAME_VAR(int32_t, G2_00B20398, 0x00b20398)
#ifndef RE_HOOK_BUILD
extern int32_t G2_00B20398;
#endif
#define G2_00B20394 GAME_VAR(int32_t, G2_00B20394, 0x00b20394)
#ifndef RE_HOOK_BUILD
extern int32_t G2_00B20394;
#endif
#define G2_00D04654 GAME_VAR(int32_t, G2_00D04654, 0x00d04654)
#ifndef RE_HOOK_BUILD
extern int32_t G2_00D04654;
#endif
#define G2_01137324 GAME_VAR(int32_t, G2_01137324, 0x01137324)
#ifndef RE_HOOK_BUILD
extern int32_t G2_01137324;
#endif
#define G2_00C54EC0 GAME_VAR(int32_t, G2_00C54EC0, 0x00c54ec0)
#ifndef RE_HOOK_BUILD
extern int32_t G2_00C54EC0;
#endif
#define G2_00D044C8 GAME_VAR(int32_t, G2_00D044C8, 0x00d044c8)
#ifndef RE_HOOK_BUILD
extern int32_t G2_00D044C8;
#endif
#define G2_00D118A8 GAME_VAR(int32_t, G2_00D118A8, 0x00d118a8)
#ifndef RE_HOOK_BUILD
extern int32_t G2_00D118A8;
#endif
#define G2_01143600 GAME_VAR(int32_t, G2_01143600, 0x01143600)
#ifndef RE_HOOK_BUILD
extern int32_t G2_01143600;
#endif
#define G2_00575EE4 GAME_VAR(int32_t, G2_00575EE4, 0x00575ee4)
#ifndef RE_HOOK_BUILD
extern int32_t G2_00575EE4;
#endif
#define G2_01134120 GAME_VAR(int32_t, G2_01134120, 0x01134120)
#ifndef RE_HOOK_BUILD
extern int32_t G2_01134120;
#endif
#define G2_011F43B0 GAME_VAR(int32_t, G2_011F43B0, 0x011f43b0)
#ifndef RE_HOOK_BUILD
extern int32_t G2_011F43B0;
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
extern g2_ints_t G2_TABLE_00550ACC;
extern g2_ints_t G2_ARR_01145940;
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
