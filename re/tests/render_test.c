#pragma GCC diagnostic ignored "-Wmissing-field-initializers"
/* Тест GL 3.3 бэкенда: рендер в offscreen (OSMesa), проверка пикселей, PNG-снимок. */
#include "../platform/plat.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define CHECK(c) do { if (!(c)) { printf("FAIL %s:%d %s\n", __FILE__, __LINE__, #c); return 1; } } while (0)

static uint32_t crc_tab[256];
static uint32_t crc32_upd(uint32_t c, const uint8_t *p, size_t n) {
    if (!crc_tab[1]) for (uint32_t i = 0; i < 256; i++) { uint32_t k = i; for (int j = 0; j < 8; j++) k = k & 1 ? 0xEDB88320u ^ (k >> 1) : k >> 1; crc_tab[i] = k; }
    c = ~c; while (n--) c = crc_tab[(c ^ *p++) & 255] ^ (c >> 8); return ~c;
}
static void be32(uint8_t *p, uint32_t v) { p[0] = v >> 24; p[1] = v >> 16; p[2] = v >> 8; p[3] = v; }
static void chunk(FILE *f, const char *t, const uint8_t *d, uint32_t n) {
    uint8_t h[8]; be32(h, n); memcpy(h + 4, t, 4); fwrite(h, 1, 8, f); if (n) fwrite(d, 1, n, f);
    uint32_t c = crc32_upd(0, (const uint8_t *)t, 4); c = crc32_upd(c, d, n); uint8_t b[4]; be32(b, c); fwrite(b, 1, 4, f);
}
/* PNG без сжатия (stored deflate), RGBA8 */
int png_write_rgba(const char *path, const uint32_t *px, int w, int h) {
    FILE *f = fopen(path, "wb"); if (!f) return -1;
    size_t row = (size_t)w * 4 + 1, raw = row * h; uint8_t *z = malloc(raw + raw / 65535 * 5 + 64), *r = malloc(raw);
    for (int y = 0; y < h; y++) { r[y * row] = 0; memcpy(r + y * row + 1, px + (size_t)y * w, (size_t)w * 4); }
    size_t zn = 0; z[zn++] = 0x78; z[zn++] = 1;
    for (size_t o = 0; o < raw || o == 0;) { size_t n = raw - o > 65535 ? 65535 : raw - o; z[zn++] = (o + n >= raw); z[zn++] = n; z[zn++] = n >> 8; z[zn++] = ~n; z[zn++] = ~n >> 8; memcpy(z + zn, r + o, n); zn += n; o += n; if (!n) break; }
    uint32_t a = 1, b = 0; for (size_t i = 0; i < raw; i++) { a = (a + r[i]) % 65521; b = (b + a) % 65521; }
    be32(z + zn, (b << 16) | a); zn += 4;
    static const uint8_t sig[8] = { 0x89, 'P', 'N', 'G', 13, 10, 26, 10 }; fwrite(sig, 1, 8, f);
    uint8_t ih[13]; be32(ih, w); be32(ih + 4, h); ih[8] = 8; ih[9] = 6; ih[10] = ih[11] = ih[12] = 0;
    chunk(f, "IHDR", ih, 13); chunk(f, "IDAT", z, (uint32_t)zn); chunk(f, "IEND", NULL, 0);
    fclose(f); free(z); free(r); return 0;
}
#define PX(x, y) px[(y) * W + (x)]
/* байты R,G,B,A в little-endian uint32 -> сравнение с допуском */
static int near_px(uint32_t p, int r, int g, int b) {
    int pr = p & 255, pg = (p >> 8) & 255, pb = (p >> 16) & 255;
    return abs(pr - r) <= 3 && abs(pg - g) <= 3 && abs(pb - b) <= 3;
}
int test_render(const char *png_path) {
    enum { W = 256, H = 192 };
    int rc = plat_render_offscreen(W, H);
    if (rc == -1) { printf("render: SKIP (нет OSMesa в сборке)\n"); return 0; }
    CHECK(rc == 0);
    plat_clear(0xFF2040C0, 1);
    /* 1) градиентный треугольник (красный/зелёный/синий углы) */
    plat_vertex t[3] = { { 20, 20, 0.5f, 1, 0xFFFF0000, 0, 0, 0 }, { 120, 20, 0.5f, 1, 0xFF00FF00, 0, 0, 0 }, { 20, 120, 0.5f, 1, 0xFF0000FF, 0, 0, 0 } };
    plat_set_zbuffer(1, 1); plat_set_blend(0, 0, 0); plat_draw_tris(t, 3);
    /* 2) квадрат с шахматной текстурой 2x2 (nearest не гарантирован — берём центры клеток) */
    uint32_t chk[4 * 4]; for (int y = 0; y < 4; y++) for (int x = 0; x < 4; x++) chk[y * 4 + x] = ((x / 2 + y / 2) & 1) ? 0xFF0000FFu /* красный R=255 в RGBA байтах */ : 0xFFFFFFFFu;
    int tx = plat_tex_create(4, 4, chk); CHECK(tx > 0);
    plat_tex_bind(tx);
    plat_vertex q[6] = { { 140, 20, 0.4f, 1, 0xFFFFFFFF, 0, 0, 0 }, { 236, 20, 0.4f, 1, 0xFFFFFFFF, 0, 1, 0 }, { 236, 116, 0.4f, 1, 0xFFFFFFFF, 0, 1, 1 },
                         { 140, 20, 0.4f, 1, 0xFFFFFFFF, 0, 0, 0 }, { 236, 116, 0.4f, 1, 0xFFFFFFFF, 0, 1, 1 }, { 140, 116, 0.4f, 1, 0xFFFFFFFF, 0, 0, 1 } };
    plat_draw_tris(q, 6); plat_tex_bind(0);
    /* 3) полупрозрачный белый квадрат (alpha 50%) поверх фона, 4) z-тест: дальний зелёный не перекрывает ближний красный */
    plat_set_blend(1, 5, 6);
    plat_vertex a[6]; uint32_t ac = 0x80FFFFFF; float ax0 = 20, ay0 = 140, ax1 = 80, ay1 = 180;
    plat_vertex av[6] = { { ax0, ay0, .3f, 1, ac }, { ax1, ay0, .3f, 1, ac }, { ax1, ay1, .3f, 1, ac }, { ax0, ay0, .3f, 1, ac }, { ax1, ay1, .3f, 1, ac }, { ax0, ay1, .3f, 1, ac } };
    memcpy(a, av, sizeof a); plat_draw_tris(a, 6);
    plat_set_blend(0, 0, 0);
    uint32_t red = 0xFFFF0000, grn = 0xFF00FF00;
    plat_vertex n[6] = { { 100, 140, .2f, 1, red }, { 160, 140, .2f, 1, red }, { 160, 180, .2f, 1, red }, { 100, 140, .2f, 1, red }, { 160, 180, .2f, 1, red }, { 100, 180, .2f, 1, red } };
    plat_vertex f[6] = { { 130, 150, .8f, 1, grn }, { 190, 150, .8f, 1, grn }, { 190, 190, .8f, 1, grn }, { 130, 150, .8f, 1, grn }, { 190, 190, .8f, 1, grn }, { 130, 190, .8f, 1, grn } };
    plat_draw_tris(n, 6); plat_draw_tris(f, 6);
    /* 5) blit2d из текстуры 4x4: левая верхняя клетка 2x2 (белая, у линейного фильтра берём пиксель в центре) -> (200,150) */
    plat_blit2d(tx, 0, 0, 2, 2, 200, 150);
    plat_flip();
    uint32_t *px = malloc(W * H * 4); CHECK(plat_render_readback(px) == 0);
    CHECK(near_px(PX(250, 5), 0x20, 0x40, 0xC0));          /* фон */
    CHECK(PX(30, 30) != PX(100, 30) && near_px(PX(24, 24), 255, 0, 0) == 0); /* градиент меняется */
    CHECK((PX(25, 23) & 255) > 180);                        /* у красной вершины R велик */
    CHECK(((PX(110, 22) >> 8) & 255) > 150);                /* у зелёной вершины G велик */
    CHECK(((PX(22, 110) >> 16) & 255) > 150);               /* у синей вершины B велик */
    CHECK(near_px(PX(165, 45), 255, 255, 255) && near_px(PX(210, 45), 255, 0, 0)); /* текстура: клетки белая/красная */
    CHECK(near_px(PX(50, 160), 0x90, 0x9F, 0xDF));          /* белый 50% над (0x20,0x40,0xC0) */
    CHECK(near_px(PX(145, 165), 255, 0, 0));                /* z-тест: красный впереди */
    CHECK(near_px(PX(175, 175), 0, 255, 0));                /* зелёный виден вне красного */
    CHECK(near_px(PX(201, 151), 255, 255, 255));            /* blit2d */
    CHECK(png_write_rgba(png_path, px, W, H) == 0);
    printf("render: OK (%s)\n", png_path);
    free(px); plat_tex_free(tx); plat_render_shutdown();
    return 0;
}
