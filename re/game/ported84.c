/* ported84.c — the model renderer (English overview).  A model = header (+2 flags, +0x16 record count,
   +0x18 normal count, +0x20 vertices, +0x24 planes, +0x28 normals, +0x2c record list) + records (polygons) of
   56 types; each record is drawn by a handler from the active table (P84_Tab0/1/2 = draw modes 0 = no
   clipping, 1 = near-plane clipping, 2 = other).  Records with flag 8 are back-face culled against their plane;
   others reuse the cached visibility of their plane (P84_Vis).  Lit models (flag 1) get per-normal and
   per-plane light = ambient + max(0, n.L), clamped to 1.  Entry points: P84_DrawModel (00428b69, any matrix),
   P84_DrawModelIdx (00429143, cached orientation matrix), P84_DrawModelC (0042b7cb, constant light),
   P84_DrawCar (0042a9f1, car body with the environment shine).  Flag 0x4000 = billboard facing the camera
   heading.  Native: handler tables are built from Game.exe's own .data tables (init_game_handlers). */
#include <stdio.h>
#include "ported84.h"
#include "ported8.h"
#include "ported11.h"
#include "ported28.h"
#include "ported33.h"
#include "ported62.h"
#include "ported86.h"
#include "ported98.h"
#include "ported102.h"
#include "reptr.h"
#include "ported85.h"
#include "redbg.h"
#include "cartab.h"
#ifndef RE_HOOK_BUILD
#include "../platform/native/diagnostics.h"
#endif
#include <math.h>
#include <string.h>

