/* v1.48 — восстановлено из Game.exe. Все функции cdecl (ret без операнда проверен по Game.exe).
   Модели миссии 004fede5, рассвет/закат 004cb102/004cb2f5, машины миссии 4 004e4d35, состояние призрака 004e5011,
   экран настроек 00414d1f (.data меню 0054db58..0054de94 — одна таблица P103_MenuTab, game/menutab.h) и др. (см. ported103.c). */
#pragma once
#include "gvar.h"
#include "reptr.h"
#include "cartab.h"
#include "menutab.h"
#include <stdint.h>

#define P103_MObjN      GAME_VAR(int32_t, P103_MObjN, 0x00c80948)      /* число записей объектов текущей миссии */
#define P103_Slider     GAME_VAR(uint8_t *, P103_Slider, 0x005fe9d8)   /* значок SLIDER */
#define P103_SliderBar  GAME_VAR(uint8_t *, P103_SliderBar, 0x005fe9d4) /* значок SLIDERBA */
typedef int32_t p103_box_t[0x42 * 6];
#define P103_CarBoxes GAME_VAR(p103_box_t, P103_CarBoxes, 0x00b2ecd0)   /* коробки машин /16: x0 y0 z0 x1 y1 z1 */
#ifndef RE_HOOK_BUILD
#pragma push_macro("P103_CarBoxes") /*gvi*/
#undef P103_CarBoxes /*gvi*/
extern p103_box_t P103_CarBoxes;
#pragma pop_macro("P103_CarBoxes") /*gvi*/
#endif
/* высота дороги 004dcb62 (кэш последней клетки/четырёхугольника; указатели в блоке карты — родные) */
#define P103_HQuad  GAME_VAR(uint8_t *, P103_HQuad, 0x00b2f300)
#define P103_HBlk   GAME_VAR(uint8_t *, P103_HBlk, 0x00b2f308)
#define P103_HCellZ GAME_VAR(int32_t, P103_HCellZ, 0x00bdfaf0)
#define P103_HCellX GAME_VAR(int32_t, P103_HCellX, 0x00bdfaf4)
#ifndef RE_HOOK_BUILD
#pragma push_macro("P103_HCellZ") /*gvi*/
#undef P103_HCellZ /*gvi*/
#pragma push_macro("P103_HCellX") /*gvi*/
#undef P103_HCellX /*gvi*/
extern uint8_t *P103_HQuad, *P103_HBlk; extern int32_t P103_HCellZ, P103_HCellX;
#pragma pop_macro("P103_HCellX") /*gvi*/
#pragma pop_macro("P103_HCellZ") /*gvi*/
#endif
#define P103_D118E0 GAME_VAR(int32_t, P103_D118E0, 0x00d118e0)   /* фаза качки (индекс P43_Sin) */
#ifndef RE_HOOK_BUILD
#pragma push_macro("P103_D118E0") /*gvi*/
#undef P103_D118E0 /*gvi*/
extern int32_t P103_D118E0;
#pragma pop_macro("P103_D118E0") /*gvi*/
#endif
typedef int32_t p103_i4_t[4];
#define P103_PathLen GAME_VAR(p103_i4_t, P103_PathLen, 0x00c81990)   /* число точек пути частицы по типу (буферы P54_Tab4) */
#define P103_PathK   GAME_VAR(float, P103_PathK, 0x00c56714)
#ifndef RE_HOOK_BUILD
#pragma push_macro("P103_PathLen") /*gvi*/
#undef P103_PathLen /*gvi*/
#pragma push_macro("P103_PathK") /*gvi*/
#undef P103_PathK /*gvi*/
extern p103_i4_t P103_PathLen; extern float P103_PathK;
#pragma pop_macro("P103_PathK") /*gvi*/
#pragma pop_macro("P103_PathLen") /*gvi*/
#endif
/* сброс записи повтора 005179d0 */
typedef uint8_t p103_b88_t[0x88];
#define P103_B5A848 GAME_VAR(int32_t, P103_B5A848, 0x00b5a848)
#define P103_B5A84C GAME_VAR(int32_t, P103_B5A84C, 0x00b5a84c)
#define P103_B5A895 GAME_VAR(uint8_t, P103_B5A895, 0x00b5a895)
#define P103_B5A8A9 GAME_VAR(uint8_t, P103_B5A8A9, 0x00b5a8a9)
#define P103_B5A8AA GAME_VAR(uint8_t, P103_B5A8AA, 0x00b5a8aa)
#define P103_B5A8B4 GAME_VAR(int32_t, P103_B5A8B4, 0x00b5a8b4)
#define P103_B5A8B8 GAME_VAR(int32_t, P103_B5A8B8, 0x00b5a8b8)
#define P103_B5A8C4 GAME_VAR(int32_t, P103_B5A8C4, 0x00b5a8c4)
#define P103_B5A8C8 GAME_VAR(int32_t, P103_B5A8C8, 0x00b5a8c8)
#define P103_C4D664 GAME_VAR(uint8_t, P103_C4D664, 0x00c4d664)
#define P103_C4D874 GAME_VAR(int32_t, P103_C4D874, 0x00c4d874)
#define P103_C4D920 GAME_VAR(int32_t, P103_C4D920, 0x00c4d920)
#define P103_C4D924 GAME_VAR(int32_t, P103_C4D924, 0x00c4d924)
#define P103_C4D9A0 GAME_VAR(int32_t, P103_C4D9A0, 0x00c4d9a0)
#define P103_C4D9A4 GAME_VAR(uint8_t, P103_C4D9A4, 0x00c4d9a4)
#define P103_C54AA0 GAME_VAR(int32_t, P103_C54AA0, 0x00c54aa0)
#define P103_C54D00 GAME_VAR(int32_t, P103_C54D00, 0x00c54d00)
#define P103_C54D04 GAME_VAR(int32_t, P103_C54D04, 0x00c54d04)
#define P103_C54EC4 GAME_VAR(int32_t, P103_C54EC4, 0x00c54ec4)
#define P103_C54FC0 GAME_VAR(int32_t, P103_C54FC0, 0x00c54fc0)
#define P103_C54FC4 GAME_VAR(int32_t, P103_C54FC4, 0x00c54fc4)
#define P103_C54EE0 GAME_VAR(p103_b88_t, P103_C54EE0, 0x00c54ee0)
#ifndef RE_HOOK_BUILD
#pragma push_macro("P103_B5A848") /*gvi*/
#undef P103_B5A848 /*gvi*/
extern int32_t P103_B5A848;
#pragma pop_macro("P103_B5A848") /*gvi*/
#pragma push_macro("P103_B5A84C") /*gvi*/
#undef P103_B5A84C /*gvi*/
extern int32_t P103_B5A84C;
#pragma pop_macro("P103_B5A84C") /*gvi*/
#pragma push_macro("P103_B5A895") /*gvi*/
#undef P103_B5A895 /*gvi*/
extern uint8_t P103_B5A895;
#pragma pop_macro("P103_B5A895") /*gvi*/
#pragma push_macro("P103_B5A8A9") /*gvi*/
#undef P103_B5A8A9 /*gvi*/
extern uint8_t P103_B5A8A9;
#pragma pop_macro("P103_B5A8A9") /*gvi*/
#pragma push_macro("P103_B5A8AA") /*gvi*/
#undef P103_B5A8AA /*gvi*/
extern uint8_t P103_B5A8AA;
#pragma pop_macro("P103_B5A8AA") /*gvi*/
#pragma push_macro("P103_B5A8B4") /*gvi*/
#undef P103_B5A8B4 /*gvi*/
extern int32_t P103_B5A8B4;
#pragma pop_macro("P103_B5A8B4") /*gvi*/
#pragma push_macro("P103_B5A8B8") /*gvi*/
#undef P103_B5A8B8 /*gvi*/
extern int32_t P103_B5A8B8;
#pragma pop_macro("P103_B5A8B8") /*gvi*/
#pragma push_macro("P103_B5A8C4") /*gvi*/
#undef P103_B5A8C4 /*gvi*/
extern int32_t P103_B5A8C4;
#pragma pop_macro("P103_B5A8C4") /*gvi*/
#pragma push_macro("P103_B5A8C8") /*gvi*/
#undef P103_B5A8C8 /*gvi*/
extern int32_t P103_B5A8C8;
#pragma pop_macro("P103_B5A8C8") /*gvi*/
#pragma push_macro("P103_C4D664") /*gvi*/
#undef P103_C4D664 /*gvi*/
extern uint8_t P103_C4D664;
#pragma pop_macro("P103_C4D664") /*gvi*/
#pragma push_macro("P103_C4D874") /*gvi*/
#undef P103_C4D874 /*gvi*/
extern int32_t P103_C4D874;
#pragma pop_macro("P103_C4D874") /*gvi*/
#pragma push_macro("P103_C4D920") /*gvi*/
#undef P103_C4D920 /*gvi*/
extern int32_t P103_C4D920;
#pragma pop_macro("P103_C4D920") /*gvi*/
#pragma push_macro("P103_C4D924") /*gvi*/
#undef P103_C4D924 /*gvi*/
extern int32_t P103_C4D924;
#pragma pop_macro("P103_C4D924") /*gvi*/
#pragma push_macro("P103_C4D9A0") /*gvi*/
#undef P103_C4D9A0 /*gvi*/
extern int32_t P103_C4D9A0;
#pragma pop_macro("P103_C4D9A0") /*gvi*/
#pragma push_macro("P103_C4D9A4") /*gvi*/
#undef P103_C4D9A4 /*gvi*/
extern uint8_t P103_C4D9A4;
#pragma pop_macro("P103_C4D9A4") /*gvi*/
#pragma push_macro("P103_C54AA0") /*gvi*/
#undef P103_C54AA0 /*gvi*/
extern int32_t P103_C54AA0;
#pragma pop_macro("P103_C54AA0") /*gvi*/
#pragma push_macro("P103_C54D00") /*gvi*/
#undef P103_C54D00 /*gvi*/
extern int32_t P103_C54D00;
#pragma pop_macro("P103_C54D00") /*gvi*/
#pragma push_macro("P103_C54D04") /*gvi*/
#undef P103_C54D04 /*gvi*/
extern int32_t P103_C54D04;
#pragma pop_macro("P103_C54D04") /*gvi*/
#pragma push_macro("P103_C54EC4") /*gvi*/
#undef P103_C54EC4 /*gvi*/
extern int32_t P103_C54EC4;
#pragma pop_macro("P103_C54EC4") /*gvi*/
#pragma push_macro("P103_C54FC0") /*gvi*/
#undef P103_C54FC0 /*gvi*/
extern int32_t P103_C54FC0;
#pragma pop_macro("P103_C54FC0") /*gvi*/
#pragma push_macro("P103_C54FC4") /*gvi*/
#undef P103_C54FC4 /*gvi*/
extern int32_t P103_C54FC4;
#pragma pop_macro("P103_C54FC4") /*gvi*/
#pragma push_macro("P103_C54EE0") /*gvi*/
#undef P103_C54EE0 /*gvi*/
extern p103_b88_t P103_C54EE0;
#pragma pop_macro("P103_C54EE0") /*gvi*/
#endif
/* сброс трафика 00492f7d */
#define P103_1373D4 GAME_VAR(int32_t, P103_1373D4, 0x011373d4)
#define P103_139A38 GAME_VAR(int32_t, P103_139A38, 0x01139a38)
#define P103_13A5A0 GAME_VAR(int32_t, P103_13A5A0, 0x0113a5a0)
#define P103_1426E0 GAME_VAR(int32_t, P103_1426E0, 0x011426e0)
#define P103_1426EC GAME_VAR(int32_t, P103_1426EC, 0x011426ec)
#define P103_1426F0 GAME_VAR(int32_t, P103_1426F0, 0x011426f0)
#define P103_1426F4 GAME_VAR(int32_t, P103_1426F4, 0x011426f4)
#define P103_143724 GAME_VAR(int32_t, P103_143724, 0x01143724)
#define P103_144320 GAME_VAR(int32_t, P103_144320, 0x01144320)
#define P103_1443C0 GAME_VAR(int32_t, P103_1443C0, 0x011443c0)
#define P103_145A44 GAME_VAR(int32_t, P103_145A44, 0x01145a44)
#define P103_DmgPct GAME_VAR(int32_t, P103_DmgPct, 0x011373c8)   /* множитель повреждений трафика, % */
#ifndef RE_HOOK_BUILD
#pragma push_macro("P103_DmgPct") /*gvi*/
#undef P103_DmgPct /*gvi*/
extern int32_t P103_DmgPct;
#pragma pop_macro("P103_DmgPct") /*gvi*/
#pragma push_macro("P103_1373D4") /*gvi*/
#undef P103_1373D4 /*gvi*/
#pragma push_macro("P103_139A38") /*gvi*/
#undef P103_139A38 /*gvi*/
#pragma push_macro("P103_13A5A0") /*gvi*/
#undef P103_13A5A0 /*gvi*/
#pragma push_macro("P103_1426E0") /*gvi*/
#undef P103_1426E0 /*gvi*/
#pragma push_macro("P103_1426EC") /*gvi*/
#undef P103_1426EC /*gvi*/
#pragma push_macro("P103_1426F0") /*gvi*/
#undef P103_1426F0 /*gvi*/
#pragma push_macro("P103_1426F4") /*gvi*/
#undef P103_1426F4 /*gvi*/
#pragma push_macro("P103_143724") /*gvi*/
#undef P103_143724 /*gvi*/
#pragma push_macro("P103_144320") /*gvi*/
#undef P103_144320 /*gvi*/
extern int32_t P103_1373D4, P103_139A38, P103_13A5A0, P103_1426E0, P103_1426EC, P103_1426F0, P103_1426F4, P103_143724, P103_144320,
#pragma pop_macro("P103_144320") /*gvi*/
#pragma pop_macro("P103_143724") /*gvi*/
#pragma pop_macro("P103_1426F4") /*gvi*/
#pragma pop_macro("P103_1426F0") /*gvi*/
#pragma pop_macro("P103_1426EC") /*gvi*/
#pragma pop_macro("P103_1426E0") /*gvi*/
#pragma pop_macro("P103_13A5A0") /*gvi*/
#pragma pop_macro("P103_139A38") /*gvi*/
#pragma pop_macro("P103_1373D4") /*gvi*/
  P103_1443C0, P103_145A44;
