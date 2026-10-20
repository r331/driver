/* ported10.c — small helpers of a bytecode mini-interpreter (English overview).
   P10_ScriptPtr (00d12414) is the instruction pointer into a stream of 16-bit opcodes with inline operands;
   P10_ScriptCtx (00d1240c) points at the context record the opcodes write into.
   TODO(RE): which script format this is (004d1xxx handlers; cutscene/animation?) is not established.
   SetTableValue_004F89B7 writes a mission-script variable (table 0056dc30, 0x30 bytes per entry). */
#include "ported10.h"
#include <string.h>
#ifndef RE_HOOK_BUILD
#include "ported42.h"
#include "reptr.h"
#endif
#ifndef RE_HOOK_BUILD
uint8_t *P10_ScriptPtr; uint8_t *P10_ScriptCtx; uint32_t P10_Tab[0x100];
#endif
static uint16_t rd16(const uint8_t *p){uint16_t v;memcpy(&v,p,2);return v;}
static uint32_t rd32(const uint8_t *p){uint32_t v;memcpy(&v,p,4);return v;}
static void wr16(uint8_t *p,uint16_t v){memcpy(p,&v,2);}
static void wr32(uint8_t *p,uint32_t v){memcpy(p,&v,4);}
/* SetTableValue_004F89B7 — Game.exe 004f89b7, cdecl.  Stores val into mission-script variable idx.
   Table entry (0x30 bytes, 12 dwords): word 0 = type (1 = read-only / not a memory variable),
   word 1 = address of the game variable the script name is bound to.
   Hook build: writes through the raw Game.exe address.  Native: uses P42_Vars and translates the
   address with re_ptr; out-of-range idx or an address with no native counterpart is ignored. */
void SetTableValue_004F89B7(int32_t idx, uint32_t val) {
#ifdef RE_HOOK_BUILD
  if (P10_Tab[idx * 12] != 1) *(uint32_t *)(uintptr_t)P10_Tab[idx * 12 + 1] = val;
#else
  /* v2.06: native — таблица переменных скрипта P42_Vars (0056dc10: type +0x20 = 0056dc30, addr +0x24 = 0056dc34), запись по re_ptr.
     Раньше native ничего не писал: DODGY_SPEED_FACTOR 00b87e1c (множитель газа игрока) оставался 0 — машина не ехала. */
  if (idx >= 0 && idx < (int32_t)(sizeof P42_Vars / sizeof P42_Vars[0]) && P42_Vars[idx].type != 1) {
    uint32_t *p = (uint32_t *)re_ptr(P42_Vars[idx].addr);
    if (p != NULL) *p = val;
  }
#endif
}
/* ScriptSkipBack_004D1635 — Game.exe 004d1635.  Backward jump: operand u16 at ip+2 is the distance,
   new ip = ip + 2 - n.  Returns 1 (continue). */
uint32_t ScriptSkipBack_004D1635(void) {
  uint32_t n = rd16(P10_ScriptPtr + 2);
  P10_ScriptPtr = P10_ScriptPtr + 2 - n; return 1; }
/* ScriptReadU32_004D1135 — Game.exe 004d1135.  Skips the opcode, copies the u32 operand to ctx+0x44.
   TODO(RE): meaning of ctx+0x44 unknown.  Returns 1. */
uint32_t ScriptReadU32_004D1135(void) {
  P10_ScriptPtr += 2; wr32(P10_ScriptCtx + 0x44, rd32(P10_ScriptPtr)); P10_ScriptPtr += 4; return 1; }
/* ScriptReadPair_004D12CA — Game.exe 004d12ca.  Sets ctx+0x38 = 1 and copies two u16 operands to
   ctx+0x3c / ctx+0x3e.  TODO(RE): meaning of the pair (a 2-D value?) unknown.  Returns 1. */
uint32_t ScriptReadPair_004D12CA(void) {
  P10_ScriptPtr += 2; wr32(P10_ScriptCtx + 0x38, 1);
  wr16(P10_ScriptCtx + 0x3c, rd16(P10_ScriptPtr)); P10_ScriptPtr += 2;
  wr16(P10_ScriptCtx + 0x3e, rd16(P10_ScriptPtr)); P10_ScriptPtr += 2; return 1; }
/* ScriptLoopStep_004D133C — Game.exe 004d133c.  Loop counter opcode: the u16 at ip+4 is a live counter.
   Counter non-zero -> decrement it, return 0 (caller repeats the loop).
   Counter zero -> reload it from the u16 just before the opcode (ip-2, the loop's initial count),
   step past it and return 1 (loop finished). */
uint32_t ScriptLoopStep_004D133C(void) {
  uint8_t *p2 = P10_ScriptPtr + 4; uint16_t c = rd16(p2);
  if (c == 0) { P10_ScriptPtr = p2; wr16(p2, rd16(P10_ScriptPtr - 2)); P10_ScriptPtr += 2; }
  else wr16(p2, (uint16_t)(c - 1));
  return c == 0; }
