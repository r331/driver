/* ported141.c — the mission ladder parser (DATA\MLADDER.DML) and the high-score screen setup
   (English overview; original notes follow).
   MLADDER is a small script describing the Undercover campaign: SETCITY, ROOM ... ENDROOM (the motel room
   with up to 4 options: missions, jokes, car select), MISSION / SUBMISSION n, INTERVIEW, RENDER, TRIGGER,
   IF / IFOK / ELSE / ENDIF, QUITONFAIL, END.  Each command becomes a 16-byte record {code, value, next, else}
   in P139_Ladder; IF/ELSE/ENDIF and rooms are linked by patching "next"/"else" of earlier records.
   The records keep Game.exe addresses (the campaign code follows them), hence the re_ptr translations. */
/* v1.86: ported141 — см. ported141.h.
   0041b8ac — строка MLADDER: при 00600394 < 0x100, 00600398 < 0x20, 0060039c < 4 — токен 0041c7da (пусто → 1), команда
     без учёта регистра: SETCITY [MIAMI|SF|LA|NY] → {0, город}; ROOM — строки 005fef38 + n·0x20 (4 × {u16 1, u16 0, u32 0}),
     0060037c/005ff338/005fef28[глубина], {1, n, сама, сама}; ENDROOM — закрытие, ссылки 0060036c[i] → следующая запись;
     INTERVIEW {0xb}; MISSION n — в ROOM пункт {2, n, адрес записи} (≤ 4), 0060036c[k] ← предыдущая запись, {2, n};
     SUBMISSION n {2, n}; JOKE/CARSELECT n — только пункт {4|8, n, 0}; RENDER {3}; TRIGGER {4}; IF {5}/IFOK {6} (atoi токена
     команды) — 005ff358[глубина]; ELSE/ENDIF {7} — связывание +0xc/+8; QUITONFAIL {9}; END {0xc}. Запись — {код, a,
     следующая, иначе}, 00600394++. Неизвестная команда — 1 (проверка в оригинале никогда не срабатывает: cmp (tok[0]==0),0x23).
   0040f3de — по 0054bf18 (1, 2, 3, 7, 0xb): строки заголовка 00c55820[0x1c..0x20] + [005fe6bc + 0x7a|0x82|0x86], 005fe694 = 8|4,
     столбцы 0054be90/a0/b0/c0/d0; 0xb — дополнительно строка таблицы 0xc: "%s: %s" и время (005fe5d4, 005fe698); заголовок
     "%s %s" → 005fe4f4; 0054be80/60 ← 00c55888/8c; 5 строк рекордов (шаг 0x2c): имя +4, время "%02d:%02d:%02d" (+0x28/+0x24/
     +0x20, вид +0x18 = 8) или "--:--:--", для 7 — "$%d"/"%d" (+0x10) или "-"; столбец очков для 1 — "%d" или "-".
   Отступления native: 0041b8ac — пункт ROOM при глубине 0 (в оригинале 005fef24/00600378 — соседние переменные) пропускается,
     записи по незарегистрированному адресу не пишутся; 0040f3de — значение 0054bf18 вне 1/2/3/7/0xb (в оригинале —
     неинициализированные локали) — выход без изменений; буферы строк 005fe4f4..005fe6f8 в native — один массив под синтетическим
     адресом re_ptr_register_dyn (005fe4e4 занят P97_FpsTxtA); нулевая/незарегистрированная запись рекорда читается как нули. */
