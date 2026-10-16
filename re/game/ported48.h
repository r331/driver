#pragma once
#include "gvar.h"
#include "unported.h"
#include "ported6.h"
#include "ported7.h"
#include "ported10.h"
#include "ported25.h"
#include "ported34.h"
#include "ported37.h"
#include "ported43.h"
#include "smallfuncs.h"
#include "uihandlers3.h"
#include "widgets.h"
#include <stdint.h>
/* Звуковые слоты (20 штук по 0x34 байта, bdc2a0), мастер-громкость/фейд, завершение/запуск подсистем,
   операции скрипта (указатель команд 00d12414, контекст 00d1240c). Всё cdecl. */
typedef struct {
  uint8_t  flags;      /* бит 0 — играет, 0x10 — зациклен, 8 — громкость изменена */
  uint8_t  pad1;
  uint16_t id;         /* номер сэмпла, 0xffff — свободен */
  uint8_t  data[0x28];
  int16_t  defVol;     /* громкость по умолчанию (сотые дБ) */
  int16_t  scaled;     /* громкость после таблицы и мастер-громкости */
  int16_t  vol;        /* текущая громкость, -10000..0 */
  int16_t  pad2;
} P48_Slot;
_Static_assert(sizeof(P48_Slot) == 0x34, "P48_Slot");
_Static_assert(__builtin_offsetof(P48_Slot, defVol) == 0x2c && __builtin_offsetof(P48_Slot, vol) == 0x30, "P48_Slot offsets");
#define P48_Snd ((P48_Slot *)S_00BDC2A0)          /* тот же массив, что S_00BDC2A0 (stride 0x34) */
typedef void (*P48_F0)(void);
typedef void (*P48_F1)(int32_t);
typedef void (*P48_F3)(int32_t, int32_t, int32_t);
typedef void (*P48_F4)(int32_t, int32_t, int32_t, int32_t);
typedef uint32_t P48_VolTabT[10001];
typedef uint8_t  P48_SampleT[0x2000];
typedef uint8_t  P48_Buf64[64];
typedef float    P48_Pos3[3];
#define P48_Drv00 GAME_VAR(P48_F0, P48_Drv00, 0x00bdcb00)   /* драйвер: выключить */
#define P48_Drv08 GAME_VAR(P48_F0, P48_Drv08, 0x00bdcb08)
#define P48_Drv0C GAME_VAR(P48_F0, P48_Drv0C, 0x00bdcb0c)
#define P48_Drv2C GAME_VAR(P48_F1, P48_Drv2C, 0x00bdcb2c)   /* выгрузить сэмпл */
#define P48_Drv38 GAME_VAR(P48_F3, P48_Drv38, 0x00bdcb38)
#define P48_Drv40 GAME_VAR(P48_F1, P48_Drv40, 0x00bdcb40)   /* остановить голос */
#define P48_Drv54 GAME_VAR(P48_F4, P48_Drv54, 0x00bdcb54)
#define P48_VolTab GAME_VAR(P48_VolTabT, P48_VolTab, 0x00b87f80)
#define P48_Samples GAME_VAR(P48_SampleT, P48_Samples, 0x00bdc886)  /* stride 8 по номеру сэмпла */
#define P48_B91D30 GAME_VAR(int32_t, P48_B91D30, 0x00b91d30)
#define P48_GlideBuf GAME_VAR(P48_Buf64, P48_GlideBuf, 0x00b1c190)
#define P48_Pos GAME_VAR(P48_Pos3, P48_Pos, 0x01136cb4)
#ifndef RE_HOOK_BUILD
extern P48_F0 P48_Drv00, P48_Drv08, P48_Drv0C; extern P48_F1 P48_Drv2C, P48_Drv40; extern P48_F3 P48_Drv38; extern P48_F4 P48_Drv54;
#pragma push_macro("P48_VolTab") /*gvi*/
#undef P48_VolTab /*gvi*/
#pragma push_macro("P48_Samples") /*gvi*/
#undef P48_Samples /*gvi*/
#pragma push_macro("P48_B91D30") /*gvi*/
#undef P48_B91D30 /*gvi*/
#pragma push_macro("P48_GlideBuf") /*gvi*/
#undef P48_GlideBuf /*gvi*/
#pragma push_macro("P48_Pos") /*gvi*/
#undef P48_Pos /*gvi*/
extern P48_VolTabT P48_VolTab; extern P48_SampleT P48_Samples; extern int32_t P48_B91D30; extern P48_Buf64 P48_GlideBuf; extern P48_Pos3 P48_Pos;
#pragma pop_macro("P48_Pos") /*gvi*/
#pragma pop_macro("P48_GlideBuf") /*gvi*/
#pragma pop_macro("P48_B91D30") /*gvi*/
#pragma pop_macro("P48_Samples") /*gvi*/
#pragma pop_macro("P48_VolTab") /*gvi*/
#endif
void     P48_FreeVoice(int32_t slot);               /* 00523e07: остановить голос и освободить слот */
void     P48_SetVoiceVolume(int32_t slot, int32_t vol); /* 00523ffd: громкость голоса (0x7fff — по умолчанию), -10000..0 */
void     P48_SetMasterVolume(float v);              /* 00523711: 0..1, пересчёт громкости играющих голосов */
void     P48_StopAll(void);                         /* 005237b1 */
void     P48_FreeSample(uint32_t id);               /* 00524b7e */
void     P48_ResetAll(void);                        /* 00523628 */
void     P48_SndShutdown(void);                     /* 00523595 */
void     P48_SndPause(int32_t a);                   /* 0052369b: a == 0 — приглушить все играющие */
void     P48_FadeEnd(void);                         /* 005243eb: конец фейда — вернуть мастер-громкость */
uint16_t P48_GetVoiceVolume(int32_t slot);          /* 005242e7 */
int32_t  P48_AnyKey(void);                          /* 004d97e9: опрос ввода, 1 если нажата любая клавиша 0..254 */
void     P48_PosToInts(int32_t *out);               /* 0041a1b5: 3 float (01136cb4) -> int32 с отбрасыванием дробной части */
int32_t  P48_GlideCheck(void);                      /* 00425f52 */
void     P48_ShutdownSystems(void);                 /* 004d3402 */
int32_t  P48_StartupSystems(void);                  /* 004d33c0 */
int32_t  P48_OpSet3(void);                          /* 004d020b: ctx[0..8] из потока, флаги &= 4 */
int32_t  P48_OpSet4(void);                          /* 004d107e: ctx[0x44],[0x28],[0x2c],[0x30] из потока */
int32_t  P48_OpRampDown(void);                      /* 004d116c: ctx.f[0x44] -= шаг; 1 и ограничение, если <= предела */
int32_t  P48_OpRampUp(void);                        /* 004d121b: ctx.f[0x44] += шаг; 1 и ограничение, если >= предела */
int32_t  P48_OpFlags(void);                         /* 004d142c: 1 — бит 0x20 флагов, 2 — слово ctx[0x40] */
int32_t  P48_OpRepeat(void);                        /* 004d1672: счётчик повторов с возвратом назад */
int32_t  P48_OpTurn(void);                          /* 004d0d7c: поворот на угол (0..4095) за шаг; 1 когда осталось меньше шага */
/* gvar-img v2.03 begin (tools/gen_gvar_img.py) */
#if !defined(RE_HOOK_BUILD) && !defined(RE_GVAR_PLAIN)
#undef P48_VolTab
#define P48_VolTab (*(P48_VolTabT *)re_gvar(0x00b87f80u, sizeof(P48_VolTabT), (void *)&P48_VolTab))
#undef P48_Samples
#define P48_Samples (*(P48_SampleT *)re_gvar(0x00bdc886u, sizeof(P48_SampleT), (void *)&P48_Samples))
#undef P48_B91D30
#define P48_B91D30 (*(int32_t *)re_gvar(0x00b91d30u, sizeof(int32_t), (void *)&P48_B91D30))
#undef P48_GlideBuf
#define P48_GlideBuf (*(P48_Buf64 *)re_gvar(0x00b1c190u, sizeof(P48_Buf64), (void *)&P48_GlideBuf))
#undef P48_Pos
#define P48_Pos (*(P48_Pos3 *)re_gvar(0x01136cb4u, sizeof(P48_Pos3), (void *)&P48_Pos))
#endif
/* gvar-img v2.03 end */
