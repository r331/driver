/* Driver PC (1999) — модуль mirror, псевдо-C из Ghidra. 1 функций */

// 004f2c9a

void FUN_004f2c9a(void)

{
  float fVar1;
  int local_3ec;
  short *local_3e8;
  int local_3e4;
  int local_3e0;
  char local_3dc [964];
  int local_18;
  float local_14;
  int local_10;
  char *local_c;
  int local_8;
  
  local_10 = 0x1f;
  fVar1 = DAT_01270c24 * DAT_01270c24;
  if (DAT_00b31f00 != 0) {
    thunk_FUN_004d8f30(DAT_00b31f00);
    DAT_00b31f00 = 0;
  }
  DAT_00b31f00 = thunk_FUN_004d8db4(0x8000,s_D__Driver_Game_mirror_c_005636f0,0x16d);
  thunk_FUN_0048db65(DAT_00b31f00,0x8000);
  for (local_3e4 = 0; local_3e4 < 0x100; local_3e4 = local_3e4 + 1) {
    thunk_FUN_0048db65(local_3dc,local_10 * local_10);
    if (*(short *)(&DAT_00cb8f20 + local_3e4 * 0x80) == -1) {
      local_8 = 0;
    }
    else {
      local_8 = (int)*(short *)(&DAT_00cb8f20 + local_3e4 * 0x80);
    }
    local_3e8 = (short *)(local_3e4 * 0x80 + 0xcb8f24 + local_8 * 4);
    for (; local_8 < local_10; local_8 = local_8 + 1) {
      if (*local_3e8 != -1) {
        local_c = local_3dc + (int)*local_3e8 + local_8 * local_10;
        for (local_3ec = 0; local_3ec < local_3e8[1]; local_3ec = local_3ec + 1) {
          *local_c = '\x01';
          local_c = local_c + 1;
        }
      }
      local_3e8 = local_3e8 + 2;
    }
    local_8 = 0;
    local_c = local_3dc;
    for (local_3e0 = -0xf; local_3e0 < 0x10; local_3e0 = local_3e0 + 1) {
      local_8 = (local_3e0 + 0xf) * local_10;
      for (local_18 = -0xf; local_18 < 0x10; local_18 = local_18 + 1) {
        if (local_c[local_8] != '\0') {
          local_14 = (float)(local_18 * local_18 + local_3e0 * local_3e0);
          if (fVar1 < local_14) {
            local_c[local_8] = '\0';
          }
        }
        local_8 = local_8 + 1;
      }
    }
    thunk_FUN_004f2f2a(DAT_00b31f00 + local_3e4 * 0x80,local_3dc);
  }
  return;
}


