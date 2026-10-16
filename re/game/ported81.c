#include "ported81.h"
#include <math.h>
#include <string.h>

#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P81_Flag")
#undef P81_Flag
#pragma push_macro("P81_Flag") /*gvi*/
#undef P81_Flag /*gvi*/
int32_t P81_Flag;
#pragma pop_macro("P81_Flag") /*gvi*/
#pragma pop_macro("P81_Flag")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P81_PosX")
#undef P81_PosX
#pragma push_macro("P81_PosX") /*gvi*/
#undef P81_PosX /*gvi*/
float P81_PosX;
#pragma pop_macro("P81_PosX") /*gvi*/
#pragma pop_macro("P81_PosX")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P81_NegX")
#undef P81_NegX
#pragma push_macro("P81_NegX") /*gvi*/
#undef P81_NegX /*gvi*/
float P81_NegX;
#pragma pop_macro("P81_NegX") /*gvi*/
#pragma pop_macro("P81_NegX")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P81_PosY")
#undef P81_PosY
#pragma push_macro("P81_PosY") /*gvi*/
#undef P81_PosY /*gvi*/
float P81_PosY;
#pragma pop_macro("P81_PosY") /*gvi*/
#pragma pop_macro("P81_PosY")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P81_NegY")
#undef P81_NegY
#pragma push_macro("P81_NegY") /*gvi*/
#undef P81_NegY /*gvi*/
float P81_NegY;
#pragma pop_macro("P81_NegY") /*gvi*/
#pragma pop_macro("P81_NegY")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P81_PosZ")
#undef P81_PosZ
#pragma push_macro("P81_PosZ") /*gvi*/
#undef P81_PosZ /*gvi*/
float P81_PosZ;
#pragma pop_macro("P81_PosZ") /*gvi*/
#pragma pop_macro("P81_PosZ")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P81_NegZ")
#undef P81_NegZ
#pragma push_macro("P81_NegZ") /*gvi*/
#undef P81_NegZ /*gvi*/
float P81_NegZ;
#pragma pop_macro("P81_NegZ") /*gvi*/
#pragma pop_macro("P81_NegZ")
#endif

/* |v| + фон (x87: сумма в расширенной точности, запись во float), потолок 1.0 (сравнение «строго больше»;
   NaN не ограничивается — как test ah,0x41 в оригинале). */
static float p81_mag(float v, float base) {
  float r = (float)((long double)fabs((double)v) + (long double)base);
  if (r > 1.0f) r = 1.0f;
  return r;
}

void P81_Light(void) {
  float base = P19_Out68;
  float x = P19_OutA, y = P19_OutB, z = P19_OutC;
  if (x >= 0.0f) { P81_PosX = p81_mag(x, base); P81_NegX = base; }   /* NaN идёт в «минус», как fcomp в оригинале */
  else           { P81_NegX = p81_mag(x, base); P81_PosX = base; }
  if (y >= 0.0f) { P81_PosY = p81_mag(y, base); P81_NegY = base; }
  else           { P81_NegY = p81_mag(y, base); P81_PosY = base; }
  if (z >= 0.0f) { P81_PosZ = p81_mag(z, base); P81_NegZ = base; }
  else           { P81_NegZ = p81_mag(z, base); P81_PosZ = base; }
}

void P81_Limit(int32_t v) {
  float ref; memcpy(&ref, &P53_Var26A4, 4);
  float d = (float)v - ref;
  if (!(d >= 0.0f)) {                                    /* fcomp: NaN идёт сюда же */
    float a = (float)fabs((double)d);
    if (a > 100.0f || !(P81_Span > 0.0f)) P81_Flag = 0x40000000;
  }
}
