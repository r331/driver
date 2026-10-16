/* Пачка простых/листовых функций — восстановлено из Game.exe (004d90f4, 004a2c98, 004a32e9, 004f652e, 004f6612, 004e8440,
   0048db8e, 004d7a21, 004d9663, 004e71dc, 004e72f8, 004b9464, 004b04c0, 004ad5d2, 004fba23, 005199bc, 00516ed3, 0051718a,
   005172bb, 005222cf, 0050fab0, 0050e9ab, 00513cc7, 00513ce0, 0052008e). */
#include "ported96.h"
#include "crt.h"
#include "director.h"
#include "directorstorage.h"
#include "dirnodes.h"
#include "globalsets.h"
#include "menustate.h"
#include "smallfuncs.h"
#include "uihandlers3.h"
#include "widgets.h"
#include "ported4.h"
#include "ported5.h"
#include "ported6.h"
#include "ported7.h"
#include "ported8.h"
#include "ported12.h"
#include "ported13.h"
#include "ported14.h"
#include "ported17.h"
#include "ported19.h"
#include "ported21.h"
#include "ported27.h"
#include "ported29.h"
#include "ported43.h"
#include "ported47.h"
#include "ported52.h"
#include "ported53.h"
#include "ported54.h"
#include "ported55.h"
#include "ported58.h"
#include "ported62.h"
#include "ported67.h"
#include "ported68.h"
#include "ported70.h"
#include "ported74.h"
#include "ported80.h"
#include "ported93.h"
#include "ported95.h"
#include "noop.h"
#include "unported.h"
#include <math.h>
#include <stdio.h>
#include <string.h>

