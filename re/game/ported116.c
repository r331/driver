/* v1.61 (см. ported116.h). */
#include "ported116.h"
#include "reptr.h"
#include "ported107.h"
#include "ported95.h"
#include "ported103.h"
#include "ported115.h"
#include "ported98.h"
#include "ported99.h"
#include "ported100.h"
#include "ported86.h"
#include "ported94.h"
#include "ported110.h"
#include "ported114.h"
#include "ported97.h"
#include "unported.h"
#include "p111_data.h"
#include <math.h>

GAME_VAR_DEF(p116_skid_t, P116_SkidRecA, 0x00b5c950)
GAME_VAR_DEF(p116_skid_t, P116_SkidRecB, 0x00b6e950)
GAME_VAR_DEF(p116_v4_t, P116_SkidV, 0x00b5c6e0)
GAME_VAR_DEF(float, P116_K546A3C, 0x00546a3c)
GAME_VAR_DEF(uint32_t, P116_MBar, 0x00b5a740)
GAME_VAR_DEF(uint32_t, P116_MSlider, 0x00b5a744)
GAME_VAR_DEF(float, P116_MLevB, 0x00b5a748)
GAME_VAR_DEF(float, P116_MLevA, 0x00b5a74c)
GAME_VAR_DEF(int32_t, P116_Blink, 0x00b5a760)
GAME_VAR_DEF(int32_t, P116_BlinkT, 0x005755c0)
GAME_VAR_DEF(int32_t, P116_SndB2035C, 0x00b2035c)

static int32_t rd32(const void *p) { int32_t v; memcpy(&v, p, 4); return v; }
static int16_t rd16(const void *p) { int16_t v; memcpy(&v, p, 2); return v; }
static float rdf(const void *p) { float v; memcpy(&v, p, 4); return v; }
static void wr32(void *p, int32_t v) { memcpy(p, &v, 4); }
static void wrf(void *p, float v) { memcpy(p, &v, 4); }
static int32_t f2b(float f) { int32_t v; memcpy(&v, &f, 4); return v; }
static const float SNAP = 1048576.0f;     /* .rdata 0054607c */
static const float NEAR_Z = 50.0f;        /* .rdata 0054609c */
static const float FAR_Z = 45000.0f;      /* .rdata 00546030 */
static const float SKID_R = 6000.0f;      /* .rdata 00546a80 / 00546a7c (−) */
#define ZTAB_N ((int32_t)(sizeof P12_00ba53a0 / sizeof P12_00ba53a0[0]))

static void state_set(int32_t a, int32_t b, int32_t c, int32_t d, int32_t e, int32_t tag) {
  if (P85_StateDirty != tag) { if (P85_StateFn) P85_StateFn(a, b, c, d, e); P85_StateDirty = tag; }
}
static void blend_set(int32_t a, int32_t b, int32_t c, int32_t d, uint8_t tag) {
  if (P85_BlendCur != tag) { if (P85_BlendFn) P85_BlendFn(a, b, c, d); P85_BlendCur = tag; P69_BlendOn = tag; }
}
static void tex_select(uint32_t page) {
  if (page != (uint32_t)P86_CurTex) {
    P86_CurTex = (int32_t)page;
    if (P86_TexSrc) P86_TexSrc(0, (uint32_t)rd32(&g_01145a60[page * 0x10 + 8]), 3, (uint32_t)rd32(&g_01145a60[page * 0x10 + 0xc]));
  }
}
static void raster(const p85_rv *a, const p85_rv *b, const p85_rv *c) { if (P85_RasterB) P85_RasterB(a, b, c); }

