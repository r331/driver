/* Освобождение слота трафика — восстановлено из Game.exe (004a66ef). */
#include "ported91.h"

#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("G0112B280")
#undef G0112B280
#pragma push_macro("G0112B280") /*gvi*/
#undef G0112B280 /*gvi*/
int32_t G0112B280;
#pragma pop_macro("G0112B280") /*gvi*/
#pragma pop_macro("G0112B280")
#endif

/* 004a66ef */
void P91_ReleaseTraffic(uint8_t *car) {
  const uint8_t *id = *(uint8_t **)(car + 0xcd0);
  TrafficRecs[(*id - 1) * 0x54 + 5] = 0;
  *(uint32_t *)(car + 0xcb4) = 0;
  G0112B284 -= 1;
  if (G0112B284 == 0 && G0112B280 < 0x200) G0112B280 = 0x200;
}
