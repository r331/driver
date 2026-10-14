/* Driver PC (1999) — модуль frontend/config, псевдо-C из Ghidra. 2 функций */

// 00406272

undefined4 FUN_00406272(undefined4 param_1,undefined4 param_2)

{
  int iVar1;
  undefined4 local_c;
  int local_8;
  
  local_8 = FUN_0052adb0(param_2,&DAT_00549e70);
  if (local_8 != 0) {
    FUN_0052b4f0(local_8,0,2);
    local_c = FUN_0052b260(local_8);
    FUN_0052b4f0(local_8,0,0);
    iVar1 = thunk_FUN_004d8db4(local_c,s_D__Driver_Game_frontend_config_c_00549e74,0x237);
    if (iVar1 != 0) {
      FUN_0052aaf0(iVar1,1,local_c,local_8);
      FUN_0052aa10(local_8);
      FUN_0052ae80(&stack0x0000000c,1,4,param_1);
      FUN_0052ae80(&local_c,1,4,param_1);
      FUN_0052ae80(iVar1,1,local_c,param_1);
      thunk_FUN_004d8f30(iVar1);
      return 1;
    }
    FUN_0052aa10(local_8);
  }
  return 0;
}


// 00406369

undefined4 FUN_00406369(undefined4 param_1,undefined4 param_2,int param_3)

{
  int local_14;
  undefined4 local_10;
  int local_c;
  int local_8;
  
  FUN_0052aaf0(&local_14,1,4,param_1);
  if (param_3 == local_14) {
    FUN_0052aaf0(&local_10,1,4,param_1);
    local_c = thunk_FUN_004d8db4(local_10,s_D__Driver_Game_frontend_config_c_00549e98,0x254);
    if (local_c != 0) {
      FUN_0052aaf0(local_c,1,local_10,param_1);
      local_8 = FUN_0052adb0(param_2,&DAT_00549ebc);
      if (local_8 != 0) {
        FUN_0052ae80(local_c,1,local_10,local_8);
        FUN_0052aa10(local_8);
        thunk_FUN_004d8f30(local_c);
        return 1;
      }
      thunk_FUN_004d8f30(local_c);
    }
  }
  return 0;
}


