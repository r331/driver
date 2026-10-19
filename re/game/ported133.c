/* v1.78: ported133 — см. ported133.h.
   004055e8 — обратная к 00406875 (P102_ConfigSnap): config.dat "rb" → P58_CfgHdr (8 байт), при подписи 0x93587031 —
     0x10c байт в P58_Cfg, сумма 0040682d = hdr[1] → 0x43 слова в переменные (все native-псевдонимы); джойстик (режим 2 —
     P36_SelectJoystick(cfg[0xc]), неудача → режим 0); раскладка P36_KeyCfg из P54_KeySrc[0..4] или [6..10]; ширина/высота
     режима из .data 0054b6c8 (0x1c на режим); громкости 0..1 (иначе 0.5), формат 8/16 бит, 22050/44100; 0 — P95_DefaultOptions.
   0049f6c7 — камера: вне режима 00bdfa54 — P59_SetupCamera; режим 01137324: 0 — 0049d84a, 1 — свободная P128_FreeCam(01136c48)
     и высота над дорогой − 512, 2 — P61_SetupCamN(01136c4c), 6 — 0049c99c, 7 — 004f0f90, 8 — 0049e47b, 9 — 0049e7a8, 0x10/0x11 — 0049e16c;
     дальше 2024999936 (.data 00546128) от игрока по XZ — сброс в режим 0.
   004cf84c — для событий с флагом 2 — объекты списка +0x1c (следующий +0x58), без флага 4: матрица из углов (+0x12 — с обратным
     знаком), видимость P83_BoxVis(радиус модели +0xc), флаг 0x20 — наклон по дороге (P100_RoadHeight на концах ±r), дым у
     модели 3 в уровне 0, вид = позиция − камера, страница текстуры +0x40, P84_DrawModel(режим 0/1/2 по видимости 1/2/иное).
   004f2360 — зеркало: стек скрипта 00d16500, сцена 00b31efc, окно ширина×4/11 (.data 005636d0), высота×2/15 (005636d4),
     машина развёрнута на 0x800 (+0xea) и наклон −(+0xe8), полный проход отрисовки как 004d4fc5 с P84_Mirror = 1, рамка 0x111111.
   004967d2 — такт трафика: обработчики .data 00551308 (0 — 00493f95, 1 — 00493f9a, 2 — 00493ff7, 3 — 004943dc, 4 — 004a7fec,
     5 — 00494620, 6 — 00494678, 7 — 004946d0), смещение машины по курсу ×0x1c2, удаление дальше 0x2d9 клеток², посадка на
     дорогу ближе, клетка записи +0x48/+0x4c, скорость, полосы, копы; подсчёт свободных/занятых, P75_TrafficFill.
   Отступления native: файл config.dat читается через g_fread с проверкой длины; NULL-указатели (P59_CarsTab, модель, стек
     скрипта, P98_GrD40) пропускаются; тип записи трафика > 7 — без обработчика; число записей ≤ 0x40; в native зеркало
     возвращает прежние P66_Scene/G2_ScriptStack (оригинал пишет 00b31f00 и 00d14f00). */
