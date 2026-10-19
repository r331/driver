/* v1.54 (см. ported109.h). */
#include "ported109.h"
#include "ported108.h"
#include "ported107.h"
#include "ported106.h"
#include "ported105.h"
#include "ported11.h"
#include "ported12.h"
#include "ported14.h"
#include "ported15.h"
#include "ported16.h"
#include "ported17.h"
#include "ported18.h"
#include "ported19.h"
#include "ported20.h"
#include "ported21.h"
#include "ported22.h"
#include "ported23.h"
#include "ported24.h"
#include "ported25.h"
#include "ported26.h"
#include "ported27.h"
#include "ported28.h"
#include "ported29.h"
#include "ported30.h"
#include "ported31.h"
#include "ported33.h"
#include "ported32.h"
#include "ported34.h"
#include "ported35.h"
#include "ported36.h"
#include "ported37.h"
#include "ported38.h"
#include "ported39.h"
#include "ported40.h"
#include "ported41.h"
#include "ported42.h"
#include "ported43.h"
#include "ported44.h"
#include "ported45.h"
#include "ported46.h"
#include "ported47.h"
#include "ported48.h"
#include "ported49.h"
#include "ported50.h"
#include "ported51.h"
#include "ported52.h"
#include "ported53.h"
#include "ported54.h"
#include "ported55.h"
#include "ported56.h"
#include "ported57.h"
#include "ported58.h"
#include "ported59.h"
#include "ported60.h"
#include "ported61.h"
#include "ported62.h"
#include "ported63.h"
#include "ported64.h"
#include "ported65.h"
#include "ported66.h"
#include "ported67.h"
#include "ported68.h"
#include "ported69.h"
#include "ported70.h"
#include "ported71.h"
#include "ported72.h"
#include "ported73.h"
#include "ported74.h"
#include "ported75.h"
#include "ported76.h"
#include "ported77.h"
#include "ported78.h"
#include "ported79.h"
#include "ported80.h"
#include "ported81.h"
#include "ported82.h"
#include "ported83.h"
#include "ported84.h"
#include "ported85.h"
#include "ported86.h"
#include "ported87.h"
#include "ported88.h"
#include "ported89.h"
#include "ported90.h"
#include "ported91.h"
#include "ported92.h"
#include "ported93.h"
#include "ported94.h"
#include "ported95.h"
#include "ported96.h"
#include "ported97.h"
#include "ported98.h"
#include "ported99.h"
#include "ported100.h"
#include "ported101.h"
#include "ported102.h"
#include "ported13.h"
#include "director.h"
#include "directorstorage.h"
#include "dirnodes.h"
#include "menustate.h"
#include "noop.h"
#include "uihandlers.h"
#include "uihandlers2.h"
#include "uihandlers3.h"
#include "uihandlers4.h"
#include "globalsets.h"
#include "smallfuncs.h"
#include "smallfuncs2.h"
#include "menuselect.h"
#include "widgets.h"
#include "ported4.h"
#include "ported5.h"
#include "ported6.h"
#include "ported7.h"
#include "ported8.h"
#include "ported9.h"
#include "ported10.h"
#include "unported.h"
#include "nodetab.h"
#include "cartab.h"
#include "menutab.h"
#include "p100_data.h"
#include "p103_data.h"
#include <math.h>
#include <string.h>
#include "ported103.h"
#include "p104_data.h"
#include <math.h>
#include <string.h>
#include "ported104.h"
#include "ported105.h"
#include "../platform/plat.h"
#include "ported4.h"
#include "ported6.h"
#include "ported7.h"
#include "ported8.h"
#include "unported.h"
#include "noop.h"
#include "globalsets.h"
#include "menustate.h"
#include "smallfuncs.h"
#include "smallfuncs2.h"
#include "uihandlers3.h"
#include "uihandlers4.h"
#include "widgets.h"
#include "cartab.h"
#include "director.h"
#include "dirnodes.h"

#include "ported107.h"


