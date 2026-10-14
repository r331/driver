/* Driver PC (1999) — модуль frontend/frontend, псевдо-C из Ghidra. 17 функций */

// 0040c610

void __thiscall FUN_0040c610(undefined4 param_1,undefined4 param_2,int param_3)

{
  int iVar1;
  int iVar2;
  
  (*DAT_01270d30)(0,0,DAT_01270c28,DAT_0125f3f0,param_1);
  iVar1 = thunk_FUN_004d8db4(0x12c000,s_D__Driver_Game_frontend_frontend_0054ab3c,0x1d5);
  if (iVar1 != 0) {
    iVar2 = FUN_0040d6e8(param_2,iVar1);
    if (iVar2 != 0) {
      FUN_0040d81b(iVar1);
      FUN_0040d81b(iVar1);
      FUN_0040d81b(iVar1);
      FUN_0040d81b(iVar1);
      if (param_3 != 0) {
        do {
          iVar2 = thunk_FUN_004d97e9();
        } while (iVar2 != 0);
        do {
          iVar2 = thunk_FUN_004d97e9();
        } while (iVar2 == 0);
      }
    }
    thunk_FUN_004d8f30(iVar1);
  }
  return;
}


// 0040c6bb

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_0040c6bb(undefined4 param_1,int param_2)

{
  int iVar1;
  int iVar2;
  float local_8;
  
  (*DAT_01270d30)(0,0,DAT_01270c28,DAT_0125f3f0);
  iVar1 = thunk_FUN_004d8db4(0x12c000,s_D__Driver_Game_frontend_frontend_0054ab60,0x1f7);
  if (iVar1 != 0) {
    iVar2 = FUN_0040d6e8(param_1,iVar1);
    if (iVar2 != 0) {
      FUN_0040da56(iVar1);
      for (local_8 = 0.0; local_8 < _DAT_00546020; local_8 = local_8 + _DAT_00546054) {
        FUN_0040dbee(local_8);
      }
      FUN_0040dbee(0x3f800000);
      FUN_0040dbee(0x3f800000);
      FUN_0040dbee(0x3f800000);
      FUN_0040dbee(0x3f800000);
      thunk_FUN_004086b4();
      do {
        if (param_2 <= DAT_005d577c) break;
        iVar2 = thunk_FUN_004d97e9();
      } while (iVar2 == 0);
      thunk_FUN_004086ea();
      for (local_8 = 1.0; _DAT_00546024 < local_8; local_8 = local_8 - _DAT_00546054) {
        FUN_0040dbee(local_8);
      }
      FUN_0040dbee(0);
      FUN_0040dbee(0);
      FUN_0040dbee(0);
      FUN_0040dbee(0);
    }
    thunk_FUN_004d8f30(iVar1);
  }
  return;
}


// 0040c813

void FUN_0040c813(undefined4 param_1,int param_2)

{
  int iVar1;
  
  thunk_FUN_0040c610(param_1,0);
  do {
    iVar1 = thunk_FUN_004d97e9();
  } while (iVar1 != 0);
  thunk_FUN_004086b4();
  do {
    if (param_2 <= DAT_005d577c) break;
    iVar1 = thunk_FUN_004d97e9();
  } while (iVar1 == 0);
  thunk_FUN_004086ea();
  thunk_FUN_004d78f3(0);
  DAT_005f7e60 = 1;
  return;
}


// 0040c867

void FUN_0040c867(void)

{
  thunk_FUN_00523e50(0,9,0xffffffff);
  return;
}


// 0040c87a

void FUN_0040c87a(void)

{
  thunk_FUN_00523e50(1,9,0xffffffff);
  return;
}


// 0040c88d

void FUN_0040c88d(void)

{
  thunk_FUN_00523e50(2,9,0xffffffff);
  return;
}


// 0040c8a0

void FUN_0040c8a0(int param_1,int param_2)

{
  undefined4 local_8;
  
  for (local_8 = 0; *(int *)(param_1 + 8 + local_8 * 0x10) != 0; local_8 = local_8 + 1) {
    (**(code **)(param_1 + 4 + local_8 * 0x10))(0);
  }
  (**(code **)(param_1 + param_2 * 0x10))(0);
  return;
}


