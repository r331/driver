/* v1.51 (см. ported106.h). Стандарт указателей v1.42: запись объекта C (0110b24c) — P95_ObjPtr; поля узлов эмулируемых текстур — re_rd_ptr. */
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

#ifdef RE_HOOK_BUILD
#  define P106_STD __attribute__((stdcall))
#else
#  define P106_STD
#endif

#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P106_SkyRot")
#undef P106_SkyRot
#pragma push_macro("P106_SkyRot") /*gvi*/
#undef P106_SkyRot /*gvi*/
int32_t P106_SkyRot;
#pragma pop_macro("P106_SkyRot") /*gvi*/
#pragma pop_macro("P106_SkyRot")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P106_PartOn")
#undef P106_PartOn
#pragma push_macro("P106_PartOn") /*gvi*/
#undef P106_PartOn /*gvi*/
int32_t P106_PartOn;
#pragma pop_macro("P106_PartOn") /*gvi*/
#pragma pop_macro("P106_PartOn")
#endif

static int32_t rd32(const void *p) { int32_t v; memcpy(&v, p, 4); return v; }
static uint16_t rd16(const void *p) { uint16_t v; memcpy(&v, p, 2); return v; }
static void wr32(void *p, int32_t v) { memcpy(p, &v, 4); }
static void wr16(void *p, uint16_t v) { memcpy(p, &v, 2); }
static void wrf(void *p, float v) { memcpy(p, &v, 4); }

/* запись модели машины m (00d0cc60 + m*0x16c); в native — в пределах S_00D0CC60, иначе нули */
static const uint8_t *carmodel(uint32_t m) {
#ifndef RE_HOOK_BUILD
  static const uint8_t zero[0x16c];
  if ((m + 1) * 0x16c > sizeof S_00D0CC60) return zero;
#endif
  return S_00D0CC60 + m * 0x16c;
}
/* машина выключена: игрок — G00D17B08 == 0, трафик — байт +1 записи TrafficRecs == 1 */
static int car_off(int32_t car) {
  if (car == 0) return G00D17B08 == 0;
#ifndef RE_HOOK_BUILD
  if (car - 1 >= 0x40) return 1;
#endif
  return TrafficRecs[(car - 1) * 0x54 + 1] == 1;
}
/* точка в системе машины → мир (w) и вид (v) */
static void car_pt(float *v, float *w, int32_t car) {
  P44_MatPtr = P98_CarMat[car];
  P44_XformT(v);
  w[0] = v[0] + (float)P99_Cars[car].pos[0];
  w[1] = v[1] + (float)-P99_Cars[car].pos[1];
  w[2] = v[2] + (float)P99_Cars[car].pos[2];
  w[3] = v[3];
  v[0] = w[0] - P44_CamX; v[1] = w[1] - P44_CamY; v[2] = w[2] - P44_CamZ;
  P44_MatPtr = P44_ViewMatT;
  P44_Xform(v);
}
/* вторая точка пары: только вид */
static void car_pt2(float *v, int32_t car) {
  v[0] = (v[0] + (float)P99_Cars[car].pos[0]) - P44_CamX;
  v[1] = (v[1] + (float)-P99_Cars[car].pos[1]) - P44_CamY;
  v[2] = (v[2] + (float)P99_Cars[car].pos[2]) - P44_CamZ;
}
static void addb(const float *v, const float *w, int16_t a, int16_t b, uint32_t fl, int32_t c, int32_t d) {
  int32_t uv[4]; memcpy(uv, w, 16);
  P96_AddObjB(v, uv, a, b, fl, 1, c, d);
}
/* объект C (0110b24c): +0 p0, +0x10 p1, флаги 0x20, углы, машина, номер огня */
static void addc(const float *p0, const float *p1, int16_t a, uint16_t hd, int32_t car, int32_t kind) {
  float *r = (float *)P95_ObjPtr((uint32_t)G0110B24C);
#ifndef RE_HOOK_BUILD
  if (r == NULL) return;
#endif
  memcpy(&r[4], p1, 16);
  memcpy(&r[0], p0, 16);
  wr32(&r[0x1a], 0x20);
  wr32(&r[0x1c], 0); wr32(&r[0x1d], 0);
  wr16(&r[0x1b], (uint16_t)a);
  wr16((uint8_t *)r + 0x6e, hd);
  wr32(&r[0x14], car);
  wrf(&r[0x15], (float)kind);
  G0110B24C += 0x78;
  G010FFA20++;
}
/* пара точек по ширине: флаг ориентации ori — сдвиг по Y, иначе по X */
static void pair(float *a, float *b, const float *s, int32_t w, float z, int ori) {
  if (ori == 0) { a[0] = s[0] - (float)w; a[1] = s[1]; b[0] = (float)w + s[0]; b[1] = s[1]; }
  else { a[0] = s[0]; a[1] = s[1] - (float)w; b[0] = s[0]; b[1] = (float)w + s[1]; }
  a[2] = z; b[2] = z; a[3] = 0.0f; b[3] = 0.0f;
}

