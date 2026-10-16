/* v1.84: ported139 — см. ported139.h.
   004f4596 — компиляция скрипта миссии: обнуление 00c810c0 (0x210, вместе с native-псевдонимами), 00c818a0 (0x18), 011342a0 (0x48),
     00c818c0 (200), 00c80f80 (0x14); 00c812b8 ← адрес 011342a0, 00c812bc ← адрес 00c818a0; 004f638d, 004f892a; строка 0x400
     (004d8db4, MScript.c:0x149) — иначе 3; файл "rt" — иначе 5; по строкам fgets → 004f621d (≠ 0 и ≠ 10 — закрыть и вернуть код),
     счётчик строк 00c80c54; конец файла — 4.
   004fbbfc — трейл: лог «Attempting to read…», старые данные 00c80c50 освобождаются (00c81108/00c8110c = 0); "rb", n = (размер − 4) / 0xc
     записей 0x14 {номер, x, y, z, 0} (MScript.c:0x1431), 00c80cc0 = 0, 01271070/7c/80/84 = 0, +0x18 четырёх записей 00c81500 = 0, 00c80bec = 0.
   004f8b0a — метка скрипта: новый массив (n + 1) адресов, копия старого, старый освобождается; запись 8 {адрес имени (strcpy + strupr), val}.
   004aaf3a — grColorCombine(3,1,0,1,0) при 01270c34 ≠ 4, grAlphaBlendFunction(4,4,0,0) при 0125f3e4 ≠ 3; 0042655a(0) на время обхода
     списка 010ffb40 (+0x74 — следующий) с выбором по первому флагу +0x68: 4/0x20000/0x40000/0x80/0x100/0x20/0x40/8/0x8000/0x1000;
     01137354 ← 01137324.
   00519647 — 00c54ee0 (0x88) из переменных игры (раскладка как у 00517d58), запись ReplayData\User\$TEMP$.CFG "wb".
   00519408 — 00c4d660 ← 00d118c0; при 00b5a894: 00519647, 00d1187c = 0x10100000, 00518d32(00b5a898), без 00b5a850 — PADS (User\$TEMP$
     или Chase\%s по 00b87eac; бит 31 00c54d08 при 00b31e30), PINGS погони; освобождение 00b5a8bc и 5 буферов 00c4d720; сброс 00c4d70c,
     00b87eac, 00b87eb0, 00c54b00.
   0040fa60 / 00410c30 — меню клавиш A/B: общий цикл (флаг варианта): опрос пунктов (0040c8f1 или 00418675 при 00b87eec), выход — проверка
     уникальности клавиш 004107b9/00411b09; режим ввода клавиши — Esc (004e383a(1)) или 0040f0fb/0040f09c (A: ≥ 0, B: > 0) → байт по адресу
     005fe764/005fe788, мигание байта +4 пункта 0054c030/0054c350 каждые 10 кадров; обработчик пункта из таблицы (×0x10) с 0 или 2.
     B при выходе копирует 0054b7c0 (5 слов) в 00d04d00.
   0041b1c0 — DATA\MLADDER.DML "r": обнуление буферов MLADDER, строки 0041c7ad → 0041b8ac до конца файла; запись-терминатор
     {8, 0, 0, 0}, 01271040/48 ← 005ff368, 01271044 ← 005fef38, 0127104c/50 = 0.
   Отступления native: 004f4596/0041b1c0 — области 00c818a0/011342a0/005ff368/005fef38 регистрируются в re_ptr один раз (адреса Game.exe);
     004f8b0a — массив/запись/имя — синтетические адреса re_ptr_register_dyn, освобождение снимает регистрацию; 0040fa60/00410c30 — таблицы
     0054c1e0/0054c530 и пункты 0054c030/0054c350 читаются через re_ptr/re_fn (нет области — обработчик/мигание пропускаются);
     00519408 — буферы 00c4d720 — uint32-адреса (re_ptr + re_ptr_unregister). */
