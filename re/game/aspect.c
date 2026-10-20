/* aspect.c — native only (v2.15): arbitrary aspect ratio "Hor+" math (English overview; original notes follow).
   The original renders 3D into a 640x480 frame: projection centre (320, 240), focal length 384
   (RE_ASPECT_FOCAL; vertical FOV 2*atan(240/384) ~ 64 deg, horizontal 2*atan(320/384) ~ 79.6 deg).
   Hor+ keeps the vertical FOV and widens the logical frame to 480*aspect = 640 + 2*S pixels; the game
   still computes in 640x480 coordinates and the backend shifts everything by +S.  The side frustum
   planes and the FRUSTRUM.DAT map-cell culling (256 heading sectors x 31x31 cells) are widened to match.
   Pure math, no game data; re_aspect_selftest checks it.  See aspect.h for the interface. */
/* v2.15: произвольное соотношение сторон (Hor+) — см. aspect.h. Чистый C, без данных игры. */
#include "aspect.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#ifndef RE_HOOK_BUILD
#include "ported19.h"
#include "../platform/plat.h"
#endif

#define RE_PI 3.14159265358979323846
/* θ оригинала: FSIN.DAT[475] (0x00b949ec − 0x00b94280 = 0x76c байт) — синус, [475 + 1024] — косинус, 4096 единиц на оборот */
/* theta0 — half-angle of the original side frustum planes: FSIN.DAT entry 475 (4096 units per turn),
   about 41.7 deg = 39.8 deg of geometry plus a ~1.9 deg margin. */
static double theta0(void) { return 2.0 * RE_PI * 475.0 / 4096.0; }
/* margin — the original's safety margin: theta0 minus the exact half-angle atan(320 / 384). */
static double margin(void) { return theta0() - atan(320.0 / RE_ASPECT_FOCAL); }

/* re_aspect_parse — parses RE_ASPECT: NULL / "" / "auto" -> 0 (follow the window), "W:H" / "WxH" / "W/H" or
   a plain ratio "1.78" -> the ratio, anything else -> -1. */
double re_aspect_parse(const char *s) {
  if (s == NULL || *s == 0 || strcmp(s, "auto") == 0 || strcmp(s, "AUTO") == 0) return 0.0;
  double a = 0, b = 0; char c = 0;
  if (sscanf(s, "%lf%c%lf", &a, &c, &b) == 3 && (c == ':' || c == 'x' || c == '/') && a > 0 && b > 0) return a / b;
  char *e = NULL; a = strtod(s, &e);
  if (e != s && e && *e == 0 && a > 0) return a;
  return -1.0;
}

/* re_aspect_target — target aspect: the parsed mode if > 0, else the window's dw/dh (4:3 if unknown). */
double re_aspect_target(int dw, int dh, double mode) {
  if (mode > 0) return mode;
  if (dw <= 0 || dh <= 0) return (double)RE_ASPECT_W / RE_ASPECT_H;
  return (double)dw / dh;
}

/* re_aspect_extra — S, logical pixels added on each side of 640 for `aspect` (rounded; capped at
   RE_ASPECT_MAX).  0 for 4:3 or narrower (those are letterboxed instead). */
int re_aspect_extra(double aspect) {
  if (!(aspect > (double)RE_ASPECT_W / RE_ASPECT_H + 1e-6)) return 0;
  if (aspect > RE_ASPECT_MAX) aspect = RE_ASPECT_MAX;
  return (int)floor((RE_ASPECT_H * aspect - RE_ASPECT_W) / 2.0 + 0.5);
}

/* re_aspect_half_angle — half horizontal angle (radians) of the side frustum planes for a half-width of
   320 + S, keeping the original margin; S <= 0 gives exactly theta0. */
double re_aspect_half_angle(int S) {
  if (S <= 0) return theta0();
  return atan((320.0 + S) / RE_ASPECT_FOCAL) + margin();
}

/* re_aspect_sectors — how many extra FRUSTRUM.DAT heading sectors (2*pi/256 each) to add on each side so
   the culling wedge covers the wider view; 0..64. */
int re_aspect_sectors(int S) {
  if (S <= 0) return 0;
  double extra_angle = re_aspect_half_angle(S) - theta0(), sector_angle = 2.0 * RE_PI / 256.0;
  int k = (int)ceil(extra_angle / sector_angle - 1e-9);
  if (k < 0) k = 0;
  if (k > 64) k = 64;
  return k;
}

/* rd16 — local helper: little-endian int16 from a byte pointer. */
static int16_t rd16(const uint8_t *p) { return (int16_t)(p[0] | (p[1] << 8)); }
/* re_frustum_union — ORs sectors sec-k .. sec+k of the FRUSTRUM.DAT table into a 31x31 cell mask.
   Table entry (0x80 bytes): int16 first row, int16 row count, then 31 x {int16 first column, int16 length};
   a negative first row/column means empty.  Returns the number of cells set. */
