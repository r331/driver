/* ported5.c — table-like batch of small menu helpers from Game.exe (names carry the address):
   key-binding picks, highlight colours, icon selection, float sliders, player-car selection, option
   toggles and one-line forwarders.  The behaviour of each is its one or two lines of code. */
#include "ported139.h"
#include "ported5.h"
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("Q00546028")
#undef Q00546028
#pragma push_macro("Q00546028") /*gvi*/
#undef Q00546028 /*gvi*/
float Q00546028;
#pragma pop_macro("Q00546028") /*gvi*/
#pragma pop_macro("Q00546028")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("Q0054602C")
#undef Q0054602C
#pragma push_macro("Q0054602C") /*gvi*/
#undef Q0054602C /*gvi*/
float Q0054602C;
#pragma pop_macro("Q0054602C") /*gvi*/
#pragma pop_macro("Q0054602C")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("Q00546030")
#undef Q00546030
#pragma push_macro("Q00546030") /*gvi*/
#undef Q00546030 /*gvi*/
float Q00546030;
#pragma pop_macro("Q00546030") /*gvi*/
#pragma pop_macro("Q00546030")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("Q0054604C")
#undef Q0054604C
#pragma push_macro("Q0054604C") /*gvi*/
#undef Q0054604C /*gvi*/
float Q0054604C;
#pragma pop_macro("Q0054604C") /*gvi*/
#pragma pop_macro("Q0054604C")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("Q00549A34")
#undef Q00549A34
#pragma push_macro("Q00549A34") /*gvi*/
#undef Q00549A34 /*gvi*/
uint32_t Q00549A34;
#pragma pop_macro("Q00549A34") /*gvi*/
#pragma pop_macro("Q00549A34")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("Q00549A60")
#undef Q00549A60
#pragma push_macro("Q00549A60") /*gvi*/
#undef Q00549A60 /*gvi*/
int32_t Q00549A60;
#pragma pop_macro("Q00549A60") /*gvi*/
#pragma pop_macro("Q00549A60")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("Q0054C03C")
#undef Q0054C03C
#pragma push_macro("Q0054C03C") /*gvi*/
#undef Q0054C03C /*gvi*/
p5_bytes_t Q0054C03C;
#pragma pop_macro("Q0054C03C") /*gvi*/
#pragma pop_macro("Q0054C03C")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("Q0054C03D")
#undef Q0054C03D
#pragma push_macro("Q0054C03D") /*gvi*/
#undef Q0054C03D /*gvi*/
p5_bytes_t Q0054C03D;
#pragma pop_macro("Q0054C03D") /*gvi*/
#pragma pop_macro("Q0054C03D")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("Q0054C03E")
#undef Q0054C03E
#pragma push_macro("Q0054C03E") /*gvi*/
#undef Q0054C03E /*gvi*/
p5_bytes_t Q0054C03E;
#pragma pop_macro("Q0054C03E") /*gvi*/
#pragma pop_macro("Q0054C03E")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("Q0054C35C")
#undef Q0054C35C
#pragma push_macro("Q0054C35C") /*gvi*/
#undef Q0054C35C /*gvi*/
p5_bytes_t Q0054C35C;
#pragma pop_macro("Q0054C35C") /*gvi*/
#pragma pop_macro("Q0054C35C")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("Q0054C35D")
#undef Q0054C35D
#pragma push_macro("Q0054C35D") /*gvi*/
#undef Q0054C35D /*gvi*/
p5_bytes_t Q0054C35D;
#pragma pop_macro("Q0054C35D") /*gvi*/
#pragma pop_macro("Q0054C35D")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("Q0054C35E")
#undef Q0054C35E
#pragma push_macro("Q0054C35E") /*gvi*/
#undef Q0054C35E /*gvi*/
p5_bytes_t Q0054C35E;
#pragma pop_macro("Q0054C35E") /*gvi*/
#pragma pop_macro("Q0054C35E")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("Q0054C6D8")
#undef Q0054C6D8
#pragma push_macro("Q0054C6D8") /*gvi*/
#undef Q0054C6D8 /*gvi*/
int32_t Q0054C6D8;
#pragma pop_macro("Q0054C6D8") /*gvi*/
#pragma pop_macro("Q0054C6D8")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("Q0054C948")
#undef Q0054C948
#pragma push_macro("Q0054C948") /*gvi*/
#undef Q0054C948 /*gvi*/
int32_t Q0054C948;
#pragma pop_macro("Q0054C948") /*gvi*/
#pragma pop_macro("Q0054C948")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("Q0054CC58")
#undef Q0054CC58
#pragma push_macro("Q0054CC58") /*gvi*/
#undef Q0054CC58 /*gvi*/
int32_t Q0054CC58;
#pragma pop_macro("Q0054CC58") /*gvi*/
#pragma pop_macro("Q0054CC58")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("Q0054DF98")
#undef Q0054DF98
#pragma push_macro("Q0054DF98") /*gvi*/
#undef Q0054DF98 /*gvi*/
uint16_t Q0054DF98;
#pragma pop_macro("Q0054DF98") /*gvi*/
#pragma pop_macro("Q0054DF98")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("Q0054DF9A")
#undef Q0054DF9A
#pragma push_macro("Q0054DF9A") /*gvi*/
#undef Q0054DF9A /*gvi*/
uint16_t Q0054DF9A;
#pragma pop_macro("Q0054DF9A") /*gvi*/
#pragma pop_macro("Q0054DF9A")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("Q0054DF9C")
#undef Q0054DF9C
#pragma push_macro("Q0054DF9C") /*gvi*/
#undef Q0054DF9C /*gvi*/
uint32_t Q0054DF9C;
#pragma pop_macro("Q0054DF9C") /*gvi*/
#pragma pop_macro("Q0054DF9C")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("Q0054E308")
#undef Q0054E308
#pragma push_macro("Q0054E308") /*gvi*/
#undef Q0054E308 /*gvi*/
int32_t Q0054E308;
#pragma pop_macro("Q0054E308") /*gvi*/
#pragma pop_macro("Q0054E308")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("Q0057B56C")
#undef Q0057B56C
#pragma push_macro("Q0057B56C") /*gvi*/
#undef Q0057B56C /*gvi*/
int32_t Q0057B56C;
#pragma pop_macro("Q0057B56C") /*gvi*/
#pragma pop_macro("Q0057B56C")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("Q0057B72C")
#undef Q0057B72C
#pragma push_macro("Q0057B72C") /*gvi*/
#undef Q0057B72C /*gvi*/
int32_t Q0057B72C;
#pragma pop_macro("Q0057B72C") /*gvi*/
#pragma pop_macro("Q0057B72C")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("Q005FE764")
#undef Q005FE764
#pragma push_macro("Q005FE764") /*gvi*/
#undef Q005FE764 /*gvi*/
uint32_t Q005FE764;
#pragma pop_macro("Q005FE764") /*gvi*/
#pragma pop_macro("Q005FE764")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("Q005FE768")
#undef Q005FE768
#pragma push_macro("Q005FE768") /*gvi*/
#undef Q005FE768 /*gvi*/
int32_t Q005FE768;
#pragma pop_macro("Q005FE768") /*gvi*/
#pragma pop_macro("Q005FE768")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("Q005FEA0C")
#undef Q005FEA0C
#pragma push_macro("Q005FEA0C") /*gvi*/
#undef Q005FEA0C /*gvi*/
int32_t Q005FEA0C;
#pragma pop_macro("Q005FEA0C") /*gvi*/
#pragma pop_macro("Q005FEA0C")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("Q005FEA10")
#undef Q005FEA10
#pragma push_macro("Q005FEA10") /*gvi*/
#undef Q005FEA10 /*gvi*/
int32_t Q005FEA10;
#pragma pop_macro("Q005FEA10") /*gvi*/
#pragma pop_macro("Q005FEA10")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("Q005FEA20")
#undef Q005FEA20
#pragma push_macro("Q005FEA20") /*gvi*/
#undef Q005FEA20 /*gvi*/
int32_t Q005FEA20;
#pragma pop_macro("Q005FEA20") /*gvi*/
#pragma pop_macro("Q005FEA20")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("Q005FEA24")
#undef Q005FEA24
#pragma push_macro("Q005FEA24") /*gvi*/
#undef Q005FEA24 /*gvi*/
int32_t Q005FEA24;
#pragma pop_macro("Q005FEA24") /*gvi*/
#pragma pop_macro("Q005FEA24")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("Q00B31E2C")
#undef Q00B31E2C
#pragma push_macro("Q00B31E2C") /*gvi*/
#undef Q00B31E2C /*gvi*/
int32_t Q00B31E2C;
#pragma pop_macro("Q00B31E2C") /*gvi*/
#pragma pop_macro("Q00B31E2C")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("Q00B87E90")
#undef Q00B87E90
#pragma push_macro("Q00B87E90") /*gvi*/
#undef Q00B87E90 /*gvi*/
int32_t Q00B87E90;
#pragma pop_macro("Q00B87E90") /*gvi*/
#pragma pop_macro("Q00B87E90")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("Q00B87E94")
#undef Q00B87E94
#pragma push_macro("Q00B87E94") /*gvi*/
#undef Q00B87E94 /*gvi*/
int32_t Q00B87E94;
#pragma pop_macro("Q00B87E94") /*gvi*/
#pragma pop_macro("Q00B87E94")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("Q00B87EF0")
#undef Q00B87EF0
#pragma push_macro("Q00B87EF0") /*gvi*/
#undef Q00B87EF0 /*gvi*/
int32_t Q00B87EF0;
#pragma pop_macro("Q00B87EF0") /*gvi*/
#pragma pop_macro("Q00B87EF0")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("Q00B87F00")
#undef Q00B87F00
#pragma push_macro("Q00B87F00") /*gvi*/
#undef Q00B87F00 /*gvi*/
int32_t Q00B87F00;
#pragma pop_macro("Q00B87F00") /*gvi*/
#pragma pop_macro("Q00B87F00")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("Q00B91D3C")
#undef Q00B91D3C
#pragma push_macro("Q00B91D3C") /*gvi*/
#undef Q00B91D3C /*gvi*/
int32_t Q00B91D3C;
#pragma pop_macro("Q00B91D3C") /*gvi*/
#pragma pop_macro("Q00B91D3C")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("Q00C55858")
#undef Q00C55858
#pragma push_macro("Q00C55858") /*gvi*/
#undef Q00C55858 /*gvi*/
int32_t Q00C55858;
#pragma pop_macro("Q00C55858") /*gvi*/
#pragma pop_macro("Q00C55858")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("Q00C5585C")
#undef Q00C5585C
#pragma push_macro("Q00C5585C") /*gvi*/
#undef Q00C5585C /*gvi*/
int32_t Q00C5585C;
#pragma pop_macro("Q00C5585C") /*gvi*/
#pragma pop_macro("Q00C5585C")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("Q00C55860")
#undef Q00C55860
#pragma push_macro("Q00C55860") /*gvi*/
#undef Q00C55860 /*gvi*/
int32_t Q00C55860;
#pragma pop_macro("Q00C55860") /*gvi*/
#pragma pop_macro("Q00C55860")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("Q00C55864")
#undef Q00C55864
#pragma push_macro("Q00C55864") /*gvi*/
#undef Q00C55864 /*gvi*/
int32_t Q00C55864;
#pragma pop_macro("Q00C55864") /*gvi*/
#pragma pop_macro("Q00C55864")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("Q00C55868")
#undef Q00C55868
#pragma push_macro("Q00C55868") /*gvi*/
#undef Q00C55868 /*gvi*/
int32_t Q00C55868;
#pragma pop_macro("Q00C55868") /*gvi*/
#pragma pop_macro("Q00C55868")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("Q00C5586C")
#undef Q00C5586C
#pragma push_macro("Q00C5586C") /*gvi*/
#undef Q00C5586C /*gvi*/
int32_t Q00C5586C;
#pragma pop_macro("Q00C5586C") /*gvi*/
#pragma pop_macro("Q00C5586C")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("Q00C55870")
#undef Q00C55870
#pragma push_macro("Q00C55870") /*gvi*/
#undef Q00C55870 /*gvi*/
int32_t Q00C55870;
#pragma pop_macro("Q00C55870") /*gvi*/
#pragma pop_macro("Q00C55870")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("Q00C55874")
#undef Q00C55874
#pragma push_macro("Q00C55874") /*gvi*/
#undef Q00C55874 /*gvi*/
int32_t Q00C55874;
#pragma pop_macro("Q00C55874") /*gvi*/
#pragma pop_macro("Q00C55874")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("Q00C559F8")
#undef Q00C559F8
#pragma push_macro("Q00C559F8") /*gvi*/
#undef Q00C559F8 /*gvi*/
int32_t Q00C559F8;
#pragma pop_macro("Q00C559F8") /*gvi*/
#pragma pop_macro("Q00C559F8")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("Q00C559FC")
#undef Q00C559FC
#pragma push_macro("Q00C559FC") /*gvi*/
#undef Q00C559FC /*gvi*/
int32_t Q00C559FC;
#pragma pop_macro("Q00C559FC") /*gvi*/
#pragma pop_macro("Q00C559FC")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("Q00C55A74")
#undef Q00C55A74
#pragma push_macro("Q00C55A74") /*gvi*/
#undef Q00C55A74 /*gvi*/
int32_t Q00C55A74;
#pragma pop_macro("Q00C55A74") /*gvi*/
#pragma pop_macro("Q00C55A74")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("Q00C812F0")
#undef Q00C812F0
#pragma push_macro("Q00C812F0") /*gvi*/
#undef Q00C812F0 /*gvi*/
int32_t Q00C812F0;
#pragma pop_macro("Q00C812F0") /*gvi*/
#pragma pop_macro("Q00C812F0")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("Q0125F3F8")
#undef Q0125F3F8
#pragma push_macro("Q0125F3F8") /*gvi*/
#undef Q0125F3F8 /*gvi*/
float Q0125F3F8;
#pragma pop_macro("Q0125F3F8") /*gvi*/
#pragma pop_macro("Q0125F3F8")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("Q01270C24")
#undef Q01270C24
#pragma push_macro("Q01270C24") /*gvi*/
#undef Q01270C24 /*gvi*/
float Q01270C24;
#pragma pop_macro("Q01270C24") /*gvi*/
#pragma pop_macro("Q01270C24")
#endif
/* MenuPickXXXXXXXX (12) — controls menu: start redefining one key binding.  Sets the "waiting for a key"
   mode (Q00B87F00 = 1), the target byte inside the key table P19_Keys1 (00d04a70 + n, n = 0..11) and the
   menu row Q005FE768 to highlight, reads input once, repaints the rows white and remembers the row in
   MenuI005FE770 (MenuI005FE774 = -1: no second row).  Return 0. */