// 0040c8f1

undefined4 FUN_0040c8f1(int param_1,uint *param_2)

{
  uint uVar1;
  int iVar2;
  undefined4 local_10;
  
  local_10 = 0;
  uVar1 = *param_2;
  iVar2 = thunk_FUN_004e383a(1);
  if (iVar2 == 0) {
    DAT_005f7e68 = DAT_005f7e68 + -1;
    if (DAT_005f7e68 < 1) {
      DAT_005f7e68 = 0x14;
      DAT_005f7e6c = DAT_005f7e6c ^ 1;
    }
    if (DAT_005f7e6c == 0) {
      (**(code **)(param_1 + 4 + *param_2 * 0x10))(1);
    }
    else {
      (**(code **)(param_1 + *param_2 * 0x10))(1);
    }
    if (DAT_005f7e4c == 0) {
      iVar2 = thunk_FUN_004e383a(0xcb);
      if (iVar2 == 0) {
        iVar2 = thunk_FUN_004e383a(0xcd);
        if (iVar2 != 0) {
          *param_2 = (uint)*(byte *)(param_1 + 0xd + *param_2 * 0x10);
          thunk_FUN_0040c867();
        }
      }
      else {
        *param_2 = (uint)*(byte *)(param_1 + 0xc + *param_2 * 0x10);
        thunk_FUN_0040c867();
      }
    }
    else {
      if (((DAT_00d04bcb | DAT_00d04bcd) & 0x80) == 0) {
        DAT_005f7e70 = 0;
        DAT_0054aa48 = 0x28;
      }
      if (DAT_005f7e70 == 0) {
        if ((DAT_00d04bcb & 0x80) == 0) {
          if ((DAT_00d04bcd & 0x80) != 0) {
            (**(code **)(param_1 + (uint)*(byte *)(param_1 + 0xd + *param_2 * 0x10) * 0x10))(0);
            DAT_005f7e70 = DAT_0054aa48;
            DAT_0054aa48 = 1;
            thunk_FUN_0040c867();
          }
        }
        else {
          (**(code **)(param_1 + (uint)*(byte *)(param_1 + 0xc + *param_2 * 0x10) * 0x10))(0);
          DAT_005f7e70 = DAT_0054aa48;
          DAT_0054aa48 = 1;
          thunk_FUN_0040c867();
        }
      }
      else {
        DAT_005f7e70 = DAT_005f7e70 + -1;
      }
    }
    iVar2 = thunk_FUN_004e383a(200);
    if (iVar2 == 0) {
      iVar2 = thunk_FUN_004e383a(0xd0);
      if (iVar2 == 0) {
        iVar2 = thunk_FUN_004e383a(0x1c);
        if (iVar2 != 0) {
          thunk_FUN_0040c867();
          local_10 = (**(code **)(param_1 + 8 + *param_2 * 0x10))();
        }
      }
      else {
        *param_2 = (uint)*(byte *)(param_1 + 0xf + *param_2 * 0x10);
        thunk_FUN_0040c867();
      }
    }
    else {
      *param_2 = (uint)*(byte *)(param_1 + 0xe + *param_2 * 0x10);
      thunk_FUN_0040c867();
    }
    if (uVar1 != *param_2) {
      (**(code **)(param_1 + 4 + uVar1 * 0x10))(0);
      (**(code **)(param_1 + *param_2 * 0x10))(0);
    }
  }
  else {
    (**(code **)(param_1 + 4 + uVar1 * 0x10))(0);
    local_10 = 0xffffffff;
  }
  return local_10;
}


// 0040cb9f

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_0040cb9f(void)

