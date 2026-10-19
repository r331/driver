#pragma once
/* names_g5.h — names shared by several readability-pass files (group 5): replay-director camera types.
   Values from GetCameraTypeName (director.c, Game.exe 004c57b7), which prints the game's own names. */

/* DIRECTOR_CAMERA type (first word of a camera record, cam->unk00). */
enum {
  DIRCAM_CHASE    = 0x00,   /* "Chase camera" */
  DIRCAM_FLYING   = 0x01,   /* "Flying camera" */
  DIRCAM_INCAR    = 0x02,   /* "In car camera" */
  DIRCAM_STATIC   = 0x10,   /* "Static camera" */
  DIRCAM_WATCHCAR = 0x11    /* "Watch car camera" */
};

/* Word indices into a camera record viewed as int32[0x23] (from CameraDump, Game.exe 004c567a). */
#define DIRCAM_W_TYPE     0x00
#define DIRCAM_W_DIST     0x02   /* camera distance */
#define DIRCAM_W_MAXDIST  0x03   /* maximum distance */
#define DIRCAM_W_POS      0x13   /* int32[3] camera position x, y, z */
#define DIRCAM_W_HOLDPOS  0x17   /* int32[3] "holding" camera position */
#define DIRCAM_W_ANGLES   0x1f   /* int16[3] camera angles */
