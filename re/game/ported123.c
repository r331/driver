/* ported123.c — falling debris, object shadows, car glows, a camera helper, the side-point distance test
   and the event-script compiler (English overview; original notes follow).  All cdecl. */
/* v1.68: ported123 — восстановлено из Game.exe. Все функции cdecl (ret без операнда; work/rets.py), 004a45eb — тоже cdecl.
   004b9e9f — шаг объекта A с гравитацией (005461e0 = 6), на дороге: тип 1 — пыль 004b955c и возврат в пул, тип 0 — отскок ×0.5;
   00502e76 — пятна под объектами P58_Objs (флаг 1, не 0x20/0x108) в видимых клетках P82_LightGrid, размер 2·P102_HudF4 + 150;
   004b3fb1 — очередь пятен фар (P123_GlowCars) с цветом P14_00d17b18·120/256, затем grDepthBiasLevel(0) и 01270e80(2);
   0049df91 — камера в позицию машины, выше на 400 (00546104), углы P44_Atan2;
   004f154e — точки игрока ±200 по курсу (00546158/00546200), ближняя к цели 00c82510/18, расстояние 00c823dc;
   004a45eb — строка события: команды 1..4 (запись 0x24), DO/LOOP 0x13..0x15, прочие — P99_CmdAppend в объект 0x60;
   004a3fa6 — блоки событий чанка, MULTIEVENT_START с MODELS/PALETTES/VELOCITIES (P99_EvA/B/C) и P99_EventAdd. */
#include "ported123.h"
#include "ported122.h"
#include "cartab.h"
#include "unported.h"
#include "ported125.h"   /* P125_ObjABurst (004b955c) */
#include "smallfuncs.h"
#include "smallfuncs2.h"
#include "ported6.h"
#include "ported7.h"
#include "ported11.h"
#include "ported12.h"
#include "ported14.h"
#include "ported21.h"
#include "ported26.h"
#include "ported33.h"
#include "ported43.h"
#include "ported44.h"
#include "ported51.h"
#include "ported58.h"
#include "ported59.h"
#include "ported68.h"
#include "ported74.h"
#include "ported76.h"
#include "ported82.h"
#include "ported94.h"
#include "ported95.h"
#include "ported98.h"
#include "ported99.h"
#include "ported100.h"
#include "ported102.h"
#include "ported120.h"
#include "ported121.h"
#include "uihandlers3.h"
#include "icontab.h"
#include "p99_data.h"
#include "reptr.h"
#include <math.h>
#include <string.h>

