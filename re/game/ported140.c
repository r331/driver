/* Save game, key names, front-end main loop, the MLADDER story interpreter (campaign flow), WAV
   sample loading and sound init, sound bank lines, and the helicopter marker flight.
   English summary; the Russian notes below give every address. */
/* v1.85: ported140 — см. ported140.h.
   00405d60 — запись сохранения 012852a0 (0x38): имя, уровень/номер/A/B/Y (012852b0..c0 = P68_Saved), сумма 0040682d → заголовок
     0057b6b0 {0x57231356, сумма}; _mkdir("SAVES"), SAVES\GAME%d.BIN "wb": 8 + 0x38.
   0040ec30 — KEYS.<ENG|FRE|GER|SPA|ITA|USA> (00c557fc вне 0..5 → 0) "r": весь файл в буфер (gvars.c:0xeb), 0x21 строка: печатные
     символы до '\n', не длиннее 15 → 0054b4b4 + i·0x10; адреса строк в таблицу 0054b080 (скан-коды 0x1c, 0x1d, 0x2a, …).
   004127f0 — 0040ec30, заставки (USCOPYRIGHT при языке 5, иначе COPYRIGHT; GT; REFLECT) по 4 очистки, 0048a940(00bdf9c0, 0, −1),
     0040bf50 = 0 → 0040c165; иначе меню 0054cc90 (ожидание 0054cb98/0054cc50) с меню выхода 0054cd20 (1 — выход: 0040cd17,
     0040c165, 00405bfa); 00bdf9cc = 0 — 004d78f3(0) без шага меню; 005d577c > 0x2c — 004129df(−1).
   0041b3ab — записи MLADDER 0x10 {код, a, следующая, иначе} по 01271048: 0 — уровень, 1 — выбор 0041b7d1 из строк 01271044 + a·0x20,
     2 — игра 0040c20b(0) (режим 9), 3 — 0048a940, 4/5 — флаги 0127104c, 6/9 — проверка 00c810c4 = 0xff0, 0xb — тренировка,
     0xc — титры (CREDITS, повтор); 1/2 сохраняют состояние в 012852b0..c0; выход — при GameMode = 1, нулевом адресе, коде вне списка.
   0048bf9a — без 00b1f420 — −1; "rb": размер, 0x12 байт заголовка с +0x18, образ (directsound.c:0x1c4) → 0048c192 → 00b1c9a0 + n·0x88,
     имя (< 0x80) в +8; при 00b91d30 — 0048cad6 и 0048cba4. Успех — dword заголовка +0x1c (у Ghidra — «неинициализированная» локаль
     поверх буфера чтения, проверено по ассемблеру: [ebp−0x1c] внутри 0x12 байт с [ebp−0x20]).
   005233be — 00523595 при 00b91cf4; номер ≥ 00b91d2c → 0; сброс затухания, 00bdc880 (0x280), 00bdc2a0 (0x410), 00b91bc4 (0x40),
     00b91c08..1c; громкость 00b87f80[i] = ftol(log10(i / 10000.0) · 2000.0) в −10000..0; 0048ba31 = 0 → лог, 0; иначе 00bdcb1c(0.15f), 1.
   00524bd8 — _strupr строки, имя до пробела → 00bdcb24(n, имя); −1 — лог, флаг 4; иначе флаги 0, громкость 0, приоритет 8,
     /LOOP | 1, /2D | 2, /FREQ= (+0), /VOL= (+4), /PRI= (+7) через 00524e22; 00b91d34++.
   004e9bbf — при 00b5a778 = 0: полёт маркера (тяга к машине игрока по курсу, поворот sin/cos 00b94280/00b95280, ограничения
     45/−50, 390 − высота, 230; счётчик ударов 00d02750 >> 6); удар > 0x4f или крен/тангаж машины 0x200..0xe00 — сбит: звук 3,
     режим 9, точка падения через 005289e2 по 01135060, 00c810c4 = 0xff0; сбитый — 004e919d; дым 004b8f4e при 0x28 < удар.
   Отступления native: 00405d60/0041b3ab — 012852b0..c0 пишутся и в P68_Saved, и в P56_SaveBuf + 0x10; 0040ec30 — таблица 0054b080
     в native только из записанных адресов (остальные 0), строки 0054b4b4 — массив с инициализатором из .data (tools/gen_p140_data.py),
     область в re_ptr регистрируется один раз; 00524bd8 — имя ограничено 0xff, драйвер 00bdcb24 в native — прямой вызов 0048bf9a
     (P140_SndLoadWav, указатель на стек не переживает int32); 0041b3ab — запись по нулевому/незарегистрированному адресу — выход;
     004e9bbf — 01137380 ← 00b1c268..6f по uint16 (P59_AngA/B/C, четвёртое слово — без native-имени, сохраняется). */
