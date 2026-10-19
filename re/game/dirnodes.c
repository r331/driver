/* dirnodes.c — the replay "director" screen (film editor): a table of nodes laid out on a grid of
   53-pixel cells (DIR_NODE, 0x2c bytes, terminated by id 0xffff), chains of nodes linked by id, replay
   waypoint lookup and dump, the corner indicator, director key reading and the free camera's height
   clamp.  Coordinates are in the 640x480 menu space. */
#include "dirnodes.h"
#include "director.h"
#include "unported.h"
#include <string.h>
#include <stdio.h>
#include "engine.h"
#include "unported.h"
GAME_VAR_DEF(DIR_NODE*, DirNodeTable, 0x00d17c58)
#define NODE_END          0xffff   /* id of the table terminator */
#define NODE_F_DISABLED   0x04     /* DIR_NODE.flags: node switched off (drawn dark) */
#define NODE_F_LINK2      0x10     /* chain follows link2 instead of link1 (taken from the chain's first node) */
#define NODE_F_MARK_LOW   0x01     /* marker drawn at the lower right instead of the lower left */
#define GRID_STEP         0x35     /* 53 px between node cells */
#define GRID_ORIGIN       0x10     /* 16 px left/top margin */
#define NODE_BOX          45       /* node square: 45 x 45 px (pixel hit test uses [origin, origin + 45)) */
#define WAYPOINT_EVERY    0x96     /* replay waypoints are recorded every 150 frames, starting at frame 2 */
#define COL_NODE_ON       0xff8b00u  /* orange */
#define COL_NODE_OFF      0x804500u  /* dark orange */
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("DirIndicatorOn")
#undef DirIndicatorOn
#pragma push_macro("DirIndicatorOn") /*gvi*/
#undef DirIndicatorOn /*gvi*/
int32_t DirIndicatorOn;
#pragma pop_macro("DirIndicatorOn") /*gvi*/
#pragma pop_macro("DirIndicatorOn")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("DirIndicatorCnt")
#undef DirIndicatorCnt
#pragma push_macro("DirIndicatorCnt") /*gvi*/
#undef DirIndicatorCnt /*gvi*/
int32_t DirIndicatorCnt;
#pragma pop_macro("DirIndicatorCnt") /*gvi*/
#pragma pop_macro("DirIndicatorCnt")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("IndicatorTex")
#undef IndicatorTex
#pragma push_macro("IndicatorTex") /*gvi*/
#undef IndicatorTex /*gvi*/
uint32_t IndicatorTex;
#pragma pop_macro("IndicatorTex") /*gvi*/
#pragma pop_macro("IndicatorTex")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("DirSelectedColor")
#undef DirSelectedColor
#pragma push_macro("DirSelectedColor") /*gvi*/
#undef DirSelectedColor /*gvi*/
uint32_t DirSelectedColor;
#pragma pop_macro("DirSelectedColor") /*gvi*/
#pragma pop_macro("DirSelectedColor")
#endif
#ifndef RE_HOOK_BUILD
uint32_t NodeIconTexArr[64];
#endif
/* 004c5367 — пустая функция */
/* DirNopStub — Game.exe 004c5367.  Empty. */
void DirNopStub(void) {}
/* 004c379d — запись буфера для кадра (frame-2 кратно 150) */
/* GetWaypointForFrame — Game.exe 004c379d.  Replay waypoint recorded at `frame`: waypoints exist for
   frames 2, 152, 302, ...; returns DirectorBuffer[(frame - 2) / 150], or NULL if frame is not such a
   frame, past the recorded count, or there is no buffer. */
