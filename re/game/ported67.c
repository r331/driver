/* ported67.c — miscellaneous front-end and effect helpers (English overview; original notes follow).
   A 30-entry pool table, centred text placement, a particle/object step, the GT / REFLEC logo and
   named icons, and three menu screens.  All cdecl (Ghidra's __fastcall/__thiscall labels on 00415ec0
   and 00415188 are wrong — ecx is never read).  Native only (the hook build keeps the originals). */
#include "ported67.h"
#include <string.h>
#include "memrw.h"

#ifndef RE_HOOK_BUILD
#pragma push_macro("P67_Items") /*gvi*/
#undef P67_Items /*gvi*/
P67_EntArr P67_Ents; P67_ItemArr P67_Items;
#pragma pop_macro("P67_Items") /*gvi*/
#pragma push_macro("P67_ItemCnt") /*gvi*/
#undef P67_ItemCnt /*gvi*/
#pragma push_macro("P67_Cur") /*gvi*/
#undef P67_Cur /*gvi*/
#pragma push_macro("P67_Sel2C") /*gvi*/
#undef P67_Sel2C /*gvi*/
#pragma push_macro("P67_Res51C") /*gvi*/
#undef P67_Res51C /*gvi*/
#pragma push_macro("P67_Tbl100") /*gvi*/
#undef P67_Tbl100 /*gvi*/
int32_t P67_ItemCnt = 0, P67_Cur = 0, P67_Sel2C = 0, P67_Res51C = 0; uint32_t P67_Tbl100 = 0;
#pragma pop_macro("P67_Tbl100") /*gvi*/
#pragma pop_macro("P67_Res51C") /*gvi*/
#pragma pop_macro("P67_Sel2C") /*gvi*/
#pragma pop_macro("P67_Cur") /*gvi*/
#pragma pop_macro("P67_ItemCnt") /*gvi*/
#endif

/* 004bb060 */
/* P67_CompactPool — Game.exe 004bb060.  Hands pooled values to free entries: every unused entry of P67_Ents
   (of 30) takes the last value of P67_Items while any are left, and is stamped with frame P67_Cur - 1.
   Then clears the pool and all "used" flags. */
void P67_CompactPool(void) {
  for (int32_t i = 0; i < 0x1e && P67_ItemCnt != 0; i++) {
    if (P67_Ents[i].used == 0) {
      P67_ItemCnt--;
      P67_Ents[i].item = P67_Items[P67_ItemCnt];
      P67_Ents[i].a = (int16_t)(P67_Cur - 1);
    }
  }
  for (int32_t i = 0; i < 0x1e; i++) { P67_Items[i] = 0; P67_Ents[i].used = 0; }
  P67_ItemCnt = 0;
}

/* F2I — local helper: the bit pattern of a float as int32 (floats are passed through int32 menu slots). */

/* 00516fbe: каждый промежуточный результат x87 записывался в float — повторяем volatile-промежуточными */
/* P67_CenterDraw — Game.exe 00516fbe.  Scales a menu position about the screen centre by P19_Scale and
   draws item p4 there (0040abac) in colour 00b5a834..36.
   The original stores every x87 intermediate to a float; the volatile temporaries reproduce that rounding.
   TODO(RE): unsure — x is centred with ScrH/2 while the value passed next to it is ScrW/2, as in Game.exe. */
void P67_CenterDraw(float x, float y, float z, uint32_t p4) {
  volatile float halfH = (float)(P19_ScrH >> 1);
  volatile float t = x - halfH;
  t = t * P19_Scale;
  volatile float halfH2 = (float)(P19_ScrH >> 1);
  t = t + halfH2;
  GlobalSet0040B0A4();
  MenuSetPos(f2i(y * P19_Scale), f2i(z * P19_Scale));
  MenuSetColor(S_00B5A834, S_00B5A835, S_00B5A836);
  volatile float halfW = (float)(P19_ScrW >> 1);
  MenuSetVals5D77C0(f2i(halfW), f2i(t), 0, 5);
  P67_Fn40ABAC(p4);
}

/* 00513fbc */
/* P67_ObjStep — Game.exe 00513fbc.  One step of a particle/animated object: runs the motion test
   (00514c9f(obj, 5, 0)); on a hit (1) handles it (0051500c) and, if flag 0x10 is set and field +0x38
   changed, restores the high half of +0x5c into +0x5e and re-arms (00514165).  Without a hit, re-arms
   unless one of flags 0x80 / 0x400 / 8 is set.  TODO(RE): unsure what fields +0x38 / +0x5c and the flags mean. */
void P67_ObjStep(void *obj) {
  uint8_t *o = (uint8_t *)obj;
  int32_t f38_old; uint32_t f5c; uint16_t f5c_hi;
  memcpy(&f38_old, o + 0x38, 4);
  memcpy(&f5c, o + 0x5c, 4);
  f5c_hi = (uint16_t)(f5c >> 16);
  int32_t hit = P67_Fn514C9F(obj, 5, 0);
  uint32_t flags; memcpy(&flags, o + 0xc, 4);
  if (hit == 1) {
    P67_Fn51500C(obj);
    memcpy(&flags, o + 0xc, 4);
    int32_t f38_new; memcpy(&f38_new, o + 0x38, 4);
    if ((flags & 0x10) != 0 && f38_new != f38_old) {
      memcpy(o + 0x5e, &f5c_hi, 2);
      P67_Fn514165(obj);
    }
  } else if ((flags & 0x80) == 0 && (flags & 0x400) == 0 && (flags & 8) == 0) {
    P67_Fn514165(obj);
  }
}

