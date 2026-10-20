/* uihandlers4.c — auto-generated batch of one-line UI setters / toggles from Game.exe (cdecl), each tagged with its
   Game.exe address.  Most addresses duplicate menustate.c (same code under other names; the hook DLL installs the
   last re_hook, native fn_table.c the first — see docs/DEAD_CODE_AUDIT.md).  Kept as is: names and order are
   referenced by the hook lists.  Groups: flag setters, the seven MenuOpt toggles (refresh), graphics switches
   (mark dirty + redraw), slider steps, menu-mode select / clear pairs, two "state 2 or 004076E2" handlers and two
   value copies. */
#include "uihandlers4.h"
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("G01271060")
#undef G01271060
#pragma push_macro("G01271060") /*gvi*/
#undef G01271060 /*gvi*/
int32_t G01271060;
#pragma pop_macro("G01271060") /*gvi*/
#pragma pop_macro("G01271060")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("G00549FBC")
#undef G00549FBC
#pragma push_macro("G00549FBC") /*gvi*/
#undef G00549FBC /*gvi*/
int32_t G00549FBC;
#pragma pop_macro("G00549FBC") /*gvi*/
#pragma pop_macro("G00549FBC")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("G00549FCC")
#undef G00549FCC
#pragma push_macro("G00549FCC") /*gvi*/
#undef G00549FCC /*gvi*/
int32_t G00549FCC;
#pragma pop_macro("G00549FCC") /*gvi*/
#pragma pop_macro("G00549FCC")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("G0054A0BC")
#undef G0054A0BC
#pragma push_macro("G0054A0BC") /*gvi*/
#undef G0054A0BC /*gvi*/
int32_t G0054A0BC;
#pragma pop_macro("G0054A0BC") /*gvi*/
#pragma pop_macro("G0054A0BC")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("G0054A0C0")
#undef G0054A0C0
#pragma push_macro("G0054A0C0") /*gvi*/
#undef G0054A0C0 /*gvi*/
int32_t G0054A0C0;
#pragma pop_macro("G0054A0C0") /*gvi*/
#pragma pop_macro("G0054A0C0")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("G0054A0CC")
#undef G0054A0CC
#pragma push_macro("G0054A0CC") /*gvi*/
#undef G0054A0CC /*gvi*/
int32_t G0054A0CC;
#pragma pop_macro("G0054A0CC") /*gvi*/
#pragma pop_macro("G0054A0CC")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("G0054A0D0")
#undef G0054A0D0
#pragma push_macro("G0054A0D0") /*gvi*/
#undef G0054A0D0 /*gvi*/
int32_t G0054A0D0;
#pragma pop_macro("G0054A0D0") /*gvi*/
#pragma pop_macro("G0054A0D0")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("G0054A838")
#undef G0054A838
#pragma push_macro("G0054A838") /*gvi*/
#undef G0054A838 /*gvi*/
int32_t G0054A838;
#pragma pop_macro("G0054A838") /*gvi*/
#pragma pop_macro("G0054A838")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("G0054A844")
#undef G0054A844
#pragma push_macro("G0054A844") /*gvi*/
#undef G0054A844 /*gvi*/
int32_t G0054A844;
#pragma pop_macro("G0054A844") /*gvi*/
#pragma pop_macro("G0054A844")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("G0054A848")
#undef G0054A848
#pragma push_macro("G0054A848") /*gvi*/
#undef G0054A848 /*gvi*/
int32_t G0054A848;
#pragma pop_macro("G0054A848") /*gvi*/
#pragma pop_macro("G0054A848")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("G0054A854")
#undef G0054A854
#pragma push_macro("G0054A854") /*gvi*/
#undef G0054A854 /*gvi*/
int32_t G0054A854;
#pragma pop_macro("G0054A854") /*gvi*/
#pragma pop_macro("G0054A854")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("G0054A858")
#undef G0054A858
#pragma push_macro("G0054A858") /*gvi*/
#undef G0054A858 /*gvi*/
int32_t G0054A858;
#pragma pop_macro("G0054A858") /*gvi*/
#pragma pop_macro("G0054A858")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("G0054A8EC")
#undef G0054A8EC
#pragma push_macro("G0054A8EC") /*gvi*/
#undef G0054A8EC /*gvi*/
int32_t G0054A8EC;
#pragma pop_macro("G0054A8EC") /*gvi*/
#pragma pop_macro("G0054A8EC")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("G0054A8FC")
#undef G0054A8FC
#pragma push_macro("G0054A8FC") /*gvi*/
#undef G0054A8FC /*gvi*/
int32_t G0054A8FC;
#pragma pop_macro("G0054A8FC") /*gvi*/
#pragma pop_macro("G0054A8FC")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("G0054A90C")
#undef G0054A90C
#pragma push_macro("G0054A90C") /*gvi*/
#undef G0054A90C /*gvi*/
int32_t G0054A90C;
#pragma pop_macro("G0054A90C") /*gvi*/
#pragma pop_macro("G0054A90C")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("G0054A91C")
#undef G0054A91C
#pragma push_macro("G0054A91C") /*gvi*/
#undef G0054A91C /*gvi*/
int32_t G0054A91C;
#pragma pop_macro("G0054A91C") /*gvi*/
#pragma pop_macro("G0054A91C")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("G0054A92C")
#undef G0054A92C
#pragma push_macro("G0054A92C") /*gvi*/
#undef G0054A92C /*gvi*/
int32_t G0054A92C;
#pragma pop_macro("G0054A92C") /*gvi*/
#pragma pop_macro("G0054A92C")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("G0054A93C")
#undef G0054A93C
#pragma push_macro("G0054A93C") /*gvi*/
#undef G0054A93C /*gvi*/
int32_t G0054A93C;
#pragma pop_macro("G0054A93C") /*gvi*/
#pragma pop_macro("G0054A93C")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("G0054A94C")
#undef G0054A94C
#pragma push_macro("G0054A94C") /*gvi*/
#undef G0054A94C /*gvi*/
int32_t G0054A94C;
#pragma pop_macro("G0054A94C") /*gvi*/
#pragma pop_macro("G0054A94C")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("G0055384C")
#undef G0055384C
#pragma push_macro("G0055384C") /*gvi*/
#undef G0055384C /*gvi*/
int32_t G0055384C;
#pragma pop_macro("G0055384C") /*gvi*/
#pragma pop_macro("G0055384C")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("G00553850")
#undef G00553850
#pragma push_macro("G00553850") /*gvi*/
#undef G00553850 /*gvi*/
int32_t G00553850;
#pragma pop_macro("G00553850") /*gvi*/
#pragma pop_macro("G00553850")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("G0055C974")
#undef G0055C974
#pragma push_macro("G0055C974") /*gvi*/
#undef G0055C974 /*gvi*/
int32_t G0055C974;
#pragma pop_macro("G0055C974") /*gvi*/
#pragma pop_macro("G0055C974")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("G005759A4")
#undef G005759A4
#pragma push_macro("G005759A4") /*gvi*/
#undef G005759A4 /*gvi*/
int32_t G005759A4;
#pragma pop_macro("G005759A4") /*gvi*/
#pragma pop_macro("G005759A4")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("G00575EE8")
#undef G00575EE8
#pragma push_macro("G00575EE8") /*gvi*/
#undef G00575EE8 /*gvi*/
int32_t G00575EE8;
#pragma pop_macro("G00575EE8") /*gvi*/
#pragma pop_macro("G00575EE8")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("G00575EF0")
#undef G00575EF0
#pragma push_macro("G00575EF0") /*gvi*/
#undef G00575EF0 /*gvi*/
int32_t G00575EF0;
#pragma pop_macro("G00575EF0") /*gvi*/
#pragma pop_macro("G00575EF0")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("G00575EF8")
#undef G00575EF8
#pragma push_macro("G00575EF8") /*gvi*/
#undef G00575EF8 /*gvi*/
int32_t G00575EF8;
#pragma pop_macro("G00575EF8") /*gvi*/
#pragma pop_macro("G00575EF8")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("G00575F30")
#undef G00575F30
#pragma push_macro("G00575F30") /*gvi*/
#undef G00575F30 /*gvi*/
int32_t G00575F30;
#pragma pop_macro("G00575F30") /*gvi*/
#pragma pop_macro("G00575F30")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("G00575F3C")
#undef G00575F3C
#pragma push_macro("G00575F3C") /*gvi*/
#undef G00575F3C /*gvi*/
int32_t G00575F3C;
#pragma pop_macro("G00575F3C") /*gvi*/
#pragma pop_macro("G00575F3C")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("G00575F44")
#undef G00575F44
#pragma push_macro("G00575F44") /*gvi*/
#undef G00575F44 /*gvi*/
int32_t G00575F44;
#pragma pop_macro("G00575F44") /*gvi*/
#pragma pop_macro("G00575F44")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("G005D577C")
#undef G005D577C
#pragma push_macro("G005D577C") /*gvi*/
#undef G005D577C /*gvi*/
int32_t G005D577C;
#pragma pop_macro("G005D577C") /*gvi*/
#pragma pop_macro("G005D577C")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("G005F7E4C")
#undef G005F7E4C
#pragma push_macro("G005F7E4C") /*gvi*/
#undef G005F7E4C /*gvi*/
int32_t G005F7E4C;
#pragma pop_macro("G005F7E4C") /*gvi*/
#pragma pop_macro("G005F7E4C")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("G00B201DC")
#undef G00B201DC
#pragma push_macro("G00B201DC") /*gvi*/
#undef G00B201DC /*gvi*/
int32_t G00B201DC;
#pragma pop_macro("G00B201DC") /*gvi*/
#pragma pop_macro("G00B201DC")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("G00B31F04")
#undef G00B31F04
#pragma push_macro("G00B31F04") /*gvi*/
#undef G00B31F04 /*gvi*/
int32_t G00B31F04;
#pragma pop_macro("G00B31F04") /*gvi*/
#pragma pop_macro("G00B31F04")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("G00B87E4C")
#undef G00B87E4C
#pragma push_macro("G00B87E4C") /*gvi*/
#undef G00B87E4C /*gvi*/
int32_t G00B87E4C;
#pragma pop_macro("G00B87E4C") /*gvi*/
#pragma pop_macro("G00B87E4C")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("G00B87E9C")
#undef G00B87E9C
#pragma push_macro("G00B87E9C") /*gvi*/
#undef G00B87E9C /*gvi*/
int32_t G00B87E9C;
#pragma pop_macro("G00B87E9C") /*gvi*/
#pragma pop_macro("G00B87E9C")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("G00BDFA44")
#undef G00BDFA44
#pragma push_macro("G00BDFA44") /*gvi*/
#undef G00BDFA44 /*gvi*/
int32_t G00BDFA44;
#pragma pop_macro("G00BDFA44") /*gvi*/
#pragma pop_macro("G00BDFA44")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("G00BDFA48")
#undef G00BDFA48
#pragma push_macro("G00BDFA48") /*gvi*/
#undef G00BDFA48 /*gvi*/
int32_t G00BDFA48;
#pragma pop_macro("G00BDFA48") /*gvi*/
#pragma pop_macro("G00BDFA48")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("G00BDFA4C")
#undef G00BDFA4C
#pragma push_macro("G00BDFA4C") /*gvi*/
#undef G00BDFA4C /*gvi*/
int32_t G00BDFA4C;
#pragma pop_macro("G00BDFA4C") /*gvi*/
#pragma pop_macro("G00BDFA4C")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("G00BDFA50")
#undef G00BDFA50
#pragma push_macro("G00BDFA50") /*gvi*/
#undef G00BDFA50 /*gvi*/
int32_t G00BDFA50;
#pragma pop_macro("G00BDFA50") /*gvi*/
#pragma pop_macro("G00BDFA50")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("G00BDFA54")
#undef G00BDFA54
#pragma push_macro("G00BDFA54") /*gvi*/
#undef G00BDFA54 /*gvi*/
int32_t G00BDFA54;
#pragma pop_macro("G00BDFA54") /*gvi*/
#pragma pop_macro("G00BDFA54")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("G00BDFA58")
#undef G00BDFA58
#pragma push_macro("G00BDFA58") /*gvi*/
#undef G00BDFA58 /*gvi*/
int32_t G00BDFA58;
#pragma pop_macro("G00BDFA58") /*gvi*/
#pragma pop_macro("G00BDFA58")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("G00C559A4")
#undef G00C559A4
#pragma push_macro("G00C559A4") /*gvi*/
#undef G00C559A4 /*gvi*/
int32_t G00C559A4;
#pragma pop_macro("G00C559A4") /*gvi*/
#pragma pop_macro("G00C559A4")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("G00C559A8")
#undef G00C559A8
#pragma push_macro("G00C559A8") /*gvi*/
#undef G00C559A8 /*gvi*/
int32_t G00C559A8;
#pragma pop_macro("G00C559A8") /*gvi*/
#pragma pop_macro("G00C559A8")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("G00C559F0")
#undef G00C559F0
#pragma push_macro("G00C559F0") /*gvi*/
#undef G00C559F0 /*gvi*/
int32_t G00C559F0;
#pragma pop_macro("G00C559F0") /*gvi*/
#pragma pop_macro("G00C559F0")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("G00C559F4")
#undef G00C559F4
#pragma push_macro("G00C559F4") /*gvi*/
#undef G00C559F4 /*gvi*/
int32_t G00C559F4;
#pragma pop_macro("G00C559F4") /*gvi*/
#pragma pop_macro("G00C559F4")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("G00C55A04")
#undef G00C55A04
#pragma push_macro("G00C55A04") /*gvi*/
#undef G00C55A04 /*gvi*/
int32_t G00C55A04;
#pragma pop_macro("G00C55A04") /*gvi*/
#pragma pop_macro("G00C55A04")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("G00D118C8")
#undef G00D118C8
#pragma push_macro("G00D118C8") /*gvi*/
#undef G00D118C8 /*gvi*/
int32_t G00D118C8;
#pragma pop_macro("G00D118C8") /*gvi*/
#pragma pop_macro("G00D118C8")
#endif
/* Set5F7E4C_1 — Game.exe 00404687 */
void Set5F7E4C_1(void) { G005F7E4C = 1;
}
/* Set54A0CC_0 — Game.exe 0040844c */
void Set54A0CC_0(void) { G0054A0CC = 0;
}
/* Set54A0BC_1 — Game.exe 00408337 */
void Set54A0BC_1(void) { G0054A0BC = 1;
}
/* Set54A0BC_0 — Game.exe 00408343 */
void Set54A0BC_0(void) { G0054A0BC = 0;
}
/* Inc5D577C — Game.exe 00408710 */
void Inc5D577C(void) { G005D577C++;
}
/* Set54A844_1 — Game.exe 0040a443 */
void Set54A844_1(void) { G0054A844 = 1;
}
/* Set54A844_0 — Game.exe 0040a44f */
void Set54A844_0(void) { G0054A844 = 0;
}
/* Set54A854_1 — Game.exe 0040a495 */
void Set54A854_1(void) { G0054A854 = 1;
}
/* Set54A854_0 — Game.exe 0040a4a1 */
void Set54A854_0(void) { G0054A854 = 0;
}
/* Set575EF0_4Ret0 — Game.exe 00404f5f */
int32_t Set575EF0_4Ret0(void) { G00575EF0 = 4; return 0;
}
/* ToggleBDFA44_Call40500D — Game.exe 00404eb0 */
int32_t ToggleBDFA44_Call40500D(void) { G00BDFA44 ^= 1; MenuRefresh(); return 0;
}
/* ToggleBDFA48_Call40500D — Game.exe 00404ec9 */
int32_t ToggleBDFA48_Call40500D(void) { G00BDFA48 ^= 1; MenuRefresh(); return 0;
}
/* ToggleBDFA4C_Call40500D — Game.exe 00404ee2 */
int32_t ToggleBDFA4C_Call40500D(void) { G00BDFA4C ^= 1; MenuRefresh(); return 0;
}
/* ToggleBDFA50_Call40500D — Game.exe 00404efb */
int32_t ToggleBDFA50_Call40500D(void) { G00BDFA50 ^= 1; MenuRefresh(); return 0;
}
/* ToggleBDFA54_Call40500D — Game.exe 00404f14 */
int32_t ToggleBDFA54_Call40500D(void) { G00BDFA54 ^= 1; MenuRefresh(); return 0;
}
/* ToggleB87E9C_Call40500D — Game.exe 00404f2d */
int32_t ToggleB87E9C_Call40500D(void) { G00B87E9C ^= 1; MenuRefresh(); return 0;
}
/* ToggleBDFA58_Call40500D — Game.exe 00404f46 */
int32_t ToggleBDFA58_Call40500D(void) { G00BDFA58 ^= 1; MenuRefresh(); return 0;
}
/* ToggleEF8_55384C — Game.exe 00408a69 */
int32_t ToggleEF8_55384C(void) { G0055384C ^= 1; G00575EF8 = 4; MenuRedraw(); return 0;
}
/* ToggleEF8_553850 — Game.exe 00408b03 */
int32_t ToggleEF8_553850(void) { G00553850 ^= 1; G00575EF8 = 4; MenuRedraw(); return 0;
}
/* ToggleEF8_B31F04 — Game.exe 00408b9d */
int32_t ToggleEF8_B31F04(void) { G00B31F04 ^= 1; G00575EF8 = 4; MenuRedraw(); return 0;
}
/* ToggleEF8_575F44 — Game.exe 00408d0c */
int32_t ToggleEF8_575F44(void) { G00575F44 ^= 1; G00575EF8 = 4; MenuRedraw(); return 0;
}
/* ToggleEF8_55C974 — Game.exe 00408da6 */
int32_t ToggleEF8_55C974(void) { G0055C974 ^= 1; G00575EF8 = 4; MenuRedraw(); return 0;
}
/* ToggleEF8_575F30 — Game.exe 00408e40 */
int32_t ToggleEF8_575F30(void) { G00575F30 ^= 1; G00575EF8 = 4; MenuRedraw(); return 0;
}
/* ToggleEF8_B201DC — Game.exe 00408eda */
int32_t ToggleEF8_B201DC(void) { G00B201DC ^= 1; G00575EF8 = 4; MenuRedraw(); return 0;
}
/* ToggleEF8_575EE8 — Game.exe 00408f74 */
int32_t ToggleEF8_575EE8(void) { G00575EE8 ^= 1; G00575EF8 = 4; MenuRedraw(); return 0;
}
/* ToggleEF8_575F3C — Game.exe 0040900e */
int32_t ToggleEF8_575F3C(void) { G00575F3C ^= 1; G00575EF8 = 4; MenuRedraw(); return 0;
}
/* ToggleEF8_D118C8 — Game.exe 004090a8 */
int32_t ToggleEF8_D118C8(void) { G00D118C8 ^= 1; G00575EF8 = 4; MenuRedraw(); return 0;
}
/* RefreshMenu00409231 — Game.exe 00409231 */
int32_t RefreshMenu00409231(void) { G00575EF8 = 4; MenuRedraw(); return 0;
}
/* RefreshMenu004092D8 — Game.exe 004092d8 */
int32_t RefreshMenu004092D8(void) { G00575EF8 = 4; MenuRedraw(); return 0;
}
/* RefreshMenu0040937F — Game.exe 0040937f */
int32_t RefreshMenu0040937F(void) { G00575EF8 = 4; MenuRedraw(); return 0;
}
/* RefreshMenu00409426 — Game.exe 00409426 */
int32_t RefreshMenu00409426(void) { G00575EF8 = 4; MenuRedraw(); return 0;
}
/* RefreshMenu004094CD — Game.exe 004094cd */
int32_t RefreshMenu004094CD(void) { G00575EF8 = 4; MenuRedraw(); return 0;
}
/* Inc5759A4Max40 — Game.exe 00409b75 */
void Inc5759A4Max40(void) { if (G005759A4 < 64) { G005759A4++; G00575EF8 = 4; MenuRedraw(); }
}
/* Dec5759A4Min0 — Game.exe 00409b9f */
void Dec5759A4Min0(void) { if (G005759A4 > 0) { G005759A4--; G00575EF8 = 4; MenuRedraw(); }
}
/* IncB87E4CMax3 — Game.exe 00409c31 */
void IncB87E4CMax3(void) { if (G00B87E4C < 3) { G00B87E4C++; G00575EF8 = 4; MenuRedraw(); }
}
/* DecB87E4CMin0 — Game.exe 00409c5b */
void DecB87E4CMin0(void) { if (G00B87E4C > 0) { G00B87E4C--; G00575EF8 = 4; MenuRedraw(); }
}
/* Select54A*_ModeN — Driving Games menu 0054a968 (RE_PROBE menu walk): mode 4 Pursuit, 5 Getaway, 2 Cross Town
   Checkpoint, 1 Trail Blazer, 3 Survival, 6 Dirt Track (then Practice 6 / Time Trial 0xb), 7 Carnage. */
