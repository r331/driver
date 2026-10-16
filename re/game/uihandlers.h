/* UI/menu-обработчики: простые сеттеры и переходы. */
#pragma once
#include "gvar.h"
#include "unported.h"
#include "menuselect.h"
#include "menustate.h"
#define UiVar00B87E38 GAME_VAR(int32_t, UiVar00B87E38, 0x00b87e38)
#define UiVar005FE84C GAME_VAR(int32_t, UiVar005FE84C, 0x005fe84c)
#define UiVar005FE850 GAME_VAR(int32_t, UiVar005FE850, 0x005fe850)
#define UiVar005FE928 GAME_VAR(int32_t, UiVar005FE928, 0x005fe928)
#define UiVar005FE92C GAME_VAR(int32_t, UiVar005FE92C, 0x005fe92c)
#define UiVar0054CC64 GAME_VAR(uint8_t, UiVar0054CC64, 0x0054cc64)
#define UiVar0054CC74 GAME_VAR(uint8_t, UiVar0054CC74, 0x0054cc74)
#define UiVar0054D10C GAME_VAR(uint8_t, UiVar0054D10C, 0x0054d10c)
#define UiVar0054D11C GAME_VAR(uint8_t, UiVar0054D11C, 0x0054d11c)
#define UiVar0054BF18 GAME_VAR(int32_t, UiVar0054BF18, 0x0054bf18)
#define UiVar005FE6BC GAME_VAR(int32_t, UiVar005FE6BC, 0x005fe6bc)
#define UiVar005FEA30 GAME_VAR(int32_t, UiVar005FEA30, 0x005fea30)
#define UiVar0054E4B0 GAME_VAR(int32_t, UiVar0054E4B0, 0x0054e4b0)
#ifndef RE_HOOK_BUILD
#pragma push_macro("UiVar00B87E38") /*gvi*/
#undef UiVar00B87E38 /*gvi*/
extern int32_t UiVar00B87E38;
#pragma pop_macro("UiVar00B87E38") /*gvi*/
#pragma push_macro("UiVar005FE84C") /*gvi*/
#undef UiVar005FE84C /*gvi*/
extern int32_t UiVar005FE84C;
#pragma pop_macro("UiVar005FE84C") /*gvi*/
#pragma push_macro("UiVar005FE850") /*gvi*/
#undef UiVar005FE850 /*gvi*/
extern int32_t UiVar005FE850;
#pragma pop_macro("UiVar005FE850") /*gvi*/
#pragma push_macro("UiVar005FE928") /*gvi*/
#undef UiVar005FE928 /*gvi*/
extern int32_t UiVar005FE928;
#pragma pop_macro("UiVar005FE928") /*gvi*/
#pragma push_macro("UiVar005FE92C") /*gvi*/
#undef UiVar005FE92C /*gvi*/
extern int32_t UiVar005FE92C;
#pragma pop_macro("UiVar005FE92C") /*gvi*/
#pragma push_macro("UiVar0054CC64") /*gvi*/
#undef UiVar0054CC64 /*gvi*/
extern uint8_t UiVar0054CC64;
#pragma pop_macro("UiVar0054CC64") /*gvi*/
#pragma push_macro("UiVar0054CC74") /*gvi*/
#undef UiVar0054CC74 /*gvi*/
extern uint8_t UiVar0054CC74;
#pragma pop_macro("UiVar0054CC74") /*gvi*/
#pragma push_macro("UiVar0054D10C") /*gvi*/
#undef UiVar0054D10C /*gvi*/
extern uint8_t UiVar0054D10C;
#pragma pop_macro("UiVar0054D10C") /*gvi*/
#pragma push_macro("UiVar0054D11C") /*gvi*/
#undef UiVar0054D11C /*gvi*/
extern uint8_t UiVar0054D11C;
#pragma pop_macro("UiVar0054D11C") /*gvi*/
#pragma push_macro("UiVar0054BF18") /*gvi*/
#undef UiVar0054BF18 /*gvi*/
extern int32_t UiVar0054BF18;
#pragma pop_macro("UiVar0054BF18") /*gvi*/
#pragma push_macro("UiVar005FE6BC") /*gvi*/
#undef UiVar005FE6BC /*gvi*/
extern int32_t UiVar005FE6BC;
#pragma pop_macro("UiVar005FE6BC") /*gvi*/
#pragma push_macro("UiVar005FEA30") /*gvi*/
#undef UiVar005FEA30 /*gvi*/
extern int32_t UiVar005FEA30;
#pragma pop_macro("UiVar005FEA30") /*gvi*/
#pragma push_macro("UiVar0054E4B0") /*gvi*/
#undef UiVar0054E4B0 /*gvi*/
extern int32_t UiVar0054E4B0;
#pragma pop_macro("UiVar0054E4B0") /*gvi*/
#endif
void Ui00408699(void); /* 00408699 */
void Ui0040C867(void); /* 0040c867 */
void Ui0040C87A(void); /* 0040c87a */
void Ui0040C88D(void); /* 0040c88d */
void Ui004120EE(int32_t mode); /* 004120ee */
void Ui004120FE(void); /* 004120fe */
void Ui00412112(void); /* 00412112 */
void Ui00412126(void); /* 00412126 */
void Ui0041213A(void); /* 0041213a */
void Ui0041214E(void); /* 0041214e */
void Ui00412162(void); /* 00412162 */
void Ui00412176(void); /* 00412176 */
void Ui0041218A(void); /* 0041218a */
void Ui004122E7(void); /* 004122e7 */
void Ui00412509(int32_t mode); /* 00412509 */
void Ui00412519(void); /* 00412519 */
void Ui0041252D(void); /* 0041252d */
void Ui00412541(void); /* 00412541 */
void Ui00412555(void); /* 00412555 */
void Ui00412569(void); /* 00412569 */
void Ui0041257D(void); /* 0041257d */
void Ui00412591(void); /* 00412591 */
void Ui004125A5(void); /* 004125a5 */
void Ui00412702(void); /* 00412702 */
void Ui00412F3A(int32_t mode); /* 00412f3a */
void Ui00412F56(void); /* 00412f56 */
int32_t Ui00412F62(void); /* 00412f62 */
void Ui00412F74(int32_t mode); /* 00412f74 */
void Ui00412F90(void); /* 00412f90 */
int32_t Ui00412F9C(void); /* 00412f9c */
void Ui00413543(void); /* 00413543 */
void Ui0041354F(void); /* 0041354f */
int32_t Ui0041355B(void); /* 0041355b */
void Ui0041357E(void); /* 0041357e */
void Ui0041358A(void); /* 0041358a */
void Ui004136CE(void); /* 004136ce */
void Ui0041371C(void); /* 0041371c */
void Ui0041376A(void); /* 0041376a */
void Ui004137B8(void); /* 004137b8 */
void Ui00413955(void); /* 00413955 */
void Ui004139A3(void); /* 004139a3 */
int32_t Ui004139C1(void); /* 004139c1 */
void Ui004139DA(void); /* 004139da */
int32_t Ui004139F8(void); /* 004139f8 */
void Ui00413A11(void); /* 00413a11 */
int32_t Ui00413A2F(void); /* 00413a2f */
void Ui00413A48(void); /* 00413a48 */
int32_t Ui00413A66(void); /* 00413a66 */
void Ui00413BC5(void); /* 00413bc5 */
void Ui00413BF7(void); /* 00413bf7 */
void Ui00413C29(void); /* 00413c29 */
void Ui00413C5B(void); /* 00413c5b */
void Ui00413C8D(void); /* 00413c8d */
int32_t Ui004157A9(void); /* 004157a9 */
int32_t Ui00415841(void); /* 00415841 */
void Ui00417A89(void); /* 00417a89 */
void Ui00417A98(void); /* 00417a98 */
int32_t Ui00417AD6(void); /* 00417ad6 */
void Ui00417AEA(void); /* 00417aea */
void Ui00417AF9(void); /* 00417af9 */
/* gvar-img v2.03 begin (tools/gen_gvar_img.py) */
#if !defined(RE_HOOK_BUILD) && !defined(RE_GVAR_PLAIN)
#undef UiVar00B87E38
#define UiVar00B87E38 (*(int32_t *)re_gvar(0x00b87e38u, sizeof(int32_t), (void *)&UiVar00B87E38))
#undef UiVar005FE84C
#define UiVar005FE84C (*(int32_t *)re_gvar(0x005fe84cu, sizeof(int32_t), (void *)&UiVar005FE84C))
#undef UiVar005FE850
#define UiVar005FE850 (*(int32_t *)re_gvar(0x005fe850u, sizeof(int32_t), (void *)&UiVar005FE850))
#undef UiVar005FE928
#define UiVar005FE928 (*(int32_t *)re_gvar(0x005fe928u, sizeof(int32_t), (void *)&UiVar005FE928))
#undef UiVar005FE92C
#define UiVar005FE92C (*(int32_t *)re_gvar(0x005fe92cu, sizeof(int32_t), (void *)&UiVar005FE92C))
#undef UiVar0054CC64
#define UiVar0054CC64 (*(uint8_t *)re_gvar(0x0054cc64u, sizeof(uint8_t), (void *)&UiVar0054CC64))
#undef UiVar0054CC74
#define UiVar0054CC74 (*(uint8_t *)re_gvar(0x0054cc74u, sizeof(uint8_t), (void *)&UiVar0054CC74))
#undef UiVar0054D10C
#define UiVar0054D10C (*(uint8_t *)re_gvar(0x0054d10cu, sizeof(uint8_t), (void *)&UiVar0054D10C))
#undef UiVar0054D11C
#define UiVar0054D11C (*(uint8_t *)re_gvar(0x0054d11cu, sizeof(uint8_t), (void *)&UiVar0054D11C))
#undef UiVar0054BF18
#define UiVar0054BF18 (*(int32_t *)re_gvar(0x0054bf18u, sizeof(int32_t), (void *)&UiVar0054BF18))
#undef UiVar005FE6BC
#define UiVar005FE6BC (*(int32_t *)re_gvar(0x005fe6bcu, sizeof(int32_t), (void *)&UiVar005FE6BC))
#undef UiVar005FEA30
#define UiVar005FEA30 (*(int32_t *)re_gvar(0x005fea30u, sizeof(int32_t), (void *)&UiVar005FEA30))
#undef UiVar0054E4B0
#define UiVar0054E4B0 (*(int32_t *)re_gvar(0x0054e4b0u, sizeof(int32_t), (void *)&UiVar0054E4B0))
#endif
/* gvar-img v2.03 end */
