/* dircam.h — the replay-director camera record (DIRECTOR_CAMERA), shared by director.c, dirnodes.c,
 * ported60.c, ported61.c and ported112.c.  Plain integer constants: using them never changes the
 * generated code.  Like carfields.h, every name says what it is based on; unknown fields are TODO(RE).
 *
 * Record: 0x8c bytes = int32[0x23].  Written by P61_StoreCamState from the live camera, read back by
 * P61_RestoreCamState, normalised by P61_CamPrepare, edited by the director key handlers in ported60.c,
 * dumped by CameraDump (director.c, Game.exe 004c567a), which prints the game's own field names.
 * DCAM_* are byte offsets for rd32/wr32(rec, DCAM_x); DIRCAM_W_* are the same fields as int32 indices.
 */
#pragma once

/* ---- camera type = DCAM_TYPE (names from GetCameraTypeName, director.c, Game.exe 004c57b7) ---- */
enum {
  DIRCAM_CHASE    = 0x00,   /* "Chase camera" */
  DIRCAM_FLYING   = 0x01,   /* "Flying camera" */
  DIRCAM_INCAR    = 0x02,   /* "In car camera" — P61_RestoreCamState rebuilds the car camera (P61_SetupCamN) */
  DIRCAM_STATIC   = 0x10,   /* "Static camera" — ported60: tripod aimed once at the car (angles from atan2) */
  DIRCAM_WATCHCAR = 0x11    /* "Watch car camera" — the only type that keeps DCAM_FLAG48 */
};
/* TODO(RE): the ported60 key handlers place a tripod as 0x11 first and turn it into 0x10 when aiming at a
   car; the readability pass first read that as "0x10 = tracking, 0x11 = fixed".  The game's own strings
   above win; confirm in the replay director. */

/* ---- byte offsets ---- */
#define DCAM_TYPE      0x00   /* int32: DIRCAM_* (also P59_Mode1137324 while the camera is live) */
#define DCAM_DIST      0x08   /* int32: "Camera distance" (P61_Dist8) */
#define DCAM_MAXDIST   0x0c   /* int32: "Cameras maximum distance" (P61_DistC); P61_CamPrepare copies DCAM_DIST here */
#define DCAM_CAR       0x10   /* int32: index of the followed car (-1 is turned into 0 = player) */
#define DCAM_ANG_REL   0x18   /* int32: angle around the car relative to its heading (0..0xfff, P61_V18).
                                 The static-camera handlers in ported60 store the absolute aim angle here and in
                                 DCAM_ANG_ABS.  TODO(RE): confirm the relative/absolute split */
#define DCAM_ANG_ABS   0x1c   /* int32: car heading + DCAM_ANG_REL (0..0xfff, P61_V1C) */
#define DCAM_PITCH     0x20   /* int32: pitch (P61_V20); ported60 aims it with atan2(dy, horizontal distance) */
#define DCAM_FLAG48    0x48   /* int32: low byte of P60_Var1373C0; toggled by the director "toggle" key in
                                 DIRCAM_WATCHCAR, cleared for every other type.  TODO(RE): meaning */
#define DCAM_POS       0x4c   /* int32[4]: "Camera position" x, y, z (+ a 4th word copied with it) */
#define DCAM_POS_X     (DCAM_POS + 0)
#define DCAM_POS_Y     (DCAM_POS + 4)
#define DCAM_POS_Z     (DCAM_POS + 8)
#define DCAM_HOLD      0x5c   /* int32[4]: "Holding camera position" x, y, z (+ 4th word).  P61_StoreCamState
                                 stores the look-at target (P61_Tgt*) here, the tripod handlers a copy of DCAM_POS,
                                 P61_CamPrepare copies it back into DCAM_POS.  TODO(RE): exact use */
#define DCAM_HOLD_X    (DCAM_HOLD + 0)
#define DCAM_HOLD_Y    (DCAM_HOLD + 4)
#define DCAM_HOLD_Z    (DCAM_HOLD + 8)
#define DCAM_OFFSET    0x6c   /* int32[3]: offset x, y, z (P61_OffX..Z); y = height relative to the car */
#define DCAM_ANGLES    0x7c   /* u16[3]: "Camera angle" (P61_AngB8 / BA / BC) */
#define DCAM_PITCH16   (DCAM_ANGLES + 0)   /* u16 copy of DCAM_PITCH */
#define DCAM_YAW16     (DCAM_ANGLES + 2)   /* u16 copy of the heading */
#define DCAM_SIZE      0x8c

/* ---- the same fields as int32 indices (CameraDump, ClampCameraHeight) ---- */
#define DIRCAM_W_TYPE     (DCAM_TYPE / 4)
#define DIRCAM_W_DIST     (DCAM_DIST / 4)
#define DIRCAM_W_MAXDIST  (DCAM_MAXDIST / 4)
#define DIRCAM_W_POS      (DCAM_POS / 4)      /* 0x13 */
#define DIRCAM_W_HOLDPOS  (DCAM_HOLD / 4)     /* 0x17 */
#define DIRCAM_W_ANGLES   (DCAM_ANGLES / 4)   /* 0x1f, int16[3] */
