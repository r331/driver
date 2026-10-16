/* v1.48 (см. ported103.h). Стандарт указателей v1.42: адреса имён в записях объектов миссий 00572f00 и строк меню 0054db58 —
   uint32_t + re_ptr/re_addr; глобальные скалярные указатели (значки ползунков 005fe9d4/d8) — родные. */
#include "ported103.h"
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

#ifndef RE_HOOK_BUILD
p103_menutab_t P103_MenuTab = { P100_DB58_INIT };
uint8_t P103_MObj[P103_MOBJ_SIZE] = P103_MOBJ_INIT;
#endif
GAME_VAR_DEF(int32_t, P103_MObjN, 0x00c80948)
GAME_VAR_DEF(uint8_t *, P103_Slider, 0x005fe9d8)
GAME_VAR_DEF(uint8_t *, P103_SliderBar, 0x005fe9d4)

GAME_VAR_DEF(int32_t, P103_1373D4, 0x011373d4)
GAME_VAR_DEF(int32_t, P103_139A38, 0x01139a38)
GAME_VAR_DEF(int32_t, P103_13A5A0, 0x0113a5a0)
GAME_VAR_DEF(int32_t, P103_1426E0, 0x011426e0)
GAME_VAR_DEF(int32_t, P103_1426EC, 0x011426ec)
GAME_VAR_DEF(int32_t, P103_1426F0, 0x011426f0)
GAME_VAR_DEF(int32_t, P103_1426F4, 0x011426f4)
GAME_VAR_DEF(int32_t, P103_143724, 0x01143724)
GAME_VAR_DEF(int32_t, P103_144320, 0x01144320)
GAME_VAR_DEF(int32_t, P103_1443C0, 0x011443c0)
GAME_VAR_DEF(int32_t, P103_145A44, 0x01145a44)
GAME_VAR_DEF(int32_t, P103_DmgPct, 0x011373c8)
GAME_VAR_DEF(p103_i4_t, P103_PathLen, 0x00c81990)
GAME_VAR_DEF(float, P103_PathK, 0x00c56714)
GAME_VAR_DEF(int32_t, P103_D118E0, 0x00d118e0)
GAME_VAR_DEF(uint8_t *, P103_HQuad, 0x00b2f300)
GAME_VAR_DEF(uint8_t *, P103_HBlk, 0x00b2f308)
GAME_VAR_DEF(int32_t, P103_HCellZ, 0x00bdfaf0)
GAME_VAR_DEF(int32_t, P103_HCellX, 0x00bdfaf4)
GAME_VAR_DEF(p103_box_t, P103_CarBoxes, 0x00b2ecd0)
GAME_VAR_DEF(int32_t, P103_B5A848, 0x00b5a848)
GAME_VAR_DEF(int32_t, P103_B5A84C, 0x00b5a84c)
GAME_VAR_DEF(uint8_t, P103_B5A895, 0x00b5a895)
GAME_VAR_DEF(uint8_t, P103_B5A8A9, 0x00b5a8a9)
GAME_VAR_DEF(uint8_t, P103_B5A8AA, 0x00b5a8aa)
GAME_VAR_DEF(int32_t, P103_B5A8B4, 0x00b5a8b4)
GAME_VAR_DEF(int32_t, P103_B5A8B8, 0x00b5a8b8)
GAME_VAR_DEF(int32_t, P103_B5A8C4, 0x00b5a8c4)
GAME_VAR_DEF(int32_t, P103_B5A8C8, 0x00b5a8c8)
GAME_VAR_DEF(uint8_t, P103_C4D664, 0x00c4d664)
GAME_VAR_DEF(int32_t, P103_C4D874, 0x00c4d874)
GAME_VAR_DEF(int32_t, P103_C4D920, 0x00c4d920)
GAME_VAR_DEF(int32_t, P103_C4D924, 0x00c4d924)
GAME_VAR_DEF(int32_t, P103_C4D9A0, 0x00c4d9a0)
GAME_VAR_DEF(uint8_t, P103_C4D9A4, 0x00c4d9a4)
GAME_VAR_DEF(int32_t, P103_C54AA0, 0x00c54aa0)
GAME_VAR_DEF(int32_t, P103_C54D00, 0x00c54d00)
GAME_VAR_DEF(int32_t, P103_C54D04, 0x00c54d04)
GAME_VAR_DEF(int32_t, P103_C54EC4, 0x00c54ec4)
GAME_VAR_DEF(int32_t, P103_C54FC0, 0x00c54fc0)
GAME_VAR_DEF(int32_t, P103_C54FC4, 0x00c54fc4)
GAME_VAR_DEF(p103_b88_t, P103_C54EE0, 0x00c54ee0)

static int32_t mul(int32_t a, int32_t b) { return (int32_t)((uint32_t)a * (uint32_t)b); }   /* imul с переполнением */
static int32_t iabs(int32_t v) { return v < 0 ? -v : v; }
static int32_t rd32(const void *p) { int32_t v; memcpy(&v, p, 4); return v; }
static void wr32(void *p, int32_t v) { memcpy(p, &v, 4); }
static int16_t rd16s(const void *p) { int16_t v; memcpy(&v, p, 2); return v; }
static uint16_t rd16(const void *p) { uint16_t v; memcpy(&v, p, 2); return v; }
static void wr16(void *p, uint16_t v) { memcpy(p, &v, 2); }
static float rdf(const void *p) { float v; memcpy(&v, p, 4); return v; }
static void wrf(void *p, float v) { memcpy(p, &v, 4); }
/* uint32 ячейки .data по адресу Game.exe (в native — зарегистрированные таблицы; вне них — 0 / пропуск) */
static int32_t gd32(uint32_t a) { const void *p = re_ptr(a); return p ? rd32(p) : 0; }
static void gw32(uint32_t a, uint32_t v) { void *p = re_ptr(a); if (p) re_wr_addr(p, v); }
static void gw16(uint32_t a, uint16_t v) { void *p = re_ptr(a); if (p) wr16(p, v); }
/* адрес строки языка (P97_StrAddr) по номеру; в native номер вне таблицы — 0 */
static uint32_t str_at(int32_t i) {
#ifndef RE_HOOK_BUILD
  if (i < 0 || i >= 0x15e) return 0;
#endif
  return P97_StrAddr[i];
}

/* ---- 004fede5: модели миссии — по таблице миссии (группы 005734ac, число записей 005734c0, запись 0x24:
   +4 номер модели, +8 адрес имени) находит модель по имени и ставит флаг 4 (+2) ей и всем её копиям (+4 = номер) ---- */
static void mobj_flag(int32_t idx) {
#ifndef RE_HOOK_BUILD
  if (idx < 0 || idx >= 1126 || P79_ModelTab[idx] == 0) return;
#endif
  uint8_t *m = (uint8_t *)P79_PTR(P79_ModelTab[idx]);
  wr16(m + 2, (uint16_t)(rd16(m + 2) | 4));
}
void P103_MissionModels(void) {
  ResolveTable_004FE830();
  P102_LampColor(P14_00b87e84);
  P100_Billboards(P14_00b87e84);
  if (D_00b87e30 > 4) return;                       /* 00546a04 (.rdata) = 4 */
#ifndef RE_HOOK_BUILD
  if (D_00b87e30 < 0) return;
#endif
  P103_MObjN = gd32(0x005734c0u + (uint32_t)D_00b87e30 * 4);
  if (P103_MObjN == 0) return;
  uint32_t rec = (uint32_t)gd32(0x005734acu + (uint32_t)D_00b87e30 * 4);
  for (int32_t k = 0; k < P103_MObjN; k++, rec += 0x24) {
    uint8_t *r = (uint8_t *)re_ptr(rec);
#ifndef RE_HOOK_BUILD
    if (r == NULL) break;
#endif
    int32_t idx;
    if (rd32(r + 8) == 0) idx = rd32(r + 4);
    else {
      const char *nm = (const char *)re_ptr((uint32_t)rd32(r + 8));
#ifndef RE_HOOK_BUILD
      if (nm == NULL) continue;
#endif
      idx = P20_FindNameNoCase(nm);
    }
    if (idx == -1) continue;
    wr32(r + 4, idx);
    mobj_flag(idx);
    for (int32_t j = 0; j < P20_Count; j++) {
#ifndef RE_HOOK_BUILD
      if (j >= 1126) break;
      if (P79_ModelTab[j] == 0) continue;
#endif
      if (rd32((const uint8_t *)P79_PTR(P79_ModelTab[j]) + 4) == idx) mobj_flag(j);
    }
  }
}