#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P96_LogBuf")
#undef P96_LogBuf
#pragma push_macro("P96_LogBuf") /*gvi*/
#undef P96_LogBuf /*gvi*/
p96_logbuf_t P96_LogBuf;
#pragma pop_macro("P96_LogBuf") /*gvi*/
#pragma pop_macro("P96_LogBuf")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P96_FpsShown")
#undef P96_FpsShown
#pragma push_macro("P96_FpsShown") /*gvi*/
#undef P96_FpsShown /*gvi*/
int32_t P96_FpsShown;
#pragma pop_macro("P96_FpsShown") /*gvi*/
#pragma pop_macro("P96_FpsShown")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P96_FpsFrames")
#undef P96_FpsFrames
#pragma push_macro("P96_FpsFrames") /*gvi*/
#undef P96_FpsFrames /*gvi*/
int32_t P96_FpsFrames;
#pragma pop_macro("P96_FpsFrames") /*gvi*/
#pragma pop_macro("P96_FpsFrames")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P96_FpsTicks")
#undef P96_FpsTicks
#pragma push_macro("P96_FpsTicks") /*gvi*/
#undef P96_FpsTicks /*gvi*/
int32_t P96_FpsTicks;
#pragma pop_macro("P96_FpsTicks") /*gvi*/
#pragma pop_macro("P96_FpsTicks")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P96_FpsTick0")
#undef P96_FpsTick0
#pragma push_macro("P96_FpsTick0") /*gvi*/
#undef P96_FpsTick0 /*gvi*/
int32_t P96_FpsTick0;
#pragma pop_macro("P96_FpsTick0") /*gvi*/
#pragma pop_macro("P96_FpsTick0")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P96_FpsFrame0")
#undef P96_FpsFrame0
#pragma push_macro("P96_FpsFrame0") /*gvi*/
#undef P96_FpsFrame0 /*gvi*/
int32_t P96_FpsFrame0;
#pragma pop_macro("P96_FpsFrame0") /*gvi*/
#pragma pop_macro("P96_FpsFrame0")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P96_RefreshHz")
#undef P96_RefreshHz
#pragma push_macro("P96_RefreshHz") /*gvi*/
#undef P96_RefreshHz /*gvi*/
int32_t P96_RefreshHz;
#pragma pop_macro("P96_RefreshHz") /*gvi*/
#pragma pop_macro("P96_RefreshHz")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P96_Sphere")
#undef P96_Sphere
#pragma push_macro("P96_Sphere") /*gvi*/
#undef P96_Sphere /*gvi*/
p96_sphere_t P96_Sphere;
#pragma pop_macro("P96_Sphere") /*gvi*/
#pragma pop_macro("P96_Sphere")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P96_RotTab")
#undef P96_RotTab
#pragma push_macro("P96_RotTab") /*gvi*/
#undef P96_RotTab /*gvi*/
p96_rottab_t P96_RotTab;
#pragma pop_macro("P96_RotTab") /*gvi*/
#pragma pop_macro("P96_RotTab")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P96_SparkOn")
#undef P96_SparkOn
#pragma push_macro("P96_SparkOn") /*gvi*/
#undef P96_SparkOn /*gvi*/
int32_t P96_SparkOn;
#pragma pop_macro("P96_SparkOn") /*gvi*/
#pragma pop_macro("P96_SparkOn")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P96_DustOn")
#undef P96_DustOn
#pragma push_macro("P96_DustOn") /*gvi*/
#undef P96_DustOn /*gvi*/
int32_t P96_DustOn;
#pragma pop_macro("P96_DustOn") /*gvi*/
#pragma pop_macro("P96_DustOn")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P96_Dust")
#undef P96_Dust
#pragma push_macro("P96_Dust") /*gvi*/
#undef P96_Dust /*gvi*/
p96_dust_t P96_Dust;
#pragma pop_macro("P96_Dust") /*gvi*/
#pragma pop_macro("P96_Dust")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P96_DustN")
#undef P96_DustN
#pragma push_macro("P96_DustN") /*gvi*/
#undef P96_DustN /*gvi*/
int32_t P96_DustN;
#pragma pop_macro("P96_DustN") /*gvi*/
#pragma pop_macro("P96_DustN")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P96_ObjBOn")
#undef P96_ObjBOn
#pragma push_macro("P96_ObjBOn") /*gvi*/
#undef P96_ObjBOn /*gvi*/
int32_t P96_ObjBOn;
#pragma pop_macro("P96_ObjBOn") /*gvi*/
#pragma pop_macro("P96_ObjBOn")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P96_ReplayB")
#undef P96_ReplayB
#pragma push_macro("P96_ReplayB") /*gvi*/
#undef P96_ReplayB /*gvi*/
uint8_t P96_ReplayB;
#pragma pop_macro("P96_ReplayB") /*gvi*/
#pragma pop_macro("P96_ReplayB")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P96_RTag")
#undef P96_RTag
#pragma push_macro("P96_RTag") /*gvi*/
#undef P96_RTag /*gvi*/
p96_tag_t P96_RTag;
#pragma pop_macro("P96_RTag") /*gvi*/
#pragma pop_macro("P96_RTag")
#endif
GAME_VAR_DEF(uint8_t *, P96_ShadIcon, 0x00b5c8d8)
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P96_ShadPage")
#undef P96_ShadPage
#pragma push_macro("P96_ShadPage") /*gvi*/
#undef P96_ShadPage /*gvi*/
uint8_t P96_ShadPage;
#pragma pop_macro("P96_ShadPage") /*gvi*/
#pragma pop_macro("P96_ShadPage")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P96_ShadIdx")
#undef P96_ShadIdx
#pragma push_macro("P96_ShadIdx") /*gvi*/
#undef P96_ShadIdx /*gvi*/
p96_i4_t P96_ShadIdx;
#pragma pop_macro("P96_ShadIdx") /*gvi*/
#pragma pop_macro("P96_ShadIdx")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P96_ShadRGB")
#undef P96_ShadRGB
#pragma push_macro("P96_ShadRGB") /*gvi*/
#undef P96_ShadRGB /*gvi*/
p96_f3_t P96_ShadRGB;
#pragma pop_macro("P96_ShadRGB") /*gvi*/
#pragma pop_macro("P96_ShadRGB")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P96_ShadUV")
#undef P96_ShadUV
#pragma push_macro("P96_ShadUV") /*gvi*/
#undef P96_ShadUV /*gvi*/
p96_f12_t P96_ShadUV;
#pragma pop_macro("P96_ShadUV") /*gvi*/
#pragma pop_macro("P96_ShadUV")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P96_ShadH")
#undef P96_ShadH
#pragma push_macro("P96_ShadH") /*gvi*/
#undef P96_ShadH /*gvi*/
float P96_ShadH;
#pragma pop_macro("P96_ShadH") /*gvi*/
#pragma pop_macro("P96_ShadH")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P96_ShadW")
#undef P96_ShadW
#pragma push_macro("P96_ShadW") /*gvi*/
#undef P96_ShadW /*gvi*/
float P96_ShadW;
#pragma pop_macro("P96_ShadW") /*gvi*/
#pragma pop_macro("P96_ShadW")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P96_PartTab")
#undef P96_PartTab
#pragma push_macro("P96_PartTab") /*gvi*/
#undef P96_PartTab /*gvi*/
p96_parttab_t P96_PartTab;
#pragma pop_macro("P96_PartTab") /*gvi*/
#pragma pop_macro("P96_PartTab")
#endif

