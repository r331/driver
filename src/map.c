/* Driver PC (1999) — модуль map, псевдо-C из Ghidra. 49 функций */

// 004eb449

void FUN_004eb449(void)

{
  DAT_00c98ed0 = thunk_FUN_004d8db4(0x400000,s_D__Driver_Game_map_c_00563040,0xf7);
  return;
}


// 004eb46a

void FUN_004eb46a(void)

{
  if (DAT_00c98ed0 != 0) {
    thunk_FUN_004d8f30(DAT_00c98ed0);
    DAT_00c98ed0 = 0;
  }
  return;
}


// 004eb490

void FUN_004eb490(undefined4 param_1)

{
  char cVar1;
  undefined4 *puVar2;
  int iVar3;
  undefined4 *puVar4;
  undefined1 local_40 [32];
  undefined4 local_20;
  int local_1c;
  int local_18;
  undefined4 local_14;
  int local_10;
  int local_c;
  int local_8;
  
  local_14 = thunk_FUN_004d8db4(0x20000,s_D__Driver_Game_map_c_00563058,0x119);
  thunk_FUN_004eb449();
  local_8 = DAT_00c98ed0;
  cVar1 = thunk_FUN_004d9596(&DAT_00cf2f8c,4,1,param_1);
  if (cVar1 != '\0') {
    for (local_18 = 0; local_18 < DAT_00cf2f8c; local_18 = local_18 + 1) {
      thunk_FUN_004d9596(&local_1c,4,1,param_1);
      thunk_FUN_004d9596(local_14,local_1c,1,param_1);
      local_1c = thunk_FUN_00475a3d(local_14,local_8);
      local_c = local_8;
      (&DAT_00cfe7a0)[local_18] = local_8;
      local_8 = local_8 + local_1c;
      local_10 = local_8 - DAT_00c98ed0;
    }
    for (local_18 = 0; local_18 < DAT_00cf2f8c; local_18 = local_18 + 1) {
      local_c = (&DAT_00cfe7a0)[local_18];
      if (*(int *)(local_c + 4) == -1) {
        thunk_FUN_00427757(local_c);
        thunk_FUN_0042793f(local_c,0);
        thunk_FUN_0042793f(local_c,1);
      }
    }
    for (local_18 = 0; local_18 < DAT_00cf2f8c; local_18 = local_18 + 1) {
      local_c = (&DAT_00cfe7a0)[local_18];
      if (*(int *)(local_c + 4) != -1) {
        thunk_FUN_00427757(local_c);
        thunk_FUN_0042793f(local_c,0);
        thunk_FUN_0042793f(local_c,1);
      }
    }
    for (local_18 = 0; local_18 < DAT_00cf2f8c; local_18 = local_18 + 1) {
      puVar2 = (undefined4 *)thunk_FUN_00426ce3(local_40,local_18);
      puVar4 = (undefined4 *)(&DAT_00cf56e0 + local_18 * 0x20);
      for (iVar3 = 8; iVar3 != 0; iVar3 = iVar3 + -1) {
        *puVar4 = *puVar2;
        puVar2 = puVar2 + 1;
        puVar4 = puVar4 + 1;
      }
      thunk_FUN_004757d2((&DAT_00cfe7a0)[local_18]);
      local_20 = thunk_FUN_00475906((&DAT_00cfe7a0)[local_18]);
      if ((*(ushort *)((&DAT_00cfe7a0)[local_18] + 2) & 0x800) == 0) {
        if ((*(ushort *)((&DAT_00cfe7a0)[local_18] + 2) & 8) == 0) {
          if ((*(ushort *)((&DAT_00cfe7a0)[local_18] + 2) & 0x1000) == 0) {
            if ((*(ushort *)((&DAT_00cfe7a0)[local_18] + 2) & 0x80) == 0) {
              if ((*(ushort *)((&DAT_00cfe7a0)[local_18] + 2) & 0x40) == 0) {
                if ((*(uint *)((&DAT_00cfe7a0)[local_18] + 8) & 2) == 0) {
                  if ((*(uint *)((&DAT_00cfe7a0)[local_18] + 8) & 0x800) == 0) {
                    (&DAT_00c98a40)[local_18] = 1;
                  }
                  else if (DAT_00b87e84 == 0) {
                    (&DAT_00c98a40)[local_18] = 0;
                  }
                  else {
                    (&DAT_00c98a40)[local_18] = 1;
                  }
                }
                else {
                  (&DAT_00c98a40)[local_18] = 7;
                }
              }
              else {
                (&DAT_00c98a40)[local_18] = 5;
              }
            }
            else {
              (&DAT_00c98a40)[local_18] = 2;
            }
          }
          else {
            (&DAT_00c98a40)[local_18] = 4;
          }
        }
        else {
          (&DAT_00c98a40)[local_18] = 6;
        }
      }
      else {
        (&DAT_00c98a40)[local_18] = 3;
      }
    }
  }
  thunk_FUN_004d8f30(local_14);
  return;
}


// 004eb7cf

void FUN_004eb7cf(undefined4 param_1)

{
  int local_8;
  
  for (local_8 = 0; local_8 < 0x400; local_8 = local_8 + 1) {
    thunk_FUN_004d9596(&DAT_0125f420 + local_8 * 0x46,0x46,1,param_1);
  }
  return;
}


// 004eb811

void FUN_004eb811(undefined4 param_1,uint param_2)

{
  int iVar1;
  undefined4 unaff_EBP;
  undefined4 *local_38;
  int local_34;
  undefined4 local_30;
  undefined4 local_2c;
  undefined4 local_28;
  undefined2 local_24;
  undefined2 local_22;
  undefined2 local_20;
  undefined4 local_1c;
  undefined4 local_18;
  undefined4 local_14;
  undefined2 local_10;
  undefined2 local_e;
  undefined2 local_c;
  ushort local_8;
  ushort uStack_6;
  undefined2 uStack_4;
  undefined2 uStack_2;
  
  uStack_4 = (undefined2)unaff_EBP;
  uStack_2 = (undefined2)((uint)unaff_EBP >> 0x10);
  DAT_00d00200 = param_2 / 0x2c;
  iVar1 = DAT_00d00200 << 6;
  DAT_00d0020c = thunk_FUN_004d8db4(iVar1,s_D__Driver_Game_map_c_00563070,0x198);
  DAT_00c97a2c = (undefined4 *)thunk_FUN_004d8db4(iVar1,s_D__Driver_Game_map_c_00563088,0x199);
  DAT_00d0dde0 = 1;
  local_38 = DAT_00c97a2c;
  for (local_34 = 0; local_34 < (int)DAT_00d00200; local_34 = local_34 + 1) {
    thunk_FUN_004d9596(&local_30,0x2c,1,param_1);
    *local_38 = local_30;
    local_38[1] = local_2c;
    local_38[2] = local_28;
    local_38[3] = 0x3f800000;
    *(undefined2 *)(local_38 + 4) = local_24;
    *(undefined2 *)((int)local_38 + 0x12) = local_22;
    *(undefined2 *)(local_38 + 5) = local_20;
    local_38[6] = local_1c;
    local_38[7] = local_18;
    local_38[8] = local_14;
    local_38[9] = 0x3f800000;
    *(undefined2 *)(local_38 + 10) = local_10;
    *(undefined2 *)((int)local_38 + 0x2a) = local_e;
    *(undefined2 *)(local_38 + 0xb) = local_c;
    local_38[0xc] = (uint)local_8;
    local_38[0xd] = (uint)uStack_6;
    local_38 = local_38 + 0x10;
  }
  return;
}


// 004eb975

void FUN_004eb975(undefined4 param_1)

