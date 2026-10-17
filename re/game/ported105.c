/* v1.50 (см. ported105.h). Стандарт указателей v1.42: адрес LFB и ссылки поверхностей в записях — uint32 (re_ptr/re_wr_ptr);
   ссылки моделей — P79_PTR. */
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
#include "../platform/plat.h"
#include <stdio.h>
#include <stdlib.h>

#ifdef RE_HOOK_BUILD
#  define P105_STD __attribute__((stdcall))
#else
#  define P105_STD
#endif

#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P105_PixDst")
#undef P105_PixDst
#pragma push_macro("P105_PixDst") /*gvi*/
#undef P105_PixDst /*gvi*/
uint32_t P105_PixDst;
#pragma pop_macro("P105_PixDst") /*gvi*/
#pragma pop_macro("P105_PixDst")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P105_SpinAng")
#undef P105_SpinAng
#pragma push_macro("P105_SpinAng") /*gvi*/
#undef P105_SpinAng /*gvi*/
int32_t P105_SpinAng;
#pragma pop_macro("P105_SpinAng") /*gvi*/
#pragma pop_macro("P105_SpinAng")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P105_MusLimit")
#undef P105_MusLimit
#pragma push_macro("P105_MusLimit") /*gvi*/
#undef P105_MusLimit /*gvi*/
int32_t P105_MusLimit;
#pragma pop_macro("P105_MusLimit") /*gvi*/
#pragma pop_macro("P105_MusLimit")
#endif

static int32_t rd32(const void *p) { int32_t v; memcpy(&v, p, 4); return v; }
static float rdf(const void *p) { float v; memcpy(&v, p, 4); return v; }

/* ---- 00407c4c: LfbLock(1); экран меню 0057b740 → LFB функцией пикселя 0057b73c; пункты меню; Unlock ---- */
int32_t P105_LfbToMenu(void) {
  uint8_t info[0x1c];
  memset(info, 0, sizeof info);
  uint32_t n = 0x1c; memcpy(info, &n, 4);
  uint32_t ok = P68_LfbLock(1, info);
#ifndef RE_HOOK_BUILD
  { static int dbg=-1; if(dbg<0) dbg=getenv("RE_TRACE_MENU")!=0; if(dbg) fprintf(stderr,"[menu] lfb ok=%u d4=%d d8=%d pix=%08x dst=%08x\n",ok,(int)D_00b1c0d4,(int)D_00b1c0d8,P100_PixFn,(unsigned)rd32(info+4)); }
#endif
  if (ok != 0) {
    P105_PixDst = (uint32_t)rd32(info + 4);
    uint8_t *dst = (uint8_t *)re_ptr(P105_PixDst);
    if (dst != NULL) {
      if (P100_PixFn == 0x0040232eu) P101_Pal16((const uint8_t *)P65_Screen, dst, 0x280, 0x1e0);
      else if (P100_PixFn == 0x00402306u) P101_Pal32((const uint8_t *)P65_Screen, dst, 0x280, 0x1e0);
    }
#ifndef RE_HOOK_BUILD
    { static int dbg=-1; if(dbg<0) dbg=getenv("RE_TRACE_MENU")!=0; if(dbg){ int nz=0,np=0,nd=0; const uint8_t*sc=(const uint8_t*)P65_Screen; for(int i=0;i<0x4b000;i++) nz+=sc[i]!=0; for(int i=0;i<256;i++) np+=P101_PalLfb[i]!=0; if(dst) for(int i=0;i<640*480*2;i+=2) nd+=(dst[i]|dst[i+1])!=0;
      int h[256]={0}; for(int i=0;i<0x4b000;i++) h[sc[i]]++; int d=0; for(int i=0;i<256;i++) d+=h[i]!=0; fprintf(stderr,"[menu] screen nz=%d pal nz=%d dst nz=%d pitch=%d distinct=%d h255=%d pal255=%08x pal10=%08x\n",nz,np,nd,(int)P100_LfbPitch,d,h[255],P101_PalLfb[255],P101_PalLfb[10]);} }
#endif
    P58_ItemsDraw((int32_t)P105_PixDst);
    Dev0042480D(1);
  }
  return ok != 0;
}

/* ---- 00422736: эмулируемая поверхность 256×256 (формат и caps из P32_DevInfo +0x520..+0x548);
   o+0x10 — поверхность, o+0x14 — IDirect3DTexture2, o+8 = 0 ---- */
