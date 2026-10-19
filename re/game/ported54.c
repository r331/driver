/* ported54 — assorted leaf functions (Game.exe, cdecl unless noted): menu icon selection, Glide texture / clear /
   swap wrappers, road-bit and map buffer allocation, default key setup, two traffic-record steps, the
   IDirect3DTexture2 query and map.c chunk readers. */
#include "ported128.h"
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
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P54_IconIdx")
#undef P54_IconIdx
#pragma push_macro("P54_IconIdx") /*gvi*/
#undef P54_IconIdx /*gvi*/
p54_i32_t P54_IconIdx;
#pragma pop_macro("P54_IconIdx") /*gvi*/
#pragma pop_macro("P54_IconIdx")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P54_Out")
#undef P54_Out
#pragma push_macro("P54_Out") /*gvi*/
#undef P54_Out /*gvi*/
p54_out_t P54_Out;
#pragma pop_macro("P54_Out") /*gvi*/
#pragma pop_macro("P54_Out")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P54_KeySrc")
#undef P54_KeySrc
#pragma push_macro("P54_KeySrc") /*gvi*/
#undef P54_KeySrc /*gvi*/
p54_keysrc_t P54_KeySrc;
#pragma pop_macro("P54_KeySrc") /*gvi*/
#pragma pop_macro("P54_KeySrc")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P54_Keys3")
#undef P54_Keys3
#pragma push_macro("P54_Keys3") /*gvi*/
#undef P54_Keys3 /*gvi*/
p54_keys3_t P54_Keys3;
#pragma pop_macro("P54_Keys3") /*gvi*/
#pragma pop_macro("P54_Keys3")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P54_Dst")
#undef P54_Dst
#pragma push_macro("P54_Dst") /*gvi*/
#undef P54_Dst /*gvi*/
p54_dst_t P54_Dst;
#pragma pop_macro("P54_Dst") /*gvi*/
#pragma pop_macro("P54_Dst")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P54_Src6")
#undef P54_Src6
#pragma push_macro("P54_Src6") /*gvi*/
#undef P54_Src6 /*gvi*/
p54_src6_t P54_Src6;
#pragma pop_macro("P54_Src6") /*gvi*/
#pragma pop_macro("P54_Src6")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P54_RoadId")
#undef P54_RoadId
#pragma push_macro("P54_RoadId") /*gvi*/
#undef P54_RoadId /*gvi*/
p54_i4_t P54_RoadId;
#pragma pop_macro("P54_RoadId") /*gvi*/
#pragma pop_macro("P54_RoadId")
#endif
GAME_VAR_DEF(p54_p4_t, P54_RoadA, 0x00c4bdd0)
GAME_VAR_DEF(p54_p4_t, P54_RoadB, 0x00c1cc80)
GAME_VAR_DEF(p54_p4_t, P54_Tab4, 0x00c81b80)
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P54_MapA")
#undef P54_MapA
#pragma push_macro("P54_MapA") /*gvi*/
#undef P54_MapA /*gvi*/
int32_t P54_MapA;
#pragma pop_macro("P54_MapA") /*gvi*/
#pragma pop_macro("P54_MapA")
#endif
GAME_VAR_DEF(void *, P54_MapAPtr, 0x00b31ecc)
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P54_MapB1")
#undef P54_MapB1
#pragma push_macro("P54_MapB1") /*gvi*/
#undef P54_MapB1 /*gvi*/
int32_t P54_MapB1;
#pragma pop_macro("P54_MapB1") /*gvi*/
#pragma pop_macro("P54_MapB1")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P54_MapB2")
#undef P54_MapB2
#pragma push_macro("P54_MapB2") /*gvi*/
#undef P54_MapB2 /*gvi*/
int32_t P54_MapB2;
#pragma pop_macro("P54_MapB2") /*gvi*/
#pragma pop_macro("P54_MapB2")
#endif
GAME_VAR_DEF(void *, P54_MapBPtr, 0x00b5a908)
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P54_GridN")
#undef P54_GridN
#pragma push_macro("P54_GridN") /*gvi*/
#undef P54_GridN /*gvi*/
int32_t P54_GridN;
#pragma pop_macro("P54_GridN") /*gvi*/
#pragma pop_macro("P54_GridN")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P54_Cnt1E0")
#undef P54_Cnt1E0
#pragma push_macro("P54_Cnt1E0") /*gvi*/
#undef P54_Cnt1E0 /*gvi*/
int32_t P54_Cnt1E0;
#pragma pop_macro("P54_Cnt1E0") /*gvi*/
#pragma pop_macro("P54_Cnt1E0")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P54_G40")
#undef P54_G40
#pragma push_macro("P54_G40") /*gvi*/
#undef P54_G40 /*gvi*/
int32_t P54_G40;
#pragma pop_macro("P54_G40") /*gvi*/
#pragma pop_macro("P54_G40")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P54_G44")
#undef P54_G44
#pragma push_macro("P54_G44") /*gvi*/
#undef P54_G44 /*gvi*/
int32_t P54_G44;
#pragma pop_macro("P54_G44") /*gvi*/
#pragma pop_macro("P54_G44")
#endif

