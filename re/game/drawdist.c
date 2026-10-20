/* v2.19: дальность прорисовки — см. drawdist.h. Чистый C, без данных игры. */
/* drawdist.c — native draw-distance extension (v2.19; English overview, see drawdist.h for the full notes).
   Pure maths, no game data, no Game.exe counterpart.  The original walks a 31x31 window of map cells around
   the camera cell masked by FRUSTRUM.DAT (256 heading sectors); with multiplier m > 1 the walk radius becomes
   round(15 * m) cells: inside the 31x31 square the original mask is used unchanged, outside it a view cone
   (heading from the FRUSTRUM.DAT sector centroids, half-angle from aspect.h plus a per-cell margin).
   The 1/z table grows past the original 0xdbba entries when the far plane needs it.
   Magic numbers: 31 = window size, 15 = its centre cell, 0xdbba = original 1/z table entries (56250). */
#include "drawdist.h"
#include "aspect.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#ifndef RE_HOOK_BUILD
#include "../platform/sdl/plat_gfx.h"
#endif

#define DD_PI 3.14159265358979323846
#define OOW_N0    0xdbba    /* entries in the original 1/z table 00ba53a0 (56250) */

/* Multiplier clamped to [1, RE_DD_MAX]; NaN -> 1. */
double re_dd_clamp(double m) {
  if (!(m > 1.0)) return 1.0;
  if (m > RE_DD_MAX) return RE_DD_MAX;
  return m;
}

/* Walk radius in cells: round(15 * m), never below the original 15. */
int re_dd_radius(double m) {
  int r = (int)floor(RE_DD_BASE_R * re_dd_clamp(m) + 0.5);
  return r < RE_DD_BASE_R ? RE_DD_BASE_R : r;
}

/* Heading of a 31x31 mask: unit vector toward the centroid of its cells (centre cell excluded), in
   (column, row) axes.  Returns 0 (and (0, 1)) for an empty mask. */
int re_dd_heading(const uint8_t *m, double *hx, double *hy) {
  double sx = 0, sy = 0;
  for (int r = 0; r < 31; r++)
    for (int c = 0; c < 31; c++)
      if (m[r * 31 + c] && (r != 15 || c != 15)) { sx += c - 15; sy += r - 15; }
  double l = sqrt(sx * sx + sy * sy);
  if (l < 1e-9) { *hx = 0; *hy = 1; return 0; }
  *hx = sx / l; *hy = sy / l;
  return 1;
}

/* Camera heading for angle ang (4096 per turn) in FRUSTRUM.DAT axes: the centroids of sectors 0 and 64 are the
   two axes (they are symmetric, so the square clipping does not bias them); h = cos(phi)*e0 + sin(phi)*e64. */
int re_dd_heading_tab(const uint8_t *tab, int ang, double *hx, double *hy) {
  uint8_t m[31 * 31];
  double ax, ay, bx, by;
  re_frustum_union(tab, 0, 0, m);
  if (!re_dd_heading(m, &ax, &ay)) { *hx = 0; *hy = 1; return 0; }
  re_frustum_union(tab, 64, 0, m);
  if (!re_dd_heading(m, &bx, &by)) { *hx = 0; *hy = 1; return 0; }
  double ph = (ang & 4095) * 2.0 * DD_PI / 4096.0, c = cos(ph), s = sin(ph);
  double x = c * ax + s * bx, y = c * ay + s * by, l = sqrt(x * x + y * y);
  if (l < 1e-9) { *hx = 0; *hy = 1; return 0; }
  *hx = x / l; *hy = y / l;
  return 1;
}

/* Cone test for cell offset (dx, dy): within radius R + 0.5 and within half-angle th of the heading plus the
   angular half-size of a cell (asin(1.5 / d)); the immediate neighbours (d < 2) are always in. */
int re_dd_cell_in(int dx, int dy, double hx, double hy, double th, int R) {
  double d = sqrt((double)dx * dx + (double)dy * dy);
  if (d > R + 0.5) return 0;
  if (d < 2.0) return 1;
  double cs = (dx * hx + dy * hy) / d;
  if (cs > 1) cs = 1;
  if (cs < -1) cs = -1;
  double pad = asin(fmin(1.0, 1.5 / d));
  return acos(cs) <= th + pad;
}

/* Walk decision for cell (dx, dy): inside the 31x31 square the original mask decides, except beyond the
   14.5-cell circle (square corners / seam) where a cell the mask rejects may still pass the cone test;
   outside the square only the cone decides.  The caller checks the PVS for cells inside the square. */
