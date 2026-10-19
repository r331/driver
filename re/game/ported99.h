/* v1.44 — восстановлено из Game.exe. Таблица игроков/машин 00d077c0 (шаг 0x148, game/cartab.h: P99_Cars, 00d07888 = поле +0xc8
   записи 0) и функции на ней: радар 00506a07, коробка передач 004d6ae7, проверки камер режиссёра 004c3427/004c5e08, копы 004d2b5d,
   дорога под машиной 0051b7a3, свободная камера 0049c99c, камера за игроком 0049e47b, сброс маркера 004e9427, машина трафика
   впереди 004a1b2d, цель копа 004a6e84; модели машин (P28_CarClean/Dam/Low — uint32-ссылки) 004c0218/004c1b6c; прочие —
   см. ported99.c. Все cdecl, кроме P99_DDEnumFmt (00420854, stdcall-колбэк DirectDraw). */
#pragma once
#include "gvar.h"
#include "reptr.h"
#include <stdint.h>

#ifdef RE_HOOK_BUILD
#  define P99_STD __attribute__((stdcall))
#else
#  define P99_STD
#endif

typedef int32_t p99_gear_t[4][5];
typedef uint8_t p99_rgb_t[3];
typedef uint8_t p99_b8_t[8];
typedef uint8_t p99_vis_t[0x2000];

#define P99_GearTab   GAME_VAR(p99_gear_t, P99_GearTab, 0x00560328)  /* .data: пороги вниз (назад/вперёд), вверх, множители */
#define P99_D17ECC    GAME_VAR(p99_b8_t, P99_D17ECC, 0x00d17ecc)     /* 8 байт после указателя 00d17ec8 */
#define P99_MrkA      GAME_VAR(int32_t, P99_MrkA, 0x00d0262c)
#define P99_MrkB      GAME_VAR(int32_t, P99_MrkB, 0x00d0263c)
#define P99_Mrk2660   GAME_VAR(int32_t, P99_Mrk2660, 0x00d02660)
#define P99_Mrk2664   GAME_VAR(int32_t, P99_Mrk2664, 0x00d02664)
#include "ported53.h"   /* P99_Mrk26B0/B8 = P53_Mrk[4]/[6] */
#include "ported98.h"   /* v1.85: P99_Mrk2730..38 — макросы над P98_MrkF */
#define P99_Mrk270C   GAME_VAR(int32_t, P99_Mrk270C, 0x00d0270c)
#define P99_Mrk2710   GAME_VAR(int32_t, P99_Mrk2710, 0x00d02710)
#define P99_Mrk2730   (P98_MrkF[4])   /* v1.85: float, макросы над P98_MrkF */
#define P99_Mrk2734   (P98_MrkF[5])
#define P99_Mrk2738   (P98_MrkF[6])
#define P99_Mrk2750   GAME_VAR(int32_t, P99_Mrk2750, 0x00d02750)
#define P99_Mrk2760   GAME_VAR(float, P99_Mrk2760, 0x00d02760)
#define P99_Mrk2764   GAME_VAR(float, P99_Mrk2764, 0x00d02764)
#define P99_Mrk2768   GAME_VAR(float, P99_Mrk2768, 0x00d02768)
#define P99_Vis       GAME_VAR(p99_vis_t, P99_Vis, 0x01136500)        /* маска видимости клеток (P76_CellFromPos/P76_InBox) */
#define P99_RoadPick  GAME_VAR(int16_t, P99_RoadPick, 0x011443c4)    /* выбранный узел дороги (-1 — нет); в игре — слово (movsx) */
#ifndef RE_HOOK_BUILD
#pragma push_macro("P99_GearTab") /*gvi*/
#undef P99_GearTab /*gvi*/
extern const p99_gear_t P99_GearTab;
#pragma pop_macro("P99_GearTab") /*gvi*/
#pragma push_macro("P99_D17ECC") /*gvi*/
#undef P99_D17ECC /*gvi*/
#pragma push_macro("P99_Vis") /*gvi*/
#undef P99_Vis /*gvi*/
extern p99_b8_t P99_D17ECC; extern p99_vis_t P99_Vis;
#pragma pop_macro("P99_Vis") /*gvi*/
#pragma pop_macro("P99_D17ECC") /*gvi*/
#pragma push_macro("P99_MrkA") /*gvi*/
#undef P99_MrkA /*gvi*/
#pragma push_macro("P99_MrkB") /*gvi*/
#undef P99_MrkB /*gvi*/
#pragma push_macro("P99_Mrk2660") /*gvi*/
#undef P99_Mrk2660 /*gvi*/
#pragma push_macro("P99_Mrk2664") /*gvi*/
#undef P99_Mrk2664 /*gvi*/
#pragma push_macro("P99_Mrk270C") /*gvi*/
#undef P99_Mrk270C /*gvi*/
extern int32_t P99_MrkA, P99_MrkB, P99_Mrk2660, P99_Mrk2664, P99_Mrk270C,
#pragma pop_macro("P99_Mrk270C") /*gvi*/
#pragma pop_macro("P99_Mrk2664") /*gvi*/
#pragma pop_macro("P99_Mrk2660") /*gvi*/
#pragma pop_macro("P99_MrkB") /*gvi*/
#pragma pop_macro("P99_MrkA") /*gvi*/
  P99_Mrk2710, P99_Mrk2750; extern float P99_Mrk2760, P99_Mrk2764, P99_Mrk2768;