/* ---- 004159e5: ползунки экрана настроек (467,381) и (467,406); выбранный пункт 0x12 / 0x13 — красный ---- */
void P116_Sliders2(void) {
  if (G6_00B87EEC == 0) return;
  int32_t g1 = 0xff, g2 = 0xff;
  if (MenuI005FE9D0 == 0x12) g1 = 0;
  if (MenuI005FE9D0 == 0x13) g2 = 0;
  if (P103_Slider != NULL) {
    P115_IconAt(467.0f, 381.0f, re_addr(P103_Slider), 0xff, g1, g1, 0, 0);
    P115_IconAt(467.0f, 406.0f, re_addr(P103_Slider), 0xff, g2, g2, 0, 0);
  }
  if (P103_SliderBar != NULL) {
    P110_IconQuad(467.0f, 381.0f, WF00575F14, 1.0f, P103_SliderBar, 0xff, (uint32_t)g1, (uint32_t)g1, 0);
    P110_IconQuad(467.0f, 406.0f, WF00575F18, 1.0f, P103_SliderBar, 0xff, (uint32_t)g2, (uint32_t)g2, 0);
  }
}

/* ---- 00417651: пять ползунков экрана графики (x 467, y 310..406 шагом 24): уровни c, b, a, d, e ---- */
void P116_Sliders5(float a, float b, float c, float d, float e, int32_t sel) {
  static const float ys[5] = { 310.0f, 334.0f, 358.0f, 382.0f, 406.0f };
  const float lv[5] = { c, b, a, d, e };
  int32_t gb[5];
  for (int32_t i = 0; i < 5; i++) gb[i] = (sel == i) ? 0 : 0xff;
  if (Q005FEA24 != 0)
    for (int32_t i = 0; i < 5; i++) P115_IconAt(467.0f, ys[i], (uint32_t)Q005FEA24, 0xff, gb[i], gb[i], 0, 0);
  if (Q005FEA20 != 0) {
    const uint8_t *bar = (const uint8_t *)re_ptr((uint32_t)Q005FEA20);
    for (int32_t i = 0; i < 5; i++) P110_IconQuad(467.0f, ys[i], lv[i], 1.0f, bar, 0xff, (uint32_t)gb[i], (uint32_t)gb[i], 0);
  }
}

/* ---- 0050eaaa: меню паузы / ввода имени ---- */
void P116_PauseMenu(void) {
  uint32_t m = (uint32_t)G00B5A730;
  if (m == 0 || P29_Mode != 0) return;
  SoundMenuSave0051080E();
  if (S_00B5A77C == 0) {
    P12_Fn00426580(0x18);
    if (m == 0x00574f08u) {
      int32_t g1 = (G00575550 == 0xd) ? 0 : 0xff, g2 = (G00575550 == 0xe) ? 0 : 0xff;
      if (P116_MSlider != 0) {
        P115_IconFlip(401.0f, 351.0f, P116_MSlider, 0xff, g1, g1, 0, 0);
        P115_IconFlip(401.0f, 376.0f, P116_MSlider, 0xff, g2, g2, 0, 0);
      }
      if (P116_MBar != 0) {
        P115_IconScaled(401.0f, 351.0f, WF00575F14, 1.0f, P116_MBar, 0xff, g1, g1, 0);
        P115_IconScaled(401.0f, 376.0f, WF00575F18, 1.0f, P116_MBar, 0xff, g2, g2, 0);
      }
    }
    if (m == 0x00575088u) {
      int32_t g1 = (G00575550 == 0x1f) ? 0 : 0xff, g2 = (G00575550 == 0x20) ? 0 : 0xff;
      if (P116_MSlider != 0) {
        P115_IconFlip(421.0f, 421.0f, P116_MSlider, 0xff, g1, g1, 0, 0);
        P115_IconFlip(421.0f, 444.0f, P116_MSlider, 0xff, g2, g2, 0, 0);
      }
      if (P116_MBar != 0) {
        P115_IconScaled(421.0f, 421.0f, P116_MLevA, 1.0f, P116_MBar, 0xff, g1, g1, 0);
        P115_IconScaled(421.0f, 444.0f, P116_MLevB, 1.0f, P116_MBar, 0xff, g2, g2, 0);
      }
    }
    const int16_t *items = (const int16_t *)re_ptr(m);
#ifndef RE_HOOK_BUILD
    if (items == NULL) { SoundMenuOut0051082A(); return; }   /* .data меню в native не зарегистрирована */
#endif
    if (m == 0x00575370u) {
      if (--P116_BlinkT < 0) { P116_BlinkT = 10; P116_Blink ^= 1; }
      if (P52_MenuA == 0 || P116_Blink == 0) P99_MenuItems(items);
      else {
        int32_t k = P52_MenuC + P52_MenuCnt * 0x11;
#ifndef RE_HOOK_BUILD
        if (k < 0 || k + 1 >= (int32_t)sizeof(p52_names_t)) { P99_MenuItems(items); SoundMenuOut0051082A(); return; }
#endif
        uint8_t *nt = (uint8_t *)&P52_NameTab[0];
        nt[k] = 0x5f; nt[k + 1] = 0;
        P99_MenuItems(items);
        nt[k] = 0;
      }
    } else P99_MenuItems(items);
  } else {
    P116_FullMap();
    P12_Fn00426580(0x18);
  }
  SoundMenuOut0051082A();
}

