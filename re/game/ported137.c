#include "drawdist.h"
#include <stdlib.h>
/* v1.82: ported137 — см. ported137.h.
   004d4663 — конец уровня: если удаётся открыть STARTPOS.X ("wb"), у записи игрока обнуляются скорости/силы
     (+0x40..+0x70 кроме +0x64/+0x74, +0x5c = −0x2aaa, +0x78..+0x84, +0xf8/+0xfc, +0x10c..+0x138) и запись 0 (sizeof) пишется в файл;
     затем освобождение карты (004efc03, 004eb46a, 004ece1a, 004ed5d2, 0051aacd), повторов (00519408 при 00c4d70c ≠ 0 или 00b87ea0),
     CD (00524873/00524763 при 00b87e90), буферов 00b5a90c..00b31f00 (DebugFree), списков и скриптов; при 00c810c4 = 0x8000 —
     0048a940(00bdf9c0, 00c81690, 00c81694), затем −1 в оба; трейлы 004fbfad/004fc57b по флагам; 00d07790 = 0; 004e3b3c.
   004f3490 — файл .MCD: [флаг узлов][число узлов → 00c821a0][число кадров]; при флаге — смещения узлов (x,y,z → x,y,z,1; узел 0 — 0)
     и 0x30 × 8 байт узлов 00c82020. Кадр: x,y,z (12 байт) + узлы по 16 байт. Кадры вне [skip_a, n − (skip_a + skip_b)) читаются
     впустую (при skip_a = 0 / skip_b = 0 соответствующая граница не действует). Выход: [0, y, z − z_пред, 1] + узлы [x,y,z,1,w].
   004f388e — модели PED1..4BASE/HEAD (для городов 0–1 четвёртые — PED1*), разности HEAD − BASE; 4 буфера 0x80002 (motion_c.c, 0x101)
     в P54_Tab4; WALK/RUN/DIVE/SITTING.MCD (тип 0 при 00bdfa58 ≠ 0 — RUSSJUMP.MCD), длины в P103_PathLen; длина суммы смещений кадров
     (x,y,z заголовка кадра, шаг 0x10 + узлы·0x14) → 00c823c0. Аргументы 004ec837 восстановлены по push.
   0040d07b — FRONTEND.TSD: "TSD ", версия (float), 8 байт (+4 = 0x100, +6 = число страниц); палитры: версия 1.0 — две по 0x400
     (01252fe0, 01252be0), иначе список (номер, номер, 0x400); первый проход — заголовки блоков (0x14, при версии > 1 — 2 байта
     перед ним), сумма имён; арена страниц (n·0x10000 + 0xffff, выравнивание 64 КБ, P41_Offset), таблица имён (имён·16) в P54_MapAPtr;
     второй проход — блоки 0040d4b3, имена 0040d56c, страница 0x10000 из блока + hdr[2] в арену, P65_Texs[k].
   004a1037 — машина car (rec — запись трафика или −1): отсечение для режимов камеры 8/2 и зеркала; видимость клетки (кроме режима 6);
     очередь пятен фар (радиус модели · 2.5); матрица P98_CarMat[car] из int16 ·1/4096 (строки 0 и 2 со сменой знака);
     позиция − камера → вид; затухание по z (1000 .. 5500/1500); ближе 15000 (или 011373c0): тень 00520278, фары, колёса, огни, пыль,
     дым, искры, обломки, брызги воды (дорога с флагом 0x80 ниже уровня), следы; на время рисования поля модели +0x20/+0x24/(+0x2c)
     подменяются на буферы машины 00dbb580/0107c3e0/00e006c0; дальше — LOW-модель.
   Отступления native: 004a1037 — подмена полей модели только если буфер машины представим ссылкой арены (P79_PTR(P79_OFF(p)) == p),
     очередь пятен фар не длиннее 65; 0040d07b — не больше 64 палитр/16 страниц P65_Texs, сбой 0040d4b3 — выход 0 (файл уже закрыт),
     указатель арены — re_addr; 004f3490 — смещений узлов не больше 32; 004d4663 — арена страниц освобождается, только если её выделил
     P137_LoadTsd. */
