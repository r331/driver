/* v2.09: эмуляция DirectSound поверх собственного микшера (только игра — g_game_present в plat_dd.c; тесты — прежние
   учётные заглушки). Буферы: первичный (флаг 0x1, Play/SetFormat — без действия), вторичные (PCM 8/16 бит, 1/2 канала,
   своя частота из WAVEFORMATEX; Lock — вся память буфера, Unlock — без копирования), дубликаты делят PCM (счётчик ссылок),
   громкость (сотые дБ), частота (0 — исходная), позиция, цикл (Play флаг 1), GetStatus (1 PLAYING | 4 LOOPING).
   3D: слушатель (позиция, ориентация front/top, DistanceFactor/DopplerFactor/RolloffFactor — 0048beee), буфер
   IDirectSound3DBuffer (позиция, режим 0 NORMAL / 1 HEADRELATIVE / 2 DISABLE): ослабление DS3D
   min/(min + rolloff·(d − min)) при MinDistance 1 (умолчание DirectSound), панорама по проекции на ось right = top × front.
   Доплер не моделируется. Микширование — dsm_mix() из plat_snd_mix (44100 Гц, стерео S16). */
#include "../plat.h"
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <stdio.h>
#define DSM_TAG 0x44534246u
enum { K_PRIMARY = 1, K_SEC = 2, K_LISTENER = 3, K_3D = 4 };
typedef struct { uint8_t *data; uint32_t bytes; int refs; } dsm_pcm;
typedef struct dsm_buf {
  uint32_t tag; int kind; dsm_pcm *pcm; int rate, ch, bits;
  int playing, loop; double pos; int32_t vol; uint32_t freq;
  int mode3d; float x, y, z; struct dsm_buf *owner, *b3d; int live;
} dsm_buf;
#define DSM_MAX 512
static dsm_buf *g_bufs[DSM_MAX];
static float g_lp[3], g_lf[3] = { 0, 0, 1 }, g_lt[3] = { 0, 1, 0 }, g_roll = 1.0f, g_distf = 1.0f, g_dopf = 1.0f;
void plat_snd_lockdev(int on);
int dsm_is(const void *o) { return o && ((const dsm_buf *)o)->tag == DSM_TAG; }
static dsm_buf *nb(int kind) {
  dsm_buf *b = (dsm_buf *)calloc(1, sizeof *b); if (!b) return NULL;
  b->tag = DSM_TAG; b->kind = kind; b->live = 1;
  plat_snd_lockdev(1);
  for (int i = 0; i < DSM_MAX; i++) if (!g_bufs[i]) { g_bufs[i] = b; break; }
  plat_snd_lockdev(0);
  return b;
}
static int g_stat_create, g_stat_play, g_stat_dup;
int dsm_stats(int *cr, int *pl, int *dup) { *cr = g_stat_create; *pl = g_stat_play; *dup = g_stat_dup; return 1; }
int32_t dsm_create_buffer(uint32_t fl, uint32_t bytes, const void *wfx, void **out) {
  dsm_buf *b = nb((fl & 1) ? K_PRIMARY : K_SEC); *out = b; if (!b) return -1;
  if (b->kind == K_SEC) {
    const uint8_t *w = (const uint8_t *)wfx;
    b->ch = 1; b->rate = 22050; b->bits = 16;
    if (w) { b->ch = w[2] | w[3] << 8; b->rate = (int)(w[4] | w[5] << 8 | w[6] << 16 | (uint32_t)w[7] << 24); b->bits = w[14] | w[15] << 8; }
    if (b->ch < 1 || b->ch > 2) b->ch = 1;
    if (b->bits != 8 && b->bits != 16) b->bits = 16;
    if (b->rate < 100 || b->rate > 200000) b->rate = 22050;
    b->pcm = (dsm_pcm *)calloc(1, sizeof *b->pcm);
    if (b->pcm) { b->pcm->bytes = bytes; b->pcm->refs = 1; b->pcm->data = (uint8_t *)calloc(bytes ? bytes : 1, 1); }
    if (!b->pcm || !b->pcm->data) return -1;
    g_stat_create++;
  }
  return 0;
}
int32_t dsm_duplicate(void *src, void **out) {
  dsm_buf *s = (dsm_buf *)src; *out = NULL;
  if (!dsm_is(s) || s->kind != K_SEC || !s->pcm) return -1;
  dsm_buf *b = nb(K_SEC); if (!b) return -1;
  b->pcm = s->pcm; s->pcm->refs++; b->rate = s->rate; b->ch = s->ch; b->bits = s->bits;
  *out = b; g_stat_dup++; return 0;
}
/* QI: ksprop → 0 (вызывающий отдаёт учётную заглушку); первичный → слушатель; вторичный → 3D-буфер */
void *dsm_qi(void *o) {
  dsm_buf *s = (dsm_buf *)o;
  if (s->kind == K_PRIMARY) return nb(K_LISTENER);
  if (s->kind == K_SEC) { dsm_buf *d = nb(K_3D); if (d) { d->owner = s; s->b3d = d; } return d; }
  return NULL;
}
void dsm_release(void *o) {
  dsm_buf *b = (dsm_buf *)o;
  plat_snd_lockdev(1);
  for (int i = 0; i < DSM_MAX; i++) if (g_bufs[i] == b) g_bufs[i] = NULL;
  for (int i = 0; i < DSM_MAX; i++) if (g_bufs[i] && g_bufs[i]->owner == b) g_bufs[i]->owner = NULL;
  if (b->kind == K_3D && b->owner) b->owner->b3d = NULL;
  if (b->pcm && --b->pcm->refs <= 0) { free(b->pcm->data); free(b->pcm); }
  plat_snd_lockdev(0);
  b->tag = 0; free(b);
}
int32_t dsm_lock(void *o, uint32_t bytes, void **p1, uint32_t *n1, void **p2, uint32_t *n2) {
  dsm_buf *b = (dsm_buf *)o;
  if (b->kind != K_SEC || !b->pcm || bytes > b->pcm->bytes) return -1;
  *p1 = b->pcm->data; *n1 = bytes; *p2 = NULL; *n2 = 0; return 0;
}
static dsm_buf *sec(void *o) { dsm_buf *b = (dsm_buf *)o; return b->kind == K_SEC ? b : NULL; }
static dsm_buf *b3(void *o) { dsm_buf *b = (dsm_buf *)o; return b->kind == K_3D ? b : NULL; }
int32_t dsm_play(void *o, uint32_t fl) {
  dsm_buf *b = sec(o); if (!b) return 0;      /* первичный — без действия */
  plat_snd_lockdev(1); b->playing = 1; b->loop = (fl & 1) != 0; plat_snd_lockdev(0); g_stat_play++;
  if (getenv("RE_SND_LOG")) fprintf(stderr, "[ds] play %p pcm %u B %d Hz %dch %db loop %d vol %d freq %u 3d %d pos %.0f\n", (void *)b, b->pcm ? b->pcm->bytes : 0, b->rate, b->ch, b->bits,
      b->loop, b->vol, b->freq, b->b3d ? b->b3d->mode3d : -1, b->pos);
  return 0;
}
int32_t dsm_stop(void *o) { dsm_buf *b = sec(o); if (b && b->playing && getenv("RE_SND_LOG")) fprintf(stderr, "[ds] stop %p\n", (void *)b); if (b) { plat_snd_lockdev(1); b->playing = 0; plat_snd_lockdev(0); } return 0; }
int32_t dsm_set_position(void *o, uint32_t pos) {
  dsm_buf *b = sec(o); if (!b) return 0;
  int fb = b->ch * (b->bits / 8); plat_snd_lockdev(1); b->pos = (double)(pos / (uint32_t)fb); plat_snd_lockdev(0); return 0;
}
int32_t dsm_set_volume(void *o, int32_t v) { dsm_buf *b = sec(o); if (b) b->vol = v; return 0; }
int32_t dsm_set_frequency(void *o, uint32_t hz) { dsm_buf *b = sec(o); if (b) b->freq = hz; return 0; }
int32_t dsm_get_status(void *o, uint32_t *st) {
  dsm_buf *b = sec(o); if (st) *st = (b && b->playing) ? (1u | (b->loop ? 4u : 0u)) : 0u; return 0;
}
int32_t dsm_3d_mode(void *o, uint32_t m) { dsm_buf *b = b3(o); if (b) b->mode3d = (int)m; return 0; }
int32_t dsm_3d_pos(void *o, float x, float y, float z) { dsm_buf *b = b3(o); if (b) { b->x = x; b->y = y; b->z = z; } return 0; }
void dsm_listener_pos(float x, float y, float z) { g_lp[0] = x; g_lp[1] = y; g_lp[2] = z; }
void dsm_listener_orient(const float *s) { memcpy(g_lf, s, 12); memcpy(g_lt, s + 3, 12); }
void dsm_listener_factors(int which, float v) { if (which == 0) g_distf = v; else if (which == 1) g_dopf = v; else g_roll = v; }
float dsm_listener_rolloff(void) { return g_roll; }