int re_dd_visit(int dx, int dy, const uint8_t *mask31, double hx, double hy, double th, int R) {
  if (dx >= -15 && dx <= 15 && dy >= -15 && dy <= 15) {
    if (mask31[(dy + 15) * 31 + dx + 15]) return 1;
    if ((double)dx * dx + (double)dy * dy <= 14.5 * 14.5) return 0;
  }
  return re_dd_cell_in(dx, dy, hx, hy, th, R);
}

/* qsort order for cell offsets: by squared distance, then row, then column (deterministic). */
static int cmp_d(const void *a, const void *b) {
  const int8_t *p = (const int8_t *)a, *q = (const int8_t *)b;
  int da = p[0] * p[0] + p[1] * p[1], db = q[0] * q[0] + q[1] * q[1];
  if (da != db) return da - db;
  if (p[1] != q[1]) return p[1] - q[1];
  return p[0] - q[0];
}
/* Fills out with all (2R+1)^2 offsets (dx, dy) sorted nearest first, so the per-class lists of 0x400 entries
   are filled with near objects before far ones.  Returns the count (0 when R is out of 0..127). */
int re_dd_order(int R, int8_t *out) {
  if (R < 0 || R > 127) return 0;
  int n = 0;
  for (int y = -R; y <= R; y++)
    for (int x = -R; x <= R; x++) { out[n * 2] = (int8_t)x; out[n * 2 + 1] = (int8_t)y; n++; }
  qsort(out, (size_t)n, 2, cmp_d);
  return n;
}

/* 1/z beyond the original table: k / zi (k as in the table fill at 00526427); 0 for zi <= 0. */
float re_dd_oow(float k, int32_t zi) { return zi <= 0 ? 0.0f : k / (float)zi; }

/* Size of the 1/z table needed for far plane `far`: the original 0xdbba when it fits, else far * 1.25 + 2
   (capped at 0x7fffff). */
int32_t re_dd_oow_n(double far) {
  if (far + 2.0 <= OOW_N0) return OOW_N0;          /* дальняя плоскость оригинала (≤ 45000) помещается в таблицу */
  double need = far * 1.25 + 2.0;
  if (need <= OOW_N0) return OOW_N0;
  if (need > 0x7fffff) need = 0x7fffff;
  return (int32_t)need;
}

/* re_dd_on: 1 while the main 3-D view is drawn with the extended distance (see drawdist.h).
   re_dd_vis: LOD/detail distance multiplier while re_dd_on, else 1. */
int re_dd_on;
float re_dd_vis(void) { return re_dd_on ? (float)re_draw_distance() : 1.0f; }

#ifndef RE_HOOK_BUILD
double re_draw_distance(void) { return re_dd_clamp(re_gfx()->draw_distance); }
#else
double re_draw_distance(void) { return 1.0; }
#endif

/* ---- самопроверка ---- */
/* синтетическая таблица «как FRUSTRUM.DAT»: клин ±45° вокруг курса сектора (sin, cos — как столбец, строка), до края квадрата 31×31 */
static void synth(uint8_t *tab, int circle) {
  memset(tab, 0, 256 * 0x80);
  for (int a = 0; a < 256; a++) {
    double ph = a * 2.0 * DD_PI / 256.0, hx = sin(ph), hy = cos(ph);
    uint8_t *e = tab + (size_t)a * 0x80;
    int first = -1, cnt = 0;
    for (int r = 0; r < 31; r++) {
      int c0 = -1, len = 0;
      for (int c = 0; c < 31; c++) {
        double dx = c - 15, dy = r - 15, d = sqrt(dx * dx + dy * dy);
        int in = (!circle || d <= 15.0) && (d == 0 || (dx * hx + dy * hy) / d >= cos(45.0 * DD_PI / 180.0));
        if (in) { if (c0 < 0) c0 = c; len++; }
      }
      e[(2 + 2 * r) * 2] = (uint8_t)(c0 & 0xff); e[(2 + 2 * r) * 2 + 1] = (uint8_t)((c0 >> 8) & 0xff);
      e[(3 + 2 * r) * 2] = (uint8_t)len; e[(3 + 2 * r) * 2 + 1] = 0;
      if (c0 >= 0) { if (first < 0) first = r; cnt = r - first + 1; }
    }
    e[0] = (uint8_t)(first & 0xff); e[1] = (uint8_t)((first >> 8) & 0xff); e[2] = (uint8_t)cnt; e[3] = 0;
  }
}

