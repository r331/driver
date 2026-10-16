/* v1.45: 30 функций (см. ported100.h). Стандарт указателей v1.42: адреса таблиц меню, буферов повтора и текстурных страниц —
   uint32_t + re_ptr; глобальные скалярные указатели (значки, буфер записи, вывод отсечения, маска зеркала) — родные. */
#include "ported100.h"
#include "p100_data.h"
#include "cartab.h"
#include "crt.h"
#include "director.h"
#include "menustate.h"
#include "smallfuncs.h"
#include "smallfuncs2.h"
#include "globalsets.h"
#include "uihandlers3.h"
#include "strtab.h"
#include "ported4.h"
#include "ported5.h"
#include "ported6.h"
#include "ported7.h"
#include "ported9.h"
#include "ported11.h"
#include "ported12.h"
#include "ported14.h"
#include "ported15.h"
#include "ported20.h"
#include "ported21.h"
#include "ported36.h"
#include "ported43.h"
#include "ported44.h"
#include "ported51.h"
#include "ported54.h"
#include "ported55.h"
#include "ported56.h"
#include "ported57.h"
#include "ported58.h"
#include "ported59.h"
#include "ported62.h"
#include "ported63.h"
#include "ported68.h"
#include "ported69.h"
#include "ported72.h"
#include "ported74.h"
#include "ported75.h"
#include "ported79.h"
#include "ported84.h"
#include "ported88.h"
#include "ported93.h"
#include "ported94.h"
#include "ported95.h"
#include "ported97.h"
#include "ported98.h"
#include "ported99.h"
#include "../platform/plat.h"
#include <math.h>
#include <string.h>

#ifndef RE_HOOK_BUILD
p100_c810_t P100_MenuC810 = P100_C810_INIT;
p100_d4a8_t P100_MenuD4A8 = P100_D4A8_INIT;
p100_e0b0_t P100_MenuE0B0 = P100_E0B0_INIT;
p100_u9_t P100_SpeedTab = P100_E33C_U32;
int32_t P100_ItemN = 1;   /* .data 0054e230 */
#endif
GAME_VAR_DEF(uint32_t, P100_ItemTab, 0x005fea48)
GAME_VAR_DEF(int32_t, P100_ItemSel, 0x005fe9f4)
GAME_VAR_DEF(uint8_t *, P100_IconFfwd, 0x005fe9fc)
GAME_VAR_DEF(uint8_t *, P100_IconPlay, 0x005fea00)
GAME_VAR_DEF(uint8_t *, P100_IconAccept, 0x005fea04)
GAME_VAR_DEF(p100_f3_t, P100_PartBase, 0x00c81b60)
GAME_VAR_DEF(p100_partofs_t, P100_PartOfs, 0x00c81e20)
GAME_VAR_DEF(p100_nodes_t, P100_PartNodes, 0x00c82020)
GAME_VAR_DEF(int32_t, P100_PartModel, 0x00c821a4)
GAME_VAR_DEF(int32_t, P100_PartMode, 0x00c821a8)
GAME_VAR_DEF(int32_t, P100_PartFlags, 0x00c824e0)
GAME_VAR_DEF(int32_t, P100_PartModelA, 0x00c97a30)
GAME_VAR_DEF(int32_t, P100_PartModelB, 0x00ce1f40)
GAME_VAR_DEF(int32_t, P100_PartRotA, 0x00d00254)
GAME_VAR_DEF(int32_t, P100_PartRotB, 0x00c98ec4)
GAME_VAR_DEF(p100_ang_t, P100_DebAng, 0x01123200)
GAME_VAR_DEF(p100_m16_t, P100_DebMat, 0x01105d20)
GAME_VAR_DEF(p100_tri_t, P100_DebTri, 0x011173e0)
GAME_VAR_DEF(uint8_t *, P100_RecBuf, 0x00b5a854)
GAME_VAR_DEF(int32_t, P100_RecKeys, 0x00d1187c)
GAME_VAR_DEF(p100_u5_t, P100_RecPtr, 0x00c4d720)
GAME_VAR_DEF(p100_u5_t, P100_RecRep, 0x00c4d780)
GAME_VAR_DEF(p100_i5_t, P100_RecTot, 0x00c4d880)
GAME_VAR_DEF(p100_i5_t, P100_RecOff, 0x00c4d940)
GAME_VAR_DEF(p100_i5_t, P100_RecVal, 0x00c4da40)
GAME_VAR_DEF(int32_t, P100_RecEnd, 0x00c4da54)
GAME_VAR_DEF(p100_i5_t, P100_RecCnt, 0x00c55020)
GAME_VAR_DEF(uint8_t, P100_RecStop, 0x00b5a8ab)
GAME_VAR_DEF(int32_t, P100_B87E24, 0x00b87e24)
GAME_VAR_DEF(int32_t, P100_1426FC, 0x011426fc)
GAME_VAR_DEF(int32_t, P100_143720, 0x01143720)
GAME_VAR_DEF(int32_t, P100_RadarX, 0x00b32a28)
GAME_VAR_DEF(int32_t, P100_RadarZ, 0x00b32a2c)
GAME_VAR_DEF(int32_t, P100_Radar16, 0x00bdfaa0)
GAME_VAR_DEF(uint8_t *, P100_RadarIcon, 0x00c8088c)
GAME_VAR_DEF(p100_i4_t, P100_Rect, 0x00c1cd00)
GAME_VAR_DEF(uint32_t, P100_PixFn, 0x0057b73c)
GAME_VAR_DEF(p100_i7_t, P100_LfbFmt, 0x005c6744)
GAME_VAR_DEF(int32_t, P100_LfbPitch, 0x005c6764)
GAME_VAR_DEF(p100_pal_t, P100_Pal32, 0x012710c0)
GAME_VAR_DEF(int32_t, P100_ClipN, 0x0115a070)
GAME_VAR_DEF(float *, P100_ClipOut, 0x0115a078)
GAME_VAR_DEF(uint8_t *, P100_Mirror, 0x00b31f00)

/* .rdata-константы Game.exe */
#define K_08   0.8f       /* 005461c0 */
#define K_2    2.0f       /* 00546050 */
#define K_099  0.99f      /* 00546088 */
#define K_4096 4096.0f    /* 005461ec */

static int32_t rd32(const void *p) { int32_t v; memcpy(&v, p, 4); return v; }
static void wr32(void *p, int32_t v) { memcpy(p, &v, 4); }
static uint16_t rd16(const void *p) { uint16_t v; memcpy(&v, p, 2); return v; }
static int16_t rd16s(const void *p) { int16_t v; memcpy(&v, p, 2); return v; }
static void wr16(void *p, uint16_t v) { memcpy(p, &v, 2); }
static float rdf(const void *p) { float v; memcpy(&v, p, 4); return v; }
static void wrf(void *p, float v) { memcpy(p, &v, 4); }
static int32_t iabs(int32_t v) { return v < 0 ? -v : v; }
static int32_t fround(float v) { return (int32_t)lrintf(v); }   /* fistp */
static uint8_t *texpage(uint32_t slot) { return (uint8_t *)re_ptr((uint32_t)rd32(&g_01145a60[slot * 0x10 + 4])); }

