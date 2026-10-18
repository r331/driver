/* SDL-вариант DirectInput: учёт вызовов без устройства (клавиатуру из SDL подключим вместе с главным циклом). */
#include "../plat.h"
#include <SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
static void dbg_keys(const uint8_t *k);   /* v2.14: RE_INPUTDBG */
static int32_t g_jx, g_jy, g_poll;
static int g_rel, g_unacq, g_evt, g_kind = -1, g_fail;
void plat_di_release(void *o) { if (o) g_rel++; }
void plat_di_unacquire(void *d) { if (d) g_unacq++; }
int32_t plat_di_set_format(void *d, int kind) { if (!d) return -1; g_kind = kind; return 0; }
static uint32_t g_fmask, g_caps; static int g_njoy, g_ndev, g_ncoop, g_nprop, g_nqry, g_ntok;
static char g_tok[64];
#define FAIL(b) (g_fmask & (1u << (b)))
int32_t plat_di_acquire(void *d) { return (d && !FAIL(8)) ? 0 : -1; }
void plat_vt_poll(void);   /* v2.08: plat_sys.c — RE_FIXED_DT: опрос ввода двигает виртуальные часы (ожидание клавиши/таймера) */
int32_t plat_di_get_state(void *d, uint32_t size, void *buf) {
  plat_vt_poll();
    { static int tr = -1, n = 0; if (tr < 0) tr = getenv("RE_TRACE_KEYS") != NULL;
      if (tr && n < 400 && (n++ % 40) == 0) fprintf(stderr, "[keys] get_state dev=%p size=0x%x кадр %d\n", d, size, plat_frame_no()); }
    if (!d || g_fail) return -1;
    memset(buf, 0, size);                /* «ничего не нажато»; v2.03: в игре — клавиатура SDL/геймпад/сценарий RE_KEYS */
    if (size == 0x100) { plat_input_fill_keys((uint8_t *)buf); dbg_keys((const uint8_t *)buf); }
    if (size == 0x50) { memcpy(buf, &g_jx, 4); memcpy((char *)buf + 4, &g_jy, 4); }   /* DIJOYSTATE: lX, lY */
    return 0;
}
int32_t plat_di_poll(void *d) { return d ? g_poll : -1; }
void plat_di_stub_joy(int32_t x, int32_t y, int32_t rc) { g_jx = x; g_jy = y; g_poll = rc; }
void plat_event_close(void *h) { if (h) g_evt++; }
int plat_di_stub_counts(int *r, int *u, int *e, int *k) { *r = g_rel; *u = g_unacq; *e = g_evt; *k = g_kind; return 1; }
void plat_di_stub_fail_state(int on) { g_fail = on; }
/* --- Force Feedback: учёт вызовов --- */
static int g_enum_fail, g_ef_created, g_ef_ckind = -1, g_ef_sets, g_ef_skind = -1; static int32_t g_ef_dx, g_ef_dy, g_ef_mag;
static const uint8_t k_const_guid[16] = { 0x20,0x1c,0x54,0x13,0x33,0x8e,0xd0,0x11,0x9a,0xd0,0x00,0xa0,0xc9,0xa0,0x6e,0x35 };
int32_t plat_di_enum_effect(void *d, uint8_t guid[16]) { if (!d || g_enum_fail) return -1; memcpy(guid, k_const_guid, 16); return 0; }
int32_t plat_di_create_effect(void *d, int kind, const uint8_t *guid, void **out) {
    if (!d || !guid || !out) return -1;
    static char tok[2]; g_ef_created++; g_ef_ckind = kind; *out = &tok[kind & 1]; return 0;
}
int32_t plat_di_set_effect(void *e, int kind, int32_t dx, int32_t dy, int32_t mag) {
    if (!e) return -1;
    g_ef_sets++; g_ef_skind = kind; g_ef_dx = dx; g_ef_dy = dy; g_ef_mag = mag; return 0;
}
int plat_di_stub_effects(int *c, int *ck, int *s, int *sk, int32_t *dx, int32_t *dy, int32_t *mag) {
    *c = g_ef_created; *ck = g_ef_ckind; *s = g_ef_sets; *sk = g_ef_skind; *dx = g_ef_dx; *dy = g_ef_dy; *mag = g_ef_mag; return 1;
}
void plat_di_stub_fail_enum(int on) { g_enum_fail = on; }
/* --- создание и настройка (InitInput) --- */
static void *tok(void) { return g_ntok < 64 ? &g_tok[g_ntok++] : NULL; }
void plat_di_stub_setup(int joysticks, uint32_t caps_flags, uint32_t fail_mask) { g_njoy = joysticks; g_caps = caps_flags; g_fmask = fail_mask; g_ndev = g_ncoop = g_nprop = g_nqry = 0; g_ntok = 0; }
int plat_di_stub_init_stats(int *dv, int *co, int *pr, int *qy) { *dv = g_ndev; *co = g_ncoop; *pr = g_nprop; *qy = g_nqry; return 1; }
void *plat_di_create(void *hinst, uint32_t version) { (void)hinst; (void)version; return FAIL(0) ? NULL : tok(); }
void *plat_di_create_sys_device(void *di, int kind) { (void)kind; if (!di || FAIL(1)) return NULL; g_ndev++; return tok(); }
void *plat_di_create_device(void *di, const void *guid) { if (!di || !guid || FAIL(2)) return NULL; g_ndev++; return tok(); }
void *plat_di_query_device2(void *dev) { if (!dev || FAIL(3)) return NULL; g_nqry++; return tok(); }
int32_t plat_di_set_coop(void *dev, void *hwnd, uint32_t flags) { (void)hwnd; (void)flags; if (!dev || FAIL(4)) return -1; g_ncoop++; return 0; }
int32_t plat_di_set_event(void *dev, void *ev) { return (dev && ev && !FAIL(5)) ? 0 : -1; }
int32_t plat_di_set_prop(void *dev, int prop, uint32_t obj, uint32_t how, int32_t a, int32_t b) { (void)prop; (void)obj; (void)how; (void)a; (void)b; if (!dev || FAIL(6)) return -1; g_nprop++; return 0; }
int32_t plat_di_get_caps_flags(void *dev, uint32_t *flags) { if (!dev || FAIL(7)) return -1; *flags = g_caps; return 0; }
int32_t plat_di_enum_joysticks(void *di, plat_di_joy_cb cb) {
    if (!di) return -1;
    for (int i = 0; i < g_njoy; i++) {
        uint32_t inst[0x20]; memset(inst, 0, sizeof inst); inst[1] = 0x1000u + (uint32_t)i; inst[9] = (i == 1) ? 0x0404u : 0x0204u;   /* dwDevType +0x24: подтип в байте 1 */
        if (!cb(inst, di)) break;
    }
    return 0;
}
void *plat_event_create(void) { return FAIL(9) ? NULL : tok(); }