#include "ported139.h"
#include "ported141.h"
#include <string.h>
#include <stdio.h>
#include <ctype.h>
#include "crt.h"
#include "reptr.h"
#include "cartab.h"
#include "unported.h"
#include "menuselect.h"
#include "menustate.h"
#include "uihandlers.h"
#include "uihandlers3.h"
#include "widgets.h"
#include "ported4.h"
#include "ported5.h"
#include "ported6.h"
#include "ported7.h"
#include "ported8.h"
#include "ported11.h"
#include "ported12.h"
#include "ported13.h"
#include "ported14.h"
#include "ported19.h"
#include "ported26.h"
#include "ported31.h"
#include "ported36.h"
#include "ported45.h"
#include "ported47.h"
#include "ported51.h"
#include "ported52.h"
#include "ported54.h"
#include "ported55.h"
#include "ported56.h"
#include "ported57.h"
#include "ported58.h"
#include "ported59.h"
#include "ported62.h"
#include "ported65.h"
#include "ported66.h"
#include "ported68.h"
#include "ported69.h"
#include "ported71.h"
#include "ported74.h"
#include "ported85.h"
#include "ported95.h"
#include "ported96.h"
#include "ported97.h"
#include "ported98.h"
#include "ported99.h"
#include "ported100.h"
#include "ported102.h"
#include "ported103.h"
#include "ported108.h"
#include "ported109.h"
#include "ported110.h"
#include "ported111.h"
#include "ported113.h"
#include "ported114.h"
#include "ported119.h"
#include "ported124.h"
#include "ported125.h"
#include "ported127.h"
#include "ported131.h"
#include "ported135.h"
#include "ported138.h"

GAME_VAR_DEF(p139_u6_t, P139_C818A0, 0x00c818a0)
GAME_VAR_DEF(int32_t, P139_LineNo, 0x00c80c54)
GAME_VAR_DEF(int32_t, P139_KeyStA, 0x005fe75c)
GAME_VAR_DEF(int32_t, P139_KeyPrA, 0x005fe760)
GAME_VAR_DEF(int32_t, P139_BlinkA, 0x005fe76c)
GAME_VAR_DEF(int32_t, P139_KeyStB, 0x005fe780)
GAME_VAR_DEF(int32_t, P139_KeyPrB, 0x005fe784)
GAME_VAR_DEF(int32_t, P139_BlinkB, 0x005fe794)
GAME_VAR_DEF(p139_b1000_t, P139_Ladder, 0x005ff368)
GAME_VAR_DEF(p139_b400_t, P139_LadStr, 0x005fef38)
GAME_VAR_DEF(p139_u4_t, P139_LadA, 0x005ff358)
GAME_VAR_DEF(p139_u4_t, P139_LadB, 0x005ff348)
GAME_VAR_DEF(p139_u4_t, P139_LadC, 0x0060037c)
GAME_VAR_DEF(p139_u4_t, P139_LadD, 0x005ff338)
GAME_VAR_DEF(p139_u4_t, P139_LadE, 0x005fef28)
GAME_VAR_DEF(p139_u4_t, P139_LadF, 0x0060036c)
GAME_VAR_DEF(uint32_t, P139_LadPtr, 0x0054ea58)
GAME_VAR_DEF(int32_t, P139_Lad390, 0x00600390)
GAME_VAR_DEF(int32_t, P139_LadN, 0x00600394)
GAME_VAR_DEF(int32_t, P139_Lad398, 0x00600398)
GAME_VAR_DEF(uint32_t, P139_IntroStr, 0x01271044)

_Static_assert(sizeof(p139_u6_t) == 0x18, "00c818a0");
_Static_assert(sizeof(p139_b1000_t) == 0x1000 && sizeof(p139_b400_t) == 0x400 && sizeof(p139_u4_t) == 0x10, "MLADDER");