/* Entry point of a Glide export by its decorated name (from the loaded glide2x.dll export list), or NULL. */
static void *glide_proc(const char *name) {
  for (int i = 0; i < P33_GlideCount(); i++)
    if (strcmp(P33_GlideName(i), name) == 0) return P33_GlideProc(i);
  return NULL;
}

/* P54_MenuTexSel — Game.exe 0040500d.  Sets the icon of each menu row from P54_SelTab (terminated by -1):
   kinds 0..6 pick the icon of the current value of one menu option (MenuOpt*), kinds 7..9 fixed icons at
   0057b664/68/6c; the icon goes into word (i * 2 + 2) * 4 of P54_Out.  TODO(RE): unsure which options 0..6 are. */
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

/* P54_TexSource — Game.exe 004248c6.  Texture download for the active renderer: nothing if no device
   (D_00b1c0d4 == 0); renderer 0 = Glide: grTexDownloadMipMap(a, b, c, d); renderer 1 = D3D: P46_TexCall2. */
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

/* P54_ClearBuffers — Game.exe 0041de46 (stdcall, ret 0xc).  D3D clear: fills the back buffer with color (unless
   S_00A421D8) and clears the Z buffer to 1.0f (zsel 0 or -1) or 0 (other), unless Z writes are off.
   b is unused. */
void P54_ClearBuffers(int32_t color, int32_t b, int16_t zsel) {
  (void)b;
  if (P22_DevReady == 0) return;
  if (S_00A421D8 == 0) P24_FillBackbuffer(P24_Back, (uint32_t)color);
  if (P22_ZWriteOff == 0) {
    if (zsel == -1 || zsel == 0) P23_ClearZ(P31_DDObj3, 0x3f800000u);   /* 1.0f */
    else P23_ClearZ(P31_DDObj3, 0);
  }
}

/* P54_ClearSwap — Game.exe 0040c5be.  Glide: clip window = whole screen, then n times clear to black (depth
   0xffff) and swap — flushes all n buffers of the swap chain. */
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

/* P54_FreeTab4 — Game.exe 004f3c16.  Frees the four buffers of P54_Tab4 (TODO(RE): unsure what they hold). */
void P54_FreeTab4(void) {
  for (int i = 0; i < 4; i++) {
    if (P54_Tab4[i] != NULL) {
      DebugFree(P54_Tab4[i]);
      P54_Tab4[i] = NULL;
    }
    P54_Tab4[i] = NULL;
  }
}

/* P54_FreeRoadbits — Game.exe 0051aacd.  Frees the four road-bit buffer pairs (see P54_AllocRoadbits). */
void P54_FreeRoadbits(void) {
  for (int i = 0; i < 4; i++) {
    DebugFree(P54_RoadA[i]); P54_RoadA[i] = NULL;
    DebugFree(P54_RoadB[i]); P54_RoadB[i] = NULL;
  }
}

/* P54_AllocRoadbits — Game.exe 0051aa5b.  Allocates four road-bit cache slots: id -1 (empty), buffer A 0x7080
   bytes and buffer B 0xe100 bytes (road.c tags 0xc9 / 0xca).  0x7080 = 120 x 240; TODO(RE): unsure of the layout. */
void P54_AllocRoadbits(void) {
  for (int i = 0; i < 4; i++) {
    P54_RoadId[i] = -1;
    P54_RoadA[i] = DebugMalloc(0x7080, P54_ROAD_C, 0xc9);
    P54_RoadB[i] = DebugMalloc(0xe100, P54_ROAD_C, 0xca);
  }
}

/* P54_AllocMapBufs — Game.exe 004ecda8.  Allocates the level map buffers: G6_00D01268 = GridN^2 cells of 0x10
   bytes, G6_00D00208 = (P54_Cnt1E0 + 0x8000) entries of 0x20 bytes, G6_00CE0F20 = 0xa0000 bytes (map.c tags
   0x562..0x564).  TODO(RE): unsure what the latter two hold. */
