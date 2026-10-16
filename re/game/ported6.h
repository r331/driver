/* Партия v0.41 */
#pragma once
#include "menutab.h"
#include "ported5.h"
#include "smallfuncs.h"
#include <string.h>
typedef void (*FnV1)(int32_t);
typedef void (*FnV2)(int32_t, int32_t);
typedef int32_t (*FnI1)(int32_t);
typedef uint8_t g6a_01145A60[0x400];
typedef uint8_t g6a_00549F84[0x400];
typedef uint8_t g6a_0054A25C[0x400];
typedef uint8_t g6a_0054DBCC[0x260];  /* v1.48: до конца таблицы меню 0054de2c (прежде 0x400) */
typedef uint8_t g6a_0054E56C[0x400];
typedef uint8_t g6a_0054E834[0x400];
typedef uint8_t g6a_00562B70[0x100];
typedef uint8_t *g6a_00B2F30C[256];
typedef int32_t g6a_00B91BC4[16];
typedef uint32_t g6a_00C5678C[0x200];
typedef int32_t g6a_00C594A0[0x40];
typedef uint8_t g6a_00D04A50[0x100];
#define G6_011368C4 GAME_VAR(int32_t, G6_011368C4, 0x011368c4)
#ifndef RE_HOOK_BUILD
extern int32_t G6_011368C4;
#endif
#define G6_01136920 GAME_VAR(int32_t, G6_01136920, 0x01136920)
#ifndef RE_HOOK_BUILD
extern int32_t G6_01136920;
#endif
#define G6_01145A60 GAME_VAR(g6a_01145A60, G6_01145A60, 0x01145a60)
#ifndef RE_HOOK_BUILD
extern g6a_01145A60 G6_01145A60;
#endif
#define G6_0125F3F0 GAME_VAR(int32_t, G6_0125F3F0, 0x0125f3f0)
#ifndef RE_HOOK_BUILD
extern int32_t G6_0125F3F0;
#endif
#define G6_01270C28 GAME_VAR(int32_t, G6_01270C28, 0x01270c28)
#ifndef RE_HOOK_BUILD
extern int32_t G6_01270C28;
#endif
#define G6_01270C34 GAME_VAR(int32_t, G6_01270C34, 0x01270c34)
#ifndef RE_HOOK_BUILD
extern int32_t G6_01270C34;
#endif
#define G6_01270D20 GAME_VAR(FnI1, G6_01270D20, 0x01270d20)
#ifndef RE_HOOK_BUILD
extern FnI1 G6_01270D20;
#endif
#define G6_01270D28 GAME_VAR(FnV1, G6_01270D28, 0x01270d28)
#ifndef RE_HOOK_BUILD
extern FnV1 G6_01270D28;
#endif
#define G6_01270DE4 GAME_VAR(FnV1, G6_01270DE4, 0x01270de4)
#ifndef RE_HOOK_BUILD
extern FnV1 G6_01270DE4;
#endif
#define G6_00549F84 GAME_VAR(g6a_00549F84, G6_00549F84, 0x00549f84)
#ifndef RE_HOOK_BUILD
extern g6a_00549F84 G6_00549F84;
#endif
#define G6_0054A25C GAME_VAR(g6a_0054A25C, G6_0054A25C, 0x0054a25c)
#ifndef RE_HOOK_BUILD
extern g6a_0054A25C G6_0054A25C;
#endif
#define G6_0054DBCC MENUTAB_VAR(g6a_0054DBCC, G6_0054DBCC, 0x0054dbcc)
#define G6_0054E56C GAME_VAR(g6a_0054E56C, G6_0054E56C, 0x0054e56c)
#ifndef RE_HOOK_BUILD
extern g6a_0054E56C G6_0054E56C;
#endif
#define G6_0054E834 GAME_VAR(g6a_0054E834, G6_0054E834, 0x0054e834)
#ifndef RE_HOOK_BUILD
extern g6a_0054E834 G6_0054E834;
#endif
#define G6_0054EF2C GAME_VAR(int32_t, G6_0054EF2C, 0x0054ef2c)
#ifndef RE_HOOK_BUILD
extern int32_t G6_0054EF2C;
#endif
#define G6_005624A0 GAME_VAR(int32_t, G6_005624A0, 0x005624a0)
#ifndef RE_HOOK_BUILD
extern int32_t G6_005624A0;
#endif
#define G6_00562B70 GAME_VAR(g6a_00562B70, G6_00562B70, 0x00562b70)
#ifndef RE_HOOK_BUILD
extern g6a_00562B70 G6_00562B70;
#endif
#define G6_005755C8 GAME_VAR(int32_t, G6_005755C8, 0x005755c8)
#ifndef RE_HOOK_BUILD
extern int32_t G6_005755C8;
#endif
#define G6_00575A70 GAME_VAR(int32_t, G6_00575A70, 0x00575a70)
#ifndef RE_HOOK_BUILD
extern int32_t G6_00575A70;
#endif
#define G6_00575EBC GAME_VAR(int32_t, G6_00575EBC, 0x00575ebc)
#ifndef RE_HOOK_BUILD
extern int32_t G6_00575EBC;
#endif
#define G6_00575EC0 GAME_VAR(int32_t, G6_00575EC0, 0x00575ec0)
#ifndef RE_HOOK_BUILD
extern int32_t G6_00575EC0;
#endif
#define G6_00575EEC GAME_VAR(int32_t, G6_00575EEC, 0x00575eec)
#ifndef RE_HOOK_BUILD
extern int32_t G6_00575EEC;
#endif
#define G6_00575EF4 GAME_VAR(int32_t, G6_00575EF4, 0x00575ef4)
#ifndef RE_HOOK_BUILD
extern int32_t G6_00575EF4;
#endif
#define G6_00575F00 GAME_VAR(int32_t, G6_00575F00, 0x00575f00)
#ifndef RE_HOOK_BUILD
extern int32_t G6_00575F00;
#endif
#define G6_00575F04 GAME_VAR(int32_t, G6_00575F04, 0x00575f04)
#ifndef RE_HOOK_BUILD
extern int32_t G6_00575F04;
#endif
#define G6_00575F20 GAME_VAR(int32_t, G6_00575F20, 0x00575f20)
#ifndef RE_HOOK_BUILD
extern int32_t G6_00575F20;
#endif
#define G6_00575F34 GAME_VAR(int32_t, G6_00575F34, 0x00575f34)
#ifndef RE_HOOK_BUILD
extern int32_t G6_00575F34;
#endif
#define G6_00575F38 GAME_VAR(int32_t, G6_00575F38, 0x00575f38)
#ifndef RE_HOOK_BUILD
extern int32_t G6_00575F38;
#endif
#define G6_0057B728 GAME_VAR(int32_t, G6_0057B728, 0x0057b728)
#ifndef RE_HOOK_BUILD
extern int32_t G6_0057B728;
#endif
#define G6_005D5788 GAME_VAR(int32_t, G6_005D5788, 0x005d5788)
#ifndef RE_HOOK_BUILD
extern int32_t G6_005D5788;
#endif
#define G6_005FE9BC GAME_VAR(int32_t, G6_005FE9BC, 0x005fe9bc)
#ifndef RE_HOOK_BUILD
extern int32_t G6_005FE9BC;
#endif
#define G6_005FE9CC GAME_VAR(int32_t, G6_005FE9CC, 0x005fe9cc)
#ifndef RE_HOOK_BUILD
extern int32_t G6_005FE9CC;
#endif
#define G6_005FEA7C GAME_VAR(int32_t, G6_005FEA7C, 0x005fea7c)
#ifndef RE_HOOK_BUILD
extern int32_t G6_005FEA7C;
#endif
#define G6_005FED9C GAME_VAR(int32_t, G6_005FED9C, 0x005fed9c)
#ifndef RE_HOOK_BUILD
extern int32_t G6_005FED9C;
#endif
#define G6_00A421F0 GAME_VAR(int32_t, G6_00A421F0, 0x00a421f0)
#ifndef RE_HOOK_BUILD
extern int32_t G6_00A421F0;
#endif
#define G6_00B1C224 GAME_VAR(int32_t, G6_00B1C224, 0x00b1c224)
#ifndef RE_HOOK_BUILD
extern int32_t G6_00B1C224;
#endif
#define G6_00B20364 GAME_VAR(int32_t, G6_00B20364, 0x00b20364)
#ifndef RE_HOOK_BUILD
extern int32_t G6_00B20364;
#endif
#define G6_00B20368 GAME_VAR(int32_t, G6_00B20368, 0x00b20368)
#ifndef RE_HOOK_BUILD
extern int32_t G6_00B20368;
#endif
#define G6_00B2F30C GAME_VAR(g6a_00B2F30C, G6_00B2F30C, 0x00b2f30c)
#ifndef RE_HOOK_BUILD
extern g6a_00B2F30C G6_00B2F30C;
#endif
#define G6_00B31F40 GAME_VAR(int32_t, G6_00B31F40, 0x00b31f40)
#ifndef RE_HOOK_BUILD
extern int32_t G6_00B31F40;
#endif
#define G6_00B5A778 GAME_VAR(int32_t, G6_00B5A778, 0x00b5a778)
#ifndef RE_HOOK_BUILD
extern int32_t G6_00B5A778;
#endif
#define G6_00B5A838 GAME_VAR(uint8_t, G6_00B5A838, 0x00b5a838)
#ifndef RE_HOOK_BUILD
extern uint8_t G6_00B5A838;
#endif
#define G6_00B5A839 GAME_VAR(uint8_t, G6_00B5A839, 0x00b5a839)
#ifndef RE_HOOK_BUILD
extern uint8_t G6_00B5A839;
#endif
#define G6_00B5A83A GAME_VAR(uint8_t, G6_00B5A83A, 0x00b5a83a)
#ifndef RE_HOOK_BUILD
extern uint8_t G6_00B5A83A;
#endif
#define G6_00B5A83C GAME_VAR(void*, G6_00B5A83C, 0x00b5a83c)
#ifndef RE_HOOK_BUILD
extern void* G6_00B5A83C;
#endif
#define G6_00B5A840 GAME_VAR(void*, G6_00B5A840, 0x00b5a840)
#ifndef RE_HOOK_BUILD
extern void* G6_00B5A840;
#endif
#define G6_00B5A8A0 GAME_VAR(int32_t, G6_00B5A8A0, 0x00b5a8a0)
#ifndef RE_HOOK_BUILD
extern int32_t G6_00B5A8A0;
#endif
#define G6_00B5A8AC GAME_VAR(int32_t, G6_00B5A8AC, 0x00b5a8ac)
#ifndef RE_HOOK_BUILD
extern int32_t G6_00B5A8AC;
#endif
#define G6_00B5A8B0 GAME_VAR(int32_t, G6_00B5A8B0, 0x00b5a8b0)
#ifndef RE_HOOK_BUILD
extern int32_t G6_00B5A8B0;
#endif
#define G6_00B87E20 GAME_VAR(int32_t, G6_00B87E20, 0x00b87e20)
#ifndef RE_HOOK_BUILD
extern int32_t G6_00B87E20;
#endif
#define G6_00B87E50 GAME_VAR(int32_t, G6_00B87E50, 0x00b87e50)
#ifndef RE_HOOK_BUILD
extern int32_t G6_00B87E50;
#endif
#define G6_00B87E74 GAME_VAR(int32_t, G6_00B87E74, 0x00b87e74)
#ifndef RE_HOOK_BUILD
extern int32_t G6_00B87E74;
#endif
#define G6_00B87EA0 GAME_VAR(int32_t, G6_00B87EA0, 0x00b87ea0)
#ifndef RE_HOOK_BUILD
extern int32_t G6_00B87EA0;
#endif
#define G6_00B87EAC GAME_VAR(int32_t, G6_00B87EAC, 0x00b87eac)
#ifndef RE_HOOK_BUILD
extern int32_t G6_00B87EAC;
#endif
#define G6_00B87EB0 GAME_VAR(int32_t, G6_00B87EB0, 0x00b87eb0)
#ifndef RE_HOOK_BUILD
extern int32_t G6_00B87EB0;
#endif
#define G6_00B87EEC GAME_VAR(int32_t, G6_00B87EEC, 0x00b87eec)
#ifndef RE_HOOK_BUILD
extern int32_t G6_00B87EEC;
#endif
#define G6_00B87EFC GAME_VAR(int32_t, G6_00B87EFC, 0x00b87efc)
#ifndef RE_HOOK_BUILD
extern int32_t G6_00B87EFC;
#endif
#define G6_00B91BC4 GAME_VAR(g6a_00B91BC4, G6_00B91BC4, 0x00b91bc4)
#ifndef RE_HOOK_BUILD
extern g6a_00B91BC4 G6_00B91BC4;
#endif
#define G6_00B91CF4 GAME_VAR(int32_t, G6_00B91CF4, 0x00b91cf4)
#ifndef RE_HOOK_BUILD
extern int32_t G6_00B91CF4;
#endif
#define G6_00B91D2C GAME_VAR(int32_t, G6_00B91D2C, 0x00b91d2c)
#ifndef RE_HOOK_BUILD
extern int32_t G6_00B91D2C;
#endif
#define G6_00B91D34 GAME_VAR(int32_t, G6_00B91D34, 0x00b91d34)
#ifndef RE_HOOK_BUILD
extern int32_t G6_00B91D34;
#endif
#define G6_00BDCB14 GAME_VAR(FnV2, G6_00BDCB14, 0x00bdcb14)
#ifndef RE_HOOK_BUILD
extern FnV2 G6_00BDCB14;
#endif
#define G6_00BDCB18 GAME_VAR(FnV1, G6_00BDCB18, 0x00bdcb18)
#ifndef RE_HOOK_BUILD
extern FnV1 G6_00BDCB18;
#endif
#define G6_00BDCB20 GAME_VAR(FnV1, G6_00BDCB20, 0x00bdcb20)
#ifndef RE_HOOK_BUILD
extern FnV1 G6_00BDCB20;
#endif
#define G6_00BDF9C0 GAME_VAR(int32_t, G6_00BDF9C0, 0x00bdf9c0)
#ifndef RE_HOOK_BUILD
extern int32_t G6_00BDF9C0;
#endif
#define G6_00BDF9C4 GAME_VAR(int32_t, G6_00BDF9C4, 0x00bdf9c4)
#ifndef RE_HOOK_BUILD
extern int32_t G6_00BDF9C4;
#endif
#define G6_00C557F8 GAME_VAR(int32_t, G6_00C557F8, 0x00c557f8)
#ifndef RE_HOOK_BUILD
extern int32_t G6_00C557F8;
#endif
#define G6_00C55800 GAME_VAR(int32_t, G6_00C55800, 0x00c55800)
#ifndef RE_HOOK_BUILD
extern int32_t G6_00C55800;
#endif
/* v1.48: пул частиц 00c56780 (0x40 × 0xb4) в native — только A_00C56780; счётчик свободных 00c56764 — P43_FreeCnt,
   список свободных 00c594a0 — P43_FreeList (G6_/P12_ — макросы над ними) */
