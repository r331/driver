#pragma once
#include "gvar.h"
#include <stdint.h>
/* Шаг D, ported96 (v1.41): пачка простых/листовых функций — журнал строк отладки (00d0fe40 + очередь 00d10e80), снятие
   кресел вне соседних клеток, случайное кресло клетки, разбор слова/строки в кавычках скрипта, таблицы сферы и поворотов
   из таблицы синусов, строка «Гц/FPS», полоса загрузки, значок по экранным/виртуальным координатам, искры/пыль/запись
   объекта B, часы заезда, метка повтора «R», три вывода текста от центра экрана, сброс режиссёра, ограничение настроек
   дальности/кадров, шаг сценария повтора, два диспетчера частиц по таблице 005759c4, значок тени машины CARSHAD. Все cdecl.

   Текст в 00d0fe40: очередь P55_PopTab хранит в поле id адрес Game.exe (0x00d0fe40 + смещение) — в native так же,
   P96_LogText переводит его в указатель на родной буфер.
   Указатель записи объекта B (01105d60, G01105D60): адрес Game.exe, переводится P95_ObjPtr (как ссылки v1.40). */

#define P96_LogBuf     GAME_VAR(p96_logbuf_t, P96_LogBuf, 0x00d0fe40)    /* 0x1040 байт строк журнала */
#define P96_FpsShown   GAME_VAR(int32_t, P96_FpsShown, 0x00d0fe14)
#define P96_FpsFrames  GAME_VAR(int32_t, P96_FpsFrames, 0x00d11684)
#define P96_FpsTicks   GAME_VAR(int32_t, P96_FpsTicks, 0x00d11688)
#define P96_FpsTick0   GAME_VAR(int32_t, P96_FpsTick0, 0x00d11810)
#define P96_FpsFrame0  GAME_VAR(int32_t, P96_FpsFrame0, 0x00d11814)
#define P96_RefreshHz  GAME_VAR(int32_t, P96_RefreshHz, 0x00575f0c)      /* .data, начальное 50 */
#define P96_Sphere     GAME_VAR(p96_sphere_t, P96_Sphere, 0x00d02780)    /* 7×32 точки {x, y, z, —} */
#define P96_RotTab     GAME_VAR(p96_rottab_t, P96_RotTab, 0x0113a6e0)    /* 1024 × 8 int */
#define P96_SparkOn    GAME_VAR(int32_t, P96_SparkOn, 0x010faf24)
#define P96_DustOn     GAME_VAR(int32_t, P96_DustOn, 0x0111d408)
#define P96_Dust       GAME_VAR(p96_dust_t, P96_Dust, 0x0110e160)        /* записи 0x24: xyz, —, скорость xyz, —, жизнь 16, 16 */
#define P96_DustN      GAME_VAR(int32_t, P96_DustN, 0x011171a0)
#define P96_ObjBOn     GAME_VAR(int32_t, P96_ObjBOn, 0x010fb204)
#define P96_ReplayB    GAME_VAR(uint8_t, P96_ReplayB, 0x00b5a850)
#define P96_RTag       GAME_VAR(p96_tag_t, P96_RTag, 0x00575d84)          /* .data "R\0\0" */
#define P96_ShadIcon   GAME_VAR(uint8_t *, P96_ShadIcon, 0x00b5c8d8)     /* значок CARSHAD (16 байт, P93_FindIcon) */
#define P96_ShadPage   GAME_VAR(uint8_t, P96_ShadPage, 0x00b5c7e2)
#define P96_ShadIdx    GAME_VAR(p96_i4_t, P96_ShadIdx, 0x00b5c7e8)
#define P96_ShadRGB    GAME_VAR(p96_f3_t, P96_ShadRGB, 0x00b5c818)
#define P96_ShadUV     GAME_VAR(p96_f12_t, P96_ShadUV, 0x00b5c8dc)       /* b5c8dc..b5c908: 12 float (u,v ×4 + ...) */
#define P96_ShadH      GAME_VAR(float, P96_ShadH, 0x00b80950)
#define P96_ShadW      GAME_VAR(float, P96_ShadW, 0x00b80954)
#define P96_PartTab    GAME_VAR(p96_parttab_t, P96_PartTab, 0x005759c4)  /* .data: 5 обработчиков частиц по типу (+0x1c) */