#include <stdlib.h>
#include "ported150.h"
#include "ported140.h"
#include "carfields.h"
#include "ported148.h"
#include <string.h>
#include <stdio.h>
#include <math.h>
#include "crt.h"
#include "reptr.h"
#include "cartab.h"
#include "unported.h"
#include "p140_data.h"
#include "menustate.h"
#include "smallfuncs.h"
#include "smallfuncs2.h"
#include "uihandlers.h"
#include "uihandlers3.h"
#include "uihandlers4.h"
#include "director.h"
#include "ported4.h"
#include "ported6.h"
#include "ported7.h"
#include "ported8.h"
#include "ported11.h"
#include "ported12.h"
#include "ported13.h"
#include "ported14.h"
#include "ported16.h"
#include "ported17.h"
#include "ported19.h"
#include "ported21.h"
#include "ported31.h"
#include "ported36.h"
#include "ported38.h"
#include "ported43.h"
#include "ported44.h"
#include "ported45.h"
#include "ported48.h"
#include "ported50.h"
#include "ported54.h"
#include "ported55.h"
#include "ported56.h"
#include "ported57.h"
#include "ported58.h"
#include "ported59.h"
#include "ported62.h"
#include "ported68.h"
#include "ported76.h"
#include "ported97.h"
#include "ported98.h"
#include "ported99.h"
#include "ported118.h"
#include "ported114.h"
#include "ported119.h"
#include "ported124.h"
#include "ported126.h"
#include "ported131.h"
#include "ported133.h"
#include "ported136.h"
#include "ported138.h"
#include "ported139.h"
#ifndef RE_HOOK_BUILD
#  include <sys/stat.h>
#  ifdef _WIN32
#    include <direct.h>
#  endif
/* re_crt_mkdir — Native CRT _mkdir (backslashes converted to '/' outside Windows). */
int re_crt_mkdir(const char *path) {
#  ifdef _WIN32
  return _mkdir(path);
#  else
  char np[1024]; plat_path_native(path, np, sizeof np);   /* v2.00: '\\' → '/' */
  return mkdir(np, 0777);
#  endif
}
#pragma push_macro("P140_KeyStr") /*gvi*/
#undef P140_KeyStr /*gvi*/
p140_keystr_t P140_KeyStr = P140_KEYSTR_INIT;   /* 0054b4b4, .data */
#pragma pop_macro("P140_KeyStr") /*gvi*/
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P140_KeyName")
#undef P140_KeyName
#pragma push_macro("P140_KeyName") /*gvi*/
#undef P140_KeyName /*gvi*/
p140_keyname_t P140_KeyName;
#pragma pop_macro("P140_KeyName") /*gvi*/
#pragma pop_macro("P140_KeyName")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P140_FrSelA")
#undef P140_FrSelA
#pragma push_macro("P140_FrSelA") /*gvi*/
#undef P140_FrSelA /*gvi*/
int32_t P140_FrSelA;
#pragma pop_macro("P140_FrSelA") /*gvi*/
#pragma pop_macro("P140_FrSelA")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P140_FrSelB")
#undef P140_FrSelB
#pragma push_macro("P140_FrSelB") /*gvi*/
#undef P140_FrSelB /*gvi*/
int32_t P140_FrSelB;
#pragma pop_macro("P140_FrSelB") /*gvi*/
#pragma pop_macro("P140_FrSelB")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P140_FrQuit")
#undef P140_FrQuit
#pragma push_macro("P140_FrQuit") /*gvi*/
#undef P140_FrQuit /*gvi*/
int32_t P140_FrQuit;
#pragma pop_macro("P140_FrQuit") /*gvi*/
#pragma pop_macro("P140_FrQuit")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P140_B91BC0")
#undef P140_B91BC0
#pragma push_macro("P140_B91BC0") /*gvi*/
#undef P140_B91BC0 /*gvi*/
int32_t P140_B91BC0;
#pragma pop_macro("P140_B91BC0") /*gvi*/
#pragma pop_macro("P140_B91BC0")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P140_B1F434")
#undef P140_B1F434
#pragma push_macro("P140_B1F434") /*gvi*/
#undef P140_B1F434 /*gvi*/
int32_t P140_B1F434;
#pragma pop_macro("P140_B1F434") /*gvi*/
#pragma pop_macro("P140_B1F434")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P140_Mrk2644")
#undef P140_Mrk2644
#pragma push_macro("P140_Mrk2644") /*gvi*/
#undef P140_Mrk2644 /*gvi*/
int32_t P140_Mrk2644;
#pragma pop_macro("P140_Mrk2644") /*gvi*/
#pragma pop_macro("P140_Mrk2644")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P140_MrkVel")
#undef P140_MrkVel
#pragma push_macro("P140_MrkVel") /*gvi*/
#undef P140_MrkVel /*gvi*/
p140_f3_t P140_MrkVel;
#pragma pop_macro("P140_MrkVel") /*gvi*/
#pragma pop_macro("P140_MrkVel")
#endif
#endif

/* rd32 — Unaligned uint32 read. */
static uint32_t rd32(const uint8_t *p) { uint32_t v; memcpy(&v, p, 4); return v; }

