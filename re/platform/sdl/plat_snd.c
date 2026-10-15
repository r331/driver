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
