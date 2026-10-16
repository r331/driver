/* v1.76: ported131 — см. ported131.h.
   0041b7d1 — выбор пункта: D_00b87e30 = P68_IntroA, цикл 00417b80(tab): −1 → GameMode = 1, результат 0; −2 → экран
     ошибки 0xf6..0xf9 по D_00b87e30 (режим меню 8, 0040c20b(0)); ≥0 — значение пункта tab + 4 + i·8.
   004f621d — строка скрипта миссии: токены P65_NextToken(P65_Line, P65_Tok) → _strupr (CRT 0053fb50; в native — ASCII);
     "//" и "#" — конец строки (0), пустой токен — 0, "," — 6, ";" пропускается; иначе команда P42_FindCommand:
     не найдена — P122_SetVar(NULL, NULL) (≠0 → код), найдена — 004f68a1(cmd) (≠0xb → код).
   0049e911 — облёт: флаги ключей +0x28 (32 ключа по 0x34) = 0, sprintf MISSION%d.FBD по P11_00b87e38, 0049f20a(имя):
     нет — P14_00b87ee4 = 0; есть — камера из ключа 1 (+0..+0xc, кадр +0x2c), скорость P19_ScrH·0xc00.
   004d4a63 — кадр игры: при P62_Frame = 0 два холостых кадра (P131_Skip = 1), иначе такт + догоняющие кадры
     (P21_FrameTicks, ×5 в режиме 6), CD-трек D_00b87e30 + 4, громкость, повтор 004d4fc5.
   004cc1a2 / 004cbc1e — Glide: состояние 3,1,0,1,0 (тег 4), смешение 4,4,0,0 (тег 3), текстура значка +8; вершины
     в оригинале — локальные структуры 0x40 (поля z/ooz/a не задаются — мусор стека; в native 0). */
#include "ported132.h"
#include "ported131.h"
#include "reptr.h"
#include "director.h"
#include "menustate.h"
#include "globalsets.h"
#include "smallfuncs.h"
#include "uihandlers.h"
#include "uihandlers4.h"
#include "ported4.h"
#include "ported5.h"
#include "ported6.h"
#include "ported7.h"
#include "ported11.h"
#include "ported12.h"
#include "ported14.h"
#include "ported17.h"
#include "ported19.h"
#include "ported21.h"
#include "ported25.h"
#include "ported29.h"
#include "ported31.h"
#include "ported42.h"
#include "ported43.h"
#include "ported44.h"
#include "ported45.h"
#include "ported48.h"
#include "ported56.h"
#include "ported59.h"
#include "ported61.h"
#include "ported62.h"
#include "ported65.h"
#include "ported67.h"
#include "ported68.h"
#include "ported69.h"
#include "ported85.h"
#include "ported86.h"
#include "ported98.h"
#include "ported99.h"
#include "ported100.h"
#include "ported79.h"
#include "ported84.h"
#include "ported101.h"
#include "ported102.h"
#include "ported103.h"
#include "ported120.h"
#include "ported55.h"
#include "ported57.h"
#include "ported58.h"
#include "ported95.h"
#include "cartab.h"
#include "ported28.h"
#include "ported124.h"
#include "ported128.h"
#include "crt.h"
#include "ported76.h"
#include "ported121.h"
#include "ported122.h"
#include "ported134.h"
#include "smallfuncs2.h"
#include "unported.h"
#include "ported147.h"
#include <math.h>
#include <stdio.h>
#include <string.h>

#ifndef RE_HOOK_BUILD
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P131_Skip")
#undef P131_Skip
#pragma push_macro("P131_Skip") /*gvi*/
#undef P131_Skip /*gvi*/
int32_t P131_Skip;
#pragma pop_macro("P131_Skip") /*gvi*/
#pragma pop_macro("P131_Skip")
#endif
#endif

