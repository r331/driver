/* v1.77: ported132 — см. ported132.h.
   00417b80 — цикл экрана меню: 004055e8, масштаб 0125f3e0 = 1.0 на время цикла (оба native-псевдонима), tab → P100_ItemTab,
     004182b0, значки LEFTARRO/RIGHTARR (uint32-адреса), пункт 4, затем Call00522323/опрос/P59_MenuKeys (−1 — выход),
     отложенное действие P58_MenuFn (re_fn; 1 — выход), кадр P66_ScreenFrame(0054e4d0, 00417fff); → P67_Res51C.
   004d4bfb — такт логики: режиссёр, пауза (G6_00B5A778 — короткий путь), клавиши записи P100_RecKeys, таймер 00c81100,
     камера, погода, обратный отсчёт 00d11928, машины/звуки, P62_Frame++ (вне режима облёта).
   004d4fc5 — кадр отрисовки: при S_00B5A77C = 0 весь мир (P26_FxD — флаг ночного режима, гасится без 00575f3c),
     затем меню паузы, строки отладки (Felony rating …, таблица 0055fdd8 — 11 строк), часы/FPS, буфер.
   004b9287 — запись дыма P95_ObjA (0x78): позиция ± (rand&0xf)−7, скорость (±(rand&3)−1 при jitter), +0x34 f, +0x50 a,
     +0x54 b, +0x60 ±step, +0x58 c, +0x64 |(b−a)/step|, +0x66 половина, +0x68 флаги 0x80006/0x100006, +0x5c (c<<4)/+0x64.
   004ca135 — огни: молния P130_Lightning (P26_FxB), мигание G00D14EEC, фары игрока (P99_Cars[0] или [0x41]),
     мигалка в режиме 10, мигалки машин трафика, огни сцены 00b87e98, огни записей 012083c0 (0x1c: xyz, радиус, rgb float).
   0049f20a — .FBD: "DRIVER Fly-By Text-file", ключи "Control Point %d" (Position/Rotation/Zoom/Frame, 10 полей),
     флаг +0x28 |= 1, последний ключ дублируется, P99_CamLast = последний + 1.
   Отступления native: строки читаются в локальный буфер (оригинал пишет в буфер имени), '\r' срезается, файл
   закрывается и при ошибке, индекс ключа 0..0x3e; деление на 0 в 004b9287 — 1; NULL-указатели функций пропускаются. */
#include "aspect.h"
#include "drawdist.h"
#include "../platform/plat.h"
#include "ported150.h"
#include "ported140.h"
#include "ported142.h"
#include "ported132.h"
#include "ported133.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "ported88.h"
#include "ported87.h"
#include "ported80.h"
#include "ported21.h"
#include "ported54.h"
#include "ported59.h"
#include "ported44.h"
#include <math.h>
#include "crt.h"
#include "reptr.h"
#include "cartab.h"
#include "unported.h"
#include "ported137.h"
#include "director.h"
#include "globalsets.h"
#include "menustate.h"
#include "noop.h"
#include "ported100.h"
#include "ported101.h"
#include "ported102.h"
#include "ported103.h"
#include "ported106.h"
#include "ported109.h"
#include "ported11.h"
#include "ported110.h"
#include "ported112.h"
#include "ported113.h"
#include "ported114.h"
#include "ported115.h"
#include "ported116.h"
#include "ported117.h"
#include "ported119.h"
#include "ported12.h"
#include "ported120.h"
#include "ported121.h"
#include "ported123.h"
#include "ported124.h"
#include "ported34.h"
#include "ported125.h"
#include "ported126.h"
#include "ported127.h"
#include "ported128.h"
#include "ported13.h"
#include "ported130.h"
#include "ported131.h"
#include "ported14.h"
#include "ported15.h"
#include "ported18.h"
#include "ported19.h"
#include "ported21.h"
#include "ported26.h"
#include "ported29.h"
#include "ported31.h"
#include "ported35.h"
#include "ported36.h"
#include "ported4.h"
#include "ported42.h"
#include "ported44.h"
#include "ported45.h"
#include "ported47.h"
#include "ported52.h"
#include "ported55.h"
#include "ported56.h"
#include "ported58.h"
#include "ported59.h"
#include "ported6.h"
#include "ported60.h"
#include "ported61.h"
#include "ported62.h"
#include "ported66.h"
#include "ported67.h"
#include "ported69.h"
#include "ported7.h"
#include "ported74.h"
#include "ported75.h"
#include "ported76.h"
#include "ported82.h"
#include "ported89.h"
#include "ported93.h"
#include "ported95.h"
#include "ported96.h"
#include "ported97.h"
#include "ported98.h"
#include "ported99.h"
#include "smallfuncs.h"
#include "smallfuncs2.h"
#include "uihandlers2.h"
#include "uihandlers3.h"
#include "uihandlers4.h"
#include "ported143.h"
#include "redbg.h"