int32_t MenuPick0040FEA0(void) {
    Q00B87F00 = 1; Q005FE764 = 0x00d04a70; Q005FE768 = 2;
    Call004E3391(); MenuHiliteWhite0041074D();
    MenuI005FE770 = Q005FE768; MenuI005FE774 = -1; return 0;
}
int32_t MenuPick0040FF5A(void) {
    Q00B87F00 = 1; Q005FE764 = 0x00d04a71; Q005FE768 = 4;
    Call004E3391(); MenuHiliteWhite0041074D();
    MenuI005FE770 = Q005FE768; MenuI005FE774 = -1; return 0;
}
int32_t MenuPick00410014(void) {
    Q00B87F00 = 1; Q005FE764 = 0x00d04a72; Q005FE768 = 16;
    Call004E3391(); MenuHiliteWhite0041074D();
    MenuI005FE770 = Q005FE768; MenuI005FE774 = -1; return 0;
}
int32_t MenuPick004100CE(void) {
    Q00B87F00 = 1; Q005FE764 = 0x00d04a74; Q005FE768 = 6;
    Call004E3391(); MenuHiliteWhite0041074D();
    MenuI005FE770 = Q005FE768; MenuI005FE774 = -1; return 0;
}
int32_t MenuPick00410188(void) {
    Q00B87F00 = 1; Q005FE764 = 0x00d04a73; Q005FE768 = 8;
    Call004E3391(); MenuHiliteWhite0041074D();
    MenuI005FE770 = Q005FE768; MenuI005FE774 = -1; return 0;
}
int32_t MenuPick00410242(void) {
    Q00B87F00 = 1; Q005FE764 = 0x00d04a76; Q005FE768 = 20;
    Call004E3391(); MenuHiliteWhite0041074D();
    MenuI005FE770 = Q005FE768; MenuI005FE774 = -1; return 0;
}
int32_t MenuPick004102FC(void) {
    Q00B87F00 = 1; Q005FE764 = 0x00d04a77; Q005FE768 = 22;
    Call004E3391(); MenuHiliteWhite0041074D();
    MenuI005FE770 = Q005FE768; MenuI005FE774 = -1; return 0;
}
int32_t MenuPick004103B6(void) {
    Q00B87F00 = 1; Q005FE764 = 0x00d04a75; Q005FE768 = 24;
    Call004E3391(); MenuHiliteWhite0041074D();
    MenuI005FE770 = Q005FE768; MenuI005FE774 = -1; return 0;
}
int32_t MenuPick00410470(void) {
    Q00B87F00 = 1; Q005FE764 = 0x00d04a7b; Q005FE768 = 18;
    Call004E3391(); MenuHiliteWhite0041074D();
    MenuI005FE770 = Q005FE768; MenuI005FE774 = -1; return 0;
}
int32_t MenuPick0041052A(void) {
    Q00B87F00 = 1; Q005FE764 = 0x00d04a78; Q005FE768 = 12;
    Call004E3391(); MenuHiliteWhite0041074D();
    MenuI005FE770 = Q005FE768; MenuI005FE774 = -1; return 0;
}
int32_t MenuPick004105E4(void) {
    Q00B87F00 = 1; Q005FE764 = 0x00d04a79; Q005FE768 = 14;
    Call004E3391(); MenuHiliteWhite0041074D();
    MenuI005FE770 = Q005FE768; MenuI005FE774 = -1; return 0;
}
int32_t MenuPick0041069E(void) {
    Q00B87F00 = 1; Q005FE764 = 0x00d04a7a; Q005FE768 = 16;
    Call004E3391(); MenuHiliteWhite0041074D();
    MenuI005FE770 = Q005FE768; MenuI005FE774 = -1; return 0;
}
/* MenuHiliteWhite / MenuHiliteRed — set the colour bytes (+0xc..+0xe of 16-byte text entries) of the
   remembered row(s) to white (ff ff ff) or red (ff 00 00): 0041074D / 004106E1 for the table at
   0054c03c, 00411A9D / 00411A31 for the table at 0054c35c. */