#pragma push_macro("P99_RoadPick") /*gvi*/
#undef P99_RoadPick /*gvi*/
extern int16_t P99_RoadPick;
#pragma pop_macro("P99_RoadPick") /*gvi*/
#endif

void    P99_RadarXform(const int32_t *src, int32_t *dst, int32_t n);   /* 00506a07: точки мира → радар (шаг 4 int) */
int32_t P99_GearBox(int32_t car);                                      /* 004d6ae7: передача по оборотам, вернуть тягу */
void    P99_CamCheckDist(int32_t *cam);                                /* 004c3427 */
int32_t P99_CamCheckPlayer(int32_t *cam);                              /* 004c5e08 */
int32_t P99_CopsNear(const int16_t *view, uint8_t *car);               /* 004d2b5d */
int32_t P99_RoadAtCar(uint32_t car);                                   /* 0051b7a3: узел дороги под машиной или -1 */
void    P99_FreeCamMove(void);                                         /* 0049c99c */
void    P99_CamBehind(void);                                           /* 0049e47b */
void    P99_MarkerReset(void);                                         /* 004e9427 */
int32_t P99_TrafficAhead(void);                                        /* 004a1b2d */
int32_t P99_CopTarget(int32_t *cop);                                   /* 004a6e84 */
void    P99_CarModelClean(int32_t car);                                /* 004c0218: копия вершин/операций целой модели машины */
void    P99_CarOpsReset(int32_t car);                                  /* 004c1b6c */

