#include "ported62.h"
#include <stdio.h>
#include <string.h>

GAME_VAR_DEF(int32_t, P62_C82434, 0x00c82434)
GAME_VAR_DEF(int32_t, P62_C82500, 0x00c82500)
GAME_VAR_DEF(float, P62_F136C54, 0x01136c54)
GAME_VAR_DEF(int32_t, P62_I137388, 0x01137388)
GAME_VAR_DEF(int32_t, P62_I13738C, 0x0113738c)
GAME_VAR_DEF(int32_t, P62_I137390, 0x01137390)
GAME_VAR_DEF(float, P62_F252A94, 0x01252a94)
GAME_VAR_DEF(float, P62_F25F3F4, 0x0125f3f4)
GAME_VAR_DEF(float, P62_F25F404, 0x0125f404)
GAME_VAR_DEF(int32_t, P62_I270C44, 0x01270c44)
GAME_VAR_DEF(int32_t, P62_I252A80, 0x01252a80)
GAME_VAR_DEF(int32_t, P62_I252B78, 0x01252b78)
GAME_VAR_DEF(int32_t, P62_I270C48, 0x01270c48)
GAME_VAR_DEF(int32_t, P62_I252B68, 0x01252b68)
GAME_VAR_DEF(uint8_t, P62_B25F400, 0x0125f400)
GAME_VAR_DEF(int32_t, P62_I14428C, 0x0114428c)
GAME_VAR_DEF(int32_t, P62_Max, 0x0112b25c)
GAME_VAR_DEF(int32_t, P62_MapN, 0x00c1cc70)
GAME_VAR_DEF(const char *, P62_ModelNames, 0x00b1ff60)
GAME_VAR_DEF(int32_t, P62_ModelCount, 0x01134124)
GAME_VAR_DEF(int32_t, P62_NoErr, 0x00bdf9c8)
GAME_VAR_DEF(int32_t, P62_Spd, 0x00d078d0)
GAME_VAR_DEF(const char *, P62_Unit, 0x00c55ccc)
GAME_VAR_DEF(int32_t, P62_Blink, 0x00c8092c)
GAME_VAR_DEF(int32_t, P62_HudOff1, 0x00b87ea0)
GAME_VAR_DEF(int32_t, P62_HudOff2, 0x00b87e98)
GAME_VAR_DEF(int32_t, P62_Frame, 0x00d118c0)
GAME_VAR_DEF(int32_t, P62_Alt, 0x00b5a830)
GAME_VAR_DEF(int32_t, P62_Menu1271060, 0x01271060)
GAME_VAR_DEF(int32_t, P62_Menu1271064, 0x01271064)
GAME_VAR_DEF(int32_t, P62_BusyA, 0x00bdfa44)
GAME_VAR_DEF(int32_t, P62_BusyB, 0x00bdfa48)
GAME_VAR_DEF(int32_t, P62_BusyC, 0x00bdfa4c)
GAME_VAR_DEF(int32_t, P62_BusyD, 0x00bdfa50)
GAME_VAR_DEF(int32_t, P62_BusyE, 0x00bdfa58)
GAME_VAR_DEF(int32_t, P62_MapW, 0x00c1ed60)
GAME_VAR_DEF(int32_t, P62_MapH, 0x00c1cc68)
GAME_VAR_DEF(int32_t, P62_Map1C10, 0x00bf1c10)
GAME_VAR_DEF(int32_t, P62_Map1C24, 0x00bf1c24)
GAME_VAR_DEF(int32_t, P62_MapC64, 0x00c1cc64)
GAME_VAR_DEF(int32_t, P62_Map2C40, 0x00c12c40)
GAME_VAR_DEF(int32_t, P62_Map1C0C, 0x00bf1c0c)
GAME_VAR_DEF(int32_t, P62_MapCC90, 0x00c1cc90)
GAME_VAR_DEF(uint8_t *, P62_MapBuf, 0x00b5a900)
GAME_VAR_DEF(p62_page_t, P62_Page, 0x00b32a34)
GAME_VAR_DEF(p62_hs1_t, P62_Hs1, 0x00b5b378)
GAME_VAR_DEF(p62_hs1_t, P62_Hs2, 0x00b5ba58)
GAME_VAR_DEF(p62_hs2_t, P62_Hs3, 0x00b5b008)
GAME_VAR_DEF(p62_hs2_t, P62_Hs4, 0x00b5ac98)
GAME_VAR_DEF(p62_hs2_t, P62_Hs5, 0x00b5a928)
GAME_VAR_DEF(p62_hs3_t, P62_Hs6, 0x00b5c138)

