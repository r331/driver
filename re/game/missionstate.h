/* missionstate.h — values of the mission state block 00c810c0.. (P56_Blk84): the state word 00c810c4
 * (P14_00c810c4 = P16_IdleMode = P56_Blk84[1]), the failure reason 00c810e8 (P14_00c810e8 = P16_IdleArg1 =
 * P56_Blk84[10]) and the end countdown 00c81100 (P14_00c81100 = P16_IdleArg2 = P56_Blk84[16]).
 * Settled from every writer in Game.exe (objdump xref of 0xc810c4 / 0xc810e8) and the RE_PROBE "mission" topic.
 * Plain integer constants: using them never changes the generated code. */
#pragma once

/* ---- 00c810c4: mission state ---- */
#define MSTATE_NONE        0x0000   /* no objective running (P138_LoadMission, MS_WAITFOROBJECTIVECOMPLETE after success) */
#define MSTATE_OBJECTIVE   0x0001   /* an objective / target is active (P115_TargetTick turns it into MSTATE_OBJ_DONE) */
#define MSTATE_RACE        0x0003   /* race running (MS_INITIALISERACE; P76_FlashStep turns it into MSTATE_OBJ_DONE) */
#define MSTATE_FAILED      0x0ff0   /* mission failed — the reason is in 00c810e8 (MREASON_*) */
#define MSTATE_OBJ_DONE    0x7fff   /* current objective reached; MS_WAITFOROBJECTIVECOMPLETE resets it to 0 and continues */
#define MSTATE_PASSED_BIT  0x8000   /* MS_MISSIONEND ors it in: mission passed (== 0x8000: P137_LevelEnd plays the cut-scene) */
#define MSTATE_RACE_DONE   0x80f1   /* MS_RACECOMPLETE */

/* ---- 00c810e8: failure reason (only meaningful with MSTATE_FAILED; 0 = success) ----
   P47_ResetPick plays the speech slot of reasons 1..4.  Reason 4 has no writer in Game.exe. */
#define MREASON_NONE       0
#define MREASON_TIME_OUT   1   /* a script timer reached 0 (P114_Timer), the chase marker was shot down (P140_MrkFly),
                                  or the script referenced a missing chunk (P58_FindChunk) */
#define MREASON_FAILED     2   /* the car stayed with fewer than 3 wheels on the ground for 300 ticks (600 with the
                                  cheat options 00bdfa44 / 00bdfa58) — P16_IdleTimer, i.e. flipped or
                                  stuck — and the script's own fail command (P127 set_fail) */
#define MREASON_LOST       3   /* the target got away: too far from the target car (P133_TrafficTick, > 0x16b) or a script
                                  object left its range (P98_ScriptRange) */
#define MREASON_SEQUENCE   5   /* the timed sequence 00d11920 ran out (P132_GameLogic) — TODO(RE): which game event */

/* ---- 00c81100: frames left before the result screen once the mission ended (0x5a / 0x96 / 0xb4 = 1.8 / 3 / 3.6 s at
   50 ticks per second) ---- */
