/* Driver PC (1999) — модуль frontend/gvars, псевдо-C из Ghidra. 1 функций */

// 0040ec30

void FUN_0040ec30(void)

{
  byte *_Str;
  int iVar1;
  byte *pbVar2;
  byte *local_120;
  size_t local_114;
  byte *local_110;
  undefined1 local_10c [256];
  int local_c;
  int local_8;
  
  local_8 = 0;
  if ((DAT_00c557fc < 0) || (5 < DAT_00c557fc)) {
    DAT_00c557fc = 0;
  }
  FUN_0052a910(local_10c,s_KEYS__s_0054ba48,(&PTR_DAT_0054b49c)[DAT_00c557fc]);
  iVar1 = FUN_0052adb0(local_10c,&DAT_0054ba50);
  if (iVar1 != 0) {
    FUN_0052b4f0(iVar1,0,2);
    local_8 = FUN_0052b260(iVar1);
    FUN_0052b4f0(iVar1,0,0);
    pbVar2 = (byte *)thunk_FUN_004d8db4(local_8 + 1,s_D__Driver_Game_frontend_gvars_c_0054ba54,0xeb)
    ;
    if (pbVar2 == (byte *)0x0) {
      FUN_0052aa10(iVar1);
    }
    else {
      FUN_0052aaf0(pbVar2,1,local_8,iVar1);
      FUN_0052aa10(iVar1);
      pbVar2[local_8] = 0;
      local_120 = pbVar2;
      for (local_c = 0; _Str = local_120, local_c < 0x21; local_c = local_c + 1) {
        if (0 < local_8) {
          local_110 = local_120;
          do {
            if (*local_120 == 10) break;
            if (0x1f < *local_120) {
              local_110 = local_120 + 1;
            }
            local_8 = local_8 + -1;
            local_120 = local_120 + 1;
          } while (1 < local_8);
          *local_110 = 0;
          local_114 = _strlen((char *)_Str);
          if (0xf < (int)local_114) {
            local_114 = 0xf;
          }
          _strncpy(s_Return_0054b4b4 + local_c * 0x10,(char *)_Str,local_114);
          s_Return_0054b4b4[local_114 + local_c * 0x10] = '\0';
          local_120 = local_120 + 1;
          local_8 = local_8 + -1;
        }
      }
      thunk_FUN_004d8f30(pbVar2);
      PTR_s_Return_0054b080 = s_Return_0054b4b4;
      PTR_s_L_Ctrl_0054b084 = s_L_Ctrl_0054b4c4;
      PTR_s_L_Shift_0054b0b8 = s_L_Shift_0054b4d4;
      PTR_s_R_Shift_0054b0e8 = s_R_Shift_0054b4e4;
      PTR_s_Num___0054b0ec = s_Num___0054b4f4;
      PTR_s_L_Alt_0054b0f0 = s_L_Alt_0054b504;
      PTR_s_Space_0054b0f4 = s_Space_0054b514;
      PTR_s_Num_Lock_0054b124 = s_Num_Lock_0054b524;
      PTR_s_Num_7_0054b12c = s_Num_7_0054b534;
      PTR_s_Num_8_0054b130 = s_Num_8_0054b544;
      PTR_s_Num_9_0054b134 = s_Num_9_0054b554;
      PTR_s_Num___0054b138 = s_Num___0054b564;
      PTR_s_Num_4_0054b13c = s_Num_4_0054b574;
      PTR_s_Num_5_0054b140 = s_Num_5_0054b584;
      PTR_s_Num_6_0054b144 = s_Num_6_0054b594;
      PTR_s_Num___0054b148 = s_Num___0054b5a4;
      PTR_s_Num_1_0054b14c = s_Num_1_0054b5b4;
      PTR_s_Num_2_0054b150 = s_Num_2_0054b5c4;
      PTR_s_Num_3_0054b154 = s_Num_3_0054b5d4;
      PTR_s_Num_0_0054b158 = s_Num_0_0054b5e4;
      PTR_s_Num___0054b15c = s_Num___0054b5f4;
      PTR_s_Num___0054b244 = s_Num___0054b604;
      PTR_s_Num_Enter_0054b280 = s_Num_Enter_0054b614;
      PTR_s_R_Ctrl_0054b284 = s_R_Ctrl_0054b624;
      PTR_s_Num___0054b2dc = s_Num___0054b634;
      PTR_s_Num___0054b2e4 = s_Num___0054b644;
      PTR_s_R_Alt_0054b2f0 = s_R_Alt_0054b654;
      PTR_DAT_0054b330 = &DAT_0054b664;
      PTR_DAT_0054b33c = &DAT_0054b674;
      PTR_s_Right_0054b344 = s_Right_0054b684;
      PTR_DAT_0054b350 = &DAT_0054b694;
      PTR_DAT_0054b490 = &DAT_0054b664;
      PTR_DAT_0054b494 = &DAT_0054b694;
      PTR_DAT_0054b498 = &DAT_0054b6b4;
    }
  }
  return;
}


