#include "ported73.h"
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
void P73_InitConsts(void) {
  static const uint8_t m[9] = { 0, 1, 3, 7, 0x0f, 0x1f, 0x3f, 0x7f, 0xff };
  memset(P73_Mask, 0, sizeof P73_Mask); memcpy(P73_Mask, m, sizeof m);
}
#endif

static int32_t F2I(float f) { int32_t v; memcpy(&v, &f, 4); return v; }

/* 005173d7: каждое значение, записанное в float, округляется (fstp), цепочки внутри — расширенной точности x87 */
void P73_Text(float x, float y, uint32_t txt, int32_t a, int32_t flags) {
  volatile float sw = (float)P19_ScrW, sh = (float)P19_ScrH;
  volatile float fx = sw / 640.0f, fy = sh / 480.0f;
  volatile float cx = sw / 2.0f, cy = sh / 2.0f;
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

/* 0051bf82: индекс типа в таблице масок берётся как есть (в оригинале индекс до 255 читает соседние данные — тут >8 даёт маску 0) */
void P73_RoadSides(void) {
  for (int32_t i = 0; i < P11_00b5a8e8 && i < 64; i++) {
    uint8_t *e = P17_MapBase + i * 0x42;
    uint8_t kind = e[4];
    uint8_t mask = kind < 9 ? P73_Mask[kind] : 0;
    uint8_t bits = (uint8_t)(e[5] & mask);
    if (bits == 0)         e[0x3b] = P17_SlotMapSide(i) == 0 ? 0x82 : 0x83;
    else if (bits == mask) e[0x3b] = P17_SlotMapSide(i) == 0 ? 0x80 : 0x81;
    else                   e[0x3b] = 0;
  }
}

/* 00511e60 */
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
void P73_CatmullRom(const float *tp, float *out, const float *p0, const float *p1, const float *p2, const float *p3) {
  volatile float t = *tp;
  volatile float t2 = (float)((long double)t * t);
  volatile float t3 = (float)((long double)t2 * t);
  float half = P51_Half, c15 = P56_C546120, c25 = P56_C54611C, one = P59_One, two = P66_C2;
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