static const char k_ms_c[] = "D:\\Driver\\Game\\MScript.c";
static void wr32(uint8_t *p, int32_t v) { memcpy(p, &v, 4); }
static int32_t rd32(const uint8_t *p) { int32_t v; memcpy(&v, p, 4); return v; }

/* адрес Game.exe области модуля (в native — один раз в реестр re_ptr) */
static uint32_t area(uint32_t addr, void *p, uint32_t size, int *done) {
#ifndef RE_HOOK_BUILD
  if (!*done) { re_ptr_register(addr, p, size); *done = 1; }
  (void)p;
  return addr;
#else
  (void)addr; (void)size; (void)done;
  return (uint32_t)(uintptr_t)p;
#endif
}
static uint32_t dyn(void *p, uint32_t size) {
#ifndef RE_HOOK_BUILD
  return re_ptr_register_dyn(p, size);
#else
  (void)size; return (uint32_t)(uintptr_t)p;
#endif
}
static void dyn_free(uint32_t a) {
  void *p = re_ptr(a);
  if (p == NULL) return;
#ifndef RE_HOOK_BUILD
  re_ptr_unregister(p);
#endif
  P98_DebugFree(p);
}

/* ---- 004f4596 ---- */
static int g_reg818a0, g_regmsg;
int32_t P139_CompileScript(const char *path) {
  P138_Blk84Clear();
  memset(P139_C818A0, 0, sizeof(p139_u6_t));
  memset(P69_MsgBlk, 0, sizeof(P69_Blk));
  memset(P127_Lamp5, 0, 200);
  memset(P127_LampOn, 0, 0x14);
  P56_Blk84[(0x00c812b8 - 0x00c810c0) / 4] = area(0x011342a0u, P69_MsgBlk, sizeof(P69_Blk), &g_regmsg);
  P113_MrkRec = area(0x00c818a0u, P139_C818A0, sizeof(p139_u6_t), &g_reg818a0);
  P56_Blk84[(0x00c812bc - 0x00c810c0) / 4] = P113_MrkRec;
  P99_ScriptFree();
  P59_VarsInit();
  P138_C8168C = 0;
  P127_SpawnCnt = 0;
  P65_Line = (char *)P98_DebugMalloc(0x400, k_ms_c, 0x149);
  if (P65_Line == NULL) return 3;
  void *f = g_fopen(path, "rt");
  if (f == NULL) return 5;
  (void)P51_FileSize(f);
  P127_ScrPos = 0;
  P139_LineNo = 0;
  while (g_fgets(P65_Line, 0x400, f) != NULL) {
    int32_t r = P131_ScriptLine();
    if (r != 0 && r != 10) { g_fclose(f); return r; }
    P139_LineNo++;
  }
  g_fclose(f);
  return 4;
}

/* ---- 004fbbfc ---- */
int32_t P139_TrailLoad(const char *path) {
  char msg[0x80];
  snprintf(msg, sizeof msg, "Attempting to read Trailblazer data file: \"%s\"", path);
  P124_DebugLog(msg);
  if (G6_00C80C50 != NULL) {
    P124_DebugLog("Trail data already exists in memory, removing.");
    P98_DebugFree(G6_00C80C50);
    G6_00C80C50 = NULL;
    G6_00C81108 = 0; P56_Blk84[(0x00c81108 - 0x00c810c0) / 4] = 0;
    P56_Blk84[(0x00c8110c - 0x00c810c0) / 4] = 0;
  }
  void *f = g_fopen(path, "rb");
  if (f == NULL) { P124_DebugLog("Failed to acces Trailblazer data file.\n"); return 0; }
  uint32_t n = ((uint32_t)P51_FileSize(f) - 4u) / 0xcu;
  G6_00C81108 = (int32_t)n; P56_Blk84[(0x00c81108 - 0x00c810c0) / 4] = n;
  int32_t *r = (int32_t *)P98_DebugMalloc((int32_t)(n * 0x14u), k_ms_c, 0x1431);
  if (r == NULL) {
    P124_DebugLog("Unable to allocate memory for trail data.  Function failed.");
    g_fclose(f);
    return 0;
  }
  memset(r, 0, n * 0x14u);
  G6_00C80C50 = r;
  for (int32_t i = 0; i < (int32_t)n; i++, r += 5) {
    g_fread(r + 1, 1, 4, f); g_fread(r + 2, 1, 4, f); g_fread(r + 3, 1, 4, f);
    r[0] = i;
  }
  P98_ScrFirst = 0;
  P124_DebugLog("Trail data has loaded successfully.\n");
  g_fclose(f);
  memset(&P125_MrkSave, 0, 4);
  P71_S127107C = 0; P71_S1271080 = 0; P71_S1271084 = 0;
  for (P125_PickIdx = 3; P125_PickIdx >= 0; P125_PickIdx--) wr32(P125_Pick + P125_PickIdx * 0x20 + 0x18, 0);
  P125_PickIdx = 0;
  return 1;
}

