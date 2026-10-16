#pragma once
#include <stdint.h>
#include "gvar.h"
/* v1.73: ported128 — позиция копа на карте радара, свободная камера, попадание точки в модель-препятствие,
   деформация машины, поворот трафика на узле. Все функции cdecl (work/rets.py: ret без операнда). */
typedef uint8_t p128_dmg_t[11 * 0x1e0];
#define P128_DmgMap  GAME_VAR(p128_dmg_t, P128_DmgMap, 0x00559254)   /* карты повреждений видов 1..11 (.data, game/p128_data.h) */
#define P128_FreeCamLock GAME_VAR(int32_t, P128_FreeCamLock, 0x01137304)
#ifndef RE_HOOK_BUILD
#pragma push_macro("P128_DmgMap") /*gvi*/
#undef P128_DmgMap /*gvi*/
#pragma push_macro("P128_FreeCamLock") /*gvi*/
#undef P128_FreeCamLock /*gvi*/
extern p128_dmg_t P128_DmgMap; extern int32_t P128_FreeCamLock;
#pragma pop_macro("P128_FreeCamLock") /*gvi*/
#pragma pop_macro("P128_DmgMap") /*gvi*/
#endif
void    P128_CopMapPos(uint32_t *rec, int32_t *dx, int32_t *dz, int32_t mode);   /* 004a706a */
void    P128_FreeCam(int32_t car);                                                /* 0049dc73 */
int32_t P128_ModelHit(float x, float y, float z, uint32_t w);                     /* 004cd3fb */
void    P128_CarDeform(int32_t idx);                                              /* 004c032a */
void    P128_TrafficNode(uint8_t *t);                                             /* 004949f0 */
int32_t P128_CopPath(uint8_t *rec);                                               /* 0050c087 */
int32_t P128_CopRoute(int32_t *rec, int32_t dx, int32_t dz, int32_t start);       /* 0050d4a2 */
void    P128_CopReplan(uint8_t *rec);                                             /* 004a742a */
void    P128_TrafficDraw(void);                                                   /* 00490bcb */
int32_t P128_ClipAreaN(const int32_t *xy, int32_t n, const int32_t *rect);           /* v1.74: родные точки */
int32_t P128_ClipArea(const int32_t *poly, const int32_t *rect);                  /* 0050a15b */
/* gvar-img v2.03 begin (tools/gen_gvar_img.py) */
#if !defined(RE_HOOK_BUILD) && !defined(RE_GVAR_PLAIN)
#undef P128_DmgMap
#define P128_DmgMap (*(p128_dmg_t *)re_gvar(0x00559254u, sizeof(p128_dmg_t), (void *)&P128_DmgMap))
#undef P128_FreeCamLock
#define P128_FreeCamLock (*(int32_t *)re_gvar(0x01137304u, sizeof(int32_t), (void *)&P128_FreeCamLock))
#endif
/* gvar-img v2.03 end */