typedef char p96_logbuf_t[0x1040];
typedef float p96_sphere_t[7 * 32][4];
typedef int32_t p96_rottab_t[1024][8];
typedef uint8_t p96_dust_t[1024 * 0x24];
typedef char p96_tag_t[4];
typedef int32_t p96_i4_t[4];
typedef float p96_f3_t[3];
typedef float p96_f12_t[12];
typedef uint32_t p96_parttab_t[5];

#ifndef RE_HOOK_BUILD
#pragma push_macro("P96_LogBuf") /*gvi*/
#undef P96_LogBuf /*gvi*/
#pragma push_macro("P96_Sphere") /*gvi*/
#undef P96_Sphere /*gvi*/
#pragma push_macro("P96_RotTab") /*gvi*/
#undef P96_RotTab /*gvi*/
#pragma push_macro("P96_Dust") /*gvi*/
#undef P96_Dust /*gvi*/
extern p96_logbuf_t P96_LogBuf; extern p96_sphere_t P96_Sphere; extern p96_rottab_t P96_RotTab; extern p96_dust_t P96_Dust;
#pragma pop_macro("P96_Dust") /*gvi*/
#pragma pop_macro("P96_RotTab") /*gvi*/
#pragma pop_macro("P96_Sphere") /*gvi*/
#pragma pop_macro("P96_LogBuf") /*gvi*/
#pragma push_macro("P96_RTag") /*gvi*/
#undef P96_RTag /*gvi*/
#pragma push_macro("P96_ShadIdx") /*gvi*/
#undef P96_ShadIdx /*gvi*/
#pragma push_macro("P96_ShadRGB") /*gvi*/
#undef P96_ShadRGB /*gvi*/
#pragma push_macro("P96_ShadUV") /*gvi*/
#undef P96_ShadUV /*gvi*/
extern p96_tag_t P96_RTag; extern p96_i4_t P96_ShadIdx; extern p96_f3_t P96_ShadRGB; extern p96_f12_t P96_ShadUV;
#pragma pop_macro("P96_ShadUV") /*gvi*/
#pragma pop_macro("P96_ShadRGB") /*gvi*/
#pragma pop_macro("P96_ShadIdx") /*gvi*/
#pragma pop_macro("P96_RTag") /*gvi*/
#pragma push_macro("P96_PartTab") /*gvi*/
#undef P96_PartTab /*gvi*/
#pragma push_macro("P96_ReplayB") /*gvi*/
#undef P96_ReplayB /*gvi*/
#pragma push_macro("P96_ShadPage") /*gvi*/
#undef P96_ShadPage /*gvi*/
extern p96_parttab_t P96_PartTab; extern uint8_t *P96_ShadIcon; extern uint8_t P96_ReplayB, P96_ShadPage;
#pragma pop_macro("P96_ShadPage") /*gvi*/
#pragma pop_macro("P96_ReplayB") /*gvi*/
#pragma pop_macro("P96_PartTab") /*gvi*/
#pragma push_macro("P96_FpsShown") /*gvi*/
#undef P96_FpsShown /*gvi*/
#pragma push_macro("P96_FpsFrames") /*gvi*/
#undef P96_FpsFrames /*gvi*/
#pragma push_macro("P96_FpsTicks") /*gvi*/
#undef P96_FpsTicks /*gvi*/
#pragma push_macro("P96_FpsTick0") /*gvi*/
#undef P96_FpsTick0 /*gvi*/
#pragma push_macro("P96_FpsFrame0") /*gvi*/
#undef P96_FpsFrame0 /*gvi*/
#pragma push_macro("P96_RefreshHz") /*gvi*/
#undef P96_RefreshHz /*gvi*/
#pragma push_macro("P96_SparkOn") /*gvi*/
#undef P96_SparkOn /*gvi*/
#pragma push_macro("P96_DustOn") /*gvi*/
#undef P96_DustOn /*gvi*/
extern int32_t P96_FpsShown, P96_FpsFrames, P96_FpsTicks, P96_FpsTick0, P96_FpsFrame0, P96_RefreshHz, P96_SparkOn, P96_DustOn,
#pragma pop_macro("P96_DustOn") /*gvi*/
#pragma pop_macro("P96_SparkOn") /*gvi*/
#pragma pop_macro("P96_RefreshHz") /*gvi*/
#pragma pop_macro("P96_FpsFrame0") /*gvi*/
#pragma pop_macro("P96_FpsTick0") /*gvi*/
#pragma pop_macro("P96_FpsTicks") /*gvi*/
#pragma pop_macro("P96_FpsFrames") /*gvi*/
#pragma pop_macro("P96_FpsShown") /*gvi*/
               P96_DustN, P96_ObjBOn;