/* ---- 004ae6fb: пятна фар на дороге (объекты B), если машина повёрнута к камере (|угол| ≤ 0x600) ---- */
void P106_CarHeadSpots(int32_t car) {
#ifndef RE_HOOK_BUILD
  if (car < 0 || car >= 65) return;
#endif
  const uint8_t *m = carmodel(P99_Cars[car].f00[2]);
  if (car_off(car)) return;
  int16_t a0 = P99_Cars[car].ang[0];
  uint32_t hd = ((uint32_t)P99_Cars[car].heading + 0x800) & 0xfff;
  int32_t d = (int32_t)(((-hd - (uint32_t)P59_AngB) + 0x800) & 0xfff) - 0x800;
  if (!(d < 0x601 && -0x601 < d)) return;
  uint16_t fl = rd16(m + 0x102);
  for (int32_t side = 0; side < 2; side++) {
    int32_t dmg = side == 0 ? P99_Cars[car].vel[0] : P99_Cars[car].vel[1];
    int32_t mark = side == 0 ? 0 : 2;
    const uint8_t *src = side == 0 ? m + 0x10 : m;
    if (dmg >= 1000) continue;
    int32_t sh = dmg >> 6;
    float s[3]; memcpy(s, src, 12);
    if ((fl & 0x8000) == 0) {
      float v[4] = { s[0], s[1], (float)sh + s[2], 0.0f }, w[4];
      car_pt(v, w, car);
      if (P95_Near <= v[2] && P14_00b87e84 != 0) addb(v, w, a0, (int16_t)hd, 0x800004, car, mark);
    } else {
      int32_t wd = ((fl & 0xc00) >> 8) + 10;
      float a[4], b[4], w[4];
      pair(a, b, s, wd, (float)sh + s[2], (fl & 0x2000) != 0);
      P44_MatPtr = P98_CarMat[car];
      P44_XformT(b);
      car_pt(a, w, car);
      car_pt2(b, car);
      P44_Xform(b);
      if (P95_Near <= a[2] && P14_00b87e84 != 0) {
        addb(a, w, a0, (int16_t)hd, 0x800004, car, mark);
        addb(b, w, a0, (int16_t)((hd + 0x32) & 0xfff), 0x800004, car, mark + 1);
      }
    }
  }
}