#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P84_Mirror")
#undef P84_Mirror
#pragma push_macro("P84_Mirror") /*gvi*/
#undef P84_Mirror /*gvi*/
uint8_t P84_Mirror;
#pragma pop_macro("P84_Mirror") /*gvi*/
#pragma pop_macro("P84_Mirror")
#endif
GAME_VAR_DEF(const uintptr_t *, P84_Tab0, 0x011effe0)
GAME_VAR_DEF(const uintptr_t *, P84_Tab1, 0x01209660)
GAME_VAR_DEF(const uintptr_t *, P84_Tab2, 0x011f4060)
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P84_VertRef")
#undef P84_VertRef
#pragma push_macro("P84_VertRef") /*gvi*/
#undef P84_VertRef /*gvi*/
uint32_t P84_VertRef;
#pragma pop_macro("P84_VertRef") /*gvi*/
#pragma pop_macro("P84_VertRef")
#endif
GAME_VAR_DEF(float *, P84_Planes, 0x012085f0)
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P84_LightIn")
#undef P84_LightIn
#pragma push_macro("P84_LightIn") /*gvi*/
#undef P84_LightIn /*gvi*/
p84_light_t P84_LightIn;
#pragma pop_macro("P84_LightIn") /*gvi*/
#pragma pop_macro("P84_LightIn")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P84_Vis")
#undef P84_Vis
#pragma push_macro("P84_Vis") /*gvi*/
#undef P84_Vis /*gvi*/
p84_vis_t P84_Vis;
#pragma pop_macro("P84_Vis") /*gvi*/
#pragma pop_macro("P84_Vis")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P84_NormLight")
#undef P84_NormLight
#pragma push_macro("P84_NormLight") /*gvi*/
#undef P84_NormLight /*gvi*/
p84_nlight_t P84_NormLight;
#pragma pop_macro("P84_NormLight") /*gvi*/
#pragma pop_macro("P84_NormLight")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P84_MatCache")
#undef P84_MatCache
#pragma push_macro("P84_MatCache") /*gvi*/
#undef P84_MatCache /*gvi*/
p84_mats_t P84_MatCache;
#pragma pop_macro("P84_MatCache") /*gvi*/
#pragma pop_macro("P84_MatCache")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P84_MatFlag")
#undef P84_MatFlag
#pragma push_macro("P84_MatFlag") /*gvi*/
#undef P84_MatFlag /*gvi*/
p84_flags_t P84_MatFlag;
#pragma pop_macro("P84_MatFlag") /*gvi*/
#pragma pop_macro("P84_MatFlag")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P84_Arg")
#undef P84_Arg
#pragma push_macro("P84_Arg") /*gvi*/
#undef P84_Arg /*gvi*/
p84_b56_t P84_Arg;
#pragma pop_macro("P84_Arg") /*gvi*/
#pragma pop_macro("P84_Arg")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P84_Lit")
#undef P84_Lit
#pragma push_macro("P84_Lit") /*gvi*/
#undef P84_Lit /*gvi*/
p84_b56_t P84_Lit;
#pragma pop_macro("P84_Lit") /*gvi*/
#pragma pop_macro("P84_Lit")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P84_TexFiltOn")
#undef P84_TexFiltOn
#pragma push_macro("P84_TexFiltOn") /*gvi*/
#undef P84_TexFiltOn /*gvi*/
int32_t P84_TexFiltOn;
#pragma pop_macro("P84_TexFiltOn") /*gvi*/
#pragma pop_macro("P84_TexFiltOn")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P84_ShineK")
#undef P84_ShineK
#pragma push_macro("P84_ShineK") /*gvi*/
#undef P84_ShineK /*gvi*/
float P84_ShineK;
#pragma pop_macro("P84_ShineK") /*gvi*/
#pragma pop_macro("P84_ShineK")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P84_ShineUV")
#undef P84_ShineUV
#pragma push_macro("P84_ShineUV") /*gvi*/
#undef P84_ShineUV /*gvi*/
p84_uv_t P84_ShineUV;
#pragma pop_macro("P84_ShineUV") /*gvi*/
#pragma pop_macro("P84_ShineUV")
#endif
#ifndef RE_HOOK_BUILD
uintptr_t P84_Handlers[6][56];
#include "p84_data.h"
void P84_InitConsts(void) {
  memcpy(P84_Arg, P84_ArgInit, 56);
  memcpy(P84_Lit, P84_LitInit, 56);
}
#include "p84_handlers.h"
/* v2.05: в игре P84_Handlers заполняются по таблицам .data Game.exe (0055082c.. — программный набор, 00550cfc.. — аппаратный):
   адрес → перенос (re_fn); неперенесённый обработчик — P85_SkipRecord (запись пропускается, как было бы без рисования).
   До v2.05 в native-игре таблицы были нулевыми — P84 не рисовал ни одной записи (чёрный кадр уровня). */
int P84_HandMissing, P84_HandSubst, P84_HandNoClip;
/* Native: fills P84_Handlers[6][56] from the handler addresses of Game.exe (.data 0055082c = D3D set,
   00550cfc = Glide set), substituting the Glide or no-clipping handler where a port is missing, else
   P85_SkipRecord; counts are printed once. */
