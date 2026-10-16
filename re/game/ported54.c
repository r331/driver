#include "ported54.h"
#include "ported33.h"
#include <string.h>
#ifdef RE_HOOK_BUILD
#  define P54_STD __attribute__((stdcall))
#else
#  define P54_STD
#endif
#define P54_MAP_C  "D:\\Driver\\Game\\map.c"
#define P54_ROAD_C "D:\\Driver\\Game\\roadbits.c"
GAME_VAR_DEF(p54_i32_t, P54_IconIdx, 0x00549c60)
GAME_VAR_DEF(p54_out_t, P54_Out, 0x00549b08)
GAME_VAR_DEF(p54_keysrc_t, P54_KeySrc, 0x0054b7a8)
GAME_VAR_DEF(p54_keys3_t, P54_Keys3, 0x00d04a70)
GAME_VAR_DEF(p54_dst_t, P54_Dst, 0x00549f80)
GAME_VAR_DEF(p54_src6_t, P54_Src6, 0x00c55908)
GAME_VAR_DEF(p54_i4_t, P54_RoadId, 0x00c39da0)
GAME_VAR_DEF(p54_p4_t, P54_RoadA, 0x00c4bdd0)
GAME_VAR_DEF(p54_p4_t, P54_RoadB, 0x00c1cc80)
GAME_VAR_DEF(p54_p4_t, P54_Tab4, 0x00c81b80)
GAME_VAR_DEF(int32_t, P54_MapA, 0x00b31ed4)
GAME_VAR_DEF(void *, P54_MapAPtr, 0x00b31ecc)
GAME_VAR_DEF(int32_t, P54_MapB1, 0x00c1ed60)
GAME_VAR_DEF(int32_t, P54_MapB2, 0x00c1cc68)
GAME_VAR_DEF(void *, P54_MapBPtr, 0x00b5a908)
GAME_VAR_DEF(int32_t, P54_GridN, 0x00c98ecc)
GAME_VAR_DEF(int32_t, P54_Cnt1E0, 0x00d001e0)
GAME_VAR_DEF(int32_t, P54_G40, 0x01139a30)
GAME_VAR_DEF(int32_t, P54_G44, 0x01139a2c)

static void *glide_proc(const char *name) {
  for (int i = 0; i < P33_GlideCount(); i++)
    if (strcmp(P33_GlideName(i), name) == 0) return P33_GlideProc(i);
  return NULL;
}

void P54_MenuTexSel(void) {
  /* Ограничение i < 12 (v1.58: размер 0057b578..0057b5a8) — защита от таблицы без конца (в оригинале конец всегда -1). */
  for (int32_t i = 0; i < (int32_t)(sizeof(p54_i16_t) / 4); i++) {
    int32_t opt;
    switch (P54_SelTab[i]) {
    case 0: opt = MenuOptBDFA44; break;
    case 1: opt = MenuOptBDFA48; break;
    case 2: opt = MenuOptBDFA4C; break;
    case 3: opt = MenuOptBDFA50; break;
    case 4: opt = MenuOptBDFA54; break;
    case 5: opt = MenuOptB87E9C; break;
    case 6: opt = MenuOptBDFA58; break;
    case 7: P54_Out[(i * 2 + 2) * 4] = 0x0057b664u; continue;
    case 8: P54_Out[(i * 2 + 2) * 4] = 0x0057b668u; continue;
    case 9: P54_Out[(i * 2 + 2) * 4] = 0x0057b66cu; continue;
    case -1: return;
    default: continue;
    }
    P54_Out[(i * 2 + 2) * 4] = P12_00c55820[P54_IconIdx[opt]];
  }
}

void P54_TexSource(int32_t a, int32_t b, int32_t c, const uint8_t *d, int32_t e) {
  if (D_00b1c0d4 == 0) return;
  if (D_00b1c0d8 == 0) {
    void (P54_STD *f)(int32_t, int32_t, int32_t, const uint8_t *) =
        (void (P54_STD *)(int32_t, int32_t, int32_t, const uint8_t *))glide_proc("_grTexDownloadMipMap@16");
    if (f) f(a, b, c, d);
  } else if (D_00b1c0d8 == 1) {
    P46_TexCall2(a, b, c, d, e);
  }
}

void P54_ClearBuffers(int32_t color, int32_t b, int16_t zsel) {
  (void)b;
  if (P22_DevReady == 0) return;
  if (S_00A421D8 == 0) P24_FillBackbuffer(P24_Back, (uint32_t)color);
  if (P22_ZWriteOff == 0) {
    if (zsel == -1 || zsel == 0) P23_ClearZ(P31_DDObj3, 0x3f800000u);   /* 1.0f */
    else P23_ClearZ(P31_DDObj3, 0);
  }
}

void P54_ClearSwap(int32_t n) {
  void (P54_STD *clip)(int32_t, int32_t, int32_t, int32_t) =
      (void (P54_STD *)(int32_t, int32_t, int32_t, int32_t))glide_proc("_grClipWindow@16");
  void (P54_STD *clear)(int32_t, int32_t, int32_t) =
      (void (P54_STD *)(int32_t, int32_t, int32_t))glide_proc("_grBufferClear@12");
  void (P54_STD *swap)(int32_t) = (void (P54_STD *)(int32_t))glide_proc("_grBufferSwap@4");
  if (clip) clip(0, 0, P19_ScrW, P19_ScrH);
  for (int32_t i = 0; i < n; i++) {
    if (clear) clear(0, 0, 0xffff);
    if (swap) swap(0);
  }
}

