/* Driver PC (1999) — модуль DirectorStorage, псевдо-C из Ghidra. 9 функций */

// 004c93e6

void ReadDirectorData(undefined4 param_1)

{
  int local_30;
  undefined4 local_2c;
  undefined4 local_28;
  int local_24;
  int local_20;
  int local_1c;
  int local_18;
  undefined4 local_14;
  int local_10;
  int local_c;
  int local_8;
  
  local_28 = FUN_0052b260(param_1);
  FUN_0052aaf0(&local_10,0xc,1,param_1);
  if ((local_10 == 0x504c5244) && (local_8 == 1)) {
    local_24 = 0xc;
    thunk_FUN_004c64bd();
    thunk_FUN_004c372a();
    for (; local_24 < local_c; local_24 = local_24 + local_1c) {
      local_14 = FUN_0052b260(param_1);
      FUN_0052aaf0(&local_20,0xc,1,param_1);
      if (local_20 == 0x4d414352) {
        if (local_18 == 2) {
          thunk_FUN_004c98de(param_1);
        }
        else if (local_18 == 1) {
          thunk_FUN_004c9a16(param_1);
        }
        else {
          thunk_FUN_004bf2a0(s_ReadDirectorData__Incompatible_r_0055f9a0);
        }
      }
      else if (local_20 == 0x52445052) {
        if (local_18 == 1) {
          FUN_0052aaf0(&local_2c,4,1,param_1);
          DAT_00d17b68 = local_2c;
        }
        else {
          thunk_FUN_004bf2a0(s_ReadDirectorData__Incompatible_d_0055f964);
        }
      }
      else if (local_20 == 0x54505957) {
        if (local_18 == 1) {
          FUN_0052aaf0(&local_30,4,1,param_1);
          if (0 < local_30) {
            thunk_FUN_004c372a();
            DAT_00d17b70 = local_30;
            DAT_00d17c5c = thunk_FUN_004d8db4(local_30 * 0xc,
                                              s_D__Driver_Game_DirectorStorage_c_0055fa1c,0xd8);
            if (DAT_00d17c5c == 0) {
              DAT_00d17b70 = 0;
            }
            else {
              FUN_0052aaf0(DAT_00d17c5c,0xc,DAT_00d17b70,param_1);
            }
          }
        }
        else {
          thunk_FUN_004bf2a0(s_ReadDirectorData__Incompatible_w_0055f9e0);
        }
      }
      else {
        thunk_FUN_004bf2a0(s_ReadDirectorData__Error__unknown_0055fa40);
      }
      FUN_0052b4f0(param_1,local_14,0);
      FUN_0052b4f0(param_1,local_1c,1);
    }
    FUN_0052b4f0(param_1,local_28,0);
    FUN_0052b4f0(param_1,local_c,1);
  }
  else {
    FUN_0052b4f0(param_1,local_28,0);
    FUN_0052b4f0(param_1,local_c,1);
  }
  return;
}


// 004c9621

void FUN_004c9621(undefined4 param_1)

{
  int iVar1;
  int iVar2;
  undefined4 local_10;
  int local_c;
  undefined4 local_8;
  
  iVar1 = FUN_0052b260(param_1);
  local_10 = 0x504c5244;
  local_8 = 1;
  FUN_0052ae80(&local_10,0xc,1,param_1,iVar1);
  thunk_FUN_004c988e(param_1);
  thunk_FUN_004c96d6(param_1);
  thunk_FUN_004c97a2(param_1);
  iVar2 = FUN_0052b260(param_1);
  local_c = iVar2 - iVar1;
  FUN_0052b4f0(param_1,iVar1,0);
  FUN_0052ae80(&local_10,0xc,1,param_1);
  FUN_0052b4f0(param_1,iVar2,0);
  return;
}


// 004c96d6

void FUN_004c96d6(undefined4 param_1)

{
  int local_20;
  int local_1c;
  int local_18;
  int local_14;
  undefined4 local_10;
  int local_c;
  undefined4 local_8;
  
  local_1c = FUN_0052b260(param_1);
  local_10 = 0x54505957;
  local_8 = 1;
  FUN_0052ae80(&local_10,0xc,1,param_1);
  local_20 = DAT_00d17b70;
  FUN_0052ae80(&local_20,4,1,param_1);
  if (local_20 != 0) {
    FUN_0052ae80(DAT_00d17c5c,0xc,local_20,param_1);
  }
  local_14 = FUN_0052b260(param_1);
  local_18 = local_14 - local_1c;
  FUN_0052b4f0(param_1,local_1c,0);
  local_c = local_18;
  FUN_0052ae80(&local_10,0xc,1,param_1);
  FUN_0052b4f0(param_1,local_14,0);
  return;
}