{
  undefined4 uVar1;
  bool bVar2;
  ushort local_38 [2];
  undefined1 local_34 [4];
  int local_30;
  int local_2c;
  short local_28 [2];
  undefined4 local_24;
  int local_20;
  int local_1c;
  int local_18;
  int local_14;
  undefined1 local_10 [4];
  int local_c;
  uint local_8;
  
  uVar1 = FUN_0052b260(param_1);
  thunk_FUN_004ec154(param_1,uVar1);
  thunk_FUN_004d9596(&local_1c,4,1,param_1);
  thunk_FUN_00489d20();
  DAT_00b31ee0 = 0;
  local_30 = *(int *)(&DAT_00562d80 + DAT_00b87e30 * 4);
  if (DAT_00b87e30 == 4) {
    local_14 = 0x11;
  }
  else {
    local_14 = -1;
  }
  local_24 = FUN_0052b260(param_1);
  local_20 = 0;
  local_2c = 0;
  while (local_2c < local_1c) {
    FUN_0052aaf0(local_38,2,1,param_1);
    FUN_0052aaf0(local_28,2,1,param_1);
    local_18 = local_2c;
    bVar2 = (local_38[0] & 0x10) == 0;
    if (bVar2) {
      FUN_0052b4f0(param_1,0x20000,1);
    }
    else {
      FUN_0052aaf0(&DAT_00c98f00,0x10000,1,param_1);
      FUN_0052aaf0(local_10,2,1,param_1);
      FUN_0052aaf0(local_34,2,1,param_1);
      FUN_0052b4f0(param_1,0x10000,1);
    }
    local_8 = (uint)!bVar2;
    if ((local_38[0] & 1) == 0) {
      if (((local_38[0] & 4) == 0) || (local_28[0] != DAT_00d1192c)) {
        if ((((local_38[0] & 8) != 0) && (local_28[0] == DAT_00d1192c)) || ((local_38[0] & 2) != 0))
        {
          local_20 = local_20 + 0x20000;
        }
      }
      else {
        local_20 = local_20 + 0x20000;
      }
    }
    else if ((local_2c == local_30) || (local_2c == local_14)) {
      if (local_8 == 0) {
        local_20 = local_20 + 0x20000;
      }
      else {
        local_20 = local_20 + 0x10000;
      }
    }
    if (local_8 == 0) {
      local_2c = local_2c + 1;
    }
    else {
      local_2c = local_2c + 2;
    }
  }
  if ((local_20 != 0) &&
     (DAT_00d01260 = thunk_FUN_004d8db4(local_20,s_D__Driver_Game_map_c_005630a0,0x225),
     DAT_00d01260 == 0)) {
    MessageBoxA(DAT_00bdf9c0,s_Could_not_malloc_space_for_RAM_t_005630c0,s_ERROR_005630b8,0);
  }
  FUN_0052b4f0(param_1,local_24,0);
  local_2c = 0;
  while (local_2c < local_1c) {
    thunk_FUN_004d9596(local_38,2,1,param_1);
    thunk_FUN_004d9596(local_28,2,1,param_1);
    local_18 = local_2c;
    bVar2 = (local_38[0] & 0x10) == 0;
    if (bVar2) {
      thunk_FUN_004d9596(&DAT_00c98f00,0x20000,1,param_1);
    }
    else {
      thunk_FUN_004d9596(&DAT_00c98f00,0x10000,1,param_1);
      thunk_FUN_004d9596(local_10,2,1,param_1);
      thunk_FUN_004d9596(local_34,2,1,param_1);
      thunk_FUN_004d9596(&DAT_00ce1f60,0x10000,1,param_1);
      local_c = local_18 + 1;
    }
    local_8 = (uint)!bVar2;
    if ((local_38[0] & 1) == 0) {
      if ((local_38[0] & 4) == 0) {
        if ((((local_38[0] & 8) != 0) && (local_28[0] == DAT_00d1192c)) || ((local_38[0] & 2) != 0))
        {
          if (local_8 == 0) {
            (&DAT_01145a60)[local_18 * 0x10] = 0;
            *(int *)(&DAT_01145a64 + local_18 * 0x10) = DAT_00d01260 + DAT_00b31ee0;
            DAT_00b31ee0 = DAT_00b31ee0 + 0x20000;
            thunk_FUN_005283b5(*(undefined4 *)(&DAT_01145a64 + local_18 * 0x10),&DAT_00c98f00,
                               0x20000);
          }
          else {
            thunk_FUN_004efc7c(local_18,&DAT_00c98f00);
            thunk_FUN_004efc7c(local_c,&DAT_00ce1f60);
            (&DAT_01145a60)[local_18 * 0x10] = 4;
            *(int *)(&DAT_01145a64 + local_18 * 0x10) = DAT_00d01260 + DAT_00b31ee0;
            DAT_00b31ee0 = DAT_00b31ee0 + 0x10000;
            thunk_FUN_005283b5(*(undefined4 *)(&DAT_01145a64 + local_18 * 0x10),&DAT_00c98f00,
                               0x10000);
            (&DAT_01145a60)[local_c * 0x10] = 0xc;
            *(int *)(&DAT_01145a64 + local_c * 0x10) = DAT_00d01260 + DAT_00b31ee0;
            DAT_00b31ee0 = DAT_00b31ee0 + 0x10000;
            thunk_FUN_005283b5(*(undefined4 *)(&DAT_01145a64 + local_c * 0x10),&DAT_00ce1f60,0x10000
                              );
          }
        }
      }
      else if (local_28[0] == DAT_00d1192c) {
        if (local_8 == 0) {
          (&DAT_01145a60)[local_18 * 0x10] = 2;
          thunk_FUN_0048a239(local_18,&DAT_00c98f00);
          *(int *)(&DAT_01145a64 + local_18 * 0x10) = DAT_00d01260 + DAT_00b31ee0;
          DAT_00b31ee0 = DAT_00b31ee0 + 0x20000;
          thunk_FUN_005283b5(*(undefined4 *)(&DAT_01145a64 + local_18 * 0x10),&DAT_00c98f00,0x20000)
          ;
        }
        else {
          thunk_FUN_004efc7c(local_18,&DAT_00c98f00);
          thunk_FUN_004efc7c(local_c,&DAT_00ce1f60);
          (&DAT_01145a60)[local_18 * 0x10] = 6;
          (&DAT_01145a60)[local_c * 0x10] = 0xe;
          thunk_FUN_00489f50(local_18,&DAT_00c98f00,&DAT_00ce1f60);
          *(int *)(&DAT_01145a64 + local_18 * 0x10) = DAT_00d01260 + DAT_00b31ee0;
          DAT_00b31ee0 = DAT_00b31ee0 + 0x10000;
          thunk_FUN_005283b5(*(undefined4 *)(&DAT_01145a64 + local_18 * 0x10),&DAT_00c98f00,0x10000)
          ;
          *(int *)(&DAT_01145a64 + local_c * 0x10) = DAT_00d01260 + DAT_00b31ee0;
          DAT_00b31ee0 = DAT_00b31ee0 + 0x10000;
          thunk_FUN_005283b5(*(undefined4 *)(&DAT_01145a64 + local_c * 0x10),&DAT_00ce1f60,0x10000);
        }
      }
    }
    else if (local_8 == 0) {
      (&DAT_01145a60)[local_18 * 0x10] = 2;
      thunk_FUN_0048a239(local_18,&DAT_00c98f00);
      if ((local_18 == local_30) || (local_18 == local_14)) {
        *(int *)(&DAT_01145a64 + local_18 * 0x10) = DAT_00d01260 + DAT_00b31ee0;
        DAT_00b31ee0 = DAT_00b31ee0 + 0x20000;
        thunk_FUN_005283b5(*(undefined4 *)(&DAT_01145a64 + local_18 * 0x10),&DAT_00c98f00,0x20000);
        if (local_18 == local_30) {
          DAT_00c82530 = 1;
        }
      }
    }
    else {
      thunk_FUN_004efc7c(local_18,&DAT_00c98f00);
      thunk_FUN_004efc7c(local_c,&DAT_00ce1f60);
      (&DAT_01145a60)[local_18 * 0x10] = 6;
      (&DAT_01145a60)[local_c * 0x10] = 0xe;
      thunk_FUN_00489f50(local_18,&DAT_00c98f00,&DAT_00ce1f60);
      if ((local_18 == local_30) || (local_18 == local_14)) {
        *(int *)(&DAT_01145a64 + local_18 * 0x10) = DAT_00d01260 + DAT_00b31ee0;
        DAT_00b31ee0 = DAT_00b31ee0 + 0x10000;
        thunk_FUN_005283b5(*(undefined4 *)(&DAT_01145a64 + local_18 * 0x10),&DAT_00c98f00,0x10000);
        if (local_18 == local_30) {
          DAT_00c82530 = 0;
        }
      }
      if ((local_c == local_30) || (local_c == local_14)) {
        *(int *)(&DAT_01145a64 + local_c * 0x10) = DAT_00d01260 + DAT_00b31ee0;
        DAT_00b31ee0 = DAT_00b31ee0 + 0x10000;
        thunk_FUN_005283b5(*(undefined4 *)(&DAT_01145a64 + local_c * 0x10),&DAT_00ce1f60,0x10000);
        if (local_c == local_30) {
          DAT_00c82530 = 0;
        }
      }
    }
    if (local_8 == 0) {
      local_2c = local_2c + 1;
    }
    else {
      local_2c = local_2c + 2;
    }
  }
  return;
}


// 004ec154

void FUN_004ec154(undefined4 param_1)

{
  int iVar1;
  CHAR local_110 [256];
  int local_10;
  short local_c [2];
  short local_8 [2];
  
  local_10 = 0x32;
  while (iVar1 = local_10 + -1, local_10 != 0) {
    *(undefined4 *)(&DAT_01252aa0 + iVar1 * 4) = 0;
    local_10 = iVar1;
  }
  local_10 = iVar1;
  thunk_FUN_004d9596(local_c,2,1,param_1);
  local_10 = (int)local_c[0];
  while (local_10 != 0) {
    local_10 = local_10 + -1;
    thunk_FUN_004d9596(local_8,2,1,param_1);
    if ((local_8[0] < 0) || (0x31 < local_8[0])) {
      FUN_0052a910(local_110,s_Illegal_palette_slot_load_access_005630f0,(int)local_8[0]);
      thunk_FUN_004bf2a0(local_110);
      FUN_0052a910(local_110,s_Tried_to_store_palette_to_slot___00563118,(int)local_8[0]);
      MessageBoxA(DAT_00bdf9c0,local_110,s_Error_0056313c,0);
      FUN_0052b4f0(param_1,0x400,1);
    }
    else {
      thunk_FUN_004d9596(&DAT_01252be0 + local_8[0] * 0x400,0x400,1,param_1);
      *(undefined4 *)(&DAT_01252aa0 + local_8[0] * 4) = 1;
    }
  }
  return;
}


// 004ec280

void FUN_004ec280(undefined4 param_1,int param_2)

{
  thunk_FUN_004d9596(&DAT_00b31ed4,4,1,param_1);
  DAT_00b31ecc = thunk_FUN_004d8db4(param_2 + -4,s_D__Driver_Game_map_c_00563144,0x32c);
  if (DAT_00b31ecc == 0) {
    DAT_00b31ed4 = 0;
  }
  else {
    thunk_FUN_004d9596(DAT_00b31ecc,param_2 + -4,1,param_1);
  }
  return;
}


// 004ec2ec

void __thiscall FUN_004ec2ec(undefined4 param_1,undefined4 param_2,undefined4 param_3)

{
  undefined4 uVar1;
  
  uVar1 = thunk_FUN_004d8db4(param_3,s_D__Driver_Game_map_c_0056315c,0x347,param_1);
  thunk_FUN_004d9596(uVar1,1,param_3,param_2);
  thunk_FUN_004d8f30(uVar1);
  return;
}


// 004ec336

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_004ec336(undefined4 param_1,int param_2)

{
  thunk_FUN_004d9596(&DAT_00c1ed60,4,1,param_1);
  thunk_FUN_004d9596(&DAT_00c1cc68,4,1,param_1);
  DAT_00bf1c10 = DAT_00c1ed60 * 0x5dc;
  DAT_00bf1c24 = DAT_00c1cc68 * 0x5dc;
  DAT_00c1cc64 = DAT_00bf1c10 / 2;
  _DAT_00c12c40 = DAT_00bf1c24 / 2;
  _DAT_00bf1c0c = DAT_00c1ed60 / 2;
  _DAT_00c1cc90 = DAT_00c1cc68 / 2;
  DAT_00b5a900 = thunk_FUN_004d8db4(param_2 + -8,s_D__Driver_Game_map_c_00563174,0x35f);
  thunk_FUN_004d9596(DAT_00b5a900,1,param_2 + -8,param_1);
  return;
}


// 004ec3fd

void FUN_004ec3fd(undefined4 param_1,int param_2)

{
  thunk_FUN_004d9596(&DAT_00c1ed60,4,1,param_1);
  thunk_FUN_004d9596(&DAT_00c1cc68,4,1,param_1);
  DAT_00b5a908 = thunk_FUN_004d8db4(param_2 + -8,s_D__Driver_Game_map_c_0056318c,0x371);
  thunk_FUN_004d9596(DAT_00b5a908,1,param_2 + -8,param_1);
  return;
}


// 004ec466

void FUN_004ec466(undefined4 param_1)

{
  thunk_FUN_004d9596(&DAT_00b5a8e8,1,4,param_1);
  thunk_FUN_004d9596(&DAT_00bf1c40,DAT_00b5a8e8,0x42,param_1);
  return;
}


// 004ec49a

void FUN_004ec49a(undefined4 param_1)

{
  thunk_FUN_004d9596(&DAT_00b5a8ec,1,4,param_1);
  thunk_FUN_004d9596(&DAT_00c1ed80,DAT_00b5a8ec,0x2c,param_1);
  return;
}


// 004ec4ce

void FUN_004ec4ce(undefined4 param_1,undefined4 param_2)

