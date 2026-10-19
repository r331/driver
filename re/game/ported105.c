/* ported105.c — front-end LFB blits, emulated texture surfaces, a spinning pickup model, the cop-chase
   music/felony tick and the garage-interview manoeuvre checks (English overview; original notes follow).
   Pointer convention v1.42: LFB addresses and surface references inside records are uint32 Game.exe-style
   addresses (re_ptr / re_wr_ptr); model references go through P79_PTR. */
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

#include "memrw.h"
#include "carfields.h"

/* ---- 00407c4c: LfbLock(1); экран меню 0057b740 → LFB функцией пикселя 0057b73c; пункты меню; Unlock ---- */
/* P105_LfbToMenu — Game.exe 00407c4c.  Locks the frame buffer, converts the 8-bit menu screen (640x480,
   P65_Screen) through the palette into it with the pixel converter chosen for the mode (16 or 32 bit,
   0040232e / 00402306), draws the menu items and unlocks.  Returns 1 if the lock succeeded.
   Native: RE_TRACE_MENU=1 prints diagnostics. */
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
/* P105_EmulSurface — Game.exe 00422736.  Creates a 256x256 texture surface (caps and pixel format from the
   selected device's info +0x520..+0x548) into o+0x10 and its IDirect3DTexture2 into o+0x14; clears o+8.
   Returns 1, or 0 on failure (nothing left allocated).  Native: 0 when no device is selected. */
int32_t P105_EmulSurface(uint8_t *o) {
  uint32_t desc[31];
  memset(desc, 0, sizeof desc);
  desc[0] = 0x7c; desc[1] = 0x1007;
  desc[2] = 0x100; desc[3] = 0x100;
#ifndef RE_HOOK_BUILD
  if (P32_DevInfo == NULL) { NoopFn0042243f(); return 0; }   /* v1.94: native — устройство не выбрано */
#endif
  memcpy(&desc[26], P32_DevInfo + 0x520, 8);    /* ddsCaps */
  memcpy(&desc[18], P32_DevInfo + 0x528, 32);   /* DDPIXELFORMAT */
  void *surf = P24_CreateSurface(P24_DD, desc);
  re_wr_ptr(o + 0x10, surf);
  if (surf == NULL) { NoopFn0042243f(); return 0; }       /* «CreateEmulatedSurface() failed» */
  memset(o + 8, 0, 4);
  void *tex = P54_GetTexture2(surf);
  re_wr_ptr(o + 0x14, tex);
  if (tex == NULL) {
    plat_dd_release(surf);
    memset(o + 0x10, 0, 4);
    NoopFn0042243f();
    return 0;
  }
  return 1;
}

/* ---- 004ca802: модель P79_ModelTab[o+0x18] в точке (o+0x20,+0x24,+0x28), вращение по Y шагом 0x1e ---- */
/* P105_SpinModel — Game.exe 004ca802.  Draws model P79_ModelTab[o+0x18] at (o+0x20, +0x24, +0x28), rotating
   about Y by 0x1e per call (shared angle P105_SpinAng), if its bounding sphere is visible; level of detail
   from the visibility result.  TODO(RE): unsure which objects use it (pickups / markers?). */
void P105_SpinModel(void *obj) {
  uint8_t *o = (uint8_t *)obj;
  int32_t idx = rd32(o + 0x18);
  if (idx >= P20_Count) return;
#ifndef RE_HOOK_BUILD
  if (idx < 0 || idx >= (int32_t)(sizeof P79_ModelTab / sizeof P79_ModelTab[0])) return;
#endif
  uint32_t model = P79_ModelTab[idx];
  if (model == 0) return;
  float pos[3] = { (float)rd32(o + 0x20), (float)rd32(o + 0x24), (float)rd32(o + 0x28) };
  const uint8_t *model_ptr = (const uint8_t *)P79_PTR(model);
#ifndef RE_HOOK_BUILD
  if (model_ptr == NULL) return;
#endif
  int32_t vis = P82_SphereVis3D(pos, rdf(model_ptr + 0xc));
  if (vis == 0) return;
  pos[0] -= P44_CamX; pos[1] -= P44_CamY; pos[2] -= P44_CamZ;
  P44_MatPtr = (float *)P44_ViewMatT;
  P44_Xform(pos);
  float mat[9] = { 1, 0, 0, 0, 1, 0, 0, 0, 1 };
  P105_SpinAng = (P105_SpinAng + 0x1e) & 0xfff;
  P44_RotY(mat, P105_SpinAng);
  if (P85_BlendCur != 3) { if (P85_BlendFn) P85_BlendFn(4, 4, 0, 0); }
  P85_BlendCur = 1; P69_BlendOn = 1;
  P84_DrawModel(model, mat, pos, vis == 1 ? 0 : vis == 2 ? 1 : 2);
}

