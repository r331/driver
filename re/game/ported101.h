/* v1.46 — восстановлено из Game.exe. Все функции cdecl (ret без операнда проверен по Game.exe; у 004f51b4/005139d7/0051500c/
   0051b974 ret — после таблиц переходов; у 00528bb7/00528c91/00528d17/005291ed/00529253/005292d1 — ручной ассемблер, сохраняет
   все регистры, но все вызывающие — код MSVC (через thunk или указатель 0057b73c), так что cdecl-замена безопасна).
   Цели скрипта 004f51b4, обломки 004b998b/004b9aec, начало воспроизведения 00518953, капли 00522d02, машина на земле 004dea35,
   соседняя клетка частицы 005139d7/0051500c/00513d0a, пересечение коробок 004997a0, границы дорог 0051c07a, звуки трафика
   004d63bc, объекты B/C 004b0256/004af076/004aecb1, колёса на земле 0051d97e, небо 004ef3cd, узел дороги 0051b974, маска зеркала
   004f29f7, проекции вершины 00528bb7/00528c91/00528d17, заливка/палитровый вывод LFB 005291ed/00529253/005292d1. */
#pragma once
#include "gvar.h"
#include "reptr.h"
#include "cartab.h"
#include <stdint.h>

typedef float    p101_f3_t[3];
typedef uint32_t p101_hud_t[12];
typedef uint8_t  p101_b148_t[0x148];
typedef uint8_t  p101_b34_t[0x34];
typedef uint8_t  p101_drops_t[6 * 0x1c];
typedef int16_t  p101_nbr_t[4];
typedef uint8_t  p101_b16_t[16];
typedef uint8_t  p101_b66_t[66];
typedef uint32_t p101_pal_t[256];

