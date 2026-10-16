/* v1.58 (см. ported113.h). */
#include "ported113.h"
#include "ported11.h"
#include "ported12.h"
#include "ported44.h"
#include "ported54.h"
#include "ported76.h"
#include "ported82.h"
#include "ported98.h"
#include "ported100.h"
#include "ported103.h"
#include "ported6.h"
#include "ported42.h"
#include "ported43.h"
#include "ported53.h"
#include "ported79.h"
#include "ported81.h"
#include "ported84.h"
#include "ported85.h"
#include "ported99.h"
#include "reptr.h"
#include "menu57.h"
#include "p57_data.h"
#include "strtab.h"
#include "ported102.h"
#include <string.h>
#include <math.h>

static float rdf(const void *p) { float v; memcpy(&v, p, 4); return v; }
static int32_t rd32(const void *p) { int32_t v; memcpy(&v, p, 4); return v; }
static void wr32(void *p, int32_t v) { memcpy(p, &v, 4); }
static int16_t rd16s(const void *p) { int16_t v; memcpy(&v, p, 2); return v; }
static const float K_ONE  = 1.0f;      /* .rdata 00546020 */
static const float K_FIVE = 5.0f;      /* .rdata 00546188 */

GAME_VAR_DEF(uint32_t, P113_MrkRec, 0x00c812bc)
GAME_VAR_DEF(int32_t, P113_MrkId, 0x00d0271c)
GAME_VAR_DEF(int32_t, P113_MrkFall, 0x00d02648)
GAME_VAR_DEF(int32_t, P113_MrkGround, 0x00d02714)
GAME_VAR_DEF(p113_m16_t, P113_MrkMat, 0x00d026c0)

#ifndef RE_HOOK_BUILD
p57_menutab_t P57_MenuTab = { P57_MENU_INIT };
#endif

/* ---- 004048dd ---- */
void P113_MenuOpts(void) {
  static const struct { uint8_t flag; uint32_t fn; uint16_t str; } k_opt[10] = {
    { 0, 0x00404eb0u, 0xf1 }, { 1, 0x00404ec9u, 0xf2 }, { 2, 0x00404ee2u, 0xf3 }, { 3, 0x00404efbu, 0xf4 },
    { 4, 0x00404f14u, 0xf5 }, { 7, 0x00404f2du, 0xaf }, { 10, 0x00404f46u, 0x10f }, { 6, 0x00404f5fu, 0x64 },
    { 8, 0x00404f70u, 0xb0 }, { 9, 0x00404faeu, 0xb1 } };    /* флаг 00bdf9e0 + 4·flag, обработчик, строка 00c55820 + 4·str */
  uint32_t c = 0;
  P54_Out[0] = P97_StrAddr[0x63];                            /* 00c559ac */
  for (int32_t i = 0; i < 10; i++) {
    if (P102_BDF9E0[k_opt[i].flag] == 0) continue;
    P57_OPT_FN(c, 0) = 0x00404e52u; P57_OPT_FN(c, 1) = 0x00404e7eu; P57_OPT_FN(c, 2) = k_opt[i].fn;
    P54_Out[(c * 2 + 1) * 4] = P97_StrAddr[k_opt[i].str];
    P54_SelTab[c] = i;
    c++;
  }
  if (c == 0) {
    P57_OPT_FN(0, 0) = 0x00404e52u; P57_OPT_FN(0, 1) = 0x00404e7eu; P57_OPT_FN(0, 2) = 0x00404ffeu;
    for (int32_t j = 0; j < 4; j++) P57_OPT_NAV(0, j) = 0;
    P54_Out[4] = P97_StrAddr[0xd3];                          /* 00c55b6c */
    P54_SelTab[0] = -1;
    c = 1;
  } else {
    for (uint32_t i = 0; i < c; i++) {
      P57_OPT_NAV(i, 0) = (uint8_t)i; P57_OPT_NAV(i, 1) = (uint8_t)i;
      P57_OPT_NAV(i, 2) = (uint8_t)(i - 1); P57_OPT_NAV(i, 3) = (uint8_t)(i + 1);
    }
    P57_OPT_NAV(0, 2) = (uint8_t)(c - 1);
    P57_OPT_NAV(c - 1, 3) = 0;
  }
  P57_OPT_FN(c, 0) = 0; P57_OPT_FN(c, 1) = 0; P57_OPT_FN(c, 2) = 0;
  for (int32_t j = 0; j < 4; j++) P57_OPT_NAV(c, j) = 0;
  P54_Out[(c * 2 + 1) * 4] = 0;
  P54_SelTab[c] = -1;
  P54_MenuTexSel();
}

