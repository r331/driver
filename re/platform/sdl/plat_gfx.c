/* v2.16: настройки графики (driver.cfg, RE_*) и обработка текстур без GL — см. plat_gfx.h */
#include "plat_gfx.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

static void scpy(char *d, const char *s, size_t n) { if (n) snprintf(d, n, "%s", s ? s : ""); }
static int ieq(const char *a, const char *b) { for (; *a && *b; a++, b++) if (tolower((unsigned char)*a) != tolower((unsigned char)*b)) return 0; return !*a && !*b; }

int re_gfx_preset(re_gfx_cfg *c, const char *name) {
    re_gfx_cfg k; memset(&k, 0, sizeof k);
    k.render_scale = 1.0; k.gamma = 1.0; k.brightness = 1.0; k.vsync = RE_VSYNC_ON; k.fullscreen = -1; k.hud_filter = RE_HUD_SHARP; k.fbo = 1;
    if (!name || ieq(name, "enhanced")) {
        scpy(k.preset, "enhanced", sizeof k.preset);
        k.msaa = 4; k.a2c = 1; k.fxaa = 0; k.aniso = 16; k.mipmaps = 1; k.dilate = 1; k.filter = RE_FILTER_TRILINEAR;
        k.draw_distance = 2.0;
    } else if (ieq(name, "original") || ieq(name, "safe")) {   /* как v2.15: билинейная без мипмапов, без сглаживания, HUD — линейно */
        scpy(k.preset, ieq(name, "safe") ? "safe" : "original", sizeof k.preset);
        if (ieq(name, "safe")) k.fbo = 0;   /* v2.24: safe — ещё и без FBO: игра рисует прямо в буфер окна, как v2.15 */
        k.msaa = 0; k.a2c = 0; k.fxaa = 0; k.aniso = 1; k.mipmaps = 0; k.dilate = 0; k.filter = RE_FILTER_LINEAR; k.hud_filter = RE_HUD_LINEAR;
        k.draw_distance = 1.0;
    } else return -1;
    /* окно/аспект/источник пресет не трогает */
    scpy(k.aspect, c->aspect, sizeof k.aspect); k.fullscreen = c->fullscreen; k.win_w = c->win_w; k.win_h = c->win_h;
    scpy(k.source, c->source, sizeof k.source);
    scpy(k.music_dir, c->music_dir, sizeof k.music_dir);   /* v2.22: и каталог музыки */
    k.game_res = c->game_res;                              /* v2.26: и разрешение кадра игры */
    *c = k; return 0;
}
void re_gfx_defaults(re_gfx_cfg *c) { memset(c, 0, sizeof *c); c->fullscreen = -1; re_gfx_preset(c, "enhanced"); }

static int pbool(const char *v, int *o) {
    if (ieq(v, "1") || ieq(v, "on") || ieq(v, "yes") || ieq(v, "true")) { *o = 1; return 0; }
    if (ieq(v, "0") || ieq(v, "off") || ieq(v, "no") || ieq(v, "false")) { *o = 0; return 0; }
    return -2;
}
static int pint(const char *v, int *o) { char *e; long x = strtol(v, &e, 10); if (e == v) return -2; while (*e == 'x' || *e == 'X' || isspace((unsigned char)*e)) e++; if (*e) return -2; *o = (int)x; return 0; }
static int pdbl(const char *v, double *o) { char *e; double x = strtod(v, &e); if (e == v || *e) return -2; *o = x; return 0; }

