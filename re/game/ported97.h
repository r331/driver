#pragma once
#include "gvar.h"
#include "reptr.h"
#include <stdint.h>
/* Шаг D, ported97 (v1.42): функции с 32-битными указателями в таблицах/списках/записях — по стандарту v1.42 (game/reptr.h):
   поля-указатели хранятся адресами Game.exe и переводятся re_ptr/re_addr, таблицы функций — re_fn.
   Таблица указателей рекордов 00bdfb20 (0051c900), запуск звука 00523cda, сброс машин 004a681a (записи 0xcd8),
   значок карты 005074e5, таблица звукового драйвера 00bdcb00 (0048bbd5), снимок LFB 004d9ad4, клетки 3×3 по списку +0x60
   (0050bc2b), список скрипта 00d12408 (004f4f10, 004cff7e, 004cf6b2, 004cf772, 004d156a, 00500090), строки меню звука/клавиш/
   настроек (0050f7b2, 0040fc9a, 00410e89, 0040ea70, 00419b35), таблицы обработчиков меню (0040c8a0, 004185d2), цели миссии
   (004f58c6, 004f57d7, 004f5c89), обзор копа 004d2c95, клавиши режиссёра 004c2ab0, мигание значков меню 00417479/00417fff,
   дым 004afcf7, подброс обломков 004ad128, затемнение со значком 004e5a1a. Все cdecl. */

#include "strtab.h"                         /* p97_strtab_t, P97_StrAddr (00c55820) */
typedef uint32_t p97_u4_t[4];
typedef uint32_t p97_u2_t[2];
typedef int32_t  p97_i2_t[2];
typedef int32_t  p97_i6_t[6];
typedef char     p97_txt32_t[0x20];
typedef char     p97_txt64_t[0x40];
typedef char     p97_s8_t[8];
typedef char     p97_s12_t[12];
typedef uint8_t  p97_pat_t[256 * 9];
typedef uint8_t  p97_menuA_t[0x1a0];
typedef uint8_t  p97_menuB_t[0x1d0];
typedef uint8_t  p97_menuC_t[0x90];
typedef uint8_t  p97_sndmenu_t[0xcc];
typedef uint8_t  p97_b2c0_t[10000];
typedef uint8_t  p97_b220_t[0x3c];
typedef uint8_t  p97_d11980_t[0xc0];
typedef uint8_t  p97_debris_t[100 * 0x3c];
typedef int32_t (*p97_lfblock_fn)(int32_t buffer, int32_t type, int32_t mode, int32_t origin, int32_t pipe, void *info);
typedef void (*p97_gr5_fn)(int32_t, int32_t, int32_t, int32_t, int32_t);
typedef void (*p97_gr1_fn)(int32_t);

