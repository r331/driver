/* Функции с 32-битными указателями в таблицах/списках/записях — восстановлено из Game.exe по стандарту v1.42
   (0051c900, 00523cda, 004a681a, 005074e5, 0048bbd5, 004d9ad4, 0050bc2b, 004f4f10, 004cff7e, 004cf6b2, 004cf772, 004d156a,
   00500090, 0050f7b2, 0040fc9a, 00410e89, 0040ea70, 00419b35, 0040c8a0, 004185d2, 004f58c6, 004f57d7, 004f5c89, 004d2c95,
   004c2ab0, 00417479, 00417fff, 004afcf7, 004ad128, 004e5a1a). */
#include "ported97.h"
#include "reptr.h"
#include "director.h"
#include "menustate.h"
#include "smallfuncs.h"
#include "smallfuncs2.h"
#include "uihandlers3.h"
#include "widgets.h"
#include "ported4.h"
#include "ported5.h"
#include "ported6.h"
#include "ported7.h"
#include "ported10.h"
#include "ported11.h"
#include "ported12.h"
#include "ported14.h"
#include "ported15.h"
#include "ported16.h"
#include "ported19.h"
#include "ported21.h"
#include "ported25.h"
#include "ported28.h"
#include "ported29.h"
#include "ported42.h"
#include "ported43.h"
#include "ported44.h"
#include "ported47.h"
#include "ported48.h"
#include "ported54.h"
#include "ported56.h"
#include "ported57.h"
#include "ported58.h"
#include "ported59.h"
#include "ported62.h"
#include "ported68.h"
#include "ported77.h"
#include "ported91.h"
#include "ported94.h"
#include "ported95.h"
#include "ported96.h"
#include "unported.h"
#include <math.h>
#include <stdio.h>
#include <string.h>

GAME_VAR_DEF(p97_strtab_t, P97_StrAddr, 0x00c55820)
GAME_VAR_DEF(re_fn_t, P97_DrvA, 0x00bdcb10)
GAME_VAR_DEF(re_fn_t, P97_DrvB, 0x00bdcb1c)
GAME_VAR_DEF(re_fn_t, P97_DrvC, 0x00bdcb28)
GAME_VAR_DEF(re_fn_t, P97_DrvD, 0x00bdcb30)
GAME_VAR_DEF(re_fn_t, P97_DrvE, 0x00bdcb34)
GAME_VAR_DEF(re_fn_t, P97_DrvF, 0x00bdcb3c)
GAME_VAR_DEF(re_fn_t, P97_DrvG, 0x00bdcb44)
GAME_VAR_DEF(re_fn_t, P97_DrvH, 0x00bdcb48)
GAME_VAR_DEF(re_fn_t, P97_DrvI, 0x00bdcb4c)
GAME_VAR_DEF(re_fn_t, P97_DrvJ, 0x00bdcb50)
GAME_VAR_DEF(re_fn_t, P97_DrvK, 0x00bdcb58)
GAME_VAR_DEF(re_fn_t, P97_DrvL, 0x00bdcb5c)
GAME_VAR_DEF(p97_lfblock_fn, P97_LfbLock, 0x01270e60)
GAME_VAR_DEF(p97_gr5_fn, P97_GrAlpha, 0x01270dcc)
GAME_VAR_DEF(p97_gr1_fn, P97_GrDepth, 0x01270d68)
GAME_VAR_DEF(int32_t, P97_ScrObjOn, 0x00c81270)
GAME_VAR_DEF(p97_sndmenu_t, P97_SndMenu, 0x00574f38)
GAME_VAR_DEF(p97_menuA_t, P97_KeyMenuA, 0x0054c030)
GAME_VAR_DEF(p97_menuB_t, P97_KeyMenuB, 0x0054c350)
GAME_VAR_DEF(p97_menuC_t, P97_OptMenuA, 0x0054acc0)
GAME_VAR_DEF(p97_menuC_t, P97_OptMenuB, 0x0054e560)
GAME_VAR_DEF(p97_txt32_t, P97_FpsTxtA, 0x005fe4e4)
GAME_VAR_DEF(p97_txt32_t, P97_FpsTxtB, 0x005fea74)
GAME_VAR_DEF(p97_txt64_t, P97_MsgBuf, 0x00c80c60)
GAME_VAR_DEF(int32_t, P97_C810A8, 0x00c810a8)
GAME_VAR_DEF(int32_t, P97_C81490, 0x00c81490)
GAME_VAR_DEF(int32_t, P97_IconL, 0x005fea3c)
GAME_VAR_DEF(int32_t, P97_IconR, 0x005fea40)
GAME_VAR_DEF(p97_debris_t, P97_Debris, 0x010fb220)
GAME_VAR_DEF(uint8_t *, P97_FadeIcon, 0x00d04788)
GAME_VAR_DEF(int32_t, P97_B2A8, 0x0112b2a8)
GAME_VAR_DEF(int32_t, P97_B2A4, 0x0112b2a4)
GAME_VAR_DEF(int32_t, P97_B2A0, 0x0112b2a0)
GAME_VAR_DEF(int32_t, P97_129584, 0x01129584)
GAME_VAR_DEF(int32_t, P97_B274, 0x0112b274)
GAME_VAR_DEF(int32_t, P97_B2B0, 0x0112b2b0)
GAME_VAR_DEF(int32_t, P97_D9DC, 0x0112d9dc)
GAME_VAR_DEF(int32_t, P97_D9D8, 0x0112d9d8)
GAME_VAR_DEF(int32_t, P97_B264, 0x0112b264)
GAME_VAR_DEF(int32_t, P97_B260, 0x0112b260)
GAME_VAR_DEF(int32_t, P97_B290, 0x0112b290)
GAME_VAR_DEF(int32_t, P97_B214, 0x0112b214)
GAME_VAR_DEF(int32_t, P97_D9E0, 0x0112d9e0)
GAME_VAR_DEF(int32_t, P97_B28C, 0x0112b28c)
GAME_VAR_DEF(int32_t, P97_B288, 0x0112b288)
GAME_VAR_DEF(p97_b2c0_t, P97_B2C0, 0x0112b2c0)
GAME_VAR_DEF(p97_b220_t, P97_B220, 0x0112b220)
GAME_VAR_DEF(p97_d11980_t, P97_D11980, 0x00d11980)
GAME_VAR_DEF(uint16_t, P97_D11A44, 0x00d11a44)

