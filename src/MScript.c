/* Driver PC (1999) — модуль MScript, псевдо-C из Ghidra. 49 функций */

// 004f4596

/* WARNING: Removing unreachable block (ram,0x004f4716) */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

int FUN_004f4596(undefined4 param_1)

{
  int iVar1;
  undefined4 uVar2;
  int iVar3;
  
  _memset(&DAT_00c810c0,0,0x210);
  _memset(&DAT_00c818a0,0,0x18);
  _memset(&DAT_011342a0,0,0x48);
  _memset(&DAT_00c818c0,0,200);
  _memset(&DAT_00c80f80,0,0x14);
  DAT_00c812b8 = &DAT_011342a0;
  DAT_00c812bc = &DAT_00c818a0;
  thunk_FUN_004f638d();
  thunk_FUN_004f892a();
  _DAT_00c8168c = 0;
  DAT_00c82504 = 0;
  DAT_00c81684 = thunk_FUN_004d8db4(0x400,s_D__Driver_Game_MScript_c_0056edac,0x149);
  if (DAT_00c81684 == 0) {
    iVar1 = 3;
  }
  else {
    iVar1 = FUN_0052adb0(param_1,&DAT_0056edc8);
    if (iVar1 == 0) {
      iVar1 = 5;
    }
    else {
      uVar2 = thunk_FUN_004d3000(iVar1);
      DAT_00c80eec = 0;
      DAT_00c80c54 = 0;
      while (iVar3 = FUN_0052c000(DAT_00c81684,0x400,iVar1,iVar1,uVar2), iVar3 != 0) {
        iVar3 = thunk_FUN_004f621d();
        if ((iVar3 != 0) && (iVar3 != 10)) {
          FUN_0052aa10(iVar1);
          return iVar3;
        }
        DAT_00c80c54 = DAT_00c80c54 + 1;
      }
      FUN_0052aa10(iVar1);
      iVar1 = 4;
    }
  }
  return iVar1;
}


// 004f472b

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_004f472b(void)

{
  int iVar1;
  undefined4 *puVar2;
  undefined4 *puVar3;
  
  if (DAT_00c81270 != 0) {
    _DAT_00c814bc = DAT_00d078dc;
    _DAT_00c814c0 = DAT_00d078e0;
    _DAT_00c814c4 = DAT_00d078e4;
    _DAT_00c814c8 = DAT_00d078e8;
    _DAT_00c814cc = DAT_00d078ec;
    _DAT_00c814d0 = DAT_00d078f0;
    _DAT_00c814d4 = DAT_00d078f8;
    _DAT_00c814dc = DAT_00d078c0;
    _DAT_00c814d8 = DAT_00d11a5c;
    thunk_FUN_004f4f10();
    if (DAT_00d14ee4 != 0) {
      thunk_FUN_004cac86();
    }
    if (DAT_00c810c4 != 0xff0) {
      thunk_FUN_004f5012();
    }
    if (DAT_00b87eb0 == 0) {
      DAT_00c814a0 = (float)DAT_00d07888;
      _DAT_00c814a8 = (float)DAT_00d07890;
    }
    else if (DAT_011426e4 == 0) {
      puVar2 = &DAT_00c814a0;
      puVar3 = &DAT_00c816c0;
      for (iVar1 = 0x10; iVar1 != 0; iVar1 = iVar1 + -1) {
        *puVar3 = *puVar2;
        puVar2 = puVar2 + 1;
        puVar3 = puVar3 + 1;
      }
      if (DAT_00c81760 != 0) {
        DAT_00c81760 = 0;
        DAT_00c812d0 = (float)DAT_00d07888;
        DAT_00c812d8 = (float)DAT_00d07890;
      }
      DAT_00ba52d0 = (int)ROUND(DAT_00c812d0);
      iVar1 = DAT_00ba52d0 - DAT_00d0cbd0;
      DAT_00ba52d0 = (int)ROUND(DAT_00c812d8);
      if (4000000 < iVar1 * iVar1 + (DAT_00ba52d0 - DAT_00d0cbd8) * (DAT_00ba52d0 - DAT_00d0cbd8)) {
        DAT_00c814a0 = DAT_00c812d0;
        _DAT_00c814a8 = DAT_00c812d8;
        DAT_00c81760 = 1;
      }
    }
    if (((DAT_00c8175c == 0) || (DAT_00c81688 == 0)) || (DAT_00b5a778 != 0)) {
      if (DAT_00c810c4 == 0xff0) {
        thunk_FUN_004f5951();
      }
      else if (DAT_00c810a4 < DAT_00bdf984) {
        DAT_00c810c4 = 0xff0;
        DAT_00c810e8 = 2;
        DAT_00c81100 = 0x5a;
        DAT_00c810cc = 0;
      }
    }
    else {
      do {
        if ((DAT_00c81688 <= DAT_00c80eec) || (DAT_00c810c4 == 0xff0)) break;
        iVar1 = thunk_FUN_004f8e0c(*(undefined4 *)(DAT_00c8175c + DAT_00c80eec * 4));
      } while (iVar1 != 0xd);
      if (DAT_00c810c4 != 0xff0) {
        thunk_FUN_004a3808(DAT_00c812b8);
        thunk_FUN_004f5afe(DAT_00c812bc);
        thunk_FUN_004f51b4(&DAT_00c810c0);
        if ((DAT_00c810c4 & 0x8000) != 0) {
          thunk_FUN_004f5a57();
        }
        if (DAT_00c810d0 != 0) {
          DAT_00c810d0 = DAT_00c810d0 + -1;
        }
        if (((DAT_00c810d8 & 4) != 0) && (DAT_00c810a4 < DAT_00bdf984)) {
          DAT_00c810c4 = 0xff0;
          DAT_00c810e8 = 2;
          DAT_00c81100 = 0x5a;
        }
        if (DAT_00c810c4 == 0xff0) {
          DAT_00c810cc = 0;
        }
      }
      if (DAT_00c810c4 == 0xff0) {
        thunk_FUN_004f5951();
      }
      thunk_FUN_004f5d67();
    }
  }
  return;
}


// 004f4a33

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_004f4a33(void)

{
  int iVar1;
  int local_10;
  int local_c;
  
  iVar1 = DAT_00c812bc;
  local_c = 0;
  if (DAT_00c81270 != 0) {
    thunk_FUN_004f60b7();
    thunk_FUN_00426580(0x18);
    thunk_FUN_00516eb4(0xff,0xff,0xff);
    if ((iVar1 != 0) && ((*(uint *)(iVar1 + 4) & 4) != 0)) {
      thunk_FUN_004fba23(iVar1);
    }
    if (DAT_00c810c4 == 0xff0) {
      switch(DAT_00c810e8) {
      case 1:
        local_10 = thunk_FUN_004f64dd(s_FAILEDMESSAGE_0056edcc);
        if (_DAT_00c80f60 != -1) {
          thunk_FUN_004f8acc(_DAT_00c80f60 + 0xf000);
        }
        _DAT_00c80f60 = -1;
        break;
      case 2:
        local_10 = thunk_FUN_004f64dd(s_SMASHEDMESSAGE_0056eddc);
        if (iRam00c80f64 != -1) {
          thunk_FUN_004f8acc(iRam00c80f64 + 0xf000);
        }
        iRam00c80f64 = -1;
        break;
      case 3:
        local_10 = thunk_FUN_004f64dd(s_OUTOFRANGEMESSAGE_0056edec);
        if (iRam00c80f68 != -1) {
          thunk_FUN_004f8acc(iRam00c80f68 + 0xf000);
        }
        iRam00c80f68 = -1;
        break;
      case 4:
        local_10 = thunk_FUN_004f64dd(s_CARGOTAWAYMESSAGE_0056ee00);
        if (iRam00c80f6c != -1) {
          thunk_FUN_004f8acc(iRam00c80f6c + 0xf000);
        }
        iRam00c80f6c = -1;
        break;
      default:
        local_10 = -1;
      }
      if ((-1 < local_10) && ((&DAT_0056dc34)[local_10 * 0xc] != 0)) {
        thunk_FUN_004fbbc5((&DAT_0056dc34)[local_10 * 0xc]);
        local_c = 1;
      }
    }
    else {
      local_c = thunk_FUN_004f4d3c();
    }
    if ((local_c == 0) && (DAT_00c810d0 != 0)) {
      thunk_FUN_004fbbc5(&DAT_00c81168);
    }
    thunk_FUN_004f5d98();
  }
  return;
}


// 004f4c3d

int FUN_004f4c3d(void)

{
  int iVar1;
  int iVar2;
  int iVar3;
  int local_38;
  int local_10;
  int local_c;
  undefined *local_8;
  
  local_8 = &DAT_00c80ce0;
  local_10 = 0x7fffffff;
  local_c = 10;
  while (local_c != 0) {
    if ((*(uint *)(local_8 + 0x10) & 1) != 0) {
      iVar3 = *(int *)(local_8 + 0x14) - DAT_00d07888;
      local_38 = *(int *)(local_8 + 0x1c) - DAT_00d07890;
      iVar1 = iVar3;
      if (iVar3 < 0) {
        iVar1 = -iVar3;
      }
      iVar2 = local_38;
      if (local_38 < 0) {
        iVar2 = -local_38;
      }
      if (iVar1 < iVar2) {
        if (local_38 < 0) {
          local_38 = -local_38;
        }
        if (iVar3 < 0) {
          iVar3 = -iVar3;
        }
        local_38 = local_38 + iVar3 / 2;
      }
      else {
        if (iVar3 < 0) {
          iVar3 = -iVar3;
        }
        if (local_38 < 0) {
          local_38 = -local_38;
        }
        local_38 = iVar3 + local_38 / 2;
      }
      if (local_38 < local_10) {
        local_10 = local_38;
      }
    }
    local_8 = local_8 + 0x34;
    local_c = local_c + -1;
  }
  return local_10;
}


// 004f4d3c

undefined4 FUN_004f4d3c(void)

{
  int iVar1;
  undefined *puVar2;
  undefined4 uVar3;
  int local_c;
  
  if ((DAT_00b87ea0 == 0) && (DAT_00b87e98 == 0)) {
    uVar3 = 0;
    puVar2 = &DAT_00c80ce0;
    local_c = 10;
    while (local_c != 0) {
      if ((*(uint *)(puVar2 + 0x10) & 1) != 0) {
        if ((*(uint *)(puVar2 + 0x10) & 2) != 0) {
          iVar1 = thunk_FUN_004f64dd(s_WINDOWMESSAGE_0056ee14,puVar2,uVar3);
          if (DAT_00c80f74 != -1) {
            thunk_FUN_004f8acc(DAT_00c80f74 + 0xf000);
          }
          DAT_00c80f74 = -1;
          if ((-1 < iVar1) && ((&DAT_0056dc34)[iVar1 * 0xc] != 0)) {
            thunk_FUN_004fbbc5((&DAT_0056dc34)[iVar1 * 0xc]);
            return 1;
          }
        }
        if (((*(uint *)(puVar2 + 0x10) & 4) != 0) && ((*(uint *)(puVar2 + 0x10) & 0x400) == 0)) {
          iVar1 = thunk_FUN_004f64dd(s_LOSETAILMESSAGE_0056ee24,puVar2,uVar3);
          *(uint *)(puVar2 + 0x10) = *(uint *)(puVar2 + 0x10) & 0xfffffffb;
          if (DAT_00c80f78 != -1) {
            thunk_FUN_004f8acc(DAT_00c80f78 + 0xf000);
          }
          DAT_00c80f78 = -1;
          if ((-1 < iVar1) && ((&DAT_0056dc34)[iVar1 * 0xc] != 0)) {
            thunk_FUN_004fbbc5((&DAT_0056dc34)[iVar1 * 0xc]);
            return 1;
          }
        }
        if ((((*(uint *)(puVar2 + 0x10) & 0x200) != 0) &&
            (iVar1 = thunk_FUN_004f64dd(s_MAXSPEEDMESSAGE_0056ee34,puVar2,uVar3), -1 < iVar1)) &&
           ((&DAT_0056dc34)[iVar1 * 0xc] != 0)) {
          thunk_FUN_004fbbc5((&DAT_0056dc34)[iVar1 * 0xc]);
          return 1;
        }
      }
      puVar2 = puVar2 + 0x34;
      local_c = local_c + -1;
    }
  }
  return 0;
}


// 004f4f10

void FUN_004f4f10(void)

{
  float *pfVar1;
  undefined *local_14;
  ushort *local_10;
  int local_c;
  
  if (DAT_00c81270 != 0) {
    local_c = 10;
    local_14 = &DAT_00c80ce0;
    while (local_c != 0) {
      if (((*(uint *)(local_14 + 0x10) & 1) != 0) && ((*(uint *)(local_14 + 0x10) & 8) != 0)) {
        for (local_10 = DAT_00d12408; local_10 != (ushort *)0x0;
            local_10 = *(ushort **)(local_10 + 0x10)) {
          if (((*local_10 & 8) != 0) && ((uint)local_10[3] == *(uint *)(local_14 + 0xc))) {
            pfVar1 = *(float **)(local_10 + 0xe);
            if (pfVar1 != (float *)0x0) {
              DAT_00ba52d0 = (int)ROUND(*pfVar1);
              *(int *)(local_14 + 0x14) = DAT_00ba52d0;
              DAT_00ba52d0 = (int)ROUND(pfVar1[2]);
              *(int *)(local_14 + 0x1c) = DAT_00ba52d0;
            }
            break;
          }
        }
      }
      local_14 = local_14 + 0x34;
      local_c = local_c + -1;
    }
  }
  return;
}


// 004f5012

void FUN_004f5012(void)

{
  float *pfVar1;
  int iVar2;
  int local_38;
  undefined *local_14;
  ushort *local_10;
  int local_c;
  
  if (DAT_00c81270 != 0) {
    local_14 = &DAT_00c80ce0;
    for (local_c = 0; local_c < 10; local_c = local_c + 1) {
      if (((*(int *)(&DAT_00b87e60 + local_c * 4) != 0) && ((*(uint *)(local_14 + 0x10) & 1) != 0))
         && ((*(uint *)(local_14 + 0x10) & 8) != 0)) {
        for (local_10 = DAT_00d12408; local_10 != (ushort *)0x0;
            local_10 = *(ushort **)(local_10 + 0x10)) {
          if (((*local_10 & 8) != 0) && ((uint)local_10[3] == *(uint *)(local_14 + 0xc))) {
            pfVar1 = *(float **)(local_10 + 0xe);
            if (pfVar1 != (float *)0x0) {
              DAT_00ba52d0 = (int)ROUND(*pfVar1);
              iVar2 = DAT_00d07888 - DAT_00ba52d0;
              if (iVar2 < 0) {
                iVar2 = -iVar2;
              }
              DAT_00ba52d0 = (int)ROUND(pfVar1[2]);
              local_38 = DAT_00d07890 - DAT_00ba52d0;
              if (local_38 < 0) {
                local_38 = -local_38;
              }
              if (iVar2 < local_38) {
                local_38 = local_38 + iVar2 / 2;
              }
              else {
                local_38 = iVar2 + local_38 / 2;
              }
              if (*(int *)(&DAT_00b87e60 + local_c * 4) < local_38) {
                DAT_00c810c4 = 0xff0;
                DAT_00c810e8 = 3;
                DAT_00c81100 = 0x5a;
              }
            }
            break;
          }
        }
      }
      local_14 = local_14 + 0x34;
    }
  }
  return;
}


// 004f51b4

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_004f51b4(int param_1)

