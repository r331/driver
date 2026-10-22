/* ported89.c — map cell visibility masks and the main walk over visible map cells (English overview;
   original notes follow).
   The city is a grid of cells grouped into tiles of N x N cells (N = P54_GridN); 4 tiles are resident in
   slots chosen by tile parity.  Each frame P89_DrawMap takes the 31x31 window of cells around the camera,
   keeps those inside the view wedge of the heading sector (FRUSTRUM.DAT) and the precomputed
   visibility mask (P89_VisMask -> P82_LightGrid), and sorts the objects of each cell into draw lists
   by class (put_obj).  Native additions: Hor+ widening (v2.15) and draw_distance > 1 (v2.19) walk extra
   cells, the latter from a draw-only cache of non-resident tiles (dd_*). */
/* Маска видимости клеток и главный обход клеток карты — восстановлено из Game.exe (004ef997, 004ef793, 004ee8f4). */
#include "redbg.h"
#include "ported89.h"
#include "aspect.h"
#include "drawdist.h"
#include <stdio.h>
#include "ported13.h"
#include <string.h>
#include <stdlib.h>
#include <math.h>

#ifdef RE_HOOK_BUILD
#  define P89_STD __attribute__((stdcall))
#else
#  define P89_STD
#endif

#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P89_CntShadow")
#undef P89_CntShadow
#pragma push_macro("P89_CntShadow") /*gvi*/
#undef P89_CntShadow /*gvi*/
int32_t P89_CntShadow;
#pragma pop_macro("P89_CntShadow") /*gvi*/
#pragma pop_macro("P89_CntShadow")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P89_CntFour")
#undef P89_CntFour
#pragma push_macro("P89_CntFour") /*gvi*/
#undef P89_CntFour /*gvi*/
int32_t P89_CntFour;
#pragma pop_macro("P89_CntFour") /*gvi*/
#pragma pop_macro("P89_CntFour")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P89_CntSeven")
#undef P89_CntSeven
#pragma push_macro("P89_CntSeven") /*gvi*/
#undef P89_CntSeven /*gvi*/
int32_t P89_CntSeven;
#pragma pop_macro("P89_CntSeven") /*gvi*/
#pragma pop_macro("P89_CntSeven")
#endif
GAME_VAR_DEF(p89_list4_t, P89_ListShadow, 0x00c97a40)
GAME_VAR_DEF(p89_list4_t, P89_ListFour, 0x00cf1f80)
GAME_VAR_DEF(p89_list2_t, P89_ListSeven, 0x00cff9e0)

/* 004ef997 */
/* P89_Fill1 — Game.exe 004ef997.  Marks all cells of the visibility mask visible (D_00d00204 bytes of 1). */
void P89_Fill1(uint8_t *out) {
  for (int32_t i = 0; i < D_00d00204; i++) *out++ = 1;
}

/* 004ef793 */
/* P89_VisMask — Game.exe 004ef793.  Decodes the visibility mask of cell `cell_in_tile` of tile `tile` from the
   map's visibility data (P46_MapBufA): offset table per tile, then per cell a run-length stream of
   {runs of 8 visible cells, n literal bytes of 8 bits each}.  No data -> everything visible.
   Native: stops on a malformed stream instead of underflowing the counter. */
