/* carfields.h — byte offsets of fields inside one car record of the car table (cartab.h, p99_car_t,
 * Game.exe 00d077c0, 66 records x 0x148 bytes: 0 = player, 1..64 = traffic/mission cars, 0x41 = spare).
 *
 * Much of the ported physics/AI code walks a car record through a raw "uint8_t *" (because the same
 * code also runs on records that the hook build reaches by Game.exe address), so fields are read with
 * rd32(car + 0x110) etc.  These macros give those offsets names: "rd32(car + CAR_SPEED)".  They are
 * plain integer constants, so using them never changes the generated code.
 *
 * Confidence: a name is given only where the use in the ported code makes the meaning clear; every
 * entry says what it is based on.  Fields still unknown are marked TODO(RE). */
#pragma once

/* ---- identity ---- */
#define CAR_ID          0x00   /* u8: slot id: 0 = player, 1..64 = traffic/mission car (traffic record id-1),
                                  0x41 = spare record 00d0cb08.  cartab.h calls byte 0 "state"; the physics/AI
                                  code only ever uses it as this id. */
#define CAR_MODEL       0x02   /* u8: car model type; index into the per-model table 00d0cc60 (stride 0x16c) */
#define CAR_MAT         0x04   /* int16[9]: orientation matrix, 20.12 fixed (p99_car_t.mat) */
#define CAR_MAT_YY      0x0c   /* int16: mat[4] (row 1, col 1) — Y of the car's up axis; > 0x800 means the car is
                                  less than 60 degrees from upright (used to pick 4 vs 12 body contact points) */

/* ---- rigid-body state (integrated by P142_CarsStep / P142_WheelPhys) ---- */
#define CAR_POS2        0x18   /* int32[3]: position x, y, z used by the physics step (p99_car_t.pos2) */
#define CAR_BODY        0x24   /* start of the 13-int32 rigid-body block integrated by P142_CarsStep:
                                  pos_hi[3], quat[4], vel[3], angvel[3] (P94_PackState reads it from here) */
#define CAR_BODY_INTS   13
#define CAR_POS_HI      0x24   /* int32[3]: same position << 4, keeping 4 extra fractional bits */
#define CAR_QUAT        0x30   /* int32[4]: orientation quaternion x, y, z, w (20.12) */
#define CAR_VEL         0x40   /* int32[3]: linear velocity x, y, z (world units << 8 per step, see P74_Dist) */
#define CAR_ANGVEL      0x4c   /* int32[3]: angular velocity (crossed with lever arms in the contact solver) */
#define CAR_DVEL_PEND   0x58   /* int32[3]: pending linear velocity change (impulse / mass, CAR_VEL units).  Each P142_CarsStep
                                  halves it and adds the half to CAR_VEL, so it decays over a few steps; P94_SpringStep
                                  (wheel step) rewrites it.  Reset value y = -0x2aaa (ported56/137): a downward kick at
                                  spawn.  RE_PROBE run: (0, -10922, 0) on the first step.  Named CAR_FORCE_OUT before. */
#define CAR_DANGVEL_PEND 0x68  /* int32[3]: pending angular velocity change (CAR_ANGVEL units): P94_SpringStep stores the
                                  wheel-step value, ported129 (car vs static object) adds r x J of a hit.  P142_CarsStep adds
                                  half of it to CAR_ANGVEL and then clears it.  So it is an angular *impulse* accumulator, not
                                  a torque.  RE_PROBE run: non-zero only after contacts.  Named CAR_TORQUE_OUT before. */

/* ---- wheels: 4 records of 4 bytes, index 0..3; even = front (steered), odd = rear ---- */
#define CAR_WHEEL       0x78   /* base of wheel i: car + CAR_WHEEL + i * CAR_WHEEL_SIZE */
#define CAR_WHEEL_SIZE  4
#define WHEEL_COMPRESS  0      /* u8: suspension compression of the last step (0 = in the air, max 0x3c) */
#define WHEEL_LOCKED    1      /* u8: wheel locked (hard braking at speed, or handbrake on the rear pair) */
#define WHEEL_SURFACE   2      /* u8: surface id under the wheel (copied from P56_B2EA48) */
#define CAR_GROUND_PT   0x88   /* 4 x {int32 x, y, z, pad}: ground point under the first four body contact points */
#define CAR_GROUND_PT_SIZE 0x10