#ifndef RE_HOOK_BUILD
/* .data Game.exe — в native начальные значения (прочитаны из Game.exe) */
p97_pat_t P97_CellPat = {                                                         /* 00574674: 8 типов по 3×3 */
  0,0,0,0,0,0,1,1,1, 0,0,0,1,0,0,1,1,0, 1,0,0,1,0,0,1,0,0, 1,1,0,1,0,0,0,0,0,
  1,1,1,0,0,0,0,0,0, 0,1,1,0,0,1,0,0,0, 0,0,1,0,0,1,0,0,1, 0,0,0,0,0,1,0,1,1 };
p97_u4_t P97_OnOff = { 2, 1, 2, 6 };
p97_u2_t P97_BitsStr = { 0x005755ecu, 0x005755f4u };
p97_u2_t P97_RateStr = { 0x005755fcu, 0x00575608u };
p97_u4_t P97_SpkStr = { 0xec, 0xed, 0xee, 0xef };
p97_s8_t P97_Str8bit = "8bit";
p97_s8_t P97_Str16bit = "16bit";
p97_s12_t P97_Str22k = "22050KHz";
p97_s12_t P97_Str44k = "44100KHz";
p97_i6_t P97_OptTabA = { 2, 1, 9, 10, 11, 29477 };
p97_i6_t P97_OptTabB = { 2, 1, 9, 10, 11, -1 };
p97_i2_t P97_BlinkA = { 50, 20 };
p97_i2_t P97_BlinkB = { 50, 20 };
#endif

void P97_InitConsts(void) {
#ifndef RE_HOOK_BUILD
  P97_BlinkA[0] = 50; P97_BlinkA[1] = 20; P97_BlinkB[0] = 50; P97_BlinkB[1] = 20;
#endif
}

static int32_t rd32(const uint8_t *p) { int32_t v; memcpy(&v, p, 4); return v; }
static void wr32(uint8_t *p, int32_t v) { memcpy(p, &v, 4); }
static uint16_t rd16(const uint8_t *p) { uint16_t v; memcpy(&v, p, 2); return v; }
static void wr16(uint8_t *p, uint16_t v) { memcpy(p, &v, 2); }
static float rdf(const uint8_t *p) { float v; memcpy(&v, p, 4); return v; }
static void wrf(uint8_t *p, float v) { memcpy(p, &v, 4); }
static int32_t fround(float v) { return (int32_t)lrintf(v); }                   /* fistp (округление к ближайшему) */
static const char *str_at(uint32_t a) { const char *s = (const char *)re_ptr(a); return s ? s : ""; }
static uint8_t *link(const uint8_t *field) { return (uint8_t *)re_rd_ptr(field); }  /* поле-указатель записи */

/* ---- 0051c900: таблица указателей таблиц рекордов (адреса Game.exe) ---- */
void P97_HsInit(void) {
  memset(P42_HighScores, 0, 0x80);
  memset(P62_Hs1, 0, 0x6e0); memset(P62_Hs2, 0, 0x6e0);
  memset(P62_Hs3, 0, 0x370); memset(P62_Hs4, 0, 0x370); memset(P62_Hs5, 0, 0x370); memset(P62_Hs6, 0, 0xb0);
  for (int32_t i = 0; i < 8; i++) P42_HighScores[i] = (int32_t)re_addr(P62_Hs1 + i * 0xdc);
  for (int32_t i = 0; i < 8; i++) P42_HighScores[8 + i] = (int32_t)re_addr(P62_Hs2 + i * 0xdc);
  for (int32_t i = 0; i < 4; i++) P42_HighScores[16 + i] = (int32_t)re_addr(P62_Hs3 + i * 0xdc);
  for (int32_t i = 0; i < 4; i++) {
    P42_HighScores[20 + i] = (int32_t)re_addr(P62_Hs4 + i * 0xdc);
    P42_HighScores[28 + i] = (int32_t)re_addr(P62_Hs6 + i * 0x2c);
  }
  for (int32_t i = 0; i < 4; i++) P42_HighScores[24 + i] = (int32_t)re_addr(P62_Hs5 + i * 0xdc);
}

