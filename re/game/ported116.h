/* v1.61, ported116 — восстановлено из Game.exe. Все функции cdecl (ret без операнда; work/rets.py).
   004159e5 — два ползунка экрана настроек (SLIDER/SLIDERBA, выбранный пункт 0x12/0x13 — красный);
   00417651 — пять ползунков экрана графики (уровни a..e, выбранный sel 0..4 — красный);
   0050eaaa — меню паузы/ввода имени: ползунки (меню 00574f08 / 00575088), мигающий курсор «_» (00575370), пункты P99_MenuItems,
             при S_00B5A77C ≠ 0 — полноэкранная карта 00502fe2;
   00506c96 — значок объекта на радаре (клетки 0x5dc от игрока, поворот по курсу, тень 255−rgb, затем цвет);
   004d5ce0 — запуск звуков уровня (двигатели игрока/машины 0x41, ветер, сирены, фон по городу) и сброс таблиц голосов;
   0040abac — строка шрифтом 005d57a0 (переключение «^^n», выравнивание по флагам 005d77c0: 2 — вправо, 1 — по центру, 0x20 — базовая линия);
   0051e65e / 0051f376 — следы шин (таблицы 00b5c950 / 00b6e950 по 4 × 0x100 записей 0x48), четырёхугольники через P85_RasterB;
   004cc801 — отражения фонарей RFLECT на дороге (записи 00d132c0, сортировка по 1/z, по три треугольника). */
#pragma once
#include <stdint.h>
#include <string.h>
#include "gvar.h"
#include "ported85.h"
typedef uint8_t p116_skid_t[4 * 0x4800];
typedef p85_rv p116_v4_t[4];
#define P116_SkidRecA GAME_VAR(p116_skid_t, P116_SkidRecA, 0x00b5c950)   /* следы: счётчик P74_SkidD, начало P74_SkidB */
#define P116_SkidRecB GAME_VAR(p116_skid_t, P116_SkidRecB, 0x00b6e950)   /* следы: счётчик P74_SkidC, начало P74_SkidA */
#define P116_SkidV    GAME_VAR(p116_v4_t, P116_SkidV, 0x00b5c6e0)        /* 4 вершины четырёхугольника следа */
#define P116_K546A3C  GAME_VAR(float, P116_K546A3C, 0x00546a3c)          /* .data 0.0015625 — масштаб значка радара */
#define P116_MBar     GAME_VAR(uint32_t, P116_MBar, 0x00b5a740)          /* значок полосы ползунка меню паузы */
#define P116_MSlider  GAME_VAR(uint32_t, P116_MSlider, 0x00b5a744)       /* значок ползунка меню паузы */
#define P116_MLevB    GAME_VAR(float, P116_MLevB, 0x00b5a748)
#define P116_MLevA    GAME_VAR(float, P116_MLevA, 0x00b5a74c)
#define P116_Blink    GAME_VAR(int32_t, P116_Blink, 0x00b5a760)          /* фаза курсора «_» */
#define P116_BlinkT   GAME_VAR(int32_t, P116_BlinkT, 0x005755c0)         /* .data 10 — счётчик мигания */
#define P116_SndB2035C GAME_VAR(int32_t, P116_SndB2035C, 0x00b2035c)
#ifndef RE_HOOK_BUILD
extern p116_skid_t P116_SkidRecA, P116_SkidRecB; extern p116_v4_t P116_SkidV; extern float P116_K546A3C, P116_MLevA, P116_MLevB;
extern uint32_t P116_MBar, P116_MSlider; extern int32_t P116_Blink, P116_BlinkT, P116_SndB2035C;
#endif
static inline float p116_f(int32_t v) { float f; memcpy(&f, &v, 4); return f; }
void P116_Sliders2(void);                                                  /* 004159e5 */
void P116_Sliders5(float a, float b, float c, float d, float e, int32_t sel); /* 00417651 */
void P116_PauseMenu(void);                                                 /* 0050eaaa */
void P116_RadarIcon(const int32_t *pos, int32_t unused, uint8_t r, uint8_t g, uint8_t b, float scale); /* 00506c96 */
void P116_SndLevelStart(void);                                             /* 004d5ce0 */
void P116_Text(uint32_t txt);                                              /* 0040abac */
void P116_SkidsA(void);                                                    /* 0051e65e */
void P116_SkidsB(void);                                                    /* 0051f376 */
void P116_Reflections(void);                                               /* 004cc801 */
