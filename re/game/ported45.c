/* Меню и ожидание — восстановлено из Game.exe (cdecl). */
#include "ported45.h"
GAME_VAR_DEF(int32_t, P45_Mode, 0x00b87e38)
GAME_VAR_DEF(uint32_t, P45_PtrB, 0x005f7e64)
GAME_VAR_DEF(uint32_t, P45_PtrA, 0x005f7e40)
GAME_VAR_DEF(int32_t, P45_Busy, 0x005f7e44)
GAME_VAR_DEF(int32_t, P45_Step, 0x005f7e48)
GAME_VAR_DEF(int32_t, P45_Pick, 0x005fed9c)
GAME_VAR_DEF(uint32_t, P45_Color, 0x0054e4d8)
GAME_VAR_DEF(uint32_t, P45_Col0, 0x00c55a6c)
GAME_VAR_DEF(uint32_t, P45_Col1, 0x00c55a5c)
GAME_VAR_DEF(uint32_t, P45_Col2, 0x00c55a60)
GAME_VAR_DEF(uint32_t, P45_Col3, 0x00c55a64)
GAME_VAR_DEF(uint32_t, P45_Col4, 0x00c55a68)

int32_t P45_ModeA(void) {
  switch (P45_Mode) {
    case 0x2e: case 0x92: P45_Mode = 0x2e; break;
    case 0x2f: case 0x93: P45_Mode = 0x2f; break;
    case 0x30: case 0x94: P45_Mode = 0x30; break;
    case 0x31: case 0x95: P45_Mode = 0x31; break;
    default: break;
  }
  MenuAction40CD17();
  Call3_0040C455(1, 0);
  return 1;
}
int32_t P45_ModeB(void) {
  switch (P45_Mode) {
    case 0x2e: case 0x92: P45_Mode = 0x92; break;
    case 0x2f: case 0x93: P45_Mode = 0x93; break;
    case 0x30: case 0x94: P45_Mode = 0x94; break;
    case 0x31: case 0x95: P45_Mode = 0x95; break;
    default: break;
  }
  MenuAction40CD17();
  Call3_0040C455(1, 0);
  return 1;
}
void P45_Wait(uint32_t a, uint32_t b) {
  P45_PtrB = a;
  P45_PtrA = b;
  P45_Busy = 1;
  for (int32_t i = 5; i > -1; i--) {
    Call00522323();
    P36_PollInput();
    P45_Step = i;
    Call0040CB9F();
  }
  P45_Busy = 0;
  StartTimer004086B4();
}
void P45_PickColor(void) {
  switch (P45_Pick) {
    case 0: P45_Color = P45_Col0; break;
    case 1: P45_Color = P45_Col1; break;
    case 2: P45_Color = P45_Col2; break;
    case 3: P45_Color = P45_Col3; break;
    case 4: P45_Color = P45_Col4; break;
    default: break;
  }
  SetRGB00516EB4(0, 0, 0);
  SetFade0051707A(0xff, 0xff, 0x80, 0x32);
}