#include "ported150.h"
#include "ported139.h"
#include "ported138.h"
#include "ported137.h"
#include <string.h>
#include <math.h>
#include <stdio.h>
#include "crt.h"
#include "reptr.h"
#include "cartab.h"
#include "unported.h"
#include "engine.h"
#include "director.h"
#include "smallfuncs.h"
#include "smallfuncs2.h"
#include "uihandlers2.h"
#include "menustate.h"
#include "ported4.h"
#include "ported5.h"
#include "ported6.h"
#include "ported11.h"
#include "ported12.h"
#include "ported14.h"
#include "ported20.h"
#include "ported25.h"
#include "ported26.h"
#include "ported27.h"
#include "ported28.h"
#include "ported35.h"
#include "ported36.h"
#include "ported41.h"
#include "ported44.h"
#include "ported46.h"
#include "ported54.h"
#include "ported56.h"
#include "ported58.h"
#include "ported59.h"
#include "ported60.h"
#include "ported62.h"
#include "ported65.h"
#include "ported72.h"
#include "ported73.h"
#include "ported76.h"
#include "ported78.h"
#include "ported79.h"
#include "ported82.h"
#include "ported84.h"
#include "ported95.h"
#include "ported97.h"
#include "ported98.h"
#include "ported99.h"
#include "ported100.h"
#include "ported101.h"
#include "ported102.h"
#include "ported103.h"
#include "ported106.h"
#include "ported119.h"
#include "ported120.h"
#include "ported122.h"
#include "ported123.h"
#include "ported124.h"
#include "ported125.h"
#include "ported133.h"
#include "ported136.h"

#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P137_McdSkipA")
#undef P137_McdSkipA
#pragma push_macro("P137_McdSkipA") /*gvi*/
#undef P137_McdSkipA /*gvi*/
p137_i5_t P137_McdSkipA;
#pragma pop_macro("P137_McdSkipA") /*gvi*/
#pragma pop_macro("P137_McdSkipA")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P137_McdSkipB")
#undef P137_McdSkipB
#pragma push_macro("P137_McdSkipB") /*gvi*/
#undef P137_McdSkipB /*gvi*/
p137_i5_t P137_McdSkipB;
#pragma pop_macro("P137_McdSkipB") /*gvi*/
#pragma pop_macro("P137_McdSkipB")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P137_PathDist")
#undef P137_PathDist
#pragma push_macro("P137_PathDist") /*gvi*/
#undef P137_PathDist /*gvi*/
p137_f4_t P137_PathDist;
#pragma pop_macro("P137_PathDist") /*gvi*/
#pragma pop_macro("P137_PathDist")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P137_PedHeadA")
#undef P137_PedHeadA
#pragma push_macro("P137_PedHeadA") /*gvi*/
#undef P137_PedHeadA /*gvi*/
int32_t P137_PedHeadA;
#pragma pop_macro("P137_PedHeadA") /*gvi*/
#pragma pop_macro("P137_PedHeadA")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P137_PedHeadB")
#undef P137_PedHeadB
#pragma push_macro("P137_PedHeadB") /*gvi*/
#undef P137_PedHeadB /*gvi*/
int32_t P137_PedHeadB;
#pragma pop_macro("P137_PedHeadB") /*gvi*/
#pragma pop_macro("P137_PedHeadB")
#endif

#ifdef RE_HOOK_BUILD
#  define P137_DUST_LIM (*(int32_t *)0x00575ee0)
#else
static int32_t p137_dust_lim = 7000;                     /* .data 00575ee0 */
#  define P137_DUST_LIM p137_dust_lim
static uint8_t *p137_tsd;                                /* арена страниц FRONTEND.TSD */
#endif

static uint32_t p137_u(float f) { uint32_t u; memcpy(&u, &f, 4); return u; }
static float p137_f(uint32_t u) { float f; memcpy(&f, &u, 4); return f; }
static int32_t p137_rd(const void *p) { int32_t v; memcpy(&v, p, 4); return v; }

