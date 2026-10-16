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
extern p139_u6_t P139_C818A0; extern int32_t P139_LineNo, P139_KeyStA, P139_KeyPrA, P139_BlinkA, P139_KeyStB, P139_KeyPrB, P139_BlinkB;
extern p139_b1000_t P139_Ladder; extern p139_b400_t P139_LadStr;
extern p139_u4_t P139_LadA, P139_LadB, P139_LadC, P139_LadD, P139_LadE, P139_LadF;
extern uint32_t P139_LadPtr, P139_IntroStr; extern int32_t P139_Lad390, P139_LadN, P139_Lad398;
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
