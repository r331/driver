/* v1.90: ported145 — см. ported145.h. Восстановлено из Game.exe (Ghidra out/Game_decomp.c + ассемблер), cdecl (ret без операнда).
   004d38b7 — загрузка уровня. Демо 00b87e38 = 200/0xfa/0xfb/0xfc → 00d11934 = 1, 00b87ea0 = 1, 005f7e50 = 4 и конфиг повтора
     I_TRAINDEMO0/DESERTDEMO1..3 (00517d58, 0 — выход 0); режим режиссёра 004c875d по 005f7e5c/005f7e50/00d11934/00d17b90/00b87ef8;
     при 00b87eb8 и не демо — 00405450 + 004055e8; 00b20308 — конфиг по имени 00d11900; миссия 004f4180(00b87e38) с сохранением
     00c8198c/00c80ee8/00c81988 для города 4; банки master.dss / cops.dss (00524496 → 00d118d0/00d118cc); LEVELS\<город>.D3D
     (004efafd, города 0..6); DATA\(US)LOADING.BMP по языку 00c557fc; сброс счётчиков; srand(0x3039) (0052e180), 004d9028;
     без 00b87eb8 — флаги опций 1 и дальности 27000.0/27000.0/1.0 (01270c24, 0125f3f8, 0125f3e0); окно 004d9539(сид города,
     fistp(65·W/640), fistp(430·H/480), ftol(575·W/640 − 65·W/640), ftol(460·H/480 − 430·H/480)) — .rdata 005468b8..c4 =
     460/575/430/65, делители 00546060/0054605c; аргументы по ассемблеру 004d3fcd..004d403b (Ghidra теряет два __ftol, как в
     004d35b2), fistp пишет промежуточно в 00ba52d0 (остаётся x). Сид окна по городу: 1 → 0x1b31c4c, 2 → 0x160d04a,
     3 → 0x19b16a9, 4 → 0x9f3750, 5 → 0xc68f60, 6 → 0x528fb4, иначе 0x161712a. Далее FRUSTRUM.DAT, буферы, 004ecade (0 — выход 0),
     инициализация подсистем, брызги/снег в 00d14f00 (004cb857 / 004cd875, 00d17af8 = 00d14f00), цвет фонарей 004cb4ff
     (по 00b202d8/00b202dc/00b87e84/00b202e0), позиция игрока: при 00bdfa60 ≠ 0 — сдвиг полей +0x54..+0x68 записи 00d07888 на
     00bdfa60/6 (+0x70 — на 6·(00bdfa60/6)), иначе при 00d06a04 — из 00c816c0 (при 005f7e50 == 0 — копия 0x40 байт из
     00c81700 и строка в debug.log); 004c032a(−1); 00c4d70c 0 → 1, и при 1 — 01136c48/00b5a898/00b87ec0 + 0051879f; CD-трек
     город + 4 при 00b87e90; grTexFilterMode(0, 1, 1) по имени (как ported124); строка «Interview …» в debug.log; возврат 1.
   Отступления native: адрес 00d14f00 — буфер P145_Splash (G2_ScriptStack — родной указатель на него); 00c812bc (uint32-адрес)
     переводится re_ptr, NULL — без 004f5c72; копия 00c81700 → 00c816c0 — по 14 словам в P127_GoalSave и 2 в P102_C816F8/FC;
     00c8198c пишется во все псевдонимы (G00C8198C, P43_AnimTab[0], A_00C8198C[0..3]). */
