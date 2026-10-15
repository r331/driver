/* Блок карты в слоты и рисование объектов карты — восстановлено из Game.exe (004ed5f8, 004ee18b, 004ee4b7). */
#include "ported87.h"
#include "ported92.h"
#include <string.h>

GAME_VAR_DEF(int32_t, P87_CntA, 0x00b31edc)
GAME_VAR_DEF(int32_t, P87_CntB, 0x00d022e0)
GAME_VAR_DEF(void **, P87_ListPtr, 0x00562d7c)
GAME_VAR_DEF(p87_lumps_t, P87_SlotLump, 0x00c39da0)
GAME_VAR_DEF(p87_lumps_t, P87_SlotLumpA, 0x00d00220)

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
void P87_LoadTile(int32_t lump, int32_t slot) {
  if (lump < 0 || lump > P76_NumSlots || lump >= 1024 || slot < 0 || slot > 3) return;
  if (!P80_LumpTab[lump] || !G6_00CE0F20 || !G6_00D01268 || !G6_00D00208 || P54_GridN <= 0) return;   /* охранные проверки — в оригинале их нет */
  P87_SlotLumpA[slot] = lump;                                 /* 00d00220[slot] */
  const uint8_t *cur = (const uint8_t *)P80_LumpTab[lump];
  int32_t n = rd32(cur); cur += 4;
  uint8_t *nodes = (uint8_t *)G6_00CE0F20 + (size_t)slot * 0x28000;
  if (n != 0) {
    for (int32_t i = 0; i < n; i++) {
      uint32_t a = rd16(cur + i * 4), b = rd16(cur + i * 4 + 2);
      uint32_t na = a, nb = b == 0xffff ? 0xffffffffu : b;
      if ((int32_t)na >= P54_Cnt1E0) na += (uint32_t)slot * 0x2000;
      if (nb != 0xffffffffu) nb += (uint32_t)slot * 0x5000;
      memcpy(nodes + (size_t)i * 8, &na, 4); memcpy(nodes + (size_t)i * 8 + 4, &nb, 4);
    }
  }
  cur += (size_t)n * 4;
  int32_t sz = rd32(cur);
  uint8_t kind = cur[4];
  const uint8_t *cd = cur + 5;
  const uint8_t *after = cur + 4 + sz;
  int32_t N = P54_GridN, cells = N * N;
  int32_t *heads = (int32_t *)G6_00D01268 + (size_t)slot * cells;
  if (kind == 0) {
    for (int32_t i = 0; i < cells; i++) heads[i] = -1;
  } else if (kind == 1) {
    for (int32_t i = 0; i < cells; i++) { uint16_t v = rd16(cd + i * 2); heads[i] = v == 0xffff ? -1 : (int32_t)v + slot * 0x5000; }
  } else if (kind == 2) {
    uint32_t bit = 0x8000; int16_t mask = (int16_t)rd16(cd); cd = cur + 7;
    for (int32_t i = 0; i < cells; i++) {
      int32_t v;
      if (((int32_t)mask & bit) == 0) v = -1;
      else { v = (int32_t)rd16(cd) + slot * 0x5000; cd += 2; }
      heads[i] = v;
      bit = (uint32_t)((int32_t)bit >> 1);
      if (bit == 0) { bit = 0x8000; mask = (int16_t)rd16(cd); cd += 2; }
    }
  }
  int32_t cnt = rd32(after); const uint8_t *rec = after + 4;
  if (cnt != 0) {
    uint8_t *o = (uint8_t *)G6_00D00208 + (size_t)(P54_Cnt1E0 + slot * 0x2000) * 0x20;
    for (int32_t i = 0; i < cnt; i++, rec += 0x14, o += 0x20) {
      uint32_t stamp = P44_XformTag; uint16_t m = rd16(rec); uint32_t mi = m & 0x7fff; int32_t ang = (int16_t)rd16(rec + 0x10), flag = (m & 0x8000) ? 1 : 0;
      memset(o, 0, 0x20);
      memcpy(o, &stamp, 4); memcpy(o + 4, &mi, 4);
      memcpy(o + 8, rec + 4, 4); memcpy(o + 0xc, rec + 8, 4); memcpy(o + 0x10, rec + 0xc, 4);
      memcpy(o + 0x18, &ang, 4); memcpy(o + 0x1c, &flag, 4);
    }
  }
  P87_SlotLump[slot] = lump;                                  /* 00c39da0[slot] */
  {
    int32_t cols = P80_Cols, row = (P72_Rows - 1 - (lump - lump % cols) / cols) * cols + lump % cols;
    if (P54_RoadA[slot]) P70_RowDecode(row, (int16_t *)P54_RoadA[slot]);
    if (P54_RoadB[slot]) P62_MapRow(row, (int32_t *)P54_RoadB[slot]);
  }
}

