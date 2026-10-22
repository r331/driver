/* ported11.c — a batch of small Game.exe functions named Action_ADDRESS (English overview; original notes
   follow): menu actions, script argument readers, level table readers, pause-menu panels and sliders,
   view setup helpers.  The address in each name is the Game.exe address (do not rename). */
#include "ported11.h"
#include "ported152.h"
#include "ported27.h"
#include "globalsets.h"
#include "ported29.h"
#ifndef RE_HOOK_BUILD
#include "ported43.h"
#include "ported44.h"
#include "ported59.h"
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P11_00b87e7c")
#undef P11_00b87e7c
#pragma push_macro("P11_00b87e7c") /*gvi*/
#undef P11_00b87e7c /*gvi*/
int32_t P11_00b87e7c;
#pragma pop_macro("P11_00b87e7c") /*gvi*/
#pragma pop_macro("P11_00b87e7c")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P11_005c6760")
#undef P11_005c6760
#pragma push_macro("P11_005c6760") /*gvi*/
#undef P11_005c6760 /*gvi*/
int32_t P11_005c6760;
#pragma pop_macro("P11_005c6760") /*gvi*/
#pragma pop_macro("P11_005c6760")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P11_01271060")
#undef P11_01271060
#pragma push_macro("P11_01271060") /*gvi*/
#undef P11_01271060 /*gvi*/
int32_t P11_01271060;
#pragma pop_macro("P11_01271060") /*gvi*/
#pragma pop_macro("P11_01271060")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P11_00b87e38")
#undef P11_00b87e38
#pragma push_macro("P11_00b87e38") /*gvi*/
#undef P11_00b87e38 /*gvi*/
int32_t P11_00b87e38;
#pragma pop_macro("P11_00b87e38") /*gvi*/
#pragma pop_macro("P11_00b87e38")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P11_00b20360")
#undef P11_00b20360
#pragma push_macro("P11_00b20360") /*gvi*/
#undef P11_00b20360 /*gvi*/
int32_t P11_00b20360;
#pragma pop_macro("P11_00b20360") /*gvi*/
#pragma pop_macro("P11_00b20360")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P11_00c81494")
#undef P11_00c81494
#pragma push_macro("P11_00c81494") /*gvi*/
#undef P11_00c81494 /*gvi*/
int32_t P11_00c81494;
#pragma pop_macro("P11_00c81494") /*gvi*/
#pragma pop_macro("P11_00c81494")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P11_00ba52d0")
#undef P11_00ba52d0
#pragma push_macro("P11_00ba52d0") /*gvi*/
#undef P11_00ba52d0 /*gvi*/
int32_t P11_00ba52d0;
#pragma pop_macro("P11_00ba52d0") /*gvi*/
#pragma pop_macro("P11_00ba52d0")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P11_00b31efc")
#undef P11_00b31efc
#pragma push_macro("P11_00b31efc") /*gvi*/
#undef P11_00b31efc /*gvi*/
int32_t P11_00b31efc;
#pragma pop_macro("P11_00b31efc") /*gvi*/
#pragma pop_macro("P11_00b31efc")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P11_00c823d0")
#undef P11_00c823d0
#pragma push_macro("P11_00c823d0") /*gvi*/
#undef P11_00c823d0 /*gvi*/
int32_t P11_00c823d0;
#pragma pop_macro("P11_00c823d0") /*gvi*/
#pragma pop_macro("P11_00c823d0")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P11_00d11934")
#undef P11_00d11934
#pragma push_macro("P11_00d11934") /*gvi*/
#undef P11_00d11934 /*gvi*/
int32_t P11_00d11934;
#pragma pop_macro("P11_00d11934") /*gvi*/
#pragma pop_macro("P11_00d11934")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P11_00b5a734")
#undef P11_00b5a734
#pragma push_macro("P11_00b5a734") /*gvi*/
#undef P11_00b5a734 /*gvi*/
int32_t P11_00b5a734;
#pragma pop_macro("P11_00b5a734") /*gvi*/
#pragma pop_macro("P11_00b5a734")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P11_00b5a730")
#undef P11_00b5a730
#pragma push_macro("P11_00b5a730") /*gvi*/
#undef P11_00b5a730 /*gvi*/
int32_t P11_00b5a730;
#pragma pop_macro("P11_00b5a730") /*gvi*/
#pragma pop_macro("P11_00b5a730")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P11_00575554")
#undef P11_00575554
#pragma push_macro("P11_00575554") /*gvi*/
#undef P11_00575554 /*gvi*/
int32_t P11_00575554;
#pragma pop_macro("P11_00575554") /*gvi*/
#pragma pop_macro("P11_00575554")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P11_00575550")
#undef P11_00575550
#pragma push_macro("P11_00575550") /*gvi*/
#undef P11_00575550 /*gvi*/
int32_t P11_00575550;
#pragma pop_macro("P11_00575550") /*gvi*/
#pragma pop_macro("P11_00575550")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P11_00bdc28c")
#undef P11_00bdc28c
#pragma push_macro("P11_00bdc28c") /*gvi*/
#undef P11_00bdc28c /*gvi*/
int32_t P11_00bdc28c;
#pragma pop_macro("P11_00bdc28c") /*gvi*/
#pragma pop_macro("P11_00bdc28c")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P11_005507d0")
#undef P11_005507d0
#pragma push_macro("P11_005507d0") /*gvi*/
#undef P11_005507d0 /*gvi*/
int32_t P11_005507d0;
#pragma pop_macro("P11_005507d0") /*gvi*/
#pragma pop_macro("P11_005507d0")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P11_005507d4")
#undef P11_005507d4
#pragma push_macro("P11_005507d4") /*gvi*/
#undef P11_005507d4 /*gvi*/
int32_t P11_005507d4;
#pragma pop_macro("P11_005507d4") /*gvi*/
#pragma pop_macro("P11_005507d4")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P11_005507d8")
#undef P11_005507d8
#pragma push_macro("P11_005507d8") /*gvi*/
#undef P11_005507d8 /*gvi*/
int32_t P11_005507d8;
#pragma pop_macro("P11_005507d8") /*gvi*/
#pragma pop_macro("P11_005507d8")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P11_00b5a8e8")
#undef P11_00b5a8e8
#pragma push_macro("P11_00b5a8e8") /*gvi*/
#undef P11_00b5a8e8 /*gvi*/
int32_t P11_00b5a8e8;
#pragma pop_macro("P11_00b5a8e8") /*gvi*/
#pragma pop_macro("P11_00b5a8e8")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P11_00b5a8ec")
#undef P11_00b5a8ec
#pragma push_macro("P11_00b5a8ec") /*gvi*/
#undef P11_00b5a8ec /*gvi*/
int32_t P11_00b5a8ec;
#pragma pop_macro("P11_00b5a8ec") /*gvi*/
#pragma pop_macro("P11_00b5a8ec")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P11_01270c38")
#undef P11_01270c38
#pragma push_macro("P11_01270c38") /*gvi*/
#undef P11_01270c38 /*gvi*/
int32_t P11_01270c38;
#pragma pop_macro("P11_01270c38") /*gvi*/
#pragma pop_macro("P11_01270c38")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P11_00575ef8")
#undef P11_00575ef8
#pragma push_macro("P11_00575ef8") /*gvi*/
#undef P11_00575ef8 /*gvi*/
int32_t P11_00575ef8;
#pragma pop_macro("P11_00575ef8") /*gvi*/
#pragma pop_macro("P11_00575ef8")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P11_01270c24")
#undef P11_01270c24
#pragma push_macro("P11_01270c24") /*gvi*/
#undef P11_01270c24 /*gvi*/
float P11_01270c24;
#pragma pop_macro("P11_01270c24") /*gvi*/
#pragma pop_macro("P11_01270c24")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P11_01270c28")
#undef P11_01270c28
#pragma push_macro("P11_01270c28") /*gvi*/
#undef P11_01270c28 /*gvi*/
float P11_01270c28;
#pragma pop_macro("P11_01270c28") /*gvi*/
#pragma pop_macro("P11_01270c28")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P11_0125f3e0")
#undef P11_0125f3e0
#pragma push_macro("P11_0125f3e0") /*gvi*/
#undef P11_0125f3e0 /*gvi*/
float P11_0125f3e0;
#pragma pop_macro("P11_0125f3e0") /*gvi*/
#pragma pop_macro("P11_0125f3e0")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P11_0125f3f8")
#undef P11_0125f3f8
#pragma push_macro("P11_0125f3f8") /*gvi*/
#undef P11_0125f3f8 /*gvi*/
float P11_0125f3f8;
#pragma pop_macro("P11_0125f3f8") /*gvi*/
#pragma pop_macro("P11_0125f3f8")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P11_00546028")
#undef P11_00546028
#pragma push_macro("P11_00546028") /*gvi*/
#undef P11_00546028 /*gvi*/
float P11_00546028;
#pragma pop_macro("P11_00546028") /*gvi*/
#pragma pop_macro("P11_00546028")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P11_0054602c")
#undef P11_0054602c
#pragma push_macro("P11_0054602c") /*gvi*/
#undef P11_0054602c /*gvi*/
float P11_0054602c;
#pragma pop_macro("P11_0054602c") /*gvi*/
#pragma pop_macro("P11_0054602c")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P11_0054604c")
#undef P11_0054604c
#pragma push_macro("P11_0054604c") /*gvi*/
#undef P11_0054604c /*gvi*/
float P11_0054604c;
#pragma pop_macro("P11_0054604c") /*gvi*/
#pragma pop_macro("P11_0054604c")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P11_00546054")
#undef P11_00546054
#pragma push_macro("P11_00546054") /*gvi*/
#undef P11_00546054 /*gvi*/
float P11_00546054;
#pragma pop_macro("P11_00546054") /*gvi*/
#pragma pop_macro("P11_00546054")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P11_00546080")
#undef P11_00546080
#pragma push_macro("P11_00546080") /*gvi*/
#undef P11_00546080 /*gvi*/
float P11_00546080;
#pragma pop_macro("P11_00546080") /*gvi*/
#pragma pop_macro("P11_00546080")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P11_00572b40")
#undef P11_00572b40
#pragma push_macro("P11_00572b40") /*gvi*/
#undef P11_00572b40 /*gvi*/
p11_u32arr P11_00572b40;
#pragma pop_macro("P11_00572b40") /*gvi*/
#pragma pop_macro("P11_00572b40")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P11_0057b740")
#undef P11_0057b740
#pragma push_macro("P11_0057b740") /*gvi*/
#undef P11_0057b740 /*gvi*/
uint8_t P11_0057b740;
#pragma pop_macro("P11_0057b740") /*gvi*/
#pragma pop_macro("P11_0057b740")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P11_005d592e")
#undef P11_005d592e
#pragma push_macro("P11_005d592e") /*gvi*/
#undef P11_005d592e /*gvi*/
uint8_t P11_005d592e;
#pragma pop_macro("P11_005d592e") /*gvi*/
#pragma pop_macro("P11_005d592e")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P11_005d57ae")
#undef P11_005d57ae
#pragma push_macro("P11_005d57ae") /*gvi*/
#undef P11_005d57ae /*gvi*/
uint8_t P11_005d57ae;
#pragma pop_macro("P11_005d57ae") /*gvi*/
#pragma pop_macro("P11_005d57ae")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P11_0125f420")
#undef P11_0125f420
#pragma push_macro("P11_0125f420") /*gvi*/
#undef P11_0125f420 /*gvi*/
p11_slots_t P11_0125f420;
#pragma pop_macro("P11_0125f420") /*gvi*/
#pragma pop_macro("P11_0125f420")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P11_00bf1c40")
#undef P11_00bf1c40
#pragma push_macro("P11_00bf1c40") /*gvi*/
#undef P11_00bf1c40 /*gvi*/
p11_big_t P11_00bf1c40;
#pragma pop_macro("P11_00bf1c40") /*gvi*/
#pragma pop_macro("P11_00bf1c40")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P11_00c1ed80")
#undef P11_00c1ed80
#pragma push_macro("P11_00c1ed80") /*gvi*/
#undef P11_00c1ed80 /*gvi*/
p11_big_t P11_00c1ed80;
#pragma pop_macro("P11_00c1ed80") /*gvi*/
#pragma pop_macro("P11_00c1ed80")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P11_00c12c60")
#undef P11_00c12c60
#pragma push_macro("P11_00c12c60") /*gvi*/
#undef P11_00c12c60 /*gvi*/
p11_big_t P11_00c12c60;
#pragma pop_macro("P11_00c12c60") /*gvi*/
#pragma pop_macro("P11_00c12c60")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P11_00c1cd20")
#undef P11_00c1cd20
#pragma push_macro("P11_00c1cd20") /*gvi*/
#undef P11_00c1cd20 /*gvi*/
p11_big_t P11_00c1cd20;
#pragma pop_macro("P11_00c1cd20") /*gvi*/
#pragma pop_macro("P11_00c1cd20")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P11_00c80c60")
#undef P11_00c80c60
#pragma push_macro("P11_00c80c60") /*gvi*/
#undef P11_00c80c60 /*gvi*/
uint8_t P11_00c80c60;
#pragma pop_macro("P11_00c80c60") /*gvi*/
#pragma pop_macro("P11_00c80c60")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P11_00552e18")
#undef P11_00552e18
#pragma push_macro("P11_00552e18") /*gvi*/
#undef P11_00552e18 /*gvi*/
uint8_t P11_00552e18;
#pragma pop_macro("P11_00552e18") /*gvi*/
#pragma pop_macro("P11_00552e18")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P11_00579710")
#undef P11_00579710
#pragma push_macro("P11_00579710") /*gvi*/
#undef P11_00579710 /*gvi*/
uint8_t P11_00579710;
#pragma pop_macro("P11_00579710") /*gvi*/
#pragma pop_macro("P11_00579710")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P11_00b94280")
#undef P11_00b94280
#pragma push_macro("P11_00b94280") /*gvi*/
#undef P11_00b94280 /*gvi*/
uint8_t P11_00b94280;
#pragma pop_macro("P11_00b94280") /*gvi*/
#pragma pop_macro("P11_00b94280")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P11_00b98280")
#undef P11_00b98280
#pragma push_macro("P11_00b98280") /*gvi*/
#undef P11_00b98280 /*gvi*/
uint8_t P11_00b98280;
#pragma pop_macro("P11_00b98280") /*gvi*/
#pragma pop_macro("P11_00b98280")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P11_011f4080")
#undef P11_011f4080
#pragma push_macro("P11_011f4080") /*gvi*/
#undef P11_011f4080 /*gvi*/
uint8_t P11_011f4080;
#pragma pop_macro("P11_011f4080") /*gvi*/
#pragma pop_macro("P11_011f4080")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P11_00b1c268")
#undef P11_00b1c268
#pragma push_macro("P11_00b1c268") /*gvi*/
#undef P11_00b1c268 /*gvi*/
uint8_t P11_00b1c268;
#pragma pop_macro("P11_00b1c268") /*gvi*/
#pragma pop_macro("P11_00b1c268")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P11_011effa0")
#undef P11_011effa0
#pragma push_macro("P11_011effa0") /*gvi*/
#undef P11_011effa0 /*gvi*/
uint8_t P11_011effa0;
#pragma pop_macro("P11_011effa0") /*gvi*/
#pragma pop_macro("P11_011effa0")
#endif
/* SndHelper_00407D97 — Game.exe 00407d97.  Unless debug text is suppressed (00b87e7c), calls 004bf910 on the
   menu screen 0057b740 with a, b.  TODO(RE): the "Snd" name is historical; unsure what 004bf910 draws. */
