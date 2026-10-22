/* smallfuncs.c — tiny Game.exe functions, one or two lines each (English overview).  The function name carries
   the Game.exe address and a descriptive name, so the comments are per group: empty stubs, single-field
   setters, index pools (free-index stacks), vector helpers, opcodes of the 004d1xxx bytecode interpreter
   (see ported10.c) and menu highlight setters.  The globals S_<address> are named by Game.exe address.
   U32/I32/U16(p, o) read/write a field at byte offset o of p.  All cdecl. */
#include "smallfuncs.h"
#include <stdint.h>
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("S_00549B04")
#undef S_00549B04
#pragma push_macro("S_00549B04") /*gvi*/
#undef S_00549B04 /*gvi*/
sf_bytes_t S_00549B04;
#pragma pop_macro("S_00549B04") /*gvi*/
#pragma pop_macro("S_00549B04")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("S_0054E44C")
#undef S_0054E44C
#pragma push_macro("S_0054E44C") /*gvi*/
#undef S_0054E44C /*gvi*/
sf_bytes_t S_0054E44C;
#pragma pop_macro("S_0054E44C") /*gvi*/
#pragma pop_macro("S_0054E44C")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("S_0054E44D")
#undef S_0054E44D
#pragma push_macro("S_0054E44D") /*gvi*/
#undef S_0054E44D /*gvi*/
sf_bytes_t S_0054E44D;
#pragma pop_macro("S_0054E44D") /*gvi*/
#pragma pop_macro("S_0054E44D")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("S_0054E44E")
#undef S_0054E44E
#pragma push_macro("S_0054E44E") /*gvi*/
#undef S_0054E44E /*gvi*/
sf_bytes_t S_0054E44E;
#pragma pop_macro("S_0054E44E") /*gvi*/
#pragma pop_macro("S_0054E44E")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("S_0054E6AC")
#undef S_0054E6AC
#pragma push_macro("S_0054E6AC") /*gvi*/
#undef S_0054E6AC /*gvi*/
sf_bytes_t S_0054E6AC;
#pragma pop_macro("S_0054E6AC") /*gvi*/
#pragma pop_macro("S_0054E6AC")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("S_0054E6AD")
#undef S_0054E6AD
#pragma push_macro("S_0054E6AD") /*gvi*/
#undef S_0054E6AD /*gvi*/
sf_bytes_t S_0054E6AD;
#pragma pop_macro("S_0054E6AD") /*gvi*/
#pragma pop_macro("S_0054E6AD")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("S_0054E6AE")
#undef S_0054E6AE
#pragma push_macro("S_0054E6AE") /*gvi*/
#undef S_0054E6AE /*gvi*/
sf_bytes_t S_0054E6AE;
#pragma pop_macro("S_0054E6AE") /*gvi*/
#pragma pop_macro("S_0054E6AE")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("S_00560A88")
#undef S_00560A88
#pragma push_macro("S_00560A88") /*gvi*/
#undef S_00560A88 /*gvi*/
sf_bytes_t S_00560A88;
#pragma pop_macro("S_00560A88") /*gvi*/
#pragma pop_macro("S_00560A88")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("S_0057B658")
#undef S_0057B658
#pragma push_macro("S_0057B658") /*gvi*/
#undef S_0057B658 /*gvi*/
int32_t S_0057B658;
#pragma pop_macro("S_0057B658") /*gvi*/
#pragma pop_macro("S_0057B658")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("S_0057B65C")
#undef S_0057B65C
#pragma push_macro("S_0057B65C") /*gvi*/
#undef S_0057B65C /*gvi*/
int32_t S_0057B65C;
#pragma pop_macro("S_0057B65C") /*gvi*/
#pragma pop_macro("S_0057B65C")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("S_005FEA30")
#undef S_005FEA30
#pragma push_macro("S_005FEA30") /*gvi*/
#undef S_005FEA30 /*gvi*/
int32_t S_005FEA30;
#pragma pop_macro("S_005FEA30") /*gvi*/
#pragma pop_macro("S_005FEA30")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("S_005FEA8C")
#undef S_005FEA8C
#pragma push_macro("S_005FEA8C") /*gvi*/
#undef S_005FEA8C /*gvi*/
int32_t S_005FEA8C;
#pragma pop_macro("S_005FEA8C") /*gvi*/
#pragma pop_macro("S_005FEA8C")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("S_00A421D8")
#undef S_00A421D8
#pragma push_macro("S_00A421D8") /*gvi*/
#undef S_00A421D8 /*gvi*/
uint32_t S_00A421D8;
#pragma pop_macro("S_00A421D8") /*gvi*/
#pragma pop_macro("S_00A421D8")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("S_00B31E40")
#undef S_00B31E40
#pragma push_macro("S_00B31E40") /*gvi*/
#undef S_00B31E40 /*gvi*/
uint8_t S_00B31E40;
#pragma pop_macro("S_00B31E40") /*gvi*/
#pragma pop_macro("S_00B31E40")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("S_00B31E41")
#undef S_00B31E41
#pragma push_macro("S_00B31E41") /*gvi*/
#undef S_00B31E41 /*gvi*/
uint8_t S_00B31E41;
#pragma pop_macro("S_00B31E41") /*gvi*/
#pragma pop_macro("S_00B31E41")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("S_00B31E42")
#undef S_00B31E42
#pragma push_macro("S_00B31E42") /*gvi*/
#undef S_00B31E42 /*gvi*/
uint8_t S_00B31E42;
#pragma pop_macro("S_00B31E42") /*gvi*/
#pragma pop_macro("S_00B31E42")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("S_00B31E43")
#undef S_00B31E43
#pragma push_macro("S_00B31E43") /*gvi*/
#undef S_00B31E43 /*gvi*/
uint8_t S_00B31E43;
#pragma pop_macro("S_00B31E43") /*gvi*/
#pragma pop_macro("S_00B31E43")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("S_00B5A76C")
#undef S_00B5A76C
#pragma push_macro("S_00B5A76C") /*gvi*/
#undef S_00B5A76C /*gvi*/
int32_t S_00B5A76C;
#pragma pop_macro("S_00B5A76C") /*gvi*/
#pragma pop_macro("S_00B5A76C")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("S_00B5A770")
#undef S_00B5A770
#pragma push_macro("S_00B5A770") /*gvi*/
#undef S_00B5A770 /*gvi*/
int32_t S_00B5A770;
#pragma pop_macro("S_00B5A770") /*gvi*/
#pragma pop_macro("S_00B5A770")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("S_00B5A77C")
#undef S_00B5A77C
#pragma push_macro("S_00B5A77C") /*gvi*/
#undef S_00B5A77C /*gvi*/
int32_t S_00B5A77C;
#pragma pop_macro("S_00B5A77C") /*gvi*/
#pragma pop_macro("S_00B5A77C")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("S_00B5A834")
#undef S_00B5A834
#pragma push_macro("S_00B5A834") /*gvi*/
#undef S_00B5A834 /*gvi*/
uint8_t S_00B5A834;
#pragma pop_macro("S_00B5A834") /*gvi*/
#pragma pop_macro("S_00B5A834")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("S_00B5A835")
#undef S_00B5A835
#pragma push_macro("S_00B5A835") /*gvi*/
#undef S_00B5A835 /*gvi*/
uint8_t S_00B5A835;
#pragma pop_macro("S_00B5A835") /*gvi*/
#pragma pop_macro("S_00B5A835")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("S_00B5A836")
#undef S_00B5A836
#pragma push_macro("S_00B5A836") /*gvi*/
#undef S_00B5A836 /*gvi*/
uint8_t S_00B5A836;
#pragma pop_macro("S_00B5A836") /*gvi*/
#pragma pop_macro("S_00B5A836")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("S_00B93E6C")
#undef S_00B93E6C
#pragma push_macro("S_00B93E6C") /*gvi*/
#undef S_00B93E6C /*gvi*/
uint32_t S_00B93E6C;
#pragma pop_macro("S_00B93E6C") /*gvi*/
#pragma pop_macro("S_00B93E6C")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("S_00B93E70")
#undef S_00B93E70
#pragma push_macro("S_00B93E70") /*gvi*/
#undef S_00B93E70 /*gvi*/
uint32_t S_00B93E70;
#pragma pop_macro("S_00B93E70") /*gvi*/
#pragma pop_macro("S_00B93E70")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("S_00B93E74")
#undef S_00B93E74
#pragma push_macro("S_00B93E74") /*gvi*/
#undef S_00B93E74 /*gvi*/
uint32_t S_00B93E74;
#pragma pop_macro("S_00B93E74") /*gvi*/
#pragma pop_macro("S_00B93E74")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("S_00BA5280")
#undef S_00BA5280
#pragma push_macro("S_00BA5280") /*gvi*/
#undef S_00BA5280 /*gvi*/
uint32_t S_00BA5280;
#pragma pop_macro("S_00BA5280") /*gvi*/
#pragma pop_macro("S_00BA5280")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("S_00BA52D4")
#undef S_00BA52D4
#pragma push_macro("S_00BA52D4") /*gvi*/
#undef S_00BA52D4 /*gvi*/
uint32_t S_00BA52D4;
#pragma pop_macro("S_00BA52D4") /*gvi*/
#pragma pop_macro("S_00BA52D4")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("S_00BA5380")
#undef S_00BA5380
#pragma push_macro("S_00BA5380") /*gvi*/
#undef S_00BA5380 /*gvi*/
uint32_t S_00BA5380;
#pragma pop_macro("S_00BA5380") /*gvi*/
#pragma pop_macro("S_00BA5380")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("S_00BDC2A0")
#undef S_00BDC2A0
#pragma push_macro("S_00BDC2A0") /*gvi*/
#undef S_00BDC2A0 /*gvi*/
sf_bytes_t S_00BDC2A0;
#pragma pop_macro("S_00BDC2A0") /*gvi*/
#pragma pop_macro("S_00BDC2A0")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("S_00BDC2A1")
#undef S_00BDC2A1
#pragma push_macro("S_00BDC2A1") /*gvi*/
#undef S_00BDC2A1 /*gvi*/
sf_bytes_t S_00BDC2A1;
#pragma pop_macro("S_00BDC2A1") /*gvi*/
#pragma pop_macro("S_00BDC2A1")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("S_00BDCD00")
#undef S_00BDCD00
#pragma push_macro("S_00BDCD00") /*gvi*/
#undef S_00BDCD00 /*gvi*/
sf_ints_t S_00BDCD00;
#pragma pop_macro("S_00BDCD00") /*gvi*/
#pragma pop_macro("S_00BDCD00")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("S_00C808A0")
#undef S_00C808A0
#pragma push_macro("S_00C808A0") /*gvi*/
#undef S_00C808A0 /*gvi*/
int32_t S_00C808A0;
#pragma pop_macro("S_00C808A0") /*gvi*/
#pragma pop_macro("S_00C808A0")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("S_00D0CC60")
#undef S_00D0CC60
#pragma push_macro("S_00D0CC60") /*gvi*/
#undef S_00D0CC60 /*gvi*/
sf_bytes_t S_00D0CC60;
#pragma pop_macro("S_00D0CC60") /*gvi*/
#pragma pop_macro("S_00D0CC60")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("S_00D0DDE0")
#undef S_00D0DDE0
#pragma push_macro("S_00D0DDE0") /*gvi*/
#undef S_00D0DDE0 /*gvi*/
int32_t S_00D0DDE0;
#pragma pop_macro("S_00D0DDE0") /*gvi*/
#pragma pop_macro("S_00D0DDE0")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("S_00D11804")
#undef S_00D11804
#pragma push_macro("S_00D11804") /*gvi*/
#undef S_00D11804 /*gvi*/
int32_t S_00D11804;
#pragma pop_macro("S_00D11804") /*gvi*/
#pragma pop_macro("S_00D11804")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("S_00D11878")
#undef S_00D11878
#pragma push_macro("S_00D11878") /*gvi*/
#undef S_00D11878 /*gvi*/
int32_t S_00D11878;
#pragma pop_macro("S_00D11878") /*gvi*/
#pragma pop_macro("S_00D11878")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("S_00D1192C")
#undef S_00D1192C
#pragma push_macro("S_00D1192C") /*gvi*/
#undef S_00D1192C /*gvi*/
int32_t S_00D1192C;
#pragma pop_macro("S_00D1192C") /*gvi*/
#pragma pop_macro("S_00D1192C")
#endif
#ifdef RE_HOOK_BUILD   /* v2.35: native — P10_ScriptCtx / P15_ListCurU (smallfuncs.h) */
GAME_VAR_DEF(uint8_t*, S_00D1240C, 0x00d1240c)
GAME_VAR_DEF(uint16_t*, S_00D12410, 0x00d12410)
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("S_00D12414")
#undef S_00D12414
#pragma push_macro("S_00D12414") /*gvi*/
#undef S_00D12414 /*gvi*/
int32_t S_00D12414;
#pragma pop_macro("S_00D12414") /*gvi*/
#pragma pop_macro("S_00D12414")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("S_010EA8A0")
#undef S_010EA8A0
#pragma push_macro("S_010EA8A0") /*gvi*/
#undef S_010EA8A0 /*gvi*/
sf_bytes_t S_010EA8A0;
#pragma pop_macro("S_010EA8A0") /*gvi*/
#pragma pop_macro("S_010EA8A0")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("S_010FAF40")
#undef S_010FAF40
#pragma push_macro("S_010FAF40") /*gvi*/
#undef S_010FAF40 /*gvi*/
sf_bytes_t S_010FAF40;
#pragma pop_macro("S_010FAF40") /*gvi*/
#pragma pop_macro("S_010FAF40")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("S_010FB0E0")
#undef S_010FB0E0
#pragma push_macro("S_010FB0E0") /*gvi*/
#undef S_010FB0E0 /*gvi*/
sf_bytes_t S_010FB0E0;
#pragma pop_macro("S_010FB0E0") /*gvi*/
#pragma pop_macro("S_010FB0E0")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("S_010FFA24")
#undef S_010FFA24
#pragma push_macro("S_010FFA24") /*gvi*/
#undef S_010FFA24 /*gvi*/
int32_t S_010FFA24;
#pragma pop_macro("S_010FFA24") /*gvi*/
#pragma pop_macro("S_010FFA24")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("S_0110E144")
#undef S_0110E144
#pragma push_macro("S_0110E144") /*gvi*/
#undef S_0110E144 /*gvi*/
int32_t S_0110E144;
#pragma pop_macro("S_0110E144") /*gvi*/
#pragma pop_macro("S_0110E144")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("S_011173C8")
#undef S_011173C8
#pragma push_macro("S_011173C8") /*gvi*/
#undef S_011173C8 /*gvi*/
int32_t S_011173C8;
#pragma pop_macro("S_011173C8") /*gvi*/
#pragma pop_macro("S_011173C8")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("S_01136C74")
#undef S_01136C74
#pragma push_macro("S_01136C74") /*gvi*/
#undef S_01136C74 /*gvi*/
int32_t S_01136C74;
#pragma pop_macro("S_01136C74") /*gvi*/
#pragma pop_macro("S_01136C74")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("S_01139A34")
#undef S_01139A34
#pragma push_macro("S_01139A34") /*gvi*/
#undef S_01139A34 /*gvi*/
int32_t S_01139A34;
#pragma pop_macro("S_01139A34") /*gvi*/
#pragma pop_macro("S_01139A34")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("S_011443EA")
#undef S_011443EA
#pragma push_macro("S_011443EA") /*gvi*/
#undef S_011443EA /*gvi*/
sf_bytes_t S_011443EA;
#pragma pop_macro("S_011443EA") /*gvi*/
#pragma pop_macro("S_011443EA")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("S_0127104C")
#undef S_0127104C
#pragma push_macro("S_0127104C") /*gvi*/
#undef S_0127104C /*gvi*/
uint32_t S_0127104C;
#pragma pop_macro("S_0127104C") /*gvi*/
#pragma pop_macro("S_0127104C")
#endif
#define U8P(p,o)  ((uint8_t*)(p)+(o))
#define U32(p,o)  (*(uint32_t*)U8P(p,o))
#define I32(p,o)  (*(int32_t*)U8P(p,o))
#define U16(p,o)  (*(uint16_t*)U8P(p,o))
/* --- пустые --- */
/* Empty functions and constant returns of the original. */
void NoopFn0041F81E(void) {}
void NoopFn0041FA49(void) {}
void NoopFn0041FA50(void) {}
void NoopFn0041FA57(void) {}
void NoopFn0041FA7D(void) {}
void NoopFn0041FA8B(void) {}
void NoopFn0041FA92(void) {}
void NoopFn0041FAB9(void) {}
int32_t ReturnZero004D03FD(void) { return 0; }
int32_t ReturnZero004E3B19(void) { return 0; }
int32_t ReturnOne00519D22(void) { return 1; }
/* --- сеттеры полей структур --- */
/* Single-field setters / tests.  ScriptSetWait*: a script wait record {time, type 12}; the X50 variant
   multiplies by 50 (seconds -> ticks: 50 game ticks per second, see P114_Timer).  SlotSetOn/Off: voice slot i (0..19)
   active byte of the 0x34-byte sound slot table.  SetRGB00516EB4: current text colour (see P70_FadeColor). */