/* Select54A90C_Mode2 — Game.exe 0040a625 */
void Select54A90C_Mode2(void) { G0054A90C = 1; G01271060 = 2;
}
/* Select54A91C_Mode1 — Game.exe 0040a64d */
void Select54A91C_Mode1(void) { G0054A91C = 1; G01271060 = 1;
}
/* Select54A8FC_Mode5 — Game.exe 0040a675 */
void Select54A8FC_Mode5(void) { G0054A8FC = 1; G01271060 = 5;
}
/* Select54A92C_Mode3 — Game.exe 0040a69d */
void Select54A92C_Mode3(void) { G0054A92C = 1; G01271060 = 3;
}
/* Select54A8EC_Mode4 — Game.exe 0040a6c5 */
void Select54A8EC_Mode4(void) { G0054A8EC = 1; G01271060 = 4;
}
/* Select54A94C_Mode7 — Game.exe 0040a6ed */
void Select54A94C_Mode7(void) { G0054A94C = 1; G01271060 = 7;
}
/* Select54A93C_Mode6 — Game.exe 0040a715 */
void Select54A93C_Mode6(void) { G0054A93C = 1; G01271060 = 6;
}
/* Clear54A90C_IfZero — Game.exe 0040a63b */
void Clear54A90C_IfZero(int32_t a0) { if (a0 == 0) G0054A90C = 0;
}
/* Clear54A91C_IfZero — Game.exe 0040a663 */
void Clear54A91C_IfZero(int32_t a0) { if (a0 == 0) G0054A91C = 0;
}
/* Clear54A8FC_IfZero — Game.exe 0040a68b */
void Clear54A8FC_IfZero(int32_t a0) { if (a0 == 0) G0054A8FC = 0;
}
/* Clear54A92C_IfZero — Game.exe 0040a6b3 */
void Clear54A92C_IfZero(int32_t a0) { if (a0 == 0) G0054A92C = 0;
}
/* Clear54A8EC_IfZero — Game.exe 0040a6db */
void Clear54A8EC_IfZero(int32_t a0) { if (a0 == 0) G0054A8EC = 0;
}
/* Clear54A94C_IfZero — Game.exe 0040a703 */
void Clear54A94C_IfZero(int32_t a0) { if (a0 == 0) G0054A94C = 0;
}
/* Menu549FBC / Menu549FCC: argument 0 sets the variable to 2, argument 2 calls 004076E2 (TODO(RE): unsure). */
/* Menu549FBC — Game.exe 00407460 */
void Menu549FBC(int32_t a0) { if (a0 == 0) G00549FBC = 2; else if (a0 == 2) Call004076E2();
}
/* Menu549FCC — Game.exe 00407539 */
void Menu549FCC(int32_t a0) { if (a0 == 0) G00549FCC = 2; else if (a0 == 2) Call004076E2();
}
/* Copy54A0C0 — Game.exe 0040831c */
void Copy54A0C0(void) { G0054A0C0 = G00C559A4; G0054A0D0 = G00C559A8;
}
/* Copy54A838 — Game.exe 0040a41c */
void Copy54A838(void) { G0054A838 = G00C55A04; G0054A848 = G00C559F0; G0054A858 = G00C559F4;
}