void SndHelper_00407D97(uint8_t a, uint8_t b) {
  if (P11_00b87e7c == 0) Call004BF910(ADDR(P11_0057b740), a, b);
}

/* SndHelper_00407D56 — Game.exe 00407d56.  Fills a rectangle of the 8-bit menu screen (x, y, width p4 rounded
   down to a multiple of 4, height p5) with colour 005c6760.  p3 unused. */
void SndHelper_00407D56(int32_t x, int32_t y, uint32_t p3, uint32_t p4, uint32_t p5) {
  (void)p3; P152_ScreenFill(x, y, (int32_t)(p4 & 0xfffffffcu), (int32_t)p5, (uint8_t)P11_005c6760);   /* v2.02: 005291ed перенесена; буфер — P65_Screen (P11_0057b740 был отдельным native-объектом) */
}

/* CopySlots_0040AA82 — Game.exe 0040aa82.  Copies 10 8-byte entries of block n (0x806 bytes per block) from
   005d57ae to 005d592e. */
void CopySlots_0040AA82(uint32_t n) {
  for (int32_t i = 0; i < 10; i++)
    Call0052B650(ADDR(P11_005d592e) + i*8 + (n&0xff)*0x806, ADDR(P11_005d57ae) + i*8 + (n&0xff)*0x806, 8);
}