/* ---- 004cb102 / 004cb2f5: рассвет / закат — шаг перехода освещения раз в 8 / 4 кадра ---- */
static void light_flag(int32_t on) {           /* 00b201dc — во все псевдонимы */
  MenuVarB201DC = on; P13_00b201dc = on; G00B201DC = on;
}
static void lamps(int32_t on) {
  P14_00b87e84 = on;
  P102_LampColor(on);
  P100_Billboards(P14_00b87e84);
}
static void light_lerp(void) {                  /* шаг к цели SetScaled_004CB097 (0.002 за раз) и раскладка света */
  float t = rdf(&P8_00d17b14);
  if (!(t >= 1.0f)) {                          /* fcomp 00546020 = 1.0; NaN — сюда же */
    P19_OutA = P19_OutA + P8_00d164e4;
    P19_OutB = P19_OutB + P8_00d17af4;
    P19_OutC = P19_OutC + P8_00d17b24;
    P19_Out68 = P19_Out68 + P8_00d17b2c;
    wrf(&P8_00d17b14, rdf(&P8_00d17b14) + 0.002f);   /* 00546884 */
  }
  P81_Light();
}
void P103_Dawn(void) {
  int32_t ph = P80_Flag17AEC / 0x1e;
  if (G6_00B5A778 != 0 || (P62_Frame & 7) != 0) return;
  P80_Flag17AEC = P80_Flag17AEC + 1;
  if (ph < 1) {
    light_flag(1);
    lamps(1);
    { const float tgt[3] = { P80_Save0, P80_Save1, P80_Save2 }; SetScaled_004CB097(tgt, P80_SaveW); }
    return;
  }
  if (ph > 0xc && P14_00d17b18 > 2) P14_00d17b18 = P14_00d17b18 - 2;
  if (ph > 0x12) light_flag(0);
  if (ph > 0x12) { lamps(0); return; }
  if (ph > 1 && G00D17AE4 < 0xff) G00D17AE4 = (uint8_t)(G00D17AE4 + 1);
  if (ph > 3 && G00D17B10 < 0xff) G00D17B10 = (uint8_t)(G00D17B10 + 1);
  if (ph > 5 && G00D17B04 < 0xff) G00D17B04 = (uint8_t)(G00D17B04 + 1);
  P98_LampColor(G00D17AE4, G00D17B10, G00D17B04);
  if (ph > 7) light_lerp();
}
void P103_Dusk(void) {
  int32_t ph = P80_Flag17AEC / 0x1e;
  if (G6_00B5A778 != 0 || (P62_Frame & 3) != 0) return;
  P80_Flag17AEC = P80_Flag17AEC + 1;
  if (ph < 1) {
    light_flag(0);
    lamps(0);
    { const float tgt[3] = { P80_Alt0, P80_Alt1, P80_Alt2 }; SetScaled_004CB097(tgt, P80_AltW); }
    return;
  }
  if (ph > 0x10) lamps(1);
  if (ph > 0x10 && P14_00d17b18 < 0xfd) P14_00d17b18 = P14_00d17b18 + 2;
  if (ph > 0x10) light_flag(1);
  if (ph > 0x16 && G00D17B20 > 0x32) G00D17B20 = (uint8_t)(G00D17B20 - 1);
  if (ph > 0x19 && G00D17B20 > 0x32) G00D17B20 = (uint8_t)(G00D17B20 - 1);
  if (ph > 0x13 && G00D164F0 > 0x32) G00D164F0 = (uint8_t)(G00D164F0 - 1);
  if (ph > 0x10 && G00D17B21 > 0x32) G00D17B21 = (uint8_t)(G00D17B21 - 1);
  P98_LampColor(G00D17B20, G00D164F0, G00D17B21);
  if (ph > 1) light_lerp();
}

/* ---- 004e4d35: миссия 4 — расставить 13 стоящих машин трафика (x со случайным сдвигом, где он есть) ---- */
void P103_Mission4Cars(void) {
  static const int32_t za[5] = { -10000, -11000, -14000, -17000, -18500 };
  static const int32_t zb[4] = { -9000, -11000, -12000, -14000 };
  static const int32_t zc[3] = { -18000, -20000, -21000 };
  if (D_00b87e30 != 4 || P11_00d11934 != 0 || P11_00b87e38 == 0xc9 || P56_B87EA8 != 0 || G6_00B87EAC != 0) return;
  for (int32_t i = 0; i < 5; i++) P102_TrafficAdd(-16000 - (int32_t)(Rand_004D9078() & 0xfe), 200, za[i], 0x400, 0);
  P102_TrafficAdd(-12800, 200, -10200, 0x400, 0);
  for (int32_t i = 0; i < 4; i++) P102_TrafficAdd((int32_t)(Rand_004D9078() & 0xfe) - 0x125c, 200, zb[i], 0xc00, 0);
  for (int32_t i = 0; i < 3; i++) P102_TrafficAdd(-8200, 200, zc[i], 0xc00, 0);
}

/* ---- 004e5011: призрак/погоня — состояние 00d04654: 0 — старт (сообщение 0x11a/0x121), 2/3 — итог (сообщение, голос), иначе след призрака ---- */
static void set_b4654(int32_t v) { P59_S4654 = v; G2_00D04654 = v; }
void P103_GhostState(void) {
  int32_t st = P59_S4654;
  if (st == 0) {
    *(uint8_t *)&P59_Picked = 0;
    P61_V18 = 0x800;
    G2_00D044C8 = 0; G00D044C8 = 0;
    P14_00d118a8 = 0; G2_00D118A8 = 0;
    P12_00d044d0 = 0;
    P14_00c810c4 = 0;
    set_b4654(1);
    if (G6_00B87EA0 == 0) P12_Fn004E5982(0x11a, 0xfa, 0);
    else if (P11_00d11934 == 0) { if (D_00b87e30 == 4) P12_Fn004E5982(0x11a, 0xfa, 0); }
    else P12_Fn004E5982(0x121, 0xfa, 0);
  } else if (st == 2) {
    if (P14_00c81100 != 0) { P61_V18 = (P61_V18 - 0xb) & 0xfff; return; }
    if (P98_M44D8 != 0) return;
    if (P88_Mode575 != 1) {
      P12_Fn004E5982(0x11b, 0x96, 0);
      SetFirstFree_004D6190(P62_Frame % 3 + 0xf00a);
    }
    P14_00c81100 = 0x96;
    P14_00c810c4 = 0x8000;
    P98_M44D8 = 1;
  } else if (st == 3) {
    if (P14_00c81100 != 0) { P61_V18 = (P61_V18 - 0xb) & 0xfff; return; }
    if (P98_M44D8 != 0) return;
    if (P88_Mode575 != 1) {
      if (P98_M4660 == 4) { P12_Fn004E5982(0x11c, 300, 0); SetFirstFree_004D6190(0xf005); }
      else {
        uint8_t n = (uint8_t)P59_Picked;
        P12_Fn004E5982(0x11d, 0x96, 0);
        if (n < 2) SetFirstFree_004D6190(0xf007);
        else if (n < 5) SetFirstFree_004D6190(0xf006);
        else if (n < 7) SetFirstFree_004D6190(0xf008);
        else SetFirstFree_004D6190(0xf009);
      }
    }
    P59_Mode1137324 = 0; *(uint8_t *)&G2_01137324 = 0;     /* оригинал пишет байт */
    *(uint8_t *)&G2_00C54EC0 = 1;
    P14_00c81100 = 300;
    P14_00c810c4 = 0xff0;
    P98_M44D8 = 1;
  } else if (G6_00B87EA0 != 0) {
    P102_GhostTrail();
    P100_GhostNear();
  }
}