#include "ported145.h"
#include "unported.h"
#include "crt.h"
#include "reptr.h"
#include "cartab.h"
#include "director.h"
#include "globalsets.h"
#include "menustate.h"
#include "noop.h"
#include "smallfuncs.h"
#include "smallfuncs2.h"
#include "uihandlers3.h"
#include "uihandlers4.h"
#include "directorstorage.h"
#include "ported100.h"
#include "ported101.h"
#include "ported102.h"
#include "ported103.h"
#include "ported104.h"
#include "ported106.h"
#include "ported11.h"
#include "ported110.h"
#include "ported112.h"
#include "ported113.h"
#include "ported116.h"
#include "ported12.h"
#include "ported120.h"
#include "ported124.h"
#include "ported125.h"
#include "ported126.h"
#include "ported127.h"
#include "ported128.h"
#include "ported129.h"
#include "ported13.h"
#include "ported130.h"
#include "ported131.h"
#include "ported133.h"
#include "ported136.h"
#include "ported137.h"
#include "ported138.h"
#include "ported14.h"
#include "ported142.h"
#include "ported15.h"
#include "ported16.h"
#include "ported17.h"
#include "ported19.h"
#include "ported21.h"
#include "ported25.h"
#include "ported26.h"
#include "ported28.h"
#include "ported29.h"
#include "ported33.h"
#include "ported36.h"
#include "ported4.h"
#include "ported43.h"
#include "ported48.h"
#include "ported5.h"
#include "ported52.h"
#include "ported54.h"
#include "ported55.h"
#include "ported56.h"
#include "ported58.h"
#include "ported59.h"
#include "ported6.h"
#include "ported60.h"
#include "ported61.h"
#include "ported62.h"
#include "ported67.h"
#include "ported69.h"
#include "ported7.h"
#include "ported71.h"
#include "ported73.h"
#include "ported74.h"
#include "ported75.h"
#include "ported76.h"
#include "ported77.h"
#include "ported78.h"
#include "ported8.h"
#include "ported86.h"
#include "ported88.h"
#include "ported93.h"
#include "ported94.h"
#include "ported95.h"
#include "ported96.h"
#include "ported97.h"
#include "ported98.h"
#include "ported99.h"
#include "widgets.h"
#include <stdio.h>
#include <string.h>
#include <math.h>

#ifndef RE_HOOK_BUILD
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P145_B20304")
#undef P145_B20304
#pragma push_macro("P145_B20304") /*gvi*/
#undef P145_B20304 /*gvi*/
int32_t P145_B20304;
#pragma pop_macro("P145_B20304") /*gvi*/
#pragma pop_macro("P145_B20304")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P145_B20308")
#undef P145_B20308
#pragma push_macro("P145_B20308") /*gvi*/
#undef P145_B20308 /*gvi*/
int32_t P145_B20308;
#pragma pop_macro("P145_B20308") /*gvi*/
#pragma pop_macro("P145_B20308")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P145_D0FE18")
#undef P145_D0FE18
#pragma push_macro("P145_D0FE18") /*gvi*/
#undef P145_D0FE18 /*gvi*/
uint16_t P145_D0FE18;
#pragma pop_macro("P145_D0FE18") /*gvi*/
#pragma pop_macro("P145_D0FE18")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P145_D10E60")
#undef P145_D10E60
#pragma push_macro("P145_D10E60") /*gvi*/
#undef P145_D10E60 /*gvi*/
uint16_t P145_D10E60;
#pragma pop_macro("P145_D10E60") /*gvi*/
#pragma pop_macro("P145_D10E60")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P145_D1184C")
#undef P145_D1184C
#pragma push_macro("P145_D1184C") /*gvi*/
#undef P145_D1184C /*gvi*/
int32_t P145_D1184C;
#pragma pop_macro("P145_D1184C") /*gvi*/
#pragma pop_macro("P145_D1184C")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P145_D118C4")
#undef P145_D118C4
#pragma push_macro("P145_D118C4") /*gvi*/
#undef P145_D118C4 /*gvi*/
int32_t P145_D118C4;
#pragma pop_macro("P145_D118C4") /*gvi*/
#pragma pop_macro("P145_D118C4")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P145_BankCops")
#undef P145_BankCops
#pragma push_macro("P145_BankCops") /*gvi*/
#undef P145_BankCops /*gvi*/
int32_t P145_BankCops;
#pragma pop_macro("P145_BankCops") /*gvi*/
#pragma pop_macro("P145_BankCops")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P145_BankMain")
#undef P145_BankMain
#pragma push_macro("P145_BankMain") /*gvi*/
#undef P145_BankMain /*gvi*/
int32_t P145_BankMain;
#pragma pop_macro("P145_BankMain") /*gvi*/
#pragma pop_macro("P145_BankMain")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P145_CfgName")
#undef P145_CfgName
#pragma push_macro("P145_CfgName") /*gvi*/
#undef P145_CfgName /*gvi*/
p145_s24_t P145_CfgName;
#pragma pop_macro("P145_CfgName") /*gvi*/
#pragma pop_macro("P145_CfgName")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P145_Splash")
#undef P145_Splash
#pragma push_macro("P145_Splash") /*gvi*/
#undef P145_Splash /*gvi*/
p145_splash_t P145_Splash;
#pragma pop_macro("P145_Splash") /*gvi*/
#pragma pop_macro("P145_Splash")
#endif
#endif