static int32_t rd32(const void *p) { int32_t v; memcpy(&v, p, 4); return v; }
static const float SNAP = 1048576.0f;     /* .rdata 0054607c */
static const float NEAR_Z = 50.0f;        /* .rdata 0054609c */
static const float SPL_FAR = 1536.0f;     /* .rdata 00546888 */
static const float SCR_W = 640.0f;        /* .rdata 00546060 */
static const float SCR_H = 480.0f;        /* .rdata 0054605c */
static const float SPL_SZ = 32.0f;        /* .rdata 00546100 */
#define ZTAB_N ((int32_t)(sizeof P12_00ba53a0 / sizeof P12_00ba53a0[0]))

static void set_menu_mode(int32_t v) { MenuMode1271060 = v; P11_01271060 = v; P62_Menu1271060 = v; G01271060 = v; }
static void set_mode38(int32_t v) { P11_00b87e38 = v; P17_Cond2 = v; P19_Cond = v; P45_Mode = v; UiVar00B87E38 = v; }

static void state_set(void) {
  if (P85_StateDirty != 4) { if (P85_StateFn) P85_StateFn(3, 1, 0, 1, 0); P85_StateDirty = 4; }
}
static void blend_set(void) {
  if (P85_BlendCur != 3) { if (P85_BlendFn) P85_BlendFn(4, 4, 0, 0); P85_BlendCur = 3; P69_BlendOn = 3; }
}
static void tex_select(uint32_t page) {
  if (page != (uint32_t)P86_CurTex) {
    P86_CurTex = (int32_t)page;
    if (P86_TexSrc) P86_TexSrc(0, (uint32_t)rd32(&g_01145a60[page * 0x10 + 8]), 3, (uint32_t)rd32(&g_01145a60[page * 0x10 + 0xc]));
  }
}
static void raster(const p85_rv *a, const p85_rv *b, const p85_rv *c) { if (P85_RasterB) P85_RasterB(a, b, c); }
static int32_t zidx(float z) {
  int32_t i = (int32_t)lrintf(z);
#ifndef RE_HOOK_BUILD
  if (i < 0 || i >= ZTAB_N) i = (i < 0) ? 0 : ZTAB_N - 1;
#endif
  return i;
}
static void vset(p85_rv *v, float x, float y, float c, float oow, float s, float t) {
  memset(v, 0, sizeof *v);
  v->x = x; v->y = y; v->r = c; v->g = c; v->b = c; v->oow = oow; v->tmu[0] = s; v->tmu[1] = t;
}

/* ---- 0041b7d1 ---- */
uint32_t P131_MenuPick(uint32_t tab) {
  int32_t i = 0;
  D_00b87e30 = P68_IntroA;
  for (;;) {
    if (i == -1) { GameMode = 1; return 0; }
    i = P132_MenuLoop(tab);
    if (i >= 0) break;
    if (i == -2) {
      if (D_00b87e30 == 1) set_mode38(0xf7);
      else if (D_00b87e30 == 2) set_mode38(0xf8);
      else if (D_00b87e30 == 3) set_mode38(0xf9);
      else set_mode38(0xf6);
      set_menu_mode(8);
      Call0040C20B(0);
    }
  }
  const uint8_t *p = (const uint8_t *)re_ptr(tab + 4u + (uint32_t)i * 8u);
#ifndef RE_HOOK_BUILD
  if (p == NULL) return 0;
#endif
  return (uint32_t)rd32(p);
}

/* ---- 004f621d ---- */
int32_t P131_ScriptLine(void) {
  for (;;) {
    int32_t r = P65_NextToken(P65_Line, P65_Tok);
    if (r != 0) return r;
    for (char *c = P65_Tok; *c; c++) if (*c >= 'a' && *c <= 'z') *c = (char)(*c - 0x20);   /* _strupr */
    size_t n = strlen(P65_Tok);
    if (P65_Tok[0] == '/' && P65_Tok[1] == '/') return 0;
    if (P65_Tok[0] == '#') return 0;
    if (n == 0) return 0;
    if (P65_Tok[0] == ',') return 6;
    if (P65_Tok[0] == ';') continue;
    void *cmd = NULL;
    P42_FindCommand(P65_Tok, &cmd);
    if (cmd == NULL) {
      r = P122_SetVar(NULL, NULL);
      if (r != 0) return r;
    } else {
      r = P147_ParseCmd(cmd);
      if (r != 0xb) return r;
    }
  }
}

