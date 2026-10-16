/* v1.59 (см. ported114.h). */
#include "ported114.h"
#include "reptr.h"
#include "noop.h"
#include "ported6.h"
#include "ported7.h"
#include "ported11.h"
#include "ported12.h"
#include "ported14.h"
#include "ported15.h"
#include "ported16.h"
#include "ported19.h"
#include "ported32.h"
#include "ported33.h"
#include "ported43.h"
#include "ported44.h"
#include "ported46.h"
#include "ported52.h"
#include "ported55.h"
#include "ported56.h"
#include "ported58.h"
#include "ported59.h"
#include "ported60.h"
#include "ported34.h"
#include "ported4.h"
#include "ported8.h"
#include "uihandlers.h"
#include "ported70.h"
#include "ported47.h"
#include "cartab.h"
#include "ported62.h"
#include "ported86.h"
#include "ported97.h"
#include "ported111.h"
#include "ported67.h"
#include "ported69.h"
#include "ported76.h"
#include "ported77.h"
#include "ported85.h"
#include "ported95.h"
#include "ported98.h"
#include "ported99.h"
#include "ported100.h"
#include "ported107.h"
#include "ported108.h"
#include "ported110.h"
#include "ported112.h"
#include "ported113.h"
#include "strtab.h"
#include "uihandlers3.h"
#include "uihandlers4.h"
#include <string.h>
#include <math.h>

GAME_VAR_DEF(p114_rgb_t, P114_Black, 0x00b1ffc0)

static int32_t rd32(const void *p) { int32_t v; memcpy(&v, p, 4); return v; }
static int16_t rd16s(const void *p) { int16_t v; memcpy(&v, p, 2); return v; }
static float rdf(const void *p) { float v; memcpy(&v, p, 4); return v; }
static void wrf(void *p, float v) { memcpy(p, &v, 4); }

/* ---- 0041d53c: загрузка мип-уровня (режим D3D 1): 8-битная текстура при включённых списках — привязать узел палитры к слоту ---- */
void P114_TexDownloadMip(int32_t tmu, int32_t addr, int32_t evenOdd, int32_t info, int32_t handle) {
  P33_FlushBatches();
  const uint8_t *in = (const uint8_t *)re_ptr((uint32_t)info);
#ifndef RE_HOOK_BUILD
  if (in == NULL) return;
#endif
  if (G6_00A421F0 == 0 || rd32(in + 0xc) != 5) { P112_TexDownload(tmu, (uint32_t)addr, evenOdd, in); return; }
  P46_TexNode *node = NULL;
  if (P46_FindTexNode(handle, &node) == 0) { NoopFn0042243f(); return; }   /* "ERROR: 8Bit texture not marked as…" */
  uint32_t slot = (uint32_t)addr >> 16;
  if (slot < 0x20) {
    P32_Slots[slot].has_list = 1;
    P32_Slots[slot].cur_id = -1;
    P32_Slots[slot].list = (P32_Node *)(void *)node;
    P32_Slots[slot].cur_handle = NULL;
  }
}

/* ---- 004e5fd7: отметка пункта idx (0..8) на «бумаге» ELPAPEL (.data 00562b80: x0, x1, y0, y1 по 16 байт) ---- */
void P114_PaperMark(int32_t idx) {
  static const float k_mark[9][4] = {   /* .data 00562b80 */
    { 21, 79, 20, 28 }, { 17, 91, 31, 39 }, { 18, 67, 41, 49 }, { 21, 59, 52, 59 }, { 23, 58, 62, 69 },
    { 20, 109, 72, 80 }, { 25, 71, 83, 89 }, { 25, 101, 93, 101 }, { 31, 62, 104, 111 } };
#ifndef RE_HOOK_BUILD
  if (idx < 0 || idx >= 9) return;
#endif
  const uint8_t *paper = (const uint8_t *)re_ptr((uint32_t)P55_Paper0);
  if (paper == NULL) return;
  float x = 640.0f - (float)paper[0xb];                    /* .rdata 00546060 */
  const float *e = k_mark[idx];
  if (P55_Paper1 == 0) {
    P107_Line(x + e[0], e[2], x + e[1], e[3], 0);
    P107_Line(x + e[1], e[2], x + e[0], e[3], 0);
  } else {
    const uint8_t *line = (const uint8_t *)re_ptr((uint32_t)P55_Paper1);
#ifndef RE_HOOK_BUILD
    if (line == NULL) return;
#endif
    P112_IconBar(line, x + e[0], e[2], P15_Vals9[idx], line[0xb]);
  }
}