static void wrf(uint8_t *p, float v) { memcpy(p, &v, 4); }
static float rdf(const uint8_t *p) { float v; memcpy(&v, p, 4); return v; }
static void wr32(uint8_t *p, int32_t v) { memcpy(p, &v, 4); }
static int32_t rd32(const uint8_t *p) { int32_t v; memcpy(&v, p, 4); return v; }
static void wr16(uint8_t *p, uint16_t v) { memcpy(p, &v, 2); }
static uint16_t rd16(const uint8_t *p) { uint16_t v; memcpy(&v, p, 2); return v; }

#ifndef RE_HOOK_BUILD
int plat_frame_no(void);   /* v2.29: номер показанного кадра — для журналов отладки */
#endif
#ifndef RE_HOOK_BUILD
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P132_B87EC8")
#undef P132_B87EC8
#pragma push_macro("P132_B87EC8") /*gvi*/
#undef P132_B87EC8 /*gvi*/
int32_t P132_B87EC8;
#pragma pop_macro("P132_B87EC8") /*gvi*/
#pragma pop_macro("P132_B87EC8")
#endif
#endif


/* ---- 00417b80 ---- */
int32_t P132_MenuLoop(uint32_t tab) {
  P133_LoadConfig();
  float sv = P19_Scale;
  P100_ItemTab = tab;
  P59_MenuLock = 0; G005FEA54 = 0;
  P19_Scale = 1.0f; P11_0125f3e0 = 1.0f;
  P110_ViewSetup(0, 0, 0);
  P58_MenuFn = 0;
  P124_MotelInit();
  P97_IconL = (int32_t)re_addr(P93_FindIcon("LEFTARRO"));
  P97_IconR = (int32_t)re_addr(P93_FindIcon("RIGHTARR"));
  P45_Pick = 4; P58_MenuSel = 4; G6_005FED9C = 4;
  Ui0041A1EC(9);
  P19_Cur = 0.0f;
  Ui004184DE(0x3f800000);
  P45_PickColor();
  Ui00418119(4);
  P67_Res51C = -1;
  P21_FrameTicks();
  for (;;) {
    Call00522323();
    P36_PollInput();
    if (P59_MenuKeys() == -1) break;
#ifndef RE_HOOK_BUILD
    { static int k; const char *e = getenv("RE_MOTELDBG");   /* v2.12: отладка меню мотеля */
      if (e && ((k++ % (atoi(e) > 0 ? atoi(e) : 50)) == 0 || P34_Keys[0x1c] || P34_Keys[0xcd]))
        fprintf(stderr, "[motel] keys 1c=%02x/%02x sel %d fn %08x idx %d feda0 %d/%d nokey %d lock %d\n", P34_Keys[0x1c], P34_KeysPrev[0x1c], (int)P58_MenuSel, (unsigned)P58_MenuFn,
                (int)P58_MenuIdx, (int)D_005feda0, (int)UiVar005FEDA0, (int)P59_NoKeyFlag, (int)P59_MenuLock); }
#endif
    if (P58_MenuFn != 0 && (D_005feda0 | P59_NoKeyFlag | UiVar005FEDA0) == 0) {
      re_fn_t fn = re_fn((uint32_t)P58_MenuFn);
      int32_t r = fn ? ((int32_t (*)(void))fn)() : 0;
      if (r == 1) break;
      Ui00418119(P58_MenuIdx);
      P58_MenuFn = 0;
    }
    P66_ScreenFrame(0x0054e4d0u, 0x00417fffu);
  }
  ShutdownAudio004183A3();
  P19_Scale = sv; P11_0125f3e0 = sv;
  return P67_Res51C;
}

