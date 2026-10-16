/* v1.70: ported125 — восстановлено из Game.exe. Все функции cdecl (work/rets.py: ret без операнда).
   004d35b2 — загрузка уровня: DATA\(US)LOADING.BMP, сброс состояния, LEVELS\FLAT.D3D (004efafd, не перенесена), srand(0x3039),
     окно отрисовки 65/640·W … 575/640·W × 430/480·H … 460/480·H (Ghidra путает аргументы 004d9539 — восстановлено по ассемблеру).
   004c43b6 — нет в Ghidra-списке (найдена через thunk 00401e8d): корень узла по +0x18, switch по id корня (таблица 004c455c/004c4584).
   004f5e55 — AddDashMessage; в native массив сообщений — родные указатели (sizeof(void*)), счётчики — int32.
   004b8d49 / 004afa4c / 004b955c — частицы в пулах 0110b260 (0x3c), 010fb220 (0x3c), 010f5160 (0x78); цвета .data 00553630.
   0042d554 — как 0042d797 (P100_ClipNear), без UV; делитель второй ветки — fabs (CRT 0052e080).
   00522f4f — запись капли 0x1c в P101_Drops (+0x18 — адрес объекта, uint32); 004fc0d9 — подбор точек (записи 0x14),
     объекты капель — P125_Pick 00c81500; 00c810c4 пишется во все native-псевдонимы.
   0050fbf4 — индексы строк из .data 00575558 (копия k_575558) в поля P117_MenuB (+0x30 + 0x28·k).
   004a5634 — список «ИМЯ\0»+u16, в конце два нуля; строчные a..y → заглавные ('z' не меняется, как в оригинале).
   004079aa — палитра 256×RGBX → 16-битные цвета по сдвигам 005c6748.., таблица P65_Blend 256×256 ближайших к среднему. */
#include "ported125.h"
#include "unported.h"
#include "engine.h"
#include "crt.h"
#include "reptr.h"
#include "cartab.h"
#include "director.h"
#include "dirnodes.h"
#include "directorstorage.h"
#include "globalsets.h"
#include "menustate.h"
#include "noop.h"
#include "smallfuncs.h"
#include "smallfuncs2.h"
#include "uihandlers3.h"
#include "uihandlers4.h"
#include "ported4.h"
#include "ported5.h"
#include "ported6.h"
#include "ported7.h"
#include "ported8.h"
#include "ported11.h"
#include "ported12.h"
#include "ported13.h"
#include "ported14.h"
#include "ported16.h"
#include "ported17.h"
#include "ported19.h"
#include "ported21.h"
#include "ported26.h"
#include "ported29.h"
#include "ported44.h"
#include "ported48.h"
#include "ported52.h"
#include "ported54.h"
#include "ported55.h"
#include "ported56.h"
#include "ported58.h"
#include "ported60.h"
#include "ported62.h"
#include "ported65.h"
#include "ported66.h"
#include "ported67.h"
#include "ported69.h"
#include "ported75.h"
#include "ported77.h"
#include "ported78.h"
#include "ported86.h"
#include "ported94.h"
#include "ported95.h"
#include "ported96.h"
#include "ported97.h"
#include "ported98.h"
#include "ported99.h"
#include "ported100.h"
#include "ported101.h"
#include "ported103.h"
#include "ported106.h"
#include "ported111.h"
#include "ported113.h"
#include "ported114.h"
#include "ported116.h"
#include "ported117.h"
#include "ported124.h"
#include "ported126.h"
#include <math.h>
#include <stdio.h>
#include <string.h>