#ifdef RE_HOOK_BUILD
#  define P145_STD __attribute__((stdcall))
#else
#  define P145_STD
#endif

static float u2f(uint32_t u) { float f; memcpy(&f, &u, 4); return f; }
#include "memrw.h"

/* (*01270d6c)(0,1,1) = grTexFilterMode — по имени из таблицы Glide (как ported124) */
static void tex_filter(int32_t a, int32_t b, int32_t c) {
  for (int i = 0; i < P33_GlideCount(); i++)
    if (strcmp(P33_GlideName(i), "_grTexFilterMode@12") == 0) {
      void (P145_STD *f)(int32_t, int32_t, int32_t) = (void (P145_STD *)(int32_t, int32_t, int32_t))P33_GlideProc(i);
      if (f != NULL) f(a, b, c);
      return;
    }
}

static void set_ea0(int32_t v) { G6_00B87EA0 = v; P62_HudOff1 = v; }
static void set_frame0(void) { P62_Frame = 0; G8_00D118C0 = 0; }
static void set_d11934(int32_t v) { P11_00d11934 = v; P17_Cond1 = v; }
static void set_c8198c(int32_t v) {
  G00C8198C = v; P43_AnimTab[0] = v;
  memcpy((uint8_t *)A_00C8198C, &v, 4);
}

