#ifndef PLAT_H
#define PLAT_H
#include <stdint.h>
/* Platform interface: game code in game/ calls only this. */
/* --- system --- */
uint32_t plat_time_ms(void);
void plat_sleep_ms(uint32_t ms);
void plat_local_hms(int *h, int *m, int *s); /* GetLocalTime */
void plat_log(const char *fmt, ...);
void *plat_file_open(const char *path, const char *mode); /* case-insensitive lookup */
/* --- window & input --- */
int plat_window_open(const char *title, int w, int h, int fullscreen);
int plat_poll_events(void); /* returns 0 on quit request */
int plat_key_down(int scancode);
void plat_window_close(void);
/* --- render (declared; SDL/OpenGL impl in sdl/plat_render.c) --- */
typedef struct { float x, y, z, rhw; uint32_t color, specular; float u, v; } plat_vertex;
int plat_tex_create(int w, int h, const uint32_t *rgba);
void plat_tex_bind(int tex);
void plat_tex_free(int tex);
void plat_set_blend(int enable, int src, int dst);
void plat_set_zbuffer(int test, int write);
void plat_draw_tris(const plat_vertex *v, int count);
void plat_clear(uint32_t color, int clear_z);
void plat_draw_lines(const plat_vertex *v, int count);     /* список линий, count чётный */
void plat_set_current_viewport(void);                      /* D3D SetCurrentViewport (SDL: no-op) */
void plat_clear_depth(void *viewport, int x, int y, int w, int h, float z); /* очистка Z в прямоугольнике */
int plat_get_render_state(int state);                      /* последнее установленное значение (для тестов; hook: 0) */
void plat_flip(void);
void plat_blit2d(int tex, int sx, int sy, int sw, int sh, int dx, int dy);
/* Состояние устройства в терминах Direct3D 6/7 (номера D3DRENDERSTATETYPE / D3DTEXTURESTAGESTATETYPE и значения как в DX):
   state: 7 ZENABLE, 14 ZWRITEENABLE, 15 ALPHATESTENABLE, 19 SRCBLEND, 20 DESTBLEND, 22 CULLMODE, 23 ZFUNC (1..8 = D3DCMP), 24 ALPHAREF, 25 ALPHAFUNC, 27 ALPHABLENDENABLE.
   В SDL-варианте применяется к GL, в hook-варианте уходит в IDirect3DDevice3 игры. */
void plat_scene_begin(void);
void plat_scene_end(void);
void plat_set_render_state(int state, uint32_t value);
void plat_set_tex_stage(int stage, int type, uint32_t value);   /* type 1 COLOROP, 16 MAGFILTER, 17 MINFILTER */
void plat_set_viewport(int x, int y, int w, int h);
/* Константы смешивания = значения D3DBLEND (1 ZERO, 2 ONE, 3 SRCCOLOR, 4 INVSRCCOLOR, 5 SRCALPHA, 6 INVSRCALPHA, 7 DESTALPHA, 8 INVDESTALPHA, 9 DESTCOLOR, 10 INVDESTCOLOR).
   color/specular вершины = 0xAARRGGBB; x,y в пикселях окна, z 0..1, rhw = 1/w (0 → 1). */
/* Подключение GL-контекста (SDL-окно или OSMesa); swap может быть NULL (offscreen). */
int plat_render_attach(void *(*get_proc)(const char *), void (*swap)(void), int w, int h);
int plat_render_offscreen(int w, int h);                 /* OSMesa; <0 если нет в сборке */
int plat_render_readback(uint32_t *rgba_topdown);        /* w*h пикселей 0xAABBGGRR (байты R,G,B,A) */
void plat_render_shutdown(void);
/* Звук и CD-аудио */
int  plat_snd_create(const void *pcm, int bytes, int rate, int channels, int bits);
void plat_snd_destroy(int h);
void plat_snd_play(int h, int loop);
void plat_snd_stop(int h);
void plat_snd_set(int h, int volume, int pitch_hz, int pan);
void plat_snd_pos3d(int h, float x, float y, float z);
/* volume/pan как в DirectSound (сотые дБ). Микшер: 44100 Гц, стерео S16; plat_snd_mix пригоден для тестов без устройства. */
void plat_snd_mix(int16_t *out_stereo, int frames);
int  plat_snd_open(void);                                /* SDL_audio, 1 = ок */
void plat_snd_close(void);
int  plat_cd_play(int track);
void plat_cd_stop(void);
int  plat_cd_current(void);
#endif
