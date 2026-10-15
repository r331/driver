#pragma once
#include "gvar.h"
#include "unported.h"
#include "engine.h"
#include "ported5.h"
#include "ported6.h"
#include "ported7.h"
#include "ported12.h"
#include "ported15.h"
#include "ported19.h"
#include "ported25.h"
#include "ported41.h"
#include "ported43.h"
#include "ported44.h"
#include "ported48.h"
#include "ported54.h"
#include "ported55.h"
#include "smallfuncs.h"
#include "uihandlers3.h"
#include "globalsets.h"
#include "director.h"
#include <stdint.h>
/* Шаг D: 22 мелкие функции (повтор/погоня, объекты, звук одного голоса, сплайн, кватернион, пути ReplayData, проверка сохранений).
   Все cdecl, кроме указанных. */
typedef uint32_t p56_blk84_t[0x84];       /* c810c0: блок настроек погони (c810c4 — флаги, c810c8 — счётчик) */
typedef uint32_t p56_blk11_t[0x11];
typedef uint32_t p56_blk10_t[16];
typedef uint8_t  p56_obj_t[66][0x148];    /* d077c0: объекты (65 + запасной d0cb08) */
typedef int32_t  p56_snd4_t[4];
typedef uint8_t  p56_ghost_t[0xb40];
typedef uint8_t  p56_page_t[0x10000];
typedef uint32_t p56_hdr_t[2];
typedef uint8_t  p56_save_t[0x38];
typedef char     p56_s60_t[0x60];
typedef char     p56_s100_t[0x100];
typedef char     p56_s1a0_t[0x1a0];
typedef char     p56_s120_t[0x120];
typedef char     p56_s360_t[0x360];

