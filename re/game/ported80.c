#include "ported80.h"
#include "ported81.h"
#include <math.h>
#include <string.h>

GAME_VAR_DEF(p80_boxtab_t, P80_Boxes, 0x00cf56e0)
GAME_VAR_DEF(p80_class_t, P80_Class, 0x00c98a40)
GAME_VAR_DEF(p80_lumps_t, P80_LumpTab, 0x00d012e0)
GAME_VAR_DEF(int32_t, P80_GridH, 0x00562d3c)
GAME_VAR_DEF(int32_t, P80_Cell, 0x00562d40)
GAME_VAR_DEF(int32_t, P80_Hdr5, 0x00d01274)
GAME_VAR_DEF(int32_t, P80_Hdr6, 0x00c97a28)
GAME_VAR_DEF(int32_t, P80_HalfW, 0x00cb8f08)
GAME_VAR_DEF(int32_t, P80_HalfH, 0x00cf2f9c)
GAME_VAR_DEF(float, P80_InvMap, 0x00c1cc60)
GAME_VAR_DEF(int32_t, P80_Cols, 0x00d00250)
GAME_VAR_DEF(float, P80_Save0, 0x00d001f0)
GAME_VAR_DEF(float, P80_Save1, 0x00d001f4)
GAME_VAR_DEF(float, P80_Save2, 0x00d001f8)
GAME_VAR_DEF(float, P80_Save3, 0x00d001fc)
GAME_VAR_DEF(float, P80_Dir3, 0x005507dc)
GAME_VAR_DEF(float, P80_SaveW, 0x00cb8f00)
GAME_VAR_DEF(float, P80_Alt0, 0x00d00240)
GAME_VAR_DEF(float, P80_Alt1, 0x00d00244)
GAME_VAR_DEF(float, P80_Alt2, 0x00d00248)
GAME_VAR_DEF(float, P80_Alt3, 0x00d0024c)
GAME_VAR_DEF(float, P80_AltW, 0x00d01264)
GAME_VAR_DEF(int32_t, P80_Flag17AEC, 0x00d17aec)
GAME_VAR_DEF(float, P80_One, 0x00546020)
GAME_VAR_DEF(float, P80_C45, 0x005461f4)
GAME_VAR_DEF(float, P80_C02, 0x00546080)
GAME_VAR_DEF(float, P80_C045, 0x005469ec)
GAME_VAR_DEF(float, P80_Half, 0x00546068)

/* Значения float-констант из .data Game.exe: 1.0, 45.0, 0.2 (0x3e4ccccd), 0.45 (0x3ee66666), 0.5 */
void P80_InitConsts(void) {
#ifndef RE_HOOK_BUILD
  P80_One = 1.0f; P80_C45 = 45.0f; P80_C02 = 0.2f; P80_C045 = 0.45f; P80_Half = 0.5f;
#endif
}

static uint32_t rd32(const void *p, int o) { uint32_t v; memcpy(&v, (const uint8_t *)p + o, 4); return v; }
static uint16_t rd16(const void *p, int o) { uint16_t v; memcpy(&v, (const uint8_t *)p + o, 2); return v; }
static float rdf(const void *p, int o) { float v; memcpy(&v, (const uint8_t *)p + o, 4); return v; }

/* 00426ce3: вершины модели (+0x20, шаг 0x10) берутся по индексам записей (+8, +0xc, +0x10 и для нечётного типа +0x14);
   шаг записи — G2_TABLE_00550ACC[тип]. Сравнения строгие, как в x87-коде оригинала. */
float *P80_Bounds(float *out, int32_t model) {
  const uint8_t *m = (const uint8_t *)P79_PTR(P79_ModelTab[model]);
  const uint8_t *verts = (const uint8_t *)P79_PTR(rd32(m, 0x20));
  const uint8_t *rec = (const uint8_t *)P79_PTR(rd32(m, 0x2c));
  float lo[3] = {1e6f, 1e6f, 1e6f}, hi[3] = {-1e6f, -1e6f, -1e6f};
  for (int i = 0; i < (int)rd16(m, 0x16); i++) {
    int nv = (rec[0] & 1) == 0 ? 3 : 4;
    for (int k = 0; k < nv; k++) {
      const uint8_t *v = verts + (size_t)rd32(rec, 8 + k * 4) * 16;
      for (int a = 0; a < 3; a++) {
        float c = rdf(v, a * 4);
        if (c < lo[a]) lo[a] = c;
        if (hi[a] < c) hi[a] = c;
      }
    }
    rec += G2_TABLE_00550ACC[rec[0]];
  }
  float h = hi[1] - lo[1];
  int32_t r = (int32_t)lrintf(h);
  P11_00ba52d0 = r;
  float res[8] = {lo[0], lo[1], lo[2], hi[0], hi[1], hi[2], h, 0};
  memcpy(&res[7], &r, 4);
  memcpy(out, res, sizeof res);
  return out;
}