void MenuHiliteWhite0041074D(void) {
    Q0054C03C[MenuI005FE770 * 0x10] = 0xff; Q0054C03D[MenuI005FE770 * 0x10] = 255; Q0054C03E[MenuI005FE770 * 0x10] = 255;
    if (MenuI005FE774 != -1) { Q0054C03C[MenuI005FE774 * 0x10] = 0xff; Q0054C03D[MenuI005FE774 * 0x10] = 255; Q0054C03E[MenuI005FE774 * 0x10] = 255; }
}
void MenuHiliteRed004106E1(void) {
    Q0054C03C[MenuI005FE770 * 0x10] = 0xff; Q0054C03D[MenuI005FE770 * 0x10] = 0; Q0054C03E[MenuI005FE770 * 0x10] = 0;
    if (MenuI005FE774 != -1) { Q0054C03C[MenuI005FE774 * 0x10] = 0xff; Q0054C03D[MenuI005FE774 * 0x10] = 0; Q0054C03E[MenuI005FE774 * 0x10] = 0; }
}
void MenuHiliteRed00411A31(void) {
    Q0054C35C[MenuI005FE798 * 0x10] = 0xff; Q0054C35D[MenuI005FE798 * 0x10] = 0; Q0054C35E[MenuI005FE798 * 0x10] = 0;
    if (MenuI005FE79C != -1) { Q0054C35C[MenuI005FE79C * 0x10] = 0xff; Q0054C35D[MenuI005FE79C * 0x10] = 0; Q0054C35E[MenuI005FE79C * 0x10] = 0; }
}
void MenuHiliteWhite00411A9D(void) {
    Q0054C35C[MenuI005FE798 * 0x10] = 0xff; Q0054C35D[MenuI005FE798 * 0x10] = 255; Q0054C35E[MenuI005FE798 * 0x10] = 255;
    if (MenuI005FE79C != -1) { Q0054C35C[MenuI005FE79C * 0x10] = 0xff; Q0054C35D[MenuI005FE79C * 0x10] = 255; Q0054C35E[MenuI005FE79C * 0x10] = 255; }
}
/* SetIconIdxXXXXXXXX (8) — store one picture address (0054cdf0 + 0x18 * k) into its menu slot and the
   matching loaded icon into Q0054CC58; reset == 0 also restarts the menu counter.  Quirk kept:
   00412D0F writes the same slot as 00412CA1 (WU0054CC28). */