{
  int iVar1;
  int iStack_8;
  
  thunk_FUN_004f556c(param_1);
  switch(*(undefined4 *)(param_1 + 4)) {
  case 4:
    if (DAT_00c808ec == 0) {
      thunk_FUN_0050268f(&DAT_00c808c0,(float)_DAT_00c810a0,0xff00,s_Scare__0056ee50,1,0);
    }
    else if (_DAT_00c808d4 <= _DAT_00c808d0) {
      *(undefined4 *)(param_1 + 4) = 0x7fff;
    }
    break;
  case 5:
    if ((DAT_00c808ec == 0) && (DAT_00b87f08 != 0)) {
      thunk_FUN_0050268f(&DAT_00c808c0,(float)DAT_00bdfa5c,0xff00,s_Opponent__0056ee44,1,0);
    }
    if ((DAT_00b87f08 == 0) || (_DAT_00c808d0 = (float)DAT_00bdfa0c, DAT_00bdfa0c < DAT_00bdfa5c)) {
      if (DAT_011426fc == 0) {
        if (DAT_011426e4 == 0) {
          if (DAT_01143720 != 0) {
            *(undefined4 *)(param_1 + 4) = 0x7fff;
            _DAT_00c80f50 = (float)DAT_00d0cbd0;
            _DAT_00c80f54 = (float)DAT_00d0cbd4;
            _DAT_00c80f58 = (float)DAT_00d0cbd8;
          }
        }
        else {
          *(undefined4 *)(param_1 + 4) = 0x7fff;
        }
      }
      else {
        *(undefined4 *)(param_1 + 4) = 0xff0;
        *(undefined4 *)(param_1 + 0x28) = 3;
        *(undefined4 *)(param_1 + 0x40) = 0x5a;
      }
    }
    else {
      *(undefined4 *)(param_1 + 4) = 0x7fff;
      DAT_00b87f08 = 0;
      DAT_011426e4 = 1;
      _DAT_00c80f50 = (float)DAT_00d0cbd0;
      _DAT_00c80f54 = (float)DAT_00d0cbd4;
      _DAT_00c80f58 = (float)DAT_00d0cbd8;
    }
    break;
  case 6:
    for (iStack_8 = 0; iStack_8 < 10; iStack_8 = iStack_8 + 1) {
      if (((((&DAT_00c80cf0)[iStack_8 * 0xd] & 1) != 0) &&
          (((&DAT_00c80cf0)[iStack_8 * 0xd] & 0x100) != 0)) &&
         (iVar1 = thunk_FUN_0049245a(*(undefined4 *)(&DAT_00c80ce8 + iStack_8 * 0x34),
                                     *(undefined4 *)(&DAT_00c80ce4 + iStack_8 * 0x34),
                                     &DAT_00c80cf4 + iStack_8 * 0xd), iVar1 != 0)) {
        *(undefined4 *)(param_1 + 4) = 0x7fff;
        (&DAT_00c80cf0)[iStack_8 * 0xd] = (&DAT_00c80cf0)[iStack_8 * 0xd] & 0xfffffefe;
      }
    }
    break;
  case 8:
    if (*(int *)(param_1 + 0x68) == -1) {
      *(undefined4 *)(param_1 + 4) = 0x7fff;
    }
    else if ((&DAT_011443f5)[*(int *)(param_1 + 0x68) * 0x54] == '\0') {
      DAT_00c80cf0 = DAT_00c80cf0 & 0xfffffffe;
      *(undefined4 *)(param_1 + 4) = 0xff0;
      *(undefined4 *)(param_1 + 0x28) = 4;
      *(undefined4 *)(param_1 + 0x40) = 0x5a;
    }
    else {
      iVar1 = thunk_FUN_004a1d31(*(undefined4 *)(param_1 + 0x68));
      if (iVar1 < *(int *)(param_1 + 0x6c)) {
        DAT_00c80cf4 = (&DAT_00d07888)[(*(int *)(param_1 + 0x68) + 1) * 0x52];
        DAT_00c80cfc = (&DAT_00d07890)[(*(int *)(param_1 + 0x68) + 1) * 0x52];
      }
      else {
        (&DAT_011443f5)[*(int *)(param_1 + 0x68) * 0x54] = 0;
        *(undefined4 *)(param_1 + 0x68) = 0xffffffff;
        DAT_00c80cf0 = DAT_00c80cf0 & 0xfffffffe;
      }
    }
  }
  if (((((*(int *)(param_1 + 4) != 0xff0) && (*(int *)(param_1 + 4) != 0x7fff)) && (param_1 != 0))
      && ((*(int *)(param_1 + 4) != 0x8000 && (*(int *)(param_1 + 4) != 0xf1)))) &&
     (iVar1 = thunk_FUN_00492398(*(undefined4 *)(param_1 + 0x78),*(undefined4 *)(param_1 + 0x74)),
     iVar1 != 0)) {
    *(undefined4 *)(param_1 + 0x74) = 0;
    *(undefined4 *)(param_1 + 4) = 0xff0;
    *(undefined4 *)(param_1 + 0x28) = 4;
    *(undefined4 *)(param_1 + 0x40) = 0x5a;
  }
  return;
}


// 004f556c

void FUN_004f556c(undefined4 param_1)

{
  int iVar1;
  int local_24;
  undefined *local_18;
  int local_c;
  
  local_18 = &DAT_00c80ce0;
  local_c = 10;
  while (local_c != 0) {
    if (((*(uint *)(local_18 + 0x10) & 1) != 0) && ((*(uint *)(local_18 + 0x10) & 0x80) == 0)) {
      iVar1 = *(int *)(local_18 + 0x14) - DAT_00d07888;
      if (iVar1 < 0) {
        iVar1 = -iVar1;
      }
      local_24 = *(int *)(local_18 + 0x1c) - DAT_00d07890;
      if (local_24 < 0) {
        local_24 = -local_24;
      }
      if (iVar1 < local_24) {
        local_24 = local_24 + iVar1 / 2;
      }
      else {
        local_24 = iVar1 + local_24 / 2;
      }
      *(uint *)(local_18 + 0x10) = *(uint *)(local_18 + 0x10) & 0xfffffffd;
      iVar1 = thunk_FUN_004f58c6(local_24,param_1,local_18);
      if (iVar1 == 0) {
        iVar1 = thunk_FUN_004f57d7(local_24,param_1,local_18);
        if (iVar1 == 0) {
          thunk_FUN_004f568a(local_24,param_1,local_18);
        }
      }
    }
    local_18 = local_18 + 0x34;
    local_c = local_c + -1;
  }
  return;
}


// 004f568a

void FUN_004f568a(int param_1,int param_2,int *param_3)

{
  bool bVar1;
  
  bVar1 = false;
  if ((0x2a9 < DAT_00d11a5c) && ((DAT_0112d9e4 != 0 || (0 < DAT_0112b270)))) {
    bVar1 = true;
  }
  if (((param_1 < *param_3) && ((*(int *)(param_2 + 4) == 2 || (*(int *)(param_2 + 4) == 7)))) &&
     ((DAT_00c810a8 == 0 && DAT_00c81490 == 0 || (!bVar1)))) {
    if ((*(uint *)(param_2 + 0x18) & 1) == 0) {
      if (*(int *)(param_2 + 0x1b4) == 0) {
        *(undefined4 *)(param_2 + 4) = 0x7fff;
        param_3[4] = param_3[4] & 0xfffffffe;
      }
      else if (DAT_00d078cc <= *(int *)(param_2 + 0x44)) {
        *(undefined4 *)(param_2 + 4) = 0x7fff;
        param_3[4] = param_3[4] & 0xfffffffe;
      }
    }
    else if (**(int **)(param_2 + 0x1fc) < *(int *)(param_2 + 0x1c) * 0x32) {
      if (*(int *)(param_2 + 0x1b4) == 0) {
        *(undefined4 *)(param_2 + 4) = 0x7fff;
        param_3[4] = param_3[4] & 0xfffffdf8;
      }
      else if (DAT_00d078cc <= *(int *)(param_2 + 0x44)) {
        *(undefined4 *)(param_2 + 4) = 0x7fff;
        param_3[4] = param_3[4] & 0xfffffdf8;
      }
    }
    else {
      thunk_FUN_004d2ade(5);
    }
  }
  return;
}


// 004f57d7

undefined4 FUN_004f57d7(int param_1,int param_2,int param_3)

{
  bool bVar1;
  undefined4 uVar2;
  
  if (*(int *)(param_2 + 4) == 2) {
    bVar1 = false;
    if ((0x2a9 < DAT_00d11a5c) && ((DAT_0112d9e4 != 0 || (0 < DAT_0112b270)))) {
      bVar1 = true;
    }
    if (((param_1 < *(int *)(param_2 + 0x2c)) && (DAT_00c810a8 != 0 || DAT_00c81490 != 0)) &&
       (bVar1)) {
      *(uint *)(param_3 + 0x10) = *(uint *)(param_3 + 0x10) | 4;
      uVar2 = 1;
    }
    else {
      if ((*(int *)(param_2 + 0x1b4) != 0) && ((*(uint *)(param_2 + 0x18) & 1) != 0)) {
        *(uint *)(param_3 + 0x10) = *(uint *)(param_3 + 0x10) & 0xfffffdff;
        if ((param_1 < 6000) &&
           ((**(int **)(param_2 + 0x1fc) < *(int *)(param_2 + 0x1c) * 0x32 &&
            (*(int *)(param_2 + 0x44) < DAT_00d078cc)))) {
          *(uint *)(param_3 + 0x10) = *(uint *)(param_3 + 0x10) | 0x200;
          return 1;
        }
      }
      uVar2 = 0;
    }
  }
  else {
    uVar2 = 0;
  }
  return uVar2;
}


// 004f58c6

undefined4 FUN_004f58c6(int param_1,int param_2,int param_3)

{
  undefined4 uVar1;
  
  if (((param_1 < *(int *)(param_2 + 0x20)) && ((*(uint *)(param_2 + 0x18) & 1) != 0)) &&
     (*(int *)(param_2 + 0x1c) * 0x32 <= **(int **)(param_2 + 0x1fc))) {
    *(uint *)(param_3 + 0x10) = *(uint *)(param_3 + 0x10) | 2;
    if ((DAT_00d118c0 & 3) == 3) {
      thunk_FUN_004a7e6e(1);
      if (0x2a9 < DAT_00d11a5c) {
        DAT_0112b268 = 1;
        DAT_0112b25c = 1;
      }
    }
    uVar1 = 1;
  }
  else {
    uVar1 = 0;
  }
  return uVar1;
}


// 004f5951

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_004f5951(void)

{
  DAT_0112b268 = 0;
  switch(DAT_00c810e8) {
  case 1:
    if (_DAT_00c80f60 != -1) {
      thunk_FUN_004f8acc(_DAT_00c80f60 + 0xf000);
      _DAT_00c80f60 = -1;
    }
    break;
  case 2:
    if (iRam00c80f64 != -1) {
      thunk_FUN_004f8acc(iRam00c80f64 + 0xf000);
      iRam00c80f64 = -1;
    }
    break;
  case 3:
    if (iRam00c80f68 != -1) {
      thunk_FUN_004f8acc(iRam00c80f68 + 0xf000);
      iRam00c80f68 = -1;
    }
    break;
  case 4:
    if (iRam00c80f6c != -1) {
      thunk_FUN_004f8acc(iRam00c80f6c + 0xf000);
      iRam00c80f6c = -1;
    }
  }
  if (0x32 < DAT_00c810cc) {
    DAT_00c810cc = 0x32;
  }
  DAT_00d118a8 = 1;
  return;
}


// 004f5a57

void FUN_004f5a57(void)

{
  DAT_0112b268 = 0;
  DAT_00c810c8 = DAT_00c810c8 + 1;
  if ((DAT_00c810c4 & 0x8000) == 0) {
    if (DAT_00c810c4 == 0xf1) {
      if (DAT_00c810c8 < 0x33) {
        thunk_FUN_004ca98d(5,DAT_00c810c8);
      }
      else {
        DAT_00c810c8 = 0x33;
      }
    }
    else {
      DAT_00c810c4 = 0x7fff;
    }
  }
  else if (DAT_00c81880 == 0) {
    DAT_00c81880 = 1;
    DAT_00c810e8 = 0;
    DAT_00c81100 = 0x96;
    DAT_00d118a8 = 1;
  }
  return;
}


// 004f5afe

void FUN_004f5afe(int *param_1)

{
  if ((param_1[1] & 4U) != 0) {
    if ((param_1[1] & 0x80U) == 0) {
      if (*param_1 == 0) {
        if (DAT_00b87eb0 == 0) {
          DAT_00c810c4 = 0xff0;
          DAT_00c810e8 = 1;
          DAT_00c81100 = 0x5a;
        }
        param_1[1] = param_1[1] & 0xfffffff7;
      }
      else if ((param_1[1] & 8U) != 0) {
        *param_1 = *param_1 + -1;
        param_1[2] = param_1[2] + 1;
      }
    }
    else if ((param_1[1] & 8U) != 0) {
      *param_1 = *param_1 + 1;
      param_1[2] = param_1[2] + 1;
    }
    if (((DAT_00c810d8 & 8) != 0) && (*param_1 == DAT_00c810f0)) {
      thunk_FUN_004cfe69(DAT_00c810f4);
    }
    param_1[4] = *param_1 / 0x32;
    param_1[5] = param_1[4] / 0x3c;
    param_1[3] = *param_1 % 0x32;
    param_1[4] = param_1[4] % 0x3c;
    param_1[3] = param_1[3] << 1;
    if (0x3b < param_1[5]) {
      param_1[5] = 0x3b;
      param_1[4] = 0x3b;
    }
  }
  return;
}


// 004f5c58

void FUN_004f5c58(int *param_1,int param_2)

{
  *param_1 = param_2 * 0x32;
  param_1[1] = 0xc;
  return;
}


// 004f5c72

void FUN_004f5c72(undefined4 *param_1,undefined4 param_2)

{
  *param_1 = param_2;
  param_1[1] = 0xc;
  return;
}


// 004f5c89

void FUN_004f5c89(int param_1,int param_2)

{
  int local_8;
  
  if (param_2 != 0) {
    if (param_2 == 1) {
      local_8 = 0x12a;
    }
    else {
      local_8 = 0xf8;
    }
    if ((*(uint *)(*(int *)(param_1 + 0x1fc) + 4) & 4) != 0) {
      DAT_00c80ca0 = DAT_00c80ca0 + param_2;
      if (param_2 < 0) {
        FUN_0052a910(&DAT_00c80c60,s__d__s__0056ee58,DAT_00c80ca0,(&DAT_00c55820)[local_8]);
      }
      else {
        FUN_0052a910(&DAT_00c80c60,s___d__s__0056ee60,DAT_00c80ca0,(&DAT_00c55820)[local_8]);
      }
      if (*(int *)(param_1 + 0x1fc) != 0) {
        **(int **)(param_1 + 0x1fc) = **(int **)(param_1 + 0x1fc) + param_2 * 0x32;
      }
      DAT_00c81494 = 0x32;
      *(int *)(param_1 + 100) = *(int *)(param_1 + 100) + 1;
    }
  }
  return;
}


// 004f5d67

void FUN_004f5d67(void)

{
  if (DAT_00c81494 < 1) {
    DAT_00c81494 = 0;
    DAT_00c80ca0 = 0;
  }
  else {
    DAT_00c81494 = DAT_00c81494 + -1;
  }
  return;
}


// 004f5d98

void FUN_004f5d98(void)

{
  if (0 < DAT_00c81494) {
    thunk_FUN_0051755e(0x140,0x50,&DAT_00c80c60,0,1,0xff,0xff,0xff);
  }
  return;
}


// 004f5dcd

void FUN_004f5dcd(void)

{
  undefined4 local_8;
  
  for (local_8 = 0; local_8 < DAT_00c814e8; local_8 = local_8 + 1) {
    thunk_FUN_004d8f30(*(undefined4 *)(DAT_00c816a0 + local_8 * 4));
  }
  if (DAT_00c816a0 != 0) {
    thunk_FUN_004d8f30(DAT_00c816a0);
  }
  if (DAT_00c810ac != 0) {
    thunk_FUN_004d8f30(DAT_00c810ac);
  }
  DAT_00c814e8 = 0;
  DAT_00c816a0 = 0;
  DAT_00c810ac = 0;
  return;
}


// 004f5e55

undefined4 AddDashMessage(char *param_1,undefined4 param_2)

{
  int iVar1;
  undefined4 uVar2;
  int iVar3;
  size_t sVar4;
  char *pcVar5;
  int local_8;
  
  iVar1 = thunk_FUN_004d8db4(DAT_00c814e8 * 4 + 4,s_D__Driver_Game_MScript_c_0056ee68,0x61b);
  if (iVar1 == 0) {
    thunk_FUN_004bf2a0(s_AddDashMessage__Unable_to_alloca_0056ee84);
    uVar2 = 0;
  }
  else {
    iVar3 = thunk_FUN_004d8db4(DAT_00c814e8 * 4 + 4,s_D__Driver_Game_MScript_c_0056eec0,0x622);
    if (iVar3 == 0) {
      thunk_FUN_004bf2a0(s_AddDashMessage__Unable_to_alloca_0056eedc);
      thunk_FUN_004d8f30(iVar1);
      uVar2 = 0;
    }
    else {
      for (local_8 = 0; local_8 < DAT_00c814e8; local_8 = local_8 + 1) {
        *(undefined4 *)(iVar3 + local_8 * 4) = *(undefined4 *)(DAT_00c810ac + local_8 * 4);
        *(undefined4 *)(iVar1 + local_8 * 4) = *(undefined4 *)(DAT_00c816a0 + local_8 * 4);
      }
      *(undefined4 *)(iVar3 + DAT_00c814e8 * 4) = param_2;
      uVar2 = 0x633;
      pcVar5 = s_D__Driver_Game_MScript_c_0056ef1c;
      sVar4 = _strlen(param_1);
      uVar2 = thunk_FUN_004d8db4(sVar4 + 1,pcVar5,uVar2);
      *(undefined4 *)(iVar1 + DAT_00c814e8 * 4) = uVar2;
      if (*(int *)(iVar1 + DAT_00c814e8 * 4) == 0) {
        thunk_FUN_004bf2a0(s_AddDashMessage__Unable_to_alloca_0056ef38);
        thunk_FUN_004d8f30(iVar1);
        thunk_FUN_004d8f30(iVar3);
        uVar2 = 0;
      }
      else {
        FUN_0052b100(*(undefined4 *)(iVar1 + DAT_00c814e8 * 4),param_1);
        if (DAT_00c816a0 != 0) {
          thunk_FUN_004d8f30(DAT_00c816a0);
        }
        if (DAT_00c810ac != 0) {
          thunk_FUN_004d8f30(DAT_00c810ac);
        }
        DAT_00c814e8 = DAT_00c814e8 + 1;
        uVar2 = 1;
        DAT_00c810ac = iVar3;
        DAT_00c816a0 = iVar1;
      }
    }
  }
  return uVar2;
}