WAYPOINT_REC *GetWaypointForFrame(int frame) {
    if (!DirectorBuffer) return 0;
    int i = (frame - 2) / WAYPOINT_EVERY;
    if (i * WAYPOINT_EVERY != frame - 2) return 0;
    if (i >= DirectorBufferCount) return 0;
    return (WAYPOINT_REC *)DirectorBuffer + i;
}
/* 004c4151 */
/* FindNodeById — Game.exe 004c4151.  Node with this id, or NULL (id 0 = none; native: also NULL table). */
DIR_NODE *FindNodeById(int id) {
    if (!id || !DirNodeTable) return 0;
    for (DIR_NODE *n = DirNodeTable; n->id != NODE_END; n++)
        if (n->id == id) return n;
    return 0;
}
/* 004c419e */
/* FindNodeByLink — Game.exe 004c419e.  First node whose link1 or link2 is id (its predecessor in a chain). */
DIR_NODE *FindNodeByLink(int id) {
    if (!id) return 0;
    for (DIR_NODE *n = DirNodeTable; n->id != NODE_END; n++)
        if (n->link1 == id || n->link2 == id) return n;
    return 0;
}
/* 004c4226 — id узла, в чей квадрат [g*53+16, g*53+61) попал пиксель */
/* FindNodeAtPixel — Game.exe 004c4226.  Id of the node whose 45x45 box contains pixel (x, y), or 0. */
int FindNodeAtPixel(int x, int y) {
    for (DIR_NODE *n = DirNodeTable; n->id != NODE_END; n++) {
        int a = n->gx * GRID_STEP, b = n->gy * GRID_STEP;
        /* 0x3d = GRID_ORIGIN + NODE_BOX */
        if (a + GRID_ORIGIN <= x && x < a + 0x3d && b + GRID_ORIGIN <= y && y < b + 0x3d) return n->id;
    }
    return 0;
}
/* 004c3f26 — возвращает «был включён»; enable==0 выключает (бит 4) */
/* SetNodeEnabled — Game.exe 004c3f26.  Enables (enable != 0) or disables node id.  Returns 1 if the node
   was enabled before, 0 if it was disabled or does not exist. */
int SetNodeEnabled(int id, int enable) {
    DIR_NODE *n = FindNodeById(id);
    if (!n) return 0;
    int was = (n->flags & NODE_F_DISABLED) == 0;
    if (!enable) n->flags |= NODE_F_DISABLED; else n->flags &= ~(uint32_t)NODE_F_DISABLED;
    return was;
}
/* 004c36da — для каждого узла: имя (+4, указатель Game.exe) -> иконка (+0x24) */
/* ClearDirectorTable — Game.exe 004c36da.  Resolves each node's icon: unk24 = LoadIconByName(name at
   unk04), or 0 for an empty name.  Native: names are 32-bit Game.exe pointers, so all icons are 0
   (nodes are then drawn as plain squares). */
void ClearDirectorTable(DIR_NODE *tbl) {
    for (DIR_NODE *n = tbl; n->id != NODE_END; n++) {
#ifdef RE_HOOK_BUILD
        const char *name = (const char *)(uintptr_t)n->unk04;
        n->unk24 = (strlen(name) == 0) ? 0 : (int32_t)LoadIconByName(name);
#else
        n->unk24 = 0; /* в native имя — 32-битный указатель, недоступен */
#endif
    }
}
/* Next node of a chain: link2 or link1 of cur, chosen by the FIRST node's NODE_F_LINK2 (inlined in the original). */
static DIR_NODE *NextInChain(DIR_NODE *start, DIR_NODE *cur) {
    return FindNodeById((start->flags & NODE_F_LINK2) ? cur->link2 : cur->link1);
}
/* 004c3c94 — рисует цепочку узлов (условие ветки берётся от первого узла, как в оригинале) */
/* DrawNodeChain — Game.exe 004c3c94.  Draws every node of the chain starting at start. */
void DrawNodeChain(DIR_NODE *start) {
    if (!start) return;
    for (DIR_NODE *c = start; c; c = NextInChain(start, c)) DrawNode(c);
}
/* 004c3cf1 — маркер рисуется для узла с id == DirectorUnk7C */
/* DrawNodeMarkersChain — Game.exe 004c3cf1.  Walks the chain and draws the marker of the node whose id is
   DirectorUnk7C (TODO(RE): unsure — the currently selected node, cf. DrawNode's colour). */
void DrawNodeMarkersChain(DIR_NODE *start) {
    if (!start) return;
    for (DIR_NODE *c = start; c; c = NextInChain(start, c))
        if (c->id == DirectorUnk7C) DrawNodeMarker(c);
}
/* 004c41ec — узел, на который указывает +0x18 узла id */
/* GetNodeParent — Game.exe 004c41ec.  Node referenced by field unk18 of node id (TODO(RE): "parent" is
   the Ghidra-era name; meaning of unk18 not confirmed). */
