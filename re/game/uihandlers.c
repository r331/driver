/* uihandlers.c — simple front-end menu handlers: setters and screen transitions (English overview).
   The address in each name UiXXXXXXXX is its Game.exe address (do not rename).  Menu tables call these
   through function pointers: "enter" handlers usually take `mode` (0 = normal entry) and set a flag,
   "leave" handlers clear it, "select" handlers return a menu result (1 / -1 / 0). */
#include "uihandlers.h"
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("UiVar00B87E38")
#undef UiVar00B87E38
#pragma push_macro("UiVar00B87E38") /*gvi*/
#undef UiVar00B87E38 /*gvi*/
int32_t UiVar00B87E38;
#pragma pop_macro("UiVar00B87E38") /*gvi*/
#pragma pop_macro("UiVar00B87E38")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("UiVar005FE84C")
#undef UiVar005FE84C
#pragma push_macro("UiVar005FE84C") /*gvi*/
#undef UiVar005FE84C /*gvi*/
int32_t UiVar005FE84C;
#pragma pop_macro("UiVar005FE84C") /*gvi*/
#pragma pop_macro("UiVar005FE84C")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("UiVar005FE850")
#undef UiVar005FE850
#pragma push_macro("UiVar005FE850") /*gvi*/
#undef UiVar005FE850 /*gvi*/
int32_t UiVar005FE850;
#pragma pop_macro("UiVar005FE850") /*gvi*/
#pragma pop_macro("UiVar005FE850")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("UiVar005FE928")
#undef UiVar005FE928
#pragma push_macro("UiVar005FE928") /*gvi*/
#undef UiVar005FE928 /*gvi*/
int32_t UiVar005FE928;
#pragma pop_macro("UiVar005FE928") /*gvi*/
#pragma pop_macro("UiVar005FE928")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("UiVar005FE92C")
#undef UiVar005FE92C
#pragma push_macro("UiVar005FE92C") /*gvi*/
#undef UiVar005FE92C /*gvi*/
int32_t UiVar005FE92C;
#pragma pop_macro("UiVar005FE92C") /*gvi*/
#pragma pop_macro("UiVar005FE92C")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("UiVar0054CC64")
#undef UiVar0054CC64
#pragma push_macro("UiVar0054CC64") /*gvi*/
#undef UiVar0054CC64 /*gvi*/
uint8_t UiVar0054CC64;
#pragma pop_macro("UiVar0054CC64") /*gvi*/
#pragma pop_macro("UiVar0054CC64")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("UiVar0054CC74")
#undef UiVar0054CC74
#pragma push_macro("UiVar0054CC74") /*gvi*/
#undef UiVar0054CC74 /*gvi*/
uint8_t UiVar0054CC74;
#pragma pop_macro("UiVar0054CC74") /*gvi*/
#pragma pop_macro("UiVar0054CC74")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("UiVar0054D10C")
#undef UiVar0054D10C
#pragma push_macro("UiVar0054D10C") /*gvi*/
#undef UiVar0054D10C /*gvi*/
uint8_t UiVar0054D10C;
#pragma pop_macro("UiVar0054D10C") /*gvi*/
#pragma pop_macro("UiVar0054D10C")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("UiVar0054D11C")
#undef UiVar0054D11C
#pragma push_macro("UiVar0054D11C") /*gvi*/
#undef UiVar0054D11C /*gvi*/
uint8_t UiVar0054D11C;
#pragma pop_macro("UiVar0054D11C") /*gvi*/
#pragma pop_macro("UiVar0054D11C")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("UiVar0054BF18")
#undef UiVar0054BF18
#pragma push_macro("UiVar0054BF18") /*gvi*/
#undef UiVar0054BF18 /*gvi*/
int32_t UiVar0054BF18;
#pragma pop_macro("UiVar0054BF18") /*gvi*/
#pragma pop_macro("UiVar0054BF18")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("UiVar005FE6BC")
#undef UiVar005FE6BC
#pragma push_macro("UiVar005FE6BC") /*gvi*/
#undef UiVar005FE6BC /*gvi*/
int32_t UiVar005FE6BC;
#pragma pop_macro("UiVar005FE6BC") /*gvi*/
#pragma pop_macro("UiVar005FE6BC")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("UiVar005FEA30")
#undef UiVar005FEA30
#pragma push_macro("UiVar005FEA30") /*gvi*/
#undef UiVar005FEA30 /*gvi*/
int32_t UiVar005FEA30;
#pragma pop_macro("UiVar005FEA30") /*gvi*/
#pragma pop_macro("UiVar005FEA30")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("UiVar0054E4B0")
#undef UiVar0054E4B0
#pragma push_macro("UiVar0054E4B0") /*gvi*/
#undef UiVar0054E4B0 /*gvi*/
int32_t UiVar0054E4B0;
#pragma pop_macro("UiVar0054E4B0") /*gvi*/
#pragma pop_macro("UiVar0054E4B0")
#endif
/* Ui00408699 — Game.exe 00408699.  Sets 00b87e38 = 0x295 and redraws the menu (0040c455(1, 0)).
   TODO(RE): unsure what 0x295 selects. */