#include "ported141.h"
#include "p141_data.h"
#include "ported139.h"
#include "ported124.h"
#include "ported19.h"
#include "ported42.h"
#include "strtab.h"
#include "uihandlers.h"
#include "widgets.h"
#include "reptr.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#ifndef RE_HOOK_BUILD
#pragma push_macro("P141_HsMenu") /*gvi*/
#undef P141_HsMenu /*gvi*/
p141_hsmenu_t P141_HsMenu = P141_HSMENU_INIT;   /* .data 0054bd10 */
#pragma pop_macro("P141_HsMenu") /*gvi*/
#pragma push_macro("P141_HsStr") /*gvi*/
#undef P141_HsStr /*gvi*/
p141_hsstr_t  P141_HsStr = P141_HSSTR_INIT;     /* .data 0054bf1c */
#pragma pop_macro("P141_HsStr") /*gvi*/
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P141_LadI")
#undef P141_LadI
#pragma push_macro("P141_LadI") /*gvi*/
#undef P141_LadI /*gvi*/
int32_t P141_LadI;
#pragma pop_macro("P141_LadI") /*gvi*/
#pragma pop_macro("P141_LadI")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P141_LadDepth")
#undef P141_LadDepth
#pragma push_macro("P141_LadDepth") /*gvi*/
#undef P141_LadDepth /*gvi*/
int32_t P141_LadDepth;
#pragma pop_macro("P141_LadDepth") /*gvi*/
#pragma pop_macro("P141_LadDepth")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P141_LadRooms")
#undef P141_LadRooms
#pragma push_macro("P141_LadRooms") /*gvi*/
#undef P141_LadRooms /*gvi*/
int32_t P141_LadRooms;
#pragma pop_macro("P141_LadRooms") /*gvi*/
#pragma pop_macro("P141_LadRooms")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P141_LadVal")
#undef P141_LadVal
#pragma push_macro("P141_LadVal") /*gvi*/
#undef P141_LadVal /*gvi*/
int32_t P141_LadVal;
#pragma pop_macro("P141_LadVal") /*gvi*/
#pragma pop_macro("P141_LadVal")
#endif
#endif
_Static_assert(sizeof(p141_hsmenu_t) == P141_HSMENU_SIZE && sizeof(p141_hsstr_t) == P141_HSSTR_SIZE, "HS");

#include "memrw.h"
/* wr16 — local helper: unaligned int16 write. */
static void wr16(uint8_t *p, int16_t v) { memcpy(p, &v, 2); }
/* ci_eq — local helper: case-insensitive string equality. */
static int ci_eq(const char *a, const char *b) {
  for (; *a && *b; a++, b++) if (toupper((unsigned char)*a) != toupper((unsigned char)*b)) return 0;
  return *a == *b;
}

/* ---------------- 0041b8ac ---------------- */
/* MLADDER record codes (word 0 of a 16-byte ladder record {code, value, next, else}). */
enum {
  LAD_SETCITY = 0, LAD_ROOM = 1, LAD_MISSION = 2, LAD_RENDER = 3, LAD_TRIGGER = 4, LAD_IF = 5, LAD_IFOK = 6,
  LAD_ENDIF = 7,       /* written for both ELSE and ENDIF */
  LAD_QUITONFAIL = 9, LAD_INTERVIEW = 0xb, LAD_END = 0xc
};
/* Option types inside a ROOM's option list (4 x {u16 type, u16 value, u32 record address}). */
enum { LAD_OPT_NONE = 1, LAD_OPT_MISSION = 2, LAD_OPT_JOKE = 4, LAD_OPT_CARSELECT = 8 };
enum { CITY_MIAMI = 0, CITY_SF = 1, CITY_LA = 2, CITY_NY = 3 };
#define LAD_REC_SIZE 0x10
/* lad_put — local helper: writes ladder record {code, a, next, else} at Game.exe address `at`. */
static void lad_put(uint32_t at, int32_t code, int32_t a, uint32_t next, uint32_t else_rec) {
  uint8_t *rec = (uint8_t *)re_ptr(at);
  if (rec == NULL) return;
  wr32(rec, code); wr32(rec + 4, a); wr32(rec + 8, (int32_t)next); wr32(rec + 0xc, (int32_t)else_rec);
}
/* lad_next — local helper: appends a record whose next/else both point at the following record. */
static void lad_next(int32_t code, int32_t a) {   /* запись {код, a, +0x10, +0x10}, сдвиг 0054ea58 */
  uint32_t next_rec = P139_LadPtr + LAD_REC_SIZE;
  lad_put(P139_LadPtr, code, a, next_rec, next_rec);
  P139_LadPtr = next_rec; P139_LadN++;
}
/* lad_link — local helper: points "else" (and "next" too when both) of record `rec` at the current end. */
static void lad_link(uint32_t rec, int both) {    /* +0xc (и +8) записи ← текущая */
  uint8_t *e = (uint8_t *)re_ptr(rec);
  if (e == NULL) return;
  if (both) wr32(e + 8, (int32_t)P139_LadPtr);
  wr32(e + 0xc, (int32_t)P139_LadPtr);
}
/* lad_err — local helper: logs msg to debug.log and returns 0 (parse error). */
static int lad_err(const char *msg) { P124_DebugLog(msg); return 0; }
/* пункт ROOM [глубина − 1]; 1 — записан */
/* lad_opt — local helper: adds an option {type, value, record address} to the innermost open ROOM.
   Returns 1, or 0 when no ROOM is open. */