/* ---- 0049e911 ---- */
void P131_FlybyStart(void) {
  char name[32];
  P14_00b87ee4 = 1;
  P99_CamDone = 0;
  for (int32_t i = 0; i < 0x20; i++) memset(&P99_CamKeys[i * 0x34 + 0x28], 0, 4);
  P99_CamOn = 0;
  snprintf(name, sizeof name, "SCRIPTS\\FLYBY\\MISSION%d.FBD", (int)P11_00b87e38);   /* .data 0055145c */
  if (P132_LoadFlyby(name) == 0) { P14_00b87ee4 = 0; return; }
  const uint8_t *k1 = &P99_CamKeys[0x34];
  float f[3]; uint32_t w;
  P99_CamOn |= 1;
  P99_CamIdx = 1;
  P99_CamT = rd32(k1 + 0x2c);
  memcpy(f, k1, 12); memcpy(&w, k1 + 12, 4);
  P44_CamX = f[0]; P44_CamY = f[1]; P44_CamZ = f[2];
  P59_VX = f[0]; P59_VY = f[1]; P59_VZ = f[2];
  P121_CamW = w; P98_CamW = w;
  P99_CamSpd = P19_ScrH * 0xc00;
  P99_CamStep = P19_ScrH * 0x20 - (P99_CamSpd >> 7);
  P99_CamB0 = 0xcc;
  P99_CamMax = P19_ScrH;
}

/* ---- 004d4a63 ---- */
void P131_GameFrame(void) {
  P12_Fn0050E963();
  int32_t keep = G6_00B5A778;
  if (P62_Frame == 0) {
    P131_Skip = 1;
    P61_SetupCamN(0);
    SetLatchValue0050E940(0);
    P12_Fn0050E963();
    GlobalSet004AADDF(); P132_GameLogic(); P132_GameDraw();
    P62_Frame = 1; G8_00D118C0 = 1; P67_Cur = 1;
    GlobalSet004AADDF(); P132_GameLogic(); P132_GameDraw();
    P62_Frame = 2; G8_00D118C0 = 2; P67_Cur = 2;
    P131_Skip = 0;
    G6_00B5A778 = keep;
    return;
  }
  if (P31_Active == 0 && G6_00B5A778 == 0) SetLatchValue0050E940(1);
  P12_Fn0050E963();
  GlobalSet004AADDF();
  P132_GameLogic();
  if (G6_00B87E20 == 0) return;
  int32_t n = (int32_t)P21_FrameTicks();
  if (P29_Mode == 6) n *= 5;
  for (; n > 1; n--) {
    if (G6_00B87E20 == 0) return;
    GlobalSet004AADDF();
    P132_GameLogic();
    if (G6_00B87E20 == 0) return;
  }
  if (Q00B87E90 != 0 && G6_00B5A778 == 0 && P25_CdPlaying == 0) {
    P25_InitCDAudio();
    P25_PlayCDTrack(D_00b87e30 + 4);
  }
  InitSoundVolumes_00523C56();
  if (P31_Active != 0) { P132_GameDraw(); P67_Cur++; }
  if (P99_CamDone != 0) P14_00b87ee4 = 0;
}

