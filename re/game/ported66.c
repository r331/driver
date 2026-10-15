#include "ported66.h"
#include "ported89.h"
#include <string.h>

#ifndef RE_HOOK_BUILD
int32_t P66_Nest = 0, P66_LoadFlag = 0;
uint32_t P66_Scene = 0;
float P66_C255 = 0, P66_C128 = 0, P66_C2 = 0;
#endif

void P66_InitConsts(void) {
#ifndef RE_HOOK_BUILD
  P66_C255 = 255.0f; P66_C128 = 128.0f; P66_C2 = 2.0f;
#endif
}

/* 004188b0 */
void P66_FrameBegin(void) {
  P66_Scene = 0x00cb8f20u;
  G6_00D0DDC0 = 0;
  if (Q00B87E90 != 0 && P25_CdPlaying == 0) {
    P25_InitCDAudio();
    P25_PlayCDTrack(3);
  }
  P66_Fn523829();
  InitSoundVolumes_00523C56();
  Ui004268E0();
  P66_Fn427EEA();
  if (P66_LoadFlag == 0) {
    int32_t s = P15_State;
    P12_Fn00426580(s == 1 ? 4 : s == 2 ? 6 : s == 3 ? 5 : 7);
  } else {
    P12_Fn00426580(1);
  }
  P89_DrawMap(0);
  P89_DrawMap(1);
  P12_Fn00426580(0x18);
}

static int16_t rd16(const uint8_t *p) { int16_t v; memcpy(&v, p, 2); return v; }
static uint32_t rd32(const uint8_t *p) { uint32_t v; memcpy(&v, p, 4); return v; }
/* __ftol оригинала — усечение; произведение двух float точно помещается в double (как в x87) */
static int32_t Scale(double a, float cur) { return (int32_t)(a * (double)cur); }

/* 0041897c */
void P66_DrawTable(const void *tbl) {
  const uint8_t *t = (const uint8_t *)tbl;
  for (int32_t i = 0; rd32(t + i * 16 + 8) != 0; i++) {
    const uint8_t *e = t + i * 16;
    int32_t x = rd16(e), y = rd16(e + 2);
    uint32_t txt = rd32(e + 8);
    uint8_t b5 = e[5];
    if (P59_NoKeyFlag == 0 && P59_MenuLock == 0) {
      uint8_t r, g, b;
      if (i == 0) {
        r = (uint8_t)Scale(P66_C255, P19_Cur);
        g = (uint8_t)Scale(P66_C255, P19_Cur);
        b = (uint8_t)Scale(P66_C128, P19_Cur);
      } else {
        r = (uint8_t)Scale((float)e[0xc], P19_Cur);
        g = (uint8_t)Scale((float)e[0xd], P19_Cur);
        b = (uint8_t)Scale((float)e[0xe], P19_Cur);
      }
      P66_DrawText(x, y, txt, 0, b5, r, g, b);
    } else {
      P66_Draw5173D7((float)x, (float)y, txt, 0, b5 | 0x10);
      P66_Draw5173D7((float)x + P66_C2, (float)y + P66_C2, txt, 0, b5 | 0x10);
      P66_Draw5173D7((float)x, (float)y, txt, 0, b5 | 4);
    }
  }
}

/* таблицы пунктов лежат в .data Game.exe: в native их образа нет — такой адрес не разыменовываем */
static const void *Resolve(uint32_t a) {
#ifdef RE_HOOK_BUILD
  return (const void *)(uintptr_t)a;
#else
  return (a >= 0x00400000u && a < 0x01400000u) ? NULL : (const void *)(uintptr_t)a;
#endif
}

static void CallCb(uint32_t cb) {
#ifdef RE_HOOK_BUILD
  ((void (*)(void))(uintptr_t)cb)();
#else
  if (cb == 0x004169afu) P66_Fn4169AF();
#endif
}

/* указатели 01270e80/01270de4 (звук меню) в native пусты, пока нет звукового драйвера — тогда эти вызовы пропускаются */
static int SndFnsReady(void) {
#ifdef RE_HOOK_BUILD
  return 1;
#else
  return FnPtr01270E80 != NULL && G6_01270DE4 != NULL;
#endif
}

/* 0041846c */
void P66_ScreenFrame(uint32_t tbl, uint32_t cb) {
  Ui0041889C();
  if (P31_Active == 0) return;
  int32_t n = P66_Nest;
  P66_Nest = n - 1;
  if (n != 0) return;
  P52_GlideFogMode();
  P66_FrameBegin();
  int snd = SndFnsReady();
  if (snd) Ui004197F8();
  if (tbl != 0) {
    const void *t = Resolve(tbl);
    if (t != NULL) P66_DrawTable(t);
  }
  if (cb != 0) CallCb(cb);
  if (snd) SoundMenuIn00419814();
  P47_GlideSwap();
  P66_Nest = (int32_t)P21_FrameTicks();
}

/* 004c862f */
void P66_DirSwitch(void) {
  if (P29_Flag48 != 0) return;
  int32_t n = P29_Mode - 1;
  switch (n) {
  case 0: case 0xb: case 7: case 8: case 9: case 3: case 5:
    P66_Fn4C3BC7(); P66_Fn4C68A7(DirectorUnk6C);
    break;
  case 2:
    if (DirectorBuffer == NULL) SetDirectorMode(1, 2, 0);
    else { P66_Fn4C3BC7(); P66_Fn4C68A7(DirectorUnk6C); }
    break;
  case 4:
    P66_Fn4C68A7(DirectorUnk6C);
    SetRGB00516EB4(0xff, 0xff, 0xff);
    P66_Fn4C3BC7();
    break;
  default:
    break;
  }
  DrawCornerIndicator();
}