#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P109_C8089C")
#undef P109_C8089C
#pragma push_macro("P109_C8089C") /*gvi*/
#undef P109_C8089C /*gvi*/
int32_t P109_C8089C;
#pragma pop_macro("P109_C8089C") /*gvi*/
#pragma pop_macro("P109_C8089C")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P109_C54B00")
#undef P109_C54B00
#pragma push_macro("P109_C54B00") /*gvi*/
#undef P109_C54B00 /*gvi*/
int32_t P109_C54B00;
#pragma pop_macro("P109_C54B00") /*gvi*/
#pragma pop_macro("P109_C54B00")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P109_C81268")
#undef P109_C81268
#pragma push_macro("P109_C81268") /*gvi*/
#undef P109_C81268 /*gvi*/
int32_t P109_C81268;
#pragma pop_macro("P109_C81268") /*gvi*/
#pragma pop_macro("P109_C81268")
#endif

#include "memrw.h"
static uint16_t rd16(const void *p) { uint16_t v; memcpy(&v, p, 2); return v; }
static void wr16(void *p, uint16_t v) { memcpy(p, &v, 2); }
static void wrf(void *p, float v) { memcpy(p, &v, 4); }
static const float OOW_LO = 0.015625f;   /* 0x3c800000 */
#ifdef RE_HOOK_BUILD
#  define P109_STD __attribute__((stdcall))
#else
#  define P109_STD
#endif
static void *glide_proc(const char *name) {
  for (int i = 0; i < P33_GlideCount(); i++)
    if (strcmp(P33_GlideName(i), name) == 0) return P33_GlideProc(i);
  return NULL;
}
static void poly_list(int32_t n, const void *v) {
  void (P109_STD *f)(int32_t, const void *) = (void (P109_STD *)(int32_t, const void *))glide_proc("_grDrawPolygonVertexList@8");
  if (f != NULL) f(n, v);
}
static void alpha_combine(int32_t a, int32_t b, int32_t c, int32_t d, int32_t e) {
  void (P109_STD *f)(int32_t, int32_t, int32_t, int32_t, int32_t) = (void (P109_STD *)(int32_t, int32_t, int32_t, int32_t, int32_t))glide_proc("_grAlphaCombine@20");
  if (f) f(a, b, c, d, e);
}
static void alpha_test(int32_t a) {
  void (P109_STD *f)(int32_t) = (void (P109_STD *)(int32_t))glide_proc("_grAlphaTestFunction@4");
  if (f) f(a);
}
static void blend0(void) {
  if (P85_BlendCur != 0) { if (P85_BlendFn) P85_BlendFn(4, 0, 4, 0); P85_BlendCur = 0; P69_BlendOn = 0; }
}
static void tex_page(int32_t tex) {
  if (tex != P86_CurTex) {
    P86_CurTex = tex;
#ifndef RE_HOOK_BUILD
    if (tex < 0 || tex >= 0x100) return;
#endif
    if (P86_TexSrc) P86_TexSrc(0, (uint32_t)rd32(&g_01145a60[tex * 0x10 + 8]), 3, (uint32_t)rd32(&g_01145a60[tex * 0x10 + 0xc]));
  }
}
/* 32-битное умножение с переполнением, как в Game.exe */
static int32_t mul32(int32_t a, int32_t b) { return (int32_t)((uint32_t)a * (uint32_t)b); }

/* ---- 0052498e: поставить сэмпл на голос (20 слотов по 0x34, 00bdc2a0): тот же сэмпл — перезапуск (драйвер +0x44), иначе
   освободить голос и загрузить (драйвер +0x28); громкость по умолчанию из записи сэмпла 00bdc880 (+4), позиция a,b,c в +4/+0x10 ---- */
