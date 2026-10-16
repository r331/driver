/* Пачка простых/листовых функций — восстановлено из Game.exe (004d2500, 004d29e1, 00405450, 004e5d64, 004ba57a, 004ba64d, 004ba457,
   004c5f69, 004d6ef2, 004c08bb, 004ab808, 0040b0fe, 00507de2, 0049f418, 0048f6c1, 004d65fa, 00405abe, 00509d27, 004d0f28, 00507310). */
#include "ported95.h"
#include "reptr.h"
#include "director.h"
#include "globalsets.h"
#include "menustate.h"
#include "ported5.h"
#include "ported6.h"
#include "ported7.h"
#include "ported10.h"
#include "ported11.h"
#include "ported13.h"
#include "ported14.h"
#include "ported19.h"
#include "ported21.h"
#include "ported26.h"
#include "ported28.h"
#include "ported35.h"
#include "ported36.h"
#include "ported4.h"
#include "ported43.h"
#include "ported44.h"
#include "ported51.h"
#include "ported52.h"
#include "ported54.h"
#include "ported55.h"
#include "ported56.h"
#include "ported58.h"
#include "ported62.h"
#include "ported63.h"
#include "ported68.h"
#include "ported72.h"
#include "ported75.h"
#include "ported80.h"
#include "ported85.h"
#include "ported87.h"
#include "ported93.h"
#include "smallfuncs2.h"
#include "uihandlers3.h"
#include "uihandlers4.h"
#include "widgets.h"
#include <math.h>
#include <string.h>

