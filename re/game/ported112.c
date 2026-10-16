/* v1.57 (см. ported112.h). */
#include <stdlib.h>
#include <stdio.h>
#include "ported112.h"
#include "reptr.h"
#include "cartab.h"
#include "director.h"
#include "menustate.h"
#include "smallfuncs.h"
#include "smallfuncs2.h"
#include "uihandlers3.h"
#include "ported6.h"
#include "ported8.h"
#include "ported10.h"
#include "ported11.h"
#include "ported12.h"
#include "ported14.h"
#include "ported15.h"
#include "ported19.h"
#include "ported21.h"
#include "ported22.h"
#include "ported29.h"
#include "ported32.h"
#include "ported33.h"
#include "ported43.h"
#include "ported44.h"
#include "ported47.h"
#include "ported58.h"
#include "ported62.h"
#include "ported68.h"
#include "ported77.h"
#include "ported80.h"
#include "ported95.h"
#include "ported97.h"
#include "ported98.h"
#include "ported102.h"
#include "ported104.h"
#include "ported105.h"
#include "ported107.h"
#include "ported109.h"
#include "ported110.h"
#include "ported111.h"
#include <string.h>
#include <math.h>

#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P112_Wanted")
#undef P112_Wanted
#pragma push_macro("P112_Wanted") /*gvi*/
#undef P112_Wanted /*gvi*/
int32_t P112_Wanted;
#pragma pop_macro("P112_Wanted") /*gvi*/
#pragma pop_macro("P112_Wanted")
#endif

#ifdef RE_HOOK_BUILD
#  define P112_STD __attribute__((stdcall))
#else
#  define P112_STD
#endif
static float rdf(const void *p) { float v; memcpy(&v, p, 4); return v; }
static void wrf(void *p, float v) { memcpy(p, &v, 4); }
static uint16_t rd16(const void *p) { uint16_t v; memcpy(&v, p, 2); return v; }
static void wr16(void *p, uint16_t v) { memcpy(p, &v, 2); }
static int32_t rd32(const void *p) { int32_t v; memcpy(&v, p, 4); return v; }
static const float K_ZERO = 0.0f;      /* .rdata 00546024 */
static const float K_NEAR = 0.3f;      /* .rdata 00546164 */

static void *glide_proc(const char *name) {
  for (int i = 0; i < P33_GlideCount(); i++)
    if (strcmp(P33_GlideName(i), name) == 0) return P33_GlideProc(i);
  return NULL;
}
static void alpha_combine(int32_t a, int32_t b, int32_t c, int32_t d, int32_t e) {   /* 01270dcc */
  void (P112_STD *f)(int32_t, int32_t, int32_t, int32_t, int32_t) = (void (P112_STD *)(int32_t, int32_t, int32_t, int32_t, int32_t))glide_proc("_grAlphaCombine@20");
  if (f) f(a, b, c, d, e);
}
static void alpha_test(int32_t a) {   /* 01270d68 */
  void (P112_STD *f)(int32_t) = (void (P112_STD *)(int32_t))glide_proc("_grAlphaTestFunction@4");
  if (f) f(a);
}

/* ---- опкоды скрипта: контекст c = P10_ScriptCtx (+0..8 позиция, +0x18..0x20 цель, +0x3c/+0x3e размер коробки,
   +0x44 скорость, +0x48 флаги, +0x5c 1/длина), поток P10_ScriptPtr. 0 — остаться на опкоде, 1 — дальше. ---- */
/* замедление у машины: если коробка контекста задевает машину — скорость × (расстояние до игрока / длина); в оригинале
   обе разности считаются от x игрока (00d07888) — так и оставлено */