#ifdef RE_HOOK_BUILD
#define G6_00C56764 GAME_VAR(int32_t, G6_00C56764, 0x00c56764)
#define G6_00C5678C GAME_VAR(g6a_00C5678C, G6_00C5678C, 0x00c5678c)
#define G6_00C594A0 GAME_VAR(g6a_00C594A0, G6_00C594A0, 0x00c594a0)
#else
extern uint8_t A_00C56780[]; extern int32_t P43_FreeCnt; extern int32_t P43_FreeList[];
#define G6_00C56764 P43_FreeCnt
#define G6_00C5678C (*(g6a_00C5678C *)(A_00C56780 + 0xc))
#define G6_00C594A0 (*(g6a_00C594A0 *)P43_FreeList)
#endif
#define G6_00C80C50 GAME_VAR(void*, G6_00C80C50, 0x00c80c50)
#ifndef RE_HOOK_BUILD
extern void* G6_00C80C50;
#endif
#define G6_00C81108 GAME_VAR(int32_t, G6_00C81108, 0x00c81108)
#ifndef RE_HOOK_BUILD
extern int32_t G6_00C81108;
#endif
#define G6_00CE0F20 GAME_VAR(void*, G6_00CE0F20, 0x00ce0f20)
#ifndef RE_HOOK_BUILD
extern void* G6_00CE0F20;
#endif
#define G6_00D00208 GAME_VAR(void*, G6_00D00208, 0x00d00208)
#ifndef RE_HOOK_BUILD
extern void* G6_00D00208;
#endif
#define G6_00D01268 GAME_VAR(void*, G6_00D01268, 0x00d01268)
#ifndef RE_HOOK_BUILD
extern void* G6_00D01268;
#endif
#define G6_00D04A50 GAME_VAR(g6a_00D04A50, G6_00D04A50, 0x00d04a50)
#ifndef RE_HOOK_BUILD
extern g6a_00D04A50 G6_00D04A50;
#endif
#define G6_00D0DDC0 GAME_VAR(int32_t, G6_00D0DDC0, 0x00d0ddc0)
#ifndef RE_HOOK_BUILD
extern int32_t G6_00D0DDC0;
#endif
#define G6_00D10E40 GAME_VAR(uint32_t, G6_00D10E40, 0x00d10e40)
#ifndef RE_HOOK_BUILD
extern uint32_t G6_00D10E40;
#endif
#define G6_00D117A4 GAME_VAR(int32_t, G6_00D117A4, 0x00d117a4)
#ifndef RE_HOOK_BUILD
extern int32_t G6_00D117A4;
#endif
#define G6_00D117A8 GAME_VAR(int32_t, G6_00D117A8, 0x00d117a8)
#ifndef RE_HOOK_BUILD
extern int32_t G6_00D117A8;
#endif
#define G6_00D11800 GAME_VAR(uint32_t, G6_00D11800, 0x00d11800)
#ifndef RE_HOOK_BUILD
extern uint32_t G6_00D11800;
#endif
#define G6_00D11880 GAME_VAR(int32_t, G6_00D11880, 0x00d11880)
#ifndef RE_HOOK_BUILD
extern int32_t G6_00D11880;
#endif
#define G6_00D11928 GAME_VAR(int32_t, G6_00D11928, 0x00d11928)
#ifndef RE_HOOK_BUILD
extern int32_t G6_00D11928;
#endif
void MenuRed0040766D(void);
void MenuWhite004076E2(void);
void MenuRed00409C85(void);
void MenuWhite00409CFA(void);
void MenuRed00415904(void);
void MenuWhite00415979(void);
void MenuRed00419D3E(void);
void MenuWhite00419DB3(void);
void MenuWhite0041AF29(int32_t i);
void MenuMark00412228(void);
int32_t MenuToggle00408994(void);
int32_t MenuToggle00408C37(void);
int32_t MenuToggle00409142(void);
int32_t MenuToggle0050FE26(void);
int32_t MenuToggle0050FEE5(void);
int32_t MenuToggle00510028(void);
int32_t MenuTri0040E9B5(void);
int32_t MenuTri00419C8C(void);
int32_t MenuQuality004088DB(void);
int32_t MenuQuality0050FA70(void);
void SoundSetFormat005235D3(int32_t a, int32_t b);
void SoundSetVolA005235F2(int32_t a);
void SoundSetVolB0052360D(int32_t a);
int32_t MenuBits0041556C(void);
int32_t MenuRate00415623(void);
int32_t MenuSoundCh004156DD(void);
void MenuBits0050F8F2(void);
void MenuRate0050F930(void);
void MenuSoundCh0050F971(void);
void MenuSound0050F781(void);
void MenuMusic0050F8A2(void);
void MenuMusic0050F8CC(void);
int32_t MenuAnyFlag00413DF3(void);
void MenuBtn00414264(int32_t p);
void MenuBtn00414376(int32_t p);
void MenuBtn00414488(int32_t p);
void MenuBtn0041459A(int32_t p);
void SetFade0051707A(uint8_t r, uint8_t g, uint8_t b, int32_t d);
void MenuPageNext00417F59(void);
void MenuPagePrev00417FAC(void);
int32_t PoolAlloc004A2C12(void);
int32_t PoolNext004AC671(void);
int32_t PoolAlloc0051210C(void);
void ShutdownAudio004183A3(void);
void MenuBack005103EC(void);
void SoundMenuIn00419814(void);
void SoundMenuOut0051082A(void);
void SoundMenuSave0051080E(void);
int32_t DrvCall004246D1(int32_t a);
int32_t DrvSetMode0042655A(int32_t a);
void ClearHandles005223BE(void);
void StartAudio005233A0(void);
void NoopFn00528455(void);
void InitSubsys004BA443(void);
void Fwd004D2D9F(int32_t a, int32_t b, int32_t c, int32_t d);
void Reset004D600B(void);
void MenuAddItem004DC8B0(uint8_t *item, int32_t flag);
int32_t StepToward004E60C1(int32_t i);
uint32_t AngleToDir00514103(uint32_t a);
void ObjInit00514C43(uint8_t *o, uint16_t a, uint32_t b, uint32_t flags);
int32_t TypeIsKnown00514F0A(const int16_t *p);
void VecAdd3_00526F7E(float *a, const float *b);
void VecNeg4_00527123(float *a);
void VecAdd4_0052715E(const float *a, const float *b, float *r);
void VecSub4_005271A8(const float *a, const float *b, float *r);
void MatIdentity3_0052614F(float *m);
void CreditsTick005193D4(void);
int32_t CreditsNext00519D2C(void);
int32_t CreditsPrev00519D70(void);
void ResetPalette00519DF3(void);
void MenuClick004F8ACC(int32_t a);
void DrawTextLine004FBBC5(int32_t t);
void FreeBuf004FC57B(void);
void FreeMapBufs004ECE1A(void);
void FreeBufs00516E2E(void);
void Update005012A3(void);
void ActorStep00494678(uint8_t *p);
int32_t StartFlyby004A05C0(void);
void Dispatch0048A68E(int32_t i);
void Dispatch0041D50E(int32_t a, int32_t b, int32_t c, int32_t d);
int32_t Fwd0042482B(int32_t a, int32_t b, int32_t c, int32_t d);
int32_t SoundGetPos005242A7(int32_t i);
void SoundSetPos00523F8A(int32_t i, int32_t v);
void SoundPlay00523E50(uint32_t id, int32_t b, int32_t c);
void Mask004D9028(uint32_t a, uint32_t b);
void CursorWrap004D9478(void);
void CursorSet004D94B7(int32_t a, int32_t b);