/* ---- 004a995c: кадр титров — строки P98_Credits по y − прокрутка G00B1FFBC, рамки/градиенты 640×480 ---- */
#ifdef RE_HOOK_BUILD
#  define WHITE_ADDR 0x00552e18u
#else
static const uint8_t k_white[4] = { 0xff, 0xff, 0xff, 0 };   /* .data 00552e18 */
#  define WHITE_ADDR re_addr(k_white)
#endif
void P114_CreditsDraw(void) {
  uint32_t black = re_addr(P114_Black), white = WHITE_ADDR;
  P107_Rect(0x140, 0x60, 0x140, 0x168, black);
  for (int32_t i = 0; P98_Credits[i].kind != 8; i++) {
    p98_credit_t *c = &P98_Credits[i];
    int32_t y = c->y - G00B1FFBC;
    if (y > 0x1c7) break;
    switch (c->kind) {
    case 0: P67_Logo(c->sub, y); break;
    case 1: case 3: case 5: if (c->txt != 0) P52_DrawLabel((int32_t)c->txt, y, c->sub); break;
    case 2: case 4: case 6:
      if ((int32_t)c->txt != -1) {
#ifndef RE_HOOK_BUILD
        if (c->txt >= 0x15e) break;
#endif
        P52_DrawLabel((int32_t)P97_StrAddr[c->txt], y, c->sub);
      }
      break;
    case 7: P112_FaceIcon((uint8_t *)c, y); break;
    default: break;
    }
  }
  P107_Rect(0x140, 0, 0x140, 0x60, black);
  P58_DrawLogo();
  P107_RectGrad(0x140, 0x60, 0x140, 0x20, white, black);
  P107_RectGrad(0x140, 0x1a8, 0x140, 0x20, black, white);
  P107_Rect(0x140, 0x1c8, 0x140, 0x18, black);
}

/* ---- 005128b7: частицы A_00C56780 с флагом 0x10 — по текстурам .data 005759a8, высота дороги − 224, P113_PartDraw ---- */
void P114_PartModels(void) {
  static const int32_t k_tex[5] = { 0x0e, 0x1a, 0x1c, 0x1d, 0x1e };   /* .data 005759a8 */
  if (P60_PartLimit == 0) return;
  P98_IconN = 0;
  for (int32_t t = 0; t < 5; t++) {
    P12_Fn00426580(k_tex[t]);
    uint8_t *p = A_00C56780;
    for (int32_t n = 0x40; n != 0; n--, p += 0xb4) {
      if ((rd32(p + 0xc) & 0x10) == 0 || rd32(p + 8) != t) continue;
      int32_t h = P100_RoadHeightF((const float *)(p + 0x84));       /* ветки типа 4 и прочих в оригинале одинаковы */
      wrf(p + 0x88, (float)-h - 224.0f);                            /* .rdata 0054619c */
      P113_PartDraw(p);
    }
  }
}

/* ---- 004f5afe: таймер записи скрипта {кадры, флаги, счётчик, сотые, сек, мин} ---- */
void P114_Timer(int32_t *t) {
#ifndef RE_HOOK_BUILD
  if (t == NULL) return;
#endif
  if ((t[1] & 4) == 0) return;
  if ((t[1] & 0x80) == 0) {
    if (t[0] == 0) {
      if (G6_00B87EB0 == 0) {
        P14_00c810c4 = 0xff0; P16_IdleMode = 0xff0; P56_Blk84[1] = 0xff0;
        P14_00c810e8 = 1; P16_IdleArg1 = 1; P56_Blk84[10] = 1;
        P14_00c81100 = 0x5a; P16_IdleArg2 = 0x5a; P56_Blk84[16] = 0x5a;
      }
      t[1] &= ~8;
    } else if (t[1] & 8) { t[0]--; t[2]++; }
  } else if (t[1] & 8) { t[0]++; t[2]++; }
  if ((P56_Blk84[6] & 8) != 0 && t[0] == (int32_t)P56_Blk84[12]) P112_ScriptRunId((uint16_t)P56_Blk84[13]);   /* 00c810d8/f0/f4 */
  t[4] = t[0] / 0x32;
  t[5] = t[4] / 0x3c;
  t[3] = t[0] % 0x32;
  t[4] = t[4] % 0x3c;
  t[3] = t[3] << 1;
  if (t[5] > 0x3b) { t[5] = 0x3b; t[4] = 0x3b; }
}