void P89_VisMask(int32_t tile, int32_t cell_in_tile, uint8_t *out) {
  const uint8_t *base = (const uint8_t *)P46_MapBufA;
  if (base == NULL) { P89_Fill1(out); return; }
  uint32_t off, v;
  memcpy(&off, base + 0x10 + (size_t)tile * 4, 4);
  const uint8_t *tab = base + off;
  memcpy(&v, tab + (size_t)cell_in_tile * 4, 4);
  const uint8_t *p = tab + (v & 0x3fffffffu);
  if (p == tab) { P89_Fill1(out); return; }
  uint32_t left = (uint32_t)D_00d00204;
  if ((left & 7) != 0) left++;
  while (left != 0) {
    uint8_t run_bytes = *p;
    const uint8_t *lit_cnt_p = p + 1;
    if ((uint32_t)run_bytes * 8 > left) return;               /* охранная проверка: в оригинале счётчик ушёл бы ниже нуля */
    left -= (uint32_t)run_bytes * 8;
    for (; run_bytes != 0; run_bytes--) { memset(out, 1, 8); out += 8; }
    if (left == 0) return;
    p += 2;
    for (uint8_t lit_bytes = *lit_cnt_p; lit_bytes != 0; lit_bytes--) {
      uint8_t bits = *p++;
      for (int k = 0; k < 8; k++) {
        *out++ = (uint8_t)(bits & 1);
        left--;
        if (left == 0) break;
        bits >>= 1;
      }
      if (left == 0) return;                            /* охранная проверка: оригинал продолжил бы с rest = 0xffffffff */
    }
  }
}

/* glide_proc / alpha_combine / alpha_test — local helpers: call grAlphaCombine / grAlphaTestFunction from the
   loaded Glide DLL. */
static void *glide_proc(const char *name) {
  for (int i = 0; i < P33_GlideCount(); i++)
    if (strcmp(P33_GlideName(i), name) == 0) return P33_GlideProc(i);
  return NULL;
}
static void alpha_combine(int32_t a, int32_t b, int32_t c, int32_t d, int32_t e) {
  void (P89_STD *f)(int32_t, int32_t, int32_t, int32_t, int32_t) = (void (P89_STD *)(int32_t, int32_t, int32_t, int32_t, int32_t))glide_proc("_grAlphaCombine@20");
  if (f) f(a, b, c, d, e);
}
static void alpha_test(int32_t a) {
  void (P89_STD *f)(int32_t) = (void (P89_STD *)(int32_t))glide_proc("_grAlphaTestFunction@4");
  if (f) f(a);
}

#include "memrw.h"
/* Draw class of a map object model (P80_Class[model]); decides when put_obj draws it. */
enum {
  OBJ_CLASS_DIRECT   = 1,   /* drawn at once (P87_DrawObjB) */
  OBJ_CLASS_LIST_A   = 2,   /* queued in P55_TabA, drawn by the caller later */
  OBJ_CLASS_SHADOW   = 3,   /* queued; drawn last, alpha-blended, lifted 4 units, by day only */
  OBJ_CLASS_ALPHA    = 4,   /* queued; drawn with alpha test (cut-out textures) */
  OBJ_CLASS_OPTIONAL = 5,   /* drawn at once only when 00575ee8 is set (Detail menu 0054a470 entry 13 "Transparent Water", MenuToggle575EE8Redraw; label by text order, inferred) */
  OBJ_CLASS_LIST_B   = 6,   /* queued in P55_TabB */
  OBJ_CLASS_SEVEN    = 7    /* queued; drawn first with render state 0x13.  TODO(RE): unsure what they are */
};
/* Glide GrCmpFnc_t values used for grAlphaTestFunction */
enum { GR_CMP_GREATER = 4, GR_CMP_ALWAYS = 7 };

/* rd16s — local helper: unaligned int16 read. */

/* разложить объект o по классам (общая часть обоих ветвей 004ee8f4) */
/* put_obj — local helper (shared by both walks of 004ee8f4): unless object o was already handled this frame
   (stamp = swap counter) or is hidden (+0x1c), draws or queues it by the class of its model; `guarded`
   adds list-size checks (native). */
