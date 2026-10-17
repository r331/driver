/* v1.80: ported135 — см. ported135.h.
   004b33d8 — P100_RoadHeight(rec) (результат не используется); вершины таблицы (rec[0xb] & 1 ? 010ffd20 : 01102d20) + idx(+0x26)·0x30
     (смещения 0/0x10/0x20) + позиция rec[0..2] − камера, P44_Xform текущей матрицей; z ≤ 224 или ≥ 01270c24/2 — +0x20 (short) = 1 и выход.
     Зеркало — x отражаются; цвет — байты +0x34..+0x36; значок DEBRIS 01123210 (P69_OvlOn), режим смешения 0, один P85_RasterB.
   004b23f8 — значок 010ffbe0 (P111_SparkIcon); (зеркало или z > 300) и z < 01270c44; точка мира +0x40 − камера через 011effa0;
     A = экранная (+0x10,+0x14), B = A + 5 по x, C = точка мира, D = C + 10 по x; |B.x − A.x| ≤ 320. Цвет по +0x50: 0 — (c+30, c, c),
     1 — c, 2 — смешение 2 и (c, c/2, 255) либо при +0x6c & 1 — (c/2, c, 255); прочие — 0 (в оригинале мусор стека). Треугольники ABC, ACD;
     при +0x50 & 2 — смешение обратно в 3. Зеркало не применяется (как в оригинале).
   004b10ce — при 010ffa30 ≠ 0, 300 < z < 01270c44 и значке SMOKE: квадрат ширины +0x50 (высота +0x50) над точкой (+0x10..+0x18);
     яркость +0x58 либо (00b20300 ≠ 0) затухание по дальности с вероятностным гашением (N14_Rand, +0x68 |= 0x1000000);
     цвет по флагам +0x68 (0x4000 — c; 0x82000 — c, смешение 2; 0x10000 — c·(0.6, 1.29, 1.69), смешение 2; иначе (c, c, c+8));
     треугольники ABC, CDA; при +0x68 & 0x92000 — смешение 3.
   004ba81f — 010ff8e0 = 00d118c0; угол rec[0] в пределах ±0x400 от курса камеры 00b1c26a; направление (−sin r0, sin r1, cos r0) через 011effa0;
     две синусоиды (rec[3] период, rec[4]/rec[8] фазы, rec[5]/rec[9] амплитуды) задают угол веера и длину; яркость rec[0xb] гаснет
     дальше 100000 от точки (−43000, 170000) (|dx|+|dz|/2 по большему); пять вершин, oow = 1e-6, без смены текстуры/смешения.
   004e6310 — CopyVec3_0052797A(00d04640), состояние 4, значок 00d04488 (NULL — текстура 0), смешение 3, матрица 011effa0 (зеркало —
     копия с отражёнными [0],[3],[6]); 40 записей: точки +0/+0x10 → +0x20/+0x30; обход от 00d04538−1 назад пока флаги +0x47 обоих ≠ 0,
     квадраты при всех z > 0054609c (ABC, ACD). Возврат как в оригинале (флаг записи либо (00d04538+1)/40).
   005063a4 — объект P58_Objs[i] (+0x14/+0x1c), разность с машиной игрока через __ftol (по ассемблеру: аргументы fx − X, fz − Z),
     основание (dz+2)>>2, (2−dx)>>2 не длиннее 15·1500; ближе 0x2a7b1 — треугольник, иначе укороченная четырёхугольная стрелка
     (P99_RadarXform 3/4 точки); без 3D-режима (00bdfa18 = 0 и 00bdfaa4 & 2 = 0) — три линии _grDrawLine, иначе треугольники (смешение 2).
   Отступления native: индекс таблицы 00ba53a0 вне диапазона — выход; NULL значка — выход (004ba81f в оригинале без проверки);
     четвёртая точка 005063a4 до P99_RadarXform — 0 (в оригинале мусор стека, результат перезаписывается). */