int re_frustum_union(const uint8_t *tab, int sec, int k, uint8_t *mask) {
  memset(mask, 0, 31 * 31);
  if (tab == NULL) return 0;
  for (int j = -k; j <= k; j++) {
    const uint8_t *entry = tab + (size_t)((sec + j) & 0xff) * 0x80;
    int first_row = rd16(entry), row_cnt = rd16(entry + 2);
    if (first_row < 0) continue;
    for (int r = first_row; r < first_row + row_cnt && r < 31; r++) {
      int first_col = rd16(entry + (size_t)(2 + 2 * r) * 2), col_len = rd16(entry + (size_t)(3 + 2 * r) * 2);
      if (first_col < 0) continue;
      for (int i = first_col; i < first_col + col_len && i < 31; i++) mask[r * 31 + i] = 1;
    }
  }
  int n = 0;
  for (int i = 0; i < 31 * 31; i++) n += mask[i];
  return n;
}

/* re_game_screen — v2.26: in native mode (game_res = native) forces the game's own screen mode to 640x480,
   because Hor+ and the HUD anchors assume that frame.  Returns 1 if *w / *h were replaced. */
int re_game_screen(int native, int32_t *w, int32_t *h) {
  if (!native || w == NULL || h == NULL || (*w == RE_ASPECT_W && *h == RE_ASPECT_H)) return 0;
  *w = RE_ASPECT_W; *h = RE_ASPECT_H; return 1;
}

#ifndef RE_HOOK_BUILD
/* re_view_extra — S of the current frame for the main 3D view: the platform's value when the game frame
   is 640 wide (i.e. not the rear-view mirror); always 0 in the hook build (original behaviour). */
int re_view_extra(void) { return P19_ScrW == RE_ASPECT_W ? plat_view_extra() : 0; }
#else
int re_view_extra(void) { return 0; }
#endif

/* ---- самопроверка ---- */
/* синтетическая таблица «как FRUSTRUM.DAT»: клин ±45° вокруг курса сектора, радиус 15, вершина в центре */
/* synth_table — selftest helper: a synthetic FRUSTRUM.DAT-like table (a +-45 deg wedge of radius 15 cells
   around each sector's heading, apex at the centre). */
static void synth_table(uint8_t *tab) {
  memset(tab, 0, 256 * 0x80);
  for (int a = 0; a < 256; a++) {
    double ph = a * 2.0 * RE_PI / 256.0, hx = sin(ph), hy = cos(ph);
    uint8_t *e = tab + (size_t)a * 0x80;
    int first = -1, cnt = 0;
    for (int r = 0; r < 31; r++) {
      int c0 = -1, len = 0;
      for (int c = 0; c < 31; c++) {
        double dx = c - 15, dy = r - 15, d = sqrt(dx * dx + dy * dy);
        int in = d <= 15.0 && (d == 0 || (dx * hx + dy * hy) / d >= cos(45.0 * RE_PI / 180.0));
        if (in) { if (c0 < 0) c0 = c; len++; }
      }
      e[(2 + 2 * r) * 2] = (uint8_t)(c0 & 0xff); e[(2 + 2 * r) * 2 + 1] = (uint8_t)((c0 >> 8) & 0xff);
      e[(3 + 2 * r) * 2] = (uint8_t)len; e[(3 + 2 * r) * 2 + 1] = 0;
      if (c0 >= 0) { if (first < 0) first = r; cnt = r - first + 1; }
    }
    e[0] = (uint8_t)(first & 0xff); e[1] = (uint8_t)((first >> 8) & 0xff); e[2] = (uint8_t)cnt; e[3] = 0;
  }
}
/* проекция игры: x_экр = X·(384/z) + 320 (+S в бэкенде); возвращает пиксель логического кадра шириной 640 + 2S */
/* proj_x / proj_y — selftest helpers: the game's projection X * (384 / z) + 320 (+S) and Y * (384 / z) + 240. */
static double proj_x(double X, double z, int S) { return X * (RE_ASPECT_FOCAL / z) + 320.0 + S; }
static double proj_y(double Y, double z) { return Y * (RE_ASPECT_FOCAL / z) + 240.0; }

/* re_aspect_selftest — checks the math above without game data.  Returns 0 if all pass, otherwise the
   number of the failed check (used by selftest / inputtest). */