int32_t P105_EmulSurface(uint8_t *o) {
  uint32_t d[31];
  memset(d, 0, sizeof d);
  d[0] = 0x7c; d[1] = 0x1007;
  d[2] = 0x100; d[3] = 0x100;
#ifndef RE_HOOK_BUILD
  if (P32_DevInfo == NULL) { NoopFn0042243f(); return 0; }   /* v1.94: native — устройство не выбрано */
#endif
  memcpy(&d[26], P32_DevInfo + 0x520, 8);    /* ddsCaps */
  memcpy(&d[18], P32_DevInfo + 0x528, 32);   /* DDPIXELFORMAT */
  void *s = P24_CreateSurface(P24_DD, d);
  re_wr_ptr(o + 0x10, s);
  if (s == NULL) { NoopFn0042243f(); return 0; }       /* «CreateEmulatedSurface() failed» */
  memset(o + 8, 0, 4);
  void *t = P54_GetTexture2(s);
  re_wr_ptr(o + 0x14, t);
  if (t == NULL) {
    plat_dd_release(s);
    memset(o + 0x10, 0, 4);
    NoopFn0042243f();
    return 0;
  }
  return 1;
}

/* ---- 004ca802: модель P79_ModelTab[o+0x18] в точке (o+0x20,+0x24,+0x28), вращение по Y шагом 0x1e ---- */
void P105_SpinModel(void *obj) {
  uint8_t *o = (uint8_t *)obj;
  int32_t idx = rd32(o + 0x18);
  if (idx >= P20_Count) return;
#ifndef RE_HOOK_BUILD
  if (idx < 0 || idx >= (int32_t)(sizeof P79_ModelTab / sizeof P79_ModelTab[0])) return;
#endif
  uint32_t m = P79_ModelTab[idx];
  if (m == 0) return;
  float p[3] = { (float)rd32(o + 0x20), (float)rd32(o + 0x24), (float)rd32(o + 0x28) };
  const uint8_t *mp = (const uint8_t *)P79_PTR(m);
#ifndef RE_HOOK_BUILD
  if (mp == NULL) return;
#endif
  int32_t vis = P82_SphereVis3D(p, rdf(mp + 0xc));
  if (vis == 0) return;
  p[0] -= P44_CamX; p[1] -= P44_CamY; p[2] -= P44_CamZ;
  P44_MatPtr = (float *)P44_ViewMatT;
  P44_Xform(p);
  float mat[9] = { 1, 0, 0, 0, 1, 0, 0, 0, 1 };
  P105_SpinAng = (P105_SpinAng + 0x1e) & 0xfff;
  P44_RotY(mat, P105_SpinAng);
  if (P85_BlendCur != 3) { if (P85_BlendFn) P85_BlendFn(4, 4, 0, 0); }
  P85_BlendCur = 1; P69_BlendOn = 1;
  P84_DrawModel(m, mat, p, vis == 1 ? 0 : vis == 2 ? 1 : 2);
}

/* ---- 004d26ea: такт музыки погони; timers — 11 пар (счётчик, …), счётчики уменьшаются до 0 ---- */
void P105_ChaseMusic(int32_t *timers) {
  static const int32_t k_theme[4] = { 0x8005, 0x8007, 0x8006, 0x8008 };   /* .data 0055fe04 */
  if (G6_00B5A778 != 0) return;
  if (G2_00D11A5C != 0 && G2_00D11A5C < 0x2aa) {
    if (P95_D11A38 == P95_ChanState) {
      G2_00D11A5C--; P14_00d11a5c = (uint32_t)G2_00D11A5C;
      P95_D11A38 = 0;
    } else P95_D11A38++;
    return;
  }
  if (P95_SndReady == 0 || G2_00D11A5C < 0x2aa) return;
  if (P11_00b20360 > 0xf0 && P62_Spd > 0x14) {
    int32_t t = (int32_t)P51_DirFromHeading((const uint8_t *)&P99_Cars[0]);
    if (D_00b87e30 == 0) t += 1;
    else if (D_00b87e30 == 1) t += 2;
    if (t != P97_B214) Fwd004D2D9F(0x8004, k_theme[t & 3], -1, -1);
    P97_B214 = t;
  }
  if (P95_D11A54 == P95_D11A4C) {
    G2_00D11A5C++;
    if (G2_00D11A5C > 0xfff) G2_00D11A5C = 0xfff;
    P14_00d11a5c = (uint32_t)G2_00D11A5C;
    P95_D11A54 = 0;
  } else P95_D11A54++;
  if (P105_MusLimit <= G2_00D11A5C) P104_TrafficTurn(P51_DirFromHeading((const uint8_t *)&P99_Cars[0]));
  for (int32_t i = 0; i < 0xb; i++)
    if (timers[i * 2] != 0) timers[i * 2]--;
}

