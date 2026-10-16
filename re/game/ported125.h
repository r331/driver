#pragma once
#include <stdint.h>
#include "gvar.h"
/* v1.70: ported125 — загрузка уровня, действие узла меню повтора, сообщения приборной панели, частицы/обломки/объекты A,
   отсечение по ближней плоскости без UV, капли «стульев», подбор контрольных точек, значения меню управления,
   таблица смешения палитры, имена моделей компилятора. Все функции cdecl. */
typedef uint8_t p125_pick_t[4 * 0x20];
typedef int32_t p125_droptime_t[0x480];
typedef char    p125_fps_t[12];
typedef int32_t p125_mrk_t[6];
#define P125_C814E0   GAME_VAR(int32_t, P125_C814E0, 0x00c814e0)
#define P125_C814E4   GAME_VAR(int32_t, P125_C814E4, 0x00c814e4)
#define P125_C81690   GAME_VAR(int32_t, P125_C81690, 0x00c81690)
#define P125_C81694   GAME_VAR(int32_t, P125_C81694, 0x00c81694)
#define P125_D118E4   GAME_VAR(int32_t, P125_D118E4, 0x00d118e4)
#define P125_D11680   GAME_VAR(int32_t, P125_D11680, 0x00d11680)
#define P125_CF56C0   GAME_VAR(int32_t, P125_CF56C0, 0x00cf56c0)
#define P125_DirD17C0C GAME_VAR(int32_t, P125_DirD17C0C, 0x00d17c0c)  /* сбрасывается действием узла, если камера не 0x11 */
#define P125_Pick     GAME_VAR(p125_pick_t, P125_Pick, 0x00c81500)     /* 4 записи 0x20: +4 модель, +8/+0xc/+0x10 x,y,z (float) */
#define P125_PickIdx  GAME_VAR(int32_t, P125_PickIdx, 0x00c80bec)    /* следующая запись P125_Pick (0..3) */
#define P125_DropTime GAME_VAR(p125_droptime_t, P125_DropTime, 0x00bde780) /* добавка времени по модели (0x1200 байт) */
#define P125_FpsStr   GAME_VAR(p125_fps_t, P125_FpsStr, 0x00b5a48c)    /* строка «%dfps»/язык для меню управления */
#define P125_MrkSave  GAME_VAR(p125_mrk_t, P125_MrkSave, 0x01271070)   /* копия 6 int записи скрипта по 100-й точке */
#define P125_ModelNamesSize GAME_VAR(int32_t, P125_ModelNamesSize, 0x00b1ff64)
#define P125_ShrR     GAME_VAR(int32_t, P125_ShrR, 0x005c6748)
#define P125_ShrG     GAME_VAR(int32_t, P125_ShrG, 0x005c674c)
#define P125_ShrB     GAME_VAR(int32_t, P125_ShrB, 0x005c6750)
#define P125_ShlR     GAME_VAR(int32_t, P125_ShlR, 0x005c6754)
#define P125_ShlG     GAME_VAR(int32_t, P125_ShlG, 0x005c6758)
#define P125_ShlB     GAME_VAR(int32_t, P125_ShlB, 0x005c675c)
#ifndef RE_HOOK_BUILD
#pragma push_macro("P125_C814E0") /*gvi*/
#undef P125_C814E0 /*gvi*/
#pragma push_macro("P125_C814E4") /*gvi*/
#undef P125_C814E4 /*gvi*/
#pragma push_macro("P125_C81690") /*gvi*/
#undef P125_C81690 /*gvi*/
#pragma push_macro("P125_C81694") /*gvi*/
#undef P125_C81694 /*gvi*/
#pragma push_macro("P125_D118E4") /*gvi*/
#undef P125_D118E4 /*gvi*/
#pragma push_macro("P125_D11680") /*gvi*/
#undef P125_D11680 /*gvi*/
#pragma push_macro("P125_CF56C0") /*gvi*/
#undef P125_CF56C0 /*gvi*/
#pragma push_macro("P125_DirD17C0C") /*gvi*/
#undef P125_DirD17C0C /*gvi*/
extern int32_t P125_C814E0, P125_C814E4, P125_C81690, P125_C81694, P125_D118E4, P125_D11680, P125_CF56C0, P125_DirD17C0C;
#pragma pop_macro("P125_DirD17C0C") /*gvi*/
#pragma pop_macro("P125_CF56C0") /*gvi*/
#pragma pop_macro("P125_D11680") /*gvi*/
#pragma pop_macro("P125_D118E4") /*gvi*/
#pragma pop_macro("P125_C81694") /*gvi*/
#pragma pop_macro("P125_C81690") /*gvi*/
#pragma pop_macro("P125_C814E4") /*gvi*/
#pragma pop_macro("P125_C814E0") /*gvi*/
#pragma push_macro("P125_Pick") /*gvi*/
#undef P125_Pick /*gvi*/
#pragma push_macro("P125_PickIdx") /*gvi*/
#undef P125_PickIdx /*gvi*/
#pragma push_macro("P125_DropTime") /*gvi*/
#undef P125_DropTime /*gvi*/
#pragma push_macro("P125_FpsStr") /*gvi*/
#undef P125_FpsStr /*gvi*/
extern p125_pick_t P125_Pick; extern int32_t P125_PickIdx; extern p125_droptime_t P125_DropTime; extern p125_fps_t P125_FpsStr;
#pragma pop_macro("P125_FpsStr") /*gvi*/
#pragma pop_macro("P125_DropTime") /*gvi*/
#pragma pop_macro("P125_PickIdx") /*gvi*/
#pragma pop_macro("P125_Pick") /*gvi*/
#pragma push_macro("P125_MrkSave") /*gvi*/
#undef P125_MrkSave /*gvi*/
#pragma push_macro("P125_ModelNamesSize") /*gvi*/
#undef P125_ModelNamesSize /*gvi*/
extern p125_mrk_t P125_MrkSave; extern int32_t P125_ModelNamesSize;
#pragma pop_macro("P125_ModelNamesSize") /*gvi*/
#pragma pop_macro("P125_MrkSave") /*gvi*/
/* v2.02: 005c6748..005c675c — слова [1..6] формата LFB 005c6744 (P100_LfbFmt, пишет P100_LfbFormat 004078d0); прежде отдельные
   native-объекты с нулями — палитра меню 004079aa сводилась к синему каналу */