/* ---- 004e969f ---- */
void P113_Heli(int32_t mode) {
  static float m[16];                                       /* оригинал: стековая матрица (указатель 00bdc28c остаётся на ней) */
  if (mode == 0) {
    if (G6_00B5A778 != 0) return;
    const uint8_t *rec = (const uint8_t *)re_ptr(P113_MrkRec);
#ifndef RE_HOOK_BUILD
    if (rec != NULL)
#endif
    if (rd32(rec + 0x10) == P113_MrkId) P113_MrkFall = 1;
    float v[4] = { 0.0f, 0.0f, 1.0f, 0.0f }, up[4] = { 0.0f, 1.0f, 0.0f, 0.0f }, r[4] = { 0 }, u[4] = { 0 };
    memset(m, 0, sizeof m);
    m[0] = 1.0f; m[4] = 1.0f; m[8] = 1.0f;
    int32_t ax = (int16_t)P42_AngY, ay = (int16_t)P42_AngX;   /* movsx 00d02700 / 00d02702 */
#ifndef RE_HOOK_BUILD
    ax &= 0xfff; ay &= 0xfff;                                 /* native: не читать до начала таблицы синусов */
#endif
    P44_RotX(m, ax);
    P44_RotY(m, ay);
    P44_MatPtr = m;
    P44_Xform(v);
    P43_Normalize(v);
    P43_Cross(r, v, up);
    P43_Cross(u, r, v);
    P113_MrkMat[1] = u[0]; P113_MrkMat[4] = u[1]; P113_MrkMat[7] = u[2];
    P113_MrkMat[0] = r[0]; P113_MrkMat[3] = r[1]; P113_MrkMat[6] = r[2];
    P113_MrkMat[2] = v[0]; P113_MrkMat[5] = v[1]; P113_MrkMat[8] = v[2];
    if (P113_MrkFall != 0) {
      float d[3]; d[0] = 0.0f; memcpy(&d[1], &P81_Flag, 4); d[2] = 0.0f;   /* 00d02708 — float */
      P44_Xform(d);
      d[1] = d[1] - 1.6006666f;                               /* .rdata 005469c8 */
      P53_Mrk[4] = P53_Mrk[4] + d[0];
      P53_Mrk[5] = P53_Mrk[5] + d[1];
      P53_Mrk[6] = P53_Mrk[6] + d[2];
      P53_Mrk[0] = P53_Mrk[0] + P53_Mrk[4];
      P53_Mrk[1] = P53_Mrk[1] - P53_Mrk[5];
      P53_Mrk[2] = P53_Mrk[2] + P53_Mrk[6];
      if ((float)P113_MrkGround < P53_Mrk[1]) {
        P53_Mrk[1] = (float)P113_MrkGround;
        P53_Mrk[4] = 0.0f; P53_Mrk[5] = 0.0f; P53_Mrk[6] = 0.0f;
      }
      P81_Flag = 0;
      if (P99_Mrk2710 < 200) {
        P81_Limit(P113_MrkGround - 1000);
        P42_SetViewAngles(-180, 0x4b0, 0, (float)P99_Mrk2710 / 200.0f);   /* .rdata 00546200 */
      } else P81_Limit(P113_MrkGround - 13000);
      P99_Mrk2710 = P99_Mrk2710 + 1;
    }
    P99_Mrk270C = (P99_Mrk270C + 0x5a) & 0xfff;
    return;
  }
#ifndef RE_HOOK_BUILD
  if (P53_Var2634 == 0 || P99_MrkB == 0) return;
#endif
  if (P82_SphereVis3D(P53_Mrk, rdf((const uint8_t *)P79_PTR(P53_Var2634) + 0xc)) == 0) return;
  if (P76_InBox(P53_Mrk, (const uint8_t *)P82_LightGrid, P82_CellCX, P82_CellCY) == 0) return;
  float pos[3] = { P53_Mrk[0] - P44_CamX, P53_Mrk[1] - P44_CamY, P53_Mrk[2] - P44_CamZ };
  P44_MatPtr = (float *)P44_ViewMatT;
  P44_Xform(pos);
  memcpy(m, P113_MrkMat, sizeof m);
  m[0] = -m[0]; m[1] = -m[1]; m[2] = -m[2];
  m[6] = -m[6]; m[7] = -m[7]; m[8] = -m[8];
  P84_DrawModel((uint32_t)P53_Var2634, m, pos, 1);
  pos[0] = -340.0f * m[2] + -290.0f * m[1] + (P53_Mrk[0] - P44_CamX);   /* .rdata 005469cc / 005469d0 */
  pos[1] = -340.0f * m[5] + -290.0f * m[4] + (P53_Mrk[1] - P44_CamY);
  pos[2] = -340.0f * m[8] + -290.0f * m[7] + (P53_Mrk[2] - P44_CamZ);
  P44_MatPtr = (float *)P44_ViewMatT;
  P44_Xform(pos);
  P44_RotY(m, P99_Mrk270C);
  P85_BlendForce = 2;
  P12_Fn00426580(0);
  P84_DrawModel((uint32_t)P99_MrkB, m, pos, 1);
  P85_BlendForce = 0;
}