static void init_game_handlers(void) {
  static int done;
  if (done || !re_ptr_has_image()) return;
  done = 1; P84_HandMissing = 0;
  for (int t = 0; t < 6; t++)
    for (int k = 0; k < 56; k++) {
      uint32_t a = P84_HandAddr[t][k];
      if (a == 0) { P84_Handlers[t][k] = 0; continue; }
      re_fn_t f = re_fn(a);
      /* D3D-набор (0055082c.., b1c0d8 = 1) перенесён лишь частично (P115_*C — типы 0..3; остальные обработчики 00453759..004737c4
         не опознаны Ghidra как функции): вместо неперенесённого — обработчик того же типа из Glide-набора (00550cfc..), он рисует
         через ячейки таблицы Glide (01270e08 grDrawTriangle …), которые P151_InstallD3D направляет в D3D-эмуляцию. */
      if (f == NULL && t < 3 && P84_HandAddr[t + 3][k] != 0) { f = re_fn(P84_HandAddr[t + 3][k]); if (f) P84_HandSubst++; }
      /* Отступление native: наборы с отсечением (режим 1 — ближняя плоскость, «другой» — дальняя) почти целиком не перенесены
         (0x436ab0.., 0x446e8a.. — тоже не опознаны Ghidra); вместо них — обработчик режима 0 того же типа без отсечения
         (как P85_RegisterNative в тестах города). Полигоны, пересекающие ближнюю плоскость, рисуются без отсечения. */
      if (f == NULL && (t % 3) != 0) {
        int b = t - (t % 3);
        if (P84_HandAddr[b][k] != 0) f = re_fn(P84_HandAddr[b][k]);
        if (f == NULL && b == 0 && P84_HandAddr[3][k] != 0) f = re_fn(P84_HandAddr[3][k]);
        if (f) P84_HandNoClip++;
      }
      if (f == NULL) { f = (re_fn_t)P85_SkipRecord; P84_HandMissing++; }
      P84_Handlers[t][k] = (uintptr_t)f;
    }
  fprintf(stderr, "[p84] обработчики записей из .data Game.exe: из Glide-набора %d, без отсечения %d, неперенесённых %d (P85_SkipRecord)\n", P84_HandSubst, P84_HandNoClip, P84_HandMissing);
}
/* 011effe0/01209660/011f4060 ← таблицы набора (режимы 0, 1, другой) */
/* P84_SelectTables — native: makes P84_Tab0/1/2 point at the D3D (alt = 0) or Glide (alt = 1) handler set. */
void P84_SelectTables(int32_t alt) {
  init_game_handlers();
  if (re_ptr_has_image()) fprintf(stderr, "[p84] набор таблиц %s\n", alt ? "аппаратный 00550cfc" : "программный 0055082c");
  P84_Tab0 = P84_Handlers[alt ? 3 : 0];
  P84_Tab1 = P84_Handlers[alt ? 4 : 1];
  P84_Tab2 = P84_Handlers[alt ? 5 : 2];
}
#else
void P84_InitConsts(void) {}
#endif

typedef long double ld;
/* Sign bit of a float (as the original tests it; -0.0 counts as negative). */
static int neg(float f) { uint32_t u; memcpy(&u, &f, 4); return (int)(u >> 31); }
/* (a·x + b·y) + c·z в расширенной точности, затем во float, как fld/fmul/faddp/fstp */
static float dot3(const float *a, float x, float y, float z) {
  ld r = (ld)x * (ld)a[0];
  r += (ld)y * (ld)a[1];
  r += (ld)z * (ld)a[2];
  return (float)r;
}
/* освещение: dot < 0 (знаковый бит) → фон; иначе фон + dot, не больше 1.0 (сравнение как целых) */
/* Light value: ambient P19_Out68 when n.L is negative, else ambient + n.L clamped to 1.0 (integer compare). */
static float shade(float d) {
  float amb = P19_Out68;
  if (neg(d)) return amb;
  d = (float)((ld)amb + (ld)d);
  { int32_t u; memcpy(&u, &d, 4); if (u > 0x3f800000) d = 1.0f; }
  return d;
}
/* Calls the handler for record `type` with its argument byte P84_Arg[type] (native diagnostics around it). */
static void call_h(const uintptr_t *tab, uint32_t type) {
  uintptr_t f = tab ? tab[type] : 0;
  RE_DBG(9);
#ifndef RE_HOOK_BUILD
  if (f == (uintptr_t)P85_SkipRecord) RE_DBG(5);
  re_diag_record(P79_OFF(G2_011F4064), type, !f || f == (uintptr_t)P85_SkipRecord);
#endif
  if (f) ((p84_handler_t)f)((uint32_t)P84_Arg[type]);
}