/* MenuAction_0041645B / MenuAction_004164B2 — Game.exe 0041645b / 004164b2.  Leave the menu, switch to
   front-end mode 10 with 00b87e38 = 200 / 0xfa and redraw.  Return 1.
   These are the Training menu 0054e1d0 entries "Car park" (00b87e38 = 200) and "Desert" (0xfa); mode 10 = Training. */
uint32_t MenuAction_0041645B(void) {
  MenuAction40CD17(); P11_01271060 = 10; P11_00b87e38 = 200; UiCall0040C455(1, 0); return 1;
}

uint32_t MenuAction_004164B2(void) {
  MenuAction40CD17(); P11_01271060 = 10; P11_00b87e38 = 0xfa; UiCall0040C455(1, 0); return 1;
}

/* GetRect_0048F34C — Game.exe 0048f34c.  0048f3b4 with words 0, 4, 8, 12 of record i of 00c1ed8a (0x2c bytes each). */
uint32_t GetRect_0048F34C(int32_t i) {
  const int16_t *p = &P11_00c1ed8a[i * 0x16];
  return Call0048F3B4(p[0], p[4], p[8], p[12]);
}

/* DrawFrame_004A9DDC — Game.exe 004a9ddc.  Draws the frame 00552e18 around (x, y, w, h) with a 6-pixel margin. */
void DrawFrame_004A9DDC(int32_t x, int32_t y, int32_t w, int32_t h) {
  Call004A9F45(x - 6, y - 6, w + 0xc, h + 0xc, ADDR(P11_00552e18));
}