/* ---- 004f8b0a ---- */
int32_t P139_AddLabel(const char *name, int32_t val, int32_t *list) {
  static const char k_err[] = "Error: Unable to add label, out of memory.";
  int32_t n = list[0] + 1;
  uint8_t *arr = (uint8_t *)P98_DebugMalloc(n * 4, k_ms_c, 0xc79);
  if (arr == NULL) { P124_DebugLog(k_err); return 0; }
  uint8_t *rec = (uint8_t *)P98_DebugMalloc(8, k_ms_c, 0xc81);
  if (rec == NULL) { P124_DebugLog(k_err); P98_DebugFree(arr); return 0; }
  size_t len = strlen(name);
  char *s = (char *)P98_DebugMalloc((int32_t)(len + 1), k_ms_c, 0xc8a);
  if (s == NULL) { P124_DebugLog(k_err); P98_DebugFree(rec); P98_DebugFree(arr); return 0; }
  memcpy(s, name, len + 1);
  for (char *c = s; *c; c++) *c = (char)toupper((unsigned char)*c);
  const uint8_t *old = (const uint8_t *)re_ptr((uint32_t)list[1]);
  for (int32_t i = 0; i < list[0]; i++) wr32(arr + i * 4, old != NULL ? rd32(old + i * 4) : 0);
  if (list[1] != 0) dyn_free((uint32_t)list[1]);
  wr32(rec, (int32_t)dyn(s, (uint32_t)(len + 1)));
  wr32(rec + 4, val);
  wr32(arr + (n - 1) * 4, (int32_t)dyn(rec, 8));
  list[0] = n;
  list[1] = (int32_t)dyn(arr, (uint32_t)(n * 4));
  return 1;
}

/* ---- 004aaf3a ---- */
void P139_Effects(void) {
  if (P85_StateDirty != 4) { if (P85_StateFn) P85_StateFn(3, 1, 0, 1, 0); P85_StateDirty = 4; }
  if (P85_BlendCur != 3) { if (P85_BlendFn) P85_BlendFn(4, 4, 0, 0); P85_BlendCur = 3; }
  int32_t m = DrvSetMode0042655A(0);
  for (uint8_t *o = P95_ObjPtr((uint32_t)G010FFB40); o != NULL; o = P95_ObjPtr((uint32_t)rd32(o + 0x74))) {
    uint32_t fl = (uint32_t)rd32(o + 0x68);
    if (fl & 4) P135_SmokeObj(o);
    else if (fl & 0x20000) P139_Fn4B588E(o);
    else if (fl & 0x40000) P111_Flare((const float *)o);
    else if (fl & 0x80) P110_GlowB(o);
    else if (fl & 0x100) P110_GlowA(o);
    else if (fl & 0x20) P139_Fn4B73F3(o);
    else if (fl & 0x40) P110_GlowC(o);
    else if (fl & 8) P135_SparkQuad(o);
    else if (fl & 0x8000) P108_SmokeA(o);
    else if (fl & 0x1000) P108_SmokeB(o);
  }
  DrvSetMode0042655A(m);
  P52_ResetB = P59_Mode1137324;
}