static float db_gain(int32_t h) { if (h >= 0) return 1.0f; if (h <= -10000) return 0.0f; return powf(10.0f, (float)h / 2000.0f); }
static float smp(const dsm_buf *b, int64_t fr, int c) {
  int i = (int)(fr * b->ch + (c < b->ch ? c : 0));
  if (b->bits == 8) return (b->pcm->data[i] - 128) / 128.0f;
  int16_t v; memcpy(&v, b->pcm->data + 2 * i, 2); return v / 32768.0f;
}
static void gains3d(const dsm_buf *b, float *gl, float *gr) {
  *gl = *gr = 1.0f;
  const dsm_buf *d = b->b3d;
  if (!d || d->mode3d == 2) return;
  float v[3] = { d->x, d->y, d->z };
  if (d->mode3d != 1) { v[0] -= g_lp[0]; v[1] -= g_lp[1]; v[2] -= g_lp[2]; }
  float dist = sqrtf(v[0] * v[0] + v[1] * v[1] + v[2] * v[2]);
  const float mind = 1.0f;
  float g = dist <= mind ? 1.0f : mind / (mind + g_roll * (dist - mind));
  float p = 0.0f;
  if (dist > 1e-3f) {
    float r[3] = { g_lt[1] * g_lf[2] - g_lt[2] * g_lf[1], g_lt[2] * g_lf[0] - g_lt[0] * g_lf[2], g_lt[0] * g_lf[1] - g_lt[1] * g_lf[0] };
    float rl = sqrtf(r[0] * r[0] + r[1] * r[1] + r[2] * r[2]);
    if (rl > 1e-6f) p = (v[0] * r[0] + v[1] * r[1] + v[2] * r[2]) / (rl * dist);
  }
  if (d->mode3d == 1 && dist <= 1e-3f) p = 0.0f;
  *gl = g * (p > 0 ? 1.0f - 0.7f * p : 1.0f);
  *gr = g * (p < 0 ? 1.0f + 0.7f * p : 1.0f);
}
/* v2.10: мягкий ограничитель — голоса суммируются в float (нормировано к 1.0), до порога DSM_KNEE сигнал не меняется,
   выше — tanh-колено: y = K + (1 − K)·tanh((x − K)/(1 − K)) — непрерывно, гладко (производная 1 на пороге) и |y| < 1,
   поэтому жёсткого клиппинга (насыщения 32767) больше нет; до v2.09 сумма 8 голосов двигателя обрезалась (62 отсчёта в пике). */
