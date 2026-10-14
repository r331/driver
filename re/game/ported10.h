#pragma once
#include "gvar.h"
/* Партия v0.10: мини-интерпретатор скрипта (указатель команд 00d12414) */
#define P10_ScriptPtr GAME_VAR(uint8_t *, P10_ScriptPtr, 0x00d12414)
#define P10_ScriptCtx GAME_VAR(uint8_t *, P10_ScriptCtx, 0x00d1240c)
#ifdef RE_HOOK_BUILD
#define P10_Tab ((uint32_t *)(uintptr_t)0x0056dc30)
#endif
#ifndef RE_HOOK_BUILD
extern uint8_t *P10_ScriptPtr;
extern uint8_t *P10_ScriptCtx;
extern uint32_t P10_Tab[];
#endif
void SetTableValue_004F89B7(int32_t idx, uint32_t val);
uint32_t ScriptSkipBack_004D1635(void);
uint32_t ScriptReadU32_004D1135(void);
uint32_t ScriptReadPair_004D12CA(void);
uint32_t ScriptLoopStep_004D133C(void);
