#pragma once
#include "gvar.h"
#include "unported.h"
#include "crt.h"
#include "ported5.h"
#include "ported8.h"
#include "ported11.h"
#include "ported12.h"
#include "ported22.h"
#include "ported27.h"
#include "ported32.h"
#include "ported42.h"
#include "ported46.h"
#include "ported51.h"
#include "ported52.h"
#include "menustate.h"
#include "smallfuncs.h"
#include "widgets.h"
#include "noop.h"
#include <stdint.h>
/* Мелкие функции (шаг D): шаг границ, ввод имени в меню, выбор текстурного источника, поиск узла текстуры,
   вызов 00500937 со стековой структурой, чтение файла целиком, три меню-действия (004161b3/004046c8/00414638).
   Все cdecl, кроме 0041f76f (stdcall ret 0x10 — переходник в re_hook). */
#define P53_MenuSel   GAME_VAR(int32_t, P53_MenuSel, 0x01271064)   /* выбранная строка меню */
#define P53_FlagF9F4  GAME_VAR(int32_t, P53_FlagF9F4, 0x00bdf9f4)
#define P53_Var2640   GAME_VAR(uint32_t, P53_Var2640, 0x00d02640)
/* v1.58: маркер-вертолёт 00d026a0..00d026bb — одна float-таблица P53_Mrk: позиция a0/a4/a8 (+ac), скорость b0/b4/b8.
   Прежние P53_Var26A0..AC, P99_Mrk26B0/B8, P81_Span — макросы над ней (P81_Span = скорость по y, 00d026b4). */
typedef float p53_mrk_t[7];
#define P53_Mrk       GAME_VAR(p53_mrk_t, P53_Mrk, 0x00d026a0)
#define P53_Var26A0   (P53_Mrk[0])
#define P53_Var26A4   (P53_Mrk[1])
#define P53_Var26A8   (P53_Mrk[2])
#define P53_Var26AC   (P53_Mrk[3])
#define P99_Mrk26B0   (P53_Mrk[4])
#define P81_Span      (P53_Mrk[5])
#define P99_Mrk26B8   (P53_Mrk[6])
#define P53_Var2634   GAME_VAR(int32_t, P53_Var2634, 0x00d02634)
#define P53_Ang2702   GAME_VAR(int16_t, P53_Ang2702, 0x00d02702)
typedef uint32_t p53_modetab_t[12 * 8];
typedef uint8_t  p53_textab_t[32 * 32];
#define P53_ModeTab   GAME_VAR(p53_modetab_t, P53_ModeTab, 0x0054d890)   /* по 0x20 байт на режим, 8 слов */
#define P53_TexTab    GAME_VAR(p53_textab_t, P53_TexTab, 0x00621c4c)     /* по 0x20 байт, первое поле — дескриптор */
#ifndef RE_HOOK_BUILD
extern int32_t P53_MenuSel, P53_FlagF9F4, P53_Var2634;
extern uint32_t P53_Var2640; extern p53_mrk_t P53_Mrk;
extern int16_t P53_Ang2702;
extern p53_modetab_t P53_ModeTab; extern p53_textab_t P53_TexTab;
#endif
void    P53_StepBounds(void);                              /* 004d6354: слот 0xf свободен → следующая запись границ или сброс */
void    P53_NameEntryKey(int32_t key);                     /* 005101f0 (после 0040efd5): ввод символа имени (-3 отмена, -2 принять, -1 стереть) */
void    P53_NameEntry(void);                               /* 005101f0 */
void    P53_SetTexSource(int32_t a, uint32_t addr, int32_t c, uint32_t info);  /* v2.01: info — адрес GrTexInfo (re_addr) */ /* 0041f76f (stdcall ret 0x10) */
int32_t P53_TexLookup(int32_t handle, int32_t b, int32_t c, int32_t d);          /* 0041d63b */
void    P53_CallWithStateP(const float *pos, uint8_t *car, int32_t c);              /* v1.74 */
void    P53_CallWithState(int32_t a, int32_t b, int32_t c);                      /* 00500154 */
int32_t P53_ReadWholeFile(const char *name, void *buf);                          /* 004d303a: размер или 0 */
int32_t P53_MenuA(void);                                   /* 004161b3 */
int32_t P53_MenuB(void);                                   /* 004046c8 */
int32_t P53_MenuC(void);                                   /* 00414638 */
