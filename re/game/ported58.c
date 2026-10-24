/* ported58.c — front-end and level helpers (English overview; original notes follow): menu screen loops and
   switches, cheat codes, item drawing, freeing level lists, demo playback, language strings, logo /
   backgrounds, save-slot names, config.dat, text width. */
#include "ported138.h"
#include "ported58.h"
#include "ported116.h"
#include "crt.h"
#include <string.h>
#include <stdio.h>
#include "menustate.h"
#include "ported102.h"
#include "ported98.h"

#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P58_MenuSel")
#undef P58_MenuSel
#pragma push_macro("P58_MenuSel") /*gvi*/
#undef P58_MenuSel /*gvi*/
int32_t P58_MenuSel;
#pragma pop_macro("P58_MenuSel") /*gvi*/
#pragma pop_macro("P58_MenuSel")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P58_MenuFn")
#undef P58_MenuFn
#pragma push_macro("P58_MenuFn") /*gvi*/
#undef P58_MenuFn /*gvi*/
int32_t P58_MenuFn;
#pragma pop_macro("P58_MenuFn") /*gvi*/
#pragma pop_macro("P58_MenuFn")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P58_MenuIdx")
#undef P58_MenuIdx
#pragma push_macro("P58_MenuIdx") /*gvi*/
#undef P58_MenuIdx /*gvi*/
int32_t P58_MenuIdx;
#pragma pop_macro("P58_MenuIdx") /*gvi*/
#pragma pop_macro("P58_MenuIdx")
#endif
GAME_VAR_DEF(p58_cheats_t, P58_Cheats, 0x00000000)
GAME_VAR_DEF(int16_t *, P58_ItemList, 0x005f7e64)
GAME_VAR_DEF(p58_rec_t *, P58_Tab4EFC03, 0x00b31ee8)
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P58_Cnt4EFC03")
#undef P58_Cnt4EFC03
#pragma push_macro("P58_Cnt4EFC03") /*gvi*/
#undef P58_Cnt4EFC03 /*gvi*/
int32_t P58_Cnt4EFC03;
#pragma pop_macro("P58_Cnt4EFC03") /*gvi*/
#pragma pop_macro("P58_Cnt4EFC03")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P58_CntC814E8")
#undef P58_CntC814E8
#pragma push_macro("P58_CntC814E8") /*gvi*/
#undef P58_CntC814E8 /*gvi*/
int32_t P58_CntC814E8;
#pragma pop_macro("P58_CntC814E8") /*gvi*/
#pragma pop_macro("P58_CntC814E8")
#endif
GAME_VAR_DEF(void **, P58_PtrsC816A0, 0x00c816a0)
GAME_VAR_DEF(int32_t *, P58_LimC810AC, 0x00c810ac)
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P58_S5FEA88")
#undef P58_S5FEA88
#pragma push_macro("P58_S5FEA88") /*gvi*/
#undef P58_S5FEA88 /*gvi*/
int32_t P58_S5FEA88;
#pragma pop_macro("P58_S5FEA88") /*gvi*/
#pragma pop_macro("P58_S5FEA88")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P58_S5FEA8C")
#undef P58_S5FEA8C
#pragma push_macro("P58_S5FEA8C") /*gvi*/
#undef P58_S5FEA8C /*gvi*/
int32_t P58_S5FEA8C;
#pragma pop_macro("P58_S5FEA8C") /*gvi*/
#pragma pop_macro("P58_S5FEA8C")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P58_S5FEA7C")
#undef P58_S5FEA7C
#pragma push_macro("P58_S5FEA7C") /*gvi*/
#undef P58_S5FEA7C /*gvi*/
int32_t P58_S5FEA7C;
#pragma pop_macro("P58_S5FEA7C") /*gvi*/
#pragma pop_macro("P58_S5FEA7C")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P58_S5FEA80")
#undef P58_S5FEA80
#pragma push_macro("P58_S5FEA80") /*gvi*/
#undef P58_S5FEA80 /*gvi*/
int32_t P58_S5FEA80;
#pragma pop_macro("P58_S5FEA80") /*gvi*/
#pragma pop_macro("P58_S5FEA80")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P58_S54E654")
#undef P58_S54E654
#pragma push_macro("P58_S54E654") /*gvi*/
#undef P58_S54E654 /*gvi*/
int32_t P58_S54E654;
#pragma pop_macro("P58_S54E654") /*gvi*/
#pragma pop_macro("P58_S54E654")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P58_S5FE9C0")
#undef P58_S5FE9C0
#pragma push_macro("P58_S5FE9C0") /*gvi*/
#undef P58_S5FE9C0 /*gvi*/
int32_t P58_S5FE9C0;
#pragma pop_macro("P58_S5FE9C0") /*gvi*/
#pragma pop_macro("P58_S5FE9C0")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P58_S5FE9B4")
#undef P58_S5FE9B4
#pragma push_macro("P58_S5FE9B4") /*gvi*/
#undef P58_S5FE9B4 /*gvi*/
uint32_t P58_S5FE9B4;
#pragma pop_macro("P58_S5FE9B4") /*gvi*/
#pragma pop_macro("P58_S5FE9B4")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P58_S5FE9B0")
#undef P58_S5FE9B0
#pragma push_macro("P58_S5FE9B0") /*gvi*/
#undef P58_S5FE9B0 /*gvi*/
uint32_t P58_S5FE9B0;
#pragma pop_macro("P58_S5FE9B0") /*gvi*/
#pragma pop_macro("P58_S5FE9B0")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P58_S5FE9B8")
#undef P58_S5FE9B8
#pragma push_macro("P58_S5FE9B8") /*gvi*/
#undef P58_S5FE9B8 /*gvi*/
uint32_t P58_S5FE9B8;
#pragma pop_macro("P58_S5FE9B8") /*gvi*/
#pragma pop_macro("P58_S5FE9B8")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P58_S5FE9F8")
#undef P58_S5FE9F8
#pragma push_macro("P58_S5FE9F8") /*gvi*/
#undef P58_S5FE9F8 /*gvi*/
int32_t P58_S5FE9F8;
#pragma pop_macro("P58_S5FE9F8") /*gvi*/
#pragma pop_macro("P58_S5FE9F8")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P58_Page")
#undef P58_Page
#pragma push_macro("P58_Page") /*gvi*/
#undef P58_Page /*gvi*/
int32_t P58_Page;
#pragma pop_macro("P58_Page") /*gvi*/
#pragma pop_macro("P58_Page")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P58_TabPtr")
#undef P58_TabPtr
#pragma push_macro("P58_TabPtr") /*gvi*/
#undef P58_TabPtr /*gvi*/
uint32_t P58_TabPtr;
#pragma pop_macro("P58_TabPtr") /*gvi*/
#pragma pop_macro("P58_TabPtr")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P58_S54DFC8")
#undef P58_S54DFC8
#pragma push_macro("P58_S54DFC8") /*gvi*/
#undef P58_S54DFC8 /*gvi*/
uint32_t P58_S54DFC8;
#pragma pop_macro("P58_S54DFC8") /*gvi*/
#pragma pop_macro("P58_S54DFC8")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P58_S54DFD8")
#undef P58_S54DFD8
#pragma push_macro("P58_S54DFD8") /*gvi*/
#undef P58_S54DFD8 /*gvi*/
uint32_t P58_S54DFD8;
#pragma pop_macro("P58_S54DFD8") /*gvi*/
#pragma pop_macro("P58_S54DFD8")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P58_S54DFE8")
#undef P58_S54DFE8
#pragma push_macro("P58_S54DFE8") /*gvi*/
#undef P58_S54DFE8 /*gvi*/
uint32_t P58_S54DFE8;
#pragma pop_macro("P58_S54DFE8") /*gvi*/
#pragma pop_macro("P58_S54DFE8")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P58_S54DFF8")
#undef P58_S54DFF8
#pragma push_macro("P58_S54DFF8") /*gvi*/
#undef P58_S54DFF8 /*gvi*/
uint32_t P58_S54DFF8;
#pragma pop_macro("P58_S54DFF8") /*gvi*/
#pragma pop_macro("P58_S54DFF8")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P58_S54E008")
#undef P58_S54E008
#pragma push_macro("P58_S54E008") /*gvi*/
#undef P58_S54E008 /*gvi*/
uint32_t P58_S54E008;
#pragma pop_macro("P58_S54E008") /*gvi*/
#pragma pop_macro("P58_S54E008")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P58_SC559D8")
#undef P58_SC559D8
#pragma push_macro("P58_SC559D8") /*gvi*/
#undef P58_SC559D8 /*gvi*/
uint32_t P58_SC559D8;
#pragma pop_macro("P58_SC559D8") /*gvi*/
#pragma pop_macro("P58_SC559D8")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P58_SC559E0")
#undef P58_SC559E0
#pragma push_macro("P58_SC559E0") /*gvi*/
#undef P58_SC559E0 /*gvi*/
uint32_t P58_SC559E0;
#pragma pop_macro("P58_SC559E0") /*gvi*/
#pragma pop_macro("P58_SC559E0")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P58_SC559E4")
#undef P58_SC559E4
#pragma push_macro("P58_SC559E4") /*gvi*/
#undef P58_SC559E4 /*gvi*/
uint32_t P58_SC559E4;
#pragma pop_macro("P58_SC559E4") /*gvi*/
#pragma pop_macro("P58_SC559E4")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P58_SC559E8")
#undef P58_SC559E8
#pragma push_macro("P58_SC559E8") /*gvi*/
#undef P58_SC559E8 /*gvi*/
uint32_t P58_SC559E8;
#pragma pop_macro("P58_SC559E8") /*gvi*/
#pragma pop_macro("P58_SC559E8")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P58_SC559EC")
#undef P58_SC559EC
#pragma push_macro("P58_SC559EC") /*gvi*/
#undef P58_SC559EC /*gvi*/
uint32_t P58_SC559EC;
#pragma pop_macro("P58_SC559EC") /*gvi*/
#pragma pop_macro("P58_SC559EC")
#endif
GAME_VAR_DEF(p58_blkidx_t, P58_BlkIdx, 0x00c29da0)
GAME_VAR_DEF(int32_t *, P58_BlkBuf, 0x00bdfbc4)
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P58_DemoFlag")
#undef P58_DemoFlag
#pragma push_macro("P58_DemoFlag") /*gvi*/
#undef P58_DemoFlag /*gvi*/
int32_t P58_DemoFlag;
#pragma pop_macro("P58_DemoFlag") /*gvi*/
#pragma pop_macro("P58_DemoFlag")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P58_S5F7E5C")
#undef P58_S5F7E5C
#pragma push_macro("P58_S5F7E5C") /*gvi*/
#undef P58_S5F7E5C /*gvi*/
int32_t P58_S5F7E5C;
#pragma pop_macro("P58_S5F7E5C") /*gvi*/
#pragma pop_macro("P58_S5F7E5C")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P58_DemoNo")
#undef P58_DemoNo
#pragma push_macro("P58_DemoNo") /*gvi*/
#undef P58_DemoNo /*gvi*/
int32_t P58_DemoNo;
#pragma pop_macro("P58_DemoNo") /*gvi*/
#pragma pop_macro("P58_DemoNo")
#endif
GAME_VAR_DEF(p58_names_t, P58_Demos, 0x00000000)
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P58_LangNo")
#undef P58_LangNo
#pragma push_macro("P58_LangNo") /*gvi*/
#undef P58_LangNo /*gvi*/
int32_t P58_LangNo;
#pragma pop_macro("P58_LangNo") /*gvi*/
#pragma pop_macro("P58_LangNo")
#endif
GAME_VAR_DEF(p58_names_t, P58_Langs, 0x00000000)
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P58_Objs")
#undef P58_Objs
#pragma push_macro("P58_Objs") /*gvi*/
#undef P58_Objs /*gvi*/
p58_objs_t P58_Objs;
#pragma pop_macro("P58_Objs") /*gvi*/
#pragma pop_macro("P58_Objs")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P58_S32980")
#undef P58_S32980
#pragma push_macro("P58_S32980") /*gvi*/
#undef P58_S32980 /*gvi*/
int32_t P58_S32980;
#pragma pop_macro("P58_S32980") /*gvi*/
#pragma pop_macro("P58_S32980")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P58_SB87EB0")
#undef P58_SB87EB0
#pragma push_macro("P58_SB87EB0") /*gvi*/
#undef P58_SB87EB0 /*gvi*/
int32_t P58_SB87EB0;
#pragma pop_macro("P58_SB87EB0") /*gvi*/
#pragma pop_macro("P58_SB87EB0")
#endif
GAME_VAR_DEF(p58_slot_t *, P58_ListB31EC4, 0x00b31ec4)
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P58_CntB31EBC")
#undef P58_CntB31EBC
#pragma push_macro("P58_CntB31EBC") /*gvi*/
#undef P58_CntB31EBC /*gvi*/
int32_t P58_CntB31EBC;
#pragma pop_macro("P58_CntB31EBC") /*gvi*/
#pragma pop_macro("P58_CntB31EBC")
#endif
GAME_VAR_DEF(void **, P58_Grid, 0x011342e8)
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P58_GridW")
#undef P58_GridW
#pragma push_macro("P58_GridW") /*gvi*/
#undef P58_GridW /*gvi*/
int32_t P58_GridW;
#pragma pop_macro("P58_GridW") /*gvi*/
#pragma pop_macro("P58_GridW")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P58_GridH")
#undef P58_GridH
#pragma push_macro("P58_GridH") /*gvi*/
#undef P58_GridH /*gvi*/
int32_t P58_GridH;
#pragma pop_macro("P58_GridH") /*gvi*/
#pragma pop_macro("P58_GridH")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P58_Font")
#undef P58_Font
#pragma push_macro("P58_Font") /*gvi*/
#undef P58_Font /*gvi*/
p58_font_t P58_Font;
#pragma pop_macro("P58_Font") /*gvi*/
#pragma pop_macro("P58_Font")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P58_Cfg")
#undef P58_Cfg
#pragma push_macro("P58_Cfg") /*gvi*/
#undef P58_Cfg /*gvi*/
p58_cfg_t P58_Cfg;
#pragma pop_macro("P58_Cfg") /*gvi*/
#pragma pop_macro("P58_Cfg")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P58_CfgHdr")
#undef P58_CfgHdr
#pragma push_macro("P58_CfgHdr") /*gvi*/
#undef P58_CfgHdr /*gvi*/
p56_hdr_t P58_CfgHdr;
#pragma pop_macro("P58_CfgHdr") /*gvi*/
#pragma pop_macro("P58_CfgHdr")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P58_CfgOn")
#undef P58_CfgOn
#pragma push_macro("P58_CfgOn") /*gvi*/
#undef P58_CfgOn /*gvi*/
int32_t P58_CfgOn;
#pragma pop_macro("P58_CfgOn") /*gvi*/
#pragma pop_macro("P58_CfgOn")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P58_CfgLock")
#undef P58_CfgLock
#pragma push_macro("P58_CfgLock") /*gvi*/
#undef P58_CfgLock /*gvi*/
int32_t P58_CfgLock;
#pragma pop_macro("P58_CfgLock") /*gvi*/
#pragma pop_macro("P58_CfgLock")
#endif