int re_aspect_selftest(void) {
  int t = 0;
#define T(c) do { t++; if (!(c)) return t; } while (0)
  T(re_aspect_parse("auto") == 0.0 && re_aspect_parse(NULL) == 0.0);
  { int32_t w = 1024, h = 768;   /* v2.26: режим игры → 640×480 в native, original — как есть */
    T(re_game_screen(1, &w, &h) == 1 && w == 640 && h == 480 && re_game_screen(1, &w, &h) == 0);
    w = 1280; h = 1024; T(re_game_screen(0, &w, &h) == 0 && w == 1280 && h == 1024);
    w = 320; h = 240; T(re_game_screen(1, &w, &h) == 1 && w == 640 && h == 480); }
  T(fabs(re_aspect_parse("4:3") - 4.0 / 3.0) < 1e-12 && fabs(re_aspect_parse("21:9") - 21.0 / 9.0) < 1e-12);
  T(fabs(re_aspect_parse("2.35") - 2.35) < 1e-12 && re_aspect_parse("abc") < 0 && re_aspect_parse("0:3") < 0);
  T(re_aspect_extra(4.0 / 3.0) == 0 && re_aspect_extra(1080.0 / 1920.0) == 0 && re_aspect_extra(1.0) == 0);
  T(re_aspect_extra(1920.0 / 1080.0) == 107 && re_aspect_extra(2560.0 / 1600.0) == 64);
  T(re_aspect_extra(3440.0 / 1440.0) == 253 && re_aspect_extra(5120.0 / 1440.0) == 533);
  T(re_aspect_extra(100.0) == re_aspect_extra(RE_ASPECT_MAX));
  T(re_aspect_target(1920, 1080, 0.0) == 1920.0 / 1080.0 && re_aspect_target(1920, 1080, 4.0 / 3.0) == 4.0 / 3.0);
  T(fabs(re_aspect_half_angle(0) - 41.748046875 * RE_PI / 180.0) < 1e-9 && re_aspect_sectors(0) == 0);
  const double asp[] = { 4.0 / 3.0, 16.0 / 10.0, 16.0 / 9.0, 3440.0 / 1440.0, 32.0 / 9.0 };
  uint8_t *tab = (uint8_t *)malloc(256 * 0x80), mask[31 * 31];
  if (tab == NULL) return 100;
  synth_table(tab);
  for (size_t i = 0; i < sizeof asp / sizeof asp[0]; i++) {
    int S = re_aspect_extra(asp[i]), W = 640 + 2 * S;
    /* ширина логического кадра = 480·аспект (до пикселя), вертикаль — 480 при любом аспекте */
    T(fabs(W - 480.0 * asp[i]) <= 1.0);
    /* край экрана: точка на полуширине (320 + S)/384·z попадает ровно в 0 и W, верх/низ — в 0 и 480 (вертикальный FOV оригинала) */
    double z = 1000.0, X = (320.0 + S) / RE_ASPECT_FOCAL * z;
    T(fabs(proj_x(X, z, S) - W) < 1e-6 && fabs(proj_x(-X, z, S)) < 1e-6);
    T(fabs(proj_y(240.0 / RE_ASPECT_FOCAL * z, z) - 480.0) < 1e-6 && fabs(proj_y(-240.0 / RE_ASPECT_FOCAL * z, z)) < 1e-6);
    /* центр проекции 4:3-части не сдвинут относительно оригинала: x = 0 → 320 + S */
    T(fabs(proj_x(0, z, S) - (320.0 + S)) < 1e-9);
    /* боковые плоскости с запасом охватывают край экрана; запас не меньше оригинального */
    double th = re_aspect_half_angle(S), edge = atan((320.0 + S) / RE_ASPECT_FOCAL);
    T(th > edge && th - edge >= re_aspect_half_angle(0) - atan(320.0 / RE_ASPECT_FOCAL) - 1e-9 && th < RE_PI / 2);
    /* клин объединения секторов покрывает угол обзора: клетка на направлении θ − 1° от курса — внутри, позади — нет */
    int k = re_aspect_sectors(S);
    T(k == 0 || k * 2.0 * RE_PI / 256.0 + 1e-9 >= th - re_aspect_half_angle(0));
    for (int sec = 0; sec < 256; sec += 37) {
      re_frustum_union(tab, sec, k, mask);
      double hx = sin(sec * 2.0 * RE_PI / 256.0), hy = cos(sec * 2.0 * RE_PI / 256.0);
      for (int r = 0; r < 31; r++) for (int c = 0; c < 31; c++) {
        double dx = c - 15, dy = r - 15, d = sqrt(dx * dx + dy * dy);
        if (d < 1.0 || d > 14.0) continue;
        double off = acos(fmax(-1.0, fmin(1.0, (dx * hx + dy * hy) / d)));
        if (off <= th) T(mask[r * 31 + c] == 1);               /* всё в угле обзора (с запасом) обходится */
        if (off >= 0.75 * RE_PI) T(mask[r * 31 + c] == 0);     /* позади камеры — нет */
      }
    }
  }
  /* k = 0 — объединение равно одной записи (4:3 — обход как в оригинале) */
  int n1 = re_frustum_union(tab, 5, 0, mask), n0 = 0;
  { const uint8_t *e = tab + 5 * 0x80;
    for (int r = 0; r < 31; r++) if (rd16(e + (size_t)(2 + 2 * r) * 2) >= 0) n0 += rd16(e + (size_t)(3 + 2 * r) * 2); }
  T(n1 == n0 && n1 > 0);
  free(tab);
#undef T
  return 0;
}
