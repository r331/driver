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
#include "mscript_ops.h"
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
#include "memrw.h"
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

/* сравнения If* 0x6b..0x70: 1 — пропустить следующую команду
   If* comparisons (MS_IFEQUAL..MS_IFGREATEROREQUAL, op 0..5): when the condition is FALSE, *c = 2 so the
   next command is skipped.  Only integer (type 3) and boolean (type 4) variables can be compared. */
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
/* Result codes of P146_ScriptCmd.  The caller (mission-script tick 004f472b, P127_ScriptTick) keeps
   executing commands in the same frame until it gets MS_RES_YIELD. */
#define MS_RES_DONE     0x0   /* command finished: continue with the next one this frame */
#define MS_RES_SOUND    0xb   /* sound/bank command (UPDATEBESTLAP, LOADSOUNDBANK, PLAYBANKEDSOUND): also continue */
#define MS_RES_YIELD    0xd   /* default: stop executing for this frame */

/* P146_ScriptCmd — Game.exe 004f8e0c (..004fb76a), cdecl.  Executes one compiled mission-script command.
   In:  cmd — the command: int32 words, cmd[0] = opcode (enum mscript_op, mscript_ops.h), then the
        arguments (cmd[1] = arg1, ...); string arguments are stored in place (e.g. cmd + 2).
   Out: result code (MS_RES_*; the original's local_14).  The script position P127_ScrPos advances by
        `step`: 1 = next command, 0 = run this command again next frame (waits), 2 = skip the next command
        (an If* whose condition is false).  GOTO / GOSUB / RETURN set P127_ScrPos themselves and return 0.
   Side effects: whatever the opcode does — targets P58_Objs, lamps, cops on/off (P56_B268), felony,
        messages, weather, cutscene camera points, script variables (P42_Vars), the GOSUB stack P146_GoSub.
   Errors in the script are reported to debug.log with the original messages.
   Note: the result constants above are named here only; the body still returns the literal values
   via `result`, exactly as the original. */