#ifdef RE_HOOK_BUILD
_Static_assert(sizeof(p58_cheat_t) == 8 && sizeof(p58_slot_t) == 8 && sizeof(p58_rec_t) == 12 && sizeof(p58_cell_t) == 12 &&
               sizeof(p58_list_t) == 8, "p58 struct sizes (32-bit Game.exe)");
#endif

/* Save / config file signatures and sizes (SAVES\GAMEn.BIN, config.dat). */
#define SAVE_MAGIC        0x57231356u
#define SAVE_NAME_BYTES   0x38      /* checksummed name block read from a save file */
#define CONFIG_MAGIC      0x93587031u
#define CONFIG_BYTES      0x10c     /* settings block of config.dat */

/* Строки таблиц из .data Game.exe (нужны только native). */
/* P58_InitConsts — native only.  Fills the .data string tables DEMO0..3 and ENG / FRE / GER / SPA / ITA / USA. */
void P58_InitConsts(void) {
#ifndef RE_HOOK_BUILD
  P58_Demos[0] = "DEMO0"; P58_Demos[1] = "DEMO1"; P58_Demos[2] = "DEMO2"; P58_Demos[3] = "DEMO3"; P58_Demos[4] = NULL;
  P58_Langs[0] = "ENG"; P58_Langs[1] = "FRE"; P58_Langs[2] = "GER"; P58_Langs[3] = "SPA"; P58_Langs[4] = "ITA"; P58_Langs[5] = "USA";
#endif
}