/* ---- 00414d1f: экран настроек — подписи пунктов (адреса строк языка в .data меню 0054dbc8.., шаг 0x20),
   значки ползунков, положения ползунков громкости (0054db6c/0054db94), громкость звука и CD ---- */
void P103_OptionsInit(void) {
  int32_t bits = (G6_00575F00 != 8), rate = (G6_00575F04 != 0x5622);
  if (G6_00B87EEC != 0) {
    P103_Slider = P93_FindIcon("SLIDER");              /* 0054de84 */
    P103_SliderBar = P93_FindIcon("SLIDERBA");         /* 0054de8c */
  }
  gw32(0x0054dbc8u, str_at(0x110)); gw32(0x0054dbe8u, str_at(0x12c)); gw32(0x0054dc08u, str_at(0x125));
  gw32(0x0054dc28u, str_at(0x50));  gw32(0x0054dc48u, str_at(0x51));  gw32(0x0054dc68u, str_at(0xd2));
  gw32(0x0054dc88u, str_at(0xe9));  gw32(0x0054dca8u, str_at(0xea));  gw32(0x0054dcc8u, str_at(0xeb));
  gw32(0x0054dce8u, str_at(0x52));  gw32(0x0054dcf8u, str_at(0x53));
  /* имя звукового драйвера: строка языка 0xc или запись 00bdcb74 (шаг 0x34; в native не зарегистрирована) */
  gw32(0x0054dbd8u, G6_00B91D2C == 0 ? str_at(0xc) : 0x00bdcb74u + (uint32_t)P12_00b87e58 * 0x34);
  gw32(0x0054dbf8u, str_at(gd32(0x0054de1cu + (uint32_t)P12_00b87e5c * 4)));
  gw32(0x0054dc18u, str_at(gd32(0x0054de00u + (uint32_t)P12_00575f50 * 4)));
  gw32(0x0054dc38u, str_at(gd32(0x0054de00u + (uint32_t)G8_00575F40 * 4)));
  gw32(0x0054dc58u, str_at(gd32(0x0054de00u + (uint32_t)Q00B87E90 * 4)));
  gw32(0x0054dc78u, str_at(gd32(0x0054de00u + (uint32_t)Q00B87E94 * 4)));
  gw32(0x0054dc98u, (uint32_t)gd32(0x0054de0cu + (uint32_t)bits * 4));   /* «8bit»/«16bit» */
  gw32(0x0054dcb8u, (uint32_t)gd32(0x0054de14u + (uint32_t)rate * 4));   /* «22050Hz»/«44100Hz» */
  gw32(0x0054dcd8u, str_at(gd32(0x0054de28u + (uint32_t)G6_00B87E50 * 4)));
  { float t = WF00575F14 * 116.0f; P11_00ba52d0 = (int32_t)lrintf(t); }     /* 00546044 = 116 */
  gw16(0x0054db6cu, (uint16_t)(P11_00ba52d0 + 0x1d5));
  { float t = WF00575F18 * 116.0f; P11_00ba52d0 = (int32_t)lrintf(t); }
  gw16(0x0054db94u, (uint16_t)(P11_00ba52d0 + 0x1d5));
  P48_SetMasterVolume(WF00575F14);
  { float t = WF00575F18 * 65535.0f; P11_00ba52d0 = (int32_t)lrintf(t); }  /* 0054601c = 65535 */
  P25_CDSetVolume((uint32_t)P11_00ba52d0);
}

static uint8_t *carp(int32_t i) { return (uint8_t *)&P99_Cars[i]; }
/* машина трафика i по указателю 0113a6c4 (в Game.exe — 00d07908 = запись 1); в native, если указатель не задан, — P99_Cars[1 + i] */
static uint8_t *tcar(int32_t i) {
#ifndef RE_HOOK_BUILD
  if (P59_CarsTab == NULL || i < 0 || i + 1 >= P99_CARS_N) return (i + 1 >= 0 && i + 1 < P99_CARS_N) ? carp(i + 1) : carp(P99_CARS_N - 1);
#endif
  return P59_CarsTab + (uint32_t)i * 0x148;
}

/* ---- 00493ff7: шаг записи трафика (0x54): узел дороги под машиной, выравнивание, сигнал, если машина в поле зрения ---- */
static void rd_store(uint8_t *rec) {
  wr32(rec + 0x18, P101_RdDist);
  wr32(rec + 0x1c, P101_RdLeft);
  wr32(rec + 0x20, (int32_t)(int16_t)P101_RdNode);   /* movsx */
  wr16(rec + 0xe, (uint16_t)P101_RdLane);
}
void P103_TrafficTick(uint8_t *rec) {
  if (rd32(rec + 0x38) == 0) return;
  uint8_t *car = tcar(rec[0]);
  if (rec[2] == 1) {
    if (P101_RoadNode(rd32(car + 0xc8), rd32(car + 0xd0), (int8_t)rec[0x24]) == 0) rd_store(rec);
    return;
  }
  int32_t al = 0;
  if (P62_HeadingDelta(rec, (uint32_t)rd32(rec + 0x24) << 10) < 0x20) al = P102_TrafficAlign(rec, (int32_t)re_addr(car + 0xc8), (int32_t)re_addr(car + 0xd0), (int8_t)rec[0x24]);
  int32_t r = P101_RoadNode(rd32(car + 0xc8), rd32(car + 0xd0), (int8_t)rec[0x24]);
  if ((al != 0 && (int16_t)P101_RdNode == -1) || (int16_t)P101_RdNode == 0x3fff) { P74_FreeTraffic(rec[0]); return; }
  if (r == 1 && rec[3] != 0) { P54_ObjInit(rec); return; }
  if (r != 0) return;
  rd_store(rec);
  rec[9] = (uint8_t)P59_CellLeft(rec);
  if (rd32(rec + 0x50) != 0) wr32(rec + 0x50, rd32(rec + 0x50) - 1);
  if (P62_Spd > 0x1e && rd32(rec + 0x38) > 10 && P94_InViewCone(car) != 0 && rd32(rec + 0x50) == 0) {
    int32_t k = rec[0] & 3;
    if (k == 3) k = 2;
    wr32(rec + 0x50, 0x14);
    int32_t v = P97_SndStart((uint32_t)(k + 0x19), -1, (float)rd32(car + 0xc8), (float)(-rd32(car + 0xcc)), (float)rd32(car + 0xd0));
    if (v != -1) SoundLoop_0052422D(v, (int32_t)re_addr(car + 0xc8));
  }
}

