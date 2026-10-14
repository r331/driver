/* Driver PC (1999) — модуль compiler, псевдо-C из Ghidra. 14 функций */

// 004a3fa6

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_004a3fa6(char *param_1)

{
  int iVar1;
  uint uVar2;
  int local_c;
  int local_8;
  
  do {
    local_c = 0;
    while ((iVar1 = thunk_FUN_004a59f2(param_1,s_EVENT_START_005520b8), iVar1 == 0 &&
           (local_c = thunk_FUN_004a59f2(param_1,s_MULTIEVENT_START_005520c4), local_c == 0))) {
      iVar1 = thunk_FUN_004a59f2(param_1,s_CHUNK_END_005520d8);
      if (iVar1 == 1) {
        return;
      }
      param_1 = (char *)thunk_FUN_004a59c6(param_1);
      param_1 = (char *)thunk_FUN_004a596b(param_1);
    }
    DAT_0113424c = 0;
    if (local_c == 0) {
      param_1 = (char *)thunk_FUN_004a59c6(param_1);
      param_1 = (char *)thunk_FUN_004a596b(param_1);
      param_1 = (char *)thunk_FUN_004a44d4(param_1);
    }
    else {
      for (param_1 = (char *)((int)param_1 + 0x10); (*param_1 == ' ' || (*param_1 == '\t'));
          param_1 = param_1 + 1) {
      }
      thunk_FUN_004a4d84(&param_1,0,0);
      uVar2 = (uint)DAT_011340c8;
      param_1 = (char *)thunk_FUN_004a59c6(param_1);
      param_1 = (char *)thunk_FUN_004a596b(param_1);
      iVar1 = thunk_FUN_004a59f2(param_1,s_MODELS_005520e4);
      if (iVar1 == 1) {
        DAT_01134244 = (undefined2 *)
                       thunk_FUN_004d8db4(uVar2 << 1,s_D__Driver_Game_compiler_c_005520ec,0x176);
        if (DAT_01134244 == (undefined2 *)0x0) {
          thunk_FUN_004a5ac3(s_8_Out_of_Memory_00552108);
          return;
        }
        param_1 = (char *)((int)param_1 + 6);
        param_1 = (char *)thunk_FUN_004a5afb(param_1,DAT_01134244,uVar2);
      }
      param_1 = (char *)thunk_FUN_004a596b(param_1);
      iVar1 = thunk_FUN_004a59f2(param_1,s_PALETTES_00552118);
      if (iVar1 == 1) {
        DAT_01134260 = thunk_FUN_004d8db4(uVar2 << 1,s_D__Driver_Game_compiler_c_00552124,0x188);
        if (DAT_01134260 == 0) {
          thunk_FUN_004a5ac3(s_8_Out_of_Memory_00552140);
          return;
        }
        param_1 = (char *)((int)param_1 + 8);
        param_1 = (char *)thunk_FUN_004a5afb(param_1,DAT_01134260,uVar2);
      }
      param_1 = (char *)thunk_FUN_004a596b(param_1);
      iVar1 = thunk_FUN_004a59f2(param_1,s_VELOCITIES_00552150);
      if (iVar1 == 1) {
        DAT_0113411c = thunk_FUN_004d8db4(uVar2 << 1,s_D__Driver_Game_compiler_c_0055215c,0x19a);
        if (DAT_0113411c == 0) {
          thunk_FUN_004a5ac3(s_8_Out_of_Memory_00552178);
          return;
        }
        param_1 = (char *)((int)param_1 + 10);
        param_1 = (char *)thunk_FUN_004a5afb(param_1,DAT_0113411c,uVar2);
      }
      param_1 = (char *)thunk_FUN_004a596b(param_1);
      param_1 = (char *)thunk_FUN_004a44d4(param_1);
      *(undefined2 *)(DAT_01134128 + 0x4a) = *DAT_01134244;
      for (local_8 = 1; local_8 < (int)uVar2; local_8 = local_8 + 1) {
        _DAT_01134248 = _DAT_01134248 + 1;
        thunk_FUN_004a4340(local_8);
      }
      if (DAT_01134244 != (undefined2 *)0x0) {
        thunk_FUN_004d8f30(DAT_01134244);
        DAT_01134244 = (undefined2 *)0x0;
      }
      if (DAT_01134260 != 0) {
        thunk_FUN_004d8f30(DAT_01134260);
        DAT_01134260 = 0;
      }
      if (DAT_0113411c != 0) {
        thunk_FUN_004d8f30(DAT_0113411c);
        DAT_0113411c = 0;
      }
    }
    param_1 = (char *)thunk_FUN_004a59c6(param_1);
    param_1 = (char *)thunk_FUN_004a596b(param_1);
  } while( true );
}


