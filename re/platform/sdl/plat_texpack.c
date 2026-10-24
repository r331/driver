/* HD texture pack (native only, v2.17+): finds and decodes PNG replacements of the game's 256x256
   texture pages (stb_image, PNG only), checks them against the original page and merges alpha.
   Pack layout: <pack>/<level>/pNNN.png (16-bit pages) and pNNN_cKKKK.png (8-bit page NNN with
   palette slot KKKK); an optional overlay directory (sky variants) is searched first. */
/* v2.17: HD-пак текстур — загрузка PNG (stb_image, public domain, только PNG) и сверка со страницей игры. */
#include "plat_texpack.h"
#include "plat_gfx.h"
#include "../plat_log.h"   /* v2.37: RE_LOG load */
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

/* re_texpack_dir — Pack directory: $RE_TEXPACK, else driver.cfg `texpack`, else NULL (pack disabled). */
const char *re_texpack_dir(void) {
    const char *e = getenv("RE_TEXPACK");
    if (e && *e) return e;
    const char *c = re_gfx()->texpack;
    return c[0] ? c : NULL;
}
/* re_texpack_level_name — Level name for the pack from a level path: the file name without directory and without a
   (case-insensitive) ".lev" suffix, truncated to n - 1 characters. */
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
/* re_texpack_decode_png — Decode a PNG in memory to malloc'ed RGBA pixels (R in the low byte).  Sets *w, *h.
   Returns NULL on error. */
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
static uint32_t *load_file(const char *path, int *w, int *h);
/* level_case — Copy a level name in case `mode`: 0 unchanged, 1 lower case, 2 upper case (ASCII). */
static void level_case(const char *in, char *out, int n, int mode) {   /* 0 — как есть, 1 — строчные, 2 — прописные */
    int i = 0;
    for (; in[i] && i < n - 1; i++) { char ch = in[i]; out[i] = mode == 1 && ch >= 'A' && ch <= 'Z' ? (char)(ch | 32) : mode == 2 && ch >= 'a' && ch <= 'z' ? (char)(ch & ~32) : ch; }
    out[i] = 0;
}
/* v2.27: вариант неба — оверлей пака: $RE_TEXPACK_SKY (подкаталог пака или полный путь; «0»/пусто — выкл.), иначе первое слово
   файла <пак>/sky.txt (напр. «sky_cc0»). Файлы оверлея (<пак>/<оверлей>/<уровень>/pNNN[_cKKKK].png) ищутся раньше основного
   пака и проходят ту же сверку со страницей.
   v2.36: второй оверлей того же устройства — HUD (перерисованные цифры часов миссии): $RE_TEXPACK_HUD или <пак>/hud.txt
   (напр. «hud_hd»); ищется раньше неба. */
/* overlay_named — Overlay directory named by environment variable `env` (sub-directory of the pack or an absolute
   path; empty or "0" disables), else by the first word of <pack>/<file>.  Writes the full path to out and returns
   it, or NULL when there is no overlay. */
static const char *overlay_named(const char *dir, const char *env, const char *file, char *out, int n) {
    if (!out || n <= 0) return NULL;
    out[0] = 0; if (!dir || !*dir) return NULL;
    char name[256] = { 0 };
    const char *e = getenv(env);
    if (e) { if (!*e || !strcmp(e, "0")) return NULL; snprintf(name, sizeof name, "%s", e); }
    else {
        char fn[1024]; snprintf(fn, sizeof fn, "%s%s%s", dir, dir[strlen(dir) - 1] != '/' ? "/" : "", file);
        FILE *f = fopen(fn, "rb"); if (!f) return NULL;
        if (fscanf(f, "%255s", name) != 1) name[0] = 0;
        fclose(f);
        if (!name[0] || !strcmp(name, "0")) return NULL;
    }
    if (name[0] == '/' || strstr(name, ":\\") || strstr(name, ":/")) snprintf(out, (size_t)n, "%s", name);
    else snprintf(out, (size_t)n, "%s%s%s", dir, dir[strlen(dir) - 1] != '/' ? "/" : "", name);
    return out;
}
/* re_texpack_overlay — Overlay directory (v2.27 sky variants): $RE_TEXPACK_SKY, else the first word of <pack>/sky.txt. */
const char *re_texpack_overlay(const char *dir, char *out, int n) { return overlay_named(dir, "RE_TEXPACK_SKY", "sky.txt", out, n); }
/* re_texpack_overlay_hud — Overlay directory (v2.36 HUD variant): $RE_TEXPACK_HUD, else the first word of <pack>/hud.txt. */
const char *re_texpack_overlay_hud(const char *dir, char *out, int n) { return overlay_named(dir, "RE_TEXPACK_HUD", "hud.txt", out, n); }
/* Tolerance of the page check for the file last returned by re_texpack_load / load8: the HUD overlay redraws glyph
   shapes on purpose (its pages differ from the original more than an upscale does), so it gets RE_TEXPACK_HUD_MAX_ERR. */