typedef void (*p109_f1)(int32_t);
typedef void (*p109_f2)(int32_t, int32_t);
void P109_SndPlay(int32_t voice, int32_t sample, float a, float b, float c) {
  if (G6_00B91CF4 == 0 || voice == -1 || G00575F40 == 0) return;
#ifndef RE_HOOK_BUILD
  if (voice < 0 || voice >= 0x14 || sample < 0 || sample >= 0x400) return;
#endif
  uint8_t *v = &S_00BDC2A0[voice * 0x34];
  if ((uint32_t)rd16(v + 2) == (uint32_t)sample) {
    v[0] = 0;
    if (P97_DrvG) ((p109_f1)P97_DrvG)(voice);
  } else {
    P48_FreeVoice(voice);
    if (P97_DrvC) ((p109_f2)P97_DrvC)(sample, voice);
  }
  const uint8_t *sm = (const uint8_t *)&P68_Samps[sample];
  int32_t vol = (int16_t)rd16(sm + 4);
  if (vol < -10000) vol = -10000;
  if (0 < vol) vol = 0;
  memset(v + 4, 0, 4);
  v[0x32] = sm[6];
  v[0x33] = sm[7];
  wr16(v + 0x2c, (uint16_t)vol);
  wr16(v + 0x30, (uint16_t)vol);
  int32_t idx = (int32_t)(float)(vol + 10000);     /* __ftol((float)(vol + 10000)) */
  wr16(v + 0x2e, (uint16_t)(P48_VolTab[idx] & 0xffff));
  wr32(v + 0x24, rd32(sm));
  wr32(v + 0x28, rd32(sm));
  wrf(v + 0x10, a); wrf(v + 4, a);
  wrf(v + 0x14, b); wrf(v + 8, b);
  wrf(v + 0x18, c); wrf(v + 0xc, c);
  wr32(v + 0x20, (v[0x32] & 1) != 0 ? 1 : 0);
  if (P97_DrvK) ((p109_f2)P97_DrvK)(voice, (v[0x32] & 2) == 0 ? 0 : 2);
  wr16(v + 2, (uint16_t)sample);
  v[0] = 0x1e;
}

/* ---- 004d7f91 / 004d81da: прямоугольник с цветом в каждой вершине (A (x,y), B (x+w,y+h), C (x,y+h), D (x+w,y)),
   два треугольника ABC, ABD; 004d81da — цвета 0xRRGGBB и координаты через P51_ScalePair ---- */
static void grad_quad(float x, float y, float w, float h, const float col[4][3], int scale) {
  if (P85_StateDirty != 0) { if (P85_StateFn) P85_StateFn(1, 0, 0, 2, 0); P85_StateDirty = 0; }
  blend0();
  p85_rv v[4];
  memset(v, 0, sizeof v);
  const float px[4] = { x, x + w, x, x + w }, py[4] = { y, y + h, y + h, y };
  for (int i = 0; i < 4; i++) {
    v[i].r = col[i][0]; v[i].g = col[i][1]; v[i].b = col[i][2];
    v[i].x = px[i]; v[i].y = py[i];
    if (scale) P51_ScalePair(&v[i].x, &v[i].y);
    v[i].oow = (P55_BDFA18 == 0) ? OOW_LO : 1.0f;
  }
  if (P85_RasterB) P85_RasterB(&v[0], &v[1], &v[2]);
  if (P85_RasterB) P85_RasterB(&v[0], &v[1], &v[3]);
  P85_StateDirty = (int32_t)0xffffffff;
}
void P109_GradRect(float x, float y, float w, float h, int32_t c0, int32_t c1, int32_t c2, int32_t c3, int32_t c4, int32_t c5,
                   int32_t c6, int32_t c7, int32_t c8, int32_t c9, int32_t c10, int32_t c11) {
  const float col[4][3] = { { (float)(uint8_t)c0, (float)(uint8_t)c1, (float)(uint8_t)c2 }, { (float)(uint8_t)c3, (float)(uint8_t)c4, (float)(uint8_t)c5 },
                            { (float)(uint8_t)c6, (float)(uint8_t)c7, (float)(uint8_t)c8 }, { (float)(uint8_t)c9, (float)(uint8_t)c10, (float)(uint8_t)c11 } };
  grad_quad(x, y, w, h, col, 0);
}
#define P109_RGB(c) { (float)(((int32_t)(c) >> 16) & 0xff), (float)(((int32_t)(c) >> 8) & 0xff), (float)((c) & 0xff) }
void P109_GradRectS(float x, float y, float w, float h, uint32_t cA, uint32_t cD, uint32_t cB, uint32_t cC) {
  const float col[4][3] = { P109_RGB(cA), P109_RGB(cB), P109_RGB(cC), P109_RGB(cD) };
  grad_quad(x, y, w, h, col, 1);
}

