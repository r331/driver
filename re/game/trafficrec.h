/* trafficrec.h — the traffic record (one per AI traffic car), shared by ported7, ported63, ported95,
 * ported102 and ported119.  Byte offsets for rd32(rec + TREC_x) / rec[TREC_x]; no structures, no code.
 * Each name says what it is based on; anything not confirmed by code carries TODO(RE).
 * Older modules (ported103.c, ported133.c) still use raw offsets with comments. */
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
#define TREC_CLASS      0x09   /* u8: low 2 bits select the speed limits P63_LimA/P63_LimB.  P102_TrafficAhead
                                  compares it as the "lane".  TODO(RE): class or lane? */
#define TREC_LANE       0x0e   /* u16: lane from the road-graph lookup (P101_RdLane; P119_TrafficStep) */
#define TREC_AT_TARGET  0x10   /* u8: set once the car is within speed + 0x352 of the target point (P119_TrafficStep) */
#define TREC_FLAGS13    0x13   /* u8: bit 3 = slowing down (P63_CarSpeed decays the target speed) */
#define TREC_ROAD_DIST  0x18   /* int32: distance along the road segment (P101_RdDist); ported119 reads it as the
                                  distance to the next road node.  TODO(RE): which end it is measured from */
#define TREC_ROAD_LEFT  0x1c   /* int32: P101_RdLeft — TODO(RE): unsure (remaining distance?) */
#define TREC_ROAD_NODE  0x20   /* int32: current road node (P101_RdNode) */
#define TREC_ROAD_DIR   0x24   /* int32 (read as int8): road direction 0..3, heading = value << 10 */
#define TREC_NEXT_NODE  0x28   /* int32: node the car is heading to — inferred from P63_NearOnNode/P63_CountByNode.
                                  P119_TrafficStep first stores the road word under the car here, then copies
                                  TREC_NEXT_NODE2 over it on the turn.  TODO(RE): road word or node id? */
#define TREC_NEXT_NODE2 0x2c   /* int32: value copied into TREC_NEXT_NODE when a turn completes (P119_TrafficStep) */
#define TREC_DIR2       0x30   /* int32: direction after the junction turn (P119_TrafficStep aligns to it, then copies it
                                  into TREC_ROAD_DIR); also matched by P63_NearOnNode.  TODO(RE): confirm */
#define TREC_F34        0x34   /* int32: TODO(RE): unsure — -1 = ignore, 0 = blocks the junction (P63_CanEnter) */
#define TREC_SPEED      0x38   /* int32: signed speed (0 = stopped) */
#define TREC_TGT_SPEED  0x3c   /* int32: target speed computed by P63_CarSpeed (from road type, stop lines, obstacles) */
#define TREC_TGT_X      0x40   /* int32: target point x (spawn position of the next segment; ported119) */
#define TREC_TGT_Z      0x44   /* int32: target point z */
#define TREC_CELL_X     0x48   /* int32: map cell of the car, x */
#define TREC_CELL_Z     0x4c   /* int32: map cell of the car, z */
#define TREC_HORN_CD    0x50   /* int32: horn cool-down */