/* ---- 00506c96: значок объекта на радаре (если в пределах 62 клеток) ---- */
void P116_RadarIcon(const int32_t *pos, int32_t unused, uint8_t r, uint8_t g, uint8_t b, float scale) {
  (void)unused;
  if (P56_Sprite == NULL) return;
#ifndef RE_HOOK_BUILD
  if (pos == NULL) return;
#endif
  int32_t px = (P99_Cars[0].pos[0] + 0x2ee) / 0x5dc + P57_ScrW / 2;
  int32_t pz = (0x2ee - P99_Cars[0].pos[2]) / 0x5dc + S_00C808A0 / 2;
  int32_t ox = (pos[0] + 0x2ee) / 0x5dc + P57_ScrW / 2;
  int32_t oz = (0x2ee - pos[2]) / 0x5dc + S_00C808A0 / 2;
  int32_t dz = oz - pz, dx = ox - px;
  if (!(dz < 0x3e && -0x3e < dz && -0x3e < dx && dx < 0x3e)) return;
  uint32_t h = (uint32_t)(int32_t)P94_Heading;
  float sn, cs;
  if (MenuOptBDFA54 != 0) { sn = P43_Sin[0]; cs = P43_Sin[0x400]; }
  else {
#ifndef RE_HOOK_BUILD
    if (h + 0x400u >= 0x1400u) return;   /* курс вне таблицы (в оригинале — чтение соседних данных) */
#endif
    sn = P43_Sin[h]; cs = P43_Sin[0x400 + h];
  }
  float fx = (float)dx * cs + (float)dz * sn;
  P11_00ba52d0 = (int32_t)lrintf(fx);
  int32_t x = P11_00ba52d0;
  float fz = -((float)dx * sn) + (float)dz * cs;
  P11_00ba52d0 = (int32_t)lrintf(fz);
  int32_t z = P11_00ba52d0;
  x = (int32_t)((float)x * P94_RadarK);
  z = (int32_t)((float)z * P94_RadarK);
  P11_00ba52d0 = (int32_t)lrintf(P56_F573FA0); x += P11_00ba52d0;
  P11_00ba52d0 = (int32_t)lrintf(P56_F573FA4); z += P11_00ba52d0;
  float s = P116_K546A3C * (float)P19_ScrW * P19_Scale * scale;
  float hs = s * P51_Half;
  x -= (int32_t)((float)P56_Sprite[0xb] * hs);
  z -= (int32_t)((float)P56_Sprite[0xc] * hs);
  P114_DrawSpr((float)x, (float)z, s, s, P56_Sprite, 0xff - r, 0xff - g, 0xff - b, 2);
  P114_DrawSpr((float)x, (float)z, s, s, P56_Sprite, r, g, b, 3);
}

