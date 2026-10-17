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
void dsm_mix(int16_t *out, int frames); int dsm_active(void);
void plat_snd_lockdev(int on){ if(on) LOCK(); else UNLOCK(); }
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
      if(s->pos>=(double)total){ if(s->loop) s->pos-=(double)total; else { s->playing=0; break; } } } }
  dsm_mix(out,frames); }
static void SDLCALL audio_cb(void*u,Uint8*st,int len){ (void)u; plat_snd_mix((int16_t*)st,len/4); }
int plat_snd_open(void){
  if(g_dev) return 1;
  if(SDL_InitSubSystem(SDL_INIT_AUDIO)<0) return 0;
  SDL_AudioSpec want; SDL_zero(want); want.freq=SND_OUT_RATE; want.format=AUDIO_S16SYS; want.channels=2; want.samples=1024; want.callback=audio_cb;
  g_dev=SDL_OpenAudioDevice(NULL,0,&want,NULL,0); if(!g_dev) return 0;
  SDL_PauseAudioDevice(g_dev,0); return 1; }
/* v2.09: игра — RE_WAV_OUT=файл.wav: микс пишется в WAV по виртуальным/реальным часам plat_time_ms (на каждом plat_flip),
   устройство SDL_audio не открывается; иначе — SDL_audio (если устройства нет — звук молча выключен). */
#include <stdio.h>
uint32_t plat_time_ms(void);
static FILE *g_wav; static uint64_t g_wav_frames, g_wav_ms0; static int g_wav_on, g_snd_game, g_pump_n;
static void wav_hdr(void){ if(!g_wav) return; uint32_t data=(uint32_t)(g_wav_frames*4); uint8_t h[44]; memcpy(h,"RIFF",4);
  uint32_t v=36+data; memcpy(h+4,&v,4); memcpy(h+8,"WAVEfmt ",8); v=16; memcpy(h+16,&v,4); uint16_t t=1; memcpy(h+20,&t,2); t=2; memcpy(h+22,&t,2);
  v=SND_OUT_RATE; memcpy(h+24,&v,4); v=SND_OUT_RATE*4; memcpy(h+28,&v,4); t=4; memcpy(h+32,&t,2); t=16; memcpy(h+34,&t,2); memcpy(h+36,"data",4); memcpy(h+40,&data,4);
  long cur=ftell(g_wav); fseek(g_wav,0,SEEK_SET); fwrite(h,1,44,g_wav); fseek(g_wav,cur,SEEK_SET); fflush(g_wav); }
static void wav_close(void){ if(g_wav){ wav_hdr(); fclose(g_wav); g_wav=NULL; } }
void plat_snd_open_game(void){
  if(g_snd_game) return; g_snd_game=1;
  const char *w=getenv("RE_WAV_OUT");
  if(w&&*w){ g_wav=fopen(w,"wb"); if(g_wav){ uint8_t z[44]={0}; fwrite(z,1,44,g_wav); g_wav_on=1; g_wav_ms0=plat_time_ms(); atexit(wav_close);
      fprintf(stderr,"[snd] RE_WAV_OUT %s\n",w); } return; }
  if(!plat_snd_open()) fprintf(stderr,"[snd] SDL_audio: нет устройства (%s) — без звука\n",SDL_GetError());
}
/* на каждом показанном кадре: дописать в WAV столько кадров, сколько прошло по plat_time_ms */
void plat_snd_pump(void){
  if(!g_wav_on||!g_wav) return;
  uint64_t ms=(uint64_t)plat_time_ms()-g_wav_ms0, want=ms*SND_OUT_RATE/1000;
  static int16_t buf[4096*2];
  while(g_wav_frames<want){ int n=(int)(want-g_wav_frames); if(n>4096) n=4096; plat_snd_mix(buf,n); fwrite(buf,4,(size_t)n,g_wav); g_wav_frames+=(uint64_t)n; }
  if(getenv("RE_SND_LOG")&&(++g_pump_n%50)==0) fprintf(stderr,"[snd] flip %d ms %llu frames %llu active %d\n",g_pump_n,(unsigned long long)ms,(unsigned long long)g_wav_frames,dsm_active());
  if((g_pump_n%200)==0) wav_hdr();
}
void plat_snd_close(void){ if(g_dev){ SDL_CloseAudioDevice(g_dev); g_dev=0; } }
static int g_cd_track=0;
int plat_cd_play(int t){ if(t<1||t>99) return 0; g_cd_track=t; return 1;}
void plat_cd_stop(void){ g_cd_track=0; }
int plat_cd_current(void){ return g_cd_track; }

/* --- CD-аудио: v2.22 — эмуляция в plat_cdaudio.c; таймеры на SDL_AddTimer --- */
#include <stdlib.h>
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