/* ---- 004d4bfb ---- */
void P132_GameLogic(void) {
  P18_ClearFlag();
  P36_PollInput();
  if (P14_00b87ee4 == 0) {
    if (P62_Frame > 1) P126_DebugKeys(0);
    P124_HandleDirector();
  }
  if (G6_00B5A778 != 0) {
    P66_Scene = 0x00cb8f20u;
    P133_CamUpdate(0);
    P82_FrustumSetup3D();
    P89_DrawMap(0);
    P12_Fn0050229C();
    P96_ReplayScript();
    P115_SndUpdate();
    P12_Fn0050E963();
    return;
  }
  int32_t hud1 = G6_00B87EA0 | P62_HudOff1;

  if ((P14_00d118a8 | G2_00D118A8) == 0 && (hud1 != 0 || P36_PadMode != 2)) {
    uint32_t k = (uint32_t)P100_RecKeys; P36_GetPadButtons(&k); P100_RecKeys = (int32_t)k;
  }
  if ((P14_00d118a8 | G2_00D118A8) != 0 || P100_143720 != 0 || P100_1426FC != 0 || P75_E4 != 0) {
    P100_RecKeys = 0x20;
    if (P97_D078CC >= 1) P100_RecKeys = 0x21;
    else if (P97_D078CC < 0) P100_RecKeys = 0x22;
  }
  P66_Scene = 0x00cb8f20u;
  G6_00D0DDC0 = 0;
#ifndef RE_HOOK_BUILD
  { /* v2.29: RE_MISSDBG=1 — отсчёт конца миссии 00c81100 (каждые 25 кадров) и ожидание речи 004d6209 */
    static int dbg = -1; if (dbg < 0) dbg = getenv("RE_MISSDBG") != NULL;
    if (dbg && P14_00c81100 != 0 && (P14_00c81100 % 25) == 1)
      fprintf(stderr, "[end] w=%d f=%d t=%d e8=%d c4=%x hud2=%d речь=%d\n", plat_frame_no(), (int)P62_Frame, (int)P14_00c81100, (int)P14_00c810e8,
              (unsigned)P14_00c810c4, (int)P62_HudOff2, (int)P42_ActionBound()); }
#endif
  if (P14_00c81100 != 0) {
    P14_00c81100--;
    if (P14_00c81100 == 0) {
      if (P62_HudOff2 != 0 && P42_ActionBound() != 0) P14_00c81100 = 0x32;
      else {
        SetLatchValue0050E940(1);
#ifndef RE_HOOK_BUILD
        { /* v2.29: RE_MISSDBG — итог миссии (00c810e8: 0 — успех, 2 — провал, 3 — цель потеряна (004f5012/004d4f5c)); RE_END_EXIT=N — выход через N кадров окна (снимок итога) */
          extern void plat_exit_after(int n); const char *e = getenv("RE_END_EXIT");
          if (getenv("RE_MISSDBG")) fprintf(stderr, "[end] w=%d f=%d итог миссии: %s (e8=%d c4=%x)\n", plat_frame_no(), (int)P62_Frame,
                                            P14_00c810e8 == 0 ? "успех" : P14_00c810e8 == 3 ? "ПРОВАЛ (цель потеряна)" : "ПРОВАЛ", (int)P14_00c810e8, (unsigned)P14_00c810c4);
          /* v2.30: RE_AUTOCONT="кадр:клавиша,…" — после успеха нажать (кадры от итога; Continue → следующая подмиссия/мотель),
             RE_CHAIN=N — так пройти N итогов подряд; RE_END_EXIT срабатывает на провале или на N-м итоге */
          static int nres = 0, lastw = -1; const char *ac = getenv("RE_AUTOCONT"), *ch = getenv("RE_CHAIN"); if (plat_frame_no() != lastw) nres++; lastw = plat_frame_no();
          if (ac && P14_00c810e8 == 0 && nres < (ch ? atoi(ch) : 1)) {
            extern int plat_keys_push(int rel, const char *name); char b[512]; snprintf(b, sizeof b, "%s", ac);
            for (char *t = strtok(b, ","); t; t = strtok(NULL, ",")) { char *c = strchr(t, ':'); if (c) { *c = 0; plat_keys_push(atoi(t), c + 1); } }
            fprintf(stderr, "[end] итог %d — RE_AUTOCONT\n", nres);
          } else if (e) plat_exit_after(atoi(e)); }
#endif
      }
    }
  }
  P127_SpawnTick(0);
  if (P14_00b87ee4 == 0) P133_CamUpdate(0); else P99_CamScriptStep();
  P82_FrustumSetup3D();
  if (P12_00b87ef8 != 0) Inc0B1FFBC();
  P89_DrawMap(0);
  if (P14_00b202d8 != 0) P103_Dawn();
  if (P14_00b202dc != 0) P103_Dusk();
  P127_FarDebris();
  int32_t live = (P14_00b87ee4 == 0 || P131_Skip != 0);
  if (live) P112_ScriptTriggers();
  P101_Drips();
  if (P95_BDFA14 != 0) P113_Heli(0);
  if (P95_C818B8 != 0) P140_MrkFly();
  if (live) { Call004A2C08(); P106_PartTick(); P12_Fn0048EBC8(); }
  if (P26_FxC != 0) { P130_SnowSpawn(); P130_SnowStep(); }
  P103_D118E0 = (P103_D118E0 + 0x3c) & 0xfff;
  if (P95_D11920 != 0 && P14_00c810c4 != 0xff0) {
    G6_00D11928--;
    P61_V18 = (P61_V18 - 0x16) & 0xfff;
    P59_Mode1137324 = 0; G2_01137324 = 0;
    if (G6_00D11928 < 0) {
      P100_B87E24 = 100; P14_00c810c4 = 0xff0; P14_00c810e8 = 5;
      SetLatchValue0050E940(1);
    }
  }
  if (live) {
    P109_InputTick();
    if ((G6_00B87EA0 | P62_HudOff1) == 0) {
      P133_TrafficTick(); Update005012A3(); P112_ChaseTick(); P100_CarSounds(P97_D11980); P14_Fn0051BD9C();
    } else Update005012A3();
  }
  P127_PlayerSkid(0);
  if ((G6_00B87EAC | G8_00B87EAC) != 0 || (P58_SB87EB0 | G6_00B87EB0 | G8_00B87EB0) != 0) P119_CarSkids(0x41);
  RE_DBG_SET(11, P100_RecKeys); RE_DBG_SET(12, P36_PadMode); RE_DBG_SET(13, P36_KeyCfg[6] | P36_KeyCfg[4] << 8 | P36_KeyCfg[5] << 16); RE_DBG_SET(14, (P14_00d118a8 | G2_00D118A8) * 1000 + hud1 * 10 + (P100_143720 != 0) + (P100_1426FC != 0) * 2 + (P75_E4 != 0) * 4);
  if (live) { RE_DBG(10); P142_CarsStep(); } else P35_PadX = 0;
  P14_Fn004E12E4();
  DrainStackC200F();
  CopyBDF984();
  P74_ShiftRows();
  if (P26_FxA != 0) { P130_RainSpawn(); P130_RainStep(); }
  P12_Fn004AAE34();
  if (live) P127_ScriptTick();
  P125_PickupTick((const uint8_t *)G6_00C80C50);
  P12_Fn0050229C();
  if (P95_B87EE0 != 0) P120_ConeRec();
  P15_RaiseLimits();
  if (P14_00b87ee4 == 0) { P62_Frame++; G8_00D118C0 = P62_Frame; }
  P121_CamSounds();
  P115_SndUpdate();
  P12_Fn0050E963();
}