/* общая часть 004adfcc/004ad837: огни +0x70 (повреждение +0x12c, номер 4) и +0x60 (+0x128, номер 6) модели */
static void tail_lights(int32_t car, int brake) {
  const uint8_t *m = carmodel(P99_Cars[car].f00[2]);
  int16_t a0 = P99_Cars[car].ang[0];
  uint16_t hd = (uint16_t)P99_Cars[car].heading;
  uint16_t fl = rd16(m + 0x102);
  for (int32_t side = 0; side < 2; side++) {
    int32_t dmg = side == 0 ? P99_Cars[car].f12c : P99_Cars[car].f128;
    const uint8_t *src = m + (side == 0 ? 0x70 : 0x60);
    int32_t kind = side == 0 ? 4 : 6;
    if (dmg >= 500) continue;
    int32_t sh = dmg >> 7;
    float s[3]; memcpy(s, src, 12);
    if ((fl & 0x4000) == 0) {
      float v[4] = { s[0], s[1], s[2] - (float)sh, 0.0f }, w[4];
      car_pt(v, w, car);
      if (P95_Near <= v[2]) {
        if (brake && P14_00b87e84 != 0) addb(v, w, a0, (int16_t)hd, 5, -1, -1);
        addc(v, w, a0, hd, car, kind);
      }
    } else {
      int32_t wd = ((rd16(m + 0x102) & 0x300) >> 6) + 10;
      float a[4], b[4], w[4];
      pair(a, b, s, wd, s[2] - (float)sh, (fl & 0x1000) != 0);
      P44_MatPtr = P98_CarMat[car];
      P44_XformT(b);
      car_pt(a, w, car);
      car_pt2(b, car);
      P44_Xform(b);
      if (P95_Near <= a[2]) {
        if (brake && P14_00b87e84 != 0) { addb(a, w, a0, (int16_t)hd, 5, -1, -1); addb(b, w, a0, (int16_t)hd, 5, -1, -1); }
        addc(a, w, a0, hd, car, kind);
        addc(b, b, a0, hd, car, kind + 1);   /* у второй точки обе копии — координаты вида (как в Game.exe) */
      }
    }
  }
}

/* ---- 004adfcc: задние огни машины (объекты C), пока объектов < 0xc9 ---- */
void P106_CarTailLights(int32_t car) {
#ifndef RE_HOOK_BUILD
  if (car < 0 || car >= 65) return;
#endif
  if (!(G010FFA20 < 0xc9 && P14_00b87e84 != 0)) return;
  if (car_off(car)) return;
  tail_lights(car, 0);
}

/* ---- 004ad837: стоп-сигналы (объекты C и B), если машина повёрнута задом к камере (|угол| ≤ 0x320) ---- */
void P106_CarBrakeLights(int32_t car) {
#ifndef RE_HOOK_BUILD
  if (car < 0 || car >= 65) return;
#endif
  if (G010FFA20 >= 0xc9) return;
  uint32_t hd = (uint32_t)P99_Cars[car].heading;
  int32_t d = (int32_t)(((((uint32_t)-(int32_t)P59_AngB & 0xfffu) - hd) + 0x800) & 0xfff) - 0x800;
  if (!(d < 0x321 && -0x321 < d)) return;
  tail_lights(car, 1);
}

/* ---- 00420a21: годится ли формат эмулируемой текстуры 256×256 для устройства dev (CreateSurface + Release) ---- */
int32_t P106_CanDevTex(const uint8_t *dev, void *dd) {
  uint32_t d[31];
  memset(d, 0, sizeof d);
  d[0] = 0x7c; d[1] = 0x1007;
  memcpy(&d[26], dev + 0x520, 8);    /* ddsCaps */
  d[3] = 0x100; d[2] = 0x100;
  memcpy(&d[18], dev + 0x528, 32);   /* DDPIXELFORMAT */
  void *s = P24_CreateSurface(dd, d);
  if (s == NULL) { NoopFn0042243f(); return 0; }     /* «CanDeviceTexture failed» */
  plat_dd_release(s);
  if (rd32(dev + 0x588) == 0) {
    memcpy(&d[18], dev + 0x548, 32);
    s = P24_CreateSurface(dd, d);
    if (s == NULL) { NoopFn0042243f(); return 0; }
    plat_dd_release(s);
  }
  return 1;
}

/* ---- 0042282f: 256×256 индексов src → 16 бит во все поверхности списка (палитра — узел +0xc) ---- */
void P106_EmulUpload8(void *node, int32_t src) {
  for (uint8_t *n = (uint8_t *)node; n != NULL; n = (uint8_t *)re_rd_ptr(n + 0x18)) {
    uint32_t d[31];
    memset(d, 0, sizeof d);
    d[0] = 0x7c;
    void *s = re_rd_ptr(n + 0x10);
    if (plat_dd_lock(s, d) == 0) {
      P74_Conv8to16((const uint8_t *)re_ptr((uint32_t)src), (const uint8_t *)re_rd_ptr(n + 0xc),
                    (uint16_t *)re_ptr(d[9]), (int32_t)d[4]);
      plat_dd_unlock(s);
#ifndef RE_HOOK_BUILD
      { uint32_t pg, kd; memcpy(&pg, n, 4); memcpy(&kd, n + 4, 4); P86_GameAttachEmul8(s, (int32_t)pg, (int32_t)kd); }   /* v2.18 */
#endif
    } else NoopFn0042243f();                          /* «Lock emultexture8() failed» */
  }
}

