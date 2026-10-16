/* v1.45 — восстановлено из Game.exe. 30 функций (все cdecl, проверено по ret в Game.exe): меню повтора 00416605 и
   выбора руля 00413e37 (таблицы меню .data 0054c810/0054d4a8../0054e0b0/0054e33c зарегистрированы в реестре re_ptr, данные —
   game/p100_data.h из tools/gen_p100_data.py), иерархия деталей 004f3c74/004f1325, обломки 004ab500 (метка __fastcall ложная:
   push ecx — место под локальную, аргументов нет), цели 004f556c, звуки машины 004d28a3, обороты 004d6740, запись/чтение
   ввода повтора 00518d32/00518f44, радар 00504479, прямоугольник дороги 0051acc5/0051aee6, высота дороги 004dd039/004dc91b,
   удар 0049ae98, формат LFB 004078d0, RIFF из ресурса 0048c43c (LockResource → plat_lock_resource), отсечение 0042eee6/0042d797,
   призрак 004e6f90, грань/пересечение коробок 00499951/00499fb0, свободная камера 004c3048, частица 004ba093, маркер 004c09e6,
   рекламные щиты 004feb59, маска зеркала 004f2c9a, трафик 00494701, значок ×2 в LFB 00407e2f. */
#pragma once
#include "gvar.h"
#include "reptr.h"
#include <stdint.h>

typedef uint32_t p100_u9_t[9];
typedef uint8_t  p100_c810_t[0x90];
typedef uint8_t  p100_d4a8_t[0x3e8];
typedef uint8_t  p100_e0b0_t[0x50];
typedef float    p100_f3_t[3];
typedef float    p100_partofs_t[32 * 4];
typedef uint8_t  p100_nodes_t[0x184];
typedef int16_t  p100_ang_t[3];
typedef float    p100_m16_t[16];
typedef float    p100_tri_t[0x100 * 12];
typedef int32_t  p100_i4_t[4];
typedef int32_t  p100_i5_t[5];
typedef uint32_t p100_u5_t[5];
typedef int32_t  p100_i7_t[7];
typedef uint8_t  p100_dim_t[0x16c * 0x20];
typedef uint32_t p100_pal_t[256];

