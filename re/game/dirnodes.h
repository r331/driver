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
void ClearDirectorTable(DIR_NODE *tbl);          /* 004c36da */
void DrawNodeChain(DIR_NODE *start);             /* 004c3c94 */
void DrawNodeMarkersChain(DIR_NODE *start);      /* 004c3cf1 */
DIR_NODE *GetNodeParent(int id);                 /* 004c41ec */
void DumpWaypoints(void);                         /* 004c37f6 */
void DrawCornerIndicator(void);                  /* 004c42a9 */
#define DirIndicatorOn  GAME_VAR(int32_t,  DirIndicatorOn,  0x00d17bac)
#define DirIndicatorCnt GAME_VAR(int32_t,  DirIndicatorCnt, 0x00d17b80)
#define IndicatorTex    GAME_VAR(uint32_t, IndicatorTex,    0x00c55c58)
#ifndef RE_HOOK_BUILD
extern int32_t DirIndicatorOn, DirIndicatorCnt; extern uint32_t IndicatorTex;
#endif
void DrawNode(DIR_NODE *node);                    /* 004c3d5c */
void DrawNodeMarker(DIR_NODE *node);              /* 004c3e6a */
#define DirSelectedColor GAME_VAR(uint32_t, DirSelectedColor, 0x00d17b8c)
#ifdef RE_HOOK_BUILD
#define NodeIconTex ((uint32_t*)(uintptr_t)0x00c55820)
#else
#define NodeIconTex NodeIconTexArr
#endif
#ifndef RE_HOOK_BUILD
extern uint32_t DirSelectedColor; extern uint32_t NodeIconTexArr[];
#endif

#define DirUseDI GAME_VAR(int32_t, DirUseDI, 0x00d17ba0)
#define KeyArr(a) ((uint8_t*)(uintptr_t)(a))
#define CamParamTbl GAME_VAR(int32_t, CamParamTbl, 0x00d0788c)
#ifndef RE_HOOK_BUILD
extern int32_t DirUseDI; extern uint8_t KeyState[0x200]; extern int32_t CamParamTblArr[0x52*4];
#endif
uint32_t ReadDirectorKeys(void);                  /* 004c3f8f */
void ClampCameraHeight(int32_t *cam);             /* 004c356d */
