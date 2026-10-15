#include "ported12.h"
#include "ported40.h"
GAME_VAR_DEF(int32_t,P12_00bdfa40,0x00bdfa40)
GAME_VAR_DEF(int32_t,P12_00b87ef8,0x00b87ef8)
GAME_VAR_DEF(int32_t,P12_005f7e5c,0x005f7e5c)
GAME_VAR_DEF(int32_t,P12_005f7e60,0x005f7e60)
GAME_VAR_DEF(int32_t,P12_00575f50,0x00575f50)
GAME_VAR_DEF(int32_t,P12_00b87e58,0x00b87e58)
GAME_VAR_DEF(int32_t,P12_00b87e5c,0x00b87e5c)
GAME_VAR_DEF(float,P12_00b32980,0x00b32980)
GAME_VAR_DEF(float,P12_00b3297c,0x00b3297c)
GAME_VAR_DEF(float,P12_00546088,0x00546088)
GAME_VAR_DEF(float,P12_00546084,0x00546084)
GAME_VAR_DEF(p12_00ba53a0_t,P12_00ba53a0,0x00ba53a0)
GAME_VAR_DEF(p12_01144340_t,P12_01144340,0x01144340)
GAME_VAR_DEF(p12_011443e0_t,P12_011443e0,0x011443e0)
GAME_VAR_DEF(p12_0112da00_t,P12_0112da00,0x0112da00)
GAME_VAR_DEF(p12_00c5678c_t,P12_00c5678c,0x00c5678c)
GAME_VAR_DEF(p12_00c594a0_t,P12_00c594a0,0x00c594a0)
GAME_VAR_DEF(int32_t,P12_00bdf980,0x00bdf980)
GAME_VAR_DEF(int32_t,P12_00bde728,0x00bde728)
GAME_VAR_DEF(int32_t,P12_00bde764,0x00bde764)
GAME_VAR_DEF(int32_t,P12_00bde760,0x00bde760)
GAME_VAR_DEF(int32_t,P12_00b5a898,0x00b5a898)
GAME_VAR_DEF(p12_0054b010_t,P12_0054b010,0x0054b010)
GAME_VAR_DEF(p12_005fe7a8_t,P12_005fe7a8,0x005fe7a8)
GAME_VAR_DEF(p12_005fe884_t,P12_005fe884,0x005fe884)
GAME_VAR_DEF(int32_t,P12_00d17b90,0x00d17b90)
GAME_VAR_DEF(int32_t,P12_005feb60,0x005feb60)
GAME_VAR_DEF(p12_005febbc_t,P12_005febbc,0x005febbc)
GAME_VAR_DEF(int32_t,P12_005feef0,0x005feef0)
GAME_VAR_DEF(int32_t,P12_005feef4,0x005feef4)
GAME_VAR_DEF(int32_t,P12_005feef8,0x005feef8)
GAME_VAR_DEF(p12_005fee40_t,P12_005fee40,0x005fee40)
GAME_VAR_DEF(p12_005fee60_t,P12_005fee60,0x005fee60)
GAME_VAR_DEF(int32_t,P12_01252b74,0x01252b74)
GAME_VAR_DEF(p12_01252aa0_t,P12_01252aa0,0x01252aa0)
GAME_VAR_DEF(int32_t,P12_00cff9ac,0x00cff9ac)
GAME_VAR_DEF(int32_t,P12_00b1c3f0,0x00b1c3f0)
GAME_VAR_DEF(int32_t,P12_00b1c3dc,0x00b1c3dc)
GAME_VAR_DEF(p12_01146f20_t,P12_01146f20,0x01146f20)
GAME_VAR_DEF(p12_00b1c3f4_t,P12_00b1c3f4,0x00b1c3f4)
GAME_VAR_DEF(p12_01145a60_t,P12_01145a60,0x01145a60)
GAME_VAR_DEF(int32_t,P12_011237b8,0x011237b8)
GAME_VAR_DEF(p12_0110b260_t,P12_0110b260,0x0110b260)
GAME_VAR_DEF(p12_00574530_t,P12_00574530,0x00574530)
GAME_VAR_DEF(p12_00c7d800_t,P12_00c7d800,0x00c7d800)
GAME_VAR_DEF(int32_t,P12_00c7d828,0x00c7d828)
GAME_VAR_DEF(int32_t,P12_00c7d834,0x00c7d834)
GAME_VAR_DEF(int32_t,P12_00c7d840,0x00c7d840)
GAME_VAR_DEF(int32_t,P12_00c7d84c,0x00c7d84c)
GAME_VAR_DEF(int32_t,P12_00c595a0,0x00c595a0)
GAME_VAR_DEF(int32_t,P12_00c55034,0x00c55034)
GAME_VAR_DEF(int32_t,P12_00d044d0,0x00d044d0)
GAME_VAR_DEF(int32_t,P12_00c821a0,0x00c821a0)
GAME_VAR_DEF(int32_t,P12_00b52a38,0x00b52a38)
GAME_VAR_DEF(int32_t,P12_00b32970,0x00b32970)
GAME_VAR_DEF(int32_t,P12_00b93ce0,0x00b93ce0)
GAME_VAR_DEF(p12_00576688_t,P12_00576688,0x00576688)
GAME_VAR_DEF(float,P12_00c808d0,0x00c808d0)

