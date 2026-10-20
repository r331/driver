/* Блок карты в слоты и рисование объектов карты — восстановлено из Game.exe (004ed5f8, 004ee18b, 004ee4b7). */
/* ported87.c — map tiles ("lumps") streamed into four slots around the camera, and drawing of the map
   objects they contain.  English summary of ported87.h:
     slot s holds one lump: list nodes at G6_00CE0F20 + s*0x5000*8, the per-cell list heads (N x N grid,
     N = P54_GridN) at G6_00D01268 + s*N*N*4, and the lump's objects (0x20-byte records) in G6_00D00208
     from index P54_Cnt1E0 + s*0x2000.  Object indices below P54_Cnt1E0 are shared (not per slot).
   Slots form a 2x2 checkerboard: slot = (lump column & 1) + (lump row & 1) * 2. */
#include "ported87.h"
#include "ported92.h"
#include "ported131.h"
#include <string.h>

#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P87_CntA")
#undef P87_CntA
#pragma push_macro("P87_CntA") /*gvi*/
#undef P87_CntA /*gvi*/
int32_t P87_CntA;
#pragma pop_macro("P87_CntA") /*gvi*/
#pragma pop_macro("P87_CntA")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P87_CntB")
#undef P87_CntB
#pragma push_macro("P87_CntB") /*gvi*/
#undef P87_CntB /*gvi*/
int32_t P87_CntB;
#pragma pop_macro("P87_CntB") /*gvi*/
#pragma pop_macro("P87_CntB")
#endif
GAME_VAR_DEF(void **, P87_ListPtr, 0x00000000)
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P87_SlotLump")
#undef P87_SlotLump
#pragma push_macro("P87_SlotLump") /*gvi*/
#undef P87_SlotLump /*gvi*/
p87_lumps_t P87_SlotLump;
#pragma pop_macro("P87_SlotLump") /*gvi*/
#pragma pop_macro("P87_SlotLump")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P87_SlotLumpA")
#undef P87_SlotLumpA
#pragma push_macro("P87_SlotLumpA") /*gvi*/
#undef P87_SlotLumpA /*gvi*/
p87_lumps_t P87_SlotLumpA;
#pragma pop_macro("P87_SlotLumpA") /*gvi*/
#pragma pop_macro("P87_SlotLumpA")
#endif

#define TILE_SLOTS       4
#define SLOT_NODES       0x5000   /* list nodes per slot (8 bytes each: object index, next node) */
#define SLOT_OBJS        0x2000   /* object records per slot */
#define MAP_OBJ_SIZE     0x20     /* in-memory map object record (0x14 bytes on disk) */
#define MAP_OBJ_DISK     0x14
#define MAX_MODELS       1126     /* entries of P79_ModelTab */
#define MAX_LUMPS        1024     /* native guard on the lump number */
/* in-memory map object record (MAP_OBJ_SIZE bytes) */
#define OBJ_STAMP        0x00     /* u32: frame stamp; equal to P47_SwapCnt once drawn this frame */
#define OBJ_MODEL        0x04     /* int32: model index (disk u16 & 0x7fff) */
#define OBJ_POS          0x08     /* float[3]: world x, y, z */
#define OBJ_ANGLE        0x18     /* int32: rotation (index into the Euler table) */
#define OBJ_HIDDEN       0x1c     /* int32: 1 if disk bit 0x8000 was set; such objects are not drawn by P87_DrawCells */
#include "modelhdr.h"   /* model header fields (MDL_*); MDL_RADIUS is the bounding radius for P83_BoxVis */
/* model flag bits (MDL_FLAGS) read here */
#define MDLF_MISSION     0x0004   /* drawn by P131_MissionObj instead */
#define MDLF_AXIS_A      0x0010   /* with 0x20: axis-aligned fast path P92_DrawAxis when the angle is a multiple of 90 deg */
#define MDLF_AXIS_B      0x0020
#define MDLF_SPIN        0x0080   /* kind A: drawn by P92_DrawSpin */
#define MDLF_LIST_A      0x0400   /* with MDL_FLAGS2 0x80: every 16th draw registered in the P87 list (counter A) */
#define MDLF_42A423      0x2000
#define MDLF_LIST_B      0x4000   /* with MDL_FLAGS2 0x2000: registered with counter B */
#define OBJ_NONE         (-1)     /* end of a cell's object list */