// 004a4340

void FUN_004a4340(int param_1)

{
  ushort *_Dst;
  void *_Dst_00;
  ushort *local_10;
  void *local_8;
  
  _Dst = (ushort *)thunk_FUN_004d8db4(0x24,s_D__Driver_Game_compiler_c_00552188,0x1cd);
  if (_Dst == (ushort *)0x0) {
    thunk_FUN_004a5ac3(s_Not_enough_memory_for_events__005521a4);
  }
  else {
    _memset(_Dst,0,0x24);
    for (local_10 = DAT_00d12408; *(int *)(local_10 + 0x10) != 0;
        local_10 = *(ushort **)(local_10 + 0x10)) {
    }
    *(ushort **)(local_10 + 0x10) = _Dst;
    if ((*local_10 & 0x20) == 0) {
      *local_10 = *local_10 | 0x10;
      local_10[4] = local_10[3];
    }
    _Dst[2] = 1;
    *_Dst = *_Dst | 8;
    *_Dst = *_Dst | 0x20;
    _Dst[3] = DAT_01134248;
    _Dst[4] = local_10[4];
    _Dst_00 = (void *)thunk_FUN_004d8db4(0x60,s_D__Driver_Game_compiler_c_005521c4,0x1ee);
    if (_Dst_00 == (void *)0x0) {
      thunk_FUN_004a5ac3(s_Not_enough_memory_for_new_model__005521e0);
    }
    else {
      _memset(_Dst_00,0,0x60);
      *(void **)(_Dst + 0xe) = _Dst_00;
      local_8 = _Dst_00;
    }
    *(undefined4 *)((int)local_8 + 0x50) = *(undefined4 *)(DAT_01134128 + 0x50);
    if (DAT_01134244 != 0) {
      *(undefined2 *)((int)local_8 + 0x4a) = *(undefined2 *)(DAT_01134244 + param_1 * 2);
    }
    if (DAT_01134260 != 0) {
      *(undefined2 *)((int)local_8 + 0x40) = *(undefined2 *)(DAT_01134260 + param_1 * 2);
    }
    if (DAT_0113411c != 0) {
      *(float *)((int)local_8 + 0x44) = (float)*(ushort *)(DAT_0113411c + param_1 * 2);
    }
  }
  return;
}


// 004a44d4

/* WARNING: Removing unreachable block (ram,0x004a45e4) */

undefined4 FUN_004a44d4(undefined4 param_1)

{
  int iVar1;
  undefined4 uVar2;
  void *local_c;
  
  DAT_00b1ff5c = (void *)thunk_FUN_004d8db4(0x24,s_D__Driver_Game_compiler_c_00552204,0x216);
  if (DAT_00b1ff5c == (void *)0x0) {
    thunk_FUN_004a5ac3(s_Not_enough_memory_for_events__00552220);
    param_1 = 0;
  }
  else {
    _memset(DAT_00b1ff5c,0,0x24);
    if (DAT_00d12408 == (void *)0x0) {
      DAT_00d12408 = DAT_00b1ff5c;
    }
    else {
      for (local_c = DAT_00d12408; *(int *)((int)local_c + 0x20) != 0;
          local_c = *(void **)((int)local_c + 0x20)) {
      }
      *(void **)((int)local_c + 0x20) = DAT_00b1ff5c;
    }
    DAT_01134118 = 0;
    DAT_01134240 = 0;
    while (iVar1 = thunk_FUN_004a59f2(param_1,s_EVENT_END_00552240), iVar1 != 1) {
      uVar2 = thunk_FUN_004a596b(param_1);
      uVar2 = thunk_FUN_004a45eb(uVar2,DAT_00b1ff5c);
      param_1 = thunk_FUN_004a59c6(uVar2);
    }
    *(undefined2 *)((int)DAT_00b1ff5c + 4) = (undefined2)DAT_0113424c;
  }
  return param_1;
}