#include "ported150.h"
#include "ported133.h"
#include "ported142.h"
#include <string.h>
#include <math.h>
#include "crt.h"
#include "reptr.h"
#include "cartab.h"
#include "unported.h"
#include "globalsets.h"
#include "menustate.h"
#include "noop.h"
#include "smallfuncs.h"
#include "smallfuncs2.h"
#include "uihandlers3.h"
#include "uihandlers4.h"
#include "widgets.h"
#include "ported4.h"
#include "ported5.h"
#include "ported6.h"
#include "ported7.h"
#include "ported10.h"
#include "ported11.h"
#include "ported12.h"
#include "ported13.h"
#include "ported14.h"
#include "ported19.h"
#include "ported21.h"
#include "ported25.h"
#include "ported26.h"
#include "ported28.h"
#include "ported29.h"
#include "ported35.h"
#include "ported36.h"
#include "ported43.h"
#include "ported44.h"
#include "ported47.h"
#include "ported48.h"
#include "ported51.h"
#include "ported54.h"
#include "ported55.h"
#include "ported56.h"
#include "ported58.h"
#include "ported59.h"
#include "ported60.h"
#include "ported61.h"
#include "ported62.h"
#include "ported63.h"
#include "ported66.h"
#include "ported68.h"
#include "ported69.h"
#include "ported74.h"
#include "ported75.h"
#include "ported77.h"
#include "ported82.h"
#include "ported83.h"
#include "ported84.h"
#include "ported88.h"
#include "ported89.h"
#include "ported95.h"
#include "ported98.h"
#include "ported99.h"
#include "ported100.h"
#include "ported101.h"
#include "ported102.h"
#include "ported103.h"
#include "ported106.h"
#include "ported108.h"
#include "ported109.h"
#include "ported110.h"
#include "ported113.h"
#include "ported114.h"
#include "ported116.h"
#include "ported119.h"
#include "ported121.h"
#include "ported123.h"
#include "ported127.h"
#include "ported128.h"
#include "ported131.h"
#include "ported132.h"
#include "ported134.h"

#ifndef RE_HOOK_BUILD
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P133_1137320")
#undef P133_1137320
#pragma push_macro("P133_1137320") /*gvi*/
#undef P133_1137320 /*gvi*/
int32_t P133_1137320;
#pragma pop_macro("P133_1137320") /*gvi*/
#pragma pop_macro("P133_1137320")
#endif
#endif

static float u2f(uint32_t u) { float f; memcpy(&f, &u, 4); return f; }
#include "memrw.h"
static int16_t rd16(const uint8_t *p) { int16_t v; memcpy(&v, p, 2); return v; }
static void wr16(uint8_t *p, int16_t v) { memcpy(p, &v, 2); }
static int32_t rnd(float f) { P11_00ba52d0 = (int32_t)lrintf(f); return P11_00ba52d0; }
static void grd40(int32_t v) { if (P98_GrD40) P98_GrD40(v); }