// 004f6011

undefined4 FUN_004f6011(int param_1)

{
  int local_10;
  int local_8;
  
  if (param_1 != 0) {
    local_8 = 0;
    for (local_10 = 0; local_10 < DAT_00c814e8; local_10 = local_10 + 1) {
      if ((local_8 <= param_1 / 0x32) && (param_1 / 0x32 < *(int *)(DAT_00c810ac + local_10 * 4))) {
        return *(undefined4 *)(DAT_00c816a0 + local_10 * 4);
      }
      local_8 = *(int *)(DAT_00c810ac + local_10 * 4);
    }
    DAT_00c810c4 = 0xff0;
    DAT_00c810e8 = 1;
    DAT_00c81100 = 0x5a;
  }
  return 0;
}


// 004f60b7

void FUN_004f60b7(void)

{
  undefined1 local_48 [64];
  int local_8;
  
  if ((DAT_00b87e7c == 0) && (DAT_00c8127c != 0)) {
    local_8 = ((int)(DAT_0125f3f0 + (DAT_0125f3f0 >> 0x1f & 7U)) >> 3) + -9;
    thunk_FUN_004d94b7(0,local_8);
    thunk_FUN_004d90f4(s_____Debug_Information_____0056ef74);
    FUN_0052a910(local_48,s_Player_car_X_position____d_0056ef90,DAT_00d07888);
    thunk_FUN_004d90f4(local_48);
    FUN_0052a910(local_48,s_Player_car_Y_position____d_0056efac,DAT_00d0788c);
    thunk_FUN_004d90f4(local_48);
    FUN_0052a910(local_48,s_Player_car_Z_position____d_0056efc8,DAT_00d07890);
    thunk_FUN_004d90f4(local_48);
    FUN_0052a910(local_48,s_Player_car_Y_rotation____d__Curr_0056efe4,(int)DAT_00d078aa,DAT_00bdf984
                );
    thunk_FUN_004d90f4(local_48);
    FUN_0052a910(local_48,s_Player_car_speed____d_0056f018,DAT_00d078cc);
    thunk_FUN_004d90f4(local_48);
    FUN_0052a910(local_48,s_Number_of_pedestrians_active___d_0056f030,DAT_00c56764,DAT_005759a4);
    thunk_FUN_004d90f4(local_48);
    if (0 < DAT_00b31f44) {
      FUN_0052a910(local_48,s_Number_of_cones_recorded___d_0056f060,DAT_00b31f44);
      thunk_FUN_004d90f4(local_48);
    }
  }
  return;
}


// 004f621d

/* WARNING: Removing unreachable block (ram,0x004f632d) */

int FUN_004f621d(void)

{
  int iVar1;
  size_t sVar2;
  undefined4 uVar3;
  int local_8;
  
  while( true ) {
    iVar1 = thunk_FUN_004f6774(DAT_00c81684,&DAT_00c81580);
    if (iVar1 != 0) {
      return iVar1;
    }
    FUN_0053fb50(&DAT_00c81580);
    sVar2 = _strlen(&DAT_00c81580);
    if ((DAT_00c81580 == '/') && (DAT_00c81581 == '/')) {
      return 0;
    }
    if (DAT_00c81580 == '#') {
      return 0;
    }
    if (sVar2 == 0) break;
    if (DAT_00c81580 == ',') {
      return 6;
    }
    if (DAT_00c81580 != ';') {
      uVar3 = thunk_FUN_004f6333(&DAT_00c81580,&local_8);
      if (local_8 == 0) {
        iVar1 = thunk_FUN_004f8485(0,0);
        if (iVar1 != 0) {
          return iVar1;
        }
      }
      else {
        iVar1 = thunk_FUN_004f68a1(local_8,uVar3);
        if (iVar1 != 0xb) {
          return iVar1;
        }
      }
    }
  }
  return 0;
}


// 004f6333

undefined4 FUN_004f6333(char *param_1,undefined4 *param_2)

{
  size_t sVar1;
  int iVar2;
  char *local_8;
  
  *param_2 = 0;
  local_8 = s_CHECKPOINT_00563980;
  while( true ) {
    sVar1 = _strlen(local_8);
    if (sVar1 == 0) {
      return 9;
    }
    iVar2 = _strcmp(param_1,local_8);
    if (iVar2 == 0) break;
    local_8 = local_8 + 0x110;
  }
  *param_2 = local_8;
  return 0;
}


// 004f638d

void FUN_004f638d(void)

{
  char *local_c;
  int local_8;
  
  if (DAT_00c8175c != 0) {
    for (local_8 = 0; local_8 < DAT_00c81688; local_8 = local_8 + 1) {
      if (*(int *)(DAT_00c8175c + local_8 * 4) != 0) {
        thunk_FUN_004d8f30(*(undefined4 *)(DAT_00c8175c + local_8 * 4));
        *(undefined4 *)(DAT_00c8175c + local_8 * 4) = 0;
      }
      *(undefined4 *)(DAT_00c8175c + local_8 * 4) = 0;
    }
    thunk_FUN_004d8f30(DAT_00c8175c);
    DAT_00c8175c = 0;
  }
  thunk_FUN_004f5dcd();
  thunk_FUN_004f8d6d(&DAT_00c81698);
  if (DAT_00c81684 != 0) {
    thunk_FUN_004d8f30(DAT_00c81684);
    DAT_00c81684 = 0;
  }
  for (local_c = s_EVENTSCRIPT_0056dc10; *(int *)(local_c + 0x20) != 0x7f; local_c = local_c + 0x30)
  {
    if (*(int *)(local_c + 0x20) == 1) {
      if (*(int *)(local_c + 0x24) != 0) {
        thunk_FUN_004d8f30(*(undefined4 *)(local_c + 0x24));
        local_c[0x24] = '\0';
        local_c[0x25] = '\0';
        local_c[0x26] = '\0';
        local_c[0x27] = '\0';
      }
      local_c[0x24] = '\0';
      local_c[0x25] = '\0';
      local_c[0x26] = '\0';
      local_c[0x27] = '\0';
    }
  }
  if (DAT_00c80c50 != 0) {
    thunk_FUN_004d8f30(DAT_00c80c50);
  }
  DAT_00c80c50 = 0;
  DAT_00c8175c = 0;
  DAT_00c81684 = 0;
  DAT_00c81688 = 0;
  return;
}


// 004f64dd

int FUN_004f64dd(char *param_1)

{
  int iVar1;
  char *local_c;
  int local_8;
  
  local_8 = 0;
  local_c = s_EVENTSCRIPT_0056dc10;
  while( true ) {
    if (*(int *)(local_c + 0x20) == 0x7f) {
      return -1;
    }
    iVar1 = _strcmp(local_c,param_1);
    if (iVar1 == 0) break;
    local_8 = local_8 + 1;
    local_c = local_c + 0x30;
  }
  return local_8;
}


// 004f652e

undefined4 FUN_004f652e(char *param_1,int param_2)

{
  size_t sVar1;
  undefined4 uVar2;
  int local_10;
  int local_c;
  int local_8;
  
  sVar1 = _strlen(param_1);
  local_10 = 0;
  for (local_c = 0; local_c < (int)sVar1; local_c = local_c + 1) {
    if (((byte)param_1[local_c] < 0x21) || (0x7f < (byte)param_1[local_c])) {
      if (local_10 != 0) break;
    }
    else {
      if (param_1[local_c] == ',') break;
      *(char *)(param_2 + local_10) = param_1[local_c];
      local_10 = local_10 + 1;
    }
  }
  if (local_10 == 0) {
    uVar2 = 0xc;
  }
  else {
    local_8 = 0;
    while (local_c = local_c + 1, local_c < (int)sVar1) {
      param_1[local_8] = param_1[local_c];
      local_8 = local_8 + 1;
    }
    *(undefined1 *)(param_2 + local_10) = 0;
    uVar2 = 0;
  }
  return uVar2;
}


// 004f6612

undefined4 FUN_004f6612(char *param_1,int param_2)

{
  size_t sVar1;
  int iVar2;
  int local_c;
  int local_8;
  
  sVar1 = _strlen(param_1);
  local_8 = 0;
  local_c = 0;
  do {
    if ((int)sVar1 <= local_c) {
      return 0xc;
    }
    if (((param_1[local_c] != '\"') && (param_1[local_c] != ' ')) && (param_1[local_c] != '\t')) {
      return 0xc;
    }
    if (param_1[local_c] == '\"') {
      iVar2 = local_c + 1;
      for (local_c = iVar2; local_c < (int)sVar1; local_c = local_c + 1) {
        if (param_1[local_c] == '\"') {
          for (local_c = 0; local_c < local_8; local_c = local_c + 1) {
            *(char *)(param_2 + local_c) = param_1[iVar2 + local_c];
          }
          *(undefined1 *)(param_2 + local_c) = 0;
          FUN_0052b100(param_1,param_1 + iVar2 + local_c + 1);
          return 0;
        }
        if (((byte)param_1[local_c] < 0x20) || (0x7f < (byte)param_1[local_c])) {
          return 0xc;
        }
        local_8 = local_8 + 1;
      }
    }
    local_c = local_c + 1;
  } while( true );
}


// 004f6774

undefined4 FUN_004f6774(char *param_1,int param_2)

{
  char cVar1;
  size_t sVar2;
  undefined4 uVar3;
  int local_18;
  int local_14;
  size_t local_10;
  int local_8;
  
  local_14 = 0;
  local_18 = 0;
  local_10 = _strlen(param_1);
  while (sVar2 = local_10 - 1, local_10 != 0) {
    cVar1 = param_1[local_18];
    local_18 = local_18 + 1;
    local_10 = sVar2;
    if (((cVar1 != ' ') && (cVar1 != '\t')) || (local_14 != 0)) {
      if (((cVar1 == ' ') || (cVar1 == '\t')) ||
         ((cVar1 == '\n' || ((cVar1 == ',' || (cVar1 == ';')))))) break;
      *(char *)(param_2 + local_14) = cVar1;
      local_14 = local_14 + 1;
    }
  }
  *(undefined1 *)(param_2 + local_14) = 0;
  local_8 = 0;
  for (; param_1[local_18] != '\0'; local_18 = local_18 + 1) {
    param_1[local_8] = param_1[local_18];
    local_8 = local_8 + 1;
  }
  param_1[local_8] = '\0';
  if (local_14 == 0) {
    uVar3 = 10;
  }
  else {
    uVar3 = 0;
  }
  return uVar3;
}


// 004f68a1

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

int FUN_004f68a1(int param_1)