/* цели скрипта */
#define P101_Hud       GAME_VAR(p101_hud_t, P101_Hud, 0x00c808c0)       /* полоса HUD (P16_FillHudRect): [4] — значение (float, = P12_00c808d0), [5] — предел, [11] — видна */
#define P101_HudVal    GAME_VAR(int32_t, P101_HudVal, 0x00c810a0)
#define P101_GoalPos   GAME_VAR(p101_f3_t, P101_GoalPos, 0x00c80f50)
/* воспроизведение: снимки записей */
#define P101_SaveCar   GAME_VAR(p101_b148_t, P101_SaveCar, 0x00c54b60)
#define P101_SaveCar2  GAME_VAR(p101_b148_t, P101_SaveCar2, 0x00c54d20)
#define P101_SaveA     GAME_VAR(p101_b34_t, P101_SaveA, 0x00c4d8a0)
#define P101_SaveA2    GAME_VAR(p101_b34_t, P101_SaveA2, 0x00c4da60)
#define P101_SaveB     GAME_VAR(p101_b34_t, P101_SaveB, 0x00c4d800)
#define P101_SaveB2    GAME_VAR(p101_b34_t, P101_SaveB2, 0x00c4da00)
#define P101_SaveC     GAME_VAR(p101_b34_t, P101_SaveC, 0x00c4d840)
#define P101_SaveC2    GAME_VAR(p101_b34_t, P101_SaveC2, 0x00c4d9c0)
#define P101_LiveA     GAME_VAR(p101_b34_t, P101_LiveA, 0x00d07754)
#define P101_LiveB     GAME_VAR(p101_b34_t, P101_LiveB, 0x00d0eb34)
#define P101_LiveC     GAME_VAR(p101_b34_t, P101_LiveC, 0x00d0f8b4)
#define P101_RecState  GAME_VAR(int32_t, P101_RecState, 0x00c4d700)
#define P101_RecFrame  GAME_VAR(int32_t, P101_RecFrame, 0x00c4d704)
#define P101_RecFrame2 GAME_VAR(int32_t, P101_RecFrame2, 0x00c4d708)
#define P101_RecSaved  GAME_VAR(int32_t, P101_RecSaved, 0x00c4da94)
/* капли (6 записей 0x1c; +0x18 — адрес объекта) */
#define P101_Drops     GAME_VAR(p101_drops_t, P101_Drops, 0x00bde680)
/* соседи клетки частицы (-0x8000 — свободно): da2, da4, da6, da8 */
#define P101_Nbr       GAME_VAR(p101_nbr_t, P101_Nbr, 0x00c55da2)
/* узел дороги (0051b974) */
#define P101_RdNode    GAME_VAR(uint16_t, P101_RdNode, 0x00c1cca0)
#define P101_RdCell    GAME_VAR(uint16_t, P101_RdCell, 0x00c1cca2)
#define P101_RdLane    GAME_VAR(int16_t, P101_RdLane, 0x00c1cca4)
#define P101_RdB2      GAME_VAR(uint8_t, P101_RdB2, 0x00c1ccb2)
#define P101_RdDist    GAME_VAR(int32_t, P101_RdDist, 0x00c1ccb4)
#define P101_RdLeft    GAME_VAR(int32_t, P101_RdLeft, 0x00c1ccb8)
/* объекты B/C */
#define P101_ObjBOn2   GAME_VAR(int32_t, P101_ObjBOn2, 0x0111a3e0)
#define P101_CarFx     GAME_VAR(p101_b66_t, P101_CarFx, 0x010fb1c0)     /* байт на машину */
#define P101_FxCol     GAME_VAR(p101_b16_t, P101_FxCol, 0x005537c8)     /* .data */
/* проекции вершины */
#define P101_ScrX0     GAME_VAR(float, P101_ScrX0, 0x0124b6d0)
#define P101_ScrY0     GAME_VAR(float, P101_ScrY0, 0x01252b70)
#define P101_TmpY      GAME_VAR(float, P101_TmpY, 0x0057a112)
/* палитра вывода LFB (16/32 бит на индекс) */
#define P101_PalLfb    GAME_VAR(p101_pal_t, P101_PalLfb, 0x01271a80)
#ifndef RE_HOOK_BUILD
#pragma push_macro("P101_Hud") /*gvi*/
#undef P101_Hud /*gvi*/
#pragma push_macro("P101_HudVal") /*gvi*/
#undef P101_HudVal /*gvi*/
#pragma push_macro("P101_GoalPos") /*gvi*/
#undef P101_GoalPos /*gvi*/
extern p101_hud_t P101_Hud; extern int32_t P101_HudVal; extern p101_f3_t P101_GoalPos;
#pragma pop_macro("P101_GoalPos") /*gvi*/
#pragma pop_macro("P101_HudVal") /*gvi*/
#pragma pop_macro("P101_Hud") /*gvi*/
#pragma push_macro("P101_SaveCar") /*gvi*/
#undef P101_SaveCar /*gvi*/
#pragma push_macro("P101_SaveCar2") /*gvi*/
#undef P101_SaveCar2 /*gvi*/
#pragma push_macro("P101_SaveA") /*gvi*/
#undef P101_SaveA /*gvi*/
#pragma push_macro("P101_SaveA2") /*gvi*/
#undef P101_SaveA2 /*gvi*/
#pragma push_macro("P101_SaveB") /*gvi*/
#undef P101_SaveB /*gvi*/
#pragma push_macro("P101_SaveB2") /*gvi*/
#undef P101_SaveB2 /*gvi*/
#pragma push_macro("P101_SaveC") /*gvi*/
#undef P101_SaveC /*gvi*/
#pragma push_macro("P101_SaveC2") /*gvi*/
#undef P101_SaveC2 /*gvi*/
extern p101_b148_t P101_SaveCar, P101_SaveCar2; extern p101_b34_t P101_SaveA, P101_SaveA2, P101_SaveB, P101_SaveB2, P101_SaveC, P101_SaveC2;
#pragma pop_macro("P101_SaveC2") /*gvi*/
#pragma pop_macro("P101_SaveC") /*gvi*/
#pragma pop_macro("P101_SaveB2") /*gvi*/
#pragma pop_macro("P101_SaveB") /*gvi*/
#pragma pop_macro("P101_SaveA2") /*gvi*/
#pragma pop_macro("P101_SaveA") /*gvi*/
#pragma pop_macro("P101_SaveCar2") /*gvi*/
#pragma pop_macro("P101_SaveCar") /*gvi*/
#pragma push_macro("P101_LiveA") /*gvi*/
#undef P101_LiveA /*gvi*/
#pragma push_macro("P101_LiveB") /*gvi*/
#undef P101_LiveB /*gvi*/
#pragma push_macro("P101_LiveC") /*gvi*/
#undef P101_LiveC /*gvi*/
#pragma push_macro("P101_RecState") /*gvi*/
#undef P101_RecState /*gvi*/
#pragma push_macro("P101_RecFrame") /*gvi*/
#undef P101_RecFrame /*gvi*/
#pragma push_macro("P101_RecFrame2") /*gvi*/
#undef P101_RecFrame2 /*gvi*/
#pragma push_macro("P101_RecSaved") /*gvi*/
#undef P101_RecSaved /*gvi*/
extern p101_b34_t P101_LiveA, P101_LiveB, P101_LiveC; extern int32_t P101_RecState, P101_RecFrame, P101_RecFrame2, P101_RecSaved;
#pragma pop_macro("P101_RecSaved") /*gvi*/
#pragma pop_macro("P101_RecFrame2") /*gvi*/
#pragma pop_macro("P101_RecFrame") /*gvi*/
#pragma pop_macro("P101_RecState") /*gvi*/
#pragma pop_macro("P101_LiveC") /*gvi*/
#pragma pop_macro("P101_LiveB") /*gvi*/
#pragma pop_macro("P101_LiveA") /*gvi*/
#pragma push_macro("P101_Drops") /*gvi*/
#undef P101_Drops /*gvi*/
#pragma push_macro("P101_Nbr") /*gvi*/
#undef P101_Nbr /*gvi*/
extern p101_drops_t P101_Drops; extern p101_nbr_t P101_Nbr;
#pragma pop_macro("P101_Nbr") /*gvi*/
#pragma pop_macro("P101_Drops") /*gvi*/
#pragma push_macro("P101_RdNode") /*gvi*/
#undef P101_RdNode /*gvi*/
#pragma push_macro("P101_RdCell") /*gvi*/
#undef P101_RdCell /*gvi*/
#pragma push_macro("P101_RdLane") /*gvi*/
#undef P101_RdLane /*gvi*/
#pragma push_macro("P101_RdB2") /*gvi*/
#undef P101_RdB2 /*gvi*/
#pragma push_macro("P101_RdDist") /*gvi*/
#undef P101_RdDist /*gvi*/
#pragma push_macro("P101_RdLeft") /*gvi*/
#undef P101_RdLeft /*gvi*/
extern uint16_t P101_RdNode, P101_RdCell; extern int16_t P101_RdLane; extern uint8_t P101_RdB2; extern int32_t P101_RdDist, P101_RdLeft;
#pragma pop_macro("P101_RdLeft") /*gvi*/
#pragma pop_macro("P101_RdDist") /*gvi*/
#pragma pop_macro("P101_RdB2") /*gvi*/
#pragma pop_macro("P101_RdLane") /*gvi*/
#pragma pop_macro("P101_RdCell") /*gvi*/
#pragma pop_macro("P101_RdNode") /*gvi*/
#pragma push_macro("P101_ObjBOn2") /*gvi*/
#undef P101_ObjBOn2 /*gvi*/
#pragma push_macro("P101_CarFx") /*gvi*/
#undef P101_CarFx /*gvi*/
#pragma push_macro("P101_FxCol") /*gvi*/
#undef P101_FxCol /*gvi*/
extern int32_t P101_ObjBOn2; extern p101_b66_t P101_CarFx; extern p101_b16_t P101_FxCol;
#pragma pop_macro("P101_FxCol") /*gvi*/
#pragma pop_macro("P101_CarFx") /*gvi*/
#pragma pop_macro("P101_ObjBOn2") /*gvi*/
#pragma push_macro("P101_ScrX0") /*gvi*/
#undef P101_ScrX0 /*gvi*/
#pragma push_macro("P101_ScrY0") /*gvi*/
#undef P101_ScrY0 /*gvi*/
#pragma push_macro("P101_TmpY") /*gvi*/
#undef P101_TmpY /*gvi*/
#pragma push_macro("P101_PalLfb") /*gvi*/
#undef P101_PalLfb /*gvi*/
extern float P101_ScrX0, P101_ScrY0, P101_TmpY; extern p101_pal_t P101_PalLfb;
#pragma pop_macro("P101_PalLfb") /*gvi*/
#pragma pop_macro("P101_TmpY") /*gvi*/
#pragma pop_macro("P101_ScrY0") /*gvi*/
#pragma pop_macro("P101_ScrX0") /*gvi*/
#endif

