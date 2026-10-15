#include "ported77.h"
#include <stdio.h>
#include <string.h>

GAME_VAR_DEF(const char*, P77_LevelName, 0x00c81164)
GAME_VAR_DEF(int32_t, P77_ListN, 0x00c81688)
GAME_VAR_DEF(void**, P77_List, 0x00c8175c)
GAME_VAR_DEF(p77_plane_t, P77_Plane, 0x011cff80)
GAME_VAR_DEF(p77_b590e0_t, P77_B590E0, 0x00b590e0)
GAME_VAR_DEF(p77_c62d60_t, P77_C62D60, 0x00c62d60)
GAME_VAR_DEF(p77_c65dc0_t, P77_C65DC0, 0x00c65dc0)
GAME_VAR_DEF(p77_c5fe00_t, P77_C5FE00, 0x00c5fe00)
GAME_VAR_DEF(p77_c7d8c0_t, P77_C7D8C0, 0x00c7d8c0)
GAME_VAR_DEF(p77_c62e60_t, P77_C62E60, 0x00c62e60)
GAME_VAR_DEF(uint8_t, P77_C7D850, 0x00c7d850)
GAME_VAR_DEF(int32_t, P77_C7D8A4, 0x00c7d8a4)
GAME_VAR_DEF(int32_t, P77_C7D8A0, 0x00c7d8a0)
GAME_VAR_DEF(int32_t, P77_C7D8A8, 0x00c7d8a8)
GAME_VAR_DEF(int32_t, P77_C65DA4, 0x00c65da4)
GAME_VAR_DEF(int32_t, P77_B5A0E8, 0x00b5a0e8)
GAME_VAR_DEF(int32_t, P77_S574570, 0x00574570)

/* Неперенесённые: загрузчики блоков уровня, обработчик блока 0x14, финальная подготовка, запись банка звуков. */
#define P77_UNPORTED_NONE 0

/* 004eca08: имя файла уровня зависит от режима (00b87eec — плоская карта, состояние 4 / 00b87e98 — iview, 5 / 00b87ea8 — train). */
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
#endif
  return g_fopen(p, "rb");
}

/* 004ecade: файл = число блоков, затем блоки [тип][размер][данные]; (прочие типы пропускаются как в оригинале — без default). */
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
int32_t P77_Menu407160(void) {
  P54_InitInputMode();
  G6_0057B728 = 0; MenuI0057B730 = 1; MenuI0054A060 = 2;
  return screen_loop(0x0054a008, &G6_0057B728, 0x00549f60, 0x00549f78, MenuRed0040766D, 0);
}
int32_t P77_Menu414C30(void) {
  Call00414D1F();
  G6_005FE9CC = 0; MenuI005FE9D0 = 6; MenuI0054DE08 = 7;
  return screen_loop(0x0054dd10, &G6_005FE9CC, 0x0054db58, 0x0054dbc0, MenuRed00415904, 0x004159e5);
}
int32_t P77_Menu408770(void) {
  G6Call004094E3();
  MenuRedraw();
  G6_005D5788 = 0; MenuI005D578C = 0; MenuI0054A694 = 1;
  return screen_loop(0x0054a470, &G6_005D5788, 0x0054a170, 0x0054a250, MenuRed00409C85, 0x00409d66);
}

/* 00509c40 */
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
int32_t P77_ListAdd(int32_t size) {
  void **arr = DebugMalloc((P77_ListN + 1) * (int)sizeof(void *), "D:\\Driver\\Game\\MScript.c", 0xb3f);
  if (arr == NULL) return 3;
  void *blk = DebugMalloc(size, "D:\\Driver\\Game\\MScript.c", 0xb43);
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
