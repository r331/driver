#pragma once
#include <stdint.h>
#include "gvar.h"
/* v1.91: ported146 — исполнение команды скрипта миссии 004f8e0c (MScript, вызывается из такта 004f472b = P127) и
   004a37d9 (позиция/режим блока сообщения 011342a0, найдена только через thunk 0040170d). cdecl. */
typedef int32_t p146_gosub_t[100];   /* 00c81300..00c8148f: стек возвратов GoSub (номер команды), глубина — 00c80f7c */
_Static_assert(sizeof(p146_gosub_t) == 0x190, "p146_gosub_t");
#define P146_GoSub   GAME_VAR(p146_gosub_t, P146_GoSub, 0x00c81300)
#ifndef RE_HOOK_BUILD
extern p146_gosub_t P146_GoSub;
#endif
int32_t P146_ScriptCmd(void *cmd);           /* 004f8e0c: код (0 — команда выполнена, 0xb — звук/музыка, 0xd — ждать/неизвестна) */
void    P146_MsgPos(int32_t a, int32_t b);   /* 004a37d9: 011342c0 ← a, 011342c8 ← b, 011342b4 ← 2, 011342b0 |= 0x200 */