void SetIconIdx00412A0D(int32_t reset) {
    WU0054CBB0 = 0x54cdf0; Q0054CC58 = Q00C5585C; if (reset == 0) MenuCounter5D577C = 0;
}
void SetIconIdx00412A7B(int32_t reset) {
    WU0054CBC4 = 0x54ce08; Q0054CC58 = Q00C55858; if (reset == 0) MenuCounter5D577C = 0;
}
void SetIconIdx00412AE9(int32_t reset) {
    WU0054CBD8 = 0x54ce20; Q0054CC58 = Q00C55874; if (reset == 0) MenuCounter5D577C = 0;
}
void SetIconIdx00412B57(int32_t reset) {
    WU0054CBEC = 0x54ce38; Q0054CC58 = Q00C55870; if (reset == 0) MenuCounter5D577C = 0;
}
void SetIconIdx00412BC5(int32_t reset) {
    WU0054CC00 = 0x54ce50; Q0054CC58 = Q00C55868; if (reset == 0) MenuCounter5D577C = 0;
}
void SetIconIdx00412C33(int32_t reset) {
    WU0054CC14 = 0x54ce68; Q0054CC58 = Q00C5586C; if (reset == 0) MenuCounter5D577C = 0;
}
void SetIconIdx00412CA1(int32_t reset) {
    WU0054CC28 = 0x54ce80; Q0054CC58 = Q00C55864; if (reset == 0) MenuCounter5D577C = 0;
}
void SetIconIdx00412D0F(int32_t reset) {
    WU0054CC28 = 0x54ce98; Q0054CC58 = Q00C55860; if (reset == 0) MenuCounter5D577C = 0;
}
/* FloatStep (4) — option sliders: raise / lower Q01270C24 (00409A91 / 00409ACA) or Q0125F3F8 (00409B03 /
   00409B3C) by the step Q0054604C within the .rdata limits, then request a menu redraw.
   TODO(RE): unsure which options the two floats are (brightness / screen scale?). */
