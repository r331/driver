/* v1.67: ported122 — восстановлено из Game.exe. Все функции cdecl (ret без операнда; work/rets.py).
   004accf0 — пятно-квадрат под точкой (запись P122_SpotRec 010fc9a0), вершины на высоте дороги −2;
   004ac779 — пятно света фар перед машиной (матрица P98_CarMat, запись P122_GlowRec 01123280, цвет гаснет с высотой);
   004ba31b — такт 200 объектов P95_ObjA (шаги по флагам 4/8/0x8000/0x1000, время жизни, возврат номера в пул);
   0040d56c — имена значков страницы в таблицу P54_MapAPtr (записи 16 байт);
   004a44d4 — блок событий до EVENT_END: запись 0x24 в куче, список 00d12408 (поле +0x20 — адрес следующей), 004a45eb;
   0040a8b0 — глифы шрифта (запись 0x806 от 005d57a0) из значков «%s%d»;
   004e7450 — копия пикселей значка в значок того же размера + обновление текстуры (0048a46b);
   004f8485 — установка переменной скрипта (таблица P42_Vars, команда P42_Cmds[2]);
   0041ab60 — меню ввода имён: пункты 0054e948/0054e828, строки 005fee60 по 0x11, курсор «.» мигает (0054e9d8);
   004a05fa — индексы моделей объектов по 18 группам 01136940 (адреса групп — 01136a80) и сортировка пузырьком. */
#include "ported122.h"
#include "cartab.h"
#include "unported.h"
#include "smallfuncs.h"
#include "smallfuncs2.h"
#include "globalsets.h"
#include "ported7.h"
#include "ported31.h"
#include "ported36.h"
#include "ported66.h"
#include "ported74.h"
#include "ported97.h"
#include "ported110.h"
#include "uihandlers2.h"
#include "uihandlers3.h"
#include "ported8.h"
#include "ported14.h"
#include "ported12.h"
#include "ported20.h"
#include "ported26.h"
#include "ported43.h"
#include "ported44.h"
#include "ported5.h"
#include "ported51.h"
#include "ported54.h"
#include "ported58.h"
#include "ported59.h"
#include "ported65.h"
#include "ported69.h"
#include "ported77.h"
#include "ported82.h"
#include "ported84.h"
#include "ported85.h"
#include "ported93.h"
#include "ported95.h"
#include "ported96.h"
#include "ported98.h"
#include "ported100.h"
#include "ported121.h"
#include "ported123.h"
#include "reptr.h"
#include <stdio.h>
#include <string.h>

GAME_VAR_DEF(p122_rec44_t, P122_SpotRec, 0x010fc9a0)
GAME_VAR_DEF(p122_rec44_t, P122_GlowRec, 0x01123280)
GAME_VAR_DEF(uint8_t *, P122_EvCur, 0x00b1ff5c)
GAME_VAR_DEF(int32_t, P122_Ev118, 0x01134118)
GAME_VAR_DEF(int32_t, P122_Ev240, 0x01134240)
GAME_VAR_DEF(int32_t, P122_Ev24C, 0x0113424c)
GAME_VAR_DEF(int32_t, P122_BlinkOn, 0x005feefc)
#ifndef RE_HOOK_BUILD
int32_t P122_Blink = 10;                     /* .data 0054e9d8 */
#endif

static int32_t rd32(const void *p) { int32_t v; memcpy(&v, p, 4); return v; }
static void wr32(void *p, int32_t v) { memcpy(p, &v, 4); }
static int16_t rd16(const void *p) { int16_t v; memcpy(&v, p, 2); return v; }
static void wr16(void *p, int16_t v) { memcpy(p, &v, 2); }

