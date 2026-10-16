#pragma once
#include <stdint.h>
#include "gvar.h"
/* v1.95: ported150 — ролики FMV (Game\pc\fmv.c: DirectShow MultiMediaStream поверх DirectDraw) и сброс очереди
   отложенных треугольников Glide (0042d384). Все обращения к DirectDraw/DirectShow/окну — через plat_*.
   Объекты FMV — GAME_VAR из ported38/ported50 (00b1c814..00b1c848), длительность звука — P108_FmvLen (00b1c850). */
typedef char    p150_path_t[0x104];
typedef uint8_t p150_desc_t[0x6c];                                           /* DDSURFACEDESC (DirectDraw 1) */
#define P150_FmvPath  GAME_VAR(p150_path_t, P150_FmvPath, 0x00b1c59c)       /* полный путь ролика (OpenVideo) */
#define P150_CdRoot   GAME_VAR(p150_path_t, P150_CdRoot, 0x00b1c6a0)        /* корень CD с роликом (004d322c) */
#define P150_VidFmt   GAME_VAR(p150_desc_t, P150_VidFmt, 0x00b1c7a8)        /* формат видеопотока: +8 высота (= P38_Letter 00b1c7b0), +0xc ширина */
#define P150_PrimDesc GAME_VAR(p150_desc_t, P150_PrimDesc, 0x00b1c530)      /* описание экрана FMV: +0x48 DDPIXELFORMAT */
#define P150_FmvOff   GAME_VAR(int32_t, P150_FmvOff, 0x00b87ef4)            /* ≠ 0 — ролики не показываются */
#ifndef RE_HOOK_BUILD
extern p150_path_t P150_FmvPath, P150_CdRoot;
extern p150_desc_t P150_VidFmt, P150_PrimDesc;
extern int32_t P150_FmvOff;
#endif
int32_t P150_FmvDDInit(void *hwnd);          /* 0048ac1c: DirectDraw для ролика (IDirectDraw4, режим 640x480, экран, клиппер); 1 — успех */
int32_t P150_OpenVideo(const char *path);    /* 0048af23 OpenVideo: MultiMediaStream видео+звук, поверхность и образец кадра; 1 — успех */
int32_t P150_OpenAudio(const char *path);    /* 0048b3e8: только звуковой поток (FilterGraph + MultiMediaStream), длительность; 1 — успех */
void    P150_PlayFmv(int32_t hwnd, int32_t n, int32_t ans);   /* 0048a940: ролик FMVDATA\RENDER<n>.MPG, иначе/после — ответ автоответчика ANS<ans>.WAV */
void    P150_FlushTris(void);                /* 0042d384: вывести очередь треугольников 0115a140 (Glide) */
