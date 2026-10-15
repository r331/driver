#include "ported59.h"
#include "sintab_data.h"
#include <string.h>
#include <stdio.h>

GAME_VAR_DEF(float, P59_CamF1, 0x01270c24)
GAME_VAR_DEF(float, P59_CamLim, 0x005460e8)
GAME_VAR_DEF(float, P59_VX, 0x00b1c270)
GAME_VAR_DEF(float, P59_VY, 0x00b1c274)
GAME_VAR_DEF(float, P59_VZ, 0x00b1c278)
GAME_VAR_DEF(uint16_t, P59_AngA, 0x00b1c268)
GAME_VAR_DEF(uint16_t, P59_AngB, 0x00b1c26a)
GAME_VAR_DEF(uint16_t, P59_AngC, 0x00b1c26c)
GAME_VAR_DEF(uint8_t, P59_Mode1137324, 0x01137324)
GAME_VAR_DEF(uint8_t *, P59_CarsTab, 0x0113a6c4)
GAME_VAR_DEF(p59_tab_c39dc0_t, P59_C39DC0, 0x00c39dc0)
GAME_VAR_DEF(int32_t, P59_ModelCount, 0x01134120)
GAME_VAR_DEF(p59_u8x9_t, P59_Flags9, 0x00d04a50)
GAME_VAR_DEF(int8_t, P59_Picked, 0x00d04650)
GAME_VAR_DEF(int32_t, P59_S4654, 0x00d04654)
GAME_VAR_DEF(int32_t, P59_S44CC, 0x00d044cc)
GAME_VAR_DEF(int32_t, P59_S4790, 0x00d04790)
GAME_VAR_DEF(int32_t, P59_S3904, 0x00d03904)
GAME_VAR_DEF(p59_i32x18_t, P59_PickTab, 0x00562ae0)
GAME_VAR_DEF(int32_t, P59_NearN, 0x00c7d7e0)
GAME_VAR_DEF(p59_u8x64_t, P59_NearList, 0x00c7d860)
GAME_VAR_DEF(p59_sin_t, P59_Sin, 0x00576f10)
GAME_VAR_DEF(p59_hdr_t, P59_Hdr, 0x0057b6f0)
GAME_VAR_DEF(p59_rep_t, P59_Rep57B6B8, 0x0057b6b8)
GAME_VAR_DEF(int32_t, P59_NoKeyFlag, 0x005feda0)
GAME_VAR_DEF(int32_t, P59_MenuLock, 0x005fea54)
GAME_VAR_DEF(float, P59_One, 0x00546020)
#ifndef RE_HOOK_BUILD
char *P59_VarStr[77];
#endif

#ifdef RE_HOOK_BUILD
_Static_assert(sizeof(p42_var_t) == 0x30, "p42_var_t");
#endif

static uint32_t rd32(const uint8_t *p, uint32_t o) { uint32_t v; memcpy(&v, p + o, 4); return v; }
static int16_t  rd16s(const uint8_t *p, uint32_t o) { int16_t v; memcpy(&v, p + o, 2); return v; }
static void     wr32(uint8_t *p, uint32_t o, uint32_t v) { memcpy(p + o, &v, 4); }

void P59_InitConsts(void) {
#ifndef RE_HOOK_BUILD
  memcpy(P59_Sin, P59_SinInit, sizeof P59_Sin);
  P59_CamLim = 2000.0f; P59_One = 1.0f;
#endif
}

/* 0049c910: камера — положение из объекта, высота над землёй не больше 28672. */
void P59_SetupCamera(void) {
  float lim = 28672.0f;
  float d = P59_CamF1 - P59_CamLim;
  if (d < lim) lim = d;
  P59_VX = (float)P59_PosX;
  P59_VY = -(float)P59_PosY - lim;
  P59_VZ = (float)P59_PosZ;
  P59_AngA = 0x400; P59_AngB = 0; P59_AngC = 0;
  InitXform_005263FE();
  P59_Mode1137324 = 6;
}

/* 004f8a2d: строковая переменная скрипта (тип 1): новая копия строки, старая освобождается. */
void P59_VarSetString(int32_t idx, const char *s) {
  if (P42_Vars[idx].type != 1) return;
  size_t n = strlen(s);
  char *buf = (char *)DebugMalloc((int)(n + 1), "D:\\Driver\\Game\\MScript.c", 0xc38);
  if (buf == NULL) return;
#ifdef RE_HOOK_BUILD
  if (P42_Vars[idx].addr != 0) { DebugFree((void *)(uintptr_t)P42_Vars[idx].addr); P42_Vars[idx].addr = 0; }
  memcpy(buf, s, n + 1);
  P42_Vars[idx].addr = (uint32_t)(uintptr_t)buf;
#else
  if (P59_VarStr[idx] != NULL) { DebugFree(P59_VarStr[idx]); P59_VarStr[idx] = NULL; }
  memcpy(buf, s, n + 1);
  P59_VarStr[idx] = buf;
#endif
}