#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P123_GlowN")
#undef P123_GlowN
#pragma push_macro("P123_GlowN") /*gvi*/
#undef P123_GlowN /*gvi*/
int32_t P123_GlowN;
#pragma pop_macro("P123_GlowN") /*gvi*/
#pragma pop_macro("P123_GlowN")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P123_GlowCars")
#undef P123_GlowCars
#pragma push_macro("P123_GlowCars") /*gvi*/
#undef P123_GlowCars /*gvi*/
p123_glowcars_t P123_GlowCars;
#pragma pop_macro("P123_GlowCars") /*gvi*/
#pragma pop_macro("P123_GlowCars")
#endif
GAME_VAR_DEF(uint8_t *, P123_EvObjCur, 0x00b1ff68)
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P123_TgtX")
#undef P123_TgtX
#pragma push_macro("P123_TgtX") /*gvi*/
#undef P123_TgtX /*gvi*/
float P123_TgtX;
#pragma pop_macro("P123_TgtX") /*gvi*/
#pragma pop_macro("P123_TgtX")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P123_TgtZ")
#undef P123_TgtZ
#pragma push_macro("P123_TgtZ") /*gvi*/
#undef P123_TgtZ /*gvi*/
float P123_TgtZ;
#pragma pop_macro("P123_TgtZ") /*gvi*/
#pragma pop_macro("P123_TgtZ")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P123_PtX")
#undef P123_PtX
#pragma push_macro("P123_PtX") /*gvi*/
#undef P123_PtX /*gvi*/
float P123_PtX;
#pragma pop_macro("P123_PtX") /*gvi*/
#pragma pop_macro("P123_PtX")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P123_PtZ")
#undef P123_PtZ
#pragma push_macro("P123_PtZ") /*gvi*/
#undef P123_PtZ /*gvi*/
float P123_PtZ;
#pragma pop_macro("P123_PtZ") /*gvi*/
#pragma pop_macro("P123_PtZ")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P123_SideX")
#undef P123_SideX
#pragma push_macro("P123_SideX") /*gvi*/
#undef P123_SideX /*gvi*/
float P123_SideX;
#pragma pop_macro("P123_SideX") /*gvi*/
#pragma pop_macro("P123_SideX")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P123_SideZ")
#undef P123_SideZ
#pragma push_macro("P123_SideZ") /*gvi*/
#undef P123_SideZ /*gvi*/
float P123_SideZ;
#pragma pop_macro("P123_SideZ") /*gvi*/
#pragma pop_macro("P123_SideZ")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P123_TgtMode")
#undef P123_TgtMode
#pragma push_macro("P123_TgtMode") /*gvi*/
#undef P123_TgtMode /*gvi*/
int32_t P123_TgtMode;
#pragma pop_macro("P123_TgtMode") /*gvi*/
#pragma pop_macro("P123_TgtMode")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P123_TgtDist")
#undef P123_TgtDist
#pragma push_macro("P123_TgtDist") /*gvi*/
#undef P123_TgtDist /*gvi*/
int32_t P123_TgtDist;
#pragma pop_macro("P123_TgtDist") /*gvi*/
#pragma pop_macro("P123_TgtDist")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P123_SideB")
#undef P123_SideB
#pragma push_macro("P123_SideB") /*gvi*/
#undef P123_SideB /*gvi*/
uint8_t P123_SideB;
#pragma pop_macro("P123_SideB") /*gvi*/
#pragma pop_macro("P123_SideB")
#endif

#include "memrw.h"
/* rd16 / wr16 / wrf / camf / set_camf — local helpers: unaligned int16 / float access; camf/set_camf read and
   write the parser's float argument slots P68_CamF[] (stored as int32 words). */
static int16_t rd16(const void *p) { int16_t v; memcpy(&v, p, 2); return v; }
static void wr16(void *p, int16_t v) { memcpy(p, &v, 2); }
static void wrf(void *p, float v) { memcpy(p, &v, 4); }
static float camf(int i) { float v; memcpy(&v, &P68_CamF[i], 4); return v; }
static void set_camf(int i, float v) { memcpy(&P68_CamF[i], &v, 4); }

#ifdef RE_HOOK_BUILD
#  define P123_STD __attribute__((stdcall))
#else
#  define P123_STD
#endif
/* depth_bias — native helper: grDepthBiasLevel(v) through the loaded Glide DLL (01270e20 in Game.exe). */
static void depth_bias(int32_t v) {   /* 01270e20 grDepthBiasLevel */
  for (int i = 0; i < P33_GlideCount(); i++)
    if (strcmp(P33_GlideName(i), "_grDepthBiasLevel@4") == 0) {
      void (P123_STD *f)(int32_t) = (void (P123_STD *)(int32_t))P33_GlideProc(i);
      if (f != NULL) f(v);
      return;
    }
}

/* ---- 004b9e9f ---- */
/* P123_ObjAFall — Game.exe 004b9e9f.  One step of a falling debris object o (0x78 bytes): keeps two previous
   positions (+0x20, +0x40), integrates velocity (+0x30..) with gravity 6 per tick.  On reaching the road:
   kind (+0x50) 1 spawns dust (004b955c) and returns the object to its pool, kind 0 bounces (vy * -0.5),
   other kinds lose their remaining life.  Life +0x58 decreases by +0x5c; the countdown +0x64 frees it at 0. */