static void put_obj(uint8_t *o, int guarded) {
  uint32_t stamp = (uint32_t)rd32(o);
  if (stamp != (uint32_t)P47_SwapCnt && rd32(o + 0x1c) == 0) {
    int32_t model = rd32(o + 4);
    if (model >= 0 && model < 1126 && S_00BDCD00[model] != 0) {
      switch (P80_Class[model]) {
      case OBJ_CLASS_DIRECT: P87_DrawObjB(o); break;
      case OBJ_CLASS_LIST_A: if (!guarded || P55_CntA < 0x400) { P55_TabA[P55_CntA] = o; P55_CntA++; } break;
      case OBJ_CLASS_SHADOW: if (!guarded || P89_CntShadow < 0x400) { P89_ListShadow[P89_CntShadow] = o; P89_CntShadow++; } break;
      case OBJ_CLASS_ALPHA: if (!guarded || P89_CntFour < 0x400) { P89_ListFour[P89_CntFour] = o; P89_CntFour++; } break;
      case OBJ_CLASS_OPTIONAL: if (P13_00575ee8 != 0) P87_DrawObjB(o); break;
      case OBJ_CLASS_LIST_B: if (!guarded || P55_CntB < 0x400) { P55_TabB[P55_CntB] = o; P55_CntB++; } break;
      case OBJ_CLASS_SEVEN: if (!guarded || P89_CntSeven < 0x200) { P89_ListSeven[P89_CntSeven] = o; P89_CntSeven++; } break;
      default: break;
      }
    }
    { uint32_t sc = (uint32_t)P47_SwapCnt; memcpy(o, &sc, 4); }
  }
}

/* разложить объекты клетки с головой списка node по классам */
/* walk_cell — local helper: puts every object of one cell (linked node list starting at `node`).
   Native: index and loop guards. */
static void walk_cell(int32_t node, int guarded) {
  int guard = 0;
  RE_DBG(7);
  while (node != -1) {
    if (node < 0 || node >= 4 * 0x5000 || ++guard > 0x5000) return;              /* охранные проверки — в оригинале их нет */
    const int32_t *node_rec = (const int32_t *)((const uint8_t *)G6_00CE0F20 + (size_t)node * 8);
    if (node_rec[0] < 0 || node_rec[0] >= P54_Cnt1E0 + 4 * 0x2000) return;
    put_obj((uint8_t *)G6_00D00208 + (size_t)node_rec[0] * 0x20, guarded);
    node = node_rec[1];
  }
}

#ifndef RE_HOOK_BUILD
/* ---- v2.19 draw_distance: кэш блоков карты только для отрисовки ----
   Игра держит 4 слота блоков (2×2 по чётности, P87_LoadTile 004ed5f8) и подгружает соседа за 20 клеток до края блока (P88_StreamTiles);
   блок — P54_GridN клеток (Майами: 60 = 180000 единиц). Дальние клетки при draw_distance > 1 могут лежать в блоке, которого нет в слотах:
   такой блок разбирается из уже загруженного в память списка P80_LumpTab (без чтения файла) в свой буфер — копия разбора 004ed5f8 без
   дорожных данных (P70_RowDecode/P62_MapRow для ИИ) и без записи в слоты игры: что загружено для логики, не меняется.
   Не больше DD_LOADS блоков за кадр (предзагрузка на DD_PRE клеток дальше радиуса), кэш DD_CACHE блоков, вытеснение — давно не нужные. */
#define DD_CACHE 16
#define DD_LOADS 2
#define DD_PRE   6
typedef struct { int32_t lump; uint32_t used; int32_t nobj, nnode; uint8_t *nodes, *objs; int32_t *heads; } dd_blk;
static dd_blk g_dd[DD_CACHE];
static uint32_t g_dd_tick;
static uintptr_t g_dd_key[4];
int32_t re_dd_loads;                                   /* счётчик разобранных блоков (лог RE_DDLOG) */

/* dd_* — native only (v2.19 draw_distance): a cache of up to DD_CACHE extra tiles decoded from the level's
   lump table for drawing only (no road data, game slots untouched), loaded at most DD_LOADS per frame,
   nearest first.  dd_reset clears it; dd_find looks a tile up; dd_load decodes one (copy of the parse in
   004ed5f8); dd_resident tests the game's slots; dd_stream marks/loads the tiles around a cell; dd_walk
   and dd_cell put the objects of a cached cell; dd_cur_radius gives the walk radius for the far plane;
   re_dd_warm preloads everything (render check / first frame); dd_extend walks the cells beyond the
   original 31x31 window, nearest first. */