void FloatStep00409A91(void) {
    if (Q01270C24 < Q00546030) { Q01270C24 = Q01270C24 + Q0054604C; MenuVar575EF8 = 4; MenuRedraw(); }
}
void FloatStep00409ACA(void) {
    if (Q0054602C < Q01270C24) { Q01270C24 = Q01270C24 - Q0054604C; MenuVar575EF8 = 4; MenuRedraw(); }
}
void FloatStep00409B03(void) {
    if (Q0125F3F8 < Q00546028) { Q0125F3F8 = Q0125F3F8 + Q0054604C; MenuVar575EF8 = 4; MenuRedraw(); }
}
void FloatStep00409B3C(void) {
    if (Q0054602C < Q0125F3F8) { Q0125F3F8 = Q0125F3F8 - Q0054604C; MenuVar575EF8 = 4; MenuRedraw(); }
}
/* PrevPcar / NextPcar — cycle the player-car choice Q0057B56C over 0..0x11 skipping 0xf, then
   SetPcarName0040479B formats its label (sprintf of 00549ac0 with number + 1 into 0057b560). */
void PrevPcar00404721(void) {
    Q0057B56C = Q0057B56C - 1;
    if (Q0057B56C < 0) Q0057B56C = 0x11;
    if (Q0057B56C == 0xf) Q0057B56C = 0xe;
    SetPcarName0040479B();
}
void NextPcar0040475E(void) {
    Q0057B56C = Q0057B56C + 1;
    if (0x11 < Q0057B56C) Q0057B56C = 0;
    if (Q0057B56C == 0xf) Q0057B56C = 0x10;
    SetPcarName0040479B();
}
void SetPcarName0040479B(void) {
    Q00549A60 = Q00C55A74;
    Call0052A910(0x57b560, 0x549ac0, Q0057B56C + 1);
    Q00549A34 = 0x57b560;
}
/* SetupMenuTable00412087 / 00412487 — fill the header words of two menu tables (icon + two state word
   addresses) and run their setup calls (used by P57_Menu411FD0 / P57_Menu4123D0). */