static float near_car_speed(const uint8_t *c, float sp, float dx, float dz) {
  int16_t bw = (int16_t)rd16(c + 0x3c), bl = (int16_t)rd16(c + 0x3e);
  if (bw == 0 || bl == 0) return sp;
  int32_t ang = -P44_Atan2((int32_t)dx, (int32_t)dz) & 0xfff;
  int32_t z = (int32_t)lrintf(rdf(c + 8)), x = (int32_t)lrintf(rdf(c));
  P11_00ba52d0 = x;
  if (P102_BoxAnyCar(x, z, ang, bw / 2, bl / 2) == NULL) return sp;
  int32_t px = P99_Cars[0].pos[0];
  int32_t a = (int32_t)lrintf(rdf(c)) - px, b = (int32_t)lrintf(rdf(c + 8)) - px;
  float d = (float)sqrt((double)(a * a + b * b));
  if (d < (float)(bl * bl)) {
    float k = d / (float)bl;
    sp = (K_NEAR <= k) ? sp * k : 0.0f;
  }
  return sp;
}
int32_t P112_OpMoveTo(void) {
  uint8_t *c = P10_ScriptCtx, *s = P10_ScriptPtr;
#ifndef RE_HOOK_BUILD
  if (c == NULL || s == NULL) return 0;
#endif
  float sp = rdf(c + 0x44);
  float tx = rdf(s + 2), ty = rdf(s + 6), tz = rdf(s + 10);
  P10_ScriptPtr = s + 0xe;
  wr16(c + 0x48, (uint16_t)(rd16(c + 0x48) & 0xff7f));
  wrf(c + 0x18, tx); wrf(c + 0x1c, ty); wrf(c + 0x20, tz);
  if (sp == K_ZERO) return 1;
  float dx = tx - rdf(c), dy = ty - rdf(c + 4), dz = tz - rdf(c + 8);
  sp = near_car_speed(c, sp, dx, dz);
  float len = (float)sqrt((double)(dz * dz + dy * dy + dx * dx));
  if (len != K_ZERO) { dx /= len; dy /= len; dz /= len; }
  if (sp <= len) {
    wrf(c, dx * sp + rdf(c)); wrf(c + 4, dy * sp + rdf(c + 4)); wrf(c + 8, dz * sp + rdf(c + 8));
    P10_ScriptPtr = s;
    return 0;
  }
  wrf(c, tx); wrf(c + 4, ty); wrf(c + 8, tz);
  wr16(c + 0x48, (uint16_t)(rd16(c + 0x48) | 0x80));
  return 1;
}
int32_t P112_OpMoveCur(void) {
  uint8_t *c = P10_ScriptCtx, *s = P10_ScriptPtr;
#ifndef RE_HOOK_BUILD
  if (c == NULL || s == NULL) return 0;
#endif
  P10_ScriptPtr = s + 2;
  float sp = rdf(c + 0x44);
  wr16(c + 0x48, (uint16_t)(rd16(c + 0x48) | 0x40));
  wr16(c + 0x48, (uint16_t)(rd16(c + 0x48) & 0xff7f));
  if (sp != K_ZERO) {
    float dx = rdf(c + 0x18) - rdf(c), dy = rdf(c + 0x1c) - rdf(c + 4), dz = rdf(c + 0x20) - rdf(c + 8);
    sp = near_car_speed(c, sp, dx, dz);
    float len = (float)sqrt((double)(dz * dz + dy * dy + dx * dx));
    if (sp <= len) { P10_ScriptPtr = s; return 0; }
    wrf(c, rdf(c + 0x18)); wrf(c + 4, rdf(c + 0x1c)); wrf(c + 8, rdf(c + 0x20));
    wr16(c + 0x48, (uint16_t)(rd16(c + 0x48) | 0x80));
  }
  wr16(c + 0x48, (uint16_t)(rd16(c + 0x48) & 0xffbf));
  return 1;
}
int32_t P112_OpMoveCurve(void) {
  uint8_t *c = P10_ScriptCtx, *s = P10_ScriptPtr;
#ifndef RE_HOOK_BUILD
  if (c == NULL || s == NULL) return 0;
#endif
  uint16_t fl = rd16(s + 2);
  float tx = rdf(s + 4), tz = rdf(s + 8), v0 = rdf(s + 0xc), v1 = rdf(s + 0x10);
  P10_ScriptPtr = s + 0x14;
  wr16(c + 0x48, (uint16_t)(rd16(c + 0x48) & 0xff7f));
  wrf(c + 0x18, tx); wrf(c + 0x20, tz);
  float dx = tx - rdf(c), dz = tz - rdf(c + 8);
  float len = (float)sqrt((double)(dz * dz + dx * dx));
  if ((rd16(c + 0x48) & 0x100) == 0) {
    wrf(c + 0x5c, 1.0f / len);
    wr16(c + 0x48, (uint16_t)(rd16(c + 0x48) | 0x100));
  }
  float t = 2048.0f - 2048.0f * len * rdf(c + 0x5c);
  if (t < 512.0f && (fl & 1) != 0) t = t + t;
  else if (t > 1536.0f && (fl & 2) != 0) t = (t - 1536.0f) + (t - 1536.0f) + 1024.0f;
  else t = 1024.0f;
  int32_t i = (int32_t)lrintf(t);
  P11_00ba52d0 = i;
#ifndef RE_HOOK_BUILD
  if (i < 0 || i >= 5120) i = 1024;
#endif
  float sp = (v1 - v0) * P43_Sin[i] + v0;
  wrf(c + 0x44, sp);
  if (len != K_ZERO) { dx /= len; dz /= len; }
  if (sp <= len) {
    wrf(c, dx * sp + rdf(c)); wrf(c + 8, dz * sp + rdf(c + 8));
    P10_ScriptPtr = s;
    return 0;
  }
  wrf(c, tx); wrf(c + 8, tz);
  wr16(c + 0x48, (uint16_t)(rd16(c + 0x48) | 0x80));
  wr16(c + 0x48, (uint16_t)(rd16(c + 0x48) & 0xfeff));
  return 1;
}

