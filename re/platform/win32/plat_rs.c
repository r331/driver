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
int plat_cd_play(int t){(void)t;return 0;}
void plat_cd_stop(void){}
int plat_cd_current(void){return 0;}