/* ---- 004d4fc5 ---- */
static const char *const k_felony[11] = {
  "Driving on the sidewalk", "Terrorising pedestrians", "Speeding", "Shooting a red light",
  "Collision with another vehicle", "Collision with a police vehicle", "Destruction of property", "FEDERAL OFFENCE",
  "Driving the wrong way", "Driving without lights", "Driving recklessly" };   /* .data 0055fdd8 */
static void grd40(int32_t v) { if (P98_GrD40) P98_GrD40(v); }
#define P132_BLK(a) (P56_Blk84[((a) - 0x00c810c0u) / 4])

void P132_GameDraw(void) {
  char buf[256];
  RE_DBG(1);
#ifndef RE_HOOK_BUILD
  { static int k; if (getenv("RE_GSTAT") && (k++ % 100) == 0) fprintf(stderr, "[gdraw] cam %.0f %.0f %.0f angB %d mode %d car0 %d %d %d cell %d,%d N %d grid %dx%d vm %.2f %.2f %.2f far %.0f\n",
      P44_CamX, P44_CamY, P44_CamZ, (int)(int16_t)P59_AngB, (int)P59_Mode1137324, (int)P99_Cars[0].pos[0], (int)P99_Cars[0].pos[1], (int)P99_Cars[0].pos[2],
      (int)P88_CellA.x, (int)P88_CellA.y, (int)P54_GridN, (int)P21_GridDiv, (int)P80_GridH, P44_ViewMat[0], P44_ViewMat[4], P44_ViewMat[8], P11_01270c24);
    if (getenv("RE_GSTAT") && (k % 100) == 1 && G6_00D01268) { int N = P54_GridN, ne[4] = {0,0,0,0};
      for (int sl = 0; sl < 4; sl++) for (int i = 0; i < N * N; i++) ne[sl] += ((int32_t *)G6_00D01268)[sl * N * N + i] != -1;
      fprintf(stderr, "[gdraw] lumps %d %d %d %d cellA %d pc %d heads %d %d %d %d\n", (int)P87_SlotLumpA[0], (int)P87_SlotLumpA[1], (int)P87_SlotLumpA[2], (int)P87_SlotLumpA[3],
        (int)P88_CellA.cell, (int)P88_CellA.pc, ne[0], ne[1], ne[2], ne[3]); } }
#endif
#ifndef RE_HOOK_BUILD
  /* v2.15 Hor+: кадр начинается с центрального сдвига; при смене S (окно/полный экран) — окно отсечения 3D заново (P110_ViewSetup) */
  { static int last_ex = -1; int ex = re_view_extra(); plat_hud_anchor(0);
    if (ex != last_ex && P19_ScrH == 0x1e0) { last_ex = ex; P110_ViewSetup(0, 0, 0); } }
#endif
  uint8_t fxd = P26_FxD;
  if ((MenuVar575F3C | P13_00575f3c | G00575F3C) == 0) P26_FxD = 0;
  P66_Scene = 0x00cb8f20u;
  P52_GlideFogMode();
  int32_t live = (P14_00b87ee4 == 0 || P131_Skip != 0);
  if (S_00B5A77C == 0) {
    Ui004268E0();
    if (P26_FxA != 0) G8_00D17B0C = 0;
    if (P14_00b87ee4 == 0) P133_CamUpdate(1);
#ifndef RE_HOOK_BUILD
    /* v2.19 draw_distance: на время 3D-вида дальняя плоскость (P11_01270c24 и её копия для отсечения полигонов Q01270C24) × m,
       таблица 1/z продолжается за 0xdbba; значения опции (сохранение в config, ползунок меню) не меняются — восстановление перед бликом солнца */
    float dd_far0 = P11_01270c24, dd_q0 = Q01270C24;
    { double m = re_draw_distance();
      if (m > 1.0) { P11_01270c24 = (float)(dd_far0 * m); Q01270C24 = (float)(dd_q0 * m); re_dd_on = 1;
        re_oow_n = re_dd_oow_n(P11_01270c24 > Q01270C24 ? P11_01270c24 : Q01270C24); }
      else { re_dd_on = 0; re_oow_n = 0xdbba; } }
#endif
    P82_FrustumSetup3D();
    if (P14_00b87e84 != 0) P132_Lights();
    if (P98_MrkOff != 0) P76_AngleColor();
    if (P13_00575ef4 == 1) P127_LampLights();
    P109_ScriptMarkers();
    P89_DrawMap(1);
    NoopFn004d1a89();
    P109_DropsDraw(0);
    Reset0042D2B0();
    P137_DrawCar(S_00D11878, -1);
    if (P95_C818B8 != 0) P98_DrawMarker();
    if (P26_FxD != 0) grd40(0);
    P116_SkidsA();
    if ((G6_00B87EAC | G8_00B87EAC) != 0 || (P58_SB87EB0 | G6_00B87EB0 | G8_00B87EB0) != 0) P116_SkidsB();
    if (P26_FxD != 0) grd40(2);
    P128_TrafficDraw();
    P150_FlushTris();
    P127_SpawnTick(1);
    P133_EventModels();
    if (P98_MrkOff == 0) { P114_PartModels(); P98_IconFlush(); }
    P123_ObjShadows();
    int32_t e1 = MenuVar575EE8, e2 = P13_00575ee8, e3 = G00575EE8;
    if (P26_FxD != 0) { MenuVar575EE8 = 0; P13_00575ee8 = 0; G00575EE8 = 0; }
    P55_RunTableA();
    if (P26_FxD != 0) { MenuVar575EE8 = e1; P13_00575ee8 = e2; G00575EE8 = e3; }
    P106_SkyModels();
    P109_DropsDraw(1);
    if (P26_FxD != 0) grd40(0);
    if (P26_FxC != 0) P110_ScriptSprites();
    if (P26_FxA != 0) P131_RainDraw();
    if (P26_FxD != 0) grd40(2);
    if (P95_BDFA14 != 0) P113_Heli(1);
    P69_SceneFrame();
    P123_CarGlows();
    if (P26_FxA != 0) P116_Reflections();
    if (P98_MrkOff != 0) P114_ColorFlash();
    P55_RunTableB();
    P98_DrawScriptModels((const uint8_t *)G6_00C80C50);
    if (P97_ScrObjOn != 0) {
      uint8_t *o = (uint8_t *)re_ptr(P132_BLK(0x00c812b8u));
      if (o) P60_ObjUpdate(o);
      CallIfD14EE4();
    }
#ifndef RE_HOOK_BUILD
    if (re_dd_on) { P11_01270c24 = dd_far0; Q01270C24 = dd_q0; re_dd_on = 0; re_oow_n = 0xdbba; }
#endif
    if (P26_FxD == 0) P143_SunFlare();
    if (live) P121_ScriptHud();
    if ((MenuVarB31F04 | P13_00b31f04 | G00B31F04) != 0) P133_MirrorDraw();
    if (P97_ScrObjOn != 0) {
      const uint8_t *o = (const uint8_t *)re_ptr(P132_BLK(0x00c812b8u));
      if (o) P14_Fn004A39F6(o);
    }
    if (P29_Mode == 0) P120_HudTimes();
    P52_HudDispatch();
    if (P14_00b87ee4 == 0) P119_Hud();
    if (P36_PadMode != 0) P96_ReplayTag();
    P66_DirSwitch();
  }
  if (G6_00B5A778 != 0) P116_PauseMenu();
#ifndef RE_HOOK_BUILD
  /* v2.10: RE_COPDBG=N — рейтинг Felony / активные копы / последнее нарушение раз в N кадров (те же переменные, что строка отладки) */
  { static int k; const char *e = getenv("RE_COPDBG"); if (e && (k++ % (atoi(e) > 0 ? atoi(e) : 50)) == 0)
      fprintf(stderr, "[cop] кадр %d felony %d cops %d sugg %d max %d last %d spd %d игрок %d %d\n", (int)P62_Frame, (int)G2_00D11A5C,
              (int)G0112B284, (int)P97_D9E0, (int)P62_Max, (int)P95_ChanLast, (int)P62_Spd, (int)P99_Cars[0].pos[0], (int)P99_Cars[0].pos[2]);
      if (e && (k % (atoi(e) > 0 ? atoi(e) : 50)) == 1) for (int32_t q = 0; q < 8; q++) {   /* копы 0112da00: +0x32d — занят */
        const uint32_t *c = &P12_0112da00[q * 0x336]; if (c[0x32d] == 0) continue;
        int32_t dx = (int32_t)c[0x319] - P99_Cars[0].pos[0], dz = (int32_t)c[0x31b] - P99_Cars[0].pos[2];
        fprintf(stderr, "[cop]   коп %d pos %d %d дист %.0f видит %d car %08x seen %d\n", q, (int)c[0x319], (int)c[0x31b],
                sqrt((double)dx * dx + (double)dz * dz), (int)c[0x333], (unsigned)c[0x334], (int)P95_SndReady); } }
#endif
  if (S_00B5A77C == 0) {
    if (P12_00b87ef8 != 0) P114_CreditsDraw();
    if ((P11_00b87e7c | G00B87E7C) == 0) {
      CursorSet004D94B7(0, 0);
      P96_LogLine("\n\n\n");
      snprintf(buf, sizeof buf, "Felony rating: %d (%d active cops %d sugg. %d max. )\n",
               (int)G2_00D11A5C, (int)G0112B284, (int)P97_D9E0, (int)P62_Max);
      P96_LogLine(buf);
      if (P95_ChanLast != -1) {
        if (P95_ChanLast == 2)
          snprintf(buf, sizeof buf, "Last observed felony: %s (%d)\n", k_felony[2], (int)P62_Spd);
        else
          snprintf(buf, sizeof buf, "Last observed felony: %s\n",
                   (P95_ChanLast >= 0 && P95_ChanLast < 11) ? k_felony[P95_ChanLast] : "");
        P96_LogLine(buf);
      }
      if (P102_D0DDEC != 0) P96_LogLine("\nCruise control active.\n");
    }
    if (P14_00b87ee4 == 0) { P21_DrawClock(); P21_DrawFps(); }
    P55_PopDeferred();
    if (P132_B87EC8 != 0) P126_ScreenShot();
    P67_CompactPool();
  }
  if (P14_00b87ee4 == 0) P47_GlideSwap(); else P114_CamFadeFrame();
  P26_FxD = fxd;
}