#define CAR_POS         0xc8   /* int32[3]: world position x, y, z (p99_car_t.pos; player = 00d07888) */
#define CAR_POS_X       0xc8
#define CAR_POS_Y       0xcc
#define CAR_POS_Z       0xd0
#define CAR_VEL_INT     0xd8   /* int32[3]: velocity rounded to integer (CAR_VEL + 0x800 >> 12), refreshed each step */
#define CAR_ANG         0xe8   /* int16[3]: Euler angles, likely pitch, heading, roll (+0xea = heading as int16) */
#define CAR_F0F4        0xf4   /* int32: TODO(RE): unsure — copy of P102_D0DD74 after the ground probe of each step */

/* ---- driving controls and derived speeds ---- */
#define CAR_WHEELS_DOWN 0xf0   /* int32: number of wheels touching the ground this step (0..4) */
#define CAR_THROTTLE    0xf8   /* int32: throttle; < 0 = brake / reverse, 0 = coast */
#define CAR_STEER       0xfc   /* int32: steering angle (4096 = 360 deg), added to the heading for the front wheels */
#define CAR_HEADING     0x100  /* int32: heading 0..0xfff (4096 = 360 deg) */
#define CAR_HANDBRAKE   0x104  /* int32: handbrake on: locks the rear wheels and cuts positive throttle */
#define CAR_BURNOUT     0x108  /* int32: burnout in progress.  Set by P107_CarInput (004ddaca) while the
                                  Burn Out control (pad bit 0x40, key cfg 10, lang.eng "Burn Out") is held without the
                                  handbrake; cleared when the forward speed passes 0xa2000 (gas is then forced on) or by the
                                  handbrake.  While set: throttle forced to 0x1b58 / 0x36b0, +600 front grip, gearbox frozen
                                  (ported100), wheel spin / skid sound / wheel dust (ported119/121/127).  RE_PROBE run with
                                  the key held: 0 -> 1 on the press at standstill.  Named CAR_F108 before. */
#define CAR_FWD_SPEED   0x10c  /* int32: signed forward speed, 20.12 (velocity projected on the heading) */
#define CAR_SPEED       0x110  /* int32: speed magnitude, octagonal approximation max(|vx|,|vz|) + min/2 */
#define CAR_SLIP_FRONT  0x114  /* int32: largest lateral slip of the front wheels this step */
#define CAR_SLIP_REAR   0x118  /* int32: largest lateral slip of the rear wheels this step */
#define CAR_DAMAGE      0x11c  /* int32[6]: damage per body zone, 0..0xfff each */
#define CAR_DAMAGE_N    6
#define CAR_DAMAGE_SUM  0x138  /* int32: accumulated hit damage: P100_CarHit adds force / 2 of every hit (it is NOT the
                                  sum of the six zones and has no cap).  Readers: Get138/Get138Entry148, P105_StuntHints
                                  ("damage" >> 3), P75_CarSound (>> 3 changed = new damage).  RE_PROBE run: changes only on
                                  collisions (never on map-cell changes) and differs from the zone sum. */
#define CAR_OVERLAP     0x13c  /* int16: set by P103_CarsOverlap when the car's bounding box overlaps another car (or forced
                                  during chases): the car then takes the sub-stepped collision path of P142_CarsStep.
                                  Cleared at the end of every wheel-physics step. */
#define CAR_DAMAGED     0x13f  /* u8: damaged by a collision this step; queues the damage-model update (004c1f9b) */
#define CAR_AI_DRIVEN   0x13e  /* u8: 1 while the cop AI steers this car (004a7fec); the wheel physics then drives the
                                  front wheels too and scales grip by difficulty.  TODO(RE): exact original meaning */
#define CAR_STEER_HOLD  0x140  /* int8: steering-hold counter: +1 per control tick while a steer key / stick is held,
                                  0 when released, capped at 0x5a (ported107).  P142_WheelPhys adds counter * 0x16 (max 0x1a)
                                  to the front grip of the driven car and sets it to -1 (0xff) when the rear lateral force
                                  opposes the steering (counter-steer).  RE_PROBE run: 1 on the first steering tick.
                                  Named CAR_F140 before. */
#define CAR_STEER_DIR   0x141  /* int8: steering key direction of this tick: +1 for pad bit 8, -1 (0xff) for pad bit 4,
                                  0 for none (ported107); P142_WheelPhys compares it with the rear lateral force sign.
                                  RE_PROBE run: keys 0x6 (gas + bit 4) -> -1 with CAR_STEER > 0.  Named CAR_F141 before. */
#define CAR_GEAR        0x142  /* u8: gear 0..3 (p99_car_t.gear) */