// 004c97a2

void FUN_004c97a2(undefined4 param_1)

{
  int local_24;
  int local_20;
  int local_1c;
  int local_18;
  int local_14;
  undefined4 local_10;
  int local_c;
  undefined4 local_8;
  
  local_20 = FUN_0052b260(param_1);
  local_10 = 0x4d414352;
  local_8 = 2;
  FUN_0052ae80(&local_10,0xc,1,param_1);
  local_24 = DAT_00d17b60;
  FUN_0052ae80(&local_24,4,1,param_1);
  for (local_18 = 0; local_18 < DAT_00d17b60; local_18 = local_18 + 1) {
    FUN_0052ae80(*(undefined4 *)(DAT_00d17c54 + local_18 * 4),0x8c,1,param_1);
  }
  local_14 = FUN_0052b260(param_1);
  local_1c = local_14 - local_20;
  FUN_0052b4f0(param_1,local_20,0);
  local_c = local_1c;
  FUN_0052ae80(&local_10,0xc,1,param_1);
  FUN_0052b4f0(param_1,local_14,0);
  return;
}


// 004c988e

void FUN_004c988e(undefined4 param_1)

{
  undefined4 local_14;
  undefined4 local_10;
  undefined4 local_c;
  undefined4 local_8;
  
  local_10 = 0x52445052;
  local_8 = 1;
  local_c = 0x10;
  FUN_0052ae80(&local_10,0xc,1,param_1);
  local_14 = DAT_00d17b68;
  FUN_0052ae80(&local_14,4,1,param_1);
  return;
}


// 004c98de

void FUN_004c98de(undefined4 param_1)

{
  int iVar1;
  undefined4 uVar2;
  int local_10;
  int local_8;
  
  FUN_0052aaf0(&local_8,4,1,param_1);
  if ((local_8 != 0) &&
     (iVar1 = thunk_FUN_004d8db4(local_8 << 2,s_D__Driver_Game_DirectorStorage_c_0055fa78,0x18c),
     iVar1 != 0)) {
    thunk_FUN_0048db65(iVar1,local_8 << 2);
    for (local_10 = 0; local_10 < local_8; local_10 = local_10 + 1) {
      uVar2 = thunk_FUN_004d8db4(0x8c,s_D__Driver_Game_DirectorStorage_c_0055fa9c,0x195);
      *(undefined4 *)(iVar1 + local_10 * 4) = uVar2;
      if (*(int *)(iVar1 + local_10 * 4) == 0) {
        for (local_10 = 0; local_10 < local_8; local_10 = local_10 + 1) {
          if (*(int *)(iVar1 + local_10 * 4) != 0) {
            thunk_FUN_004d8f30(*(undefined4 *)(iVar1 + local_10 * 4));
          }
        }
        thunk_FUN_004d8f30(iVar1);
        return;
      }
      FUN_0052aaf0(*(undefined4 *)(iVar1 + local_10 * 4),0x8c,1,param_1);
    }
    thunk_FUN_004c64bd();
    DAT_00d17b60 = local_8;
    DAT_00d17c54 = iVar1;
  }
  return;
}


// 004c9a16

void FUN_004c9a16(undefined4 param_1)

