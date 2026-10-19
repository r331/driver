/* widgets.c — a batch of tiny Game.exe menu handlers and helpers (English overview).
   The address in each function name is its Game.exe address (do not rename).  One-liners grouped by kind:
   row selection, volume / cycle / float steppers, menu-row state bytes, icon names, option toggles and a
   few small math/getter helpers.  Globals are named W<type><address> (I int32, U uint32, F float, A/B arrays). */
#include "ported141.h"
#include "widgets.h"
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("WI00575EE4")
#undef WI00575EE4
#pragma push_macro("WI00575EE4") /*gvi*/
#undef WI00575EE4 /*gvi*/
int32_t WI00575EE4;
#pragma pop_macro("WI00575EE4") /*gvi*/
#pragma pop_macro("WI00575EE4")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("WI00B87E2C")
#undef WI00B87E2C
#pragma push_macro("WI00B87E2C") /*gvi*/
#undef WI00B87E2C /*gvi*/
int32_t WI00B87E2C;
#pragma pop_macro("WI00B87E2C") /*gvi*/
#pragma pop_macro("WI00B87E2C")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("WI005FE694")
#undef WI005FE694
#pragma push_macro("WI005FE694") /*gvi*/
#undef WI005FE694 /*gvi*/
int32_t WI005FE694;
#pragma pop_macro("WI005FE694") /*gvi*/
#pragma pop_macro("WI005FE694")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("WU005FE788")
#undef WU005FE788
#pragma push_macro("WU005FE788") /*gvi*/
#undef WU005FE788 /*gvi*/
uint32_t WU005FE788;
#pragma pop_macro("WU005FE788") /*gvi*/
#pragma pop_macro("WU005FE788")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("WI005FE78C")
#undef WI005FE78C
#pragma push_macro("WI005FE78C") /*gvi*/
#undef WI005FE78C /*gvi*/
int32_t WI005FE78C;
#pragma pop_macro("WI005FE78C") /*gvi*/
#pragma pop_macro("WI005FE78C")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("WI005FE790")
#undef WI005FE790
#pragma push_macro("WI005FE790") /*gvi*/
#undef WI005FE790 /*gvi*/
int32_t WI005FE790;
#pragma pop_macro("WI005FE790") /*gvi*/
#pragma pop_macro("WI005FE790")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("WF00575F14")
#undef WF00575F14
#pragma push_macro("WF00575F14") /*gvi*/
#undef WF00575F14 /*gvi*/
float WF00575F14;
#pragma pop_macro("WF00575F14") /*gvi*/
#pragma pop_macro("WF00575F14")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("WF00575F18")
#undef WF00575F18
#pragma push_macro("WF00575F18") /*gvi*/
#undef WF00575F18 /*gvi*/
float WF00575F18;
#pragma pop_macro("WF00575F18") /*gvi*/
#pragma pop_macro("WF00575F18")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("WF00546020")
#undef WF00546020
#pragma push_macro("WF00546020") /*gvi*/
#undef WF00546020 /*gvi*/
float WF00546020;
#pragma pop_macro("WF00546020") /*gvi*/
#pragma pop_macro("WF00546020")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("WF00546024")
#undef WF00546024
#pragma push_macro("WF00546024") /*gvi*/
#undef WF00546024 /*gvi*/
float WF00546024;
#pragma pop_macro("WF00546024") /*gvi*/
#pragma pop_macro("WF00546024")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("WF0054606C")
#undef WF0054606C
#pragma push_macro("WF0054606C") /*gvi*/
#undef WF0054606C /*gvi*/
float WF0054606C;
#pragma pop_macro("WF0054606C") /*gvi*/
#pragma pop_macro("WF0054606C")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("WU0054E830")
#undef WU0054E830
#pragma push_macro("WU0054E830") /*gvi*/
#undef WU0054E830 /*gvi*/
uint32_t WU0054E830;
#pragma pop_macro("WU0054E830") /*gvi*/
#pragma pop_macro("WU0054E830")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("WU00C55A70")
#undef WU00C55A70
#pragma push_macro("WU00C55A70") /*gvi*/
#undef WU00C55A70 /*gvi*/
uint32_t WU00C55A70;
#pragma pop_macro("WU00C55A70") /*gvi*/
#pragma pop_macro("WU00C55A70")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("WU0054CBB0")
#undef WU0054CBB0
#pragma push_macro("WU0054CBB0") /*gvi*/
#undef WU0054CBB0 /*gvi*/
uint32_t WU0054CBB0;
#pragma pop_macro("WU0054CBB0") /*gvi*/
#pragma pop_macro("WU0054CBB0")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("WU0054CBC4")
#undef WU0054CBC4
#pragma push_macro("WU0054CBC4") /*gvi*/
#undef WU0054CBC4 /*gvi*/
uint32_t WU0054CBC4;
#pragma pop_macro("WU0054CBC4") /*gvi*/
#pragma pop_macro("WU0054CBC4")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("WU0054CBD8")
#undef WU0054CBD8
#pragma push_macro("WU0054CBD8") /*gvi*/
#undef WU0054CBD8 /*gvi*/
uint32_t WU0054CBD8;
#pragma pop_macro("WU0054CBD8") /*gvi*/
#pragma pop_macro("WU0054CBD8")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("WU0054CBEC")
#undef WU0054CBEC
#pragma push_macro("WU0054CBEC") /*gvi*/
#undef WU0054CBEC /*gvi*/
uint32_t WU0054CBEC;
#pragma pop_macro("WU0054CBEC") /*gvi*/
#pragma pop_macro("WU0054CBEC")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("WU0054CC00")
#undef WU0054CC00
#pragma push_macro("WU0054CC00") /*gvi*/
#undef WU0054CC00 /*gvi*/
uint32_t WU0054CC00;
#pragma pop_macro("WU0054CC00") /*gvi*/
#pragma pop_macro("WU0054CC00")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("WU0054CC14")
#undef WU0054CC14
#pragma push_macro("WU0054CC14") /*gvi*/
#undef WU0054CC14 /*gvi*/
uint32_t WU0054CC14;
#pragma pop_macro("WU0054CC14") /*gvi*/
#pragma pop_macro("WU0054CC14")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("WU0054CC28")
#undef WU0054CC28
#pragma push_macro("WU0054CC28") /*gvi*/
#undef WU0054CC28 /*gvi*/
uint32_t WU0054CC28;
#pragma pop_macro("WU0054CC28") /*gvi*/
#pragma pop_macro("WU0054CC28")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("WA00B20330")
#undef WA00B20330
#pragma push_macro("WA00B20330") /*gvi*/
#undef WA00B20330 /*gvi*/
wd_ints5_t WA00B20330;
#pragma pop_macro("WA00B20330") /*gvi*/
#pragma pop_macro("WA00B20330")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("WI00B20344")
#undef WI00B20344
#pragma push_macro("WI00B20344") /*gvi*/
#undef WI00B20344 /*gvi*/
int32_t WI00B20344;
#pragma pop_macro("WI00B20344") /*gvi*/
#pragma pop_macro("WI00B20344")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("WA0056039C")
#undef WA0056039C
#pragma push_macro("WA0056039C") /*gvi*/
#undef WA0056039C /*gvi*/
wd_pairs4_t WA0056039C;
#pragma pop_macro("WA0056039C") /*gvi*/
#pragma pop_macro("WA0056039C")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("WI00B20348")
#undef WI00B20348
#pragma push_macro("WI00B20348") /*gvi*/
#undef WI00B20348 /*gvi*/
int32_t WI00B20348;
#pragma pop_macro("WI00B20348") /*gvi*/
#pragma pop_macro("WI00B20348")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("WH00B2C3A8")
#undef WH00B2C3A8
#pragma push_macro("WH00B2C3A8") /*gvi*/
#undef WH00B2C3A8 /*gvi*/
uint16_t WH00B2C3A8;
#pragma pop_macro("WH00B2C3A8") /*gvi*/
#pragma pop_macro("WH00B2C3A8")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("WB0054C6D4")
#undef WB0054C6D4
#pragma push_macro("WB0054C6D4") /*gvi*/
#undef WB0054C6D4 /*gvi*/
wd_bytes_t WB0054C6D4;
#pragma pop_macro("WB0054C6D4") /*gvi*/
#pragma pop_macro("WB0054C6D4")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("WB0054C944")
#undef WB0054C944
#pragma push_macro("WB0054C944") /*gvi*/
#undef WB0054C944 /*gvi*/
wd_bytes_t WB0054C944;
#pragma pop_macro("WB0054C944") /*gvi*/
#pragma pop_macro("WB0054C944")
#endif
/* SelectRow — local helper: selects menu row record `row_addr` (Game.exe address) with item id `id`
   (005fe788/78c/790, then 00411a9d), stores the id as the current selection 005fe798 and clears 005fe79c.
   Returns 0. */