/* ---- 00416605: меню повтора — значки FFWD/PLAY/ACCEPT8B, число видимых пунктов, скорость по пункту с флагом 8 ---- */
void P100_ReplayMenuInit(void) {
  P100_IconFfwd = P93_FindIcon("FFWD");
  P100_IconPlay = P93_FindIcon("PLAY");
  P100_IconAccept = P93_FindIcon("ACCEPT8B");
  P9_005fe9f0 = 1;
  P58_S5FE9F8 = 0;
  P100_ItemN = 0;
  const uint8_t *t = (const uint8_t *)re_ptr(P100_ItemTab);
#ifndef RE_HOOK_BUILD
  if (t != NULL)   /* 00417b80 (ставит таблицу) не перенесён: без таблицы пунктов нет */
#endif
  while (P100_ItemN < 4 && (rd16(t + P100_ItemN * 8) & 1) == 0) {
    uint16_t f = rd16(t + P100_ItemN * 8);
    if ((f & 0x10) == 0) P58_S5FE9F8++;
    if ((f & 8) != 0) {
      uint32_t v = rd16(t + 2 + P100_ItemN * 8);
      if (v >= 3) v = 2;
      P68_B87E54 = (int32_t)P100_SpeedTab[v * 3];
    }
    P100_ItemN++;
  }
#ifndef RE_HOOK_BUILD
  if (P100_ItemN == 0) P100_ItemSel = 0; else   /* в оригинале деление на 0 невозможно: пункт 0 без флага 1 */
#endif
  P100_ItemSel = P58_S5FE9F8 % P100_ItemN;
  SelectByDifficulty_00416D17();
}

/* ---- 00413e37: экран руля/джойстика — таблицы пунктов по режиму 01271060 и устройству 00575ef0 ---- */
static void menu_items(uint32_t a) {
  P58_S5FE9B8 = a;
#ifndef RE_HOOK_BUILD
  P15_MenuItems = UiPtr005FE9B8 = (uint8_t *)re_ptr(a);   /* псевдонимы 005fe9b8 в native */
#endif
}
static void menu_text(uint32_t a) {
  P58_S5FE9B0 = a;
#ifndef RE_HOOK_BUILD
  P15_MenuText = (uint8_t *)re_ptr(a);
#endif
}
static void menu_mode(int32_t m) {
  P15_MenuMode = m;
#ifndef RE_HOOK_BUILD
  G6_005FE9BC = m;
#endif
}
void P100_PadMenuInit(void) {
  int32_t base = -1;
  switch (MenuMode1271060) {
  case 1: case 2: case 4: case 5:
    menu_mode(1); menu_items(0x0054d670); menu_text(0x0054d4a8); base = 0x7a; P97_MenuCall0(0x0054d800, 0); break;
  case 3: case 7:
    menu_mode(0); menu_items(0x0054d4d0); menu_text(0x0054d4a8); base = 0x82; P97_MenuCall0(0x0054d620, 0); break;
  case 6: case 0xb:
    menu_mode(2); menu_items(0x0054d530); menu_text(0); base = 0x86; P97_MenuCall0(0x0054d620, 0); break;
  }
  int32_t n;
  if (P15_MenuMode == 0 || P15_MenuMode == 2) {
    switch (MenuState575EF0) {
    case 2: P58_S5FE9B4 = 0x0054d5b0; P15_SetHighlightRange(3, 4); break;
    case 3: P58_S5FE9B4 = 0x0054d5e0; P15_SetHighlightRange(4, 4); break;
    case 4: P58_S5FE9B4 = 0x0054d620; P15_SetHighlightRange(5, 4); break;
    default: MenuState575EF0 = 1; /* fallthrough */
    case 1: P58_S5FE9B4 = 0x0054d590; P15_SetHighlightRange(2, 4); break;
    }
    n = 4;
  } else {
    switch (MenuState575EF0) {
    case 2: P58_S5FE9B4 = 0x0054d740; P15_SetHighlightRange(5, 8); break;
    case 3: P58_S5FE9B4 = 0x0054d790; P15_SetHighlightRange(7, 8); break;
    case 4: P58_S5FE9B4 = 0x0054d800; P15_SetHighlightRange(9, 8); break;
    default: MenuState575EF0 = 1; /* fallthrough */
    case 1: P58_S5FE9B4 = 0x0054d710; P15_SetHighlightRange(3, 8); break;
    }
    n = 8;
  }
  uint8_t *it = (uint8_t *)re_ptr(P58_S5FE9B8);
  if (base < 0 || it == NULL) return;   /* режим вне таблицы: в оригинале — неинициализированный индекс строки */
  wr32(it + 8, (int32_t)P97_StrAddr[0x6f]);   /* 00c559dc */
  for (int32_t k = 0; k < n; k++) wr32(it + 0x18 + k * 0x10, (int32_t)P97_StrAddr[base + k]);
}

/* ---- 004f3c74 / 004f1325: иерархия деталей (узел: [0] модель, [1] число детей или 0xff — лист, [2..] дети) ---- */
static void part_xform_leaf(const float *pos, const float *q, float *m44, float *v) {
  v[0] = (pos[0] - P44_CamX) + P100_PartBase[0];
  v[1] = (pos[1] - P44_CamY) + P100_PartBase[1];
  v[2] = (pos[2] - P44_CamZ) + P100_PartBase[2];
  P44_MatPtr = (float *)P44_ViewMatT;
  P44_Xform(v);
  P43_QuatToMat(q, m44);
}
static void part_child(const float *quats, const uint8_t *node, const float *q, const float *pos, float *q5, float *v) {
  float m44[16];
  P44_QuatMul(quats + (uint32_t)node[0] * 5, q, q5);
  memcpy(v, &P100_PartOfs[(uint32_t)node[0] * 4], 16);
  P43_QuatToMat(q, m44);
  P44_MatPtr = m44;
  P44_Xform(v);
  v[0] += pos[0]; v[1] += pos[1]; v[2] += pos[2];
}
static const uint8_t *part_node(uint32_t i) {
#ifndef RE_HOOK_BUILD
  if (i * 8 >= sizeof P100_PartNodes) return NULL;
#endif
  return &P100_PartNodes[i * 8];
}
void P100_DrawParts(uint8_t *obj, const float *quats, const uint8_t *node, const float *q, const float *pos) {
  if (node[1] == 0xff) {
    float v[3], m44[16], mt[16];
    part_xform_leaf(pos, q, m44, v);
    if (node[0] == (uint32_t)P100_PartRotA || node[0] == (uint32_t)P100_PartRotB) P44_RotY(m44, rd32(obj + 0x50));
    P44_Transpose(m44, mt);
    P84_DrawModel(P79_ModelTab[P100_PartModel + node[0]], mt, v, P100_PartMode - 1);
  } else {
    float q5[5], v[4];
    part_child(quats, node, q, pos, q5, v);
    for (int32_t i = 0; i < node[1]; i++) {
      const uint8_t *c = part_node(node[i + 2]);
      if (c != NULL) P100_DrawParts(obj, quats, c, q5, v);
    }
  }
}
void P100_DrawPartsB(const float *quats, const uint8_t *node, const float *q, const float *pos) {
  if (node[1] == 0xff) {
    float v[3], m44[16], mt[16];
    part_xform_leaf(pos, q, m44, v);
    P44_Transpose(m44, mt);
    if ((P100_PartFlags & 1) == 0) P84_DrawModel(P79_ModelTab[P100_PartModelA + node[0]], mt, v, P100_PartMode - 1);
    else P84_DrawModel(P79_ModelTab[P100_PartModelB + node[0]], mt, v, P100_PartMode - 1);
  } else {
    float q5[5], v[4];
    part_child(quats, node, q, pos, q5, v);
    for (int32_t i = 0; i < node[1]; i++) {
      const uint8_t *c = part_node(node[i + 2]);
      if (c != NULL) P100_DrawPartsB(quats, c, q5, v);
    }
  }
}

