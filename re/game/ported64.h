#pragma once
#include "gvar.h"
#include "unported.h"
#include "engine.h"
#include "crt.h"
#include "ported42.h"
#include "ported57.h"
#include "ported59.h"
#include "smallfuncs.h"
#include <stdint.h>
/* Шаг D: 10 функций — сохранение повтора (SAVES\REPLAYn.BIN) и место в таблице рекордов. Все cdecl.
   Запись состязания (struct): +8 результат, +0xc таблица рекордов (32-битный указатель), +0x10/+0x28 время, +0x2c тип, +0x40 флаг «есть результат».
   Строка таблицы — 0x2c байт: +0x10 результат, +0x14 время, +0x18 признак занятости (8). Время сравнивается как PackRGB (+0xc,+0x10,+0x14). */
#ifndef RE_HOOK_BUILD
/* В native 32-битное поле +0xc не вмещает указатель: 0051cc55 кладёт текущую таблицу сюда (тест задаёт P64_NativeTable). */
extern const uint8_t *P64_NativeTable;
extern const uint8_t *P64_CurTable;
#endif
int32_t P64_SaveChunk(void *file, const char *name, uint32_t tag);   /* 00406272: [тег][размер][данные файла name] */
int32_t P64_SaveReplay(int32_t slot);                                /* 00406096: SAVES\REPLAY<slot+1>.BIN */
int32_t P64_ReplayStart(int32_t slot, const char *name);             /* 00405f6f: имя повтора, сумма, затем запись */
int32_t P64_RankBestFirst(uint8_t *e);   /* 0051cf17: тип 1 — больше результат, при равенстве меньше время */
int32_t P64_RankTimeMore(uint8_t *e);    /* 0051ce94: тип 2 — место по времени (новое меньше → выше) */
int32_t P64_RankTimeLess(uint8_t *e);    /* 0051cfda: тип 3 */
int32_t P64_RankTimeB(uint8_t *e);       /* 0051d05d: тип 0xb */
int32_t P64_RankScoreB(uint8_t *e);      /* 0051d0e0: тип 7 — как 0051cf17 */
int32_t P64_RankTop(uint8_t *e);         /* 0051d1a3: тип 0xc */
int32_t P64_RankPlace(void *e, int32_t type, int32_t idx);   /* 0051cc55: выбор таблицы и вызов нужной проверки */
