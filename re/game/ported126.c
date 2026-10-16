/* v1.71: ported126 — восстановлено из Game.exe. Все функции cdecl (work/rets.py: ret без операнда).
   004efafd — LEVELS\FLAT.D3D: число записей, затем {слот u32, число u32, число×u32} → P58_Tab4EFC03 (родные указатели,
     p58_rec_t), освобождение — P58 (004efc03). В native псевдоним P40_ListPtr/P40_ListCount (тот же адрес) не пишется.
   004906f9 — начальная позиция игрока: режим 00b87eec — P48_PosToInts; CHASE (00b87e98, 00b87e38 = 0xc9 или флаги
     00b87eac/eb0 без «повтора 2») — записи ReplayData\Chase\%s.LEADER (запасная 0x41) и .PLAYER (0); иначе файл из
     P56_PathStart или старт из P56_Blk84 (00c812c0..c8, курс 00c810fc). Камера −400 над точкой, поля +0x11c..+0x138.
   004e9006 / 004e919d — капли у объектов клетки (флаг модели +8 & 0x400), обход квадратом 1500 (ряд 0x3c — со сдвигом 3000).
   004d9951 — снимок экрана: заголовок BMP — копия .data 0056046c (0x36 байт) с W/H; формат "%#04d" — в MSVC и glibc '#'
     для d игнорируется, пишем "%04d".
   004d74e0 — отладочные клавиши (P34_Keys): 0x0c/0x0d — зум, 0x58 — снимок, 1 — пауза (50e940), раскладка P36_KeyCfg[0..3] —
     дальность 01270c24 (15000..45000) и зеркало 0125f3f8 (до 42000) шагом 3000; при 00575f4c: 0x1e, 0x22, 0x21 (урон −100),
     0x18 (фронт).
   004f1745 — точки появления: P123_SideDist, до 4 записей 0x18 в 00c82440, точка камеры ±800 по курсу игрока.
   0040c6bb — как 0040c610 (P124_ShowBmp), но через P12_Fn0040DA56 + P76_TileFill (затемнение), ожидание — счётчик 005d577c.
   004e10e3 — колёса +0x78 (4 байта через 4): при отрыве — 0x32 кадров дыма P125_SmokePuffs (вид 5, 3 частицы).
   004ad244 — обломки P125_DebrisBurst у края дороги (P72_RoadWord = −1, P72_RoadLookup ≠ 0, модель без флага 0x80);
     третий аргумент 1 — остаток push 1 перед rand (по ассемблеру: add esp,0xc). */
#include "ported126.h"
#include "unported.h"
#include "engine.h"
#include "crt.h"
#include "reptr.h"
#include "cartab.h"
#include "globalsets.h"
#include "menustate.h"
#include "smallfuncs.h"
#include "smallfuncs2.h"
#include "uihandlers3.h"
#include "uihandlers4.h"
#include "widgets.h"
#include "ported4.h"
#include "ported5.h"
#include "ported6.h"
#include "ported7.h"
#include "ported8.h"
#include "ported11.h"
#include "ported12.h"
#include "ported14.h"
#include "ported16.h"
#include "ported19.h"
#include "ported27.h"
#include "ported29.h"
#include "ported34.h"
#include "ported36.h"
#include "ported42.h"
#include "ported43.h"
#include "ported44.h"
#include "ported48.h"
#include "ported54.h"
#include "ported56.h"
#include "ported58.h"
#include "ported59.h"
#include "ported61.h"
#include "ported62.h"
#include "ported72.h"
#include "ported76.h"
#include "ported77.h"
#include "ported79.h"
#include "ported88.h"
#include "ported94.h"
#include "ported95.h"
#include "ported97.h"
#include "ported98.h"
#include "ported100.h"
#include "ported101.h"
#include "ported102.h"
#include "ported117.h"
#include "ported123.h"
#include "ported124.h"
#include "ported125.h"
#include <math.h>
#include <stdio.h>
#include <string.h>

