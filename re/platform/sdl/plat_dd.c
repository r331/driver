/* SDL-вариант объектов DirectDraw/Direct3D: учётные записи без устройства.
   Игровой код (game/ported24.c) работает с дескрипторами; реальное окно/буфер даёт plat_render.c. */
#include "../plat.h"
#include <stdlib.h>
#include <string.h>
typedef struct { uint32_t tag; int32_t lost; int32_t attached; int32_t clipper; } dd_obj;
static int g_live;
static int32_t g_fill[4]; static uint32_t g_fill_px; static int g_fill_n;
static void *mk(uint32_t tag) { dd_obj *o = (dd_obj *)calloc(1, sizeof *o); if (o) { o->tag = tag; g_live++; } return o; }
void *plat_dd_create_surface(void *dd, const void *desc) { if (!dd || !desc) return NULL; return mk(1); }
int32_t plat_dd_set_display_mode(void *dd, int w, int h, int bpp) { (void)w; (void)h; (void)bpp; return dd ? 0 : -1; }
void *plat_dd_create_clipper(void *dd) { return dd ? mk(2) : NULL; }
int32_t plat_dd_set_clipper(void *s, void *c) { if (!s || !c) return -1; ((dd_obj *)s)->clipper = 1; return 0; }
int32_t plat_dd_attach_surface(void *s, void *a) { if (!s || !a) return -1; ((dd_obj *)s)->attached++; return 0; }
void *plat_dd_get_attached(void *s, uint32_t caps) { (void)caps; return s ? mk(1) : NULL; }
void plat_dd_release(void *o) { if (o) { free(o); g_live--; } }
int32_t plat_dd_is_lost(void *s) { return s ? ((dd_obj *)s)->lost : 0; }
int32_t plat_dd_restore(void *s) { if (s) ((dd_obj *)s)->lost = 0; return 0; }
int32_t plat_dd_fill_rect(void *s, int x0, int y0, int x1, int y1, uint32_t px) {
    (void)s; g_fill[0] = x0; g_fill[1] = y0; g_fill[2] = x1; g_fill[3] = y1; g_fill_px = px; g_fill_n++; return 0;
}
void *plat_d3d_create_device(void *d3d, const void *iid, void *surf) { (void)iid; return (d3d && surf) ? mk(3) : NULL; }
void *plat_d3d_create_viewport(void *d3d) { return d3d ? mk(4) : NULL; }
int32_t plat_d3d_add_viewport(void *dev, void *vp) { return (dev && vp) ? 0 : -1; }
int32_t plat_d3d_set_viewport_rect(void *vp, int w, int h) { return (vp && w > 0 && h > 0) ? 0 : -1; }
void plat_window_maximize(void *wnd) { (void)wnd; }
int plat_dd_stub_count(void) { return g_live; }
int plat_dd_stub_last_fill(int32_t *r, uint32_t *px) { if (!g_fill_n) return 0; memcpy(r, g_fill, sizeof g_fill); *px = g_fill_px; return g_fill_n; }
