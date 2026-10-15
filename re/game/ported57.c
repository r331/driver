#include "ported57.h"
#include "crt.h"
#include <string.h>

GAME_VAR_DEF(int32_t, P57_S5D5794, 0x005d5794)
GAME_VAR_DEF(int32_t, P57_S5D5774, 0x005d5774)
GAME_VAR_DEF(int32_t, P57_S5FE4EC, 0x005fe4ec)
GAME_VAR_DEF(int32_t, P57_S5FE990, 0x005fe990)
GAME_VAR_DEF(int32_t, P57_S5FE9A0, 0x005fe9a0)
GAME_VAR_DEF(int32_t, P57_S5D579C, 0x005d579c)
GAME_VAR_DEF(int32_t, P57_S5FE6B8, 0x005fe6b8)
GAME_VAR_DEF(int32_t, P57_S5FE998, 0x005fe998)
GAME_VAR_DEF(int32_t, P57_S5FE9A8, 0x005fe9a8)
GAME_VAR_DEF(int32_t, P57_S5FE9E8, 0x005fe9e8)
GAME_VAR_DEF(int32_t, P57_S57B568, 0x0057b568)
GAME_VAR_DEF(int32_t, P57_S5FE848, 0x005fe848)
GAME_VAR_DEF(int32_t, P57_S5FE924, 0x005fe924)
GAME_VAR_DEF(int32_t, P57_ScrW, 0x00c80890)
GAME_VAR_DEF(float, P57_Div1500, 0x005469c4)

/* Начальные значения констант из .data Game.exe (нужны только native). */
void P57_InitConsts(void) {
#ifndef RE_HOOK_BUILD
  P57_Div1500 = 1500.0f;
#endif
}

/* 0040cd17: SetMenuIdle — остановить таймер, 6 раз: сообщения, ввод, шаг i (0040cb9f читает его из 5f7e48). */
void P57_MenuDone(void) {
  Call004086EA();
  Ui0040C87A();
  P45_Busy = 1;
  for (int32_t i = 0; i < 6; i++) {
    Call00522323();
    Call004E3391();
    P45_Step = i;
    Call0040CB9F();
  }
  P45_Busy = 0;
}

