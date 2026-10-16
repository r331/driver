#pragma once
#include <stdint.h>
#include "gvar.h"
/* v1.69: ported124 — мотель (меню ответов/машин/шуток), показ BMP 640×480, выбор машины, debug.log, наблюдение переменных,
   меню повтора и такт режиссёра. Все функции cdecl. */
#define P124_ReplayPrev GAME_VAR(int32_t, P124_ReplayPrev, 0x00d17c60)  /* прежний узел меню повтора (до 004c38e2) */
#define P124_DirBlink   GAME_VAR(int32_t, P124_DirBlink,   0x00d17b78)  /* такт мигания выбранного узла 0..31 */
#define P124_LogOn      GAME_VAR(int32_t, P124_LogOn,      0x00553bbc)  /* .data, начальное 1: писать debug.log */
#define P124_LogSize    GAME_VAR(int32_t, P124_LogSize,    0x00b20254)  /* ftell после последней записи debug.log */
#ifndef RE_HOOK_BUILD
extern int32_t P124_ReplayPrev, P124_DirBlink, P124_LogOn, P124_LogSize;
#endif
int32_t P124_MotelKeys(int32_t junk);                      /* 00416794: в оригинале __fastcall-мусор в ECX (не используется) — передавать 0 */
void    P124_MotelSample(void);                            /* 00416d6d: ANS/CAR/JOKE%03d.WAV выбранного пункта в сэмпл 7 */
void    P124_ShowBmp(const char *name, int32_t wait);      /* 0040c610: BMP 640×480×24 на экран (4× блит), ожидание клавиши */
int32_t P124_ReadBmp(const char *name, uint8_t *dst);      /* 0040d6e8: чтение BMP 640×480×24 в RGBA-буфер (снизу вверх), 1/0 */
void    P124_MotelInit(void);                              /* 004182b0: вход в мотель (флайбай, звук MOTEL.DSS, CD-дорожка 3) */
int32_t P124_CarSelect(int32_t row);                       /* 004171f0: экран выбора машины (CARSEL%d.FBD), результат 00417386 */
void    P124_DebugLog(const char *msg);                    /* 004bf2a0: строка в debug.log (первая запись — с усечением) */
void    P124_WatchShow(void);                              /* 004bf4a1: 32 наблюдаемые переменные (010ea620, шаг 0xc) в журнал экрана */
void    P124_ReplayMenu(int32_t dir);                      /* 004c38e2: ReplayMenuHandler — перемещение по узлам меню повтора */
void    P124_HandleDirector(void);                         /* 004c813d: HandleDirector — такт режиссёра повтора */