/* ---- 0040d81b: масштабный блит src 640×480 (RGBA, байты r,g,b) → LFB P19_ScrW×P19_ScrH (16/32 бит по формату LfbLock), grBufferSwap(0) ---- */
void P105_BlitScaled(const uint8_t *src) {
  uint8_t info[0x1c];
  memset(info, 0, sizeof info);
  uint32_t n = 0x1c; memcpy(info, &n, 4);
  if (P68_LfbLock(1, info) != 1) return;
  float kx = P19_DivW / (float)P19_ScrW;
  float ky = P19_DivH / (float)P19_ScrH;
  uint8_t bpp = info[0x14];
  uint32_t pitch = (uint32_t)rd32(info + 8);
  uint32_t step = bpp == 0x10 ? pitch >> 1 : pitch >> 2;
  uint8_t *dst = (uint8_t *)re_ptr((uint32_t)rd32(info + 4));
  if (dst != NULL && src != NULL) {
    uint16_t *d16 = (uint16_t *)dst; uint32_t *d32 = (uint32_t *)dst;
    for (int32_t y = 0; y < P19_ScrH; y++) {
      int32_t sy = (int32_t)((double)y * (double)ky);
      for (int32_t x = 0; x < P19_ScrW; x++) {
        int32_t sx = (int32_t)((double)x * (double)kx);
        const uint8_t *s = src + (sy * 0x280 + sx) * 4;
        uint32_t r = (uint32_t)(s[0] >> (info[0x15] & 0x1f)) & 0xff;
        uint32_t g = (uint32_t)(s[1] >> (info[0x16] & 0x1f)) & 0xff;
        uint32_t b = (uint32_t)(s[2] >> (info[0x17] & 0x1f)) & 0xff;
        uint32_t v = r << (info[0x18] & 0x1f) | g << (info[0x19] & 0x1f) | b << (info[0x1a] & 0x1f);
        if (bpp == 0x10) *d16++ = (uint16_t)v; else *d32++ = v;
      }
      d16 += step - (uint32_t)P19_ScrW; d32 += step - (uint32_t)P19_ScrW;
    }
  }
  Dev0042480D(1);
  for (int i = 0; i < P33_GlideCount(); i++)
    if (strcmp(P33_GlideName(i), "_grBufferSwap@4") == 0) {
      void (P105_STD *swap)(int32_t) = (void (P105_STD *)(int32_t))P33_GlideProc(i);
      if (swap) swap(0);
      break;
    }
}

/* ---- 004e53b5: подсказки трюков (режим 4 или P59_S4654 == 1); keys — биты управления, car — запись машины игрока ---- */
static const int32_t k_seq0[16] = { 0, 1, 4, 3, 6, 7, 10, 9, 12, 13, 10, 9, 6, 7, 4, 3 };   /* .data 005468d0 */
static const int32_t k_seq1[16] = { 1, 2, 5, 4, 7, 8, 11, 10, 13, 14, 11, 10, 7, 8, 5, 4 }; /* .data 00546910 */
static const int32_t k_seq2[12] = { 0, 1, 2, 5, 8, 11, 14, 13, 12, 9, 6, 3 };              /* .data 00546950 */
static const p95_seq_t k_seqs[3] = { { 16, k_seq0 }, { 16, k_seq1 }, { 12, k_seq2 } };     /* .data 00562c10..00562c27 */

