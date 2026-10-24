/* SDL-вариант объектов DirectDraw/Direct3D: учётные записи без устройства.
   Игровой код (game/ported24.c) работает с дескрипторами; реальное окно/буфер даёт plat_render.c. */
/* plat_dd.c (English overview) — native stand-ins for the DirectDraw / Direct3D / DirectSound /
   DirectShow COM objects the game creates.  Objects are small tagged records (dd_obj).  In the game
   (g_game_present) surfaces own pixel memory with a synthetic 32-bit address for lpSurface, textures are
   converted to RGBA and uploaded to GL on use, the back buffer's LFB writes are overlaid at Flip, and
   DirectSound buffers are forwarded to the software mixer (plat_dsmix.c, DSG()).  Without the game
   (selftest) every call is only recorded so tests can inspect the last call ("stub stats"). */
#include "../plat.h"
#include "plat_texpack.h"
#include "../../game/reprof.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct dd_obj { uint32_t tag; int32_t lost; int32_t attached; int32_t clipper; int32_t w, h;
    /* v2.01: игра (g_game_present) — поверхность с памятью пикселей */
    uint8_t *px; int32_t pitch, bpp; uint32_t pf[8]; uint32_t addr; int gltex, dirty, role; uint32_t caps;
    struct dd_obj *surf; struct dd_obj *pal; uint8_t pal_rgba[256 * 4]; uint32_t ck_lo, ck_hi; int has_ck;
    uint32_t *hd; int hdw, hd_page, hd_pal; double hd_tol; int hd_hud;     /* v2.18: HD-картинка страницы из пака (plat_dd_attach_hd), 16 бит */
    int page8; uint64_t page8_key; } dd_obj;      /* v2.18: поверхность PAL8 со страницей уровня (plat_dd_tag_page8), -1 — нет */
static int g_game_present;   /* v2.00: 1 — игра (plat_dd_stub_enum с 0x100): Flip показывает кадр GL; v2.01: поверхности с памятью */
/* v2.01: адрес памяти поверхности для 32-битного поля lpSurface (game/reptr.c — синтетический адрес 0x80000000+) */
uint32_t re_ptr_register_dyn(void *native, uint32_t size);
void     re_ptr_unregister(const void *native);
static int g_trace_dd = -1;
static int trace_dd(void) { if (g_trace_dd < 0) { const char *e = getenv("RE_TRACE_DD"); g_trace_dd = e && *e && *e != '0'; } return g_trace_dd; }
static uint32_t g_desc[31]; static int g_desc_n; static void *g_tex; static int g_tex_stage, g_pal_entries, g_pal_changed;
static int g_live; static uint32_t g_coop_flags;
static int32_t g_fill[4]; static uint32_t g_fill_px; static int g_fill_n;
/* v2.09: DirectSound в игре — plat_dsmix.c */
int dsm_is(const void *o); int32_t dsm_create_buffer(uint32_t fl, uint32_t bytes, const void *wfx, void **out);
int32_t dsm_duplicate(void *src, void **out); void *dsm_qi(void *o); void dsm_release(void *o);
int32_t dsm_lock(void *o, uint32_t bytes, void **p1, uint32_t *n1, void **p2, uint32_t *n2);
int32_t dsm_play(void *o, uint32_t fl); int32_t dsm_stop(void *o); int32_t dsm_set_position(void *o, uint32_t pos);
int32_t dsm_set_volume(void *o, int32_t v); int32_t dsm_set_frequency(void *o, uint32_t hz); int32_t dsm_get_status(void *o, uint32_t *st);
int32_t dsm_3d_mode(void *o, uint32_t m); int32_t dsm_3d_pos(void *o, float x, float y, float z);
void dsm_listener_pos(float x, float y, float z); void dsm_listener_orient(const float *s); void dsm_listener_factors(int which, float v);
#define DSG(o) (g_game_present && dsm_is(o))
void plat_snd_open_game(void);
static void *mk(uint32_t tag) { dd_obj *o = (dd_obj *)calloc(1, sizeof *o); if (o) { o->tag = tag; g_live++; } return o; }

/* ===== v2.01: поверхности DirectDraw в памяти (только игра, g_game_present; тесты — прежние учётные заглушки) =====
   Поверхность: w×h, pitch = w·bpp/8 (выровнено на 4), формат пикселей — из DDSURFACEDESC2 (+0x48, флаг DDSD_PIXELFORMAT 0x1000),
   иначе формат экрана (16 бит RGB565). Lock отдаёт lpSurface (desc[9]) — синтетический 32-битный адрес (re_ptr_register_dyn),
   pitch (desc[4]), размеры и формат. Текстура Direct3D (QueryInterface IID_IDirect3DTexture2) — объект tag 6 со ссылкой на
   поверхность; plat_set_texture → при изменённой памяти перевод в RGBA (маски формата, PAL8 — палитра поверхности,
   цветовой ключ — альфа 0) и загрузка в GL (plat_tex_update), затем plat_tex_bind. Первичная/задняя поверхность: 3D рисуется
   прямо в GL-кадр; запись в заднюю через Lock (LFB) накладывается на кадр при Flip (пиксель 0 — прозрачный), память затем
   обнуляется; Blt COLORFILL задней — очистка прямоугольника GL. */