#include "ported135.h"
#include <string.h>
#include <math.h>
#include "crt.h"
#include "reptr.h"
#include "cartab.h"
#include "unported.h"
#include "globalsets.h"
#include "menustate.h"
#include "noop.h"
#include "smallfuncs.h"
#include "smallfuncs2.h"
#include "uihandlers3.h"
#include "uihandlers4.h"
#include "widgets.h"
#include "ported4.h"
#include "ported5.h"
#include "ported6.h"
#include "ported7.h"
#include "ported10.h"
#include "ported11.h"
#include "ported12.h"
#include "ported13.h"
#include "ported14.h"
#include "ported19.h"
#include "ported21.h"
#include "ported25.h"
#include "ported26.h"
#include "ported28.h"
#include "ported29.h"
#include "ported35.h"
#include "ported36.h"
#include "ported43.h"
#include "ported44.h"
#include "ported47.h"
#include "ported48.h"
#include "ported51.h"
#include "ported54.h"
#include "ported55.h"
#include "ported56.h"
#include "ported58.h"
#include "ported59.h"
#include "ported60.h"
#include "ported61.h"
#include "ported62.h"
#include "ported63.h"
#include "ported66.h"
#include "ported68.h"
#include "ported69.h"
#include "ported74.h"
#include "ported75.h"
#include "ported77.h"
#include "ported82.h"
#include "ported83.h"
#include "ported84.h"
#include "ported88.h"
#include "ported89.h"
#include "ported95.h"
#include "ported98.h"
#include "ported99.h"
#include "ported100.h"
#include "ported101.h"
#include "ported102.h"
#include "ported103.h"
#include "ported106.h"
#include "ported108.h"
#include "ported109.h"
#include "ported110.h"
#include "ported113.h"
#include "ported114.h"
#include "ported116.h"
#include "ported119.h"
#include "ported121.h"
#include "ported123.h"
#include "ported127.h"
#include "ported128.h"
#include "ported131.h"
#include "ported132.h"
#include "ported126.h"
#include "ported133.h"
#include "ported85.h"
#include "ported86.h"
#include "ported104.h"
#include "ported111.h"
#include "ported115.h"
#include "ported52.h"
#include "ported134.h"

static int32_t rd32(const void *p) { int32_t v; memcpy(&v, p, 4); return v; }
static float rdf(const void *p) { float v; memcpy(&v, p, 4); return v; }
static void wr32(void *p, int32_t v) { memcpy(p, &v, 4); }
static void wr16(void *p, uint16_t v) { memcpy(p, &v, 2); }
#define NZ ((int32_t)(RE_OOW_N))

static void raster(const p85_rv *a, const p85_rv *b, const p85_rv *c) { if (P85_RasterB) P85_RasterB(a, b, c); }
static void blend(uint8_t m, int32_t a, int32_t b, int32_t c, int32_t d) {
  if (P85_BlendCur != m) { if (P85_BlendFn) P85_BlendFn(a, b, c, d); P85_BlendCur = m; P69_BlendOn = m; }
}
static void tex_select(const uint8_t *ic) {
  if (ic[8] != (uint32_t)P86_CurTex) {
    P86_CurTex = ic[8];
    if (P86_TexSrc) P86_TexSrc(0, (uint32_t)rd32(&g_01145a60[ic[8] * 0x10 + 8]), 3, (uint32_t)rd32(&g_01145a60[ic[8] * 0x10 + 0xc]));
  }
}
/* 1/z по таблице 00ba53a0 (индекс — fistp z); 0 при выходе за таблицу */
static int zw(float z, float *w) {
  int32_t i = (int32_t)lrintf(z);
#ifndef RE_HOOK_BUILD
  if (i < 0 || i >= NZ) return 0;
#endif
  *w = RE_OOW(i);
  return 1;
}
static void scr(p85_rv *v, float x, float y, float w) {
  v->x = (x * P43_ScaleA * w + P43_OffX) - P43_Half;
  v->y = (y * P43_ScaleA * w + P43_OffY) - P43_Half;
  v->oow = w;
}
static void rgb(p85_rv *v, float r, float g, float b) { v->r = r; v->g = g; v->b = b; }
static void uv(p85_rv *v, uint8_t s, uint8_t t) { v->tmu[0] = (float)s * v->oow; v->tmu[1] = (float)t * v->oow; }

