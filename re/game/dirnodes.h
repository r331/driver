/* DirNodes — таблица узлов режиссёра (записи по 0x2c байт, конец — id == 0xffff). */
#pragma once
#include "gvar.h"
typedef struct DIR_NODE {
    int32_t unk00, unk04, unk08;
    int32_t gx;         /* +0x0c клетка по X (шаг 0x35) */
    int32_t gy;         /* +0x10 клетка по Y */
    uint32_t flags;     /* +0x14 бит 2 — выключен */
    int32_t unk18;
    int32_t link1;      /* +0x1c id следующего */
    int32_t link2;      /* +0x20 id следующего (если flags&0x10) */
    int32_t unk24;
    int32_t id;         /* +0x28 */
} DIR_NODE;
_Static_assert(sizeof(DIR_NODE) == 0x2c, "DIR_NODE size");
typedef struct WAYPOINT_REC WAYPOINT_REC;
#define DirNodeTable GAME_VAR(DIR_NODE*, DirNodeTable, 0x00d17c58)
#ifndef RE_HOOK_BUILD
extern DIR_NODE *DirNodeTable;
#endif
void DirNopStub(void);
WAYPOINT_REC *GetWaypointForFrame(int frame);
DIR_NODE *FindNodeById(int id);
DIR_NODE *FindNodeByLink(int id);
int FindNodeAtPixel(int x, int y);
int SetNodeEnabled(int id, int enable);