/* --- (en) In-memory DirectDraw surfaces (game only): pixel format, RGBA conversion, GL upload, present. --- */
enum { ROLE_TEX = 0, ROLE_PRIMARY = 1, ROLE_BACK = 2, ROLE_Z = 3 };
static int g_scr_w = 640, g_scr_h = 480;
static const uint32_t k_pf565[8] = { 0x20, 0x40, 0, 16, 0xf800, 0x7e0, 0x1f, 0 };
static int g_tr_n;
#define TR(...) do { if (trace_dd() && g_tr_n < 400) { g_tr_n++; fprintf(stderr, "[dd] " __VA_ARGS__); } } while (0)
static int gs_alloc(dd_obj *o) {
    if (o->w <= 0 || o->h <= 0 || o->w > 4096 || o->h > 4096) { RE_LOGW(render, "DirectDraw: поверхность %dx%d вне 1..4096 — без памяти пикселей", o->w, o->h); return 0; }
    o->bpp = (int32_t)o->pf[3]; if (o->bpp != 8 && o->bpp != 16 && o->bpp != 24 && o->bpp != 32) o->bpp = 16;
    o->pitch = ((o->w * o->bpp / 8) + 3) & ~3;
    o->px = (uint8_t *)calloc((size_t)o->pitch * (size_t)o->h, 1); if (!o->px) { RE_LOGE(mem, "DirectDraw: calloc поверхности %dx%d (%d бит) — NULL", o->w, o->h, o->bpp); return 0; }
    o->addr = re_ptr_register_dyn(o->px, (uint32_t)(o->pitch * o->h));
    o->page8 = -1; o->dirty = 1; return 1;
}
static uint8_t mask8(uint32_t v, uint32_t m) {
    if (!m) return 0;
    int sh = 0; while (!((m >> sh) & 1)) sh++; uint32_t mm = m >> sh, x = (v & m) >> sh;
    return (uint8_t)(mm ? (x * 255u + mm / 2) / mm : 0);
}
static uint32_t gs_raw(const dd_obj *o, const uint8_t *p) {
    switch (o->bpp) { case 8: return p[0]; case 16: return (uint32_t)p[0] | (uint32_t)p[1] << 8;
    case 24: return (uint32_t)p[0] | (uint32_t)p[1] << 8 | (uint32_t)p[2] << 16;
    default: return (uint32_t)p[0] | (uint32_t)p[1] << 8 | (uint32_t)p[2] << 16 | (uint32_t)p[3] << 24; }
}
/* v2.38 (performance): mask8 with the mask's shift found once per surface instead of per pixel and channel */
typedef struct { uint32_t m, sh, mm; } mask_t;
static mask_t mask_prep(uint32_t m) { mask_t r = { m, 0, 0 }; if (m) { while (!((m >> r.sh) & 1)) r.sh++; r.mm = m >> r.sh; } return r; }
static inline uint8_t mask8p(uint32_t v, const mask_t *k) {   /* == mask8(v, k->m) */
    if (!k->m) return 0;
    uint32_t x = (v & k->m) >> k->sh;
    return (uint8_t)(k->mm ? (x * 255u + k->mm / 2) / k->mm : 0);
}
/* RGBA (байты r,g,b,a в памяти), overlay: пиксель 0 — альфа 0 */
static uint32_t *gs_to_rgba(const dd_obj *o, int overlay) {
    uint32_t *out = (uint32_t *)malloc((size_t)o->w * (size_t)o->h * 4); if (!out) { RE_LOGE(mem, "DirectDraw: malloc RGBA %dx%d — NULL, поверхность не загружена в GL", o->w, o->h); return NULL; }
    int alpha = (o->pf[1] & 1) && o->pf[7];
    const uint8_t *pal = o->pal ? o->pal->pal_rgba : NULL;
    const mask_t kr = mask_prep(o->pf[4]), kg = mask_prep(o->pf[5]), kb = mask_prep(o->pf[6]), ka = mask_prep(o->pf[7]);
    for (int y = 0; y < o->h; y++) {
        const uint8_t *row = o->px + (size_t)y * o->pitch;
        for (int x = 0; x < o->w; x++) {
            uint32_t v = gs_raw(o, row + x * (o->bpp / 8)); uint8_t r, g, b, a;
            if (o->bpp == 8) { if (pal) { r = pal[v * 4]; g = pal[v * 4 + 1]; b = pal[v * 4 + 2]; } else r = g = b = (uint8_t)v; a = 255; }
            else { r = mask8p(v, &kr); g = mask8p(v, &kg); b = mask8p(v, &kb); a = alpha ? mask8p(v, &ka) : 255; }
            if (o->has_ck && v >= o->ck_lo && v <= o->ck_hi) a = 0;
            if (overlay) a = v ? 255 : 0;
            out[(size_t)y * o->w + x] = (uint32_t)r | (uint32_t)g << 8 | (uint32_t)b << 16 | (uint32_t)a << 24;
        }
    }
    return out;
}
/* v2.18: HD-пак в игре. 16 бит: картинка прикрепляется к поверхности слота и при загрузке в GL сверяется с её памятью
   (re_texpack_merge). PAL8: поверхность помечена страницей; при рисовании поставщик (game/ported86.c) по странице и текущей палитре
   поверхности отдаёт готовую GL-текстуру пары (страница, палитра) — смена палитры не требует перезагрузки. Запись в поверхность
   (Unlock) снимает и картинку, и пометку: код слота ставит их заново после своей загрузки. */