int re_gfx_set(re_gfx_cfg *c, const char *k, const char *v) {
    int b;
    if (ieq(k, "preset")) return re_gfx_preset(c, v) ? -2 : 0;
    if (ieq(k, "msaa")) { if (ieq(v, "off")) { c->msaa = 0; return 0; } return pint(v, &c->msaa); }
    if (ieq(k, "a2c") || ieq(k, "alpha_to_coverage")) return pbool(v, &c->a2c);
    if (ieq(k, "fxaa")) return pbool(v, &c->fxaa);
    if (ieq(k, "aniso")) { if (ieq(v, "off")) { c->aniso = 1; return 0; } return pint(v, &c->aniso); }
    if (ieq(k, "mipmaps")) return pbool(v, &c->mipmaps);
    if (ieq(k, "dilate")) return pbool(v, &c->dilate);
    if (ieq(k, "filter")) {
        if (ieq(v, "nearest") || ieq(v, "point")) c->filter = RE_FILTER_NEAREST;
        else if (ieq(v, "linear") || ieq(v, "bilinear")) c->filter = RE_FILTER_LINEAR;
        else if (ieq(v, "trilinear")) c->filter = RE_FILTER_TRILINEAR;
        else return -2;
        return 0;
    }
    if (ieq(k, "hud_filter")) {
        if (ieq(v, "nearest")) c->hud_filter = RE_HUD_NEAREST;
        else if (ieq(v, "linear")) c->hud_filter = RE_HUD_LINEAR;
        else if (ieq(v, "sharp") || ieq(v, "sharp-bilinear") || ieq(v, "sharp_bilinear")) c->hud_filter = RE_HUD_SHARP;
        else return -2;
        return 0;
    }
    if (ieq(k, "render_scale")) return pdbl(v, &c->render_scale);
    if (ieq(k, "draw_distance")) { if (ieq(v, "original") || ieq(v, "off")) { c->draw_distance = 1.0; return 0; } return pdbl(v, &c->draw_distance); }
    if (ieq(k, "vsync")) {
        if (ieq(v, "adaptive")) { c->vsync = RE_VSYNC_ADAPTIVE; return 0; }
        if (pbool(v, &b)) return -2;
        c->vsync = b; return 0;
    }
    if (ieq(k, "fps_limit")) { if (ieq(v, "off")) { c->fps_limit = 0; return 0; } return pint(v, &c->fps_limit); }
    if (ieq(k, "gamma")) return pdbl(v, &c->gamma);
    if (ieq(k, "brightness")) return pdbl(v, &c->brightness);
    if (ieq(k, "sharpen")) return pdbl(v, &c->sharpen);
    if (ieq(k, "music_dir")) { if (strlen(v) >= sizeof c->music_dir) return -2; scpy(c->music_dir, v, sizeof c->music_dir); return 0; }   /* v2.22 */
    if (ieq(k, "texpack")) { if (strlen(v) >= sizeof c->texpack) return -2; scpy(c->texpack, v, sizeof c->texpack); return 0; }
    if (ieq(k, "aspect")) { if (strlen(v) >= sizeof c->aspect) return -2; scpy(c->aspect, v, sizeof c->aspect); return 0; }
    if (ieq(k, "fbo")) { if (ieq(v, "auto")) { c->fbo = 1; return 0; } return pbool(v, &c->fbo); }   /* v2.24 */
    if (ieq(k, "game_res")) {   /* v2.26: native (640×480 внутри, по умолчанию) | original (режим из меню/config.dat игры) */
        if (ieq(v, "native") || ieq(v, "auto") || ieq(v, "640x480")) { c->game_res = 0; return 0; }
        if (ieq(v, "original") || ieq(v, "game")) { c->game_res = 1; return 0; }
        return -2;
    }
    if (ieq(k, "fullscreen")) {   /* v2.24: + desktop / exclusive */
        if (ieq(v, "desktop")) { c->fullscreen = 1; return 0; }
        if (ieq(v, "exclusive")) { c->fullscreen = 2; return 0; }
        if (pbool(v, &b)) return -2; c->fullscreen = b; return 0;
    }
    if (ieq(k, "windowed_res")) {
        int w = 0, h = 0; char x = 0;
        if (sscanf(v, "%d%c%d", &w, &x, &h) != 3 || (x != 'x' && x != 'X') || w < 160 || h < 120 || w > 16384 || h > 16384) return -2;
        c->win_w = w; c->win_h = h; return 0;
    }
    return -1;
}