{
  size_t sVar1;
  int iVar2;
  undefined4 *puVar3;
  undefined4 *puVar4;
  undefined1 auStack_e4 [64];
  int iStack_a4;
  int local_a0;
  int iStack_9c;
  int iStack_98;
  int iStack_94;
  char *local_90;
  undefined1 auStack_8c [128];
  undefined4 *local_c;
  int local_8;
  
  local_90 = (char *)0x0;
  if (param_1 == 0) {
    return 9;
  }
  switch(*(undefined4 *)(param_1 + 0x104)) {
  case 2:
    local_a0 = thunk_FUN_004f6774(DAT_00c81684,&DAT_00c81580);
    if (local_a0 == 0) {
      FUN_0053fb50(&DAT_00c81580);
      iVar2 = thunk_FUN_004f8485(param_1,0);
      return iVar2;
    }
    return local_a0;
  default:
    local_a0 = thunk_FUN_004f87e0(param_1);
    if (local_a0 != 0) {
      return local_a0;
    }
    iVar2 = thunk_FUN_004f8643(*(undefined4 *)(param_1 + 0x108));
    if (iVar2 != 0) {
      return iVar2;
    }
    local_c = *(undefined4 **)(DAT_00c8175c + -4 + DAT_00c81688 * 4);
    *local_c = *(undefined4 *)(param_1 + 0x104);
    for (local_8 = 0; local_c = local_c + 1, local_8 < *(int *)(param_1 + 0x100);
        local_8 = local_8 + 1) {
      *local_c = (&DAT_00c80c00)[local_8];
    }
    break;
  case 0xc:
  case 0xd:
    local_a0 = thunk_FUN_004f6774(DAT_00c81684,&DAT_00c81580);
    if (local_a0 != 0) {
      return local_a0;
    }
    FUN_0053fb50(&DAT_00c81580);
    iStack_98 = thunk_FUN_004f64dd(&DAT_00c81580);
    if (iStack_98 != -1) {
      if ((&DAT_0056dc30)[iStack_98 * 0xc] == 3) {
        thunk_FUN_004f8643(8);
        puVar3 = *(undefined4 **)(DAT_00c8175c + -4 + DAT_00c81688 * 4);
        *puVar3 = 0xc;
        puVar3[1] = iStack_98;
        return 0;
      }
      return 0xc;
    }
    return 0xc;
  case 0xe:
  case 0xf:
    local_a0 = thunk_FUN_004f6774(DAT_00c81684,&DAT_00c81580);
    if (local_a0 != 0) {
      return local_a0;
    }
    FUN_0053fb50(&DAT_00c81580);
    iStack_98 = thunk_FUN_004f64dd(&DAT_00c81580);
    if (iStack_98 != -1) {
      if ((&DAT_0056dc30)[iStack_98 * 0xc] == 3) {
        thunk_FUN_004f8643(8);
        puVar3 = *(undefined4 **)(DAT_00c8175c + -4 + DAT_00c81688 * 4);
        *puVar3 = 0xe;
        puVar3[1] = iStack_98;
        return 0;
      }
      return 0xc;
    }
    return 0xc;
  case 0x10:
    local_a0 = thunk_FUN_004f6774(DAT_00c81684,&DAT_00c81580);
    if (local_a0 != 0) {
      return local_a0;
    }
    FUN_0053fb50(&DAT_00c81580);
    iStack_98 = thunk_FUN_004f64dd(&DAT_00c81580);
    if (iStack_98 == -1) {
      return 0xc;
    }
    if ((&DAT_0056dc30)[iStack_98 * 0xc] != 3) {
      return 0xc;
    }
    local_a0 = thunk_FUN_004f6774(DAT_00c81684,&DAT_00c81580);
    if (local_a0 == 0) {
      iStack_9c = FUN_0052e250(&DAT_00c81580,0x56f080,&DAT_00c80c00);
      if ((iStack_9c != 0) && (iStack_9c != -1)) {
        thunk_FUN_004f8643(0xc);
        puVar3 = *(undefined4 **)(DAT_00c8175c + -4 + DAT_00c81688 * 4);
        *puVar3 = 0x10;
        puVar3[1] = iStack_98;
        puVar3[2] = DAT_00c80c00;
        return 0xb;
      }
      return 0xc;
    }
    return local_a0;
  case 0x11:
    local_a0 = thunk_FUN_004f6774(DAT_00c81684,&DAT_00c81580);
    if (local_a0 != 0) {
      return local_a0;
    }
    FUN_0053fb50(&DAT_00c81580);
    iStack_98 = thunk_FUN_004f64dd(&DAT_00c81580);
    if (iStack_98 == -1) {
      return 0xc;
    }
    if ((&DAT_0056dc30)[iStack_98 * 0xc] != 3) {
      return 0xc;
    }
    local_a0 = thunk_FUN_004f6774(DAT_00c81684,&DAT_00c81580);
    if (local_a0 == 0) {
      iStack_9c = FUN_0052e250(&DAT_00c81580,0x56f084,&DAT_00c80c00);
      if ((iStack_9c != 0) && (iStack_9c != -1)) {
        thunk_FUN_004f8643(0xc);
        puVar3 = *(undefined4 **)(DAT_00c8175c + -4 + DAT_00c81688 * 4);
        *puVar3 = 0x11;
        puVar3[1] = iStack_98;
        puVar3[2] = DAT_00c80c00;
        return 0xb;
      }
      return 0xc;
    }
    return local_a0;
  case 0x13:
    iVar2 = thunk_FUN_004f87e0(param_1);
    if (iVar2 != 0) {
      return iVar2;
    }
    DAT_00c81278 = 1;
    DAT_00c812c0 = DAT_00c80c00;
    DAT_00c812c4 = 0xfffffe0c;
    DAT_00c812c8 = iRam00c80c04;
    break;
  case 0x14:
    local_a0 = thunk_FUN_004f6774(DAT_00c81684,&DAT_00c81580);
    if (local_a0 != 0) {
      return local_a0;
    }
    FUN_0053fb50(&DAT_00c81580);
    iStack_9c = FUN_0052e250(&DAT_00c81580,0x56f08c,&DAT_00c80c00);
    if ((iStack_9c != 0) && (iStack_9c != -1)) {
      if (3 < DAT_00c80c00) {
        DAT_00c80c00 = 3;
      }
      local_8 = 0;
      while( true ) {
        if (DAT_00c80c00 * 3 <= local_8) {
          iStack_94 = DAT_00c80c00 * 0xc + 8;
          thunk_FUN_004f8643(iStack_94);
          local_c = *(undefined4 **)(DAT_00c8175c + -4 + DAT_00c81688 * 4);
          *local_c = 0x14;
          local_c[1] = DAT_00c80c00;
          local_c = local_c + 2;
          for (local_8 = 0; local_8 < DAT_00c80c00 * 3; local_8 = local_8 + 1) {
            *local_c = *(undefined4 *)(local_8 * 4 + 0xc80c04);
            local_c = local_c + 1;
          }
          return 0xb;
        }
        local_a0 = thunk_FUN_004f6774(DAT_00c81684,&DAT_00c81580);
        if (local_a0 != 0) break;
        FUN_0053fb50(&DAT_00c81580);
        iStack_9c = FUN_0052e250(&DAT_00c81580,0x56f090,local_8 * 4 + 0xc80c04);
        if ((iStack_9c == 0) || (iStack_9c == -1)) {
          return 0xc;
        }
        local_8 = local_8 + 1;
      }
      return local_a0;
    }
    return 0xc;
  case 0x16:
    local_a0 = thunk_FUN_004f6774(DAT_00c81684,&DAT_00c81580);
    if (local_a0 != 0) {
      return local_a0;
    }
    FUN_0053fb50(&DAT_00c81580);
    iStack_9c = FUN_0052e250(&DAT_00c81580,0x56f088,&DAT_00c80c00);
    if ((iStack_9c != 0) && (iStack_9c != -1)) {
      local_a0 = thunk_FUN_004f6612(DAT_00c81684,&DAT_00c81580);
      if (local_a0 == 0) {
        sVar1 = _strlen(&DAT_00c81580);
        iStack_94 = sVar1 + 1;
        thunk_FUN_004f8643(sVar1 + 0xd);
        local_c = *(undefined4 **)(DAT_00c8175c + -4 + DAT_00c81688 * 4);
        *local_c = 0x16;
        local_c[1] = DAT_00c80c00 * 0x32;
        local_c[2] = iStack_94;
        local_c = local_c + 3;
        thunk_FUN_005283b5(local_c,&DAT_00c81580,iStack_94);
        return 0xb;
      }
      return local_a0;
    }
    return 0xc;
  case 0x1e:
    DAT_00b202e0 = 1;
    break;
  case 0x1f:
    DAT_00b201dc = 1;
    DAT_00b87e84 = 1;
    DAT_00b87e88 = 0;
    break;
  case 0x20:
    DAT_00b201dc = 1;
    DAT_00b87e84 = 1;
    DAT_00b202d4 = 1;
    break;
  case 0x22:
    local_a0 = thunk_FUN_004f6612(DAT_00c81684,&DAT_00c81780);
    if (local_a0 != 0) {
      DAT_00c81164 = (undefined *)0x0;
      DAT_00c81780 = 0;
      return local_a0;
    }
    DAT_00c81164 = &DAT_00c81780;
    FUN_0053fb50(&DAT_00c81780);
    for (local_8 = 0; local_8 < 7; local_8 = local_8 + 1) {
      iVar2 = _strcmp(&DAT_00c81780,(&PTR_s_MIAMI_01_LEV_00562d44)[local_8]);
      if (iVar2 == 0) {
        DAT_00b87e30 = local_8;
        return 0xb;
      }
    }
    break;
  case 0x27:
    DAT_00b202dc = 1;
    DAT_00d17aec = 0;
    break;
  case 0x28:
    DAT_00b202d8 = 1;
    DAT_00b87e84 = 1;
    DAT_00b201dc = 1;
    DAT_00d17aec = 0;
    break;
  case 0x34:
    iVar2 = thunk_FUN_004f87e0(param_1);
    if (iVar2 != 0) {
      return iVar2;
    }
    DAT_00c810fc = DAT_00c80c00;
    break;
  case 0x3d:
    iVar2 = thunk_FUN_004f6612(DAT_00c81684,0xc80f00);
    if (iVar2 != 0) {
      DAT_00c81780 = 0;
      return iVar2;
    }
    iStack_a4 = 0;
    local_a0 = 0;
    while( true ) {
      FUN_0052a910(auStack_e4,s_replaydata_Chase__s_d_leader_0056f0c8,0xc80f00,iStack_a4);
      iVar2 = FUN_0052adb0(auStack_e4,0x56f0e8);
      if (iVar2 == 0) break;
      FUN_0052aa10(iVar2);
      iStack_a4 = iStack_a4 + 1;
    }
    if (iStack_a4 != 0) {
      if (DAT_005f7e50 == 0) {
        DAT_00b5a8cc = (char)((longlong)(ulonglong)(byte)(DAT_00b5a8cc + 1) % (longlong)iStack_a4);
      }
      FUN_0052a910(&DAT_00c54ac0,0x56f0ec,0xc80f00,DAT_00b5a8cc);
      DAT_00b87eb0 = 1;
      DAT_00c4d70c = 3;
    }
    break;
  case 0x3e:
    iVar2 = thunk_FUN_004f6612(DAT_00c81684,&DAT_00c80fa0);
    if (iVar2 != 0) {
      DAT_00c80fa0 = 0;
      return iVar2;
    }
    break;
  case 0x3f:
    DAT_00c818b8 = 1;
    break;
  case 0x40:
    local_a0 = thunk_FUN_004f6774(DAT_00c81684,&DAT_00c81580);
    if (local_a0 != 0) {
      return local_a0;
    }
    iVar2 = FUN_0052e250(&DAT_00c81580,0x56f0f4,&DAT_00c80c00);
    if ((iVar2 == 0) || (iVar2 == -1)) {
      return 0xc;
    }
    DAT_00d1192c = DAT_00c80c00;
    if ((((DAT_00bdfa40 != 0) && (-1 < (int)DAT_00b87e30)) && ((int)DAT_00b87e30 < 4)) &&
       (DAT_01271060 == 8)) {
      DAT_00d1192c = DAT_00bdfa40 + -1;
    }
    break;
  case 0x41:
    local_a0 = thunk_FUN_004f6774(DAT_00c81684,&DAT_00c81580);
    if (local_a0 != 0) {
      return local_a0;
    }
    iVar2 = FUN_0052e250(&DAT_00c81580,0x56f0f8,&DAT_00c80c00);
    if ((iVar2 == 0) || (iVar2 == -1)) {
      return 0xc;
    }
    DAT_00bdfa60 = DAT_00c80c00;
    break;
  case 0x42:
    DAT_00b202e4 = 1;
    break;
  case 0x43:
    local_a0 = thunk_FUN_004f6774(DAT_00c81684,&DAT_00c81580);
    if (local_a0 != 0) {
      return local_a0;
    }
    iVar2 = FUN_0052e250(&DAT_00c81580,0x56f0fc,&DAT_00c80c00);
    if ((iVar2 == 0) || (iVar2 == -1)) {
      return 0xc;
    }
    _DAT_00bdf9d4 = DAT_00c80c00;
    break;
  case 0x44:
    local_a0 = thunk_FUN_004f6774(DAT_00c81684,&DAT_00c81580);
    if (local_a0 != 0) {
      return local_a0;
    }
    iVar2 = FUN_0052e250(&DAT_00c81580,0x56f100,&DAT_00c80c00);
    if ((iVar2 == 0) || (iVar2 == -1)) {
      return 0xc;
    }
    _DAT_00bdf9d0 = DAT_00c80c00 + 4;
    break;
  case 0x4d:
    local_a0 = thunk_FUN_004f6774(DAT_00c81684,&DAT_00c81580);
    if (local_a0 != 0) {
      return local_a0;
    }
    iStack_9c = FUN_0052e250(&DAT_00c81580,0x56f104,&DAT_00c80c00);
    if ((iStack_9c == 0) || (iStack_9c == -1)) {
      return 0xc;
    }
    local_a0 = thunk_FUN_004f6774(DAT_00c81684,&DAT_00c81580);
    if (local_a0 == 0) {
      iVar2 = FUN_0052e250(&DAT_00c81580,0x56f108,0xc80c04);
      if ((iVar2 == 0) || (iVar2 == -1)) {
        return 0xc;
      }
      DAT_00c814e4 = iRam00c80c04;
      DAT_00c814e0 = DAT_00c80c00;
    }
    else {
      DAT_00c814e4 = -1;
      DAT_00c814e0 = DAT_00c80c00;
    }
    break;
  case 0x4e:
    local_a0 = thunk_FUN_004f6774(DAT_00c81684,&DAT_00c81580);
    if (local_a0 != 0) {
      return local_a0;
    }
    iStack_9c = FUN_0052e250(&DAT_00c81580,0x56f10c,&DAT_00c80c00);
    if ((iStack_9c == 0) || (iStack_9c == -1)) {
      return 0xc;
    }
    local_a0 = thunk_FUN_004f6774(DAT_00c81684,&DAT_00c81580);
    if (local_a0 == 0) {
      iVar2 = FUN_0052e250(&DAT_00c81580,0x56f110,0xc80c04);
      if ((iVar2 == 0) || (iVar2 == -1)) {
        return 0xc;
      }
      DAT_00c81694 = iRam00c80c04;
      DAT_00c81690 = DAT_00c80c00;
    }
    else {
      DAT_00c81694 = -1;
      DAT_00c81690 = DAT_00c80c00;
    }
    break;
  case 0x53:
    if (DAT_005f7e50 == 0) {
      thunk_FUN_004bf2a0(s_MSCRIPT__Reusing_player_position_0056f094);
      puVar3 = &DAT_00c81700;
      puVar4 = &DAT_00c816c0;
      for (iVar2 = 0x10; iVar2 != 0; iVar2 = iVar2 + -1) {
        *puVar4 = *puVar3;
        puVar3 = puVar3 + 1;
        puVar4 = puVar4 + 1;
      }
    }
    DAT_00c81278 = 1;
    DAT_00ba52d0 = (int)ROUND(DAT_00c816c0);
    DAT_00c812c0 = DAT_00ba52d0;
    DAT_00c812c4 = 0xfffffe0c;
    DAT_00ba52d0 = (int)ROUND(DAT_00c816c8);
    DAT_00c812c8 = DAT_00ba52d0;
    DAT_00d06a04 = 1;
    break;
  case 0x54:
    DAT_00b20300 = 1;
    break;
  case 0x5e:
    local_a0 = thunk_FUN_004f6612(DAT_00c81684,&DAT_00c81580);
    if (local_a0 != 0) {
      return local_a0;
    }
    sVar1 = _strlen(&DAT_00c81580);
    iStack_94 = sVar1 + 1;
    thunk_FUN_004f8643(sVar1 + 9);
    local_c = *(undefined4 **)(DAT_00c8175c + -4 + DAT_00c81688 * 4);
    *local_c = 0x5e;
    local_c[1] = iStack_94;
    local_c = local_c + 2;
    thunk_FUN_005283b5(local_c,&DAT_00c81580,iStack_94);
    break;
  case 0x5f:
    DAT_00b201dc = 1;
    DAT_00b87e84 = 1;
    DAT_00b87e88 = 1;
    break;
  case 0x66:
    local_a0 = thunk_FUN_004f6774(DAT_00c81684,&DAT_00c81580);
    if (local_a0 != 0) {
      return local_a0;
    }
    FUN_0053fb50(&DAT_00c81580);
    iStack_9c = FUN_0052e250(&DAT_00c81580,0x56f114,&DAT_00c80c00);
    if ((iStack_9c != 0) && (iStack_9c != -1)) {
      local_a0 = thunk_FUN_004f6612(DAT_00c81684,&DAT_00c81580);
      if (local_a0 == 0) {
        sVar1 = _strlen(&DAT_00c81580);
        iStack_94 = sVar1 + 1;
        thunk_FUN_004f8643(sVar1 + 0xd);
        local_c = *(undefined4 **)(DAT_00c8175c + -4 + DAT_00c81688 * 4);
        *local_c = 0x66;
        local_c[1] = DAT_00c80c00 * 0x32;
        local_c[2] = iStack_94;
        local_c = local_c + 3;
        thunk_FUN_005283b5(local_c,&DAT_00c81580,iStack_94);
        return 0xb;
      }
      return local_a0;
    }
    return 0xc;
  case 0x69:
    local_a0 = thunk_FUN_004f6774(DAT_00c81684,&DAT_00c81580);
    if (local_a0 == 0) {
      func_0x00401438(&DAT_00c81580,DAT_00c81688,&DAT_00c81698);
      return 0xb;
    }
    return local_a0;
  case 0x6a:
    local_a0 = thunk_FUN_004f6774(DAT_00c81684,&DAT_00c81580);
    if (local_a0 == 0) {
      sVar1 = _strlen(&DAT_00c81580);
      iStack_94 = sVar1 + 1;
      thunk_FUN_004f8643(sVar1 + 9);
      local_c = *(undefined4 **)(DAT_00c8175c + -4 + DAT_00c81688 * 4);
      *local_c = 0x6a;
      local_c[1] = iStack_94;
      local_c = local_c + 2;
      FUN_0052b100(local_c,&DAT_00c81580);
      return 0xb;
    }
    return local_a0;
  case 0x6b:
    local_90 = s_IfEqual__0056f118;
  case 0x6c:
    if (local_90 == (char *)0x0) {
      local_90 = s_IfNotEqual__0056f124;
    }
  case 0x6d:
    if (local_90 == (char *)0x0) {
      local_90 = s_IfLessThan__0056f134;
    }
  case 0x6e:
    if (local_90 == (char *)0x0) {
      local_90 = s_IfGreaterThan__0056f144;
    }
  case 0x6f:
    if (local_90 == (char *)0x0) {
      local_90 = s_IfLessOrEqual__0056f154;
    }
  case 0x70:
    if (local_90 == (char *)0x0) {
      local_90 = s_IfGreaterOrEqual__0056f164;
    }
    local_a0 = thunk_FUN_004f6774(DAT_00c81684,&DAT_00c81580);
    if (local_a0 != 0) {
      return local_a0;
    }
    FUN_0053fb50(&DAT_00c81580);
    iVar2 = thunk_FUN_004f64dd(&DAT_00c81580);
    if (iVar2 == -1) {
      FUN_0052a910(auStack_8c,s__sVariable_not_found__0056f178,local_90);
      thunk_FUN_004bf2a0(auStack_8c);
      return 0xc;
    }
    local_a0 = thunk_FUN_004f6774(DAT_00c81684,&DAT_00c81580);
    if (local_a0 == 0) {
      FUN_0053fb50(&DAT_00c81580);
      iStack_9c = FUN_0052e250(&DAT_00c81580,0x56f190,&DAT_00c80c00);
      if ((iStack_9c != 0) && (iStack_9c != -1)) {
        thunk_FUN_004f8643(0xc);
        puVar3 = *(undefined4 **)(DAT_00c8175c + -4 + DAT_00c81688 * 4);
        *puVar3 = *(undefined4 *)(param_1 + 0x104);
        puVar3[1] = iVar2;
        puVar3[2] = DAT_00c80c00;
        return 0xb;
      }
      return 0xc;
    }
    return local_a0;
  case 0x71:
    local_a0 = thunk_FUN_004f6774(DAT_00c81684,&DAT_00c81580);
    if (local_a0 == 0) {
      sVar1 = _strlen(&DAT_00c81580);
      iStack_94 = sVar1 + 1;
      thunk_FUN_004f8643(sVar1 + 9);
      local_c = *(undefined4 **)(DAT_00c8175c + -4 + DAT_00c81688 * 4);
      *local_c = 0x71;
      local_c[1] = iStack_94;
      local_c = local_c + 2;
      FUN_0052b100(local_c,&DAT_00c81580);
      return 0xb;
    }
    return local_a0;
  case 0x73:
    local_a0 = thunk_FUN_004f6612(DAT_00c81684,&DAT_00c81580);
    if (local_a0 != 0) {
      return local_a0;
    }
    sVar1 = _strlen(&DAT_00c81580);
    iStack_94 = sVar1 + 1;
    thunk_FUN_004f8643(sVar1 + 9);
    local_c = *(undefined4 **)(DAT_00c8175c + -4 + DAT_00c81688 * 4);
    *local_c = 0x73;
    local_c[1] = iStack_94;
    local_c = local_c + 2;
    thunk_FUN_005283b5(local_c,&DAT_00c81580,iStack_94);
    break;
  case 0x86:
    if (DAT_005f7e50 == 0) {
      func_0x00401a28(DAT_00b87e30 & 3);
    }
    return 0xb;
  case 0x87:
    local_a0 = thunk_FUN_004f6774(DAT_00c81684,&DAT_00c81580);
    if (local_a0 != 0) {
      return local_a0;
    }
    FUN_0053fb50(&DAT_00c81580);
    iStack_9c = FUN_0052e250(&DAT_00c81580,0x56f194,&DAT_00c80c00);
    if ((iStack_9c != 0) && (iStack_9c != -1)) {
      if (4 < DAT_00c80c00) {
        DAT_00c80c00 = 4;
      }
      local_8 = 0;
      while( true ) {
        if (DAT_00c80c00 <= local_8) {
          DAT_00b20368 = DAT_00c80c00;
          for (local_8 = 0; local_8 < DAT_00c80c00; local_8 = local_8 + 1) {
            *(undefined4 *)(&DAT_00d11830 + local_8 * 4) = *(undefined4 *)(local_8 * 4 + 0xc80c04);
          }
          return 0xb;
        }
        local_a0 = thunk_FUN_004f6774(DAT_00c81684,&DAT_00c81580);
        if (local_a0 != 0) break;
        FUN_0053fb50(&DAT_00c81580);
        iStack_9c = FUN_0052e250(&DAT_00c81580,0x56f198,local_8 * 4 + 0xc80c04);
        if ((iStack_9c == 0) || (iStack_9c == -1)) {
          return 0xc;
        }
        local_8 = local_8 + 1;
      }
      return local_a0;
    }
    return 0xc;
  case 0x88:
    DAT_00d1192c = DAT_00b87e54;
    return 0xb;
  case 0x89:
  case 0x8a:
    local_a0 = thunk_FUN_004f6612(DAT_00c81684,&DAT_00c81580);
    if (local_a0 == 0) {
      sVar1 = _strlen(&DAT_00c81580);
      iStack_94 = sVar1 + 1;
      thunk_FUN_004f8643(sVar1 + 9);
      local_c = *(undefined4 **)(DAT_00c8175c + -4 + DAT_00c81688 * 4);
      *local_c = *(undefined4 *)(param_1 + 0x104);
      local_c[1] = iStack_94;
      local_c = local_c + 2;
      thunk_FUN_005283b5(local_c,&DAT_00c81580,iStack_94);
      return 0xb;
    }
    return local_a0;
  case 0x8d:
    local_a0 = thunk_FUN_004f6774(DAT_00c81684,&DAT_00c81580);
    if (local_a0 != 0) {
      return local_a0;
    }
    FUN_0053fb50(&DAT_00c81580);
    iStack_9c = FUN_0052e250(&DAT_00c81580,0x56f19c,&DAT_00c80c00);
    if ((iStack_9c != 0) && (iStack_9c != -1)) {
      local_a0 = thunk_FUN_004f6612(DAT_00c81684,&DAT_00c81580);
      if (local_a0 == 0) {
        sVar1 = _strlen(&DAT_00c81580);
        iStack_94 = sVar1 + 1;
        thunk_FUN_004f8643(sVar1 + 0xd);
        local_c = *(undefined4 **)(DAT_00c8175c + -4 + DAT_00c81688 * 4);
        *local_c = *(undefined4 *)(param_1 + 0x104);
        local_c[1] = DAT_00c80c00;
        local_c[2] = iStack_94;
        local_c = local_c + 3;
        thunk_FUN_005283b5(local_c,&DAT_00c81580,iStack_94);
        return 0xb;
      }
      return local_a0;
    }
    return 0xc;
  case 0x96:
    local_a0 = thunk_FUN_004f6774(DAT_00c81684,&DAT_00c81580);
    if (local_a0 != 0) {
      return local_a0;
    }
    iVar2 = FUN_0052e250(&DAT_00c81580,0x56f1a0,&DAT_00c80c00);
    if ((iVar2 == 0) || (iVar2 == -1)) {
      return 0xc;
    }
    DAT_00575efc = DAT_00c80c00;
    break;
  case 0x97:
    DAT_00b87ea0 = 1;
  }
  return 0xb;
}


