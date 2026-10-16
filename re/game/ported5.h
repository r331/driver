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
#pragma push_macro("Q00546028") /*gvi*/
#undef Q00546028 /*gvi*/
extern float Q00546028;
#pragma pop_macro("Q00546028") /*gvi*/
#endif
#define Q0054602C GAME_VAR(float, Q0054602C, 0x0054602c)
#ifndef RE_HOOK_BUILD
#pragma push_macro("Q0054602C") /*gvi*/
#undef Q0054602C /*gvi*/
extern float Q0054602C;
#pragma pop_macro("Q0054602C") /*gvi*/
#endif
#define Q00546030 GAME_VAR(float, Q00546030, 0x00546030)
#ifndef RE_HOOK_BUILD
#pragma push_macro("Q00546030") /*gvi*/
#undef Q00546030 /*gvi*/
extern float Q00546030;
#pragma pop_macro("Q00546030") /*gvi*/
#endif
#define Q0054604C GAME_VAR(float, Q0054604C, 0x0054604c)
#ifndef RE_HOOK_BUILD
#pragma push_macro("Q0054604C") /*gvi*/
#undef Q0054604C /*gvi*/
extern float Q0054604C;
#pragma pop_macro("Q0054604C") /*gvi*/
#endif
#define Q00549A34 GAME_VAR(uint32_t, Q00549A34, 0x00549a34)
#ifndef RE_HOOK_BUILD
#pragma push_macro("Q00549A34") /*gvi*/
#undef Q00549A34 /*gvi*/
extern uint32_t Q00549A34;
#pragma pop_macro("Q00549A34") /*gvi*/
#endif
#define Q00549A60 GAME_VAR(int32_t, Q00549A60, 0x00549a60)
#ifndef RE_HOOK_BUILD
#pragma push_macro("Q00549A60") /*gvi*/
#undef Q00549A60 /*gvi*/
extern int32_t Q00549A60;
#pragma pop_macro("Q00549A60") /*gvi*/
#endif
typedef uint8_t p5_bytes_t[0x400];
#define Q0054C03C GAME_VAR(p5_bytes_t, Q0054C03C, 0x0054c03c)
#ifndef RE_HOOK_BUILD
#pragma push_macro("Q0054C03C") /*gvi*/
#undef Q0054C03C /*gvi*/
extern p5_bytes_t Q0054C03C;
#pragma pop_macro("Q0054C03C") /*gvi*/
#endif
#define Q0054C03D GAME_VAR(p5_bytes_t, Q0054C03D, 0x0054c03d)
#ifndef RE_HOOK_BUILD
#pragma push_macro("Q0054C03D") /*gvi*/
#undef Q0054C03D /*gvi*/
extern p5_bytes_t Q0054C03D;
#pragma pop_macro("Q0054C03D") /*gvi*/
#endif
#define Q0054C03E GAME_VAR(p5_bytes_t, Q0054C03E, 0x0054c03e)
#ifndef RE_HOOK_BUILD
#pragma push_macro("Q0054C03E") /*gvi*/
#undef Q0054C03E /*gvi*/
extern p5_bytes_t Q0054C03E;
#pragma pop_macro("Q0054C03E") /*gvi*/
#endif
#define Q0054C35C GAME_VAR(p5_bytes_t, Q0054C35C, 0x0054c35c)
#ifndef RE_HOOK_BUILD
#pragma push_macro("Q0054C35C") /*gvi*/
#undef Q0054C35C /*gvi*/
extern p5_bytes_t Q0054C35C;
#pragma pop_macro("Q0054C35C") /*gvi*/
#endif
#define Q0054C35D GAME_VAR(p5_bytes_t, Q0054C35D, 0x0054c35d)
#ifndef RE_HOOK_BUILD
#pragma push_macro("Q0054C35D") /*gvi*/
#undef Q0054C35D /*gvi*/
extern p5_bytes_t Q0054C35D;
#pragma pop_macro("Q0054C35D") /*gvi*/
#endif
#define Q0054C35E GAME_VAR(p5_bytes_t, Q0054C35E, 0x0054c35e)
#ifndef RE_HOOK_BUILD
#pragma push_macro("Q0054C35E") /*gvi*/
#undef Q0054C35E /*gvi*/
extern p5_bytes_t Q0054C35E;
#pragma pop_macro("Q0054C35E") /*gvi*/
#endif
#define Q0054C6D8 GAME_VAR(int32_t, Q0054C6D8, 0x0054c6d8)
#ifndef RE_HOOK_BUILD
#pragma push_macro("Q0054C6D8") /*gvi*/
#undef Q0054C6D8 /*gvi*/
extern int32_t Q0054C6D8;
#pragma pop_macro("Q0054C6D8") /*gvi*/
#endif
#define Q0054C948 GAME_VAR(int32_t, Q0054C948, 0x0054c948)
#ifndef RE_HOOK_BUILD
#pragma push_macro("Q0054C948") /*gvi*/
#undef Q0054C948 /*gvi*/
extern int32_t Q0054C948;
#pragma pop_macro("Q0054C948") /*gvi*/
#endif
#define Q0054CC58 GAME_VAR(int32_t, Q0054CC58, 0x0054cc58)
#ifndef RE_HOOK_BUILD
#pragma push_macro("Q0054CC58") /*gvi*/
#undef Q0054CC58 /*gvi*/
extern int32_t Q0054CC58;
#pragma pop_macro("Q0054CC58") /*gvi*/
#endif
#define Q0054DF98 GAME_VAR(uint16_t, Q0054DF98, 0x0054df98)
#ifndef RE_HOOK_BUILD
#pragma push_macro("Q0054DF98") /*gvi*/
#undef Q0054DF98 /*gvi*/
extern uint16_t Q0054DF98;
#pragma pop_macro("Q0054DF98") /*gvi*/
#endif
#define Q0054DF9A GAME_VAR(uint16_t, Q0054DF9A, 0x0054df9a)
#ifndef RE_HOOK_BUILD
#pragma push_macro("Q0054DF9A") /*gvi*/
#undef Q0054DF9A /*gvi*/
extern uint16_t Q0054DF9A;
#pragma pop_macro("Q0054DF9A") /*gvi*/
#endif
#define Q0054DF9C GAME_VAR(uint32_t, Q0054DF9C, 0x0054df9c)
#ifndef RE_HOOK_BUILD
#pragma push_macro("Q0054DF9C") /*gvi*/
#undef Q0054DF9C /*gvi*/
extern uint32_t Q0054DF9C;
#pragma pop_macro("Q0054DF9C") /*gvi*/
#endif
#define Q0054E308 GAME_VAR(int32_t, Q0054E308, 0x0054e308)
#ifndef RE_HOOK_BUILD
#pragma push_macro("Q0054E308") /*gvi*/
#undef Q0054E308 /*gvi*/
extern int32_t Q0054E308;
#pragma pop_macro("Q0054E308") /*gvi*/
#endif
#define Q0057B56C GAME_VAR(int32_t, Q0057B56C, 0x0057b56c)
#ifndef RE_HOOK_BUILD
#pragma push_macro("Q0057B56C") /*gvi*/
#undef Q0057B56C /*gvi*/
extern int32_t Q0057B56C;
#pragma pop_macro("Q0057B56C") /*gvi*/
#endif
#define Q0057B72C GAME_VAR(int32_t, Q0057B72C, 0x0057b72c)
#ifndef RE_HOOK_BUILD
#pragma push_macro("Q0057B72C") /*gvi*/
#undef Q0057B72C /*gvi*/
extern int32_t Q0057B72C;
#pragma pop_macro("Q0057B72C") /*gvi*/
#endif
#define Q005FE764 GAME_VAR(uint32_t, Q005FE764, 0x005fe764)
#ifndef RE_HOOK_BUILD
#pragma push_macro("Q005FE764") /*gvi*/
#undef Q005FE764 /*gvi*/
extern uint32_t Q005FE764;
#pragma pop_macro("Q005FE764") /*gvi*/
#endif
#define Q005FE768 GAME_VAR(int32_t, Q005FE768, 0x005fe768)
#ifndef RE_HOOK_BUILD
#pragma push_macro("Q005FE768") /*gvi*/
#undef Q005FE768 /*gvi*/
extern int32_t Q005FE768;
#pragma pop_macro("Q005FE768") /*gvi*/
#endif
#define Q005FEA0C GAME_VAR(int32_t, Q005FEA0C, 0x005fea0c)
#ifndef RE_HOOK_BUILD
#pragma push_macro("Q005FEA0C") /*gvi*/
#undef Q005FEA0C /*gvi*/
extern int32_t Q005FEA0C;
#pragma pop_macro("Q005FEA0C") /*gvi*/
#endif
#define Q005FEA10 GAME_VAR(int32_t, Q005FEA10, 0x005fea10)
#ifndef RE_HOOK_BUILD
#pragma push_macro("Q005FEA10") /*gvi*/
#undef Q005FEA10 /*gvi*/
extern int32_t Q005FEA10;
#pragma pop_macro("Q005FEA10") /*gvi*/
#endif
#define Q005FEA20 GAME_VAR(int32_t, Q005FEA20, 0x005fea20)
#ifndef RE_HOOK_BUILD
#pragma push_macro("Q005FEA20") /*gvi*/
#undef Q005FEA20 /*gvi*/
extern int32_t Q005FEA20;
#pragma pop_macro("Q005FEA20") /*gvi*/
#endif
#define Q005FEA24 GAME_VAR(int32_t, Q005FEA24, 0x005fea24)
#ifndef RE_HOOK_BUILD
#pragma push_macro("Q005FEA24") /*gvi*/
#undef Q005FEA24 /*gvi*/
extern int32_t Q005FEA24;
#pragma pop_macro("Q005FEA24") /*gvi*/
#endif
#define Q00B31E2C GAME_VAR(int32_t, Q00B31E2C, 0x00b31e2c)
#ifndef RE_HOOK_BUILD
#pragma push_macro("Q00B31E2C") /*gvi*/
#undef Q00B31E2C /*gvi*/
extern int32_t Q00B31E2C;
#pragma pop_macro("Q00B31E2C") /*gvi*/
#endif
#define Q00B87E90 GAME_VAR(int32_t, Q00B87E90, 0x00b87e90)
#ifndef RE_HOOK_BUILD
#pragma push_macro("Q00B87E90") /*gvi*/
#undef Q00B87E90 /*gvi*/
extern int32_t Q00B87E90;
#pragma pop_macro("Q00B87E90") /*gvi*/
#endif
#define Q00B87E94 GAME_VAR(int32_t, Q00B87E94, 0x00b87e94)
#ifndef RE_HOOK_BUILD
#pragma push_macro("Q00B87E94") /*gvi*/
#undef Q00B87E94 /*gvi*/
extern int32_t Q00B87E94;
#pragma pop_macro("Q00B87E94") /*gvi*/
#endif
#define Q00B87EF0 GAME_VAR(int32_t, Q00B87EF0, 0x00b87ef0)
#ifndef RE_HOOK_BUILD
#pragma push_macro("Q00B87EF0") /*gvi*/
#undef Q00B87EF0 /*gvi*/
extern int32_t Q00B87EF0;
#pragma pop_macro("Q00B87EF0") /*gvi*/
#endif
#define Q00B87F00 GAME_VAR(int32_t, Q00B87F00, 0x00b87f00)
#ifndef RE_HOOK_BUILD
#pragma push_macro("Q00B87F00") /*gvi*/
#undef Q00B87F00 /*gvi*/
extern int32_t Q00B87F00;
#pragma pop_macro("Q00B87F00") /*gvi*/
#endif
#define Q00B91D3C GAME_VAR(int32_t, Q00B91D3C, 0x00b91d3c)
#ifndef RE_HOOK_BUILD
#pragma push_macro("Q00B91D3C") /*gvi*/
#undef Q00B91D3C /*gvi*/
extern int32_t Q00B91D3C;
#pragma pop_macro("Q00B91D3C") /*gvi*/
#endif
#define Q00C55858 GAME_VAR(int32_t, Q00C55858, 0x00c55858)
#ifndef RE_HOOK_BUILD
#pragma push_macro("Q00C55858") /*gvi*/
#undef Q00C55858 /*gvi*/
extern int32_t Q00C55858;
#pragma pop_macro("Q00C55858") /*gvi*/
#endif
#define Q00C5585C GAME_VAR(int32_t, Q00C5585C, 0x00c5585c)
#ifndef RE_HOOK_BUILD
#pragma push_macro("Q00C5585C") /*gvi*/
#undef Q00C5585C /*gvi*/
extern int32_t Q00C5585C;
#pragma pop_macro("Q00C5585C") /*gvi*/
#endif
#define Q00C55860 GAME_VAR(int32_t, Q00C55860, 0x00c55860)
#ifndef RE_HOOK_BUILD
#pragma push_macro("Q00C55860") /*gvi*/
#undef Q00C55860 /*gvi*/
extern int32_t Q00C55860;
#pragma pop_macro("Q00C55860") /*gvi*/
#endif
#define Q00C55864 GAME_VAR(int32_t, Q00C55864, 0x00c55864)
#ifndef RE_HOOK_BUILD
#pragma push_macro("Q00C55864") /*gvi*/
#undef Q00C55864 /*gvi*/
extern int32_t Q00C55864;
#pragma pop_macro("Q00C55864") /*gvi*/
#endif
#define Q00C55868 GAME_VAR(int32_t, Q00C55868, 0x00c55868)
#ifndef RE_HOOK_BUILD
#pragma push_macro("Q00C55868") /*gvi*/
#undef Q00C55868 /*gvi*/
extern int32_t Q00C55868;
#pragma pop_macro("Q00C55868") /*gvi*/
#endif
#define Q00C5586C GAME_VAR(int32_t, Q00C5586C, 0x00c5586c)
#ifndef RE_HOOK_BUILD
#pragma push_macro("Q00C5586C") /*gvi*/
#undef Q00C5586C /*gvi*/
extern int32_t Q00C5586C;
#pragma pop_macro("Q00C5586C") /*gvi*/
#endif
#define Q00C55870 GAME_VAR(int32_t, Q00C55870, 0x00c55870)
#ifndef RE_HOOK_BUILD
#pragma push_macro("Q00C55870") /*gvi*/
#undef Q00C55870 /*gvi*/
extern int32_t Q00C55870;
#pragma pop_macro("Q00C55870") /*gvi*/
#endif
#define Q00C55874 GAME_VAR(int32_t, Q00C55874, 0x00c55874)
#ifndef RE_HOOK_BUILD
#pragma push_macro("Q00C55874") /*gvi*/
#undef Q00C55874 /*gvi*/
extern int32_t Q00C55874;
#pragma pop_macro("Q00C55874") /*gvi*/
#endif
#define Q00C559F8 GAME_VAR(int32_t, Q00C559F8, 0x00c559f8)
#ifndef RE_HOOK_BUILD
#pragma push_macro("Q00C559F8") /*gvi*/
#undef Q00C559F8 /*gvi*/
extern int32_t Q00C559F8;
#pragma pop_macro("Q00C559F8") /*gvi*/
#endif
#define Q00C559FC GAME_VAR(int32_t, Q00C559FC, 0x00c559fc)
#ifndef RE_HOOK_BUILD
#pragma push_macro("Q00C559FC") /*gvi*/
#undef Q00C559FC /*gvi*/
extern int32_t Q00C559FC;
#pragma pop_macro("Q00C559FC") /*gvi*/
#endif
#define Q00C55A74 GAME_VAR(int32_t, Q00C55A74, 0x00c55a74)
#ifndef RE_HOOK_BUILD
#pragma push_macro("Q00C55A74") /*gvi*/
#undef Q00C55A74 /*gvi*/
extern int32_t Q00C55A74;
#pragma pop_macro("Q00C55A74") /*gvi*/
#endif
#define Q00C812F0 GAME_VAR(int32_t, Q00C812F0, 0x00c812f0)
#ifndef RE_HOOK_BUILD
#pragma push_macro("Q00C812F0") /*gvi*/
#undef Q00C812F0 /*gvi*/
extern int32_t Q00C812F0;
#pragma pop_macro("Q00C812F0") /*gvi*/
#endif
#define Q0125F3F8 GAME_VAR(float, Q0125F3F8, 0x0125f3f8)
#ifndef RE_HOOK_BUILD
#pragma push_macro("Q0125F3F8") /*gvi*/
#undef Q0125F3F8 /*gvi*/
extern float Q0125F3F8;
#pragma pop_macro("Q0125F3F8") /*gvi*/
#endif
#define Q01270C24 GAME_VAR(float, Q01270C24, 0x01270c24)
#ifndef RE_HOOK_BUILD
#pragma push_macro("Q01270C24") /*gvi*/
#undef Q01270C24 /*gvi*/
extern float Q01270C24;
#pragma pop_macro("Q01270C24") /*gvi*/
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
/* gvar-img v2.03 begin (tools/gen_gvar_img.py) */
#if !defined(RE_HOOK_BUILD) && !defined(RE_GVAR_PLAIN)
#undef Q00546028
#define Q00546028 (*(float *)re_gvar(0x00546028u, sizeof(float), (void *)&Q00546028))
#undef Q0054602C
#define Q0054602C (*(float *)re_gvar(0x0054602cu, sizeof(float), (void *)&Q0054602C))
#undef Q00546030
#define Q00546030 (*(float *)re_gvar(0x00546030u, sizeof(float), (void *)&Q00546030))
#undef Q0054604C
#define Q0054604C (*(float *)re_gvar(0x0054604cu, sizeof(float), (void *)&Q0054604C))
#undef Q00549A34
#define Q00549A34 (*(uint32_t *)re_gvar(0x00549a34u, sizeof(uint32_t), (void *)&Q00549A34))
#undef Q00549A60
#define Q00549A60 (*(int32_t *)re_gvar(0x00549a60u, sizeof(int32_t), (void *)&Q00549A60))
#undef Q0054C03C
#define Q0054C03C (*(p5_bytes_t *)re_gvar(0x0054c03cu, sizeof(p5_bytes_t), (void *)&Q0054C03C))
#undef Q0054C03D
#define Q0054C03D (*(p5_bytes_t *)re_gvar(0x0054c03du, sizeof(p5_bytes_t), (void *)&Q0054C03D))
#undef Q0054C03E
#define Q0054C03E (*(p5_bytes_t *)re_gvar(0x0054c03eu, sizeof(p5_bytes_t), (void *)&Q0054C03E))
#undef Q0054C35C
#define Q0054C35C (*(p5_bytes_t *)re_gvar(0x0054c35cu, sizeof(p5_bytes_t), (void *)&Q0054C35C))
#undef Q0054C35D
#define Q0054C35D (*(p5_bytes_t *)re_gvar(0x0054c35du, sizeof(p5_bytes_t), (void *)&Q0054C35D))
#undef Q0054C35E
#define Q0054C35E (*(p5_bytes_t *)re_gvar(0x0054c35eu, sizeof(p5_bytes_t), (void *)&Q0054C35E))
#undef Q0054C6D8
#define Q0054C6D8 (*(int32_t *)re_gvar(0x0054c6d8u, sizeof(int32_t), (void *)&Q0054C6D8))
#undef Q0054C948
#define Q0054C948 (*(int32_t *)re_gvar(0x0054c948u, sizeof(int32_t), (void *)&Q0054C948))
#undef Q0054CC58
#define Q0054CC58 (*(int32_t *)re_gvar(0x0054cc58u, sizeof(int32_t), (void *)&Q0054CC58))
#undef Q0054DF98
#define Q0054DF98 (*(uint16_t *)re_gvar(0x0054df98u, sizeof(uint16_t), (void *)&Q0054DF98))
#undef Q0054DF9A
#define Q0054DF9A (*(uint16_t *)re_gvar(0x0054df9au, sizeof(uint16_t), (void *)&Q0054DF9A))
#undef Q0054DF9C
#define Q0054DF9C (*(uint32_t *)re_gvar(0x0054df9cu, sizeof(uint32_t), (void *)&Q0054DF9C))
#undef Q0054E308
#define Q0054E308 (*(int32_t *)re_gvar(0x0054e308u, sizeof(int32_t), (void *)&Q0054E308))
#undef Q0057B56C
#define Q0057B56C (*(int32_t *)re_gvar(0x0057b56cu, sizeof(int32_t), (void *)&Q0057B56C))
#undef Q0057B72C
#define Q0057B72C (*(int32_t *)re_gvar(0x0057b72cu, sizeof(int32_t), (void *)&Q0057B72C))
#undef Q005FE764
#define Q005FE764 (*(uint32_t *)re_gvar(0x005fe764u, sizeof(uint32_t), (void *)&Q005FE764))
#undef Q005FE768
#define Q005FE768 (*(int32_t *)re_gvar(0x005fe768u, sizeof(int32_t), (void *)&Q005FE768))
#undef Q005FEA0C
#define Q005FEA0C (*(int32_t *)re_gvar(0x005fea0cu, sizeof(int32_t), (void *)&Q005FEA0C))
#undef Q005FEA10
#define Q005FEA10 (*(int32_t *)re_gvar(0x005fea10u, sizeof(int32_t), (void *)&Q005FEA10))
#undef Q005FEA20
#define Q005FEA20 (*(int32_t *)re_gvar(0x005fea20u, sizeof(int32_t), (void *)&Q005FEA20))
#undef Q005FEA24
#define Q005FEA24 (*(int32_t *)re_gvar(0x005fea24u, sizeof(int32_t), (void *)&Q005FEA24))
#undef Q00B31E2C
#define Q00B31E2C (*(int32_t *)re_gvar(0x00b31e2cu, sizeof(int32_t), (void *)&Q00B31E2C))
#undef Q00B87E90
#define Q00B87E90 (*(int32_t *)re_gvar(0x00b87e90u, sizeof(int32_t), (void *)&Q00B87E90))
#undef Q00B87E94
#define Q00B87E94 (*(int32_t *)re_gvar(0x00b87e94u, sizeof(int32_t), (void *)&Q00B87E94))
#undef Q00B87EF0
#define Q00B87EF0 (*(int32_t *)re_gvar(0x00b87ef0u, sizeof(int32_t), (void *)&Q00B87EF0))
#undef Q00B87F00
#define Q00B87F00 (*(int32_t *)re_gvar(0x00b87f00u, sizeof(int32_t), (void *)&Q00B87F00))
#undef Q00B91D3C
#define Q00B91D3C (*(int32_t *)re_gvar(0x00b91d3cu, sizeof(int32_t), (void *)&Q00B91D3C))
#undef Q00C55858
#define Q00C55858 (*(int32_t *)re_gvar(0x00c55858u, sizeof(int32_t), (void *)&Q00C55858))
#undef Q00C5585C
#define Q00C5585C (*(int32_t *)re_gvar(0x00c5585cu, sizeof(int32_t), (void *)&Q00C5585C))
#undef Q00C55860
#define Q00C55860 (*(int32_t *)re_gvar(0x00c55860u, sizeof(int32_t), (void *)&Q00C55860))
#undef Q00C55864
#define Q00C55864 (*(int32_t *)re_gvar(0x00c55864u, sizeof(int32_t), (void *)&Q00C55864))
#undef Q00C55868
#define Q00C55868 (*(int32_t *)re_gvar(0x00c55868u, sizeof(int32_t), (void *)&Q00C55868))
#undef Q00C5586C
#define Q00C5586C (*(int32_t *)re_gvar(0x00c5586cu, sizeof(int32_t), (void *)&Q00C5586C))
#undef Q00C55870
#define Q00C55870 (*(int32_t *)re_gvar(0x00c55870u, sizeof(int32_t), (void *)&Q00C55870))
#undef Q00C55874
#define Q00C55874 (*(int32_t *)re_gvar(0x00c55874u, sizeof(int32_t), (void *)&Q00C55874))
#undef Q00C559F8
#define Q00C559F8 (*(int32_t *)re_gvar(0x00c559f8u, sizeof(int32_t), (void *)&Q00C559F8))
#undef Q00C559FC
#define Q00C559FC (*(int32_t *)re_gvar(0x00c559fcu, sizeof(int32_t), (void *)&Q00C559FC))
#undef Q00C55A74
#define Q00C55A74 (*(int32_t *)re_gvar(0x00c55a74u, sizeof(int32_t), (void *)&Q00C55A74))
#undef Q00C812F0
#define Q00C812F0 (*(int32_t *)re_gvar(0x00c812f0u, sizeof(int32_t), (void *)&Q00C812F0))
#undef Q0125F3F8
#define Q0125F3F8 (*(float *)re_gvar(0x0125f3f8u, sizeof(float), (void *)&Q0125F3F8))
#undef Q01270C24
#define Q01270C24 (*(float *)re_gvar(0x01270c24u, sizeof(float), (void *)&Q01270C24))
#endif
/* gvar-img v2.03 end */
