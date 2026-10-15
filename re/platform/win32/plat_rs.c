/* hook-вариант: render/звук — заглушки, затем вызовы обёрток Game.exe */
/* hook-вариант: render/звук пока без-операций; будут звать обёртки Game.exe по адресу */
#include "../plat.h"
static int g_next_tex = 1;
static int g_blend, g_zt, g_zw;
int plat_tex_create(int w, int h, const uint32_t *rgba) { (void)w; (void)h; (void)rgba; return g_next_tex++; }
void plat_tex_bind(int tex) { (void)tex; }
void plat_tex_free(int tex) { (void)tex; }
void plat_set_blend(int e, int s, int d) { (void)s; (void)d; g_blend = e; }
void plat_set_zbuffer(int t, int w) { g_zt = t; g_zw = w; (void)g_blend; (void)g_zt; (void)g_zw; }
void plat_draw_tris(const plat_vertex *v, int c) { (void)v; (void)c; }
void plat_clear(uint32_t c, int z) { (void)c; (void)z; }
void plat_flip(void) {}
void plat_blit2d(int t, int a, int b, int c, int d, int e, int f) { (void)t;(void)a;(void)b;(void)c;(void)d;(void)e;(void)f; }
#include "../plat.h"
int plat_snd_create(const void*p,int b,int r,int c,int bits){(void)p;(void)b;(void)r;(void)c;(void)bits;return 0;}
void plat_snd_destroy(int h){(void)h;}
void plat_snd_play(int h,int l){(void)h;(void)l;}
void plat_snd_stop(int h){(void)h;}
void plat_snd_set(int h,int v,int p,int n){(void)h;(void)v;(void)p;(void)n;}
void plat_snd_pos3d(int h,float x,float y,float z){(void)h;(void)x;(void)y;(void)z;}
void plat_snd_mix(int16_t*o,int n){(void)o;(void)n;}
int plat_snd_open(void){return 0;}
void plat_snd_close(void){}
int plat_cd_play(int t){(void)t;return 0;}
void plat_cd_stop(void){}
int plat_cd_current(void){return 0;}
int plat_render_attach(void *(*g)(const char *), void (*s)(void), int w, int h){(void)g;(void)s;(void)w;(void)h;return -1;}
int plat_render_offscreen(int w, int h){(void)w;(void)h;return -1;}
int plat_render_readback(uint32_t *o){(void)o;return -1;}
void plat_render_shutdown(void){}

/* --- состояние устройства: IDirect3DDevice3 / IDirect3DViewport3 игры (глобалы Game.exe) --- */
typedef long (__attribute__((stdcall)) *d3d_fn0)(void *);
typedef long (__attribute__((stdcall)) *d3d_fn2)(void *, uint32_t, uint32_t);
typedef long (__attribute__((stdcall)) *d3d_fn3)(void *, uint32_t, uint32_t, uint32_t);
typedef long (__attribute__((stdcall)) *d3d_fn1p)(void *, void *);
#define D3D_DEV  (*(void **)0x00a42160)
#define D3D_VP   (*(void **)0x00a42164)
#define VT(o, off) ((*(void ***)(o))[(off) / 4])
void plat_scene_begin(void) { void *d = D3D_DEV; ((d3d_fn0)VT(d, 0x24))(d); }
void plat_scene_end(void)   { void *d = D3D_DEV; ((d3d_fn0)VT(d, 0x28))(d); }
void plat_set_render_state(int state, uint32_t value) { void *d = D3D_DEV; ((d3d_fn2)VT(d, 0x58))(d, (uint32_t)state, value); }
void plat_set_tex_stage(int stage, int type, uint32_t value) { void *d = D3D_DEV; ((d3d_fn3)VT(d, 0xa0))(d, (uint32_t)stage, (uint32_t)type, value); }
void plat_set_viewport(int x, int y, int w, int h) {
    void *v = D3D_VP;
    struct { uint32_t size; int32_t x, y, w, h; float clip_x, clip_y, clip_w, clip_h, min_z, max_z; } vp;
    vp.size = 0x2c; vp.x = x; vp.y = y; vp.w = w; vp.h = h;
    vp.clip_x = 0; vp.clip_y = 0; vp.clip_w = (float)w; vp.clip_h = (float)h; vp.min_z = 0; vp.max_z = 1.0f;
    ((d3d_fn1p)VT(v, 0x44))(v, &vp);
}
uint32_t plat_get_tex_stage(int stage, int type) {
    void *d = D3D_DEV; uint32_t out = 0;
    typedef long (__attribute__((stdcall)) *gt_t)(void *, uint32_t, uint32_t, uint32_t *);
    ((gt_t)VT(d, 0x9c))(d, (uint32_t)stage, (uint32_t)type, &out);
    return out;
}
void plat_draw_prim(int ptype, const plat_vertex *v, int count) {
    void *d = D3D_DEV;
    typedef long (__attribute__((stdcall)) *dp_t)(void *, uint32_t, uint32_t, const void *, uint32_t, uint32_t);
    ((dp_t)VT(d, 0x70))(d, (uint32_t)ptype, 0x1c4, v, (uint32_t)count, 0x18);
}
int plat_draw_prim_last(int *ptype, int *count) { (void)ptype; (void)count; return 0; }
void plat_draw_lines(const plat_vertex *v, int count) {
    void *d = D3D_DEV;
    typedef long (__attribute__((stdcall)) *dp_t)(void *, uint32_t, uint32_t, const void *, uint32_t, uint32_t);
    ((dp_t)VT(d, 0x70))(d, 2, 0x1c4, v, (uint32_t)count, 0x18);
}
void plat_set_current_viewport(void) { void *d = D3D_DEV; ((d3d_fn1p)VT(d, 0x30))(d, D3D_VP); }
int plat_get_render_state(int state) { (void)state; return 0; }
void plat_clear_depth(void *viewport, int x, int y, int w, int h, float z) {
    /* IDirect3DViewport3::Clear2(count, rects, flags=D3DCLEAR_ZBUFFER, color=0, z, stencil=0) */
    typedef long (__attribute__((stdcall)) *cl_t)(void *, uint32_t, void *, uint32_t, uint32_t, float, uint32_t);
    int32_t r[4] = { x, y, x + w, y + h };
    ((cl_t)VT(viewport, 0x50))(viewport, 1, r, 2, 0, z, 0);
}

