#pragma once
#include "gvar.h"
#include "../platform/plat.h"
#include "ported22.h"
#include "ported24.h"
#include "ported31.h"
#include "ported32.h"
#include "ported33.h"
#include <stdint.h>
/* Рендер, шаг C: блокировка поверхностей, формат пикселей, показ кадра и создание экранных поверхностей (Render.c / DDraw.c).
   0041eb8c, 0041ec82, 0041d3ed, 0041dec8, 00420c5a, 00420cac, 00421149. */
#define P39_Locked GAME_VAR(int32_t, P39_Locked, 0x00a421d0)   /* 1 — поверхность заблокирована (Lock удался) */
#define P39_Dummy  GAME_VAR(uint8_t, P39_Dummy, 0x006007c0)    /* буфер-пустышка, когда Lock не удался */
#ifndef RE_HOOK_BUILD
#pragma push_macro("P39_Locked") /*gvi*/
#undef P39_Locked /*gvi*/
extern int32_t P39_Locked;
#pragma pop_macro("P39_Locked") /*gvi*/
#pragma push_macro("P39_Dummy") /*gvi*/
#undef P39_Dummy /*gvi*/
extern uint8_t P39_Dummy[64];
#pragma pop_macro("P39_Dummy") /*gvi*/
#endif
/* Описание заблокированной поверхности, которое игра передаёт вызывающим (смещения из Game.exe). */
typedef struct {
  uint32_t reserved;   /* +0 */
  uint32_t ptr;        /* +4 lpSurface (в hook-сборке — адрес Game.exe) */
  int32_t  pitch;      /* +8 */
  int32_t  one;        /* +0xc: всегда 1 */
  int32_t  zero;       /* +0x10 */
  uint8_t  bpp;        /* +0x14 */
  uint8_t  r_loss, g_loss, b_loss;      /* +0x15..0x17: 8 − число бит канала */
  uint8_t  r_shift, g_shift, b_shift;   /* +0x18..0x1a: позиция младшего бита канала */
} P39_SurfInfo;
_Static_assert(sizeof(P39_SurfInfo) == 0x1c, "P39_SurfInfo");
_Static_assert(offsetof(P39_SurfInfo, bpp) == 0x14, "bpp");
_Static_assert(offsetof(P39_SurfInfo, b_shift) == 0x1a, "b_shift");
int32_t P39_LockSurface(int32_t a0, int32_t which, int32_t a2, int32_t a3, int32_t a4, P39_SurfInfo *out); /* 0041eb8c (stdcall, 6 арг.): which 0 — экран, 1 — задний буфер; 1 — готово */
int32_t P39_UnlockSurface(int32_t a0, int32_t which);   /* 0041ec82 (stdcall, 2 арг.): Unlock, если был Lock; BeginScene; 1 — готово */
int32_t P39_GetSurfaceFormat(int32_t which, P39_SurfInfo *out);   /* 0041d3ed: Lock + формат пикселей (биты и сдвиги каналов); 1 — готово */
void    P39_Present(int32_t wait);          /* 0041dec8 (stdcall, 1 арг.): показать кадр — Blt в окно или Flip на весь экран */
void   *P39_QueryDD4(void *dd);             /* 00420c5a: QueryInterface(IDirectDraw4); 0 — ошибка */
void   *P39_QueryD3D(void *dd);             /* 00420cac: QueryInterface(IDirect3D3); 0 — ошибка */
int32_t P39_CreateFrontBack(int32_t w, int32_t h);   /* 00421149: основная поверхность, задний буфер w×h, клиппер; 1 — удалось */
/* gvar-img v2.03 begin (tools/gen_gvar_img.py) */
#if !defined(RE_HOOK_BUILD) && !defined(RE_GVAR_PLAIN)
#undef P39_Locked
#define P39_Locked (*(int32_t *)re_gvar(0x00a421d0u, sizeof(int32_t), (void *)&P39_Locked))
#undef P39_Dummy
#define P39_Dummy (*(uint8_t *)re_gvar(0x006007c0u, sizeof(uint8_t), (void *)&P39_Dummy))
#endif
/* gvar-img v2.03 end */