// 004a45eb

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 FUN_004a45eb(undefined4 param_1,ushort *param_2)

{
  float fVar1;
  ushort uVar2;
  undefined4 uVar3;
  void *pvVar4;
  undefined2 extraout_var;
  float10 fVar5;
  
  uVar3 = thunk_FUN_004a596b();
  uVar2 = thunk_FUN_004a4a5f();
  if (uVar2 != 0x32) {
    if (uVar2 < 4) {
      if (uVar2 == 1) {
        *(float *)(param_2 + 8) = DAT_0113425c * DAT_0113425c;
        *(float *)(param_2 + 10) = DAT_01134258;
        *(float *)(param_2 + 0xc) = DAT_01134254;
      }
      else if (uVar2 == 2) {
        *param_2 = *param_2 | 4;
        *(uint *)(param_2 + 6) = (uint)DAT_01134112 * DAT_00562d38 + (uint)DAT_011340c8;
      }
      else if (uVar2 == 3) {
        *param_2 = *param_2 | 8;
        param_2[3] = DAT_011340c8;
        _DAT_01134248 = (uint)DAT_011340c8;
      }
      else {
        thunk_FUN_004a5ac3();
      }
    }
    else {
      if (uVar2 == 4) {
        if (DAT_01134240 != 0) {
          thunk_FUN_004a5ac3();
        }
        uVar2 = DAT_011340c8;
        pvVar4 = (void *)thunk_FUN_004d8db4(0x60,s_D__Driver_Game_compiler_c_0055227c);
        if (*(int *)(param_2 + 0xe) == 0) {
          if (pvVar4 == (void *)0x0) {
            thunk_FUN_004a5ac3();
          }
          else {
            *(void **)(param_2 + 0xe) = pvVar4;
            DAT_00b1ff68 = pvVar4;
          }
        }
        else if (pvVar4 == (void *)0x0) {
          thunk_FUN_004a5ac3();
        }
        else {
          *(void **)((int)DAT_00b1ff68 + 0x58) = pvVar4;
          DAT_00b1ff68 = pvVar4;
        }
        _memset(DAT_00b1ff68,0,0x60);
        *(ushort *)((int)DAT_00b1ff68 + 0x4a) = uVar2;
        *(undefined2 *)((int)DAT_00b1ff68 + 0x40) = 0xffff;
        DAT_01134128 = DAT_00b1ff68;
        DAT_0113424c = DAT_0113424c + 1;
        thunk_FUN_004a5338(CONCAT22((short)((uint)DAT_00b1ff68 >> 0x10),4),DAT_00b1ff68);
      }
      else {
        if (DAT_01134240 != 0) {
          DAT_01134118 = DAT_01134118 + (uint)*(ushort *)(&DAT_00551b32 + (uint)uVar2 * 2);
        }
        switch(uVar2) {
        case 5:
        case 6:
        case 7:
        case 8:
        case 10:
        case 0xb:
        case 0xc:
        case 0xd:
        case 0xf:
        case 0x10:
        case 0x11:
        case 0x12:
        case 0x16:
        case 0x17:
        case 0x1a:
        case 0x1b:
        case 0x1c:
        case 0x1d:
        case 0x1e:
        case 0x1f:
        case 0x20:
          thunk_FUN_004a5338(uVar2,DAT_00b1ff68);
          break;
        case 9:
          fVar5 = (float10)FUN_0052dfd4((double)(DAT_01134250 * DAT_01134250 +
                                                DAT_01134254 * DAT_01134254 +
                                                DAT_01134258 * DAT_01134258));
          fVar1 = (float)fVar5;
          DAT_01134258 = DAT_01134258 / fVar1;
          DAT_01134254 = DAT_01134254 / fVar1;
          DAT_01134250 = DAT_01134250 / fVar1;
          thunk_FUN_004a5338(CONCAT22(extraout_var,uVar2),DAT_00b1ff68);
          break;
        case 0xe:
          DAT_01134112 = DAT_011340c8;
          thunk_FUN_004a5338(CONCAT22((short)(uVar2 - 5 >> 0x10),uVar2),DAT_00b1ff68);
          break;
        case 0x13:
          if (DAT_01134240 != 0) {
            thunk_FUN_004a5ac3();
          }
          DAT_01134240 = 1;
          DAT_01134118 = 0;
          break;
        case 0x14:
          if (DAT_01134240 == 0) {
            thunk_FUN_004a5ac3();
          }
          DAT_011340c8 = ((short)DAT_01134118 - *(short *)(&DAT_00551b32 + (uint)uVar2 * 2)) + 2;
          thunk_FUN_004a5338(uVar2,DAT_00b1ff68);
          DAT_01134240 = 0;
          break;
        case 0x15:
          if (DAT_01134240 == 0) {
            thunk_FUN_004a5ac3();
          }
          DAT_01134112 = DAT_011340c8;
          DAT_01134114 = DAT_011340c8;
          DAT_011340c8 = ((short)DAT_01134118 + 6) - *(short *)(&DAT_00551b32 + (uint)uVar2 * 2);
          thunk_FUN_004a5338(uVar2,DAT_00b1ff68);
          DAT_01134240 = 0;
        }
      }
    }
  }
  return uVar3;
}


