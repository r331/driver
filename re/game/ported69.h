#pragma once
#include "gvar.h"
#include "unported.h"
#include "ported4.h"
#include "ported6.h"
#include "ported12.h"
#include "ported26.h"
#include "ported33.h"
#include "ported42.h"
#include "ported44.h"
#include "ported55.h"
#include "menustate.h"
#include <stdint.h>
/* Шаг D: 6 функций — подписи отсчёта («3 2 1 GO», CHECKPOINT, FINISHED) по языку, подсчёт очков по порогам,
   кадр сцены (Glide: смешивание/комбинирование цвета, туман), освобождение накладок, освобождение устройств Glide.
   Все cdecl (метки __thiscall/__fastcall у 004a3630/004a0d5f/004246f0 ложные — ecx не читается). */
typedef uint8_t P69_Blk[0x48];
#define P69_Num3      GAME_VAR(uint32_t, P69_Num3, 0x01134298)
#define P69_Num2      GAME_VAR(uint32_t, P69_Num2, 0x01134264)
#define P69_Num1      GAME_VAR(uint32_t, P69_Num1, 0x01134294)
#define P69_Go        GAME_VAR(uint32_t, P69_Go, 0x0113429c)
#define P69_Check     GAME_VAR(uint32_t, P69_Check, 0x0113428c)
#define P69_Finish    GAME_VAR(uint32_t, P69_Finish, 0x01134288)
#define P69_MsgBlk    GAME_VAR(P69_Blk, P69_MsgBlk, 0x011342a0)      /* 0x48 байт, обнуляется */
#define P69_MsgW      GAME_VAR(int32_t, P69_MsgW, 0x011342d4)         /* = 0x8c */
#define P69_Score     GAME_VAR(int32_t, P69_Score, 0x011368c4)
#define P69_Bonus     GAME_VAR(int32_t, P69_Bonus, 0x01136ac8)
#define P69_ScoreCpy  GAME_VAR(int32_t, P69_ScoreCpy, 0x01271068)
#define P69_BlendOn   GAME_VAR(uint8_t, P69_BlendOn, 0x0125f3e4)
#define P69_OvlOn     GAME_VAR(int32_t, P69_OvlOn, 0x01123210)
#define P69_DevOn     GAME_VAR(int32_t, P69_DevOn, 0x00b1c0d0)
#define P69_TBASE     0x01136940u                                     /* адрес таблицы порогов (79 слов), указатели в 01136a80[] — её адреса */
#define P69_TEND      0x01136a78u
typedef uint32_t P69_ThrTab[79];
typedef uint32_t P69_PtrTab[19];                                      /* 01136a80: [0] — служебное слово, [1..18] — указатели; индекс c читает [c+1]/[c] */
typedef int32_t P69_Pts[18];
#define P69_Thr       GAME_VAR(P69_ThrTab, P69_Thr, 0x01136940)
#define P69_Ptrs      GAME_VAR(P69_PtrTab, P69_Ptrs, 0x01136a80)
#define P69_PtsTab    GAME_VAR(P69_Pts, P69_PtsTab, 0x00551528)
#ifndef RE_HOOK_BUILD
#pragma push_macro("P69_Num3") /*gvi*/
#undef P69_Num3 /*gvi*/
#pragma push_macro("P69_Num2") /*gvi*/
#undef P69_Num2 /*gvi*/
#pragma push_macro("P69_Num1") /*gvi*/
#undef P69_Num1 /*gvi*/
#pragma push_macro("P69_Go") /*gvi*/
#undef P69_Go /*gvi*/
#pragma push_macro("P69_Check") /*gvi*/
#undef P69_Check /*gvi*/
#pragma push_macro("P69_Finish") /*gvi*/
#undef P69_Finish /*gvi*/
#pragma push_macro("P69_MsgBlk") /*gvi*/
#undef P69_MsgBlk /*gvi*/
extern uint32_t P69_Num3, P69_Num2, P69_Num1, P69_Go, P69_Check, P69_Finish; extern P69_Blk P69_MsgBlk;
#pragma pop_macro("P69_MsgBlk") /*gvi*/
#pragma pop_macro("P69_Finish") /*gvi*/
#pragma pop_macro("P69_Check") /*gvi*/
#pragma pop_macro("P69_Go") /*gvi*/
#pragma pop_macro("P69_Num1") /*gvi*/
#pragma pop_macro("P69_Num2") /*gvi*/
#pragma pop_macro("P69_Num3") /*gvi*/
#pragma push_macro("P69_MsgW") /*gvi*/
#undef P69_MsgW /*gvi*/
#pragma push_macro("P69_Score") /*gvi*/
#undef P69_Score /*gvi*/
#pragma push_macro("P69_Bonus") /*gvi*/
#undef P69_Bonus /*gvi*/
#pragma push_macro("P69_ScoreCpy") /*gvi*/
#undef P69_ScoreCpy /*gvi*/
#pragma push_macro("P69_OvlOn") /*gvi*/
#undef P69_OvlOn /*gvi*/
#pragma push_macro("P69_DevOn") /*gvi*/
#undef P69_DevOn /*gvi*/
#pragma push_macro("P69_BlendOn") /*gvi*/
#undef P69_BlendOn /*gvi*/
extern int32_t P69_MsgW, P69_Score, P69_Bonus, P69_ScoreCpy, P69_OvlOn, P69_DevOn; extern uint8_t P69_BlendOn;
#pragma pop_macro("P69_BlendOn") /*gvi*/
#pragma pop_macro("P69_DevOn") /*gvi*/
#pragma pop_macro("P69_OvlOn") /*gvi*/
#pragma pop_macro("P69_ScoreCpy") /*gvi*/
#pragma pop_macro("P69_Bonus") /*gvi*/
#pragma pop_macro("P69_Score") /*gvi*/
#pragma pop_macro("P69_MsgW") /*gvi*/
#pragma push_macro("P69_Thr") /*gvi*/
#undef P69_Thr /*gvi*/
#pragma push_macro("P69_Ptrs") /*gvi*/
#undef P69_Ptrs /*gvi*/
#pragma push_macro("P69_PtsTab") /*gvi*/
#undef P69_PtsTab /*gvi*/
extern P69_ThrTab P69_Thr; extern P69_PtrTab P69_Ptrs; extern P69_Pts P69_PtsTab;
#pragma pop_macro("P69_PtsTab") /*gvi*/
#pragma pop_macro("P69_Ptrs") /*gvi*/
#pragma pop_macro("P69_Thr") /*gvi*/
#endif
void    P69_SetupMsgs(void);              /* 004a3630: имена надписей отсчёта по языку P55_Lang (0/5 EN, 1 FR, 2 GR, 3 SP, 4 IT) */
uint8_t P69_Bracket(uint32_t v);          /* 004a0cca: номер порога (0..0x12) в таблице, 0x12 — выше всех */
int32_t P69_AddScore(int32_t v);          /* 004a0d5f: 0xff00 — бонус/120*100; иначе таблица очков по порогу; не больше 999999; всегда 0 */
void    P69_ReleaseOverlays(void);        /* 004b3ddb: grAlphaBlendFunction(4,0,4,0) и 004b33d8 для 200 записей с флагом 2 */
void    P69_SceneFrame(void);             /* 004aaea6: кадр сцены */
void    P69_FreeDevices(void);            /* 004246f0: освободить указатели устройств Glide, обнулить, FreeGlide */
void    P69_InitConsts(void);             /* native: таблицы очков (00551528) */
/* gvar-img v2.03 begin (tools/gen_gvar_img.py) */
#if !defined(RE_HOOK_BUILD) && !defined(RE_GVAR_PLAIN)
#undef P69_Num3
#define P69_Num3 (*(uint32_t *)re_gvar(0x01134298u, sizeof(uint32_t), (void *)&P69_Num3))
#undef P69_Num2
#define P69_Num2 (*(uint32_t *)re_gvar(0x01134264u, sizeof(uint32_t), (void *)&P69_Num2))
#undef P69_Num1
#define P69_Num1 (*(uint32_t *)re_gvar(0x01134294u, sizeof(uint32_t), (void *)&P69_Num1))
#undef P69_Go
#define P69_Go (*(uint32_t *)re_gvar(0x0113429cu, sizeof(uint32_t), (void *)&P69_Go))
#undef P69_Check
#define P69_Check (*(uint32_t *)re_gvar(0x0113428cu, sizeof(uint32_t), (void *)&P69_Check))
#undef P69_Finish
#define P69_Finish (*(uint32_t *)re_gvar(0x01134288u, sizeof(uint32_t), (void *)&P69_Finish))
#undef P69_MsgBlk
#define P69_MsgBlk (*(P69_Blk *)re_gvar(0x011342a0u, sizeof(P69_Blk), (void *)&P69_MsgBlk))
#undef P69_MsgW
#define P69_MsgW (*(int32_t *)re_gvar(0x011342d4u, sizeof(int32_t), (void *)&P69_MsgW))
#undef P69_Score
#define P69_Score (*(int32_t *)re_gvar(0x011368c4u, sizeof(int32_t), (void *)&P69_Score))
#undef P69_Bonus
#define P69_Bonus (*(int32_t *)re_gvar(0x01136ac8u, sizeof(int32_t), (void *)&P69_Bonus))
#undef P69_ScoreCpy
#define P69_ScoreCpy (*(int32_t *)re_gvar(0x01271068u, sizeof(int32_t), (void *)&P69_ScoreCpy))
#undef P69_BlendOn
#define P69_BlendOn (*(uint8_t *)re_gvar(0x0125f3e4u, sizeof(uint8_t), (void *)&P69_BlendOn))
#undef P69_OvlOn
#define P69_OvlOn (*(int32_t *)re_gvar(0x01123210u, sizeof(int32_t), (void *)&P69_OvlOn))
#undef P69_DevOn
#define P69_DevOn (*(int32_t *)re_gvar(0x00b1c0d0u, sizeof(int32_t), (void *)&P69_DevOn))
#undef P69_Thr
#define P69_Thr (*(P69_ThrTab *)re_gvar(0x01136940u, sizeof(P69_ThrTab), (void *)&P69_Thr))
#undef P69_Ptrs
#define P69_Ptrs (*(P69_PtrTab *)re_gvar(0x01136a80u, sizeof(P69_PtrTab), (void *)&P69_Ptrs))
#undef P69_PtsTab
#define P69_PtsTab (*(P69_Pts *)re_gvar(0x00551528u, sizeof(P69_Pts), (void *)&P69_PtsTab))
#endif
/* gvar-img v2.03 end */