#ifdef RE_HOOK_BUILD
#  define P87_LIST_END ((void **)0x00cfe7a0)
static void list_init(void) {}
#else
static void *p87_list[256];
#  define P87_LIST_END (&p87_list[256])
static void list_init(void) { if (!P87_ListPtr) P87_ListPtr = p87_list; }
#endif

static uint16_t rd16(const uint8_t *p) { uint16_t v; memcpy(&v, p, 2); return v; }
static int32_t  rd32(const uint8_t *p) { int32_t v; memcpy(&v, p, 4); return v; }
static float    rdf(const uint8_t *p) { float v; memcpy(&v, p, 4); return v; }

/* 004ed5f8 */
/* P87_LoadTile — Game.exe 004ed5f8.  Unpacks map lump `lump` (P80_LumpTab[lump], raw lump data) into
   slot `slot` (0..3):
     1. list nodes {u16 object, u16 next} -> int32 pairs; object indices >= P54_Cnt1E0 get + slot*0x2000,
        next gets + slot*0x5000, 0xffff -> -1;
     2. cell list heads, stored in one of three encodings: 0 = all empty, 1 = one u16 per cell,
        2 = 16-cell bit masks (bit 15 first) followed by a u16 for each set bit;
     3. object records (0x14 on disk -> 0x20 in memory, stamped with P44_XformTag);
     4. P87_SlotLump[slot] = lump, and the road maps of the tile row (P70_RowDecode, P62_MapRow; the
        row index is flipped vertically: rows are stored bottom-up).
   Native: bounds/NULL guards at the top that the original does not have. */
void P87_LoadTile(int32_t lump, int32_t slot) {
  if (lump < 0 || lump > P76_NumSlots || lump >= MAX_LUMPS || slot < 0 || slot > TILE_SLOTS - 1) return;
  if (!P80_LumpTab[lump] || !G6_00CE0F20 || !G6_00D01268 || !G6_00D00208 || P54_GridN <= 0) return;   /* охранные проверки — в оригинале их нет */
  P87_SlotLumpA[slot] = lump;                                 /* 00d00220[slot] */
  const uint8_t *cur = (const uint8_t *)P80_LumpTab[lump];
  int32_t n = rd32(cur); cur += 4;
  uint8_t *nodes = (uint8_t *)G6_00CE0F20 + (size_t)slot * 0x28000;   /* SLOT_NODES * 8 bytes */
  if (n != 0) {
    for (int32_t i = 0; i < n; i++) {
      uint32_t a = rd16(cur + i * 4), b = rd16(cur + i * 4 + 2);   /* a = object index, b = next node */
      uint32_t na = a, nb = b == 0xffff ? 0xffffffffu : b;
      if ((int32_t)na >= P54_Cnt1E0) na += (uint32_t)slot * SLOT_OBJS;
      if (nb != 0xffffffffu) nb += (uint32_t)slot * SLOT_NODES;
      memcpy(nodes + (size_t)i * 8, &na, 4); memcpy(nodes + (size_t)i * 8 + 4, &nb, 4);
    }
  }
  cur += (size_t)n * 4;
  int32_t sz = rd32(cur);                /* byte size of the cell-head block (encoding byte included) */
  uint8_t kind = cur[4];                 /* cell-head encoding 0 / 1 / 2 */
  const uint8_t *cd = cur + 5;
  const uint8_t *after = cur + 4 + sz;
  int32_t N = P54_GridN, cells = N * N;
  int32_t *heads = (int32_t *)G6_00D01268 + (size_t)slot * cells;
  if (kind == 0) {
    for (int32_t i = 0; i < cells; i++) heads[i] = -1;
  } else if (kind == 1) {
    for (int32_t i = 0; i < cells; i++) { uint16_t v = rd16(cd + i * 2); heads[i] = v == 0xffff ? -1 : (int32_t)v + slot * SLOT_NODES; }
  } else if (kind == 2) {
    /* sparse: a u16 mask per 16 cells (MSB = first cell); a set bit is followed by that cell's head */
    uint32_t bit = 0x8000; int16_t mask = (int16_t)rd16(cd); cd = cur + 7;
    for (int32_t i = 0; i < cells; i++) {
      int32_t v;
      if (((int32_t)mask & bit) == 0) v = -1;
      else { v = (int32_t)rd16(cd) + slot * SLOT_NODES; cd += 2; }
      heads[i] = v;
      bit = (uint32_t)((int32_t)bit >> 1);
      if (bit == 0) { bit = 0x8000; mask = (int16_t)rd16(cd); cd += 2; }
    }
  }
  int32_t cnt = rd32(after); const uint8_t *rec = after + 4;
  if (cnt != 0) {
    uint8_t *o = (uint8_t *)G6_00D00208 + (size_t)(P54_Cnt1E0 + slot * SLOT_OBJS) * MAP_OBJ_SIZE;
    /* disk record: +0 u16 model | 0x8000 hidden, +4/+8/+0xc float x, y, z, +0x10 int16 angle */
    for (int32_t i = 0; i < cnt; i++, rec += MAP_OBJ_DISK, o += MAP_OBJ_SIZE) {
      uint32_t stamp = P44_XformTag; uint16_t m = rd16(rec); uint32_t mi = m & 0x7fff; int32_t ang = (int16_t)rd16(rec + 0x10), flag = (m & 0x8000) ? 1 : 0;
      memset(o, 0, MAP_OBJ_SIZE);
      memcpy(o + OBJ_STAMP, &stamp, 4); memcpy(o + OBJ_MODEL, &mi, 4);
      memcpy(o + OBJ_POS, rec + 4, 4); memcpy(o + OBJ_POS + 4, rec + 8, 4); memcpy(o + OBJ_POS + 8, rec + 0xc, 4);
      memcpy(o + OBJ_ANGLE, &ang, 4); memcpy(o + OBJ_HIDDEN, &flag, 4);
    }
  }
  P87_SlotLump[slot] = lump;                                  /* 00c39da0[slot] */
  {
    /* lump index with its row mirrored (P72_Rows - 1 - row), column kept */
    int32_t cols = P80_Cols, row = (P72_Rows - 1 - (lump - lump % cols) / cols) * cols + lump % cols;
    if (P54_RoadA[slot]) P70_RowDecode(row, (int16_t *)P54_RoadA[slot]);
    if (P54_RoadB[slot]) P62_MapRow(row, (int32_t *)P54_RoadB[slot]);
  }
}