GAME_VAR_DEF(p95_objsA_t, P95_ObjA, 0x010f5160)
GAME_VAR_DEF(p95_objsB_t, P95_ObjB, 0x0110e500)
GAME_VAR_DEF(p95_objsA_t, P95_ObjC, 0x011237c0)
GAME_VAR_DEF(int32_t, P95_ChanState, 0x00d11978)
GAME_VAR_DEF(int32_t, P95_D1197C, 0x00d1197c)
GAME_VAR_DEF(int32_t, P95_ChanLast, 0x00d11a34)
GAME_VAR_DEF(int32_t, P95_D11A38, 0x00d11a38)
GAME_VAR_DEF(int32_t, P95_SndRate, 0x00d11a40)
GAME_VAR_DEF(int32_t, P95_D11A4C, 0x00d11a4c)
GAME_VAR_DEF(int32_t, P95_D11A54, 0x00d11a54)
GAME_VAR_DEF(int32_t, P95_112D9D4, 0x0112d9d4)
GAME_VAR_DEF(int32_t, P95_SndReady, 0x0112d9e4)
GAME_VAR_DEF(int32_t, P95_AmbN, 0x0112b270)
GAME_VAR_DEF(uint8_t, P95_B87E14, 0x00b87e14)
GAME_VAR_DEF(int32_t, P95_B87E34, 0x00b87e34)
GAME_VAR_DEF(int32_t, P95_B87E3C, 0x00b87e3c)
GAME_VAR_DEF(int32_t, P95_B87E40, 0x00b87e40)
GAME_VAR_DEF(int32_t, P95_B87EA4, 0x00b87ea4)
GAME_VAR_DEF(int32_t, P95_B87EB4, 0x00b87eb4)
GAME_VAR_DEF(int32_t, P95_B87EBC, 0x00b87ebc)
GAME_VAR_DEF(int32_t, P95_B87EC0, 0x00b87ec0)
GAME_VAR_DEF(int32_t, P95_B87EC4, 0x00b87ec4)
GAME_VAR_DEF(int32_t, P95_B87ED0, 0x00b87ed0)
GAME_VAR_DEF(int32_t, P95_B87ED8, 0x00b87ed8)
GAME_VAR_DEF(int32_t, P95_B87EDC, 0x00b87edc)
GAME_VAR_DEF(int32_t, P95_B87EE0, 0x00b87ee0)
GAME_VAR_DEF(int32_t, P95_B87F08, 0x00b87f08)
GAME_VAR_DEF(int32_t, P95_BDF9D0, 0x00bdf9d0)
GAME_VAR_DEF(int32_t, P95_BDF9D4, 0x00bdf9d4)
GAME_VAR_DEF(int32_t, P95_BDFA0C, 0x00bdfa0c)
GAME_VAR_DEF(int32_t, P95_BDFA14, 0x00bdfa14)
GAME_VAR_DEF(int32_t, P95_BDFA5C, 0x00bdfa5c)
GAME_VAR_DEF(int32_t, P95_BDFA60, 0x00bdfa60)
GAME_VAR_DEF(int32_t, P95_C818B8, 0x00c818b8)
GAME_VAR_DEF(int32_t, P95_D11920, 0x00d11920)
GAME_VAR_DEF(int32_t, P95_575F1C, 0x00575f1c)
GAME_VAR_DEF(int32_t, P95_Deb0, 0x0107c3c8)
GAME_VAR_DEF(int32_t, P95_Deb1, 0x010de050)
GAME_VAR_DEF(p95_u4_t, P95_DebRnd, 0x010de060)
GAME_VAR_DEF(p95_u16_t, P95_DebPos, 0x010de230)
GAME_VAR_DEF(uint8_t, P95_PoolPage, 0x01123282)
GAME_VAR_DEF(p95_u12_t, P95_PoolQuad, 0x01123288)
GAME_VAR_DEF(p95_line_fn, P95_DrawLine, 0x01270e00)
GAME_VAR_DEF(p95_vtx_t, P95_LineV0, 0x00b32988)
GAME_VAR_DEF(p95_vtx_t, P95_LineV1, 0x00b329c8)
#ifndef RE_HOOK_BUILD
/* начальные значения .data/.rdata Game.exe */
float P95_Near = 50.0f;                                              /* 0054609c */
int32_t P95_SndOn = 1;                                               /* 00575f54 */
p95_chandef_t P95_ChanDef = { 128, 0, 128, 64, 64, 32, 32, 64, 128, 256, 64 };              /* 0055fd50 */
p95_chanvol_t P95_ChanVol = { 682, 0, 682, 75, 682, 0, 682, 0, 682, 682, 682, 682, 682, 682, 682, 25, 682, 0, 682, 0, 682, 0 };   /* 0055fd80 */
int32_t P95_Near1 = -1, P95_Near2 = -1;                              /* 0056038c/00560390 (в .data — 0, задаются 004d65fa) */
int32_t P95_ModeSel = 2;                                             /* 00549cc8 */
p95_modetab_t P95_ModeTab = {                                        /* 0054b6c8: w, h, имя (12 байт), ?, номер */
  320, 240, 540029491u, 875700344u, 48, 0, 1,   512, 384, 540160309u, 942874744u, 52, 0, 3,
  640, 480, 540030006u, 942940280u, 48, 0, 7,   800, 600, 540028984u, 808853624u, 48, 0, 8,
  1024, 768, 875704369u, 924874784u, 14390, 0, 12,   1280, 1024, 808989233u, 824211488u, 3420720u, 0, 13,
  1600, 1200, 808465969u, 824211488u, 3158066u, 0, 14,   0xffffffffu, 0xffffffffu, 0, 0, 0, 0, 0xffffffffu };
p95_i2_t P95_CrossOfs = { -2, 3 };                                   /* 00573f48 */
p95_i6_t P95_CrossTab = { -2, -3, 2, 3, 2, -3 };                     /* 00573f50 */
#endif

static int32_t rd32(const uint8_t *p) { int32_t v; memcpy(&v, p, 4); return v; }
static void wr32(uint8_t *p, int32_t v) { memcpy(p, &v, 4); }
static float rdf(const uint8_t *p) { float v; memcpy(&v, p, 4); return v; }
static void wrf(uint8_t *p, float v) { memcpy(p, &v, 4); }
static void wrfu(uint32_t *p, float v) { memcpy(p, &v, 4); }
static int32_t ftol(double v) { return (int32_t)v; }   /* __ftol: усечение к нулю */
static int32_t Abs(int32_t v) { return v < 0 ? -v : v; }