/* ---- 0041f4a1: загрузка эмулируемой текстуры: info — GrTexInfo (+4 largeLod, +0xc формат, +0x10 адрес данных) ---- */
void P112_TexDownload(int32_t tmu, uint32_t addr, int32_t evenOdd, const uint8_t *info) {
  (void)tmu; (void)evenOdd;
  if (P22_DevReady == 0) return;
  P33_FlushBatches();
#ifndef RE_HOOK_BUILD
  if (info == NULL) return;
#endif
  uint32_t slot;
  if (rd32(info + 0xc) == 5) {
    slot = addr >> 16;
    if (slot > 0x1f || rd32(info + 4) != 0) return;
    P109_SlotUpload8((const uint8_t *)re_rd_ptr(info + 0x10), (int32_t)slot);
  } else {
    slot = (addr >> 17) << 1;
    if (slot > 0x1f || rd32(info + 4) != 0) return;
    P109_SlotUpload16((const uint16_t *)re_rd_ptr(info + 0x10), (int32_t)slot);
  }
  P32_Slots[slot].has_list = 0;
  P32_Slots[slot].cur_id = -1;
  P32_Slots[slot].list = NULL;
  P32_Slots[slot].cur_handle = NULL;
}

/* ---- 004a9bb0: лицо в титрах — значок записи P98_Faces[rec+2] с рамкой, по центру x = 480 ---- */
void P112_FaceIcon(uint8_t *rec, int32_t y) {
  if (y <= -0x21 || P98_CreditsFace(rec) == 0) return;
  uint16_t k = rd16(rec + 2);
#ifndef RE_HOOK_BUILD
  if (k >= 3) return;
#endif
  uint8_t *ic = (uint8_t *)re_ptr(P98_Faces[k].icon);
#ifndef RE_HOOK_BUILD
  if (ic == NULL) return;
#endif
  uint32_t w = ic[0xb] ? ic[0xb] : 0x100, h = ic[0xc] ? ic[0xc] : 0x100;
  DrawFrame_004A9DDC((int32_t)(0x1e0 - w / 2), y, (int32_t)w, (int32_t)h);
  P12_Fn00426580(0x1f);
  P110_IconRect((int32_t)(0x1e0 - w / 2), y, (int32_t)w, (int32_t)h, ic, (int32_t)P98_Faces[k].page);
}

