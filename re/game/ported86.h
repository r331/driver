#pragma once
#include "gvar.h"
#include "ported40.h"
#include "ported63.h"
#include "ported85.h"
#include <stdint.h>
/* Шаг D, ported86 (веха 1, рендер мира): текстурные и гуро-обработчики типов записи модели, набор 1 режим 0.
   Размер записи / поля (смещения):
     20  0x38  0043 35e6  текстурный треугольник: [2] номер текстуры, [4] плоскость, [8,0xc,0x10] вершины, [0x14..0x28] u,v ×3, [0x2c..0x34] цвет r,g,b
     21  0x44  00433f4c   текстурный четырёхугольник: вершины [8..0x14], u,v ×4 [0x18..0x34], цвет [0x38..0x40]
     22  0x44  00434c58   как 20, но [0x14,0x18,0x1c] — индексы второго (накладного) прохода, u,v с 0x20, цвет с 0x38; накладка не перенесена
     23  0x54  0043593e   как 21, накладка [0x18..0x24], u,v с 0x28, цвет с 0x48
     50  0x2c  00432b77   треугольник Гуро: [0x14,0x18,0x1c] — номера нормалей (P84_NormLight), цвет [0x20..0x28]
     51  0x34  00433017   четырёхугольник Гуро: нормали [0x18..0x24], цвет [0x28..0x30]
   Текстурные: u·oow и v·oow вершины кладутся в sow/tow растеризатора (tmu[0], tmu[1]). Цвет вершины = плоскость P84_LightIn × цвет записи
   плюс динамические источники света (P63_SphN штук из P63_Hits → запись 0x24 в 011f40e0: x,y,z, цвет +0x10, r² +0x1c, 1/r² +0x20), потолок 255.
   Состояние растеризатора для текстуры — P85_StateDirty = 4 (иначе 0, «без текстуры»). Текущая текстура — 0125f3ec; при смене вызывается
   указатель 01270d5c (grTexSource: tmu, адрес в памяти текстур, маска, GrTexInfo). Тип 22/23: накладка (детализация, байт 00550828 ≠ 0) пропущена. */
#ifdef RE_HOOK_BUILD
typedef void (__attribute__((stdcall)) *p86_texsrc_fn)(int32_t tmu, uint32_t addr, int32_t mask, uint32_t info);
#else
typedef void (*p86_texsrc_fn)(int32_t tmu, uint32_t addr, int32_t mask, uint32_t info);
#endif
#define P86_CurTex GAME_VAR(int32_t, P86_CurTex, 0x0125f3ec)
#define P86_TexSrc GAME_VAR(p86_texsrc_fn, P86_TexSrc, 0x01270d5c)
#define P86_Detail GAME_VAR(uint8_t, P86_Detail, 0x00550828)
#ifndef RE_HOOK_BUILD
#pragma push_macro("P86_CurTex") /*gvi*/
#undef P86_CurTex /*gvi*/
extern int32_t P86_CurTex;
#pragma pop_macro("P86_CurTex") /*gvi*/
extern p86_texsrc_fn P86_TexSrc;
#pragma push_macro("P86_Detail") /*gvi*/
#undef P86_Detail /*gvi*/
extern uint8_t P86_Detail;
#pragma pop_macro("P86_Detail") /*gvi*/
/* native: текстуры карты. Страница файла уровня → plat_tex (RGBA); номер слота игры = номер страницы */
void P86_NativeReset(void);                                           /* освободить текстуры прошлого уровня */
void P86_NativeCapture(int32_t slot, int pair, const void *page0, const void *page1); /* вызывается из P41_LoadTexPages */
int  P86_NativeHandle(int32_t slot);                                  /* plat_tex слота или 0 */
/* v2.17: HD-пак (RE_TEXPACK / texpack): размер текстуры слота (256 или из пака), число подменённых страниц уровня,
   отклонённых сверкой; итог загрузки уровня → лог «[texpack] загружено N страниц» */
int  P86_NativeTexW(int32_t slot);
extern int32_t P86_TexpackN, P86_TexpackRejected;
void P86_NativeCaptureEnd(void);
extern int32_t P86_TexCount;
void P86_NativeInit(void);                                            /* ставит P86_TexSrc, регистрирует обработчики 20..23/50/51 */
#endif
void P86_TexTri(uint32_t arg);       /* 004335e6, тип 20 */
void P86_TexQuad(uint32_t arg);      /* 00433f4c, тип 21 */
void P86_TexTriD(uint32_t arg);      /* 00434c58, тип 22 */
void P86_TexQuadD(uint32_t arg);     /* 0043593e, тип 23 */
void P86_GouraudTri(uint32_t arg);   /* 00432b77, тип 50 */
void P86_GouraudQuad(uint32_t arg);  /* 00433017, тип 51 */
/* gvar-img v2.03 begin (tools/gen_gvar_img.py) */
#if !defined(RE_HOOK_BUILD) && !defined(RE_GVAR_PLAIN)
#undef P86_CurTex
#define P86_CurTex (*(int32_t *)re_gvar(0x0125f3ecu, sizeof(int32_t), (void *)&P86_CurTex))
#undef P86_Detail
#define P86_Detail (*(uint8_t *)re_gvar(0x00550828u, sizeof(uint8_t), (void *)&P86_Detail))
#endif
/* gvar-img v2.03 end */