void SetField24_00502779(uint8_t* p, int32_t v) { I32(p, 0x24) = v; }
void ClearField2C_00502680(uint8_t* p) { I32(p, 0x2c) = 0; }
void AddToCounter00519D09(int32_t v) { S_01136C74 += v; }
void ClearFlagByte0048FBBA(int32_t n) { S_011443EA[(n - 1) * 0x54] = 0; }
void ScriptSetWait004F5C72(int32_t* p, int32_t v) { p[0] = v; p[1] = 12; }
/* seconds -> ticks: the game logic runs 50 ticks per second (P114_Timer: sec = ticks / 50, hundredths = ticks % 50 * 2) */
void ScriptSetWaitX50_004F5C58(int32_t* p, int32_t v) { p[0] = v * 0x32; p[1] = 12; }
void ToggleBit0051049E(void) { if (S_00C808A0 != 0) S_00B5A77C ^= 1; }
int32_t IsFlag80_00514E4C(uint8_t* p) { return (U32(p, 0xc) & 0x80) != 0; }
void SetFlagFromArg0041E1E4(int32_t v) { S_00A421D8 = (uint32_t)(v != 1); }
void SetLatchValue0050E940(int32_t v) { if (v == S_00B5A76C) S_00B5A770 = 1; S_00B5A76C = v; }
int32_t IsSlotActive00524473(int32_t i) { return (S_00BDC2A0[i * 0x34] & 0x11) != 0; }
int32_t TestBit0041B7AD(uint32_t n) { return (S_0127104C & (1u << (n & 31))) != 0; }
void SetRGB00516EB4(uint8_t r, uint8_t g, uint8_t b) { S_00B5A834 = r; S_00B5A835 = g; S_00B5A836 = b; }
void SlotSetOn0052432A(int32_t i) { if (-1 < i && i < 0x14) S_00BDC2A1[i * 0x34] = 1; }
void SlotSetOff0052434A(int32_t i) { if (-1 < i && i < 0x14) S_00BDC2A1[i * 0x34] = 0; }
/* --- стеки индексов (пулы) --- */
/* Index pools: Push stores a free index below the stack pointer, Pop takes one (-1 when the pool is full:
   100 / 200 entries).  CounterDecrement: decrements to 0, returns 1 if it was positive.  AllocSlot: next of
   8 slots numbered 0x14.., -1 when exhausted. */