/* ---- прочие (v1.44) ---- */
typedef uint8_t  p99_camkeys_t[0x34 * 0x40];
typedef struct { int32_t count; void **items; } p99_list_t;   /* как p58_list_t (ported58.h) */
#define P99_CamKeys   GAME_VAR(p99_camkeys_t, P99_CamKeys, 0x01136c80)  /* ключи сценария камеры: +0x28 флаги, +0x2c кадр */
#define P99_CamDelay  GAME_VAR(int32_t, P99_CamDelay, 0x00c810d0)
#define P99_CamDone   GAME_VAR(int32_t, P99_CamDone, 0x00b87ee8)
#define P99_CamOn     GAME_VAR(int32_t, P99_CamOn, 0x01136c60)
#define P99_CamEnd    GAME_VAR(uint8_t, P99_CamEnd, 0x01136c5c)
#define P99_CamIdx    GAME_VAR(int32_t, P99_CamIdx, 0x01137314)
#define P99_CamStep   GAME_VAR(int32_t, P99_CamStep, 0x01137358)
#define P99_CamT      GAME_VAR(int32_t, P99_CamT, 0x01137360)
#define P99_CamMax    GAME_VAR(int32_t, P99_CamMax, 0x0113736c)
#define P99_CamLast   GAME_VAR(int32_t, P99_CamLast, 0x01137374)
#define P99_CamFade   GAME_VAR(int32_t, P99_CamFade, 0x01137378)
#define P99_CamB0     GAME_VAR(int32_t, P99_CamB0, 0x011373b0)
#define P99_CamSpd    GAME_VAR(int32_t, P99_CamSpd, 0x011373c4)
#define P99_MsgWin    GAME_VAR(int32_t, P99_MsgWin, 0x00c80f74)
#define P99_MsgLose   GAME_VAR(int32_t, P99_MsgLose, 0x00c80f78)
#define P99_ScrNames  GAME_VAR(p99_list_t, P99_ScrNames, 0x00c81698)
#define P99_C80880    GAME_VAR(void *, P99_C80880, 0x00c80880)
#define P99_EvObj     GAME_VAR(uint8_t *, P99_EvObj, 0x01134128)       /* текущий объект компилятора событий */
#define P99_EvA       GAME_VAR(uint8_t *, P99_EvA, 0x01134244)         /* int16 по номеру → объект +0x4a */
#define P99_EvB       GAME_VAR(uint8_t *, P99_EvB, 0x01134260)         /* int16 → +0x40 */
#define P99_EvC       GAME_VAR(uint8_t *, P99_EvC, 0x0113411c)         /* uint16 → float +0x44 */
#define P99_EvId      GAME_VAR(int32_t, P99_EvId, 0x01134248)
#ifndef RE_HOOK_BUILD
#pragma push_macro("P99_CamKeys") /*gvi*/
#undef P99_CamKeys /*gvi*/
extern p99_camkeys_t P99_CamKeys; extern p99_list_t P99_ScrNames; extern void *P99_C80880;
#pragma pop_macro("P99_CamKeys") /*gvi*/
#pragma push_macro("P99_CamEnd") /*gvi*/
#undef P99_CamEnd /*gvi*/
#pragma push_macro("P99_CamDelay") /*gvi*/
#undef P99_CamDelay /*gvi*/
#pragma push_macro("P99_CamDone") /*gvi*/
#undef P99_CamDone /*gvi*/
#pragma push_macro("P99_CamOn") /*gvi*/
#undef P99_CamOn /*gvi*/
#pragma push_macro("P99_CamIdx") /*gvi*/
#undef P99_CamIdx /*gvi*/
#pragma push_macro("P99_CamStep") /*gvi*/
#undef P99_CamStep /*gvi*/
#pragma push_macro("P99_CamT") /*gvi*/
#undef P99_CamT /*gvi*/
#pragma push_macro("P99_CamMax") /*gvi*/
#undef P99_CamMax /*gvi*/
#pragma push_macro("P99_CamLast") /*gvi*/
#undef P99_CamLast /*gvi*/
extern uint8_t P99_CamEnd; extern int32_t P99_CamDelay, P99_CamDone, P99_CamOn, P99_CamIdx, P99_CamStep, P99_CamT, P99_CamMax, P99_CamLast,
#pragma pop_macro("P99_CamLast") /*gvi*/
#pragma pop_macro("P99_CamMax") /*gvi*/
#pragma pop_macro("P99_CamT") /*gvi*/
#pragma pop_macro("P99_CamStep") /*gvi*/
#pragma pop_macro("P99_CamIdx") /*gvi*/
#pragma pop_macro("P99_CamOn") /*gvi*/
#pragma pop_macro("P99_CamDone") /*gvi*/
#pragma pop_macro("P99_CamDelay") /*gvi*/
#pragma pop_macro("P99_CamEnd") /*gvi*/
  P99_CamFade, P99_CamB0, P99_CamSpd, P99_MsgWin, P99_MsgLose, P99_EvId;