/* ---- 004ab500: сброс обломков — 0x100 повёрнутых треугольников, 100 записей обломков ---- */
void P100_DebrisInit(void) {
  P14_Fn0048DB65(P97_Debris, 6000);
  P14_Fn0048DB65(S_010FB0E0, 200);
  P100_DebAng[0] = 0; P100_DebAng[1] = 0; P100_DebAng[2] = 0;
  for (int32_t i = 0; i < 0x100; i++) {
    float *t = &P100_DebTri[i * 12];
    P43_EulerMatrix(P100_DebMat, P100_DebAng);
    P44_MatPtr = P100_DebMat;
    t[0] = -30.0f; t[1] = 7.0f;  t[2] = 0.0f;
    t[4] = 0.0f;   t[5] = -7.0f; t[6] = 0.0f;
    t[8] = 30.0f;  t[9] = 7.0f;  t[10] = 0.0f;
    P44_Xform(t); P44_Xform(t + 4); P44_Xform(t + 8);
    P100_DebAng[0] = (int16_t)((P100_DebAng[0] + 0x10) & 0xfff);
    P100_DebAng[1] = (int16_t)((P100_DebAng[1] + 0x60) & 0xfff);
    P100_DebAng[2] = (int16_t)(P100_DebAng[2] & 0xfff);
  }
  for (int32_t i = 0; i < 100; i++) {
    wr16(&P97_Debris[i * 0x3c + 0x26], 0);
    wr16(&P97_Debris[i * 0x3c + 0x24], (uint16_t)i);
    wr16(&S_010FB0E0[i * 2], (uint16_t)i);
  }
  S_010FFA24 = 0;
}

/* ---- 004f556c: проверка целей по 10 объектам 00c80ce0 (шаг 0x34) ---- */
void P100_GoalsCheck(uint8_t *goal) {
  for (int32_t k = 0; k < 10; k++) {
    uint8_t *o = P58_Objs[k];
    uint32_t f = (uint32_t)rd32(o + 0x10);
    if ((f & 1) == 0 || (f & 0x80) != 0) continue;
    int32_t dx = iabs(rd32(o + 0x14) - P59_PosX);
    int32_t dz = iabs(rd32(o + 0x1c) - P59_PosZ);
    int32_t d = dx < dz ? dz + dx / 2 : dx + dz / 2;
    wr32(o + 0x10, (int32_t)(f & 0xfffffffdu));
    if (P97_GoalReached(d, goal, o) == 0 && P97_GoalCops(d, goal, o) == 0) P99_GoalCheck(d, goal, (int32_t *)o);
  }
}

/* ---- 004d28a3: звуки машины игрока по дороге/скорости ---- */
void P100_CarSounds(uint8_t *tab) {
  uint8_t h = (uint8_t)Round1024(P94_HeadingI);
  uint16_t w = (uint16_t)P72_RoadWord(P59_PosX, P59_PosZ);   /* третий аргумент (курс) 0051b111 не читает */
  (void)h;
  if (w == 0xffff) P99_RoadPick = -1;
  else if (w == 0x8000) { }
  else if (w < 0x4000 && (int32_t)w != P99_RoadPick) {
    if (P99_JunctionBlock(w) != 0) P95_SndTrigger(tab, 3, 0x1000);
    P99_RoadPick = (int16_t)w;
  }
  if (P14_00b87e84 != 0 && 1000 < P99_Cars[0].vel[0] && 1000 < P99_Cars[0].vel[1]) P95_SndTrigger(tab, 9, 0x1000);
  if (P99_Cars[0].f104 != 0 || P98_D078C8 != 0) P95_SndTrigger(tab, 10, 0x1000);
  if (200 < P62_Spd) P95_SndTrigger(tab, 2, 0x1000);
}

/* ---- 004d6740: обороты двигателя (+0x144) и нагрузка (+0x146) машины ---- */
void P100_CarRevs(int32_t car) {
  p99_car_t *c = &P99_Cars[car];
  int32_t thr = c->ff8;
  uint16_t cur = (uint16_t)c->f144, tgt;
  c->f143 = 0;
  if (c->f108 == 0) tgt = (uint16_t)P99_GearBox(car);
  else { tgt = 20000; c->gear = 0; if (cur < 8000) cur = 8000; }
  if ((int32_t)((uint32_t)cur - (uint32_t)tgt) < 0x2d1) {
    if (800 < (int32_t)((uint32_t)tgt - (uint32_t)cur)) tgt = (uint16_t)(cur + 800);
  } else { tgt = (uint16_t)(cur - 0x2d0); thr = 0; c->f143 = 1; }
  c->f144 = (int16_t)tgt;
  if (thr == 0 && c->speed < 0x1f) {
    c->f146 = (int16_t)(c->f146 + 100);
    if (10000 < c->f146) c->f146 = 10000;
  } else {
    int16_t lo = thr == 0 ? 2000 : 0;
    c->f146 = (int16_t)(c->f146 - 2000);
    if (c->f146 < lo) c->f146 = lo;
  }
}

