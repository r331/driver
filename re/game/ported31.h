#pragma once
#include "gvar.h"
#include "../platform/plat.h"
#include "ported24.h"
#include <stdint.h>
/* Окно игры и цикл сообщений (WinMain.c): создание окна, оконная процедура, прокачка сообщений — над plat_*. */
#define P31_Active    GAME_VAR(int32_t, P31_Active, 0x00bdf9cc)    /* окно активно (WM_ACTIVATEAPP / WM_ACTIVATE) */
#define P31_WindowMode GAME_VAR(int32_t, P31_WindowMode, 0x00bdf9c8) /* 1 — курсор прячется над окном */
#define P31_PriorityHigh GAME_VAR(int32_t, P31_PriorityHigh, 0x00b87e8c) /* 0 — «выше обычного», иначе «реального времени» */
#define P31_GlideModule GAME_VAR(int32_t, P31_GlideModule, 0x00b1c0e8) /* HMODULE glide2x.dll (0 — не загружена) */
#define P31_DDObj0 GAME_VAR(void *, P31_DDObj0, 0x00a42154)  /* прочие COM-объекты DirectDraw/Direct3D, освобождаемые вместе с DD */
#define P31_DDObj1 GAME_VAR(void *, P31_DDObj1, 0x00a4215c)
#define P31_DDObj2 GAME_VAR(void *, P31_DDObj2, 0x00a42160)
#define P31_DDObj3 GAME_VAR(void *, P31_DDObj3, 0x00a42164)
#define P31_DDObj4 GAME_VAR(void *, P31_DDObj4, 0x00a42174)
#define P31_DDVal0 GAME_VAR(int32_t, P31_DDVal0, 0x00a421ac)
#define P31_DDVal1 GAME_VAR(int32_t, P31_DDVal1, 0x00a421b0)
#define P31_DDVal2 GAME_VAR(int32_t, P31_DDVal2, 0x00a421b4)
#define P31_DDVal3 GAME_VAR(int32_t, P31_DDVal3, 0x00a421b8)
#define P31_DDVal4 GAME_VAR(int32_t, P31_DDVal4, 0x00a421c0)
#define P31_DDVal5 GAME_VAR(int32_t, P31_DDVal5, 0x00a421c8)
#ifndef RE_HOOK_BUILD
extern void *P31_DDObj0, *P31_DDObj1, *P31_DDObj2, *P31_DDObj3, *P31_DDObj4;
#pragma push_macro("P31_DDVal0") /*gvi*/
#undef P31_DDVal0 /*gvi*/
#pragma push_macro("P31_DDVal1") /*gvi*/
#undef P31_DDVal1 /*gvi*/
#pragma push_macro("P31_DDVal2") /*gvi*/
#undef P31_DDVal2 /*gvi*/
#pragma push_macro("P31_DDVal3") /*gvi*/
#undef P31_DDVal3 /*gvi*/
#pragma push_macro("P31_DDVal4") /*gvi*/
#undef P31_DDVal4 /*gvi*/
#pragma push_macro("P31_DDVal5") /*gvi*/
#undef P31_DDVal5 /*gvi*/
extern int32_t P31_DDVal0, P31_DDVal1, P31_DDVal2, P31_DDVal3, P31_DDVal4, P31_DDVal5;
#pragma pop_macro("P31_DDVal5") /*gvi*/
#pragma pop_macro("P31_DDVal4") /*gvi*/
#pragma pop_macro("P31_DDVal3") /*gvi*/
#pragma pop_macro("P31_DDVal2") /*gvi*/
#pragma pop_macro("P31_DDVal1") /*gvi*/
#pragma pop_macro("P31_DDVal0") /*gvi*/
#endif
#ifndef RE_HOOK_BUILD
#pragma push_macro("P31_Active") /*gvi*/
#undef P31_Active /*gvi*/
#pragma push_macro("P31_WindowMode") /*gvi*/
#undef P31_WindowMode /*gvi*/
#pragma push_macro("P31_PriorityHigh") /*gvi*/
#undef P31_PriorityHigh /*gvi*/
#pragma push_macro("P31_GlideModule") /*gvi*/
#undef P31_GlideModule /*gvi*/
extern int32_t P31_Active, P31_WindowMode, P31_PriorityHigh, P31_GlideModule;
#pragma pop_macro("P31_GlideModule") /*gvi*/
#pragma pop_macro("P31_PriorityHigh") /*gvi*/
#pragma pop_macro("P31_WindowMode") /*gvi*/
#pragma pop_macro("P31_Active") /*gvi*/
#endif
void Call00522323(void);                      /* 00522323: прокачать все ожидающие сообщения окна */
int32_t P31_InitWindow(void *hinst, int32_t show); /* 005223dc: класс «Driver», окно 640x480 «Driver V6.3w», ShowWindow; 1 — удалось */
/* 005224a8: оконная процедура (в оригинале stdcall, ret 0x10; с v1.95 хук). Сообщения WM_* как в оригинале;
   для WM_CREATE lparam — CREATESTRUCTA* (hInstance — plat_wm_create_hinst; в SDL lparam = hInstance). */
int32_t P31_WndProc(void *hwnd, uint32_t msg, uint32_t wparam, int32_t lparam);
int32_t P31_LoadGlide(void);                  /* 00425730: LoadLibrary("glide2x.dll"); 1 — загрузилась */
void P31_ReleaseDirectDraw(void);         /* 0041f2a0: освободить все COM-объекты DirectDraw/Direct3D, вернуть кооперативный режим, обнулить состояние */
/* gvar-img v2.03 begin (tools/gen_gvar_img.py) */
#if !defined(RE_HOOK_BUILD) && !defined(RE_GVAR_PLAIN)
#undef P31_Active
#define P31_Active (*(int32_t *)re_gvar(0x00bdf9ccu, sizeof(int32_t), (void *)&P31_Active))
#undef P31_WindowMode
#define P31_WindowMode (*(int32_t *)re_gvar(0x00bdf9c8u, sizeof(int32_t), (void *)&P31_WindowMode))
#undef P31_PriorityHigh
#define P31_PriorityHigh (*(int32_t *)re_gvar(0x00b87e8cu, sizeof(int32_t), (void *)&P31_PriorityHigh))
#undef P31_GlideModule
#define P31_GlideModule (*(int32_t *)re_gvar(0x00b1c0e8u, sizeof(int32_t), (void *)&P31_GlideModule))
#undef P31_DDVal0
#define P31_DDVal0 (*(int32_t *)re_gvar(0x00a421acu, sizeof(int32_t), (void *)&P31_DDVal0))
#undef P31_DDVal1
#define P31_DDVal1 (*(int32_t *)re_gvar(0x00a421b0u, sizeof(int32_t), (void *)&P31_DDVal1))
#undef P31_DDVal2
#define P31_DDVal2 (*(int32_t *)re_gvar(0x00a421b4u, sizeof(int32_t), (void *)&P31_DDVal2))
#undef P31_DDVal3
#define P31_DDVal3 (*(int32_t *)re_gvar(0x00a421b8u, sizeof(int32_t), (void *)&P31_DDVal3))
#undef P31_DDVal4
#define P31_DDVal4 (*(int32_t *)re_gvar(0x00a421c0u, sizeof(int32_t), (void *)&P31_DDVal4))
#undef P31_DDVal5
#define P31_DDVal5 (*(int32_t *)re_gvar(0x00a421c8u, sizeof(int32_t), (void *)&P31_DDVal5))
#endif
/* gvar-img v2.03 end */