/* 012852b0..c0: состояние для возврата (уровень, номер записи, A, B, Y) */
/* save_state — Copy the campaign position (level, ladder record index, chapter, story flags 0127104c, 00b87e54)
   into P68_Saved (012852b0..c0) for saving / returning. */
static void save_state(void) {
  P68_Saved[0] = P19_Level;
  P68_Saved[1] = (int32_t)(P68_IntroCur - P68_IntroBase) >> 4;
  P68_Saved[2] = P68_IntroA;
  P68_Saved[3] = (int32_t)S_0127104C;
  P68_Saved[4] = P68_B87E54;
#ifndef RE_HOOK_BUILD
  memcpy((uint8_t *)P56_SaveBuf + 0x10, P68_Saved, sizeof(P68_SaveArr));   /* native-псевдоним внутри 012852a0 */
#endif
}

/* ---- 00405d60 ---- */
/* P140_SaveGame — Game.exe 00405d60, cdecl.  Write SAVES\GAME<slot+1>.BIN: 8-byte header {0x57231356, checksum} + 0x38-byte record (name up
   to 15 characters + the campaign position).  Creates SAVES if needed. */
void P140_SaveGame(int32_t slot, const char *name) {
  char path[0x100];
  memset(P56_SaveBuf, 0, 0x38);
  if (name != NULL) { size_t n = strlen(name); if (n > 0x0f) n = 0x0f; memcpy(P56_SaveBuf, name, n); }
  save_state();
  int32_t sum = SumBytes((const uint8_t *)P56_SaveBuf, 0x38);
  memset(P56_SaveHdr, 0, 8);
  P56_SaveHdr[0] = 0x57231356u;
  P56_SaveHdr[1] = (uint32_t)sum;
  g_mkdir("SAVES");
  snprintf(path, sizeof path, "SAVES\\GAME%d.BIN", slot + 1);
  void *f = g_fopen(path, "wb");
  if (f != NULL) {
    g_fwrite(P56_SaveHdr, 1, 8, f);
    g_fwrite(P56_SaveBuf, 1, 0x38, f);
    g_fclose(f);
  }
}

/* ---- 0040ec30 ---- */
static const char *const k_lang[6] = { "ENG", "FRE", "GER", "SPA", "ITA", "USA" };
/* таблица 0054b080: смещение указателя → номер строки 0054b4b4 */
static const uint16_t k_keyptr[][2] = {
  { 0x080, 0 }, { 0x084, 1 }, { 0x0b8, 2 }, { 0x0e8, 3 }, { 0x0ec, 4 }, { 0x0f0, 5 }, { 0x0f4, 6 }, { 0x124, 7 },
  { 0x12c, 8 }, { 0x130, 9 }, { 0x134, 10 }, { 0x138, 11 }, { 0x13c, 12 }, { 0x140, 13 }, { 0x144, 14 }, { 0x148, 15 },
  { 0x14c, 16 }, { 0x150, 17 }, { 0x154, 18 }, { 0x158, 19 }, { 0x15c, 20 }, { 0x244, 21 }, { 0x280, 22 }, { 0x284, 23 },
  { 0x2dc, 24 }, { 0x2e4, 25 }, { 0x2f0, 26 }, { 0x330, 27 }, { 0x33c, 28 }, { 0x344, 29 }, { 0x350, 30 }, { 0x490, 27 },
  { 0x494, 30 }, { 0x498, 32 } };
static int g_regkeys;
/* P140_KeysLoad — Game.exe 0040ec30, cdecl.  Load key names from KEYS.<ENG|FRE|GER|SPA|ITA|USA> (language 00c557fc, out-of-range -> English):
   0x21 lines of printable text (max 15 characters) into P140_KeyStr, and the per-DIK-code name
   pointers P140_KeyName. */
void P140_KeysLoad(void) {
  char path[0x100];
  int32_t len = 0;
  if (P55_Lang < 0 || 5 < P55_Lang) { P55_Lang = 0; P58_LangNo = 0; }
  snprintf(path, sizeof path, "KEYS.%s", k_lang[P55_Lang]);
  void *f = g_fopen(path, "r");
  if (f == NULL) return;
  g_fseek(f, 0, 2);
  len = (int32_t)g_ftell(f);
  g_fseek(f, 0, 0);
  if (len < 0) { g_fclose(f); return; }
  uint8_t *buf = (uint8_t *)P98_DebugMalloc(len + 1, "D:\\Driver\\Game\\frontend\\gvars.c", 0xeb);
  if (buf == NULL) { g_fclose(f); return; }
  size_t got = g_fread(buf, 1, (size_t)len, f);
  g_fclose(f);
  if (got < (size_t)len) memset(buf + got, 0, (size_t)len - got);
  buf[len] = 0;
  uint8_t *p = buf;
  for (int c = 0; c < 0x21; c++) {
    if (0 < len) {
      uint8_t *s = p, *last = p;
      do {
        if (*p == 10) break;
        if (0x1f < *p) last = p + 1;
        len--; p++;
      } while (1 < len);
      *last = 0;
      size_t n = strlen((const char *)s);
      if (0xf < n) n = 0xf;
      memcpy(P140_KeyStr + c * 0x10, s, n);
      P140_KeyStr[n + c * 0x10] = 0;
      p++; len--;
    }
  }
  P98_DebugFree(buf);
#ifndef RE_HOOK_BUILD
  if (!g_regkeys) { re_ptr_register(P140_KEYSTR_ADDR, P140_KeyStr, sizeof(p140_keystr_t)); g_regkeys = 1; }
  const uint32_t base = P140_KEYSTR_ADDR;
#else
  const uint32_t base = (uint32_t)(uintptr_t)P140_KeyStr;
  (void)g_regkeys;
#endif
  for (size_t i = 0; i < sizeof k_keyptr / sizeof k_keyptr[0]; i++)
    P140_KeyName[(k_keyptr[i][0] - 0x80u) / 4] = base + (uint32_t)k_keyptr[i][1] * 0x10u;   /* v2.00: смещения от 0054b000 (индекс = скан-код DIK); раньше писало за таблицу 0054b080 (до 0054b518) и в hook */
}