/* 004eb490 */
void P80_LoadModels(void *f) {
  int32_t size;
  uint8_t *tmp = (uint8_t *)DebugMalloc(0x20000, "D:\\Driver\\Game\\map.c", 0x119);
  AllocMapBuffer400000();
  uint8_t *dst = (uint8_t *)D_00c98ed0;
  P27_ReadChunked(&P20_Count, 4, 1, f);
  int32_t n = P20_Count;
  if (n > 1126) n = P20_Count = 1126;       /* охранная проверка (в оригинале её нет) */
  for (int32_t i = 0; i < n; i++) {
    P27_ReadChunked(&size, 4, 1, f);
    if (size < 0 || size > 0x20000) size = 0;
    P27_ReadChunked(tmp, size, 1, f);
    size = P79_Convert(tmp, dst);
    P79_ModelTab[i] = P79_OFF(dst);
    dst += size;
  }
  for (int32_t i = 0; i < n; i++) {
    void *m = P79_PTR(P79_ModelTab[i]);
    if ((int32_t)rd32(m, 4) == -1) { P79_Relocate(m); P79_Radius(m, 0); P79_Radius(m, 1); }
  }
  for (int32_t i = 0; i < n; i++) {
    void *m = P79_PTR(P79_ModelTab[i]);
    if ((int32_t)rd32(m, 4) != -1) { P79_Relocate(m); P79_Radius(m, 0); P79_Radius(m, 1); }
  }
  for (int32_t i = 0; i < n; i++) {
    P80_Bounds(P80_Boxes[i], i);
    void *m = P79_PTR(P79_ModelTab[i]);
    P79_MarkRecords(m);
    P79_FindSameVerts(m);
    uint16_t fl = rd16(m, 2); uint32_t fl8 = rd32(m, 8); uint8_t c;
    if (fl & 0x800) c = 3;
    else if (fl & 8) c = 6;
    else if (fl & 0x1000) c = 4;
    else if (fl & 0x80) c = 2;
    else if (fl & 0x40) c = 5;
    else if (fl8 & 2) c = 7;
    else if (fl8 & 0x800) c = (P14_00b87e84 == 0) ? 0 : 1;
    else c = 1;
    P80_Class[i] = c;
  }
  DebugFree(tmp);
}

/* 004ed055: заголовок блока 2 — 11 слов {w, h, cell, nSlots, grid, ?, ?, w(float), dx, dy, dz} (0x2c байта);
   затем число записей и по 0x14 байта → в таблицу по 0x20 байт; затем nSlots списков {n, n слов; m, m байт; k, k×0x14}.
   Указатели на списки кладутся в P80_LumpTab (родного размера); сами списки идут подряд в буфер D_00d00230. */