void PoolPush004AC6AC(uint16_t v) { S_011173C8 -= 1; ((uint16_t*)S_010FAF40)[S_011173C8] = v; }
void PoolPush004AC702(uint16_t v) { S_0110E144 -= 1; ((uint16_t*)S_010EA8A0)[S_0110E144] = v; }
void PoolPush004AC755(uint16_t v) { S_010FFA24 -= 1; ((uint16_t*)S_010FB0E0)[S_010FFA24] = v; }
int32_t PoolPop004AC726(void) {
    int32_t r;
    if (S_010FFA24 < 100) { r = ((int16_t*)S_010FB0E0)[S_010FFA24]; S_010FFA24++; } else r = -1;
    return r;
}
int32_t PoolPop004AC6D0(void) {
    int32_t r;
    if (S_0110E144 < 200) { r = ((int16_t*)S_010EA8A0)[S_0110E144]; S_0110E144++; } else r = -1;
    return r;
}
int32_t CounterDecrement004D97B8(void) {
    int32_t old = S_00D11804;
    if (0 < S_00D11804) S_00D11804--;
    return 0 < old;
}
int32_t AllocSlot00492508(void) {
    int32_t r;
    if (S_01139A34 == 8) r = -1; else { r = S_01139A34 + 0x14; S_01139A34++; }
    return r;
}
uint32_t PackRGB00503ECC(const uint8_t* p) { return (uint32_t)I32(p, 0x14) << 16 | (uint32_t)I32(p, 0x10) << 8 | U32(p, 0xc); }
int32_t IsKeyOnly004E38B4(void) { return !(S_00B31E42 == 0 || S_00B31E40 != 0); }
int32_t IsKeyOnly004E38D9(void) { return !(S_00B31E43 == 0 || S_00B31E41 != 0); }
int32_t ExchangeTable00522F2A(int32_t i, int32_t v) { int32_t o = S_00BDCD00[i]; S_00BDCD00[i] = v; return o; }
void InitFlags004946DA(uint8_t* p) { I32(p, 0x3c) = 0; I32(p, 0x38) = 0; p[0x11] = 1; p[0x12] = 1; }
void WrapCounter004A3A80(uint8_t* p) {
    if (0x1d < I32(p, 0xc)) { U32(p, 0x10) &= 0xfffffeffu; I32(p, 0xc) = 0; }
}
/* Vector helpers: copies into fixed globals (00ba5280.. = TODO(RE), 00b93e6c..74 = translation used by
   RotVec_005279CB), negation, reset to (0, 0, 0, ?, 1.0). */
