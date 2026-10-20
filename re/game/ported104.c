/* ported104 — graphics-options menu init, mission start reset, player traffic-turn setup, debris tables and the car
   damage -> dent texture / damaged-model update (Game.exe, cdecl).  The Russian notes above each function are the
   original port notes; English headers summarise them.  Original file note: */
/* v1.49 (см. ported104.h). Стандарт указателей v1.42: адреса строк в таблице 0054a170 и P97_StrAddr — uint32 (re_ptr);
   ссылки текстур вмятин P27_DentTex — адреса Game.exe (re_ptr); ссылки моделей машин — P79_PTR. */
#include "ported104.h"
#include "ported11.h"
#include "ported12.h"
#include "ported14.h"
#include "ported15.h"
#include "ported16.h"
#include "ported17.h"
#include "ported18.h"
#include "ported19.h"
#include "ported20.h"
#include "ported21.h"
#include "ported22.h"
#include "ported23.h"
#include "ported24.h"
#include "ported25.h"
#include "ported26.h"
#include "ported27.h"
#include "ported28.h"
#include "ported29.h"
#include "ported30.h"
#include "ported31.h"
#include "ported33.h"
#include "ported32.h"
#include "ported34.h"
#include "ported35.h"
#include "ported36.h"
#include "ported37.h"
#include "ported38.h"
#include "ported39.h"
#include "ported40.h"
#include "ported41.h"
#include "ported42.h"
#include "ported43.h"
#include "ported44.h"
#include "ported45.h"
#include "ported46.h"
#include "ported47.h"
#include "ported48.h"
#include "ported49.h"
#include "ported50.h"
#include "ported51.h"
#include "ported52.h"
#include "ported53.h"
#include "ported54.h"
#include "ported55.h"
#include "ported56.h"
#include "ported57.h"
#include "ported58.h"
#include "ported59.h"
#include "ported60.h"
#include "ported61.h"
#include "ported62.h"
#include "ported63.h"
#include "ported64.h"
#include "ported65.h"
#include "ported66.h"
#include "ported67.h"
#include "ported68.h"
#include "ported69.h"
#include "ported70.h"
#include "ported71.h"
#include "ported72.h"
#include "ported73.h"
#include "ported74.h"
#include "ported75.h"
#include "ported76.h"
#include "ported77.h"
#include "ported78.h"
#include "ported79.h"
#include "ported80.h"
#include "ported81.h"
#include "ported82.h"
#include "ported83.h"
#include "ported84.h"
#include "ported85.h"
#include "ported86.h"
#include "ported87.h"
#include "ported88.h"
#include "ported89.h"
#include "ported90.h"
#include "ported91.h"
#include "ported92.h"
#include "ported93.h"
#include "ported94.h"
#include "ported95.h"
#include "ported96.h"
#include "ported97.h"
#include "ported98.h"
#include "ported99.h"
#include "ported100.h"
#include "ported101.h"
#include "ported102.h"
#include "ported13.h"
#include "director.h"
#include "directorstorage.h"
#include "dirnodes.h"
#include "menustate.h"
#include "noop.h"
#include "uihandlers.h"
#include "uihandlers2.h"
#include "uihandlers3.h"
#include "uihandlers4.h"
#include "globalsets.h"
#include "smallfuncs.h"
#include "smallfuncs2.h"
#include "menuselect.h"
#include "widgets.h"
#include "ported4.h"
#include "ported5.h"
#include "ported6.h"
#include "ported7.h"
#include "ported8.h"
#include "ported9.h"
#include "ported10.h"
#include "unported.h"
#include "nodetab.h"
#include "cartab.h"
#include "menutab.h"
#include "p100_data.h"
#include "p103_data.h"
#include <math.h>
#include <string.h>
#include "ported103.h"
#include "p104_data.h"
#include <math.h>
#include <string.h>