/* ---- 004b9287 ---- */
void P132_Smoke(const float *pos, const float *vel, int32_t a, int32_t b, int32_t step, int32_t c, int32_t mode,
                float f, int32_t jitter) {
  if (G6_00B5A778 != 0 || (MenuVar55384C | P13_0055384c | G0055384C) == 0 || (P62_Frame & 1) == 0) return;
  int32_t i = PoolPop004AC6D0();
  if (i < 0) return;
#ifndef RE_HOOK_BUILD
  if (i >= 200) return;
#endif
  uint8_t *r = P95_ObjA + i * 0x78;
  uint32_t u = N14_Rand();
  wrf(r, (float)(int32_t)((u & 0xf) - 7) + pos[0]);
  wrf(r + 4, pos[1]);
  u = N14_Rand();
  wrf(r + 8, (float)(int32_t)((u & 0xf) - 7) + pos[2]);
  if (jitter == 0) {
    wrf(r + 0x20, vel[0]); wrf(r + 0x24, vel[1]); wrf(r + 0x28, vel[2]);
  } else {
    u = N14_Rand(); wrf(r + 0x20, (float)(int32_t)((u & 3) - 1) + vel[0]);
    wrf(r + 0x24, vel[1]);
    u = N14_Rand(); wrf(r + 0x28, (float)(int32_t)((u & 3) - 1) + vel[2]);
  }
  wrf(r + 0x34, f);
  wr32(r + 0x50, a);
  wr32(r + 0x54, b);
  wr32(r + 0x60, b < a ? -step : step);
  wr32(r + 0x58, c);
  int32_t q = (b - a) / (step != 0 ? step : 1);
  wr16(r + 0x64, (uint16_t)(q < 0 ? -q : q));
  wr16(r + 0x66, (uint16_t)((int32_t)rd16(r + 0x64) >> 1));
  int32_t d = (int32_t)rd16(r + 0x64); if (d == 0) d = 1;
  wr32(r + 0x68, mode == 1 ? 0x80006 : 0x100006);
  wr32(r + 0x5c, (c << 4) / d);
  (void)rd32; (void)rdf;
}