// 004a4a5f

ushort FUN_004a4a5f(char *param_1)

{
  char cVar1;
  int iVar2;
  size_t sVar3;
  ushort uVar4;
  int local_1c;
  int local_18;
  int local_10;
  char *local_c;
  int local_8;
  
  if ((*param_1 == '#') || ((*param_1 == '/' && (param_1[1] == '/')))) {
    return 0x32;
  }
  uVar4 = 0;
  local_18 = 0;
  do {
    if (0x1f < local_18) {
LAB_004a4ada:
      if (uVar4 == 0) {
        return 0;
      }
      sVar3 = _strlen((&PTR_DAT_00551c30)[uVar4]);
      param_1 = param_1 + sVar3;
      if (*(short *)(&DAT_00551b72 + (uint)uVar4 * 2) == 0) {
        return uVar4;
      }
      local_8 = 0;
      for (; *param_1 == ' '; param_1 = param_1 + 1) {
        local_8 = local_8 + 1;
      }
      if ((local_8 == 0) && (*param_1 != '\0')) {
        uVar4 = 0;
      }
      if (uVar4 == 0) {
        return 0;
      }
      local_10 = 0;
      local_1c = 0;
      local_c = *(char **)(&DAT_00551bb0 + (uint)uVar4 * 4);
      while( true ) {
        if (*local_c == '\0') {
          return uVar4;
        }
        cVar1 = *local_c;
        local_c = local_c + 1;
        if (cVar1 == 'f') {
          thunk_FUN_004a4f7d(param_1,local_10);
          thunk_FUN_004a50f7(&param_1);
          local_10 = local_10 + 1;
        }
        else if (cVar1 == 'i') {
          thunk_FUN_004a4d84(&param_1,local_1c,CONCAT22((short)((uint)local_c >> 0x10),uVar4));
          thunk_FUN_004a50a2(&param_1);
          local_1c = local_1c + 1;
        }
        if (*local_c == '\0') break;
        for (; *param_1 == ' '; param_1 = param_1 + 1) {
        }
        cVar1 = *param_1;
        param_1 = param_1 + 1;
        if (cVar1 != ',') {
          thunk_FUN_004a5ac3(s_Expecting_comma______00552324);
          return 0;
        }
        for (; *param_1 == ' '; param_1 = param_1 + 1) {
        }
      }
      for (; *param_1 == ' '; param_1 = param_1 + 1) {
      }
      while( true ) {
        if (*param_1 == '\n') {
          return uVar4;
        }
        if (*param_1 == '#') {
          return uVar4;
        }
        if ((*param_1 == '/') && (param_1[1] == '/')) {
          return uVar4;
        }
        if ((((*param_1 != '\t') && (*param_1 != ' ')) && (*param_1 != '\t')) &&
           ((*param_1 != '\n' && (*param_1 != '\r')))) break;
        param_1 = param_1 + 1;
      }
      thunk_FUN_004a5ac3(s_Junk_at_end_of_line__0055233c);
      return 0;
    }
    iVar2 = thunk_FUN_004a519a(param_1,(&PTR_s_TRIGGER_RADIUS_00551c34)[local_18]);
    if (iVar2 != 0) {
      uVar4 = (short)local_18 + 1;
      goto LAB_004a4ada;
    }
    local_18 = local_18 + 1;
  } while( true );
}


// 004a4d84

