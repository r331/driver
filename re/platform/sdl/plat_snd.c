#include "../plat.h"
#include <stdlib.h>
#include <string.h>
/* Таблица звуковых буферов (хранит PCM и параметры); вывод через SDL_audio — следующий шаг. */
#define SND_MAX 256
typedef struct { void *pcm; int bytes, rate, ch, bits, playing, loop, vol, pitch, pan; float x, y, z; } snd_t;
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
void plat_snd_destroy(int h){snd_t*s=S(h); if(s){free(s->pcm); memset(s,0,sizeof *s);}}
void plat_snd_play(int h,int l){snd_t*s=S(h); if(s){s->playing=1;s->loop=l;}}
void plat_snd_stop(int h){snd_t*s=S(h); if(s) s->playing=0;}
void plat_snd_set(int h,int v,int p,int n){snd_t*s=S(h); if(s){s->vol=v;s->pitch=p;s->pan=n;}}
void plat_snd_pos3d(int h,float x,float y,float z){snd_t*s=S(h); if(s){s->x=x;s->y=y;s->z=z;}}
int plat_cd_play(int t){(void)t;return 0;}
void plat_cd_stop(void){}
