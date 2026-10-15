/* Диспетчеры текстур, границы, загрузка блоков карты — восстановлено из Game.exe (cdecl). */
#include "ported46.h"
#include "ported41.h"
#include "engine.h"
#include "flush.h"
#include <string.h>
GAME_VAR_DEF(P46_TexNode *, P46_TexHead, 0x00a42180)
GAME_VAR_DEF(uint32_t, P46_MapBufA, 0x00b31ee4)
GAME_VAR_DEF(uint32_t, P46_MapBufB, 0x00b5a90c)
GAME_VAR_DEF(uint32_t, P46_MapBufC, 0x00bdfbc4)

int32_t P46_FindTexNode(int32_t handle, P46_TexNode **out) {
  if (G6_00A421F0 == 0) return 0;
  for (P46_TexNode *n = P46_TexHead; n != NULL; n = n->next)
    if (n->handle == handle) { *out = n; return 1; }
  return 0;
}
void P46_TexCall(int32_t handle, int32_t arg) {
  P46_TexNode *n;
  P33_FlushBatches();
  if (P46_FindTexNode(handle, &n)) P46_Fn4228EB(n, arg);
}
void P46_TexCall2(int32_t a, int32_t b, int32_t c, const uint8_t *d, int32_t handle) {
  P46_TexNode *n;
  int32_t kind, arg;
  P33_FlushBatches();
  memcpy(&kind, d + 0xc, 4);
  if (kind == 5 && P46_FindTexNode(handle, &n)) {
    memcpy(&arg, d + 0x10, 4);
    P46_Fn42282F(n, arg);
    return;
  }
  P46Call0041F4A1(a, b, c, (void *)d);
}
void P46_SetBounds(int32_t a, int32_t b, int32_t c, int32_t d) {
  if (IsSlotActive00524473(0xf) == 0) {
    memcpy(&A_00B20330[0], &a, 4); memcpy(&A_00B20330[4], &b, 4);
    memcpy(&A_00B20330[8], &c, 4); memcpy(&A_00B20330[12], &d, 4);
    G8_00B20344 = 0;
    P46_Fn4D6354();
  }
}
void P46_UpdateObjects(void) {
  for (int32_t i = 0; i < G6_00D0DDC0; i++) {
    uint8_t *o = G6_00B2F30C[i];
    P46_Fn4DF024(o, o[3] == 1);
  }
}
void P46_LoadMapA(void *file, int32_t size) {
  void *b = DebugMalloc(size, "D:\\Driver\\Game\\map.c", 0x42b);
  P46_MapBufA = (uint32_t)(uintptr_t)b;
  if (b != NULL) P27_ReadChunked(b, size, 1, file);
}
void P46_LoadMapB(void *file, int32_t size) {
  void *b = DebugMalloc(size, "D:\\Driver\\Game\\map.c", 0x39f);
  P46_MapBufB = (uint32_t)(uintptr_t)b;
  if (b != NULL) {
    P27_ReadChunked(b, size, 1, file);
    P46_MapBufC = P46_MapBufB;
    P46_Fn51BE3C();
  }
}