/* ---- 00523cda: запуск сэмпла (номер или банк<<12|номер) на голосе; -1 — свободный/вытесняемый по приоритету ---- */
int32_t P97_SndStart(uint32_t sample, int32_t voice, float a, float b, float c) {
  if (G6_00B91CF4 == 0 || G00575F40 == 0) return -1;
  int32_t s = (int32_t)sample;
  if (0xfff < s) s = (int32_t)(sample & 0xff) + G6_00B91BC4[(s >> 0xc) & 0xf];
  if (s < 0 || G6_00B91D34 <= s) return -1;
  if ((P48_Samples[s * 8] & 4) != 0) return -1;
  if (voice == -1) {
    int32_t best = -1;
    for (voice = 0x13; -1 < voice; voice--) {
      const uint8_t *v = &S_00BDC2A0[voice * 0x34];
      if (v[1] == 0) {
        if ((v[0] & 0x11) == 0) break;
        if (P48_Samples[s * 8 + 1] <= v[0x33]) best = voice;
      }
    }
    if (voice == -1) voice = best;
  }
  if (voice == -1) return -1;
  P97_Fn52498E(voice, s, a, b, c);
  return voice;
}

/* ---- 004a681a: сброс машин/трафика (8 записей 0xcd8 по 0112da00) ---- */
void P97_ResetCars(void) {
  P77_ResetTables();
  P14_Fn0048DB65(P97_B2C0, 10000);
  P97_B2A8 = 0; P97_B2A4 = 0; P97_B2A0 = 0; P97_129584 = 0; P97_B274 = 0; P97_B2B0 = 0; G0112B280 = 0;
  P97_D9DC = 0; P97_D9D8 = 0; P97_B264 = 0; P97_B260 = 0; P62_Max = 0; P95_112D9D4 = 0; P97_B290 = 0; P95_AmbN = 0;
  G0112B284 = 0; P68_D11A48 = 0; P97_B214 = -1; P95_SndReady = 0; P95_D1197C = 0;
  P97_D9E0 = (G6_00B87EAC == 0 && G6_00B87EB0 == 0) ? 1 : 0;
  P47_Flag = 1; P97_B28C = 0; P97_B288 = 0; P77_C7D850 = 0;
  for (int32_t i = 0; i < 8; i++) {
    uint32_t *c = &P12_0112da00[i * 0x336];
    P14_Fn0048DB65(c, 0xcd8);
    c[0] = (uint32_t)i; c[0x32d] = 0; c[0x32e] = 0;
  }
  P95_AmbN = 0; G0112B280 = 0x201; P97_B290 = 0; D_00d1193c = -1;
  FillThresholds_004A6370(P97_B220);
  P95_SndInit(P97_D11980);
#ifdef RE_HOOK_BUILD
  FillRange004D2B16((uint16_t *)&P95_SndRate);
#else
  { uint16_t t[3]; FillRange004D2B16(t); memcpy(&P95_SndRate, t, 4); P97_D11A44 = t[2]; }
#endif
  P62_Max = 0;
  P12_Fn0050C010();
}

/* ---- 005074e5: значок на карте (P56_Sprite) с обводкой: обратный цвет режимом 2, цвет режимом 3 ---- */
void P97_MapIcon(float x, float y, uint32_t r, uint32_t g, uint32_t b, float scale) {
  if (P56_Sprite == NULL) return;
  float s = 0.0015625f * (float)P19_ScrW * P19_Scale * scale;
  float h = s * 0.5f;
  P57_ScreenToView(&x, &y);
  x = x - (float)P56_Sprite[0xb] * h;
  y = y - (float)P56_Sprite[0xc] * h;
  P56_DrawSpr(x, y, s, s, P56_Sprite, (int32_t)(0xff - (r & 0xff)), (int32_t)(0xff - (g & 0xff)), (int32_t)(0xff - (b & 0xff)), 2);
  P56_DrawSpr(x, y, s, s, P56_Sprite, (int32_t)(r & 0xff), (int32_t)(g & 0xff), (int32_t)(b & 0xff), 3);
}