/* ---- 0040dce0: плитка w×h текстуры idx в (x,y) цветом rgb (uv с поправкой 0.5), grDrawPolygonVertexList ---- */
void P109_TileDraw(int32_t x, int32_t y, int32_t w, int32_t h, int32_t idx, void *color) {
  const uint8_t *rgb = (const uint8_t *)color;
  float k = (P55_BDFA18 == 0) ? OOW_LO : 1.0f, c = P80_Half;
  float v[4][15];
  memset(v, 0, sizeof v);
  const float px[4] = { (float)x, (float)(x + w), (float)(x + w), (float)x }, py[4] = { (float)y, (float)y, (float)(y + h), (float)(y + h) };
  const float su[4] = { c * k, ((float)w - c) * k, ((float)w - c) * k, c * k }, tv[4] = { c * k, c * k, ((float)h - c) * k, ((float)h - c) * k };
  for (int i = 0; i < 4; i++) {
    v[i][0] = px[i]; v[i][1] = py[i];
    v[i][3] = (float)rgb[0]; v[i][4] = (float)rgb[1]; v[i][5] = (float)rgb[2];
    v[i][7] = 255.0f; v[i][8] = k; v[i][9] = su[i]; v[i][10] = tv[i];
  }
  tex_page(idx);
  if (P85_StateDirty != 4) { if (P85_StateFn) P85_StateFn(3, 1, 0, 1, 0); P85_StateDirty = 4; }
  blend0();
  poly_list(4, v);
}

/* ---- 0040b6fd: значок (страница page, u,v, размер tw×th текселей) в (x,y) с масштабом sx,sy; без 3D (005f7e58) — спрайт в буфер
   (005d77c0 & 8 — с прозрачностью 00407d07, иначе по ключу 00407cb8), аргументы — __ftol (усечение) ---- */
void P109_IconDraw(float x, float y, float sx, float sy, float u, float vv, float tw, float th, int32_t page, const uint8_t *rgb) {
  if (P56_F7E58 != 0) {
    if ((G005D77C0 & 8) == 0) P65_SpriteKeyed((int32_t)x, (int32_t)y, page, (int32_t)u, (int32_t)vv, (int32_t)tw, (int32_t)th);
    else P65_SpriteBlend((int32_t)x, (int32_t)y, page, (int32_t)u, (int32_t)vv, (int32_t)tw, (int32_t)th);
    return;
  }
  float k = (P55_BDFA18 == 0) ? OOW_LO : 1.0f, c;
  uint32_t cb = P56_AA30; memcpy(&c, &cb, 4);          /* .data 0054aa30 = 0.5 */
  u = u + c; vv = vv + c; tw = tw - c; th = th - c;
  float v[4][15];
  memset(v, 0, sizeof v);
  const float px[4] = { x, tw * sx + x, tw * sx + x, x }, py[4] = { y, y, th * sy + y, th * sy + y };
  const float su[4] = { u * k, (u + tw) * k, (u + tw) * k, u * k }, tv[4] = { vv * k, vv * k, (vv + th) * k, (vv + th) * k };
  for (int i = 0; i < 4; i++) {
    v[i][0] = px[i]; v[i][1] = py[i];
    v[i][3] = (float)rgb[0]; v[i][4] = (float)rgb[1]; v[i][5] = (float)rgb[2];
    v[i][7] = 255.0f; v[i][8] = k; v[i][9] = su[i]; v[i][10] = tv[i];
  }
  tex_page(page);
  if (P85_StateDirty != 4) { if (P85_StateFn) P85_StateFn(3, 1, 0, 1, 0); P85_StateDirty = 4; }
  blend0();
  poly_list(4, v);
}

/* ---- 00522a50: модели капель (6 записей 00bde680 по 0x1c, +0x18 — адрес объекта): mode 0 — модели без флага 8, 1 — с флагом 8,
   другое — все; матрица — EulerTab[-курс] с поворотами X/Z по фазе; флаг модели 0x1000 — alpha-combine/alpha-test на время ---- */