/* общая часть 00428b69/00429143: mdl — заголовок, modmat — матрица модели (для света), viewm — ViewMat×modmat */
static void call_ha(const uintptr_t *tab, uint32_t type, uint32_t arg) {
  uintptr_t f = tab ? tab[type] : 0;
#ifndef RE_HOOK_BUILD
  re_diag_record(P79_OFF(G2_011F4064), type, !f || f == (uintptr_t)P85_SkipRecord);
#endif
  if (f) ((p84_handler_t)f)(arg);
}
/* var = 0 — 00428b69/00429143; var = 1 — 0042b7cb (аргумент обработчика 2 без света / 3 со светом, свет плоскости = shade(0.01)) */
static void draw_core(uint8_t *mdl, const float *modmat, const float *viewm, const float *pos, const uintptr_t *tab, int var) {
#ifndef RE_HOOK_BUILD
  re_diag_model(P79_OFF(mdl));
#endif
  uint16_t flags = *(uint16_t *)(mdl + 2), nrec = *(uint16_t *)(mdl + 0x16), nnrm = *(uint16_t *)(mdl + 0x18);
  float lx = 0, ly = 0, lz = 0;
  static float local[16];   /* зеркальная копия матрицы остаётся в P44_MatPtr после возврата (в оригинале — стек) */
  float p3[3] = { pos[0], pos[1], pos[2] };
  float nx, ny, nz;
  int lit = flags & 1;
  RE_DBG(8);
  if (lit) {
    float lv[4] = { P19_OutA, P19_OutB, P19_OutC, 0 };   /* 4-е слово (005507dc) Xform не читает */
    P44_MatPtr = (float *)modmat;
    P44_Xform(lv);
    lx = lv[0]; ly = lv[1]; lz = lv[2];
  }
  P44_MatPtr = (float *)viewm;
  P44_XformT(p3);
  nx = -p3[0]; ny = -p3[1]; nz = -p3[2];
  G2_011F4064 = (uint8_t *)P79_PTR(*(uint32_t *)(mdl + 0x2c));
  if (P84_Mirror) {
    memcpy(local, viewm, sizeof(local));
    local[0] = -local[0]; local[3] = -local[3]; local[6] = -local[6];
    P44_MatPtr = local;
  }
  if (lit) {
    const float *n = (const float *)P79_PTR(*(uint32_t *)(mdl + 0x28));
    for (int i = 0; i < nnrm; i++, n += 4) P84_NormLight[i] = shade(dot3(n, lx, ly, lz));
  }
#ifndef RE_HOOK_BUILD
  static int s_md = -2; if (s_md == -2) s_md = getenv("RE_MDLDBG") ? (int)strtol(getenv("RE_MDLDBG"), NULL, 16) : -1;
  int dbgm = (s_md >= 0 && P79_OFF(mdl) == (uint32_t)s_md); static int s_mdk;
  if (dbgm && s_mdk < 3) fprintf(stderr, "[mdl] %06x flags %04x nrec %d tab %p\n", (unsigned)s_md, flags, nrec, (const void *)tab);
  if (dbgm && s_mdk < 1) { const float *vv = (const float *)P79_PTR(*(uint32_t *)(mdl + 0x20)); const uint16_t *h = (const uint16_t *)mdl;
    fprintf(stderr, "[mdl] hdr"); for (int q = 0; q < 0x1c; q++) fprintf(stderr, " %04x", h[q]); fprintf(stderr, "\n");
    for (int q = 0; q < 16; q++) fprintf(stderr, "[mdl]  v%d %.1f %.1f %.1f %.1f\n", q, vv[q*4], vv[q*4+1], vv[q*4+2], vv[q*4+3]);
    const uint8_t *r = (const uint8_t *)P79_PTR(*(uint32_t *)(mdl + 0x2c)); fprintf(stderr, "[mdl]  rec0"); for (int q = 0; q < 40; q++) fprintf(stderr, " %02x", r[q]); fprintf(stderr, "\n"); }
#endif
  for (int i = 0; i < nrec; i++) {
    uint8_t *rec = G2_011F4064;
    uint32_t type = rec[0];
#ifndef RE_HOOK_BUILD
    if (dbgm && s_mdk < 3) fprintf(stderr, "[mdl]  rec %d type %u f1 %02x plane %d vis %d h %s\n", i, type, rec[1], *(int32_t *)(rec + 4), P84_Vis[*(int32_t *)(rec + 4)],
        tab[type] == (uintptr_t)P85_SkipRecord ? "SKIP" : "ok");
    if (dbgm && s_mdk < 3) { float cc[3]; memcpy(cc, rec + 0x38, 12); fprintf(stderr, "[mdl]   lit %d lightin %f col %.1f %.1f %.1f lv %f %f %f\n", P84_Lit[type], P84_LightIn[*(int32_t *)(rec + 4)], cc[0], cc[1], cc[2], lx, ly, lz); }
    if (dbgm && i == nrec - 1) s_mdk++;
#endif
    int32_t pi = *(int32_t *)(rec + 4);
    float *pl = P84_Planes + (size_t)pi * 4;
    uint8_t *vis = &P84_Vis[pi];
    int step = G2_TABLE_00550ACC[type];
    if (!(rec[1] & 8)) {
      if (!*vis) {
#ifndef RE_HOOK_BUILD
        re_diag_record(P79_OFF(rec), type, 2);
#endif
        G2_011F4064 = rec + step;
      }
      else if (var) call_ha(tab, type, lit ? 3u : 2u);
      else call_h(tab, type);
    } else {
      ld a = (ld)nx * (ld)pl[0];
      a += (ld)ny * (ld)pl[1];
      a += (ld)nz * (ld)pl[2];
      a -= (ld)pl[3];
      if (!neg((float)a)) {
#ifndef RE_HOOK_BUILD
        re_diag_record(P79_OFF(rec), type, 2);
#endif
        *vis = 0; G2_011F4064 = rec + step;
      }
      else {
        *vis = 1;
        if (lit && P84_Lit[type]) P84_LightIn[pi] = var ? shade(0.01f) : shade(dot3(pl, lx, ly, lz));
        if (var) call_ha(tab, type, lit ? 3u : 2u); else call_h(tab, type);
      }
    }
  }
  P44_XformTag++;
#ifndef RE_HOOK_BUILD
  re_diag_model(UINT32_MAX);
#endif
}

