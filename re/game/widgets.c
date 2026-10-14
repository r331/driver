#include "widgets.h"
GAME_VAR_DEF(int32_t, WI00575EE4, 0x00575ee4)
GAME_VAR_DEF(int32_t, WI00B87E2C, 0x00b87e2c)
GAME_VAR_DEF(int32_t, WI005FE694, 0x005fe694)
GAME_VAR_DEF(uint32_t, WU005FE788, 0x005fe788)
GAME_VAR_DEF(int32_t, WI005FE78C, 0x005fe78c)
GAME_VAR_DEF(int32_t, WI005FE790, 0x005fe790)
GAME_VAR_DEF(float, WF00575F14, 0x00575f14)
GAME_VAR_DEF(float, WF00575F18, 0x00575f18)
GAME_VAR_DEF(float, WF00546020, 0x00546020)
GAME_VAR_DEF(float, WF00546024, 0x00546024)
GAME_VAR_DEF(float, WF0054606C, 0x0054606c)
GAME_VAR_DEF(uint32_t, WU0054E830, 0x0054e830)
GAME_VAR_DEF(uint32_t, WU00C55A70, 0x00c55a70)
GAME_VAR_DEF(uint32_t, WU0054CBB0, 0x0054cbb0)
GAME_VAR_DEF(uint32_t, WU0054CBC4, 0x0054cbc4)
GAME_VAR_DEF(uint32_t, WU0054CBD8, 0x0054cbd8)
GAME_VAR_DEF(uint32_t, WU0054CBEC, 0x0054cbec)
GAME_VAR_DEF(uint32_t, WU0054CC00, 0x0054cc00)
GAME_VAR_DEF(uint32_t, WU0054CC14, 0x0054cc14)
GAME_VAR_DEF(uint32_t, WU0054CC28, 0x0054cc28)
GAME_VAR_DEF(wd_ints5_t, WA00B20330, 0x00b20330)
GAME_VAR_DEF(int32_t, WI00B20344, 0x00b20344)
GAME_VAR_DEF(wd_pairs4_t, WA0056039C, 0x0056039c)
GAME_VAR_DEF(int32_t, WI00B20348, 0x00b20348)
GAME_VAR_DEF(uint16_t, WH00B2C3A8, 0x00b2c3a8)
GAME_VAR_DEF(wd_bytes_t, WB0054C6D4, 0x0054c6d4)
GAME_VAR_DEF(wd_bytes_t, WB0054C944, 0x0054c944)
static int32_t SelectRow(uint32_t row_addr, int32_t id) {
    WI005FE78C = 1; WU005FE788 = row_addr; WI005FE790 = id; Call00411A9D();
    MenuI005FE798 = WI005FE790; MenuI005FE79C = -1; return 0;
}
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
void VolumeUp00409BC9(void) {WI00575EE4 += 0x10; if (WI00575EE4 > 0x40) WI00575EE4 = 0x40; G00575EF8 = 4; MenuRedraw();}
void VolumeDown00409BFD(void) {WI00575EE4 -= 0x10; if (WI00575EE4 < 0x10) WI00575EE4 = 0x10; G00575EF8 = 4; MenuRedraw();}
int32_t CycleInc0040E918(void) {WI00B87E2C++; if (WI00B87E2C == 3) WI00B87E2C = 0; Call0040EA70(); return 0;}
int32_t CycleDec0040F364(void) {UiVar005FE6BC--; if (UiVar005FE6BC < 0) UiVar005FE6BC = WI005FE694 - 1; Call0040F3DE(); return 0;}
int32_t CycleInc0040F3AD(void) {UiVar005FE6BC++; if (WI005FE694 <= UiVar005FE6BC) UiVar005FE6BC = 0; Call0040F3DE(); return 0;}
void MenuRowsTo2_00412254(void) {WB0054C6D4[(UiVar005FE84C * 2 + 3) * 0x10] = 2; WB0054C6D4[(UiVar005FE84C * 2 + 4) * 0x10] = 2;}
void MenuAllRowsTo2_00412280(void) {for (int i = 0; i < 8; i++) { WB0054C6D4[(i * 2 + 3) * 0x10] = 2; WB0054C6D4[(i * 2 + 4) * 0x10] = 2; }}
void MenuRowsTo3_00412643(void) {WB0054C944[(UiVar005FE928 * 2 + 3) * 0x10] = 3; WB0054C944[(UiVar005FE928 * 2 + 4) * 0x10] = 3;}
void MenuRowsTo2_0041266F(void) {WB0054C944[(UiVar005FE928 * 2 + 3) * 0x10] = 2; WB0054C944[(UiVar005FE928 * 2 + 4) * 0x10] = 2;}
void MenuAllRowsTo2_0041269B(void) {for (int i = 0; i < 8; i++) { WB0054C944[(i * 2 + 3) * 0x10] = 2; WB0054C944[(i * 2 + 4) * 0x10] = 2; }}
void SetIconName00412A36(int32_t reset) {if (reset == 0) WU0054CBB0 = 0x0054cdfc;}
void SetIconName00412AA4(int32_t reset) {if (reset == 0) WU0054CBC4 = 0x0054ce14;}
void SetIconName00412B12(int32_t reset) {if (reset == 0) WU0054CBD8 = 0x0054ce2c;}
void SetIconName00412B80(int32_t reset) {if (reset == 0) WU0054CBEC = 0x0054ce44;}
void SetIconName00412BEE(int32_t reset) {if (reset == 0) WU0054CC00 = 0x0054ce5c;}
void SetIconName00412C5C(int32_t reset) {if (reset == 0) WU0054CC14 = 0x0054ce74;}
void SetIconName00412CCA(int32_t reset) {if (reset == 0) WU0054CC28 = 0x0054ce8c;}
void SetIconName00412D38(int32_t reset) {if (reset == 0) WU0054CC28 = 0x0054cea4;}
void StepUp00415848(void) {if (WF00575F14 < WF00546020) { WF00575F14 = WF00575F14 + WF0054606C; Call00414D1F(); }}
void StepDown00415877(void) {if (WF00546024 < WF00575F14) { WF00575F14 = WF00575F14 - WF0054606C; Call00414D1F(); }}
void StepUp004158A6(void) {if (WF00575F18 < WF00546020) { WF00575F18 = WF00575F18 + WF0054606C; Call00414D1F(); }}
void StepDown004158D5(void) {if (WF00546024 < WF00575F18) { WF00575F18 = WF00575F18 - WF0054606C; Call00414D1F(); }}
void StepUp0050F9B4(void) {if (WF00575F14 < WF00546020) { WF00575F14 = WF00575F14 + WF0054606C; Call0050F7B2(); }}
void StepDown0050F9E3(void) {if (WF00546024 < WF00575F14) { WF00575F14 = WF00575F14 - WF0054606C; Call0050F7B2(); }}
void StepUp0050FA12(void) {if (WF00575F18 < WF00546020) { WF00575F18 = WF00575F18 + WF0054606C; Call0050F7B2(); }}
void StepDown0050FA41(void) {if (WF00546024 < WF00575F18) { WF00575F18 = WF00575F18 - WF0054606C; Call0050F7B2(); }}
void CopyWord0041AD8D(void) {WU0054E830 = WU00C55A70; Call0041AFCA();}
int32_t RangeCheck00514E6A(const int32_t* p, int32_t n) {return p[0x2c/4] <= n * p[0x30/4] + p[0x34/4];}
float Dot3_00526029(const float* a, const float* b) {return a[2] * b[2] + a[1] * b[1] + a[0] * b[0];}
float GetConst0041FA5E(void) {return WF00546024;}
void ClearSlots004D61CF(void) {for (int i = 0; i < 5; i++) WA00B20330[i] = -1; WI00B20344 = 0;}
void ClearPairs004D6C20(void) {for (int i = 0; i < 4; i++) WA0056039C[i * 2] = 0; WI00B20348 = 0;}
void Pack565_004D950F(int16_t r, int16_t g, int16_t b) {WH00B2C3A8 = (uint16_t)((((int32_t)r >> 3) << 11) | (((int32_t)g >> 2) << 5) | (b >> 3));}
void AddVelocity004E122C(int32_t* o) {o[0x4c/4] += *(int16_t*)((uint8_t*)o + 4) * 0x32; o[0x50/4] += *(int16_t*)((uint8_t*)o + 10) * 0x32; o[0x54/4] += *(int16_t*)((uint8_t*)o + 0x10) * 0x32;}
int32_t Get4Words004E4379(const int32_t* s, int32_t* d) {if (d) { d[0] = s[1]; d[1] = s[2]; d[2] = s[3]; d[3] = s[4]; } return 0;}
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