undefined4 FUN_004a4d84(int *param_1,undefined4 param_2,short param_3)

{
  char cVar1;
  int iVar2;
  short local_118 [2];
  undefined4 local_114;
  int local_110;
  undefined1 local_10c [256];
  int local_c;
  uint local_8;
  
  cVar1 = *(char *)*param_1;
  if (cVar1 == '-') {
    *param_1 = *param_1 + 1;
  }
  local_8 = (uint)(cVar1 == '-');
  local_c = FUN_0052e250(*param_1,&DAT_00552354,local_118);
  thunk_FUN_004a50a2(param_1);
  if (((local_c == 0) || (local_c == -1)) && (param_3 == 4)) {
    iVar2 = thunk_FUN_004a522a(*param_1,local_10c);
    *param_1 = iVar2;
    local_114 = DAT_00b1ff60;
    local_110 = thunk_FUN_004a58ad(local_10c,local_118);
    if (local_110 == 0) {
      thunk_FUN_004a5ac3(s_Model_number_must_be_an_unsigned_00552358);
      return 0;
    }
  }
  else if ((local_c == 0) || (local_c == -1)) {
    thunk_FUN_004a5ac3(s_Expecting_integer_value__00552394);
    return 0;
  }
  if (local_8 == 0) {
    switch(param_2) {
    case 0:
      DAT_011340c8 = local_118[0];
      break;
    case 1:
      DAT_01134112 = local_118[0];
      break;
    case 2:
      DAT_01134114 = local_118[0];
      break;
    case 3:
      DAT_01134116 = local_118[0];
    }
  }
  else {
    switch(param_2) {
    case 0:
      DAT_011340c8 = -local_118[0];
      break;
    case 1:
      DAT_01134112 = -local_118[0];
      break;
    case 2:
      DAT_01134114 = -local_118[0];
      break;
    case 3:
      DAT_01134116 = -local_118[0];
    }
  }
  return 1;
}


// 004a4f7d

undefined4 FUN_004a4f7d(char *param_1,undefined4 param_2)

{
  char cVar1;
  undefined4 uVar2;
  float local_10;
  int local_c;
  uint local_8;
  
  cVar1 = *param_1;
  if (cVar1 == '-') {
    param_1 = param_1 + 1;
  }
  local_8 = (uint)(cVar1 == '-');
  local_c = FUN_0052e250(param_1,&DAT_005523b0,&local_10);
  thunk_FUN_004a50f7(&param_1);
  if ((local_c == 0) || (local_c == -1)) {
    thunk_FUN_004a5ac3(s_Expecting_floating_point_value__005523b4);
    uVar2 = 0;
  }
  else {
    if (local_8 == 0) {
      switch(param_2) {
      case 0:
        DAT_0113425c = local_10;
        break;
      case 1:
        DAT_01134258 = local_10;
        break;
      case 2:
        DAT_01134254 = local_10;
        break;
      case 3:
        DAT_01134250 = local_10;
      }
    }
    else {
      switch(param_2) {
      case 0:
        DAT_0113425c = -local_10;
        break;
      case 1:
        DAT_01134258 = -local_10;
        break;
      case 2:
        DAT_01134254 = -local_10;
        break;
      case 3:
        DAT_01134250 = -local_10;
      }
    }
    uVar2 = 1;
  }
  return uVar2;
}


// 004a50a2

void FUN_004a50a2(int *param_1)

{
  if (*(char *)*param_1 == '-') {
    *param_1 = *param_1 + 1;
  }
  while ((0x2f < *(byte *)*param_1 && (*(byte *)*param_1 < 0x3a))) {
    *param_1 = *param_1 + 1;
  }
  return;
}


// 004a50f7

undefined4 FUN_004a50f7(int *param_1)

{
  bool bVar1;
  
  bVar1 = false;
  if (*(char *)*param_1 == '-') {
    *param_1 = *param_1 + 1;
  }
  while( true ) {
    while ((0x2f < *(byte *)*param_1 && (*(byte *)*param_1 < 0x3a))) {
      *param_1 = *param_1 + 1;
    }
    if ((*(char *)*param_1 == '.') && (bVar1)) break;
    if (*(char *)*param_1 != '.') {
      return 1;
    }
    *param_1 = *param_1 + 1;
    bVar1 = true;
  }
  return 0;
}


// 004a519a

