/* trafficrec.h — the traffic record (one per AI traffic car), shared by ported7, ported63, ported95,
 * ported102 and ported119.  Byte offsets for rd32(rec + TREC_x) / rec[TREC_x]; no structures, no code.
 * Each name says what it is based on; anything not confirmed by code carries TODO(RE).
 * Older modules (ported103.c, ported133.c) still use raw offsets with comments. */
#pragma once

/* ---- Traffic record: TrafficRecs (Game.exe 011443e0), 64 (+1) records of 0x54 bytes ----
   State values are the TRF_* enum in ported133.c. */
#define TREC_SIZE       0x54
#define TREC_CAR        0x00   /* u8: car index in P59_CarsTab (record i drives car i+1; RE_PROBE: byte = i) */
#define TREC_STATE      0x01   /* u8: TRF_* state (0 = free slot) */
#define TREC_SUBSTATE   0x02   /* u8: sub-state (P103_TrafficTick: 1 = only refresh the road position) */
#define TREC_F03        0x03   /* u8: TODO(RE): unsure — switches the record via P54_ObjInit; P63_NearOnNode
                                  counts such cars by their current node */
#define TREC_F08        0x08   /* u8: TODO(RE): unsure — non-zero for cars P63_NearOnNode considers */
#define TREC_CLASS      0x09   /* u8: LANE across the road (not a class): written from P59_CellLeft — cells of 0x5dc units
                                  from the road edge, mirrored per direction.  P102_TrafficAhead matches it as the lane,
                                  P63_CarSpeed picks the speed limits P63_LimA/B by lane & 3 (lane-dependent speed).
                                  RE_PROBE run: equal to P59_CellLeft in 493 of 512 samples; the others are state 3
                                  (junction turn, not refreshed).  Name kept for the existing users. */
#define TREC_LANE       0x0e   /* u16: from the road-graph lookup (P101_RdLane; P119_TrafficStep).  TODO(RE): not the lane
                                  (that is +9); RE_PROBE values 0, 1, 2, 4 — road type / width class? */
#define TREC_AT_TARGET  0x10   /* u8: set once the car is within speed + 0x352 of the target point (P119_TrafficStep) */
#define TREC_FLAGS13    0x13   /* u8: bit 3 = slowing down (P63_CarSpeed decays the target speed) */
#define TREC_ROAD_DIST  0x18   /* int32: distance LEFT to the end of the current road segment (next junction) — decreases
                                  as the car drives (RE_PROBE: 317 of 320 consecutive samples).  P101_RdDist. */
#define TREC_ROAD_DONE  0x1c   /* int32: distance already covered from the segment start (P101_RdLeft — that name is the
                                  wrong way round): TREC_ROAD_DIST + TREC_ROAD_DONE = segment length, constant per
                                  segment in every RE_PROBE sample. */
#define TREC_ROAD_NODE  0x20   /* int32: current road node (P101_RdNode) */
#define TREC_ROAD_DIR   0x24   /* int32 (read as int8): road direction 0..3, heading = value << 10 */
#define TREC_NEXT_NODE  0x28   /* int32: road word of the current segment: index into the 0x24-byte segment table
                                  00c39dc0 (P59_CellLeft), bit 0x4000 set while crossing a junction (seen in state 3); any of 0xc000 set = not a plain segment.
                                  Not a node id.  P119_TrafficStep copies TREC_NEXT_NODE2 over it when a turn completes. */
#define TREC_NEXT_NODE2 0x2c   /* int32: road word of the segment after the coming junction (copied into +0x28 on the turn) */
#define TREC_DIR2       0x30   /* int32: road direction after the coming junction = (TREC_ROAD_DIR + TREC_F34) & 3
                                  (RE_PROBE: 457 of 457 samples in state 2); copied into TREC_ROAD_DIR on the turn. */
#define TREC_F34        0x34   /* int32: turn chosen for the coming junction: 0 straight, +1 / -1 = direction index
                                  +1 / -1 (heading +-0x400).  RE_PROBE: always matches TREC_DIR2 - TREC_ROAD_DIR.
                                  P63_CanEnter / P75_TrafficPos use it as the turn. */
#define TREC_SPEED      0x38   /* int32: signed speed (0 = stopped) */
#define TREC_TGT_SPEED  0x3c   /* int32: target speed computed by P63_CarSpeed (from road type, stop lines, obstacles) */
#define TREC_TGT_X      0x40   /* int32: target point x (spawn position of the next segment; ported119) */
#define TREC_TGT_Z      0x44   /* int32: target point z */
#define TREC_CELL_X     0x48   /* int32: map cell of the car, x */
#define TREC_CELL_Z     0x4c   /* int32: map cell of the car, z */
/* Byte +0xc: model of the driven car (RE_PROBE: equal to CAR_MODEL in all 512 samples).  Byte +5: 0 for every
   ordinary traffic record in the Take A Ride run (no cops spawned there) — P60_NextTrafficCar wants it != 0
   together with state 4 (TRF_COP) and model 1; unconfirmed. */
#define TREC_HORN_CD    0x50   /* int32: horn cool-down */
