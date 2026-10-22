/* ported76.c — assorted small Game.exe functions (English overview; original notes follow): triangle
   submission for the Direct3D path, Glide device registration, a full-screen tiled fill, a flashing
   pickup timer, map-cell lookups, a colour ramp and loading of the high-score tables. */
#include "redbg.h"
#include "ported76.h"
#include "ported89.h"
#include <string.h>
#ifndef RE_HOOK_BUILD
#include "../platform/sdl/plat_detail.h"
#endif
#ifdef RE_HOOK_BUILD
#  define P76_STD __attribute__((stdcall))
#else
#  define P76_STD
#endif

#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P76_Angle")
#undef P76_Angle
#pragma push_macro("P76_Angle") /*gvi*/
#undef P76_Angle /*gvi*/
int32_t P76_Angle;
#pragma pop_macro("P76_Angle") /*gvi*/
#pragma pop_macro("P76_Angle")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P76_ColA")
#undef P76_ColA
#pragma push_macro("P76_ColA") /*gvi*/
#undef P76_ColA /*gvi*/
uint8_t P76_ColA;
#pragma pop_macro("P76_ColA") /*gvi*/
#pragma pop_macro("P76_ColA")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P76_ColB")
#undef P76_ColB
#pragma push_macro("P76_ColB") /*gvi*/
#undef P76_ColB /*gvi*/
uint8_t P76_ColB;
#pragma pop_macro("P76_ColB") /*gvi*/
#pragma pop_macro("P76_ColB")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P76_ColC")
#undef P76_ColC
#pragma push_macro("P76_ColC") /*gvi*/
#undef P76_ColC /*gvi*/
uint8_t P76_ColC;
#pragma pop_macro("P76_ColC") /*gvi*/
#pragma pop_macro("P76_ColC")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P76_ColObj")
#undef P76_ColObj
#pragma push_macro("P76_ColObj") /*gvi*/
#undef P76_ColObj /*gvi*/
p76_obj_t P76_ColObj;
#pragma pop_macro("P76_ColObj") /*gvi*/
#pragma pop_macro("P76_ColObj")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P76_NumSlots")
#undef P76_NumSlots
#pragma push_macro("P76_NumSlots") /*gvi*/
#undef P76_NumSlots /*gvi*/
int32_t P76_NumSlots;
#pragma pop_macro("P76_NumSlots") /*gvi*/
#pragma pop_macro("P76_NumSlots")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P76_K255")
#undef P76_K255
#pragma push_macro("P76_K255") /*gvi*/
#undef P76_K255 /*gvi*/
float P76_K255;
#pragma pop_macro("P76_K255") /*gvi*/
#pragma pop_macro("P76_K255")
#endif

_Static_assert(sizeof(plat_vertex) == 0x20, "plat_vertex");

/* P76_InitConsts — no Game.exe address (initialises the .data constant P76_K255 = 255.0 that the
   original has preset). */
void P76_InitConsts(void) { P76_K255 = 255.0f; }

/* Append one complete triangle, flushing batches before the slot fills. */
/* tri — local helper: appends one triangle to the vertex batch of the current texture slot (P22_TexVarA),
   flushing first if fewer than 3 vertices are free (P33_EnsureRoom); vertices are converted with
   P23_ConvVertexA or ...B.  Native: also feeds the facade-detail capture (v2.31). */