#ifndef RE_HOOK_BUILD
p104_menugfx_t P104_MenuGfx = { P104_MENUGFX_INIT };
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P104_DebA")
#undef P104_DebA
#pragma push_macro("P104_DebA") /*gvi*/
#undef P104_DebA /*gvi*/
p104_deb_t P104_DebA;
#pragma pop_macro("P104_DebA") /*gvi*/
#pragma pop_macro("P104_DebA")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P104_DebB")
#undef P104_DebB
#pragma push_macro("P104_DebB") /*gvi*/
#undef P104_DebB /*gvi*/
p104_deb_t P104_DebB;
#pragma pop_macro("P104_DebB") /*gvi*/
#pragma pop_macro("P104_DebB")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P104_DebC")
#undef P104_DebC
#pragma push_macro("P104_DebC") /*gvi*/
#undef P104_DebC /*gvi*/
p104_deb_t P104_DebC;
#pragma pop_macro("P104_DebC") /*gvi*/
#pragma pop_macro("P104_DebC")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P104_Buf760")
#undef P104_Buf760
#pragma push_macro("P104_Buf760") /*gvi*/
#undef P104_Buf760 /*gvi*/
p104_buf760_t P104_Buf760;
#pragma pop_macro("P104_Buf760") /*gvi*/
#pragma pop_macro("P104_Buf760")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P104_12B26C")
#undef P104_12B26C
#pragma push_macro("P104_12B26C") /*gvi*/
#undef P104_12B26C /*gvi*/
int32_t P104_12B26C;
#pragma pop_macro("P104_12B26C") /*gvi*/
#pragma pop_macro("P104_12B26C")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P104_139A28")
#undef P104_139A28
#pragma push_macro("P104_139A28") /*gvi*/
#undef P104_139A28 /*gvi*/
int32_t P104_139A28;
#pragma pop_macro("P104_139A28") /*gvi*/
#pragma pop_macro("P104_139A28")
#endif

#include "memrw.h"
#include "carfields.h"
/* Accessors for Game.exe .data addresses through re_ptr (unmapped address: reads 0, writes are dropped). */
static int32_t gd32(uint32_t a) { const void *p = re_ptr(a); return p ? rd32(p) : 0; }
static void gw32(uint32_t a, uint32_t v) { void *p = re_ptr(a); if (p) wr32(p, (int32_t)v); }
static void gw16(uint32_t a, uint16_t v) { void *p = re_ptr(a); if (p) wr16(p, v); }
static float gdf(uint32_t a) { const void *p = re_ptr(a); return p ? rdf(p) : 0.0f; }
static void gwf(uint32_t a, float v) { void *p = re_ptr(a); if (p) wrf(p, v); }
/* Address of string i of the localised string table P97_StrAddr (native: 0 outside 0..0x15d). */
static uint32_t str_at(int32_t i) {
#ifndef RE_HOOK_BUILD
  if (i < 0 || i >= 0x15e) return 0;
#endif
  return P97_StrAddr[i];
}
/* индекс строки из таблицы int32 base[i] (.data 0054a640..); в native вне зарегистрированной таблицы — 0 */
static uint32_t str_tab(uint32_t base, int32_t i) { return str_at(gd32(base + (uint32_t)i * 4)); }
/* x87 fistp: round to nearest even in the current (default) rounding mode. */
static int32_t fistp(long double v) { return (int32_t)llrintl(v); }

/* ---- 00409622: экран графики — подписи пунктов (адреса строк P97_StrAddr в поля +8 записей 0x20 таблицы 0054a250..),
   значения переключателей (индексы строк 0054a640.. по текущим настройкам) и положения пяти ползунков (float 0054a680..690,
   координата x = round(доля·116) + 0x1d5 в +0x14 записей 0054a170..) ---- */
/* Slider: stores fraction frac (0..1) at fa and the knob x = round(frac * 116) + 0x1d5 at xa (int16). */
static void slider(uint32_t fa, uint32_t xa, float frac) {
  gwf(fa, frac);
  P11_00ba52d0 = fistp((long double)gdf(fa) * 116.0L);              /* 00546044 = 116.0 */
  gw16(xa, (uint16_t)((int16_t)P11_00ba52d0 + 0x1d5));
}
/* P104_GfxMenuInit — Game.exe 00409622.  Fills the graphics-options menu: 19 item labels, the current value string
   of each switch (string-index tables at .data 0054a640..), and five sliders (two distances mapped from
   15000..42000 / 15000..45000, one 0..64, one 16..64, one 0..3).  c / t / s are three-way settings derived from
   pairs of flags (TODO(RE): unsure which options they are). */
