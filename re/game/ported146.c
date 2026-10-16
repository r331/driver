/* v1.91: ported146 — см. ported146.h. Восстановлено из Game.exe (Ghidra out/Game_decomp.c + ассемблер), cdecl (ret без операнда).
   004f8e0c — команда скрипта миссии: cmd[0] — код (0..0x95, переход по таблице 004fb76b), далее аргументы int32 / строки
     на месте. Возврат local_14: 0xd по умолчанию, 0 — выполнена, 0xb — звук/банк/музыка (0x74..0x76); номер команды 00c80eec
     увеличивается на local_c (1; 0 — ждать; 2 — пропуск следующей команды при ложном условии If*), GOTO/GoSub/Return
     ставят номер сами и выходят с 0. Реальная граница функции — 004f8e0c..004fb76a (ret), 0x295f байт; таблица переходов
     004fb76b..004fb9c2 (в functions.csv было 104). Сравнения 00d11a5c — знаковые (jge, 004f91f6/004f9957).
   Записи: 00c812b8 — адрес записи 0x48 (P69_MsgBlk), 00c812bc — адрес записи таймера {время, флаги} (P113_MrkRec), обе
     переводятся re_ptr; цели 00c80ce0 + i·0x34 (10) — P58_Objs (для цели 0 — ещё P115_TgtOn/P115_Tgt и P65_Ints, по адресу);
     переменные скрипта 0056dc10 (0x30: type +0x20, адрес +0x24) — P42_Vars, значение по re_ptr(addr) (native: NULL — пропуск);
     фонари 00c818c0 + i·0x28 (5) — P127_Lamp5; стек GoSub 00c81300 — новая GAME_VAR P146_GoSub (100).
   Псевдонимы (work/alias.py, work/own191.py): 00c810c4 — P14_00c810c4 и P56_Blk84[1]; 00c810d0 — P99_CamDelay; 00c81268 —
     P109_C81268; 00575f30 — MenuVar575F30/P13_00575f30/G00575F30; 00d118a8, 00d11a5c, 00d14ee0/e4 — P14_* и G2_/D_;
     0112b268 — P47_Flag/P56_B268; 01271070 — P125_MrkSave и P56_Blk11[4..9]; 012710a0 — P8_012710a0 и P56_Blk11[16];
     00d02702 — P42_AngX/P53_Ang2702. Строки ошибок — литералы .data 0056f468..00570090. .rdata 00546a00 = 3.86f.
   0x74: 00401c62 → 00503ddf (найдена только через thunk) — перенесена в v1.92 как P147_ScoreRec. */
#include "ported146.h"
#include "unported.h"
#include "ported147.h"
#include "reptr.h"
#include "cartab.h"
#include "menustate.h"
#include "smallfuncs.h"
#include "smallfuncs2.h"
#include "uihandlers4.h"
#include "ported4.h"
#include "ported6.h"
#include "ported8.h"
#include "ported10.h"
#include "ported11.h"
#include "ported13.h"
#include "ported14.h"
#include "ported15.h"
#include "ported20.h"
#include "ported42.h"
#include "ported44.h"
#include "ported47.h"
#include "ported53.h"
#include "ported55.h"
#include "ported56.h"
#include "ported58.h"
#include "ported59.h"
#include "ported62.h"
#include "ported65.h"
#include "ported68.h"
#include "ported69.h"
#include "ported77.h"
#include "ported94.h"
#include "ported95.h"
#include "ported97.h"
#include "ported98.h"
#include "ported99.h"
#include "ported101.h"
#include "ported103.h"
#include "ported109.h"
#include "ported112.h"
#include "ported113.h"
#include "ported115.h"
#include "ported119.h"
#include "ported123.h"
#include "ported124.h"
#include "ported125.h"
#include "ported126.h"
#include "ported127.h"
#include "ported134.h"
#include "ported138.h"
#include "ported139.h"
#include <math.h>
#include <stdio.h>
#include <string.h>

#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P146_GoSub")
#undef P146_GoSub
#pragma push_macro("P146_GoSub") /*gvi*/
#undef P146_GoSub /*gvi*/
p146_gosub_t P146_GoSub;
#pragma pop_macro("P146_GoSub") /*gvi*/
#pragma pop_macro("P146_GoSub")
#endif