#pragma push_macro("P100_LfbFmt") /*gvi*/
#undef P100_LfbFmt /*gvi*/
extern int32_t P100_LfbFmt[7];
#pragma pop_macro("P100_LfbFmt") /*gvi*/
#undef P125_ShrR
#undef P125_ShrG
#undef P125_ShrB
#undef P125_ShlR
#undef P125_ShlG
#undef P125_ShlB
#define P125_ShrR (P100_LfbFmt[1])
#define P125_ShrG (P100_LfbFmt[2])
#define P125_ShrB (P100_LfbFmt[3])
#define P125_ShlR (P100_LfbFmt[4])
#define P125_ShlG (P100_LfbFmt[5])
#define P125_ShlB (P100_LfbFmt[6])
#endif
int32_t P125_LevelLoad(void);                                   /* 004d35b2: экран загрузки, сброс состояния, загрузка уровня; 1 — успех */
void    P125_ReplayNodeAction(int32_t id);                      /* 004c43b6: действие узла меню повтора (корень по +0x18) */
int32_t P125_AddDashMessage(const char *msg, int32_t lim);      /* 004f5e55: AddDashMessage — 1/0 */
void    P125_SmokePuffs(const int32_t *pos, const int32_t *vel, int32_t n, uint32_t kind, int32_t blue); /* 004b8d49: пул 0110b260 */
void    P125_CtrlMenuValues(void);                              /* 0050fbf4: значения пунктов меню управления (P117_MenuB) */
void    P125_ClipNearXY(const uint8_t *a, const uint8_t *b);   /* 0042d554: отсечение ребра по ближней плоскости (без UV) */
int32_t P125_DropHit(uint8_t *obj, const int32_t *vel);        /* 00522f4f: удар по объекту → капля (0) или счётчик (1) */
void    P125_ModelName(const char *line, uint16_t num);         /* 004a5634: «ИМЯ = N» в список имён моделей 00b1ff60 */
void    P125_BlendTable(const uint8_t *pal, uint32_t *out, uint8_t key, uint8_t fill); /* 004079aa: палитра → 16 бит и таблица 50% */
void    P125_DebrisBurst(const float *pos, int32_t n, int32_t kind); /* 004afa4c: обломки P97_Debris */
void    P125_ObjABurst(const int32_t *pos, const int32_t *vel, int32_t n, int32_t kind); /* 004b955c: объекты A (0x78) */
void    P125_PickupTick(const uint8_t *tab);                   /* 004fc0d9: подбор точек (записи 0x14) у машины игрока */
/* gvar-img v2.03 begin (tools/gen_gvar_img.py) */
#if !defined(RE_HOOK_BUILD) && !defined(RE_GVAR_PLAIN)
#undef P125_C814E0
#define P125_C814E0 (*(int32_t *)re_gvar(0x00c814e0u, sizeof(int32_t), (void *)&P125_C814E0))
#undef P125_C814E4
#define P125_C814E4 (*(int32_t *)re_gvar(0x00c814e4u, sizeof(int32_t), (void *)&P125_C814E4))
#undef P125_C81690
#define P125_C81690 (*(int32_t *)re_gvar(0x00c81690u, sizeof(int32_t), (void *)&P125_C81690))
#undef P125_C81694
#define P125_C81694 (*(int32_t *)re_gvar(0x00c81694u, sizeof(int32_t), (void *)&P125_C81694))
#undef P125_D118E4
#define P125_D118E4 (*(int32_t *)re_gvar(0x00d118e4u, sizeof(int32_t), (void *)&P125_D118E4))
#undef P125_D11680
#define P125_D11680 (*(int32_t *)re_gvar(0x00d11680u, sizeof(int32_t), (void *)&P125_D11680))
#undef P125_CF56C0
#define P125_CF56C0 (*(int32_t *)re_gvar(0x00cf56c0u, sizeof(int32_t), (void *)&P125_CF56C0))
#undef P125_DirD17C0C
#define P125_DirD17C0C (*(int32_t *)re_gvar(0x00d17c0cu, sizeof(int32_t), (void *)&P125_DirD17C0C))
#undef P125_Pick
#define P125_Pick (*(p125_pick_t *)re_gvar(0x00c81500u, sizeof(p125_pick_t), (void *)&P125_Pick))
#undef P125_PickIdx
#define P125_PickIdx (*(int32_t *)re_gvar(0x00c80becu, sizeof(int32_t), (void *)&P125_PickIdx))
#undef P125_DropTime
#define P125_DropTime (*(p125_droptime_t *)re_gvar(0x00bde780u, sizeof(p125_droptime_t), (void *)&P125_DropTime))
#undef P125_FpsStr
#define P125_FpsStr (*(p125_fps_t *)re_gvar(0x00b5a48cu, sizeof(p125_fps_t), (void *)&P125_FpsStr))
#undef P125_MrkSave
#define P125_MrkSave (*(p125_mrk_t *)re_gvar(0x01271070u, sizeof(p125_mrk_t), (void *)&P125_MrkSave))
#undef P125_ModelNamesSize
#define P125_ModelNamesSize (*(int32_t *)re_gvar(0x00b1ff64u, sizeof(int32_t), (void *)&P125_ModelNamesSize))
#endif
/* gvar-img v2.03 end */
