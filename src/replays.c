/* Driver PC (1999) — модуль replays, псевдо-C из Ghidra. 7 функций */

// 005181da

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_005181da(void)

{
  int iVar1;
  int iVar2;
  undefined4 uVar3;
  undefined1 local_88 [4];
  undefined1 local_84 [128];
  
  _DAT_00b87ec4 = 1;
  iVar1 = FUN_0052adb0(&DAT_00c54f80,&DAT_00575c04);
  if (iVar1 != 0) {
    iVar2 = thunk_FUN_004d3000(iVar1);
    if (DAT_00b87ea0 == 0) {
      DAT_00c4d724 = thunk_FUN_004d8db4(iVar2 + -4,s_D__Driver_Game_replays_c_00575c24,0x253);
    }
    else {
      DAT_00c4d724 = thunk_FUN_004d8db4(0x40000,s_D__Driver_Game_replays_c_00575c08,0x251);
    }
    FUN_0052aaf0(&DAT_00c4d668,1,4,iVar1);
    FUN_0052aaf0(&DAT_00c4d884,1,4,iVar1);
    FUN_0052aaf0(DAT_00c4d724,1,iVar2 + -4,iVar1);
    FUN_0052aa10(iVar1);
    if ((DAT_00c4d884 & 0x80000000) != 0) {
      DAT_00c4d884 = DAT_00c4d884 & 0x7fffffff;
      DAT_00c4d9a4 = 1;
    }
    if ((DAT_00b87ea0 == 0) || (DAT_00575efc != 2)) {
      uVar3 = FUN_0052adb0(&DAT_00c54fe0,&DAT_00575c40);
      FUN_0052aaf0(&DAT_00d0cb08,1,0x148,uVar3);
      FUN_0052aa10(uVar3);
    }
    DAT_00d0cc3c = 0;
    DAT_00d0cc38 = 0;
    DAT_00d0cc34 = 0;
    DAT_00d0cc30 = 0;
    DAT_00d0cc2c = 0;
    DAT_00d0cc28 = 0;
    _DAT_00d0cc24 = 0;
    DAT_00d0cb08._2_1_ = DAT_00bdf9d4;
    DAT_00d0cb08._0_1_ = 0x41;
    DAT_011458e1 = 7;
    DAT_011458e2 = 0;
    DAT_011458ec = DAT_00bdf9d4;
    DAT_011458ed = DAT_00bdf9d0;
    _DAT_00c4d784 = 0;
    _DAT_00c4d944 = 0;
    DAT_00c55024 = 0;
    DAT_00b5a8c0 = 0;
    DAT_00b31e1c = 0;
    _DAT_00b5a870 = 0;
    DAT_00b31e20 = 0;
    _DAT_00b5a884 = 0;
    thunk_FUN_004c0218(0x40);
    DAT_00b5a8bc = thunk_FUN_004d8db4(0xd2000,s_D__Driver_Game_replays_c_00575c44,0x281);
    if (DAT_00b5a8bc != 0) {
      FUN_0052a910(local_84,s_ReplayData_Chase__s_PINGS_00575c60,&DAT_00c54ac0);
      uVar3 = FUN_0052adb0(local_84,&DAT_00575c7c);
      FUN_0052aaf0(&DAT_00b5a8c4,1,4,uVar3);
      FUN_0052aaf0(DAT_00b5a8bc,DAT_00b5a8c4,0x1a4,uVar3);
      FUN_0052aa10(uVar3);
    }
  }
  if (DAT_00c54b00 == 0) {
    DAT_00b5a898 = 0;
    DAT_01136c48 = 0;
    _DAT_00b87ec0 = 1;
    thunk_FUN_0051879f();
  }
  else {
    iVar1 = FUN_0052adb0(&DAT_00c4d680,&DAT_00575c80);
    if (iVar1 != 0) {
      iVar2 = thunk_FUN_004d3000(iVar1);
      DAT_00c4d720 = thunk_FUN_004d8db4(iVar2 + -4,s_D__Driver_Game_replays_c_00575c84,0x297);
      FUN_0052aaf0(local_88,1,4,iVar1);
      FUN_0052aaf0(&DAT_00c4d880,1,4,iVar1);
      FUN_0052aaf0(DAT_00c4d720,1,iVar2 + -4,iVar1);
      FUN_0052aa10(iVar1);
      if ((DAT_00c4d880 & 0x80000000) != 0) {
        DAT_00c4d880 = DAT_00c4d880 & 0x7fffffff;
        DAT_00c4d9a4 = 1;
      }
      if ((DAT_00b87ea0 == 0) || (DAT_00575efc != 2)) {
        uVar3 = FUN_0052adb0(&DAT_00c4d8e0,&DAT_00575ca0);
        FUN_0052aaf0(&DAT_00d077c0,1,0x148,uVar3);
        FUN_0052aa10(uVar3);
      }
      DAT_00d078f4 = 0;
      DAT_00d078f0 = 0;
      DAT_00d078ec = 0;
      DAT_00d078e8 = 0;
      DAT_00d078e4 = 0;
      DAT_00d078e0 = 0;
      DAT_00d078dc = 0;
      DAT_00d077c0._0_1_ = 0;
      DAT_00c4d780 = 0;
      DAT_00c4d940 = 0;
      DAT_00c55020 = 0;
      DAT_00b5a86c = 0;
      DAT_00b5a880 = 0;
      thunk_FUN_004c0218(0xffffffff);
      DAT_00b5a850 = DAT_00b5a850 + '\x01';
    }
  }
  return;
}


