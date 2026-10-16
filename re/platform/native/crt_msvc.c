/* v2.00: CRT Game.exe (MSVC), которого нет в native: srand 0052e180 / rand 0052e190.
   Тот же ЛКГ, что у MSVC (214013, 2531011, 15 бит), — последовательность совпадает с оригиналом при том же зерне. */
#include <stdint.h>
static uint32_t g_holdrand = 1;
void Call0052E180(uint32_t seed) { g_holdrand = seed; }
extern int re_selftest_on;   /* tests/selftest.c: тесты рассчитаны на прежнюю заглушку rand = 0 */
uint32_t N14_Rand(void) {
  if (re_selftest_on) return 0;
  g_holdrand = g_holdrand * 214013u + 2531011u; return (g_holdrand >> 16) & 0x7fffu; }