static void dd_reset(void) { for (int i = 0; i < DD_CACHE; i++) g_dd[i].lump = -1; }
static dd_blk *dd_find(int32_t lump) {
  for (int i = 0; i < DD_CACHE; i++) if (g_dd[i].lump == lump && g_dd[i].nodes) return &g_dd[i];
  return NULL;
}
static int dd_load(dd_blk *b, int32_t lump) {
  int32_t N = P54_GridN, cells = N * N;
  if (lump < 0 || lump > P76_NumSlots || lump >= 1024 || !P80_LumpTab[lump] || N <= 0) return 0;
  if (!b->nodes) { b->nodes = (uint8_t *)malloc(0x5000 * 8); b->objs = (uint8_t *)malloc(0x2000 * 0x20); }
  b->heads = (int32_t *)realloc(b->heads, (size_t)cells * 4);
  if (!b->nodes || !b->objs || !b->heads) return 0;
  const uint8_t *cur = (const uint8_t *)P80_LumpTab[lump];
  int32_t n = rd32(cur); cur += 4;
  if (n < 0 || n > 0x5000) return 0;
  for (int32_t i = 0; i < n; i++) {
    uint32_t a = (uint32_t)(uint16_t)rds16(cur + i * 4), nb = (uint32_t)(uint16_t)rds16(cur + i * 4 + 2);
    int32_t na = (int32_t)a, nx = nb == 0xffff ? -1 : (int32_t)nb;
    memcpy(b->nodes + (size_t)i * 8, &na, 4); memcpy(b->nodes + (size_t)i * 8 + 4, &nx, 4);
  }
  b->nnode = n;
  cur += (size_t)n * 4;
  int32_t sz = rd32(cur);
  uint8_t kind = cur[4];
  const uint8_t *cd = cur + 5, *after = cur + 4 + sz;
  if (kind == 1) {
    for (int32_t i = 0; i < cells; i++) { uint16_t v = (uint16_t)rds16(cd + i * 2); b->heads[i] = v == 0xffff ? -1 : (int32_t)v; }
  } else if (kind == 2) {
    uint32_t bit = 0x8000; int16_t mask = rds16(cd); cd = cur + 7;
    for (int32_t i = 0; i < cells; i++) {
      int32_t v;
      if (((int32_t)mask & bit) == 0) v = -1;
      else { v = (int32_t)(uint16_t)rds16(cd); cd += 2; }
      b->heads[i] = v;
      bit = (uint32_t)((int32_t)bit >> 1);
      if (bit == 0) { bit = 0x8000; mask = rds16(cd); cd += 2; }
    }
  } else {
    for (int32_t i = 0; i < cells; i++) b->heads[i] = -1;
  }
  int32_t cnt = rd32(after); const uint8_t *rec = after + 4;
  if (cnt < 0) cnt = 0;
  if (cnt > 0x2000) cnt = 0x2000;
  for (int32_t i = 0; i < cnt; i++, rec += 0x14) {
    uint8_t *o = b->objs + (size_t)i * 0x20;
    uint32_t stamp = P44_XformTag; uint16_t m = (uint16_t)rds16(rec); uint32_t mi = m & 0x7fff;
    int32_t ang = rds16(rec + 0x10), flag = (m & 0x8000) ? 1 : 0;
    memset(o, 0, 0x20);
    memcpy(o, &stamp, 4); memcpy(o + 4, &mi, 4);
    memcpy(o + 8, rec + 4, 4); memcpy(o + 0xc, rec + 8, 4); memcpy(o + 0x10, rec + 0xc, 4);
    memcpy(o + 0x18, &ang, 4); memcpy(o + 0x1c, &flag, 4);
  }
  b->nobj = cnt;
  b->lump = lump;
  re_dd_loads++;
  return 1;
}
static int dd_resident(int32_t lump) {
  for (int s = 0; s < 4; s++) if (P87_SlotLump[s] == lump) return 1;
  return 0;
}
/* блоки, пересекающие квадрат ±(R + DD_PRE) вокруг клетки (cx, cy): отметить нужными, недостающие — разобрать (ближние раньше) */
static void dd_stream(int32_t cx, int32_t cy, int32_t R) {
  int32_t N = P54_GridN, cols = P80_Cols, rows = P72_Rows;
  uintptr_t key[4] = { (uintptr_t)P80_LumpTab[0], (uintptr_t)N, (uintptr_t)P21_GridDiv, (uintptr_t)P54_Cnt1E0 };
  if (memcmp(key, g_dd_key, sizeof key) != 0) { memcpy(g_dd_key, key, sizeof key); dd_reset(); }
  if (N <= 0 || cols <= 0 || rows <= 0) return;
  g_dd_tick++;
  int32_t r = R + DD_PRE;
  int32_t bx0 = (cx - r) / N, bx1 = (cx + r) / N, by0 = (cy - r) / N, by1 = (cy + r) / N;
  if (cx - r < 0) bx0 = 0;
  if (cy - r < 0) by0 = 0;
  if (bx1 >= cols) bx1 = cols - 1;
  if (by1 >= rows) by1 = rows - 1;
  int loads = 0;
  for (int pass = 0; pass < 2; pass++)
    for (int32_t by = by0; by <= by1; by++)
      for (int32_t bx = bx0; bx <= bx1; bx++) {
        int32_t lump = by * cols + bx;
        if (dd_resident(lump)) continue;
        dd_blk *b = dd_find(lump);
        if (b) { b->used = g_dd_tick; continue; }
        /* первый проход — блок клетки камеры и соседние по стороне (ближние), второй — остальные */
        int near_blk = (bx == cx / N || by == cy / N);
        if ((pass == 0) != near_blk || loads >= DD_LOADS) continue;
        int best = -1; uint32_t bu = 0xffffffffu;
        for (int i = 0; i < DD_CACHE; i++) {
          if (g_dd[i].lump < 0 || !g_dd[i].nodes) { best = i; break; }
          if (g_dd[i].used != g_dd_tick && g_dd[i].used < bu) { bu = g_dd[i].used; best = i; }
        }
        if (best < 0) continue;
        g_dd[best].lump = -1;
        if (dd_load(&g_dd[best], lump)) g_dd[best].used = g_dd_tick;
        loads++;
      }
}
static void dd_walk(dd_blk *b, int32_t node) {
  int guard = 0;
  while (node != -1) {
    if (node < 0 || node >= b->nnode || ++guard > 0x5000) return;
    const int32_t *nd = (const int32_t *)(b->nodes + (size_t)node * 8);
    int32_t oi = nd[0];
    uint8_t *o;
    if (oi < 0) return;
    if (oi < P54_Cnt1E0) o = (uint8_t *)G6_00D00208 + (size_t)oi * 0x20;            /* общий объект уровня — как в слотах игры */
    else if (oi - P54_Cnt1E0 < b->nobj) o = b->objs + (size_t)(oi - P54_Cnt1E0) * 0x20;
    else return;
    put_obj(o, 1);
    node = nd[1];
  }
}
/* клетка (x, y) любого блока: слот игры, если блок в нём, иначе кэш; 0 — блока нет (ещё не разобран) */
static int dd_cell(int32_t x, int32_t y) {
  int32_t N = P54_GridN, nn = N * N;
  int32_t bx = x / N, by = y / N, lump = by * P80_Cols + bx, rx = x - bx * N, ry = y - by * N;
  P88_CellA.px = (uint8_t)bx; P88_CellA.py = (uint8_t)by;
  P88_CellA.pc = (uint8_t)((bx & 1) + (by & 1) * 2);
  if (P87_SlotLump[P88_CellA.pc] == lump) { walk_cell(((int32_t *)G6_00D01268)[(size_t)P88_CellA.pc * nn + rx + ry * N], 1); return 1; }
  dd_blk *b = dd_find(lump);
  if (!b) return 0;
  dd_walk(b, b->heads[rx + ry * N]);
  return 1;
}
static int32_t dd_cur_radius(void) {
  int32_t cell = P80_Cell > 0 ? P80_Cell : 3000;
  int32_t R = (int32_t)ceil(P11_01270c24 / (float)cell) + 1, Rmax = re_dd_radius(re_draw_distance()) + 1;
  return R > Rmax ? Rmax : R;
}
/* предзагрузка всех блоков радиуса сразу (проверка рендера / первый кадр) — без ограничения DD_LOADS за кадр */
void re_dd_warm(void) {
  int32_t before;
  if (P54_GridN <= 0) return;
  do { before = re_dd_loads; dd_stream(P88_CellA.x, P88_CellA.y, dd_cur_radius()); } while (re_dd_loads != before && re_dd_loads - before < 64);
}
/* обход клеток за окном оригинала: квадрат радиуса R по расстоянию (ближние раньше), без клеток, уже пройденных веткой оригинала/Hor+ */
static void dd_extend(const uint8_t *um, int32_t R) {
  static int8_t ord[(2 * 127 + 1) * (2 * 127 + 1) * 2];
  static int32_t ord_r = -1, ord_n = 0;
  if (R > 120) R = 120;
  if (R != ord_r) { ord_n = re_dd_order(R, ord); ord_r = R; }
  double hx, hy;
  re_dd_heading_tab((const uint8_t *)P55_Frustum, (int)(int16_t)P59_AngB, &hx, &hy);
  double th = re_aspect_half_angle(re_view_extra());
  const uint8_t *lg = (const uint8_t *)P82_LightGrid;
  int32_t cx = P88_CellA.x, cy = P88_CellA.y, miss = 0, done = 0;
  dd_stream(cx, cy, R);
  for (int32_t i = 0; i < ord_n; i++) {
    int dx = ord[2 * i], dy = ord[2 * i + 1];
    int insq = dx >= -15 && dx <= 15 && dy >= -15 && dy <= 15;
    if (insq && um[(dy + 15) * 31 + dx + 15]) continue;                      /* пройдено веткой оригинала */
    if (!re_dd_visit(dx, dy, um, hx, hy, th, R)) continue;
    if (insq && lg[(size_t)(dy + 15) * P21_GridStride + dx + 15] == 0) continue;   /* PVS оригинала (31×31) */
    int32_t x = cx + dx, y = cy + dy;
    if (x < 0 || y < 0 || x >= P21_GridDiv || y >= P80_GridH) continue;
    if (dd_cell(x, y)) done++; else miss++;
  }
  { static int k; if (getenv("RE_DDLOG") && (k++ % 100) == 0)
      fprintf(stderr, "[dd] R %d far %.0f клеток %d нет блока %d разобрано блоков %d курс %.2f %.2f th %.1f°\n", (int)R, P11_01270c24, done, miss,
              (int)re_dd_loads, hx, hy, th * 57.29578); }
}
#endif

