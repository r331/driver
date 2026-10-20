/* Общие мелкие помощники перенесённого кода: чтение/запись полей структур Game.exe по смещению
   (невыровненно, через memcpy — без нарушения strict aliasing) и целочисленные операции x87/MSVC.
   Раньше каждый ported*.c держал свою копию; здесь — один экземпляр. Поведение не изменилось:
   те же memcpy/lrintf, что и в копиях. Варианты с другой сигнатурой (rd32(p, o), wr16(p, o, v) …)
   остаются локальными в своих файлах. cleanup/round2: + rdu16/rds16/wr16/wrf и битовые преобразования
   float <-> int (u2f/fbits/f2i) — бывшие копии rd16/r16/rd16s/w16/rf/wf/bits/F2I в ported*.c. */
/* English: shared helpers for reading/writing fields of Game.exe structures by byte offset.
   rd32/wr32/rdf go through memcpy (unaligned-safe, no strict-aliasing issues); iabs is a plain
   absolute value; fround rounds to nearest like the x87
   "fistp" with the default rounding mode.  rdu16/rds16/wr16 are the 16-bit field accessors (unsigned /
   sign-extended), wrf stores a float; u2f / fbits / f2i reinterpret float bits (no conversion).  Field offsets of the car record have names in
   carfields.h, fixed-point / angle constants in fixmath.h. */
#pragma once
#include <stdint.h>
#include <string.h>
#include <math.h>

static inline int32_t rd32(const void *p) { int32_t v; memcpy(&v, p, 4); return v; }
static inline void    wr32(void *p, int32_t v) { memcpy(p, &v, 4); }
static inline float   rdf(const void *p) { float v; memcpy(&v, p, 4); return v; }
static inline int32_t iabs(int32_t v) { return v < 0 ? -v : v; }
static inline int32_t fround(float v) { return (int32_t)lrintf(v); }   /* fistp (округление к ближайшему, как FPU по умолчанию) */
static inline uint16_t rdu16(const void *p) { uint16_t v; memcpy(&v, p, 2); return v; }
static inline int16_t  rds16(const void *p) { int16_t v; memcpy(&v, p, 2); return v; }
static inline void     wr16(void *p, uint16_t v) { memcpy(p, &v, 2); }
static inline void     wrf(void *p, float v) { memcpy(p, &v, 4); }
static inline float    u2f(uint32_t u) { float f; memcpy(&f, &u, 4); return f; }   /* bits -> float */
static inline uint32_t fbits(float v) { uint32_t u; memcpy(&u, &v, 4); return u; }  /* float -> bits */
static inline int32_t  f2i(float v) { int32_t i; memcpy(&i, &v, 4); return i; }    /* float -> bits, signed */
