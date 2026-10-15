#include "ported67.h"
#include <string.h>

#ifndef RE_HOOK_BUILD
P67_EntArr P67_Ents; P67_ItemArr P67_Items;
int32_t P67_ItemCnt = 0, P67_Cur = 0, P67_Sel2C = 0, P67_Res51C = 0; uint32_t P67_Tbl100 = 0;
#endif

/* 004bb060 */
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

static int32_t F2I(float f) { int32_t v; memcpy(&v, &f, 4); return v; }

/* 00516fbe: каждый промежуточный результат x87 записывался в float — повторяем volatile-промежуточными */
void P67_CenterDraw(float x, float y, float z, uint32_t p4) {
  volatile float halfH = (float)(P19_ScrH >> 1);
  volatile float t = x - halfH;
  t = t * P19_Scale;
  volatile float halfH2 = (float)(P19_ScrH >> 1);
  t = t + halfH2;
  GlobalSet0040B0A4();
  MenuSetPos(F2I(y * P19_Scale), F2I(z * P19_Scale));
  MenuSetColor(S_00B5A834, S_00B5A835, S_00B5A836);
  volatile float halfW = (float)(P19_ScrW >> 1);
  MenuSetVals5D77C0(F2I(halfW), F2I(t), 0, 5);
  P67_Fn40ABAC(p4);
}

/* 00513fbc */
void P67_ObjStep(void *obj) {
  uint8_t *o = (uint8_t *)obj;
  int32_t f38_old; uint32_t c; uint16_t hi;
  memcpy(&f38_old, o + 0x38, 4);
  memcpy(&c, o + 0x5c, 4);
  hi = (uint16_t)(c >> 16);
  int32_t r = P67_Fn514C9F(obj, 5, 0);
  uint32_t flags; memcpy(&flags, o + 0xc, 4);
  if (r == 1) {
    P67_Fn51500C(obj);
    memcpy(&flags, o + 0xc, 4);
    int32_t f38_new; memcpy(&f38_new, o + 0x38, 4);
    if ((flags & 0x10) != 0 && f38_new != f38_old) {
      memcpy(o + 0x5e, &hi, 2);
      P67_Fn514165(obj);
    }
  } else if ((flags & 0x80) == 0 && (flags & 0x400) == 0 && (flags & 8) == 0) {
    P67_Fn514165(obj);
  }
}

/* 004a9e88 / 0040cfdf */
static void IconSize(const uint8_t *ic, uint32_t *w, uint32_t *h) {
  *w = ic[0xb] == 0 ? 0x100u : ic[0xb];
  *h = ic[0xc] == 0 ? 0x100u : ic[0xc];
}
void P67_Logo(int32_t which, int32_t y) {
  if (!(y + 0x40 > 0x5f)) return;
  const uint8_t *ic = P56_FindIcon(which == 1 ? "GT" : "REFLEC");
  if (ic == NULL) return;
  uint32_t w, h; IconSize(ic, &w, &h);
  P58_Fn4AA4EA((int32_t)(0x1e0u - w / 2), y, (int32_t)w, (int32_t)h, (void *)ic, -1);
}
void P67_DrawIcon(int32_t x, int32_t y, int32_t unused, const char *name) {
  (void)unused;
  const uint8_t *ic = P56_FindIcon(name);
  if (ic == NULL) return;
  uint32_t w, h; IconSize(ic, &w, &h);
  P65_SpriteKeyed(x, y, ic[8], ic[9], ic[10], (int32_t)w, (int32_t)h);
}

/* 00415ec0 */
int32_t P67_Menu415EC0(void) {
  int32_t r;
  P19_Sel = 0;
  P57_MenuInit(0x0054e0b0, P19_Sel);
  P58_PrepPage();
  P57_MenuInit(P67_Tbl100, P19_Sel);
  Call0040CCB4(0x0054df98, 0x0054dfc0);
  for (;;) {
    Call00522323();
    Call004E3391();
    r = P57_MenuStep(P67_Tbl100, &P19_Sel);
    if (r != 0) break;
    Call0040CB9F();
  }
  MenuMode1271060 = 0;
  P12_00bdfa40 = 0;
  if (r == -1) { P57_MenuDone(); r = 0; }
  return r;
}

/* 00417970 */
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
