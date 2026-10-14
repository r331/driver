/* Driver PC (1999) — модуль general, псевдо-C из Ghidra. 1 функций */

// 004d9951

void FUN_004d9951(void)

{
  int iVar1;
  undefined1 local_28 [32];
  int local_8;
  
  if (DAT_005604b4 == -1) {
    DAT_005604b4 = 1;
    while( true ) {
      FUN_0052a910(local_28,s_PIC___04d_BMP_0056083c,DAT_005604b4);
      iVar1 = FUN_0052adb0(local_28,&DAT_0056084c);
      if (iVar1 == 0) break;
      FUN_0052aa10(iVar1);
      DAT_005604b4 = DAT_005604b4 + 1;
    }
  }
  DAT_0056047e = (undefined1)DAT_01270c28;
  DAT_0056047f = (undefined1)((uint)DAT_01270c28 >> 8);
  DAT_00560482 = (undefined1)DAT_0125f3f0;
  DAT_00560483 = (undefined1)((uint)DAT_0125f3f0 >> 8);
  FUN_0052a910(local_28,s_PIC___04d_BMP_00560850,DAT_005604b4);
  iVar1 = FUN_0052adb0(local_28,&DAT_00560860);
  if (iVar1 != 0) {
    local_8 = thunk_FUN_004d8db4(DAT_01270c28 * DAT_0125f3f0 * 3,s_D__Driver_Game_general_c_00560864
                                 ,0x75b);
    if (local_8 != 0) {
      thunk_FUN_004d9ad4(local_8);
      FUN_0052ae80(&DAT_0056046c,1,0x36,iVar1);
      FUN_0052ae80(local_8,3,DAT_01270c28 * DAT_0125f3f0,iVar1);
      thunk_FUN_004d8f30(local_8);
      local_8 = 0;
    }
    FUN_0052aa10(iVar1);
    DAT_005604b4 = DAT_005604b4 + 1;
  }
  return;
}


