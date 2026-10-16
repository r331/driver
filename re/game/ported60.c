#include "ported60.h"
#include <math.h>
#include <string.h>

#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P60_Var1373C0")
#undef P60_Var1373C0
#pragma push_macro("P60_Var1373C0") /*gvi*/
#undef P60_Var1373C0 /*gvi*/
int32_t P60_Var1373C0;
#pragma pop_macro("P60_Var1373C0") /*gvi*/
#pragma pop_macro("P60_Var1373C0")
#endif
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P60_PartLimit")
#undef P60_PartLimit
#pragma push_macro("P60_PartLimit") /*gvi*/
#undef P60_PartLimit /*gvi*/
int32_t P60_PartLimit;
#pragma pop_macro("P60_PartLimit") /*gvi*/
#pragma pop_macro("P60_PartLimit")
#endif

static int32_t rd32(const uint8_t *p, uint32_t o) { int32_t v; memcpy(&v, p + o, 4); return v; }
static void    wr32(uint8_t *p, uint32_t o, int32_t v) { memcpy(p + o, &v, 4); }
static void    wr16(uint8_t *p, uint32_t o, uint16_t v) { memcpy(p + o, &v, 2); }
static uint8_t *Cam(void) { return (uint8_t *)&DirectorCam; }

int32_t P60_NextTrafficCar(int32_t from) {
  int32_t arg = from + 1;
  const uint8_t *rec = (const uint8_t *)TrafficRecs + (uint32_t)from * 0x54;
  for (int32_t cnt = 0; cnt < 0x40; cnt++, rec += 0x54, arg++) {
    if (arg >= 0x41) return 0;
    if (rec[5] != 0 && rec[0xc] == 1 && rec[1] == 4) {
      const uint8_t *car = (const uint8_t *)P60_Cars + (uint32_t)arg * 0x148;
      int32_t dx = (int32_t)((uint32_t)P59_PosX - (uint32_t)rd32(car, 0xc8));
      int32_t dz = (int32_t)((uint32_t)P59_PosZ - (uint32_t)rd32(car, 0xd0));
      int32_t d = (int32_t)((uint32_t)dx * (uint32_t)dx + (uint32_t)dz * (uint32_t)dz);
      if (d < 0x35a4e900) return arg;
    }
  }
  return 0;
}

/* общие части команд «треножной» камеры: режим 0x11 — взгляд зафиксирован, 0x10 — следит за машиной */
static void tripod_hold(uint8_t *cam) {
  wr32(cam, 0, 0x11);
  wr32(cam, 0x5c, rd32(cam, 0x4c)); wr32(cam, 0x60, rd32(cam, 0x50)); wr32(cam, 0x64, rd32(cam, 0x54));
}
static void tripod_toggle(uint8_t *cam) {
  if (rd32(cam, 0) == 0x11) wr32(cam, 0x48, rd32(cam, 0x48) == 0);
}

void AddTripodCamera(int32_t cmd) {
  uint8_t *cam = Cam();
  const uint8_t *car = (const uint8_t *)P60_Cars;          /* индекс машины сбрасывается в 0 */
  wr32(cam, 0x10, 0);
  switch (cmd - 0x13) {
  case 0: if (rd32(cam, 0) == 0x11 || rd32(cam, 0) == 0x10) SetDirectorMode(8, 0, 0); break;
  case 1: if (rd32(cam, 0) != 2) tripod_hold(cam); break;
  case 2:
    if (rd32(cam, 0) != 2) {
      if (rd32(cam, 0) == 0x10) { SetDirectorMode(0xa, 0, 0); break; }
      wr32(cam, 0x5c, rd32(cam, 0x4c)); wr32(cam, 0x60, rd32(cam, 0x50)); wr32(cam, 0x64, rd32(cam, 0x54));
      int32_t dx = (int32_t)((uint32_t)rd32(car, 0xc8) - (uint32_t)rd32(cam, 0x4c));
      int32_t dz = (int32_t)((uint32_t)rd32(car, 0xd0) - (uint32_t)rd32(cam, 0x54));
      int32_t a = (-P44_Atan2(dx, dz)) & 0xfff;
      wr32(cam, 0x18, a); wr32(cam, 0x1c, a);
      wr16(cam, 0x7e, (uint16_t)a);
      wr32(cam, 0x20, 0);
      wr32(cam, 0, 0x10);
    }
    break;
  case 3: tripod_toggle(cam); break;
  default: DebugLog("AddTripodCamera: Unknown command id."); break;
  }
}

