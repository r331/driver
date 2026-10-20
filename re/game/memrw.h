/* Общие мелкие помощники перенесённого кода: чтение/запись полей структур Game.exe по смещению
   (невыровненно, через memcpy — без нарушения strict aliasing) и целочисленные операции x87/MSVC.
   Раньше каждый ported*.c держал свою копию; здесь — один экземпляр. Поведение не изменилось:
   те же memcpy/lrintf, что и в копиях. Варианты с другой сигнатурой (rd16 со знаком/без, rd32(p, o))
   остаются локальными в своих файлах. */
#pragma once
#include <stdint.h>
#include <string.h>
#include <math.h>

static inline int32_t rd32(const void *p) { int32_t v; memcpy(&v, p, 4); return v; }
static inline void    wr32(void *p, int32_t v) { memcpy(p, &v, 4); }
static inline float   rdf(const void *p) { float v; memcpy(&v, p, 4); return v; }
static inline int32_t iabs(int32_t v) { return v < 0 ? -v : v; }
static inline int32_t fround(float v) { return (int32_t)lrintf(v); }   /* fistp (округление к ближайшему, как FPU по умолчанию) */