static int g_hd_up, g_hd_rej, g_hd_att, g_pal8_bind;
static plat_pal8_provider g_pal8_prov;
void plat_dd_set_pal8_provider(plat_pal8_provider fn) { g_pal8_prov = fn; }
static int is_surf(void *v) { return v && g_game_present && !dsm_is(v) && ((dd_obj *)v)->px; }
void plat_dd_attach_hd(void *v, uint32_t *rgba, int w, int page, int pal) {
    dd_obj *o = (dd_obj *)v;
    if (!is_surf(v)) { free(rgba); return; }
    if (!rgba) { if (o->hd) { free(o->hd); o->hd = NULL; o->dirty = 1; } return; }   /* снять (в слоте другая страница) */
    free(o->hd); o->hd = rgba; o->hdw = w; o->hd_page = page; o->hd_pal = pal; o->hd_tol = re_texpack_last_tol(); o->hd_hud = re_texpack_last_hud(); o->dirty = 1; g_hd_att++;   /* v2.36: порог сверки файла (HUD шире) */
}
void plat_dd_tag_page8(void *v, int page, uint64_t key) { dd_obj *o = (dd_obj *)v; if (!is_surf(v) || o->bpp != 8) return; o->page8 = page; o->page8_key = key; }
void plat_dd_hd_stats(int *att, int *up, int *rej, int *pal8) { if (att) *att = g_hd_att; if (up) *up = g_hd_up; if (rej) *rej = g_hd_rej; if (pal8) *pal8 = g_pal8_bind; }
static void gs_upload_(dd_obj *o, int overlay);
static void gs_upload(dd_obj *o, int overlay) {   /* profiled wrapper (RE_PROFILE) */
    if (!o->px || !o->dirty) return;
    RP_BEGIN(RP_TEX_UPLOAD); RP_COUNT(RC_SURF_UPLOADS, 1); gs_upload_(o, overlay); RP_END(RP_TEX_UPLOAD);
}
static void gs_upload_(dd_obj *o, int overlay) {
    if (!o->px || !o->dirty) return;
    uint32_t *rgba = gs_to_rgba(o, overlay); if (!rgba) return;
    if (trace_dd()) { int nz = 0, pz = 0; for (int i = 0; i < o->pitch * o->h; i++) nz += o->px[i] != 0;
        if (o->pal) for (int i = 0; i < 1024; i++) pz += o->pal->pal_rgba[i] != 0;
        TR("upload %p %dx%d bpp %d nz %d pal %p palnz %d rgba0 %08x mid %08x\n", (void *)o, o->w, o->h, o->bpp, nz, (void *)o->pal, pz, rgba[0], rgba[o->w * o->h / 2 + o->w / 2]); }
    if (o->hd && o->w == 256 && o->h == 256 && !overlay) {   /* v2.18: HD из пака — если память поверхности всё ещё та страница */
        double e = 0;
        if (re_texpack_merge_ex(rgba, o->hd, o->hdw, o->hd_tol, o->hd_hud, &e)) {   /* v2.36: файл HUD — своя гладкая альфа */
            if (o->gltex) plat_tex_update(o->gltex, o->hdw, o->hdw, o->hd); else o->gltex = plat_tex_create(o->hdw, o->hdw, o->hd);
            g_hd_up++; RE_LOGT(load, "HD-пак: страница %d (палитра %d) → GL %dx%d, ошибка сверки %.1f", o->hd_page, o->hd_pal, o->hdw, o->hdw, e); free(rgba); o->dirty = 0; return;
        }
        plat_log("[texpack] игра: HD страницы %d отклонён: не похож на загруженную страницу (ошибка %.1f)\n", o->hd_page, e);
        RE_LOGW(load, "HD-пак: страница %d (палитра %d%s) отклонена при загрузке в GL — не похожа на страницу в памяти (ошибка %.1f > порога %.1f)", o->hd_page, o->hd_pal, o->hd_hud ? ", HUD" : "", e, o->hd_tol);
        free(o->hd); o->hd = NULL; g_hd_rej++;
    }
    if (o->gltex) plat_tex_update(o->gltex, o->w, o->h, rgba); else o->gltex = plat_tex_create(o->w, o->h, rgba);
    { static int atdbg = -1; if (atdbg < 0) atdbg = getenv("RE_ATDBG") != NULL; if (atdbg) { int a0 = 0, a255 = 0, nz = 0; for (int i = 0; i < o->w * o->h; i++) { unsigned a = rgba[i] >> 24; a0 += a == 0; a255 += a == 255; nz += (rgba[i] & 0xffffff) != 0; }
        fprintf(stderr, "[tex] gl %d %dx%d bpp %d pf %08x masks %08x %08x %08x %08x ck %d %x-%x a0 %d a255 %d nz %d\n", o->gltex, o->w, o->h, o->bpp, o->pf[1], o->pf[4], o->pf[5], o->pf[6], o->pf[7],
            o->has_ck, o->ck_lo, o->ck_hi, a0, a255, nz); } }
    free(rgba); o->dirty = 0;
}
static dd_obj *g_gs_back, *g_gs_primary;
static void gs_present(void) {
    dd_obj *b = g_gs_back;
    if (b && b->px && b->dirty) {   /* LFB-запись в заднюю поверхность — поверх кадра */
        gs_upload(b, 1);
        if (b->gltex) plat_blit2d(b->gltex, 0, 0, b->w, b->h, 0, 0);
        memset(b->px, 0, (size_t)b->pitch * b->h); b->dirty = 0;
    }
    plat_flip();
}
void *plat_dd_create_surface(void *dd, const void *desc) {
    if (!dd || !desc) return NULL;
    dd_obj *o = (dd_obj *)mk(1); if (!o) return NULL;
    memcpy(g_desc, desc, sizeof g_desc); g_desc_n++;
    if (g_desc[1] & 6) { o->h = (int32_t)g_desc[2]; o->w = (int32_t)g_desc[3]; }
    if (g_game_present) {
        o->caps = g_desc[26];
        memcpy(o->pf, (g_desc[1] & 0x1000) ? &g_desc[18] : k_pf565, 32);
        if (g_desc[1] & 0x10000) { o->has_ck = 1; o->ck_lo = g_desc[16]; o->ck_hi = g_desc[17]; }
        if (o->caps & 0x200) { o->role = ROLE_PRIMARY; o->w = g_scr_w; o->h = g_scr_h; g_gs_primary = o; }
        else if (o->caps & 0x20000) o->role = ROLE_Z;
        if (o->role != ROLE_Z) gs_alloc(o);
        RE_LOGT(render, "DirectDraw: поверхность %dx%d, %d бит, роль %d, caps 0x%x", o->w, o->h, o->bpp, o->role, o->caps);
        TR("create %p %dx%d bpp %d flags %x caps %x pf %x/%x masks %x %x %x %x role %d addr %08x\n", (void *)o, o->w, o->h, o->bpp,
           g_desc[1], o->caps, o->pf[1], o->pf[3], o->pf[4], o->pf[5], o->pf[6], o->pf[7], o->role, o->addr);
    }
    return o;
}
int32_t plat_dd_set_display_mode(void *dd, int w, int h, int bpp) { (void)bpp; if (dd && w > 0 && h > 0) { g_scr_w = w; g_scr_h = h; RE_LOGI(render, "игра: режим экрана %dx%d, %d бит (SetDisplayMode)", w, h, bpp); } return dd ? 0 : -1; }
void *plat_dd_create_clipper(void *dd) { return dd ? mk(2) : NULL; }
int32_t plat_dd_set_clipper(void *s, void *c) { if (!s || !c) return -1; ((dd_obj *)s)->clipper = 1; return 0; }
int32_t plat_dd_attach_surface(void *s, void *a) { if (!s || !a) return -1; ((dd_obj *)s)->attached++; return 0; }
void *plat_dd_get_attached(void *s, uint32_t caps) {
    (void)caps; if (!s) return NULL;
    dd_obj *o = (dd_obj *)mk(1);
    if (o && g_game_present) {   /* v2.01: задняя поверхность — размер и формат первичной */
        dd_obj *p = (dd_obj *)s; o->w = p->w; o->h = p->h; memcpy(o->pf, p->pf, 32); o->role = ROLE_BACK; o->caps = 4;
        gs_alloc(o); g_gs_back = o; TR("back %p %dx%d addr %08x\n", (void *)o, o->w, o->h, o->addr);
    }
    return o; }
void plat_dd_release(void *v) {
    if (!v) return;
    if (dsm_is(v)) { dsm_release(v); return; }
    dd_obj *o = (dd_obj *)v;
    if (o->px) { re_ptr_unregister(o->px); free(o->px); }
    if (o->gltex) plat_tex_free(o->gltex);
    free(o->hd);
    if (o == g_gs_back) g_gs_back = NULL;
    if (o == g_gs_primary) g_gs_primary = NULL;
    free(o); g_live--; }