{
  DAT_00b5a90c = thunk_FUN_004d8db4(param_2,s_D__Driver_Game_map_c_005631a4,0x39f);
  if (DAT_00b5a90c != 0) {
    thunk_FUN_004d9596(DAT_00b5a90c,param_2,1,param_1);
    DAT_00bdfbc4 = DAT_00b5a90c;
    thunk_FUN_0051be3c();
  }
  return;
}


// 004ec522

void FUN_004ec522(undefined4 param_1)

{
  thunk_FUN_004d9596(&DAT_00b5a8e8,1,4,param_1);
  thunk_FUN_004d9596(&DAT_00c12c60,DAT_00b5a8e8,0x14,param_1);
  return;
}


// 004ec556

void FUN_004ec556(undefined4 param_1)

{
  thunk_FUN_004d9596(&DAT_00b5a8ec,1,4,param_1);
  thunk_FUN_004d9596(&DAT_00c1cd20,DAT_00b5a8ec,8,param_1);
  return;
}


// 004ec58a

void FUN_004ec58a(undefined4 param_1)

{
  undefined4 uVar1;
  undefined4 uVar2;
  undefined4 local_10;
  int local_c;
  undefined4 local_8;
  
  local_8 = thunk_FUN_004d8db4(0x80000,s_D__Driver_Game_map_c_005631bc,0x3d4);
  uVar1 = thunk_FUN_004d8db4(0x80000,s_D__Driver_Game_map_c_005631d4,0x3d5);
  for (local_c = 0; local_c < DAT_00d12418; local_c = local_c + 1) {
    if (*(int *)(&DAT_00d11a60 + local_c * 4) != 0) {
      thunk_FUN_004d8f30(*(undefined4 *)(&DAT_00d11a60 + local_c * 4));
      *(undefined4 *)(&DAT_00d11a60 + local_c * 4) = 0;
    }
  }
  thunk_FUN_004d9596(&DAT_00d12418,4,1,param_1,uVar1);
  local_c = 0;
  while( true ) {
    if (DAT_00d12418 <= local_c) {
      thunk_FUN_004d8f30(uVar1);
      thunk_FUN_004d8f30(local_8,0);
      return;
    }
    thunk_FUN_004d9596(&local_10,4,1,param_1);
    thunk_FUN_004d9596(local_8,local_10,1,param_1);
    local_10 = thunk_FUN_00475a3d(local_8,uVar1);
    uVar2 = thunk_FUN_004d8db4(local_10,s_D__Driver_Game_map_c_005631ec,0x3ed);
    *(undefined4 *)(&DAT_00d11a60 + local_c * 4) = uVar2;
    if (*(int *)(&DAT_00d11a60 + local_c * 4) == 0) break;
    thunk_FUN_005283b5(*(undefined4 *)(&DAT_00d11a60 + local_c * 4),uVar1,local_10);
    thunk_FUN_00427757(*(undefined4 *)(&DAT_00d11a60 + local_c * 4));
    thunk_FUN_0042793f(*(undefined4 *)(&DAT_00d11a60 + local_c * 4),0);
    thunk_FUN_0042793f(*(undefined4 *)(&DAT_00d11a60 + local_c * 4),1);
    thunk_FUN_004757d2(*(undefined4 *)(&DAT_00d11a60 + local_c * 4));
    thunk_FUN_00475906(*(undefined4 *)(&DAT_00d11a60 + local_c * 4));
    local_c = local_c + 1;
  }
  DAT_00d12418 = 0;
  MessageBoxA(DAT_00bdf9c0,s_Not_enogh_memory_for_event_model_00563214,s_Memory_Error__00563204,0x30
             );
  thunk_FUN_004d8f30(uVar1);
  thunk_FUN_004d8f30(local_8,0);
  return;
}


// 004ec7ac

void __thiscall FUN_004ec7ac(undefined4 param_1,undefined4 param_2,undefined4 param_3)

{
  int iVar1;
  
  iVar1 = thunk_FUN_004d8db4(param_3,s_D__Driver_Game_map_c_00563238,0x415,param_1);
  if (iVar1 != 0) {
    thunk_FUN_004d9596(iVar1,param_3,1,param_2);
    DAT_00b31ed8 = iVar1;
  }
  return;
}


// 004ec7f4

void FUN_004ec7f4(undefined4 param_1,undefined4 param_2)

{
  DAT_00b31ee4 = thunk_FUN_004d8db4(param_2,s_D__Driver_Game_map_c_00563250,0x42b);
  if (DAT_00b31ee4 != 0) {
    thunk_FUN_004d9596(DAT_00b31ee4,param_2,1,param_1);
  }
  return;
}


// 004ec837

int FUN_004ec837(char *param_1)

{
  char cVar1;
  int iVar2;
  char *local_c;
  int local_8;
  
  if (DAT_00b31ed8 != (char *)0x0) {
    local_c = DAT_00b31ed8;
    for (local_8 = 0; local_8 < DAT_00cf2f8c; local_8 = local_8 + 1) {
      iVar2 = __strcmpi(local_c,param_1);
      if (iVar2 == 0) {
        return local_8;
      }
      do {
        cVar1 = *local_c;
        local_c = local_c + 1;
      } while (cVar1 != '\0');
    }
  }
  return -1;
}


// 004ec8a8

undefined4 FUN_004ec8a8(char *param_1)

{
  char cVar1;
  int iVar2;
  char *local_c;
  int local_8;
  
  if (DAT_00b31ed8 != (char *)0x0) {
    local_c = DAT_00b31ed8;
    for (local_8 = 0; local_8 < DAT_00cf2f8c; local_8 = local_8 + 1) {
      iVar2 = _strcmp(local_c,param_1);
      if (iVar2 == 0) {
        return (&DAT_00cfe7a0)[local_8];
      }
      do {
        cVar1 = *local_c;
        local_c = local_c + 1;
      } while (cVar1 != '\0');
    }
  }
  return 0;
}


// 004ec91e

int FUN_004ec91e(char *param_1)

{
  bool bVar1;
  int local_18;
  int local_14;
  size_t local_10;
  int local_8;
  
  if ((DAT_00b31ed4 != 0) && (local_10 = _strlen(param_1), local_10 != 0)) {
    if (8 < (int)local_10) {
      local_10 = 8;
    }
    local_8 = DAT_00b31ed4;
    local_18 = DAT_00b31ecc;
    if (DAT_00b31ecc != 0) {
      while (local_8 != 0) {
        bVar1 = true;
        for (local_14 = 0; local_14 < (int)local_10; local_14 = local_14 + 1) {
          if (param_1[local_14] != *(char *)(local_18 + local_14)) {
            bVar1 = false;
            break;
          }
        }
        if (bVar1) {
          if (local_14 == 8) {
            return local_18;
          }
          if (*(char *)(local_18 + local_14) == '\0') {
            return local_18;
          }
        }
        local_18 = local_18 + 0x10;
        local_8 = local_8 + -1;
      }
    }
  }
  return 0;
}


// 004eca08

undefined4 FUN_004eca08(void)

{
  undefined1 local_108 [256];
  undefined4 local_8;
  
  if (DAT_00b87eec == 0) {
    if ((DAT_00b87e30 == 4) || (DAT_00b87e98 != 0)) {
      local_8 = FUN_0052adb0(s_Levels_iview_lev_00563280,&DAT_0056327c);
    }
    else if ((DAT_00b87e30 == 5) || (DAT_00b87ea8 != 0)) {
      local_8 = FUN_0052adb0(s_Levels_train_lev_00563298,&DAT_00563294);
    }
    else {
      if (DAT_00c81164 == 0) {
        FUN_0052a910(local_108,s_Levels_Miami_01_lev_005632ac);
      }
      else {
        FUN_0052a910(local_108,s_Levels__s_005632c0,DAT_00c81164);
      }
      local_8 = FUN_0052adb0(local_108,&DAT_005632cc);
    }
  }
  else {
    local_8 = FUN_0052adb0(s_Levels_flat_lev_0056326c,&DAT_00563268);
  }
  return local_8;
}


// 004ecade

undefined4 FUN_004ecade(void)

{
  undefined4 uVar1;
  int local_18;
  undefined4 local_14;
  undefined4 local_10;
  int local_c;
  int local_8;
  
  thunk_FUN_00426580(0xffffffff);
  local_8 = thunk_FUN_004eca08();
  DAT_00b31ed8 = 0;
  if (local_8 == 0) {
    uVar1 = 0;
  }
  else {
    thunk_FUN_004d9596(&local_18,4,1,local_8);
    for (local_c = 0; local_c < local_18; local_c = local_c + 1) {
      uVar1 = FUN_0052b260(local_8);
      thunk_FUN_004d9596(&local_14,4,1,local_8);
      thunk_FUN_004d9596(&local_10,4,1,local_8);
      switch(local_14) {
      case 0:
        thunk_FUN_004eb975(local_8,local_10);
        break;
      case 1:
        thunk_FUN_004eb490(local_8);
        break;
      case 2:
        thunk_FUN_004ed055(local_8);
        break;
      case 4:
        thunk_FUN_004eb811(local_8,local_10);
        break;
      case 5:
        thunk_FUN_004ec280(local_8,local_10);
        break;
      case 6:
        thunk_FUN_004ec2ec(local_8,local_10);
        break;
      case 7:
        thunk_FUN_004ec336(local_8,local_10);
        break;
      case 8:
        thunk_FUN_004ec466(local_8,local_10);
        break;
      case 9:
        thunk_FUN_004ec49a(local_8,local_10);
        break;
      case 10:
        thunk_FUN_004ec4ce(local_8,local_10);
        break;
      case 0xb:
        thunk_FUN_004ec3fd(local_8,local_10);
        break;
      case 0xc:
        thunk_FUN_004ec7ac(local_8,local_10);
        break;
      case 0xd:
        thunk_FUN_004ec58a(local_8,local_10);
        break;
      case 0xe:
        thunk_FUN_004ec7f4(local_8,local_10);
        break;
      case 0xf:
        thunk_FUN_004eb7cf(local_8,local_10);
        break;
      case 0x10:
        thunk_FUN_004ec522(local_8,local_10);
        break;
      case 0x11:
        thunk_FUN_004ec556(local_8,local_10);
        break;
      case 0x12:
        FUN_0052b4f0(local_8,local_10,1);
        break;
      case 0x13:
        thunk_FUN_004eafcf(local_8,local_10);
        break;
      case 0x14:
        thunk_FUN_004a2f77(local_8,local_10,local_14,uVar1);
      }
    }
    FUN_0052aa10(local_8);
    thunk_FUN_00426580(1);
    thunk_FUN_004d7b73();
    thunk_FUN_00516e76();
    thunk_FUN_00501c63();
    thunk_FUN_00501770();
    thunk_FUN_00426caf();
    uVar1 = 1;
  }
  return uVar1;
}


// 004ecda8

void FUN_004ecda8(void)