extern uint8_t *P99_EvObj, *P99_EvA, *P99_EvB, *P99_EvC;
#endif
/* цвета пунктов меню (байты RGB в записях .data меню): 0054cbba + 0x14·k (k = 0..6), 0054cc5c, 0054aa40 */
#define P99_MenuText0 GAME_VAR(int32_t, P99_MenuText0, 0x0054cc68)
#define P99_MenuText1 GAME_VAR(int32_t, P99_MenuText1, 0x0054cc78)
#define P99_Rgb0      GAME_VAR(p99_rgb_t, P99_Rgb0, 0x0054cbba)
#define P99_Rgb1      GAME_VAR(p99_rgb_t, P99_Rgb1, 0x0054cbce)
#define P99_Rgb2      GAME_VAR(p99_rgb_t, P99_Rgb2, 0x0054cbe2)
#define P99_Rgb3      GAME_VAR(p99_rgb_t, P99_Rgb3, 0x0054cbf6)
#define P99_Rgb4      GAME_VAR(p99_rgb_t, P99_Rgb4, 0x0054cc0a)
#define P99_Rgb5      GAME_VAR(p99_rgb_t, P99_Rgb5, 0x0054cc1e)
#define P99_Rgb6      GAME_VAR(p99_rgb_t, P99_Rgb6, 0x0054cc32)
#define P99_Rgb7      GAME_VAR(p99_rgb_t, P99_Rgb7, 0x0054cc5c)
#define P99_Rgb8      GAME_VAR(p99_rgb_t, P99_Rgb8, 0x0054aa40)
#ifndef RE_HOOK_BUILD
#pragma push_macro("P99_MenuText0") /*gvi*/
#undef P99_MenuText0 /*gvi*/
#pragma push_macro("P99_MenuText1") /*gvi*/
#undef P99_MenuText1 /*gvi*/
extern int32_t P99_MenuText0, P99_MenuText1;
#pragma pop_macro("P99_MenuText1") /*gvi*/
#pragma pop_macro("P99_MenuText0") /*gvi*/
#pragma push_macro("P99_Rgb0") /*gvi*/
#undef P99_Rgb0 /*gvi*/
#pragma push_macro("P99_Rgb1") /*gvi*/
#undef P99_Rgb1 /*gvi*/
#pragma push_macro("P99_Rgb2") /*gvi*/
#undef P99_Rgb2 /*gvi*/
#pragma push_macro("P99_Rgb3") /*gvi*/
#undef P99_Rgb3 /*gvi*/
#pragma push_macro("P99_Rgb4") /*gvi*/
#undef P99_Rgb4 /*gvi*/
#pragma push_macro("P99_Rgb5") /*gvi*/
#undef P99_Rgb5 /*gvi*/
#pragma push_macro("P99_Rgb6") /*gvi*/
#undef P99_Rgb6 /*gvi*/
#pragma push_macro("P99_Rgb7") /*gvi*/
#undef P99_Rgb7 /*gvi*/
#pragma push_macro("P99_Rgb8") /*gvi*/
#undef P99_Rgb8 /*gvi*/
extern p99_rgb_t P99_Rgb0, P99_Rgb1, P99_Rgb2, P99_Rgb3, P99_Rgb4, P99_Rgb5, P99_Rgb6, P99_Rgb7, P99_Rgb8;
#pragma pop_macro("P99_Rgb8") /*gvi*/
#pragma pop_macro("P99_Rgb7") /*gvi*/
#pragma pop_macro("P99_Rgb6") /*gvi*/
#pragma pop_macro("P99_Rgb5") /*gvi*/
#pragma pop_macro("P99_Rgb4") /*gvi*/
#pragma pop_macro("P99_Rgb3") /*gvi*/
#pragma pop_macro("P99_Rgb2") /*gvi*/
#pragma pop_macro("P99_Rgb1") /*gvi*/
#pragma pop_macro("P99_Rgb0") /*gvi*/
#endif

