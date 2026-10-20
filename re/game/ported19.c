/* ported19.c — key-binding uniqueness checks for the controls menu, the menu value fader, a word
   tokenizer, three chained menu selection handlers gated by progress, and the 640x480 -> screen
   coordinate scale used by menu drawing. */
#include "ported19.h"
#include "unported.h"
#include <string.h>
#ifndef RE_HOOK_BUILD
uint8_t P19_Keys1[16], P19_Keys2[16];
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P19_Cur")
#undef P19_Cur
#pragma push_macro("P19_Cur") /*gvi*/
#undef P19_Cur /*gvi*/
float P19_Cur;
#pragma pop_macro("P19_Cur") /*gvi*/
#pragma pop_macro("P19_Cur")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P19_Target")
#undef P19_Target
#pragma push_macro("P19_Target") /*gvi*/
#undef P19_Target /*gvi*/
float P19_Target;
#pragma pop_macro("P19_Target") /*gvi*/
#pragma pop_macro("P19_Target")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P19_Active")
#undef P19_Active
#pragma push_macro("P19_Active") /*gvi*/
#undef P19_Active /*gvi*/
int32_t P19_Active;
#pragma pop_macro("P19_Active") /*gvi*/
#pragma pop_macro("P19_Active")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P19_Out68")
#undef P19_Out68
#pragma push_macro("P19_Out68") /*gvi*/
#undef P19_Out68 /*gvi*/
float P19_Out68;
#pragma pop_macro("P19_Out68") /*gvi*/
#pragma pop_macro("P19_Out68")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P19_OutA")
#undef P19_OutA
#pragma push_macro("P19_OutA") /*gvi*/
#undef P19_OutA /*gvi*/
float P19_OutA;
#pragma pop_macro("P19_OutA") /*gvi*/
#pragma pop_macro("P19_OutA")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P19_OutB")
#undef P19_OutB
#pragma push_macro("P19_OutB") /*gvi*/
#undef P19_OutB /*gvi*/
float P19_OutB;
#pragma pop_macro("P19_OutB") /*gvi*/
#pragma pop_macro("P19_OutB")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P19_OutC")
#undef P19_OutC
#pragma push_macro("P19_OutC") /*gvi*/
#undef P19_OutC /*gvi*/
float P19_OutC;
#pragma pop_macro("P19_OutC") /*gvi*/
#pragma pop_macro("P19_OutC")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P19_Step")
#undef P19_Step
#pragma push_macro("P19_Step") /*gvi*/
#undef P19_Step /*gvi*/
float P19_Step;
#pragma pop_macro("P19_Step") /*gvi*/
#pragma pop_macro("P19_Step")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P19_ScrW")
#undef P19_ScrW
#pragma push_macro("P19_ScrW") /*gvi*/
#undef P19_ScrW /*gvi*/
int32_t P19_ScrW;
#pragma pop_macro("P19_ScrW") /*gvi*/
#pragma pop_macro("P19_ScrW")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P19_ScrH")
#undef P19_ScrH
#pragma push_macro("P19_ScrH") /*gvi*/
#undef P19_ScrH /*gvi*/
int32_t P19_ScrH;
#pragma pop_macro("P19_ScrH") /*gvi*/
#pragma pop_macro("P19_ScrH")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P19_Scale")
#undef P19_Scale
#pragma push_macro("P19_Scale") /*gvi*/
#undef P19_Scale /*gvi*/
float P19_Scale;
#pragma pop_macro("P19_Scale") /*gvi*/
#pragma pop_macro("P19_Scale")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P19_DivW")
#undef P19_DivW
#pragma push_macro("P19_DivW") /*gvi*/
#undef P19_DivW /*gvi*/
float P19_DivW;
#pragma pop_macro("P19_DivW") /*gvi*/
#pragma pop_macro("P19_DivW")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P19_DivH")
#undef P19_DivH
#pragma push_macro("P19_DivH") /*gvi*/
#undef P19_DivH /*gvi*/
float P19_DivH;
#pragma pop_macro("P19_DivH") /*gvi*/
#pragma pop_macro("P19_DivH")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P19_DivC")
#undef P19_DivC
#pragma push_macro("P19_DivC") /*gvi*/
#undef P19_DivC /*gvi*/
float P19_DivC;
#pragma pop_macro("P19_DivC") /*gvi*/
#pragma pop_macro("P19_DivC")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P19_Level")
#undef P19_Level
#pragma push_macro("P19_Level") /*gvi*/
#undef P19_Level /*gvi*/
int32_t P19_Level;
#pragma pop_macro("P19_Level") /*gvi*/
#pragma pop_macro("P19_Level")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P19_Sel")
#undef P19_Sel
#pragma push_macro("P19_Sel") /*gvi*/
#undef P19_Sel /*gvi*/
int32_t P19_Sel;
#pragma pop_macro("P19_Sel") /*gvi*/
#pragma pop_macro("P19_Sel")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P19_PtrA")
#undef P19_PtrA
#pragma push_macro("P19_PtrA") /*gvi*/
#undef P19_PtrA /*gvi*/
uint32_t P19_PtrA;
#pragma pop_macro("P19_PtrA") /*gvi*/
#pragma pop_macro("P19_PtrA")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P19_Wd")
#undef P19_Wd
#pragma push_macro("P19_Wd") /*gvi*/
#undef P19_Wd /*gvi*/
uint16_t P19_Wd;
#pragma pop_macro("P19_Wd") /*gvi*/
#pragma pop_macro("P19_Wd")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P19_Ht")
#undef P19_Ht
#pragma push_macro("P19_Ht") /*gvi*/
#undef P19_Ht /*gvi*/
uint16_t P19_Ht;
#pragma pop_macro("P19_Ht") /*gvi*/
#pragma pop_macro("P19_Ht")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P19_F1")
#undef P19_F1
#pragma push_macro("P19_F1") /*gvi*/
#undef P19_F1 /*gvi*/
int32_t P19_F1;
#pragma pop_macro("P19_F1") /*gvi*/
#pragma pop_macro("P19_F1")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P19_F2")
#undef P19_F2
#pragma push_macro("P19_F2") /*gvi*/
#undef P19_F2 /*gvi*/
int32_t P19_F2;
#pragma pop_macro("P19_F2") /*gvi*/
#pragma pop_macro("P19_F2")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P19_F3")
#undef P19_F3
#pragma push_macro("P19_F3") /*gvi*/
#undef P19_F3 /*gvi*/
int32_t P19_F3;
#pragma pop_macro("P19_F3") /*gvi*/
#pragma pop_macro("P19_F3")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P19_Cond")
#undef P19_Cond
#pragma push_macro("P19_Cond") /*gvi*/
#undef P19_Cond /*gvi*/
int32_t P19_Cond;
#pragma pop_macro("P19_Cond") /*gvi*/
#pragma pop_macro("P19_Cond")
#endif

