/* Driver PC (1999) — модуль roadbits, псевдо-C из Ghidra. 1 функций */

// 0051aa5b

void FUN_0051aa5b(void)

{
  undefined4 uVar1;
  int local_8;
  
  for (local_8 = 0; local_8 < 4; local_8 = local_8 + 1) {
    *(undefined4 *)(&DAT_00c39da0 + local_8 * 4) = 0xffffffff;
    uVar1 = thunk_FUN_004d8db4(0x7080,s_D__Driver_Game_roadbits_c_00575e40,0xc9);
    *(undefined4 *)(&DAT_00c4bdd0 + local_8 * 4) = uVar1;
    uVar1 = thunk_FUN_004d8db4(0xe100,s_D__Driver_Game_roadbits_c_00575e5c,0xca);
    *(undefined4 *)(&DAT_00c1cc80 + local_8 * 4) = uVar1;
  }
  return;
}


