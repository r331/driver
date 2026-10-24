/* ported86.c — native only: textured and Gouraud handlers for model primitive records (record types
   20..23, 50, 51; handler set 1, mode 0) plus the native texture store and HD texture-pack hookup
   (English overview; original notes follow).
   The handlers are ports of Game.exe functions; the rest (pages as GL textures, 8-bit page x palette
   pairs, RE_TEXLOG statistics, texture-pack lookup and verification) has no Game.exe counterpart.
   In the game itself drawing goes through Game.exe's Direct3D emulation (game_path()), and only the
   texture-pack attachment helpers (P86_Game*) are used. */
/* Текстурные и гуро-обработчики записей модели (набор 1, режим 0) — восстановлено из Game.exe. */
#include "ported86.h"
#include "ported12.h"
#include "ported14.h"
#include "smallfuncs2.h"
#include "ported33.h"
#include "../platform/plat.h"
#ifndef RE_HOOK_BUILD
#include "ported77.h"
#include "ported58.h"
#include "ported53.h"
#include "../platform/sdl/plat_texpack.h"
#include <stdio.h>
#include <math.h>
#endif
#include <string.h>
#include <stdlib.h>

#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P86_CurTex")
#undef P86_CurTex
#pragma push_macro("P86_CurTex") /*gvi*/
#undef P86_CurTex /*gvi*/
int32_t P86_CurTex;
#pragma pop_macro("P86_CurTex") /*gvi*/
#pragma pop_macro("P86_CurTex")
#endif
GAME_VAR_DEF(p86_texsrc_fn, P86_TexSrc, 0x01270d5c)
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P86_Detail")
#undef P86_Detail
#pragma push_macro("P86_Detail") /*gvi*/
#undef P86_Detail /*gvi*/
uint8_t P86_Detail;
#pragma pop_macro("P86_Detail") /*gvi*/
#pragma pop_macro("P86_Detail")
#endif

typedef struct { int nv; int uv; int col; int size; int detail; } p86_fmt;
static const p86_fmt F20 = { 3, 0x14, 0x2c, 0x38, 0 };
static const p86_fmt F21 = { 4, 0x18, 0x38, 0x44, 0 };
static const p86_fmt F22 = { 3, 0x20, 0x38, 0x44, 1 };
static const p86_fmt F23 = { 4, 0x28, 0x48, 0x54, 1 };

/* rf / ri — local helpers: float / int32 at byte offset off of a record. */
static float rf(const uint8_t *p, int off) { float f; memcpy(&f, p + off, 4); return f; }
static int32_t ri(const uint8_t *p, int off) { int32_t i; memcpy(&i, p + off, 4); return i; }

/* прибавить к цвету вершины вклад всех динамических источников света (запись 0x24 в 011f40e0) */
/* add_lights — local helper: adds every dynamic light hit (P63_Hits, records of 0x24 bytes in 011f40e0:
   position, colour [4..6], radius^2 [7], scale [8]) to vertex colour c: (radius^2 - d^2) * scale * colour,
   clamped to 255. */
static void add_lights(float c[3], const p85_vtx *v) {
  for (int i = 0; i < P63_SphN; i++) {
    const float *light = (const float *)((const uint8_t *)G2_011F40E0 + (size_t)(uint32_t)P63_Hits[i] * 0x24);
    float dx = light[0] - v->vx, dy = light[1] - v->vy, dz = light[2] - v->z;
    float dist_sq = dx * dx + dy * dy;
    dist_sq = dist_sq + dz * dz;
    if (dist_sq < light[7]) {                      /* радиус² */
      float strength = light[7] - dist_sq;
      strength = strength * light[8];
      for (int k = 0; k < 3; k++) {
        float x = strength * light[4 + k];
        c[k] = x + c[k];
        if (c[k] > 255.0f) c[k] = 255.0f;
      }
    }
  }
}
/* set_color / set_uv — local helpers: rasteriser vertex colour, and texture u/v pre-multiplied by 1/z. */
static void set_color(p85_rv *r, const float c[3]) { r->r = c[0]; r->g = c[1]; r->b = c[2]; }
static void set_uv(p85_rv *r, const uint8_t *rec, int off, const p85_vtx *v) {
  r->tmu[0] = rf(rec, off) * v->oow;
  r->tmu[1] = rf(rec, off + 4) * v->oow;
}
/* tex_state — local helper: sets the textured render state (once) and binds texture page rec[2] when it
   changes (P86_TexSrc with the slot's address and info). */