#ifndef RE_HOOK_BUILD
int32_t P126_PicNum = -1;                  /* .data 005604b4 */
int32_t P126_DebugOn = 1;                  /* .data 00575f4c */
GAME_VAR_DEF(int32_t, P126_SpawnN, 0x00c82528)
GAME_VAR_DEF(int32_t, P126_SpawnSide, 0x00c824d4)
GAME_VAR_DEF(int32_t, P126_SpawnAxis, 0x00c824d8)
GAME_VAR_DEF(int32_t, P126_SpawnT, 0x00c8252c)
GAME_VAR_DEF(p126_spawn_t, P126_Spawn, 0x00c82440)
GAME_VAR_DEF(float, P126_TgtY, 0x00c82514)
GAME_VAR_DEF(float, P126_TgtW, 0x00c8251c)
GAME_VAR_DEF(float, P126_PtY, 0x00c824b4)
GAME_VAR_DEF(float, P126_PtW, 0x00c824bc)
GAME_VAR_DEF(float, P126_SideY, 0x00c824c4)
GAME_VAR_DEF(float, P126_SideW, 0x00c824cc)
#endif

static int32_t rd32(const void *p) { int32_t v; memcpy(&v, p, 4); return v; }
static void wr32(void *p, int32_t v) { memcpy(p, &v, 4); }
static int16_t rd16(const void *p) { int16_t v; memcpy(&v, p, 2); return v; }
static void wrf(void *p, float v) { memcpy(p, &v, 4); }
static float rdf(const void *p) { float v; memcpy(&v, p, 4); return v; }
static int32_t fround(float v) { return (int32_t)lrintf(v); }   /* fistp */
#define P126_BLK(off) (*(int32_t *)&P56_Blk84[((off) - 0x00c810c0) / 4])   /* поля внутри P56_Blk84 */
#define P126_CAR(i)   ((uint8_t *)&P99_Cars[(i)])

/* ---- 004efafd ---- */
void P126_ReadMapPals(const char *name) {
  void *f = g_fopen(name, "rb");
  if (f == NULL) return;
  int32_t n = 0;
  g_fread(&n, 1, 4, f);
  if (n < 0) n = 0;                                       /* защита: в оригинале нет */
  P58_Cnt4EFC03 = n;
  p58_rec_t *t = (p58_rec_t *)P98_DebugMalloc(n * 0xc, "D:\\Driver\\Game\\map.c", 0xd88);
  P58_Tab4EFC03 = t;
  if (t == NULL) { P58_Cnt4EFC03 = 0; g_fclose(f); return; }   /* защита */
  for (int32_t i = 0; i < n; i++) {
    g_fread(&t[i].a, 1, 4, f);
    g_fread(&t[i].c, 1, 4, f);
    t[i].p = P98_DebugMalloc(t[i].c << 2, "D:\\Driver\\Game\\map.c", 0xd8e);
    if (t[i].p != NULL) g_fread(t[i].p, t[i].c, 4, f);
  }
  g_fclose(f);
}