void P54_FreeTab4(void) {
  for (int i = 0; i < 4; i++) {
    if (P54_Tab4[i] != NULL) {
      DebugFree(P54_Tab4[i]);
      P54_Tab4[i] = NULL;
    }
    P54_Tab4[i] = NULL;
  }
}

void P54_FreeRoadbits(void) {
  for (int i = 0; i < 4; i++) {
    DebugFree(P54_RoadA[i]); P54_RoadA[i] = NULL;
    DebugFree(P54_RoadB[i]); P54_RoadB[i] = NULL;
  }
}

void P54_AllocRoadbits(void) {
  for (int i = 0; i < 4; i++) {
    P54_RoadId[i] = -1;
    P54_RoadA[i] = DebugMalloc(0x7080, P54_ROAD_C, 0xc9);
    P54_RoadB[i] = DebugMalloc(0xe100, P54_ROAD_C, 0xca);
  }
}

void P54_AllocMapBufs(void) {
  G6_00D01268 = DebugMalloc(P54_GridN * P54_GridN * 0x10, P54_MAP_C, 0x562);
  G6_00D00208 = DebugMalloc((P54_Cnt1E0 + 0x8000) * 0x20, P54_MAP_C, 0x563);
  G6_00CE0F20 = DebugMalloc(0xa0000, P54_MAP_C, 0x564);
}

int32_t P54_DefaultKeys(void) {
  if (Q0057B72C == 0) {
    memcpy(P36_KeyCfg, &P54_KeySrc[0], 20);
    memcpy(&P54_KeySrc[6], &P54_KeySrc[0], 20);
  } else {
    memcpy(P36_KeyCfg, &P54_KeySrc[0], 20);
    P54_Keys3[0] = P54_KeySrc[12];
    P54_Keys3[1] = P54_KeySrc[13];
    P54_Keys3[2] = P54_KeySrc[14];
  }
  Call004072BE();
  return 0;
}

void P54_InitInputMode(void) {
  if (P35_InputMode == 0) Q0057B72C = 0;
  else Q0057B72C = GetB31E18() + 1;
  P54_Dst[0] = P54_Src6[0];
  P54_Dst[4] = P54_Src6[1];
  P54_Dst[12] = P54_Src6[2];
  P54_Dst[16] = P54_Src6[3];
  P54_Dst[20] = P54_Src6[4];
  P54_Dst[24] = P54_Src6[5];
  Call004072BE();
}

void P54_ObjTick(uint8_t *o) {
  o[8] = 0;
  if (o[0xb] == 0) {
    int32_t link; memcpy(&link, o + 0x28, 4);
    if (link == -1) return;
    if ((Rand_004D9078() & 0x1f) == o[0]) N54_Fn4949F0(o);
  } else {
    o[0xb]--;
  }
}

void P54_ObjInit(uint8_t *o) {
  int32_t x, y, z;
  memcpy(&x, o + 0x2c, 4); memcpy(&y, o + 0x30, 4); memcpy(&z, o + 0x34, 4);
  N54_Fn4913CC(x, y, z, 2, o[9]);
  o[0x13] &= 0xfb;
  memcpy(o + 0x40, &P54_G40, 4);
  memcpy(o + 0x44, &P54_G44, 4);
  o[1] = 3;
  o[0x10] = 0;
}

void *P54_GetTexture2(void *tex) {
  static const uint8_t iid_tex2[16] = { 0x02,0x15,0x28,0x93,0xf8,0x8c,0xd0,0x11,0x89,0xab,0x00,0xa0,0xc9,0x05,0x41,0x29 };
  void *out = NULL;
  NoopFn0042243f();   /* «GetDirect3DTexture2Interface» (в релизе — пусто) */
  if (tex == NULL) return NULL;
  if (plat_com_query_interface(tex, iid_tex2, &out) != 0) {
    NoopFn0042243f();
    return NULL;
  }
  return out;
}

void P54_ReadNames(void *file, int32_t size) {
  void *buf = DebugMalloc(size, P54_MAP_C, 0x415);
  if (buf == NULL) return;
  P27_ReadChunked(buf, size, 1, file);
  P20_Names = (char *)buf;
}

void P54_ReadMapA(void *file, int32_t size) {
  P27_ReadChunked(&P54_MapA, 4, 1, file);
  size -= 4;
  P54_MapAPtr = DebugMalloc(size, P54_MAP_C, 0x32c);
  if (P54_MapAPtr == NULL) P54_MapA = 0;
  else P27_ReadChunked(P54_MapAPtr, size, 1, file);
}

void P54_ReadMapB(void *file, int32_t size) {
  P27_ReadChunked(&P54_MapB1, 4, 1, file);
  P27_ReadChunked(&P54_MapB2, 4, 1, file);
  P54_MapBPtr = DebugMalloc(size - 8, P54_MAP_C, 0x371);
  P27_ReadChunked(P54_MapBPtr, 1, size - 8, file);
}