/* ---- 004d38b7 ---- */
int32_t P145_LevelLoad(void) {
  const char *demo = NULL;
  if (GameMode == 0) DeleteWaypointFile();
  if (G6_00B87EAC != 0 && (P15_State == 4 || P15_State == 5)) set_ea0(1);
  P110_FullClip = 1;
  P21_FpsLast = 0; P21_FpsVal = 0; P21_FpsCnt = 0;
  set_frame0();
  P67_Cur = 0; P142_340C0 = 0; P112_Wanted = 0; P98_FreeTurn = 0;
  P48_ResetAll();
  switch (P11_00b87e38) {
  case 200:  demo = "I_TRAINDEMO0"; break;
  case 0xfa: demo = "DESERTDEMO1"; break;
  case 0xfb: demo = "DESERTDEMO2"; break;
  case 0xfc: demo = "DESERTDEMO3"; break;
  default: set_d11934(0); break;
  }
  if (demo != NULL) { set_d11934(1); set_ea0(1); GameMode = 4; }
  if (P11_00d11934 != 0 && P138_ReplayCfg(demo) == 0) return 0;
  ResetDirectorState();
  if (P12_005f7e5c == 0) {
    if (GameMode == 4) {
      if (P11_00d11934 != 0) SetDirectorMode(0xf, 0, 0);
      else if (P12_00d17b90 != 0) SetDirectorMode(0xd, 0, 0);
      else SetDirectorMode(0xb, 0, 0);
    } else if (GameMode == 5) SetDirectorMode(1, 1, 0);
    else SetDirectorMode(0, 0, 0);
  } else if (P12_00b87ef8 == 0) SetDirectorMode(7, 0, 0);
  else SetDirectorMode(0xe, 0, 0);
  P103_D118E0 = 0;
  uint8_t keep = P52_NoTrail;
  P52_NoTrail = 0;
  if (P55_B87EB8 != 0 && P11_00d11934 == 0) {
    P95_ResetRace();
    P145_B20304 = 0;
    P133_LoadConfig();
    set_ea0(0);
    P14_00b87e84 = 0;
    P26_FxB = 0;
  }
  P71_ScoreSetup();
  P102_D06A04 = 0;
  P103_ReplayReset();
  if (P145_B20308 != 0 && P138_ReplayCfg(P145_CfgName) == 0) return 0;
  int32_t sv14 = G00C8198C, svc = P17_Src, sv18 = G00C81988;
  P138_LoadMission(P11_00b87e38);
  if (G6_00B87EAC != 0 && (P15_State == 4 || P15_State == 5)) set_ea0(1);
  if (P15_State == 4) { set_c8198c(sv14); P17_Src = svc; G00C81988 = sv18; }
  if (P15_State == 2 || P15_State == 4) P14_00b87e84 = 1;
  P145_BankMain = P77_LoadBank("master.dss", 0);
  P145_BankCops = P77_LoadBank("cops.dss", 0x8000);
  SoundSetVolB0052360D(1);
  P58_FreeRecs();
  switch (P15_State) {
  case 0: P126_ReadMapPals("LEVELS\\MIAMI.D3D"); break;
  case 1: P126_ReadMapPals("LEVELS\\FRISCO.D3D"); break;
  case 2: P126_ReadMapPals("LEVELS\\LA.D3D"); break;
  case 3: P126_ReadMapPals("LEVELS\\NEWYORK.D3D"); break;
  case 4: P126_ReadMapPals("LEVELS\\IVIEW.D3D"); break;
  case 5: P126_ReadMapPals("LEVELS\\TRAIN.D3D"); break;
  case 6: P126_ReadMapPals("LEVELS\\NC_01.D3D"); break;
  default: break;
  }
  P124_ShowBmp(P55_Lang == 5 ? "DATA\\USLOADING.BMP" : "DATA\\LOADING.BMP", 0);
  P62_InitCamDefaults();
  GlobalSet004CA0C0();
  P131_LoadCosDen(0);
  CopySlotTemplate004A1010();
  GlobalSet004CF100();
  P98_C824A0 = 0; P127_SpawnReq = 0; P127_SpawnRst = 0; G00BDF984 = 0;
  P103_DmgPct = 100; P100_RecKeys = 0x20;
  P145_D118C4 = 0; P145_D1184C = 0; P125_D118E4 = 1;
  S_00D11878 = 0;
  P14_00d118a8 = 0; G2_00D118A8 = 0;
  G6_00D11928 = 0xb4;
  P145_D10E60 = 0xffff; P145_D0FE18 = 0xffff;
  S_00D11804 = 0; G00D11804 = 0;
  P125_D11680 = 0; P96_FpsShown = 0; P96_FpsTick0 = 0; P96_FpsFrame0 = 0;
  P62_InitRenderConsts();
  P78_VertsB = NULL; P78_VertsA = NULL; P78_VertCount = 0; P129_HitModel = 0;
  Call0052E180(0x3039);                       /* srand */
  Mask004D9028(0xd431, 0x350b1);
  if (P95_C818B8 != 0) S_00D1192C = 1;
  P58_FreeList();
  if (P55_B87EB8 == 0) {
    P13_00575ebc = 1; G6_00575EBC = 1;
    P13_00575ec0 = 1; G6_00575EC0 = 1;
    MenuVar55384C = 1; P13_0055384c = 1; G0055384C = 1;
    MenuVarD118C8 = 1; P13_00d118c8 = 1; G00D118C8 = 1;
    MenuVar55C974 = 1; P13_0055c974 = 1; P28_ShineFlag = 1; G0055C974 = 1;
    P13_00d11880 = 1; G6_00D11880 = 1;
    MenuVar575EE8 = 1; P13_00575ee8 = 1; G00575EE8 = 1;
    MenuVar553850 = 1; P13_00553850 = 1; G00553850 = 1;
    P11_01270c24 = u2f(0x46d2f000u); P13_01270c24 = (int32_t)0x46d2f000; Q01270C24 = u2f(0x46d2f000u); P59_CamF1 = u2f(0x46d2f000u);
    P11_0125f3f8 = u2f(0x46d2f000u); P13_0125f3f8 = (int32_t)0x46d2f000; Q0125F3F8 = u2f(0x46d2f000u);
    P11_0125f3e0 = 1.0f; P19_Scale = 1.0f;
  }
  P110_ViewSetup(0, 0, 0);
  float x0 = (65.0f * (float)P19_ScrW) / P19_DivW;    /* .rdata 005468c4 */
  float y0 = (430.0f * (float)P19_ScrH) / P19_DivH;   /* 005468c0 */
  float x1 = (575.0f * (float)P19_ScrW) / P19_DivW;   /* 005468bc */
  float y1 = (460.0f * (float)P19_ScrH) / P19_DivH;   /* 005468b8 */
  int32_t seed;
  switch (P15_State) {
  case 1: seed = 0x1b31c4c; break;
  case 2: seed = 0x160d04a; break;
  case 3: seed = 0x19b16a9; break;
  case 4: seed = 0x9f3750; break;
  case 5: seed = 0xc68f60; break;
  case 6: seed = 0x528fb4; break;
  default: seed = 0x161712a; break;
  }
  int32_t iy = fround(y0);
  P11_00ba52d0 = fround(x0);
  SetDrawParams_004D9539(seed, P11_00ba52d0, iy, (int32_t)(x1 - x0), (int32_t)(y1 - y0));
  LoadFsin_00525E50();
  P55_LoadFrustum();
  AllocMapBuffer300000();
  P54_AllocRoadbits();
  if (P77_LoadLevel() == 0) return 0;
  ClearDirectorTables();
  Pack565Bytes004BF452(0xf0, 0xf0, 0xa0);
  NoopFn004bf471();
  P56_AllocEulerTab(1);
  P94_BuildDirTab();
  P74_SkidInit();
  P52_ResetSlots();
  P96_ShadowInit();
  P95_B87E34 = P15_State;
  P56_ReplayPaths(P15_State);
  P126_PlayerStart();
  P97_ResetCars();
  P28_LoadCarModels();
  P95_InitDebris();
  GlobalSet0051BD78();
  NoopFn004d1a84();
  P137_MotionInit();
  P103_MissionModels();
  StartFlyby004A05C0();
  P125_CF56C0 = 0; P106_SkyRot = 0; P21_FrameTotal = 0;
  set_frame0();
  if (P36_PadMode == 2) P138_LoadPads();
  P142_D07788 = (P26_FxA == 0 && P26_FxC == 0) ? 0 : 10000;
  if (G6_00B87EAC != 0 || P95_B87EB4 != 0 || P58_SB87EB0 != 0) {
    MenuVar5759A4 = 0x10; P13_005759a4 = 0x10; P60_PartLimit = 0x10; G005759A4 = 0x10;
  }
  P73_ParticlesReset();
  if (P29_Mode == 0) P131_FlybyStart();
  P75_ResetObjs();
  P103_TrafficReset();
  P102_ResetCars();
  if (P15_State == 4 || P15_State == 5) P104_MissionInit();
  P69_SetupMsgs();
  if (P56_B87EA8 != 0) Set0D044C8();
  if (P14_00b87e84 != 0) P14_Fn004CAD47();
  if (P26_FxA != 0) {
    P98_InitSplash((uint8_t *)P145_Splash);
    G2_ScriptStack = P145_Splash;
    P26_FxC = 0;
  } else if (P26_FxC != 0) {
    P120_ScriptReset(P145_Splash);
    G2_ScriptStack = P145_Splash;
  }
  P101_SkyInit();
  if (P58_SB87EB0 != 0) P138_ReplayLoad();
  Pack565_004D950F(0xff, 0xff, 0);
  P73_C566FC = 0;
  Clear2C3B8();
  P101_MirrorMaskR(15.0f);                    /* 0x41700000 */
  P100_MirrorMask();
  P127_ScriptTick();
  P136_CompileEvents();
  if (P14_00b202d8 != 0) P98_LampColor(G00D17AE4, G00D17B10, G00D17B04);
  else if (P14_00b202dc != 0) P98_LampColor(G00D17B20, G00D164F0, G00D17B21);
  else if (P14_00b87e84 != 0) P98_LampColor(P130_LampRGB[0], P130_LampRGB[1], P130_LampRGB[2]);
  else if (P26_FxA != 0) P98_LampColor(0x9a, 0x9a, 0x9a);
  P99_MarkerReset();
  if (P95_BDFA60 != 0) {
    int32_t d = P95_BDFA60 / 6;
    P145_D078DC += d; P145_D078E0 += d; P145_D078E4 += d;
    P145_D078E8 += d; P145_D078EC += d; P145_D078F0 += d;
    G00D078F8 += d * 6;
    P95_BDFA60 = 0;
    P128_CarDeform(-1);
  } else if (P102_D06A04 != 0) {
    if (GameMode == 0) {
      P124_DebugLog("GAMEMAIN: Reusing player position (MStart = MNext)");
      uint32_t w[16];
      memcpy(w, P127_GoalPause, sizeof w);
      memcpy(P127_GoalSave, w, sizeof(p127_u14_t));
      P102_C816F8 = (int32_t)w[14]; P102_C816FC = (int32_t)w[15];
    }
    P145_D078DC = (int32_t)P127_GoalSave[7];  P145_D078E0 = (int32_t)P127_GoalSave[8];
    P145_D078E4 = (int32_t)P127_GoalSave[9];  P145_D078E8 = (int32_t)P127_GoalSave[10];
    P145_D078EC = (int32_t)P127_GoalSave[11]; P145_D078F0 = (int32_t)P127_GoalSave[12];
    G00D078F8 = (int32_t)P127_GoalSave[13];
    P128_CarDeform(-1);
  }
  P52_NoTrail = keep;
  P11_01270c38 = 1;
  if (P95_B87EE0 != 0) LoadTrail004FBE96();
  if (P95_B87EDC != 0) Fwd004FC0C7();
  P52_GlideFogSetup();
  int pads = 0;
  if (P36_PadMode == 0) { P36_PadMode = 1; pads = 1; }
  else if (P36_PadMode == 1) pads = 1;
  if (pads) {
    if (G6_00B87EAC == 0) { P61_V10 = 0; P12_00b5a898 = 0; P95_B87EC0 = 1; }
    else { P61_V10 = 0x41; P12_00b5a898 = 1; }
    P138_ReplayInit();
  }
  if (P12_00b87ef8 != 0) P98_CreditsInit();
  if (P58_SB87EB0 != 0 && G6_00B87EA0 == 0 && P62_HudOff2 == 0) {
    int32_t *m = (int32_t *)re_ptr(P113_MrkRec);
    if (m != NULL) ScriptSetWait004F5C72(m, P74_C4D668);
  }
#ifndef RE_HOOK_BUILD
  P131_MusicHint();   /* v2.33: ночь/погоня — до запроса дорожки уровня */
#endif
  if (Q00B87E90 != 0) { P25_InitCDAudio(); P25_PlayCDTrack(P15_State + 4); }
  P48_FadeEnd();
  P116_SndLevelStart();
  if (P16_FlagA != 0) P43_CdFadeInit();
  P21_FrameTicks();
  P86_Detail = 0;
  tex_filter(0, 1, 1);
  P110_FullClip = 0;
  P11_01270c38 = 2;
  if (G6_00B87EAC != 0) G00575F24 = 1;
  char msg[256];
  snprintf(msg, sizeof msg, "Interview %d, Training %d, mode %d, chaseHQmode %d", P62_HudOff2, G6_00B87EA0, P88_Mode575, P95_B87F08);
  P124_DebugLog(msg);
  return 1;
}
