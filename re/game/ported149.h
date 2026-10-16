#pragma once
#include <stdint.h>
#include "gvar.h"
/* v1.94: ported149 — блок D3D/DirectDraw (Game\pc\DDraw.c / D3D.c): перечисление драйверов DirectDraw 0041ce90
   (+ колбэк 0041fac0, stdcall ret 0x10), колбэк устройств Direct3D 0041fcc7 (stdcall ret 0x18), сборка таблицы
   устройств 0041fe07, освобождение эмулируемых текстур 0041d6aa, эмулируемая 8-битная текстура: новый узел 004225eb и
   дополнительная поверхность к узлу 0042248b. Все обращения к DirectDraw/Direct3D — через plat_dd_* / plat_d3d_*.
   Записи в куче с 32-битными ссылками (адреса Game.exe; в native — re_addr/re_rd_ptr):
     драйвер DirectDraw 0x44: +0 имя, +0x20 GUID, +0x30 основной (guid NULL), +0x34/+0x38 голова/хвост устройств,
       +0x3c следующий, +0x40 предыдущий; голова 00a42148, хвост 00a4214c;
     устройство D3D 0x230: +0 имя, +0x20 GUID, +0x30 D3DDEVICEDESC HAL (0xfc), +0x12c HEL (0xfc), +0x228/+0x22c след./пред. */
#define P149_DDHead GAME_VAR(uint32_t, P149_DDHead, 0x00a42148)   /* адрес первой записи драйвера DirectDraw */
#define P149_DDTail GAME_VAR(uint32_t, P149_DDTail, 0x00a4214c)   /* адрес последней */
#ifndef RE_HOOK_BUILD
#pragma push_macro("P149_DDHead") /*gvi*/
#undef P149_DDHead /*gvi*/
#pragma push_macro("P149_DDTail") /*gvi*/
#undef P149_DDTail /*gvi*/
extern uint32_t P149_DDHead, P149_DDTail;
#pragma pop_macro("P149_DDTail") /*gvi*/
#pragma pop_macro("P149_DDHead") /*gvi*/
#endif
int32_t P149_DDEnumAll(void);                                                    /* 0041ce90: 1 — добавлены устройства */
int32_t P149_DDEnumCb(const void *guid, const char *desc, const char *name, void *ctx);   /* 0041fac0: в оригинале stdcall */
int32_t P149_D3DDevCb(const void *guid, const char *desc, const char *name,
                      const void *hw, const void *hel, void *ctx);              /* 0041fcc7: в оригинале stdcall */
void    P149_BuildDevs(void);                                                    /* 0041fe07: записи 01270ec0 (не больше 4) */
void    P149_EmulFreeAll(void);                                                  /* 0041d6aa */
int32_t P149_EmulAddSub(void *node, int32_t src, int32_t kind, int32_t pal);    /* 0042248b: 1 — успех */
int32_t P149_EmulNew(int32_t handle, int32_t src, int32_t kind, int32_t pal);   /* 004225eb: 1 — успех */
/* gvar-img v2.03 begin (tools/gen_gvar_img.py) */
#if !defined(RE_HOOK_BUILD) && !defined(RE_GVAR_PLAIN)
#undef P149_DDHead
#define P149_DDHead (*(uint32_t *)re_gvar(0x00a42148u, sizeof(uint32_t), (void *)&P149_DDHead))
#undef P149_DDTail
#define P149_DDTail (*(uint32_t *)re_gvar(0x00a4214cu, sizeof(uint32_t), (void *)&P149_DDTail))
#endif
/* gvar-img v2.03 end */
