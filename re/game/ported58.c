#include "ported58.h"
#include "ported116.h"
#include "crt.h"
#include <string.h>
#include <stdio.h>

GAME_VAR_DEF(int32_t, P58_MenuSel, 0x005fed9c)
GAME_VAR_DEF(int32_t, P58_MenuFn, 0x005fea44)
GAME_VAR_DEF(int32_t, P58_MenuIdx, 0x005fea38)
GAME_VAR_DEF(p58_cheats_t, P58_Cheats, 0x0054cfd8)
GAME_VAR_DEF(int16_t *, P58_ItemList, 0x005f7e64)
GAME_VAR_DEF(p58_rec_t *, P58_Tab4EFC03, 0x00b31ee8)
GAME_VAR_DEF(int32_t, P58_Cnt4EFC03, 0x00b31eec)
GAME_VAR_DEF(int32_t, P58_CntC814E8, 0x00c814e8)
GAME_VAR_DEF(void **, P58_PtrsC816A0, 0x00c816a0)
GAME_VAR_DEF(int32_t *, P58_LimC810AC, 0x00c810ac)
GAME_VAR_DEF(int32_t, P58_S5FEA88, 0x005fea88)
GAME_VAR_DEF(int32_t, P58_S5FEA8C, 0x005fea8c)
GAME_VAR_DEF(int32_t, P58_S5FEA7C, 0x005fea7c)
GAME_VAR_DEF(int32_t, P58_S5FEA80, 0x005fea80)
GAME_VAR_DEF(int32_t, P58_S54E654, 0x0054e654)
GAME_VAR_DEF(int32_t, P58_S5FE9C0, 0x005fe9c0)
GAME_VAR_DEF(uint32_t, P58_S5FE9B4, 0x005fe9b4)
GAME_VAR_DEF(uint32_t, P58_S5FE9B0, 0x005fe9b0)
GAME_VAR_DEF(uint32_t, P58_S5FE9B8, 0x005fe9b8)
GAME_VAR_DEF(int32_t, P58_S5FE9F8, 0x005fe9f8)
GAME_VAR_DEF(int32_t, P58_Page, 0x00575ef0)
GAME_VAR_DEF(uint32_t, P58_TabPtr, 0x0054e100)
GAME_VAR_DEF(uint32_t, P58_S54DFC8, 0x0054dfc8)
GAME_VAR_DEF(uint32_t, P58_S54DFD8, 0x0054dfd8)
GAME_VAR_DEF(uint32_t, P58_S54DFE8, 0x0054dfe8)
GAME_VAR_DEF(uint32_t, P58_S54DFF8, 0x0054dff8)
GAME_VAR_DEF(uint32_t, P58_S54E008, 0x0054e008)
GAME_VAR_DEF(uint32_t, P58_SC559D8, 0x00c559d8)
GAME_VAR_DEF(uint32_t, P58_SC559E0, 0x00c559e0)
GAME_VAR_DEF(uint32_t, P58_SC559E4, 0x00c559e4)
GAME_VAR_DEF(uint32_t, P58_SC559E8, 0x00c559e8)
GAME_VAR_DEF(uint32_t, P58_SC559EC, 0x00c559ec)
GAME_VAR_DEF(p58_blkidx_t, P58_BlkIdx, 0x00c29da0)
GAME_VAR_DEF(int32_t *, P58_BlkBuf, 0x00bdfbc4)
GAME_VAR_DEF(int32_t, P58_DemoFlag, 0x00b87f0c)
GAME_VAR_DEF(int32_t, P58_S5F7E5C, 0x005f7e5c)
GAME_VAR_DEF(int32_t, P58_DemoNo, 0x005d5780)
GAME_VAR_DEF(p58_names_t, P58_Demos, 0x0054a130)
GAME_VAR_DEF(int32_t, P58_LangNo, 0x00c557fc)
GAME_VAR_DEF(p58_names_t, P58_Langs, 0x005759e4)
GAME_VAR_DEF(p58_objs_t, P58_Objs, 0x00c80ce0)
GAME_VAR_DEF(int32_t, P58_S32980, 0x00b32980)
GAME_VAR_DEF(int32_t, P58_SB87EB0, 0x00b87eb0)
GAME_VAR_DEF(p58_slot_t *, P58_ListB31EC4, 0x00b31ec4)
GAME_VAR_DEF(int32_t, P58_CntB31EBC, 0x00b31ebc)
GAME_VAR_DEF(void **, P58_Grid, 0x011342e8)
GAME_VAR_DEF(int32_t, P58_GridW, 0x0113452c)
GAME_VAR_DEF(int32_t, P58_GridH, 0x01134530)
GAME_VAR_DEF(p58_font_t, P58_Font, 0x005d57a0)
GAME_VAR_DEF(p58_cfg_t, P58_Cfg, 0x01285320)
GAME_VAR_DEF(p56_hdr_t, P58_CfgHdr, 0x0057b6a0)
GAME_VAR_DEF(int32_t, P58_CfgOn, 0x00b87eb8)
GAME_VAR_DEF(int32_t, P58_CfgLock, 0x0057b700)