/* ---- 004cc1a2 ---- */
void P131_Splash(void) {
  const uint8_t *ic = G00D164EC;
  if (ic == NULL || G6_00B5A778 != 0) return;
  P12_Fn00426580(0);
  state_set();
  tex_select(ic[8]);
  blend_set();
  uint32_t k = 0x32;
  while (k != 0) {
    P44_MatPtr = (float *)P44_ViewMatT;
    k--;
    float v[3], q[3];
    v[0] = (float)(int32_t)((N14_Rand() & 0xfff) - 0x800);
    v[2] = (float)(int32_t)((N14_Rand() & 0xfff) - 0x800);
    q[0] = v[0] + P44_CamX; q[1] = 0.0f; q[2] = v[2] + P44_CamZ;
    int32_t h = P100_RoadHeightF(q);
    v[1] = ((float)-h - P44_CamY) - NEAR_Z;
    P44_Xform(v);
    if (!(NEAR_Z <= v[2] && v[2] < SPL_FAR)) continue;
    float w = P12_00ba53a0[zidx(v[2])], f = P43_ScaleA * w;
    float sx = (v[0] * f + P43_OffX) - SNAP, sy = (v[1] * f + P43_OffY) - SNAP;
    if (!(0.0f < sx && sx < SCR_W && 0.0f < sy && sy < SCR_H)) continue;
    P11_00ba52d0 = (int32_t)lrintf(SPL_SZ * f);
    float d = (float)P11_00ba52d0;
    float c = (float)(uint8_t)((N14_Rand() & 0x1f) + 0x28);
    uint8_t sa, sb;                       /* s вершин A/D и B/C: чётный k — 0xb / 9, нечётный — 9 / 0xb */
    if ((k & 1) == 0) { sa = ic[0xb]; sb = ic[9]; } else { sa = ic[9]; sb = ic[0xb]; }
    float t0 = (float)ic[10] * w, t1 = (float)ic[0xc] * w;
    p85_rv A, B, C, D;
    vset(&A, sx, sy, c, w, (float)sa * w, t0);
    vset(&B, sx + d, sy, c, w, (float)sb * w, t0);
    vset(&C, sx + d, sy + d, c, w, (float)sb * w, t1);
    vset(&D, sx, sy + d, c, w, (float)sa * w, t1);
    raster(&A, &B, &C);
    raster(&A, &C, &D);
  }
}

/* ---- 004cbc1e ---- */
void P131_RainDraw(void) {
  int32_t *st = G2_ScriptStack;
  if (st == NULL || st[0] == 0) return;
  const uint8_t *ic = G00D14EF0;
#ifndef RE_HOOK_BUILD
  if (ic == NULL) return;
#endif
  float dw = (float)(P19_ScrW >> 8);
  int32_t saved = DrvSetMode0042655A(0);
  P131_Splash();
  blend_set();
  state_set();
  tex_select(ic[8]);
  const uint8_t *r = (const uint8_t *)(st + 0x65);
  int32_t n = st[0];
#ifndef RE_HOOK_BUILD
  if (n > 100) n = 100;
#endif
  for (; n != 0; n--, r += 0x34) {
    if (r[0x30] != 2) continue;
    float x0, y0, w; memcpy(&x0, r + 0x20, 4); memcpy(&y0, r + 0x24, 4); memcpy(&w, r + 0x28, 4);
    float x1 = (float)rd32(r + 0x10), y1 = (float)rd32(r + 0x14);
    uint8_t cb = (uint8_t)(r[0x31] + 0x28);
    float cf = (float)cb, ch = (float)(cb / 2);
    p85_rv A, B, C, D;
    vset(&A, x0, y0, cf, w, (float)ic[9] * w, (float)ic[10] * w);
    vset(&B, x0 + dw, y0, cf, w, (float)ic[0xb] * w, (float)ic[10] * w);
    vset(&C, x1 + dw, y1, ch, w, (float)ic[0xb] * w, (float)ic[0xc] * w);
    vset(&D, x1, y1, ch, w, (float)ic[9] * w, (float)ic[0xc] * w);
    raster(&A, &B, &C);
    raster(&A, &C, &D);
  }
  DrvSetMode0042655A(saved);
}

/* ---- 004fef26: модель с объектами миссии — записи 0x24 таблицы города (адреса групп .data 005734ac, число P103_MObjN):
   +0 тип, +4 модель, +0xc..+0x14 сдвиг (float), +0x1c/+0x1e/+0x20 int16. __ftol(x + z) — фаза качания. ---- */