/* ---- 004a77b0: такт погони — уровень розыска 00d11a5c (0..0xfff), копы, музыка погони, трафик ---- */
static void set_wanted(int32_t v) { G2_00D11A5C = v; P14_00d11a5c = (uint32_t)v; }
void P112_ChaseTick(void) {
  if (P62_BusyB != 0) set_wanted(0);
  if (P62_BusyE != 0) { set_wanted(0xfff); P104_12B26C = 300; P105_MusLimit = 0; }
#ifndef RE_HOOK_BUILD
  { static int k; const char *e = getenv("RE_COPDBG"); if (e && (k++ % (atoi(e) > 0 ? atoi(e) : 50)) == 0)
      fprintf(stderr, "[chase] flag %d eb4 %d eac %d eb0 %d hudoff %d\n", (int)P47_Flag, (int)P95_B87EB4, (int)G6_00B87EAC,
              (int)P58_SB87EB0, (int)P62_HudOff1); }
#endif
  if (P47_Flag == 0 || P95_B87EB4 != 0 || G6_00B87EAC != 0 || P58_SB87EB0 != 0 || P62_HudOff1 != 0) {
    P95_AmbN = 0; P95_SndReady = 0; P62_I14428C = 0;
    return;
  }
  if (G2_00D11A5C == 0xfff) P112_Wanted = 1;
  P102_CopsTick();
  P105_ChaseMusic((int32_t *)(void *)P97_D11980);
  Dec145934();
  if (G2_00D11A5C < 0x2aa) P97_D9E0 = 1;
  else {
    P97_D9E0 = (G2_00D11A5C - 0x2aa) / 0x355 + 1;
    if (P62_Max < P97_D9E0) P97_D9E0 = P62_Max;
  }
  if (G0112B284 < P97_D9E0 && P62_Max != 0) {
    P68_D11A48 = P68_D11A48 + 1;
    if (P95_B87E3C < P68_D11A48) P62_I14428C = 1;
  } else P68_D11A48 = 0;
  if (P77_C7D850 != 0) P110_RadarGrid();
}

/* ---- записи скрипта: список с P15_ListHead, следующая — адрес +0x20; текущая пишется в оба псевдонима 00d12410 ---- */
static void set_cur(uint8_t *r) { P15_ListCur = r; S_00D12410 = (uint16_t *)(void *)r; }
static void run_cur(void) { P97_ScriptResetCur(); P111_ScriptTick(); }
void P112_ScriptRunId(uint16_t id) {
  uint8_t *sp = P10_ScriptPtr, *sc = P10_ScriptCtx, *cur = P15_ListCur;
  int32_t sp2 = S_00D12414; uint8_t *sc2 = S_00D1240C; uint16_t *cur2 = S_00D12410;
  for (set_cur(P15_ListHead); P15_ListCur != NULL; set_cur((uint8_t *)re_rd_ptr(P15_ListCur + 0x20))) {
    uint16_t f = rd16(P15_ListCur);
    if ((f & 8) != 0 && (f & 2) == 0 && rd16(P15_ListCur + 6) == id) run_cur();
  }
  P10_ScriptPtr = sp; P10_ScriptCtx = sc; P15_ListCur = cur;
  S_00D12414 = sp2; S_00D1240C = sc2; S_00D12410 = cur2;
}
void P112_ScriptTriggers(void) {
  for (set_cur(P15_ListHead); P15_ListCur != NULL; set_cur((uint8_t *)re_rd_ptr(P15_ListCur + 0x20))) {
    uint8_t *r = P15_ListCur;
    uint16_t f = rd16(r);
    if ((f & 2) != 0) { P111_ScriptTick(); continue; }
#ifndef RE_HOOK_BUILD
    if (S_00D11878 < 0 || S_00D11878 >= P99_CARS_N) continue;
#endif
    int32_t px = P99_Cars[S_00D11878].pos[0], pz = P99_Cars[S_00D11878].pos[2];
    if ((f & 4) != 0) {
      if ((pz / P80_Cell + P80_HalfH) * P21_GridDiv + px / P80_Cell + P80_HalfW == rd32(r + 0xc)) run_cur();
    } else if ((f & 8) == 0) {
      float dx = (float)px - rdf(r + 0x14), dz = (float)pz - rdf(r + 0x18);
      if (dx < K_ZERO) dx = -dx;
      if (dz < K_ZERO) dz = -dz;
      if (dz * dz + dx * dx <= rdf(r + 0x10)) run_cur();
    }
  }
}