void ChangeTripodCamera(int32_t cmd) {
  uint8_t *cam = Cam();
  const uint8_t *car = (const uint8_t *)P60_Cars + (rd32(cam, 0x10) == -1 ? 0u : (uint32_t)rd32(cam, 0x10) * 0x148);
  switch (cmd - 0x17) {
  case 0: if (rd32(cam, 0) == 0x11 || rd32(cam, 0) == 0x10) SetDirectorMode(8, 0, 0); break;
  case 1: if (rd32(cam, 0) != 2) tripod_hold(cam); break;
  case 2:
    if (rd32(cam, 0) != 2) {
      if (rd32(cam, 0) == 0x10) { SetDirectorMode(0xa, 0, 0); break; }
      wr32(cam, 0x5c, rd32(cam, 0x4c)); wr32(cam, 0x60, rd32(cam, 0x50)); wr32(cam, 0x64, rd32(cam, 0x54));
      int32_t dx = (int32_t)((uint32_t)rd32(car, 0xc8) - (uint32_t)rd32(cam, 0x4c));
      int32_t dy = (int32_t)((uint32_t)rd32(car, 0xcc) - (uint32_t)rd32(cam, 0x50));
      int32_t dz = (int32_t)((uint32_t)rd32(car, 0xd0) - (uint32_t)rd32(cam, 0x54));
      int32_t a = (-P44_Atan2(dx, dz)) & 0xfff;
      wr32(cam, 0x18, a); wr32(cam, 0x1c, a);
      wr16(cam, 0x7e, (uint16_t)a);
      int32_t d = (int32_t)((uint32_t)dx * (uint32_t)dx + (uint32_t)dz * (uint32_t)dz);
      int32_t dist = (int32_t)sqrt((double)d);
      int32_t pitch = P44_Atan2(dy, dist);
      wr32(cam, 0x20, pitch);
      wr16(cam, 0x7c, (uint16_t)pitch);
      wr32(cam, 0, 0x10);
    }
    break;
  case 3: tripod_toggle(cam); break;
  default: DebugLog("ChangeTripodCamera: Unknown command id."); break;
  }
}

/* переход по цепочке узлов до узла с unk18 == stop (или 0) */
static DIR_NODE *chain_end(int32_t id, int32_t stop) {
  DIR_NODE *n = FindNodeById(id);
  while (n->unk18 != stop && n->unk18 != 0) n = FindNodeById(n->unk18);
  return n;
}
static void cam_copy_from_rec(const DIRECTOR_CAMERA *src) { memcpy(Cam(), src, 0x8c); }
/* DirectorCam+0x4c..0x58 -> +0x5c..0x68 (c10.. -> c20..; четыре слова) */
static void cam_hold_pos4(uint8_t *cam) {
  for (int i = 0; i < 4; i++) wr32(cam, 0x5c + 4 * i, rd32(cam, 0x4c + 4 * i));
}

void AddCamera(int32_t id) {
  uint8_t *cam = Cam();
  DIR_NODE *node = chain_end(id, 6);
  switch (node->id) {
  case 9:
    if (node->id == id) {
      P60_Var1373C0 = 0;
      if (CountNearbyCars() == 0) {
        P59_Mode1137324 = 2;
        P60_SetupCamN(0);
        StoreCameraState(cam);
      } else {
        wr32(cam, 0, 2);
        DirectorUnk7C = node->link1;
      }
    } else {
      wr32(cam, 0x10, P60_NextTrafficCar(rd32(cam, 0x10)));
    }
    break;
  case 10:
    if (node->id == id) {
      P60_Var1373C0 = 0;
      if (CountNearbyCars() == 0) {
        wr32(cam, 0x10, 0);
        P60_CamPrepare(cam);
      } else {
        P60_CamPrepare(cam);
        RestoreCameraState(cam);
      }
      DirectorUnk7C = node->link1;
      DIR_NODE *n2 = FindNodeById(node->link1);
      if (n2->flags & 4) DirectorUnk7C = n2->link1;
    } else if (id == 0x1f) {
      SetDirectorMode(8, 0, 0);
    } else if (id == 0x1e) {
      wr32(cam, 0x10, P60_NextTrafficCar(rd32(cam, 0x10)));
      P60_CamPrepare(cam);
    }
    break;
  case 0xb:
    if (node->id == id) {
      if (rd32(cam, 0) != 0x11 && rd32(cam, 0) != 0x10) {
        wr32(cam, 0x10, 0);
        wr32(cam, 0, 0x11);
        cam_hold_pos4(cam);
      }
      DirectorUnk7C = node->link1;
    } else {
      AddTripodCamera(id);
    }
    break;
  case 0xc: {
    DropCameraBackup();
    DIRECTOR_CAMERA *c = FindCameraById(DirectorUnk6C);
    if (c != NULL) DeleteCamera(c->index);
    AddDirectorCamera(&DirectorCam, DirectorUnk6C);
    cam_copy_from_rec(FindCameraForFrame(DirectorUnk6C));
    DirectorUnk7C = 6;
    break;
  }
  default: DebugLog("AddCamera: Unknown command id.\n"); break;
  }
}