#define LOG_BASE 0x00d0fe40u

static int32_t rd32(const uint8_t *p, int o) { int32_t v; memcpy(&v, p + o, 4); return v; }
static void wr32(uint8_t *p, int o, int32_t v) { memcpy(p + o, &v, 4); }
static void wrf(uint8_t *p, int o, float v) { memcpy(p + o, &v, 4); }
static void wr16(uint8_t *p, int o, int16_t v) { memcpy(p + o, &v, 2); }
static int32_t f2i(float f) { int32_t v; memcpy(&v, &f, 4); return v; }   /* 0040ab59/0040ab6f принимают float в int-слоте */

void P96_InitConsts(void) {
#ifndef RE_HOOK_BUILD
  P96_RefreshHz = 50;
  memset(P96_RTag, 0, sizeof P96_RTag); P96_RTag[0] = 'R';
#endif
}

const char *P96_LogText(uint32_t id) {
#ifdef RE_HOOK_BUILD
  return (const char *)(uintptr_t)id;
#else
  if (id < LOG_BASE || id >= LOG_BASE + sizeof P96_LogBuf) return "";
  return P96_LogBuf + (id - LOG_BASE);
#endif
}

/* 004d90f4: в очередь P55_PopTab — {адрес строки, цвет WH00B2C3A8, столбец, строка}; перевод строки и ширина экрана/8 сдвигают строку */
void P96_LogLine(const char *s) {
  if (P55_PopCnt >= 0x80) return;
  P55_Pop *e = &P55_PopTab[P55_PopCnt];
  e->w = WH00B2C3A8;
  e->x = (uint32_t)G6_00D117A4;
  e->y = (uint32_t)G6_00D117A8;
  e->id = LOG_BASE + (uint32_t)P55_PopB2AC;
  int32_t cols = P19_ScrW / 8;
  for (; *s != '\0'; s++) {
#ifndef RE_HOOK_BUILD
    if (P55_PopB2AC < 0 || P55_PopB2AC >= (int32_t)sizeof P96_LogBuf - 1) break;   /* в оригинале проверки нет */
#endif
    P96_LogBuf[P55_PopB2AC] = *s;
    P55_PopB2AC++;
    if (*s == '\n') {
      G6_00D117A4 = 0; G6_00D117A8++;
    } else {
      G6_00D117A4++;
      if (G6_00D117A4 == cols) { G6_00D117A4 = 0; G6_00D117A8++; }
    }
  }
#ifndef RE_HOOK_BUILD
  if (P55_PopB2AC < 0 || P55_PopB2AC >= (int32_t)sizeof P96_LogBuf) { P55_PopCnt++; return; }
#endif
  P96_LogBuf[P55_PopB2AC] = 0;
  P55_PopB2AC++;
  P55_PopCnt++;
}

/* 004bf485 (Call004BF485) без обрезки указателя в native: при G00B87E7C == 0 — в журнал */
static void p96_print(const char *s) { if (G00B87E7C == 0) P96_LogLine(s); }

/* 004a2c98: записи 0x18 по 01134540 {слот, клетка, номер кресла, x, z, флаги (+0x14 — D_01134554)} */
void P96_DropFarChairs(void) {
  if (P58_Grid == NULL) return;
  for (int32_t i = 0; i < 100; i++) {
    const uint8_t *r = &A_01134540[i * 24];
    if ((D_01134554[i * 6] & 1) == 0) continue;
    int32_t cell = rd32(r, 12) / P80_Cell + P21_GridDiv / 2 + (rd32(r, 16) / P80_Cell + P80_GridH / 2) * (P21_GridDiv / P54_GridN);
    if (cell == P55_VarD20 || cell == P55_VarD24 || cell == P55_VarD28 || cell == P55_VarD2C) continue;
    ReleaseSlot4A2C5B(rd32(r, 0));
    p58_cell_t *c = (p58_cell_t *)P58_Grid[rd32(r, 4)];
    if (c == NULL || c->items == NULL) continue;                            /* в оригинале проверки нет */
    uint8_t *it = (uint8_t *)c->items + rd32(r, 8) * 0x14;
    wr32(it, 8, (int32_t)((uint32_t)rd32(it, 8) & 0xfffffffeu));
  }
}