/* ---- 004055e8 ---- */
int32_t P133_LoadConfig(void) {
  if (P58_CfgOn == 0 || P58_CfgLock != 0) return 1;
  void *f = g_fopen("config.dat", "rb");
  if (f == NULL) { P95_DefaultOptions(); return 0; }
  P58_CfgHdr[0] = 0; P58_CfgHdr[1] = 0;
  g_fread(P58_CfgHdr, 1, 8, f);
  if (P58_CfgHdr[0] != 0x93587031u) { g_fclose(f); P95_DefaultOptions(); return 0; }
  g_fread(P58_Cfg, 1, 0x10c, f);
  g_fclose(f);
  if (SumBytes(P58_Cfg, 0x10c) != (int32_t)P58_CfgHdr[1]) { P95_DefaultOptions(); return 0; }
  uint32_t c[0x43]; memcpy(c, P58_Cfg, sizeof c);
  P55_V57B6FC = (int32_t)c[0];
  P95_ModeSel = (int32_t)c[1];
  P35_ReqBpp = (int32_t)c[2];
  P35_InputMode = (uint8_t)c[3];
  Q00B87EF0 = (int32_t)c[0x22];
  memcpy(&P54_KeySrc[6], &c[4], 5 * 4);                          /* 0054b7c0 */
  P54_Keys3[0] = c[9]; P54_Keys3[1] = c[10]; P54_Keys3[2] = c[11];
  if (P35_InputMode == 2) {
    if (P36_SelectJoystick((int32_t)c[0xc]) == 0) P35_InputMode = 0;
    else {
      if (Q00B31E2C == 0) Q00B87EF0 = 0;
      memcpy(P36_KeyCfg, &P54_KeySrc[0], 5 * 4);
    }
  }
  if (P35_InputMode == 0) memcpy(P36_KeyCfg, &P54_KeySrc[6], 5 * 4);
  P13_00d11880 = (int32_t)c[0xd]; G6_00D11880 = (int32_t)c[0xd];
  MenuVar55384C = (int32_t)c[0xe]; P13_0055384c = (int32_t)c[0xe]; G0055384C = (int32_t)c[0xe];
  MenuVar553850 = (int32_t)c[0xf]; P13_00553850 = (int32_t)c[0xf]; G00553850 = (int32_t)c[0xf];
  MenuVarB31F04 = (int32_t)c[0x10]; P13_00b31f04 = (int32_t)c[0x10]; G00B31F04 = (int32_t)c[0x10];
  P13_00575ebc = (int32_t)c[0x11]; G6_00575EBC = (int32_t)c[0x11];
  P13_00575ec0 = (int32_t)c[0x12]; G6_00575EC0 = (int32_t)c[0x12];
  MenuVar55C974 = (int32_t)c[0x13]; P13_0055c974 = (int32_t)c[0x13]; P28_ShineFlag = (int32_t)c[0x13]; G0055C974 = (int32_t)c[0x13];
  MenuVar575F30 = (int32_t)c[0x14]; P13_00575f30 = (int32_t)c[0x14]; G00575F30 = (int32_t)c[0x14];
  MenuVarB201DC = (int32_t)c[0x15]; P13_00b201dc = (int32_t)c[0x15]; G00B201DC = (int32_t)c[0x15];
  MenuVar575EE8 = (int32_t)c[0x16]; P13_00575ee8 = (int32_t)c[0x16]; G00575EE8 = (int32_t)c[0x16];
  MenuVarD118C8 = (int32_t)c[0x17]; P13_00d118c8 = (int32_t)c[0x17]; G00D118C8 = (int32_t)c[0x17];
  G8_00575F40 = (int32_t)c[0x18]; G00575F40 = (int32_t)c[0x18];
  Q00B87E90 = (int32_t)c[0x19];
  Q00B87E94 = (int32_t)c[0x1a];
  WF00575F14 = u2f(c[0x1b]);
  WF00575F18 = u2f(c[0x1c]);
  MenuState575EF0 = (int32_t)c[0x1d]; P19_Level = (int32_t)c[0x1d]; P58_Page = (int32_t)c[0x1d]; G00575EF0 = (int32_t)c[0x1d];
  P11_01270c24 = u2f(c[0x1e]); P13_01270c24 = (int32_t)c[0x1e]; Q01270C24 = u2f(c[0x1e]); P59_CamF1 = u2f(c[0x1e]);
  P11_0125f3f8 = u2f(c[0x1f]); P13_0125f3f8 = (int32_t)c[0x1f]; Q0125F3F8 = u2f(c[0x1f]);
  P11_0125f3e0 = u2f(c[0x20]); P19_Scale = u2f(c[0x20]);
  MenuVar5759A4 = (int32_t)c[0x21]; P13_005759a4 = (int32_t)c[0x21]; P60_PartLimit = (int32_t)c[0x21]; G005759A4 = (int32_t)c[0x21];
  P13_00575ef4 = (int32_t)c[0x23]; G6_00575EF4 = (int32_t)c[0x23];
  P13_00b87e74 = (int32_t)c[0x2e]; G6_00B87E74 = (int32_t)c[0x2e];
  MenuVar575F3C = (int32_t)c[0x24]; P13_00575f3c = (int32_t)c[0x24]; G00575F3C = (int32_t)c[0x24];
  P13_00575f20 = (int32_t)c[0x25]; G6_00575F20 = (int32_t)c[0x25];
  MenuVar575F44 = (int32_t)c[0x26]; P13_00575f44 = (int32_t)c[0x26]; G00575F44 = (int32_t)c[0x26];
  G00575F48 = (int32_t)c[0x27];
  G00575F24 = (int32_t)c[0x28];
  WI00B87E2C = (int32_t)c[0x29];
  P21_FrameFlagB = (int32_t)c[0x2a]; G6_00575F34 = (int32_t)c[0x2a];
  P21_FrameFlagA = (int32_t)c[0x2b]; G6_00575F38 = (int32_t)c[0x2b];
  P21_FrameMin = (int32_t)c[0x2c]; G6_00575EEC = (int32_t)c[0x2c];
  MenuVar575EF8 = (int32_t)c[0x2d]; P11_00575ef8 = (int32_t)c[0x2d]; G00575EF8 = (int32_t)c[0x2d];
  G6_00575F00 = (int32_t)c[0x2f];
  G6_00575F04 = (int32_t)c[0x30];
  G6_00B87E50 = (int32_t)c[0x31];
  memcpy(P102_BDF9E0, &c[0x32], 0xb * 4);
  P13_00575ee4 = (int32_t)c[0x3d]; P21_EntryCount = (int32_t)c[0x3d]; P51_TrafficN = (int32_t)c[0x3d];
  G8_00575EE4 = (int32_t)c[0x3d]; G2_00575EE4 = (int32_t)c[0x3d]; WI00575EE4 = (int32_t)c[0x3d];
  P12_00b87e58 = (int32_t)c[0x3e];
  P12_00b87e5c = (int32_t)c[0x3f];
  P12_00575f50 = (int32_t)c[0x40];
  P102_57B6A8 = (int32_t)c[0x41];
  P102_57B6F8 = (int32_t)c[0x42];
  {
    uint32_t sel = (uint32_t)P95_ModeSel;
#ifndef RE_HOOK_BUILD
    if (sel >= 8) sel = 0;                                       /* native: 8 записей .data 0054b6c8 */
#endif
    P68_ModeW = (int32_t)P95_ModeTab[sel * 7 + 0]; P68_ModeH = (int32_t)P95_ModeTab[sel * 7 + 1];
  }
  if (WF00575F14 < 0.0f || 1.0f < WF00575F14) WF00575F14 = 0.5f;   /* .data 00546024 = 0, 00546020 = 1 */
  if (WF00575F18 < 0.0f || 1.0f < WF00575F18) WF00575F18 = 0.5f;
  if (G6_00575F00 != 8 && G6_00575F00 != 0x10) G6_00575F00 = 8;
  if (G6_00575F04 != 0x5622 && G6_00575F04 != 0xac44) G6_00575F04 = 0x5622;
  P48_SetMasterVolume(WF00575F14);
  P25_CDSetVolume((uint32_t)rnd(WF00575F18 * 65535.0f));      /* .data 0054601c */
  SoundSetFormat005235D3(G6_00575F00, G6_00575F04);
  SoundSetVolA005235F2(G6_00B87E50);
  return 1;
}