/* 00417e0d: пять вариантов; в 005fea44 кладётся адрес обработчика в Game.exe (thunk-и 00401dde / 00401dc5 / 00417f45 / 00402621 / 004013c5). */
/* P58_MenuSwitch — Game.exe 00417e0d.  Picks one of 5 screens by P58_MenuSel: fade to black, camera route 5..9,
   stores the screen's handler (a Game.exe thunk address) in 005fea44 and its index. */
void P58_MenuSwitch(void) {
  switch (P58_MenuSel) {
  case 0: SetFade0051707A(0, 0, 0, 0x32); Ui00418119(5); P58_MenuFn = 0x00401dde; P58_MenuIdx = 0; break;
  case 1: SetFade0051707A(0, 0, 0, 0x32); Ui00418119(6); P58_MenuFn = 0x00401dc5; P58_MenuIdx = 1; break;
  case 2: SetFade0051707A(0, 0, 0, 0x32); Ui004184DE(0); Ui00418119(7); P58_MenuFn = 0x00417f45; P58_MenuIdx = 2; break;
  case 3: SetFade0051707A(0, 0, 0, 0x32); Ui00418119(8); P58_MenuFn = 0x00402621; P58_MenuIdx = 3; break;
  case 4: SetFade0051707A(0, 0, 0, 0x32); Ui00418119(9); P58_MenuFn = 0x004013c5; P58_MenuIdx = 4; break;
  default: break;
  }
}

