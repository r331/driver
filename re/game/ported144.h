#pragma once
#include <stdint.h>
#include "gvar.h"
/* v1.89: ported144 — эффект флага 0x20000 из 004aaf3a (004b588e): вспышка значком CARLYT/COPFLARE с цветом и размером из
   .data 00553870 (те же 14 записей 0x1c, что у 004b6deb: game/p111_data.h, tools/gen_p111_data.py) и след размытия по
   истории экранных позиций (01105da0 — P143_LampHist при флаге 0x800000, иначе запись 011232e0). cdecl. */
typedef uint8_t p144_rec28_t[0x28];
#define P144_Hist0 GAME_VAR(p144_rec28_t, P144_Hist0, 0x011232e0)   /* история позиций для объектов без флага 0x800000 (фонарь 0) */
#ifndef RE_HOOK_BUILD
extern p144_rec28_t P144_Hist0;
#endif
void P144_FlagFx(const uint8_t *o);   /* 004b588e */
