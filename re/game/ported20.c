#include "ported20.h"
#include <string.h>
#ifndef RE_HOOK_BUILD
int32_t P20_Values[4096];
#endif
GAME_VAR_DEF(char*, P20_Names, 0x00b31ed8)
GAME_VAR_DEF(int32_t, P20_Count, 0x00cf2f8c)

static int ci_eq(const char* a, const char* b) {
  for (;; a++, b++) {
    char x = *a, y = *b;
    if (x >= 'A' && x <= 'Z') x += 32;
    if (y >= 'A' && y <= 'Z') y += 32;
    if (x != y) return 0;
    if (!x) return 1;
  }
}
int32_t P20_FindNameNoCase(const char* s) {
  if (!P20_Names) return -1;
  const char* p = P20_Names;
  for (int i = 0; i < P20_Count; i++) {
    if (ci_eq(p, s)) return i;
    p += strlen(p) + 1;
  }
  return -1;
}
int32_t P20_FindNameValue(const char* s) {
  if (!P20_Names) return 0;
  const char* p = P20_Names;
  for (int i = 0; i < P20_Count; i++) {
    if (strcmp(p, s) == 0) return P20_Values[i];
    p += strlen(p) + 1;
  }
  return 0;
}