/* Общая часть 004accf0/004ac779: 4 вершины мира → кэш вершин 0..3, проекция, четырёхугольник записи rec. */
static void quad_tail(float v[4][3], uint8_t *rec, uint32_t mode, int fade) {
  float m[9];
  for (int k = 0; k < 4; k++) {
    p85_vtx *c = &P85_VCache[k];
    c->x = v[k][0] - P44_CamX; c->y = v[k][1] - P44_CamY; c->z = v[k][2] - P44_CamZ;
  }
  for (int k = 0; k < 4; k++) P85_VCache[k].stamp = P44_XformTag;
  if (P84_Mirror == 0) P44_MatPtr = (float *)P44_ViewMatT;
  else { memcpy(m, P44_ViewMatT, sizeof m); m[0] = -m[0]; m[3] = -m[3]; m[6] = -m[6]; P44_MatPtr = m; }
  for (int k = 0; k < 4; k++) {
    P44_Xform(&P85_VCache[k].x);
    if (Q00546030 < P85_VCache[k].z) { P44_XformTag++; return; }
  }
  if (fade) {
    float h = (P85_VCache[2].z + P85_VCache[3].z) / 2.0f - 10240.0f, s;
    if (h < 0.0f) s = 1.0f;
    else if (h - 4760.0f <= 0.0f) s = 1.0f - h / 4760.0f;
    else s = 0.0f;
    for (int k = 0; k < 3; k++) { float f; memcpy(&f, rec + 0x38 + k * 4, 4); f *= s; memcpy(rec + 0x38 + k * 4, &f, 4); }
  }
  G2_011F4064 = rec;
  if (P85_VCache[0].z < P95_Near || P85_VCache[1].z < P95_Near || P85_VCache[2].z < P95_Near || P85_VCache[3].z < P95_Near)
    P121_ClipTexQuad(mode);
  else {
    P82_Edge = 1;
    for (int k = 0; k < 4; k++) P43_ProjectGrid((uint8_t *)&P85_VCache[k]);
    P121_TexQuadFlat(mode);
  }
  P44_XformTag++;
}

/* ---- 004accf0 ---- */
void P122_SpotShadow(uint32_t pos, int32_t size) {
  const float *p = (const float *)re_ptr(pos);
  if (p == NULL) return;
  P122_SpotShadowF(p, size);
}
void P122_SpotShadowF(const float *p, int32_t size) {   /* v1.68: тело 004accf0 по родному указателю (00502e76) */
  float s = (float)size, v[4][3] = {
    { -s + p[0], 0.0f, s + p[2] }, { s + p[0], 0.0f, s + p[2] },
    { s + p[0], 0.0f, -s + p[2] }, { -s + p[0], 0.0f, -s + p[2] } };
  for (int k = 0; k < 4; k++) v[k][1] = (float)(-2 - P100_RoadHeightF(v[k]));
  quad_tail(v, P122_SpotRec, 2, 0);
}

/* ---- 004ac779 ---- */
void P122_CarGlow(int32_t car) {
  if (car < 0 || car >= 65) return;            /* P98_CarMat — 65 матриц */
  const uint8_t *c = (const uint8_t *)&P99_Cars[car];
  float v[4][3] = { { -350.0f, 0.0f, -500.0f }, { 350.0f, 0.0f, -500.0f },
                    { 350.0f, 0.0f, -1500.0f }, { -350.0f, 0.0f, -1500.0f } };
  P44_MatPtr = P98_CarMat[car];
  for (int k = 0; k < 4; k++) P44_XformT(v[k]);
  for (int k = 0; k < 4; k++) { v[k][0] += (float)rd32(c + 0xc8); v[k][2] += (float)rd32(c + 0xd0); }
  for (int k = 0; k < 4; k++) v[k][1] = (float)(-0x14 - P100_RoadHeightF(v[k]));
  quad_tail(v, P122_GlowRec, 3, 1);
}

/* ---- 004ba31b ---- */
void P122_ObjATick(void) {
  for (int32_t i = 0; i < 200; i++) {
    uint8_t *o = &P95_ObjA[i * 0x78];
    uint32_t f = (uint32_t)rd32(o + 0x68);
    if ((f & 2) == 0) continue;
    if (f & 4) P100_PartStep((float *)o);
    else if (f & 8) P123_ObjAFall(o);
    else if (f & 0x8000) StepSpeedA_004B9E2B(o);
    else if (f & 0x1000) StepSpeedB_004B9E54(o);
    if (f & 0x9000) {
      int32_t t = rd32(o + 0x58) - rd32(o + 0x5c);
      wr32(o + 0x58, t);
      if (t < 1) { wr32(o + 0x58, 0); wr16(o + 0x64, 1); }
      wr16(o + 0x64, (int16_t)(rd16(o + 0x64) - 1));
      if (rd16(o + 0x64) == 0) { wr32(o + 0x68, 0); PoolPush004AC702((uint16_t)rd16(o + 0x6c)); }
    }
  }
}

