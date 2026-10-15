#include "ported81.h"
#include <math.h>
#include <string.h>

GAME_VAR_DEF(float, P81_Span, 0x00d026b4)
GAME_VAR_DEF(int32_t, P81_Flag, 0x00d02708)
GAME_VAR_DEF(float, P81_PosX, 0x011f0050)
GAME_VAR_DEF(float, P81_NegX, 0x01209648)
GAME_VAR_DEF(float, P81_PosY, 0x011b6144)
GAME_VAR_DEF(float, P81_NegY, 0x01209664)
GAME_VAR_DEF(float, P81_PosZ, 0x01209640)
GAME_VAR_DEF(float, P81_NegZ, 0x01209610)

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