/* ---- 004906f9 ---- */
static void read_rec(uint8_t *dst, const char *name) {
  void *f = g_fopen(name, "rb");
  if (f == NULL) return;                                  /* защита: в оригинале fread(NULL) */
  P27_ReadChunked(dst, 1, 0x148, f);
  g_fclose(f);
}
void P126_PlayerStart(void) {
  int32_t q[3];
  uint8_t *me = P126_CAR(S_00D11878);
  char nm[64];
  if (G6_00B87EEC == 0) {
    if (P62_HudOff2 == 0) {
      if ((G6_00B87EAC == 0 && G6_00B87EB0 == 0) || (G6_00B87EA0 != 0 && P88_Mode575 == 2)) {
        if (P126_BLK(0x00c81278) == 0) {
          void *f = g_fopen((const char *)&P56_PathStart, "rb");
          if (f == NULL) {
            q[0] = q[1] = q[2] = 0;
            P126_CAR(0)[2] = 0;
            P56_ObjInit(P126_CAR(0), q);
            P94_HeadingI = 0x400;
            P59_ObjDir(P126_CAR(0), 0);
          } else {
            P14_Fn0048DB65(P126_CAR(0), 0x148);
            P27_ReadChunked(P126_CAR(0), 1, 0x148, f);
            g_fclose(f);
            P126_CAR(0)[2] = 0;
          }
        } else {
          q[0] = P126_BLK(0x00c812c0); q[1] = P126_BLK(0x00c812c4); q[2] = P126_BLK(0x00c812c8);
          P56_ObjInit(P126_CAR(0), q);
          P94_HeadingI = P126_BLK(0x00c810fc);
          P126_CAR(0)[2] = (uint8_t)P95_BDF9D4;
          P59_ObjDir(P126_CAR(0), 0);
        }
      } else {
        snprintf(nm, sizeof nm, "ReplayData\\Chase\\%s.LEADER", (const char *)&P56_PathName);
        read_rec(P126_CAR(0x41), nm);
        P126_CAR(0x41)[2] = 0;
        snprintf(nm, sizeof nm, "ReplayData\\Chase\\%s.PLAYER", (const char *)&P56_PathName);
        read_rec(P126_CAR(0), nm);
        P126_CAR(0)[2] = (uint8_t)P95_BDF9D4;
      }
    } else if (P11_00b87e38 == 0xc9) {
      snprintf(nm, sizeof nm, "ReplayData\\Chase\\%s.LEADER", (const char *)&P56_PathName);
      read_rec(P126_CAR(0x41), nm);
      P126_CAR(0x41)[2] = 0;
      snprintf(nm, sizeof nm, "ReplayData\\Chase\\%s.PLAYER", (const char *)&P56_PathName);
      read_rec(P126_CAR(0), nm);
      P126_CAR(0)[2] = (uint8_t)P95_BDF9D4;
    } else {
      wr32(me + 0xc8, -10000); wr32(me + 0xcc, -500); wr32(me + 0xd0, -21504);
      q[0] = rd32(me + 0xc8); q[1] = rd32(me + 0xcc); q[2] = rd32(me + 0xd0);
      P126_CAR(0)[2] = 0;
      P56_ObjInit(me, q);
      P94_HeadingI = 0x400;
    }
  } else {
    P48_PosToInts(q);
    wr32(me + 0xc8, q[0]); wr32(me + 0xcc, q[1]); wr32(me + 0xd0, q[2]);
    P56_ObjInit(me, q);
    P94_HeadingI = 0x400;
  }
  if (G6_00B87EA0 != 0 && P88_Mode575 == 2) memcpy(P126_CAR(0x41), P126_CAR(0), 0x148);
  int32_t x = P88_ObjX, z = P88_ObjZ;
  if (G6_00B87EAC == 0 && G6_00B87EB0 == 0) { x = rd32(me + 0xc8); z = rd32(me + 0xd0); }
  P44_CamZ = (float)z; P44_CamX = (float)x; P44_CamY = -400.0f;
#ifndef RE_HOOK_BUILD
  P59_VZ = P44_CamZ; P59_VX = P44_CamX; P59_VY = P44_CamY;   /* псевдонимы 00b1c270..78 */
#endif
  uint8_t *c0 = P126_CAR(0);
  wr32(c0 + 0x138, 0); wr32(c0 + 0x130, 0); wr32(c0 + 0x12c, 0); wr32(c0 + 0x128, 0);
  wr32(c0 + 0x124, 0); wr32(c0 + 0x120, 0); wr32(c0 + 0x11c, 0);
}

/* ---- 004e9006 ---- */
void P126_DropsAt(const float *pos) {
  int32_t x = fround(((float)P42_CellX + pos[0]) * P42_CellScale);
  int32_t z = fround(((float)P42_CellY + pos[2]) * P42_CellScale);
  P11_00ba52d0 = z;
  int32_t N = P54_GridN;
  if (N <= 0 || G6_00D01268 == NULL || G6_00CE0F20 == NULL || G6_00D00208 == NULL) return;   /* защита */
  int32_t bx = x / N, bz = z / N;
  int32_t slot = (bx & 1) + (bz & 1) * 2;
  int32_t cx = x - bx * N, cz = z - bz * N;
  int32_t cell = slot * N * N + cx + cz * N;
  if (cell < 0 || cell >= 4 * N * N) return;                                                   /* защита */
  int32_t node = ((int32_t *)G6_00D01268)[cell];
  for (int32_t guard = 0; node != -1 && node >= 0 && node < 4 * 0x5000 && guard < 0x5000; guard++) {   /* защита */
    const int32_t *nd = (const int32_t *)((uint8_t *)G6_00CE0F20 + (size_t)node * 8);
    uint8_t *o = (uint8_t *)G6_00D00208 + (size_t)nd[0] * 0x20;
    int32_t mi = rd32(o + 4);
    uint32_t m = ((uint32_t)mi < 1126u) ? P79_ModelTab[mi] : 0;
    if (m != 0 && (rd32((uint8_t *)P79_PTR(m) + 8) & 0x400) != 0) {
      int32_t vel[4] = { 0, 0, 0, 0 };
      int32_t r = (int32_t)N14_Rand();
      vel[0] = -0x32 - r % 0x32;
      P125_DropHit(o, vel);
    }
    node = nd[1];
  }
}