#define B84(a)   (*(int32_t *)&P56_Blk84[((a) - 0x00c810c0u) / 4])   /* поля внутри P56_Blk84 */
static int32_t fround(float v) { return (int32_t)lrintf(v); }   /* fistp */
static int32_t rd32(const uint8_t *p) { int32_t v; memcpy(&v, p, 4); return v; }
static void    wr32(uint8_t *p, int32_t v) { memcpy(p, &v, 4); }
static void    wrf(uint8_t *p, float v) { memcpy(p, &v, 4); }
static float   i2f(int32_t v) { float f; memcpy(&f, &v, 4); return f; }
static int32_t f2i(float f) { int32_t v; memcpy(&v, &f, 4); return v; }

/* ---- 004a37d9 ---- */
void P146_MsgPos(int32_t a, int32_t b) {
  uint8_t *m = (uint8_t *)P69_MsgBlk;
  wr32(m + 0x20, a);
  wr32(m + 0x28, b);
  wr32(m + 0x14, 2);
  wr32(m + 0x10, rd32(m + 0x10) | 0x200);
}

static void set_c4(int32_t v) { P14_00c810c4 = v; B84(0x00c810c4u) = v; }
static void set_camdelay(int32_t v) { P99_CamDelay = v; B84(0x00c810d0u) = v; }
static void set_d11a5c(int32_t v) { P14_00d11a5c = (uint32_t)v; G2_00D11A5C = v; }
static void set_d118a8(int32_t v) { P14_00d118a8 = v; G2_00D118A8 = v; }
static void set_d14ee(int32_t e4, int32_t e0) { P14_00d14ee4 = e4; D_00d14ee4 = e4; P14_00d14ee0 = e0; D_00d14ee0 = e0; }
static void set_b268(int32_t v) { P47_Flag = v; P56_B268 = v; }
static void set_10a0(int32_t v) { P8_012710a0 = v; P56_Blk11[0x10] = (uint32_t)v; }

/* цель i (0x34 байта от 00c80ce0): все native-псевдонимы адреса */
static void tgt_w(int32_t i, uint32_t off, int32_t v) {
  wr32(&P58_Objs[i][off], v);
  uint32_t a = 0x00c80ce0u + (uint32_t)i * 0x34u + off;
  if (a == 0x00c80cf0u) P115_TgtOn = v;
  else if (a >= 0x00c80cf4u && a < 0x00c80d04u) P115_Tgt[(a - 0x00c80cf4u) / 4] = v;
  if (a < 0x00c80d00u) P65_Ints[(a - 0x00c80c00u) / 4] = v;
}
static int32_t tgt_r(int32_t i, uint32_t off) { return rd32(&P58_Objs[i][off]); }
static void tgt_flag(int32_t i, uint32_t orv, uint32_t andv, const char *err) {
  if (i < 10) tgt_w(i, 0x10, (int32_t)(((uint32_t)tgt_r(i, 0x10) & andv) | orv));
  else P124_DebugLog(err);
}

static int32_t *var_ptr(int32_t i) { return (int32_t *)re_ptr(P42_Vars[i].addr); }
static void var_add(int32_t i, int32_t d) { int32_t *p = var_ptr(i); if (p != NULL) *p += d; }

/* сравнения If* 0x6b..0x70: 1 — пропустить следующую команду */
static int32_t var_cmp(int32_t op, int32_t var, int32_t v, int32_t *c) {
  static const char *const nm[6] = { "IfEqual", "IfNotEqual", "IfLessThan", "IfGreaterThan", "IfLessOrEqual", "IfGreaterOrEqual" };
  static const char *const kd[3] = { "string", "floating point", "boolean" };
  char msg[0x80];
  int32_t t = P42_Vars[var].type;
  if (t == 1 || t == 2 || (t == 4 && v != 0 && v != 1)) {
    snprintf(msg, sizeof msg, "%s: Type mismatch, cannot convert %s variable for integer comparison.", nm[op], kd[t == 4 ? 2 : t - 1]);
    P124_DebugLog(msg);
    return 0;
  }
  if (t != 3 && t != 4) return 0;
  int32_t *p = var_ptr(var);
  if (p == NULL) return 0;
  int32_t x = *p, skip = 0;
  switch (op) {
  case 0: skip = x != v; break;
  case 1: skip = x == v; break;
  case 2: skip = v <= x; break;
  case 3: skip = x <= v; break;
  case 4: skip = v < x; break;
  default: skip = x < v; break;
  }
  if (skip) *c = 2;
  return 0;
}