static int lad_opt(int16_t type, int16_t val, uint32_t addr) {
  int32_t room = P141_LadDepth - 1;
  if (room < 0 || room > 3) return 0;
  uint8_t *opt = (uint8_t *)re_ptr(P139_LadC[room] + (uint32_t)P139_LadE[room] * 8u);
  if (opt != NULL) { wr16(opt, type); wr16(opt + 2, val); wr32(opt + 4, (int32_t)addr); }
  P139_LadE[room]++;
  return 1;
}
/* lad_cnt — local helper: number of options in the innermost open ROOM. */
static int32_t lad_cnt(void) { int32_t j = P141_LadDepth - 1; return (j < 0 || j > 3) ? 0 : (int32_t)P139_LadE[j]; }

/* P141_LadderLine — Game.exe 0041b8ac, cdecl.  Parses one line of DATA\MLADDER.DML into ladder records.
   Returns 1 (including empty lines and unknown commands), 0 on an error (message in debug.log).
   Limits: 0x100 records, 0x20 rooms, nesting depth 4.  A MISSION inside a ROOM is also added as a room option,
   and the record before it is remembered (P139_LadF) so ENDROOM can link it past the room.
   Quirk kept: the original's "unknown command" check can never fire, so unknown words are ignored.
   Native deviations: a room option at depth 0 is skipped; writes to unregistered addresses are dropped. */