/* ---- 004127f0 ---- */
/* set_menu_mode — Write the menu mode 01271060 and all its aliases. */
static void set_menu_mode(int32_t v) {
  MenuMode1271060 = v; P11_01271060 = v; P62_Menu1271060 = v; G01271060 = v;
#ifndef RE_HOOK_BUILD
  P56_Blk11[0] = (uint32_t)v;
#endif
}
/* set_counter — Write the front-end idle counter 005d577c and its aliases. */
static void set_counter(int32_t v) { MenuCounter5D577C = v; D_005d577c = v; G005D577C = v; }
/* P140_Frontend — Game.exe 004127f0, cdecl.  Front end: key names, the three splash pictures (COPYRIGHT / USCOPYRIGHT, GT, REFLECT), intro
   FMV, front-end init, then the main menu loop (table 0054cc90) with the quit confirmation menu
   (0054cd20); quitting saves config.dat.  While the window is inactive only the clock runs; after
   0x2c idle ticks 004129df(-1) runs (attract mode, inferred).  `unused` is the ECX of Ghidra's
   __fastcall signature. */
void P140_Frontend(int32_t unused) {
  (void)unused;
  P140_KeysLoad();
  P54_ClearSwap(4);
  P126_ShowBmpFade(P55_Lang == 5 ? "DATA\\USCOPYRIGHT.BMP" : "DATA\\COPYRIGHT.BMP", 5);
  P54_ClearSwap(4);
  P126_ShowBmpFade("DATA\\GT.BMP", 5);
  P54_ClearSwap(4);
  P126_ShowBmpFade("DATA\\REFLECT.BMP", 5);
  P150_PlayFmv(G6_00BDF9C0, 0, -1);
  if (P136_FrontInit() == 0) { P56_ResetFrontend(); return; }
  set_menu_mode(0);
  P140_FrSelA = 0;
  P97_MenuCall0(0x0054cc90u, 0);
  P45_Wait(0x0054cb98u, 0x0054cc50u);
  for (;;) {
    Call00522323();
    P36_PollInput();
    if (P31_Active == 0) { set_counter(0); P21_FrameTicks(); continue; }
    if (0x2c < MenuCounter5D577C) P12_Fn004129DF(-1);
    if (P140_FrQuit == 0) {
      int32_t r = P114_MenuStep(0x0054cc90u, &P140_FrSelA);
      if (r == -1) {
        P140_FrQuit = 1; P140_FrSelB = 0;
        P99_MenuDim(1);
        P97_MenuCall0(0x0054cd20u, P140_FrSelB);
      } else if (r == 1) {
        P45_Wait(0x0054cb98u, 0x0054cc50u);
      }
    } else {
      int32_t r = P114_MenuStep(0x0054cd20u, &P140_FrSelB);
      if (r == 1) { P57_MenuDone(); P56_ResetFrontend(); P58_SaveConfig(); return; }
      if (r == -1) { P140_FrQuit = 0; P99_MenuDim(0); P97_MenuCall0(0x0054cc90u, P140_FrSelA); }
    }
    set_menu_mode(0);
    P119_MenuFrame();
  }
}

/* ---- 0041b3ab ---- */
/* set_level — Write the highest unlocked level 00575ef0 and its aliases. */
static void set_level(int32_t v) { MenuState575EF0 = v; P19_Level = v; P58_Page = v; G00575EF0 = v; }
/* set_e38 — Write the mission number 00b87e38 and its aliases. */
static void set_e38(int32_t v) { P11_00b87e38 = v; P17_Cond2 = v; P19_Cond = v; P45_Mode = v; UiVar00B87E38 = v; }
/* set_1dc — Write 00b201dc and its aliases. */
static void set_1dc(int32_t v) { MenuVarB201DC = v; P13_00b201dc = v; G00B201DC = v; }
/* set_ea0 — Write 00b87ea0 (training/interview flag) and P62_HudOff1. */
static void set_ea0(int32_t v) { G6_00B87EA0 = v; P62_HudOff1 = v; }
/* set_e5c — Write 005f7e5c and its alias. */
static void set_e5c(int32_t v) { P12_005f7e5c = v; P58_S5F7E5C = v; }
/* set_c4 — Write 00c810c4 (mission result, see C4_FAILED) and its aliases. */
static void set_c4(int32_t v) {
  P14_00c810c4 = v; P16_IdleMode = v;
#ifndef RE_HOOK_BUILD
  P56_Blk84[1] = (uint32_t)v;
#endif
}
#include "ladder.h"   /* MLADDER record codes LAD_* */
#include "missionstate.h"
#define C4_FAILED MSTATE_FAILED   /* 00c810c4 "mission failed" (missionstate.h); the marker shot down gives reason 1 */