#ifdef RE_HOOK_BUILD
_Static_assert(sizeof(p58_cheat_t) == 8 && sizeof(p58_slot_t) == 8 && sizeof(p58_rec_t) == 12 && sizeof(p58_cell_t) == 12 &&
               sizeof(p58_list_t) == 8, "p58 struct sizes (32-bit Game.exe)");
#endif

/* Строки таблиц из .data Game.exe (нужны только native). */
void P58_InitConsts(void) {
#ifndef RE_HOOK_BUILD
  P58_Demos[0] = "DEMO0"; P58_Demos[1] = "DEMO1"; P58_Demos[2] = "DEMO2"; P58_Demos[3] = "DEMO3"; P58_Demos[4] = NULL;
  P58_Langs[0] = "ENG"; P58_Langs[1] = "FRE"; P58_Langs[2] = "GER"; P58_Langs[3] = "SPA"; P58_Langs[4] = "ITA"; P58_Langs[5] = "USA";
#endif
}

/* 00417e0d: пять вариантов; в 005fea44 кладётся адрес обработчика в Game.exe (thunk-и 00401dde / 00401dc5 / 00417f45 / 00402621 / 004013c5). */
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
void P58_FreeRecs(void) {
  Dev00424858();
  if (P58_Tab4EFC03 != NULL) {
    for (int32_t i = 0; i < P58_Cnt4EFC03; i++) DebugFree(P58_Tab4EFC03[i].p);
    DebugFree(P58_Tab4EFC03);
    P58_Tab4EFC03 = NULL; P58_Cnt4EFC03 = 0;
  }
}

/* 004f5dcd */
void P58_FreeLists(void) {
  for (int32_t i = 0; i < P58_CntC814E8; i++) DebugFree(P58_PtrsC816A0[i]);
  if (P58_PtrsC816A0 != NULL) DebugFree(P58_PtrsC816A0);
  if (P58_LimC810AC != NULL) DebugFree(P58_LimC810AC);
  P58_CntC814E8 = 0; P58_PtrsC816A0 = NULL; P58_LimC810AC = NULL;
}

/* 004f8d6d: список {число, массив элементов}; элемент начинается с указателя на строку. */
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
int32_t P58_Menu413D70(void) {
  int32_t r;
  P58_Fn413E37();
  P58_S5FE9C0 = 0;
  r = menu_loop(P58_S5FE9B4, &P58_S5FE9C0, P58_S5FE9B0, P58_S5FE9B8);
  if (r == -1) { P57_MenuDone(); r = 0; }
  return r;
}

/* 00416540: звук 3..6 по 5fe9f8, затем опрос 00416794 с перерисовкой 0041846c(0054e250, 004169af). */
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
void P58_PlayDemo(int32_t n) {
  P58_DemoFlag = 1; P58_S5F7E5C = 1;
  P47_Fn517D58(n == -1 ? P58_Demos[P58_DemoNo] : P58_Demos[n]);
  Call3_0040C455(1, 1);
  P58_S5F7E5C = 0; P58_DemoFlag = 0;
  if (n == -1) {
    P58_DemoNo++;
    if (P58_Demos[P58_DemoNo] == NULL) P58_DemoNo = 0;
  }
}