/* ---- 004d4663 ---- */
#define P137_FREE(v) do { if ((v) != 0) { P98_DebugFree((void *)(v)); (v) = 0; } } while (0)
void P137_LevelEnd(void) {
  void *f = g_fopen("STARTPOS.X", "wb");
  if (f != NULL) {
    p99_car_t *c = &P99_Cars[0];
    c->f138 = 0; c->f130 = 0; c->f12c = 0; c->f128 = 0;
    c->vel[2] = 0; c->vel[1] = 0; c->vel[0] = 0;
    memset(c->f78, 0, sizeof(c->f78));
    c->ff8 = 0; c->ffc = 0; c->f10c = 0; c->f114 = 0; c->f118 = 0; c->speed = 0;
    for (int i = 0; i < 7; i++) c->f40[i] = 0;
    c->f40[7] = (int32_t)0xffffd556;
    c->f40[8] = 0; c->f40[10] = 0; c->f40[11] = 0; c->f40[12] = 0;
    g_fwrite(c, 1, sizeof(P99_Cars[0]), f);
    g_fclose(f);
  }
  P58_FreeRecs();
  FreeMapBuffer400000();
  FreeMapBufs004ECE1A();
  FreeMapBuffer300000();
  P54_FreeRoadbits();
  if (P36_PadMode != 0 || G6_00B87EA0 != 0) P139_ReplayEnd();
  if (Q00B87E90 != 0) { P25_CDStop(); P25_CDClose(); }
  FreeBufferD17EC8();
  P137_FREE(P46_MapBufB);
  P137_FREE(P54_MapAPtr);
#ifdef RE_HOOK_BUILD
  if (P41_Arena != 0) { P98_DebugFree((void *)(uintptr_t)P41_Arena); P41_Arena = 0; }
#else
  if (P41_Arena != 0) {
    if (p137_tsd != NULL && re_ptr(P41_Arena) == (void *)p137_tsd) { P98_DebugFree(p137_tsd); p137_tsd = NULL; }
    P41_Arena = 0;
  }
#endif
  P137_FREE(P54_MapBPtr);
  P137_FREE(P62_MapBuf);
  P137_FREE(P46_MapBufA);
  if (P56_EulerTab != 0) { P98_DebugFree(P56_EulerTab); P56_EulerTab = 0; UiVar00B1C280 = 0; }
  P137_FREE(P20_Names);
  P137_FREE(P78_VertsA);
  P137_FREE(P78_VertsB);
  P137_FREE(P99_C80880);
  P137_FREE(P100_Mirror);
  P58_FreeList();
  P54_FreeTab4();
  P98_ScriptFreeAll();
  FreeDirectorData();
  Reset004D600B();
  FreeBuffer_004F30E6();
  if (P14_00c810c4 == 0x8000) P150_PlayFmv(G6_00BDF9C0, P125_C81690, P125_C81694);
  P125_C81690 = -1;
  P125_C81694 = -1;
  P99_ScriptFree();
  if (P95_B87EE0 != 0) P138_TrailEnd();
  if (P95_B87EDC != 0) FreeBuf004FC57B();
  P35_PadX = 0;
  P35_UpdateForce();
}

/* ---- 004f3490 ---- */
int32_t P137_LoadMcd(const char *name, void *dst, int32_t skip_a, int32_t skip_b) {
  char msg[0x100];
  int32_t n = 0, flag = 0, frames = 0;
  uint32_t *o = (uint32_t *)dst;
  snprintf(msg, sizeof(msg), "Attempting to load file: %s", name);
  P124_DebugLog(msg);
  void *f = g_fopen(name, "rb");
  if (f == NULL) return 0;
  P27_ReadChunked(&flag, 4, 1, f);
  P27_ReadChunked(&P12_00c821a0, 4, 1, f);
  P27_ReadChunked(&frames, 4, 1, f);
  if (flag != 0) {
    for (int32_t i = 0; i < P12_00c821a0; i++) {
      uint32_t v[3];
      P27_ReadChunked(v, 0xc, 1, f);
      if (i < 32) { memcpy(&P100_PartOfs[i * 4], v, 0xc); P100_PartOfs[i * 4 + 3] = 1.0f; }
    }
    P100_PartOfs[0] = 0.0f; P100_PartOfs[1] = 0.0f; P100_PartOfs[2] = 0.0f;
    P27_ReadChunked(P100_PartNodes, 8, 0x30, f);
  }
  float zprev = 0.0f;
  for (int32_t k = 0; k < frames; k++) {
    uint32_t h[3], nd[4];
    P27_ReadChunked(h, 0xc, 1, f);
    if ((skip_a == 0 || skip_a <= k) && (skip_b == 0 || k < frames - (skip_a + skip_b))) {
      float z = p137_f(h[2]);
      if (n == 0) zprev = z;
      o[0] = 0; o[1] = h[1]; o[2] = p137_u(z - zprev); o[3] = 0x3f800000u;
      o += 4;
      zprev = z;
      n++;
      for (int32_t j = 0; j < P12_00c821a0; j++) {
        P27_ReadChunked(nd, 0x10, 1, f);
        o[0] = nd[0]; o[1] = nd[1]; o[2] = nd[2]; o[3] = 0x3f800000u; o[4] = nd[3];
        o += 5;
      }
    } else {
      for (int32_t j = 0; j < P12_00c821a0; j++) P27_ReadChunked(nd, 0x10, 1, f);
    }
  }
  g_fclose(f);
  return n;
}