/* 004a32e9 */
uint8_t *P96_PickChair(int32_t cell) {
  if (P58_Grid == NULL) return NULL;
  p58_cell_t *c = (p58_cell_t *)P58_Grid[cell];
  if (c == NULL || c->b == 0) return NULL;
  int32_t r = (int32_t)Rand_004D9078();
  uint8_t *it = (uint8_t *)c->items + (r % c->b) * 0x14;
  if ((rd32(it, 8) & 1) != 0) return NULL;
  return it;
}

/* 004f652e: первое слово (печатные 0x21..0x7f) до ',' или пробела после слова; остаток сдвигается в начало строки */
int32_t P96_ParseWord(char *line, char *out) {
  int32_t len = (int32_t)strlen(line), n = 0, i;
  for (i = 0; i < len; i++) {
    uint8_t ch = (uint8_t)line[i];
    if (ch < 0x21 || ch > 0x7f) { if (n != 0) break; }
    else { if (ch == ',') break; out[n++] = (char)ch; }
  }
  if (n == 0) return 0xc;
  int32_t k = 0;
  while (++i < len) line[k++] = line[i];
  out[n] = 0;
  return 0;
}

/* 004f6612: пропустить пробелы/табуляции, затем "строка" (символы 0x20..0x7f); хвост после кавычки — в начало (strcpy) */
int32_t P96_ParseQuoted(char *line, char *out) {
  int32_t len = (int32_t)strlen(line), n = 0, i = 0;
  for (;;) {
    if (len <= i) return 0xc;
    if (line[i] != '"' && line[i] != ' ' && line[i] != '\t') return 0xc;
    if (line[i] == '"') {
      int32_t start = i + 1;
      for (i = start; i < len; i++) {
        if (line[i] == '"') {
          for (i = 0; i < n; i++) out[i] = line[start + i];
          out[i] = 0;
          const char *tail = line + start + i + 1;
          memmove(line, tail, strlen(tail) + 1);
          return 0;
        }
        if ((uint8_t)line[i] < 0x20 || (uint8_t)line[i] > 0x7f) return 0xc;
        n++;
      }
    }
    i++;
  }
}

/* 004e8440: 7 колец по 32 точки, y = ±0.25·k, радиус sqrt(1 − y²) (CRT sqrt 0052dfd4) */
void P96_InitSphere(void) {
  for (int32_t k = 0; k < 4; k++) {
    float y = (float)k * 0.25f;
    float r = (float)sqrt((double)(1.0f - y * y));
    for (int32_t c = 0; c < 32; c++) {
      float *lo = P96_Sphere[(3 - k) * 32 + c], *hi = P96_Sphere[(k + 3) * 32 + c];
      lo[0] = P43_Sin[c * 0x80] * r;
      hi[0] = lo[0];
      hi[1] = y;
      lo[1] = -y;
      lo[2] = P43_Sin[0x400 + c * 0x80] * r;
      hi[2] = lo[2];
    }
  }
}

/* 0048db8e: 4 угла прямоугольника (±180, ±450), повёрнутые на угол i·4; fstp во float, затем fistp */
static int32_t rnd2(double v) { return (int32_t)lrintf((float)v); }
void P96_InitRotTab(void) {
  const double A = -180.0, B = 450.0, C = 180.0, D = -450.0;   /* .rdata 005460d8/d4/d0/cc */
  for (int32_t i = 0; i < 0x400; i++) {
    double s = P43_Sin[i * 4], c = P43_Sin[(i * 4 + 0x400) & 0xfff];
    int32_t *t = P96_RotTab[i];
    t[0] = rnd2(A * c - B * s); t[1] = rnd2(B * c + A * s);
    t[2] = rnd2(C * c - B * s); t[3] = rnd2(B * c + C * s);
    t[4] = rnd2(A * c - D * s); t[5] = rnd2(D * c + A * s);
    t[6] = rnd2(C * c - D * s); t[7] = rnd2(D * c + C * s);
  }
}