#define P97_DrvA      GAME_VAR(re_fn_t, P97_DrvA, 0x00bdcb10)        /* звуковой драйвер: слоты без прежних имён */
#define P97_DrvB      GAME_VAR(re_fn_t, P97_DrvB, 0x00bdcb1c)
#define P97_DrvC      GAME_VAR(re_fn_t, P97_DrvC, 0x00bdcb28)
#define P97_DrvD      GAME_VAR(re_fn_t, P97_DrvD, 0x00bdcb30)
#define P97_DrvE      GAME_VAR(re_fn_t, P97_DrvE, 0x00bdcb34)
#define P97_DrvF      GAME_VAR(re_fn_t, P97_DrvF, 0x00bdcb3c)
#define P97_DrvG      GAME_VAR(re_fn_t, P97_DrvG, 0x00bdcb44)
#define P97_DrvH      GAME_VAR(re_fn_t, P97_DrvH, 0x00bdcb48)
#define P97_DrvI      GAME_VAR(re_fn_t, P97_DrvI, 0x00bdcb4c)
#define P97_DrvJ      GAME_VAR(re_fn_t, P97_DrvJ, 0x00bdcb50)
#define P97_DrvK      GAME_VAR(re_fn_t, P97_DrvK, 0x00bdcb58)
#define P97_DrvL      GAME_VAR(re_fn_t, P97_DrvL, 0x00bdcb5c)
#define P97_LfbLock   GAME_VAR(p97_lfblock_fn, P97_LfbLock, 0x01270e60)  /* grLfbLock */
#define P97_GrAlpha   GAME_VAR(p97_gr5_fn, P97_GrAlpha, 0x01270dcc)
#define P97_GrDepth   GAME_VAR(p97_gr1_fn, P97_GrDepth, 0x01270d68)
#define P97_CellPat   GAME_VAR(p97_pat_t, P97_CellPat, 0x00574674)      /* .data: 9 байт на тип (3×3) */
#define P97_ScrObjOn  GAME_VAR(int32_t, P97_ScrObjOn, 0x00c81270)
#define P97_OnOff     GAME_VAR(p97_u4_t, P97_OnOff, 0x00575558)         /* .data {2,1,2,6} */
#define P97_BitsStr   GAME_VAR(p97_u2_t, P97_BitsStr, 0x00575598)       /* .data: адреса "8bit"/"16bit" */
#define P97_RateStr   GAME_VAR(p97_u2_t, P97_RateStr, 0x005755a0)       /* .data: адреса "22050KHz"/"44100KHz" */
#define P97_SpkStr    GAME_VAR(p97_u4_t, P97_SpkStr, 0x005755a8)        /* .data {0xec..0xef} */
#define P97_Str8bit   GAME_VAR(p97_s8_t, P97_Str8bit, 0x005755ec)
#define P97_Str16bit  GAME_VAR(p97_s8_t, P97_Str16bit, 0x005755f4)
#define P97_Str22k    GAME_VAR(p97_s12_t, P97_Str22k, 0x005755fc)
#define P97_Str44k    GAME_VAR(p97_s12_t, P97_Str44k, 0x00575608)
#define P97_SndMenu   GAME_VAR(p97_sndmenu_t, P97_SndMenu, 0x00574f38)   /* пункты меню звука, шаг 0x28 */
#define P97_KeyMenuA  GAME_VAR(p97_menuA_t, P97_KeyMenuA, 0x0054c030)
#define P97_KeyMenuB  GAME_VAR(p97_menuB_t, P97_KeyMenuB, 0x0054c350)
#define P97_OptMenuA  GAME_VAR(p97_menuC_t, P97_OptMenuA, 0x0054acc0)
#define P97_OptMenuB  GAME_VAR(p97_menuC_t, P97_OptMenuB, 0x0054e560)
#define P97_OptTabA   GAME_VAR(p97_i6_t, P97_OptTabA, 0x0054adb0)       /* .data {2,1,9,10,11,29477} */
#define P97_OptTabB   GAME_VAR(p97_i6_t, P97_OptTabB, 0x0054e640)       /* .data {2,1,9,10,11,-1} */
#define P97_FpsTxtA   GAME_VAR(p97_txt32_t, P97_FpsTxtA, 0x005fe4e4)
#define P97_FpsTxtB   GAME_VAR(p97_txt32_t, P97_FpsTxtB, 0x005fea74)
#define P97_MsgBuf    GAME_VAR(p97_txt64_t, P97_MsgBuf, 0x00c80c60)
#define P97_C810A8    GAME_VAR(int32_t, P97_C810A8, 0x00c810a8)
#define P97_C81490    GAME_VAR(int32_t, P97_C81490, 0x00c81490)
#define P97_D078CC    CARTAB_VAR(int32_t, P97_D078CC, 0x00d078cc)
#define P97_BlinkA    GAME_VAR(p97_i2_t, P97_BlinkA, 0x0054e360)        /* .data {50, 20}: яркость, шаг */
#define P97_BlinkB    GAME_VAR(p97_i2_t, P97_BlinkB, 0x0054e4f0)        /* .data {50, 20} */
#define P97_IconL     GAME_VAR(int32_t, P97_IconL, 0x005fea3c)
#define P97_IconR     GAME_VAR(int32_t, P97_IconR, 0x005fea40)
#define P97_Debris    GAME_VAR(p97_debris_t, P97_Debris, 0x010fb220)    /* 100 записей 0x3c */
#define P97_FadeIcon  GAME_VAR(uint8_t *, P97_FadeIcon, 0x00d04788)
/* сброс машин 004a681a */
#define P97_B2A8      GAME_VAR(int32_t, P97_B2A8, 0x0112b2a8)
#define P97_B2A4      GAME_VAR(int32_t, P97_B2A4, 0x0112b2a4)
#define P97_B2A0      GAME_VAR(int32_t, P97_B2A0, 0x0112b2a0)
#define P97_129584    GAME_VAR(int32_t, P97_129584, 0x01129584)
#define P97_B274      GAME_VAR(int32_t, P97_B274, 0x0112b274)
#define P97_B2B0      GAME_VAR(int32_t, P97_B2B0, 0x0112b2b0)
#define P97_D9DC      GAME_VAR(int32_t, P97_D9DC, 0x0112d9dc)
#define P97_D9D8      GAME_VAR(int32_t, P97_D9D8, 0x0112d9d8)
#define P97_B264      GAME_VAR(int32_t, P97_B264, 0x0112b264)
#define P97_B260      GAME_VAR(int32_t, P97_B260, 0x0112b260)
#define P97_B290      GAME_VAR(int32_t, P97_B290, 0x0112b290)
#define P97_B214      GAME_VAR(int32_t, P97_B214, 0x0112b214)
#define P97_D9E0      GAME_VAR(int32_t, P97_D9E0, 0x0112d9e0)
#define P97_B28C      GAME_VAR(int32_t, P97_B28C, 0x0112b28c)
#define P97_B288      GAME_VAR(int32_t, P97_B288, 0x0112b288)
#define P97_B2C0      GAME_VAR(p97_b2c0_t, P97_B2C0, 0x0112b2c0)
#define P97_B220      GAME_VAR(p97_b220_t, P97_B220, 0x0112b220)
#define P97_D11980    GAME_VAR(p97_d11980_t, P97_D11980, 0x00d11980)
#define P97_D11A44    GAME_VAR(uint16_t, P97_D11A44, 0x00d11a44)

