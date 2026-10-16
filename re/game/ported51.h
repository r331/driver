#pragma once
#include "gvar.h"
#include "nodetab.h"
#include "unported.h"
#include "ported19.h"
#include "ported44.h"
#include <stdint.h>
/* Мелкие листовые функции (шаг D): звук с дрожанием высоты, масштаб пары координат, разбор текстовых строк,
   размер файла, инициализация слота, поиск по таблицам. Все cdecl. Указатели-аргументы — на структуры игры
   (обращение по смещениям: на arm64 указатели в структурах 8 байт, поэтому через rd/wr по смещению). */
#define P51_PitchCount GAME_VAR(int32_t, P51_PitchCount, 0x00560388)  /* -1 — выкл, 0 — играть, иначе обратный отсчёт */
#define P51_Half       GAME_VAR(float, P51_Half, 0x00546068)          /* 0.5 */
#define P51_TrafficN   GAME_VAR(int32_t, P51_TrafficN, 0x00575ee4)
typedef uint8_t p51_tab_1ed80_t[0x2c * 64];
#define P51_Tab1ED80   SLOTTAB_VAR(p51_tab_1ed80_t, P51_Tab1ED80, 0x00c1ed80) /* записи по 0x2c байт; байт +3 — флаг блокировки */
#ifndef RE_HOOK_BUILD
#pragma push_macro("P51_PitchCount") /*gvi*/
#undef P51_PitchCount /*gvi*/
#pragma push_macro("P51_TrafficN") /*gvi*/
#undef P51_TrafficN /*gvi*/
extern int32_t P51_PitchCount, P51_TrafficN;
#pragma pop_macro("P51_TrafficN") /*gvi*/
#pragma pop_macro("P51_PitchCount") /*gvi*/
#pragma push_macro("P51_Half") /*gvi*/
#undef P51_Half /*gvi*/
extern float P51_Half;
#pragma pop_macro("P51_Half") /*gvi*/
#endif
void    P51_PitchJitterSfx(void);                        /* 004d69ed: звук 0x16 с разбросом высоты ±0x1000 по таймеру */
void    P51_ScalePair(float *x, float *y);               /* 004d8487: (v/640|480 − 0.5)·масштаб + 0.5, умножить на размер экрана */
int32_t P51_PrefixMatch(const char *line, const char *word); /* 004a59f2: после пробелов строка начинается со слова — 1 */
char   *P51_SkipToLine(char *p, const char *word);       /* 004a5a83: пропускать строки, пока не встретится строка со словом */
int32_t P51_FileSize(void *file);                        /* 004d3000: fseek END, ftell, fseek 0 */
uint8_t P51_DirFromHeading(const uint8_t *obj);          /* 004a63c6: Round1024(+0x100)&0xff, при +0x10c<0 — на полоборота (+2 &3) */
void    P51_InitCarSlot(uint32_t owner, uint8_t *slot, uint32_t id); /* 00491928: обнулить 0xcd8 байт, задать поля */
int32_t P51_TrafficConflict(uint32_t self, int32_t a, uint32_t b, int32_t c); /* 0048eb25: есть ли в таблице трафика конфликтная запись */
int32_t P51_NodeKind(const uint8_t *node);               /* 0048f7fe: 0..3 по флагам узла и таблице c1ed80 */
void    P51_SteerHeading(uint8_t *obj, const int32_t *vec); /* 004d0071: довернуть курс (+0x12, int16) к углу вектора не быстрее 0x20 за вызов */
int32_t P51_SkipNumber(char **pp);                       /* 004a50f7: пропустить [-]цифры[.цифры]; 1 — число закончилось, 0 — вторая точка */
/* gvar-img v2.03 begin (tools/gen_gvar_img.py) */
#if !defined(RE_HOOK_BUILD) && !defined(RE_GVAR_PLAIN)
#undef P51_PitchCount
#define P51_PitchCount (*(int32_t *)re_gvar(0x00560388u, sizeof(int32_t), (void *)&P51_PitchCount))
#undef P51_Half
#define P51_Half (*(float *)re_gvar(0x00546068u, sizeof(float), (void *)&P51_Half))
#undef P51_TrafficN
#define P51_TrafficN (*(int32_t *)re_gvar(0x00575ee4u, sizeof(int32_t), (void *)&P51_TrafficN))
#endif
/* gvar-img v2.03 end */
