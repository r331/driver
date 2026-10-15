#include "ported76.h"
#include "ported89.h"
#include <string.h>
#ifdef RE_HOOK_BUILD
#  define P76_STD __attribute__((stdcall))
#else
#  define P76_STD
#endif

GAME_VAR_DEF(int32_t, P76_Angle, 0x00d02680)
GAME_VAR_DEF(uint8_t, P76_ColA, 0x00d02668)
GAME_VAR_DEF(uint8_t, P76_ColB, 0x00d02320)
GAME_VAR_DEF(uint8_t, P76_ColC, 0x00d02669)
GAME_VAR_DEF(p76_obj_t, P76_ColObj, 0x00d02650)
GAME_VAR_DEF(int32_t, P76_NumSlots, 0x00cfe6e0)
GAME_VAR_DEF(float, P76_K255, 0x00546064)

_Static_assert(sizeof(plat_vertex) == 0x20, "plat_vertex");

void P76_InitConsts(void) { P76_K255 = 255.0f; }

/* Три вершины подряд в буфер текущего слота текстуры (P22_TexVarA); оригинал не проверяет границ буфера (0x1000 вершин) — здесь проверка есть. */
static void tri(const int32_t *v0, const int32_t *v1, const int32_t *v2, int variant_b) {
  const int32_t *in[3] = { v0, v1, v2 };
  if (P22_DevReady == 0) return;
  int32_t slot = P22_TexVarA;
  if (slot < 0 || slot >= 33) return;
  for (int i = 0; i < 3; i++) {
    int32_t n = P33_Count[slot];
    if (n < 0 || n >= 0x1000) return;
    plat_vertex *dst = (plat_vertex *)(P33_VBuf[slot] + (size_t)n * 0x20);
    P33_Count[slot] = n + 1;
    if (variant_b) P23_ConvVertexB(in[i], dst); else P23_ConvVertexA(in[i], dst);
  }
}
void P76_TriA1(const int32_t *a, const int32_t *b, const int32_t *c) { tri(a, b, c, 0); }
void P76_TriB1(const int32_t *a, const int32_t *b, const int32_t *c) { tri(a, b, c, 1); }
void P76_TriA2(const int32_t *a, const int32_t *b, const int32_t *c) { tri(a, b, c, 0); }
void P76_TriB2(const int32_t *a, const int32_t *b, const int32_t *c) { tri(a, b, c, 1); }

/* 0048a525: n — номер записи; список индексов (до 0x40, 0xff — конец) → помечаем записи 01145a60 (шаг 16) */
void P76_MarkSlots(int32_t n) {
  if (n < 0 || n >= P76_NumSlots || n >= 0x400) return;
  for (int32_t i = 0; i < 0x40; i++) {
    uint32_t u = P11_0125f420[i + n * 0x46];
    if (u == 0xff) break;
    uint8_t *e = &P12_01145a60[u * 0x10];
    if (e[1] == 0xff) {
      if ((e[0] & 0x10) == 0 && P12_00b1c3dc < 0x40) {
        e[0] |= 0x10;
        P12_00b1c3f4[P12_00b1c3dc] = (int32_t)u;
        P12_00b1c3dc++;
      }
    } else if (e[1] < 0x40) {
      P12_01146f20[e[1] * 0x1c] |= 2;
    }
  }
}

/* 00424b70: запись устройства (0x4c байта): +4 «3Dfx», +0x24 «Glide 2.x», тип 0 */
int32_t P76_GlideRegister(void) {
  if (P42_DevCount < 4) {
    if (P33_GlideOk == 0) P33_GlideOk = P31_LoadGlide();
    if (P33_GlideOk != 0) {
      uint8_t *e = (uint8_t *)&P74_DevTab[0] + (size_t)P42_DevCount * 0x4c;
      memset(e, 0, 0x4c);
      strcpy((char *)e + 4, "3Dfx");
      strcpy((char *)e + 0x24, "Glide 2.x");
      P42_DevCount = P42_DevCount + 1;
    }
  }
  return P33_GlideOk;
}

/* 0040dbee: v — яркость 0..1 (×255 → байт для R, G, B); экран 640x480 плитками 256x256 (правый столбец 128, нижний ряд 224) */
void P76_TileFill(float v) {
  uint8_t col[3];
  int32_t k = (int32_t)((long double)v * P76_K255);
  col[0] = col[1] = col[2] = (uint8_t)k;
  int32_t idx = 0;
  for (int32_t y = 0; y < 0x1e0; y += 0x100) {
    int32_t h = 0x100;
    if (y + 0x100 > 0x1e0) h = 0xe0;
    for (int32_t x = 0; x < 0x280; x += 0x100) {
      int32_t w = 0x100;
      if (x + 0x100 > 0x280) w = 0x80;
      P76_Fn40DCE0(x, y, w, h, idx, col);
      idx++;
    }
  }
  for (int i = 0; i < P33_GlideCount(); i++)
    if (strcmp(P33_GlideName(i), "_grBufferSwap@4") == 0) {
      void (P76_STD *swap)(int32_t) = (void (P76_STD *)(int32_t))P33_GlideProc(i);
      if (swap) swap(1);
      break;
    }
}