/* ---- 004ca135 ---- */
static int32_t sin_div(int32_t s) { int32_t v = s * 0xdac; return v / 4096; }   /* (v + (v>>31 & 0xfff)) >> 12 */
static void flash(const float *p) {
  P11_00ba52d0 = (int32_t)lrintf(P44_CamX - p[0]); int32_t dx = P11_00ba52d0;
  P11_00ba52d0 = (int32_t)lrintf(P44_CamZ - p[2]); int32_t dz = P11_00ba52d0;
  if (dx < 0) dx = -dx;
  if (dz < 0) dz = -dz;
  int32_t dist = dx < dz ? dz + dx / 2 : dx + dz / 2;
  if ((float)dist < P11_01270c24) {
    if (G00D14EEC < 0x40) P82_AddLight(p, 2000, G00D14EEC << 2, 0, 0);
    else P82_AddLight(p, 0x5dc, 0, 0, G00D14EEC << 2);
  }
}
void P132_Lights(void) {
  float p[3];
  if (P26_FxB != 0) P130_Lightning();
  if (G6_00B5A778 == 0) G00D14EEC = (G00D14EEC + 0x10) & 0x7f;
  G00D14EF4 = 0;
  int32_t eac = G6_00B87EAC | G8_00B87EAC;
  if (G00D17B08 != 0) {
    int32_t vx = P99_Cars[0].vel[0], vy = P99_Cars[0].vel[1];
    if (eac != 0) { vx = 0; vy = 0; }
    if (vx < 1000 || vy < 1000) {
      const p99_car_t *c = eac != 0 ? &P99_Cars[0x41] : &P99_Cars[0];
      int32_t k = ((vx < 1000) + (vy < 1000)) * 0x80 - 1;
      uint32_t h = (uint32_t)c->heading;
      p[1] = (float)-c->pos[1];
      p[0] = (float)c->pos[0] + (float)sin_div(P59_Sin[h & 0xfff]);
      p[2] = (float)c->pos[2] + (float)sin_div(P59_Sin[(h + 0x400) & 0xfff]);
      P82_AddLight(p, 3000, k, k, k);
      G00D14EF4 = 1;
    }
  }
  if (S_00D1192C == 10 && P98_DD70 == 1 && 100 < (int32_t)rd32((const uint8_t *)&P99_Cars[0] + 0xc)) {
    p[0] = (float)P99_Cars[0].pos[0]; p[1] = (float)-P99_Cars[0].pos[1]; p[2] = (float)P99_Cars[0].pos[2];
    flash(p);
  }
  if (P13_00575ef4 != 0) {
    for (int32_t i = 0; i < 0x40; i++) {
      const uint8_t *t = TrafficRecs + i * 0x54;
      const p99_car_t *c = &P99_Cars[i + 1];
      if (t[5] != 0 && t[0xc] == 1 && t[1] == 4 && 99 < rd32((const uint8_t *)c + 0xc) &&
          (t[5] - 1) < 16 && 0.01f <= rdf(P74_Cars + (t[5] - 1) * 0xcd8 + 0x20)) {
        p[0] = (float)c->pos[0]; p[1] = (float)-c->pos[1]; p[2] = (float)c->pos[2];
        flash(p);
      }
    }
    if (P62_HudOff2 != 0) {
      static const float k_pts[6][2] = { { -15360.0f, -8192.0f }, { -15360.0f, -15360.0f }, { -15360.0f, -21504.0f },
                                         { -6144.0f, -8192.0f }, { -6144.0f, -15360.0f }, { -6144.0f, -21504.0f } };
      p[0] = k_pts[0][0]; p[1] = -700.0f; p[2] = k_pts[0][1];
      if ((N14_Rand() & 3) == 0) P82_AddLight(p, (int32_t)(N14_Rand() & 0x1ff) + 3000, 0xff, 0xdc, 0xf);
      for (int32_t j = 1; j < 6; j++) {
        p[0] = k_pts[j][0]; p[1] = -700.0f; p[2] = k_pts[j][1];
        P82_AddLight(p, 3000, 0xff, 0xdc, 0xf);
      }
    }
    if (G011EFFE4 != 0) {
      for (int32_t j = 0; j < G011EFFE4 && j < 0x40000 / 0x1c; j++) {
        const uint8_t *e = A_012083C0 + j * 0x1c;
        p[0] = rdf(e); p[1] = rdf(e + 4); p[2] = rdf(e + 8);
        int32_t cb = (int32_t)rdf(e + 0x18), cg = (int32_t)rdf(e + 0x14), cr = (int32_t)rdf(e + 0x10);
        P82_AddLight(p, rd32(e + 0xc), cr, cg, cb);
      }
      G011EFFE4 = 0; G8_011EFFE4 = 0;
    }
  }
}

