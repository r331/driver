/* Assorted small routines: bounds-track sequencer, name entry, Glide texture source,
   texture lookup, helicopter-marker object boxes, whole-file read, three menu actions. */
#include "ported129.h"
#include "ported149.h"
#include "reptr.h"
#include "ported53.h"
#include <string.h>
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P53_MenuSel")
#undef P53_MenuSel
#pragma push_macro("P53_MenuSel") /*gvi*/
#undef P53_MenuSel /*gvi*/
int32_t P53_MenuSel;
#pragma pop_macro("P53_MenuSel") /*gvi*/
#pragma pop_macro("P53_MenuSel")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P53_FlagF9F4")
#undef P53_FlagF9F4
#pragma push_macro("P53_FlagF9F4") /*gvi*/
#undef P53_FlagF9F4 /*gvi*/
int32_t P53_FlagF9F4;
#pragma pop_macro("P53_FlagF9F4") /*gvi*/
#pragma pop_macro("P53_FlagF9F4")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P53_Var2640")
#undef P53_Var2640
#pragma push_macro("P53_Var2640") /*gvi*/
#undef P53_Var2640 /*gvi*/
uint32_t P53_Var2640;
#pragma pop_macro("P53_Var2640") /*gvi*/
#pragma pop_macro("P53_Var2640")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P53_Mrk")
#undef P53_Mrk
#pragma push_macro("P53_Mrk") /*gvi*/
#undef P53_Mrk /*gvi*/
p53_mrk_t P53_Mrk;
#pragma pop_macro("P53_Mrk") /*gvi*/
#pragma pop_macro("P53_Mrk")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P53_Var2634")
#undef P53_Var2634
#pragma push_macro("P53_Var2634") /*gvi*/
#undef P53_Var2634 /*gvi*/
int32_t P53_Var2634;
#pragma pop_macro("P53_Var2634") /*gvi*/
#pragma pop_macro("P53_Var2634")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P53_Ang2702")
#undef P53_Ang2702
#pragma push_macro("P53_Ang2702") /*gvi*/
#undef P53_Ang2702 /*gvi*/
int16_t P53_Ang2702;
#pragma pop_macro("P53_Ang2702") /*gvi*/
#pragma pop_macro("P53_Ang2702")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P53_ModeTab")
#undef P53_ModeTab
#pragma push_macro("P53_ModeTab") /*gvi*/
#undef P53_ModeTab /*gvi*/
p53_modetab_t P53_ModeTab;
#pragma pop_macro("P53_ModeTab") /*gvi*/
#pragma pop_macro("P53_ModeTab")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P53_TexTab")
#undef P53_TexTab
#pragma push_macro("P53_TexTab") /*gvi*/
#undef P53_TexTab /*gvi*/
p53_textab_t P53_TexTab;
#pragma pop_macro("P53_TexTab") /*gvi*/
#pragma pop_macro("P53_TexTab")
#endif

/* Name-entry keys returned by 0040efd5 (anything > 0 is a character to append). */
enum { NAMEKEY_NONE = 0, NAMEKEY_BACKSPACE = -1, NAMEKEY_ACCEPT = -2, NAMEKEY_CANCEL = -3 };
#define NAME_STRIDE   0x11   /* bytes per name in P52_NameTab (15 characters + NUL + 1) */
#define NAME_MAX_LEN  0xf    /* characters per name */
#define SLOT_BOUNDS_TRACK 0xf  /* sound/track slot polled by P53_StepBounds */
#define GRTEXFMT_KIND_5   5    /* GrTexInfo format at +0xc that addresses textures in 64 KiB units */
#define TEXTAB_N          0x20 /* entries in P53_TexTab (0x20 bytes each) */

/* P53_StepBounds — Game.exe 004d6354, cdecl.  Advance the track/bounds sequence: when slot 0xf is idle, start the next entry of the
   int32 list A_00B20330 (index 00b20344, post-incremented); a -1 entry ends the list —
   clears the slots and increments 00b20360.  TODO(RE): unsure what the list holds (the
   header calls it "bounds records"; TryStartTrack suggests audio tracks). */