/* ScriptReadShort3_004D02C6 — Game.exe 004d02c6.  Script command: skips the opcode word and copies three
   int16 arguments into the script context (+0x10).  Returns 1. */
uint32_t ScriptReadShort3_004D02C6(void) {
  P10_ScriptPtr += 2;
  for (int i = 0; i < 3; i++) { memcpy(P10_ScriptCtx + 0x10 + i*2, P10_ScriptPtr, 2); P10_ScriptPtr += 2; }
  return 1;
}

/* ScriptReadVec3_004D033F — Game.exe 004d033f.  Script command: three int32 arguments into the context (+0x18),
   then flags +0x48: set bit 0, clear bits 1 and 7.  Returns 1. */
uint32_t ScriptReadVec3_004D033F(void) {
  P10_ScriptPtr += 2;
  for (int i = 0; i < 3; i++) { memcpy(P10_ScriptCtx + 0x18 + i*4, P10_ScriptPtr, 4); P10_ScriptPtr += 4; }
  { uint16_t f; memcpy(&f, P10_ScriptCtx + 0x48, 2); f = (uint16_t)((f & 0xff7d) | 1); memcpy(P10_ScriptCtx + 0x48, &f, 2); }
  return 1;
}

/* TryStartTrack_004D611B — Game.exe 004d611b.  If sound channel 0xf is free, plays sample a on it and clears
   00b20360. */