/* ===== v2.03: ввод SDL → DirectInput-клавиатура (только игра, plat_input_enable(1) из platform/native/main.c) =====
   GetDeviceState(0x100): 256 байт DIK, 0x80 — нажата. Источники: SDL_GetKeyboardState (таблица SDL_Scancode → DIK),
   первый SDL_GameController (крестовина/левый стик → стрелки, A/Start → RETURN, B/Back → ESCAPE, X → SPACE),
   сценарий RE_KEYS="кадр:клавиша[,…]" — клавиша нажата с кадра N (plat_frame_no) RE_KEYS_HOLD кадров (по умолчанию 2).
   Клавиша: имя (UP DOWN LEFT RIGHT RETURN ENTER ESC ESCAPE SPACE TAB BACK F1..F12 A..Z 0..9 LSHIFT RSHIFT LCTRL RCTRL LALT)
   или номер DIK (0x1c / 28). Буферизованный ввод (GetDeviceData) игра не использует (перенос 004e417f — только GetDeviceState). */
static int g_in_on;
void plat_input_enable(int on) {
    g_in_on = on;
    if (on && SDL_WasInit(SDL_INIT_VIDEO) && !SDL_WasInit(SDL_INIT_GAMECONTROLLER)) SDL_InitSubSystem(SDL_INIT_GAMECONTROLLER);
}
static const struct { const char *n; uint8_t dik; } k_names[] = {
    {"ESC",0x01},{"ESCAPE",0x01},{"1",0x02},{"2",0x03},{"3",0x04},{"4",0x05},{"5",0x06},{"6",0x07},{"7",0x08},{"8",0x09},{"9",0x0a},{"0",0x0b},
    {"MINUS",0x0c},{"EQUALS",0x0d},{"BACK",0x0e},{"BACKSPACE",0x0e},{"TAB",0x0f},
    {"Q",0x10},{"W",0x11},{"E",0x12},{"R",0x13},{"T",0x14},{"Y",0x15},{"U",0x16},{"I",0x17},{"O",0x18},{"P",0x19},
    {"LBRACKET",0x1a},{"RBRACKET",0x1b},{"RETURN",0x1c},{"ENTER",0x1c},{"LCTRL",0x1d},
    {"A",0x1e},{"S",0x1f},{"D",0x20},{"F",0x21},{"G",0x22},{"H",0x23},{"J",0x24},{"K",0x25},{"L",0x26},
    {"SEMICOLON",0x27},{"APOSTROPHE",0x28},{"GRAVE",0x29},{"LSHIFT",0x2a},{"BACKSLASH",0x2b},
    {"Z",0x2c},{"X",0x2d},{"C",0x2e},{"V",0x2f},{"B",0x30},{"N",0x31},{"M",0x32},{"COMMA",0x33},{"PERIOD",0x34},{"SLASH",0x35},
    {"RSHIFT",0x36},{"LALT",0x38},{"SPACE",0x39},{"CAPSLOCK",0x3a},
    {"F1",0x3b},{"F2",0x3c},{"F3",0x3d},{"F4",0x3e},{"F5",0x3f},{"F6",0x40},{"F7",0x41},{"F8",0x42},{"F9",0x43},{"F10",0x44},
    {"F11",0x57},{"F12",0x58},{"KPENTER",0x9c},{"RCTRL",0x9d},{"RALT",0xb8},
    {"HOME",0xc7},{"UP",0xc8},{"PGUP",0xc9},{"LEFT",0xcb},{"RIGHT",0xcd},{"END",0xcf},{"DOWN",0xd0},{"PGDN",0xd1},{"INSERT",0xd2},{"DELETE",0xd3},
};
static uint8_t sc_to_dik(SDL_Scancode sc) {
    if (sc >= SDL_SCANCODE_A && sc <= SDL_SCANCODE_Z) { char n[2] = { (char)('A' + (sc - SDL_SCANCODE_A)), 0 };
        for (size_t i = 0; i < sizeof k_names / sizeof k_names[0]; i++) if (!strcmp(k_names[i].n, n)) return k_names[i].dik; }
    if (sc >= SDL_SCANCODE_1 && sc <= SDL_SCANCODE_0) return (uint8_t)(0x02 + (sc - SDL_SCANCODE_1));
    if (sc >= SDL_SCANCODE_F1 && sc <= SDL_SCANCODE_F10) return (uint8_t)(0x3b + (sc - SDL_SCANCODE_F1));
    switch (sc) {
    case SDL_SCANCODE_ESCAPE: return 0x01; case SDL_SCANCODE_MINUS: return 0x0c; case SDL_SCANCODE_EQUALS: return 0x0d;
    case SDL_SCANCODE_BACKSPACE: return 0x0e; case SDL_SCANCODE_TAB: return 0x0f; case SDL_SCANCODE_LEFTBRACKET: return 0x1a;
    case SDL_SCANCODE_RIGHTBRACKET: return 0x1b; case SDL_SCANCODE_RETURN: return 0x1c; case SDL_SCANCODE_LCTRL: return 0x1d;
    case SDL_SCANCODE_SEMICOLON: return 0x27; case SDL_SCANCODE_APOSTROPHE: return 0x28; case SDL_SCANCODE_GRAVE: return 0x29;
    case SDL_SCANCODE_LSHIFT: return 0x2a; case SDL_SCANCODE_BACKSLASH: return 0x2b; case SDL_SCANCODE_COMMA: return 0x33;
    case SDL_SCANCODE_PERIOD: return 0x34; case SDL_SCANCODE_SLASH: return 0x35; case SDL_SCANCODE_RSHIFT: return 0x36;
    case SDL_SCANCODE_KP_MULTIPLY: return 0x37; case SDL_SCANCODE_LALT: return 0x38; case SDL_SCANCODE_SPACE: return 0x39;
    case SDL_SCANCODE_CAPSLOCK: return 0x3a; case SDL_SCANCODE_NUMLOCKCLEAR: return 0x45; case SDL_SCANCODE_SCROLLLOCK: return 0x46;
    case SDL_SCANCODE_KP_7: return 0x47; case SDL_SCANCODE_KP_8: return 0x48; case SDL_SCANCODE_KP_9: return 0x49;
    case SDL_SCANCODE_KP_MINUS: return 0x4a; case SDL_SCANCODE_KP_4: return 0x4b; case SDL_SCANCODE_KP_5: return 0x4c;
    case SDL_SCANCODE_KP_6: return 0x4d; case SDL_SCANCODE_KP_PLUS: return 0x4e; case SDL_SCANCODE_KP_1: return 0x4f;
    case SDL_SCANCODE_KP_2: return 0x50; case SDL_SCANCODE_KP_3: return 0x51; case SDL_SCANCODE_KP_0: return 0x52;
    case SDL_SCANCODE_KP_PERIOD: return 0x53; case SDL_SCANCODE_F11: return 0x57; case SDL_SCANCODE_F12: return 0x58;
    case SDL_SCANCODE_KP_ENTER: return 0x9c; case SDL_SCANCODE_RCTRL: return 0x9d; case SDL_SCANCODE_KP_DIVIDE: return 0xb5;
    case SDL_SCANCODE_RALT: return 0xb8; case SDL_SCANCODE_HOME: return 0xc7; case SDL_SCANCODE_UP: return 0xc8;
    case SDL_SCANCODE_PAGEUP: return 0xc9; case SDL_SCANCODE_LEFT: return 0xcb; case SDL_SCANCODE_RIGHT: return 0xcd;
    case SDL_SCANCODE_END: return 0xcf; case SDL_SCANCODE_DOWN: return 0xd0; case SDL_SCANCODE_PAGEDOWN: return 0xd1;
    case SDL_SCANCODE_INSERT: return 0xd2; case SDL_SCANCODE_DELETE: return 0xd3;
    default: return 0;
    }
}
int plat_key_dik(const char *name) {   /* имя или номер → DIK; -1 — неизвестно */
    if (!name || !*name) return -1;
    if (name[0] >= '0' && name[0] <= '9' && name[1]) { char *e; long v = strtol(name, &e, 0); if (!*e && v > 0 && v < 256) return (int)v; }
    for (size_t i = 0; i < sizeof k_names / sizeof k_names[0]; i++) if (!SDL_strcasecmp(k_names[i].n, name)) return k_names[i].dik;
    return -1;
}
#define MAX_SCRIPT 256
static struct { int frame, hold; uint8_t dik; uint8_t logged; } g_scr[MAX_SCRIPT];   /* v2.05: hold — «кадр:клавиша:кадров» */
static int g_nscr = -1, g_hold = 2;
static void script_load(void) {
    g_nscr = 0;
    const char *h = getenv("RE_KEYS_HOLD"); if (h && atoi(h) > 0) g_hold = atoi(h);
    const char *s = getenv("RE_KEYS"); if (!s) return;
    char buf[4096]; snprintf(buf, sizeof buf, "%s", s);
    for (char *tk = strtok(buf, ", "); tk && g_nscr < MAX_SCRIPT; tk = strtok(NULL, ", ")) {
        char *c = strchr(tk, ':'); if (!c) { fprintf(stderr, "[keys] RE_KEYS: пропуск «%s» (нужно кадр:клавиша)\n", tk); continue; }
        *c = 0; char *c2 = strchr(c + 1, ':'); int hold = 0; if (c2) { *c2 = 0; hold = atoi(c2 + 1); }
        int d = plat_key_dik(c + 1);
        if (d < 0) { fprintf(stderr, "[keys] RE_KEYS: неизвестная клавиша «%s»\n", c + 1); continue; }
        g_scr[g_nscr].frame = atoi(tk); g_scr[g_nscr].hold = hold; g_scr[g_nscr].dik = (uint8_t)d; g_scr[g_nscr].logged = 0; g_nscr++;
    }
    fprintf(stderr, "[keys] сценарий RE_KEYS: %d нажатий, удержание %d кадр.\n", g_nscr, g_hold);
}
/* v2.30: отладка — нажатие через rel кадров от текущего (RE_AUTOCONT: выбор Continue после итога миссии); 0 — принято */
int plat_keys_push(int rel, const char *name) {
    if (g_nscr < 0) script_load();
    int d = plat_key_dik(name);
    if (d < 0 || g_nscr >= MAX_SCRIPT) return -1;
    g_scr[g_nscr].frame = plat_frame_no() + rel; g_scr[g_nscr].hold = 0; g_scr[g_nscr].dik = (uint8_t)d; g_scr[g_nscr].logged = 0; g_nscr++;
    return 0;
}
/* v2.30: отладочный автопилот (RE_AUTORAM) — клавиша нажата на ближайшие 2 опроса */
static uint8_t g_auto[256];
void plat_auto_key(int dik) { if (dik > 0 && dik < 256) g_auto[dik] = 2; }
static SDL_GameController *g_pad;
static uint8_t g_latch[256];
void plat_input_key_event(int scancode, int down, int repeat) {
    if (!g_in_on || !down || repeat) return;
    uint8_t d = sc_to_dik((SDL_Scancode)scancode);
    if (d) g_latch[d] = 1;
}
void plat_input_fill_keys(uint8_t *k) {
    if (!g_in_on) return;
    if (g_nscr < 0) script_load();
    int fr = plat_frame_no();
    for (int i = 0; i < 256; i++) if (g_auto[i]) { k[i] = 0x80; g_auto[i]--; }
    for (int i = 0; i < g_nscr; i++)
        if (fr >= g_scr[i].frame && fr < g_scr[i].frame + (g_scr[i].hold > 0 ? g_scr[i].hold : g_hold)) {
            k[g_scr[i].dik] = 0x80;
            if (!g_scr[i].logged) { g_scr[i].logged = 1; fprintf(stderr, "[keys] кадр %d: DIK 0x%02x нажата\n", fr, g_scr[i].dik); }
        }
    if (!SDL_WasInit(SDL_INIT_VIDEO)) return;
    /* v2.14: короткое нажатие (KEYDOWN и KEYUP между двумя опросами игры) — защёлка держит клавишу до первого чтения */
    for (int i = 0; i < 256; i++) if (g_latch[i]) { k[i] = 0x80; g_latch[i] = 0; }
    /* состояние клавиатуры — по scancode (физическое положение клавиши, не зависит от раскладки); обновляется разбором
       событий в главном потоке (plat_pump_messages / plat_flip) */
    int n = 0; const Uint8 *st = SDL_GetKeyboardState(&n);
    for (int sc = 0; st && sc < n; sc++) if (st[sc]) { uint8_t d = sc_to_dik((SDL_Scancode)sc); if (d) k[d] = 0x80; }
    if (SDL_GetModState() & (KMOD_GUI | KMOD_ALT)) { k[0x1c] = 0; k[0x9c] = 0; }   /* Cmd/Alt+Enter — полный экран, не игре */
    if (!SDL_WasInit(SDL_INIT_GAMECONTROLLER)) return;
    if (g_pad && !SDL_GameControllerGetAttached(g_pad)) { SDL_GameControllerClose(g_pad); g_pad = NULL; }
    if (!g_pad) for (int j = 0; j < SDL_NumJoysticks(); j++) if (SDL_IsGameController(j) && (g_pad = SDL_GameControllerOpen(j))) break;
    if (!g_pad) return;
    SDL_GameControllerUpdate();
    int ax = SDL_GameControllerGetAxis(g_pad, SDL_CONTROLLER_AXIS_LEFTX), ay = SDL_GameControllerGetAxis(g_pad, SDL_CONTROLLER_AXIS_LEFTY);
    if (SDL_GameControllerGetButton(g_pad, SDL_CONTROLLER_BUTTON_DPAD_UP) || ay < -16000) k[0xc8] = 0x80;
    if (SDL_GameControllerGetButton(g_pad, SDL_CONTROLLER_BUTTON_DPAD_DOWN) || ay > 16000) k[0xd0] = 0x80;
    if (SDL_GameControllerGetButton(g_pad, SDL_CONTROLLER_BUTTON_DPAD_LEFT) || ax < -16000) k[0xcb] = 0x80;
    if (SDL_GameControllerGetButton(g_pad, SDL_CONTROLLER_BUTTON_DPAD_RIGHT) || ax > 16000) k[0xcd] = 0x80;
    if (SDL_GameControllerGetButton(g_pad, SDL_CONTROLLER_BUTTON_A) || SDL_GameControllerGetButton(g_pad, SDL_CONTROLLER_BUTTON_START)) k[0x1c] = 0x80;
    if (SDL_GameControllerGetButton(g_pad, SDL_CONTROLLER_BUTTON_B) || SDL_GameControllerGetButton(g_pad, SDL_CONTROLLER_BUTTON_BACK)) k[0x01] = 0x80;
    if (SDL_GameControllerGetButton(g_pad, SDL_CONTROLLER_BUTTON_X)) k[0x39] = 0x80;
}