void P123_ObjAFall(uint8_t *o) {
  for (int k = 0; k < 4; k++) { wr32(o + 0x40 + k * 4, rd32(o + 0x20 + k * 4)); wr32(o + 0x20 + k * 4, rd32(o + k * 4)); }
  wrf(o + 0, rdf(o + 0) + rdf(o + 0x30));
  wrf(o + 4, rdf(o + 4) + rdf(o + 0x34));
  wrf(o + 8, rdf(o + 8) + rdf(o + 0x38));
  wrf(o + 0x34, rdf(o + 0x34) + 6.0f);                 /* 005461e0: gravity (y grows downward) */
  float ground_y = (float)-P100_RoadHeightF((const float *)o);
  if (ground_y < rdf(o + 4)) {
    int32_t kind = rd32(o + 0x50);
    if (kind == 1) {
      int32_t pos[3], vel[3] = { 0, -5, 0 };
      P11_00ba52d0 = (int32_t)lrintf(rdf(o + 0)); pos[0] = P11_00ba52d0;
      P11_00ba52d0 = (int32_t)lrintf(ground_y);          pos[1] = P11_00ba52d0;
      P11_00ba52d0 = (int32_t)lrintf(rdf(o + 8)); pos[2] = P11_00ba52d0;
      P125_ObjABurst(pos, vel, 5, 0);
      wr32(o + 0x68, 0);
      PoolPush004AC702((uint16_t)rd16(o + 0x6c));
    } else if (kind == 0) {
      wrf(o + 4, ground_y);
      wrf(o + 0x34, -(rdf(o + 0x34) * 0.5f));            /* 00546068 */
    } else wr32(o + 0x58, 0);
  }
  wr32(o + 0x58, rd32(o + 0x58) - rd32(o + 0x5c));
  if (rd32(o + 0x58) < 1) { wr32(o + 0x58, 0); wr16(o + 0x64, 1); }
  wr16(o + 0x64, (int16_t)(rd16(o + 0x64) - 1));
  if (rd16(o + 0x64) == 0) { wr32(o + 0x68, 0); PoolPush004AC702((uint16_t)rd16(o + 0x6c)); }
}

/* ---- 00502e76 ---- */
/* P123_ObjShadows — Game.exe 00502e76.  Draws a round shadow (white spot record, size 2 * P102_HudF4 + 150)
   under each of the 10 objects P58_Objs that are active (flag 1), not hidden (0x20 / 0x108) and in a lit
   visible map cell.  Skipped in replay/demo (00b87ea0) or without the spot icon. */
void P123_ObjShadows(void) {
  if (P94_IconRec == 0 || G6_00B87EA0 != 0) return;
  float white = 255.0f;
  for (int k = 0; k < 3; k++) { P98_IconCol[k] = white; wrf(P122_SpotRec + 0x38 + k * 4, white); }   /* 010fc9d8 — псевдонимы */
  if (P26_FxD != 0 && P98_GrD40 != NULL) P98_GrD40(0);
  P12_Fn00426580(0);
  for (int k = 0; k < 10; k++) {
    const uint8_t *o = P58_Objs[k];
    uint32_t flags = (uint32_t)rd32(o + 0x10);
    if ((flags & 1) == 0 || (flags & 0x20) != 0) continue;
    int32_t x = rd32(o + 0x14), y = rd32(o + 0x18), z = rd32(o + 0x1c);
    float pos[3] = { (float)(x + rd32(o + 0x24)), (float)y, (float)(z + rd32(o + 0x2c)) };
    if (P76_InBox(pos, P82_LightGrid, P82_CellCX, P82_CellCY) != 0 && (flags & 0x108) == 0) {
      pos[0] = (float)x; pos[2] = (float)z;
      P122_SpotShadowF(pos, P102_HudF4 * 2 + 0x96);
    }
  }
  if (P26_FxD != 0 && P98_GrD40 != NULL) P98_GrD40(2);
}

