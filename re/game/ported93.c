/* Sprite/icon lookup by name in the icon directory (P54_MapA entries at P54_MapAPtr). */
/* Поиск значка по имени — восстановлено из Game.exe (004ec91e). */
#include "ported93.h"
#include <string.h>

/* P93_FindIcon — Game.exe 004ec91e, cdecl.  Find an icon record by name.
   In:  name — icon name; only the first 8 characters are compared (records hold an 8-byte,
        not necessarily NUL-terminated name at offset 0).
   Out: pointer to the 16-byte record whose name matches (exactly 8 chars, or the record name ends
        where the given name ends); NULL if the directory is empty, the name is empty or not found. */
uint8_t *P93_FindIcon(const char *name) {
  int32_t n, len, i;
  uint8_t *rec;
  if (P54_MapA == 0) return NULL;
  len = (int32_t)strlen(name);
  if (len == 0) return NULL;
  if (len > 8) len = 8;
  n = P54_MapA;
  rec = (uint8_t *)P54_MapAPtr;
  if (rec == NULL) return NULL;
  for (; n != 0; n--, rec += 0x10) {
    int match = 1;
    for (i = 0; i < len; i++) {
      if (name[i] != (char)rec[i]) { match = 0; break; }
    }
    if (match) {
      if (i == 8) return rec;
      if (rec[i] == 0) return rec;
    }
  }
  return NULL;
}