/* общая часть 004ee18b / 004ee4b7; kind 0 — A (004ee18b), 1 — B (004ee4b7) */
/* Draws one map object record.  Steps: model lookup, visibility test P83_BoxVis (0 = culled, 1 / 2 =
   visible, 2 apparently "needs clipping"), mission objects go to P131_MissionObj, optional registration
   of every 16th draw in the P87_ListPtr list, camera-relative position -> view space (P44_Xform), then
   one of the model drawers chosen by model flags and visibility; the model matrix pointer is reset to
   the view matrix afterwards.  Draw mode: 0 = no clip, 1 = clip, 2 = far/large (radius box >= 200).
   TODO(RE): unsure about the exact meaning of modes and of the list at 00562d7c. */
static void draw_obj(const uint8_t *obj, int kind) {
  int32_t mi = rd32(obj + OBJ_MODEL);
  if (mi < 0 || mi >= MAX_MODELS) return;
  uint32_t mref = P79_ModelTab[mi];
  if (!mref) return;
  const uint8_t *mdl = (const uint8_t *)P79_PTR(mref);
  int32_t vis = P83_BoxVis((const float *)(obj + OBJ_POS), rdf(mdl + MDL_RADIUS));
  if (vis == 0) return;
  uint32_t flags = rd16(mdl + MDL_FLAGS);
  if (flags & MDLF_MISSION) {
    P131_MissionObj(mref, (const uint8_t *)obj, vis);
    P44_MatPtr = (float *)P44_ViewMatT;
    return;
  }
  uint32_t mflags = (uint32_t)rd32(mdl + MDL_FLAGS2);
  list_init();
  if ((flags & MDLF_LIST_B) == 0 || (mflags & 0x2000) == 0) {
    if ((flags & MDLF_LIST_A) != 0 && (mflags & 0x80) != 0) {
      uint32_t t = (uint32_t)P87_CntA & 0xf; P87_CntA++;
      if (t == 0 && P87_ListPtr < P87_LIST_END) *P87_ListPtr++ = (void *)obj;
    }
  } else {
    uint32_t t = (uint32_t)P87_CntB & 0xf; P87_CntB++;
    if (t == 0 && P87_ListPtr < P87_LIST_END) *P87_ListPtr++ = (void *)obj;
  }
  float p[3]; p[0] = rdf(obj + OBJ_POS) - P44_CamX; p[1] = rdf(obj + OBJ_POS + 4) - P44_CamY; p[2] = rdf(obj + OBJ_POS + 8) - P44_CamZ;
  P44_Xform(p);
  int32_t ang = rd32(obj + OBJ_ANGLE);
  int32_t low = ((int32_t *)P80_Boxes[mi])[7] < 200;           /* 00cf56fc + модель·0x20 */
  if (kind == 0 && (flags & MDLF_SPIN)) {
    P92_DrawSpin(mref, ang, p, vis == 2 ? 1 : 0);   /* 0042a5de */
  } else if (kind == 1 && (flags & MDLF_LIST_B) == 0 && (flags & (MDLF_42A423 | MDLF_LIST_A)) != 0 && rd16(mdl + MDL_NRECS) == 1) {
    P87_Fn42A423(mref, ang, p, vis == 1 ? 0 : vis == 2 ? 1 : 0);
  } else {
    int32_t mode = vis == 1 ? 0 : vis == 2 ? 1 : (low ? 0 : 2);
    if ((flags & MDLF_LIST_B) == 0 && (ang & 0x3ff) == 0 && (flags & (MDLF_AXIS_A | MDLF_AXIS_B)) != 0) P92_DrawAxis(mref, ang, p, mode);   /* 0042982e */
    else P84_DrawModelIdx(mref, ang, p, mode);
  }
  P44_MatPtr = (float *)P44_ViewMatT;
}
/* P87_DrawObjA — Game.exe 004ee18b: draw_obj kind A (spinning models allowed).
   P87_DrawObjB — Game.exe 004ee4b7: draw_obj kind B (P87_Fn42A423 path allowed). */