/* ---- ссылки списка глубины ---- */
/* v1.42: частный случай общего реестра re_ptr/re_addr (game/reptr.c; массивы P95_ObjA/B/C там в статических областях) */
uint8_t *P95_ObjPtr(uint32_t ref) { return (uint8_t *)re_ptr(ref); }
uint32_t P95_ObjRef(const uint8_t *rec) { return re_addr(rec); }

/* вставка записи в список 010ffb40 по убыванию z (+zoff): после первого, у которого следующего нет или z не больше */
static void Insert(uint8_t *p, int zoff) {
  wr32(p + 0x74, 0); wr32(p + 0x70, 0);
  if (G010FFB40 == 0) { G010FFB40 = (int32_t)P95_ObjRef(p); return; }
  uint8_t *q = P95_ObjPtr((uint32_t)G010FFB40);
  while (rd32(q + 0x74) != 0 && rdf(p + zoff) < rdf(q + zoff)) q = P95_ObjPtr((uint32_t)rd32(q + 0x74));
  wr32(p + 0x74, rd32(q + 0x74));
  wr32(p + 0x70, (int32_t)P95_ObjRef(q));
  wr32(q + 0x74, (int32_t)P95_ObjRef(p));
}

/* 004d2500: tab — 11 каналов по 8 байт {активен, значение}, +0x58 — пары громкостей, +0xb0 — флаг */
void P95_SndInit(uint8_t *tab) {
  P68_D11A48 = 0; D_00d1193c = 0; P95_D1197C = 0; P95_ChanLast = -1; G2_00D11A5C = 0; P95_112D9D4 = 0;
  for (int32_t i = 0; i < 0xb; i++) {
    wr32(tab + 4 + i * 8, P95_ChanDef[i]);
    wr32(tab + i * 8, 0);
    wr32(tab + 0x58 + i * 8, P95_ChanVol[i * 2]);
    wr32(tab + 0x5c + i * 8, P95_ChanVol[i * 2 + 1]);
  }
  P95_D11A4C = 0x3e; P95_ChanState = 0x3e; P95_D11A54 = 0; P95_D11A38 = 0;
  wr32(tab + 0xb0, 1);
}

/* 004d29e1 */
void P95_SndTrigger(uint8_t *tab, int32_t ch, int32_t vol) {
  uint32_t c = (uint8_t)ch;
  if (P62_BusyB == 0 && P95_SndOn != 0 && rd32(tab + c * 8) == 0 && P95_SndReady != 0) {
    P95_ChanLast = (int32_t)c;
    wr32(tab + c * 8, rd32(tab + 4 + c * 8));
    int32_t v = (P95_SndRate == 8000) ? rd32(tab + 0x5c + c * 8) : rd32(tab + 0x58 + c * 8);
    AddClamp4095_004D2ADE((int32_t)((uint32_t)v * (uint32_t)vol) >> 12);
    if (c == 4) Call004D2D85(0x8009);
    if (c == 3) Call004D2D85(0x800b);
  }
}

/* 00405450: сброс флагов заезда/интерфейса */
void P95_ResetRace(void) {
  P95_BDF9D4 = 0; P95_BDF9D0 = 0; P95_B87E14 = 0; P95_BDFA14 = 0; P95_B87E34 = 0; P95_B87E3C = 0; P52_FogOn = 0;
  G6_00B87EA0 = 0; P95_B87EA4 = 0; P56_B87EA8 = 0; G6_00B87EAC = 0; P58_SB87EB0 = 0; P95_B87EB4 = 0; P95_B87EBC = 0;
  P95_B87EC0 = 0; P95_B87EC4 = 0; P95_B87ED0 = 0; P95_B87E40 = 0; P95_B87ED8 = 0; P95_B87EDC = 0; P95_B87EE0 = 0;
  P95_SndOn = 1; P28_BadGuyFlag = 0; P95_B87F08 = 0; P95_C818B8 = 0; P95_BDFA0C = 0; G00BDF984 = 0; P95_BDFA60 = 0;
  P95_BDFA5C = 0; P95_D11920 = 0; P55_PopSkip = 1; P14_00b202d8 = 0; P14_00b202dc = 0; P95_575F1C = 0; P13_00b201dc = 0;
  G00D17B08 = 0;
  if (GameMode == 0) { P14_00b87e84 = 0; P26_FxA = 0; P26_FxB = 0; P26_FxD = 0; }
}