int32_t P141_LadderLine(char *line) {
  char tok[0x80];
  if (!(P139_LadN < 0x100 && P139_Lad398 < 0x20 && P141_LadDepth < 4)) return lad_err("MLADDER: Ladder too big");
  if (P19_TakeToken(line, tok) == 1) return 1;
  if (ci_eq(tok, "SETCITY")) {
    int32_t city;
    if (P19_TakeToken(line, tok) == 1) return lad_err("MLADDER: Missing parameter");
    if (ci_eq(tok, "[MIAMI]")) city = CITY_MIAMI; else if (ci_eq(tok, "[SF]")) city = CITY_SF;
    else if (ci_eq(tok, "[LA]")) city = CITY_LA; else if (ci_eq(tok, "[NY]")) city = CITY_NY;
    else return lad_err("MLADDER: Unknown CITY");
    lad_next(LAD_SETCITY, city);
  } else if (ci_eq(tok, "ROOM")) {
    if (P139_Lad398 > 0x1f) return lad_err("MLADDER: Too many rooms");
    if (P139_Lad390 == 0) { P139_Lad390 = (int32_t)re_addr(P139_LadStr); P139_Lad398 = 0; }
    else P139_Lad390 += 0x20;
    uint8_t *r = (uint8_t *)re_ptr((uint32_t)P139_Lad390);
    for (P141_LadI = 0; P141_LadI < 4; P141_LadI++)
      if (r != NULL) { wr16(r + P141_LadI * 8, LAD_OPT_NONE); wr16(r + P141_LadI * 8 + 2, 0); wr32(r + P141_LadI * 8 + 4, 0); }
    P139_LadC[P141_LadDepth] = (uint32_t)P139_Lad390;
    P139_LadD[P141_LadDepth] = (uint32_t)P139_Lad398;
    P139_LadE[P141_LadDepth] = 0;
    P141_LadRooms++;
    lad_put(P139_LadPtr, LAD_ROOM, P139_Lad398, P139_LadPtr, P139_LadPtr);   /* next/else point at itself until linked */
    P139_LadPtr += LAD_REC_SIZE; P139_LadN++; P139_Lad398++; P141_LadDepth++;
  } else if (ci_eq(tok, "ENDROOM")) {
    if (--P141_LadDepth < 0) return lad_err("MLADDER: Unmatched ENDROOM");
    if (P139_LadC[P141_LadDepth] == 0) return lad_err("MLADDER: Unmatched ENDROOM");
    P141_LadRooms--;
    P139_LadC[P141_LadDepth] = 0;
    for (P141_LadI = 0; P141_LadI < 4; P141_LadI++)
      if (P139_LadF[P141_LadI] != 0) { lad_link(P139_LadF[P141_LadI], 1); P139_LadF[P141_LadI] = 0; }
  } else if (ci_eq(tok, "INTERVIEW")) {
    lad_next(LAD_INTERVIEW, 0);
  } else if (ci_eq(tok, "MISSION")) {
    if (P19_TakeToken(line, tok) == 1) return lad_err("MLADDER: Missing MISSION parameter");
    P141_LadVal = atoi(tok);
    if (P141_LadRooms != 0) {
      int32_t n_opts = lad_cnt();
      if (n_opts > 3) return lad_err("MLADDER: Too many options in ROOM");
      if (n_opts > 0) P139_LadF[n_opts] = P139_LadPtr - LAD_REC_SIZE;   /* previous record: linked past the room at ENDROOM */
      lad_opt(LAD_OPT_MISSION, (int16_t)P141_LadVal, P139_LadPtr);
    }
    lad_next(LAD_MISSION, P141_LadVal);
  } else if (ci_eq(tok, "SUBMISSION")) {
    if (P19_TakeToken(line, tok) == 1) return lad_err("MLADDER: Missing SUBMISSION parameter");
    P141_LadVal = atoi(tok);
    lad_next(LAD_MISSION, P141_LadVal);
  } else if (ci_eq(tok, "JOKE") || ci_eq(tok, "CARSELECT")) {
    int joke = ci_eq(tok, "JOKE");
    if (P141_LadRooms == 0) return lad_err(joke ? "MLADDER: JOKE used outside ROOM" : "MLADDER: CARSELECT used outside ROOM");
    if (lad_cnt() > 3) return lad_err("MLADDER: Too many options in ROOM");
    if (P19_TakeToken(line, tok) == 1) return lad_err(joke ? "MLADDER: Missing JOKE parameter" : "MLADDER: Missing CARSELECT parameter");
    P141_LadVal = atoi(tok);
    lad_opt(joke ? LAD_OPT_JOKE : LAD_OPT_CARSELECT, (int16_t)P141_LadVal, 0);
  } else if (ci_eq(tok, "RENDER")) {
    if (P19_TakeToken(line, tok) == 1) return lad_err("MLADDER: Missing RENDER parameter");
    lad_next(LAD_RENDER, atoi(tok));
  } else if (ci_eq(tok, "TRIGGER")) {
    if (P19_TakeToken(line, tok) == 1) return lad_err("MLADDER: Missing TRIGGER parameter");
    lad_next(LAD_TRIGGER, atoi(tok));
  } else if (ci_eq(tok, "IF") || ci_eq(tok, "IFOK")) {
    int32_t code = LAD_IFOK;
    if (ci_eq(tok, "IF")) {
      code = LAD_IF;
      if (P19_TakeToken(line, tok) == 1) return lad_err("MLADDER: Missing IF parameter");
    }
    if (P141_LadDepth >= 0 && P141_LadDepth < 4) P139_LadA[P141_LadDepth] = P139_LadPtr;
    lad_next(code, atoi(tok));
    P141_LadDepth++;
  } else if (ci_eq(tok, "ELSE")) {
    if (--P141_LadDepth < 0) return lad_err("MLADDER: Unmatched ELSE");
    lad_next(LAD_ENDIF, 0);
    if (P139_LadA[P141_LadDepth] != 0) { lad_link(P139_LadA[P141_LadDepth], 0); P139_LadA[P141_LadDepth] = 0; }
    P139_LadB[P141_LadDepth] = P139_LadPtr - LAD_REC_SIZE;
    P141_LadDepth++;
  } else if (ci_eq(tok, "ENDIF")) {
    if (--P141_LadDepth < 0) return lad_err("MLADDER: Unmatched ENDIF");
    lad_next(LAD_ENDIF, 0);
    if (P139_LadA[P141_LadDepth] == 0) {
      if (P139_LadB[P141_LadDepth] == 0) return lad_err("MLADDER: Unmatched ENDIF");
      lad_link(P139_LadB[P141_LadDepth], 1); P139_LadB[P141_LadDepth] = 0;
    } else { lad_link(P139_LadA[P141_LadDepth], 0); P139_LadA[P141_LadDepth] = 0; }
  } else if (ci_eq(tok, "QUITONFAIL")) {
    lad_next(LAD_QUITONFAIL, 0);
  } else if (ci_eq(tok, "END")) {
    lad_next(LAD_END, 0);
  }
  return 1;
}

