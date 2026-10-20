/* ported60.c — replay director camera commands and a few small helpers (English overview).
   AddCamera / ChangeCamera (004c459f / 004c483e) and the tripod variants act on the director's working
   camera DirectorCam (00d17bc4) in response to menu command ids of the replay director's node tree.
   Also: next nearby cop car for the camera to follow, per-frame object update, particle spawn.  All cdecl. */
#include "ported60.h"
#include "ported43.h"   /* v2.09: P43_FreeCnt/P43_FreeList/A_00C56780 — объекты образа данных (пешеходы) */
#include "ported7.h"
#include "carfields.h"
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

/* DirectorCam fields (ported60.h). */
#define DCAM_MODE    0x00   /* 2 = (TODO(RE): unsure), 0x10 = tripod tracking a car, 0x11 = tripod with fixed view */
#define DCAM_CAR     0x10   /* car index the camera follows (-1 treated as 0) */
#define DCAM_ANG     0x18   /* heading (4096 = 360) */
#define DCAM_ANG_B   0x1c   /* second copy of the heading.  TODO(RE): why two */
#define DCAM_PITCH   0x20
#define DCAM_F48     0x48   /* flag toggled by command "toggle" in mode 0x11.  TODO(RE): meaning */
#define DCAM_POS_X   0x4c   /* camera position x, y, z (+ a 4th word copied with it) */
#define DCAM_POS_Y   0x50
#define DCAM_POS_Z   0x54
#define DCAM_HOLD_X  0x5c   /* copy of the position taken when the tripod is placed.  TODO(RE): exact use */
#define DCAM_HOLD_Y  0x60
#define DCAM_HOLD_Z  0x64
#define DCAM_PITCH16 0x7c   /* int16 copies of pitch / heading */
#define DCAM_ANG16   0x7e
#define COP_FOLLOW_DIST2 0x35a4e900   /* 30000^2: squared distance limit for P60_NextTrafficCar */
static int32_t rd32(const uint8_t *p, uint32_t o) { int32_t v; memcpy(&v, p + o, 4); return v; }
static void    wr32(uint8_t *p, uint32_t o, int32_t v) { memcpy(p + o, &v, 4); }
static void    wr16(uint8_t *p, uint32_t o, uint16_t v) { memcpy(p + o, &v, 2); }
static uint8_t *Cam(void) { return (uint8_t *)&DirectorCam; }

/* P60_NextTrafficCar — Game.exe 004c5c5d.  Despite the name, returns the first car after `from` whose traffic
   record is a cop (record [5] != 0, state [1] == 4 = cop AI, car model kind [0xc] == 1 — the police model?) and is
   within 30000 units of the player (x/z, squared, 32-bit wrapping as in the original); 0 = none. */
int32_t P60_NextTrafficCar(int32_t from) {
  int32_t arg = from + 1;
  const uint8_t *rec = (const uint8_t *)TrafficRecs + (uint32_t)from * 0x54;
  for (int32_t cnt = 0; cnt < 0x40; cnt++, rec += 0x54, arg++) {
    if (arg >= 0x41) return 0;
    if (rec[5] != 0 && rec[0xc] == 1 && rec[1] == 4) {
      const uint8_t *car = (const uint8_t *)P60_Cars + (uint32_t)arg * 0x148;
      int32_t dx = (int32_t)((uint32_t)P59_PosX - (uint32_t)rd32(car, CAR_POS_X));
      int32_t dz = (int32_t)((uint32_t)P59_PosZ - (uint32_t)rd32(car, CAR_POS_Z));
      int32_t d = (int32_t)((uint32_t)dx * (uint32_t)dx + (uint32_t)dz * (uint32_t)dz);
      if (d < COP_FOLLOW_DIST2) return arg;
    }
  }
  return 0;
}

/* общие части команд «треножной» камеры: режим 0x11 — взгляд зафиксирован, 0x10 — следит за машиной */
static void tripod_hold(uint8_t *cam) {
  wr32(cam, DCAM_MODE, 0x11);
  wr32(cam, DCAM_HOLD_X, rd32(cam, DCAM_POS_X)); wr32(cam, DCAM_HOLD_Y, rd32(cam, DCAM_POS_Y)); wr32(cam, DCAM_HOLD_Z, rd32(cam, DCAM_POS_Z));
}
static void tripod_toggle(uint8_t *cam) {
  if (rd32(cam, DCAM_MODE) == 0x11) wr32(cam, DCAM_F48, rd32(cam, DCAM_F48) == 0);
}