/* ---- 005129e1 ---- */
void P113_PartDraw(uint8_t *p) {
  int32_t ty = rd32(p + 0x1c) - 1;
  int32_t k = rd32(p + 0x34);
#ifndef RE_HOOK_BUILD
  if (ty < 0 || ty >= 4) return;
  if (k < 0 || (P103_PathLen[ty] > 0 && k >= P103_PathLen[ty])) return;
#endif
  const uint8_t *buf = (const uint8_t *)P54_Tab4[ty];
#ifndef RE_HOOK_BUILD
  if (buf == NULL) return;
#endif
  int32_t st = P12_00c821a0 * 0x14 + 0x10;
  const float *fr = (const float *)(buf + st * k);
  const float *f0 = NULL;
  float t = 0.0f, y;
  if ((rd32(p + 0xc) & 0x80) == 0) {
    y = fr[1];
  } else {
    int32_t w = rd16s(p + 4);                                  /* 00c81b7c[w] = P54_Tab4[w-1] */
#ifndef RE_HOOK_BUILD
    if (w < 1 || w > 4 || P54_Tab4[w - 1] == NULL) return;
#endif
    f0 = (const float *)P54_Tab4[w - 1];
    if (rd32(p + 0x40) > 4) wr32(p + 0x40, 5);
    if (rd32(p + 0x40) < 0) wr32(p + 0x40, 0);
    t = (float)(5 - rd32(p + 0x40)) / K_FIVE;
    y = (K_ONE - t) * (f0[1] - fr[1]) + fr[1];
  }
  P100_PartBase[0] = rdf(p + 0x84);
  P100_PartBase[1] = y + rdf(p + 0x88);
  P100_PartBase[2] = rdf(p + 0x8c);
  float dx = P100_PartBase[0] - P44_CamX, dz = P100_PartBase[2] - P44_CamZ;
  P11_00ba52d0 = (int32_t)lrintf(dx); int32_t ax = P11_00ba52d0 < 0 ? -P11_00ba52d0 : P11_00ba52d0;
  P11_00ba52d0 = (int32_t)lrintf(dz); int32_t az = P11_00ba52d0 < 0 ? -P11_00ba52d0 : P11_00ba52d0;
  int32_t d = ax < az ? az + ax / 2 : ax + az / 2;
  if (d >= 0x3a99) return;
  P100_PartMode = P82_SphereVis3D(P100_PartBase, 800.0f);       /* 0x44480000 */
  if (P100_PartMode == 0) return;
  if (P76_InBox(P100_PartBase, (const uint8_t *)P82_LightGrid, P82_CellCX, P82_CellCY) == 0) return;
  int16_t ang[3] = { rd16s(p + 0x5c), rd16s(p + 0x5e), rd16s(p + 0x60) };
  float q[5], pos[3] = { 0.0f, 0.0f, 0.0f };
  P44_EulerToQuat(ang, q);
  P100_PartModel = rd32(p + 0x44);
  if ((rd32(p + 0xc) & 0x80) == 0) {
    P100_DrawParts(p, fr + 4, (const uint8_t *)P100_PartNodes, q, pos);
  } else {
    P12_Fn004F3E78(fr, f0, t);
    P100_DrawParts(p, (const float *)P12_PartLerp, (const uint8_t *)P100_PartNodes, q, pos);
  }
#ifndef RE_HOOK_BUILD
  if (P98_IconN < 0 || P98_IconN >= (int32_t)(sizeof(P98_IconIdx) / sizeof(P98_IconIdx[0]))) return;
#endif
  P98_IconIdx[P98_IconN] = (int32_t)rd16s(p + 2);
  P98_IconN = P98_IconN + 1;
}