/* ---- 0049f6c7 ---- */
static void cam_y(float v) { P44_CamY = v; P59_VY = v; }
static void set_mode(int32_t m) { P59_Mode1137324 = (uint8_t)m; G2_01137324 = m; }
void P133_CamUpdate(int32_t lock) {
  if ((MenuOptBDFA54 | G00BDFA54) != 0 && P29_Mode == 0) { P59_SetupCamera(); return; }
  P128_FreeCamLock = lock;
  if (P98_C824A0 != 0) set_mode(7);
  if ((G6_00B5A778 == 0 || P29_Mode != 0) && lock == 0) {
    P133_1137320 = P98_FreeTurn; P61_Heading = (int16_t)((uint32_t)P98_FreeTurn >> 16);
    if (P36_Pad0 != 0) { cam_y(P44_CamY - P43_FadeDiv); P61_OffY = P61_OffY - P43_FadeDiv; }
    if (P36_Pad1 != 0) { cam_y(P44_CamY + P43_FadeDiv); P61_OffY = P61_OffY + P43_FadeDiv; }
  }
  if ((G6_00B87EA0 | P62_HudOff1) != 0 && P88_Mode575 == 0) {
    P60_Var1373C0 = 0; P43_ScaleA = 384.0f; P134_CamChase(0x41); return;
  }
  switch (P59_Mode1137324) {
  case 0: P60_Var1373C0 = 0; P43_ScaleA = 384.0f; P134_CamChase(P61_V10); break;
  case 1: {
    P60_Var1373C0 = 0; P43_ScaleA = 384.0f;
    P128_FreeCam(P61_V10);
    float cam[3] = { P44_CamX, P44_CamY, P44_CamZ };
    P61_OffY = (float)-P100_RoadHeightF(cam) - 512.0f;          /* .data 005460dc */
    P61_Dist8 = 1280.0f;
    break; }
  case 2: P60_Var1373C0 = 0; P43_ScaleA = 384.0f; P61_SetupCamN(P61_V10b); break;
  case 6: P99_FreeCamMove(); break;
  case 7: P134_CamCine(); break;
  case 8: P99_CamBehind(); break;
  case 9: P131_CamShake(); break;
  case 0x10: P134_CamTarget(-1); break;
  case 0x11: P134_CamTarget(P61_V10); break;
  default: break;
  }
  float dx = fabsf((float)P99_Cars[0].pos[0] - P44_CamX), dz = fabsf((float)P99_Cars[0].pos[2] - P44_CamZ);
  if (2024999936.0f < dz * dz + dx * dx) {
    set_mode(0); P61_OffY = -256.0f; P61_Dist8 = 1280.0f; P61_V18 = 0x800;
  }
}

