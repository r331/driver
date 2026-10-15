/* SDL-вариант DirectInput: учёт вызовов без устройства (клавиатуру из SDL подключим вместе с главным циклом). */
#include "../plat.h"
#include <string.h>
static int32_t g_jx, g_jy, g_poll;
static int g_rel, g_unacq, g_evt, g_kind = -1, g_fail;
void plat_di_release(void *o) { if (o) g_rel++; }
void plat_di_unacquire(void *d) { if (d) g_unacq++; }
int32_t plat_di_set_format(void *d, int kind) { if (!d) return -1; g_kind = kind; return 0; }
static uint32_t g_fmask, g_caps; static int g_njoy, g_ndev, g_ncoop, g_nprop, g_nqry, g_ntok;
static char g_tok[64];
#define FAIL(b) (g_fmask & (1u << (b)))
int32_t plat_di_acquire(void *d) { return (d && !FAIL(8)) ? 0 : -1; }
int32_t plat_di_get_state(void *d, uint32_t size, void *buf) {
    if (!d || g_fail) return -1;
    memset(buf, 0, size);                /* пока «ничего не нажато» */
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