{
  int iVar1;
  int iVar2;
  undefined4 uVar3;
  undefined4 local_48 [2];
  undefined4 local_40;
  undefined4 local_3c;
  undefined4 local_38;
  undefined4 local_34;
  undefined4 local_30;
  undefined4 local_1c;
  undefined4 local_18;
  undefined4 local_14;
  undefined4 local_10;
  int local_c;
  int local_8;
  
  FUN_0052aaf0(&local_8,4,1,param_1);
  if ((local_8 != 0) &&
     (iVar2 = thunk_FUN_004d8db4(local_8 << 2,s_D__Driver_Game_DirectorStorage_c_0055fac0,0x1c5),
     iVar2 != 0)) {
    thunk_FUN_0048db65(iVar2,local_8 << 2);
    for (local_c = 0; local_c < local_8; local_c = local_c + 1) {
      uVar3 = thunk_FUN_004d8db4(0x8c,s_D__Driver_Game_DirectorStorage_c_0055fae4,0x1ce);
      *(undefined4 *)(iVar2 + local_c * 4) = uVar3;
      if (*(int *)(iVar2 + local_c * 4) == 0) {
        for (local_c = 0; local_c < local_8; local_c = local_c + 1) {
          if (*(int *)(iVar2 + local_c * 4) != 0) {
            thunk_FUN_004d8f30(*(undefined4 *)(iVar2 + local_c * 4));
          }
        }
        thunk_FUN_004d8f30(iVar2);
        return;
      }
      FUN_0052aaf0(local_48,0x3c,1,param_1);
      thunk_FUN_0048db65(*(undefined4 *)(iVar2 + local_c * 4),0x8c);
      iVar1 = *(int *)(iVar2 + local_c * 4);
      *(undefined4 *)(iVar1 + 0x5c) = local_1c;
      *(undefined4 *)(iVar1 + 0x60) = local_18;
      *(undefined4 *)(iVar1 + 100) = local_14;
      *(undefined4 *)(iVar1 + 0x68) = local_10;
      iVar1 = *(int *)(iVar2 + local_c * 4);
      *(undefined4 *)(iVar1 + 0x4c) = local_1c;
      *(undefined4 *)(iVar1 + 0x50) = local_18;
      *(undefined4 *)(iVar1 + 0x54) = local_14;
      *(undefined4 *)(iVar1 + 0x58) = local_10;
      *(undefined4 *)(*(int *)(iVar2 + local_c * 4) + 8) = local_40;
      *(undefined4 *)(*(int *)(iVar2 + local_c * 4) + 0xc) = local_3c;
      *(undefined4 *)(*(int *)(iVar2 + local_c * 4) + 0x18) = local_30;
      *(undefined4 *)(*(int *)(iVar2 + local_c * 4) + 0x10) = local_38;
      *(undefined4 *)(*(int *)(iVar2 + local_c * 4) + 0x14) = local_34;
      **(undefined4 **)(iVar2 + local_c * 4) = local_48[0];
    }
    thunk_FUN_004c64bd();
    DAT_00d17b60 = local_8;
    DAT_00d17c54 = iVar2;
  }
  return;
}


// 004c9bf4

void FUN_004c9bf4(int param_1)

{
  int iVar1;
  int local_10;
  int local_c;
  int local_8;
  
  DAT_00d17b30 = 1;
  if ((param_1 / 0x96) * 0x96 == param_1) {
    iVar1 = FUN_0052adb0(s_Scripts_Waypoint_tmp_0055fb0c,&DAT_0055fb08);
    if (iVar1 != 0) {
      local_8 = param_1;
      local_10 = (DAT_00d07888 / 0x5dc) * 0x5dc;
      local_c = (DAT_00d07890 / 0x5dc) * 0x5dc;
      FUN_0052ae80(&local_10,0xc,1,iVar1);
      DAT_00d17b40 = DAT_00d17b40 + 1;
      FUN_0052aa10(iVar1);
    }
  }
  return;
}


// 004c9ca0

undefined4 LoadWaypoints(void)

{
  int iVar1;
  undefined4 uVar2;
  int iVar3;
  int iVar4;
  uint uVar5;
  int iVar6;
  
  iVar1 = FUN_0052adb0(s_Scripts_Waypoint_tmp_0055fb28,&DAT_0055fb24);
  if (iVar1 == 0) {
    thunk_FUN_004bf2a0(s_LoadWaypoints__Unable_to_open_wa_0055fb40);
    uVar2 = 0;
  }
  else {
    thunk_FUN_004c64bd();
    thunk_FUN_004c372a();
    iVar3 = FUN_0052b260(iVar1);
    FUN_0052b4f0(iVar1,0,2);
    iVar4 = FUN_0052b260(iVar1);
    FUN_0052b4f0(iVar1,iVar3,0);
    uVar5 = (uint)(iVar4 - iVar3) / 0xc;
    if (uVar5 != 0) {
      iVar6 = thunk_FUN_004d8db4(uVar5 * 0xc,s_D__Driver_Game_DirectorStorage_c_0055fb70,0x238);
      if (iVar6 == 0) {
        thunk_FUN_004bf2a0(s_LoadWaypoints__Unable_to_allocat_0055fb94);
        FUN_0052aa10(iVar1);
        return 0;
      }
      DAT_00d17b70 = uVar5;
      DAT_00d17c5c = iVar6;
      FUN_0052aaf0(iVar6,iVar4 - iVar3,1,iVar1);
    }
    FUN_0052aa10(iVar1);
    if (DAT_00d17b60 == 0) {
      thunk_FUN_004c9360();
    }
    thunk_FUN_004c9dcc();
    uVar2 = 1;
  }
  return uVar2;
}