/* Handler table for draw mode (low byte): 0 -> P84_Tab0, 1 -> P84_Tab1, else P84_Tab2. */
static const uintptr_t *pick_tab(int32_t mode) {
  uint8_t m = (uint8_t)mode;
  return m == 1 ? P84_Tab1 : (m == 0 ? P84_Tab0 : P84_Tab2);
}
/* Common start of every entry point: light spheres touching the model, transform bias = pos (x negated in
   the mirror), model vertices and planes. */
static void prologue(uint8_t *mdl, uint32_t mref, const float *pos) {
  if (G2_011F43B0 == 0) P63_SphN = 0; else P63_SphereHits(pos, (const uint8_t *)mdl);
  (void)mref;
  P44_BiasX = P84_Mirror ? -pos[0] : pos[0];
  P44_BiasY = pos[1];
  P44_BiasZ = pos[2];
  P84_VertRef = *(uint32_t *)(mdl + 0x20);
  P84_Planes = (float *)P79_PTR(*(uint32_t *)(mdl + 0x24));
}

/* 00428b69 */
/* P84_DrawModel — Game.exe 00428b69, cdecl.  Draws model mref with orientation matrix mat at world position pos
   in draw mode `mode` (see pick_tab).  Billboards (flag 0x4000) use the matrix for the camera heading instead. */
void P84_DrawModel(uint32_t mref, const float *mat, const float *pos, int32_t mode) {
  uint8_t *mdl = (uint8_t *)P79_PTR(mref);
  float view[16];
  const uintptr_t *tab = pick_tab(mode);
  prologue(mdl, mref, pos);
  if (*(uint16_t *)(mdl + 2) & 0x4000)
    mat = (const float *)(P56_EulerTab + (size_t)(((uint32_t)(-(int32_t)(int16_t)P59_AngB)) & 0xfff) * 0x40);
  memset(view, 0, sizeof(view));
  Mat3Mul_0052859A(P44_ViewMat, mat, view);
  draw_core(mdl, mat, view, pos, tab, 0);
}