/* Общая часть: таблица пунктов, ожидание-прокрутка, опрос меню до ненулевого результата. state уже обнулён. */
static int32_t menu_run(uint32_t tbl, int32_t *state, uint32_t a, uint32_t b) {
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
static int32_t menu_end(int32_t r) {
  if (r == -1) { P57_MenuDone(); r = 0; }
  return r;
}

int32_t P57_Menu40A3A0(void) {
  P57_Setup40A41C(); P57_S5D5794 = 0;
  return menu_end(menu_run(0x0054a870, &P57_S5D5794, 0x0054a818, 0x0054a830));
}
int32_t P57_Menu4082A0(void) {
  P57_Setup40831C(); P57_S5D5774 = 0;
  return menu_end(menu_run(0x0054a0e8, &P57_S5D5774, 0x0054a0a0, 0x0054a0b8));
}
int32_t P57_Menu40E870(void) {
  Call0040EA70(); P57_S5FE4EC = 0;
  return menu_end(menu_run(0x0054ad60, &P57_S5FE4EC, 0x0054aca8, 0x0054acc0));
}
int32_t P57_Menu4134A0(void) {
  P57_Setup41351C(); P57_S5FE990 = 0;
  return menu_end(menu_run(0x0054d138, &P57_S5FE990, 0x0054d0e0, 0x0054d0f8));
}
int32_t P57_Menu413890(void) {
  P57_Setup41390C(); P57_S5FE9A0 = 0;
  return menu_end(menu_run(0x0054d300, &P57_S5FE9A0, 0x0054d278, 0x0054d290));
}
int32_t P57_Menu40A540(void) {
  P57_Setup40A5C6(); P57_S5D579C = 0;
  int32_t r = menu_run(0x0054a968, &P57_S5D579C, 0x0054a8c0, 0x0054a8d8);
  MenuMode1271060 = 0;
  return menu_end(r);
}
int32_t P57_Menu40F2D0(void) {
  Call0040F3DE(); P57_S5FE6B8 = 0;
  return menu_end(menu_run(0x0054bee8, &P57_S5FE6B8, 0x0054bcf0, 0x0054bd08));
}
int32_t P57_Menu413610(void) {
  P57_Setup413691(); P57_S5FE998 = 0;
  int32_t r = menu_run(0x0054d200, &P57_S5FE998, 0x0054d188, 0x0054d1a0);
  P47_Fn405BFA();
  return menu_end(r);
}
int32_t P57_Menu413B00(void) {
  P57_Setup413B7C(); P57_S5FE9A8 = 0;
  return menu_end(menu_run(0x0054d418, &P57_S5FE9A8, 0x0054d390, 0x0054d3a8));
}
int32_t P57_Menu416390(void) {
  P57_Setup41640C(); P57_S5FE9E8 = 0;
  return menu_end(menu_run(0x0054e1d0, &P57_S5FE9E8, 0x0054e168, 0x0054e190));
}
int32_t P57_Menu4045E0(void) {
  Q0057B56C = P12_00bdfa40 - 1;
  if (Q0057B56C < 0) Q0057B56C = 0;
  P57_Setup40479B(); P57_S57B568 = 0;
  int32_t r = menu_run(0x00549a78, &P57_S57B568, 0x00549a30, 0x00549a58);
  MenuFlag5F7E4C = 0;
  return menu_end(r);
}
/* 00404850: как выше, но перед каждым опросом копирует состояние в 57b65c; после цикла — 00405bfa. */
int32_t P57_Menu404850(void) {
  int32_t r;
  P57_Setup4048DD(); S_0057B658 = 0;
  P57_MenuInit(0x0057b5a8, 0);
  Call0040CCB4(0x00549ae8, 0x00549b00);
  for (;;) {
    Call00522323();
    Call004E3391();
    S_0057B65C = S_0057B658;
    r = P57_MenuStep(0x0057b5a8, &S_0057B658);
    if (r != 0) break;
    Call0040CB9F();
  }
  P47_Fn405BFA();
  return menu_end(r);
}
/* 00411fd0 / 004123d0: пока открыта подсказка (флаг), Esc/Enter её закрывает, иначе опрос меню. */
int32_t P57_Menu411FD0(void) {
  int32_t r;
  P57_Setup412087(); P57_Setup412280();
  P57_S5FE848 = 0; UiVar005FE84C = 0;
  P57_MenuInit(0x0054c810, 0);
  Call0040CCB4(0x0054c6b8, 0x0054c6d0);
  for (;;) {
    Call00522323();
    Call004E3391();
    if (UiVar005FE850 == 0) {
      r = P57_MenuStep(0x0054c810, &P57_S5FE848);
      if (r != 0) return menu_end(r);
    } else if (IsKeyDown(1) != 0 || IsKeyDown(0x1c) != 0) {
      P57_Setup4122E7();
    }
    Call0040CB9F();
  }
}
int32_t P57_Menu4123D0(void) {
  int32_t r;
  P57_Setup412487(); P57_Setup41269B();
  P57_S5FE924 = 0; UiVar005FE928 = 0;
  P57_MenuInit(0x0054ca80, 0);
  Call0040CCB4(0x0054c928, 0x0054c940);
  for (;;) {
    Call00522323();
    Call004E3391();
    if (UiVar005FE92C == 0) {
      r = P57_MenuStep(0x0054ca80, &P57_S5FE924);
      if (r != 0) return menu_end(r);
    } else if (IsKeyDown(1) != 0 || IsKeyDown(0x1c) != 0) {
      P57_Setup412702();
    }
    Call0040CB9F();
  }
}

/* 004c92c0 / 004c9310: сохранить/загрузить данные режиссёра в файл name; 1 — успех. */
int32_t SaveDirector(const char *name) {
  void *f = g_fopen(name, "wb");
  if (f == 0) {
    DebugLog("SaveDirector: Unable to write director data file.  Please make sure target is not write protected.");
    return 0;
  }
  WriteDirectorData(f);
  g_fclose(f);
  return 1;
}
int32_t LoadDirector(const char *name) {
  void *f = g_fopen(name, "rb");
  if (f == 0) {
    DebugLog("LoadDirector: Unable to open director file, please make sure it exists.");
    return 0;
  }
  ReadDirectorData(f);
  g_fclose(f);
  return 1;
}
/* 004c93b1: если есть точки пути — пересчитать их и записать режиссёра. */
void P57_SaveDirectorIfAny(const char *name) {
  if (WaypointDirty != 0 || WaypointCount != 0) {
    LoadWaypoints();
    DirectorLastFrame = G8_00D118C0 - 4;
    SaveDirector(name);
  }
}

/* 00406439 / 00406479: чтение и запись таблицы рекордов SAVES\SCORES.HI. */
void P57_LoadScores(void) {
  P57_Fn51C900();
  void *f = g_fopen("SAVES\\SCORES.HI", "rb");
  if (f != 0) { P57_Fn51CAA7(f); g_fclose(f); }
}
void P57_SaveScores(void) {
  void *f = g_fopen("SAVES\\SCORES.HI", "wb");
  if (f != 0) { P57_Fn51CB98(f); g_fclose(f); }
}
/* 00406b51: файл name открывается на чтение? */
int32_t P57_FileExists(const char *name) {
  void *f = g_fopen(name, "rb");
  if (f != 0) { g_fclose(f); return 1; }
  return 0;
}
/* 004d30a3: записать size байт из buf в новый файл name. При неудаче записи файл не закрывается (как в оригинале). */
int32_t P57_WriteFile(const char *name, const void *buf, int32_t size) {
  void *f = g_fopen(name, "wb");
  if (f == 0) return 0;
  if (g_fwrite(buf, (size_t)size, 1, f) == 0) return 0;
  g_fclose(f);
  return 1;
}
/* 004ec2ec: прочитать и выбросить блок size байт из файла уровня. */
void P57_SkipBlock(void *file, int32_t size) {
  void *buf = DebugMalloc(size, "D:\\Driver\\Game\\map.c", 0x347);
  P27_ReadChunked(buf, 1, size, file);
  DebugFree(buf);
}
/* 00421a39: сброс 32 слотов текстур. */
void P57_ResetTexNodes(void) {
  Call0041D6AA();
  for (int32_t i = 0; i < 0x20; i++) P57_Fn4221BF(i);
  P32_CurHandle = 0;
  P31_DDVal5 = 0;
}
/* 005075f6: экранные координаты → вид (x87: деление и сложение в расширенной точности). */
void P57_ScreenToView(float *x, float *y) {
  float lx = *x, ly = *y;
  float wi = (float)P57_ScrW, hi = (float)S_00C808A0;
  lx = (float)((long double)lx / P57_Div1500 + (long double)wi / P19_DivC);
  ly = (float)((long double)(-ly) / P57_Div1500 + (long double)hi / P19_DivC);
  P57_Fn507672(&lx, &ly);
  *x = lx; *y = ly;
}
