#include "ported19.h"
#include "unported.h"
#include <string.h>
#ifndef RE_HOOK_BUILD
uint8_t P19_Keys1[16], P19_Keys2[16];
#endif
GAME_VAR_DEF(float, P19_Cur, 0x005fea58)
GAME_VAR_DEF(float, P19_Target, 0x005fea5c)
GAME_VAR_DEF(int32_t, P19_Active, 0x005fea60)
GAME_VAR_DEF(float, P19_Out68, 0x01251a68)
GAME_VAR_DEF(float, P19_OutA, 0x005507d0)
GAME_VAR_DEF(float, P19_OutB, 0x005507d4)
GAME_VAR_DEF(float, P19_OutC, 0x005507d8)
GAME_VAR_DEF(float, P19_Step, 0x00546070)
GAME_VAR_DEF(int32_t, P19_ScrW, 0x01270c28)
GAME_VAR_DEF(int32_t, P19_ScrH, 0x0125f3f0)
GAME_VAR_DEF(float, P19_Scale, 0x0125f3e0)
GAME_VAR_DEF(float, P19_DivW, 0x00546060)
GAME_VAR_DEF(float, P19_DivH, 0x0054605c)
GAME_VAR_DEF(float, P19_DivC, 0x00546050)
GAME_VAR_DEF(int32_t, P19_Level, 0x00575ef0)
GAME_VAR_DEF(int32_t, P19_Sel, 0x005fe9e0)
GAME_VAR_DEF(uint32_t, P19_PtrA, 0x0054df9c)
GAME_VAR_DEF(uint16_t, P19_Wd, 0x0054df98)
GAME_VAR_DEF(uint16_t, P19_Ht, 0x0054df9a)
GAME_VAR_DEF(int32_t, P19_F1, 0x0054dfe4)
GAME_VAR_DEF(int32_t, P19_F2, 0x0054dff4)
GAME_VAR_DEF(int32_t, P19_F3, 0x0054e004)
GAME_VAR_DEF(int32_t, P19_Cond, 0x00b87e38)

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

int32_t P19_KeysUnique14(void) {
  for (int i = 0; i < 14; i++)
    for (int j = i + 1; j < 14; j++)
      if (P19_Keys2[i] == P19_Keys2[j]) return 0;
  return 1;
}

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

float P19_ScaleX(float v) {
  return (v * ((float)P19_ScrW / P19_DivW) - (float)P19_ScrW / P19_DivC) * P19_Scale + (float)P19_ScrW / P19_DivC;
}
float P19_ScaleY(float v) {
  return (v * ((float)P19_ScrH / P19_DivH) - (float)P19_ScrH / P19_DivC) * P19_Scale + (float)P19_ScrH / P19_DivC;
}