#ifndef RE_HOOK_BUILD
GAME_VAR_DEF(int32_t, P125_C814E0, 0x00c814e0)
GAME_VAR_DEF(int32_t, P125_C814E4, 0x00c814e4)
GAME_VAR_DEF(int32_t, P125_C81690, 0x00c81690)
GAME_VAR_DEF(int32_t, P125_C81694, 0x00c81694)
GAME_VAR_DEF(int32_t, P125_D118E4, 0x00d118e4)
GAME_VAR_DEF(int32_t, P125_D11680, 0x00d11680)
GAME_VAR_DEF(int32_t, P125_CF56C0, 0x00cf56c0)
GAME_VAR_DEF(int32_t, P125_DirD17C0C, 0x00d17c0c)
GAME_VAR_DEF(p125_pick_t, P125_Pick, 0x00c81500)
GAME_VAR_DEF(int32_t, P125_PickIdx, 0x00c80bec)
GAME_VAR_DEF(p125_droptime_t, P125_DropTime, 0x00bde780)
GAME_VAR_DEF(p125_fps_t, P125_FpsStr, 0x00b5a48c)
GAME_VAR_DEF(p125_mrk_t, P125_MrkSave, 0x01271070)
GAME_VAR_DEF(int32_t, P125_ModelNamesSize, 0x00b1ff64)
GAME_VAR_DEF(int32_t, P125_ShrR, 0x005c6748)
GAME_VAR_DEF(int32_t, P125_ShrG, 0x005c674c)
GAME_VAR_DEF(int32_t, P125_ShrB, 0x005c6750)
GAME_VAR_DEF(int32_t, P125_ShlR, 0x005c6754)
GAME_VAR_DEF(int32_t, P125_ShlG, 0x005c6758)
GAME_VAR_DEF(int32_t, P125_ShlB, 0x005c675c)
#endif

static int32_t rd32(const void *p) { int32_t v; memcpy(&v, p, 4); return v; }
static void wr32(void *p, int32_t v) { memcpy(p, &v, 4); }
static int16_t rd16(const void *p) { int16_t v; memcpy(&v, p, 2); return v; }
static void wr16(void *p, int16_t v) { memcpy(p, &v, 2); }
static float rdf(const void *p) { float v; memcpy(&v, p, 4); return v; }
static void wrf(void *p, float v) { memcpy(p, &v, 4); }
static int32_t fround(float v) { return (int32_t)lrintf(v); }   /* fistp */

#define P125_BLK(off) (*(int32_t *)&P56_Blk84[((off) - 0x00c810c0) / 4])   /* поля внутри P56_Blk84 */
#define P125_Car0X CARTAB_VAR(int32_t, P125_Car0X, 0x00d07800)
#define P125_Car0Z CARTAB_VAR(int32_t, P125_Car0Z, 0x00d07808)

/* .data 00553630: цвета дыма по времени суток S_00D1192C (RGBX) */
static const uint8_t k_553630[32] = { 0x6f,0x73,0x91,0, 0xb8,0xcf,0xda,0, 0xe2,0x82,0x79,0, 0x3c,0x32,0x2c,0,
                                      0x76,0x9a,0xc5,0, 0xba,0x9e,0x90,0, 0x61,0x6d,0x80,0, 0xd0,0x94,0x75,0 };
/* .data 00575558: индексы строк пунктов меню управления (вкл/выкл, режимы) */
static const int32_t k_575558[16] = { 2, 1, 2, 6, 7, 8, 7, 0xe8, 2, 5, 7, 5, 10, 0xe2, 0xe8, 0xe3 };