/* P19_KeysUnique12 — Game.exe 004107b9.  Returns 1 if the 12 key bindings P19_Keys1 (read in the order
   0..4, 6, 7, 5, 8..11) are pairwise different, ignoring entries equal to 0x22; else 0.
   TODO(RE): unsure why 0x22 is exempt (DIK_G, or a "no key" marker). */
int32_t P19_KeysUnique12(void) {
  static const int idx[12] = {0,1,2,3,4,6,7,5,8,9,10,11};
  char k[12];
  for (int i = 0; i < 12; i++) k[i] = (char)P19_Keys1[idx[i]];
  for (int i = 0; i < 12; i++)
    if (k[i] != '"')
      for (int j = i + 1; j < 12; j++)
        if (k[j] != '"' && k[i] == k[j]) return 0;
  return 1;
}

/* P19_KeysUnique14 — Game.exe 00411b09.  Returns 1 if the 14 bytes of P19_Keys2 (0054b7c4) are pairwise
   different (no exemption), else 0. */
int32_t P19_KeysUnique14(void) {
  for (int i = 0; i < 14; i++)
    for (int j = i + 1; j < 14; j++)
      if (P19_Keys2[i] == P19_Keys2[j]) return 0;
  return 1;
}

/* P19_FadeStep — Game.exe 004184f5.  While P19_Active, moves P19_Cur toward P19_Target by P19_Step
   (stopping exactly at the target and clearing P19_Active), then copies P19_Cur to four outputs
   (01251a68, 005507d0/d4/d8).  TODO(RE): unsure what the four outputs are (fade colour components?). */