void TryStartTrack_004D611B(uint32_t a) {
  if (Call00524473(0xf) == 0) { UiCall00523E50((int32_t)a, 0xf, -1); P11_00b20360 = 0; }
}

/* DrawBanner_004F5D98 — Game.exe 004f5d98.  While 00c81494 > 0 draws sprite 00c80c60 at (320, 80). */
void DrawBanner_004F5D98(void) {
  if (0 < P11_00c81494) DrawSprite(0x140, 0x50, ADDR(P11_00c80c60), 0, 1, 0xff, 0xff, 0xff);
}

/* ReadBlocks_004EB7CF — Game.exe 004eb7cf.  Reads 0x400 records of 0x46 bytes into 0125f420 (used by P76_MarkSlots). */
void ReadBlocks_004EB7CF(void *f) {
  for (int32_t i = 0; i < 0x400; i++) P27_ReadChunked(&P11_0125f420[i * 0x46], 0x46, 1, f);
}

/* Общая часть таблиц уровня: число записей (4 байта), затем записи по esz байт; в native счётчик ограничен размером массива. */
/* read_table — local helper: a level table = int32 count + count records of esz bytes.
   Native: a count that would overflow the destination reads nothing. */
static void read_table(void *f, int32_t *cnt, void *dst, int32_t esz) {
  P27_ReadChunked(cnt, 1, 4, f);
#ifndef RE_HOOK_BUILD
  if (*cnt < 0 || (int64_t)*cnt * esz > (int64_t)sizeof(p11_big_t)) { *cnt = 0; return; }
#endif
  P27_ReadChunked(dst, *cnt, esz, f);
}
/* ReadTable_004EC466 / 004EC49A / 004EC522 / 004EC556 — Game.exe addresses as named.  Read four level tables
   (records of 0x42, 0x2c, 0x14 and 8 bytes).  TODO(RE): unsure what the tables hold. */