/* ---- 004d35b2 ---- */
int32_t P125_LevelLoad(void) {
  uint8_t keep = P52_NoTrail;
  P52_NoTrail = 0;
  P124_ShowBmp(P55_Lang == 5 ? "DATA\\USLOADING.BMP" : "DATA\\LOADING.BMP", 0);
  P58_FreeRecs();
  P126_ReadMapPals("LEVELS\\FLAT.D3D");
  P62_HudOff2 = 0; P62_HudOff1 = 0; G6_00B87EA0 = 0;
  MenuVarB201DC = 0; P13_00b201dc = 0; G00B201DC = 0;
  P14_00b87e84 = 0; P52_FogOn = 0; P14_00b202d8 = 0; P14_00b202dc = 0;
  P125_C814E0 = -1; P125_C814E4 = -1; P125_C81690 = -1; P125_C81694 = -1;
  P125_D118E4 = 1; S_00D11878 = 0; S_00D1192C = 0;
  P14_00d118a8 = 0; G2_00D118A8 = 0; S_00D11804 = 0; G00D11804 = 0;
  P125_D11680 = 0; P96_FpsShown = 0; P96_FpsTick0 = 0; P96_FpsFrame0 = 0;
  P62_InitRenderConsts();
  P62_InitCamDefaults();
  P21_FpsLast = 0; P21_FpsVal = 0; P21_FpsCnt = 0;
  P62_Frame = 0; G8_00D118C0 = 0; P67_Cur = 0;
  P78_VertsB = NULL; P78_VertsA = NULL;
  Call0052E180(0x3039);                       /* srand */
  Mask004D9028(0xd431, 0x350b1);
  P58_FreeList();
  float x0 = 65.0f * (float)P19_ScrW / 640.0f, y0 = 430.0f * (float)P19_ScrH / 480.0f;
  float x1 = 575.0f * (float)P19_ScrW / 640.0f, y1 = 460.0f * (float)P19_ScrH / 480.0f;
  int32_t iy = fround(y0);
  P11_00ba52d0 = fround(x0);
  SetDrawParams_004D9539(0xe08543, P11_00ba52d0, iy, (int32_t)(x1 - x0), (int32_t)(y1 - y0));
  LoadFsin_00525E50();
  P55_LoadFrustum();
  AllocMapBuffer300000();
  P54_AllocRoadbits();
  int32_t ok = P77_LoadLevel();
  if (ok != 0) {
    Pack565Bytes004BF452(0xf0, 0xf0, 0xa0);
    NoopFn004bf471();
    P56_AllocEulerTab(1);
    P126_PlayerStart();
    P125_CF56C0 = 0; P106_SkyRot = 0; P21_FrameTotal = 0;
    P62_Frame = 0; G8_00D118C0 = 0;
    P75_ResetObjs();
    P103_TrafficReset();
    Clear2C3B8();
    P86_Detail = 0;
    P52_NoTrail = keep;
  }
  return ok != 0;
}

/* ---- 004c43b6 ---- */
void P125_ReplayNodeAction(int32_t id) {
  DIR_NODE *n = FindNodeById(id);
  if (n == NULL) return;                       /* native: в оригинале чтение по нулю */
  while (n->unk18 != 0) { n = FindNodeById(n->unk18); if (n == NULL) return; }
  switch (n->id) {
  case 1: SetDirectorMode(4, 0, 0); break;
  case 2: SetDirectorMode(3, 0, 0); break;
  case 3: SetDirectorMode(6, 0, 0); break;
  case 4: SetDirectorMode(5, 0, 0); break;
  case 5:
    if (DirectorUnk6C > 2) {
      SaveDirector("REPLAYDATA\\USER\\$TEMP$.CAMS");
      G005F7E54 = 5; P17_Const6 = 5; P8_005f7e54 = 5;
      G6_00B87E20 = 0;
    }
    break;
  case 6: if (n->id == id) DirectorUnk7C = n->link2; else AddCamera(id); break;
  case 7: if (n->id == id) DirectorUnk7C = n->link2; else ChangeCamera(id); break;
  case 8:
    SaveDirector("REPLAYDATA\\USER\\$TEMP$.CAMS");
    SetDirectorMode(0, 1, 0);
    SetLatchValue0050E940(1);
    break;
  case 27:
    if (P29_Mode == 3) SetDirectorMode(1, 2, 0);
    else if (P29_Mode == 6) SetDirectorMode(1, 3, 0);
    else SetDirectorMode(1, 1, 0);
    break;
  default: break;
  }
  if (*(int32_t *)&DirectorCam != 0x11) P125_DirD17C0C = 0;
}

/* ---- 004f5e55: AddDashMessage ---- */
int32_t P125_AddDashMessage(const char *msg, int32_t lim) {
  int32_t n = P58_CntC814E8;
  void **ptrs = (void **)DebugMalloc((int)((size_t)(n + 1) * sizeof(void *)), "D:\\Driver\\Game\\MScript.c", 0x61b);
  if (ptrs == NULL) { P124_DebugLog("AddDashMessage: Unable to allocate new list for messages."); return 0; }
  int32_t *lims = (int32_t *)DebugMalloc((n + 1) * 4, "D:\\Driver\\Game\\MScript.c", 0x622);
  if (lims == NULL) {
    P124_DebugLog("AddDashMessage: Unable to allocate new list for dash timers.");
    DebugFree(ptrs); return 0;
  }
  for (int32_t i = 0; i < n; i++) { lims[i] = P58_LimC810AC[i]; ptrs[i] = P58_PtrsC816A0[i]; }
  lims[n] = lim;
  ptrs[n] = DebugMalloc((int)strlen(msg) + 1, "D:\\Driver\\Game\\MScript.c", 0x633);
  if (ptrs[n] == NULL) {
    P124_DebugLog("AddDashMessage: Unable to allocate memory for new message.");
    DebugFree(ptrs); DebugFree(lims); return 0;
  }
  strcpy((char *)ptrs[n], msg);
  if (P58_PtrsC816A0 != NULL) DebugFree(P58_PtrsC816A0);
  if (P58_LimC810AC != NULL) DebugFree(P58_LimC810AC);
  P58_CntC814E8 = n + 1;
  P58_LimC810AC = lims;
  P58_PtrsC816A0 = ptrs;
  return 1;
}

