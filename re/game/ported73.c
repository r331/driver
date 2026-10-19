/* ported73.c — assorted small routines: scaled menu text placement (P73_Text), one-way-street flags of
   road nodes (P73_RoadSides), reset of the 64-entry particle/pedestrian object pool (P73_ParticlesReset)
   and a Catmull-Rom spline step (P73_CatmullRom).  The float routines reproduce x87 rounding points
   exactly (volatile float = value stored with fstp; long double = value kept on the FPU stack). */
#include "ported73.h"
#include "ported43.h"   /* v2.09: P43_FreeCnt/P43_FreeList/A_00C56780 — объекты образа данных (пешеходы) */
#include "ported7.h"
#include "ported59.h"   /* v2.21: P59_NODES_MAX */
#include "reptr.h"
#include <string.h>

#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P73_Mask")
#undef P73_Mask
#pragma push_macro("P73_Mask") /*gvi*/
#undef P73_Mask /*gvi*/
p73_mask_t P73_Mask;
#pragma pop_macro("P73_Mask") /*gvi*/
#pragma pop_macro("P73_Mask")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P73_C566FC")
#undef P73_C566FC
#pragma push_macro("P73_C566FC") /*gvi*/
#undef P73_C566FC /*gvi*/
int32_t P73_C566FC;
#pragma pop_macro("P73_C566FC") /*gvi*/
#pragma pop_macro("P73_C566FC")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P73_C5670C")
#undef P73_C5670C
#pragma push_macro("P73_C5670C") /*gvi*/
#undef P73_C5670C /*gvi*/
int32_t P73_C5670C;
#pragma pop_macro("P73_C5670C") /*gvi*/
#pragma pop_macro("P73_C5670C")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P73_C56760")
#undef P73_C56760
#pragma push_macro("P73_C56760") /*gvi*/
#undef P73_C56760 /*gvi*/
int32_t P73_C56760;
#pragma pop_macro("P73_C56760") /*gvi*/
#pragma pop_macro("P73_C56760")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P73_D00214")
#undef P73_D00214
#pragma push_macro("P73_D00214") /*gvi*/
#undef P73_D00214 /*gvi*/
int32_t P73_D00214;
#pragma pop_macro("P73_D00214") /*gvi*/
#pragma pop_macro("P73_D00214")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P73_CF56BC")
#undef P73_CF56BC
#pragma push_macro("P73_CF56BC") /*gvi*/
#undef P73_CF56BC /*gvi*/
int32_t P73_CF56BC;
#pragma pop_macro("P73_CF56BC") /*gvi*/
#pragma pop_macro("P73_CF56BC")
#endif

#ifndef RE_HOOK_BUILD
/* P73_InitConsts — native only (no Game.exe code): fills P73_Mask with the .data table at 00575e34,
   mask[n] = (1 << n) - 1 for n = 0..8. */
void P73_InitConsts(void) {
  static const uint8_t m[9] = { 0, 1, 3, 7, 0x0f, 0x1f, 0x3f, 0x7f, 0xff };
  memset(P73_Mask, 0, sizeof P73_Mask); memcpy(P73_Mask, m, sizeof m);
}
#endif

/* Bit pattern of a float, for the menu setters that take floats as raw dwords. */
static int32_t F2I(float f) { int32_t v; memcpy(&v, &f, 4); return v; }

/* 005173d7: каждое значение, записанное в float, округляется (fstp), цепочки внутри — расширенной точности x87 */
/* P73_Text — Game.exe 005173d7.  Draws menu string txt at 640x480 design coordinates (x, y), mapped to
   the real screen P19_ScrW x P19_ScrH and then zoomed by P19_Scale about the screen centre.  Sets the
   glyph scale (MenuSetPos), the colour (bytes 00b5a834..36), position + a/flags (MenuSetVals5D77C0)
   and prints through P67_Fn40ABAC.  TODO(RE): unsure what `a` is (passed on as a byte, alpha?). */
void P73_Text(float x, float y, uint32_t txt, int32_t a, int32_t flags) {
  volatile float sw = (float)P19_ScrW, sh = (float)P19_ScrH;
  volatile float fx = sw / 640.0f, fy = sh / 480.0f;   /* design -> screen scale */
  volatile float cx = sw / 2.0f, cy = sh / 2.0f;       /* screen centre */
  float s = P19_Scale;
  volatile float px = (float)(((long double)x * fx - cx) * s + cx);
  volatile float py = (float)(((long double)y * fy - cy) * s + cy);
  GlobalSet0040B0A4();
  volatile float sx = (float)((long double)fx * s), sy = (float)((long double)fy * s);
  MenuSetPos(F2I(sx), F2I(sy));
  MenuSetColor(S_00B5A834, S_00B5A835, S_00B5A836);
  MenuSetVals5D77C0(F2I(px), F2I(py), (uint8_t)a, (uint8_t)flags);
  P67_Fn40ABAC(txt);
}

/* 0051bf82: одностороннее движение — байт +0x3d узла 00bf1c40 (0x80..0x83 — участок одностороннего движения по стороне 0..3,
   0 — двустороннее; его читают появление трафика 00491a56 и др.). Индекс типа в таблице масок 00575e34 берётся как есть: в оригинале
   индекс до 255 читает соседние данные — в native они из образа данных (re_ptr), без образа (selftest) >8 даёт маску 0.
   v2.21: цикл шёл только по первым 64 узлам (i < 64 — размер прежней native-таблицы); в Майами 356 узлов — у узлов ≥ 64 флаг
   оставался 0, и трафик появлялся на односторонних улицах в обе стороны («встречка»). */
