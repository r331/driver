/* Вызовы функций Game.exe, которые ещё не перенесены.
   RE_HOOK_BUILD: вызов по адресу в оригинальном Game.exe (__cdecl).
   Нативная сборка: заглушка из platform/native/stubs.c, пишет в лог «not ported: ИМЯ (адрес)».
   Список — X-макросы: UNPORTED_V(имя, адрес, (параметры), (аргументы)) для void,
                       UNPORTED_R(тип, имя, адрес, (параметры), (аргументы)) для остальных (заглушка возвращает 0). */
#pragma once
#include "gvar.h"

#define UNPORTED_LIST(V, R) \
    V(MenuRefresh, 0x0040500d, (void), ()) \
    V(StoreCameraState,   0x004c5499, (void *cam), (cam))   /* камера <- текущее состояние игровой камеры */ \
    V(RestoreCameraState, 0x004c536c, (void *cam), (cam))   /* текущее состояние игровой камеры <- cam */ \
    R(void *, FindCameraRecordForFrame, 0x004c61b2, (int frame), (frame)) \
    R(int, FindAutoCamera, 0x004c6740, (void **out), (out))   /* выбирает автокамеру в *out, 0 — не нашлось */ \
    V(InitNewCamera, 0x004c32c1, (void *cam), (cam)) \
    R(uint32_t, LoadIconByName, 0x004ec91e, (const char *name), (name)) \
    V(DrawSprite, 0x0051755e, (int x, int y, uint32_t tex, int a, int b, int c, int d, int e), (x, y, tex, a, b, c, d, e)) \
    V(DrawRect, 0x004d7c46, (float x, float y, float w, float h, uint32_t color), (x, y, w, h, color)) \
    V(DrawIcon, 0x004e72f8, (float x, float y, float sx, float sy, uint32_t icon, uint32_t color), (x, y, sx, sy, icon, color)) \
    R(int, GetMarkerYAdjust, 0x004023c9, (int a), (a)) \
    R(int, IsKeyDown, 0x004e383a, (int sc), (sc)) \
    R(int, GetGroundHeight, 0x004dd039, (int *pos), (pos)) \
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
