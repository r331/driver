/* Offscreen OpenGL 3.3 core context via OSMesa, for render tests without a display (native only;
   built when OSMesa is found). */
/* Offscreen-контекст через OSMesa (тесты рендера без дисплея). Собирается, если найден OSMesa. */
#include "../plat.h"
#include <GL/osmesa.h>
#include <stdlib.h>
#include "plat_gfx.h"
static OSMesaContext g_ctx; static void *g_buf;
/* ge — getenv adapter for re_gfx_env; getproc — GL function lookup through OSMesa. */
static const char *ge(const char *n) { return getenv(n); }
static void *getproc(const char *n) { return (void *)OSMesaGetProcAddress(n); }
/* plat_render_offscreen — Create a w x h RGBA offscreen OSMesa context (24-bit depth) and attach the
   GL renderer to it.  On first call applies the "original" graphics preset (pixels as in v2.15)
   unless RE_PRESET is set, then RE_* overrides.  Returns plat_render_attach()'s result,
   -10 if the context cannot be created, -11 if the buffer cannot be allocated/made current.
   The buffer is never freed (one context per process). */
int plat_render_offscreen(int w, int h) {
    const int attr[] = { OSMESA_FORMAT, OSMESA_RGBA, OSMESA_DEPTH_BITS, 24, OSMESA_PROFILE, OSMESA_CORE_PROFILE,
                         OSMESA_CONTEXT_MAJOR_VERSION, 3, OSMESA_CONTEXT_MINOR_VERSION, 3, 0 };
    /* v2.16: тесты offscreen — пресет original (пиксели как v2.15), если не задан RE_PRESET/RE_* */
    { static int once; if (!once) { once = 1; re_gfx_cfg *c = re_gfx(); if (!getenv("RE_PRESET")) re_gfx_preset(c, "original"); re_gfx_env(c, ge); } }
    g_ctx = OSMesaCreateContextAttribs(attr, NULL); if (!g_ctx) return -10;
    g_buf = malloc((size_t)w * h * 4); if (!g_buf || !OSMesaMakeCurrent(g_ctx, g_buf, GL_UNSIGNED_BYTE, w, h)) return -11;
    return plat_render_attach(getproc, NULL, w, h);
}