/* сообщения 0x7d..0x85, 0x8f: строка миссии в переменную скрипта по имени */
static int32_t var_msg(const char *name, int32_t s) {
  if (s == -1) return 0xd;
  int32_t v = P42_FindVar(name);
  if (v != -1) P99_VarSetStr((uint8_t *)&P42_Vars[v], (const char *)re_ptr(P98_MisStr[s]));
  return 0;
}

static void felony_floor(int32_t lvl) {
  if (lvl != 0 && MenuOptBDFA48 == 0) {
    int32_t m = (lvl - 1) * 0x355 + 0x2aa;
    if (G2_00D11A5C < m) set_d11a5c(m);
    P68_D11A48 = P95_B87E3C + 1;
  }
}

static void cine_point(float *dst, float *scale, const int32_t *p) {
  int32_t sp = p[4];
  dst[0] = (float)p[1];
  dst[1] = -(float)p[2];
  dst[2] = (float)p[3];
  if (p[0] == 1) { dst[0] += (float)P59_PosX; dst[1] += (float)P59_PosY; dst[2] += (float)P59_PosZ; }
  *scale = (sp < 0x32 || 200 < sp) ? 386.0f : 3.86f * (float)sp;   /* .rdata 00546a00 */
  P127_SpawnCnt++;
}

static void spawn_civ(int32_t i, const int32_t *a, int32_t x, int32_t z) {
  P103_TrafficSpawn((int8_t)a[0], a[1], (int8_t)a[2], a[3], x, z);
  tgt_w(i, 4, B84(0x00c81110u));
  tgt_w(i, 8, a[0]);
  tgt_w(i, 0x10, 0x100);
}

