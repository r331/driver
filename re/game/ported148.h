#pragma once
#include <stdint.h>
#include "gvar.h"
/* v1.93: ported148 — блок DirectSound (directsound.c): перечисление драйверов 0048ba20 (+ колбэк 0048cdab, stdcall ret 0x10),
   запуск драйвера 0048ba31, буфер из образа WAV 0048c192, дубликат голоса 0048c2a3, перезаливка 0048c3e7,
   заливка Lock/Unlock 0048c47e, IKsPropertySet с EAX 0048cad6. Все обращения к DirectSound — через plat_ds_*. */
typedef struct { uint32_t guid_ptr; uint8_t guid[16]; char name[0x20]; } p148_drv_t;   /* запись 0x34: +0 адрес GUID (+4 или 0) */
_Static_assert(sizeof(p148_drv_t) == 0x34, "p148_drv_t");
typedef p148_drv_t p148_drvtab_t[8];
#define P148_Drv    GAME_VAR(p148_drvtab_t, P148_Drv, 0x00bdcb60)   /* драйверы DirectSound (не больше 8, счёт G6_00B91D2C) */
#define P148_EaxOn  GAME_VAR(int32_t, P148_EaxOn, 0x005511e8)       /* .data, начальное 1: включить EAX после запуска */
#ifndef RE_HOOK_BUILD
extern p148_drvtab_t P148_Drv; extern int32_t P148_EaxOn;
#endif
void    P148_SndEnum(void);                                              /* 0048ba20: DirectSoundEnumerate(0048cdab) */
int32_t P148_EnumCb(const void *guid, const char *desc, const char *module, void *ctx);   /* 0048cdab: в оригинале stdcall */
int32_t P148_SndOpen(int32_t drv, int32_t mode, int32_t hwnd);           /* 0048ba31: 1 — успех */
void   *P148_BufFromWav(void *ds, const void *wav, int32_t soft);        /* 0048c192: NULL — ошибка */
int32_t P148_DupVoice(int32_t n, int32_t voice);                         /* 0048c2a3: 1 — успех (__thiscall у Ghidra ложный) */
int32_t P148_Refill(void *buf, const void *wav);                         /* 0048c3e7: Restore + заливка; 1 — успех */
int32_t P148_Fill(void *buf, const void *data, uint32_t size);           /* 0048c47e: 1 — успех */
void   *P148_KsProps(void *buf);                                         /* 0048cad6: IKsPropertySet с EAX (маска 3); NULL — нет */