static void trim(char *s) {
    char *p = s; while (isspace((unsigned char)*p)) p++;
    memmove(s, p, strlen(p) + 1);
    size_t n = strlen(s); while (n && isspace((unsigned char)s[n - 1])) s[--n] = 0;
    if (n >= 2 && s[0] == '"' && s[n - 1] == '"') { memmove(s, s + 1, n - 2); s[n - 2] = 0; }
}
int re_gfx_parse(re_gfx_cfg *c, const char *text, void (*err)(const char *msg)) {
    int errs = 0;
    if (!text) return 0;
    for (int pass = 0; pass < 2; pass++) {   /* 0 — preset, 1 — остальные ключи */
        const char *p = text; int line = 0;
        while (*p) {
            const char *e = p; while (*e && *e != '\n') e++;
            char buf[256]; size_t n = (size_t)(e - p); if (n >= sizeof buf) n = sizeof buf - 1;
            memcpy(buf, p, n); buf[n] = 0; line++;
            p = *e ? e + 1 : e;
            char *h = strpbrk(buf, "#;"); if (h) *h = 0;
            trim(buf); if (!buf[0]) continue;
            if (buf[0] == '[') continue;   /* [graphics] — секции допускаются и игнорируются */
            char *eq = strchr(buf, '=');
            if (!eq) { if (pass == 1) { errs++; if (err) { char m[320]; snprintf(m, sizeof m, "driver.cfg:%d: нет '=': %s", line, buf); err(m); } } continue; }
            *eq = 0; char *k = buf, *v = eq + 1; trim(k); trim(v);
            int isp = ieq(k, "preset");
            if ((pass == 0) != isp) continue;
            int r = re_gfx_set(c, k, v);
            if (r) { errs++; if (err) { char m[320]; snprintf(m, sizeof m, "driver.cfg:%d: %s '%s'%s%s", line, r == -1 ? "неизвестный ключ" : "плохое значение", k, r == -2 ? " = " : "", r == -2 ? v : ""); err(m); } }
        }
    }
    re_gfx_clamp(c);
    return errs;
}
int re_gfx_env(re_gfx_cfg *c, const char *(*g)(const char *)) {
    static const char *map[][2] = { { "RE_MSAA", "msaa" }, { "RE_A2C", "a2c" }, { "RE_FXAA", "fxaa" }, { "RE_ANISO", "aniso" },
        { "RE_MIPMAPS", "mipmaps" }, { "RE_DILATE", "dilate" }, { "RE_FILTER", "filter" }, { "RE_HUD_FILTER", "hud_filter" },
        { "RE_RENDER_SCALE", "render_scale" }, { "RE_VSYNC", "vsync" }, { "RE_FPS_LIMIT", "fps_limit" }, { "RE_GAMMA", "gamma" },
        { "RE_BRIGHTNESS", "brightness" }, { "RE_SHARPEN", "sharpen" }, { "RE_TEXPACK", "texpack" }, { "RE_DRAW_DIST", "draw_distance" }, { "RE_FBO", "fbo" }, { "RE_GAME_RES", "game_res" } };
    int errs = 0; const char *v;
    if (!g) return 0;
    if ((v = g("RE_PRESET")) && *v && re_gfx_preset(c, v)) errs++;
    for (size_t i = 0; i < sizeof map / sizeof map[0]; i++)
        if ((v = g(map[i][0])) && *v && re_gfx_set(c, map[i][1], v)) errs++;
    re_gfx_clamp(c);
    return errs;
}
void re_gfx_clamp(re_gfx_cfg *c) {
    int m = c->msaa; c->msaa = m >= 8 ? 8 : m >= 4 ? 4 : m >= 2 ? 2 : 0;
    if (c->aniso < 1) c->aniso = 1;
    if (c->aniso > 16) c->aniso = 16;
    if (c->filter < 0 || c->filter > 2) c->filter = RE_FILTER_LINEAR;
    if (c->hud_filter < 0 || c->hud_filter > 2) c->hud_filter = RE_HUD_SHARP;
    if (!(c->render_scale >= 0.5)) c->render_scale = c->render_scale > 0 ? 0.5 : 1.0;
    if (c->render_scale > 2.0) c->render_scale = 2.0;
    if (c->vsync < -1 || c->vsync > 1) c->vsync = RE_VSYNC_ON;
    if (c->fps_limit < 0) c->fps_limit = 0;
    if (c->fps_limit > 1000) c->fps_limit = 1000;
    if (!(c->gamma >= 0.5)) c->gamma = c->gamma > 0 ? 0.5 : 1.0;
    if (c->gamma > 2.5) c->gamma = 2.5;
    if (!(c->brightness >= 0.5)) c->brightness = c->brightness > 0 ? 0.5 : 1.0;
    if (c->brightness > 2.0) c->brightness = 2.0;
    if (!(c->sharpen >= 0)) c->sharpen = 0;
    if (c->sharpen > 1) c->sharpen = 1;
    c->fbo = c->fbo != 0;
    if (c->fullscreen < -1 || c->fullscreen > 2) c->fullscreen = 1;
    if (!(c->draw_distance >= 1.0)) c->draw_distance = 1.0;
    if (c->draw_distance > 4.0) c->draw_distance = 4.0;
    c->a2c = c->a2c != 0; c->fxaa = c->fxaa != 0; c->mipmaps = c->mipmaps != 0; c->dilate = c->dilate != 0;
}
const char *re_gfx_describe(const re_gfx_cfg *c, char *b, int n) {
    static const char *fl[] = { "nearest", "linear", "trilinear" }, *hf[] = { "nearest", "linear", "sharp" };
    snprintf(b, (size_t)n, "preset %s: msaa %d a2c %d fxaa %d aniso %d mipmaps %d dilate %d filter %s hud_filter %s render_scale %.2f vsync %s fps_limit %d gamma %.2f brightness %.2f sharpen %.2f draw_distance %.2f fbo %d game_res %s aspect %s fullscreen %d windowed_res %dx%d texpack %s cfg %s",
             c->preset, c->msaa, c->a2c, c->fxaa, c->aniso, c->mipmaps, c->dilate, fl[c->filter], hf[c->hud_filter], c->render_scale,
             c->vsync == RE_VSYNC_ADAPTIVE ? "adaptive" : c->vsync ? "on" : "off", c->fps_limit, c->gamma, c->brightness, c->sharpen, c->draw_distance, c->fbo, c->game_res ? "original" : "native",
             c->aspect[0] ? c->aspect : "-", c->fullscreen, c->win_w, c->win_h, c->texpack[0] ? c->texpack : "-", c->source[0] ? c->source : "-");
    return b;
}