{
  DAT_00d01268 = thunk_FUN_004d8db4(DAT_00c98ecc * DAT_00c98ecc * 0x10,
                                    s_D__Driver_Game_map_c_005632d0,0x562);
  DAT_00d00208 = thunk_FUN_004d8db4((DAT_00d001e0 + 0x8000) * 0x20,s_D__Driver_Game_map_c_005632e8,
                                    0x563);
  DAT_00ce0f20 = thunk_FUN_004d8db4(0xa0000,s_D__Driver_Game_map_c_00563300,0x564);
  return;
}


// 004ece1a

void FUN_004ece1a(void)

{
  if (DAT_00d01268 != 0) {
    thunk_FUN_004d8f30(DAT_00d01268);
    DAT_00d01268 = 0;
  }
  if (DAT_00d00208 != 0) {
    thunk_FUN_004d8f30(DAT_00d00208);
    DAT_00d00208 = 0;
  }
  if (DAT_00ce0f20 != 0) {
    thunk_FUN_004d8f30(DAT_00ce0f20);
    DAT_00ce0f20 = 0;
  }
  return;
}


// 004ece84

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

int FUN_004ece84(void)

{
  int iVar1;
  int iVar2;
  
  iVar1 = __ftol();
  iVar2 = __ftol();
  return iVar1 + iVar2 * DAT_00562d38;
}


// 004ecee8

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 FUN_004ecee8(undefined4 param_1,int param_2,int param_3,int param_4)

{
  int iVar1;
  int iVar2;
  int iVar3;
  
  iVar1 = __ftol();
  iVar2 = __ftol();
  iVar1 = iVar1 - param_3;
  iVar2 = iVar2 - param_4;
  iVar3 = iVar1;
  if (iVar1 < 0) {
    iVar3 = -iVar1;
  }
  if (iVar3 <= DAT_00cf56b8) {
    iVar3 = iVar2;
    if (iVar2 < 0) {
      iVar3 = -iVar2;
    }
    if (iVar3 <= DAT_00cf56b8) {
      if (*(char *)(param_2 + iVar1 + 0xf + (iVar2 + 0xf) * DAT_00d00258) != '\0') {
        return 1;
      }
      return 0;
    }
  }
  return 0;
}


// 004ecfbd

undefined4 FUN_004ecfbd(int param_1,int param_2,int param_3,int param_4)

{
  int iVar1;
  
  param_3 = param_1 % DAT_00562d38 - param_3;
  param_4 = param_1 / DAT_00562d38 - param_4;
  iVar1 = param_3;
  if (param_3 < 0) {
    iVar1 = -param_3;
  }
  if (iVar1 <= DAT_00cf56b8) {
    iVar1 = param_4;
    if (param_4 < 0) {
      iVar1 = -param_4;
    }
    if (iVar1 <= DAT_00cf56b8) {
      if (*(char *)(param_2 + param_3 + 0xf + (param_4 + 0xf) * DAT_00d00258) != '\0') {
        return 1;
      }
      return 0;
    }
  }
  return 0;
}


// 004ed055

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_004ed055(undefined4 param_1)

{
  float fVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  undefined1 local_58 [2];
  ushort local_56;
  undefined2 uStack_54;
  undefined2 uStack_52;
  undefined4 local_50;
  undefined4 local_4c;
  undefined4 local_48;
  int local_44;
  undefined4 *local_40;
  int local_3c;
  int local_38;
  int local_34;
  int local_30;
  int local_2c;
  undefined4 local_28;
  undefined4 local_24;
  float local_20;
  undefined4 local_1c;
  undefined4 local_18;
  undefined4 local_14;
  int local_10;
  int *local_c;
  float local_8;
  
  local_c = DAT_00d00230;
  DAT_00c1cc74 = 0x3a2ec33e;
  thunk_FUN_004d9596(&local_3c,0x2c,1,param_1);
  DAT_00562d38 = local_3c;
  DAT_00562d3c = local_38;
  DAT_00562d40 = local_34;
  _DAT_00d01274 = local_28;
  _DAT_00c97a28 = local_24;
  DAT_01251a68 = local_20;
  DAT_00cfe6e0 = local_30;
  DAT_00c98ecc = local_2c;
  DAT_00cf56b8 = (int)(45000 / (longlong)local_34);
  DAT_00d00258 = DAT_00cf56b8 * 2 + 1;
  DAT_00d00204 = DAT_00d00258 * DAT_00d00258;
  DAT_00cb8f08 = local_3c / 2;
  DAT_00cf2f9c = local_38 / 2;
  _DAT_00ce0f2c = DAT_00cb8f08 * local_34;
  _DAT_00ce0f30 = DAT_00cf2f9c * local_34;
  DAT_00c1cc70 = local_2c * (local_34 / 0x5dc);
  _DAT_00c1cc60 = _DAT_00546020 / (float)DAT_00c1cc70;
  DAT_00d00250 = local_3c / local_2c;
  DAT_00cb8f04 = local_38 / local_2c;
  thunk_FUN_00526521(local_1c,local_18,local_14);
  DAT_00d001f0 = DAT_005507d0;
  DAT_00d001f4 = DAT_005507d4;
  DAT_00d001f8 = DAT_005507d8;
  DAT_00d001fc = DAT_005507dc;
  DAT_00cb8f00 = DAT_01251a68;
  DAT_00d0024c = DAT_005507dc;
  local_8 = (float)(DAT_00b87e4c << 1) / _DAT_005461f4 + _DAT_00546080;
  DAT_00d00240 = DAT_005507d0 * local_8;
  DAT_00d00244 = DAT_005507d4 * local_8;
  DAT_00d00248 = DAT_005507d8 * local_8;
  DAT_00d01264 = DAT_01251a68 * local_8;
  fVar1 = DAT_00d00240;
  fVar2 = DAT_00d00244;
  fVar3 = DAT_00d00248;
  if (DAT_00b202d8 == 0) {
    if (DAT_00b202dc == 0) {
      fVar4 = DAT_00d01264;
      if ((DAT_00b87e84 == 0) &&
         (fVar1 = DAT_005507d0, fVar2 = DAT_005507d4, fVar3 = DAT_005507d8, fVar4 = DAT_01251a68,
         DAT_00b202e0 != 0)) {
        fVar1 = DAT_005507d0 * _DAT_005469ec;
        fVar2 = DAT_005507d4 * _DAT_005469ec;
        fVar3 = DAT_005507d8 * _DAT_005469ec;
        fVar4 = DAT_01251a68 * _DAT_00546068;
      }
    }
    else {
      DAT_00d17aec = 0;
      fVar1 = DAT_005507d0;
      fVar2 = DAT_005507d4;
      fVar3 = DAT_005507d8;
      fVar4 = DAT_01251a68;
    }
  }
  else {
    DAT_00d17aec = 0;
    fVar4 = DAT_00d01264;
  }
  DAT_01251a68 = fVar4;
  DAT_005507d8 = fVar3;
  DAT_005507d4 = fVar2;
  DAT_005507d0 = fVar1;
  thunk_FUN_004cb619();
  thunk_FUN_004d9596(&DAT_00d001e0,4,1,param_1);
  thunk_FUN_004ecda8();
  local_40 = DAT_00d00208;
  for (local_44 = 0; local_44 < DAT_00d001e0; local_44 = local_44 + 1) {
    thunk_FUN_004d9596(local_58,0x14,1,param_1);
    *local_40 = 0;
    local_40[1] = (uint)local_56;
    local_40[2] = CONCAT22(uStack_52,uStack_54);
    local_40[3] = local_50;
    local_40[4] = local_4c;
    local_40[5] = 0x3f800000;
    local_40[6] = local_48;
    local_40 = local_40 + 8;
  }
  for (local_44 = 0; local_44 < DAT_00cfe6e0; local_44 = local_44 + 1) {
    *(int **)(&DAT_00d012e0 + local_44 * 4) = local_c;
    thunk_FUN_004d9596(&local_10,4,1,param_1);
    *local_c = local_10;
    local_c = local_c + 1;
    if (local_10 != 0) {
      thunk_FUN_004d9596(local_c,4,local_10,param_1);
      local_c = local_c + local_10;
    }
    thunk_FUN_004d9596(&local_10,4,1,param_1);
    *local_c = local_10;
    local_c = local_c + 1;
    thunk_FUN_004d9596(local_c,1,local_10,param_1);
    local_c = (int *)((int)local_c + local_10);
    thunk_FUN_004d9596(&local_10,4,1,param_1);
    *local_c = local_10;
    local_c = local_c + 1;
    if (local_10 != 0) {
      thunk_FUN_004d9596(local_c,0x14,local_10,param_1);
      local_c = local_c + local_10 * 5;
    }
  }
  return;
}


// 004ed5b1

void FUN_004ed5b1(void)

{
  DAT_00d00230 = thunk_FUN_004d8db4(0x300000,s_D__Driver_Game_map_c_00563318,0x6d1);
  return;
}


// 004ed5d2

void FUN_004ed5d2(void)

{
  if (DAT_00d00230 != 0) {
    thunk_FUN_004d8f30(DAT_00d00230);
    DAT_00d00230 = 0;
  }
  return;
}


// 004ed5f8

void FUN_004ed5f8(int param_1,int param_2)

