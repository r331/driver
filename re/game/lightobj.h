/* lightobj.h — light object record (lamp flares and their trails), shared by ported143.c (sun flare /
 * lamp glow) and ported144.c (light flares).  Built in camera space by 004aaf3a for objects with flag
 * 0x20000.  Byte offsets only; no structures, no code. */
#pragma once

#define LO_X      0x00    /* float camera-space x, y, z */
#define LO_Y      0x04
#define LO_Z      0x08
#define LO_EMIT   0x10    /* 3 dwords passed to PushEntry_004CC784 (reflection queue; presumably the world position) */
#define LO_CAR    0x50    /* int16 car index (row of P143_LampHist, 0x140 bytes = 8 lamps) */
#define LO_LAMP   0x54    /* int16 lamp index 0..7, -1 = no trail */
#define LO_TYPE   0x64    /* uint16: & 0x7f flare type (row of 00553870), 0x80 = directional (fades off-axis) */
#define LO_FLAGS  0x68    /* 0xe00000 = has a trail, 0x800000 = trail history per car (P143_LampHist) */
#define LO_DIR_V  0x6c    /* uint16 facing angle compared with the vertical angle to the camera */
#define LO_DIR_H  0x6e    /* uint16 facing angle compared with the horizontal angle to the camera */

/* Trail history record (0x28 bytes, P143_LampHist): 4 x {int32 sx, int32 sy} ring indexed by frame & 3,
   +0x20 int16 frame of the last update. */
#define HIST_FRAME 0x20