static void tex_state(const uint8_t *rec) {
  if (P85_StateDirty != 4) { P85_StateFn(3, 1, 0, 1, 0); P85_StateDirty = 4; }
  if ((int32_t)rec[2] != P86_CurTex) {
    P86_CurTex = rec[2];
    const P40_Slot *s = &P40_Slots[rec[2]];
    P86_TexSrc(0, s->texaddr, 3, s->info);
  }
}

/* do_tex — local helper shared by the four textured handlers: record layout `f` (vertex count, offsets of
   UVs and colour, record size, "detail" flag).  Projects the vertices, rejects off-screen primitives,
   colour = record colour * face light (+ dynamic lights), then rasterises one triangle (0,1,2) or two
   (0,2,1) + (0,2,3) for a quad.  Detail records are skipped when P86_Detail == 2. */
static void do_tex(uint32_t arg, const p86_fmt *f) {
  const uint8_t *rec = G2_011F4064;
  int32_t vidx[4];
  p85_vtx *v[4];
  for (int i = 0; i < f->nv; i++) vidx[i] = ri(rec, 8 + 4 * i);
  G2_011F4064 = (uint8_t *)rec + f->size;
  for (int i = 0; i < f->nv; i++) v[i] = P85_Prep(vidx[i]);
  if ((uint8_t)P82_Edge) { const p85_vtx *vs[4] = { v[0], v[1], v[2], v[3] }; if (P85_EdgeReject(vs, f->nv)) return; }
  float light = P84_LightIn[ri(rec, 4)];
  float base[3];
  for (int i = 0; i < 3; i++) base[i] = light * rf(rec, f->col + 4 * i);
  /* порядок вершин растеризатора: треугольник (0,1,2); четырёхугольник (0,2,1) и затем (0,2,3) */
  static const int ord[3] = { 0, 2, 1 };
  const int *order = f->nv == 3 ? (const int[3]){ 0, 1, 2 } : ord;
  float col3[3][3];
  for (int i = 0; i < 3; i++) { memcpy(col3[i], base, sizeof base); if (P63_SphN != 0) add_lights(col3[i], v[order[i]]); }
  tex_state(rec);
  P85_SetBlend((uint8_t)arg);
  for (int i = 0; i < 3; i++) {
    p85_rv *r = &P85_RV[i];
    P85_PutVtx(r, v[order[i]]);
    set_uv(r, rec, f->uv + 8 * order[i], v[order[i]]);
    set_color(r, col3[i]);
  }
  if (!(f->detail && P86_Detail == 2)) P85_CallRaster();
  if (f->nv == 4) {
    float c3[3];
    memcpy(c3, base, sizeof base);
    if (P63_SphN != 0) add_lights(c3, v[3]);
    P85_PutVtx(&P85_RV[2], v[3]);
    set_uv(&P85_RV[2], rec, f->uv + 24, v[3]);
    if (P63_SphN != 0) set_color(&P85_RV[2], c3);
    if (!(f->detail && P86_Detail == 2)) P85_CallRaster();
  }
}
/* P86_TexTri / P86_TexQuad / P86_TexTriD / P86_TexQuadD — Game.exe 004335e6 / 00433f4c / 00434c58 / 0043593e.
   Handlers for record types 20 (textured triangle), 21 (quad), 22 / 23 (the same with extra data,
   skipped at low detail).  arg = blend mode. */
void P86_TexTri(uint32_t arg) { do_tex(arg, &F20); }
void P86_TexQuad(uint32_t arg) { do_tex(arg, &F21); }
void P86_TexTriD(uint32_t arg) { do_tex(arg, &F22); }
void P86_TexQuadD(uint32_t arg) { do_tex(arg, &F23); }

