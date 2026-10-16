/* v1.50 — восстановлено из Game.exe. Все функции cdecl (ret без операнда проверен по Game.exe).
   00407c4c — копия LFB в буфер меню (функция пикселя 0057b73c → P101_Pal16/P101_Pal32), 00422736 — эмулируемая
   поверхность 256×256 для текстуры, 004ca802 — модель объекта с вращением (P79_ModelTab), 004d26ea — такт музыки
   погони (смена темы по направлению игрока), 0040d81b — масштабный блит 640×480 RGBA → LFB и grBufferSwap(0),
   004e53b5 — счётчики «трюков»/подсказок игрока в режиме 4 (P59_PickUp). */
#pragma once
#include "gvar.h"
#include "reptr.h"
#include "cartab.h"
#include <stdint.h>

#define P105_PixDst  GAME_VAR(uint32_t, P105_PixDst, 0x005c6740)   /* адрес LFB последней копии 00407c4c */
#define P105_SpinAng GAME_VAR(int32_t, P105_SpinAng, 0x00b202e8)   /* угол вращения модели 004ca802 (+0x1e & 0xfff) */
#define P105_MusLimit GAME_VAR(int32_t, P105_MusLimit, 0x0112b234) /* порог 00d11a5c для поворота трафика */
#ifndef RE_HOOK_BUILD
extern uint32_t P105_PixDst; extern int32_t P105_SpinAng, P105_MusLimit;
#endif

int32_t  P105_LfbToMenu(void);                      /* 00407c4c */
int32_t  P105_EmulSurface(uint8_t *o);              /* 00422736 */
void     P105_SpinModel(void *o);                   /* 004ca802 */
void     P105_ChaseMusic(int32_t *timers);          /* 004d26ea */
void     P105_BlitScaled(const uint8_t *src);       /* 0040d81b */
void     P105_StuntHints(int32_t keys, void *car);  /* 004e53b5 */
