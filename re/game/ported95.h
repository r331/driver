#pragma once
#include "gvar.h"
#include <stdint.h>
/* Шаг D, ported95 (v1.40): пачка простых/листовых функций — таблица звуковых каналов (00d11980) и запуск канала, сброс состояния
   заезда, совпадение последовательности направлений, сортировка трёх массивов объектов 0x78 по глубине (связный список 010ffb40),
   номер слота блока карты по точке, фоновые звуки, начальные значения осколков, значок CARPOOL6, ширина строки текущим шрифтом,
   поворот точек мини-карты, курс камеры из кватерниона, счёт/ближайшие записи трафика, настройки по умолчанию, линия Glide,
   шаг поворота скрипта камеры, крестик на мини-карте. Все cdecl.

   Ссылки +0x70/+0x74 в записях 0x78 (и голова списка 010ffb40): в hook — адреса Game.exe; в native — те же «адреса Game.exe»
   (0x010f5160 + i·0x78 и т. д.), которые P95_ObjPtr переводит в указатель на родной массив (как таблица рекордов в v1.15). */

#define P95_ObjA      GAME_VAR(p95_objsA_t, P95_ObjA, 0x010f5160)   /* 200 записей 0x78 (+0 x,y,z; +0x10 xyz в камере; +0x68 флаги) */
#define P95_ObjB      GAME_VAR(p95_objsB_t, P95_ObjB, 0x0110e500)   /* записи 0x78, счётчик G010FFD04 (до 011237c0 — 722) */
#define P95_ObjC      GAME_VAR(p95_objsA_t, P95_ObjC, 0x011237c0)   /* 200 записей 0x78, счётчик G010FFA20 */
#define P95_Near      GAME_VAR(float, P95_Near, 0x0054609c)         /* .rdata 50.0f — ближняя граница по z */
#define P95_ChanState GAME_VAR(int32_t, P95_ChanState, 0x00d11978)
#define P95_D1197C    GAME_VAR(int32_t, P95_D1197C, 0x00d1197c)
#define P95_ChanLast  GAME_VAR(int32_t, P95_ChanLast, 0x00d11a34)   /* последний запущенный канал (−1 — нет) */
#define P95_D11A38    GAME_VAR(int32_t, P95_D11A38, 0x00d11a38)
#define P95_SndRate   GAME_VAR(int32_t, P95_SndRate, 0x00d11a40)    /* 8000 — второй столбец громкостей */
#define P95_D11A4C    GAME_VAR(int32_t, P95_D11A4C, 0x00d11a4c)
#define P95_D11A54    GAME_VAR(int32_t, P95_D11A54, 0x00d11a54)
#define P95_112D9D4   GAME_VAR(int32_t, P95_112D9D4, 0x0112d9d4)
#define P95_SndReady  GAME_VAR(int32_t, P95_SndReady, 0x0112d9e4)
#define P95_SndOn     GAME_VAR(int32_t, P95_SndOn, 0x00575f54)      /* .data, начальное 1 */
#define P95_ChanDef   GAME_VAR(p95_chandef_t, P95_ChanDef, 0x0055fd50)  /* .data: 11 значений по умолчанию (+4 записи канала) */
#define P95_ChanVol   GAME_VAR(p95_chanvol_t, P95_ChanVol, 0x0055fd80)  /* .data: 11 пар громкостей (+0x58/+0x5c) */
#define P95_AmbN      GAME_VAR(int32_t, P95_AmbN, 0x0112b270)
#define P95_B87E14    GAME_VAR(uint8_t, P95_B87E14, 0x00b87e14)
#define P95_B87E34    GAME_VAR(int32_t, P95_B87E34, 0x00b87e34)
#define P95_B87E3C    GAME_VAR(int32_t, P95_B87E3C, 0x00b87e3c)
#define P95_B87E40    GAME_VAR(int32_t, P95_B87E40, 0x00b87e40)
#define P95_B87EA4    GAME_VAR(int32_t, P95_B87EA4, 0x00b87ea4)
#define P95_B87EB4    GAME_VAR(int32_t, P95_B87EB4, 0x00b87eb4)
#define P95_B87EBC    GAME_VAR(int32_t, P95_B87EBC, 0x00b87ebc)
#define P95_B87EC0    GAME_VAR(int32_t, P95_B87EC0, 0x00b87ec0)
#define P95_B87EC4    GAME_VAR(int32_t, P95_B87EC4, 0x00b87ec4)
#define P95_B87ED0    GAME_VAR(int32_t, P95_B87ED0, 0x00b87ed0)
#define P95_B87ED8    GAME_VAR(int32_t, P95_B87ED8, 0x00b87ed8)
#define P95_B87EDC    GAME_VAR(int32_t, P95_B87EDC, 0x00b87edc)
#define P95_B87EE0    GAME_VAR(int32_t, P95_B87EE0, 0x00b87ee0)
#define P95_B87F08    GAME_VAR(int32_t, P95_B87F08, 0x00b87f08)
#define P95_BDF9D0    GAME_VAR(int32_t, P95_BDF9D0, 0x00bdf9d0)
#define P95_BDF9D4    GAME_VAR(int32_t, P95_BDF9D4, 0x00bdf9d4)
#define P95_BDFA0C    GAME_VAR(int32_t, P95_BDFA0C, 0x00bdfa0c)
#define P95_BDFA14    GAME_VAR(int32_t, P95_BDFA14, 0x00bdfa14)
#define P95_BDFA5C    GAME_VAR(int32_t, P95_BDFA5C, 0x00bdfa5c)
#define P95_BDFA60    GAME_VAR(int32_t, P95_BDFA60, 0x00bdfa60)
#define P95_C818B8    GAME_VAR(int32_t, P95_C818B8, 0x00c818b8)
#define P95_D11920    GAME_VAR(int32_t, P95_D11920, 0x00d11920)
#define P95_575F1C    GAME_VAR(int32_t, P95_575F1C, 0x00575f1c)
#define P95_Deb0      GAME_VAR(int32_t, P95_Deb0, 0x0107c3c8)
#define P95_Deb1      GAME_VAR(int32_t, P95_Deb1, 0x010de050)
#define P95_DebRnd    GAME_VAR(p95_u4_t, P95_DebRnd, 0x010de060)
#define P95_DebPos    GAME_VAR(p95_u16_t, P95_DebPos, 0x010de230)   /* 4 точки по 4 слова (float x, y, z, —) */
#define P95_PoolIcon  ICONTAB_VAR(uint32_t, 7) /* запись значка CARPOOL6 (16 байт, P93_FindIcon) */
#define P95_PoolPage  GAME_VAR(uint8_t, P95_PoolPage, 0x01123282)
#define P95_PoolQuad  GAME_VAR(p95_u12_t, P95_PoolQuad, 0x01123288) /* 4 индекса + 8 float uv */
#define P95_Near1     GAME_VAR(int32_t, P95_Near1, 0x0056038c)      /* ближайшая запись трафика типа 4 (номер+1, −1 — нет) */
#define P95_Near2     GAME_VAR(int32_t, P95_Near2, 0x00560390)      /* вторая ближайшая */
#define P95_ModeSel   GAME_VAR(int32_t, P95_ModeSel, 0x00549cc8)
#define P95_ModeTab   GAME_VAR(p95_modetab_t, P95_ModeTab, 0x0054b6c8)  /* .data: 8 видеорежимов по 0x1c (w, h, имя, …, номер) */
#define P95_DrawLine  GAME_VAR(p95_line_fn, P95_DrawLine, 0x01270e00)   /* _grDrawLine@8 */
#define P95_LineV0    GAME_VAR(p95_vtx_t, P95_LineV0, 0x00b32988)   /* GrVertex (x, y, z, r, g, b, ooz, a, oow, …) */
#define P95_LineV1    GAME_VAR(p95_vtx_t, P95_LineV1, 0x00b329c8)
#define P95_CrossOfs  GAME_VAR(p95_i2_t, P95_CrossOfs, 0x00573f48)  /* .data: −2, 3 */
#define P95_CrossTab  GAME_VAR(p95_i6_t, P95_CrossTab, 0x00573f50)  /* .data: (−2,−3) (2,3) (2,−3) */

