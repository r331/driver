/* Driver PC (1999) — модуль denting, псевдо-C из Ghidra. 1 функций */

// 004c17ae

void FUN_004c17ae(void)

{
  undefined4 uVar1;
  int local_20;
  int local_1c;
  undefined1 local_18 [20];
  
  for (local_20 = 0; local_20 < 0xb; local_20 = local_20 + 1) {
    for (local_1c = 0; local_1c < 6; local_1c = local_1c + 1) {
      switch(DAT_00d1192c) {
      case 0:
        FUN_0052a910(local_18,0x55ce80,local_1c,local_20 + 1);
        break;
      case 1:
        FUN_0052a910(local_18,s__iTRUCK_i_0055ce88,local_1c,local_20 + 1);
        break;
      case 2:
        FUN_0052a910(local_18,0x55ce94,local_1c,local_20 + 1);
        break;
      case 3:
        FUN_0052a910(local_18,0x55ce9c,local_1c,local_20 + 1);
        break;
      case 4:
        FUN_0052a910(local_18,0x55cea4,local_1c,local_20 + 1);
        break;
      case 5:
        FUN_0052a910(local_18,0x55ceac,local_1c,local_20 + 1);
        break;
      case 6:
        FUN_0052a910(local_18,0x55ceb4,local_1c,local_20 + 1);
        break;
      case 7:
        FUN_0052a910(local_18,0x55cebc,local_1c,local_20 + 1);
        break;
      case 8:
        FUN_0052a910(local_18,0x55cec4,local_1c,local_20 + 1);
        break;
      case 9:
        FUN_0052a910(local_18,0x55cecc,local_1c,local_20 + 1);
        break;
      case 10:
        FUN_0052a910(local_18,0x55ced4,local_1c,local_20 + 1);
        break;
      case 0xb:
        FUN_0052a910(local_18,0x55cedc,local_1c,local_20 + 1);
        break;
      case 0xc:
        FUN_0052a910(local_18,0x55cee4,local_1c,local_20 + 1);
        break;
      case 0xd:
        FUN_0052a910(local_18,0x55ceec,local_1c,local_20 + 1);
        break;
      case 0xe:
        FUN_0052a910(local_18,0x55cef4,local_1c,local_20 + 1);
        break;
      case 0xf:
        FUN_0052a910(local_18,0x55cefc,local_1c,local_20 + 1);
        break;
      case 0x10:
        FUN_0052a910(local_18,0x55cf04,local_1c,local_20 + 1);
        break;
      case 0x11:
        FUN_0052a910(local_18,0x55cf0c,local_1c,local_20 + 1);
        break;
      default:
        FUN_0052a910(local_18,s__iBD_i_0055cf14,local_1c,local_20 + 1);
      }
      uVar1 = thunk_FUN_004ec91e(local_18);
      (&DAT_00d17d60)[local_20 * 6 + local_1c] = uVar1;
    }
  }
  if (DAT_00d17ec8 != 0) {
    thunk_FUN_004d8f30(DAT_00d17ec8);
    DAT_00d17ec8 = 0;
  }
  DAT_00d17ec8 = thunk_FUN_004d8db4(0x20000,s_D__Driver_Game_denting_c_0055cf1c,0x500);
  if (DAT_00d17ec8 == 0) {
    MessageBoxA(DAT_00bdf9c0,s_Could_not_malloc_space_for_tempo_0055cf40,s_ERROR_0055cf38,0);
  }
  thunk_FUN_004c1b6c(0);
  return;
}