static double g_last_tol = RE_TEXPACK_MAX_ERR;
double re_texpack_last_tol(void) { return g_last_tol; }
/* re_texpack_last_hud — 1 when the file last returned by re_texpack_load / load8 came from the HUD overlay (v2.36). */
int re_texpack_last_hud(void) { return g_last_tol == RE_TEXPACK_HUD_MAX_ERR; }
static uint32_t *load_one(const char *dir, const char *level, int idx, int pal, int *w, int *h);
/* load_any — Load page idx (palette slot pal, -1 for 16-bit pages): the HUD overlay, the sky overlay, then the pack.
   hud.txt / sky.txt are re-read on every call (cheap, a few hundred pages per level).
   v2.39: the tolerance of the file found goes to *tol (no shared state), so the asynchronous loader
   (plat_texpack_async.c) can call it from worker threads; the synchronous wrappers copy it to g_last_tol. */
static uint32_t *load_any(const char *dir, const char *level, int idx, int pal, int *w, int *h, double *tol) {
    char odir[1024];   /* hud.txt / sky.txt читаются при каждой загрузке страницы (их сотни за уровень, файлы крошечные) */
    if (re_texpack_overlay_hud(dir, odir, sizeof odir)) {
        uint32_t *px = load_one(odir, level, idx, pal, w, h);
        if (px) { *tol = RE_TEXPACK_HUD_MAX_ERR; return px; }
    }
    *tol = RE_TEXPACK_MAX_ERR;
    if (re_texpack_overlay(dir, odir, sizeof odir)) { uint32_t *px = load_one(odir, level, idx, pal, w, h); if (px) return px; }
    return load_one(dir, level, idx, pal, w, h);
}
/* v2.18: каталог уровня — как в игре (P77_CurLevelPath, напр. MIAMI_01), строчными, ПРОПИСНЫМИ (файл miami_01.lev) */
/* load_one — Try the level directory as given, in lower case and in upper case; returns the first PNG
   that loads and passes load_file's size check. */
static uint32_t *load_one(const char *dir, const char *level, int idx, int pal, int *w, int *h) {
    char path[1024];
    for (int c = 0; c < 3; c++) {
        char lv[128]; level_case(level, lv, sizeof lv, c); if (c && !strcmp(lv, level)) continue;
        if (pal < 0) snprintf(path, sizeof path, "%s%s%s/p%03d.png", dir, dir[0] && dir[strlen(dir) - 1] != '/' ? "/" : "", lv, idx);
        else snprintf(path, sizeof path, "%s%s%s/p%03d_c%04d.png", dir, dir[0] && dir[strlen(dir) - 1] != '/' ? "/" : "", lv, idx, pal);
        uint32_t *px = load_file(path, w, h); if (px) return px;
    }
    return NULL;
}
/* re_texpack_load — HD replacement for 16-bit page idx of `level`, or NULL. */
uint32_t *re_texpack_load(const char *dir, const char *level, int idx, int *w, int *h) {
    if (!dir || !level || !*level) return NULL;
    return load_any(dir, level, idx, -1, w, h, &g_last_tol);
}
/* v2.18: 8-битная страница с палитрой: <dir>/<level>/pNNN_cKKKK.png, KKKK — номер слота палитры уровня (0..49) */
/* re_texpack_load8 — HD replacement for 8-bit page idx with palette slot pal (0..49), or NULL. */
uint32_t *re_texpack_load8(const char *dir, const char *level, int idx, int pal, int *w, int *h) {
    if (!dir || !level || !*level || pal < 0) return NULL;
    return load_any(dir, level, idx, pal, w, h, &g_last_tol);
}
/* re_texpack_load8_tol — v2.39: re_texpack_load8 for any thread: the page-check tolerance of the file goes to *tol instead of
   re_texpack_last_tol(). */
