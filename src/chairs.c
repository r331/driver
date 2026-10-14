/* Driver PC (1999) — модуль chairs, псевдо-C из Ghidra. 2 функций */

// 004a2f77

void FUN_004a2f77(undefined4 param_1,int param_2)

{
  int iVar1;
  int local_b4;
  int local_ac;
  undefined1 local_a8 [128];
  int local_28;
  undefined1 local_24 [4];
  int local_20;
  int local_1c;
  undefined1 local_18 [4];
  int local_14;
  int local_10;
  int local_c;
  int local_8;
  
  thunk_FUN_004bf2a0(s_Attempting_to_process_Chair_plac_0055178c);
  thunk_FUN_004a3354();
  iVar1 = FUN_0052b260(param_1);
  FUN_0052aaf0(local_18,1,0x14,param_1);
  if (local_14 == 2) {
    iVar1 = local_10 * local_c * 4;
    FUN_0052a910(local_a8,s_Map_is__d_cells_wide_and__d_cell_00551828,local_10,local_c,4,iVar1,
                 (int)(iVar1 + (iVar1 >> 0x1f & 0x3ffU)) >> 10);
    thunk_FUN_004bf2a0(local_a8);
    DAT_011342e8 = (void *)thunk_FUN_004d8db4(local_10 * local_c * 4,
                                              s_D__Driver_Game_chairs_c_00551888,0x17c);
    if (DAT_011342e8 == (void *)0x0) {
      FUN_0052a910(local_a8,s_Error_allocating_memory_for_Chai_005518a0,local_10 * local_c * 4);
      thunk_FUN_004bf2a0(local_a8);
    }
    else {
      _memset(DAT_011342e8,0,local_10 * local_c * 4);
      DAT_01134530 = local_10;
      DAT_0113452c = local_c;
      local_b4 = local_8;
      do {
        if (local_b4 == 0) {
          FUN_0052a910(local_a8,s_ProcessChairLump_completed_succe_00551968,DAT_01134ea0);
          thunk_FUN_004bf2a0(local_a8);
          return;
        }
        FUN_0052aaf0(local_24,1,0xc,param_1);
        local_28 = thunk_FUN_004d8db4(local_20 * 0x14,s_D__Driver_Game_chairs_c_005518ec,0x193);
        if (local_28 == 0) {
          thunk_FUN_004bf2a0(s_Unable_to_allocate_memory_for_ch_00551904);
          thunk_FUN_004a3354();
          return;
        }
        DAT_01134ea0 = DAT_01134ea0 + local_20;
        local_1c = local_28;
        for (local_ac = 0; local_ac < local_20; local_ac = local_ac + 1) {
          FUN_0052aaf0(local_28 + local_ac * 0x14,1,0x14,param_1);
        }
        iVar1 = thunk_FUN_004a31fc(local_24);
        local_b4 = local_b4 + -1;
      } while (iVar1 != 0);
      thunk_FUN_004bf2a0(s_Failed_to_Add_chair_list_to_game_00551930);
      thunk_FUN_004d8f30(local_28);
      thunk_FUN_004a3354();
    }
  }
  else {
    FUN_0052b4f0(param_1,iVar1 + param_2,0);
    thunk_FUN_004bf2a0(s_Chair_chunk_is_an_incompatible_v_005517bc);
  }
  return;
}


// 004a31fc

undefined4 FUN_004a31fc(int *param_1)

{
  undefined4 uVar1;
  
  if (DAT_011342e8 == 0) {
    uVar1 = 0;
  }
  else if ((DAT_0113452c == 0) || (DAT_01134530 == 0)) {
    uVar1 = 0;
  }
  else {
    if (*(int *)(DAT_011342e8 + *param_1 * 4) == 0) {
      uVar1 = thunk_FUN_004d8db4(0xc,s_D__Driver_Game_chairs_c_005519bc,0x1ce);
      *(undefined4 *)(DAT_011342e8 + *param_1 * 4) = uVar1;
      if (*(int *)(DAT_011342e8 + *param_1 * 4) == 0) {
        return 0;
      }
    }
    else if (*(int *)(*(int *)(DAT_011342e8 + *param_1 * 4) + 8) != 0) {
      thunk_FUN_004d8f30(*(undefined4 *)(*(int *)(DAT_011342e8 + *param_1 * 4) + 8));
    }
    *(int *)(*(int *)(DAT_011342e8 + *param_1 * 4) + 8) = param_1[2];
    **(int **)(DAT_011342e8 + *param_1 * 4) = *param_1;
    *(int *)(*(int *)(DAT_011342e8 + *param_1 * 4) + 4) = param_1[1];
    uVar1 = 1;
  }
  return uVar1;
}


