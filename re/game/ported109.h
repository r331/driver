/* v1.54 — восстановлено из Game.exe. Все функции cdecl (ret без операнда проверен по Game.exe; метка __fastcall у 004219e8 ложная —
   ecx передаётся в 00421a80, которая его не читает).
   0052498e — сэмпл на голос, 004d7f91 / 004d81da — прямоугольник с цветами вершин (004d81da — через P51_ScalePair),
   0040dce0 — плитка текстуры, 0040b6fd — значок (Glide или спрайт в буфер), 00522a50 — модели капель, 004219e8 — эмулируемые текстуры
   всех слотов, 00421719 / 00421861 — загрузка 8/16-битной эмулируемой текстуры слота, 00502cee — маркеры целей скрипта,
   00504866 — стрелки радара, 005191c5 — такт ввода/записи, 00505b54 — машины трафика на радаре. */
#pragma once
#include <stdint.h>
#include "gvar.h"

#define P109_C8089C GAME_VAR(int32_t, P109_C8089C, 0x00c8089c)   /* показывать трафик на радаре */
#define P109_C54B00 GAME_VAR(int32_t, P109_C54B00, 0x00c54b00)   /* режим 3: игрок читает запись */
#define P109_C81268 GAME_VAR(int32_t, P109_C81268, 0x00c81268)   /* аргумент 00518953 */
#ifndef RE_HOOK_BUILD
#pragma push_macro("P109_C8089C") /*gvi*/
#undef P109_C8089C /*gvi*/
#pragma push_macro("P109_C54B00") /*gvi*/
#undef P109_C54B00 /*gvi*/
#pragma push_macro("P109_C81268") /*gvi*/
#undef P109_C81268 /*gvi*/
extern int32_t P109_C8089C, P109_C54B00, P109_C81268;
#pragma pop_macro("P109_C81268") /*gvi*/
#pragma pop_macro("P109_C54B00") /*gvi*/
#pragma pop_macro("P109_C8089C") /*gvi*/
#endif

void    P109_SndPlay(int32_t voice, int32_t sample, float a, float b, float c);          /* 0052498e */
void    P109_GradRect(float x, float y, float w, float h, int32_t c0, int32_t c1, int32_t c2, int32_t c3, int32_t c4, int32_t c5,
                      int32_t c6, int32_t c7, int32_t c8, int32_t c9, int32_t c10, int32_t c11); /* 004d7f91 */
void    P109_GradRectS(float x, float y, float w, float h, uint32_t cA, uint32_t cD, uint32_t cB, uint32_t cC); /* 004d81da */
void    P109_TileDraw(int32_t x, int32_t y, int32_t w, int32_t h, int32_t idx, void *color);    /* 0040dce0 */
void    P109_IconDraw(float x, float y, float sx, float sy, float u, float v, float tw, float th, int32_t page, const uint8_t *rgb); /* 0040b6fd */
void    P109_DropsDraw(int32_t mode);                                                     /* 00522a50 */
int32_t P109_EmulInit(void);                                                              /* 004219e8 */
int32_t P109_SlotUpload8(const uint8_t *src, int32_t slot);                               /* 00421719 */
int32_t P109_SlotUpload16(const uint16_t *src, int32_t slot);                             /* 00421861 */
void    P109_ScriptMarkers(void);                                                         /* 00502cee */
void    P109_RadarArrows(void);                                                           /* 00504866 */
void    P109_InputTick(void);                                                             /* 005191c5 */
void    P109_RadarTraffic(void);                                                          /* 00505b54 */
/* gvar-img v2.03 begin (tools/gen_gvar_img.py) */
#if !defined(RE_HOOK_BUILD) && !defined(RE_GVAR_PLAIN)
#undef P109_C8089C
#define P109_C8089C (*(int32_t *)re_gvar(0x00c8089cu, sizeof(int32_t), (void *)&P109_C8089C))
#undef P109_C54B00
#define P109_C54B00 (*(int32_t *)re_gvar(0x00c54b00u, sizeof(int32_t), (void *)&P109_C54B00))
#undef P109_C81268
#define P109_C81268 (*(int32_t *)re_gvar(0x00c81268u, sizeof(int32_t), (void *)&P109_C81268))
#endif
/* gvar-img v2.03 end */