/* P140_LadderRun — Game.exe 0041b3ab, cdecl.  Run the MLADDER campaign script from record P68_IntroCur until it returns to the menu: each
   record {code, a, next, else} (LAD_* in ladder.h) unlocks levels, shows choice screens, plays missions
   or cut-scenes, tests story flags or the last mission's result, runs the interview or credits.
   Stops on a NULL/unregistered record address, an unknown code, or when GameMode becomes 1
   (quit).  Native: RE_SKIP_INTERVIEW=1 acts like the skip-interview cheat. */
void P140_LadderRun(void) {
  for (;;) {
    const uint8_t *rec = (const uint8_t *)re_ptr(P68_IntroCur);
    if (rec == NULL) return;
    uint32_t a = rd32(rec + 4);
    switch (rd32(rec)) {
    case LAD_SETCITY:
      P68_IntroA = (int32_t)a;
      if (P19_Level < P68_IntroA + 1) { set_level(P68_IntroA + 1); P58_SaveConfig(); }
      P68_IntroCur = rd32(rec + 8);
      break;
    case LAD_ROOM:
      save_state();
      D_00b87e30 = P68_IntroA;
      P68_IntroCur = P131_MenuPick(P139_IntroStr + a * 0x20u);
      if (P68_IntroCur == 0) return;
      break;
    case LAD_MISSION:
      save_state();
      D_00b87e30 = P68_IntroA;
      set_e38((int32_t)a);
      set_menu_mode(9);
      P136_GameLoop(0);
      if (GameMode == 1) return;
      rec = (const uint8_t *)re_ptr(P68_IntroCur);
      if (rec == NULL) return;
      P68_IntroCur = rd32(rec + 8);
      break;
    case LAD_RENDER:
      P150_PlayFmv(G6_00BDF9C0, (int32_t)a, -1);
      P68_IntroCur = rd32(rec + 8);
      break;
    case LAD_TRIGGER:
      FlagSet0127104C((uint8_t)a);
      P68_IntroCur = rd32(rec + 8);
      break;
    case LAD_IF:
      P68_IntroCur = TestBit0041B7AD(a) == 0 ? rd32(rec + 0xc) : rd32(rec + 8);
      break;
    case LAD_IFOK:
      P68_IntroCur = P14_00c810c4 == C4_FAILED ? rd32(rec + 0xc) : rd32(rec + 8);
      break;
    case LAD_ENDIF:
      P68_IntroCur = rd32(rec + 8);
      break;
    case LAD_QUITONFAIL:
      if (P14_00c810c4 == C4_FAILED) return;
      P68_IntroCur = rd32(rec + 8);
      break;
    case LAD_INTERVIEW:
#ifndef RE_HOOK_BUILD
      /* v2.11: RE_SKIP_INTERVIEW=1 — отладка: как чит 00b87e9c (пункт 5 меню Cheats, при 00bdf9fc ≠ 0) — интервью пропускается */
      if (getenv("RE_SKIP_INTERVIEW") != NULL) MenuOptB87E9C = 1;
#endif
      if (MenuOptB87E9C == 0) {
        D_00b87e30 = 4; set_e38(0); set_ea0(0); P62_HudOff2 = 1; set_1dc(1); P14_00b87e84 = 1;
        P136_GameLoop(0);
        D_00b87e30 = 0; set_e38(0); P62_HudOff2 = 0; set_1dc(0); P14_00b87e84 = 0;
        P133_LoadConfig();
        if (GameMode == 1) return;
      } else {
        set_c4(0x8000);
      }
      rec = (const uint8_t *)re_ptr(P68_IntroCur);
      if (rec == NULL) return;
      P68_IntroCur = rd32(rec + 8);
      break;
    case LAD_END:
      P12_00b87ef8 = 1; set_e5c(1);
      P138_ReplayCfg("CREDITS");
      P136_GameLoop(1);
      set_e5c(0); P12_00b87ef8 = 0;
      P58_CheatsAll();
      P58_SaveConfig();
      rec = (const uint8_t *)re_ptr(P68_IntroCur);
      if (rec == NULL) return;
      P68_IntroCur = rd32(rec + 8);
      break;
    default:
      return;
    }
  }
}

