/* v2.14: тест ввода без окна OpenGL и без файлов игры (driver --inputtest, ctest «inputtest», в CI macOS/Linux).
   Проверяет: (1) тест и разбор событий идут в главном потоке процесса (macOS: pthread_main_np — события Cocoa приходят
   только туда); (2) событие SDL_KEYDOWN/KEYUP, вставленное SDL_PushEvent, проходит разбор событий игры
   (plat_pump_messages) и попадает в GetDeviceState как DIK — даже если отпущено до опроса (защёлка);
   (3) Cmd+Enter / Alt+Enter не доходит до игры (переключение полного экрана); (4) стрелки/пробел дают биты езды
   P36_GetPadButtons; (5) вписывание кадра 640×480 в буфер 1920×1080 / 2560×1600 (pillarbox/letterbox при RE_ASPECT=4:3);
   (6) v2.15 Hor+: S для 16:9/16:10/21:9/32:9/портрета, мышь в меню (640×480 по центру), математика проекции re_aspect_selftest.
   Не проверяет реальную клавиатуру macOS (нужен человек: RE_INPUTDBG=1 → driver_input.log). */
#include "../platform/plat.h"
#include "../game/ported34.h"
#include "../game/ported36.h"
#include "../game/aspect.h"
#include <SDL.h>
#include <stdio.h>
#include <string.h>
#define CHK(c) do { if (!(c)) { printf("FAIL %s:%d %s\n", __FILE__, __LINE__, #c); return 1; } } while (0)
void plat_input_enable(int on);
void plat_input_fill_keys(uint8_t *k);
static void push_key(SDL_Scancode sc, int down, Uint16 mod) {
    SDL_Event e; memset(&e, 0, sizeof e);
    e.type = down ? SDL_KEYDOWN : SDL_KEYUP; e.key.state = down ? SDL_PRESSED : SDL_RELEASED;
    e.key.keysym.scancode = sc; e.key.keysym.sym = SDL_GetKeyFromScancode(sc); e.key.keysym.mod = mod;
    SDL_PushEvent(&e);
}
int re_input_test(void) {
    int mt = plat_is_main_thread();
    printf("inputtest: главный поток %d (SDL %s)\n", mt, SDL_GetPlatform());
#if defined(__APPLE__) || defined(__linux__)
    CHK(mt == 1);
#endif
    CHK(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS) == 0);
    SDL_Window *w = SDL_CreateWindow("inputtest", 0, 0, 64, 64, 0);   /* без OpenGL: драйвер dummy */
    (void)w;
    plat_input_enable(1);
    uint8_t k[256];
    /* (2) нажали и отпустили до опроса — игра всё равно видит клавишу один раз */
    push_key(SDL_SCANCODE_LEFT, 1, 0); push_key(SDL_SCANCODE_LEFT, 0, 0);
    plat_pump_messages();
    memset(k, 0, sizeof k); plat_input_fill_keys(k); CHK(k[0xcb] == 0x80);
    memset(k, 0, sizeof k); plat_input_fill_keys(k); CHK(k[0xcb] == 0);
    push_key(SDL_SCANCODE_A, 1, 0); push_key(SDL_SCANCODE_SPACE, 1, 0); push_key(SDL_SCANCODE_APOSTROPHE, 1, 0);
    plat_pump_messages();
    memset(k, 0, sizeof k); plat_input_fill_keys(k); CHK(k[0x1e] == 0x80 && k[0x39] == 0x80 && k[0x28] == 0x80);
    /* (3) Cmd+Enter / Alt+Enter */
    push_key(SDL_SCANCODE_RETURN, 1, KMOD_LGUI); push_key(SDL_SCANCODE_RETURN, 1, KMOD_LALT); plat_pump_messages();
    memset(k, 0, sizeof k); plat_input_fill_keys(k); CHK(k[0x1c] == 0);
    push_key(SDL_SCANCODE_RETURN, 1, 0); plat_pump_messages();
    memset(k, 0, sizeof k); plat_input_fill_keys(k); CHK(k[0x1c] == 0x80);
    /* Diagnostic capture chords must not reach the game's D key (DIK 0x20). */
    push_key(SDL_SCANCODE_D, 1, KMOD_GUI | KMOD_SHIFT);
    push_key(SDL_SCANCODE_D, 0, KMOD_GUI | KMOD_SHIFT);
    push_key(SDL_SCANCODE_D, 1, KMOD_CTRL | KMOD_SHIFT);
    push_key(SDL_SCANCODE_D, 0, KMOD_CTRL | KMOD_SHIFT);
    plat_pump_messages();
    memset(k, 0, sizeof k); plat_input_fill_keys(k); CHK(k[0x20] == 0);
    push_key(SDL_SCANCODE_D, 1, 0); push_key(SDL_SCANCODE_D, 0, 0);
    plat_pump_messages();
    memset(k, 0, sizeof k); plat_input_fill_keys(k); CHK(k[0x20] == 0x80);
    /* (4) биты езды */
    uint32_t m = 0;
    memset(P34_Keys, 0, 256); memset(P36_KeyCfg, 0, 20);
    P34_Keys[0xc8] = 0x80; P36_GetPadButtons(&m); CHK(m == 2);
    P34_Keys[0xc8] = 0; P34_Keys[0xd0] = 0x80; P36_GetPadButtons(&m); CHK(m == 1);
    P34_Keys[0xd0] = 0; P34_Keys[0xcb] = 0x80; P34_Keys[0x39] = 0x80; P36_GetPadButtons(&m); CHK(m == (8 | 0x20));
    P34_Keys[0xcb] = 0; P34_Keys[0x39] = 0; P34_Keys[0xcd] = 0x80; P36_GetPadButtons(&m); CHK(m == 4);
    memset(P34_Keys, 0, 256);
    /* (5) вписывание кадра (без GL: только арифметика) */
    int lx, ly;
    plat_render_set_aspect("4:3");                                                      /* v2.14: оригинал, полосы */
    plat_render_set_logical(640, 480); plat_render_set_drawable(1920, 1080);
    CHK(plat_view_extra() == 0);
    CHK(plat_render_to_logical(240.0, 0.0, &lx, &ly) && lx == 0 && ly == 0);           /* полоса слева 240 px */
    CHK(!plat_render_to_logical(100.0, 500.0, &lx, &ly));
    CHK(plat_render_to_logical(1679.0, 1079.0, &lx, &ly) && lx == 639 && ly == 479);
    plat_render_set_drawable(2560, 1600);                                               /* 4:3 в 16:10 — 2133×1600 */
    CHK(plat_render_to_logical(1280.0, 800.0, &lx, &ly) && lx == 320 && ly == 240);
    /* (6) v2.15 Hor+ (RE_ASPECT=auto): вертикаль 480, ширина 480·аспект; меню/мышь — в 640×480 по центру */
    { int r = re_aspect_selftest(); if (r) printf("re_aspect_selftest: проверка %d\n", r); CHK(r == 0); }
    plat_render_set_aspect("auto");
    plat_render_set_drawable(1920, 1080); CHK(plat_view_extra() == 107);                  /* 16:9: 854×480 */
    CHK(plat_render_to_logical(960.0, 540.0, &lx, &ly) && lx == 320 && ly == 240);
    CHK(!plat_render_to_logical(100.0, 540.0, &lx, &ly) && lx < 0);                     /* 3D/HUD вне 640 — не меню */
    plat_render_set_drawable(2560, 1600); CHK(plat_view_extra() == 64);                   /* 16:10: 768×480 */
    plat_render_set_drawable(3440, 1440); CHK(plat_view_extra() == 253);                  /* 21:9 */
    plat_render_set_drawable(5120, 1440); CHK(plat_view_extra() == 533);                  /* 32:9 */
    plat_render_set_drawable(1080, 1920); CHK(plat_view_extra() == 0);                    /* портрет: letterbox 4:3 */
    CHK(plat_render_to_logical(540.0, 960.0, &lx, &ly) && lx == 320 && ly == 240);
    CHK(!plat_render_to_logical(540.0, 100.0, &lx, &ly));                                /* полоса сверху */
    plat_render_set_aspect("21:9"); plat_render_set_drawable(1920, 1080); CHK(plat_view_extra() == 240);   /* 1120×480 в 16:9 — letterbox */
    CHK(!plat_render_to_logical(960.0, 10.0, &lx, &ly));
    plat_render_set_aspect(NULL);
    SDL_Quit();
    printf("inputtest: OK\n");
    return 0;
}