#define DSM_KNEE 0.7f
static float dsm_soft(float x) {
  float a = fabsf(x);
  if (a <= DSM_KNEE) return x;
  float y = DSM_KNEE + (1.0f - DSM_KNEE) * tanhf((a - DSM_KNEE) / (1.0f - DSM_KNEE));
  return x < 0 ? -y : y;
}
float dsm_soft_limit(float x) { return dsm_soft(x); }   /* для теста */
void dsm_mix(int16_t *out, int frames) {
  enum { CH = 1024 };
  static float acc[2 * CH];
  for (int base = 0; base < frames; base += CH) {
    int n = frames - base < CH ? frames - base : CH;
    int16_t *o = out + 2 * base;
    for (int i = 0; i < 2 * n; i++) acc[i] = o[i] / 32768.0f;   /* то, что уже смешано до нас (plat_snd) */
    for (int h = 0; h < DSM_MAX; h++) {
      dsm_buf *b = g_bufs[h];
      if (!b || b->kind != K_SEC || !b->playing || !b->pcm) continue;
      int fb = b->ch * (b->bits / 8); int64_t total = b->pcm->bytes / (uint32_t)fb;
      if (total < 1) { b->playing = 0; continue; }
      double step = (double)(b->freq ? b->freq : (uint32_t)b->rate) / 44100.0;
      float g = db_gain(b->vol), g3l, g3r; gains3d(b, &g3l, &g3r);
      float gl = g * g3l, gr = g * g3r;
      for (int f = 0; f < n; f++) {
        int64_t i0 = (int64_t)b->pos; if (i0 >= total) i0 = total - 1;
        float fr = (float)(b->pos - (double)i0); int64_t i1 = i0 + 1;
        if (i1 >= total) i1 = b->loop ? 0 : i0;
        float l = smp(b, i0, 0) * (1 - fr) + smp(b, i1, 0) * fr, r = b->ch > 1 ? smp(b, i0, 1) * (1 - fr) + smp(b, i1, 1) * fr : l;
        acc[2 * f] += l * gl; acc[2 * f + 1] += r * gr;
        b->pos += step;
        if (b->pos >= (double)total) { if (b->loop) b->pos -= (double)total; else { b->playing = 0; b->pos = 0; break; } }
      }
    }
    for (int i = 0; i < 2 * n; i++) { float y = dsm_soft(acc[i]) * 32760.0f;   /* tanhf в float доходит до 1.0 только при x ≫ 1 — запас до 32767 */ o[i] = (int16_t)lrintf(y); }
  }
}
int dsm_active(void) { int n = 0; for (int h = 0; h < DSM_MAX; h++) if (g_bufs[h] && g_bufs[h]->kind == K_SEC && g_bufs[h]->playing) n++; return n; }