/* меню (.data; в native — массивы из p100_data.h, зарегистрированы в k_regions game/reptr.c) */
#define P100_MenuC810  GAME_VAR(p100_c810_t, P100_MenuC810, 0x0054c810)  /* обработчики меню (шаг 0x10) */
#define P100_MenuD4A8  GAME_VAR(p100_d4a8_t, P100_MenuD4A8, 0x0054d4a8)  /* пункты/обработчики меню руля 0054d4a8..0054d890 */
#define P100_MenuE0B0  GAME_VAR(p100_e0b0_t, P100_MenuE0B0, 0x0054e0b0)  /* обработчики меню (шаг 0x10) */
#define P100_SpeedTab  GAME_VAR(p100_u9_t, P100_SpeedTab, 0x0054e33c)    /* скорости повтора: 3 строки × 3 */
#define P100_ItemN     GAME_VAR(int32_t, P100_ItemN, 0x0054e230)         /* .data = 1 */
#define P100_ItemTab   GAME_VAR(uint32_t, P100_ItemTab, 0x005fea48)      /* адрес таблицы пунктов (шаг 8), ставит 00417b80 */
#define P100_ItemSel   GAME_VAR(int32_t, P100_ItemSel, 0x005fe9f4)
#define P100_IconFfwd  GAME_VAR(uint8_t *, P100_IconFfwd, 0x005fe9fc)
#define P100_IconPlay  GAME_VAR(uint8_t *, P100_IconPlay, 0x005fea00)
#define P100_IconAccept GAME_VAR(uint8_t *, P100_IconAccept, 0x005fea04)
/* иерархия деталей */
#define P100_PartBase  GAME_VAR(p100_f3_t, P100_PartBase, 0x00c81b60)
#define P100_PartOfs   GAME_VAR(p100_partofs_t, P100_PartOfs, 0x00c81e20)   /* смещение узла: x, y, z, w */
#define P100_PartNodes GAME_VAR(p100_nodes_t, P100_PartNodes, 0x00c82020)   /* узлы по 8 байт: модель, число детей (0xff — лист), дети */
#define P100_PartModel GAME_VAR(int32_t, P100_PartModel, 0x00c821a4)
#define P100_PartMode  GAME_VAR(int32_t, P100_PartMode, 0x00c821a8)
#define P100_PartFlags GAME_VAR(int32_t, P100_PartFlags, 0x00c824e0)
#define P100_PartModelA GAME_VAR(int32_t, P100_PartModelA, 0x00c97a30)
#define P100_PartModelB GAME_VAR(int32_t, P100_PartModelB, 0x00ce1f40)
#define P100_PartRotA  GAME_VAR(int32_t, P100_PartRotA, 0x00d00254)
#define P100_PartRotB  GAME_VAR(int32_t, P100_PartRotB, 0x00c98ec4)
/* обломки */
#define P100_DebAng    GAME_VAR(p100_ang_t, P100_DebAng, 0x01123200)
#define P100_DebMat    GAME_VAR(p100_m16_t, P100_DebMat, 0x01105d20)
#define P100_DebTri    GAME_VAR(p100_tri_t, P100_DebTri, 0x011173e0)       /* 0x100 треугольников по 3 вектора (x, y, z, —) */
/* запись/чтение ввода повтора */
#define P100_RecBuf    GAME_VAR(uint8_t *, P100_RecBuf, 0x00b5a854)
#define P100_RecKeys   GAME_VAR(int32_t, P100_RecKeys, 0x00d1187c)
#define P100_RecPtr    GAME_VAR(p100_u5_t, P100_RecPtr, 0x00c4d720)        /* адреса буферов по игрокам */
#define P100_RecRep    GAME_VAR(p100_u5_t, P100_RecRep, 0x00c4d780)
#define P100_RecTot    GAME_VAR(p100_i5_t, P100_RecTot, 0x00c4d880)
#define P100_RecOff    GAME_VAR(p100_i5_t, P100_RecOff, 0x00c4d940)
#define P100_RecVal    GAME_VAR(p100_i5_t, P100_RecVal, 0x00c4da40)
#define P100_RecEnd    GAME_VAR(int32_t, P100_RecEnd, 0x00c4da54)
#define P100_RecCnt    GAME_VAR(p100_i5_t, P100_RecCnt, 0x00c55020)
#define P100_RecStop   GAME_VAR(uint8_t, P100_RecStop, 0x00b5a8ab)
#define P100_B87E24    GAME_VAR(int32_t, P100_B87E24, 0x00b87e24)
#define P100_1426FC    GAME_VAR(int32_t, P100_1426FC, 0x011426fc)
#define P100_143720    GAME_VAR(int32_t, P100_143720, 0x01143720)
/* радар */
#define P100_RadarX    GAME_VAR(int32_t, P100_RadarX, 0x00b32a28)
#define P100_RadarZ    GAME_VAR(int32_t, P100_RadarZ, 0x00b32a2c)
#define P100_Radar16   GAME_VAR(int32_t, P100_Radar16, 0x00bdfaa0)
#define P100_RadarIcon GAME_VAR(uint8_t *, P100_RadarIcon, 0x00c8088c)
/* дорога, машины */
#define P100_Rect      GAME_VAR(p100_i4_t, P100_Rect, 0x00c1cd00)
/* v1.47: записи моделей машин 0x16c (+4 — ширина), 00d0cdc4 = S_00D0CC60 + 0x164 — в native макрос над S_00D0CC60, без отдельной переменной */
#ifdef RE_HOOK_BUILD
#  define P100_CarDim  GAME_VAR(p100_dim_t, P100_CarDim, 0x00d0cdc4)
#else
#pragma push_macro("S_00D0CC60") /*gvi*/
#undef S_00D0CC60 /*gvi*/
extern uint8_t S_00D0CC60[];
#pragma pop_macro("S_00D0CC60") /*gvi*/
#  define P100_CarDim  (*(p100_dim_t *)(S_00D0CC60 + 0x164))
#endif
/* LFB */
#define P100_PixFn     GAME_VAR(uint32_t, P100_PixFn, 0x0057b73c)          /* адрес функции пикселя (0040232e — 16 бит, иначе 00402306) */
#define P100_LfbFmt    GAME_VAR(p100_i7_t, P100_LfbFmt, 0x005c6744)        /* байты формата +0x14..+0x1a ответа LfbLock; [0] — бит на пиксель */
#define P100_LfbPitch  GAME_VAR(int32_t, P100_LfbPitch, 0x005c6764)
#define P100_Pal32     GAME_VAR(p100_pal_t, P100_Pal32, 0x012710c0)
/* отсечение */
#define P100_ClipN     GAME_VAR(int32_t, P100_ClipN, 0x0115a070)
#define P100_ClipOut   GAME_VAR(float *, P100_ClipOut, 0x0115a078)        /* вершины по 12 float */
#define P100_Mirror    GAME_VAR(uint8_t *, P100_Mirror, 0x00b31f00)        /* маска зеркала 0x100 × 0x80 */
#ifndef RE_HOOK_BUILD
#pragma push_macro("P100_MenuC810") /*gvi*/
#undef P100_MenuC810 /*gvi*/
#pragma push_macro("P100_MenuD4A8") /*gvi*/
#undef P100_MenuD4A8 /*gvi*/
#pragma push_macro("P100_MenuE0B0") /*gvi*/
#undef P100_MenuE0B0 /*gvi*/
#pragma push_macro("P100_SpeedTab") /*gvi*/
#undef P100_SpeedTab /*gvi*/
extern p100_c810_t P100_MenuC810; extern p100_d4a8_t P100_MenuD4A8; extern p100_e0b0_t P100_MenuE0B0; extern p100_u9_t P100_SpeedTab;
#pragma pop_macro("P100_SpeedTab") /*gvi*/
#pragma pop_macro("P100_MenuE0B0") /*gvi*/
#pragma pop_macro("P100_MenuD4A8") /*gvi*/
#pragma pop_macro("P100_MenuC810") /*gvi*/
#pragma push_macro("P100_ItemN") /*gvi*/
#undef P100_ItemN /*gvi*/
#pragma push_macro("P100_ItemSel") /*gvi*/
#undef P100_ItemSel /*gvi*/
#pragma push_macro("P100_ItemTab") /*gvi*/
#undef P100_ItemTab /*gvi*/
extern int32_t P100_ItemN, P100_ItemSel; extern uint32_t P100_ItemTab; extern uint8_t *P100_IconFfwd, *P100_IconPlay, *P100_IconAccept;
#pragma pop_macro("P100_ItemTab") /*gvi*/
#pragma pop_macro("P100_ItemSel") /*gvi*/
#pragma pop_macro("P100_ItemN") /*gvi*/
#pragma push_macro("P100_PartBase") /*gvi*/
#undef P100_PartBase /*gvi*/
#pragma push_macro("P100_PartOfs") /*gvi*/
#undef P100_PartOfs /*gvi*/
#pragma push_macro("P100_PartNodes") /*gvi*/
#undef P100_PartNodes /*gvi*/
extern p100_f3_t P100_PartBase; extern p100_partofs_t P100_PartOfs; extern p100_nodes_t P100_PartNodes;
#pragma pop_macro("P100_PartNodes") /*gvi*/
#pragma pop_macro("P100_PartOfs") /*gvi*/
#pragma pop_macro("P100_PartBase") /*gvi*/
#pragma push_macro("P100_PartModel") /*gvi*/
#undef P100_PartModel /*gvi*/
#pragma push_macro("P100_PartMode") /*gvi*/
#undef P100_PartMode /*gvi*/
#pragma push_macro("P100_PartFlags") /*gvi*/
#undef P100_PartFlags /*gvi*/
#pragma push_macro("P100_PartModelA") /*gvi*/
#undef P100_PartModelA /*gvi*/
#pragma push_macro("P100_PartModelB") /*gvi*/
#undef P100_PartModelB /*gvi*/
#pragma push_macro("P100_PartRotA") /*gvi*/
#undef P100_PartRotA /*gvi*/
#pragma push_macro("P100_PartRotB") /*gvi*/
#undef P100_PartRotB /*gvi*/
extern int32_t P100_PartModel, P100_PartMode, P100_PartFlags, P100_PartModelA, P100_PartModelB, P100_PartRotA, P100_PartRotB;
#pragma pop_macro("P100_PartRotB") /*gvi*/
#pragma pop_macro("P100_PartRotA") /*gvi*/
#pragma pop_macro("P100_PartModelB") /*gvi*/
#pragma pop_macro("P100_PartModelA") /*gvi*/
#pragma pop_macro("P100_PartFlags") /*gvi*/
#pragma pop_macro("P100_PartMode") /*gvi*/
#pragma pop_macro("P100_PartModel") /*gvi*/
#pragma push_macro("P100_DebAng") /*gvi*/
#undef P100_DebAng /*gvi*/
#pragma push_macro("P100_DebMat") /*gvi*/
#undef P100_DebMat /*gvi*/
#pragma push_macro("P100_DebTri") /*gvi*/
#undef P100_DebTri /*gvi*/
extern p100_ang_t P100_DebAng; extern p100_m16_t P100_DebMat; extern p100_tri_t P100_DebTri;
#pragma pop_macro("P100_DebTri") /*gvi*/
#pragma pop_macro("P100_DebMat") /*gvi*/
#pragma pop_macro("P100_DebAng") /*gvi*/
#pragma push_macro("P100_RecKeys") /*gvi*/
#undef P100_RecKeys /*gvi*/
#pragma push_macro("P100_RecPtr") /*gvi*/
#undef P100_RecPtr /*gvi*/
#pragma push_macro("P100_RecRep") /*gvi*/
#undef P100_RecRep /*gvi*/
extern uint8_t *P100_RecBuf; extern int32_t P100_RecKeys; extern p100_u5_t P100_RecPtr, P100_RecRep;
#pragma pop_macro("P100_RecRep") /*gvi*/
#pragma pop_macro("P100_RecPtr") /*gvi*/
#pragma pop_macro("P100_RecKeys") /*gvi*/
#pragma push_macro("P100_RecTot") /*gvi*/
#undef P100_RecTot /*gvi*/
#pragma push_macro("P100_RecOff") /*gvi*/
#undef P100_RecOff /*gvi*/
#pragma push_macro("P100_RecVal") /*gvi*/
#undef P100_RecVal /*gvi*/
#pragma push_macro("P100_RecCnt") /*gvi*/
#undef P100_RecCnt /*gvi*/
#pragma push_macro("P100_RecEnd") /*gvi*/
#undef P100_RecEnd /*gvi*/
#pragma push_macro("P100_B87E24") /*gvi*/
#undef P100_B87E24 /*gvi*/
#pragma push_macro("P100_1426FC") /*gvi*/
#undef P100_1426FC /*gvi*/
#pragma push_macro("P100_143720") /*gvi*/
#undef P100_143720 /*gvi*/
extern p100_i5_t P100_RecTot, P100_RecOff, P100_RecVal, P100_RecCnt; extern int32_t P100_RecEnd, P100_B87E24, P100_1426FC, P100_143720;
#pragma pop_macro("P100_143720") /*gvi*/
#pragma pop_macro("P100_1426FC") /*gvi*/
#pragma pop_macro("P100_B87E24") /*gvi*/
#pragma pop_macro("P100_RecEnd") /*gvi*/
#pragma pop_macro("P100_RecCnt") /*gvi*/
#pragma pop_macro("P100_RecVal") /*gvi*/
#pragma pop_macro("P100_RecOff") /*gvi*/
#pragma pop_macro("P100_RecTot") /*gvi*/
#pragma push_macro("P100_RecStop") /*gvi*/
#undef P100_RecStop /*gvi*/
extern uint8_t P100_RecStop;
#pragma pop_macro("P100_RecStop") /*gvi*/
#pragma push_macro("P100_RadarX") /*gvi*/
#undef P100_RadarX /*gvi*/
#pragma push_macro("P100_RadarZ") /*gvi*/
#undef P100_RadarZ /*gvi*/
#pragma push_macro("P100_Radar16") /*gvi*/
#undef P100_Radar16 /*gvi*/
extern int32_t P100_RadarX, P100_RadarZ, P100_Radar16; extern uint8_t *P100_RadarIcon;
#pragma pop_macro("P100_Radar16") /*gvi*/
#pragma pop_macro("P100_RadarZ") /*gvi*/
#pragma pop_macro("P100_RadarX") /*gvi*/
#pragma push_macro("P100_Rect") /*gvi*/
#undef P100_Rect /*gvi*/
extern p100_i4_t P100_Rect;
#pragma pop_macro("P100_Rect") /*gvi*/
#pragma push_macro("P100_PixFn") /*gvi*/
#undef P100_PixFn /*gvi*/
#pragma push_macro("P100_LfbFmt") /*gvi*/
#undef P100_LfbFmt /*gvi*/
#pragma push_macro("P100_LfbPitch") /*gvi*/
#undef P100_LfbPitch /*gvi*/
#pragma push_macro("P100_Pal32") /*gvi*/
#undef P100_Pal32 /*gvi*/
extern uint32_t P100_PixFn; extern p100_i7_t P100_LfbFmt; extern int32_t P100_LfbPitch; extern p100_pal_t P100_Pal32;
#pragma pop_macro("P100_Pal32") /*gvi*/
#pragma pop_macro("P100_LfbPitch") /*gvi*/
#pragma pop_macro("P100_LfbFmt") /*gvi*/
#pragma pop_macro("P100_PixFn") /*gvi*/
#pragma push_macro("P100_ClipN") /*gvi*/
#undef P100_ClipN /*gvi*/
extern int32_t P100_ClipN; extern float *P100_ClipOut; extern uint8_t *P100_Mirror;
#pragma pop_macro("P100_ClipN") /*gvi*/
#endif