static int16_t rd16s(const uint8_t *p) { int16_t v; memcpy(&v, p, 2); return v; }
static float rdf(const void *p) { float v; memcpy(&v, p, 4); return v; }
static int32_t gd32(uint32_t a) { const void *p = re_ptr(a); return p ? rd32(p) : 0; }
static float sway(float x, float z) {
  int32_t t = (int32_t)(x + z);
  return P43_Sin[(((P62_Frame + t) & 0xff) - 0x80) << 4 & 0xfff];
}
static uint8_t light_kind(uint32_t ang) {
  int32_t a = (int32_t)ang;
  if ((a < -9 || a > 9) && (a < 0x7f7 || a > 0x809)) return G00C29D81;
  return G00C29D80;
}
static void mark2(const uint8_t *o, float x0, float y, float z, int16_t k, int32_t two, float x1) {
  P102_ObjMark(o, x0, y, z, k);
  if (two) P102_ObjMark(o, x1, y, z, k);
}
void P131_MissionObj(uint32_t m, const uint8_t *obj, int32_t mode) {
  if (D_00b87e30 > 4) return;                        /* .rdata 00546a04 = 4 */
#ifndef RE_HOOK_BUILD
  if (D_00b87e30 < 0 || obj == NULL) return;
#endif
  uint32_t rec = (uint32_t)gd32(0x005734acu + (uint32_t)D_00b87e30 * 4u);
  int32_t mi = rd32(obj + 4), id = mi;
#ifndef RE_HOOK_BUILD
  if (mi >= 0 && mi < 1126 && P79_ModelTab[mi] != 0)
#endif
  { int32_t par = rd32((const uint8_t *)P79_PTR(P79_ModelTab[mi]) + 4); if (par != -1) id = par; }
  float x = rdf(obj + 8), y = rdf(obj + 0xc), z = rdf(obj + 0x10);
  uint32_t ang = (uint32_t)rd32(obj + 0x18) & 0xfff;
  for (int32_t k = 0; k < P103_MObjN; k++, rec += 0x24) {
    const uint8_t *c = (const uint8_t *)re_ptr(rec);
#ifndef RE_HOOK_BUILD
    if (c == NULL) break;
#endif
    if (rd32(c + 4) != id) continue;
    float c3 = rdf(c + 0xc), c4 = rdf(c + 0x10), c5 = rdf(c + 0x14);
    int16_t s1c = rd16s(c + 0x1c), s1e = rd16s(c + 0x1e), s20 = rd16s(c + 0x20);
    float pos[3]; float vel[4] = { 0.0f, 0.0f, 0.0f, 0.0f };   /* 004b9287 читает float */
    switch (rd32(c)) {
    case 0: case 1: {
      uint8_t l = light_kind(ang);
      int32_t t1 = rd32(c) == 1;
      if (l == 1 || l == 2) mark2(obj, -648.0f, -944.0f, -50.0f, 0x200, 1, t1 ? 348.0f : 136.0f);
      else if (l == 3) mark2(obj, -460.0f, -944.0f, -50.0f, 0x800, 1, t1 ? 536.0f : 324.0f);
      else if (l == 4) mark2(obj, -554.0f, -944.0f, -50.0f, 0x400, 1, t1 ? 442.0f : 230.0f);
      break; }
    case 2: case 3: case 4: {
      uint8_t l = light_kind(ang);
      if (l == 1 || l == 2) P102_ObjMark(obj, -717.0f, -1470.0f, -78.0f, 0x200);
      else if (l == 3) P102_ObjMark(obj, -716.0f, -1239.0f, -78.0f, 0x800);
      else if (l == 4) P102_ObjMark(obj, -717.0f, -1355.0f, -78.0f, 0x400);
      break; }
    case 5: {
      int32_t n = (int32_t)(N14_Rand() & 0x3f) + 0x50;
      pos[0] = x + c3; pos[1] = y + c4; pos[2] = z + c5;
      if ((P62_Frame & 7) == 7) P132_Smoke(pos, vel, n, 300, s1c, s1e, s20, -2.0f, 1);
      break; }
    case 6: {
      int32_t n = (int32_t)(N14_Rand() & 0x1f) + 0x28;
      pos[0] = x + c3; pos[1] = y + c4; pos[2] = z + c5;
      if ((P62_Frame & 7) == 3) P132_Smoke(pos, vel, n, n * 6, 2, 0x78, s20, -1.5f, 1);
      break; }
    case 7: {
      float d = sway(x, z) * (float)s1c;
      y += d;
      P101_AddObjB(obj, c3, d + c4, c5, s20, s1e, 0x100);
      break; }
    case 8: {
      float d = sway(x, z) * (float)s1c;
      y += d;
      if (((P62_Frame + (int32_t)(x + z)) & 0x20) != 0) P101_AddObjB(obj, c3, d + c4, c5, s20, s1e, 0x100);
      break; }
    case 9: {
      int32_t n = (int32_t)(N14_Rand() & 0x3f) + 200;
      const float *e = (const float *)(const void *)(P56_EulerTab + ang * 0x40);
      float dx = c3 * e[0] + c5 * e[6], dy = c4, dz = c3 * e[2] + c5 * e[8];
      float d = sway(x, z) * (float)s1c;
      y += d;
      pos[0] = x + dx; pos[1] = y + dy; pos[2] = z + dz;
      if ((P62_Frame & 7) == 7) P132_Smoke(pos, vel, n, 500, 7, 200, s20, -1.0f, 1);
      break; }
    case 10: case 0xc: case 0xe:
      P101_AddObjB(obj, c3, c4, c5, s20, s1e, 0x100);
      break;
    case 0xb:
      P101_AddObjB(obj, c3, c4, c5, s20, s1e, 0x100);
      P101_AddObjB(obj, (float)s1c, c4, c5, s20, s1e, 0x100);
      break;
    case 0xd:
      P120_ObjBShade((uint8_t *)(uintptr_t)obj, c3, c4, c5, s20, s1e);
      break;
    case 0xf: {
      int32_t n = (int32_t)(N14_Rand() & 0x1f) + 0x32;
      float f = (float)(N14_Rand() & 0xf) / 15.0f + 0.1f;   /* .rdata 00546a08 / 005461bc */
      pos[0] = x + c3; pos[1] = y + c4; pos[2] = z + c5;
      if ((P62_Frame & 7) == 3) P132_Smoke(pos, vel, n, n * 5, 4, 0x32, 2, -f, 1);
      break; }
    default: break;
    }
  }
  float v[3] = { x - P44_CamX, y - P44_CamY, z - P44_CamZ };
  P44_MatPtr = (float *)P44_ViewMatT;
  P44_Xform(v);
  P84_DrawModelIdx(m, (int32_t)ang, v, mode == 1 ? 0 : (mode == 2 ? 1 : 2));
}