static int32_t SelectRow(uint32_t row_addr, int32_t id) {
    WI005FE78C = 1; WU005FE788 = row_addr; WI005FE790 = id; Call00411A9D();
    MenuI005FE798 = WI005FE790; MenuI005FE79C = -1; return 0;
}
/* SelectRowXXXXXXXX — Game.exe 004110c2 ... 004119f3: one handler per menu row (row byte 0054b7c4..d1, id). */
int32_t SelectRow004110C2(void) {return SelectRow(0x0054b7c4, 0x2);}
int32_t SelectRow00411177(void) {return SelectRow(0x0054b7c5, 0x4);}
int32_t SelectRow0041122C(void) {return SelectRow(0x0054b7c8, 0x6);}
int32_t SelectRow004112E1(void) {return SelectRow(0x0054b7c6, 0x8);}
int32_t SelectRow00411396(void) {return SelectRow(0x0054b7ca, 0x10);}
int32_t SelectRow0041144B(void) {return SelectRow(0x0054b7c7, 0xa);}
int32_t SelectRow00411500(void) {return SelectRow(0x0054b7c9, 0x12);}
int32_t SelectRow004115B5(void) {return SelectRow(0x0054b7d0, 0x14);}
int32_t SelectRow0041166A(void) {return SelectRow(0x0054b7cb, 0x18);}
int32_t SelectRow0041171F(void) {return SelectRow(0x0054b7cc, 0x1a);}
int32_t SelectRow004117D4(void) {return SelectRow(0x0054b7cd, 0x1c);}
int32_t SelectRow00411889(void) {return SelectRow(0x0054b7ce, 0xc);}
int32_t SelectRow0041193E(void) {return SelectRow(0x0054b7cf, 0xe);}
int32_t SelectRow004119F3(void) {return SelectRow(0x0054b7d1, 0x16);}
/* VolumeUp00409BC9 / VolumeDown00409BFD — Game.exe 00409bc9 / 00409bfd.  Volume 00575ee4 in steps of 0x10,
   clamped to 0x10..0x40; marks the menu dirty (00575ef8 = 4) and redraws. */