/* ---- 004e8bd0: пять колец дыма вокруг P76_ColObj и вспышка цветом P76_ColA/B/C на всё окно 3D (два треугольника, смешивание 3) ---- */
void P114_ColorFlash(void) {
  if (P76_Angle >= 0xc0) return;
  float s = (float)P76_Angle * 8.0f + 500.0f;                       /* .rdata 0054616c, 005469c0 */
  float pos[3] = { rdf(P76_ColObj + 0) - P44_CamX, rdf(P76_ColObj + 4) - P44_CamY, rdf(P76_ColObj + 8) - P44_CamZ };
  int32_t old = DrvSetMode0042655A(0);
  P110_SmokeRing(s - 20.0f, pos, 0, P76_ColA, P76_ColB, P76_ColC, 0, 0);
  P110_SmokeRing(s, pos, 0x1000 - P99_Mrk2660, P76_ColA, P76_ColB, P76_ColC, 0, 1);
  P110_SmokeRing(s, pos, P99_Mrk2660, P76_ColA, P76_ColB, P76_ColC, 0, 1);
  P110_SmokeRing((s - 200.0f) * 4.0f, pos, P99_Mrk2660, P76_ColA, P76_ColA, P76_ColA, 1, 1);
  P110_SmokeRing((s - 200.0f) * 12.0f, pos, P99_Mrk2660, P76_ColA, P76_ColA, P76_ColA, 1, 1);
  if (P85_StateDirty != 0) { if (P85_StateFn) P85_StateFn(1, 0, 0, 2, 0); P85_StateDirty = 0; G6_01270C34 = 0; }
  if (P85_BlendCur != 3) { if (P85_BlendFn) P85_BlendFn(4, 4, 0, 0); P85_BlendCur = 3; P69_BlendOn = 3; }
  p85_rv a, b, c;
  memset(&a, 0, sizeof a); memset(&b, 0, sizeof b); memset(&c, 0, sizeof c);   /* z, ooz, a в оригинале не заданы */
  float r = (float)P76_ColA, g = (float)P76_ColB, bl = (float)P76_ColC, oow = (P55_BDFA18 == 0) ? 0.015625f : 1.0f;
  a.x = P110_ClipX1; a.y = P110_ClipY0; b.x = P110_ClipX0; b.y = P110_ClipY1; c.x = P110_ClipX0; c.y = P110_ClipY0;
  a.r = b.r = c.r = r; a.g = b.g = c.g = g; a.b = b.b = c.b = bl; a.oow = b.oow = c.oow = oow;
  if (P85_RasterB) P85_RasterB(&a, &b, &c);
  c.x = P110_ClipX1; c.y = P110_ClipY1;
  if (P85_RasterB) P85_RasterB(&a, &b, &c);
  DrvSetMode0042655A(old);
}

/* ---- 0050cfeb: отладочный путь (список узлов по 0x20: +0 следующий, +4 предыдущий — адреса; +8/+0xc x/z, +0x14/+0x16 экран,
        +0x18 тип, +0x1e направление) — квадраты и линии на экране, только в режиме 6 или при отладке 00c7d850 ---- */
void P114_PathDraw(uint8_t *p, int32_t mode) {
  if (G00BDFA54 != 0 || (P59_Mode1137324 != 6 && P77_C7D850 == 0)) return;
  float py = -1.0f;
#ifndef RE_HOOK_BUILD
  if (p == NULL) return;
#endif
  float px = (float)rd16s(p + 0x14);
  for (; p != NULL; p = (uint8_t *)re_rd_ptr(p)) {
    float v[3] = { (float)rd32(p + 8) - P44_CamX, 8.0f - P44_CamY, (float)rd32(p + 0xc) - P44_CamZ };
    P44_MatPtr = P44_ViewMat;
    P44_XformT(v);
    int32_t zi = (int32_t)lrintf(v[2]);
    if (zi <= 0x32 || zi >= 45000) continue;
#ifndef RE_HOOK_BUILD
    if (zi >= (int32_t)(sizeof P12_00ba53a0 / sizeof P12_00ba53a0[0])) continue;
#endif
    float k = P43_ScaleA * P12_00ba53a0[zi];
    float sx = (v[0] * k + P43_OffX) - P43_Half, sy = (v[1] * k + P43_OffY) - P43_Half, sz = 500.0f * k;
    float qx = sx - sz / 2.0f, qy = sy - sz / 2.0f;                 /* .rdata 00546050 */
    if (rd16s(p + 0x18) == 9) {
      const uint8_t *prev = (const uint8_t *)re_rd_ptr(p + 4);
      if (prev != NULL) {
        uint8_t d = prev[0x1e];
        uint32_t col;
        if (d == 2 || d == 6) col = (mode == 1) ? 0x7f8000u : 0xff0000u;
        else if (d == 0 || d == 4) col = (mode == 1) ? 0x7f80u : 0xff00u;
        else col = (mode == 1) ? 0x7fu : 0xffu;
        P108_FillRect(qx, qy, sz, sz, col);
      }
    } else P108_FillRect(qx, qy, sz, sz, (mode == 1) ? 0x007fc422u : 0x00ff8844u);
    if (px != 0.0f && py != 0.0f) {
      int32_t y1 = (int32_t)lrintf(sy), x1 = (int32_t)lrintf(sx), y0 = (int32_t)lrintf(py), x0 = (int32_t)lrintf(px);
      P11_00ba52d0 = x0;
      P95_DrawLineRGB(x0, y0, x1, y1, (mode == 1) ? 0x7fffffu : 0xffffffu);
    }
    px = sx; py = sy;
  }
}