/* ---- 00519647 ---- */
static void cfg_w(int o, int32_t v) { wr32(P103_C54EE0 + o, v); }
static int32_t rnd(float v) { return (int32_t)(v < 0 ? v - 0.5f : v + 0.5f); }   /* fistp, округление к ближайшему */
void P139_SaveCfg(void) {
  memset(P103_C54EE0, 0, 0x88);
  cfg_w(0x6c, P12_00bdfa40); cfg_w(0x70, MenuOptBDFA44); cfg_w(0x74, MenuOptBDFA48); cfg_w(0x78, MenuOptBDFA4C);
  cfg_w(0x7c, MenuOptBDFA50); cfg_w(0x80, MenuOptBDFA54); cfg_w(0x84, MenuOptBDFA58);
  P103_C54EE0[0x28] = (uint8_t)P62_HudOff2;
  P103_C54EE0[0x2b] = P102_D06A04 != 0;
  if (P103_C54EE0[0x2b]) {
    for (int k = 0; k < 7; k++) cfg_w(0x44 + 4 * k, (int32_t)P127_GoalSave[7 + k]);
    for (int k = 0; k < 3; k++) { float fv; memcpy(&fv, &P127_GoalSave[k], 4); P11_00ba52d0 = rnd(fv); cfg_w(0x2c + 4 * k, P11_00ba52d0); }
    cfg_w(0x38, P102_C816F8); cfg_w(0x3c, P102_C816FC);
  }
  cfg_w(0x60, P13_00575ee4);
  cfg_w(0x40, P13_005759a4);
  cfg_w(0x64, WI00B87E2C);
  cfg_w(0x68, G00575F24);
  cfg_w(0x0c, P99_Cars[0].f00[2]);
  P103_C54EE0[0x10] = (uint8_t)P14_00b87e84;
  P103_C54EE0[0x11] = (uint8_t)P26_FxA; P103_C54EE0[0x12] = (uint8_t)P26_FxC; P103_C54EE0[0x13] = (uint8_t)P26_FxB;
  P103_C54EE0[0x14] = (uint8_t)P26_FxD;
  { int32_t v; memcpy(&v, P56_PathPings + 0x40, 4); cfg_w(0x24, v); }   /* 00c4d660 */
  if (P58_SB87EB0 != 0) P103_C54EE0[0x2a] = 1;
  if (P11_00b87e38 == 0) { cfg_w(0, 0); cfg_w(4, D_00b87e30); }
  else {
    cfg_w(4, P11_00b87e38);
    if (P58_SB87EB0 == 0) cfg_w(0, 1);
    else { cfg_w(0, 2); cfg_w(8, (uint8_t)P138_B5A8CC); }
  }
  void *f = g_fopen("ReplayData\\User\\$TEMP$.CFG", "wb");
  if (f != NULL) { g_fwrite(P103_C54EE0, 1, 0x88, f); g_fclose(f); }
}