/* гуро: цвет записи × освещённость нормали вершины */
/* do_gouraud — local helper for the Gouraud handlers: colour = record colour * per-vertex normal light. */
static void do_gouraud(uint32_t arg, int nv, int nloff, int coloff, int size) {
  const uint8_t *rec = G2_011F4064;
  int32_t vidx[4];
  p85_vtx *v[4];
  for (int i = 0; i < nv; i++) vidx[i] = ri(rec, 8 + 4 * i);
  G2_011F4064 = (uint8_t *)rec + size;
  for (int i = 0; i < nv; i++) v[i] = P85_Prep(vidx[i]);
  if ((uint8_t)P82_Edge) { const p85_vtx *vs[4] = { v[0], v[1], v[2], v[3] }; if (P85_EdgeReject(vs, nv)) return; }
  float col[3];
  for (int i = 0; i < 3; i++) col[i] = rf(rec, coloff + 4 * i);
  static const int ord4[3] = { 0, 2, 1 };
  const int *order = nv == 3 ? (const int[3]){ 0, 1, 2 } : ord4;
  P85_CallState();
  P85_SetBlend((uint8_t)arg);
  for (int i = 0; i < 3; i++) {
    p85_rv *r = &P85_RV[i];
    float norm_light = P84_NormLight[ri(rec, nloff + 4 * order[i])];
    P85_PutVtx(r, v[order[i]]);
    r->r = col[0] * norm_light; r->g = col[1] * norm_light; r->b = col[2] * norm_light;
  }
  P85_CallRaster();
  if (nv == 4) {
    float norm_light = P84_NormLight[ri(rec, nloff + 12)];
    P85_PutVtx(&P85_RV[2], v[3]);
    P85_RV[2].r = col[0] * norm_light; P85_RV[2].g = col[1] * norm_light; P85_RV[2].b = col[2] * norm_light;
    P85_CallRaster();
  }
}
/* P86_GouraudTri / P86_GouraudQuad — Game.exe 00432b77 / 00433017.  Handlers for record types 50 / 51
   (untextured, smooth-shaded triangle / quad). */
void P86_GouraudTri(uint32_t arg) { do_gouraud(arg, 3, 0x14, 0x20, 0x2c); }
void P86_GouraudQuad(uint32_t arg) { do_gouraud(arg, 4, 0x18, 0x28, 0x34); }

#ifndef RE_HOOK_BUILD
int32_t P86_TexCount;
static int g_tex[256], g_texw[256];
static int g_bound;
int32_t P86_TexpackN, P86_TexpackRejected;
/* v2.18: 8-битные страницы. В Glide страница пары — GR_TEXFMT_P_8 (fill_block формат 5), цвет — по палитре, которую
   P12_Fn00426580 (00426580) загружает grTexDownloadTable во время рисования (слот палитры — g_01252b74; карта — 1, небо и часть
   объектов — свои слоты; список (страница → палитры) уровня — LEVELS\*.D3D, P58_Tab4EFC03, по нему D3D-эмуляция 0041d63b
   заранее делает текстуру на каждую пару). Здесь (рисование через native_texsrc — проверка рендера test_real_level) хранятся
   индексы страницы и текстура на пару (страница, слот палитры): при загрузке — по списку D3D и палитре по умолчанию, прочие —
   при первом рисовании. Альфа 255 (у P_8 нет альфы, chroma-key игра не включает; в 004229fa прозрачный индекс -1 — выключен).
   До v2.18 бралась одна палитра (1) на все страницы. */
/* игра рисует через D3D-эмуляцию Game.exe (P151 ставит P86_TexSrc = 0041f76f, P53_SetTexSource) — текстуры P86 там не используются */
/* game_path — native helper: 1 when the game draws through Game.exe's D3D emulation (texture source set to
   P53_SetTexSource), so P86's own GL textures are not used. */
static int game_path(void) { return P86_TexSrc != NULL && P86_TexSrc == (p86_texsrc_fn)P53_SetTexSource; }
#define P86_NPAL 64                      /* слотов в таблице 01252be0; 63 — серый (нет загруженной палитры) */
static uint8_t *g_raw8[256];
static int g_ptex[256][P86_NPAL], g_ptexw[256][P86_NPAL];
static uint8_t g_palcopy[P86_NPAL][0x400];
static unsigned char g_palhave[P86_NPAL];
static int g_last_slot = -1, g_last_pal = -2, g_last_h;
int32_t P86_Texpack8N, P86_Pal8Tex;
/* RE_TEXLOG=файл: статистика рисования по парам (страница, палитра) — треугольники и площадь на экране 640×480 (пикс.) */
typedef struct { int32_t tris; double area; } p86_stat;
static p86_stat (*g_stat)[P86_NPAL + 1];
/* stat_dump / P86_NativeStatFlush / P86_TexLogOn / clip_area / P86_NativeStat — RE_TEXLOG statistics: per
   (page, palette) triangle count and on-screen area (triangle clipped to 640x480, Sutherland-Hodgman),
   appended to the log file per level. */