/* ---- 004228eb: 256 строк по 0x200 байт src в поверхности списка с типом +4 == G6_0054EF2C ---- */
void P106_EmulUpload16(void *node, int32_t src) {
  for (uint8_t *n = (uint8_t *)node; n != NULL; n = (uint8_t *)re_rd_ptr(n + 0x18)) {
    if (rd32(n + 4) != G6_0054EF2C) continue;
    uint32_t d[31];
    memset(d, 0, sizeof d);
    d[0] = 0x7c;
    void *s = re_rd_ptr(n + 0x10);
    if (plat_dd_lock(s, d) == 0) {
      uint8_t *dst = (uint8_t *)re_ptr(d[9]);
#ifndef RE_HOOK_BUILD
      if (dst == NULL) { plat_dd_unlock(s); src += 0x20000; continue; }
#endif
      for (int32_t y = 0; y < 0x100; y++) {
        P13_Fn00422AC0(dst, re_ptr((uint32_t)src), 0x200);
        dst += ((int32_t)d[4] >> 1) * 2;
        src += 0x200;
      }
      plat_dd_unlock(s);
    } else NoopFn0042243f();
  }
}

/* ---- 004d92d2: строка text шрифтом 8×8 (P21_Font8) в LFB с позиции (G6_00D117A4, G6_00D117A8) цветом WH00B2C3A8 ---- */
typedef struct { uint32_t size; void *lfb; uint32_t stride; uint32_t mode; uint32_t origin; } p106_lfbinfo_t;
void P106_LfbText(uint32_t text) {
  p106_lfbinfo_t info; memset(&info, 0, sizeof info);
  info.size = 0x14;
  const uint8_t *t = (const uint8_t *)re_ptr(text);
#ifndef RE_HOOK_BUILD
  if (P97_LfbLock == NULL || t == NULL) return;
#endif
  P97_LfbLock(1, 1, 0xff, 0, 0, &info);
#ifndef RE_HOOK_BUILD
  if (info.lfb == NULL) return;
#endif
  uint8_t *line = (uint8_t *)info.lfb + G6_00D117A8 * 8 * (int32_t)(info.stride >> 1) * 2 + G6_00D117A4 * 0x10;
  uint8_t c;
  while ((c = *t++) != 0) {
    if (c == 10) {
      CursorWrap004D9478();
      line = (uint8_t *)info.lfb + G6_00D117A8 * 8 * (int32_t)(info.stride >> 1) * 2 + G6_00D117A4 * 0x10;
      continue;
    }
    if (0x60 < c && c < 0x7b) c = (uint8_t)(c + 0xa0);
    uint8_t *p = line;
    for (int32_t row = 0; row < 8; row++) {
      uint8_t bits = P21_Font8[c * 8 + row];
      for (int32_t x = 0; x < 8; x++) {
        if (bits & 0x80) wr16(p, WH00B2C3A8);
        p += 2;
        bits = (uint8_t)(bits << 1);
      }
      p += (int32_t)(info.stride & 0xfffffffeu) - 0x10;
    }
    line += 0x10;
    G6_00D117A4++;
  }
#ifndef RE_HOOK_BUILD
  if (FnPtr01270EAC == NULL) return;
#endif
  FnPtr01270EAC(1, 1);
}

/* ---- 004ef66a: небо — модели P79_ModelTab[0..3] в точке (0, 40, 36) вида, текстура по таблице .data 00562d9c ---- */
/* .data 00562d9c: 7 городов × 5 (tools/pedump rd из Game.exe) */
static const int32_t k_sky_tex[7 * 5] = {
  0x2, 0x14, 0x15, 0x14, 0x16,  0x2, 0x14, 0x15, 0x14, 0x16,  0x2, 0x2, 0x2, 0x2, 0x2,  0x2, 0x14, 0x15, 0x14, 0x16,
  0x2, 0x2, 0x2, 0x2, 0x2,  0x2, 0x2, 0x2, 0x2, 0x2,  0x2, 0x2, 0x2, 0x2, 0x2 };