/* ---- 00507925: стрелка на радаре к цели i (P58_Objs[i] +0x14/+0x1c) от игрока: длина min(dist / P19_Scale, 50),
   поворот P95_MapRotate вокруг игрока; в режиме карты (P55_BDFA18) или флаге 2 P131_BDFAA4 — треугольник 0xc0,
   иначе — три линии 0x80. Поля вершин кроме x, y, r, g, b, oow в оригинале не задаются (в native 0). ---- */
#ifndef RE_HOOK_BUILD
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P131_BDFAA4")
#undef P131_BDFAA4
#pragma push_macro("P131_BDFAA4") /*gvi*/
#undef P131_BDFAA4 /*gvi*/
int32_t P131_BDFAA4;
#pragma pop_macro("P131_BDFAA4") /*gvi*/
#pragma pop_macro("P131_BDFAA4")
#endif
#endif
void P131_RadarArrow(int32_t i) {
#ifndef RE_HOOK_BUILD
  if (i < 0 || i >= 10) return;
#endif
  float one = (P55_BDFA18 != 0) ? 1.0f : 0.015625f;
  float p1[2] = { (float)P99_Cars[0].pos[0], (float)P99_Cars[0].pos[2] };
  float p2[2] = { (float)rd32(&P58_Objs[i][0x14]), (float)rd32(&P58_Objs[i][0x1c]) };
  P57_ScreenToView(&p1[0], &p1[1]);
  P57_ScreenToView(&p2[0], &p2[1]);
  int32_t dx = (int32_t)(p2[0] - p1[0]), dz = (int32_t)(p2[1] - p1[1]);
  float dist = (float)sqrt((double)(dx * dx + dz * dz));
  int32_t ang = P44_Atan2(dz, dx) & 0xfff;
  if (D_00b87e30 == 1) ang = (ang + 0xc00) & 0xfff;
  else if (D_00b87e30 == 0 || D_00b87e30 == 2 || D_00b87e30 == 3) ang = (ang - 0x400) & 0xfff;
  dist = dist / P19_Scale;
  float d = dist;
  if (d > NEAR_Z) d = 50.0f;
  int32_t pt[6];
  pt[0] = (int32_t)(-15.0f * d / NEAR_Z); pt[1] = 0;     /* .rdata 00546a48 / 00546a08 */
  pt[2] = (int32_t)(15.0f * d / NEAR_Z);  pt[3] = 0;
  pt[4] = 0;
  P11_00ba52d0 = (int32_t)lrintf(dist); pt[5] = P11_00ba52d0;
  P95_MapRotate(pt, pt, 3, p1, ang);
  if (P85_StateDirty != 0) { if (P85_StateFn) P85_StateFn(1, 0, 0, 2, 0); P85_StateDirty = 0; }
  int32_t tri = (P55_BDFA18 != 0 || (P131_BDFAA4 & 2) != 0);
  int32_t c = tri ? 0xc0 : 0x80;
  float cq = (float)(c / 4), cf = (float)c;
  p85_rv A, B, C;
  vset(&A, (float)pt[0], (float)pt[1], cq, one, 0.0f, 0.0f);
  vset(&B, (float)pt[2], (float)pt[3], cq, one, 0.0f, 0.0f);
  vset(&C, (float)pt[4], (float)pt[5], cf, one, 0.0f, 0.0f);
  if (tri) {
    if (P85_BlendCur != 2) { if (P85_BlendFn) P85_BlendFn(0, 6, 4, 0); P85_BlendCur = 2; P69_BlendOn = 2; }
    raster(&A, &B, &C);
  } else {
    if (P85_BlendCur != 0) { if (P85_BlendFn) P85_BlendFn(4, 0, 4, 0); P85_BlendCur = 0; P69_BlendOn = 0; }
    if (P95_DrawLine) { P95_DrawLine(&A.x, &C.x); P95_DrawLine(&A.x, &B.x); P95_DrawLine(&B.x, &C.x); }
  }
}