void P105_StuntHints(int32_t keys, void *carp) {
  uint8_t *car = (uint8_t *)carp;
  if (!((G6_00B87EAC != 0 || P59_S4654 == 1) && D_00b87e30 == 4)) return;
  int32_t spd = rd32(car + 0x10c) >> 0xc;
  int32_t back = spd < 0;
  if (back) spd = -spd;
  if (P98_M4480 < spd) P98_M4480 = spd;
  int32_t lat = rd32(car + 0x50) >> 0xc;
  if (lat < 0) lat = -lat;
  if (P98_M4460 < lat) P98_M4460 = lat;
  int32_t dmg = Get138(car) >> 3;
#ifndef RE_HOOK_BUILD
  { static int dbg = -1; if (dbg < 0) { const char *e = getenv("RE_IVDBG"); dbg = e ? atoi(e) : 0; if (dbg < 0) dbg = 0; }
    if (dbg > 0 && P62_Frame % dbg == 0)
      fprintf(stderr, "[iv] f=%d st=%d picked=%d fl=%d%d%d%d%d%d%d%d%d keys=%03x spd=%d v=%d lat=%d dmg=%d hits=%d cell=%d pos=%d,%d t=%d\n",
              (int)P62_Frame, (int)P59_S4654, (int)P59_Picked, P59_Flags9[0], P59_Flags9[1], P59_Flags9[2], P59_Flags9[3], P59_Flags9[4],
              P59_Flags9[5], P59_Flags9[6], P59_Flags9[7], P59_Flags9[8], (unsigned)keys & 0x1ff, (int)spd, (int)rd32(car + 0x10c), (int)lat,
              (int)dmg, (int)P98_M4660, (int)P15_GridCell(rd32(car + 200), rd32(car + 0xd0)), (int)rd32(car + 200), (int)rd32(car + 0xd0), 0); }
#endif
#ifndef RE_HOOK_BUILD
  { /* v2.25: RE_IVPICK="кадр:задание;…" — отладка: на кадре P62_Frame засчитать задание интервью 0..8 (как засчитывает игра, P59_PickUp) */
    static int pn = -1; static int32_t pf[16], pi[16];
    if (pn < 0) { pn = 0; const char *e = getenv("RE_IVPICK");
      while (e && *e && pn < 16) { int32_t f, i; if (sscanf(e, "%d:%d", &f, &i) != 2) break; pf[pn] = f; pi[pn] = i; pn++; e = strchr(e, ';'); if (e) e++; } }
    for (int t = 0; t < pn; t++) if ((int32_t)P62_Frame == pf[t] && pi[t] >= 0 && pi[t] < 9 && P59_S4654 == 1) {
      fprintf(stderr, "[iv] RE_IVPICK кадр %d → задание %d\n", (int)P62_Frame, (int)pi[t]); P59_PickUp(pi[t]); }
  }
#endif
  if (P59_S4654 == 1 && P98_M4660 == 4) {
    P59_S4654 = 3; G2_00D04654 = 3;
    P14_00d118a8 = 1; G2_00D118A8 = 1;
    G2_00D044C8 = 0; G00D044C8 = 0;
    return;
  }
  PushHistory_004E5938(P15_GridCell(rd32(car + 200), rd32(car + 0xd0)));
  if (P95_SeqMatch(&k_seqs[0]) != 0) P59_PickUp(2);
  if (P95_SeqMatch(&k_seqs[1]) != 0) P59_PickUp(2);
  if (P95_SeqMatch(&k_seqs[2]) != 0) P59_PickUp(8);
  if (lat < 0x12d) P98_M4A5C = 0;
  else if (P98_M4A5C == 0) { P98_M4A5C = 1; P98_M4464 = 0x46; }
  else if (P98_M4464 == 0) P59_PickUp(4);
  else P98_M4464--;
  if (lat < 0xfb) P98_M4A48 = 0;
  else if (P98_M4A48 == 0) { if ((keys & 0x20) != 0) { P98_M4A48 = 1; P98_M390C = 0x28; } }
  else if (P98_M390C == 0) P59_PickUp(3);
  else P98_M390C--;
  if (P59_S44CC > 0) P59_S44CC--;
  if (P59_S4790 > 0) P59_S4790--;
  if (P59_S3904 > 0) P59_S3904--;
  if (P98_M4468 > 0) P98_M4468--;
  int32_t hit = 0;
  if (P44_Rst_B31EA0 != 0 && P98_M4468 == 0) {
    hit = 1; P98_M4468 = 0x28; P98_M38F8 = dmg;
    P12_Fn004E5982(0x11e, 0x96, 1);
    if (P42_ActionBound() == 0) SetFirstFree_004D6190(P62_Frame % 3 + 0xf000);
  }
  if (P98_M4468 > 0) P44_Rst_B31EA0 = 0;
  if (dmg - P98_M38F8 > 0x1e && P98_M4468 == 0) {
    hit = 1; P98_M4468 = 0x28;
    P12_Fn004E5982(0x11f, 0x96, 1);
    if (P42_ActionBound() == 0) SetFirstFree_004D6190(P62_Frame % 3 + 0xf000);
  }
  if (P98_M4468 > 0) P98_M38F8 = dmg;
  if (hit && P98_M4660 < 4) P98_M4660++;
  if (back && spd > 100) P98_M4780 = 1;
  if (lat < 0xc9 || P98_M4780 == 0) { P98_M4780 = 0; P98_M3580 = 0x28; }
  else if (P98_M3580 == 0) P59_PickUp(5);
  else P98_M3580--;
  int32_t v = rd32(car + 0x10c);
  if (v < 0xaa001) { if ((keys & 1) == 0 || hit) P98_M48F4 = 0; }
  else { P98_M48F4 = 1; P98_M4664 = 0x28; }
  if (P98_M48F4 != 0) { if (P98_M4664 == 0) P59_PickUp(7); else P98_M4664--; }
  if (v > 0xb4000) P98_M4474++;
  if (hit || v < 0) P98_M4474 = 0;
  if (P98_M4474 > 5 && v < 0x14000) { P59_PickUp(6); P98_M4474 = 0; }
  if ((keys & 0x40) != 0 && spd > 0x32) P59_PickUp(0);
  if ((keys & 0x20) != 0 && spd > 0x32) P59_PickUp(1);
}