int32_t plat_dd_is_lost(void *s) { return s ? ((dd_obj *)s)->lost : 0; }
int32_t plat_dd_restore(void *s) { if (s) ((dd_obj *)s)->lost = 0; return 0; }
int32_t plat_dd_fill_rect(void *s, int x0, int y0, int x1, int y1, uint32_t px) {
    g_fill[0] = x0; g_fill[1] = y0; g_fill[2] = x1; g_fill[3] = y1; g_fill_px = px; g_fill_n++;
    dd_obj *o = (dd_obj *)s;
    if (g_game_present && o) {   /* v2.01: Blt COLORFILL */
        if (o->role == ROLE_PRIMARY || o->role == ROLE_BACK) {
            uint32_t c = (uint32_t)mask8(px, o->pf[4]) << 16 | (uint32_t)mask8(px, o->pf[5]) << 8 | mask8(px, o->pf[6]);
            plat_clear_rect(c, x0, y0, x1 - x0, y1 - y0);
        } else if (o->px) {
            if (x0 < 0) x0 = 0;
            if (y0 < 0) y0 = 0;
            if (x1 > o->w) x1 = o->w;
            if (y1 > o->h) y1 = o->h;
            int bp = o->bpp / 8;
            for (int y = y0; y < y1; y++) for (int x = x0; x < x1; x++) memcpy(o->px + (size_t)y * o->pitch + x * bp, &px, (size_t)bp);
            o->dirty = 1;
        }
    }
    return 0;
}
void *plat_d3d_create_device(void *d3d, const void *iid, void *surf) { (void)iid; return (d3d && surf) ? mk(3) : NULL; }
void *plat_d3d_create_viewport(void *d3d) { return d3d ? mk(4) : NULL; }
int32_t plat_d3d_add_viewport(void *dev, void *vp) { return (dev && vp) ? 0 : -1; }
int32_t plat_d3d_set_viewport_rect(void *vp, int w, int h) { return (vp && w > 0 && h > 0) ? 0 : -1; }
void plat_window_maximize(void *wnd) { (void)wnd; }
int plat_dd_stub_count(void) { return g_live; }
int plat_dd_stub_last_fill(int32_t *r, uint32_t *px) { if (!g_fill_n) return 0; memcpy(r, g_fill, sizeof g_fill); *px = g_fill_px; return g_fill_n; }
int32_t plat_dd_set_cooperative(void *dd, void *hwnd, uint32_t flags) { (void)hwnd; g_coop_flags = flags; return dd ? 0 : -1; }
int plat_dd_last_coop(void) { return (int)g_coop_flags; }
int32_t plat_dd_get_surface_size(void *s, int32_t *w, int32_t *h) { if (!s) return -1; *w = ((dd_obj *)s)->w; *h = ((dd_obj *)s)->h; return 0; }
void *plat_dd_create_palette(void *dd, uint32_t flags, const void *e) {
    (void)flags; if (!dd || !e) return NULL;
    dd_obj *o = (dd_obj *)mk(5); if (o) memcpy(o->pal_rgba, e, sizeof o->pal_rgba); return o; }
int32_t plat_dd_surface_set_palette(void *s, void *p) {
    if (!s || !p) return -1;
    if (g_game_present) { ((dd_obj *)s)->pal = (dd_obj *)p; ((dd_obj *)s)->dirty = 1; } return 0; }
int32_t plat_dd_palette_set_entries(void *p, uint32_t f, uint32_t first, uint32_t n, const void *e) {
    (void)f; if (!p) return -1; g_pal_entries++;
    if (e && first < 256) { if (n > 256 - first) n = 256 - first; memcpy(((dd_obj *)p)->pal_rgba + first * 4, e, (size_t)n * 4); }
    return 0; }
void plat_tex_palette_changed(void *t, uint32_t first, uint32_t n) {
    (void)first; (void)n; g_pal_changed++;
    if (g_game_present && t && ((dd_obj *)t)->tag == 6 && ((dd_obj *)t)->surf) ((dd_obj *)t)->surf->dirty = 1; }
void plat_set_texture(int stage, void *tex) {
    g_tex_stage = stage; g_tex = tex;
    if (!g_game_present || stage != 0) return;
    dd_obj *t = (dd_obj *)tex, *s = (t && t->tag == 6) ? t->surf : (t && t->tag == 1 ? t : NULL);
    TR("set_texture %p surf %p\n", tex, (void *)s);
    if (s && s->px && s->bpp == 8 && s->page8 >= 0 && !s->has_ck && g_pal8_prov && s->pal) {   /* v2.18: PAL8 со страницей — текстура пары из пака */
        int h = g_pal8_prov(s->page8, s->page8_key, s->pal->pal_rgba);
        if (h > 0) { g_pal8_bind++; RP_COUNT(RC_PAL8_BINDS, 1); plat_tex_bind(h); return; }
    }
    if (s && s->px) { gs_upload(s, 0); plat_tex_bind(s->gltex); } else plat_tex_bind(0); }
void *plat_stub_last_texture(int *stage) { if (stage) *stage = g_tex_stage; return g_tex; }
int plat_stub_pal_stats(int *a, int *b) { *a = g_pal_entries; *b = g_pal_changed; return 1; }
int plat_dd_stub_last_desc(uint32_t *d) { if (!g_desc_n) return 0; memcpy(d, g_desc, sizeof g_desc); return g_desc_n; }
/* --- создание DirectDraw и режим экрана --- */
/* --- (en) DirectDraw creation and display mode. --- */
static uint32_t g_disp_flags = 0x40; static int g_disp_fail_create, g_disp_fail_mode;
void *plat_dd_create(const void *guid) { (void)guid; return g_disp_fail_create ? NULL : mk(0); }
int32_t plat_dd_get_display_flags(void *dd, uint32_t *f) { if (!dd || g_disp_fail_mode) return -1; *f = g_disp_flags; return 0; }
void plat_dd_stub_display(uint32_t f, int fc, int fm) { g_disp_flags = f; g_disp_fail_create = fc; g_disp_fail_mode = fm; }
/* --- FMV / DirectSound: учётные записи --- */
/* --- (en) FMV / DirectSound bookkeeping. --- */
static uint32_t g_fmv_fail; static int g_ms_state = -1, g_upd, g_blts, g_fills; static int32_t g_blt_rc[4]; static uint32_t g_fill_all_px, g_spk; static uint8_t g_fmt[18];
int32_t plat_mms_set_state(void *m, int st) { if (!m || (g_fmv_fail & 1)) return -1; g_ms_state = st; return 0; }
int32_t plat_sample_update(void *s) { if (!s || (g_fmv_fail & 2)) return -1; g_upd++; return 0; }
int32_t plat_dd_blt_from(void *d, const int32_t *r, void *s) { if (!d || !s || (g_fmv_fail & 4)) return -1; if (r) memcpy(g_blt_rc, r, sizeof g_blt_rc); g_blts++; return 0; }
int32_t plat_dd_fill_all(void *s, uint32_t px) { if (!s) return -1; g_fill_all_px = px; g_fills++; return 0; }
int32_t plat_ds_set_format(void *p, const void *w) { if (!p || !w) return -1; memcpy(g_fmt, w, 18); return 0; }
int32_t plat_ds_set_speaker_config(void *ds, uint32_t cfg) { if (!ds) return -1; g_spk = cfg; return 0; }
void plat_fmv_stub_fail(uint32_t m) { g_fmv_fail = m; }
int plat_fmv_stub_stats(int *st, int *u, int32_t *r, int *b, uint32_t *fp, int *f, uint8_t *fmt, uint32_t *spk) {
    *st = g_ms_state; *u = g_upd; memcpy(r, g_blt_rc, sizeof g_blt_rc); *b = g_blts; *fp = g_fill_all_px; *f = g_fills; memcpy(fmt, g_fmt, 18); *spk = g_spk; return 1; }