/* ---- 004f388e ---- */
static const char *const p137_mcd[4] = { "WALK.MCD", "RUN.MCD", "DIVE.MCD", "SITTING.MCD" };   /* .data 00563714 */
int32_t P137_MotionInit(void) {
  P124_DebugLog("\nAttempting to initialise motion capture data...");
  P106_PartOn = 1;
  P73_CF56BC = P20_FindNameNoCase("PED1BASE");
  P73_D00214 = P20_FindNameNoCase("PED2BASE");
  P100_PartModelA = P20_FindNameNoCase("PED3BASE");
  P100_PartModelB = P20_FindNameNoCase(D_00b87e30 < 2 ? "PED1BASE" : "PED4BASE");
  P100_PartRotA = P20_FindNameNoCase("PED1HEAD");
  P100_PartRotB = P20_FindNameNoCase("PED2HEAD");
  P137_PedHeadA = P20_FindNameNoCase("PED3HEAD");
  P137_PedHeadB = P20_FindNameNoCase(D_00b87e30 < 2 ? "PED1HEAD" : "PED4HEAD");
  if (P73_CF56BC == -1 || P73_D00214 == -1 || P100_PartRotA == -1 || P100_PartRotB == -1) {
    P106_PartOn = 0;
    P124_DebugLog("Could not find required models.  Pedestrians have been disabled.");
    return 0;
  }
  P100_PartRotA -= P73_CF56BC;
  P100_PartRotB -= P73_D00214;
  P137_PedHeadA -= P100_PartModelA;
  P137_PedHeadB -= P100_PartModelB;
  for (int i = 0; i < 4; i++) P54_Tab4[i] = NULL;
  for (int i = 0; i < 4; i++) {
    P54_Tab4[i] = P98_DebugMalloc(0x80002, "D:\\Driver\\Game\\motion_c.c", 0x101);
    if (P54_Tab4[i] == NULL) { P106_PartOn = 0; return 0; }
    if (i == 0 && MenuOptBDFA58 != 0)
      P103_PathLen[0] = P137_LoadMcd("RUSSJUMP.MCD", P54_Tab4[0], P137_McdSkipA[0], P137_McdSkipB[0]);
    else
      P103_PathLen[i] = P137_LoadMcd(p137_mcd[i], P54_Tab4[i], P137_McdSkipA[i], P137_McdSkipB[i]);
    if (P103_PathLen[i] == 0) {
      P106_PartOn = 0;
      P124_DebugLog("Unable to Load file!  Pedestrians have been disabled.");
      return 0;
    }
    P124_DebugLog("File loaded successfully.");
    float sx = 0.0f, sy = 0.0f, sz = 0.0f;
    const uint8_t *b = (const uint8_t *)P54_Tab4[i];
    for (int32_t k = 0; k < P103_PathLen[i]; k++) {
      const uint8_t *fr = b + (size_t)(P12_00c821a0 * 0x14 + 0x10) * (size_t)k;
      sx += p137_f((uint32_t)p137_rd(fr)); sy += p137_f((uint32_t)p137_rd(fr + 4)); sz += p137_f((uint32_t)p137_rd(fr + 8));
    }
    P137_PathDist[i] = (float)sqrt((double)(sx * sx + sy * sy + sz * sz));
  }
  P124_DebugLog("Motion capture has been initialised.");
  return 1;
}