void P109_DropsDraw(int32_t mode32) {
  int8_t mode = (int8_t)mode32;
  if (mode != 0) P85_BlendForce = 2;
  for (int32_t k = 0; k < 6; k++) {
    const uint8_t *d = &P101_Drops[k * 0x1c];
    uint32_t oa = (uint32_t)rd32(d + 0x18);
    if (oa == 0) continue;
    uint8_t *o = (uint8_t *)re_ptr(oa);
#ifndef RE_HOOK_BUILD
    if (o == NULL) continue;
    int32_t mi0 = rd32(o + 4);
    if (mi0 < 0 || mi0 >= (int32_t)(sizeof(P79_ModelTab) / sizeof(P79_ModelTab[0])) || P79_ModelTab[mi0] == 0) continue;
#endif
    uint32_t mref = P79_ModelTab[rd32(o + 4)];
    uint8_t *m = (uint8_t *)P79_PTR(mref);
    if ((rd16(m + 2) & 8) == 0) { if (mode == 1) continue; }
    else if (mode == 0) continue;
    if ((rd16(m + 2) & 0x1000) != 0 && P62_I252B78 != 1) { alpha_combine(3, 8, 0, 1, 1); alpha_test(4); P62_I252B78 = 1; }
    wrf(o + 8, (float)rd32(d + 0xc));
    if (P76_InBox((const float *)(o + 8), (const uint8_t *)P82_LightGrid, P82_CellCX, P82_CellCY) != 0) {
      int32_t vis = P83_BoxVis((const float *)(o + 8), rdf(m + 0xc));
      if (vis != 0
#ifndef RE_HOOK_BUILD
          && P56_EulerTab != NULL
#endif
         ) {
        float mat[16];
        memcpy(mat, P56_EulerTab + ((uint32_t)(-(int32_t)P59_AngB) & 0xfffu) * 0x40, 0x40);
        int32_t d0 = rd32(d), d1 = rd32(d + 4), d2 = rd32(d + 8);
        P44_RotX(mat, mul32(mul32(d1, d0), d2) & 0xfff);
        P44_RotZ(mat, mul32(d1, d0) & 0xfff);
        float p[3] = { rdf(o + 8) - P44_CamX, rdf(o + 0xc) - P44_CamY, rdf(o + 0x10) - P44_CamZ };
        P44_MatPtr = (float *)P44_ViewMatT;
        P44_Xform(p);
        uint16_t sv = rd16(m + 2);
        wr16(m + 2, sv & 0xbfff);
        P84_DrawModel(mref, mat, p, vis == 1 ? 0 : (vis == 2 ? 1 : 2));
        wr16(m + 2, sv);
      }
    }
    if ((rd16(m + 2) & 0x1000) != 0 && P62_I252B78 != 0) { alpha_combine(3, 8, 0, 2, 1); alpha_test(7); P62_I252B78 = 0; }
    wr32(o + 8, (int32_t)0xcb989680);                  /* -20000000.0f — убрать с карты */
  }
  P85_BlendForce = 0;
}

/* ---- 004219e8: таблица пикселей + эмулируемые 8-битные текстуры всех 32 слотов (парами); метка __fastcall ложная — ecx уходит
   в 00421a80, которая его не читает ---- */
int32_t P109_EmulInit(void) {
  P98_PixTabInit();
  for (int32_t i = 0; i < 0x20; i += 2)
    if (P108_EmulTex8(i) == 0) return 0;
  NoopFn0041e083();
  P31_DDVal5 = 1;
  return 1;
}

/* ---- 00421719: 256 строк по 256 байт src в 8-битную эмулируемую текстуру слота (чётный — создать, нечётный — должен быть 8 бит) ---- */
int32_t P109_SlotUpload8(const uint8_t *src, int32_t slot) {
#ifndef RE_HOOK_BUILD
  if (slot < 0 || slot >= 32 || src == NULL) return 0;
#endif
  if ((slot & 1) == 0) { if (P108_EmulTex8(slot) == 0) return 0; }
  else if (P32_Slots[slot].bpp != 8) { NoopFn0042243f(); return 0; }   /* «Can't load 8bit texture into 16bit» */
  uint32_t d[31];
  memset(d, 0, sizeof d);
  d[0] = 0x7c;
  void *s = P32_Slots[slot].surf;
  if (plat_dd_lock(s, d) != 0) { NoopFn0042243f(); return 0; }       /* «Lock texture8() failed» */
  uint8_t *dst = (uint8_t *)re_ptr(d[9]);
#ifndef RE_HOOK_BUILD
  if (dst == NULL) { plat_dd_unlock(s); return 1; }
#endif
  for (int32_t y = 0; y < 0x100; y++) {
    P13_Fn00422AC0(dst, src, 0x100);
    dst += (int32_t)d[4];
    src += 0x100;
  }
  plat_dd_unlock(s);
#ifndef RE_HOOK_BUILD
  P86_GameTag8(s, src - 0x10000);   /* v2.18: HD-пак — страница уровня на PAL8-поверхности слота */
#endif
  return 1;
}

