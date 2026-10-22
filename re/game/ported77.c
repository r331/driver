/* Level loading (.lev block file), sound bank text file, three front-end menu screens,
   per-level table reset, MScript block list and the camera far plane. */
#include "ported77.h"
#include <stdio.h>
#include <string.h>

GAME_VAR_DEF(const char*, P77_LevelName, 0x00c81164)
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P77_ListN")
#undef P77_ListN
#pragma push_macro("P77_ListN") /*gvi*/
#undef P77_ListN /*gvi*/
int32_t P77_ListN;
#pragma pop_macro("P77_ListN") /*gvi*/
#pragma pop_macro("P77_ListN")
#endif
GAME_VAR_DEF(void**, P77_List, 0x00c8175c)
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P77_Plane")
#undef P77_Plane
#pragma push_macro("P77_Plane") /*gvi*/
#undef P77_Plane /*gvi*/
p77_plane_t P77_Plane;
#pragma pop_macro("P77_Plane") /*gvi*/
#pragma pop_macro("P77_Plane")
#endif
GAME_VAR_DEF(p77_b590e0_t, P77_B590E0, 0x00b590e0)
GAME_VAR_DEF(p77_c62d60_t, P77_C62D60, 0x00c62d60)
GAME_VAR_DEF(p77_c65dc0_t, P77_C65DC0, 0x00c65dc0)
GAME_VAR_DEF(p77_c5fe00_t, P77_C5FE00, 0x00c5fe00)
GAME_VAR_DEF(p77_c7d8c0_t, P77_C7D8C0, 0x00c7d8c0)
GAME_VAR_DEF(p77_c62e60_t, P77_C62E60, 0x00c62e60)
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P77_C7D850")
#undef P77_C7D850
#pragma push_macro("P77_C7D850") /*gvi*/
#undef P77_C7D850 /*gvi*/
uint8_t P77_C7D850;
#pragma pop_macro("P77_C7D850") /*gvi*/
#pragma pop_macro("P77_C7D850")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P77_C7D8A4")
#undef P77_C7D8A4
#pragma push_macro("P77_C7D8A4") /*gvi*/
#undef P77_C7D8A4 /*gvi*/
int32_t P77_C7D8A4;
#pragma pop_macro("P77_C7D8A4") /*gvi*/
#pragma pop_macro("P77_C7D8A4")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P77_C7D8A0")
#undef P77_C7D8A0
#pragma push_macro("P77_C7D8A0") /*gvi*/
#undef P77_C7D8A0 /*gvi*/
int32_t P77_C7D8A0;
#pragma pop_macro("P77_C7D8A0") /*gvi*/
#pragma pop_macro("P77_C7D8A0")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P77_C7D8A8")
#undef P77_C7D8A8
#pragma push_macro("P77_C7D8A8") /*gvi*/
#undef P77_C7D8A8 /*gvi*/
int32_t P77_C7D8A8;
#pragma pop_macro("P77_C7D8A8") /*gvi*/
#pragma pop_macro("P77_C7D8A8")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P77_C65DA4")
#undef P77_C65DA4
#pragma push_macro("P77_C65DA4") /*gvi*/
#undef P77_C65DA4 /*gvi*/
int32_t P77_C65DA4;
#pragma pop_macro("P77_C65DA4") /*gvi*/
#pragma pop_macro("P77_C65DA4")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P77_B5A0E8")
#undef P77_B5A0E8
#pragma push_macro("P77_B5A0E8") /*gvi*/
#undef P77_B5A0E8 /*gvi*/
int32_t P77_B5A0E8;
#pragma pop_macro("P77_B5A0E8") /*gvi*/
#pragma pop_macro("P77_B5A0E8")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P77_S574570")
#undef P77_S574570
#pragma push_macro("P77_S574570") /*gvi*/
#undef P77_S574570 /*gvi*/
int32_t P77_S574570;
#pragma pop_macro("P77_S574570") /*gvi*/
#pragma pop_macro("P77_S574570")
#endif

/* Неперенесённые: загрузчики блоков уровня, обработчик блока 0x14, финальная подготовка, запись банка звуков. */
#define P77_UNPORTED_NONE 0