/* 004d7a21: раз в 15 кадров — частота кадров по счётчику P62_Frame; строка «%d Hz, %d FPS.» в журнал */
void P96_FpsText(void) {
  char buf[80];
  if (P21_FrameTotal == 0) return;
  if (P21_FrameTotal % 15 == 0 && P96_FpsFrame0 < P21_FrameTotal) {
    P96_FpsFrames = P21_FrameTotal - P96_FpsFrame0;
    P96_FpsTicks = P62_Frame - P96_FpsTick0;
    P96_FpsFrame0 = P21_FrameTotal;
    P96_FpsTick0 = P62_Frame;
    float q = (float)(uint32_t)P96_FpsTicks / (float)(uint32_t)P96_FpsFrames;
    P96_FpsShown = (int32_t)lrintf(q * (float)P96_RefreshHz);
  }
  snprintf(buf, sizeof buf, "%d Hz, %d FPS.", P96_RefreshHz, P96_FpsShown);
  p96_print(buf);
  Call004BF476();
}

/* 004d9663: полоса загрузки по прочитанным байтам P27_ReadBytes из P8_00d0fe1c; следующий порог +0x20000 */
void P96_LoadBar(void) {
  if (P27_ReadBytes >= P8_00d0fe1c) return;
  P27_ReadLimit = P27_ReadBytes + 0x20000;
  if (P8_00d0fe1c < P27_ReadLimit) P27_ReadLimit = P8_00d0fe1c;
  float c;
  if (P27_ReadBytes == 0) c = 0.0f;
  else if (P27_ReadBytes < P8_00d0fe1c) c = (float)P27_ReadBytes / (float)P8_00d0fe1c;
  else c = 1.0f;
  uint32_t a = (uint32_t)lrintf(255.0f * c) & 0xff;
  P52_GlideFogMode();
  P96_Fn4D7F91((float)P8_00d117f8, (float)P8_00d117fc, c * (float)P8_00d117e4, (float)P8_00d117ec,
               0xff, 0, 0, 0, (int32_t)a, 0, 0, 0, 0xff, (int32_t)a, (int32_t)a, 0);
  P47_GlideSwap();
}

/* 004e71dc / 004e72f8: виртуальные 640×480 → экран с масштабом от центра; значок {+8 страница, +9..+12 u0 v0 u1 v1} */
static float vx(float x) { return (float)((((double)x / 640.0 - 0.5) * P19_Scale + 0.5) * (double)(float)P19_ScrW); }
static float vy(float y) { return (float)((((double)y / 480.0 - 0.5) * P19_Scale + 0.5) * (double)(float)P19_ScrH); }
static void icon_draw(float x, float y, float w, float h, const uint8_t *icon, const uint8_t *rgb) {
  P96_Fn40B6FD(x, y, w, h, (float)icon[9], (float)icon[10], (float)icon[11], (float)icon[12], icon[8], rgb);
}
void P96_IconAt(float x, float y, const uint8_t *icon, uint8_t r, uint8_t g, uint8_t b) {
  uint8_t rgb[3] = {r, g, b};
  float s = (float)((double)((float)P19_ScrW / 640.0f) * P19_Scale);
  icon_draw(vx(x), vy(y), s, s, icon, rgb);
}
void P96_IconRect(float x, float y, float w, float h, const uint8_t *icon, uint32_t c) {
  uint8_t rgb[3] = {(uint8_t)(c >> 16), (uint8_t)(c >> 8), (uint8_t)c};
  double k = (double)((float)P19_ScrW / 640.0f);
  icon_draw(vx(x), vy(y), (float)(k * w * P19_Scale), (float)(k * h * P19_Scale), icon, rgb);
}

/* 004b9464: искра — запись 0x78 массива A (010f5160) из пула 004ac6d0 */
void P96_SpawnSpark(const float *pos, int32_t a, int32_t b, int16_t c) {
  if (G6_00B5A778 != 0 || (P62_Frame & 1) != 0) return;
  int32_t i = PoolPop004AC6D0();
  if (i < 0) return;
#ifndef RE_HOOK_BUILD
  if (i >= 200) return;
#endif
  uint8_t *r = P95_ObjA + i * 0x78;
  wr32(r, 0x68, 0x1002);
  wrf(r, 0, (float)(N14_Rand() & 3) + pos[0]);
  wrf(r, 4, pos[1]);
  wrf(r, 8, (float)(N14_Rand() & 3) + pos[2]);
  wr32(r, 0x50, a); wr32(r, 0x54, b);
  wr16(r, 0x64, c);
  wr32(r, 0x28, 0); wr32(r, 0x24, 0); wr32(r, 0x20, 0);
  wr32(r, 0x60, 2); wr32(r, 0x58, 0x50); wr32(r, 0x5c, 2);
}