#ifdef RE_HOOK_BUILD
#  define P114_STD __attribute__((stdcall))
#else
#  define P114_STD
#endif
static void *glide_proc(const char *name) {
  for (int i = 0; i < P33_GlideCount(); i++)
    if (strcmp(P33_GlideName(i), name) == 0) return P33_GlideProc(i);
  return NULL;
}
static void alpha_combine(int32_t a, int32_t b, int32_t c, int32_t d, int32_t e) {
  void (P114_STD *f)(int32_t, int32_t, int32_t, int32_t, int32_t) = (void (P114_STD *)(int32_t, int32_t, int32_t, int32_t, int32_t))glide_proc("_grAlphaCombine@20");
  if (f) f(a, b, c, d, e);
}
static void alpha_test(int32_t a) {
  void (P114_STD *f)(int32_t) = (void (P114_STD *)(int32_t))glide_proc("_grAlphaTestFunction@4");
  if (f) f(a);
}
static void state4(void) {
  if (P85_StateDirty != 4) { if (P85_StateFn) P85_StateFn(3, 1, 0, 1, 0); P85_StateDirty = 4; G6_01270C34 = 4; }
}
static void blend(uint8_t m) {
  static const int32_t k[4][4] = { { 4, 0, 4, 0 }, { 0, 5, 4, 0 }, { 0, 6, 4, 0 }, { 4, 4, 0, 0 } };
  if (m > 3) return;
  if (P85_BlendCur != m) { if (P85_BlendFn) P85_BlendFn(k[m][0], k[m][1], k[m][2], k[m][3]); P85_BlendCur = m; P69_BlendOn = m; }
}

/* ---- 004b3e55: обломки P97_Debris (100 × 0x3c, +0x22 флаги): проход значками с альфа-тестом, затем тени (смешивание 2) ---- */
void P114_DebrisAll(void) {
  state4();
  blend(0);
  if (P62_I252B78 != 1) { alpha_combine(3, 8, 0, 1, 1); alpha_test(4); P62_I252B78 = 1; }
  for (int32_t i = 0; i < 100; i++) {
    const uint8_t *o = P97_Debris + i * 0x3c;
    if ((o[0x22] & 2) != 0) P111_DebrisIcon((const float *)o, 0);
  }
  if (P62_I252B78 != 0) { alpha_combine(3, 8, 0, 2, 1); alpha_test(7); P62_I252B78 = 0; }
  if (G6_00D11880 == 0) return;
  blend(2);
  for (int32_t i = 0; i < 100; i++) {
    const uint8_t *o = P97_Debris + i * 0x3c;
    if ((o[0x22] & 2) != 0) P111_DebrisIcon((const float *)o, 1);
  }
}