{
  int *piVar1;
  char cVar2;
  ushort uVar3;
  ushort *puVar4;
  int iVar5;
  uint *local_54;
  int local_4c;
  ushort local_48;
  ushort *local_40;
  int local_34;
  ushort *local_2c;
  int local_28;
  undefined4 *local_18;
  uint local_14;
  ushort *local_10;
  uint *local_c;
  
  if ((-1 < param_1) && (param_1 <= DAT_00cfe6e0)) {
    (&DAT_00d00220)[param_2] = param_1;
    iVar5 = **(int **)(&DAT_00d012e0 + param_1 * 4);
    puVar4 = (ushort *)(*(int **)(&DAT_00d012e0 + param_1 * 4) + 1);
    if (iVar5 != 0) {
      local_54 = (uint *)(DAT_00ce0f20 + param_2 * 0x28000);
      local_40 = puVar4;
      local_c = local_54;
      for (local_34 = 0; local_34 < iVar5; local_34 = local_34 + 1) {
        *local_c = (uint)*local_40;
        if (local_40[1] == 0xffff) {
          local_c[1] = 0xffffffff;
        }
        else {
          local_c[1] = (uint)local_40[1];
        }
        local_c = local_c + 2;
        local_40 = local_40 + 2;
      }
      for (local_28 = 0; local_28 < iVar5; local_28 = local_28 + 1) {
        if (DAT_00d001e0 <= (int)*local_54) {
          *local_54 = *local_54 + param_2 * 0x2000;
        }
        if (local_54[1] != 0xffffffff) {
          local_54[1] = local_54[1] + param_2 * 0x5000;
        }
        local_54 = local_54 + 2;
      }
    }
    puVar4 = puVar4 + iVar5 * 2;
    cVar2 = (char)puVar4[2];
    local_10 = (ushort *)((int)puVar4 + 5);
    iVar5 = param_2 * DAT_00c98ecc * DAT_00c98ecc;
    piVar1 = (int *)((int)puVar4 + *(int *)puVar4 + 4);
    if (cVar2 == '\0') {
      for (local_28 = 0; local_28 < DAT_00c98ecc * DAT_00c98ecc; local_28 = local_28 + 1) {
        *(undefined4 *)(DAT_00d01268 + (iVar5 + local_28) * 4) = 0xffffffff;
      }
    }
    else if (cVar2 == '\x01') {
      for (local_28 = 0; local_28 < DAT_00c98ecc * DAT_00c98ecc; local_28 = local_28 + 1) {
        uVar3 = *local_10;
        local_10 = local_10 + 1;
        if (uVar3 == 0xffff) {
          local_4c = -1;
        }
        else {
          local_4c = (uint)uVar3 + param_2 * 0x5000;
        }
        *(int *)(DAT_00d01268 + (iVar5 + local_28) * 4) = local_4c;
      }
    }
    else if (cVar2 == '\x02') {
      local_14 = 0x8000;
      local_48 = *local_10;
      local_10 = (ushort *)((int)puVar4 + 7);
      for (local_28 = 0; local_28 < DAT_00c98ecc * DAT_00c98ecc; local_28 = local_28 + 1) {
        if (((int)(short)local_48 & local_14) == 0) {
          local_4c = -1;
        }
        else {
          uVar3 = *local_10;
          local_10 = local_10 + 1;
          local_4c = (uint)uVar3 + param_2 * 0x5000;
        }
        *(int *)(DAT_00d01268 + (iVar5 + local_28) * 4) = local_4c;
        local_14 = (int)local_14 >> 1;
        if (local_14 == 0) {
          local_14 = 0x8000;
          local_48 = *local_10;
          local_10 = local_10 + 1;
        }
      }
    }
    iVar5 = *piVar1;
    local_2c = (ushort *)(piVar1 + 1);
    if (iVar5 != 0) {
      local_18 = (undefined4 *)(DAT_00d00208 + (DAT_00d001e0 + param_2 * 0x2000) * 0x20);
      for (local_28 = 0; local_28 < iVar5; local_28 = local_28 + 1) {
        *local_18 = DAT_01270c20;
        local_18[1] = *local_2c & 0x7fff;
        local_18[2] = *(undefined4 *)(local_2c + 2);
        local_18[3] = *(undefined4 *)(local_2c + 4);
        local_18[4] = *(undefined4 *)(local_2c + 6);
        local_18[6] = (int)(short)local_2c[8];
        if ((*local_2c & 0x8000) == 0) {
          local_18[7] = 0;
        }
        else {
          local_18[7] = 1;
        }
        local_2c = local_2c + 10;
        local_18 = local_18 + 8;
      }
    }
    *(int *)(&DAT_00c39da0 + param_2 * 4) = param_1;
    iVar5 = ((DAT_00cb8f04 + -1) - (param_1 - param_1 % DAT_00d00250) / DAT_00d00250) * DAT_00d00250
            + param_1 % DAT_00d00250;
    thunk_FUN_0051ab31(iVar5,*(undefined4 *)(&DAT_00c4bdd0 + param_2 * 4));
    thunk_FUN_0051ac05(iVar5,*(undefined4 *)(&DAT_00c1cc80 + param_2 * 4));
  }
  return;
}


// 004edaa2

void FUN_004edaa2(void)

{
  int iVar1;
  bool bVar2;
  uint local_34;
  int aiStack_28 [4];
  undefined4 uStack_18;
  undefined4 uStack_14;
  int local_10;
  uint local_c;
  uint local_8;
  
  local_8 = 0;
  local_c = 0;
  local_34 = 0;
  if (DAT_00cff9b8 < 0x14) {
    bVar2 = DAT_00cff9b0 != 0;
    if (bVar2) {
      aiStack_28[0] = -1;
      aiStack_28[1] = 0;
      local_8 = 1;
    }
    local_34 = (uint)bVar2;
    local_8 = (uint)bVar2;
  }
  else if ((DAT_00c98ecc + -0x14 < DAT_00cff9b8) && (DAT_00cff9b0 < DAT_00562d38 / DAT_00c98ecc)) {
    aiStack_28[0] = 1;
    aiStack_28[1] = 0;
    local_34 = 1;
    local_8 = 2;
  }
  if (DAT_00cff9bc < 0x14) {
    if (DAT_00cff9b4 != 0) {
      aiStack_28[local_34 * 2] = 0;
      aiStack_28[local_34 * 2 + 1] = -1;
      local_34 = local_34 + 1;
      local_c = 1;
    }
    local_c = (uint)(DAT_00cff9b4 != 0);
  }
  else if ((DAT_00c98ecc + -0x14 < DAT_00cff9bc) && (DAT_00cff9b4 != 0)) {
    aiStack_28[local_34 * 2] = 0;
    aiStack_28[local_34 * 2 + 1] = 1;
    local_34 = local_34 + 1;
    local_c = 2;
  }
  if (local_34 == 2) {
    if (local_c == 1) {
      if (local_8 == 1) {
        uStack_18 = 0xffffffff;
        uStack_14 = 0xffffffff;
      }
      else {
        uStack_18 = 1;
        uStack_14 = 0xffffffff;
      }
      uStack_14 = 0xffffffff;
      local_34 = 3;
    }
    else if (local_8 == 1) {
      uStack_18 = 0xffffffff;
      uStack_14 = 1;
      local_34 = 3;
    }
    else {
      uStack_18 = 1;
      uStack_14 = 1;
      local_34 = 3;
    }
  }
  for (local_10 = 0; local_10 < (int)local_34; local_10 = local_10 + 1) {
    iVar1 = DAT_00cff9ac + aiStack_28[local_10 * 2] +
            aiStack_28[local_10 * 2 + 1] * (DAT_00562d38 / DAT_00c98ecc);
    if ((((iVar1 != DAT_00d00220) && (iVar1 != DAT_00d00224)) && (iVar1 != DAT_00d00228)) &&
       (iVar1 != DAT_00d0022c)) {
      thunk_FUN_004ed5f8(iVar1,(DAT_00cff9b0 + aiStack_28[local_10 * 2] & 1U) +
                               (DAT_00cff9b4 + aiStack_28[local_10 * 2 + 1] & 1U) * 2);
    }
  }
  return;
}


// 004edd08

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_004edd08(int param_1)

{
  int iVar1;
  undefined4 *puVar2;
  undefined4 *puVar3;
  
  if (param_1 == 0) {
    DAT_00c97a00 = __ftol();
    DAT_00c97a04 = __ftol();
    DAT_00c97a08 = DAT_00c97a00 + DAT_00c97a04 * DAT_00562d38;
    DAT_00c97a10 = DAT_00c97a00 / DAT_00c98ecc;
    DAT_00c97a14 = DAT_00c97a04 / DAT_00c98ecc;
    DAT_00c97a20 = DAT_00c97a0c;
    DAT_00c97a0c = DAT_00c97a10 + DAT_00c97a14 * (DAT_00562d38 / DAT_00c98ecc);
    DAT_00c97a24 = (byte)DAT_00c97a10 & 1;
    DAT_00c97a25 = (byte)DAT_00c97a14 & 1;
    DAT_00c97a26 = DAT_00c97a24 + DAT_00c97a25 * '\x02';
    DAT_00c97a18 = DAT_00c97a00 - DAT_00c97a10 * DAT_00c98ecc;
    DAT_00c97a1c = DAT_00c97a04 - DAT_00c97a14 * DAT_00c98ecc;
    if (DAT_00b87eec == 0) {
      DAT_00cff9a0 = __ftol();
      DAT_00cff9a4 = __ftol();
      DAT_00cff9a8 = DAT_00cff9a0 + DAT_00cff9a4 * DAT_00562d38;
      DAT_00cff9b0 = DAT_00cff9a0 / DAT_00c98ecc;
      DAT_00cff9b4 = DAT_00cff9a4 / DAT_00c98ecc;
      DAT_00cff9c0 = DAT_00cff9ac;
      DAT_00cff9ac = DAT_00cff9b0 + DAT_00cff9b4 * (DAT_00562d38 / DAT_00c98ecc);
      DAT_00cff9c4 = (byte)DAT_00cff9b0 & 1;
      DAT_00cff9c5 = (byte)DAT_00cff9b4 & 1;
      DAT_00cff9c6 = DAT_00cff9c4 + DAT_00cff9c5 * '\x02';
      DAT_00cff9b8 = DAT_00cff9a0 - DAT_00cff9b0 * DAT_00c98ecc;
      DAT_00cff9bc = DAT_00cff9a4 - DAT_00cff9b4 * DAT_00c98ecc;
    }
    else {
      puVar2 = &DAT_00c97a00;
      puVar3 = &DAT_00cff9a0;
      for (iVar1 = 10; iVar1 != 0; iVar1 = iVar1 + -1) {
        *puVar3 = *puVar2;
        puVar2 = puVar2 + 1;
        puVar3 = puVar3 + 1;
      }
    }
    thunk_FUN_004edaa2();
  }
  else {
    thunk_FUN_00489ed6();
  }
  return;
}


// 004ee065

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_004ee065(void)

{
  PTR_DAT_00562d7c = (undefined *)&DAT_00cfe760;
  DAT_00b31edc = 0;
  DAT_00d022e0 = 0;
  DAT_00b31ee0 = 0;
  DAT_00cf1f60 = 1;
  _DAT_00b31ed0 = 0;
  DAT_00cff9c0 = 0xffffffff;
  DAT_00c97a20 = 0xffffffff;
  _memset(&DAT_00bdcd00,1,0x1200);
  thunk_FUN_004edd08(0);
  thunk_FUN_004edd08(1);
  DAT_00d0022c = 0xffffffff;
  DAT_00d00228 = 0xffffffff;
  DAT_00d00224 = 0xffffffff;
  DAT_00d00220 = 0xffffffff;
  thunk_FUN_004ed5f8(DAT_00cff9ac,DAT_00cff9c6);
  thunk_FUN_004edaa2();
  return;
}


// 004ee129

void FUN_004ee129(void)

{
  DAT_00cff9c0 = 0xffffffff;
  DAT_00c97a20 = 0xffffffff;
  DAT_00d0022c = 0xffffffff;
  DAT_00d00228 = 0xffffffff;
  DAT_00d00224 = 0xffffffff;
  DAT_00d00220 = 0xffffffff;
  thunk_FUN_004ed5f8(DAT_00cff9ac,DAT_00cff9c6);
  thunk_FUN_004edaa2();
  return;
}


// 004ee18b

void FUN_004ee18b(int param_1)