/* ---- 004d26ea: такт музыки погони; timers — 11 пар (счётчик, …), счётчики уменьшаются до 0 ---- */
/* P105_ChaseMusic — Game.exe 004d26ea.  Per-tick felony/chase update (skipped while paused).
   Felony (00d11a5c) below 0x2aa decays by 1 every P95_ChanState+1 ticks.  At or above 0x2aa with a cop
   sound channel ready: at speed (00b20360 > 0xf0, P62_Spd > 20) switches the chase music theme by the
   player's compass direction (offset by city), raises felony by 1 every P95_D11A4C+1 ticks (max 0xfff),
   and once felony reaches P105_MusLimit lets traffic react to the player's direction (P104_TrafficTurn).
   Counts the 11 timers (pairs, first word) in `timers` down to 0.
   TODO(RE): the function name came from the music switch; it is mostly the felony tick. */
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
    int32_t dir = (int32_t)P51_DirFromHeading((const uint8_t *)&P99_Cars[0]);
    if (D_00b87e30 == 0) dir += 1;
    else if (D_00b87e30 == 1) dir += 2;
    if (dir != P97_B214) Fwd004D2D9F(0x8004, k_theme[dir & 3], -1, -1);
    P97_B214 = dir;
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
/* P105_BlitScaled — Game.exe 0040d81b.  Nearest-neighbour scales a 640x480 RGBA picture (bytes r, g, b, -) to the
   frame buffer (P19_ScrW x P19_ScrH, 16 or 32 bit; channel shifts from the LfbLock info +0x15..+0x1a),
   unlocks and swaps buffers (grBufferSwap(0)). */
