/* SDL-вариант DirectInput: учёт вызовов без устройства (клавиатуру из SDL подключим вместе с главным циклом). */
#include "../plat.h"
#include <string.h>
static int32_t g_jx, g_jy, g_poll;
static int g_rel, g_unacq, g_evt, g_kind = -1, g_fail;
void plat_di_release(void *o) { if (o) g_rel++; }
void plat_di_unacquire(void *d) { if (d) g_unacq++; }
int32_t plat_di_set_format(void *d, int kind) { if (!d) return -1; g_kind = kind; return 0; }
int32_t plat_di_acquire(void *d) { return d ? 0 : -1; }
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
    if (!e) return -1; g_ef_sets++; g_ef_skind = kind; g_ef_dx = dx; g_ef_dy = dy; g_ef_mag = mag; return 0;
}
int plat_di_stub_effects(int *c, int *ck, int *s, int *sk, int32_t *dx, int32_t *dy, int32_t *mag) {
    *c = g_ef_created; *ck = g_ef_ckind; *s = g_ef_sets; *sk = g_ef_skind; *dx = g_ef_dx; *dy = g_ef_dy; *mag = g_ef_mag; return 1;
}
void plat_di_stub_fail_enum(int on) { g_enum_fail = on; }