/* ---- 0048bbd5: таблица звукового драйвера DirectSound (00bdcb00..00bdcb5c) через re_fn ---- */
void P97_SndDrvInit(void) {
  P48_Drv00 = (P48_F0)re_fn(0x0048bcc0);
  P48_Drv08 = (P48_F0)re_fn(0x0048bd3b);
  P48_Drv0C = (P48_F0)re_fn(0x0048bd40);
  P97_DrvA = re_fn(0x0048bd65);
  G6_00BDCB14 = (FnV2)re_fn(0x0048bdcc);
  G6_00BDCB18 = (FnV1)re_fn(0x0048be68);
  P97_DrvB = re_fn(0x0048beee);
  G6_00BDCB20 = (FnV1)re_fn(0x0048bf52);
  P68_DrvLoad = (P68_FLoad)re_fn(0x0048bf9a);
  P97_DrvC = re_fn(0x0048c2a3);
  P48_Drv2C = (P48_F1)re_fn(0x0048c520);
  P97_DrvD = re_fn(0x0048c74b);
  P97_DrvE = re_fn(0x0048c77e);
  P48_Drv38 = (P48_F3)re_fn(0x0048c7bd);
  P97_DrvF = re_fn(0x0048c7f0);
  P48_Drv40 = (P48_F1)re_fn(0x0048c83d);
  P97_DrvG = re_fn(0x0048c8d6);
  P97_DrvH = re_fn(0x0048c97c);
  P97_DrvI = re_fn(0x0048c9b2);
  P97_DrvJ = re_fn(0x0048c9e8);
  P48_Drv54 = (P48_F4)re_fn(0x0048ca28);
  P97_DrvK = re_fn(0x0048ca68);
  P97_DrvL = re_fn(0x0048caa0);
}

/* ---- 004d9ad4: снимок кадра через grLfbLock: RGB565 → BGR, строки снизу вверх ---- */
typedef struct { uint32_t size; void *lfb; uint32_t stride; uint32_t mode; uint32_t origin; } p97_lfbinfo_t;
void P97_LfbSnap(uint8_t *out) {
  p97_lfbinfo_t info; memset(&info, 0, sizeof info);
  info.size = 0x14;
#ifndef RE_HOOK_BUILD
  if (P97_LfbLock == NULL) return;
#endif
  P97_LfbLock(0, 0, 0xff, 0, 0, &info);
  const uint8_t *row = (const uint8_t *)info.lfb + (P19_ScrH - 1) * (int32_t)(info.stride >> 1) * 2;
  for (int32_t y = 0; y < P19_ScrH; y++) {
    const uint8_t *p = row;
    for (int32_t x = 0; x < P19_ScrW; x++) {
      uint16_t v = rd16(p); p += 2;
      out[0] = (uint8_t)((v & 0x1f) << 3);
      out[1] = (uint8_t)((v & 0x7e0) >> 3);
      out[2] = (uint8_t)((v >> 8) & 0xf8);
      out += 3;
    }
    row -= info.stride & 0xfffffffeu;
  }
#ifndef RE_HOOK_BUILD
  if (FnPtr01270EAC == NULL) return;
#endif
  FnPtr01270EAC(0, 0);
}

/* ---- 0050bc2b: +0x20 в клетках 3×3 вокруг 0x5e8 сетки 00c62e60 по шаблону типа записи списка +0x60 ---- */
void P97_MarkCells(uint8_t *rec) {
  uint8_t *p = rec + 0x60;
  int32_t n = rd32(rec + 0x14) - 1 + P77_C65DA4;
  while (n != 0) { p = link(p); n--; }
  const uint8_t *pat = &P97_CellPat[(uint32_t)p[0x1e] * 9];
  for (int32_t i = 0; i < 9; i++) {
    if (pat[i] != 0) {
      int32_t idx = 0x5e8 + (i % 3 - 1) + (i / 3 - 1) * 0x37;
      wr32(P77_C62E60 + idx * 4, rd32(P77_C62E60 + idx * 4) + 0x20);
    }
  }
}

/* ---- список скрипта 00d12408: узел 0x24 (+0 флаги16, +6 id16, +0x1c первый объект, +0x20 следующий),
        объект 0x60 (+0x50 база, +0x54 указатель в базе, +0x58 следующий) — поля-указатели = адреса Game.exe ---- */
