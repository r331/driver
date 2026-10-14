/* Driver PC (1999) — модуль Director, псевдо-C из Ghidra. 4 функций */

// 004c6264

undefined4 AddDirectorCamera(int param_1,int param_2)

{
  int iVar1;
  undefined4 uVar2;
  int local_c;
  
  iVar1 = thunk_FUN_004c6168(param_2);
  if (iVar1 != 0) {
    DeleteCamera(*(undefined4 *)(iVar1 + 4));
  }
  *(int *)(param_1 + 0x14) = param_2;
  local_c = 0;
  while( true ) {
    if (DAT_00d17b60 <= local_c) {
      uVar2 = InsertCamera(param_1,0xffffffff);
      return uVar2;
    }
    if (param_2 == *(int *)(*(int *)(DAT_00d17c54 + local_c * 4) + 0x14)) break;
    if (param_2 < *(int *)(*(int *)(DAT_00d17c54 + local_c * 4) + 0x14)) {
      uVar2 = InsertCamera(param_1,local_c);
      return uVar2;
    }
    local_c = local_c + 1;
  }
  thunk_FUN_004bf2a0(s_Director_c__AddDirectorCamera__C_0055ec9c);
  return 0;
}


// 004c6312

undefined4 InsertCamera(undefined4 *param_1,int param_2)

{
  int iVar1;
  undefined4 uVar2;
  undefined4 *puVar3;
  int iVar4;
  int local_14;
  int local_c;
  int local_8;
  
  if (DAT_00d17b60 <= param_2) {
    param_2 = -1;
  }
  iVar1 = thunk_FUN_004d8db4(DAT_00d17b60 * 4 + 4,s_D__Driver_Game_Director_c_0055ecd4,0xa8a);
  if (iVar1 == 0) {
    thunk_FUN_004bf2a0(s_InsertCamera__Error__unable_to_a_0055ecf0);
    uVar2 = 0;
  }
  else {
    puVar3 = (undefined4 *)thunk_FUN_004d8db4(0x8c,s_D__Driver_Game_Director_c_0055ed34,0xa91);
    if (puVar3 == (undefined4 *)0x0) {
      thunk_FUN_004bf2a0(s_InsertCamera__Error__unable_to_a_0055ed50);
      thunk_FUN_004d8f30(iVar1);
      uVar2 = 0;
    }
    else {
      if (param_2 == -1) {
        for (local_8 = 0; local_8 < DAT_00d17b60; local_8 = local_8 + 1) {
          *(undefined4 *)(iVar1 + local_8 * 4) = *(undefined4 *)(DAT_00d17c54 + local_8 * 4);
        }
        *(undefined4 **)(iVar1 + DAT_00d17b60 * 4) = puVar3;
        local_14 = DAT_00d17b60;
        DAT_00d17b60 = DAT_00d17b60 + 1;
      }
      else {
        DAT_00d17b60 = DAT_00d17b60 + 1;
        local_c = 0;
        for (local_8 = 0; local_8 < DAT_00d17b60; local_8 = local_8 + 1) {
          if (local_8 == param_2) {
            *(undefined4 **)(iVar1 + local_8 * 4) = puVar3;
            local_14 = local_8;
          }
          else {
            *(undefined4 *)(iVar1 + local_8 * 4) = *(undefined4 *)(DAT_00d17c54 + local_c * 4);
            local_c = local_c + 1;
          }
        }
      }
      for (iVar4 = 0x23; iVar4 != 0; iVar4 = iVar4 + -1) {
        *puVar3 = *param_1;
        param_1 = param_1 + 1;
        puVar3 = puVar3 + 1;
      }
      if (DAT_00d17c54 != 0) {
        thunk_FUN_004d8f30(DAT_00d17c54);
      }
      DAT_00d17c54 = iVar1;
      thunk_FUN_004c622c();
      uVar2 = *(undefined4 *)(DAT_00d17c54 + local_14 * 4);
    }
  }
  return uVar2;
}


// 004c64bd

void FUN_004c64bd(void)

{
  undefined4 local_8;
  
  for (local_8 = 0; local_8 < DAT_00d17b60; local_8 = local_8 + 1) {
    thunk_FUN_004d8f30(*(undefined4 *)(DAT_00d17c54 + local_8 * 4));
  }
  if (DAT_00d17c54 != 0) {
    thunk_FUN_004d8f30(DAT_00d17c54);
  }
  DAT_00d17b60 = 0;
  DAT_00d17c54 = 0;
  return;
}


// 004c6524

void DeleteCamera(int param_1)

{
  int iVar1;
  int local_c;
  int local_8;
  
  if ((param_1 < DAT_00d17b60) && (-1 < param_1)) {
    if (DAT_00d17b60 < 2) {
      thunk_FUN_004d8f30(*(undefined4 *)(DAT_00d17c54 + param_1 * 4));
      thunk_FUN_004d8f30(DAT_00d17c54);
      DAT_00d17c50 = 0;
      DAT_00d17c54 = 0;
    }
    else {
      iVar1 = thunk_FUN_004d8db4(DAT_00d17b60 * 4 + -4,s_D__Driver_Game_Director_c_0055edc8,0xae9);
      if (iVar1 == 0) {
        thunk_FUN_004bf2a0(s_DeleteCamera__Error__Unable_to_a_0055ede4);
        return;
      }
      local_8 = 0;
      for (local_c = 0; local_c < DAT_00d17b60; local_c = local_c + 1) {
        if (local_c != param_1) {
          *(undefined4 *)(iVar1 + local_8 * 4) = *(undefined4 *)(DAT_00d17c54 + local_c * 4);
          *(int *)(*(int *)(iVar1 + local_8 * 4) + 4) = local_8;
          local_8 = local_8 + 1;
        }
      }
      if ((DAT_00d17c50 != 0) && (*(int *)(DAT_00d17c50 + 4) == param_1)) {
        DAT_00d17c50 = 0;
      }
      thunk_FUN_004d8f30(*(undefined4 *)(DAT_00d17c54 + param_1 * 4));
      thunk_FUN_004d8f30(DAT_00d17c54);
      DAT_00d17c54 = iVar1;
    }
    DAT_00d17b60 = DAT_00d17b60 + -1;
    thunk_FUN_004c622c();
  }
  else {
    thunk_FUN_004bf2a0(s_DeleteCamera__Error__Specified_c_0055ed90);
  }
  return;
}


