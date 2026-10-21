#pragma once
#include "gvar.h"
#include "unported.h"
#include "ported6.h"
#include "ported7.h"
#include "ported27.h"
#include "smallfuncs.h"
#include <stdint.h>
/* Рендер-диспетчеры по узлам текстур, границы виджета, карта (map.c), обход объектов. cdecl, кроме 0041d5e7/0041d89c (void) — тоже cdecl. */
typedef struct P46_TexNode {      /* узел списка текстур (голова 00a42180); в оригинале next на +0x1c */
  int32_t handle;                 /* +0 */
  uint8_t body[0x18];             /* +4 */
  struct P46_TexNode *next;       /* +1c */
} P46_TexNode;
#ifdef RE_HOOK_BUILD
_Static_assert(offsetof(P46_TexNode, next) == 0x1c, "P46_TexNode");
#endif
#define P46_TexHead   GAME_VAR(P46_TexNode *, P46_TexHead, 0x00a42180)
#define P46_MapBufA   GAME_VAR(void *, P46_MapBufA, 0x00b31ee4)
#define P46_MapBufB   GAME_VAR(void *, P46_MapBufB, 0x00b5a90c)
#define P46_MapBufC   GAME_VAR(void *, P46_MapBufC, 0x00bdfbc4)
#ifndef RE_HOOK_BUILD
extern P46_TexNode *P46_TexHead;
extern void *P46_MapBufA, *P46_MapBufB, *P46_MapBufC;
#endif
int32_t P46_FindTexNode(int32_t handle, P46_TexNode **out);           /* 00422444: поиск узла по номеру (если списки включены), 1/0 */
void    P46_TexCall(int32_t handle, int32_t arg);                       /* 0041d89c: сброс буферов, затем действие над узлом 004228eb */
void    P46_TexCall2(int32_t a, int32_t b, int32_t c, const uint8_t *d, int32_t handle); /* 0041d5e7: тип 5 -> 0042282f, иначе 0041f4a1 */
void    P46_SetBounds(int32_t a, int32_t b, int32_t c, int32_t d);     /* 004d614a: границы (b20330..3c), сброс b20344, если слот 0xf свободен */
void    P46_UpdateObjects(void);                                        /* 004defd1: 004df024(obj, obj[3]==1) для каждого объекта */
void    P46_LoadMapA(void *file, int32_t size);                         /* 004ec7f4: malloc size (map.c:0x42b) + чтение из файла */
void    P46_LoadMapB(void *file, int32_t size);                         /* 004ec4ce: malloc size (map.c:0x39f) + чтение + 0051be3c */
/* v2.35: 00bdfbc4 — one object: the native pointer P58_BlkBuf (block index of map B); P46_MapBufC is a read-only view */
#ifndef RE_HOOK_BUILD
extern int32_t *P58_BlkBuf;
#undef P46_MapBufC
#define P46_MapBufC ((void *)P58_BlkBuf)
#endif