/* ---- 004cf84c ---- */
static void set_ctx(uint8_t *c) { P10_ScriptCtx = c; S_00D1240C = c; }
void P133_EventModels(void) {
  float zero[4] = { 0, 0, 0, 0 };
  int32_t page = -1;
  for (S_00D12410 = (uint16_t *)re_ptr((uint32_t)G00D12408); S_00D12410 != NULL;
       S_00D12410 = (uint16_t *)re_rd_ptr((uint8_t *)S_00D12410 + 0x20)) {
    uint8_t *ev = (uint8_t *)S_00D12410;
    if ((rd16(ev) & 2) == 0) continue;
    for (set_ctx((uint8_t *)re_rd_ptr(ev + 0x1c)); P10_ScriptCtx != NULL; set_ctx((uint8_t *)re_rd_ptr(P10_ScriptCtx + 0x58))) {
      uint8_t *o = P10_ScriptCtx;
      if ((rd32(o + 0x48) & 4) != 0) continue;
      float m[16], pos[3]; int16_t ang[3];
      memcpy(pos, o, sizeof pos);
      wr16(o + 0x12, (int16_t)(-rd16(o + 0x12) & 0xfff));
      memcpy(ang, o + 0x10, sizeof ang);
      P43_EulerMatrix(m, ang);
      wr16(o + 0x12, (int16_t)(-rd16(o + 0x12) & 0xfff));
      uint32_t idx = (uint16_t)rd16(o + 0x4a);
#ifndef RE_HOOK_BUILD
      if (idx >= sizeof(P28_EventModels) / sizeof(P28_EventModels[0])) continue;
#endif
      uint32_t mdl = P28_EventModels[idx];
      const uint8_t *mp = (const uint8_t *)re_ptr(mdl);
      if (mp == NULL) continue;
      float r = rdf(mp + 0xc);
      int32_t vis = P83_BoxVis(pos, r);
      if (vis == 0) continue;
      if ((rd32(o + 0x48) & 0x20) != 0) {
        float a[3] = { -r, 0, 0 }, b[3] = { r, 0, 0 };
        P44_MatPtr = m;
        P44_Xform(a); P44_Xform(b);
        for (int k = 0; k < 3; k++) { a[k] += pos[k]; b[k] += pos[k]; }
        int32_t e[3], g[3];
        e[0] = rnd(a[0]); e[2] = rnd(a[2]); g[0] = rnd(b[0]); g[2] = rnd(b[2]); e[1] = 0; g[1] = 0;
        e[1] = P100_RoadHeight(e);
        g[1] = P100_RoadHeight(g);
        P44_RotZ(m, P44_Atan2(g[0] - e[0], g[1] - e[1]));
      }
      if (D_00b87e30 == 0 && rd16(o + 0x4a) == 3) {
        static const float off[2][3] = { { -1400.0f, 140.0f, 20.0f }, { -1340.0f, 140.0f, -20.0f } };
        float m2[16]; int16_t a2[3] = { 0, (int16_t)(rd16(o + 0x12) & 0xfff), 0 };
        int32_t n = (int32_t)(N14_Rand() & 0x1f) + 0x46;
        P43_EulerMatrix(m2, a2);
        P44_MatPtr = m2;
        for (int k = 0; k < 2; k++) {
          float v[3] = { off[k][0], off[k][1], off[k][2] };
          P44_Xform(v);
          if (k == 1) n = (int32_t)(N14_Rand() & 0x1f) + 0x46;
          float p[3] = { v[0] + pos[0], v[1] + pos[1], v[2] + pos[2] };
          P132_Smoke(p, zero, n * 5, 0x78, 8, 0x78, 2, 0.2f, 0);
        }
      }
      P44_MatPtr = (float *)(void *)&P44_ViewMatT;
      float rel[3] = { pos[0] - P44_CamX, pos[1] - P44_CamY, pos[2] - P44_CamZ };
      P44_Xform(rel);
      int16_t pg = rd16(o + 0x40);
      if (pg != page && pg != -1) { page = pg; P12_Fn00426580(page); }
      P84_DrawModel(mdl, m, rel, vis == 1 ? 0 : (vis == 2 ? 1 : 2));
    }
  }
}

