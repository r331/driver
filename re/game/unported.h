/* Вызовы функций Game.exe, которые ещё не перенесены.
   RE_HOOK_BUILD: вызов по адресу в оригинальном Game.exe (__cdecl).
   Нативная сборка: заглушка из platform/native/stubs.c, пишет в лог «not ported: ИМЯ (адрес)».
   Список — X-макросы: UNPORTED_V(имя, адрес, (параметры), (аргументы)) для void,
                       UNPORTED_R(тип, имя, адрес, (параметры), (аргументы)) для остальных (заглушка возвращает 0). */
#pragma once
#include "gvar.h"

#define UNPORTED_LIST(V, R) \
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
    V(G6Call0048A239, 0x0048a239, (int32_t a0, int32_t a1), (a0, a1)) \
    V(G6Call00489F50, 0x00489f50, (int32_t a0, int32_t a1, int32_t a2), (a0, a1, a2)) \
    V(G6Call00422AE7, 0x00422ae7, (void), ()) \
    V(G6Call0041F57D, 0x0041f57d, (int32_t a0, int32_t a1, int32_t a2), (a0, a1, a2)) \
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
    V(Call004C372A, 0x004c372a, (void), ()) \
    V(Call0052434A, 0x0052434a, (int32_t a0), (a0)) \
    V(Call004D303A, 0x004d303a, (uint32_t a0, uint32_t a1), (a0, a1)) \
    V(Call005261AD, 0x005261ad, (uint32_t a0, uint32_t a1), (a0, a1)) \
    V(Call00528461, 0x00528461, (uint32_t a0, uint32_t a1), (a0, a1)) \
    V(Call00528982, 0x00528982, (uint32_t a0), (a0)) \
    V(Call00425B12, 0x00425b12, (int32_t a0, int32_t a1, int32_t a2), (a0, a1, a2)) \
    V(Call004D8F30, 0x004d8f30, (uint32_t a0), (a0)) \
    V(SetDirectorMode_004C875D, 0x004c875d, (int32_t a0, int32_t a1, int32_t a2), (a0, a1, a2)) \
    V(SetCameraPosition, 0x00523c99, (float x, float y, float z), (x, y, z))

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