/* ---- 0040d56c ---- */
void P122_MapNames(const uint8_t *hdr, const char *names, uint8_t page) {
  const uint8_t *r = (const uint8_t *)names + rd32(hdr + 4);
  for (int32_t i = 0; i < rd16(hdr + 0xc); i++, r += 0xc) {
    const char *s = names;
    for (int32_t n = rd16(r + 10); n != 0; n--) while (*s++ != '\0') {}
    uint8_t *d = (uint8_t *)P54_MapAPtr + P54_MapA * 0x10;
    for (int32_t k = 0; k < 8; k++) {
      char ch = s[k];
      if (ch == '\0' || ch == '.') { d[k] = 0; break; }
      d[k] = (uint8_t)((ch >= 'a' && ch <= 'z') ? ch - 0x20 : ch);   /* 0052b9c0 toupper */
    }
    d[8] = page; d[9] = r[4]; d[10] = r[5]; d[11] = r[6]; d[12] = r[8];
    P54_MapA++;
  }
}

/* ---- 004a44d4 ---- */
char *P122_EventsParse(char *p) {
  P122_EvCur = (uint8_t *)P98_DebugMalloc(0x24, "D:\\Driver\\Game\\compiler.c", 0x216);
  if (P122_EvCur == NULL) { P26_ErrorInLine("Not enough memory for events!"); return NULL; }
  memset(P122_EvCur, 0, 0x24);
  uint32_t a = re_addr(P122_EvCur);
  if (G00D12408 == 0) G00D12408 = (int32_t)a;
  else {
    uint8_t *e = (uint8_t *)re_ptr((uint32_t)G00D12408);
    while (e != NULL && re_rd_addr(e + 0x20) != 0) e = (uint8_t *)re_rd_ptr(e + 0x20);
    if (e != NULL) re_wr_addr(e + 0x20, a);
  }
  P122_Ev118 = 0; P122_Ev240 = 0;
  while (p != NULL && P51_PrefixMatch(p, "EVENT_END") != 1) {
    const uint8_t *q = SkipToIdentStart_004A596B((const uint8_t *)p);
    uint32_t r = P123_EvLine(re_addr(q), a);
    char *n = (char *)re_ptr(r);
    if (n == NULL) return NULL;          /* native: строка вне известных областей */
    p = SkipLine004A59C6(n);
  }
  wr16(P122_EvCur + 4, (int16_t)P122_Ev24C);
  return p;
}

/* ---- 0040a8b0 ---- */
static void font_wr(uint32_t off, const void *src, uint32_t n) {   /* off — от 005d57a0; все псевдонимы таблицы */
  if (off + n <= sizeof(P58_Font)) memcpy(&P58_Font[off], src, n);
  if (off >= 0xe && off - 0xe + n <= sizeof(P14_005d57ae)) memcpy(&P14_005d57ae[off - 0xe], src, n);
  if (off >= 0xe && off - 0xe + n <= sizeof(A_005D57AE)) memcpy(&A_005D57AE[off - 0xe], src, n);
}
int32_t P122_FontIcons(uint32_t prefix, int32_t font, int32_t a3, int32_t a4, int32_t a5) {
  const char *pre = (const char *)re_ptr(prefix);
  uint32_t base = (uint32_t)(font & 0xff) * 0x806, last = 0xffffffffu;
  if (pre == NULL) return -1;            /* native: строка вне известных областей */
  for (int32_t c = 0; c < 0x100; c++) {
    char nm[64];
    snprintf(nm, sizeof nm, "%s%d", pre, c);
    const uint8_t *ic = P93_FindIcon(nm);
    uint32_t g = base + 0xe + (uint32_t)c * 8;
    int16_t z = 0;
    if (ic == NULL) { font_wr(g, &z, 2); continue; }
    int16_t pg = ic[8], one = 1;
    uint8_t uvwh[4] = { ic[9], ic[10], (uint8_t)(ic[0xb] ? ic[0xb] : 0xff), (uint8_t)(ic[0xc] ? ic[0xc] : 0xff) };
    font_wr(g + 2, &pg, 2); font_wr(g, &one, 2); font_wr(g + 4, uvwh, 4);
    last = ic[8];
  }
  int16_t h[3] = { (int16_t)a5, (int16_t)a3, (int16_t)a4 };
  font_wr(base + 8, h, 6);
  return (int32_t)last;
}