/* ---- 0040d07b ---- */
int32_t P137_LoadTsd(const char *name) {
  uint8_t tag[4], hdr8[8], skip[4];
  float ver = 0.0f;
  int16_t npal = 0, idx = 0;
  int32_t h[5];
  for (int i = 0; i < 0x32; i++) P12_01252aa0[i] = 0;
  void *f = g_fopen(name, "rb");
  if (f == NULL) return 0;
  g_fread(tag, 1, 4, f);
  if (memcmp(tag, "TSD ", 4) != 0) { g_fclose(f); return 0; }
  g_fread(&ver, 1, 4, f);
  g_fread(hdr8, 1, 8, f);
  int16_t magic, pages;
  memcpy(&magic, hdr8 + 4, 2); memcpy(&pages, hdr8 + 6, 2);
  if (magic != 0x100) { g_fclose(f); return 0; }
  if (p137_u(ver) == 0x3f800000u) {
    g_fread(&P14_01252be0[0x400], 1, 0x400, f); P12_01252aa0[1] = 1;
    g_fread(&P14_01252be0[0], 1, 0x400, f); P12_01252aa0[0] = 1;
  } else {
    uint8_t tmp[0x400];
    g_fread(&npal, 1, 2, f);
    for (int32_t i = 0; i < npal; i++) {
      g_fread(&idx, 1, 2, f);
      g_fread(&idx, 1, 2, f);
      if (idx >= 0 && idx < 64) { g_fread(&P14_01252be0[idx * 0x400], 1, 0x400, f); P12_01252aa0[idx] = 1; }
      else g_fread(tmp, 1, 0x400, f);
    }
  }
  long start = g_ftell(f);
  int32_t arena = 0, names = 0;
  for (int32_t i = 0; i < pages; i++) {
    if (1.0f < ver) g_fread(skip, 1, 2, f);
    g_fread(h, 1, 0x14, f);
    h[0] -= 0x14; h[1] -= 0x14; h[2] -= 0x14;
    int16_t cnt; memcpy(&cnt, (uint8_t *)h + 0xc, 2);
    names += cnt;
    arena += 0x10000;
    g_fseek(f, h[0], 1);
  }
  uint8_t *base = NULL;
  if (arena != 0) {
    base = (uint8_t *)P98_DebugMalloc(arena + 0xffff, "D:\\Driver\\Game\\frontend\\frontend.c", 0x3b6);
    if (base == NULL) { g_fclose(f); return 0; }
  }
#ifdef RE_HOOK_BUILD
  P41_Arena = (uint32_t)(uintptr_t)base;
#else
  p137_tsd = base;
  P41_Arena = base != NULL ? re_ptr_register_dyn(base, (uint32_t)(arena + 0xffff)) : 0;   /* v2.04: вся арена (re_addr давал область 1 байт) */
#endif
  P41_Offset = (int32_t)((0x10000u - ((uint32_t)(uintptr_t)base & 0xffffu)) & 0xffffu);
  P54_MapAPtr = P98_DebugMalloc(names << 4, "D:\\Driver\\Game\\frontend\\frontend.c", 0x3c0);
  if (P54_MapAPtr == NULL) { g_fclose(f); return 0; }
  g_fseek(f, start, 0);
  P54_MapA = 0;
  for (int32_t k = 0; k < pages; k++) {
    uint8_t *blk = (uint8_t *)P59_ReadBlock(f, ver, h);
    if (blk == NULL) return 0;                           /* native: 0040d4b3 уже закрыл файл */
    P122_MapNames((const uint8_t *)h, (const char *)blk, (uint8_t)k);
    uint8_t *page = base + P41_Offset;
    if (k < 64) P65_Texs[k].p = page;   /* v2.02: 64 страницы (было 16) */
    memcpy(page, blk + h[2], 0x10000);
    P41_Offset += 0x10000;
    P98_DebugFree(blk);
  }
  g_fclose(f);
  return 1;
}

