/* SDL-вариант DirectInput: учёт вызовов без устройства (клавиатуру из SDL подключим вместе с главным циклом). */
#include "../plat.h"
#include <string.h>
static int g_rel, g_unacq, g_evt, g_kind = -1, g_fail;
void plat_di_release(void *o) { if (o) g_rel++; }
void plat_di_unacquire(void *d) { if (d) g_unacq++; }
int32_t plat_di_set_format(void *d, int kind) { if (!d) return -1; g_kind = kind; return 0; }
int32_t plat_di_acquire(void *d) { return d ? 0 : -1; }
int32_t plat_di_get_state(void *d, uint32_t size, void *buf) {
    if (!d || g_fail) return -1;
    memset(buf, 0, size); return 0;      /* пока «ничего не нажато» */
}
void plat_event_close(void *h) { if (h) g_evt++; }
int plat_di_stub_counts(int *r, int *u, int *e, int *k) { *r = g_rel; *u = g_unacq; *e = g_evt; *k = g_kind; return 1; }
void plat_di_stub_fail_state(int on) { g_fail = on; }