#pragma push_macro("P96_ShadH") /*gvi*/
#undef P96_ShadH /*gvi*/
#pragma push_macro("P96_ShadW") /*gvi*/
#undef P96_ShadW /*gvi*/
extern float P96_ShadH, P96_ShadW;
#pragma pop_macro("P96_ShadW") /*gvi*/
#pragma pop_macro("P96_ShadH") /*gvi*/
#endif

void     P96_InitConsts(void);                    /* native: начальные значения .data (575f0c, 575d84) */
const char *P96_LogText(uint32_t id);             /* поле id очереди журнала → строка */
void     P96_LogLine(const char *s);              /* 004d90f4: строка в журнал (до 128), позиция x/y по ширине экрана/8 */
void     P96_DropFarChairs(void);                 /* 004a2c98: снять сидящих пешеходов вне 4 соседних клеток */
uint8_t *P96_PickChair(int32_t cell);             /* 004a32e9: случайное кресло клетки (NULL, если занято/нет) */
int32_t  P96_ParseWord(char *line, char *out);    /* 004f652e: слово до ',' или пробела; 0 / 0xc */
int32_t  P96_ParseQuoted(char *line, char *out);  /* 004f6612: строка в кавычках; 0 / 0xc */
void     P96_InitSphere(void);                    /* 004e8440 */
void     P96_InitRotTab(void);                    /* 0048db8e */
void     P96_FpsText(void);                       /* 004d7a21 */
void     P96_LoadBar(void);                       /* 004d9663 */
void     P96_IconAt(float x, float y, const uint8_t *icon, uint8_t r, uint8_t g, uint8_t b);              /* 004e71dc */
void     P96_IconRect(float x, float y, float w, float h, const uint8_t *icon, uint32_t rgb);              /* 004e72f8 */
void     P96_SpawnSpark(const float *pos, int32_t a, int32_t b, int16_t c);                                      /* 004b9464 */
void     P96_SpawnDust(const float *pos, int32_t n);                                                             /* 004b04c0 */
void     P96_AddObjB(const float *pos, const int32_t *uv, int16_t a, int16_t b, uint32_t flags, int32_t mark,
                     int32_t c, int32_t d);                                                                 /* 004ad5d2 */
