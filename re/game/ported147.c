/* v1.92: ported147 — 004f68a1 (разбор команды MScript) и 00503ddf (запись рекорда по записи скрипта).
   004f68a1: реальная граница 004f68a1..004f832e (ret, cdecl), 0x1a8e = 6798 байт (в functions.csv было 295);
   таблица переходов 004f832f (+ байтовая 004f83ef, коды 2..0x97, остальные — ветка по умолчанию 004f8271).
   По умолчанию: P65_ReadInts(cmd), P77_ListAdd(cmd->size), запись {id, P65_Ints[0..argc)}.
   Особые коды: 2 — установка переменной (004f8485 = P122_SetVar(cmd, NULL)); 0xc/0xd, 0xe/0xf — запись {0xc|0xe, переменная}
   и возврат 0 (строка закончена); 0x10/0x11, 0x6b..0x70 (If*) — {id, переменная, число}; 0x14/0x87 — до 3/4 троек/чисел;
   строки 0x16/0x66/0x5e/0x73/0x89/0x8a/0x8d (в кавычках, memcpy) и 0x6a/0x71 (токен, strcpy); 0x22 — имя уровня
   в 00c81780 (P138_LevBuf) и город по .data 00562d44 (те же 7 имён, что k_lev в ported138); 0x3d — имя погони 00c80f00
   (новая GAME_VAR P147_ChaseName), счёт файлов replaydata\Chase\%s%d.leader, выбор по байту 00b5a8cc; 0x3e — 00c80fa0
   (P136_MapName); 0x53 — копия 00c81700 → 00c816c0 (как в P145_LevelLoad) и старт fistp(x), fistp(z); 0x69 — метка
   скрипта (thunk 00401438 → 004f8b0a P139_AddLabel; в native — вариант с родными указателями списка P99_ScrNames,
   который читают P65_FindByName/P58_FreeNames); 0x86 — thunk 00401a28 → 004fc5e1 P26_RandomFx(город & 3).
   Таблицы .data 0056dc30 (тип переменной = P42_Vars[i].type), 00c80fa0, 00c81780 уже есть в native (P42_Vars,
   P136_MapName, P138_LevBuf) — генератор не нужен. Все псевдонимы адресов пишутся (work/own191.py).
   Отступление native: результат P77_ListAdd ≠ 0 (нет памяти) → возврат 3 (оригинал пишет в последнюю/чужую запись).
   00503ddf: 6 слов записи re_ptr(00c812bc) → 00b32a10 (режим 6) или 00503ef4(запись, 01271070, 00b32a10) и копия записи
   в 01271070; слово 00b32a14 = 8; 00503e83(*00b32a08, 00b32a10) ≠ 0 → копия в *00b32a08 (+4 = 8), 1. В native адрес
   01271088 (единственное значение 00b32a08 из P71_ScoreSetup) — слова P56_Blk11[10..15] и псевдонимы P71_S1271*. */
#include "ported147.h"
#include "unported.h"
#include "reptr.h"
#include "crt.h"
#include "director.h"
#include "menustate.h"
#include "smallfuncs.h"
#include "uihandlers4.h"
#include "ported4.h"
#include "ported6.h"
#include "ported7.h"
#include "ported8.h"
#include "ported11.h"
#include "ported12.h"
#include "ported13.h"
#include "ported14.h"
#include "ported15.h"
#include "ported26.h"
#include "ported36.h"
#include "ported42.h"
#include "ported52.h"
#include "ported56.h"
#include "ported58.h"
#include "ported62.h"
#include "ported65.h"
#include "ported68.h"
#include "ported69.h"
#include "ported71.h"
#include "ported77.h"
#include "ported80.h"
#include "ported88.h"
#include "ported95.h"
#include "ported96.h"
#include "ported98.h"
#include "ported99.h"
#include "ported102.h"
#include "ported122.h"
#include "ported124.h"
#include "ported125.h"
#include "ported127.h"
#include "ported136.h"
#include "ported113.h"
#include "ported138.h"
#include "ported139.h"
#include <math.h>
#include <stdio.h>
#include <string.h>

#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P147_Rec2A10")
#undef P147_Rec2A10
#pragma push_macro("P147_Rec2A10") /*gvi*/
#undef P147_Rec2A10 /*gvi*/
p147_rec6_t P147_Rec2A10;
#pragma pop_macro("P147_Rec2A10") /*gvi*/
#pragma pop_macro("P147_Rec2A10")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P147_ChaseName")
#undef P147_ChaseName
#pragma push_macro("P147_ChaseName") /*gvi*/
#undef P147_ChaseName /*gvi*/
p147_chase_t P147_ChaseName;
#pragma pop_macro("P147_ChaseName") /*gvi*/
#pragma pop_macro("P147_ChaseName")
#endif