/* 00516da0: строки «LANG.xxx» и «MISSION.xxx» для текущего языка (0..5). */
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
void P58_DrawLogo(void) {
  uint8_t *ic = P56_FindIcon("DLOGO");
  if (ic == NULL) return;
  uint32_t w = ic[0xb] ? ic[0xb] : 0x100;
  uint32_t h = ic[0xc] ? ic[0xc] : 0x100;
  P58_Fn4AA4EA((int32_t)(0x1e0 - w / 2), 10, (int32_t)w, (int32_t)h, ic, -1);
}

/* 00506bff: 10 объектов по 0x34 байта (флаги +0x10: бит 1 вкл., бит 0x10 скрыт), либо запасной */
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
void P58_Backgrounds(void) {
  P58_Fn40CFDF(0x000, 0x030, 0x0054aa40, "BKGRND1A", 0);
  P58_Fn40CFDF(0x100, 0x030, 0x0054aa40, "BKGRND1B", 0);
  P58_Fn40CFDF(0x200, 0x030, 0x0054aa40, "BKGRND1C", 0);
  P58_Fn40CFDF(0x000, 0x130, 0x0054aa40, "BKGRND1D", 0);
  P58_Fn40CFDF(0x100, 0x130, 0x0054aa40, "BKGRND1E", 0);
  P58_Fn40CFDF(0x200, 0x130, 0x0054aa40, "BKGRND1F", 0);
}

/* 00405e79: файл SAVES\GAMEn.BIN (n = slot+1): подпись 0x57231356 и сумма 0x38 байт; затем строка копируется в dst (strcpy в оригинале, здесь не дальше 0x38 байт). */
int32_t P58_SaveSlot(int32_t slot, char *dst) {
  char name[32];
  snprintf(name, sizeof name, "SAVES\\GAME%d.BIN", slot + 1);
  void *f = g_fopen(name, "rb");
  if (f == NULL) return 0;
  g_fread(P56_SaveHdr, 1, 8, f);
  g_fread(P56_SaveBuf, 1, 0x38, f);
  g_fclose(f);
  if (P56_SaveHdr[0] != 0x57231356u) return 0;
  if (P56_Fn40682D(P56_SaveBuf, 0x38) != (int32_t)P56_SaveHdr[1]) return 0;
  int i = 0;
  while (i < 0x38 && P56_SaveBuf[i] != 0) { dst[i] = (char)P56_SaveBuf[i]; i++; }
  dst[i] = 0;
  return 1;
}

/* 00405bfa: запись CONFIG.DAT {подпись 0x93587031, сумма} + 0x10c байт настроек. */
void P58_SaveConfig(void) {
  if (P58_CfgOn == 0 || P58_CfgLock != 0) return;
  P58_Fn406875(P58_Cfg);
  int32_t sum = P56_Fn40682D(P58_Cfg, 0x10c);
  P58_CfgHdr[0] = 0x93587031u; P58_CfgHdr[1] = (uint32_t)sum;
  void *f = g_fopen("config.dat", "wb");
  if (f != NULL) {
    g_fwrite(P58_CfgHdr, 1, 8, f);
    g_fwrite(P58_Cfg, 1, 0x10c, f);
    g_fclose(f);
  }
}

/* 0040b1cc: ширина строки шрифтом font (запись глифа 8 байт, таблица 0x806 на шрифт). */
float P58_TextWidth(const uint8_t *s, int32_t font) {
  float w = 0.0f;
  if (font < 0 || font >= 8) return 0.0f;      /* оригинал номер не проверяет */
  const uint8_t *t = &P58_Font[0] + font * 0x806;
  while (*s != 0) {
    uint32_t c = *s++;
    int16_t flag, a, b; memcpy(&flag, t + 0xe + c * 8, 2); memcpy(&a, t + 0xc, 2); memcpy(&b, t + 0xa, 2);
    int32_t v = (flag == 0) ? (int32_t)a : (int32_t)t[0x14 + c * 8] + (int32_t)b;
    w = w + (float)v;
  }
  return w;
}