/* ---- 00518d32: запись ввода игрока pad в буфер повтора (записи по 5 байт: повтор, клавиши, руль x, y) ---- */
static void rec_put(uint8_t rep, int32_t keys, int32_t x, int32_t y) {
  uint8_t *b = P100_RecBuf;
#ifndef RE_HOOK_BUILD
  if (b == NULL) { P74_C4BDE0 += 5; return; }   /* буфер 0x40000 выделяет неперенесённый код */
#endif
  b += P74_C4BDE0;
  b[0] = rep; wr16(b + 1, (uint16_t)keys); b[3] = (uint8_t)x; b[4] = (uint8_t)y;
  P74_C4BDE0 += 5;
}
void P100_RecInput(int32_t p) {
  if (P74_B5A894 == 0) return;
  if (G8_00B87EAC != 0) P74_C4D668++;
  if (P74_C4BDE0 >= 0x3fffc) { P74_B5A894 = 0; return; }
  if (P100_RecKeys == P74_C4D7A0[p] && (uint32_t)P74_B5A858[p] < 0xff && P74_C4DA58 <= P62_Frame &&
      P36_JoyX == P74_B5A86C[p] && P21_AxisValue == P74_B5A880[p]) {
    P74_B5A858[p]++;
    return;
  }
  if (P74_B5A858[p] != 0) {
    if (P74_C4BDE0 != 0) P74_C4BDE0 -= 5;
    rec_put((uint8_t)P74_B5A858[p], P74_C4D7A0[p], P74_B5A86C[p], P74_B5A880[p]);
  }
  P74_B5A858[p] = 0;
  rec_put(0, P100_RecKeys, P36_JoyX, P21_AxisValue);
  P74_C4D7A0[p] = P100_RecKeys;
  P74_B5A86C[p] = P36_JoyX;
  P74_B5A880[p] = P21_AxisValue;
  P74_C54D08++;
}

/* ---- 00518f44: чтение ввода игрока pad из повтора; 0x20 — нет данных ---- */
static int32_t rec_mine(int32_t p) { return p == 0 || (P88_Mode575 == 2 && G6_00B87EA0 != 0); }
int32_t P100_RecRead(int32_t p) {
  if (P100_RecPtr[p] == 0) return 0x20;
  if (P58_SB87EB0 != 0 && (P75_E4 != 0 || P100_1426FC != 0 || P100_143720 != 0)) return 0x20;
  if (P100_RecRep[p] != 0) {
    P100_RecRep[p]--;
    if (rec_mine(p)) { P36_JoyX = P74_B5A86C[p]; P21_AxisValue = P74_B5A880[p]; }
    return P100_RecVal[p];
  }
  if (P100_RecCnt[p] == P100_RecTot[p] && (G6_00B87EA0 == 0 || P88_Mode575 != 2 || p == 0)) {
    if (G6_00B87EA0 != 0) { SetMode2_004E612A(); return 0x20; }
    if (P58_SB87EB0 != 0) {
      if (P100_1426FC == 0 && P75_E4 == 0 && P100_143720 == 0) P100_143720 = 1;
      if (P100_RecPtr[0] == 0) return 0x20;
      if (P100_RecCnt[0] == P100_RecTot[0]) {
        if (P100_RecEnd == 0) { G6_00B87E20 = 0; P100_B87E24 = 100; return 0; }
        P100_RecStop = 1;
        GlobalSet00519DDB();
        P43_CdFadeInit();
      }
    }
    return 0x20;
  }
  const uint8_t *e = (const uint8_t *)re_ptr(P100_RecPtr[p] + (uint32_t)P100_RecOff[p]);
#ifndef RE_HOOK_BUILD
  if (e == NULL) return 0x20;
#endif
  P100_RecRep[p] = e[0];
  P100_RecVal[p] = rd16s(e + 1);
  P74_B5A86C[p] = (int8_t)e[3];
  P74_B5A880[p] = (int8_t)e[4];
  if (rec_mine(p)) { P36_JoyX = P74_B5A86C[p]; P21_AxisValue = P74_B5A880[p]; }
  P100_RecOff[p] += 5;
  P100_RecCnt[p]++;
  return P100_RecVal[p];
}

/* ---- 00504479: окно карты радара 128×128 вокруг игрока (или объекта 00d0cbd0) в текстуру значка 00c8088c ---- */
void P100_RadarMap(int32_t force) {
  int32_t cx, cz;
  if (G8_00B87EAC == 0) { cx = (P59_PosX + 0x2ee) / 0x5dc + P57_ScrW / 2; cz = (0x2ee - P59_PosZ) / 0x5dc + S_00C808A0 / 2; }
  else { cx = (P88_ObjX + 0x2ee) / 0x5dc + P57_ScrW / 2; cz = (0x2ee - P88_ObjZ) / 0x5dc + S_00C808A0 / 2; }
  if (cx == P100_RadarX && cz == P100_RadarZ && force == 0) return;
  P100_RadarX = cx; P100_RadarZ = cz;
  P12_00b32970 = 0x80;
  P12_00b52a38 = P57_ScrW - 0x80;
  const uint8_t *ic = P100_RadarIcon;
  uint8_t *map = (uint8_t *)P99_C80880;
#ifndef RE_HOOK_BUILD
  if (ic == NULL || map == NULL) return;
#endif
  if (P100_Radar16 == 0) {
    uint8_t *page = texpage(ic[8]);
#ifndef RE_HOOK_BUILD
    if (page == NULL) return;
#endif
    P14_Fn00504439(map + (cz - 0x40) * P57_ScrW - 0x40 + cx, page + ic[9] + (uint32_t)ic[10] * 0x100);
    P12_Fn0048A46B(ic[8], rd32(&g_01145a60[(uint32_t)ic[8] * 0x10 + 4]));
  } else {
    uint8_t *src = map + (cz - 0x40) * P57_ScrW * 2 - 0x80 + cx * 2;
    P12_Fn00504699((int32_t)re_addr(src), (int32_t)re_addr(P56_Page + (uint32_t)ic[10] * 0x100 + ic[9]));
    CallIf424A02(ic[8], (int32_t)re_addr(P56_Page));
  }
}

/* ---- 0051acc5 / 0051aee6: прямоугольник клеток узла дороги node со стороны side → 00c1cd00 ---- */
static int32_t road_rect(int32_t node, int32_t side, int32_t ox, int32_t oz) {
#ifndef RE_HOOK_BUILD
  if (node < 0 || node >= (int32_t)(sizeof P11_00bf1c40 / 0x42)) return 0;
#endif
  const uint8_t *r = &P11_00c12c60[node * 0x14];
  int8_t c = (int8_t)r[0x10];
  int8_t s = (int8_t)side;
  if (c == 0 && (s == 1 || s == 3)) return 0;
  if (c == 1 && (s == 0 || s == 2)) return 0;
  P100_Rect[0] = rd32(r) + ox;
  P100_Rect[1] = rd32(r + 4) + oz;
  P100_Rect[2] = rd32(r + 8) + ox;
  P100_Rect[3] = rd32(r + 0xc) + oz;
  uint8_t m = P11_00bf1c40[node * 0x42 + 7], n = P11_00bf1c40[node * 0x42 + 6], bits = 0;
  for (uint32_t k = n; k != 0; k--) { if (m & 1) bits++; m >>= 1; }
  uint32_t rest = (uint8_t)(n - bits);
  if (c == 0) { if (s == 0) P100_Rect[0] += (int32_t)rest; else P100_Rect[2] -= bits; }
  else { if (s == 3) P100_Rect[3] -= bits; else P100_Rect[1] += (int32_t)rest; }
  return 1;
}
int32_t P100_RoadRect(int32_t node, int32_t side) { return road_rect(node, side, 0, 0); }
void P100_RoadRectAbs(int32_t node, int32_t side) { road_rect(node, side, P62_Map1C0C, P62_MapCC90); }