/* ---- 004b33d8 ---- */
void P135_DebrisTri(int32_t *rec) {
  uint8_t *r = (uint8_t *)rec;
  uint16_t idx; memcpy(&idx, r + 0x26, 2);
  P100_RoadHeight(rec);
#ifndef RE_HOOK_BUILD
  if (idx >= 256) return;
#endif
  const float *t = ((rec[0xb] & 1) == 0 ? P104_DebA : P104_DebB) + idx * 12;
  float p[3][3];
  for (int k = 0; k < 3; k++) {
    p[k][0] = ((float)rec[0] + t[k * 4]) - P44_CamX;
    p[k][1] = ((float)rec[1] + t[k * 4 + 1]) - P44_CamY;
    p[k][2] = ((float)rec[2] + t[k * 4 + 2]) - P44_CamZ;
    P44_Xform(p[k]);
    if (p[k][2] <= 224.0f || P11_01270c24 / 2.0f <= p[k][2]) { wr16(r + 0x20, 1); return; }
  }
  if (P84_Mirror != 0) { p[0][0] = -p[0][0]; p[1][0] = -p[1][0]; p[2][0] = -p[2][0]; }
  const uint8_t *ic = (const uint8_t *)re_ptr((uint32_t)P69_OvlOn);
#ifndef RE_HOOK_BUILD
  if (ic == NULL) return;
#endif
  p85_rv v[3];
  memset(v, 0, sizeof v);
  for (int k = 0; k < 3; k++) {
    float w;
    if (!zw(p[k][2], &w)) return;
    scr(&v[k], p[k][0], p[k][1], w);
    rgb(&v[k], (float)r[0x34], (float)r[0x35], (float)r[0x36]);
  }
  tex_select(ic);
  uv(&v[0], ic[9], ic[10]); uv(&v[1], ic[0xb], ic[10]); uv(&v[2], ic[9], ic[0xc]);
  blend(0, 4, 0, 4, 0);
  raster(&v[0], &v[1], &v[2]);
}

/* ---- 004b23f8 ---- */
void P135_SparkQuad(uint8_t *o) {
  if (P111_SparkIcon == 0) return;
  float z = rdf(o + 0x18);
  if (!((P84_Mirror != 0 || 300.0f < z) && z < (float)P62_I270C44)) return;
  float c3[3] = { rdf(o + 0x40) - P44_CamX, rdf(o + 0x44) - P44_CamY, rdf(o + 0x48) - P44_CamZ };
  P44_MatPtr = (float *)P44_ViewMatT;
  P44_Xform(c3);
  float x = rdf(o + 0x10), y = rdf(o + 0x14), wa, wc;
  if (!zw(z, &wa) || !zw(c3[2], &wc)) return;
  p85_rv v[4];
  memset(v, 0, sizeof v);
  scr(&v[0], x, y, wa); scr(&v[1], x + 5.0f, y, wa);
  scr(&v[2], c3[0], c3[1], wc); scr(&v[3], c3[0] + 10.0f, c3[1], wc);
  if (!(v[1].x - v[0].x <= 320.0f && v[0].x - v[1].x <= 320.0f)) return;
  int32_t mode = rd32(o + 0x50), c = rd32(o + 0x58);
  float r = 0, g = 0, b = 0;
  if (mode == 0) { r = (float)(c + 0x1e); g = b = (float)c; }
  else if (mode == 1) { r = g = b = (float)c; }
  else if (mode == 2) {
    blend(2, 0, 6, 4, 0);
    uint16_t f; memcpy(&f, o + 0x6c, 2);
    if ((f & 1) == 0) { r = (float)c; g = (float)(c / 2); } else { r = (float)(c / 2); g = (float)c; }
    b = 255.0f;
  }
  for (int k = 0; k < 4; k++) rgb(&v[k], r, g, b);
  const uint8_t *ic = (const uint8_t *)re_ptr(P111_SparkIcon);
#ifndef RE_HOOK_BUILD
  if (ic == NULL) return;
#endif
  tex_select(ic);
  uv(&v[3], ic[9], ic[10]); uv(&v[0], ic[0xb], ic[10]); uv(&v[1], ic[0xb], ic[0xc]); uv(&v[2], ic[9], ic[0xc]);
  raster(&v[0], &v[1], &v[2]);
  raster(&v[0], &v[2], &v[3]);
  if ((mode & 2) != 0) blend(3, 4, 4, 0, 0);
}