/* ---------------- 0040f3de ---------------- */
#define HS_BUF0 0x005fe4f4u   /* заголовок 0x40, строки 005fe534 (5 × 0x20), 005fe5d4, 005fe5f4 (5 × 0x20), 005fe698, пустые 005fe6c0.. */
#ifdef RE_HOOK_BUILD
/* hs_p / hs_a — local helpers for the string buffers 005fe4f4..005fe6f8: hs_p gives a C pointer, hs_a the
   address stored into the menu table (hook: the Game.exe address itself; native: a synthetic address
   registered with re_ptr_register_dyn). */
static char *hs_p(uint32_t a) { return (char *)(uintptr_t)a; }
static uint32_t hs_a(uint32_t a) { return a; }
#else
static char g_hsbuf[0x005fe6f8u - HS_BUF0];
static uint32_t g_hsdyn;
static char *hs_p(uint32_t a) { return &g_hsbuf[a - HS_BUF0]; }
static uint32_t hs_a(uint32_t a) {
  if (g_hsdyn == 0) g_hsdyn = re_ptr_register_dyn(g_hsbuf, sizeof g_hsbuf);
  return g_hsdyn + (a - HS_BUF0);
}
#endif
/* hs_set — local helper: stores a word into the high-score menu table at Game.exe address a. */
static void hs_set(uint32_t a, uint32_t v) { wr32(&P141_HSM8(a), (int32_t)v); }
/* str_at — local helper: game string i of the string table (empty string if missing). */
static const char *str_at(int32_t i) {
  const char *s = (i >= 0 && i < 0x15e) ? (const char *)re_ptr(P97_StrAddr[i]) : NULL;
  return s ? s : "";
}
static const uint8_t k_zero[0x2c];
/* hs_rec — local helper: high-score record at address a, or an all-zero record if unmapped. */
static const uint8_t *hs_rec(uint32_t a) { const uint8_t *p = (const uint8_t *)re_ptr(a); return p ? p : k_zero; }
/* hs_time — local helper: formats the record time (+0x28 : +0x24 : +0x20) as "%02d:%02d:%02d"
   ("%d:..." when big), or "--:--:--" when the record is empty (+0x18 != 8).
   TODO(RE): unsure what value 8 at +0x18 means beyond "record filled". */
static void hs_time(char *dst, const uint8_t *r, int big) {
  if (rd32(r + 0x18) == 8)
    snprintf(dst, 0x20, big ? "%d:%02d:%02d" : "%02d:%02d:%02d", rd32(r + 0x28), rd32(r + 0x24), rd32(r + 0x20));
  else snprintf(dst, 0x20, "--:--:--");
}

/* P141_HsSetup — Game.exe 0040f3de, cdecl.  Fills the high-score screen for table UiVar0054BF18 and level
   005fe6bc: title strings, column headers, and 5 rows (records 0x2c bytes apart: name at +4, time or
   score).  Table 7 shows money ("$%d") instead of a time; table 1 adds a score column; table 0xb shows
   the best of table 0xc as an extra "%s: %s" line with its time.
   TODO(RE): unsure which game modes tables 1, 2, 3, 7, 0xb are.
   Native deviation: other table ids return without changes (the original uses uninitialised locals). */