/* ---- 004d8511: значок ic (+8 страница, +9/+10 u/v, +0xb/+0xc ширина/высота) в (x, y) с масштабом sx/sy, цвет r,g,b, смешивание 0..3 ---- */
void P114_DrawSpr(float x, float y, float sx, float sy, void *icv, int32_t r, int32_t g, int32_t b, int32_t bl) {
  const uint8_t *ic = (const uint8_t *)icv;
  state4();
  blend((uint8_t)bl);
#ifndef RE_HOOK_BUILD
  if (ic == NULL) return;
#endif
  if ((int32_t)ic[8] != P86_CurTex) {
    P86_CurTex = ic[8];
    if (P86_TexSrc) P86_TexSrc(0, (uint32_t)rd32(&P12_01145a60[(uint32_t)ic[8] * 0x10 + 8]), 3, (uint32_t)rd32(&P12_01145a60[(uint32_t)ic[8] * 0x10 + 0xc]));
  }
  float x1 = x + sx * (float)ic[0xb], y1 = y + sy * (float)ic[0xc];
  float u0 = (float)ic[9] + 0.5f, v0 = (float)ic[10] + 0.5f;                        /* .rdata 00546068 */
  float u1 = (float)((uint32_t)ic[9] + ic[0xb]) - 0.5f, v1 = (float)((uint32_t)ic[10] + ic[0xc]) - 0.5f;
  float oow = (P55_BDFA18 == 0) ? 0.015625f : 1.0f;
  p85_rv v[4];
  memset(v, 0, sizeof v);                                              /* z, ooz, a в оригинале не заданы */
  const float px[4] = { x, x1, x1, x }, py[4] = { y, y, y1, y1 }, pu[4] = { u0, u1, u1, u0 }, pv[4] = { v0, v0, v1, v1 };
  for (int i = 0; i < 4; i++) {
    v[i].x = px[i]; v[i].y = py[i];
    v[i].r = (float)(uint8_t)r; v[i].g = (float)(uint8_t)g; v[i].b = (float)(uint8_t)b;
    v[i].oow = oow; v[i].tmu[0] = pu[i] * oow; v[i].tmu[1] = pv[i] * oow;
  }
  if (P85_RasterB) { P85_RasterB(&v[0], &v[1], &v[2]); P85_RasterB(&v[2], &v[3], &v[0]); }
}

/* ---- 0049f474: кадр сценария камеры — при задержке 00c810d0 очистка и текст 00c81168; затемнение P99_CamFade
        (прямоугольник ScrW × CamMax двумя треугольниками, смешивание 2), grBufferSwap(0), высота окна CamSpd >> 12 ---- */
void P114_CamFadeFrame(void) {
  int32_t delay = (P99_CamDelay != 0);
  if (delay) {
    void (P114_STD *clr)(int32_t, int32_t, int32_t) = (void (P114_STD *)(int32_t, int32_t, int32_t))glide_proc("_grBufferClear@12");
    if (clr) clr(0, 0, 0xffff);
    DrawTextLine004FBBC5((int32_t)re_addr((uint8_t *)P56_Blk84 + 0xa8));   /* 00c81168 */
    P99_CamFade = P99_CamB0;
  }
  if (P99_CamFade != 0) {
    if (P85_StateDirty != 0) { if (P85_StateFn) P85_StateFn(1, 0, 0, 2, 0); P85_StateDirty = 0; G6_01270C34 = 0; }
    blend(2);
    float f = (float)P99_CamFade, w = (float)P19_ScrW, h = (float)P99_CamMax, oow = (P55_BDFA18 == 0) ? 0.015625f : 1.0f;
    p85_rv a, b, c;
    memset(&a, 0, sizeof a); memset(&b, 0, sizeof b); memset(&c, 0, sizeof c);
    a.x = 0; a.y = 0; b.x = w; b.y = h; c.x = 0; c.y = h;
    a.r = a.g = a.b = b.r = b.g = b.b = c.r = c.g = c.b = f;
    a.oow = b.oow = c.oow = oow;
    if (FnPtr01270E80) FnPtr01270E80(0);
    if (P85_RasterB) P85_RasterB(&a, &b, &c);
    c.x = w; c.y = 0;
    if (P85_RasterB) P85_RasterB(&a, &b, &c);
    if (FnPtr01270E80) FnPtr01270E80(2);
  }
  void (P114_STD *swp)(int32_t) = (void (P114_STD *)(int32_t))glide_proc("_grBufferSwap@4");
  if (swp) swp(0);
  if (delay) { P99_CamFade = 0xff; return; }
  int32_t h = P99_CamSpd >> 0xc;
  if (P19_ScrH != h) { P19_ScrH = h; G6_0125F3F0 = h; P110_ViewSetup(0, (P99_CamMax - h) / 2, 0); }
  if (P11_01270c38 != 0) { P110_ViewSetup(0, (P99_CamMax - P19_ScrH) / 2, 1); P11_01270c38--; }
  P47_SwapCnt++;
}