/* ---- 004e919d ---- */
void P126_DropScan(int32_t unused) {
  (void)unused;
  float *p = (float *)&P76_ColObj;   /* +0 x, +8 z */
  const float d = 1500.0f, s = 3000.0f;   /* .data 005469c4 / 0054604c */
  if (P76_Angle == 10) {
    P126_DropsAt(p);
  } else if (P76_Angle == 0x1e) {
    p[0] += d; P126_DropsAt(p);
    p[2] += d; P126_DropsAt(p);
    p[0] -= d; P126_DropsAt(p);
    p[0] -= d; P126_DropsAt(p);
    p[2] -= d; P126_DropsAt(p);
    p[2] -= d; P126_DropsAt(p);
    p[0] += d; P126_DropsAt(p);
    p[0] += d; P126_DropsAt(p);
    p[2] += d; p[0] -= d;
  } else if (P76_Angle == 0x3c) {
    p[0] += s; p[2] += s;
    for (int i = 0; i < 4; i++) { p[0] -= d; P126_DropsAt(p); }
    for (int i = 0; i < 4; i++) { p[2] -= d; P126_DropsAt(p); }
    for (int i = 0; i < 4; i++) { p[0] += d; P126_DropsAt(p); }
    for (int i = 0; i < 4; i++) { p[2] += d; P126_DropsAt(p); }
    p[0] -= s; p[2] -= s;
  }
}

/* ---- 004d9951 ---- */
static const uint8_t k_bmphdr[0x36] = {   /* .data 0056046c */
  0x42,0x4d,0x36,0x60,0x00,0x00,0x00,0x00,0x00,0x00,0x36,0x00,0x00,0x00,0x28,0x00,0x00,0x00,0x80,0x00,0x00,0x00,0x40,0x00,
  0x00,0x00,0x01,0x00,0x18,0x00,0x00,0x00,0x00,0x00,0x00,0x60,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
  0x00,0x00,0x00,0x00,0x00,0x00 };
void P126_ScreenShot(void) {
  char nm[32];
  if (P126_PicNum == -1) {
    P126_PicNum = 1;
    for (;;) {
      snprintf(nm, sizeof nm, "PIC_%04d.BMP", (int)P126_PicNum);
      void *f = g_fopen(nm, "rb");
      if (f == NULL) break;
      g_fclose(f);
      P126_PicNum++;
    }
  }
  uint8_t h[0x36];
  memcpy(h, k_bmphdr, sizeof h);
  h[0x12] = (uint8_t)P19_ScrW; h[0x13] = (uint8_t)((uint32_t)P19_ScrW >> 8);
  h[0x16] = (uint8_t)P19_ScrH; h[0x17] = (uint8_t)((uint32_t)P19_ScrH >> 8);
#ifdef RE_HOOK_BUILD
  memcpy((void *)(uintptr_t)0x0056046c, h, sizeof h);   /* оригинал правит .data на месте */
#endif
  snprintf(nm, sizeof nm, "PIC_%04d.BMP", (int)P126_PicNum);
  void *f = g_fopen(nm, "wb");
  if (f == NULL) return;
  uint8_t *buf = (uint8_t *)P98_DebugMalloc(P19_ScrW * P19_ScrH * 3, "D:\\Driver\\Game\\general.c", 0x75b);
  if (buf != NULL) {
    P97_LfbSnap(buf);
    g_fwrite(h, 1, 0x36, f);
    g_fwrite(buf, 3, (size_t)(P19_ScrW * P19_ScrH), f);
    P98_DebugFree(buf);
  }
  g_fclose(f);
  P126_PicNum++;
}

