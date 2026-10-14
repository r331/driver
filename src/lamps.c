/* Driver PC (1999) — модуль lamps, псевдо-C из Ghidra. 1 функций */

// 004eafe0

undefined4 FUN_004eafe0(undefined4 param_1)

{
  undefined4 uVar1;
  int local_18;
  int local_14;
  int local_10;
  undefined4 local_c;
  int local_8;
  
  local_c = FUN_0052b260(param_1);
  FUN_0052aaf0(&DAT_00d02300,0x14,1,param_1);
  if ((((DAT_00d02300 == 'G') && (DAT_00d02301 == 'L')) && (DAT_00d02302 == 'M')) &&
     (DAT_00d02303 == 'P')) {
    if (DAT_00b31ec4 != (void *)0x0) {
      thunk_FUN_004eb19b();
    }
    DAT_00b31ebc = DAT_00d02308 * DAT_00d0230c;
    DAT_00b31ec4 = (void *)thunk_FUN_004d8db4(DAT_00b31ebc * 8,s_D__Driver_Game_lamps_c_00562d00,
                                              0x102);
    if (DAT_00b31ec4 == (void *)0x0) {
      uVar1 = 0;
    }
    else {
      _memset(DAT_00b31ec4,0,DAT_00b31ebc << 3);
      local_8 = DAT_00d02310;
      while (local_8 != 0) {
        local_8 = local_8 + -1;
        FUN_0052aaf0(&local_18,8,1,param_1);
        local_10 = local_18;
        *(int *)((int)DAT_00b31ec4 + local_18 * 8) = local_14;
        if (local_14 == 0) {
          *(undefined4 *)((int)DAT_00b31ec4 + local_18 * 8 + 4) = 0;
        }
        else {
          uVar1 = thunk_FUN_004d8db4(*(int *)((int)DAT_00b31ec4 + local_18 * 8) * 0x28,
                                     s_D__Driver_Game_lamps_c_00562d18,0x114);
          *(undefined4 *)((int)DAT_00b31ec4 + local_10 * 8 + 4) = uVar1;
          if (*(int *)((int)DAT_00b31ec4 + local_10 * 8 + 4) == 0) {
            thunk_FUN_004eb19b();
            return 0;
          }
          FUN_0052aaf0(*(undefined4 *)((int)DAT_00b31ec4 + local_10 * 8 + 4),0x28,
                       *(undefined4 *)((int)DAT_00b31ec4 + local_10 * 8),param_1);
        }
      }
      uVar1 = 1;
    }
  }
  else {
    FUN_0052b4f0(param_1,local_c,0);
    uVar1 = 0;
  }
  return uVar1;
}