/* ---- 004ef9cd: косметика машин LEVELS\<город>.COS → S_00D0CC60 (0x1110) и вмятины LEVELS\miami_01.DEN (NC_01.DEN
   для города 6) → .data 00559074 (0x1680 = P28_Dst1 + P128_DmgMap), 0055a6f4 (0x1140 = P28_Dst2 + P131_DenB),
   0055b834 (0x1140, P131_DenC). В Ghidra __fastcall без чтения ECX — явный мусорный параметр (v1.69). ---- */
#ifndef RE_HOOK_BUILD
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P131_DenB")
#undef P131_DenB
#pragma push_macro("P131_DenB") /*gvi*/
#undef P131_DenB /*gvi*/
p131_denb_t P131_DenB;
#pragma pop_macro("P131_DenB") /*gvi*/
#pragma pop_macro("P131_DenB")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P131_DenC")
#undef P131_DenC
#pragma push_macro("P131_DenC") /*gvi*/
#undef P131_DenC /*gvi*/
p131_denc_t P131_DenC;
#pragma pop_macro("P131_DenC") /*gvi*/
#pragma pop_macro("P131_DenC")
#endif
#endif
static const char *const k_cos[7] = {                  /* .data 00562d60 */
  "LEVELS\\MIAMI_01.COS", "LEVELS\\FRISCO_01.COS", "LEVELS\\LA_01.COS", "LEVELS\\NY_01.COS",
  "LEVELS\\IVIEW.COS", "LEVELS\\TRAIN.COS", "LEVELS\\NC_01.COS" };