/* ---- 004dd039 / 004dc91b: высота поверхности дороги в точке (x, z) (минус уровень клетки, если вне многоугольников) ---- */
static int32_t road_height(int32_t x, int32_t z) {
  if (P72_RoadLookup(x, z) == 0) return 0;
  const uint8_t *blk = NULL;
#ifndef RE_HOOK_BUILD
  if (P72_Id < 0x4000)
#endif
    blk = (const uint8_t *)P58_BlkIdx[P72_Id];
  if (blk == NULL) return -P72_Low;
  int32_t fx = (x + 0x2ee + P62_MapC64) % 0x5dc;
  fx = 0x2ee - iabs(fx);
  int32_t fz = (P62_Map2C40 - (z - 0x2ee)) % 0x5dc;
  fz = 0x2ee - iabs(fz);
  uint32_t d = (uint32_t)(-(int32_t)P72_Dir) & 0xfff;
  int32_t u = x, v = z;
  if (d < 0x801) {
    if (d == 0x800) { v = -fz; u = fx; }
    else if (d == 0) { v = fz; u = -fx; }
    else if (d == 0x400) { v = fx; u = fz; }
  } else if (d == 0xc00) { v = -fx; u = -fz; }
  const uint8_t *q = blk + 8;
  for (int32_t k = 0; k < rd16s(blk + 6); k++, q += 0x34) {
    int32_t hit = rd16s(q + 0x30) == 4 ? P44_PointInQuad(u, v, (const int32_t *)q) : P14_Fn00526A34(u, v, (const int32_t *)q);
    if (hit != 0) {
      P11_00ba52d0 = fround((((float)v * rdf(q + 0x28) + (float)u * rdf(q + 0x20)) - rdf(q + 0x2c)) - (float)P72_Low);
      return P11_00ba52d0;
    }
  }
  return -P72_Low;
}
int32_t P100_RoadHeight(const int32_t *pos) { return road_height(pos[0], pos[2]); }
int32_t P100_RoadHeightF(const float *pos) {
  P11_00ba52d0 = fround(pos[0]);
  int32_t x = P11_00ba52d0;
  P11_00ba52d0 = fround(pos[2]);
  return road_height(x, P11_00ba52d0);
}

/* ---- 0049ae98: удар по машине — зона повреждения по направлению, очки ---- */
static int32_t hit_scored(const uint8_t *car) {
  if (car[0] == 0 || (G6_01136920 & 1) == 0) return 0;
#ifndef RE_HOOK_BUILD
  if ((uint32_t)(car[0] - 1) >= 0x40) return 0;
#endif
  return TrafficRecs[(car[0] - 1) * 0x54 + 5] == 0;
}
void P100_CarHit(uint8_t *car, const int32_t *a, const int32_t *b, int32_t force) {
  if (force < 0xa000) return;
  int32_t dx = b[0] - a[0], dz = b[2] - a[2];
  int32_t side = (a[4] * dx + 0x800 + a[6] * dz) >> 12;
  int16_t hw = 0;
#ifndef RE_HOOK_BUILD
  if (car[2] < 0x20)
#endif
    hw = (int16_t)(rd16s(&P100_CarDim[(uint32_t)car[2] * 0x16c + 4]) >> 1);
  int32_t zone;
  if (((a[8] * dx + 0x800 + a[10] * dz) >> 12) < 1) zone = hw < side ? 0 : (-(int32_t)hw < side) + 4;
  else zone = hw < side ? 1 : (side <= -(int32_t)hw) + 2;
  force /= 300;
  if (force > 0x800) force = 0x800;
  uint8_t *z = car + 0x11c + zone * 4;
  if (hit_scored(car)) P69_Bonus -= rd32(z);
  wr32(z, 0xfff - (((0xfff - force) * (0xfff - rd32(z)) + 0x800) >> 12));
  wr32(car + 0x138, rd32(car + 0x138) + force / 2);
  int32_t h = rd32(z) / 2;
  switch (zone) {
  case 0: if (rd32(car + 0x120) < h) wr32(car + 0x120, h); break;
  case 1: if (rd32(car + 0x11c) < h) wr32(car + 0x11c, h); break;
  case 3: if (rd32(car + 0x12c) < h) wr32(car + 0x12c, h); break;
  case 4: if (rd32(car + 0x128) < h) wr32(car + 0x128, h); break;
  }
  if (hit_scored(car)) { P69_Bonus += rd32(z); P69_AddScore(0xff00); }
}

/* ---- 004078d0: формат LFB (LfbLock(1)): шаг строки и байты формата +0x14..+0x1a, функция пикселя по глубине ---- */
int32_t P100_LfbFormat(void) {
  uint8_t info[0x1c];
  memset(info, 0, sizeof info);
  wr32(info, 0x14);
  if (P68_LfbLock(1, info) == 0) return 0;
  Dev0042480D(1);
  P100_PixFn = info[0x14] == 0x10 ? 0x0040232eu : 0x00402306u;
  P100_LfbPitch = rd32(info + 8);
  for (int32_t i = 0; i < 7; i++) P100_LfbFmt[i] = info[0x14 + i];
  return 1;
}

/* ---- 0048c43c: RIFF-звук из ресурса ---- */
int32_t P100_RiffFromRes(void *res, const void **fmt, const void **data, uint32_t *size) {
  return P98_RiffFind(plat_lock_resource(res), fmt, data, size) != 0;
}