/* ---- 0048bf9a ---- */
/* P140_SndLoadWav — Game.exe 0048bf9a, cdecl.  Load WAV file `path` into DirectSound voice n (buffer via P148_BufFromWav, EAX properties when
   enabled; the file name is kept in the voice).  Returns the dword at file offset 0x1c
   (nAvgBytesPerSec, used as the sample's frequency field), or -1 on error / no DirectSound. */
int32_t P140_SndLoadWav(int32_t n, const char *path) {
  uint8_t hdr[0x14];
  if (P38_Ds == NULL) return -1;
  void *f = g_fopen(path, "rb");
  if (f == NULL) return -1;
  g_fseek(f, 0, 2);
  int32_t size = (int32_t)g_ftell(f);
  if (size == -1) { g_fclose(f); return -1; }
  memset(hdr, 0, sizeof hdr);
  g_fseek(f, 0x18, 0);
  g_fread(hdr, 1, 0x12, f);
  g_fseek(f, 0, 0);
  void *buf = P98_DebugMalloc(size, "D:\\Driver\\Game\\eax\\directsound.c", 0x1c4);
  if (buf == NULL) { g_fclose(f); return -1; }
  g_fread(buf, 1, (size_t)size, f);
  g_fclose(f);
  P50_Voice *v = &P50_Voices[n];
  v->a = P148_BufFromWav(P38_Ds, buf, P140_B1F434);
  P98_DebugFree(buf);
  if (v->a == NULL) return -1;
  if (strlen(path) < 0x80) strcpy((char *)v->rest, path);
  else v->rest[0] = 0;
  if (P48_B91D30 != 0) {
    v->b = P148_KsProps(v->a);
    if (v->b != NULL) P50_EaxSetDefault(v->b);
  }
  return (int32_t)rd32(hdr + 4);
}

/* ---- 005233be ---- */
/* P140_SndInit — Game.exe 005233be, cdecl.  (Re)start sound driver drv: resets fades, sample and channel tables, builds the volume table
   P48_VolTab[i] = 2000 * log10(i / 10000) clamped to -10000..0 (DirectSound hundredths of dB),
   opens the driver and sets the master level 0.15.  Returns 1, or 0 for a bad driver index or
   when the hardware cannot be opened. */
int32_t P140_SndInit(int32_t drv, int32_t arg, int32_t eax) {
  if (G6_00B91CF4 != 0) P48_SndShutdown();
  if (drv < 0 || G6_00B91D2C <= drv) return 0;
  P43_FadeLen = 1.0f;
  P48_B91D30 = eax;
  P43_FadeSteps = 0; P43_FadeA = 0.0f; P43_FadeB = 0; P43_FadeStep = 0.0f;
  memset(P68_Samps, 0, 0x280);
#ifndef RE_HOOK_BUILD
  memset(P48_Samples, 0, 0x280 - 6);   /* native-псевдоним +6/+7 записей 00bdc880 */
  memset(S_00BDC2A0, 0, 0x410);
#endif
  memset(A_00BDC2A0, 0, 0x410);
  memset(G6_00B91BC4, 0, sizeof(g6a_00B91BC4));
  P8_00b91c08 = 0; P8_00b91c0c = 0; P8_00b91c10 = 0; P8_00b91c14 = 0; P8_00b91c18 = 0; P8_00b91c1c = 0;
  P48_VolTab[0] = (uint32_t)-10000;
  for (int32_t i = 1; i < 10000; i++) {
    int32_t v = (int32_t)(log10((double)i / 10000.0) * 2000.0);
    if (v < -10000) v = -10000;
    if (0 < v) v = 0;
    P48_VolTab[i] = (uint32_t)v;
  }
  P140_B91BC0 = 0;
  if (P148_SndOpen(drv, arg, G6_00BDF9C0) == 0) {
    G6_00B91CF4 = 0; G8_00B91CF4 = 0;
    P124_DebugLog("=> Error allocating sound hardware <=");
    return 0;
  }
  if (P97_DrvB != NULL) ((void (*)(float))P97_DrvB)(0.15f);
  G6_00B91CF4 = 1; G8_00B91CF4 = 1;
  return 1;
}

/* ---- 00524bd8 ---- */
/* P140_BankLine — Game.exe 00524bd8, cdecl.  Parse one sound bank line "NAME [/LOOP] [/2D] [/FREQ=n] [/VOL=n] [/PRI=n]" (upper-cased in
   place): load sample 00b91d34 (flags: 1 loop, 2 2D, 4 load error; default priority 8) and
   increment the sample count. */