void P104_GfxMenuInit(void) {
  int32_t c = P13_00575ef4 == 0 ? 0 : (P13_00b87e74 == 0 ? 1 : 2);
  int32_t t = P13_00575ec0 == 0 ? 0 : (P13_00575ebc == 0 ? 1 : 2);
  int32_t s = P13_00d11880 == 0 ? 0 : (P13_00575f20 == 0 ? 1 : 2);
  static const uint16_t lab[19][2] = {   /* поле → номер строки ((адрес − 00c55820) / 4) */
    {0x258, 0xe4}, {0x278, 0x2b}, {0x298, 0x2c}, {0x2b8, 0x2d}, {0x2d8, 0x31}, {0x2f8, 0xe5}, {0x318, 0x2e}, {0x338, 0x30},
    {0x358, 0x39}, {0x378, 0x2f}, {0x398, 0x34}, {0x3b8, 0x33}, {0x3d8, 0x37}, {0x3f8, 0x32}, {0x418, 0x38}, {0x428, 0x36},
    {0x438, 0x35}, {0x448, 0xf7}, {0x458, 0xe7} };
  for (int k = 0; k < 19; k++) gw32(0x0054a000u + lab[k][0], str_at(lab[k][1]));
  gw32(0x0054a268, str_tab(0x0054a66c, P11_00575ef8));
  gw32(0x0054a288, str_tab(0x0054a660, s));
  gw32(0x0054a2a8, str_tab(0x0054a640, P13_0055384c));
  gw32(0x0054a2c8, str_tab(0x0054a640, P13_00553850));
  gw32(0x0054a2e8, str_tab(0x0054a640, P13_00575f30));
  gw32(0x0054a308, str_tab(0x0054a640, P13_00b201dc));
  gw32(0x0054a328, str_tab(0x0054a640, P13_00b31f04));
  gw32(0x0054a348, str_tab(0x0054a640, P13_0055c974));
  gw32(0x0054a368, str_tab(0x0054a640, P13_00575f44));
  gw32(0x0054a388, str_tab(0x0054a648, t));
  gw32(0x0054a3a8, str_tab(0x0054a654, c));
  gw32(0x0054a3c8, str_tab(0x0054a640, P13_00d118c8));
  gw32(0x0054a3e8, str_tab(0x0054a640, P13_00575f3c));
  gw32(0x0054a408, str_tab(0x0054a640, P13_00575ee8));
  slider(0x0054a68c, 0x0054a184, (P11_0125f3f8 - 15000.0f) / 27000.0f);   /* 0054602c, 00546048 */
  slider(0x0054a688, 0x0054a1ac, (P11_01270c24 - 15000.0f) / 30000.0f);   /* 00546040 */
  slider(0x0054a680, 0x0054a1d4, (float)P13_005759a4 / 64.0f);            /* 0054603c */
  slider(0x0054a684, 0x0054a1fc, (float)(P13_00575ee4 - 0x10) / 48.0f);   /* 00546038 */
  slider(0x0054a690, 0x0054a224, (float)MenuVarB87E4C / 3.0f);            /* 00546034 */
}

/* ---- 004e4bdc: сброс состояния миссии перед стартом: 004e49c0, обнуление счётчиков/таймеров, значок STOPWATCH,
   машины миссии 4 (004e4d35), бумага/призрак, банк звуков BANK0.DSS в слот 0xf000 ---- */
/* P104_MissionInit — Game.exe 004e4bdc.  Resets the per-mission state before a mission starts: mission counters and
   timers, fade state, the STOPWATCH icon, mission-4 cars, newspaper and ghost, and loads sound bank BANK0.DSS into
   slot 0xf000.  Several values are written through two aliases of one Game.exe address (native split names). */
void P104_MissionInit(void) {
  P98_ResetMission();
  P98_M38F8 = 0; P98_M4460 = 0; P98_M4480 = 0; P59_S44CC = 0; P59_S4790 = 0; P59_S3904 = 0; P98_M4468 = 0;
  G2_00D044C8 = 0; G00D044C8 = 0;
  P98_M4474 = 0; P98_M44D8 = 0; P98_M4A48 = 0; P98_M4A5C = 0;
  P98_M390C = 0x28; P98_M4464 = 0x46; P94_FadeVal = 0; P94_FadeDir = 0;
  P97_FadeIcon = P93_FindIcon("STOPWATCH");                         /* 00562c28 */
  P98_M4A60 = 0; P98_M478C = 0; P94_FadePos = 0.0f;
  P59_S4654 = 0; G2_00D04654 = 0;
  P56_D4470 = 0xf0; P98_M453C = 0; P98_M4A4C = 0x1e;
  { uint32_t b = 0x3faeb852u; float f; memcpy(&f, &b, 4); P94_FadeSpeed = f; }   /* 1.365 */
  P61_V18 = 0x800;
  P103_Mission4Cars();
  P14_00d118a8 = 1; G2_00D118A8 = 1;
  P59_Mode1137324 = 0; *(uint8_t *)&G2_01137324 = 0;                  /* байт */
  *(uint8_t *)&G2_00C54EC0 = 1;                                       /* байт */
  P98_M4660 = 0;
  P55_LoadPaper();
  P56_GhostInit();
  P77_LoadBank("BANK0.DSS", 0xf000);                                 /* 00562c34 */
}

