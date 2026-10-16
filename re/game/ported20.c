#include "ported20.h"
#include <string.h>
#ifndef RE_HOOK_BUILD
/* v2.04: P20_Values — макрос над P79_ModelTab (ported20.h) */
#endif
GAME_VAR_DEF(char*, P20_Names, 0x00b31ed8)
#ifndef RE_HOOK_BUILD /* gvar-img */
#pragma push_macro("P20_Count")
#undef P20_Count
#pragma push_macro("P20_Count") /*gvi*/
#undef P20_Count /*gvi*/
int32_t P20_Count;
#pragma pop_macro("P20_Count") /*gvi*/
#pragma pop_macro("P20_Count")
#endif

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
#ifndef RE_HOOK_BUILD
    if (strcmp(p, s) == 0) return i < 1126 ? P20_Values[i] : 0;   /* native: таблица 00cfe7a0 — 1126 слов */
#else
    if (strcmp(p, s) == 0) return P20_Values[i];
#endif
    p += strlen(p) + 1;
  }
  return 0;
}