{
  ushort uVar1;
  int iVar2;
  uint uVar3;
  float local_1c;
  float local_18;
  float local_14;
  int local_c;
  uint local_8;
  
  local_c = (&DAT_00cfe7a0)[*(int *)(param_1 + 4)];
  local_8 = (uint)*(ushort *)(local_c + 2);
  iVar2 = thunk_FUN_00428672(param_1 + 8,*(undefined4 *)(local_c + 0xc));
  if (iVar2 != 0) {
    if ((local_8 & 4) == 0) {
      if (((local_8 & 0x4000) == 0) || ((*(uint *)(local_c + 8) & 0x2000) == 0)) {
        if (((local_8 & 0x400) != 0) &&
           ((((*(uint *)(local_c + 8) & 0x80) != 0 &&
             (uVar3 = DAT_00b31edc & 0xf, DAT_00b31edc = DAT_00b31edc + 1, uVar3 == 0)) &&
            ((int)PTR_DAT_00562d7c < 0xcfe7a0)))) {
          *(int *)PTR_DAT_00562d7c = param_1;
          PTR_DAT_00562d7c = PTR_DAT_00562d7c + 4;
        }
      }
      else {
        uVar3 = DAT_00d022e0 & 0xf;
        DAT_00d022e0 = DAT_00d022e0 + 1;
        if ((uVar3 == 0) && ((int)PTR_DAT_00562d7c < 0xcfe7a0)) {
          *(int *)PTR_DAT_00562d7c = param_1;
          PTR_DAT_00562d7c = PTR_DAT_00562d7c + 4;
        }
      }
      local_1c = *(float *)(param_1 + 8) - DAT_00b1c270;
      local_18 = *(float *)(param_1 + 0xc) - DAT_00b1c274;
      local_14 = *(float *)(param_1 + 0x10) - DAT_00b1c278;
      thunk_FUN_00528982(&local_1c);
      uVar1 = *(ushort *)(local_c + 2);
      local_8 = (uint)uVar1;
      if ((uVar1 & 0x80) == 0) {
        if ((((uVar1 & 0x4000) == 0) && ((*(uint *)(param_1 + 0x18) & 0x3ff) == 0)) &&
           ((uVar1 & 0x30) != 0)) {
          if (iVar2 == 1) {
            thunk_FUN_0042982e(local_c,*(undefined4 *)(param_1 + 0x18),&local_1c,0);
          }
          else if (iVar2 == 2) {
            thunk_FUN_0042982e(local_c,*(undefined4 *)(param_1 + 0x18),&local_1c,1);
          }
          else if (*(int *)(&DAT_00cf56fc + *(int *)(param_1 + 4) * 0x20) < 200) {
            thunk_FUN_0042982e(local_c,*(undefined4 *)(param_1 + 0x18),&local_1c,0);
          }
          else {
            thunk_FUN_0042982e(local_c,*(undefined4 *)(param_1 + 0x18),&local_1c,2);
          }
          DAT_00bdc28c = &DAT_011effa0;
        }
        else {
          if (iVar2 == 1) {
            thunk_FUN_00429143(local_c,*(undefined4 *)(param_1 + 0x18),&local_1c,0);
          }
          else if (iVar2 == 2) {
            thunk_FUN_00429143(local_c,*(undefined4 *)(param_1 + 0x18),&local_1c,1);
          }
          else if (*(int *)(&DAT_00cf56fc + *(int *)(param_1 + 4) * 0x20) < 200) {
            thunk_FUN_00429143(local_c,*(undefined4 *)(param_1 + 0x18),&local_1c,0);
          }
          else {
            thunk_FUN_00429143(local_c,*(undefined4 *)(param_1 + 0x18),&local_1c,2);
          }
          DAT_00bdc28c = &DAT_011effa0;
        }
      }
      else {
        if (iVar2 == 2) {
          thunk_FUN_0042a5de(local_c,*(undefined4 *)(param_1 + 0x18),&local_1c,1);
        }
        else {
          thunk_FUN_0042a5de(local_c,*(undefined4 *)(param_1 + 0x18),&local_1c,0);
        }
        DAT_00bdc28c = &DAT_011effa0;
      }
    }
    else {
      thunk_FUN_004fef26(local_c,param_1,iVar2);
      DAT_00bdc28c = &DAT_011effa0;
    }
  }
  return;
}


// 004ee4b7

void FUN_004ee4b7(int param_1)

{
  ushort uVar1;
  int iVar2;
  uint uVar3;
  float local_1c;
  float local_18;
  float local_14;
  int local_c;
  uint local_8;
  
  local_c = (&DAT_00cfe7a0)[*(int *)(param_1 + 4)];
  iVar2 = thunk_FUN_00428672(param_1 + 8,*(undefined4 *)(local_c + 0xc));
  if (iVar2 != 0) {
    uVar1 = *(ushort *)(local_c + 2);
    local_8 = (uint)uVar1;
    if ((uVar1 & 4) == 0) {
      if (((uVar1 & 0x4000) == 0) || ((*(uint *)(local_c + 8) & 0x2000) == 0)) {
        if (((uVar1 & 0x400) != 0) &&
           ((((*(uint *)(local_c + 8) & 0x80) != 0 &&
             (uVar3 = DAT_00b31edc & 0xf, DAT_00b31edc = DAT_00b31edc + 1, uVar3 == 0)) &&
            ((int)PTR_DAT_00562d7c < 0xcfe7a0)))) {
          *(int *)PTR_DAT_00562d7c = param_1;
          PTR_DAT_00562d7c = PTR_DAT_00562d7c + 4;
        }
      }
      else {
        uVar3 = DAT_00d022e0 & 0xf;
        DAT_00d022e0 = DAT_00d022e0 + 1;
        if ((uVar3 == 0) && ((int)PTR_DAT_00562d7c < 0xcfe7a0)) {
          *(int *)PTR_DAT_00562d7c = param_1;
          PTR_DAT_00562d7c = PTR_DAT_00562d7c + 4;
        }
      }
      local_1c = *(float *)(param_1 + 8) - DAT_00b1c270;
      local_18 = *(float *)(param_1 + 0xc) - DAT_00b1c274;
      local_14 = *(float *)(param_1 + 0x10) - DAT_00b1c278;
      thunk_FUN_00528982(&local_1c);
      if ((local_8 & 0x4000) == 0) {
        if ((((local_8 & 0x2000) != 0) || ((local_8 & 0x400) != 0)) &&
           (*(short *)(local_c + 0x16) == 1)) {
          if (iVar2 == 1) {
            thunk_FUN_0042a423(local_c,*(undefined4 *)(param_1 + 0x18),&local_1c,0);
          }
          else if (iVar2 == 2) {
            thunk_FUN_0042a423(local_c,*(undefined4 *)(param_1 + 0x18),&local_1c,1);
          }
          else {
            thunk_FUN_0042a423(local_c,*(undefined4 *)(param_1 + 0x18),&local_1c,0);
          }
          DAT_00bdc28c = &DAT_011effa0;
          return;
        }
        if (((*(uint *)(param_1 + 0x18) & 0x3ff) == 0) && ((local_8 & 0x30) != 0)) {
          if (iVar2 == 1) {
            thunk_FUN_0042982e(local_c,*(undefined4 *)(param_1 + 0x18),&local_1c,0);
          }
          else if (iVar2 == 2) {
            thunk_FUN_0042982e(local_c,*(undefined4 *)(param_1 + 0x18),&local_1c,1);
          }
          else if (*(int *)(&DAT_00cf56fc + *(int *)(param_1 + 4) * 0x20) < 200) {
            thunk_FUN_0042982e(local_c,*(undefined4 *)(param_1 + 0x18),&local_1c,0);
          }
          else {
            thunk_FUN_0042982e(local_c,*(undefined4 *)(param_1 + 0x18),&local_1c,2);
          }
          DAT_00bdc28c = &DAT_011effa0;
          return;
        }
      }
      if (iVar2 == 1) {
        thunk_FUN_00429143(local_c,*(undefined4 *)(param_1 + 0x18),&local_1c,0);
      }
      else if (iVar2 == 2) {
        thunk_FUN_00429143(local_c,*(undefined4 *)(param_1 + 0x18),&local_1c,1);
      }
      else if (*(int *)(&DAT_00cf56fc + *(int *)(param_1 + 4) * 0x20) < 200) {
        thunk_FUN_00429143(local_c,*(undefined4 *)(param_1 + 0x18),&local_1c,0);
      }
      else {
        thunk_FUN_00429143(local_c,*(undefined4 *)(param_1 + 0x18),&local_1c,2);
      }
      DAT_00bdc28c = &DAT_011effa0;
    }
    else {
      thunk_FUN_004fef26(local_c,param_1,iVar2);
      DAT_00bdc28c = &DAT_011effa0;
    }
  }
  return;
}


// 004ee813

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_004ee813(undefined4 param_1,undefined4 param_2,int *param_3,int *param_4)

{
  int iVar1;
  int iVar2;
  
  iVar1 = __ftol();
  *param_3 = iVar1;
  iVar2 = __ftol();
  *param_4 = iVar2;
  thunk_FUN_004ef793(iVar1 / DAT_00c98ecc + (iVar2 / DAT_00c98ecc) * (DAT_00562d38 / DAT_00c98ecc),
                     (iVar2 - (iVar2 / DAT_00c98ecc) * DAT_00c98ecc) * DAT_00c98ecc +
                     (iVar1 - (iVar1 / DAT_00c98ecc) * DAT_00c98ecc),param_2);
  return;
}


// 004ee8f4

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_004ee8f4(int param_1)