/* ---- 004b3fb1 ---- */
/* P123_CarGlows — Game.exe 004b3fb1.  Draws the queued headlight glows (P123_GlowCars, count P123_GlowN)
   with brightness P14_00d17b18 * 120 / 256, then resets the depth bias and the queue. */
void P123_CarGlows(void) {
  if (P95_PoolIcon == 0) { P123_GlowN = 0; return; }
  int32_t level = (int32_t)P14_00d17b18 * 0x78 >> 8;
  float col = (float)level;
  if (P26_FxD != 0 && P98_GrD40 != NULL) P98_GrD40(0);
  P12_Fn00426580(0);
  int32_t old_mode = DrvSetMode0042655A(0);
  while (P123_GlowN != 0) {
    P123_GlowN--;
    for (int k = 0; k < 3; k++) wrf(P122_GlowRec + 0x38 + k * 4, col);
    if (P123_GlowN >= 0 && P123_GlowN < 65) P122_CarGlow(P123_GlowCars[P123_GlowN]);
  }
  depth_bias(0);
  P123_GlowN = 0;
  if (FnPtr01270E80) FnPtr01270E80(2);
  DrvSetMode0042655A(old_mode);
  if (P26_FxD != 0 && P98_GrD40 != NULL) P98_GrD40(2);
}

/* ---- 0049df91 ---- */
/* P123_CamAtCar — Game.exe 0049df91.  Puts the camera 400 units above car `car` (y grows downward, hence
   -400) and points it at the car: pitch/yaw from P44_Atan2 on the offset scaled to 8 fractional bits
   (scaled down by 4 until the horizontal distance is <= 64000).  Roll 0.  Rebuilds the view transform. */
void P123_CamAtCar(int32_t car) {
  if (car < 0 || car > 0x41) return;
  const p99_car_t *c = &P99_Cars[car];
  float vx = (float)c->pos[0], vy = (float)c->pos[1] - 400.0f, vz = (float)c->pos[2];
  P59_VX = vx; P59_VY = vy; P59_VZ = vz;
  P44_CamX = vx; P44_CamY = vy; P44_CamZ = vz;          /* 00b1c270.. — псевдонимы */
  float dx = (float)c->pos[0] - vx, dy = vy + (float)c->pos[1], dz = (float)c->pos[2] - vz;
  float dist_xz = (float)sqrt((double)(dz * dz + dx * dx));
  P11_00ba52d0 = (int32_t)lrintf(dist_xz);  int32_t dist_fx = P11_00ba52d0 << 8;
  P11_00ba52d0 = (int32_t)lrintf(dx); int32_t bx = P11_00ba52d0 << 8;
  P11_00ba52d0 = (int32_t)lrintf(dy); int32_t by = P11_00ba52d0 << 8;
  P11_00ba52d0 = (int32_t)lrintf(dz); int32_t bz = P11_00ba52d0 << 8;
  for (; 64000 < dist_fx; dist_fx /= 4) { bx /= 4; by /= 4; bz /= 4; }
  P59_AngA = (uint16_t)((uint32_t)(P44_Atan2(dist_fx, by) - 0x400) & 0xfff);
  P59_AngB = (uint16_t)((uint32_t)-P44_Atan2(bx, bz) & 0xfff);
  P59_AngC = 0;
  InitXform_005263FE();
}

/* ---- 004f154e ---- */
/* P123_SideDist — Game.exe 004f154e.  Takes the two points 200 units to the left and right of the player
   (perpendicular to the heading P94_Heading), picks the one nearer the target (P123_TgtX/Z) into
   P123_SideX/Z (P123_SideB = 1 for the right one) and stores the distance in P123_TgtDist (rounded).
   In target mode 2 the distance is from point P123_PtX/Z instead. */