/* ---- 004a1037 ---- */
static int p137_ref_ok(const void *p) {
#ifdef RE_HOOK_BUILD
  (void)p; return 1;
#else
  return P79_PTR(P79_OFF(p)) == p;
#endif
}
void P137_DrawCar(int32_t car, int32_t rec) {
  float pos[3];
  if (car < 0 || car >= P99_CARS_N) return;
  if (rec == -1 && P59_Mode1137324 == 8) return;
  if (P84_Mirror != 0 && rec == -1) return;
  if (rec == -1 && P59_Mode1137324 == 2) {
    int32_t a = P133_1137320 >> 16;
    if (a < 0) a = -a;
    if (0x400 < a) return;
  }
  p99_car_t *c = &P99_Cars[car];
  pos[0] = (float)c->pos[0]; pos[1] = -(float)c->pos[1]; pos[2] = (float)c->pos[2];
  if (P59_Mode1137324 != 6 && P76_InBox(pos, (const uint8_t *)P82_LightGrid, P82_CellCX, P82_CellCY) == 0) return;
  int32_t slot = 0, kind = 0, rk = 0;
  const uint8_t *tr = (const uint8_t *)P12_011443e0;
  if (rec != -1) {
    if (rec < 0 || rec >= 0x40) return;
    slot = rec + 1;
    rk = tr[rec * 0x54 + 5];
    kind = tr[rec * 0x54 + 0xc];
  }
  if (kind < 0 || kind >= 12) return;
  uint32_t mref = P28_CarClean[kind];
  uint8_t *mdl = (uint8_t *)P79_PTR(mref);
  float rad = p137_f((uint32_t)p137_rd(mdl + 0xc));
  if (P14_00b87e84 != 0 && car != 0 && car - 1 < 0x40) {
    const uint8_t *r = tr + (car - 1) * 0x54;
    if (r[1] != 1 && c->vel[0] < 1000 && c->vel[1] < 1000 && P82_SphereVis3D(pos, rad * P56_C54611C) != 0 && P123_GlowN < 65) {
      P123_GlowCars[P123_GlowN] = car;
      P123_GlowN++;
    }
  }
  int32_t vis = P82_SphereVis3D(pos, rad);
  if (vis == 0) return;
  float *m = P98_CarMat[car];
  const float k = 1.0f / 4096.0f;
  for (int i = 0; i < 9; i++) m[i] = (float)c->mat[i] * k;
  m[0] = -m[0]; m[1] = -m[1]; m[2] = -m[2]; m[6] = -m[6]; m[7] = -m[7]; m[8] = -m[8];
  pos[0] -= P44_CamX; pos[1] -= P44_CamY; pos[2] -= P44_CamZ;
  P44_MatPtr = (float *)P44_ViewMatT;
  P44_Xform(pos);
  int32_t edge = P82_Edge;
  float lim = (P26_FxD == 0) ? 5500.0f : 1500.0f, shk;
  if (pos[2] <= lim) shk = (1000.0f <= pos[2]) ? 1.0f - (pos[2] - 1000.0f) / (lim - 1000.0f) : 1.0f;
  else shk = 0.0f;
  if (Q01270C24 - 1000.0f < pos[2]) return;
  int32_t timer = p137_rd(&P98_CarTimer[slot * 4]);
#ifndef RE_HOOK_BUILD
  /* v2.19: порог деталей машины (тень, фары, колёса, огни) × draw_distance — только во время 3D-вида */
  if (!(pos[2] <= 15000.0f * re_dd_vis() || P60_Var1373C0 != 0)) {
#else
  if (!(pos[2] <= 15000.0f || P60_Var1373C0 != 0)) {
#endif
    P84_DrawCar(P28_CarLow[kind], m, pos, 0, car, kind, timer, shk);
    return;
  }
  int dskip = 0;
#ifndef RE_HOOK_BUILD
  { const char *e = getenv("RE_CARSKIP"); dskip = e ? atoi(e) : 0; }   /* v2.06: отладка — 1 тень, 2 пятна фар, 4 колёса, 8 дым, 16 задние огни */
#endif
  if (P95_D11920 == 0 || rec != -1) {
    if (!(dskip & 1)) P138_CarShadow(car);
    P82_Edge = edge;
    if (!(dskip & 2)) P106_CarHeadSpots(car);
  }
  if (!(dskip & 4)) P136_DrawWheels(car, m, vis);
  int32_t sp = 0;
  if (car == S_00D11878 && P95_D11920 == 0) {
    if (dskip & 16) {} else if (c->f10c < 1 || -1 < c->ff8) P106_CarTailLights(car); else P106_CarBrakeLights(car);
    if (c->f10c < 0 && c->ff8 < 0) P101_CarSkids(car);
    if (c->f10c < 0x4b000 && 0 < c->f10c && 200 < c->ffc) P102_CarLights(car, 0);
    else if (c->f10c < 0x4b000 && 0 < c->f10c && c->ffc < -200) P102_CarLights(car, 1);
  }
  if (P95_D11920 == 0) {
    sp = c->f10c;
    int calm = c->vel[0] < 0xfa1 && c->vel[1] < 0xfa1;
    if (calm && rk != 0) {
      int32_t ix = rk - 1;
      calm = ix >= 0 && (size_t)(ix + 1) * 0xcd8 + 0x40 <= sizeof(P12_0112da00) &&
             p137_rd((const uint8_t *)P12_0112da00 + 0x40 + ix * 0xcd8) <= P137_DUST_LIM;
    }
    if (calm) {
      if ((3000 < c->vel[0] || 3000 < c->vel[1]) && sp < 400000 && -200000 < sp) P119_CarDust(car, 0, sp);
    } else if (sp < 400000 && -200000 < sp) {
      P119_CarDust(car, 1, sp);
      if (sp < 30000 && -30000 < sp) P120_CarSparks(car);
    }
  }
  if (80000 < sp || sp < -40000) P97_KickDebris(c->pos);
  if (((P95_D11920 == 0 && sp < 60000 && -60000 < sp) || (MenuOptBDFA44 != 0 && car == 0)) &&
      (car == 0 || (car - 1 < 0x40 && tr[(car - 1) * 0x54 + 1] != 1)))
    { if (!(dskip & 8)) P120_CarSmoke(car, sp); }
  if (MenuVar55384C != 0 && car == 0 && P72_RoadLookup(c->pos[0], c->pos[2]) != 0) {
    uint32_t w = P79_ModelTab[P72_Id];
    if (w != 0 && (*(const uint16_t *)((const uint8_t *)P79_PTR(w) + 2) & 0x80) != 0 && c->pos[1] + P72_Low < 0) {
      if (G6_005624A0 == 0) {
        P99_Cars[0].ff8 = (int32_t)0xffffe4a8;
        P99_Cars[0].f40[0] >>= 1; P99_Cars[0].f40[1] >>= 1; P99_Cars[0].f40[2] >>= 1;
        P95_D11920 = 1;
      } else {
        P120_CarDebris(0, P72_Low);
        P99_Cars[0].ff8 = (int32_t)0xffffe4a8;
        P99_Cars[0].f40[0] >>= 1; P99_Cars[0].f40[1] >>= 1; P99_Cars[0].f40[2] >>= 1;
        G6_005624A0--;
      }
    }
  }
  if (car == 0 && S_00D1192C == 10 && P98_DD70 != 0) P102_CarTracks(0, &P98_DDE4, 1.0f);
  uint32_t s20 = (uint32_t)p137_rd(mdl + 0x20), s24 = (uint32_t)p137_rd(mdl + 0x24), s2c = 0;
  const void *pa = &P98_CarOpsA[slot * 0x1040], *pb = &P98_CarOpsB[slot * 0x1700], *pc = &P98_CarOpsC[slot * 0x9580];
  int swap = p137_ref_ok(pa) && p137_ref_ok(pb) && (slot == 0 || p137_ref_ok(pc));
  if (swap) {
    uint32_t v;
    if (slot != 0) s2c = (uint32_t)p137_rd(mdl + 0x2c);
    v = P79_OFF(pa); memcpy(mdl + 0x20, &v, 4);
    v = P79_OFF(pb); memcpy(mdl + 0x24, &v, 4);
    if (slot != 0) { v = P79_OFF(pc); memcpy(mdl + 0x2c, &v, 4); }
  }
  if (vis == 1) P84_DrawCar(mref, m, pos, 0, car, kind, timer, shk);
  else if (vis == 2) P84_DrawCar(mref, m, pos, 1, car, kind, timer, shk);
  if (swap) {
    memcpy(mdl + 0x20, &s20, 4);
    memcpy(mdl + 0x24, &s24, 4);
    if (slot != 0) memcpy(mdl + 0x2c, &s2c, 4);
  }
}