/* 004a3aa7: o[12] (+0x30) — счётчик кадров; на 1, 30, 60 — звук 0x10, на 90 — звук 0x11 и сброс */
void P76_FlashStep(int32_t *o) {
  o[12] += 1;
  if (o[12] == 1) {
    SoundPlay00523E50(0x10, 0x10, -1);
  } else if (o[12] == 0x1e) {
    o[3] = 0;
    SoundPlay00523E50(0x10, 0x10, -1);
  } else if (o[12] == 0x3c) {
    o[3] = 0;
    SoundPlay00523E50(0x10, 0x10, -1);
  } else if (o[12] > 0x59) {
    SoundPlay00523E50(0x11, 0x10, -1);
    o[3] = 0;
    o[5] = 0;
    o[4] |= 4;
    o[12] = 0;
    o[13] = 0x8c;
    if (P16_IdleMode == 3) P16_IdleMode = 0x7fff;
  }
}

/* x87: fild → float, fadd/fmul в расширенной точности, результат float */
static float cell_coord(int32_t base, float p) {
  float b = (float)base;
  return (float)(((long double)b + p) * P42_CellScale);
}

/* 004ecee8: pos[0]/pos[2] → клетка; в пределах P21_GridRadius от (cx, cy) — значение grid[(dx+15) + (dy+15)*stride] != 0 */
int32_t P76_InBox(const float *pos, const uint8_t *grid, int32_t cx, int32_t cy) {
  float fx = cell_coord(P42_CellX, pos[0]);
  float fy = cell_coord(P42_CellY, pos[2]);
  int32_t dx = (int32_t)fx - cx;
  int32_t dy = (int32_t)fy - cy;
  int32_t ax = dx < 0 ? -dx : dx;
  if (ax > P21_GridRadius) return 0;
  int32_t ay = dy < 0 ? -dy : dy;
  if (ay > P21_GridRadius) return 0;
  dx += 0xf; dy += 0xf;
  return grid[dx + dy * P21_GridStride] != 0 ? 1 : 0;
}

/* 004ee813: клетка (ox, oy) в сетке размером N=P54_GridN; 004ef793(номер блока, номер внутри блока, arg) */
void P76_CellFromPos(const float *pos, uint8_t *arg, int32_t *ox, int32_t *oy) {
  float fx = cell_coord(P42_CellX, pos[0]);
  float fy = cell_coord(P42_CellY, pos[2]);
  int32_t x = (int32_t)fx, y = (int32_t)fy;
  *ox = x; *oy = y;
  int32_t n = P54_GridN;
  if (n == 0) return;                 /* оригинал упал бы на делении */
  int32_t qx = x / n, qy = y / n;
  int32_t blk = qx + qy * (P21_GridDiv / n);
  int32_t sub = (y - qy * n) * n + (x - qx * n);
  P89_VisMask(blk, sub, arg);
}

/* 004e8f1e: Angle (0..191) → три байта цвета; ≥192 — ничего */
void P76_AngleColor(void) {
  int32_t v = P76_Angle;
  if (v < 0x40) {
    P76_ColA = (uint8_t)(0xff - v);
    P76_ColB = (uint8_t)(0xff - v);
    P76_ColC = (uint8_t)(0xff - v * 4);
  } else if (v < 0x80) {
    P76_ColA = (uint8_t)(0xff - v);
    P76_ColB = (uint8_t)(0x13f - v * 2);
    P76_ColC = 0;
  } else if (v < 0xc0) {
    P76_ColA = (uint8_t)(0x17f - v * 2);
    P76_ColB = (uint8_t)(0xc0 - v);
    P76_ColC = 0;
  } else {
    return;
  }
  P76_Fn4268EF(&P76_ColObj[0], 6000, P76_ColA, P76_ColB, P76_ColC);
}

/* 0051caa7: заголовок 16 байт (magic 'ERCS' = 0x53435245, [3] — версия 3), затем шесть таблиц записей по 0x2c байта (0x28, 0x28, 0x14, 0x14, 0x14, 4 записей);
   при неверном заголовке позиция файла возвращается */
int32_t P76_LoadHsTables(void *f) {
  int32_t hdr[4];
  long pos = g_ftell(f);
  g_fread(hdr, 0x10, 1, f);
  if (hdr[0] != 0x53435245 || hdr[3] != 3) {
    g_fseek(f, pos, 0);
    return 0;
  }
  g_fread(&P62_Hs1[0], 0x2c, 0x28, f);
  g_fread(&P62_Hs2[0], 0x2c, 0x28, f);
  g_fread(&P62_Hs3[0], 0x2c, 0x14, f);
  g_fread(&P62_Hs4[0], 0x2c, 0x14, f);
  g_fread(&P62_Hs5[0], 0x2c, 0x14, f);
  g_fread(&P62_Hs6[0], 0x2c, 4, f);
  return 1;
}
