#pragma once
#include "gvar.h"
#include "unported.h"
#include "crt.h"
#include "engine.h"
#include "menuselect.h"
#include "ported4.h"
#include "ported5.h"
#include "ported6.h"
#include "ported11.h"
#include "ported12.h"
#include "ported20.h"
#include "ported27.h"
#include "ported28.h"
#include "ported41.h"
#include "ported68.h"
#include "ported44.h"
#include "ported46.h"
#include "ported54.h"
#include "ported56.h"
#include "ported57.h"
#include "ported58.h"
#include "ported59.h"
#include "ported62.h"
#include "ported78.h"
#include "ported80.h"
#include <stdint.h>
/* Шаг D, ported77 (все cdecl):
   - 004eca08 — открыть файл уровня (Levels\\iview.lev / train.lev / flat.lev / Miami_01.lev / Levels\\<имя>), в native '\\' → '/';
   - 004ecade — загрузка уровня: разбор блоков файла (число блоков, затем тип/размер/данные), раздача по загрузчикам;
   - 00524496 — загрузка банка звуков из текстового файла (строки, не начинающиеся с ';');
   - три экрана меню 00407160 / 00414c30 / 00408770 (схема «подготовка → таблица → ожидание → опрос / режим 00b87eec»);
   - 00509c40 — сброс таблиц рекордов/записей; 004f8643 — добавление блока в список MScript;
   - 004282f8 — плоскость камеры по расстоянию. */
#define P77_LevelName GAME_VAR(const char*, P77_LevelName, 0x00c81164)
#define P77_ListN     GAME_VAR(int32_t, P77_ListN, 0x00c81688)
#define P77_List      GAME_VAR(void**, P77_List, 0x00c8175c)
typedef float p77_plane_t[4];
#define P77_Plane     GAME_VAR(p77_plane_t, P77_Plane, 0x011cff80)
typedef uint8_t p77_b590e0_t[0x1008], p77_c62d60_t[0x100], p77_c65dc0_t[0x17a20], p77_c5fe00_t[0x2f4c], p77_c7d8c0_t[0x2f44], p77_c62e60_t[0x2f44];
#define P77_B590E0    GAME_VAR(p77_b590e0_t, P77_B590E0, 0x00b590e0)
#define P77_C62D60    GAME_VAR(p77_c62d60_t, P77_C62D60, 0x00c62d60)
#define P77_C65DC0    GAME_VAR(p77_c65dc0_t, P77_C65DC0, 0x00c65dc0)
#define P77_C5FE00    GAME_VAR(p77_c5fe00_t, P77_C5FE00, 0x00c5fe00)
#define P77_C7D8C0    GAME_VAR(p77_c7d8c0_t, P77_C7D8C0, 0x00c7d8c0)
#define P77_C62E60    GAME_VAR(p77_c62e60_t, P77_C62E60, 0x00c62e60)
#define P77_C7D850    GAME_VAR(uint8_t, P77_C7D850, 0x00c7d850)
#define P77_C7D8A4    GAME_VAR(int32_t, P77_C7D8A4, 0x00c7d8a4)
#define P77_C7D8A0    GAME_VAR(int32_t, P77_C7D8A0, 0x00c7d8a0)
#define P77_C7D8A8    GAME_VAR(int32_t, P77_C7D8A8, 0x00c7d8a8)
#define P77_C65DA4    GAME_VAR(int32_t, P77_C65DA4, 0x00c65da4)
#define P77_B5A0E8    GAME_VAR(int32_t, P77_B5A0E8, 0x00b5a0e8)
#define P77_S574570   GAME_VAR(int32_t, P77_S574570, 0x00574570)
#ifndef RE_HOOK_BUILD
extern const char *P77_LevelName; extern int32_t P77_ListN; extern void **P77_List; extern p77_plane_t P77_Plane;
extern p77_b590e0_t P77_B590E0; extern p77_c62d60_t P77_C62D60; extern p77_c65dc0_t P77_C65DC0; extern p77_c5fe00_t P77_C5FE00;
extern p77_c7d8c0_t P77_C7D8C0; extern p77_c62e60_t P77_C62E60; extern uint8_t P77_C7D850;
extern int32_t P77_C7D8A4, P77_C7D8A0, P77_C7D8A8, P77_C65DA4, P77_B5A0E8, P77_S574570;
#endif
void   *P77_OpenLevel(void);                                 /* 004eca08 */
int32_t P77_LoadLevel(void);                                 /* 004ecade */
int32_t P77_LoadBank(const char *name, uint16_t slot);       /* 00524496 */
int32_t P77_Menu407160(void);                                /* 00407160 */
int32_t P77_Menu414C30(void);                                /* 00414c30 */
int32_t P77_Menu408770(void);                                /* 00408770 */
void    P77_ResetTables(void);                               /* 00509c40 */
int32_t P77_ListAdd(int32_t size);                           /* 004f8643 */
void    P77_CameraPlane(int32_t d);                          /* 004282f8 */
