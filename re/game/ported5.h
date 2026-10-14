/* Партия v0.40 */
#pragma once
#include "gvar.h"
#include "director.h"
#include "directorstorage.h"
#include "dirnodes.h"
#include "globalsets.h"
#include "menuselect.h"
#include "menustate.h"
#include "noop.h"
#include "ported4.h"
#include "smallfuncs.h"
#include "smallfuncs2.h"
#include "uihandlers.h"
#include "uihandlers2.h"
#include "uihandlers3.h"
#include "uihandlers4.h"
#include "widgets.h"
#include "engine.h"
#include "unported.h"
#define Q00546028 GAME_VAR(float, Q00546028, 0x00546028)
#ifndef RE_HOOK_BUILD
extern float Q00546028;
#endif
#define Q0054602C GAME_VAR(float, Q0054602C, 0x0054602c)
#ifndef RE_HOOK_BUILD
extern float Q0054602C;
#endif
#define Q00546030 GAME_VAR(float, Q00546030, 0x00546030)
#ifndef RE_HOOK_BUILD
extern float Q00546030;
#endif
#define Q0054604C GAME_VAR(float, Q0054604C, 0x0054604c)
#ifndef RE_HOOK_BUILD
extern float Q0054604C;
#endif
#define Q00549A34 GAME_VAR(uint32_t, Q00549A34, 0x00549a34)
#ifndef RE_HOOK_BUILD
extern uint32_t Q00549A34;
#endif
#define Q00549A60 GAME_VAR(int32_t, Q00549A60, 0x00549a60)
#ifndef RE_HOOK_BUILD
extern int32_t Q00549A60;
#endif
typedef uint8_t p5_bytes_t[0x400];
#define Q0054C03C GAME_VAR(p5_bytes_t, Q0054C03C, 0x0054c03c)
#ifndef RE_HOOK_BUILD
extern p5_bytes_t Q0054C03C;
#endif
#define Q0054C03D GAME_VAR(p5_bytes_t, Q0054C03D, 0x0054c03d)
#ifndef RE_HOOK_BUILD
extern p5_bytes_t Q0054C03D;
#endif
#define Q0054C03E GAME_VAR(p5_bytes_t, Q0054C03E, 0x0054c03e)
#ifndef RE_HOOK_BUILD
extern p5_bytes_t Q0054C03E;
#endif
#define Q0054C35C GAME_VAR(p5_bytes_t, Q0054C35C, 0x0054c35c)
#ifndef RE_HOOK_BUILD
extern p5_bytes_t Q0054C35C;
#endif
#define Q0054C35D GAME_VAR(p5_bytes_t, Q0054C35D, 0x0054c35d)
#ifndef RE_HOOK_BUILD
extern p5_bytes_t Q0054C35D;
#endif
#define Q0054C35E GAME_VAR(p5_bytes_t, Q0054C35E, 0x0054c35e)
#ifndef RE_HOOK_BUILD
extern p5_bytes_t Q0054C35E;
#endif
#define Q0054C6D8 GAME_VAR(int32_t, Q0054C6D8, 0x0054c6d8)
#ifndef RE_HOOK_BUILD
extern int32_t Q0054C6D8;
#endif
#define Q0054C948 GAME_VAR(int32_t, Q0054C948, 0x0054c948)
#ifndef RE_HOOK_BUILD
extern int32_t Q0054C948;
#endif
#define Q0054CC58 GAME_VAR(int32_t, Q0054CC58, 0x0054cc58)
#ifndef RE_HOOK_BUILD
extern int32_t Q0054CC58;
#endif
#define Q0054DF98 GAME_VAR(uint16_t, Q0054DF98, 0x0054df98)
#ifndef RE_HOOK_BUILD
extern uint16_t Q0054DF98;
#endif
#define Q0054DF9A GAME_VAR(uint16_t, Q0054DF9A, 0x0054df9a)
#ifndef RE_HOOK_BUILD
extern uint16_t Q0054DF9A;
#endif
#define Q0054DF9C GAME_VAR(uint32_t, Q0054DF9C, 0x0054df9c)
#ifndef RE_HOOK_BUILD
extern uint32_t Q0054DF9C;
#endif
#define Q0054E308 GAME_VAR(int32_t, Q0054E308, 0x0054e308)
#ifndef RE_HOOK_BUILD
extern int32_t Q0054E308;
#endif
#define Q0057B56C GAME_VAR(int32_t, Q0057B56C, 0x0057b56c)
#ifndef RE_HOOK_BUILD
extern int32_t Q0057B56C;
#endif
#define Q0057B72C GAME_VAR(int32_t, Q0057B72C, 0x0057b72c)
#ifndef RE_HOOK_BUILD
extern int32_t Q0057B72C;
#endif
#define Q005FE764 GAME_VAR(uint32_t, Q005FE764, 0x005fe764)
#ifndef RE_HOOK_BUILD
extern uint32_t Q005FE764;
#endif
#define Q005FE768 GAME_VAR(int32_t, Q005FE768, 0x005fe768)
#ifndef RE_HOOK_BUILD
extern int32_t Q005FE768;
#endif
#define Q005FEA0C GAME_VAR(int32_t, Q005FEA0C, 0x005fea0c)
#ifndef RE_HOOK_BUILD
extern int32_t Q005FEA0C;
#endif
#define Q005FEA10 GAME_VAR(int32_t, Q005FEA10, 0x005fea10)
#ifndef RE_HOOK_BUILD
extern int32_t Q005FEA10;
#endif
#define Q005FEA20 GAME_VAR(int32_t, Q005FEA20, 0x005fea20)
#ifndef RE_HOOK_BUILD
extern int32_t Q005FEA20;
#endif
#define Q005FEA24 GAME_VAR(int32_t, Q005FEA24, 0x005fea24)
#ifndef RE_HOOK_BUILD
extern int32_t Q005FEA24;
#endif
#define Q00B31E2C GAME_VAR(int32_t, Q00B31E2C, 0x00b31e2c)
#ifndef RE_HOOK_BUILD
extern int32_t Q00B31E2C;
#endif
#define Q00B87E90 GAME_VAR(int32_t, Q00B87E90, 0x00b87e90)
#ifndef RE_HOOK_BUILD
extern int32_t Q00B87E90;
#endif
#define Q00B87E94 GAME_VAR(int32_t, Q00B87E94, 0x00b87e94)
#ifndef RE_HOOK_BUILD
extern int32_t Q00B87E94;
#endif
#define Q00B87EF0 GAME_VAR(int32_t, Q00B87EF0, 0x00b87ef0)
#ifndef RE_HOOK_BUILD
extern int32_t Q00B87EF0;
#endif
#define Q00B87F00 GAME_VAR(int32_t, Q00B87F00, 0x00b87f00)
#ifndef RE_HOOK_BUILD
extern int32_t Q00B87F00;
#endif
#define Q00B91D3C GAME_VAR(int32_t, Q00B91D3C, 0x00b91d3c)
#ifndef RE_HOOK_BUILD
extern int32_t Q00B91D3C;
#endif
#define Q00C55858 GAME_VAR(int32_t, Q00C55858, 0x00c55858)
#ifndef RE_HOOK_BUILD
extern int32_t Q00C55858;
#endif
#define Q00C5585C GAME_VAR(int32_t, Q00C5585C, 0x00c5585c)
#ifndef RE_HOOK_BUILD
extern int32_t Q00C5585C;
#endif
#define Q00C55860 GAME_VAR(int32_t, Q00C55860, 0x00c55860)
#ifndef RE_HOOK_BUILD
extern int32_t Q00C55860;
#endif
#define Q00C55864 GAME_VAR(int32_t, Q00C55864, 0x00c55864)
#ifndef RE_HOOK_BUILD
extern int32_t Q00C55864;
#endif
#define Q00C55868 GAME_VAR(int32_t, Q00C55868, 0x00c55868)
#ifndef RE_HOOK_BUILD
extern int32_t Q00C55868;
#endif
#define Q00C5586C GAME_VAR(int32_t, Q00C5586C, 0x00c5586c)
#ifndef RE_HOOK_BUILD
extern int32_t Q00C5586C;
#endif
#define Q00C55870 GAME_VAR(int32_t, Q00C55870, 0x00c55870)
#ifndef RE_HOOK_BUILD
extern int32_t Q00C55870;
#endif
#define Q00C55874 GAME_VAR(int32_t, Q00C55874, 0x00c55874)
#ifndef RE_HOOK_BUILD
extern int32_t Q00C55874;
#endif
#define Q00C559F8 GAME_VAR(int32_t, Q00C559F8, 0x00c559f8)
#ifndef RE_HOOK_BUILD
extern int32_t Q00C559F8;
#endif
#define Q00C559FC GAME_VAR(int32_t, Q00C559FC, 0x00c559fc)
#ifndef RE_HOOK_BUILD
extern int32_t Q00C559FC;
#endif
#define Q00C55A74 GAME_VAR(int32_t, Q00C55A74, 0x00c55a74)
#ifndef RE_HOOK_BUILD
extern int32_t Q00C55A74;
#endif
#define Q00C812F0 GAME_VAR(int32_t, Q00C812F0, 0x00c812f0)
#ifndef RE_HOOK_BUILD
extern int32_t Q00C812F0;
#endif
#define Q0125F3F8 GAME_VAR(float, Q0125F3F8, 0x0125f3f8)
#ifndef RE_HOOK_BUILD
extern float Q0125F3F8;
#endif
#define Q01270C24 GAME_VAR(float, Q01270C24, 0x01270c24)
#ifndef RE_HOOK_BUILD
extern float Q01270C24;
#endif
int32_t MenuPick0040FEA0(void);
int32_t MenuPick0040FF5A(void);
int32_t MenuPick00410014(void);
int32_t MenuPick004100CE(void);
int32_t MenuPick00410188(void);
int32_t MenuPick00410242(void);
int32_t MenuPick004102FC(void);
int32_t MenuPick004103B6(void);
int32_t MenuPick00410470(void);
int32_t MenuPick0041052A(void);
int32_t MenuPick004105E4(void);
int32_t MenuPick0041069E(void);
void MenuHiliteWhite0041074D(void);
void MenuHiliteRed004106E1(void);
void MenuHiliteRed00411A31(void);
void MenuHiliteWhite00411A9D(void);
void SetIconIdx00412A0D(int32_t reset);
void SetIconIdx00412A7B(int32_t reset);
void SetIconIdx00412AE9(int32_t reset);
void SetIconIdx00412B57(int32_t reset);
void SetIconIdx00412BC5(int32_t reset);
void SetIconIdx00412C33(int32_t reset);
void SetIconIdx00412CA1(int32_t reset);
void SetIconIdx00412D0F(int32_t reset);
void FloatStep00409A91(void);
void FloatStep00409ACA(void);
void FloatStep00409B03(void);
void FloatStep00409B3C(void);
void PrevPcar00404721(void);
void NextPcar0040475E(void);
void SetPcarName0040479B(void);
void SetupMenuTable00412087(void);
void SetupMenuTable00412487(void);
int32_t ToggleOpt004154CD(void);
int32_t ToggleOpt0041542A(void);
void SetupMiami00416040(void);
void LoadArrowIcons00417353(void);
int32_t LoadSliderIcons00417620(void);
int32_t ToggleVar00407636(void);
void StartTimer004086B4(void);
void Call3_0040C455(int32_t a, int32_t b);
void Chain0048AC0D(void);
void Chain004D5FFC(void);
void PlayTrack004D7B60(void);
void Pack565Bytes004BF452(uint8_t r, uint8_t g, uint8_t b);
void Fwd004D262C(int32_t a);
void Fwd004EAFCF(int32_t a);
void Fwd00513CF9(int32_t a);
void Copy400_00407C27(int32_t a);
void LoadTrail004FBE96(void);
void Fwd004FC0C7(void);
