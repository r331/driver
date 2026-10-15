#include "ported11.h"
#include "ported29.h"
GAME_VAR_DEF(int32_t, P11_00b87e7c, 0x00b87e7c)
GAME_VAR_DEF(int32_t, P11_005c6760, 0x005c6760)
GAME_VAR_DEF(int32_t, P11_01271060, 0x01271060)
GAME_VAR_DEF(int32_t, P11_00b87e38, 0x00b87e38)
GAME_VAR_DEF(int32_t, P11_00b20360, 0x00b20360)
GAME_VAR_DEF(int32_t, P11_00c81494, 0x00c81494)
GAME_VAR_DEF(int32_t, P11_00ba52d0, 0x00ba52d0)
GAME_VAR_DEF(int32_t, P11_00b31efc, 0x00b31efc)
GAME_VAR_DEF(int32_t, P11_00c823d0, 0x00c823d0)
GAME_VAR_DEF(int32_t, P11_00d11934, 0x00d11934)
GAME_VAR_DEF(int32_t, P11_00b5a734, 0x00b5a734)
GAME_VAR_DEF(int32_t, P11_00b5a730, 0x00b5a730)
GAME_VAR_DEF(int32_t, P11_00575554, 0x00575554)
GAME_VAR_DEF(int32_t, P11_00575550, 0x00575550)
GAME_VAR_DEF(int32_t, P11_00bdc28c, 0x00bdc28c)
GAME_VAR_DEF(int32_t, P11_005507d0, 0x005507d0)
GAME_VAR_DEF(int32_t, P11_005507d4, 0x005507d4)
GAME_VAR_DEF(int32_t, P11_005507d8, 0x005507d8)
GAME_VAR_DEF(int32_t, P11_00b5a8e8, 0x00b5a8e8)
GAME_VAR_DEF(int32_t, P11_00b5a8ec, 0x00b5a8ec)
GAME_VAR_DEF(int32_t, P11_01270c38, 0x01270c38)
GAME_VAR_DEF(int32_t, P11_00575ef8, 0x00575ef8)
GAME_VAR_DEF(float, P11_01270c24, 0x01270c24)
GAME_VAR_DEF(float, P11_01270c28, 0x01270c28)
GAME_VAR_DEF(float, P11_0125f3e0, 0x0125f3e0)
GAME_VAR_DEF(float, P11_0125f3f8, 0x0125f3f8)
GAME_VAR_DEF(float, P11_00546028, 0x00546028)
GAME_VAR_DEF(float, P11_0054602c, 0x0054602c)
GAME_VAR_DEF(float, P11_0054604c, 0x0054604c)
GAME_VAR_DEF(float, P11_00546054, 0x00546054)
GAME_VAR_DEF(float, P11_00546080, 0x00546080)
GAME_VAR_DEF(p11_s16arr, P11_00c1ed8a, 0x00c1ed8a)
GAME_VAR_DEF(p11_u32arr, P11_00572b40, 0x00572b40)
GAME_VAR_DEF(uint8_t, P11_0057b740, 0x0057b740)
GAME_VAR_DEF(uint8_t, P11_005d592e, 0x005d592e)
GAME_VAR_DEF(uint8_t, P11_005d57ae, 0x005d57ae)
GAME_VAR_DEF(p11_slots_t, P11_0125f420, 0x0125f420)
GAME_VAR_DEF(uint8_t, P11_00bf1c40, 0x00bf1c40)
GAME_VAR_DEF(uint8_t, P11_00c1ed80, 0x00c1ed80)
GAME_VAR_DEF(uint8_t, P11_00c12c60, 0x00c12c60)
GAME_VAR_DEF(uint8_t, P11_00c1cd20, 0x00c1cd20)
GAME_VAR_DEF(uint8_t, P11_00c80c60, 0x00c80c60)
GAME_VAR_DEF(uint8_t, P11_00552e18, 0x00552e18)
GAME_VAR_DEF(uint8_t, P11_00579710, 0x00579710)
GAME_VAR_DEF(uint8_t, P11_00b94280, 0x00b94280)
GAME_VAR_DEF(uint8_t, P11_00b98280, 0x00b98280)
GAME_VAR_DEF(uint8_t, P11_011f4080, 0x011f4080)
GAME_VAR_DEF(uint8_t, P11_00b1c268, 0x00b1c268)
GAME_VAR_DEF(uint8_t, P11_011effa0, 0x011effa0)
GAME_VAR_DEF(uint8_t, P11_00575370, 0x00575370)
GAME_VAR_DEF(uint8_t, P11_00574f08, 0x00574f08)
GAME_VAR_DEF(uint8_t, P11_00575088, 0x00575088)
void SndHelper_00407D97(uint8_t a, uint8_t b) {
  if (P11_00b87e7c == 0) Call004BF910(ADDR(P11_0057b740), a, b);
}