/* 004a9e88 / 0040cfdf */
/* IconSize — local helper: icon width/height from bytes 0xb/0xc of an icon record (0 means 256). */
static void IconSize(const uint8_t *ic, uint32_t *w, uint32_t *h) {
  *w = ic[0xb] == 0 ? 0x100u : ic[0xb];
  *h = ic[0xc] == 0 ? 0x100u : ic[0xc];
}
/* P67_Logo — Game.exe 004a9e88.  Draws the "GT" (which == 1) or "REFLEC" logo centred on x = 480
   (0x1e0 - w/2) at row y; skipped when y + 0x40 <= 0x5f (off the top). */
void P67_Logo(int32_t which, int32_t y) {
  if (!(y + 0x40 > 0x5f)) return;
  const uint8_t *ic = P56_FindIcon(which == 1 ? "GT" : "REFLEC");
  if (ic == NULL) return;
  uint32_t w, h; IconSize(ic, &w, &h);
  P58_Fn4AA4EA((int32_t)(0x1e0u - w / 2), y, (int32_t)w, (int32_t)h, (void *)ic, -1);
}
/* P67_DrawIcon — Game.exe 0040cfdf.  Draws icon `name` at (x, y) as a colour-keyed sprite
   (source position from bytes 8..10 of the icon record).  The third argument is unused. */
void P67_DrawIcon(int32_t x, int32_t y, int32_t unused, const char *name) {
  (void)unused;
  const uint8_t *ic = P56_FindIcon(name);
  if (ic == NULL) return;
  uint32_t w, h; IconSize(ic, &w, &h);
  P65_SpriteKeyed(x, y, ic[8], ic[9], ic[10], (int32_t)w, (int32_t)h);
}

/* 00415ec0 */
/* P67_Menu415EC0 — Game.exe 00415ec0.  Runs a menu screen (tables 0054e0b0 / P67_Tbl100) until a choice
   is made.  Returns the choice; -1 (cancel) closes the menu and returns 0. */
int32_t P67_Menu415EC0(void) {
  int32_t res;
  P19_Sel = 0;
  P57_MenuInit(0x0054e0b0, P19_Sel);
  P58_PrepPage();
  P57_MenuInit(P67_Tbl100, P19_Sel);
  Call0040CCB4(0x0054df98, 0x0054dfc0);
  for (;;) {
    Call00522323();
    Call004E3391();
    res = P57_MenuStep(P67_Tbl100, &P19_Sel);
    if (res != 0) break;
    Call0040CB9F();
  }
  MenuMode1271060 = 0;
  P12_00bdfa40 = 0;
  if (res == -1) { P57_MenuDone(); res = 0; }
  return res;
}

/* 00417970 */
/* P67_Menu417970 — Game.exe 00417970.  Runs the menu screen with table 0054e480 until UiVar0054E4B0 is set
   (-1 from the step = cancel -> 0).  On a non-zero result sets P67_Res51C = -1 and runs 00418433.
   Returns UiVar0054E4B0. */
int32_t P67_Menu417970(void) {
  GlobalSet00417A2E();
  P67_Sel2C = 0;
  S_005FEA30 = 1;
  UiVar0054E4B0 = -1;
  P58_Fn4185D2(0x0054e480, 0, 0x0054e440);
  while (UiVar0054E4B0 == -1) {
    Call00522323();
    Call004E3391();
    P67_Sel2C = P58_Fn418675(0x0054e480, P67_Sel2C);
    if (P67_Sel2C == -1) { UiVar0054E4B0 = 0; break; }
    SetColorRed00417A55();
    Call0041846C(0x0054e440, 0);
  }
  if (UiVar0054E4B0 != 0) {
    P67_Res51C = -1;
    P12_Fn00418433(0x0054e440, 0);
  }
  return UiVar0054E4B0;
}

/* 00415188: режим звука 1→2, 2→0, иначе →1; перезапуск звука, затем поток TITLE.DSS или MOTEL.DSS */
/* P67_Menu415188 — Game.exe 00415188.  Cycles the sound mode 00b87e5c 1 -> 2 -> 0 -> 1, restarts the
   sound system with it and resumes the front-end stream: TITLE.DSS, or MOTEL.DSS in the motel (00b87eec).
   Returns 0. */
int32_t P67_Menu415188(void) {
  P48_ResetAll();
  if (P12_00b87e5c == 1) P12_00b87e5c = 2;
  else if (P12_00b87e5c == 2) P12_00b87e5c = 0;
  else P12_00b87e5c = 1;
  P48_SndShutdown();
  Call005233BE(P12_00b87e58, P12_00b87e5c, P12_00575f50);
  if (G6_00B87EEC == 0) { P67_Stream("TITLE.DSS", 0); Call0052360D(0); }
  else { P67_Stream("MOTEL.DSS", 0); Call0052360D(5); }
  Call00414D1F();
  return 0;
}