/* 00429143 */
/* P84_DrawModelIdx — Game.exe 00429143, cdecl.  As P84_DrawModel with orientation idx into P56_EulerTab; the
   view x orientation product is cached per frame in P84_MatCache[idx] (valid while P84_MatFlag == P47_SwapCnt). */
void P84_DrawModelIdx(uint32_t mref, int32_t idx, const float *pos, int32_t mode) {
  uint8_t *mdl = (uint8_t *)P79_PTR(mref);
  const uintptr_t *tab = pick_tab(mode);
  const float *mat;
  prologue(mdl, mref, pos);
  if (*(uint16_t *)(mdl + 2) & 0x4000) idx = (int32_t)(((uint32_t)(-(int32_t)(int16_t)P59_AngB)) & 0xfff);
  mat = (const float *)(P56_EulerTab + (size_t)idx * 0x40);
  if (P84_MatFlag[idx] != (int32_t)P47_SwapCnt) {
    Mat3Mul_0052859A(P44_ViewMat, mat, P84_MatCache[idx]);
    P84_MatFlag[idx] = (int32_t)P47_SwapCnt;
  }
  draw_core(mdl, mat, P84_MatCache[idx], pos, tab, 0);
}

/* ---- v1.81 ---- */
/* 0042b7cb: как 00428b69 (угол 0x4000 — та же таблица 00b1c280 по −00b1c26a), но обработчик получает константу:
   2 — модель без света, 3 — со светом; освещённость видимой плоскости (P84_Lit[тип]) — shade(0.01) вместо n·L
   (в оригинале dot записывается и сразу перезаписывается 0x3c23d70a). */
void P84_DrawModelC(uint32_t mref, const float *mat, const float *pos, int32_t mode) {
  uint8_t *mdl = (uint8_t *)P79_PTR(mref);
  float view[16];
  const uintptr_t *tab = pick_tab(mode);
  prologue(mdl, mref, pos);
  if (*(uint16_t *)(mdl + 2) & 0x4000)
    mat = (const float *)(P56_EulerTab + (size_t)(((uint32_t)(-(int32_t)(int16_t)P59_AngB)) & 0xfff) * 0x40);
  memset(view, 0, sizeof(view));
  Mat3Mul_0052859A(P44_ViewMat, mat, view);
  draw_core(mdl, mat, view, pos, tab, 1);
}

#ifdef RE_HOOK_BUILD
#  define P84_STD __attribute__((stdcall))
#else
#  define P84_STD
#endif
static void tex_filter(int32_t a, int32_t b, int32_t c) {   /* (*01270d6c) = grTexFilterMode — по имени (как ported124) */
  for (int i = 0; i < P33_GlideCount(); i++)
    if (strcmp(P33_GlideName(i), "_grTexFilterMode@12") == 0) {
      void (P84_STD *f)(int32_t, int32_t, int32_t) = (void (P84_STD *)(int32_t, int32_t, int32_t))P33_GlideProc(i);
      if (f != NULL) f(a, b, c);
      return;
    }
}
/* fistp: round to nearest with the FPU default mode. */
static int32_t fist(ld v) { return (int32_t)lrintl(v); }    /* fistp, округление к ближайшему */

