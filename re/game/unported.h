/* Вызовы функций Game.exe, которые ещё не перенесены.
   RE_HOOK_BUILD: вызов по адресу в оригинальном Game.exe (__cdecl).
   Нативная сборка: заглушка из platform/native/stubs.c, пишет в лог «not ported: ИМЯ (адрес)».
   Список — X-макросы: UNPORTED_V(имя, адрес, (параметры), (аргументы)) для void,
                       UNPORTED_R(тип, имя, адрес, (параметры), (аргументы)) для остальных (заглушка возвращает 0). */
#pragma once
#include "gvar.h"

#define UNPORTED_LIST(V, R) \
    R(int32_t, P59_Fn4A6A57, 0x004a6a57, (const void *a, const void *b, const void *c), (a, b, c)) \
    V(P59_Fn4A5634, 0x004a5634, (const char *a, int32_t i), (a, i)) \
    R(int32_t, P59_Fn417970, 0x00417970, (void), ()) \
    V(P57_MenuInit, 0x0040c8a0, (uint32_t tbl, int32_t n), (tbl, n)) \
    R(int32_t, P57_MenuStep, 0x0040c8f1, (uint32_t tbl, int32_t *state), (tbl, state)) \
    V(P57_Setup40A41C, 0x0040a41c, (void), ()) \
    V(P57_Setup40831C, 0x0040831c, (void), ()) \
    V(P57_Setup41351C, 0x0041351c, (void), ()) \
    V(P57_Setup41390C, 0x0041390c, (void), ()) \
    V(P57_Setup40A5C6, 0x0040a5c6, (void), ()) \
    V(P57_Setup413691, 0x00413691, (void), ()) \
    V(P57_Setup413B7C, 0x00413b7c, (void), ()) \
    V(P57_Setup41640C, 0x0041640c, (void), ()) \
    V(P57_Setup40479B, 0x0040479b, (void), ()) \
    V(P57_Setup4048DD, 0x004048dd, (void), ()) \
    V(P57_Setup412087, 0x00412087, (void), ()) \
    V(P57_Setup412280, 0x00412280, (void), ()) \
    V(P57_Setup4122E7, 0x004122e7, (void), ()) \
    V(P57_Setup412487, 0x00412487, (void), ()) \
    V(P57_Setup41269B, 0x0041269b, (void), ()) \
    V(P57_Setup412702, 0x00412702, (void), ()) \
    V(P57_Fn51C900, 0x0051c900, (void), ()) \
    V(P57_Fn51CAA7, 0x0051caa7, (void *f), (f)) \
    V(P57_Fn51CB98, 0x0051cb98, (void *f), (f)) \
    V(P57_Fn4221BF, 0x004221bf, (int32_t i), (i)) \
    V(P57_Fn507672, 0x00507672, (float *x, float *y), (x, y)) \
    V(P56_CallSetVoice, 0x00523cda, (uint32_t a0, int32_t a1, float a2, float a3, float a4), (a0, a1, a2, a3, a4)) \
    R(uint8_t *, P56_FindIcon, 0x004ec91e, (const char *a0), (a0)) \
    V(P56_DrawText, 0x0051755e, (int32_t a0, int32_t a1, const char *a2, int32_t a3, int32_t a4, int32_t a5, int32_t a6, int32_t a7), (a0, a1, a2, a3, a4, a5, a6, a7)) \
    V(P56_DrawSpr, 0x004d8511, (float a0, float a1, float a2, float a3, void *a4, int32_t a5, int32_t a6, int32_t a7, int32_t a8), (a0, a1, a2, a3, a4, a5, a6, a7, a8)) \
    V(P56_Fn406479, 0x00406479, (void), ()) \
    V(P56_Fn4DA76A, 0x004da76a, (int32_t *a0, uint8_t *a1), (a0, a1)) \
    R(int32_t, P56_Fn40682D, 0x0040682d, (void *a0, int32_t a1), (a0, a1)) \
    V(P56_Fn4E5284, 0x004e5284, (void *a0), (a0)) \
    V(P56_Fn4E5011, 0x004e5011, (int32_t a0, void *a1), (a0, a1)) \
    V(P56_Fn4E53B5, 0x004e53b5, (int32_t a0, void *a1), (a0, a1)) \
    V(P55_Fn4EE18B, 0x004ee18b, (uint32_t a0), (a0)) \
    V(P55_Fn4ED5F8, 0x004ed5f8, (int32_t a0, int32_t a1), (a0, a1)) \
    V(P55_Fn4EDAA2, 0x004edaa2, (void), ()) \
    R(int32_t, P55_Fn405E79, 0x00405e79, (int32_t a0, void *a1), (a0, a1)) \
    R(int32_t, P55_Fn405FDB, 0x00405fdb, (int32_t a0, void *a1), (a0, a1)) \
    V(P55_Fn4D92D2, 0x004d92d2, (uint32_t a0), (a0)) \
    V(P55_Fn5248CD, 0x005248cd, (void), ()) \
    V(P55_Fn424530, 0x00424530, (int32_t a0, int32_t a1, int32_t a2), (a0, a1, a2)) \
    R(int32_t, P55_Fn4245E2, 0x004245e2, (void), ()) \
    R(int32_t, P55_Fn425F7B, 0x00425f7b, (int32_t a0, int32_t a1, int32_t a2), (a0, a1, a2)) \
    V(P55_Fn4264A7, 0x004264a7, (void), ()) \
    V(P55_Fn417651, 0x00417651, (int32_t a0, int32_t a1, int32_t a2, int32_t a3, int32_t a4, int32_t a5), (a0, a1, a2, a3, a4, a5)) \
    V(P55_Fn4E7450, 0x004e7450, (int32_t a0, const char *a1), (a0, a1)) \
    V(N54_Fn4949F0, 0x004949f0, (void *a0), (a0)) \
    V(N54_Fn4913CC, 0x004913cc, (int32_t a0, int32_t a1, int32_t a2, int32_t a3, uint32_t a4), (a0, a1, a2, a3, a4)) \
    R(int32_t, P53_Fn40EFD5, 0x0040efd5, (void), ()) \
    R(int32_t, P53_Fn42248B, 0x0042248b, (void *a0, int32_t a1, int32_t a2, int32_t a3), (a0, a1, a2, a3)) \
    R(int32_t, P53_Fn4225EB, 0x004225eb, (int32_t a0, int32_t a1, int32_t a2, int32_t a3), (a0, a1, a2, a3)) \
    V(P53_Fn500937, 0x00500937, (void *a0, int32_t a1, int32_t a2, int32_t a3, int32_t a4, int32_t a5), (a0, a1, a2, a3, a4, a5)) \
    R(int32_t, P53_Fn4045E0, 0x004045e0, (void), ()) \
    V(P53_Fn4146FB, 0x004146fb, (int32_t a0), (a0)) \
    V(P52_Fn4E6310, 0x004e6310, (void), ()) \
    V(P52_Fn4E5A1A, 0x004e5a1a, (void), ()) \
    V(P52_Fn4E5B78, 0x004e5b78, (void), ()) \
    V(P52_Fn4ABD69, 0x004abd69, (void), ()) \
    V(P52_Fn4AB127, 0x004ab127, (void), ()) \
    V(P52_Fn4AB500, 0x004ab500, (void), ()) \
    V(P52_Fn4AB808, 0x004ab808, (void), ()) \
    V(P52_Fn4AB95C, 0x004ab95c, (void), ()) \
    V(P52_Fn4ABA7C, 0x004aba7c, (void), ()) \
    R(int32_t, P52_Fn48B3E8, 0x0048b3e8, (int32_t a0), (a0)) \
    R(int32_t, P52_Fn48B5E3, 0x0048b5e3, (void), ()) \
    V(P52_Fn5173D7, 0x005173d7, (float a0, float a1, int32_t a2, int32_t a3, int32_t a4), (a0, a1, a2, a3, a4)) \
    V(P52_Fn519408, 0x00519408, (void), ()) \
    R(int32_t, P52_Fn405F6F, 0x00405f6f, (int32_t a0, void *a1), (a0, a1)) \
    V(P52_Fn41D53C, 0x0041d53c, (int32_t a0, int32_t a1, int32_t a2, int32_t a3, int32_t a4), (a0, a1, a2, a3, a4)) \
    V(P48_Fn516DA0, 0x00516da0, (void), ()) \
    R(int32_t, P47_Fn51B111, 0x0051b111, (int32_t a0, int32_t a1), (a0, a1)) \
    R(uint32_t, P47_Fn51B566, 0x0051b566, (int32_t a0, int32_t a1), (a0, a1)) \
    V(P47_Fn4D90F4, 0x004d90f4, (const char *a0), (a0)) \
    R(int32_t, P47_Fn49F20A, 0x0049f20a, (const char *a0), (a0)) \
    R(int32_t, P47_Fn40A3A0, 0x0040a3a0, (void), ()) \
    V(P47_Fn405BFA, 0x00405bfa, (void), ()) \
    R(int32_t, P47_Fn405FDB, 0x00405fdb, (int32_t a0, int32_t a1), (a0, a1)) \
    R(int32_t, P47_Fn406199, 0x00406199, (int32_t a0), (a0)) \
    V(P47_Fn517D58, 0x00517d58, (const char *a0), (a0)) \
    R(uint32_t, N14_Rand, 0x0052e190, (void), ()) \
    V(Fn00416040, 0x00416040, (int32_t a0), (a0)) \
    V(N14_Fn4CB4FF, 0x004cb4ff, (int32_t a0, int32_t a1, int32_t a2), (a0, a1, a2)) \
    V(N14_Fn4FBA23, 0x004fba23, (const uint8_t* a0), (a0)) \
    V(N14_Fn4D6C5A, 0x004d6c5a, (void), ()) \
    V(N14_Fn4D6DAC, 0x004d6dac, (void), ()) \
    V(N14_Fn4D6EF2, 0x004d6ef2, (void), ()) \
    V(N14_Fn5259C8, 0x005259c8, (int32_t a0), (a0)) \
    V(N14_Fn4D2ADE, 0x004d2ade, (int32_t a0), (a0)) \
    V(N14_Fn4A7EE9, 0x004a7ee9, (int32_t a0), (a0)) \
    V(N14_Fn48A627, 0x0048a627, (void), ()) \
    R(uint32_t, N14_Fn503ECC, 0x00503ecc, (const uint8_t* a0), (a0)) \
    V(Call00405D60, 0x00405d60, (int32_t a0, uint32_t a1), (a0, a1)) \
    V(Call0049EC01, 0x0049ec01, (int32_t a0, uint32_t a1), (a0, a1)) \
    V(Call0040CCB4, 0x0040ccb4, (uint32_t a0, uint32_t a1), (a0, a1)) \
    R(int32_t, R12_4082A0, 0x004082a0, (void), ()) \
    R(int32_t, R12_413D70, 0x00413d70, (void), ()) \
    R(int32_t, R12_413B00, 0x00413b00, (void), ()) \
    R(int32_t, R12_4134A0, 0x004134a0, (void), ()) \
    R(int32_t, R12_413890, 0x00413890, (void), ()) \
    R(int32_t, R12_416390, 0x00416390, (void), ()) \
    R(int32_t, R12_40A540, 0x0040a540, (void), ()) \
    R(int32_t, R12_404850, 0x00404850, (void), ()) \
    R(int32_t, R12_415EC0, 0x00415ec0, (void), ()) \
    R(int32_t, R12_413610, 0x00413610, (void), ()) \
    R(int32_t, R12_411FD0, 0x00411fd0, (void), ()) \
    R(int32_t, R12_40E870, 0x0040e870, (void), ()) \
    R(int32_t, R12_4123D0, 0x004123d0, (void), ()) \
    R(int32_t, R12_40F2D0, 0x0040f2d0, (void), ()) \
    R(int32_t, R12_410C30, 0x00410c30, (void), ()) \
    R(int32_t, R12_40FA60, 0x0040fa60, (void), ()) \
    R(int32_t, R12_408770, 0x00408770, (void), ()) \
    R(int32_t, R12_414C30, 0x00414c30, (void), ()) \
    R(int32_t, R12_407160, 0x00407160, (void), ()) \
    V(Call00517D58, 0x00517d58, (uint32_t a0), (a0)) \
    R(int32_t, R12_405CB4, 0x00405cb4, (int32_t a0), (a0)) \
    R(int32_t, R12_405F2E, 0x00405f2e, (int32_t a0), (a0)) \
    V(Call004122C4, 0x004122c4, (void), ()) \
    V(Call004126DF, 0x004126df, (void), ()) \
    V(Call00523595, 0x00523595, (void), ()) \
    V(Call005233BE, 0x005233be, (int32_t a0, int32_t a1, int32_t a2), (a0, a1, a2)) \
    V(Call00524496, 0x00524496, (uint32_t a0, int32_t a1), (a0, a1)) \
    V(Call0052360D, 0x0052360d, (int32_t a0), (a0)) \
    V(Call004184DE, 0x004184de, (uint32_t a0), (a0)) \
    V(Call0041846C, 0x0041846c, (uint32_t a0, uint32_t a1), (a0, a1)) \
    V(Call0040C610, 0x0040c610, (uint32_t a0, int32_t a1), (a0, a1)) \
    V(Call004086B4, 0x004086b4, (void), ()) \
    V(Call004086EA, 0x004086ea, (void), ()) \
    V(Call004D78F3, 0x004d78f3, (int32_t a0), (a0)) \
    R(int32_t, R12_4D97E9, 0x004d97e9, (void), ()) \
    R(uint32_t, R12_40DAE1, 0x0040dae1, (uint32_t a0, int32_t a1, int32_t a2), (a0, a1, a2)) \
    V(Call00424921, 0x00424921, (int32_t a0, int32_t a1, uint32_t a2, int32_t a3), (a0, a1, a2, a3)) \
    V(Call0048A525, 0x0048a525, (int32_t a0), (a0)) \
    V(Call0048A68E, 0x0048a68e, (int32_t a0), (a0)) \
    V(Call004248C6, 0x004248c6, (int32_t a0, int32_t a1, int32_t a2, uint32_t a3, int32_t a4), (a0, a1, a2, a3, a4)) \
    V(Call004C0C6F, 0x004c0c6f, (int32_t a0), (a0)) \
    V(Call004BA31B, 0x004ba31b, (void), ()) \
    V(Call004B9AEC, 0x004b9aec, (void), ()) \
    V(Call004B9D79, 0x004b9d79, (void), ()) \
    V(Call004B998B, 0x004b998b, (uint32_t a0), (a0)) \
    V(Call004911D9, 0x004911d9, (void), ()) \
    V(Call0050F289, 0x0050f289, (void), ()) \
    V(Call0050EE00, 0x0050ee00, (void), ()) \
    R(int32_t, R12_40A8B0, 0x0040a8b0, (uint32_t a0, int32_t a1, int32_t a2, int32_t a3, int32_t a4), (a0, a1, a2, a3, a4)) \
    V(Call004DAA36, 0x004daa36, (uint32_t a0, uint32_t a1), (a0, a1)) \
    V(Call00527885, 0x00527885, (int32_t a0, int32_t a1, int32_t a2, uint32_t a3), (a0, a1, a2, a3)) \
    V(Call004D6190, 0x004d6190, (int32_t a0), (a0)) \
    V(Call0048DB65, 0x0048db65, (uint32_t a0, int32_t a1), (a0, a1)) \
    V(Call0051551E, 0x0051551e, (int32_t a0), (a0)) \
    V(Call00493ECE, 0x00493ece, (int32_t a0), (a0)) \
    V(Call0051200F, 0x0051200f, (uint32_t a0), (a0)) \
    V(Call005186CE, 0x005186ce, (void), ()) \
    V(Call004E3391, 0x004e3391, (void), ()) \
    V(Call0052A910, 0x0052a910, (uint32_t a0, uint32_t a1, int32_t a2), (a0, a1, a2)) \
    V(Call0041219E, 0x0041219e, (void), ()) \
    V(Call004125B9, 0x004125b9, (void), ()) \
    V(Call0052369B, 0x0052369b, (int32_t a0), (a0)) \
    V(Call00524873, 0x00524873, (void), ()) \
    V(Call00524763, 0x00524763, (void), ()) \
    V(Call00408770, 0x00408770, (void), ()) \
    V(Call004072BE, 0x004072be, (void), ()) \
    R(int32_t, Call00528221, 0x00528221, (int32_t a0, int32_t a1, uint32_t a2), (a0, a1, a2)) \
    V(Call0040C165, 0x0040c165, (void), ()) \
    V(Call0040C20B, 0x0040c20b, (int32_t a0), (a0)) \
    V(Call0040BF50, 0x0040bf50, (void), ()) \
    V(Call0048B65D, 0x0048b65d, (void), ()) \
    V(Call0048B568, 0x0048b568, (void), ()) \
    V(Call005237B1, 0x005237b1, (void), ()) \
    V(Call0052436A, 0x0052436a, (void), ()) \
    V(Call0052479E, 0x0052479e, (int32_t a0), (a0)) \
    V(Call004D28A3, 0x004d28a3, (int32_t a0), (a0)) \
    V(Call004EAFE0, 0x004eafe0, (int32_t a0), (a0)) \
    V(Call00514A47, 0x00514a47, (int32_t a0), (a0)) \
    V(Call005283B5, 0x005283b5, (uint32_t a0, int32_t a1, int32_t a2), (a0, a1, a2)) \
    R(int32_t, Call0052ADB0, 0x0052adb0, (uint32_t a0, uint32_t a1), (a0, a1)) \
    V(Call004FBBFC, 0x004fbbfc, (uint32_t a0), (a0)) \
    V(Call0040EA70, 0x0040ea70, (void), ()) \
    V(Call00419B35, 0x00419b35, (void), ()) \
    V(Call00414D1F, 0x00414d1f, (void), ()) \
    V(Call0041A1F9, 0x0041a1f9, (int32_t a0), (a0)) \
    R(int32_t, Call0042655A, 0x0042655a, (int32_t a0), (a0)) \
    V(Call0041D6AA, 0x0041d6aa, (void), ()) \
    V(Call004D90F4, 0x004d90f4, (int32_t a0), (a0)) \
    V(Call004D611B, 0x004d611b, (int32_t a0), (a0)) \
    V(Call004A2C98, 0x004a2c98, (void), ()) \
    V(Call004D9478, 0x004d9478, (void), ()) \
    V(Call004C1B46, 0x004c1b46, (void), ()) \
    V(UiCall0041A8AB, 0x0041a8ab, (void), ()) \
    V(UiCall004EE065, 0x004ee065, (void), ()) \
    V(UiCall004184F5, 0x004184f5, (void), ()) \
    V(UiCall005170AB, 0x005170ab, (void), ()) \
    V(UiCall00419DB3, 0x00419db3, (void), ()) \
    V(UiCall0041A085, 0x0041a085, (void), ()) \
    V(UiCall00417620, 0x00417620, (void), ()) \
    V(UiCall00414C30, 0x00414c30, (void), ()) \
    V(UiCall00407160, 0x00407160, (void), ()) \
    V(UiCall00419AB0, 0x00419ab0, (void), ()) \
    V(UiCall0041B059, 0x0041b059, (void), ()) \
    V(UiCall0041AF29, 0x0041af29, (int32_t a0), (a0)) \
    V(UiCall0041F2A0, 0x0041f2a0, (void), ()) \
    V(UiCall00424647, 0x00424647, (void), ()) \
    V(UiCall00528455, 0x00528455, (void), ()) \
    V(UiCall004D8F30, 0x004d8f30, (int32_t a0), (a0)) \
    V(UiCall0040C455, 0x0040c455, (int32_t a0, int32_t a1), (a0, a1)) \
    V(UiCall00523E50, 0x00523e50, (int32_t a0, int32_t a1, int32_t a2), (a0, a1, a2)) \
    V(UiCall00412254, 0x00412254, (void), ()) \
    V(UiCall00412228, 0x00412228, (void), ()) \
    V(UiCall00412087, 0x00412087, (void), ()) \
    V(UiCall0041266F, 0x0041266f, (void), ()) \
    V(UiCall00412643, 0x00412643, (void), ()) \
    V(UiCall00412487, 0x00412487, (void), ()) \
    V(UiCall0040C480, 0x0040c480, (int32_t a0), (a0)) \
    V(UiCall00408600, 0x00408600, (int32_t a0), (a0)) \
    V(UiCall00417AA2, 0x00417aa2, (void), ()) \
    V(MenuAction40CD17, 0x0040cd17, (void), ()) \
    V(Call0040CB9F, 0x0040cb9f, (void), ()) \
    V(MenuRedraw, 0x00409622, (void), ()) \
    V(MenuRefresh, 0x0040500d, (void), ()) \
    V(Call004076E2, 0x004076e2, (void), ()) \
    V(StoreCameraState,   0x004c5499, (void *cam), (cam))   /* камера <- текущее состояние игровой камеры */ \
    V(RestoreCameraState, 0x004c536c, (void *cam), (cam))   /* текущее состояние игровой камеры <- cam */ \
    R(void *, FindCameraRecordForFrame, 0x004c61b2, (int frame), (frame)) \
    R(int, FindAutoCamera, 0x004c6740, (void **out), (out))   /* выбирает автокамеру в *out, 0 — не нашлось */ \
    V(InitNewCamera, 0x004c32c1, (void *cam), (cam)) \
    R(uint32_t, LoadIconByName, 0x004ec91e, (const char *name), (name)) \
    V(DrawSprite, 0x0051755e, (int x, int y, uint32_t tex, int a, int b, int c, int d, int e), (x, y, tex, a, b, c, d, e)) \
    V(DrawRect, 0x004d7c46, (float x, float y, float w, float h, uint32_t color), (x, y, w, h, color)) \
    V(GameDrawIcon, 0x004e72f8, (float x, float y, float sx, float sy, uint32_t icon, uint32_t color), (x, y, sx, sy, icon, color)) \
    R(int, GetMarkerYAdjust, 0x004023c9, (int a), (a)) \
    R(int, IsKeyDown, 0x004e383a, (int sc), (sc)) \
    R(int, GetGroundHeight, 0x004dd039, (int *pos), (pos)) \
    V(Call00411A9D, 0x00411a9d, (void), ()) \
    V(Call0040F3DE, 0x0040f3de, (void), ()) \
    V(Call0041AFCA, 0x0041afca, (void), ()) \
    V(Call0050F7B2, 0x0050f7b2, (void), ()) \
    V(Call0050FBF4, 0x0050fbf4, (void), ()) \
    V(P4Call004A3354, 0x004a3354, (void), ()) \
    V(P4Call0041A8CD, 0x0041a8cd, (void), ()) \
    V(P4Call0051AA5B, 0x0051aa5b, (void), ()) \
    V(P4Call004ECADE, 0x004ecade, (void), ()) \
    V(P4Call004D2D85, 0x004d2d85, (int32_t a0), (a0)) \
    V(P4Call0041D89C, 0x0041d89c, (int32_t a0, int32_t a1), (a0, a1)) \
    V(P4Call004CA98D, 0x004ca98d, (int32_t a0, int32_t a1), (a0, a1)) \
    V(P4Call00528293, 0x00528293, (int32_t a0), (a0)) \
    V(P4Call004C032A, 0x004c032a, (int32_t a0), (a0)) \
    V(P4Call004076E2, 0x004076e2, (void), ()) \
    V(P4Call00409CFA, 0x00409cfa, (void), ()) \
    V(P4Call0041074D, 0x0041074d, (void), ()) \
    V(P4Call00411A9D, 0x00411a9d, (void), ()) \
    V(P4Call00415979, 0x00415979, (void), ()) \
    V(G6Call004064B4, 0x004064b4, (int32_t a0, int32_t a1), (a0, a1)) \
    V(G6Call004094E3, 0x004094e3, (void), ()) \
    V(G6Call0050FAB0, 0x0050fab0, (void), ()) \
    V(G6Call004D5FFC, 0x004d5ffc, (void), ()) \
    V(G6Call004D5CE0, 0x004d5ce0, (void), ()) \
    V(G6Call00524398, 0x00524398, (void), ()) \
    V(G6Call00523628, 0x00523628, (void), ()) \
    V(G6Call0041A16C, 0x0041a16c, (void), ()) \
    V(G6Call004D4663, 0x004d4663, (void), ()) \
    V(G6Call0040C5BE, 0x0040c5be, (int32_t a0), (a0)) \
    V(G6Call0050E940, 0x0050e940, (int32_t a0), (a0)) \
    V(G6Call00418119, 0x00418119, (int32_t a0), (a0)) \
    V(G6Call00417CBB, 0x00417cbb, (void), ()) \
    V(G6Call004A2B70, 0x004a2b70, (void), ()) \
    V(G6Call0048BA20, 0x0048ba20, (void), ()) \
    V(G6Call004BA457, 0x004ba457, (void), ()) \
    V(G6Call004BA57A, 0x004ba57a, (void), ()) \
    V(G6Call004BA64D, 0x004ba64d, (void), ()) \
    V(G6Call004D614A, 0x004d614a, (int32_t a0, int32_t a1, int32_t a2, int32_t a3), (a0, a1, a2, a3)) \
    V(G6Call00519D22, 0x00519d22, (int32_t a0), (a0)) \
    V(G6Call00426580, 0x00426580, (int32_t a0), (a0)) \
    V(G6Call00516EB4, 0x00516eb4, (int32_t a0, int32_t a1, int32_t a2), (a0, a1, a2)) \
    V(G6Call00500E1D, 0x00500e1d, (int32_t a0), (a0)) \
    V(G6Call00491360, 0x00491360, (void), ()) \
    V(G6Call004A05FA, 0x004a05fa, (void), ()) \
    V(Call0042486B, 0x0042486b, (int32_t a0, uint32_t a1, int32_t a2, uint32_t a3, int32_t a4), (a0, a1, a2, a3, a4)) \
    R(int32_t, G6Call0041D63B, 0x0041d63b, (int32_t a0, int32_t a1, int32_t a2, int32_t a3), (a0, a1, a2, a3)) \
    R(int32_t, G6Call00523CDA, 0x00523cda, (int32_t a0, int32_t a1, int32_t a2, int32_t a3, int32_t a4), (a0, a1, a2, a3, a4)) \
    V(Call004BF910, 0x004bf910, (uint32_t a0, uint32_t a1, uint32_t a2), (a0, a1, a2)) \
    V(Call005291ED, 0x005291ed, (uint32_t a0, uint32_t a1, uint32_t a2, uint32_t a3), (a0, a1, a2, a3)) \
    V(Call0052B650, 0x0052b650, (uint32_t a0, uint32_t a1, uint32_t a2), (a0, a1, a2)) \
    V(Call004D9596, 0x004d9596, (uint32_t a0, uint32_t a1, uint32_t a2, uint32_t a3), (a0, a1, a2, a3)) \
    V(Call004D94B7, 0x004d94b7, (uint32_t a0, uint32_t a1), (a0, a1)) \
    R(int32_t, Call00524473, 0x00524473, (int32_t a0), (a0)) \
    V(Call004A9F45, 0x004a9f45, (int32_t a0, int32_t a1, int32_t a2, int32_t a3, uint32_t a4), (a0, a1, a2, a3, a4)) \
    R(uint32_t, Call0048F3B4, 0x0048f3b4, (int32_t a0, int32_t a1, int32_t a2, int32_t a3), (a0, a1, a2, a3)) \
    R(uint32_t, Call004EC8A8, 0x004ec8a8, (uint32_t a0), (a0)) \
    V(Call00510784, 0x00510784, (void), ()) \
    V(Call0050FAB0, 0x0050fab0, (void), ()) \
    V(Call004C64BD, 0x004c64bd, (void), ()) \
    V(Call004D3402, 0x004d3402, (void), ()) \
    V(Call004246F0, 0x004246f0, (void), ()) \
    V(Call004C372A, 0x004c372a, (void), ()) \
    V(Call00421A39, 0x00421a39, (void), ()) \
    V(Call0052434A, 0x0052434a, (int32_t a0), (a0)) \
    V(Call004D303A, 0x004d303a, (uint32_t a0, uint32_t a1), (a0, a1)) \
    V(Call005261AD, 0x005261ad, (uint32_t a0, uint32_t a1), (a0, a1)) \
    V(Call00528461, 0x00528461, (uint32_t a0, uint32_t a1), (a0, a1)) \
    V(Call00528982, 0x00528982, (uint32_t a0), (a0)) \
    V(Call00425B12, 0x00425b12, (int32_t a0, int32_t a1, int32_t a2), (a0, a1, a2)) \
    V(Call004D8F30, 0x004d8f30, (uint32_t a0), (a0)) \
    V(CrtFree_0052CB70, 0x0052cb70, (uint32_t a0), (a0)) \
    V(Call004D9663, 0x004d9663, (void), ()) \
    V(Call004C1B6C, 0x004c1b6c, (int32_t a0), (a0)) \
    R(int32_t, Call004EC91E, 0x004ec91e, (const char* a0), (a0)) \
    V(Call0052E180, 0x0052e180, (uint32_t a0), (a0)) \
    V(Call005243EB, 0x005243eb, (void), ()) \
    V(Call004C2042, 0x004c2042, (void), ()) \
    V(Call004C0218, 0x004c0218, (int32_t a0), (a0)) \
    R(int32_t, Call00475A3D, 0x00475a3d, (void *src, void *dst), (src, dst)) \
    V(Call00427757, 0x00427757, (void *m), (m)) \
    V(Call0042793F, 0x0042793f, (void *m, int32_t a1), (m, a1)) \
    V(Call004757D2, 0x004757d2, (void *m), (m)) \
    V(Call00475906, 0x00475906, (void *m), (m)) \
    V(SetCameraPosition, 0x00523c99, (float x, float y, float z), (x, y, z)) \
    V(P46_Fn4228EB, 0x004228eb, (void *node, int32_t a1), (node, a1)) \
    V(P46_Fn42282F, 0x0042282f, (void *node, int32_t a1), (node, a1)) \
    V(P46_Fn4D6354, 0x004d6354, (void), ()) \
    V(P46_Fn4DF024, 0x004df024, (void *p, int32_t a1), (p, a1)) \
    V(P46_Fn51BE3C, 0x0051be3c, (void), ()) \
    V(P58_Fn407E2F, 0x00407e2f, (int32_t a0, int32_t a1, int32_t a2, int32_t a3, void *a4, int32_t a5), (a0, a1, a2, a3, a4, a5)) \
    V(P58_Fn4185D2, 0x004185d2, (uint32_t tbl, int32_t a1, uint32_t tbl2), (tbl, a1, tbl2)) \
    R(int32_t, P58_Fn418675, 0x00418675, (uint32_t tbl, int32_t cur), (tbl, cur)) \
    V(P58_Fn416605, 0x00416605, (void), ()) \
    R(int32_t, P58_Fn416794, 0x00416794, (void), ()) \
    V(P58_Fn51763A, 0x0051763a, (const char *a0, int32_t a1), (a0, a1)) \
    V(P58_Fn4AA4EA, 0x004aa4ea, (int32_t a0, int32_t a1, int32_t a2, int32_t a3, void *a4, int32_t a5), (a0, a1, a2, a3, a4, a5)) \
    V(P58_Fn506C96, 0x00506c96, (void *a0, int32_t a1, int32_t a2, int32_t a3, int32_t a4, int32_t a5), (a0, a1, a2, a3, a4, a5)) \
    V(P58_Fn40CFDF, 0x0040cfdf, (int32_t x, int32_t y, uint32_t tbl, const char *name, int32_t a4), (x, y, tbl, name, a4)) \
    V(P58_Fn406875, 0x00406875, (void *a0), (a0)) \
    V(P58_Fn413E37, 0x00413e37, (void), ())

