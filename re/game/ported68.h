#pragma once
#include "gvar.h"
#include "unported.h"
#include "engine.h"
#include "ported4.h"
#include "ported6.h"
#include "ported11.h"
#include "ported12.h"
#include "ported19.h"
#include "ported39.h"
#include "ported44.h"
#include "ported47.h"
#include "ported48.h"
#include "ported51.h"
#include "ported55.h"
#include "ported56.h"
#include "ported58.h"
#include "ported62.h"
#include "ported33.h"
#include "ported67.h"
#include "noop.h"
#include "smallfuncs.h"
#include <stdint.h>
/* Шаг D: 9 функций — детектор повторов, чтение слов из файла, наведение объекта, шаг частицы (вариант 00513efd),
   разбор аргументов камеры, смена сэмпла, захват буфера кадра Glide, сброс экрана интро, создание машины трафика.
   Все cdecl (метки __thiscall/__fastcall у этих функций нет). */
typedef struct { uint8_t cnt; uint8_t pad[3]; int32_t key; } P68_Rep;          /* запись 8 байт: счётчик повторов, ключ */
_Static_assert(sizeof(P68_Rep) == 8, "P68_Rep");
typedef P68_Rep P68_RepArr[5];
typedef struct { int32_t handle; uint16_t extra; uint8_t pad[2]; } P68_Samp;  /* +0 дескриптор драйвера, +4 служебное; +6/+7 — P48_Samples */
_Static_assert(sizeof(P68_Samp) == 8, "P68_Samp");
typedef P68_Samp P68_SampArr[0x400];
typedef int32_t (*P68_FLoad)(int32_t sample, int32_t arg);
typedef uint32_t P68_Cam4[4];
typedef int32_t P68_SaveArr[5];
#define P68_Rep_     GAME_VAR(P68_RepArr, P68_Rep_, 0x00bde740)
#define P68_Samps    GAME_VAR(P68_SampArr, P68_Samps, 0x00bdc880)
#define P68_DrvLoad  GAME_VAR(P68_FLoad, P68_DrvLoad, 0x00bdcb24)    /* драйвер звука: загрузить сэмпл, −1 — ошибка */
#define P68_CamF     GAME_VAR(P68_Cam4, P68_CamF, 0x01134250)         /* 4 слова; читаются в порядке 3,2,1,0 */
#define P68_CamI0    GAME_VAR(uint16_t, P68_CamI0, 0x011340c8)
#define P68_CamI1    GAME_VAR(uint16_t, P68_CamI1, 0x01134112)
#define P68_CamI2    GAME_VAR(uint16_t, P68_CamI2, 0x01134114)
#define P68_CamI3    GAME_VAR(uint16_t, P68_CamI3, 0x01134116)
#define P68_ModeW    GAME_VAR(int32_t, P68_ModeW, 0x00549cc0)
#define P68_ModeH    GAME_VAR(int32_t, P68_ModeH, 0x00549cc4)
#define P68_Saved    GAME_VAR(P68_SaveArr, P68_Saved, 0x012852b0)     /* сохранённое состояние интро: уровень, номер, A, B, Y */
#define P68_IntroBase GAME_VAR(uint32_t, P68_IntroBase, 0x01271040)   /* начало скрипта интро (32-битный адрес) */
#define P68_IntroCur  GAME_VAR(uint32_t, P68_IntroCur, 0x01271048)
#define P68_IntroA    GAME_VAR(int32_t, P68_IntroA, 0x01271050)
#define P68_D11A48    GAME_VAR(int32_t, P68_D11A48, 0x00d11a48)
#define P68_B87E54    GAME_VAR(int32_t, P68_B87E54, 0x00b87e54)
#ifndef RE_HOOK_BUILD
#pragma push_macro("P68_CamF") /*gvi*/
#undef P68_CamF /*gvi*/
extern P68_RepArr P68_Rep_; extern P68_SampArr P68_Samps; extern P68_FLoad P68_DrvLoad; extern P68_Cam4 P68_CamF;
#pragma pop_macro("P68_CamF") /*gvi*/
#pragma push_macro("P68_CamI0") /*gvi*/
#undef P68_CamI0 /*gvi*/
#pragma push_macro("P68_CamI1") /*gvi*/
#undef P68_CamI1 /*gvi*/
#pragma push_macro("P68_CamI2") /*gvi*/
#undef P68_CamI2 /*gvi*/
#pragma push_macro("P68_CamI3") /*gvi*/
#undef P68_CamI3 /*gvi*/
#pragma push_macro("P68_ModeW") /*gvi*/
#undef P68_ModeW /*gvi*/
#pragma push_macro("P68_ModeH") /*gvi*/
#undef P68_ModeH /*gvi*/
#pragma push_macro("P68_B87E54") /*gvi*/
#undef P68_B87E54 /*gvi*/
#pragma push_macro("P68_D11A48") /*gvi*/
#undef P68_D11A48 /*gvi*/
extern uint16_t P68_CamI0, P68_CamI1, P68_CamI2, P68_CamI3; extern int32_t P68_ModeW, P68_ModeH, P68_B87E54, P68_D11A48;
#pragma pop_macro("P68_D11A48") /*gvi*/
#pragma pop_macro("P68_B87E54") /*gvi*/
#pragma pop_macro("P68_ModeH") /*gvi*/
#pragma pop_macro("P68_ModeW") /*gvi*/
#pragma pop_macro("P68_CamI3") /*gvi*/
#pragma pop_macro("P68_CamI2") /*gvi*/
#pragma pop_macro("P68_CamI1") /*gvi*/
#pragma pop_macro("P68_CamI0") /*gvi*/
#pragma push_macro("P68_Saved") /*gvi*/
#undef P68_Saved /*gvi*/
#pragma push_macro("P68_IntroBase") /*gvi*/
#undef P68_IntroBase /*gvi*/
#pragma push_macro("P68_IntroCur") /*gvi*/
#undef P68_IntroCur /*gvi*/
#pragma push_macro("P68_IntroA") /*gvi*/
#undef P68_IntroA /*gvi*/
extern P68_SaveArr P68_Saved; extern uint32_t P68_IntroBase, P68_IntroCur; extern int32_t P68_IntroA;
#pragma pop_macro("P68_IntroA") /*gvi*/
#pragma pop_macro("P68_IntroCur") /*gvi*/
#pragma pop_macro("P68_IntroBase") /*gvi*/
#pragma pop_macro("P68_Saved") /*gvi*/
#endif
int32_t  P68_RepeatCheck(int32_t key);                          /* 00522e64: 1 на третьем повторе ключа из последних 4, иначе 0 */
int32_t  P68_ReadWords(void *file, uint8_t *buf);               /* 00524ed1: строка из файла, пробелы/табы сжаты в один, без конца-NUL при EOF; длина или −1 */
void     P68_AimSetup(uint8_t *obj);                            /* 00514f47: курс объекта на цель (+0x94..) и вектор (+0x64..) */
void     P68_ObjStepB(uint8_t *obj);                            /* 00513efd: как 00513fbc, но сначала 00514a47 */
uint8_t *P68_ReadCamArgs(uint8_t *out, const char *fmt);        /* 004a5505: 'f' — слово из 01134250.., 'i' — слово из 011340c8/…; вернуть конец */
int32_t  P68_ChangeSample(int32_t arg, int32_t n);              /* 0052455f: перезагрузить сэмпл n через драйвер; 1/0 */
uint32_t P68_LfbLock(int32_t which, void *info);                /* 0042476c: Glide grLfbLock или Lock поверхности D3D; формат пикселей в info+0x14.. */
void     P68_ScreenReset(int32_t restore);                      /* 0040c480: сброс фронтенда, смена режима, восстановление позиции интро */
uint8_t *P68_SpawnCar(uint8_t *rec, uint32_t owner);            /* 004a67b0: свободный слот машины трафика (без смещения −1, как в оригинале) */
/* gvar-img v2.03 begin (tools/gen_gvar_img.py) */
#if !defined(RE_HOOK_BUILD) && !defined(RE_GVAR_PLAIN)
#undef P68_CamF
#define P68_CamF (*(P68_Cam4 *)re_gvar(0x01134250u, sizeof(P68_Cam4), (void *)&P68_CamF))
#undef P68_CamI0
#define P68_CamI0 (*(uint16_t *)re_gvar(0x011340c8u, sizeof(uint16_t), (void *)&P68_CamI0))
#undef P68_CamI1
#define P68_CamI1 (*(uint16_t *)re_gvar(0x01134112u, sizeof(uint16_t), (void *)&P68_CamI1))
#undef P68_CamI2
#define P68_CamI2 (*(uint16_t *)re_gvar(0x01134114u, sizeof(uint16_t), (void *)&P68_CamI2))
#undef P68_CamI3
#define P68_CamI3 (*(uint16_t *)re_gvar(0x01134116u, sizeof(uint16_t), (void *)&P68_CamI3))
#undef P68_ModeW
#define P68_ModeW (*(int32_t *)re_gvar(0x00549cc0u, sizeof(int32_t), (void *)&P68_ModeW))
#undef P68_ModeH
#define P68_ModeH (*(int32_t *)re_gvar(0x00549cc4u, sizeof(int32_t), (void *)&P68_ModeH))
#undef P68_Saved
#define P68_Saved (*(P68_SaveArr *)re_gvar(0x012852b0u, sizeof(P68_SaveArr), (void *)&P68_Saved))
#undef P68_IntroBase
#define P68_IntroBase (*(uint32_t *)re_gvar(0x01271040u, sizeof(uint32_t), (void *)&P68_IntroBase))
#undef P68_IntroCur
#define P68_IntroCur (*(uint32_t *)re_gvar(0x01271048u, sizeof(uint32_t), (void *)&P68_IntroCur))
#undef P68_IntroA
#define P68_IntroA (*(int32_t *)re_gvar(0x01271050u, sizeof(int32_t), (void *)&P68_IntroA))
#undef P68_D11A48
#define P68_D11A48 (*(int32_t *)re_gvar(0x00d11a48u, sizeof(int32_t), (void *)&P68_D11A48))
#undef P68_B87E54
#define P68_B87E54 (*(int32_t *)re_gvar(0x00b87e54u, sizeof(int32_t), (void *)&P68_B87E54))
#endif
/* gvar-img v2.03 end */
/* v2.09: записи сэмплов 00bdc880 в игре — тоже в образе данных: байты +6/+7 записи — это P48_Samples 00bdc886 (флаги /LOOP /2D,
   приоритет), который генератор уже поместил в образ; при native-объекте P68_Samps флаги не доходили до P109_SndPlay (все звуки
   без цикла, 3D всегда). Не в блоке генератора — P68_SampArr не в его списке проверенных структур. */
#if !defined(RE_HOOK_BUILD) && !defined(RE_GVAR_PLAIN)
#undef P68_Samps
#define P68_Samps (*(P68_SampArr *)re_gvar(0x00bdc880u, sizeof(P68_SampArr), (void *)&P68_Samps))
#endif