uint32_t *re_texpack_load8_tol(const char *dir, const char *level, int idx, int pal, int *w, int *h, double *tol) {
    double t = RE_TEXPACK_MAX_ERR;
    uint32_t *px = (!dir || !level || !*level || pal < 0) ? NULL : load_any(dir, level, idx, pal, w, h, &t);
    if (tol) *tol = t;
    return px;
}
/* re_texpack_pal8_rgba — Expand an 8-bit 256x256 page to RGBA through a BGRA palette (grey ramp when pal is NULL);
   alpha is always 255 (GR_TEXFMT_P_8 has no transparent index). */
void re_texpack_pal8_rgba(const uint8_t *idx, const uint8_t *pal, uint32_t *out) {
    for (int i = 0; i < 256 * 256; i++) {
        unsigned k = idx[i];
        uint32_t r = k, g = k, b = k;                   /* без палитры — серый по индексу (как прежде) */
        if (pal) { b = pal[k * 4]; g = pal[k * 4 + 1]; r = pal[k * 4 + 2]; }
        out[i] = 0xFF000000u | b << 16 | g << 8 | r;   /* GR_TEXFMT_P_8: альфа 255, прозрачного индекса нет */
    }
}
/* load_file — Read and decode one PNG file (max 64 MiB).  Only square power-of-two images 256..1024
   pixels wide are accepted. */
static uint32_t *load_file(const char *path, int *w, int *h) {
    FILE *f = fopen(path, "rb");
    if (!f) { RE_LOGT(load, "HD-пак: нет файла %s", path); return NULL; }
    fseek(f, 0, SEEK_END); long n = ftell(f); fseek(f, 0, SEEK_SET);
    if (n <= 0 || n > (64L << 20)) { RE_LOGW(load, "HD-пак: %s — размер %ld байт вне 1..64 МиБ, пропущен", path, n); fclose(f); return NULL; }
    unsigned char *b = (unsigned char *)malloc((size_t)n);
    if (!b || fread(b, 1, (size_t)n, f) != (size_t)n) { if (!b) RE_LOGE(mem, "HD-пак: malloc(%ld) для %s — NULL", n, path); else RE_LOGW(load, "HD-пак: %s — ошибка чтения", path); fclose(f); free(b); return NULL; }
    fclose(f);
    int x = 0, y = 0;
    uint32_t *px = re_texpack_decode_png(b, (int)n, &x, &y);
    free(b);
    if (!px) { RE_LOGW(load, "HD-пак: %s — PNG не декодируется (%s), пропущен", path, stbi_failure_reason() ? stbi_failure_reason() : "?"); return NULL; }
    if (x != y || x < 256 || x > 1024 || (x & (x - 1))) { RE_LOGW(load, "HD-пак: %s — %dx%d, нужен квадрат 256/512/1024, пропущен", path, x, y); free(px); return NULL; }
    RE_LOGT(load, "HD-пак: %s %dx%d загружен", path, x, y);
    *w = x; *h = y;
    return px;
}
/* среднее блока HD-картинки (sx×sy) в точке x,y страницы 256 */
/* block_avg — Average RGBA of the sx x sy block of the HD image that covers original texel (x, y). */
static void block_avg(const uint32_t *hd, int w, int sx, int sy, int x, int y, unsigned c[4]) {
    unsigned r = 0, g = 0, b = 0, a = 0;
    for (int dy = 0; dy < sy; dy++) for (int dx = 0; dx < sx; dx++) {
        uint32_t p = hd[(size_t)(y * sy + dy) * w + x * sx + dx];
        r += p & 255; g += (p >> 8) & 255; b += (p >> 16) & 255; a += p >> 24;
    }
    unsigned k = (unsigned)(sx * sy); c[0] = r / k; c[1] = g / k; c[2] = b / k; c[3] = a / k;
}
/* re_texpack_compare_rgba — Compare an HD image with a 256x256 RGBA reference: *err = mean absolute RGB difference per
   texel (0..255) of the block averages, *amis = fraction of texels whose alpha >= 128 differs. */