void SndHelper_00407D56(int32_t x, int32_t y, uint32_t p3, uint32_t p4, uint32_t p5) {
  (void)p3; Call005291ED(ADDR(P11_0057b740) + (uint32_t)(y * 0x280) + (uint32_t)x, p4 & 0xfffffffcu, p5, (uint32_t)P11_005c6760);
}

void CopySlots_0040AA82(uint32_t n) {
  for (int32_t i = 0; i < 10; i++)
    Call0052B650(ADDR(P11_005d592e) + i*8 + (n&0xff)*0x806, ADDR(P11_005d57ae) + i*8 + (n&0xff)*0x806, 8);
}

uint32_t MenuAction_0041645B(void) {
  MenuAction40CD17(); P11_01271060 = 10; P11_00b87e38 = 200; UiCall0040C455(1, 0); return 1;
}

uint32_t MenuAction_004164B2(void) {
  MenuAction40CD17(); P11_01271060 = 10; P11_00b87e38 = 0xfa; UiCall0040C455(1, 0); return 1;
}

uint32_t GetRect_0048F34C(int32_t i) {
  const int16_t *p = &P11_00c1ed8a[i * 0x16];
  return Call0048F3B4(p[0], p[4], p[8], p[12]);
}

void DrawFrame_004A9DDC(int32_t x, int32_t y, int32_t w, int32_t h) {
  Call004A9F45(x - 6, y - 6, w + 0xc, h + 0xc, ADDR(P11_00552e18));
}

uint32_t ScriptReadShort3_004D02C6(void) {
  P10_ScriptPtr += 2;
  for (int i = 0; i < 3; i++) { memcpy(P10_ScriptCtx + 0x10 + i*2, P10_ScriptPtr, 2); P10_ScriptPtr += 2; }
  return 1;
}

uint32_t ScriptReadVec3_004D033F(void) {
  P10_ScriptPtr += 2;
  for (int i = 0; i < 3; i++) { memcpy(P10_ScriptCtx + 0x18 + i*4, P10_ScriptPtr, 4); P10_ScriptPtr += 4; }
  { uint16_t f; memcpy(&f, P10_ScriptCtx + 0x48, 2); f = (uint16_t)((f & 0xff7d) | 1); memcpy(P10_ScriptCtx + 0x48, &f, 2); }
  return 1;
}

void TryStartTrack_004D611B(uint32_t a) {
  if (Call00524473(0xf) == 0) { UiCall00523E50((int32_t)a, 0xf, -1); P11_00b20360 = 0; }
}

void DrawBanner_004F5D98(void) {
  if (0 < P11_00c81494) DrawSprite(0x140, 0x50, ADDR(P11_00c80c60), 0, 1, 0xff, 0xff, 0xff);
}

void ReadBlocks_004EB7CF(uint32_t f) {
  for (int32_t i = 0; i < 0x400; i++) Call004D9596(ADDR(P11_0125f420) + i*0x46, 0x46, 1, f);
}

void ReadTable_004EC466(uint32_t f) {
  Call004D9596(ADDR(P11_00b5a8e8), 1, 4, f);
  Call004D9596(ADDR(P11_00bf1c40), (uint32_t)P11_00b5a8e8, 0x42, f);
}

void ReadTable_004EC49A(uint32_t f) {
  Call004D9596(ADDR(P11_00b5a8ec), 1, 4, f);
  Call004D9596(ADDR(P11_00c1ed80), (uint32_t)P11_00b5a8ec, 0x2c, f);
}

void ReadTable_004EC522(uint32_t f) {
  Call004D9596(ADDR(P11_00b5a8e8), 1, 4, f);
  Call004D9596(ADDR(P11_00c12c60), (uint32_t)P11_00b5a8e8, 0x14, f);
}

