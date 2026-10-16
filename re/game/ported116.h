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
#pragma push_macro("P116_SkidRecA") /*gvi*/
#undef P116_SkidRecA /*gvi*/
#pragma push_macro("P116_SkidRecB") /*gvi*/
#undef P116_SkidRecB /*gvi*/
#pragma push_macro("P116_K546A3C") /*gvi*/
#undef P116_K546A3C /*gvi*/
#pragma push_macro("P116_MLevA") /*gvi*/
#undef P116_MLevA /*gvi*/
#pragma push_macro("P116_MLevB") /*gvi*/
#undef P116_MLevB /*gvi*/
extern p116_skid_t P116_SkidRecA, P116_SkidRecB; extern p116_v4_t P116_SkidV; extern float P116_K546A3C, P116_MLevA, P116_MLevB;
#pragma pop_macro("P116_MLevB") /*gvi*/
#pragma pop_macro("P116_MLevA") /*gvi*/
#pragma pop_macro("P116_K546A3C") /*gvi*/
#pragma pop_macro("P116_SkidRecB") /*gvi*/
#pragma pop_macro("P116_SkidRecA") /*gvi*/
#pragma push_macro("P116_MBar") /*gvi*/
#undef P116_MBar /*gvi*/
#pragma push_macro("P116_MSlider") /*gvi*/
#undef P116_MSlider /*gvi*/
#pragma push_macro("P116_Blink") /*gvi*/
#undef P116_Blink /*gvi*/
#pragma push_macro("P116_BlinkT") /*gvi*/
#undef P116_BlinkT /*gvi*/
#pragma push_macro("P116_SndB2035C") /*gvi*/
#undef P116_SndB2035C /*gvi*/
extern uint32_t P116_MBar, P116_MSlider; extern int32_t P116_Blink, P116_BlinkT, P116_SndB2035C;
#pragma pop_macro("P116_SndB2035C") /*gvi*/
#pragma pop_macro("P116_BlinkT") /*gvi*/
#pragma pop_macro("P116_Blink") /*gvi*/
#pragma pop_macro("P116_MSlider") /*gvi*/
#pragma pop_macro("P116_MBar") /*gvi*/
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
/* gvar-img v2.03 begin (tools/gen_gvar_img.py) */
#if !defined(RE_HOOK_BUILD) && !defined(RE_GVAR_PLAIN)
#undef P116_SkidRecA
#define P116_SkidRecA (*(p116_skid_t *)re_gvar(0x00b5c950u, sizeof(p116_skid_t), (void *)&P116_SkidRecA))
#undef P116_SkidRecB
#define P116_SkidRecB (*(p116_skid_t *)re_gvar(0x00b6e950u, sizeof(p116_skid_t), (void *)&P116_SkidRecB))
#undef P116_K546A3C
#define P116_K546A3C (*(float *)re_gvar(0x00546a3cu, sizeof(float), (void *)&P116_K546A3C))
#undef P116_MBar
#define P116_MBar (*(uint32_t *)re_gvar(0x00b5a740u, sizeof(uint32_t), (void *)&P116_MBar))
#undef P116_MSlider
#define P116_MSlider (*(uint32_t *)re_gvar(0x00b5a744u, sizeof(uint32_t), (void *)&P116_MSlider))
#undef P116_MLevB
#define P116_MLevB (*(float *)re_gvar(0x00b5a748u, sizeof(float), (void *)&P116_MLevB))
#undef P116_MLevA
#define P116_MLevA (*(float *)re_gvar(0x00b5a74cu, sizeof(float), (void *)&P116_MLevA))
#undef P116_Blink
#define P116_Blink (*(int32_t *)re_gvar(0x00b5a760u, sizeof(int32_t), (void *)&P116_Blink))
#undef P116_BlinkT
#define P116_BlinkT (*(int32_t *)re_gvar(0x005755c0u, sizeof(int32_t), (void *)&P116_BlinkT))
#undef P116_SndB2035C
#define P116_SndB2035C (*(int32_t *)re_gvar(0x00b2035cu, sizeof(int32_t), (void *)&P116_SndB2035C))
#endif
/* gvar-img v2.03 end */