/* ---- 004b10ce ---- */
void P135_SmokeObj(uint8_t *o) {
  float z = rdf(o + 0x18);
  if (!(P52_Ones0 != 0 && 300.0f < z && z < (float)P62_I270C44 && P108_SmokeIcon != 0)) return;
  float x = rdf(o + 0x10), y = rdf(o + 0x14);
  int32_t sz = rd32(o + 0x50);
  float h = (float)(sz >> 1);
  float xl = x - h, xr = x + h, yt = y - (float)sz;
  if (P84_Mirror != 0) { xl = -xl; xr = -xr; }
  float w;
  if (!zw(z, &w)) return;
  p85_rv v[4];
  memset(v, 0, sizeof v);
  scr(&v[0], xl, yt, w); scr(&v[1], xr, yt, w); scr(&v[2], xr, y, w); scr(&v[3], xl, y, w);
  if (!(v[1].x - v[0].x <= 320.0f && v[0].x - v[1].x <= 320.0f)) return;
  uint32_t fl = (uint32_t)rd32(o + 0x68);
  float c;
  if (P26_FxD == 0) c = (float)rd32(o + 0x58);
  else {
    uint32_t u = N14_Rand();
    float f2 = w * 4000.0f, f1 = w * 8000.0f;
    if ((fl & 0x1000000) == 0 && (int32_t)lrintf(((f1 - f2) * 255.0f) / ((1.0f + f1) - 2.0f * f2)) < (int32_t)(u & 0xff)) {
      wr32(o + 0x58, 0);
      return;
    }
    fl |= 0x1000000;
    wr32(o + 0x68, (int32_t)fl);
    float k = (f2 <= 1.0f) ? (f1 - f2) / ((1.0f + f1) - 2.0f * f2) : 1.0f;
    c = (float)rd32(o + 0x58) * k;
  }
  const uint8_t *ic = (const uint8_t *)re_ptr(P108_SmokeIcon);
#ifndef RE_HOOK_BUILD
  if (ic == NULL) return;
#endif
  tex_select(ic);
  float r = c, g = c, b = c;
  if ((fl & 0x4000) == 0) {
    if ((fl & 0x82000) != 0) blend(2, 0, 6, 4, 0);
    else if ((fl & 0x10000) != 0) { r = c * 0.6f; g = c * 1.29f; b = c * 1.69f; blend(2, 0, 6, 4, 0); }
    else b = c + 8.0f;
  }
  for (int k = 0; k < 4; k++) rgb(&v[k], r, g, b);
  uv(&v[0], ic[9], ic[10]); uv(&v[1], ic[0xb], ic[10]); uv(&v[2], ic[0xb], ic[0xc]); uv(&v[3], ic[9], ic[0xc]);
  raster(&v[0], &v[1], &v[2]);
  raster(&v[2], &v[3], &v[0]);
  if ((fl & 0x92000) != 0) blend(3, 4, 4, 0, 0);
}