/* 004eca08: имя файла уровня зависит от режима (00b87eec — плоская карта, состояние 4 / 00b87e98 — iview, 5 / 00b87ea8 — train). */
#ifndef RE_HOOK_BUILD
char P77_CurLevelPath[256];   /* v2.17: путь последнего открытого .lev (native) */
#endif
/* P77_OpenLevel — Game.exe 004eca08, cdecl.  Open the level file for reading: flat.lev (flat-map mode 00b87eec), iview.lev (state 4 or
   iview flag), train.lev (state 5 or train flag), else Levels\<P77_LevelName> (Miami_01.lev
   by default).  Native: backslashes become '/', and the path is remembered in
   P77_CurLevelPath for the HD texture pack.  Returns the FILE handle or NULL. */
void *P77_OpenLevel(void) {
  char path[256];
  const char *p;
  if (G6_00B87EEC != 0) p = "Levels\\flat.lev";
  else if (D_00b87e30 == 4 || P62_HudOff2 != 0) p = "Levels\\iview.lev";
  else if (D_00b87e30 == 5 || P56_B87EA8 != 0) p = "Levels\\train.lev";
  else {
    if (P77_LevelName == NULL) snprintf(path, sizeof path, "Levels\\Miami_01.lev");
    else snprintf(path, sizeof path, "Levels\\%s", P77_LevelName);
    p = path;
  }
#ifndef RE_HOOK_BUILD
  char native[256];
  size_t i = 0;
  for (; p[i] != 0 && i + 1 < sizeof native; i++) native[i] = p[i] == '\\' ? '/' : p[i];
  native[i] = 0;
  p = native;
  snprintf(P77_CurLevelPath, sizeof P77_CurLevelPath, "%s", native);   /* v2.17: имя уровня для HD-пака текстур */
#endif
  return g_fopen(p, "rb");
}

/* 004ecade: файл = число блоков, затем блоки [тип][размер][данные]; (прочие типы пропускаются как в оригинале — без default). */
/* P77_LoadLevel — Game.exe 004ecade, cdecl.  Load the current level: a block count, then blocks {int32 type, int32 size, data}
   dispatched to their loaders (type 3 and unknown types are not skipped — as the original,
   which has no default; 0x12 is skipped by size).  Then finds wheel models and runs the
   post-load setup (00516e76, 00501c63, 00501770, 00426caf).  Returns 1, or 0 if the file is
   missing. */
int32_t P77_LoadLevel(void) {
  int32_t count = 0, kind, size;
  P12_Fn00426580(-1);
  void *f = P77_OpenLevel();
  P20_Names = NULL;
  if (f == NULL) return 0;
  P27_ReadChunked(&count, 4, 1, f);
  for (int32_t i = 0; i < count; i++) {
    P27_ReadChunked(&kind, 4, 1, f);
    P27_ReadChunked(&size, 4, 1, f);
    switch (kind) {
    case 0:    P41_LoadTexPages(f); break;
    case 1:    P80_LoadModels(f); break;
    case 2:    P80_LoadHeader(f); break;
    case 4:    P78_LoadVerts(f, size); break;
    case 5:    P54_ReadMapA(f, size); break;
    case 6:    P57_SkipBlock(f, size); break;
    case 7:    P62_LoadMapHeader(f, size); break;
    case 8:    ReadTable_004EC466(f); break;
    case 9:    ReadTable_004EC49A(f); break;
    case 10:   P46_LoadMapB(f, size); break;
    case 0xb:  P54_ReadMapB(f, size); break;
    case 0xc:  P54_ReadNames(f, size); break;
    case 0xd:  P28_LoadEventModels(f); break;
    case 0xe:  P46_LoadMapA(f, size); break;
    case 0xf:  ReadBlocks_004EB7CF(f); break;
    case 0x10: ReadTable_004EC522(f); break;
    case 0x11: ReadTable_004EC556(f); break;
    case 0x12: g_fseek(f, size, 1); break;
    case 0x13: P78_LoadLampsBlock(f); break;
    case 0x14: P78_LoadChairs(f, size); break;
    default: break;
    }
  }
  g_fclose(f);
  P12_Fn00426580(1);
  P26_FindWheelModels();
  P12_Fn00516E76();
  P77_Fn501C63();
  P77_Fn501770();
  Ui00426CAF();
  return 1;
}

