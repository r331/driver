/* SDL-вариант объектов DirectDraw/Direct3D: учётные записи без устройства.
   Игровой код (game/ported24.c) работает с дескрипторами; реальное окно/буфер даёт plat_render.c. */
#include "../plat.h"
#include <stdlib.h>
#include <string.h>
typedef struct { uint32_t tag; int32_t lost; int32_t attached; int32_t clipper; int32_t w, h; } dd_obj;
static uint32_t g_desc[31]; static int g_desc_n; static void *g_tex; static int g_tex_stage, g_pal_entries, g_pal_changed;
static int g_live; static uint32_t g_coop_flags;
static int32_t g_fill[4]; static uint32_t g_fill_px; static int g_fill_n;
static void *mk(uint32_t tag) { dd_obj *o = (dd_obj *)calloc(1, sizeof *o); if (o) { o->tag = tag; g_live++; } return o; }
void *plat_dd_create_surface(void *dd, const void *desc) {
    if (!dd || !desc) return NULL;
    dd_obj *o = (dd_obj *)mk(1); if (!o) return NULL;
    memcpy(g_desc, desc, sizeof g_desc); g_desc_n++;
    if (g_desc[1] & 6) { o->h = (int32_t)g_desc[2]; o->w = (int32_t)g_desc[3]; }
    return o;
}
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
int32_t plat_dd_set_cooperative(void *dd, void *hwnd, uint32_t flags) { (void)hwnd; g_coop_flags = flags; return dd ? 0 : -1; }
int plat_dd_last_coop(void) { return (int)g_coop_flags; }
int32_t plat_dd_get_surface_size(void *s, int32_t *w, int32_t *h) { if (!s) return -1; *w = ((dd_obj *)s)->w; *h = ((dd_obj *)s)->h; return 0; }
void *plat_dd_create_palette(void *dd, uint32_t flags, const void *e) { (void)flags; return (dd && e) ? mk(5) : NULL; }
int32_t plat_dd_surface_set_palette(void *s, void *p) { return (s && p) ? 0 : -1; }
int32_t plat_dd_palette_set_entries(void *p, uint32_t f, uint32_t first, uint32_t n, const void *e) { (void)f; (void)first; (void)n; (void)e; if (!p) return -1; g_pal_entries++; return 0; }
void plat_tex_palette_changed(void *t, uint32_t first, uint32_t n) { (void)t; (void)first; (void)n; g_pal_changed++; }
void plat_set_texture(int stage, void *tex) { g_tex_stage = stage; g_tex = tex; }
void *plat_stub_last_texture(int *stage) { if (stage) *stage = g_tex_stage; return g_tex; }
int plat_stub_pal_stats(int *a, int *b) { *a = g_pal_entries; *b = g_pal_changed; return 1; }
int plat_dd_stub_last_desc(uint32_t *d) { if (!g_desc_n) return 0; memcpy(d, g_desc, sizeof g_desc); return g_desc_n; }
/* --- создание DirectDraw и режим экрана --- */
static uint32_t g_disp_flags = 0x40; static int g_disp_fail_create, g_disp_fail_mode;
void *plat_dd_create(const void *guid) { (void)guid; return g_disp_fail_create ? NULL : mk(0); }
int32_t plat_dd_get_display_flags(void *dd, uint32_t *f) { if (!dd || g_disp_fail_mode) return -1; *f = g_disp_flags; return 0; }
void plat_dd_stub_display(uint32_t f, int fc, int fm) { g_disp_flags = f; g_disp_fail_create = fc; g_disp_fail_mode = fm; }
/* --- FMV / DirectSound: учётные записи --- */
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
static int g_lk_fail, g_pf_fail, g_locks, g_unlocks, g_flips, g_blts_rc, g_clip_sets, g_rects_n; static uint32_t g_pf_bits, g_pf_m[3], g_flip_flags; static int32_t g_flip_hr, g_drc[4], g_src_rc[4];
static uint8_t g_lock_mem[64];
int32_t plat_dd_lock(void *s, void *d) {
    if (!s || !d || g_lk_fail) return -1;
    uint32_t *u = (uint32_t *)d; u[4] = 640; u[9] = (uint32_t)(uintptr_t)g_lock_mem; g_locks++; return 0; }
int32_t plat_dd_unlock(void *s) { if (!s) return -1; g_unlocks++; return 0; }
int32_t plat_dd_get_pixel_format(void *s, uint32_t *pf) {
    if (!s || g_pf_fail) return -1;
    memset(pf, 0, 32); pf[0] = 0x20; pf[3] = g_pf_bits; pf[4] = g_pf_m[0]; pf[5] = g_pf_m[1]; pf[6] = g_pf_m[2]; return 0; }
