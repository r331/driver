#pragma once
#include <stdint.h>
#include "gvar.h"
/* v1.74: ported129 — столкновения машин со статическими объектами карты (коробки объектов 00b31f50, слияние соседних,
   удар по объекту 0049b14d), такт объектов машины 00500e1d, отметка машин трафика на карте радара 0050b088.
   Все функции cdecl (work/rets.py: ret без операнда). */
typedef int32_t p129_boxes_t[60][8];          /* 00b31f50: 60 коробок по 0x20 {x, y, z, -, полуX, полуZ, флаги/угол, высота} */
#define P129_Boxes    GAME_VAR(p129_boxes_t, P129_Boxes, 0x00b31f50)
#define P129_BoxN     GAME_VAR(int32_t, P129_BoxN, 0x00c80944)      /* число отложенных коробок */
#define P129_HitModel GAME_VAR(uint16_t, P129_HitModel, 0x00c80938) /* модель объекта последнего удара */
#define P129_C81680   GAME_VAR(int32_t, P129_C81680, 0x00c81680)    /* номер миссии/сцены (звук удара 0x1be/0x1bf/0x15a/0x15b) */
#define P129_C81130   (*(int32_t *)(void *)((uint8_t *)P56_Blk84 + 0x70))   /* 00c81130 внутри P56_Blk84 (v1.65) */
#ifndef RE_HOOK_BUILD
extern p129_boxes_t P129_Boxes; extern int32_t P129_BoxN, P129_C81680; extern uint16_t P129_HitModel;
#endif
int32_t P129_BoxMerge(int32_t i, int32_t j, int32_t car);                                    /* 005001bb */
int32_t P129_ObjHit(uint8_t *car, int32_t *box, uint8_t *obj);                               /* 0049b14d */
void    P129_ObjBoxes(uint8_t *obj, const float *pos, uint8_t *car, int32_t idx, uint32_t model, int32_t defer); /* 00500937 */
void    P129_CarObjects(int32_t car);                                                        /* 00500e1d */
void    P129_MapCars(int32_t *rec);                                                          /* 0050b088 */
