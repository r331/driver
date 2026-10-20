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
void P89_Fill1(uint8_t *out) {
  for (int32_t i = 0; i < D_00d00204; i++) *out++ = 1;
}

/* 004ef793 */
void P89_VisMask(int32_t blk, int32_t sub, uint8_t *out) {
  const uint8_t *base = (const uint8_t *)P46_MapBufA;
  if (base == NULL) { P89_Fill1(out); return; }
  uint32_t off, v;
  memcpy(&off, base + 0x10 + (size_t)blk * 4, 4);
  const uint8_t *tab = base + off;
  memcpy(&v, tab + (size_t)sub * 4, 4);
  const uint8_t *p = tab + (v & 0x3fffffffu);
  if (p == tab) { P89_Fill1(out); return; }
  uint32_t rest = (uint32_t)D_00d00204;
  if ((rest & 7) != 0) rest++;
  while (rest != 0) {
    uint8_t n = *p;
    const uint8_t *q = p + 1;
    if ((uint32_t)n * 8 > rest) return;               /* охранная проверка: в оригинале счётчик ушёл бы ниже нуля */
    rest -= (uint32_t)n * 8;
    for (; n != 0; n--) { memset(out, 1, 8); out += 8; }
    if (rest == 0) return;
    p += 2;
    for (uint8_t m = *q; m != 0; m--) {
      uint8_t b = *p++;
      for (int k = 0; k < 8; k++) {
        *out++ = (uint8_t)(b & 1);
        rest--;
        if (rest == 0) break;
        b >>= 1;
      }
      if (rest == 0) return;                            /* охранная проверка: оригинал продолжил бы с rest = 0xffffffff */
    }
  }
}

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
static int16_t rd16s(const uint8_t *p) { int16_t v; memcpy(&v, p, 2); return v; }

/* разложить объект o по классам (общая часть обоих ветвей 004ee8f4) */
static void put_obj(uint8_t *o, int guarded) {
  uint32_t stamp = (uint32_t)rd32(o);
  if (stamp != (uint32_t)P47_SwapCnt && rd32(o + 0x1c) == 0) {
    int32_t mi = rd32(o + 4);
    if (mi >= 0 && mi < 1126 && S_00BDCD00[mi] != 0) {
      switch (P80_Class[mi]) {
      case 1: P87_DrawObjB(o); break;
      case 2: if (!guarded || P55_CntA < 0x400) { P55_TabA[P55_CntA] = o; P55_CntA++; } break;
      case 3: if (!guarded || P89_CntShadow < 0x400) { P89_ListShadow[P89_CntShadow] = o; P89_CntShadow++; } break;
      case 4: if (!guarded || P89_CntFour < 0x400) { P89_ListFour[P89_CntFour] = o; P89_CntFour++; } break;
      case 5: if (P13_00575ee8 != 0) P87_DrawObjB(o); break;
      case 6: if (!guarded || P55_CntB < 0x400) { P55_TabB[P55_CntB] = o; P55_CntB++; } break;
      case 7: if (!guarded || P89_CntSeven < 0x200) { P89_ListSeven[P89_CntSeven] = o; P89_CntSeven++; } break;
      default: break;
      }
    }
    { uint32_t sc = (uint32_t)P47_SwapCnt; memcpy(o, &sc, 4); }
  }
}