/* 004f892a: начальные значения переменных: тип 1 — строка (lo), 3 — число (hi), 4 — без действия.
   Оригинал идёт до записи с типом 0x7f; в native таблица пока пуста, поэтому цикл ограничен 76 записями. */
void P59_VarsInit(void) {
  for (int32_t i = 0; i < 76 && P42_Vars[i].type != 0x7f; i++) {
    switch (P42_Vars[i].type) {
    case 1:
#ifdef RE_HOOK_BUILD
      P59_VarSetString(i, (const char *)(uintptr_t)(uint32_t)P42_Vars[i].lo);
#endif
      break;
    case 3: SetTableValue_004F89B7(i, (uint32_t)P42_Vars[i].hi); break;
    case 4: NoopFn004F89EB(); break;
    default: break;
    }
  }
}

/* 0048eca3: есть ли в трафике чужая запись с тем же узлом (+0x28), направлением (+0x24) и малым расстоянием/задержкой. */
int32_t P59_TrafficFind(uint32_t self, int32_t a, uint32_t b) {
  const uint8_t *e = P12_011443e0;
  int32_t lim = (rd32(P12_011443e0, (self & 63) * 0x54 + 0x34) == 0) ? 3000 : 6000;
  for (int32_t i = 0; i < P51_TrafficN; i++, e += 0x54) {
    if (e[1] != 0 && e[1] != 1 && (uint32_t)e[0] != self && (int32_t)rd32(e, 0x28) == a && rd32(e, 0x24) == (b & 0xff) &&
        (int32_t)rd32(e, 0x1c) < lim && (int32_t)rd32(e, 0x38) < 0x1e) return 1;
  }
  return 0;
}

/* 0048ed6f: r — запись трафика (машина r[0], узел +0x2c, направление r[0x30], поле +0x20). */
int32_t P59_TrafficCheck(const uint8_t *r, int32_t flag) {
  uint32_t node = rd32(r, 0x2c);
  if (flag != 0 && Ret1() == 0) return 1;
  int16_t v = (node < 64) ? rd16s(P59_BF1C48, node * 0x42) : 0;
  if (v < 4 && P51_TrafficConflict(r[0], (int32_t)node, r[0x30], (int32_t)rd32(r, 0x20)) != 0) return 1;
  return P59_TrafficFind(r[0], (int32_t)node, r[0x30]);
}

/* 00491650: сколько клеток осталось до границы участка (по направлению k) для записи r. */
uint32_t P59_CellLeft(const uint8_t *r) {
  const uint8_t *car = P59_CarsTab + r[0] * 0x148;
  uint32_t v28 = rd32(r, 0x28);
  if ((v28 & 0xc000) == 0 && (int32_t)v28 >= 0) {
    uint32_t k = rd32(r, 0x24);
    const uint8_t *rec = P59_C39DC0 + v28 * 0x24;
    if (rec[k] == 1) return k & 0xffffff00u;
    int32_t c = 0;
    switch (k) {
    case 0: c = (((int32_t)rd32(car, 200) + 0x2ee) - (int32_t)rd32(rec, 4)) / 0x5dc; break;
    case 1: c = ((int32_t)rd32(rec, 0x10) - ((int32_t)rd32(car, 0xd0) - 0x2ee)) / 0x5dc; break;
    case 2: c = ((int32_t)rd32(rec, 0x14) - ((int32_t)rd32(car, 200) - 0x2ee)) / 0x5dc; break;
    case 3: c = (((int32_t)rd32(car, 0xd0) + 0x2ee) - (int32_t)rd32(rec, 0x20)) / 0x5dc; break;
    default: break;                                          /* в оригинале переменная не задана */
    }
    return (uint32_t)(((int32_t)rec[k] - c) - 1);
  }
  return (uint32_t)(uintptr_t)r & 0xffffff00u;
}

/* 004a3f06: раздел MODEL_NAMES: каждое имя (до CHUNK_END) передаётся разборщику 004a5634 с номером. */
const char *P59_ModelNames(const char *text) {
  P59_ModelCount = 0;
  int32_t idx = 0;
  char *p = P51_SkipToLine((char *)text, "MODEL_NAMES");
  p = SkipLine004A59C6(p);
  while (P51_PrefixMatch(p, "CHUNK_END") != 1) {
    const char *q = (const char *)SkipToIdentStart_004A596B((const uint8_t *)p);
    P59_Fn4A5634(q, idx);
    p = SkipLine004A59C6((char *)q);
    idx = (int32_t)(int16_t)(idx + 1);
  }
  return p;
}