static re_gfx_cfg g_cfg; static int g_cfg_init;
re_gfx_cfg *re_gfx(void) { if (!g_cfg_init) { re_gfx_defaults(&g_cfg); g_cfg_init = 1; } return &g_cfg; }
static const char *env_get(const char *n) { return getenv(n); }
static char *slurp(const char *path) {
    FILE *f = fopen(path, "rb"); if (!f) return NULL;
    char *b = (char *)malloc(65537); if (!b) { fclose(f); return NULL; }
    size_t n = fread(b, 1, 65536, f); fclose(f); b[n] = 0; return b;
}
int re_gfx_load(const char *exe_dir, const char *user_dir, void (*err)(const char *msg)) {
    re_gfx_cfg *c = re_gfx(); char path[512]; char *text = NULL; int errs = 0;
    const char *e = getenv("RE_CFG");
    if (e && *e) { scpy(path, e, sizeof path); text = slurp(path); }
    if (!text && exe_dir && *exe_dir) { snprintf(path, sizeof path, "%s%sdriver.cfg", exe_dir, exe_dir[strlen(exe_dir) - 1] == '/' ? "" : "/"); text = slurp(path); }
    if (!text && user_dir && *user_dir) { snprintf(path, sizeof path, "%s%sdriver.cfg", user_dir, user_dir[strlen(user_dir) - 1] == '/' ? "" : "/"); text = slurp(path); }
    if (text) { scpy(c->source, path, sizeof c->source); errs += re_gfx_parse(c, text, err); free(text); }
    errs += re_gfx_env(c, env_get);
    return errs;
}