DIR_NODE *GetNodeParent(int id) {
    if (!id) return 0;
    DIR_NODE *n = FindNodeById(id);
    return n ? FindNodeById(n->unk18) : 0;
}
/* 004c37f6 — пишет в лог все путевые точки повтора (запись 12 байт: x, z, кадр) */
/* DumpWaypoints — Game.exe 004c37f6.  Debug-logs every replay waypoint (12-byte records: x, z, frame). */
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
/* DrawCornerIndicator — Game.exe 004c42a9.  While DirIndicatorOn and DirIndicatorCnt < 32, draws
   IndicatorTex at the screen corner DirectorUnk84 selects (0 top-left, 1 top-right, 2 bottom-left,
   3 bottom-right, 4 centre); the 5th DrawSprite argument picks the mirrored variant per corner. */
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
/* DrawNode — Game.exe 004c3d5c.  Draws the node's 45x45 cell: its icon scaled to the box (icon bytes
   +0xb / +0xc = width / height), or a filled square without icon; colour = DirSelectedColor for node
   DirectorUnk7C, else orange (enabled) / dark orange (disabled). */
void DrawNode(DIR_NODE *n) {
    uint32_t col = (n->id == DirectorUnk7C) ? DirSelectedColor : ((n->flags & NODE_F_DISABLED) ? COL_NODE_OFF : COL_NODE_ON);
    float x = 53.0f * (float)n->gx + 16.0f, y = 53.0f * (float)n->gy + 16.0f;
    if (n->unk24 == 0) { DrawRect(x, y, 45.0f, 45.0f, col); return; }
#ifdef RE_HOOK_BUILD
    const uint8_t *icon = (const uint8_t *)(uintptr_t)(uint32_t)n->unk24;
    GameDrawIcon(x, y, 45.0f / (float)icon[0xb], 45.0f / (float)icon[0xc], (uint32_t)n->unk24, col);
#endif
}
/* 004c3e6a — маркер узла: иконка (по unk00) в углу клетки; серый (0x40) если узел выключен, бит 1 — нижний правый угол */
/* DrawNodeMarker — Game.exe 004c3e6a.  Draws the node's marker sprite NodeIconTex[unk00] (none for -1) at
   the bottom of its cell — lower right when flag bit 0 is set (lifted by GetMarkerYAdjust), else below
   the cell; grey (0x40) when the node is disabled. */
void DrawNodeMarker(DIR_NODE *n) {
    int x = n->gx * GRID_STEP + GRID_ORIGIN, y = n->gy * GRID_STEP + GRID_ORIGIN;
    uint32_t c = (n->flags & NODE_F_DISABLED) ? 0x40 : 0xff;
    if (n->flags & NODE_F_MARK_LOW) { x += 0x31; y += 0x2d - GetMarkerYAdjust(0); }
    else y += 0x31;
    if (n->unk00 != -1) DrawSprite(x, y, NodeIconTex[n->unk00], 0, 0, c, c, c);
}

#ifndef RE_HOOK_BUILD
int32_t CamParamTblArr[0x52*4];   /* v2.03: KeyState — макрос над A_00D04B00 (dirnodes.h) */
#  define KS(a) KeyState[(a)-0x00d04b00]
#  define CPT(i) (((int32_t *)&CamParamTbl)[i])   /* v1.44: поле +0xcc таблицы машин P99_Cars */
#else
#  define KS(a) (*(uint8_t*)(uintptr_t)(a))
#  define CPT(i) (((int32_t*)(uintptr_t)0x00d0788c)[i])
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("DirUseDI")
#undef DirUseDI
#pragma push_macro("DirUseDI") /*gvi*/
#undef DirUseDI /*gvi*/
int32_t DirUseDI;
#pragma pop_macro("DirUseDI") /*gvi*/
#pragma pop_macro("DirUseDI")
#endif

/* Director key bits returned by ReadDirectorKeys. */
enum {
    DKEY_LEFT = 0x01, DKEY_RIGHT = 0x02, DKEY_UP = 0x04, DKEY_DOWN = 0x08,
    DKEY_SELECT = 0x10,   /* Enter or Space */
    DKEY_MINUS = 0x20,    /* keypad - */
    DKEY_PLUS = 0x40,     /* keypad + */
    DKEY_SHIFT = 0x80,    /* either Shift */
    DKEY_END = 0x100      /* End (keyboard-state path only) */
};