void SetupMenuTable00412087(void) {
    Q0054C6D8 = Q00C559F8; G0054C6E8 = 0x5fe858; G0054C6F8 = 0x5fe85c;
    Call0041219E();
}
void SetupMenuTable00412487(void) {
    Q0054C948 = Q00C559FC; G0054C958 = 0x5fe934; G0054C968 = 0x5fe938;
    Call004125B9();
}
/* ToggleOpt004154CD — toggles Q00B87E94 (passed to P48_SndPause; also gates the Doppler velocity calls in
   P115_SndUpdate) and redraws.  ToggleOpt0041542A — toggles CD music Q00B87E90; switching it off stops
   and closes the CD.  Both return 0. */
int32_t ToggleOpt004154CD(void) {
    Q00B87E94 ^= 1; Call0052369B(Q00B87E94); Call00414D1F(); return 0;
}
int32_t ToggleOpt0041542A(void) {
    Q00B87E90 ^= 1;
    if (Q00B87E90 == 0) { Call00524873(); Call00524763(); }
    Call00414D1F(); return 0;
}
/* SetupMiami00416040 — entry 1 of the progress-gated menu (see P19_Sel2): hint 0054e104, size
   0x147 x 0xb6, enable flag, id 0x2e into 00b87e38. */
void SetupMiami00416040(void) {
    Q0054DF9C = 0x54e104; Q0054DF98 = 0x147; Q0054DF9A = 0xb6;
    MenuB0054DFD4 = 1; UiVar00B87E38 = 0x2e;
}
/* LoadArrowIcons / LoadSliderIcons — load the LEFTARRO / RIGHTARR and SLIDER / SLIDERBA icons
   (the latter then calls 00408770 and returns -1). */