typedef uint8_t p95_objsA_t[200 * 0x78];
typedef uint8_t p95_objsB_t[722 * 0x78];
typedef int32_t p95_chandef_t[11];
typedef int32_t p95_chanvol_t[22];
typedef uint32_t p95_u4_t[4];
typedef uint32_t p95_u12_t[12];
typedef uint32_t p95_u16_t[16];
typedef uint32_t p95_modetab_t[8 * 7];
typedef float p95_vtx_t[16];
typedef int32_t p95_i2_t[2];
typedef int32_t p95_i6_t[6];
#ifdef RE_HOOK_BUILD
typedef void (__attribute__((stdcall)) *p95_line_fn)(const float *a, const float *b);
#else
typedef void (*p95_line_fn)(const float *a, const float *b);
#endif
/* аргумент 004e5d64: число направлений и их список (в Game.exe — таблицы .data 00562c10/18/20 с адресом списка) */
typedef struct { int32_t n; const int32_t *list; } p95_seq_t;

#ifndef RE_HOOK_BUILD
#pragma push_macro("P95_ObjA") /*gvi*/
#undef P95_ObjA /*gvi*/
#pragma push_macro("P95_ObjC") /*gvi*/
#undef P95_ObjC /*gvi*/
#pragma push_macro("P95_ObjB") /*gvi*/
#undef P95_ObjB /*gvi*/
#pragma push_macro("P95_Near") /*gvi*/
#undef P95_Near /*gvi*/
extern p95_objsA_t P95_ObjA, P95_ObjC; extern p95_objsB_t P95_ObjB; extern float P95_Near;
#pragma pop_macro("P95_Near") /*gvi*/
#pragma pop_macro("P95_ObjB") /*gvi*/
#pragma pop_macro("P95_ObjC") /*gvi*/
#pragma pop_macro("P95_ObjA") /*gvi*/
#pragma push_macro("P95_ChanState") /*gvi*/
#undef P95_ChanState /*gvi*/
#pragma push_macro("P95_D1197C") /*gvi*/
#undef P95_D1197C /*gvi*/
#pragma push_macro("P95_ChanLast") /*gvi*/
#undef P95_ChanLast /*gvi*/
#pragma push_macro("P95_D11A38") /*gvi*/
#undef P95_D11A38 /*gvi*/
#pragma push_macro("P95_SndRate") /*gvi*/
#undef P95_SndRate /*gvi*/
#pragma push_macro("P95_D11A4C") /*gvi*/
#undef P95_D11A4C /*gvi*/
#pragma push_macro("P95_D11A54") /*gvi*/
#undef P95_D11A54 /*gvi*/
#pragma push_macro("P95_112D9D4") /*gvi*/
#undef P95_112D9D4 /*gvi*/
#pragma push_macro("P95_SndReady") /*gvi*/
#undef P95_SndReady /*gvi*/
#pragma push_macro("P95_SndOn") /*gvi*/
#undef P95_SndOn /*gvi*/
extern int32_t P95_ChanState, P95_D1197C, P95_ChanLast, P95_D11A38, P95_SndRate, P95_D11A4C, P95_D11A54, P95_112D9D4, P95_SndReady, P95_SndOn;
#pragma pop_macro("P95_SndOn") /*gvi*/
#pragma pop_macro("P95_SndReady") /*gvi*/
#pragma pop_macro("P95_112D9D4") /*gvi*/
#pragma pop_macro("P95_D11A54") /*gvi*/
#pragma pop_macro("P95_D11A4C") /*gvi*/
#pragma pop_macro("P95_SndRate") /*gvi*/
#pragma pop_macro("P95_D11A38") /*gvi*/
#pragma pop_macro("P95_ChanLast") /*gvi*/
#pragma pop_macro("P95_D1197C") /*gvi*/
#pragma pop_macro("P95_ChanState") /*gvi*/
#pragma push_macro("P95_ChanDef") /*gvi*/
#undef P95_ChanDef /*gvi*/
#pragma push_macro("P95_ChanVol") /*gvi*/
#undef P95_ChanVol /*gvi*/
#pragma push_macro("P95_AmbN") /*gvi*/
#undef P95_AmbN /*gvi*/
#pragma push_macro("P95_B87E14") /*gvi*/
#undef P95_B87E14 /*gvi*/
extern p95_chandef_t P95_ChanDef; extern p95_chanvol_t P95_ChanVol; extern int32_t P95_AmbN; extern uint8_t P95_B87E14;
#pragma pop_macro("P95_B87E14") /*gvi*/
#pragma pop_macro("P95_AmbN") /*gvi*/
#pragma pop_macro("P95_ChanVol") /*gvi*/
#pragma pop_macro("P95_ChanDef") /*gvi*/
#pragma push_macro("P95_B87E34") /*gvi*/
#undef P95_B87E34 /*gvi*/
#pragma push_macro("P95_B87E3C") /*gvi*/
#undef P95_B87E3C /*gvi*/
#pragma push_macro("P95_B87E40") /*gvi*/
#undef P95_B87E40 /*gvi*/
#pragma push_macro("P95_B87EA4") /*gvi*/
#undef P95_B87EA4 /*gvi*/
#pragma push_macro("P95_B87EB4") /*gvi*/
#undef P95_B87EB4 /*gvi*/
#pragma push_macro("P95_B87EBC") /*gvi*/
#undef P95_B87EBC /*gvi*/
#pragma push_macro("P95_B87EC0") /*gvi*/
#undef P95_B87EC0 /*gvi*/
#pragma push_macro("P95_B87EC4") /*gvi*/
#undef P95_B87EC4 /*gvi*/
#pragma push_macro("P95_B87ED0") /*gvi*/
#undef P95_B87ED0 /*gvi*/
#pragma push_macro("P95_B87ED8") /*gvi*/
#undef P95_B87ED8 /*gvi*/
#pragma push_macro("P95_B87EDC") /*gvi*/
#undef P95_B87EDC /*gvi*/
#pragma push_macro("P95_B87EE0") /*gvi*/
#undef P95_B87EE0 /*gvi*/
#pragma push_macro("P95_B87F08") /*gvi*/
#undef P95_B87F08 /*gvi*/
extern int32_t P95_B87E34, P95_B87E3C, P95_B87E40, P95_B87EA4, P95_B87EB4, P95_B87EBC, P95_B87EC0, P95_B87EC4, P95_B87ED0, P95_B87ED8, P95_B87EDC, P95_B87EE0, P95_B87F08;
#pragma pop_macro("P95_B87F08") /*gvi*/
#pragma pop_macro("P95_B87EE0") /*gvi*/
#pragma pop_macro("P95_B87EDC") /*gvi*/
#pragma pop_macro("P95_B87ED8") /*gvi*/
#pragma pop_macro("P95_B87ED0") /*gvi*/
#pragma pop_macro("P95_B87EC4") /*gvi*/
#pragma pop_macro("P95_B87EC0") /*gvi*/
#pragma pop_macro("P95_B87EBC") /*gvi*/
#pragma pop_macro("P95_B87EB4") /*gvi*/
#pragma pop_macro("P95_B87EA4") /*gvi*/
#pragma pop_macro("P95_B87E40") /*gvi*/
#pragma pop_macro("P95_B87E3C") /*gvi*/
#pragma pop_macro("P95_B87E34") /*gvi*/
#pragma push_macro("P95_BDF9D0") /*gvi*/
#undef P95_BDF9D0 /*gvi*/
#pragma push_macro("P95_BDF9D4") /*gvi*/
#undef P95_BDF9D4 /*gvi*/
#pragma push_macro("P95_BDFA0C") /*gvi*/
#undef P95_BDFA0C /*gvi*/
#pragma push_macro("P95_BDFA14") /*gvi*/
#undef P95_BDFA14 /*gvi*/
#pragma push_macro("P95_BDFA5C") /*gvi*/
#undef P95_BDFA5C /*gvi*/
#pragma push_macro("P95_BDFA60") /*gvi*/
#undef P95_BDFA60 /*gvi*/
#pragma push_macro("P95_C818B8") /*gvi*/
#undef P95_C818B8 /*gvi*/
#pragma push_macro("P95_D11920") /*gvi*/
#undef P95_D11920 /*gvi*/
#pragma push_macro("P95_575F1C") /*gvi*/
#undef P95_575F1C /*gvi*/
extern int32_t P95_BDF9D0, P95_BDF9D4, P95_BDFA0C, P95_BDFA14, P95_BDFA5C, P95_BDFA60, P95_C818B8, P95_D11920, P95_575F1C;
#pragma pop_macro("P95_575F1C") /*gvi*/
#pragma pop_macro("P95_D11920") /*gvi*/
#pragma pop_macro("P95_C818B8") /*gvi*/
#pragma pop_macro("P95_BDFA60") /*gvi*/
#pragma pop_macro("P95_BDFA5C") /*gvi*/
#pragma pop_macro("P95_BDFA14") /*gvi*/
#pragma pop_macro("P95_BDFA0C") /*gvi*/
#pragma pop_macro("P95_BDF9D4") /*gvi*/
#pragma pop_macro("P95_BDF9D0") /*gvi*/
#pragma push_macro("P95_Deb0") /*gvi*/
#undef P95_Deb0 /*gvi*/
#pragma push_macro("P95_Deb1") /*gvi*/
#undef P95_Deb1 /*gvi*/
#pragma push_macro("P95_DebRnd") /*gvi*/
#undef P95_DebRnd /*gvi*/
#pragma push_macro("P95_DebPos") /*gvi*/
#undef P95_DebPos /*gvi*/
extern int32_t P95_Deb0, P95_Deb1; extern p95_u4_t P95_DebRnd; extern p95_u16_t P95_DebPos;
#pragma pop_macro("P95_DebPos") /*gvi*/
#pragma pop_macro("P95_DebRnd") /*gvi*/
#pragma pop_macro("P95_Deb1") /*gvi*/
#pragma pop_macro("P95_Deb0") /*gvi*/
#pragma push_macro("P95_PoolPage") /*gvi*/
#undef P95_PoolPage /*gvi*/
#pragma push_macro("P95_PoolQuad") /*gvi*/
#undef P95_PoolQuad /*gvi*/
extern uint8_t P95_PoolPage; extern p95_u12_t P95_PoolQuad;
#pragma pop_macro("P95_PoolQuad") /*gvi*/
#pragma pop_macro("P95_PoolPage") /*gvi*/
#pragma push_macro("P95_Near1") /*gvi*/
#undef P95_Near1 /*gvi*/
#pragma push_macro("P95_Near2") /*gvi*/
#undef P95_Near2 /*gvi*/
#pragma push_macro("P95_ModeSel") /*gvi*/
#undef P95_ModeSel /*gvi*/
#pragma push_macro("P95_ModeTab") /*gvi*/
#undef P95_ModeTab /*gvi*/
extern int32_t P95_Near1, P95_Near2, P95_ModeSel; extern p95_modetab_t P95_ModeTab;
#pragma pop_macro("P95_ModeTab") /*gvi*/
#pragma pop_macro("P95_ModeSel") /*gvi*/
#pragma pop_macro("P95_Near2") /*gvi*/
#pragma pop_macro("P95_Near1") /*gvi*/
#pragma push_macro("P95_LineV0") /*gvi*/
#undef P95_LineV0 /*gvi*/
#pragma push_macro("P95_LineV1") /*gvi*/
#undef P95_LineV1 /*gvi*/
#pragma push_macro("P95_CrossOfs") /*gvi*/
#undef P95_CrossOfs /*gvi*/
#pragma push_macro("P95_CrossTab") /*gvi*/
#undef P95_CrossTab /*gvi*/
extern p95_line_fn P95_DrawLine; extern p95_vtx_t P95_LineV0, P95_LineV1; extern p95_i2_t P95_CrossOfs; extern p95_i6_t P95_CrossTab;
#pragma pop_macro("P95_CrossTab") /*gvi*/
#pragma pop_macro("P95_CrossOfs") /*gvi*/
#pragma pop_macro("P95_LineV1") /*gvi*/
#pragma pop_macro("P95_LineV0") /*gvi*/
#endif

