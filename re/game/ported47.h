#pragma once
#include "gvar.h"
#include "unported.h"
#include "ported4.h"
#include "ported6.h"
#include "ported11.h"
#include "ported14.h"
#include "ported30.h"
#include "ported45.h"
#include "menustate.h"
#include "smallfuncs2.h"
#include <stdint.h>
/* Мелкие функции: чтение строки, флаги скриптов, диспетчер заставки, отладочный текст, обёртки Glide. cdecl, кроме 0042467f (stdcall, ret 0x1c). */
typedef int32_t P47_SlotArr[4];
#define P47_Slots   GAME_VAR(P47_SlotArr, P47_Slots, 0x00c80f60)   /* выбранные ячейки по режимам 1..4 (-1 — пусто) */
#define P47_Limit   GAME_VAR(int32_t, P47_Limit, 0x00c810cc)
#define P47_Flag    GAME_VAR(int32_t, P47_Flag, 0x0112b268)
#define P47_CamB    GAME_VAR(int32_t, P47_CamB, 0x00b5a8a4)
#define P47_WinArg5 GAME_VAR(int32_t, P47_WinArg5, 0x00b1c0dc)
#define P47_SwapCnt GAME_VAR(int32_t, P47_SwapCnt, 0x01270c30)
#ifndef RE_HOOK_BUILD
extern P47_SlotArr P47_Slots; extern int32_t P47_Limit, P47_Flag, P47_CamB, P47_WinArg5, P47_SwapCnt;
#endif
int32_t P47_ReadLine(void *file, char *buf);   /* 0041c7ad: fgets(buf,128,file): 0 — прочитано, -1 — конец */
int32_t P47_Call51B111(int32_t a, int32_t b);  /* 004c6091: вызывает 0051b111(a,b), результат отбрасывает, возвращает 1 */
int32_t P47_NoFlags(int32_t a, int32_t b);     /* 00495886: 1, если (0051b566(a,b) & 0x3c000000) == 0 */
void    P47_ResetPick(void);                   /* 004f5951: сброс выбранной ячейки режима, лимит 50, флаг d118a8 */
int32_t P47_TitleDispatch(void);               /* 0040a73d: по режиму меню — 00413d70/0040a3a0, при 0 — ожидание */
void    P47_LoadFlyby(int32_t n);              /* 0041a130: SCRIPTS\FLYBY\FLATn.FBD должен существовать, иначе фатальная ошибка */
void    P47_CameraModeText(void);              /* 004d9908: отладочная строка «CameraMode: a, b, c» */
void    P47_DirText(int32_t a);                /* 004d9827: отладочная строка «Dir: NORTH|EAST|SOUTH|WEST» */
int32_t P47_PrepareTemp(int32_t a);            /* 00405f2e: 00405fdb, 00406199, затем $TEMP$ */
int32_t P47_GlideWinOpen(int32_t a1, int32_t a2, int32_t a3, int32_t a4, int32_t a5, int32_t a6, int32_t a7); /* 0042467f (stdcall): grSstWinOpen */
void    P47_GlideSwap(void);                   /* 0042651a: grBufferSwap(0), счётчики кадров */
void    P47_TexTable(int32_t a, int32_t b, int32_t c, int32_t d); /* 00424921: grTexDownloadTable или 0041d50e */