void P123_SideDist(void) {
  uint32_t ang = (uint32_t)(-(int32_t)P94_Heading) & 0xfff;
  float cos_a = P43_Sin[0x400 + ang], sin_a = P43_Sin[ang];
  float px = (float)P59_PosX, pz = (float)P59_PosZ;
  float x0 = -200.0f * cos_a + px, x1 = 200.0f * cos_a + px, z0 = -200.0f * sin_a + pz, z1 = 200.0f * sin_a + pz;
  float ax = x0 - P123_TgtX, bx = x1 - P123_TgtX, az = z0 - P123_TgtZ, bz = z1 - P123_TgtZ;
  float d0 = (float)sqrt((double)(az * az + ax * ax)), d1 = (float)sqrt((double)(bz * bz + bx * bx)), d = d1;
  P123_SideB = (uint8_t)(d1 <= d0);
  P123_SideX = x1; P123_SideZ = z1;
  if (!P123_SideB) { P123_SideX = x0; P123_SideZ = z0; d = d0; }
  P11_00ba52d0 = (int32_t)lrintf(d);
  P123_TgtDist = P11_00ba52d0;
  if (P123_TgtMode == 2) {
    float ex = P123_PtX - P123_TgtX, ez = P123_PtZ - P123_TgtZ;
    P11_00ba52d0 = (int32_t)lrintf((float)sqrt((double)(ez * ez + ex * ex)));
    P123_TgtDist = P11_00ba52d0;
  }
  P11_00ba52d0 = P123_TgtDist;
}

/* ---- 004a45eb ---- */
static const uint16_t k_cmdsz123[] = P99_CMDSZ_INIT;   /* .data 00551b32 */
/* Event-script command codes handled specially below (others are appended to the current object).
   Names follow the parser's own error messages; TODO(RE): exact keywords of 4 and 0x32 not checked. */
enum {
  EV_CMD_OBJECT  = 4,      /* starts a new 0x60-byte event object ("new model") */
  EV_CMD_DO      = 0x13,
  EV_CMD_LOOP    = 0x14,   /* LOOP back to the matching DO */
  EV_CMD_LOOP_N  = 0x15,   /* LOOP form with a count (copies the argument into two counters) */
  EV_CMD_SKIP    = 0x32    /* line yields nothing */
};
/* cmdsz — local helper: encoded size of event command c (table .data 00551b32), 0 if out of range. */
static uint16_t cmdsz(uint16_t c) { return c < sizeof k_cmdsz123 / sizeof k_cmdsz123[0] ? k_cmdsz123[c] : 0; }
/* P123_EvLine — Game.exe 004a45eb, cdecl.  Compiles one line of an event block into event `evaddr`
   (Game.exe addresses).  Commands 1..3 set event fields (1: radius^2 and two floats, 2: flag 4 and a
   grid cell index, 3: flag 8 and an id); EV_CMD_OBJECT allocates a new event object (linked at +0x58);
   DO / LOOP track the loop body size; everything else is appended to the current object (P99_CmdAppend),
   command 9 normalising its vector argument first.  Returns the address of the parsed word.
   Native: stops instead of writing through NULL when an allocation failed. */