#define B84(a)   (*(int32_t *)&P56_Blk84[((a) - 0x00c810c0u) / 4])   /* поля внутри P56_Blk84 */

static const char *const k_lev[7] = { "MIAMI_01.LEV", "FRISCO_01.LEV", "LA_01.LEV", "NY_01.LEV", "IVIEW.LEV", "TRAIN.LEV", "NC_01.LEV" };   /* .data 00562d44 */

static void strupr_c(char *s) { for (; *s; s++) if (*s >= 'a' && *s <= 'z') *s = (char)(*s - 0x20); }   /* 0053fb50 _strupr */
static int32_t tok(void) { return P65_NextToken(P65_Line, P65_Tok); }
static int32_t num(const char *s, int32_t *out) { int r = g_sscanf(s, "%d", out); return r != 0 && r != -1; }   /* 0052e250 "%d" */
static int32_t *rec_add(int32_t size) {   /* 004f8643 + последняя запись P77_List */
  if (P77_ListAdd(size) != 0) return NULL;
  return (int32_t *)P77_List[P77_ListN - 1];
}
static int32_t quoted(char *dst, size_t n) {   /* 004f6612 в буфер dst (в native — через буфер строки, с усечением до n) */
  char tmp[0x400];
  tmp[0] = 0;
  int32_t r = P96_ParseQuoted(P65_Line, tmp);
  snprintf(dst, n, "%s", tmp);
  return r;
}
static void set_city(int32_t c) { D_00b87e30 = c; P15_State = c; }
static void set_b201dc(int32_t v) { MenuVarB201DC = v; P13_00b201dc = v; G00B201DC = v; }
static void set_b87e84(int32_t v) { P14_00b87e84 = v; P98_Range[9] = v; }
static int32_t fist(uint32_t bits) { float f; memcpy(&f, &bits, 4); return (int32_t)lrintf(f); }   /* fistp */

#ifndef RE_HOOK_BUILD
/* 004f8b0a для списка с родными указателями (p65_tab_t: P65_FindByName / P58_FreeNames) — те же сообщения и DebugMalloc. */
static int32_t add_label_n(const char *name, int32_t val, p65_tab_t *list) {
  static const char k_err[] = "Error: Unable to add label, out of memory.";
  static const char k_ms_c[] = "D:\\Driver\\Game\\MScript.c";
  int32_t n = list->count + 1;
  p65_ent_t **arr = (p65_ent_t **)P98_DebugMalloc(n * (int32_t)sizeof(p65_ent_t *), k_ms_c, 0xc79);
  if (arr == NULL) { P124_DebugLog(k_err); return 0; }
  p65_ent_t *rec = (p65_ent_t *)P98_DebugMalloc((int32_t)sizeof(p65_ent_t), k_ms_c, 0xc81);
  if (rec == NULL) { P124_DebugLog(k_err); P98_DebugFree(arr); return 0; }
  size_t len = strlen(name);
  char *s = (char *)P98_DebugMalloc((int32_t)(len + 1), k_ms_c, 0xc8a);
  if (s == NULL) { P124_DebugLog(k_err); P98_DebugFree(rec); P98_DebugFree(arr); return 0; }
  memcpy(s, name, len + 1);
  strupr_c(s);
  for (int32_t i = 0; i < list->count; i++) arr[i] = list->ents[i];
  if (list->ents != NULL) P98_DebugFree(list->ents);
  rec->name = s; rec->value = val;
  arr[n - 1] = rec;
  list->count = n; list->ents = arr;
  return 1;
}
#endif

/* копия 00c81700 → 00c816c0 (16 слов: 14 — P127_GoalSave, +0x38/+0x3c — P102_C816F8/FC) */
static void goal_copy(void) {
  uint32_t w[16];
  memcpy(w, P127_GoalPause, sizeof w);
  memcpy(P127_GoalSave, w, sizeof(p127_u14_t));
  P102_C816F8 = (int32_t)w[14]; P102_C816FC = (int32_t)w[15];
}