#ifndef RE_HOOK_BUILD

extern re_fn_t P97_DrvA, P97_DrvB, P97_DrvC, P97_DrvD, P97_DrvE, P97_DrvF, P97_DrvG, P97_DrvH, P97_DrvI, P97_DrvJ, P97_DrvK, P97_DrvL;
extern p97_lfblock_fn P97_LfbLock; extern p97_gr5_fn P97_GrAlpha; extern p97_gr1_fn P97_GrDepth;
extern p97_pat_t P97_CellPat; extern int32_t P97_ScrObjOn;
extern p97_u4_t P97_OnOff, P97_SpkStr; extern p97_u2_t P97_BitsStr, P97_RateStr;
extern p97_s8_t P97_Str8bit, P97_Str16bit; extern p97_s12_t P97_Str22k, P97_Str44k;
extern p97_sndmenu_t P97_SndMenu; extern p97_menuA_t P97_KeyMenuA; extern p97_menuB_t P97_KeyMenuB; extern p97_menuC_t P97_OptMenuA, P97_OptMenuB;
extern p97_i6_t P97_OptTabA, P97_OptTabB; extern p97_txt32_t P97_FpsTxtA, P97_FpsTxtB; extern p97_txt64_t P97_MsgBuf;
extern int32_t P97_C810A8, P97_C81490, P97_IconL, P97_IconR; extern p97_i2_t P97_BlinkA, P97_BlinkB;
extern p97_debris_t P97_Debris; extern uint8_t *P97_FadeIcon;
extern int32_t P97_B2A8, P97_B2A4, P97_B2A0, P97_129584, P97_B274, P97_B2B0, P97_D9DC, P97_D9D8, P97_B264, P97_B260, P97_B290, P97_B214, P97_D9E0, P97_B28C, P97_B288;
extern p97_b2c0_t P97_B2C0; extern p97_b220_t P97_B220; extern p97_d11980_t P97_D11980; extern uint16_t P97_D11A44;
#endif

void    P97_HsInit(void);                                                         /* 0051c900 */
int32_t P97_SndStart(uint32_t sample, int32_t voice, float a, float b, float c);  /* 00523cda: голос или -1 */
void    P97_ResetCars(void);                                                      /* 004a681a */
void    P97_MapIcon(float x, float y, uint32_t r, uint32_t g, uint32_t b, float scale);  /* 005074e5 */
void    P97_SndDrvInit(void);                                                     /* 0048bbd5 */
void    P97_LfbSnap(uint8_t *out);                                                /* 004d9ad4: кадр → BGR снизу вверх */
void    P97_MarkCells(uint8_t *rec);                                              /* 0050bc2b */
void    P97_ObjsFromScript(void);                                                 /* 004f4f10 */
void    P97_ScriptResetCur(void);                                                 /* 004cff7e */
int32_t P97_ScriptSave(uint8_t *out);                                             /* 004cf6b2: байт записано */
void    P97_ScriptLoad(const uint8_t *in);                                        /* 004cf772 */
int32_t P97_ScriptOpNext(void);                                                   /* 004d156a */
void    P97_ScriptEach(int32_t a, int32_t b, int32_t c);                          /* 00500090 */
void    P97_SndMenuInit(void);                                                    /* 0050f7b2 */
void    P97_KeyMenuAInit(void);                                                   /* 0040fc9a */
void    P97_KeyMenuBInit(void);                                                   /* 00410e89 */
void    P97_OptMenuAInit(void);                                                   /* 0040ea70 */
void    P97_OptMenuBInit(void);                                                   /* 00419b35 */
void    P97_MenuCall0(uint32_t tab, int32_t sel);                                 /* 0040c8a0 */
void    P97_MenuCall2(uint32_t tab, int32_t sel, uint32_t items);                 /* 004185d2 */
int32_t P97_GoalReached(int32_t t, uint8_t *goal, uint8_t *obj);                  /* 004f58c6 */
int32_t P97_GoalCops(int32_t t, uint8_t *goal, uint8_t *obj);                     /* 004f57d7 */
void    P97_AddTime(uint8_t *goal, int32_t delta);                                /* 004f5c89 */
int32_t P97_CopsSee(const int16_t *view, uint8_t *car);                           /* 004d2c95 */
void    P97_DirKeys(uint32_t keys);                                               /* 004c2ab0 */
void    P97_BlinkAStep(void);                                                     /* 00417479 */
void    P97_BlinkBStep(void);                                                     /* 00417fff */
void    P97_SpawnSmoke(const float *pos, const float *vel, const uint8_t *rgb, int16_t kind, int32_t arg);  /* 004afcf7 */
void    P97_KickDebris(const int32_t *pos);                                       /* 004ad128 */
void    P97_FadeIconDraw(void);                                                   /* 004e5a1a */
void    P97_InitConsts(void);                                                     /* native: начальные значения .data */