/* 004b04c0: пыль — n записей 0x24 по 0110e160, если первая запись не живая (+0x20 == 0) */
void P96_SpawnDust(const float *pos, int32_t n) {
  if (P96_SparkOn == 0 || P96_DustOn == 0 || rd32(P96_Dust, 0x20) != 0) return;
  P96_DustN = n;
  uint8_t *r = P96_Dust;
  for (; n != 0; n--) {
#ifndef RE_HOOK_BUILD
    if (r >= P96_Dust + sizeof P96_Dust) break;
#endif
    wrf(r, 0, (float)(int32_t)((N14_Rand() & 0x3f) - 0x20) + pos[0]);
    wrf(r, 4, (float)(int32_t)((N14_Rand() & 0x3f) - 0x20) + pos[1]);
    wrf(r, 8, (float)(int32_t)((N14_Rand() & 0x3f) - 0x20) + pos[2]);
    wrf(r, 0x10, (float)(int32_t)((N14_Rand() & 0x3f) - 0x20));
    wrf(r, 0x14, (float)(int32_t)(-5 - (int32_t)(N14_Rand() & 0xf)));
    wrf(r, 0x18, (float)(int32_t)((N14_Rand() & 0x3f) - 0x20));
    wr16(r, 0x20, 0x3c); wr16(r, 0x22, 10);
    r += 0x24;
  }
}

/* 004ad5d2: запись массива B по указателю 01105d60 (адрес Game.exe → P95_ObjPtr), счётчик G010FFD04 */
void P96_AddObjB(const float *pos, const int32_t *uv, int16_t a, int16_t b, uint32_t flags, int32_t mark, int32_t c, int32_t d) {
  if (P96_ObjBOn == 0 || P13_00b201dc == 0) return;
  uint8_t *r = P95_ObjPtr((uint32_t)G01105D60);
  if (r == NULL) return;                                                    /* native: вне массива B */
  wrf(r, 0, pos[0]); wrf(r, 4, pos[1]); wrf(r, 8, pos[2] - 10.0f);          /* .rdata 0054612c = 10.0 */
  for (int k = 0; k < 4; k++) wr32(r, 0x10 + 4 * k, uv[k]);
  wr32(r, 0x68, 0x20002); wr32(r, 0x74, 0); wr32(r, 0x70, 0);
  wr16(r, 0x64, (int16_t)(mark == 0 ? (uint16_t)flags : (uint16_t)(flags | 0x80)));
  wr16(r, 0x6c, a); wr16(r, 0x6e, b);
  wr32(r, 0x50, c); wr32(r, 0x54, d);
  wr32(r, 0x68, (int32_t)((uint32_t)rd32(r, 0x68) | (flags & 0xe00000)));
  G01105D60 += 0x78;
  G010FFD04++;
}

/* 004fba23 */
void P96_ClockText(const uint8_t *t) {
  char buf[20];
  if (P29_Mode != 0) return;
  if (P13_00b31f04 == 0) {
    snprintf(buf, sizeof buf, "%02d:%02d", rd32(t, 0x14), rd32(t, 0x10));
    P70_ShadowText(0x140, 2, (uint32_t)(uintptr_t)buf, 1, 1, 0xff, 0xff, 0xff);
    float w = P58_TextWidth((const uint8_t *)buf, 1);
    int32_t x = ((int32_t)lrintf(w) >> 1) + 0x140;
    snprintf(buf, sizeof buf, ".%02d", rd32(t, 0xc));
    P70_ShadowText(x, 4, (uint32_t)(uintptr_t)buf, 0, 0, 0xff, 0xff, 0xff);
  } else {
    snprintf(buf, sizeof buf, "%02d:%02d", rd32(t, 0x14), rd32(t, 0x10));
    P70_ShadowText(10, 0x1a8, (uint32_t)(uintptr_t)buf, 1, 0, 0xff, 0xff, 0xff);
    float w = P58_TextWidth((const uint8_t *)buf, 1);
    int32_t x = (int32_t)lrintf(w) + 10;
    snprintf(buf, sizeof buf, ".%02d", rd32(t, 0xc));
    P70_ShadowText(x, 0x1aa, (uint32_t)(uintptr_t)buf, 0, 0, 0xff, 0xff, 0xff);
  }
}