void P97_ObjsFromScript(void) {
  if (P97_ScrObjOn == 0) return;
  for (int32_t k = 0; k < 10; k++) {
    uint8_t *o = P58_Objs[k];
    uint32_t f = (uint32_t)rd32(o + 0x10);
    if ((f & 1) == 0 || (f & 8) == 0) continue;
    for (uint8_t *n = P15_ListHead; n != NULL; n = link(n + 0x20)) {
      if ((rd16(n) & 8) != 0 && (uint32_t)rd16(n + 6) == (uint32_t)rd32(o + 0xc)) {
        uint8_t *c = link(n + 0x1c);
        if (c != NULL) {
          P11_00ba52d0 = fround(rdf(c)); wr32(o + 0x14, P11_00ba52d0);
          P11_00ba52d0 = fround(rdf(c + 8)); wr32(o + 0x1c, P11_00ba52d0);
        }
        break;
      }
    }
  }
}
void P97_ScriptResetCur(void) {
  uint8_t *cur = P15_ListCur;
  uint8_t *c = link(cur + 0x1c);
  wr16(cur, (uint16_t)(rd16(cur) | 2));
  for (; c != NULL; c = link(c + 0x58)) {
    wr32(c + 8, 0); wr32(c + 4, 0); wr32(c, 0);
    wr32(c + 0x30, 0); wr32(c + 0x2c, 0); wr32(c + 0x28, 0);
    wr16(c + 0x14, 0); wr16(c + 0x12, 0); wr16(c + 0x10, 0); wr16(c + 0x48, 0);
    wr32(c + 0x54, rd32(c + 0x50));
  }
}
int32_t P97_ScriptSave(uint8_t *out) {
  int32_t total = 0;
  for (uint8_t *n = P15_ListHead; n != NULL; n = link(n + 0x20)) {
    memcpy(out, n, 0x24); out += 0x24; total += 0x24;
    for (uint8_t *c = link(n + 0x1c); c != NULL; c = link(c + 0x58)) {
      wr32(c + 0x54, rd32(c + 0x54) - rd32(c + 0x50));
      memcpy(out, c, 0x60); out += 0x60; total += 0x60;
      wr32(c + 0x54, rd32(c + 0x54) + rd32(c + 0x50));
    }
  }
  return total;
}
void P97_ScriptLoad(const uint8_t *in) {
  for (uint8_t *n = P15_ListHead; n != NULL; n = link(n + 0x20)) {
    int32_t h = rd32(n + 0x1c), nx = rd32(n + 0x20);
    memcpy(n, in, 0x24);
    wr32(n + 0x20, nx); wr32(n + 0x1c, h);
    in += 0x24;
    for (uint8_t *c = link(n + 0x1c); c != NULL; c = link(c + 0x58)) {
      int32_t base = rd32(c + 0x50), cn = rd32(c + 0x58);
      memcpy(c, in, 0x60);
      in += 0x60;
      wr32(c + 0x58, cn); wr32(c + 0x50, base);
      wr32(c + 0x54, rd32(c + 0x54) + rd32(c + 0x50));
    }
  }
}
/* 004d156a: операция скрипта — переход к следующему узлу (если он с флагом 0x20 — к id+1 текущего) */
int32_t P97_ScriptOpNext(void) {
  P10_ScriptPtr += 2;
  uint16_t c = rd16(P10_ScriptPtr);
  P10_ScriptPtr += 2;
  uint8_t *nx = link(P15_ListCur + 0x20);
  if (nx != NULL && (rd16(nx) & 0x20) != 0) c = (uint16_t)(rd16(P15_ListCur + 6) + 1);
  else if (c == 0) return 1;
  P65_Fn4CFE69(c);
  return 1;
}
/* 00500090: обход активных объектов скрипта → 00500937 (модель события из P28_EventModels как адрес) */
void P97_ScriptEach(int32_t a, int32_t b, int32_t c) {
  for (uint8_t *n = P15_ListHead; n != NULL; n = link(n + 0x20)) {
    if ((rd16(n) & 2) == 0) continue;
    for (uint8_t *o = link(n + 0x1c); o != NULL; o = link(o + 0x58)) {
      if ((rd16(o + 0x48) & 0x200) != 0) continue;
      uint8_t tmp[0x1c]; memset(tmp, 0, sizeof tmp);
      uint16_t m = rd16(o + 0x4a);
      wr32(tmp + 4, m);
      memcpy(tmp + 8, o, 16);
      wr32(tmp + 0x18, (int16_t)rd16(o + 0x12));
      P53_Fn500937(tmp, a, b, c, (int32_t)P28_EventModels[m], 0);
    }
  }
}