static void tri(const int32_t *v0, const int32_t *v1, const int32_t *v2, int variant_b) {
  const int32_t *in[3] = { v0, v1, v2 };
  if (P22_DevReady == 0) return;
  int32_t slot = P22_TexVarA;
  if (!P33_EnsureRoom(slot, 3)) return;
#ifndef RE_HOOK_BUILD
  if (re_detail_capture) re_detail_tri(v0, v1, v2);   /* v2.31: детальные меши фасадов — совпадение страницы/UV */
#endif
  for (int i = 0; i < 3; i++) {
    int32_t count = P33_Count[slot];
    plat_vertex *out_vtx = (plat_vertex *)(P33_VBuf[slot] + (size_t)count * 0x20);
    P33_Count[slot] = count + 1;
    if (variant_b) P23_ConvVertexB(in[i], out_vtx); else P23_ConvVertexA(in[i], out_vtx);
  }
}
/* P76_TriA1, P76_TriB1, P76_TriA2, P76_TriB2 — Game.exe 0041e926, 0041ea2a, 0041f825, 0041f929.
   Triangle handlers of the Direct3D renderer: "A" uses vertex conversion A, "B" conversion B.
   The "1" and "2" pairs are separate functions in Game.exe with the same body here.
   TODO(RE): unsure what distinguishes conversion A from B (see P23_ConvVertexA/B) and the "1"/"2" pairs. */
void P76_TriA1(const int32_t *a, const int32_t *b, const int32_t *c) { tri(a, b, c, 0); }
void P76_TriB1(const int32_t *a, const int32_t *b, const int32_t *c) { tri(a, b, c, 1); }
void P76_TriA2(const int32_t *a, const int32_t *b, const int32_t *c) { tri(a, b, c, 0); }
void P76_TriB2(const int32_t *a, const int32_t *b, const int32_t *c) { tri(a, b, c, 1); }

/* 0048a525: n — номер записи; список индексов (до 0x40, 0xff — конец) → помечаем записи 01145a60 (шаг 16) */
/* P76_MarkSlots — Game.exe 0048a525.  For record n of 0125f420 (stride 0x46, up to 0x40 indices, 0xff ends
   the list) marks the referenced entries of 01145a60 (16 bytes each): an entry with byte 1 == 0xff gets
   flag 0x10 and is queued in 00b1c3f4 (max 0x40); otherwise flag 2 is set on record byte1 of 01146f20.
   TODO(RE): unsure what these tables are (map objects / their instances?). */
void P76_MarkSlots(int32_t n) {
  if (n < 0 || n >= P76_NumSlots || n >= 0x400) return;
  for (int32_t i = 0; i < 0x40; i++) {
    uint32_t ent_idx = P11_0125f420[i + n * 0x46];
    if (ent_idx == 0xff) break;
    uint8_t *ent = &P12_01145a60[ent_idx * 0x10];
    if (ent[1] == 0xff) {
      if ((ent[0] & 0x10) == 0 && P12_00b1c3dc < 0x40) {
        ent[0] |= 0x10;
        P12_00b1c3f4[P12_00b1c3dc] = (int32_t)ent_idx;
        P12_00b1c3dc++;
      }
    } else if (ent[1] < 0x40) {
      P12_01146f20[ent[1] * 0x1c] |= 2;
    }
  }
}

/* 00424b70: запись устройства (0x4c байта): +4 «3Dfx», +0x24 «Glide 2.x», тип 0 */
/* P76_GlideRegister — Game.exe 00424b70.  If fewer than 4 render devices are listed and the Glide DLL loads,
   adds a device entry (0x4c bytes: +4 "3Dfx", +0x24 "Glide 2.x").  Returns P33_GlideOk. */
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
/* P76_TileFill — Game.exe 0040dbee.  Fills the 640x480 screen with grey level v (0..1 -> 0..255) in
   256x256 tiles (the right column 128 wide, the bottom row 224 high), then swaps buffers (grBufferSwap(1)). */
