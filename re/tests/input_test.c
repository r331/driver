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
#include "../game/ported98.h"
#include "../game/ported100.h"
#include "../game/ported103.h"
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
static void pad_sample(uint8_t *k) {
    SDL_JoystickUpdate(); plat_pump_messages();
    memset(k, 0, 256); plat_input_fill_keys(k);
}
static int rumble_calls;
static Uint16 rumble_low, rumble_high;
/* v2.32: какое значение должен вернуть колбэк Rumble виртуального джойстика, чтобы SDL_JoystickRumble вернул 0.
   SDL2 Classic: 0 = успех. sdl2-compat (по крайней мере 2.32.70 и 2.32.74, VirtualJoystick_Rumble) передаёт
   int-результат колбэка в SDL3 как bool без преобразования, т.е. «успех» = 1. Вместо списка версий —
   однократный зонд на том же виртуальном джойстике до того, как его увидит игра (реальное железо этот
   адаптер не использует). Отдельный пробный джойстик не годится: в sdl2-compat после его отключения
   индексы устройств расходятся с игрой. */
static int rumble_ok = -1, rumble_probe = -1;
static int SDLCALL record_rumble(void *unused, Uint16 low, Uint16 high) {
    (void)unused;
    if (rumble_probe >= 0) return rumble_probe;   /* зонд: не считается вызовом игры */
    rumble_calls++; rumble_low = low; rumble_high = high;
    return rumble_ok > 0 ? 1 : 0;
}
static void probe_rumble_result(SDL_Joystick *joy) {
    /* разные силы: SDL пропускает вызов драйвера при повторе тех же значений */
    int r0, r1 = -2;
    rumble_probe = 0; r0 = SDL_JoystickRumble(joy, 1000, 1000, 50);
    if (r0 == 0) rumble_ok = 0;
    else { rumble_probe = 1; r1 = SDL_JoystickRumble(joy, 2000, 2000, 50); rumble_ok = r1 == 0 ? 1 : -1; }
    rumble_probe = rumble_ok > 0; SDL_JoystickRumble(joy, 0, 0, 0); rumble_probe = -1;
    printf("inputtest: зонд вибрации: колбэк 0 -> %d, 1 -> %d; успех колбэка = %d%s\n", r0, r1, rumble_ok,
           rumble_ok == 1 ? " (инверсия sdl2-compat)" : rumble_ok < 0 ? " (зонд не удался)" : "");
}
static int test_damage_rumble(uint8_t *k) {
    p99_car_t saved = P99_Cars[0];
    int active = P31_Active, demo = G6_00B87EA0, alternate = G6_00B87EAC;
    int pct = P103_DmgPct, invulnerable = MenuOptBDFA4C, strong = MenuOptBDFA58;
    P31_Active = 1; G6_00B87EA0 = G6_00B87EAC = 0;
    P103_DmgPct = 100; MenuOptBDFA4C = MenuOptBDFA58 = 0;
    memset(&P99_Cars[0], 0, sizeof P99_Cars[0]);
    int32_t direction[3] = {0, 0, 4096};
    int count = rumble_calls;
    CHK(P103_CarDamage((uint8_t *)&P99_Cars[0], direction, 0x800) == 0);
    CHK(rumble_calls == count);
    uint8_t npc[0x148]; memset(npc, 0, sizeof npc); npc[0] = 1;
    CHK(P103_CarDamage(npc, direction, 0x10000) == 1); CHK(rumble_calls == count);
    MenuOptBDFA4C = 1;
    CHK(P103_CarDamage((uint8_t *)&P99_Cars[0], direction, 0x10000) == 0);
    CHK(rumble_calls == count); MenuOptBDFA4C = 0;
    CHK(P103_CarDamage((uint8_t *)&P99_Cars[0], direction, 0x10000) == 1);
    CHK(rumble_calls == count + 1 && rumble_low > 0 && rumble_high > 0);
    Uint16 medium = rumble_low;
    P103_CarDamage((uint8_t *)&P99_Cars[0], direction, 0x1000);
    CHK(rumble_calls == count + 1 && rumble_low == medium);
    P103_CarDamage((uint8_t *)&P99_Cars[0], direction, 0x40000);
    CHK(rumble_calls == count + 2 && rumble_low > medium && rumble_low <= 60000);
    /* Pause cancels an ongoing pulse, then the scenery damage path can rumble. */
    G6_00B87EFC = 1; pad_sample(k); CHK(rumble_low == 0 && rumble_high == 0);
    count = rumble_calls;
    P35_DamageRumble((uint8_t *)&P99_Cars[0], 100); CHK(rumble_calls == count);
    G6_00B87EFC = 0; pad_sample(k);
    int32_t a[11] = {0}, b[3] = {0, 0, 4096};
    P100_CarHit((uint8_t *)&P99_Cars[0], a, b, 0x20000);
    CHK(rumble_calls == count + 1 && rumble_low > 0);
    SDL_Event e; memset(&e, 0, sizeof e); e.type = SDL_WINDOWEVENT;
    e.window.event = SDL_WINDOWEVENT_FOCUS_LOST; SDL_PushEvent(&e); pad_sample(k);
    CHK(rumble_low == 0 && rumble_high == 0);
    count = rumble_calls;
    P35_DamageRumble((uint8_t *)&P99_Cars[0], 100); CHK(rumble_calls == count);
    e.window.event = SDL_WINDOWEVENT_FOCUS_GAINED; SDL_PushEvent(&e); pad_sample(k);
    P36_PadMode = 2; P35_DamageRumble((uint8_t *)&P99_Cars[0], 100);
    CHK(rumble_calls == count); P36_PadMode = 0;
    SDL_setenv("RE_RUMBLE", "0", 1); P35_DamageRumble((uint8_t *)&P99_Cars[0], 100);
    CHK(rumble_calls == count); SDL_setenv("RE_RUMBLE", "1", 1);
    P99_Cars[0] = saved; P31_Active = active; G6_00B87EA0 = demo; G6_00B87EAC = alternate;
    P103_DmgPct = pct; MenuOptBDFA4C = invulnerable; MenuOptBDFA58 = strong;
    return 0;
}
static int test_gamepad(void) {
    uint8_t k[256]; uint32_t mask;
    SDL_VirtualJoystickDesc descriptor; memset(&descriptor, 0, sizeof descriptor);
    descriptor.version = SDL_VIRTUAL_JOYSTICK_DESC_VERSION;
    descriptor.type = SDL_JOYSTICK_TYPE_GAMECONTROLLER;
    descriptor.naxes = SDL_CONTROLLER_AXIS_MAX; descriptor.nbuttons = SDL_CONTROLLER_BUTTON_MAX;
    descriptor.axis_mask = (1u << SDL_CONTROLLER_AXIS_MAX) - 1;
    descriptor.button_mask = (1u << SDL_CONTROLLER_BUTTON_MAX) - 1;
    descriptor.name = "Driver rumble test controller"; descriptor.Rumble = record_rumble;
    int index = SDL_JoystickAttachVirtualEx(&descriptor);
    CHK(index >= 0 && SDL_IsGameController(index));
    SDL_Joystick *joy = SDL_JoystickOpen(index); CHK(joy != NULL);
    probe_rumble_result(joy); CHK(rumble_ok >= 0);
    SDL_JoystickSetVirtualAxis(joy, SDL_CONTROLLER_AXIS_TRIGGERLEFT, -32768);
    SDL_JoystickSetVirtualAxis(joy, SDL_CONTROLLER_AXIS_TRIGGERRIGHT, -32768);
    G6_00B87EFC = 1;
    pad_sample(k); CHK(k[0xc8] == 0 && k[0x1c] == 0);
    SDL_JoystickSetVirtualAxis(joy, SDL_CONTROLLER_AXIS_LEFTX, 22000);
    pad_sample(k); CHK(k[0xcd] == 0x80 && k[0xcb] == 0);
    SDL_JoystickSetVirtualAxis(joy, SDL_CONTROLLER_AXIS_LEFTX, 0);
    SDL_JoystickSetVirtualButton(joy, SDL_CONTROLLER_BUTTON_A, 1);
    pad_sample(k); CHK(k[0x1c] == 0x80 && k[0x01] == 0);
    /* Entering gameplay with A still held must not apply the handbrake. */
    memset(P36_KeyCfg, 0, sizeof P36_KeyCfg);
    P36_KeyCfg[4] = 0x2c; P36_KeyCfg[5] = 0x2d;
    P36_KeyCfg[6] = 0x28; P36_KeyCfg[7] = 0x35;
    P36_KeyCfg[8] = 0x1f; P36_KeyCfg[9] = 0x1c;
    P36_KeyCfg[10] = 0x11; P36_KeyCfg[13] = 0x20; P36_KeyCfg[15] = 0x23;
    P98_KeyMode = 0x02; G6_00B87EFC = 0;
    pad_sample(k); CHK(k[0x1c] == 0);
    SDL_JoystickSetVirtualButton(joy, SDL_CONTROLLER_BUTTON_A, 0); pad_sample(k);
    SDL_JoystickSetVirtualAxis(joy, SDL_CONTROLLER_AXIS_LEFTX, -24000);
    SDL_JoystickSetVirtualAxis(joy, SDL_CONTROLLER_AXIS_TRIGGERRIGHT, 32767);
    pad_sample(k);
    memcpy(P34_Keys, k, 256); P36_PadMode = 0; P36_GetPadButtons(&mask);
    CHK(mask == (8 | 2));
    CHK(test_damage_rumble(k) == 0);
    SDL_JoystickSetVirtualAxis(joy, SDL_CONTROLLER_AXIS_LEFTX, 3000);
    SDL_JoystickSetVirtualAxis(joy, SDL_CONTROLLER_AXIS_TRIGGERRIGHT, -32768);
    SDL_JoystickSetVirtualAxis(joy, SDL_CONTROLLER_AXIS_TRIGGERLEFT, 32767);
    SDL_JoystickSetVirtualButton(joy, SDL_CONTROLLER_BUTTON_A, 1);
    SDL_JoystickSetVirtualButton(joy, SDL_CONTROLLER_BUTTON_X, 1);
    SDL_JoystickSetVirtualButton(joy, SDL_CONTROLLER_BUTTON_LEFTSTICK, 1);
    pad_sample(k); memcpy(P34_Keys, k, 256); P36_GetPadButtons(&mask);
    CHK(mask == (1 | 0x20 | 0x40 | 0x100));
    /* Respect changed keyboard bindings, preserve simultaneous keyboard input. */
    P36_KeyCfg[9] = 0x24; pad_sample(k); CHK(k[0x24] == 0x80 && k[0x1c] == 0);
    SDL_JoystickSetVirtualButton(joy, SDL_CONTROLLER_BUTTON_Y, 1);
    SDL_JoystickSetVirtualButton(joy, SDL_CONTROLLER_BUTTON_START, 1);
    pad_sample(k); CHK(k[0x02] == 0x80 && k[0x01] == 0x80 && k[0x1c] == 0);
    k[0x21] = 0x80; plat_input_fill_keys(k); CHK(k[0x21] == 0x80);
    SDL_JoystickClose(joy); CHK(SDL_JoystickDetachVirtual(index) == 0);
    pad_sample(k); CHK(k[0x24] == 0 && k[0x35] == 0 && k[0x02] == 0 && k[0x01] == 0);
    /* Reconnection and a complete short press between game polls. */
    index = SDL_JoystickAttachVirtual(SDL_JOYSTICK_TYPE_GAMECONTROLLER,
                                      SDL_CONTROLLER_AXIS_MAX, SDL_CONTROLLER_BUTTON_MAX, 0);
    CHK(index >= 0); joy = SDL_JoystickOpen(index); CHK(joy != NULL);
    G6_00B87EFC = 1; pad_sample(k);
    SDL_JoystickSetVirtualButton(joy, SDL_CONTROLLER_BUTTON_A, 1);
    SDL_JoystickUpdate(); plat_pump_messages();
    SDL_JoystickSetVirtualButton(joy, SDL_CONTROLLER_BUTTON_A, 0);
    pad_sample(k); CHK(k[0x1c] == 0x80);
    pad_sample(k); CHK(k[0x1c] == 0);
    SDL_JoystickSetVirtualButton(joy, SDL_CONTROLLER_BUTTON_A, 1); pad_sample(k);
    SDL_Event event; memset(&event, 0, sizeof event); event.type = SDL_WINDOWEVENT;
    event.window.event = SDL_WINDOWEVENT_FOCUS_LOST; SDL_PushEvent(&event);
    pad_sample(k); CHK(k[0x1c] == 0);
    SDL_JoystickSetVirtualButton(joy, SDL_CONTROLLER_BUTTON_A, 0);
    event.window.event = SDL_WINDOWEVENT_FOCUS_GAINED; SDL_PushEvent(&event); pad_sample(k);
    SDL_JoystickClose(joy); CHK(SDL_JoystickDetachVirtual(index) == 0); pad_sample(k);
    G6_00B87EFC = 0; memset(P34_Keys, 0, 256); memset(P36_KeyCfg, 0, sizeof P36_KeyCfg);
    return 0;
}
int re_input_test(void) {
    int mt = plat_is_main_thread();
    SDL_version version; SDL_GetVersion(&version);
    printf("inputtest: главный поток %d (SDL %s %u.%u.%u, %s)\n", mt, SDL_GetPlatform(),
           version.major, version.minor, version.patch, SDL_GetRevision());
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
    CHK(test_gamepad() == 0);
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
    plat_input_enable(0);
    SDL_Quit();
    printf("inputtest: OK\n");
    return 0;
}
