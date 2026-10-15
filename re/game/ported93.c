/* Поиск значка по имени — восстановлено из Game.exe (004ec91e). */
#include "ported93.h"
#include <string.h>

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