/* 004ee8f4 */
/* P89_DrawMap — Game.exe 004ee8f4, cdecl.  mode 0: only updates the camera cell and the visibility mask.
   mode != 0: also builds the light matrices, walks the visible cells (all 30x30 in camera mode 6,
   otherwise the FRUSTRUM.DAT rows of the heading sector, sector = heading / 16), queueing objects, then
   draws the class-7 list, the alpha-tested list (cut-outs) and, by day with shadows on (00d11880, no fog),
   the shadow list blended and lifted by 4 units; finally resets the alpha state. */
void P89_DrawMap(int32_t mode) {
  P87_CntB = 0;
  if (mode != 0) {
    P83_LightMatrices();
    if (G6_00B87EEC == 0) P12_Fn00426580(1);
  }
  P88_CellUpdate(mode);
  int32_t tile_n = P54_GridN;
  RE_DBG(6);
  if (tile_n <= 0 || !G6_00CE0F20 || !G6_00D01268 || !G6_00D00208) return;           /* охранная проверка — оригинал упал бы на делении */
  P89_VisMask(P88_CellA.cell, (P88_CellA.y % tile_n) * tile_n + P88_CellA.x % tile_n, (uint8_t *)P82_LightGrid);
  if (mode == 0) return;
  int32_t cx = P88_CellA.x;
  const uint8_t *frust_row = (const uint8_t *)P55_Frustum + (size_t)((((int32_t)(int16_t)P59_AngB + (((int32_t)(int16_t)P59_AngB >> 31) & 0xf)) >> 4) * 0x80);
  int32_t x0 = cx - 0xf;
  int32_t y0 = P88_CellA.y - 0xf + rds16(frust_row);
  P89_CntSeven = 0; P55_CntB = 0; P89_CntFour = 0; P55_CntA = 0; P89_CntShadow = 0;
  P88_CellA.py = (uint8_t)(y0 / tile_n);
  int32_t ry = y0 - ((y0 / tile_n) & 0xff) * tile_n;
  int32_t nn = tile_n * tile_n;
  int32_t first_row = rds16(frust_row), end_row = first_row + rds16(frust_row + 2);
  const uint8_t *light_row = (const uint8_t *)P82_LightGrid + (size_t)first_row * P21_GridStride;
  P44_MatPtr = (float *)P44_ViewMatT;
  int32_t *heads = (int32_t *)G6_00D01268;
  if (P59_Mode1137324 == 6) {
    y0 = P88_CellA.y - 0xf;
    P88_CellA.py = (uint8_t)(y0 / tile_n);
    ry = y0 - ((y0 / tile_n) & 0xff) * tile_n;
    for (int32_t row_i = -0xf; row_i < 0xf; row_i++) {
      for (int32_t c = -0xf; c < 0xf; c++) {
        int32_t x = c + cx;
        P88_CellA.px = (uint8_t)(x / tile_n);
        int32_t rx = x - ((x / tile_n) & 0xff) * tile_n;
        if (x > -1 && y0 > -1 && x < P21_GridDiv && y0 < P80_GridH) {
          P88_CellA.pc = (uint8_t)((P88_CellA.px & 1) + (P88_CellA.py & 1) * 2);
          walk_cell(heads[(size_t)P88_CellA.pc * nn + rx + ry * tile_n], 1);
        }
        if (rx + 1 == tile_n) P88_CellA.px++;
      }
      ry++;
      if (ry == tile_n) { ry = 0; P88_CellA.py++; }
      y0++;
    }
  }
#ifndef RE_HOOK_BUILD
  else if (re_view_extra() > 0) {
    /* v2.15 Hor+: FRUSTRUM.DAT рассчитан на угол 4:3 — обходим объединение секторов курса ±k (aspect.h), таблица не меняется.
       Порядок обхода и запись P88_CellA.px/py/pc — как в ветке оригинала: строки сверху вниз, клетки слева направо. */
    static uint8_t um[31 * 31];
    int32_t sec = (((int32_t)(int16_t)P59_AngB + (((int32_t)(int16_t)P59_AngB >> 31) & 0xf)) >> 4);
    re_frustum_union((const uint8_t *)P55_Frustum, sec, re_aspect_sectors(re_view_extra()), um);
    const uint8_t *lg = (const uint8_t *)P82_LightGrid;
    for (int32_t row_i = 0; row_i < 31; row_i++) {
      int32_t y = P88_CellA.y - 0xf + row_i;
      if (y < 0 || y >= P80_GridH) continue;
      P88_CellA.py = (uint8_t)(y / tile_n);
      int32_t ry2 = y - ((y / tile_n) & 0xff) * tile_n;
      for (int32_t c = 0; c < 31; c++) {
        if (um[row_i * 31 + c] == 0) continue;
        int32_t x = cx - 0xf + c;
        if (x < 0 || x >= P21_GridDiv || lg[(size_t)row_i * P21_GridStride + c] == 0) continue;
        P88_CellA.px = (uint8_t)(x / tile_n);
        int32_t rx = x - ((x / tile_n) & 0xff) * tile_n;
        P88_CellA.pc = (uint8_t)((P88_CellA.px & 1) + (P88_CellA.py & 1) * 2);
        walk_cell(heads[(size_t)P88_CellA.pc * nn + rx + ry2 * tile_n], 1);
      }
    }
  }
#endif
  else {
    for (int32_t row_i = first_row; row_i < end_row; row_i++) {
      int32_t c = rds16(frust_row + (size_t)(row_i * 2 + 2) * 2);
      if (c != -1) {
        int32_t x = c + x0;
        int32_t cend = c + rds16(frust_row + (size_t)(row_i * 2 + 3) * 2);
        P88_CellA.px = (uint8_t)(x / tile_n);
        int32_t rx = x - ((x / tile_n) & 0xff) * tile_n;
        for (; c < cend; c++) {
          if (x > -1 && y0 > -1 && x < P21_GridDiv && y0 < P80_GridH && light_row[c] != 0) {
            P88_CellA.pc = (uint8_t)((P88_CellA.px & 1) + (P88_CellA.py & 1) * 2);
            walk_cell(heads[(size_t)P88_CellA.pc * nn + rx + ry * tile_n], 1);
          }
          rx++;
          if (rx == tile_n) { rx = 0; P88_CellA.px++; }
          x++;
        }
      }
      ry++;
      if (ry == tile_n) { ry = 0; P88_CellA.py++; }
      light_row += P21_GridStride;
      y0++;
    }
  }
#ifndef RE_HOOK_BUILD
  /* v2.19 draw_distance > 1 (только основной 3D-вид P132_GameDraw, re_dd_on): клетки за окном 31×31 */
  if (re_dd_on && P59_Mode1137324 != 6) {
    static uint8_t dm[31 * 31];
    int32_t sec = (((int32_t)(int16_t)P59_AngB + (((int32_t)(int16_t)P59_AngB >> 31) & 0xf)) >> 4);
    re_frustum_union((const uint8_t *)P55_Frustum, sec, re_aspect_sectors(re_view_extra()), dm);
    int32_t R = dd_cur_radius();
    if (R > 15) dd_extend(dm, R);
  }
#endif
  int32_t saved = P12_01252b74;
  if (P89_CntSeven != 0) {
    P12_Fn00426580(0x13);
    for (int32_t i = 0; i < P89_CntSeven; i++) P87_DrawObjB((const uint8_t *)P89_ListSeven[i]);
    P12_Fn00426580(saved);
  }
  if (P89_CntFour != 0) {
    P85_StateDirty = (int32_t)0xffffffff;
    P69_BlendOn = 0xff;
    P62_I252B78 = (int32_t)0xffffffff;
    alpha_combine(3, 8, 0, 1, 1);
    alpha_test(GR_CMP_GREATER);
    P62_I252B78 = 1;
    for (int32_t i = 0; i < P89_CntFour; i++) P87_DrawObjA((const uint8_t *)P89_ListFour[i]);
  }
  if (G6_00D11880 != 0 && P89_CntShadow != 0 && P14_00b87e84 == 0 && P26_FxD == 0) {
    P85_StateDirty = (int32_t)0xffffffff;
    P69_BlendOn = 0xff;
    P62_I252B78 = (int32_t)0xffffffff;
    alpha_combine(4, 8, 1, 1, 1);
    alpha_test(GR_CMP_ALWAYS);
    P62_I252B78 = 2;
    int32_t old = DrvSetMode0042655A(0);
    for (int32_t i = 0; i < P89_CntShadow; i++) {
      uint8_t *o = (uint8_t *)P89_ListShadow[i];
      float y; memcpy(&y, o + 0xc, 4); y -= P43_Four; memcpy(o + 0xc, &y, 4);
      P87_DrawObjA(o);
      memcpy(&y, o + 0xc, 4); y += P43_Four; memcpy(o + 0xc, &y, 4);
    }
    DrvSetMode0042655A(old);
  }
  if (P62_I252B78 != 0) {
    alpha_combine(3, 8, 0, 2, 1);
    alpha_test(GR_CMP_ALWAYS);
    P62_I252B78 = 0;
  }
}