/* ---- 004d5ce0: звуки уровня ---- */
void P116_SndLevelStart(void) {
  int32_t c = 0;
  Chain004D5FFC();
  G8_00B20344 = 0;
  for (int32_t i = 0; i < 5; i++) wr32(&A_00B20330[i * 4], -1);
  P11_00b20360 = 0;
  P95_Near2 = -1; P95_Near1 = -1;
  P107_HornVol = -10000;
  P98_DD70 = 0; P107_DDE6 = 0;
  if (G6_00B87EAC != 0) c = 0x41;
  const int32_t *p = P99_Cars[c].pos;
  SlotSetOn0052432A(0);
  P97_SndStart(0, 0, (float)p[0], (float)-p[1], (float)p[2]);
  P48_SetVoiceVolume(0, -10000);
  SlotSetOn0052432A(1);
  P97_SndStart(0x22, 1, (float)p[0], (float)-p[1], (float)p[2]);
  P48_SetVoiceVolume(1, -10000);
  SlotSetOn0052432A(5);
  P97_SndStart(0, 5, 0.0f, 0.0f, -20000.0f);
  P48_SetVoiceVolume(5, -10000);
  SlotSetOn0052432A(6);
  P97_SndStart(0, 6, 0.0f, 0.0f, -20000.0f);
  P48_SetVoiceVolume(6, -10000);
  SlotSetOn0052432A(4);
  P97_SndStart(6, 4, 0.0f, 0.0f, 0.0f);
  P48_SetVoiceVolume(4, -10000);
  SoundSetPos00523F8A(4, -1);
  if (P62_HudOff2 == 0 && G6_00B87EA0 == 0) {
    SlotSetOn0052432A(7);
    SoundPlay00523E50(7, 7, -1);
    P48_SetVoiceVolume(7, -10000);
    SlotSetOn0052432A(8);
    SoundPlay00523E50(0x21, 8, -1);
    P48_SetVoiceVolume(8, -10000);
  }
  if (P26_FxA != 0) {
    SlotSetOn0052432A(0xb);
    SoundPlay00523E50(0x15, 0xb, -1);
  }
  if (S_00D1192C == 10) P97_SndStart(7, 2, 0.0f, 0.0f, 0.0f);
  else P97_SndStart(10, 2, 0.0f, 0.0f, 0.0f);
  P48_SetVoiceVolume(2, -10000);
  SoundLoop_0052422D(2, (int32_t)re_addr(&P99_Cars[0].pos[0]));
  SlotSetOn0052432A(2);
  SlotSetOn0052432A(3);
  SlotSetOn0052432A(0xf);
  ClearPairs004D6C20();
  ClearPair004D6D68();
  P44_ResetState();
  CopyTable_004D6E9F();
  P116_SndB2035C = 0;
  P115_SndUpdate();
  P48_SetVoiceVolume(0, 0);
}

/* ---- 0040abac: строка шрифтом (позиция/масштаб/флаги — 005d77c0.., 0054aa24.., цвет 0054aa2c) ---- */
static const uint8_t *font_tab(uint32_t f) {
#ifndef RE_HOOK_BUILD
  if (f >= 8) return NULL;
#endif
  return &P58_Font[0] + f * 0x806;
}
static float text_width(const uint8_t *s, uint32_t f, float sx) {
  float w = 0.0f;
  for (;;) {
    uint8_t ch = *s;
    if (ch == 0) break;
    if (ch == 0x5e && s[1] == 0x5e) { f = (uint8_t)(s[2] - 0x30); s += 3; continue; }
    s++;
    const uint8_t *t = font_tab(f);
    if (t == NULL) continue;
    if (rd16(t + 0xe + ch * 8) == 0) w = (float)rd16(t + 0xc) * sx + w;
    else w = (float)((int32_t)t[0x14 + ch * 8] + (int32_t)rd16(t + 0xa)) * sx + w;
  }
  return w;
}
void P116_Text(uint32_t txt) {
  const uint8_t *s = (const uint8_t *)re_ptr(txt);
#ifndef RE_HOOK_BUILD
  if (s == NULL) return;
#endif
  int32_t saved = 0;
  float sx = p116_f(MenuPosX54AA24), sy = p116_f(MenuPosY54AA28);
  if (P56_F7E58 == 0) {
    const uint8_t *t0 = font_tab(MenuByte5D77C1);
    P12_Fn00426580(t0 ? (int32_t)rd16(t0 + 8) : 0);
    saved = DrvSetMode0042655A(0);
  }
  float x = p116_f(MenuVal5D77C4), y = p116_f(MenuVal5D77C8);
  uint8_t fl = MenuByte5D77C0;
  if ((fl & 2) != 0) x = x - text_width(s, MenuByte5D77C1, sx);
  else if ((fl & 1) != 0) x = x - text_width(s, MenuByte5D77C1, sx) / P19_DivC;
  if ((fl & 0x20) != 0) y = y - (float)ScanSlot_0040AAE2(MenuByte5D77C1);
#ifdef RE_HOOK_BUILD
  const uint8_t *rgb = &MenuColorR54AA2C;
#else
  const uint8_t rgb[3] = { MenuColorR54AA2C, MenuColorG54AA2D, MenuColorB54AA2E };
#endif
  for (;;) {
    uint8_t ch = *s;
    if (ch == 0) break;
    if (ch == 0x5e && s[1] == 0x5e) {
      MenuByte5D77C1 = (uint8_t)(s[2] - 0x30);
      s += 3;
      if ((MenuByte5D77C0 & 0x20) != 0) y = p116_f(MenuVal5D77C8) - (float)ScanSlot_0040AAE2(MenuByte5D77C1);
      continue;
    }
    s++;
    const uint8_t *t = font_tab(MenuByte5D77C1);
    if (t == NULL) continue;
    const uint8_t *gl = t + 0xe + ch * 8;
    if (rd16(gl) == 0) x = (float)rd16(t + 0xc) * sx + x;
    else {
      MenuVal5D77C4 = f2b(x);
      P115_IconDraw(x, y, sx, sy, (float)gl[4], (float)gl[5], (float)gl[6], (float)gl[7], (int32_t)rd16(gl + 2), rgb);
      x = (float)((int32_t)gl[6] + (int32_t)rd16(t + 0xa)) * sx + x;
    }
  }
  MenuVal5D77C4 = f2b(x);
  if (P56_F7E58 == 0) DrvSetMode0042655A(saved);
}