/* ---- 00492f7d: сброс трафика — счётчики, буферы, таблица машин трафика 00d07908 (P99_Cars[1..64]) и записи 011443e0 ---- */
void P103_TrafficReset(void) {
  D_01134ea0 = 0; P102_HitFrame = 0; P75_E8 = 0; P103_13A5A0 = 0; P103_145A44 = 0; P103_1426EC = 0; P103_143724 = 0; P103_1426F4 = 0;
  P14_Fn0048DB65(P75_Spawn, 0xb40);
  P14_Fn0048DB65(P102_DustPts, 0xb40);
  P14_Fn0048DB65(P63_Ids, 0x100);
  P14_Fn0048DB65(P63_Dist, 0x100);
  P14_Fn0048DB65(P12_01144340, 0x80);
  P54_G44 = 0; P54_G40 = 0; P63_Near = 0; P103_144320 = 0; P75_43CC = 0; G2_01143600 = 0; P102_DustN = 0; P75_43D0 = 0; P75_4288 = 0;
  P63_Cnt3 = 0; P63_Cnt2 = 0; P63_Cnt1 = 0; P63_Cnt0 = 0; P103_1426E0 = 0; P103_1426F0 = 0;
  P103_1426F4 = 5; P103_143724 = 10; P103_1426EC = 4; P103_145A44 = 2; P103_13A5A0 = 0; P75_E8 = 0;
  P75_12BC = WI00575EE4;                                /* число машин трафика из настроек (00575ee4) */
  G01145934 = 0; P103_139A38 = 0; P103_1373D4 = 0; G01144284 = 0; G0113A6C0 = 0;
  P103_1443C0 = -1; G011426F8 = -1;
#ifdef RE_HOOK_BUILD
  *(uint32_t *)&P99_RoadPick = 0xffff;                 /* оригинал пишет dword 0x0000ffff в 011443c4 */
#else
  P99_RoadPick = -1;                                   /* native: слово 011443c4 (старшее слово отдельно не хранится) */
#endif
  P100_143720 = 0; P75_E4 = 0; P100_1426FC = 0; P62_I14428C = 0; S_01139A34 = 0;
  P96_InitRotTab();
  P73_RoadSides();
  P101_RoadBounds();
  P14_Fn0051BED5();
  P59_CarsTab = carp(1); G0113A6C4 = P59_CarsTab;      /* 00d07908 */
  P14_Fn0048DB65(carp(1), 0x5200);
  P14_Fn0048DB65(TrafficRecs, 0x1500);
  G2_01143600 = 0;
  uint8_t *r = TrafficRecs;
  for (int32_t i = 0; i < 0x40; i++, r += 0x54) {
    G2_ARR_01145940[i] = i;
    r[8] = 0; r[0] = (uint8_t)i; r[1] = 0;
  }
}

/* ---- 0051b208: соседний узел дороги по клетке карты (x, z): шаг по строке (bit0 dir = 0) или по столбцу (= 1)
   за пределы участка с тем же номером; 011426f0 — с какой стороны (1 — к началу, 0 — к концу), иначе 0xff ---- */
static int16_t road_cell(int32_t w, int32_t row, int32_t col, int32_t n) {
  const int16_t *ta = (const int16_t *)P54_RoadA[w];
#ifndef RE_HOOK_BUILD
  if (ta == NULL || row < 0 || col < 0 || row >= n || col >= n) return -1;   /* в оригинале — чтение за таблицей */
#endif
  return ta[row * n + col];
}
int32_t P103_RoadNeighbour(int32_t x, int32_t z, uint32_t dir) {
  int32_t cx = (x + 0x2ee + P62_MapC64) / 0x5dc;
  int32_t cz = (P62_Map2C40 - (z - 0x2ee)) / 0x5dc;
  P103_1426F0 = 0xff;
  if (cx < 0 || cx >= P54_MapB1 || cz < 0 || cz >= P54_MapB2) return -1;
  int32_t n = P62_MapN;
#ifndef RE_HOOK_BUILD
  if (n == 0) return -1;
#endif
  int32_t col = cx - (cx / n) * n, row = cz - (cz / n) * n;
  int32_t w = ((cx / n) & 1) + (((P72_Rows - 1) - cz / n) & 1) * 2;
  int16_t s = road_cell(w, row, col, n);
  if (s == -1) return -1;
  int32_t lim = P58_DemoFlag == 0 ? P11_00b5a8e8 : 0x3fff;
  int16_t v;
  if ((dir & 1) == 0) {
    int32_t c = col;
    while (road_cell(w, row, c, n) == s) c--;
    v = road_cell(w, row, c - 1, n);
    if (v > -1 && v < lim) { P103_1426F0 = 1; return v; }
    c = col;
    while (road_cell(w, row, c, n) == s) c++;
    v = road_cell(w, row, c + 1, n);
    if (v > -1 && v < lim) { P103_1426F0 = 0; return v; }
  } else {
    int32_t r = row;
    while (road_cell(w, r, col, n) == s) r++;
    v = road_cell(w, r + 1, col, n);
    if (v > -1 && v < lim) { P103_1426F0 = 1; return v; }
    r = row;
    while (road_cell(w, r, col, n) == s) r--;
    v = road_cell(w, r - 1, col, n);
    if (v > -1 && v < lim) { P103_1426F0 = 0; return v; }
  }
  return -1;
}

/* запись модели машины m (00d0cc60 + m*0x16c); в native — в пределах S_00D0CC60 (0x4000 байт), иначе нули */
static const uint8_t *carmodel(uint32_t m) {
#ifndef RE_HOOK_BUILD
  static const uint8_t zero[0x16c];
  if ((m + 1) * 0x16c > sizeof S_00D0CC60) return zero;
#endif
  return S_00D0CC60 + m * 0x16c;
}
/* запись трафика i (0x54); в native вне 0..0x3f — пустая */
static uint8_t *trec(int32_t i) {
#ifndef RE_HOOK_BUILD
  if (i < 0 || i >= 0x40) { static uint8_t dummy[0x54]; memset(dummy, 0, sizeof dummy); return dummy; }
#endif
  return TrafficRecs + i * 0x54;
}

/* ---- 0049aa14: повреждение машины от удара: сторона по направлению dir в осях машины (матрица +4..+0x14, int16),
   сила → накопление в +0x11c[сторона], +0x138; очки за повреждение машин миссии (01136920 бит 0) ---- */
int32_t P103_CarDamage(uint8_t *car, const int32_t *dir, int32_t force) {
  uint8_t id = car[0];
  if ((id == 0 || G6_00B87EA0 != 0) && MenuOptBDFA4C != 0) return 0;
  if (MenuOptBDFA58 != 0 && car[2] == 1) return 0;
  if (id == 0 || id > 0x40) force = mul(force, P103_DmgPct) / 100;
  if (force < 0x1000) return 0;
  int32_t side = (int32_t)((uint32_t)mul(rd16s(car + 8), dir[0]) + (uint32_t)mul(rd16s(car + 0xe), dir[1]) + 0x800u + (uint32_t)mul(rd16s(car + 0x14), dir[2])) >> 0xc;
  int16_t half = (int16_t)(rd16s(carmodel(car[2]) + 0x168) >> 1);
  int32_t fwd = (int32_t)((uint32_t)mul(rd16s(car + 4), dir[0]) + (uint32_t)mul(rd16s(car + 0xa), dir[1]) + 0x800u + (uint32_t)mul(rd16s(car + 0x10), dir[2])) >> 0xc;
  int32_t k;
  if (fwd < 1) k = half < side ? 0 : (-(int32_t)half < side) + 4;
  else         k = half < side ? 1 : (side <= -(int32_t)half) + 2;
  int32_t v = force >> 8;
  if (id == 0 || id > 0x40) {
    if (v > 0x400) v = 0x400;
    v = (v * 0x400 + v * v) >> 10;
  } else {
    switch (P11_00b87e38) {
    case 0x15a: case 0x15b: case 0x1be: case 0x1bf:
      v = ((force / 400 + 0x400) * 7) / 8;
      break;
    default:
      if (v > 0x400) v = 0x400;
      v = ((v * 0x400 + v * v) >> 10) + 0x10;
    }
  }
  int32_t mis = id != 0 && (G6_01136920 & 1) != 0 && trec(id - 1)[5] == 0;
  uint8_t *acc = car + 0x11c + k * 4;
  if (mis) P69_Bonus = P69_Bonus - rd32(acc);
  wr32(acc, 0xfff - ((int32_t)((uint32_t)mul(0xfff - v, 0xfff - rd32(acc)) + 0x800u) >> 0xc));
  wr32(car + 0x138, rd32(car + 0x138) + v);
  int32_t h = rd32(acc) / 2;
  switch (k) {
  case 0: if (rd32(car + 0x120) < h) wr32(car + 0x120, h); break;
  case 1: if (rd32(car + 0x11c) < h) wr32(car + 0x11c, h); break;
  case 3: if (rd32(car + 0x12c) < h) wr32(car + 0x12c, h); break;
  case 4: if (rd32(car + 0x128) < h) wr32(car + 0x128, h); break;
  default: break;
  }
  if (mis) { P69_Bonus = P69_Bonus + rd32(acc); P69_AddScore(0xff00); }
  return 1;
}