/* ---- 004ba81f ---- */
static int32_t iabs(int32_t v) { return v < 0 ? -v : v; }
void P135_SixBeam(const uint32_t *rec) {
  P102_SixFlag = P62_Frame;
  int32_t d = ((int32_t)(rec[0] - (uint32_t)P59_AngB + 0x800) & 0xfff) - 0x800;
  if (!(d < 0x401 && -0x401 < d)) return;
  float k = (P19_Scale * (float)P19_ScrW) / 640.0f;
  float p[3] = { -P43_Sin[rec[0] & 0xfff], P43_Sin[rec[1] & 0xfff], P43_Sin[(rec[0] & 0xfff) + 0x400] };
  P44_MatPtr = (float *)P44_ViewMatT;
  P44_Xform(p);
  int32_t per = (int32_t)rec[3];
#ifndef RE_HOOK_BUILD
  if (per == 0) return;
#endif
  float len = (float)(int32_t)rec[6] / 1000.0f;
  uint32_t ph = (uint32_t)((int32_t)((P102_SixFlag + (int32_t)rec[8]) * 0x1000) / per) & 0xfff;
  float wav = P43_Sin[ph];
  float len2 = (wav * (float)(int32_t)rec[9] + (float)(int32_t)rec[7]) / 1000.0f;
  uint32_t ph2 = (uint32_t)((int32_t)((P102_SixFlag + (int32_t)rec[4]) * 0x1000) / per) & 0xfff;
  uint32_t a = (rec[2] + (uint32_t)(((int32_t)P59_Sin[ph2] * (int32_t)rec[5]) / 4096)) & 0xfff;
  float sc = (P43_ScaleA * k) / p[2];
  float sa = P43_Sin[a], ca = P43_Sin[a + 0x400];
  float bx = p[0] - ca * len, by = p[1] - sa * len;
  float fx = sa * (float)(int32_t)rec[10] + p[0];
  float fy = p[1] - (wav * 0.01f * (float)(int32_t)rec[9] + 1.0f) * (float)(int32_t)rec[10];
  int32_t ix = iabs((int32_t)lrintf(P44_CamX) + 43000), iz = iabs((int32_t)lrintf(P44_CamZ) - 170000);
  int32_t dist = ix < iz ? iz + ix / 2 : ix + iz / 2;
  int32_t n = (int32_t)rec[0xb];
  if (dist > 100000) {
    n = (int32_t)rec[0xb] - (dist - 100000) / 2000;
    fy = (float)(dist - 100000) / 400000.0f + fy;
    if (n < 1) return;
  }
  float cx = fx - ca * len2, cy = fy - sa * len2;
  float X[5] = { p[0], bx, cx, 2.0f * fx - cx, 2.0f * p[0] - bx };
  float Y[5] = { p[1], by, cy, 2.0f * fy - cy, 2.0f * p[1] - by };
  if (P84_Mirror != 0) for (int i = 0; i < 5; i++) X[i] = -X[i];
  const uint8_t *ic = (const uint8_t *)re_ptr(P98_SixRec);
#ifndef RE_HOOK_BUILD
  if (ic == NULL) return;
#endif
  p85_rv v[5];
  memset(v, 0, sizeof v);
  float s9 = (float)ic[9] * 1e-06f, s10 = (float)ic[10] * 1e-06f, sb = (float)ic[0xb] * 1e-06f, sc2 = (float)ic[0xc] * 1e-06f;
  for (int i = 0; i < 5; i++) {
    v[i].x = (X[i] * sc + P43_OffX) - P43_Half;
    v[i].y = (Y[i] * sc + P43_OffY) - P43_Half;
    v[i].oow = 1e-06f;
    rgb(&v[i], (float)n, (float)n, (float)n);
  }
  v[0].tmu[0] = (s9 + s9) * 0.5f; v[0].tmu[1] = (s10 + sc2) * 0.5f;
  v[1].tmu[0] = s9; v[1].tmu[1] = s10;
  v[2].tmu[0] = sb; v[2].tmu[1] = s10;
  v[3].tmu[0] = sb; v[3].tmu[1] = sc2;
  v[4].tmu[0] = s9; v[4].tmu[1] = sc2;
  raster(&v[0], &v[1], &v[2]);
  raster(&v[0], &v[2], &v[3]);
  raster(&v[0], &v[3], &v[4]);
}