// 004f8485

int FUN_004f8485(undefined *param_1,char *param_2)

{
  undefined4 *puVar1;
  int iVar2;
  size_t sVar3;
  int local_c;
  
  local_c = 0;
  if (param_2 == (char *)0x0) {
    param_2 = s_EVENTSCRIPT_0056dc10;
    while ((*(int *)(param_2 + 0x20) != 0x7f && (iVar2 = _strcmp(&DAT_00c81580,param_2), iVar2 != 0)
           )) {
      local_c = local_c + 1;
      param_2 = param_2 + 0x30;
    }
    sVar3 = _strlen(param_2);
    if (sVar3 == 0) {
      return 9;
    }
    param_1 = &DAT_00563ba0;
  }
  if (*(int *)(param_1 + 0x104) != 2) {
    return 9;
  }
  if (*(int *)(param_2 + 0x20) == 1) {
    iVar2 = thunk_FUN_004f6612(DAT_00c81684,&DAT_00c81580);
    if (iVar2 != 0) {
      return iVar2;
    }
    if (local_c == 0) {
      thunk_FUN_004f8a2d(0,&DAT_00c81580);
      return 0;
    }
    sVar3 = _strlen(&DAT_00c81580);
    thunk_FUN_004f8643(sVar3 + 9);
    puVar1 = *(undefined4 **)(DAT_00c8175c + -4 + DAT_00c81688 * 4);
    *puVar1 = 2;
    puVar1[1] = local_c;
    FUN_0052b100(puVar1 + 2,&DAT_00c81580);
  }
  else {
    iVar2 = thunk_FUN_004f87e0(param_1);
    if (iVar2 != 0) {
      return iVar2;
    }
    thunk_FUN_004f8643(0xc);
    puVar1 = *(undefined4 **)(DAT_00c8175c + -4 + DAT_00c81688 * 4);
    *puVar1 = 2;
    puVar1[1] = local_c;
    puVar1[2] = DAT_00c80c00;
  }
  return 0;
}


// 004f8643

undefined4 FUN_004f8643(undefined4 param_1)

{
  int iVar1;
  undefined4 uVar2;
  int iVar3;
  int local_c;
  
  iVar1 = thunk_FUN_004d8db4(DAT_00c81688 * 4 + 4,s_D__Driver_Game_MScript_c_0056f1a4,0xb3f);
  if (iVar1 == 0) {
    uVar2 = 3;
  }
  else {
    iVar3 = thunk_FUN_004d8db4(param_1,s_D__Driver_Game_MScript_c_0056f1c0,0xb43);
    if (iVar3 == 0) {
      thunk_FUN_004d8f30(iVar1);
      uVar2 = 3;
    }
    else {
      for (local_c = 0; local_c < DAT_00c81688; local_c = local_c + 1) {
        *(undefined4 *)(iVar1 + local_c * 4) = *(undefined4 *)(DAT_00c8175c + local_c * 4);
      }
      *(int *)(iVar1 + local_c * 4) = iVar3;
      if (DAT_00c8175c != 0) {
        thunk_FUN_004d8f30(DAT_00c8175c);
      }
      DAT_00c81688 = DAT_00c81688 + 1;
      uVar2 = 0;
      DAT_00c8175c = iVar1;
    }
  }
  return uVar2;
}


// 004f8735

char * FUN_004f8735(undefined4 param_1)

{
  char *pcVar1;
  
  switch(param_1) {
  case 0:
    pcVar1 = s_No_errors_found_0056f1dc;
    break;
  default:
    pcVar1 = s_Unknown_error_code_0056f2f8;
    break;
  case 2:
    pcVar1 = s_Word_value_has_been_retrieved_0056f1ec;
    break;
  case 3:
    pcVar1 = s_Out_of_memory_0056f20c;
    break;
  case 4:
    pcVar1 = s_End_of_file_reached_0056f21c;
    break;
  case 5:
    pcVar1 = s_Specified_file_was_not_found_0056f230;
    break;
  case 6:
    pcVar1 = s_Unexpected_comma_0056f250;
    break;
  case 7:
    pcVar1 = s_Unexpected_end_of_file_0056f264;
    break;
  case 8:
    pcVar1 = s_Unexpected_end_of_line_0056f27c;
    break;
  case 9:
    pcVar1 = s_Unrecognised_command_0056f294;
    break;
  case 10:
    pcVar1 = s_End_of_line_reached_0056f2ac;
    break;
  case 0xb:
    pcVar1 = s_Compilation_completed_successful_0056f2c0;
    break;
  case 0xc:
    pcVar1 = s_Illegal_parameter_0056f2e4;
  }
  return pcVar1;
}


// 004f87e0

int FUN_004f87e0(int param_1)

{
  int iVar1;
  int local_8;
  
  local_8 = 0;
  while( true ) {
    if (*(int *)(param_1 + 0x100) <= local_8) {
      return 0;
    }
    iVar1 = thunk_FUN_004f6774(DAT_00c81684,&DAT_00c81580);
    if (iVar1 != 0) break;
    iVar1 = FUN_0052e250(&DAT_00c81580,&DAT_0056f30c,&DAT_00c80c00 + local_8);
    if ((iVar1 == 0) || (iVar1 == -1)) {
      return 0xc;
    }
    local_8 = local_8 + 1;
  }
  return iVar1;
}


// 004f8862

void FUN_004f8862(int param_1,char *param_2)

{
  char cVar1;
  char *pcVar2;
  int local_14;
  char *local_c;
  char *local_8;
  
  if (*(int *)(param_1 + 0x20) == 1) {
    local_14 = 0;
    local_c = param_2;
    local_8 = param_2;
    while (cVar1 = *local_8, local_8 = local_8 + 1, cVar1 != '\0') {
      local_14 = local_14 + 1;
    }
    pcVar2 = (char *)thunk_FUN_004d8db4(local_14 + 1,s_D__Driver_Game_MScript_c_0056f310,0xbc1);
    local_8 = pcVar2;
    if (pcVar2 != (char *)0x0) {
      do {
        *local_8 = *local_c;
        cVar1 = *local_8;
        local_8 = local_8 + 1;
        local_c = local_c + 1;
      } while (cVar1 != '\0');
      if (*(int *)(param_1 + 0x24) != 0) {
        thunk_FUN_004d8f30(*(undefined4 *)(param_1 + 0x24));
        *(undefined4 *)(param_1 + 0x24) = 0;
      }
      *(char **)(param_1 + 0x24) = pcVar2;
    }
  }
  return;
}


// 004f892a

void FUN_004f892a(void)

{
  int local_c;
  char *local_8;
  
  local_c = 0;
  for (local_8 = s_EVENTSCRIPT_0056dc10; *(int *)(local_8 + 0x20) != 0x7f; local_8 = local_8 + 0x30)
  {
    if (*(int *)(local_8 + 0x20) == 1) {
      thunk_FUN_004f8a2d(local_c,*(undefined4 *)(local_8 + 0x28));
    }
    else if (*(int *)(local_8 + 0x20) == 3) {
      thunk_FUN_004f89b7(local_c,*(undefined4 *)(local_8 + 0x2c));
    }
    else if (*(int *)(local_8 + 0x20) == 4) {
      thunk_FUN_004f89eb(local_c,*(undefined4 *)(local_8 + 0x2c));
    }
    local_c = local_c + 1;
  }
  return;
}


// 004f89b7

void FUN_004f89b7(int param_1,undefined4 param_2)

{
  if ((&DAT_0056dc30)[param_1 * 0xc] != 1) {
    *(undefined4 *)(&DAT_0056dc34)[param_1 * 0xc] = param_2;
  }
  return;
}


// 004f89eb

/* WARNING: Removing unreachable block (ram,0x004f8a18) */

void FUN_004f89eb(void)

{
  return;
}


// 004f8a2d

void FUN_004f8a2d(int param_1,char *param_2)

{
  size_t sVar1;
  int iVar2;
  
  if ((&DAT_0056dc30)[param_1 * 0xc] == 1) {
    sVar1 = _strlen(param_2);
    iVar2 = thunk_FUN_004d8db4(sVar1 + 1,s_D__Driver_Game_MScript_c_0056f32c,0xc38);
    if (iVar2 != 0) {
      if ((&DAT_0056dc34)[param_1 * 0xc] != 0) {
        thunk_FUN_004d8f30((&DAT_0056dc34)[param_1 * 0xc]);
        (&DAT_0056dc34)[param_1 * 0xc] = 0;
      }
      thunk_FUN_005283b5(iVar2,param_2,sVar1 + 1);
      (&DAT_0056dc34)[param_1 * 0xc] = iVar2;
    }
  }
  return;
}


// 004f8acc

void FUN_004f8acc(undefined4 param_1)

{
  if (DAT_00b31f40 == 0) {
    thunk_FUN_00523e50(param_1,0xd,0xffffffff);
  }
  else {
    thunk_FUN_00523e50(param_1,0xe,0xffffffff);
  }
  DAT_00b31f40 = ~DAT_00b31f40;
  return;
}


// 004f8b0a

undefined4 FUN_004f8b0a(char *param_1,int param_2,int *param_3)

{
  int *piVar1;
  undefined4 uVar2;
  int iVar3;
  int *piVar4;
  size_t sVar5;
  char *pcVar6;
  int local_8;
  
  piVar1 = (int *)thunk_FUN_004d8db4(8,s_D__Driver_Game_MScript_c_0056f348,0xc6f);
  if (piVar1 == (int *)0x0) {
    thunk_FUN_004bf2a0(s_Error__Unable_to_add_label__out_o_0056f364);
    uVar2 = 0;
  }
  else {
    *piVar1 = *param_3 + 1;
    iVar3 = thunk_FUN_004d8db4(*piVar1 << 2,s_D__Driver_Game_MScript_c_0056f390,0xc79);
    piVar1[1] = iVar3;
    if (piVar1[1] == 0) {
      thunk_FUN_004bf2a0(s_Error__Unable_to_add_label__out_o_0056f3ac);
      thunk_FUN_004d8f30(piVar1);
      uVar2 = 0;
    }
    else {
      piVar4 = (int *)thunk_FUN_004d8db4(8,s_D__Driver_Game_MScript_c_0056f3d8,0xc81);
      if (piVar4 == (int *)0x0) {
        thunk_FUN_004bf2a0(s_Error__Unable_to_add_label__out_o_0056f3f4);
        thunk_FUN_004d8f30(piVar1[1]);
        thunk_FUN_004d8f30(piVar1);
        uVar2 = 0;
      }
      else {
        uVar2 = 0xc8a;
        pcVar6 = s_D__Driver_Game_MScript_c_0056f420;
        sVar5 = _strlen(param_1);
        iVar3 = thunk_FUN_004d8db4(sVar5 + 1,pcVar6,uVar2);
        *piVar4 = iVar3;
        if (*piVar4 == 0) {
          thunk_FUN_004bf2a0(s_Error__Unable_to_add_label__out_o_0056f43c);
          thunk_FUN_004d8f30(piVar4);
          thunk_FUN_004d8f30(piVar1[1]);
          thunk_FUN_004d8f30(piVar1);
          uVar2 = 0;
        }
        else {
          FUN_0052b100(*piVar4,param_1);
          FUN_0053fb50(*piVar4);
          for (local_8 = 0; local_8 < *param_3; local_8 = local_8 + 1) {
            *(undefined4 *)(piVar1[1] + local_8 * 4) = *(undefined4 *)(param_3[1] + local_8 * 4);
          }
          if (param_3[1] != 0) {
            thunk_FUN_004d8f30(param_3[1]);
          }
          piVar4[1] = param_2;
          *(int **)(piVar1[1] + *param_3 * 4) = piVar4;
          iVar3 = piVar1[1];
          *param_3 = *piVar1;
          param_3[1] = iVar3;
          thunk_FUN_004d8f30(piVar1);
          uVar2 = 1;
        }
      }
    }
  }
  return uVar2;
}


// 004f8cfd

undefined4 __thiscall FUN_004f8cfd(undefined4 param_1,char *param_2,int *param_3)

{
  int iVar1;
  int iVar2;
  
  if (param_2 != (char *)0x0) {
    FUN_0053fb50(param_2,param_1);
    for (iVar2 = 0; iVar2 < *param_3; iVar2 = iVar2 + 1) {
      iVar1 = _strcmp(param_2,(char *)**(undefined4 **)(param_3[1] + iVar2 * 4));
      if (iVar1 == 0) {
        return *(undefined4 *)(*(int *)(param_3[1] + iVar2 * 4) + 4);
      }
    }
  }
  return 0xffffffff;
}


// 004f8d6d

void FUN_004f8d6d(int *param_1)

{
  int iVar1;
  int local_8;
  
  if (*param_1 != 0) {
    iVar1 = param_1[1];
    for (local_8 = 0; local_8 < *param_1; local_8 = local_8 + 1) {
      if (**(int **)(iVar1 + local_8 * 4) != 0) {
        thunk_FUN_004d8f30(**(undefined4 **)(iVar1 + local_8 * 4));
      }
      thunk_FUN_004d8f30(*(undefined4 *)(iVar1 + local_8 * 4));
    }
    if (iVar1 != 0) {
      thunk_FUN_004d8f30(iVar1);
    }
    *param_1 = 0;
    param_1[1] = 0;
  }
  return;
}


// 004f8e0c

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 FUN_004f8e0c(undefined4 *param_1)

