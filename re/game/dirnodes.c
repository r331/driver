#include "dirnodes.h"
#include "director.h"
#include "unported.h"
#include <string.h>
#include <stdio.h>
#include "engine.h"
#include "unported.h"
GAME_VAR_DEF(DIR_NODE*, DirNodeTable, 0x00d17c58)
GAME_VAR_DEF(int32_t, DirIndicatorOn, 0x00d17bac)
GAME_VAR_DEF(int32_t, DirIndicatorCnt, 0x00d17b80)
GAME_VAR_DEF(uint32_t, IndicatorTex, 0x00c55c58)
GAME_VAR_DEF(uint32_t, DirSelectedColor, 0x00d17b8c)
#ifndef RE_HOOK_BUILD
uint32_t NodeIconTexArr[64];
#endif
/* 004c5367 — пустая функция */
void DirNopStub(void) {}
/* 004c379d — запись буфера для кадра (frame-2 кратно 150) */
WAYPOINT_REC *GetWaypointForFrame(int frame) {
    if (!DirectorBuffer) return 0;
    int i = (frame - 2) / 0x96;
    if (i * 0x96 != frame - 2) return 0;
    if (i >= DirectorBufferCount) return 0;
    return (WAYPOINT_REC *)DirectorBuffer + i;
}
/* 004c4151 */
DIR_NODE *FindNodeById(int id) {
    if (!id || !DirNodeTable) return 0;
    for (DIR_NODE *n = DirNodeTable; n->id != 0xffff; n++)
        if (n->id == id) return n;
    return 0;
}
/* 004c419e */
DIR_NODE *FindNodeByLink(int id) {
    if (!id) return 0;
    for (DIR_NODE *n = DirNodeTable; n->id != 0xffff; n++)
        if (n->link1 == id || n->link2 == id) return n;
    return 0;
}
/* 004c4226 — id узла, в чей квадрат [g*53+16, g*53+61) попал пиксель */
int FindNodeAtPixel(int x, int y) {
    for (DIR_NODE *n = DirNodeTable; n->id != 0xffff; n++) {
        int a = n->gx * 0x35, b = n->gy * 0x35;
        if (a + 0x10 <= x && x < a + 0x3d && b + 0x10 <= y && y < b + 0x3d) return n->id;
    }
    return 0;
}
/* 004c3f26 — возвращает «был включён»; enable==0 выключает (бит 4) */
int SetNodeEnabled(int id, int enable) {
    DIR_NODE *n = FindNodeById(id);
    if (!n) return 0;
    int was = (n->flags & 4) == 0;
    if (!enable) n->flags |= 4; else n->flags &= ~4u;
    return was;
}
/* 004c36da — для каждого узла: имя (+4, указатель Game.exe) -> иконка (+0x24) */
void ClearDirectorTable(DIR_NODE *tbl) {
    for (DIR_NODE *n = tbl; n->id != 0xffff; n++) {
#ifdef RE_HOOK_BUILD
        const char *name = (const char *)(uintptr_t)n->unk04;
        n->unk24 = (strlen(name) == 0) ? 0 : (int32_t)LoadIconByName(name);
#else
        n->unk24 = 0; /* в native имя — 32-битный указатель, недоступен */
#endif
    }
}
static DIR_NODE *NextInChain(DIR_NODE *start, DIR_NODE *cur) {
    return FindNodeById((start->flags & 0x10) ? cur->link2 : cur->link1);
}
/* 004c3c94 — рисует цепочку узлов (условие ветки берётся от первого узла, как в оригинале) */
void DrawNodeChain(DIR_NODE *start) {
    if (!start) return;
    for (DIR_NODE *c = start; c; c = NextInChain(start, c)) DrawNode(c);
}
/* 004c3cf1 — маркер рисуется для узла с id == DirectorUnk7C */
void DrawNodeMarkersChain(DIR_NODE *start) {
    if (!start) return;
    for (DIR_NODE *c = start; c; c = NextInChain(start, c))
        if (c->id == DirectorUnk7C) DrawNodeMarker(c);
}
/* 004c41ec — узел, на который указывает +0x18 узла id */
DIR_NODE *GetNodeParent(int id) {
    if (!id) return 0;
    DIR_NODE *n = FindNodeById(id);
    return n ? FindNodeById(n->unk18) : 0;
}
/* 004c37f6 — пишет в лог все путевые точки повтора (запись 12 байт: x, z, кадр) */
void DumpWaypoints(void) {
    char buf[64];
    if (DirectorBufferCount == 0) return;
    snprintf(buf, sizeof buf, "The game contains %d replay waypoints.", (int)DirectorBufferCount);
    DebugLog(buf);
    const int32_t *w = (const int32_t *)DirectorBuffer;
    for (int i = 0; i < DirectorBufferCount; i++) {
        snprintf(buf, sizeof buf, "Waypoint number %d, dump information:", i); DebugLog(buf);
        snprintf(buf, sizeof buf, "Frame index: %d", (int)w[i * 3 + 2]); DebugLog(buf);
        snprintf(buf, sizeof buf, "X position: %d\nZ position: %d", (int)w[i * 3], (int)w[i * 3 + 1]); DebugLog(buf);
    }
}
/* 004c42a9 — рисует индикатор в углу экрана (0..3 углы, 4 центр) пока счётчик < 0x20 */
void DrawCornerIndicator(void) {
    if (!DirIndicatorOn || DirIndicatorCnt >= 0x20) return;
    switch (DirectorUnk84) {
    case 0: DrawSprite(0x10,  0x10,  IndicatorTex, 0, 0,    0xff, 0, 0); break;
    case 1: DrawSprite(0x270, 0x10,  IndicatorTex, 0, 2,    0xff, 0, 0); break;
    case 2: DrawSprite(0x10,  0x1d0, IndicatorTex, 0, 0x20, 0xff, 0, 0); break;
    case 3: DrawSprite(0x270, 0x1d0, IndicatorTex, 0, 0x22, 0xff, 0, 0); break;
    case 4: DrawSprite(0x140, 0xf0,  IndicatorTex, 0, 1,    0xff, 0, 0); break;
    }
}
/* 004c3d5c — рисует узел в сетке (шаг 53, смещение 16): цвет — выбранный / включён 0xff8b00 / выключен 0x804500 */
void DrawNode(DIR_NODE *n) {
    uint32_t col = (n->id == DirectorUnk7C) ? DirSelectedColor : ((n->flags & 4) ? 0x804500u : 0xff8b00u);
    float x = 53.0f * (float)n->gx + 16.0f, y = 53.0f * (float)n->gy + 16.0f;
    if (n->unk24 == 0) { DrawRect(x, y, 45.0f, 45.0f, col); return; }
#ifdef RE_HOOK_BUILD
    const uint8_t *icon = (const uint8_t *)(uintptr_t)(uint32_t)n->unk24;
    DrawIcon(x, y, 45.0f / (float)icon[0xb], 45.0f / (float)icon[0xc], (uint32_t)n->unk24, col);
#endif
}
/* 004c3e6a — маркер узла: иконка (по unk00) в углу клетки; серый (0x40) если узел выключен, бит 1 — нижний правый угол */
void DrawNodeMarker(DIR_NODE *n) {
    int x = n->gx * 0x35 + 0x10, y = n->gy * 0x35 + 0x10;
    uint32_t c = (n->flags & 4) ? 0x40 : 0xff;
    if (n->flags & 1) { x += 0x31; y += 0x2d - GetMarkerYAdjust(0); }
    else y += 0x31;
    if (n->unk00 != -1) DrawSprite(x, y, NodeIconTex[n->unk00], 0, 0, c, c, c);
}
