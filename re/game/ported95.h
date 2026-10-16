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
extern p95_objsA_t P95_ObjA, P95_ObjC; extern p95_objsB_t P95_ObjB; extern float P95_Near;
extern int32_t P95_ChanState, P95_D1197C, P95_ChanLast, P95_D11A38, P95_SndRate, P95_D11A4C, P95_D11A54, P95_112D9D4, P95_SndReady, P95_SndOn;
extern p95_chandef_t P95_ChanDef; extern p95_chanvol_t P95_ChanVol; extern int32_t P95_AmbN; extern uint8_t P95_B87E14;
extern int32_t P95_B87E34, P95_B87E3C, P95_B87E40, P95_B87EA4, P95_B87EB4, P95_B87EBC, P95_B87EC0, P95_B87EC4, P95_B87ED0, P95_B87ED8, P95_B87EDC, P95_B87EE0, P95_B87F08;
extern int32_t P95_BDF9D0, P95_BDF9D4, P95_BDFA0C, P95_BDFA14, P95_BDFA5C, P95_BDFA60, P95_C818B8, P95_D11920, P95_575F1C;
extern int32_t P95_Deb0, P95_Deb1; extern p95_u4_t P95_DebRnd; extern p95_u16_t P95_DebPos;
extern uint8_t P95_PoolPage; extern p95_u12_t P95_PoolQuad;
extern int32_t P95_Near1, P95_Near2, P95_ModeSel; extern p95_modetab_t P95_ModeTab;
extern p95_line_fn P95_DrawLine; extern p95_vtx_t P95_LineV0, P95_LineV1; extern p95_i2_t P95_CrossOfs; extern p95_i6_t P95_CrossTab;
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
