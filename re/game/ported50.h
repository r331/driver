#pragma once
#include "gvar.h"
#include "../platform/plat.h"
#include "ported49.h"
#include "ported38.h"
#include <stdint.h>
/* DirectSound/FMV: освобождение и сброс объектов, EAX-свойства (IKsPropertySet). Шаг C:
   0048b568, 0048ac0d, 0048b242, 0048bcc0, 0048cc5f, 0048c520, 0048c83d, 0048c8d6, 0048cba4, 0048cbd3, 0048ccdd, 0048cc64.
   Все функции cdecl (метка __thiscall у Ghidra ложная). */
typedef struct { void *a; void *b; uint8_t rest[0x80]; } P50_Voice;      /* ячейка 0x88 байт: два COM-указателя (+0, +4) */
#ifdef RE_HOOK_BUILD
_Static_assert(sizeof(P50_Voice) == 0x88, "P50_Voice");
#endif
typedef P50_Voice P50_VoiceTab[64];
#define P50_Voices   GAME_VAR(P50_VoiceTab, P50_Voices, 0x00b1c9a0)
#define P50_FmvA     GAME_VAR(void *, P50_FmvA, 0x00b1c840)       /* поток FMV (аудио-часть) */
#define P50_FmvB     GAME_VAR(void *, P50_FmvB, 0x00b1c844)
#define P50_FmvC     GAME_VAR(void *, P50_FmvC, 0x00b1c848)
#define P50_FmvFlag  GAME_VAR(void *, P50_FmvFlag, 0x00b1c83c)
#define P50_Fmv834   GAME_VAR(void *, P50_Fmv834, 0x00b1c834)
#define P50_Fmv830   GAME_VAR(void *, P50_Fmv830, 0x00b1c830)
#define P50_Fmv82C   GAME_VAR(void *, P50_Fmv82C, 0x00b1c82c)
#ifndef RE_HOOK_BUILD
extern P50_VoiceTab P50_Voices;
extern void *P50_FmvA, *P50_FmvB, *P50_FmvC, *P50_FmvFlag, *P50_Fmv834, *P50_Fmv830, *P50_Fmv82C;
#endif
void    P50_FmvReleaseObjs(void);        /* 0048b568 */
void    P50_FmvStopRelease(void);        /* 0048ac0d: остановить поток и освободить */
void    P50_FmvReleaseAll(void);         /* 0048b242 */
void    P50_SoundShutdown(void);         /* 0048bcc0: освободить свойства, слушатель, первичный буфер, DirectSound */
void    P50_Nop(void);                   /* 0048cc5f */
void    P50_ReleaseVoice(int32_t idx);   /* 0048c520 */
void    P50_ReleaseBuf(int32_t idx);     /* 0048c83d: Stop, освободить 3D и обычный буфер */
void    P50_ResetBuf(int32_t idx);       /* 0048c8d6: Stop, позиция 0, громкость 0, скорость 3D 0 */
void    P50_EaxSetDefault(void *ps);     /* 0048cba4: Set(EAX-свойство 1, -1.0f) */
int32_t P50_EaxEnable(void);             /* 0048cbd3: если Get/Set поддерживаются (маска 3) — включить; 1 — успех */
int32_t P50_CreateDummyBuf(void);        /* 0048ccdd: пустой 3D-буфер (11050 Гц, 16 бит, моно) для получения IKsPropertySet; 1 — успех */
int32_t P50_CreateKsProps(void);         /* 0048cc64: + QueryInterface(IKsPropertySet); 1 — успех */