#pragma push_macro("P103_MObjN") /*gvi*/
#undef P103_MObjN /*gvi*/
extern int32_t P103_MObjN; extern uint8_t *P103_Slider, *P103_SliderBar;
#pragma pop_macro("P103_MObjN") /*gvi*/
extern uint8_t P103_MObj[];      /* .data 00572f00..00573810 (game/p103_data.h), зарегистрирована в k_regions */
#endif

void     P103_MissionModels(void);                                                      /* 004fede5 */
void     P103_Dawn(void);                                                               /* 004cb102 */
void     P103_Dusk(void);                                                               /* 004cb2f5 */
void     P103_Mission4Cars(void);                                                       /* 004e4d35 */
void     P103_GhostState(void);                                                         /* 004e5011 */
void     P103_OptionsInit(void);                                                        /* 00414d1f */
void     P103_TrafficTick(uint8_t *rec);                                                /* 00493ff7 */
void     P103_TrafficReset(void);                                                       /* 00492f7d */
int32_t  P103_RoadNeighbour(int32_t x, int32_t z, uint32_t dir);                         /* 0051b208 */
int32_t  P103_CarDamage(uint8_t *car, const int32_t *dir, int32_t force);                 /* 0049aa14 */
int32_t  P103_CopMeet(uint8_t *cop, const uint8_t *rec);                                 /* 004a6a57 */
void     P103_ReplayReset(void);                                                        /* 005179d0 */
void     P103_TrafficSpawn(int8_t lane, int32_t kind, int8_t speed, int32_t heading, int32_t x, int32_t z);   /* 00492530 */
int32_t  P103_TrafficCanGo(uint8_t *r);                                                 /* 0048edff */
void     P103_CarsOverlap(void);                                                        /* 004deb99 */
int32_t  P103_BoxContactTime(int32_t *p, uint8_t *out);                                 /* 0049a520 */
float    P103_RoadHeight(const float *pos);                                             /* 004dcb62 */
int32_t  P103_GroundAt(const int32_t *pos, int32_t *normal, int32_t *out);                /* 004dd262 */
void     P103_PartPath(uint8_t *p);                                                     /* 00512de7 */
/* gvar-img v2.03 begin (tools/gen_gvar_img.py) */
#if !defined(RE_HOOK_BUILD) && !defined(RE_GVAR_PLAIN)
#undef P103_MObjN
#define P103_MObjN (*(int32_t *)re_gvar(0x00c80948u, sizeof(int32_t), (void *)&P103_MObjN))
#undef P103_CarBoxes
#define P103_CarBoxes (*(p103_box_t *)re_gvar(0x00b2ecd0u, sizeof(p103_box_t), (void *)&P103_CarBoxes))
#undef P103_HCellZ
#define P103_HCellZ (*(int32_t *)re_gvar(0x00bdfaf0u, sizeof(int32_t), (void *)&P103_HCellZ))
#undef P103_HCellX
#define P103_HCellX (*(int32_t *)re_gvar(0x00bdfaf4u, sizeof(int32_t), (void *)&P103_HCellX))
#undef P103_D118E0
#define P103_D118E0 (*(int32_t *)re_gvar(0x00d118e0u, sizeof(int32_t), (void *)&P103_D118E0))
#undef P103_PathLen
#define P103_PathLen (*(p103_i4_t *)re_gvar(0x00c81990u, sizeof(p103_i4_t), (void *)&P103_PathLen))
#undef P103_PathK
#define P103_PathK (*(float *)re_gvar(0x00c56714u, sizeof(float), (void *)&P103_PathK))
#undef P103_B5A848
#define P103_B5A848 (*(int32_t *)re_gvar(0x00b5a848u, sizeof(int32_t), (void *)&P103_B5A848))
#undef P103_B5A84C
#define P103_B5A84C (*(int32_t *)re_gvar(0x00b5a84cu, sizeof(int32_t), (void *)&P103_B5A84C))
#undef P103_B5A895
#define P103_B5A895 (*(uint8_t *)re_gvar(0x00b5a895u, sizeof(uint8_t), (void *)&P103_B5A895))
#undef P103_B5A8A9
#define P103_B5A8A9 (*(uint8_t *)re_gvar(0x00b5a8a9u, sizeof(uint8_t), (void *)&P103_B5A8A9))
#undef P103_B5A8AA
#define P103_B5A8AA (*(uint8_t *)re_gvar(0x00b5a8aau, sizeof(uint8_t), (void *)&P103_B5A8AA))
#undef P103_B5A8B4
#define P103_B5A8B4 (*(int32_t *)re_gvar(0x00b5a8b4u, sizeof(int32_t), (void *)&P103_B5A8B4))
#undef P103_B5A8B8
#define P103_B5A8B8 (*(int32_t *)re_gvar(0x00b5a8b8u, sizeof(int32_t), (void *)&P103_B5A8B8))
#undef P103_B5A8C4
#define P103_B5A8C4 (*(int32_t *)re_gvar(0x00b5a8c4u, sizeof(int32_t), (void *)&P103_B5A8C4))
#undef P103_B5A8C8
#define P103_B5A8C8 (*(int32_t *)re_gvar(0x00b5a8c8u, sizeof(int32_t), (void *)&P103_B5A8C8))
#undef P103_C4D664
#define P103_C4D664 (*(uint8_t *)re_gvar(0x00c4d664u, sizeof(uint8_t), (void *)&P103_C4D664))
#undef P103_C4D874
#define P103_C4D874 (*(int32_t *)re_gvar(0x00c4d874u, sizeof(int32_t), (void *)&P103_C4D874))
#undef P103_C4D920
#define P103_C4D920 (*(int32_t *)re_gvar(0x00c4d920u, sizeof(int32_t), (void *)&P103_C4D920))
#undef P103_C4D924
#define P103_C4D924 (*(int32_t *)re_gvar(0x00c4d924u, sizeof(int32_t), (void *)&P103_C4D924))
#undef P103_C4D9A0
#define P103_C4D9A0 (*(int32_t *)re_gvar(0x00c4d9a0u, sizeof(int32_t), (void *)&P103_C4D9A0))
#undef P103_C4D9A4
#define P103_C4D9A4 (*(uint8_t *)re_gvar(0x00c4d9a4u, sizeof(uint8_t), (void *)&P103_C4D9A4))
#undef P103_C54AA0
#define P103_C54AA0 (*(int32_t *)re_gvar(0x00c54aa0u, sizeof(int32_t), (void *)&P103_C54AA0))
#undef P103_C54D00
#define P103_C54D00 (*(int32_t *)re_gvar(0x00c54d00u, sizeof(int32_t), (void *)&P103_C54D00))
#undef P103_C54D04
#define P103_C54D04 (*(int32_t *)re_gvar(0x00c54d04u, sizeof(int32_t), (void *)&P103_C54D04))
#undef P103_C54EC4
#define P103_C54EC4 (*(int32_t *)re_gvar(0x00c54ec4u, sizeof(int32_t), (void *)&P103_C54EC4))
#undef P103_C54FC0
#define P103_C54FC0 (*(int32_t *)re_gvar(0x00c54fc0u, sizeof(int32_t), (void *)&P103_C54FC0))
#undef P103_C54FC4
#define P103_C54FC4 (*(int32_t *)re_gvar(0x00c54fc4u, sizeof(int32_t), (void *)&P103_C54FC4))
#undef P103_C54EE0
#define P103_C54EE0 (*(p103_b88_t *)re_gvar(0x00c54ee0u, sizeof(p103_b88_t), (void *)&P103_C54EE0))
#undef P103_1373D4
#define P103_1373D4 (*(int32_t *)re_gvar(0x011373d4u, sizeof(int32_t), (void *)&P103_1373D4))
#undef P103_139A38
#define P103_139A38 (*(int32_t *)re_gvar(0x01139a38u, sizeof(int32_t), (void *)&P103_139A38))
#undef P103_13A5A0
#define P103_13A5A0 (*(int32_t *)re_gvar(0x0113a5a0u, sizeof(int32_t), (void *)&P103_13A5A0))
#undef P103_1426E0
#define P103_1426E0 (*(int32_t *)re_gvar(0x011426e0u, sizeof(int32_t), (void *)&P103_1426E0))
#undef P103_1426EC
#define P103_1426EC (*(int32_t *)re_gvar(0x011426ecu, sizeof(int32_t), (void *)&P103_1426EC))
#undef P103_1426F0
#define P103_1426F0 (*(int32_t *)re_gvar(0x011426f0u, sizeof(int32_t), (void *)&P103_1426F0))
#undef P103_1426F4
#define P103_1426F4 (*(int32_t *)re_gvar(0x011426f4u, sizeof(int32_t), (void *)&P103_1426F4))
#undef P103_143724
#define P103_143724 (*(int32_t *)re_gvar(0x01143724u, sizeof(int32_t), (void *)&P103_143724))
#undef P103_144320
#define P103_144320 (*(int32_t *)re_gvar(0x01144320u, sizeof(int32_t), (void *)&P103_144320))
#undef P103_1443C0
#define P103_1443C0 (*(int32_t *)re_gvar(0x011443c0u, sizeof(int32_t), (void *)&P103_1443C0))
#undef P103_145A44
#define P103_145A44 (*(int32_t *)re_gvar(0x01145a44u, sizeof(int32_t), (void *)&P103_145A44))
#undef P103_DmgPct
#define P103_DmgPct (*(int32_t *)re_gvar(0x011373c8u, sizeof(int32_t), (void *)&P103_DmgPct))
#endif
/* gvar-img v2.03 end */