/* ---- 004f2360 ---- */
#ifndef RE_HOOK_BUILD
static int32_t P133_MirrorStack[0x1600 / 4];                    /* 00d16500 (стек скрипта зеркала) */
#endif
static void scr_w(int32_t v) { P19_ScrW = v; G6_01270C28 = v; P11_01270c28 = u2f((uint32_t)v); }
static void scr_h(int32_t v) { P19_ScrH = v; G6_0125F3F0 = v; }
void P133_MirrorDraw(void) {
  float cx = P44_CamX, cy = P44_CamY, cz = P44_CamZ; uint32_t cw = P98_CamW;
  int32_t w0 = P19_ScrW, h0 = P19_ScrH; float plane = P11_01270c24;
  if ((P62_HudOff2 == 0 || (P59_S4654 != 3 && P59_S4654 != 2)) && P98_C824A0 == 0 && P29_Mode == 0 &&
      P14_00b87ee4 == 0 && P98_MrkOff == 0) {
    GlobalSet004AADDF();
#ifdef RE_HOOK_BUILD
    G2_ScriptStack = (int32_t *)(uintptr_t)0x00d16500u;
#else
    int32_t *st0 = G2_ScriptStack; uint32_t sc0 = P66_Scene;
    G2_ScriptStack = P133_MirrorStack;
#endif
    P66_Scene = (uint32_t)P11_00b31efc;
    P77_CameraPlane(rnd(P11_0125f3f8));
    NegateCamZ004EAF8D();
    P84_Mirror = 1;
    float fw = (float)w0, fh = (float)h0 * 0.13333334f;         /* .data 005636d4 */
    int32_t hw = w0 >> 1, hh = h0 >> 1;
    scr_w(rnd(fw * 0.36363637f));                               /* .data 005636d0 */
    scr_h(rnd(fh));
    int32_t y = rnd(((float)hh - fh * 0.5f) + ((fh * 0.5f + 9.0f) - (float)hh) * P19_Scale);
    int32_t x = rnd((float)hw - fw * 0.36363637f * 0.5f);
    P110_ViewSetup(x, y, 2);
    P44_XformTag++; P47_SwapCnt++;
    P99_Cars[0].ang[0] = (int16_t)(-P99_Cars[0].ang[0] & 0xfff);
    P99_Cars[0].ang[1] = (int16_t)((P99_Cars[0].ang[1] + 0x800) & 0xfff);
    P61_SetupCamN(0);
    P99_Cars[0].ang[0] = (int16_t)(-P99_Cars[0].ang[0] & 0xfff);
    P99_Cars[0].ang[1] = (int16_t)((P99_Cars[0].ang[1] + 0x800) & 0xfff);
    P82_FrustumSetup3D();
    P89_DrawMap(1);
    NoopFn004d1a89();
    P109_DropsDraw(0);
    if (P26_FxD != 0) grd40(0);
    P116_SkidsA();
    if ((G6_00B87EAC | G8_00B87EAC) != 0 || (P58_SB87EB0 | G6_00B87EB0 | G8_00B87EB0) != 0) P116_SkidsB();
    if (P26_FxD != 0) grd40(2);
    Reset0042D2B0();
    P128_TrafficDraw();
    P150_FlushTris();
    P133_EventModels();
    P114_PartModels();
    P98_IconFlush();
    P123_ObjShadows();
    int32_t e1 = MenuVar575EE8, e2 = P13_00575ee8, e3 = G00575EE8;
    if (P26_FxD != 0) { MenuVar575EE8 = 0; P13_00575ee8 = 0; G00575EE8 = 0; }
    P55_RunTableA();
    if (P26_FxD != 0) { MenuVar575EE8 = e1; P13_00575ee8 = e2; G00575EE8 = e3; }
    P106_SkyModels();
    if (P26_FxD != 0) grd40(0);
    if (P26_FxC != 0) P110_ScriptSprites();
    if (P26_FxD != 0) grd40(2);
    if (P95_BDFA14 != 0) P113_Heli(1);
    P69_SceneFrame();
    P123_CarGlows();
    P55_RunTableB();
    P109_DropsDraw(1);
    P133_CamUpdate(1);
    int32_t bx = rnd(P110_ClipX0), by = rnd(P110_ClipY0);
    int32_t bw = rnd(P110_ClipX1 - P110_ClipX0), bh = rnd(P110_ClipY1 - P110_ClipY0);
    scr_h(h0); scr_w(w0);
    P110_ViewSetup(0, 0, 0);
    int32_t lw = (0.5f <= P19_Scale) ? 2 : 1;                   /* .data 00546068 */
    P108_FillRect((float)(bx - lw), (float)(by - lw), (float)(bw + lw * 2), (float)lw, 0x111111);
    P108_FillRect((float)(bx - lw), (float)(by + bh), (float)(bw + lw * 2), (float)lw, 0x111111);
    P108_FillRect((float)(bx - lw), (float)by, (float)lw, (float)bh, 0x111111);
    P108_FillRect((float)(bx + bw), (float)by, (float)lw, (float)bh, 0x111111);
    P84_Mirror = 0;
    P77_CameraPlane(rnd(plane));
#ifdef RE_HOOK_BUILD
    P66_Scene = (uint32_t)(uintptr_t)P100_Mirror;
    G2_ScriptStack = (int32_t *)(uintptr_t)0x00d14f00u;
#else
    P66_Scene = sc0; G2_ScriptStack = st0;
#endif
  }
  P44_CamX = cx; P59_VX = cx; P44_CamY = cy; P59_VY = cy; P44_CamZ = cz; P59_VZ = cz; P98_CamW = cw; P121_CamW = cw;
}