void CopyVec3_005265BC(uint32_t* v) { S_00BA5280 = v[0]; S_00BA52D4 = v[1]; S_00BA5380 = v[2]; }
void CopyVec3_0052797A(uint32_t* v) { S_00B93E6C = v[0]; S_00B93E70 = v[1]; S_00B93E74 = v[2]; }
void NegateVec3_00526FB6(float* v) { v[0] = -v[0]; v[1] = -v[1]; v[2] = -v[2]; }
void NegateVec3_005270F6(float* v) { v[0] = -v[0]; v[1] = -v[1]; v[2] = -v[2]; }
void NegateVec3To_00526FE3(float* d, float* s) { d[0] = -s[0]; d[1] = -s[1]; d[2] = -s[2]; }
void ResetVec_005272C6(uint32_t* v) { v[4] = 0x3f800000u; v[2] = 0; v[1] = 0; v[0] = 0; }
/* CopySlotTemplate004A1010: copies the 0x16c-byte per-model car parameter record of the player car model
   (S_00560A88 + model * 0x16c) to the active record S_00D0CC60. */
void CopySlotTemplate004A1010(void) {
    uint32_t* s = (uint32_t*)(S_00560A88 + (size_t)S_00D1192C * 0x16c);
    uint32_t* d = (uint32_t*)S_00D0CC60;
    for (int i = 0; i < 0x5b; i++) d[i] = s[i];
}
/* --- опкоды скрипта (смещение указателя + флаги) --- */
/* Opcodes of the 004d1xxx bytecode interpreter: ip S_00D12414 advances past the opcode (2 bytes, or 4 with an
   operand) and flags in the context record S_00D1240C (+0x44, u16 +0x48) are set/cleared.  Return 1 = continue
   with the next opcode, 0 = stop for this frame (TODO(RE): inferred from the loop opcode in ported10.c). */