/* 005199bc: метка «R» в журнал — зелёная (b5a850) или красная (b5a894) */
void P96_ReplayTag(void) {
  char tag[4] = {P96_RTag[0], P96_RTag[1], P96_RTag[2], 0};
  if (P96_ReplayB != 0) Pack565Bytes004BF452(0, 0xf0, 0);
  else if (P74_B5A894 != 0) Pack565Bytes004BF452(0xf0, 0, 0);
  else return;
  RoundSet_004BF400(0.0f, 0.0f);
  p96_print(tag);
  Pack565Bytes004BF452(0xf0, 0xf0, 0xa0);
}

/* 00516ed3: x, y — экранные, масштаб P19_Scale от центра; флаги 4 */
void P96_TextCenter(float x, float y, float sx, float sy, uint32_t txt) {
  int32_t cx = P19_ScrW >> 1, cy = P19_ScrH >> 1;
  float s = P19_Scale;
  float fx = (x - (float)cx) * s, fy = (y - (float)cy) * s;
  GlobalSet0040B0A4();
  MenuSetPos(f2i(sx * s), f2i(sy * s));
  MenuSetColor(S_00B5A834, S_00B5A835, S_00B5A836);
  MenuSetVals5D77C0(f2i(fx + (float)cx), f2i(fy + (float)cy), 0, 4);
  P67_Fn40ABAC(txt);
}

static uint8_t align_flags(int32_t align, uint8_t base) { return (uint8_t)(align == -1 ? base | 0x10 : align == 1 ? base | 4 : base); }

/* 0051718a: виртуальные 640×480; align −1/1/иначе → флаги 0x10/4/0 */
void P96_TextAt(float x, float y, uint32_t txt, uint8_t a, int32_t align) {
  float sw = (float)P19_ScrW, sh = (float)P19_ScrH, s = P19_Scale;
  float fx = sw / 640.0f, fy = sh / 480.0f;
  float px = (float)(((double)x * fx - sw / 2.0f) * s + sw / 2.0f);
  float py = (float)(((double)y * fy - sh / 2.0f) * s + sh / 2.0f);
  GlobalSet0040B0A4();
  MenuSetPos(f2i(fx * s), f2i(fy * s));
  MenuSetColor(S_00B5A834, S_00B5A835, S_00B5A836);
  MenuSetVals5D77C0(f2i(px), f2i(py), a, align_flags(align, 0));
  P67_Fn40ABAC(txt);
}

/* 005172bb: по центру экрана по x; флаги 0x11/5/1 */
void P96_TextMid(float y, uint32_t txt, uint8_t a, int32_t align) {
  float sw = (float)P19_ScrW, sh = (float)P19_ScrH, s = P19_Scale;
  float fx = sw / 640.0f, fy = sh / 480.0f;
  float px = sw / 2.0f;
  float py = (float)(((double)y * fy - sh / 2.0f) * s + sh / 2.0f);
  GlobalSet0040B0A4();
  MenuSetPos(f2i(fx * s), f2i(fy * s));
  MenuSetColor(S_00B5A834, S_00B5A835, S_00B5A836);
  MenuSetVals5D77C0(f2i(px), f2i(py), a, align_flags(align, 1));
  P67_Fn40ABAC(txt);
}

/* 005222cf: удалить waypoint-файл и временный файл камер, обнулить 400 байт состояния режиссёра (00d17b60..00d17cf0) */
void P96_ResetDirector(void) {
  DeleteWaypointFile();
  g_remove("REPLAYDATA\\USER\\$TEMP$.CAMS");
#ifdef RE_HOOK_BUILD
  P14_Fn0048DB65((void *)(uintptr_t)0x00d17b60, 400);
#else
  /* в native диапазон — отдельные переменные; обнуляются все известные */
  NumCameras = 0; DirectorUnk64 = 0; DirectorLastFrame = 0; DirectorUnk6C = 0; DirectorBufferCount = 0; P29_Flag74 = 0;
  DirectorUnk7C = 0; DirIndicatorCnt = 0; DirectorUnk84 = 0; DirectorUnk88 = 0; DirectorUnk8C = 0; DirSelectedColor = 0;
  P12_00d17b90 = 0; P29_Flag94 = 0; P29_Flag98 = 0; P29_Flag9C = 0; DirUseDI = 0; P29_FlagA4 = 0; P29_FlagA8 = 0;
  DirIndicatorOn = 0; P29_FlagB0 = 0; CamBackupValid = 0; P29_Mode = 0; P29_Param = 0;
  memset(&DirectorCam, 0, sizeof DirectorCam); memset(&CamBackup, 0, sizeof CamBackup);
  CurCamera = NULL; CameraList = NULL; DirNodeTable = NULL; DirectorBuffer = NULL;
#endif
  SetDirectorMode(0, 0, 0);
}

