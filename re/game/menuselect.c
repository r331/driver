/* Front-end menu item callbacks, named by their Game.exe address.  The menu engine calls an item's
   callback with a mode: MenuSelectXXXXXXXX(mode) — modes 0/1 set the display flag byte of one or two
   menu-table rows to 3 (MenuBxxxxxxxx = byte at that address), mode 2 stores the item's pair of
   selection values (e.g. which sub-menu row / next row, -1 = none); MenuLeaveXXXXXXXX(mode) — mode 0
   resets row flag bytes (to 0 or 2).  Some items also set MenuFlag5F7E4C.
   TODO(RE): unsure what flag values 0/2/3 mean exactly (likely normal / disabled / highlighted)
   and which screen each group belongs to.  Comments below spell out each body. */
#include "menuselect.h"
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("MenuB00549F8C")
#undef MenuB00549F8C
#pragma push_macro("MenuB00549F8C") /*gvi*/
#undef MenuB00549F8C /*gvi*/
uint8_t MenuB00549F8C;
#pragma pop_macro("MenuB00549F8C") /*gvi*/
#pragma pop_macro("MenuB00549F8C")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("MenuB00549F9C")
#undef MenuB00549F9C
#pragma push_macro("MenuB00549F9C") /*gvi*/
#undef MenuB00549F9C /*gvi*/
uint8_t MenuB00549F9C;
#pragma pop_macro("MenuB00549F9C") /*gvi*/
#pragma pop_macro("MenuB00549F9C")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("MenuB00549FBC")
#undef MenuB00549FBC
#pragma push_macro("MenuB00549FBC") /*gvi*/
#undef MenuB00549FBC /*gvi*/
uint8_t MenuB00549FBC;
#pragma pop_macro("MenuB00549FBC") /*gvi*/
#pragma pop_macro("MenuB00549FBC")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("MenuB00549FCC")
#undef MenuB00549FCC
#pragma push_macro("MenuB00549FCC") /*gvi*/
#undef MenuB00549FCC /*gvi*/
uint8_t MenuB00549FCC;
#pragma pop_macro("MenuB00549FCC") /*gvi*/
#pragma pop_macro("MenuB00549FCC")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("MenuB00549FDC")
#undef MenuB00549FDC
#pragma push_macro("MenuB00549FDC") /*gvi*/
#undef MenuB00549FDC /*gvi*/
uint8_t MenuB00549FDC;
#pragma pop_macro("MenuB00549FDC") /*gvi*/
#pragma pop_macro("MenuB00549FDC")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("MenuB00549FEC")
#undef MenuB00549FEC
#pragma push_macro("MenuB00549FEC") /*gvi*/
#undef MenuB00549FEC /*gvi*/
uint8_t MenuB00549FEC;
#pragma pop_macro("MenuB00549FEC") /*gvi*/
#pragma pop_macro("MenuB00549FEC")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("MenuI0054A060")
#undef MenuI0054A060
#pragma push_macro("MenuI0054A060") /*gvi*/
#undef MenuI0054A060 /*gvi*/
int32_t MenuI0054A060;
#pragma pop_macro("MenuI0054A060") /*gvi*/
#pragma pop_macro("MenuI0054A060")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("MenuB0054C044")
#undef MenuB0054C044
#pragma push_macro("MenuB0054C044") /*gvi*/
#undef MenuB0054C044 /*gvi*/
uint8_t MenuB0054C044;
#pragma pop_macro("MenuB0054C044") /*gvi*/
#pragma pop_macro("MenuB0054C044")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("MenuB0054C054")
#undef MenuB0054C054
#pragma push_macro("MenuB0054C054") /*gvi*/
#undef MenuB0054C054 /*gvi*/
uint8_t MenuB0054C054;
#pragma pop_macro("MenuB0054C054") /*gvi*/
#pragma pop_macro("MenuB0054C054")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("MenuB0054C064")
#undef MenuB0054C064
#pragma push_macro("MenuB0054C064") /*gvi*/
#undef MenuB0054C064 /*gvi*/
uint8_t MenuB0054C064;
#pragma pop_macro("MenuB0054C064") /*gvi*/
#pragma pop_macro("MenuB0054C064")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("MenuB0054C074")
#undef MenuB0054C074
#pragma push_macro("MenuB0054C074") /*gvi*/
#undef MenuB0054C074 /*gvi*/
uint8_t MenuB0054C074;
#pragma pop_macro("MenuB0054C074") /*gvi*/
#pragma pop_macro("MenuB0054C074")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("MenuB0054C084")
#undef MenuB0054C084
#pragma push_macro("MenuB0054C084") /*gvi*/
#undef MenuB0054C084 /*gvi*/
uint8_t MenuB0054C084;
#pragma pop_macro("MenuB0054C084") /*gvi*/
#pragma pop_macro("MenuB0054C084")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("MenuB0054C094")
#undef MenuB0054C094
#pragma push_macro("MenuB0054C094") /*gvi*/
#undef MenuB0054C094 /*gvi*/
uint8_t MenuB0054C094;
#pragma pop_macro("MenuB0054C094") /*gvi*/
#pragma pop_macro("MenuB0054C094")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("MenuB0054C0A4")
#undef MenuB0054C0A4
#pragma push_macro("MenuB0054C0A4") /*gvi*/
#undef MenuB0054C0A4 /*gvi*/
uint8_t MenuB0054C0A4;
#pragma pop_macro("MenuB0054C0A4") /*gvi*/
#pragma pop_macro("MenuB0054C0A4")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("MenuB0054C0B4")
#undef MenuB0054C0B4
#pragma push_macro("MenuB0054C0B4") /*gvi*/
#undef MenuB0054C0B4 /*gvi*/
uint8_t MenuB0054C0B4;
#pragma pop_macro("MenuB0054C0B4") /*gvi*/
#pragma pop_macro("MenuB0054C0B4")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("MenuB0054C0C4")
#undef MenuB0054C0C4
#pragma push_macro("MenuB0054C0C4") /*gvi*/
#undef MenuB0054C0C4 /*gvi*/
uint8_t MenuB0054C0C4;
#pragma pop_macro("MenuB0054C0C4") /*gvi*/
#pragma pop_macro("MenuB0054C0C4")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("MenuB0054C0D4")
#undef MenuB0054C0D4
#pragma push_macro("MenuB0054C0D4") /*gvi*/
#undef MenuB0054C0D4 /*gvi*/
uint8_t MenuB0054C0D4;
#pragma pop_macro("MenuB0054C0D4") /*gvi*/
#pragma pop_macro("MenuB0054C0D4")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("MenuB0054C0E4")
#undef MenuB0054C0E4
#pragma push_macro("MenuB0054C0E4") /*gvi*/
#undef MenuB0054C0E4 /*gvi*/
uint8_t MenuB0054C0E4;
#pragma pop_macro("MenuB0054C0E4") /*gvi*/
#pragma pop_macro("MenuB0054C0E4")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("MenuB0054C0F4")
#undef MenuB0054C0F4
#pragma push_macro("MenuB0054C0F4") /*gvi*/
#undef MenuB0054C0F4 /*gvi*/
uint8_t MenuB0054C0F4;
#pragma pop_macro("MenuB0054C0F4") /*gvi*/
#pragma pop_macro("MenuB0054C0F4")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("MenuB0054C104")
#undef MenuB0054C104
#pragma push_macro("MenuB0054C104") /*gvi*/
#undef MenuB0054C104 /*gvi*/
uint8_t MenuB0054C104;
#pragma pop_macro("MenuB0054C104") /*gvi*/
#pragma pop_macro("MenuB0054C104")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("MenuB0054C114")
#undef MenuB0054C114
#pragma push_macro("MenuB0054C114") /*gvi*/
#undef MenuB0054C114 /*gvi*/
uint8_t MenuB0054C114;
#pragma pop_macro("MenuB0054C114") /*gvi*/
#pragma pop_macro("MenuB0054C114")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("MenuB0054C124")
#undef MenuB0054C124
#pragma push_macro("MenuB0054C124") /*gvi*/
#undef MenuB0054C124 /*gvi*/
uint8_t MenuB0054C124;
#pragma pop_macro("MenuB0054C124") /*gvi*/
#pragma pop_macro("MenuB0054C124")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("MenuB0054C134")
#undef MenuB0054C134
#pragma push_macro("MenuB0054C134") /*gvi*/
#undef MenuB0054C134 /*gvi*/
uint8_t MenuB0054C134;
#pragma pop_macro("MenuB0054C134") /*gvi*/
#pragma pop_macro("MenuB0054C134")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("MenuB0054C144")
#undef MenuB0054C144
#pragma push_macro("MenuB0054C144") /*gvi*/
#undef MenuB0054C144 /*gvi*/
uint8_t MenuB0054C144;
#pragma pop_macro("MenuB0054C144") /*gvi*/
#pragma pop_macro("MenuB0054C144")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("MenuB0054C154")
#undef MenuB0054C154
#pragma push_macro("MenuB0054C154") /*gvi*/
#undef MenuB0054C154 /*gvi*/
uint8_t MenuB0054C154;
#pragma pop_macro("MenuB0054C154") /*gvi*/
#pragma pop_macro("MenuB0054C154")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("MenuB0054C164")
#undef MenuB0054C164
#pragma push_macro("MenuB0054C164") /*gvi*/
#undef MenuB0054C164 /*gvi*/
uint8_t MenuB0054C164;
#pragma pop_macro("MenuB0054C164") /*gvi*/
#pragma pop_macro("MenuB0054C164")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("MenuB0054C174")
#undef MenuB0054C174
#pragma push_macro("MenuB0054C174") /*gvi*/
#undef MenuB0054C174 /*gvi*/
uint8_t MenuB0054C174;
#pragma pop_macro("MenuB0054C174") /*gvi*/
#pragma pop_macro("MenuB0054C174")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("MenuB0054C184")
#undef MenuB0054C184
#pragma push_macro("MenuB0054C184") /*gvi*/
#undef MenuB0054C184 /*gvi*/
uint8_t MenuB0054C184;
#pragma pop_macro("MenuB0054C184") /*gvi*/
#pragma pop_macro("MenuB0054C184")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("MenuB0054C194")
#undef MenuB0054C194
#pragma push_macro("MenuB0054C194") /*gvi*/
#undef MenuB0054C194 /*gvi*/
uint8_t MenuB0054C194;
#pragma pop_macro("MenuB0054C194") /*gvi*/
#pragma pop_macro("MenuB0054C194")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("MenuB0054C1A4")
#undef MenuB0054C1A4
#pragma push_macro("MenuB0054C1A4") /*gvi*/
#undef MenuB0054C1A4 /*gvi*/
uint8_t MenuB0054C1A4;
#pragma pop_macro("MenuB0054C1A4") /*gvi*/
#pragma pop_macro("MenuB0054C1A4")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("MenuB0054C1B4")
#undef MenuB0054C1B4
#pragma push_macro("MenuB0054C1B4") /*gvi*/
#undef MenuB0054C1B4 /*gvi*/
uint8_t MenuB0054C1B4;
#pragma pop_macro("MenuB0054C1B4") /*gvi*/
#pragma pop_macro("MenuB0054C1B4")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("MenuB0054C364")
#undef MenuB0054C364
#pragma push_macro("MenuB0054C364") /*gvi*/
#undef MenuB0054C364 /*gvi*/
uint8_t MenuB0054C364;
#pragma pop_macro("MenuB0054C364") /*gvi*/
#pragma pop_macro("MenuB0054C364")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("MenuB0054C374")
#undef MenuB0054C374
#pragma push_macro("MenuB0054C374") /*gvi*/
#undef MenuB0054C374 /*gvi*/
uint8_t MenuB0054C374;
#pragma pop_macro("MenuB0054C374") /*gvi*/
#pragma pop_macro("MenuB0054C374")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("MenuB0054C384")
#undef MenuB0054C384
#pragma push_macro("MenuB0054C384") /*gvi*/
#undef MenuB0054C384 /*gvi*/
uint8_t MenuB0054C384;
#pragma pop_macro("MenuB0054C384") /*gvi*/
#pragma pop_macro("MenuB0054C384")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("MenuB0054C394")
#undef MenuB0054C394
#pragma push_macro("MenuB0054C394") /*gvi*/
#undef MenuB0054C394 /*gvi*/
uint8_t MenuB0054C394;
#pragma pop_macro("MenuB0054C394") /*gvi*/
#pragma pop_macro("MenuB0054C394")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("MenuB0054C3A4")
#undef MenuB0054C3A4
#pragma push_macro("MenuB0054C3A4") /*gvi*/
#undef MenuB0054C3A4 /*gvi*/
uint8_t MenuB0054C3A4;
#pragma pop_macro("MenuB0054C3A4") /*gvi*/
#pragma pop_macro("MenuB0054C3A4")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("MenuB0054C3B4")
#undef MenuB0054C3B4
#pragma push_macro("MenuB0054C3B4") /*gvi*/
#undef MenuB0054C3B4 /*gvi*/
uint8_t MenuB0054C3B4;
#pragma pop_macro("MenuB0054C3B4") /*gvi*/
#pragma pop_macro("MenuB0054C3B4")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("MenuB0054C3C4")
#undef MenuB0054C3C4
#pragma push_macro("MenuB0054C3C4") /*gvi*/
#undef MenuB0054C3C4 /*gvi*/
uint8_t MenuB0054C3C4;
#pragma pop_macro("MenuB0054C3C4") /*gvi*/
#pragma pop_macro("MenuB0054C3C4")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("MenuB0054C3D4")
#undef MenuB0054C3D4
#pragma push_macro("MenuB0054C3D4") /*gvi*/
#undef MenuB0054C3D4 /*gvi*/
uint8_t MenuB0054C3D4;
#pragma pop_macro("MenuB0054C3D4") /*gvi*/
#pragma pop_macro("MenuB0054C3D4")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("MenuB0054C3E4")
#undef MenuB0054C3E4
#pragma push_macro("MenuB0054C3E4") /*gvi*/
#undef MenuB0054C3E4 /*gvi*/
uint8_t MenuB0054C3E4;
#pragma pop_macro("MenuB0054C3E4") /*gvi*/
#pragma pop_macro("MenuB0054C3E4")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("MenuB0054C3F4")
#undef MenuB0054C3F4
#pragma push_macro("MenuB0054C3F4") /*gvi*/
#undef MenuB0054C3F4 /*gvi*/
uint8_t MenuB0054C3F4;
#pragma pop_macro("MenuB0054C3F4") /*gvi*/
#pragma pop_macro("MenuB0054C3F4")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("MenuB0054C404")
#undef MenuB0054C404
#pragma push_macro("MenuB0054C404") /*gvi*/
#undef MenuB0054C404 /*gvi*/
uint8_t MenuB0054C404;
#pragma pop_macro("MenuB0054C404") /*gvi*/
#pragma pop_macro("MenuB0054C404")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("MenuB0054C414")
#undef MenuB0054C414
#pragma push_macro("MenuB0054C414") /*gvi*/
#undef MenuB0054C414 /*gvi*/
uint8_t MenuB0054C414;
#pragma pop_macro("MenuB0054C414") /*gvi*/
#pragma pop_macro("MenuB0054C414")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("MenuB0054C424")
#undef MenuB0054C424
#pragma push_macro("MenuB0054C424") /*gvi*/
#undef MenuB0054C424 /*gvi*/
uint8_t MenuB0054C424;
#pragma pop_macro("MenuB0054C424") /*gvi*/
#pragma pop_macro("MenuB0054C424")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("MenuB0054C434")
#undef MenuB0054C434
#pragma push_macro("MenuB0054C434") /*gvi*/
#undef MenuB0054C434 /*gvi*/
uint8_t MenuB0054C434;
#pragma pop_macro("MenuB0054C434") /*gvi*/
#pragma pop_macro("MenuB0054C434")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("MenuB0054C444")
#undef MenuB0054C444
#pragma push_macro("MenuB0054C444") /*gvi*/
#undef MenuB0054C444 /*gvi*/
uint8_t MenuB0054C444;
#pragma pop_macro("MenuB0054C444") /*gvi*/
#pragma pop_macro("MenuB0054C444")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("MenuB0054C454")
#undef MenuB0054C454
#pragma push_macro("MenuB0054C454") /*gvi*/
#undef MenuB0054C454 /*gvi*/
uint8_t MenuB0054C454;
#pragma pop_macro("MenuB0054C454") /*gvi*/
#pragma pop_macro("MenuB0054C454")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("MenuB0054C464")
#undef MenuB0054C464
#pragma push_macro("MenuB0054C464") /*gvi*/
#undef MenuB0054C464 /*gvi*/
uint8_t MenuB0054C464;
#pragma pop_macro("MenuB0054C464") /*gvi*/
#pragma pop_macro("MenuB0054C464")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("MenuB0054C474")
#undef MenuB0054C474
#pragma push_macro("MenuB0054C474") /*gvi*/
#undef MenuB0054C474 /*gvi*/
uint8_t MenuB0054C474;
#pragma pop_macro("MenuB0054C474") /*gvi*/
#pragma pop_macro("MenuB0054C474")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("MenuB0054C484")
#undef MenuB0054C484
#pragma push_macro("MenuB0054C484") /*gvi*/
#undef MenuB0054C484 /*gvi*/
uint8_t MenuB0054C484;
#pragma pop_macro("MenuB0054C484") /*gvi*/
#pragma pop_macro("MenuB0054C484")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("MenuB0054C494")
#undef MenuB0054C494
#pragma push_macro("MenuB0054C494") /*gvi*/
#undef MenuB0054C494 /*gvi*/
uint8_t MenuB0054C494;
#pragma pop_macro("MenuB0054C494") /*gvi*/
#pragma pop_macro("MenuB0054C494")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("MenuB0054C4A4")
#undef MenuB0054C4A4
#pragma push_macro("MenuB0054C4A4") /*gvi*/
#undef MenuB0054C4A4 /*gvi*/
uint8_t MenuB0054C4A4;
#pragma pop_macro("MenuB0054C4A4") /*gvi*/
#pragma pop_macro("MenuB0054C4A4")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("MenuB0054C4B4")
#undef MenuB0054C4B4
#pragma push_macro("MenuB0054C4B4") /*gvi*/
#undef MenuB0054C4B4 /*gvi*/
uint8_t MenuB0054C4B4;
#pragma pop_macro("MenuB0054C4B4") /*gvi*/
#pragma pop_macro("MenuB0054C4B4")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("MenuB0054C4C4")
#undef MenuB0054C4C4
#pragma push_macro("MenuB0054C4C4") /*gvi*/
#undef MenuB0054C4C4 /*gvi*/
uint8_t MenuB0054C4C4;
#pragma pop_macro("MenuB0054C4C4") /*gvi*/
#pragma pop_macro("MenuB0054C4C4")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("MenuB0054C4D4")
#undef MenuB0054C4D4
#pragma push_macro("MenuB0054C4D4") /*gvi*/
#undef MenuB0054C4D4 /*gvi*/
uint8_t MenuB0054C4D4;
#pragma pop_macro("MenuB0054C4D4") /*gvi*/
#pragma pop_macro("MenuB0054C4D4")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("MenuB0054C4E4")
#undef MenuB0054C4E4
#pragma push_macro("MenuB0054C4E4") /*gvi*/
#undef MenuB0054C4E4 /*gvi*/
uint8_t MenuB0054C4E4;
#pragma pop_macro("MenuB0054C4E4") /*gvi*/
#pragma pop_macro("MenuB0054C4E4")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("MenuB0054C4F4")
#undef MenuB0054C4F4
#pragma push_macro("MenuB0054C4F4") /*gvi*/
#undef MenuB0054C4F4 /*gvi*/
uint8_t MenuB0054C4F4;
#pragma pop_macro("MenuB0054C4F4") /*gvi*/
#pragma pop_macro("MenuB0054C4F4")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("MenuB0054C504")
#undef MenuB0054C504
#pragma push_macro("MenuB0054C504") /*gvi*/
#undef MenuB0054C504 /*gvi*/
uint8_t MenuB0054C504;
#pragma pop_macro("MenuB0054C504") /*gvi*/
#pragma pop_macro("MenuB0054C504")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("MenuB0054C514")
#undef MenuB0054C514
#pragma push_macro("MenuB0054C514") /*gvi*/
#undef MenuB0054C514 /*gvi*/
uint8_t MenuB0054C514;
#pragma pop_macro("MenuB0054C514") /*gvi*/
#pragma pop_macro("MenuB0054C514")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("MenuB0054D1B4")
#undef MenuB0054D1B4
#pragma push_macro("MenuB0054D1B4") /*gvi*/
#undef MenuB0054D1B4 /*gvi*/
uint8_t MenuB0054D1B4;
#pragma pop_macro("MenuB0054D1B4") /*gvi*/
#pragma pop_macro("MenuB0054D1B4")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("MenuB0054D1C4")
#undef MenuB0054D1C4
#pragma push_macro("MenuB0054D1C4") /*gvi*/
#undef MenuB0054D1C4 /*gvi*/
uint8_t MenuB0054D1C4;
#pragma pop_macro("MenuB0054D1C4") /*gvi*/
#pragma pop_macro("MenuB0054D1C4")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("MenuB0054D1D4")
#undef MenuB0054D1D4
#pragma push_macro("MenuB0054D1D4") /*gvi*/
#undef MenuB0054D1D4 /*gvi*/
uint8_t MenuB0054D1D4;
#pragma pop_macro("MenuB0054D1D4") /*gvi*/
#pragma pop_macro("MenuB0054D1D4")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("MenuB0054D1E4")
#undef MenuB0054D1E4
#pragma push_macro("MenuB0054D1E4") /*gvi*/
#undef MenuB0054D1E4 /*gvi*/
uint8_t MenuB0054D1E4;
#pragma pop_macro("MenuB0054D1E4") /*gvi*/
#pragma pop_macro("MenuB0054D1E4")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("MenuB0054D2A4")
#undef MenuB0054D2A4
#pragma push_macro("MenuB0054D2A4") /*gvi*/
#undef MenuB0054D2A4 /*gvi*/
uint8_t MenuB0054D2A4;
#pragma pop_macro("MenuB0054D2A4") /*gvi*/
#pragma pop_macro("MenuB0054D2A4")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("MenuB0054D2B4")
#undef MenuB0054D2B4
#pragma push_macro("MenuB0054D2B4") /*gvi*/
#undef MenuB0054D2B4 /*gvi*/
uint8_t MenuB0054D2B4;
#pragma pop_macro("MenuB0054D2B4") /*gvi*/
#pragma pop_macro("MenuB0054D2B4")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("MenuB0054D2C4")
#undef MenuB0054D2C4
#pragma push_macro("MenuB0054D2C4") /*gvi*/
#undef MenuB0054D2C4 /*gvi*/
uint8_t MenuB0054D2C4;
#pragma pop_macro("MenuB0054D2C4") /*gvi*/
#pragma pop_macro("MenuB0054D2C4")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("MenuB0054D2D4")
#undef MenuB0054D2D4
#pragma push_macro("MenuB0054D2D4") /*gvi*/
#undef MenuB0054D2D4 /*gvi*/
uint8_t MenuB0054D2D4;
#pragma pop_macro("MenuB0054D2D4") /*gvi*/
#pragma pop_macro("MenuB0054D2D4")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("MenuB0054D2E4")
#undef MenuB0054D2E4
#pragma push_macro("MenuB0054D2E4") /*gvi*/
#undef MenuB0054D2E4 /*gvi*/
uint8_t MenuB0054D2E4;
#pragma pop_macro("MenuB0054D2E4") /*gvi*/
#pragma pop_macro("MenuB0054D2E4")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("MenuB0054D3BC")
#undef MenuB0054D3BC
#pragma push_macro("MenuB0054D3BC") /*gvi*/
#undef MenuB0054D3BC /*gvi*/
uint8_t MenuB0054D3BC;
#pragma pop_macro("MenuB0054D3BC") /*gvi*/
#pragma pop_macro("MenuB0054D3BC")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("MenuB0054D3CC")
#undef MenuB0054D3CC
#pragma push_macro("MenuB0054D3CC") /*gvi*/
#undef MenuB0054D3CC /*gvi*/
uint8_t MenuB0054D3CC;
#pragma pop_macro("MenuB0054D3CC") /*gvi*/
#pragma pop_macro("MenuB0054D3CC")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("MenuB0054D3DC")
#undef MenuB0054D3DC
#pragma push_macro("MenuB0054D3DC") /*gvi*/
#undef MenuB0054D3DC /*gvi*/
uint8_t MenuB0054D3DC;
#pragma pop_macro("MenuB0054D3DC") /*gvi*/
#pragma pop_macro("MenuB0054D3DC")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("MenuB0054D3EC")
#undef MenuB0054D3EC
#pragma push_macro("MenuB0054D3EC") /*gvi*/
#undef MenuB0054D3EC /*gvi*/
uint8_t MenuB0054D3EC;
#pragma pop_macro("MenuB0054D3EC") /*gvi*/
#pragma pop_macro("MenuB0054D3EC")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("MenuB0054D3FC")
#undef MenuB0054D3FC
#pragma push_macro("MenuB0054D3FC") /*gvi*/
#undef MenuB0054D3FC /*gvi*/
uint8_t MenuB0054D3FC;
#pragma pop_macro("MenuB0054D3FC") /*gvi*/
#pragma pop_macro("MenuB0054D3FC")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("MenuB0054DFD4")
#undef MenuB0054DFD4
#pragma push_macro("MenuB0054DFD4") /*gvi*/
#undef MenuB0054DFD4 /*gvi*/
uint8_t MenuB0054DFD4;
#pragma pop_macro("MenuB0054DFD4") /*gvi*/
#pragma pop_macro("MenuB0054DFD4")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("MenuB0054DFE4")
#undef MenuB0054DFE4
#pragma push_macro("MenuB0054DFE4") /*gvi*/
#undef MenuB0054DFE4 /*gvi*/
uint8_t MenuB0054DFE4;
#pragma pop_macro("MenuB0054DFE4") /*gvi*/
#pragma pop_macro("MenuB0054DFE4")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("MenuB0054DFF4")
#undef MenuB0054DFF4
#pragma push_macro("MenuB0054DFF4") /*gvi*/
#undef MenuB0054DFF4 /*gvi*/
uint8_t MenuB0054DFF4;
#pragma pop_macro("MenuB0054DFF4") /*gvi*/
#pragma pop_macro("MenuB0054DFF4")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("MenuB0054E004")
#undef MenuB0054E004
#pragma push_macro("MenuB0054E004") /*gvi*/
#undef MenuB0054E004 /*gvi*/
uint8_t MenuB0054E004;
#pragma pop_macro("MenuB0054E004") /*gvi*/
#pragma pop_macro("MenuB0054E004")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("MenuB0054E1A4")
#undef MenuB0054E1A4
#pragma push_macro("MenuB0054E1A4") /*gvi*/
#undef MenuB0054E1A4 /*gvi*/
uint8_t MenuB0054E1A4;
#pragma pop_macro("MenuB0054E1A4") /*gvi*/
#pragma pop_macro("MenuB0054E1A4")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("MenuB0054E1B4")
#undef MenuB0054E1B4
#pragma push_macro("MenuB0054E1B4") /*gvi*/
#undef MenuB0054E1B4 /*gvi*/
uint8_t MenuB0054E1B4;
#pragma pop_macro("MenuB0054E1B4") /*gvi*/
#pragma pop_macro("MenuB0054E1B4")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("MenuI0057B730")
#undef MenuI0057B730
#pragma push_macro("MenuI0057B730") /*gvi*/
#undef MenuI0057B730 /*gvi*/
int32_t MenuI0057B730;
#pragma pop_macro("MenuI0057B730") /*gvi*/
#pragma pop_macro("MenuI0057B730")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("MenuI005D578C")
#undef MenuI005D578C
#pragma push_macro("MenuI005D578C") /*gvi*/
#undef MenuI005D578C /*gvi*/
int32_t MenuI005D578C;
#pragma pop_macro("MenuI005D578C") /*gvi*/
#pragma pop_macro("MenuI005D578C")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("MenuI005FE770")
#undef MenuI005FE770
#pragma push_macro("MenuI005FE770") /*gvi*/
#undef MenuI005FE770 /*gvi*/
int32_t MenuI005FE770;
#pragma pop_macro("MenuI005FE770") /*gvi*/
#pragma pop_macro("MenuI005FE770")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("MenuI005FE774")
#undef MenuI005FE774
#pragma push_macro("MenuI005FE774") /*gvi*/
#undef MenuI005FE774 /*gvi*/
int32_t MenuI005FE774;
#pragma pop_macro("MenuI005FE774") /*gvi*/
#pragma pop_macro("MenuI005FE774")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("MenuI005FE798")
#undef MenuI005FE798
#pragma push_macro("MenuI005FE798") /*gvi*/
#undef MenuI005FE798 /*gvi*/
int32_t MenuI005FE798;
#pragma pop_macro("MenuI005FE798") /*gvi*/
#pragma pop_macro("MenuI005FE798")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("MenuI005FE79C")
#undef MenuI005FE79C
#pragma push_macro("MenuI005FE79C") /*gvi*/
#undef MenuI005FE79C /*gvi*/
int32_t MenuI005FE79C;
#pragma pop_macro("MenuI005FE79C") /*gvi*/
#pragma pop_macro("MenuI005FE79C")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("MenuI005FE9D0")
#undef MenuI005FE9D0
#pragma push_macro("MenuI005FE9D0") /*gvi*/
#undef MenuI005FE9D0 /*gvi*/
int32_t MenuI005FE9D0;
#pragma pop_macro("MenuI005FE9D0") /*gvi*/
#pragma pop_macro("MenuI005FE9D0")
#endif
/* MenuSelect00407334 — Game.exe 00407334, cdecl.  Modes 0/1: 00549f8c = 3, 00549f9c = 3; mode 2: 0057b730 = 1, 0054a060 = 2. */
void MenuSelect00407334(int32_t mode) { if (mode >= 0) { if (mode < 2) { MenuB00549F8C = 3; MenuB00549F9C = 3; } else if (mode == 2) { MenuI0057B730 = 1; MenuI0054A060 = 2; } } }
/* MenuSelect00407421 — Game.exe 00407421, cdecl.  Modes 0/1: 00549fbc = 3; mode 2: 0057b730 = 4, 0054a060 = -1. */
void MenuSelect00407421(int32_t mode) { if (mode >= 0) { if (mode < 2) { MenuB00549FBC = 3; } else if (mode == 2) { MenuI0057B730 = 4; MenuI0054A060 = -1; } } }
/* MenuSelect004074FA — Game.exe 004074fa, cdecl.  Modes 0/1: 00549fcc = 3; mode 2: 0057b730 = 5, 0054a060 = -1. */
void MenuSelect004074FA(int32_t mode) { if (mode >= 0) { if (mode < 2) { MenuB00549FCC = 3; } else if (mode == 2) { MenuI0057B730 = 5; MenuI0054A060 = -1; } } }
/* MenuSelect004075BF — Game.exe 004075bf, cdecl.  Modes 0/1: 00549fdc = 3, 00549fec = 3; mode 2: 0057b730 = 6, 0054a060 = 7. */
void MenuSelect004075BF(int32_t mode) { if (mode >= 0) { if (mode < 2) { MenuB00549FDC = 3; MenuB00549FEC = 3; } else if (mode == 2) { MenuI0057B730 = 6; MenuI0054A060 = 7; } } }
/* MenuSelect00408864 — Game.exe 00408864, cdecl.  Modes 0/1: 0054a254 = 3, 0054a264 = 3; mode 2: 005d578c = 0, 0054a694 = 1. */
void MenuSelect00408864(int32_t mode) { if (mode >= 0) { if (mode < 2) { MenuB0054A254 = 3; MenuB0054A264 = 3; } else if (mode == 2) { MenuI005D578C = 0; MenuI0054A694 = 1; } } }
/* MenuSelect0040891D — Game.exe 0040891d, cdecl.  Modes 0/1: 0054a274 = 3, 0054a284 = 3; mode 2: 005d578c = 2, 0054a694 = 3. */
void MenuSelect0040891D(int32_t mode) { if (mode >= 0) { if (mode < 2) { MenuB0054A274 = 3; MenuB0054A284 = 3; } else if (mode == 2) { MenuI005D578C = 2; MenuI0054A694 = 3; } } }
/* MenuSelect004089F2 — Game.exe 004089f2, cdecl.  Modes 0/1: 0054a294 = 3, 0054a2a4 = 3; mode 2: 005d578c = 4, 0054a694 = 5. */
void MenuSelect004089F2(int32_t mode) { if (mode >= 0) { if (mode < 2) { MenuB0054A294 = 3; MenuB0054A2A4 = 3; } else if (mode == 2) { MenuI005D578C = 4; MenuI0054A694 = 5; } } }
/* MenuSelect00408A8C — Game.exe 00408a8c, cdecl.  Modes 0/1: 0054a2b4 = 3, 0054a2c4 = 3; mode 2: 005d578c = 6, 0054a694 = 7. */
void MenuSelect00408A8C(int32_t mode) { if (mode >= 0) { if (mode < 2) { MenuB0054A2B4 = 3; MenuB0054A2C4 = 3; } else if (mode == 2) { MenuI005D578C = 6; MenuI0054A694 = 7; } } }
/* MenuSelect00408B26 — Game.exe 00408b26, cdecl.  Modes 0/1: 0054a314 = 3, 0054a324 = 3; mode 2: 005d578c = 12, 0054a694 = 13. */
void MenuSelect00408B26(int32_t mode) { if (mode >= 0) { if (mode < 2) { MenuB0054A314 = 3; MenuB0054A324 = 3; } else if (mode == 2) { MenuI005D578C = 12; MenuI0054A694 = 13; } } }
/* MenuSelect00408BC0 — Game.exe 00408bc0, cdecl.  Modes 0/1: 0054a374 = 3, 0054a384 = 3; mode 2: 005d578c = 18, 0054a694 = 19. */
void MenuSelect00408BC0(int32_t mode) { if (mode >= 0) { if (mode < 2) { MenuB0054A374 = 3; MenuB0054A384 = 3; } else if (mode == 2) { MenuI005D578C = 18; MenuI0054A694 = 19; } } }
/* MenuSelect00408C95 — Game.exe 00408c95, cdecl.  Modes 0/1: 0054a354 = 3, 0054a364 = 3; mode 2: 005d578c = 16, 0054a694 = 17. */
void MenuSelect00408C95(int32_t mode) { if (mode >= 0) { if (mode < 2) { MenuB0054A354 = 3; MenuB0054A364 = 3; } else if (mode == 2) { MenuI005D578C = 16; MenuI0054A694 = 17; } } }
/* MenuSelect00408D2F — Game.exe 00408d2f, cdecl.  Modes 0/1: 0054a334 = 3, 0054a344 = 3; mode 2: 005d578c = 14, 0054a694 = 15. */
void MenuSelect00408D2F(int32_t mode) { if (mode >= 0) { if (mode < 2) { MenuB0054A334 = 3; MenuB0054A344 = 3; } else if (mode == 2) { MenuI005D578C = 14; MenuI0054A694 = 15; } } }
/* MenuSelect00408DC9 — Game.exe 00408dc9, cdecl.  Modes 0/1: 0054a2d4 = 3, 0054a2e4 = 3; mode 2: 005d578c = 8, 0054a694 = 9. */
void MenuSelect00408DC9(int32_t mode) { if (mode >= 0) { if (mode < 2) { MenuB0054A2D4 = 3; MenuB0054A2E4 = 3; } else if (mode == 2) { MenuI005D578C = 8; MenuI0054A694 = 9; } } }
/* MenuSelect00408E63 — Game.exe 00408e63, cdecl.  Modes 0/1: 0054a2f4 = 3, 0054a304 = 3; mode 2: 005d578c = 10, 0054a694 = 11. */
void MenuSelect00408E63(int32_t mode) { if (mode >= 0) { if (mode < 2) { MenuB0054A2F4 = 3; MenuB0054A304 = 3; } else if (mode == 2) { MenuI005D578C = 10; MenuI0054A694 = 11; } } }
/* MenuSelect00408EFD — Game.exe 00408efd, cdecl.  Modes 0/1: 0054a3f4 = 3, 0054a404 = 3; mode 2: 005d578c = 26, 0054a694 = 27. */
void MenuSelect00408EFD(int32_t mode) { if (mode >= 0) { if (mode < 2) { MenuB0054A3F4 = 3; MenuB0054A404 = 3; } else if (mode == 2) { MenuI005D578C = 26; MenuI0054A694 = 27; } } }
/* MenuSelect00408F97 — Game.exe 00408f97, cdecl.  Modes 0/1: 0054a3d4 = 3, 0054a3e4 = 3; mode 2: 005d578c = 24, 0054a694 = 25. */
void MenuSelect00408F97(int32_t mode) { if (mode >= 0) { if (mode < 2) { MenuB0054A3D4 = 3; MenuB0054A3E4 = 3; } else if (mode == 2) { MenuI005D578C = 24; MenuI0054A694 = 25; } } }
/* MenuSelect00409031 — Game.exe 00409031, cdecl.  Modes 0/1: 0054a3b4 = 3, 0054a3c4 = 3; mode 2: 005d578c = 22, 0054a694 = 23. */
void MenuSelect00409031(int32_t mode) { if (mode >= 0) { if (mode < 2) { MenuB0054A3B4 = 3; MenuB0054A3C4 = 3; } else if (mode == 2) { MenuI005D578C = 22; MenuI0054A694 = 23; } } }
/* MenuSelect004090CB — Game.exe 004090cb, cdecl.  Modes 0/1: 0054a394 = 3, 0054a3a4 = 3; mode 2: 005d578c = 20, 0054a694 = 21. */
void MenuSelect004090CB(int32_t mode) { if (mode >= 0) { if (mode < 2) { MenuB0054A394 = 3; MenuB0054A3A4 = 3; } else if (mode == 2) { MenuI005D578C = 20; MenuI0054A694 = 21; } } }
/* MenuSelect004091A0 — Game.exe 004091a0, cdecl.  Modes 0/1: 0054a424 = 3, 005f7e4c = 1; mode 2: 005d578c = 29, 0054a694 = -1, 005f7e4c = 1. */
void MenuSelect004091A0(int32_t mode) { if (mode >= 0) { if (mode < 2) { MenuB0054A424 = 3; MenuFlag5F7E4C = 1; } else if (mode == 2) { MenuI005D578C = 29; MenuI0054A694 = -1; MenuFlag5F7E4C = 1; } } }
/* MenuSelect00409247 — Game.exe 00409247, cdecl.  Modes 0/1: 0054a414 = 3, 005f7e4c = 1; mode 2: 005d578c = 28, 0054a694 = -1, 005f7e4c = 1. */
void MenuSelect00409247(int32_t mode) { if (mode >= 0) { if (mode < 2) { MenuB0054A414 = 3; MenuFlag5F7E4C = 1; } else if (mode == 2) { MenuI005D578C = 28; MenuI0054A694 = -1; MenuFlag5F7E4C = 1; } } }
/* MenuSelect004092EE — Game.exe 004092ee, cdecl.  Modes 0/1: 0054a434 = 3, 005f7e4c = 1; mode 2: 005d578c = 30, 0054a694 = -1, 005f7e4c = 1. */
void MenuSelect004092EE(int32_t mode) { if (mode >= 0) { if (mode < 2) { MenuB0054A434 = 3; MenuFlag5F7E4C = 1; } else if (mode == 2) { MenuI005D578C = 30; MenuI0054A694 = -1; MenuFlag5F7E4C = 1; } } }
/* MenuSelect00409395 — Game.exe 00409395, cdecl.  Modes 0/1: 0054a444 = 3, 005f7e4c = 1; mode 2: 005d578c = 31, 0054a694 = -1, 005f7e4c = 1. */
void MenuSelect00409395(int32_t mode) { if (mode >= 0) { if (mode < 2) { MenuB0054A444 = 3; MenuFlag5F7E4C = 1; } else if (mode == 2) { MenuI005D578C = 31; MenuI0054A694 = -1; MenuFlag5F7E4C = 1; } } }
/* MenuSelect0040943C — Game.exe 0040943c, cdecl.  Modes 0/1: 0054a454 = 3, 005f7e4c = 1; mode 2: 005d578c = 32, 0054a694 = -1, 005f7e4c = 1. */
void MenuSelect0040943C(int32_t mode) { if (mode >= 0) { if (mode < 2) { MenuB0054A454 = 3; MenuFlag5F7E4C = 1; } else if (mode == 2) { MenuI005D578C = 32; MenuI0054A694 = -1; MenuFlag5F7E4C = 1; } } }
/* MenuLeave0040E8FF — Game.exe 0040e8ff, cdecl.  Mode 0: 0054acd4 = 2, 0054ace4 = 2. */
void MenuLeave0040E8FF(int32_t mode) { if (mode == 0) { MenuByte54ACD4 = 2; MenuByte54ACE4 = 2; } }
/* MenuLeave0040E957 — Game.exe 0040e957, cdecl.  Mode 0: 0054acf4 = 2, 0054ad04 = 2. */
void MenuLeave0040E957(int32_t mode) { if (mode == 0) { MenuByte54ACF4 = 2; MenuByte54AD04 = 2; } }
/* MenuLeave0040E99C — Game.exe 0040e99c, cdecl.  Mode 0: 0054ad14 = 2, 0054ad24 = 2. */
void MenuLeave0040E99C(int32_t mode) { if (mode == 0) { MenuByte54AD14 = 2; MenuByte54AD24 = 2; } }
/* MenuLeave0040EA3E — Game.exe 0040ea3e, cdecl.  Mode 0: 0054ad34 = 2, 0054ad44 = 2. */
void MenuLeave0040EA3E(int32_t mode) { if (mode == 0) { MenuByte54AD34 = 2; MenuByte54AD44 = 2; } }
/* MenuSelect0040FE29 — Game.exe 0040fe29, cdecl.  Modes 0/1: 0054c044 = 3, 0054c054 = 3; mode 2: 005fe770 = 1, 005fe774 = 2. */
void MenuSelect0040FE29(int32_t mode) { if (mode >= 0) { if (mode < 2) { MenuB0054C044 = 3; MenuB0054C054 = 3; } else if (mode == 2) { MenuI005FE770 = 1; MenuI005FE774 = 2; } } }
/* MenuSelect0040FEE3 — Game.exe 0040fee3, cdecl.  Modes 0/1: 0054c064 = 3, 0054c074 = 3; mode 2: 005fe770 = 3, 005fe774 = 4. */
void MenuSelect0040FEE3(int32_t mode) { if (mode >= 0) { if (mode < 2) { MenuB0054C064 = 3; MenuB0054C074 = 3; } else if (mode == 2) { MenuI005FE770 = 3; MenuI005FE774 = 4; } } }
/* MenuSelect0040FF9D — Game.exe 0040ff9d, cdecl.  Modes 0/1: 0054c0c4 = 3, 0054c0d4 = 3; mode 2: 005fe770 = 9, 005fe774 = 10. */
void MenuSelect0040FF9D(int32_t mode) { if (mode >= 0) { if (mode < 2) { MenuB0054C0C4 = 3; MenuB0054C0D4 = 3; } else if (mode == 2) { MenuI005FE770 = 9; MenuI005FE774 = 10; } } }
/* MenuSelect00410057 — Game.exe 00410057, cdecl.  Modes 0/1: 0054c084 = 3, 0054c094 = 3; mode 2: 005fe770 = 5, 005fe774 = 6. */
void MenuSelect00410057(int32_t mode) { if (mode >= 0) { if (mode < 2) { MenuB0054C084 = 3; MenuB0054C094 = 3; } else if (mode == 2) { MenuI005FE770 = 5; MenuI005FE774 = 6; } } }
/* MenuSelect00410111 — Game.exe 00410111, cdecl.  Modes 0/1: 0054c0a4 = 3, 0054c0b4 = 3; mode 2: 005fe770 = 7, 005fe774 = 8. */
void MenuSelect00410111(int32_t mode) { if (mode >= 0) { if (mode < 2) { MenuB0054C0A4 = 3; MenuB0054C0B4 = 3; } else if (mode == 2) { MenuI005FE770 = 7; MenuI005FE774 = 8; } } }
/* MenuSelect004101CB — Game.exe 004101cb, cdecl.  Modes 0/1: 0054c164 = 3, 0054c174 = 3; mode 2: 005fe770 = 19, 005fe774 = 20. */
void MenuSelect004101CB(int32_t mode) { if (mode >= 0) { if (mode < 2) { MenuB0054C164 = 3; MenuB0054C174 = 3; } else if (mode == 2) { MenuI005FE770 = 19; MenuI005FE774 = 20; } } }
/* MenuSelect00410285 — Game.exe 00410285, cdecl.  Modes 0/1: 0054c184 = 3, 0054c194 = 3; mode 2: 005fe770 = 21, 005fe774 = 22. */
void MenuSelect00410285(int32_t mode) { if (mode >= 0) { if (mode < 2) { MenuB0054C184 = 3; MenuB0054C194 = 3; } else if (mode == 2) { MenuI005FE770 = 21; MenuI005FE774 = 22; } } }
/* MenuSelect0041033F — Game.exe 0041033f, cdecl.  Modes 0/1: 0054c1a4 = 3, 0054c1b4 = 3; mode 2: 005fe770 = 23, 005fe774 = 24. */
void MenuSelect0041033F(int32_t mode) { if (mode >= 0) { if (mode < 2) { MenuB0054C1A4 = 3; MenuB0054C1B4 = 3; } else if (mode == 2) { MenuI005FE770 = 23; MenuI005FE774 = 24; } } }
/* MenuSelect004103F9 — Game.exe 004103f9, cdecl.  Modes 0/1: 0054c144 = 3, 0054c154 = 3; mode 2: 005fe770 = 17, 005fe774 = 18. */
void MenuSelect004103F9(int32_t mode) { if (mode >= 0) { if (mode < 2) { MenuB0054C144 = 3; MenuB0054C154 = 3; } else if (mode == 2) { MenuI005FE770 = 17; MenuI005FE774 = 18; } } }
/* MenuSelect004104B3 — Game.exe 004104b3, cdecl.  Modes 0/1: 0054c0e4 = 3, 0054c0f4 = 3; mode 2: 005fe770 = 11, 005fe774 = 12. */
void MenuSelect004104B3(int32_t mode) { if (mode >= 0) { if (mode < 2) { MenuB0054C0E4 = 3; MenuB0054C0F4 = 3; } else if (mode == 2) { MenuI005FE770 = 11; MenuI005FE774 = 12; } } }
/* MenuSelect0041056D — Game.exe 0041056d, cdecl.  Modes 0/1: 0054c104 = 3, 0054c114 = 3; mode 2: 005fe770 = 13, 005fe774 = 14. */
void MenuSelect0041056D(int32_t mode) { if (mode >= 0) { if (mode < 2) { MenuB0054C104 = 3; MenuB0054C114 = 3; } else if (mode == 2) { MenuI005FE770 = 13; MenuI005FE774 = 14; } } }
/* MenuSelect00410627 — Game.exe 00410627, cdecl.  Modes 0/1: 0054c124 = 3, 0054c134 = 3; mode 2: 005fe770 = 15, 005fe774 = 16. */
void MenuSelect00410627(int32_t mode) { if (mode >= 0) { if (mode < 2) { MenuB0054C124 = 3; MenuB0054C134 = 3; } else if (mode == 2) { MenuI005FE770 = 15; MenuI005FE774 = 16; } } }
/* MenuSelect0041104B — Game.exe 0041104b, cdecl.  Modes 0/1: 0054c364 = 3, 0054c374 = 3; mode 2: 005fe798 = 1, 005fe79c = 2. */
void MenuSelect0041104B(int32_t mode) { if (mode >= 0) { if (mode < 2) { MenuB0054C364 = 3; MenuB0054C374 = 3; } else if (mode == 2) { MenuI005FE798 = 1; MenuI005FE79C = 2; } } }
/* MenuSelect00411100 — Game.exe 00411100, cdecl.  Modes 0/1: 0054c384 = 3, 0054c394 = 3; mode 2: 005fe798 = 3, 005fe79c = 4. */
void MenuSelect00411100(int32_t mode) { if (mode >= 0) { if (mode < 2) { MenuB0054C384 = 3; MenuB0054C394 = 3; } else if (mode == 2) { MenuI005FE798 = 3; MenuI005FE79C = 4; } } }
/* MenuSelect004111B5 — Game.exe 004111b5, cdecl.  Modes 0/1: 0054c3a4 = 3, 0054c3b4 = 3; mode 2: 005fe798 = 5, 005fe79c = 6. */
void MenuSelect004111B5(int32_t mode) { if (mode >= 0) { if (mode < 2) { MenuB0054C3A4 = 3; MenuB0054C3B4 = 3; } else if (mode == 2) { MenuI005FE798 = 5; MenuI005FE79C = 6; } } }
/* MenuSelect0041126A — Game.exe 0041126a, cdecl.  Modes 0/1: 0054c3c4 = 3, 0054c3d4 = 3; mode 2: 005fe798 = 7, 005fe79c = 8. */
void MenuSelect0041126A(int32_t mode) { if (mode >= 0) { if (mode < 2) { MenuB0054C3C4 = 3; MenuB0054C3D4 = 3; } else if (mode == 2) { MenuI005FE798 = 7; MenuI005FE79C = 8; } } }
/* MenuSelect0041131F — Game.exe 0041131f, cdecl.  Modes 0/1: 0054c444 = 3, 0054c454 = 3; mode 2: 005fe798 = 15, 005fe79c = 16. */
void MenuSelect0041131F(int32_t mode) { if (mode >= 0) { if (mode < 2) { MenuB0054C444 = 3; MenuB0054C454 = 3; } else if (mode == 2) { MenuI005FE798 = 15; MenuI005FE79C = 16; } } }
/* MenuSelect004113D4 — Game.exe 004113d4, cdecl.  Modes 0/1: 0054c3e4 = 3, 0054c3f4 = 3; mode 2: 005fe798 = 9, 005fe79c = 10. */
void MenuSelect004113D4(int32_t mode) { if (mode >= 0) { if (mode < 2) { MenuB0054C3E4 = 3; MenuB0054C3F4 = 3; } else if (mode == 2) { MenuI005FE798 = 9; MenuI005FE79C = 10; } } }
/* MenuSelect00411489 — Game.exe 00411489, cdecl.  Modes 0/1: 0054c464 = 3, 0054c474 = 3; mode 2: 005fe798 = 17, 005fe79c = 18. */
void MenuSelect00411489(int32_t mode) { if (mode >= 0) { if (mode < 2) { MenuB0054C464 = 3; MenuB0054C474 = 3; } else if (mode == 2) { MenuI005FE798 = 17; MenuI005FE79C = 18; } } }
/* MenuSelect0041153E — Game.exe 0041153e, cdecl.  Modes 0/1: 0054c484 = 3, 0054c494 = 3; mode 2: 005fe798 = 19, 005fe79c = 20. */
void MenuSelect0041153E(int32_t mode) { if (mode >= 0) { if (mode < 2) { MenuB0054C484 = 3; MenuB0054C494 = 3; } else if (mode == 2) { MenuI005FE798 = 19; MenuI005FE79C = 20; } } }
/* MenuSelect004115F3 — Game.exe 004115f3, cdecl.  Modes 0/1: 0054c4c4 = 3, 0054c4d4 = 3; mode 2: 005fe798 = 23, 005fe79c = 24. */
void MenuSelect004115F3(int32_t mode) { if (mode >= 0) { if (mode < 2) { MenuB0054C4C4 = 3; MenuB0054C4D4 = 3; } else if (mode == 2) { MenuI005FE798 = 23; MenuI005FE79C = 24; } } }
/* MenuSelect004116A8 — Game.exe 004116a8, cdecl.  Modes 0/1: 0054c4e4 = 3, 0054c4f4 = 3; mode 2: 005fe798 = 25, 005fe79c = 26. */
void MenuSelect004116A8(int32_t mode) { if (mode >= 0) { if (mode < 2) { MenuB0054C4E4 = 3; MenuB0054C4F4 = 3; } else if (mode == 2) { MenuI005FE798 = 25; MenuI005FE79C = 26; } } }
/* MenuSelect0041175D — Game.exe 0041175d, cdecl.  Modes 0/1: 0054c504 = 3, 0054c514 = 3; mode 2: 005fe798 = 27, 005fe79c = 28. */
void MenuSelect0041175D(int32_t mode) { if (mode >= 0) { if (mode < 2) { MenuB0054C504 = 3; MenuB0054C514 = 3; } else if (mode == 2) { MenuI005FE798 = 27; MenuI005FE79C = 28; } } }
/* MenuSelect00411812 — Game.exe 00411812, cdecl.  Modes 0/1: 0054c404 = 3, 0054c414 = 3; mode 2: 005fe798 = 11, 005fe79c = 12. */
void MenuSelect00411812(int32_t mode) { if (mode >= 0) { if (mode < 2) { MenuB0054C404 = 3; MenuB0054C414 = 3; } else if (mode == 2) { MenuI005FE798 = 11; MenuI005FE79C = 12; } } }
/* MenuSelect004118C7 — Game.exe 004118c7, cdecl.  Modes 0/1: 0054c424 = 3, 0054c434 = 3; mode 2: 005fe798 = 13, 005fe79c = 14. */
void MenuSelect004118C7(int32_t mode) { if (mode >= 0) { if (mode < 2) { MenuB0054C424 = 3; MenuB0054C434 = 3; } else if (mode == 2) { MenuI005FE798 = 13; MenuI005FE79C = 14; } } }
/* MenuSelect0041197C — Game.exe 0041197c, cdecl.  Modes 0/1: 0054c4a4 = 3, 0054c4b4 = 3; mode 2: 005fe798 = 21, 005fe79c = 22. */
void MenuSelect0041197C(int32_t mode) { if (mode >= 0) { if (mode < 2) { MenuB0054C4A4 = 3; MenuB0054C4B4 = 3; } else if (mode == 2) { MenuI005FE798 = 21; MenuI005FE79C = 22; } } }
/* MenuLeave004136DA — Game.exe 004136da, cdecl.  Mode 0: 0054d1b4 = 0. */
void MenuLeave004136DA(int32_t mode) { if (mode == 0) { MenuB0054D1B4 = 0; } }
/* MenuLeave00413728 — Game.exe 00413728, cdecl.  Mode 0: 0054d1c4 = 0. */
void MenuLeave00413728(int32_t mode) { if (mode == 0) { MenuB0054D1C4 = 0; } }
/* MenuLeave00413776 — Game.exe 00413776, cdecl.  Mode 0: 0054d1d4 = 0. */
void MenuLeave00413776(int32_t mode) { if (mode == 0) { MenuB0054D1D4 = 0; } }
/* MenuLeave004137C4 — Game.exe 004137c4, cdecl.  Mode 0: 0054d1e4 = 0. */
void MenuLeave004137C4(int32_t mode) { if (mode == 0) { MenuB0054D1E4 = 0; } }
/* MenuLeave00413961 — Game.exe 00413961, cdecl.  Mode 0: 0054d2a4 = 0. */
void MenuLeave00413961(int32_t mode) { if (mode == 0) { MenuB0054D2A4 = 0; } }
/* MenuLeave004139AF — Game.exe 004139af, cdecl.  Mode 0: 0054d2b4 = 0. */
void MenuLeave004139AF(int32_t mode) { if (mode == 0) { MenuB0054D2B4 = 0; } }
/* MenuLeave004139E6 — Game.exe 004139e6, cdecl.  Mode 0: 0054d2c4 = 0. */
void MenuLeave004139E6(int32_t mode) { if (mode == 0) { MenuB0054D2C4 = 0; } }
/* MenuLeave00413A1D — Game.exe 00413a1d, cdecl.  Mode 0: 0054d2d4 = 0. */
void MenuLeave00413A1D(int32_t mode) { if (mode == 0) { MenuB0054D2D4 = 0; } }
/* MenuLeave00413A54 — Game.exe 00413a54, cdecl.  Mode 0: 0054d2e4 = 0. */
void MenuLeave00413A54(int32_t mode) { if (mode == 0) { MenuB0054D2E4 = 0; } }
/* MenuLeave00413BE5 — Game.exe 00413be5, cdecl.  Mode 0: 0054d3bc = 0. */
void MenuLeave00413BE5(int32_t mode) { if (mode == 0) { MenuB0054D3BC = 0; } }
/* MenuLeave00413C17 — Game.exe 00413c17, cdecl.  Mode 0: 0054d3cc = 0. */
void MenuLeave00413C17(int32_t mode) { if (mode == 0) { MenuB0054D3CC = 0; } }
/* MenuLeave00413C49 — Game.exe 00413c49, cdecl.  Mode 0: 0054d3dc = 0. */
void MenuLeave00413C49(int32_t mode) { if (mode == 0) { MenuB0054D3DC = 0; } }
/* MenuLeave00413C7B — Game.exe 00413c7b, cdecl.  Mode 0: 0054d3ec = 0. */
void MenuLeave00413C7B(int32_t mode) { if (mode == 0) { MenuB0054D3EC = 0; } }
/* MenuLeave00413CAD — Game.exe 00413cad, cdecl.  Mode 0: 0054d3fc = 0. */
void MenuLeave00413CAD(int32_t mode) { if (mode == 0) { MenuB0054D3FC = 0; } }
/* MenuSelect00414F9D — Game.exe 00414f9d, cdecl.  Modes 0/1: 0054dbc4 = 3, 0054dbd4 = 3; mode 2: 005fe9d0 = 0, 0054de08 = 1. */
void MenuSelect00414F9D(int32_t mode) { if (mode >= 0) { if (mode < 2) { MenuB0054DBC4 = 3; MenuB0054DBD4 = 3; } else if (mode == 2) { MenuI005FE9D0 = 0; MenuI0054DE08 = 1; } } }
/* MenuSelect00415111 — Game.exe 00415111, cdecl.  Modes 0/1: 0054dbe4 = 3, 0054dbf4 = 3; mode 2: 005fe9d0 = 2, 0054de08 = 3. */
void MenuSelect00415111(int32_t mode) { if (mode >= 0) { if (mode < 2) { MenuB0054DBE4 = 3; MenuB0054DBF4 = 3; } else if (mode == 2) { MenuI005FE9D0 = 2; MenuI0054DE08 = 3; } } }
/* MenuSelect00415230 — Game.exe 00415230, cdecl.  Modes 0/1: 0054dc04 = 3, 0054dc14 = 3; mode 2: 005fe9d0 = 4, 0054de08 = 5. */
void MenuSelect00415230(int32_t mode) { if (mode >= 0) { if (mode < 2) { MenuB0054DC04 = 3; MenuB0054DC14 = 3; } else if (mode == 2) { MenuI005FE9D0 = 4; MenuI0054DE08 = 5; } } }
/* MenuSelect00415323 — Game.exe 00415323, cdecl.  Modes 0/1: 0054dc24 = 3, 0054dc34 = 3; mode 2: 005fe9d0 = 6, 0054de08 = 7. */
void MenuSelect00415323(int32_t mode) { if (mode >= 0) { if (mode < 2) { MenuB0054DC24 = 3; MenuB0054DC34 = 3; } else if (mode == 2) { MenuI005FE9D0 = 6; MenuI0054DE08 = 7; } } }
/* MenuSelect004153B3 — Game.exe 004153b3, cdecl.  Modes 0/1: 0054dc44 = 3, 0054dc54 = 3; mode 2: 005fe9d0 = 8, 0054de08 = 9. */
void MenuSelect004153B3(int32_t mode) { if (mode >= 0) { if (mode < 2) { MenuB0054DC44 = 3; MenuB0054DC54 = 3; } else if (mode == 2) { MenuI005FE9D0 = 8; MenuI0054DE08 = 9; } } }
/* MenuSelect00415456 — Game.exe 00415456, cdecl.  Modes 0/1: 0054dc64 = 3, 0054dc74 = 3; mode 2: 005fe9d0 = 10, 0054de08 = 11. */
void MenuSelect00415456(int32_t mode) { if (mode >= 0) { if (mode < 2) { MenuB0054DC64 = 3; MenuB0054DC74 = 3; } else if (mode == 2) { MenuI005FE9D0 = 10; MenuI0054DE08 = 11; } } }
/* MenuSelect004154F5 — Game.exe 004154f5, cdecl.  Modes 0/1: 0054dc84 = 3, 0054dc94 = 3; mode 2: 005fe9d0 = 12, 0054de08 = 13. */
void MenuSelect004154F5(int32_t mode) { if (mode >= 0) { if (mode < 2) { MenuB0054DC84 = 3; MenuB0054DC94 = 3; } else if (mode == 2) { MenuI005FE9D0 = 12; MenuI0054DE08 = 13; } } }
/* MenuSelect004155AC — Game.exe 004155ac, cdecl.  Modes 0/1: 0054dca4 = 3, 0054dcb4 = 3; mode 2: 005fe9d0 = 14, 0054de08 = 15. */
void MenuSelect004155AC(int32_t mode) { if (mode >= 0) { if (mode < 2) { MenuB0054DCA4 = 3; MenuB0054DCB4 = 3; } else if (mode == 2) { MenuI005FE9D0 = 14; MenuI0054DE08 = 15; } } }
/* MenuSelect00415666 — Game.exe 00415666, cdecl.  Modes 0/1: 0054dcc4 = 3, 0054dcd4 = 3; mode 2: 005fe9d0 = 16, 0054de08 = 17. */
void MenuSelect00415666(int32_t mode) { if (mode >= 0) { if (mode < 2) { MenuB0054DCC4 = 3; MenuB0054DCD4 = 3; } else if (mode == 2) { MenuI005FE9D0 = 16; MenuI0054DE08 = 17; } } }
/* MenuSelect00415718 — Game.exe 00415718, cdecl.  Modes 0/1: 0054dce4 = 3, 005f7e4c = 1; mode 2: 005fe9d0 = 18, 0054de08 = -1, 005f7e4c = 1. */
void MenuSelect00415718(int32_t mode) { if (mode >= 0) { if (mode < 2) { MenuB0054DCE4 = 3; MenuFlag5F7E4C = 1; } else if (mode == 2) { MenuI005FE9D0 = 18; MenuI0054DE08 = -1; MenuFlag5F7E4C = 1; } } }
/* MenuSelect004157B0 — Game.exe 004157b0, cdecl.  Modes 0/1: 0054dcf4 = 3, 005f7e4c = 1; mode 2: 005fe9d0 = 19, 0054de08 = -1, 005f7e4c = 1. */
void MenuSelect004157B0(int32_t mode) { if (mode >= 0) { if (mode < 2) { MenuB0054DCF4 = 3; MenuFlag5F7E4C = 1; } else if (mode == 2) { MenuI005FE9D0 = 19; MenuI0054DE08 = -1; MenuFlag5F7E4C = 1; } } }
/* MenuLeave00416072 — Game.exe 00416072, cdecl.  Mode 0: 0054dfd4 = 0. */
void MenuLeave00416072(int32_t mode) { if (mode == 0) { MenuB0054DFD4 = 0; } }
/* MenuLeave004160D7 — Game.exe 004160d7, cdecl.  Mode 0: 0054dfe4 = 0. */
void MenuLeave004160D7(int32_t mode) { if (mode == 0) { MenuB0054DFE4 = 0; } }
/* MenuLeave0041613C — Game.exe 0041613c, cdecl.  Mode 0: 0054dff4 = 0. */
void MenuLeave0041613C(int32_t mode) { if (mode == 0) { MenuB0054DFF4 = 0; } }
/* MenuLeave004161A1 — Game.exe 004161a1, cdecl.  Mode 0: 0054e004 = 0. */
void MenuLeave004161A1(int32_t mode) { if (mode == 0) { MenuB0054E004 = 0; } }
/* MenuLeave00416449 — Game.exe 00416449, cdecl.  Mode 0: 0054e1a4 = 0. */
void MenuLeave00416449(int32_t mode) { if (mode == 0) { MenuB0054E1A4 = 0; } }
/* MenuLeave004164A0 — Game.exe 004164a0, cdecl.  Mode 0: 0054e1b4 = 0. */
void MenuLeave004164A0(int32_t mode) { if (mode == 0) { MenuB0054E1B4 = 0; } }