void P131_LoadCosDen(int32_t junk) {
  (void)junk;
  P124_DebugLog("*** Loading cosmetics data ***");
  void *f = NULL;
#ifndef RE_HOOK_BUILD
  if (D_00b87e30 >= 0 && D_00b87e30 < 7)
#endif
  f = g_fopen(k_cos[D_00b87e30], "rb");
  if (f == NULL) P124_DebugLog("XXX Cosmetics data failed to load!");
  else {
    g_fread(S_00D0CC60, 0x1110, 1, f);
    g_fclose(f);
    P124_DebugLog("*** Cosmetics data loaded ***");
  }
  P124_DebugLog("*** Loading denting data ***");
  f = g_fopen(D_00b87e30 == 6 ? "LEVELS\\NC_01.DEN" : "LEVELS\\miami_01.DEN", "rb");
  if (f == NULL) { P124_DebugLog("XXX Dentings data failed to load!"); return; }
#ifdef RE_HOOK_BUILD
  g_fread(P28_Dst1, 0x1680, 1, f);
  g_fread(P28_Dst2, 0x1140, 1, f);
  g_fread(P131_DenC, 0x1140, 1, f);
#else
  _Static_assert(sizeof P28_Dst1 + sizeof P128_DmgMap == 0x1680, "den1");
  _Static_assert(sizeof P28_Dst2 + sizeof P131_DenB == 0x1140, "den2");
  g_fread(P28_Dst1, sizeof P28_Dst1, 1, f); g_fread(P128_DmgMap, sizeof P128_DmgMap, 1, f);
  g_fread(P28_Dst2, sizeof P28_Dst2, 1, f); g_fread(P131_DenB, sizeof P131_DenB, 1, f);
  g_fread(P131_DenC, sizeof P131_DenC, 1, f);
#endif
  g_fclose(f);
  P124_DebugLog("*** Dentings data loaded ***");
}

/* ---- 0049e7a8: углы камеры из P131_CamAng (01137380: 4 × uint16 → 00b1c268..00b1c26e), подтяжка камеры к точке
   столкновения P76_ColObj на расстояние 3000 (.rdata 0054604c, делитель 20 — 00546118; кроме повтора без режима),
   дрожание по P76_Angle < 0x30, затем 0049cad4 / InitXform. ---- */
#ifndef RE_HOOK_BUILD
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P131_CamAng")
#undef P131_CamAng
#pragma push_macro("P131_CamAng") /*gvi*/
#undef P131_CamAng /*gvi*/
p131_camang_t P131_CamAng;
#pragma pop_macro("P131_CamAng") /*gvi*/
#pragma pop_macro("P131_CamAng")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P131_AngD")
#undef P131_AngD
#pragma push_macro("P131_AngD") /*gvi*/
#undef P131_AngD /*gvi*/
uint16_t P131_AngD;
#pragma pop_macro("P131_AngD") /*gvi*/
#pragma pop_macro("P131_AngD")
#endif
#endif
void P131_CamShake(void) {
  P59_AngA = P131_CamAng[0]; P59_AngB = P131_CamAng[1]; P59_AngC = P131_CamAng[2]; P131_AngD = P131_CamAng[3];
  P11_00b1c268 = (uint8_t)P59_AngA;
  if (G6_00B5A778 == 0 || P29_Mode != 0) {
    float fx = P44_CamX - rdf(&P76_ColObj[0]), fz = P44_CamZ - rdf(&P76_ColObj[8]);
    float d = (float)sqrt((double)fx * fx + (double)fz * fz);
    float k = (3000.0f - d) / (20.0f * d);
    P44_CamX = fx * k + P44_CamX; P59_VX = P44_CamX;
    P44_CamZ = fz * k + P44_CamZ; P59_VZ = P44_CamZ;
    P134_CamCollide(1);
  }
  if (P76_Angle < 0x30) {
    uint32_t r = N14_Rand();
    if (P76_Angle < (int32_t)(r & 0x3f)) {
      uint16_t s = (uint16_t)((0x30 - P76_Angle) >> 1);
      if (r & 0x2000) P59_AngA = (uint16_t)(P59_AngA + s);
      if (r & 0x1000) P59_AngA = (uint16_t)(P59_AngA - s);
      if (r & 0x800) P59_AngB = (uint16_t)(P59_AngB + s);
      if (r & 0x400) P59_AngB = (uint16_t)(P59_AngB - s);
      P11_00b1c268 = (uint8_t)P59_AngA;
    }
  }
  InitXform_005263FE();
}