/* ---- 00519408 ---- */
void P139_ReplayEnd(void) {
  { int32_t v = P62_Frame; memcpy(P56_PathPings + 0x40, &v, 4); }   /* 00c4d660 ← 00d118c0 */
  if (P74_B5A894 != 0) {
    P139_SaveCfg();
    P100_RecKeys = 0x10100000;
    P100_RecInput(P12_00b5a898);
    P74_B5A894 = 0;
    if (P96_ReplayB == 0) {
      char path[0x80];
      void *f;
      if (G6_00B87EAC == 0) f = g_fopen("ReplayData\\User\\$TEMP$.PADS", "wb");
      else { snprintf(path, sizeof path, "ReplayData\\Chase\\%s.PADS", P56_PathName); f = g_fopen(path, "wb"); }
      if (f != NULL) {
        if (P36_PrevFlag != 0) P74_C54D08 = (int32_t)((uint32_t)P74_C54D08 | 0x80000000u);
        g_fwrite(&P74_C4D668, 1, 4, f);
        g_fwrite(&P74_C54D08, 1, 4, f);
        if (P100_RecBuf != NULL) g_fwrite(P100_RecBuf, 1, (size_t)(uint32_t)P74_C4BDE0, f);
        g_fclose(f);
        P98_DebugFree(P100_RecBuf);
        P100_RecBuf = NULL;
      }
      if (G6_00B87EAC != 0) {
        snprintf(path, sizeof path, "ReplayData\\Chase\\%s.PINGS", P56_PathName);
        f = g_fopen(path, "wb");
        if (f != NULL) {
          g_fwrite(&P55_RecCnt, 1, 4, f);
          if (P55_RecBase != NULL) g_fwrite(P55_RecBase, (size_t)(uint32_t)P55_RecCnt, 0x1a4, f);
          g_fclose(f);
        }
      }
    }
  }
  if (P55_RecBase != NULL) { P98_DebugFree(P55_RecBase); P55_RecBase = NULL; }
  for (int i = 0; i < 5; i++)
    if (P100_RecPtr[i] != 0) { dyn_free(P100_RecPtr[i]); P100_RecPtr[i] = 0; }
  P36_PadMode = 0;
  G6_00B87EAC = 0; G8_00B87EAC = 0;
  P58_SB87EB0 = 0; G6_00B87EB0 = 0; G8_00B87EB0 = 0;
  P109_C54B00 = 0;
}

/* ---- 0040fa60 / 00410c30 ---- */
typedef struct { uint32_t tbl, wa, wb, items; int32_t *st, *pr, *blink; int b; } keymenu_t;
static void call_item(uint32_t tbl, int32_t i, int32_t arg) {
  const uint8_t *e = (const uint8_t *)re_ptr(tbl + (uint32_t)i * 0x10u);
  if (e == NULL) return;
  void (*fn)(int32_t) = (void (*)(int32_t))re_fn((uint32_t)rd32(e));
  if (fn) fn(arg);
}
static int32_t keymenu(const keymenu_t *m) {
  int32_t *edit = m->b ? &WI005FE78C : &Q00B87F00;
  uint32_t *dst = m->b ? &WU005FE788 : &Q005FE764;
  int32_t *idx = m->b ? &WI005FE790 : &Q005FE768;
  int32_t lc = 0;
  P97_MenuCall0(m->tbl, 0);
  if (G6_00B87EEC == 0) P45_Wait(m->wa, m->wb);
  for (;;) {
    Call00522323();
    P36_PollInput();
    if (*edit == 0) {
      int fin = 0;
      if (G6_00B87EEC == 0) {
        lc = P114_MenuStep(m->tbl, m->st);
        if (lc != 0) { if ((m->b ? P19_KeysUnique14() : P19_KeysUnique12()) != 0) fin = 1; else Ui0040C88D(); }
      } else {
        *m->pr = *m->st;
        *m->st = P110_MenuSel(m->tbl, *m->st);
        if (*m->st == -1) {
          if ((m->b ? P19_KeysUnique14() : P19_KeysUnique12()) != 0) { lc = 0; fin = 1; }
          else { *m->st = *m->pr; Ui0040C88D(); }
        }
      }
      if (fin) {
        if (m->b) memcpy(P36_KeyCfg, &P54_KeySrc[6], 5 * 4);   /* 0054b7c0 → 00d04d00 */
        if (lc == -1) { if (G6_00B87EEC == 0) P57_MenuDone(); lc = 0; }
        return lc;
      }
    } else if (IsFlagSetNotMasked_004E383A(1) == 0) {
      if (--*m->blink < 1) {
        *m->blink = 10;
        uint8_t *it = (uint8_t *)re_ptr(m->items + 4u + (uint32_t)*idx * 0x10u);
        if (it != NULL) *it ^= 1;
      }
      int32_t k = m->b ? (int32_t)P12_Fn0040F09C() : P14_Fn0040F0FB();
      if (m->b ? k > 0 : k >= 0) {
        Ui0040C867();
        uint8_t *d = (uint8_t *)re_ptr(*dst);
        if (d != NULL) *d = (uint8_t)k;
        *edit = 0;
        call_item(m->tbl, *m->st, G6_00B87EEC == 0 ? 0 : 2);
        if (m->b) P97_KeyMenuBInit(); else P97_KeyMenuAInit();
      }
    } else {
      Ui0040C867();
      *edit = 0;
      call_item(m->tbl, *m->st, G6_00B87EEC == 0 ? 0 : 2);
    }
    if (G6_00B87EEC == 0) P119_MenuFrame();
    else { if (m->b) MenuHiliteRed00411A31(); else MenuHiliteRed004106E1(); P66_ScreenFrame(m->items, 0); }
  }
}
int32_t P139_KeyMenuA(void) {
  static const keymenu_t m = { 0x0054c1e0u, 0x0054c018u, 0x0054c030u, 0x0054c030u, &P139_KeyStA, &P139_KeyPrA, &P139_BlinkA, 0 };
  P97_KeyMenuAInit();
  P139_KeyStA = 0; MenuI005FE770 = 1; MenuI005FE774 = 2;
  return keymenu(&m);
}
int32_t P139_KeyMenuB(void) {
  static const keymenu_t m = { 0x0054c530u, 0x0054c338u, 0x0054c350u, 0x0054c350u, &P139_KeyStB, &P139_KeyPrB, &P139_BlinkB, 1 };
  P97_KeyMenuBInit();
  WI005FE78C = 0; P139_KeyStB = 0; MenuI005FE798 = 1; MenuI005FE79C = 2;
  return keymenu(&m);
}