void    P101_GoalTick(uint8_t *goal);                                         /* 004f51b4 */
void    P101_DebrisBounce(int32_t *p);                                        /* 004b998b */
void    P101_ReplayBegin(int32_t keep);                                       /* 00518953 */
void    P101_Drips(void);                                                     /* 00522d02 */
void    P101_CarGround(p99_car_t *car, uint8_t *out);                         /* 004dea35 */
uint32_t P101_PickCell(uint32_t want, int32_t x, int32_t z, float *out);       /* 005139d7 */
int32_t P101_BoxHit(int32_t *a, int32_t *b, int32_t *best);                   /* 004997a0 */
void    P101_RoadBounds(void);                                                /* 0051c07a */
void    P101_PartFall(uint8_t *p);                                            /* 00513d0a */
void    P101_PartTurn(uint8_t *p);                                            /* 0051500c */
void    P101_TrafficSounds(void);                                             /* 004d63bc */
void    P101_AddObjB(const uint8_t *src, float x, float y, float z, int16_t kind, int16_t b, int16_t val);  /* 004b0256 */
void    P101_CarLight(int32_t car, const float *v, int32_t flags);            /* 004af076 */
void    P101_DebrisFly(void);                                                 /* 004b9aec */
void    P101_WheelsGround(const uint8_t *car, float *out);                    /* 0051d97e */
void    P101_SkyInit(void);                                                   /* 004ef3cd */
#ifndef RE_HOOK_BUILD
void    P101_SkyUvFix(void);    /* v2.27: v колец купола неба у четвертей — к медиане (шов неба) */
extern int32_t P101_SkyUvFixed;
#endif
int32_t P101_RoadNode(int32_t x, int32_t z, int8_t side);                     /* 0051b974 */
void    P101_MirrorMaskR(float r);                                            /* 004f29f7 */
void    P101_CarSkids(int32_t car);                                           /* 004aecb1 */
void    P101_ProjT(float *v);                                                 /* 00528bb7 */
void    P101_XformBias2(float *v);                                            /* 00528c91 */
void    P101_Proj(float *v);                                                  /* 00528d17 */
void    P101_Pal16(const uint8_t *src, uint8_t *dst, int32_t unused, int32_t rows);  /* 00529253 */
void    P101_Pal32(const uint8_t *src, uint8_t *dst, int32_t unused, int32_t rows);  /* 005292d1 */
void    P101_ClipNearUV(const uint8_t *a, const uint8_t *b, float ua0, float ua1, float ub0, float ub1);   /* 0042da16 */
void    P101_ClipFarUV(const uint8_t *a, const uint8_t *b, float ua0, float ua1, float ub0, float ub1);    /* 0042f124 */
void    P101_ClipNearUVW(const uint8_t *a, const uint8_t *b, float ua0, float ua1, float ua2, float ub0, float ub1, float ub2);  /* 0042dce8 */
void    P101_ClipNearRGB(const uint8_t *a, const uint8_t *b, float ua0, float ua1, float ua2, float ub0, float ub1, float ub2);  /* 0042e3c7 */
void    P101_ClipNear5A(const uint8_t *a, const uint8_t *b, float ua0, float ua1, float ua2, float ua3, float ua4,
                        float ub0, float ub1, float ub2, float ub3, float ub4);   /* 0042e007 */
