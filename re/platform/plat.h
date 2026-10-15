#ifndef PLAT_H
#define PLAT_H
#include <stdint.h>
/* Platform interface: game code in game/ calls only this. */
/* --- system --- */
uint32_t plat_time_ms(void);
void plat_sleep_ms(uint32_t ms);
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
void plat_flip(void);
void plat_blit2d(int tex, int sx, int sy, int sw, int sh, int dx, int dy);
/* Звук и CD-аудио */
int  plat_snd_create(const void *pcm, int bytes, int rate, int channels, int bits);
void plat_snd_destroy(int h);
void plat_snd_play(int h, int loop);
void plat_snd_stop(int h);
void plat_snd_set(int h, int volume, int pitch_hz, int pan);
void plat_snd_pos3d(int h, float x, float y, float z);
int  plat_cd_play(int track);
void plat_cd_stop(void);
int  plat_cd_current(void);
#endif