{
  int iVar1;
  int iVar2;
  float fVar3;
  undefined1 local_8;
  undefined1 local_7;
  undefined1 local_6;
  undefined1 local_5;
  
  if ((DAT_00bdf9cc != 0) && (DAT_005f7e60 = DAT_005f7e60 + -1, DAT_005f7e60 == 0)) {
    if ((DAT_00b87e90 != 0) && (DAT_00b91d38 == 0)) {
      InitCDAudio();
      PlayCDTrack(2);
    }
    thunk_FUN_00523829();
    thunk_FUN_00523c56();
    thunk_FUN_004264bd();
    thunk_FUN_00407c42();
    FUN_0040cf35();
    FUN_0040cd6f();
    FUN_0040ce31();
    if (DAT_005f7e44 != 0) {
      local_8 = 0;
      local_7 = 0;
      local_6 = 0;
      local_5 = 0;
      fVar3 = (float)_DAT_005f7e48;
      iVar1 = __ftol(fVar3);
      iVar2 = 0x1b0 - iVar1;
      thunk_FUN_00407d56(0,0x30,&local_8,0x280,iVar1,fVar3,iVar2);
      thunk_FUN_00407d56(0,iVar2,&local_8,0x280,iVar1 + 1);
    }
    thunk_FUN_00407d97(0,0xff);
    thunk_FUN_00407c4c();
    thunk_FUN_0042651a();
    DAT_005f7e60 = thunk_FUN_004d78f3(0);
  }
  return;
}


// 0040ccb4

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_0040ccb4(undefined4 param_1,undefined4 param_2)

{
  undefined4 local_8;
  
  DAT_005f7e64 = param_1;
  DAT_005f7e40 = param_2;
  DAT_005f7e44 = 1;
  for (local_8 = 5; -1 < local_8; local_8 = local_8 + -1) {
    thunk_FUN_00522323();
    thunk_FUN_004e3391();
    _DAT_005f7e48 = local_8;
    thunk_FUN_0040cb9f();
  }
  DAT_005f7e44 = 0;
  thunk_FUN_004086b4();
  return;
}


// 0040cd17

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __fastcall FUN_0040cd17(undefined4 param_1)

{
  int iVar1;
  
  thunk_FUN_004086ea(param_1);
  thunk_FUN_0040c87a();
  DAT_005f7e44 = 1;
  for (iVar1 = 0; iVar1 < 6; iVar1 = iVar1 + 1) {
    thunk_FUN_00522323();
    thunk_FUN_004e3391();
    _DAT_005f7e48 = iVar1;
    iVar1 = _DAT_005f7e48;
    thunk_FUN_0040cb9f();
  }
  DAT_005f7e44 = 0;
  return;
}


// 0040cd6f

void FUN_0040cd6f(void)

{
  short *psVar1;
  int iVar2;
  
  if (DAT_005f7e64 != (short *)0x0) {
    iVar2 = 0;
    for (psVar1 = DAT_005f7e64; (psVar1[4] & 4U) == 0; psVar1 = psVar1 + 10) {
      if ((psVar1[4] & 8U) == 0) {
        if ((psVar1[4] & 1U) == 0) {
          thunk_FUN_00407d56((int)*psVar1,(int)psVar1[1],psVar1 + 7,(int)psVar1[5],(int)psVar1[6],
                             psVar1,iVar2);
        }
        else {
          FUN_0040cfdf((int)*psVar1,(int)psVar1[1],psVar1 + 7,*(undefined4 *)(psVar1 + 2),0);
        }
      }
      iVar2 = iVar2 + 1;
    }
  }
  return;
}


// 0040ce31

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_0040ce31(void)

{
  undefined3 uVar1;
  short *local_8;
  
  local_8 = DAT_005f7e40;
  if (DAT_005f7e40 != (short *)0x0) {
    thunk_FUN_0040b0a4();
    for (; *(int *)(local_8 + 4) != 0; local_8 = local_8 + 8) {
      uVar1 = (undefined3)((uint)local_8 >> 8);
      thunk_FUN_0040ab3a(CONCAT31(uVar1,(char)local_8[6]),
                         CONCAT31(uVar1,*(undefined1 *)((int)local_8 + 0xd)),(char)local_8[7]);
      if (*(byte *)(local_8 + 2) < 2) {
        thunk_FUN_0040ab6f((float)(int)*local_8,(float)(int)local_8[1] - _DAT_00546020,
                           CONCAT31(uVar1,(char)local_8[2]),
                           CONCAT31(uVar1,*(undefined1 *)((int)local_8 + 5)));
      }
      else {
        thunk_FUN_0040ab6f((float)(int)*local_8,(float)(int)local_8[1] - _DAT_00546034,
                           CONCAT31(uVar1,(char)local_8[2]),
                           CONCAT31(uVar1,*(undefined1 *)((int)local_8 + 5)));
      }
      thunk_FUN_0040abac(*(undefined4 *)(local_8 + 4));
    }
  }
  return;
}