int32_t ScriptOpSkipClear004D1111(void) { SF_SCRIPT_IP_ADD(2); I32(S_00D1240C, 0x44) = 0; return 1; }
int32_t ScriptOpSetBit4_004D13D8(void) { SF_SCRIPT_IP_ADD(2); U16(S_00D1240C, 0x48) |= 4; return 0; }
int32_t ScriptOpClearBit2_004D1402(void) { SF_SCRIPT_IP_ADD(2); *S_00D12410 &= 0xfffd; return 0; }
int32_t ScriptOpSetBit200_004D03D0(void) { SF_SCRIPT_IP_ADD(2); U16(S_00D1240C, 0x48) |= 0x200; return 1; }
int32_t ScriptOpSetBit2_004D0404(void) { SF_SCRIPT_IP_ADD(2); U16(S_00D1240C, 0x48) = (U16(S_00D1240C, 0x48) & 0xff7e) | 2; return 1; }
int32_t ScriptOpToggle10_004D1737(void) { SF_SCRIPT_IP_ADD(2); U16(S_00D1240C, 0x48) ^= 0x10; return 1; }
int32_t ScriptOpSkip4_004D1601(void) { SF_SCRIPT_IP_ADD(4); return 1; }
void RingAdvance004D7B36(void) { S_00D11878++; if (S_00D11878 == S_00D0DDE0) S_00D11878 = 0; }
/* --- подсветка пунктов меню (значения 2/3 в таблицах) --- */
/* Menu highlight setters: write state 2 / 3 or colour red (0xff, 0, 0) / white to the two 0x10-byte entries of
   the selected menu row. */