/* ---- 004f8e0c ---- */
int32_t P146_ScriptCmd(void *cmd) {
  int32_t *p = (int32_t *)cmd;
  int32_t r = 0xd, c = 1;
  uint8_t *rec = (uint8_t *)re_ptr((uint32_t)B84(0x00c812b8u));
  int32_t *mrk = (int32_t *)re_ptr(P113_MrkRec);
  int32_t a1 = p[1];
  char buf[0x80];
  switch (p[0]) {
  case 0:
    r = 0;
    P146_MsgPos(p[2], p[3]);
    if (rec != NULL) { wr32(rec + 8, rd32(rec + 8) & ~0x80); wr32(rec + 0x18, a1); wr32(rec + 0x1c, 250000); }
    break;
  case 1:
    c = 0;
    set_c4(P14_00c810c4 | 0x8000);
    set_10a0(1);
    break;
  case 2:
    r = 0;
    if (P42_Vars[a1].type == 1) P59_VarSetString(a1, (const char *)(p + 2));
    else SetTableValue_004F89B7(a1, (uint32_t)p[2]);
    break;
  case 3: r = 0; P112_ScriptRunId((uint16_t)a1); break;
  case 4: r = 0; MenuClick004F8ACC(a1); break;
  case 5: r = 0; if (rec != NULL) memset(rec, 0, 0x48); break;
  case 6:
    r = 0;
    set_c4(3);
    if (rec != NULL) { wr32(rec + 8, 0x80); wr32(rec + 0x14, 1); wr32(rec + 0x10, 0x400); wr32(rec + 4, 1); }
    break;
  case 7:
    if (P14_00c810c4 != 0 && (P14_00c810c4 != 1 || rec == NULL || (rd32(rec + 8) & 0x80) == 0)) {
      int32_t done = P14_00c810c4 == 0x7fff;
      if (done) { set_c4(0); r = 0; }
      c = done;
    }
    break;
  case 8: r = 0; if (mrk != NULL) { mrk[0] = 0; mrk[1] = 0x8c; } break;
  case 9: r = 0; if (mrk != NULL) ScriptSetWaitX50_004F5C58(mrk, a1); break;
  case 10: set_d118a8(1); break;
  case 0xb: set_d118a8(0); break;
  case 0xc: r = 0; var_add(a1, 1); break;
  case 0xe: r = 0; var_add(a1, -1); break;
  case 0x10: r = 0; var_add(a1, p[2]); break;
  case 0x11: r = 0; var_add(a1, -p[2]); break;
  case 0x12: r = 0; if (rec != NULL) { wr32(rec + 0x10, rd32(rec + 0x10) | 0x100); wr32(rec + 0xc, 0); } break;
  case 0x14: {
    r = 0;
    const int32_t *q = p + 2;
    felony_floor(a1);
    for (int32_t n = a1; n != 0; n--, q += 3) P119_TrafficParked(q[0], q[1], q[2]);
    break; }
  case 0x15: r = 0; break;
  case 0x16:
    r = 0;
    set_camdelay(a1);
    P44_Copy4((uint8_t *)P56_Blk84 + 0xa8, p + 3, (uint32_t)p[2]);
    break;
  case 0x17:
    r = 0;
    B84(0x00c810c8u) = 0;
    set_c4(0x80f1);
    if (rec != NULL) wr32(rec + 0x10, rd32(rec + 0x10) & ~4);
    set_10a0(1);
    if (rec != NULL) for (int k = 0; k < 6; k++) { P125_MrkSave[k] = rd32(rec + 0x30 + k * 4); P56_Blk11[4 + k] = (uint32_t)P125_MrkSave[k]; }
    break;
  case 0x18:
    if (B84(0x00c810d4u) == 0) B84(0x00c810d4u) = a1 * 0x32;
    else if (--B84(0x00c810d4u) == 0) { r = 0; break; }
    c = 0;
    break;
  case 0x19:
    r = 0;
    if (a1 < 10) {
      tgt_w(a1, 0, p[2]); tgt_w(a1, 0x14, p[3]); tgt_w(a1, 0x1c, p[4]);
      tgt_w(a1, 0x24, 0); tgt_w(a1, 0x28, 0); tgt_w(a1, 0x2c, 0);
    } else P124_DebugLog("SetTarget: Illegal target index in mission script.");
    break;
  case 0x1a: r = 0; tgt_flag(a1, 1, ~0u, "EnableTarget: Illegal target index in mission script."); break;
  case 0x1b: r = 0; tgt_flag(a1, 0, ~1u, "DisableTarget: Illegal target index in mission script."); break;
  case 0x1c:
    r = 0;
    if (MenuMode1271060 == 2) { if (rec != NULL) wr32(rec + 0x34, rd32(rec + 0x34) & ~8); }
    else if (mrk != NULL) mrk[1] &= ~8;
    break;
  case 0x1d: r = 0; if (mrk != NULL && (mrk[1] & 4) != 0) mrk[1] |= 8; break;
  case 0x21: r = 0; P97_SndStart((uint32_t)a1, 0xc, (float)p[2], (float)p[3], (float)p[4]); break;
  case 0x23: r = 0; B84(0x00c810dcu) = a1; break;
  case 0x24: r = 0; B84(0x00c810d8u) |= 1; break;
  case 0x25: r = 0; B84(0x00c810d8u) &= ~1; break;
  case 0x26: r = 0; P62_Max = a1; break;
  case 0x29:
    r = 0;
    if (a1 < 10) {
      if (p[2] == -1) tgt_w(a1, 0x10, tgt_r(a1, 0x10) & ~8);
      else {
        tgt_w(a1, 0x10, tgt_r(a1, 0x10) | 8); tgt_w(a1, 0xc, p[2]);
        tgt_w(a1, 0x24, 0); tgt_w(a1, 0x28, 0); tgt_w(a1, 0x2c, 0);
      }
    } else P124_DebugLog("TargetEvent: Illegal target index in mission script.");
    break;
  case 0x2a: r = 0; if (a1 < 5) { uint8_t *l = &P127_Lamp5[a1 * 0x28]; wrf(l + 8, (float)p[2]); wrf(l + 0xc, (float)p[3]); wrf(l + 0x10, (float)p[4]); } break;
  case 0x2b: r = 0; if (a1 < 5) { uint8_t *l = &P127_Lamp5[a1 * 0x28]; wr32(l + 0x18, p[2]); wr32(l + 0x1c, p[3]); wr32(l + 0x20, p[4]); } break;
  case 0x2c: r = 0; if (a1 < 5) wr32(&P127_Lamp5[a1 * 0x28], p[2]); break;
  case 0x2d: r = 0; if (a1 < 5) wrf(&P127_Lamp5[a1 * 0x28 + 4], (float)p[2]); break;
  case 0x2e: r = 0; if (a1 < 5) P127_LampOn[a1] = 1; break;
  case 0x2f: r = 0; if (a1 < 5) P127_LampOn[a1] = 0; break;
  case 0x30: r = 0; MenuVar575F30 = 0; P13_00575f30 = 0; G00575F30 = 0; break;
  case 0x31: r = 0; set_b268(0); break;
  case 0x32: r = 0; set_b268(1); break;
  case 0x33: r = 0; P47_Slots[0] = a1; break;
  case 0x34: r = 0; P94_Heading = (int16_t)(a1 & 0xfff); break;
  case 0x35: felony_floor(a1); r = 0; break;
  case 0x36:
    r = 0;
    if (a1 < 10) spawn_civ(a1, p + 2, p[6], p[7]);
    else P124_DebugLog("Script Error: AddCivCar - Illegal index value supplied.\n");
    break;
  case 0x37: r = 0; B84(0x00c810d8u) |= 4; break;
  case 0x38: r = 0; B84(0x00c810d8u) &= ~4; break;
  case 0x39: B84(0x00c810f4u) = p[2]; B84(0x00c810d8u) |= 8; B84(0x00c810f0u) = a1 * 0x32; break;
  case 0x3a: r = 0; if (mrk != NULL) mrk[1] = 0; break;
  case 0x3b: r = 0; if (mrk != NULL) mrk[0] += a1 * 0x32; break;
  case 0x3c: r = 0; if (mrk != NULL) mrk[0] += a1 * -0x32; break;
  case 0x45: r = 0; P123_TgtX = (float)a1; P126_TgtY = (float)p[2]; P123_TgtZ = (float)p[3]; break;
  case 0x46: r = 0; P126_SpawnAxis = a1; break;
  case 0x47: r = 0; P126_SpawnN = a1; break;
  case 0x48: r = 0; P126_SpawnSide = 1; break;
  case 0x49: r = 0; P126_SpawnSide = 0; break;
  case 0x4a: r = 0; P127_SpawnReq = 1; break;
  case 0x4b: if (P98_C824A0 == 0 && P127_SpawnReq == 0) r = 0; else c = 0; break;
  case 0x4c: r = 0; P62_C82434 = a1; P62_C82500 = -200 - a1; break;
  case 0x4f: r = 0; P123_TgtMode = a1; break;
  case 0x50: {
    P11_00ba52d0 = fround(P101_GoalPos[0]);
    int32_t x = P11_00ba52d0;
    P11_00ba52d0 = fround(P101_GoalPos[2]);
    r = 0;
    spawn_civ(a1, p + 2, x, P11_00ba52d0);
    break; }
  case 0x51:
    r = 0;
    P123_PtX = P101_GoalPos[0] + i2f(P65_Ints[0x2c]);
    P126_PtY = P101_GoalPos[1];
    P126_TgtY = P101_GoalPos[1];
    P123_PtZ = P101_GoalPos[2] + i2f(P65_Ints[0x2e]);
    P123_TgtX = P123_PtX;
    P123_TgtZ = P123_PtZ;
    break;
  case 0x52: r = 0; P65_Ints[0x2c] = f2i((float)a1); P65_Ints[0x2e] = f2i((float)p[2]); break;
  case 0x55: r = 0; tgt_flag(a1, 0, ~0x10u, "EnablePulse: Illegal target index in mission script."); break;
  case 0x56: r = 0; tgt_flag(a1, 0x10, ~0u, "DisablePulse: Illegal target index in mission script."); break;
  case 0x57: r = 0; tgt_flag(a1, 0, ~0x20u, "EnableArrow: Illegal target index in mission script."); break;
  case 0x58: r = 0; tgt_flag(a1, 0x20, ~0u, "DisableArrow: Illegal target index in mission script."); break;
  case 0x59: r = 0; tgt_flag(a1, 0, ~0x40u, "EnableTrace: Illegal target index in mission script."); break;
  case 0x5a: r = 0; tgt_flag(a1, 0x40, ~0u, "DisableTrace: Illegal target index in mission script."); break;
  case 0x5b: r = 0; tgt_flag(a1, 0, ~0x80u, "EnableDetection: Illegal target index in mission script."); break;
  case 0x5c: r = 0; tgt_flag(a1, 0x80, ~0u, "DisableDetection: Illegal target index in mission script."); break;
  case 0x5d:
    r = 0;
    if (a1 < 10) { tgt_w(a1, 0x24, p[2]); tgt_w(a1, 0x28, p[3]); tgt_w(a1, 0x2c, p[4]); }
    else P124_DebugLog("TargetArrow: Illegal target index in mission script.");
    break;
  case 0x5e: r = 0; P139_TrailLoad((const char *)(p + 2)); break;
  case 0x60: r = 0; P15_ListClearActiveByTag((uint32_t)a1); break;
  case 0x61:
    P53_Mrk[0] = (float)a1;
    P113_MrkGround = p[2];
    P53_Mrk[1] = (float)P113_MrkGround;
    P53_Mrk[2] = (float)p[3];
    P42_AngBase = p[4];
    P42_AngX = (uint16_t)P42_AngBase; P53_Ang2702 = (int16_t)P42_AngBase;
    P113_MrkId = 0x7fffffff;
    P95_BDFA14 = 1;
    r = 0;
    break;
  case 0x62: P113_MrkFall = 1; r = 0; break;
  case 99: P113_MrkId = a1; r = 0; break;
  case 100: r = 0; tgt_flag(a1, 0x400, ~0u, "ToggleTailMessage: Illegal target index in mission script."); break;
  case 0x65: r = 0; tgt_flag(a1, 0, ~0x400u, "ToggleTailMessage: Illegal target index in mission script."); break;
  case 0x66: r = 0; P125_AddDashMessage((const char *)(p + 3), a1); break;
  case 0x67:
    r = 0;
    if (mrk != NULL && (mrk[1] & 4) != 0) {
      int32_t t = mrk[0];
      const char *s = (const char *)P58_FindChunk(t);
      if (s != NULL) { set_camdelay(t * 0x32); P44_Copy4((uint8_t *)P56_Blk84 + 0xa8, s, (uint32_t)strlen(s)); }
    }
    break;
  case 0x68: r = 0; P58_FreeLists(); break;
  case 0x6a: {
    int32_t to = P65_FindByName((char *)(p + 2), (p65_tab_t *)&P99_ScrNames);
    if (to != -1) { P127_ScrPos = to; return 0; }
    P124_DebugLog("Script error in GOTO: Unknown label.");
    break; }
  case 0x6b: case 0x6c: case 0x6d: case 0x6e: case 0x6f: case 0x70:
    r = 0;
    var_cmp(p[0] == 0x6b ? 0 : p[0] == 0x6c ? 1 : p[0] == 0x6d ? 2 : p[0] == 0x6e ? 3 : p[0] == 0x6f ? 4 : 5, a1, p[2], &c);
    break;
  case 0x71:
    r = 0;
    if (P138_C80F7C < 100) {
      int32_t to = P65_FindByName((char *)(p + 2), (p65_tab_t *)&P99_ScrNames);
      if (to != -1) { P146_GoSub[P138_C80F7C] = P127_ScrPos + 1; P127_ScrPos = to; P138_C80F7C++; return 0; }
      P124_DebugLog("Script error, GoSub: Unknown label.");
    } else P124_DebugLog("Script error, GoSub: Out of Stack space.");
    break;
  case 0x72:
    r = 0;
    if (0 < P138_C80F7C) { P127_ScrPos = P146_GoSub[P138_C80F7C - 1]; P138_C80F7C--; return 0; }
    P124_DebugLog("Script error, Return without GoSub!");
    break;
  case 0x73: r = 0; P124_DebugLog((const char *)(p + 2)); break;
  case 0x74: { r = 0xb; int32_t v = P147_ScoreRec(); P109_C81268 = v; B84(0x00c81268u) = v; break; }
  case 0x75: r = 0xb; snprintf(buf, sizeof buf, "BANK%d.DSS", a1); P77_LoadBank(buf, 0xf000); break;
  case 0x76: r = 0xb; TryStartTrack_004D611B((uint32_t)(a1 + 0xf000)); break;
  case 0x77: {
    int32_t *t = &B84(0x00c810d4u);
    int ok = 0;
    if (mrk != NULL && (*t == 0 || *t == mrk[0])) {
      *t = a1 * 0x32;
      ok = ((mrk[1] & 0x80) != 0 && *t <= mrk[0]) || ((mrk[1] & 8) != 0 && mrk[0] <= *t);
    }
    if (ok) { *t = 0; r = 0; } else c = 0;
    break; }
  case 0x78: r = 0; P123_PtX = (float)a1; P126_PtY = (float)p[2]; P123_PtZ = (float)p[3]; break;
  case 0x79:
    r = 0;
    P123_PtX = (float)a1; P126_PtY = (float)p[2]; P123_PtZ = (float)p[3];
    P123_TgtX = P123_PtX; P126_TgtY = P126_PtY; P123_TgtZ = P123_PtZ;
    break;
  case 0x7a: {
    int32_t v = P99_TrafficAhead();
    if (v == -1) c = 0;
    else { r = 0; B84(0x00c8112cu) = a1; B84(0x00c81128u) = v; }
    break; }
  case 0x7b:
    if (p[2] != -1) {
      r = 0;
      set_camdelay(a1 * 0x32);
      const char *s = (const char *)re_ptr(P98_MisStr[p[2]]);
      if (s != NULL) strcpy((char *)P56_Blk84 + 0xa8, s);
    }
    break;
  case 0x7c: r = 0; if (p[2] != -1) P125_AddDashMessage((const char *)re_ptr(P98_MisStr[p[2]]), a1); break;
  case 0x7d: r = var_msg("FAILEDMESSAGE", a1); break;
  case 0x7e: r = var_msg("WINDOWMESSAGE", a1); break;
  case 0x7f: r = var_msg("LOSETAILMESSAGE", a1); break;
  case 0x80: r = var_msg("SMASHEDMESSAGE", a1); break;
  case 0x81: r = var_msg("OUTOFRANGEMESSAGE", a1); break;
  case 0x82: r = var_msg("CARGOTAWAYMESSAGE", a1); break;
  case 0x83: r = var_msg("OPPONENTBAR", a1); break;
  case 0x84: r = var_msg("DAMAGEBAR", a1); break;
  case 0x85: r = var_msg("FELONYBAR", a1); break;
  case 0x89: case 0x8a: {
    r = 0;
    const char *nm = (const char *)(p + 2);
    int32_t m = P20_FindNameNoCase(nm);
    if (m == -1) {
      if (p[0] == 0x89) {
        if (a1 < 0x5a) snprintf(buf, sizeof buf, "EnableModel: Unknown model name provided (%s), function failed.", nm);
        else snprintf(buf, sizeof buf, "EnableModel: Unknown model name provided, function failed.");
      } else {
        if (a1 < 0x5a) snprintf(buf, sizeof buf, "DisableModel: Unknown model name provided (%s), function failed.", nm);
        else snprintf(buf, sizeof buf, "DisableModel: Unknown model name provided, function failed.");
      }
      P124_DebugLog(buf);
    } else ExchangeTable00522F2A(m, p[0] == 0x89 ? 1 : 0);
    break; }
  case 0x8b: r = 0; P103_C54D04 = 1; break;
  case 0x8c: r = 0; P103_C54FC4 = 1; break;
  case 0x8d: {
    r = 0;
    int32_t m = P20_FindNameNoCase((const char *)(p + 3));
    if (m == -1) P124_DebugLog("ModelBonus: Error: Could not find specified model!");
    else P125_DropTime[m] = a1;
    break; }
  case 0x8e: P55_ResetSel(); break;
  case 0x8f: r = var_msg("MAXSPEEDMESSAGE", a1); break;
  case 0x90: r = 0; B84(0x00c81138u) = a1; B84(0x00c81134u) = p[2]; break;
  case 0x91: r = 0; cine_point(P134_Cine1, &P134_ScaleE, p + 1); break;
  case 0x92: r = 0; cine_point(P134_Cine0, &P134_ScaleB, p + 1); break;
  case 0x93: r = 0; P127_SpawnRst = 1; break;
  case 0x94: r = 0; set_d14ee(1, 0); set_c4(3); break;
  case 0x95: r = 0; set_d14ee(1, 5); break;
  default: break;
  }
  P127_ScrPos += c;
  return r;
}