/* ---- 004e6310 ---- */
static float g_mirror_mat[16];
#define GREC(i) (P56_GhostBuf + (i) * 0x48)
int32_t P135_GhostTrail(void) {
#ifdef RE_HOOK_BUILD
  CopyVec3_0052797A((uint32_t *)&P98_M4640);
#else
  { uint32_t v3[3]; memcpy(&v3[0], &P98_M4640, 4); memcpy(&v3[1], &P98_M4644, 4); memcpy(&v3[2], &P98_M4648, 4);   /* v2.13: 3 отдельных native-объекта вне образа */
    CopyVec3_0052797A(v3); }
#endif
  if (P85_StateDirty != 4) { if (P85_StateFn) P85_StateFn(3, 1, 0, 1, 0); P85_StateDirty = 4; }
  const uint8_t *ic = P56_GhostPtr;
  if (ic == NULL) {
    if (P86_CurTex != 0) {
      P86_CurTex = 0;
      if (P86_TexSrc) P86_TexSrc(0, (uint32_t)rd32(&g_01145a60[8]), 3, (uint32_t)rd32(&g_01145a60[0xc]));
    }
  } else tex_select(ic);
  blend(3, 4, 4, 0, 0);
  if (P84_Mirror == 0) P44_MatPtr = (float *)P44_ViewMatT;
  else {
    size_t n = sizeof P44_ViewMatT < sizeof g_mirror_mat ? sizeof P44_ViewMatT : sizeof g_mirror_mat;
    memcpy(g_mirror_mat, (const void *)P44_ViewMatT, n);
    g_mirror_mat[0] = -g_mirror_mat[0]; g_mirror_mat[3] = -g_mirror_mat[3]; g_mirror_mat[6] = -g_mirror_mat[6];
    P44_MatPtr = g_mirror_mat;
  }
  for (int32_t i = 0; i < 0x28; i++) {
    uint8_t *r = GREC(i);
    for (int h = 0; h < 2; h++) {
      float q[3] = { rdf(r + h * 0x10) - P44_CamX, rdf(r + h * 0x10 + 4) - P44_CamY, rdf(r + h * 0x10 + 8) - P44_CamZ };
      P44_Xform(q);
      memcpy(r + 0x20 + h * 0x10, q, 12);
      memcpy(r + 0x2c + h * 0x10, r + 0xc + h * 0x10, 4);
    }
  }
  int32_t i = P56_G4538 - 1;
  if (i < 0) i = P56_G4538 + 0x27;
  uint32_t ret = 0;
  for (;;) {
#ifndef RE_HOOK_BUILD
    if (i < 0 || i >= 0x28) return 0;
#endif
    int32_t j = i - 1;
    if (j < 0) j = i + 0x27;
    uint8_t *ri = GREC(i), *rj = GREC(j);
    if (ri[0x47] == 0 || rj[0x47] == 0) return ri[0x47];
    if (P95_Near < rdf(ri + 0x28) && P95_Near < rdf(rj + 0x28) && P95_Near < rdf(rj + 0x38) && P95_Near < rdf(ri + 0x38)) {
      p85_rv v[4];
      memset(v, 0, sizeof v);
      const uint8_t *src[4] = { ri + 0x20, rj + 0x20, rj + 0x30, ri + 0x30 };
      int ok = 1;
      for (int k = 0; k < 4; k++) {
        float w;
        if (!zw(rdf(src[k] + 8), &w)) { ok = 0; break; }
        scr(&v[k], rdf(src[k]), rdf(src[k] + 4), w);
        const uint8_t *cr = (k == 0 || k == 3) ? ri : rj;
        rgb(&v[k], (float)cr[0x44], (float)cr[0x45], (float)cr[0x46]);
      }
      if (ok) {
        if (ic != NULL) { uv(&v[0], ic[9], ic[10]); uv(&v[1], ic[0xb], ic[10]); uv(&v[2], ic[0xb], ic[0xc]); uv(&v[3], ic[9], ic[0xc]); }
        raster(&v[0], &v[1], &v[2]);
        raster(&v[0], &v[2], &v[3]);
      }
    }
    i = (i - 1 < 0) ? i + 0x27 : i - 1;
    ret = (uint32_t)((P56_G4538 + 1) / 0x28);
    if (i == (P56_G4538 + 1) % 0x28) break;
    if (i == P56_G4538) return (int32_t)ret;
  }
  return (int32_t)ret;
}
#undef GREC