/* ---- 0049565b: начало поворота трафика у игрока: клетка карты под игроком (0051b111), узел дороги (не перекрёсток,
   длина ≥ 0x14, сторона по биту 0 dir), длины четырёх сторон узла (P59_C39DC0) и соседнего узла (0051b208) ---- */
/* Record i (stride st) of a table of sz bytes; native: an all-zero record when out of range. */
static const uint8_t *rec(const uint8_t *tab, uint32_t sz, int32_t i, uint32_t st) {
#ifndef RE_HOOK_BUILD
  static const uint8_t zero[0x100];
  if (i < 0 || (uint32_t)(i + 1) * st > sz) return zero;
#else
  (void)sz;
#endif
  return tab + (uint32_t)i * st;
}
/* P104_TrafficTurn — Game.exe 0049565b.  Starts a traffic "turn" event at the player's map cell in direction dir
   (0..3, bit 0 = which side of the road): rejected (0) when one is already active (G01145934 / G011426F8), the cell
   is a junction (road word bits 0xc000), the road is shorter than 0x14 or the side does not match.  Otherwise sums
   the lengths of the node's two sides along dir plus those of the neighbouring node, stores node / direction /
   lengths in the traffic globals and returns 1.  TODO(RE): unsure what the event is used for. */
int32_t P104_TrafficTurn(uint32_t dir) {
  int32_t px = P59_PosX, pz = P59_PosZ;
  if (G01145934 != 0) return 0;
  if (G011426F8 != -1) return 0;
  uint16_t w = (uint16_t)P72_RoadWord(px, pz);   /* road word of the cell: node index, bits 0xc000 = junction */
  if ((w & 0xc000) != 0) return 0;
  int16_t len; memcpy(&len, rec(P11_00bf1c40, sizeof P11_00bf1c40, w, 0x42) + 8, 2);   /* 00bf1c48 */
  if (len < 0x14) return 0;
  uint8_t side = rec(P11_00c12c60, sizeof P11_00c12c60, w, 0x14)[0x10];               /* 00c12c70 */
  if ((dir & 1) == 0) { if (side == 1) return 0; }
  else if (side == 0) return 0;
  uint32_t d = dir & 0xff;
  const uint8_t *n = rec(P59_C39DC0, sizeof P59_C39DC0, w, 0x24);
  P103_1373D4 = (int32_t)n[d] + (int32_t)n[(d + 2) & 3];
  G0113A6C0 = P103_1373D4;
  P103_1443C0 = P103_RoadNeighbour(px, pz, d);
  P103_1426F0 = 0xff;
  if (P103_1443C0 != -1) {
    const uint8_t *m = rec(P59_C39DC0, sizeof P59_C39DC0, P103_1443C0, 0x24);
    G0113A6C0 = (int32_t)m[(d + 2) & 3] + G0113A6C0 + (int32_t)m[d];
  }
  P104_139A28 = G0113A6C0 + 1;
  G0113A6C0 = G0113A6C0 + P104_139A28;
  if (G0113A6C0 == 0) return 0;
  G01144284 = 0;
  G011426F8 = (int32_t)w;
  *(uint8_t *)&P103_1426E0 = (uint8_t)dir;                          /* байт 011426e0 */
  G01145934 = P104_12B26C;
  P103_139A38 = G0113A6C0;
  return 1;
}

/* ---- 004ab127: таблицы обломков: очистка 0110b260 (200 × 0x3c) и 010faf40 (400 байт), буфер 00cfe760,
   номера записей; 256 поворотов (углы 01123200 += 0x10/0x60) трёх наборов вершин 010ffd20/01102d20/0111a400 ---- */