void P19_FadeStep(void) {
  if (P19_Active == 0) return;
  if (P19_Target <= P19_Cur) {
    if (P19_Target < P19_Cur) {
      P19_Cur = P19_Cur - P19_Step;
      if (P19_Cur <= P19_Target) { P19_Cur = P19_Target; P19_Active = 0; }
    }
  } else {
    P19_Cur = P19_Cur + P19_Step;
    if (P19_Target <= P19_Cur) { P19_Cur = P19_Target; P19_Active = 0; }
  }
  P19_Out68 = P19_Cur; P19_OutA = P19_Cur; P19_OutB = P19_Cur; P19_OutC = P19_Cur;
}

/* P19_TakeToken — Game.exe 0041c7da.  Cuts the first word off s: skips leading spaces, copies characters
   up to the next space or '\n' into out (NUL-terminated), and shifts the rest of s (after that one
   delimiter) to the front of s.  Returns 1 if the word is empty, else 0.  No bound on out. */
int P19_TakeToken(char* s, char* out) {
  int n = 0, pos = 0;
  size_t left = strlen(s);
  while (left != 0) {
    char c = s[pos++];
    left--;
    if (c != ' ' || n != 0) {
      if (c == ' ' || c == '\n') break;
      out[n++] = c;
    }
  }
  out[n] = 0;
  int w = 0;
  for (; s[pos] != 0; pos++) s[w++] = s[pos];
  s[w] = 0;
  return n == 0;
}

/* P19_Sel2 / P19_Sel3 / P19_Sel4 — Game.exe 00416084 / 004160e9 / 0041614e.  Menu entry k (2..4) handler,
   gated by the progress value P19_Level: if P19_Level < k the selection falls back to entry k-1
   (P19_Sel = k-2, then entry k-1's handler; entry 1 is Fn00416040).  Otherwise it sets the hint text
   address and size (P19_PtrA / P19_Wd / P19_Ht), the entry's enable flag P19_Fk and the id written to
   P19_Cond (00b87e38): 0x2f / 0x30 / 0x31.  TODO(RE): unsure — which menu (city or mission select)
   and what the 00b87e38 ids name. */
void P19_Sel2(int32_t a) {
  if (P19_Level < 2) { P19_Sel = 0; Fn00416040(a); }
  else { P19_PtrA = 0x54e10c; P19_Wd = 0x148; P19_Ht = 0xa6; P19_F1 = 1; P19_Cond = 0x2f; }
}
void P19_Sel3(int32_t a) {
  if (P19_Level < 3) { P19_Sel = 1; P19_Sel2(a); }
  else { P19_PtrA = 0x54e110; P19_Wd = 0x14a; P19_Ht = 0xc0; P19_F2 = 1; P19_Cond = 0x30; }
}
void P19_Sel4(int32_t a) {
  if (P19_Level < 4) { P19_Sel = 2; P19_Sel3(a); }
  else { P19_PtrA = 0x54e114; P19_Wd = 0x147; P19_Ht = 0x9a; P19_F3 = 1; P19_Cond = 0x31; }
}

/* P19_ScaleX — Game.exe 005174c6.  Design x (640-wide) -> screen x, zoomed by P19_Scale about the screen
   centre: (v * ScrW / DivW - ScrW / DivC) * Scale + ScrW / DivC, with DivW = 640, DivC = 2 read from
   .rdata (00546060 / 00546050; values per ported73.c's P73_Text, which inlines the same formula). */
float P19_ScaleX(float v) {
  return (v * ((float)P19_ScrW / P19_DivW) - (float)P19_ScrW / P19_DivC) * P19_Scale + (float)P19_ScrW / P19_DivC;
}
/* P19_ScaleY — Game.exe 00517512.  Same as P19_ScaleX for y (DivH = 480 at 0054605c). */
float P19_ScaleY(float v) {
  return (v * ((float)P19_ScrH / P19_DivH) - (float)P19_ScrH / P19_DivC) * P19_Scale + (float)P19_ScrH / P19_DivC;
}
