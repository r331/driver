/* Driver PC (1999) — модуль file, псевдо-C из Ghidra. 2 функций */

// 004d30f8

int FUN_004d30f8(undefined4 param_1)

{
  char cVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  
  iVar2 = FUN_0052adb0(param_1,&DAT_0055ffd8);
  if (iVar2 != 0) {
    iVar3 = thunk_FUN_004d3000(iVar2);
    if (((iVar3 != 0) &&
        (iVar4 = thunk_FUN_004d8db4(iVar3,s_D__Driver_Game_file_c_0055ffdc,0x86), iVar4 != 0)) &&
       (cVar1 = thunk_FUN_004d9596(iVar4,iVar3,1,iVar2), cVar1 != '\0')) {
      FUN_0052aa10(iVar2);
      return iVar4;
    }
    FUN_0052aa10(iVar2);
  }
  return 0;
}


// 004d318e

int FUN_004d318e(undefined4 param_1,int *param_2)

{
  char cVar1;
  int iVar2;
  int iVar3;
  
  iVar2 = FUN_0052adb0(param_1,&DAT_0055fff4);
  if (iVar2 != 0) {
    iVar3 = thunk_FUN_004d3000(iVar2);
    *param_2 = iVar3;
    if (((*param_2 != 0) &&
        (iVar3 = thunk_FUN_004d8db4(*param_2,s_D__Driver_Game_file_c_0055fff8,0xb1), iVar3 != 0)) &&
       (cVar1 = thunk_FUN_004d9596(iVar3,*param_2,1,iVar2), cVar1 != '\0')) {
      FUN_0052aa10(iVar2);
      return iVar3;
    }
    FUN_0052aa10(iVar2);
  }
  return 0;
}