/* ===== v2.14: RE_INPUTDBG=1 — журнал ввода driver_input.log (macOS: ~/Library/Logs/driver_input.log, иначе рядом с бинарником,
   если каталог не пишется — текущий каталог). Пишутся: версии SDL (заголовки/библиотека), видеодрайвер, главный ли поток,
   события SDL (клавиши: scancode, keycode, mod, repeat; окно: фокус/показ/размер; геймпад; мышь — только кнопки), активация
   окна игры (WM_ACTIVATEAPP), раз в кадр-смену — набор нажатых DIK, который получает игра. ===== */
#if defined(__APPLE__)
#include <pthread.h>
#elif defined(__linux__)
#include <unistd.h>
#include <sys/syscall.h>
#endif
static FILE *g_idbg; static int g_idbg_on = -1;
int plat_is_main_thread(void) {   /* 1 — главный поток процесса, 0 — нет, -1 — неизвестно */
#if defined(__APPLE__)
    return pthread_main_np() ? 1 : 0;
#elif defined(__linux__)
    return (long)syscall(SYS_gettid) == (long)getpid() ? 1 : 0;
#else
    return -1;
#endif
}
static FILE *idbg(void) {
    if (g_idbg_on < 0) {
        const char *e = getenv("RE_INPUTDBG"); g_idbg_on = e && *e && *e != '0';
        if (g_idbg_on) {
            char path[1024] = "";
#if defined(__APPLE__)
            const char *home = getenv("HOME");
            if (home) { snprintf(path, sizeof path, "%s/Library/Logs/driver_input.log", home); g_idbg = fopen(path, "w"); }
#endif
            if (!g_idbg) { char *b = SDL_GetBasePath(); if (b) { snprintf(path, sizeof path, "%sdriver_input.log", b); SDL_free(b); g_idbg = fopen(path, "w"); } }
            if (!g_idbg) { snprintf(path, sizeof path, "driver_input.log"); g_idbg = fopen(path, "w"); }
            if (g_idbg) {
                SDL_version c, l; SDL_VERSION(&c); SDL_GetVersion(&l);
                fprintf(stderr, "[input] RE_INPUTDBG: журнал %s\n", path);
                fprintf(g_idbg, "Driver input log. SDL headers %d.%d.%d, library %d.%d.%d (%s), video %s, platform %s, main thread %d\n",
                        c.major, c.minor, c.patch, l.major, l.minor, l.patch, SDL_GetRevision(), SDL_GetCurrentVideoDriver() ? SDL_GetCurrentVideoDriver() : "-",
                        SDL_GetPlatform(), plat_is_main_thread());
                fflush(g_idbg);
            } else g_idbg_on = 0;
        }
    }
    return g_idbg_on ? g_idbg : NULL;
}
void plat_input_dbg(const char *fmt, ...) {
    FILE *f = idbg(); if (!f) return;
    va_list a; va_start(a, fmt);
    fprintf(f, "[%6u ms, кадр %d] ", SDL_GetTicks(), plat_frame_no()); vfprintf(f, fmt, a); fputc('\n', f); fflush(f);
    va_end(a);
}
void plat_input_dbg_event(const void *ev) {
    const SDL_Event *e = (const SDL_Event *)ev;
    if (!idbg()) return;
    static int checked;
    if (!checked) { checked = 1; plat_input_dbg("цикл событий: главный поток %d", plat_is_main_thread()); }
    switch (e->type) {
    case SDL_KEYDOWN: case SDL_KEYUP:
        plat_input_dbg("%s scancode %d (%s) keycode 0x%x (%s) mod 0x%x repeat %d окно %u → DIK 0x%02x",
            e->type == SDL_KEYDOWN ? "KEYDOWN" : "KEYUP  ", e->key.keysym.scancode, SDL_GetScancodeName(e->key.keysym.scancode),
            (unsigned)e->key.keysym.sym, SDL_GetKeyName(e->key.keysym.sym), e->key.keysym.mod, e->key.repeat, e->key.windowID,
            sc_to_dik(e->key.keysym.scancode));
        break;
    case SDL_WINDOWEVENT: {
        static const char *const n[] = { "NONE","SHOWN","HIDDEN","EXPOSED","MOVED","RESIZED","SIZE_CHANGED","MINIMIZED","MAXIMIZED",
                                         "RESTORED","ENTER","LEAVE","FOCUS_GAINED","FOCUS_LOST","CLOSE","TAKE_FOCUS","HIT_TEST" };
        if (e->window.event == SDL_WINDOWEVENT_MOVED || e->window.event == SDL_WINDOWEVENT_EXPOSED) break;
        SDL_Window *w = SDL_GetWindowFromID(e->window.windowID);
        plat_input_dbg("WINDOW %s %d %d, флаги окна 0x%x (фокус клавиатуры %d)", e->window.event < 17 ? n[e->window.event] : "?",
            e->window.data1, e->window.data2, w ? SDL_GetWindowFlags(w) : 0, w ? !!(SDL_GetWindowFlags(w) & SDL_WINDOW_INPUT_FOCUS) : -1);
        break; }
    case SDL_CONTROLLERDEVICEADDED: case SDL_CONTROLLERDEVICEREMOVED: case SDL_JOYDEVICEADDED: case SDL_JOYDEVICEREMOVED:
        plat_input_dbg("устройство 0x%x индекс %d", e->type, e->cdevice.which); break;
    case SDL_CONTROLLERBUTTONDOWN: case SDL_CONTROLLERBUTTONUP:
        plat_input_dbg("геймпад кнопка %d %s", e->cbutton.button, e->type == SDL_CONTROLLERBUTTONDOWN ? "down" : "up"); break;
    case SDL_MOUSEBUTTONDOWN: plat_input_dbg("мышь кнопка %d в %d,%d", e->button.button, e->button.x, e->button.y); break;
    case SDL_QUIT: plat_input_dbg("QUIT"); break;
    case SDL_TEXTINPUT: case SDL_MOUSEMOTION: case SDL_CONTROLLERAXISMOTION: case SDL_JOYAXISMOTION: break;
    default: break;
    }
}
static void dbg_keys(const uint8_t *k) {   /* набор DIK, видимый игре, — при каждом изменении */
    if (!idbg()) return;
    static uint8_t prev[256];
    if (!memcmp(prev, k, 256)) return;
    memcpy(prev, k, 256);
    char b[512]; int n = 0; b[0] = 0;
    for (int i = 0; i < 256 && n < (int)sizeof b - 8; i++) if (k[i]) n += snprintf(b + n, sizeof b - n, " %02x", i);
    plat_input_dbg("игра видит DIK:%s", n ? b : " (ничего)");
}