/* ReadDirectorKeys — Game.exe 004c3f8f.  Returns the DKEY_* mask of director keys held now.
   DirUseDI == 0: reads the raw keyboard state block (00d04b00 + DIK scan code) and ORs the bits.
   DirUseDI != 0: uses IsKeyDown — quirk kept: each test ASSIGNS instead of OR-ing, so only the last
   matching key survives, and End is not read.  Scan codes: 0x2a/0x36 Shift, 0x4a/0x4e keypad -/+,
   0xcb/0xcd/0xc8/0xd0 arrows, 0x1c Enter, 0x39 Space, 0xcf End. */
uint32_t ReadDirectorKeys(void) {
    uint32_t m = 0;
    if (!DirUseDI) {
        if (KS(0xd04b2a) || KS(0xd04b36)) m = 0x80;
        if (KS(0xd04b4a)) m |= 0x20;
        if (KS(0xd04b4e)) m |= 0x40;
        if (KS(0xd04bcb)) m |= 1;
        if (KS(0xd04bcd)) m |= 2;
        if (KS(0xd04bc8)) m |= 4;
        if (KS(0xd04bd0)) m |= 8;
        if (KS(0xd04b1c) || KS(0xd04b39)) m |= 0x10;
        if (KS(0xd04bcf)) m |= 0x100;
    } else {
        if (IsKeyDown(0x2a) || IsKeyDown(0x36)) m = 0x80;
        if (IsKeyDown(0x4a)) m = 0x20;
        if (IsKeyDown(0x4e)) m = 0x40;
        if (IsKeyDown(0xcb)) m = 1;
        if (IsKeyDown(0xcd)) m = 2;
        if (IsKeyDown(200)) m = 4;
        if (IsKeyDown(0xd0)) m = 8;
        if (IsKeyDown(0x1c) || IsKeyDown(0x39)) m = 0x10;
    }
    return m;
}

/* ClampCameraHeight — Game.exe 004c356d.  Keeps a director camera between 100 and 1600 units above the
   ground under it (y grows downward, so "above" = smaller y; ground = -GetGroundHeight(pos)).
   cam (int32 words): [0] mode (0 = TODO(RE): unsure, free camera?), [4] index of the followed car
   (-1 -> 0), [0x13..0x16] position (y = [0x14]), [0x17..0x1a] a second position copy,
   [0x1c] y + the followed car's y.  CPT(idx * 0x52) is int32 0x52*idx of the table at 00d0788c:
   0x52 words = 0x148 = one car record, and 00d0788c = car table 00d077c0 + 0xcc (CAR_POS_Y), so it is
   car[idx]'s world y.  Mode 0 copies the position to [0x17..] only when the clamp changed it; other
   modes clamp at the top and reset to 1700 (0x6a4) above ground when more than 1600 above.
   TODO(RE): unsure what [0x17..0x1a] and [0x1c] are used for (look-at target?). */
void ClampCameraHeight(int32_t *p) {
    if (p[4] == -1) p[4] = 0;
    int idx = p[4];
    if (p[0] == 0) {
        int old = p[0x14];
        int g = -GetGroundHeight(p + 0x13);
        if (g - 100 < p[0x14]) p[0x14] = g - 100;
        if (p[0x14] < g - 0x640) p[0x14] = g - 0x640;
        if (old != p[0x14]) {
            p[0x17] = p[0x13]; p[0x18] = p[0x14]; p[0x19] = p[0x15]; p[0x1a] = p[0x16];
            p[0x1c] = p[0x14] + CPT(idx * 0x52);
        }
    } else {
        int g = -GetGroundHeight(p + 0x13);
        int lim = g - 100;
        if (lim < p[0x14]) { p[0x1c] = lim + CPT(idx * 0x52); p[0x14] = lim; p[0x18] = lim; }
        if (p[0x14] - lim < -0x640) {
            p[0x14] = g - 0x6a4; p[0x18] = g - 0x6a4; p[0x1c] = p[0x14] + CPT(idx * 0x52);
        }
    }
}