/* P73_RoadSides — Game.exe 0051bf82.  For every road node (P17_MapBase, 0x42-byte records, count
   P11_00b5a8e8): kind = byte +4, lane bits = byte +5 & mask[kind]; writes byte +0x3b:
     no bits set  -> 0x82 (+1 if P17_SlotMapSide(i) != 0)
     all bits set -> 0x80 (+1 likewise)
     otherwise    -> 0 (two-way).
   (The Russian note above says +0x3d; the code writes +0x3b, matching ported73.h.  TODO(RE): which
   lane direction "no bits" vs "all bits" stands for.) */
void P73_RoadSides(void) {
  for (int32_t i = 0; i < P11_00b5a8e8 && i < P59_NODES_MAX; i++) {
    uint8_t *e = P17_MapBase + i * 0x42;          /* road node record */
    uint8_t kind = e[4];
    uint8_t mask = kind < 9 ? P73_Mask[kind] : 0;
#ifndef RE_HOOK_BUILD
    if (kind >= 9) { const uint8_t *m = (const uint8_t *)re_ptr(0x00575e34u + kind); if (m != NULL) mask = *m; }
#else
    /* Overrides the two lines above: like the original, index P73_Mask (00575e34) directly with any kind,
       which reads the neighbouring .data bytes for kind >= 9 (native: P73_Mask is a view into the data image).
       The lines above are therefore dead but harmless; kept so the generated code stays identical. */
    mask = P73_Mask[kind];
#endif
    uint8_t bits = (uint8_t)(e[5] & mask);
    if (bits == 0)         e[0x3b] = P17_SlotMapSide(i) == 0 ? 0x82 : 0x83;
    else if (bits == mask) e[0x3b] = P17_SlotMapSide(i) == 0 ? 0x80 : 0x81;
    else                   e[0x3b] = 0;
  }
}

/* 00511e60 */
/* P73_ParticlesReset — Game.exe 00511e60.  Resets the pool of 64 objects A_00C56780 (0xb4 bytes each;
   ported43.h: pedestrians) and its free list P43_FreeList: zeroes the counters and the pool, gives each
   object its index (int16 at +2) and the per-parity value (+0x44: even = P73_D00214, odd = P73_CF56BC),
   free list = identity.  Then the counting radius P71_Near = 0x44aa20 * 64 / P60_PartLimit (unchanged if
   the limit is 0) and P73_C56760 = limit / 4 + 1 (limit > 0, rounded toward 0) else 0.
   The chained assignments reproduce the original's store order. */
void P73_ParticlesReset(void) {
  P71_NearAdd = 0;
  P71_Near = P71_NearAdd;
  P73_C566FC = 0;
  P43_FreeCnt = P73_C566FC;
  G8_00C56710 = P43_FreeCnt;
  P73_C5670C = 0;
  memset(P43_FreeList, 0, 0x100);
  memset(A_00C56780, 0, 0x2d00);
  P43_FreeCnt = 0;
  G8_00C56710 = 0;
  for (int32_t i = 0; i < 0x40; i++) {
    int32_t v = (i & 1) ? P73_CF56BC : P73_D00214;
    memcpy(&A_00C56780[i * 0xb4 + 0x44], &v, 4);
    P43_FreeList[i] = i;
    int16_t id = (int16_t)i; memcpy(&A_00C56780[i * 0xb4 + 2], &id, 2);
  }
  P71_Near = 0x44aa20;
  if (P60_PartLimit != 0) P71_Near = (int32_t)((uint32_t)P71_Near << 6) / P60_PartLimit;
  P71_NearAdd = 0;
  P73_C5670C = 0;
  if (P60_PartLimit > 0) P73_C56760 = (P60_PartLimit + ((P60_PartLimit >> 31) & 3)) / 4 + 1;
  else P73_C56760 = 0;
}

/* 0049f031: t, t^2, t^3 и четыре веса хранятся во float (fstp), цепочки внутри весов и суммы — расширенной точности */
/* P73_CatmullRom — Game.exe 0049f031.  Evaluates a Catmull-Rom spline segment at t = *tp for the
   components 4, 0, 1, 2 (in that order) of four control points:
     out = a0*p0 + a1*p1 + a2*p2 + a3*p3, with the standard weights
     a0 = -t/2 + t^2 - t^3/2,  a1 = 1 - 2.5 t^2 + 1.5 t^3,  a2 = t/2 + 2 t^2 - 1.5 t^3,  a3 = (t^3 - t^2)/2
   (constants read from Game.exe .rdata: half, 1.5, 2.5, 1, 2).  Component 3 is not touched.
   TODO(RE): unsure what component 4 of a point is (time / roll?). */
void P73_CatmullRom(const float *tp, float *out, const float *p0, const float *p1, const float *p2, const float *p3) {
  volatile float t = *tp;
  volatile float t2 = (float)((long double)t * t);
  volatile float t3 = (float)((long double)t2 * t);
  float half = P51_Half, c15 = P56_C546120, c25 = P56_C54611C, one = P59_One, two = P66_C2;   /* 0.5, 1.5, 2.5, 1, 2 */
  volatile float a0 = (float)(((long double)t2 - (long double)half * t3) - (long double)half * t);
  volatile float a1 = (float)(((long double)c15 * t3 - (long double)c25 * t2) + one);
  volatile float a2 = (float)((long double)half * t + ((long double)two * t2 - (long double)c15 * t3));
  volatile float a3 = (float)((long double)half * t3 - (long double)half * t2);
  static const int idx[4] = { 4, 0, 1, 2 };
  for (int k = 0; k < 4; k++) {
    int i = idx[k];
    out[i] = (float)((((long double)a0 * p0[i] + (long double)a1 * p1[i]) + (long double)a2 * p2[i]) + (long double)a3 * p3[i]);
  }
}