/* ---- 005073f1: карта — игрок (белый) и цели P58_Objs (10 × 0x34: +0x10 флаги, +0x14/+0x1c x/z) красным, масштаб |00b3297c| ---- */
void P114_RadarMarks(void) {
  float px = (float)P59_PosX, pz = (float)P59_PosZ;
  P12_Fn00426580(0);
  P97_MapIcon(px, pz, 0xff, 0xff, 0xff, fabsf(P12_00b3297c));
  for (int32_t i = 0; i < 10; i++) {
    const uint8_t *o = (const uint8_t *)P58_Objs + i * 0x34;
    uint32_t fl = (uint32_t)rd32(o + 0x10);
    if ((fl & 1) != 0 && (fl & 0x10) == 0) P97_MapIcon((float)rd32(o + 0x14), (float)rd32(o + 0x1c), 0xff, 0, 0, fabsf(P12_00b3297c));
  }
  P70_RadarNearestB();
}

GAME_VAR_DEF(int32_t, P114_BlinkCnt, 0x005f7e68)
GAME_VAR_DEF(int32_t, P114_BlinkOn, 0x005f7e6c)
GAME_VAR_DEF(int32_t, P114_RepCnt, 0x005f7e70)
#ifndef RE_HOOK_BUILD
int32_t P114_RepDelay = 10;
#endif

/* ---- 0040c8f1: шаг меню. Пункт таблицы (0x10): +0 рисовать (мигание), +4 рисовать обычным, +8 выбрать; +0xc/+0xd влево/вправо,
        +0xe/+0xf вверх/вниз (номер пункта). Обработчики — адреса Game.exe через re_fn. Esc (1) — -1 ---- */
typedef void (*p114_fn1_t)(int32_t);
typedef int32_t (*p114_fn0_t)(void);
static void call1(const uint8_t *t, uint32_t i, uint32_t off, int32_t a) {
  p114_fn1_t f = (p114_fn1_t)re_fn((uint32_t)rd32(t + i * 0x10 + off));
  if (f) f(a);
}
int32_t P114_MenuStep(uint32_t tbl, int32_t *cur) {
  const uint8_t *t = (const uint8_t *)re_ptr(tbl);
#ifndef RE_HOOK_BUILD
  if (t == NULL || cur == NULL) return -1;
#endif
  int32_t ret = 0;
  uint32_t was = (uint32_t)*cur;
  if (IsFlagSetNotMasked_004E383A(1) != 0) { call1(t, was, 4, 0); return -1; }
  if (--P114_BlinkCnt < 1) { P114_BlinkCnt = 0x14; P114_BlinkOn ^= 1; }
  call1(t, (uint32_t)*cur, P114_BlinkOn == 0 ? 4 : 0, 1);
  if (D_005f7e4c == 0) {
    if (IsFlagSetNotMasked_004E383A(0xcb) != 0) { *cur = t[0xc + (uint32_t)*cur * 0x10]; Ui0040C867(); }
    else if (IsFlagSetNotMasked_004E383A(0xcd) != 0) { *cur = t[0xd + (uint32_t)*cur * 0x10]; Ui0040C867(); }
  } else {
    uint8_t kl = P34_Keys[0xcb], kr = P34_Keys[0xcd];
    if (((kl | kr) & 0x80) == 0) { P114_RepCnt = 0; P114_RepDelay = 0x28; }
    if (P114_RepCnt == 0) {
      if (kl & 0x80) { call1(t, t[0xc + (uint32_t)*cur * 0x10], 0, 0); P114_RepCnt = P114_RepDelay; P114_RepDelay = 1; Ui0040C867(); }
      else if (kr & 0x80) { call1(t, t[0xd + (uint32_t)*cur * 0x10], 0, 0); P114_RepCnt = P114_RepDelay; P114_RepDelay = 1; Ui0040C867(); }
    } else P114_RepCnt--;
  }
  if (IsFlagSetNotMasked_004E383A(200) != 0) { *cur = t[0xe + (uint32_t)*cur * 0x10]; Ui0040C867(); }
  else if (IsFlagSetNotMasked_004E383A(0xd0) != 0) { *cur = t[0xf + (uint32_t)*cur * 0x10]; Ui0040C867(); }
  else if (IsFlagSetNotMasked_004E383A(0x1c) != 0) {
    Ui0040C867();
    p114_fn0_t f = (p114_fn0_t)re_fn((uint32_t)rd32(t + (uint32_t)*cur * 0x10 + 8));
    if (f) ret = f();
  }
  if (was != (uint32_t)*cur) { call1(t, was, 4, 0); call1(t, (uint32_t)*cur, 0, 0); }
  return ret;
}