{
  int *piVar1;
  int iVar2;
  undefined4 uVar3;
  short *psVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  int *piVar8;
  int local_60;
  int local_58;
  undefined *local_48;
  int local_40;
  int local_3c;
  int local_28;
  int local_24;
  int local_1c;
  int local_8;
  
  DAT_00d022e0 = 0;
  if ((param_1 != 0) && (thunk_FUN_00428928(), DAT_00b87eec == 0)) {
    thunk_FUN_00426580(1);
  }
  thunk_FUN_004edd08(param_1);
  thunk_FUN_004ef793(DAT_00c97a0c,
                     (DAT_00c97a04 % DAT_00c98ecc) * DAT_00c98ecc + DAT_00c97a00 % DAT_00c98ecc,
                     &DAT_00cf2fa0);
  iVar6 = DAT_00c97a00;
  if (param_1 != 0) {
    psVar4 = (short *)(DAT_00cf2f84 +
                      ((int)((int)DAT_00b1c26a + ((int)DAT_00b1c26a >> 0x1f & 0xfU)) >> 4) * 0x80);
    iVar7 = DAT_00c97a00 + -0xf;
    local_60 = DAT_00c97a04 + -0xf + (int)*psVar4;
    DAT_00d00218 = 0;
    DAT_00d022e4 = 0;
    DAT_00ce0f24 = 0;
    DAT_00cf2f88 = 0;
    DAT_00cfe6e4 = 0;
    DAT_00c97a25 = (byte)(local_60 / DAT_00c98ecc);
    local_1c = local_60 - (local_60 / DAT_00c98ecc & 0xffU) * DAT_00c98ecc;
    iVar5 = DAT_00c98ecc * DAT_00c98ecc;
    local_3c = (int)*psVar4;
    iVar2 = local_3c + psVar4[1];
    local_48 = &DAT_00cf2fa0 + local_3c * DAT_00d00258;
    DAT_00bdc28c = &DAT_011effa0;
    if (DAT_01137324 == '\x06') {
      local_60 = DAT_00c97a04 + -0xf;
      DAT_00c97a25 = (byte)(local_60 / DAT_00c98ecc);
      local_1c = local_60 - (local_60 / DAT_00c98ecc & 0xffU) * DAT_00c98ecc;
      for (local_3c = -0xf; local_3c < 0xf; local_3c = local_3c + 1) {
        for (local_24 = -0xf; local_24 < 0xf; local_24 = local_24 + 1) {
          iVar7 = local_24 + iVar6;
          DAT_00c97a24 = (byte)(iVar7 / DAT_00c98ecc);
          iVar2 = iVar7 - (iVar7 / DAT_00c98ecc & 0xffU) * DAT_00c98ecc;
          if ((((-1 < iVar7) && (-1 < local_60)) && (iVar7 < DAT_00562d38)) &&
             (local_60 < DAT_00562d3c)) {
            DAT_00c97a26 = (DAT_00c97a24 & 1) + (DAT_00c97a25 & 1) * '\x02';
            local_58 = *(int *)(DAT_00d01268 +
                               ((uint)DAT_00c97a26 * iVar5 + iVar2 + local_1c * DAT_00c98ecc) * 4);
            while (local_58 != -1) {
              piVar1 = (int *)(DAT_00ce0f20 + local_58 * 8);
              piVar8 = (int *)(DAT_00d00208 + *piVar1 * 0x20);
              if ((*piVar8 != DAT_01270c30) && (piVar8[7] == 0)) {
                if (*(int *)(&DAT_00bdcd00 + piVar8[1] * 4) != 0) {
                  switch((&DAT_00c98a40)[piVar8[1]]) {
                  case 1:
                    thunk_FUN_004ee4b7(piVar8);
                    break;
                  case 2:
                    if (DAT_00cf2f88 < 0x400) {
                      (&DAT_00ce0f40)[DAT_00cf2f88] = piVar8;
                      DAT_00cf2f88 = DAT_00cf2f88 + 1;
                    }
                    break;
                  case 3:
                    if (DAT_00cfe6e4 < 0x400) {
                      *(int **)(&DAT_00c97a40 + DAT_00cfe6e4 * 4) = piVar8;
                      DAT_00cfe6e4 = DAT_00cfe6e4 + 1;
                    }
                    break;
                  case 4:
                    if (DAT_00ce0f24 < 0x400) {
                      *(int **)(&DAT_00cf1f80 + DAT_00ce0f24 * 4) = piVar8;
                      DAT_00ce0f24 = DAT_00ce0f24 + 1;
                    }
                    break;
                  case 5:
                    if (DAT_00575ee8 != 0) {
                      thunk_FUN_004ee4b7(piVar8);
                    }
                    break;
                  case 6:
                    if (DAT_00d022e4 < 0x400) {
                      (&DAT_00d00260)[DAT_00d022e4] = piVar8;
                      DAT_00d022e4 = DAT_00d022e4 + 1;
                    }
                    break;
                  case 7:
                    if (DAT_00d00218 < 0x200) {
                      *(int **)(&DAT_00cff9e0 + DAT_00d00218 * 4) = piVar8;
                      DAT_00d00218 = DAT_00d00218 + 1;
                    }
                  }
                }
                *piVar8 = DAT_01270c30;
              }
              local_58 = piVar1[1];
            }
          }
          if (iVar2 + 1 == DAT_00c98ecc) {
            DAT_00c97a24 = DAT_00c97a24 + 1;
          }
        }
        local_1c = local_1c + 1;
        if (local_1c == DAT_00c98ecc) {
          local_1c = 0;
          DAT_00c97a25 = DAT_00c97a25 + 1;
        }
        local_60 = local_60 + 1;
      }
    }
    else {
      for (; local_3c < iVar2; local_3c = local_3c + 1) {
        local_24 = (int)psVar4[local_3c * 2 + 2];
        if (local_24 != -1) {
          local_40 = local_24 + iVar7;
          iVar6 = local_24 + psVar4[local_3c * 2 + 3];
          DAT_00c97a24 = (byte)(local_40 / DAT_00c98ecc);
          local_8 = local_40 - (local_40 / DAT_00c98ecc & 0xffU) * DAT_00c98ecc;
          for (; local_24 < iVar6; local_24 = local_24 + 1) {
            if ((((-1 < local_40) && (-1 < local_60)) && (local_40 < DAT_00562d38)) &&
               ((local_60 < DAT_00562d3c && (local_48[local_24] != '\0')))) {
              DAT_00c97a26 = (DAT_00c97a24 & 1) + (DAT_00c97a25 & 1) * '\x02';
              local_58 = *(int *)(DAT_00d01268 +
                                 ((uint)DAT_00c97a26 * iVar5 + local_8 + local_1c * DAT_00c98ecc) *
                                 4);
              while (local_58 != -1) {
                piVar1 = (int *)(DAT_00ce0f20 + local_58 * 8);
                piVar8 = (int *)(DAT_00d00208 + *piVar1 * 0x20);
                if ((*piVar8 != DAT_01270c30) && (piVar8[7] == 0)) {
                  if (*(int *)(&DAT_00bdcd00 + piVar8[1] * 4) != 0) {
                    switch((&DAT_00c98a40)[piVar8[1]]) {
                    case 1:
                      thunk_FUN_004ee4b7(piVar8);
                      break;
                    case 2:
                      (&DAT_00ce0f40)[DAT_00cf2f88] = piVar8;
                      DAT_00cf2f88 = DAT_00cf2f88 + 1;
                      break;
                    case 3:
                      *(int **)(&DAT_00c97a40 + DAT_00cfe6e4 * 4) = piVar8;
                      DAT_00cfe6e4 = DAT_00cfe6e4 + 1;
                      break;
                    case 4:
                      *(int **)(&DAT_00cf1f80 + DAT_00ce0f24 * 4) = piVar8;
                      DAT_00ce0f24 = DAT_00ce0f24 + 1;
                      break;
                    case 5:
                      if (DAT_00575ee8 != 0) {
                        thunk_FUN_004ee4b7(piVar8);
                      }
                      break;
                    case 6:
                      (&DAT_00d00260)[DAT_00d022e4] = piVar8;
                      DAT_00d022e4 = DAT_00d022e4 + 1;
                      break;
                    case 7:
                      *(int **)(&DAT_00cff9e0 + DAT_00d00218 * 4) = piVar8;
                      DAT_00d00218 = DAT_00d00218 + 1;
                    }
                  }
                  *piVar8 = DAT_01270c30;
                }
                local_58 = piVar1[1];
              }
            }
            local_8 = local_8 + 1;
            if (local_8 == DAT_00c98ecc) {
              local_8 = 0;
              DAT_00c97a24 = DAT_00c97a24 + 1;
            }
            local_40 = local_40 + 1;
          }
        }
        local_1c = local_1c + 1;
        if (local_1c == DAT_00c98ecc) {
          local_1c = 0;
          DAT_00c97a25 = DAT_00c97a25 + 1;
        }
        local_48 = local_48 + DAT_00d00258;
        local_60 = local_60 + 1;
      }
    }
    uVar3 = DAT_01252b74;
    if (DAT_00d00218 != 0) {
      thunk_FUN_00426580(0x13);
      for (local_28 = 0; local_28 < DAT_00d00218; local_28 = local_28 + 1) {
        thunk_FUN_004ee4b7(*(undefined4 *)(&DAT_00cff9e0 + local_28 * 4));
      }
      thunk_FUN_00426580(uVar3);
    }
    if (DAT_00ce0f24 != 0) {
      DAT_01270c34 = 0xffffffff;
      DAT_0125f3e4 = 0xff;
      DAT_01252b78 = 0xffffffff;
      (*DAT_01270dcc)(3,8,0,1,1);
      (*DAT_01270d68)(4);
      DAT_01252b78 = 1;
      for (local_28 = 0; local_28 < DAT_00ce0f24; local_28 = local_28 + 1) {
        thunk_FUN_004ee18b(*(undefined4 *)(&DAT_00cf1f80 + local_28 * 4));
      }
    }
    if (((DAT_00d11880 != 0) && (DAT_00cfe6e4 != 0)) &&
       ((DAT_00b87e84 == 0 && (DAT_00b20300 == '\0')))) {
      DAT_01270c34 = 0xffffffff;
      DAT_0125f3e4 = 0xff;
      DAT_01252b78 = 0xffffffff;
      (*DAT_01270dcc)(4,8,1,1,1);
      (*DAT_01270d68)(7);
      DAT_01252b78 = 2;
      uVar3 = thunk_FUN_0042655a(0);
      for (local_28 = 0; local_28 < DAT_00cfe6e4; local_28 = local_28 + 1) {
        *(float *)(*(int *)(&DAT_00c97a40 + local_28 * 4) + 0xc) =
             *(float *)(*(int *)(&DAT_00c97a40 + local_28 * 4) + 0xc) - _DAT_005461ac;
        thunk_FUN_004ee18b(*(undefined4 *)(&DAT_00c97a40 + local_28 * 4));
        *(float *)(*(int *)(&DAT_00c97a40 + local_28 * 4) + 0xc) =
             *(float *)(*(int *)(&DAT_00c97a40 + local_28 * 4) + 0xc) + _DAT_005461ac;
      }
      thunk_FUN_0042655a(uVar3);
    }
    if (DAT_01252b78 != 0) {
      (*DAT_01270dcc)(3,8,0,2,1);
      (*DAT_01270d68)(7);
      DAT_01252b78 = 0;
    }
  }
  return;
}


// 004ef309

void FUN_004ef309(void)

{
  undefined4 uVar1;
  undefined4 *local_c;
  int local_8;
  
  if (DAT_00cf2f88 != 0) {
    DAT_00bdc28c = &DAT_011effa0;
    local_8 = DAT_00cf2f88;
    local_c = &DAT_00ce0f40;
    while (local_8 != 0) {
      uVar1 = *local_c;
      local_c = local_c + 1;
      thunk_FUN_004ee18b(uVar1);
      local_8 = local_8 + -1;
    }
  }
  return;
}


// 004ef364

void FUN_004ef364(void)