/* 004a6dcd: машины полиции/трафика рядом с self (4a6a57), индексы кладёт в список. */
int32_t P59_NearCars(const int32_t *self) {
  const uint8_t *rec = P12_011443e0;
  const uint8_t *car = P59_CarRecs;
  P59_NearN = 0;
  for (int32_t i = 0; i < 64; i++, car += 0x148, rec += 0x54) {
    if (rec[1] != 0 && (uint32_t)rec[5] != (uint32_t)*self + 1u && P59_Fn4A6A57(self, rec, car) != 0) {
      P59_NearList[P59_NearN] = (uint8_t)i;
      P59_NearN++;
    }
  }
  return P59_NearN != 0;
}

/* 004e5ea2: подобрать предмет i (9 штук): подпись, звук; после девятого — режим 2. */
int32_t P59_PickUp(int32_t i) {
  if (P59_Flags9[i] != 0) return 0;
  P59_Flags9[i] = 1;
  P59_Picked++;
  P12_Fn004E5982(P59_PickTab[i * 2], 0x96, 0);
  if (P59_PickTab[i * 2 + 1] != -1) Call004D6190(P59_PickTab[i * 2 + 1] + 0xf000);
  if (P59_Picked == 9) P59_S4654 = 2;
  P59_S44CC = 0; P59_S4790 = 0; P59_S3904 = 0;
  return 1;
}

/* 004daac7: положение в 1/16 (mode 1), скорость 0, направление из таблицы синусов (угол +0x100), затем 004da8d9. */
void P59_ObjDir(uint8_t *o, int32_t mode) {
  if (mode == 1) {
    wr32(o, 0x24, rd32(o, 200) << 4); wr32(o, 0x28, rd32(o, 0xcc) << 4); wr32(o, 0x2c, rd32(o, 0xd0) << 4);
  }
  uint32_t ix = (uint32_t)((int32_t)rd32(o, 0x100) / 2) & 0xfff;
  wr32(o, 0x30, 0);
  wr32(o, 0x34, (uint32_t)(int32_t)P59_Sin[ix]);
  wr32(o, 0x38, 0);
  wr32(o, 0x3c, (uint32_t)(int32_t)P59_Sin[(ix + 0x400) & 0xfff]);
  P56_ObjSync((int32_t *)(void *)(o + 0x24), o);
}

/* 00405fdb: SAVES\REPLAYn.BIN — подпись 0x38910457 и сумма 0x38 байт; при успехе копия заголовка в out. */
int32_t P59_ReplayCheck(int32_t slot, void *out) {
  char name[32];
  snprintf(name, sizeof name, "SAVES\\REPLAY%d.BIN", slot + 1);
  void *f = g_fopen(name, "rb");
  if (f == NULL) return 0;
  g_fread(P59_Hdr, 1, 8, f);
  g_fread(P59_Rep57B6B8, 1, 0x38, f);
  g_fclose(f);
  if (P59_Hdr[0] == 0x38910457u && P56_Fn40682D(P59_Rep57B6B8, 0x38) == (int32_t)P59_Hdr[1]) {
    if (out != NULL) memcpy(out, P59_Rep57B6B8, 0x38);
    return 1;
  }
  return 0;
}

/* 00417d56: Esc / стрелки / Enter в меню. Возвращает -1, если выбор сделан (00417970 вернула 1). */
int32_t P59_MenuKeys(void) {
  if (IsKeyDown(1) == 0 || P59_NoKeyFlag != 0 || P58_MenuFn != 0) {
    if (IsKeyDown(0xcb) == 0) {
      if (IsKeyDown(0xcd) == 0) {
        if (IsKeyDown(0x1c) != 0) { Ui00418886(); P59_MenuLock = 0; P58_MenuSwitch(); }
      } else { P58_MenuFn = 0; Ui00418886(); MenuPageNext00417F59(); }
    } else { P58_MenuFn = 0; Ui00418886(); MenuPagePrev00417FAC(); }
  } else {
    Ui00418886();
    P59_MenuLock = 0;
    if (P59_Fn417970() == 1) return -1;
  }
  return 0;
}

/* 0040d4b3: блок из файла: [2 байта пропуска при scale > 1] + заголовок 0x14 байт (размеры минус 0x14) + данные. */
void *P59_ReadBlock(void *file, float scale, int32_t *hdr) {
  if (P59_One < scale) { uint8_t skip[4]; g_fread(skip, 1, 2, file); }
  g_fread(hdr, 1, 0x14, file);
  hdr[0] -= 0x14; hdr[1] -= 0x14; hdr[2] -= 0x14;
  void *buf = DebugMalloc(hdr[0], "D:\\Driver\\Game\\frontend\\frontend.c", 0x3f5);
  if (buf == NULL) { g_fclose(file); return NULL; }
  g_fread(buf, 1, hdr[0], file);
  return buf;
}