void ReadTable_004EC556(uint32_t f) {
  Call004D9596(ADDR(P11_00b5a8ec), 1, 4, f);
  Call004D9596(ADDR(P11_00c1cd20), (uint32_t)P11_00b5a8ec, 8, f);
}

void FreeBuffer_004F30E6(void) {
  if (P11_00b31efc != 0) Call004D8F30((uint32_t)P11_00b31efc);
  P11_00b31efc = 0; P11_00c823d0 = 0;
}

void ResolveTable_004FE830(void) {
  for (uint32_t *p = &P11_00572b40[0]; p[1] != 0; p += 5) *p = Call004EC8A8(p[1]);
}

void BackOrDirector_005103C4(void) {
  if (P11_00d11934 == 0) G6Call0050E940(0); else SetDirectorMode(0xf, 0, 0);
}

void SwitchPanel_005104B9(void) {
  P11_00b5a734 = P11_00b5a730; P11_00575554 = P11_00575550;
  P11_00b5a730 = (uint32_t)ADDR(P11_00575370); P11_00575550 = 1;
  Call00510784();
}

void SwitchPanel_0051066A(void) {
  P11_00b5a734 = P11_00b5a730; P11_00575554 = P11_00575550;
  P11_00b5a730 = (uint32_t)ADDR(P11_00574f08); P11_00575550 = 1;
  Call0050F7B2();
}

void SwitchPanel_0051069E(void) {
  P11_00b5a734 = P11_00b5a730; P11_00575554 = P11_00575550;
  P11_00b5a730 = (uint32_t)ADDR(P11_00575088); P11_00575550 = 1;
  Call0050FAB0();
}

void ResetDirector_00522306(void) {
  Call004C64BD(); Call004C372A(); SetDirectorMode(0, 0, 0);
}

void InitChannels_0052436A(void) {
  for (int32_t i = 0; i < 0x14; i++) Call0052434A(i);
}

void LoadFsin_00525E50(void) {
  Call004D303A(ADDR(P11_00579710), ADDR(P11_00b94280));
  Call005283B5(ADDR(P11_00b98280), ADDR(P11_00b94280), 0x1000);
}

void InitXform_005263FE(void) {
  Call005261AD(ADDR(P11_011f4080), ADDR(P11_00b1c268));
  Call00528461(ADDR(P11_011f4080), ADDR(P11_011effa0));
}

void InitVec_00526582(void) {
  P11_005507d0 = 0; P11_005507d4 = 0; P11_005507d8 = 0; /* float 1.0f set below */
  { uint32_t one = 0x3f800000; memcpy(&P11_005507d8, &one, 4); }
  P11_00bdc28c = ADDR(P11_011f4080);
  Call00528982(ADDR(P11_005507d0));
}

void RoundSet_004BF400(float a, float b) {
  P11_00ba52d0 = (int32_t)lrintf(b);
  int32_t t = P11_00ba52d0;
  P11_00ba52d0 = (int32_t)lrintf(a);
  Call004D94B7((uint32_t)P11_00ba52d0, (uint32_t)t);
}

void StepUp_0051010C(void) {
  if (P11_01270c24 < P11_00546028) { P11_01270c24 = P11_01270c24 + P11_0054604c; P11_00575ef8 = 4; Call0050FBF4(); }
}

void StepDown_00510145(void) {
  if (P11_0054602c < P11_01270c24) { P11_01270c24 = P11_01270c24 - P11_0054604c; P11_00575ef8 = 4; Call0050FBF4(); }
}

void StepUp_0051017E(void) {
  if (P11_0125f3f8 < P11_00546028) { P11_0125f3f8 = P11_0125f3f8 + P11_0054604c; P11_00575ef8 = 4; Call0050FBF4(); }
}

void StepDown_005101B7(void) {
  if (P11_0054602c < P11_0125f3f8) { P11_0125f3f8 = P11_0125f3f8 - P11_0054604c; P11_00575ef8 = 4; Call0050FBF4(); }
}

void Zoom_00425E9E(void) {
  if (P11_00546080 < P11_0125f3e0) { P11_0125f3e0 = P11_0125f3e0 - P11_00546054; Call00425B12(0, 0, 1); P11_01270c38 = 2; }
}
