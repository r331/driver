/* v1.57, ported112 — восстановлено из Game.exe. Все функции cdecl (ret без операнда проверен work/rets.py), кроме 0041f4a1
   (stdcall, ret 0x10 — переходник ставит re_hook по stdcall_tbl.h; метка __thiscall ложная: ecx не читается).
   004d09fd / 004d1765 / 004d0734 — опкоды скрипта .data 0055fcac (движение контекста к точке; k_fns в game/reptr.c),
   0041f4a1 — загрузка эмулируемой текстуры слота по адресу TMU (8/16 бит, сброс палитры слота),
   004a9bb0 — лицо в титрах (рамка + значок по центру 960), 004a77b0 — такт погони/копов (уровень розыска 00d11a5c),
   004cfe69 — запуск записей скрипта с флагом 8 по номеру, 004cf123 — проверка триггеров записей скрипта (радиус/клетка),
   004e7755 / 004e7613 — значок в масштабе экрана (полный / полоса по доле num/den), 004c68a7 — шкала камер режиссёра. */
#pragma once
#include <stdint.h>
#include "gvar.h"
#define P112_Wanted GAME_VAR(int32_t, P112_Wanted, 0x0112b2b4)   /* флаг «максимальный розыск» (00d11a5c == 0xfff) */
#ifndef RE_HOOK_BUILD
#pragma push_macro("P112_Wanted") /*gvi*/
#undef P112_Wanted /*gvi*/
extern int32_t P112_Wanted;
#pragma pop_macro("P112_Wanted") /*gvi*/
#endif
int32_t P112_OpMoveTo(void);                                                       /* 004d09fd */
int32_t P112_OpMoveCur(void);                                                      /* 004d1765 */
int32_t P112_OpMoveCurve(void);                                                    /* 004d0734 */
void    P112_TexDownload(int32_t tmu, uint32_t addr, int32_t evenOdd, const uint8_t *info); /* 0041f4a1 (stdcall) */
void    P112_FaceIcon(uint8_t *rec, int32_t y);                                    /* 004a9bb0 */
void    P112_ChaseTick(void);                                                      /* 004a77b0 */
void    P112_ScriptRunId(uint16_t id);                                             /* 004cfe69 */
void    P112_ScriptTriggers(void);                                                 /* 004cf123 */
void    P112_IconScaled(const uint8_t *ic, float x, float y, float sw, float sh);  /* 004e7755 */
void    P112_IconBar(const uint8_t *ic, float x, float y, int32_t num, int32_t den); /* 004e7613 */
void    P112_DirTimeline(int32_t frame);                                           /* 004c68a7 */
/* gvar-img v2.03 begin (tools/gen_gvar_img.py) */
#if !defined(RE_HOOK_BUILD) && !defined(RE_GVAR_PLAIN)
#undef P112_Wanted
#define P112_Wanted (*(int32_t *)re_gvar(0x0112b2b4u, sizeof(int32_t), (void *)&P112_Wanted))
#endif
/* gvar-img v2.03 end */