int32_t P99_ChairHit(float x, float y);                              /* 004a2e14 */
int32_t P99_JunctionBlock(int32_t node);                             /* 00496eb4 */
int32_t P99_ScriptMsgs(void);                                        /* 004f4d3c */
void    P99_MenuDim(int32_t on);                                     /* 00412d7d */
int32_t P99_PartAhead(uint8_t *p, int32_t n);                        /* 00514c9f */
int32_t P99_DDEnumFmt(const uint32_t *fmt, uint8_t *ctx);            /* 00420854 (stdcall ret 8: колбэк перечисления форматов) */
void    P99_ScriptFree(void);                                        /* 004f638d */
void    P99_MapFree(void);                                           /* 004d3444 */
void    P99_CamScriptStep(void);                                     /* 0049ea37 */
void    P99_VarSetStr(uint8_t *var, const char *s);                  /* 004f8862 */
void    P99_CmdAppend(uint16_t cmd, uint8_t *ev);                    /* 004a5338 */
void    P99_EventAdd(int32_t n);                                     /* 004a4340 */
int32_t P99_PartOnChair(uint8_t *p, int32_t n);                      /* 0051358d */
void    P99_GoalCheck(int32_t t, uint8_t *g, int32_t *o);            /* 004f568a */
int32_t P99_PathAhead(uint8_t *car);                                 /* 004a7920 */
int32_t P99_SegCross(const int32_t *a, const int32_t *b, const int32_t *c, const int32_t *d, int32_t *ox, int32_t *oy); /* 00526aeb */
int32_t P99_SegClip(const int32_t *box, const int32_t *a, const int32_t *b, int32_t *o0, int32_t *o1);                 /* 00526cd5 */
void    P99_MenuItems(const int16_t *it);                            /* 0050f569 */
/* gvar-img v2.03 begin (tools/gen_gvar_img.py) */
#if !defined(RE_HOOK_BUILD) && !defined(RE_GVAR_PLAIN)
#undef P99_GearTab
#define P99_GearTab (*(p99_gear_t *)re_gvar(0x00560328u, sizeof(p99_gear_t), (void *)&P99_GearTab))
#undef P99_D17ECC
#define P99_D17ECC (*(p99_b8_t *)re_gvar(0x00d17eccu, sizeof(p99_b8_t), (void *)&P99_D17ECC))
#undef P99_MrkA
#define P99_MrkA (*(int32_t *)re_gvar(0x00d0262cu, sizeof(int32_t), (void *)&P99_MrkA))
#undef P99_MrkB
#define P99_MrkB (*(int32_t *)re_gvar(0x00d0263cu, sizeof(int32_t), (void *)&P99_MrkB))
#undef P99_Mrk2660
#define P99_Mrk2660 (*(int32_t *)re_gvar(0x00d02660u, sizeof(int32_t), (void *)&P99_Mrk2660))
#undef P99_Mrk2664
#define P99_Mrk2664 (*(int32_t *)re_gvar(0x00d02664u, sizeof(int32_t), (void *)&P99_Mrk2664))
#undef P99_Mrk270C
#define P99_Mrk270C (*(int32_t *)re_gvar(0x00d0270cu, sizeof(int32_t), (void *)&P99_Mrk270C))
#undef P99_Mrk2710
#define P99_Mrk2710 (*(int32_t *)re_gvar(0x00d02710u, sizeof(int32_t), (void *)&P99_Mrk2710))
#undef P99_Mrk2750
#define P99_Mrk2750 (*(int32_t *)re_gvar(0x00d02750u, sizeof(int32_t), (void *)&P99_Mrk2750))
#undef P99_Mrk2760
#define P99_Mrk2760 (*(float *)re_gvar(0x00d02760u, sizeof(float), (void *)&P99_Mrk2760))
#undef P99_Mrk2764
#define P99_Mrk2764 (*(float *)re_gvar(0x00d02764u, sizeof(float), (void *)&P99_Mrk2764))
#undef P99_Mrk2768
#define P99_Mrk2768 (*(float *)re_gvar(0x00d02768u, sizeof(float), (void *)&P99_Mrk2768))
#undef P99_Vis
#define P99_Vis (*(p99_vis_t *)re_gvar(0x01136500u, sizeof(p99_vis_t), (void *)&P99_Vis))
#undef P99_RoadPick
#define P99_RoadPick (*(int16_t *)re_gvar(0x011443c4u, sizeof(int16_t), (void *)&P99_RoadPick))
#undef P99_CamKeys
#define P99_CamKeys (*(p99_camkeys_t *)re_gvar(0x01136c80u, sizeof(p99_camkeys_t), (void *)&P99_CamKeys))
#undef P99_CamDelay
#define P99_CamDelay (*(int32_t *)re_gvar(0x00c810d0u, sizeof(int32_t), (void *)&P99_CamDelay))
#undef P99_CamDone
#define P99_CamDone (*(int32_t *)re_gvar(0x00b87ee8u, sizeof(int32_t), (void *)&P99_CamDone))
#undef P99_CamOn
#define P99_CamOn (*(int32_t *)re_gvar(0x01136c60u, sizeof(int32_t), (void *)&P99_CamOn))
#undef P99_CamEnd
#define P99_CamEnd (*(uint8_t *)re_gvar(0x01136c5cu, sizeof(uint8_t), (void *)&P99_CamEnd))
#undef P99_CamIdx
#define P99_CamIdx (*(int32_t *)re_gvar(0x01137314u, sizeof(int32_t), (void *)&P99_CamIdx))
#undef P99_CamStep
#define P99_CamStep (*(int32_t *)re_gvar(0x01137358u, sizeof(int32_t), (void *)&P99_CamStep))
#undef P99_CamT
#define P99_CamT (*(int32_t *)re_gvar(0x01137360u, sizeof(int32_t), (void *)&P99_CamT))
#undef P99_CamMax
#define P99_CamMax (*(int32_t *)re_gvar(0x0113736cu, sizeof(int32_t), (void *)&P99_CamMax))
#undef P99_CamLast
#define P99_CamLast (*(int32_t *)re_gvar(0x01137374u, sizeof(int32_t), (void *)&P99_CamLast))
#undef P99_CamFade
#define P99_CamFade (*(int32_t *)re_gvar(0x01137378u, sizeof(int32_t), (void *)&P99_CamFade))
#undef P99_CamB0
#define P99_CamB0 (*(int32_t *)re_gvar(0x011373b0u, sizeof(int32_t), (void *)&P99_CamB0))
#undef P99_CamSpd
#define P99_CamSpd (*(int32_t *)re_gvar(0x011373c4u, sizeof(int32_t), (void *)&P99_CamSpd))
#undef P99_MsgWin
#define P99_MsgWin (*(int32_t *)re_gvar(0x00c80f74u, sizeof(int32_t), (void *)&P99_MsgWin))
#undef P99_MsgLose
#define P99_MsgLose (*(int32_t *)re_gvar(0x00c80f78u, sizeof(int32_t), (void *)&P99_MsgLose))
#undef P99_EvId
#define P99_EvId (*(int32_t *)re_gvar(0x01134248u, sizeof(int32_t), (void *)&P99_EvId))
#undef P99_MenuText0
#define P99_MenuText0 (*(int32_t *)re_gvar(0x0054cc68u, sizeof(int32_t), (void *)&P99_MenuText0))
#undef P99_MenuText1
#define P99_MenuText1 (*(int32_t *)re_gvar(0x0054cc78u, sizeof(int32_t), (void *)&P99_MenuText1))
#undef P99_Rgb0
#define P99_Rgb0 (*(p99_rgb_t *)re_gvar(0x0054cbbau, sizeof(p99_rgb_t), (void *)&P99_Rgb0))
#undef P99_Rgb1
#define P99_Rgb1 (*(p99_rgb_t *)re_gvar(0x0054cbceu, sizeof(p99_rgb_t), (void *)&P99_Rgb1))
#undef P99_Rgb2
#define P99_Rgb2 (*(p99_rgb_t *)re_gvar(0x0054cbe2u, sizeof(p99_rgb_t), (void *)&P99_Rgb2))
#undef P99_Rgb3
#define P99_Rgb3 (*(p99_rgb_t *)re_gvar(0x0054cbf6u, sizeof(p99_rgb_t), (void *)&P99_Rgb3))
#undef P99_Rgb4
#define P99_Rgb4 (*(p99_rgb_t *)re_gvar(0x0054cc0au, sizeof(p99_rgb_t), (void *)&P99_Rgb4))
#undef P99_Rgb5
#define P99_Rgb5 (*(p99_rgb_t *)re_gvar(0x0054cc1eu, sizeof(p99_rgb_t), (void *)&P99_Rgb5))
#undef P99_Rgb6
#define P99_Rgb6 (*(p99_rgb_t *)re_gvar(0x0054cc32u, sizeof(p99_rgb_t), (void *)&P99_Rgb6))
#undef P99_Rgb7
#define P99_Rgb7 (*(p99_rgb_t *)re_gvar(0x0054cc5cu, sizeof(p99_rgb_t), (void *)&P99_Rgb7))
#undef P99_Rgb8
#define P99_Rgb8 (*(p99_rgb_t *)re_gvar(0x0054aa40u, sizeof(p99_rgb_t), (void *)&P99_Rgb8))
#endif
/* gvar-img v2.03 end */