{
  size_t sVar1;
  int iVar2;
  int iVar3;
  int *piVar4;
  undefined4 *puVar5;
  undefined4 *puVar6;
  bool bVar7;
  undefined1 auStack_304 [128];
  int iStack_284;
  int iStack_280;
  undefined1 auStack_27c [128];
  int iStack_1fc;
  int iStack_1f8;
  int iStack_1f4;
  int iStack_1f0;
  int iStack_1ec;
  int iStack_1e8;
  int iStack_1e4;
  int iStack_1e0;
  int iStack_1dc;
  int iStack_1d8;
  int iStack_1d4;
  int iStack_1d0;
  int iStack_1cc;
  int iStack_1c8;
  int iStack_1c4;
  int iStack_1c0;
  int iStack_1bc;
  int iStack_1b8;
  int iStack_1b4;
  int iStack_1b0;
  int iStack_1ac;
  int iStack_1a8;
  int iStack_1a0;
  int iStack_19c;
  undefined1 auStack_198 [32];
  int iStack_178;
  int iStack_174;
  int iStack_170;
  char *pcStack_16c;
  int *piStack_168;
  char *pcStack_164;
  int *piStack_160;
  char *pcStack_15c;
  int *piStack_158;
  char *pcStack_154;
  int *piStack_150;
  char *pcStack_14c;
  int *piStack_148;
  char *pcStack_144;
  int *piStack_140;
  int iStack_13c;
  int iStack_138;
  char *pcStack_134;
  int iStack_130;
  undefined4 *puStack_12c;
  int iStack_128;
  int iStack_124;
  int iStack_120;
  int iStack_11c;
  int iStack_118;
  undefined4 uStack_114;
  undefined4 uStack_110;
  undefined4 uStack_10c;
  undefined4 uStack_ac;
  int iStack_a8;
  int iStack_a4;
  int iStack_a0;
  undefined4 uStack_9c;
  undefined4 uStack_98;
  undefined4 uStack_94;
  undefined4 uStack_90;
  int iStack_8c;
  undefined4 uStack_88;
  undefined4 uStack_84;
  undefined4 uStack_80;
  undefined4 uStack_7c;
  undefined4 uStack_78;
  int iStack_54;
  int iStack_50;
  int iStack_4c;
  int iStack_48;
  int iStack_44;
  undefined4 uStack_40;
  undefined4 uStack_3c;
  undefined4 uStack_38;
  int iStack_34;
  undefined4 uStack_30;
  undefined4 uStack_2c;
  int iStack_28;
  int iStack_24;
  undefined4 uStack_20;
  int iStack_1c;
  undefined4 local_14;
  uint local_c;
  undefined4 local_8;
  
  local_14 = 0xd;
  local_c = 1;
  local_8 = *param_1;
  piVar4 = param_1 + 1;
  switch(local_8) {
  case 0:
    local_14 = 0;
    iStack_24 = *piVar4;
    uStack_2c = param_1[2];
    uStack_30 = param_1[3];
    func_0x0040170d(uStack_2c,uStack_30);
    *(uint *)((int)DAT_00c812b8 + 8) = *(uint *)((int)DAT_00c812b8 + 8) & 0xffffff7f;
    *(int *)((int)DAT_00c812b8 + 0x18) = iStack_24;
    *(undefined4 *)((int)DAT_00c812b8 + 0x1c) = 250000;
    break;
  case 1:
    local_c = 0;
    DAT_00c810c4 = DAT_00c810c4 | 0x8000;
    _DAT_012710a0 = 1;
    break;
  case 2:
    local_14 = 0;
    iStack_24 = *piVar4;
    if ((&DAT_0056dc30)[iStack_24 * 0xc] == 1) {
      thunk_FUN_004f8a2d(iStack_24,param_1 + 2);
    }
    else {
      thunk_FUN_004f89b7(iStack_24,param_1[2]);
    }
    break;
  case 3:
    local_14 = 0;
    thunk_FUN_004cfe69(CONCAT22((short)((uint)piVar4 >> 0x10),(short)*piVar4));
    break;
  case 4:
    local_14 = 0;
    thunk_FUN_004f8acc(*piVar4);
    break;
  case 5:
    local_14 = 0;
    _memset(DAT_00c812b8,0,0x48);
    break;
  case 6:
    local_14 = 0;
    DAT_00c810c4 = 3;
    *(undefined4 *)((int)DAT_00c812b8 + 8) = 0x80;
    *(undefined4 *)((int)DAT_00c812b8 + 0x14) = 1;
    *(undefined4 *)((int)DAT_00c812b8 + 0x10) = 0x400;
    *(undefined4 *)((int)DAT_00c812b8 + 4) = 1;
    break;
  case 7:
    if ((DAT_00c810c4 != 0) &&
       ((DAT_00c810c4 != 1 || ((*(uint *)((int)DAT_00c812b8 + 8) & 0x80) == 0)))) {
      bVar7 = DAT_00c810c4 == 0x7fff;
      if (bVar7) {
        DAT_00c810c4 = 0;
        local_14 = 0;
      }
      local_c = (uint)bVar7;
    }
    break;
  case 8:
    local_14 = 0;
    *DAT_00c812bc = 0;
    DAT_00c812bc[1] = 0x8c;
    break;
  case 9:
    local_14 = 0;
    func_0x00402806(DAT_00c812bc,*piVar4);
    break;
  case 10:
    DAT_00d118a8 = 1;
    break;
  case 0xb:
    DAT_00d118a8 = 0;
    break;
  case 0xc:
    local_14 = 0;
    *(int *)(&DAT_0056dc34)[*piVar4 * 0xc] = *(int *)(&DAT_0056dc34)[*piVar4 * 0xc] + 1;
    break;
  case 0xe:
    local_14 = 0;
    *(int *)(&DAT_0056dc34)[*piVar4 * 0xc] = *(int *)(&DAT_0056dc34)[*piVar4 * 0xc] + -1;
    break;
  case 0x10:
    local_14 = 0;
    *(int *)(&DAT_0056dc34)[*piVar4 * 0xc] = *(int *)(&DAT_0056dc34)[*piVar4 * 0xc] + param_1[2];
    break;
  case 0x11:
    local_14 = 0;
    *(int *)(&DAT_0056dc34)[*piVar4 * 0xc] = *(int *)(&DAT_0056dc34)[*piVar4 * 0xc] - param_1[2];
    break;
  case 0x12:
    local_14 = 0;
    *(uint *)((int)DAT_00c812b8 + 0x10) = *(uint *)((int)DAT_00c812b8 + 0x10) | 0x100;
    *(undefined4 *)((int)DAT_00c812b8 + 0xc) = 0;
    break;
  case 0x14:
    local_14 = 0;
    iStack_1c = *piVar4;
    param_1 = param_1 + 2;
    if ((iStack_1c != 0) && (DAT_00bdfa48 == 0)) {
      iStack_34 = (iStack_1c + -1) * 0x355 + 0x2aa;
      if (DAT_00d11a5c < iStack_34) {
        DAT_00d11a5c = iStack_34;
      }
      DAT_00d11a48 = DAT_00b87e3c + 1;
    }
    while (iStack_1c != 0) {
      uStack_40 = *param_1;
      uStack_38 = param_1[1];
      uStack_3c = param_1[2];
      param_1 = param_1 + 3;
      iStack_1c = iStack_1c + -1;
      func_0x00402937(uStack_40,uStack_38,uStack_3c);
    }
    break;
  case 0x15:
    local_14 = 0;
    break;
  case 0x16:
    local_14 = 0;
    DAT_00c810d0 = *piVar4;
    uStack_20 = param_1[2];
    thunk_FUN_005283b5(&DAT_00c81168,param_1 + 3,uStack_20);
    break;
  case 0x17:
    local_14 = 0;
    DAT_00c810c8 = 0;
    DAT_00c810c4 = 0x80f1;
    *(uint *)((int)DAT_00c812b8 + 0x10) = *(uint *)((int)DAT_00c812b8 + 0x10) & 0xfffffffb;
    _DAT_012710a0 = 1;
    puVar5 = (undefined4 *)((int)DAT_00c812b8 + 0x30);
    puVar6 = &DAT_01271070;
    for (iVar2 = 6; iVar2 != 0; iVar2 = iVar2 + -1) {
      *puVar6 = *puVar5;
      puVar5 = puVar5 + 1;
      puVar6 = puVar6 + 1;
    }
    break;
  case 0x18:
    if (iRam00c810d4 == 0) {
      iRam00c810d4 = *piVar4 * 0x32;
    }
    else {
      iRam00c810d4 = iRam00c810d4 + -1;
      if (iRam00c810d4 == 0) {
        local_14 = 0;
        break;
      }
    }
    local_c = 0;
    break;
  case 0x19:
    local_14 = 0;
    iStack_28 = *piVar4;
    uStack_20 = param_1[2];
    if (iStack_28 < 10) {
      *(undefined4 *)(&DAT_00c80ce0 + iStack_28 * 0x34) = uStack_20;
      (&DAT_00c80cf4)[iStack_28 * 0xd] = param_1[3];
      (&DAT_00c80cfc)[iStack_28 * 0xd] = param_1[4];
      (&DAT_00c80d04)[iStack_28 * 0xd] = 0;
      (&DAT_00c80d08)[iStack_28 * 0xd] = 0;
      (&DAT_00c80d0c)[iStack_28 * 0xd] = 0;
    }
    else {
      thunk_FUN_004bf2a0(s_SetTarget__Illegal_target_index_i_0056f468);
    }
    break;
  case 0x1a:
    local_14 = 0;
    iStack_28 = *piVar4;
    if (iStack_28 < 10) {
      (&DAT_00c80cf0)[iStack_28 * 0xd] = (&DAT_00c80cf0)[iStack_28 * 0xd] | 1;
    }
    else {
      thunk_FUN_004bf2a0(s_EnableTarget__Illegal_target_ind_0056f49c);
    }
    break;
  case 0x1b:
    local_14 = 0;
    iStack_28 = *piVar4;
    if (iStack_28 < 10) {
      (&DAT_00c80cf0)[iStack_28 * 0xd] = (&DAT_00c80cf0)[iStack_28 * 0xd] & 0xfffffffe;
    }
    else {
      thunk_FUN_004bf2a0(s_DisableTarget__Illegal_target_in_0056f4d4);
    }
    break;
  case 0x1c:
    local_14 = 0;
    if (DAT_01271060 == 2) {
      *(uint *)((int)DAT_00c812b8 + 0x34) = *(uint *)((int)DAT_00c812b8 + 0x34) & 0xfffffff7;
    }
    else {
      DAT_00c812bc[1] = DAT_00c812bc[1] & 0xfffffff7;
    }
    break;
  case 0x1d:
    local_14 = 0;
    if ((DAT_00c812bc[1] & 4U) != 0) {
      DAT_00c812bc[1] = DAT_00c812bc[1] | 8;
    }
    break;
  case 0x21:
    iStack_50 = *piVar4;
    iStack_44 = param_1[2];
    iStack_48 = param_1[3];
    iStack_4c = param_1[4];
    local_14 = 0;
    thunk_FUN_00523cda(iStack_50,0xc,(float)iStack_44,(float)iStack_48,(float)iStack_4c);
    break;
  case 0x23:
    local_14 = 0;
    iRam00c810dc = *piVar4;
    break;
  case 0x24:
    local_14 = 0;
    DAT_00c810d8 = DAT_00c810d8 | 1;
    break;
  case 0x25:
    local_14 = 0;
    DAT_00c810d8 = DAT_00c810d8 & 0xfffffffe;
    break;
  case 0x26:
    local_14 = 0;
    DAT_0112b25c = *piVar4;
    break;
  case 0x29:
    local_14 = 0;
    iStack_28 = *piVar4;
    iStack_54 = param_1[2];
    if (iStack_28 < 10) {
      if (iStack_54 == -1) {
        (&DAT_00c80cf0)[iStack_28 * 0xd] = (&DAT_00c80cf0)[iStack_28 * 0xd] & 0xfffffff7;
      }
      else {
        (&DAT_00c80cf0)[iStack_28 * 0xd] = (&DAT_00c80cf0)[iStack_28 * 0xd] | 8;
        (&DAT_00c80cec)[iStack_28 * 0xd] = iStack_54;
        (&DAT_00c80d04)[iStack_28 * 0xd] = 0;
        (&DAT_00c80d08)[iStack_28 * 0xd] = 0;
        (&DAT_00c80d0c)[iStack_28 * 0xd] = 0;
      }
    }
    else {
      thunk_FUN_004bf2a0(s_TargetEvent__Illegal_target_inde_0056f50c);
    }
    break;
  case 0x2a:
    local_14 = 0;
    iVar2 = *piVar4;
    if (iVar2 < 5) {
      *(float *)(iVar2 * 0x28 + 0xc818c8) = (float)(int)param_1[2];
      *(float *)(iVar2 * 0x28 + 0xc818cc) = (float)(int)param_1[3];
      *(float *)(iVar2 * 0x28 + 0xc818d0) = (float)(int)param_1[4];
    }
    break;
  case 0x2b:
    local_14 = 0;
    iVar2 = *piVar4;
    if (iVar2 < 5) {
      *(undefined4 *)(iVar2 * 0x28 + 0xc818d8) = param_1[2];
      *(undefined4 *)(iVar2 * 0x28 + 0xc818dc) = param_1[3];
      *(undefined4 *)(iVar2 * 0x28 + 0xc818e0) = param_1[4];
    }
    break;
  case 0x2c:
    local_14 = 0;
    if (*piVar4 < 5) {
      *(undefined4 *)(&DAT_00c818c0 + *piVar4 * 0x28) = param_1[2];
    }
    break;
  case 0x2d:
    local_14 = 0;
    if (*piVar4 < 5) {
      *(float *)(*piVar4 * 0x28 + 0xc818c4) = (float)(int)param_1[2];
    }
    break;
  case 0x2e:
    local_14 = 0;
    if (*piVar4 < 5) {
      *(undefined4 *)(&DAT_00c80f80 + *piVar4 * 4) = 1;
    }
    break;
  case 0x2f:
    local_14 = 0;
    if (*piVar4 < 5) {
      *(undefined4 *)(&DAT_00c80f80 + *piVar4 * 4) = 0;
    }
    break;
  case 0x30:
    local_14 = 0;
    DAT_00575f30 = 0;
    break;
  case 0x31:
    local_14 = 0;
    DAT_0112b268 = 0;
    break;
  case 0x32:
    local_14 = 0;
    DAT_0112b268 = 1;
    break;
  case 0x33:
    local_14 = 0;
    _DAT_00c80f60 = *piVar4;
    break;
  case 0x34:
    local_14 = 0;
    DAT_00d078aa = (ushort)*piVar4 & 0xfff;
    break;
  case 0x35:
    if ((*piVar4 != 0) && (DAT_00bdfa48 == 0)) {
      iVar2 = (*piVar4 + -1) * 0x355 + 0x2aa;
      if (DAT_00d11a5c < iVar2) {
        DAT_00d11a5c = iVar2;
      }
      DAT_00d11a48 = DAT_00b87e3c + 1;
    }
    local_14 = 0;
    break;
  case 0x36:
    iStack_8c = *piVar4;
    uStack_90 = param_1[2];
    uStack_7c = param_1[3];
    uStack_78 = param_1[4];
    uStack_80 = param_1[5];
    uStack_84 = param_1[6];
    uStack_88 = param_1[7];
    local_14 = 0;
    if (iStack_8c < 10) {
      func_0x00402563(uStack_90,uStack_7c,uStack_78,uStack_80,uStack_84,uStack_88);
      *(undefined4 *)(&DAT_00c80ce4 + iStack_8c * 0x34) = uRam00c81110;
      *(undefined4 *)(&DAT_00c80ce8 + iStack_8c * 0x34) = uStack_90;
      (&DAT_00c80cf0)[iStack_8c * 0xd] = 0x100;
    }
    else {
      thunk_FUN_004bf2a0(s_Script_Error__AddCivCar___Illega_0056f544);
    }
    break;
  case 0x37:
    local_14 = 0;
    DAT_00c810d8 = DAT_00c810d8 | 4;
    break;
  case 0x38:
    local_14 = 0;
    DAT_00c810d8 = DAT_00c810d8 & 0xfffffffb;
    break;
  case 0x39:
    _DAT_00c810f4 = param_1[2];
    DAT_00c810d8 = DAT_00c810d8 | 8;
    DAT_00c810f0 = *piVar4 * 0x32;
    break;
  case 0x3a:
    local_14 = 0;
    DAT_00c812bc[1] = 0;
    break;
  case 0x3b:
    local_14 = 0;
    *DAT_00c812bc = *DAT_00c812bc + *piVar4 * 0x32;
    break;
  case 0x3c:
    local_14 = 0;
    *DAT_00c812bc = *DAT_00c812bc + *piVar4 * -0x32;
    break;
  case 0x45:
    local_14 = 0;
    DAT_00c82510 = (float)*piVar4;
    DAT_00c82514 = (float)(int)param_1[2];
    DAT_00c82518 = (float)(int)param_1[3];
    break;
  case 0x46:
    local_14 = 0;
    DAT_00c824d8 = *piVar4;
    break;
  case 0x47:
    local_14 = 0;
    DAT_00c82528 = *piVar4;
    break;
  case 0x48:
    local_14 = 0;
    DAT_00c824d4 = 1;
    break;
  case 0x49:
    local_14 = 0;
    DAT_00c824d4 = 0;
    break;
  case 0x4a:
    local_14 = 0;
    DAT_00c82524 = 1;
    break;
  case 0x4b:
    if ((DAT_00c824a0 == 0) && (DAT_00c82524 == 0)) {
      local_14 = 0;
    }
    else {
      local_c = 0;
    }
    break;
  case 0x4c:
    local_14 = 0;
    DAT_00c82434 = *piVar4;
    DAT_00c82500 = -200 - DAT_00c82434;
    break;
  case 0x4f:
    local_14 = 0;
    DAT_00c824d0 = *piVar4;
    break;
  case 0x50:
    iStack_a8 = *piVar4;
    uStack_ac = param_1[2];
    uStack_98 = param_1[3];
    uStack_94 = param_1[4];
    uStack_9c = param_1[5];
    DAT_00ba52d0 = (int)ROUND(_DAT_00c80f50);
    iVar2 = DAT_00ba52d0;
    iStack_a0 = DAT_00ba52d0;
    DAT_00ba52d0 = (int)ROUND(_DAT_00c80f58);
    iStack_a4 = DAT_00ba52d0;
    local_14 = 0;
    func_0x00402563(uStack_ac,uStack_98,uStack_94,uStack_9c,iVar2,DAT_00ba52d0);
    *(undefined4 *)(&DAT_00c80ce4 + iStack_a8 * 0x34) = uRam00c81110;
    *(undefined4 *)(&DAT_00c80ce8 + iStack_a8 * 0x34) = uStack_ac;
    (&DAT_00c80cf0)[iStack_a8 * 0xd] = 0x100;
    break;
  case 0x51:
    local_14 = 0;
    DAT_00c824b0 = _DAT_00c80f50 + _DAT_00c80cb0;
    DAT_00c824b4 = _DAT_00c80f54;
    DAT_00c82514 = _DAT_00c80f54;
    DAT_00c824b8 = _DAT_00c80f58 + _DAT_00c80cb8;
    DAT_00c82510 = DAT_00c824b0;
    DAT_00c82518 = DAT_00c824b8;
    break;
  case 0x52:
    local_14 = 0;
    _DAT_00c80cb0 = (float)*piVar4;
    _DAT_00c80cb8 = (float)(int)param_1[2];
    break;
  case 0x55:
    local_14 = 0;
    iStack_28 = *piVar4;
    if (iStack_28 < 10) {
      (&DAT_00c80cf0)[iStack_28 * 0xd] = (&DAT_00c80cf0)[iStack_28 * 0xd] & 0xffffffef;
    }
    else {
      thunk_FUN_004bf2a0(s_EnablePulse__Illegal_target_inde_0056f580);
    }
    break;
  case 0x56:
    local_14 = 0;
    iStack_28 = *piVar4;
    if (iStack_28 < 10) {
      (&DAT_00c80cf0)[iStack_28 * 0xd] = (&DAT_00c80cf0)[iStack_28 * 0xd] | 0x10;
    }
    else {
      thunk_FUN_004bf2a0(s_DisablePulse__Illegal_target_ind_0056f5b8);
    }
    break;
  case 0x57:
    local_14 = 0;
    iStack_28 = *piVar4;
    if (iStack_28 < 10) {
      (&DAT_00c80cf0)[iStack_28 * 0xd] = (&DAT_00c80cf0)[iStack_28 * 0xd] & 0xffffffdf;
    }
    else {
      thunk_FUN_004bf2a0(s_EnableArrow__Illegal_target_inde_0056f5f0);
    }
    break;
  case 0x58:
    local_14 = 0;
    iStack_28 = *piVar4;
    if (iStack_28 < 10) {
      (&DAT_00c80cf0)[iStack_28 * 0xd] = (&DAT_00c80cf0)[iStack_28 * 0xd] | 0x20;
    }
    else {
      thunk_FUN_004bf2a0(s_DisableArrow__Illegal_target_ind_0056f628);
    }
    break;
  case 0x59:
    local_14 = 0;
    iStack_28 = *piVar4;
    if (iStack_28 < 10) {
      (&DAT_00c80cf0)[iStack_28 * 0xd] = (&DAT_00c80cf0)[iStack_28 * 0xd] & 0xffffffbf;
    }
    else {
      thunk_FUN_004bf2a0(s_EnableTrace__Illegal_target_inde_0056f660);
    }
    break;
  case 0x5a:
    local_14 = 0;
    iStack_28 = *piVar4;
    if (iStack_28 < 10) {
      (&DAT_00c80cf0)[iStack_28 * 0xd] = (&DAT_00c80cf0)[iStack_28 * 0xd] | 0x40;
    }
    else {
      thunk_FUN_004bf2a0(s_DisableTrace__Illegal_target_ind_0056f698);
    }
    break;
  case 0x5b:
    local_14 = 0;
    iStack_28 = *piVar4;
    if (iStack_28 < 10) {
      (&DAT_00c80cf0)[iStack_28 * 0xd] = (&DAT_00c80cf0)[iStack_28 * 0xd] & 0xffffff7f;
    }
    else {
      thunk_FUN_004bf2a0(s_EnableDetection__Illegal_target_i_0056f6d0);
    }
    break;
  case 0x5c:
    local_14 = 0;
    iStack_28 = *piVar4;
    if (iStack_28 < 10) {
      (&DAT_00c80cf0)[iStack_28 * 0xd] = (&DAT_00c80cf0)[iStack_28 * 0xd] | 0x80;
    }
    else {
      thunk_FUN_004bf2a0(s_DisableDetection__Illegal_target_0056f70c);
    }
    break;
  case 0x5d:
    local_14 = 0;
    iStack_28 = *piVar4;
    uStack_110 = param_1[2];
    uStack_114 = param_1[3];
    uStack_10c = param_1[4];
    if (iStack_28 < 10) {
      (&DAT_00c80d04)[iStack_28 * 0xd] = uStack_110;
      (&DAT_00c80d08)[iStack_28 * 0xd] = uStack_114;
      (&DAT_00c80d0c)[iStack_28 * 0xd] = uStack_10c;
    }
    else {
      thunk_FUN_004bf2a0(s_TargetArrow__Illegal_target_inde_0056f748);
    }
    break;
  case 0x5e:
    local_14 = 0;
    iStack_118 = *piVar4;
    thunk_FUN_004fbbfc(param_1 + 2);
    break;
  case 0x60:
    local_14 = 0;
    iStack_11c = *piVar4;
    func_0x0040281a(iStack_11c);
    break;
  case 0x61:
    DAT_00d026a0 = (float)*piVar4;
    DAT_00d02714 = param_1[2];
    DAT_00d026a4 = (float)DAT_00d02714;
    DAT_00d026a8 = (float)(int)param_1[3];
    DAT_00d02718 = param_1[4];
    DAT_00d02702 = (undefined2)DAT_00d02718;
    DAT_00d0271c = 0x7fffffff;
    DAT_00bdfa14 = 1;
    local_14 = 0;
    break;
  case 0x62:
    DAT_00d02648 = 1;
    local_14 = 0;
    break;
  case 99:
    DAT_00d0271c = *piVar4;
    local_14 = 0;
    break;
  case 100:
    local_14 = 0;
    iStack_120 = *piVar4;
    if (iStack_120 < 10) {
      (&DAT_00c80cf0)[iStack_120 * 0xd] = (&DAT_00c80cf0)[iStack_120 * 0xd] | 0x400;
    }
    else {
      thunk_FUN_004bf2a0(s_ToggleTailMessage__Illegal_targe_0056f780);
    }
    break;
  case 0x65:
    local_14 = 0;
    iStack_124 = *piVar4;
    if (iStack_124 < 10) {
      (&DAT_00c80cf0)[iStack_124 * 0xd] = (&DAT_00c80cf0)[iStack_124 * 0xd] & 0xfffffbff;
    }
    else {
      thunk_FUN_004bf2a0(s_ToggleTailMessage__Illegal_targe_0056f7bc);
    }
    break;
  case 0x66:
    local_14 = 0;
    iStack_128 = *piVar4;
    puStack_12c = param_1 + 3;
    func_0x00401df2(puStack_12c,iStack_128);
    break;
  case 0x67:
    local_14 = 0;
    if ((DAT_00c812bc[1] & 4U) != 0) {
      iStack_130 = *DAT_00c812bc;
      pcStack_134 = (char *)func_0x0040191a(*DAT_00c812bc);
      if (pcStack_134 != (char *)0x0) {
        DAT_00c810d0 = iStack_130 * 0x32;
        sVar1 = _strlen(pcStack_134);
        thunk_FUN_005283b5(&DAT_00c81168,pcStack_134,sVar1);
      }
    }
    break;
  case 0x68:
    local_14 = 0;
    thunk_FUN_004f5dcd();
    break;
  case 0x6a:
    iStack_13c = *piVar4;
    iStack_138 = func_0x004025f9(param_1 + 2,&DAT_00c81698);
    if (iStack_138 != -1) {
      DAT_00c80eec = iStack_138;
      return 0;
    }
    thunk_FUN_004bf2a0(s_Script_error_in_GOTO__Unknown_la_0056f7f8);
    break;
  case 0x6b:
    local_14 = 0;
    iVar2 = *piVar4;
    pcStack_144 = s_EVENTSCRIPT_0056dc10 + iVar2 * 0x30;
    piVar4 = param_1 + 2;
    piStack_140 = (int *)(&DAT_0056dc34)[iVar2 * 0xc];
    switch((&DAT_0056dc30)[iVar2 * 0xc]) {
    case 1:
      thunk_FUN_004bf2a0(s_IfEqual__Type_mismatch__cannot_c_0056f820);
      break;
    case 2:
      thunk_FUN_004bf2a0(s_IfEqual__Type_mismatch__cannot_c_0056f870);
      break;
    case 3:
      if (*piStack_140 != *piVar4) {
        local_c = 2;
      }
      break;
    case 4:
      if ((*piVar4 == 0) || (*piVar4 == 1)) {
        if (*piStack_140 != *piVar4) {
          local_c = 2;
        }
      }
      else {
        thunk_FUN_004bf2a0(s_IfEqual__Type_mismatch__cannot_c_0056f8c8);
      }
    }
    break;
  case 0x6c:
    local_14 = 0;
    iVar2 = *piVar4;
    pcStack_14c = s_EVENTSCRIPT_0056dc10 + iVar2 * 0x30;
    piVar4 = param_1 + 2;
    piStack_148 = (int *)(&DAT_0056dc34)[iVar2 * 0xc];
    switch((&DAT_0056dc30)[iVar2 * 0xc]) {
    case 1:
      thunk_FUN_004bf2a0(s_IfNotEqual__Type_mismatch__canno_0056f918);
      break;
    case 2:
      thunk_FUN_004bf2a0(s_IfNotEqual__Type_mismatch__canno_0056f96c);
      break;
    case 3:
      if (*piStack_148 == *piVar4) {
        local_c = 2;
      }
      break;
    case 4:
      if ((*piVar4 == 0) || (*piVar4 == 1)) {
        if (*piStack_148 == *piVar4) {
          local_c = 2;
        }
      }
      else {
        thunk_FUN_004bf2a0(s_IfNotEqual__Type_mismatch__canno_0056f9c8);
      }
    }
    break;
  case 0x6d:
    local_14 = 0;
    iVar2 = *piVar4;
    pcStack_15c = s_EVENTSCRIPT_0056dc10 + iVar2 * 0x30;
    piVar4 = param_1 + 2;
    piStack_158 = (int *)(&DAT_0056dc34)[iVar2 * 0xc];
    switch((&DAT_0056dc30)[iVar2 * 0xc]) {
    case 1:
      thunk_FUN_004bf2a0(s_IfLessThan__Type_mismatch__canno_0056fb2c);
      break;
    case 2:
      thunk_FUN_004bf2a0(s_IfLessThan__Type_mismatch__canno_0056fb80);
      break;
    case 3:
      if (*piVar4 <= *piStack_158) {
        local_c = 2;
      }
      break;
    case 4:
      if ((*piVar4 == 0) || (*piVar4 == 1)) {
        if (*piVar4 <= *piStack_158) {
          local_c = 2;
        }
      }
      else {
        thunk_FUN_004bf2a0(s_IfLessThan__Type_mismatch__canno_0056fbdc);
      }
    }
    break;
  case 0x6e:
    local_14 = 0;
    iVar2 = *piVar4;
    pcStack_154 = s_EVENTSCRIPT_0056dc10 + iVar2 * 0x30;
    piVar4 = param_1 + 2;
    piStack_150 = (int *)(&DAT_0056dc34)[iVar2 * 0xc];
    switch((&DAT_0056dc30)[iVar2 * 0xc]) {
    case 1:
      thunk_FUN_004bf2a0(s_IfGreaterThan__Type_mismatch__ca_0056fa1c);
      break;
    case 2:
      thunk_FUN_004bf2a0(s_IfGreaterThan__Type_mismatch__ca_0056fa74);
      break;
    case 3:
      if (*piStack_150 <= *piVar4) {
        local_c = 2;
      }
      break;
    case 4:
      if ((*piVar4 == 0) || (*piVar4 == 1)) {
        if (*piStack_150 <= *piVar4) {
          local_c = 2;
        }
      }
      else {
        thunk_FUN_004bf2a0(s_IfGreaterThan__Type_mismatch__ca_0056fad4);
      }
    }
    break;
  case 0x6f:
    local_14 = 0;
    iVar2 = *piVar4;
    pcStack_164 = s_EVENTSCRIPT_0056dc10 + iVar2 * 0x30;
    piVar4 = param_1 + 2;
    piStack_160 = (int *)(&DAT_0056dc34)[iVar2 * 0xc];
    switch((&DAT_0056dc30)[iVar2 * 0xc]) {
    case 1:
      thunk_FUN_004bf2a0(s_IfLessOrEqual__Type_mismatch__ca_0056fc30);
      break;
    case 2:
      thunk_FUN_004bf2a0(s_IfLessOrEqual__Type_mismatch__ca_0056fc88);
      break;
    case 3:
      if (*piVar4 < *piStack_160) {
        local_c = 2;
      }
      break;
    case 4:
      if ((*piVar4 == 0) || (*piVar4 == 1)) {
        if (*piVar4 < *piStack_160) {
          local_c = 2;
        }
      }
      else {
        thunk_FUN_004bf2a0(s_IfLessOrEqual__Type_mismatch__ca_0056fce8);
      }
    }
    break;
  case 0x70:
    local_14 = 0;
    iVar2 = *piVar4;
    pcStack_16c = s_EVENTSCRIPT_0056dc10 + iVar2 * 0x30;
    piVar4 = param_1 + 2;
    piStack_168 = (int *)(&DAT_0056dc34)[iVar2 * 0xc];
    switch((&DAT_0056dc30)[iVar2 * 0xc]) {
    case 1:
      thunk_FUN_004bf2a0(s_IfGreaterOrEqual__Type_mismatch__0056fd40);
      break;
    case 2:
      thunk_FUN_004bf2a0(s_IfGreaterOrEqual__Type_mismatch__0056fd98);
      break;
    case 3:
      if (*piStack_168 < *piVar4) {
        local_c = 2;
      }
      break;
    case 4:
      if ((*piVar4 == 0) || (*piVar4 == 1)) {
        if (*piStack_168 < *piVar4) {
          local_c = 2;
        }
      }
      else {
        thunk_FUN_004bf2a0(s_IfGreaterOrEqual__Type_mismatch__0056fdf8);
      }
    }
    break;
  case 0x71:
    local_14 = 0;
    if (DAT_00c80f7c < 100) {
      iStack_174 = *piVar4;
      iStack_170 = func_0x004025f9(param_1 + 2,&DAT_00c81698);
      if (iStack_170 != -1) {
        *(int *)(DAT_00c80f7c * 4 + 0xc81300) = DAT_00c80eec + 1;
        DAT_00c80eec = iStack_170;
        DAT_00c80f7c = DAT_00c80f7c + 1;
        return 0;
      }
      thunk_FUN_004bf2a0(s_Script_error__GoSub__Unknown_lab_0056fe80);
    }
    else {
      thunk_FUN_004bf2a0(s_Script_error__GoSub__Out_of_Stac_0056fe54);
    }
    break;
  case 0x72:
    local_14 = 0;
    if (0 < DAT_00c80f7c) {
      DAT_00c80eec = *(undefined4 *)((DAT_00c80f7c + -1) * 4 + 0xc81300);
      DAT_00c80f7c = DAT_00c80f7c + -1;
      return 0;
    }
    thunk_FUN_004bf2a0(s_Script_error__Return_without_GoS_0056fea4);
    break;
  case 0x73:
    local_14 = 0;
    iStack_178 = *piVar4;
    thunk_FUN_004bf2a0(param_1 + 2);
    break;
  case 0x74:
    local_14 = 0xb;
    DAT_00c81268 = func_0x00401c62();
    break;
  case 0x75:
    local_14 = 0xb;
    iStack_19c = *piVar4;
    FUN_0052a910(auStack_198,s_BANK_d_DSS_0056fec8,iStack_19c);
    thunk_FUN_00524496(auStack_198,0xf000);
    break;
  case 0x76:
    local_14 = 0xb;
    iStack_1a0 = *piVar4;
    thunk_FUN_004d611b(iStack_1a0 + 0xf000);
    break;
  case 0x77:
    if (((iRam00c810d4 == 0) || (iRam00c810d4 == *DAT_00c812bc)) &&
       (((iRam00c810d4 = *piVar4 * 0x32, (DAT_00c812bc[1] & 0x80U) != 0 &&
         (iRam00c810d4 <= *DAT_00c812bc)) ||
        (((DAT_00c812bc[1] & 8U) != 0 && (*DAT_00c812bc <= iRam00c810d4)))))) {
      iRam00c810d4 = 0;
      local_14 = 0;
    }
    else {
      local_c = 0;
    }
    break;
  case 0x78:
    local_14 = 0;
    DAT_00c824b0 = (float)*piVar4;
    DAT_00c824b4 = (float)(int)param_1[2];
    DAT_00c824b8 = (float)(int)param_1[3];
    break;
  case 0x79:
    local_14 = 0;
    DAT_00c824b0 = (float)*piVar4;
    DAT_00c824b4 = (float)(int)param_1[2];
    DAT_00c824b8 = (float)(int)param_1[3];
    DAT_00c82510 = DAT_00c824b0;
    DAT_00c82514 = DAT_00c824b4;
    DAT_00c82518 = DAT_00c824b8;
    break;
  case 0x7a:
    iVar2 = func_0x00401d0c();
    if (iVar2 == -1) {
      local_c = 0;
    }
    else {
      local_14 = 0;
      iRam00c8112c = *piVar4;
      iRam00c81128 = iVar2;
    }
    break;
  case 0x7b:
    iStack_1ac = *piVar4;
    iStack_1a8 = param_1[2];
    if (iStack_1a8 != -1) {
      local_14 = 0;
      DAT_00c810d0 = iStack_1ac * 0x32;
      FUN_0052b100(&DAT_00c81168,*(undefined4 *)(&DAT_00c55280 + iStack_1a8 * 4));
    }
    break;
  case 0x7c:
    local_14 = 0;
    iStack_1b4 = *piVar4;
    iStack_1b0 = param_1[2];
    if (iStack_1b0 != -1) {
      func_0x00401df2(*(undefined4 *)(&DAT_00c55280 + iStack_1b0 * 4),iStack_1b4);
    }
    break;
  case 0x7d:
    iStack_1b8 = *piVar4;
    if (iStack_1b8 != -1) {
      local_14 = 0;
      iStack_1bc = thunk_FUN_004f64dd(s_FAILEDMESSAGE_0056fed4);
      if (iStack_1bc != -1) {
        thunk_FUN_004f8862(s_EVENTSCRIPT_0056dc10 + iStack_1bc * 0x30,
                           *(undefined4 *)(&DAT_00c55280 + iStack_1b8 * 4));
      }
    }
    break;
  case 0x7e:
    iStack_1c0 = *piVar4;
    if (iStack_1c0 != -1) {
      local_14 = 0;
      iStack_1c4 = thunk_FUN_004f64dd(s_WINDOWMESSAGE_0056fee4);
      if (iStack_1c4 != -1) {
        thunk_FUN_004f8862(s_EVENTSCRIPT_0056dc10 + iStack_1c4 * 0x30,
                           *(undefined4 *)(&DAT_00c55280 + iStack_1c0 * 4));
      }
    }
    break;
  case 0x7f:
    iStack_1c8 = *piVar4;
    if (iStack_1c8 != -1) {
      local_14 = 0;
      iStack_1cc = thunk_FUN_004f64dd(s_LOSETAILMESSAGE_0056fef4);
      if (iStack_1cc != -1) {
        thunk_FUN_004f8862(s_EVENTSCRIPT_0056dc10 + iStack_1cc * 0x30,
                           *(undefined4 *)(&DAT_00c55280 + iStack_1c8 * 4));
      }
    }
    break;
  case 0x80:
    iStack_1d0 = *piVar4;
    if (iStack_1d0 != -1) {
      local_14 = 0;
      iStack_1d4 = thunk_FUN_004f64dd(s_SMASHEDMESSAGE_0056ff04);
      if (iStack_1d4 != -1) {
        thunk_FUN_004f8862(s_EVENTSCRIPT_0056dc10 + iStack_1d4 * 0x30,
                           *(undefined4 *)(&DAT_00c55280 + iStack_1d0 * 4));
      }
    }
    break;
  case 0x81:
    iStack_1d8 = *piVar4;
    if (iStack_1d8 != -1) {
      local_14 = 0;
      iStack_1dc = thunk_FUN_004f64dd(s_OUTOFRANGEMESSAGE_0056ff14);
      if (iStack_1dc != -1) {
        thunk_FUN_004f8862(s_EVENTSCRIPT_0056dc10 + iStack_1dc * 0x30,
                           *(undefined4 *)(&DAT_00c55280 + iStack_1d8 * 4));
      }
    }
    break;
  case 0x82:
    iStack_1e0 = *piVar4;
    if (iStack_1e0 != -1) {
      local_14 = 0;
      iStack_1e4 = thunk_FUN_004f64dd(s_CARGOTAWAYMESSAGE_0056ff28);
      if (iStack_1e4 != -1) {
        thunk_FUN_004f8862(s_EVENTSCRIPT_0056dc10 + iStack_1e4 * 0x30,
                           *(undefined4 *)(&DAT_00c55280 + iStack_1e0 * 4));
      }
    }
    break;
  case 0x83:
    iStack_1e8 = *piVar4;
    if (iStack_1e8 != -1) {
      local_14 = 0;
      iStack_1ec = thunk_FUN_004f64dd(s_OPPONENTBAR_0056ff3c);
      if (iStack_1ec != -1) {
        thunk_FUN_004f8862(s_EVENTSCRIPT_0056dc10 + iStack_1ec * 0x30,
                           *(undefined4 *)(&DAT_00c55280 + iStack_1e8 * 4));
      }
    }
    break;
  case 0x84:
    iStack_1f0 = *piVar4;
    if (iStack_1f0 != -1) {
      local_14 = 0;
      iStack_1f4 = thunk_FUN_004f64dd(s_DAMAGEBAR_0056ff48);
      if (iStack_1f4 != -1) {
        thunk_FUN_004f8862(s_EVENTSCRIPT_0056dc10 + iStack_1f4 * 0x30,
                           *(undefined4 *)(&DAT_00c55280 + iStack_1f0 * 4));
      }
    }
    break;
  case 0x85:
    iStack_1f8 = *piVar4;
    if (iStack_1f8 != -1) {
      local_14 = 0;
      iStack_1fc = thunk_FUN_004f64dd(s_FELONYBAR_0056ff54);
      if (iStack_1fc != -1) {
        thunk_FUN_004f8862(s_EVENTSCRIPT_0056dc10 + iStack_1fc * 0x30,
                           *(undefined4 *)(&DAT_00c55280 + iStack_1f8 * 4));
      }
    }
    break;
  case 0x89:
    local_14 = 0;
    iStack_280 = *piVar4;
    param_1 = param_1 + 2;
    iStack_284 = thunk_FUN_004ec837(param_1);
    if (iStack_284 == -1) {
      if (iStack_280 < 0x5a) {
        FUN_0052a910(auStack_27c,s_EnableModel__Unknown_model_name_p_0056ff60,param_1);
      }
      else {
        FUN_0052a910(auStack_27c,s_EnableModel__Unknown_model_name_p_0056ffa0,param_1);
      }
      thunk_FUN_004bf2a0(auStack_27c);
    }
    else {
      func_0x004014b0(iStack_284,1);
    }
    break;
  case 0x8a:
    local_14 = 0;
    iVar2 = *piVar4;
    iVar3 = thunk_FUN_004ec837(param_1 + 2);
    if (iVar3 == -1) {
      if (iVar2 < 0x5a) {
        FUN_0052a910(auStack_304,s_DisableModel__Unknown_model_name_0056ffdc,param_1 + 2);
      }
      else {
        FUN_0052a910(auStack_304,s_DisableModel__Unknown_model_name_00570020);
      }
      thunk_FUN_004bf2a0(auStack_304);
    }
    else {
      func_0x004014b0(iVar3,0);
    }
    break;
  case 0x8b:
    local_14 = 0;
    DAT_00c54d04 = 1;
    break;
  case 0x8c:
    local_14 = 0;
    DAT_00c54fc4 = 1;
    break;
  case 0x8d:
    local_14 = 0;
    iVar2 = *piVar4;
    iVar3 = thunk_FUN_004ec837(param_1 + 3);
    if (iVar3 == -1) {
      thunk_FUN_004bf2a0(s_ModelBonus__Error__Could_not_fin_0057005c);
    }
    else {
      *(int *)(&DAT_00bde780 + iVar3 * 4) = iVar2;
    }
    break;
  case 0x8e:
    func_0x00402766();
    break;
  case 0x8f:
    iVar2 = *piVar4;
    if (iVar2 != -1) {
      local_14 = 0;
      iVar3 = thunk_FUN_004f64dd(s_MAXSPEEDMESSAGE_00570090);
      if (iVar3 != -1) {
        thunk_FUN_004f8862(s_EVENTSCRIPT_0056dc10 + iVar3 * 0x30,
                           *(undefined4 *)(&DAT_00c55280 + iVar2 * 4));
      }
    }
    break;
  case 0x90:
    local_14 = 0;
    iRam00c81138 = *piVar4;
    uRam00c81134 = param_1[2];
    break;
  case 0x91:
    iVar2 = param_1[5];
    local_14 = 0;
    _DAT_00c824f0 = (float)(int)param_1[2];
    _DAT_00c824f4 = -(float)(int)param_1[3];
    _DAT_00c824f8 = (float)(int)param_1[4];
    if (*piVar4 == 1) {
      _DAT_00c824f0 = _DAT_00c824f0 + (float)DAT_00d07888;
      _DAT_00c824f4 = _DAT_00c824f4 + (float)DAT_00d0788c;
      _DAT_00c824f8 = _DAT_00c824f8 + (float)DAT_00d07890;
    }
    if ((iVar2 < 0x32) || (200 < iVar2)) {
      _DAT_00c824dc = 386.0;
    }
    else {
      _DAT_00c824dc = _UNK_00546a00 * (float)iVar2;
    }
    DAT_00c82504 = DAT_00c82504 + 1;
    break;
  case 0x92:
    iVar2 = param_1[5];
    local_14 = 0;
    _DAT_00c82420 = (float)(int)param_1[2];
    _DAT_00c82424 = -(float)(int)param_1[3];
    _DAT_00c82428 = (float)(int)param_1[4];
    if (*piVar4 == 1) {
      _DAT_00c82420 = _DAT_00c82420 + (float)DAT_00d07888;
      _DAT_00c82424 = _DAT_00c82424 + (float)DAT_00d0788c;
      _DAT_00c82428 = _DAT_00c82428 + (float)DAT_00d07890;
    }
    if ((iVar2 < 0x32) || (200 < iVar2)) {
      _DAT_00c82520 = 386.0;
    }
    else {
      _DAT_00c82520 = _UNK_00546a00 * (float)iVar2;
    }
    DAT_00c82504 = DAT_00c82504 + 1;
    break;
  case 0x93:
    local_14 = 0;
    DAT_00c82508 = 1;
    break;
  case 0x94:
    local_14 = 0;
    DAT_00d14ee4 = 1;
    DAT_00d14ee0 = 0;
    DAT_00c810c4 = 3;
    break;
  case 0x95:
    local_14 = 0;
    DAT_00d14ee4 = 1;
    DAT_00d14ee0 = 5;
  }
  DAT_00c80eec = DAT_00c80eec + local_c;
  return local_14;
}