/* AddTripodCamera — Game.exe 004c4b3a.  Tripod sub-commands while adding a camera (cmd 0x13..0x16):
   0x13 leave tripod mode (director mode 8), 0x14 fix the view (mode 0x11), 0x15 track the player car
   (mode 0x10, heading toward the car, pitch 0; from mode 0x10 -> director mode 0xa), 0x16 toggle +0x48.
   Resets the followed car to 0. */
void AddTripodCamera(int32_t cmd) {
  uint8_t *cam = Cam();
  const uint8_t *car = (const uint8_t *)P60_Cars;          /* индекс машины сбрасывается в 0 */
  wr32(cam, DCAM_CAR, 0);
  switch (cmd - 0x13) {
  case 0: if (rd32(cam, DCAM_MODE) == 0x11 || rd32(cam, DCAM_MODE) == 0x10) SetDirectorMode(8, 0, 0); break;
  case 1: if (rd32(cam, DCAM_MODE) != 2) tripod_hold(cam); break;
  case 2:
    if (rd32(cam, DCAM_MODE) != 2) {
      if (rd32(cam, DCAM_MODE) == 0x10) { SetDirectorMode(0xa, 0, 0); break; }
      wr32(cam, DCAM_HOLD_X, rd32(cam, DCAM_POS_X)); wr32(cam, DCAM_HOLD_Y, rd32(cam, DCAM_POS_Y)); wr32(cam, DCAM_HOLD_Z, rd32(cam, DCAM_POS_Z));
      int32_t dx = (int32_t)((uint32_t)rd32(car, CAR_POS_X) - (uint32_t)rd32(cam, DCAM_POS_X));
      int32_t dz = (int32_t)((uint32_t)rd32(car, CAR_POS_Z) - (uint32_t)rd32(cam, DCAM_POS_Z));
      int32_t a = (-P44_Atan2(dx, dz)) & 0xfff;
      wr32(cam, DCAM_ANG, a); wr32(cam, DCAM_ANG_B, a);
      wr16(cam, DCAM_ANG16, (uint16_t)a);
      wr32(cam, DCAM_PITCH, 0);
      wr32(cam, DCAM_MODE, 0x10);
    }
    break;
  case 3: tripod_toggle(cam); break;
  default: DebugLog("AddTripodCamera: Unknown command id."); break;
  }
}

/* ChangeTripodCamera — Game.exe 004c4cee.  Same for editing an existing camera (cmd 0x17..0x1a), following the
   camera's own car and also computing the pitch toward it. */
void ChangeTripodCamera(int32_t cmd) {
  uint8_t *cam = Cam();
  const uint8_t *car = (const uint8_t *)P60_Cars + (rd32(cam, DCAM_CAR) == -1 ? 0u : (uint32_t)rd32(cam, DCAM_CAR) * 0x148);
  switch (cmd - 0x17) {
  case 0: if (rd32(cam, DCAM_MODE) == 0x11 || rd32(cam, DCAM_MODE) == 0x10) SetDirectorMode(8, 0, 0); break;
  case 1: if (rd32(cam, DCAM_MODE) != 2) tripod_hold(cam); break;
  case 2:
    if (rd32(cam, DCAM_MODE) != 2) {
      if (rd32(cam, DCAM_MODE) == 0x10) { SetDirectorMode(0xa, 0, 0); break; }
      wr32(cam, DCAM_HOLD_X, rd32(cam, DCAM_POS_X)); wr32(cam, DCAM_HOLD_Y, rd32(cam, DCAM_POS_Y)); wr32(cam, DCAM_HOLD_Z, rd32(cam, DCAM_POS_Z));
      int32_t dx = (int32_t)((uint32_t)rd32(car, CAR_POS_X) - (uint32_t)rd32(cam, DCAM_POS_X));
      int32_t dy = (int32_t)((uint32_t)rd32(car, CAR_POS_Y) - (uint32_t)rd32(cam, DCAM_POS_Y));
      int32_t dz = (int32_t)((uint32_t)rd32(car, CAR_POS_Z) - (uint32_t)rd32(cam, DCAM_POS_Z));
      int32_t a = (-P44_Atan2(dx, dz)) & 0xfff;
      wr32(cam, DCAM_ANG, a); wr32(cam, DCAM_ANG_B, a);
      wr16(cam, DCAM_ANG16, (uint16_t)a);
      int32_t d = (int32_t)((uint32_t)dx * (uint32_t)dx + (uint32_t)dz * (uint32_t)dz);
      int32_t dist = (int32_t)sqrt((double)d);
      int32_t pitch = P44_Atan2(dy, dist);
      wr32(cam, DCAM_PITCH, pitch);
      wr16(cam, DCAM_PITCH16, (uint16_t)pitch);
      wr32(cam, DCAM_MODE, 0x10);
    }
    break;
  case 3: tripod_toggle(cam); break;
  default: DebugLog("ChangeTripodCamera: Unknown command id."); break;
  }
}

