#include "../plat.h"
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <SDL.h>
/* Таблица звуковых буферов + программный микшер (44100 Гц, стерео, S16). volume и pan — как в DirectSound:
   сотые доли дБ (0 = максимум, -10000 = тишина; pan -10000 лево .. +10000 право). Положение 3D пока хранится, но не используется. */
static SDL_AudioDeviceID g_dev;
#define LOCK() do{ if(g_dev) SDL_LockAudioDevice(g_dev); }while(0)
#define UNLOCK() do{ if(g_dev) SDL_UnlockAudioDevice(g_dev); }while(0)
#define SND_MAX 256
typedef struct { void *pcm; int bytes, rate, ch, bits, playing, loop, vol, pitch, pan; double pos; float x, y, z; } snd_t;
static snd_t snds[SND_MAX];
int plat_snd_create(const void*p,int b,int r,int c,int bits){
  if(!p||b<=0) return 0;
  for(int i=1;i<SND_MAX;i++) if(!snds[i].pcm){
    snd_t*s=&snds[i]; memset(s,0,sizeof *s);
    s->pcm=malloc((size_t)b); if(!s->pcm) return 0;
    memcpy(s->pcm,p,(size_t)b); s->bytes=b; s->rate=r; s->ch=c; s->bits=bits; s->pitch=r;
    return i; }
  return 0; }
static snd_t*S(int h){return (h>0&&h<SND_MAX&&snds[h].pcm)?&snds[h]:NULL;}
void plat_snd_destroy(int h){snd_t*s=S(h); if(s){LOCK(); free(s->pcm); memset(s,0,sizeof *s); UNLOCK();}}
void plat_snd_play(int h,int l){snd_t*s=S(h); if(s){LOCK(); if(!s->playing) s->pos=0; s->playing=1;s->loop=l; UNLOCK();}}
void plat_snd_stop(int h){snd_t*s=S(h); if(s){LOCK(); s->playing=0; UNLOCK();}}
void plat_snd_set(int h,int v,int p,int n){snd_t*s=S(h); if(s){LOCK(); s->vol=v;s->pitch=p>0?p:s->rate;s->pan=n; UNLOCK();}}
void plat_snd_pos3d(int h,float x,float y,float z){snd_t*s=S(h); if(s){s->x=x;s->y=y;s->z=z;}}

#define SND_OUT_RATE 44100
static float smp(const snd_t*s,int64_t fr,int c){ /* выборка кадра fr, канал c → -1..1 */
  int ch=s->ch>1?2:1; int i=(int)(fr*ch+(c<ch?c:0));
  if(s->bits==8) return (((const uint8_t*)s->pcm)[i]-128)/128.0f;
  return ((const int16_t*)s->pcm)[i]/32768.0f; }
static float db_gain(int hundredths){ if(hundredths>=0) return 1.0f; if(hundredths<=-10000) return 0.0f; return powf(10.0f,(float)hundredths/2000.0f); }
void plat_snd_mix(int16_t *out,int frames){
  memset(out,0,(size_t)frames*2*sizeof *out);
  for(int h=1;h<SND_MAX;h++){ snd_t*s=&snds[h]; if(!s->pcm||!s->playing) continue;
    int ch=s->ch>1?2:1, bps=s->bits==8?1:2; int64_t total=s->bytes/(ch*bps); if(total<1){s->playing=0;continue;}
    double step=(double)(s->pitch>0?s->pitch:s->rate)/SND_OUT_RATE;
    float g=db_gain(s->vol), gl=g*(s->pan>0?db_gain(-s->pan):1.0f), gr=g*(s->pan<0?db_gain(s->pan):1.0f);
    for(int f=0;f<frames;f++){
      int64_t i0=(int64_t)s->pos; float fr=(float)(s->pos-(double)i0); int64_t i1=i0+1;
      if(i1>=total) i1=s->loop?0:i0;
      float l=smp(s,i0,0)*(1-fr)+smp(s,i1,0)*fr, r=ch>1?smp(s,i0,1)*(1-fr)+smp(s,i1,1)*fr:l;
      int a=out[2*f]+(int)(l*gl*32767.0f), b=out[2*f+1]+(int)(r*gr*32767.0f);
      out[2*f]=(int16_t)(a>32767?32767:a<-32768?-32768:a); out[2*f+1]=(int16_t)(b>32767?32767:b<-32768?-32768:b);
      s->pos+=step;
      if(s->pos>=(double)total){ if(s->loop) s->pos-=(double)total; else { s->playing=0; break; } } } } }
static void SDLCALL audio_cb(void*u,Uint8*st,int len){ (void)u; plat_snd_mix((int16_t*)st,len/4); }
int plat_snd_open(void){
  if(g_dev) return 1;
  if(SDL_InitSubSystem(SDL_INIT_AUDIO)<0) return 0;
  SDL_AudioSpec want; SDL_zero(want); want.freq=SND_OUT_RATE; want.format=AUDIO_S16SYS; want.channels=2; want.samples=1024; want.callback=audio_cb;
  g_dev=SDL_OpenAudioDevice(NULL,0,&want,NULL,0); if(!g_dev) return 0;
  SDL_PauseAudioDevice(g_dev,0); return 1; }