void P140_BankLine(char *line) {
  char name[0x100];
  int32_t i = 0;
  for (char *c = line; *c; c++) if (*c >= 'a' && *c <= 'z') *c = (char)(*c - 0x20);   /* _strupr */
  for (; line[i] != ' ' && line[i] != 0 && i < 0xff; i++) name[i] = line[i];
  name[i] = 0;
  int32_t n = G6_00B91D34;
#ifdef RE_HOOK_BUILD
  int32_t h = P68_DrvLoad(n, (int32_t)(uintptr_t)name);
#else
  int32_t h = P140_SndLoadWav(n, name);
#endif
  if (n >= 0 && n < 0x400) {
    P68_Samps[n].handle = h;
    if (h == -1) {
      P124_DebugLog("Error while loading sample");
      P48_Samples[n * 8] = 4;
    } else {
      P48_Samples[n * 8] = 0;
      P68_Samps[n].extra = 0;
      P48_Samples[n * 8 + 1] = 8;
      if (strstr(line, "/LOOP") != NULL) P48_Samples[n * 8] |= 1;
      if (strstr(line, "/2D") != NULL) P48_Samples[n * 8] |= 2;
      const char *p;
      if ((p = strstr(line, "/FREQ=")) != NULL) P68_Samps[n].handle = P58_ParseInt((const uint8_t *)p + 6);
      if ((p = strstr(line, "/VOL=")) != NULL) P68_Samps[n].extra = (uint16_t)P58_ParseInt((const uint8_t *)p + 5);
      if ((p = strstr(line, "/PRI=")) != NULL) P48_Samples[n * 8 + 1] = (uint8_t)P58_ParseInt((const uint8_t *)p + 5);
    }
  }
  G6_00B91D34 = n + 1;
}

/* ---- 004e9bbf ---- */
#define CAR0 ((uint8_t *)&P99_Cars[0])
/* c0i — int32 field of the player's car record (P99_Cars[0]). */
static int32_t c0i(uint32_t off) { int32_t v; memcpy(&v, CAR0 + off, 4); return v; }
/* c0w — int16 field of the player's car record. */
static int16_t c0w(uint32_t off) { int16_t v; memcpy(&v, CAR0 + off, 2); return v; }
/* mrk_hit — Stage the marker hit value (P99_Mrk2730 or P99_Mrk2738, rounded) in 00ba52d0 as the original. */
static void mrk_hit(int32_t k) { P11_00ba52d0 = (int32_t)lrintf(k == 0 ? P99_Mrk2730 : P99_Mrk2738); }
/* mrk_smoke — Smoke/skid effect at the marker position. */
static void mrk_smoke(void) {
  P118_SkidFx(P98_MrkPos, 100, 500, 1, c0i(CAR_SPEED), P140_MrkVel, 0);
}
/* P140_MrkFly — Game.exe 004e9bbf, cdecl.  Helicopter marker flight (unless paused): steer towards the player's car along its heading
   with limited climb (45 / -50), keep ~390 above ground; count hits (00d02750 >> 6).  A hit over
   0x4f or the player's car pitched/rolled between 0x200 and 0xe00 shoots it down: sound 3, menu
   mode 9, crash point, result C4_FAILED.  A downed marker falls (004e919d); smoke above 0x28 hits.
   TODO(RE): unsure — "marker" may be the chase target helicopter of specific missions. */