static void stat_dump(void) {
  const char *fn = getenv("RE_TEXLOG");
  if (!g_stat || !fn) return;
  FILE *f = fopen(fn, "a");
  if (!f) return;
  char lv[128]; re_texpack_level_name(P77_CurLevelPath, lv, sizeof lv);
  fprintf(f, "# level %s: slot pal(-1 = 16-bit) tris area_px\n", lv);
  for (int s = 0; s < 256; s++) for (int p = 0; p <= P86_NPAL; p++)
    if (g_stat[s][p].tris) fprintf(f, "%d %d %d %.0f\n", s, p == P86_NPAL ? -1 : p, (int)g_stat[s][p].tris, g_stat[s][p].area);
  fclose(f);
  memset(g_stat, 0, sizeof(p86_stat) * 256 * (P86_NPAL + 1));
}
void P86_NativeStatFlush(void) { stat_dump(); }
/* pick_palette / cur_pal — native helpers: palette slot to draw 8-bit pages with: the current slot
   (01252b74) if loaded, else slot 1 or the first loaded one; 63 = grey placeholder. */
static int pick_palette(void) {
  if (P12_01252aa0[1]) return 1;
  for (int i = 0; i < 0x32; i++) if (P12_01252aa0[i]) return i;
  return -1;
}
/* слот палитры для рисования: текущий (g_01252b74), если загружен; иначе прежний выбор (1 или первый загруженный); 63 — серый */
static int cur_pal(void) {
  int p = P12_01252b74;
  if (p < 0 || p >= 0x32 || !P12_01252aa0[p]) p = pick_palette();
  return p < 0 ? P86_NPAL - 1 : p;
}
int P86_TexLogOn(void) { static int on = -1; if (on < 0) on = getenv("RE_TEXLOG") != NULL; return on; }
/* площадь треугольника, обрезанного по экрану игры 640×480 (Сазерленд–Ходжмен) */
static double clip_area(const float *xy) {
  float a[16][2], b[16][2]; int n = 3;
  for (int i = 0; i < 3; i++) { a[i][0] = xy[2 * i]; a[i][1] = xy[2 * i + 1]; }
  for (int e = 0; e < 4 && n > 0; e++) {
    int m = 0, ax = e & 1, lo = e < 2; float lim = lo ? 0.0f : (ax ? 480.0f : 640.0f);
    for (int i = 0; i < n; i++) {
      const float *p = a[i], *q = a[(i + 1) % n];
      int pin = lo ? p[ax] >= lim : p[ax] <= lim, qin = lo ? q[ax] >= lim : q[ax] <= lim;
      if (pin && m < 16) { b[m][0] = p[0]; b[m][1] = p[1]; m++; }
      if (pin != qin && m < 16) { float t = (lim - p[ax]) / (q[ax] - p[ax]); b[m][0] = p[0] + t * (q[0] - p[0]); b[m][1] = p[1] + t * (q[1] - p[1]); m++; }
    }
    n = m; memcpy(a, b, sizeof(float) * 2 * (size_t)m);
  }
  double s = 0;
  for (int i = 0; i < n; i++) s += (double)a[i][0] * a[(i + 1) % n][1] - (double)a[(i + 1) % n][0] * a[i][1];
  return fabs(s) * 0.5;
}
void P86_NativeStat(const float *xy) {
  if (!P86_TexLogOn()) return;
  int s = P86_CurTex;
  if (s < 0 || s >= 256 || (!g_tex[s] && !g_raw8[s])) return;
  if (!g_stat) { g_stat = calloc(256, sizeof *g_stat); if (!g_stat) return; atexit(stat_dump); }
  int p = g_raw8[s] ? cur_pal() : P86_NPAL;
  g_stat[s][p].tris++; g_stat[s][p].area += clip_area(xy);
}
/* pal8_free — frees all palette variants of 8-bit page `slot`. */
static void pal8_free(int slot) {
  for (int p = 0; p < P86_NPAL; p++) { if (g_ptex[slot][p]) plat_tex_free(g_ptex[slot][p]); g_ptex[slot][p] = 0; g_ptexw[slot][p] = 0; }
}
/* путь игры: хэши страниц уровня (16 бит — 128 КБ, 8 бит — 64 КБ) и отметки «файла нет/отклонён» */
static uint64_t g_hash16[256], g_hash8[256]; static unsigned char g_is16[256], g_miss16[256], g_miss8[256][P86_NPAL];
int32_t P86_GameAttachN;
/* fnv64 — FNV-1a 64-bit hash (identifies texture pages by content). */
static uint64_t fnv64(const uint8_t *p, size_t n) { uint64_t h = 1469598103934665603ull; for (size_t i = 0; i < n; i++) { h ^= p[i]; h *= 1099511628211ull; } return h; }
/* P86_NativeReset — frees the previous level's textures, hashes and texture-pack state. */
void P86_NativeReset(void) {
  if (g_stat) stat_dump();
  for (int i = 0; i < 256; i++) { if (g_tex[i]) plat_tex_free(g_tex[i]); g_tex[i] = 0; g_texw[i] = 0; pal8_free(i); free(g_raw8[i]); g_raw8[i] = NULL; }
  memset(g_palhave, 0, sizeof g_palhave);
  memset(g_is16, 0, sizeof g_is16); memset(g_miss16, 0, sizeof g_miss16); memset(g_miss8, 0, sizeof g_miss8);
  memset(g_hash8, 0, sizeof g_hash8); memset(g_hash16, 0, sizeof g_hash16);
  g_last_slot = -1; g_last_pal = -2; g_last_h = 0;
  P86_TexCount = 0; P86_TexpackN = 0; P86_TexpackRejected = 0; P86_Texpack8N = 0; P86_Pal8Tex = 0; P86_GameAttachN = 0;
}
/* v2.17: страница из HD-пака: <RE_TEXPACK>/<уровень>/pNNN.png (NNN = slot = индекс i в P41_LoadTexPages). UV в бэкенде
   нормализованы по странице (u/256 в plat_render.c), поэтому 1024×1024 ложится на те же координаты без масштабирования.
   Сверка с исходной страницей защищает от перепутанной индексации: при большой ошибке остаётся оригинал 256×256. */