/* Copies a 3-vertex debris shape (float[3] each) into three float[4] slots and rotates them by P44_MatPtr. */
static void deb_set(float *v, const float *src) {
  for (int k = 0; k < 3; k++) { v[k * 4] = src[k * 3]; v[k * 4 + 1] = src[k * 3 + 1]; v[k * 4 + 2] = src[k * 3 + 2]; }
  P44_Xform(v); P44_Xform(v + 4); P44_Xform(v + 8);
}
/* P104_DebrisTabs — Game.exe 004ab127.  Clears the 200 debris records (0x3c bytes) and the free list, numbers the
   records, and precomputes 256 rotated copies of three triangle shapes (two small, one large) by stepping Euler
   angles (+0x10, +0x60, 0 per copy). */
void P104_DebrisTabs(void) {
  P14_Fn0048DB65(P12_0110b260, 12000);
  P14_Fn0048DB65(S_010FAF40, 400);
  for (int i = 0; i < 0x10; i++) P104_Buf760[i] = 0;
  for (int i = 0; i < 200; i++) {
    wr16(&P12_0110b260[i * 0x3c + 0x26], 0);
    wr16(&P12_0110b260[i * 0x3c + 0x24], (uint16_t)i);
    wr16(&S_010FAF40[i * 2], (uint16_t)i);
  }
  P100_DebAng[0] = 0; P100_DebAng[1] = 0; P100_DebAng[2] = 0;
  static const float va[9] = { -10.0f, 10.0f, 0.0f,  0.0f, -10.0f, 0.0f,  10.0f, 10.0f, 0.0f };
  static const float vb[9] = { -7.0f, 7.0f, 0.0f,  0.0f, -7.0f, 0.0f,  7.0f, 7.0f, 0.0f };
  static const float vc[9] = { -35.0f, 0.0f, 40.0f,  40.0f, 0.0f, 35.0f,  -30.0f, 0.0f, -35.0f };
  for (int i = 0; i < 0x100; i++) {
    P43_EulerMatrix(P100_DebMat, P100_DebAng);
    P44_MatPtr = P100_DebMat;
    deb_set(&P104_DebA[i * 12], va);
    deb_set(&P104_DebB[i * 12], vb);
    deb_set(&P104_DebC[i * 12], vc);
    P100_DebAng[0] = (int16_t)((P100_DebAng[0] + 0x10) & 0xfff);
    P100_DebAng[1] = (int16_t)((P100_DebAng[1] + 0x60) & 0xfff);
    P100_DebAng[2] = (int16_t)(P100_DebAng[2] & 0xfff);
  }
  S_011173C8 = 0;
}

/* ---- 004c1c23: повреждения машины → вид. car 0 (игрок): уровень вмятин каждой из 6 сторон (+0x11c.. × 6 >> 12, ≤5);
   при смене — блит кусков текстуры вмятин (P27_DentTex[кусок*6+уровень] → страница D_00d17ec8) и загрузка страницы (0048a46b).
   car ≠ 0: флаги сторон по порогам 0x52c/1000 → записи операций модели (P98_CarOpsC) копируются из «битой» модели ---- */
#ifndef RE_HOOK_BUILD
static const uint8_t k_dent[] = P104_DENT_INIT;   /* 00554fc4: по модели 0x48 = 6 сторон × 3 номера куска (-1 — конец) */
static const uint8_t k_face[] = P104_FACE_INIT;   /* 0055b834: по типу машины 0x170 байт — сторона записи операции */
#define TEXP(i) ((uint8_t *)P65_TexPage((int32_t)(i)))   /* v2.06: страница слота (01145a64 = P40_Slots[i].data) */
#else
#define TEXP(i) ((uint8_t *)P65_Texs[(i)].p)
#endif
/* P104_CarDents — Game.exe 004c1c23.  Updates the visible damage of car (skipped while P95_B87ED0).
   Player (car 0): dent level per body zone = damage * 6 >> 12, max 5; for each changed zone the dent texture
   pieces of that level (table 00554fc4 per player car) are blitted into the car's texture page D_00d17ec8, which
   is then re-uploaded.
   Other cars: zone flags from damage thresholds (front pair / rear pair >= 0x52c, single zones > 1000); every draw
   record of the clean model whose face (table 0055b834 per car kind) is flagged is replaced by the damaged model's
   record.  Stops when the two models' records stop matching in kind / size. */