/* ---- 004f68a1 ---- */
int32_t P147_ParseCmd(void *cmdp) {
  p42_cmd_t *cmd = (p42_cmd_t *)cmdp;
  const char *ifname = NULL;
  int32_t r, v, *p;
  if (cmd == NULL) return 9;
  int32_t id = cmd->id;
  switch (id) {
  case 2:
    r = tok(); if (r != 0) return r;
    strupr_c(P65_Tok);
    return P122_SetVar(cmd, NULL);
  case 0xc: case 0xd: case 0xe: case 0xf:
    r = tok(); if (r != 0) return r;
    strupr_c(P65_Tok);
    v = P42_FindVar(P65_Tok);
    if (v == -1 || P42_Vars[v].type != 3) return 0xc;
    if ((p = rec_add(8)) == NULL) return 3;
    p[0] = id <= 0xd ? 0xc : 0xe; p[1] = v;
    return 0;
  case 0x10: case 0x11:
    r = tok(); if (r != 0) return r;
    strupr_c(P65_Tok);
    v = P42_FindVar(P65_Tok);
    if (v == -1 || P42_Vars[v].type != 3) return 0xc;
    r = tok(); if (r != 0) return r;
    if (!num(P65_Tok, &P65_Ints[0])) return 0xc;
    if ((p = rec_add(0xc)) == NULL) return 3;
    p[0] = id; p[1] = v; p[2] = P65_Ints[0];
    return 0xb;
  case 0x13:
    r = P65_ReadInts(cmd); if (r != 0) return r;
    B84(0x00c81278u) = 1; B84(0x00c812c0u) = P65_Ints[0]; B84(0x00c812c4u) = -500; B84(0x00c812c8u) = P65_Ints[1];
    break;
  case 0x14: case 0x87: {
    int32_t maxn = id == 0x14 ? 3 : 4, per = id == 0x14 ? 3 : 1;
    r = tok(); if (r != 0) return r;
    strupr_c(P65_Tok);
    if (!num(P65_Tok, &P65_Ints[0])) return 0xc;
    if (P65_Ints[0] > maxn) P65_Ints[0] = maxn;
    int32_t n = P65_Ints[0];
    for (int32_t i = 0; i < n * per; i++) {
      r = tok(); if (r != 0) return r;
      strupr_c(P65_Tok);
      if (1 + i >= 64 || !num(P65_Tok, &P65_Ints[1 + i])) return 0xc;
    }
    if (id == 0x14) {
      if ((p = rec_add(n * 0xc + 8)) == NULL) return 3;
      p[0] = 0x14; p[1] = n;
      for (int32_t i = 0; i < n * 3; i++) p[2 + i] = P65_Ints[1 + i];
    } else {
      G6_00B20368 = n; G8_00B20368 = n;
      for (int32_t i = 0; i < n; i++) memcpy(&A_00D11830[i * 4], &P65_Ints[1 + i], 4);
    }
    return 0xb;
  }
  case 0x16: case 0x66: case 0x8d: {
    r = tok(); if (r != 0) return r;
    strupr_c(P65_Tok);
    if (!num(P65_Tok, &P65_Ints[0])) return 0xc;
    r = P96_ParseQuoted(P65_Line, P65_Tok); if (r != 0) return r;
    int32_t len = (int32_t)strlen(P65_Tok) + 1;
    if ((p = rec_add(len + 0xc)) == NULL) return 3;
    p[0] = id; p[1] = id == 0x8d ? P65_Ints[0] : P65_Ints[0] * 0x32; p[2] = len;
    memcpy(p + 3, P65_Tok, (size_t)len);
    return 0xb;
  }
  case 0x5e: case 0x73: case 0x89: case 0x8a: {
    r = P96_ParseQuoted(P65_Line, P65_Tok); if (r != 0) return r;
    int32_t len = (int32_t)strlen(P65_Tok) + 1;
    if ((p = rec_add(len + 8)) == NULL) return 3;
    p[0] = id; p[1] = len;
    memcpy(p + 2, P65_Tok, (size_t)len);
    return 0xb;
  }
  case 0x6a: case 0x71: {
    r = tok(); if (r != 0) return r;
    int32_t len = (int32_t)strlen(P65_Tok) + 1;
    if ((p = rec_add(len + 8)) == NULL) return 3;
    p[0] = id; p[1] = len;
    strcpy((char *)(p + 2), P65_Tok);
    return 0xb;
  }
  case 0x1e: P26_FxA = 1; break;
  case 0x1f: set_b201dc(1); set_b87e84(1); P52_FogOn = 0; break;
  case 0x5f: set_b201dc(1); set_b87e84(1); P52_FogOn = 1; break;
  case 0x20: set_b201dc(1); set_b87e84(1); P26_FxB = 1; break;
  case 0x22:
    r = quoted(P138_LevBuf, sizeof(p138_s100_t));
    if (r != 0) { P77_LevelName = NULL; B84(0x00c81164u) = 0; P138_LevBuf[0] = 0; return r; }
    P77_LevelName = P138_LevBuf; B84(0x00c81164u) = (int32_t)re_addr(P138_LevBuf);
    strupr_c(P138_LevBuf);
    for (int32_t i = 0; i < 7; i++)
      if (strcmp(P138_LevBuf, k_lev[i]) == 0) { set_city(i); return 0xb; }
    break;
  case 0x27: P14_00b202dc = 1; P80_Flag17AEC = 0; break;
  case 0x28: P14_00b202d8 = 1; set_b87e84(1); set_b201dc(1); P80_Flag17AEC = 0; break;
  case 0x34:
    r = P65_ReadInts(cmd); if (r != 0) return r;
    B84(0x00c810fcu) = P65_Ints[0];
    break;
  case 0x3d: {
    r = quoted(P147_ChaseName, sizeof(p147_chase_t));
    if (r != 0) { P138_LevBuf[0] = 0; return r; }   /* оригинал: 00c81780 = 0 */
    int32_t n = 0;
    char path[64];
    for (;;) {
      snprintf(path, sizeof path, "replaydata\\Chase\\%s%d.leader", P147_ChaseName, (int)n);
      void *f = g_fopen(path, "rb");
      if (f == NULL) break;
      g_fclose(f);
      n++;
    }
    if (n != 0) {
      uint8_t b = (uint8_t)P138_B5A8CC;
      if (GameMode == 0) { b = (uint8_t)(b + 1); b = (uint8_t)((int32_t)b % n); P138_B5A8CC = (int32_t)(((uint32_t)P138_B5A8CC & ~0xffu) | b); }
      snprintf(P56_PathName, sizeof(p56_s100_t), "%s%d", P147_ChaseName, (int)b);
      P58_SB87EB0 = 1; G6_00B87EB0 = 1; G8_00B87EB0 = 1;
      P36_PadMode = 3;
    }
    break;
  }
  case 0x3e:
    r = quoted(P136_MapName, sizeof(p136_path_t));
    if (r != 0) { P136_MapName[0] = 0; return r; }
    break;
  case 0x3f: P95_C818B8 = 1; break;
  case 0x40:
    r = tok(); if (r != 0) return r;
    if (!num(P65_Tok, &P65_Ints[0])) return 0xc;
    S_00D1192C = P65_Ints[0];
    if (P12_00bdfa40 != 0 && D_00b87e30 >= 0 && D_00b87e30 < 4 && P62_Menu1271060 == 8) S_00D1192C = P12_00bdfa40 - 1;
    break;
  case 0x41: case 0x43: case 0x44: case 0x96:
    r = tok(); if (r != 0) return r;
    if (!num(P65_Tok, &P65_Ints[0])) return 0xc;
    if (id == 0x41) P95_BDFA60 = P65_Ints[0];
    else if (id == 0x43) P95_BDF9D4 = P65_Ints[0];
    else if (id == 0x44) P95_BDF9D0 = P65_Ints[0] + 4;
    else P88_Mode575 = P65_Ints[0];
    break;
  case 0x42: P26_FxC = 1; break;
  case 0x4d: case 0x4e: {
    r = tok(); if (r != 0) return r;
    if (!num(P65_Tok, &P65_Ints[0])) return 0xc;
    int32_t b = -1;
    if (tok() == 0) {
      if (!num(P65_Tok, &P65_Ints[1])) return 0xc;
      b = P65_Ints[1];
    }
    if (id == 0x4d) { P125_C814E4 = b; P125_C814E0 = P65_Ints[0]; }
    else { P125_C81694 = b; P125_C81690 = P65_Ints[0]; }
    break;
  }
  case 0x53:
    if (GameMode == 0) { P124_DebugLog("MSCRIPT: Reusing player position (MStart = MNext)"); goal_copy(); }
    B84(0x00c81278u) = 1;
    P11_00ba52d0 = fist(P127_GoalSave[0]);
    B84(0x00c812c0u) = P11_00ba52d0; B84(0x00c812c4u) = -500;
    P11_00ba52d0 = fist(P127_GoalSave[2]);
    B84(0x00c812c8u) = P11_00ba52d0;
    P102_D06A04 = 1;
    break;
  case 0x54: P26_FxD = 1; break;
  case 0x69:
    r = tok(); if (r != 0) return r;
#ifdef RE_HOOK_BUILD
    P139_AddLabel(P65_Tok, P77_ListN, (int32_t *)&P99_ScrNames);
#else
    add_label_n(P65_Tok, P77_ListN, (p65_tab_t *)&P99_ScrNames);
#endif
    return 0xb;
  case 0x6b: ifname = "IfEqual: "; /* fallthrough */
  case 0x6c: if (ifname == NULL) ifname = "IfNotEqual: "; /* fallthrough */
  case 0x6d: if (ifname == NULL) ifname = "IfLessThan: "; /* fallthrough */
  case 0x6e: if (ifname == NULL) ifname = "IfGreaterThan: "; /* fallthrough */
  case 0x6f: if (ifname == NULL) ifname = "IfLessOrEqual: "; /* fallthrough */
  case 0x70: {
    if (ifname == NULL) ifname = "IfGreaterOrEqual: ";
    r = tok(); if (r != 0) return r;
    strupr_c(P65_Tok);
    v = P42_FindVar(P65_Tok);
    if (v == -1) {
      char msg[128];
      snprintf(msg, sizeof msg, "%sVariable not found.", ifname);
      P124_DebugLog(msg);
      return 0xc;
    }
    r = tok(); if (r != 0) return r;
    strupr_c(P65_Tok);
    if (!num(P65_Tok, &P65_Ints[0])) return 0xc;
    if ((p = rec_add(0xc)) == NULL) return 3;
    p[0] = id; p[1] = v; p[2] = P65_Ints[0];
    return 0xb;
  }
  case 0x86:
    if (GameMode == 0) P26_RandomFx(D_00b87e30 & 3);
    return 0xb;
  case 0x88: S_00D1192C = P68_B87E54; return 0xb;
  case 0x97: G6_00B87EA0 = 1; P62_HudOff1 = 1; break;
  default:
    r = P65_ReadInts(cmd); if (r != 0) return r;
    r = P77_ListAdd(cmd->size); if (r != 0) return r;
    p = (int32_t *)P77_List[P77_ListN - 1];
    p[0] = id;
    for (int32_t i = 0; i < cmd->argc; i++) p[1 + i] = P65_Ints[i];
    break;
  }
  return 0xb;
}