static void depth_bias(int32_t v) {
  for (int i = 0; i < P33_GlideCount(); i++)
    if (strcmp(P33_GlideName(i), "_grDepthBiasLevel@4") == 0) {
      void (P106_STD *f)(int32_t) = (void (P106_STD *)(int32_t))P33_GlideProc(i);
      if (f != NULL) f(v);
      return;
    }
}
void P106_SkyModels(void) {
  float pos[4] = { 0.0f, 40.0f, 36.0f, 0.0f };   /* 0x42200000, 0x42100000 */
  int32_t k = (P14_00b202d8 == 0 && P14_00b202dc == 0) ? P14_00b87e84 + P26_FxA * 2 : 4;
  int32_t idx = D_00b87e30 * 5 + k;
#ifndef RE_HOOK_BUILD
  if (idx < 0 || idx >= 7 * 5) return;
#endif
  P12_Fn00426580(k_sky_tex[idx]);
  P44_MatPtr = P44_ViewMatT;
  P44_Xform(pos);
#ifndef RE_HOOK_BUILD
  if (P56_EulerTab == NULL) return;
#endif
  const float *mat = (const float *)(P56_EulerTab + P106_SkyRot * 0x40);
  P62_B25F400 = 0;
  int32_t mode = DrvSetMode0042655A(0);
  depth_bias(0x7fff);
  for (int i = 0; i < 4; i++) P84_DrawModel(P79_ModelTab[i], mat, pos, 1);
  depth_bias(0);
  DrvSetMode0042655A(mode);
}

