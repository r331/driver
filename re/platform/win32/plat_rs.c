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