// 005186ce

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_005186ce(void)

{
  int local_8;
  
  DAT_00c4da58 = DAT_00d118c0 + 1;
  for (local_8 = 0; local_8 < 5; local_8 = local_8 + 1) {
    *(undefined4 *)(&DAT_00b5a858 + local_8 * 4) = 0;
    (&DAT_00b5a86c)[local_8] = 0;
    (&DAT_00b5a880)[local_8] = 0;
    *(undefined4 *)(&DAT_00c4d7a0 + local_8 * 4) = 0;
  }
  _DAT_00b5a89c = 0;
  DAT_00b5a8a0 = 0;
  DAT_00b5a8a4 = 0;
  if (DAT_00b87eac != 0) {
    DAT_00c4d668 = 0;
  }
  DAT_00b31e1c = 0;
  DAT_00b31e20 = 0;
  DAT_00c4bde0 = 0;
  DAT_00c54d08 = 0;
  DAT_00b5a8c0 = 0;
  DAT_00b5a894 = 1;
  return;
}


// 0051879f

void FUN_0051879f(void)

{
  undefined4 uVar1;
  undefined1 local_44 [64];
  
  if ((DAT_00b5a850 == '\0') &&
     (DAT_00b5a854 = thunk_FUN_004d8db4(0x40000,s_D__Driver_Game_replays_c_00575ca4,0x31b),
     DAT_00b5a854 != 0)) {
    if (DAT_00b87eac != 0) {
      DAT_00b5a8bc = (void *)thunk_FUN_004d8db4(0xd2000,s_D__Driver_Game_replays_c_00575cc0,0x330);
      if (DAT_00b5a8bc == (void *)0x0) {
        return;
      }
      _memset(DAT_00b5a8bc,0,0xd2000);
      if (DAT_00b87eac != 0) {
        FUN_0052a910(local_44,s_ReplayData_Chase__s_LEADER_00575cdc,&DAT_00c54ac0);
        uVar1 = FUN_0052adb0(local_44,&DAT_00575cf8);
        FUN_0052aaf0(&DAT_00d0cb08,1,0x148,uVar1);
        FUN_0052aa10(uVar1);
        DAT_00d0cb08._0_1_ = 0x41;
        DAT_00d0cb08._2_1_ = DAT_00bdf9d4;
        DAT_011458e1 = 8;
        DAT_011458e2 = 0;
        DAT_011458ec = DAT_00bdf9d4;
        DAT_011458ed = DAT_00bdf9d0;
        thunk_FUN_004c0218(0x40);
      }
    }
    thunk_FUN_005186ce();
    DAT_00d1187c = 0x20;
    thunk_FUN_00519a45(0);
  }
  return;
}


// 005188ec

void FUN_005188ec(void)

{
  thunk_FUN_005283b5(&DAT_00c54d20,&DAT_00d077c0,0x148);
  thunk_FUN_005283b5(&DAT_00c4da60,&DAT_00d06a20,0x34);
  thunk_FUN_005283b5(&DAT_00c4da00,&DAT_00d0de00,0x34);
  thunk_FUN_005283b5(&DAT_00c4d9c0,&DAT_00d0eb80,0x34);
  DAT_00b5a898 = 0;
  thunk_FUN_005186ce();
  return;
}


// 00518953

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_00518953(int param_1)

