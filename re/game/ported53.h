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
#pragma push_macro("P53_MenuSel") /*gvi*/
#undef P53_MenuSel /*gvi*/
#pragma push_macro("P53_FlagF9F4") /*gvi*/
#undef P53_FlagF9F4 /*gvi*/
#pragma push_macro("P53_Var2634") /*gvi*/
#undef P53_Var2634 /*gvi*/
extern int32_t P53_MenuSel, P53_FlagF9F4, P53_Var2634;
#pragma pop_macro("P53_Var2634") /*gvi*/
#pragma pop_macro("P53_FlagF9F4") /*gvi*/
#pragma pop_macro("P53_MenuSel") /*gvi*/
#pragma push_macro("P53_Var2640") /*gvi*/
#undef P53_Var2640 /*gvi*/
#pragma push_macro("P53_Mrk") /*gvi*/
#undef P53_Mrk /*gvi*/
extern uint32_t P53_Var2640; extern p53_mrk_t P53_Mrk;
#pragma pop_macro("P53_Mrk") /*gvi*/
#pragma pop_macro("P53_Var2640") /*gvi*/
#pragma push_macro("P53_Ang2702") /*gvi*/
#undef P53_Ang2702 /*gvi*/
extern int16_t P53_Ang2702;
#pragma pop_macro("P53_Ang2702") /*gvi*/
#pragma push_macro("P53_ModeTab") /*gvi*/
#undef P53_ModeTab /*gvi*/
#pragma push_macro("P53_TexTab") /*gvi*/
#undef P53_TexTab /*gvi*/
extern p53_modetab_t P53_ModeTab; extern p53_textab_t P53_TexTab;
#pragma pop_macro("P53_TexTab") /*gvi*/
#pragma pop_macro("P53_ModeTab") /*gvi*/
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
/* gvar-img v2.03 begin (tools/gen_gvar_img.py) */
#if !defined(RE_HOOK_BUILD) && !defined(RE_GVAR_PLAIN)
#undef P53_MenuSel
#define P53_MenuSel (*(int32_t *)re_gvar(0x01271064u, sizeof(int32_t), (void *)&P53_MenuSel))
#undef P53_FlagF9F4
#define P53_FlagF9F4 (*(int32_t *)re_gvar(0x00bdf9f4u, sizeof(int32_t), (void *)&P53_FlagF9F4))
#undef P53_Var2640
#define P53_Var2640 (*(uint32_t *)re_gvar(0x00d02640u, sizeof(uint32_t), (void *)&P53_Var2640))
#undef P53_Mrk
#define P53_Mrk (*(p53_mrk_t *)re_gvar(0x00d026a0u, sizeof(p53_mrk_t), (void *)&P53_Mrk))
#undef P53_Var2634
#define P53_Var2634 (*(int32_t *)re_gvar(0x00d02634u, sizeof(int32_t), (void *)&P53_Var2634))
#undef P53_Ang2702
#define P53_Ang2702 (*(int16_t *)re_gvar(0x00d02702u, sizeof(int16_t), (void *)&P53_Ang2702))
#undef P53_ModeTab
#define P53_ModeTab (*(p53_modetab_t *)re_gvar(0x0054d890u, sizeof(p53_modetab_t), (void *)&P53_ModeTab))
#undef P53_TexTab
#define P53_TexTab (*(p53_textab_t *)re_gvar(0x00621c4cu, sizeof(p53_textab_t), (void *)&P53_TexTab))
#endif
/* gvar-img v2.03 end */