void P54_AllocMapBufs(void) {
  G6_00D01268 = DebugMalloc(P54_GridN * P54_GridN * 0x10, P54_MAP_C, 0x562);
  G6_00D00208 = DebugMalloc((P54_Cnt1E0 + 0x8000) * 0x20, P54_MAP_C, 0x563);
  G6_00CE0F20 = DebugMalloc(0xa0000, P54_MAP_C, 0x564);
}

/* P54_DefaultKeys — Game.exe 0040748a.  Restores the default key bindings: the first 20 bytes of P54_KeySrc go to
   the active key config; keyboard mode (Q0057B72C == 0) also resets the second set (P54_KeySrc[6..]), a joystick
   mode only the three P54_Keys3 entries (from P54_KeySrc[12..14]).  Then 004072BE applies them.  Returns 0. */
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

/* P54_InitInputMode — Game.exe 0040724c.  Q0057B72C = 0 for keyboard (P35_InputMode == 0) or joystick number + 1
   (GetB31E18() + 1); copies six default values from P54_Src6 into P54_Dst[0, 4, 12, 16, 20, 24] and applies the
   bindings (004072BE).  TODO(RE): unsure what the six values are. */
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

/* P54_ObjTick — Game.exe 00493f9a.  Idle tick of a traffic record (0x54 bytes): clears byte +8; while the
   cool-down byte +0xb is non-zero it counts down; otherwise, when the record has a road link (+0x28 != -1),
   on average once per 32 ticks (random & 0x1f == record id) picks a new road node (P128_TrafficNode). */
void P54_ObjTick(uint8_t *o) {
  o[8] = 0;
  if (o[0xb] == 0) {
    int32_t link; memcpy(&link, o + 0x28, 4);
    if (link == -1) return;
    if ((Rand_004D9078() & 0x1f) == o[0]) P128_TrafficNode(o);
  } else {
    o[0xb]--;
  }
}

/* P54_ObjInit — Game.exe 00493e3d.  Re-initialises a traffic record at its stored position (+0x2c/+0x30/+0x34)
   via 004913CC(x, y, z, 2, byte +9), clears flag 0x04 of byte +0x13, copies P54_G40/P54_G44 into +0x40/+0x44,
   sets state byte +1 = 3 and clears byte +0x10.  TODO(RE): unsure what state 3 and the arguments mean. */
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

/* P54_GetTexture2 — Game.exe 0042200c.  QueryInterface(IID_IDirect3DTexture2) on a DirectDraw surface; returns
   the interface or NULL (also for a NULL surface). */
void *P54_GetTexture2(void *tex) {
  /* IID_IDirect3DTexture2 {93281502-8CF8-11D0-89AB-00A0C9054129} */
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

/* P54_ReadNames — Game.exe 004ec7ac.  Reads the level's name table chunk (size bytes) into a new buffer, which
   becomes P20_Names.  Allocation failure: the chunk is not read. */
void P54_ReadNames(void *file, int32_t size) {
  void *buf = DebugMalloc(size, P54_MAP_C, 0x415);
  if (buf == NULL) return;
  P27_ReadChunked(buf, size, 1, file);
  P20_Names = (char *)buf;
}

/* P54_ReadMapA — Game.exe 004ec280.  Chunk = [int32 count P54_MapA][data]; data goes to a new buffer
   P54_MapAPtr (count reset to 0 when the allocation fails). */
void P54_ReadMapA(void *file, int32_t size) {
  P27_ReadChunked(&P54_MapA, 4, 1, file);
  size -= 4;
  P54_MapAPtr = DebugMalloc(size, P54_MAP_C, 0x32c);
  if (P54_MapAPtr == NULL) P54_MapA = 0;
  else P27_ReadChunked(P54_MapAPtr, size, 1, file);
}

/* P54_ReadMapB — Game.exe 004ec3fd.  Chunk = [int32 P54_MapB1][int32 P54_MapB2][data] -> P54_MapBPtr (no NULL
   check, as the original). */
void P54_ReadMapB(void *file, int32_t size) {
  P27_ReadChunked(&P54_MapB1, 4, 1, file);
  P27_ReadChunked(&P54_MapB2, 4, 1, file);
  P54_MapBPtr = DebugMalloc(size - 8, P54_MAP_C, 0x371);
  P27_ReadChunked(P54_MapBPtr, 1, size - 8, file);
}