void *plat_dd_query_dd4(void *dd) { return dd ? mk(0) : NULL; }
void *plat_dd_query_d3d(void *dd) { return dd ? mk(0) : NULL; }
void plat_window_client_rect(void *h, int32_t *rc) { (void)h; rc[0] = 0; rc[1] = 0; rc[2] = 800; rc[3] = 600; }
void plat_client_to_screen(void *h, int32_t *pt) { (void)h; pt[0] += 100; pt[1] += 50; }
int32_t plat_dd_clipper_set_hwnd(void *c, void *h) { (void)h; if (!c) return -1; g_clip_sets++; return 0; }
int32_t plat_dd_blt_rect(void *d, const int32_t *dr, void *s, const int32_t *sr) {
    if (!d || !s) return -1; memcpy(g_drc, dr, sizeof g_drc); memcpy(g_src_rc, sr, sizeof g_src_rc); g_blts_rc++; return 0; }
int32_t plat_dd_flip(void *s, uint32_t fl) { if (!s) return -1; g_flips++; g_flip_flags = fl; return g_flip_hr; }
void plat_dd_stub_surface(int lf, int pff, uint32_t bits, uint32_t r, uint32_t g, uint32_t b, int32_t fhr) {
    g_lk_fail = lf; g_pf_fail = pff; g_pf_bits = bits; g_pf_m[0] = r; g_pf_m[1] = g; g_pf_m[2] = b; g_flip_hr = fhr; (void)g_rects_n; }
int plat_dd_stub_surface_stats(int *lk, int *ul, int *fl, uint32_t *ff, int *bl, int32_t *dr, int32_t *sr, int *cs) {
    *lk = g_locks; *ul = g_unlocks; *fl = g_flips; *ff = g_flip_flags; *bl = g_blts_rc; memcpy(dr, g_drc, sizeof g_drc); memcpy(sr, g_src_rc, sizeof g_src_rc); *cs = g_clip_sets; return 1; }
/* --- DirectSound 3D: учётные записи (последний вызов) --- */
static int g_ds3_op; static float g_ds3_v[6]; static uint32_t g_ds3_u;
static int32_t ds3_rec(void *o, int op, float a, float b, float c, uint32_t u) {
    if (!o) return -1; g_ds3_op = op; g_ds3_v[0] = a; g_ds3_v[1] = b; g_ds3_v[2] = c; g_ds3_u = u; return 0; }
int32_t plat_ds_listener_set_position(void *l, float x, float y, float z) { return ds3_rec(l, 1, x, y, z, 0); }
int32_t plat_ds_listener_set_orientation(void *l, const float *s) {
    int32_t r = ds3_rec(l, 2, 0, 0, 0, 0); if (r == 0) memcpy(g_ds3_v, s, sizeof g_ds3_v); return r; }
int32_t plat_ds_listener_set_velocity(void *l, float x, float y, float z) { return ds3_rec(l, 3, x, y, z, 0); }
int32_t plat_ds_listener_commit(void *l) { return ds3_rec(l, 4, 0, 0, 0, 0); }
int32_t plat_ds_buf_play(void *b, uint32_t fl) { return ds3_rec(b, 5, 0, 0, 0, fl); }
int32_t plat_ds_buf_set_volume(void *b, int32_t v) { return ds3_rec(b, 6, 0, 0, 0, (uint32_t)v); }
int32_t plat_ds_buf_set_frequency(void *b, uint32_t hz) { return ds3_rec(b, 7, 0, 0, 0, hz); }
int32_t plat_ds_buf_get_status(void *b, uint32_t *st) { int32_t r = ds3_rec(b, 8, 0, 0, 0, 0); if (r == 0 && st) *st = 0x1; return r; }
int32_t plat_ds3d_set_mode(void *b, uint32_t m) { return ds3_rec(b, 9, 0, 0, 0, m); }
int32_t plat_ds3d_set_position(void *b, float x, float y, float z) { return ds3_rec(b, 10, x, y, z, 0); }
int32_t plat_ds3d_set_velocity(void *b, float x, float y, float z) { return ds3_rec(b, 11, x, y, z, 0); }
int plat_ds3d_stub_last(int *op, float *v6, uint32_t *u) { *op = g_ds3_op; memcpy(v6, g_ds3_v, sizeof g_ds3_v); *u = g_ds3_u; return 1; }