/* ---- строки меню: в полях +8 пунктов (шаг 0x10/0x20/0x28) лежат адреса строк ---- */
void P97_SndMenuInit(void) {
  uint32_t bits = (uint32_t)(G6_00575F00 != 8), rate = (uint32_t)(G6_00575F04 != 0x5622);
  P48_SetMasterVolume(WF00575F14);
  P11_00ba52d0 = (int32_t)lrint((double)WF00575F18 * 65535.0);
  P25_CDSetVolume((uint32_t)P11_00ba52d0);
  wr32(P97_SndMenu + 0x00, (int32_t)P97_OnOff[G00575F40]);
  wr32(P97_SndMenu + 0x28, (int32_t)P97_OnOff[Q00B87E90]);
  wr32(P97_SndMenu + 0x50, (int32_t)P97_OnOff[Q00B87E94]);
  wr32(P97_SndMenu + 0x78, (int32_t)P97_BitsStr[bits]);
  wr32(P97_SndMenu + 0xa0, (int32_t)P97_RateStr[rate]);
  wr32(P97_SndMenu + 0xc8, (int32_t)P97_SpkStr[G6_00B87E50]);
}
#define S(i) ((int32_t)P97_StrAddr[i])
static void ka(uint32_t addr, int32_t v) { wr32(P97_KeyMenuA + (addr - 0x0054c030u), v); }
static int32_t key3(int k) { return (int32_t)re_addr(P21_GetNameByIndex(((const uint8_t *)P54_Keys3)[k])); }
void P97_KeyMenuAInit(void) {
  ka(0x0054c038, S(0x42)); ka(0x0054c048, S(0x46)); ka(0x0054c068, S(0x48)); ka(0x0054c088, S(0x47));
  ka(0x0054c0c8, S(0x45)); ka(0x0054c0a8, S(0x49)); ka(0x0054c0e8, S(0x4d)); ka(0x0054c108, S(0x4e));
  ka(0x0054c128, S(0xe6)); ka(0x0054c148, S(0x126)); ka(0x0054c168, S(0x4a)); ka(0x0054c188, S(0x4b));
  ka(0x0054c1a8, S(0x4c));
  ka(0x0054c058, key3(0)); ka(0x0054c078, key3(1)); ka(0x0054c0d8, key3(2)); ka(0x0054c098, key3(4));
  ka(0x0054c0b8, key3(3)); ka(0x0054c0f8, key3(8)); ka(0x0054c118, key3(9)); ka(0x0054c138, key3(10));
  ka(0x0054c158, key3(11)); ka(0x0054c178, key3(6)); ka(0x0054c198, key3(7)); ka(0x0054c1b8, key3(5));
  ka(0x0054c1c8, S(0xd1));
}
static void kb(uint32_t addr, int32_t v) { wr32(P97_KeyMenuB + (addr - 0x0054c350u), v); }
static int32_t keyd(int k) { return (int32_t)MenuTableGet54B010(((const uint8_t *)P54_KeySrc)[0x1c + k]); }
void P97_KeyMenuBInit(void) {
  kb(0x0054c358, S(0x42)); kb(0x0054c368, S(0x43)); kb(0x0054c388, S(0x44)); kb(0x0054c3a8, S(0x45));
  kb(0x0054c3c8, S(0x46)); kb(0x0054c3e8, S(0x48)); kb(0x0054c408, S(0x4d)); kb(0x0054c428, S(0x4e));
  kb(0x0054c448, S(0x47)); kb(0x0054c468, S(0x49)); kb(0x0054c488, S(0xe6)); kb(0x0054c4c8, S(0x4a));
  kb(0x0054c4e8, S(0x4b)); kb(0x0054c508, S(0x4c)); kb(0x0054c4a8, S(0x126));
  kb(0x0054c378, keyd(0)); kb(0x0054c398, keyd(1)); kb(0x0054c3b8, keyd(4)); kb(0x0054c3d8, keyd(2));
  kb(0x0054c3f8, keyd(3)); kb(0x0054c418, keyd(10)); kb(0x0054c438, keyd(11)); kb(0x0054c458, keyd(6));
  kb(0x0054c478, keyd(5)); kb(0x0054c498, keyd(12)); kb(0x0054c4d8, keyd(7)); kb(0x0054c4f8, keyd(8));
  kb(0x0054c518, keyd(9)); kb(0x0054c4b8, keyd(13));
}
static void opt_menu(uint8_t *m, uint32_t base, char *buf, const int32_t *tab) {
  if (P21_FrameFlagB == 0) snprintf(buf, 0x20, "%s", str_at(P97_StrAddr[2]));
  else if (P21_FrameFlagA == 0) snprintf(buf, 0x20, "%dfps", P21_FrameMin != 0 ? (int32_t)(50 / (int64_t)P21_FrameMin) : 0);
  else snprintf(buf, 0x20, "%s", str_at(P97_StrAddr[0xd5]));
  wr32(m + 0x08, S(0x54)); wr32(m + 0x18, S(0x55)); wr32(m + 0x38, S(0x56)); wr32(m + 0x58, S(0x57)); wr32(m + 0x78, S(0x58));
  wr32(m + 0x28, S(tab[2 + WI00B87E2C]));
  wr32(m + 0x48, S(tab[G00575F24]));
  wr32(m + 0x68, (int32_t)re_addr(buf));
  wr32(m + 0x88, S(tab[G00575F48]));
  (void)base;
}
void P97_OptMenuAInit(void) { opt_menu(P97_OptMenuA, 0x0054acc0u, P97_FpsTxtA, P97_OptTabA); }   /* 0054acc8.. */
void P97_OptMenuBInit(void) { opt_menu(P97_OptMenuB, 0x0054e560u, P97_FpsTxtB, P97_OptTabB); }   /* 0054e568.. */
#undef S

/* ---- 0040c8a0 / 004185d2: таблица пунктов меню {+0 обработчик, +4 обработчик, +8 ≠0 — есть пункт}, шаг 0x10 ---- */
typedef void (*p97_menufn_t)(int32_t);
static void menu_call(uint32_t fa, int32_t arg) {
  p97_menufn_t f = (p97_menufn_t)re_fn(fa);
#ifndef RE_HOOK_BUILD
  if (f == NULL) return;
#endif
  f(arg);
}
void P97_MenuCall0(uint32_t tab, int32_t sel) {
  const uint8_t *t = (const uint8_t *)re_ptr(tab);
#ifndef RE_HOOK_BUILD
  if (t == NULL) return;   /* таблица .data не зарегистрирована в реестре native */
#endif
  for (int32_t i = 0; rd32(t + 8 + i * 0x10) != 0; i++) menu_call((uint32_t)rd32(t + 4 + i * 0x10), 0);
  menu_call((uint32_t)rd32(t + sel * 0x10), 0);
}
void P97_MenuCall2(uint32_t tab, int32_t sel, uint32_t items) {
  uint8_t *it = (uint8_t *)re_ptr(items);
  const uint8_t *t = (const uint8_t *)re_ptr(tab);
#ifndef RE_HOOK_BUILD
  if (t == NULL || it == NULL) return;
#endif
  for (int32_t i = 0; (int16_t)rd16(it + i * 0x10) != -1; i++) { it[0xc + i * 0x10] = 0xff; it[0xd + i * 0x10] = 0xff; it[0xe + i * 0x10] = 0xff; }
  for (int32_t i = 0; rd32(t + 8 + i * 0x10) != 0; i++) menu_call((uint32_t)rd32(t + 4 + i * 0x10), 2);
  menu_call((uint32_t)rd32(t + sel * 0x10), 2);
}