/* --- блокировка, формат пикселей, показ кадра --- */
/* --- (en) Lock, pixel format, frame present (Flip / Blt). --- */
static int g_lk_fail, g_pf_fail, g_locks, g_unlocks, g_flips, g_blts_rc, g_clip_sets, g_rects_n; static uint32_t g_pf_bits, g_pf_m[3], g_flip_flags; static int32_t g_flip_hr, g_drc[4], g_src_rc[4];
static uint8_t g_lock_mem[64];
int32_t plat_dd_lock(void *s, void *d) {
    if (!s || !d || g_lk_fail) return -1;
    uint32_t *u = (uint32_t *)d;
    dd_obj *o = (dd_obj *)s;
    if (g_game_present && o->tag == 1 && o->px) {   /* v2.01: настоящая память поверхности */
        u[1] = 0x100f | 8; u[2] = (uint32_t)o->h; u[3] = (uint32_t)o->w; u[4] = (uint32_t)o->pitch; u[9] = o->addr;
        memcpy(&u[18], o->pf, 32); u[26] = o->caps; g_locks++;
        TR("lock %p role %d addr %08x pitch %d\n", (void *)o, o->role, o->addr, o->pitch);
        return 0; }
    u[4] = 640; u[9] = (uint32_t)(uintptr_t)g_lock_mem; g_locks++; return 0; }
int32_t plat_dd_unlock(void *s) { if (!s) return -1; g_unlocks++;
    if (g_game_present && !dsm_is(s) && ((dd_obj *)s)->px) { dd_obj *o = (dd_obj *)s; o->dirty = 1; o->page8 = -1; if (o->hd) { free(o->hd); o->hd = NULL; } }
    return 0; }
int32_t plat_dd_get_pixel_format(void *s, uint32_t *pf) {
    if (g_game_present && s && ((dd_obj *)s)->tag == 1) { memcpy(pf, ((dd_obj *)s)->pf, 32); pf[0] = 0x20; return 0; }
    if (!s || g_pf_fail) return -1;
    memset(pf, 0, 32); pf[0] = 0x20; pf[3] = g_pf_bits; pf[4] = g_pf_m[0]; pf[5] = g_pf_m[1]; pf[6] = g_pf_m[2]; return 0; }
void *plat_dd_query_dd4(void *dd) { return dd ? mk(0) : NULL; }
void *plat_dd_query_d3d(void *dd) { return dd ? mk(0) : NULL; }
void plat_window_client_rect(void *h, int32_t *rc) { (void)h; rc[0] = 0; rc[1] = 0; rc[2] = 800; rc[3] = 600; }
void plat_client_to_screen(void *h, int32_t *pt) { (void)h; pt[0] += 100; pt[1] += 50; }
int32_t plat_dd_clipper_set_hwnd(void *c, void *h) { (void)h; if (!c) return -1; g_clip_sets++; return 0; }
int32_t plat_dd_blt_rect(void *d, const int32_t *dr, void *s, const int32_t *sr) {
    if (!d || !s) return -1;
    memcpy(g_drc, dr, sizeof g_drc); memcpy(g_src_rc, sr, sizeof g_src_rc); g_blts_rc++;
    if (g_game_present && d == (void *)g_gs_primary && s == (void *)g_gs_back) gs_present();   /* v2.01: оконный режим — Blt front←back */
    return 0; }
int32_t plat_dd_flip(void *s, uint32_t fl) { if (!s) return -1; g_flips++; g_flip_flags = fl; if (g_game_present) { gs_present(); return 0; } return g_flip_hr; }
void plat_dd_stub_surface(int lf, int pff, uint32_t bits, uint32_t r, uint32_t g, uint32_t b, int32_t fhr) {
    g_lk_fail = lf; g_pf_fail = pff; g_pf_bits = bits; g_pf_m[0] = r; g_pf_m[1] = g; g_pf_m[2] = b; g_flip_hr = fhr; (void)g_rects_n; }
int plat_dd_stub_surface_stats(int *lk, int *ul, int *fl, uint32_t *ff, int *bl, int32_t *dr, int32_t *sr, int *cs) {
    *lk = g_locks; *ul = g_unlocks; *fl = g_flips; *ff = g_flip_flags; *bl = g_blts_rc; memcpy(dr, g_drc, sizeof g_drc); memcpy(sr, g_src_rc, sizeof g_src_rc); *cs = g_clip_sets; return 1; }
/* --- DirectSound 3D: учётные записи (последний вызов) --- */
/* --- (en) DirectSound 3D listener / buffer calls: forwarded to the mixer in the game, last call recorded for tests. --- */
static int g_ds3_op; static float g_ds3_v[6]; static uint32_t g_ds3_u;
static int32_t ds3_rec(void *o, int op, float a, float b, float c, uint32_t u) {
    if (!o) return -1;
    g_ds3_op = op; g_ds3_v[0] = a; g_ds3_v[1] = b; g_ds3_v[2] = c; g_ds3_u = u; return 0; }
int32_t plat_ds_listener_set_position(void *l, float x, float y, float z) { if (DSG(l)) dsm_listener_pos(x, y, z); return ds3_rec(l, 1, x, y, z, 0); }
int32_t plat_ds_listener_set_orientation(void *l, const float *s) {
    if (DSG(l)) dsm_listener_orient(s);
    int32_t r = ds3_rec(l, 2, 0, 0, 0, 0); if (r == 0) memcpy(g_ds3_v, s, sizeof g_ds3_v); return r; }