void P76_TileFill(float v) {
  uint8_t col[3];
  int32_t level = (int32_t)((long double)v * P76_K255);
  col[0] = col[1] = col[2] = (uint8_t)level;
  int32_t tile = 0;
  for (int32_t y = 0; y < 0x1e0; y += 0x100) {
    int32_t h = 0x100;
    if (y + 0x100 > 0x1e0) h = 0xe0;
    for (int32_t x = 0; x < 0x280; x += 0x100) {
      int32_t w = 0x100;
      if (x + 0x100 > 0x280) w = 0x80;
      P76_Fn40DCE0(x, y, w, h, tile, col);
      tile++;
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
/* P76_FlashStep — Game.exe 004a3aa7.  Per-frame step of a timed flashing object: o[12] counts frames;
   sound 0x10 at frames 1, 30 and 60, and at frame 90 sound 0x11, reset of the object (o[3], o[5] = 0,
   flag 4 in o[4], o[13] = 0x8c) and the counter.  Leaves idle mode 3 (P16_IdleMode -> 0x7fff).
   TODO(RE): unsure which game object this is. */
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
/* cell_coord — local helper: map-grid coordinate (base + p) * CellScale with the original x87 rounding. */
static float cell_coord(int32_t base, float p) {
  float b = (float)base;
  return (float)(((long double)b + p) * P42_CellScale);
}

/* 004ecee8: pos[0]/pos[2] → клетка; в пределах P21_GridRadius от (cx, cy) — значение grid[(dx+15) + (dy+15)*stride] != 0 */
/* P76_InBox — Game.exe 004ecee8.  1 if pos (x, z) lies within P21_GridRadius cells of (cx, cy) and the
   31x31 visibility grid (centre at 15, 15) has that cell set, else 0. */
int32_t P76_InBox(const float *pos, const uint8_t *grid, int32_t cx, int32_t cy) {
  float fx = cell_coord(P42_CellX, pos[0]);
  float fy = cell_coord(P42_CellY, pos[2]);
  int32_t dx = (int32_t)fx - cx;
  int32_t dy = (int32_t)fy - cy;
  int32_t adx = dx < 0 ? -dx : dx;
  if (adx > P21_GridRadius) return 0;
  int32_t ady = dy < 0 ? -dy : dy;
  if (ady > P21_GridRadius) return 0;
  dx += 0xf; dy += 0xf;
  return grid[dx + dy * P21_GridStride] != 0 ? 1 : 0;
}

/* 004ee813: клетка (ox, oy) в сетке размером N=P54_GridN; 004ef793(номер блока, номер внутри блока, arg) */
/* P76_CellFromPos — Game.exe 004ee813.  Grid cell (x, y) of pos -> *ox, *oy; then asks P89_VisMask for the
   tile number and the cell index inside the tile (N = P54_GridN cells per tile side).
   Native: returns after setting *ox and *oy when N == 0 (the original would divide by zero). */
void P76_CellFromPos(const float *pos, uint8_t *arg, int32_t *ox, int32_t *oy) {
  float fx = cell_coord(P42_CellX, pos[0]);
  float fy = cell_coord(P42_CellY, pos[2]);
  int32_t x = (int32_t)fx, y = (int32_t)fy;
  *ox = x; *oy = y;
  int32_t tile_n = P54_GridN;
  if (tile_n == 0) return;                 /* оригинал упал бы на делении */
  int32_t tile_x = x / tile_n, tile_y = y / tile_n;
  int32_t tile = tile_x + tile_y * (P21_GridDiv / tile_n);
  int32_t cell_in_tile = (y - tile_y * tile_n) * tile_n + (x - tile_x * tile_n);
  P89_VisMask(tile, cell_in_tile, arg);
}

/* 004e8f1e: Angle (0..191) → три байта цвета; ≥192 — ничего */
/* P76_AngleColor — Game.exe 004e8f1e.  Maps P76_Angle 0..191 to an RGB triple (white -> yellow -> red ->
   dark, in three 64-step ramps) and applies it to object P76_ColObj (004268ef, value 6000);
   >= 192 does nothing.  TODO(RE): unsure what the object and 6000 are. */
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
/* P76_LoadHsTables — Game.exe 0051caa7.  Reads the high-score tables from an open file: a 16-byte header
   (magic "ERCS", version 3 in word 3), then six tables of 0x2c-byte records (40, 40, 20, 20, 20, 4 records).
   Returns 1; on a bad header restores the file position and returns 0. */
int32_t P76_LoadHsTables(void *f) {
  int32_t header[4];
  long start = g_ftell(f);
  g_fread(header, 0x10, 1, f);
  if (header[0] != 0x53435245 || header[3] != 3) {   /* "ERCS" little-endian, version 3 */
    g_fseek(f, start, 0);
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
