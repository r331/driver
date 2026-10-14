#include "uihandlers4.h"
GAME_VAR_DEF(int32_t, G01271060, 0x01271060)
GAME_VAR_DEF(int32_t, G00549FBC, 0x00549fbc)
GAME_VAR_DEF(int32_t, G00549FCC, 0x00549fcc)
GAME_VAR_DEF(int32_t, G0054A0BC, 0x0054a0bc)
GAME_VAR_DEF(int32_t, G0054A0C0, 0x0054a0c0)
GAME_VAR_DEF(int32_t, G0054A0CC, 0x0054a0cc)
GAME_VAR_DEF(int32_t, G0054A0D0, 0x0054a0d0)
GAME_VAR_DEF(int32_t, G0054A838, 0x0054a838)
GAME_VAR_DEF(int32_t, G0054A844, 0x0054a844)
GAME_VAR_DEF(int32_t, G0054A848, 0x0054a848)
GAME_VAR_DEF(int32_t, G0054A854, 0x0054a854)
GAME_VAR_DEF(int32_t, G0054A858, 0x0054a858)
GAME_VAR_DEF(int32_t, G0054A8EC, 0x0054a8ec)
GAME_VAR_DEF(int32_t, G0054A8FC, 0x0054a8fc)
GAME_VAR_DEF(int32_t, G0054A90C, 0x0054a90c)
GAME_VAR_DEF(int32_t, G0054A91C, 0x0054a91c)
GAME_VAR_DEF(int32_t, G0054A92C, 0x0054a92c)
GAME_VAR_DEF(int32_t, G0054A93C, 0x0054a93c)
GAME_VAR_DEF(int32_t, G0054A94C, 0x0054a94c)
GAME_VAR_DEF(int32_t, G0055384C, 0x0055384c)
GAME_VAR_DEF(int32_t, G00553850, 0x00553850)
GAME_VAR_DEF(int32_t, G0055C974, 0x0055c974)
GAME_VAR_DEF(int32_t, G005759A4, 0x005759a4)
GAME_VAR_DEF(int32_t, G00575EE8, 0x00575ee8)
GAME_VAR_DEF(int32_t, G00575EF0, 0x00575ef0)
GAME_VAR_DEF(int32_t, G00575EF8, 0x00575ef8)
GAME_VAR_DEF(int32_t, G00575F30, 0x00575f30)
GAME_VAR_DEF(int32_t, G00575F3C, 0x00575f3c)
GAME_VAR_DEF(int32_t, G00575F44, 0x00575f44)
GAME_VAR_DEF(int32_t, G005D577C, 0x005d577c)
GAME_VAR_DEF(int32_t, G005F7E4C, 0x005f7e4c)
GAME_VAR_DEF(int32_t, G00B201DC, 0x00b201dc)
GAME_VAR_DEF(int32_t, G00B31F04, 0x00b31f04)
GAME_VAR_DEF(int32_t, G00B87E4C, 0x00b87e4c)
GAME_VAR_DEF(int32_t, G00B87E9C, 0x00b87e9c)
GAME_VAR_DEF(int32_t, G00BDFA44, 0x00bdfa44)
GAME_VAR_DEF(int32_t, G00BDFA48, 0x00bdfa48)
GAME_VAR_DEF(int32_t, G00BDFA4C, 0x00bdfa4c)
GAME_VAR_DEF(int32_t, G00BDFA50, 0x00bdfa50)
GAME_VAR_DEF(int32_t, G00BDFA54, 0x00bdfa54)
GAME_VAR_DEF(int32_t, G00BDFA58, 0x00bdfa58)
GAME_VAR_DEF(int32_t, G00C559A4, 0x00c559a4)
GAME_VAR_DEF(int32_t, G00C559A8, 0x00c559a8)
GAME_VAR_DEF(int32_t, G00C559F0, 0x00c559f0)
GAME_VAR_DEF(int32_t, G00C559F4, 0x00c559f4)
GAME_VAR_DEF(int32_t, G00C55A04, 0x00c55a04)
GAME_VAR_DEF(int32_t, G00D118C8, 0x00d118c8)
void Set5F7E4C_1(void) { G005F7E4C = 1;
}
void Set54A0CC_0(void) { G0054A0CC = 0;
}
void Set54A0BC_1(void) { G0054A0BC = 1;
}
void Set54A0BC_0(void) { G0054A0BC = 0;
}
void Inc5D577C(void) { G005D577C++;
}
void Set54A844_1(void) { G0054A844 = 1;
}
void Set54A844_0(void) { G0054A844 = 0;
}
void Set54A854_1(void) { G0054A854 = 1;
}
void Set54A854_0(void) { G0054A854 = 0;
}
int32_t Set575EF0_4Ret0(void) { G00575EF0 = 4; return 0;
}
int32_t ToggleBDFA44_Call40500D(void) { G00BDFA44 ^= 1; MenuRefresh(); return 0;
}
int32_t ToggleBDFA48_Call40500D(void) { G00BDFA48 ^= 1; MenuRefresh(); return 0;
}
int32_t ToggleBDFA4C_Call40500D(void) { G00BDFA4C ^= 1; MenuRefresh(); return 0;
}
int32_t ToggleBDFA50_Call40500D(void) { G00BDFA50 ^= 1; MenuRefresh(); return 0;
}
int32_t ToggleBDFA54_Call40500D(void) { G00BDFA54 ^= 1; MenuRefresh(); return 0;
}
int32_t ToggleB87E9C_Call40500D(void) { G00B87E9C ^= 1; MenuRefresh(); return 0;
}
int32_t ToggleBDFA58_Call40500D(void) { G00BDFA58 ^= 1; MenuRefresh(); return 0;
}
int32_t ToggleEF8_55384C(void) { G0055384C ^= 1; G00575EF8 = 4; MenuRedraw(); return 0;
}
int32_t ToggleEF8_553850(void) { G00553850 ^= 1; G00575EF8 = 4; MenuRedraw(); return 0;
}
int32_t ToggleEF8_B31F04(void) { G00B31F04 ^= 1; G00575EF8 = 4; MenuRedraw(); return 0;
}
int32_t ToggleEF8_575F44(void) { G00575F44 ^= 1; G00575EF8 = 4; MenuRedraw(); return 0;
}
int32_t ToggleEF8_55C974(void) { G0055C974 ^= 1; G00575EF8 = 4; MenuRedraw(); return 0;
}
int32_t ToggleEF8_575F30(void) { G00575F30 ^= 1; G00575EF8 = 4; MenuRedraw(); return 0;
}
int32_t ToggleEF8_B201DC(void) { G00B201DC ^= 1; G00575EF8 = 4; MenuRedraw(); return 0;
}
int32_t ToggleEF8_575EE8(void) { G00575EE8 ^= 1; G00575EF8 = 4; MenuRedraw(); return 0;
}
int32_t ToggleEF8_575F3C(void) { G00575F3C ^= 1; G00575EF8 = 4; MenuRedraw(); return 0;
}
int32_t ToggleEF8_D118C8(void) { G00D118C8 ^= 1; G00575EF8 = 4; MenuRedraw(); return 0;
}
int32_t RefreshMenu00409231(void) { G00575EF8 = 4; MenuRedraw(); return 0;
}
int32_t RefreshMenu004092D8(void) { G00575EF8 = 4; MenuRedraw(); return 0;
}
int32_t RefreshMenu0040937F(void) { G00575EF8 = 4; MenuRedraw(); return 0;
}
int32_t RefreshMenu00409426(void) { G00575EF8 = 4; MenuRedraw(); return 0;
}
int32_t RefreshMenu004094CD(void) { G00575EF8 = 4; MenuRedraw(); return 0;
}
void Inc5759A4Max40(void) { if (G005759A4 < 64) { G005759A4++; G00575EF8 = 4; MenuRedraw(); }
}
void Dec5759A4Min0(void) { if (G005759A4 > 0) { G005759A4--; G00575EF8 = 4; MenuRedraw(); }
}
void IncB87E4CMax3(void) { if (G00B87E4C < 3) { G00B87E4C++; G00575EF8 = 4; MenuRedraw(); }
}
void DecB87E4CMin0(void) { if (G00B87E4C > 0) { G00B87E4C--; G00575EF8 = 4; MenuRedraw(); }
}
void Select54A90C_Mode2(void) { G0054A90C = 1; G01271060 = 2;
}
void Select54A91C_Mode1(void) { G0054A91C = 1; G01271060 = 1;
}
void Select54A8FC_Mode5(void) { G0054A8FC = 1; G01271060 = 5;
}
void Select54A92C_Mode3(void) { G0054A92C = 1; G01271060 = 3;
}
void Select54A8EC_Mode4(void) { G0054A8EC = 1; G01271060 = 4;
}
void Select54A94C_Mode7(void) { G0054A94C = 1; G01271060 = 7;
}
void Select54A93C_Mode6(void) { G0054A93C = 1; G01271060 = 6;
}
void Clear54A90C_IfZero(int32_t a0) { if (a0 == 0) G0054A90C = 0;
}
void Clear54A91C_IfZero(int32_t a0) { if (a0 == 0) G0054A91C = 0;
}
void Clear54A8FC_IfZero(int32_t a0) { if (a0 == 0) G0054A8FC = 0;
}
void Clear54A92C_IfZero(int32_t a0) { if (a0 == 0) G0054A92C = 0;
}
void Clear54A8EC_IfZero(int32_t a0) { if (a0 == 0) G0054A8EC = 0;
}
void Clear54A94C_IfZero(int32_t a0) { if (a0 == 0) G0054A94C = 0;
}
void Menu549FBC(int32_t a0) { if (a0 == 0) G00549FBC = 2; else if (a0 == 2) Call004076E2();
}
void Menu549FCC(int32_t a0) { if (a0 == 0) G00549FCC = 2; else if (a0 == 2) Call004076E2();
}
void Copy54A0C0(void) { G0054A0C0 = G00C559A4; G0054A0D0 = G00C559A8;
}
void Copy54A838(void) { G0054A838 = G00C55A04; G0054A848 = G00C559F0; G0054A858 = G00C559F4;
}
