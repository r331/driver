/* Driver PC (1999) — модуль overlay, псевдо-C из Ghidra. 1 функций */

// 00501770

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_00501770(void)

{
  byte bVar1;
  bool bVar2;
  int iVar3;
  ushort auStack_268 [256];
  byte local_68;
  undefined3 uStack_67;
  int local_64;
  int local_60;
  int local_5c;
  int local_58;
  int local_54;
  int local_50;
  undefined1 local_4c [4];
  int local_48;
  int local_44;
  uint local_3e;
  undefined1 *local_24;
  undefined1 *local_20;
  undefined1 local_1c [16];
  int local_c;
  undefined *local_8;
  
  local_8 = (&PTR_s_MIAMI_00_MAP_00574018)[DAT_00b87e30];
  if (DAT_00c80880 != 0) {
    thunk_FUN_004d8f30(DAT_00c80880);
    DAT_00c80880 = 0;
  }
  if (local_8 == (undefined *)0x0) {
    DAT_00c80880 = 0;
    DAT_00c808a0 = 0;
    DAT_00c80890 = 0;
    DAT_00c80884 = 0;
    DAT_00c8089c = 0;
  }
  else {
    if (DAT_00c80fa0 == '\0') {
      local_c = FUN_0052adb0((&PTR_s_MIAMI_00_MAP_00574018)[DAT_00b87e30],&DAT_005740d4);
    }
    else {
      local_c = FUN_0052adb0(&DAT_00c80fa0,&DAT_005740d0);
    }
    if (local_c == 0) {
      DAT_00c808a0 = 0;
      DAT_00c80890 = 0;
      DAT_00c80884 = 0;
      DAT_00c8089c = 0;
    }
    else {
      thunk_FUN_004d9596(local_1c,0xe,1,local_c);
      thunk_FUN_004d9596(local_4c,0x28,1,local_c);
      thunk_FUN_004d9596(&DAT_012587e0,4,0x100,local_c);
      _DAT_01252afc = 1;
      local_20 = &DAT_012587e0;
      local_24 = &DAT_012587e0;
      DAT_012587e2 = 0;
      DAT_012587e1 = 0;
      DAT_012587e0 = 0;
      DAT_00c80890 = local_48;
      DAT_00c808a0 = local_44;
      DAT_00c8089c = 1;
      DAT_00c80884 = 0;
      if (DAT_00bdfaa0 == 0) {
        DAT_00c80880 = thunk_FUN_004d8db4(local_48 * local_44,s_D__Driver_Game_overlay_c_00574110,
                                          0x1d0);
        if ((DAT_00c80880 == 0) || ((local_3e & 0xffff) != 8)) {
          DAT_00c808a0 = 0;
          DAT_00c80890 = 0;
          DAT_00c80884 = 0;
          DAT_00c8089c = 0;
        }
        else {
          thunk_FUN_004d9596(DAT_00c80880,DAT_00c808a0,DAT_00c80890,local_c);
        }
      }
      else {
        bVar2 = false;
        if ((((local_3e & 0xffff) == 8) &&
            (DAT_00c80880 = thunk_FUN_004d8db4(local_48 * local_44 * 2,
                                               s_D__Driver_Game_overlay_c_005740d8,0x1a6),
            DAT_00c80880 != 0)) &&
           (local_58 = thunk_FUN_004d8db4(DAT_00c80890 * DAT_00c808a0,
                                          s_D__Driver_Game_overlay_c_005740f4,0x1a9), local_58 != 0)
           ) {
          thunk_FUN_004d9596(local_58,DAT_00c808a0,DAT_00c80890,local_c);
          iVar3 = DAT_00c80880;
          for (local_60 = 0; local_60 < 0x100; local_60 = local_60 + 1) {
            local_54 = (int)(uint)(byte)(&DAT_012587e2)[local_60 * 4] >> ((byte)DAT_00bdfa80 & 0x1f)
            ;
            local_5c = (int)(uint)(byte)(&DAT_012587e1)[local_60 * 4] >> ((byte)DAT_00bdfa88 & 0x1f)
            ;
            local_50 = (int)(uint)(byte)(&DAT_012587e0)[local_60 * 4] >> ((byte)DAT_00bdfa90 & 0x1f)
            ;
            auStack_268[local_60] =
                 (ushort)(local_54 << ((byte)DAT_00bdfa84 & 0x1f)) |
                 (ushort)(local_5c << ((byte)DAT_00bdfa8c & 0x1f)) |
                 (ushort)(local_50 << ((byte)DAT_00bdfa94 & 0x1f));
          }
          for (local_64 = 0; local_64 < DAT_00c808a0; local_64 = local_64 + 1) {
            for (local_60 = 0; local_60 < DAT_00c80890; local_60 = local_60 + 1) {
              bVar1 = *(byte *)(local_58 + local_64 * DAT_00c80890 + local_60);
              _local_68 = CONCAT31(uStack_67,bVar1);
              *(ushort *)(iVar3 + (local_64 * DAT_00c80890 + local_60) * 2) = auStack_268[bVar1];
            }
          }
          thunk_FUN_004d8f30(local_58);
          bVar2 = true;
        }
        if (!bVar2) {
          DAT_00c808a0 = 0;
          DAT_00c80890 = 0;
          DAT_00c80884 = 0;
          DAT_00c8089c = 0;
        }
      }
      FUN_0052aa10(local_c);
    }
    if (*(int *)(&DAT_00573fa8 + DAT_00b87e30 * 0x10) == -1) {
      _DAT_00b32a04 = 0;
      _DAT_00b32a0c = 0;
      _DAT_00b32a30 = DAT_00c80890;
      _DAT_00b52a34 = DAT_00c808a0;
    }
    else {
      _DAT_00b32a04 = *(undefined4 *)(&DAT_00573fa8 + DAT_00b87e30 * 0x10);
      _DAT_00b32a0c = *(undefined4 *)(&DAT_00573fac + DAT_00b87e30 * 0x10);
      _DAT_00b32a30 =
           *(int *)(&DAT_00573fb0 + DAT_00b87e30 * 0x10) -
           *(int *)(&DAT_00573fa8 + DAT_00b87e30 * 0x10);
      _DAT_00b52a34 =
           *(int *)(&DAT_00573fb4 + DAT_00b87e30 * 0x10) -
           *(int *)(&DAT_00573fac + DAT_00b87e30 * 0x10);
    }
  }
  return;
}