/* ===== текстуры ===== */
#define CA(p) ((p) >> 24)
int re_gfx_dilate(uint32_t *px, int w, int h, int max_pass) {
    if (!px || w <= 0 || h <= 0) return 0;
    size_t n = (size_t)w * h; int filled = 0;
    unsigned char *known = (unsigned char *)malloc(n); if (!known) return 0;
    double sr = 0, sg = 0, sb = 0; size_t no = 0, left = 0;
    for (size_t i = 0; i < n; i++) {
        known[i] = CA(px[i]) != 0;
        if (known[i]) { sr += px[i] & 255; sg += (px[i] >> 8) & 255; sb += (px[i] >> 16) & 255; no++; } else left++;
    }
    if (!no || !left) { free(known); return 0; }
    unsigned char *nk = (unsigned char *)malloc(n); uint32_t *out = (uint32_t *)malloc(n * 4);
    if (!nk || !out) { free(known); free(nk); free(out); return 0; }
    for (int pass = 0; pass < max_pass && left; pass++) {
        memcpy(nk, known, n); memcpy(out, px, n * 4); int ch = 0;
        for (int y = 0; y < h; y++) for (int x = 0; x < w; x++) {
            size_t i = (size_t)y * w + x; if (known[i]) continue;
            unsigned r = 0, g = 0, b = 0, k = 0;
            for (int dy = -1; dy <= 1; dy++) for (int dx = -1; dx <= 1; dx++) {
                int xx = x + dx, yy = y + dy; if ((!dx && !dy) || xx < 0 || yy < 0 || xx >= w || yy >= h) continue;
                size_t j = (size_t)yy * w + xx; if (!known[j]) continue;
                r += px[j] & 255; g += (px[j] >> 8) & 255; b += (px[j] >> 16) & 255; k++;
            }
            if (!k) continue;
            out[i] = ((r + k / 2) / k) | ((g + k / 2) / k) << 8 | ((b + k / 2) / k) << 16 | (px[i] & 0xFF000000u);
            nk[i] = 1; ch++;
        }
        memcpy(px, out, n * 4); memcpy(known, nk, n); left -= (size_t)ch; filled += ch;
        if (!ch) break;
    }
    if (left) {   /* дальние прозрачные пиксели — средний цвет непрозрачных */
        uint32_t avg = (uint32_t)(sr / no + 0.5) | (uint32_t)(sg / no + 0.5) << 8 | (uint32_t)(sb / no + 0.5) << 16;
        for (size_t i = 0; i < n; i++) if (!known[i]) { px[i] = avg | (px[i] & 0xFF000000u); filled++; }
    }
    free(known); free(nk); free(out); return filled;
}
double re_gfx_coverage(const uint32_t *px, int w, int h, int ref) {
    size_t n = (size_t)w * h, k = 0; if (!n) return 0;
    for (size_t i = 0; i < n; i++) k += (int)CA(px[i]) >= ref;
    return (double)k / n;
}
int re_gfx_has_partial_alpha(const uint32_t *px, int w, int h) {
    size_t n = (size_t)w * h; for (size_t i = 0; i < n; i++) if (CA(px[i]) != 255) return 1;
    return 0;
}
void re_gfx_mip_next(const uint32_t *s, int w, int h, uint32_t *d, double cov, int ref) {
    int nw = w > 1 ? w / 2 : 1, nh = h > 1 ? h / 2 : 1;
    unsigned char *al = (unsigned char *)malloc((size_t)nw * nh);
    for (int y = 0; y < nh; y++) for (int x = 0; x < nw; x++) {
        double r = 0, g = 0, b = 0, a = 0, ur = 0, ug = 0, ub = 0; int k = 0;
        for (int dy = 0; dy < 2; dy++) for (int dx = 0; dx < 2; dx++) {
            int xx = x * 2 + dx, yy = y * 2 + dy; if (xx >= w) xx = w - 1; if (yy >= h) yy = h - 1;
            uint32_t p = s[(size_t)yy * w + xx]; double pa = CA(p);
            r += (p & 255) * pa; g += ((p >> 8) & 255) * pa; b += ((p >> 16) & 255) * pa; a += pa;
            ur += p & 255; ug += (p >> 8) & 255; ub += (p >> 16) & 255; k++;
        }
        uint32_t o;
        if (a > 0) o = (uint32_t)(r / a + 0.5) | (uint32_t)(g / a + 0.5) << 8 | (uint32_t)(b / a + 0.5) << 16;
        else o = (uint32_t)(ur / k + 0.5) | (uint32_t)(ug / k + 0.5) << 8 | (uint32_t)(ub / k + 0.5) << 16;   /* прозрачный блок: уже dilated цвет */
        int ai = (int)(a / k + 0.5); if (al) al[(size_t)y * nw + x] = (unsigned char)ai;
        d[(size_t)y * nw + x] = o | (uint32_t)ai << 24;
    }
    if (al && cov >= 0) {   /* сохранение покрытия: множитель альфы, при котором доля alpha >= ref ≈ cov (бинарный поиск) */
        size_t n = (size_t)nw * nh; double lo = 0.0, hi = 8.0;
        for (int it = 0; it < 16; it++) {
            double m = (lo + hi) / 2; size_t k = 0;
            for (size_t i = 0; i < n; i++) k += al[i] * m >= ref;
            if ((double)k / n > cov) hi = m; else lo = m;
        }
        size_t kl = 0, kh = 0; for (size_t i = 0; i < n; i++) { kl += al[i] * lo >= ref; kh += al[i] * hi >= ref; }
        double m = fabs((double)kl / n - cov) < fabs((double)kh / n - cov) ? lo : hi;   /* ближе к покрытию; поровну — больше */
        for (size_t i = 0; i < n; i++) { double v = al[i] * m; int ai = v > 255 ? 255 : (int)(v + 0.5); d[i] = (d[i] & 0xFFFFFFu) | (uint32_t)ai << 24; }
    }
    free(al);
}
void re_gfx_mip_box(const uint32_t *s, int w, int h, uint32_t *d) {
    int nw = w > 1 ? w / 2 : 1, nh = h > 1 ? h / 2 : 1;
    for (int y = 0; y < nh; y++) for (int x = 0; x < nw; x++) {
        unsigned acc[4] = { 0, 0, 0, 0 };
        for (int dy = 0; dy < 2; dy++) for (int dx = 0; dx < 2; dx++) {
            int xx = x * 2 + dx, yy = y * 2 + dy; if (xx >= w) xx = w - 1; if (yy >= h) yy = h - 1;
            uint32_t p = s[(size_t)yy * w + xx]; for (int k = 0; k < 4; k++) acc[k] += (p >> (8 * k)) & 255;
        }
        d[(size_t)y * nw + x] = ((acc[0] + 2) / 4) | ((acc[1] + 2) / 4) << 8 | ((acc[2] + 2) / 4) << 16 | ((acc[3] + 2) / 4) << 24;
    }
}