void VolumeUp00409BC9(void) {WI00575EE4 += 0x10; if (WI00575EE4 > 0x40) WI00575EE4 = 0x40; G00575EF8 = 4; MenuRedraw();}
void VolumeDown00409BFD(void) {WI00575EE4 -= 0x10; if (WI00575EE4 < 0x10) WI00575EE4 = 0x10; G00575EF8 = 4; MenuRedraw();}
/* CycleInc0040E918 — Game.exe 0040e918.  Cycles 00b87e2c through 0, 1, 2 and refreshes (0040ea70).
   TODO(RE): unsure what setting 00b87e2c is (P142 uses it to pick the cop steering mode table — likely difficulty). */
int32_t CycleInc0040E918(void) {WI00B87E2C++; if (WI00B87E2C == 3) WI00B87E2C = 0; Call0040EA70(); return 0;}
/* CycleDec0040F364 / CycleInc0040F3AD — Game.exe 0040f364 / 0040f3ad.  Previous / next level on the high-score
   screen (wraps over 005fe694 levels) and rebuilds it (P141_HsSetup). */
int32_t CycleDec0040F364(void) {UiVar005FE6BC--; if (UiVar005FE6BC < 0) UiVar005FE6BC = WI005FE694 - 1; P141_HsSetup(); return 0;}
int32_t CycleInc0040F3AD(void) {UiVar005FE6BC++; if (WI005FE694 <= UiVar005FE6BC) UiVar005FE6BC = 0; P141_HsSetup(); return 0;}
/* MenuRowsTo2 / MenuAllRowsTo2 / MenuRowsTo3 — Game.exe 00412254, 00412280, 00412643, 0041266f, 0041269b.
   Set the state byte of the two lines of the selected row (or of all 8 rows) in menu tables 0054c6d4 /
   0054c944 (records of 0x10 bytes, two per row starting at record 3) to 2 or 3.
   TODO(RE): unsure what states 2 and 3 look like (normal / highlighted?). */