void P105_BlitScaled(const uint8_t *src) {
  uint8_t info[0x1c];
  memset(info, 0, sizeof info);
  uint32_t n = 0x1c; memcpy(info, &n, 4);
  if (P68_LfbLock(1, info) != 1) return;
  float scale_x = P19_DivW / (float)P19_ScrW;
  float scale_y = P19_DivH / (float)P19_ScrH;
  uint8_t bpp = info[0x14];
  uint32_t pitch = (uint32_t)rd32(info + 8);
  uint32_t pitch_px = bpp == 0x10 ? pitch >> 1 : pitch >> 2;
  uint8_t *dst = (uint8_t *)re_ptr((uint32_t)rd32(info + 4));
  if (dst != NULL && src != NULL) {
    uint16_t *d16 = (uint16_t *)dst; uint32_t *d32 = (uint32_t *)dst;
    for (int32_t y = 0; y < P19_ScrH; y++) {
      int32_t sy = (int32_t)((double)y * (double)scale_y);
      for (int32_t x = 0; x < P19_ScrW; x++) {
        int32_t sx = (int32_t)((double)x * (double)scale_x);
        const uint8_t *src_px = src + (sy * 0x280 + sx) * 4;
        uint32_t r = (uint32_t)(src_px[0] >> (info[0x15] & 0x1f)) & 0xff;
        uint32_t g = (uint32_t)(src_px[1] >> (info[0x16] & 0x1f)) & 0xff;
        uint32_t b = (uint32_t)(src_px[2] >> (info[0x17] & 0x1f)) & 0xff;
        uint32_t pixel = r << (info[0x18] & 0x1f) | g << (info[0x19] & 0x1f) | b << (info[0x1a] & 0x1f);
        if (bpp == 0x10) *d16++ = (uint16_t)pixel; else *d32++ = pixel;
      }
      d16 += pitch_px - (uint32_t)P19_ScrW; d32 += pitch_px - (uint32_t)P19_ScrW;
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

/* P105_StuntHints — Game.exe 004e53b5.  Checks the manoeuvres of the garage interview (city index 4, in
   Undercover or interview state P59_S4654 == 1) and credits them with P59_PickUp(0..8).
   In: keys — control bits of this tick (0x20 / 0x40 / 1 tested below), carp — the player's car record.
   Tracks max forward speed and yaw rate (angular velocity y), damage hits (4 hits end the interview:
   state 3, controls taken away), a cell history for the slalom/lap sequences (k_seq0/1 -> task 2,
   k_seq2 -> task 8), sustained yaw (task 4 after 70 ticks above 300; task 3 after 40 ticks above 250
   started with key 0x20; task 5 after reversing faster than 100 then yawing), top speed held with key 1
   (task 7), hard stop from high speed (task 6), and keys 0x40 / 0x20 above speed 50 (tasks 0 / 1).
   TODO(RE): map task indices 0..8 to the interview's named manoeuvres; key bit meanings.
   Native: RE_IVDBG / RE_IVPICK debug hooks (no effect unless set). */
void P105_StuntHints(int32_t keys, void *carp) {
  uint8_t *car = (uint8_t *)carp;
  if (!((G6_00B87EAC != 0 || P59_S4654 == 1) && D_00b87e30 == 4)) return;
  int32_t fwd_speed = rd32(car + CAR_FWD_SPEED) >> 0xc;
  int32_t reversing = fwd_speed < 0;
  if (reversing) fwd_speed = -fwd_speed;
  if (P98_M4480 < fwd_speed) P98_M4480 = fwd_speed;
  int32_t yaw_rate = rd32(car + CAR_ANGVEL + 4) >> 0xc;
  if (yaw_rate < 0) yaw_rate = -yaw_rate;
  if (P98_M4460 < yaw_rate) P98_M4460 = yaw_rate;
  int32_t damage = Get138(car) >> 3;
#ifndef RE_HOOK_BUILD
  { static int dbg = -1; if (dbg < 0) { const char *e = getenv("RE_IVDBG"); dbg = e ? atoi(e) : 0; if (dbg < 0) dbg = 0; }
    if (dbg > 0 && P62_Frame % dbg == 0)
      fprintf(stderr, "[iv] f=%d st=%d picked=%d fl=%d%d%d%d%d%d%d%d%d keys=%03x spd=%d v=%d lat=%d dmg=%d hits=%d cell=%d pos=%d,%d t=%d\n",
              (int)P62_Frame, (int)P59_S4654, (int)P59_Picked, P59_Flags9[0], P59_Flags9[1], P59_Flags9[2], P59_Flags9[3], P59_Flags9[4],
              P59_Flags9[5], P59_Flags9[6], P59_Flags9[7], P59_Flags9[8], (unsigned)keys & 0x1ff, (int)fwd_speed, (int)rd32(car + CAR_FWD_SPEED), (int)yaw_rate,
              (int)damage, (int)P98_M4660, (int)P15_GridCell(rd32(car + CAR_POS_X), rd32(car + CAR_POS_Z)), (int)rd32(car + CAR_POS_X), (int)rd32(car + CAR_POS_Z), 0); }
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
  PushHistory_004E5938(P15_GridCell(rd32(car + CAR_POS_X), rd32(car + CAR_POS_Z)));
  if (P95_SeqMatch(&k_seqs[0]) != 0) P59_PickUp(2);
  if (P95_SeqMatch(&k_seqs[1]) != 0) P59_PickUp(2);
  if (P95_SeqMatch(&k_seqs[2]) != 0) P59_PickUp(8);
  if (yaw_rate < 0x12d) P98_M4A5C = 0;
  else if (P98_M4A5C == 0) { P98_M4A5C = 1; P98_M4464 = 0x46; }
  else if (P98_M4464 == 0) P59_PickUp(4);
  else P98_M4464--;
  if (yaw_rate < 0xfb) P98_M4A48 = 0;
  else if (P98_M4A48 == 0) { if ((keys & 0x20) != 0) { P98_M4A48 = 1; P98_M390C = 0x28; } }
  else if (P98_M390C == 0) P59_PickUp(3);
  else P98_M390C--;
  if (P59_S44CC > 0) P59_S44CC--;
  if (P59_S4790 > 0) P59_S4790--;
  if (P59_S3904 > 0) P59_S3904--;
  if (P98_M4468 > 0) P98_M4468--;
  int32_t hit = 0;
  if (P44_Rst_B31EA0 != 0 && P98_M4468 == 0) {
    hit = 1; P98_M4468 = 0x28; P98_M38F8 = damage;
    P12_Fn004E5982(0x11e, 0x96, 1);
    if (P42_ActionBound() == 0) SetFirstFree_004D6190(P62_Frame % 3 + 0xf000);
  }
  if (P98_M4468 > 0) P44_Rst_B31EA0 = 0;
  if (damage - P98_M38F8 > 0x1e && P98_M4468 == 0) {
    hit = 1; P98_M4468 = 0x28;
    P12_Fn004E5982(0x11f, 0x96, 1);
    if (P42_ActionBound() == 0) SetFirstFree_004D6190(P62_Frame % 3 + 0xf000);
  }
  if (P98_M4468 > 0) P98_M38F8 = damage;
  if (hit && P98_M4660 < 4) P98_M4660++;
  if (reversing && fwd_speed > 100) P98_M4780 = 1;
  if (yaw_rate < 0xc9 || P98_M4780 == 0) { P98_M4780 = 0; P98_M3580 = 0x28; }
  else if (P98_M3580 == 0) P59_PickUp(5);
  else P98_M3580--;
  int32_t fwd_speed_fx = rd32(car + CAR_FWD_SPEED);
  if (fwd_speed_fx < 0xaa001) { if ((keys & 1) == 0 || hit) P98_M48F4 = 0; }
  else { P98_M48F4 = 1; P98_M4664 = 0x28; }
  if (P98_M48F4 != 0) { if (P98_M4664 == 0) P59_PickUp(7); else P98_M4664--; }
  if (fwd_speed_fx > 0xb4000) P98_M4474++;
  if (hit || fwd_speed_fx < 0) P98_M4474 = 0;
  if (P98_M4474 > 5 && fwd_speed_fx < 0x14000) { P59_PickUp(6); P98_M4474 = 0; }
  if ((keys & 0x40) != 0 && fwd_speed > 0x32) P59_PickUp(0);
  if ((keys & 0x20) != 0 && fwd_speed > 0x32) P59_PickUp(1);
}