/* ---- 00421861: 256×256 индексов 16 бит src → 16-битная эмулируемая текстура слота через таблицу пикселей 00601bc0 ---- */
int32_t P109_SlotUpload16(const uint16_t *src, int32_t slot) {
#ifndef RE_HOOK_BUILD
  if (slot < 0 || slot >= 32 || src == NULL) return 0;
#endif
  if (P32_Slots[slot].has_list == 0 && P108_EmulTex16(slot) == 0) return 0;
  uint32_t d[31];
  memset(d, 0, sizeof d);
  d[0] = 0x7c;
  void *s = P32_Slots[slot].surf;
  if (plat_dd_lock(s, d) != 0) { NoopFn0042243f(); return 0; }       /* «Lock texture16() failed» */
  uint16_t *row = (uint16_t *)re_ptr(d[9]);
#ifndef RE_HOOK_BUILD
  if (row == NULL) { plat_dd_unlock(s); return 1; }
#endif
  for (int32_t y = 0; y < 0x100; y++) {
    for (int32_t x = 0; x < 0x100; x++) row[x] = P98_PixTab[*src++];
    row += (d[4] >> 1);
  }
  plat_dd_unlock(s);
#ifndef RE_HOOK_BUILD
  P86_GameAttach16(s, src - 0x10000);   /* v2.18: HD-пак — 16-битная страница по содержимому */
#endif
  return 1;
}

/* ---- 00502cee: маркеры целей скрипта (фигуры радара 00573f08/18/28/38 над машиной 0x41 и объектами P58_Objs) ---- */
void P109_ScriptMarkers(void) {
  if (G6_00B87EA0 != 0) return;
  if (G6_00B87EB0 != 0) {
    int32_t pos[4] = { P99_Cars[0x41].pos[0], 0, P99_Cars[0x41].pos[2], 0 }, ofs[3] = { 0, 0, 0 }, scr[3] = { -200, 0, 0 };
    P108_RadarShape(0x00573f08u, pos, ofs, scr);
  }
  if (P97_ScrObjOn == 0) return;
  for (int32_t i = 0; i < 10; i++) {
    const uint8_t *o = P58_Objs[i];
    uint32_t fl = (uint32_t)rd32(o + 0x10);
    if ((fl & 1) == 0 || (fl & 0x20) != 0) continue;
    uint32_t shape = (fl & 4) ? 0x00573f18u : (fl & 2) ? 0x00573f28u : (fl & 0x200) ? 0x00573f38u : 0x00573f08u;
    int32_t pos[4], ofs[3], scr[3] = { 0, 0, 0 };
    memcpy(pos, o + 0x14, 16);
    memcpy(ofs, o + 0x24, 12);
    P108_RadarShape(shape, pos, ofs, scr);
  }
}

/* ---- 00504866: стрелки радара на машины трафика типа 4 впереди игрока (в системе курса игрока) ---- */
void P109_RadarArrows(void) {
  int32_t h = P99_Cars[0].heading;
  int32_t s1 = P59_Sin[(h + 0x400) & 0xfff], s2 = P59_Sin[h & 0xfff];
  const p99_car_t *me = &P99_Cars[0];
  for (int32_t i = 0; i < 0x40; i++) {
    const uint8_t *rec = &TrafficRecs[i * 0x54];
    if (rec[1] == 0 || rec[5] == 0) continue;
    const p99_car_t *c = &P99_Cars[i + 1];
    int32_t dx = c->pos2[0] - me->pos2[0], dz = c->pos2[2] - me->pos2[2];
    int32_t a = mul32((int32_t)((uint32_t)mul32(dx, s1) - (uint32_t)mul32(dz, s2) + 0x800u) >> 12, 3);
    a = a / 4;
    int32_t b = -((int32_t)((uint32_t)mul32(dx, s2) + 0x800u + (uint32_t)mul32(dz, s1)) >> 12);
    int32_t aa = a < 0 ? -a : a;
    if (aa < b && rec[1] == 4) P108_RadarArrow((a * 0x10a) / b, 0x3fff0 / (b / 8 + 600));
  }
}

