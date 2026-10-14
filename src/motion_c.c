/* Driver PC (1999) — модуль motion_c, псевдо-C из Ghidra. 1 функций */

// 004f388e

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 FUN_004f388e(void)

{
  undefined4 uVar1;
  float10 fVar2;
  int local_30;
  int local_2c;
  
  thunk_FUN_004bf2a0();
  DAT_00c56700 = 1;
  DAT_00cf56bc = thunk_FUN_004ec837();
  DAT_00d00214 = thunk_FUN_004ec837();
  DAT_00c97a30 = thunk_FUN_004ec837();
  if (DAT_00b87e30 < 2) {
    DAT_00ce1f40 = thunk_FUN_004ec837();
  }
  else {
    DAT_00ce1f40 = thunk_FUN_004ec837();
  }
  DAT_00d00254 = thunk_FUN_004ec837();
  DAT_00c98ec4 = thunk_FUN_004ec837();
  DAT_00cf56b4 = thunk_FUN_004ec837();
  if (DAT_00b87e30 < 2) {
    DAT_00d00210 = thunk_FUN_004ec837();
  }
  else {
    DAT_00d00210 = thunk_FUN_004ec837();
  }
  if ((((DAT_00cf56bc == -1) || (DAT_00d00214 == -1)) || (DAT_00d00254 == -1)) ||
     (DAT_00c98ec4 == -1)) {
    DAT_00c56700 = 0;
    thunk_FUN_004bf2a0();
    uVar1 = 0;
  }
  else {
    DAT_00d00254 = DAT_00d00254 - DAT_00cf56bc;
    DAT_00c98ec4 = DAT_00c98ec4 - DAT_00d00214;
    DAT_00cf56b4 = DAT_00cf56b4 - DAT_00c97a30;
    DAT_00d00210 = DAT_00d00210 - DAT_00ce1f40;
    for (local_2c = 0; local_2c < 4; local_2c = local_2c + 1) {
      *(undefined4 *)(&DAT_00c81b80 + local_2c * 4) = 0;
    }
    for (local_2c = 0; local_2c < 4; local_2c = local_2c + 1) {
      uVar1 = thunk_FUN_004d8db4(0x80002,s_D__Driver_Game_motion_c_c_00563874,0x101);
      *(undefined4 *)(&DAT_00c81b80 + local_2c * 4) = uVar1;
      if (*(int *)(&DAT_00c81b80 + local_2c * 4) == 0) {
        DAT_00c56700 = 0;
        return 0;
      }
      if ((local_2c == 0) && (DAT_00bdfa58 != 0)) {
        _DAT_00c81990 =
             thunk_FUN_004f3490(s_RUSSJUMP_MCD_00563890,_DAT_00c81b80,_DAT_00b31f10,_DAT_00b31f24);
      }
      else {
        uVar1 = thunk_FUN_004f3490((&PTR_s_WALK_MCD_00563714)[local_2c],
                                   *(undefined4 *)(&DAT_00c81b80 + local_2c * 4),
                                   *(undefined4 *)(&DAT_00b31f10 + local_2c * 4),
                                   *(undefined4 *)(&DAT_00b31f24 + local_2c * 4));
        *(undefined4 *)(&DAT_00c81990 + local_2c * 4) = uVar1;
      }
      if (*(int *)(&DAT_00c81990 + local_2c * 4) == 0) {
        DAT_00c56700 = 0;
        thunk_FUN_004bf2a0();
        return 0;
      }
      thunk_FUN_004bf2a0();
      for (local_30 = 0; local_30 < *(int *)(&DAT_00c81990 + local_2c * 4); local_30 = local_30 + 1)
      {
      }
      fVar2 = (float10)FUN_0052dfd4();
      *(float *)(&DAT_00c823c0 + local_2c * 4) = (float)fVar2;
    }
    thunk_FUN_004bf2a0();
    uVar1 = 1;
  }
  return uVar1;
}


