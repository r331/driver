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
/* Plain static (not inline), like the per-file copies they replace: GCC -O1 (hook build) then makes the same
   inlining decisions as before, so the objects do not change.  "unused" — a file need not use all of them.
   wr16 takes int32_t and truncates, so int16_t / uint16_t / int32_t callers all store the same low 16 bits.
   RE_MEMRW_LOCAL16: a file that defines it before including memrw.h keeps its own local 16-bit / float-bit
   helpers (ported102/127/133/142/143/144: moving their definitions into the header changes GCC's operand order
   or function layout in the -O1 hook objects — same semantics, different bytes — so they were left as they were). */
#ifndef RE_MEMRW_LOCAL16
#if defined(__GNUC__)
#  define RE_MEMRW_FN static __attribute__((unused))
#else
#  define RE_MEMRW_FN static
#endif
RE_MEMRW_FN uint16_t rdu16(const void *p) { uint16_t v; memcpy(&v, p, 2); return v; }
RE_MEMRW_FN int16_t  rds16(const void *p) { int16_t v; memcpy(&v, p, 2); return v; }
RE_MEMRW_FN void     wr16(void *p, int32_t v) { int16_t s = (int16_t)v; memcpy(p, &s, 2); }
RE_MEMRW_FN void     wrf(void *p, float v) { memcpy(p, &v, 4); }
RE_MEMRW_FN float    u2f(uint32_t u) { float f; memcpy(&f, &u, 4); return f; }   /* bits -> float */
RE_MEMRW_FN uint32_t fbits(float v) { uint32_t u; memcpy(&u, &v, 4); return u; }  /* float -> bits */
RE_MEMRW_FN int32_t  f2i(float v) { int32_t i; memcpy(&i, &v, 4); return i; }    /* float -> bits, signed */
#endif /* RE_MEMRW_LOCAL16 */