int32_t P146_ScriptCmd(void *cmd) {
  int32_t *p = (int32_t *)cmd;
  int32_t result = MS_RES_YIELD, step = 1;   /* step: how far P127_ScrPos moves after this command */
  uint8_t *rec = (uint8_t *)re_ptr((uint32_t)B84(0x00c812b8u));
  int32_t *mrk = (int32_t *)re_ptr(P113_MrkRec);
  int32_t arg1 = p[1];
  char buf[0x80];
  switch (p[0]) {
  case MS_CHECKPOINT:
    result = 0;
    P146_MsgPos(p[2], p[3]);
    if (rec != NULL) { wr32(rec + 8, rd32(rec + 8) & ~0x80); wr32(rec + 0x18, arg1); wr32(rec + 0x1c, 250000); }
    break;
  case MS_MISSIONEND:
    step = 0;
    set_c4(P14_00c810c4 | 0x8000);
    set_10a0(1);
    break;
  case MS_SET:
    result = 0;
    if (P42_Vars[arg1].type == 1) P59_VarSetString(arg1, (const char *)(p + 2));
    else SetTableValue_004F89B7(arg1, (uint32_t)p[2]);
    break;
  case MS_TRIGGEREVENT: result = 0; P112_ScriptRunId((uint16_t)arg1); break;
  case MS_PLAYSOUND: result = 0; MenuClick004F8ACC(arg1); break;
  case MS_RESETCHECKPOINTS: result = 0; if (rec != NULL) memset(rec, 0, 0x48); break;
  case MS_INITIALISERACE:
    result = 0;
    set_c4(3);
    if (rec != NULL) { wr32(rec + 8, 0x80); wr32(rec + 0x14, 1); wr32(rec + 0x10, 0x400); wr32(rec + 4, 1); }
    break;
  case MS_WAITFOROBJECTIVECOMPLETE:
    if (P14_00c810c4 != 0 && (P14_00c810c4 != 1 || rec == NULL || (rd32(rec + 8) & 0x80) == 0)) {
      int32_t done = P14_00c810c4 == 0x7fff;
      if (done) { set_c4(0); result = 0; }
      step = done;
    }
    break;
  case MS_TIMEPLAYER: result = 0; if (mrk != NULL) { mrk[0] = 0; mrk[1] = 0x8c; } break;
  case MS_COUNTDOWN: result = 0; if (mrk != NULL) ScriptSetWaitX50_004F5C58(mrk, arg1); break;
  case MS_STOPPLAYER: set_d118a8(1); break;
  case MS_RELEASEPLAYER: set_d118a8(0); break;
  case MS_INCREASE: result = 0; var_add(arg1, 1); break;
  case MS_DECREASE: result = 0; var_add(arg1, -1); break;
  case MS_ADD: result = 0; var_add(arg1, p[2]); break;
  case MS_SUB: result = 0; var_add(arg1, -p[2]); break;
  case MS_CHECKPOINTLOGO: result = 0; if (rec != NULL) { wr32(rec + 0x10, rd32(rec + 0x10) | 0x100); wr32(rec + 0xc, 0); } break;
  case MS_SPAWNCOPS: {
    result = 0;
    const int32_t *q = p + 2;
    felony_floor(arg1);
    for (int32_t n = arg1; n != 0; n--, q += 3) P119_TrafficParked(q[0], q[1], q[2]);
    break; }
  case MS_PLAYCUTSCENE: result = 0; break;
  case MS_INFORMPLAYER:
    result = 0;
    set_camdelay(arg1);
    P44_Copy4((uint8_t *)P56_Blk84 + 0xa8, p + 3, (uint32_t)p[2]);
    break;
  case MS_RACECOMPLETE:
    result = 0;
    B84(0x00c810c8u) = 0;
    set_c4(0x80f1);
    if (rec != NULL) wr32(rec + 0x10, rd32(rec + 0x10) & ~4);
    set_10a0(1);
    if (rec != NULL) for (int k = 0; k < 6; k++) { P125_MrkSave[k] = rd32(rec + 0x30 + k * 4); P56_Blk11[4 + k] = (uint32_t)P125_MrkSave[k]; }
    break;
  case MS_WAIT:
    if (B84(0x00c810d4u) == 0) B84(0x00c810d4u) = arg1 * 0x32;
    else if (--B84(0x00c810d4u) == 0) { result = 0; break; }
    step = 0;
    break;
  case MS_SETTARGET:
    result = 0;
    if (arg1 < 10) {
      tgt_w(arg1, 0, p[2]); tgt_w(arg1, 0x14, p[3]); tgt_w(arg1, 0x1c, p[4]);
      tgt_w(arg1, 0x24, 0); tgt_w(arg1, 0x28, 0); tgt_w(arg1, 0x2c, 0);
    } else P124_DebugLog("SetTarget: Illegal target index in mission script.");
    break;
  case MS_ENABLETARGET: result = 0; tgt_flag(arg1, 1, ~0u, "EnableTarget: Illegal target index in mission script."); break;
  case MS_DISABLETARGET: result = 0; tgt_flag(arg1, 0, ~1u, "DisableTarget: Illegal target index in mission script."); break;
  case MS_STOPTIMER:
    result = 0;
    if (MenuMode1271060 == 2) { if (rec != NULL) wr32(rec + 0x34, rd32(rec + 0x34) & ~8); }
    else if (mrk != NULL) mrk[1] &= ~8;
    break;
  case MS_CONTINUETIMER: result = 0; if (mrk != NULL && (mrk[1] & 4) != 0) mrk[1] |= 8; break;
  case MS_PLAY3DSOUND: result = 0; P97_SndStart((uint32_t)arg1, 0xc, (float)p[2], (float)p[3], (float)p[4]); break;
  case MS_MISSIONWINDOW: result = 0; B84(0x00c810dcu) = arg1; break;
  case MS_ENABLEWINDOW: result = 0; B84(0x00c810d8u) |= 1; break;
  case MS_DISABLEWINDOW: result = 0; B84(0x00c810d8u) &= ~1; break;
  case MS_SETMAXIMUMCOPS: result = 0; P62_Max = arg1; break;
  case MS_TARGETEVENT:
    result = 0;
    if (arg1 < 10) {
      if (p[2] == -1) tgt_w(arg1, 0x10, tgt_r(arg1, 0x10) & ~8);
      else {
        tgt_w(arg1, 0x10, tgt_r(arg1, 0x10) | 8); tgt_w(arg1, 0xc, p[2]);
        tgt_w(arg1, 0x24, 0); tgt_w(arg1, 0x28, 0); tgt_w(arg1, 0x2c, 0);
      }
    } else P124_DebugLog("TargetEvent: Illegal target index in mission script.");
    break;
  case MS_LAMPPOSITION: result = 0; if (arg1 < 5) { uint8_t *l = &P127_Lamp5[arg1 * 0x28]; wrf(l + 8, (float)p[2]); wrf(l + 0xc, (float)p[3]); wrf(l + 0x10, (float)p[4]); } break;
  case MS_LAMPCOLOR: result = 0; if (arg1 < 5) { uint8_t *l = &P127_Lamp5[arg1 * 0x28]; wr32(l + 0x18, p[2]); wr32(l + 0x1c, p[3]); wr32(l + 0x20, p[4]); } break;
  case MS_LAMPTYPE: result = 0; if (arg1 < 5) wr32(&P127_Lamp5[arg1 * 0x28], p[2]); break;
  case MS_LAMPRANGE: result = 0; if (arg1 < 5) wrf(&P127_Lamp5[arg1 * 0x28 + 4], (float)p[2]); break;
  case MS_ENABLELAMP: result = 0; if (arg1 < 5) P127_LampOn[arg1] = 1; break;
  case MS_DISABLELAMP: result = 0; if (arg1 < 5) P127_LampOn[arg1] = 0; break;
  case MS_NOLENSFLARE: result = 0; MenuVar575F30 = 0; P13_00575f30 = 0; G00575F30 = 0; break;
  case MS_COPS_OFF: result = 0; set_b268(0); break;
  case MS_COPS_ON: result = 0; set_b268(1); break;
  case MS_SETFAILEDSOUND: result = 0; P47_Slots[0] = arg1; break;
  case MS_SETPLAYERYROTATION: result = 0; P94_Heading = (int16_t)(arg1 & 0xfff); break;
  case MS_FORCEFELONYRATING: felony_floor(arg1); result = 0; break;
  case MS_ADDCIVCAR:
    result = 0;
    if (arg1 < 10) spawn_civ(arg1, p + 2, p[6], p[7]);
    else P124_DebugLog("Script Error: AddCivCar - Illegal index value supplied.\n");
    break;
  case MS_ENABLEPLAYERDAMAGE: result = 0; B84(0x00c810d8u) |= 4; break;
  case MS_DISABLEPLAYERDAMAGE: result = 0; B84(0x00c810d8u) &= ~4; break;
  case MS_TRIGGEREVENTAT: B84(0x00c810f4u) = p[2]; B84(0x00c810d8u) |= 8; B84(0x00c810f0u) = arg1 * 0x32; break;
  case MS_KILLTIMER: result = 0; if (mrk != NULL) mrk[1] = 0; break;
  case MS_ADDTOTIMER: result = 0; if (mrk != NULL) mrk[0] += arg1 * 0x32; break;
  case MS_SUBFROMTIMER: result = 0; if (mrk != NULL) mrk[0] += arg1 * -0x32; break;
  case MS_MCS_SETSTARTCOORD: result = 0; P123_TgtX = (float)arg1; P126_TgtY = (float)p[2]; P123_TgtZ = (float)p[3]; break;
  case MS_MCS_SETDOORAXIS: result = 0; P126_SpawnAxis = arg1; break;
  case MS_MCS_SETNUMBADGUYS: result = 0; P126_SpawnN = arg1; break;
  case MS_MCS_SETRUN: result = 0; P126_SpawnSide = 1; break;
  case MS_MCS_SETWALK: result = 0; P126_SpawnSide = 0; break;
  case MS_MCS_ACTIVATE: result = 0; P127_SpawnReq = 1; break;
  case MS_MCS_WAITFORSCENE: if (P98_C824A0 == 0 && P127_SpawnReq == 0) result = 0; else step = 0; break;
  case MS_MCS_SETSTARTHEIGHT: result = 0; P62_C82434 = arg1; P62_C82500 = -200 - arg1; break;
  case MS_MCS_DROPOFF: result = 0; P123_TgtMode = arg1; break;
  case MS_ADDCIVCARATREPLAY: {
    P11_00ba52d0 = fround(P101_GoalPos[0]);
    int32_t x = P11_00ba52d0;
    P11_00ba52d0 = fround(P101_GoalPos[2]);
    result = 0;
    spawn_civ(arg1, p + 2, x, P11_00ba52d0);
    break; }
  case MS_MCS_REPLAYCAROFFSET:
    result = 0;
    P123_PtX = P101_GoalPos[0] + i2f(P65_Ints[0x2c]);
    P126_PtY = P101_GoalPos[1];
    P126_TgtY = P101_GoalPos[1];
    P123_PtZ = P101_GoalPos[2] + i2f(P65_Ints[0x2e]);
    P123_TgtX = P123_PtX;
    P123_TgtZ = P123_PtZ;
    break;
  case 0x52: /* opcode 82 has no keyword in the table (MCS_USEREPLAYCARPOSITION compiles to 81); TODO(RE): unsure how 82 is produced */
    result = 0; P65_Ints[0x2c] = f2i((float)arg1); P65_Ints[0x2e] = f2i((float)p[2]); break;
  case MS_ENABLETARGETPULSE: result = 0; tgt_flag(arg1, 0, ~0x10u, "EnablePulse: Illegal target index in mission script."); break;
  case MS_DISABLETARGETPULSE: result = 0; tgt_flag(arg1, 0x10, ~0u, "DisablePulse: Illegal target index in mission script."); break;
  case MS_ENABLETARGETARROW: result = 0; tgt_flag(arg1, 0, ~0x20u, "EnableArrow: Illegal target index in mission script."); break;
  case MS_DISABLETARGETARROW: result = 0; tgt_flag(arg1, 0x20, ~0u, "DisableArrow: Illegal target index in mission script."); break;
  case MS_ENABLETARGETTRACER: result = 0; tgt_flag(arg1, 0, ~0x40u, "EnableTrace: Illegal target index in mission script."); break;
  case MS_DISABLETARGETTRACER: result = 0; tgt_flag(arg1, 0x40, ~0u, "DisableTrace: Illegal target index in mission script."); break;
  case MS_ENABLEDETECTION: result = 0; tgt_flag(arg1, 0, ~0x80u, "EnableDetection: Illegal target index in mission script."); break;
  case MS_DISABLEDETECTION: result = 0; tgt_flag(arg1, 0x80, ~0u, "DisableDetection: Illegal target index in mission script."); break;
  case MS_TARGETARROW:
    result = 0;
    if (arg1 < 10) { tgt_w(arg1, 0x24, p[2]); tgt_w(arg1, 0x28, p[3]); tgt_w(arg1, 0x2c, p[4]); }
    else P124_DebugLog("TargetArrow: Illegal target index in mission script.");
    break;
  case MS_LOADTRAIL: result = 0; P139_TrailLoad((const char *)(p + 2)); break;
  case MS_KILLEVENT: result = 0; P15_ListClearActiveByTag((uint32_t)arg1); break;
  case MS_CHOPPER:
    P53_Mrk[0] = (float)arg1;
    P113_MrkGround = p[2];
    P53_Mrk[1] = (float)P113_MrkGround;
    P53_Mrk[2] = (float)p[3];
    P42_AngBase = p[4];
    P42_AngX = (uint16_t)P42_AngBase; P53_Ang2702 = (int16_t)P42_AngBase;
    P113_MrkId = 0x7fffffff;
    P95_BDFA14 = 1;
    result = 0;
    break;
  case MS_CHOPPER_FORCE: P113_MrkFall = 1; result = 0; break;
  case MS_CHOPPER_START: P113_MrkId = arg1; result = 0; break;
  case MS_DISABLETAILMESSAGE: result = 0; tgt_flag(arg1, 0x400, ~0u, "ToggleTailMessage: Illegal target index in mission script."); break;
  case MS_ENABLETAILMESSAGE: result = 0; tgt_flag(arg1, 0, ~0x400u, "ToggleTailMessage: Illegal target index in mission script."); break;
  case MS_ADDDASHMESSAGE: result = 0; P125_AddDashMessage((const char *)(p + 3), arg1); break;
  case MS_SHOWDASHMESSAGE:
    result = 0;
    if (mrk != NULL && (mrk[1] & 4) != 0) {
      int32_t t = mrk[0];
      const char *s = (const char *)P58_FindChunk(t);
      if (s != NULL) { set_camdelay(t * 0x32); P44_Copy4((uint8_t *)P56_Blk84 + 0xa8, s, (uint32_t)strlen(s)); }
    }
    break;
  case MS_CLEARDASHDATA: result = 0; P58_FreeLists(); break;
  case MS_GOTO: {
    int32_t to = P65_FindByName((char *)(p + 2), (p65_tab_t *)&P99_ScrNames);
    if (to != -1) { P127_ScrPos = to; return 0; }
    P124_DebugLog("Script error in GOTO: Unknown label.");
    break; }
  case MS_IFEQUAL: case MS_IFNOTEQUAL: case MS_IFLESSTHAN: case MS_IFGREATERTHAN: case MS_IFLESSOREQUAL: case MS_IFGREATEROREQUAL:
    result = 0;
    var_cmp(p[0] == MS_IFEQUAL ? 0 : p[0] == MS_IFNOTEQUAL ? 1 : p[0] == MS_IFLESSTHAN ? 2 : p[0] == MS_IFGREATERTHAN ? 3 : p[0] == MS_IFLESSOREQUAL ? 4 : 5, arg1, p[2], &step);
    break;
  case MS_GOSUB:
    result = 0;
    if (P138_C80F7C < 100) {
      int32_t to = P65_FindByName((char *)(p + 2), (p65_tab_t *)&P99_ScrNames);
      if (to != -1) { P146_GoSub[P138_C80F7C] = P127_ScrPos + 1; P127_ScrPos = to; P138_C80F7C++; return 0; }
      P124_DebugLog("Script error, GoSub: Unknown label.");
    } else P124_DebugLog("Script error, GoSub: Out of Stack space.");
    break;
  case MS_RETURN:
    result = 0;
    if (0 < P138_C80F7C) { P127_ScrPos = P146_GoSub[P138_C80F7C - 1]; P138_C80F7C--; return 0; }
    P124_DebugLog("Script error, Return without GoSub!");
    break;
  case MS_LOG: result = 0; P124_DebugLog((const char *)(p + 2)); break;
  case MS_UPDATEBESTLAP: { result = 0xb; int32_t v = P147_ScoreRec(); P109_C81268 = v; B84(0x00c81268u) = v; break; }
  case MS_LOADSOUNDBANK: result = 0xb; snprintf(buf, sizeof buf, "BANK%d.DSS", arg1); P77_LoadBank(buf, 0xf000); break;
  case MS_PLAYBANKEDSOUND: result = 0xb; TryStartTrack_004D611B((uint32_t)(arg1 + 0xf000)); break;
  case MS_WAITUNTIL: {
    int32_t *t = &B84(0x00c810d4u);
    int ok = 0;
    if (mrk != NULL && (*t == 0 || *t == mrk[0])) {
      *t = arg1 * 0x32;
      ok = ((mrk[1] & 0x80) != 0 && *t <= mrk[0]) || ((mrk[1] & 8) != 0 && mrk[0] <= *t);
    }
    if (ok) { *t = 0; result = 0; } else step = 0;
    break; }
  case MS_MCS_SETENDCOORD: result = 0; P123_PtX = (float)arg1; P126_PtY = (float)p[2]; P123_PtZ = (float)p[3]; break;
  case MS_MCS_SETDOORCOORD:
    result = 0;
    P123_PtX = (float)arg1; P126_PtY = (float)p[2]; P123_PtZ = (float)p[3];
    P123_TgtX = P123_PtX; P126_TgtY = P126_PtY; P123_TgtZ = P123_PtZ;
    break;
  case MS_CREATEGANGCAR: {
    int32_t v = P99_TrafficAhead();
    if (v == -1) step = 0;
    else { result = 0; B84(0x00c8112cu) = arg1; B84(0x00c81128u) = v; }
    break; }
  case MS_INFORMPLAYERBYID:
    if (p[2] != -1) {
      result = 0;
      set_camdelay(arg1 * 0x32);
      const char *s = (const char *)re_ptr(P98_MisStr[p[2]]);
      if (s != NULL) strcpy((char *)P56_Blk84 + 0xa8, s);
    }
    break;
  case MS_ADDDASHMESSAGEBYID: result = 0; if (p[2] != -1) P125_AddDashMessage((const char *)re_ptr(P98_MisStr[p[2]]), arg1); break;
  case MS_FAILEDMESSAGEID: result = var_msg("FAILEDMESSAGE", arg1); break;
  case MS_WINDOWMESSAGEID: result = var_msg("WINDOWMESSAGE", arg1); break;
  case MS_LOSETAILMESSAGEID: result = var_msg("LOSETAILMESSAGE", arg1); break;
  case MS_SMASHEDMESSAGEID: result = var_msg("SMASHEDMESSAGE", arg1); break;
  case MS_OUTOFRANGEMESSAGEID: result = var_msg("OUTOFRANGEMESSAGE", arg1); break;
  case MS_CARGOTAWAYMESSAGEID: result = var_msg("CARGOTAWAYMESSAGE", arg1); break;
  case MS_OPPONENTBARID: result = var_msg("OPPONENTBAR", arg1); break;
  case MS_DAMAGEBARID: result = var_msg("DAMAGEBAR", arg1); break;
  case MS_FELONYBARID: result = var_msg("FELONYBAR", arg1); break;
  case MS_ENABLEMODEL: case MS_DISABLEMODEL: {
    result = 0;
    const char *nm = (const char *)(p + 2);
    int32_t m = P20_FindNameNoCase(nm);
    if (m == -1) {
      if (p[0] == MS_ENABLEMODEL) {
        if (arg1 < 0x5a) snprintf(buf, sizeof buf, "EnableModel: Unknown model name provided (%s), function failed.", nm);
        else snprintf(buf, sizeof buf, "EnableModel: Unknown model name provided, function failed.");
      } else {
        if (arg1 < 0x5a) snprintf(buf, sizeof buf, "DisableModel: Unknown model name provided (%s), function failed.", nm);
        else snprintf(buf, sizeof buf, "DisableModel: Unknown model name provided, function failed.");
      }
      P124_DebugLog(buf);
    } else ExchangeTable00522F2A(m, p[0] == MS_ENABLEMODEL ? 1 : 0);
    break; }
  case MS_STARTGHOSTLAP: result = 0; P103_C54D04 = 1; break;
  case MS_ENDGHOSTLAP: result = 0; P103_C54FC4 = 1; break;
  case MS_MODELBONUS: {
    result = 0;
    int32_t m = P20_FindNameNoCase((const char *)(p + 3));
    if (m == -1) P124_DebugLog("ModelBonus: Error: Could not find specified model!");
    else P125_DropTime[m] = arg1;
    break; }
  case MS_RESETMAP: P55_ResetSel(); break;
  case MS_MAXSPEEDMESSAGEID: result = var_msg("MAXSPEEDMESSAGE", arg1); break;
  case MS_MODELTARGETRANGE: result = 0; B84(0x00c81138u) = arg1; B84(0x00c81134u) = p[2]; break;
  /* Note: as ported, SETCAMERASTART fills P134_Cine1 and SETCAMERAEND fills P134_Cine0, while P134_CamCine
     interpolates Cine0 -> Cine1 (t = 0 at Cine0).  TODO(RE): unsure whether the P134 names or the order are swapped. */
  case MS_MCS_SETCAMERASTART: result = 0; cine_point(P134_Cine1, &P134_ScaleE, p + 1); break;
  case MS_MCS_SETCAMERAEND: result = 0; cine_point(P134_Cine0, &P134_ScaleB, p + 1); break;
  case MS_CUTTOCAR: result = 0; P127_SpawnRst = 1; break;
  case MS_DRAW321GO: result = 0; set_d14ee(1, 0); set_c4(3); break;
  case MS_DRAWFINISHED: result = 0; set_d14ee(1, 5); break;
  default: break;
  }
  P127_ScrPos += step;
  return result;
}