/* 004e5d64: есть ли в кольцевом списке s->list (вперёд или назад) подряд больше n совпадений с историей 00d044e0 */
static int32_t Hist(int32_t i) { int32_t v; memcpy(&v, &A_00D044E0[(size_t)i * 4], 4); return v; }
int32_t P95_SeqMatch(const p95_seq_t *s) {
  const int32_t n = s->n;
  if (s->list == NULL) return 0;
  for (int dir = 1; dir >= -1; dir -= 2)
    for (int32_t i = 0; i < n; i++) {
      if (Hist(0) != s->list[i]) continue;
      int32_t k = 0, j = i;
      while (k < (int32_t)(sizeof(g8_bytes_t) / 4) && Hist(k) == s->list[j]) {
        k++; j += dir;
        if (dir > 0 && n <= j) j = 0;
        if (dir < 0 && j < 0) j = n - 1;
      }
      if (n < k) return 1;
    }
  return 0;
}

/* 004ba57a / 004ba64d: записи ближе P95_Near по z (+8) пропускаются, остальные — в список глубины */
void P95_SortObjC(void) {
  uint8_t *p = P95_ObjC;
  for (int32_t n = G010FFA20; n != 0; n--, p += 0x78) if (P95_Near <= rdf(p + 8)) Insert(p, 8);
}
void P95_SortObjB(void) {
  uint8_t *p = P95_ObjB;
  for (int32_t n = G010FFD04; n != 0; n--, p += 0x78) if (P95_Near <= rdf(p + 8)) Insert(p, 8);
}

/* 004ba457: 200 записей; у отмеченных (флаг 2 в +0x68) — положение в системе камеры (+0x10), затем в список по z (+0x18) */
void P95_SortObjA(void) {
  uint8_t *p = P95_ObjA;
  P44_MatPtr = (float *)P44_ViewMatT;
  for (int32_t n = 200; n != 0; n--, p += 0x78) {
    if ((rd32(p + 0x68) & 2) == 0) continue;
    wrf(p + 0x10, rdf(p) - P44_CamX); wrf(p + 0x14, rdf(p + 4) - P44_CamY); wrf(p + 0x18, rdf(p + 8) - P44_CamZ);
    float v[3]; memcpy(v, p + 0x10, 12); P44_Xform(v); memcpy(p + 0x10, v, 12);
    wr32(p + 0x74, 0); wr32(p + 0x70, 0);
    if (P95_Near <= rdf(p + 0x18)) Insert(p, 0x18);
  }
}

/* 004c5f69: если в точке есть дорога — номер блока карты + 1, когда блок загружен в один из 4 слотов, иначе 0 */
int32_t P95_SlotAt(int32_t x, int32_t z) {
  if (P72_RoadLookup(x, z) == 0) return 0;
  if ((int16_t)P72_Id == 0) return 0;
  int32_t cx = (x + 0x2ee + P62_MapC64) / 0x5dc, cy = (P62_Map2C40 - (z - 0x2ee)) / 0x5dc;
  if (cx < 0 || P62_MapW <= cx || cy < 0 || P62_MapH <= cy) return 0;
  int32_t b = ((P72_Rows - 1) - cy / P62_MapN) * P80_Cols + cx / P62_MapN;
  if (b == P87_SlotLumpA[0] || b == P87_SlotLumpA[1] || b == P87_SlotLumpA[2] || b == P87_SlotLumpA[3]) return b + 1;
  return 0;
}