/* ---- 0049f20a ---- */
static char *fline(char *b, int32_t n, void *f) {
  b[0] = 0;
  char *r = g_fgets(b, n, f);
  size_t l = strlen(b);
  if (l >= 2 && b[l - 2] == '\r' && b[l - 1] == '\n') { b[l - 2] = '\n'; b[l - 1] = 0; }
  else if (l >= 1 && b[l - 1] == '\r') b[l - 1] = 0;
  return r;
}
int32_t P132_LoadFlyby(const char *name) {
  char line[32];
  void *f = g_fopen(name, "rt");
  if (f == NULL) return 0;
  fline(line, 0x1e, f);
  if (strcmp(line, "DRIVER Fly-By Text-file\n") != 0) { g_fclose(f); return 0; }
  g_fscanf(f, "\n");
  fline(line, 0xe, f);
  int32_t k = 0;
  while (strcmp(line, "End of Fly-By") != 0) {
    float v[9] = { 0 }; int32_t fr = 0;
    int32_t n = g_fscanf(f, "%d\n", &k);
    n += g_fscanf(f, "  Position: %f, %f, %f\n", &v[0], &v[1], &v[2]);
    n += g_fscanf(f, "  Rotation: %f, %f, %f, %f\n", &v[3], &v[4], &v[5], &v[6]);
    n += g_fscanf(f, "  Zoom:     %f\n", &v[7]);
    n += g_fscanf(f, "  Frame:    %d\n\n", &fr);
    if (k < 0 || k >= 0x3f) { g_fclose(f); return 0; }
    uint8_t *r = &P99_CamKeys[k * 0x34];
    wrf(r, v[0]); wrf(r + 4, v[1]); wrf(r + 8, v[2]);
    wrf(r + 0x20, v[3]); wrf(r + 0x10, v[4]); wrf(r + 0x14, v[5]); wrf(r + 0x18, v[6]);
    wrf(r + 0x24, v[7]); wr32(r + 0x2c, fr);
    if (n != 10) { g_fclose(f); return 0; }
    wr32(r + 0x28, rd32(r + 0x28) | 1);
    if (fline(line, 0xe, f) == NULL) { g_fclose(f); return 0; }   /* оригинал на EOF зацикливается */
  }
  memcpy(&P99_CamKeys[(k + 1) * 0x34], &P99_CamKeys[k * 0x34], 0x34);
  g_fclose(f);
  P99_CamLast = k + 1;
  return 1;
}