/* ---- 004e7450 ---- */
void P122_IconCopy(int32_t dst, const char *name) {
  const uint8_t *s = P93_FindIcon(name), *d = (const uint8_t *)re_ptr((uint32_t)dst);
  if (s == NULL || d == NULL) return;
  uint32_t sw = s[0xb] ? s[0xb] : 0x100, sh = s[0xc] ? s[0xc] : 0x100;
  uint32_t dw = d[0xb] ? d[0xb] : 0x100, dh = d[0xc] ? d[0xc] : 0x100;
  if (sw != dw || sh != dh || s[8] >= 16 || d[8] >= 16) return;   /* native: страница вне P65_Texs — пропуск */
  uint8_t *dp = (uint8_t *)P65_Texs[d[8]].p, *sp = (uint8_t *)P65_Texs[s[8]].p;
  if (sp == NULL || dp == NULL) return;
  const uint8_t *src = sp + ((uint32_t)s[10] * 0x100 + s[9]) * 2;
  uint8_t *out = dp + ((uint32_t)d[10] * 0x100 + d[9]) * 2;
  for (uint32_t y = 0; y < sh; y++, src += 0x200, out += 0x200) memmove(out, src, sw * 2);
  P12_Fn0048A46B(d[8], (int32_t)re_addr(dp));
}

/* ---- 004f8485 ---- */
int32_t P122_SetVar(p42_cmd_t *cmd, p42_var_t *var) {
  int32_t idx = 0;
  if (var == NULL) {
    var = &P42_Vars[0];
    const int32_t nvars = (int32_t)(sizeof P42_Vars / sizeof P42_Vars[0]);   /* native: таблица без 0x7f — не выходить за её конец */
    while (idx < nvars && var->type != 0x7f && strcmp(P65_Tok, var->name) != 0) { idx++; var++; }
    if (idx >= nvars || strlen(var->name) == 0) return 9;
    cmd = &P42_Cmds[2];
  }
  if (cmd->id != 2) return 9;
  int32_t *rec;
  if (var->type == 1) {
    int32_t r = P96_ParseQuoted(P65_Line, P65_Tok);
    if (r != 0) return r;
    if (idx == 0) { P59_VarSetString(0, P65_Tok); return 0; }
    P77_ListAdd((int32_t)strlen(P65_Tok) + 9);
    rec = (int32_t *)P77_List[P77_ListN - 1];
    rec[0] = 2; rec[1] = idx;
    strcpy((char *)(rec + 2), P65_Tok);
  } else {
    int32_t r = P65_ReadInts(cmd);
    if (r != 0) return r;
    P77_ListAdd(0xc);
    rec = (int32_t *)P77_List[P77_ListN - 1];
    rec[0] = 2; rec[1] = idx; rec[2] = P65_Ints[0];
  }
  return 0;
}

