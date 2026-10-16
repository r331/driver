#include "ported129.h"
#include "reptr.h"
#include "ported53.h"
#include <string.h>
GAME_VAR_DEF(int32_t, P53_MenuSel, 0x01271064)
GAME_VAR_DEF(int32_t, P53_FlagF9F4, 0x00bdf9f4)
GAME_VAR_DEF(uint32_t, P53_Var2640, 0x00d02640)
GAME_VAR_DEF(p53_mrk_t, P53_Mrk, 0x00d026a0)
GAME_VAR_DEF(int32_t, P53_Var2634, 0x00d02634)
GAME_VAR_DEF(int16_t, P53_Ang2702, 0x00d02702)
GAME_VAR_DEF(p53_modetab_t, P53_ModeTab, 0x0054d890)
GAME_VAR_DEF(p53_textab_t, P53_TexTab, 0x00621c4c)

void P53_StepBounds(void) {
  if (IsSlotActive00524473(0xf) != 0) return;
  int32_t idx = G8_00B20344, v;
  memcpy(&v, &A_00B20330[idx * 4], 4);
  if (v == -1) {
    ClearSlots004D61CF();
    P11_00b20360 = P11_00b20360 + 1;
  } else {
    G8_00B20344 = idx + 1;
    TryStartTrack_004D611B((uint32_t)v);
  }
}

void P53_NameEntryKey(int32_t key) {
  switch (key) {
  case 0: break;
  case -3: P52_MenuA = 0; P52_MenuB = 0; Call00510784(); break;
  case -2: if (P52_MenuC != 0) { P52_MenuB = 1; P52_MenuReload(); } break;
  case -1:
    if (0 < P52_MenuC) { P52_MenuC = P52_MenuC - 1; P52_NameTab[P52_MenuC + P52_MenuCnt * 0x11] = 0; }
    break;
  default:
    if (P52_MenuC < 0xf) {
      P52_NameTab[P52_MenuC + P52_MenuCnt * 0x11] = (uint8_t)key;
      P52_MenuC = P52_MenuC + 1;
      P52_NameTab[P52_MenuC + P52_MenuCnt * 0x11] = 0;
    }
  }
}
void P53_NameEntry(void) { P53_NameEntryKey(P53_Fn40EFD5()); }

void P53_SetTexSource(int32_t a, uint32_t addr, int32_t c, const uint8_t *d) {
  (void)a; (void)c;
  if (P22_DevReady == 0) return;
  int32_t kind; memcpy(&kind, d + 0xc, 4);
  uint32_t idx = (kind == 5) ? (addr >> 0x10) : ((addr >> 0x11) << 1);
  if (idx < 0x20) {
    uint32_t h; memcpy(&h, &P53_TexTab[idx * 0x20], 4);
    P22_TexVarA = (int32_t)idx;
    P22_TexVarB = (int32_t)idx;
    P32_CurHandle = (void *)(uintptr_t)h;
    P32_CurSlot = -1;
  } else {
    NoopFn0042243f();   /* «ERROR: Invalid texture source address» (в релизе — пусто) */
  }
}

int32_t P53_TexLookup(int32_t handle, int32_t b, int32_t c, int32_t d) {
  if (G6_00A421F0 == 0) return 1;
  for (P46_TexNode *n = P46_TexHead; n != NULL; n = n->next)
    if (n->handle == handle) return P53_Fn42248B(n, b, c, d);
  return P53_Fn4225EB(handle, b, c, d);
}

void P53_CallWithState(int32_t a, int32_t b, int32_t c) {
  P53_CallWithStateP((const float *)re_ptr((uint32_t)a), (uint8_t *)re_ptr((uint32_t)b), c);
}
/* v1.74: вариант с родными указателями (позиция, машина) — вызов из P129_CarObjects */
void P53_CallWithStateP(const float *pos, uint8_t *car, int32_t c) {
  uint32_t st[8];
  memset(st, 0, sizeof st);
  st[1] = P53_Var2640; memcpy(&st[2], &P53_Mrk[0], 16);   /* 00d026a0..ac — биты float */
  st[6] = (uint32_t)(-(int32_t)P53_Ang2702) & 0xfffu;
  P129_ObjBoxes((uint8_t *)st, pos, car, c, (uint32_t)P53_Var2634, 0);
}

int32_t P53_ReadWholeFile(const char *name, void *buf) {
  void *f = g_fopen(name, "rb");
  if (f == NULL) return 0;
  int32_t size = P51_FileSize(f);
  if (P27_ReadChunked(buf, size, 1, f) == 0) return 0;   /* как в оригинале: файл не закрывается при сбое */
  g_fclose(f);
  return size;
}

int32_t P53_MenuA(void) {
  int32_t r;
  MenuAction40CD17();
  MenuMode1271060 = 8;
  if (P53_FlagF9F4 == 0) {
    if (P11_00b87e38 == 0x30) { UiCall0040C455(1, 0); return 1; }
    r = R12_4082A0();
  } else {
    r = P53_Fn4045E0();
  }
  if (r == 0) Call0040CCB4(0x0054df98u, 0x0054dfc0u);
  return r;
}

int32_t P53_MenuB(void) {
  int32_t r;
  P12_00bdfa40 = Q0057B56C + 1;
  MenuAction40CD17();
  if (P11_00b87e38 == 0x30) {
    UiCall0040C455(1, 0);
    r = 1;
  } else {
    r = R12_4082A0();
    if (r == 0) Call0040CCB4(0x00549a30u, 0x00549a58u);
  }
  return r;
}

int32_t P53_MenuC(void) {
  MenuAction40CD17();
  int32_t m = MenuMode1271060;
  switch (m) {
  case 1: case 2: case 3: case 7: case 0xb:
    P11_00b87e38 = (int32_t)P53_ModeTab[m * 8 + P53_MenuSel];
    UiCall0040C455(1, 0);
    if (P8_0054da10 != 0) P53_Fn4146FB(m);
    break;
  case 4: case 5: case 6:
    P11_00b87e38 = (int32_t)P53_ModeTab[m * 8 + P53_MenuSel];
    UiCall0040C455(1, 0);
    break;
  default: break;
  }
  return 1;
}