static int32_t  rd32(const uint8_t *p, uint32_t o) { int32_t v; memcpy(&v, p + o, 4); return v; }
static void     wr32(uint8_t *p, uint32_t o, int32_t v) { memcpy(p + o, &v, 4); }
static void     wr16(uint8_t *p, uint32_t o, uint16_t v) { memcpy(p + o, &v, 2); }
static float    fbits(uint32_t b) { float f; memcpy(&f, &b, 4); return f; }
#define SIN(i) ((int32_t)P59_Sin[(i) & 0xfff])

/* 0049c850 */
void P62_InitCamDefaults(void) {
  P61_V20 = 0;
  P61_V1C = 0x800;
  P62_C82434 = -0x400;
  P62_C82500 = -200 - P62_C82434;               /* 0x338 */
  P61_OffX = fbits(0xc2340000); P61_OffY = fbits(0xc3800000); P61_OffZ = fbits(0xc3200000);
  P61_Dist8 = fbits(0x44a00000); P61_DistC = fbits(0x44a00000);
  P62_F136C54 = fbits(0x41200000);
  P61_V10b = 0;
  P61_V18 = 0x800;
  P61_V10 = 0;
  P59_Mode1137324 = 0;                           /* байтовые записи, как в оригинале */
  P52_ResetB = 0;
  *(uint8_t *)&P60_Var1373C0 = 0;
  P62_I137388 = 0;
  P62_I13738C = 42000;
  P62_I137390 = 0;
}

/* 00425a50 */
void P62_InitRenderConsts(void) {
  P43_ScaleA = fbits(0x44900000);
  P19_Out68 = fbits(0x3f000000);
  P42_CellScale = fbits(0x39aec33e);
  P62_F252A94 = (float)P19_ScrW / P19_DivC;
  P62_F25F3F4 = (float)P19_ScrH / P19_DivC;
  if (P58_CfgOn == 0) P11_01270c24 = fbits(0x47241000);
  P62_F25F404 = fbits(0x47543100);
  P62_I270C44 = 0xdbba;
  P12_01252b74 = 0;
  P62_I252A80 = 1;
  P62_I252B78 = -1;
  P62_I270C48 = 1;
  P11_01270c38 = 0;
  P62_I252B68 = 0;
  P62_B25F400 = 0;
}

/* 0049431d: машина *id; курс +0x100 (12 бит); +0xfc — желаемый доворот (±0x200 или половина разности) */
int32_t P62_HeadingDelta(const uint8_t *id, uint32_t want) {
  uint8_t *car = P59_CarsTab + (uint32_t)*id * 0x148;
  uint32_t cur = (uint32_t)rd32(car, 0x100) & 0xfff;
  int32_t d = (int32_t)(((want - cur) + 0x800) & 0xfff) - 0x800;
  int32_t out = 0;
  if (cur != want) {
    int32_t a = d < 0 ? -d : d;
    if (a < 0x80) out = d / 2;
    else out = d < 0 ? -0x200 : 0x200;
  }
  wr32(car, 0xfc, out);
  return d < 0 ? -d : d;
}

/* 00492398 */
int32_t P62_FarFromPlayer(int32_t id, int32_t dist) {
  if (dist == 0) return 0;
  const uint8_t *e = (const uint8_t *)TrafficRecs;
  int32_t i = 0;
  for (; i < 0x40 && (uint32_t)e[6] != (uint32_t)id + 1u; e += 0x54) i++;
  if (i >= 0x40) return 0;
  const uint8_t *car = P59_CarsTab + (uint32_t)i * 0x148;
  uint32_t dx = (uint32_t)rd32(car, 200) - (uint32_t)P59_PosX;
  uint32_t dz = (uint32_t)rd32(car, 0xd0) - (uint32_t)P59_PosZ;
  return (int32_t)((uint32_t)dist * (uint32_t)dist) < (int32_t)(dx * dx + dz * dz);
}

