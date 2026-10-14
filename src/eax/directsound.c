/* Driver PC (1999) — модуль eax/directsound, псевдо-C из Ghidra. 1 функций */

// 0048bf9a

undefined4 FUN_0048bf9a(int param_1,char *param_2)

{
  undefined4 uVar1;
  size_t sVar2;
  undefined1 local_24 [4];
  undefined4 local_20;
  int local_10;
  int local_c;
  int local_8;
  
  if (DAT_00b1f420 == 0) {
    local_20 = 0xffffffff;
  }
  else {
    local_10 = FUN_0052adb0(param_2,&DAT_00551260);
    if (local_10 == 0) {
      local_20 = 0xffffffff;
    }
    else {
      FUN_0052b4f0(local_10,0,2);
      local_c = FUN_0052b260(local_10);
      if (local_c == -1) {
        FUN_0052aa10(local_10);
        local_20 = 0xffffffff;
      }
      else {
        FUN_0052b4f0(local_10,0x18,0);
        FUN_0052aaf0(local_24,1,0x12,local_10);
        FUN_0052b4f0(local_10,0,0);
        local_8 = thunk_FUN_004d8db4(local_c,s_D__Driver_Game_eax_directsound_c_00551264,0x1c4);
        if (local_8 == 0) {
          FUN_0052aa10(local_10);
          local_20 = 0xffffffff;
        }
        else {
          FUN_0052aaf0(local_8,1,local_c,local_10);
          FUN_0052aa10(local_10);
          uVar1 = thunk_FUN_0048c192(DAT_00b1f420,local_8,DAT_00b1f434);
          *(undefined4 *)(&DAT_00b1c9a0 + param_1 * 0x88) = uVar1;
          if (*(int *)(&DAT_00b1c9a0 + param_1 * 0x88) == 0) {
            thunk_FUN_004d8f30(local_8);
            local_20 = 0xffffffff;
          }
          else {
            thunk_FUN_004d8f30(local_8);
            sVar2 = _strlen(param_2);
            if (sVar2 < 0x80) {
              FUN_0052b100(&DAT_00b1c9a8 + param_1 * 0x88,param_2);
            }
            else {
              (&DAT_00b1c9a8)[param_1 * 0x88] = 0;
            }
            if (DAT_00b91d30 != 0) {
              uVar1 = FUN_0048cad6(*(undefined4 *)(&DAT_00b1c9a0 + param_1 * 0x88));
              *(undefined4 *)(&DAT_00b1c9a4 + param_1 * 0x88) = uVar1;
              if (*(int *)(&DAT_00b1c9a4 + param_1 * 0x88) != 0) {
                FUN_0048cba4(*(undefined4 *)(&DAT_00b1c9a4 + param_1 * 0x88));
              }
            }
          }
        }
      }
    }
  }
  return local_20;
}