#ifdef RE_HOOK_BUILD
#  define UNPORTED_V(name, addr, params, args) \
     static void (__cdecl * const name) params __attribute__((unused)) = (void (__cdecl *) params)(uintptr_t)(addr);
#  define UNPORTED_R(ret, name, addr, params, args) \
     static ret (__cdecl * const name) params __attribute__((unused)) = (ret (__cdecl *) params)(uintptr_t)(addr);
#else
#  define UNPORTED_V(name, addr, params, args)      void name params;
#  define UNPORTED_R(ret, name, addr, params, args) ret name params;
#endif
UNPORTED_LIST(UNPORTED_V, UNPORTED_R)

/* Оригинальные функции с `ret N` (stdcall): вызывать как __stdcall (не в списке выше). Поиск — tools/gen_stdcall.py. */
#ifdef RE_HOOK_BUILD
static void (__stdcall * const G6Call0041F57D)(int32_t, int32_t, int32_t) __attribute__((unused)) = (void (__stdcall *)(int32_t, int32_t, int32_t))(uintptr_t)0x0041f57d;
#else
void G6Call0041F57D(int32_t a0, int32_t a1, int32_t a2);
#endif

/* 0041f4a1: stdcall, 4 аргумента (ret 0x10). */
#ifdef RE_HOOK_BUILD
static void (__stdcall * const P46Call0041F4A1)(int32_t, int32_t, int32_t, void *) __attribute__((unused)) = (void (__stdcall *)(int32_t, int32_t, int32_t, void *))(uintptr_t)0x0041f4a1;
#else
void P46Call0041F4A1(int32_t a0, int32_t a1, int32_t a2, void *a3);
#endif

#include "ported31.h"