void P87_DrawObjA(const uint8_t *obj) { draw_obj(obj, 0); }   /* 004ee18b */
void P87_DrawObjB(const uint8_t *obj) { draw_obj(obj, 1); }   /* 004ee4b7 */

/* P87_DrawCells — no Game.exe address (native helper; no caller in the tree at 1274c40).  Draws the map
   objects of the (2r+1)^2 grid cells around cell (cx, cy): for each cell whose lump is resident in its
   slot, walks the cell's object list and draws each visible object once per frame (stamp vs
   P47_SwapCnt; hidden objects skipped) — class 1 / 7 as kind B, class 4 as kind A (P80_Class).
   Returns the number of objects drawn.  Native guards against corrupt lists are marked below. */
int32_t P87_DrawCells(int32_t cx, int32_t cy, int32_t r) {
  int32_t N = P54_GridN, W = P21_GridDiv, H = P80_GridH, drawn = 0;
  if (N <= 0) return 0;
  P44_MatPtr = (float *)P44_ViewMatT;
  for (int32_t y = cy - r; y <= cy + r; y++) {
    for (int32_t x = cx - r; x <= cx + r; x++) {
      if (x < 0 || y < 0 || x >= W || y >= H) continue;
      int32_t slot = ((x / N) & 1) + ((y / N) & 1) * 2;
      int32_t lump = (y / N) * P80_Cols + x / N;
      if (P87_SlotLump[slot] != lump) continue;
      int32_t node = ((int32_t *)G6_00D01268)[slot * N * N + (x % N) + (y % N) * N];
      for (int32_t guard = 0; node != OBJ_NONE && node >= 0 && node < TILE_SLOTS * SLOT_NODES && guard < SLOT_NODES; guard++) {   /* охранные проверки — в оригинале их нет */
        const int32_t *nd = (const int32_t *)((uint8_t *)G6_00CE0F20 + (size_t)node * 8);
        if (nd[0] < 0 || nd[0] >= P54_Cnt1E0 + TILE_SLOTS * SLOT_OBJS) break;
        uint8_t *o = (uint8_t *)G6_00D00208 + (size_t)nd[0] * MAP_OBJ_SIZE;
        uint32_t stamp = (uint32_t)rd32(o + OBJ_STAMP);
        if (stamp != (uint32_t)P47_SwapCnt && rd32(o + OBJ_HIDDEN) == 0) {
          int32_t mi = rd32(o + OBJ_MODEL);
          if (mi >= 0 && mi < MAX_MODELS) {
            uint8_t cls = P80_Class[mi];
            if (cls == 1 || cls == 7) { draw_obj(o, 1); drawn++; }
            else if (cls == 4) { draw_obj(o, 0); drawn++; }
          }
          { uint32_t sc = (uint32_t)P47_SwapCnt; memcpy(o, &sc, 4); }
        }
        node = nd[1];
      }
    }
  }
  return drawn;
}