/* приближённое расстояние max + min/2 */
static int32_t dist2(int32_t dx, int32_t dz) {
  int32_t a = iabs(dx), b = iabs(dz);
  return a < b ? b + a / 2 : a + b / 2;
}
/* ---- 004a6a57: коп (запись 0xcd8 в 0112da00: +0xc64/+0xc6c позиция, +0xc курс, +0x28 скорость) и машина трафика rec:
   ближе 15000 — 1, если машину ведёт игрок-коп/никто; иначе прогноз движения обоих до 20 шагов — сближение < 0x4b0 → +0x3c = 0x14, 1 ---- */
int32_t P103_CopMeet(uint8_t *cop, const uint8_t *rec) {
  const uint8_t *car = tcar(rec[0]);
  int32_t cx = rd32(car + 0xc8), cz = rd32(car + 0xd0);
  int32_t px = rd32(cop + 0xc64), pz = rd32(cop + 0xc6c);
  int32_t dx = cx - px, dz = cz - pz;
  int32_t d = dist2(dx, dz);
  if (d >= 15000) return 0;
  if (rec[5] == 0) return 1;
#ifndef RE_HOOK_BUILD
  if (rec[5] > 8) return 0;
#endif
  if (P12_0112da00[(rec[5] - 1) * 0x336 + 0x331] == 1) return 1;
  uint32_t a = (uint32_t)P44_Atan2(dx, dz);
  if (iabs((int32_t)((((a & 0xfff) - (uint32_t)rd32(cop + 0xc)) + 0x800) & 0xfff) - 0x800) >= 0x400) return 0;
  int32_t sp = rd32(cop + 0x28), csp = rd32(car + 0x110);
  uint32_t hd = (uint32_t)rd32(cop + 0xc), chd = (uint32_t)rd32(car + 0x100);
  int32_t n = sp == 0 ? 0 : d / sp;
  int32_t sx, sz, vx, vz;
  if (n < 4) {
    sx = mul(sp, P59_Sin[hd & 0xfff]) >> 0xc;  sz = mul(sp, P59_Sin[(hd + 0x400) & 0xfff]) >> 0xc;
    vx = mul(csp, P59_Sin[chd & 0xfff]) >> 0xc; vz = mul(csp, P59_Sin[(chd + 0x400) & 0xfff]) >> 0xc;
  } else {
    n = n / 4;
    sx = mul(sp, P59_Sin[hd & 0xfff]) >> 10;  sz = mul(sp, P59_Sin[(hd + 0x400) & 0xfff]) >> 10;
    vx = mul(csp, P59_Sin[chd & 0xfff]) >> 10; vz = mul(csp, P59_Sin[(chd + 0x400) & 0xfff]) >> 10;
  }
  if (n > 0x14) n = 0x14;
  for (; n != 0; n--) {
    px += sx; pz += sz; cx += vx; cz += vz;
    if (dist2(px - cx, pz - cz) < 0x4b0) { wr32(cop + 0x3c, 0x14); return 1; }
  }
  return 0;
}

/* ---- 005179d0: сброс записи/воспроизведения повтора (метка __fastcall ложная: ecx лишь проходит в 0048db65) ---- */
void P103_ReplayReset(void) {
  P101_RecState = 1; P101_RecSaved = 0;
  *(uint8_t *)&G2_00C54EC0 = 0;                      /* оригинал пишет байт */
  P103_C4D9A0 = 0; P100_RecEnd = 0; P103_C4D664 = 0; P96_ReplayB = 0; P100_RecBuf = NULL; P74_C54D08 = 0;
  P100_RecCnt[4] = 0; P100_RecCnt[3] = 0; P100_RecCnt[2] = 0; P100_RecCnt[1] = 0; P100_RecCnt[0] = 0;
  P101_RecFrame = 0; P101_RecFrame2 = 0; P74_C4BDE0 = 0; P74_B5A89C = 0; P103_C4D920 = 0; P103_C54D04 = 0; P103_C54FC4 = 0;
  P14_Fn0048DB65(P98_CamRecs, 0x5000);
  G6_00B5A8A0 = 0; P47_CamB = 0;
  *(uint8_t *)&P52_ResetA = 0; P103_B5A8A9 = 0; P103_B5A8AA = 0;
  P103_C54D00 = 0; P103_C54EC4 = 0; P103_C4D924 = 0; P103_C54AA0 = 0; P103_C54FC0 = 0;
  P100_RecStop = 0; P103_C4D874 = 0; G6_00B5A8AC = 0; G6_00B5A8B0 = 0; G6_00575A70 = -1;
  P103_B5A8B4 = 0; P103_B5A8B8 = 0; P103_B5A84C = 0; P103_B5A848 = 0; P55_RecBase = NULL; P55_RecCnt = 0; P103_B5A8C4 = 0; P103_B5A8C8 = 0;
  G00B5A8CD = 0;
  P14_Fn0048DB65(P103_C54EE0, 0x88);
  P14_Fn0048DB65(P101_SaveCar, 0x148);
  for (int32_t i = 0; i < 5; i++) {
    P100_RecPtr[i] = 0; P100_RecOff[i] = 0; P74_B5A858[i] = 0; P100_RecVal[i] = 0; P74_C4D7A0[i] = 0;
    P100_RecRep[i] = 0; P74_B5A86C[i] = 0; P74_B5A880[i] = 0; P100_RecTot[i] = 0;
  }
  P100_RecKeys = 0x20;
  P96_ReplayB = 0; P74_B5A894 = 0; P103_B5A895 = 0; P12_00b5a898 = 0; P74_B5A89C = 0; G6_00B5A8A0 = 0; P47_CamB = 0;
  *(uint8_t *)&P52_ResetA = 0; P103_B5A8A9 = 0; P103_B5A8AA = 0; P100_RecStop = 0;
  P55_RecCnt = 0; P103_B5A8C4 = 0; P103_B5A8C8 = 0; G00B5A8CD = 0; G6_00B5A8AC = 0; G6_00B5A8B0 = 0; P103_C4D9A4 = 0;
  P103_B5A84C = 0; G6_00575A70 = -1; P103_B5A848 = 0; P103_B5A8B4 = 0; P103_B5A8B8 = 0; P55_RecBase = NULL; P100_RecBuf = NULL;
}

/* ---- 00492530: новая машина трафика: слот записи (при нехватке освобождается машина с наибольшим x+z), запись 0x54,
   машина 0x148 (курс, модель, позиция), коп в таблице 0112da00 (тип 1/2), модель, направление, клетка ---- */