/* ---- 004b8d49: клубы в пуле 0110b260 (записи 0x3c) ---- */
void P125_SmokePuffs(const int32_t *pos, const int32_t *vel, int32_t n, uint32_t kind, int32_t blue) {
  if (G6_00B5A778 != 0 || P69_OvlOn == 0) return;
  for (int32_t k = 0; k < n; k++) {
    int32_t i = PoolNext004AC671();
    if (i < 0) return;
#ifndef RE_HOOK_BUILD
    if (i >= 200) return;
#endif
    uint8_t *r = P12_0110b260 + i * 0x3c;
    wr32(r, pos[0]); wr32(r + 4, -pos[1]); wr32(r + 8, pos[2]);
    wr32(r + 0x30, 0);
    uint32_t u = N14_Rand();
    int32_t vx, vy, vz;
    if ((int32_t)kind < 5) {
      vy = (int32_t)(u & 0x7f00) * n * 2;
      vx = vel[0] + ((int32_t)(u & 0x7f) - 0x40) * n * 0x400;
      uint32_t w = N14_Rand();
      vz = vel[2] + ((int32_t)(w & 0x7fff) - 0x4000) * n * 2;
      wr32(r + 0x28, (int32_t)(u & 0xff));
      if (blue == 0) {
        int32_t t = S_00D1192C & 7;
        r[0x34] = k_553630[t * 4]; r[0x35] = k_553630[t * 4 + 1]; r[0x36] = k_553630[t * 4 + 2];
      } else {
        r[0x34] = (uint8_t)((u & 0xf) + 0x6f); r[0x35] = 0x73; r[0x36] = 0x91;
      }
    } else {
      vy = vel[1]; vx = vel[0]; vz = vel[2];
      wr32(r + 0x28, 2);
      r[0x36] = 0x3c; r[0x35] = 0x3c; r[0x34] = 0x3c;
    }
    wr32(r + 0x2c, (int32_t)(kind & 7));
    wr32(r + 0x10, vx >> 0xc);
    wr32(r + 0x14, -(vy >> 0xc));
    wr32(r + 0x18, vz >> 0xc);
    wr16(r + 0x20, 100);
    wr16(r + 0x22, 2);
    wr16(r + 0x26, (int16_t)((P62_Frame + k) & 0x1f));
  }
}

/* ---- 0050fbf4: значения меню управления ---- */
void P125_CtrlMenuValues(void) {
  int32_t c = P13_00575ef4 == 0 ? 0 : (P13_00b87e74 == 0 ? 1 : 2);
  int32_t b = P13_00575ec0 == 0 ? 0 : (P13_00575ebc == 0 ? 1 : 2);
  int32_t a = P13_00d11880 == 0 ? 0 : (P13_00575f20 == 0 ? 1 : 2);
  const char *s2 = (const char *)re_ptr(P97_StrAddr[2]), *sd5 = (const char *)re_ptr(P97_StrAddr[0xd5]);
  if (P21_FrameFlagB == 0) snprintf(P125_FpsStr, sizeof P125_FpsStr, "%s", s2 ? s2 : "");
  else if (P21_FrameFlagA == 0) snprintf(P125_FpsStr, sizeof P125_FpsStr, "%dfps", P21_FrameMin != 0 ? 0x32 / P21_FrameMin : 0);
  else snprintf(P125_FpsStr, sizeof P125_FpsStr, "%s", sd5 ? sd5 : "");
  P116_MLevB = (P11_01270c24 - P11_0054602c) / 27000.0f;
  P116_MLevA = (P11_0125f3f8 - P11_0054602c) / 27000.0f;
  uint8_t *m = P117_MenuB;
#define K(i) (((uint32_t)(i) < 16u) ? k_575558[(i)] : 0)
  wr32(m + 0x30,  K(11 + MenuVar575EF8));
  wr32(m + 0x58,  K(8 + a));
  wr32(m + 0x80,  K(MenuVar55384C));
  wr32(m + 0xa8,  K(MenuVar553850));
  wr32(m + 0xd0,  K(MenuVar575F30));
  wr32(m + 0xf8,  K(MenuVarB201DC));
  wr32(m + 0x120, K(MenuVar55C974));
  wr32(m + 0x148, K(MenuVar575F44));
  wr32(m + 0x170, K(2 + b));
  wr32(m + 0x198, K(5 + c));
  wr32(m + 0x1c0, K(MenuVarD118C8));
  wr32(m + 0x1e8, K(MenuVar575F3C));
  wr32(m + 0x210, K(MenuVar575EE8));
  wr32(m + 0x260, K(MenuVarB31F04));
#undef K
}