size_t FUN_004a519a(byte *param_1,byte *param_2)

{
  byte bVar1;
  byte bVar2;
  size_t sVar3;
  size_t local_c;
  
  sVar3 = _strlen((char *)param_2);
  local_c = sVar3;
  if (sVar3 != 0) {
    do {
      if (local_c == 0) {
        if (((0x5a < *param_1) || (*param_1 < 0x41)) && (*param_1 != 0x5f)) {
          return sVar3;
        }
        return 0;
      }
      bVar1 = *param_1;
      bVar2 = *param_2;
      param_2 = param_2 + 1;
      param_1 = param_1 + 1;
      local_c = local_c - 1;
    } while (bVar1 == bVar2);
  }
  return 0;
}


// 004a522a

byte * FUN_004a522a(byte *param_1,byte *param_2)

{
  if ((*param_1 < 0x30) || (0x39 < *param_1)) {
    for (; *param_1 != 0; param_1 = param_1 + 1) {
      if ((0x60 < *param_1) && (*param_1 < 0x7b)) {
        *param_1 = *param_1 - 0x20;
      }
      if ((*param_1 < 0x41) || (0x5a < *param_1)) {
        if ((*param_1 < 0x30) || (0x39 < *param_1)) {
          if (*param_1 != 0x5f) break;
          *param_2 = *param_1;
        }
        else {
          *param_2 = *param_1;
        }
      }
      else {
        *param_2 = *param_1;
      }
      param_2 = param_2 + 1;
    }
    *param_2 = 0;
  }
  else {
    *param_2 = 0;
  }
  return param_1;
}


// 004a5338

void FUN_004a5338(ushort param_1,int param_2)

{
  undefined1 *puVar1;
  int iVar2;
  uint uVar3;
  ushort *local_c;
  
  uVar3 = (uint)*(ushort *)(&DAT_00551b32 + (uint)param_1 * 2);
  if (*(int *)(param_2 + 0x50) == 0) {
    *(uint *)(param_2 + 0x4c) = uVar3 + 2;
    local_c = (ushort *)
              thunk_FUN_004d8db4(*(undefined4 *)(param_2 + 0x4c),
                                 s_D__Driver_Game_compiler_c_005523d4,0x4c3);
    if (local_c == (ushort *)0x0) {
      thunk_FUN_004a5ac3(s_Not_enough_memory_for_new_comman_005523f0);
    }
    *(ushort **)(param_2 + 0x50) = local_c;
  }
  else {
    iVar2 = thunk_FUN_004d8db4(*(int *)(param_2 + 0x4c) + uVar3,s_D__Driver_Game_compiler_c_00552414
                               ,0x4cf);
    if (iVar2 == 0) {
      thunk_FUN_004a5ac3(s_Not_enough_memory_for_new_comman_00552430);
    }
    thunk_FUN_005283b5(iVar2,*(undefined4 *)(param_2 + 0x50),*(undefined4 *)(param_2 + 0x4c));
    thunk_FUN_004d8f30(*(undefined4 *)(param_2 + 0x50));
    *(undefined4 *)(param_2 + 0x50) = 0;
    *(int *)(param_2 + 0x50) = iVar2;
    local_c = (ushort *)(iVar2 + -2 + *(int *)(param_2 + 0x4c));
    *(uint *)(param_2 + 0x4c) = *(int *)(param_2 + 0x4c) + uVar3;
  }
  *local_c = param_1;
  local_c = local_c + 1;
  if (param_1 == 0xe) {
    thunk_FUN_004a5505(local_c,&DAT_00552454);
  }
  else if (param_1 == 0x14) {
    thunk_FUN_004a5505(local_c,&DAT_00552458);
  }
  else if (param_1 == 0x15) {
    thunk_FUN_004a5505(local_c,&DAT_0055245c);
  }
  else {
    thunk_FUN_004a5505(local_c,*(undefined4 *)(&DAT_00551bb0 + (uint)param_1 * 4));
  }
  puVar1 = (undefined1 *)(*(int *)(param_2 + 0x50) + -2 + *(int *)(param_2 + 0x4c));
  *puVar1 = 0;
  puVar1[1] = 0;
  return;
}


// 004a5505

/* WARNING: Removing unreachable block (ram,0x004a560e) */

undefined4 * FUN_004a5505(undefined4 *param_1,char *param_2)