void re_texpack_compare_rgba(const uint32_t *hd, int w, int h, const uint32_t *ref, double *err, double *amis) {
    int sx = w / 256, sy = h / 256; double e = 0; long am = 0;
    for (int y = 0; y < 256; y++) for (int x = 0; x < 256; x++) {
        unsigned c[4]; block_avg(hd, w, sx, sy, x, y, c);
        uint32_t s = ref[y * 256 + x];
        if ((c[3] >= 128) != ((s >> 24) >= 128)) am++;
        e += (abs((int)c[0] - (int)(s & 255)) + abs((int)c[1] - (int)((s >> 8) & 255)) + abs((int)c[2] - (int)((s >> 16) & 255))) / 3.0;
    }
    if (err) *err = e / 65536.0;
    if (amis) *amis = (double)am / 65536.0;
}
/* re_texpack_merge — Check an HD image (w x w) against the original RGBA page and, if the error is at most
   RE_TEXPACK_MAX_ERR, replace its alpha with the original's (nearest texel).  Returns 1 when
   merged; 0 (and *err = -1 for a bad size) otherwise. */
int re_texpack_merge(const uint32_t *orig, uint32_t *hd, int w, double *err) { return re_texpack_merge_tol(orig, hd, w, RE_TEXPACK_MAX_ERR, err); }
/* re_texpack_merge_tol — re_texpack_merge with the error limit `tol` (re_texpack_last_tol() of the attached file). */
int re_texpack_merge_tol(const uint32_t *orig, uint32_t *hd, int w, double tol, double *err) { return re_texpack_merge_ex(orig, hd, w, tol, 0, err); }
/* re_texpack_merge_ex — re_texpack_merge_tol; keep_alpha (v2.36, files of the HUD overlay): the HD file's own alpha is kept
   (a smooth silhouette drawn at 4x — the alpha test then cuts a clean edge instead of the original's 4x4 steps) when, averaged
   back to 256, it disagrees with the original's alpha on at most RE_TEXPACK_MAX_AMIS of the texels; otherwise, and always
   without keep_alpha, the alpha is replaced by the original's (nearest texel). */
int re_texpack_merge_ex(const uint32_t *orig, uint32_t *hd, int w, double tol, int keep_alpha, double *err) {
    if (!orig || !hd || w < 256 || w > 1024 || (w & (w - 1))) { if (err) *err = -1; return 0; }
    double e = 0, am = 1; re_texpack_compare_rgba(hd, w, w, orig, &e, &am);
    if (err) *err = e;
    if (e > tol) return 0;
    if (keep_alpha && am <= RE_TEXPACK_MAX_AMIS) return 1;   /* своя альфа файла HUD (гладкий силуэт) */
    int s = w / 256;
    for (int y = 0; y < w; y++) for (int x = 0; x < w; x++) {
        uint32_t *p = &hd[(size_t)y * w + x];
        *p = (*p & 0x00FFFFFFu) | (orig[(y / s) * 256 + x / s] & 0xFF000000u);
    }
    return 1;
}
/* re_texpack_compare — As re_texpack_compare_rgba against a 16-bit ARGB1555 page (5-bit channels expanded to 8 bits).
   The colour error counts every texel, also transparent ones. */
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