/* ---- 0051e65e / 0051f376: следы шин ---- */
static float skid_mat[16];
static void proj(p85_rv *v, const float *c, float w) {
  v->x = (c[0] * w * P43_ScaleA + P43_OffX) - SNAP;
  v->y = (c[1] * w * P43_ScaleA + P43_OffY) - SNAP;
}
static int32_t zidx(float z) {
  int32_t i = (int32_t)lrintf(z);
#ifndef RE_HOOK_BUILD
  if (i < 0 || i >= ZTAB_N) i = (i < 0) ? 0 : ZTAB_N - 1;
#endif
  return i;
}
static int in_r(float v) { return v <= SKID_R && -SKID_R <= v; }
static void rel(float *o, const uint8_t *r) { o[0] = rdf(r) - P44_CamX; o[1] = rdf(r + 4) - P44_CamY; o[2] = rdf(r + 8) - P44_CamZ; }
static void skid_col(p85_rv *v, float c) { v->r = c; v->g = c; v->b = c; }
static void skid_cols(p85_rv *v, int on, uint8_t lit) {
  if (!on) { v->r = v->g = v->b = 0.0f; return; }
  if (lit == 0) skid_col(v, 25.0f);
  else { v->r = 54.0f; v->g = 76.0f; v->b = 93.0f; }
}
static void skids(uint8_t *tab, const int32_t *cnt, const int32_t *start) {
  const uint8_t *sk = P74_Skid;
#ifndef RE_HOOK_BUILD
  if (sk == NULL) return;
#endif
  float c9 = (float)sk[9], c10 = (float)sk[10], c11 = (float)sk[0xb], c12 = (float)sk[0xc];
  if (P13_00575ec0 == 0) return;
  P12_Fn00426580(0);
  if (P84_Mirror == 0) P44_MatPtr = (float *)P44_ViewMatT;
  else {
    memset(skid_mat, 0, sizeof skid_mat);
    memcpy(skid_mat, P44_ViewMatT, sizeof(p44_m9_t));
    skid_mat[0] = -skid_mat[0]; skid_mat[3] = -skid_mat[3]; skid_mat[6] = -skid_mat[6];
    P44_MatPtr = skid_mat;
  }
  int32_t saved = DrvSetMode0042655A(0);
  if (P13_00575ebc == 0) state_set(1, 0, 0, 2, 0, 0);
  else { state_set(3, 1, 0, 1, 0, 4); tex_select(sk[8]); }
  blend_set(0, 6, 4, 0, 2);
  p85_rv *V = P116_SkidV;
  int32_t mode = -1; uint32_t lastc = 0xffffffffu;
  float a[3], b[3], c[3], d[3], w3 = 0.0f;
  for (int32_t t = 0; t < 4; t++) {
    if (cnt[t] == 0) continue;
    int first = 1;
    uint8_t *base = tab + t * 0x4800;
#ifndef RE_HOOK_BUILD
    if (start[t] < 0 || start[t] >= 0x100) continue;
#endif
    uint8_t *r = base + start[t] * 0x48;
    for (int32_t k = 0; k < cnt[t]; k++, r += 0x48) {
      if (r == base + 0x4800) r = base;
      int ok = 0;
      if (r[0] == 0 || first) {
        first = 1;
        rel(a, r + 8);
        if (!(in_r(a[0]) && in_r(a[2]))) continue;
        P44_Xform(a);
        if (!(NEAR_Z < a[2] && a[2] <= FAR_Z)) continue;
        rel(c, r + 0x28);
        if (!(in_r(c[0]) && in_r(c[2]))) continue;
        P44_Xform(c);
        if (!(NEAR_Z < c[2] && c[2] <= FAR_Z)) continue;
        rel(b, r + 0x18); P44_Xform(b);
        if (!(NEAR_Z < b[2] && b[2] <= FAR_Z)) continue;
        rel(d, r + 0x38); P44_Xform(d);
        if (!(NEAR_Z < d[2] && d[2] <= FAR_Z)) continue;
        V[0].oow = P12_00ba53a0[zidx(a[2])]; proj(&V[0], a, V[0].oow);
        V[1].oow = P12_00ba53a0[zidx(b[2])]; proj(&V[1], b, V[1].oow);
        V[2].oow = P12_00ba53a0[zidx(c[2])]; proj(&V[2], c, V[2].oow);
        ok = 1;
      } else {
        first = 1;
        memcpy(&V[0], &V[2], 0xf * 4);
        memcpy(&V[1], &V[3], 0xf * 4);
        rel(c, r + 0x28);
        if (!(in_r(c[0]) && in_r(c[2]))) continue;
        P44_Xform(c);
        if (!(NEAR_Z < c[2])) continue;
        rel(d, r + 0x38); P44_Xform(d);
        if (!(NEAR_Z < d[2])) continue;
        V[2].oow = P12_00ba53a0[zidx(c[2])]; proj(&V[2], c, V[2].oow);
        ok = 1;
      }
      if (!ok) continue;
      w3 = P12_00ba53a0[zidx(d[2])];
      { float f = w3 * P43_ScaleA; V[3].x = (d[0] * f + P43_OffX) - SNAP; V[3].y = (d[1] * f + P43_OffY) - SNAP; }
      first = 0;
      int16_t typ = rd16(r + 2); uint8_t lit = r[4];
      int32_t want = (typ == 0) ? 0 : (typ == 1) ? 1 : 2;
      if (mode != want || lit != lastc) {
        mode = want;
        skid_cols(&V[2], want != 2, lit); skid_cols(&V[3], want != 2, lit);
        skid_cols(&V[0], want != 0, lit); skid_cols(&V[1], want != 0, lit);
        lastc = lit;
      }
      V[3].tmu[0] = c9 * w3;          V[3].tmu[1] = c10 * w3;
      V[2].tmu[0] = c11 * V[2].oow;   V[2].tmu[1] = c10 * V[2].oow;
      V[0].tmu[0] = c11 * V[0].oow;   V[0].tmu[1] = c12 * V[0].oow;
      V[1].tmu[0] = c9 * V[1].oow;    V[1].tmu[1] = c12 * V[1].oow;
      V[3].oow = w3;
      raster(&V[0], &V[1], &V[2]);
      raster(&V[1], &V[2], &V[3]);
    }
  }
  DrvSetMode0042655A(saved);
}
void P116_SkidsA(void) { skids(&P116_SkidRecA[0], P74_SkidD, P74_SkidB); }
void P116_SkidsB(void) { skids(&P116_SkidRecB[0], P74_SkidC, P74_SkidA); }

