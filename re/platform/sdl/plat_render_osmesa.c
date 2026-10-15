/* Offscreen-контекст через OSMesa (тесты рендера без дисплея). Собирается, если найден OSMesa. */
#include "../plat.h"
#include <GL/osmesa.h>
#include <stdlib.h>
static OSMesaContext g_ctx; static void *g_buf;
static void *getproc(const char *n) { return (void *)OSMesaGetProcAddress(n); }
int plat_render_offscreen(int w, int h) {
    const int attr[] = { OSMESA_FORMAT, OSMESA_RGBA, OSMESA_DEPTH_BITS, 24, OSMESA_PROFILE, OSMESA_CORE_PROFILE,
                         OSMESA_CONTEXT_MAJOR_VERSION, 3, OSMESA_CONTEXT_MINOR_VERSION, 3, 0 };
    g_ctx = OSMesaCreateContextAttribs(attr, NULL); if (!g_ctx) return -10;
    g_buf = malloc((size_t)w * h * 4); if (!g_buf || !OSMesaMakeCurrent(g_ctx, g_buf, GL_UNSIGNED_BYTE, w, h)) return -11;
    return plat_render_attach(getproc, NULL, w, h);
}