/* ---- 004a05fa ---- */
static const char *const k_objnames[18][9] = {
  { "CONE", "CONE1", "CONE2", "CONE3", "TRAININGCONES1", "TRAININGCONES2", "TRAININGCONES3", "TRAININGCONES4", "BIGCONE" },
  { "BALLARD", "BALLARD2" }, { "BIN1", "BIN2" }, { "BOX", "BOX1", "BOX2", "BOX3", "PAPERBOX", "PAPERBOX2" },
  { "BARR1", "CP_BARRIER", "FENCE" }, { "PHONE", "PHONE1", "PHONE2" },
  { "SIGN1", "SIGN2", "SIGN3", "SIGN4", "SIGN5", "SIGN6" }, { "TABLE", "TABLE2" }, { "CHAIR", "CHAIR2" },
  { "PARK_M" }, { "BOARD1", "BOARD2", "BOARD3" }, { NULL }, { "TAR_DRUM", "DRUM" }, { "BENCH" }, { "HOTDOGS" },
  { NULL }, { NULL } /* 16: GLASS01..GLASS34 */, { "UMBRELLA", "PARASOL" } };
int32_t P122_ObjNames(void) {
  uint32_t k = 0;
  for (int c = 0; c < 18; c++) {
    P69_Ptrs[c] = P69_TBASE + k * 4;
    if (c == 16) {
      for (int i = 0; i < 0x22; i++) { char nm[16]; snprintf(nm, sizeof nm, "GLASS%02d", i + 1); P69_Thr[k++] = (uint32_t)P20_FindNameNoCase(nm); }
    } else
      for (int i = 0; i < 9 && k_objnames[c][i] != NULL; i++) P69_Thr[k++] = (uint32_t)P20_FindNameNoCase(k_objnames[c][i]);
  }
  for (int c = 0; c < 18; c++)
    for (uint8_t b = 1; P69_Ptrs[c] + (uint32_t)b * 4 < P69_Ptrs[c + 1]; b++)
      for (uint8_t j = b; j-- != 0;) {
        uint32_t i = (P69_Ptrs[c] - P69_TBASE) / 4 + j;
        if (i + 1 >= 79) break;
        if (P69_Thr[i + 1] < P69_Thr[i]) { uint32_t t = P69_Thr[i]; P69_Thr[i] = P69_Thr[i + 1]; P69_Thr[i + 1] = t; }
      }
  return 0;
}

/* ---- 0041ab60 ---- */
static void name_put(int32_t i, uint8_t v) { if (i >= 0 && i < (int32_t)sizeof(P12_005fee60)) P12_005fee60[i] = v; }
int32_t P122_NameMenu(void) {
  CopyWord0041AD8D();
  P8_005feee8 = 0; P8_005feeec = 0; G005FEEEC = 0;
  P97_MenuCall2(0x0054e948u, 0, 0x0054e828u);
  while (P8_005feee8 != -1) {
    Call00522323();
    P36_PollInput();
    if (P12_005feef0 == 0) {
      RedMarkers_0041ADA1();
      P8_005feee8 = P110_MenuSel(0x0054e948u, P8_005feee8);
    } else {
      int32_t k = P74_KeyScan();
      switch (k) {
      case 0: break;
      case -3: Ui00418886(); P12_005feef0 = 0; P12_005feef4 = 0; P55_NamesC(); break;
      case -2: if (P12_005feef8 != 0) { Ui00418886(); P12_005feef4 = 1; P12_Fn0041AF85(); } break;
      case -1:
        if (0 < P12_005feef8) { Ui00418886(); P12_005feef8--; name_put(P12_005feef8 + P8_005feeec * 0x11, 0); }
        break;
      default:
        if (P12_005feef8 < 0xf) {
          Ui00418886();
          name_put(P12_005feef8 + P8_005feeec * 0x11, (uint8_t)k);
          P12_005feef8++;
          name_put(P12_005feef8 + P8_005feeec * 0x11, 0);
        }
      }
    }
    if (--P122_Blink < 0) { P122_Blink = 10; P122_BlinkOn ^= 1; }
    if (P12_005feef0 == 0 || P122_BlinkOn == 0) P66_ScreenFrame(0x0054e828u, 0);
    else {
      int32_t i = P12_005feef8 + P8_005feeec * 0x11;
      name_put(i, 0x2e); name_put(i + 1, 0);
      P66_ScreenFrame(0x0054e828u, 0);
      name_put(i, 0);
    }
  }
  return 0;
}