/* ---- цели миссии: запись цели, +0x1fc — указатель на счётчик (адрес Game.exe) ---- */
static int32_t goal_count(const uint8_t *g) { const uint8_t *p = link(g + 0x1fc); return p ? rd32(p) : 0; }
int32_t P97_GoalReached(int32_t t, uint8_t *g, uint8_t *o) {
  if (t < rd32(g + 0x20) && (rd32(g + 0x18) & 1) != 0 && rd32(g + 0x1c) * 0x32 <= goal_count(g)) {
    wr32(o + 0x10, rd32(o + 0x10) | 2);
    if ((P62_Frame & 3) == 3) {
      P14_Fn004A7E6E(1);
      if (0x2a9 < G2_00D11A5C) { P47_Flag = 1; P62_Max = 1; }
    }
    return 1;
  }
  return 0;
}
int32_t P97_GoalCops(int32_t t, uint8_t *g, uint8_t *o) {
  if (rd32(g + 4) != 2) return 0;
  int32_t on = (0x2a9 < G2_00D11A5C && (P95_SndReady != 0 || 0 < P95_AmbN)) ? 1 : 0;
  if (t < rd32(g + 0x2c) && (P97_C810A8 != 0 || P97_C81490 != 0) && on) {
    wr32(o + 0x10, rd32(o + 0x10) | 4);
    return 1;
  }
  if (rd32(g + 0x1b4) != 0 && (rd32(g + 0x18) & 1) != 0) {
    wr32(o + 0x10, (int32_t)((uint32_t)rd32(o + 0x10) & 0xfffffdffu));
    if (t < 6000 && goal_count(g) < rd32(g + 0x1c) * 0x32 && rd32(g + 0x44) < P97_D078CC) {
      wr32(o + 0x10, rd32(o + 0x10) | 0x200);
      return 1;
    }
  }
  return 0;
}
void P97_AddTime(uint8_t *g, int32_t d) {
  if (d == 0) return;
  int32_t idx = d == 1 ? 0x12a : 0xf8;
  uint8_t *p = link(g + 0x1fc);
  if (p == NULL || (rd32(p + 4) & 4) == 0) return;
  D_00c80ca0 += d;
  snprintf(P97_MsgBuf, sizeof P97_MsgBuf, d < 0 ? "%d %s!" : "+%d %s!", D_00c80ca0, str_at(P97_StrAddr[idx]));
  wr32(p, rd32(p) + d * 0x32);
  P11_00c81494 = 0x32;
  wr32(g + 100, rd32(g + 100) + 1);
}

/* ---- 004d2c95: видит ли коп игрока (view: радиус близко, дальность, угол обзора) ---- */
int32_t P97_CopsSee(const int16_t *view, uint8_t *car) {
  const uint8_t *o = link(car + 0xcd0);
  if (o == NULL) return 0;
  int32_t dx = P59_PosX - rd32(o + 0x18);
  int32_t dz = P59_PosZ - rd32(o + 0x20);
  int32_t d2 = dx * dx + dz * dz;
  if (d2 < (int32_t)view[0] * (int32_t)view[0]) { P56_CopsA = 1; return 1; }
  int32_t a = P44_Atan2(dz, dx);
  int32_t df = (((rd32(car + 0xc) - (int32_t)((uint32_t)(a + 0x400) & 0xfff)) + 0x800) & 0xfff) - 0x800;
  if (df < 0) df = -df;
  if (df < (int32_t)view[2] / 2 && d2 < (int32_t)view[1] * (int32_t)view[1]) { P56_CopsB = 1; return 1; }
  return 0;
}

/* ---- 004c2ab0: клавиши режиссёра — удалить/добавить камеру перед текущей ---- */
void P97_DirKeys(uint32_t keys) {
  if ((keys & 0x10) == 0) P29_Flag94 = 0;
  else if (P29_Flag94 == 0) { SetDirectorMode(0xc, DirectorUnk7C, 0); return; }
  DIRECTOR_CAMERA *c = FindCameraForFrame(DirectorUnk6C);
  if (c == NULL) { P29_Flag94 = 0; SetDirectorMode(0xc, DirectorUnk7C, 0); return; }
  if (0 < c->id && (keys & 1) != 0) {
    DIRECTOR_CAMERA *p = FindCameraById(c->id - 1);
    if (p != NULL) DeleteCamera(p->index);
    c->id--;
  }
  if ((keys & 2) != 0 && c->id < DirectorUnk6C) c->id++;
}