/* 0050fab0: дальности видимости в [15000, 42000], минимальный шаг кадров в [1, 10] */
static float clampf(float v) {
  float a = (v <= 42000.0f) ? v : 42000.0f;          /* .rdata 00546028 / 0054602c */
  return (15000.0f <= a) ? a : 15000.0f;
}
void P96_ClampOptions(void) {
  Q01270C24 = clampf(Q01270C24);
  Q0125F3F8 = clampf(Q0125F3F8);
  int32_t v = P21_FrameMin < 11 ? P21_FrameMin : 10;
  P21_FrameMin = v < 1 ? 1 : v;
  Call0050FBF4();
}

/* 0050e9ab: шаг сценария повтора (P17_PtrA/ValA); по концу — возврат к сохранённому (PtrB/ValB) или к паре 738/73c */
void P96_ReplayScript(void) {
  if (P17_PtrA == 0 || P29_Mode != 0) return;
  if (S_00B5A77C != 0) {
    if (IsFlagSetNotMasked_004E383A(1) != 0 || IsFlagSetNotMasked_004E383A(0x1c) != 0) S_00B5A77C = 0;
    return;
  }
  if (P52_MenuA != 0) { P53_NameEntry(); return; }
  P17_ValA = P96_Fn50F304(P17_PtrA, P17_ValA);
  if (P17_ValA != -1) return;
  if (G00B5A774 == 0) {
    P17_ValA = P17_ValB;
    P17_PtrA = P17_PtrB;
    if (P17_PtrB == 0) {
      if (P17_Cond1 == 0) SetLatchValue0050E940(0);
      else SetDirectorMode(0xf, 0, 0);
    }
    P17_PtrB = 0;
  } else {
    P17_ValA = G00B5A73C;
    P17_PtrA = (uint32_t)G00B5A738;
    G00B5A774 = 0;
  }
}

/* 00513cc7 / 00513ce0: обработчик по типу частицы (+0x1c) из таблицы 005759c4 */
#ifndef RE_HOOK_BUILD
static void part_step(uint8_t *p) { P67_ObjStep(p); }
static void part_noop(uint8_t *p) { (void)p; NoopFn0051406e(); }
static void (*const part_tab[5])(uint8_t *) = {P70_SpawnPart4, P68_ObjStepB, part_step, P43_AnimNext, part_noop};
#endif
static void part_run(uint8_t *p) {
  int32_t t = rd32(p, 0x1c);
#ifdef RE_HOOK_BUILD
  ((void (__cdecl *)(uint8_t *))(uintptr_t)P96_PartTab[t])(p);
#else
  if (t >= 0 && t < 5) part_tab[t](p);
#endif
}
void P96_PartRunA(uint8_t *p) { part_run(p); }
void P96_PartRunB(uint8_t *p) { part_run(p); }

/* 0052008e: значок CARSHAD → индексы 0..3, страница, uv углов (+1.5 / −0.5 от краёв), размеры, цвет 255 */
void P96_ShadowInit(void) {
  P96_ShadIcon = P93_FindIcon("CARSHAD");
  const uint8_t *ic = P96_ShadIcon;
  if (ic == NULL) return;
  for (int k = 0; k < 4; k++) P96_ShadIdx[k] = k;
  P96_ShadPage = ic[8];
  float *uv = P96_ShadUV;
  uv[0] = (float)ic[9] + 1.5f;                                        /* .rdata 00546120 = 1.5, 00546068 = 0.5 */
  uv[1] = (float)ic[10] + 1.5f;
  uv[4] = (float)((uint32_t)ic[9] + ic[11]) - 0.5f;
  uv[5] = (float)ic[10] + 1.5f;
  uv[10] = (float)((uint32_t)ic[9] + ic[11]) - 0.5f;
  uv[11] = (float)((uint32_t)ic[10] + ic[12]) - 0.5f;
  uv[2] = (float)ic[9] + 1.5f;
  uv[3] = (float)((uint32_t)ic[10] + ic[12]) - 0.5f;
  P96_ShadW = uv[4] - uv[0];
  P96_ShadH = uv[11] - uv[1];
  P96_ShadRGB[0] = 255.0f; P96_ShadRGB[1] = 255.0f; P96_ShadRGB[2] = 255.0f;
}
