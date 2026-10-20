/* names_g3.h — field offsets of Game.exe records used by several modules of readability group 3
   (ported63.c, ported79.c, ...).  Offsets only (rd32(rec + TREC_ROAD_NODE)); no structures, no code.
   Each name says what it is based on; anything not confirmed by code carries TODO(RE). */
#pragma once

/* ---- Traffic record: TrafficRecs (Game.exe 011443e0), 64 (+1) records of 0x54 bytes ----
   State values are the TRF_* enum in ported133.c. */
#define TREC_SIZE       0x54
#define TREC_CAR        0x00   /* u8: car index in P59_CarsTab (record i drives car i+1) */
#define TREC_STATE      0x01   /* u8: TRF_* state (0 = free slot) */
#define TREC_SUBSTATE   0x02   /* u8: sub-state (P103_TrafficTick: 1 = only refresh the road position) */
#define TREC_F03        0x03   /* u8: TODO(RE): unsure — switches the record via P54_ObjInit; P63_NearOnNode
                                  counts such cars by their current node */
#define TREC_F08        0x08   /* u8: TODO(RE): unsure — non-zero for cars P63_NearOnNode considers */
#define TREC_CLASS      0x09   /* u8: low 2 bits select the speed limits P63_LimA/P63_LimB */
#define TREC_FLAGS13    0x13   /* u8: bit 3 = slowing down (P63_CarSpeed decays the target speed) */
#define TREC_ROAD_DIST  0x18   /* int32: distance along the road segment (P101_RdDist) */
#define TREC_ROAD_LEFT  0x1c   /* int32: P101_RdLeft — TODO(RE): unsure (remaining distance?) */
#define TREC_ROAD_NODE  0x20   /* int32: current road node (P101_RdNode) */
#define TREC_ROAD_DIR   0x24   /* int32 (read as int8): road direction 0..3, heading = value << 10 */
#define TREC_NEXT_NODE  0x28   /* int32: node the car is heading to — inferred from P63_NearOnNode/P63_CountByNode */
#define TREC_DIR2       0x30   /* int32: second direction matched by P63_NearOnNode — TODO(RE): unsure */
#define TREC_F34        0x34   /* int32: TODO(RE): unsure — -1 = ignore, 0 = blocks the junction (P63_CanEnter) */
#define TREC_SPEED      0x38   /* int32: signed speed (0 = stopped) */
#define TREC_TGT_SPEED  0x3c   /* int32: target speed computed by P63_CarSpeed */
#define TREC_CELL_X     0x48   /* int32: map cell of the car, x */
#define TREC_CELL_Z     0x4c   /* int32: map cell of the car, z */
#define TREC_HORN_CD    0x50   /* int32: horn cool-down */

/* ---- Map model header (ported79.c): 0x38 bytes, followed by its arrays ----
   "Links" are offsets from the map arena in native, absolute addresses in the hook build (P79_OFF/P79_PTR);
   while MDL_LINKED is set in MDL_FLAGS they are absolute, otherwise relative to the model itself. */
#define MDL_HDR_SIZE    0x38
#define MDL_FLAGS       0x02   /* u16: MDL_LINKED, axis-classification marks 0x10 / 0x30 (P79_MarkRecords) */
#define MDL_LINKED      0x8000
#define MDL_PARENT      0x04   /* int32: -1 = own geometry, else index in P79_ModelTab of the model whose
                                  vertex/normal arrays and table +0x34 this one shares */
#define MDL_RADIUS      0x0c   /* float: largest vertex distance from the origin */
#define MDL_RADIUS_XZ   0x10   /* float: same, ignoring Y */
#define MDL_NVERTS      0x14   /* u16: vertices (float4 each) at MDL_VERTS */
#define MDL_NRECS       0x16   /* u16: polygon records at MDL_RECS; one float4 per record at MDL_RECVEC */
#define MDL_N28         0x18   /* u16: float4 entries at MDL_L28 — TODO(RE): unsure what they are */
#define MDL_NBYTES1C    0x1a   /* u16: bytes at MDL_L1C — TODO(RE): unsure */
#define MDL_L1C         0x1c   /* link: byte array */
#define MDL_VERTS       0x20   /* link: vertices, float x, y, z, w (w = 1.0 in memory) */
#define MDL_RECVEC      0x24   /* link: one float4 per record — likely the polygon normal (axis-aligned ones
                                  are classified by P79_VertClass); TODO(RE): confirm */
#define MDL_L28         0x28   /* link: float4 array (MDL_N28 entries) */
#define MDL_RECS        0x2c   /* link: variable-size polygon records; byte 0 = type (size from 00550acc) */
#define MDL_SUB         0x30   /* link: sub-block with links at +0xc, +0x10, +0x14, +0x18 (relative to itself) */
#define MDL_L34         0x34   /* link: table {int32 n; n * 0x14 bytes} or 0 */

/* ---- DirectInput keyboard scan codes (DIK_*, dinput.h) used by the input code ---- */
#define DIK_ESCAPE      0x01
#define DIK_RETURN      0x1c
#define DIK_SPACE       0x39
#define DIK_NUMPADENTER 0x9c
#define DIK_UP          0xc8
#define DIK_LEFT        0xcb
#define DIK_RIGHT       0xcd
#define DIK_DOWN        0xd0

/* ---- Indices into the key configuration P36_KeyCfg (DIK code per action) ----
   4..7 follow the v2.14 native arrow-key block in P36_GetPadButtons; 8..15 the native gamepad
   mapping in plat_di.c (gamepad_keys). */
enum {
  KEYCFG_LEFT = 4, KEYCFG_RIGHT = 5, KEYCFG_GAS = 6, KEYCFG_BRAKE = 7,
  KEYCFG_HARDTURN = 8, KEYCFG_HANDBRAKE = 9, KEYCFG_BURNOUT = 10,
  KEYCFG_LOOKBACK = 13, KEYCFG_HORN = 15
};