/* ---- 005191c5: такт ввода по режиму пульта 00c4d70c (3 — запись/воспроизведение, 1 — запись игрока или машины 0x41, 2 — чтение) ---- */
void P109_InputTick(void) {
  if (P103_C54D04 != 0) P12_Fn005188EC();
  if (P103_C54FC4 != 0) P101_ReplayBegin(P109_C81268);
  int32_t ay = P21_AxisValue, jx = P36_JoyX;
  P103_C54D04 = 0;
  P103_C54FC4 = 0;
  if (P36_PadMode == 3 && (G6_00B87EA0 == 0 || P88_Mode575 != 3)) {
    if (G6_00B87EA0 == 0 || P88_Mode575 != 2) {
      int32_t k = (P16_IdleMode == 0x7fff) ? 0x20 : P100_RecRead(1);
      P107_CarInput(0x41, (uint32_t)k);
      MenuAddItem004DC8B0((uint8_t *)&P99_Cars[0x41], 1);
      if (G6_00B87EA0 == 0 || P88_Mode575 != 0) {
        if (P109_C54B00 == 0) P100_RecInput(0);
        else P100_RecKeys = P100_RecRead(0);
        P107_CarInput(0, (uint32_t)P100_RecKeys);
        MenuAddItem004DC8B0((uint8_t *)&P99_Cars[0], 1);
      }
    } else {
      P108_ReplayStep();
      P36_JoyX = jx;
      P21_AxisValue = ay; P9_00b31e20 = ay;
      P100_RecInput(0);
      P107_CarInput(0, (uint32_t)P100_RecKeys);
      MenuAddItem004DC8B0((uint8_t *)&P99_Cars[0], 1);
    }
  } else if (P36_PadMode == 1) {
    if (G6_00B87EAC == 0) {
      P100_RecInput(0);
      P107_CarInput(0, (uint32_t)P100_RecKeys);
      MenuAddItem004DC8B0((uint8_t *)&P99_Cars[0], 1);
    } else {
      P100_RecInput(1);
      P107_CarInput(0x41, (uint32_t)P100_RecKeys);
      MenuAddItem004DC8B0((uint8_t *)&P99_Cars[0x41], 1);
    }
  } else if (P36_PadMode == 2) {
    int32_t k = P100_RecRead(0);
    P107_CarInput(0, (uint32_t)k);
    MenuAddItem004DC8B0((uint8_t *)&P99_Cars[0], 1);
  }
}

/* ---- 00505b54: машины трафика на радаре (в 45000 от игрока): треугольник по курсу 00505e2b + квадрат 0xff ---- */
void P109_RadarTraffic(void) {
  if (P100_RadarIcon == NULL || P109_C8089C == 0) return;
  float f1 = 0.003125f * (float)P19_ScrW * P19_Scale;     /* .rdata 00546a30 */
  float f2 = f1 * P80_Half;
  if (!(P59_One <= f1)) return;
  uint32_t ia = (uint32_t)(-(int32_t)P99_Cars[0].ang[1]) & 0xfffu;
  float sn = P43_Sin[ia], cs = P43_Sin[0x400 + ia];
  if (G00BDFA54 != 0) { sn = P43_Sin[0]; cs = P43_Sin[0x400]; }
  for (int32_t i = 0; i < 0x40; i++) {
    const uint8_t *rec = &TrafficRecs[i * 0x54];
    if (rec[1] == 0 || rec[5] == 0 || rec[1] == 1) continue;
    const uint8_t *car;
#ifndef RE_HOOK_BUILD
    if (P59_CarsTab == NULL) car = (const uint8_t *)&P99_Cars[rec[0] + 1 < P99_CARS_N ? rec[0] + 1 : P99_CARS_N - 1]; else
#endif
    car = P59_CarsTab + (uint32_t)rec[0] * 0x148;
    int32_t cx = rd32(car + 200), cz = rd32(car + 0xd0);
    int32_t dx = (cx + 0x2ee) - (P99_Cars[0].pos[0] + 0x2ee);
    int32_t dz = (-0x2ee - cz) - (-0x2ee - P99_Cars[0].pos[2]);
    int32_t ax = dx < 0 ? -dx : dx, az = dz < 0 ? -dz : dz;
    int32_t dist = ax < az ? az + ax / 2 : ax + az / 2;
    if (dist >= 45000) continue;
    float x = ((float)dx * cs - (float)dz * sn) * P63_Scale * P94_RadarK + P56_F573FA0;
    float z = ((float)dz * cs + (float)dx * sn) * P63_Scale * P94_RadarK + P56_F573FA4;
    P108_RadarCar((float)cx, (float)cz, i);
    P108_FillRect(x - f2, z - f2, f1, f1, 0xff);
  }
}