/* 00524496: банк звуков — текстовый файл; строки с ';' в начале — комментарии, остальные разбирает 00524bd8 (она увеличивает счётчик 00b91d34). */
/* P77_LoadBank — Game.exe 00524496, cdecl.  Load a sound bank text file: lines starting with ';' are comments, each other line is parsed
   by 00524bd8 (which increments the sound count 00b91d34).  A non-zero slot records the first
   sound index in 00b91bc4[(slot >> 12) & 15].  Returns 00b91d34 minus (old count + parsed
   lines), i.e. 0 when every line added one sound.  Returns 0 if sound is off or no file. */
int32_t P77_LoadBank(const char *name, uint16_t slot) {
  uint32_t line[32];
  int32_t n;
  if (G6_00B91CF4 == 0) return 0;
  n = G6_00B91D34;
  if (slot != 0) G6_00B91BC4[(slot >> 12) & 15] = G6_00B91D34;
  void *f = g_fopen(name, "r");
  if (f == NULL) return 0;
  while (P68_ReadWords(f, (uint8_t *)line) != -1) {
    if ((line[0] & 0xff) != 0x3b) { P77_Fn524BD8(line); n++; }
  }
  g_fclose(f);
  return G6_00B91D34 - n;
}

/* Общий цикл экрана меню: таблица пунктов tbl, состояние *st, заголовок a/b, перерисовка redraw + 0041846c(b, cb).
   Режим 00b87eec != 0 — шаг 00418675 вместо опроса 0040c8f1; выход по -1 (в опросе — с ожиданием 0040cd17). */
/* screen_loop — Common loop of a front-end menu screen: table tbl, selected row *st, title strings a/b,
   redraw callback and screen callback cb.  In flat-map mode (00b87eec) steps 00418675 and
   redraws until it returns -1 (result 0); otherwise polls P57_MenuStep until it returns
   non-zero (-1 = back -> 0).  Returns the menu result. */
static int32_t screen_loop(uint32_t tbl, int32_t *st, uint32_t a, uint32_t b, void (*redraw)(void), uint32_t cb) {
  int32_t r;
  P57_MenuInit(tbl, 0);
  if (G6_00B87EEC == 0) Call0040CCB4(a, b);
  for (;;) {
    Call00522323();
    Call004E3391();
    if (G6_00B87EEC != 0) {
      *st = P58_Fn418675(tbl, *st);
      if (*st == -1) return 0;
      redraw();
      Call0041846C(b, cb);
    } else {
      r = P57_MenuStep(tbl, st);
      if (r != 0) {
        if (r == -1) { if (G6_00B87EEC == 0) P57_MenuDone(); r = 0; }
        return r;
      }
      Call0040CB9F();
    }
  }
}
/* P77_Menu407160 — Game.exe 00407160, cdecl.  Front-end menu screen at table 0054a008 (no callback).  TODO(RE): unsure which screen. */
int32_t P77_Menu407160(void) {
  P54_InitInputMode();
  G6_0057B728 = 0; MenuI0057B730 = 1; MenuI0054A060 = 2;
  return screen_loop(0x0054a008, &G6_0057B728, 0x00549f60, 0x00549f78, MenuRed0040766D, 0);
}
/* P77_Menu414C30 — Game.exe 00414c30, cdecl.  Front-end menu screen at table 0054dd10, callback 004159e5.  TODO(RE): unsure which screen. */
int32_t P77_Menu414C30(void) {
  Call00414D1F();
  G6_005FE9CC = 0; MenuI005FE9D0 = 6; MenuI0054DE08 = 7;
  return screen_loop(0x0054dd10, &G6_005FE9CC, 0x0054db58, 0x0054dbc0, MenuRed00415904, 0x004159e5);
}
/* P77_Menu408770 — Game.exe 00408770, cdecl.  Front-end menu screen at table 0054a470, callback 00409d66.  TODO(RE): unsure which screen. */
int32_t P77_Menu408770(void) {
  G6Call004094E3();
  MenuRedraw();
  G6_005D5788 = 0; MenuI005D578C = 0; MenuI0054A694 = 1;
  return screen_loop(0x0054a470, &G6_005D5788, 0x0054a170, 0x0054a250, MenuRed00409C85, 0x00409d66);
}

/* P77_ResetTables — Game.exe 00509c40, cdecl.  Clear the per-level object tables (b590e0, c62d60, c65dc0, c7d800, c5fe00, near list
   c7d860, c7d8c0, c62e60) and their counters; 00574570 is reset to 0x5e8.
   TODO(RE): unsure what 0x5e8 is. */
