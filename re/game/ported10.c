#include "ported10.h"
#include <string.h>
#ifndef RE_HOOK_BUILD
uint8_t *P10_ScriptPtr; uint8_t *P10_ScriptCtx; uint32_t P10_Tab[0x100];
#endif
static uint16_t rd16(const uint8_t *p){uint16_t v;memcpy(&v,p,2);return v;}
static uint32_t rd32(const uint8_t *p){uint32_t v;memcpy(&v,p,4);return v;}
static void wr16(uint8_t *p,uint16_t v){memcpy(p,&v,2);}
static void wr32(uint8_t *p,uint32_t v){memcpy(p,&v,4);}
void SetTableValue_004F89B7(int32_t idx, uint32_t val) {
  if (P10_Tab[idx * 12] != 1) {
#ifdef RE_HOOK_BUILD
    *(uint32_t *)(uintptr_t)P10_Tab[idx * 12 + 1] = val;
#else
    (void)val;
#endif
  } }
uint32_t ScriptSkipBack_004D1635(void) {
  uint32_t n = rd16(P10_ScriptPtr + 2);
  P10_ScriptPtr = P10_ScriptPtr + 2 - n; return 1; }
uint32_t ScriptReadU32_004D1135(void) {
  P10_ScriptPtr += 2; wr32(P10_ScriptCtx + 0x44, rd32(P10_ScriptPtr)); P10_ScriptPtr += 4; return 1; }
uint32_t ScriptReadPair_004D12CA(void) {
  P10_ScriptPtr += 2; wr32(P10_ScriptCtx + 0x38, 1);
  wr16(P10_ScriptCtx + 0x3c, rd16(P10_ScriptPtr)); P10_ScriptPtr += 2;
  wr16(P10_ScriptCtx + 0x3e, rd16(P10_ScriptPtr)); P10_ScriptPtr += 2; return 1; }
uint32_t ScriptLoopStep_004D133C(void) {
  uint8_t *p2 = P10_ScriptPtr + 4; uint16_t c = rd16(p2);
  if (c == 0) { P10_ScriptPtr = p2; wr16(p2, rd16(P10_ScriptPtr - 2)); P10_ScriptPtr += 2; }
  else wr16(p2, (uint16_t)(c - 1));
  return c == 0; }