/* 0042a9f1: кузов машины car (00d077c0 + car·0x148). Пролог как 00428b69; один раз grTexFilterMode(0,1,1) (флаг 01252bc0);
   ViewMat×mat; освещение нормалей — всегда (свет через mat). Записи обходятся подряд: плоскость и освещённость берутся по номеру
   записи (не по +4), без кэша видимости. Обычный режим (нет 0055c974 или shk = 0): P86_Detail = 0, обработчики по P84_Arg.
   Блик (shk ≠ 0): UV нормалей в 01159d80 по столбцам 0 и 2 матрицы машины P98_CarMat[car] и значку CARSHINE (байты 9..0xc),
   сдвиг по позиции машины / 256 по модулю половины значка; для записи — P28_Dst2[запись + shine·0x170]: 0 — Detail 0, 1..2 — Detail 1
   и 01159d58 = shk·50. Машина 0x41 при 00b87ea0 ≠ 0 (призрак) — матрица 011360a0, Detail всегда 2 и 01159d58 = 100.
   Отступления native: shine ≠ 0 или запись ≥ 0x170 — байт 0; NULL значка / нулевые размеры — обычный режим не меняется, UV = 0;
   car вне 0..0x41 — выход. a7 (в оригинале a7 >> 2 в неиспользуемой локали) не читается. */
static float g_view[16];   /* остаётся в P44_MatPtr после возврата (в оригинале — стек) */
/* P84_DrawCar — Game.exe 0042a9f1, cdecl.  Draws the body of car `car` (model mref, matrix mat, position pos):
   every record is culled against its own plane (no visibility cache), normals are always lit.  When the shine
   is enabled (P28_ShineFlag and shk != 0) or for the ghost car (0x41 while P62_HudOff1), environment-map UVs
   are computed per normal from columns 0 and 2 of the car's world matrix into the CARSHINE icon (scrolling with
   the car position / 256), and per record P28_Dst2 selects plain (Detail 0) or shiny (Detail 1, strength
   shk * 50; ghost: Detail 2, 100) drawing.  a7 is unused.  See the Russian notes above for native deviations. */