void ChangeCamera(int32_t id) {
  uint8_t *cam = Cam();
  DIR_NODE *node = chain_end(id, 7);
  switch (node->id) {
  case 0xd:
    if (node->id == id) {
      P60_Var1373C0 = 0;
      if (CountNearbyCars() == 0) {
        P59_Mode1137324 = 2;
        P60_SetupCamN(0);
        StoreCameraState(cam);
      } else {
        wr32(cam, 0, 2);
        DirectorUnk7C = node->link1;
      }
    } else {
      wr32(cam, 0x10, P60_NextTrafficCar(rd32(cam, 0x10)));
    }
    break;
  case 0xe:
    if (node->id == id) {
      P60_Var1373C0 = 0;
      if (CountNearbyCars() == 0) {
        wr32(cam, 0x10, 0);
        P60_CamPrepare(cam);
        RestoreCameraState(cam);
      } else if (P59_Mode1137324 != 0) {
        P60_CamPrepare(cam);
        RestoreCameraState(cam);
      }
      DirectorUnk7C = node->link1;
      DIR_NODE *n2 = FindNodeById(node->link1);
      if (n2->flags & 4) DirectorUnk7C = n2->link1;
    } else if (id == 0x23) {
      SetDirectorMode(8, 0, 0);
    } else if (id == 0x22) {
      wr32(cam, 0x10, P60_NextTrafficCar(rd32(cam, 0x10)));
      P60_CamPrepare(cam);
    }
    break;
  case 0xf:
    if (node->id == id) {
      if (rd32(cam, 0) != 0x11 && rd32(cam, 0) != 0x10) {
        wr32(cam, 0, 0x11);
        cam_hold_pos4(cam);
      }
      DirectorUnk7C = node->link1;
    } else {
      ChangeTripodCamera(id);
    }
    break;
  case 0x10:
    SetDirectorMode(9, 0, 0);
    break;
  case 0x11: {
    DIRECTOR_CAMERA *c = FindCameraForFrame(DirectorUnk6C);
    if (c != NULL) DeleteCamera(c->index);
    DirectorUnk7C = (FindCameraForFrame(DirectorUnk6C) == NULL) ? 6 : 7;
    break;
  }
  case 0x12: {
    DropCameraBackup();
    DIRECTOR_CAMERA *c = FindCameraForFrame(DirectorUnk6C);
    StoreCameraState(c);
    RenumberCameras();
    cam_copy_from_rec(c);
    DirectorUnk7C = 7;
    break;
  }
  default: DebugLog("ChangeCamera: Unknown command id."); break;
  }
}

void P60_ObjUpdate(uint8_t *o) {
  if (o != NULL && rd32(o, 0x10) != 0) {
    wr32(o, 0x24, -GetGroundHeight((int *)(o + 0x20)));
    if ((uint32_t)rd32(o, 0x10) & 0x200) P60_Fn4CA802(o);
    if (rd32(o, 0x14) == 1) P14_Fn004A3B80(o);
  }
}

int32_t P60_SpawnParticle(uint8_t *p, int32_t flag) {
  int32_t ok = 0;
  if (P43_FreeCnt < P60_PartLimit && flag == 0) {
    (void)Rand_004D9078();
    wr16(p, 0, 1);
    wr32(p, 0x1c, 1);
    P60_Fn514261(p);
    ok = 1;
  }
  return ok;
}
