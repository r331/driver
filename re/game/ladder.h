/* ladder.h — MLADDER campaign script records, shared by the compiler (P141, ported141.c) and the
 * interpreter (P140_LadderRun, ported140.c).  A compiled ladder is a list of 0x10-byte records
 * {int32 code, int32 a, int32 next, int32 else} (record addresses, not indices).
 * Code names follow the MLADDER source keyword that emits them; the comment says what the
 * interpreter does with the record.  Plain integer constants: using them never changes the code. */
#pragma once

#define LAD_REC_SIZE 0x10

enum {
  LAD_SETCITY    = 0,   /* SETCITY [city]: remember chapter a (city.h CITY_*), unlock level a + 1 */
  LAD_ROOM       = 1,   /* ROOM ... ENDROOM: choice screen with strings a; next = the chosen branch */
  LAD_MISSION    = 2,   /* MISSION n / SUBMISSION n: play mission a */
  LAD_RENDER     = 3,   /* RENDER n: play cut-scene (FMV) a */
  LAD_TRIGGER    = 4,   /* TRIGGER n: set story flag a (0127104c) */
  LAD_IF         = 5,   /* IF n: story flag a set -> next, else -> else */
  LAD_IFOK       = 6,   /* IFOK: last mission failed -> else, otherwise next */
  LAD_ENDIF      = 7,   /* emitted for both ELSE and ENDIF: unconditional jump to next */
  LAD_QUITONFAIL = 9,   /* QUITONFAIL: stop the ladder if the last mission failed */
  LAD_INTERVIEW  = 0xb, /* INTERVIEW: the garage interview (skipped by cheat 00b87e9c) */
  LAD_END        = 0xc  /* END: credits replay, then unlock all cheats */
};

/* Option types inside a ROOM's option list (4 x {u16 type, u16 value, u32 record address}). */
enum { LAD_OPT_NONE = 1, LAD_OPT_MISSION = 2, LAD_OPT_JOKE = 4, LAD_OPT_CARSELECT = 8 };