/* --- DirectDraw/Direct3D-объекты: прямые вызовы vtable объектов игры --- */
typedef long (__attribute__((stdcall)) *dd_f1)(void *, void *);
typedef long (__attribute__((stdcall)) *dd_f2)(void *, void *, void *);
typedef long (__attribute__((stdcall)) *dd_f3)(void *, void *, void *, void *);
typedef long (__attribute__((stdcall)) *dd_f4)(void *, void *, void *, void *, void *);
typedef long (__attribute__((stdcall)) *dd_f6)(void *, void *, void *, void *, void *, void *);
typedef long (__attribute__((stdcall)) *dd_f0)(void *);
static void *wrap_out(long hr, void *out) { return hr == 0 ? out : (void *)0; }
void *plat_dd_create_surface(void *dd, const void *desc) {   /* IDirectDraw::CreateSurface(desc, &out, NULL) */
    void *out = 0; long hr = ((dd_f3)VT(dd, 0x18))(dd, (void *)desc, &out, 0); return wrap_out(hr, out); }
int32_t plat_dd_set_display_mode(void *dd, int w, int h, int bpp) {   /* SetDisplayMode(w,h,bpp,0,0) */
    return ((dd_f6)VT(dd, 0x54))(dd, (void *)(intptr_t)w, (void *)(intptr_t)h, (void *)(intptr_t)bpp, 0, 0); }
void *plat_dd_create_clipper(void *dd) {   /* CreateClipper(0, &out, NULL) */
    void *out = 0; long hr = ((dd_f3)VT(dd, 0x10))(dd, 0, &out, 0); return wrap_out(hr, out); }
int32_t plat_dd_set_clipper(void *s, void *c) { return ((dd_f1)VT(s, 0x70))(s, c); }
int32_t plat_dd_attach_surface(void *s, void *a) { return ((dd_f1)VT(s, 0x0c))(s, a); }
void *plat_dd_get_attached(void *s, uint32_t caps) {   /* GetAttachedSurface(&caps, &out) */
    void *out = 0; uint32_t c = caps; long hr = ((dd_f2)VT(s, 0x30))(s, &c, &out); return wrap_out(hr, out); }
void plat_dd_release(void *o) { ((dd_f0)VT(o, 8))(o); }
int32_t plat_dd_is_lost(void *s) { return ((dd_f0)VT(s, 0x60))(s); }
int32_t plat_dd_restore(void *s) { return ((dd_f0)VT(s, 0x6c))(s); }
int32_t plat_dd_fill_rect(void *s, int x0, int y0, int x1, int y1, uint32_t pixel) {
    /* Blt(&rect, NULL, NULL, DDBLT_WAIT|DDBLT_COLORFILL, &DDBLTFX{dwSize=100, dwFillColor@0x50}) */
    int32_t rc[4] = { x0, y0, x1, y1 };
    uint32_t fx[25]; for (int i = 0; i < 25; i++) fx[i] = 0;
    fx[0] = 100; fx[20] = pixel;
    return ((dd_f6)VT(s, 0x14))(s, rc, 0, 0, (void *)0x01000400, fx); }