void ReadTable_004EC466(void *f) { read_table(f, &P11_00b5a8e8, P11_00bf1c40, 0x42); }
void ReadTable_004EC49A(void *f) { read_table(f, &P11_00b5a8ec, P11_00c1ed80, 0x2c); }
void ReadTable_004EC522(void *f) { read_table(f, &P11_00b5a8e8, P11_00c12c60, 0x14); }
void ReadTable_004EC556(void *f) { read_table(f, &P11_00b5a8ec, P11_00c1cd20, 8); }

/* FreeBuffer_004F30E6 — Game.exe 004f30e6.  Frees the buffer 00b31efc (if any) and clears 00c823d0. */
void FreeBuffer_004F30E6(void) {
  if (P11_00b31efc != 0) Call004D8F30((uint32_t)P11_00b31efc);
  P11_00b31efc = 0; P11_00c823d0 = 0;
}

/* ResolveTable_004FE830 — Game.exe 004fe830.  For each 5-word entry of 00572b40 (until word 1 is 0) resolves the
   name in word 1 to its model value (004ec8a8 = P20_FindNameValue) into word 0. */
void ResolveTable_004FE830(void) {
  for (uint32_t *p = &P11_00572b40[0]; p[1] != 0; p += 5) *p = Call004EC8A8(p[1]);
}

/* BackOrDirector_005103C4 — Game.exe 005103c4.  Back from the pause menu: unpause (0050e940(0)), or in the replay
   director (00d11934) switch the director to mode 0xf. */
void BackOrDirector_005103C4(void) {
  if (P11_00d11934 == 0) G6Call0050E940(0); else SetDirectorMode(0xf, 0, 0);
}

/* SwitchPanel_005104B9 / 0051066A / 0051069E — Game.exe addresses as named.  Open a pause-menu sub-panel
   (menu tables 00575370 / 00574f08 / 00575088), remembering the previous one, and build it. */
void SwitchPanel_005104B9(void) {
  P11_00b5a734 = P11_00b5a730; P11_00575554 = P11_00575550;
  P11_00b5a730 = (int32_t)0x00575370u; G00B5A730 = P11_00b5a730; P11_00575550 = 1;   /* v1.62: адрес .data меню; псевдоним G00B5A730 */
  Call00510784();
}

void SwitchPanel_0051066A(void) {
  P11_00b5a734 = P11_00b5a730; P11_00575554 = P11_00575550;
  P11_00b5a730 = (int32_t)0x00574f08u; G00B5A730 = P11_00b5a730; P11_00575550 = 1;   /* v1.62: адрес .data меню; псевдоним G00B5A730 */
  Call0050F7B2();
}

void SwitchPanel_0051069E(void) {
  P11_00b5a734 = P11_00b5a730; P11_00575554 = P11_00575550;
  P11_00b5a730 = (int32_t)0x00575088u; G00B5A730 = P11_00b5a730; P11_00575550 = 1;   /* v1.62: адрес .data меню; псевдоним G00B5A730 */
  Call0050FAB0();
}

/* ResetDirector_00522306 — Game.exe 00522306.  Resets the replay director (004c64bd, 004c372a, mode 0). */
void ResetDirector_00522306(void) {
  Call004C64BD(); Call004C372A(); SetDirectorMode(0, 0, 0);
}

/* InitChannels_0052436A — Game.exe 0052436a.  Resets the 20 sound channels (0052434a). */
void InitChannels_0052436A(void) {
  for (int32_t i = 0; i < 0x14; i++) Call0052434A(i);
}

/* LoadFsin_00525E50 — Game.exe 00525e50.  Loads FSIN.DAT (the 4096-entry sine table) into 00b94280 and converts it to
   floats at 00b98280.  TODO(RE): exact conversion of 005283b5 not checked. */
void LoadFsin_00525E50(void) {
  Call004D303A(ADDR(P11_00579710), ADDR(P11_00b94280));
  Call005283B5(ADDR(P11_00b98280), ADDR(P11_00b94280), 0x1000);
}

/* InitXform_005263FE — Game.exe 005263fe.  Builds the view matrix from the camera angles (00b1c268..) and its
   transpose.  Native: uses the real objects P44_ViewMat / P59_Ang* / P44_ViewMatT (v2.13, see note). */
