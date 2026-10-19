/* ported91 — release the traffic slot owned by a car object (Game.exe 004a66ef).
   Original note: */
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
/* P91_ReleaseTraffic — Game.exe 004a66ef, cdecl.  Frees the traffic record a car object is bound to.
   In:  car — car object; car+0xcd0 points at the traffic id byte (1-based index into TrafficRecs, records
        of 0x54 bytes); the pointer is native-sized in native and 32-bit in the hook build.
   Side effects: clears the record's "in use" byte (+5), clears car+0xcb4 (TODO(RE): unsure what it holds),
        decrements the live-traffic counter G0112B284; when it reaches 0, raises G0112B280 to at least 0x200
        (TODO(RE): unsure — looks like a spawn cool-down / timer floor). */
void P91_ReleaseTraffic(uint8_t *car) {
  const uint8_t *id = *(uint8_t **)(car + 0xcd0);
  TrafficRecs[(*id - 1) * 0x54 + 5] = 0;
  *(uint32_t *)(car + 0xcb4) = 0;
  G0112B284 -= 1;
  if (G0112B284 == 0 && G0112B280 < 0x200) G0112B280 = 0x200;
}