/* 00413381 / 004133b4: таблица кодов читов {строка, адрес флага}: все / по строке. */
/* P58_CheatsAll / P58_CheatByName — Game.exe 00413381 / 004133b4.  Enable all cheats, or the one whose code string
   matches `name` (table {string, flag address}, max 12), then save config.dat. */
void P58_CheatsAll(void) {
  for (int i = 0; i < 12 && P58_Cheats[i].name != NULL; i++) *P58_Cheats[i].var = 1;
  P47_Fn405BFA();
}
void P58_CheatByName(const char *name) {
  for (int i = 0; i < 12 && P58_Cheats[i].name != NULL; i++)
    if (strcmp(name, P58_Cheats[i].name) == 0) *P58_Cheats[i].var = 1;
  P47_Fn405BFA();
}

/* 00407dba: записи по 20 байт {…, флаги +8}; конец — бит 4, рисуются записи с битом 8. */
/* P58_ItemsDraw — Game.exe 00407dba.  Draws the menu items of P58_ItemList (20-byte records, flag word +8: bit 4 ends
   the list, bit 8 = visible) into frame-buffer address a. */
void P58_ItemsDraw(int32_t a) {
  if (P58_ItemList == NULL) return;
  int32_t idx = 0;
  for (int16_t *p = P58_ItemList; (p[4] & 4) == 0; p += 10) {
    if ((p[4] & 8) != 0) {
      int32_t v; memcpy(&v, p + 2, 4);
      P58_Fn407E2F(a, p[0], p[1], v, p, idx);
    }
    idx++;
  }
}