/* ---- значок в масштабе экрана: ic — запись значка (+8 страница, +9..+0xc u, v, ширина, высота) ---- */
static void icon_draw(const uint8_t *ic, float x, float y, float sx, float sy, float tw) {
  uint8_t rgb[3] = { 0xff, 0xff, 0xff };
  if (P62_I252B78 != 1) { alpha_combine(3, 8, 0, 1, 1); alpha_test(4); P62_I252B78 = 1; }
  P109_IconDraw(x, y, sx, sy, (float)ic[9], (float)ic[10], tw, (float)ic[0xc], ic[8], rgb);
  if (P62_I252B78 != 0) { alpha_combine(3, 8, 0, 2, 1); alpha_test(7); P62_I252B78 = 0; }
}
static float screen_k(void) { return (P19_Scale * (float)P19_ScrW) / P19_DivW; }
void P112_IconScaled(const uint8_t *ic, float x, float y, float sw, float sh) {
#ifndef RE_HOOK_BUILD
  if (ic == NULL) return;
#endif
  float fx = P19_ScaleX(x), fy = P19_ScaleY(y), k = screen_k();
  icon_draw(ic, fx, fy, sw * k, sh * k, (float)ic[0xb]);
}
void P112_IconBar(const uint8_t *ic, float x, float y, int32_t num, int32_t den) {
#ifndef RE_HOOK_BUILD
  if (ic == NULL) return;
#endif
  float fx = P19_ScaleX(x), fy = P19_ScaleY(y);
  float part = (float)num / (float)den, k = screen_k();
  icon_draw(ic, fx, fy, k, k * 1.1f, (float)ic[0xb] * part);
}

/* ---- 004c68a7: шкала камер режиссёра (окно ±304 кадра вокруг frame) — полосы по типу камеры, рамка, засечки ---- */
void P112_DirTimeline(int32_t frame) {
  if (P29_FlagB0 == 0) return;
  int32_t sv = DrvSetMode0042655A(0);
  float f = (float)frame;
  for (int32_t i = 0; i < NumCameras; i++) {
    DIRECTOR_CAMERA *cam = GetCamera(i), *nx = GetCamera(i + 1);
#ifndef RE_HOOK_BUILD
    if (cam == NULL) continue;
#endif
    float a = (float)cam->id - 1.0f;
    float b = (float)(nx != NULL ? nx->id : DirectorLastFrame);
    if (!(f - 304.0f <= b && a <= f + 304.0f)) continue;
    if (a < f - 304.0f) a = f - 304.0f;
    if (f + 304.0f < b) b = f + 304.0f;
    uint32_t c30 = 0, c34 = 0, c24 = 0, c28 = 0;
    switch (cam->unk00) {
    case 0:    c30 = 0xff0000; c34 = 0x7f0000; c24 = 0x3f0000; c28 = 0x7f0000; break;
    case 2:    c30 = 0xff00;   c34 = 0x7f00;   c24 = 0x3f00;   c28 = 0x7f00;   break;
    case 0x10: c30 = 0xffff00; c34 = 0x7f7f00; c24 = 0x3f3f00; c28 = 0x7f7f00; break;
    case 0x11: c30 = 0x46ffff; c34 = 0x237f7f; c24 = 0x113f3f; c28 = 0x237f7f; break;
    default: break;
    }
    float x0 = (a - (f - 304.0f)) + 16.0f;
    P109_GradRectS(x0, 432.0f, ((b - (f - 304.0f)) + 16.0f) - x0, 64.0f, c30, c34, c24, c28);
  }
  P107_Line(320.0f, 432.0f, 320.0f, 464.0f, 0);
  P107_Line(16.0f, 432.0f, 624.0f, 432.0f, 0);
  P107_Line(16.0f, 464.0f, 624.0f, 464.0f, 0);
  P107_Line(16.0f, 432.0f, 16.0f, 464.0f, 0);
  P107_Line(624.0f, 432.0f, 624.0f, 464.0f, 0);
  static const int32_t offs[4] = { 2, 0xe, 0x1a, 0x26 };
  static const float tops[4] = { 456.0f, 460.0f, 460.0f, 460.0f };
  for (int32_t t = frame - 0x162; t < frame + 0x162; t += 0x32) {
    int32_t base = (t / 0x32) * 0x32;
    for (int k = 0; k < 4; k++) {
      float x = (float)((base + offs[k]) - (frame - 0x130)) + 16.0f;
      if (16.0f <= x && x <= 624.0f) P107_Line(x, 464.0f, x, tops[k], 0);
    }
  }
  DrvSetMode0042655A(sv);
}
