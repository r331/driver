/* fpucw.c — state of the emulated x87 control word (see fpucw.h).  Native build only uses it; the hook build
   loads the real control word in InitFpuCw_005283E2 / P18_ClearFlag / NoopFn00528455. */
#include <stdlib.h>
#include "fpucw.h"

int re_fpu_chop;
void re_fpu_load_cw(int chop) {
  static int allow = -1;
  if (allow < 0) { const char *e = getenv("RE_FPU_CHOP"); allow = !(e && e[0] == '0'); }   /* RE_FPU_CHOP=0: debug, always nearest */
  re_fpu_chop = chop && allow;
}