/* 004d6ef2: фоновые звуки — случайная пауза, затем дорожка из таблицы 00b20310 (по кадру), не чаще паузы */
void P95_AmbientTick(void) {
  if (G6_00B20364 == 0) return;
  if ((int32_t)G2_00D11A5C < 0x2aa || P95_AmbN < 1 || G6_00B20368 < 1) { G8_00B2034C = 0; return; }
  if (G8_00B2034C == 0) {
    uint32_t r = Rand_004D9078();
    G8_00B2034C = 1;
    P75_B20350 = (int32_t)((r & 3) * 0x32 + 200 + (r & 7));
    return;
  }
  P75_B20350 = P75_B20350 - 1;
  if (P75_B20350 < 1) {
    int32_t i = P62_Frame % G6_00B20368;
    uint8_t *e = &A_00B20310[(size_t)i * 8];
    if (P75_B20350 < P62_Frame - rd32(e + 4)) {
      TryStartTrack_004D611B((uint32_t)(rd32(e) + 0xf000));
      wr32(e + 4, P62_Frame);
    }
    uint32_t r = Rand_004D9078();
    P75_B20350 = (int32_t)((r & 7) * 0x32 + 0x2ee + (r & 0x1f));
  }
}

/* 004c08bb */
void P95_InitDebris(void) {
  P95_Deb0 = (int32_t)(Rand_004D9078() & 0x7ff);
  P95_Deb1 = 0;
  for (int i = 0; i < 4; i++) P95_DebRnd[i] = Rand_004D9078() & 0x7ff;
  G010DE22C = 1; G010DE228 = 1; G010DE224 = 1; G010DE220 = 1;
  static const uint32_t pos[16] = { 0x434d0000u, 0x41a00000u, 0x43910000u, 0, 0x434d0000u, 0x41a00000u, 0xc3898000u, 0,
                                    0xc34d0000u, 0x41a00000u, 0x43910000u, 0, 0xc34d0000u, 0x41a00000u, 0xc3898000u, 0 };
  for (int i = 0; i < 16; i++) if ((i & 3) != 3) P95_DebPos[i] = pos[i];   /* 205,20,290 / 205,20,−275 / −205,20,290 / −205,20,−275 */
}

/* 004ab808: значок CARPOOL6 → страница и прямоугольник (4 индекса, 8 uv) */
void P95_PoolIconInit(void) {
  const uint8_t *r = P93_FindIcon("CARPOOL6");
  P95_PoolIcon = re_addr(r);
  if (r == NULL) return;
  P95_PoolQuad[0] = 0; P95_PoolQuad[1] = 1; P95_PoolQuad[2] = 2; P95_PoolQuad[3] = 3;
  P95_PoolPage = r[8];
  wrfu(&P95_PoolQuad[4], (float)(r[9] + 1));
  wrfu(&P95_PoolQuad[5], (float)((uint32_t)r[10] + r[12]));
  wrfu(&P95_PoolQuad[6], (float)((uint32_t)r[9] + r[11]));
  wrfu(&P95_PoolQuad[7], (float)((uint32_t)r[10] + r[12]));
  wrfu(&P95_PoolQuad[8], (float)((uint32_t)r[9] + r[11]));
  wrfu(&P95_PoolQuad[9], (float)(r[10] + 1));
  wrfu(&P95_PoolQuad[10], (float)(r[9] + 1));
  wrfu(&P95_PoolQuad[11], (float)(r[10] + 1));
}

/* 0040b0fe: ширина строки текущим шрифтом меню (00b5d77c1) — то же, что 0040b1cc */
float P95_TextWidthCur(const uint8_t *s) { return P58_TextWidth(s, (int32_t)MenuByte5D77C1); }

/* 00507de2: поворот точек (x, —, z, —) на угол ang (при 00bdfa54 — без поворота), масштаб 0125f3e0 и сдвиг ofs */
void P95_MapRotate(const int32_t *src, int32_t *dst, int32_t n, const float *ofs, int32_t ang) {
  float sn = P43_Sin[ang], cs = P43_Sin[ang + 0x400];
  if (MenuOptBDFA54 != 0) { sn = P43_Sin[0]; cs = P43_Sin[0x400]; }
  for (; n != 0; n--, src += 4, dst += 4) {
    float x = (float)src[0], z = (float)src[2];
    dst[0] = ftol((double)x * cs + (double)z * -sn);
    dst[2] = ftol((double)x * sn + (double)z * cs);
    dst[0] = ftol((double)(float)dst[0] * P19_Scale + ofs[0]);
    dst[2] = ftol((double)(float)dst[2] * P19_Scale + ofs[2]);
  }
}