int32_t plat_ds_listener_set_velocity(void *l, float x, float y, float z) { return ds3_rec(l, 3, x, y, z, 0); }
int32_t plat_ds_listener_set_factor(void *l, int w, float v) { if (DSG(l)) dsm_listener_factors(w, v); return ds3_rec(l, 16 + w, v, 0, 0, 0); }
int32_t plat_ds_listener_commit(void *l) { return ds3_rec(l, 4, 0, 0, 0, 0); }
int32_t plat_ds_buf_play(void *b, uint32_t fl) { if (DSG(b)) dsm_play(b, fl); return ds3_rec(b, 5, 0, 0, 0, fl); }
int32_t plat_ds_buf_set_volume(void *b, int32_t v) { if (DSG(b)) dsm_set_volume(b, v); return ds3_rec(b, 6, 0, 0, 0, (uint32_t)v); }
int32_t plat_ds_buf_set_frequency(void *b, uint32_t hz) { if (DSG(b)) dsm_set_frequency(b, hz); return ds3_rec(b, 7, 0, 0, 0, hz); }
int32_t plat_ds_buf_get_status(void *b, uint32_t *st) { if (DSG(b)) return dsm_get_status(b, st); int32_t r = ds3_rec(b, 8, 0, 0, 0, 0); if (r == 0 && st) *st = 0x1; return r; }
int32_t plat_ds3d_set_mode(void *b, uint32_t m) { if (DSG(b)) dsm_3d_mode(b, m); return ds3_rec(b, 9, 0, 0, 0, m); }
int32_t plat_ds3d_set_position(void *b, float x, float y, float z) { if (DSG(b)) dsm_3d_pos(b, x, y, z); return ds3_rec(b, 10, x, y, z, 0); }
int32_t plat_ds3d_set_velocity(void *b, float x, float y, float z) { return ds3_rec(b, 11, x, y, z, 0); }
int plat_ds3d_stub_last(int *op, float *v6, uint32_t *u) { *op = g_ds3_op; memcpy(v6, g_ds3_v, sizeof g_ds3_v); *u = g_ds3_u; return 1; }
static uint32_t g_dsx_fail, g_dsx_support = 3, g_dsx_pid, g_dsx_plen, g_dsx_pd0; static uint8_t g_dsx_pg[16]; static int g_dsx_pn;
int32_t plat_ds_buf_stop(void *b) { if (DSG(b)) dsm_stop(b); return ds3_rec(b, 12, 0, 0, 0, 0); }
int32_t plat_ds_buf_set_position(void *b, uint32_t pos) { if (DSG(b)) dsm_set_position(b, pos); return ds3_rec(b, 13, 0, 0, 0, pos); }
int32_t plat_ds3d_set_velocity_ex(void *b, float x, float y, float z, uint32_t ap) { return ds3_rec(b, 14, x, y, z, ap); }
int32_t plat_ds_create_buffer(void *ds, uint32_t fl, uint32_t bytes, const void *wfx, void **out) {
    if (g_game_present && ds && !(g_dsx_fail & 1)) return dsm_create_buffer(fl, bytes, wfx, out);
    (void)wfx; if (!ds || (g_dsx_fail & 1)) { *out = NULL; return -1; }
    *out = plat_dd_create(NULL); g_ds3_op = 15; g_ds3_u = fl; g_ds3_v[0] = (float)bytes; return 0; }
int32_t plat_com_query_interface(void *obj, const void *iid, void **out) {
    if (!obj || (g_dsx_fail & 2)) { *out = NULL; return -1; }
    static const uint8_t iid_ks[16] = { 0x30,0xac,0xef,0x31,0x5c,0x51,0xd0,0x11,0xa9,0xaa,0x00,0xaa,0x00,0x61,0xbe,0x93 };
    if (DSG(obj) && !(iid && memcmp(iid, iid_ks, 16) == 0)) { *out = dsm_qi(obj); return *out ? 0 : -1; }
    static const uint8_t iid_tex2[16] = { 0x02,0x15,0x28,0x93,0xf8,0x8c,0xd0,0x11,0x89,0xab,0x00,0xa0,0xc9,0x05,0x41,0x29 };
    if (g_game_present && iid && ((dd_obj *)obj)->tag == 1 && memcmp(iid, iid_tex2, 16) == 0) {   /* v2.01: текстура ↔ поверхность */
        dd_obj *t = (dd_obj *)mk(6); if (t) t->surf = (dd_obj *)obj; *out = t; return t ? 0 : -1; }
    *out = plat_dd_create(NULL); return 0; }
int32_t plat_ds_prop_set(void *ps, const void *g, uint32_t id, const void *d, uint32_t len) {
    if (!ps) return -1;
    memcpy(g_dsx_pg, g, 16); g_dsx_pid = id; g_dsx_plen = len; g_dsx_pd0 = 0; memcpy(&g_dsx_pd0, d, len < 4 ? len : 4); g_dsx_pn++; return 0; }
int32_t plat_ds_prop_support(void *ps, const void *g, uint32_t id, uint32_t *sup) {
    (void)g; (void)id; if (!ps || (g_dsx_fail & 4)) return -1; *sup = g_game_present ? 0 : g_dsx_support; return 0; }   /* v2.09: в игре EAX нет */
/* --- v1.93: DirectSound — создание/перечисление/дубликат/Lock (заглушки для тестов; память Lock — буфер 64 КБ) --- */
/* --- (en) DirectSound create / enumerate / duplicate / Lock (test stubs; game buffers live in plat_dsmix.c). --- */
static int g_dsd_n = 1; static uint8_t g_dsd_g[8][16]; static const char *g_dsd_name[8] = { "Primary Sound Driver" }; static int g_dsd_null[8] = { 1 };
static uint32_t g_dsd_caps, g_dsd_fail, g_dsd_split; static int g_dsd_cr, g_dsd_coop, g_dsd_dup, g_dsd_lk, g_dsd_ul, g_dsd_rs;
static uint8_t g_dsd_mem[0x10000];
void plat_ds_stub_drivers(int n, const uint8_t (*g)[16], const char *const *nm, uint32_t caps) {
    if (n > 8) n = 8;
    g_dsd_n = n; g_dsd_caps = caps;
    for (int i = 0; i < n; i++) { g_dsd_null[i] = g == NULL || i == 0; if (g) memcpy(g_dsd_g[i], g[i], 16); g_dsd_name[i] = nm[i]; } }
void plat_ds_stub_dsfail(uint32_t m, uint32_t sp) { g_dsd_fail = m; g_dsd_split = sp; }
int plat_ds_stub_dsstats(int *c, int *co, int *d, int *l, int *u, int *r, uint8_t *m64) {
    *c = g_dsd_cr; *co = g_dsd_coop; *d = g_dsd_dup; *l = g_dsd_lk; *u = g_dsd_ul; *r = g_dsd_rs; memcpy(m64, g_dsd_mem, 64); return 1; }