/* texpack_try — v2.17: replaces 16-bit page `slot` by <RE_TEXPACK>/<level>/pNNN.png if it matches the
   original page closely enough (guards against wrong indexing).  Returns 1 if used. */
static int texpack_try(int32_t slot, const uint16_t *page) {
  const char *dir = re_texpack_dir();
  if (!dir) return 0;
  char lv[128]; re_texpack_level_name(P77_CurLevelPath, lv, sizeof lv);
  int w = 0, h = 0;
  uint32_t *hd = re_texpack_load(dir, lv, slot, &w, &h);
  if (!hd) return 0;
  double err = 0, am = 0;
  re_texpack_compare(hd, w, h, page, &err, &am);
  if (err > re_texpack_last_tol() || am > RE_TEXPACK_MAX_AMIS) {
    plat_log("[texpack] %s/p%03d.png отклонён: не похож на страницу %d (ошибка %.1f, альфа %.2f%%)\n", lv, (int)slot, (int)slot, err, am * 100.0);
    free(hd); P86_TexpackRejected++; return 0;
  }
  if (g_tex[slot]) plat_tex_free(g_tex[slot]);
  g_tex[slot] = plat_tex_create(w, h, hd);   /* chroma-key/альфа-тест, мипмапы, dilation, aniso — тот же tex_upload */
  free(hd);
  if (!g_tex[slot]) return 0;
  g_texw[slot] = w; P86_TexCount++; P86_TexpackN++;
  return 1;
}
/* HD-текстура пары (страница, палитра) из пака pNNN_cKKKK.png со сверкой с той же страницей в той же палитре; 0 — нет/отклонён */
/* pal8_hd — v2.18: HD texture for (page, palette) from pNNN_cKKKK.png, verified against the page in that
   palette.  Returns the texture or 0 (missing / rejected, remembered in g_miss8). */