static int32_t fistp_ld(int32_t v, float s) { return (int32_t)lrintl((long double)v * (long double)s); }   /* fild; fmul; fistp */
void P103_TrafficSpawn(int8_t lane, int32_t kind, int8_t speed, int32_t heading, int32_t x, int32_t z) {
  int32_t i;
  if (P58_SB87EB0 == 0) i = PopIndex00493E9B();
  else { i = AllocSlot00492508(); if (i == -1) return; }
  if (i == -1) {
    int32_t best = 0, bi = 0;
    for (int32_t k = 0; k < WI00575EE4; k++) {
      int32_t v = rd32(tcar(k) + 0xc8) + rd32(tcar(k) + 0xd0);
      if (best < v) { bi = k; best = v; }
    }
    P74_FreeTraffic(bi);
    i = PopIndex00493E9B();
  }
#ifndef RE_HOOK_BUILD
  if (i < 0 || i >= 0x40) return;
#endif
  uint8_t *r = trec(i), *c = tcar(i);
  P14_Fn0048DB65(c, 0x148);
  c[0] = (uint8_t)(i + 1);
  r[1] = 1; r[6] = (uint8_t)(lane + 1); r[7] = 0; r[8] = 0; r[2] = 0;
  wr32(r + 0x28, -1);
  wr32(c + 0x100, heading);
  c[2] = (uint8_t)kind;
  wr32(c + 0xc8, x);
  wr32(c + 0xd0, z);
  P101_CarGround((p99_car_t *)c, r);
  wr32(r + 0x44, 0x7fffffff); wr32(r + 0x40, 0x7fffffff); wr32(r + 0x3c, 0); wr32(r + 0x38, 0);
  r[0xd] = (uint8_t)(speed + 4);
  r[0xc] = (uint8_t)kind;
  if (kind == 1) { r[5] = 1; r[0xd] = 0x19; }
  else if (kind == 2) { r[5] = 1; r[0xc] = 2; r[0xd] = 4; }
  else r[5] = 0;
  if (r[5] != 0) {
    int32_t s = P62_FindFreeTrafficSlot();
    r[5] = (uint8_t)s;
    s = s - 1;
#ifndef RE_HOOK_BUILD
    if (s >= 0 && s < 8)
#endif
    {
      uint32_t *cop = &P12_0112da00[s * 0x336];
      P14_Fn0048DB65(cop, 0xcd8);
      cop[0] = (uint32_t)s;
      cop[0x32d] = 1;
      cop[0x334] = re_addr(tcar(r[0]));
      cop[0x32f] = 1;
#ifndef RE_HOOK_BUILD
      if (s < 16) wr32(P74_Cars + s * 0xcd8, 1);       /* псевдоним 0112e6b4 */
#endif
    }
    G0112B284 = G0112B284 + 1;
  }
  P99_CarModelClean(i);
  P59_ObjDir(c, 1);
  wr32(r + 0x48, rd32(tcar(r[0]) + 0xc8) + 0x2ee);
  wr32(r + 0x4c, rd32(tcar(r[0]) + 0xd0) - 0x2ee);
  P11_00ba52d0 = fistp_ld(rd32(r + 0x48), P63_Scale); wr32(r + 0x48, P11_00ba52d0);
  P11_00ba52d0 = fistp_ld(rd32(r + 0x4c), P63_Scale); wr32(r + 0x4c, P11_00ba52d0);
  r[0x13] = 0;
}

/* ---- 0048edff: можно ли машине трафика rec (0x54) перестроиться / проехать узел: машины на соседних полосах слота
   (P11_00c1ed80 + узел*0x2c + 0xa + полоса*8) ближе 15000 мешают; затем P59_TrafficCheck ---- */
static int16_t slot_lane(int32_t node, uint32_t lane) {
  const uint8_t *p = (const uint8_t *)P11_00c1ed80;
#ifndef RE_HOOK_BUILD
  if (node < 0 || (uint32_t)(node + 1) * 0x2c > sizeof P11_00c1ed80) return -1;
#endif
  return rd16s(p + node * 0x2c + 0xa + lane * 8);
}
static int32_t trec_i32(uint32_t i, uint32_t off) {
#ifndef RE_HOOK_BUILD
  if (i >= 0x40) return 0;
#endif
  return rd32(TrafficRecs + i * 0x54 + off);
}
int32_t P103_TrafficCanGo(uint8_t *r) {
  int32_t node = rd32(r + 0x20);
  uint32_t lm = (uint32_t)(rd32(r + 0x24) - 1) & 3, lp = (uint32_t)(rd32(r + 0x24) + 1) & 3;
  int32_t a = slot_lane(node, lm), b = slot_lane(node, lp);
  int32_t st = rd32(r + 0x34), n;
  if (st == 0) {
    if (a != -1) {
      n = P63_NearOnNode(r[0], a, (int32_t)lp, node);
      for (int32_t k = 0; k < n; k++) {
        if (P63_Dist[k] >= 15000) continue;
        uint32_t id = (uint32_t)P63_Ids[k];
        if ((id & 0x80) != 0) return 0;
        if (trec_i32(id, 0x38) != 0 && trec_i32(id, 0x2c) != rd32(r + 0x28)) return 0;
      }
    }
    if (b != -1) {
      n = P63_NearOnNode(r[0], b, (int32_t)lm, node);
      for (int32_t k = 0; k < n; k++)
        if (P63_Dist[k] < 15000 && trec_i32((uint32_t)P63_Ids[k], 0x38) != 0) return 0;
    }
    if (P59_TrafficCheck(r, 1) != 0) return 0;
  } else if (st < 1) {
    if (a != -1) {
      n = P63_NearOnNode(r[0], a, (int32_t)lp, node);
      for (int32_t k = 0; k < n; k++) {
        if (P63_Dist[k] >= 15000) continue;
        uint32_t id = (uint32_t)P63_Ids[k];
        if ((id & 0x80) != 0) return 0;
        if (trec_i32(id, 0x38) != 0 && trec_i32(id, 0x2c) != rd32(r + 0x28)) return 0;
      }
    }
    if (b != -1) {
      n = P63_NearOnNode(r[0], b, (int32_t)lm, node);
      for (int32_t k = 0; k < n; k++) {
        if (P63_Dist[k] >= 15000) continue;
        uint32_t id = (uint32_t)P63_Ids[k];
        if ((id & 0x80) != 0) return 0;
        if (trec_i32(id, 0x2c) != slot_lane(node, (uint32_t)rd32(r + 0x24)) && trec_i32(id, 0x38) != 0) return 0;
      }
    }
    if (P59_TrafficCheck(r, 1) != 0) return 0;
  } else {
    if (a != -1) {
      n = P63_NearOnNode(r[0], a, (int32_t)lp, node);
      for (int32_t k = 0; k < n; k++) {
        if (P63_Dist[k] >= 15000) continue;
        uint32_t id = (uint32_t)P63_Ids[k];
        if ((id & 0x80) != 0) return 0;
        /* оригинал проверяет +0x38 записи 01144320 (не найденной) — сохранено */
        if (trec_i32(id, 0x2c) == b && trec_i32((uint32_t)P103_144320, 0x38) != 0) return 0;
      }
    }
    if (P59_TrafficCheck(r, 1) != 0) return 0;
  }
  return 1;
}

/* ---- 004deb99: коробки машин (по модели и матрице, /16) и пометка пересекающихся пар (+0x13c = 1, ClearFlagByte0048FBBA) ---- */
static int32_t half_ext(int16_t m, int16_t a) {          /* |a * (m*9/8)| */
  return iabs(mul(a, mul(m, 9) / 8));
}
void P103_CarsOverlap(void) {
  if (P95_B87E14 != 0 || G6_00B87EA0 != 0) return;
  int32_t n = (P58_SB87EB0 == 0 && G6_00B87EAC == 0) ? 0x41 : 0x42;
  int32_t *bx = P103_CarBoxes;
  for (int32_t i = 0; i < n; i++, bx += 6) {
    const uint8_t *c = carp(i), *m = carmodel(c[2]);
    int16_t mx = rd16s(m + 0x164), my = rd16s(m + 0x166), mz = rd16s(m + 0x168);
    int32_t ex = ((half_ext(mz, rd16s(c + 8)) + 0x800 + half_ext(mx, rd16s(c + 4))) >> 0xc) + my;
    int32_t ez = ((half_ext(mz, rd16s(c + 0x14)) + 0x800 + half_ext(mx, rd16s(c + 0x10))) >> 0xc) + my;
    bx[0] = (rd32(c + 0x18) - ex) / 16;
    bx[2] = (rd32(c + 0x20) - ez) / 16;
    bx[3] = (rd32(c + 0x18) + ex) / 16;
    bx[5] = (rd32(c + 0x20) + ez) / 16;
    int32_t vx = rd32(c + 0x40), vz = rd32(c + 0x48);
    if (vx < 0) bx[0] += ((vx + 0x800) >> 0xc) / 8; else bx[3] += ((vx + 0x800) >> 0xc) / 8;
    if (vz < 0) bx[2] += ((vz + 0x800) >> 0xc) / 8; else bx[5] += ((vz + 0x800) >> 0xc) / 8;
    bx[1] = (rd32(c + 0xcc) - 0x960) / 16;
    bx[4] = (rd32(c + 0xcc) + 0x960) / 16;
  }
  const int32_t *a = P103_CarBoxes;
  for (int32_t i = 0; i < n; i++, a += 6) {
    for (int32_t j = i + 1; j < n; j++) {
      const int32_t *b = P103_CarBoxes + j * 6;
      if (b[0] < a[3] && b[2] < a[5] && a[0] < b[3] && a[2] < b[5] && b[1] < a[4] && a[1] < b[4] &&
          (i == 0 || trec(i - 1)[1] != 0) && trec(j - 1)[1] != 0) {
        wr16(carp(i) + 0x13c, 1);
        wr16(carp(j) + 0x13c, 1);
        ClearFlagByte0048FBBA(i);
        ClearFlagByte0048FBBA(j);
      }
    }
  }
}

