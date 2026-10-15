#pragma once
#include "gvar.h"
#include "../platform/plat.h"
#include <stdint.h>
/* Рендер, шаг C (DirectDraw/Direct3D-обёртки инициализации) над plat_dd_* / plat_d3d_*.
   Объекты COM игра хранит как void* (в hook-сборке — 32-битные указатели Game.exe). Все функции __cdecl. */
#define P24_DD          GAME_VAR(void *, P24_DD, 0x00a42158)
#define P24_Primary     GAME_VAR(void *, P24_Primary, 0x00a42168)
#define P24_Back        GAME_VAR(void *, P24_Back, 0x00a4216c)
#define P24_ZSurf       GAME_VAR(void *, P24_ZSurf, 0x00a42170)
#define P24_Fullscreen  GAME_VAR(int32_t, P24_Fullscreen, 0x00a421f4)
#define P24_Bpp         GAME_VAR(int32_t, P24_Bpp, 0x0054ef28)
#define P24_RShiftR     GAME_VAR(int32_t, P24_RShiftR, 0x00a42184)   /* потеря бит R при упаковке */
#define P24_RShiftL     GAME_VAR(int32_t, P24_RShiftL, 0x00a42188)   /* позиция R */
#define P24_GShiftR     GAME_VAR(int32_t, P24_GShiftR, 0x00a4218c)
#define P24_GShiftL     GAME_VAR(int32_t, P24_GShiftL, 0x00a42190)
#define P24_BShiftR     GAME_VAR(int32_t, P24_BShiftR, 0x00a42194)
#define P24_BShiftL     GAME_VAR(int32_t, P24_BShiftL, 0x00a42198)
#define P24_Hwnd        GAME_VAR(void *, P24_Hwnd, 0x00a421bc)
#define P24_RestoreMode GAME_VAR(int32_t, P24_RestoreMode, 0x00a421c4)
#define P24_ModeW       GAME_VAR(int32_t, P24_ModeW, 0x00a421a4)
#define P24_ModeH       GAME_VAR(int32_t, P24_ModeH, 0x00a421a8)
#ifndef RE_HOOK_BUILD
extern void *P24_DD, *P24_Primary, *P24_Back, *P24_ZSurf, *P24_Hwnd;
extern int32_t P24_Fullscreen, P24_Bpp, P24_RShiftR, P24_RShiftL, P24_GShiftR, P24_GShiftL, P24_BShiftR, P24_BShiftL, P24_RestoreMode, P24_ModeW, P24_ModeH;
#endif
void   *P24_CreateSurface(void *dd, const void *desc);                 /* 00420c10 */
void   *P24_CreateDevice(void *d3d, const void *iid, void *surf);      /* 00420cfe */
void   *P24_CreateViewport(void *d3d);                                 /* 00420d5d */
int32_t P24_AddViewport(void *dev, void *vp, int32_t w, int32_t h);    /* 00420dad */
int32_t P24_FillBackbuffer(void *surf, uint32_t rgb);                  /* 00420ef6 */
int32_t P24_SetDisplayMode(void *dd, int32_t w, int32_t h);            /* 0042101b */
int32_t P24_CreatePrimarySurface(void);                                /* 0042106d */
void   *P24_CreateClipper(void *dd);                                   /* 00421250 */
int32_t P24_SetClipper(void *surf, void *clipper);                     /* 00421298 */
int32_t P24_AttachSurface(void *surf, void *attached);                 /* 004214dd */
void    P24_RestoreDisplay(void);                                      /* 004213a4 */
void    P24_RestoreSurfaces(void);                                     /* 004212dc */