static int32_t rd32(const uint8_t *p) { int32_t v; memcpy(&v, p, 4); return v; }
static void wr32(uint8_t *p, int32_t v) { memcpy(p, &v, 4); }

int32_t P12_Fn004046C8(void) {
  int32_t r;
  g_00bdfa40 = g_0057b56c + 1;
  MenuAction40CD17();
  if (g_00b87e38 == 0x30) { UiCall0040C455(1, 0); r = 1; }
  else { r = R12_4082A0(); if (r == 0) M12(0x549a30, 0x549a58); }
  return r;
}
uint32_t P12_Fn00404F70(void) {
  MenuAction40CD17(); g_00b87e38 = 0x105; g_01271060 = 8;
  UiCall0040C455(1, 0); M12(0x549ae8, 0x549b00); return 0;
}
uint32_t P12_Fn00404FAE(void) {
  MenuAction40CD17(); g_00b87ef8 = 1; g_005f7e5c = 1;
  Call00517D58(0x549c68); UiCall0040C455(1, 1);
  g_005f7e5c = 0; g_00b87ef8 = 0; return 1;
}
uint32_t P12_Fn004152A7(void) {
  g_00575f50 ^= 1;
  G6Call00523628(); Call00523595();
  Call005233BE(g_00b87e58, g_00b87e5c, g_00575f50);
  if (g_00b87eec == 0) { Call00524496(0x54ded4, 0); Call0052360D(0); }
  else { Call00524496(0x54dec8, 0); Call0052360D(5); }
  Call00414D1F(); return 0;
}
int32_t P12_Fn00407563(void) {
  int32_t r;
  if (g_00b87eec == 0) MenuAction40CD17();
  r = (g_0057b72c == 0) ? R12_410C30() : R12_40FA60();
  if (r == 0 && g_00b87eec == 0) M12(0x549f60, 0x549f78);
  return r;
}
#define MENUWRAP(NAME, CALLEE, SETV, A, B) \
  int32_t NAME(void) { int32_t r; MenuAction40CD17(); SETV; r = CALLEE(); if (r == 0) M12(A, B); return r; }