/* ---- 0042eee6 / 0042d797: отсечение ребра a→b дальней (01270c24) / ближней (0054609c) плоскостью; вершины +0xc x, +0x10 y, +0x14 z ---- */
static void clip_emit(float x, float y, float z) {
  float *o = P100_ClipOut;
#ifndef RE_HOOK_BUILD
  if (o == NULL) return;
#endif
  o[0] = x; o[1] = y; o[2] = z;
}
static void clip_next(int32_t n) { P100_ClipN += n; }
void P100_ClipFar(const uint8_t *a, const uint8_t *b) {
  float F = Q01270C24, za = rdf(a + 0x14), zb = rdf(b + 0x14);
  if (!(za <= F || zb <= F)) return;
  if (F < za || F < zb) {
    if (za <= F || F < zb) {
      float t = (za - F) / (za - zb);
      clip_emit(rdf(a + 0xc) - (rdf(a + 0xc) - rdf(b + 0xc)) * t, rdf(a + 0x10) - (rdf(a + 0x10) - rdf(b + 0x10)) * t, F);
      clip_next(1); P100_ClipOut += 0xc;
    } else {
      float t = (zb - F) / (zb - za);
      clip_emit(rdf(b + 0xc) - (rdf(b + 0xc) - rdf(a + 0xc)) * t, rdf(b + 0x10) - (rdf(b + 0x10) - rdf(a + 0x10)) * t, F);
      P100_ClipOut += 0xc;
      clip_emit(rdf(b + 0xc), rdf(b + 0x10), zb);
      clip_next(2); P100_ClipOut += 0xc;
    }
  } else {
    clip_emit(rdf(b + 0xc), rdf(b + 0x10), zb);
    clip_next(1); P100_ClipOut += 0xc;
  }
}
static void clip_uv(float u) {
#ifndef RE_HOOK_BUILD
  if (P100_ClipOut == NULL) return;
#endif
  P100_ClipOut[6] = u;
}
void P100_ClipNear(const uint8_t *a, const uint8_t *b, float ua, float ub) {
  float N = P95_Near, za = rdf(a + 0x14), zb = rdf(b + 0x14);
  if (!(N <= za || N <= zb)) return;
  if (za < N || zb < N) {
    if (N <= za || zb < N) {
      float t = (za - N) / (za - zb);
      clip_emit(rdf(a + 0xc) - (rdf(a + 0xc) - rdf(b + 0xc)) * t, rdf(a + 0x10) - (rdf(a + 0x10) - rdf(b + 0x10)) * t, 50.0f);
      clip_uv(ua - (ua - ub) * t);
      clip_next(1); P100_ClipOut += 0xc;
    } else {
      float t = (zb - N) / (zb - za);
      clip_uv(ub - (ub - ua) * t);
      clip_emit(rdf(b + 0xc) - (rdf(b + 0xc) - rdf(a + 0xc)) * t, rdf(b + 0x10) - (rdf(b + 0x10) - rdf(a + 0x10)) * t, 50.0f);
      P100_ClipOut += 0xc;
      clip_uv(ub);
      clip_emit(rdf(b + 0xc), rdf(b + 0x10), zb);
      clip_next(2); P100_ClipOut += 0xc;
    }
  } else {
    clip_uv(ub);
    clip_emit(rdf(b + 0xc), rdf(b + 0x10), zb);
    clip_next(1); P100_ClipOut += 0xc;
  }
}

/* ---- 004e6f90: ближайшая точка пути призрака (40 записей 0x48 в 00d03920) ---- */
void P100_GhostNear(void) {
  int32_t best = 99999999, n;
  if (G6_00B5A778 != 0 || (G6_00B87EA0 == 0 && P11_00b87e38 != 0xc9) || (G6_00B87EA0 != 0 && P88_Mode575 != 1)) return;
  if (0 < P98_M4A4C) P98_M4A4C--;
  if (P56_G3908 == 0) { if (P56_G4538 == 0) return; n = P56_G4538 - 1; }
  else n = 0x28;
  while (n-- != 0) {
#ifndef RE_HOOK_BUILD
    if (n >= 40) continue;
#endif
    const uint8_t *r = &P56_GhostBuf[n * 0x48];
    int32_t d = 0;
    for (int32_t k = 0; k < 2; k++) {
      P11_00ba52d0 = fround(rdf(r + k * 0x10));
      d += iabs(P59_PosX - P11_00ba52d0);
      P11_00ba52d0 = fround(rdf(r + 8 + k * 0x10));
      d += iabs(P59_PosZ - P11_00ba52d0);
    }
    if (d < best) { P98_M4658 = (uint8_t)n; best = d; }
  }
  if (best < 800 && P98_M4658 != P98_M38F7) P98_M38F7 = P98_M4658;
  if (0xdac < best) {
    P12_Fn004E5982(0x124, 0x96, 0);
    if (P98_M4A4C == 0) { P98_M478C++; P98_M4A4C = 0x1e; }
  }
}

/* ---- 00499951: расстояние от грани k коробки a до коробки b (fixed 4.12), лучшее — в best ---- */
void P100_BoxFace(const int32_t *a, const int32_t *b, int32_t k, int32_t *best, int32_t sgn) {
  int32_t nx = a[k * 4], ny = a[k * 4 + 1], nz = a[k * 4 + 2];
  int32_t px = b[12], py = b[13], pz = b[14], side = 0;
  int32_t d = ((b[12] - a[12]) * nx + (b[13] - a[13]) * ny + 0x800 + (b[14] - a[14]) * nz) >> 12;
  if (d < 0) { nx = -nx; ny = -ny; nz = -nz; } else d = -d;
  d += a[16 + k];
  for (int32_t j = 0; j < 3; j++) {
    const int32_t *e = b + 19 + j * 4;
    int32_t t = (e[0] * nx + e[1] * ny + 0x800 + e[2] * nz) >> 12;
    if (t < 0) { d -= t; px += e[0]; py += e[1]; pz += e[2]; if (j == 2) side = 1; }
    else { d += t; px -= e[0]; py -= e[1]; pz -= e[2]; if (j == 2) side = 0; }
  }
  if (d < best[0]) {
    best[0] = d;
    if (-1 < d) {
      best[1] = px; best[2] = py; best[3] = pz;
      if (sgn < 0) { nx = -nx; ny = -ny; nz = -nz; }
      best[5] = nx; best[6] = ny; best[7] = nz;
      best[9] = side;
    }
  }
}

/* ---- 00499fb0: пересечение двух повёрнутых прямоугольников (записи по 0x18 слов) ---- */
int32_t P100_BoxOverlap(int32_t *p) {
  int32_t s1 = P59_Sin[((uint32_t)(p[0x28] - p[0x10]) + 0x400u) & 0x7ff];
  int32_t s2 = P59_Sin[(uint32_t)(p[0x28] - p[0x10]) & 0x7ffu];
  for (int32_t i = 1; i >= 0; i--) {
    int32_t *r = p + i * 0x18;
    r[4] = P59_Sin[(uint32_t)r[0x10] & 0xfffu];
    r[6] = P59_Sin[((uint32_t)r[0x10] + 0x400u) & 0xfff];
    r[8] = r[6];
    r[10] = -r[4];
  }
  int32_t dx = p[0] - p[0x18], dz = p[2] - p[0x1a];
  for (uint32_t c = 2; c != 0; c--) {
    uint32_t o = c & 1, u = c - 1;
    int32_t *r = p + u * 0x18, *q = p + o * 0x18;
    for (int32_t l = 2; l != 0; l--) {
      int32_t j = l - 1;
      r[l + 0x12] = (r[j * 4 + 4] * dx + 0x800 + r[j * 4 + 6] * dz) >> 12;
      r[l + 0x14] = r[l + 0x10] + ((q[l + 0x10] * s1 + 0x800 + q[0x12 - j] * s2) >> 12);
      if (r[l + 0x14] < r[l + 0x12] || r[l + 0x12] < -r[l + 0x14]) return 0;
    }
  }
  return 1;
}