void P141_HsSetup(void) {
  int32_t title_str, title2_str, time_col, score_col;
  uint32_t a0, a1, a2, a3, a4;
  int32_t level = UiVar005FE6BC;
  switch (UiVar0054BF18) {
  case 1: title_str = 0x1d; title2_str = level + 0x7a; WI005FE694 = 8; score_col = 1; time_col = 1;
    a0 = P97_StrAddr[0x21]; a1 = P97_StrAddr[0x23]; a2 = P97_StrAddr[0x24]; a3 = hs_a(0x005fe6d0u); a4 = hs_a(0x005fe6d4u); break;
  case 2: title_str = 0x1c; title2_str = level + 0x7a; WI005FE694 = 8; score_col = 0; time_col = 1;
    a0 = P97_StrAddr[0x21]; a1 = hs_a(0x005fe6c4u); a2 = P97_StrAddr[0x24]; a3 = hs_a(0x005fe6c8u); a4 = hs_a(0x005fe6ccu); break;
  case 3: title_str = 0x1e; title2_str = level + 0x82; WI005FE694 = 4; score_col = 0; time_col = 1;
    a0 = P97_StrAddr[0x21]; a1 = hs_a(0x005fe6d8u); a2 = P97_StrAddr[0x24]; a3 = hs_a(0x005fe6dcu); a4 = hs_a(0x005fe6e0u); break;
  case 7: title_str = 0x20; title2_str = level + 0x82; WI005FE694 = 4; score_col = 0; time_col = 0;
    a0 = P97_StrAddr[0x21]; a1 = hs_a(0x005fe6e8u); a2 = P97_StrAddr[0x22]; a3 = hs_a(0x005fe6ecu); a4 = hs_a(0x005fe6f0u); break;
  case 0xb: {
    title_str = 0x1f; title2_str = level + 0x86; WI005FE694 = 4; score_col = 0; time_col = 1;
    a0 = P97_StrAddr[0x21]; a1 = hs_a(0x005fe6e4u); a2 = P97_StrAddr[0x24];
    uint32_t hs_addr = (uint32_t)P42_GetHighScore(0xc, level);
    const char *nm = (const char *)re_ptr(hs_addr + 4u);
    snprintf(hs_p(0x005fe5d4u), 0x20, "%s: %s", str_at(0xd4), nm ? nm : "");
    hs_time(hs_p(0x005fe698u), hs_rec(hs_addr), 1);
    a3 = hs_a(0x005fe5d4u); a4 = hs_a(0x005fe698u);
    break; }
  default: return;
  }
  hs_set(0x0054be90u, a0); hs_set(0x0054bea0u, a1); hs_set(0x0054beb0u, a2); hs_set(0x0054bec0u, a3); hs_set(0x0054bed0u, a4);
  snprintf(hs_p(HS_BUF0), 0x40, "%s %s", str_at(title_str), str_at(title2_str));
  hs_set(0x0054bd10u, hs_a(HS_BUF0));
  hs_set(0x0054be80u, P97_StrAddr[0x1a]);
  hs_set(0x0054be60u, P97_StrAddr[0x1b]);
  uint32_t hs_addr = (uint32_t)P42_GetHighScore(UiVar0054BF18, level);
  for (int32_t rank = 0; rank < 5; rank++, hs_addr += 0x2cu) {
    const uint8_t *rec = hs_rec(hs_addr);
    uint32_t row = 0x0054bd10u + (uint32_t)rank * 0x40u;
    uint32_t txt_a = 0x005fe534u + (uint32_t)rank * 0x20u;
    hs_set(row + 0x20, hs_addr + 4u);
    hs_set(row + 0x30, hs_a(0x005fe6f4u));
    if (time_col == 0) {
      if (rd32(rec + 0x18) == 8) snprintf(hs_p(txt_a), 0x20, UiVar0054BF18 == 7 ? "$%d" : "%d", rd32(rec + 0x10));
      else snprintf(hs_p(txt_a), 0x20, "-");
    } else hs_time(hs_p(txt_a), rec, 0);
    hs_set(row + 0x40, hs_a(txt_a));
    if (score_col != 0) {
      if (rd32(rec + 0x18) == 8) {
        uint32_t txt_b = 0x005fe5f4u + (uint32_t)rank * 0x20u;
        snprintf(hs_p(txt_b), 0x20, "%d", rd32(rec + 0x10));
        hs_set(row + 0x30, hs_a(txt_b));
      } else hs_set(row + 0x30, 0x0054bf8cu);
    }
  }
}
