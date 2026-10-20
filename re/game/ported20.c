/* ported20.c — lookups in the model name table (English overview; original notes follow).
   P20_Names (00b31ed8) is a block of P20_Count consecutive NUL-terminated names; name i corresponds to
   word i of the model table at 00cfe7a0 (P20_Values, native: P79_ModelTab). */
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

/* ci_eq — local helper: ASCII case-insensitive string equality (only A-Z are folded).  1 = equal. */
static int ci_eq(const char* a, const char* b) {
  for (;; a++, b++) {
    char x = *a, y = *b;
    if (x >= 'A' && x <= 'Z') x += 32;
    if (y >= 'A' && y <= 'Z') y += 32;
    if (x != y) return 0;
    if (!x) return 1;
  }
}
/* P20_FindNameNoCase — Game.exe 004ec837.  Index of name s in the name block, compared case-insensitively;
   -1 if absent or no names are loaded. */
int32_t P20_FindNameNoCase(const char* s) {
  if (!P20_Names) return -1;
  const char* p = P20_Names;
  for (int i = 0; i < P20_Count; i++) {
    if (ci_eq(p, s)) return i;
    p += strlen(p) + 1;
  }
  return -1;
}
/* P20_FindNameValue — Game.exe 004ec8a8.  Looks up s (case-sensitive) and returns the matching word of the
   model table (e.g. a model pointer/handle), or 0 if not found.
   Native deviation: indices >= 1126 (size of the table at 00cfe7a0) return 0 instead of reading past it. */
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