/* ---- 0042d554: ребро a→b по ближней плоскости (z = +0x14), вывод x,y,z в P100_ClipOut ---- */
static void clip_put(float x, float y, float z) { P100_ClipOut[0] = x; P100_ClipOut[1] = y; P100_ClipOut[2] = z; P100_ClipOut += 0xc; }
void P125_ClipNearXY(const uint8_t *a, const uint8_t *b) {
  float N = P95_Near, za = rdf(a + 0x14), zb = rdf(b + 0x14);
  if (!(N <= za || N <= zb)) return;
  if (za < N || zb < N) {
    if (N <= za || zb < N) {
      float t = (za - N) / (za - zb);
      clip_put(rdf(a + 0xc) - (rdf(a + 0xc) - rdf(b + 0xc)) * t, rdf(a + 0x10) - (rdf(a + 0x10) - rdf(b + 0x10)) * t, 50.0f);
      P100_ClipN += 1;
    } else {
      float t = (zb - N) / fabsf(zb - za);
      clip_put(rdf(b + 0xc) - (rdf(b + 0xc) - rdf(a + 0xc)) * t, rdf(b + 0x10) - (rdf(b + 0x10) - rdf(a + 0x10)) * t, 50.0f);
      clip_put(rdf(b + 0xc), rdf(b + 0x10), zb);
      P100_ClipN += 2;
    }
  } else {
    clip_put(rdf(b + 0xc), rdf(b + 0x10), zb);
    P100_ClipN += 1;
  }
}

/* ---- 00522f4f: удар по объекту (+4 модель, +8 x, +0x10 z) ---- */
int32_t P125_DropHit(uint8_t *obj, const int32_t *vel) {
  uint32_t oa = re_addr(obj);
  for (int32_t k = 0; k < 6; k++) {
    uint8_t *d = &P101_Drops[k * 0x1c];
    if ((uint32_t)rd32(d + 0x18) == oa) { wr32(d, rd32(d) + 1); return 1; }
  }
  int32_t model = rd32(obj + 4);
  if ((G6_01136920 & 1) != 0) P69_AddScore(model);
  P97_AddTime((uint8_t *)P56_Blk84, ((uint32_t)model < 0x480u) ? P125_DropTime[model] : 0);
  if (P125_BLK(0x00c8126c) != 0 && P94_NearestObjDist() < P125_BLK(0x00c81120)) P97_AddTime((uint8_t *)P56_Blk84, 1);
  int32_t i = P12_00bde764;
  P12_00bdf980++;
  P12_00bde764 = i + 1;
#ifndef RE_HOOK_BUILD
  if ((uint32_t)i >= 6u) i = 0;
#endif
  uint8_t *d = &P101_Drops[i * 0x1c];
  wr32(d, 0);
  wr32(d + 0x18, (int32_t)oa);
  P11_00ba52d0 = fround(rdf(obj + 8));
  wr32(d + 0xc, P11_00ba52d0);
  wr16(d + 0x10, (int16_t)(vel[0] >> 10));
  wr16(d + 0x14, (int16_t)(vel[2] >> 10));
  int16_t s = rd16(d + 0x10) < 0 ? (int16_t)vel[0] : (int16_t)-(int16_t)vel[0];
  s = rd16(d + 0x14) < 0 ? (int16_t)(s + (int16_t)vel[2]) : (int16_t)(s - (int16_t)vel[2]);
  s = (int16_t)(s >> 1);
  wr16(d + 0x12, s);
  uint32_t u = N14_Rand();
  wr32(d + 4, (u & 1) == 0 ? -(int32_t)s / 2 : (int32_t)s / 2);
  wr32(d + 8, (u & 2) == 0 ? -1 : 1);
  if (rd16(d + 0x12) < -0x96) wr16(d + 0x12, (int16_t)-0x96);
  if (P12_00bde764 > 5) P12_00bde764 = 0;
  P99_ChairHit(rdf(obj + 8), rdf(obj + 0x10));
  wr32(obj + 8, (int32_t)0xcb989680);
  return 0;
}