static int pal8_hd(int slot, int pal, const uint32_t *px) {
  const char *dir = re_texpack_dir();
  if (!dir || pal >= 0x32 || g_miss8[slot][pal]) return 0;
  char lv[128]; re_texpack_level_name(P77_CurLevelPath, lv, sizeof lv);
  int w = 0, h = 0;
  uint32_t *hd = re_texpack_load8(dir, lv, slot, pal, &w, &h);
  if (!hd) { g_miss8[slot][pal] = 1; return 0; }
  double err = 0, am = 0;
  re_texpack_compare_rgba(hd, w, h, px, &err, &am);
  int t = 0;
  if (err > re_texpack_last_tol() || am > RE_TEXPACK_MAX_AMIS) {
    plat_log("[texpack] %s/p%03d_c%04d.png отклонён: не похож на страницу %d с палитрой %d (ошибка %.1f, альфа %.2f%%)\n", lv, slot, pal, slot, pal, err, am * 100.0);
    P86_TexpackRejected++; g_miss8[slot][pal] = 1;
  } else if ((t = plat_tex_create(w, h, hd))) {
    g_ptex[slot][pal] = t; g_ptexw[slot][pal] = w; P86_TexpackN++; P86_Texpack8N++; P86_Pal8Tex++;
  }
  free(hd);
  return t;
}
/* текстура пары (страница slot, палитра pal): HD из пака или 256×256 по палитре */
/* pal8_make — texture for (page slot, palette pal): the HD one if available, else 256x256 through the palette. */
static int pal8_make(int slot, int pal) {
  static uint32_t px[256 * 256];
  const uint8_t *pe = pal < 0x32 ? &P14_01252be0[pal * 0x400] : NULL;
  if (pe) { memcpy(g_palcopy[pal], pe, 0x400); g_palhave[pal] = 1; }
  re_texpack_pal8_rgba(g_raw8[slot], pe, px);
  if (pe && pal8_hd(slot, pal, px)) return g_ptex[slot][pal];
  g_ptex[slot][pal] = plat_tex_create(256, 256, px);
  if (g_ptex[slot][pal]) { g_ptexw[slot][pal] = 256; P86_Pal8Tex++; }
  return g_ptex[slot][pal];
}
/* pal_changed_check — drops the cached textures of palette slot pal when its contents changed. */
static void pal_changed_check(int pal) {
  if (pal < 0x32 && g_palhave[pal] && memcmp(g_palcopy[pal], &P14_01252be0[pal * 0x400], 0x400) != 0) {
    for (int s = 0; s < 256; s++) if (g_ptex[s][pal]) { plat_tex_free(g_ptex[s][pal]); g_ptex[s][pal] = 0; g_ptexw[s][pal] = 0; }
    for (int s = 0; s < 256; s++) g_miss8[s][pal] = 0;
    g_palhave[pal] = 0;   /* содержимое слота палитры сменилось — текстуры этой палитры пересоздаются */
    g_last_slot = -1;
  }
}
/* pal8_handle — cached lookup / creation of the (page, palette) texture. */
static int pal8_handle(int slot, int pal) {
  if (slot == g_last_slot && pal == g_last_pal) return g_last_h;
  pal_changed_check(pal);
  int h = g_ptex[slot][pal] ? g_ptex[slot][pal] : pal8_make(slot, pal);
  g_last_slot = slot; g_last_pal = pal; g_last_h = h;
  return h;
}
/* P86_NativeCaptureEnd — logs the texture-pack summary after a level's pages are loaded. */
void P86_NativeCaptureEnd(void) {
  const char *dir = re_texpack_dir();
  if (!dir) return;
  char lv[128]; re_texpack_level_name(P77_CurLevelPath, lv, sizeof lv);
  if (game_path()) plat_log("[texpack] игра: HD-пак %s/%s — страницы подменяются при загрузке в GL (сверка с памятью поверхности)\n", dir, lv);
  else plat_log("[texpack] загружено %d страниц, из них 8-битных пар (страница, палитра) %d (%s/%s, отклонено %d)\n", (int)P86_TexpackN, (int)P86_Texpack8N, dir, lv, (int)P86_TexpackRejected);
}
/* P86_NativeHandle / P86_NativeTexW / P86_NativeTexW8 — GL texture of page slot (with the current or the
   given palette for 8-bit pages) and its width (256, or the HD width). */
int P86_NativeHandle(int32_t slot) {
  if (slot < 0 || slot >= 256) return 0;
  if (g_raw8[slot] && !game_path()) return pal8_handle(slot, cur_pal());
  return g_tex[slot];
}
int P86_NativeTexW(int32_t slot) {
  if (slot < 0 || slot >= 256) return 0;
  if (g_raw8[slot] && !game_path()) { int h = P86_NativeHandle(slot); return h ? g_ptexw[slot][cur_pal()] : 0; }
  return g_tex[slot] ? g_texw[slot] : 0;
}
int P86_NativeTexW8(int32_t slot, int32_t pal) {
  if (slot < 0 || slot >= 256 || pal < 0 || pal >= P86_NPAL || !g_raw8[slot]) return 0;
  return pal8_handle(slot, pal) ? g_ptexw[slot][pal] : 0;
}
/* ---- v2.18: путь игры. 8-битная страница в native-игре — PAL8-поверхность аппаратного слота (P109_SlotUpload8; палитра —
   P32_SetPalette по 00426580), на устройствах без PAL8 — эмулированная текстура пары (P149_EmulNew/AddSub 004225eb/0042248b);
   16-битная — поверхность слота (P109_SlotUpload16, кэш 32 слотов). Страница узнаётся по хэшу данных. ---- */
/* pal_match / game_pal8_tex — game path: find which palette slot a PAL8 surface's palette is (r, g, b vs the
   B, G, R table 01252be0) and return the HD texture for (page, that palette). */