MENUWRAP(P12_Fn0040A45B, R12_413D70, g_01271060 = 6, 0x54a818, 0x54a830)
MENUWRAP(P12_Fn0040A4AD, R12_413D70, g_01271060 = 0xb, 0x54a818, 0x54a830)
MENUWRAP(P12_Fn00412A4B, R12_413B00, (void)0, 0x54cb98, 0x54cc50)
MENUWRAP(P12_Fn00412AB9, R12_4134A0, (void)0, 0x54cb98, 0x54cc50)
MENUWRAP(P12_Fn00412B27, R12_413890, (void)0, 0x54cb98, 0x54cc50)
MENUWRAP(P12_Fn00412B95, R12_416390, (void)0, 0x54cb98, 0x54cc50)
MENUWRAP(P12_Fn00412C03, R12_40A540, (void)0, 0x54cb98, 0x54cc50)
MENUWRAP(P12_Fn00412C71, R12_404850, (void)0, 0x54cb98, 0x54cc50)
MENUWRAP(P12_Fn00412CDF, R12_415EC0, (void)0, 0x54cb98, 0x54cc50)
MENUWRAP(P12_Fn00412D4D, R12_413610, (void)0, 0x54cb98, 0x54cc50)
MENUWRAP(P12_Fn00413596, R12_411FD0, (void)0, 0x54d0e0, 0x54d0f8)
MENUWRAP(P12_Fn004136EC, R12_408770, (void)0, 0x54d188, 0x54d1a0)
MENUWRAP(P12_Fn0041373A, R12_414C30, (void)0, 0x54d188, 0x54d1a0)
MENUWRAP(P12_Fn00413788, R12_407160, (void)0, 0x54d188, 0x54d1a0)
MENUWRAP(P12_Fn004137D6, R12_40E870, (void)0, 0x54d188, 0x54d1a0)
MENUWRAP(P12_Fn00413973, R12_4123D0, (void)0, 0x54d278, 0x54d290)
MENUWRAP(P12_Fn00413CBF, R12_40F2D0, (void)0, 0x54d390, 0x54d3a8)