/* ---- 004c3048: свободная камера режиссёра вокруг машины (клавиши: 1/2 — поворот, 4/8 — дальше/ближе, 0x20/0x40 — выше/ниже) ---- */
void P100_FreeCamKeys(uint32_t keys) {
  int32_t *cam = (int32_t *)&DirectorCam;
  if (cam[4] == -1) cam[4] = 0;
  int32_t step = (keys & 0x80) == 0 ? 0x28 : 0x50;
#ifndef RE_HOOK_BUILD
  if ((uint32_t)cam[4] >= P99_CARS_N) return;
#endif
  const p99_car_t *car = &P99_Cars[cam[4]];
  uint32_t ang = ((uint32_t)car->heading + (uint32_t)cam[6]) & 0xfff;
  if (keys & 1) ang += step >> 3;
  if (keys & 2) ang -= step >> 3;
  if (keys & 0x20) cam[0x1c] -= step;
  if (keys & 0x40) cam[0x1c] += step;
  if (keys & 4) cam[2] -= step;
  if (keys & 8) cam[2] += step;
  if (cam[2] < 0x14) cam[2] = 0x14;
  if (14999 < cam[2]) cam[2] = 15000;
  ang &= 0xfff;
  float v[3] = { 0.0f, (float)cam[0x1c], (float)cam[2] };
  float m[9] = { 1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f };
  P44_RotY(m, (int32_t)ang);
  P44_MatPtr = m;
  P44_Xform(v);
  P11_00ba52d0 = fround(v[0]); cam[0x13] = car->pos[0] + P11_00ba52d0;
  P11_00ba52d0 = fround(v[1]); cam[0x14] = P11_00ba52d0 - car->pos[1];
  P11_00ba52d0 = fround(v[2]); cam[0x15] = car->pos[2] + P11_00ba52d0;
  cam[3] = cam[2];
  cam[6] = (int32_t)((ang - (uint32_t)car->heading) & 0xfff);
  cam[7] = (int32_t)(ang & 0xfff);
}

/* ---- 004ba093: шаг частицы (float-запись: +0 позиция, +0x20 скорость, +0x30 ускорение, +0x50.. int, +0x64 жизнь) ---- */
static int32_t fi(const float *p, int32_t i) { return rd32(p + i); }
static void fiw(float *p, int32_t i, int32_t v) { wr32(p + i, v); }
static void part_tail(float *p) {
  if (fi(p, 0x16) < 1) { fiw(p, 0x16, 0); wr16((uint8_t *)p + 0x64, 1); }
  wr16((uint8_t *)p + 0x64, (uint16_t)(rd16(p + 0x19) - 1));
  if (rd16(p + 0x19) == 0) { fiw(p, 0x1a, 0); PoolPush004AC702(rd16(p + 0x1b)); }
}
void P100_PartStep(float *p) {
  float w[4];
  P94_Wobble(w, 1);
  uint32_t fl = (uint32_t)fi(p, 0x1a);
  if ((fl & 2) == 0) return;
  uint16_t life = rd16((uint8_t *)p + 0x64), lim = rd16((uint8_t *)p + 0x66);
  if ((fl & 0x180000) == 0) {
    if ((fl & 0x2000) == 0) p[1] -= K_08; else p[1] += K_2;
    p[0] += p[8]; p[1] += p[9]; p[2] += p[10];
    if (lim < life) { p[8] -= p[0xc]; p[9] -= p[0xd]; p[10] -= p[0xe]; }
    fiw(p, 0x14, fi(p, 0x14) + fi(p, 0x18));
    fiw(p, 0x16, fi(p, 0x16) - fi(p, 0x17));
  } else {
    p[1] = p[0xd] + p[9] + p[1];
    if (lim < life) { p[0] += p[8]; p[2] += p[10]; }
    else { p[0] = p[8] / K_2 + p[0]; p[2] = p[10] / K_2 + p[2]; }
    fiw(p, 0x14, fi(p, 0x14) + fi(p, 0x18));
    p[0xd] *= K_099;
    fiw(p, 0x16, (fi(p, 0x16) * 0x10 - fi(p, 0x17)) >> 4);
  }
  part_tail(p);
}

/* ---- 004c09e6: маркер k (0..3) у машины игрока — точка 010de230 + k*0x10 в мир, матрица маркера ---- */
static int32_t *mark_flag(int32_t k) {
  switch (k) { case 0: return &G010DE220; case 1: return &G010DE224; case 2: return &G010DE228; default: return &G010DE22C; }
}
void P100_MarkerSpawn(int32_t k) {
#ifndef RE_HOOK_BUILD
  if ((uint32_t)k > 3) return;
#endif
  int32_t *fl = mark_flag(k);
  if (!(0.0 <= (double)P97_D078CC && *fl != 0)) return;
  const p99_car_t *c = &P99_Cars[0];
  uint8_t *b = P98_CarBufC;   /* 010de220..010de318 */
  const float px = rdf(&P95_DebPos[k * 4]), pz = rdf(&P95_DebPos[k * 4 + 2]);
  *fl = 0;
  float v[3] = { px, rdf(&P95_DebPos[k * 4 + 1]), pz };
  P44_MatPtr = (float *)P98_MrkMat;
  P44_XformT(v);
  v[0] += (float)c->pos[0]; v[1] -= (float)c->pos[1]; v[2] += (float)c->pos[2];
  wrf(b + 0xd0, v[0]); wrf(b + 0xd4, v[1]); wrf(b + 0xd8, v[2]);
  memcpy(b + 0x50, P98_CarMat[0], 0x40);   /* v1.46: в native тоже вся матрица 0x40 (P98_CarMat) */
  int16_t ang[3] = { 0, 0, 10 };
  P43_EulerMatrix((float *)(b + 0x90), ang);
  if (k == 3 || k == 2) {
    static const int32_t idx[6] = { 0, 3, 6, 2, 5, 8 };
    for (int32_t i = 0; i < 6; i++) wrf(b + 0x50 + idx[i] * 4, -rdf(b + 0x50 + idx[i] * 4));
  }
  wrf(b + 0xe0, ((float)(c->f40[4] >> 12) * pz) / K_4096 + (float)(c->f40[0] >> 12));
  wrf(b + 0xe4, (float)(c->f40[1] >> 12) + 0.0f);
  wrf(b + 0xe8, ((float)-(c->f40[4] >> 12) * px) / K_4096 + (float)(c->f40[2] >> 12));
  /* +0xec (010de30c) в оригинале получает неинициализированную локальную — не пишем */
  wr32(b + 0xf4, 100);
}