void plat_snd_close(void){ if(g_dev){ SDL_CloseAudioDevice(g_dev); g_dev=0; } }
static int g_cd_track=0;
int plat_cd_play(int t){ if(t<1||t>99) return 0; g_cd_track=t; return 1;}
void plat_cd_stop(void){ g_cd_track=0; }
int plat_cd_current(void){ return g_cd_track; }

/* --- CD-аудио/таймеры (SDL): привода нет — учётная заглушка для тестов; таймеры на SDL_AddTimer --- */
#include <stdlib.h>
static int g_cdn, g_cdaux = -1, g_cdopen, g_cdplay;
static uint32_t g_cdfrom, g_cdto, g_cdvol;
void plat_cd_stub_set(int n, int aux) { g_cdn = n; g_cdaux = aux; }
int plat_cd_stub_state(uint32_t *f, uint32_t *t, uint32_t *v) { *f = g_cdfrom; *t = g_cdto; *v = g_cdvol; return g_cdplay; }
int plat_cd_open(void *hwnd) { (void)hwnd; if (g_cdn <= 0) return 0; g_cdopen = 1; return 1; }
void plat_cd_close(void) { g_cdopen = 0; g_cdplay = 0; }
int plat_cd_track_count(void) { return g_cdopen ? g_cdn : -1; }
int plat_cd_track_info(int t, uint32_t *pos, uint32_t *len) {
  if (!g_cdopen || t < 1 || t > g_cdn) return 1;
  *pos = (uint32_t)t | (uint32_t)(t * 2) << 8;     /* T, M */
  *len = 3u | 30u << 8;                            /* M=3, S=30 */
  return 0;
}
int plat_cd_play_range(void *hwnd, uint32_t from, uint32_t to) { (void)hwnd; if (!g_cdopen) return 0; g_cdfrom = from; g_cdto = to; g_cdplay = 1; return 1; }
int plat_cd_play_to(uint32_t to) { if (!g_cdopen) return 0; g_cdto = to; g_cdplay = 1; return 1; }
void plat_cd_pause(void) { g_cdplay = 0; }
int plat_aux_find_cd(void) { return g_cdaux; }
void plat_aux_set_volume(int dev, uint32_t lr) { if (dev == g_cdaux) g_cdvol = lr; }
int plat_timer_period_begin(unsigned ms) { (void)ms; return 0; }
void plat_timer_period_end(unsigned ms) { (void)ms; }
typedef struct { void (*cb)(unsigned); unsigned flags; unsigned id; } TmrCtx;
static Uint32 tmr_cb(Uint32 interval, void *p) {
  TmrCtx *c = (TmrCtx *)p;
  c->cb((unsigned)c->id);
  return c->flags & 1 ? interval : 0;
}
static TmrCtx g_tc[64]; static int g_tcn;
/* v2.08: RE_FIXED_DT — таймеры по виртуальным часам plat_time_ms, вызов в основном потоке (id = 0x10000 + слот) */
int plat_fixed_dt(void); uint32_t plat_time_ms(void);
typedef struct { void (*cb)(unsigned); unsigned flags, delay, on; uint32_t due; } VtTmr;
static VtTmr g_vtt[64]; static int g_vt_in;
void plat_vt_timers(uint32_t now) {
  if (g_vt_in) return;
  g_vt_in = 1;
  for (int i = 0; i < 64; i++) {
    VtTmr *t = &g_vtt[i]; int guard = 0;
    while (t->on && (int32_t)(now - t->due) >= 0 && guard++ < 100) {
      if (t->flags & 1) t->due += t->delay ? t->delay : 1; else t->on = 0;
      t->cb(0x10000u + (unsigned)i);
    }
  }
  g_vt_in = 0;
}
unsigned plat_timer_start(unsigned delay, unsigned flags, void (*cb)(unsigned)) {
  if (plat_fixed_dt()) {
    for (int i = 0; i < 64; i++) if (!g_vtt[i].on) {
      uint32_t now = plat_time_ms();
      g_vtt[i].cb = cb; g_vtt[i].flags = flags; g_vtt[i].delay = delay; g_vtt[i].due = now + delay; g_vtt[i].on = 1;
      return 0x10000u + (unsigned)i;
    }
    return 0;
  }
  TmrCtx *c = &g_tc[g_tcn++ & 63];
  c->cb = cb; c->flags = flags; c->id = 0;
  SDL_TimerID id = SDL_AddTimer(delay, tmr_cb, c);
  c->id = (unsigned)id;
  return (unsigned)id;
}
void plat_timer_kill(unsigned id) {
  if (id >= 0x10000u && id < 0x10040u) { g_vtt[id - 0x10000u].on = 0; return; }
  SDL_RemoveTimer((SDL_TimerID)id);
}