/* 0042d2c9: запись 0x2e слов = тег + 3 вершины по 15 слов, очередь растёт на 0xb8 байт */
void P62_QueueTri(const uint32_t *a, const uint32_t *b, const uint32_t *c, uint32_t tag) {
  uint8_t *q = G0115A13C;
  memcpy(q + 4, a, 15 * 4);
  memcpy(q + 0x40, b, 15 * 4);
  memcpy(q + 0x7c, c, 15 * 4);
  memcpy(q, &tag, 4);
  G01159D74 += 1;
  G0115A13C = q + 0x2e * 4;
}

/* 0051ac05: смещение строки в +8+idx*4 (−1 — пустая), дальше пары (счёт, значение) */
int32_t P62_MapRow(int32_t idx, int32_t *dst) {
  const uint8_t *data = (const uint8_t *)P54_MapBPtr;
  int32_t off = rd32(data, 8 + (uint32_t)idx * 4);
  int32_t n = P62_MapN * P62_MapN;
  if (off == -1) {
    for (; n != 0; n--) *dst++ = -1;
    return 0;
  }
  const uint8_t *p = data + off;
  while (n > 0) {
    int32_t cnt = rd32(p, 0), val = rd32(p, 4);
    n -= cnt;
    p += 8;
    for (; cnt > 0; cnt--) *dst++ = val;
  }
  return 1;
}

/* 004a58ad: таблица «имя\0 + u16» подряд, P62_ModelCount записей */
int32_t P62_ModelLookup(const char *name, uint16_t *out) {
  const char *p = P62_ModelNames;
  int32_t n = P62_ModelCount;
  for (;;) {
    if (n == 0) {
      char buf[256];
      snprintf(buf, sizeof buf, "Unkown model, %s.", name);
      if (P62_NoErr == 0) P26_ErrorInLine(buf);
      return 0;
    }
    n--;
    if (strcmp(name, p) == 0) break;
    p += strlen(p) + 3;
  }
  p += strlen(p) + 1;
  memcpy(out, p, 2);
  return 1;
}

/* 004a6749 */
int32_t P62_FindFreeTrafficSlot(void) {
  uint8_t *base = (uint8_t *)P12_0112da00;
  for (int32_t i = 1; i <= 8; i++) {
    uint8_t *slot = base + (uint32_t)(i - 1) * 0xcd8;
    if (rd32(slot, 0xcb4) == 0) {
      memset(slot, 0, 0xcd8);
      wr32(slot, 0, i - 1);
      return i;
    }
  }
  return -1;
}

/* 0049199a */
void P62_SpawnTrafficCar(int32_t n) {
  if (G0112B284 < P62_Max) {
    uint8_t *rec = (uint8_t *)TrafficRecs + (uint32_t)n * 0x54;
    int32_t r = P62_FindFreeTrafficSlot();
    if (r != -1) {
      rec[5] = (uint8_t)r;
      r--;
      rec[0xd] = 0x19;
      wr16(rec, 0x16, 0);
      uint8_t *slot = (uint8_t *)P12_0112da00 + (uint32_t)r * 0xcd8;
      P51_InitCarSlot((uint32_t)(uintptr_t)(P59_CarsTab + (uint32_t)n * 0x148), slot, (uint32_t)r);
      G0112B284 += 1;
      wr32(slot, 0xcbc, 0);
      wr32(slot, 0x5c, 1);
    }
    P62_I14428C = 0;
  }
}

/* 005047ab */
void P62_DownloadPage(uint32_t h, const uint16_t *bmp, int32_t x, int32_t y, int32_t w, int32_t hh, int32_t stride) {
  if (bmp == NULL) {
    DebugLog("DownloadPageFromBmp: Bitmap not found, operation aborted.");
    return;
  }
  if (w < 0 || w > 256 || hh < 0 || hh > 256) return;   /* оригинал не проверяет; страница 256x256 */
  const uint16_t *src = bmp + ((int64_t)y * stride + x);
  uint16_t *dst = P62_Page;
  for (; hh != 0; hh--) {
    memcpy(dst, src, (size_t)w * 2);
    dst += 0x100;
    src += stride;
  }
  P62_Fn424A02(h, P62_Page);
}

