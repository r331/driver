/* v2.17: HD-пак текстур — загрузка PNG (stb_image, public domain, только PNG) и сверка со страницей игры. */
#include "plat_texpack.h"
#include "plat_gfx.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_STATIC
#define STBI_ONLY_PNG
#define STBI_NO_STDIO
#define STBI_NO_LINEAR
#define STBI_NO_HDR
#if defined(__GNUC__) || defined(__clang__)
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-function"
#pragma GCC diagnostic ignored "-Wsign-compare"
#pragma GCC diagnostic ignored "-Wunused-parameter"
#endif
#include "../../third_party/stb_image.h"
#if defined(__GNUC__) || defined(__clang__)
#pragma GCC diagnostic pop
#pragma GCC diagnostic ignored "-Wunused-function"   /* статические объявления stb (gif и пр.) без определений */
#endif

const char *re_texpack_dir(void) {
    const char *e = getenv("RE_TEXPACK");
    if (e && *e) return e;
    const char *c = re_gfx()->texpack;
    return c[0] ? c : NULL;
}
void re_texpack_level_name(const char *path, char *out, int n) {
    if (!out || n <= 0) return;
    out[0] = 0; if (!path) return;
    const char *b = path;
    for (const char *p = path; *p; p++) if (*p == '/' || *p == '\\') b = p + 1;
    int len = (int)strlen(b);
    if (len > 4 && b[len - 4] == '.' && (b[len - 3] | 32) == 'l' && (b[len - 2] | 32) == 'e' && (b[len - 1] | 32) == 'v') len -= 4;
    if (len >= n) len = n - 1;
    memcpy(out, b, (size_t)len); out[len] = 0;
}
uint32_t *re_texpack_decode_png(const void *buf, int len, int *w, int *h) {
    int x = 0, y = 0, ch = 0;
    unsigned char *d = stbi_load_from_memory((const unsigned char *)buf, len, &x, &y, &ch, 4);
    if (!d) return NULL;
    uint32_t *px = (uint32_t *)malloc((size_t)x * y * 4);
    if (px) for (size_t i = 0; i < (size_t)x * y; i++)
        px[i] = (uint32_t)d[i * 4] | (uint32_t)d[i * 4 + 1] << 8 | (uint32_t)d[i * 4 + 2] << 16 | (uint32_t)d[i * 4 + 3] << 24;
    stbi_image_free(d);
    if (px) { *w = x; *h = y; }
    return px;
}
uint32_t *re_texpack_load(const char *dir, const char *level, int idx, int *w, int *h) {
    if (!dir || !level || !*level) return NULL;
    char path[1024];
    snprintf(path, sizeof path, "%s%s%s/p%03d.png", dir, dir[0] && dir[strlen(dir) - 1] != '/' ? "/" : "", level, idx);
    FILE *f = fopen(path, "rb");
    if (!f) return NULL;
    fseek(f, 0, SEEK_END); long n = ftell(f); fseek(f, 0, SEEK_SET);
    if (n <= 0 || n > (64L << 20)) { fclose(f); return NULL; }
    unsigned char *b = (unsigned char *)malloc((size_t)n);
    if (!b || fread(b, 1, (size_t)n, f) != (size_t)n) { fclose(f); free(b); return NULL; }
    fclose(f);
    int x = 0, y = 0;
    uint32_t *px = re_texpack_decode_png(b, (int)n, &x, &y);
    free(b);
    if (!px) return NULL;
    if (x != y || x < 256 || x > 1024 || (x & (x - 1))) { free(px); return NULL; }
    *w = x; *h = y;
    return px;
}
void re_texpack_compare(const uint32_t *hd, int w, int h, const uint16_t *page, double *err, double *amis) {
    int sx = w / 256, sy = h / 256; double e = 0; long am = 0;
    for (int y = 0; y < 256; y++) for (int x = 0; x < 256; x++) {
        unsigned r = 0, g = 0, b = 0, a = 0;
        for (int dy = 0; dy < sy; dy++) for (int dx = 0; dx < sx; dx++) {
            uint32_t p = hd[(size_t)(y * sy + dy) * w + x * sx + dx];
            r += p & 255; g += (p >> 8) & 255; b += (p >> 16) & 255; a += p >> 24;
        }
        unsigned k = (unsigned)(sx * sy); r /= k; g /= k; b /= k; a /= k;
        uint16_t s = page[y * 256 + x];
        int op = (s & 0x8000) != 0;
        if ((a >= 128) != op) am++;
        unsigned R = (s >> 10) & 31, G = (s >> 5) & 31, B = s & 31;
        R = R << 3 | R >> 2; G = G << 3 | G >> 2; B = B << 3 | B >> 2;
        double d = (abs((int)r - (int)R) + abs((int)g - (int)G) + abs((int)b - (int)B)) / 3.0;
        e += d;   /* по всем пикселям: прозрачным может оказаться любое состояние бита (решает альфа-тест при рисовании) */
    }
    if (err) *err = e / 65536.0;
    if (amis) *amis = (double)am / 65536.0;
}