int32_t plat_ds_enumerate(plat_ds_enum_cb cb, void *ctx) {
    for (int i = 0; i < g_dsd_n; i++) if (cb(g_dsd_null[i] ? NULL : g_dsd_g[i], g_dsd_name[i], "", ctx) == 0) break;
    return 0; }
int32_t plat_ds_create(const void *g, void **out) {
    (void)g; g_dsd_cr++; if (g_dsd_fail & 1) { *out = NULL; return -1; } *out = plat_dd_create(NULL);
    if (g_game_present && *out) plat_snd_open_game();   /* v2.09: устройство SDL_audio или запись RE_WAV_OUT */
    return *out ? 0 : -1; }
int32_t plat_ds_set_coop(void *ds, void *hwnd, uint32_t lv) { (void)hwnd; if (!ds || (g_dsd_fail & 4)) return -1; g_dsd_coop = (int)lv; return 0; }
int32_t plat_ds_get_caps_flags(void *ds, uint32_t *f) { if (!ds || (g_dsd_fail & 2)) return -1; *f = g_dsd_caps; return 0; }
int32_t plat_ds_duplicate(void *ds, void *src, void **out) {
    g_dsd_dup++; if (!ds || !src || (g_dsd_fail & 8)) { *out = NULL; return -1; }
    if (DSG(src)) return dsm_duplicate(src, out);
    if (g_dsd_fail & 0x40) { g_dsd_fail &= ~0x40u; *out = NULL; return (int32_t)0x88780096u; }
    *out = plat_dd_create(NULL); return 0; }
int32_t plat_ds_buf_lock(void *b, uint32_t bytes, void **p1, uint32_t *n1, void **p2, uint32_t *n2) {
    if (DSG(b)) { g_dsd_lk++; return dsm_lock(b, bytes, p1, n1, p2, n2); }
    if (!b || (g_dsd_fail & 0x10) || bytes > sizeof g_dsd_mem) return -1;
    g_dsd_lk++;
    uint32_t s = g_dsd_split && g_dsd_split < bytes ? g_dsd_split : bytes;
    *p1 = g_dsd_mem; *n1 = s; *p2 = s < bytes ? g_dsd_mem + s : NULL; *n2 = bytes - s; return 0; }
int32_t plat_ds_buf_unlock(void *b, void *p1, uint32_t n1, void *p2, uint32_t n2) { (void)p1; (void)n1; (void)p2; (void)n2; if (!b) return -1; g_dsd_ul++; return 0; }
int32_t plat_ds_buf_restore(void *b) { if (!b || (g_dsd_fail & 0x20)) return -1; g_dsd_rs++; return 0; }
void plat_ds_stub_ctl(uint32_t fm, uint32_t sup) { g_dsx_fail = fm; g_dsx_support = sup; }
int plat_ds_stub_prop(uint8_t *g, uint32_t *id, uint32_t *len, uint32_t *d0, int *n) {
    memcpy(g, g_dsx_pg, 16); *id = g_dsx_pid; *len = g_dsx_plen; *d0 = g_dsx_pd0; *n = g_dsx_pn; return 1; }
/* --- v1.94: перечисление DirectDraw/Direct3D — тестовые заглушки (SDL не перечисляет адаптеры DirectDraw):
   драйвер 0 — основной (guid NULL) «Primary Display Driver», остальные с guid {i}; устройства — «SDL HAL i»
   (D3DDEVICEDESC: dwSize 0xfc, dwFlags 0, dcmColorModel = 2 у HAL, 0 у последнего при n_dev > 1) --- */
/* --- (en) DirectDraw / Direct3D enumeration: one fake primary driver; in the game the GL device is reported as a
   HAL device with full blend caps (without them the game's blend check rejected additive smoke). --- */
static int g_dde_n = 1, g_d3de_n = 1; static uint32_t g_dde_fail;
void plat_dd_stub_enum(int n_dd, int n_dev, uint32_t fm) { g_dde_n = n_dd; g_d3de_n = n_dev; g_dde_fail = fm; g_game_present = (fm & 0x100) != 0;
    if (g_game_present) plat_set_render_state(15, 0); }   /* v2.01: игра — умолчание D3D ALPHATESTENABLE = FALSE (тесты рендера — прежнее 1) */
int32_t plat_dd_enumerate(plat_dd_enum_cb cb, void *ctx) {
    if (g_dde_fail & 1) return -1;
    for (int i = 0; i < g_dde_n; i++) {
        uint8_t g[16] = { (uint8_t)i, 0xdd };
        char nm[32]; snprintf(nm, sizeof nm, i == 0 ? "Primary Display Driver" : "Display %d", i);
        if (cb(i == 0 ? NULL : g, nm, i == 0 ? "display" : "dd", ctx) == 0) break;
    }
    return 0; }
int32_t plat_d3d_enum_devices(void *d3d, plat_d3d_dev_cb cb, void *ctx) {
    if (!d3d || (g_dde_fail & 2)) return -1;
    for (int i = 0; i < g_d3de_n; i++) {
        uint32_t hw[63] = { 0xfc, 0, (g_d3de_n > 1 && i == g_d3de_n - 1) ? 0u : 2u }, hel[63] = { 0xfc, 0, 1 };
        hw[3] = 0x1000u + (uint32_t)i; uint8_t g[16] = { 0x3d, (uint8_t)i };
        if (g_dde_fail & 0x100) {   /* v2.00: игра (не тест) — GL-устройство как HAL D3DDEVICEDESC: COLORMODEL|DEVCAPS, RGB,
                                       FLOATTLVERTEX|DRAWPRIMTLVERTEX|HWRASTERIZATION, текстуры 1..2048 */
            memset(hw, 0, sizeof hw); hw[0] = 0xfc; hw[1] = 3; hw[2] = 2; hw[3] = 0x1u | 0x400u | 0x80000u;
            hw[43] = 1; hw[44] = 1; hw[45] = 2048; hw[46] = 2048;
            /* v2.06: dpcLineCaps (+0x2c) / dpcTriCaps (+0x64): ZCmp/AlphaCmp — все, Src/DestBlendCaps — все D3DPBLENDCAPS (0x1fff).
               Без них 0041e9d2 (P23_SetBlendMode) считал аддитивное смешивание недоступным: дым выхлопа — чёрный квадрат. */
            for (int k = 0; k < 2; k++) { uint32_t *pc = &hw[k == 0 ? 11 : 25]; pc[0] = 0x38; pc[3] = 0xff; pc[4] = 0x1fff; pc[5] = 0x1fff; pc[6] = 0xff; }
            memcpy(hel, hw, sizeof hel); }
        char nm[32]; snprintf(nm, sizeof nm, (g_dde_fail & 0x100) ? "SDL OpenGL %d" : "SDL HAL %d", i);
        if (cb(g, "SDL Direct3D stub", nm, hw, hel, ctx) == 0) break;
    }
    return 0; }