/* 0051cb98: заголовок «ERCS» (0x53435245), версия 3, затем шесть таблиц */
int32_t P62_SaveScores(void *file) {
  uint32_t hdr[4] = { 0x53435245, 0, 0, 3 };
  g_fwrite(hdr, 0x10, 1, file);
  g_fwrite(P62_Hs1, 0x2c, 0x28, file);
  g_fwrite(P62_Hs2, 0x2c, 0x28, file);
  g_fwrite(P62_Hs3, 0x2c, 0x14, file);
  g_fwrite(P62_Hs4, 0x2c, 0x14, file);
  g_fwrite(P62_Hs5, 0x2c, 0x14, file);
  g_fwrite(P62_Hs6, 0x2c, 4, file);
  return 1;
}

/* 00413df3 */
int32_t P62_MenuBusy(void) {
  if (P62_BusyA == 0 && P62_BusyB == 0 && P62_BusyC == 0 && (P62_BusyD == 0 || P62_Menu1271060 == 7) && P62_BusyE == 0) return 0;
  return 1;
}

/* 0051cdec */
int32_t P62_ScoreTable(int32_t *idx, int32_t alt) {
  int32_t r = 0;
  if (P62_MenuBusy() == 0) {
    if (alt == 0) {
      *idx = P62_Fn51CC55(&P62_Menu1271060, P62_Menu1271060, P62_Menu1271064);
      if (*idx != -1) r = P42_GetHighScore(P62_Menu1271060, P62_Menu1271064);
    } else if (P62_Menu1271060 == 0xb) {
      *idx = P62_Fn51CC55(&P62_Menu1271060, 0xc, P62_Menu1271064);
      if (*idx != -1) r = P42_GetHighScore(0xc, P62_Menu1271064);
    }
  }
  return r;
}

/* 005025dc: «%d%s» — скорость·3/10 и единица; после 200 мигает яркостью */
void P62_SpeedText(void) {
  if (P62_HudOff1 == 0 && P62_HudOff2 == 0) {
    char buf[32];
    int32_t v = (P62_Spd * 3) / 10;
    uint8_t c;
    snprintf(buf, sizeof buf, "%d%s", v, P62_Unit ? P62_Unit : "");
    if (P62_Spd > 0xc8 && P62_Blink != 0) c = (uint8_t)((P62_Frame & 0x1f) << 3);
    else c = 0xff;
    P56_DrawText(0x25d, 0x1c2, buf, 0, 2, 0xff, c, c);
  }
}

/* 004ec336 */
void P62_LoadMapHeader(void *file, int32_t size) {
  P27_ReadChunked(&P62_MapW, 4, 1, file);
  P27_ReadChunked(&P62_MapH, 4, 1, file);
  P62_Map1C10 = P62_MapW * 0x5dc;
  P62_Map1C24 = P62_MapH * 0x5dc;
  P62_MapC64 = P62_Map1C10 / 2;
  P62_Map2C40 = P62_Map1C24 / 2;
  P62_Map1C0C = P62_MapW / 2;
  P62_MapCC90 = P62_MapH / 2;
  P62_MapBuf = (uint8_t *)DebugMalloc(size - 8, "D:\\Driver\\Game\\map.c", 0x35f);
  P27_ReadChunked(P62_MapBuf, 1, size - 8, file);
}

/* 00514c72 */
void P62_ParticleSet(uint8_t *p, int32_t kind, int32_t a, uint32_t flags, int32_t b) {
  wr16(p, 4, (uint16_t)kind);
  wr32(p, 0x24, a);
  wr32(p, 0x40, b);
  wr32(p, 0xc, (int32_t)(flags | 0x80));
}

/* 00515813 */
void P62_ParticleInit(uint8_t *p, void *car) {
  uint32_t h = P62_Fn515CCA(p, car);
  wr16(p, 0, 1);
  if (P62_Alt == 0) {
    wr32(p, 0x14, (int32_t)h);
    wr16(p, 0x5e, (uint16_t)h);
    P62_ParticleSet(p, 3, 0, (uint32_t)rd32(p, 0xc) & 0xfffffbffu, 1);
  } else {
    wr32(p, 0xc, rd32(p, 0xc) | 0x800);
    float fa = (float)(SIN(h) >> 7), fb = (float)(SIN(h + 0x400) >> 7);
    memcpy(p + 0x74, &fa, 4);
    wr32(p, 0x78, (int32_t)0xc25c0000);
    memcpy(p + 0x7c, &fb, 4);
  }
}