/* 004efc03 */
/* P58_FreeRecs — Game.exe 004efc03.  Frees the level's page -> palette list (P58_Tab4EFC03, see ported86.c). */
void P58_FreeRecs(void) {
  Dev00424858();
  if (P58_Tab4EFC03 != NULL) {
    /* P126_ReadMapPals allocates through the tracked allocator. Retire its
       records as well as the host memory before another level reuses it. */
    for (int32_t i = 0; i < P58_Cnt4EFC03; i++) P98_DebugFree(P58_Tab4EFC03[i].p);
    P98_DebugFree(P58_Tab4EFC03);
    P58_Tab4EFC03 = NULL; P58_Cnt4EFC03 = 0;
  }
}

/* 004f5dcd */
/* P58_FreeLists — Game.exe 004f5dcd.  Frees the mission's chunk pointers and limits (see P58_FindChunk). */
void P58_FreeLists(void) {
  for (int32_t i = 0; i < P58_CntC814E8; i++) DebugFree(P58_PtrsC816A0[i]);
  if (P58_PtrsC816A0 != NULL) DebugFree(P58_PtrsC816A0);
  if (P58_LimC810AC != NULL) DebugFree(P58_LimC810AC);
  P58_CntC814E8 = 0; P58_PtrsC816A0 = NULL; P58_LimC810AC = NULL;
}

/* 004f8d6d: список {число, массив элементов}; элемент начинается с указателя на строку. */
/* P58_FreeNames — Game.exe 004f8d6d.  Frees a {count, items} list whose items start with a string pointer. */
void P58_FreeNames(p58_list_t *l) {
  if (l->count == 0) return;
  void **arr = l->items;
  for (int32_t i = 0; i < l->count; i++) {
    void **e = (void **)arr[i];
    if (*e != NULL) DebugFree(*e);
    DebugFree(e);
  }
  if (arr != NULL) DebugFree(arr);
  l->count = 0; l->items = NULL;
}

/* Общий цикл экрана меню: таблица пунктов, ожидание-прокрутка, опрос до ненулевого результата. */
/* menu_loop — local helper: generic menu screen loop (init table, wait animation, step until a result). */
static int32_t menu_loop(uint32_t tbl, int32_t *state, uint32_t a, uint32_t b) {
  int32_t r;
  P57_MenuInit(tbl, 0);
  Call0040CCB4(a, b);
  for (;;) {
    Call00522323();
    Call004E3391();
    r = P57_MenuStep(tbl, state);
    if (r != 0) break;
    Call0040CB9F();
  }
  return r;
}

/* 00419f00 / 00419ab0: экраны со своей таблицей пунктов 0054e700/0054e600 — шаг 00418675, перерисовка, выход по -1. */
/* P58_Menu419F00 / P58_Menu419AB0 — Game.exe 00419f00 / 00419ab0.  Run the screens with item tables 0054e700 /
   0054e600 (P110_MenuSel) until Esc; the first saves config.dat afterwards.  Return -1. */
int32_t P58_Menu419F00(void) {
  GlobalSet00419F80();
  P58_S5FEA88 = 0; P58_S5FEA8C = 1;
  P58_Fn4185D2(0x0054e700, 0, 0x0054e6a0);
  while (P58_S5FEA88 != -1) {
    Call00522323();
    Call004E3391();
    P58_S5FEA88 = P58_Fn418675(0x0054e700, P58_S5FEA88);
    SetColorRed0041A051();
    Call0041846C(0x0054e6a0, 0);
  }
  P47_Fn405BFA();
  return -1;
}
int32_t P58_Menu419AB0(void) {
  Call00419B35();
  P58_S5FEA7C = 0; P58_S5FEA80 = 3; P58_S54E654 = 4;
  P58_Fn4185D2(0x0054e600, 0, 0x0054e560);
  while (P58_S5FEA7C != -1) {
    Call00522323();
    Call004E3391();
    P58_S5FEA7C = P58_Fn418675(0x0054e600, P58_S5FEA7C);
    MenuRed00419D3E();
    Call0041846C(0x0054e560, 0);
  }
  return -1;
}

/* 00413d70: подготовка 00413e37, таблица/параметры в 5fe9b4/5fe9b0/5fe9b8; выход -1 = закрыть (0). */
/* P58_Menu413D70 — Game.exe 00413d70.  Prepares (00413e37) and runs the screen in 005fe9b4..; -1 closes it and
   returns 0, else the choice. */