/* ---- 004d74e0 ---- */
void P126_DebugKeys(int32_t unused) {
  (void)unused;
  if (P34_Keys[0x0c] != 0) Zoom_00425E9E();
  if (P34_Keys[0x0d] != 0) P12_Fn00425EE0();
  if (IsFlagSetNotMasked_004E383A(0x58) != 0) P126_ScreenShot();
  if (G6_00B5A778 != 0) return;
  if (IsFlagSetNotMasked_004E383A(1) != 0 && P29_Mode == 0) SetLatchValue0050E940(1);
  P98_FreeCamKeys();
  int set = 0;
  if (P34_Keys[P36_KeyCfg[0]] != 0 && 15000.0f < P11_01270c24) { P11_01270c24 -= 3000.0f; P100_MirrorMask(); set = 1; }
  if (P34_Keys[P36_KeyCfg[1]] != 0 && P11_01270c24 < 45000.0f) { P11_01270c24 += 3000.0f; P100_MirrorMask(); set = 1; }
  if (P34_Keys[P36_KeyCfg[2]] != 0 && 15000.0f < P11_0125f3f8) { P11_0125f3f8 -= 3000.0f; P101_MirrorMaskR(P11_0125f3f8); set = 1; }
  if (P34_Keys[P36_KeyCfg[3]] != 0 && P11_0125f3f8 < 42000.0f) { P11_0125f3f8 += 3000.0f; P101_MirrorMaskR(P11_0125f3f8); set = 1; }
  (void)set;
  /* 00575ef8 = 4 после каждого изменения — во все native-псевдонимы */
  if (set) { P11_00575ef8 = 4;
#ifndef RE_HOOK_BUILD
    MenuVar575EF8 = 4; G00575EF8 = 4;
#endif
  }
  if (P126_DebugOn == 0) return;
  if (IsFlagSetNotMasked_004E383A(0x1e) != 0) P12_Fn004DC8EA();
  if (IsFlagSetNotMasked_004E383A(0x22) != 0) P95_B87E14 ^= 1;
  if (P34_Keys[0x21] != 0) {
    uint8_t *c0 = P126_CAR(0);
    int32_t sum = 0;
    for (int i = 0; i < 6; i++) {
      int32_t v = rd32(c0 + 0x11c + 4 * i);
      v = (v < 0x65) ? 0 : v - 100;
      wr32(c0 + 0x11c + 4 * i, v);
      sum += v;
    }
    G00D078F8 = sum;
    AddUnique_004C1F9B(-1);
    GlobalSet004C09B9();
  }
  if (P34_KeysPrev[0x18] == 0 && P34_Keys[0x18] != 0) P77_C7D850 ^= 1;
}

/* ---- 004f1745 ---- */
void P126_SpawnInit(void) {
  uint8_t *r = P126_Spawn;
  int16_t delay = 0;
  P123_SideDist();
  uint32_t a = (uint32_t)(-(int32_t)P94_Heading) & 0xfffu;
  float c = P43_Sin[a + 0x400], s = P43_Sin[a];
  if (4 < P126_SpawnN) P126_SpawnN = 4;
  for (int32_t i = 0; i < P126_SpawnN; i++, r += 0x18) {
    if (P123_TgtMode == 1) {
      wrf(r + 8, P123_SideX); wrf(r + 0xc, P126_SideY); wrf(r + 0x10, P123_SideZ); wrf(r + 0x14, P126_SideW);
    } else {
      wrf(r + 8, P123_TgtX); wrf(r + 0xc, P126_TgtY); wrf(r + 0x10, P123_TgtZ); wrf(r + 0x14, P126_TgtW);
      if (P126_SpawnAxis == 0) wrf(r + 8, (float)(int32_t)((Rand_004D9078() & 0x1ff) - 0x100) + rdf(r + 8));
      else wrf(r + 0x10, (float)(int32_t)((Rand_004D9078() & 0x1ff) - 0x100) + rdf(r + 0x10));
    }
    memcpy(r + 2, &delay, 2);
    r[1] = (P126_SpawnSide == 0) ? 1 : 2;
    r[0] = 1;
    int32_t n = P43_AnimTab[r[1]];
    wr32(r + 4, n != 0 ? (int32_t)Rand_004D9078() % n : 0);   /* защита от деления на 0 */
    if (P126_SpawnSide == 0) delay = (int16_t)(delay + 0x28 + (Rand_004D9078() & 0xf));
    else delay = (int16_t)(delay + 0x14 + (Rand_004D9078() & 0xf));
  }
  uint8_t *me = P126_CAR(0);
  float k = (P123_SideB == 0) ? 800.0f : -800.0f;   /* .data 005469e0 / 005469f8 */
  P61_OffX = k * c + (float)rd32(me + 0xc8);
  P61_OffZ = k * s + (float)rd32(me + 0xd0);
  float pos[3] = { P61_OffX, P61_OffY, P61_OffZ };
  int32_t h = P100_RoadHeightF(pos);
  P61_OffY = (float)(-P62_C82434 - h);
  P59_Mode1137324 = 7;
#ifndef RE_HOOK_BUILD
  G2_01137324 = 7;
#endif
  if (P123_TgtMode != 0) {
    P123_SideX = P123_PtX; P126_SideY = P126_PtY; P123_SideZ = P123_PtZ; P126_SideW = P126_PtW;
  }
  P126_SpawnT = 0x32;
  P98_C824A0 = 1;
}