uint32_t P123_EvLine(uint32_t text, uint32_t evaddr) {
  const uint8_t *word = SkipToIdentStart_004A596B((const uint8_t *)re_ptr(text));
  uint8_t *event = (uint8_t *)re_ptr(evaddr);
  uint32_t ret = re_addr(word);
  if (word == NULL || event == NULL) return ret;
  uint16_t cmd = P121_ParseCamLine((char *)word);
  if (cmd == EV_CMD_SKIP) return ret;
  if (cmd < EV_CMD_OBJECT) {
    if (cmd == 1) { float f = camf(3); wrf(event + 0x10, f * f); wrf(event + 0x14, camf(2)); wrf(event + 0x18, camf(1)); }
    else if (cmd == 2) { wr16(event, (int16_t)(rd16(event) | 4)); wr32(event + 0xc, (int32_t)((uint32_t)P68_CamI1 * (uint32_t)P21_GridDiv + P68_CamI0)); }
    else if (cmd == 3) { wr16(event, (int16_t)(rd16(event) | 8)); wr16(event + 6, (int16_t)P68_CamI0); P99_EvId = P68_CamI0; }
    else P26_ErrorInLine("Unknown Command in script!");
    return ret;
  }
  if (cmd == EV_CMD_OBJECT) {
    if (P122_Ev240 != 0) P26_ErrorInLine("DO without LOOP!");
    uint16_t id = P68_CamI0;
    uint8_t *obj = (uint8_t *)P98_DebugMalloc(0x60, "D:\\Driver\\Game\\compiler.c", 0x281);
    if (rd32(event + 0x1c) == 0) {
      if (obj == NULL) P26_ErrorInLine("Not enough memory for\nnew model!");
      else { re_wr_ptr(event + 0x1c, obj); P123_EvObjCur = obj; }
    } else if (obj == NULL) P26_ErrorInLine("Not enough memory for\nnew model!");
    else { if (P123_EvObjCur != NULL) re_wr_ptr(P123_EvObjCur + 0x58, obj); P123_EvObjCur = obj; }
    if (P123_EvObjCur == NULL) return ret;                 /* оригинал писал бы по нулевому адресу */
    memset(P123_EvObjCur, 0, 0x60);
    wr16(P123_EvObjCur + 0x4a, (int16_t)id);
    wr16(P123_EvObjCur + 0x40, -1);
    P99_EvObj = P123_EvObjCur;
    P122_Ev24C++;
    P99_CmdAppend(EV_CMD_OBJECT, P123_EvObjCur);
    return ret;
  }
  if (P122_Ev240 != 0) P122_Ev118 += cmdsz(cmd);
  switch (cmd) {
  case 5: case 6: case 7: case 8: case 10: case 0xb: case 0xc: case 0xd: case 0xf: case 0x10: case 0x11: case 0x12:
  case 0x16: case 0x17: case 0x1a: case 0x1b: case 0x1c: case 0x1d: case 0x1e: case 0x1f: case 0x20:
    if (P123_EvObjCur) P99_CmdAppend(cmd, P123_EvObjCur);
    break;
  case 9: {
    float l = (float)sqrt((double)(camf(0) * camf(0) + camf(1) * camf(1) + camf(2) * camf(2)));
    set_camf(2, camf(2) / l); set_camf(1, camf(1) / l); set_camf(0, camf(0) / l);
    if (P123_EvObjCur) P99_CmdAppend(cmd, P123_EvObjCur);
    break; }
  case 0xe:
    P68_CamI1 = P68_CamI0;
    if (P123_EvObjCur) P99_CmdAppend(cmd, P123_EvObjCur);
    break;
  case EV_CMD_DO:
    if (P122_Ev240 != 0) P26_ErrorInLine("Cannot have embedded DO!");
    P122_Ev240 = 1; P122_Ev118 = 0;
    break;
  case EV_CMD_LOOP:
    if (P122_Ev240 == 0) P26_ErrorInLine("LOOP without DO!");
    P68_CamI0 = (uint16_t)((int16_t)P122_Ev118 - (int16_t)cmdsz(EV_CMD_LOOP) + 2);   /* jump distance back to the DO */
    if (P123_EvObjCur) P99_CmdAppend(cmd, P123_EvObjCur);
    P122_Ev240 = 0;
    break;
  case EV_CMD_LOOP_N:
    if (P122_Ev240 == 0) P26_ErrorInLine("LOOP without DO!");
    P68_CamI1 = P68_CamI0; P68_CamI2 = P68_CamI0;
    P68_CamI0 = (uint16_t)((int16_t)P122_Ev118 + 6 - (int16_t)cmdsz(EV_CMD_LOOP_N));
    if (P123_EvObjCur) P99_CmdAppend(cmd, P123_EvObjCur);
    P122_Ev240 = 0;
    break;
  default: break;
  }
  return ret;
}

