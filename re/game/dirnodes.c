#include "dirnodes.h"
#include "director.h"
#include "unported.h"
#include <string.h>
GAME_VAR_DEF(DIR_NODE*, DirNodeTable, 0x00d17c58)
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