static int pal_match(int k, const uint8_t *rgba) {   /* записи палитры поверхности r,g,b,flags ↔ слот k таблицы (B,G,R,X) */
  const uint8_t *e = &P14_01252be0[k * 0x400];
  for (int i = 0; i < 256; i++) if (rgba[i * 4] != e[i * 4 + 2] || rgba[i * 4 + 1] != e[i * 4 + 1] || rgba[i * 4 + 2] != e[i * 4]) return 0;
  return 1;
}
static int game_pal8_tex(int page, uint64_t key, const uint8_t *pal_rgba) {
  if (page < 0 || page >= 256 || !g_raw8[page] || g_hash8[page] != key || !pal_rgba || !re_texpack_dir()) return 0;
  int k = P12_01252b74;
  if (k < 0 || k >= 0x32 || !P12_01252aa0[k] || !pal_match(k, pal_rgba)) {
    k = -1;
    for (int i = 0; i < 0x32 && k < 0; i++) if (P12_01252aa0[i] && pal_match(i, pal_rgba)) k = i;
    if (k < 0) return 0;
  }
  pal_changed_check(k);
  if (g_ptex[page][k]) return g_ptex[page][k];
  if (g_miss8[page][k]) return 0;
  static uint32_t px[256 * 256];
  memcpy(g_palcopy[k], &P14_01252be0[k * 0x400], 0x400); g_palhave[k] = 1;
  re_texpack_pal8_rgba(g_raw8[page], &P14_01252be0[k * 0x400], px);
  int t = pal8_hd(page, k, px);
  if (t) P86_GameAttachN++;
  return t;
}
/* P86_GameTag8 / P86_GameAttachEmul8 / P86_GameAttach16 — game path: tag a hardware PAL8 surface with its
   page index, or attach the HD image to an emulated (page, palette) surface / a 16-bit page surface
   found by content hash; the GL upload compares it with the surface (re_texpack_merge). */
void P86_GameTag8(void *surf, const uint8_t *src) {
  if (!surf || !src || !re_texpack_dir()) return;
  uint64_t hs = fnv64(src, 0x10000);
  for (int i = 0; i < 256; i++) if (g_raw8[i] && g_hash8[i] == hs) { plat_dd_tag_page8(surf, i, hs); return; }
}
void P86_GameAttachEmul8(void *surf, int32_t page, int32_t pal) {
  const char *dir = re_texpack_dir();
  if (!dir || !surf || page < 0 || page >= 256 || pal < 0 || pal >= 0x32 || g_miss8[page][pal]) return;
  char lv[128]; re_texpack_level_name(P77_CurLevelPath, lv, sizeof lv);
  int w = 0, h = 0;
  uint32_t *hd = re_texpack_load8(dir, lv, page, pal, &w, &h);
  if (!hd) { g_miss8[page][pal] = 1; return; }
  plat_dd_attach_hd(surf, hd, w, page, pal); P86_GameAttachN++;   /* сверка — при загрузке в GL (re_texpack_merge) */
}
void P86_GameAttach16(void *surf, const uint16_t *src) {
  const char *dir = re_texpack_dir();
  if (!dir || !surf || !src) return;
  uint64_t hs = fnv64((const uint8_t *)src, 0x20000);
  for (int i = 0; i < 256; i++) if (g_is16[i] && g_hash16[i] == hs) {
    if (g_miss16[i]) return;
    char lv[128]; re_texpack_level_name(P77_CurLevelPath, lv, sizeof lv);
    int w = 0, h = 0;
    uint32_t *hd = re_texpack_load(dir, lv, i, &w, &h);
    if (!hd) { g_miss16[i] = 1; return; }
    plat_dd_attach_hd(surf, hd, w, i, -1); P86_GameAttachN++;
    return;
  }
}
/* P86_NativeCapture — called from P41_LoadTexPages for each page (pair = two 8-bit pages): game path —
   remember hashes / raw 8-bit data for the texture pack; render-check path — make GL textures (16-bit
   ARGB1555 -> RGBA, 8-bit: one texture per palette listed for the page in LEVELS\*.D3D plus the default). */