/* ---- 004967d2 ---- */
static void traffic_fn(uint8_t *r) {
  switch (r[1]) {                                               /* .data 00551308 */
  case 0: NoopFn00493f95(); break;
  case 1: P54_ObjTick(r); break;
  case 2: P103_TrafficTick(r); break;
  case 3: P119_TrafficStep(r); break;
  case 4: P142_CopDrive(r); break;
  case 5: P134_TrafficHold(r); break;
  case 6: ActorStep00494678(r); break;
  case 7: NoopFn004946d0(); break;
  default: break;
  }
}
static int32_t far2(int32_t ax, int32_t az, int32_t bx, int32_t bz) {
  int32_t dx = ax - bx, dz = az - bz;
  if (dx < 0) dx = -dx;
  if (dz < 0) dz = -dz;
  int32_t a = rnd((float)dx * P63_Scale), b = rnd((float)dz * P63_Scale);
  return a * a + b * b;
}
static int32_t sin_step(uint32_t a) { return ((int32_t)P59_Sin[a & 0xfff] * 0x1c2) / 4096; }
void P133_TrafficTick(void) {
  uint8_t *car = P59_CarsTab, *rec = TrafficRecs;
  int32_t px, pz;
  int32_t eb0 = P58_SB87EB0 | G6_00B87EB0 | G8_00B87EB0, eac = G6_00B87EAC | G8_00B87EAC;
  if (eac == 0 && eb0 == 0) { px = P99_Cars[0].pos[0]; pz = P99_Cars[0].pos[2]; }
  else {
    P13_00575ee4 = 0x20; P21_EntryCount = 0x20; P51_TrafficN = 0x20; G8_00575EE4 = 0x20; G2_00575EE4 = 0x20; WI00575EE4 = 0x20;
    px = P99_Cars[0x41].pos[0]; pz = P99_Cars[0x41].pos[2];
  }
  rnd((float)(pz - 0x2ee) * P63_Scale);
  P102_ScanCells();
  int32_t n = P51_TrafficN;
  if (eb0 != 0 && P75_E4 == 0) {
    if (0x16b < far2(P99_Cars[0].pos[0], P99_Cars[0].pos[2], px, pz) && P100_1426FC == 0 && P100_143720 == 0) {
      P14_00c810c4 = 0xff0; P56_Blk84[1] = 0xff0;
      P14_00c810e8 = 3; P56_Blk84[10] = 3;
      P14_00c81100 = 0x96; P56_Blk84[16] = 0x96;
      P100_1426FC = 1;
      return;
    }
  }
  if ((G6_00B87EA0 | P62_HudOff1) != 0) return;
#ifndef RE_HOOK_BUILD
  if (car == NULL) return;
  if (n > 0x40) n = 0x40;
#endif
  for (int32_t i = 0; i < n; i++, rec += 0x54, car += 0x148) {
    uint32_t h = (uint32_t)rd32(car + 0x100);
    traffic_fn(rec);
    if (rec[1] == 0) continue;
    if (rec[1] != 1) {
      wr32(car + 200, rd32(car + 200) + sin_step(h));
      wr32(car + 0xd0, rd32(car + 0xd0) + sin_step(h + 0x400));
    }
    int32_t d = far2(rd32(car + 200), rd32(car + 0xd0), px, pz);
    if (rec[6] == 0) {
      if (0x2d9 < d) { if (eb0 == 0) P74_FreeTraffic(i); continue; }
    } else if (d < 0x2da && rec[0x14] == 0) P101_CarGround((p99_car_t *)(void *)car, rec);
#ifndef RE_HOOK_BUILD
    if (rec[0] >= P99_CARS_N - 1) continue;
#endif
    const uint8_t *oc = P59_CarsTab + (uint32_t)rec[0] * 0x148;
    wr32(rec + 0x48, rd32(oc + 200) + 0x2ee);
    wr32(rec + 0x4c, rd32(oc + 0xd0) - 0x2ee);
    wr32(rec + 0x48, rnd((float)rd32(rec + 0x48) * P63_Scale));
    wr32(rec + 0x4c, rnd((float)rd32(rec + 0x4c) * P63_Scale));
    if (rec[1] == 1 && rec[2] == 0 && rec[6] == 0) {
      if (99 < rec[10]) continue;
      rec[10]++;
    }
    if (rec[1] == 4) MenuAddItem004DC8B0(car, 0);
    else {
      wr32(rec + 0x38, rd32(car + 0x10c) < 1 ? -rd32(car + 0x110) : rd32(car + 0x110));
      if (i < 0x40) { P119_TrafficSpeed(rec, car); MenuAddItem004DC8B0(car, 0); }
      if (rec[1] == 2 && rec[2] != 1 && (P62_Frame & 1) != 0 && rd32(rec + 0x28) != -1) {
        if (rd32(rec + 0x18) < 0x4651 || rd32(rec + 0x40) != 0x7fffffff || rd32(rec + 0x44) != 0x7fffffff) P100_TrafficSlot(rec);
        else if (18000 < rd32(rec + 0x18)) P127_TrafficLane(rec);
      }
    }
    if (rec[5] != 0) P121_CopSync(rec);
  }
  P75_4288 = 0; P75_43D0 = 0;
  rec = TrafficRecs;
  for (int32_t i = 0; i < 0x40; i++, rec += 0x54) { if (rec[1] == 0) P75_43D0++; else P75_4288++; }
  if (eb0 != 0) G2_01143600 = P75_4288;
  P75_TrafficFill();
}