/* разложить объекты клетки с головой списка node по классам */
static void walk_cell(int32_t node, int guarded) {
  int guard = 0;
  RE_DBG(7);
  while (node != -1) {
    if (node < 0 || node >= 4 * 0x5000 || ++guard > 0x5000) return;              /* охранные проверки — в оригинале их нет */
    const int32_t *nd = (const int32_t *)((const uint8_t *)G6_00CE0F20 + (size_t)node * 8);
    if (nd[0] < 0 || nd[0] >= P54_Cnt1E0 + 4 * 0x2000) return;
    put_obj((uint8_t *)G6_00D00208 + (size_t)nd[0] * 0x20, guarded);
    node = nd[1];
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
    uint32_t a = (uint32_t)(uint16_t)rd16s(cur + i * 4), nb = (uint32_t)(uint16_t)rd16s(cur + i * 4 + 2);
    int32_t na = (int32_t)a, nx = nb == 0xffff ? -1 : (int32_t)nb;
    memcpy(b->nodes + (size_t)i * 8, &na, 4); memcpy(b->nodes + (size_t)i * 8 + 4, &nx, 4);
  }
  b->nnode = n;
  cur += (size_t)n * 4;
  int32_t sz = rd32(cur);
  uint8_t kind = cur[4];
  const uint8_t *cd = cur + 5, *after = cur + 4 + sz;
  if (kind == 1) {
    for (int32_t i = 0; i < cells; i++) { uint16_t v = (uint16_t)rd16s(cd + i * 2); b->heads[i] = v == 0xffff ? -1 : (int32_t)v; }
  } else if (kind == 2) {
    uint32_t bit = 0x8000; int16_t mask = rd16s(cd); cd = cur + 7;
    for (int32_t i = 0; i < cells; i++) {
      int32_t v;
      if (((int32_t)mask & bit) == 0) v = -1;
      else { v = (int32_t)(uint16_t)rd16s(cd); cd += 2; }
      b->heads[i] = v;
      bit = (uint32_t)((int32_t)bit >> 1);
      if (bit == 0) { bit = 0x8000; mask = rd16s(cd); cd += 2; }
    }
  } else {
    for (int32_t i = 0; i < cells; i++) b->heads[i] = -1;
  }
  int32_t cnt = rd32(after); const uint8_t *rec = after + 4;
  if (cnt < 0) cnt = 0;
  if (cnt > 0x2000) cnt = 0x2000;
  for (int32_t i = 0; i < cnt; i++, rec += 0x14) {
    uint8_t *o = b->objs + (size_t)i * 0x20;
    uint32_t stamp = P44_XformTag; uint16_t m = (uint16_t)rd16s(rec); uint32_t mi = m & 0x7fff;
    int32_t ang = rd16s(rec + 0x10), flag = (m & 0x8000) ? 1 : 0;
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
void P89_DrawMap(int32_t mode) {
  P87_CntB = 0;
  if (mode != 0) {
    P83_LightMatrices();
    if (G6_00B87EEC == 0) P12_Fn00426580(1);
  }
  P88_CellUpdate(mode);
  int32_t N = P54_GridN;
  RE_DBG(6);
  if (N <= 0 || !G6_00CE0F20 || !G6_00D01268 || !G6_00D00208) return;           /* охранная проверка — оригинал упал бы на делении */
  P89_VisMask(P88_CellA.cell, (P88_CellA.y % N) * N + P88_CellA.x % N, (uint8_t *)P82_LightGrid);
  if (mode == 0) return;
  int32_t cx = P88_CellA.x;
  const uint8_t *row = (const uint8_t *)P55_Frustum + (size_t)((((int32_t)(int16_t)P59_AngB + (((int32_t)(int16_t)P59_AngB >> 31) & 0xf)) >> 4) * 0x80);
  int32_t x0 = cx - 0xf;
  int32_t y0 = P88_CellA.y - 0xf + rd16s(row);
  P89_CntSeven = 0; P55_CntB = 0; P89_CntFour = 0; P55_CntA = 0; P89_CntShadow = 0;
  P88_CellA.py = (uint8_t)(y0 / N);
  int32_t ry = y0 - ((y0 / N) & 0xff) * N;
  int32_t nn = N * N;
  int32_t first = rd16s(row), rows = first + rd16s(row + 2);
  const uint8_t *lt = (const uint8_t *)P82_LightGrid + (size_t)first * P21_GridStride;
  P44_MatPtr = (float *)P44_ViewMatT;
  int32_t *heads = (int32_t *)G6_00D01268;
  if (P59_Mode1137324 == 6) {
    y0 = P88_CellA.y - 0xf;
    P88_CellA.py = (uint8_t)(y0 / N);
    ry = y0 - ((y0 / N) & 0xff) * N;
    for (int32_t r = -0xf; r < 0xf; r++) {
      for (int32_t c = -0xf; c < 0xf; c++) {
        int32_t x = c + cx;
        P88_CellA.px = (uint8_t)(x / N);
        int32_t rx = x - ((x / N) & 0xff) * N;
        if (x > -1 && y0 > -1 && x < P21_GridDiv && y0 < P80_GridH) {
          P88_CellA.pc = (uint8_t)((P88_CellA.px & 1) + (P88_CellA.py & 1) * 2);
          walk_cell(heads[(size_t)P88_CellA.pc * nn + rx + ry * N], 1);
        }
        if (rx + 1 == N) P88_CellA.px++;
      }
      ry++;
      if (ry == N) { ry = 0; P88_CellA.py++; }
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
    for (int32_t r = 0; r < 31; r++) {
      int32_t y = P88_CellA.y - 0xf + r;
      if (y < 0 || y >= P80_GridH) continue;
      P88_CellA.py = (uint8_t)(y / N);
      int32_t ry2 = y - ((y / N) & 0xff) * N;
      for (int32_t c = 0; c < 31; c++) {
        if (um[r * 31 + c] == 0) continue;
        int32_t x = cx - 0xf + c;
        if (x < 0 || x >= P21_GridDiv || lg[(size_t)r * P21_GridStride + c] == 0) continue;
        P88_CellA.px = (uint8_t)(x / N);
        int32_t rx = x - ((x / N) & 0xff) * N;
        P88_CellA.pc = (uint8_t)((P88_CellA.px & 1) + (P88_CellA.py & 1) * 2);
        walk_cell(heads[(size_t)P88_CellA.pc * nn + rx + ry2 * N], 1);
      }
    }
  }
#endif
  else {
    for (int32_t r = first; r < rows; r++) {
      int32_t c = rd16s(row + (size_t)(r * 2 + 2) * 2);
      if (c != -1) {
        int32_t x = c + x0;
        int32_t cend = c + rd16s(row + (size_t)(r * 2 + 3) * 2);
        P88_CellA.px = (uint8_t)(x / N);
        int32_t rx = x - ((x / N) & 0xff) * N;
        for (; c < cend; c++) {
          if (x > -1 && y0 > -1 && x < P21_GridDiv && y0 < P80_GridH && lt[c] != 0) {
            P88_CellA.pc = (uint8_t)((P88_CellA.px & 1) + (P88_CellA.py & 1) * 2);
            walk_cell(heads[(size_t)P88_CellA.pc * nn + rx + ry * N], 1);
          }
          rx++;
          if (rx == N) { rx = 0; P88_CellA.px++; }
          x++;
        }
      }
      ry++;
      if (ry == N) { ry = 0; P88_CellA.py++; }
      lt += P21_GridStride;
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
    alpha_test(4);
    P62_I252B78 = 1;
    for (int32_t i = 0; i < P89_CntFour; i++) P87_DrawObjA((const uint8_t *)P89_ListFour[i]);
  }
  if (G6_00D11880 != 0 && P89_CntShadow != 0 && P14_00b87e84 == 0 && P26_FxD == 0) {
    P85_StateDirty = (int32_t)0xffffffff;
    P69_BlendOn = 0xff;
    P62_I252B78 = (int32_t)0xffffffff;
    alpha_combine(4, 8, 1, 1, 1);
    alpha_test(7);
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
    alpha_test(7);
    P62_I252B78 = 0;
  }
}