void LoadArrowIcons00417353(void) {
    Q005FEA0C = LoadIconByName("LEFTARRO");
    Q005FEA10 = LoadIconByName("RIGHTARR");
    Q0054E308 = Q00C55A74;
}
int32_t LoadSliderIcons00417620(void) {
    Q005FEA24 = LoadIconByName("SLIDER"); Q005FEA20 = LoadIconByName("SLIDERBA");
    Call00408770(); return -1;
}
/* ToggleVar00407636 — if Q0057B72C: toggles Q00B87EF0 (forced to 0 when Q00B31E2C == 0) and redraws. */
int32_t ToggleVar00407636(void) {
    if (Q0057B72C != 0) {
        if (Q00B31E2C == 0) Q00B87EF0 = 0; else Q00B87EF0 ^= 1;
        Call004072BE();
    }
    return 0;
}
/* StartTimer004086B4 — (re)starts the 1000 ms periodic menu timer (P25_TimerStart, callback 00408710)
   into slot D_0054a144 and clears the menu counter. */
void StartTimer004086B4(void) {
    if (D_0054a144 != -1) StopTimer4086EA();
    MenuCounter5D577C = 0;
    D_0054a144 = Call00528221(1000, 1, 0x408710);
}
/* Remaining one-liners: Call3_0040C455 (three menu calls, a == 0 clears 00b87e38), Chain0048AC0D (FMV
   stop + release = P50_FmvStopRelease), Chain004D5FFC (stop all sound + 0052436a), PlayTrack004D7B60
   (replay the current CD track), Pack565Bytes, Fwd* (forwarders), Copy400 (copy 0x400 bytes from a to
   01271a80), LoadTrail* (load TRAIL.DAT). */
void Call3_0040C455(int32_t a, int32_t b) {
    Call0040C165(); if (a == 0) UiVar00B87E38 = 0;
    Call0040C20B(b); Call0040BF50();
}
void Chain0048AC0D(void) {
    Call0048B65D(); Call0048B568();
}
void Chain004D5FFC(void) {
    Call005237B1(); Call0052436A();
}
void PlayTrack004D7B60(void) {
    Call0052479E(Q00B91D3C);
}
void Pack565Bytes004BF452(uint8_t r, uint8_t g, uint8_t b) {
    Pack565_004D950F(r, g, b);
}
void Fwd004D262C(int32_t a) {
    Call004D28A3(a);
}
void Fwd004EAFCF(int32_t a) {
    Call004EAFE0(a);
}
void Fwd00513CF9(int32_t a) {
    Call00514A47(a);
}
void Copy400_00407C27(int32_t a) {
    Call005283B5(0x1271a80, a, 0x400);
}
void LoadTrail004FBE96(void) {
    Q00C812F0 = Call0052ADB0(0x5701d8, 0x5701d4);
}
void Fwd004FC0C7(void) {
    P139_TrailLoad("TRAIL.DAT");   /* 00570248 */
}