void Ui00408699(void) {
    UiVar00B87E38 = 0x295;
    UiCall0040C455(1,0);
}
/* Ui0040C867 / Ui0040C87A / Ui0040C88D — Game.exe 0040c867 / 0040c87a / 0040c88d.  Play front-end sound
   0 / 1 / 2 of bank 9 (00523e50(n, 9, -1)). */
void Ui0040C867(void) {
    UiCall00523E50(0,9,0xffffffff);
}
void Ui0040C87A(void) {
    UiCall00523E50(1,9,0xffffffff);
}
void Ui0040C88D(void) {
    UiCall00523E50(2,9,0xffffffff);
}
/* Ui004120EE — Game.exe 004120ee.  On normal entry (mode 0) resets the selected row's lines (00412254). */
void Ui004120EE(int32_t mode) {
    if (mode == 0) {
        UiCall00412254();
    }
}
/* Ui004120FE ... Ui0041218A — Game.exe 004120fe ... 0041218a.  Select row 0..7 of the first 8-row menu
   (005fe84c) and apply it (00412228). */
void Ui004120FE(void) {
    UiVar005FE84C = 0;
    UiCall00412228();
}
void Ui00412112(void) {
    UiVar005FE84C = 1;
    UiCall00412228();
}
void Ui00412126(void) {
    UiVar005FE84C = 2;
    UiCall00412228();
}
void Ui0041213A(void) {
    UiVar005FE84C = 3;
    UiCall00412228();
}
void Ui0041214E(void) {
    UiVar005FE84C = 4;
    UiCall00412228();
}
void Ui00412162(void) {
    UiVar005FE84C = 5;
    UiCall00412228();
}
void Ui00412176(void) {
    UiVar005FE84C = 6;
    UiCall00412228();
}
void Ui0041218A(void) {
    UiVar005FE84C = 7;
    UiCall00412228();
}
/* Ui004122E7 — Game.exe 004122e7.  005fe850 = 0, then 00412087. */
void Ui004122E7(void) {
    UiVar005FE850 = 0;
    UiCall00412087();
}
/* Ui00412509 — Game.exe 00412509.  On normal entry (mode 0) resets the selected row's lines (0041266f). */
void Ui00412509(int32_t mode) {
    if (mode == 0) {
        UiCall0041266F();
    }
}
/* Ui00412519 ... Ui004125A5 — Game.exe 00412519 ... 004125a5.  Select row 0..7 of the second 8-row menu
   (005fe928) and highlight it (00412643). */
void Ui00412519(void) {
    UiVar005FE928 = 0;
    UiCall00412643();
}
void Ui0041252D(void) {
    UiVar005FE928 = 1;
    UiCall00412643();
}
void Ui00412541(void) {
    UiVar005FE928 = 2;
    UiCall00412643();
}
void Ui00412555(void) {
    UiVar005FE928 = 3;
    UiCall00412643();
}
void Ui00412569(void) {
    UiVar005FE928 = 4;
    UiCall00412643();
}
void Ui0041257D(void) {
    UiVar005FE928 = 5;
    UiCall00412643();
}
void Ui00412591(void) {
    UiVar005FE928 = 6;
    UiCall00412643();
}
void Ui004125A5(void) {
    UiVar005FE928 = 7;
    UiCall00412643();
}
/* Ui00412702 — Game.exe 00412702.  005fe92c = 0, then 00412487. */
void Ui00412702(void) {
    UiVar005FE92C = 0;
    UiCall00412487();
}
/* Ui00412F3A / Ui00412F56 / Ui00412F62 — Game.exe 00412f3a / 00412f56 / 00412f62.  Enter (flag 0054cc64 = 1,
   reset the menu counter 005d577c on normal entry) / leave (flag = 0) / select (reset counter, return -1). */
void Ui00412F3A(int32_t mode) {
    UiVar0054CC64 = 1;
    if (mode == 0) {
        MenuCounter5D577C = 0;
    }
}
void Ui00412F56(void) {
    UiVar0054CC64 = 0;
}
int32_t Ui00412F62(void) {
    MenuCounter5D577C = 0;
    return -1;
}
/* Ui00412F74 / Ui00412F90 / Ui00412F9C — Game.exe 00412f74 / 00412f90 / 00412f9c.  Same for flag 0054cc74;
   the select handler returns 1. */