void P140_MrkFly(void) {
  if (G6_00B5A778 != 0) return;
  if (P98_MrkOff == 0) {
    float dx = (float)c0i(CAR_VEL) - P99_Mrk2760;
    float dy = (float)c0i(CAR_VEL + 4) - P99_Mrk2764;
    float dz = (float)c0i(CAR_VEL + 8) - P99_Mrk2768;
    P99_Mrk2760 = (float)c0i(CAR_VEL); P99_Mrk2764 = (float)c0i(CAR_VEL + 4); P99_Mrk2768 = (float)c0i(CAR_VEL + 8);
    uint32_t u = (uint32_t)(c0i(CAR_HEADING) - 0x400) & 0xfff;
    float sn = P43_Sin[u], cs = P43_Sin[0x400 + u];
    float a = cs * dz + sn * dx;
    float b = sn * dz + -dx * cs;
    float d = (float)sqrt((double)(b * b + a * a));
    float v = (float)sqrt((double)(P99_Mrk2738 * P99_Mrk2738 + P99_Mrk2730 * P99_Mrk2730));
    if (v == 0.0f) {
      if (d <= 7500.0f) { P140_Mrk2748 = 0.0f; P140_Mrk2740 = 0.0f; }
      else { P140_Mrk2740 = (a * (7500.0f - d)) / d; P140_Mrk2748 = (b * (7500.0f - d)) / d; }
    } else {
      P140_Mrk2740 = (-P99_Mrk2730 * 7500.0f) / v - a;
      P140_Mrk2748 = (-P99_Mrk2738 * 7500.0f) / v - b;
    }
    if (P98_MrkSrc[1] < 0.0f) {
      P140_Mrk2744 = 3000.0f;
    } else {
      P98_MrkSrc[1] = 0.0f;
      if (-dy <= 3000.0f) P140_Mrk2744 = 0.0f;
      else P140_Mrk2744 = 3000.0f + dy;
    }
    if (3000.0f < P140_Mrk2740 + P140_Mrk2748) P99_Mrk2750 = P99_Mrk2750 + 1;
    int sx = !signbit(P99_Mrk2730), nzx = P99_Mrk2730 != 0.0f;
    int sz = !signbit(P99_Mrk2738), nzz = P99_Mrk2738 != 0.0f;
    P99_Mrk2730 = P140_Mrk2740 / 4500.0f + P99_Mrk2730;
    P99_Mrk2734 = P140_Mrk2744 / 800.0f + P99_Mrk2734;
    P99_Mrk2738 = P140_Mrk2748 / 4500.0f + P99_Mrk2738;
    if (signbit(P99_Mrk2730)) sx = !sx;
    if (signbit(P99_Mrk2738)) sz = !sz;
    if (!sx && nzx) P99_Mrk2730 = 0.0f;
    if (!sz && nzz) P99_Mrk2738 = 0.0f;
    P98_MrkSrc[0] = P98_MrkSrc[0] + P99_Mrk2730;
    P98_MrkSrc[1] = P98_MrkSrc[1] + P99_Mrk2734;
    P98_MrkSrc[2] = P98_MrkSrc[2] + P99_Mrk2738;
    float top = 390.0f - (float)((c0i(CAR_DAMAGE + 0xc) + c0i(CAR_DAMAGE + 0x10)) >> 6);
    if (45.0f < P98_MrkSrc[0]) {
      P98_MrkSrc[0] = 45.0f; mrk_hit(0); P99_Mrk2750 = P99_Mrk2750 + P11_00ba52d0 * 5; P99_Mrk2730 = 0.0f;
    }
    if (P98_MrkSrc[0] < -50.0f) {
      P98_MrkSrc[0] = -50.0f; mrk_hit(0); P99_Mrk2750 = P99_Mrk2750 + P11_00ba52d0 * -5; P99_Mrk2730 = 0.0f;
    }
    if (top < P98_MrkSrc[2]) {
      mrk_hit(1); P99_Mrk2750 = P99_Mrk2750 + P11_00ba52d0 * 5; P99_Mrk2738 = 0.0f; P98_MrkSrc[2] = top;
    }
    if (P98_MrkSrc[2] < 230.0f) {
      P98_MrkSrc[2] = 230.0f; mrk_hit(1); P99_Mrk2750 = P99_Mrk2750 + P11_00ba52d0 * -5; P99_Mrk2738 = 0.0f;
    }
    P99_MrkA = P99_Mrk2750 >> 6;
    int32_t rx = c0w(CAR_ANG), rz = c0w(CAR_ANG + 4);
    if (0x4f < P99_MrkA || (0x200 < rx && rx < 0xe00) || (0x200 < rz && rz < 0xe00)) {
      P97_SndStart(3, 3, P98_MrkPos[0], P98_MrkPos[1], P98_MrkPos[2]);
      P99_MrkA = 0x50;
      P140_Mrk2644 = 1;
      P98_MrkOff = 1;
      P59_Mode1137324 = 9;
      G2_01137324 = (G2_01137324 & ~0xff) | 9;
      P131_CamAng[0] = P59_AngA; P131_CamAng[1] = P59_AngB; P131_CamAng[2] = P59_AngC;
#ifdef RE_HOOK_BUILD
      memcpy(&P131_CamAng[3], (const void *)(uintptr_t)0x00b1c26eu, 2);
#endif
      for (uint32_t k = 0; k < 6; k++) { int32_t w = 0x1000; memcpy(CAR0 + 0x11c + k * 4, &w, 4); }
      float o[3] = { P98_MrkSrc[0], P98_MrkSrc[1] - 100.0f, P98_MrkSrc[2] };
      memcpy(P76_ColObj, o, sizeof o);
      P44_MatPtr = (float *)P98_CarMat;   /* 00bdc28c = 01135060 (v2.35: P11_00bdc28c is a view of P44_MatPtr in native) */
      P44_XformT((float *)P76_ColObj);
      memcpy(o, P76_ColObj, sizeof o);
      o[0] = o[0] + (float)c0i(CAR_POS_X);
      o[1] = o[1] + (float)-c0i(CAR_POS_Y);
      o[2] = o[2] + (float)c0i(CAR_POS_Z);
      memcpy(P76_ColObj, o, sizeof o);
      set_c4(C4_FAILED);
      P14_00c810e8 = 1; P14_00c81100 = 0xb4;
#ifndef RE_HOOK_BUILD
      P56_Blk84[(0x00c810e8 - 0x00c810c0) / 4] = 1; P56_Blk84[(0x00c81100 - 0x00c810c0) / 4] = 0xb4;
#endif
    }
  } else {
    P140_Mrk2644 = 0;
    P76_Angle = P76_Angle + 2;
    P99_Mrk2664 = (P99_Mrk2664 + 2) & 0xfff;
    P99_Mrk2660 = (P99_Mrk2660 + 3) & 0xfff;
    P126_DropScan(0);
  }
  if (0x28 < P99_MrkA) {
    if (P99_MrkA < 0x37) { if ((P62_Frame & 6) == 6) mrk_smoke(); }
    else if (P99_MrkA < 0x46) { if ((P62_Frame & 2) != 0) mrk_smoke(); }
    else mrk_smoke();
  }
}