// 004fba23

/* WARNING: Restarted to delay deadcode elimination for space: stack */

void FUN_004fba23(int param_1)

{
  float10 fVar1;
  undefined1 local_20 [20];
  int local_c;
  float local_8;
  
  if (DAT_00d17bbc == 0) {
    if (DAT_00b31f04 == 0) {
      FUN_0052a910(local_20,s__02d__02d_005700b4,*(undefined4 *)(param_1 + 0x14),
                   *(undefined4 *)(param_1 + 0x10));
      thunk_FUN_0051755e(0x140,2,local_20,1,1,0xff,0xff,0xff);
      fVar1 = (float10)thunk_FUN_0040b1cc(local_20,1);
      local_8 = (float)fVar1;
      DAT_00ba52d0 = (int)ROUND(local_8);
      local_c = (DAT_00ba52d0 >> 1) + 0x140;
      FUN_0052a910(local_20,s___02d_005700c0,*(undefined4 *)(param_1 + 0xc));
      thunk_FUN_0051755e(local_c,4,local_20,0,0,0xff,0xff,0xff);
    }
    else {
      FUN_0052a910(local_20,s__02d__02d_005700a0,*(undefined4 *)(param_1 + 0x14),
                   *(undefined4 *)(param_1 + 0x10));
      thunk_FUN_0051755e(10,0x1a8,local_20,1,0,0xff,0xff,0xff);
      fVar1 = (float10)thunk_FUN_0040b1cc(local_20,1);
      local_8 = (float)fVar1;
      DAT_00ba52d0 = (int)ROUND(local_8);
      local_c = DAT_00ba52d0 + 10;
      FUN_0052a910(local_20,s___02d_005700ac,*(undefined4 *)(param_1 + 0xc));
      thunk_FUN_0051755e(local_c,0x1aa,local_20,0,0,0xff,0xff,0xff);
    }
  }
  return;
}