void    P101_ClipNear5B(const uint8_t *a, const uint8_t *b, float ua0, float ua1, float ua2, float ua3, float ua4,
                        float ub0, float ub1, float ub2, float ub3, float ub4);   /* 0042e6e6 */
/* gvar-img v2.03 begin (tools/gen_gvar_img.py) */
#if !defined(RE_HOOK_BUILD) && !defined(RE_GVAR_PLAIN)
#undef P101_Hud
#define P101_Hud (*(p101_hud_t *)re_gvar(0x00c808c0u, sizeof(p101_hud_t), (void *)&P101_Hud))
#undef P101_HudVal
#define P101_HudVal (*(int32_t *)re_gvar(0x00c810a0u, sizeof(int32_t), (void *)&P101_HudVal))
#undef P101_GoalPos
#define P101_GoalPos (*(p101_f3_t *)re_gvar(0x00c80f50u, sizeof(p101_f3_t), (void *)&P101_GoalPos))
#undef P101_SaveCar
#define P101_SaveCar (*(p101_b148_t *)re_gvar(0x00c54b60u, sizeof(p101_b148_t), (void *)&P101_SaveCar))
#undef P101_SaveCar2
#define P101_SaveCar2 (*(p101_b148_t *)re_gvar(0x00c54d20u, sizeof(p101_b148_t), (void *)&P101_SaveCar2))
#undef P101_SaveA
#define P101_SaveA (*(p101_b34_t *)re_gvar(0x00c4d8a0u, sizeof(p101_b34_t), (void *)&P101_SaveA))
#undef P101_SaveA2
#define P101_SaveA2 (*(p101_b34_t *)re_gvar(0x00c4da60u, sizeof(p101_b34_t), (void *)&P101_SaveA2))
#undef P101_SaveB
#define P101_SaveB (*(p101_b34_t *)re_gvar(0x00c4d800u, sizeof(p101_b34_t), (void *)&P101_SaveB))
#undef P101_SaveB2
#define P101_SaveB2 (*(p101_b34_t *)re_gvar(0x00c4da00u, sizeof(p101_b34_t), (void *)&P101_SaveB2))
#undef P101_SaveC
#define P101_SaveC (*(p101_b34_t *)re_gvar(0x00c4d840u, sizeof(p101_b34_t), (void *)&P101_SaveC))
#undef P101_SaveC2
#define P101_SaveC2 (*(p101_b34_t *)re_gvar(0x00c4d9c0u, sizeof(p101_b34_t), (void *)&P101_SaveC2))
#undef P101_LiveA
#define P101_LiveA (*(p101_b34_t *)re_gvar(0x00d07754u, sizeof(p101_b34_t), (void *)&P101_LiveA))
#undef P101_LiveB
#define P101_LiveB (*(p101_b34_t *)re_gvar(0x00d0eb34u, sizeof(p101_b34_t), (void *)&P101_LiveB))
#undef P101_LiveC
#define P101_LiveC (*(p101_b34_t *)re_gvar(0x00d0f8b4u, sizeof(p101_b34_t), (void *)&P101_LiveC))
#undef P101_RecState
#define P101_RecState (*(int32_t *)re_gvar(0x00c4d700u, sizeof(int32_t), (void *)&P101_RecState))
#undef P101_RecFrame
#define P101_RecFrame (*(int32_t *)re_gvar(0x00c4d704u, sizeof(int32_t), (void *)&P101_RecFrame))
#undef P101_RecFrame2
#define P101_RecFrame2 (*(int32_t *)re_gvar(0x00c4d708u, sizeof(int32_t), (void *)&P101_RecFrame2))
#undef P101_RecSaved
#define P101_RecSaved (*(int32_t *)re_gvar(0x00c4da94u, sizeof(int32_t), (void *)&P101_RecSaved))
#undef P101_Drops
#define P101_Drops (*(p101_drops_t *)re_gvar(0x00bde680u, sizeof(p101_drops_t), (void *)&P101_Drops))
#undef P101_Nbr
#define P101_Nbr (*(p101_nbr_t *)re_gvar(0x00c55da2u, sizeof(p101_nbr_t), (void *)&P101_Nbr))
#undef P101_RdNode
#define P101_RdNode (*(uint16_t *)re_gvar(0x00c1cca0u, sizeof(uint16_t), (void *)&P101_RdNode))
#undef P101_RdCell
#define P101_RdCell (*(uint16_t *)re_gvar(0x00c1cca2u, sizeof(uint16_t), (void *)&P101_RdCell))
#undef P101_RdLane
#define P101_RdLane (*(int16_t *)re_gvar(0x00c1cca4u, sizeof(int16_t), (void *)&P101_RdLane))
#undef P101_RdB2
#define P101_RdB2 (*(uint8_t *)re_gvar(0x00c1ccb2u, sizeof(uint8_t), (void *)&P101_RdB2))
#undef P101_RdDist
#define P101_RdDist (*(int32_t *)re_gvar(0x00c1ccb4u, sizeof(int32_t), (void *)&P101_RdDist))
#undef P101_RdLeft
#define P101_RdLeft (*(int32_t *)re_gvar(0x00c1ccb8u, sizeof(int32_t), (void *)&P101_RdLeft))
#undef P101_ObjBOn2
#define P101_ObjBOn2 (*(int32_t *)re_gvar(0x0111a3e0u, sizeof(int32_t), (void *)&P101_ObjBOn2))
#undef P101_CarFx
#define P101_CarFx (*(p101_b66_t *)re_gvar(0x010fb1c0u, sizeof(p101_b66_t), (void *)&P101_CarFx))
#undef P101_FxCol
#define P101_FxCol (*(p101_b16_t *)re_gvar(0x005537c8u, sizeof(p101_b16_t), (void *)&P101_FxCol))
#undef P101_ScrX0
#define P101_ScrX0 (*(float *)re_gvar(0x0124b6d0u, sizeof(float), (void *)&P101_ScrX0))
#undef P101_ScrY0
#define P101_ScrY0 (*(float *)re_gvar(0x01252b70u, sizeof(float), (void *)&P101_ScrY0))
#undef P101_TmpY
#define P101_TmpY (*(float *)re_gvar(0x0057a112u, sizeof(float), (void *)&P101_TmpY))
#undef P101_PalLfb
#define P101_PalLfb (*(p101_pal_t *)re_gvar(0x01271a80u, sizeof(p101_pal_t), (void *)&P101_PalLfb))
#endif
/* gvar-img v2.03 end */