/* ---- 005063a4 ---- */
static int32_t approx(int32_t a, int32_t b) { a = iabs(a); b = iabs(b); return a < b ? b + a / 2 : a + b / 2; }
void P135_RadarLine(int32_t i) {
#ifndef RE_HOOK_BUILD
  if (i < 0 || i >= 10) return;
#endif
  const uint8_t *o = P58_Objs[i];
  float fx = (float)rd32(o + 0x14), fz = (float)rd32(o + 0x1c);
  int32_t p[16];
  memset(p, 0, sizeof p);
  p[8] = (int32_t)(fx - (float)P59_PosX);    /* __ftol */
  p[10] = (int32_t)(fz - (float)P59_PosZ);
  p[0] = (p[10] + 2) >> 2;
  p[2] = (2 - p[8]) >> 2;
  int32_t k = approx(p[0], p[2]) / 0x5dc;
  if (0xf < k) { p[0] = (p[0] * 0xf) / k; p[2] = (p[2] * 0xf) / k; }
  p[4] = -p[0]; p[6] = -p[2];
  int32_t dist = approx(p[8], p[10]);
  if (P85_StateDirty != 0) { if (P85_StateFn) P85_StateFn(1, 0, 0, 2, 0); P85_StateDirty = 0; }
  p85_rv v[4];
  memset(v, 0, sizeof v);
  float oow = P55_BDFA18 == 0 ? 0.015625f : 1.0f;
  for (int n = 0; n < 4; n++) { v[n].oow = oow; float c = n < 2 ? 32.0f : 128.0f; rgb(&v[n], c, c, c); }
  int lines = (P55_BDFA18 == 0 && (P131_BDFAA4 & 2) == 0);
  int32_t q[16];
  if (dist < 0x2a7b1) {
    memcpy(q, p, sizeof q);
    P99_RadarXform(q, p, 3);
  } else {
    int32_t s = dist / 0x5dc;
    memcpy(q, p, sizeof q);
    P99_RadarXform(q, p, 4);
    p[12] = p[4] + ((p[8] - p[4]) * 0x74) / s;
    p[14] = p[6] + ((p[10] - p[6]) * 0x74) / s;
    p[8] = p[0] + ((p[8] - p[0]) * 0x74) / s;
    p[10] = p[2] + ((p[10] - p[2]) * 0x74) / s;
    v[3].x = (float)p[12]; v[3].y = (float)p[14];
  }
  v[0].x = (float)p[0]; v[0].y = (float)p[2];
  v[1].x = (float)p[4]; v[1].y = (float)p[6];
  v[2].x = (float)p[8]; v[2].y = (float)p[10];
  if (lines) {
    blend(0, 4, 0, 4, 0);
    if (P95_DrawLine) {
      P95_DrawLine((const float *)&v[0], (const float *)&v[2]);
      P95_DrawLine((const float *)&v[1], (const float *)(dist < 0x2a7b1 ? &v[2] : &v[3]));
      P95_DrawLine((const float *)&v[0], (const float *)&v[1]);
    }
  } else {
    blend(2, 0, 6, 4, 0);
    raster(&v[0], &v[1], &v[2]);
    if (dist >= 0x2a7b1) raster(&v[3], &v[1], &v[2]);
  }
}