void    P100_ReplayMenuInit(void);                                               /* 00416605 */
void    P100_PadMenuInit(void);                                                  /* 00413e37 */
void    P100_DrawParts(uint8_t *obj, const float *quats, const uint8_t *node, const float *q, const float *pos);  /* 004f3c74 */
void    P100_DrawPartsB(const float *quats, const uint8_t *node, const float *q, const float *pos);             /* 004f1325 */
void    P100_DebrisInit(void);                                                   /* 004ab500 */
void    P100_GoalsCheck(uint8_t *goal);                                          /* 004f556c */
void    P100_CarSounds(uint8_t *tab);                                            /* 004d28a3 */
void    P100_CarRevs(int32_t car);                                               /* 004d6740 */
void    P100_RecInput(int32_t pad);                                              /* 00518d32 */
int32_t P100_RecRead(int32_t pad);                                               /* 00518f44 (метка __thiscall ложная: ecx не используется) */
void    P100_RadarMap(int32_t force);                                            /* 00504479 */
int32_t P100_RoadRect(int32_t node, int32_t side);                               /* 0051acc5 */
void    P100_RoadRectAbs(int32_t node, int32_t side);                            /* 0051aee6 */
int32_t P100_RoadHeight(const int32_t *pos);                                     /* 004dd039 */
int32_t P100_RoadHeightF(const float *pos);                                      /* 004dc91b */
void    P100_CarHit(uint8_t *car, const int32_t *a, const int32_t *b, int32_t force);  /* 0049ae98 */
int32_t P100_LfbFormat(void);                                                    /* 004078d0 */
int32_t P100_RiffFromRes(void *res, const void **fmt, const void **data, uint32_t *size);  /* 0048c43c */
void    P100_ClipFar(const uint8_t *a, const uint8_t *b);                        /* 0042eee6 */
void    P100_ClipNear(const uint8_t *a, const uint8_t *b, float ua, float ub);   /* 0042d797 */
void    P100_GhostNear(void);                                                    /* 004e6f90 */
void    P100_BoxFace(const int32_t *a, const int32_t *b, int32_t k, int32_t *best, int32_t sgn);  /* 00499951 */
int32_t P100_BoxOverlap(int32_t *p);                                             /* 00499fb0 */
void    P100_FreeCamKeys(uint32_t keys);                                         /* 004c3048 */
void    P100_PartStep(float *p);                                                 /* 004ba093 */
void    P100_MarkerSpawn(int32_t k);                                             /* 004c09e6 */
void    P100_Billboards(int32_t on);                                             /* 004feb59 */
void    P100_MirrorMask(void);                                                   /* 004f2c9a */
void    P100_TrafficSlot(uint8_t *car);                                          /* 00494701 */
void    P100_IconLfb2x(uint8_t *dst, int32_t x, uint32_t y, const char *name);   /* 00407e2f */
/* gvar-img v2.03 begin (tools/gen_gvar_img.py) */
#if !defined(RE_HOOK_BUILD) && !defined(RE_GVAR_PLAIN)
#undef P100_MenuC810
#define P100_MenuC810 (*(p100_c810_t *)re_gvar(0x0054c810u, sizeof(p100_c810_t), (void *)&P100_MenuC810))
#undef P100_MenuD4A8
#define P100_MenuD4A8 (*(p100_d4a8_t *)re_gvar(0x0054d4a8u, sizeof(p100_d4a8_t), (void *)&P100_MenuD4A8))
#undef P100_MenuE0B0
#define P100_MenuE0B0 (*(p100_e0b0_t *)re_gvar(0x0054e0b0u, sizeof(p100_e0b0_t), (void *)&P100_MenuE0B0))
#undef P100_SpeedTab
#define P100_SpeedTab (*(p100_u9_t *)re_gvar(0x0054e33cu, sizeof(p100_u9_t), (void *)&P100_SpeedTab))
#undef P100_ItemN
#define P100_ItemN (*(int32_t *)re_gvar(0x0054e230u, sizeof(int32_t), (void *)&P100_ItemN))
#undef P100_ItemTab
#define P100_ItemTab (*(uint32_t *)re_gvar(0x005fea48u, sizeof(uint32_t), (void *)&P100_ItemTab))
#undef P100_ItemSel
#define P100_ItemSel (*(int32_t *)re_gvar(0x005fe9f4u, sizeof(int32_t), (void *)&P100_ItemSel))
#undef P100_PartBase
#define P100_PartBase (*(p100_f3_t *)re_gvar(0x00c81b60u, sizeof(p100_f3_t), (void *)&P100_PartBase))
#undef P100_PartOfs
#define P100_PartOfs (*(p100_partofs_t *)re_gvar(0x00c81e20u, sizeof(p100_partofs_t), (void *)&P100_PartOfs))
#undef P100_PartNodes
#define P100_PartNodes (*(p100_nodes_t *)re_gvar(0x00c82020u, sizeof(p100_nodes_t), (void *)&P100_PartNodes))
#undef P100_PartModel
#define P100_PartModel (*(int32_t *)re_gvar(0x00c821a4u, sizeof(int32_t), (void *)&P100_PartModel))
#undef P100_PartMode
#define P100_PartMode (*(int32_t *)re_gvar(0x00c821a8u, sizeof(int32_t), (void *)&P100_PartMode))
#undef P100_PartFlags
#define P100_PartFlags (*(int32_t *)re_gvar(0x00c824e0u, sizeof(int32_t), (void *)&P100_PartFlags))
#undef P100_PartModelA
#define P100_PartModelA (*(int32_t *)re_gvar(0x00c97a30u, sizeof(int32_t), (void *)&P100_PartModelA))
#undef P100_PartModelB
#define P100_PartModelB (*(int32_t *)re_gvar(0x00ce1f40u, sizeof(int32_t), (void *)&P100_PartModelB))
#undef P100_PartRotA
#define P100_PartRotA (*(int32_t *)re_gvar(0x00d00254u, sizeof(int32_t), (void *)&P100_PartRotA))
#undef P100_PartRotB
#define P100_PartRotB (*(int32_t *)re_gvar(0x00c98ec4u, sizeof(int32_t), (void *)&P100_PartRotB))
#undef P100_DebAng
#define P100_DebAng (*(p100_ang_t *)re_gvar(0x01123200u, sizeof(p100_ang_t), (void *)&P100_DebAng))
#undef P100_DebMat
#define P100_DebMat (*(p100_m16_t *)re_gvar(0x01105d20u, sizeof(p100_m16_t), (void *)&P100_DebMat))
#undef P100_DebTri
#define P100_DebTri (*(p100_tri_t *)re_gvar(0x011173e0u, sizeof(p100_tri_t), (void *)&P100_DebTri))
#undef P100_RecKeys
#define P100_RecKeys (*(int32_t *)re_gvar(0x00d1187cu, sizeof(int32_t), (void *)&P100_RecKeys))
#undef P100_RecPtr
#define P100_RecPtr (*(p100_u5_t *)re_gvar(0x00c4d720u, sizeof(p100_u5_t), (void *)&P100_RecPtr))
#undef P100_RecRep
#define P100_RecRep (*(p100_u5_t *)re_gvar(0x00c4d780u, sizeof(p100_u5_t), (void *)&P100_RecRep))
#undef P100_RecTot
#define P100_RecTot (*(p100_i5_t *)re_gvar(0x00c4d880u, sizeof(p100_i5_t), (void *)&P100_RecTot))
#undef P100_RecOff
#define P100_RecOff (*(p100_i5_t *)re_gvar(0x00c4d940u, sizeof(p100_i5_t), (void *)&P100_RecOff))
#undef P100_RecVal
#define P100_RecVal (*(p100_i5_t *)re_gvar(0x00c4da40u, sizeof(p100_i5_t), (void *)&P100_RecVal))
#undef P100_RecEnd
#define P100_RecEnd (*(int32_t *)re_gvar(0x00c4da54u, sizeof(int32_t), (void *)&P100_RecEnd))
#undef P100_RecCnt
#define P100_RecCnt (*(p100_i5_t *)re_gvar(0x00c55020u, sizeof(p100_i5_t), (void *)&P100_RecCnt))
#undef P100_RecStop
#define P100_RecStop (*(uint8_t *)re_gvar(0x00b5a8abu, sizeof(uint8_t), (void *)&P100_RecStop))
#undef P100_B87E24
#define P100_B87E24 (*(int32_t *)re_gvar(0x00b87e24u, sizeof(int32_t), (void *)&P100_B87E24))
#undef P100_1426FC
#define P100_1426FC (*(int32_t *)re_gvar(0x011426fcu, sizeof(int32_t), (void *)&P100_1426FC))
#undef P100_143720
#define P100_143720 (*(int32_t *)re_gvar(0x01143720u, sizeof(int32_t), (void *)&P100_143720))
#undef P100_RadarX
#define P100_RadarX (*(int32_t *)re_gvar(0x00b32a28u, sizeof(int32_t), (void *)&P100_RadarX))
#undef P100_RadarZ
#define P100_RadarZ (*(int32_t *)re_gvar(0x00b32a2cu, sizeof(int32_t), (void *)&P100_RadarZ))
#undef P100_Radar16
#define P100_Radar16 (*(int32_t *)re_gvar(0x00bdfaa0u, sizeof(int32_t), (void *)&P100_Radar16))
#undef P100_Rect
#define P100_Rect (*(p100_i4_t *)re_gvar(0x00c1cd00u, sizeof(p100_i4_t), (void *)&P100_Rect))
#undef P100_PixFn
#define P100_PixFn (*(uint32_t *)re_gvar(0x0057b73cu, sizeof(uint32_t), (void *)&P100_PixFn))
#undef P100_LfbFmt
#define P100_LfbFmt (*(p100_i7_t *)re_gvar(0x005c6744u, sizeof(p100_i7_t), (void *)&P100_LfbFmt))
#undef P100_LfbPitch
#define P100_LfbPitch (*(int32_t *)re_gvar(0x005c6764u, sizeof(int32_t), (void *)&P100_LfbPitch))
#undef P100_Pal32
#define P100_Pal32 (*(p100_pal_t *)re_gvar(0x012710c0u, sizeof(p100_pal_t), (void *)&P100_Pal32))
#undef P100_ClipN
#define P100_ClipN (*(int32_t *)re_gvar(0x0115a070u, sizeof(int32_t), (void *)&P100_ClipN))
#endif
/* gvar-img v2.03 end */
