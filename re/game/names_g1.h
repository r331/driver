/* names_g1.h — named offsets introduced by the readability pass (group 1) that more than one file of the
 * group uses.  Plain integer constants: using them never changes the generated code.
 * Like carfields.h, every name says what it is based on; unknown fields are TODO(RE). */
#pragma once

/* ---- director camera record (0x8c bytes; ported61.h: "запись камеры режиссёра") ----
 * Written by P61_StoreCamState from the live camera, read back by P61_RestoreCamState, normalised by
 * P61_CamPrepare; ClampCameraHeight (dirnodes.c) walks the same record as int32 words. */
#define DCAM_MODE        0x00   /* int32: camera mode (P59_Mode1137324); 2 = attached to car DCAM_CAR
                                   (P61_SetupCamN), 0x11 = mode that keeps DCAM_FLAG48; others TODO(RE) */
#define DCAM_DIST        0x08   /* int32: distance (P61_Dist8) */
#define DCAM_DIST_C      0x0c   /* int32: second distance (P61_DistC); P61_CamPrepare copies DCAM_DIST here */
#define DCAM_CAR         0x10   /* int32: index of the followed car (-1 is turned into 0 = player) */
#define DCAM_ANG_REL     0x18   /* int32: angle around the car relative to its heading (0..0xfff) */
#define DCAM_ANG_ABS     0x1c   /* int32: car heading + DCAM_ANG_REL (0..0xfff) */
#define DCAM_V20         0x20   /* int32: P61_V20.  TODO(RE): unsure */
#define DCAM_FLAG48      0x48   /* int32: low byte of P60_Var1373C0, only kept in mode 0x11.  TODO(RE): unsure */
#define DCAM_POS         0x4c   /* int32[4]: camera position x, y, z (+ a 4th word copied with it) */
#define DCAM_TARGET      0x5c   /* int32[4]: look-at target x, y, z (+ 4th word) */
#define DCAM_OFFSET      0x6c   /* int32[3]: offset x, y, z (P61_OffX..Z); y = height relative to the car */
#define DCAM_ANGLES      0x7c   /* u16[3]: angles (P61_AngB8 / BA / BC) */
#define DCAM_SIZE        0x8c
