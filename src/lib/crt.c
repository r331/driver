/* Driver PC (1999) — модуль CRT, псевдо-C из Ghidra. 341 функций */

// 0052a910

undefined4 FUN_0052a910(undefined1 *param_1,int param_2)

{
  code *pcVar1;
  int iVar2;
  undefined4 uVar3;
  undefined1 *local_24;
  int local_20;
  undefined1 *local_1c;
  undefined4 local_18;
  
  if ((param_1 == (undefined1 *)0x0) &&
     (iVar2 = FUN_0052fad0(2,"sprintf.c",0x5d,0,"string != NULL"), iVar2 == 1)) {
    pcVar1 = (code *)swi(3);
    uVar3 = (*pcVar1)();
    return uVar3;
  }
  if ((param_2 == 0) && (iVar2 = FUN_0052fad0(2,"sprintf.c",0x5e,0,"format != NULL"), iVar2 == 1)) {
    pcVar1 = (code *)swi(3);
    uVar3 = (*pcVar1)();
    return uVar3;
  }
  local_18 = 0x42;
  local_1c = param_1;
  local_24 = param_1;
  local_20 = 0x7fffffff;
  uVar3 = FUN_0052eb20(&local_24,param_2,&stack0x0000000c);
  local_20 = local_20 + -1;
  if (local_20 < 0) {
    FUN_0052e8a0(0,&local_24);
  }
  else {
    *local_24 = 0;
  }
  return uVar3;
}


// 0052aa10

undefined4 FUN_0052aa10(int param_1)

{
  code *pcVar1;
  int iVar2;
  undefined4 uVar3;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  if ((*(uint *)(param_1 + 0xc) & 0x40) == 0) {
    if ((param_1 == 0) && (iVar2 = FUN_0052fad0(2,"fclose.c",0x77,0,"str != NULL"), iVar2 == 1)) {
      pcVar1 = (code *)swi(3);
      uVar3 = (*pcVar1)();
      return uVar3;
    }
    if ((*(uint *)(param_1 + 0xc) & 0x83) != 0) {
      local_8 = FUN_00530360(param_1);
      FUN_00530260(param_1);
      iVar2 = FUN_00530170(*(undefined4 *)(param_1 + 0x10));
      if (iVar2 < 0) {
        local_8 = 0xffffffff;
      }
      else if (*(int *)(param_1 + 0x1c) != 0) {
        FUN_0052cb90(*(undefined4 *)(param_1 + 0x1c),2);
        *(undefined4 *)(param_1 + 0x1c) = 0;
      }
    }
    *(undefined4 *)(param_1 + 0xc) = 0;
  }
  else {
    *(undefined4 *)(param_1 + 0xc) = 0;
    local_8 = 0xffffffff;
  }
  return local_8;
}


// 0052aaf0

uint FUN_0052aaf0(undefined1 *param_1,uint param_2,uint param_3,int *param_4)

{
  int iVar1;
  uint uVar2;
  uint local_28;
  uint local_24;
  uint local_20;
  uint local_10;
  undefined1 *local_c;
  undefined1 local_8;
  
  local_c = param_1;
  uVar2 = param_2 * param_3;
  if (uVar2 == 0) {
    param_3 = 0;
  }
  else {
    local_10 = uVar2;
    if ((param_4[3] & 0x10cU) == 0) {
      local_20 = 0x1000;
    }
    else {
      local_20 = param_4[6];
    }
    while (local_10 != 0) {
      if (((param_4[3] & 0x10cU) == 0) || (param_4[1] == 0)) {
        if (local_10 < local_20) {
          iVar1 = FUN_00530510(param_4);
          if (iVar1 == -1) {
            return (uVar2 - local_10) / param_2;
          }
          local_8 = (undefined1)iVar1;
          *local_c = local_8;
          local_c = local_c + 1;
          local_10 = local_10 - 1;
          local_20 = param_4[6];
        }
        else {
          if (local_20 == 0) {
            local_28 = local_10;
          }
          else {
            local_28 = local_10 - local_10 % local_20;
          }
          iVar1 = FUN_005306f0(param_4[4],local_c,local_28);
          if (iVar1 == 0) {
            param_4[3] = param_4[3] | 0x10;
            return (uVar2 - local_10) / param_2;
          }
          if (iVar1 == -1) {
            param_4[3] = param_4[3] | 0x20;
            return (uVar2 - local_10) / param_2;
          }
          local_10 = local_10 - iVar1;
          local_c = local_c + iVar1;
        }
      }
      else {
        if (local_10 < (uint)param_4[1]) {
          local_24 = local_10;
        }
        else {
          local_24 = param_4[1];
        }
        FUN_0052b650(local_c,*param_4,local_24);
        local_10 = local_10 - local_24;
        param_4[1] = param_4[1] - local_24;
        *param_4 = *param_4 + local_24;
        local_c = local_c + local_24;
      }
    }
  }
  return param_3;
}


// 0052acc0

undefined4 FUN_0052acc0(char *param_1,char *param_2,undefined4 param_3)

{
  code *pcVar1;
  int iVar2;
  undefined4 uVar3;
  
  if ((param_1 == (char *)0x0) &&
     (iVar2 = FUN_0052fad0(2,"fopen.c",0x35,0,"file != NULL"), iVar2 == 1)) {
    pcVar1 = (code *)swi(3);
    uVar3 = (*pcVar1)();
    return uVar3;
  }
  if ((*param_1 == '\0') &&
     (iVar2 = FUN_0052fad0(2,"fopen.c",0x36,0,"*file != _T(\'\\0\')"), iVar2 == 1)) {
    pcVar1 = (code *)swi(3);
    uVar3 = (*pcVar1)();
    return uVar3;
  }
  if ((param_2 == (char *)0x0) &&
     (iVar2 = FUN_0052fad0(2,"fopen.c",0x37,0,"mode != NULL"), iVar2 == 1)) {
    pcVar1 = (code *)swi(3);
    uVar3 = (*pcVar1)();
    return uVar3;
  }
  if ((*param_2 == '\0') &&
     (iVar2 = FUN_0052fad0(2,"fopen.c",0x38,0,"*mode != _T(\'\\0\')"), iVar2 == 1)) {
    pcVar1 = (code *)swi(3);
    uVar3 = (*pcVar1)();
    return uVar3;
  }
  iVar2 = FUN_00530ee0();
  if (iVar2 == 0) {
    uVar3 = 0;
  }
  else {
    uVar3 = FUN_00530b50(param_1,param_2,param_3,iVar2);
  }
  return uVar3;
}


// 0052adb0

void FUN_0052adb0(undefined4 param_1,undefined4 param_2)

{
  FUN_0052acc0(param_1,param_2,0x40);
  return;
}


// 0052add0

void FUN_0052add0(void)

{
  FUN_0052ae10();
  DAT_00b94038 = __ms_p5_mp_test_fdiv();
  __setdefaultprecision();
  return;
}


// 0052ae00

void FUN_0052ae00(void)

{
  return;
}


// 0052ae10

void FUN_0052ae10(void)

{
  PTR___fptrap_0057a268 = __cfltcvt;
  PTR___fptrap_0057a26c = __cropzeros;
  PTR___fptrap_0057a270 = __fassign;
  PTR___fptrap_0057a274 = FUN_005310a0;
  PTR___fptrap_0057a278 = __positive;
  PTR___fptrap_0057a27c = __cfltcvt;
  return;
}


// 0052ae60

undefined4 FUN_0052ae60(undefined4 param_1)

{
  undefined4 uVar1;
  
  uVar1 = DAT_00b94034;
  DAT_00b94034 = param_1;
  return uVar1;
}


// 0052ae80

uint FUN_0052ae80(char *param_1,uint param_2,uint param_3,int *param_4)

{
  int iVar1;
  uint uVar2;
  uint uVar3;
  uint local_2c;
  uint local_28;
  uint local_24;
  uint local_20;
  uint local_10;
  char *local_c;
  
  local_c = param_1;
  uVar3 = param_2 * param_3;
  if (uVar3 == 0) {
    param_2 = 0;
  }
  else {
    local_10 = uVar3;
    if ((param_4[3] & 0x10cU) == 0) {
      local_20 = 0x1000;
    }
    else {
      local_20 = param_4[6];
    }
    do {
      while( true ) {
        while( true ) {
          if (local_10 == 0) {
            return param_3;
          }
          if (((param_4[3] & 0x108U) == 0) || (param_4[1] == 0)) break;
          if (local_10 < (uint)param_4[1]) {
            local_24 = local_10;
          }
          else {
            local_24 = param_4[1];
          }
          FUN_0052b650(*param_4,local_c,local_24);
          local_10 = local_10 - local_24;
          param_4[1] = param_4[1] - local_24;
          *param_4 = *param_4 + local_24;
          local_c = local_c + local_24;
        }
        if (local_20 <= local_10) break;
        iVar1 = FUN_0052e8a0((int)*local_c,param_4);
        if (iVar1 == -1) {
          return (uVar3 - local_10) / param_2;
        }
        local_c = local_c + 1;
        local_10 = local_10 - 1;
        if (param_4[6] < 1) {
          local_2c = 1;
        }
        else {
          local_2c = param_4[6];
        }
        local_20 = local_2c;
      }
      if (((param_4[3] & 0x108U) != 0) && (iVar1 = FUN_00530360(param_4), iVar1 != 0)) {
        return (uVar3 - local_10) / param_2;
      }
      if (local_20 == 0) {
        local_28 = local_10;
      }
      else {
        local_28 = local_10 - local_10 % local_20;
      }
      uVar2 = FUN_00531800(param_4[4],local_c,local_28);
      if (uVar2 == 0xffffffff) {
        param_4[3] = param_4[3] | 0x20;
        return (uVar3 - local_10) / param_2;
      }
      local_10 = local_10 - uVar2;
      local_c = local_c + uVar2;
    } while (local_28 <= uVar2);
    param_4[3] = param_4[3] | 0x20;
    param_2 = (uVar3 - local_10) / param_2;
  }
  return param_2;
}


// 0052b0a0

/* Library Function - Single Match
    _memset
   
   Libraries: Visual Studio 1998 Debug, Visual Studio 1998 Release */

void * __cdecl _memset(void *_Dst,int _Val,size_t _Size)

{
  uint uVar1;
  uint uVar2;
  size_t sVar3;
  uint *puVar4;
  
  if (_Size == 0) {
    return _Dst;
  }
  uVar1 = _Val & 0xff;
  puVar4 = _Dst;
  if (3 < _Size) {
    uVar2 = -(int)_Dst & 3;
    sVar3 = _Size;
    if (uVar2 != 0) {
      sVar3 = _Size - uVar2;
      do {
        *(undefined1 *)puVar4 = (undefined1)_Val;
        puVar4 = (uint *)((int)puVar4 + 1);
        uVar2 = uVar2 - 1;
      } while (uVar2 != 0);
    }
    uVar1 = uVar1 * 0x1010101;
    _Size = sVar3 & 3;
    uVar2 = sVar3 >> 2;
    if (uVar2 != 0) {
      for (; uVar2 != 0; uVar2 = uVar2 - 1) {
        *puVar4 = uVar1;
        puVar4 = puVar4 + 1;
      }
      if (_Size == 0) {
        return _Dst;
      }
    }
  }
  do {
    *(char *)puVar4 = (char)uVar1;
    puVar4 = (uint *)((int)puVar4 + 1);
    _Size = _Size - 1;
  } while (_Size != 0);
  return _Dst;
}


// 0052b100

uint * FUN_0052b100(uint *param_1,uint *param_2)

{
  byte bVar1;
  uint uVar2;
  uint uVar3;
  uint *puVar4;
  
  puVar4 = param_1;
  while (((uint)param_2 & 3) != 0) {
    bVar1 = (byte)*param_2;
    uVar3 = (uint)bVar1;
    param_2 = (uint *)((int)param_2 + 1);
    if (bVar1 == 0) goto LAB_0052b1e8;
    *(byte *)puVar4 = bVar1;
    puVar4 = (uint *)((int)puVar4 + 1);
  }
  do {
    uVar2 = *param_2;
    uVar3 = *param_2;
    param_2 = param_2 + 1;
    if (((uVar2 ^ 0xffffffff ^ uVar2 + 0x7efefeff) & 0x81010100) != 0) {
      if ((char)uVar3 == '\0') {
LAB_0052b1e8:
        *(byte *)puVar4 = (byte)uVar3;
        return param_1;
      }
      if ((char)(uVar3 >> 8) == '\0') {
        *(short *)puVar4 = (short)uVar3;
        return param_1;
      }
      if ((uVar3 & 0xff0000) == 0) {
        *(short *)puVar4 = (short)uVar3;
        *(byte *)((int)puVar4 + 2) = 0;
        return param_1;
      }
      if ((uVar3 & 0xff000000) == 0) {
        *puVar4 = uVar3;
        return param_1;
      }
    }
    *puVar4 = uVar3;
    puVar4 = puVar4 + 1;
  } while( true );
}


// 0052b110

uint * FUN_0052b110(uint *param_1,uint *param_2)

{
  byte bVar1;
  uint uVar2;
  uint *puVar3;
  uint uVar4;
  uint *puVar5;
  
  puVar3 = param_1;
  do {
    if (((uint)puVar3 & 3) == 0) goto LAB_0052b12c;
    uVar4 = *puVar3;
    puVar3 = (uint *)((int)puVar3 + 1);
  } while ((byte)uVar4 != 0);
  goto LAB_0052b15f;
  while( true ) {
    if ((uVar4 & 0xff0000) == 0) {
      puVar5 = (uint *)((int)puVar5 + 2);
      goto joined_r0x0052b17b;
    }
    if ((uVar4 & 0xff000000) == 0) break;
LAB_0052b12c:
    do {
      puVar5 = puVar3;
      puVar3 = puVar5 + 1;
    } while (((*puVar5 ^ 0xffffffff ^ *puVar5 + 0x7efefeff) & 0x81010100) == 0);
    uVar4 = *puVar5;
    if ((char)uVar4 == '\0') goto joined_r0x0052b17b;
    if ((char)(uVar4 >> 8) == '\0') {
      puVar5 = (uint *)((int)puVar5 + 1);
      goto joined_r0x0052b17b;
    }
  }
LAB_0052b15f:
  puVar5 = (uint *)((int)puVar3 + -1);
joined_r0x0052b17b:
  do {
    if (((uint)param_2 & 3) == 0) {
      do {
        uVar2 = *param_2;
        uVar4 = *param_2;
        param_2 = param_2 + 1;
        if (((uVar2 ^ 0xffffffff ^ uVar2 + 0x7efefeff) & 0x81010100) != 0) {
          if ((char)uVar4 == '\0') {
LAB_0052b1e8:
            *(byte *)puVar5 = (byte)uVar4;
            return param_1;
          }
          if ((char)(uVar4 >> 8) == '\0') {
            *(short *)puVar5 = (short)uVar4;
            return param_1;
          }
          if ((uVar4 & 0xff0000) == 0) {
            *(short *)puVar5 = (short)uVar4;
            *(byte *)((int)puVar5 + 2) = 0;
            return param_1;
          }
          if ((uVar4 & 0xff000000) == 0) {
            *puVar5 = uVar4;
            return param_1;
          }
        }
        *puVar5 = uVar4;
        puVar5 = puVar5 + 1;
      } while( true );
    }
    bVar1 = (byte)*param_2;
    uVar4 = (uint)bVar1;
    param_2 = (uint *)((int)param_2 + 1);
    if (bVar1 == 0) goto LAB_0052b1e8;
    *(byte *)puVar5 = bVar1;
    puVar5 = (uint *)((int)puVar5 + 1);
  } while( true );
}


// 0052b1f0

/* Library Function - Multiple Matches With Different Base Names
    __wremove
    _remove
   
   Library: Visual Studio */

int __cdecl FID_conflict__remove(char *_Filename)

{
  BOOL BVar1;
  int iVar2;
  undefined4 local_8;
  
  BVar1 = DeleteFileA(_Filename);
  if (BVar1 == 0) {
    local_8 = GetLastError();
  }
  else {
    local_8 = 0;
  }
  if (local_8 == 0) {
    iVar2 = 0;
  }
  else {
    __dosmaperr(local_8);
    iVar2 = -1;
  }
  return iVar2;
}


// 0052b240

void FUN_0052b240(char *param_1)

{
  FID_conflict__remove(param_1);
  return;
}


// 0052b260

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

int FUN_0052b260(uint *param_1)

{
  uint uVar1;
  code *pcVar2;
  int iVar3;
  int iVar4;
  char *pcVar5;
  int local_20;
  int local_1c;
  uint local_14;
  char *local_8;
  
  if ((param_1 == (uint *)0x0) && (iVar3 = FUN_0052fad0(2,"ftell.c",99,0,"str != NULL"), iVar3 == 1)
     ) {
    pcVar2 = (code *)swi(3);
    iVar3 = (*pcVar2)();
    return iVar3;
  }
  uVar1 = param_1[4];
  if ((int)param_1[1] < 0) {
    param_1[1] = 0;
  }
  local_20 = FUN_00531eb0(uVar1,0,1);
  if (local_20 < 0) {
    local_1c = -1;
  }
  else if ((param_1[3] & 0x108) == 0) {
    local_1c = local_20 - param_1[1];
  }
  else {
    local_1c = *param_1 - param_1[2];
    iVar3 = (int)uVar1 >> 5;
    if ((param_1[3] & 3) == 0) {
      if ((param_1[3] & 0x80) == 0) {
        _DAT_00b94050 = 0x16;
        return -1;
      }
    }
    else if (((int)*(char *)((&DAT_01286a60)[iVar3] + 4 + (uVar1 & 0x1f) * 8) & 0x80U) != 0) {
      for (local_8 = (char *)param_1[2]; local_8 < (char *)*param_1; local_8 = local_8 + 1) {
        if (*local_8 == '\n') {
          local_1c = local_1c + 1;
        }
      }
    }
    if (local_20 != 0) {
      if ((param_1[3] & 1) != 0) {
        if (param_1[1] == 0) {
          local_1c = 0;
        }
        else {
          local_14 = param_1[1] + (*param_1 - param_1[2]);
          if (((int)*(char *)((&DAT_01286a60)[iVar3] + 4 + (uVar1 & 0x1f) * 8) & 0x80U) != 0) {
            iVar4 = FUN_00531eb0(uVar1,0,2);
            if (iVar4 == local_20) {
              pcVar5 = (char *)(param_1[2] + local_14);
              for (local_8 = (char *)param_1[2]; local_8 < pcVar5; local_8 = local_8 + 1) {
                if (*local_8 == '\n') {
                  local_14 = local_14 + 1;
                }
              }
              if ((param_1[3] & 0x2000) != 0) {
                local_14 = local_14 + 1;
              }
            }
            else {
              FUN_00531eb0(uVar1,local_20,0);
              if (((local_14 < 0x201) && ((param_1[3] & 8) != 0)) && ((param_1[3] & 0x400) == 0)) {
                local_14 = 0x200;
              }
              else {
                local_14 = param_1[6];
              }
              if ((*(byte *)((&DAT_01286a60)[iVar3] + 4 + (uVar1 & 0x1f) * 8) & 4) != 0) {
                local_14 = local_14 + 1;
              }
            }
          }
          local_20 = local_20 - local_14;
        }
      }
      local_1c = local_20 + local_1c;
    }
  }
  return local_1c;
}


// 0052b4f0

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

int FUN_0052b4f0(int param_1,int param_2,int param_3)

{
  code *pcVar1;
  int iVar2;
  
  if ((param_1 == 0) && (iVar2 = FUN_0052fad0(2,"fseek.c",0x92,0,"str != NULL"), iVar2 == 1)) {
    pcVar1 = (code *)swi(3);
    iVar2 = (*pcVar1)();
    return iVar2;
  }
  if (((*(uint *)(param_1 + 0xc) & 0x83) == 0) ||
     (((param_3 != 0 && (param_3 != 1)) && (param_3 != 2)))) {
    _DAT_00b94050 = 0x16;
    iVar2 = -1;
  }
  else {
    *(uint *)(param_1 + 0xc) = *(uint *)(param_1 + 0xc) & 0xffffffef;
    if (param_3 == 1) {
      iVar2 = FUN_0052b260(param_1);
      param_2 = param_2 + iVar2;
      param_3 = 0;
    }
    FUN_00530360(param_1);
    if ((*(uint *)(param_1 + 0xc) & 0x80) == 0) {
      if ((((*(uint *)(param_1 + 0xc) & 1) != 0) && ((*(uint *)(param_1 + 0xc) & 8) != 0)) &&
         ((*(uint *)(param_1 + 0xc) & 0x400) == 0)) {
        *(undefined4 *)(param_1 + 0x18) = 0x200;
      }
    }
    else {
      *(uint *)(param_1 + 0xc) = *(uint *)(param_1 + 0xc) & 0xfffffffc;
    }
    iVar2 = FUN_00531eb0(*(undefined4 *)(param_1 + 0x10),param_2,param_3);
    iVar2 = (iVar2 != -1) - 1;
  }
  return iVar2;
}


// 0052b620

int FUN_0052b620(int param_1)

{
  undefined4 local_8;
  
  if (param_1 < 0) {
    local_8 = -param_1;
  }
  else {
    local_8 = param_1;
  }
  return local_8;
}


// 0052b650

undefined4 * FUN_0052b650(undefined4 *param_1,undefined4 *param_2,uint param_3)

{
  uint uVar1;
  undefined4 *puVar2;
  
  if ((param_2 < param_1) && (param_1 < (undefined4 *)(param_3 + (int)param_2))) {
    param_2 = (undefined4 *)((param_3 - 4) + (int)param_2);
    puVar2 = (undefined4 *)((param_3 - 4) + (int)param_1);
    if (((uint)puVar2 & 3) == 0) {
      uVar1 = param_3 >> 2;
      param_3 = param_3 & 3;
      if (7 < uVar1) {
        for (; uVar1 != 0; uVar1 = uVar1 - 1) {
          *puVar2 = *param_2;
          param_2 = param_2 + -1;
          puVar2 = puVar2 + -1;
        }
        switch(param_3) {
        case 0:
          return param_1;
        case 2:
          goto LAB_0052b958;
        case 3:
          goto LAB_0052b96c;
        }
        goto LAB_0052b948;
      }
    }
    else {
      switch(param_3) {
      case 0:
        goto LAB_0052b940;
      case 1:
        goto LAB_0052b948;
      case 2:
        goto LAB_0052b958;
      case 3:
        goto LAB_0052b96c;
      default:
        uVar1 = param_3 - ((uint)puVar2 & 3);
        switch((uint)puVar2 & 3) {
        case 1:
          param_3 = uVar1 & 3;
          *(undefined1 *)((int)puVar2 + 3) = *(undefined1 *)((int)param_2 + 3);
          param_2 = (undefined4 *)((int)param_2 + -1);
          uVar1 = uVar1 >> 2;
          puVar2 = (undefined4 *)((int)puVar2 - 1);
          if (7 < uVar1) {
            for (; uVar1 != 0; uVar1 = uVar1 - 1) {
              *puVar2 = *param_2;
              param_2 = param_2 + -1;
              puVar2 = puVar2 + -1;
            }
            switch(param_3) {
            case 0:
              return param_1;
            case 2:
              goto LAB_0052b958;
            case 3:
              goto LAB_0052b96c;
            }
            goto LAB_0052b948;
          }
          break;
        case 2:
          param_3 = uVar1 & 3;
          *(undefined1 *)((int)puVar2 + 3) = *(undefined1 *)((int)param_2 + 3);
          uVar1 = uVar1 >> 2;
          *(undefined1 *)((int)puVar2 + 2) = *(undefined1 *)((int)param_2 + 2);
          param_2 = (undefined4 *)((int)param_2 + -2);
          puVar2 = (undefined4 *)((int)puVar2 - 2);
          if (7 < uVar1) {
            for (; uVar1 != 0; uVar1 = uVar1 - 1) {
              *puVar2 = *param_2;
              param_2 = param_2 + -1;
              puVar2 = puVar2 + -1;
            }
            switch(param_3) {
            case 0:
              return param_1;
            case 2:
              goto LAB_0052b958;
            case 3:
              goto LAB_0052b96c;
            }
            goto LAB_0052b948;
          }
          break;
        case 3:
          param_3 = uVar1 & 3;
          *(undefined1 *)((int)puVar2 + 3) = *(undefined1 *)((int)param_2 + 3);
          *(undefined1 *)((int)puVar2 + 2) = *(undefined1 *)((int)param_2 + 2);
          uVar1 = uVar1 >> 2;
          *(undefined1 *)((int)puVar2 + 1) = *(undefined1 *)((int)param_2 + 1);
          param_2 = (undefined4 *)((int)param_2 + -3);
          puVar2 = (undefined4 *)((int)puVar2 - 3);
          if (7 < uVar1) {
            for (; uVar1 != 0; uVar1 = uVar1 - 1) {
              *puVar2 = *param_2;
              param_2 = param_2 + -1;
              puVar2 = puVar2 + -1;
            }
            switch(param_3) {
            case 0:
              return param_1;
            case 2:
              goto LAB_0052b958;
            case 3:
              goto LAB_0052b96c;
            }
            goto LAB_0052b948;
          }
        }
      }
    }
    switch(uVar1) {
    case 7:
      puVar2[7 - uVar1] = param_2[7 - uVar1];
    case 6:
      puVar2[6 - uVar1] = param_2[6 - uVar1];
    case 5:
      puVar2[5 - uVar1] = param_2[5 - uVar1];
    case 4:
      puVar2[4 - uVar1] = param_2[4 - uVar1];
    case 3:
      puVar2[3 - uVar1] = param_2[3 - uVar1];
    case 2:
      puVar2[2 - uVar1] = param_2[2 - uVar1];
    case 1:
      puVar2[1 - uVar1] = param_2[1 - uVar1];
      param_2 = param_2 + -uVar1;
      puVar2 = puVar2 + -uVar1;
    }
    switch(param_3) {
    case 1:
LAB_0052b948:
      *(undefined1 *)((int)puVar2 + 3) = *(undefined1 *)((int)param_2 + 3);
      return param_1;
    case 2:
LAB_0052b958:
      *(undefined1 *)((int)puVar2 + 3) = *(undefined1 *)((int)param_2 + 3);
      *(undefined1 *)((int)puVar2 + 2) = *(undefined1 *)((int)param_2 + 2);
      return param_1;
    case 3:
LAB_0052b96c:
      *(undefined1 *)((int)puVar2 + 3) = *(undefined1 *)((int)param_2 + 3);
      *(undefined1 *)((int)puVar2 + 2) = *(undefined1 *)((int)param_2 + 2);
      *(undefined1 *)((int)puVar2 + 1) = *(undefined1 *)((int)param_2 + 1);
      return param_1;
    }
LAB_0052b940:
    return param_1;
  }
  puVar2 = param_1;
  if (((uint)param_1 & 3) == 0) {
    uVar1 = param_3 >> 2;
    param_3 = param_3 & 3;
    if (7 < uVar1) {
      for (; uVar1 != 0; uVar1 = uVar1 - 1) {
        *puVar2 = *param_2;
        param_2 = param_2 + 1;
        puVar2 = puVar2 + 1;
      }
      switch(param_3) {
      case 0:
        return param_1;
      case 2:
        goto LAB_0052b7bc;
      case 3:
        goto LAB_0052b7d0;
      }
      goto LAB_0052b7b0;
    }
  }
  else {
    switch(param_3) {
    case 0:
      goto LAB_0052b7a8;
    case 1:
      goto LAB_0052b7b0;
    case 2:
      goto LAB_0052b7bc;
    case 3:
      goto LAB_0052b7d0;
    default:
      uVar1 = (param_3 - 4) + ((uint)param_1 & 3);
      switch((uint)param_1 & 3) {
      case 1:
        param_3 = uVar1 & 3;
        *(undefined1 *)param_1 = *(undefined1 *)param_2;
        *(undefined1 *)((int)param_1 + 1) = *(undefined1 *)((int)param_2 + 1);
        uVar1 = uVar1 >> 2;
        *(undefined1 *)((int)param_1 + 2) = *(undefined1 *)((int)param_2 + 2);
        param_2 = (undefined4 *)((int)param_2 + 3);
        puVar2 = (undefined4 *)((int)param_1 + 3);
        if (7 < uVar1) {
          for (; uVar1 != 0; uVar1 = uVar1 - 1) {
            *puVar2 = *param_2;
            param_2 = param_2 + 1;
            puVar2 = puVar2 + 1;
          }
          switch(param_3) {
          case 0:
            return param_1;
          case 2:
            goto LAB_0052b7bc;
          case 3:
            goto LAB_0052b7d0;
          }
          goto LAB_0052b7b0;
        }
        break;
      case 2:
        param_3 = uVar1 & 3;
        *(undefined1 *)param_1 = *(undefined1 *)param_2;
        uVar1 = uVar1 >> 2;
        *(undefined1 *)((int)param_1 + 1) = *(undefined1 *)((int)param_2 + 1);
        param_2 = (undefined4 *)((int)param_2 + 2);
        puVar2 = (undefined4 *)((int)param_1 + 2);
        if (7 < uVar1) {
          for (; uVar1 != 0; uVar1 = uVar1 - 1) {
            *puVar2 = *param_2;
            param_2 = param_2 + 1;
            puVar2 = puVar2 + 1;
          }
          switch(param_3) {
          case 0:
            return param_1;
          case 2:
            goto LAB_0052b7bc;
          case 3:
            goto LAB_0052b7d0;
          }
          goto LAB_0052b7b0;
        }
        break;
      case 3:
        param_3 = uVar1 & 3;
        *(undefined1 *)param_1 = *(undefined1 *)param_2;
        param_2 = (undefined4 *)((int)param_2 + 1);
        uVar1 = uVar1 >> 2;
        puVar2 = (undefined4 *)((int)param_1 + 1);
        if (7 < uVar1) {
          for (; uVar1 != 0; uVar1 = uVar1 - 1) {
            *puVar2 = *param_2;
            param_2 = param_2 + 1;
            puVar2 = puVar2 + 1;
          }
          switch(param_3) {
          case 0:
            return param_1;
          case 2:
            goto LAB_0052b7bc;
          case 3:
            goto LAB_0052b7d0;
          }
          goto LAB_0052b7b0;
        }
      }
    }
  }
  switch(uVar1) {
  case 7:
    puVar2[uVar1 - 7] = param_2[uVar1 - 7];
  case 6:
    puVar2[uVar1 - 6] = param_2[uVar1 - 6];
  case 5:
    puVar2[uVar1 - 5] = param_2[uVar1 - 5];
  case 4:
    puVar2[uVar1 - 4] = param_2[uVar1 - 4];
  case 3:
    puVar2[uVar1 - 3] = param_2[uVar1 - 3];
  case 2:
    puVar2[uVar1 - 2] = param_2[uVar1 - 2];
  case 1:
    puVar2[uVar1 - 1] = param_2[uVar1 - 1];
    param_2 = param_2 + uVar1;
    puVar2 = puVar2 + uVar1;
  }
  switch(param_3) {
  case 1:
LAB_0052b7b0:
    *(undefined1 *)puVar2 = *(undefined1 *)param_2;
    return param_1;
  case 2:
LAB_0052b7bc:
    *(undefined1 *)puVar2 = *(undefined1 *)param_2;
    *(undefined1 *)((int)puVar2 + 1) = *(undefined1 *)((int)param_2 + 1);
    return param_1;
  case 3:
LAB_0052b7d0:
    *(undefined1 *)puVar2 = *(undefined1 *)param_2;
    *(undefined1 *)((int)puVar2 + 1) = *(undefined1 *)((int)param_2 + 1);
    *(undefined1 *)((int)puVar2 + 2) = *(undefined1 *)((int)param_2 + 2);
    return param_1;
  }
LAB_0052b7a8:
  return param_1;
}


// 0052b988

/* Library Function - Single Match
    __ftol
   
   Library: Visual Studio */

longlong __ftol(void)

{
  float10 in_ST0;
  
  return (longlong)ROUND(in_ST0);
}


// 0052b9b0

int FUN_0052b9b0(int param_1)

{
  return param_1 + -0x20;
}


// 0052b9c0

uint FUN_0052b9c0(uint param_1)

{
  int iVar1;
  uint local_14;
  uint local_10;
  undefined1 local_c;
  undefined1 local_b;
  undefined1 local_a;
  undefined4 local_8;
  
  if (DAT_00b940cc == 0) {
    if ((0x60 < (int)param_1) && ((int)param_1 < 0x7b)) {
      param_1 = param_1 - 0x20;
    }
  }
  else {
    if ((int)param_1 < 0x100) {
      if (DAT_0057a5fc < 2) {
        local_14 = *(ushort *)(PTR_DAT_0057a3f0 + param_1 * 2) & 2;
      }
      else {
        local_14 = FUN_00532300(param_1,2);
      }
      if (local_14 == 0) {
        return param_1;
      }
    }
    if ((*(ushort *)(PTR_DAT_0057a3f0 + ((int)param_1 >> 8 & 0xffU) * 2) & 0x8000) == 0) {
      local_c = (undefined1)param_1;
      local_b = 0;
      local_8 = 1;
    }
    else {
      local_c = (undefined1)(param_1 >> 8);
      local_b = (undefined1)param_1;
      local_a = 0;
      local_8 = 2;
    }
    iVar1 = FUN_00531fa0(DAT_00b940cc,0x200,&local_c,local_8,&local_10,3,0,1);
    if (iVar1 != 0) {
      if (iVar1 == 1) {
        param_1 = local_10 & 0xff;
      }
      else {
        param_1 = local_10 & 0xff | (local_10 >> 8 & 0xff) << 8;
      }
    }
  }
  return param_1;
}


// 0052baf0

uint FUN_0052baf0(int *param_1)

{
  code *pcVar1;
  int iVar2;
  uint uVar3;
  uint local_c;
  
  if ((param_1 == (int *)0x0) &&
     (iVar2 = FUN_0052fad0(2,"fgetc.c",0x29,0,"stream != NULL"), iVar2 == 1)) {
    pcVar1 = (code *)swi(3);
    uVar3 = (*pcVar1)();
    return uVar3;
  }
  param_1[1] = param_1[1] + -1;
  if (param_1[1] < 0) {
    local_c = FUN_00530510(param_1);
  }
  else {
    local_c = (uint)*(byte *)*param_1;
    *param_1 = *param_1 + 1;
  }
  return local_c;
}


// 0052bb80

void FUN_0052bb80(undefined4 param_1)

{
  FUN_0052baf0(param_1);
  return;
}


// 0052bba0

/* Library Function - Single Match
    _strncpy
   
   Libraries: Visual Studio 1998 Debug, Visual Studio 1998 Release */

char * __cdecl _strncpy(char *_Dest,char *_Source,size_t _Count)

{
  uint uVar1;
  uint uVar2;
  char cVar3;
  uint uVar4;
  uint *puVar5;
  
  if (_Count == 0) {
    return _Dest;
  }
  puVar5 = (uint *)_Dest;
  if (((uint)_Source & 3) != 0) {
    while( true ) {
      uVar4 = *(uint *)_Source;
      _Source = (char *)((int)_Source + 1);
      *(char *)puVar5 = (char)uVar4;
      puVar5 = (uint *)((int)puVar5 + 1);
      _Count = _Count - 1;
      if (_Count == 0) {
        return _Dest;
      }
      if ((char)uVar4 == '\0') break;
      if (((uint)_Source & 3) == 0) {
        uVar4 = _Count >> 2;
        goto joined_r0x0052bbde;
      }
    }
    do {
      if (((uint)puVar5 & 3) == 0) {
        uVar4 = _Count >> 2;
        cVar3 = '\0';
        if (uVar4 == 0) goto LAB_0052bc1b;
        goto LAB_0052bc89;
      }
      *(char *)puVar5 = '\0';
      puVar5 = (uint *)((int)puVar5 + 1);
      _Count = _Count - 1;
    } while (_Count != 0);
    return _Dest;
  }
  uVar4 = _Count >> 2;
  if (uVar4 != 0) {
    do {
      uVar1 = *(uint *)_Source;
      uVar2 = *(uint *)_Source;
      _Source = (char *)((int)_Source + 4);
      if (((uVar1 ^ 0xffffffff ^ uVar1 + 0x7efefeff) & 0x81010100) != 0) {
        if ((char)uVar2 == '\0') {
          *puVar5 = 0;
joined_r0x0052bc85:
          while( true ) {
            uVar4 = uVar4 - 1;
            puVar5 = puVar5 + 1;
            if (uVar4 == 0) break;
LAB_0052bc89:
            *puVar5 = 0;
          }
          cVar3 = '\0';
          _Count = _Count & 3;
          if (_Count != 0) goto LAB_0052bc1b;
          return _Dest;
        }
        if ((char)(uVar2 >> 8) == '\0') {
          *puVar5 = uVar2 & 0xff;
          goto joined_r0x0052bc85;
        }
        if ((uVar2 & 0xff0000) == 0) {
          *puVar5 = uVar2 & 0xffff;
          goto joined_r0x0052bc85;
        }
        if ((uVar2 & 0xff000000) == 0) {
          *puVar5 = uVar2;
          goto joined_r0x0052bc85;
        }
      }
      *puVar5 = uVar2;
      puVar5 = puVar5 + 1;
      uVar4 = uVar4 - 1;
joined_r0x0052bbde:
    } while (uVar4 != 0);
    _Count = _Count & 3;
    if (_Count == 0) {
      return _Dest;
    }
  }
  do {
    cVar3 = (char)*(uint *)_Source;
    _Source = (char *)((int)_Source + 1);
    *(char *)puVar5 = cVar3;
    puVar5 = (uint *)((int)puVar5 + 1);
    if (cVar3 == '\0') {
      while (_Count = _Count - 1, _Count != 0) {
LAB_0052bc1b:
        *(char *)puVar5 = cVar3;
        puVar5 = (uint *)((int)puVar5 + 1);
      }
      return _Dest;
    }
    _Count = _Count - 1;
  } while (_Count != 0);
  return _Dest;
}


// 0052bca0

/* Library Function - Single Match
    _strlen
   
   Libraries: Visual Studio 1998 Debug, Visual Studio 1998 Release */

size_t __cdecl _strlen(char *_Str)

{
  uint uVar1;
  uint *puVar2;
  uint *puVar3;
  
  puVar2 = (uint *)_Str;
  do {
    if (((uint)puVar2 & 3) == 0) goto LAB_0052bcc0;
    uVar1 = *puVar2;
    puVar2 = (uint *)((int)puVar2 + 1);
  } while ((char)uVar1 != '\0');
LAB_0052bcf3:
  return (size_t)((int)puVar2 + (-1 - (int)_Str));
LAB_0052bcc0:
  do {
    do {
      puVar3 = puVar2;
      puVar2 = puVar3 + 1;
    } while (((*puVar3 ^ 0xffffffff ^ *puVar3 + 0x7efefeff) & 0x81010100) == 0);
    uVar1 = *puVar3;
    if ((char)uVar1 == '\0') {
      return (int)puVar3 - (int)_Str;
    }
    if ((char)(uVar1 >> 8) == '\0') {
      return (size_t)((int)puVar3 + (1 - (int)_Str));
    }
    if ((uVar1 & 0xff0000) == 0) {
      return (size_t)((int)puVar3 + (2 - (int)_Str));
    }
  } while ((uVar1 & 0xff000000) != 0);
  goto LAB_0052bcf3;
}


// 0052bd20

/* Library Function - Single Match
    _strcmp
   
   Libraries: Visual Studio 1998 Debug, Visual Studio 1998 Release */

int __cdecl _strcmp(char *_Str1,char *_Str2)

{
  undefined2 uVar1;
  undefined4 uVar2;
  byte bVar3;
  byte bVar4;
  bool bVar5;
  
  if (((uint)_Str1 & 3) != 0) {
    if (((uint)_Str1 & 1) != 0) {
      bVar4 = *_Str1;
      _Str1 = _Str1 + 1;
      bVar5 = bVar4 < (byte)*_Str2;
      if (bVar4 != *_Str2) goto LAB_0052bd64;
      _Str2 = _Str2 + 1;
      if (bVar4 == 0) {
        return 0;
      }
      if (((uint)_Str1 & 2) == 0) goto LAB_0052bd30;
    }
    uVar1 = *(undefined2 *)_Str1;
    _Str1 = _Str1 + 2;
    bVar4 = (byte)uVar1;
    bVar5 = bVar4 < (byte)*_Str2;
    if (bVar4 != *_Str2) goto LAB_0052bd64;
    if (bVar4 == 0) {
      return 0;
    }
    bVar4 = (byte)((ushort)uVar1 >> 8);
    bVar5 = bVar4 < (byte)_Str2[1];
    if (bVar4 != _Str2[1]) goto LAB_0052bd64;
    if (bVar4 == 0) {
      return 0;
    }
    _Str2 = _Str2 + 2;
  }
LAB_0052bd30:
  while( true ) {
    uVar2 = *(undefined4 *)_Str1;
    bVar4 = (byte)uVar2;
    bVar5 = bVar4 < (byte)*_Str2;
    if (bVar4 != *_Str2) break;
    if (bVar4 == 0) {
      return 0;
    }
    bVar4 = (byte)((uint)uVar2 >> 8);
    bVar5 = bVar4 < (byte)_Str2[1];
    if (bVar4 != _Str2[1]) break;
    if (bVar4 == 0) {
      return 0;
    }
    bVar4 = (byte)((uint)uVar2 >> 0x10);
    bVar5 = bVar4 < (byte)_Str2[2];
    if (bVar4 != _Str2[2]) break;
    bVar3 = (byte)((uint)uVar2 >> 0x18);
    if (bVar4 == 0) {
      return 0;
    }
    bVar5 = bVar3 < (byte)_Str2[3];
    if (bVar3 != _Str2[3]) break;
    _Str2 = _Str2 + 4;
    _Str1 = _Str1 + 4;
    if (bVar3 == 0) {
      return 0;
    }
  }
LAB_0052bd64:
  return (uint)bVar5 * -2 + 1;
}


// 0052bdb0

int FUN_0052bdb0(byte *param_1)

{
  byte *pbVar1;
  uint uVar2;
  uint local_18;
  uint local_14;
  int local_c;
  uint local_8;
  
  while( true ) {
    if (DAT_0057a5fc < 2) {
      local_14 = *(ushort *)(PTR_DAT_0057a3f0 + (uint)*param_1 * 2) & 8;
    }
    else {
      local_14 = FUN_00532300(*param_1,8);
    }
    if (local_14 == 0) break;
    param_1 = param_1 + 1;
  }
  uVar2 = (uint)*param_1;
  if ((uVar2 == 0x2d) || (pbVar1 = param_1 + 1, local_8 = uVar2, uVar2 == 0x2b)) {
    local_8 = (uint)param_1[1];
    pbVar1 = param_1 + 2;
  }
  param_1 = pbVar1;
  local_c = 0;
  while( true ) {
    if (DAT_0057a5fc < 2) {
      local_18 = *(ushort *)(PTR_DAT_0057a3f0 + local_8 * 2) & 4;
    }
    else {
      local_18 = FUN_00532300(local_8,4);
    }
    if (local_18 == 0) break;
    local_c = local_c * 10 + -0x30 + local_8;
    local_8 = (uint)*param_1;
    param_1 = param_1 + 1;
  }
  if (uVar2 == 0x2d) {
    local_c = -local_c;
  }
  return local_c;
}


// 0052beb0

void FUN_0052beb0(undefined4 param_1)

{
  FUN_0052bdb0(param_1);
  return;
}


// 0052bed0

longlong FUN_0052bed0(byte *param_1)

{
  byte *pbVar1;
  uint uVar2;
  longlong lVar3;
  uint local_1c;
  uint local_18;
  int local_10;
  int local_c;
  uint local_8;
  
  while( true ) {
    if (DAT_0057a5fc < 2) {
      local_18 = *(ushort *)(PTR_DAT_0057a3f0 + (uint)*param_1 * 2) & 8;
    }
    else {
      local_18 = FUN_00532300(*param_1,8);
    }
    if (local_18 == 0) break;
    param_1 = param_1 + 1;
  }
  uVar2 = (uint)*param_1;
  if ((uVar2 == 0x2d) || (pbVar1 = param_1 + 1, local_8 = uVar2, uVar2 == 0x2b)) {
    local_8 = (uint)param_1[1];
    pbVar1 = param_1 + 2;
  }
  param_1 = pbVar1;
  lVar3 = 0;
  while( true ) {
    local_c = (int)((ulonglong)lVar3 >> 0x20);
    local_10 = (int)lVar3;
    if (DAT_0057a5fc < 2) {
      local_1c = *(ushort *)(PTR_DAT_0057a3f0 + local_8 * 2) & 4;
    }
    else {
      local_1c = FUN_00532300(local_8,4);
    }
    if (local_1c == 0) break;
    lVar3 = __allmul(lVar3,10,0);
    lVar3 = lVar3 + (int)(local_8 - 0x30);
    local_8 = (uint)*param_1;
    param_1 = param_1 + 1;
  }
  if (uVar2 == 0x2d) {
    lVar3 = CONCAT44(-(local_c + (uint)(local_10 != 0)),-local_10);
  }
  return lVar3;
}


// 0052c000

char * FUN_0052c000(char *param_1,int param_2,int *param_3)

{
  code *pcVar1;
  int iVar2;
  char *pcVar3;
  uint local_18;
  char local_10;
  char *local_c;
  
  local_c = param_1;
  if ((param_1 == (char *)0x0) &&
     (iVar2 = FUN_0052fad0(2,"fgets.c",0x3b,0,"string != NULL"), iVar2 == 1)) {
    pcVar1 = (code *)swi(3);
    pcVar3 = (char *)(*pcVar1)();
    return pcVar3;
  }
  if ((param_3 == (int *)0x0) &&
     (iVar2 = FUN_0052fad0(2,"fgets.c",0x3c,0,"str != NULL"), iVar2 == 1)) {
    pcVar1 = (code *)swi(3);
    pcVar3 = (char *)(*pcVar1)();
    return pcVar3;
  }
  if (param_2 < 1) {
    param_1 = (char *)0x0;
  }
  else {
    do {
      param_2 = param_2 + -1;
      if (param_2 == 0) break;
      param_3[1] = param_3[1] + -1;
      if (param_3[1] < 0) {
        local_18 = FUN_00530510(param_3);
      }
      else {
        local_18 = (uint)*(byte *)*param_3;
        *param_3 = *param_3 + 1;
      }
      if (local_18 == 0xffffffff) {
        if (local_c == param_1) {
          return (char *)0x0;
        }
        break;
      }
      local_10 = (char)local_18;
      *local_c = local_10;
      local_c = local_c + 1;
    } while (local_10 != '\n');
    *local_c = '\0';
  }
  return param_1;
}


// 0052c130

void FUN_0052c130(undefined4 param_1)

{
  __nh_malloc_dbg(param_1,DAT_00b940e4,1,0,0);
  return;
}


// 0052c150

void FUN_0052c150(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  __nh_malloc_dbg(param_1,DAT_00b940e4,param_2,param_3,param_4);
  return;
}


// 0052c180

/* Library Function - Single Match
    __nh_malloc
   
   Library: Visual Studio 2003 Debug */

void * __cdecl __nh_malloc(size_t _Size,int _NhFlag)

{
  void *pvVar1;
  
  pvVar1 = (void *)__nh_malloc_dbg(_Size,_NhFlag,1,0,0);
  return pvVar1;
}


// 0052c1a0

/* Library Function - Single Match
    __nh_malloc_dbg
   
   Library: Visual Studio 2003 Debug */

int __thiscall
__nh_malloc_dbg(int param_1,size_t param_2,int param_3,undefined4 param_4,undefined4 param_5,
               undefined4 param_6)

{
  int iVar1;
  
  while( true ) {
    param_1 = FUN_0052c210(param_2,param_4,param_5,param_6,param_1);
    if (param_1 != 0) {
      return param_1;
    }
    if (param_3 == 0) break;
    iVar1 = __callnewh(param_2);
    if (iVar1 == 0) {
      return 0;
    }
  }
  return 0;
}


// 0052c1f0

void FUN_0052c1f0(undefined4 param_1)

{
  FUN_0052c210(param_1,1,0,0);
  return;
}


// 0052c210

undefined4 * FUN_0052c210(uint param_1,uint param_2,int param_3,undefined4 param_4)

{
  code *pcVar1;
  bool bVar2;
  undefined4 *puVar3;
  int iVar4;
  undefined4 *puVar5;
  int iVar6;
  
  bVar2 = false;
  if ((((DAT_0057a1e0 & 4) != 0) && (iVar4 = FUN_0052d250(), iVar4 == 0)) &&
     (iVar4 = FUN_0052fad0(2,"dbgheap.c",0x141,0,"_CrtCheckMemory()"), iVar4 == 1)) {
    pcVar1 = (code *)swi(3);
    puVar5 = (undefined4 *)(*pcVar1)();
    return puVar5;
  }
  iVar4 = DAT_0057a1e4;
  if (DAT_0057a1e4 == DAT_0057a1e8) {
    pcVar1 = (code *)swi(3);
    puVar5 = (undefined4 *)(*pcVar1)();
    return puVar5;
  }
  iVar6 = (*(code *)PTR_FUN_0057a610)(1,0,param_1,param_2,DAT_0057a1e4,param_3,param_4);
  if (iVar6 == 0) {
    if (param_3 == 0) {
      iVar4 = FUN_0052fad0(0,0,0,0,&DAT_00546c68,"Client hook allocation failure.\n");
      if (iVar4 == 1) {
        pcVar1 = (code *)swi(3);
        puVar5 = (undefined4 *)(*pcVar1)();
        return puVar5;
      }
    }
    else {
      iVar4 = FUN_0052fad0(0,0,0,0,"Client hook allocation failure at file %hs line %d.\n",param_3,
                           param_4);
      if (iVar4 == 1) {
        pcVar1 = (code *)swi(3);
        puVar5 = (undefined4 *)(*pcVar1)();
        return puVar5;
      }
    }
    puVar5 = (undefined4 *)0x0;
  }
  else {
    if (((param_2 & 0xffff) != 2) && ((DAT_0057a1e0 & 1) == 0)) {
      bVar2 = true;
    }
    if ((param_1 < 0xffffffe1) && (param_1 + 0x24 < 0xffffffe1)) {
      if (((((param_2 & 0xffff) != 4) && (param_2 != 1)) && ((param_2 & 0xffff) != 2)) &&
         ((param_2 != 3 &&
          (iVar6 = FUN_0052fad0(1,0,0,0,&DAT_00546c68,
                                "Error: memory allocation: bad memory block type.\n"), iVar6 == 1)))
         ) {
        pcVar1 = (code *)swi(3);
        puVar5 = (undefined4 *)(*pcVar1)();
        return puVar5;
      }
      puVar5 = (undefined4 *)FUN_005324e0(param_1 + 0x24);
      if (puVar5 == (undefined4 *)0x0) {
        puVar5 = (undefined4 *)0x0;
      }
      else {
        DAT_0057a1e4 = DAT_0057a1e4 + 1;
        if (bVar2) {
          *puVar5 = 0;
          puVar5[1] = 0;
          puVar5[2] = 0;
          puVar5[3] = 0xfedcbabc;
          puVar5[4] = param_1;
          puVar5[5] = 3;
          puVar5[6] = 0;
        }
        else {
          DAT_00b94040 = DAT_00b94040 + param_1;
          DAT_00b94048 = DAT_00b94048 + param_1;
          if (DAT_00b9404c < DAT_00b94048) {
            DAT_00b9404c = DAT_00b94048;
          }
          puVar3 = puVar5;
          if (DAT_00b94044 != (undefined4 *)0x0) {
            DAT_00b94044[1] = puVar5;
            puVar3 = DAT_00b9403c;
          }
          DAT_00b9403c = puVar3;
          *puVar5 = DAT_00b94044;
          puVar5[1] = 0;
          puVar5[2] = param_3;
          puVar5[3] = param_4;
          puVar5[4] = param_1;
          puVar5[5] = param_2;
          puVar5[6] = iVar4;
          DAT_00b94044 = puVar5;
        }
        _memset(puVar5 + 7,(uint)DAT_0057a1ec,4);
        _memset((void *)((int)puVar5 + param_1 + 0x20),(uint)DAT_0057a1ec,4);
        _memset(puVar5 + 8,(uint)DAT_0057a1ee,param_1);
        puVar5 = puVar5 + 8;
      }
    }
    else {
      iVar4 = FUN_0052fad0(1,0,0,0,"Invalid allocation size: %u bytes.\n",param_1);
      if (iVar4 == 1) {
        pcVar1 = (code *)swi(3);
        puVar5 = (undefined4 *)(*pcVar1)();
        return puVar5;
      }
      puVar5 = (undefined4 *)0x0;
    }
  }
  return puVar5;
}


// 0052c530

void FUN_0052c530(undefined4 param_1,undefined4 param_2)

{
  __calloc_dbg(param_1,param_2,1,0,0);
  return;
}


// 0052c550

/* Library Function - Single Match
    __calloc_dbg
   
   Library: Visual Studio 2003 Debug */

undefined1 *
__calloc_dbg(int param_1,int param_2,undefined4 param_3,undefined4 param_4,undefined4 param_5)

{
  undefined1 *puVar1;
  undefined1 *local_10;
  
  puVar1 = (undefined1 *)FUN_0052c150(param_2 * param_1,param_3,param_4,param_5);
  if (puVar1 != (undefined1 *)0x0) {
    for (local_10 = puVar1; local_10 < puVar1 + param_2 * param_1; local_10 = local_10 + 1) {
      *local_10 = 0;
    }
  }
  return puVar1;
}


// 0052c5b0

void FUN_0052c5b0(undefined4 param_1,undefined4 param_2)

{
  __realloc_dbg(param_1,param_2,1,0,0);
  return;
}


// 0052c5d0

/* Library Function - Single Match
    __realloc_dbg
   
   Library: Visual Studio 2003 Debug */

undefined4 __thiscall
__realloc_dbg(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,
             undefined4 param_5,undefined4 param_6)

{
  undefined4 uVar1;
  
  uVar1 = FUN_0052c600(param_2,param_3,param_4,param_5,param_6,1,param_1);
  return uVar1;
}


// 0052c600

int * FUN_0052c600(int param_1,uint param_2,uint param_3,int param_4,int param_5,int param_6)

{
  code *pcVar1;
  int *piVar2;
  int iVar3;
  int *piVar4;
  int iVar5;
  bool bVar6;
  int *local_10;
  
  if (param_1 == 0) {
    piVar2 = (int *)FUN_0052c150(param_2,param_3,param_4,param_5);
  }
  else if ((param_6 == 0) || (param_2 != 0)) {
    if (((DAT_0057a1e0 & 4) != 0) &&
       ((iVar3 = FUN_0052d250(), iVar3 == 0 &&
        (iVar3 = FUN_0052fad0(2,"dbgheap.c",0x239,0,"_CrtCheckMemory()"), iVar3 == 1)))) {
      pcVar1 = (code *)swi(3);
      piVar4 = (int *)(*pcVar1)();
      return piVar4;
    }
    iVar3 = DAT_0057a1e4;
    if (DAT_0057a1e4 == DAT_0057a1e8) {
      pcVar1 = (code *)swi(3);
      piVar4 = (int *)(*pcVar1)();
      return piVar4;
    }
    iVar5 = (*(code *)PTR_FUN_0057a610)(2,param_1,param_2,param_3,DAT_0057a1e4,param_4,param_5);
    if (iVar5 == 0) {
      if (param_4 == 0) {
        iVar3 = FUN_0052fad0(0,0,0,0,&DAT_00546c68,"Client hook re-allocation failure.\n");
        if (iVar3 == 1) {
          pcVar1 = (code *)swi(3);
          piVar4 = (int *)(*pcVar1)();
          return piVar4;
        }
      }
      else {
        iVar3 = FUN_0052fad0(0,0,0,0,"Client hook re-allocation failure at file %hs line %d.\n",
                             param_4,param_5);
        if (iVar3 == 1) {
          pcVar1 = (code *)swi(3);
          piVar4 = (int *)(*pcVar1)();
          return piVar4;
        }
      }
      piVar2 = (int *)0x0;
    }
    else if (param_2 < 0xffffffdc) {
      if ((((param_3 != 1) && ((param_3 & 0xffff) != 4)) && ((param_3 & 0xffff) != 2)) &&
         (iVar5 = FUN_0052fad0(1,0,0,0,&DAT_00546c68,
                               "Error: memory allocation: bad memory block type.\n"), iVar5 == 1)) {
        pcVar1 = (code *)swi(3);
        piVar4 = (int *)(*pcVar1)();
        return piVar4;
      }
      iVar5 = FUN_0052d690(param_1);
      if ((iVar5 == 0) &&
         (iVar5 = FUN_0052fad0(2,"dbgheap.c",0x261,0,"_CrtIsValidHeapPointer(pUserData)"),
         iVar5 == 1)) {
        pcVar1 = (code *)swi(3);
        piVar4 = (int *)(*pcVar1)();
        return piVar4;
      }
      piVar4 = (int *)(param_1 + -0x20);
      bVar6 = *(int *)(param_1 + -0xc) == 3;
      if (bVar6) {
        if (((*(int *)(param_1 + -0x14) != -0x1234544) || (*(int *)(param_1 + -8) != 0)) &&
           (iVar5 = FUN_0052fad0(2,"dbgheap.c",0x26b,0,
                                 "pOldBlock->nLine == IGNORE_LINE && pOldBlock->lRequest == IGNORE_REQ"
                                ), iVar5 == 1)) {
          pcVar1 = (code *)swi(3);
          piVar4 = (int *)(*pcVar1)();
          return piVar4;
        }
      }
      else {
        if (((*(uint *)(param_1 + -0xc) & 0xffff) == 2) && ((param_3 & 0xffff) == 1)) {
          param_3 = 2;
        }
        if (((*(uint *)(param_1 + -0xc) & 0xffff) != (param_3 & 0xffff)) &&
           (iVar5 = FUN_0052fad0(2,"dbgheap.c",0x272,0,
                                 "_BLOCK_TYPE(pOldBlock->nBlockUse)==_BLOCK_TYPE(nBlockUse)"),
           iVar5 == 1)) {
          pcVar1 = (code *)swi(3);
          piVar4 = (int *)(*pcVar1)();
          return piVar4;
        }
      }
      if (param_6 == 0) {
        local_10 = (int *)FUN_00532550(piVar4,param_2 + 0x24);
        if (local_10 == (int *)0x0) {
          return (int *)0x0;
        }
      }
      else {
        local_10 = (int *)FUN_005325e0(piVar4,param_2 + 0x24);
        if (local_10 == (int *)0x0) {
          return (int *)0x0;
        }
      }
      DAT_0057a1e4 = DAT_0057a1e4 + 1;
      if (!bVar6) {
        DAT_00b94040 = (DAT_00b94040 - local_10[4]) + param_2;
        DAT_00b94048 = (DAT_00b94048 - local_10[4]) + param_2;
        if (DAT_00b9404c < DAT_00b94048) {
          DAT_00b9404c = DAT_00b94048;
        }
      }
      piVar2 = local_10 + 8;
      if ((uint)local_10[4] < param_2) {
        _memset((void *)((int)piVar2 + local_10[4]),(uint)DAT_0057a1ee,param_2 - local_10[4]);
      }
      _memset((void *)((int)piVar2 + param_2),(uint)DAT_0057a1ec,4);
      if (!bVar6) {
        local_10[2] = param_4;
        local_10[3] = param_5;
        local_10[6] = iVar3;
      }
      local_10[4] = param_2;
      if (((param_6 == 0) && (local_10 != piVar4)) &&
         (iVar3 = FUN_0052fad0(2,"dbgheap.c",0x2a8,0,
                               "fRealloc || (!fRealloc && pNewBlock == pOldBlock)"), iVar3 == 1)) {
        pcVar1 = (code *)swi(3);
        piVar4 = (int *)(*pcVar1)();
        return piVar4;
      }
      if ((local_10 != piVar4) && (!bVar6)) {
        if (*local_10 == 0) {
          if ((DAT_00b9403c != piVar4) &&
             (iVar3 = FUN_0052fad0(2,"dbgheap.c",0x2b7,0,"_pLastBlock == pOldBlock"), iVar3 == 1)) {
            pcVar1 = (code *)swi(3);
            piVar4 = (int *)(*pcVar1)();
            return piVar4;
          }
          DAT_00b9403c = (int *)local_10[1];
        }
        else {
          *(int *)(*local_10 + 4) = local_10[1];
        }
        if (local_10[1] == 0) {
          if ((DAT_00b94044 != piVar4) &&
             (iVar3 = FUN_0052fad0(2,"dbgheap.c",0x2c2,0,"_pFirstBlock == pOldBlock"), iVar3 == 1))
          {
            pcVar1 = (code *)swi(3);
            piVar4 = (int *)(*pcVar1)();
            return piVar4;
          }
          DAT_00b94044 = (int *)*local_10;
        }
        else {
          *(int *)local_10[1] = *local_10;
        }
        if (DAT_00b94044 == (int *)0x0) {
          DAT_00b9403c = local_10;
        }
        else {
          DAT_00b94044[1] = (int)local_10;
        }
        *local_10 = (int)DAT_00b94044;
        local_10[1] = 0;
        DAT_00b94044 = local_10;
      }
    }
    else {
      iVar3 = FUN_0052fad0(1,0,0,0,"Allocation too large or negative: %u bytes.\n",param_2);
      if (iVar3 == 1) {
        pcVar1 = (code *)swi(3);
        piVar4 = (int *)(*pcVar1)();
        return piVar4;
      }
      piVar2 = (int *)0x0;
    }
  }
  else {
    FUN_0052cb90(param_1,param_3);
    piVar2 = (int *)0x0;
  }
  return piVar2;
}


// 0052cb20

void FUN_0052cb20(undefined4 param_1,undefined4 param_2)

{
  __expand_dbg(param_1,param_2,1,0,0);
  return;
}


// 0052cb40

/* Library Function - Single Match
    __expand_dbg
   
   Library: Visual Studio 2003 Debug */

undefined4 __thiscall
__expand_dbg(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,
            undefined4 param_5,undefined4 param_6)

{
  undefined4 uVar1;
  
  uVar1 = FUN_0052c600(param_2,param_3,param_4,param_5,param_6,0,param_1);
  return uVar1;
}


// 0052cb70

void FUN_0052cb70(undefined4 param_1)

{
  FUN_0052cb90(param_1,1);
  return;
}


// 0052cb90

void FUN_0052cb90(void *param_1,int param_2)

{
  code *pcVar1;
  int iVar2;
  int *_Dst;
  
  if ((((DAT_0057a1e0 & 4) != 0) && (iVar2 = FUN_0052d250(), iVar2 == 0)) &&
     (iVar2 = FUN_0052fad0(2,"dbgheap.c",0x3e1,0,"_CrtCheckMemory()"), iVar2 == 1)) {
    pcVar1 = (code *)swi(3);
    (*pcVar1)();
    return;
  }
  if (param_1 != (void *)0x0) {
    iVar2 = (*(code *)PTR_FUN_0057a610)(3,param_1,0,param_2,0,0,0);
    if (iVar2 == 0) {
      iVar2 = FUN_0052fad0(0,0,0,0,&DAT_00546c68,"Client hook free failure.\n");
      if (iVar2 == 1) {
        pcVar1 = (code *)swi(3);
        (*pcVar1)();
        return;
      }
    }
    else {
      iVar2 = FUN_0052d690(param_1);
      if ((iVar2 == 0) &&
         (iVar2 = FUN_0052fad0(2,"dbgheap.c",0x3f3,0,"_CrtIsValidHeapPointer(pUserData)"),
         iVar2 == 1)) {
        pcVar1 = (code *)swi(3);
        (*pcVar1)();
        return;
      }
      _Dst = (int *)((int)param_1 + -0x20);
      if ((((*(uint *)((int)param_1 + -0xc) & 0xffff) != 4) && (*(int *)((int)param_1 + -0xc) != 1))
         && (((*(uint *)((int)param_1 + -0xc) & 0xffff) != 2 &&
             ((*(int *)((int)param_1 + -0xc) != 3 &&
              (iVar2 = FUN_0052fad0(2,"dbgheap.c",0x3f9,0,"_BLOCK_TYPE_IS_VALID(pHead->nBlockUse)"),
              iVar2 == 1)))))) {
        pcVar1 = (code *)swi(3);
        (*pcVar1)();
        return;
      }
      if ((DAT_0057a1e0 & 4) == 0) {
        iVar2 = FUN_0052d1c0((int)param_1 + -4,DAT_0057a1ec,4);
        if ((iVar2 == 0) &&
           (iVar2 = FUN_0052fad0(1,0,0,0,"DAMAGE: before %hs block (#%d) at 0x%08X.\n",
                                 (&PTR_DAT_0057a1f0)[*(uint *)((int)param_1 + -0xc) & 0xffff],
                                 *(undefined4 *)((int)param_1 + -8),param_1), iVar2 == 1)) {
          pcVar1 = (code *)swi(3);
          (*pcVar1)();
          return;
        }
        iVar2 = FUN_0052d1c0((int)param_1 + *(int *)((int)param_1 + -0x10),DAT_0057a1ec,4);
        if ((iVar2 == 0) &&
           (iVar2 = FUN_0052fad0(1,0,0,0,"DAMAGE: after %hs block (#%d) at 0x%08X.\n",
                                 (&PTR_DAT_0057a1f0)[*(uint *)((int)param_1 + -0xc) & 0xffff],
                                 *(undefined4 *)((int)param_1 + -8),param_1), iVar2 == 1)) {
          pcVar1 = (code *)swi(3);
          (*pcVar1)();
          return;
        }
      }
      if (*(int *)((int)param_1 + -0xc) == 3) {
        if (((*(int *)((int)param_1 + -0x14) != -0x1234544) || (*(int *)((int)param_1 + -8) != 0))
           && (iVar2 = FUN_0052fad0(2,"dbgheap.c",0x40e,0,
                                    "pHead->nLine == IGNORE_LINE && pHead->lRequest == IGNORE_REQ"),
              iVar2 == 1)) {
          pcVar1 = (code *)swi(3);
          (*pcVar1)();
          return;
        }
        _memset(_Dst,(uint)DAT_0057a1ed,*(int *)((int)param_1 + -0x10) + 0x24);
        FUN_005327b0(_Dst);
      }
      else {
        if ((*(int *)((int)param_1 + -0xc) == 2) && (param_2 == 1)) {
          param_2 = 2;
        }
        if ((*(int *)((int)param_1 + -0xc) != param_2) &&
           (iVar2 = FUN_0052fad0(2,"dbgheap.c",0x41b,0,"pHead->nBlockUse == nBlockUse"), iVar2 == 1)
           ) {
          pcVar1 = (code *)swi(3);
          (*pcVar1)();
          return;
        }
        DAT_00b94048 = DAT_00b94048 - *(int *)((int)param_1 + -0x10);
        if ((DAT_0057a1e0 & 2) == 0) {
          if (*_Dst == 0) {
            if ((DAT_00b9403c != _Dst) &&
               (iVar2 = FUN_0052fad0(2,"dbgheap.c",0x42a,0,"_pLastBlock == pHead"), iVar2 == 1)) {
              pcVar1 = (code *)swi(3);
              (*pcVar1)();
              return;
            }
            DAT_00b9403c = *(int **)((int)param_1 + -0x1c);
          }
          else {
            *(undefined4 *)(*_Dst + 4) = *(undefined4 *)((int)param_1 + -0x1c);
          }
          if (*(int *)((int)param_1 + -0x1c) == 0) {
            if ((DAT_00b94044 != _Dst) &&
               (iVar2 = FUN_0052fad0(2,"dbgheap.c",0x434,0,"_pFirstBlock == pHead"), iVar2 == 1)) {
              pcVar1 = (code *)swi(3);
              (*pcVar1)();
              return;
            }
            DAT_00b94044 = (int *)*_Dst;
          }
          else {
            **(int **)((int)param_1 + -0x1c) = *_Dst;
          }
          _memset(_Dst,(uint)DAT_0057a1ed,*(int *)((int)param_1 + -0x10) + 0x24);
          FUN_005327b0(_Dst);
        }
        else {
          *(undefined4 *)((int)param_1 + -0xc) = 0;
          _memset(param_1,(uint)DAT_0057a1ed,*(size_t *)((int)param_1 + -0x10));
        }
      }
    }
  }
  return;
}


// 0052cf80

void FUN_0052cf80(undefined4 param_1)

{
  FUN_0052cfa0(param_1,1);
  return;
}


// 0052cfa0

undefined4 FUN_0052cfa0(int param_1,int param_2)

{
  code *pcVar1;
  int iVar2;
  undefined4 uVar3;
  
  if ((((DAT_0057a1e0 & 4) != 0) && (iVar2 = FUN_0052d250(), iVar2 == 0)) &&
     (iVar2 = FUN_0052fad0(2,"dbgheap.c",0x47c,0,"_CrtCheckMemory()"), iVar2 == 1)) {
    pcVar1 = (code *)swi(3);
    uVar3 = (*pcVar1)();
    return uVar3;
  }
  iVar2 = FUN_0052d690(param_1);
  if ((iVar2 == 0) &&
     (iVar2 = FUN_0052fad0(2,"dbgheap.c",0x485,0,"_CrtIsValidHeapPointer(pUserData)"), iVar2 == 1))
  {
    pcVar1 = (code *)swi(3);
    uVar3 = (*pcVar1)();
    return uVar3;
  }
  if ((((*(uint *)(param_1 + -0xc) & 0xffff) != 4) && (*(int *)(param_1 + -0xc) != 1)) &&
     (((*(uint *)(param_1 + -0xc) & 0xffff) != 2 &&
      ((*(int *)(param_1 + -0xc) != 3 &&
       (iVar2 = FUN_0052fad0(2,"dbgheap.c",0x48b,0,"_BLOCK_TYPE_IS_VALID(pHead->nBlockUse)"),
       iVar2 == 1)))))) {
    pcVar1 = (code *)swi(3);
    uVar3 = (*pcVar1)();
    return uVar3;
  }
  if ((*(int *)(param_1 + -0xc) == 2) && (param_2 == 1)) {
    param_2 = 2;
  }
  if (((*(int *)(param_1 + -0xc) != 3) && (*(int *)(param_1 + -0xc) != param_2)) &&
     (iVar2 = FUN_0052fad0(2,"dbgheap.c",0x492,0,"pHead->nBlockUse == nBlockUse"), iVar2 == 1)) {
    pcVar1 = (code *)swi(3);
    uVar3 = (*pcVar1)();
    return uVar3;
  }
  return *(undefined4 *)(param_1 + -0x10);
}


// 0052d0f0

undefined4 FUN_0052d0f0(undefined4 param_1)

{
  undefined4 uVar1;
  
  uVar1 = DAT_0057a1e8;
  DAT_0057a1e8 = param_1;
  return uVar1;
}


// 0052d110

void FUN_0052d110(int param_1,undefined4 param_2)

{
  code *pcVar1;
  int iVar2;
  
  iVar2 = FUN_0052d690(param_1);
  if (iVar2 != 0) {
    if (((((*(uint *)(param_1 + -0xc) & 0xffff) != 4) && (*(int *)(param_1 + -0xc) != 1)) &&
        ((*(uint *)(param_1 + -0xc) & 0xffff) != 2)) &&
       ((*(int *)(param_1 + -0xc) != 3 &&
        (iVar2 = FUN_0052fad0(2,"dbgheap.c",0x4d3,0,"_BLOCK_TYPE_IS_VALID(pHead->nBlockUse)"),
        iVar2 == 1)))) {
      pcVar1 = (code *)swi(3);
      (*pcVar1)();
      return;
    }
    *(undefined4 *)(param_1 + -0xc) = param_2;
  }
  return;
}


// 0052d1a0

undefined * FUN_0052d1a0(undefined *param_1)

{
  undefined *puVar1;
  
  puVar1 = PTR_FUN_0057a610;
  PTR_FUN_0057a610 = param_1;
  return puVar1;
}


// 0052d1c0

undefined4 FUN_0052d1c0(char *param_1,char param_2,int param_3)

{
  code *pcVar1;
  char *pcVar2;
  undefined4 uVar3;
  int iVar4;
  undefined4 local_8;
  
  local_8 = 1;
  pcVar2 = param_1;
  while( true ) {
    do {
      param_1 = pcVar2;
      iVar4 = param_3 + -1;
      if (param_3 == 0) {
        return local_8;
      }
      pcVar2 = param_1 + 1;
      param_3 = iVar4;
    } while (*param_1 == param_2);
    iVar4 = FUN_0052fad0(0,0,0,0,"memory check error at 0x%08X = 0x%02X, should be 0x%02X.\n",
                         param_1,*param_1,param_2);
    if (iVar4 == 1) break;
    local_8 = 0;
  }
  pcVar1 = (code *)swi(3);
  uVar3 = (*pcVar1)();
  return uVar3;
}


// 0052d250

undefined4 FUN_0052d250(void)

{
  code *pcVar1;
  bool bVar2;
  int iVar3;
  undefined4 uVar4;
  char *local_18;
  undefined4 *local_c;
  undefined4 local_8;
  
  local_8 = 1;
  if ((DAT_0057a1e0 & 1) == 0) {
    local_8 = 1;
  }
  else {
    iVar3 = FUN_00532800();
    if ((iVar3 == -1) || (iVar3 == -2)) {
      for (local_c = DAT_00b94044; local_c != (undefined4 *)0x0; local_c = (undefined4 *)*local_c) {
        bVar2 = true;
        if (((((local_c[5] & 0xffff) == 4) || (local_c[5] == 1)) || ((local_c[5] & 0xffff) == 2)) ||
           (local_c[5] == 3)) {
          local_18 = (&PTR_DAT_0057a1f0)[local_c[5] & 0xffff];
        }
        else {
          local_18 = "DAMAGED";
        }
        iVar3 = FUN_0052d1c0(local_c + 7,DAT_0057a1ec,4);
        if (iVar3 == 0) {
          iVar3 = FUN_0052fad0(0,0,0,0,"DAMAGE: before %hs block (#%d) at 0x%08X.\n",local_18,
                               local_c[6],local_c + 8);
          if (iVar3 == 1) {
            pcVar1 = (code *)swi(3);
            uVar4 = (*pcVar1)();
            return uVar4;
          }
          bVar2 = false;
        }
        iVar3 = FUN_0052d1c0((int)local_c + local_c[4] + 0x20,DAT_0057a1ec,4);
        if (iVar3 == 0) {
          iVar3 = FUN_0052fad0(0,0,0,0,"DAMAGE: after %hs block (#%d) at 0x%08X.\n",local_18,
                               local_c[6],local_c + 8);
          if (iVar3 == 1) {
            pcVar1 = (code *)swi(3);
            uVar4 = (*pcVar1)();
            return uVar4;
          }
          bVar2 = false;
        }
        if ((local_c[5] == 0) &&
           (iVar3 = FUN_0052d1c0(local_c + 8,DAT_0057a1ed,local_c[4]), iVar3 == 0)) {
          iVar3 = FUN_0052fad0(0,0,0,0,"DAMAGE: on top of Free block at 0x%08X.\n",local_c + 8);
          if (iVar3 == 1) {
            pcVar1 = (code *)swi(3);
            uVar4 = (*pcVar1)();
            return uVar4;
          }
          bVar2 = false;
        }
        if (!bVar2) {
          if ((local_c[2] != 0) &&
             (iVar3 = FUN_0052fad0(0,0,0,0,"%hs allocated at file %hs(%d).\n",local_18,local_c[2],
                                   local_c[3]), iVar3 == 1)) {
            pcVar1 = (code *)swi(3);
            uVar4 = (*pcVar1)();
            return uVar4;
          }
          iVar3 = FUN_0052fad0(0,0,0,0,"%hs located at 0x%08X is %u bytes long.\n",local_18,
                               local_c + 8,local_c[4]);
          if (iVar3 == 1) {
            pcVar1 = (code *)swi(3);
            uVar4 = (*pcVar1)();
            return uVar4;
          }
          local_8 = 0;
        }
      }
    }
    else {
      switch(iVar3) {
      case -6:
        iVar3 = FUN_0052fad0(0,0,0,0,&DAT_00546c68,"_heapchk fails with _HEAPBADPTR.\n");
        if (iVar3 == 1) {
          pcVar1 = (code *)swi(3);
          uVar4 = (*pcVar1)();
          return uVar4;
        }
        break;
      case -5:
        iVar3 = FUN_0052fad0(0,0,0,0,&DAT_00546c68,"_heapchk fails with _HEAPBADEND.\n");
        if (iVar3 == 1) {
          pcVar1 = (code *)swi(3);
          uVar4 = (*pcVar1)();
          return uVar4;
        }
        break;
      case -4:
        iVar3 = FUN_0052fad0(0,0,0,0,&DAT_00546c68,"_heapchk fails with _HEAPBADNODE.\n");
        if (iVar3 == 1) {
          pcVar1 = (code *)swi(3);
          uVar4 = (*pcVar1)();
          return uVar4;
        }
        break;
      case -3:
        iVar3 = FUN_0052fad0(0,0,0,0,&DAT_00546c68,"_heapchk fails with _HEAPBADBEGIN.\n");
        if (iVar3 == 1) {
          pcVar1 = (code *)swi(3);
          uVar4 = (*pcVar1)();
          return uVar4;
        }
        break;
      default:
        iVar3 = FUN_0052fad0(0,0,0,0,&DAT_00546c68,"_heapchk fails with unknown return value!\n");
        if (iVar3 == 1) {
          pcVar1 = (code *)swi(3);
          uVar4 = (*pcVar1)();
          return uVar4;
        }
      }
      local_8 = 0;
    }
  }
  return local_8;
}


// 0052d5b0

int FUN_0052d5b0(int param_1)

{
  int iVar1;
  
  iVar1 = DAT_0057a1e0;
  if (param_1 != -1) {
    DAT_0057a1e0 = param_1;
  }
  return iVar1;
}


// 0052d5e0

void FUN_0052d5e0(code *param_1,undefined4 param_2)

{
  undefined4 *local_8;
  
  if ((DAT_0057a1e0 & 1) != 0) {
    for (local_8 = DAT_00b94044; local_8 != (undefined4 *)0x0; local_8 = (undefined4 *)*local_8) {
      if ((local_8[5] & 0xffff) == 4) {
        (*param_1)(local_8 + 8,param_2);
      }
    }
  }
  return;
}


// 0052d640

/* Library Function - Multiple Matches With Different Base Names
    int __cdecl ATL::AtlIsValidAddress(void const *,unsigned int,int)
    __CrtIsValidPointer
   
   Library: Visual Studio 2003 Debug */

undefined4 FID_conflict_AtlIsValidAddress(void *param_1,UINT_PTR param_2,int param_3)

{
  BOOL BVar1;
  
  if (((param_1 != (void *)0x0) && (BVar1 = IsBadReadPtr(param_1,param_2), BVar1 == 0)) &&
     ((param_3 == 0 || (BVar1 = IsBadWritePtr(param_1,param_2), BVar1 == 0)))) {
    return 1;
  }
  return 0;
}


// 0052d690

BOOL __thiscall FUN_0052d690(undefined4 param_1,int param_2)

{
  BOOL BVar1;
  int iVar2;
  
  if (param_2 == 0) {
    BVar1 = 0;
  }
  else {
    iVar2 = FID_conflict_AtlIsValidAddress(param_2 + -0x20,0x20,1,param_1);
    if (iVar2 == 0) {
      BVar1 = 0;
    }
    else {
      iVar2 = FUN_005329f0(param_2 + -0x20);
      if (iVar2 == 0) {
        if ((DAT_00b9405c & 0x8000) == 0) {
          BVar1 = HeapValidate(DAT_01286a48,0,(LPCVOID)(param_2 + -0x20));
        }
        else {
          BVar1 = 1;
        }
      }
      else {
        BVar1 = FUN_00532a50(iVar2,param_2 + -0x20);
      }
    }
  }
  return BVar1;
}


// 0052d720

undefined4 __thiscall
FUN_0052d720(undefined4 param_1,int param_2,int param_3,undefined4 *param_4,undefined4 *param_5,
            undefined4 *param_6)

{
  int iVar1;
  int iVar2;
  
  iVar1 = FUN_0052d690(param_2,param_1);
  if (((iVar1 != 0) &&
      ((((iVar1 = param_2 + -0x20, (*(uint *)(param_2 + -0xc) & 0xffff) == 4 ||
         (*(int *)(param_2 + -0xc) == 1)) || ((*(uint *)(param_2 + -0xc) & 0xffff) == 2)) ||
       (*(int *)(param_2 + -0xc) == 3)))) &&
     (((iVar2 = FID_conflict_AtlIsValidAddress(param_2,param_3,1), iVar2 != 0 &&
       (*(int *)(iVar1 + 0x10) == param_3)) && (*(int *)(iVar1 + 0x18) <= DAT_0057a1e4)))) {
    if (param_4 != (undefined4 *)0x0) {
      *param_4 = *(undefined4 *)(iVar1 + 0x18);
    }
    if (param_5 != (undefined4 *)0x0) {
      *param_5 = *(undefined4 *)(iVar1 + 8);
    }
    if (param_6 != (undefined4 *)0x0) {
      *param_6 = *(undefined4 *)(iVar1 + 0xc);
    }
    return 1;
  }
  return 0;
}


// 0052d7f0

undefined4 FUN_0052d7f0(undefined4 param_1)

{
  undefined4 uVar1;
  
  uVar1 = DAT_01286bd4;
  DAT_01286bd4 = param_1;
  return uVar1;
}


// 0052d810

void FUN_0052d810(undefined4 *param_1)

{
  code *pcVar1;
  int iVar2;
  undefined4 *local_c;
  int local_8;
  
  if (param_1 == (undefined4 *)0x0) {
    iVar2 = FUN_0052fad0(0,0,0,0,&DAT_00546c68,"_CrtMemCheckPoint: NULL state pointer.\n");
    if (iVar2 == 1) {
      pcVar1 = (code *)swi(3);
      (*pcVar1)();
      return;
    }
  }
  else {
    *param_1 = DAT_00b94044;
    for (local_8 = 0; local_8 < 5; local_8 = local_8 + 1) {
      param_1[local_8 + 6] = 0;
      param_1[local_8 + 1] = 0;
    }
    for (local_c = DAT_00b94044; local_c != (undefined4 *)0x0; local_c = (undefined4 *)*local_c) {
      if ((local_c[5] & 0xffff) < 5) {
        param_1[(local_c[5] & 0xffff) + 1] = param_1[(local_c[5] & 0xffff) + 1] + 1;
        param_1[(local_c[5] & 0xffff) + 6] = param_1[(local_c[5] & 0xffff) + 6] + local_c[4];
      }
      else {
        iVar2 = FUN_0052fad0(0,0,0,0,"Bad memory block found at 0x%08X.\n",local_c);
        if (iVar2 == 1) {
          pcVar1 = (code *)swi(3);
          (*pcVar1)();
          return;
        }
      }
    }
    param_1[0xb] = DAT_00b9404c;
    param_1[0xc] = DAT_00b94040;
  }
  return;
}


// 0052d970

undefined4 FUN_0052d970(undefined4 *param_1,int param_2,int param_3)

{
  code *pcVar1;
  int iVar2;
  undefined4 uVar3;
  undefined4 local_c;
  int local_8;
  
  local_c = 0;
  if (((param_1 == (undefined4 *)0x0) || (param_2 == 0)) || (param_3 == 0)) {
    iVar2 = FUN_0052fad0(0,0,0,0,&DAT_00546c68,"_CrtMemDifference: NULL state pointer.\n");
    if (iVar2 == 1) {
      pcVar1 = (code *)swi(3);
      uVar3 = (*pcVar1)();
      return uVar3;
    }
    local_c = 0;
  }
  else {
    for (local_8 = 0; local_8 < 5; local_8 = local_8 + 1) {
      param_1[local_8 + 6] =
           *(int *)(param_3 + 0x18 + local_8 * 4) - *(int *)(param_2 + 0x18 + local_8 * 4);
      param_1[local_8 + 1] =
           *(int *)(param_3 + 4 + local_8 * 4) - *(int *)(param_2 + 4 + local_8 * 4);
      if (((param_1[local_8 + 6] != 0) || (param_1[local_8 + 1] != 0)) &&
         ((local_8 != 0 && ((local_8 != 2 || ((DAT_0057a1e0 & 0x10) != 0)))))) {
        local_c = 1;
      }
    }
    param_1[0xb] = *(int *)(param_3 + 0x2c) - *(int *)(param_2 + 0x2c);
    param_1[0xc] = *(int *)(param_3 + 0x30) - *(int *)(param_2 + 0x30);
    *param_1 = 0;
  }
  return local_c;
}


// 0052daa0

void FUN_0052daa0(undefined4 *param_1)

{
  code *pcVar1;
  int iVar2;
  undefined4 *local_c;
  undefined4 *local_8;
  
  local_c = (undefined4 *)0x0;
  iVar2 = FUN_0052fad0(0,0,0,0,&DAT_00546c68,"Dumping objects ->\n");
  if (iVar2 == 1) {
    pcVar1 = (code *)swi(3);
    (*pcVar1)();
    return;
  }
  if (param_1 != (undefined4 *)0x0) {
    local_c = (undefined4 *)*param_1;
  }
  local_8 = DAT_00b94044;
  do {
    if ((local_8 == (undefined4 *)0x0) || (local_8 == local_c)) {
      iVar2 = FUN_0052fad0(0,0,0,0,&DAT_00546c68,"Object dump complete.\n");
      if (iVar2 == 1) {
        pcVar1 = (code *)swi(3);
        (*pcVar1)();
        return;
      }
      return;
    }
    if ((((local_8[5] & 0xffff) != 3) && ((local_8[5] & 0xffff) != 0)) &&
       (((local_8[5] & 0xffff) != 2 || ((DAT_0057a1e0 & 0x10) != 0)))) {
      if (local_8[2] != 0) {
        iVar2 = FID_conflict_AtlIsValidAddress(local_8[2],1,0);
        if (iVar2 == 0) {
          iVar2 = FUN_0052fad0(0,0,0,0,"#File Error#(%d) : ",local_8[3]);
          if (iVar2 == 1) {
            pcVar1 = (code *)swi(3);
            (*pcVar1)();
            return;
          }
        }
        else {
          iVar2 = FUN_0052fad0(0,0,0,0,"%hs(%d) : ",local_8[2],local_8[3]);
          if (iVar2 == 1) {
            pcVar1 = (code *)swi(3);
            (*pcVar1)();
            return;
          }
        }
      }
      iVar2 = FUN_0052fad0(0,0,0,0,"{%ld} ",local_8[6]);
      if (iVar2 == 1) {
        pcVar1 = (code *)swi(3);
        (*pcVar1)();
        return;
      }
      if ((local_8[5] & 0xffff) == 4) {
        iVar2 = FUN_0052fad0(0,0,0,0,"client block at 0x%08X, subtype %x, %u bytes long.\n",
                             local_8 + 8,(int)local_8[5] >> 0x10 & 0xffff,local_8[4]);
        if (iVar2 == 1) {
          pcVar1 = (code *)swi(3);
          (*pcVar1)();
          return;
        }
        if (DAT_01286bd4 == (code *)0x0) {
          FUN_0052dd50(local_8);
        }
        else {
          (*DAT_01286bd4)(local_8 + 8,local_8[4]);
        }
      }
      else if (local_8[5] == 1) {
        iVar2 = FUN_0052fad0(0,0,0,0,"normal block at 0x%08X, %u bytes long.\n",local_8 + 8,
                             local_8[4]);
        if (iVar2 == 1) {
          pcVar1 = (code *)swi(3);
          (*pcVar1)();
          return;
        }
        FUN_0052dd50(local_8);
      }
      else if ((local_8[5] & 0xffff) == 2) {
        iVar2 = FUN_0052fad0(0,0,0,0,"crt block at 0x%08X, subtype %x, %u bytes long.\n",local_8 + 8
                             ,(int)local_8[5] >> 0x10 & 0xffff,local_8[4]);
        if (iVar2 == 1) {
          pcVar1 = (code *)swi(3);
          (*pcVar1)();
          return;
        }
        FUN_0052dd50(local_8);
      }
    }
    local_8 = (undefined4 *)*local_8;
  } while( true );
}


// 0052dd50

void FUN_0052dd50(int param_1)

{
  byte bVar1;
  code *pcVar2;
  byte bVar3;
  int iVar4;
  uint local_5c;
  int local_58;
  int local_50;
  byte local_4c [20];
  undefined1 local_38 [52];
  
  local_50 = 0;
  while( true ) {
    if (*(int *)(param_1 + 0x10) < 0x10) {
      local_58 = *(int *)(param_1 + 0x10);
    }
    else {
      local_58 = 0x10;
    }
    if (local_58 <= local_50) break;
    bVar1 = *(byte *)(param_1 + local_50 + 0x20);
    if (DAT_0057a5fc < 2) {
      local_5c = *(ushort *)(PTR_DAT_0057a3f0 + (uint)bVar1 * 2) & 0x157;
    }
    else {
      local_5c = FUN_00532300(bVar1,0x157);
    }
    bVar3 = bVar1;
    if (local_5c == 0) {
      bVar3 = 0x20;
    }
    local_4c[local_50] = bVar3;
    FUN_0052a910(local_38 + local_50 * 3,"%.2X ",bVar1);
    local_50 = local_50 + 1;
  }
  local_4c[local_50] = 0;
  iVar4 = FUN_0052fad0(0,0,0,0," Data: <%s> %s\n",local_4c,local_38);
  if (iVar4 == 1) {
    pcVar2 = (code *)swi(3);
    (*pcVar2)();
    return;
  }
  return;
}


// 0052de70

undefined4 FUN_0052de70(void)

{
  code *pcVar1;
  int iVar2;
  undefined4 uVar3;
  undefined1 local_38 [8];
  int local_30;
  int local_2c;
  int local_24;
  
  FUN_0052d810(local_38);
  if (((local_24 == 0) && (local_30 == 0)) && (((DAT_0057a1e0 & 0x10) == 0 || (local_2c == 0)))) {
    uVar3 = 0;
  }
  else {
    iVar2 = FUN_0052fad0(0,0,0,0,&DAT_00546c68,"Detected memory leaks!\n");
    if (iVar2 == 1) {
      pcVar1 = (code *)swi(3);
      uVar3 = (*pcVar1)();
      return uVar3;
    }
    FUN_0052daa0(0);
    uVar3 = 1;
  }
  return uVar3;
}


// 0052def0

void FUN_0052def0(int param_1)

{
  code *pcVar1;
  int iVar2;
  int local_8;
  
  if (param_1 != 0) {
    for (local_8 = 0; local_8 < 5; local_8 = local_8 + 1) {
      iVar2 = FUN_0052fad0(0,0,0,0,"%ld bytes in %ld %hs Blocks.\n",
                           *(undefined4 *)(param_1 + 0x18 + local_8 * 4),
                           *(undefined4 *)(param_1 + 4 + local_8 * 4),(&PTR_DAT_0057a1f0)[local_8]);
      if (iVar2 == 1) {
        pcVar1 = (code *)swi(3);
        (*pcVar1)();
        return;
      }
    }
    iVar2 = FUN_0052fad0(0,0,0,0,"Largest number used: %ld bytes.\n",*(undefined4 *)(param_1 + 0x2c)
                        );
    if (iVar2 == 1) {
      pcVar1 = (code *)swi(3);
      (*pcVar1)();
      return;
    }
    iVar2 = FUN_0052fad0(0,0,0,0,"Total allocations: %ld bytes.\n",*(undefined4 *)(param_1 + 0x30));
    if (iVar2 == 1) {
      pcVar1 = (code *)swi(3);
      (*pcVar1)();
      return;
    }
  }
  return;
}


// 0052dfc0

void FUN_0052dfc0(void)

{
  float10 in_ST0;
  
  FUN_005348b8((double)in_ST0);
  FUN_0052dfdd();
  return;
}


// 0052dfd4

uint FUN_0052dfd4(uint param_1,uint param_2)

{
  uint uVar1;
  undefined1 in_ZF;
  short in_FPUControlWord;
  
  __fload_withFB();
  if ((bool)in_ZF) {
    if (((param_2 & 0xfffff) != 0) || (param_1 != 0)) {
      uVar1 = FUN_0053485c();
      goto LAB_0052e05b;
    }
    param_1 = param_2 & 0x80000000;
    param_2 = 0;
joined_r0x0052e04c:
    if (param_1 == 0) {
LAB_0052dffe:
      if (DAT_00b94034 != 0) {
        return param_2;
      }
      uVar1 = __math_exit();
      return uVar1;
    }
  }
  else {
    if (in_FPUControlWord != 0x27f) {
      param_2 = FUN_00534845();
    }
    if ((param_2 & 0x80000000) == 0) goto LAB_0052dffe;
    if (((param_2 & 0x7ff00000) == 0) && ((param_2 & 0xfffff) == 0)) goto joined_r0x0052e04c;
  }
  uVar1 = 1;
LAB_0052e05b:
  if (DAT_00b94034 != 0) {
    return uVar1;
  }
  uVar1 = __startOneArgErrorHandling();
  return uVar1;
}


// 0052dfdd

uint FUN_0052dfdd(uint param_1,uint param_2)

{
  uint uVar1;
  bool in_ZF;
  short in_FPUControlWord;
  
  if (in_ZF) {
    if (((param_2 & 0xfffff) != 0) || (param_1 != 0)) {
      uVar1 = FUN_0053485c();
      goto LAB_0052e05b;
    }
    param_1 = param_2 & 0x80000000;
    param_2 = 0;
joined_r0x0052e04c:
    if (param_1 == 0) {
LAB_0052dffe:
      if (DAT_00b94034 != 0) {
        return param_2;
      }
      uVar1 = __math_exit();
      return uVar1;
    }
  }
  else {
    if (in_FPUControlWord != 0x27f) {
      param_2 = FUN_00534845();
    }
    if ((param_2 & 0x80000000) == 0) goto LAB_0052dffe;
    if (((param_2 & 0x7ff00000) == 0) && ((param_2 & 0xfffff) == 0)) goto joined_r0x0052e04c;
  }
  uVar1 = 1;
LAB_0052e05b:
  if (DAT_00b94034 != 0) {
    return uVar1;
  }
  uVar1 = __startOneArgErrorHandling();
  return uVar1;
}


// 0052e080

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

float10 FUN_0052e080(undefined4 param_1,undefined4 param_2)

{
  undefined4 uVar1;
  int iVar2;
  float10 fVar3;
  
  uVar1 = FUN_00535900();
  if ((param_2._2_2_ & 0x7ff0) == 0x7ff0) {
    iVar2 = FUN_00535700();
    if (iVar2 == 1) {
      FUN_00535900();
      fVar3 = (float10)(double)CONCAT26(param_2._2_2_,CONCAT24((undefined2)param_2,param_1));
    }
    else if (iVar2 == 2) {
      FUN_00535900();
      fVar3 = -(float10)(double)CONCAT26(param_2._2_2_,CONCAT24((undefined2)param_2,param_1));
    }
    else if (iVar2 == 3) {
      fVar3 = (float10)FUN_005349c0(0x15,param_1,param_2,uVar1);
    }
    else {
      fVar3 = (float10)FUN_00534a90(8,0x15,param_1,param_2,
                                    (double)CONCAT26(param_2._2_2_,
                                                     CONCAT24((undefined2)param_2,param_1)) +
                                    _DAT_005460b8,uVar1);
    }
  }
  else {
    FUN_00535900();
    fVar3 = (float10)ABS((double)CONCAT44(param_2,param_1));
  }
  return fVar3;
}


// 0052e180

void FUN_0052e180(undefined4 param_1)

{
  DAT_0057a218 = param_1;
  return;
}


// 0052e190

uint FUN_0052e190(void)

{
  DAT_0057a218 = DAT_0057a218 * 0x343fd + 0x269ec3;
  return DAT_0057a218 >> 0x10 & 0x7fff;
}


// 0052e1c0

undefined4 FUN_0052e1c0(int param_1,int param_2)

{
  code *pcVar1;
  int iVar2;
  undefined4 uVar3;
  
  if ((param_1 == 0) && (iVar2 = FUN_0052fad0(2,"fscanf.c",0x36,0,"stream != NULL"), iVar2 == 1)) {
    pcVar1 = (code *)swi(3);
    uVar3 = (*pcVar1)();
    return uVar3;
  }
  if ((param_2 == 0) && (iVar2 = FUN_0052fad0(2,"fscanf.c",0x37,0,"format != NULL"), iVar2 == 1)) {
    pcVar1 = (code *)swi(3);
    uVar3 = (*pcVar1)();
    return uVar3;
  }
  uVar3 = FUN_005359c0(param_1,param_2,&stack0x0000000c);
  return uVar3;
}


// 0052e250

undefined4 FUN_0052e250(char *param_1,int param_2)

{
  code *pcVar1;
  int iVar2;
  undefined4 uVar3;
  char *local_24;
  size_t local_20;
  char *local_1c;
  undefined4 local_18;
  
  if ((param_1 == (char *)0x0) &&
     (iVar2 = FUN_0052fad0(2,"sscanf.c",0x42,0,"string != NULL"), iVar2 == 1)) {
    pcVar1 = (code *)swi(3);
    uVar3 = (*pcVar1)();
    return uVar3;
  }
  if ((param_2 == 0) && (iVar2 = FUN_0052fad0(2,"sscanf.c",0x43,0,"format != NULL"), iVar2 == 1)) {
    pcVar1 = (code *)swi(3);
    uVar3 = (*pcVar1)();
    return uVar3;
  }
  local_18 = 0x49;
  local_1c = param_1;
  local_24 = param_1;
  local_20 = _strlen(param_1);
  uVar3 = FUN_005359c0(&local_24,param_2,&stack0x0000000c);
  return uVar3;
}


// 0052e310

undefined4 FUN_0052e310(int param_1,int param_2)

{
  code *pcVar1;
  int iVar2;
  undefined4 uVar3;
  undefined4 uVar4;
  
  if ((param_1 == 0) && (iVar2 = FUN_0052fad0(2,"fprintf.c",0x38,0,"str != NULL"), iVar2 == 1)) {
    pcVar1 = (code *)swi(3);
    uVar3 = (*pcVar1)();
    return uVar3;
  }
  if ((param_2 == 0) && (iVar2 = FUN_0052fad0(2,"fprintf.c",0x39,0,"format != NULL"), iVar2 == 1)) {
    pcVar1 = (code *)swi(3);
    uVar3 = (*pcVar1)();
    return uVar3;
  }
  uVar3 = FUN_00536ec0(param_1);
  uVar4 = FUN_0052eb20(param_1,param_2,&stack0x0000000c);
  FUN_00537020(uVar3,param_1);
  return uVar4;
}


// 0052e3c0

void FUN_0052e3c0(void)

{
  if (PTR_FUN_0057a1d0 != (undefined *)0x0) {
    (*(code *)PTR_FUN_0057a1d0)();
  }
  __initterm(&DAT_00549208,&DAT_00549418);
  __initterm(&DAT_00549000,&DAT_00549104);
  return;
}


// 0052e400

void FUN_0052e400(undefined4 param_1)

{
  FUN_0052e480(param_1,0,0);
  return;
}


// 0052e420

/* Library Function - Single Match
    __exit
   
   Library: Visual Studio 2003 Debug */

void __cdecl __exit(int _Code)

{
  FUN_0052e480(_Code,1,0);
  return;
}


// 0052e440

void FUN_0052e440(void)

{
  FUN_0052e480(0,0,1);
  return;
}


// 0052e460

void FUN_0052e460(void)

{
  FUN_0052e480(0,1,1);
  return;
}


// 0052e480

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __thiscall FUN_0052e480(int *param_1,UINT param_2,int param_3,int param_4)

{
  HANDLE hProcess;
  uint uVar1;
  UINT uExitCode;
  int *piVar2;
  
  if (DAT_00b94098 == 1) {
    uExitCode = param_2;
    hProcess = GetCurrentProcess();
    TerminateProcess(hProcess,uExitCode);
  }
  _DAT_00b94094 = 1;
  DAT_00b94090 = (undefined1)param_4;
  if (param_3 == 0) {
    piVar2 = DAT_01286bcc;
    if (DAT_01286bd0 != (int *)0x0) {
      while (piVar2 = piVar2 + -1, param_1 = piVar2, DAT_01286bd0 <= piVar2) {
        if (*piVar2 != 0) {
          (*(code *)*piVar2)();
        }
      }
    }
    __initterm(&DAT_0054951c,&DAT_00549724,param_1);
  }
  __initterm(&DAT_00549828,&DAT_0054992c,param_1);
  if ((DAT_00b9409c == 0) && (uVar1 = FUN_0052d5b0(0xffffffff), (uVar1 & 0x20) != 0)) {
    DAT_00b9409c = 1;
    FUN_0052de70();
  }
  if (param_4 == 0) {
    DAT_00b94098 = 1;
                    /* WARNING: Subroutine does not return */
    ExitProcess(param_2);
  }
  return;
}


// 0052e560

/* Library Function - Single Match
    __initterm
   
   Library: Visual Studio 2003 Debug */

void __initterm(int *param_1,int *param_2)

{
  for (; param_1 < param_2; param_1 = param_1 + 1) {
    if (*param_1 != 0) {
      (*(code *)*param_1)();
    }
  }
  return;
}


// 0052e590

void FUN_0052e590(void)

{
  float10 in_ST0;
  
  FUN_005348b8((double)in_ST0);
  FUN_0052e5ad();
  return;
}


// 0052e5a4

uint FUN_0052e5a4(int param_1,uint param_2)

{
  uint uVar1;
  undefined1 in_ZF;
  unkbyte10 extraout_ST0;
  
  uVar1 = __fload_withFB();
  if (!(bool)in_ZF) {
    if ((param_2 & 0x7ff00000) == 0) {
      if (((param_2 & 0xfffff) == 0) && (param_1 == 0)) {
        uVar1 = 2;
        goto LAB_0052e63d;
      }
    }
    else if ((param_2 & 0x80000000) != 0) goto LAB_0052e60c;
    log2(extraout_ST0);
LAB_0052e5da:
    if (DAT_00b94034 != 0) {
      return param_2;
    }
    uVar1 = __math_exit();
    return uVar1;
  }
  if (((uVar1 & 0xfffff) != 0) || (param_1 != 0)) {
    uVar1 = FUN_0053485c();
    goto LAB_0052e63d;
  }
  param_2 = 0;
  if ((uVar1 & 0x80000000) == 0) goto LAB_0052e5da;
LAB_0052e60c:
  uVar1 = 1;
LAB_0052e63d:
  if (DAT_00b94034 != 0) {
    return uVar1;
  }
  uVar1 = __startOneArgErrorHandling();
  return uVar1;
}


// 0052e5ad

uint FUN_0052e5ad(int param_1,uint param_2)

{
  uint in_EAX;
  uint uVar1;
  bool in_ZF;
  unkbyte10 in_ST0;
  
  if (!in_ZF) {
    if ((param_2 & 0x7ff00000) == 0) {
      if (((param_2 & 0xfffff) == 0) && (param_1 == 0)) {
        uVar1 = 2;
        goto LAB_0052e63d;
      }
    }
    else if ((param_2 & 0x80000000) != 0) goto LAB_0052e60c;
    log2(in_ST0);
LAB_0052e5da:
    if (DAT_00b94034 != 0) {
      return param_2;
    }
    uVar1 = __math_exit();
    return uVar1;
  }
  if (((in_EAX & 0xfffff) != 0) || (param_1 != 0)) {
    uVar1 = FUN_0053485c();
    goto LAB_0052e63d;
  }
  param_2 = 0;
  if ((in_EAX & 0x80000000) == 0) goto LAB_0052e5da;
LAB_0052e60c:
  uVar1 = 1;
LAB_0052e63d:
  if (DAT_00b94034 != 0) {
    return uVar1;
  }
  uVar1 = __startOneArgErrorHandling();
  return uVar1;
}


// 0052e660

/* Library Function - Single Match
    _strstr
   
   Libraries: Visual Studio 1998 Debug, Visual Studio 1998 Release */

char * __cdecl _strstr(char *_Str,char *_SubStr)

{
  char *pcVar1;
  char *pcVar2;
  char cVar3;
  char *pcVar4;
  char *pcVar5;
  
  if (*_SubStr == '\0') {
    return _Str;
  }
  if (_SubStr[1] == '\0') {
    pcVar4 = (char *)FUN_00537306();
    return pcVar4;
  }
  do {
    cVar3 = *_Str;
    do {
      while (_Str = _Str + 1, cVar3 != *_SubStr) {
        if (cVar3 == '\0') {
          return (char *)0x0;
        }
        cVar3 = *_Str;
      }
      cVar3 = *_Str;
      pcVar5 = _Str + 1;
      pcVar4 = _SubStr;
    } while (cVar3 != _SubStr[1]);
    do {
      if (pcVar4[2] == '\0') {
LAB_0052e6d3:
        return _Str + -1;
      }
      if (*pcVar5 != pcVar4[2]) break;
      pcVar1 = pcVar4 + 3;
      if (*pcVar1 == '\0') goto LAB_0052e6d3;
      pcVar2 = pcVar5 + 1;
      pcVar4 = pcVar4 + 2;
      pcVar5 = pcVar5 + 2;
    } while (*pcVar1 == *pcVar2);
  } while( true );
}


// 0052e6e0

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void entry(void)

{
  DWORD DVar1;
  int iVar2;
  undefined4 uVar3;
  HMODULE pHVar4;
  undefined4 uVar5;
  uint local_70;
  _STARTUPINFOA local_60;
  undefined1 *local_1c;
  _EXCEPTION_POINTERS *local_18;
  void *pvStack_14;
  undefined1 *puStack_10;
  undefined *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &DAT_00547340;
  puStack_10 = &LAB_00538004;
  pvStack_14 = ExceptionList;
  local_1c = &stack0xffffff84;
  ExceptionList = &pvStack_14;
  DVar1 = GetVersion();
  _DAT_00b94068 = DVar1 >> 8 & 0xff;
  DAT_00b94064 = DVar1 & 0xff;
  _DAT_00b94060 = DAT_00b94064 * 0x100 + _DAT_00b94068;
  DAT_00b9405c = DVar1 >> 0x10;
  iVar2 = FUN_00532870(0);
  if (iVar2 == 0) {
    FUN_0052e870(0x1c);
  }
  local_8 = 0;
  FUN_00531b40();
  DAT_01286bac = GetCommandLineA();
  DAT_00b940a0 = FUN_00537cf0();
  FUN_005377e0();
  FUN_00537690();
  FUN_0052e3c0();
  local_60.dwFlags = 0;
  GetStartupInfoA(&local_60);
  uVar3 = FUN_005375d0();
  if ((local_60.dwFlags & 1) == 0) {
    local_70 = 10;
  }
  else {
    local_70 = local_60._48_4_ & 0xffff;
  }
  uVar5 = 0;
  pHVar4 = GetModuleHandleA((LPCSTR)0x0);
  uVar3 = thunk_FUN_00521f10(pHVar4,uVar5,uVar3,local_70);
  FUN_0052e400(uVar3);
  __XcptFilter(local_18->ExceptionRecord->ExceptionCode,local_18);
  return;
}


// 0052e840

/* Library Function - Single Match
    __amsg_exit
   
   Library: Visual Studio 2003 Debug */

void __cdecl __amsg_exit(int param_1)

{
  if (DAT_00b940a8 == 1) {
    __FF_MSGBANNER();
  }
  FUN_00538130(param_1);
  (*(code *)PTR___exit_0057a230)(0xff);
  return;
}


// 0052e870

void FUN_0052e870(undefined4 param_1)

{
  if (DAT_00b940a8 == 1) {
    __FF_MSGBANNER();
  }
  FUN_00538130(param_1);
                    /* WARNING: Subroutine does not return */
  ExitProcess(0xff);
}


// 0052e8a0

uint FUN_0052e8a0(uint param_1,int *param_2)

{
  code *pcVar1;
  int *piVar2;
  int iVar3;
  uint uVar4;
  undefined *local_18;
  int local_10;
  int local_8;
  
  if ((param_2 == (int *)0x0) &&
     (iVar3 = FUN_0052fad0(2,"_flsbuf.c",0x69,0,"str != NULL"), iVar3 == 1)) {
    pcVar1 = (code *)swi(3);
    uVar4 = (*pcVar1)();
    return uVar4;
  }
  piVar2 = param_2;
  uVar4 = param_2[4];
  if (((param_2[3] & 0x82U) == 0) || ((param_2[3] & 0x40U) != 0)) {
    param_2[3] = param_2[3] | 0x20;
    param_1 = 0xffffffff;
  }
  else {
    if ((param_2[3] & 1U) != 0) {
      param_2[1] = 0;
      if ((param_2[3] & 0x10U) == 0) {
        param_2[3] = param_2[3] | 0x20;
        return 0xffffffff;
      }
      *param_2 = param_2[2];
      param_2[3] = param_2[3] & 0xfffffffe;
    }
    param_2[3] = param_2[3] | 2;
    param_2[3] = param_2[3] & 0xffffffef;
    param_2[1] = 0;
    local_10 = 0;
    if (((param_2[3] & 0x10cU) == 0) &&
       (((param_2 != (int *)&DAT_0057a938 && (param_2 != (int *)&DAT_0057a958)) ||
        (iVar3 = __isatty(uVar4), iVar3 == 0)))) {
      FUN_00538340(piVar2);
    }
    if ((piVar2[3] & 0x108U) == 0) {
      local_8 = 1;
      local_10 = FUN_00531800(uVar4,&param_1,1);
    }
    else {
      if ((*piVar2 - piVar2[2] < 0) &&
         (iVar3 = FUN_0052fad0(2,"_flsbuf.c",0xa0,0,
                               "(\"inconsistent IOB fields\", stream->_ptr - stream->_base >= 0)"),
         iVar3 == 1)) {
        pcVar1 = (code *)swi(3);
        uVar4 = (*pcVar1)();
        return uVar4;
      }
      local_8 = *piVar2 - piVar2[2];
      *piVar2 = piVar2[2] + 1;
      piVar2[1] = piVar2[6] + -1;
      if (local_8 < 1) {
        if (uVar4 == 0xffffffff) {
          local_18 = &DAT_0057a3e8;
        }
        else {
          local_18 = (undefined *)((&DAT_01286a60)[(int)uVar4 >> 5] + (uVar4 & 0x1f) * 8);
        }
        if ((local_18[4] & 0x20) != 0) {
          FUN_00531eb0(uVar4,0,2);
        }
      }
      else {
        local_10 = FUN_00531800(uVar4,piVar2[2],local_8);
      }
      *(undefined1 *)piVar2[2] = (undefined1)param_1;
    }
    if (local_10 == local_8) {
      param_1 = param_1 & 0xff;
    }
    else {
      piVar2[3] = piVar2[3] | 0x20;
      param_1 = 0xffffffff;
    }
  }
  return param_1;
}


// 0052eb20

/* WARNING: Type propagation algorithm not settling */

int FUN_0052eb20(undefined4 param_1,byte *param_2,undefined4 *param_3)

{
  byte bVar1;
  code *pcVar2;
  ulonglong uVar3;
  byte *pbVar4;
  short sVar5;
  byte *pbVar6;
  uint uVar7;
  size_t sVar8;
  int iVar9;
  undefined2 extraout_var;
  short *psVar10;
  bool bVar11;
  ulonglong uVar12;
  longlong lVar13;
  int iStack_2a8;
  uint local_294;
  undefined1 auStack_28c [4];
  size_t sStack_288;
  short *psStack_284;
  int iStack_280;
  undefined8 uStack_27c;
  int iStack_274;
  undefined8 uStack_270;
  undefined4 uStack_268;
  undefined4 uStack_264;
  int *piStack_260;
  int iStack_25c;
  short *psStack_258;
  short *psStack_254;
  short *psStack_250;
  undefined2 uStack_24c;
  int iStack_248;
  undefined1 uStack_244;
  char cStack_243;
  int iStack_240;
  int iStack_23c;
  int iStack_238;
  int iStack_234;
  int local_230;
  short asStack_22c [255];
  undefined2 uStack_2d;
  undefined3 uStack_2b;
  size_t local_28;
  short *psStack_24;
  int iStack_20;
  int local_1c;
  undefined2 uStack_18;
  int iStack_14;
  uint local_10;
  undefined4 uStack_c;
  uint uStack_8;
  
  local_28 = 0;
  local_230 = 0;
  local_1c = 0;
  pbVar6 = param_2;
  do {
    param_2 = pbVar6;
    bVar1 = *param_2;
    stack0xffffffd4 = CONCAT31(uStack_2b,bVar1);
    pbVar6 = param_2 + 1;
    if ((bVar1 == 0) || (local_230 < 0)) {
      return local_230;
    }
    if (((char)bVar1 < ' ') || ('x' < (char)bVar1)) {
      local_294 = 0;
    }
    else {
      local_294 = (int)"(\"inconsistent IOB fields\", stream->_ptr - stream->_base >= 0)"
                       [(char)bVar1 + 0x2c] & 0xf;
    }
    local_10 = local_294;
    local_1c = (int)(char)(&DAT_00547398)[local_294 * 8 + local_1c] >> 4;
    switch(local_1c) {
    case 0:
LAB_0052ebe0:
      iStack_20 = 0;
      pbVar4 = pbVar6;
      if ((*(ushort *)(PTR_DAT_0057a3f0 + (uint)bVar1 * 2) & 0x8000) != 0) {
        FUN_0052f850((int)(char)bVar1,param_1,&local_230);
        stack0xffffffd4 = CONCAT31(uStack_2b,*pbVar6);
        pbVar4 = param_2 + 2;
        if (*pbVar6 == 0) {
          iVar9 = FUN_0052fad0(2,"output.c",0x186,0,"ch != _T(\'\\0\')");
          if (iVar9 == 1) {
            pcVar2 = (code *)swi(3);
            iVar9 = (*pcVar2)();
            return iVar9;
          }
        }
      }
      param_2 = pbVar4;
      FUN_0052f850((int)uStack_2d._1_1_,param_1,&local_230);
      pbVar6 = param_2;
      break;
    case 1:
      uStack_c = 0;
      iStack_240 = 0;
      iStack_248 = 0;
      iStack_14 = 0;
      uStack_8 = 0;
      iStack_238 = -1;
      iStack_20 = 0;
      break;
    case 2:
      switch(bVar1) {
      case 0x20:
        uStack_8 = uStack_8 | 2;
        break;
      case 0x23:
        uStack_8 = uStack_8 | 0x80;
        break;
      case 0x2b:
        uStack_8 = uStack_8 | 1;
        break;
      case 0x2d:
        uStack_8 = uStack_8 | 4;
        break;
      case 0x30:
        uStack_8 = uStack_8 | 8;
      }
      break;
    case 3:
      if (bVar1 == 0x2a) {
        iStack_248 = FUN_0052f960(&param_3);
        if (iStack_248 < 0) {
          uStack_8 = uStack_8 | 4;
          iStack_248 = -iStack_248;
        }
      }
      else {
        iStack_248 = iStack_248 * 10 + -0x30 + (int)(char)bVar1;
      }
      break;
    case 4:
      iStack_238 = 0;
      break;
    case 5:
      if (bVar1 == 0x2a) {
        iStack_238 = FUN_0052f960(&param_3);
        if (iStack_238 < 0) {
          iStack_238 = -1;
        }
      }
      else {
        iStack_238 = iStack_238 * 10 + -0x30 + (int)(char)bVar1;
      }
      break;
    case 6:
      switch(bVar1) {
      case 0x49:
        if ((*pbVar6 != 0x36) || (param_2[2] != 0x34)) {
          local_1c = 0;
          goto LAB_0052ebe0;
        }
        uStack_8 = uStack_8 | 0x8000;
        pbVar6 = param_2 + 3;
        break;
      case 0x68:
        uStack_8 = uStack_8 | 0x20;
        break;
      case 0x6c:
        uStack_8 = uStack_8 | 0x10;
        break;
      case 0x77:
        uStack_8 = uStack_8 | 0x800;
      }
      param_2 = pbVar6;
      pbVar6 = param_2;
      break;
    case 7:
      psVar10 = psStack_24;
      switch(bVar1) {
      case 0x43:
        if ((uStack_8 & 0x830) == 0) {
          uStack_8 = uStack_8 | 0x800;
        }
      case 99:
        if ((uStack_8 & 0x810) == 0) {
          uStack_24c = FUN_0052f960(&param_3);
          asStack_22c[0]._0_1_ = (undefined1)uStack_24c;
          local_28 = 1;
        }
        else {
          uStack_18 = FUN_0052f9a0(&param_3);
          local_28 = FUN_00538590(asStack_22c,CONCAT22(extraout_var,uStack_18));
          if ((int)local_28 < 0) {
            iStack_240 = 1;
          }
        }
        psVar10 = asStack_22c;
        break;
      case 0x45:
      case 0x47:
        uStack_c = 1;
        stack0xffffffd4 = CONCAT31(uStack_2b,bVar1 + 0x20);
      case 0x65:
      case 0x66:
      case 0x67:
        uStack_8 = uStack_8 | 0x40;
        psStack_24 = asStack_22c;
        if (iStack_238 < 0) {
          iStack_238 = 6;
        }
        else if ((iStack_238 == 0) && (uStack_2d._1_1_ == 'g')) {
          iStack_238 = 1;
        }
        uStack_268 = *param_3;
        uStack_264 = param_3[1];
        param_3 = param_3 + 2;
        (*(code *)PTR___fptrap_0057a268)
                  (&uStack_268,psStack_24,(int)uStack_2d._1_1_,iStack_238,uStack_c);
        if (((uStack_8 & 0x80) != 0) && (iStack_238 == 0)) {
          (*(code *)PTR___fptrap_0057a274)(psStack_24);
        }
        if ((uStack_2d._1_1_ == 'g') && ((uStack_8 & 0x80) == 0)) {
          (*(code *)PTR___fptrap_0057a26c)(psStack_24);
        }
        if ((char)*psStack_24 == '-') {
          uStack_8 = uStack_8 | 0x100;
          psStack_24 = (short *)((int)psStack_24 + 1);
        }
        local_28 = _strlen((char *)psStack_24);
        psVar10 = psStack_24;
        break;
      case 0x53:
        if ((uStack_8 & 0x830) == 0) {
          uStack_8 = uStack_8 | 0x800;
        }
      case 0x73:
        if (iStack_238 == -1) {
          iStack_2a8 = 0x7fffffff;
        }
        else {
          iStack_2a8 = iStack_238;
        }
        iStack_25c = iStack_2a8;
        psStack_24 = (short *)FUN_0052f960(&param_3);
        if ((uStack_8 & 0x810) == 0) {
          if (psStack_24 == (short *)0x0) {
            psStack_24 = (short *)PTR_DAT_0057a238;
          }
          for (psStack_254 = psStack_24; (iStack_25c != 0 && ((char)*psStack_254 != '\0'));
              psStack_254 = (short *)((int)psStack_254 + 1)) {
            iStack_25c = iStack_25c + -1;
          }
          local_28 = (int)psStack_254 - (int)psStack_24;
          iStack_25c = iStack_25c + -1;
          psVar10 = psStack_24;
        }
        else {
          if (psStack_24 == (short *)0x0) {
            psStack_24 = (short *)PTR_DAT_0057a23c;
          }
          iStack_20 = 1;
          for (psStack_258 = psStack_24; (iStack_25c != 0 && (*psStack_258 != 0));
              psStack_258 = psStack_258 + 1) {
            iStack_25c = iStack_25c + -1;
          }
          local_28 = (int)psStack_258 - (int)psStack_24 >> 1;
          iStack_25c = iStack_25c + -1;
          psVar10 = psStack_24;
        }
        break;
      case 0x5a:
        psStack_250 = (short *)FUN_0052f960(&param_3);
        if ((psStack_250 == (short *)0x0) || (*(int *)(psStack_250 + 2) == 0)) {
          psStack_24 = (short *)PTR_DAT_0057a238;
          local_28 = _strlen(PTR_DAT_0057a238);
          psVar10 = psStack_24;
        }
        else if ((uStack_8 & 0x800) == 0) {
          iStack_20 = 0;
          local_28 = (size_t)*psStack_250;
          psVar10 = *(short **)(psStack_250 + 2);
        }
        else {
          local_28 = (uint)(int)*psStack_250 >> 1;
          iStack_20 = 1;
          psVar10 = *(short **)(psStack_250 + 2);
        }
        break;
      case 100:
      case 0x69:
        uStack_8 = uStack_8 | 0x40;
        iStack_23c = 10;
        goto LAB_0052f2e5;
      case 0x6e:
        piStack_260 = (int *)FUN_0052f960(&param_3);
        if ((uStack_8 & 0x20) == 0) {
          *piStack_260 = local_230;
        }
        else {
          *(undefined2 *)piStack_260 = (undefined2)local_230;
        }
        iStack_240 = 1;
        psVar10 = psStack_24;
        break;
      case 0x6f:
        iStack_23c = 8;
        if ((uStack_8 & 0x80) != 0) {
          uStack_8 = uStack_8 | 0x200;
        }
        goto LAB_0052f2e5;
      case 0x70:
        iStack_238 = 8;
      case 0x58:
        iStack_234 = 7;
        goto LAB_0052f28f;
      case 0x75:
        iStack_23c = 10;
        goto LAB_0052f2e5;
      case 0x78:
        iStack_234 = 0x27;
LAB_0052f28f:
        iStack_23c = 0x10;
        if ((uStack_8 & 0x80) != 0) {
          uStack_244 = 0x30;
          cStack_243 = (char)iStack_234 + 'Q';
          iStack_14 = 2;
        }
LAB_0052f2e5:
        if ((uStack_8 & 0x8000) == 0) {
          if ((uStack_8 & 0x20) == 0) {
            if ((uStack_8 & 0x40) == 0) {
              uVar7 = FUN_0052f960(&param_3);
              uVar12 = (ulonglong)uVar7;
            }
            else {
              iVar9 = FUN_0052f960(&param_3);
              uVar12 = (ulonglong)iVar9;
            }
          }
          else if ((uStack_8 & 0x40) == 0) {
            uVar7 = FUN_0052f960(&param_3);
            uVar12 = (ulonglong)(uVar7 & 0xffff);
          }
          else {
            sVar5 = FUN_0052f960(&param_3);
            uVar12 = (ulonglong)(int)sVar5;
          }
        }
        else {
          uVar12 = FUN_0052f980(&param_3);
        }
        uStack_27c._4_4_ = (int)(uVar12 >> 0x20);
        uStack_27c._0_4_ = (int)uVar12;
        uVar3 = uVar12;
        if ((((uStack_8 & 0x40) != 0) && ((longlong)uVar12 < 0x100000000)) && ((longlong)uVar12 < 0)
           ) {
          uStack_8 = uStack_8 | 0x100;
          uVar3 = CONCAT44(-(uStack_27c._4_4_ + (uint)((int)uStack_27c != 0)),-(int)uStack_27c);
        }
        uStack_270._4_4_ = (int)(uVar3 >> 0x20);
        uStack_270._0_4_ = (int)uVar3;
        if ((uStack_8 & 0x8000) == 0) {
          uStack_270._4_4_ = 0;
        }
        lVar13 = CONCAT44(uStack_270._4_4_,(int)uStack_270);
        if (iStack_238 < 0) {
          iStack_238 = 1;
        }
        else {
          uStack_8 = uStack_8 & 0xfffffff7;
        }
        if ((int)uStack_270 == 0 && uStack_270._4_4_ == 0) {
          iStack_14 = 0;
        }
        psStack_24 = &uStack_2d;
        uStack_27c = uVar12;
        while ((iVar9 = iStack_238 + -1, 0 < iStack_238 || (lVar13 != 0))) {
          iStack_238 = iVar9;
          uStack_270 = lVar13;
          iStack_274 = __aullrem(lVar13,iStack_23c,iStack_23c >> 0x1f);
          iStack_274 = iStack_274 + 0x30;
          lVar13 = __aulldiv(uStack_270,iStack_23c,iStack_23c >> 0x1f);
          if (0x39 < iStack_274) {
            iStack_274 = iStack_274 + iStack_234;
          }
          *(char *)psStack_24 = (char)iStack_274;
          psStack_24 = (short *)((int)psStack_24 + -1);
        }
        local_28 = (int)&uStack_2d - (int)psStack_24;
        psVar10 = (short *)((int)psStack_24 + 1);
        uStack_270 = 0;
        iStack_238 = iVar9;
        if (((uStack_8 & 0x200) != 0) && ((*(char *)psVar10 != '0' || (local_28 == 0)))) {
          *(char *)psStack_24 = '0';
          local_28 = local_28 + 1;
          psVar10 = psStack_24;
        }
      }
      psStack_24 = psVar10;
      if (iStack_240 == 0) {
        if ((uStack_8 & 0x40) != 0) {
          if ((uStack_8 & 0x100) == 0) {
            if ((uStack_8 & 1) == 0) {
              if ((uStack_8 & 2) != 0) {
                uStack_244 = 0x20;
                iStack_14 = 1;
              }
            }
            else {
              uStack_244 = 0x2b;
              iStack_14 = 1;
            }
          }
          else {
            uStack_244 = 0x2d;
            iStack_14 = 1;
          }
        }
        iStack_280 = (iStack_248 - local_28) - iStack_14;
        if ((uStack_8 & 0xc) == 0) {
          FUN_0052f8d0(0x20,iStack_280,param_1,&local_230);
        }
        FUN_0052f910(&uStack_244,iStack_14,param_1,&local_230);
        if (((uStack_8 & 8) != 0) && ((uStack_8 & 4) == 0)) {
          FUN_0052f8d0(0x30,iStack_280,param_1,&local_230);
        }
        if ((iStack_20 == 0) || ((int)local_28 < 1)) {
          FUN_0052f910(psStack_24,local_28,param_1,&local_230);
        }
        else {
          psStack_284 = psStack_24;
          sStack_288 = local_28;
          while (sVar8 = sStack_288 - 1, bVar11 = sStack_288 != 0, sStack_288 = sVar8, bVar11) {
            sVar5 = *psStack_284;
            psStack_284 = psStack_284 + 1;
            iVar9 = FUN_00538590(auStack_28c,CONCAT22((short)(sVar8 >> 0x10),sVar5));
            if (iVar9 < 1) break;
            FUN_0052f910(auStack_28c,iVar9,param_1,&local_230);
          }
        }
        if ((uStack_8 & 4) != 0) {
          FUN_0052f8d0(0x20,iStack_280,param_1,&local_230);
        }
      }
    }
  } while( true );
}


// 0052f850

void __thiscall FUN_0052f850(undefined4 param_1,uint param_2,int *param_3,int *param_4)

{
  param_3[1] = param_3[1] + -1;
  if (param_3[1] < 0) {
    param_2 = FUN_0052e8a0(param_2,param_3,param_1);
  }
  else {
    *(undefined1 *)*param_3 = (undefined1)param_2;
    param_2 = param_2 & 0xff;
    *param_3 = *param_3 + 1;
  }
  if (param_2 == 0xffffffff) {
    *param_4 = -1;
  }
  else {
    *param_4 = *param_4 + 1;
  }
  return;
}


// 0052f8d0

void FUN_0052f8d0(undefined4 param_1,int param_2,undefined4 param_3,int *param_4)

{
  do {
    if (param_2 < 1) {
      return;
    }
    FUN_0052f850(param_1,param_3,param_4);
    param_2 = param_2 + -1;
  } while (*param_4 != -1);
  return;
}


// 0052f910

void FUN_0052f910(char *param_1,int param_2,undefined4 param_3,int *param_4)

{
  char cVar1;
  
  do {
    if (param_2 < 1) {
      return;
    }
    cVar1 = *param_1;
    param_1 = param_1 + 1;
    FUN_0052f850((int)cVar1,param_3,param_4);
    param_2 = param_2 + -1;
  } while (*param_4 != -1);
  return;
}


// 0052f960

undefined4 FUN_0052f960(int *param_1)

{
  *param_1 = *param_1 + 4;
  return *(undefined4 *)(*param_1 + -4);
}


// 0052f980

undefined8 FUN_0052f980(int *param_1)

{
  *param_1 = *param_1 + 8;
  return *(undefined8 *)(*param_1 + -8);
}


// 0052f9a0

undefined2 FUN_0052f9a0(int *param_1)

{
  *param_1 = *param_1 + 4;
  return *(undefined2 *)(*param_1 + -4);
}


// 0052f9c0

void FUN_0052f9c0(void)

{
  DebugBreak();
  return;
}


// 0052f9d0

undefined4 FUN_0052f9d0(int param_1,uint param_2)

{
  undefined4 uVar1;
  
  if ((param_1 < 0) || (2 < param_1)) {
    uVar1 = 0xffffffff;
  }
  else if (param_2 == 0xffffffff) {
    uVar1 = *(undefined4 *)(&DAT_0057a244 + param_1 * 4);
  }
  else if ((param_2 & 0xfffffff8) == 0) {
    uVar1 = *(undefined4 *)(&DAT_0057a244 + param_1 * 4);
    *(uint *)(&DAT_0057a244 + param_1 * 4) = param_2;
  }
  else {
    uVar1 = 0xffffffff;
  }
  return uVar1;
}


// 0052fa30

/* Library Function - Single Match
    __CrtSetReportFile
   
   Library: Visual Studio 2003 Debug */

undefined4 __CrtSetReportFile(int param_1,int param_2)

{
  undefined4 uVar1;
  HANDLE pvVar2;
  
  if ((param_1 < 0) || (2 < param_1)) {
    uVar1 = 0xfffffffe;
  }
  else if (param_2 == -6) {
    uVar1 = *(undefined4 *)(&DAT_0057a250 + param_1 * 4);
  }
  else {
    uVar1 = *(undefined4 *)(&DAT_0057a250 + param_1 * 4);
    if (param_2 == -4) {
      pvVar2 = GetStdHandle(0xfffffff5);
      *(HANDLE *)(&DAT_0057a250 + param_1 * 4) = pvVar2;
    }
    else if (param_2 == -5) {
      pvVar2 = GetStdHandle(0xfffffff4);
      *(HANDLE *)(&DAT_0057a250 + param_1 * 4) = pvVar2;
    }
    else {
      *(int *)(&DAT_0057a250 + param_1 * 4) = param_2;
    }
  }
  return uVar1;
}


// 0052fab0

undefined4 FUN_0052fab0(undefined4 param_1)

{
  undefined4 uVar1;
  
  uVar1 = DAT_01286ba0;
  DAT_01286ba0 = param_1;
  return uVar1;
}


// 0052fad0

undefined4 FUN_0052fad0(int param_1,int param_2,int param_3,undefined4 param_4,int param_5)

{
  LONG LVar1;
  size_t nNumberOfBytesToWrite;
  int iVar2;
  undefined4 *puVar3;
  char local_3028 [20];
  DWORD local_3014;
  HMODULE local_3010;
  undefined1 local_300c;
  undefined4 local_300b;
  CHAR local_200c;
  undefined4 local_200b;
  undefined4 local_100c;
  undefined1 *local_1008;
  undefined1 local_1004;
  undefined4 local_1003;
  undefined4 uStackY_24;
  CHAR *pCStackY_20;
  DWORD *lpNumberOfBytesWritten;
  LPOVERLAPPED lpOverlapped;
  
  FUN_00538c10();
  local_300c = 0;
  puVar3 = &local_300b;
  for (iVar2 = 0x3ff; iVar2 != 0; iVar2 = iVar2 + -1) {
    *puVar3 = 0;
    puVar3 = puVar3 + 1;
  }
  *(undefined2 *)puVar3 = 0;
  *(undefined1 *)((int)puVar3 + 2) = 0;
  local_200c = '\0';
  puVar3 = &local_200b;
  for (iVar2 = 0x3ff; iVar2 != 0; iVar2 = iVar2 + -1) {
    *puVar3 = 0;
    puVar3 = puVar3 + 1;
  }
  *(undefined2 *)puVar3 = 0;
  *(undefined1 *)((int)puVar3 + 2) = 0;
  local_1004 = 0;
  puVar3 = &local_1003;
  for (iVar2 = 0x3ff; iVar2 != 0; iVar2 = iVar2 + -1) {
    *puVar3 = 0;
    puVar3 = puVar3 + 1;
  }
  *(undefined2 *)puVar3 = 0;
  *(undefined1 *)((int)puVar3 + 2) = 0;
  local_1008 = &stack0x00000018;
  if ((param_1 < 0) || (2 < param_1)) {
    local_100c = 0xffffffff;
  }
  else if ((param_1 == 2) && (LVar1 = InterlockedIncrement((LONG *)&DAT_0057a240), 0 < LVar1)) {
    if ((DAT_00b940ac == (FARPROC)0x0) &&
       ((local_3010 = LoadLibraryA("user32.dll"), local_3010 == (HMODULE)0x0 ||
        (DAT_00b940ac = GetProcAddress(local_3010,"wsprintfA"), DAT_00b940ac == (FARPROC)0x0)))) {
      local_100c = 0xffffffff;
    }
    else {
      (*DAT_00b940ac)();
      OutputDebugStringA(&local_200c);
      InterlockedDecrement((LONG *)&DAT_0057a240);
      FUN_0052f9c0();
      local_100c = 0xffffffff;
    }
  }
  else {
    if ((param_5 != 0) && (iVar2 = FUN_00538b10(), iVar2 < 0)) {
      FUN_0052b100();
    }
    if (param_1 == 2) {
      FUN_0052b100();
    }
    FUN_0052b110();
    if (param_1 == 2) {
      if ((uRam0057a24c & 1) != 0) {
        FUN_0052b110();
      }
      FUN_0052b110();
    }
    if (param_2 == 0) {
      FUN_0052b100();
    }
    else {
      pCStackY_20 = &local_200c;
      uStackY_24 = 0x52fce5;
      iVar2 = FUN_00538a10();
      if (iVar2 < 0) {
        FUN_0052b100();
      }
    }
    if ((DAT_01286ba0 == (code *)0x0) || (iVar2 = (*DAT_01286ba0)(), iVar2 == 0)) {
      if (((*(uint *)(&DAT_0057a244 + param_1 * 4) & 1) != 0) &&
         (*(int *)(&DAT_0057a250 + param_1 * 4) != -1)) {
        lpOverlapped = (LPOVERLAPPED)0x0;
        lpNumberOfBytesWritten = &local_3014;
        nNumberOfBytesToWrite = _strlen(&local_200c);
        pCStackY_20 = (CHAR *)0x52fdab;
        WriteFile(*(HANDLE *)(&DAT_0057a250 + param_1 * 4),&local_200c,nNumberOfBytesToWrite,
                  lpNumberOfBytesWritten,lpOverlapped);
      }
      if ((*(uint *)(&DAT_0057a244 + param_1 * 4) & 2) != 0) {
        OutputDebugStringA(&local_200c);
      }
      if ((*(uint *)(&DAT_0057a244 + param_1 * 4) & 4) == 0) {
        if (param_1 == 2) {
          InterlockedDecrement((LONG *)&DAT_0057a240);
        }
        local_100c = 0;
      }
      else {
        if (param_3 != 0) {
          __itoa(param_3,local_3028,10);
        }
        pCStackY_20 = (CHAR *)0x52fe26;
        local_100c = FUN_0052fe60();
        if (param_1 == 2) {
          InterlockedDecrement((LONG *)&DAT_0057a240);
        }
      }
    }
    else if (param_1 == 2) {
      InterlockedDecrement((LONG *)&DAT_0057a240);
    }
  }
  return local_100c;
}


// 0052fe60

bool FUN_0052fe60(int param_1,undefined *param_2,undefined *param_3,char *param_4,char *param_5)

{
  int iVar1;
  DWORD DVar2;
  size_t sVar3;
  char *local_113c;
  char *local_1138;
  char *local_1134;
  undefined *local_1130;
  char *local_112c;
  undefined *local_1128;
  undefined *local_1124;
  char *local_1118;
  char *local_1114;
  undefined1 local_1110 [4096];
  int local_110;
  CHAR local_10c [200];
  undefined4 uStackY_44;
  undefined1 *puStackY_40;
  undefined4 uStackY_3c;
  char *pcStackY_38;
  undefined *puStackY_34;
  char *pcStackY_30;
  char *pcStackY_2c;
  char *pcStackY_28;
  char *pcStackY_24;
  undefined *puStackY_20;
  char *pcStackY_1c;
  undefined *puStackY_18;
  char *pcStackY_14;
  char *_Str;
  
  FUN_00538c10();
  if (param_5 == (char *)0x0) {
    pcStackY_14 = "dbgrpt.c";
    puStackY_18 = (undefined *)0x2;
    pcStackY_1c = (char *)0x52fe8b;
    iVar1 = FUN_0052fad0();
    if (iVar1 == 1) {
      FUN_0052f9c0();
    }
  }
  pcStackY_14 = (char *)0x52feb2;
  DVar2 = GetModuleFileNameA((HMODULE)0x0,local_10c,0x104);
  if (DVar2 == 0) {
    FUN_0052b100();
  }
  _Str = local_10c;
  sVar3 = _strlen(_Str);
  if (0x40 < sVar3) {
    _strlen(_Str);
    pcStackY_14 = (char *)0x52ff0a;
    _strncpy((char *)0x3,"...",3);
  }
  local_1114 = param_4;
  if ((param_4 != (char *)0x0) && (sVar3 = _strlen(param_4), 0x40 < sVar3)) {
    sVar3 = _strlen(param_4);
    local_1114 = param_4 + (sVar3 - 0x40);
    pcStackY_14 = (char *)0x52ff65;
    _strncpy(local_1114,"...",3);
  }
  if (param_1 == 2) {
    local_1118 = 
    "\n\nFor information on how your program can cause an assertion\nfailure, see the Visual C++ documentation on asserts."
    ;
  }
  else {
    local_1118 = "";
  }
  if (*param_5 == '\0') {
    local_1124 = &DAT_005475a8;
  }
  else {
    local_1124 = &DAT_00547594;
  }
  if (param_3 == (undefined *)0x0) {
    local_1128 = &DAT_005475a8;
    local_112c = "";
    puStackY_18 = local_1128;
  }
  else {
    local_112c = "\nLine: ";
    puStackY_18 = param_3;
  }
  if (param_2 == (undefined *)0x0) {
    local_1130 = &DAT_005475a8;
    local_1134 = "";
    puStackY_20 = local_1130;
  }
  else {
    local_1134 = "\nFile: ";
    puStackY_20 = param_2;
  }
  if (local_1114 == (char *)0x0) {
    local_1138 = "";
    local_113c = "";
    pcStackY_28 = local_1138;
  }
  else {
    local_113c = "\nModule: ";
    pcStackY_28 = local_1114;
  }
  pcStackY_14 = local_1124;
  pcStackY_1c = local_112c;
  pcStackY_24 = local_1134;
  pcStackY_2c = local_113c;
  pcStackY_30 = local_1118;
  puStackY_34 = (&PTR_s_Warning_0057a25c)[param_1];
  pcStackY_38 = 
  "Debug %s!\n\nProgram: %s%s%s%s%s%s%s%s%s%s%s\n\n(Press Retry to debug the application)";
  uStackY_3c = 0x1000;
  puStackY_40 = local_1110;
  uStackY_44 = 0x530102;
  iVar1 = FUN_00538a10();
  if (iVar1 < 0) {
    FUN_0052b100();
  }
  pcStackY_14 = (char *)0x530133;
  local_110 = FUN_00539070();
  if (local_110 == 3) {
    FUN_00538e50();
                    /* WARNING: Subroutine does not return */
    __exit(3);
  }
  return local_110 == 4;
}


// 00530170

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 FUN_00530170(uint param_1)

{
  int iVar1;
  int iVar2;
  HANDLE hObject;
  BOOL BVar3;
  undefined4 uVar4;
  ulong local_8;
  
  if ((DAT_01286b9c <= param_1) ||
     ((*(byte *)((&DAT_01286a60)[(int)param_1 >> 5] + 4 + (param_1 & 0x1f) * 8) & 1) == 0)) {
    _DAT_00b94050 = 9;
    DAT_00b94054 = 0;
    return 0xffffffff;
  }
  iVar1 = FUN_005393e0(param_1);
  if (iVar1 != -1) {
    if ((param_1 == 1) || (param_1 == 2)) {
      iVar1 = FUN_005393e0(1);
      iVar2 = FUN_005393e0(2);
      if (iVar1 == iVar2) goto LAB_00530209;
    }
    hObject = (HANDLE)FUN_005393e0(param_1);
    BVar3 = CloseHandle(hObject);
    if (BVar3 == 0) {
      local_8 = GetLastError();
      goto LAB_0053021b;
    }
  }
LAB_00530209:
  local_8 = 0;
LAB_0053021b:
  FUN_00539310(param_1);
  *(undefined1 *)((&DAT_01286a60)[(int)param_1 >> 5] + 4 + (param_1 & 0x1f) * 8) = 0;
  if (local_8 == 0) {
    uVar4 = 0;
  }
  else {
    __dosmaperr(local_8);
    uVar4 = 0xffffffff;
  }
  return uVar4;
}


// 00530260

void FUN_00530260(undefined4 *param_1)

{
  code *pcVar1;
  int iVar2;
  
  if ((param_1 == (undefined4 *)0x0) &&
     (iVar2 = FUN_0052fad0(2,"_freebuf.c",0x30,0,"stream != NULL"), iVar2 == 1)) {
    pcVar1 = (code *)swi(3);
    (*pcVar1)();
    return;
  }
  if (((param_1[3] & 0x83) != 0) && ((param_1[3] & 8) != 0)) {
    FUN_0052cb90(param_1[2],2);
    param_1[3] = param_1[3] & 0xfffffbf7;
    *param_1 = 0;
    param_1[2] = 0;
    param_1[1] = 0;
  }
  return;
}


// 00530300

int FUN_00530300(int param_1)

{
  int iVar1;
  
  if (param_1 == 0) {
    iVar1 = FUN_00530430(0);
  }
  else {
    iVar1 = FUN_00530360(param_1);
    if (iVar1 == 0) {
      if ((*(uint *)(param_1 + 0xc) & 0x4000) == 0) {
        iVar1 = 0;
      }
      else {
        iVar1 = FUN_00539530(*(undefined4 *)(param_1 + 0x10));
        iVar1 = -(uint)(iVar1 != 0);
      }
    }
    else {
      iVar1 = -1;
    }
  }
  return iVar1;
}


// 00530360

undefined4 FUN_00530360(int *param_1)

{
  int iVar1;
  int iVar2;
  undefined4 local_8;
  
  local_8 = 0;
  if ((((param_1[3] & 3U) == 2) && ((param_1[3] & 0x108U) != 0)) &&
     (iVar2 = *param_1 - param_1[2], 0 < iVar2)) {
    iVar1 = FUN_00531800(param_1[4],param_1[2],iVar2);
    if (iVar1 == iVar2) {
      if ((param_1[3] & 0x80U) != 0) {
        param_1[3] = param_1[3] & 0xfffffffd;
      }
    }
    else {
      param_1[3] = param_1[3] | 0x20;
      local_8 = 0xffffffff;
    }
  }
  *param_1 = param_1[2];
  param_1[1] = 0;
  return local_8;
}


// 00530420

void FUN_00530420(void)

{
  FUN_00530430(1);
  return;
}


// 00530430

int FUN_00530430(int param_1)

{
  int iVar1;
  int local_10;
  int local_c;
  int local_8;
  
  local_8 = 0;
  local_c = 0;
  for (local_10 = 0; local_10 < DAT_01286a20; local_10 = local_10 + 1) {
    if ((*(int *)(DAT_012856c8 + local_10 * 4) != 0) &&
       ((*(uint *)(*(int *)(DAT_012856c8 + local_10 * 4) + 0xc) & 0x83) != 0)) {
      if (param_1 == 1) {
        iVar1 = FUN_00530300(*(undefined4 *)(DAT_012856c8 + local_10 * 4));
        if (iVar1 != -1) {
          local_8 = local_8 + 1;
        }
      }
      else if (((param_1 == 0) &&
               ((*(uint *)(*(int *)(DAT_012856c8 + local_10 * 4) + 0xc) & 2) != 0)) &&
              (iVar1 = FUN_00530300(*(undefined4 *)(DAT_012856c8 + local_10 * 4)), iVar1 == -1)) {
        local_c = -1;
      }
    }
  }
  if (param_1 == 1) {
    local_c = local_8;
  }
  return local_c;
}


// 00530510

uint FUN_00530510(int *param_1)

{
  code *pcVar1;
  int iVar2;
  uint uVar3;
  undefined *local_c;
  
  if ((param_1 == (int *)0x0) &&
     (iVar2 = FUN_0052fad0(2,"_filbuf.c",0x69,0,"str != NULL"), iVar2 == 1)) {
    pcVar1 = (code *)swi(3);
    uVar3 = (*pcVar1)();
    return uVar3;
  }
  if (((param_1[3] & 0x83U) == 0) || ((param_1[3] & 0x40U) != 0)) {
    uVar3 = 0xffffffff;
  }
  else if ((param_1[3] & 2U) == 0) {
    param_1[3] = param_1[3] | 1;
    if ((param_1[3] & 0x10cU) == 0) {
      FUN_00538340(param_1);
    }
    else {
      *param_1 = param_1[2];
    }
    iVar2 = FUN_005306f0(param_1[4],param_1[2],param_1[6]);
    param_1[1] = iVar2;
    if ((param_1[1] == 0) || (param_1[1] == -1)) {
      param_1[3] = param_1[3] | (-(uint)(param_1[1] != 0) & 0x10) + 0x10;
      param_1[1] = 0;
      uVar3 = 0xffffffff;
    }
    else {
      if ((param_1[3] & 0x82U) == 0) {
        if (param_1[4] == -1) {
          local_c = &DAT_0057a3e8;
        }
        else {
          local_c = (undefined *)((&DAT_01286a60)[param_1[4] >> 5] + (param_1[4] & 0x1fU) * 8);
        }
        if (((int)(char)local_c[4] & 0x82U) == 0x82) {
          param_1[3] = param_1[3] | 0x2000;
        }
      }
      if (((param_1[6] == 0x200) && ((param_1[3] & 8U) != 0)) && ((param_1[3] & 0x400U) == 0)) {
        param_1[6] = 0x1000;
      }
      param_1[1] = param_1[1] + -1;
      uVar3 = (uint)*(byte *)*param_1;
      *param_1 = *param_1 + 1;
    }
  }
  else {
    param_1[3] = param_1[3] | 0x20;
    uVar3 = 0xffffffff;
  }
  return uVar3;
}


// 005306f0

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

int FUN_005306f0(uint param_1,char *param_2,DWORD param_3)

{
  BOOL BVar1;
  int iVar2;
  char local_20 [4];
  int local_1c;
  char *local_18;
  DWORD local_14;
  char *local_10;
  DWORD local_c;
  char *local_8;
  
  if ((param_1 < DAT_01286b9c) &&
     (iVar2 = (int)param_1 >> 5,
     (*(byte *)((&DAT_01286a60)[iVar2] + 4 + (param_1 & 0x1f) * 8) & 1) != 0)) {
    local_1c = 0;
    local_18 = param_2;
    if ((param_3 == 0) || ((*(byte *)((&DAT_01286a60)[iVar2] + 4 + (param_1 & 0x1f) * 8) & 2) != 0))
    {
      local_1c = 0;
    }
    else {
      if (((*(byte *)((&DAT_01286a60)[iVar2] + 4 + (param_1 & 0x1f) * 8) & 0x48) != 0) &&
         (*(char *)((&DAT_01286a60)[iVar2] + 5 + (param_1 & 0x1f) * 8) != '\n')) {
        *param_2 = *(char *)((&DAT_01286a60)[iVar2] + 5 + (param_1 & 0x1f) * 8);
        local_18 = param_2 + 1;
        local_1c = 1;
        param_3 = param_3 - 1;
        *(undefined1 *)((&DAT_01286a60)[iVar2] + 5 + (param_1 & 0x1f) * 8) = 10;
      }
      BVar1 = ReadFile(*(HANDLE *)((&DAT_01286a60)[iVar2] + (param_1 & 0x1f) * 8),local_18,param_3,
                       &local_14,(LPOVERLAPPED)0x0);
      if (BVar1 == 0) {
        local_c = GetLastError();
        if (local_c == 5) {
          _DAT_00b94050 = 9;
          local_1c = -1;
          DAT_00b94054 = 5;
        }
        else if (local_c == 0x6d) {
          local_1c = 0;
        }
        else {
          __dosmaperr(local_c);
          local_1c = -1;
        }
      }
      else {
        local_1c = local_1c + local_14;
        if (((int)*(char *)((&DAT_01286a60)[iVar2] + 4 + (param_1 & 0x1f) * 8) & 0x80U) != 0) {
          if ((local_14 == 0) || (*param_2 != '\n')) {
            *(byte *)((&DAT_01286a60)[iVar2] + 4 + (param_1 & 0x1f) * 8) =
                 *(byte *)((&DAT_01286a60)[iVar2] + 4 + (param_1 & 0x1f) * 8) & 0xfb;
          }
          else {
            *(byte *)((&DAT_01286a60)[iVar2] + 4 + (param_1 & 0x1f) * 8) =
                 *(byte *)((&DAT_01286a60)[iVar2] + 4 + (param_1 & 0x1f) * 8) | 4;
          }
          local_10 = param_2;
          local_8 = param_2;
          while (local_8 < param_2 + local_1c) {
            if (*local_8 == '\x1a') {
              if ((*(byte *)((&DAT_01286a60)[iVar2] + 4 + (param_1 & 0x1f) * 8) & 0x40) == 0) {
                *(byte *)((&DAT_01286a60)[iVar2] + 4 + (param_1 & 0x1f) * 8) =
                     *(byte *)((&DAT_01286a60)[iVar2] + 4 + (param_1 & 0x1f) * 8) | 2;
              }
              break;
            }
            if (*local_8 == '\r') {
              if (local_8 < param_2 + local_1c + -1) {
                if (local_8[1] == '\n') {
                  local_8 = local_8 + 2;
                  *local_10 = '\n';
                }
                else {
                  *local_10 = *local_8;
                  local_8 = local_8 + 1;
                }
                local_10 = local_10 + 1;
              }
              else {
                local_8 = local_8 + 1;
                local_c = 0;
                BVar1 = ReadFile(*(HANDLE *)((&DAT_01286a60)[iVar2] + (param_1 & 0x1f) * 8),local_20
                                 ,1,&local_14,(LPOVERLAPPED)0x0);
                if (BVar1 == 0) {
                  local_c = GetLastError();
                }
                if ((local_c == 0) && (local_14 != 0)) {
                  if ((*(byte *)((&DAT_01286a60)[iVar2] + 4 + (param_1 & 0x1f) * 8) & 0x48) == 0) {
                    if ((local_10 == param_2) && (local_20[0] == '\n')) {
                      *local_10 = '\n';
                      local_10 = local_10 + 1;
                    }
                    else {
                      FUN_00531eb0(param_1,0xffffffff,1);
                      if (local_20[0] != '\n') {
                        *local_10 = '\r';
                        local_10 = local_10 + 1;
                      }
                    }
                  }
                  else {
                    if (local_20[0] == '\n') {
                      *local_10 = '\n';
                    }
                    else {
                      *local_10 = '\r';
                      *(char *)((&DAT_01286a60)[iVar2] + 5 + (param_1 & 0x1f) * 8) = local_20[0];
                    }
                    local_10 = local_10 + 1;
                  }
                }
                else {
                  *local_10 = '\r';
                  local_10 = local_10 + 1;
                }
              }
            }
            else {
              *local_10 = *local_8;
              local_10 = local_10 + 1;
              local_8 = local_8 + 1;
            }
          }
          local_1c = (int)local_10 - (int)param_2;
        }
      }
    }
  }
  else {
    _DAT_00b94050 = 9;
    DAT_00b94054 = 0;
    local_1c = -1;
  }
  return local_1c;
}


// 00530b50

undefined4 * FUN_00530b50(int param_1,char *param_2,undefined4 param_3,undefined4 *param_4)

{
  char cVar1;
  code *pcVar2;
  bool bVar3;
  bool bVar4;
  bool bVar5;
  int iVar6;
  undefined4 *puVar7;
  uint local_20;
  uint local_18;
  
  local_20 = DAT_00b94228;
  bVar4 = false;
  bVar5 = false;
  if ((param_1 == 0) && (iVar6 = FUN_0052fad0(2,"_open.c",0x47,0,"filename != NULL"), iVar6 == 1)) {
    pcVar2 = (code *)swi(3);
    puVar7 = (undefined4 *)(*pcVar2)();
    return puVar7;
  }
  if ((param_2 == (char *)0x0) &&
     (iVar6 = FUN_0052fad0(2,"_open.c",0x48,0,"mode != NULL"), iVar6 == 1)) {
    pcVar2 = (code *)swi(3);
    puVar7 = (undefined4 *)(*pcVar2)();
    return puVar7;
  }
  if ((param_4 == (undefined4 *)0x0) &&
     (iVar6 = FUN_0052fad0(2,"_open.c",0x49,0,"str != NULL"), iVar6 == 1)) {
    pcVar2 = (code *)swi(3);
    puVar7 = (undefined4 *)(*pcVar2)();
    return puVar7;
  }
  cVar1 = *param_2;
  if (cVar1 == 'a') {
    local_18 = 0x109;
    local_20 = local_20 | 2;
  }
  else if (cVar1 == 'r') {
    local_18 = 0;
    local_20 = local_20 | 1;
  }
  else {
    if (cVar1 != 'w') {
      return (undefined4 *)0x0;
    }
    local_18 = 0x301;
    local_20 = local_20 | 2;
  }
  bVar3 = true;
  while ((param_2 = param_2 + 1, *param_2 != '\0' && (bVar3))) {
    switch(*param_2) {
    case '+':
      if ((local_18 & 2) == 0) {
        local_18 = local_18 & 0xfffffffe | 2;
        local_20 = local_20 & 0xfffffffc | 0x80;
      }
      else {
        bVar3 = false;
      }
      break;
    default:
      bVar3 = false;
      break;
    case 'D':
      if ((local_18 & 0x40) == 0) {
        local_18 = local_18 | 0x40;
      }
      else {
        bVar3 = false;
      }
      break;
    case 'R':
      if (bVar5) {
        bVar3 = false;
      }
      else {
        bVar5 = true;
        local_18 = local_18 | 0x10;
      }
      break;
    case 'S':
      if (bVar5) {
        bVar3 = false;
      }
      else {
        bVar5 = true;
        local_18 = local_18 | 0x20;
      }
      break;
    case 'T':
      if ((local_18 & 0x1000) == 0) {
        local_18 = local_18 | 0x1000;
      }
      else {
        bVar3 = false;
      }
      break;
    case 'b':
      if ((local_18 & 0xc000) == 0) {
        local_18 = local_18 | 0x8000;
      }
      else {
        bVar3 = false;
      }
      break;
    case 'c':
      if (bVar4) {
        bVar3 = false;
      }
      else {
        bVar4 = true;
        local_20 = local_20 | 0x4000;
      }
      break;
    case 'n':
      if (bVar4) {
        bVar3 = false;
      }
      else {
        bVar4 = true;
        local_20 = local_20 & 0xffffbfff;
      }
      break;
    case 't':
      if ((local_18 & 0xc000) == 0) {
        local_18 = local_18 | 0x4000;
      }
      else {
        bVar3 = false;
      }
    }
  }
  iVar6 = FUN_00539620(param_1,local_18,param_3,0x1a4);
  if (iVar6 < 0) {
    param_4 = (undefined4 *)0x0;
  }
  else {
    DAT_00b94204 = DAT_00b94204 + 1;
    param_4[3] = local_20;
    param_4[1] = 0;
    *param_4 = 0;
    param_4[2] = 0;
    param_4[7] = 0;
    param_4[4] = iVar6;
  }
  return param_4;
}


// 00530ee0

undefined4 * FUN_00530ee0(void)

{
  undefined4 uVar1;
  undefined4 *local_c;
  int local_8;
  
  local_c = (undefined4 *)0x0;
  local_8 = 0;
  do {
    if (DAT_01286a20 <= local_8) {
LAB_00530f86:
      if (local_c != (undefined4 *)0x0) {
        local_c[1] = 0;
        local_c[3] = 0;
        local_c[2] = 0;
        *local_c = 0;
        local_c[7] = 0;
        local_c[4] = 0xffffffff;
      }
      return local_c;
    }
    if (*(int *)(DAT_012856c8 + local_8 * 4) == 0) {
      uVar1 = FUN_0052c150(0x20,2,"stream.c",0x55);
      *(undefined4 *)(DAT_012856c8 + local_8 * 4) = uVar1;
      if (*(int *)(DAT_012856c8 + local_8 * 4) != 0) {
        local_c = *(undefined4 **)(DAT_012856c8 + local_8 * 4);
      }
      goto LAB_00530f86;
    }
    if ((*(uint *)(*(int *)(DAT_012856c8 + local_8 * 4) + 0xc) & 0x83) == 0) {
      local_c = *(undefined4 **)(DAT_012856c8 + local_8 * 4);
      goto LAB_00530f86;
    }
    local_8 = local_8 + 1;
  } while( true );
}


// 00530fd0

/* Library Function - Single Match
    __setdefaultprecision
   
   Library: Visual Studio 2003 Debug */

void __setdefaultprecision(void)

{
  __controlfp(0x10000,0x30000);
  return;
}


// 00530ff0

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

bool FUN_00530ff0(void)

{
  return _DAT_005460b8 < 0.0;
}


// 00531050

/* Library Function - Single Match
    __ms_p5_mp_test_fdiv
   
   Libraries: Visual Studio 2003, Visual Studio 2005, Visual Studio 2008 */

void __ms_p5_mp_test_fdiv(void)

{
  HMODULE hModule;
  FARPROC pFVar1;
  
  hModule = GetModuleHandleA("KERNEL32");
  if ((hModule != (HMODULE)0x0) &&
     (pFVar1 = GetProcAddress(hModule,"IsProcessorFeaturePresent"), pFVar1 != (FARPROC)0x0)) {
    (*pFVar1)(0);
    return;
  }
  FUN_00530ff0();
  return;
}


// 005310a0

void FUN_005310a0(char *param_1)

{
  char cVar1;
  int iVar2;
  uint local_10;
  char local_c;
  
  iVar2 = FUN_00539fc0((int)*param_1);
  if (iVar2 != 0x65) {
    do {
      param_1 = param_1 + 1;
      if (DAT_0057a5fc < 2) {
        local_10 = *(ushort *)(PTR_DAT_0057a3f0 + *param_1 * 2) & 4;
      }
      else {
        local_10 = FUN_00532300((int)*param_1,4);
      }
    } while (local_10 != 0);
  }
  local_c = *param_1;
  *param_1 = DAT_0057a600;
  do {
    param_1 = param_1 + 1;
    cVar1 = *param_1;
    *param_1 = local_c;
    local_c = cVar1;
  } while (*param_1 != '\0');
  return;
}


// 00531150

/* Library Function - Single Match
    __cropzeros
   
   Libraries: Visual Studio 2003 Debug, Visual Studio 2003 Release */

void __cdecl __cropzeros(char *_Buf)

{
  char *pcVar1;
  char *local_8;
  
  for (; (*_Buf != '\0' && (*_Buf != DAT_0057a600)); _Buf = _Buf + 1) {
  }
  if (*_Buf != '\0') {
    do {
      pcVar1 = _Buf;
      _Buf = pcVar1 + 1;
      if ((*_Buf == '\0') || (*_Buf == 'e')) break;
    } while (*_Buf != 'E');
    local_8 = _Buf;
    for (_Buf = pcVar1; *_Buf == '0'; _Buf = _Buf + -1) {
    }
    if (*_Buf == DAT_0057a600) {
      _Buf = _Buf + -1;
    }
    do {
      _Buf = _Buf + 1;
      *_Buf = *local_8;
      local_8 = local_8 + 1;
    } while (*_Buf != '\0');
  }
  return;
}


// 00531230

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* Library Function - Single Match
    __positive
   
   Libraries: Visual Studio 2003 Debug, Visual Studio 2003 Release */

int __cdecl __positive(double *arg)

{
  uint local_8;
  
  local_8 = (uint)(_DAT_00546090 <= *arg);
  return local_8;
}


// 00531260

/* Library Function - Single Match
    __fassign
   
   Libraries: Visual Studio 2003 Debug, Visual Studio 2003 Release */

void __cdecl __fassign(int flag,char *argument,char *number)

{
  undefined4 local_10;
  undefined4 local_c;
  undefined4 local_8;
  
  if (flag == 0) {
    FUN_0053a890(&local_10,number);
    *(undefined4 *)argument = local_10;
  }
  else {
    FUN_0053a810(&local_c,number);
    *(undefined4 *)argument = local_c;
    *(undefined4 *)(argument + 4) = local_8;
  }
  return;
}


// 005312b0

undefined1 * FUN_005312b0(undefined4 *param_1,undefined1 *param_2,int param_3,int param_4)

{
  undefined1 *puVar1;
  int local_10;
  int *local_c;
  undefined1 *local_8;
  
  if (DAT_00b940b4 == '\0') {
    local_c = (int *)FUN_0053a9d0(*param_1,param_1[1]);
    FUN_0053a8d0(param_2 + (uint)(0 < param_3) + (uint)(*local_c == 0x2d),param_3 + 1,local_c);
  }
  else {
    local_c = DAT_00b940b0;
    __shift(param_2 + (*DAT_00b940b0 == 0x2d),0 < param_3);
  }
  local_8 = param_2;
  if (*local_c == 0x2d) {
    *param_2 = 0x2d;
    local_8 = param_2 + 1;
  }
  if (0 < param_3) {
    *local_8 = local_8[1];
    local_8 = local_8 + 1;
    *local_8 = DAT_0057a600;
  }
  puVar1 = (undefined1 *)FUN_0052b100(local_8 + (uint)(DAT_00b940b4 == '\0') + param_3,"e+000");
  if (param_4 != 0) {
    *puVar1 = 0x45;
  }
  if (*(char *)local_c[3] != '0') {
    local_10 = local_c[1] + -1;
    if (local_10 < 0) {
      local_10 = -local_10;
      puVar1[1] = 0x2d;
    }
    if (99 < local_10) {
      puVar1[2] = puVar1[2] + (char)(local_10 / 100);
      local_10 = local_10 % 100;
    }
    if (9 < local_10) {
      puVar1[3] = puVar1[3] + (char)(local_10 / 10);
      local_10 = local_10 % 10;
    }
    puVar1[4] = puVar1[4] + (char)local_10;
  }
  return param_2;
}


// 00531470

undefined1 * FUN_00531470(undefined4 *param_1,undefined1 *param_2,size_t param_3)

{
  int iVar1;
  size_t local_14;
  int *local_c;
  undefined1 *local_8;
  
  if (DAT_00b940b4 == '\0') {
    local_c = (int *)FUN_0053a9d0(*param_1,param_1[1]);
    FUN_0053a8d0(param_2 + (*local_c == 0x2d),param_3 + local_c[1],local_c);
  }
  else {
    local_c = DAT_00b940b0;
    if (DAT_00b940b8 == param_3) {
      iVar1 = DAT_00b940b8 + (*DAT_00b940b0 == 0x2d);
      param_2[iVar1] = 0x30;
      (param_2 + iVar1)[1] = 0;
    }
  }
  local_8 = param_2;
  if (*local_c == 0x2d) {
    *param_2 = 0x2d;
    local_8 = param_2 + 1;
  }
  if (local_c[1] < 1) {
    __shift(local_8,1);
    *local_8 = 0x30;
    local_8 = local_8 + 1;
  }
  else {
    local_8 = local_8 + local_c[1];
  }
  if (0 < (int)param_3) {
    __shift(local_8,1);
    *local_8 = DAT_0057a600;
    if (local_c[1] < 0) {
      if (DAT_00b940b4 == '\0') {
        if ((int)param_3 < -local_c[1]) {
          local_14 = param_3;
        }
        else {
          local_14 = -local_c[1];
        }
        param_3 = local_14;
      }
      else {
        param_3 = -local_c[1];
      }
      __shift(local_8 + 1,param_3);
      _memset(local_8 + 1,0x30,param_3);
    }
  }
  return param_2;
}


// 00531600

void __thiscall
FUN_00531600(undefined4 param_1,undefined4 *param_2,int param_3,int param_4,undefined4 param_5)

{
  char *pcVar1;
  char *pcVar2;
  
  DAT_00b940b0 = (int *)FUN_0053a9d0(*param_2,param_2[1],param_1);
  DAT_00b940b8 = DAT_00b940b0[1] + -1;
  pcVar1 = (char *)(param_3 + (uint)(*DAT_00b940b0 == 0x2d));
  FUN_0053a8d0(pcVar1,param_4,DAT_00b940b0);
  DAT_00b940bc = DAT_00b940b8 < DAT_00b940b0[1] + -1;
  DAT_00b940b8 = DAT_00b940b0[1] + -1;
  if ((DAT_00b940b8 < -4) || (param_4 <= DAT_00b940b8)) {
    __cftoe_g(param_2,param_3,param_4,param_5);
  }
  else {
    if ((bool)DAT_00b940bc) {
      do {
        pcVar2 = pcVar1;
        pcVar1 = pcVar2 + 1;
      } while (*pcVar2 != '\0');
      pcVar2[-1] = '\0';
    }
    __cftof_g(param_2,param_3,param_4);
  }
  return;
}


// 00531700

/* Library Function - Single Match
    __cftoe_g
   
   Libraries: Visual Studio 2003 Debug, Visual Studio 2003 Release */

undefined4 __thiscall
__cftoe_g(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,
         undefined4 param_5)

{
  undefined4 uVar1;
  
  DAT_00b940b4 = 1;
  uVar1 = FUN_005312b0(param_2,param_3,param_4,param_5,param_1);
  DAT_00b940b4 = 0;
  return uVar1;
}


// 00531740

/* Library Function - Single Match
    __cftof_g
   
   Libraries: Visual Studio 2003 Debug, Visual Studio 2003 Release */

undefined4 __thiscall
__cftof_g(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  undefined4 uVar1;
  
  DAT_00b940b4 = 1;
  uVar1 = FUN_00531470(param_2,param_3,param_4,param_1);
  DAT_00b940b4 = 0;
  return uVar1;
}


// 00531770

/* Library Function - Single Match
    __cfltcvt
   
   Libraries: Visual Studio 2003 Debug, Visual Studio 2003 Release */

errno_t __cdecl
__cfltcvt(double *arg,char *buffer,size_t sizeInBytes,int format,int precision,int caps)

{
  errno_t eVar1;
  
  if ((sizeInBytes == 0x65) || (sizeInBytes == 0x45)) {
    eVar1 = FUN_005312b0(arg,buffer,format,precision);
  }
  else if (sizeInBytes == 0x66) {
    eVar1 = FUN_00531470(arg,buffer,format);
  }
  else {
    eVar1 = FUN_00531600(arg,buffer,format,precision);
  }
  return eVar1;
}


// 005317d0

/* Library Function - Single Match
    __shift
   
   Library: Visual Studio */

void __shift(char *param_1,int param_2)

{
  size_t sVar1;
  
  if (param_2 != 0) {
    sVar1 = _strlen(param_1);
    FUN_0053abc0(param_1 + param_2,param_1,sVar1 + 1);
  }
  return;
}


// 00531800

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

int FUN_00531800(uint param_1,char *param_2,uint param_3)

{
  char cVar1;
  BOOL BVar2;
  int iVar3;
  int local_424;
  DWORD local_41c;
  char local_418 [1028];
  DWORD local_14;
  ulong local_10;
  char *local_c;
  char *local_8;
  
  if ((param_1 < DAT_01286b9c) &&
     (iVar3 = (int)param_1 >> 5,
     (*(byte *)((&DAT_01286a60)[iVar3] + 4 + (param_1 & 0x1f) * 8) & 1) != 0)) {
    local_14 = 0;
    local_424 = 0;
    if (param_3 == 0) {
      local_424 = 0;
    }
    else {
      if ((*(byte *)((&DAT_01286a60)[iVar3] + 4 + (param_1 & 0x1f) * 8) & 0x20) != 0) {
        FUN_00531eb0(param_1,0,2);
      }
      if (((int)*(char *)((&DAT_01286a60)[iVar3] + 4 + (param_1 & 0x1f) * 8) & 0x80U) == 0) {
        BVar2 = WriteFile(*(HANDLE *)((&DAT_01286a60)[iVar3] + (param_1 & 0x1f) * 8),param_2,param_3
                          ,&local_41c,(LPOVERLAPPED)0x0);
        if (BVar2 == 0) {
          local_10 = GetLastError();
        }
        else {
          local_10 = 0;
          local_14 = local_41c;
        }
      }
      else {
        local_8 = param_2;
        local_10 = 0;
        do {
          if (param_3 <= (uint)((int)local_8 - (int)param_2)) break;
          local_c = local_418;
          while (((int)local_c - (int)local_418 < 0x400 &&
                 ((uint)((int)local_8 - (int)param_2) < param_3))) {
            cVar1 = *local_8;
            local_8 = local_8 + 1;
            if (cVar1 == '\n') {
              local_424 = local_424 + 1;
              *local_c = '\r';
              local_c = local_c + 1;
            }
            *local_c = cVar1;
            local_c = local_c + 1;
          }
          BVar2 = WriteFile(*(HANDLE *)((&DAT_01286a60)[iVar3] + (param_1 & 0x1f) * 8),local_418,
                            (int)local_c - (int)local_418,&local_41c,(LPOVERLAPPED)0x0);
          if (BVar2 == 0) {
            local_10 = GetLastError();
            break;
          }
          local_14 = local_14 + local_41c;
        } while ((int)local_c - (int)local_418 <= (int)local_41c);
      }
      if (local_14 == 0) {
        if (local_10 == 0) {
          if (((*(byte *)((&DAT_01286a60)[iVar3] + 4 + (param_1 & 0x1f) * 8) & 0x40) == 0) ||
             (*param_2 != '\x1a')) {
            _DAT_00b94050 = 0x1c;
            DAT_00b94054 = 0;
            local_424 = -1;
          }
          else {
            local_424 = 0;
          }
        }
        else {
          if (local_10 == 5) {
            _DAT_00b94050 = 9;
            DAT_00b94054 = local_10;
          }
          else {
            __dosmaperr(local_10);
          }
          local_424 = -1;
        }
      }
      else {
        local_424 = local_14 - local_424;
      }
    }
  }
  else {
    _DAT_00b94050 = 9;
    DAT_00b94054 = 0;
    local_424 = -1;
  }
  return local_424;
}


// 00531ab0

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* Library Function - Single Match
    __dosmaperr
   
   Library: Visual Studio 2003 Debug */

void __cdecl __dosmaperr(ulong param_1)

{
  uint local_8;
  
  DAT_00b94054 = param_1;
  local_8 = 0;
  while( true ) {
    if (0x2c < local_8) {
      if ((param_1 < 0x13) || (0x24 < param_1)) {
        if ((param_1 < 0xbc) || (0xca < param_1)) {
          _DAT_00b94050 = 0x16;
        }
        else {
          _DAT_00b94050 = 8;
        }
      }
      else {
        _DAT_00b94050 = 0xd;
      }
      return;
    }
    if (param_1 == *(ulong *)(&DAT_0057a280 + local_8 * 8)) break;
    local_8 = local_8 + 1;
  }
  _DAT_00b94050 = *(undefined4 *)(&DAT_0057a284 + local_8 * 8);
  return;
}


// 00531b40

void FUN_00531b40(void)

{
  undefined4 *puVar1;
  int *piVar2;
  DWORD DVar3;
  HANDLE hFile;
  DWORD local_70;
  UINT local_6c;
  UINT local_68;
  byte *local_64;
  int local_60;
  uint local_5c;
  undefined4 *local_54;
  _STARTUPINFOA local_4c;
  byte *local_8;
  
  local_54 = (undefined4 *)FUN_0052c150(0x100,2,"ioinit.c",0x81);
  if (local_54 == (undefined4 *)0x0) {
    __amsg_exit(0x1b);
  }
  DAT_01286b9c = 0x20;
  DAT_01286a60 = local_54;
  for (; local_54 < DAT_01286a60 + 0x40; local_54 = local_54 + 2) {
    *(undefined1 *)(local_54 + 1) = 0;
    *local_54 = 0xffffffff;
    *(undefined1 *)((int)local_54 + 5) = 10;
  }
  GetStartupInfoA(&local_4c);
  if ((local_4c.cbReserved2 != 0) &&
     (CONCAT22(local_4c.lpReserved2._2_2_,local_4c.lpReserved2._0_2_) != 0)) {
    local_6c = *(UINT *)CONCAT22(local_4c.lpReserved2._2_2_,local_4c.lpReserved2._0_2_);
    local_8 = (byte *)(CONCAT22(local_4c.lpReserved2._2_2_,local_4c.lpReserved2._0_2_) + 4);
    local_64 = local_8 + local_6c;
    if (0x7ff < (int)local_6c) {
      local_6c = 0x800;
    }
    local_68 = local_6c;
    local_60 = 1;
    while ((int)DAT_01286b9c < (int)local_6c) {
      local_54 = (undefined4 *)FUN_0052c150(0x100,2,"ioinit.c",0xb6);
      if (local_54 == (undefined4 *)0x0) {
        local_68 = DAT_01286b9c;
        break;
      }
      (&DAT_01286a60)[local_60] = local_54;
      DAT_01286b9c = DAT_01286b9c + 0x20;
      for (; local_54 < (undefined4 *)((int)(&DAT_01286a60)[local_60] + 0x100);
          local_54 = local_54 + 2) {
        *(undefined1 *)(local_54 + 1) = 0;
        *local_54 = 0xffffffff;
        *(undefined1 *)((int)local_54 + 5) = 10;
      }
      local_60 = local_60 + 1;
    }
    for (local_5c = 0; (int)local_5c < (int)local_68; local_5c = local_5c + 1) {
      if (((*(int *)local_64 != -1) && ((*local_8 & 1) != 0)) &&
         (((*local_8 & 8) != 0 || (DVar3 = GetFileType(*(HANDLE *)local_64), DVar3 != 0)))) {
        puVar1 = (undefined4 *)((int)(&DAT_01286a60)[(int)local_5c >> 5] + (local_5c & 0x1f) * 8);
        *puVar1 = *(undefined4 *)local_64;
        *(byte *)(puVar1 + 1) = *local_8;
      }
      local_8 = local_8 + 1;
      local_64 = local_64 + 4;
    }
  }
  for (local_5c = 0; (int)local_5c < 3; local_5c = local_5c + 1) {
    piVar2 = DAT_01286a60 + local_5c * 2;
    if (*piVar2 == -1) {
      *(undefined1 *)(piVar2 + 1) = 0x81;
      if (local_5c == 0) {
        local_70 = 0xfffffff6;
      }
      else {
        local_70 = 0xfffffff5 - (local_5c != 1);
      }
      hFile = GetStdHandle(local_70);
      if ((hFile == (HANDLE)0xffffffff) || (DVar3 = GetFileType(hFile), DVar3 == 0)) {
        *(byte *)(piVar2 + 1) = *(byte *)(piVar2 + 1) | 0x40;
      }
      else {
        *piVar2 = (int)hFile;
        if ((DVar3 & 0xff) == 2) {
          *(byte *)(piVar2 + 1) = *(byte *)(piVar2 + 1) | 0x40;
        }
        else if ((DVar3 & 0xff) == 3) {
          *(byte *)(piVar2 + 1) = *(byte *)(piVar2 + 1) | 8;
        }
      }
    }
    else {
      *(byte *)(piVar2 + 1) = *(byte *)(piVar2 + 1) | 0x80;
    }
  }
  SetHandleCount(DAT_01286b9c);
  return;
}


// 00531e50

/* Library Function - Single Match
    __ioterm
   
   Library: Visual Studio 2003 Debug */

void __cdecl __ioterm(void)

{
  int local_8;
  
  for (local_8 = 0; local_8 < 0x40; local_8 = local_8 + 1) {
    if ((&DAT_01286a60)[local_8] != 0) {
      FUN_0052cb90((&DAT_01286a60)[local_8],2);
      (&DAT_01286a60)[local_8] = 0;
    }
  }
  return;
}


// 00531eb0

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

DWORD FUN_00531eb0(uint param_1,LONG param_2,DWORD param_3)

{
  DWORD DVar1;
  HANDLE hFile;
  int iVar2;
  ulong local_8;
  
  if ((param_1 < DAT_01286b9c) &&
     (iVar2 = (int)param_1 >> 5,
     (*(byte *)((&DAT_01286a60)[iVar2] + 4 + (param_1 & 0x1f) * 8) & 1) != 0)) {
    hFile = (HANDLE)FUN_005393e0(param_1);
    if (hFile == (HANDLE)0xffffffff) {
      _DAT_00b94050 = 9;
      DVar1 = 0xffffffff;
    }
    else {
      DVar1 = SetFilePointer(hFile,param_2,(PLONG)0x0,param_3);
      if (DVar1 == 0xffffffff) {
        local_8 = GetLastError();
      }
      else {
        local_8 = 0;
      }
      if (local_8 == 0) {
        *(byte *)((&DAT_01286a60)[iVar2] + 4 + (param_1 & 0x1f) * 8) =
             *(byte *)((&DAT_01286a60)[iVar2] + 4 + (param_1 & 0x1f) * 8) & 0xfd;
      }
      else {
        __dosmaperr(local_8);
        DVar1 = 0xffffffff;
      }
    }
  }
  else {
    _DAT_00b94050 = 9;
    DAT_00b94054 = 0;
    DVar1 = 0xffffffff;
  }
  return DVar1;
}


// 00531fa0

int FUN_00531fa0(LCID param_1,uint param_2,LPCSTR param_3,int param_4,LPWSTR param_5,int param_6,
                UINT param_7,int param_8)

{
  int iVar1;
  int iVar2;
  void *local_14;
  undefined1 *puStack_10;
  undefined *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &DAT_005476e8;
  puStack_10 = &LAB_00538004;
  local_14 = ExceptionList;
  ExceptionList = &local_14;
  if (DAT_00b940c0 == 0) {
    ExceptionList = &local_14;
    iVar1 = LCMapStringW(0,0x100,L"",1,(LPWSTR)0x0,0);
    if (iVar1 == 0) {
      iVar1 = LCMapStringA(0,0x100,"",1,(LPSTR)0x0,0);
      if (iVar1 == 0) {
        ExceptionList = local_14;
        return 0;
      }
      DAT_00b940c0 = 2;
    }
    else {
      DAT_00b940c0 = 1;
    }
  }
  if (0 < param_4) {
    param_4 = FUN_005322b0(param_3,param_4);
  }
  if (DAT_00b940c0 == 2) {
    iVar1 = LCMapStringA(param_1,param_2,param_3,param_4,(LPSTR)param_5,param_6);
  }
  else if (DAT_00b940c0 == 1) {
    if (param_7 == 0) {
      param_7 = DAT_00b940dc;
    }
    iVar2 = MultiByteToWideChar(param_7,(-(uint)(param_8 != 0) & 8) + 1,param_3,param_4,(LPWSTR)0x0,
                                0);
    if (iVar2 == 0) {
      iVar1 = 0;
    }
    else {
      local_8 = 0;
      FUN_00538c10();
      local_8 = 0xffffffff;
      if (&stack0x00000000 == (undefined1 *)0x44) {
        iVar1 = 0;
      }
      else {
        iVar1 = MultiByteToWideChar(param_7,1,param_3,param_4,(LPWSTR)&stack0xffffffbc,iVar2);
        if (iVar1 == 0) {
          iVar1 = 0;
        }
        else {
          iVar1 = LCMapStringW(param_1,param_2,(LPCWSTR)&stack0xffffffbc,iVar2,(LPWSTR)0x0,0);
          if (iVar1 == 0) {
            iVar1 = 0;
          }
          else if ((param_2 & 0x400) == 0) {
            local_8 = 1;
            FUN_00538c10();
            local_8 = 0xffffffff;
            if (&stack0x00000000 == (undefined1 *)0x44) {
              iVar1 = 0;
            }
            else {
              iVar2 = LCMapStringW(param_1,param_2,(LPCWSTR)&stack0xffffffbc,iVar2,
                                   (LPWSTR)&stack0xffffffbc,iVar1);
              if (iVar2 == 0) {
                iVar1 = 0;
              }
              else if (param_6 == 0) {
                iVar1 = WideCharToMultiByte(param_7,0x220,(LPCWSTR)&stack0xffffffbc,iVar1,(LPSTR)0x0
                                            ,0,(LPCSTR)0x0,(LPBOOL)0x0);
                if (iVar1 == 0) {
                  iVar1 = 0;
                }
              }
              else {
                iVar1 = WideCharToMultiByte(param_7,0x220,(LPCWSTR)&stack0xffffffbc,iVar1,
                                            (LPSTR)param_5,param_6,(LPCSTR)0x0,(LPBOOL)0x0);
                if (iVar1 == 0) {
                  iVar1 = 0;
                }
              }
            }
          }
          else if (param_6 != 0) {
            if (param_6 < iVar1) {
              iVar1 = 0;
            }
            else {
              iVar2 = LCMapStringW(param_1,param_2,(LPCWSTR)&stack0xffffffbc,iVar2,param_5,param_6);
              if (iVar2 == 0) {
                iVar1 = 0;
              }
            }
          }
        }
      }
    }
  }
  else {
    iVar1 = 0;
  }
  ExceptionList = local_14;
  return iVar1;
}


// 005322b0

int FUN_005322b0(char *param_1,int param_2)

{
  int local_c;
  char *local_8;
  
  local_c = param_2;
  for (local_8 = param_1; (local_c != 0 && (*local_8 != '\0')); local_8 = local_8 + 1) {
    local_c = local_c + -1;
  }
  if (*local_8 == '\0') {
    param_2 = (int)local_8 - (int)param_1;
  }
  return param_2;
}


// 00532300

uint FUN_00532300(int param_1,uint param_2)

{
  int iVar1;
  undefined1 local_10;
  undefined1 local_f;
  undefined1 local_e;
  undefined4 local_c;
  uint local_8;
  
  if (param_1 + 1U < 0x101) {
    param_2 = *(ushort *)(PTR_DAT_0057a3f0 + param_1 * 2) & param_2;
  }
  else {
    if ((*(ushort *)(PTR_DAT_0057a3f0 + (param_1 >> 8 & 0xffU) * 2) & 0x8000) == 0) {
      local_10 = (undefined1)param_1;
      local_f = 0;
      local_c = 1;
    }
    else {
      local_10 = (undefined1)((uint)param_1 >> 8);
      local_f = (undefined1)param_1;
      local_e = 0;
      local_c = 2;
    }
    iVar1 = FUN_0053af10(1,&local_10,local_c,&local_8,0,0,1);
    if (iVar1 == 0) {
      param_2 = 0;
    }
    else {
      param_2 = local_8 & 0xffff & param_2;
    }
  }
  return param_2;
}


// 005323c0

/* Library Function - Single Match
    __allmul
   
   Library: Visual Studio */

longlong __allmul(uint param_1,int param_2,uint param_3,int param_4)

{
  if (param_4 == 0 && param_2 == 0) {
    return (ulonglong)param_1 * (ulonglong)param_3;
  }
  return CONCAT44((int)((ulonglong)param_1 * (ulonglong)param_3 >> 0x20) +
                  param_2 * param_3 + param_1 * param_4,
                  (int)((ulonglong)param_1 * (ulonglong)param_3));
}


// 00532400

undefined4 FUN_00532400(undefined4 param_1)

{
  undefined4 uVar1;
  
  uVar1 = DAT_00b940e8;
  DAT_00b940e8 = param_1;
  return uVar1;
}


// 00532420

undefined4 FUN_00532420(void)

{
  return DAT_00b940e8;
}


// 00532430

/* Library Function - Single Match
    __callnewh
   
   Library: Visual Studio 2003 Debug */

int __cdecl __callnewh(size_t _Size)

{
  int iVar1;
  
  if ((DAT_00b940e8 != (code *)0x0) && (iVar1 = (*DAT_00b940e8)(_Size), iVar1 != 0)) {
    return 1;
  }
  return 0;
}


// 00532460

void FUN_00532460(undefined4 param_1)

{
  __nh_malloc_base(param_1,DAT_00b940e4);
  return;
}


// 00532480

/* Library Function - Single Match
    __nh_malloc_base
   
   Library: Visual Studio 2003 Debug */

int __thiscall __nh_malloc_base(int param_1,uint param_2,int param_3)

{
  int iVar1;
  
  if (param_2 < 0xffffffe1) {
    do {
      if (param_2 < 0xffffffe1) {
        param_1 = FUN_005324e0(param_2,param_1);
      }
      else {
        param_1 = 0;
      }
      if (param_1 != 0) {
        return param_1;
      }
      if (param_3 == 0) {
        return 0;
      }
      iVar1 = __callnewh(param_2);
    } while (iVar1 != 0);
  }
  return 0;
}


// 005324e0

LPVOID __thiscall FUN_005324e0(undefined4 param_1,uint param_2)

{
  LPVOID pvVar1;
  
  if ((DAT_0057a618 < param_2) ||
     (pvVar1 = (LPVOID)FUN_00533080(param_2,param_1), pvVar1 == (LPVOID)0x0)) {
    if (param_2 == 0) {
      param_2 = 1;
    }
    pvVar1 = HeapAlloc(DAT_01286a48,0,param_2 + 0xf & 0xfffffff0);
  }
  return pvVar1;
}


// 00532540

undefined4 FUN_00532540(void)

{
  return 1;
}


// 00532550

LPVOID FUN_00532550(LPVOID param_1,uint param_2)

{
  int iVar1;
  LPVOID local_8;
  
  if (param_2 < 0xffffffe1) {
    iVar1 = FUN_005329f0(param_1);
    if (iVar1 == 0) {
      if (param_2 == 0) {
        param_2 = 1;
      }
      local_8 = HeapReAlloc(DAT_01286a48,0x10,param_1,param_2 + 0xf & 0xfffffff0);
    }
    else {
      local_8 = (LPVOID)0x0;
      if ((param_2 <= DAT_0057a618) && (iVar1 = FUN_005338c0(iVar1,param_1,param_2), iVar1 != 0)) {
        local_8 = param_1;
      }
    }
  }
  else {
    local_8 = (LPVOID)0x0;
  }
  return local_8;
}


// 005325e0

LPVOID FUN_005325e0(LPVOID param_1,uint param_2)

{
  LPVOID pvVar1;
  int iVar2;
  int iVar3;
  uint uVar4;
  uint local_18;
  uint local_14;
  LPVOID local_c;
  
  if (param_1 == (LPVOID)0x0) {
    pvVar1 = (LPVOID)FUN_00532460(param_2);
  }
  else if (param_2 == 0) {
    FUN_005327b0(param_1);
    pvVar1 = (LPVOID)0x0;
  }
  else {
    do {
      local_c = (LPVOID)0x0;
      if (param_2 < 0xffffffe1) {
        iVar2 = FUN_005329f0(param_1);
        if (iVar2 == 0) {
          if (param_2 == 0) {
            param_2 = 1;
          }
          param_2 = param_2 + 0xf & 0xfffffff0;
          local_c = HeapReAlloc(DAT_01286a48,0,param_1,param_2);
        }
        else {
          if (param_2 <= DAT_0057a618) {
            iVar3 = FUN_005338c0(iVar2,param_1,param_2);
            if (iVar3 == 0) {
              local_c = (LPVOID)FUN_00533080(param_2);
              if (local_c != (LPVOID)0x0) {
                local_14 = *(int *)((int)param_1 + -4) - 1;
                if (param_2 <= local_14) {
                  local_14 = param_2;
                }
                FUN_0052b650(local_c,param_1,local_14);
                FUN_00532ab0(iVar2,param_1);
              }
            }
            else {
              local_c = param_1;
            }
          }
          if (local_c == (LPVOID)0x0) {
            if (param_2 == 0) {
              param_2 = 1;
            }
            param_2 = param_2 + 0xf & 0xfffffff0;
            local_c = HeapAlloc(DAT_01286a48,0,param_2);
            if (local_c != (LPVOID)0x0) {
              uVar4 = *(int *)((int)param_1 + -4) - 1;
              local_18 = param_2;
              if (uVar4 < param_2) {
                local_18 = uVar4;
              }
              FUN_0052b650(local_c,param_1,local_18);
              FUN_00532ab0(iVar2,param_1);
            }
          }
        }
      }
      if (local_c != (LPVOID)0x0) {
        return local_c;
      }
      if (DAT_00b940e4 == 0) {
        return (LPVOID)0x0;
      }
      iVar2 = __callnewh(param_2);
    } while (iVar2 != 0);
    pvVar1 = (LPVOID)0x0;
  }
  return pvVar1;
}


// 005327b0

void __thiscall FUN_005327b0(undefined4 param_1,LPVOID param_2)

{
  int iVar1;
  
  if (param_2 != (LPVOID)0x0) {
    iVar1 = FUN_005329f0(param_2,param_1);
    if (iVar1 == 0) {
      HeapFree(DAT_01286a48,0,param_2);
    }
    else {
      FUN_00532ab0(iVar1,param_2);
    }
  }
  return;
}


// 00532800

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 FUN_00532800(void)

{
  int iVar1;
  BOOL BVar2;
  DWORD DVar3;
  undefined4 local_8;
  
  local_8 = 0xfffffffe;
  iVar1 = FUN_00533fe0();
  if (iVar1 < 0) {
    local_8 = 0xfffffffc;
  }
  BVar2 = HeapValidate(DAT_01286a48,0,(LPCVOID)0x0);
  if (BVar2 == 0) {
    DVar3 = GetLastError();
    if (DVar3 == 0x78) {
      DAT_00b94054 = 0x78;
      _DAT_00b94050 = 0x28;
    }
    else {
      local_8 = 0xfffffffc;
    }
  }
  return local_8;
}


// 00532860

void FUN_00532860(void)

{
  FUN_00532800();
  return;
}


// 00532870

undefined4 FUN_00532870(int param_1)

{
  undefined4 uVar1;
  int iVar2;
  
  DAT_01286a48 = HeapCreate((uint)(param_1 == 0),0x1000,0);
  if (DAT_01286a48 == (HANDLE)0x0) {
    uVar1 = 0;
  }
  else {
    iVar2 = FUN_00532990();
    if (iVar2 == 0) {
      HeapDestroy(DAT_01286a48);
      uVar1 = 0;
    }
    else {
      uVar1 = 1;
    }
  }
  return uVar1;
}


// 005328c0

void FUN_005328c0(void)

{
  undefined4 local_c;
  undefined4 local_8;
  
  local_c = DAT_01286a44;
  for (local_8 = 0; local_8 < DAT_01286a40; local_8 = local_8 + 1) {
    VirtualFree(*(LPVOID *)((int)local_c + 0xc),0x100000,0x4000);
    VirtualFree(*(LPVOID *)((int)local_c + 0xc),0,0x8000);
    HeapFree(DAT_01286a48,0,*(LPVOID *)((int)local_c + 0x10));
    local_c = (LPVOID)((int)local_c + 0x14);
  }
  HeapFree(DAT_01286a48,0,DAT_01286a44);
  HeapDestroy(DAT_01286a48);
  return;
}


// 00532960

undefined4 FUN_00532960(void)

{
  return DAT_0057a618;
}


// 00532970

bool FUN_00532970(uint param_1)

{
  if (param_1 < 0x3f9) {
    DAT_0057a618 = param_1;
  }
  return param_1 < 0x3f9;
}


// 00532990

bool FUN_00532990(void)

{
  DAT_01286a44 = HeapAlloc(DAT_01286a48,0,0x140);
  if (DAT_01286a44 != (LPVOID)0x0) {
    DAT_01286a3c = 0;
    DAT_01286a40 = 0;
    DAT_01286a24 = 0x10;
    DAT_01286a38 = DAT_01286a44;
  }
  return DAT_01286a44 != (LPVOID)0x0;
}


// 005329f0

uint FUN_005329f0(int param_1)

{
  uint local_c;
  
  local_c = DAT_01286a44;
  while( true ) {
    if (DAT_01286a44 + DAT_01286a40 * 0x14 <= local_c) {
      return 0;
    }
    if ((uint)(param_1 - *(int *)(local_c + 0xc)) < 0x100000) break;
    local_c = local_c + 0x14;
  }
  return local_c;
}


// 00532a50

undefined4 FUN_00532a50(int param_1,int param_2)

{
  uint uVar1;
  undefined4 local_10;
  
  uVar1 = param_2 - *(int *)(param_1 + 0xc);
  if ((((*(uint *)(param_1 + 8) & 0x80000000U >> ((byte)(uVar1 >> 0xf) & 0x1f)) == 0) &&
      ((uVar1 & 0xf) == 0)) && ((uVar1 & 0xfff) != 0)) {
    local_10 = 1;
  }
  else {
    local_10 = 0;
  }
  return local_10;
}


// 00532ab0

void FUN_00532ab0(uint *param_1,int param_2)

{
  int *piVar1;
  int *piVar2;
  char cVar3;
  uint uVar4;
  uint uVar5;
  uint uVar6;
  byte bVar7;
  uint uVar8;
  uint *puVar9;
  int local_34;
  uint local_30;
  uint local_2c;
  uint local_28;
  int *local_20;
  
  uVar4 = param_1[4];
  uVar8 = param_2 - param_1[3] >> 0xf;
  piVar2 = (int *)(uVar4 + 0x144 + uVar8 * 0x204);
  local_20 = (int *)(param_2 + -4);
  local_34 = *local_20 + -1;
  puVar9 = (uint *)((int)local_20 + local_34);
  uVar5 = *puVar9;
  uVar6 = *(uint *)(param_2 + -8);
  if ((uVar5 & 1) == 0) {
    local_28 = ((int)uVar5 >> 4) - 1;
    if (0x3f < local_28) {
      local_28 = 0x3f;
    }
    if (puVar9[1] == puVar9[2]) {
      bVar7 = (byte)local_28;
      if (local_28 < 0x20) {
        *(uint *)(uVar4 + 0x44 + uVar8 * 4) =
             *(uint *)(uVar4 + 0x44 + uVar8 * 4) & ~(0x80000000U >> (bVar7 & 0x1f));
        *(char *)(uVar4 + local_28 + 4) = *(char *)(uVar4 + local_28 + 4) + -1;
        if (*(char *)(uVar4 + local_28 + 4) == '\0') {
          *param_1 = *param_1 & ~(0x80000000U >> (bVar7 & 0x1f));
        }
      }
      else {
        *(uint *)(uVar4 + 0xc4 + uVar8 * 4) =
             *(uint *)(uVar4 + 0xc4 + uVar8 * 4) & ~(0x80000000U >> (bVar7 - 0x20 & 0x1f));
        *(char *)(uVar4 + local_28 + 4) = *(char *)(uVar4 + local_28 + 4) + -1;
        if (*(char *)(uVar4 + local_28 + 4) == '\0') {
          param_1[1] = param_1[1] & ~(0x80000000U >> (bVar7 - 0x20 & 0x1f));
        }
      }
    }
    *(uint *)(puVar9[2] + 4) = puVar9[1];
    *(uint *)(puVar9[1] + 8) = puVar9[2];
    local_34 = local_34 + uVar5;
  }
  local_2c = (local_34 >> 4) - 1;
  if (0x3f < local_2c) {
    local_2c = 0x3f;
  }
  if ((uVar6 & 1) == 0) {
    local_20 = (int *)((int)local_20 - uVar6);
    local_30 = ((int)uVar6 >> 4) - 1;
    if (0x3f < local_30) {
      local_30 = 0x3f;
    }
    local_34 = local_34 + uVar6;
    local_2c = (local_34 >> 4) - 1;
    if (0x3f < local_2c) {
      local_2c = 0x3f;
    }
    if (local_30 != local_2c) {
      if (local_20[1] == local_20[2]) {
        bVar7 = (byte)local_30;
        if (local_30 < 0x20) {
          *(uint *)(uVar4 + 0x44 + uVar8 * 4) =
               *(uint *)(uVar4 + 0x44 + uVar8 * 4) & ~(0x80000000U >> (bVar7 & 0x1f));
          *(char *)(uVar4 + local_30 + 4) = *(char *)(uVar4 + local_30 + 4) + -1;
          if (*(char *)(uVar4 + local_30 + 4) == '\0') {
            *param_1 = *param_1 & ~(0x80000000U >> (bVar7 & 0x1f));
          }
        }
        else {
          *(uint *)(uVar4 + 0xc4 + uVar8 * 4) =
               *(uint *)(uVar4 + 0xc4 + uVar8 * 4) & ~(0x80000000U >> (bVar7 - 0x20 & 0x1f));
          *(char *)(uVar4 + local_30 + 4) = *(char *)(uVar4 + local_30 + 4) + -1;
          if (*(char *)(uVar4 + local_30 + 4) == '\0') {
            param_1[1] = param_1[1] & ~(0x80000000U >> (bVar7 - 0x20 & 0x1f));
          }
        }
      }
      *(int *)(local_20[2] + 4) = local_20[1];
      *(int *)(local_20[1] + 8) = local_20[2];
    }
  }
  if (((uVar6 & 1) != 0) || (local_30 != local_2c)) {
    piVar1 = piVar2 + local_2c * 2;
    local_20[1] = piVar1[1];
    local_20[2] = (int)piVar1;
    piVar1[1] = (int)local_20;
    *(int **)(local_20[1] + 8) = local_20;
    if (local_20[1] == local_20[2]) {
      bVar7 = (byte)local_2c;
      if (local_2c < 0x20) {
        cVar3 = *(char *)(uVar4 + local_2c + 4);
        *(char *)(uVar4 + local_2c + 4) = *(char *)(uVar4 + local_2c + 4) + '\x01';
        if (cVar3 == '\0') {
          *param_1 = *param_1 | 0x80000000U >> (bVar7 & 0x1f);
        }
        *(uint *)(uVar4 + 0x44 + uVar8 * 4) =
             *(uint *)(uVar4 + 0x44 + uVar8 * 4) | 0x80000000U >> (bVar7 & 0x1f);
      }
      else {
        cVar3 = *(char *)(uVar4 + local_2c + 4);
        *(char *)(uVar4 + local_2c + 4) = *(char *)(uVar4 + local_2c + 4) + '\x01';
        if (cVar3 == '\0') {
          param_1[1] = param_1[1] | 0x80000000U >> (bVar7 - 0x20 & 0x1f);
        }
        *(uint *)(uVar4 + 0xc4 + uVar8 * 4) =
             *(uint *)(uVar4 + 0xc4 + uVar8 * 4) | 0x80000000U >> (bVar7 - 0x20 & 0x1f);
      }
    }
  }
  *local_20 = local_34;
  *(int *)((int)local_20 + local_34 + -4) = local_34;
  *piVar2 = *piVar2 + -1;
  if (*piVar2 == 0) {
    if (DAT_01286a3c != (uint *)0x0) {
      VirtualFree((LPVOID)(DAT_01286a3c[3] + DAT_01286a34 * 0x8000),0x8000,0x4000);
      DAT_01286a3c[2] = DAT_01286a3c[2] | 0x80000000U >> ((byte)DAT_01286a34 & 0x1f);
      *(undefined4 *)(DAT_01286a3c[4] + 0xc4 + DAT_01286a34 * 4) = 0;
      *(char *)(DAT_01286a3c[4] + 0x43) = *(char *)(DAT_01286a3c[4] + 0x43) + -1;
      if (*(char *)(DAT_01286a3c[4] + 0x43) == '\0') {
        DAT_01286a3c[1] = DAT_01286a3c[1] & 0xfffffffe;
      }
      if (DAT_01286a3c[2] == 0xffffffff) {
        VirtualFree((LPVOID)DAT_01286a3c[3],0,0x8000);
        HeapFree(DAT_01286a48,0,(LPVOID)DAT_01286a3c[4]);
        FUN_0053abc0(DAT_01286a3c,DAT_01286a3c + 5,
                     (DAT_01286a44 + DAT_01286a40 * 0x14) - (int)(DAT_01286a3c + 5));
        DAT_01286a40 = DAT_01286a40 + -1;
        if (DAT_01286a3c < param_1) {
          param_1 = param_1 + -5;
        }
        DAT_01286a38 = DAT_01286a44;
      }
    }
    DAT_01286a3c = param_1;
    DAT_01286a34 = uVar8;
  }
  return;
}


// 00533080

int * FUN_00533080(int param_1)

{
  int *piVar1;
  int *piVar2;
  char cVar3;
  int *piVar4;
  int iVar5;
  undefined4 uVar6;
  byte bVar7;
  uint *puVar8;
  int *piVar9;
  uint uVar10;
  uint local_38;
  int local_34;
  uint local_28;
  int local_24;
  uint local_20;
  uint *local_1c;
  int local_18;
  
  puVar8 = DAT_01286a44 + DAT_01286a40 * 5;
  uVar10 = param_1 + 0x17U & 0xfffffff0;
  iVar5 = ((int)(param_1 + 0x17U) >> 4) + -1;
  bVar7 = (byte)iVar5;
  if (iVar5 < 0x20) {
    local_28 = 0xffffffff >> (bVar7 & 0x1f);
    local_38 = 0xffffffff;
  }
  else {
    local_28 = 0;
    local_38 = 0xffffffff >> (bVar7 - 0x20 & 0x1f);
  }
  for (local_1c = DAT_01286a38;
      (local_1c < puVar8 && ((local_28 & *local_1c) == 0 && (local_38 & local_1c[1]) == 0));
      local_1c = local_1c + 5) {
  }
  if (local_1c == puVar8) {
    for (local_1c = DAT_01286a44;
        (local_1c < DAT_01286a38 && ((local_28 & *local_1c) == 0 && (local_38 & local_1c[1]) == 0));
        local_1c = local_1c + 5) {
    }
    if (local_1c == DAT_01286a38) {
      for (; (local_1c < puVar8 && (local_1c[2] == 0)); local_1c = local_1c + 5) {
      }
      if (local_1c == puVar8) {
        for (local_1c = DAT_01286a44; (local_1c < DAT_01286a38 && (local_1c[2] == 0));
            local_1c = local_1c + 5) {
        }
        if ((local_1c == DAT_01286a38) &&
           (local_1c = (uint *)FUN_005335c0(), local_1c == (uint *)0x0)) {
          return (int *)0x0;
        }
      }
      uVar6 = FUN_005336d0(local_1c);
      *(undefined4 *)local_1c[4] = uVar6;
      if (*(int *)local_1c[4] == -1) {
        return (int *)0x0;
      }
    }
  }
  DAT_01286a38 = local_1c;
  piVar4 = (int *)local_1c[4];
  local_34 = *piVar4;
  if ((local_34 == -1) ||
     ((local_28 & piVar4[local_34 + 0x11]) == 0 && (local_38 & piVar4[local_34 + 0x31]) == 0)) {
    local_34 = 0;
    while ((local_28 & piVar4[local_34 + 0x11]) == 0 && (local_38 & piVar4[local_34 + 0x31]) == 0) {
      local_34 = local_34 + 1;
    }
  }
  piVar2 = piVar4 + local_34 * 0x81 + 0x51;
  local_24 = 0;
  local_20 = local_28 & piVar4[local_34 + 0x11];
  if (local_20 == 0) {
    local_24 = 0x20;
    local_20 = local_38 & piVar4[local_34 + 0x31];
  }
  for (; -1 < (int)local_20; local_20 = local_20 << 1) {
    local_24 = local_24 + 1;
  }
  piVar9 = (int *)piVar2[local_24 * 2 + 1];
  iVar5 = *piVar9 - uVar10;
  local_18 = (iVar5 >> 4) + -1;
  if (0x3f < local_18) {
    local_18 = 0x3f;
  }
  if (local_18 != local_24) {
    if (piVar9[1] == piVar9[2]) {
      bVar7 = (byte)local_24;
      if (local_24 < 0x20) {
        piVar4[local_34 + 0x11] = piVar4[local_34 + 0x11] & ~(0x80000000U >> (bVar7 & 0x1f));
        *(char *)((int)piVar4 + local_24 + 4) = *(char *)((int)piVar4 + local_24 + 4) + -1;
        if (*(char *)((int)piVar4 + local_24 + 4) == '\0') {
          *local_1c = *local_1c & ~(0x80000000U >> (bVar7 & 0x1f));
        }
      }
      else {
        piVar4[local_34 + 0x31] = piVar4[local_34 + 0x31] & ~(0x80000000U >> (bVar7 - 0x20 & 0x1f));
        *(char *)((int)piVar4 + local_24 + 4) = *(char *)((int)piVar4 + local_24 + 4) + -1;
        if (*(char *)((int)piVar4 + local_24 + 4) == '\0') {
          local_1c[1] = local_1c[1] & ~(0x80000000U >> (bVar7 - 0x20 & 0x1f));
        }
      }
    }
    *(int *)(piVar9[2] + 4) = piVar9[1];
    *(int *)(piVar9[1] + 8) = piVar9[2];
    if (iVar5 != 0) {
      piVar1 = piVar2 + local_18 * 2;
      piVar9[1] = piVar1[1];
      piVar9[2] = (int)piVar1;
      piVar1[1] = (int)piVar9;
      *(int **)(piVar9[1] + 8) = piVar9;
      if (piVar9[1] == piVar9[2]) {
        bVar7 = (byte)local_18;
        if (local_18 < 0x20) {
          cVar3 = *(char *)((int)piVar4 + local_18 + 4);
          *(char *)((int)piVar4 + local_18 + 4) = *(char *)((int)piVar4 + local_18 + 4) + '\x01';
          if (cVar3 == '\0') {
            *local_1c = *local_1c | 0x80000000U >> (bVar7 & 0x1f);
          }
          piVar4[local_34 + 0x11] = piVar4[local_34 + 0x11] | 0x80000000U >> (bVar7 & 0x1f);
        }
        else {
          cVar3 = *(char *)((int)piVar4 + local_18 + 4);
          *(char *)((int)piVar4 + local_18 + 4) = *(char *)((int)piVar4 + local_18 + 4) + '\x01';
          if (cVar3 == '\0') {
            local_1c[1] = local_1c[1] | 0x80000000U >> (bVar7 - 0x20 & 0x1f);
          }
          piVar4[local_34 + 0x31] = piVar4[local_34 + 0x31] | 0x80000000U >> (bVar7 - 0x20 & 0x1f);
        }
      }
    }
  }
  if (iVar5 != 0) {
    *piVar9 = iVar5;
    *(int *)((int)piVar9 + iVar5 + -4) = iVar5;
  }
  piVar9 = (int *)((int)piVar9 + iVar5);
  *piVar9 = uVar10 + 1;
  *(uint *)((int)piVar9 + (uVar10 - 4)) = uVar10 + 1;
  iVar5 = *piVar2;
  *piVar2 = *piVar2 + 1;
  if (((iVar5 == 0) && (local_1c == DAT_01286a3c)) && (local_34 == DAT_01286a34)) {
    DAT_01286a3c = (uint *)0x0;
  }
  *piVar4 = local_34;
  return piVar9 + 1;
}


// 005335c0

undefined4 * FUN_005335c0(void)

{
  LPVOID pvVar1;
  undefined4 *puVar2;
  
  if (DAT_01286a40 == DAT_01286a24) {
    pvVar1 = HeapReAlloc(DAT_01286a48,0,DAT_01286a44,(DAT_01286a24 + 0x10) * 0x14);
    if (pvVar1 == (LPVOID)0x0) {
      return (undefined4 *)0x0;
    }
    DAT_01286a24 = DAT_01286a24 + 0x10;
    DAT_01286a44 = pvVar1;
  }
  puVar2 = (undefined4 *)((int)DAT_01286a44 + DAT_01286a40 * 0x14);
  pvVar1 = HeapAlloc(DAT_01286a48,8,0x41c4);
  puVar2[4] = pvVar1;
  if (puVar2[4] == 0) {
    puVar2 = (undefined4 *)0x0;
  }
  else {
    pvVar1 = VirtualAlloc((LPVOID)0x0,0x100000,0x2000,4);
    puVar2[3] = pvVar1;
    if (puVar2[3] == 0) {
      HeapFree(DAT_01286a48,0,(LPVOID)puVar2[4]);
      puVar2 = (undefined4 *)0x0;
    }
    else {
      *puVar2 = 0;
      puVar2[1] = 0;
      puVar2[2] = 0xffffffff;
      DAT_01286a40 = DAT_01286a40 + 1;
      *(undefined4 *)puVar2[4] = 0xffffffff;
    }
  }
  return puVar2;
}


// 005336d0

int FUN_005336d0(int param_1)

{
  int iVar1;
  int iVar2;
  char cVar3;
  int iVar4;
  LPVOID pvVar5;
  LPVOID lpAddress;
  undefined4 local_2c;
  undefined4 local_24;
  undefined4 local_c;
  undefined4 local_8;
  
  iVar4 = *(int *)(param_1 + 0x10);
  local_c = *(int *)(param_1 + 8);
  local_2c = 0;
  for (; -1 < local_c; local_c = local_c << 1) {
    local_2c = local_2c + 1;
  }
  iVar2 = iVar4 + 0x144 + local_2c * 0x204;
  for (local_24 = 0; local_24 < 0x3f; local_24 = local_24 + 1) {
    iVar1 = iVar2 + local_24 * 8;
    *(int *)(iVar1 + 8) = iVar1;
    *(int *)(iVar1 + 4) = iVar1;
  }
  lpAddress = (LPVOID)(*(int *)(param_1 + 0xc) + local_2c * 0x8000);
  pvVar5 = VirtualAlloc(lpAddress,0x8000,0x1000,4);
  if (pvVar5 == (LPVOID)0x0) {
    local_2c = -1;
  }
  else {
    for (local_8 = lpAddress; local_8 <= (LPVOID)((int)lpAddress + 0x7000U);
        local_8 = (LPVOID)((int)local_8 + 0x1000)) {
      *(undefined4 *)((int)local_8 + 8) = 0xffffffff;
      *(undefined4 *)((int)local_8 + 0xffc) = 0xffffffff;
      *(undefined4 *)((int)local_8 + 0xc) = 0xff0;
      *(int *)((int)local_8 + 0x10) = (int)local_8 + 0x100c;
      *(int *)((int)local_8 + 0x14) = (int)local_8 + -0xff4;
      *(undefined4 *)((int)local_8 + 0xff8) = 0xff0;
    }
    *(int *)(iVar2 + 0x1fc) = (int)lpAddress + 0xc;
    *(int *)(*(int *)(iVar2 + 0x1fc) + 8) = iVar2 + 0x1f8;
    *(int *)(iVar2 + 0x200) = (int)lpAddress + 0x700c;
    *(int *)(*(int *)(iVar2 + 0x200) + 4) = iVar2 + 0x1f8;
    *(undefined4 *)(iVar4 + 0x44 + local_2c * 4) = 0;
    *(undefined4 *)(iVar4 + 0xc4 + local_2c * 4) = 1;
    cVar3 = *(char *)(iVar4 + 0x43);
    *(char *)(iVar4 + 0x43) = *(char *)(iVar4 + 0x43) + '\x01';
    if (cVar3 == '\0') {
      *(uint *)(param_1 + 4) = *(uint *)(param_1 + 4) | 1;
    }
    *(uint *)(param_1 + 8) = *(uint *)(param_1 + 8) & ~(0x80000000U >> ((byte)local_2c & 0x1f));
  }
  return local_2c;
}


// 005338c0

undefined4 FUN_005338c0(uint *param_1,int param_2,int param_3)

{
  int iVar1;
  char cVar2;
  uint uVar3;
  uint uVar4;
  uint uVar5;
  int *piVar6;
  uint *puVar7;
  int iVar8;
  byte bVar9;
  int *piVar10;
  uint uVar11;
  int local_2c;
  uint local_28;
  uint local_24;
  
  uVar5 = param_3 + 0x17U & 0xfffffff0;
  uVar3 = param_1[4];
  uVar11 = param_2 - param_1[3] >> 0xf;
  iVar1 = uVar3 + 0x144 + uVar11 * 0x204;
  piVar6 = (int *)(param_2 + -4);
  local_2c = *piVar6 + -1;
  puVar7 = (uint *)((int)piVar6 + local_2c);
  uVar4 = *puVar7;
  if (local_2c < (int)uVar5) {
    if (((uVar4 & 1) != 0) || ((int)(local_2c + uVar4) < (int)uVar5)) {
      return 0;
    }
    local_24 = ((int)uVar4 >> 4) - 1;
    if (0x3f < local_24) {
      local_24 = 0x3f;
    }
    if (puVar7[1] == puVar7[2]) {
      bVar9 = (byte)local_24;
      if (local_24 < 0x20) {
        *(uint *)(uVar3 + 0x44 + uVar11 * 4) =
             *(uint *)(uVar3 + 0x44 + uVar11 * 4) & ~(0x80000000U >> (bVar9 & 0x1f));
        *(char *)(uVar3 + local_24 + 4) = *(char *)(uVar3 + local_24 + 4) + -1;
        if (*(char *)(uVar3 + local_24 + 4) == '\0') {
          *param_1 = *param_1 & ~(0x80000000U >> (bVar9 & 0x1f));
        }
      }
      else {
        *(uint *)(uVar3 + 0xc4 + uVar11 * 4) =
             *(uint *)(uVar3 + 0xc4 + uVar11 * 4) & ~(0x80000000U >> (bVar9 - 0x20 & 0x1f));
        *(char *)(uVar3 + local_24 + 4) = *(char *)(uVar3 + local_24 + 4) + -1;
        if (*(char *)(uVar3 + local_24 + 4) == '\0') {
          param_1[1] = param_1[1] & ~(0x80000000U >> (bVar9 - 0x20 & 0x1f));
        }
      }
    }
    *(uint *)(puVar7[2] + 4) = puVar7[1];
    *(uint *)(puVar7[1] + 8) = puVar7[2];
    iVar8 = (local_2c + uVar4) - uVar5;
    if (0 < iVar8) {
      piVar10 = (int *)((int)piVar6 + uVar5);
      local_24 = (iVar8 >> 4) - 1;
      if (0x3f < local_24) {
        local_24 = 0x3f;
      }
      iVar1 = iVar1 + local_24 * 8;
      piVar10[1] = *(int *)(iVar1 + 4);
      piVar10[2] = iVar1;
      *(int **)(iVar1 + 4) = piVar10;
      *(int **)(piVar10[1] + 8) = piVar10;
      if (piVar10[1] == piVar10[2]) {
        bVar9 = (byte)local_24;
        if (local_24 < 0x20) {
          cVar2 = *(char *)(uVar3 + local_24 + 4);
          *(char *)(uVar3 + local_24 + 4) = *(char *)(uVar3 + local_24 + 4) + '\x01';
          if (cVar2 == '\0') {
            *param_1 = *param_1 | 0x80000000U >> (bVar9 & 0x1f);
          }
          *(uint *)(uVar3 + 0x44 + uVar11 * 4) =
               *(uint *)(uVar3 + 0x44 + uVar11 * 4) | 0x80000000U >> (bVar9 & 0x1f);
        }
        else {
          cVar2 = *(char *)(uVar3 + local_24 + 4);
          *(char *)(uVar3 + local_24 + 4) = *(char *)(uVar3 + local_24 + 4) + '\x01';
          if (cVar2 == '\0') {
            param_1[1] = param_1[1] | 0x80000000U >> (bVar9 - 0x20 & 0x1f);
          }
          *(uint *)(uVar3 + 0xc4 + uVar11 * 4) =
               *(uint *)(uVar3 + 0xc4 + uVar11 * 4) | 0x80000000U >> (bVar9 - 0x20 & 0x1f);
        }
      }
      *piVar10 = iVar8;
      *(int *)((int)piVar10 + iVar8 + -4) = iVar8;
    }
    *piVar6 = uVar5 + 1;
    *(uint *)((int)piVar6 + (uVar5 - 4)) = uVar5 + 1;
  }
  else if ((int)uVar5 < local_2c) {
    *piVar6 = uVar5 + 1;
    *(uint *)((int)piVar6 + (uVar5 - 4)) = uVar5 + 1;
    piVar6 = (int *)((int)piVar6 + uVar5);
    local_2c = local_2c - uVar5;
    local_28 = (local_2c >> 4) - 1;
    if (0x3f < local_28) {
      local_28 = 0x3f;
    }
    if ((uVar4 & 1) == 0) {
      local_24 = ((int)uVar4 >> 4) - 1;
      if (0x3f < local_24) {
        local_24 = 0x3f;
      }
      if (puVar7[1] == puVar7[2]) {
        bVar9 = (byte)local_24;
        if (local_24 < 0x20) {
          *(uint *)(uVar3 + 0x44 + uVar11 * 4) =
               *(uint *)(uVar3 + 0x44 + uVar11 * 4) & ~(0x80000000U >> (bVar9 & 0x1f));
          *(char *)(uVar3 + local_24 + 4) = *(char *)(uVar3 + local_24 + 4) + -1;
          if (*(char *)(uVar3 + local_24 + 4) == '\0') {
            *param_1 = *param_1 & ~(0x80000000U >> (bVar9 & 0x1f));
          }
        }
        else {
          *(uint *)(uVar3 + 0xc4 + uVar11 * 4) =
               *(uint *)(uVar3 + 0xc4 + uVar11 * 4) & ~(0x80000000U >> (bVar9 - 0x20 & 0x1f));
          *(char *)(uVar3 + local_24 + 4) = *(char *)(uVar3 + local_24 + 4) + -1;
          if (*(char *)(uVar3 + local_24 + 4) == '\0') {
            param_1[1] = param_1[1] & ~(0x80000000U >> (bVar9 - 0x20 & 0x1f));
          }
        }
      }
      *(uint *)(puVar7[2] + 4) = puVar7[1];
      *(uint *)(puVar7[1] + 8) = puVar7[2];
      local_2c = local_2c + uVar4;
      local_28 = (local_2c >> 4) - 1;
      if (0x3f < local_28) {
        local_28 = 0x3f;
      }
    }
    iVar1 = iVar1 + local_28 * 8;
    piVar6[1] = *(int *)(iVar1 + 4);
    piVar6[2] = iVar1;
    *(int **)(iVar1 + 4) = piVar6;
    *(int **)(piVar6[1] + 8) = piVar6;
    if (piVar6[1] == piVar6[2]) {
      bVar9 = (byte)local_28;
      if (local_28 < 0x20) {
        cVar2 = *(char *)(uVar3 + local_28 + 4);
        *(char *)(uVar3 + local_28 + 4) = *(char *)(uVar3 + local_28 + 4) + '\x01';
        if (cVar2 == '\0') {
          *param_1 = *param_1 | 0x80000000U >> (bVar9 & 0x1f);
        }
        *(uint *)(uVar3 + 0x44 + uVar11 * 4) =
             *(uint *)(uVar3 + 0x44 + uVar11 * 4) | 0x80000000U >> (bVar9 & 0x1f);
      }
      else {
        cVar2 = *(char *)(uVar3 + local_28 + 4);
        *(char *)(uVar3 + local_28 + 4) = *(char *)(uVar3 + local_28 + 4) + '\x01';
        if (cVar2 == '\0') {
          param_1[1] = param_1[1] | 0x80000000U >> (bVar9 - 0x20 & 0x1f);
        }
        *(uint *)(uVar3 + 0xc4 + uVar11 * 4) =
             *(uint *)(uVar3 + 0xc4 + uVar11 * 4) | 0x80000000U >> (bVar9 - 0x20 & 0x1f);
      }
    }
    *piVar6 = local_2c;
    *(int *)((int)piVar6 + local_2c + -4) = local_2c;
  }
  return 1;
}


// 00533eb0

void FUN_00533eb0(void)

{
  if (DAT_01286a3c != 0) {
    VirtualFree((LPVOID)(*(int *)(DAT_01286a3c + 0xc) + DAT_01286a34 * 0x8000),0x8000,0x4000);
    *(uint *)(DAT_01286a3c + 8) =
         *(uint *)(DAT_01286a3c + 8) | 0x80000000U >> ((byte)DAT_01286a34 & 0x1f);
    *(undefined4 *)(*(int *)(DAT_01286a3c + 0x10) + 0xc4 + DAT_01286a34 * 4) = 0;
    *(char *)(*(int *)(DAT_01286a3c + 0x10) + 0x43) =
         *(char *)(*(int *)(DAT_01286a3c + 0x10) + 0x43) + -1;
    if (*(char *)(*(int *)(DAT_01286a3c + 0x10) + 0x43) == '\0') {
      *(uint *)(DAT_01286a3c + 4) = *(uint *)(DAT_01286a3c + 4) & 0xfffffffe;
    }
    if ((*(int *)(DAT_01286a3c + 8) == -1) && (1 < DAT_01286a40)) {
      HeapFree(DAT_01286a48,0,*(LPVOID *)(DAT_01286a3c + 0x10));
      FUN_0053abc0(DAT_01286a3c,DAT_01286a3c + 0x14,
                   (DAT_01286a44 + DAT_01286a40 * 0x14) - (DAT_01286a3c + 0x14));
      DAT_01286a40 = DAT_01286a40 + -1;
    }
    DAT_01286a3c = 0;
  }
  return;
}


// 00533fe0

undefined4 FUN_00533fe0(void)

{
  LPVOID lp;
  uint uVar1;
  BOOL BVar2;
  undefined4 uVar3;
  uint *puVar4;
  byte bVar5;
  uint *puVar6;
  int local_16c;
  uint local_15c;
  uint local_154;
  int local_150;
  uint local_14c;
  uint local_148;
  int local_144;
  uint *local_140;
  uint *local_138;
  uint *local_134;
  uint local_130;
  uint *local_12c;
  int local_124;
  uint local_120;
  int aiStack_11c [64];
  uint *local_1c;
  int local_18;
  uint *local_14;
  int local_10;
  uint *local_c;
  uint local_8;
  
  BVar2 = IsBadWritePtr(DAT_01286a44,DAT_01286a40 * 0x14);
  if (BVar2 == 0) {
    local_140 = DAT_01286a44;
    for (local_124 = 0; local_124 < DAT_01286a40; local_124 = local_124 + 1) {
      lp = (LPVOID)local_140[4];
      BVar2 = IsBadWritePtr(lp,0x41c4);
      if (BVar2 != 0) {
        return 0xfffffffe;
      }
      local_12c = (uint *)local_140[3];
      local_1c = (uint *)((int)lp + 0x144);
      local_8 = local_140[2];
      local_148 = 0;
      local_15c = 0;
      for (local_10 = 0; local_10 < 0x20; local_10 = local_10 + 1) {
        local_120 = 0;
        local_154 = 0;
        local_130 = 0;
        for (local_150 = 0; local_150 < 0x40; local_150 = local_150 + 1) {
          aiStack_11c[local_150] = 0;
        }
        if (-1 < (int)local_8) {
          BVar2 = IsBadWritePtr(local_12c,0x8000);
          if (BVar2 != 0) {
            return 0xfffffffc;
          }
          local_c = local_12c;
          for (local_144 = 0; local_144 < 8; local_144 = local_144 + 1) {
            local_134 = local_c + 3;
            puVar6 = local_c + 0x3ff;
            if ((local_c[2] != 0xffffffff) || (*puVar6 != 0xffffffff)) {
              return 0xfffffffb;
            }
            do {
              uVar1 = *local_134;
              if ((uVar1 & 1) == 0) {
                local_150 = ((int)uVar1 >> 4) + -1;
                if (0x3f < local_150) {
                  local_150 = 0x3f;
                }
                aiStack_11c[local_150] = aiStack_11c[local_150] + 1;
                local_14c = uVar1;
              }
              else {
                if (0x400 < (int)(uVar1 - 1)) {
                  return 0xfffffffa;
                }
                local_130 = local_130 + 1;
                local_14c = uVar1 - 1;
              }
              if ((((int)local_14c < 0x10) || ((local_14c & 0xf) != 0)) || (0xff0 < (int)local_14c))
              {
                return 0xfffffff9;
              }
              if (*(uint *)((int)local_134 + (local_14c - 4)) != uVar1) {
                return 0xfffffff8;
              }
              local_134 = (uint *)((int)local_134 + local_14c);
            } while (local_134 < puVar6);
            if (local_134 != puVar6) {
              return 0xfffffff8;
            }
            local_c = local_c + 0x400;
          }
          if (*local_1c != local_130) {
            return 0xfffffff7;
          }
          local_138 = local_1c;
          for (local_18 = 0; local_18 < 0x40; local_18 = local_18 + 1) {
            local_134 = local_138;
            for (local_16c = 0;
                (puVar6 = (uint *)local_134[1], puVar6 != local_138 &&
                (local_16c != aiStack_11c[local_18])); local_16c = local_16c + 1) {
              if ((puVar6 < local_12c) || (local_12c + 0x2000 <= puVar6)) {
                return 0xfffffff6;
              }
              puVar4 = (uint *)(((uint)puVar6 & 0xfffff000) + 0xffc);
              for (local_14 = (uint *)(((uint)puVar6 & 0xfffff000) + 0xc);
                  (local_14 != puVar4 && (local_14 != puVar6));
                  local_14 = (uint *)((int)local_14 + (*local_14 & 0xfffffffe))) {
              }
              if (local_14 == puVar4) {
                return 0xfffffff5;
              }
              local_150 = ((int)*puVar6 >> 4) + -1;
              if (0x3f < local_150) {
                local_150 = 0x3f;
              }
              if (local_150 != local_18) {
                return 0xfffffff4;
              }
              if ((uint *)puVar6[2] != local_134) {
                return 0xfffffff3;
              }
              local_134 = puVar6;
            }
            if (local_16c != 0) {
              bVar5 = (byte)local_18;
              if (local_18 < 0x20) {
                local_120 = local_120 | 0x80000000U >> (bVar5 & 0x1f);
                local_148 = local_148 | 0x80000000U >> (bVar5 & 0x1f);
              }
              else {
                local_154 = local_154 | 0x80000000U >> (bVar5 - 0x20 & 0x1f);
                local_15c = local_15c | 0x80000000U >> (bVar5 - 0x20 & 0x1f);
              }
            }
            if (((uint *)local_134[1] != local_138) || (local_16c != aiStack_11c[local_18])) {
              return 0xfffffff2;
            }
            if ((uint *)local_138[2] != local_134) {
              return 0xfffffff1;
            }
            local_138 = local_138 + 2;
          }
        }
        if ((local_120 != *(uint *)((int)lp + local_10 * 4 + 0x44)) ||
           (local_154 != *(uint *)((int)lp + local_10 * 4 + 0xc4))) {
          return 0xfffffff0;
        }
        local_12c = local_12c + 0x2000;
        local_1c = local_1c + 0x81;
        local_8 = local_8 << 1;
      }
      if ((local_148 != *local_140) || (local_15c != local_140[1])) {
        return 0xffffffef;
      }
      local_140 = local_140 + 5;
    }
    uVar3 = 0;
  }
  else {
    uVar3 = 0xffffffff;
  }
  return uVar3;
}


// 005346f8

void FUN_005346f8(void)

{
  return;
}


// 00534706

float10 FUN_00534706(void)

{
  return (float10)0;
}


// 005347d0

float10 __fastcall
FUN_005347d0(undefined4 param_1,undefined4 param_2,undefined2 param_3,undefined4 param_4,
            undefined4 param_5,undefined4 param_6,undefined4 param_7,undefined4 param_8)

{
  float10 in_ST0;
  undefined1 local_24 [8];
  undefined4 uStack_1c;
  undefined4 uStack_18;
  undefined4 local_14;
  undefined4 local_10;
  double dStack_c;
  
  local_14 = param_7;
  local_10 = param_8;
  dStack_c = (double)in_ST0;
  uStack_1c = param_5;
  uStack_18 = param_6;
  FUN_0053b0d0(param_2,local_24,&param_3);
  return (float10)dStack_c;
}


// 005347e7

/* Library Function - Single Match
    __startOneArgErrorHandling
   
   Library: Visual Studio */

float10 __fastcall
__startOneArgErrorHandling
          (undefined4 param_1,undefined4 param_2,undefined2 param_3,undefined4 param_4,
          undefined4 param_5,undefined4 param_6)

{
  float10 in_ST0;
  undefined1 local_24 [8];
  undefined4 local_1c;
  undefined4 local_18;
  double local_c;
  
  local_c = (double)in_ST0;
  local_1c = param_5;
  local_18 = param_6;
  FUN_0053b0d0(param_2,local_24,&param_3);
  return (float10)local_c;
}


// 00534845

void FUN_00534845(void)

{
  return;
}


// 0053485c

undefined4 FUN_0053485c(void)

{
  uint in_EAX;
  
  if ((in_EAX & 0x80000) != 0) {
    return 7;
  }
  return 1;
}


// 00534875

/* Library Function - Single Match
    __fload_withFB
   
   Library: Visual Studio */

uint __fastcall __fload_withFB(undefined4 param_1,int param_2)

{
  uint uVar1;
  
  uVar1 = *(uint *)(param_2 + 4) & 0x7ff00000;
  if (uVar1 != 0x7ff00000) {
    return uVar1;
  }
  return *(uint *)(param_2 + 4);
}


// 005348b8

uint FUN_005348b8(undefined4 param_1,uint param_2)

{
  if ((param_2 & 0x7ff00000) != 0x7ff00000) {
    return param_2 & 0x7ff00000;
  }
  return param_2;
}


// 005348db

/* Library Function - Single Match
    __math_exit
   
   Library: Visual Studio */

void __math_exit(void)

{
  ushort in_FPUStatusWord;
  ushort unaff_retaddr;
  
  if (((unaff_retaddr != 0x27f) && ((unaff_retaddr & 0x20) != 0)) &&
     ((in_FPUStatusWord & 0x20) != 0)) {
    __startOneArgErrorHandling();
    return;
  }
  return;
}


// 005349c0

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

float10 FUN_005349c0(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  float10 fVar1;
  
  if (DAT_0057abd0 == 0) {
    fVar1 = (float10)__umatherr(1,param_1,param_2,param_3,0,0,param_2,param_3,param_4);
  }
  else {
    _DAT_00b94050 = 0x21;
    FUN_00535900(param_4,0xffff);
    fVar1 = (float10)(double)CONCAT44(param_3,param_2);
  }
  return fVar1;
}


// 00534a20

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

float10 FUN_00534a20(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,
                    undefined4 param_5,undefined4 param_6)

{
  double dVar1;
  float10 fVar2;
  
  dVar1 = (double)CONCAT44(param_3,param_2) + (double)CONCAT44(param_5,param_4);
  if (DAT_0057abd0 == 0) {
    fVar2 = (float10)__umatherr(1,param_1,param_2,param_3,param_4,param_5,dVar1,param_6);
  }
  else {
    _DAT_00b94050 = 0x21;
    FUN_00535900(param_6,0xffff);
    fVar2 = (float10)dVar1;
  }
  return fVar2;
}


// 00534a90

float10 FUN_00534a90(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,
                    undefined4 param_5,undefined4 param_6,undefined4 param_7)

{
  int iVar1;
  float10 fVar2;
  undefined1 local_60 [56];
  uint local_28;
  int local_8;
  
  iVar1 = FUN_005350f0(param_1,&param_5,param_7);
  if (iVar1 == 0) {
    local_28 = local_28 & 0xfffffffe;
    FUN_00534c20(local_60,&param_7,param_1,param_2,&param_3,&param_5);
  }
  local_8 = FUN_00535590(param_1);
  if ((DAT_0057abd0 == 0) && (local_8 != 0)) {
    fVar2 = (float10)__umatherr(local_8,param_2,param_3,param_4,0,0,param_5,param_6,param_7);
  }
  else {
    __set_errno(local_8);
    FUN_00535900(param_7,0xffff);
    fVar2 = (float10)(double)CONCAT44(param_6,param_5);
  }
  return fVar2;
}


// 00534b50

float10 FUN_00534b50(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,
                    undefined4 param_5,undefined4 param_6,undefined4 param_7,undefined4 param_8,
                    undefined4 param_9)

{
  int iVar1;
  float10 fVar2;
  undefined1 local_60 [40];
  undefined4 local_38;
  undefined4 local_34;
  uint local_28;
  int local_8;
  
  iVar1 = FUN_005350f0(param_1,&param_7,param_9);
  if (iVar1 == 0) {
    local_28 = local_28 & 0xffffffe1 | 3;
    local_38 = param_5;
    local_34 = param_6;
    FUN_00534c20(local_60,&param_9,param_1,param_2,&param_3,&param_7);
  }
  local_8 = FUN_00535590(param_1);
  if ((DAT_0057abd0 == 0) && (local_8 != 0)) {
    fVar2 = (float10)__umatherr(local_8,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                                param_9);
  }
  else {
    __set_errno(local_8);
    FUN_00535900(param_9,0xffff);
    fVar2 = (float10)(double)CONCAT44(param_8,param_7);
  }
  return fVar2;
}


// 00534c20

void FUN_00534c20(uint *param_1,uint *param_2,uint param_3,uint param_4,uint *param_5,uint *param_6)

{
  uint uVar1;
  DWORD local_8;
  
  param_1[1] = 0;
  param_1[2] = 0;
  param_1[3] = 0;
  if ((param_3 & 0x10) != 0) {
    local_8 = 0xc000008f;
    param_1[1] = param_1[1] | 1;
  }
  if ((param_3 & 2) != 0) {
    local_8 = 0xc0000093;
    param_1[1] = param_1[1] | 2;
  }
  if ((param_3 & 1) != 0) {
    local_8 = 0xc0000091;
    param_1[1] = param_1[1] | 4;
  }
  if ((param_3 & 4) != 0) {
    local_8 = 0xc000008e;
    param_1[1] = param_1[1] | 8;
  }
  if ((param_3 & 8) != 0) {
    local_8 = 0xc0000090;
    param_1[1] = param_1[1] | 0x10;
  }
  param_1[2] = param_1[2] & 0xffffffef | (uint)((*param_2 & 1) == 0) << 4;
  param_1[2] = param_1[2] & 0xfffffff7 | (uint)((*param_2 & 4) == 0) << 3;
  param_1[2] = param_1[2] & 0xfffffffb | (uint)((*param_2 & 8) == 0) << 2;
  param_1[2] = param_1[2] & 0xfffffffd | (uint)((*param_2 & 0x10) == 0) << 1;
  param_1[2] = param_1[2] & 0xfffffffe | (uint)((*param_2 & 0x20) == 0);
  uVar1 = FUN_005358c0();
  if ((uVar1 & 1) != 0) {
    param_1[3] = param_1[3] | 0x10;
  }
  if ((uVar1 & 4) != 0) {
    param_1[3] = param_1[3] | 8;
  }
  if ((uVar1 & 8) != 0) {
    param_1[3] = param_1[3] | 4;
  }
  if ((uVar1 & 0x10) != 0) {
    param_1[3] = param_1[3] | 2;
  }
  if ((uVar1 & 0x20) != 0) {
    param_1[3] = param_1[3] | 1;
  }
  uVar1 = *param_2 & 0xc00;
  if (uVar1 < 0x801) {
    if (uVar1 == 0x800) {
      *param_1 = *param_1 & 0xfffffffc | 2;
    }
    else if (uVar1 == 0) {
      *param_1 = *param_1 & 0xfffffffc;
    }
    else if (uVar1 == 0x400) {
      *param_1 = *param_1 & 0xfffffffc | 1;
    }
  }
  else if (uVar1 == 0xc00) {
    *param_1 = *param_1 | 3;
  }
  uVar1 = *param_2 & 0x300;
  if (uVar1 == 0) {
    *param_1 = *param_1 & 0xffffffe3 | 8;
  }
  else if (uVar1 == 0x200) {
    *param_1 = *param_1 & 0xffffffe3 | 4;
  }
  else if (uVar1 == 0x300) {
    *param_1 = *param_1 & 0xffffffe3;
  }
  *param_1 = *param_1 & 0xfffe001f | (param_4 & 0xfff) << 5;
  param_1[8] = param_1[8] | 1;
  param_1[8] = param_1[8] & 0xffffffe1 | 2;
  param_1[4] = *param_5;
  param_1[5] = param_5[1];
  param_1[0x14] = param_1[0x14] | 1;
  param_1[0x14] = param_1[0x14] & 0xffffffe1 | 2;
  param_1[0x10] = *param_6;
  param_1[0x11] = param_6[1];
  FUN_005358e0();
  RaiseException(local_8,0,1,(ULONG_PTR *)&param_1);
  if ((param_1[2] >> 4 & 1) != 0) {
    *param_2 = *param_2 & 0xfffffffe;
  }
  if ((param_1[2] >> 3 & 1) != 0) {
    *param_2 = *param_2 & 0xfffffffb;
  }
  if ((param_1[2] >> 2 & 1) != 0) {
    *param_2 = *param_2 & 0xfffffff7;
  }
  if ((param_1[2] >> 1 & 1) != 0) {
    *param_2 = *param_2 & 0xffffffef;
  }
  if ((param_1[2] & 1) != 0) {
    *param_2 = *param_2 & 0xffffffdf;
  }
  switch(*param_1 & 3) {
  case 0:
    *param_2 = *param_2 & 0xfffff3ff;
    break;
  case 1:
    *param_2 = *param_2 & 0xfffff3ff | 0x400;
    break;
  case 2:
    *param_2 = *param_2 & 0xfffff3ff | 0x800;
    break;
  case 3:
    *param_2 = *param_2 & 0xfffff3ff | 0xc00;
  }
  uVar1 = *param_1 >> 2 & 7;
  if (uVar1 == 0) {
    *param_2 = *param_2 & 0xfffff3ff | 0x300;
  }
  else if (uVar1 == 1) {
    *param_2 = *param_2 & 0xfffff3ff | 0x200;
  }
  else if (uVar1 == 2) {
    *param_2 = *param_2 & 0xfffff3ff;
  }
  *param_6 = param_1[0x10];
  param_6[1] = param_1[0x11];
  return;
}


// 005350f0

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

bool FUN_005350f0(uint param_1,double *param_2,uint param_3)

{
  double dVar1;
  ulonglong uVar2;
  uint uVar3;
  float10 fVar4;
  undefined8 local_44;
  undefined8 local_3c;
  undefined8 local_34;
  undefined8 local_2c;
  int local_1c;
  int local_18;
  undefined8 local_14;
  uint local_c;
  uint local_8;
  
  local_8 = param_1 & 0x1f;
  if (((param_1 & 8) == 0) || ((param_3 & 1) == 0)) {
    if (((param_1 & 4) == 0) || ((param_3 & 4) == 0)) {
      if (((param_1 & 1) == 0) || ((param_3 & 8) == 0)) {
        if (((param_1 & 2) != 0) && ((param_3 & 0x10) != 0)) {
          local_c = (uint)((param_1 & 0x10) != 0);
          if (*param_2 == _DAT_00546090) {
            local_c = 1;
          }
          else {
            fVar4 = (float10)FUN_00535780(*(undefined4 *)param_2,*(undefined4 *)((int)param_2 + 4),
                                          &local_1c);
            dVar1 = (double)fVar4;
            local_18 = local_1c + -0x600;
            if (local_18 < -0x432) {
              local_14 = dVar1 * _DAT_00546090;
              local_c = 1;
            }
            else {
              local_14 = (double)((ulonglong)dVar1 & 0xfffffffffffff);
              local_14 = (double)((ulonglong)local_14 | 0x10000000000000);
              for (; local_18 < -0x3fd; local_18 = local_18 + 1) {
                if ((((ulonglong)local_14 & 1) != 0) && (local_c == 0)) {
                  local_c = 1;
                }
                uVar3 = (uint)local_14 >> 1;
                uVar2 = (ulonglong)local_14 & 0x100000000;
                local_14._0_4_ = uVar3;
                if (uVar2 != 0) {
                  local_14._0_4_ = uVar3 | 0x80000000;
                }
                local_14 = (double)CONCAT44(local_14._4_4_ >> 1,(uint)local_14);
              }
              if (dVar1 < _DAT_00546090) {
                local_14 = -local_14;
              }
            }
            *(uint *)param_2 = (uint)local_14;
            *(uint *)((int)param_2 + 4) = local_14._4_4_;
          }
          if (local_c != 0) {
            FUN_00535940(0x10);
          }
          local_8 = local_8 & 0xfffffffd;
        }
      }
      else {
        FUN_00535940(8);
        uVar3 = param_3 & 0xc00;
        if (uVar3 < 0x801) {
          if (uVar3 == 0x800) {
            if (*param_2 <= _DAT_00546090) {
              local_34 = -(double)CONCAT44(DAT_0057a73c,DAT_0057a738);
            }
            else {
              local_34 = (double)CONCAT44(DAT_0057a72c,DAT_0057a728);
            }
            *(undefined4 *)param_2 = (undefined4)local_34;
            *(undefined4 *)((int)param_2 + 4) = local_34._4_4_;
          }
          else if (uVar3 == 0) {
            if (*param_2 <= _DAT_00546090) {
              local_2c = -(double)CONCAT44(DAT_0057a72c,DAT_0057a728);
            }
            else {
              local_2c = (double)CONCAT44(DAT_0057a72c,DAT_0057a728);
            }
            *(undefined4 *)param_2 = (undefined4)local_2c;
            *(undefined4 *)((int)param_2 + 4) = local_2c._4_4_;
          }
          else if (uVar3 == 0x400) {
            if (*param_2 <= _DAT_00546090) {
              local_3c = -(double)CONCAT44(DAT_0057a72c,DAT_0057a728);
            }
            else {
              local_3c = (double)CONCAT44(DAT_0057a73c,DAT_0057a738);
            }
            *(undefined4 *)param_2 = (undefined4)local_3c;
            *(undefined4 *)((int)param_2 + 4) = local_3c._4_4_;
          }
        }
        else if (uVar3 == 0xc00) {
          if (*param_2 <= _DAT_00546090) {
            local_44 = -(double)CONCAT44(DAT_0057a73c,DAT_0057a738);
          }
          else {
            local_44 = (double)CONCAT44(DAT_0057a73c,DAT_0057a738);
          }
          *(undefined4 *)param_2 = (undefined4)local_44;
          *(undefined4 *)((int)param_2 + 4) = local_44._4_4_;
        }
        local_8 = local_8 & 0xfffffffe;
      }
    }
    else {
      FUN_00535940(4);
      local_8 = local_8 & 0xfffffffb;
    }
  }
  else {
    FUN_00535940(1);
    local_8 = local_8 & 0xfffffff7;
  }
  if (((param_1 & 0x10) != 0) && ((param_3 & 0x20) != 0)) {
    FUN_00535940(0x20);
    local_8 = local_8 & 0xffffffef;
  }
  return local_8 == 0;
}


// 00535470

/* Library Function - Single Match
    __umatherr
   
   Libraries: Visual Studio 2003 Debug, Visual Studio 2003 Release */

float10 __umatherr(int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,
                  undefined4 param_5,undefined4 param_6,undefined4 param_7,undefined4 param_8,
                  undefined4 param_9)

{
  double dVar1;
  int iVar2;
  _exception local_24;
  
  local_24.name = (char *)__get_fname(param_2);
  if (local_24.name == (char *)0x0) {
    FUN_00535900(param_9,0xffff);
    __set_errno(param_1);
    dVar1 = (double)CONCAT44(param_8,param_7);
  }
  else {
    local_24.type = param_1;
    local_24.arg1._0_4_ = param_3;
    local_24.arg1._4_4_ = param_4;
    local_24.arg2._0_4_ = param_5;
    local_24.arg2._4_4_ = param_6;
    local_24.retval._0_4_ = param_7;
    local_24.retval._4_4_ = param_8;
    FUN_00535900(param_9,0xffff);
    iVar2 = __matherr(&local_24);
    if (iVar2 == 0) {
      __set_errno(param_1);
    }
    dVar1 = (double)CONCAT44(local_24.retval._4_4_,local_24.retval._0_4_);
  }
  return (float10)dVar1;
}


// 00535510

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* Library Function - Single Match
    __set_errno
   
   Libraries: Visual Studio 2003 Debug, Visual Studio 2003 Release */

errno_t __cdecl __set_errno(int _Value)

{
  if (_Value == 1) {
    _DAT_00b94050 = 0x21;
  }
  else if ((1 < _Value) && (_Value < 4)) {
    _DAT_00b94050 = 0x22;
  }
  return _Value;
}


// 00535550

/* Library Function - Single Match
    __get_fname
   
   Library: Visual Studio */

undefined * __get_fname(int param_1)

{
  int local_8;
  
  local_8 = 0;
  while( true ) {
    if (0x1a < local_8) {
      return (undefined *)0x0;
    }
    if (*(int *)(&DAT_0057a650 + local_8 * 8) == param_1) break;
    local_8 = local_8 + 1;
  }
  return (&PTR_DAT_0057a654)[local_8 * 2];
}


// 00535590

undefined4 FUN_00535590(uint param_1)

{
  undefined4 local_8;
  
  if ((param_1 & 0x20) == 0) {
    if ((param_1 & 8) == 0) {
      if ((param_1 & 4) == 0) {
        if ((param_1 & 1) == 0) {
          if ((param_1 & 2) == 0) {
            local_8 = 0;
          }
          else {
            local_8 = 4;
          }
        }
        else {
          local_8 = 3;
        }
      }
      else {
        local_8 = 2;
      }
    }
    else {
      local_8 = 1;
    }
  }
  else {
    local_8 = 5;
  }
  return local_8;
}


// 00535610

float10 FUN_00535610(undefined4 param_1,undefined4 param_2,short param_3)

{
  return (float10)(double)CONCAT26(param_2._2_2_ & 0x800f | (param_3 + 0x3fe) * 0x10,
                                   CONCAT24((undefined2)param_2,param_1));
}


// 00535650

int FUN_00535650(undefined4 param_1,undefined8 param_2)

{
  short local_8;
  
  local_8 = (short)((int)(param_2._2_4_ & 0x7ff0) >> 4);
  return (int)(short)(local_8 + -0x3fe);
}


// 00535680

void FUN_00535680(undefined4 param_1,uint param_2,int param_3)

{
  FUN_00535610(param_1,param_2,(short)((int)(param_2 >> 0x10 & 0x7ff0) >> 4) + -0x3fe + param_3);
  return;
}


// 005356c0

float10 FUN_005356c0(undefined4 param_1,undefined4 param_2,short param_3)

{
  return (float10)(double)CONCAT26(param_2._2_2_ & 0x800f | param_3 << 4,
                                   CONCAT24((undefined2)param_2,param_1));
}


// 00535700

undefined4 FUN_00535700(int param_1,uint param_2)

{
  undefined4 uVar1;
  
  if ((param_2 == 0x7ff00000) && (param_1 == 0)) {
    uVar1 = 1;
  }
  else if ((param_2 == 0xfff00000) && (param_1 == 0)) {
    uVar1 = 2;
  }
  else if ((param_2._2_2_ & 0x7ff8) == 0x7ff8) {
    uVar1 = 3;
  }
  else if (((param_2._2_2_ & 0x7ff8) == 0x7ff0) && (((param_2 & 0x7ffff) != 0 || (param_1 != 0)))) {
    uVar1 = 4;
  }
  else {
    uVar1 = 0;
  }
  return uVar1;
}


// 00535780

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

float10 FUN_00535780(uint param_1,uint param_2,int *param_3)

{
  double dVar1;
  int iVar2;
  float10 fVar3;
  double local_10;
  int local_8;
  
  if ((double)CONCAT26(param_2._2_2_,CONCAT24((ushort)param_2,param_1)) == _DAT_00546090) {
    local_10 = 0.0;
    local_8 = 0;
  }
  else if (((param_2 & 0x7ff00000) == 0) && (((param_2 & 0xfffff) != 0 || (param_1 != 0)))) {
    local_8 = -0x3fd;
    dVar1 = (double)CONCAT26(param_2._2_2_,CONCAT24((ushort)param_2,param_1));
    while ((param_2._2_2_ & 0x10) == 0) {
      iVar2 = CONCAT22(param_2._2_2_,(ushort)param_2) << 1;
      param_2._0_2_ = (ushort)iVar2;
      param_2._2_2_ = (ushort)((uint)iVar2 >> 0x10);
      if ((param_1 & 0x80000000) != 0) {
        param_2._0_2_ = (ushort)param_2 | 1;
      }
      param_1 = param_1 << 1;
      local_8 = local_8 + -1;
    }
    param_2._2_2_ = param_2._2_2_ & 0xffef;
    if (dVar1 < _DAT_00546090) {
      param_2._2_2_ = param_2._2_2_ | 0x8000;
    }
    fVar3 = (float10)FUN_00535610(param_1,CONCAT22(param_2._2_2_,(ushort)param_2),0);
    local_10 = (double)fVar3;
  }
  else {
    fVar3 = (float10)FUN_00535610(param_1,param_2,0);
    local_10 = (double)fVar3;
    local_8 = (short)((int)(param_2._2_2_ & 0x7ff0) >> 4) + -0x3fe;
  }
  *param_3 = local_8;
  return (float10)local_10;
}


// 005358c0

int FUN_005358c0(void)

{
  short in_FPUStatusWord;
  
  return (int)in_FPUStatusWord;
}


// 005358e0

int FUN_005358e0(void)

{
  short in_FPUStatusWord;
  
  return (int)in_FPUStatusWord;
}


// 00535900

int FUN_00535900(void)

{
  short in_FPUControlWord;
  
  return (int)in_FPUControlWord;
}


// 00535940

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_00535940(void)

{
  return;
}


// 005359c0

int FUN_005359c0(int param_1,byte *param_2,undefined4 *param_3)

{
  byte bVar1;
  code *pcVar2;
  byte bVar3;
  int iVar4;
  undefined4 uVar5;
  uint uVar6;
  byte *pbVar7;
  bool bVar8;
  longlong lVar9;
  uint local_228;
  uint uStack_224;
  uint uStack_220;
  uint uStack_21c;
  uint uStack_218;
  uint uStack_214;
  uint uStack_210;
  uint uStack_20c;
  uint local_200;
  uint local_1fc;
  byte bStack_1f4;
  undefined1 uStack_1f3;
  uint uStack_1f0;
  int local_1ec;
  uint *puStack_1e8;
  byte *pbStack_1e4;
  int local_1e0;
  uint local_1dc;
  undefined4 *local_1d8;
  byte bStack_1d4;
  byte abStack_1d3 [351];
  char local_74;
  int local_70;
  char local_6c;
  char local_68;
  byte abStack_64 [11];
  undefined1 uStack_59;
  uint local_44;
  uint *local_40;
  char local_3c;
  uint local_38;
  undefined8 uStack_34;
  char local_2c;
  uint uStack_28;
  uint local_24;
  int local_20;
  char local_1c;
  char local_18;
  byte local_14;
  uint local_10;
  uint local_c;
  undefined2 auStack_8 [2];
  
  if ((param_2 == (byte *)0x0) &&
     (iVar4 = FUN_0052fad0(2,"input.c",0x109,0,"format != NULL"), iVar4 == 1)) {
    pcVar2 = (code *)swi(3);
    iVar4 = (*pcVar2)();
    return iVar4;
  }
  if ((param_1 == 0) && (iVar4 = FUN_0052fad0(2,"input.c",0x10c,0,"stream != NULL"), iVar4 == 1)) {
    pcVar2 = (code *)swi(3);
    iVar4 = (*pcVar2)();
    return iVar4;
  }
  local_2c = '\0';
  local_38 = 0;
  local_24 = local_38;
  do {
    if (*param_2 == 0) {
LAB_00536caa:
      if ((local_1dc == 0xffffffff) && ((local_38 == 0 && (local_2c == '\0')))) {
        local_228 = 0xffffffff;
        local_38 = local_228;
      }
      return local_38;
    }
    if (DAT_0057a5fc < 2) {
      local_1fc = *(ushort *)(PTR_DAT_0057a3f0 + (uint)*param_2 * 2) & 8;
    }
    else {
      local_1fc = FUN_00532300(*param_2,8);
    }
    if (local_1fc != 0) {
      local_24 = local_24 - 1;
      uVar5 = __whiteout(&local_24,param_1,param_1);
      FUN_00536e60(uVar5);
      do {
        param_2 = param_2 + 1;
        iVar4 = FUN_0053b520(*param_2);
      } while (iVar4 != 0);
    }
    if (*param_2 == 0x25) {
      local_44 = 0;
      local_c = local_c & 0xffffff00;
      local_70 = 0;
      local_1ec = 0;
      local_20 = 0;
      local_14 = 0;
      local_6c = '\0';
      local_74 = '\0';
      local_1c = '\0';
      local_68 = '\0';
      local_18 = '\0';
      local_3c = '\x01';
      local_1e0 = 0;
LAB_00535b35:
      if (local_1c == '\0') {
        pbVar7 = param_2 + 1;
        local_10 = (uint)*pbVar7;
        if (DAT_0057a5fc < 2) {
          local_200 = *(ushort *)(PTR_DAT_0057a3f0 + local_10 * 2) & 4;
        }
        else {
          local_200 = FUN_00532300(local_10,4);
        }
        if (local_200 == 0) {
          switch(local_10) {
          case 0x2a:
            local_74 = local_74 + '\x01';
            param_2 = pbVar7;
            break;
          case 0x46:
          case 0x4e:
            param_2 = pbVar7;
            break;
          case 0x49:
            if ((param_2[2] == 0x36) && (param_2[3] == 0x34)) {
              local_1e0 = local_1e0 + 1;
              uStack_34 = 0;
              param_2 = param_2 + 3;
              break;
            }
          default:
            local_1c = local_1c + '\x01';
            param_2 = pbVar7;
            break;
          case 0x4c:
            local_3c = local_3c + '\x01';
            param_2 = pbVar7;
            break;
          case 0x68:
            local_3c = local_3c + -1;
            local_18 = local_18 + -1;
            param_2 = pbVar7;
            break;
          case 0x6c:
            local_3c = local_3c + '\x01';
          case 0x77:
            local_18 = local_18 + '\x01';
            param_2 = pbVar7;
          }
        }
        else {
          local_1ec = local_1ec + 1;
          local_20 = (local_10 - 0x30) + local_20 * 10;
          param_2 = pbVar7;
        }
        goto LAB_00535b35;
      }
      if (local_74 == '\0') {
        local_1d8 = param_3;
        local_40 = (uint *)*param_3;
        param_3 = param_3 + 1;
      }
      local_1c = '\0';
      if (local_18 == '\0') {
        if ((*param_2 == 0x53) || (*param_2 == 0x43)) {
          local_18 = '\x01';
        }
        else {
          local_18 = -1;
        }
      }
      local_10 = *param_2 | 0x20;
      lVar9 = uStack_34;
      if (local_10 != 0x6e) {
        if ((local_10 == 99) || (local_10 == 0x7b)) {
          local_24 = local_24 + 1;
          local_1dc = __inc(param_1);
          lVar9 = uStack_34;
        }
        else {
          local_1dc = __whiteout(&local_24,param_1);
          lVar9 = uStack_34;
        }
      }
      uStack_34 = lVar9;
      if ((local_1ec != 0) && (local_20 == 0)) {
        local_24 = local_24 - 1;
        FUN_00536e60(local_1dc,param_1);
        goto LAB_00536caa;
      }
      pbVar7 = param_2;
      switch(local_10) {
      case 99:
        if (local_1ec == 0) {
          local_1ec = 1;
          local_20 = local_20 + 1;
        }
        if ('\0' < local_18) {
          local_68 = local_68 + '\x01';
        }
        pbStack_1e4 = (byte *)0x57a770;
        local_14 = local_14 - 1;
        goto code_r0x00535e40;
      case 100:
      case 0x6f:
      case 0x75:
        goto code_r0x005362c4;
      case 0x65:
      case 0x66:
      case 0x67:
        pbStack_1e4 = &bStack_1d4;
        if (local_1dc == 0x2d) {
          bStack_1d4 = 0x2d;
          pbStack_1e4 = abStack_1d3;
code_r0x0053676f:
          local_20 = local_20 + -1;
          local_24 = local_24 + 1;
          local_1dc = __inc(param_1);
          lVar9 = uStack_34;
        }
        else if (local_1dc == 0x2b) goto code_r0x0053676f;
        uStack_34 = lVar9;
        if ((local_1ec == 0) || (0x15d < local_20)) {
          local_20 = 0x15d;
        }
        while( true ) {
          if (DAT_0057a5fc < 2) {
            uStack_21c = *(ushort *)(PTR_DAT_0057a3f0 + local_1dc * 2) & 4;
          }
          else {
            uStack_21c = FUN_00532300(local_1dc,4);
          }
          if ((uStack_21c == 0) ||
             (iVar4 = local_20 + -1, bVar8 = local_20 == 0, local_20 = iVar4, bVar8)) break;
          local_70 = local_70 + 1;
          *pbStack_1e4 = (byte)local_1dc;
          pbStack_1e4 = pbStack_1e4 + 1;
          local_24 = local_24 + 1;
          local_1dc = __inc(param_1);
        }
        if ((DAT_0057a600 == (byte)local_1dc) &&
           (iVar4 = local_20 + -1, bVar8 = local_20 != 0, local_20 = iVar4, bVar8)) {
          local_24 = local_24 + 1;
          local_1dc = __inc(param_1);
          *pbStack_1e4 = DAT_0057a600;
          pbStack_1e4 = pbStack_1e4 + 1;
          while( true ) {
            if (DAT_0057a5fc < 2) {
              uStack_220 = *(ushort *)(PTR_DAT_0057a3f0 + local_1dc * 2) & 4;
            }
            else {
              uStack_220 = FUN_00532300(local_1dc,4);
            }
            if ((uStack_220 == 0) ||
               (iVar4 = local_20 + -1, bVar8 = local_20 == 0, local_20 = iVar4, bVar8)) break;
            local_70 = local_70 + 1;
            *pbStack_1e4 = (byte)local_1dc;
            pbStack_1e4 = pbStack_1e4 + 1;
            local_24 = local_24 + 1;
            local_1dc = __inc(param_1);
          }
        }
        if ((local_70 != 0) &&
           (((local_1dc == 0x65 || (local_1dc == 0x45)) &&
            (iVar4 = local_20 + -1, bVar8 = local_20 != 0, local_20 = iVar4, bVar8)))) {
          *pbStack_1e4 = 0x65;
          pbStack_1e4 = pbStack_1e4 + 1;
          local_24 = local_24 + 1;
          local_1dc = __inc(param_1);
          if (local_1dc == 0x2d) {
            *pbStack_1e4 = 0x2d;
            pbStack_1e4 = pbStack_1e4 + 1;
code_r0x005369d7:
            if (local_20 != 0) {
              local_24 = local_24 + 1;
              local_20 = local_20 + -1;
              local_1dc = __inc(param_1);
            }
          }
          else if (local_1dc == 0x2b) goto code_r0x005369d7;
          while( true ) {
            if (DAT_0057a5fc < 2) {
              uStack_224 = *(ushort *)(PTR_DAT_0057a3f0 + local_1dc * 2) & 4;
            }
            else {
              uStack_224 = FUN_00532300(local_1dc,4);
            }
            if ((uStack_224 == 0) ||
               (iVar4 = local_20 + -1, bVar8 = local_20 == 0, local_20 = iVar4, bVar8)) break;
            local_70 = local_70 + 1;
            *pbStack_1e4 = (byte)local_1dc;
            pbStack_1e4 = pbStack_1e4 + 1;
            local_24 = local_24 + 1;
            local_1dc = __inc(param_1);
          }
        }
        local_24 = local_24 - 1;
        FUN_00536e60(local_1dc,param_1);
        if (local_70 == 0) goto LAB_00536caa;
        lVar9 = uStack_34;
        if (local_74 == '\0') {
          local_38 = local_38 + 1;
          *pbStack_1e4 = 0;
          (*(code *)PTR___fptrap_0057a270)(local_3c + -1,local_40,&bStack_1d4);
          lVar9 = uStack_34;
        }
        break;
      default:
        if (*param_2 != local_1dc) {
          local_24 = local_24 - 1;
          FUN_00536e60(local_1dc,param_1);
          goto LAB_00536caa;
        }
        local_2c = local_2c + -1;
        if (local_74 == '\0') {
          param_3 = local_1d8;
        }
        break;
      case 0x69:
        local_10 = 100;
      case 0x78:
        if (local_1dc == 0x2d) {
          local_6c = local_6c + '\x01';
code_r0x005361df:
          local_20 = local_20 + -1;
          if ((local_20 == 0) && (local_1ec != 0)) {
            local_1c = local_1c + '\x01';
          }
          else {
            local_24 = local_24 + 1;
            local_1dc = __inc(param_1);
            lVar9 = uStack_34;
          }
        }
        else if (local_1dc == 0x2b) goto code_r0x005361df;
        uStack_34 = lVar9;
        if (local_1dc == 0x30) {
          local_24 = local_24 + 1;
          local_1dc = __inc(param_1);
          if (((byte)local_1dc == 'x') || ((byte)local_1dc == 'X')) {
            local_24 = local_24 + 1;
            local_1dc = __inc(param_1);
            local_10 = 0x78;
          }
          else {
            local_70 = local_70 + 1;
            if (local_10 == 0x78) {
              local_24 = local_24 - 1;
              FUN_00536e60(local_1dc,param_1);
              local_1dc = 0x30;
            }
            else {
              local_10 = 0x6f;
            }
          }
        }
        goto code_r0x0053631e;
      case 0x6e:
        local_44 = local_24;
        if (local_74 != '\0') break;
        goto code_r0x005366e1;
      case 0x70:
        local_3c = '\x01';
code_r0x005362c4:
        if (local_1dc == 0x2d) {
          local_6c = local_6c + '\x01';
code_r0x005362e1:
          local_20 = local_20 + -1;
          if ((local_20 == 0) && (local_1ec != 0)) {
            local_1c = local_1c + '\x01';
          }
          else {
            local_24 = local_24 + 1;
            local_1dc = __inc(param_1);
          }
        }
        else if (local_1dc == 0x2b) goto code_r0x005362e1;
code_r0x0053631e:
        lVar9 = uStack_34;
        if (local_1e0 == 0) {
          while (local_1c == '\0') {
            uStack_34 = lVar9;
            if ((local_10 == 0x78) || (local_10 == 0x70)) {
              if (DAT_0057a5fc < 2) {
                uStack_214 = *(ushort *)(PTR_DAT_0057a3f0 + local_1dc * 2) & 0x80;
              }
              else {
                uStack_214 = FUN_00532300(local_1dc,0x80);
                lVar9 = uStack_34;
              }
              if (uStack_214 == 0) {
                local_1c = local_1c + '\x01';
              }
              else {
                local_44 = local_44 << 4;
                uStack_34 = lVar9;
                local_1dc = FUN_00536da0(local_1dc);
                lVar9 = uStack_34;
              }
            }
            else {
              if (DAT_0057a5fc < 2) {
                uStack_218 = *(ushort *)(PTR_DAT_0057a3f0 + local_1dc * 2) & 4;
              }
              else {
                uStack_218 = FUN_00532300(local_1dc,4);
                lVar9 = uStack_34;
              }
              if (uStack_218 == 0) {
                local_1c = local_1c + '\x01';
              }
              else if (local_10 == 0x6f) {
                if ((int)local_1dc < 0x38) {
                  local_44 = local_44 << 3;
                }
                else {
                  local_1c = local_1c + '\x01';
                }
              }
              else {
                local_44 = local_44 * 10;
              }
            }
            uStack_34 = lVar9;
            if (local_1c == '\0') {
              local_70 = local_70 + 1;
              local_44 = (local_44 - 0x30) + local_1dc;
              if ((local_1ec == 0) || (local_20 = local_20 + -1, local_20 != 0)) {
                local_24 = local_24 + 1;
                local_1dc = __inc(param_1);
                lVar9 = uStack_34;
              }
              else {
                local_1c = '\x01';
              }
            }
            else {
              local_24 = local_24 - 1;
              FUN_00536e60(local_1dc,param_1);
              lVar9 = uStack_34;
            }
          }
          if (local_6c != '\0') {
            local_44 = -local_44;
          }
        }
        else {
          while( true ) {
            uStack_34._4_4_ = (int)((ulonglong)lVar9 >> 0x20);
            uStack_34._0_4_ = (int)lVar9;
            if (local_1c != '\0') break;
            uStack_34 = lVar9;
            if (local_10 == 0x78) {
              if (DAT_0057a5fc < 2) {
                uStack_20c = *(ushort *)(PTR_DAT_0057a3f0 + local_1dc * 2) & 0x80;
              }
              else {
                uStack_20c = FUN_00532300(local_1dc,0x80);
              }
              if (uStack_20c == 0) {
                local_1c = local_1c + '\x01';
              }
              else {
                lVar9 = func_0x0053b7b0();
                uStack_34 = lVar9;
                local_1dc = FUN_00536da0(local_1dc);
              }
            }
            else {
              if (DAT_0057a5fc < 2) {
                uStack_210 = *(ushort *)(PTR_DAT_0057a3f0 + local_1dc * 2) & 4;
              }
              else {
                uStack_210 = FUN_00532300(local_1dc,4);
              }
              if (uStack_210 == 0) {
                local_1c = local_1c + '\x01';
              }
              else if (local_10 == 0x6f) {
                if ((int)local_1dc < 0x38) {
                  lVar9 = func_0x0053b7b0();
                  uStack_34 = lVar9;
                }
                else {
                  local_1c = local_1c + '\x01';
                }
              }
              else {
                func_0x0053b7b0();
                lVar9 = func_0x0053b7b0();
                uStack_34 = lVar9;
              }
            }
            if (local_1c == '\0') {
              local_70 = local_70 + 1;
              if ((local_1ec == 0) || (local_20 = local_20 + -1, local_20 != 0)) {
                local_24 = local_24 + 1;
                uStack_34 = uStack_34 + (int)(local_1dc - 0x30);
                local_1dc = __inc(param_1);
                lVar9 = uStack_34;
              }
              else {
                local_1c = '\x01';
                lVar9 = uStack_34 + (int)(local_1dc - 0x30);
              }
            }
            else {
              local_24 = local_24 - 1;
              FUN_00536e60(local_1dc,param_1);
              lVar9 = uStack_34;
            }
          }
          if (local_6c != '\0') {
            lVar9 = CONCAT44(-(uStack_34._4_4_ + (uint)((int)uStack_34 != 0)),-(int)uStack_34);
          }
        }
        if (local_10 == 0x46) {
          local_70 = 0;
        }
        if (local_70 == 0) goto LAB_00536caa;
        if (local_74 == '\0') {
          local_38 = local_38 + 1;
code_r0x005366e1:
          if (local_1e0 == 0) {
            if (local_3c == '\0') {
              *(undefined2 *)local_40 = (undefined2)local_44;
            }
            else {
              *local_40 = local_44;
            }
          }
          else {
            *(longlong *)local_40 = lVar9;
          }
        }
        break;
      case 0x73:
        if ('\0' < local_18) {
          local_68 = local_68 + '\x01';
        }
        pbStack_1e4 = (byte *)0x57a768;
        local_14 = local_14 - 1;
        goto code_r0x00535e40;
      case 0x7b:
        if ('\0' < local_18) {
          local_68 = local_68 + '\x01';
        }
        pbVar7 = param_2 + 1;
        pbStack_1e4 = pbVar7;
        if (*pbVar7 == 0x5e) {
          pbStack_1e4 = param_2 + 2;
          local_14 = local_14 - 1;
        }
code_r0x00535e40:
        param_2 = pbVar7;
        _memset(abStack_64,0,0x20);
        if ((local_10 == 0x7b) && (*pbStack_1e4 == 0x5d)) {
          local_c = CONCAT31(local_c._1_3_,0x5d);
          uStack_59 = 0x20;
          pbStack_1e4 = pbStack_1e4 + 1;
        }
        while (*pbStack_1e4 != 0x5d) {
          bVar1 = *pbStack_1e4;
          uStack_1f0 = CONCAT31(uStack_1f0._1_3_,bVar1);
          pbVar7 = pbStack_1e4 + 1;
          if (((bVar1 == 0x2d) && ((local_c & 0xff) != 0)) && (*pbVar7 != 0x5d)) {
            bVar1 = *pbVar7;
            pbStack_1e4 = pbStack_1e4 + 2;
            if ((uint)bVar1 <= (local_c & 0xff)) {
              bVar3 = (byte)local_c;
              local_c = CONCAT31(local_c._1_3_,bVar1);
              bVar1 = bVar3;
            }
            uStack_28 = CONCAT31(uStack_28._1_3_,bVar1);
            for (uStack_1f0 = CONCAT31(uStack_1f0._1_3_,(byte)local_c);
                (uStack_1f0 & 0xff) <= (uStack_28 & 0xff);
                uStack_1f0 = CONCAT31(uStack_1f0._1_3_,(byte)uStack_1f0 + 1)) {
              abStack_64[(int)(uStack_1f0 & 0xff) >> 3] =
                   abStack_64[(int)(uStack_1f0 & 0xff) >> 3] | (byte)(1 << ((byte)uStack_1f0 & 7));
            }
            local_c = local_c & 0xffffff00;
          }
          else {
            local_c = CONCAT31(local_c._1_3_,bVar1);
            abStack_64[(int)(uint)bVar1 >> 3] =
                 abStack_64[(int)(uint)bVar1 >> 3] | (byte)(1 << (bVar1 & 7));
            pbStack_1e4 = pbVar7;
          }
        }
        if (*pbStack_1e4 == 0) goto LAB_00536caa;
        if (local_10 == 0x7b) {
          param_2 = pbStack_1e4;
        }
        puStack_1e8 = local_40;
        local_24 = local_24 - 1;
        FUN_00536e60(local_1dc,param_1);
        while( true ) {
          if ((local_1ec != 0) &&
             (iVar4 = local_20 + -1, bVar8 = local_20 == 0, local_20 = iVar4, lVar9 = uStack_34,
             bVar8)) goto code_r0x00536175;
          local_24 = local_24 + 1;
          local_1dc = __inc(param_1);
          if ((local_1dc == 0xffffffff) ||
             (bVar1 = (byte)local_1dc,
             ((int)(char)(abStack_64[(int)local_1dc >> 3] ^ local_14) & 1 << (bVar1 & 7)) == 0))
          break;
          if (local_74 == '\0') {
            if (local_68 == '\0') {
              *(byte *)local_40 = bVar1;
              local_40 = (uint *)((int)local_40 + 1);
            }
            else {
              bStack_1f4 = bVar1;
              if ((*(ushort *)(PTR_DAT_0057a3f0 + (local_1dc & 0xff) * 2) & 0x8000) != 0) {
                local_24 = local_24 + 1;
                uStack_1f3 = __inc(param_1);
              }
              FUN_0053b260(auStack_8,&bStack_1f4,DAT_0057a5fc);
              *(undefined2 *)local_40 = auStack_8[0];
              local_40 = (uint *)((int)local_40 + 2);
            }
          }
          else {
            puStack_1e8 = (uint *)((int)puStack_1e8 + 1);
          }
        }
        local_24 = local_24 - 1;
        FUN_00536e60(local_1dc,param_1);
        lVar9 = uStack_34;
code_r0x00536175:
        if (puStack_1e8 == local_40) goto LAB_00536caa;
        if ((local_74 == '\0') && (local_38 = local_38 + 1, local_10 != 99)) {
          if (local_68 == '\0') {
            *(byte *)local_40 = 0;
          }
          else {
            *(undefined2 *)local_40 = 0;
          }
        }
      }
      local_2c = local_2c + '\x01';
      pbVar7 = param_2 + 1;
      uStack_34 = lVar9;
    }
    else {
      local_24 = local_24 + 1;
      bVar1 = *param_2;
      local_1dc = __inc(param_1);
      if (bVar1 != local_1dc) {
        local_24 = local_24 - 1;
        FUN_00536e60(local_1dc,param_1);
        goto LAB_00536caa;
      }
      pbVar7 = param_2 + 1;
      if ((*(ushort *)(PTR_DAT_0057a3f0 + (local_1dc & 0xff) * 2) & 0x8000) != 0) {
        local_24 = local_24 + 1;
        bVar1 = param_2[1];
        uVar6 = __inc(param_1);
        if (bVar1 == uVar6) {
          local_24 = local_24 - 1;
          pbVar7 = param_2 + 2;
          goto LAB_00536c81;
        }
        local_24 = local_24 - 1;
        FUN_00536e60(uVar6,param_1);
        local_24 = local_24 - 1;
        FUN_00536e60(local_1dc,param_1);
        goto LAB_00536caa;
      }
    }
LAB_00536c81:
    param_2 = pbVar7;
    if ((local_1dc == 0xffffffff) && ((*param_2 != 0x25 || (param_2[1] != 0x6e))))
    goto LAB_00536caa;
  } while( true );
}


// 00536da0

uint FUN_00536da0(uint param_1)

{
  uint local_c;
  uint local_8;
  
  if (DAT_0057a5fc < 2) {
    local_8 = *(ushort *)(PTR_DAT_0057a3f0 + param_1 * 2) & 4;
  }
  else {
    local_8 = FUN_00532300(param_1,4);
  }
  if (local_8 == 0) {
    local_c = (param_1 & 0xffffffdf) - 7;
  }
  else {
    local_c = param_1;
  }
  return local_c;
}


// 00536e00

/* Library Function - Single Match
    __inc
   
   Library: Visual Studio 2003 Debug */

uint __thiscall __inc(undefined4 param_1,int *param_2)

{
  uint uVar1;
  
  param_2[1] = param_2[1] + -1;
  if (param_2[1] < 0) {
    uVar1 = FUN_00530510(param_2,param_1);
  }
  else {
    uVar1 = (uint)*(byte *)*param_2;
    *param_2 = *param_2 + 1;
  }
  return uVar1;
}


// 00536e60

void FUN_00536e60(int param_1,undefined4 param_2)

{
  if (param_1 != -1) {
    FUN_0053b7d0(param_1,param_2);
  }
  return;
}


// 00536e80

/* Library Function - Single Match
    __whiteout
   
   Library: Visual Studio 2003 Debug */

undefined4 __thiscall __whiteout(undefined4 param_1,int *param_2,undefined4 param_3)

{
  int iVar1;
  
  do {
    *param_2 = *param_2 + 1;
    param_1 = __inc(param_3,param_1);
    iVar1 = FUN_0053b520(param_1);
  } while (iVar1 != 0);
  return param_1;
}


// 00536ec0

undefined4 FUN_00536ec0(undefined4 *param_1)

{
  code *pcVar1;
  int iVar2;
  undefined4 uVar3;
  int local_c;
  
  if ((param_1 == (undefined4 *)0x0) &&
     (iVar2 = FUN_0052fad0(2,"_sftbuf.c",0x41,0,"str != NULL"), iVar2 == 1)) {
    pcVar1 = (code *)swi(3);
    uVar3 = (*pcVar1)();
    return uVar3;
  }
  iVar2 = __isatty(param_1[4]);
  if (iVar2 == 0) {
    return 0;
  }
  if (param_1 == (undefined4 *)&DAT_0057a938) {
    local_c = 0;
  }
  else {
    if (param_1 != (undefined4 *)&DAT_0057a958) {
      return 0;
    }
    local_c = 1;
  }
  DAT_00b94204 = DAT_00b94204 + 1;
  if ((param_1[3] & 0x10c) != 0) {
    return 0;
  }
  if (*(int *)(&DAT_00b940ec + local_c * 4) == 0) {
    uVar3 = FUN_0052c150(0x1000,2,"_sftbuf.c",0x5e);
    *(undefined4 *)(&DAT_00b940ec + local_c * 4) = uVar3;
    if (*(int *)(&DAT_00b940ec + local_c * 4) == 0) {
      param_1[2] = param_1 + 5;
      *param_1 = param_1[2];
      param_1[6] = 2;
      param_1[1] = 2;
      goto LAB_00536ff9;
    }
  }
  param_1[2] = *(undefined4 *)(&DAT_00b940ec + local_c * 4);
  *param_1 = param_1[2];
  param_1[6] = 0x1000;
  param_1[1] = 0x1000;
LAB_00536ff9:
  param_1[3] = param_1[3] | 0x1102;
  return 1;
}


// 00537020

void FUN_00537020(int param_1,undefined4 *param_2)

{
  code *pcVar1;
  int iVar2;
  
  if (((param_1 != 0) && (param_1 != 1)) &&
     (iVar2 = FUN_0052fad0(2,"_sftbuf.c",0xa1,0,"flag == 0 || flag == 1"), iVar2 == 1)) {
    pcVar1 = (code *)swi(3);
    (*pcVar1)();
    return;
  }
  if (param_1 == 0) {
    if ((param_2[3] & 0x1000) != 0) {
      FUN_00530360(param_2);
    }
  }
  else if ((param_2[3] & 0x1000) != 0) {
    FUN_00530360(param_2);
    param_2[3] = param_2[3] & 0xffffeeff;
    param_2[6] = 0;
    *param_2 = 0;
    param_2[2] = 0;
  }
  return;
}


// 0053723e

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined5 __fastcall FUN_0053723e(undefined4 param_1,undefined1 param_2)

{
  undefined4 uVar1;
  undefined4 in_EAX;
  undefined1 extraout_DL;
  int unaff_EBP;
  float10 in_ST0;
  float10 fVar2;
  float10 fVar3;
  undefined4 unaff_retaddr;
  
  fVar2 = ABS(in_ST0);
  *(ushort *)(unaff_EBP + -0xa0) =
       (ushort)(_DAT_0057a79e < fVar2) << 8 | (ushort)(NAN(_DAT_0057a79e) || NAN(fVar2)) << 10 |
       (ushort)(_DAT_0057a79e == fVar2) << 0xe;
  if ((*(byte *)(unaff_EBP + -0x9f) & 0x41) == 0) {
    fVar3 = ROUND(in_ST0);
    fVar2 = (float10)0;
    *(ushort *)(unaff_EBP + -0xa0) =
         (ushort)(fVar3 < fVar2) << 8 | (ushort)(NAN(fVar3) || NAN(fVar2)) << 10 |
         (ushort)(fVar3 == fVar2) << 0xe;
    fVar3 = in_ST0 - fVar3;
    fVar2 = (float10)0;
    *(ushort *)(unaff_EBP + -0xa0) =
         (ushort)(fVar3 < fVar2) << 8 | (ushort)(NAN(fVar3) || NAN(fVar2)) << 10 |
         (ushort)(fVar3 == fVar2) << 0xe;
    f2xm1(ABS(fVar3));
    return CONCAT14(*(undefined1 *)(unaff_EBP + -0x9f),in_EAX);
  }
  fVar2 = (float10)0;
  *(ushort *)(unaff_EBP + -0xa0) =
       (ushort)(in_ST0 < fVar2) << 8 | (ushort)(NAN(in_ST0) || NAN(fVar2)) << 10 |
       (ushort)(in_ST0 == fVar2) << 0xe;
  if ((*(byte *)(unaff_EBP + -0x9f) & 1) == 0) {
    return CONCAT14(param_2,unaff_retaddr);
  }
  *(undefined1 *)(unaff_EBP + -0x90) = 4;
  uVar1 = FUN_00534706();
  return CONCAT14(extraout_DL,uVar1);
}


// 00537306

uint * FUN_00537306(uint *param_1)

{
  uint uVar1;
  char cVar2;
  uint in_EAX;
  uint uVar3;
  uint uVar4;
  uint *puVar5;
  char cVar6;
  uint uVar7;
  
  cVar6 = (char)in_EAX;
  while (((uint)param_1 & 3) != 0) {
    uVar7 = *param_1;
    if ((char)uVar7 == cVar6) {
      return param_1;
    }
    param_1 = (uint *)((int)param_1 + 1);
    if ((char)uVar7 == '\0') {
      return (uint *)0x0;
    }
  }
  uVar7 = in_EAX | in_EAX << 8;
  while( true ) {
    while( true ) {
      uVar1 = *param_1;
      uVar4 = uVar1 ^ (uVar7 << 0x10 | uVar7);
      uVar3 = uVar1 ^ 0xffffffff ^ uVar1 + 0x7efefeff;
      puVar5 = param_1 + 1;
      if (((uVar4 ^ 0xffffffff ^ uVar4 + 0x7efefeff) & 0x81010100) != 0) break;
      param_1 = puVar5;
      if ((uVar3 & 0x81010100) != 0) {
        if ((uVar3 & 0x1010100) != 0) {
          return (uint *)0x0;
        }
        if ((uVar1 + 0x7efefeff & 0x80000000) == 0) {
          return (uint *)0x0;
        }
      }
    }
    uVar1 = *param_1;
    if ((char)uVar1 == cVar6) {
      return param_1;
    }
    if ((char)uVar1 == '\0') {
      return (uint *)0x0;
    }
    cVar2 = (char)(uVar1 >> 8);
    if (cVar2 == cVar6) {
      return (uint *)((int)param_1 + 1);
    }
    if (cVar2 == '\0') {
      return (uint *)0x0;
    }
    cVar2 = (char)(uVar1 >> 0x10);
    if (cVar2 == cVar6) {
      return (uint *)((int)param_1 + 2);
    }
    if (cVar2 == '\0') break;
    cVar2 = (char)(uVar1 >> 0x18);
    if (cVar2 == cVar6) {
      return (uint *)((int)param_1 + 3);
    }
    param_1 = puVar5;
    if (cVar2 == '\0') {
      return (uint *)0x0;
    }
  }
  return (uint *)0x0;
}


// 005373c0

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* Library Function - Single Match
    __XcptFilter
   
   Library: Visual Studio 2003 Debug */

int __cdecl __XcptFilter(ulong _ExceptionNum,_EXCEPTION_POINTERS *_ExceptionPtr)

{
  code *pcVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  int *piVar4;
  int iVar5;
  int local_14;
  
  piVar4 = (int *)xcptlookup(_ExceptionNum);
  uVar3 = DAT_00b940f4;
  if ((piVar4 == (int *)0x0) || (piVar4[2] == 0)) {
    iVar5 = UnhandledExceptionFilter(_ExceptionPtr);
  }
  else if (piVar4[2] == 5) {
    piVar4[2] = 0;
    iVar5 = 1;
  }
  else if (piVar4[2] == 1) {
    iVar5 = -1;
    DAT_00b940f4 = (_EXCEPTION_POINTERS *)uVar3;
  }
  else {
    pcVar1 = (code *)piVar4[2];
    DAT_00b940f4 = _ExceptionPtr;
    if (piVar4[1] == 8) {
      for (local_14 = DAT_0057a868; uVar2 = DAT_0057a874, local_14 < DAT_0057a868 + _DAT_0057a86c;
          local_14 = local_14 + 1) {
        *(undefined4 *)(local_14 * 0xc + 0x57a7f8) = 0;
      }
      if (*piVar4 == -0x3fffff72) {
        DAT_0057a874 = 0x83;
      }
      else if (*piVar4 == -0x3fffff70) {
        DAT_0057a874 = 0x81;
      }
      else if (*piVar4 == -0x3fffff6f) {
        DAT_0057a874 = 0x84;
      }
      else if (*piVar4 == -0x3fffff6d) {
        DAT_0057a874 = 0x85;
      }
      else if (*piVar4 == -0x3fffff73) {
        DAT_0057a874 = 0x82;
      }
      else if (*piVar4 == -0x3fffff71) {
        DAT_0057a874 = 0x86;
      }
      else if (*piVar4 == -0x3fffff6e) {
        DAT_0057a874 = 0x8a;
      }
      (*pcVar1)(8,DAT_0057a874);
      DAT_0057a874 = uVar2;
    }
    else {
      piVar4[2] = 0;
      (*pcVar1)(piVar4[1]);
    }
    iVar5 = -1;
    DAT_00b940f4 = (_EXCEPTION_POINTERS *)uVar3;
  }
  return iVar5;
}


// 00537570

/* Library Function - Single Match
    _xcptlookup
   
   Library: Visual Studio 2003 Debug */

int * __cdecl xcptlookup(int param_1)

{
  int *local_8;
  
  local_8 = &DAT_0057a7f0;
  do {
    if (*local_8 == param_1) break;
    local_8 = local_8 + 3;
  } while (local_8 < &DAT_0057a7f0 + DAT_0057a870 * 3);
  if ((&DAT_0057a7f0 + DAT_0057a870 * 3 <= local_8) || (*local_8 != param_1)) {
    local_8 = (int *)0x0;
  }
  return local_8;
}


// 005375d0

byte * __fastcall FUN_005375d0(undefined4 param_1)

{
  byte *pbVar1;
  int iVar2;
  byte *pbVar3;
  
  if (DAT_01286bc8 == 0) {
    FUN_0053d310(param_1);
  }
  pbVar3 = DAT_01286bac;
  pbVar1 = DAT_01286bac;
  if (*DAT_01286bac == 0x22) {
    while ((pbVar1 = pbVar3 + 1, *pbVar1 != 0x22 && (*pbVar1 != 0))) {
      iVar2 = FUN_0053ca90(*pbVar1);
      pbVar3 = pbVar1;
      if (iVar2 != 0) {
        pbVar3 = pbVar1 + 1;
      }
    }
    if (*pbVar1 == 0x22) {
      pbVar1 = pbVar3 + 2;
    }
  }
  else {
    for (; 0x20 < *pbVar1; pbVar1 = pbVar1 + 1) {
    }
  }
  for (; (*pbVar1 != 0 && (*pbVar1 < 0x21)); pbVar1 = pbVar1 + 1) {
  }
  return pbVar1;
}


// 00537690

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_00537690(void)

{
  size_t sVar1;
  int iVar2;
  int *local_10;
  int local_c;
  char *local_8;
  
  if (DAT_01286bc8 == 0) {
    FUN_0053d310();
  }
  local_c = 0;
  for (local_8 = DAT_00b940a0; *local_8 != '\0'; local_8 = local_8 + sVar1 + 1) {
    if (*local_8 != '=') {
      local_c = local_c + 1;
    }
    sVar1 = _strlen(local_8);
  }
  local_10 = (int *)FUN_0052c150(local_c * 4 + 4,2,"stdenvp.c",0x6d);
  DAT_00b94078 = local_10;
  if (local_10 == (int *)0x0) {
    __amsg_exit(9);
  }
  for (local_8 = DAT_00b940a0; *local_8 != '\0'; local_8 = local_8 + sVar1 + 1) {
    sVar1 = _strlen(local_8);
    if (*local_8 != '=') {
      iVar2 = FUN_0052c150(sVar1 + 1,2,"stdenvp.c",0x79);
      *local_10 = iVar2;
      if (*local_10 == 0) {
        __amsg_exit(9);
      }
      FUN_0052b100(*local_10,local_8);
      local_10 = local_10 + 1;
    }
  }
  FUN_0052cb90(DAT_00b940a0,2);
  DAT_00b940a0 = (char *)0x0;
  *local_10 = 0;
  _DAT_01286bb8 = 1;
  return;
}


// 005377e0

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_005377e0(void)

{
  char *local_18;
  int local_10;
  int local_c;
  int local_8;
  
  if (DAT_01286bc8 == 0) {
    FUN_0053d310();
  }
  GetModuleFileNameA((HMODULE)0x0,&DAT_00b940f8,0x104);
  DAT_00b94088 = &DAT_00b940f8;
  if (*DAT_01286bac == '\0') {
    local_18 = &DAT_00b940f8;
  }
  else {
    local_18 = DAT_01286bac;
  }
  FUN_005378c0(local_18,0,0,&local_10,&local_8);
  local_c = FUN_0052c150(local_8 + local_10 * 4,2,"stdargv.c",0x80);
  if (local_c == 0) {
    __amsg_exit(8);
  }
  FUN_005378c0(local_18,local_c,local_c + local_10 * 4,&local_10,&local_8);
  _DAT_00b9406c = local_10 + -1;
  _DAT_00b94070 = local_c;
  return;
}


// 005378c0

void FUN_005378c0(byte *param_1,undefined4 *param_2,byte *param_3,int *param_4,int *param_5)

{
  byte bVar1;
  bool bVar2;
  byte *pbVar3;
  bool bVar4;
  uint local_14;
  byte *local_8;
  
  *param_5 = 0;
  *param_4 = 1;
  local_8 = param_1;
  if (param_2 != (undefined4 *)0x0) {
    *param_2 = param_3;
    param_2 = param_2 + 1;
  }
  if (*param_1 == 0x22) {
    while ((pbVar3 = local_8 + 1, *pbVar3 != 0x22 && (*pbVar3 != 0))) {
      if ((((&DAT_012855c1)[*pbVar3] & 4) != 0) && (*param_5 = *param_5 + 1, param_3 != (byte *)0x0)
         ) {
        *param_3 = *pbVar3;
        param_3 = param_3 + 1;
        pbVar3 = local_8 + 2;
      }
      local_8 = pbVar3;
      *param_5 = *param_5 + 1;
      if (param_3 != (byte *)0x0) {
        *param_3 = *local_8;
        param_3 = param_3 + 1;
      }
    }
    *param_5 = *param_5 + 1;
    if (param_3 != (byte *)0x0) {
      *param_3 = 0;
      param_3 = param_3 + 1;
    }
    if (*pbVar3 == 0x22) {
      pbVar3 = local_8 + 2;
    }
  }
  else {
    do {
      *param_5 = *param_5 + 1;
      if (param_3 != (byte *)0x0) {
        *param_3 = *local_8;
        param_3 = param_3 + 1;
      }
      bVar1 = *local_8;
      pbVar3 = local_8 + 1;
      if (((&DAT_012855c1)[bVar1] & 4) != 0) {
        *param_5 = *param_5 + 1;
        if (param_3 != (byte *)0x0) {
          *param_3 = local_8[1];
          param_3 = param_3 + 1;
        }
        pbVar3 = local_8 + 2;
      }
      local_8 = pbVar3;
    } while (((bVar1 != 0x20) && (bVar1 != 0)) && (bVar1 != 9));
    if (bVar1 == 0) {
      pbVar3 = local_8 + -1;
    }
    else {
      pbVar3 = local_8;
      if (param_3 != (byte *)0x0) {
        param_3[-1] = 0;
      }
    }
  }
  local_8 = pbVar3;
  bVar2 = false;
  while( true ) {
    if (*local_8 != 0) {
      for (; (*local_8 == 0x20 || (*local_8 == 9)); local_8 = local_8 + 1) {
      }
    }
    if (*local_8 == 0) break;
    if (param_2 != (undefined4 *)0x0) {
      *param_2 = param_3;
      param_2 = param_2 + 1;
    }
    *param_4 = *param_4 + 1;
    while( true ) {
      bVar4 = true;
      local_14 = 0;
      for (; *local_8 == 0x5c; local_8 = local_8 + 1) {
        local_14 = local_14 + 1;
      }
      if (*local_8 == 0x22) {
        if (local_14 % 2 == 0) {
          if (bVar2) {
            bVar4 = local_8[1] == 0x22;
            if (bVar4) {
              local_8 = local_8 + 1;
            }
          }
          else {
            bVar4 = false;
          }
          bVar2 = !bVar2;
        }
        local_14 = local_14 >> 1;
      }
      while (local_14 != 0) {
        if (param_3 != (byte *)0x0) {
          *param_3 = 0x5c;
          param_3 = param_3 + 1;
        }
        *param_5 = *param_5 + 1;
        local_14 = local_14 - 1;
      }
      if ((*local_8 == 0) || ((!bVar2 && ((*local_8 == 0x20 || (*local_8 == 9)))))) break;
      if (bVar4) {
        if (param_3 == (byte *)0x0) {
          if (((&DAT_012855c1)[*local_8] & 4) != 0) {
            local_8 = local_8 + 1;
            *param_5 = *param_5 + 1;
          }
        }
        else {
          if (((&DAT_012855c1)[*local_8] & 4) != 0) {
            *param_3 = *local_8;
            param_3 = param_3 + 1;
            local_8 = local_8 + 1;
            *param_5 = *param_5 + 1;
          }
          *param_3 = *local_8;
          param_3 = param_3 + 1;
        }
        *param_5 = *param_5 + 1;
      }
      local_8 = local_8 + 1;
    }
    if (param_3 != (byte *)0x0) {
      *param_3 = 0;
      param_3 = param_3 + 1;
    }
    *param_5 = *param_5 + 1;
  }
  if (param_2 != (undefined4 *)0x0) {
    *param_2 = 0;
  }
  *param_4 = *param_4 + 1;
  return;
}


// 00537cf0

LPSTR FUN_00537cf0(void)

{
  char *pcVar1;
  LPWCH pWVar2;
  int iVar3;
  LPSTR pCVar4;
  int cchWideChar;
  LPCH local_1c;
  LPWCH local_18;
  char *local_10;
  LPWCH local_c;
  
  local_18 = (LPWCH)0x0;
  local_1c = (LPCH)0x0;
  if (DAT_00b941fc == 0) {
    local_18 = GetEnvironmentStringsW();
    if (local_18 == (LPWCH)0x0) {
      local_1c = GetEnvironmentStrings();
      if (local_1c == (LPCH)0x0) {
        return (LPSTR)0x0;
      }
      DAT_00b941fc = 2;
    }
    else {
      DAT_00b941fc = 1;
    }
  }
  if (DAT_00b941fc == 1) {
    if ((local_18 == (LPWCH)0x0) && (local_18 = GetEnvironmentStringsW(), local_18 == (LPWCH)0x0)) {
      pCVar4 = (LPSTR)0x0;
    }
    else {
      local_c = local_18;
      pWVar2 = local_c;
      while (local_c = pWVar2, *local_c != L'\0') {
        pWVar2 = local_c + 1;
        if (local_c[1] == L'\0') {
          pWVar2 = local_c + 2;
        }
      }
      cchWideChar = ((int)local_c - (int)local_18 >> 1) + 1;
      iVar3 = WideCharToMultiByte(0,0,local_18,cchWideChar,(LPSTR)0x0,0,(LPCSTR)0x0,(LPBOOL)0x0);
      if ((iVar3 == 0) ||
         (local_1c = (LPCH)FUN_0052c150(iVar3,2,"a_env.c",100), local_1c == (LPSTR)0x0)) {
        FreeEnvironmentStringsW(local_18);
        pCVar4 = (LPSTR)0x0;
      }
      else {
        iVar3 = WideCharToMultiByte(0,0,local_18,cchWideChar,local_1c,iVar3,(LPCSTR)0x0,(LPBOOL)0x0)
        ;
        if (iVar3 == 0) {
          FUN_0052cb90(local_1c,2);
          local_1c = (LPSTR)0x0;
        }
        FreeEnvironmentStringsW(local_18);
        pCVar4 = local_1c;
      }
    }
  }
  else if (DAT_00b941fc == 2) {
    if ((local_1c == (LPCH)0x0) && (local_1c = GetEnvironmentStrings(), local_1c == (LPCH)0x0)) {
      pCVar4 = (LPSTR)0x0;
    }
    else {
      local_10 = local_1c;
      pcVar1 = local_10;
      while (local_10 = pcVar1, *local_10 != '\0') {
        pcVar1 = local_10 + 1;
        if (local_10[1] == '\0') {
          pcVar1 = local_10 + 2;
        }
      }
      pCVar4 = (LPSTR)FUN_0052c150(local_10 + (1 - (int)local_1c),2,"a_env.c",0x8f);
      if (pCVar4 == (LPSTR)0x0) {
        FreeEnvironmentStringsA(local_1c);
        pCVar4 = (LPSTR)0x0;
      }
      else {
        FUN_0052b650(pCVar4,local_1c,local_10 + (1 - (int)local_1c));
        FreeEnvironmentStringsA(local_1c);
      }
    }
  }
  else {
    pCVar4 = (LPSTR)0x0;
  }
  return pCVar4;
}


// 00537f0c

/* Library Function - Single Match
    __global_unwind2
   
   Library: Visual Studio */

void __global_unwind2(PVOID param_1)

{
  RtlUnwind(param_1,(PVOID)0x537f24,(PEXCEPTION_RECORD)0x0,(PVOID)0x0);
  return;
}


// 00537f4e

/* Library Function - Single Match
    __local_unwind2
   
   Libraries: Visual Studio 1998 Debug, Visual Studio 1998 Release, Visual Studio 2003 Debug, Visual
   Studio 2003 Release */

void __local_unwind2(int param_1,int param_2)

{
  int iVar1;
  int iVar2;
  void *pvStack_1c;
  undefined1 *puStack_18;
  undefined4 local_14;
  int iStack_10;
  
  iStack_10 = param_1;
  puStack_18 = &LAB_00537f2c;
  pvStack_1c = ExceptionList;
  ExceptionList = &pvStack_1c;
  while( true ) {
    iVar1 = *(int *)(param_1 + 8);
    iVar2 = *(int *)(param_1 + 0xc);
    if ((iVar2 == -1) || (iVar2 == param_2)) break;
    local_14 = *(undefined4 *)(iVar1 + iVar2 * 0xc);
    *(undefined4 *)(param_1 + 0xc) = local_14;
    if (*(int *)(iVar1 + 4 + iVar2 * 0xc) == 0) {
      FUN_00537fe2(0x101);
      (**(code **)(iVar1 + 8 + iVar2 * 0xc))();
    }
  }
  ExceptionList = pvStack_1c;
  return;
}


// 00537fe2

void FUN_00537fe2(void)

{
  undefined4 in_EAX;
  int unaff_EBP;
  
  DAT_0057a880 = *(undefined4 *)(unaff_EBP + 8);
  DAT_0057a87c = in_EAX;
  DAT_0057a884 = unaff_EBP;
  return;
}


// 005380c1

void FUN_005380c1(int param_1)

{
  __local_unwind2(*(undefined4 *)(param_1 + 0x18),*(undefined4 *)(param_1 + 0x1c));
  return;
}


// 005380e0

/* Library Function - Single Match
    __FF_MSGBANNER
   
   Library: Visual Studio 2003 Debug */

void __cdecl __FF_MSGBANNER(void)

{
  if ((DAT_00b940a8 == 1) || ((DAT_00b940a8 == 0 && (DAT_0057a234 == 1)))) {
    FUN_00538130(0xfc);
    if (DAT_00b94200 != (code *)0x0) {
      (*DAT_00b94200)();
    }
    FUN_00538130(0xff);
  }
  return;
}


// 00538130

void FUN_00538130(int param_1)

{
  code *pcVar1;
  int iVar2;
  size_t sVar3;
  HANDLE hFile;
  DWORD DVar4;
  undefined *lpBuffer;
  DWORD *lpNumberOfBytesWritten;
  LPOVERLAPPED lpOverlapped;
  undefined1 local_1b4 [160];
  CHAR local_114 [260];
  char *local_10;
  uint local_c;
  DWORD local_8;
  
  for (local_c = 0; (local_c < 0x12 && (param_1 != *(int *)(&DAT_0057a888 + local_c * 8)));
      local_c = local_c + 1) {
  }
  if (param_1 == *(int *)(&DAT_0057a888 + local_c * 8)) {
    if ((param_1 != 0xfc) &&
       (iVar2 = FUN_0052fad0(1,0,0,0,(&PTR_s_R6002___floating_point_not_loade_0057a88c)[local_c * 2]
                            ), iVar2 == 1)) {
      pcVar1 = (code *)swi(3);
      (*pcVar1)();
      return;
    }
    if ((DAT_00b940a8 == 1) || ((DAT_00b940a8 == 0 && (DAT_0057a234 == 1)))) {
      lpOverlapped = (LPOVERLAPPED)0x0;
      lpNumberOfBytesWritten = &local_8;
      sVar3 = _strlen((&PTR_s_R6002___floating_point_not_loade_0057a88c)[local_c * 2]);
      lpBuffer = (&PTR_s_R6002___floating_point_not_loade_0057a88c)[local_c * 2];
      hFile = GetStdHandle(0xfffffff4);
      WriteFile(hFile,lpBuffer,sVar3,lpNumberOfBytesWritten,lpOverlapped);
    }
    else if (param_1 != 0xfc) {
      DVar4 = GetModuleFileNameA((HMODULE)0x0,local_114,0x104);
      if (DVar4 == 0) {
        FUN_0052b100(local_114,"<program name unknown>");
      }
      local_10 = local_114;
      sVar3 = _strlen(local_10);
      if (0x3c < sVar3 + 1) {
        sVar3 = _strlen(local_114);
        local_10 = local_10 + (sVar3 - 0x3b);
        _strncpy(local_10,"...",3);
      }
      FUN_0052b100(local_1b4,"Runtime Error!\n\nProgram: ");
      FUN_0052b110(local_1b4,local_10);
      FUN_0052b110(local_1b4,&DAT_00547594);
      FUN_0052b110(local_1b4,(&PTR_s_R6002___floating_point_not_loade_0057a88c)[local_c * 2]);
      FUN_00539070(local_1b4,"Microsoft Visual C++ Runtime Library",0x12010);
    }
  }
  return;
}


// 005382f0

/* Library Function - Single Match
    __GET_RTERRMSG
   
   Library: Visual Studio 2003 Debug */

wchar_t * __cdecl __GET_RTERRMSG(int param_1)

{
  wchar_t *pwVar1;
  uint local_8;
  
  for (local_8 = 0; (local_8 < 0x12 && (param_1 != *(int *)(&DAT_0057a888 + local_8 * 8)));
      local_8 = local_8 + 1) {
  }
  if (param_1 == *(int *)(&DAT_0057a888 + local_8 * 8)) {
    pwVar1 = (wchar_t *)(&PTR_s_R6002___floating_point_not_loade_0057a88c)[local_8 * 2];
  }
  else {
    pwVar1 = (wchar_t *)0x0;
  }
  return pwVar1;
}


// 00538340

void FUN_00538340(undefined4 *param_1)

{
  code *pcVar1;
  int iVar2;
  undefined4 uVar3;
  
  if ((param_1 == (undefined4 *)0x0) &&
     (iVar2 = FUN_0052fad0(2,"_getbuf.c",0x2e,0,"str != NULL"), iVar2 == 1)) {
    pcVar1 = (code *)swi(3);
    (*pcVar1)();
    return;
  }
  DAT_00b94204 = DAT_00b94204 + 1;
  uVar3 = FUN_0052c150(0x1000,2,"_getbuf.c",0x3b);
  param_1[2] = uVar3;
  if (param_1[2] == 0) {
    param_1[3] = param_1[3] | 4;
    param_1[2] = param_1 + 5;
    param_1[6] = 2;
  }
  else {
    param_1[3] = param_1[3] | 8;
    param_1[6] = 0x1000;
  }
  *param_1 = param_1[2];
  param_1[1] = 0;
  return;
}


// 00538410

/* Library Function - Single Match
    __isatty
   
   Library: Visual Studio 2003 Debug */

int __cdecl __isatty(int _FileHandle)

{
  uint uVar1;
  
  if ((uint)_FileHandle < DAT_01286b9c) {
    uVar1 = (int)*(char *)((&DAT_01286a60)[_FileHandle >> 5] + 4 + (_FileHandle & 0x1fU) * 8) & 0x40
    ;
  }
  else {
    uVar1 = 0;
  }
  return uVar1;
}


// 00538440

void __fastcall FUN_00538440(undefined4 param_1)

{
  int iVar1;
  uint uVar2;
  
  if (DAT_01286a20 == 0) {
    DAT_01286a20 = 0x200;
  }
  else if (DAT_01286a20 < 0x14) {
    DAT_01286a20 = 0x14;
  }
  DAT_012856c8 = __calloc_dbg(DAT_01286a20,4,2,"_file.c",0x83,param_1);
  if (DAT_012856c8 == 0) {
    DAT_01286a20 = 0x14;
    DAT_012856c8 = __calloc_dbg(0x14,4,2,"_file.c",0x86,param_1);
    if (DAT_012856c8 == 0) {
      __amsg_exit(0x1a);
    }
  }
  for (iVar1 = 0; iVar1 < 0x14; iVar1 = iVar1 + 1) {
    *(undefined ***)(DAT_012856c8 + iVar1 * 4) = &PTR_DAT_0057a918 + iVar1 * 8;
  }
  for (uVar2 = 0; (int)uVar2 < 3; uVar2 = uVar2 + 1) {
    if ((*(int *)((&DAT_01286a60)[(int)uVar2 >> 5] + (uVar2 & 0x1f) * 8) == -1) ||
       (*(int *)((&DAT_01286a60)[(int)uVar2 >> 5] + (uVar2 & 0x1f) * 8) == 0)) {
      *(undefined4 *)(&DAT_0057a928 + uVar2 * 0x20) = 0xffffffff;
    }
  }
  return;
}


// 00538570

void FUN_00538570(void)

{
  FUN_00530420();
  if (DAT_00b94090 != '\0') {
    FUN_0053d340();
  }
  return;
}


// 00538590

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

int FUN_00538590(LPSTR param_1,uint param_2)

{
  int iVar1;
  BOOL local_c [2];
  
  if (param_1 == (LPSTR)0x0) {
    iVar1 = 0;
  }
  else if (DAT_00b940cc == 0) {
    if ((param_2 & 0xffff) < 0x100) {
      *param_1 = (CHAR)param_2;
      iVar1 = 1;
    }
    else {
      _DAT_00b94050 = 0x2a;
      iVar1 = -1;
    }
  }
  else {
    local_c[0] = 0;
    iVar1 = WideCharToMultiByte(DAT_00b940dc,0x220,(LPCWSTR)&param_2,1,param_1,DAT_0057a5fc,
                                (LPCSTR)0x0,local_c);
    if ((iVar1 == 0) || (local_c[0] != 0)) {
      _DAT_00b94050 = 0x2a;
      iVar1 = -1;
    }
  }
  return iVar1;
}


// 00538630

/* Library Function - Single Match
    __aulldiv
   
   Library: Visual Studio 2003 Debug */

undefined8 __aulldiv(uint param_1,uint param_2,uint param_3,uint param_4)

{
  ulonglong uVar1;
  longlong lVar2;
  uint uVar3;
  int iVar4;
  uint uVar5;
  uint uVar7;
  uint uVar8;
  uint uVar9;
  uint uVar6;
  
  uVar9 = param_1;
  uVar6 = param_4;
  uVar7 = param_2;
  uVar3 = param_3;
  if (param_4 == 0) {
    uVar3 = param_2 / param_3;
    iVar4 = (int)(((ulonglong)param_2 % (ulonglong)param_3 << 0x20 | (ulonglong)param_1) /
                 (ulonglong)param_3);
  }
  else {
    do {
      uVar5 = uVar6 >> 1;
      uVar3 = (uint)(CONCAT14((uVar6 & 1) != 0,uVar3) >> 1);
      uVar8 = uVar7 >> 1;
      uVar9 = (uint)(CONCAT14((uVar7 & 1) != 0,uVar9) >> 1);
      uVar6 = uVar5;
      uVar7 = uVar8;
    } while (uVar5 != 0);
    uVar1 = CONCAT44(uVar8,uVar9) / (ulonglong)uVar3;
    iVar4 = (int)uVar1;
    lVar2 = (ulonglong)param_3 * (uVar1 & 0xffffffff);
    uVar3 = (uint)((ulonglong)lVar2 >> 0x20);
    uVar9 = uVar3 + iVar4 * param_4;
    if (((CARRY4(uVar3,iVar4 * param_4)) || (param_2 < uVar9)) ||
       ((param_2 <= uVar9 && (param_1 < (uint)lVar2)))) {
      iVar4 = iVar4 + -1;
    }
    uVar3 = 0;
  }
  return CONCAT44(uVar3,iVar4);
}


// 005386a0

/* Library Function - Single Match
    __aullrem
   
   Library: Visual Studio 2003 Debug */

undefined8 __aullrem(uint param_1,uint param_2,uint param_3,uint param_4)

{
  ulonglong uVar1;
  longlong lVar2;
  uint uVar3;
  uint uVar4;
  uint uVar5;
  int iVar6;
  int iVar7;
  uint uVar8;
  uint uVar9;
  uint uVar10;
  bool bVar11;
  
  uVar4 = param_1;
  uVar9 = param_4;
  uVar10 = param_2;
  uVar3 = param_3;
  if (param_4 == 0) {
    iVar6 = (int)(((ulonglong)param_2 % (ulonglong)param_3 << 0x20 | (ulonglong)param_1) %
                 (ulonglong)param_3);
    iVar7 = 0;
  }
  else {
    do {
      uVar5 = uVar9 >> 1;
      uVar3 = (uint)(CONCAT14((uVar9 & 1) != 0,uVar3) >> 1);
      uVar8 = uVar10 >> 1;
      uVar4 = (uint)(CONCAT14((uVar10 & 1) != 0,uVar4) >> 1);
      uVar9 = uVar5;
      uVar10 = uVar8;
    } while (uVar5 != 0);
    uVar1 = CONCAT44(uVar8,uVar4) / (ulonglong)uVar3;
    uVar3 = (int)uVar1 * param_4;
    lVar2 = (uVar1 & 0xffffffff) * (ulonglong)param_3;
    uVar9 = (uint)((ulonglong)lVar2 >> 0x20);
    uVar4 = (uint)lVar2;
    uVar10 = uVar9 + uVar3;
    if (((CARRY4(uVar9,uVar3)) || (param_2 < uVar10)) || ((param_2 <= uVar10 && (param_1 < uVar4))))
    {
      bVar11 = uVar4 < param_3;
      uVar4 = uVar4 - param_3;
      uVar10 = (uVar10 - param_4) - (uint)bVar11;
    }
    iVar6 = -(uVar4 - param_1);
    iVar7 = -(uint)(uVar4 - param_1 != 0) - ((uVar10 - param_2) - (uint)(uVar4 < param_1));
  }
  return CONCAT44(iVar7,iVar6);
}


// 00538720

/* Library Function - Single Match
    __itoa
   
   Library: Visual Studio 2003 Debug */

char * __cdecl __itoa(int _Value,char *_Dest,int _Radix)

{
  if ((_Radix == 10) && (_Value < 0)) {
    xtoa(_Value,_Dest,10,1);
  }
  else {
    xtoa(_Value,_Dest,_Radix,0);
  }
  return _Dest;
}


// 00538770

/* Library Function - Single Match
    _xtoa
   
   Library: Visual Studio 2003 Debug */

void __cdecl xtoa(uint param_1,char *param_2,uint param_3,int param_4)

{
  char cVar1;
  char *pcVar2;
  uint uVar3;
  char *local_c;
  char *local_8;
  
  local_8 = param_2;
  if (param_4 != 0) {
    *param_2 = '-';
    local_8 = param_2 + 1;
    param_1 = -param_1;
  }
  local_c = local_8;
  do {
    pcVar2 = local_8;
    uVar3 = param_1 % param_3;
    param_1 = param_1 / param_3;
    cVar1 = (char)uVar3;
    if (uVar3 < 10) {
      *local_8 = cVar1 + '0';
    }
    else {
      *local_8 = cVar1 + 'W';
    }
    local_8 = local_8 + 1;
  } while (param_1 != 0);
  *local_8 = '\0';
  local_8 = pcVar2;
  do {
    cVar1 = *local_8;
    *local_8 = *local_c;
    *local_c = cVar1;
    local_8 = local_8 + -1;
    local_c = local_c + 1;
  } while (local_c < local_8);
  return;
}


// 00538840

/* Library Function - Single Match
    __ltoa
   
   Library: Visual Studio 2003 Debug */

char * __cdecl __ltoa(long _Value,char *_Dest,int _Radix)

{
  undefined4 local_8;
  
  if ((_Radix == 10) && (_Value < 0)) {
    local_8 = 1;
  }
  else {
    local_8 = 0;
  }
  xtoa(_Value,_Dest,_Radix,local_8);
  return _Dest;
}


// 00538880

/* Library Function - Single Match
    __ultoa
   
   Library: Visual Studio 2003 Debug */

char * __cdecl __ultoa(ulong _Value,char *_Dest,int _Radix)

{
  xtoa(_Value,_Dest,_Radix,0);
  return _Dest;
}


// 005388a0

/* Library Function - Single Match
    __i64toa
   
   Library: Visual Studio 2003 Debug */

char * __cdecl __i64toa(longlong _Val,char *_DstBuf,int _Radix)

{
  undefined4 local_8;
  
  if (((_Radix == 10) && (_Val < 0x100000000)) && (_Val < 0)) {
    local_8 = 1;
  }
  else {
    local_8 = 0;
  }
  x64toa(_Val,_DstBuf,_Radix,local_8);
  return _DstBuf;
}


// 005388f0

/* Library Function - Single Match
    _x64toa@20
   
   Library: Visual Studio 2003 Debug
   __stdcall x64toa,20 */

void x64toa(int param_1,int param_2,char *param_3,undefined4 param_4,int param_5)

{
  char cVar1;
  char *pcVar2;
  uint uVar3;
  bool bVar4;
  longlong lVar5;
  char *local_c;
  char *local_8;
  
  local_8 = param_3;
  if (param_5 != 0) {
    *param_3 = '-';
    local_8 = param_3 + 1;
    bVar4 = param_1 != 0;
    param_1 = -param_1;
    param_2 = -(param_2 + (uint)bVar4);
  }
  lVar5 = CONCAT44(param_2,param_1);
  local_c = local_8;
  do {
    pcVar2 = local_8;
    uVar3 = __aullrem(lVar5,param_4,0);
    lVar5 = __aulldiv(lVar5,param_4,0);
    if (uVar3 < 10) {
      *local_8 = (char)uVar3 + '0';
    }
    else {
      *local_8 = (char)uVar3 + 'W';
    }
    local_8 = local_8 + 1;
  } while (lVar5 != 0);
  *local_8 = '\0';
  local_8 = pcVar2;
  do {
    cVar1 = *local_8;
    *local_8 = *local_c;
    *local_c = cVar1;
    local_8 = local_8 + -1;
    local_c = local_c + 1;
  } while (local_c < local_8);
  return;
}


// 005389f0

/* Library Function - Single Match
    __ui64toa
   
   Library: Visual Studio 2003 Debug */

char * __cdecl __ui64toa(ulonglong _Val,char *_DstBuf,int _Radix)

{
  x64toa(_Val,_DstBuf,_Radix,0);
  return _DstBuf;
}


// 00538a10

undefined4 FUN_00538a10(undefined1 *param_1,int param_2,int param_3)

{
  code *pcVar1;
  int iVar2;
  undefined4 uVar3;
  undefined1 *local_24;
  int local_20;
  undefined1 *local_1c;
  undefined4 local_18;
  
  if ((param_1 == (undefined1 *)0x0) &&
     (iVar2 = FUN_0052fad0(2,"sprintf.c",0x5d,0,"string != NULL"), iVar2 == 1)) {
    pcVar1 = (code *)swi(3);
    uVar3 = (*pcVar1)();
    return uVar3;
  }
  if ((param_3 == 0) && (iVar2 = FUN_0052fad0(2,"sprintf.c",0x5e,0,"format != NULL"), iVar2 == 1)) {
    pcVar1 = (code *)swi(3);
    uVar3 = (*pcVar1)();
    return uVar3;
  }
  local_18 = 0x42;
  local_1c = param_1;
  local_24 = param_1;
  local_20 = param_2;
  uVar3 = FUN_0052eb20(&local_24,param_3,&stack0x00000010);
  local_20 = local_20 + -1;
  if (local_20 < 0) {
    FUN_0052e8a0(0,&local_24);
  }
  else {
    *local_24 = 0;
  }
  return uVar3;
}


// 00538b10

undefined4 FUN_00538b10(undefined1 *param_1,int param_2,int param_3,undefined4 param_4)

{
  code *pcVar1;
  int iVar2;
  undefined4 uVar3;
  undefined1 *local_24;
  int local_20;
  undefined1 *local_1c;
  undefined4 local_18;
  
  if ((param_1 == (undefined1 *)0x0) &&
     (iVar2 = FUN_0052fad0(2,"vsprintf.c",0x5a,0,"string != NULL"), iVar2 == 1)) {
    pcVar1 = (code *)swi(3);
    uVar3 = (*pcVar1)();
    return uVar3;
  }
  if ((param_3 == 0) && (iVar2 = FUN_0052fad0(2,"vsprintf.c",0x5b,0,"format != NULL"), iVar2 == 1))
  {
    pcVar1 = (code *)swi(3);
    uVar3 = (*pcVar1)();
    return uVar3;
  }
  local_18 = 0x42;
  local_1c = param_1;
  local_24 = param_1;
  local_20 = param_2;
  uVar3 = FUN_0052eb20(&local_24,param_3,param_4);
  local_20 = local_20 + -1;
  if (local_20 < 0) {
    FUN_0052e8a0(0,&local_24);
  }
  else {
    *local_24 = 0;
  }
  return uVar3;
}


// 00538c10

/* WARNING: Unable to track spacebase fully for stack */

void FUN_00538c10(void)

{
  uint in_EAX;
  undefined1 *puVar1;
  undefined4 unaff_retaddr;
  
  puVar1 = &stack0x00000004;
  for (; 0xfff < in_EAX; in_EAX = in_EAX - 0x1000) {
    puVar1 = puVar1 + -0x1000;
  }
  *(undefined4 *)(puVar1 + (-4 - in_EAX)) = unaff_retaddr;
  return;
}


// 00538c40

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

int FUN_00538c40(int param_1,int param_2)

{
  int iVar1;
  BOOL BVar2;
  int local_c;
  undefined4 *local_8;
  
  if ((param_2 != 4) && (param_2 != 3)) {
    if ((param_1 == 2) || (((param_1 == 0x15 || (param_1 == 0x16)) || (param_1 == 0xf)))) {
      if (((param_1 == 2) || (param_1 == 0x15)) && (DAT_00b94218 == 0)) {
        BVar2 = SetConsoleCtrlHandler(ctrlevent_capture,1);
        if (BVar2 != 1) {
          DAT_00b94054 = GetLastError();
          _DAT_00b94050 = 0x16;
          return -1;
        }
        DAT_00b94218 = 1;
      }
      switch(param_1) {
      case 2:
        local_c = DAT_00b94208;
        DAT_00b94208 = param_2;
        break;
      case 0xf:
        local_c = DAT_00b94214;
        DAT_00b94214 = param_2;
        break;
      case 0x15:
        local_c = DAT_00b9420c;
        DAT_00b9420c = param_2;
        break;
      case 0x16:
        local_c = DAT_00b94210;
        DAT_00b94210 = param_2;
      }
      return local_c;
    }
    if ((((param_1 == 8) || (param_1 == 4)) || (param_1 == 0xb)) &&
       (local_8 = (undefined4 *)siglookup(param_1), local_8 != (undefined4 *)0x0)) {
      iVar1 = local_8[2];
      do {
        if (local_8[1] != param_1) {
          return iVar1;
        }
        local_8[2] = param_2;
        local_8 = local_8 + 3;
      } while (local_8 < &DAT_0057a7f0 + DAT_0057a870 * 3);
      return iVar1;
    }
  }
  _DAT_00b94050 = 0x16;
  return -1;
}


// 00538de0

/* Library Function - Single Match
    _ctrlevent_capture@4
   
   Library: Visual Studio 2003 Debug
   __stdcall ctrlevent_capture,4 */

undefined4 ctrlevent_capture(int param_1)

{
  undefined4 uVar1;
  code *local_10;
  undefined4 *local_c;
  undefined4 local_8;
  
  if (param_1 == 0) {
    local_c = &DAT_00b94208;
    local_10 = DAT_00b94208;
    local_8 = 2;
  }
  else {
    local_c = &DAT_00b9420c;
    local_10 = DAT_00b9420c;
    local_8 = 0x15;
  }
  if (local_10 == (code *)0x0) {
    uVar1 = 0;
  }
  else {
    if (local_10 != (code *)0x1) {
      *local_c = 0;
      (*local_10)(local_8);
    }
    uVar1 = 1;
  }
  return uVar1;
}


// 00538e50

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 FUN_00538e50(int param_1)

{
  int iVar1;
  code *pcStack_18;
  undefined4 *puStack_14;
  undefined4 uStack_10;
  int iStack_c;
  undefined4 uStack_8;
  
  switch(param_1) {
  case 2:
    puStack_14 = &DAT_00b94208;
    pcStack_18 = DAT_00b94208;
    break;
  default:
    return 0xffffffff;
  case 4:
  case 8:
  case 0xb:
    iVar1 = siglookup(param_1);
    puStack_14 = (undefined4 *)(iVar1 + 8);
    pcStack_18 = (code *)*puStack_14;
    break;
  case 0xf:
    puStack_14 = &DAT_00b94214;
    pcStack_18 = DAT_00b94214;
    break;
  case 0x15:
    puStack_14 = &DAT_00b9420c;
    pcStack_18 = DAT_00b9420c;
    break;
  case 0x16:
    puStack_14 = &DAT_00b94210;
    pcStack_18 = DAT_00b94210;
  }
  if (pcStack_18 != (code *)0x1) {
    if (pcStack_18 == (code *)0x0) {
                    /* WARNING: Subroutine does not return */
      __exit(3);
    }
    if (((param_1 == 8) || (param_1 == 0xb)) || (param_1 == 4)) {
      uStack_10 = DAT_00b940f4;
      DAT_00b940f4 = 0;
      if (param_1 == 8) {
        uStack_8 = DAT_0057a874;
        DAT_0057a874 = 0x8c;
      }
    }
    if (param_1 == 8) {
      for (iStack_c = DAT_0057a868; iStack_c < DAT_0057a868 + _DAT_0057a86c; iStack_c = iStack_c + 1
          ) {
        *(undefined4 *)(iStack_c * 0xc + 0x57a7f8) = 0;
      }
    }
    else {
      *puStack_14 = 0;
    }
    if (param_1 == 8) {
      (*pcStack_18)(8,DAT_0057a874);
    }
    else {
      (*pcStack_18)(param_1);
      if ((param_1 != 0xb) && (param_1 != 4)) {
        return 0;
      }
    }
    if (param_1 == 8) {
      DAT_0057a874 = uStack_8;
    }
    DAT_00b940f4 = uStack_10;
    return 0;
  }
  return 0;
}


// 00539010

/* Library Function - Single Match
    _siglookup
   
   Library: Visual Studio 2003 Debug */

undefined4 * __cdecl siglookup(int param_1)

{
  undefined4 *local_8;
  
  local_8 = &DAT_0057a7f0;
  do {
    if (local_8[1] == param_1) break;
    local_8 = local_8 + 3;
  } while (local_8 < &DAT_0057a7f0 + DAT_0057a870 * 3);
  if ((&DAT_0057a7f0 + DAT_0057a870 * 3 <= local_8) || (local_8[1] != param_1)) {
    local_8 = (undefined4 *)0x0;
  }
  return local_8;
}


// 00539070

int FUN_00539070(undefined4 param_1,undefined4 param_2,undefined4 param_3)

{
  HMODULE hModule;
  int iVar1;
  int local_8;
  
  local_8 = 0;
  if (DAT_00b9421c == (FARPROC)0x0) {
    hModule = LoadLibraryA("user32.dll");
    if (hModule != (HMODULE)0x0) {
      DAT_00b9421c = GetProcAddress(hModule,"MessageBoxA");
      if (DAT_00b9421c != (FARPROC)0x0) {
        DAT_00b94220 = GetProcAddress(hModule,"GetActiveWindow");
        DAT_00b94224 = GetProcAddress(hModule,"GetLastActivePopup");
        goto LAB_005390e3;
      }
    }
    iVar1 = 0;
  }
  else {
LAB_005390e3:
    if (DAT_00b94220 != (FARPROC)0x0) {
      local_8 = (*DAT_00b94220)();
    }
    if ((local_8 != 0) && (DAT_00b94224 != (FARPROC)0x0)) {
      local_8 = (*DAT_00b94224)(local_8);
    }
    iVar1 = (*DAT_00b9421c)(local_8,param_1,param_2,param_3);
  }
  return iVar1;
}


// 00539130

int FUN_00539130(void)

{
  int local_10;
  int local_c;
  undefined4 *local_8;
  
  local_c = -1;
  local_10 = 0;
  do {
    if (0x3f < local_10) {
      return local_c;
    }
    if ((&DAT_01286a60)[local_10] == 0) {
      local_8 = (undefined4 *)FUN_0052c150(0x100,2,"osfinfo.c",0x79);
      if (local_8 == (undefined4 *)0x0) {
        return local_c;
      }
      (&DAT_01286a60)[local_10] = local_8;
      DAT_01286b9c = DAT_01286b9c + 0x20;
      for (; local_8 < (undefined4 *)((&DAT_01286a60)[local_10] + 0x100); local_8 = local_8 + 2) {
        *(undefined1 *)(local_8 + 1) = 0;
        *local_8 = 0xffffffff;
        *(undefined1 *)((int)local_8 + 5) = 10;
      }
      return local_10 << 5;
    }
    for (local_8 = (undefined4 *)(&DAT_01286a60)[local_10];
        local_8 < (undefined4 *)((&DAT_01286a60)[local_10] + 0x100); local_8 = local_8 + 2) {
      if ((*(byte *)(local_8 + 1) & 1) == 0) {
        *local_8 = 0xffffffff;
        local_c = local_10 * 0x20 + ((int)local_8 - (&DAT_01286a60)[local_10] >> 3);
        break;
      }
    }
    if (local_c != -1) {
      return local_c;
    }
    local_10 = local_10 + 1;
  } while( true );
}


// 00539260

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* Library Function - Single Match
    __set_osfhnd
   
   Library: Visual Studio 2003 Debug */

int __cdecl __set_osfhnd(int param_1,intptr_t param_2)

{
  int iVar1;
  
  if (((uint)param_1 < DAT_01286b9c) &&
     (*(int *)((&DAT_01286a60)[param_1 >> 5] + (param_1 & 0x1fU) * 8) == -1)) {
    if (DAT_0057a234 == 1) {
      if (param_1 == 0) {
        SetStdHandle(0xfffffff6,(HANDLE)param_2);
      }
      else if (param_1 == 1) {
        SetStdHandle(0xfffffff5,(HANDLE)param_2);
      }
      else if (param_1 == 2) {
        SetStdHandle(0xfffffff4,(HANDLE)param_2);
      }
    }
    *(intptr_t *)((&DAT_01286a60)[param_1 >> 5] + (param_1 & 0x1fU) * 8) = param_2;
    iVar1 = 0;
  }
  else {
    _DAT_00b94050 = 9;
    DAT_00b94054 = 0;
    iVar1 = -1;
  }
  return iVar1;
}


// 00539310

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 FUN_00539310(uint param_1)

{
  undefined4 uVar1;
  int iVar2;
  
  if (((param_1 < DAT_01286b9c) &&
      (iVar2 = (int)param_1 >> 5,
      (*(byte *)((&DAT_01286a60)[iVar2] + 4 + (param_1 & 0x1f) * 8) & 1) != 0)) &&
     (*(int *)((&DAT_01286a60)[iVar2] + (param_1 & 0x1f) * 8) != -1)) {
    if (DAT_0057a234 == 1) {
      if (param_1 == 0) {
        SetStdHandle(0xfffffff6,(HANDLE)0x0);
      }
      else if (param_1 == 1) {
        SetStdHandle(0xfffffff5,(HANDLE)0x0);
      }
      else if (param_1 == 2) {
        SetStdHandle(0xfffffff4,(HANDLE)0x0);
      }
    }
    *(undefined4 *)((&DAT_01286a60)[iVar2] + (param_1 & 0x1f) * 8) = 0xffffffff;
    uVar1 = 0;
  }
  else {
    _DAT_00b94050 = 9;
    DAT_00b94054 = 0;
    uVar1 = 0xffffffff;
  }
  return uVar1;
}


// 005393e0

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 FUN_005393e0(uint param_1)

{
  undefined4 uVar1;
  
  if ((param_1 < DAT_01286b9c) &&
     ((*(byte *)((&DAT_01286a60)[(int)param_1 >> 5] + 4 + (param_1 & 0x1f) * 8) & 1) != 0)) {
    uVar1 = *(undefined4 *)((&DAT_01286a60)[(int)param_1 >> 5] + (param_1 & 0x1f) * 8);
  }
  else {
    _DAT_00b94050 = 9;
    DAT_00b94054 = 0;
    uVar1 = 0xffffffff;
  }
  return uVar1;
}


// 00539440

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

uint FUN_00539440(HANDLE param_1,uint param_2)

{
  DWORD DVar1;
  uint uVar2;
  byte local_10;
  
  local_10 = 0;
  if ((param_2 & 8) != 0) {
    local_10 = 0x20;
  }
  if ((param_2 & 0x4000) != 0) {
    local_10 = local_10 | 0x80;
  }
  if ((param_2 & 0x80) != 0) {
    local_10 = local_10 | 0x10;
  }
  DVar1 = GetFileType(param_1);
  if (DVar1 == 0) {
    DVar1 = GetLastError();
    __dosmaperr(DVar1);
    uVar2 = 0xffffffff;
  }
  else {
    if (DVar1 == 2) {
      local_10 = local_10 | 0x40;
    }
    else if (DVar1 == 3) {
      local_10 = local_10 | 8;
    }
    uVar2 = FUN_00539130();
    if (uVar2 == 0xffffffff) {
      _DAT_00b94050 = 0x18;
      DAT_00b94054 = 0;
      uVar2 = 0xffffffff;
    }
    else {
      __set_osfhnd(uVar2,(intptr_t)param_1);
      *(byte *)((&DAT_01286a60)[(int)uVar2 >> 5] + 4 + (uVar2 & 0x1f) * 8) = local_10 | 1;
    }
  }
  return uVar2;
}


// 00539530

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 __thiscall FUN_00539530(undefined4 param_1,uint param_2)

{
  HANDLE hFile;
  BOOL BVar1;
  DWORD DVar2;
  
  DVar2 = DAT_00b94054;
  if (((param_2 < DAT_01286b9c) &&
      ((*(byte *)((&DAT_01286a60)[(int)param_2 >> 5] + 4 + (param_2 & 0x1f) * 8) & 1) != 0)) &&
     ((*(byte *)((&DAT_01286a60)[(int)param_2 >> 5] + 4 + (param_2 & 0x1f) * 8) & 1) != 0)) {
    hFile = (HANDLE)FUN_005393e0(param_2,param_1);
    BVar1 = FlushFileBuffers(hFile);
    if (BVar1 == 0) {
      DVar2 = GetLastError();
    }
    else {
      DVar2 = 0;
    }
    if (DVar2 == 0) {
      return 0;
    }
  }
  DAT_00b94054 = DVar2;
  _DAT_00b94050 = 9;
  return 0xffffffff;
}


// 005395e0

/* Library Function - Multiple Matches With Different Base Names
    __open
    __wopen
   
   Library: Visual Studio 2003 Debug */

int __cdecl FID_conflict___open(char *_Filename,int _OpenFlag,...)

{
  int iVar1;
  undefined4 in_stack_0000000c;
  
  iVar1 = FUN_00539620(_Filename,_OpenFlag,0x40,in_stack_0000000c,0);
  return iVar1;
}


// 00539620

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

uint FUN_00539620(LPCSTR param_1,uint param_2,undefined4 param_3,uint param_4)

{
  DWORD DVar1;
  int iVar2;
  int iVar3;
  uint uVar4;
  bool bVar5;
  byte local_3c;
  uint local_38;
  char acStack_34 [4];
  undefined4 uStack_30;
  uint uStack_2c;
  _SECURITY_ATTRIBUTES local_28;
  DWORD DStack_1c;
  uint uStack_18;
  uint uStack_14;
  DWORD DStack_10;
  DWORD DStack_c;
  HANDLE pvStack_8;
  
  local_28.nLength = 0xc;
  local_28.lpSecurityDescriptor = (LPVOID)0x0;
  bVar5 = (param_2 & 0x80) == 0;
  if (bVar5) {
    local_3c = 0;
  }
  else {
    local_3c = 0x10;
  }
  local_28.bInheritHandle = (BOOL)bVar5;
  if ((param_2 & 0x8000) == 0) {
    if ((param_2 & 0x4000) == 0) {
      if (DAT_00b94268 != 0x8000) {
        local_3c = local_3c | 0x80;
      }
    }
    else {
      local_3c = local_3c | 0x80;
    }
  }
  uVar4 = param_2 & 3;
  if (uVar4 == 0) {
    local_38 = 0x80000000;
  }
  else if (uVar4 == 1) {
    local_38 = 0x40000000;
  }
  else {
    if (uVar4 != 2) {
      _DAT_00b94050 = 0x16;
      DAT_00b94054 = 0;
      return 0xffffffff;
    }
    local_38 = 0xc0000000;
  }
  switch(param_3) {
  case 0x10:
    DStack_c = 0;
    break;
  default:
    _DAT_00b94050 = 0x16;
    DAT_00b94054 = 0;
    return 0xffffffff;
  case 0x20:
    DStack_c = 1;
    break;
  case 0x30:
    DStack_c = 2;
    break;
  case 0x40:
    DStack_c = 3;
  }
  uVar4 = param_2 & 0x700;
  if (uVar4 < 0x401) {
    if (uVar4 != 0x400) {
      if (0x200 < uVar4) {
        if (uVar4 != 0x300) {
          _DAT_00b94050 = 0x16;
          DAT_00b94054 = 0;
          return 0xffffffff;
        }
        DStack_1c = 2;
        goto LAB_005397fe;
      }
      if (uVar4 == 0x200) goto LAB_005397d0;
      if (uVar4 != 0) {
        if (uVar4 != 0x100) {
          _DAT_00b94050 = 0x16;
          DAT_00b94054 = 0;
          return 0xffffffff;
        }
        DStack_1c = 4;
        goto LAB_005397fe;
      }
    }
    DStack_1c = 3;
  }
  else {
    if (uVar4 != 0x500) {
      if (uVar4 == 0x600) {
LAB_005397d0:
        DStack_1c = 5;
        goto LAB_005397fe;
      }
      if (uVar4 != 0x700) {
        _DAT_00b94050 = 0x16;
        DAT_00b94054 = 0;
        return 0xffffffff;
      }
    }
    DStack_1c = 1;
  }
LAB_005397fe:
  uStack_2c = 0x80;
  if ((param_2 & 0x100) != 0) {
    uStack_14 = param_4;
    uStack_30 = 0;
    if ((param_4 & ~DAT_00b94058 & 0x80) == 0) {
      uStack_2c = 1;
    }
  }
  if ((param_2 & 0x40) != 0) {
    uStack_2c = uStack_2c | 0x4000000;
    local_38 = local_38 | 0x10000;
  }
  if ((param_2 & 0x1000) != 0) {
    uStack_2c = uStack_2c | 0x100;
  }
  if ((param_2 & 0x20) == 0) {
    if ((param_2 & 0x10) != 0) {
      uStack_2c = uStack_2c | 0x10000000;
    }
  }
  else {
    uStack_2c = uStack_2c | 0x8000000;
  }
  uStack_18 = FUN_00539130();
  if (uStack_18 == 0xffffffff) {
    _DAT_00b94050 = 0x18;
    DAT_00b94054 = 0;
    uStack_18 = 0xffffffff;
  }
  else {
    pvStack_8 = CreateFileA(param_1,local_38,DStack_c,&local_28,DStack_1c,uStack_2c,(HANDLE)0x0);
    if (pvStack_8 == (HANDLE)0xffffffff) {
      DVar1 = GetLastError();
      __dosmaperr(DVar1);
      uStack_18 = 0xffffffff;
    }
    else {
      DStack_10 = GetFileType(pvStack_8);
      if (DStack_10 == 0) {
        CloseHandle(pvStack_8);
        DVar1 = GetLastError();
        __dosmaperr(DVar1);
        uStack_18 = 0xffffffff;
      }
      else {
        if (DStack_10 == 2) {
          local_3c = local_3c | 0x40;
        }
        else if (DStack_10 == 3) {
          local_3c = local_3c | 8;
        }
        __set_osfhnd(uStack_18,(intptr_t)pvStack_8);
        *(byte *)((&DAT_01286a60)[(int)uStack_18 >> 5] + 4 + (uStack_18 & 0x1f) * 8) = local_3c | 1;
        if ((((local_3c & 0x48) == 0) && (((int)(char)(local_3c | 1) & 0x80U) != 0)) &&
           ((param_2 & 2) != 0)) {
          iVar2 = FUN_00531eb0(uStack_18,0xffffffff,2);
          if (iVar2 == -1) {
            if (DAT_00b94054 != 0x83) {
              FUN_00530170(uStack_18);
              return 0xffffffff;
            }
          }
          else {
            acStack_34[0] = '\0';
            iVar3 = FUN_005306f0(uStack_18,acStack_34,1);
            if (((iVar3 == 0) && (acStack_34[0] == '\x1a')) &&
               (iVar2 = FUN_0053d3f0(uStack_18,iVar2), iVar2 == -1)) {
              FUN_00530170(uStack_18);
              return 0xffffffff;
            }
            iVar2 = FUN_00531eb0(uStack_18,0,0);
            if (iVar2 == -1) {
              FUN_00530170(uStack_18);
              return 0xffffffff;
            }
          }
        }
        if (((local_3c & 0x48) == 0) && ((param_2 & 8) != 0)) {
          *(byte *)((&DAT_01286a60)[(int)uStack_18 >> 5] + 4 + (uStack_18 & 0x1f) * 8) =
               *(byte *)((&DAT_01286a60)[(int)uStack_18 >> 5] + 4 + (uStack_18 & 0x1f) * 8) | 0x20;
        }
      }
    }
  }
  return uStack_18;
}


// 00539b30

void FUN_00539b30(void)

{
  FUN_00539f00();
  return;
}


// 00539b50

uint FUN_00539b50(uint param_1,uint param_2)

{
  uint uVar1;
  
  uVar1 = FUN_00539c20();
  uVar1 = param_1 & param_2 | uVar1 & ~param_2;
  FUN_00539da0(uVar1);
  return uVar1;
}


// 00539ba0

/* Library Function - Single Match
    __controlfp
   
   Library: Visual Studio 2003 Debug */

uint __cdecl __controlfp(uint _NewValue,uint _Mask)

{
  uint uVar1;
  
  uVar1 = FUN_00539b50(_NewValue,_Mask & 0xfff7ffff);
  return uVar1;
}


// 00539bc0

void FUN_00539bc0(void)

{
  int iVar1;
  
  iVar1 = DAT_00b940f4;
  __setdefaultprecision();
  if ((iVar1 != 0) && ((**(uint **)(iVar1 + 4) & 0x10008) != 0)) {
    iVar1 = *(int *)(iVar1 + 4);
    *(undefined4 *)(iVar1 + 0x20) = 0;
    *(undefined4 *)(iVar1 + 0x24) = 0xffff;
  }
  return;
}


// 00539c20

uint FUN_00539c20(uint param_1)

{
  uint uVar1;
  uint local_8;
  
  local_8 = 0;
  if ((param_1 & 1) != 0) {
    local_8 = 0x10;
  }
  if ((param_1 & 4) != 0) {
    local_8 = local_8 | 8;
  }
  if ((param_1 & 8) != 0) {
    local_8 = local_8 | 4;
  }
  if ((param_1 & 0x10) != 0) {
    local_8 = local_8 | 2;
  }
  if ((param_1 & 0x20) != 0) {
    local_8 = local_8 | 1;
  }
  if ((param_1 & 2) != 0) {
    local_8 = local_8 | 0x80000;
  }
  uVar1 = param_1 & 0xc00;
  if (uVar1 < 0x801) {
    if (uVar1 == 0x800) {
      local_8 = local_8 | 0x200;
    }
    else if ((uVar1 != 0) && (uVar1 == 0x400)) {
      local_8 = local_8 | 0x100;
    }
  }
  else if (uVar1 == 0xc00) {
    local_8 = local_8 | 0x300;
  }
  if ((param_1 & 0x300) == 0) {
    local_8 = local_8 | 0x20000;
  }
  else if ((param_1 & 0x300) == 0x200) {
    local_8 = local_8 | 0x10000;
  }
  if ((param_1 & 0x1000) != 0) {
    local_8 = local_8 | 0x40000;
  }
  return local_8;
}


// 00539da0

undefined4 FUN_00539da0(uint param_1)

{
  uint uVar1;
  ushort local_8;
  
  local_8 = (ushort)((param_1 & 0x10) != 0);
  if ((param_1 & 8) != 0) {
    local_8 = local_8 | 4;
  }
  if ((param_1 & 4) != 0) {
    local_8 = local_8 | 8;
  }
  if ((param_1 & 2) != 0) {
    local_8 = local_8 | 0x10;
  }
  if ((param_1 & 1) != 0) {
    local_8 = local_8 | 0x20;
  }
  if ((param_1 & 0x80000) != 0) {
    local_8 = local_8 | 2;
  }
  uVar1 = param_1 & 0x300;
  if (uVar1 < 0x201) {
    if (uVar1 == 0x200) {
      local_8 = local_8 | 0x800;
    }
    else if ((uVar1 != 0) && (uVar1 == 0x100)) {
      local_8 = local_8 | 0x400;
    }
  }
  else if (uVar1 == 0x300) {
    local_8 = local_8 | 0xc00;
  }
  if ((param_1 & 0x30000) == 0) {
    local_8 = local_8 | 0x300;
  }
  else if ((param_1 & 0x30000) == 0x10000) {
    local_8 = local_8 | 0x200;
  }
  if ((param_1 & 0x40000) != 0) {
    local_8 = local_8 | 0x1000;
  }
  return CONCAT22((short)((param_1 & 0x40000) >> 0x10),local_8);
}


// 00539f00

uint FUN_00539f00(uint param_1)

{
  undefined4 local_8;
  
  local_8 = 0;
  if ((param_1 & 1) != 0) {
    local_8 = 0x10;
  }
  if ((param_1 & 4) != 0) {
    local_8 = local_8 | 8;
  }
  if ((param_1 & 8) != 0) {
    local_8 = local_8 | 4;
  }
  if ((param_1 & 0x10) != 0) {
    local_8 = local_8 | 2;
  }
  if ((param_1 & 0x20) != 0) {
    local_8 = local_8 | 1;
  }
  if ((param_1 & 2) != 0) {
    local_8 = local_8 | 0x80000;
  }
  return local_8;
}


// 00539fb0

int FUN_00539fb0(int param_1)

{
  return param_1 + 0x20;
}


// 00539fc0

uint FUN_00539fc0(uint param_1)

{
  int iVar1;
  uint local_14;
  uint local_10;
  undefined1 local_c;
  undefined1 local_b;
  undefined1 local_a;
  undefined4 local_8;
  
  if (DAT_00b940cc == 0) {
    if ((0x40 < (int)param_1) && ((int)param_1 < 0x5b)) {
      param_1 = param_1 + 0x20;
    }
  }
  else {
    if ((int)param_1 < 0x100) {
      if (DAT_0057a5fc < 2) {
        local_14 = *(ushort *)(PTR_DAT_0057a3f0 + param_1 * 2) & 1;
      }
      else {
        local_14 = FUN_00532300(param_1,1);
      }
      if (local_14 == 0) {
        return param_1;
      }
    }
    if ((*(ushort *)(PTR_DAT_0057a3f0 + ((int)param_1 >> 8 & 0xffU) * 2) & 0x8000) == 0) {
      local_c = (undefined1)param_1;
      local_b = 0;
      local_8 = 1;
    }
    else {
      local_c = (undefined1)(param_1 >> 8);
      local_b = (undefined1)param_1;
      local_a = 0;
      local_8 = 2;
    }
    iVar1 = FUN_00531fa0(DAT_00b940cc,0x100,&local_c,local_8,&local_10,3,0,1);
    if (iVar1 != 0) {
      if (iVar1 == 1) {
        param_1 = local_10 & 0xff;
      }
      else {
        param_1 = local_10 & 0xff | (local_10 >> 8 & 0xff) << 8;
      }
    }
  }
  return param_1;
}


// 0053a0f0

undefined4 FUN_0053a0f0(int param_1,int param_2)

{
  uint uVar1;
  int local_10;
  
  local_10 = (int)(param_2 + (param_2 >> 0x1f & 0x1fU)) >> 5;
  uVar1 = *(uint *)(param_1 + local_10 * 4) & ~(-1 << (0x1f - ((byte)param_2 & 0x1f) & 0x1f));
  while( true ) {
    if (uVar1 != 0) {
      return 0;
    }
    local_10 = local_10 + 1;
    if (2 < local_10) break;
    uVar1 = *(uint *)(param_1 + local_10 * 4);
  }
  return 1;
}


// 0053a180

/* Library Function - Single Match
    __IncMan
   
   Library: Visual Studio */

int __IncMan(int param_1,int param_2)

{
  int local_14;
  int local_10;
  
  local_10 = (int)(param_2 + (param_2 >> 0x1f & 0x1fU)) >> 5;
  local_14 = ___addl(*(undefined4 *)(param_1 + local_10 * 4),
                     1 << (0x1f - ((byte)param_2 & 0x1f) & 0x1f),param_1 + local_10 * 4);
  while ((local_10 = local_10 + -1, -1 < local_10 && (local_14 != 0))) {
    local_14 = ___addl(*(undefined4 *)(param_1 + local_10 * 4),1,param_1 + local_10 * 4);
  }
  return local_14;
}


// 0053a230

undefined4 FUN_0053a230(int param_1,int param_2)

{
  int iVar1;
  byte bVar2;
  undefined4 local_1c;
  int local_14;
  
  local_1c = 0;
  local_14 = (int)(param_2 + (param_2 >> 0x1f & 0x1fU)) >> 5;
  bVar2 = 0x1f - ((byte)param_2 & 0x1f);
  if (((*(uint *)(param_1 + local_14 * 4) & 1 << (bVar2 & 0x1f)) != 0) &&
     (iVar1 = FUN_0053a0f0(param_1,param_2 + 1), iVar1 == 0)) {
    local_1c = __IncMan(param_1,param_2 + -1);
  }
  *(uint *)(param_1 + local_14 * 4) = *(uint *)(param_1 + local_14 * 4) & -1 << (bVar2 & 0x1f);
  while (local_14 = local_14 + 1, local_14 < 3) {
    *(undefined4 *)(param_1 + local_14 * 4) = 0;
  }
  return local_1c;
}


// 0053a310

/* Library Function - Single Match
    __CopyMan
   
   Library: Visual Studio */

void __CopyMan(undefined4 *param_1,undefined4 *param_2)

{
  int local_10;
  undefined4 *local_c;
  undefined4 *local_8;
  
  local_8 = param_2;
  local_c = param_1;
  for (local_10 = 0; local_10 < 3; local_10 = local_10 + 1) {
    *local_c = *local_8;
    local_c = local_c + 1;
    local_8 = local_8 + 1;
  }
  return;
}


// 0053a360

/* Library Function - Single Match
    __FillZeroMan
   
   Library: Visual Studio */

void __FillZeroMan(int param_1)

{
  undefined4 local_8;
  
  for (local_8 = 0; local_8 < 3; local_8 = local_8 + 1) {
    *(undefined4 *)(param_1 + local_8 * 4) = 0;
  }
  return;
}


// 0053a390

/* Library Function - Single Match
    __IsZeroMan
   
   Library: Visual Studio */

undefined4 __IsZeroMan(int param_1)

{
  int local_8;
  
  local_8 = 0;
  while( true ) {
    if (2 < local_8) {
      return 1;
    }
    if (*(int *)(param_1 + local_8 * 4) != 0) break;
    local_8 = local_8 + 1;
  }
  return 0;
}


// 0053a3d0

/* Library Function - Single Match
    __ShrMan
   
   Library: Visual Studio */

void __ShrMan(int param_1,int param_2)

{
  uint uVar1;
  int iVar2;
  byte bVar3;
  int local_10;
  uint local_c;
  
  iVar2 = (int)(param_2 + (param_2 >> 0x1f & 0x1fU)) >> 5;
  bVar3 = (byte)param_2 & 0x1f;
  local_c = 0;
  for (local_10 = 0; local_10 < 3; local_10 = local_10 + 1) {
    uVar1 = *(uint *)(param_1 + local_10 * 4);
    *(uint *)(param_1 + local_10 * 4) = *(uint *)(param_1 + local_10 * 4) >> bVar3;
    *(uint *)(param_1 + local_10 * 4) = *(uint *)(param_1 + local_10 * 4) | local_c;
    local_c = (uVar1 & ~(-1 << bVar3)) << (0x20 - bVar3 & 0x1f);
  }
  for (local_10 = 2; -1 < local_10; local_10 = local_10 + -1) {
    if (local_10 < iVar2) {
      *(undefined4 *)(param_1 + local_10 * 4) = 0;
    }
    else {
      *(undefined4 *)(param_1 + local_10 * 4) = *(undefined4 *)(param_1 + (local_10 - iVar2) * 4);
    }
  }
  return;
}


// 0053a4c0

undefined4 FUN_0053a4c0(ushort *param_1,uint *param_2,int *param_3)

{
  int iVar1;
  uint uVar2;
  undefined1 local_34 [16];
  uint local_24;
  undefined4 local_20;
  uint local_1c;
  uint local_18;
  int local_14;
  int local_c;
  int local_8;
  
  local_8 = (param_1[5] & 0x7fff) - 0x3fff;
  local_24 = param_1[5] & 0x8000;
  local_1c = *(uint *)(param_1 + 3);
  local_18 = *(uint *)(param_1 + 1);
  local_14 = (uint)*param_1 << 0x10;
  if (local_8 == -0x3fff) {
    local_c = 0;
    iVar1 = __IsZeroMan(&local_1c);
    if (iVar1 == 0) {
      __FillZeroMan(&local_1c);
      local_20 = 2;
    }
    else {
      local_20 = 0;
    }
  }
  else {
    __CopyMan(local_34,&local_1c);
    iVar1 = FUN_0053a230(&local_1c,param_3[2]);
    if (iVar1 != 0) {
      local_8 = local_8 + 1;
    }
    if (local_8 < param_3[1] - param_3[2]) {
      __FillZeroMan(&local_1c);
      local_c = 0;
      local_20 = 2;
    }
    else if (param_3[1] < local_8) {
      if (local_8 < *param_3) {
        local_c = local_8 + param_3[5];
        local_1c = local_1c & 0x7fffffff;
        __ShrMan(&local_1c,param_3[3]);
        local_20 = 0;
      }
      else {
        __FillZeroMan(&local_1c);
        local_1c = local_1c | 0x80000000;
        __ShrMan(&local_1c,param_3[3]);
        local_c = *param_3 + param_3[5];
        local_20 = 1;
      }
    }
    else {
      iVar1 = param_3[1] - local_8;
      __CopyMan(&local_1c,local_34,iVar1);
      __ShrMan(&local_1c,iVar1);
      FUN_0053a230(&local_1c,param_3[2]);
      __ShrMan(&local_1c,param_3[3] + 1);
      local_c = 0;
      local_20 = 2;
    }
  }
  uVar2 = local_1c | local_c << (0x20U - ((char)param_3[3] + '\x01') & 0x1f) |
          -(uint)(local_24 != 0) & 0x80000000;
  if (param_3[4] == 0x40) {
    param_2[1] = uVar2;
    *param_2 = local_18;
  }
  else if (param_3[4] == 0x20) {
    *param_2 = uVar2;
  }
  return local_20;
}


// 0053a710

void FUN_0053a710(undefined4 param_1,undefined4 param_2)

{
  FUN_0053a4c0(param_1,param_2,&DAT_0057aba0);
  return;
}


// 0053a730

void FUN_0053a730(undefined4 param_1,undefined4 param_2)

{
  FUN_0053a4c0(param_1,param_2,&DAT_0057abb8);
  return;
}


// 0053a750

bool FUN_0053a750(ushort *param_1,undefined4 *param_2)

{
  ushort uVar1;
  int iVar2;
  undefined4 local_14;
  undefined4 local_10;
  int local_c;
  undefined4 local_8;
  
  local_8 = CONCAT22(local_8._2_2_,param_1[5]) & 0xffff7fff;
  uVar1 = param_1[5];
  local_14 = *(undefined4 *)(param_1 + 3);
  local_10 = *(undefined4 *)(param_1 + 1);
  local_c = (uint)*param_1 << 0x10;
  iVar2 = FUN_0053a230(&local_14,0x40);
  if (iVar2 != 0) {
    local_14 = 0x80000000;
    local_8 = (uint)(ushort)((short)local_8 + 1);
  }
  param_2[1] = local_14;
  *param_2 = local_10;
  *(ushort *)(param_2 + 2) = uVar1 & 0x8000 | (ushort)local_8;
  return (local_8 & 0xffff) == 0x7fff;
}


// 0053a810

void FUN_0053a810(undefined4 param_1,undefined4 param_2)

{
  undefined1 local_14 [4];
  undefined1 local_10 [12];
  
  FUN_0053d960(local_10,local_14,param_2,0,0,0,0);
  FUN_0053a710(local_10,param_1);
  return;
}


// 0053a850

void FUN_0053a850(undefined4 param_1,undefined4 param_2)

{
  undefined1 local_14 [4];
  undefined1 local_10 [12];
  
  FUN_0053d960(local_10,local_14,param_2,1,0,0,0);
  FUN_0053a750(local_10,param_1);
  return;
}


// 0053a890

void FUN_0053a890(undefined4 param_1,undefined4 param_2)

{
  undefined1 local_14 [4];
  undefined1 local_10 [12];
  
  FUN_0053d960(local_10,local_14,param_2,0,0,0,0);
  FUN_0053a730(local_10,param_1);
  return;
}


// 0053a8d0

void FUN_0053a8d0(char *param_1,int param_2,int param_3)

{
  char cVar1;
  char *pcVar2;
  size_t sVar3;
  char *local_c;
  char *local_8;
  
  local_c = *(char **)(param_3 + 0xc);
  *param_1 = '0';
  pcVar2 = param_1;
  for (; local_8 = pcVar2 + 1, 0 < param_2; param_2 = param_2 + -1) {
    if (*local_c == '\0') {
      cVar1 = '0';
    }
    else {
      cVar1 = *local_c;
      local_c = local_c + 1;
    }
    *local_8 = cVar1;
    pcVar2 = local_8;
  }
  *local_8 = '\0';
  if ((-1 < param_2) && (local_8 = pcVar2, '4' < *local_c)) {
    for (; *local_8 == '9'; local_8 = local_8 + -1) {
      *local_8 = '0';
    }
    *local_8 = *local_8 + '\x01';
  }
  if (*param_1 == '1') {
    *(int *)(param_3 + 4) = *(int *)(param_3 + 4) + 1;
  }
  else {
    sVar3 = _strlen(param_1 + 1);
    FUN_0053abc0(param_1,param_1 + 1,sVar3 + 1);
  }
  return;
}


// 0053a9d0

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined * FUN_0053a9d0(void)

{
  undefined4 local_10;
  undefined4 local_c;
  undefined2 local_8;
  
  FUN_0053aa50(&local_10,&stack0x00000004);
  _DAT_00b94258 = FUN_0053e4e0(local_10,local_c,local_8,0x11,0,&DAT_00b94230);
  _DAT_00b94250 = (int)DAT_00b94232;
  _DAT_00b94254 = (int)DAT_00b94230;
  _DAT_00b9425c = &DAT_00b94234;
  return &DAT_00b94250;
}


// 0053aa50

void FUN_0053aa50(uint *param_1,uint *param_2)

{
  ushort uVar1;
  uint uVar2;
  int iVar3;
  ushort uVar4;
  short local_18;
  uint local_10;
  
  local_10 = 0x80000000;
  iVar3 = (int)(*(ushort *)((int)param_2 + 6) & 0x7ff0) >> 4;
  uVar1 = *(ushort *)((int)param_2 + 6);
  uVar2 = *param_2;
  local_18 = (short)iVar3;
  if (iVar3 == 0) {
    if (((param_2[1] & 0xfffff) == 0) && (uVar2 == 0)) {
      param_1[1] = 0;
      *param_1 = 0;
      *(undefined2 *)(param_1 + 2) = 0;
      return;
    }
    uVar4 = 0x3c01;
    local_10 = 0;
  }
  else if (iVar3 == 0x7ff) {
    uVar4 = 0x7fff;
  }
  else {
    uVar4 = local_18 + 0x3c00;
  }
  param_1[1] = local_10 | (param_2[1] & 0xfffff) << 0xb | uVar2 >> 0x15;
  *param_1 = uVar2 << 0xb;
  while ((param_1[1] & 0x80000000) == 0) {
    param_1[1] = param_1[1] << 1 | (uint)((*param_1 & 0x80000000) != 0);
    *param_1 = *param_1 << 1;
    uVar4 = uVar4 - 1;
  }
  *(ushort *)(param_1 + 2) = uVar1 & 0x8000 | uVar4;
  return;
}


// 0053abc0

undefined4 * FUN_0053abc0(undefined4 *param_1,undefined4 *param_2,uint param_3)

{
  uint uVar1;
  undefined4 *puVar2;
  
  if ((param_2 < param_1) && (param_1 < (undefined4 *)(param_3 + (int)param_2))) {
    param_2 = (undefined4 *)((param_3 - 4) + (int)param_2);
    puVar2 = (undefined4 *)((param_3 - 4) + (int)param_1);
    if (((uint)puVar2 & 3) == 0) {
      uVar1 = param_3 >> 2;
      param_3 = param_3 & 3;
      if (7 < uVar1) {
        for (; uVar1 != 0; uVar1 = uVar1 - 1) {
          *puVar2 = *param_2;
          param_2 = param_2 + -1;
          puVar2 = puVar2 + -1;
        }
        switch(param_3) {
        case 0:
          return param_1;
        case 2:
          goto LAB_0053aec8;
        case 3:
          goto LAB_0053aedc;
        }
        goto LAB_0053aeb8;
      }
    }
    else {
      switch(param_3) {
      case 0:
        goto LAB_0053aeb0;
      case 1:
        goto LAB_0053aeb8;
      case 2:
        goto LAB_0053aec8;
      case 3:
        goto LAB_0053aedc;
      default:
        uVar1 = param_3 - ((uint)puVar2 & 3);
        switch((uint)puVar2 & 3) {
        case 1:
          param_3 = uVar1 & 3;
          *(undefined1 *)((int)puVar2 + 3) = *(undefined1 *)((int)param_2 + 3);
          param_2 = (undefined4 *)((int)param_2 + -1);
          uVar1 = uVar1 >> 2;
          puVar2 = (undefined4 *)((int)puVar2 - 1);
          if (7 < uVar1) {
            for (; uVar1 != 0; uVar1 = uVar1 - 1) {
              *puVar2 = *param_2;
              param_2 = param_2 + -1;
              puVar2 = puVar2 + -1;
            }
            switch(param_3) {
            case 0:
              return param_1;
            case 2:
              goto LAB_0053aec8;
            case 3:
              goto LAB_0053aedc;
            }
            goto LAB_0053aeb8;
          }
          break;
        case 2:
          param_3 = uVar1 & 3;
          *(undefined1 *)((int)puVar2 + 3) = *(undefined1 *)((int)param_2 + 3);
          uVar1 = uVar1 >> 2;
          *(undefined1 *)((int)puVar2 + 2) = *(undefined1 *)((int)param_2 + 2);
          param_2 = (undefined4 *)((int)param_2 + -2);
          puVar2 = (undefined4 *)((int)puVar2 - 2);
          if (7 < uVar1) {
            for (; uVar1 != 0; uVar1 = uVar1 - 1) {
              *puVar2 = *param_2;
              param_2 = param_2 + -1;
              puVar2 = puVar2 + -1;
            }
            switch(param_3) {
            case 0:
              return param_1;
            case 2:
              goto LAB_0053aec8;
            case 3:
              goto LAB_0053aedc;
            }
            goto LAB_0053aeb8;
          }
          break;
        case 3:
          param_3 = uVar1 & 3;
          *(undefined1 *)((int)puVar2 + 3) = *(undefined1 *)((int)param_2 + 3);
          *(undefined1 *)((int)puVar2 + 2) = *(undefined1 *)((int)param_2 + 2);
          uVar1 = uVar1 >> 2;
          *(undefined1 *)((int)puVar2 + 1) = *(undefined1 *)((int)param_2 + 1);
          param_2 = (undefined4 *)((int)param_2 + -3);
          puVar2 = (undefined4 *)((int)puVar2 - 3);
          if (7 < uVar1) {
            for (; uVar1 != 0; uVar1 = uVar1 - 1) {
              *puVar2 = *param_2;
              param_2 = param_2 + -1;
              puVar2 = puVar2 + -1;
            }
            switch(param_3) {
            case 0:
              return param_1;
            case 2:
              goto LAB_0053aec8;
            case 3:
              goto LAB_0053aedc;
            }
            goto LAB_0053aeb8;
          }
        }
      }
    }
    switch(uVar1) {
    case 7:
      puVar2[7 - uVar1] = param_2[7 - uVar1];
    case 6:
      puVar2[6 - uVar1] = param_2[6 - uVar1];
    case 5:
      puVar2[5 - uVar1] = param_2[5 - uVar1];
    case 4:
      puVar2[4 - uVar1] = param_2[4 - uVar1];
    case 3:
      puVar2[3 - uVar1] = param_2[3 - uVar1];
    case 2:
      puVar2[2 - uVar1] = param_2[2 - uVar1];
    case 1:
      puVar2[1 - uVar1] = param_2[1 - uVar1];
      param_2 = param_2 + -uVar1;
      puVar2 = puVar2 + -uVar1;
    }
    switch(param_3) {
    case 1:
LAB_0053aeb8:
      *(undefined1 *)((int)puVar2 + 3) = *(undefined1 *)((int)param_2 + 3);
      return param_1;
    case 2:
LAB_0053aec8:
      *(undefined1 *)((int)puVar2 + 3) = *(undefined1 *)((int)param_2 + 3);
      *(undefined1 *)((int)puVar2 + 2) = *(undefined1 *)((int)param_2 + 2);
      return param_1;
    case 3:
LAB_0053aedc:
      *(undefined1 *)((int)puVar2 + 3) = *(undefined1 *)((int)param_2 + 3);
      *(undefined1 *)((int)puVar2 + 2) = *(undefined1 *)((int)param_2 + 2);
      *(undefined1 *)((int)puVar2 + 1) = *(undefined1 *)((int)param_2 + 1);
      return param_1;
    }
LAB_0053aeb0:
    return param_1;
  }
  puVar2 = param_1;
  if (((uint)param_1 & 3) == 0) {
    uVar1 = param_3 >> 2;
    param_3 = param_3 & 3;
    if (7 < uVar1) {
      for (; uVar1 != 0; uVar1 = uVar1 - 1) {
        *puVar2 = *param_2;
        param_2 = param_2 + 1;
        puVar2 = puVar2 + 1;
      }
      switch(param_3) {
      case 0:
        return param_1;
      case 2:
        goto LAB_0053ad2c;
      case 3:
        goto LAB_0053ad40;
      }
      goto LAB_0053ad20;
    }
  }
  else {
    switch(param_3) {
    case 0:
      goto LAB_0053ad18;
    case 1:
      goto LAB_0053ad20;
    case 2:
      goto LAB_0053ad2c;
    case 3:
      goto LAB_0053ad40;
    default:
      uVar1 = (param_3 - 4) + ((uint)param_1 & 3);
      switch((uint)param_1 & 3) {
      case 1:
        param_3 = uVar1 & 3;
        *(undefined1 *)param_1 = *(undefined1 *)param_2;
        *(undefined1 *)((int)param_1 + 1) = *(undefined1 *)((int)param_2 + 1);
        uVar1 = uVar1 >> 2;
        *(undefined1 *)((int)param_1 + 2) = *(undefined1 *)((int)param_2 + 2);
        param_2 = (undefined4 *)((int)param_2 + 3);
        puVar2 = (undefined4 *)((int)param_1 + 3);
        if (7 < uVar1) {
          for (; uVar1 != 0; uVar1 = uVar1 - 1) {
            *puVar2 = *param_2;
            param_2 = param_2 + 1;
            puVar2 = puVar2 + 1;
          }
          switch(param_3) {
          case 0:
            return param_1;
          case 2:
            goto LAB_0053ad2c;
          case 3:
            goto LAB_0053ad40;
          }
          goto LAB_0053ad20;
        }
        break;
      case 2:
        param_3 = uVar1 & 3;
        *(undefined1 *)param_1 = *(undefined1 *)param_2;
        uVar1 = uVar1 >> 2;
        *(undefined1 *)((int)param_1 + 1) = *(undefined1 *)((int)param_2 + 1);
        param_2 = (undefined4 *)((int)param_2 + 2);
        puVar2 = (undefined4 *)((int)param_1 + 2);
        if (7 < uVar1) {
          for (; uVar1 != 0; uVar1 = uVar1 - 1) {
            *puVar2 = *param_2;
            param_2 = param_2 + 1;
            puVar2 = puVar2 + 1;
          }
          switch(param_3) {
          case 0:
            return param_1;
          case 2:
            goto LAB_0053ad2c;
          case 3:
            goto LAB_0053ad40;
          }
          goto LAB_0053ad20;
        }
        break;
      case 3:
        param_3 = uVar1 & 3;
        *(undefined1 *)param_1 = *(undefined1 *)param_2;
        param_2 = (undefined4 *)((int)param_2 + 1);
        uVar1 = uVar1 >> 2;
        puVar2 = (undefined4 *)((int)param_1 + 1);
        if (7 < uVar1) {
          for (; uVar1 != 0; uVar1 = uVar1 - 1) {
            *puVar2 = *param_2;
            param_2 = param_2 + 1;
            puVar2 = puVar2 + 1;
          }
          switch(param_3) {
          case 0:
            return param_1;
          case 2:
            goto LAB_0053ad2c;
          case 3:
            goto LAB_0053ad40;
          }
          goto LAB_0053ad20;
        }
      }
    }
  }
  switch(uVar1) {
  case 7:
    puVar2[uVar1 - 7] = param_2[uVar1 - 7];
  case 6:
    puVar2[uVar1 - 6] = param_2[uVar1 - 6];
  case 5:
    puVar2[uVar1 - 5] = param_2[uVar1 - 5];
  case 4:
    puVar2[uVar1 - 4] = param_2[uVar1 - 4];
  case 3:
    puVar2[uVar1 - 3] = param_2[uVar1 - 3];
  case 2:
    puVar2[uVar1 - 2] = param_2[uVar1 - 2];
  case 1:
    puVar2[uVar1 - 1] = param_2[uVar1 - 1];
    param_2 = param_2 + uVar1;
    puVar2 = puVar2 + uVar1;
  }
  switch(param_3) {
  case 1:
LAB_0053ad20:
    *(undefined1 *)puVar2 = *(undefined1 *)param_2;
    return param_1;
  case 2:
LAB_0053ad2c:
    *(undefined1 *)puVar2 = *(undefined1 *)param_2;
    *(undefined1 *)((int)puVar2 + 1) = *(undefined1 *)((int)param_2 + 1);
    return param_1;
  case 3:
LAB_0053ad40:
    *(undefined1 *)puVar2 = *(undefined1 *)param_2;
    *(undefined1 *)((int)puVar2 + 1) = *(undefined1 *)((int)param_2 + 1);
    *(undefined1 *)((int)puVar2 + 2) = *(undefined1 *)((int)param_2 + 2);
    return param_1;
  }
LAB_0053ad18:
  return param_1;
}


// 0053af00

/* Library Function - Single Match
    __fptrap
   
   Library: Visual Studio 2003 Debug */

void __cdecl __fptrap(void)

{
  __amsg_exit(2);
  return;
}


// 0053af10

BOOL FUN_0053af10(DWORD param_1,LPCSTR param_2,int param_3,LPWORD param_4,UINT param_5,LCID param_6,
                 int param_7)

{
  undefined1 *puVar1;
  BOOL BVar2;
  int iVar3;
  WORD local_20 [2];
  undefined1 *local_1c;
  void *local_14;
  undefined1 *puStack_10;
  undefined *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &DAT_00547b70;
  puStack_10 = &LAB_00538004;
  local_14 = ExceptionList;
  local_1c = &stack0xffffffc4;
  ExceptionList = &local_14;
  puVar1 = &stack0xffffffc4;
  if (DAT_00b94260 == 0) {
    ExceptionList = &local_14;
    BVar2 = GetStringTypeW(1,L"",1,local_20);
    if (BVar2 == 0) {
      BVar2 = GetStringTypeA(0,1,"",1,local_20);
      if (BVar2 == 0) {
        ExceptionList = local_14;
        return 0;
      }
      DAT_00b94260 = 2;
      puVar1 = local_1c;
    }
    else {
      DAT_00b94260 = 1;
      puVar1 = local_1c;
    }
  }
  local_1c = puVar1;
  if (DAT_00b94260 == 2) {
    if (param_6 == 0) {
      param_6 = DAT_00b940cc;
    }
    BVar2 = GetStringTypeA(param_6,param_1,param_2,param_3,param_4);
  }
  else if (DAT_00b94260 == 1) {
    if (param_5 == 0) {
      param_5 = DAT_00b940dc;
    }
    iVar3 = MultiByteToWideChar(param_5,(-(uint)(param_7 != 0) & 8) + 1,param_2,param_3,(LPWSTR)0x0,
                                0);
    if (iVar3 == 0) {
      BVar2 = 0;
    }
    else {
      local_8 = 0;
      FUN_00538c10();
      local_1c = &stack0xffffffc4;
      _memset(&stack0xffffffc4,0,iVar3 << 1);
      local_8 = 0xffffffff;
      if (&stack0x00000000 == (undefined1 *)0x3c) {
        BVar2 = 0;
      }
      else {
        iVar3 = MultiByteToWideChar(param_5,1,param_2,param_3,(LPWSTR)&stack0xffffffc4,iVar3);
        if (iVar3 == 0) {
          BVar2 = 0;
        }
        else {
          BVar2 = GetStringTypeW(param_1,(LPCWSTR)&stack0xffffffc4,iVar3,param_4);
        }
      }
    }
  }
  else {
    BVar2 = 0;
  }
  ExceptionList = local_14;
  return BVar2;
}


// 0053b0d0

/* WARNING: Restarted to delay deadcode elimination for space: stack */

void FUN_0053b0d0(int param_1,_exception *param_2,ushort *param_3)

{
  int iVar1;
  undefined1 local_6c [40];
  undefined4 local_44;
  undefined4 local_40;
  uint local_34;
  uint local_14;
  uint *local_10;
  int local_c;
  int local_8;
  
  local_14 = (uint)*param_3;
  local_10 = &local_14;
  switch(param_2->type) {
  case 1:
  case 5:
    local_8 = 8;
    break;
  case 2:
    local_8 = 4;
    break;
  case 3:
    local_8 = 0x11;
    break;
  case 4:
    local_8 = 0x12;
    break;
  case 7:
    param_2->type = 1;
  default:
    local_8 = 0;
    break;
  case 8:
    local_8 = 0x10;
  }
  if ((local_8 != 0) && (iVar1 = FUN_005350f0(local_8,&param_2->retval,local_14), iVar1 == 0)) {
    if ((param_1 == 0x10) || ((param_1 == 0x16 || (param_1 == 0x1d)))) {
      local_34 = local_34 & 0xffffffe1 | 3;
      local_44 = *(undefined4 *)&param_2->arg2;
      local_40 = *(undefined4 *)((int)&param_2->arg2 + 4);
    }
    else {
      local_34 = local_34 & 0xfffffffe;
    }
    FUN_00534c20(local_6c,local_10,local_8,param_1,&param_2->arg1,&param_2->retval);
  }
  FUN_00535900(*local_10,0xffff);
  local_c = 0;
  if ((param_2->type != 8) && (DAT_0057abd0 == 0)) {
    local_c = __matherr(param_2);
  }
  if (local_c == 0) {
    __set_errno(param_2->type);
  }
  return;
}


// 0053b250

/* Library Function - Single Match
    __matherr
   
   Library: Visual Studio */

int __cdecl __matherr(_exception *_Except)

{
  return 0;
}


// 0053b260

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

uint FUN_0053b260(LPWSTR param_1,byte *param_2,uint param_3)

{
  code *pcVar1;
  int iVar2;
  uint uVar3;
  
  if (((DAT_0057a5fc != 1) && (DAT_0057a5fc != 2)) &&
     (iVar2 = FUN_0052fad0(2,"mbtowc.c",0x4f,0,"MB_CUR_MAX == 1 || MB_CUR_MAX == 2"), iVar2 == 1)) {
    pcVar1 = (code *)swi(3);
    uVar3 = (*pcVar1)();
    return uVar3;
  }
  if ((param_2 == (byte *)0x0) || (param_3 == 0)) {
    uVar3 = 0;
  }
  else if (*param_2 == 0) {
    if (param_1 != (LPWSTR)0x0) {
      *param_1 = L'\0';
    }
    uVar3 = 0;
  }
  else if (DAT_00b940cc == 0) {
    if (param_1 != (LPWSTR)0x0) {
      *param_1 = (ushort)*param_2;
    }
    uVar3 = 1;
  }
  else if ((*(ushort *)(PTR_DAT_0057a3f0 + (uint)*param_2 * 2) & 0x8000) == 0) {
    iVar2 = MultiByteToWideChar(DAT_00b940dc,9,(LPCSTR)param_2,1,param_1,
                                (uint)(param_1 != (LPWSTR)0x0));
    if (iVar2 == 0) {
      _DAT_00b94050 = 0x2a;
      uVar3 = 0xffffffff;
    }
    else {
      uVar3 = 1;
    }
  }
  else if (((((int)DAT_0057a5fc < 2) || ((int)param_3 < (int)DAT_0057a5fc)) ||
           (iVar2 = MultiByteToWideChar(DAT_00b940dc,9,(LPCSTR)param_2,DAT_0057a5fc,param_1,
                                        (uint)(param_1 != (LPWSTR)0x0)), uVar3 = DAT_0057a5fc,
           iVar2 == 0)) && ((param_3 < DAT_0057a5fc || (uVar3 = DAT_0057a5fc, param_2[1] == 0)))) {
    _DAT_00b94050 = 0x2a;
    uVar3 = 0xffffffff;
  }
  return uVar3;
}


// 0053b3c0

uint __thiscall FUN_0053b3c0(undefined4 param_1,int param_2)

{
  uint uVar1;
  
  if (DAT_0057a5fc < 2) {
    uVar1 = *(ushort *)(PTR_DAT_0057a3f0 + param_2 * 2) & 0x103;
  }
  else {
    uVar1 = FUN_00532300(param_2,0x103,param_1);
  }
  return uVar1;
}


// 0053b410

uint __thiscall FUN_0053b410(undefined4 param_1,int param_2)

{
  uint uVar1;
  
  if (DAT_0057a5fc < 2) {
    uVar1 = *(ushort *)(PTR_DAT_0057a3f0 + param_2 * 2) & 1;
  }
  else {
    uVar1 = FUN_00532300(param_2,1,param_1);
  }
  return uVar1;
}


// 0053b450

uint __thiscall FUN_0053b450(undefined4 param_1,int param_2)

{
  uint uVar1;
  
  if (DAT_0057a5fc < 2) {
    uVar1 = *(ushort *)(PTR_DAT_0057a3f0 + param_2 * 2) & 2;
  }
  else {
    uVar1 = FUN_00532300(param_2,2,param_1);
  }
  return uVar1;
}


// 0053b490

uint __thiscall FUN_0053b490(undefined4 param_1,int param_2)

{
  uint uVar1;
  
  if (DAT_0057a5fc < 2) {
    uVar1 = *(ushort *)(PTR_DAT_0057a3f0 + param_2 * 2) & 4;
  }
  else {
    uVar1 = FUN_00532300(param_2,4,param_1);
  }
  return uVar1;
}


// 0053b4d0

uint __thiscall FUN_0053b4d0(undefined4 param_1,int param_2)

{
  uint uVar1;
  
  if (DAT_0057a5fc < 2) {
    uVar1 = *(ushort *)(PTR_DAT_0057a3f0 + param_2 * 2) & 0x80;
  }
  else {
    uVar1 = FUN_00532300(param_2,0x80,param_1);
  }
  return uVar1;
}


// 0053b520

uint __thiscall FUN_0053b520(undefined4 param_1,int param_2)

{
  uint uVar1;
  
  if (DAT_0057a5fc < 2) {
    uVar1 = *(ushort *)(PTR_DAT_0057a3f0 + param_2 * 2) & 8;
  }
  else {
    uVar1 = FUN_00532300(param_2,8,param_1);
  }
  return uVar1;
}


// 0053b560

uint __thiscall FUN_0053b560(undefined4 param_1,int param_2)

{
  uint uVar1;
  
  if (DAT_0057a5fc < 2) {
    uVar1 = *(ushort *)(PTR_DAT_0057a3f0 + param_2 * 2) & 0x10;
  }
  else {
    uVar1 = FUN_00532300(param_2,0x10,param_1);
  }
  return uVar1;
}


// 0053b5a0

uint __thiscall FUN_0053b5a0(undefined4 param_1,int param_2)

{
  uint uVar1;
  
  if (DAT_0057a5fc < 2) {
    uVar1 = *(ushort *)(PTR_DAT_0057a3f0 + param_2 * 2) & 0x107;
  }
  else {
    uVar1 = FUN_00532300(param_2,0x107,param_1);
  }
  return uVar1;
}


// 0053b5f0

uint __thiscall FUN_0053b5f0(undefined4 param_1,int param_2)

{
  uint uVar1;
  
  if (DAT_0057a5fc < 2) {
    uVar1 = *(ushort *)(PTR_DAT_0057a3f0 + param_2 * 2) & 0x157;
  }
  else {
    uVar1 = FUN_00532300(param_2,0x157,param_1);
  }
  return uVar1;
}


// 0053b640

uint __thiscall FUN_0053b640(undefined4 param_1,int param_2)

{
  uint uVar1;
  
  if (DAT_0057a5fc < 2) {
    uVar1 = *(ushort *)(PTR_DAT_0057a3f0 + param_2 * 2) & 0x117;
  }
  else {
    uVar1 = FUN_00532300(param_2,0x117,param_1);
  }
  return uVar1;
}


// 0053b690

uint __thiscall FUN_0053b690(undefined4 param_1,int param_2)

{
  uint uVar1;
  
  if (DAT_0057a5fc < 2) {
    uVar1 = *(ushort *)(PTR_DAT_0057a3f0 + param_2 * 2) & 0x20;
  }
  else {
    uVar1 = FUN_00532300(param_2,0x20,param_1);
  }
  return uVar1;
}


// 0053b6d0

bool FUN_0053b6d0(uint param_1)

{
  return param_1 < 0x80;
}


// 0053b6e0

uint FUN_0053b6e0(uint param_1)

{
  return param_1 & 0x7f;
}


// 0053b6f0

undefined4 FUN_0053b6f0(int param_1)

{
  undefined4 local_c;
  uint local_8;
  
  if (DAT_0057a5fc < 2) {
    local_8 = *(ushort *)(PTR_DAT_0057a3f0 + param_1 * 2) & 0x103;
  }
  else {
    local_8 = FUN_00532300(param_1,0x103);
  }
  if ((local_8 == 0) && (param_1 != 0x5f)) {
    local_c = 0;
  }
  else {
    local_c = 1;
  }
  return local_c;
}


// 0053b750

undefined4 FUN_0053b750(int param_1)

{
  undefined4 local_c;
  uint local_8;
  
  if (DAT_0057a5fc < 2) {
    local_8 = *(ushort *)(PTR_DAT_0057a3f0 + param_1 * 2) & 0x107;
  }
  else {
    local_8 = FUN_00532300(param_1,0x107);
  }
  if ((local_8 == 0) && (param_1 != 0x5f)) {
    local_c = 0;
  }
  else {
    local_c = 1;
  }
  return local_c;
}


// 0053b7d0

uint FUN_0053b7d0(uint param_1,int *param_2)

{
  code *pcVar1;
  int iVar2;
  uint uVar3;
  
  if ((param_2 == (int *)0x0) &&
     (iVar2 = FUN_0052fad0(2,"ungetc.c",0x60,0,"str != NULL"), iVar2 == 1)) {
    pcVar1 = (code *)swi(3);
    uVar3 = (*pcVar1)();
    return uVar3;
  }
  if ((param_1 == 0xffffffff) ||
     (((param_2[3] & 1U) == 0 && (((param_2[3] & 0x80U) == 0 || ((param_2[3] & 2U) != 0)))))) {
    param_1 = 0xffffffff;
  }
  else {
    if (param_2[2] == 0) {
      FUN_00538340(param_2);
    }
    if (*param_2 == param_2[2]) {
      if (param_2[1] != 0) {
        return 0xffffffff;
      }
      *param_2 = *param_2 + 1;
    }
    if ((param_2[3] & 0x40U) == 0) {
      *param_2 = *param_2 + -1;
      *(char *)*param_2 = (char)param_1;
    }
    else {
      *param_2 = *param_2 + -1;
      if (*(char *)*param_2 != (char)param_1) {
        *param_2 = *param_2 + 1;
        return 0xffffffff;
      }
    }
    param_2[1] = param_2[1] + 1;
    param_2[3] = param_2[3] & 0xffffffef;
    param_2[3] = param_2[3] | 1;
    param_1 = param_1 & 0xff;
  }
  return param_1;
}


// 0053b910

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 FUN_0053b910(int param_1,int param_2,int param_3,int param_4,undefined4 *param_5)

{
  int iVar1;
  undefined4 local_2c;
  undefined4 local_28;
  undefined8 local_24;
  undefined8 local_1c;
  undefined4 local_10;
  
  local_10 = 0;
  if (_DAT_00546090 <= (double)CONCAT44(param_2,param_1)) {
    local_1c = (double)CONCAT44(param_2,param_1);
  }
  else {
    local_1c = -(double)CONCAT44(param_2,param_1);
  }
  if ((param_4 == 0x7ff00000) && (param_3 == 0)) {
    if (local_1c <= _DAT_005460b8) {
      if (_DAT_005460b8 <= local_1c) {
        *param_5 = DAT_0057a730;
        param_5[1] = DAT_0057a734;
        local_10 = 1;
      }
      else {
        *param_5 = 0;
        param_5[1] = 0;
      }
    }
    else {
      *param_5 = DAT_0057a728;
      param_5[1] = DAT_0057a72c;
    }
  }
  else if ((param_4 == -0x100000) && (param_3 == 0)) {
    if (local_1c <= _DAT_005460b8) {
      if (_DAT_005460b8 <= local_1c) {
        *param_5 = DAT_0057a730;
        param_5[1] = DAT_0057a734;
        local_10 = 1;
      }
      else {
        *param_5 = DAT_0057a728;
        param_5[1] = DAT_0057a72c;
      }
    }
    else {
      *param_5 = 0;
      param_5[1] = 0;
    }
  }
  else if ((param_2 == 0x7ff00000) && (param_1 == 0)) {
    if ((double)CONCAT44(param_4,param_3) <= _DAT_00546090) {
      if (_DAT_00546090 <= (double)CONCAT44(param_4,param_3)) {
        *param_5 = 0;
        param_5[1] = 0x3ff00000;
      }
      else {
        *param_5 = 0;
        param_5[1] = 0;
      }
    }
    else {
      *param_5 = DAT_0057a728;
      param_5[1] = DAT_0057a72c;
    }
  }
  else if ((param_2 == -0x100000) && (param_1 == 0)) {
    iVar1 = FUN_0053bb80(param_3,param_4);
    if ((double)CONCAT44(param_4,param_3) <= _DAT_00546090) {
      if (_DAT_00546090 <= (double)CONCAT44(param_4,param_3)) {
        *param_5 = 0;
        param_5[1] = 0x3ff00000;
      }
      else {
        if (iVar1 == 1) {
          local_2c = DAT_0057a748;
          local_28 = DAT_0057a74c;
        }
        else {
          local_2c = 0;
          local_28 = 0;
        }
        *param_5 = local_2c;
        param_5[1] = local_28;
      }
    }
    else {
      if (iVar1 == 1) {
        local_24 = -(double)CONCAT44(DAT_0057a72c,DAT_0057a728);
      }
      else {
        local_24 = (double)CONCAT44(DAT_0057a72c,DAT_0057a728);
      }
      *param_5 = (undefined4)local_24;
      param_5[1] = local_24._4_4_;
    }
  }
  return local_10;
}


// 0053bb80

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 FUN_0053bb80(undefined4 param_1,undefined4 param_2)

{
  uint uVar1;
  undefined4 uVar2;
  float10 fVar3;
  
  uVar1 = FUN_0053ef90(param_1,param_2);
  if ((uVar1 & 0x90) == 0) {
    fVar3 = (float10)FUN_0053ea00(param_1,param_2);
    if ((double)fVar3 == (double)CONCAT44(param_2,param_1)) {
      fVar3 = (float10)FUN_0053ea00((double)CONCAT44(param_2,param_1) / _DAT_00546140);
      if ((float10)(double)CONCAT44(param_2,param_1) / (float10)_DAT_00546140 == fVar3) {
        uVar2 = 2;
      }
      else {
        uVar2 = 1;
      }
    }
    else {
      uVar2 = 0;
    }
  }
  else {
    uVar2 = 0;
  }
  return uVar2;
}


// 0053bc00

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

uint FUN_0053bc00(int param_1,uint param_2,ushort param_3,undefined4 param_4,uint param_5,
                 uint param_6)

{
  float10 fVar1;
  uint uVar2;
  float10 fVar3;
  
  fVar1 = (float10)CONCAT28(param_3,CONCAT44(param_2,param_1));
  while (!CARRY4(param_2,param_2)) {
    if (param_1 == 0 && param_2 == 0) {
      return 0;
    }
    if ((param_3 & 0x7fff) != 0) {
      return param_3 & 0x7fff;
    }
    uVar2 = param_6 & 0x7fff;
    if (uVar2 == 0) {
      if (CARRY4(param_5,param_5)) {
        return param_5 * 2;
      }
    }
    else if ((uVar2 == 0x7fff) || (uVar2 = param_5 * 2, !CARRY4(param_5,param_5))) {
      return uVar2;
    }
    fVar3 = fVar1 * (float10)_DAT_0057abf8;
    param_1 = SUB104(fVar3,0);
    param_3 = (ushort)((unkuint10)fVar3 >> 0x40);
    param_2 = (uint)((unkuint10)fVar3 >> 0x20);
  }
  uVar2 = param_2 * 2 ^ 0xe000000;
  if ((uVar2 & 0xe000000) != 0) {
    return uVar2;
  }
  uVar2 = (param_2 & 0x7fffffff) >> 0x1b;
  if ((&DAT_0057abe0)[uVar2] != '\0') {
    if (((param_3 & 0x7fff) != 0) && ((param_3 & 0x7fff) != 0x7fff)) {
      if ((param_6 & 0x7fff) != 1) {
        return param_6 & 0x7fff;
      }
      return 1;
    }
    return param_3 & 0x7fff;
  }
  return uVar2;
}


// 0053c3f1

undefined4 FUN_0053c3f1(void)

{
  undefined4 in_EAX;
  
  FUN_0053bc00();
  return in_EAX;
}


// 0053c990

void FUN_0053c990(undefined4 param_1)

{
  FUN_0053cb10(param_1,0,1);
  return;
}


// 0053c9b0

void FUN_0053c9b0(undefined4 param_1)

{
  FUN_0053cb10(param_1,0,3);
  return;
}


// 0053c9d0

void FUN_0053c9d0(undefined4 param_1)

{
  FUN_0053cb10(param_1,0,2);
  return;
}


// 0053c9f0

void FUN_0053c9f0(undefined4 param_1)

{
  FUN_0053cb10(param_1,0x107,1);
  return;
}


// 0053ca10

void FUN_0053ca10(undefined4 param_1)

{
  FUN_0053cb10(param_1,0x103,1);
  return;
}


// 0053ca30

void FUN_0053ca30(undefined4 param_1)

{
  FUN_0053cb10(param_1,0x117,3);
  return;
}


// 0053ca50

void FUN_0053ca50(undefined4 param_1)

{
  FUN_0053cb10(param_1,0x157,3);
  return;
}


// 0053ca70

void FUN_0053ca70(undefined4 param_1)

{
  FUN_0053cb10(param_1,0x10,2);
  return;
}


// 0053ca90

void FUN_0053ca90(undefined4 param_1)

{
  FUN_0053cb10(param_1,0,4);
  return;
}


// 0053cab0

void FUN_0053cab0(undefined4 param_1)

{
  FUN_0053cb10(param_1,0,8);
  return;
}


// 0053cad0

/* Library Function - Single Match
    __ismbbkana
   
   Library: Visual Studio 2003 Debug */

int __cdecl __ismbbkana(uint _C)

{
  int iVar1;
  
  if ((DAT_0128542c == 0x3a4) && (iVar1 = FUN_0053cb10(_C,0,3), iVar1 != 0)) {
    return 1;
  }
  return 0;
}


// 0053cb10

undefined4 FUN_0053cb10(uint param_1,uint param_2,byte param_3)

{
  uint local_8;
  
  if (((&DAT_012855c1)[param_1 & 0xff] & param_3) == 0) {
    if (param_2 == 0) {
      local_8 = 0;
    }
    else {
      local_8 = *(ushort *)(&DAT_0057a3fa + (param_1 & 0xff) * 2) & param_2;
    }
    if (local_8 == 0) {
      return 0;
    }
  }
  return 1;
}


// 0053cb80

undefined4 FUN_0053cb80(undefined4 param_1)

{
  UINT CodePage;
  undefined4 uVar1;
  BOOL BVar2;
  BYTE *local_2c;
  uint local_28;
  _cpinfo local_24;
  uint local_10;
  byte *local_c;
  uint local_8;
  
  CodePage = getSystemCP(param_1);
  if (CodePage == DAT_0128542c) {
    uVar1 = 0;
  }
  else if (CodePage == 0) {
    setSBCS();
    FUN_0053cfe0();
    uVar1 = 0;
  }
  else {
    for (local_8 = 0; local_8 < 5; local_8 = local_8 + 1) {
      if (*(UINT *)(&DAT_0057ad48 + local_8 * 0x30) == CodePage) {
        for (local_28 = 0; local_28 < 0x101; local_28 = local_28 + 1) {
          (&DAT_012855c0)[local_28] = 0;
        }
        for (local_10 = 0; local_10 < 4; local_10 = local_10 + 1) {
          for (local_c = &DAT_0057ad58 + local_10 * 8 + local_8 * 0x30;
              (*local_c != 0 && (local_c[1] != 0)); local_c = local_c + 2) {
            for (local_28 = (uint)*local_c; local_28 <= local_c[1]; local_28 = local_28 + 1) {
              (&DAT_012855c1)[local_28] = (&DAT_012855c1)[local_28] | (&DAT_0057ad40)[local_10];
            }
          }
        }
        DAT_012854bc = 1;
        DAT_0128542c = CodePage;
        DAT_012856c4 = FUN_0053cee0(CodePage);
        for (local_10 = 0; local_10 < 6; local_10 = local_10 + 1) {
          *(undefined2 *)(&DAT_012854b0 + local_10 * 2) =
               *(undefined2 *)(&DAT_0057ad4c + local_10 * 2 + local_8 * 0x30);
        }
        FUN_0053cfe0();
        return 0;
      }
    }
    BVar2 = GetCPInfo(CodePage,&local_24);
    if (BVar2 == 1) {
      for (local_28 = 0; local_28 < 0x101; local_28 = local_28 + 1) {
        (&DAT_012855c0)[local_28] = 0;
      }
      DAT_012856c4 = 0;
      if (local_24.MaxCharSize < 2) {
        DAT_012854bc = 0;
        DAT_0128542c = CodePage;
      }
      else {
        DAT_0128542c = CodePage;
        for (local_2c = local_24.LeadByte; (*local_2c != 0 && (local_2c[1] != 0));
            local_2c = local_2c + 2) {
          for (local_28 = (uint)*local_2c; local_28 <= local_2c[1]; local_28 = local_28 + 1) {
            (&DAT_012855c1)[local_28] = (&DAT_012855c1)[local_28] | 4;
          }
        }
        for (local_28 = 1; local_28 < 0xff; local_28 = local_28 + 1) {
          (&DAT_012855c1)[local_28] = (&DAT_012855c1)[local_28] | 8;
        }
        DAT_012856c4 = FUN_0053cee0(DAT_0128542c);
        DAT_012854bc = 1;
      }
      for (local_10 = 0; local_10 < 6; local_10 = local_10 + 1) {
        *(undefined2 *)(&DAT_012854b0 + local_10 * 2) = 0;
      }
      FUN_0053cfe0();
      uVar1 = 0;
    }
    else if (DAT_00b94264 == 0) {
      uVar1 = 0xffffffff;
    }
    else {
      setSBCS();
      FUN_0053cfe0();
      uVar1 = 0;
    }
  }
  return uVar1;
}


// 0053ce80

/* Library Function - Single Match
    _getSystemCP
   
   Library: Visual Studio 2003 Debug */

UINT __cdecl getSystemCP(UINT param_1)

{
  DAT_00b94264 = 0;
  if (param_1 == 0xfffffffe) {
    DAT_00b94264 = 1;
    param_1 = GetOEMCP();
  }
  else if (param_1 == 0xfffffffd) {
    DAT_00b94264 = 1;
    param_1 = GetACP();
  }
  else if (param_1 == 0xfffffffc) {
    DAT_00b94264 = 1;
    param_1 = DAT_00b940dc;
  }
  return param_1;
}


// 0053cee0

undefined4 FUN_0053cee0(undefined4 param_1)

{
  undefined4 uVar1;
  
  switch(param_1) {
  case 0x3a4:
    uVar1 = 0x411;
    break;
  default:
    uVar1 = 0;
    break;
  case 0x3a8:
    uVar1 = 0x804;
    break;
  case 0x3b5:
    uVar1 = 0x412;
    break;
  case 0x3b6:
    uVar1 = 0x404;
  }
  return uVar1;
}


// 0053cf60

/* Library Function - Single Match
    _setSBCS
   
   Library: Visual Studio 2003 Debug */

void __cdecl setSBCS(void)

{
  int local_8;
  
  for (local_8 = 0; local_8 < 0x101; local_8 = local_8 + 1) {
    (&DAT_012855c0)[local_8] = 0;
  }
  DAT_0128542c = 0;
  DAT_012854bc = 0;
  DAT_012856c4 = 0;
  for (local_8 = 0; local_8 < 6; local_8 = local_8 + 1) {
    *(undefined2 *)(&DAT_012854b0 + local_8 * 2) = 0;
  }
  return;
}


// 0053cfe0

void FUN_0053cfe0(void)

{
  BOOL BVar1;
  uint local_520;
  undefined1 local_51c [256];
  undefined1 local_41c [256];
  _cpinfo local_31c;
  undefined1 local_308 [256];
  ushort local_208 [256];
  BYTE *local_8;
  
  BVar1 = GetCPInfo(DAT_0128542c,&local_31c);
  if (BVar1 == 1) {
    for (local_520 = 0; local_520 < 0x100; local_520 = local_520 + 1) {
      local_308[local_520] = (undefined1)local_520;
    }
    local_308[0] = 0x20;
    for (local_8 = local_31c.LeadByte; *local_8 != 0; local_8 = local_8 + 2) {
      for (local_520 = (uint)*local_8; local_520 <= local_8[1]; local_520 = local_520 + 1) {
        local_308[local_520] = 0x20;
      }
    }
    FUN_0053af10(1,local_308,0x100,local_208,DAT_0128542c,DAT_012856c4,0);
    FUN_00531fa0(DAT_012856c4,0x100,local_308,0x100,local_41c,0x100,DAT_0128542c,0);
    FUN_00531fa0(DAT_012856c4,0x200,local_308,0x100,local_51c,0x100,DAT_0128542c,0);
    for (local_520 = 0; local_520 < 0x100; local_520 = local_520 + 1) {
      if ((local_208[local_520] & 1) == 0) {
        if ((local_208[local_520] & 2) == 0) {
          (&DAT_012854c0)[local_520] = 0;
        }
        else {
          (&DAT_012855c1)[local_520] = (&DAT_012855c1)[local_520] | 0x20;
          (&DAT_012854c0)[local_520] = local_51c[local_520];
        }
      }
      else {
        (&DAT_012855c1)[local_520] = (&DAT_012855c1)[local_520] | 0x10;
        (&DAT_012854c0)[local_520] = local_41c[local_520];
      }
    }
  }
  else {
    for (local_520 = 0; local_520 < 0x100; local_520 = local_520 + 1) {
      if ((local_520 < 0x41) || (0x5a < local_520)) {
        if ((local_520 < 0x61) || (0x7a < local_520)) {
          (&DAT_012854c0)[local_520] = 0;
        }
        else {
          (&DAT_012855c1)[local_520] = (&DAT_012855c1)[local_520] | 0x20;
          (&DAT_012854c0)[local_520] = (char)local_520 + -0x20;
        }
      }
      else {
        (&DAT_012855c1)[local_520] = (&DAT_012855c1)[local_520] | 0x10;
        (&DAT_012854c0)[local_520] = (char)local_520 + ' ';
      }
    }
  }
  return;
}


// 0053d2f0

undefined4 FUN_0053d2f0(void)

{
  undefined4 uVar1;
  
  uVar1 = DAT_0128542c;
  if (DAT_012854bc == 0) {
    uVar1 = 0;
  }
  return uVar1;
}


// 0053d310

void FUN_0053d310(void)

{
  if (DAT_01286bc8 == 0) {
    FUN_0053cb80(0xfffffffd);
    DAT_01286bc8 = 1;
  }
  return;
}


// 0053d340

int FUN_0053d340(void)

{
  int iVar1;
  undefined4 local_c;
  undefined4 local_8;
  
  local_8 = 0;
  for (local_c = 3; local_c < DAT_01286a20; local_c = local_c + 1) {
    if (*(int *)(DAT_012856c8 + local_c * 4) != 0) {
      if ((*(uint *)(*(int *)(DAT_012856c8 + local_c * 4) + 0xc) & 0x83) != 0) {
        iVar1 = FUN_0052aa10(*(undefined4 *)(DAT_012856c8 + local_c * 4));
        if (iVar1 != -1) {
          local_8 = local_8 + 1;
        }
      }
      if (0x13 < local_c) {
        FUN_0052cb90(*(undefined4 *)(DAT_012856c8 + local_c * 4),2);
        *(undefined4 *)(DAT_012856c8 + local_c * 4) = 0;
      }
    }
  }
  return local_8;
}


// 0053d3f0

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

int FUN_0053d3f0(uint param_1,int param_2)

{
  code *pcVar1;
  int iVar2;
  HANDLE hFile;
  BOOL BVar3;
  int local_1020;
  int local_101c;
  undefined1 local_1008 [4064];
  undefined4 uStackY_28;
  undefined4 uStackY_24;
  char *pcStackY_20;
  
  FUN_00538c10();
  local_1020 = 0;
  if ((param_1 < DAT_01286b9c) &&
     ((*(byte *)((&DAT_01286a60)[(int)param_1 >> 5] + 4 + (param_1 & 0x1f) * 8) & 1) != 0)) {
    if (param_2 < 0) {
      pcStackY_20 = "chsize.c";
      uStackY_24 = 2;
      uStackY_28 = 0x53d470;
      iVar2 = FUN_0052fad0();
      if (iVar2 == 1) {
        pcVar1 = (code *)swi(3);
        iVar2 = (*pcVar1)();
        return iVar2;
      }
    }
    pcStackY_20 = (char *)0x53d48c;
    iVar2 = FUN_00531eb0();
    if (iVar2 != -1) {
      pcStackY_20 = (char *)0x53d4ab;
      local_101c = FUN_00531eb0();
      if (local_101c != -1) {
        local_101c = param_2 - local_101c;
        if (local_101c < 1) {
          if (local_101c < 0) {
            pcStackY_20 = (char *)0x53d5f2;
            FUN_00531eb0();
            hFile = (HANDLE)FUN_005393e0();
            BVar3 = SetEndOfFile(hFile);
            local_1020 = (BVar3 != 0) - 1;
            if (local_1020 == -1) {
              _DAT_00b94050 = 0xd;
              DAT_00b94054 = GetLastError();
            }
          }
        }
        else {
          pcStackY_20 = (char *)0x53d4f4;
          _memset(local_1008,0,0x1000);
          FUN_0053f070();
          do {
            pcStackY_20 = (char *)0x53d576;
            iVar2 = FUN_00531800();
            if (iVar2 == -1) {
              if (DAT_00b94054 == 5) {
                _DAT_00b94050 = 0xd;
              }
              local_1020 = -1;
              break;
            }
            local_101c = local_101c - iVar2;
          } while (0 < local_101c);
          FUN_0053f070();
        }
        pcStackY_20 = (char *)0x53d645;
        FUN_00531eb0();
        return local_1020;
      }
    }
  }
  else {
    _DAT_00b94050 = 9;
  }
  return -1;
}


// 0053d660

/* Library Function - Single Match
    ___addl
   
   Library: Visual Studio 2012 Debug */

undefined4 ___addl(uint param_1,uint param_2,uint *param_3)

{
  uint uVar1;
  undefined4 local_c;
  
  local_c = 0;
  uVar1 = param_1 + param_2;
  if ((uVar1 < param_1) || (uVar1 < param_2)) {
    local_c = 1;
  }
  *param_3 = uVar1;
  return local_c;
}


// 0053d6a0

/* Library Function - Single Match
    ___add_12
   
   Library: Visual Studio */

void ___add_12(undefined4 *param_1,undefined4 *param_2)

{
  int iVar1;
  
  iVar1 = ___addl(*param_1,*param_2,param_1);
  if (iVar1 != 0) {
    iVar1 = ___addl(param_1[1],1,param_1 + 1);
    if (iVar1 != 0) {
      param_1[2] = param_1[2] + 1;
    }
  }
  iVar1 = ___addl(param_1[1],param_2[1],param_1 + 1);
  if (iVar1 != 0) {
    param_1[2] = param_1[2] + 1;
  }
  ___addl(param_1[2],param_2[2],param_1 + 2);
  return;
}


// 0053d750

/* Library Function - Single Match
    ___shl_12
   
   Libraries: Visual Studio 2003, Visual Studio 2005, Visual Studio 2008, Visual Studio 2010 */

void ___shl_12(uint *param_1)

{
  uint uVar1;
  uint uVar2;
  
  uVar1 = *param_1;
  uVar2 = param_1[1];
  *param_1 = *param_1 << 1;
  param_1[1] = param_1[1] << 1 | (uint)((uVar1 & 0x80000000) != 0);
  param_1[2] = param_1[2] << 1 | (uint)((uVar2 & 0x80000000) != 0);
  return;
}


// 0053d7b0

/* Library Function - Single Match
    ___shr_12
   
   Libraries: Visual Studio 2003, Visual Studio 2005, Visual Studio 2008, Visual Studio 2010 */

void ___shr_12(uint *param_1)

{
  uint uVar1;
  uint uVar2;
  
  uVar1 = param_1[2];
  uVar2 = param_1[1];
  param_1[2] = param_1[2] >> 1;
  param_1[1] = param_1[1] >> 1 | -(uint)((uVar1 & 1) != 0) & 0x80000000;
  *param_1 = *param_1 >> 1 | -(uint)((uVar2 & 1) != 0) & 0x80000000;
  return;
}


// 0053d820

void FUN_0053d820(char *param_1,int param_2,uint *param_3)

{
  short local_14;
  uint local_10;
  uint local_c;
  uint local_8;
  
  local_14 = 0x404e;
  *param_3 = 0;
  param_3[1] = 0;
  param_3[2] = 0;
  for (; param_2 != 0; param_2 = param_2 + -1) {
    local_10 = *param_3;
    local_c = param_3[1];
    local_8 = param_3[2];
    ___shl_12(param_3);
    ___shl_12(param_3);
    ___add_12(param_3,&local_10);
    ___shl_12(param_3);
    local_10 = (uint)*param_1;
    local_c = 0;
    local_8 = 0;
    ___add_12(param_3,&local_10);
    param_1 = param_1 + 1;
  }
  while (param_3[2] == 0) {
    param_3[2] = param_3[1] >> 0x10;
    param_3[1] = param_3[1] << 0x10 | *param_3 >> 0x10;
    *param_3 = *param_3 << 0x10;
    local_14 = local_14 + -0x10;
  }
  while ((param_3[2] & 0x8000) == 0) {
    ___shl_12(param_3);
    local_14 = local_14 + -1;
  }
  *(short *)((int)param_3 + 10) = local_14;
  return;
}


// 0053d960

uint FUN_0053d960(undefined2 *param_1,undefined4 *param_2,byte *param_3,undefined4 param_4,
                 int param_5,int param_6,int param_7)

{
  byte bVar1;
  bool bVar2;
  byte *pbVar3;
  uint uStack_b4;
  uint uStack_b0;
  uint uStack_a4;
  uint uStack_9c;
  uint uStack_94;
  int iStack_80;
  int local_78;
  uint local_74;
  int local_70;
  char *local_6c;
  byte *local_68;
  undefined2 local_64;
  undefined4 local_62;
  undefined4 local_5e;
  ushort local_5a;
  int local_58;
  ushort local_54;
  int local_50;
  undefined2 local_4c;
  uint local_48;
  int local_44;
  uint local_40;
  char local_3c [23];
  char local_25;
  undefined4 local_20;
  int local_1c;
  int local_18;
  undefined4 local_14;
  int local_10;
  undefined4 local_c;
  byte *local_8;
  
  local_6c = local_3c;
  local_20 = local_20 & 0xffff0000;
  local_78 = 1;
  local_74 = 0;
  local_58 = 0;
  local_10 = 0;
  local_1c = 0;
  local_44 = 0;
  bVar2 = false;
  local_18 = 0;
  local_70 = 0;
  local_48 = 0;
  local_50 = 0;
  local_68 = param_3;
  for (local_8 = param_3;
      (((*local_8 == 0x20 || (*local_8 == 9)) || (*local_8 == 10)) || (*local_8 == 0xd));
      local_8 = local_8 + 1) {
  }
  do {
    if (local_50 == 10) {
      *param_2 = local_8;
      if ((local_58 != 0) && (local_44 == 0)) {
        if (0x18 < local_74) {
          if ('\x04' < local_25) {
            local_25 = local_25 + '\x01';
          }
          local_74 = 0x18;
          local_6c = local_6c + -1;
          local_70 = local_70 + 1;
        }
        if (local_74 == 0) {
          local_4c = 0;
          local_54 = 0;
          local_14 = 0;
          local_c = 0;
        }
        else {
          while (local_6c = local_6c + -1, *local_6c == '\0') {
            local_74 = local_74 - 1;
            local_70 = local_70 + 1;
          }
          FUN_0053d820(local_3c,local_74,&local_64);
          if (local_78 < 0) {
            local_18 = -local_18;
          }
          local_18 = local_18 + local_70;
          if (local_1c == 0) {
            local_18 = local_18 + param_5;
          }
          if (local_10 == 0) {
            local_18 = local_18 - param_6;
          }
          if (local_18 < 0x1451) {
            if (local_18 < -0x1450) {
              bVar2 = true;
            }
            else {
              FUN_0053f5b0(&local_64,local_18,param_4);
              local_4c = local_64;
              local_c = local_62;
              local_14 = local_5e;
              local_54 = local_5a;
            }
          }
          else {
            local_44 = 1;
          }
        }
      }
      if (local_58 == 0) {
        local_4c = 0;
        local_54 = 0;
        local_14 = 0;
        local_c = 0;
        local_48 = local_48 | 4;
      }
      else if (local_44 == 0) {
        if (bVar2) {
          local_4c = 0;
          local_54 = 0;
          local_14 = 0;
          local_c = 0;
          local_48 = local_48 | 1;
        }
      }
      else {
        local_54 = 0x7fff;
        local_14 = 0x80000000;
        local_c = 0;
        local_4c = 0;
        local_48 = local_48 | 2;
      }
      *param_1 = local_4c;
      *(undefined4 *)(param_1 + 1) = local_c;
      *(undefined4 *)(param_1 + 3) = local_14;
      param_1[5] = local_54 | (ushort)local_20;
      return local_48;
    }
    bVar1 = *local_8;
    local_40 = CONCAT31(local_40._1_3_,bVar1);
    pbVar3 = local_8 + 1;
    switch(local_50) {
    case 0:
      if (((char)bVar1 < '1') || ('9' < (char)bVar1)) {
        if (bVar1 == DAT_0057a600) {
          local_50 = 5;
        }
        else if (bVar1 == 0x2b) {
          local_50 = 2;
          local_20 = (uint)local_20._2_2_ << 0x10;
        }
        else if (bVar1 == 0x2d) {
          local_50 = 2;
          local_20 = CONCAT22(local_20._2_2_,0x8000);
        }
        else if (bVar1 == 0x30) {
          local_50 = 1;
        }
        else {
          local_50 = 10;
          pbVar3 = local_8;
        }
      }
      else {
        local_50 = 3;
        pbVar3 = local_8;
      }
      break;
    case 1:
      local_58 = 1;
      if (((char)bVar1 < '1') || ('9' < (char)bVar1)) {
        if (bVar1 == DAT_0057a600) {
          local_50 = 4;
        }
        else {
          switch(bVar1) {
          case 0x2b:
          case 0x2d:
            local_50 = 0xb;
            pbVar3 = local_8;
            break;
          default:
            local_50 = 10;
            pbVar3 = local_8;
            break;
          case 0x30:
            local_50 = 1;
            break;
          case 0x44:
          case 0x45:
          case 100:
          case 0x65:
            local_50 = 6;
          }
        }
      }
      else {
        local_50 = 3;
        pbVar3 = local_8;
      }
      break;
    case 2:
      if (((char)bVar1 < '1') || ('9' < (char)bVar1)) {
        if (bVar1 == DAT_0057a600) {
          local_50 = 5;
        }
        else if (bVar1 == 0x30) {
          local_50 = 1;
        }
        else {
          local_50 = 10;
          local_8 = local_68;
          pbVar3 = local_8;
        }
      }
      else {
        local_50 = 3;
        pbVar3 = local_8;
      }
      break;
    case 3:
      local_58 = 1;
      local_8 = pbVar3;
      while( true ) {
        if (DAT_0057a5fc < 2) {
          uStack_94 = *(ushort *)(PTR_DAT_0057a3f0 + (local_40 & 0xff) * 2) & 4;
        }
        else {
          uStack_94 = FUN_00532300(local_40 & 0xff,4);
        }
        if (uStack_94 == 0) break;
        if (local_74 < 0x19) {
          local_74 = local_74 + 1;
          *local_6c = (char)local_40 + -0x30;
          local_6c = local_6c + 1;
        }
        else {
          local_70 = local_70 + 1;
        }
        local_40 = CONCAT31(local_40._1_3_,*local_8);
        local_8 = local_8 + 1;
      }
      pbVar3 = local_8;
      if ((char)local_40 == DAT_0057a600) {
        local_50 = 4;
      }
      else {
        switch((char)local_40) {
        case '+':
        case '-':
          local_50 = 0xb;
          pbVar3 = local_8 + -1;
          break;
        default:
          local_50 = 10;
          pbVar3 = local_8 + -1;
          break;
        case 'D':
        case 'E':
        case 'd':
        case 'e':
          local_50 = 6;
        }
      }
      break;
    case 4:
      local_58 = 1;
      local_10 = 1;
      local_8 = pbVar3;
      if (local_74 == 0) {
        while ((char)local_40 == '0') {
          local_70 = local_70 + -1;
          local_40 = CONCAT31(local_40._1_3_,*local_8);
          local_8 = local_8 + 1;
        }
      }
      while( true ) {
        if (DAT_0057a5fc < 2) {
          uStack_9c = *(ushort *)(PTR_DAT_0057a3f0 + (local_40 & 0xff) * 2) & 4;
        }
        else {
          uStack_9c = FUN_00532300(local_40 & 0xff,4);
        }
        if (uStack_9c == 0) break;
        if (local_74 < 0x19) {
          local_74 = local_74 + 1;
          *local_6c = (char)local_40 + -0x30;
          local_6c = local_6c + 1;
          local_70 = local_70 + -1;
        }
        local_40 = CONCAT31(local_40._1_3_,*local_8);
        local_8 = local_8 + 1;
      }
      switch((char)local_40) {
      case '+':
      case '-':
        local_50 = 0xb;
        pbVar3 = local_8 + -1;
        break;
      default:
        local_50 = 10;
        pbVar3 = local_8 + -1;
        break;
      case 'D':
      case 'E':
      case 'd':
      case 'e':
        local_50 = 6;
        pbVar3 = local_8;
      }
      break;
    case 5:
      local_10 = 1;
      if (DAT_0057a5fc < 2) {
        uStack_a4 = *(ushort *)(PTR_DAT_0057a3f0 + (uint)bVar1 * 2) & 4;
        local_8 = pbVar3;
      }
      else {
        local_8 = pbVar3;
        uStack_a4 = FUN_00532300(bVar1,4);
      }
      if (uStack_a4 == 0) {
        local_50 = 10;
        local_8 = local_68;
        pbVar3 = local_8;
      }
      else {
        local_50 = 4;
        pbVar3 = local_8 + -1;
      }
      break;
    case 6:
      local_68 = local_8 + -1;
      if (((char)bVar1 < '1') || ('9' < (char)bVar1)) {
        if (bVar1 == 0x2b) {
          local_50 = 7;
        }
        else if (bVar1 == 0x2d) {
          local_50 = 7;
          local_78 = -1;
        }
        else if (bVar1 == 0x30) {
          local_50 = 8;
        }
        else {
          local_50 = 10;
          pbVar3 = local_68;
        }
      }
      else {
        local_50 = 9;
        pbVar3 = local_8;
      }
      break;
    case 7:
      if (((char)bVar1 < '1') || ('9' < (char)bVar1)) {
        if (bVar1 == 0x30) {
          local_50 = 8;
        }
        else {
          local_50 = 10;
          local_8 = local_68;
          pbVar3 = local_8;
        }
      }
      else {
        local_50 = 9;
        pbVar3 = local_8;
      }
      break;
    case 8:
      local_1c = 1;
      local_8 = pbVar3;
      while ((char)local_40 == '0') {
        bVar1 = *local_8;
        local_8 = local_8 + 1;
        local_40 = CONCAT31(local_40._1_3_,bVar1);
      }
      if (((char)local_40 < '1') || ('9' < (char)local_40)) {
        local_50 = 10;
      }
      else {
        local_50 = 9;
      }
      local_8 = local_8 + -1;
      pbVar3 = local_8;
      break;
    case 9:
      local_1c = 1;
      iStack_80 = 0;
      local_8 = pbVar3;
      while( true ) {
        if (DAT_0057a5fc < 2) {
          uStack_b0 = *(ushort *)(PTR_DAT_0057a3f0 + (local_40 & 0xff) * 2) & 4;
        }
        else {
          uStack_b0 = FUN_00532300(local_40 & 0xff,4);
        }
        if (uStack_b0 == 0) goto code_r0x0053e087;
        iStack_80 = iStack_80 * 10 + -0x30 + (int)(char)local_40;
        if (0x1450 < iStack_80) break;
        local_40 = CONCAT31(local_40._1_3_,*local_8);
        local_8 = local_8 + 1;
      }
      iStack_80 = 0x1451;
code_r0x0053e087:
      local_18 = iStack_80;
      while( true ) {
        if (DAT_0057a5fc < 2) {
          uStack_b4 = *(ushort *)(PTR_DAT_0057a3f0 + (local_40 & 0xff) * 2) & 4;
        }
        else {
          uStack_b4 = FUN_00532300(local_40 & 0xff,4);
        }
        if (uStack_b4 == 0) break;
        local_40 = CONCAT31(local_40._1_3_,*local_8);
        local_8 = local_8 + 1;
      }
      local_50 = 10;
      pbVar3 = local_8 + -1;
      break;
    case 0xb:
      if (param_7 == 0) {
        local_50 = 10;
        pbVar3 = local_8;
      }
      else {
        local_68 = local_8;
        if (bVar1 == 0x2b) {
          local_50 = 7;
        }
        else if (bVar1 == 0x2d) {
          local_50 = 7;
          local_78 = -1;
        }
        else {
          local_50 = 10;
          pbVar3 = local_8;
        }
      }
    }
    local_8 = pbVar3;
  } while( true );
}


// 0053e490

uint FUN_0053e490(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  int iVar1;
  uint local_18;
  undefined1 local_10 [12];
  
  local_18 = FUN_0053d960(local_10,param_2,param_3,param_4,0,0,0);
  iVar1 = FUN_0053a750(local_10,param_1);
  if (iVar1 == 1) {
    local_18 = local_18 | 2;
  }
  return local_18;
}


// 0053e4e0

undefined4
FUN_0053e4e0(int param_1,uint param_2,ushort param_3,int param_4,uint param_5,short *param_6)

{
  int iVar1;
  ushort uVar2;
  char *pcVar3;
  uint local_78;
  short local_60;
  undefined4 local_5c;
  undefined1 local_58;
  undefined1 local_57;
  undefined1 local_56;
  undefined1 local_55;
  undefined1 local_54;
  undefined1 local_53;
  undefined1 local_52;
  undefined1 local_51;
  undefined1 local_50;
  undefined1 local_4f;
  undefined1 local_4e;
  undefined1 local_4d;
  int local_4c;
  int local_48;
  ushort local_44;
  undefined2 uStack_42;
  undefined2 local_40;
  undefined2 uStack_3e;
  undefined2 local_3c;
  undefined2 uStack_3a;
  undefined2 uStack_38;
  undefined2 uStack_36;
  undefined2 uStack_34;
  undefined1 local_32;
  char cStack_31;
  undefined2 uStack_30;
  undefined1 uStack_2e;
  char cStack_2d;
  uint local_28;
  undefined4 local_24;
  undefined4 local_20;
  undefined4 local_1c;
  undefined4 local_18;
  int local_14;
  ushort local_10;
  int local_c;
  short *local_8;
  
  _local_40 = CONCAT22(uStack_3e,0x4d);
  local_24 = 0x134312f4;
  local_58 = 0xcc;
  local_57 = 0xcc;
  local_56 = 0xcc;
  local_55 = 0xcc;
  local_54 = 0xcc;
  local_53 = 0xcc;
  local_52 = 0xcc;
  local_51 = 0xcc;
  local_50 = 0xcc;
  local_4f = 0xcc;
  local_4e = 0xfb;
  local_4d = 0x3f;
  local_5c = 1;
  local_28 = param_2;
  local_4c = param_1;
  if ((param_3 & 0x8000) == 0) {
    *(undefined1 *)(param_6 + 1) = 0x20;
  }
  else {
    *(undefined1 *)(param_6 + 1) = 0x2d;
  }
  if ((((param_3 & 0x7fff) == 0) && (param_2 == 0)) && (param_1 == 0)) {
    *param_6 = 0;
    *(undefined1 *)(param_6 + 1) = 0x20;
    *(undefined1 *)((int)param_6 + 3) = 1;
    *(undefined1 *)(param_6 + 2) = 0x30;
    *(undefined1 *)((int)param_6 + 5) = 0;
    local_5c = 1;
  }
  else if ((param_3 & 0x7fff) == 0x7fff) {
    *param_6 = 1;
    if (((param_2 == 0x80000000) && (param_1 == 0)) || ((param_2 & 0x40000000) != 0)) {
      if ((((param_3 & 0x8000) == 0) || (param_2 != 0xc0000000)) || (param_1 != 0)) {
        if ((param_2 == 0x80000000) && (param_1 == 0)) {
          FUN_0052b100(param_6 + 2,"1#INF");
          *(undefined1 *)((int)param_6 + 3) = 5;
        }
        else {
          FUN_0052b100(param_6 + 2,"1#QNAN");
          *(undefined1 *)((int)param_6 + 3) = 6;
        }
      }
      else {
        FUN_0052b100(param_6 + 2,"1#IND");
        *(undefined1 *)((int)param_6 + 3) = 5;
      }
    }
    else {
      FUN_0052b100(param_6 + 2,"1#SNAN");
      *(undefined1 *)((int)param_6 + 3) = 6;
    }
    local_5c = 0;
  }
  else {
    local_10 = param_3 & 0xff;
    uVar2 = (ushort)(byte)(param_2 >> 0x18);
    _local_44 = CONCAT22(uStack_42,uVar2);
    local_c = (param_3 & 0x7fff) * 0x4d10 + (uint)(param_3 >> 8 & 0x7f) * 0x4d + (uint)uVar2 * 0x9a
              + -0x134312f4;
    local_60 = (short)((uint)local_c >> 0x10);
    local_32 = (undefined1)(param_3 & 0x7fff);
    cStack_31 = (char)((param_3 & 0x7fff) >> 8);
    uStack_36 = (undefined2)param_2;
    uStack_34 = (undefined2)(param_2 >> 0x10);
    uStack_3a = (undefined2)param_1;
    uStack_38 = (undefined2)((uint)param_1 >> 0x10);
    local_3c = 0;
    FUN_0053f5b0(&local_3c,-(int)local_60,1);
    if (0x3ffe < CONCAT11(cStack_31,local_32)) {
      local_60 = local_60 + 1;
      FUN_0053f170(&local_3c,&local_58);
    }
    *param_6 = local_60;
    if (((param_5 & 1) == 0) || (param_4 = param_4 + local_60, 0 < param_4)) {
      if (0x15 < param_4) {
        param_4 = 0x15;
      }
      iVar1 = CONCAT11(cStack_31,local_32) - 0x3ffe;
      uStack_30 = (undefined2)iVar1;
      uStack_2e = (undefined1)((uint)iVar1 >> 0x10);
      cStack_2d = (char)((uint)iVar1 >> 0x18);
      local_32 = 0;
      cStack_31 = '\0';
      for (local_48 = 0; local_48 < 8; local_48 = local_48 + 1) {
        ___shl_12(&local_3c);
      }
      if (cStack_2d < '\0') {
        for (local_78 = -CONCAT13(cStack_2d,CONCAT12(uStack_2e,uStack_30)) & 0xff; 0 < (int)local_78
            ; local_78 = local_78 - 1) {
          ___shr_12(&local_3c);
        }
      }
      local_8 = param_6 + 2;
      for (local_14 = param_4 + 1; 0 < local_14; local_14 = local_14 + -1) {
        local_20 = CONCAT22(uStack_3a,local_3c);
        local_1c = CONCAT22(uStack_36,uStack_38);
        local_18 = CONCAT13(cStack_31,CONCAT12(local_32,uStack_34));
        ___shl_12(&local_3c);
        ___shl_12(&local_3c);
        ___add_12(&local_3c,&local_20);
        ___shl_12(&local_3c);
        *(char *)local_8 = cStack_31 + '0';
        local_8 = (short *)((int)local_8 + 1);
        cStack_31 = '\0';
      }
      pcVar3 = (char *)((int)local_8 + -1);
      local_8 = local_8 + -1;
      if (*pcVar3 < '5') {
        for (; (param_6 + 2 <= local_8 && ((char)*local_8 == '0'));
            local_8 = (short *)((int)local_8 + -1)) {
        }
        if (local_8 < param_6 + 2) {
          *param_6 = 0;
          *(undefined1 *)(param_6 + 1) = 0x20;
          *(undefined1 *)((int)param_6 + 3) = 1;
          *(undefined1 *)(param_6 + 2) = 0x30;
          *(undefined1 *)((int)param_6 + 5) = 0;
          return 1;
        }
      }
      else {
        for (; (param_6 + 2 <= local_8 && ((char)*local_8 == '9'));
            local_8 = (short *)((int)local_8 + -1)) {
          *(char *)local_8 = '0';
        }
        if (local_8 < param_6 + 2) {
          local_8 = (short *)((int)local_8 + 1);
          *param_6 = *param_6 + 1;
        }
        *(char *)local_8 = (char)*local_8 + '\x01';
      }
      *(char *)((int)param_6 + 3) = ((char)local_8 - ((char)param_6 + '\x04')) + '\x01';
      *(undefined1 *)((int)param_6 + *(char *)((int)param_6 + 3) + 4) = 0;
    }
    else {
      *param_6 = 0;
      *(undefined1 *)(param_6 + 1) = 0x20;
      *(undefined1 *)((int)param_6 + 3) = 1;
      *(undefined1 *)(param_6 + 2) = 0x30;
      *(undefined1 *)((int)param_6 + 5) = 0;
      local_5c = 1;
    }
  }
  return local_5c;
}


// 0053ea00

float10 FUN_0053ea00(double param_1)

{
  return (float10)ROUND(param_1);
}


// 0053ea20

/* Library Function - Single Match
    __copysign
   
   Libraries: Visual Studio 2003 Debug, Visual Studio 2003 Release */

double __cdecl __copysign(double _Number,double _Sign)

{
  return (double)CONCAT44(_Number._4_4_ & 0x7fffffff | _Sign._4_4_ & 0x80000000,_Number._0_4_);
}


// 0053ea50

/* Library Function - Single Match
    __chgsign
   
   Libraries: Visual Studio 2003 Debug, Visual Studio 2003 Release */

double __cdecl __chgsign(double _X)

{
  return (double)CONCAT44(_X._4_4_ & 0x7fffffff | ~_X._4_4_ & 0x80000000,_X._0_4_);
}


// 0053ea80

void FUN_0053ea80(undefined4 param_1,undefined4 param_2,undefined4 param_3)

{
  FUN_0053f680(param_1,param_2,param_3);
  return;
}


// 0053eaa0

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

float10 FUN_0053eaa0(undefined4 param_1,undefined4 param_2)

{
  int iVar1;
  float10 fVar2;
  int local_c;
  undefined4 local_8;
  
  local_8 = FUN_00535900();
  if ((param_2._2_2_ & 0x7ff0) != 0x7ff0) {
    if ((double)CONCAT26(param_2._2_2_,CONCAT24((undefined2)param_2,param_1)) == _DAT_00546090) {
      fVar2 = (float10)FUN_00534a90(4,0x25,param_1,param_2,-_DAT_0057a728,local_8);
      return fVar2;
    }
    FUN_00535780(param_1,param_2,&local_c);
    FUN_00535900();
    return (float10)(local_c + -1);
  }
  iVar1 = FUN_00535700();
  if (0 < iVar1) {
    if (iVar1 < 3) {
      FUN_00535900();
      return (float10)(double)CONCAT26(param_2._2_2_,CONCAT24((undefined2)param_2,param_1));
    }
    if (iVar1 == 3) {
      fVar2 = (float10)FUN_005349c0(0x25,param_1,param_2,local_8);
      return fVar2;
    }
  }
  fVar2 = (float10)FUN_00534a90(8,0x25,param_1,param_2,
                                (double)CONCAT26(param_2._2_2_,CONCAT24((undefined2)param_2,param_1)
                                                ) + _DAT_005460b8,local_8);
  return fVar2;
}


// 0053ebd0

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

float10 FUN_0053ebd0(int param_1,uint param_2,int param_3,uint param_4)

{
  double dVar1;
  undefined4 unaff_EBP;
  float10 fVar2;
  int local_20;
  double local_1c;
  int local_14;
  undefined4 local_10;
  int local_c;
  undefined4 uStack_8;
  undefined2 uStack_4;
  undefined2 uStack_2;
  
  uStack_4 = (undefined2)unaff_EBP;
  uStack_2 = (undefined2)((uint)unaff_EBP >> 0x10);
  local_10 = FUN_00535900();
  if (((param_2._2_2_ & 0x7ff0) == 0x7ff0) || ((param_4._2_2_ & 0x7ff0) == 0x7ff0)) {
    if ((((param_2._2_2_ & 0x7ff8) == 0x7ff0) && (((param_2 & 0x7ffff) != 0 || (param_1 != 0)))) ||
       (((param_4._2_2_ & 0x7ff8) == 0x7ff0 && (((param_4 & 0x7ffff) != 0 || (param_3 != 0)))))) {
      fVar2 = (float10)FUN_00534b50(8,0x26,param_1,param_2,param_3,param_4,
                                    (double)CONCAT26(param_2._2_2_,
                                                     CONCAT24((undefined2)param_2,param_1)) +
                                    (double)CONCAT26(param_4._2_2_,
                                                     CONCAT24((undefined2)param_4,param_3)),local_10
                                   );
      return fVar2;
    }
    if (((param_2._2_2_ & 0x7ff8) == 0x7ff8) || ((param_4._2_2_ & 0x7ff8) == 0x7ff8)) {
      fVar2 = (float10)FUN_00534a20(0x26,param_1,param_2,param_3,param_4,local_10);
      return fVar2;
    }
  }
  if ((double)CONCAT26(param_4._2_2_,CONCAT24((undefined2)param_4,param_3)) ==
      (double)CONCAT26(param_2._2_2_,CONCAT24((undefined2)param_2,param_1))) {
    FUN_00535900();
    fVar2 = (float10)(double)CONCAT26(param_2._2_2_,CONCAT24((undefined2)param_2,param_1));
  }
  else {
    if ((double)CONCAT26(param_2._2_2_,CONCAT24((undefined2)param_2,param_1)) == _DAT_00546090) {
      local_c = 1;
      if ((double)CONCAT26(param_4._2_2_,CONCAT24((undefined2)param_4,param_3)) <=
          (double)CONCAT26(param_2._2_2_,CONCAT24((undefined2)param_2,param_1))) {
        uStack_8._0_2_ = 0;
        uStack_8._2_2_ = 0x8000;
      }
      else {
        uStack_8._0_2_ = 0;
        uStack_8._2_2_ = 0;
      }
    }
    if (((_DAT_00546090 < (double)CONCAT26(param_2._2_2_,CONCAT24((undefined2)param_2,param_1))) &&
        ((double)CONCAT26(param_4._2_2_,CONCAT24((undefined2)param_4,param_3)) <
         (double)CONCAT26(param_2._2_2_,CONCAT24((undefined2)param_2,param_1)))) ||
       (((double)CONCAT26(param_2._2_2_,CONCAT24((undefined2)param_2,param_1)) < _DAT_00546090 &&
        ((double)CONCAT26(param_2._2_2_,CONCAT24((undefined2)param_2,param_1)) <
         (double)CONCAT26(param_4._2_2_,CONCAT24((undefined2)param_4,param_3)))))) {
      local_c = param_1 + -1;
      uStack_8 = param_2;
      if (param_1 == 0) {
        uStack_8 = param_2 - 1;
      }
    }
    else if ((((_DAT_00546090 <
                (double)CONCAT26(param_2._2_2_,CONCAT24((undefined2)param_2,param_1))) &&
              ((double)CONCAT26(param_2._2_2_,CONCAT24((undefined2)param_2,param_1)) <
               (double)CONCAT26(param_4._2_2_,CONCAT24((undefined2)param_4,param_3)))) ||
             ((uStack_8 = CONCAT22(uStack_8._2_2_,(undefined2)uStack_8),
              (double)CONCAT26(param_2._2_2_,CONCAT24((undefined2)param_2,param_1)) < _DAT_00546090
              && (uStack_8 = CONCAT22(uStack_8._2_2_,(undefined2)uStack_8),
                 (double)CONCAT26(param_4._2_2_,CONCAT24((undefined2)param_4,param_3)) <
                 (double)CONCAT26(param_2._2_2_,CONCAT24((undefined2)param_2,param_1)))))) &&
            (local_c = param_1 + 1, uStack_8 = param_2, local_c == 0)) {
      uStack_8 = param_2 + 1;
    }
    if (((uStack_8 & 0x7ff00000) == 0) && (((uStack_8 & 0xfffff) != 0 || (local_c != 0)))) {
      fVar2 = (float10)FUN_00535780(local_c,uStack_8,&local_14);
      local_1c = (double)fVar2;
      fVar2 = (float10)FUN_00535610(local_1c,local_14 + 0x600);
      dVar1 = (double)fVar2;
      local_c = SUB84(dVar1,0);
      uStack_8._0_2_ = (undefined2)((ulonglong)dVar1 >> 0x20);
      uStack_8._2_2_ = (undefined2)((ulonglong)dVar1 >> 0x30);
      fVar2 = (float10)FUN_00534b50(0x12,0x26,param_1,param_2,param_3,param_4,dVar1,local_10);
    }
    else if (((uStack_8 == 0x7ff00000) && (local_c == 0)) ||
            ((uStack_8 == 0xfff00000 && (local_c == 0)))) {
      fVar2 = (float10)FUN_00535780(local_c,uStack_8,&local_20);
      fVar2 = (float10)FUN_00535610((double)fVar2,local_20 + -0x600);
      dVar1 = (double)fVar2;
      local_c = SUB84(dVar1,0);
      uStack_8._0_2_ = (undefined2)((ulonglong)dVar1 >> 0x20);
      uStack_8._2_2_ = (undefined2)((ulonglong)dVar1 >> 0x30);
      fVar2 = (float10)FUN_00534b50(0x11,0x26,param_1,param_2,param_3,param_4,dVar1,local_10);
    }
    else {
      FUN_00535900();
      fVar2 = (float10)(double)CONCAT26(uStack_8._2_2_,CONCAT24((undefined2)uStack_8,local_c));
    }
  }
  return fVar2;
}


// 0053ef10

bool FUN_0053ef10(undefined4 param_1,undefined8 param_2)

{
  return (param_2._2_4_ & 0x7ff0) != 0x7ff0;
}


// 0053ef40

undefined4 FUN_0053ef40(int param_1,uint param_2)

{
  undefined4 uVar1;
  
  if ((((param_2._2_2_ & 0x7ff8) == 0x7ff0) && (((param_2 & 0x7ffff) != 0 || (param_1 != 0)))) ||
     ((param_2._2_2_ & 0x7ff8) == 0x7ff8)) {
    uVar1 = 1;
  }
  else {
    uVar1 = 0;
  }
  return uVar1;
}


// 0053ef90

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

int FUN_0053ef90(int param_1,uint param_2)

{
  int iVar1;
  
  if ((param_2._2_2_ & 0x7ff0) == 0x7ff0) {
    iVar1 = FUN_00535700(param_1,param_2);
    if (iVar1 == 1) {
      iVar1 = 0x200;
    }
    else if (iVar1 == 2) {
      iVar1 = 4;
    }
    else if (iVar1 == 3) {
      iVar1 = 2;
    }
    else {
      iVar1 = 1;
    }
  }
  else if (((param_2 & 0x7ff00000) == 0) && (((param_2 & 0xfffff) != 0 || (param_1 != 0)))) {
    iVar1 = (-(uint)((param_2 & 0x80000000) != 0) & 0xffffff90) + 0x80;
  }
  else if ((double)CONCAT26(param_2._2_2_,CONCAT24((undefined2)param_2,param_1)) == _DAT_00546090) {
    iVar1 = (-(uint)((param_2 & 0x80000000) != 0) & 0xffffffe0) + 0x40;
  }
  else {
    iVar1 = (-(uint)((param_2 & 0x80000000) != 0) & 0xffffff08) + 0x100;
  }
  return iVar1;
}


// 0053f070

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

int FUN_0053f070(uint param_1,int param_2)

{
  char cVar1;
  int iVar2;
  
  if ((param_1 < DAT_01286b9c) &&
     (iVar2 = (int)param_1 >> 5,
     (*(byte *)((&DAT_01286a60)[iVar2] + 4 + (param_1 & 0x1f) * 8) & 1) != 0)) {
    cVar1 = *(char *)((&DAT_01286a60)[iVar2] + 4 + (param_1 & 0x1f) * 8);
    if (param_2 == 0x8000) {
      *(byte *)((&DAT_01286a60)[iVar2] + 4 + (param_1 & 0x1f) * 8) =
           *(byte *)((&DAT_01286a60)[iVar2] + 4 + (param_1 & 0x1f) * 8) & 0x7f;
    }
    else {
      if (param_2 != 0x4000) {
        _DAT_00b94050 = 0x16;
        return -1;
      }
      *(byte *)((&DAT_01286a60)[iVar2] + 4 + (param_1 & 0x1f) * 8) =
           *(byte *)((&DAT_01286a60)[iVar2] + 4 + (param_1 & 0x1f) * 8) | 0x80;
    }
    iVar2 = (-(uint)(((int)cVar1 & 0x80U) != 0) & 0xffffc000) + 0x8000;
  }
  else {
    _DAT_00b94050 = 9;
    iVar2 = -1;
  }
  return iVar2;
}


// 0053f170

void FUN_0053f170(int *param_1,int *param_2)

{
  ushort uVar1;
  ushort uVar2;
  ushort uVar3;
  int iVar4;
  int iVar5;
  int local_38;
  ushort local_34;
  int local_2c;
  int local_28;
  int local_20;
  ushort local_18;
  undefined2 uStack_16;
  short local_14 [4];
  undefined4 local_c;
  int local_8;
  
  local_8 = 0;
  local_18 = 0;
  uStack_16 = 0;
  local_14[0] = 0;
  local_14[1] = 0;
  local_14[2] = 0;
  local_14[3] = 0;
  uVar1 = *(ushort *)((int)param_1 + 10);
  uVar2 = *(ushort *)((int)param_2 + 10);
  uVar3 = uVar1 ^ uVar2;
  local_34 = (uVar1 & 0x7fff) + (uVar2 & 0x7fff);
  if ((((uVar1 & 0x7fff) < 0x7fff) && ((uVar2 & 0x7fff) < 0x7fff)) && (local_34 < 0xbffe)) {
    if (local_34 < 0x3fc0) {
      param_1[2] = 0;
      param_1[1] = 0;
      *param_1 = 0;
    }
    else if ((((uVar1 & 0x7fff) == 0) && (local_34 = local_34 + 1, (param_1[2] & 0x7fffffffU) == 0))
            && ((param_1[1] == 0 && (*param_1 == 0)))) {
      *(undefined2 *)((int)param_1 + 10) = 0;
    }
    else if ((((uVar2 & 0x7fff) == 0) && (local_34 = local_34 + 1, (param_2[2] & 0x7fffffffU) == 0))
            && ((param_2[1] == 0 && (*param_2 == 0)))) {
      param_1[2] = 0;
      param_1[1] = 0;
      *param_1 = 0;
    }
    else {
      local_2c = 0;
      for (local_20 = 0; local_20 < 5; local_20 = local_20 + 1) {
        local_28 = local_20 << 1;
        local_c = 8;
        for (local_38 = 5 - local_20; 0 < local_38; local_38 = local_38 + -1) {
          iVar4 = ___addl(*(undefined4 *)((int)&local_18 + local_2c),
                          (uint)*(ushort *)((int)param_1 + local_28) *
                          (uint)*(ushort *)((int)param_2 + local_c),
                          (undefined4 *)((int)&local_18 + local_2c));
          if (iVar4 != 0) {
            *(short *)((int)local_14 + local_2c) = *(short *)((int)local_14 + local_2c) + 1;
          }
          local_28 = local_28 + 2;
          local_c = local_c + -2;
        }
        local_2c = local_2c + 2;
      }
      local_34 = local_34 + 0xc002;
      while ((0 < (short)local_34 && ((local_14[3] & 0x8000U) == 0))) {
        ___shl_12(&local_18);
        local_34 = local_34 - 1;
      }
      if ((short)local_34 < 1) {
        for (local_34 = local_34 - 1; (short)local_34 < 0; local_34 = local_34 + 1) {
          if ((local_18 & 1) != 0) {
            local_8 = local_8 + 1;
          }
          ___shr_12(&local_18);
        }
        if (local_8 != 0) {
          local_18 = local_18 | 1;
        }
      }
      iVar4 = CONCAT22(local_14[0],uStack_16);
      if ((0x8000 < local_18) ||
         (iVar5 = CONCAT22(local_14[2],local_14[1]),
         (CONCAT22(uStack_16,local_18) & 0x1ffff) == 0x18000)) {
        if (CONCAT22(local_14[0],uStack_16) == -1) {
          iVar4 = 0;
          if (CONCAT22(local_14[2],local_14[1]) == -1) {
            iVar5 = 0;
            if (local_14[3] == 0xffff) {
              local_14[3] = 0x8000;
              local_34 = local_34 + 1;
            }
            else {
              local_14[3] = local_14[3] + 1;
            }
          }
          else {
            iVar5 = CONCAT22(local_14[2],local_14[1]) + 1;
          }
        }
        else {
          iVar4 = CONCAT22(local_14[0],uStack_16) + 1;
          iVar5 = CONCAT22(local_14[2],local_14[1]);
        }
      }
      local_14[0] = (short)((uint)iVar4 >> 0x10);
      uStack_16 = (undefined2)iVar4;
      local_14[2] = (short)((uint)iVar5 >> 0x10);
      local_14[1] = (short)iVar5;
      if (local_34 < 0x7fff) {
        *(undefined2 *)param_1 = uStack_16;
        *(uint *)((int)param_1 + 2) = CONCAT22(local_14[1],local_14[0]);
        *(uint *)((int)param_1 + 6) = CONCAT22(local_14[3],local_14[2]);
        *(ushort *)((int)param_1 + 10) = local_34 | uVar3 & 0x8000;
      }
      else {
        param_1[2] = (-(uint)((uVar3 & 0x8000) != 0) & 0x80000000) + 0x7fff8000;
        param_1[1] = 0;
        *param_1 = 0;
      }
    }
  }
  else {
    param_1[2] = (-(uint)((uVar3 & 0x8000) != 0) & 0x80000000) + 0x7fff8000;
    param_1[1] = 0;
    *param_1 = 0;
  }
  return;
}


// 0053f5b0

void FUN_0053f5b0(undefined2 *param_1,uint param_2,int param_3)

{
  uint uVar1;
  ushort local_18;
  undefined4 uStack_16;
  undefined2 uStack_12;
  undefined4 local_10;
  ushort *local_c;
  undefined *local_8;
  
  local_8 = &DAT_0057add8;
  if (param_2 != 0) {
    if ((int)param_2 < 0) {
      param_2 = -param_2;
      local_8 = &DAT_0057af38;
    }
    uStack_16 = CONCAT22(uStack_16._2_2_,(undefined2)uStack_16);
    if (param_3 == 0) {
      *param_1 = 0;
      uStack_16 = CONCAT22(uStack_16._2_2_,(undefined2)uStack_16);
    }
    while (param_2 != 0) {
      local_8 = local_8 + 0x54;
      uVar1 = param_2 & 7;
      param_2 = (int)param_2 >> 3;
      if (uVar1 != 0) {
        local_c = (ushort *)(local_8 + uVar1 * 0xc);
        if (0x7fff < *local_c) {
          local_18 = (ushort)*(undefined4 *)local_c;
          uStack_16._0_2_ = (undefined2)((uint)*(undefined4 *)local_c >> 0x10);
          uStack_16._2_2_ = (undefined2)*(undefined4 *)(local_c + 2);
          uStack_12 = (undefined2)((uint)*(undefined4 *)(local_c + 2) >> 0x10);
          local_10 = *(undefined4 *)(local_c + 4);
          uStack_16 = CONCAT22(uStack_16._2_2_,(undefined2)uStack_16) + -1;
          local_c = &local_18;
        }
        FUN_0053f170(param_1,local_c);
      }
    }
  }
  return;
}


// 0053f680

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

float10 FUN_0053f680(undefined4 param_1,undefined4 param_2,int param_3)

{
  int iVar1;
  float10 fVar2;
  double dVar3;
  undefined4 uVar4;
  int local_38;
  int local_18;
  int local_14;
  undefined4 local_10;
  double local_c;
  
  local_10 = FUN_00535900();
  if ((param_2._2_2_ & 0x7ff0) == 0x7ff0) {
    iVar1 = FUN_00535700();
    if (0 < iVar1) {
      if (iVar1 < 3) {
        FUN_00535900();
        return (float10)(double)CONCAT26(param_2._2_2_,CONCAT24((undefined2)param_2,param_1));
      }
      if (iVar1 == 3) {
        fVar2 = (float10)FUN_00534a20(0x19,param_1,param_2,(double)param_3,local_10);
        return fVar2;
      }
    }
    fVar2 = (float10)FUN_00534b50(8,0x19,param_1,param_2,(double)param_3,
                                  (double)CONCAT26(param_2._2_2_,
                                                   CONCAT24((undefined2)param_2,param_1)) +
                                  _DAT_005460b8,local_10);
    return fVar2;
  }
  if ((double)CONCAT26(param_2._2_2_,CONCAT24((undefined2)param_2,param_1)) == _DAT_00546090) {
    FUN_00535900();
    return (float10)(double)CONCAT26(param_2._2_2_,CONCAT24((undefined2)param_2,param_1));
  }
  fVar2 = (float10)FUN_00535780(param_1,param_2,&local_14);
  dVar3 = (double)fVar2;
  if (param_3 < 0) {
    local_38 = -param_3;
  }
  else {
    local_38 = param_3;
  }
  if (local_38 <= 0x7fffffff) {
    local_18 = local_14 + param_3;
  }
  else {
    local_18 = param_3;
  }
  if (0xa00 < local_18) {
    uVar4 = local_10;
    dVar3 = __copysign((double)CONCAT44(DAT_0057a72c,DAT_0057a728),dVar3);
    fVar2 = (float10)FUN_00534b50(0x11,0x19,param_1,param_2,(double)param_3,dVar3,uVar4);
    return fVar2;
  }
  if (0x400 < local_18) {
    fVar2 = (float10)FUN_00535610(dVar3,local_18 + -0x600);
    local_c = (double)fVar2;
    fVar2 = (float10)FUN_00534b50(0x11,0x19,param_1,param_2,(double)param_3,local_c,local_10);
    return fVar2;
  }
  if (local_18 < -0x9fd) {
    fVar2 = (float10)FUN_00534b50(0x12,0x19,param_1,param_2,(double)param_3,dVar3 * _DAT_00546090,
                                  local_10);
    return fVar2;
  }
  if (local_18 < -0x3fd) {
    fVar2 = (float10)FUN_00535610(dVar3,local_18 + 0x600);
    local_c = (double)fVar2;
    fVar2 = (float10)FUN_00534b50(0x12,0x19,param_1,param_2,(double)param_3,local_c,local_10);
    return fVar2;
  }
  fVar2 = (float10)FUN_00535610(dVar3,local_18);
  local_c = (double)fVar2;
  FUN_00535900();
  return (float10)local_c;
}


// 0053fa24

void RtlUnwind(PVOID TargetFrame,PVOID TargetIp,PEXCEPTION_RECORD ExceptionRecord,PVOID ReturnValue)

{
                    /* WARNING: Could not recover jumptable at 0x0053fa24. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  RtlUnwind(TargetFrame,TargetIp,ExceptionRecord,ReturnValue);
  return;
}


// 0053fa70

undefined4 FUN_0053fa70(LPCSTR param_1)

{
  BOOL BVar1;
  undefined4 uVar2;
  undefined4 local_8;
  
  BVar1 = CreateDirectoryA(param_1,(LPSECURITY_ATTRIBUTES)0x0);
  if (BVar1 == 0) {
    local_8 = GetLastError();
  }
  else {
    local_8 = 0;
  }
  if (local_8 == 0) {
    uVar2 = 0;
  }
  else {
    __dosmaperr(local_8);
    uVar2 = 0xffffffff;
  }
  return uVar2;
}


// 0053fac0

/* Library Function - Single Match
    __strcmpi
   
   Libraries: Visual Studio 1998 Debug, Visual Studio 1998 Release */

int __cdecl __strcmpi(char *_Str1,char *_Str2)

{
  char cVar1;
  uint uVar2;
  byte bVar3;
  byte bVar4;
  byte bVar5;
  char cVar6;
  int iVar7;
  
  if (DAT_00b940cc == 0) {
    bVar5 = 0xff;
    do {
      do {
        cVar6 = '\0';
        if (bVar5 == 0) goto LAB_0053fb0e;
        bVar5 = *_Str2;
        _Str2 = _Str2 + 1;
        bVar4 = *_Str1;
        _Str1 = _Str1 + 1;
      } while (bVar4 == bVar5);
      bVar3 = bVar5 + 0xbf + (-((byte)(bVar5 + 0xbf) < 0x1a) & 0x20U) + 0x41;
      bVar4 = bVar4 + 0xbf;
      bVar5 = bVar4 + (-(bVar4 < 0x1a) & 0x20U) + 0x41;
    } while (bVar5 == bVar3);
    cVar6 = (bVar5 < bVar3) * -2 + '\x01';
LAB_0053fb0e:
    iVar7 = (int)cVar6;
  }
  else {
    iVar7 = 0xff;
    do {
      do {
        if ((char)iVar7 == '\0') {
          return iVar7;
        }
        cVar6 = *_Str2;
        iVar7 = CONCAT31((int3)((uint)iVar7 >> 8),cVar6);
        _Str2 = _Str2 + 1;
        cVar1 = *_Str1;
        _Str1 = _Str1 + 1;
      } while (cVar6 == cVar1);
      bVar5 = FUN_00539fc0(cVar1,iVar7);
      iVar7 = FUN_00539fc0();
    } while (bVar5 == (byte)iVar7);
    uVar2 = (uint)(bVar5 < (byte)iVar7);
    iVar7 = (1 - uVar2) - (uint)(uVar2 != 0);
  }
  return iVar7;
}


// 0053fb50

char * FUN_0053fb50(char *param_1)

{
  int iVar1;
  char *local_10;
  int local_c;
  
  local_c = 0;
  if (DAT_00b940cc == 0) {
    for (local_10 = param_1; *local_10 != '\0'; local_10 = local_10 + 1) {
      if (('`' < *local_10) && (*local_10 < '{')) {
        *local_10 = *local_10 + -0x20;
      }
    }
  }
  else {
    iVar1 = FUN_00531fa0(DAT_00b940cc,0x200,param_1,0xffffffff,0,0,0,1);
    if (((iVar1 != 0) && (local_c = FUN_0052c150(iVar1,2,"strupr.c",0x62), local_c != 0)) &&
       (iVar1 = FUN_00531fa0(DAT_00b940cc,0x200,param_1,0xffffffff,local_c,iVar1,0,1), iVar1 != 0))
    {
      FUN_0052b100(param_1,local_c);
    }
    FUN_0052cb90(local_c,2);
  }
  return param_1;
}