/* ---- 0049a520: момент касания двух коробок (пара записей 0x60 в p): двоичный поиск по скорости (+0x30/+0x38/+0x5c,
   8 делений пополам) с P100_BoxOverlap; результат 0..0x1000, out+0x24 — «было касание в начале» ---- */
static void box_step(int32_t *p, int32_t sgn) {
  for (int32_t i = 1; i >= 0; i--) {
    int32_t *b = p + i * 0x18;
    if (sgn > 0) { b[0] += b[0xc]; b[2] += b[0xe]; b[0x10] += b[0x17]; }
    else         { b[0] -= b[0xc]; b[2] -= b[0xe]; b[0x10] -= b[0x17]; }
  }
}
int32_t P103_BoxContactTime(int32_t *p, uint8_t *out) {
  int32_t hit = 1, first = 1, t = 0x1000, step = 0x800;
  int32_t sx[2], sz[2], sy[2];
  for (int32_t i = 1; i >= 0; i--) { sx[i] = p[i * 0x18]; sz[i] = p[i * 0x18 + 2]; sy[i] = p[i * 0x18 + 0x10]; }
  for (int32_t k = 8; k != 0; ) {
    k--;
    for (int32_t i = 1; i >= 0; i--) {
      int32_t *b = p + i * 0x18;
      b[0xc] >>= 1; b[0xe] >>= 1; b[0x17] >>= 1;
      if (hit == 0) { b[0] += b[0xc]; b[2] += b[0xe]; b[0x10] += b[0x17]; }
      else          { b[0] -= b[0xc]; b[2] -= b[0xe]; b[0x10] -= b[0x17]; }
    }
    if (hit == 0) { first = 0; t += step; } else t -= step;
    hit = P100_BoxOverlap(p);
    if (k != 0) step >>= 1;
  }
  if (hit == 0) {
    box_step(p, 1);
    t += step;
    P100_BoxOverlap(p);
  } else if (first != 0) {
    for (int32_t i = 1; i >= 0; i--) {
      p[i * 0x18] = sx[i]; p[i * 0x18 + 2] = sz[i]; p[i * 0x18 + 0x10] = sy[i];
      hit = P100_BoxOverlap(p);
    }
    t = 0x1000;
  }
  wr32(out + 0x24, first);
  return t;
}

/* ---- 004dcb62: высота поверхности под точкой pos (x, -, z): клетка карты 0x5dc → запись P54_RoadB → блок P58_BlkIdx,
   поиск четырёхугольника (+0x30 = 4 — P44_PointInQuad, иначе треугольник P14_Fn00526A34), плоскость +0x20/+0x28/+0x2c ---- */
static float plane_h(const uint8_t *q, int32_t x, int32_t z) {
  float a = (float)((long double)(float)x * rdf(q + 0x20) + (long double)(float)z * rdf(q + 0x28) - rdf(q + 0x2c));
  return a - (float)P72_Low;
}
static int32_t quad_hit(const uint8_t *q, int32_t x, int32_t z) {
  return rd16s(q + 0x30) == 4 ? P44_PointInQuad(x, z, (const int32_t *)q) : P14_Fn00526A34(x, z, (const int32_t *)q);
}
float P103_RoadHeight(const float *pos) {
  static const int16_t dirs[4] = { 0, 0x400, 0x800, 0xc00 };     /* .data 005624a8 */
  uint8_t *prev = P103_HQuad;
  P11_00ba52d0 = (int32_t)lrintf(pos[0]); int32_t x = P11_00ba52d0;
  P11_00ba52d0 = (int32_t)lrintf(pos[2]); int32_t z = P11_00ba52d0;
  int32_t ax = x + 0x2ee + P62_MapC64, az = P62_Map2C40 - (z - 0x2ee);
  int32_t cx = ax / 0x5dc, cz = az / 0x5dc, rx = ax % 0x5dc, rz = az % 0x5dc;
  int32_t same = (cx == P103_HCellX && cz == P103_HCellZ);
  if (!same) {
    if (cx < 0 || cx >= P54_MapB1 || cz < 0 || cz >= P54_MapB2) { P103_HQuad = NULL; P103_HCellZ = 0x7fffff; P103_HCellX = 0x7fffff; return 0.0f; }
    int32_t n = P62_MapN;
#ifndef RE_HOOK_BUILD
    if (n == 0) { P103_HQuad = NULL; P103_HCellZ = 0x7fffff; P103_HCellX = 0x7fffff; return 0.0f; }
#endif
    const uint32_t *tb = (const uint32_t *)P54_RoadB[((cx / n) & 1) + (((P72_Rows - 1) - cz / n) & 1) * 2];
#ifndef RE_HOOK_BUILD
    if (tb == NULL) { P103_HQuad = NULL; P103_HCellZ = 0x7fffff; P103_HCellX = 0x7fffff; return 0.0f; }
#endif
    uint32_t v = tb[(cz - (cz / n) * n) * n + (cx - (cx / n) * n)];
    if (v == 0) { P103_HQuad = NULL; P103_HCellZ = 0x7fffff; P103_HCellX = 0x7fffff; return 0.0f; }
    P72_Id = (uint16_t)((v >> 16) & 0x3ff);
    P72_Low = (int32_t)(int16_t)v;
    P72_Dir = (uint16_t)dirs[v >> 0x1e];
    P103_HBlk = (uint8_t *)P58_BlkIdx[(int16_t)P72_Id];
  }
  if (P103_HBlk == NULL) { P103_HCellX = 0x7fffff; P103_HCellZ = 0x7fffff; P103_HQuad = NULL; return (float)(-P72_Low); }
  rx = 0x2ee - iabs(rx); rz = 0x2ee - iabs(rz);
  uint32_t d = (uint32_t)(-(int32_t)(int16_t)P72_Dir) & 0xfff;
  int32_t lx = x, lz = z;
  if (d < 0x801) {
    if (d == 0x800) { lz = -rz; lx = rx; }
    else if (d == 0) { lz = rz; lx = -rx; }
    else if (d == 0x400) { lz = rx; lx = rz; }
  } else if (d == 0xc00) { lz = -rx; lx = -rz; }
  P103_HCellZ = cz; P103_HCellX = cx;
  if (same && P103_HQuad != NULL && quad_hit(P103_HQuad, lx, lz) != 0) return plane_h(prev, lx, lz);
  uint8_t *q = P103_HBlk + 8;
  for (int32_t k = 0; k < rd16s(P103_HBlk + 6); k++, q += 0x34)
    if (quad_hit(q, lx, lz) != 0) { P103_HQuad = q; return plane_h(q, lx, lz); }
  P103_HQuad = NULL;
  return (float)(-P72_Low);
}

/* ---- 004dd262: точка на поверхности под pos (x, y, z): out = (x, высота, z), normal — нормаль ×4096;
   модель клетки с флагом 0x80 (вода) — качка по P43_Sin, флаг 0x4000 — волны по P59_Sin; возврат 0x1000 / 0x800 ---- */
