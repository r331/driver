#pragma once
#include <stdint.h>
#include "gvar.h"
/* v1.84: ported139 — компиляция скрипта миссии, трейл, метки скрипта, эффекты сцены, конец/сохранение повтора,
   меню клавиш A/B, компиляция MLADDER.DML. Все cdecl. */
typedef uint32_t p139_u6_t[6];
typedef uint8_t  p139_b1000_t[0x1000];
typedef uint8_t  p139_b400_t[0x400];
typedef uint32_t p139_u4_t[4];
#define P139_C818A0   GAME_VAR(p139_u6_t, P139_C818A0, 0x00c818a0)     /* запись скрипта (P113_MrkRec ← её адрес) */
#define P139_LineNo   GAME_VAR(int32_t, P139_LineNo, 0x00c80c54)       /* номер строки компиляции скрипта */
#define P139_KeyStA   GAME_VAR(int32_t, P139_KeyStA, 0x005fe75c)       /* пункт меню клавиш A */
#define P139_KeyPrA   GAME_VAR(int32_t, P139_KeyPrA, 0x005fe760)
#define P139_BlinkA   GAME_VAR(int32_t, P139_BlinkA, 0x005fe76c)
#define P139_KeyStB   GAME_VAR(int32_t, P139_KeyStB, 0x005fe780)       /* пункт меню клавиш B */
#define P139_KeyPrB   GAME_VAR(int32_t, P139_KeyPrB, 0x005fe784)
#define P139_BlinkB   GAME_VAR(int32_t, P139_BlinkB, 0x005fe794)
#define P139_Ladder   GAME_VAR(p139_b1000_t, P139_Ladder, 0x005ff368)  /* код MLADDER (записи 0x10) */
#define P139_LadStr   GAME_VAR(p139_b400_t, P139_LadStr, 0x005fef38)   /* строки MLADDER */
#define P139_LadA     GAME_VAR(p139_u4_t, P139_LadA, 0x005ff358)
#define P139_LadB     GAME_VAR(p139_u4_t, P139_LadB, 0x005ff348)
#define P139_LadC     GAME_VAR(p139_u4_t, P139_LadC, 0x0060037c)
#define P139_LadD     GAME_VAR(p139_u4_t, P139_LadD, 0x005ff338)
#define P139_LadE     GAME_VAR(p139_u4_t, P139_LadE, 0x005fef28)
#define P139_LadF     GAME_VAR(p139_u4_t, P139_LadF, 0x0060036c)
#define P139_LadPtr   GAME_VAR(uint32_t, P139_LadPtr, 0x0054ea58)      /* адрес текущей записи P139_Ladder */
#define P139_Lad390   GAME_VAR(int32_t, P139_Lad390, 0x00600390)
#define P139_LadN     GAME_VAR(int32_t, P139_LadN, 0x00600394)         /* число записей */
#define P139_Lad398   GAME_VAR(int32_t, P139_Lad398, 0x00600398)
#define P139_IntroStr GAME_VAR(uint32_t, P139_IntroStr, 0x01271044)    /* адрес P139_LadStr */
#ifndef RE_HOOK_BUILD
#pragma push_macro("P139_C818A0") /*gvi*/
#undef P139_C818A0 /*gvi*/
#pragma push_macro("P139_LineNo") /*gvi*/
#undef P139_LineNo /*gvi*/
#pragma push_macro("P139_KeyStA") /*gvi*/
#undef P139_KeyStA /*gvi*/
#pragma push_macro("P139_KeyPrA") /*gvi*/
#undef P139_KeyPrA /*gvi*/
#pragma push_macro("P139_BlinkA") /*gvi*/
#undef P139_BlinkA /*gvi*/
#pragma push_macro("P139_KeyStB") /*gvi*/
#undef P139_KeyStB /*gvi*/
#pragma push_macro("P139_KeyPrB") /*gvi*/
#undef P139_KeyPrB /*gvi*/
#pragma push_macro("P139_BlinkB") /*gvi*/
#undef P139_BlinkB /*gvi*/
extern p139_u6_t P139_C818A0; extern int32_t P139_LineNo, P139_KeyStA, P139_KeyPrA, P139_BlinkA, P139_KeyStB, P139_KeyPrB, P139_BlinkB;
#pragma pop_macro("P139_BlinkB") /*gvi*/
#pragma pop_macro("P139_KeyPrB") /*gvi*/
#pragma pop_macro("P139_KeyStB") /*gvi*/
#pragma pop_macro("P139_BlinkA") /*gvi*/
#pragma pop_macro("P139_KeyPrA") /*gvi*/
#pragma pop_macro("P139_KeyStA") /*gvi*/
#pragma pop_macro("P139_LineNo") /*gvi*/
#pragma pop_macro("P139_C818A0") /*gvi*/
#pragma push_macro("P139_Ladder") /*gvi*/
#undef P139_Ladder /*gvi*/
#pragma push_macro("P139_LadStr") /*gvi*/
#undef P139_LadStr /*gvi*/
extern p139_b1000_t P139_Ladder; extern p139_b400_t P139_LadStr;
#pragma pop_macro("P139_LadStr") /*gvi*/
#pragma pop_macro("P139_Ladder") /*gvi*/
#pragma push_macro("P139_LadA") /*gvi*/
#undef P139_LadA /*gvi*/
#pragma push_macro("P139_LadB") /*gvi*/
#undef P139_LadB /*gvi*/
#pragma push_macro("P139_LadC") /*gvi*/
#undef P139_LadC /*gvi*/
#pragma push_macro("P139_LadD") /*gvi*/
#undef P139_LadD /*gvi*/
#pragma push_macro("P139_LadE") /*gvi*/
#undef P139_LadE /*gvi*/
#pragma push_macro("P139_LadF") /*gvi*/
#undef P139_LadF /*gvi*/
extern p139_u4_t P139_LadA, P139_LadB, P139_LadC, P139_LadD, P139_LadE, P139_LadF;
#pragma pop_macro("P139_LadF") /*gvi*/
#pragma pop_macro("P139_LadE") /*gvi*/
#pragma pop_macro("P139_LadD") /*gvi*/
#pragma pop_macro("P139_LadC") /*gvi*/
#pragma pop_macro("P139_LadB") /*gvi*/
#pragma pop_macro("P139_LadA") /*gvi*/
#pragma push_macro("P139_LadPtr") /*gvi*/
#undef P139_LadPtr /*gvi*/
#pragma push_macro("P139_IntroStr") /*gvi*/
#undef P139_IntroStr /*gvi*/
#pragma push_macro("P139_Lad390") /*gvi*/
#undef P139_Lad390 /*gvi*/
#pragma push_macro("P139_LadN") /*gvi*/
#undef P139_LadN /*gvi*/
#pragma push_macro("P139_Lad398") /*gvi*/
#undef P139_Lad398 /*gvi*/
extern uint32_t P139_LadPtr, P139_IntroStr; extern int32_t P139_Lad390, P139_LadN, P139_Lad398;
#pragma pop_macro("P139_Lad398") /*gvi*/
#pragma pop_macro("P139_LadN") /*gvi*/
#pragma pop_macro("P139_Lad390") /*gvi*/
#pragma pop_macro("P139_IntroStr") /*gvi*/
#pragma pop_macro("P139_LadPtr") /*gvi*/
#endif
int32_t P139_CompileScript(const char *path);              /* 004f4596: 3 — нет памяти, 5 — нет файла, 4 — конец, иначе код ошибки строки */
int32_t P139_TrailLoad(const char *path);                  /* 004fbbfc: трейл (тройки int) в G6_00C80C50, записи 0x14; 1 — успех */
int32_t P139_AddLabel(const char *name, int32_t val, int32_t *list); /* 004f8b0a: list = {n, адрес массива адресов {имя, val}}; 1 — успех */
void    P139_Effects(void);                                /* 004aaf3a: эффекты из списка 010ffb40 по флагам +0x68 */
void    P139_SaveCfg(void);                                /* 00519647: переменные игры → 00c54ee0 → ReplayData\User\$TEMP$.CFG */
void    P139_ReplayEnd(void);                              /* 00519408: сохранение PADS/PINGS, освобождение буферов повтора */
int32_t P139_KeyMenuA(void);                               /* 0040fa60: меню клавиш (таблица 0054c1e0) */
int32_t P139_KeyMenuB(void);                               /* 00410c30: меню клавиш (таблица 0054c530) */
int32_t P139_LadderLoad(void);                             /* 0041b1c0: компиляция DATA\MLADDER.DML; 1 — успех */
/* gvar-img v2.03 begin (tools/gen_gvar_img.py) */
#if !defined(RE_HOOK_BUILD) && !defined(RE_GVAR_PLAIN)
#undef P139_C818A0
#define P139_C818A0 (*(p139_u6_t *)re_gvar(0x00c818a0u, sizeof(p139_u6_t), (void *)&P139_C818A0))
#undef P139_LineNo
#define P139_LineNo (*(int32_t *)re_gvar(0x00c80c54u, sizeof(int32_t), (void *)&P139_LineNo))
#undef P139_KeyStA
#define P139_KeyStA (*(int32_t *)re_gvar(0x005fe75cu, sizeof(int32_t), (void *)&P139_KeyStA))
#undef P139_KeyPrA
#define P139_KeyPrA (*(int32_t *)re_gvar(0x005fe760u, sizeof(int32_t), (void *)&P139_KeyPrA))
#undef P139_BlinkA
#define P139_BlinkA (*(int32_t *)re_gvar(0x005fe76cu, sizeof(int32_t), (void *)&P139_BlinkA))
#undef P139_KeyStB
#define P139_KeyStB (*(int32_t *)re_gvar(0x005fe780u, sizeof(int32_t), (void *)&P139_KeyStB))
#undef P139_KeyPrB
#define P139_KeyPrB (*(int32_t *)re_gvar(0x005fe784u, sizeof(int32_t), (void *)&P139_KeyPrB))
#undef P139_BlinkB
#define P139_BlinkB (*(int32_t *)re_gvar(0x005fe794u, sizeof(int32_t), (void *)&P139_BlinkB))
#undef P139_Ladder
#define P139_Ladder (*(p139_b1000_t *)re_gvar(0x005ff368u, sizeof(p139_b1000_t), (void *)&P139_Ladder))
#undef P139_LadStr
#define P139_LadStr (*(p139_b400_t *)re_gvar(0x005fef38u, sizeof(p139_b400_t), (void *)&P139_LadStr))
#undef P139_LadA
#define P139_LadA (*(p139_u4_t *)re_gvar(0x005ff358u, sizeof(p139_u4_t), (void *)&P139_LadA))
#undef P139_LadB
#define P139_LadB (*(p139_u4_t *)re_gvar(0x005ff348u, sizeof(p139_u4_t), (void *)&P139_LadB))
#undef P139_LadC
#define P139_LadC (*(p139_u4_t *)re_gvar(0x0060037cu, sizeof(p139_u4_t), (void *)&P139_LadC))
#undef P139_LadD
#define P139_LadD (*(p139_u4_t *)re_gvar(0x005ff338u, sizeof(p139_u4_t), (void *)&P139_LadD))
#undef P139_LadE
#define P139_LadE (*(p139_u4_t *)re_gvar(0x005fef28u, sizeof(p139_u4_t), (void *)&P139_LadE))
#undef P139_LadF
#define P139_LadF (*(p139_u4_t *)re_gvar(0x0060036cu, sizeof(p139_u4_t), (void *)&P139_LadF))
#undef P139_LadPtr
#define P139_LadPtr (*(uint32_t *)re_gvar(0x0054ea58u, sizeof(uint32_t), (void *)&P139_LadPtr))
#undef P139_Lad390
#define P139_Lad390 (*(int32_t *)re_gvar(0x00600390u, sizeof(int32_t), (void *)&P139_Lad390))
#undef P139_LadN
#define P139_LadN (*(int32_t *)re_gvar(0x00600394u, sizeof(int32_t), (void *)&P139_LadN))
#undef P139_Lad398
#define P139_Lad398 (*(int32_t *)re_gvar(0x00600398u, sizeof(int32_t), (void *)&P139_Lad398))
#undef P139_IntroStr
#define P139_IntroStr (*(uint32_t *)re_gvar(0x01271044u, sizeof(uint32_t), (void *)&P139_IntroStr))
#endif
/* gvar-img v2.03 end */
