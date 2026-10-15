#pragma once
#include "gvar.h"
#include "unported.h"
#include "engine.h"
#include "crt.h"
#include "ported6.h"
#include "ported7.h"
#include "ported43.h"
#include "ported58.h"
#include "ported59.h"
#include "ported62.h"
#include "smallfuncs.h"
#include <stdint.h>
/* Шаг D: 9 функций — запуск частиц (варианты 4 и 2), поиск частицы по позиции, строка RLE-карты, чтение блока повтора и загрузка
   SAVES\REPLAYn.BIN, плавный переход цвета, текст с тенью, выбор ближайшего объекта радара. Все cdecl. */
void    P70_SpawnPart4(uint8_t *p);                               /* 00514332: как 00514261, но тип 4 */
void    P70_SpawnPart2(uint8_t *p);                               /* 00514403: как 00514261, но тип 2 */
int32_t P70_FindParticle(int32_t x, int32_t z);                   /* 00513905: номер (0..63) частицы с флагом 0x10 в пределах |dx|+|dz| < 100, иначе -1 */
int32_t P70_RowDecode(int32_t row, int16_t *dst);                 /* 0051ab31: строка карты (RLE пар {счёт, значение}) в MapN*MapN значений; 0 — пустая строка заполнена -1 */
int32_t P70_ReadChunk(void *f, const char *name, int32_t tag);    /* 00406369: блок [тег][размер][данные] из файла повтора в отдельный файл */
int32_t P70_LoadReplay(int32_t slot);                             /* 00406199: загрузить SAVES\REPLAY<slot+1>.BIN: заголовок, 0x38, блоки CFG/CAMS/PADS */
int32_t P70_FadeColor(void);                                      /* 005170ab: шаг перехода цвета b5a834.. к b5a838..; 1 — переход закончен */
void    P70_ShadowText(int32_t x, int32_t y, uint32_t txt, int32_t a, uint32_t flags, uint8_t r, uint8_t g, uint8_t b);  /* 0051755e: белая тень + текст цветом rgb */
void    P70_RadarNearest(void);                                   /* 005062cc: ближайший активный объект (флаг 1, без 0x40) → 005063a4 */
void    P70_RadarNearestB(void);                                  /* 0050784d: то же → 00507925 */