// 0040cf35

void FUN_0040cf35(void)

{
  FUN_0040cfdf(0,0x30,&DAT_0054aa40,s_BKGRND1A_0054ab84,0);
  FUN_0040cfdf(0x100,0x30,&DAT_0054aa40,s_BKGRND1B_0054ab90,0);
  FUN_0040cfdf(0x200,0x30,&DAT_0054aa40,s_BKGRND1C_0054ab9c,0);
  FUN_0040cfdf(0,0x130,&DAT_0054aa40,s_BKGRND1D_0054aba8,0);
  FUN_0040cfdf(0x100,0x130,&DAT_0054aa40,s_BKGRND1E_0054abb4,0);
  FUN_0040cfdf(0x200,0x130,&DAT_0054aa40,s_BKGRND1F_0054abc0,0);
  return;
}


// 0040cfdf

void FUN_0040cfdf(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  int iVar1;
  uint local_18;
  uint local_14;
  
  iVar1 = thunk_FUN_004ec91e(param_4);
  if (iVar1 != 0) {
    if (*(char *)(iVar1 + 0xb) == '\0') {
      local_14 = 0x100;
    }
    else {
      local_14 = (uint)*(byte *)(iVar1 + 0xb);
    }
    if (*(char *)(iVar1 + 0xc) == '\0') {
      local_18 = 0x100;
    }
    else {
      local_18 = (uint)*(byte *)(iVar1 + 0xc);
    }
    thunk_FUN_00407cb8(param_1,param_2,*(undefined1 *)(iVar1 + 8),*(undefined1 *)(iVar1 + 9),
                       CONCAT31((int3)(local_18 >> 8),*(undefined1 *)(iVar1 + 10)),local_14,local_18
                      );
  }
  return;
}


// 0040d07b

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 FUN_0040d07b(undefined4 param_1)