/* ---- 004feb59: цвета рекламных щитов BILBRD1..7 (on=1 — включены) ---- */
void P100_Billboards(int32_t on) {
  static const char *const names[7] = { "BILBRD1", "BILBRD2", "BILBRD3", "BILBRD4", "BILBRD5", "BILBRD6", "BILBRD7" };
  float hi = on == 1 ? 255.0f : 192.0f, lo = on == 1 ? 40.0f : 176.0f;
  for (int32_t n = 0; n < 7; n++) {
    int32_t idx = P20_FindNameNoCase(names[n]);
    if (idx == -1) continue;
    uint32_t ref = P79_ModelTab[idx];
#ifndef RE_HOOK_BUILD
    if (ref == 0) continue;
#endif
    const uint8_t *m = (const uint8_t *)P79_PTR(ref);
    uint8_t *r = (uint8_t *)P79_PTR(*(const uint32_t *)(m + 0x2c));
    for (uint32_t cnt = rd16(m + 0x16); cnt != 0; cnt--) {
      if (r[0] == 7) {
        const int32_t hiA = n == 0 ? 0x5c : 0x44, loA = n == 0 ? 0x50 : 0x5c, loB = n == 0 ? 0x44 : 0x50;
        for (int32_t i = 0; i < 3; i++) { wrf(r + hiA + i * 4, hi); wrf(r + 0x38 + i * 4, hi); }
        for (int32_t i = 0; i < 3; i++) { wrf(r + loA + i * 4, lo); wrf(r + loB + i * 4, lo); }
      }
      r += G2_TABLE_00550ACC[r[0]];
    }
  }
}

/* ---- 004f2c9a: маска зеркала — 0x100 строк по 0x80: пятна 00cb8f20 в круге радиуса 01270c24 ---- */
void P100_MirrorMask(void) {
  const int32_t N = 0x1f;
  float r2 = Q01270C24 * Q01270C24;
  if (P100_Mirror != NULL) { P98_DebugFree(P100_Mirror); P100_Mirror = NULL; }
  P100_Mirror = (uint8_t *)P98_DebugMalloc(0x8000, "D:\\Driver\\Game\\mirror.c", 0x16d);
#ifndef RE_HOOK_BUILD
  if (P100_Mirror == NULL) return;
#endif
  P14_Fn0048DB65(P100_Mirror, 0x8000);
  for (int32_t row = 0; row < 0x100; row++) {
    uint8_t g[964];
    P14_Fn0048DB65(g, (uint32_t)(N * N));
    const uint8_t *fr = &P55_Frustum[row * 0x80];
    int32_t k = rd16s(fr) == -1 ? 0 : rd16s(fr);
    const uint8_t *sp = fr + 4 + k * 4;
    for (; k < N; k++, sp += 4) {
      if (rd16s(sp) == -1) continue;
      uint8_t *c = g + rd16s(sp) + k * N;
      for (int32_t i = 0; i < rd16s(sp + 2); i++) *c++ = 1;
    }
    for (int32_t y = -0xf; y < 0x10; y++) {
      int32_t i = (y + 0xf) * N;
      for (int32_t x = -0xf; x < 0x10; x++, i++)
        if (g[i] != 0 && r2 < (float)(x * x + y * y)) g[i] = 0;
    }
    P94_RowSpans((int16_t *)(P100_Mirror + row * 0x80), g);
  }
}

/* ---- 00494701: машина трафика car (запись 0x54) занимает полосу появления, если рядом нет других ---- */
void P100_TrafficSlot(uint8_t *car) {
  if ((car[0x13] & 9) != 0 || (Rand_004D9078() & 7) != 0) return;
  int32_t cls = rd32(car + 0x28);
#ifndef RE_HOOK_BUILD
  if (cls < 0 || cls >= (int32_t)(sizeof P11_00bf1c40 / 0x42)) return;
#endif
  if ((P11_00bf1c40[0x3c + cls * 0x42] & 1) == 0 || car[9] != 0 || rd32(car + 0x18) < 18000 || rd32(car + 0x1c) < 3000 ||
      P21_CountActiveEntries(cls) != 0) return;
  P75_TrafficPos(cls, rd32(car + 0x24), 0, 1, 0);
  P11_00ba52d0 = fround((float)P54_G40 * P63_Scale);
  int32_t gx = P11_00ba52d0;
  P11_00ba52d0 = fround((float)P54_G44 * P63_Scale);
  int32_t odd = (rd32(car + 0x24) & 1) != 0;
  const uint8_t *o = TrafficRecs;
  for (int32_t i = 0; i < P51_TrafficN; i++, o += 0x54) {
#ifndef RE_HOOK_BUILD
    if (i >= 0x40) break;
#endif
    if (o[1] == 0 || car[0] == o[0]) continue;
    if (!odd ? rd32(o + 0x48) == gx : rd32(o + 0x4c) == P11_00ba52d0) {
      int32_t off = odd ? 0x48 : 0x4c;
      if (iabs(rd32(car + off) - rd32(o + off)) < 8) return;
    }
  }
  switch (rd32(car + 0x24)) {
  case 0: wr32(car + 0x40, P54_G40 + 0x1ee); break;
  case 1: wr32(car + 0x44, P54_G44 - 0x1be); break;
  case 2: wr32(car + 0x40, P54_G40 - 0x1ee); break;
  case 3: wr32(car + 0x44, P54_G44 + 0x1be); break;
  }
  car[0x13] |= 0x11;
}

/* ---- 00407e2f: значок name в LFB dst с удвоением (по центру x, строка y), палитра 012710c0 ---- */
void P100_IconLfb2x(uint8_t *dst, int32_t x, uint32_t y, const char *name) {
  const uint8_t *ic = P93_FindIcon(name);
  if (ic == NULL) return;
  int32_t w = ic[0xb] == 0 ? 0x100 : ic[0xb];
  int32_t h = ic[0xc] == 0 ? 0x100 : ic[0xc];
  const uint8_t *src = texpage(ic[8]);
#ifndef RE_HOOK_BUILD
  if (src == NULL || dst == NULL) return;
#endif
  src += ic[9] + (uint32_t)ic[10] * 0x100;
  int32_t bpp16 = P100_LfbFmt[0] == 0x10;
  uint8_t *row = dst + (x - (w >> 1)) * (bpp16 ? 2 : 4) + y * (uint32_t)P100_LfbPitch;
  for (int32_t r = 0; r < h * 2; r++) {
    const uint8_t *s = src;
    uint8_t *d = row;
    for (int32_t i = 0; i < w; i++) {
      uint32_t c = P100_Pal32[*s++];
      if (bpp16) { uint32_t v = c << 16 | c; memcpy(d, &v, 4); d += 4; }
      else { memcpy(d, &c, 4); memcpy(d + 4, &c, 4); d += 8; }
    }
    if (r & 1) src += 0x100;
    row += P100_LfbPitch;
  }
}
