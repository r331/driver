#pragma once
#include <stdint.h>
#include "gvar.h"
/* v1.80: ported135 — отрисовка частиц и следов (Glide-треугольники через P85_RasterB):
   обломок 004b33d8, искра 004b23f8, дымовой квадрат объекта 004b10ce, луч «шестёрки» 004ba81f,
   след призрака 004e6310, линия радара к объекту 005063a4. Все cdecl (work/rets.py: ret без операнда). */
void    P135_DebrisTri(int32_t *rec);      /* 004b33d8: треугольник обломка (позиция int, вершины P104_DebA/B, значок DEBRIS) */
void    P135_SparkQuad(uint8_t *o);        /* 004b23f8: искра — квадрат от экранной точки +0x10 к точке мира +0x40 */
void    P135_SmokeObj(uint8_t *o);         /* 004b10ce: квадрат дыма объекта (+0x50 размер, +0x58 яркость, +0x68 флаги) */
void    P135_SixBeam(const uint32_t *rec); /* 004ba81f: веер из трёх треугольников записи P98_Six (0x30) */
int32_t P135_GhostTrail(void);             /* 004e6310: лента следа призрака P56_GhostBuf (40 × 0x48) */
void    P135_RadarLine(int32_t i);         /* 005063a4: стрелка радара к объекту P58_Objs[i] */