void Ui00412F74(int32_t mode) {
    UiVar0054CC74 = 1;
    if (mode == 0) {
        MenuCounter5D577C = 0;
    }
}
void Ui00412F90(void) {
    UiVar0054CC74 = 0;
}
int32_t Ui00412F9C(void) {
    MenuCounter5D577C = 0;
    return 1;
}
/* Ui00413543 / Ui0041354F — Game.exe 00413543 / 0041354f.  Set / clear flag 0054d10c. */
void Ui00413543(void) {
    UiVar0054D10C = 1;
}
void Ui0041354F(void) {
    UiVar0054D10C = 0;
}
/* Ui0041355B — Game.exe 0041355b.  Leaves the menu (0040cd17), switches to front-end menu mode 9 and opens it
   (0040c480(0)).  Returns 1. */
int32_t Ui0041355B(void) {
    MenuAction40CD17();
    MenuMode1271060 = 9;
    UiCall0040C480(0);
    return 1;
}
/* Ui0041357E / Ui0041358A — Game.exe 0041357e / 0041358a.  Set / clear flag 0054d11c. */
void Ui0041357E(void) {
    UiVar0054D11C = 1;
}
void Ui0041358A(void) {
    UiVar0054D11C = 0;
}
/* Ui004136CE ... Ui004139A3 — Game.exe 004136ce ... 004139a3.  Mark one menu item's state byte
   (0054d1b4 ... 0054d2b4) as 1.  TODO(RE): unsure what state 1 is (highlighted?). */
void Ui004136CE(void) {
    MenuB0054D1B4 = 1;
}
void Ui0041371C(void) {
    MenuB0054D1C4 = 1;
}
void Ui0041376A(void) {
    MenuB0054D1D4 = 1;
}
void Ui004137B8(void) {
    MenuB0054D1E4 = 1;
}
void Ui00413955(void) {
    MenuB0054D2A4 = 1;
}
void Ui004139A3(void) {
    MenuB0054D2B4 = 1;
}
/* Ui004139C1 / Ui004139F8 / Ui00413A2F / Ui00413A66 — Game.exe 004139c1 / 004139f8 / 00413a2f / 00413a66.
   Leave the menu and start choice 0 / 1 / 2 / 3 of 00408600.  Return 1.  The state-byte setters
   Ui004139DA / Ui00413A11 / Ui00413A48 sit between them (0054d2c4 / d4 / e4 = 1). */
int32_t Ui004139C1(void) {
    MenuAction40CD17();
    UiCall00408600(0);
    return 1;
}
void Ui004139DA(void) {
    MenuB0054D2C4 = 1;
}
int32_t Ui004139F8(void) {
    MenuAction40CD17();
    UiCall00408600(1);
    return 1;
}
void Ui00413A11(void) {
    MenuB0054D2D4 = 1;
}
int32_t Ui00413A2F(void) {
    MenuAction40CD17();
    UiCall00408600(2);
    return 1;
}
void Ui00413A48(void) {
    MenuB0054D2E4 = 1;
}
int32_t Ui00413A66(void) {
    MenuAction40CD17();
    UiCall00408600(3);
    return 1;
}
/* Ui00413BC5 ... Ui00413C8D — Game.exe 00413bc5 ... 00413c8d.  High-score menu items: mark the item and pick
   the high-score table shown by P141_HsSetup (UiVar0054BF18 = 2, 1, 3, 0xb, 7), starting at level 0. */
void Ui00413BC5(void) {
    MenuB0054D3BC = 1;
    UiVar0054BF18 = 2;
    UiVar005FE6BC = 0;
}
void Ui00413BF7(void) {
    MenuB0054D3CC = 1;
    UiVar0054BF18 = 1;
    UiVar005FE6BC = 0;
}
void Ui00413C29(void) {
    MenuB0054D3DC = 1;
    UiVar0054BF18 = 3;
    UiVar005FE6BC = 0;
}
void Ui00413C5B(void) {
    MenuB0054D3EC = 1;
    UiVar0054BF18 = 0xb;
    UiVar005FE6BC = 0;
}
void Ui00413C8D(void) {
    MenuB0054D3FC = 1;
    UiVar0054BF18 = 7;
    UiVar005FE6BC = 0;
}
/* Ui004157A9 / Ui00415841 — Game.exe 004157a9 / 00415841.  Empty handlers returning 0. */
int32_t Ui004157A9(void) {
    return 0;
}
int32_t Ui00415841(void) {
    return 0;
}
/* Ui00417A89 / Ui00417A98 / Ui00417AD6 / Ui00417AEA / Ui00417AF9 — Game.exe 00417a89 ... 00417af9.
   005fea30 = 1 or 2 (selected entry) and redraw (00417aa2); Ui00417AD6 ends the screen with result 0
   (UiVar0054E4B0 = 0, return 1) — see P67_Menu417970. */
void Ui00417A89(void) {
    UiVar005FEA30 = 1;
}
void Ui00417A98(void) {
    UiCall00417AA2();
}
int32_t Ui00417AD6(void) {
    UiVar0054E4B0 = 0;
    return 1;
}
void Ui00417AEA(void) {
    UiVar005FEA30 = 2;
}
void Ui00417AF9(void) {
    UiCall00417AA2();
}