void P86_NativeCapture(int32_t slot, int pair, const void *page0, const void *page1) {
  static uint32_t px[256 * 256];
  if (slot < 0 || slot >= 256) return;
  if (game_path()) {   /* игра: GL-текстуры P86 не нужны; хэши страниц и индексы 8-битных — для HD-пака */
    plat_dd_set_pal8_provider(game_pal8_tex);
    if (!pair) { g_is16[slot] = 1; g_hash16[slot] = fnv64((const uint8_t *)page0, 0x20000); return; }
    for (int h = 0; h < 2 && slot + h < 256; h++) {
      int sl = slot + h; g_is16[sl] = 0; pal8_free(sl);
      if (!g_raw8[sl]) g_raw8[sl] = (uint8_t *)malloc(0x10000);
      if (!g_raw8[sl]) continue;
      memcpy(g_raw8[sl], h ? page1 : page0, 0x10000);
      g_hash8[sl] = fnv64(g_raw8[sl], 0x10000);
    }
    return;
  }
  if (!pair) {
    const uint16_t *s = (const uint16_t *)page0;       /* ARGB1555 */
    if (texpack_try(slot, s)) return;
    for (int i = 0; i < 256 * 256; i++) {
      uint16_t w = s[i];
      uint32_t r = (w >> 10) & 31, g = (w >> 5) & 31, b = w & 31, a = (w & 0x8000) ? 255u : 0u;
      r = r << 3 | r >> 2; g = g << 3 | g >> 2; b = b << 3 | b >> 2;
      px[i] = a << 24 | b << 16 | g << 8 | r;
    }
    if (g_tex[slot]) plat_tex_free(g_tex[slot]);
    g_tex[slot] = plat_tex_create(256, 256, px);
    if (g_tex[slot]) { P86_TexCount++; g_texw[slot] = 256; }
    return;
  }
  for (int h = 0; h < 2 && slot + h < 256; h++) {
    int sl = slot + h;
    if (g_tex[sl]) { plat_tex_free(g_tex[sl]); g_tex[sl] = 0; g_texw[sl] = 0; }
    pal8_free(sl);
    if (!g_raw8[sl]) g_raw8[sl] = (uint8_t *)malloc(0x10000);
    if (!g_raw8[sl]) continue;
    memcpy(g_raw8[sl], h ? page1 : page0, 0x10000);
    memset(g_miss8[sl], 0, sizeof g_miss8[0]);
    g_last_slot = -1;
    /* заранее: палитры страницы из списка D3D (как 0041d63b) и палитра по умолчанию — HD-PNG грузятся при загрузке уровня */
    int made = 0;
    const p58_rec_t *rec = P58_Tab4EFC03;
    for (int i = 0; rec && i < P58_Cnt4EFC03; i++) if (rec[i].a == sl && rec[i].p) {
      const int32_t *l = (const int32_t *)rec[i].p;
      for (int j = 0; j < rec[i].c; j++) if (l[j] >= 0 && l[j] < 0x32 && P12_01252aa0[l[j]] && !g_ptex[sl][l[j]]) { pal8_make(sl, l[j]); made++; }
    }
    int p = cur_pal();
    if (!g_ptex[sl][p]) pal8_make(sl, p);
    if (g_ptex[sl][p] || made) P86_TexCount++;
  }
}
/* native_texsrc — native replacement for the texture-source call: binds the GL texture of P86_CurTex. */
static void native_texsrc(int32_t tmu, uint32_t addr, int32_t mask, uint32_t info) {
  (void)tmu; (void)addr; (void)mask; (void)info;
  g_bound = P86_NativeHandle(P86_CurTex);
  plat_tex_bind(g_bound);
}
/* _grAlphaTestFunction@4 в native: GR_CMP_ALWAYS (7) — альфа-тест выключен (так рисуется всё непрозрачное,
   в т.ч. асфальт — у его текселей ARGB1555 бит альфы 0), остальные функции — отбрасывание по альфе */
/* native_alpha_test — native grAlphaTestFunction: GR_CMP_ALWAYS (7) disables alpha testing (opaque surfaces,
   asphalt texels have alpha bit 0), any other function discards by alpha. */
static void native_alpha_test(int32_t fn) { plat_set_render_state(15, fn != 7); }
/* P86_NativeInit — installs the native texture source / alpha test and the handlers above for record types
   20..23, 50, 51 in all 6 handler tables. */
void P86_NativeInit(void) {
  P33_SetNativeProc("_grAlphaTestFunction@4", (void *)native_alpha_test);
  native_alpha_test(7);                                /* состояние Glide после grSstWinOpen — GR_CMP_ALWAYS */
  P86_TexSrc = native_texsrc;
  P86_CurTex = -1;
  for (int t = 0; t < 6; t++) {
    P84_Handlers[t][20] = (uintptr_t)P86_TexTri;
    P84_Handlers[t][21] = (uintptr_t)P86_TexQuad;
    P84_Handlers[t][22] = (uintptr_t)P86_TexTriD;
    P84_Handlers[t][23] = (uintptr_t)P86_TexQuadD;
    P84_Handlers[t][50] = (uintptr_t)P86_GouraudTri;
    P84_Handlers[t][51] = (uintptr_t)P86_GouraudQuad;
  }
}
#endif
