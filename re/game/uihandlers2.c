/* Tiny UI / front-end handlers, named by their Game.exe address (UiXXXXXXXX = Game.exe 00xxxxxx).
   Each one sets a few globals and/or calls one or two functions; comments below just spell out
   what the body does.  The int-returning bodies in 0041dec1..0041faab are constant-return stubs
   from the Direct3D/Glide wrapper range of Game.exe (several are stdcall — see stdcall_tbl.h).
   TODO(RE): unsure which Glide/D3D entry each stub stands for.
   The groups 00419c2d..00419d1b (pairs) and 00419fbd..0041a045 (triples) look like menu-item
   callbacks: set the selection (005fea80/0054e654 or 005fea8c), call 00419db3 / 0041a085, and in
   the second group open a screen.  TODO(RE): unsure which menu they belong to. */
#include "uihandlers2.h"
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("UiVar005FEA80")
#undef UiVar005FEA80
#pragma push_macro("UiVar005FEA80") /*gvi*/
#undef UiVar005FEA80 /*gvi*/
int32_t UiVar005FEA80;
#pragma pop_macro("UiVar005FEA80") /*gvi*/
#pragma pop_macro("UiVar005FEA80")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("UiVar0054E654")
#undef UiVar0054E654
#pragma push_macro("UiVar0054E654") /*gvi*/
#undef UiVar0054E654 /*gvi*/
int32_t UiVar0054E654;
#pragma pop_macro("UiVar0054E654") /*gvi*/
#pragma pop_macro("UiVar0054E654")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("UiVar005FEA8C")
#undef UiVar005FEA8C
#pragma push_macro("UiVar005FEA8C") /*gvi*/
#undef UiVar005FEA8C /*gvi*/
int32_t UiVar005FEA8C;
#pragma pop_macro("UiVar005FEA8C") /*gvi*/
#pragma pop_macro("UiVar005FEA8C")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("UiVar005FEDA0")
#undef UiVar005FEDA0
#pragma push_macro("UiVar005FEDA0") /*gvi*/
#undef UiVar005FEDA0 /*gvi*/
int32_t UiVar005FEDA0;
#pragma pop_macro("UiVar005FEDA0") /*gvi*/
#pragma pop_macro("UiVar005FEDA0")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("UiVar005FEA98")
#undef UiVar005FEA98
#pragma push_macro("UiVar005FEA98") /*gvi*/
#undef UiVar005FEA98 /*gvi*/
int32_t UiVar005FEA98;
#pragma pop_macro("UiVar005FEA98") /*gvi*/
#pragma pop_macro("UiVar005FEA98")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("UiVar005FEB48")
#undef UiVar005FEB48
#pragma push_macro("UiVar005FEB48") /*gvi*/
#undef UiVar005FEB48 /*gvi*/
int32_t UiVar005FEB48;
#pragma pop_macro("UiVar005FEB48") /*gvi*/
#pragma pop_macro("UiVar005FEB48")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("UiVar01251A70")
#undef UiVar01251A70
#pragma push_macro("UiVar01251A70") /*gvi*/
#undef UiVar01251A70 /*gvi*/
uint8_t UiVar01251A70;
#pragma pop_macro("UiVar01251A70") /*gvi*/
#pragma pop_macro("UiVar01251A70")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("UiVar011F43B0")
#undef UiVar011F43B0
#pragma push_macro("UiVar011F43B0") /*gvi*/
#undef UiVar011F43B0 /*gvi*/
int32_t UiVar011F43B0;
#pragma pop_macro("UiVar011F43B0") /*gvi*/
#pragma pop_macro("UiVar011F43B0")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("UiVar00B1C280")
#undef UiVar00B1C280
#pragma push_macro("UiVar00B1C280") /*gvi*/
#undef UiVar00B1C280 /*gvi*/
int32_t UiVar00B1C280;
#pragma pop_macro("UiVar00B1C280") /*gvi*/
#pragma pop_macro("UiVar00B1C280")
#endif
/* Ui00417B03 — Game.exe 00417b03, cdecl.  0054e4b0 = 1, returns 1. */
int32_t Ui00417B03(void) {
    UiVar0054E4B0 = 1;
    return 1;
}
/* Ui004183E8 — Game.exe 004183e8, cdecl.  Calls 0041a8ab(), calls 004ee065(). */
void Ui004183E8(void) {
    UiCall0041A8AB();
    UiCall004EE065();
}
/* Ui00418886 — Game.exe 00418886, cdecl.  Calls 00523e50(0,9,0x5622). */
void Ui00418886(void) {
    UiCall00523E50(0,9,0x5622);
}
/* Ui0041889C — Game.exe 0041889c, cdecl.  Front-end frame prelude (first call of P66_ScreenFrame): calls 004184f5(), calls 005170ab(), calls 0041a8ab(). */
void Ui0041889C(void) {
    UiCall004184F5();
    UiCall005170AB();
    UiCall0041A8AB();
}
/* Ui00419C2D — Game.exe 00419c2d, cdecl.  005fea80 = 3, 0054e654 = 4. */
void Ui00419C2D(void) {
    UiVar005FEA80 = 3;
    UiVar0054E654 = 4;
}
/* Ui00419C46 — Game.exe 00419c46, cdecl.  Calls 00419db3(). */
void Ui00419C46(void) {
    UiCall00419DB3();
}
/* Ui00419C69 — Game.exe 00419c69, cdecl.  005fea80 = 5, 0054e654 = 6. */
void Ui00419C69(void) {
    UiVar005FEA80 = 5;
    UiVar0054E654 = 6;
}
/* Ui00419C82 — Game.exe 00419c82, cdecl.  Calls 00419db3(). */
void Ui00419C82(void) {
    UiCall00419DB3();
}
/* Ui00419D02 — Game.exe 00419d02, cdecl.  005fea80 = 7, 0054e654 = 8. */
void Ui00419D02(void) {
    UiVar005FEA80 = 7;
    UiVar0054E654 = 8;
}
/* Ui00419D1B — Game.exe 00419d1b, cdecl.  Calls 00419db3(). */
void Ui00419D1B(void) {
    UiCall00419DB3();
}
/* Ui00419FBD — Game.exe 00419fbd, cdecl.  005fea8c = 1. */
void Ui00419FBD(void) {
    UiVar005FEA8C = 1;
}
/* Ui00419FCC — Game.exe 00419fcc, cdecl.  Calls 0041a085(). */
void Ui00419FCC(void) {
    UiCall0041A085();
}
/* Ui00419FD6 — Game.exe 00419fd6, cdecl.  Calls 00417620(), returns 0. */
int32_t Ui00419FD6(void) {
    UiCall00417620();
    return 0;
}
/* Ui00419FE2 — Game.exe 00419fe2, cdecl.  005fea8c = 2. */
void Ui00419FE2(void) {
    UiVar005FEA8C = 2;
}
/* Ui00419FF1 — Game.exe 00419ff1, cdecl.  Calls 0041a085(). */
void Ui00419FF1(void) {
    UiCall0041A085();
}
/* Ui00419FFB — Game.exe 00419ffb, cdecl.  Calls 00414c30(), returns 0. */
int32_t Ui00419FFB(void) {
    UiCall00414C30();
    return 0;
}
/* Ui0041A007 — Game.exe 0041a007, cdecl.  005fea8c = 3. */
void Ui0041A007(void) {
    UiVar005FEA8C = 3;
}
/* Ui0041A016 — Game.exe 0041a016, cdecl.  Calls 0041a085(). */
void Ui0041A016(void) {
    UiCall0041A085();
}
/* Ui0041A020 — Game.exe 0041a020, cdecl.  Calls 00407160(), returns 0. */
int32_t Ui0041A020(void) {
    UiCall00407160();
    return 0;
}
/* Ui0041A02C — Game.exe 0041a02c, cdecl.  005fea8c = 4. */
void Ui0041A02C(void) {
    UiVar005FEA8C = 4;
}
/* Ui0041A03B — Game.exe 0041a03b, cdecl.  Calls 0041a085(). */
void Ui0041A03B(void) {
    UiCall0041A085();
}
/* Ui0041A045 — Game.exe 0041a045, cdecl.  Calls 00419ab0(), returns 0. */
int32_t Ui0041A045(void) {
    UiCall00419AB0();
    return 0;
}
/* Ui0041A192 — Game.exe 0041a192, cdecl.  005feda0 = 0, 005fea98 = 0, 005feb48 = 0. */
void Ui0041A192(void) {
    UiVar005FEDA0 = 0;
    UiVar005FEA98 = 0;
    UiVar005FEB48 = 0;
}
/* Ui0041AE25 — Game.exe 0041ae25, cdecl.  Calls 0041b059(). */
void Ui0041AE25(void) {
    UiCall0041B059();
}
/* Ui0041D94A — Game.exe 0041d94a, cdecl.  Calls 0041f2a0(). */
void Ui0041D94A(void) {
    UiCall0041F2A0();
}
/* Ui0041DEC1 — Game.exe 0041dec1, cdecl.  Returns 0. */
int32_t Ui0041DEC1(void) {
    return 0;
}
/* Ui0041EC79 — Game.exe 0041ec79, stdcall (ret 28).  Returns 0. */
int32_t Ui0041EC79(void) {
    return 0;
}
/* Ui0041ED0E — Game.exe 0041ed0e, stdcall (ret 32).  Returns 1. */
int32_t Ui0041ED0E(void) {
    return 1;
}
/* Ui0041ED2D — Game.exe 0041ed2d, stdcall (ret 4).  Returns 1. */
int32_t Ui0041ED2D(void) {
    return 1;
}
/* Ui0041ED3E — Game.exe 0041ed3e, cdecl.  Returns 0. */
int32_t Ui0041ED3E(void) {
    return 0;
}
/* Ui0041ED83 — Game.exe 0041ed83, cdecl.  Returns 0. */
int32_t Ui0041ED83(void) {
    return 0;
}
/* Ui0041ED8A — Game.exe 0041ed8a, cdecl.  Returns 0. */
int32_t Ui0041ED8A(void) {
    return 0;
}
/* Ui0041ED91 — Game.exe 0041ed91, cdecl.  Returns 0. */
int32_t Ui0041ED91(void) {
    return 0;
}
/* Ui0041F47C — Game.exe 0041f47c, stdcall (ret 16).  Returns 0. */
int32_t Ui0041F47C(void) {
    return 0;
}
/* Ui0041F74A — Game.exe 0041f74a, stdcall (ret 4).  Returns 0. */
int32_t Ui0041F74A(void) {
    return 0;
}
/* Ui0041F7E7 — Game.exe 0041f7e7, stdcall (ret 8).  Returns 0. */
int32_t Ui0041F7E7(void) {
    return 0;
}
/* Ui0041F7F7 — Game.exe 0041f7f7, stdcall (ret 8).  Returns 0. */
int32_t Ui0041F7F7(void) {
    return 0;
}
/* Ui0041F800 — Game.exe 0041f800, stdcall (ret 8).  Returns 0. */
int32_t Ui0041F800(void) {
    return 0;
}
/* Ui0041FA2D — Game.exe 0041fa2d, stdcall (ret 16).  Returns 0. */
int32_t Ui0041FA2D(void) {
    return 0;
}
/* Ui0041FA40 — Game.exe 0041fa40, stdcall (ret 4).  Returns 0. */
int32_t Ui0041FA40(void) {
    return 0;
}
/* Ui0041FA6B — Game.exe 0041fa6b, stdcall (ret 60).  Returns 0. */
int32_t Ui0041FA6B(void) {
    return 0;
}
/* Ui0041FA74 — Game.exe 0041fa74, stdcall (ret 48).  Returns 0. */
int32_t Ui0041FA74(void) {
    return 0;
}
/* Ui0041FA84 — Game.exe 0041fa84, cdecl.  Returns 0. */
int32_t Ui0041FA84(void) {
    return 0;
}
/* Ui0041FA99 — Game.exe 0041fa99, stdcall (ret 4).  Returns 0. */
int32_t Ui0041FA99(void) {
    return 0;
}
/* Ui0041FAA2 — Game.exe 0041faa2, stdcall (ret 4).  Returns 0. */
int32_t Ui0041FAA2(void) {
    return 0;
}
/* Ui0041FAAB — Game.exe 0041faab, stdcall (ret 4).  Returns 0. */
int32_t Ui0041FAAB(void) {
    return 0;
}
/* Ui004264A7 — Game.exe 004264a7, cdecl.  01251a70 = 0, calls 00424647(), calls 00528455().  Part of the shutdown sequence (P30_FatalError). */
void Ui004264A7(void) {
    UiVar01251A70 = 0;
    UiCall00424647();
    UiCall00528455();
}
/* Ui004268E0 — Game.exe 004268e0, cdecl.  011f43b0 = 0 (empties the sphere table read by P63_SphereHits). */
void Ui004268E0(void) {
    UiVar011F43B0 = 0;
}