void InitXform_005263FE(void) {
#ifdef RE_HOOK_BUILD
  Call005261AD(ADDR(P11_011f4080), ADDR(P11_00b1c268));
  Call00528461(ADDR(P11_011f4080), ADDR(P11_011effa0));
#else
  /* v2.13: однобайтовые псевдонимы P11_* вне образа (selftest) — отдельные объекты по 1 байту, а матрица 3x3/три угла
     писались за их границы (ASan: global-buffer-overflow; на macOS — порча соседних глобалов, free(0x27) в P31_ReleaseDirectDraw).
     Те же адреса 011f4080/00b1c268/011effa0 — настоящие объекты P44_ViewMat / P59_AngA..C / P44_ViewMatT (в игре — образ). */
  int16_t ang[3] = { (int16_t)P59_AngA, (int16_t)P59_AngB, (int16_t)P59_AngC };
  P43_EulerMatrix((float *)&P44_ViewMat, ang);
  P44_Transpose((const float *)&P44_ViewMat, (float *)&P44_ViewMatT);
#endif
}

/* InitVec_00526582 — Game.exe 00526582.  Sets the vector 005507d0 to (0, 0, 1), selects the view matrix and
   transforms it (00528982). */
void InitVec_00526582(void) {
  P11_005507d0 = 0; P11_005507d4 = 0; P11_005507d8 = 0; /* float 1.0f set below */
  { uint32_t one = 0x3f800000; memcpy(&P11_005507d8, &one, 4); }
  P11_00bdc28c = ADDR(P11_011f4080);
#ifndef RE_HOOK_BUILD
  P44_MatPtr = (float *)P44_ViewMat;   /* native: 00bdc28c — родной указатель P44_MatPtr (его читает P44_Xform 00528982), 32-битный P11_00bdc28c — отдельный объект */
#endif
  Call00528982(ADDR(P11_005507d0));
}

/* RoundSet_004BF400 — Game.exe 004bf400.  Rounds (a, b) to integers and sets the text cursor there (004d94b7). */
void RoundSet_004BF400(float a, float b) {
  P11_00ba52d0 = (int32_t)lrintf(b);
  int32_t t = P11_00ba52d0;
  P11_00ba52d0 = (int32_t)lrintf(a);
  Call004D94B7((uint32_t)P11_00ba52d0, (uint32_t)t);
}

/* StepUp_0051010C / StepDown_00510145 — Game.exe 0051010c / 00510145.  Pause-menu slider for the far plane
   01270c24 (draw distance): +/- step 0054604c within 0054602c..00546028, then redraw the menu. */
void StepUp_0051010C(void) {
  if (P11_01270c24 < P11_00546028) { P11_01270c24 = P11_01270c24 + P11_0054604c; P11_00575ef8 = 4; Call0050FBF4(); }
}

void StepDown_00510145(void) {
  if (P11_0054602c < P11_01270c24) { P11_01270c24 = P11_01270c24 - P11_0054604c; P11_00575ef8 = 4; Call0050FBF4(); }
}

/* StepUp_0051017E / StepDown_005101B7 — Game.exe 0051017e / 005101b7.  Same slider for 0125f3f8.
   TODO(RE): unsure which setting 0125f3f8 is (fog distance?). */
void StepUp_0051017E(void) {
  if (P11_0125f3f8 < P11_00546028) { P11_0125f3f8 = P11_0125f3f8 + P11_0054604c; P11_00575ef8 = 4; Call0050FBF4(); }
}

void StepDown_005101B7(void) {
  if (P11_0054602c < P11_0125f3f8) { P11_0125f3f8 = P11_0125f3f8 - P11_0054604c; P11_00575ef8 = 4; Call0050FBF4(); }
}

/* Zoom_00425E9E — Game.exe 00425e9e.  Decreases 0125f3e0 by 00546054 while above 00546080, re-runs the view setup
   and schedules two more updates (01270c38 = 2, see P47_GlideSwap).  TODO(RE): unsure what 0125f3e0 is (FOV?). */
void Zoom_00425E9E(void) {
  if (P11_00546080 < P11_0125f3e0) { P11_0125f3e0 = P11_0125f3e0 - P11_00546054; Call00425B12(0, 0, 1); P11_01270c38 = 2; }
}