/* ---- 004a5634: «ИМЯ = N» ---- */
void P125_ModelName(const char *line, uint16_t num) {
  char name[0x108];
  int32_t L = 0;
  const uint8_t *p = (const uint8_t *)line;
  while (*p != '=' && *p != ' ' && L < 0x100) {
    uint8_t c = *p++;
    if (0x60 < c && c < 0x7a) c = (uint8_t)(c - 0x20);
    name[L++] = (char)c;
  }
  name[L] = 0;
  while (*p != 0 && *p++ != '=') {}
  while (*p == ' ') p++;
  uint32_t v = num;
  if (sscanf((const char *)p, "%u", &v) != 1) v = num;
  uint16_t w = (uint16_t)v;
  memcpy(name + L + 1, &w, 2);
  int32_t len = L + 3;                          /* имя, ноль, u16 */
  P62_ModelCount++;
  if (P62_ModelNames == NULL) {
    uint8_t *b = (uint8_t *)DebugMalloc(len + 2, "D:\\Driver\\Game\\compiler.c", 0x585);
    if (b == NULL) { if (P62_NoErr == 0) P26_ErrorInLine("Not enough memory for\nmodel names list!"); return; }
    memset(b, 0, (size_t)(len + 2));
    P44_Copy4(b, name, (uint32_t)len);
    P125_ModelNamesSize = len + 2;
    P62_ModelNames = (const char *)b;
  } else {
    uint8_t *b = (uint8_t *)DebugMalloc(P125_ModelNamesSize + len, "D:\\Driver\\Game\\compiler.c", 0x56f);
    if (b == NULL) { if (P62_NoErr == 0) P26_ErrorInLine("Not enough memory for\nmodel names list!"); return; }
    P44_Copy4(b, P62_ModelNames, (uint32_t)(P125_ModelNamesSize - 2));
    memset(b + P125_ModelNamesSize - 2, 0, (size_t)(len + 2));
    P44_Copy4(b + P125_ModelNamesSize - 2, name, (uint32_t)len);
    DebugFree((void *)P62_ModelNames);
    P125_ModelNamesSize += len;
    P62_ModelNames = (const char *)b;
  }
}

/* ---- 004079aa: палитра (B,G,R,X) → 16 бит; P65_Blend[a][b] — ближайший к среднему цвет ---- */
static int32_t iabs(int32_t v) { return v < 0 ? -v : v; }
void P125_BlendTable(const uint8_t *pal, uint32_t *out, uint8_t key, uint8_t fill) {
  for (int32_t i = 0; i < 0x100; i++)
    out[i] = (uint32_t)((pal[i * 4 + 2] >> (P125_ShrR & 0x1f)) << (P125_ShlR & 0x1f) |
                        (pal[i * 4 + 1] >> (P125_ShrG & 0x1f)) << (P125_ShlG & 0x1f) |
                        (pal[i * 4] >> (P125_ShrB & 0x1f)) << (P125_ShlB & 0x1f));
  uint8_t *bl = (uint8_t *)P65_Blend;
  for (int32_t a = 0; a < 0x100; a++) {
    for (int32_t b = 0; b < 0x100; b++) {
      uint32_t best;
      if (b == key) best = (uint32_t)a;
      else {
        int32_t r = (pal[a * 4 + 2] >> 1) + (pal[b * 4 + 2] >> 1);
        int32_t g = (pal[a * 4 + 1] >> 1) + (pal[b * 4 + 1] >> 1);
        int32_t bb = (pal[a * 4] >> 1) + (pal[b * 4] >> 1);
        int32_t dmin = 0x7fffffff; best = 0;
        for (int32_t k = 0; k < 0x100; k++) {
          int32_t dd = iabs(pal[k * 4 + 2] - r) * 0x10 + iabs(pal[k * 4 + 1] - g) * 0x10 + iabs(pal[k * 4] - bb) * 0x10;
          if (dd < dmin) { best = (uint32_t)k; dmin = dd; if (dd < 100) break; }
        }
      }
      bl[b + a * 0x100] = (uint8_t)best;
    }
  }
  P65_ColorKey = key;
  P11_005c6760 = fill;
  memset(P65_Screen, fill, sizeof P65_Screen);   /* 0x4b000 = 640×480 */
}