/* ---- 00417479 / 00417fff: мигание значков меню (яркость 0..255 туда-обратно) ---- */
static uint32_t blink(int32_t *st) {
  st[0] += st[1];
  if (0xff < st[0]) { st[0] = 0xff; st[1] = -st[1]; }
  if (st[0] < 0) { st[0] = 0; st[1] = -st[1]; }
  return (uint32_t)st[0] & 0xff;
}
void P97_BlinkAStep(void) {
  int32_t v = (int32_t)blink(P97_BlinkA);
  if (Q005FEA0C != 0) P97_Fn418E70(30.0f, 420.0f, (uint32_t)Q005FEA0C, v, v, v, 0, 3);
  if (Q005FEA10 != 0) P97_Fn418E70(580.0f, 420.0f, (uint32_t)Q005FEA10, v, v, v, 0, 3);
}
void P97_BlinkBStep(void) {
  int32_t v = (int32_t)blink(P97_BlinkB);
  if (P97_IconL != 0) {
    P97_Fn418E70(32.0f, 422.0f, (uint32_t)P97_IconL, v, v, v, 0, 2);
    P97_Fn418E70(30.0f, 420.0f, (uint32_t)P97_IconL, v, v, v, 0, 3);
  }
  if (P97_IconR != 0) {
    P97_Fn418E70(582.0f, 422.0f, (uint32_t)P97_IconR, v, v, v, 0, 2);
    P97_Fn418E70(580.0f, 420.0f, (uint32_t)P97_IconR, v, v, v, 0, 3);
  }
}

/* ---- 004afcf7: частица дыма в пуле 0110b260 (записи 0x3c) ---- */
void P97_SpawnSmoke(const float *pos, const float *vel, const uint8_t *rgb, int16_t kind, int32_t arg) {
  int32_t i = PoolNext004AC671();
  if (i < 0) return;
  uint8_t *r = P12_0110b260 + i * 0x3c;
  P11_00ba52d0 = fround(pos[0]); wr32(r + 0x00, P11_00ba52d0);
  P11_00ba52d0 = fround(pos[1]); wr32(r + 0x04, P11_00ba52d0);
  P11_00ba52d0 = fround(pos[2]); wr32(r + 0x08, P11_00ba52d0);
  P11_00ba52d0 = fround(vel[0]); wr32(r + 0x10, P11_00ba52d0);
  P11_00ba52d0 = fround(vel[1]); wr32(r + 0x14, P11_00ba52d0);
  P11_00ba52d0 = fround(vel[2]); wr32(r + 0x18, P11_00ba52d0);
  wr16(r + 0x20, (uint16_t)kind);
  wr16(r + 0x22, 2);
  wr16(r + 0x26, 0);
  wr32(r + 0x28, arg);
  r[0x34] = rgb[0]; r[0x35] = rgb[1]; r[0x36] = rgb[2];
}

/* ---- 004ad128: подбросить обломки (100 записей 0x3c, 010fb220) в квадрате ±0xb4 от точки ---- */
void P97_KickDebris(const int32_t *pos) {
  if (P16_FlagA != 0) return;
  for (int32_t k = 0; k < 100; k++) {
    uint8_t *r = P97_Debris + k * 0x3c;
    if ((rd16(r + 0x22) & 2) == 0 || !(-200.0f < (float)pos[1] + rdf(r + 4))) continue;
    P11_00ba52d0 = fround(rdf(r));
    int32_t dx = pos[0] - P11_00ba52d0;
    P11_00ba52d0 = fround(rdf(r + 8));
    int32_t dz = pos[2] - P11_00ba52d0;
    if (dx < 0xb4 && -0xb4 < dx && dz < 0xb4 && -0xb4 < dz) {
      uint32_t u = N14_Rand();
      wrf(r + 0x14, (float)(int32_t)(-0x14 - (int32_t)(u & 0x3f)));
      wrf(r + 4, rdf(r + 4) - 1.0f);
    }
  }
}

/* ---- 004e5a1a: значок затемнения + стрелка по фазе P94_FadePos ---- */
void P97_FadeIconDraw(void) {
  if (P97_FadeIcon != NULL) {
    if (P62_I252B78 != 1) {
      if (P97_GrAlpha) P97_GrAlpha(3, 8, 0, 1, 1);
      if (P97_GrDepth) P97_GrDepth(4);
      P62_I252B78 = 1;
    }
    if (P94_FadeDir == 0) P96_IconAt(0.0f, 0.0f, P97_FadeIcon, 0xff, 0xff, 0xff);
    else P96_IconAt(0.0f, 0.0f, P97_FadeIcon, 0xff, (uint8_t)(0xff - P94_FadeVal), (uint8_t)(0xff - P94_FadeVal));
    if (P62_I252B78 != 0) {
      if (P97_GrAlpha) P97_GrAlpha(3, 8, 0, 2, 1);
      if (P97_GrDepth) P97_GrDepth(7);
      P62_I252B78 = 0;
    }
  }
  P11_00ba52d0 = fround(P94_FadePos);
  uint32_t i = (uint32_t)P11_00ba52d0 & 0xfff;
  P97_Fn4262CE(47.0f, 87.0f, (float)((double)P43_Sin[i] * 32.0 + 47.0), (float)((double)P43_Sin[i + 0x400] * -32.0 + 87.0), 0);
}