void P104_CarDents(int32_t car) {
  if (P95_B87ED0 != 0) return;
  if (car == 0) {
    int changed = 0;
    for (int32_t side = 5; side >= 0; side--) {
      int32_t lv = (int32_t)((uint32_t)rd32((const uint8_t *)&P99_Cars[0] + CAR_DAMAGE + side * 4) * 6u) >> 12;   /* imul, sar */
      if (lv > 5) lv = 5;
      if (P99_D17ECC[side] == (uint8_t)lv) continue;
      for (int32_t k = 0; k < 3; k++) {
        uint32_t off = (uint32_t)(k * 4 + side * 0xc + S_00D1192C * 0x48);
#ifndef RE_HOOK_BUILD
        if (S_00D1192C < 0 || off + 4 > sizeof k_dent) break;
        int32_t piece = rd32(k_dent + off);
#else
        int32_t piece = gd32(0x00554fc4u + off);
#endif
        if (piece == -1) break;
#ifndef RE_HOOK_BUILD
        if (piece < 0 || piece * 6 + lv < 0 || piece * 6 + lv >= 66 || piece * 6 >= 66) continue;
#endif
        const uint8_t *src = (const uint8_t *)re_ptr((uint32_t)P27_DentTex[piece * 6 + lv]);
        const uint8_t *dst = (const uint8_t *)re_ptr((uint32_t)P27_DentTex[piece * 6]);
        if (src != NULL && dst != NULL)
          P15_BlitRect16(TEXP(src[8]), src[9], src[10], src[0xb], src[0xc], (uint8_t *)D_00d17ec8, dst[9], dst[10]);
      }
      P99_D17ECC[side] = (uint8_t)lv;
      changed = 1;
    }
    if (changed) {
      const uint8_t *d0 = (const uint8_t *)re_ptr((uint32_t)P27_DentTex[0]);
      if (d0 != NULL) P12_Fn0048A46B(d0[8], (int32_t)re_addr(D_00d17ec8));
    }
    return;
  }
#ifndef RE_HOOK_BUILD
  if (car < 1 || car >= 66 || car > 0x40) return;
#endif
  uint32_t kind = TrafficRecs[(car - 1) * 0x54 + 0xc];
  const uint8_t *cr = (const uint8_t *)&P99_Cars[car];
  uint32_t fl[7];
  /* fl[0] = record count, fl[1..6] = "zone damaged" per face id (TODO(RE): unsure which zone is front/rear) */
  fl[1] = fl[2] = (rd32(cr + CAR_DAMAGE + 0) < 0x52c && rd32(cr + CAR_DAMAGE + 4) < 0x52c) ? 0u : 1u;
  fl[3] = 1000 < rd32(cr + CAR_DAMAGE + 8);
  fl[4] = fl[5] = (rd32(cr + CAR_DAMAGE + 12) < 0x52c && rd32(cr + CAR_DAMAGE + 16) < 0x52c) ? 0u : 1u;
  fl[6] = 1000 < rd32(cr + CAR_DAMAGE + 20);
  if (P28_CarDam[kind] == 0 || P28_CarClean[kind] == 0) return;     /* native: модели не загружены */
  const uint8_t *md = (const uint8_t *)P79_PTR(P28_CarDam[kind]);
  const uint8_t *mc = (const uint8_t *)P79_PTR(P28_CarClean[kind]);
  const uint8_t *src = (const uint8_t *)P79_PTR(rd32(md + 0x2c));
  uint8_t *dst = &P98_CarOpsC[car * 0x9580];
#ifndef RE_HOOK_BUILD
  if (kind >= 12 || src == NULL) return;
  const uint8_t *face = k_face + kind * 0x170;
#else
  const uint8_t *face = (const uint8_t *)(uintptr_t)(0x0055b834u + kind * 0x170);
#endif
  uint16_t cnt; memcpy(&cnt, mc + 0x16, 2);
  fl[0] = cnt;
  uint16_t cnt2; memcpy(&cnt2, md + 0x16, 2);
  if (cnt2 != fl[0]) return;
  for (int32_t i = 0; i < (int32_t)fl[0]; i++) {
    int32_t sz = G2_TABLE_00550ACC[*src];
    uint32_t f = *face++;
    if (f != 0 && fl[f] != 0) P44_Copy4(dst, src, (uint32_t)G2_TABLE_00550ACC[*src]);
    if (*src != *dst) return;
    if (sz != G2_TABLE_00550ACC[*dst]) return;
    src += sz;
    dst += G2_TABLE_00550ACC[*dst];
  }
}