void P12_Fn004129DF(int32_t p) {
  MenuAction40CD17(); UiCall00408600(p);
  if (p == -1) M12(0x54cb98, 0x54cc50);
}
void P12_Fn004183F7(uint32_t a, uint32_t b) {
  Call004184DE(0x3f800000u);
  while (g_005fea60 != 0) { Call00522323(); Call004E3391(); UiCall004184F5(); Call0041846C(a, b); }
}
void P12_Fn00418433(uint32_t a, uint32_t b) {
  Call004184DE(0);
  while (g_005fea60 != 0) { Call00522323(); Call004E3391(); UiCall004184F5(); Call0041846C(a, b); }
}
void P12_Fn0050229C(void) {
  if (g_00b5a778 == 0) {
    g_00b32980 = g_00b32980 + g_00546054;
    if (g_00546020 <= g_00b32980) g_00b32980 = -1.0f;
  } else {
    g_00b3297c = g_00b3297c + g_00546054;
    if (g_00546020 <= g_00b3297c) g_00b3297c = -1.0f;
  }
}
void P12_Fn00526427(void) {
  for (int32_t i = 0; i < 0xdbba; i++) {
    if (i == 0) g_00ba53a0[0] = 0;
    else g_00ba53a0[i] = g_0125f3e0 / (float)i;
  }
}
void P12_Fn00496505(void) {
  for (int32_t i = 0; i < g_01144284; i++) Call00493ECE((int32_t)g_01144340[i]);
  g_01145934 = 0; g_011426f8 = -1; g_01144284 = 0; g_0113a6c0 = 0;
}
void P12_Fn00491360(void) {
  for (int32_t i = 0; i < 0x40; i++) {
    const uint8_t *p = &g_011443e0[i * 0x54];
    if (p[1] != 0 && (p[2] == 1 || p[5] != 0)) G6Call00500E1D(p[0] + 1);
  }
}
void P12_Fn0048EBC8(void) {
  for (int32_t i = 0; i < 8; i++) {
    const uint32_t *p = &g_0112da00[i * 0x336];
    if (p[0x32d] != 0 && p[0x333] != 0 && p[0x331] == 0) Call0051551E((int32_t)p[0x334]);
  }
}
void P12_Fn00511FB8(void) {
  for (int32_t i = 0; i < 0x40; i++)
    if ((g_00c5678c[i * 0x2d] & 0x10) != 0)
      Call0051200F(0x00c56780u + (uint32_t)g_00c594a0[i] * 0x5a);
}
void P12_Fn005229F0(void) {
  g_00bdf980 = 0; g_00bde728 = 0; g_00bde764 = 0; g_00bde760 = 0;
  Call0048DB65(0x00bde740, 0x20); Call0048DB65(0x00bde680, 0xa8); Call0048DB65(0x00bde780, 0x1200);
}
void P12_Fn005188EC(void) {
  Call005283B5(0x00c54d20, 0x00d077c0, 0x148);
  Call005283B5(0x00c4da60, 0x00d06a20, 0x34);
  Call005283B5(0x00c4da00, 0x00d0de00, 0x34);
  Call005283B5(0x00c4d9c0, 0x00d0eb80, 0x34);
  g_00b5a898 = 0; Call005186CE();
}
uint32_t P12_Fn0040F09C(void) {
  for (uint32_t i = 0; i < 0x100; i++)
    if (g_0054b010[i] != 0 && IsKeyDown((int)(i & 0xff)) != 0) return i;
  return 0;
}
uint32_t P12_Fn004120AF(void) {
  if (g_005fe7a8[g_005fe84c] != 0) {
    if (R12_405CB4(g_005fe84c) != 0) { UiCall0040C480(1); return 1; }
    Call004122C4();
  }
  return 0;
}
uint32_t P12_Fn004124AF(void) {
  if (g_005fe884[g_005fe928] != 0) {
    if (R12_405F2E(g_005fe928) != 0) {
      MenuAction40CD17(); g_00d17b90 = 1; UiCall0040C455(1, 1); g_00d17b90 = 0; return 1;
    }
    Call004126DF();
  }
  return 0;
}
void P12_Fn0040C813(uint32_t a, int32_t b) {
  Call0040C610(a, 0);
  while (R12_4D97E9() != 0) {}
  Call004086B4();
  do { if (b <= g_005d577c) break; } while (R12_4D97E9() == 0);
  Call004086EA(); Call004D78F3(0); g_005f7e60 = 1;
}
void P12_Fn0040DA56(uint32_t a) {
  int32_t n = 0;
  P40_ResetTexMem();
  for (int32_t y = 0; y < 0x1e0; y += 0x100)
    for (int32_t x = 0; x < 0x280; x += 0x100) {
      uint32_t v = R12_40DAE1(a, x, y);
      P40_UploadSlot(n, (int32_t)v); n++;
    }
}
void P12_Fn0041A8CD(void) {
  if (g_005fea98 == rd32(&g_005febbc[(g_005feb60 + 1) * 0x34]) &&
      (g_005feb60 = g_005feb60 + 1, g_005feb60 == g_005feb48 - 1)) {
    Call0041A1F9(g_005feb00); g_005fea54 = 0; g_005feda0 = 0;
  } else {
    Call0049EC01(g_005fea98, 0x005feb90u + (uint32_t)g_005feb60 * 0xd);
  }
}
uint32_t P12_Fn0041AECF(void) {
  UiCall0041AF29(g_005feeec * 2 + 1);
  g_005feef0 = 1;
  if (g_005fee40[g_005feeec] == 0) g_005feef8 = 0;
  else g_005feef8 = (int32_t)strlen((const char *)&g_005fee60[g_005feeec * 0x11]);
  return 0;
}
void P12_Fn0041AF85(void) {
  g_005feef0 = 0; g_005feef4 = 0; g_005feef8 = 0;
  Call00405D60(g_005feeec, 0x005fee60u + (uint32_t)g_005feeec * 0x11);
  Call0041AFCA();
}
int32_t P12_Fn00426580(int32_t p) {
  int32_t old = g_01252b74;
  if (p == -1) g_01252b74 = -1;
  else if (p != g_01252b74 && g_01252aa0[p] != 0) {
    Call00424921(0, 2, 0x01252be0u + (uint32_t)p * 0x400, p);
    g_01252b74 = p;
  }
  return old;
}
void P12_Fn00425EE0(void) {
  if (g_0125f3e0 < g_00546020) {
    g_0125f3e0 = g_0125f3e0 + g_00546054;
    if (g_00546088 < g_0125f3e0 && g_0125f3e0 < g_00546084) g_0125f3e0 = 1.0f;
    Call00425B12(0, 0, 1);
    g_01270c38 = 2;
  }
}
void P12_Fn00489ED6(void) {
  if (g_00cff9ac != g_00b1c3f0) {
    g_00b1c3dc = 0;
    for (int32_t i = 0; i < 0x40; i++) g_01146f20[i * 0x1c] &= 0xfd;
    Call0048A525(g_00cff9ac);
    if (g_00b1c3dc != 0) P12_Fn0048A627();
  }
  g_00b1c3f0 = g_00cff9ac;
}
void P12_Fn0048A627(void) {
  for (int32_t i = 0; i < g_00b1c3dc; i++) {
    int32_t k = g_00b1c3f4[i];
    g_01145a60[k * 0x10] &= 0xef;
    Call0048A68E(k);
  }
  g_00b1c3dc = 0;
}
void P12_Fn0048A46B(int32_t p, int32_t v) {
  if (g_01145a60[p * 0x10 + 1] != 0xff) {
    uint32_t u = g_01145a60[p * 0x10 + 1];
    wr32(&g_01145a60[p * 0x10 + 4], v);
    wr32(&g_01146f20[u * 0x1c + 0x18], v);
    Call004248C6(0, rd32(&g_01146f20[u * 0x1c + 4]), 3, 0x01146f28u + u * 0x1c, p);
  }
}
void P12_Fn004B9933(void) {
  if (g_011173c8 != 0) {
    for (int32_t i = 0; i < 200; i++) {
      uint16_t f; memcpy(&f, &g_0110b260[i * 0x3c + 0x22], 2);
      if ((f & 2) != 0) Call004B998B(0x0110b260u + (uint32_t)i * 0x3c);
    }
  }
}
void P12_Fn004AAE34(void) {
  if (g_00b5a778 == 0) {
    if (g_00553850 != 0) Call004C0C6F(0);
    if ((g_00d118c0 & 1) == 0) {
      g_00bdc28c = 0x011effa0;
      Call004BA31B(); Call004B9AEC(); Call004B9D79(); P12_Fn004B9933();
      g_011237b8 = (g_011237b8 + 1) & 0xf;
      Call004911D9();
    }
  }
}
void P12_Fn0050E963(void) {
  if (g_00b5a76c == 0) {
    if (g_00b5a778 != 0 || g_00b5a770 != 0) Call0050F289();
  } else if (g_00b5a778 == 0 || g_00b5a770 != 0) Call0050EE00();
  g_00b5a770 = 0;
}
void P12_Fn0050C010(void) {
  for (int32_t i = 0; i < 8; i++) g_00c7d800[i] = g_00574530[i * 2] + g_00574530[i * 2 + 1] * 0x37;
  g_00c7d828 = 0x00c7d82c; g_00c7d834 = 0x00c7d838; g_00c7d840 = 0x00c7d844;
  g_00c7d84c = 0; g_00c595a0 = 0;
}
void P12_Fn00516E76(void) {
  g_00c55034 = R12_40A8B0(0x00575a28, 0, -1, 5, 0x18);
  R12_40A8B0(0x00575a30, 1, -1, 5, 0x18);
  CopySlots_0040AA82(1);
}
void P12_Fn004DC8EA(void) {
  Call004DAA36(0x00d077c0u + (uint32_t)g_00d11878 * 0x52, 0x00d077d8u + (uint32_t)g_00d11878 * 0x52);
}
void P12_Fn004E5982(int32_t a, int32_t b, int32_t c) {
  if (c == 0 || g_00d044d0 == 0) { Call0052A910(0x00d04680, g_00c55820[a], 0); g_00d044d0 = b; }
}
void P12_Fn004F3E78(int32_t a, int32_t b, int32_t c) {
  a += 0x10; b += 0x10;
  for (int32_t i = 0; i < g_00c821a0; i++) {
    Call00527885(a, b, c, 0x00c81ba0u + (uint32_t)i * 0x14); a += 0x14; b += 0x14;
  }
}
void P12_Fn00504699(int32_t a, int32_t b) {
  for (int32_t i = 0; i < 0x80; i++) {
    Call005283B5((uint32_t)b, a, 0x100);
    a = a + 0x100 + g_00b52a38 * 2; b = b + 0x100 + g_00b32970 * 2;
  }
}
void P12_Fn00525CB7(int32_t p) {
  if (g_00b93ce0 != p && 500 < g_00d118c0 - g_00576688[p * 3 + 1]) {
    Call004D6190(g_00576688[p * 3] + 0xf000);
    g_00576688[p * 3 + 1] = g_00d118c0;
    g_00c808d0 = g_00c808d0 + (float)g_00576688[p * 3 + 2];
    g_00b93ce0 = p;
  }
}