/* переход по цепочке узлов до узла с unk18 == stop (или 0) */
/* Follows the director node chain from id through unk18 links until the link is `stop` or 0. */
static DIR_NODE *chain_end(int32_t id, int32_t stop) {
  DIR_NODE *n = FindNodeById(id);
  while (n->unk18 != stop && n->unk18 != 0) n = FindNodeById(n->unk18);
  return n;
}
static void cam_copy_from_rec(const DIRECTOR_CAMERA *src) { memcpy(Cam(), src, 0x8c); }
/* DirectorCam+0x4c..0x58 -> +0x5c..0x68 (c10.. -> c20..; четыре слова) */
static void cam_hold_pos4(uint8_t *cam) {
  for (int i = 0; i < 4; i++) wr32(cam, DCAM_HOLD_X + 4 * i, rd32(cam, DCAM_POS_X + 4 * i));
}

/* AddCamera — Game.exe 004c459f.  Handles a director menu command id while adding a camera; the node at the
   end of the chain selects the group: 9 = chase camera (select / next car), 10 = (TODO(RE)) camera on a car
   with next-car / back commands, 0xb = tripod (AddTripodCamera), 0xc = store the camera at the current frame
   (DirectorUnk6C) replacing any existing one.  DirectorUnk7C receives the next menu node. */
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
        wr32(cam, DCAM_MODE, 2);
        DirectorUnk7C = node->link1;
      }
    } else {
      wr32(cam, DCAM_CAR, P60_NextTrafficCar(rd32(cam, DCAM_CAR)));
    }
    break;
  case 10:
    if (node->id == id) {
      P60_Var1373C0 = 0;
      if (CountNearbyCars() == 0) {
        wr32(cam, DCAM_CAR, 0);
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
      wr32(cam, DCAM_CAR, P60_NextTrafficCar(rd32(cam, DCAM_CAR)));
      P60_CamPrepare(cam);
    }
    break;
  case 0xb:
    if (node->id == id) {
      if (rd32(cam, DCAM_MODE) != 0x11 && rd32(cam, DCAM_MODE) != 0x10) {
        wr32(cam, DCAM_CAR, 0);
        wr32(cam, DCAM_MODE, 0x11);
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

/* ChangeCamera — Game.exe 004c483e.  Same for editing a camera: groups 0xd/0xe/0xf as 9/10/0xb above,
   0x10 -> director mode 9, 0x11 delete the camera at the current frame, 0x12 store the edited camera. */
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
        wr32(cam, DCAM_MODE, 2);
        DirectorUnk7C = node->link1;
      }
    } else {
      wr32(cam, DCAM_CAR, P60_NextTrafficCar(rd32(cam, DCAM_CAR)));
    }
    break;
  case 0xe:
    if (node->id == id) {
      P60_Var1373C0 = 0;
      if (CountNearbyCars() == 0) {
        wr32(cam, DCAM_CAR, 0);
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
      wr32(cam, DCAM_CAR, P60_NextTrafficCar(rd32(cam, DCAM_CAR)));
      P60_CamPrepare(cam);
    }
    break;
  case 0xf:
    if (node->id == id) {
      if (rd32(cam, DCAM_MODE) != 0x11 && rd32(cam, DCAM_MODE) != 0x10) {
        wr32(cam, DCAM_MODE, 0x11);
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

/* P60_ObjUpdate — Game.exe 004a399a.  For an active object (+0x10 != 0): y (+0x24) = -ground height at its
   position (+0x20), extra update when flag 0x200, P14_Fn004A3B80 when +0x14 == 1.  TODO(RE): object type. */
void P60_ObjUpdate(uint8_t *o) {
  if (o != NULL && rd32(o, 0x10) != 0) {
    wr32(o, 0x24, -GetGroundHeight((int *)(o + 0x20)));
    if ((uint32_t)rd32(o, 0x10) & 0x200) P60_Fn4CA802(o);
    if (rd32(o, 0x14) == 1) P14_Fn004A3B80(o);
  }
}

/* P60_SpawnParticle — Game.exe 0051378b.  When flag == 0 and fewer than P60_PartLimit objects are free
   (TODO(RE): the comparison reads "free count < limit" — check), consumes one random number, marks p
   (+0 = 1, +0x1c = 1) and spawns it via P60_Fn514261.  Returns 1 if spawned. */
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