void MenuRowsTo3_00404E52(void) { S_00549B04[(S_0057B658 * 2 + 1) * 0x10] = 3; S_00549B04[(S_0057B658 * 2 + 2) * 0x10] = 3; }
void MenuRowsIf0To2_00404E7E(int32_t f) {
    if (f == 0) { S_00549B04[(S_0057B65C * 2 + 1) * 0x10] = 2; S_00549B04[(S_0057B65C * 2 + 2) * 0x10] = 2; }
}
void SetColorRed00417A55(void) { S_0054E44C[S_005FEA30 * 0x10] = 0xff; S_0054E44D[S_005FEA30 * 0x10] = 0; S_0054E44E[S_005FEA30 * 0x10] = 0; }
void SetColorWhite00417AA2(void) { S_0054E44C[S_005FEA30 * 0x10] = 0xff; S_0054E44D[S_005FEA30 * 0x10] = 0xff; S_0054E44E[S_005FEA30 * 0x10] = 0xff; }
void SetColorRed0041A051(void) { S_0054E6AC[S_005FEA8C * 0x10] = 0xff; S_0054E6AD[S_005FEA8C * 0x10] = 0; S_0054E6AE[S_005FEA8C * 0x10] = 0; }
void SetColorWhite0041A085(void) { S_0054E6AC[S_005FEA8C * 0x10] = 0xff; S_0054E6AD[S_005FEA8C * 0x10] = 0xff; S_0054E6AE[S_005FEA8C * 0x10] = 0xff; }