/* общая часть 004ee18b / 004ee4b7; kind 0 — A (004ee18b), 1 — B (004ee4b7) */
static void draw_obj(const uint8_t *obj, int kind) {
  int32_t mi = rd32(obj + 4);
  if (mi < 0 || mi >= 1126) return;
  uint32_t mref = P79_ModelTab[mi];
  if (!mref) return;
  const uint8_t *mdl = (const uint8_t *)P79_PTR(mref);
  int32_t vis = P83_BoxVis((const float *)(obj + 8), rdf(mdl + 0xc));
  if (vis == 0) return;
  uint32_t flags = rd16(mdl + 2);
  if (flags & 4) {
    P87_Fn4FEF26(mref, obj, vis);
    P44_MatPtr = (float *)P44_ViewMatT;
    return;
  }
  uint32_t mflags = (uint32_t)rd32(mdl + 8);
  list_init();
  if ((flags & 0x4000) == 0 || (mflags & 0x2000) == 0) {
    if ((flags & 0x400) != 0 && (mflags & 0x80) != 0) {
      uint32_t t = (uint32_t)P87_CntA & 0xf; P87_CntA++;
      if (t == 0 && P87_ListPtr < P87_LIST_END) *P87_ListPtr++ = (void *)obj;
    }
  } else {
    uint32_t t = (uint32_t)P87_CntB & 0xf; P87_CntB++;
    if (t == 0 && P87_ListPtr < P87_LIST_END) *P87_ListPtr++ = (void *)obj;
  }
  float p[3]; p[0] = rdf(obj + 8) - P44_CamX; p[1] = rdf(obj + 0xc) - P44_CamY; p[2] = rdf(obj + 0x10) - P44_CamZ;
  P44_Xform(p);
  int32_t ang = rd32(obj + 0x18);
  int32_t low = ((int32_t *)P80_Boxes[mi])[7] < 200;           /* 00cf56fc + модель·0x20 */
  if (kind == 0 && (flags & 0x80)) {
    P92_DrawSpin(mref, ang, p, vis == 2 ? 1 : 0);   /* 0042a5de */
  } else if (kind == 1 && (flags & 0x4000) == 0 && (flags & 0x2400) != 0 && rd16(mdl + 0x16) == 1) {
    P87_Fn42A423(mref, ang, p, vis == 1 ? 0 : vis == 2 ? 1 : 0);
  } else {
    int32_t mode = vis == 1 ? 0 : vis == 2 ? 1 : (low ? 0 : 2);
    if ((flags & 0x4000) == 0 && (ang & 0x3ff) == 0 && (flags & 0x30) != 0) P92_DrawAxis(mref, ang, p, mode);   /* 0042982e */
    else P84_DrawModelIdx(mref, ang, p, mode);
  }
  P44_MatPtr = (float *)P44_ViewMatT;
}
void P87_DrawObjA(const uint8_t *obj) { draw_obj(obj, 0); }   /* 004ee18b */
void P87_DrawObjB(const uint8_t *obj) { draw_obj(obj, 1); }   /* 004ee4b7 */

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
      for (int32_t guard = 0; node != -1 && node >= 0 && node < 4 * 0x5000 && guard < 0x5000; guard++) {   /* охранные проверки — в оригинале их нет */
        const int32_t *nd = (const int32_t *)((uint8_t *)G6_00CE0F20 + (size_t)node * 8);
        if (nd[0] < 0 || nd[0] >= P54_Cnt1E0 + 4 * 0x2000) break;
        uint8_t *o = (uint8_t *)G6_00D00208 + (size_t)nd[0] * 0x20;
        uint32_t stamp = (uint32_t)rd32(o);
        if (stamp != (uint32_t)P47_SwapCnt && rd32(o + 0x1c) == 0) {
          int32_t mi = rd32(o + 4);
          if (mi >= 0 && mi < 1126) {
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