void     P96_ClockText(const uint8_t *t);         /* 004fba23: t+0xc сотые, +0x10 секунды, +0x14 минуты */
void     P96_ReplayTag(void);                     /* 005199bc */
void     P96_TextCenter(float x, float y, float sx, float sy, uint32_t txt);                               /* 00516ed3 */
void     P96_TextAt(float x, float y, uint32_t txt, uint8_t a, int32_t align);                             /* 0051718a */
void     P96_TextMid(float y, uint32_t txt, uint8_t a, int32_t align);                                     /* 005172bb */
void     P96_ResetDirector(void);                 /* 005222cf */
void     P96_ClampOptions(void);                  /* 0050fab0 */
void     P96_ReplayScript(void);                  /* 0050e9ab */
void     P96_PartRunA(uint8_t *p);                /* 00513cc7 */
void     P96_PartRunB(uint8_t *p);                /* 00513ce0 */
void     P96_ShadowInit(void);                    /* 0052008e */
/* gvar-img v2.03 begin (tools/gen_gvar_img.py) */
#if !defined(RE_HOOK_BUILD) && !defined(RE_GVAR_PLAIN)
#undef P96_LogBuf
#define P96_LogBuf (*(p96_logbuf_t *)re_gvar(0x00d0fe40u, sizeof(p96_logbuf_t), (void *)&P96_LogBuf))
#undef P96_FpsShown
#define P96_FpsShown (*(int32_t *)re_gvar(0x00d0fe14u, sizeof(int32_t), (void *)&P96_FpsShown))
#undef P96_FpsFrames
#define P96_FpsFrames (*(int32_t *)re_gvar(0x00d11684u, sizeof(int32_t), (void *)&P96_FpsFrames))
#undef P96_FpsTicks
#define P96_FpsTicks (*(int32_t *)re_gvar(0x00d11688u, sizeof(int32_t), (void *)&P96_FpsTicks))
#undef P96_FpsTick0
#define P96_FpsTick0 (*(int32_t *)re_gvar(0x00d11810u, sizeof(int32_t), (void *)&P96_FpsTick0))
#undef P96_FpsFrame0
#define P96_FpsFrame0 (*(int32_t *)re_gvar(0x00d11814u, sizeof(int32_t), (void *)&P96_FpsFrame0))
#undef P96_RefreshHz
#define P96_RefreshHz (*(int32_t *)re_gvar(0x00575f0cu, sizeof(int32_t), (void *)&P96_RefreshHz))
#undef P96_Sphere
#define P96_Sphere (*(p96_sphere_t *)re_gvar(0x00d02780u, sizeof(p96_sphere_t), (void *)&P96_Sphere))
#undef P96_RotTab
#define P96_RotTab (*(p96_rottab_t *)re_gvar(0x0113a6e0u, sizeof(p96_rottab_t), (void *)&P96_RotTab))
#undef P96_SparkOn
#define P96_SparkOn (*(int32_t *)re_gvar(0x010faf24u, sizeof(int32_t), (void *)&P96_SparkOn))
#undef P96_DustOn
#define P96_DustOn (*(int32_t *)re_gvar(0x0111d408u, sizeof(int32_t), (void *)&P96_DustOn))
#undef P96_Dust
#define P96_Dust (*(p96_dust_t *)re_gvar(0x0110e160u, sizeof(p96_dust_t), (void *)&P96_Dust))
#undef P96_DustN
#define P96_DustN (*(int32_t *)re_gvar(0x011171a0u, sizeof(int32_t), (void *)&P96_DustN))
#undef P96_ObjBOn
#define P96_ObjBOn (*(int32_t *)re_gvar(0x010fb204u, sizeof(int32_t), (void *)&P96_ObjBOn))
#undef P96_ReplayB
#define P96_ReplayB (*(uint8_t *)re_gvar(0x00b5a850u, sizeof(uint8_t), (void *)&P96_ReplayB))
#undef P96_RTag
#define P96_RTag (*(p96_tag_t *)re_gvar(0x00575d84u, sizeof(p96_tag_t), (void *)&P96_RTag))
#undef P96_ShadPage
#define P96_ShadPage (*(uint8_t *)re_gvar(0x00b5c7e2u, sizeof(uint8_t), (void *)&P96_ShadPage))
#undef P96_ShadIdx
#define P96_ShadIdx (*(p96_i4_t *)re_gvar(0x00b5c7e8u, sizeof(p96_i4_t), (void *)&P96_ShadIdx))
#undef P96_ShadRGB
#define P96_ShadRGB (*(p96_f3_t *)re_gvar(0x00b5c818u, sizeof(p96_f3_t), (void *)&P96_ShadRGB))
#undef P96_ShadUV
#define P96_ShadUV (*(p96_f12_t *)re_gvar(0x00b5c8dcu, sizeof(p96_f12_t), (void *)&P96_ShadUV))
#undef P96_ShadH
#define P96_ShadH (*(float *)re_gvar(0x00b80950u, sizeof(float), (void *)&P96_ShadH))
#undef P96_ShadW
#define P96_ShadW (*(float *)re_gvar(0x00b80954u, sizeof(float), (void *)&P96_ShadW))
#undef P96_PartTab
#define P96_PartTab (*(p96_parttab_t *)re_gvar(0x005759c4u, sizeof(p96_parttab_t), (void *)&P96_PartTab))
#endif
/* gvar-img v2.03 end */