int32_t P58_Menu413D70(void) {
  int32_t r;
  P58_Fn413E37();
  P58_S5FE9C0 = 0;
  r = menu_loop(P58_S5FE9B4, &P58_S5FE9C0, P58_S5FE9B0, P58_S5FE9B8);
  if (r == -1) { P57_MenuDone(); r = 0; }
  return r;
}

/* 00416540: звук 3..6 по 5fe9f8, затем опрос 00416794 с перерисовкой 0041846c(0054e250, 004169af). */
/* P58_Menu416540 — Game.exe 00416540.  Plays voice sample 3..6 for selection 005fe9f8, runs the screen (00416794)
   until a result, frees the voice.  Returns the result. */
int32_t P58_Menu416540(void) {
  int32_t r;
  P58_Fn416605();
  switch (P58_S5FE9F8) {
  case 1: SoundPlay00523E50(3, 10, 0x5622); break;
  case 2: SoundPlay00523E50(4, 10, 0x5622); break;
  case 3: SoundPlay00523E50(5, 10, 0x5622); break;
  case 4: SoundPlay00523E50(6, 10, 0x5622); break;
  default: break;
  }
  for (;;) {
    Call00522323();
    Call004E3391();
    r = P58_Fn416794();
    if (r != 0) break;
    Call0041846C(0x0054e250, 0x004169af);
  }
  P48_FreeVoice(10);
  return r;
}

/* 00415f67: таблица пунктов по странице (2..4, иначе 1) и копирование пяти значений. */
/* P58_PrepPage — Game.exe 00415f67.  Selects the item table of page 1..4 (others -> 1), highlights it and copies
   five strings into the page. */
void P58_PrepPage(void) {
  switch (P58_Page) {
  case 2: P58_TabPtr = 0x0054e040; SetHiliteBits_0041621C(3, 4); break;
  case 3: P58_TabPtr = 0x0054e070; SetHiliteBits_0041621C(4, 4); break;
  case 4: P58_TabPtr = 0x0054e0b0; SetHiliteBits_0041621C(5, 4); break;
  default: P58_Page = 1; /* fallthrough */
  case 1: P58_TabPtr = 0x0054e020; SetHiliteBits_0041621C(2, 4); break;
  }
  P58_S54DFC8 = P58_SC559D8; P58_S54DFD8 = P58_SC559E0; P58_S54DFE8 = P58_SC559E4;
  P58_S54DFF8 = P58_SC559E8; P58_S54E008 = P58_SC559EC;
}

/* 0051be3c: таблица 0x4000 указателей на записи блока карты по номеру (short в начале записи); запись = 8 + 0x34*n байт. */
/* P58_BuildBlockIndex — Game.exe 0051be3c.  Index of 0x4000 pointers to map block records by their number (int16
   at the start of each record; record = 8 + 0x34 * n bytes).  Native: out-of-range numbers are skipped. */
void P58_BuildBlockIndex(void) {
  for (int32_t i = 0; i < 0x4000; i++) P58_BlkIdx[i] = NULL;
  int32_t *p = P58_BlkBuf + 1;
  int32_t n = *P58_BlkBuf;
  for (int32_t i = 0; i < n; i++) {
    int32_t idx = (int16_t)*p;
    if (idx >= 0 && idx < 0x4000) P58_BlkIdx[idx] = p;   /* оригинал индекс не проверяет */
    p += (int16_t)(((const uint8_t *)p)[6] | (((const uint8_t *)p)[7] << 8)) * 0xd + 2;
  }
}

/* 00408600: демо-ролик n (или следующий по кругу при -1). */
/* P58_PlayDemo — Game.exe 00408600.  Plays demo replay n, or with -1 the next one in turn (DEMO0..3, wrapping). */
void P58_PlayDemo(int32_t n) {
  P58_DemoFlag = 1; P58_S5F7E5C = 1;
  P138_ReplayCfg(n == -1 ? P58_Demos[P58_DemoNo] : P58_Demos[n]);
  Call3_0040C455(1, 1);
  P58_S5F7E5C = 0; P58_DemoFlag = 0;
  if (n == -1) {
    P58_DemoNo++;
    if (P58_Demos[P58_DemoNo] == NULL) P58_DemoNo = 0;
  }
}

/* 00516da0: строки «LANG.xxx» и «MISSION.xxx» для текущего языка (0..5). */
/* P58_LangStrings — Game.exe 00516da0.  Loads the "LANG.xxx" and "MISSION.xxx" string files of language 0..5. */
void P58_LangStrings(void) {
  char buf[256];
  if (P58_LangNo < 0 || P58_LangNo > 5) P58_LangNo = 0;
  const char *l = P58_Langs[P58_LangNo]; if (l == NULL) l = "(null)";
  snprintf(buf, sizeof buf, "LANG.%s", l);
  P58_Fn51763A(buf, 0);
  snprintf(buf, sizeof buf, "MISSION.%s", l);
  P58_Fn51763A(buf, 1);
}