void P80_LoadHeader(void *f) {
  int32_t h[11];
  uint8_t *cur = (uint8_t *)D_00d00230;
  float tmp;
  { uint32_t c = 0x3a2ec33eu; memcpy(&tmp, &c, 4); P63_Scale = tmp; }
  P27_ReadChunked(h, 0x2c, 1, f);
  float hf7, hf8, hf9, hf10;
  memcpy(&hf7, &h[7], 4); memcpy(&hf8, &h[8], 4); memcpy(&hf9, &h[9], 4); memcpy(&hf10, &h[10], 4);
  P21_GridDiv = h[0]; P80_GridH = h[1]; P80_Cell = h[2];
  P80_Hdr5 = h[5]; P80_Hdr6 = h[6]; P19_Out68 = hf7;
  P76_NumSlots = h[3]; P54_GridN = h[4];
  P21_GridRadius = P80_Cell != 0 ? 45000 / P80_Cell : 0;
  P21_GridStride = P21_GridRadius * 2 + 1;
  D_00d00204 = P21_GridStride * P21_GridStride;
  P80_HalfW = P21_GridDiv / 2; P80_HalfH = P80_GridH / 2;
  P42_CellX = P80_HalfW * P80_Cell; P42_CellY = P80_HalfH * P80_Cell;
  P62_MapN = P54_GridN * (P80_Cell / 0x5dc);
  P80_InvMap = (float)((long double)P80_One / (float)P62_MapN);
  P80_Cols = P54_GridN != 0 ? P21_GridDiv / P54_GridN : 0;
  P72_Rows = P54_GridN != 0 ? P80_GridH / P54_GridN : 0;
  P43_NormalizeToOut(hf8, hf9, hf10);
  P80_Save0 = P19_OutA; P80_Save1 = P19_OutB; P80_Save2 = P19_OutC; P80_Save3 = P80_Dir3;
  P80_SaveW = P19_Out68;
  P80_Alt3 = P80_Dir3;
  P80_Alt0 = P19_OutA; P80_Alt1 = P19_OutB; P80_Alt2 = P19_OutC;
  P80_AltW = P19_Out68;
  float k = (float)((long double)(float)(int32_t)((uint32_t)G00B87E4C << 1) / P80_C45 + P80_C02);
  P80_Alt0 *= k; P80_Alt1 *= k; P80_Alt2 *= k; P80_AltW *= k;
  if (P14_00b202d8 != 0) {
    P19_OutA = P80_Alt0; P19_OutB = P80_Alt1; P19_OutC = P80_Alt2; P80_Dir3 = P80_Alt3; P19_Out68 = P80_AltW;
    P80_Flag17AEC = 0;
  } else if (P14_00b202dc != 0) {
    P19_OutA = P80_Save0; P19_OutB = P80_Save1; P19_OutC = P80_Save2; P80_Dir3 = P80_Save3; P19_Out68 = P80_SaveW;
    P80_Flag17AEC = 0;
  } else if (P14_00b87e84 != 0) {
    P19_OutA = P80_Alt0; P19_OutB = P80_Alt1; P19_OutC = P80_Alt2; P80_Dir3 = P80_Alt3; P19_Out68 = P80_AltW;
  } else {
    P19_OutA = P80_Save0; P19_OutB = P80_Save1; P19_OutC = P80_Save2; P80_Dir3 = P80_Save3; P19_Out68 = P80_SaveW;
    if (P26_FxA != 0) {
      P19_Out68 *= P80_Half;
      P19_OutA *= P80_C045; P19_OutB *= P80_C045; P19_OutC *= P80_C045;
    }
  }
  P81_Light();
  P27_ReadChunked(&P54_Cnt1E0, 4, 1, f);
  P54_AllocMapBufs();
  uint8_t *ent = (uint8_t *)G6_00D00208;
  for (int32_t i = 0; i < P54_Cnt1E0; i++, ent += 0x20) {
    uint8_t rec[0x14]; uint32_t w; uint16_t u;
    P27_ReadChunked(rec, 0x14, 1, f);
    memset(ent, 0, 0x20);
    memcpy(&u, rec + 2, 2); w = u; memcpy(ent + 4, &w, 4);
    memcpy(ent + 8, rec + 4, 4); memcpy(ent + 0xc, rec + 8, 4); memcpy(ent + 0x10, rec + 0xc, 4);
    { float one = 1.0f; memcpy(ent + 0x14, &one, 4); }
    memcpy(ent + 0x18, rec + 0x10, 4);
  }
  for (int32_t i = 0; i < P76_NumSlots && i < 1024; i++) {
    int32_t n;
    P80_LumpTab[i] = cur;
    P27_ReadChunked(&n, 4, 1, f); memcpy(cur, &n, 4); cur += 4;
    if (n != 0) { P27_ReadChunked(cur, 4, n, f); cur += (size_t)n * 4; }
    P27_ReadChunked(&n, 4, 1, f); memcpy(cur, &n, 4); cur += 4;
    P27_ReadChunked(cur, 1, n, f); cur += n;
    P27_ReadChunked(&n, 4, 1, f); memcpy(cur, &n, 4); cur += 4;
    if (n != 0) { P27_ReadChunked(cur, 0x14, n, f); cur += (size_t)n * 0x14; }
  }
}
