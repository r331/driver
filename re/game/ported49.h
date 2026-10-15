#pragma once
#include "gvar.h"
#include "../platform/plat.h"
#include <stdint.h>
/* DirectSound 3D: слушатель (IDirectSound3DListener, b1f428), таблица звуковых буферов (b1c900: буфер + 3D-буфер по 8 байт),
   свойства (b1f42c/b1f430). Все функции cdecl (метка __thiscall у Ghidra ложная — проверено по дизассемблеру).
   Шаг C: 0048bd40, 0048c74b, 0048c77e, 0048c7bd, 0048c97c, 0048c9b2, 0048caa0, 0048ca68, 0048c9e8, 0048ca28, 0048c7f0, 0048ccaf, 0048cd82. */
typedef struct { void *buf; void *buf3d; } P49_Pair;     /* в оригинале 8 байт (два 32-битных указателя) */
#ifdef RE_HOOK_BUILD
_Static_assert(sizeof(P49_Pair) == 8, "P49_Pair");
#endif
typedef P49_Pair P49_PairTab[64];
#define P49_Listener GAME_VAR(void *, P49_Listener, 0x00b1f428)   /* IDirectSound3DListener */
#define P49_Prop2C   GAME_VAR(void *, P49_Prop2C, 0x00b1f42c)
#define P49_Prop30   GAME_VAR(void *, P49_Prop30, 0x00b1f430)
#define P49_Bufs     GAME_VAR(P49_PairTab, P49_Bufs, 0x00b1c900)
#ifndef RE_HOOK_BUILD
extern void *P49_Listener, *P49_Prop2C, *P49_Prop30;
extern P49_PairTab P49_Bufs;
#endif
void    P49_Commit(void);                                  /* 0048bd40: CommitDeferredSettings */
void    P49_ListenerPos(float x, float y, float z);        /* 0048c74b */
void    P49_ListenerOrient(float fx, float fy, float fz, float ux, float uy, float uz); /* 0048c77e */
void    P49_ListenerVel(float x, float y, float z);        /* 0048c7bd */
void    P49_SetVolume(int32_t idx, int32_t vol);           /* 0048c97c */
void    P49_SetFreq(int32_t idx, uint32_t hz);             /* 0048c9b2 */
void    P49_GetStatus(int32_t idx, uint32_t *status);      /* 0048caa0 */
void    P49_SetMode3D(int32_t idx, uint32_t mode);         /* 0048ca68 */
void    P49_SetPos3D(int32_t idx, float x, float y, float z);   /* 0048c9e8 */
void    P49_SetVel3D(int32_t idx, float x, float y, float z);   /* 0048ca28 */
int32_t P49_Play(int32_t idx, uint32_t flags);             /* 0048c7f0: 1 — успех */
void    P49_ReleaseProp2C(void);                           /* 0048cd82 */
void    P49_ReleaseProps(void);                            /* 0048ccaf */