void P84_DrawCar(uint32_t mref, const float *mat, const float *pos, int32_t mode, int32_t car, int32_t shine, int32_t a7, float shk) {
  uint8_t *mdl = (uint8_t *)P79_PTR(mref);
  const uintptr_t *tab = pick_tab(mode);
  uint16_t nrec = *(uint16_t *)(mdl + 0x16), nnrm = *(uint16_t *)(mdl + 0x18);
  float p3[3] = { pos[0], pos[1], pos[2] }, nx, ny, nz, lx, ly, lz;
  const float *pl;
  int ghost, shinemode;
  (void)a7;
  if (car < 0 || car > 0x41) return;
  prologue(mdl, mref, pos);
  if (P84_TexFiltOn != 1) { tex_filter(0, 1, 1); P84_TexFiltOn = 1; }
  memset(g_view, 0, sizeof(g_view));
  Mat3Mul_0052859A(P44_ViewMat, mat, g_view);
  {
    float lv[4] = { P19_OutA, P19_OutB, P19_OutC, 0 };
    P44_MatPtr = (float *)mat;
    P44_Xform(lv);
    lx = lv[0]; ly = lv[1]; lz = lv[2];
  }
  P44_MatPtr = g_view;
  P44_XformT(p3);
  nx = -p3[0]; ny = -p3[1]; nz = -p3[2];
  {
    const float *n = (const float *)P79_PTR(*(uint32_t *)(mdl + 0x28));
    for (int i = 0; i < nnrm; i++, n += 4) P84_NormLight[i] = shade(dot3(n, lx, ly, lz));
  }
  if (P84_Mirror) { g_view[0] = -g_view[0]; g_view[3] = -g_view[3]; g_view[6] = -g_view[6]; }
  ghost = (P62_HudOff1 != 0 && car == 0x41);
  shinemode = ghost || !(P28_ShineFlag == 0 || shk == 0.0f);
  if (shinemode) {
    const uint8_t *ic = (const uint8_t *)re_ptr((uint32_t)P28_CarShine);
    const float *m = ghost || car == 0x41 ? P102_GhostMat : P98_CarMat[car];
    const p99_car_t *c = &P99_Cars[car];
    int32_t hw = ic ? ic[0xb] >> 1 : 0, hh = ic ? ic[0xc] >> 1 : 0;
    float fh = (float)hh, b9 = ic ? (float)ic[9] : 0, b10 = ic ? (float)ic[10] : 0;
    float q9c = ic ? (float)(ic[0xb] >> 2) : 0, q98 = ic ? (float)(ic[0xc] >> 2) : 0, ub, vb, ua, va;
    int32_t t;
    t = fist((ld)(float)c->pos[0] * (ld)0.00390625f); P11_00ba52d0 = t;
    ub = hw ? (float)(-t % hw) : 0.0f;
    t = fist((ld)(float)c->pos[2] * (ld)0.00390625f); P11_00ba52d0 = t;
    va = hh ? (float)(t % hh) : 0.0f;
    if (neg(ub)) ub = ub + fh;      /* в оригинале к обоим прибавляется половина высоты */
    if (neg(va)) va = va + fh;
    ua = ub + b9; vb = va + b10;
    {
      const float *n = (const float *)P79_PTR(*(uint32_t *)(mdl + 0x28));
      uint8_t *uv = P84_ShineUV;
      for (int i = 0; i < nnrm && i < 0x100; i++, n += 4, uv += 2) {
        float a = (float)(((ld)n[0] * (ld)m[0] + (ld)n[1] * (ld)m[3]) + (ld)n[2] * (ld)m[6]);
        float b = (float)(((ld)n[0] * (ld)m[2] + (ld)n[1] * (ld)m[5]) + (ld)n[2] * (ld)m[8]);
        t = fist(((ld)-a + (ld)1.0f) * (ld)q9c + (ld)ua); P11_00ba52d0 = t; uv[0] = (uint8_t)t;
        t = fist(((ld)-b + (ld)1.0f) * (ld)q98 + (ld)vb); P11_00ba52d0 = t; uv[1] = (uint8_t)t;
      }
    }
  } else P86_Detail = 0;
  G2_011F4064 = (uint8_t *)P79_PTR(*(uint32_t *)(mdl + 0x2c));
  pl = P84_Planes;
  for (int i = 0; i < nrec; i++, pl += 4) {
    uint8_t *rec = G2_011F4064;
    uint32_t type = rec[0];
    ld a = (ld)nx * (ld)pl[0];
    a += (ld)ny * (ld)pl[1];
    a += (ld)nz * (ld)pl[2];
    a -= (ld)pl[3];
    if (!neg((float)a)) { G2_011F4064 = rec + G2_TABLE_00550ACC[type]; continue; }
    if (P84_Lit[type]) P84_LightIn[i] = shade(dot3(pl, lx, ly, lz));
    if (shinemode) {
      uint32_t k = (uint32_t)i + (uint32_t)shine * 0x170u;
      uint8_t d = (shine == 0 && k < sizeof(P28_Dst2)) ? P28_Dst2[k] : 0;
      if (ghost) { P86_Detail = 2; if (d != 0 && d < 3) P84_ShineK = 100.0f; }
      else if (d == 0) P86_Detail = 0;
      else if (d < 3) { P86_Detail = 1; P84_ShineK = shk * 50.0f; }
    }
#ifndef RE_HOOK_BUILD
    { static int dbg = -1, nn; if (dbg < 0) dbg = getenv("RE_CARTEX") != NULL; if (dbg && nn < 400) { nn++;   /* v2.06: отладка — страница/слот записей кузова */
      call_h(tab, type); fprintf(stderr, "[cartex] car %d rec %d type %u slot %d page %u fl %u blk %u data %08x ta %08x\n", car, i, type, (int)P22_TexVarA, rec[2], P40_Slots[rec[2]].flags, P40_Slots[rec[2]].block, P40_Slots[rec[2]].data, P40_Slots[rec[2]].texaddr); continue; } }
#endif
    call_h(tab, type);
  }
  if (shinemode) P86_Detail = 0;
  P44_XformTag++;
}