static const uint8_t *cell_model(void) {
#ifndef RE_HOOK_BUILD
  if (P72_Id >= 1126 || P79_ModelTab[P72_Id] == 0) return NULL;
#endif
  return P79_ModelTab[P72_Id] == 0 ? NULL : (const uint8_t *)P79_PTR(P79_ModelTab[P72_Id]);
}
int32_t P103_GroundAt(const int32_t *pos, int32_t *normal, int32_t *out) {
  P56_B2EA48 = 0;
  out[0] = pos[0]; int32_t x = out[0];
  out[2] = pos[2]; int32_t z = out[2];
  if (P72_RoadLookup(x, z) == 0) { normal[0] = 0; normal[1] = 0x1000; normal[2] = 0; out[1] = 0; return 0x1000; }
  const uint8_t *blk = (const uint8_t *)P58_BlkIdx[P72_Id];
  if (blk == NULL) {
    out[1] = -P72_Low;
    normal[0] = 0; normal[1] = 0x1000; normal[2] = 0;
    const uint8_t *m = cell_model();
    if (m == NULL || (rd16(m + 2) & 0x80) == 0 || pos[1] - out[1] > 0x13) {
      if (m == NULL || (rd32(m + 8) & 0x4000) == 0) return 0x1000;
      out[1] += (int32_t)P59_Sin[((uint32_t)(x + z) * 2) & 0xfff] >> 9;
      return 0x800;
    }
    int32_t ph = P103_D118E0;
#ifndef RE_HOOK_BUILD
    if (ph < 0 || ph >= 5120) ph = 0;
#endif
    { float t = P43_Sin[ph] * 30.0f; P11_00ba52d0 = (int32_t)lrintf(t); }   /* 005468cc = 30 */
    out[1] -= P11_00ba52d0 + 200;
    P102_D0DD74 = P102_D0DD74 + 1;
    return 0x800;
  }
  int32_t rx = (x + 0x2ee + P62_MapC64) % 0x5dc; rx = 0x2ee - iabs(rx);
  int32_t rz = (P62_Map2C40 - (z - 0x2ee)) % 0x5dc; rz = 0x2ee - iabs(rz);
  uint32_t d = (uint32_t)(-(int32_t)(int16_t)P72_Dir) & 0xfff;
  int32_t lx = x, lz = z;
  if (d < 0x801) {
    if (d == 0x800) { lz = -rz; lx = rx; }
    else if (d == 0) { lz = rz; lx = -rx; }
    else if (d == 0x400) { lz = rx; lx = rz; }
  } else if (d == 0xc00) { lz = -rx; lx = -rz; }
  const uint8_t *q = blk + 8;
  for (int32_t k = 0; k < rd16s(blk + 6); k++, q += 0x34) {
    if (quad_hit(q, lx, lz) == 0) continue;
    float nx = rdf(q + 0x20), ny = rdf(q + 0x24), nz = rdf(q + 0x28);
    float h = plane_h(q, lx, lz);
    if (d == 0) { nz = -nz; nx = -nx; }
    else if (d == 0x400) { float t = nx; nx = nz; nz = -t; }
    else if (d == 0xc00) { float t = nx; nx = -nz; nz = t; }
    { float t = 4096.0f * nx; P11_00ba52d0 = (int32_t)lrintf(t); normal[0] = P11_00ba52d0; }   /* 005461ec = 4096 */
    { float t = 4096.0f * ny; P11_00ba52d0 = (int32_t)lrintf(t); normal[1] = P11_00ba52d0; }
    { float t = 4096.0f * nz; P11_00ba52d0 = (int32_t)lrintf(t); normal[2] = P11_00ba52d0; }
    P11_00ba52d0 = (int32_t)lrintf(h); out[1] = P11_00ba52d0;
    const uint8_t *m = cell_model();
    if (m != NULL && (rd32(m + 8) & 0x4000) != 0) {
      P56_B2EA48 = 1;
      out[1] += (int32_t)P59_Sin[((uint32_t)(lx + lz) * 2) & 0xfff] >> 9;
      return 0x800;
    }
    return 0x1000;
  }
  normal[0] = 0; normal[1] = 0x1000; normal[2] = 0;
  out[1] = -P72_Low;
  return 0x1000;
}

/* ---- 00512de7: движение частицы по пути (тип +0x1c: буфер P54_Tab4[тип-1], точек P103_PathLen[тип-1], шаг
   P12_00c821a0*0x14+0x10): курс +0x5e (P43_Sin), позиция +0x84/+0x8c, номер точки +0x34 (+= +0x30); тип 3 — множитель
   по удалению от игрока; флаг 0x80 — счётчик жизни +0x40 (0..5), по истечении ResetObjState_00514E99 ---- */
void P103_PartPath(uint8_t *p) {
  int16_t ang = rd16s(p + 0x5e);
#ifndef RE_HOOK_BUILD
  if (ang < 0 || ang + 0x400 >= 5120) ang = 0;
#endif
  float c = P43_Sin[0x400 + ang], s = P43_Sin[ang];    /* 00b95280 / 00b94280 */
  int32_t ty = rd32(p + 0x1c) - 1;
#ifndef RE_HOOK_BUILD
  if (ty < 0 || ty >= 4) return;
#endif
  int32_t k = rd32(p + 0x34);
  int32_t n = P103_PathLen[ty];
  const uint8_t *buf = (const uint8_t *)P54_Tab4[ty];
  uint32_t fl = (uint32_t)rd32(p + 0xc);
  if ((fl & 0x80) != 0) {
    if (rd32(p + 0x40) > 4) wr32(p + 0x40, 5);
    if (rd32(p + 0x40) < 0) wr32(p + 0x40, 0);
  }
  if (G6_00B5A778 == 0) wr32(p + 0x34, rd32(p + 0x34) + rd32(p + 0x30));
  if ((fl & 0x80) == 0) {
#ifndef RE_HOOK_BUILD
    if (buf == NULL || n <= 0) return;
#endif
    P100_PartBase[0] = rdf(p + 0x84);
    memcpy(&P100_PartBase[1], p + 0x88, 4);
    P100_PartBase[2] = rdf(p + 0x8c);
    int32_t st = P12_00c821a0 * 0x14 + 0x10;
    while (++k <= rd32(p + 0x34)) {
      const uint8_t *pt = buf + (k < n ? mul(st, k) : mul(st, k % n));
      float a = rdf(pt), b = rdf(pt + 8), m;
      if (rd32(p + 0x1c) == 3) {
        float dx = rdf(p + 0x84) - (float)rd32(carp(0) + 0xc8);
        float dz = rdf(p + 0x8c) - (float)rd32(carp(0) + 0xd0);
        dx = fabsf(dx); dz = fabsf(dz);
        float d = !(dx >= dz) ? (float)((long double)dx * 0.5f + dz) : (float)((long double)dz * 0.5f + dx);
        float v = d / 275.0f;                                  /* 00546a70 */
        if (v > 3.0f) v = 3.0f;
        P103_PathK = 4.0f - v;
        m = P103_PathK;
      } else if (rd32(p + 0x1c) == 2) m = 0.7f;                /* 00546168 */
      else m = 0.4f;                                           /* 00546a6c */
      P100_PartBase[0] = (float)(((long double)s * b + (long double)c * a) * m + P100_PartBase[0]);
      P100_PartBase[2] = (float)(((long double)c * b - (long double)s * a) * m + P100_PartBase[2]);
    }
    wrf(p + 0x84, P100_PartBase[0]);
    memcpy(p + 0x88, &P100_PartBase[1], 4);
    wrf(p + 0x8c, P100_PartBase[2]);
  }
#ifndef RE_HOOK_BUILD
  if (n > 0)
#endif
  if (n <= rd32(p + 0x34)) wr32(p + 0x34, rd32(p + 0x34) % n);
  if ((fl & 0x80) != 0) {
    int32_t t = rd32(p + 0x40);
    wr32(p + 0x40, t - 1);
    if (t == 0) ResetObjState_00514E99(p);
  }
}
