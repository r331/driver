#pragma once
#include "gvar.h"
#include "../platform/plat.h"
#include "ported25.h"
#include <stdint.h>
/* FMV-проигрыватель (DirectShow MultiMedia Stream) и DirectSound-обёртки, шаг C: 0048ae12, 0048b2fd, 0048b32b, 0048b34c, 0048b65d, 0048bdcc, 0048be68. */
#define P38_Mms       GAME_VAR(void *, P38_Mms, 0x00b1c828)       /* IMultiMediaStream */
#define P38_Mms2      GAME_VAR(void *, P38_Mms2, 0x00b1c83c)      /* второй поток (звук), его останавливает 0048b65d */
#define P38_Sample    GAME_VAR(void *, P38_Sample, 0x00b1c838)    /* IDirectDrawStreamSample */
#define P38_Dest      GAME_VAR(void *, P38_Dest, 0x00b1c81c)      /* поверхность назначения (экран) */
#define P38_Src       GAME_VAR(void *, P38_Src, 0x00b1c820)       /* поверхность потока */
#define P38_Obj824    GAME_VAR(void *, P38_Obj824, 0x00b1c824)
#define P38_DD        GAME_VAR(void *, P38_DD, 0x00b1c818)        /* IDirectDraw FMV */
#define P38_Obj814    GAME_VAR(void *, P38_Obj814, 0x00b1c814)
#define P38_Letter    GAME_VAR(int32_t, P38_Letter, 0x00b1c7b0)   /* высота чёрной полосы (в половинках) сверху/снизу */
#define P38_DsPrimary GAME_VAR(void *, P38_DsPrimary, 0x00b1f424) /* первичный буфер DirectSound */
#define P38_Ds        GAME_VAR(void *, P38_Ds, 0x00b1f420)        /* IDirectSound */
#define P38_TimerSlot GAME_VAR(int32_t, P38_TimerSlot, 0x00551130) /* слот таймера FMV (-1 — нет) */
#define P38_TimerFlag GAME_VAR(int32_t, P38_TimerFlag, 0x00551134)
#ifndef RE_HOOK_BUILD
extern void *P38_Mms, *P38_Mms2, *P38_Sample, *P38_Dest, *P38_Src, *P38_Obj824, *P38_DD, *P38_Obj814, *P38_DsPrimary, *P38_Ds;
extern int32_t P38_Letter, P38_TimerSlot, P38_TimerFlag;
#endif
int32_t P38_MmsRun(void);          /* 0048b2fd: SetState(RUN); 1 — успех */
void    P38_MmsStop(void);         /* 0048b32b: SetState(STOP) */
int32_t P38_UpdateFrame(void);     /* 0048b34c: Update образца и Blt в экран (640 строк, по центру высоты 480); 1 — успех */
void    P38_FmvRelease(void);      /* 0048ae12: освободить поверхности/DirectDraw FMV (экран заливается чёрным) */
void    P38_FmvStop(void);         /* 0048b65d: остановить поток и таймер FMV */
void    P38_SetPrimaryFormat(int32_t bits, int32_t rate);   /* 0048bdcc: формат первичного буфера (стерео PCM) */
void    P38_SetSpeakerConfig(int32_t mode);                 /* 0048be68: SetSpeakerConfig (1→3, 2→2, 3→1, 4→5, иначе 4) */