uint8_t *P95_ObjPtr(uint32_t ref);           /* ссылка списка → запись (NULL для 0) */
uint32_t P95_ObjRef(const uint8_t *rec);     /* запись → ссылка */

void    P95_SndInit(uint8_t *tab);                               /* 004d2500 */
void    P95_SndTrigger(uint8_t *tab, int32_t ch, int32_t vol);   /* 004d29e1: ch — байт */
void    P95_ResetRace(void);                                     /* 00405450 */
int32_t P95_SeqMatch(const p95_seq_t *s);                        /* 004e5d64 */
void    P95_SortObjC(void);                                      /* 004ba57a */
void    P95_SortObjB(void);                                      /* 004ba64d */
void    P95_SortObjA(void);                                      /* 004ba457 */
int32_t P95_SlotAt(int32_t x, int32_t z);                        /* 004c5f69 */
void    P95_AmbientTick(void);                                   /* 004d6ef2 */
void    P95_InitDebris(void);                                    /* 004c08bb */
void    P95_PoolIconInit(void);                                  /* 004ab808 */
float   P95_TextWidthCur(const uint8_t *s);                      /* 0040b0fe */
void    P95_MapRotate(const int32_t *src, int32_t *dst, int32_t n, const float *ofs, int32_t ang);   /* 00507de2 */
void    P95_CamFromQuat(const float *q);                         /* 0049f418 */
int32_t P95_CountNear(int32_t x, int32_t z, int32_t r);          /* 0048f6c1 */
void    P95_NearestTwo(void);                                    /* 004d65fa */
void    P95_DefaultOptions(void);                                /* 00405abe */
void    P95_DrawLineRGB(int32_t x0, int32_t y0, int32_t x1, int32_t y1, uint32_t rgb);   /* 00509d27 */
int32_t P95_ScriptTurn(void);                                    /* 004d0f28 */
void    P95_DrawCross(const float *pos);                         /* 00507310 */
/* gvar-img v2.03 begin (tools/gen_gvar_img.py) */
#if !defined(RE_HOOK_BUILD) && !defined(RE_GVAR_PLAIN)
#undef P95_ObjA
#define P95_ObjA (*(p95_objsA_t *)re_gvar(0x010f5160u, sizeof(p95_objsA_t), (void *)&P95_ObjA))
#undef P95_ObjB
#define P95_ObjB (*(p95_objsB_t *)re_gvar(0x0110e500u, sizeof(p95_objsB_t), (void *)&P95_ObjB))
#undef P95_ObjC
#define P95_ObjC (*(p95_objsA_t *)re_gvar(0x011237c0u, sizeof(p95_objsA_t), (void *)&P95_ObjC))
#undef P95_Near
#define P95_Near (*(float *)re_gvar(0x0054609cu, sizeof(float), (void *)&P95_Near))
#undef P95_ChanState
#define P95_ChanState (*(int32_t *)re_gvar(0x00d11978u, sizeof(int32_t), (void *)&P95_ChanState))
#undef P95_D1197C
#define P95_D1197C (*(int32_t *)re_gvar(0x00d1197cu, sizeof(int32_t), (void *)&P95_D1197C))
#undef P95_ChanLast
#define P95_ChanLast (*(int32_t *)re_gvar(0x00d11a34u, sizeof(int32_t), (void *)&P95_ChanLast))
#undef P95_D11A38
#define P95_D11A38 (*(int32_t *)re_gvar(0x00d11a38u, sizeof(int32_t), (void *)&P95_D11A38))
#undef P95_SndRate
#define P95_SndRate (*(int32_t *)re_gvar(0x00d11a40u, sizeof(int32_t), (void *)&P95_SndRate))
#undef P95_D11A4C
#define P95_D11A4C (*(int32_t *)re_gvar(0x00d11a4cu, sizeof(int32_t), (void *)&P95_D11A4C))
#undef P95_D11A54
#define P95_D11A54 (*(int32_t *)re_gvar(0x00d11a54u, sizeof(int32_t), (void *)&P95_D11A54))
#undef P95_112D9D4
#define P95_112D9D4 (*(int32_t *)re_gvar(0x0112d9d4u, sizeof(int32_t), (void *)&P95_112D9D4))
#undef P95_SndReady
#define P95_SndReady (*(int32_t *)re_gvar(0x0112d9e4u, sizeof(int32_t), (void *)&P95_SndReady))
#undef P95_SndOn
#define P95_SndOn (*(int32_t *)re_gvar(0x00575f54u, sizeof(int32_t), (void *)&P95_SndOn))
#undef P95_ChanDef
#define P95_ChanDef (*(p95_chandef_t *)re_gvar(0x0055fd50u, sizeof(p95_chandef_t), (void *)&P95_ChanDef))
#undef P95_ChanVol
#define P95_ChanVol (*(p95_chanvol_t *)re_gvar(0x0055fd80u, sizeof(p95_chanvol_t), (void *)&P95_ChanVol))
#undef P95_AmbN
#define P95_AmbN (*(int32_t *)re_gvar(0x0112b270u, sizeof(int32_t), (void *)&P95_AmbN))
#undef P95_B87E14
#define P95_B87E14 (*(uint8_t *)re_gvar(0x00b87e14u, sizeof(uint8_t), (void *)&P95_B87E14))
#undef P95_B87E34
#define P95_B87E34 (*(int32_t *)re_gvar(0x00b87e34u, sizeof(int32_t), (void *)&P95_B87E34))
#undef P95_B87E3C
#define P95_B87E3C (*(int32_t *)re_gvar(0x00b87e3cu, sizeof(int32_t), (void *)&P95_B87E3C))
#undef P95_B87E40
#define P95_B87E40 (*(int32_t *)re_gvar(0x00b87e40u, sizeof(int32_t), (void *)&P95_B87E40))
#undef P95_B87EA4
#define P95_B87EA4 (*(int32_t *)re_gvar(0x00b87ea4u, sizeof(int32_t), (void *)&P95_B87EA4))
#undef P95_B87EB4
#define P95_B87EB4 (*(int32_t *)re_gvar(0x00b87eb4u, sizeof(int32_t), (void *)&P95_B87EB4))
#undef P95_B87EBC
#define P95_B87EBC (*(int32_t *)re_gvar(0x00b87ebcu, sizeof(int32_t), (void *)&P95_B87EBC))
#undef P95_B87EC0
#define P95_B87EC0 (*(int32_t *)re_gvar(0x00b87ec0u, sizeof(int32_t), (void *)&P95_B87EC0))
#undef P95_B87EC4
#define P95_B87EC4 (*(int32_t *)re_gvar(0x00b87ec4u, sizeof(int32_t), (void *)&P95_B87EC4))
#undef P95_B87ED0
#define P95_B87ED0 (*(int32_t *)re_gvar(0x00b87ed0u, sizeof(int32_t), (void *)&P95_B87ED0))
#undef P95_B87ED8
#define P95_B87ED8 (*(int32_t *)re_gvar(0x00b87ed8u, sizeof(int32_t), (void *)&P95_B87ED8))
#undef P95_B87EDC
#define P95_B87EDC (*(int32_t *)re_gvar(0x00b87edcu, sizeof(int32_t), (void *)&P95_B87EDC))
#undef P95_B87EE0
#define P95_B87EE0 (*(int32_t *)re_gvar(0x00b87ee0u, sizeof(int32_t), (void *)&P95_B87EE0))
#undef P95_B87F08
#define P95_B87F08 (*(int32_t *)re_gvar(0x00b87f08u, sizeof(int32_t), (void *)&P95_B87F08))
#undef P95_BDF9D0
#define P95_BDF9D0 (*(int32_t *)re_gvar(0x00bdf9d0u, sizeof(int32_t), (void *)&P95_BDF9D0))
#undef P95_BDF9D4
#define P95_BDF9D4 (*(int32_t *)re_gvar(0x00bdf9d4u, sizeof(int32_t), (void *)&P95_BDF9D4))
#undef P95_BDFA0C
#define P95_BDFA0C (*(int32_t *)re_gvar(0x00bdfa0cu, sizeof(int32_t), (void *)&P95_BDFA0C))
#undef P95_BDFA14
#define P95_BDFA14 (*(int32_t *)re_gvar(0x00bdfa14u, sizeof(int32_t), (void *)&P95_BDFA14))
#undef P95_BDFA5C
#define P95_BDFA5C (*(int32_t *)re_gvar(0x00bdfa5cu, sizeof(int32_t), (void *)&P95_BDFA5C))
#undef P95_BDFA60
#define P95_BDFA60 (*(int32_t *)re_gvar(0x00bdfa60u, sizeof(int32_t), (void *)&P95_BDFA60))
#undef P95_C818B8
#define P95_C818B8 (*(int32_t *)re_gvar(0x00c818b8u, sizeof(int32_t), (void *)&P95_C818B8))
#undef P95_D11920
#define P95_D11920 (*(int32_t *)re_gvar(0x00d11920u, sizeof(int32_t), (void *)&P95_D11920))
#undef P95_575F1C
#define P95_575F1C (*(int32_t *)re_gvar(0x00575f1cu, sizeof(int32_t), (void *)&P95_575F1C))
#undef P95_Deb0
#define P95_Deb0 (*(int32_t *)re_gvar(0x0107c3c8u, sizeof(int32_t), (void *)&P95_Deb0))
#undef P95_Deb1
#define P95_Deb1 (*(int32_t *)re_gvar(0x010de050u, sizeof(int32_t), (void *)&P95_Deb1))
#undef P95_DebRnd
#define P95_DebRnd (*(p95_u4_t *)re_gvar(0x010de060u, sizeof(p95_u4_t), (void *)&P95_DebRnd))
#undef P95_DebPos
#define P95_DebPos (*(p95_u16_t *)re_gvar(0x010de230u, sizeof(p95_u16_t), (void *)&P95_DebPos))
#undef P95_PoolPage
#define P95_PoolPage (*(uint8_t *)re_gvar(0x01123282u, sizeof(uint8_t), (void *)&P95_PoolPage))
#undef P95_PoolQuad
#define P95_PoolQuad (*(p95_u12_t *)re_gvar(0x01123288u, sizeof(p95_u12_t), (void *)&P95_PoolQuad))
#undef P95_Near1
#define P95_Near1 (*(int32_t *)re_gvar(0x0056038cu, sizeof(int32_t), (void *)&P95_Near1))
#undef P95_Near2
#define P95_Near2 (*(int32_t *)re_gvar(0x00560390u, sizeof(int32_t), (void *)&P95_Near2))
#undef P95_ModeSel
#define P95_ModeSel (*(int32_t *)re_gvar(0x00549cc8u, sizeof(int32_t), (void *)&P95_ModeSel))
#undef P95_ModeTab
#define P95_ModeTab (*(p95_modetab_t *)re_gvar(0x0054b6c8u, sizeof(p95_modetab_t), (void *)&P95_ModeTab))
#undef P95_LineV0
#define P95_LineV0 (*(p95_vtx_t *)re_gvar(0x00b32988u, sizeof(p95_vtx_t), (void *)&P95_LineV0))
#undef P95_LineV1
#define P95_LineV1 (*(p95_vtx_t *)re_gvar(0x00b329c8u, sizeof(p95_vtx_t), (void *)&P95_LineV1))
#undef P95_CrossOfs
#define P95_CrossOfs (*(p95_i2_t *)re_gvar(0x00573f48u, sizeof(p95_i2_t), (void *)&P95_CrossOfs))
#undef P95_CrossTab
#define P95_CrossTab (*(p95_i6_t *)re_gvar(0x00573f50u, sizeof(p95_i6_t), (void *)&P95_CrossTab))
#endif
/* gvar-img v2.03 end */