/* ---- 004afa4c: обломки в P97_Debris (100 записей 0x3c) ---- */
void P125_DebrisBurst(const float *pos, int32_t n, int32_t kind) {
  if (MenuVar553850 == 0 || P69_OvlOn == 0) return;
  for (int32_t k = 0; k < n; k++) {
    int32_t i = PoolPop004AC726();
    if (i < 0) return;
#ifndef RE_HOOK_BUILD
    if (i >= 100) return;
#endif
    uint8_t *r = P97_Debris + i * 0x3c;
    wrf(r, ((float)(N14_Rand() & 0xfe) + pos[0]) - P66_C128);
    wrf(r + 4, pos[1]);
    wrf(r + 8, ((float)(N14_Rand() & 0xfe) + pos[2]) - P66_C128);
    wr32(r + 0x18, 0); wr32(r + 0x14, 0); wr32(r + 0x10, 0);
    wr16(r + 0x20, 700);
    wr16(r + 0x22, 2);
    wr32(r + 0x28, (int32_t)(N14_Rand() & 3) + 2);
    if (kind == 1) {
      uint32_t u = N14_Rand() & 3;
      if (u == 0) { r[0x2c] = 0xff; r[0x2d] = 0xff; r[0x2e] = 0xff; }
      else if (u == 1) { r[0x2c] = (uint8_t)((N14_Rand() & 0x3f) + 0x6e); r[0x2d] = 0xaa; r[0x2e] = 0x82; }
      else { r[0x2c] = 0xbe; r[0x2d] = (uint8_t)((N14_Rand() & 0x3f) + 0x82); r[0x2e] = 0x82; }
      wr16(r + 0x26, (int16_t)(N14_Rand() & 0xfe));
    } else {
      r[0x2c] = 0xff; r[0x2d] = 0xff;
      r[0x2e] = (uint8_t)((N14_Rand() & 0x3f) - 0x40);
      wr16(r + 0x26, (int16_t)(((N14_Rand() & 0x1f) - 0x10) & 0xff));
    }
    if (P19_Out68 <= 0.7f) {                  /* 00546168 */
      for (int c = 0; c < 3; c++) r[0x2c + c] = (uint8_t)(int32_t)(((double)P19_Out68 + 0.3f) * (double)r[0x2c + c]);
    }
    wr16(r + 0x34, (int16_t)(N14_Rand() & 0xfff));
    wr16(r + 0x36, (int16_t)(N14_Rand() & 0xfff));
    r[0x38] = (uint8_t)((N14_Rand() & 0x3f) - 0x40);
    r[0x39] = (uint8_t)((N14_Rand() & 0x3f) - 0x40);
    r[0x3a] = (uint8_t)kind;
  }
}