/* ---- 0040c6bb ---- */
void P126_ShowBmpFade(const char *name, int32_t wait) {
  if (P117_ClipFn) P117_ClipFn(0, 0, P19_ScrW, P19_ScrH);
  uint8_t *buf = (uint8_t *)P98_DebugMalloc(0x12c000, "D:\\Driver\\Game\\frontend\\frontend.c", 0x1f7);
  if (buf == NULL) return;
  if (P124_ReadBmp(name, buf) != 0) {
    P12_Fn0040DA56(re_addr(buf));
    for (float v = 0.0f; v < 1.0f; v += 0.05f) P76_TileFill(v);
    P76_TileFill(1.0f); P76_TileFill(1.0f); P76_TileFill(1.0f); P76_TileFill(1.0f);
    StartTimer004086B4();
    while (wait > MenuCounter5D577C && P48_AnyKey() == 0) {}
    StopTimer4086EA();
    for (float v = 1.0f; 0.0f < v; v -= 0.05f) P76_TileFill(v);
    P76_TileFill(0.0f); P76_TileFill(0.0f); P76_TileFill(0.0f); P76_TileFill(0.0f);
  }
  P98_DebugFree(buf);
}

/* ---- 004e10e3 ---- */
void P126_WheelSmoke(uint8_t *car) {
  for (int i = 0; i < 4; i++)
    if (car[0x78 + i * 4] != 0) { P102_D06A00 = 0; P102_D0DD84 = 1; return; }
  if (P102_D0DD84 != 0) {
    P102_D0DD84 = 0;
    P102_D06A00 = 0x32;
    AddVelocity004E122C((int32_t *)car);
  }
  if ((uint8_t)P102_D06A00 != 0) {
    uint8_t b = (uint8_t)((uint8_t)P102_D06A00 - 1);
    P102_D06A00 = b;
    if (b < 0x2d && (uint8_t)((uint8_t)N14_Rand() & 0x3f) < b) {
      int32_t vel[4] = { 0, 0, 0, 0 };
      int32_t pos[3];
      pos[0] = rd32(car + 0xc8) - 0x100 + (int32_t)(N14_Rand() & 0x1ff);
      pos[1] = rd32(car + 0xcc) - 200;
      pos[2] = rd32(car + 0xd0) - 0x100 + (int32_t)(N14_Rand() & 0x1ff);
      P125_SmokePuffs(pos, vel, 3, 5, car[2]);
    }
  }
}

/* ---- 004ad244 ---- */
void P126_KerbDebris(uint8_t *car) {
  if (P62_HudOff2 != 0 || S_010FFA24 >= 0x50) return;
  uint32_t a = (uint32_t)(((P62_Frame & 2) == 0) ? rd16(car + 0xea) - 100 : rd16(car + 0xea) + 100) & 0xfffu;
  float pos[3];
  pos[0] = 10000.0f * P43_Sin[a] + (float)rd32(car + 0xc8);        /* .data 0054615c */
  pos[2] = 10000.0f * P43_Sin[(a + 0x400) & 0xfff] + (float)rd32(car + 0xd0);
  int32_t x = fround(pos[0]), z = fround(pos[2]);
  P11_00ba52d0 = z;
  if ((int16_t)P72_RoadWord(x, z) != -1) return;
  if (P72_RoadLookup(x, z) == 0) return;
  uint32_t m = (P72_Id < 1126u) ? P79_ModelTab[P72_Id] : 0;
  if (m == 0 || (rd16((uint8_t *)P79_PTR(m) + 2) & 0x80) != 0) return;
  pos[1] = (float)(-P72_Low);
  P125_DebrisBurst(pos, (int32_t)(N14_Rand() & 7), 1);
}