/* --- v1.95: FMV через DirectShow — в SDL MPEG-ролики не декодируются: по умолчанию CoCreateInstance отказывает
   (E_NOTIMPL), и игра пропускает ролик, как при отсутствии DirectShow. Тестовый режим (plat_fmv_stub_open(1, …)) —
   учётные объекты с форматом w×h и длительностью. Окно: UpdateWindow/SetForegroundWindow — счётчики (+ SDL_RaiseWindow
   в plat_sys.c не нужен: окно SDL одно и всегда сверху у игры). --- */
/* --- (en) DirectShow FMV: not decoded natively — CoCreateInstance fails by default and the game skips the
   movie; a test mode returns bookkeeping objects. --- */
static int g_fo_ok, g_fo_cr, g_fo_open, g_fo_smp, g_fo_fg, g_fo_upd; static uint32_t g_fo_fail; static int32_t g_fo_w = 320, g_fo_h = 200, g_fo_rc[4];
static double g_fo_dur = 1.0; static char g_fo_path[64];
#define FO_FAIL(b) (!g_fo_ok || (g_fo_fail & (1u << (b))))
void plat_fmv_stub_open(int ok, uint32_t m, int32_t w, int32_t h, double d) {
    g_fo_ok = ok; g_fo_fail = m; g_fo_w = w; g_fo_h = h; g_fo_dur = d; g_fo_cr = g_fo_open = g_fo_smp = g_fo_fg = g_fo_upd = 0; g_fo_path[0] = 0; }
int plat_fmv_stub_open_stats(int *cr, int *op, char *p64, int *smp, int32_t *rc, int *fg, int *upd) {
    *cr = g_fo_cr; *op = g_fo_open; memcpy(p64, g_fo_path, 64); *smp = g_fo_smp; memcpy(rc, g_fo_rc, sizeof g_fo_rc); *fg = g_fo_fg; *upd = g_fo_upd; return 1; }
int32_t plat_com_create(const void *c, const void *i, void **out) {
    (void)c; (void)i; *out = NULL; if (FO_FAIL(0)) return (int32_t)0x80004001u; *out = mk(20); g_fo_cr++; return 0; }
int32_t plat_mms_initialize(void *m, uint32_t t, uint32_t f, void *g) { (void)t; (void)f; (void)g; return (!m || FO_FAIL(2)) ? -1 : 0; }
int32_t plat_mms_add_stream(void *m, void *src, const void *pur, uint32_t f) {
    (void)pur; (void)f; if (!m) return -1; return FO_FAIL(src ? 3 : 4) ? -1 : 0; }
int32_t plat_mms_open_file(void *m, const char *p, uint32_t f) {
    (void)f; if (!m || FO_FAIL(5)) return -1; snprintf(g_fo_path, sizeof g_fo_path, "%s", p ? p : ""); g_fo_open++; return 0; }
int32_t plat_mms_get_stream(void *m, const void *pur, void **out) { (void)pur; *out = NULL; if (!m || FO_FAIL(6)) return -1; *out = mk(21); return 0; }
int32_t plat_ddms_get_format(void *s, void *d) {
    if (!s || FO_FAIL(7)) return -1;
    uint32_t *u = (uint32_t *)d; u[1] = 0x1006; u[2] = (uint32_t)g_fo_h; u[3] = (uint32_t)g_fo_w; return 0; }
int32_t plat_ddms_create_sample(void *s, void *surf, const int32_t *rc, uint32_t f, void **out) {
    (void)f; *out = NULL; if (!s || !surf || FO_FAIL(9)) return -1; if (rc) memcpy(g_fo_rc, rc, sizeof g_fo_rc); *out = mk(22); g_fo_smp++; return 0; }
int32_t plat_dd_get_surface_desc(void *s, void *d) {
    if (!s || FO_FAIL(8)) return -1;
    uint32_t *u = (uint32_t *)d; u[1] = 0x1007; u[2] = 480; u[3] = 640;
    u[0x48 / 4] = 0x20; u[0x48 / 4 + 1] = 0x40; u[0x48 / 4 + 3] = 16; u[0x48 / 4 + 4] = 0xf800; u[0x48 / 4 + 5] = 0x7e0; u[0x48 / 4 + 6] = 0x1f; return 0; }
int32_t plat_media_get_duration(void *p, double *sec) { if (!p || FO_FAIL(10)) return -1; *sec = g_fo_dur; return 0; }
void plat_window_update(void *h) { (void)h; g_fo_upd++; }
void plat_window_foreground(void *h) { (void)h; g_fo_fg++; }
/* --- v1.96: GetCaps, EnumTextureFormats / EnumZBufferFormats — учётные: форматы, которые реально умеет plat_render
   (ARGB1555, RGB565, PAL8 через палитру в шейдере; Z 16 бит) --- */
/* --- (en) GetCaps, texture / z-buffer format enumeration: the formats the GL renderer really supports. --- */
static uint32_t g_caps_fail, g_caps2;
void plat_dd_stub_caps(uint32_t m, uint32_t c2) { g_caps_fail = m; g_caps2 = c2; }
int32_t plat_dd_get_caps(void *dd, void *hal, void *hel) {
    if (!dd || (g_caps_fail & 1)) return -1;
    uint32_t *a = (uint32_t *)hal, *b = (uint32_t *)hel;
    if (a) { uint32_t n = a[0]; memset(a, 0, 0x17c); a[0] = n; a[2] = g_caps2; }
    if (b) { uint32_t n = b[0]; memset(b, 0, 0x17c); b[0] = n; }
    return 0; }
int32_t plat_d3d_enum_tex_formats(void *dev, plat_pf_enum_cb cb, void *ctx) {
    if (!dev || (g_caps_fail & 2)) return -1;
    static const uint32_t f[3][8] = { { 0x20, 0x41, 0, 16, 0x7c00, 0x3e0, 0x1f, 0x8000 },
                                      { 0x20, 0x40, 0, 16, 0xf800, 0x7e0, 0x1f, 0 },
                                      { 0x20, 0x60, 0, 8, 0, 0, 0, 0 } };
    for (int i = 0; i < 3; i++) if (cb(f[i], (uint8_t *)ctx) == 0) break;
    return 0; }
int32_t plat_d3d_enum_zbuffer(void *d3d, const void *g, plat_pf_enum_cb cb, void *ctx) {
    (void)g; if (!d3d || (g_caps_fail & 4)) return -1;
    static const uint32_t z[8] = { 0x20, 0x400, 0, 16, 0, 0xffff, 0, 0 };
    cb(z, (uint8_t *)ctx); return 0; }