{
  int local_c;
  int local_8;
  
  local_c = 0;
  local_8 = 0;
  do {
    if (*param_2 == 'f') {
      switch(local_8) {
      case 0:
        *param_1 = DAT_0113425c;
        break;
      case 1:
        *param_1 = DAT_01134258;
        break;
      case 2:
        *param_1 = DAT_01134254;
        break;
      case 3:
        *param_1 = DAT_01134250;
      }
      local_8 = local_8 + 1;
      param_1 = param_1 + 1;
    }
    else {
      if (*param_2 != 'i') {
        return param_1;
      }
      switch(local_c) {
      case 0:
        *(undefined2 *)param_1 = DAT_011340c8;
        break;
      case 1:
        *(undefined2 *)param_1 = DAT_01134112;
        break;
      case 2:
        *(undefined2 *)param_1 = DAT_01134114;
        break;
      case 3:
        *(undefined2 *)param_1 = DAT_01134116;
      }
      local_c = local_c + 1;
      param_1 = (undefined4 *)((int)param_1 + 2);
    }
    param_2 = param_2 + 1;
  } while( true );
}


// 004a5634

/* WARNING: Type propagation algorithm not settling */

void FUN_004a5634(byte *param_1,undefined2 param_2)

{
  undefined2 *puVar1;
  byte bVar2;
  void *pvVar3;
  int iVar4;
  int iVar5;
  byte local_108;
  undefined2 auStack_107 [127];
  int local_8;
  
  local_8 = 0;
  while ((*param_1 != 0x3d && (*param_1 != 0x20))) {
    (&local_108)[local_8] = *param_1;
    param_1 = param_1 + 1;
    if ((0x60 < (&local_108)[local_8]) && ((&local_108)[local_8] < 0x7a)) {
      (&local_108)[local_8] = (&local_108)[local_8] - 0x20;
    }
    local_8 = local_8 + 1;
  }
  (&local_108)[local_8] = 0;
  do {
    bVar2 = *param_1;
    param_1 = param_1 + 1;
  } while (bVar2 != 0x3d);
  for (; *param_1 == 0x20; param_1 = param_1 + 1) {
  }
  FUN_0052e250(param_1,&DAT_00552460,&param_2);
  (&local_108)[local_8] = 0;
  puVar1 = (undefined2 *)((int)auStack_107 + local_8);
  local_8 = local_8 + 1;
  *puVar1 = param_2;
  iVar4 = local_8 + 2;
  DAT_01134124 = DAT_01134124 + 1;
  if (DAT_00b1ff60 == (void *)0x0) {
    iVar5 = local_8 + 4;
    local_8 = iVar4;
    DAT_00b1ff60 = (void *)thunk_FUN_004d8db4(iVar5,s_D__Driver_Game_compiler_c_005524a8,0x585);
    if (DAT_00b1ff60 == (void *)0x0) {
      if (DAT_00bdf9c8 == 0) {
        thunk_FUN_004a5ac3(s_Not_enough_memory_for_model_name_005524c4);
      }
    }
    else {
      _memset(DAT_00b1ff60,0,local_8 + 2);
      thunk_FUN_005283b5(DAT_00b1ff60,&local_108,local_8);
      DAT_00b1ff64 = local_8 + 2;
    }
  }
  else {
    local_8 = iVar4;
    pvVar3 = (void *)thunk_FUN_004d8db4(DAT_00b1ff64 + iVar4,s_D__Driver_Game_compiler_c_00552464,
                                        0x56f);
    if (pvVar3 == (void *)0x0) {
      if (DAT_00bdf9c8 == 0) {
        thunk_FUN_004a5ac3(s_Not_enough_memory_for_model_name_00552480);
      }
    }
    else {
      thunk_FUN_005283b5(pvVar3,DAT_00b1ff60,DAT_00b1ff64 + -2);
      _memset((void *)((int)pvVar3 + DAT_00b1ff64 + -2),0,local_8 + 2);
      thunk_FUN_005283b5((int)pvVar3 + DAT_00b1ff64 + -2,&local_108,local_8);
      thunk_FUN_004d8f30(DAT_00b1ff60);
      DAT_00b1ff64 = DAT_00b1ff64 + local_8;
      DAT_00b1ff60 = pvVar3;
    }
  }
  return;
}