{
  undefined4 uVar1;
  undefined4 *local_c;
  int local_8;
  
  if (DAT_00d022e4 != 0) {
    DAT_00bdc28c = &DAT_011effa0;
    local_8 = DAT_00d022e4;
    local_c = &DAT_00d00260;
    DAT_00b1c38c = 2;
    while (local_8 != 0) {
      uVar1 = *local_c;
      local_c = local_c + 1;
      thunk_FUN_004ee18b(uVar1);
      local_8 = local_8 + -1;
    }
    DAT_00b1c38c = 0;
  }
  return;
}


// 004ef3cd

void FUN_004ef3cd(void)

{
  int iVar1;
  int iVar2;
  uint local_20;
  int local_1c;
  int local_10;
  int local_8;
  
  thunk_FUN_00427a08(DAT_00cfe7a0,0x3fd9999a,0x3fd9999a,0x3fd9999a);
  thunk_FUN_00427a08(DAT_00cfe7a4,0x3fd9999a,0x3fd9999a,0x3fd9999a);
  thunk_FUN_00427a08(DAT_00cfe7a8,0x3fd9999a,0x3fd9999a,0x3fd9999a);
  thunk_FUN_00427a08(DAT_00cfe7ac,0x3fd9999a,0x3fd9999a,0x3fd9999a);
  thunk_FUN_00427a71(DAT_00cfe7a0,0x3fd9999a);
  thunk_FUN_00427a71(DAT_00cfe7a4,0x3fd9999a);
  thunk_FUN_00427a71(DAT_00cfe7a8,0x3fd9999a);
  thunk_FUN_00427a71(DAT_00cfe7ac,0x3fd9999a);
  if (DAT_00b87e30 < 4) {
    local_8 = DAT_00b87e30 * 10;
    if ((DAT_00b202d8 == 0) && (DAT_00b202dc == 0)) {
      local_10 = local_8 + DAT_00b202e0 * 4 + DAT_00b87e84 * 2;
    }
    else {
      local_10 = local_8 + 8;
    }
    if (local_10 != local_8) {
      local_1c = 0;
      for (; (local_1c < 2 && ((&PTR_s_PCSKY_00562e28)[local_10] != (undefined *)0x0));
          local_10 = local_10 + 1) {
        iVar1 = thunk_FUN_004ec91e((&PTR_s_PCSKY_00562e28)[local_8]);
        local_20 = (uint)*(byte *)(iVar1 + 8);
        iVar2 = thunk_FUN_004ec91e((&PTR_s_PCSKY_00562e28)[local_10]);
        if (iVar2 == 0) {
          return;
        }
        if (DAT_00c82530 == 0) {
          thunk_FUN_004c1749(*(undefined4 *)(&DAT_01145a64 + (uint)*(byte *)(iVar2 + 8) * 0x10),
                             *(undefined1 *)(iVar2 + 9),*(undefined1 *)(iVar2 + 10),
                             *(byte *)(iVar2 + 0xb) + 1,*(byte *)(iVar2 + 0xc) + 1,
                             *(undefined4 *)(&DAT_01145a64 + local_20 * 0x10),
                             *(undefined1 *)(iVar1 + 9),*(undefined1 *)(iVar1 + 10));
        }
        else {
          thunk_FUN_004c16d9(*(undefined4 *)(&DAT_01145a64 + (uint)*(byte *)(iVar2 + 8) * 0x10),
                             *(undefined1 *)(iVar2 + 9),*(undefined1 *)(iVar2 + 10),
                             *(byte *)(iVar2 + 0xb) + 1,*(byte *)(iVar2 + 0xc) + 1,
                             *(undefined4 *)(&DAT_01145a64 + local_20 * 0x10),
                             *(undefined1 *)(iVar1 + 9),*(undefined1 *)(iVar1 + 10));
        }
        local_8 = local_8 + 1;
        local_1c = local_1c + 1;
      }
      if (local_1c != 0) {
        thunk_FUN_0048a46b(local_20,*(undefined4 *)(&DAT_01145a64 + local_20 * 0x10));
      }
    }
  }
  return;
}


// 004ef66a

void FUN_004ef66a(void)

{
  undefined4 uVar1;
  undefined4 local_1c;
  undefined4 local_18;
  undefined4 local_14;
  undefined4 local_10;
  int local_c;
  int local_8;
  
  local_1c = 0;
  local_18 = 0x42200000;
  local_14 = 0x42100000;
  local_10 = 0;
  if ((DAT_00b202d8 == 0) && (DAT_00b202dc == 0)) {
    local_c = DAT_00b87e84 + DAT_00b202e0 * 2;
  }
  else {
    local_c = 4;
  }
  thunk_FUN_00426580(*(undefined4 *)(DAT_00b87e30 * 0x14 + 0x562d9c + local_c * 4));
  DAT_00bdc28c = &DAT_011effa0;
  thunk_FUN_00528982(&local_1c);
  local_8 = DAT_00b1c280 + DAT_00cf2f80 * 0x40;
  DAT_0125f400 = 0;
  uVar1 = thunk_FUN_0042655a(0);
  (*DAT_01270e20)(0x7fff,uVar1);
  thunk_FUN_00428b69(DAT_00cfe7a0,local_8,&local_1c,1);
  thunk_FUN_00428b69(DAT_00cfe7a4,local_8,&local_1c,1);
  thunk_FUN_00428b69(DAT_00cfe7a8,local_8,&local_1c,1);
  thunk_FUN_00428b69(DAT_00cfe7ac,local_8,&local_1c,1);
  (*DAT_01270e20)(0);
  thunk_FUN_0042655a(uVar1);
  return;
}


// 004ef793

void FUN_004ef793(int param_1,int param_2,byte *param_3)

{
  byte *pbVar1;
  byte bVar2;
  byte bVar3;
  uint local_1c;
  int local_18;
  byte *local_10;
  int local_8;
  
  if (DAT_00b31ee4 == 0) {
    for (local_18 = 0; local_18 < (int)DAT_00d00204; local_18 = local_18 + 1) {
      *param_3 = 1;
      param_3 = param_3 + 1;
    }
  }
  else {
    pbVar1 = (byte *)(DAT_00b31ee4 + *(int *)(DAT_00b31ee4 + 0x10 + param_1 * 4));
    local_10 = pbVar1 + (*(uint *)(pbVar1 + param_2 * 4) & 0x3fffffff);
    if (local_10 == pbVar1) {
      thunk_FUN_004ef997(param_3);
    }
    else {
      local_1c = DAT_00d00204;
      if ((DAT_00d00204 & 7) != 0) {
        local_1c = DAT_00d00204 + 1;
      }
      while (local_1c != 0) {
        bVar2 = *local_10;
        pbVar1 = local_10 + 1;
        local_1c = local_1c + (uint)bVar2 * -8;
        for (; bVar2 != 0; bVar2 = bVar2 - 1) {
          *param_3 = 1;
          param_3[1] = 1;
          param_3[2] = 1;
          param_3[3] = 1;
          param_3[4] = 1;
          param_3[5] = 1;
          param_3[6] = 1;
          param_3[7] = 1;
          param_3 = param_3 + 8;
        }
        if (local_1c == 0) {
          return;
        }
        local_10 = local_10 + 2;
        for (bVar2 = *pbVar1; bVar2 != 0; bVar2 = bVar2 - 1) {
          bVar3 = *local_10;
          local_10 = local_10 + 1;
          for (local_8 = 0; local_8 < 8; local_8 = local_8 + 1) {
            *param_3 = bVar3 & 1;
            param_3 = param_3 + 1;
            local_1c = local_1c - 1;
            if (local_1c == 0) break;
            bVar3 = bVar3 >> 1;
          }
        }
      }
    }
  }
  return;
}


// 004ef997

void FUN_004ef997(undefined1 *param_1)

{
  int local_8;
  
  for (local_8 = 0; local_8 < DAT_00d00204; local_8 = local_8 + 1) {
    *param_1 = 1;
    param_1 = param_1 + 1;
  }
  return;
}


// 004ef9cd

void __fastcall FUN_004ef9cd(undefined4 param_1)

{
  int iVar1;
  
  thunk_FUN_004bf2a0(s_____Loading_cosmetics_data_____00563408,param_1);
  iVar1 = FUN_0052adb0((&PTR_s_LEVELS_MIAMI_01_COS_00562d60)[DAT_00b87e30],&DAT_00563428);
  if (iVar1 == 0) {
    thunk_FUN_004bf2a0(s_XXX_Cosmetics_data_failed_to_loa_0056344c);
  }
  else {
    FUN_0052aaf0(&DAT_00d0cc60,0x1110,1,iVar1);
    FUN_0052aa10(iVar1);
    thunk_FUN_004bf2a0(s_____Cosmetics_data_loaded_____0056342c);
  }
  thunk_FUN_004bf2a0(s_____Loading_denting_data_____00563470);
  if (DAT_00b87e30 == 6) {
    iVar1 = FUN_0052adb0(s_LEVELS_NC_01_DEN_00563494,&DAT_00563490);
  }
  else {
    iVar1 = FUN_0052adb0(s_LEVELS_miami_01_DEN_005634ac,&DAT_005634a8);
  }
  if (iVar1 == 0) {
    thunk_FUN_004bf2a0(s_XXX_Dentings_data_failed_to_load_005634e0);
  }
  else {
    FUN_0052aaf0(&DAT_00559074,0x1680,1,iVar1);
    FUN_0052aaf0(&DAT_0055a6f4,0x1140,1,iVar1);
    FUN_0052aaf0(&DAT_0055b834,0x1140,1,iVar1);
    FUN_0052aa10(iVar1);
    thunk_FUN_004bf2a0(s_____Dentings_data_loaded_____005634c0);
  }
  return;
}


// 004efafd

void FUN_004efafd(undefined4 param_1)

{
  int iVar1;
  undefined4 uVar2;
  int local_c;
  int local_8;
  
  iVar1 = FUN_0052adb0(param_1,&DAT_00563504);
  if (iVar1 != 0) {
    FUN_0052aaf0(&DAT_00b31eec,1,4,iVar1);
    DAT_00b31ee8 = thunk_FUN_004d8db4(DAT_00b31eec * 0xc,s_D__Driver_Game_map_c_00563508,0xd88);
    local_c = DAT_00b31ee8;
    for (local_8 = 0; local_8 < DAT_00b31eec; local_8 = local_8 + 1) {
      FUN_0052aaf0(local_c,1,4,iVar1);
      FUN_0052aaf0(local_c + 8,1,4,iVar1);
      uVar2 = thunk_FUN_004d8db4(*(int *)(local_c + 8) << 2,s_D__Driver_Game_map_c_00563520,0xd8e);
      *(undefined4 *)(local_c + 4) = uVar2;
      FUN_0052aaf0(*(undefined4 *)(local_c + 4),*(undefined4 *)(local_c + 8),4,iVar1);
      local_c = local_c + 0xc;
    }
    FUN_0052aa10(iVar1);
  }
  return;
}