/* ---- 00512174: такт 64 частиц A_00C56780 (0xb4): клетки карты вокруг, падение/курс, вращение, путь, дальность от игрока ---- */
static float rdf4(const uint8_t *p) { float v; memcpy(&v, p, 4); return v; }
static int32_t fr(float v) { return (int32_t)lrintf(v); }   /* fistp */
static int16_t road_at(const uint8_t *p, int32_t dx, int32_t dz) {
  P11_00ba52d0 = fr(rdf4(p + 0x8c));
  int32_t z = P11_00ba52d0;
  P11_00ba52d0 = fr(rdf4(p + 0x84));
  return (int16_t)P72_RoadWord(P11_00ba52d0 + dx, z + dz);
}
static void spin_end(uint8_t *p) {
  wr32(p + 0xc, (int32_t)((uint32_t)rd32(p + 0xc) & 0xffffcfffu));
  wr16(p + 0x5e, rd16(p + 0x14));
  P71_Course(p);
}
#ifndef RE_HOOK_BUILD
/* v2.09: RE_PEDDBG=1 — раз в 100 вызовов: включены ли пешеходы, лимит, точки появления, занятые слоты */
static void ped_dbg(void) {
  static int n; static int on = -1; if (on < 0) on = getenv("RE_PEDDBG") != NULL; if (!on || (n++ % (getenv("RE_PEDN") ? atoi(getenv("RE_PEDN")) : 100)) != 0) return;
  int act = 0, t[4] = { 0 }; const uint8_t *q = A_00C56780;
  float dmin = 1e30f;
  for (int i = 0; i < 0x40; i++, q += 0xb4) if (((uint32_t)rd32(q + 0xc) & 0x10) != 0) { act++; int16_t k = (int16_t)rd16(q); if (k >= 0 && k < 4) t[k]++;
      float fx, fz; memcpy(&fx, q + 0x84, 4); memcpy(&fz, q + 0x8c, 4); fx -= (float)P99_Cars[0].pos[0]; fz -= (float)P99_Cars[0].pos[2];
      float d = sqrtf(fx * fx + fz * fz); if (d < dmin) dmin = d;
      if (i < 3) fprintf(stderr, "[ped]  #%d тип %d pos %.0f %.0f fl %x\n", i, k, fx + (float)P99_Cars[0].pos[0], fz + (float)P99_Cars[0].pos[2], (unsigned)rd32(q + 0xc)); }
  { extern int32_t P113_PedStat[5];
    if (act) fprintf(stderr, "[ped] nearest %.0f draw: calls %d near %d frustum %d grid %d mind %d\n", dmin, P113_PedStat[0], P113_PedStat[1],
                     P113_PedStat[2], P113_PedStat[3], P113_PedStat[4]); P113_PedStat[4] = 0x7fffffff; }
  fprintf(stderr, "[ped] call %d on %d limit %d ebc %d dustN %d used %d active %d (type0 %d 1 %d 2 %d 3 %d) car %d %d\n", n - 1, P106_PartOn, P60_PartLimit,
      P95_B87EBC, P102_DustN, G6_00C56764, act, t[0], t[1], t[2], t[3], P99_Cars[0].pos[0], P99_Cars[0].pos[2]);
}
#endif
void P106_PartTick(void) {
#ifndef RE_HOOK_BUILD
  ped_dbg();
  /* v2.10: RE_PEDNEAR=K — отладка видимости: первый активный пешеход каждый такт ставится перед машиной игрока
     (машина + K/1000 · (машина − камера) по XZ), чтобы проверить, рисует ли P113_PartDraw → P100_DrawParts модель */
  { static int on = -1; static float kk; if (on < 0) { on = getenv("RE_PEDNEAR") != NULL; if (on) kk = (float)atof(getenv("RE_PEDNEAR")) / 1000.0f; }
    if (on) { uint8_t *q = A_00C56780;
      for (int i = 0; i < 0x40; i++, q += 0xb4) if (((uint32_t)rd32(q + 0xc) & 0x10) != 0) {
        float cx = (float)P99_Cars[0].pos[0], cz = (float)P99_Cars[0].pos[2];
        float f[3] = { cx + kk * (cx - P44_CamX), 0.0f, cz + kk * (cz - P44_CamZ) };
        f[1] = (float)-P100_RoadHeightF(f);
        memcpy(q + 0x84, f, 12); break; } } }
#endif
  if (P106_PartOn == 0 || P60_PartLimit == 0) return;
  P73_C5670C++;
  P98_PartDist = P99_Cars[0].speed * 0xf;
  if (P98_PartDist < 0x5dc) P98_PartDist = 0x5dc;
  P102_CarPlanes((const uint8_t *)&P99_Cars[0], P98_PartPl, P98_PartDist);
  if (P95_B87EBC != 0) return;
  CountActive_005120A7();
  P102_SpawnDust();
  uint8_t *p = A_00C56780;
  for (int32_t n = 0x40; n != 0; n--, p += 0xb4) {
    if (((uint32_t)rd32(p + 0xc) & 0x10) != 0) {
      P102_NbrC = road_at(p, 0, 0);
      P101_Nbr[0] = road_at(p, 0, -0x5dc);
      P101_Nbr[1] = road_at(p, 0, 0x5dc);
      P101_Nbr[2] = road_at(p, 0x5dc, 0);
      P101_Nbr[3] = road_at(p, -0x5dc, 0);
      uint32_t fl = (uint32_t)rd32(p + 0xc);
      if ((fl & 0x800) == 0) {
        if (P102_NbrC == -0x8000) {
          memcpy(p + 0xa4, p + 0x84, 16);
          if ((fl & 8) != 0) {
            wr32(p + 0xc, (int32_t)(fl & 0xfffffff7u));
            uint16_t a = rd16(p + 0x5e);
            P101_PartTurn(p);
            if (((uint32_t)rd32(p + 0xc) & 0x10) != 0) { wr16(p + 0x5e, a); P71_Course(p); }
          }
        } else if ((fl & 8) == 0 && rd32(p + 0x1c) != 3) {
          wr32(p + 0xc, (int32_t)(fl | 8));
          memcpy(p + 0x94, p + 0xa4, 16);
          P11_00ba52d0 = fr(rdf4(p + 0x94) - rdf4(p + 0x84));
          int32_t dx = P11_00ba52d0;
          P11_00ba52d0 = fr(rdf4(p + 0x9c) - rdf4(p + 0x8c));
          int32_t ang = P44_Atan2(P11_00ba52d0, dx);
          uint32_t dir = AngleToDir00514103((0xfffffc00u - (uint32_t)ang) & 0xfff);
          P71_Course(p);
          wr32(p + 0x38, (int32_t)dir);
        }
      } else P101_PartFall(p);
      wr16(p + 0x4c, 0); wr16(p + 0x4e, 0);
      fl = (uint32_t)rd32(p + 0xc);
      if ((fl & 0x800) == 0 || rd32(p + 0x1c) != 3) {
        int16_t t = (int16_t)rd16(p);
        if (t == 1) P96_PartRunA(p);
        else if (t == 2) P96_PartRunB(p);
        else if (t == 3) P98_PartAim((int16_t *)p);   /* 00513cf9 — переход на 00514a47 */
      }
    }
    if (((uint32_t)rd32(p + 0xc) & 0x10) == 0) continue;
    uint32_t fl = (uint32_t)rd32(p + 0xc);
    int16_t t = (int16_t)rd16(p);
    if ((fl & 0x1000) == 0) {
      if ((fl & 0x2000) != 0) {
        wr16(p + 0x5e, (uint16_t)((rd16(p + 0x5e) + 0x80) & 0xfff));
        wr32(p + 0x18, rd32(p + 0x18) - 0x80);
        if (rd32(p + 0x18) < 1) spin_end(p);
      }
    } else {
      uint16_t a = (uint16_t)(rd16(p + 0x5e) - 0x80);
      if (t == 2) a = (uint16_t)(a - 0x80);
      wr16(p + 0x5e, (uint16_t)(a & 0xfff));
      wr32(p + 0x18, rd32(p + 0x18) - 0x80);
      if (t == 2) wr32(p + 0x18, rd32(p + 0x18) - 0x80);
      if (rd32(p + 0x18) < 1) spin_end(p);
    }
    P103_PartPath(p);
    float dz = rdf4(p + 0x8c) - (float)P99_Cars[0].pos[2];
    float dx = rdf4(p + 0x84) - (float)P99_Cars[0].pos[0];
    if (dz * dz + dx * dx <= 1640249984.0f) {      /* .rdata 00546a68 */
      if (P99_Cars[0].speed != 0) P98_PartCheck((int16_t *)p);
    } else P43_FreeSlot(p);
  }
}