void P53_StepBounds(void) {
  if (IsSlotActive00524473(SLOT_BOUNDS_TRACK) != 0) return;
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

/* P53_NameEntryKey — Apply one name-entry key to the current name (row P52_MenuCnt of P52_NameTab, cursor
   P52_MenuC): -3 cancels (closes the menu), -2 accepts a non-empty name and reloads the menu,
   -1 deletes the last character, any other non-zero key appends a character (max 15).
   Native split of the second half of 005101f0. */
void P53_NameEntryKey(int32_t key) {
  switch (key) {
  case NAMEKEY_NONE: break;
  case NAMEKEY_CANCEL: P52_MenuA = 0; P52_MenuB = 0; Call00510784(); break;
  case NAMEKEY_ACCEPT: if (P52_MenuC != 0) { P52_MenuB = 1; P52_MenuReload(); } break;
  case NAMEKEY_BACKSPACE:
    if (0 < P52_MenuC) { P52_MenuC = P52_MenuC - 1; P52_NameTab[P52_MenuC + P52_MenuCnt * NAME_STRIDE] = 0; }
    break;
  default:
    if (P52_MenuC < NAME_MAX_LEN) {
      P52_NameTab[P52_MenuC + P52_MenuCnt * NAME_STRIDE] = (uint8_t)key;
      P52_MenuC = P52_MenuC + 1;
      P52_NameTab[P52_MenuC + P52_MenuCnt * NAME_STRIDE] = 0;
    }
  }
}
/* P53_NameEntry — Game.exe 005101f0, cdecl.  Read a key with 0040efd5 and apply it with P53_NameEntryKey. */
void P53_NameEntry(void) { P53_NameEntryKey(P53_Fn40EFD5()); }

/* P53_SetTexSource — Game.exe 0041f76f, stdcall (ret 16).  Glide grTexSource emulation: select the texture whose memory address is `addr`.
   info is the GrTexInfo address; for format kind 5 the slot is addr >> 16, otherwise
   (addr >> 17) * 2.  A slot < 0x20 becomes current (P22_TexVarA/B, P32_CurHandle from
   P53_TexTab, palette slot -1); otherwise the (release-build empty) error hook is called.
   a and c (tmu, even/odd) are unused.  Does nothing when the device is not ready. */
void P53_SetTexSource(int32_t a, uint32_t addr, int32_t c, uint32_t info) {
  (void)a; (void)c;
  if (P22_DevReady == 0) return;
  const uint8_t *d = (const uint8_t *)re_ptr(info);   /* v2.01: GrTexInfo — 32-битный адрес (re_addr), как в ячейке Glide */
#ifndef RE_HOOK_BUILD
  if (d == NULL) return;
#endif
  int32_t kind; memcpy(&kind, d + 0xc, 4);
  uint32_t idx = (kind == GRTEXFMT_KIND_5) ? (addr >> 0x10) : ((addr >> 0x11) << 1);   /* texture memory address -> slot */
  if (idx < TEXTAB_N) {
    uint32_t h; memcpy(&h, &P53_TexTab[idx * 0x20], 4);
    P22_TexVarA = (int32_t)idx;
    P22_TexVarB = (int32_t)idx;
    P32_CurHandle = (void *)(uintptr_t)h;
    P32_CurSlot = -1;
  } else {
    NoopFn0042243f();   /* «ERROR: Invalid texture source address» (в релизе — пусто) */
  }
}

/* P53_TexLookup — Game.exe 0041d63b, cdecl.  Find the emulated texture node for `handle` in P46_TexHead and add (b, c, d) to it, or create
   a new node.  Returns 1 when 00a421f0 is clear.  TODO(RE): unsure what b/c/d are. */
int32_t P53_TexLookup(int32_t handle, int32_t b, int32_t c, int32_t d) {
  if (G6_00A421F0 == 0) return 1;
  for (P46_TexNode *n = P46_TexHead; n != NULL; n = n->next)
    if (n->handle == handle) return P149_EmulAddSub(n, b, c, d);
  return P149_EmulNew(handle, b, c, d);
}

/* P53_CallWithState — Game.exe 00500154, cdecl.  Address-based wrapper of P53_CallWithStateP (a = position, b = car, as Game.exe addresses). */
void P53_CallWithState(int32_t a, int32_t b, int32_t c) {
  P53_CallWithStateP((const float *)re_ptr((uint32_t)a), (uint8_t *)re_ptr((uint32_t)b), c);
}
/* v1.74: вариант с родными указателями (позиция, машина) — вызов из P129_CarObjects */
/* P53_CallWithStateP — Build an 8-word state block {0, 00d02640, marker position x/y/z/w (P53_Mrk[0..3] as float
   bits), -00d02702 & 0xfff (negated angle), 0} and pass it with pos, car, c and 00d02634 to
   P129_ObjBoxes.  Native variant with real pointers (called from P129_CarObjects). */
void P53_CallWithStateP(const float *pos, uint8_t *car, int32_t c) {
  uint32_t st[8];
  memset(st, 0, sizeof st);
  st[1] = P53_Var2640; memcpy(&st[2], &P53_Mrk[0], 16);   /* 00d026a0..ac — биты float */
  st[6] = (uint32_t)(-(int32_t)P53_Ang2702) & 0xfffu;
  P129_ObjBoxes((uint8_t *)st, pos, car, c, (uint32_t)P53_Var2634, 0);
}

/* P53_ReadWholeFile — Game.exe 004d303a, cdecl.  Read the whole file `name` into buf.  Returns its size, or 0 if it cannot be opened or read
   (on a read error the file is left open, as in the original). */
int32_t P53_ReadWholeFile(const char *name, void *buf) {
  void *f = g_fopen(name, "rb");
  if (f == NULL) return 0;
  int32_t size = P51_FileSize(f);
  if (P27_ReadChunked(buf, size, 1, f) == 0) return 0;   /* как в оригинале: файл не закрывается при сбое */
  g_fclose(f);
  return size;
}

/* P53_MenuA — Game.exe 004161b3, cdecl.  Front-end menu action.  Sets menu mode 8; with 00bdf9f4 clear either starts the game screen
   directly (00b87e38 == 0x30) or runs 004082a0, otherwise runs 004045e0; on result 0 shows the
   message pair 0054df98/0054dfc0.  Returns the result.  TODO(RE): unsure which menu entry this is. */
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

/* P53_MenuB — Game.exe 004046c8, cdecl.  Front-end menu action: sets 00bdfa40 = 0057b56c + 1, then like P53_MenuA's first branch with
   the message pair 00549a30/00549a58.  TODO(RE): unsure which menu entry this is. */
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

/* P53_MenuC — Game.exe 00414638, cdecl.  Front-end menu action: for menu modes 1..7 and 0xb set the game mode 00b87e38 from
   P53_ModeTab[mode][selected row] and start the game screen; modes 1, 2, 3, 7, 0xb also call
   004146fb when 0054da10 is set.  Returns 1. */
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