void *plat_d3d_create_device(void *d3d, const void *iid, void *surf) {   /* IDirect3D3::CreateDevice(iid, surf, &out, NULL) */
    void *out = 0; long hr = ((dd_f4)VT(d3d, 0x20))(d3d, (void *)iid, surf, &out, 0); return wrap_out(hr, out); }
void *plat_d3d_create_viewport(void *d3d) {   /* CreateViewport(&out, NULL) */
    void *out = 0; long hr = ((dd_f2)VT(d3d, 0x18))(d3d, &out, 0); return wrap_out(hr, out); }
int32_t plat_d3d_add_viewport(void *dev, void *vp) { return ((dd_f1)VT(dev, 0x14))(dev, vp); }
int32_t plat_d3d_set_viewport_rect(void *vp, int w, int h) {   /* IDirect3DViewport3::SetViewport(D3DVIEWPORT) */
    struct { uint32_t size, x, y; int32_t w, h; float clip_x, clip_y, clip_w, clip_h, min_z, max_z; } v;
    v.size = 0x2c; v.x = 0; v.y = 0; v.w = w; v.h = h; v.clip_x = 0; v.clip_y = 0; v.clip_w = (float)w; v.clip_h = (float)h; v.min_z = 0; v.max_z = 1.0f;
    return ((dd_f1)VT(vp, 0x44))(vp, &v); }
int plat_dd_stub_count(void) { return 0; }
int plat_dd_stub_last_fill(int32_t *r, uint32_t *px) { (void)r; (void)px; return 0; }

int32_t plat_dd_set_cooperative(void *dd, void *hwnd, uint32_t flags) { return (int32_t)((int32_t (__stdcall *)(void *, void *, uint32_t))VT(dd, 0x50))(dd, hwnd, flags); }
int plat_dd_last_coop(void) { return 0; }

/* --- палитры, размер поверхности, SetTexture --- */
int32_t plat_dd_get_surface_size(void *s, int32_t *w, int32_t *h) {   /* GetSurfaceDesc (vtable 0x58): высота +8, ширина +0xc */
    uint32_t d[31]; for (int i = 0; i < 31; i++) d[i] = 0; d[0] = 0x7c;
    long hr = ((dd_f1)VT(s, 0x58))(s, d); *h = (int32_t)d[2]; *w = (int32_t)d[3]; return hr; }
void *plat_dd_create_palette(void *dd, uint32_t flags, const void *e) {   /* IDirectDraw::CreatePalette(flags, entries, &out, NULL) */
    void *out = 0; long hr = ((dd_f4)VT(dd, 0x14))(dd, (void *)(uintptr_t)flags, (void *)e, &out, 0); return wrap_out(hr, out); }
int32_t plat_dd_surface_set_palette(void *s, void *p) { return ((dd_f1)VT(s, 0x7c))(s, p); }
int32_t plat_dd_palette_set_entries(void *p, uint32_t f, uint32_t first, uint32_t n, const void *e) {
    return ((dd_f4)VT(p, 0x18))(p, (void *)(uintptr_t)f, (void *)(uintptr_t)first, (void *)(uintptr_t)n, (void *)e); }
void plat_tex_palette_changed(void *t, uint32_t first, uint32_t n) { ((dd_f2)VT(t, 0x10))(t, (void *)(uintptr_t)first, (void *)(uintptr_t)n); }
void plat_set_texture(int stage, void *tex) { void *d = D3D_DEV; ((dd_f2)VT(d, 0x98))(d, (void *)(intptr_t)stage, tex); }
void *plat_stub_last_texture(int *stage) { if (stage) *stage = 0; return 0; }
int plat_stub_pal_stats(int *a, int *b) { *a = 0; *b = 0; return 0; }
int plat_dd_stub_last_desc(uint32_t *d) { (void)d; return 0; }

/* --- DirectInput (IDirectInputDevice vtable Game.exe): Release 8, GetDeviceState 0x24, SetDataFormat 0x2c, Acquire 0x1c, Unacquire 0x20 --- */
void plat_di_release(void *o) { ((dd_f0)VT(o, 8))(o); }
void plat_di_unacquire(void *d) { ((dd_f0)VT(d, 0x20))(d); }
int32_t plat_di_set_format(void *d, int kind) {
    static const uintptr_t fmt[3] = { 0x0052a610, 0x005295f0, 0x0052a8f0 };
    if (kind < 0 || kind > 2) return -1;
    return ((dd_f1)VT(d, 0x2c))(d, (void *)fmt[kind]);
}
int32_t plat_di_acquire(void *d) { return ((dd_f0)VT(d, 0x1c))(d); }
int32_t plat_di_get_state(void *d, uint32_t size, void *buf) { return ((dd_f2)VT(d, 0x24))(d, (void *)(uintptr_t)size, buf); }
int32_t plat_di_poll(void *d) { return ((dd_f0)VT(d, 0x64))(d); }
void plat_di_stub_joy(int32_t x, int32_t y, int32_t rc) { (void)x; (void)y; (void)rc; }
int plat_di_stub_counts(int *r, int *u, int *e, int *k) { *r = *u = *e = *k = 0; return 0; }
void plat_di_stub_fail_state(int on) { (void)on; }