/* ---- 004cc801: отражения фонарей (записи 0x48 в 00d132c0; +0x44 — адрес следующей в Game.exe) ---- */
#define REFL_ADDR 0x00d132c0u
static uint8_t *refl_rec(uint32_t a) {
  if (a == 0) return NULL;
#ifndef RE_HOOK_BUILD
  if (a < REFL_ADDR || a >= REFL_ADDR + 100u * 0x48u) return NULL;
#endif
  return &A_00D132C0[a - REFL_ADDR];
}
static const int32_t k_flare[P111_FLARE_N][7] = P111_FLARE_INIT;   /* .data 00553870 */
void P116_Reflections(void) {
  const uint8_t *ic = G00D14EF0;
  if (ic == NULL) return;
  P44_MatPtr = (float *)P44_ViewMatT;
  uint32_t head = 0;
  int32_t n = G8_00D17B0C;
#ifndef RE_HOOK_BUILD
  if (n > 100) n = 100;
#endif
  while (n-- > 0) {
    uint8_t *p = &A_00D132C0[n * 0x48];
    float v[3];
    v[0] = rdf(p); v[2] = rdf(p + 8);
    int32_t h = P100_RoadHeightF((const float *)p);
    float gy = (float)(-0x1c - h);
    P11_00ba52d0 = (int32_t)lrintf(-(rdf(p + 4) - gy));
    int32_t hgt = P11_00ba52d0;
    v[0] -= P44_CamX; v[1] = gy - P44_CamY; v[2] -= P44_CamZ;
    P44_Xform(v);
    if (!(NEAR_Z <= v[2] && v[2] < P11_01270c24)) continue;
    float w = P12_00ba53a0[zidx(v[2])], f = P43_ScaleA * w;
    P11_00ba52d0 = (int32_t)lrintf((float)((hgt >> 3) + 0x50) * f);
    int32_t t = P11_00ba52d0, half = t >> 1;
    float k = 0.7f - v[2] / 8000.0f;
    if (k < 0.3f) k = 0.3f;
    P11_00ba52d0 = (int32_t)lrintf(((v[0] * f + P43_OffX) - (float)(t >> 2)) - SNAP); wr32(p + 0x14, P11_00ba52d0);
    P11_00ba52d0 = (int32_t)lrintf((v[1] * f + P43_OffY) - SNAP); wr32(p + 0x18, P11_00ba52d0);
    wrf(p + 0x3c, w);
    wr32(p + 0x1c, rd32(p + 0x14) + half);
    wr32(p + 0x20, rd32(p + 0x18));
    int32_t sx = rd32(p + 0x14), sy = rd32(p + 0x18);
    if (!(0 < sx && sx < P19_ScrW && 0 < sy && sy < P19_ScrH)) continue;
    P11_00ba52d0 = (int32_t)lrintf((rdf(p) - P44_CamX) * k); int32_t qa = P11_00ba52d0;
    P11_00ba52d0 = (int32_t)lrintf((rdf(p + 8) - P44_CamZ) * k); int32_t qb = P11_00ba52d0;
    float q[3] = { (float)qa + P44_CamX, v[1], (float)qb + P44_CamZ };
    int32_t h2 = P100_RoadHeightF(q);
    q[0] -= P44_CamX; q[1] = ((float)-h2 - 28.0f) - P44_CamY; q[2] -= P44_CamZ;
    P44_Xform(q);
    if (!(NEAR_Z <= q[2] && q[2] < P11_01270c24)) continue;
    float w2 = P12_00ba53a0[zidx(q[2])], f2 = P43_ScaleA * w2;
    P11_00ba52d0 = (int32_t)lrintf((float)((hgt >> 3) + 0x14) * f2);
    int32_t a4 = P11_00ba52d0 >> 2, a8 = P11_00ba52d0 >> 3;
    P11_00ba52d0 = (int32_t)lrintf(((q[0] * f2 + P43_OffX) - (float)a8) - SNAP); wr32(p + 0x2c, P11_00ba52d0);
    P11_00ba52d0 = (int32_t)lrintf((q[1] * f2 + P43_OffY) - SNAP); wr32(p + 0x30, P11_00ba52d0);
    wr32(p + 0x24, rd32(p + 0x2c) + a4);
    wr32(p + 0x34, rd32(p + 0x2c) + a8);
    wr32(p + 0x38, rd32(p + 0x30));
    wr32(p + 0x28, rd32(p + 0x38));
    wrf(p + 0x40, w2);
    uint32_t pa = REFL_ADDR + (uint32_t)n * 0x48u;
    if (head == 0) { head = pa; wr32(p + 0x44, 0); }
    else {
      uint8_t *it = refl_rec(head);
      while (it != NULL && rd32(it + 0x44) != 0 && rdf(it + 0x40) <= w2) {
        uint8_t *nx = refl_rec((uint32_t)rd32(it + 0x44));
        if (nx == NULL) break;
        it = nx;
      }
      if (it == NULL) continue;
      wr32(p + 0x44, rd32(it + 0x44));
      wr32(it + 0x44, (int32_t)pa);
    }
  }
  if (head == 0) return;
  P12_Fn00426580(0);
  state_set(3, 1, 0, 1, 0, 4);
  tex_select(ic[8]);
  int32_t saved = DrvSetMode0042655A(0);
  for (uint8_t *r = refl_rec(head); r != NULL; r = refl_rec((uint32_t)rd32(r + 0x44))) {
    if (r[0x10] == 5 || r[0x10] == 9) blend_set(4, 4, 0, 0, 3);
    else blend_set(2, 4, 0, 0, 5);
    int32_t cr = 0, cg = 0, cb = 0, sc = r[0x11];
    if (r[0x10] < P111_FLARE_N) { cr = k_flare[r[0x10]][0]; cg = k_flare[r[0x10]][1]; cb = k_flare[r[0x10]][2]; }
    float R = (float)(cr * sc >> 9), G = (float)(cg * sc >> 9), B = (float)(cb * sc >> 9);
    float o0 = rdf(r + 0x3c), o1 = rdf(r + 0x40);
    p85_rv vA, vB, vC, vD, vE;
    memset(&vA, 0, sizeof vA); memset(&vB, 0, sizeof vB); memset(&vC, 0, sizeof vC); memset(&vD, 0, sizeof vD); memset(&vE, 0, sizeof vE);
    vA.x = (float)rd32(r + 0x14); vA.y = (float)rd32(r + 0x18);
    vB.x = (float)rd32(r + 0x1c); vB.y = (float)rd32(r + 0x20);
    vC.x = (float)rd32(r + 0x24); vC.y = (float)rd32(r + 0x28);
    vD.x = (float)rd32(r + 0x2c); vD.y = (float)rd32(r + 0x30);
    vE.x = (float)rd32(r + 0x34); vE.y = (float)rd32(r + 0x38);
    p85_rv *all[5] = { &vA, &vB, &vC, &vD, &vE };
    for (int32_t i = 0; i < 5; i++) { all[i]->r = R; all[i]->g = G; all[i]->b = B; }
    vA.oow = vB.oow = o0; vC.oow = vD.oow = vE.oow = o1;
    vA.tmu[0] = (float)ic[9] * o0;    vA.tmu[1] = (float)ic[10] * o0;
    vB.tmu[0] = (float)ic[0xb] * o0;  vB.tmu[1] = (float)ic[10] * o0;
    vC.tmu[0] = (float)ic[0xb] * o1;  vC.tmu[1] = (float)ic[0xc] * o1;
    vD.tmu[0] = (float)ic[9] * o1;    vD.tmu[1] = (float)ic[0xc] * o1;
    vE.tmu[0] = (vC.tmu[0] + vD.tmu[0]) * P51_Half; vE.tmu[1] = (float)ic[0xc] * o1;
    raster(&vE, &vB, &vC);
    raster(&vA, &vE, &vD);
    raster(&vA, &vE, &vB);
  }
  DrvSetMode0042655A(saved);
}