void MenuRowsTo2_00412254(void) {WB0054C6D4[(UiVar005FE84C * 2 + 3) * 0x10] = 2; WB0054C6D4[(UiVar005FE84C * 2 + 4) * 0x10] = 2;}
void MenuAllRowsTo2_00412280(void) {for (int i = 0; i < 8; i++) { WB0054C6D4[(i * 2 + 3) * 0x10] = 2; WB0054C6D4[(i * 2 + 4) * 0x10] = 2; }}
void MenuRowsTo3_00412643(void) {WB0054C944[(UiVar005FE928 * 2 + 3) * 0x10] = 3; WB0054C944[(UiVar005FE928 * 2 + 4) * 0x10] = 3;}
void MenuRowsTo2_0041266F(void) {WB0054C944[(UiVar005FE928 * 2 + 3) * 0x10] = 2; WB0054C944[(UiVar005FE928 * 2 + 4) * 0x10] = 2;}
void MenuAllRowsTo2_0041269B(void) {for (int i = 0; i < 8; i++) { WB0054C944[(i * 2 + 3) * 0x10] = 2; WB0054C944[(i * 2 + 4) * 0x10] = 2; }}
/* SetIconNameXXXXXXXX — Game.exe 00412a36 ... 00412d38.  When called with reset == 0, point an icon slot
   (0054cbb0 ... 0054cc28) at its name string (0054cdfc ... 0054cea4).  Note 00412cca and 00412d38 both
   write slot 0054cc28, as in Game.exe. */
void SetIconName00412A36(int32_t reset) {if (reset == 0) WU0054CBB0 = 0x0054cdfc;}
void SetIconName00412AA4(int32_t reset) {if (reset == 0) WU0054CBC4 = 0x0054ce14;}
void SetIconName00412B12(int32_t reset) {if (reset == 0) WU0054CBD8 = 0x0054ce2c;}
void SetIconName00412B80(int32_t reset) {if (reset == 0) WU0054CBEC = 0x0054ce44;}
void SetIconName00412BEE(int32_t reset) {if (reset == 0) WU0054CC00 = 0x0054ce5c;}
void SetIconName00412C5C(int32_t reset) {if (reset == 0) WU0054CC14 = 0x0054ce74;}
void SetIconName00412CCA(int32_t reset) {if (reset == 0) WU0054CC28 = 0x0054ce8c;}
void SetIconName00412D38(int32_t reset) {if (reset == 0) WU0054CC28 = 0x0054cea4;}
/* StepUp / StepDown — Game.exe 00415848, 00415877, 004158a6, 004158d5, 0050f9b4, 0050f9e3, 0050fa12,
   0050fa41.  Raise / lower float setting 00575f14 or 00575f18 by the step 0054606c while it stays below
   00546020 / above 00546024, then apply it (00414d1f in the front end, 0050f7b2 in the pause menu).
   TODO(RE): unsure which two settings these are (likely the two volume sliders: sound effects / music). */
void StepUp00415848(void) {if (WF00575F14 < WF00546020) { WF00575F14 = WF00575F14 + WF0054606C; Call00414D1F(); }}
void StepDown00415877(void) {if (WF00546024 < WF00575F14) { WF00575F14 = WF00575F14 - WF0054606C; Call00414D1F(); }}
void StepUp004158A6(void) {if (WF00575F18 < WF00546020) { WF00575F18 = WF00575F18 + WF0054606C; Call00414D1F(); }}
void StepDown004158D5(void) {if (WF00546024 < WF00575F18) { WF00575F18 = WF00575F18 - WF0054606C; Call00414D1F(); }}
void StepUp0050F9B4(void) {if (WF00575F14 < WF00546020) { WF00575F14 = WF00575F14 + WF0054606C; Call0050F7B2(); }}
void StepDown0050F9E3(void) {if (WF00546024 < WF00575F14) { WF00575F14 = WF00575F14 - WF0054606C; Call0050F7B2(); }}
void StepUp0050FA12(void) {if (WF00575F18 < WF00546020) { WF00575F18 = WF00575F18 + WF0054606C; Call0050F7B2(); }}
void StepDown0050FA41(void) {if (WF00546024 < WF00575F18) { WF00575F18 = WF00575F18 - WF0054606C; Call0050F7B2(); }}
/* CopyWord0041AD8D — Game.exe 0041ad8d.  0054e830 = 00c55a70, then 0041afca. */
void CopyWord0041AD8D(void) {WU0054E830 = WU00C55A70; Call0041AFCA();}
/* RangeCheck00514E6A — Game.exe 00514e6a.  1 if p[+0x2c] <= n * p[+0x30] + p[+0x34]. */
int32_t RangeCheck00514E6A(const int32_t* p, int32_t n) {return p[0x2c/4] <= n * p[0x30/4] + p[0x34/4];}
/* Dot3_00526029 — Game.exe 00526029.  Float dot product a . b (summed z, y, x as in Game.exe). */
float Dot3_00526029(const float* a, const float* b) {return a[2] * b[2] + a[1] * b[1] + a[0] * b[0];}
/* GetConst0041FA5E — Game.exe 0041fa5e.  Returns the float constant 00546024. */
float GetConst0041FA5E(void) {return WF00546024;}
/* ClearSlots004D61CF / ClearPairs004D6C20 — Game.exe 004d61cf / 004d6c20.  Reset the 5-slot list 00b20330
   to -1 (count 00b20344 = 0) / the first words of the 4 pairs 0056039c (count 00b20348 = 0). */