{
  DAT_00d1187c = 0x10100000;
  thunk_FUN_00518d32(DAT_00b5a898);
  if (param_1 != 0) {
    thunk_FUN_005283b5(&DAT_00c54b60,&DAT_00c54d20,0x148);
    thunk_FUN_005283b5(&DAT_00c4d8a0,&DAT_00c4da60,0x34);
    thunk_FUN_005283b5(&DAT_00c4d800,&DAT_00c4da00,0x34);
    thunk_FUN_005283b5(&DAT_00c4d840,&DAT_00c4d9c0,0x34);
    thunk_FUN_005283b5(DAT_00c4d724,DAT_00b5a854,DAT_00c4bde0);
    DAT_00c4d708 = DAT_00c54d08;
    DAT_00c4da94 = 1;
  }
  thunk_FUN_005188ec();
  _DAT_00c4d784 = DAT_00c4d780;
  _DAT_00c4d944 = DAT_00c4d940;
  DAT_00c55024 = DAT_00c55020;
  _DAT_00b5a870 = DAT_00b5a86c;
  _DAT_00b5a884 = DAT_00b5a880;
  thunk_FUN_005283b5(&DAT_00d0cb08,&DAT_00c54b60,0x148);
  thunk_FUN_005283b5(&DAT_00d07754,&DAT_00c4d8a0,0x34);
  thunk_FUN_005283b5(&DAT_00d0eb34,&DAT_00c4d800,0x34);
  thunk_FUN_005283b5(&DAT_00d0f8b4,&DAT_00c4d840,0x34);
  DAT_00d0cb08._0_1_ = 0x41;
  thunk_FUN_004c0218(0x41);
  DAT_00c4d704 = 0;
  DAT_00c4d700 = 1;
  return;
}


// 00518ab4

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __fastcall FUN_00518ab4(undefined4 param_1)

{
  undefined4 uVar1;
  
  if ((((DAT_00b87ea0 == 0) || (DAT_00575efc != 2)) || (DAT_00c4d700 != 0)) && (DAT_00c4da94 != 0))
  {
    uVar1 = thunk_FUN_00518f44(1,param_1);
    if (DAT_00c55024 == DAT_00c4d708) {
      thunk_FUN_005283b5(&DAT_00d0cb08,&DAT_00c54b60,0x148);
      thunk_FUN_005283b5(&DAT_00d07754,&DAT_00c4d8a0,0x34);
      thunk_FUN_005283b5(&DAT_00d0eb34,&DAT_00c4d800,0x34);
      thunk_FUN_005283b5(&DAT_00d0f8b4,&DAT_00c4d840,0x34);
      DAT_00d0cb08._0_1_ = 0x41;
      thunk_FUN_004c0218(0x41);
      _DAT_00c4d784 = 0;
      _DAT_00c4da44 = 0;
      DAT_00c55024 = 0;
      _DAT_00c4d944 = 0;
      DAT_00c4d700 = 0;
    }
    else {
      thunk_FUN_004ddaca(0x41,uVar1);
      thunk_FUN_004dc8b0(&DAT_00d0cb08,1);
    }
  }
  return;
}


// 00518bbc

void FUN_00518bbc(void)

{
  int iVar1;
  int iVar2;
  
  if ((DAT_00b87eb0 == 0) && (iVar1 = FUN_0052adb0(&DAT_00c4d680,&DAT_00575cfc), iVar1 != 0)) {
    iVar2 = thunk_FUN_004d3000(iVar1);
    DAT_00c4d720 = thunk_FUN_004d8db4(iVar2 + -4,s_D__Driver_Game_replays_c_00575d00,0x3ed);
    FUN_0052aaf0(&DAT_00c4d668,1,4,iVar1);
    FUN_0052aaf0(&DAT_00c4d880,1,4,iVar1);
    FUN_0052aaf0(DAT_00c4d720,1,iVar2 + -4,iVar1);
    FUN_0052aa10(iVar1);
    if ((DAT_00c4d880 & 0x80000000) != 0) {
      DAT_00c4d880 = DAT_00c4d880 & 0x7fffffff;
      DAT_00c4d9a4 = 1;
    }
    DAT_00d078f8 = 0;
    DAT_00d078f0 = 0;
    DAT_00d078ec = 0;
    DAT_00d078e8 = 0;
    DAT_00d078e4 = 0;
    DAT_00d078e0 = 0;
    DAT_00d078dc = 0;
    DAT_00c4d780 = 0;
    DAT_00c4d940 = 0;
    DAT_00c55020 = 0;
    DAT_00b5a8c0 = 0;
    DAT_00b31e1c = 0;
    DAT_00b5a86c = 0;
    DAT_00b31e20 = 0;
    DAT_00b5a880 = 0;
  }
  return;
}