/* ---- 0048bf52: пресет окружения EAX i (IKsPropertySet::Set, свойство 0, 16 байт из .data 005511f0) ---- */
static const uint8_t k_eax_guid[16] = { 0xc1, 0x6f, 0x4e, 0x4a, 0x41, 0xc3, 0xd1, 0x11, 0xb7, 0x3a, 0x44, 0x45, 0x53, 0x54, 0x00, 0x00 };  /* .data 00546740 */
/* .data 005511f0: 7 записей {окружение, громкость, затухание, демпфирование} (tools/pedump rd из Game.exe) */
static const uint32_t k_eax_preset[7][4] = {
  { 6, 0x3ece5604u, 0x4088ed91u, 0x3f000000u }, { 16, 0x3de353f8u, 0x40311687u, 0x3e656042u },
  { 14, 0x3e800000u, 0x3fe04189u, 0x3f46a7f0u }, { 20, 0x3e54fdf4u, 0x3fd374bcu, 0x3fc00000u },
  { 22, 0x3f800000u, 0x3fbfdf3bu, 0x00000000u }, { 2, 0x3ed58106u, 0x3ecccccdu, 0x3f2a7efau },
  { 21, 0x3f26e979u, 0x4038b439u, 0x3e800000u } };
void P106_EaxPreset(int32_t i) {
  if (P48_B91D30 == 0 || P49_Prop30 == NULL) return;
#ifndef RE_HOOK_BUILD
  if (i < 0 || i >= 7) return;
#endif
  plat_ds_prop_set(P49_Prop30, k_eax_guid, 0, k_eax_preset[i], 0x10);
}