/* --- DirectInput Force Feedback (IDirectInputDevice2: EnumEffects 0x4c, CreateEffect 0x48; IDirectInputEffect: SetParameters 0x18) --- */
static int __attribute__((stdcall)) di_enum_cb(const uint32_t *info, uint32_t *out) {   /* 004e4379: GUID из DIEFFECTINFO (+4) */
    if (out) { out[0] = info[1]; out[1] = info[2]; out[2] = info[3]; out[3] = info[4]; }
    return 0;
}
int32_t plat_di_enum_effect(void *d, uint8_t guid[16]) { return ((dd_f3)VT(d, 0x4c))(d, (void *)di_enum_cb, guid, (void *)1); }
int32_t plat_di_create_effect(void *d, int kind, const uint8_t *guid, void **out) {
    uint32_t m = 0, dir[2] = { 0, 0 }, ax[2] = { 0, 4 }, eff[13];
    if (kind == 0) {
        eff[0] = 0x34; eff[1] = 0x12; eff[2] = 250000; eff[3] = 0; eff[4] = 10000; eff[5] = 0xffffffff; eff[6] = 0; eff[7] = 2;
        eff[8] = (uint32_t)(uintptr_t)ax; eff[9] = (uint32_t)(uintptr_t)dir; eff[10] = 0; eff[11] = 4; eff[12] = (uint32_t)(uintptr_t)&m;
    } else {
        uint32_t ax1 = 4, dir1 = 1; m = 5000;
        eff[0] = 0x34; eff[1] = 0x12; eff[2] = 15000; eff[3] = 0; eff[4] = 0x1d4c; eff[5] = 0xffffffff; eff[6] = 0; eff[7] = 1;
        eff[8] = (uint32_t)(uintptr_t)&ax1; eff[9] = (uint32_t)(uintptr_t)&dir1; eff[10] = 0; eff[11] = 4; eff[12] = (uint32_t)(uintptr_t)&m;
        return ((dd_f4)VT(d, 0x48))(d, (void *)guid, eff, out, 0);
    }
    return ((dd_f4)VT(d, 0x48))(d, (void *)guid, eff, out, 0);
}
int32_t plat_di_set_effect(void *e, int kind, int32_t dx, int32_t dy, int32_t mag) {
    uint32_t eff[13]; int32_t dir[2] = { dx, dy }; uint32_t ax = 4; int32_t m = mag;
    for (int i = 0; i < 13; i++) eff[i] = 0;
    eff[0] = 0x34; eff[1] = 0x12; eff[11] = 4; eff[12] = (uint32_t)(uintptr_t)&m;
    if (kind == 0) { eff[7] = 2; eff[9] = (uint32_t)(uintptr_t)dir; return ((dd_f2)VT(e, 0x18))(e, eff, (void *)0x20000140); }
    eff[8] = (uint32_t)(uintptr_t)&ax;   /* cAxes остаётся 0, как в оригинале */
    return ((dd_f2)VT(e, 0x18))(e, eff, (void *)0x20000100);
}
int plat_di_stub_effects(int *c, int *ck, int *s, int *sk, int32_t *dx, int32_t *dy, int32_t *m) { *c = *ck = *s = *sk = 0; *dx = *dy = *m = 0; return 0; }
void plat_di_stub_fail_enum(int on) { (void)on; }

/* --- DirectDrawCreate / GetDisplayMode --- */
extern long __attribute__((stdcall)) DirectDrawCreate(void *guid, void **out, void *outer);
void *plat_dd_create(const void *guid) { void *o = 0; return DirectDrawCreate((void *)guid, &o, 0) == 0 ? o : (void *)0; }
int32_t plat_dd_get_display_flags(void *dd, uint32_t *f) {   /* DDSURFACEDESC (0x6c): flags +4, ddpfPixelFormat.dwFlags +0x4c */
    uint32_t d[27]; for (int i = 0; i < 27; i++) d[i] = 0; d[0] = 0x6c; d[1] = 0x1000;
    long hr = ((dd_f1)VT(dd, 0x30))(dd, d); *f = d[19]; return hr; }
void plat_dd_stub_display(uint32_t f, int a, int b) { (void)f; (void)a; (void)b; }