/* ---- 00503ddf ---- */
static void set_2a10(const int32_t *w) {
  memcpy(P147_Rec2A10, w, sizeof(p147_rec6_t));
  P71_V2A14 = w[1]; P71_V2A1C = w[3]; P71_V2A20 = w[4]; P71_V2A24 = w[5];
}
static void get_1070(int32_t *w) { memcpy(w, P125_MrkSave, sizeof(p125_mrk_t)); }
static void set_1070(const int32_t *w) {
  memcpy(P125_MrkSave, w, sizeof(p125_mrk_t));
  for (int k = 0; k < 6; k++) P56_Blk11[4 + k] = (uint32_t)w[k];
  P71_S1271074 = w[1]; P71_S127107C = w[3]; P71_S1271080 = w[4]; P71_S1271084 = w[5];
}
int32_t P147_ScoreRec(void) {
  int32_t rec[6], cur[6];
  const uint8_t *src = (const uint8_t *)re_ptr(P113_MrkRec);
  if (src == NULL) return 0;   /* native: нет записи — оригинал читал бы по 0 */
  memcpy(rec, src, sizeof rec);
  if (P62_Menu1271060 == 6) memcpy(cur, rec, sizeof cur);
  else {
    int32_t old[6];
    get_1070(old);
    P14_Fn00503EF4((const uint8_t *)rec, (const uint8_t *)old, (uint8_t *)cur);
    set_1070(rec);
  }
  cur[1] = 8;
  set_2a10(cur);
  uint8_t *dp = NULL;
#ifndef RE_HOOK_BUILD
  int32_t dst[6];
  int native1088 = P71_Ptr2A08 == 0x01271088u;
  if (native1088) { for (int k = 0; k < 6; k++) dst[k] = (int32_t)P56_Blk11[10 + k]; dp = (uint8_t *)dst; }
  else
#endif
  dp = (uint8_t *)re_ptr(P71_Ptr2A08);
  if (dp == NULL) return 0;   /* native: оригинал читал бы по 0 */
  if (P14_Fn00503E83(dp, (const uint8_t *)cur) == 0) return 0;
  memcpy(dp, cur, sizeof cur);
  ((int32_t *)dp)[1] = 8;
#ifndef RE_HOOK_BUILD
  if (native1088) {
    for (int k = 0; k < 6; k++) P56_Blk11[10 + k] = (uint32_t)dst[k];
    P71_S127108C = dst[1]; P71_S1271094 = dst[3]; P71_S1271098 = dst[4]; P71_S127109C = dst[5];
  }
#endif
  return 1;
}