/* Self-test (ctest): 0 = pass, otherwise the number of the failed check.  Checks clamping, radius, 1/z table
   sizing, walk order, and on synthetic frustum tables (wedge and circle, three Hor+ widths) that the cone
   walk has no holes inside the view angle, nothing behind the camera or past R, and never trims the
   original 31x31 mask. */
int re_dd_selftest(void) {
  int t = 0;
#define T(c) do { t++; if (!(c)) { free(tab); free(ord); return t; } } while (0)
  uint8_t *tab = (uint8_t *)malloc(256 * 0x80), mask[31 * 31];
  int8_t *ord = (int8_t *)malloc((size_t)(2 * 60 + 1) * (2 * 60 + 1) * 2);
  if (!tab || !ord) { free(tab); free(ord); return 100; }
  T(re_dd_clamp(0.5) == 1.0 && re_dd_clamp(NAN) == 1.0 && re_dd_clamp(9.0) == RE_DD_MAX && re_dd_clamp(2.5) == 2.5);
  T(re_dd_radius(1.0) == 15 && re_dd_radius(2.0) == 30 && re_dd_radius(3.0) == 45 && re_dd_radius(4.0) == 60 && re_dd_radius(0.1) == 15);
  /* таблица 1/z: оригинальный размер при far 45000, продолжение k/z совпадает с формулой заполнения 00526427 и монотонно */
  T(re_dd_oow_n(45000.0) == 0xdbba && re_dd_oow_n(90000.0) >= 112500 && re_dd_oow_n(180000.0) >= 225000);
  T(re_dd_oow(1.0f, 0) == 0.0f && fabsf(re_dd_oow(2.0f, 0xdbba) - 2.0f / 56250.0f) < 1e-12f && re_dd_oow(1.0f, 100000) < re_dd_oow(1.0f, 56249));
  /* порядок обхода: полный квадрат, (0,0) первым, расстояние не убывает */
  for (int R = 15; R <= 60; R += 15) {
    int n = re_dd_order(R, ord);
    T(n == (2 * R + 1) * (2 * R + 1) && ord[0] == 0 && ord[1] == 0);
    int ok = 1, prev = 0;
    for (int i = 0; i < n; i++) { int d = ord[2 * i] * ord[2 * i] + ord[2 * i + 1] * ord[2 * i + 1]; if (d < prev) ok = 0; prev = d; }
    T(ok);
  }
  const int Ss[] = { 0, 107, 253 };
  for (int circle = 0; circle < 2; circle++) {
    synth(tab, circle);
    for (int si = 0; si < 3; si++) {
      int S = Ss[si], k = re_aspect_sectors(S);
      double th = re_aspect_half_angle(S);
      for (int sec = 0; sec < 256; sec += 13) {
        re_frustum_union(tab, sec, k, mask);
        double hx, hy, ph = sec * 2.0 * DD_PI / 256.0;
        T(re_dd_heading_tab(tab, sec * 16, &hx, &hy));
        /* курс по осям таблицы совпадает с курсом сектора (до половины шага сектора: клетки ровно на границе клина делятся несимметрично) */
        T(hx * sin(ph) + hy * cos(ph) > cos(DD_PI / 256.0));
        for (int R = 30; R <= 60; R += 15)
          for (int dy = -R; dy <= R; dy++)
            for (int dx = -R; dx <= R; dx++) {
              double d = sqrt((double)dx * dx + (double)dy * dy);
              int v = re_dd_visit(dx, dy, mask, hx, hy, th, R);
              int insq = dx >= -15 && dx <= 15 && dy >= -15 && dy <= 15;
              if (d < 1.0) continue;
              double off = acos(fmax(-1.0, fmin(1.0, (dx * sin(ph) + dy * cos(ph)) / d)));
              /* в угле обзора и в радиусе — обходится (нет дыр на стыке 31×31 и конуса, в углах квадрата тоже) */
              if (off <= th - 2.0 * DD_PI / 256.0 && d <= R) T(v == 1);
              /* позади камеры и за радиусом — нет */
              if (d >= 2.0 && off >= 0.6 * DD_PI) T(v == 0);
              if (d > R + 0.5) T(v == 0);
              /* внутри квадрата 31×31 маска оригинала не урезается */
              if (insq && mask[(dy + 15) * 31 + dx + 15]) T(v == 1);
            }
      }
    }
  }
  free(tab); free(ord);
#undef T
  return 0;
}
