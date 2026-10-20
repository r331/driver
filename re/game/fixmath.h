/* fixmath.h — named constants for the fixed-point and angle conventions of Game.exe.
 *
 * Driver (PC, 1999) keeps most of its game-logic math in the integer format inherited from the
 * PlayStation version:
 *
 *   - Fixed point "20.12": a value v stands for v / 4096.  1.0 == FX_ONE (0x1000).
 *     A product of two 20.12 numbers is rescaled with "(a * b + FX_HALF) >> FX_SHIFT"
 *     (round to nearest), or with a plain ">> FX_SHIFT" (truncate toward -inf) — the original code
 *     uses both, and the ported code must keep whichever one it found.
 *   - Angles: a full turn is ANG_FULL (4096 == 360 degrees), ANG_90 == 1024, ANG_180 == 2048.
 *     Angles index the sine table P59_Sin (Game.exe 00576f10, 4096 entries, 20.12 values) after
 *     masking with ANG_MASK; cos(a) is read as sin(a + ANG_90).
 *   - Orientation matrices in car records are int16 3x3 in 20.12 (cartab.h: p99_car_t.mat).
 *
 * These macros only name the numbers: replacing a literal 0x1000 / 0x800 / 0xfff by them never
 * changes the generated code.  Use them only where the literal really is the fixed-point one or an
 * angle (0x1000 is also used as a plain count/size in places). */
#pragma once

#define FX_SHIFT   12              /* 20.12 fixed point: fractional bits */
#define FX_ONE     0x1000          /* 1.0 in 20.12 */
#define FX_HALF    0x800           /* 0.5 in 20.12 (rounding term before >> FX_SHIFT) */

#define ANG_FULL   0x1000          /* 360 degrees */
#define ANG_MASK   0xfff           /* wrap an angle to [0, 360) */
#define ANG_90     0x400           /* 90 degrees: sin(a + ANG_90) == cos(a) */
#define ANG_180    0x800           /* 180 degrees */
