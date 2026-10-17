/* Маска видимости клеток и главный обход клеток карты — восстановлено из Game.exe (004ef997, 004ef793, 004ee8f4). */
#include "redbg.h"
#include "ported89.h"
#include "aspect.h"
#include "ported13.h"
#include <string.h>
#include <stdlib.h>

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

static int32_t rd32(const uint8_t *p) { int32_t v; memcpy(&v, p, 4); return v; }
static int16_t rd16s(const uint8_t *p) { int16_t v; memcpy(&v, p, 2); return v; }

/* разложить объекты клетки с головой списка node по классам (общая часть обоих ветвей 004ee8f4) */
static void walk_cell(int32_t node, int guarded) {
  int guard = 0;
  RE_DBG(7);
  while (node != -1) {
    if (node < 0 || node >= 4 * 0x5000 || ++guard > 0x5000) return;              /* охранные проверки — в оригинале их нет */
    const int32_t *nd = (const int32_t *)((const uint8_t *)G6_00CE0F20 + (size_t)node * 8);
    if (nd[0] < 0 || nd[0] >= P54_Cnt1E0 + 4 * 0x2000) return;
    uint8_t *o = (uint8_t *)G6_00D00208 + (size_t)nd[0] * 0x20;
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
    node = nd[1];
  }
}

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