/* 004a9b1a: значок DLOGO по центру сверху (размер в байтах +0xb/+0xc, 0 = 256). */
/* P58_DrawLogo — Game.exe 004a9b1a.  Draws the DLOGO icon centred at the top (x = 480 - w/2, y = 10). */
void P58_DrawLogo(void) {
  uint8_t *ic = P56_FindIcon("DLOGO");
  if (ic == NULL) return;
  uint32_t w = ic[0xb] ? ic[0xb] : 0x100;
  uint32_t h = ic[0xc] ? ic[0xc] : 0x100;
  P58_Fn4AA4EA((int32_t)(0x1e0 - w / 2), 10, (int32_t)w, (int32_t)h, ic, -1);
}

/* 00506bff: 10 объектов по 0x34 байта (флаги +0x10: бит 1 вкл., бит 0x10 скрыт), либо запасной */
/* P58_DrawObjs — Game.exe 00506bff.  Radar icons of the 10 mission objects (flag 1 on, 0x10 hidden), or of the spare
   object in a chase replay (00b87eb0). */
void P58_DrawObjs(void) {
  if (P58_SB87EB0 == 0) {
    for (int i = 0; i < 10; i++) {
      uint32_t fl; memcpy(&fl, &P58_Objs[i][0x10], 4);
      if ((fl & 1) != 0 && (fl & 0x10) == 0) P116_RadarIcon((const int32_t *)&P58_Objs[i][0x14], 0, 0xff, 0, 0, p116_f(P58_S32980));
    }
  } else {
    P116_RadarIcon((const int32_t *)&P58_ObjSpare, 0, 0xff, 0, 0, p116_f(P58_S32980));
  }
}

/* 00524e22: десятичное число со знаком до пробела/конца строки; не цифра — 0. */
/* P58_ParseInt — Game.exe 00524e22.  Signed decimal up to a space or the end; any other character gives 0. */
int32_t P58_ParseInt(const uint8_t *s) {
  uint32_t v = 0; int neg = 0;
  if (*s == '-') { neg = 1; s++; }
  for (;;) {
    if (*s == 0 || *s == 0x20) return (int32_t)(neg ? 0u - v : v);
    uint8_t c = *s++;
    if (c < '0' || c > '9') return 0;
    v = v * 10u + (uint32_t)(c - '0');
  }
}

/* 004eb19b: список {?, буфер} с конца, затем сам массив */
/* P58_FreeList — Game.exe 004eb19b.  Frees list 00b31ec4 (buffers from the end), then the array. */
void P58_FreeList(void) {
  if (P58_ListB31EC4 != NULL) {
    while (P58_CntB31EBC != 0) {
      P58_CntB31EBC--;
      if (P58_ListB31EC4[P58_CntB31EBC].p != NULL) {
        DebugFree(P58_ListB31EC4[P58_CntB31EBC].p);
        P58_ListB31EC4[P58_CntB31EBC].p = NULL;
      }
      P58_ListB31EC4[P58_CntB31EBC].p = NULL;
    }
    DebugFree(P58_ListB31EC4);
    P58_ListB31EC4 = NULL;
  }
  P58_CntB31EBC = 0;
}

/* 004a3354: сетка ширина×высота указателей на {…, …, буфер} */
/* P58_FreeGrid — Game.exe 004a3354.  Frees the width x height grid of cell records and their item buffers. */
void P58_FreeGrid(void) {
  if (P58_Grid != NULL) {
    for (int32_t i = 0; i < P58_GridW * P58_GridH; i++) {
      p58_cell_t *c = (p58_cell_t *)P58_Grid[i];
      if (c != NULL) {
        DebugFree(c->items);
        DebugFree(c);
        P58_Grid[i] = NULL;
      }
    }
    DebugFree(P58_Grid);
  }
  P58_GridH = 0; P58_GridW = 0; P58_Grid = NULL;
}

/* 004f6011: кусок (указатель) по накопленным границам v/0x32; не найден — флаги ошибки в блоке c810c0. */
/* P58_FindChunk — Game.exe 004f6011.  Returns the chunk whose cumulative limit covers v / 50; if none, sets the
   error state in the 00c810c0 block (result 0xff0, flag, countdown 0x5a).  NULL for v == 0 or not found.
   TODO(RE): unsure what v measures (a distance or time along a route?). */
void *P58_FindChunk(int32_t v) {
  if (v != 0) {
    int32_t lo = 0;
    for (int32_t i = 0; i < P58_CntC814E8; i++) {
      if (lo <= v / 0x32 && v / 0x32 < P58_LimC810AC[i]) return P58_PtrsC816A0[i];
      lo = P58_LimC810AC[i];
    }
    P56_Blk84[1] = 0xff0; P56_Blk84[10] = 1; P56_Blk84[16] = 0x5a;
  }
  return NULL;
}