void P77_ResetTables(void) {
  memset(P77_B590E0, 0, sizeof P77_B590E0);
  memset(P77_C62D60, 0, sizeof P77_C62D60);
  memset(P77_C65DC0, 0, sizeof P77_C65DC0);
  _Static_assert(sizeof(P12_00c7d800) >= 0x20, "00c7d800");
  memset(&P12_00c7d800, 0, 0x20);
  memset(P77_C5FE00, 0, sizeof P77_C5FE00);
  _Static_assert(sizeof(P59_NearList) == 0x40, "00c7d860");
  memset(&P59_NearList, 0, 0x40);
  memset(P77_C7D8C0, 0, sizeof P77_C7D8C0);
  memset(P77_C62E60, 0, sizeof P77_C62E60);
  P77_C7D850 = 0;
  P12_00c595a0 = 0;
  P77_C7D8A4 = 0;
  P77_C7D8A0 = 0;
  P77_S574570 = 0x5e8;
  P77_B5A0E8 = 0;
  P77_C65DA4 = 0;
  P77_C7D8A8 = 0;
  *(uint8_t *)&P59_NearN = 0;   /* оригинал пишет один байт */
}

/* 004f8643: список указателей на блоки MScript растёт на один: новый блок size байт; 3 — нет памяти, 0 — готово. */
/* P77_ListAdd — Game.exe 004f8643, cdecl.  Grow the MScript block list by one new block of `size` bytes.  Returns 0, or 3 (MScript
   "Out of memory") if an allocation fails. */
int32_t P77_ListAdd(int32_t size) {
  void **arr = DebugMalloc((P77_ListN + 1) * (int)sizeof(void *), "D:\\Driver\\Game\\MScript.c", 0xb3f);
  if (arr == NULL) return 3;
#ifdef RE_HOOK_BUILD
  void *blk = DebugMalloc(size, "D:\\Driver\\Game\\MScript.c", 0xb43);
#else
  /* v2.35: +4 — P146_ScriptCmd reads the first argument p[1] of every command, also of 4-byte commands without
     arguments; in Game.exe that word is the debug tag after the block, here it was a heap over-read (ASan) */
  void *blk = DebugMalloc(size + 4, "D:\\Driver\\Game\\MScript.c", 0xb43);
  if (blk != NULL) memset((uint8_t *)blk + size, 0, 4);
#endif
  if (blk == NULL) { DebugFree(arr); return 3; }
  int32_t i;
  for (i = 0; i < P77_ListN; i++) arr[i] = P77_List[i];
  arr[i] = blk;
  if (P77_List != NULL) DebugFree(P77_List);
  P77_ListN = P77_ListN + 1;
  P77_List = arr;
  return 0;
}

/* 004282f8: d — расстояние; матрица вида = 011f4080, плоскость (нормаль = −(0,0,−1)·M, d = (p+cam)·n). */
/* P77_CameraPlane — Game.exe 004282f8, cdecl.  Set the far clip distance d: 01270c24 = d, 01270c44 = d * 1.25 (signed /4 rounding toward
   zero), and the plane P77_Plane = (n, n . (p + camera)) where n = -(0, 0, -1) transformed by
   the view matrix and p = (0, 0, d) transformed.  The dot product is summed in extended
   precision (x87) in the original's order. */
void P77_CameraPlane(int32_t d) {
  float v[3];
  Q01270C24 = (float)d;
  P62_I270C44 = d + ((d + ((d >> 31) & 3)) >> 2);
  P44_MatPtr = (float *)P44_ViewMat;
  v[0] = 0.0f; v[1] = 0.0f; v[2] = -1.0f;
  P44_Xform(v);
  P77_Plane[0] = -v[0]; P77_Plane[1] = -v[1]; P77_Plane[2] = -v[2];
  v[0] = 0.0f; v[1] = 0.0f; v[2] = Q01270C24;
  P44_Xform(v);
  P77_Plane[3] = (float)(((long double)v[2] + P44_CamZ) * P77_Plane[2] + ((long double)v[1] + P44_CamY) * P77_Plane[1] +
                         ((long double)v[0] + P44_CamX) * P77_Plane[0]);
}