/* ---- 004b955c: объекты A (0x78) — искры/дым ---- */
void P125_ObjABurst(const int32_t *pos, const int32_t *vel, int32_t n, int32_t kind) {
  if (G6_00B5A778 != 0 || P111_SparkIcon == 0) return;
  for (int32_t k = 0; k < n; k++) {
    int32_t i = PoolPop004AC6D0();
    if (i < 0) return;
#ifndef RE_HOOK_BUILD
    if (i >= 200) return;
#endif
    uint8_t *r = P95_ObjA + i * 0x78;
    wrf(r, (float)pos[0]); wrf(r + 4, (float)pos[1]); wrf(r + 8, (float)pos[2]);
    if (kind == 2) {
      wrf(r, (float)(N14_Rand() & 0x3f) + rdf(r));
      wrf(r + 4, (float)(N14_Rand() & 0x1f) + rdf(r + 4));
      wrf(r + 8, (float)(N14_Rand() & 0x3f) + rdf(r + 8));
    }
    memcpy(r + 0x20, r, 0xc); wr32(r + 0x2c, rd32(r + 0xc));
    memcpy(r + 0x40, r, 0xc); wr32(r + 0x4c, rd32(r + 0xc));
    wr32(r + 0x68, 10);
    wr16(r + 0x6e, (int16_t)((k << 2) & 0xff));
    wr32(r + 0x60, (int32_t)(N14_Rand() & 0x3f));
    wr32(r + 0x50, kind);
    uint32_t u = N14_Rand(); int32_t vx = vel[0];
    uint32_t v = N14_Rand(); int32_t vy = vel[1];
    uint32_t w = N14_Rand(); int32_t vz = vel[2];
    wrf(r + 0x30, (float)((int32_t)(vx + ((int32_t)(u & 0x7fff) - 0x4000) * 5) >> 0xc));
    wrf(r + 0x34, (float)-((int32_t)(vy + (int32_t)(v & 0x7fff) * (kind == 0 ? 4 : 5)) >> 0xc));
    wrf(r + 0x38, (float)((int32_t)(vz + ((int32_t)(w & 0x7fff) - 0x4000) * 5) >> 0xc));
    if (kind == 0) { wr16(r + 0x64, 10); wr32(r + 0x58, 0x1e); wr32(r + 0x5c, 2); }
    else { wr16(r + 0x64, 0x28); wr32(r + 0x58, kind == 2 ? 0x3c : 0x78); wr32(r + 0x5c, 5); }
  }
}

/* ---- 004fc0d9: подбор точек маршрута (записи 0x14: +4 x, +8 y, +0xc z) ---- */
static int32_t pick_dist(const uint8_t *p) {
  int32_t dx = iabs(PlayerPosX - rd32(p + 4)), dz = iabs(PlayerPosZ - rd32(p + 0xc));
  return dx < dz ? dz + dx / 2 : dx + dz / 2;
}
void P125_PickupTick(const uint8_t *tab) {
  if (!((P14_00c810c4 == 7 || P95_B87EDC != 0) && tab != NULL)) return;
  const uint8_t *p = tab + P98_ScrFirst * 0x14;
  for (int32_t k = 0; k < 5 && k + P98_ScrFirst <= G6_00C81108; k++) {
    int32_t d = pick_dist(p);
    if (P95_B87EDC == 0 && d < 500) {
      int32_t *mr = (int32_t *)re_ptr(P113_MrkRec);
      if (mr != NULL && (mr[1] & 4) != 0) mr[0] += 0x32;
      uint8_t *o = P125_Pick + (P125_PickIdx & 3) * 0x20;
      wrf(o + 8, (float)rd32(p + 4)); wrf(o + 0xc, (float)rd32(p + 8)); wrf(o + 0x10, (float)rd32(p + 0xc));
      wr32(o + 4, P98_ScrModel);
      int32_t v[3] = { P125_Car0X / 0x1000, -0x11, P125_Car0Z / 0x1000 };
      P125_DropHit(o, v);
      P125_PickIdx = (P125_PickIdx + 1) & 3;
      int32_t s = P97_SndStart(P11_00572b40[2], -1, (float)PlayerPosX, (float)-P59_PosY, (float)PlayerPosZ);
      if (s != -1) { SoundSetPos00523F8A(s, (int32_t)P11_00572b40[4]); P48_SetVoiceVolume(s, (int32_t)P11_00572b40[3]); }
      P125_BLK(0x00c8110c) += 1;
      P98_ScrFirst += 1 + k;
      k = 0;
      P69_ScoreCpy = P125_BLK(0x00c8110c);
      if (P98_ScrFirst == 100) {
        P14_00c810c4 = 0x7fff; P16_IdleMode = 0x7fff; P56_Blk84[1] = 0x7fff;
        int32_t *rec = (int32_t *)re_ptr(P113_MrkRec);
        if (rec != NULL) { P114_Timer(rec); memcpy(P125_MrkSave, rec, sizeof P125_MrkSave); }
        return;
      }
    }
    p += 0x14;
  }
}