/* 0049f418: матрица вида из кватерниона, курс P59_AngB = atan2 по третьей строке, транспонат */
void P95_CamFromQuat(const float *q) {
  P43_QuatToMat(q, P44_ViewMat);
  int32_t a = ftol((double)P44_ViewMat[8] * 100000.0), b = ftol((double)-P44_ViewMat[6] * 100000.0);
  P59_AngB = (uint16_t)P44_Atan2(b, a);
  P44_Transpose(P44_ViewMat, P44_ViewMatT);
}

/* 0048f6c1: сколько активных записей трафика в квадрате r вокруг точки; ближайшее манхэттенское расстояние — в 011443c8 */
static int32_t RoundMul(int32_t v) { return (int32_t)lrintl((long double)(float)v * (long double)P63_Scale); }
int32_t P95_CountNear(int32_t x, int32_t z, int32_t r) {
  const uint8_t *p = (const uint8_t *)TrafficRecs;
  int32_t cnt = 0;
  P11_00ba52d0 = RoundMul(x + 0x2ee);
  int32_t px = P11_00ba52d0;
  P11_00ba52d0 = RoundMul(z - 0x2ee);
  P63_Near = 0x400;
  for (int32_t i = 0; i < P51_TrafficN && i < 0x40; i++, p += 0x54) {
    if (p[1] == 0 || (p[1] == 1 && p[2] == 0)) continue;
    int32_t dx = Abs(rd32(p + 0x48) - px), dz = Abs(rd32(p + 0x4c) - P11_00ba52d0);
    if (dx < r && dz < r) { if (dx + dz < P63_Near) P63_Near = dx + dz; cnt++; }
  }
  return cnt;
}

/* 004d65fa: две ближайшие к камере записи трафика типа 4 (не в состоянии 2) — номера+1 в 0056038c/00560390 */
void P95_NearestTwo(void) {
  const uint8_t *p = (const uint8_t *)TrafficRecs;
  int32_t best = 10000, second = 10000;
  P95_Near2 = -1; P95_Near1 = P95_Near2;
  P11_00ba52d0 = (int32_t)lrintf(P44_CamX);
  int32_t cx = P11_00ba52d0 / 0x5dc;
  P11_00ba52d0 = (int32_t)lrintf(P44_CamZ);
  for (int32_t i = 0; i < 0x40; i++, p += 0x54) {
    if (p[1] != 4 || p[0xc] == 2) continue;
    int32_t d = Abs(rd32(p + 0x48) - cx) + Abs(rd32(p + 0x4c) - P11_00ba52d0 / 0x5dc);
    if (d < best) { P95_Near2 = P95_Near1; P95_Near1 = i + 1; second = best; best = d; }
    else if (d < second) { P95_Near2 = i + 1; second = d; }
  }
}

/* 00405abe: настройки по умолчанию (режим 640×480, раскладка, громкости 1.0, звук 22050/16 бит) */
void P95_DefaultOptions(void) {
  P95_ModeSel = 2;
  P68_ModeW = (int32_t)P95_ModeTab[P95_ModeSel * 7];
  P68_ModeH = (int32_t)P95_ModeTab[P95_ModeSel * 7 + 1];
  P35_InputMode = 0;
  memcpy(P36_KeyCfg, &P54_KeySrc[0], 20);
  memcpy(&P54_KeySrc[6], &P54_KeySrc[0], 20);
  P54_Keys3[0] = P54_KeySrc[12]; P54_Keys3[1] = P54_KeySrc[13]; P54_Keys3[2] = P54_KeySrc[14];
  G00575F40 = 1; Q00B87E90 = 1; Q00B87E94 = 1;
  WF00575F14 = 1.0f; WF00575F18 = 1.0f;
  MenuState575EF0 = 2; P19_Scale = 1.0f; Q00B87EF0 = 0; P21_FrameMin = 1; G00575F48 = 1; G00575F24 = 1; WI00B87E2C = 1;
  P21_FrameFlagB = 1; P21_FrameFlagA = 1; G6_00575F00 = 8; G6_00575F04 = 0x5622; G6_00B87E50 = 0;
  P13_Fn004064B4(1, 1);
}

