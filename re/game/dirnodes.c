#include "dirnodes.h"
#include "director.h"
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