{
  undefined4 uVar1;
  int iVar2;
  undefined1 local_4c [4];
  short local_48 [2];
  int local_44;
  int local_40;
  undefined1 local_3c [4];
  short local_38;
  short local_36;
  short local_34 [2];
  undefined4 local_30;
  int local_2c;
  char local_28;
  char cStack_27;
  char cStack_26;
  char cStack_25;
  undefined1 local_24;
  undefined1 uStack_23;
  undefined1 uStack_22;
  undefined1 uStack_21;
  int local_20;
  int local_1c;
  int local_18;
  int local_14;
  int local_10;
  short local_c;
  
  local_44 = 0;
  for (local_20 = 0; local_20 < 0x32; local_20 = local_20 + 1) {
    *(undefined4 *)(&DAT_01252aa0 + local_20 * 4) = 0;
  }
  local_44 = FUN_0052adb0(param_1,&DAT_0054abcc);
  if (local_44 == 0) {
    uVar1 = 0;
  }
  else {
    FUN_0052aaf0(&local_28,1,4,local_44);
    if ((((local_28 == 'T') && (cStack_27 == 'S')) && (cStack_26 == 'D')) && (cStack_25 == ' ')) {
      FUN_0052aaf0(&local_24,1,4,local_44);
      FUN_0052aaf0(local_3c,1,8,local_44);
      if (local_38 == 0x100) {
        if (CONCAT13(uStack_21,CONCAT12(uStack_22,CONCAT11(uStack_23,local_24))) == 0x3f800000) {
          FUN_0052aaf0(&DAT_01252fe0,1,0x400,local_44);
          _DAT_01252aa4 = 1;
          FUN_0052aaf0(&DAT_01252be0,1,0x400,local_44);
          _DAT_01252aa0 = 1;
        }
        else {
          FUN_0052aaf0(local_34,1,2,local_44);
          for (local_20 = 0; local_20 < local_34[0]; local_20 = local_20 + 1) {
            FUN_0052aaf0(local_48,1,2,local_44);
            FUN_0052aaf0(local_48,1,2,local_44);
            FUN_0052aaf0(&DAT_01252be0 + local_48[0] * 0x400,1,0x400,local_44);
            *(undefined4 *)(&DAT_01252aa0 + local_48[0] * 4) = 1;
          }
        }
        local_30 = FUN_0052b260(local_44);
        local_2c = 0;
        local_40 = 0;
        for (local_1c = 0; local_1c < local_36; local_1c = local_1c + 1) {
          if (_DAT_00546020 <
              (float)CONCAT13(uStack_21,CONCAT12(uStack_22,CONCAT11(uStack_23,local_24)))) {
            FUN_0052aaf0(local_4c,1,2,local_44);
          }
          FUN_0052aaf0(&local_18,1,0x14,local_44);
          local_18 = local_18 + -0x14;
          local_14 = local_14 + -0x14;
          local_10 = local_10 + -0x14;
          local_40 = local_40 + local_c;
          local_2c = local_2c + 0x10000;
          FUN_0052b4f0(local_44,local_18,1);
        }
        if ((local_2c != 0) &&
           (DAT_00d01260 = thunk_FUN_004d8db4(local_2c + 0xffff,
                                              s_D__Driver_Game_frontend_frontend_0054abd0,0x3b6),
           DAT_00d01260 == 0)) {
          FUN_0052aa10(local_44);
          return 0;
        }
        DAT_00b31ee0 = 0x10000 - (DAT_00d01260 & 0xffff) & 0xffff;
        DAT_00b31ecc = thunk_FUN_004d8db4(local_40 << 4,s_D__Driver_Game_frontend_frontend_0054abf4,
                                          0x3c0);
        if (DAT_00b31ecc == 0) {
          FUN_0052aa10(local_44);
          uVar1 = 0;
        }
        else {
          FUN_0052b4f0(local_44,local_30,0);
          DAT_00b31ed4 = 0;
          local_1c = 0;
          for (local_20 = 0; local_20 < local_36; local_20 = local_20 + 1) {
            iVar2 = FUN_0040d4b3(local_44,CONCAT13(uStack_21,
                                                   CONCAT12(uStack_22,CONCAT11(uStack_23,local_24)))
                                 ,&local_18,0,0,0,0);
            FUN_0040d56c(&local_18,iVar2,local_1c);
            *(uint *)(&DAT_01145a64 + local_1c * 0x10) = DAT_00d01260 + DAT_00b31ee0;
            FUN_0052b650(*(undefined4 *)(&DAT_01145a64 + local_1c * 0x10),iVar2 + local_10,0x10000);
            local_1c = local_1c + 1;
            DAT_00b31ee0 = DAT_00b31ee0 + 0x10000;
            thunk_FUN_004d8f30(iVar2);
          }
          FUN_0052aa10(local_44);
          uVar1 = 1;
        }
      }
      else {
        FUN_0052aa10(local_44);
        uVar1 = 0;
      }
    }
    else {
      FUN_0052aa10(local_44);
      uVar1 = 0;
    }
  }
  return uVar1;
}


// 0040d4b3

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

int FUN_0040d4b3(undefined4 param_1,float param_2,int *param_3)

{
  int iVar1;
  undefined1 local_8 [4];
  
  if (_DAT_00546020 < param_2) {
    FUN_0052aaf0(local_8,1,2,param_1);
  }
  FUN_0052aaf0(param_3,1,0x14,param_1);
  *param_3 = *param_3 + -0x14;
  param_3[1] = param_3[1] + -0x14;
  param_3[2] = param_3[2] + -0x14;
  iVar1 = thunk_FUN_004d8db4(*param_3,s_D__Driver_Game_frontend_frontend_0054ac18,0x3f5);
  if (iVar1 == 0) {
    FUN_0052aa10(param_1);
    iVar1 = 0;
  }
  else {
    FUN_0052aaf0(iVar1,1,*param_3,param_1);
  }
  return iVar1;
}