/* ---- 0041b1c0 ---- */
static int g_reglad, g_regstr;
int32_t P139_LadderLoad(void) {
  char line[0x80];
  memset(P139_Ladder, 0, sizeof(p139_b1000_t)); memset(P139_LadStr, 0, sizeof(p139_b400_t));
  memset(P139_LadA, 0, 0x10); memset(P139_LadB, 0, 0x10); memset(P139_LadC, 0, 0x10);
  memset(P139_LadD, 0, 0x10); memset(P139_LadE, 0, 0x10); memset(P139_LadF, 0, 0x10);
  uint32_t base = area(0x005ff368u, P139_Ladder, sizeof(p139_b1000_t), &g_reglad);
  uint32_t str = area(0x005fef38u, P139_LadStr, sizeof(p139_b400_t), &g_regstr);
  P139_LadPtr = base;
  P139_Lad390 = 0; P139_LadN = 0; P139_Lad398 = 0;
  void *f = g_fopen("DATA\\MLADDER.DML", "r");
  if (f == NULL) { P124_DebugLog("MLADDER: DATA\\MLADDER.DML missing"); return 0; }
  P124_DebugLog("\nMLADDER: Compiling...");
  for (;;) {
    if (P47_ReadLine(f, line) == -1) {
      g_fclose(f);
      uint8_t *e = (uint8_t *)re_ptr(P139_LadPtr);
      if (e != NULL) { wr32(e, 8); wr32(e + 4, 0); wr32(e + 8, 0); wr32(e + 0xc, 0); }
      P139_LadN++;
      P124_DebugLog("MLADDER: Compilation successful\n");
      P68_IntroBase = base; P68_IntroCur = base; P139_IntroStr = str;
      S_0127104C = 0; G0127104C = 0; P68_IntroA = 0;
      return 1;
    }
    if (P141_LadderLine(line) == 0) break;
  }
  g_fclose(f);
  P124_DebugLog("MLADDER: Compilation failed\n");
  return 0;
}