void ClearSlots004D61CF(void) {for (int i = 0; i < 5; i++) WA00B20330[i] = -1; WI00B20344 = 0;}
void ClearPairs004D6C20(void) {for (int i = 0; i < 4; i++) WA0056039C[i * 2] = 0; WI00B20348 = 0;}
/* Pack565_004D950F — Game.exe 004d950f.  Packs 8-bit r, g, b into RGB565 at 00b2c3a8. */
void Pack565_004D950F(int16_t r, int16_t g, int16_t b) {WH00B2C3A8 = (uint16_t)((((int32_t)r >> 3) << 11) | (((int32_t)g >> 2) << 5) | (b >> 3));}
/* AddVelocity004E122C — Game.exe 004e122c.  Adds 50x the int16 values at o+4 / o+10 / o+0x10 to the int32
   accumulators o+0x4c / 0x50 / 0x54.  TODO(RE): unsure which object this is (name from the shape only). */
void AddVelocity004E122C(int32_t* o) {o[0x4c/4] += *(int16_t*)((uint8_t*)o + 4) * 0x32; o[0x50/4] += *(int16_t*)((uint8_t*)o + 10) * 0x32; o[0x54/4] += *(int16_t*)((uint8_t*)o + 0x10) * 0x32;}
/* Get4Words004E4379 — Game.exe 004e4379.  Copies words 1..4 of s to d (if d is not NULL).  Returns 0. */
int32_t Get4Words004E4379(const int32_t* s, int32_t* d) {if (d) { d[0] = s[1]; d[1] = s[2]; d[2] = s[3]; d[3] = s[4]; } return 0;}
/* ToggleXXXXXXXX — Game.exe 0050fe82 ... 00510007.  Pause/options menu switches: flip one flag, mark the menu
   dirty (00575ef8 = 4) and redraw it (0050fbf4). */
void Toggle0050FE82(void) {G0055384C ^= 1; G00575EF8 = 4; Call0050FBF4();}
void Toggle0050FEA3(void) {G00553850 ^= 1; G00575EF8 = 4; Call0050FBF4();}
void Toggle0050FEC4(void) {G00B31F04 ^= 1; G00575EF8 = 4; Call0050FBF4();}
void Toggle0050FF41(void) {G00575F44 ^= 1; G00575EF8 = 4; Call0050FBF4();}
void Toggle0050FF62(void) {G0055C974 ^= 1; G00575EF8 = 4; Call0050FBF4();}
void Toggle0050FF83(void) {G00575F30 ^= 1; G00575EF8 = 4; Call0050FBF4();}
void Toggle0050FFA4(void) {G00B201DC ^= 1; G00575EF8 = 4; Call0050FBF4();}
void Toggle0050FFC5(void) {G00575EE8 ^= 1; G00575EF8 = 4; Call0050FBF4();}
void Toggle0050FFE6(void) {G00575F3C ^= 1; G00575EF8 = 4; Call0050FBF4();}
void Toggle00510007(void) {G00D118C8 ^= 1; G00575EF8 = 4; Call0050FBF4();}