/* ---- 004a3fa6 ---- */
/* next_line — local helper: start of the first word on the next line, or NULL. */
static char *next_line(char *p) { p = SkipLine004A59C6(p); return p ? (char *)SkipToIdentStart_004A596B((const uint8_t *)p) : NULL; }
/* parse_list — local helper: if the line starts with `word`, allocates n int16 values and parses them.
   Returns 0 on a parse/allocation error, 1 otherwise (also when the word is absent). */
static int parse_list(char **pp, const char *word, int32_t skip, uint8_t **dst, uint32_t n, int32_t line) {
  if (P51_PrefixMatch(*pp, word) != 1) return 1;
  *dst = (uint8_t *)P98_DebugMalloc((int32_t)(n << 1), "D:\\Driver\\Game\\compiler.c", line);
  if (*dst == NULL) { P26_ErrorInLine("8 Out of Memory"); return 0; }
  *pp = P74_ParseShorts(*pp + skip, (uint16_t *)*dst, (int32_t)n);
  return *pp != NULL;
}
/* P123_EventsChunk — Game.exe 004a3fa6.  Parses all EVENT_START / MULTIEVENT_START blocks of a chunk up to
   CHUNK_END.  A MULTIEVENT_START n block carries MODELS / PALETTES / VELOCITIES lists of n values; the
   event is compiled once and then duplicated for i = 1..n-1 (P99_EventAdd) with consecutive ids. */
void P123_EventsChunk(char *p) {
  for (;;) {
    int32_t multi = 0;
    for (;;) {
      if (p == NULL) return;
      if (P51_PrefixMatch(p, "EVENT_START") != 0) break;
      multi = P51_PrefixMatch(p, "MULTIEVENT_START");
      if (multi != 0) break;
      if (P51_PrefixMatch(p, "CHUNK_END") == 1) return;
      p = next_line(p);
    }
    P122_Ev24C = 0;
    if (multi == 0) {
      p = next_line(p);
      if (p == NULL) return;
      p = P122_EventsParse(p);
    } else {
      for (p += 0x10; *p == ' ' || *p == '\t'; p++) {}
      P120_ParseCamInt(&p, 0, 0);
      uint32_t count = P68_CamI0;
      p = next_line(p);
      if (p == NULL) return;
      if (!parse_list(&p, "MODELS", 6, &P99_EvA, count, 0x176)) return;
      p = (char *)SkipToIdentStart_004A596B((const uint8_t *)p);
      if (!parse_list(&p, "PALETTES", 8, &P99_EvB, count, 0x188)) return;
      p = (char *)SkipToIdentStart_004A596B((const uint8_t *)p);
      if (!parse_list(&p, "VELOCITIES", 10, &P99_EvC, count, 0x19a)) return;
      p = (char *)SkipToIdentStart_004A596B((const uint8_t *)p);
      p = P122_EventsParse(p);
      if (P99_EvObj != NULL && P99_EvA != NULL) wr16(P99_EvObj + 0x4a, rd16(P99_EvA));
      for (int32_t i = 1; i < (int32_t)count; i++) { P99_EvId++; P99_EventAdd(i); }
      if (P99_EvA != NULL) { P98_DebugFree(P99_EvA); P99_EvA = NULL; }
      if (P99_EvB != NULL) { P98_DebugFree(P99_EvB); P99_EvB = NULL; }
      if (P99_EvC != NULL) { P98_DebugFree(P99_EvC); P99_EvC = NULL; }
    }
    if (p == NULL) return;
    p = next_line(p);
  }
}