/* 00509d27: линия Glide цветом 0xRRGGBB (оба конца +2 пикселя), состояние и смешивание сбрасываются как в 0042... */
void P95_DrawLineRGB(int32_t x0, int32_t y0, int32_t x1, int32_t y1, uint32_t rgb) {
  float a[16], b[16];
  memset(a, 0, sizeof a); memset(b, 0, sizeof b);   /* z, ooz, a в оригинале не заданы (стек) */
  if (P85_StateDirty != 0) { P85_StateFn(1, 0, 0, 2, 0); P85_StateDirty = 0; }
  if (P85_BlendCur != 0) { P85_BlendFn(4, 0, 4, 0); P85_BlendCur = 0; }
  a[0] = (float)(x0 + 2); a[1] = (float)(y0 + 2);
  b[3] = a[3] = (float)((int32_t)rgb >> 16 & 0xff);
  b[4] = a[4] = (float)((int32_t)rgb >> 8 & 0xff);
  b[5] = a[5] = (float)(rgb & 0xff);
  b[8] = a[8] = (P55_BDFA18 == 0) ? 0.015625f : 1.0f;   /* oow: 0x3c800000 / 0x3f800000 */
  b[0] = (float)(x1 + 2); b[1] = (float)(y1 + 2);
  P95_DrawLine(a, b);
  P85_StateDirty = -1;
  P85_BlendCur = 0xff;
}

/* 004d0f28: шаг поворота угла (ось из скрипта: 0 — +0x10, 1 — +0x12, 2 — +0x14 контекста) к цели; при достижении — следующая команда */
int32_t P95_ScriptTurn(void) {
  const uint8_t *s = P10_ScriptPtr;
  int16_t axis; uint16_t step, target; memcpy(&axis, s + 2, 2); memcpy(&step, s + 4, 2); memcpy(&target, s + 6, 2);
  if (axis < 0 || axis > 2) return 0;   /* в оригинале указатель не инициализирован */
  uint8_t *a = P10_ScriptCtx + 0x10 + axis * 2;
  uint16_t cur; memcpy(&cur, a, 2);
  int32_t lim = (step < 0x800) ? (int32_t)step : 0x1000 - (int32_t)step;
  int32_t d = Abs((int32_t)target - (int32_t)(int16_t)cur);
  if (lim <= d) { cur = (uint16_t)((cur + step) & 0xfff); memcpy(a, &cur, 2); return 0; }
  P10_ScriptPtr = P10_ScriptPtr + 8;
  memcpy(a, &target, 2);
  return 1;
}

/* 00507310: три отрезка ломаной (крестик) вокруг pos (x, —, z) — линии Glide через вершины 00b32988/00b329c8 */
void P95_DrawCross(const float *pos) {
  int32_t x = ftol((double)(float)P95_CrossOfs[0] + pos[0]);
  int32_t y = ftol((double)(float)P95_CrossOfs[1] + pos[2]);
  for (int i = 0; i < 3; i++) {
    P95_LineV0[0] = (float)x; P95_LineV0[1] = (float)y;
    x = ftol((double)(float)P95_CrossTab[i * 2] * P19_Scale + pos[0]);
    y = ftol((double)(float)P95_CrossTab[i * 2 + 1] * P19_Scale + pos[2]);
    P95_LineV1[0] = (float)x; P95_LineV1[1] = (float)y;
    P95_DrawLine(P95_LineV0, P95_LineV1);
  }
}
