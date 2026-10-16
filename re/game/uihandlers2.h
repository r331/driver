/* UI/menu-обработчики: простые сеттеры и переходы. */
#pragma once
#include "gvar.h"
#include "unported.h"
#include "uihandlers.h"
#define UiVar005FEA80 GAME_VAR(int32_t, UiVar005FEA80, 0x005fea80)
#define UiVar0054E654 GAME_VAR(int32_t, UiVar0054E654, 0x0054e654)
#define UiVar005FEA8C GAME_VAR(int32_t, UiVar005FEA8C, 0x005fea8c)
#define UiVar005FEDA0 GAME_VAR(int32_t, UiVar005FEDA0, 0x005feda0)
#define UiVar005FEA98 GAME_VAR(int32_t, UiVar005FEA98, 0x005fea98)
#define UiVar005FEB48 GAME_VAR(int32_t, UiVar005FEB48, 0x005feb48)
#define UiVar01251A70 GAME_VAR(uint8_t, UiVar01251A70, 0x01251a70)
#define UiVar011F43B0 GAME_VAR(int32_t, UiVar011F43B0, 0x011f43b0)
#define UiVar00B1C280 GAME_VAR(int32_t, UiVar00B1C280, 0x00b1c280)
#ifndef RE_HOOK_BUILD
#pragma push_macro("UiVar005FEA80") /*gvi*/
#undef UiVar005FEA80 /*gvi*/
extern int32_t UiVar005FEA80;
#pragma pop_macro("UiVar005FEA80") /*gvi*/
#pragma push_macro("UiVar0054E654") /*gvi*/
#undef UiVar0054E654 /*gvi*/
extern int32_t UiVar0054E654;
#pragma pop_macro("UiVar0054E654") /*gvi*/
#pragma push_macro("UiVar005FEA8C") /*gvi*/
#undef UiVar005FEA8C /*gvi*/
extern int32_t UiVar005FEA8C;
#pragma pop_macro("UiVar005FEA8C") /*gvi*/
#pragma push_macro("UiVar005FEDA0") /*gvi*/
#undef UiVar005FEDA0 /*gvi*/
extern int32_t UiVar005FEDA0;
#pragma pop_macro("UiVar005FEDA0") /*gvi*/
#pragma push_macro("UiVar005FEA98") /*gvi*/
#undef UiVar005FEA98 /*gvi*/
extern int32_t UiVar005FEA98;
#pragma pop_macro("UiVar005FEA98") /*gvi*/
#pragma push_macro("UiVar005FEB48") /*gvi*/
#undef UiVar005FEB48 /*gvi*/
extern int32_t UiVar005FEB48;
#pragma pop_macro("UiVar005FEB48") /*gvi*/
#pragma push_macro("UiVar01251A70") /*gvi*/
#undef UiVar01251A70 /*gvi*/
extern uint8_t UiVar01251A70;
#pragma pop_macro("UiVar01251A70") /*gvi*/
#pragma push_macro("UiVar011F43B0") /*gvi*/
#undef UiVar011F43B0 /*gvi*/
extern int32_t UiVar011F43B0;
#pragma pop_macro("UiVar011F43B0") /*gvi*/
#pragma push_macro("UiVar00B1C280") /*gvi*/
#undef UiVar00B1C280 /*gvi*/
extern int32_t UiVar00B1C280;
#pragma pop_macro("UiVar00B1C280") /*gvi*/
#endif
int32_t Ui00417B03(void); /* 00417b03 */
void Ui004183E8(void); /* 004183e8 */
void Ui00418886(void); /* 00418886 */
void Ui0041889C(void); /* 0041889c */
void Ui00419C2D(void); /* 00419c2d */
void Ui00419C46(void); /* 00419c46 */
void Ui00419C69(void); /* 00419c69 */
void Ui00419C82(void); /* 00419c82 */
void Ui00419D02(void); /* 00419d02 */
void Ui00419D1B(void); /* 00419d1b */
void Ui00419FBD(void); /* 00419fbd */
void Ui00419FCC(void); /* 00419fcc */
int32_t Ui00419FD6(void); /* 00419fd6 */
void Ui00419FE2(void); /* 00419fe2 */
void Ui00419FF1(void); /* 00419ff1 */
int32_t Ui00419FFB(void); /* 00419ffb */
void Ui0041A007(void); /* 0041a007 */
void Ui0041A016(void); /* 0041a016 */
int32_t Ui0041A020(void); /* 0041a020 */
void Ui0041A02C(void); /* 0041a02c */
void Ui0041A03B(void); /* 0041a03b */
int32_t Ui0041A045(void); /* 0041a045 */
void Ui0041A192(void); /* 0041a192 */
void Ui0041AE25(void); /* 0041ae25 */
void Ui0041D94A(void); /* 0041d94a */
int32_t Ui0041DEC1(void); /* 0041dec1 */
int32_t Ui0041EC79(void); /* 0041ec79 */
int32_t Ui0041ED0E(void); /* 0041ed0e */
int32_t Ui0041ED2D(void); /* 0041ed2d */
int32_t Ui0041ED3E(void); /* 0041ed3e */
int32_t Ui0041ED83(void); /* 0041ed83 */
int32_t Ui0041ED8A(void); /* 0041ed8a */
int32_t Ui0041ED91(void); /* 0041ed91 */
int32_t Ui0041F47C(void); /* 0041f47c */
int32_t Ui0041F74A(void); /* 0041f74a */
int32_t Ui0041F7E7(void); /* 0041f7e7 */
int32_t Ui0041F7F7(void); /* 0041f7f7 */
int32_t Ui0041F800(void); /* 0041f800 */
int32_t Ui0041FA2D(void); /* 0041fa2d */
int32_t Ui0041FA40(void); /* 0041fa40 */
int32_t Ui0041FA6B(void); /* 0041fa6b */
int32_t Ui0041FA74(void); /* 0041fa74 */
int32_t Ui0041FA84(void); /* 0041fa84 */
int32_t Ui0041FA99(void); /* 0041fa99 */
int32_t Ui0041FAA2(void); /* 0041faa2 */
int32_t Ui0041FAAB(void); /* 0041faab */
void Ui004264A7(void); /* 004264a7 */
void Ui004268E0(void); /* 004268e0 */
/* gvar-img v2.03 begin (tools/gen_gvar_img.py) */
#if !defined(RE_HOOK_BUILD) && !defined(RE_GVAR_PLAIN)
#undef UiVar005FEA80
#define UiVar005FEA80 (*(int32_t *)re_gvar(0x005fea80u, sizeof(int32_t), (void *)&UiVar005FEA80))
#undef UiVar0054E654
#define UiVar0054E654 (*(int32_t *)re_gvar(0x0054e654u, sizeof(int32_t), (void *)&UiVar0054E654))
#undef UiVar005FEA8C
#define UiVar005FEA8C (*(int32_t *)re_gvar(0x005fea8cu, sizeof(int32_t), (void *)&UiVar005FEA8C))
#undef UiVar005FEDA0
#define UiVar005FEDA0 (*(int32_t *)re_gvar(0x005feda0u, sizeof(int32_t), (void *)&UiVar005FEDA0))
#undef UiVar005FEA98
#define UiVar005FEA98 (*(int32_t *)re_gvar(0x005fea98u, sizeof(int32_t), (void *)&UiVar005FEA98))
#undef UiVar005FEB48
#define UiVar005FEB48 (*(int32_t *)re_gvar(0x005feb48u, sizeof(int32_t), (void *)&UiVar005FEB48))
#undef UiVar01251A70
#define UiVar01251A70 (*(uint8_t *)re_gvar(0x01251a70u, sizeof(uint8_t), (void *)&UiVar01251A70))
#undef UiVar011F43B0
#define UiVar011F43B0 (*(int32_t *)re_gvar(0x011f43b0u, sizeof(int32_t), (void *)&UiVar011F43B0))
#undef UiVar00B1C280
#define UiVar00B1C280 (*(int32_t *)re_gvar(0x00b1c280u, sizeof(int32_t), (void *)&UiVar00B1C280))
#endif
/* gvar-img v2.03 end */