// 004fbbc5

void FUN_004fbbc5(undefined4 param_1)

{
  if (DAT_00b5a778 == 0) {
    thunk_FUN_0051755e(0x140,0xf0,param_1,0,1,0xff,0xff,0xff);
  }
  return;
}


// 004fbbfc

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 FUN_004fbbfc(undefined4 param_1)

{
  int iVar1;
  undefined4 uVar2;
  int iVar3;
  uint uVar4;
  int *local_8c;
  undefined1 local_88 [128];
  int local_8;
  
  FUN_0052a910(local_88,s_Attempting_to_read_Trailblazer_d_005700c8,param_1);
  thunk_FUN_004bf2a0(local_88);
  if (DAT_00c80c50 != (int *)0x0) {
    thunk_FUN_004bf2a0(s_Trail_data_already_exists_in_mem_005700f8);
    thunk_FUN_004d8f30(DAT_00c80c50);
    DAT_00c80c50 = (int *)0x0;
    DAT_00c81108 = 0;
    DAT_00c8110c = 0;
  }
  iVar1 = FUN_0052adb0(param_1,&DAT_00570128);
  if (iVar1 == 0) {
    thunk_FUN_004bf2a0(s_Failed_to_acces_Trailblazer_data_0057012c);
    uVar2 = 0;
  }
  else {
    iVar3 = thunk_FUN_004d3000(iVar1);
    uVar4 = (iVar3 - 4U) / 0xc;
    DAT_00c81108 = uVar4;
    local_8c = (int *)thunk_FUN_004d8db4(uVar4 * 0x14,s_D__Driver_Game_MScript_c_00570154,0x1431);
    if (local_8c == (int *)0x0) {
      thunk_FUN_004bf2a0(s_Unable_to_allocate_memory_for_tr_00570170);
      FUN_0052aa10(iVar1);
      uVar2 = 0;
    }
    else {
      _memset(local_8c,0,uVar4 * 0x14);
      DAT_00c80c50 = local_8c;
      for (local_8 = 0; local_8 < (int)uVar4; local_8 = local_8 + 1) {
        FUN_0052aaf0(local_8c + 1,1,4,iVar1);
        FUN_0052aaf0(local_8c + 2,1,4,iVar1);
        FUN_0052aaf0(local_8c + 3,1,4,iVar1);
        *local_8c = local_8;
        local_8c = local_8c + 5;
      }
      DAT_00c80cc0 = 0;
      thunk_FUN_004bf2a0(s_Trail_data_has_loaded_successful_005701ac);
      FUN_0052aa10(iVar1);
      DAT_01271070 = 0;
      _DAT_0127107c = 0;
      _DAT_01271080 = 0;
      _DAT_01271084 = 0;
      for (DAT_00c80bec = 3; -1 < DAT_00c80bec; DAT_00c80bec = DAT_00c80bec + -1) {
        *(undefined4 *)(DAT_00c80bec * 0x20 + 0xc81518) = 0;
      }
      DAT_00c80bec = 0;
      uVar2 = 1;
    }
  }
  return uVar2;
}