/* 0040cf35: фон главного меню 3×2 плитки BKGRND1A..F */
/* P58_Backgrounds — Game.exe 0040cf35.  Draws the main-menu background as 3x2 tiles BKGRND1A..F. */
void P58_Backgrounds(void) {
  P58_Fn40CFDF(0x000, 0x030, 0x0054aa40, "BKGRND1A", 0);
  P58_Fn40CFDF(0x100, 0x030, 0x0054aa40, "BKGRND1B", 0);
  P58_Fn40CFDF(0x200, 0x030, 0x0054aa40, "BKGRND1C", 0);
  P58_Fn40CFDF(0x000, 0x130, 0x0054aa40, "BKGRND1D", 0);
  P58_Fn40CFDF(0x100, 0x130, 0x0054aa40, "BKGRND1E", 0);
  P58_Fn40CFDF(0x200, 0x130, 0x0054aa40, "BKGRND1F", 0);
}

/* 00405e79: файл SAVES\GAMEn.BIN (n = slot+1): подпись 0x57231356 и сумма 0x38 байт; затем строка копируется в dst (strcpy в оригинале, здесь не дальше 0x38 байт). */
/* P58_SaveSlot — Game.exe 00405e79.  Reads the name of save slot `slot` (SAVES\GAME<slot+1>.BIN: signature
   SAVE_MAGIC + checksum, then 0x38 bytes) into dst.  Returns 1, or 0 if missing / invalid.
   Native: the copy stops at 0x38 bytes (strcpy in Game.exe). */
int32_t P58_SaveSlot(int32_t slot, char *dst) {
  char name[32];
  snprintf(name, sizeof name, "SAVES\\GAME%d.BIN", slot + 1);
  void *f = g_fopen(name, "rb");
  if (f == NULL) return 0;
  g_fread(P56_SaveHdr, 1, 8, f);
  g_fread(P56_SaveBuf, 1, SAVE_NAME_BYTES, f);
  g_fclose(f);
  if (P56_SaveHdr[0] != SAVE_MAGIC) return 0;
  if (P56_Fn40682D(P56_SaveBuf, SAVE_NAME_BYTES) != (int32_t)P56_SaveHdr[1]) return 0;   /* byte checksum */
  int i = 0;
  while (i < SAVE_NAME_BYTES && P56_SaveBuf[i] != 0) { dst[i] = (char)P56_SaveBuf[i]; i++; }
  dst[i] = 0;
  return 1;
}

/* 00405bfa: запись CONFIG.DAT {подпись 0x93587031, сумма} + 0x10c байт настроек. */
/* P58_SaveConfig — Game.exe 00405bfa.  Writes config.dat: {CONFIG_MAGIC, checksum} + 0x10c bytes of settings,
   unless saving is off or locked. */
void P58_SaveConfig(void) {
  if (P58_CfgOn == 0 || P58_CfgLock != 0) return;
  { uint32_t snap[0x43]; P102_ConfigSnap(snap); memcpy(P58_Cfg, snap, CONFIG_BYTES); }   /* v1.78: 00406875 перенесена (P102) */
  int32_t sum = SumBytes(P58_Cfg, CONFIG_BYTES);   /* v1.78: ported 0040682d (была заглушка) */
  P58_CfgHdr[0] = CONFIG_MAGIC; P58_CfgHdr[1] = (uint32_t)sum;
  void *f = g_fopen("config.dat", "wb");
  if (f != NULL) {
    g_fwrite(P58_CfgHdr, 1, 8, f);
    g_fwrite(P58_Cfg, 1, CONFIG_BYTES, f);
    g_fclose(f);
  }
}

/* 0040b1cc: ширина строки шрифтом font (запись глифа 8 байт, таблица 0x806 на шрифт). */
/* P58_TextWidth — Game.exe 0040b1cc.  Width of string s in font `font` (0x806-byte table per font, 8-byte glyph
   records: a glyph with flag 0 advances by the font's default width (+0xc), others by glyph width + the
   font's spacing (+0xa); variable names follow that reading).
   Native: invalid font numbers return 0. */
float P58_TextWidth(const uint8_t *s, int32_t font) {
  float w = 0.0f;
  if (font < 0 || font >= 8) return 0.0f;      /* оригинал номер не проверяет */
  const uint8_t *font_tab = &P58_Font[0] + font * 0x806;
  while (*s != 0) {
    uint32_t ch = *s++;
    int16_t flag, space_w, spacing; memcpy(&flag, font_tab + 0xe + ch * 8, 2); memcpy(&space_w, font_tab + 0xc, 2); memcpy(&spacing, font_tab + 0xa, 2);
    int32_t adv = (flag == 0) ? (int32_t)space_w : (int32_t)font_tab[0x14 + ch * 8] + (int32_t)spacing;
    w = w + (float)adv;
  }
  return w;
}