#define P56_Blk84    GAME_VAR(p56_blk84_t, P56_Blk84, 0x00c810c0)
#define P56_Save84   GAME_VAR(p56_blk84_t, P56_Save84, 0x00b5a498)
#define P56_Blk11    GAME_VAR(p56_blk11_t, P56_Blk11, 0x01271060)
#define P56_Save11   GAME_VAR(p56_blk11_t, P56_Save11, 0x00b5a448)
#define P56_Blk16    GAME_VAR(p56_blk10_t, P56_Blk16, 0x00b5c898)
#define P56_Objs     GAME_VAR(p56_obj_t, P56_Objs, 0x00d077c0)
#define P56_LoopTab  GAME_VAR(p56_snd4_t, P56_LoopTab, 0x00560378)
#define P56_Cur      GAME_VAR(int32_t, P56_Cur, 0x005603c8)
#define P56_B2EA48   GAME_VAR(int32_t, P56_B2EA48, 0x00b2ea48)
#define P56_B268     GAME_VAR(int32_t, P56_B268, 0x0112b268)
#define P56_C81880   GAME_VAR(int32_t, P56_C81880, 0x00c81880)
#define P56_F7E58    GAME_VAR(int32_t, P56_F7E58, 0x005f7e58)
#define P56_AA30     GAME_VAR(uint32_t, P56_AA30, 0x0054aa30)
#define P56_GhostBuf GAME_VAR(p56_ghost_t, P56_GhostBuf, 0x00d03920)
#define P56_G4538    GAME_VAR(int32_t, P56_G4538, 0x00d04538)
#define P56_G3908    GAME_VAR(int32_t, P56_G3908, 0x00d03908)
#define P56_GhostPtr GAME_VAR(uint8_t *, P56_GhostPtr, 0x00d04488)
#define P56_B87EA8   GAME_VAR(int32_t, P56_B87EA8, 0x00b87ea8)
#define P56_D4470    GAME_VAR(int32_t, P56_D4470, 0x00d04470)
#define P56_Page     GAME_VAR(p56_page_t, P56_Page, 0x00b32a34)
#define P56_EulerTab GAME_VAR(uint8_t *, P56_EulerTab, 0x00b1c280)
#define P56_C546120  GAME_VAR(float, P56_C546120, 0x00546120)
#define P56_C54611C  GAME_VAR(float, P56_C54611C, 0x0054611c)
#define P56_C546A38  GAME_VAR(float, P56_C546A38, 0x00546a38)
#define P56_F573FA0  GAME_VAR(float, P56_F573FA0, 0x00573fa0)
#define P56_F573FA4  GAME_VAR(float, P56_F573FA4, 0x00573fa4)
#define P56_Sprite   GAME_VAR(uint8_t *, P56_Sprite, 0x00c80888)
#define P56_CopsA    GAME_VAR(int32_t, P56_CopsA, 0x00d11a50)
#define P56_CopsB    GAME_VAR(int32_t, P56_CopsB, 0x00d11a58)
#define P56_PathLeader GAME_VAR(p56_s60_t, P56_PathLeader, 0x00c54fe0)
#define P56_PathPlayer GAME_VAR(p56_s100_t, P56_PathPlayer, 0x00c4d8e0)
#define P56_PathPads   GAME_VAR(p56_s60_t, P56_PathPads, 0x00c54f80)
#define P56_PathPings  GAME_VAR(p56_s120_t, P56_PathPings, 0x00c4d620)
#define P56_PathCams   GAME_VAR(p56_s100_t, P56_PathCams, 0x00c54e80)
#define P56_PathKey    GAME_VAR(p56_s1a0_t, P56_PathKey, 0x00c4d740)
#define P56_PathStart  GAME_VAR(p56_s360_t, P56_PathStart, 0x00c54b20)
#define P56_PathName   GAME_VAR(p56_s100_t, P56_PathName, 0x00c54ac0)
#define P56_SaveHdr  GAME_VAR(p56_hdr_t, P56_SaveHdr, 0x0057b6b0)
#define P56_SaveBuf  GAME_VAR(p56_save_t, P56_SaveBuf, 0x012852a0)
#ifndef RE_HOOK_BUILD
extern p56_blk84_t P56_Blk84, P56_Save84; extern p56_blk11_t P56_Blk11, P56_Save11; extern p56_blk10_t P56_Blk16;
extern p56_obj_t P56_Objs; extern p56_snd4_t P56_LoopTab;
extern int32_t P56_Cur, P56_B2EA48, P56_B268, P56_C81880, P56_F7E58, P56_G4538, P56_G3908, P56_B87EA8, P56_D4470, P56_CopsA, P56_CopsB;
extern uint32_t P56_AA30; extern p56_ghost_t P56_GhostBuf; extern uint8_t *P56_GhostPtr, *P56_EulerTab, *P56_Sprite; extern p56_page_t P56_Page;
extern float P56_C546120, P56_C54611C, P56_C546A38, P56_F573FA0, P56_F573FA4;
extern p56_s60_t P56_PathLeader, P56_PathPads; extern p56_s100_t P56_PathPlayer, P56_PathCams, P56_PathName; extern p56_s120_t P56_PathPings;
extern p56_s1a0_t P56_PathKey; extern p56_s360_t P56_PathStart; extern p56_hdr_t P56_SaveHdr; extern p56_save_t P56_SaveBuf;
#endif
void    P56_InitConsts(void);
void    P56_ReplaySetup(void);                                   /* 005105da */
void    P56_ObjSync(int32_t *a, uint8_t *o);                     /* 004da8d9 */
void    P56_ObjInit(uint8_t *o, const int32_t *q);               /* 004daa36 */
void    P56_LoopStart(int32_t n);                                /* 004d62ae */
void    P56_LoopUpdate(void);                                    /* 004d6a47 */
void    P56_SetVoicePos(int32_t slot, float x, float y, float z);/* 00523ec6 */
void    P56_ResetFrontend(void);                                 /* 0040c165 */
void    P56_ChaseTick(void);                                     /* 004f5a57 */
void    P56_CopyBlock16(const uint32_t *src);                    /* 0051d8ca */
void    P56_GhostInit(void);                                     /* 004e625e */
int32_t P56_CarPosCheck(int32_t id, int32_t min, uint32_t *out); /* 0049245a */
int32_t P56_ReplayRead(void);                                    /* 0051990a */
void    P56_HudTick(int32_t a);                                  /* 004e4f62 */
void    P56_DrawRowRects(const int16_t *p, int32_t x, int32_t y);/* 004f3032 */
void    P56_BmpPage(int32_t page, const uint8_t *bmp, int32_t x, int32_t y, int32_t w, int32_t h, int32_t stride); /* 005046f7 */
uint8_t *P56_AllocEulerTab(int32_t step);                        /* 00426c06 */
void    P56_Spline(float t, float *out, float p0, float p1, float p2, float p3); /* 0049ee5d */
void    P56_QuatRot(float *a, const float *b);                   /* 0049f180 */
void    P56_DrawSprite(void);                                    /* 00506b4b */
void    P56_ReplayPaths(int32_t n);                              /* 00518137 */
void    P56_CopsDebug(void);                                     /* 004d263d */
int32_t P56_SaveCheck(int32_t slot);                             /* 00405cb4 */
