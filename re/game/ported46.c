/* ported46 — texture-node dispatchers, widget bounds, per-object wheel physics pass and map.c block loaders
   (all cdecl, restored from Game.exe).  Original note: */
/* Диспетчеры текстур, границы, загрузка блоков карты — восстановлено из Game.exe (cdecl). */
#include "ported112.h"
#include "ported142.h"
#include "ported46.h"
#include "ported41.h"
#include "ported58.h"
#include "engine.h"
#include "flush.h"
#include <string.h>
GAME_VAR_DEF(P46_TexNode *, P46_TexHead, 0x00a42180)
GAME_VAR_DEF(void *, P46_MapBufA, 0x00b31ee4)
GAME_VAR_DEF(void *, P46_MapBufB, 0x00b5a90c)
#ifdef RE_HOOK_BUILD   /* v2.35: native — a view of P58_BlkBuf (ported46.h) */
GAME_VAR_DEF(void *, P46_MapBufC, 0x00bdfbc4)
#endif

/* Texture-node kind handled directly by P46_TexCall2 (field +0xc of the download descriptor). */
#define TEXDESC_KIND      0xc
#define TEXDESC_ARG       0x10
#define TEXKIND_NODE      5      /* TODO(RE): unsure what kind 5 means; it is routed to the node action 0042282f */

/* P46_FindTexNode — Game.exe 00422444.  Looks up the texture node with the given handle in the list
   P46_TexHead (only when node lists are enabled, G6_00A421F0 != 0).
   Out: *out = the node.  Returns 1 if found, 0 otherwise (also 0 when lists are disabled). */
int32_t P46_FindTexNode(int32_t handle, P46_TexNode **out) {
  if (G6_00A421F0 == 0) return 0;
  for (P46_TexNode *n = P46_TexHead; n != NULL; n = n->next)
    if (n->handle == handle) { *out = n; return 1; }
  return 0;
}
/* P46_TexCall — Game.exe 0041d89c.  Flushes pending render batches, then applies action 004228eb
   (P46_Fn4228EB) with arg to the texture node of handle, if one exists. */
void P46_TexCall(int32_t handle, int32_t arg) {
  P46_TexNode *n;
  P33_FlushBatches();
  if (P46_FindTexNode(handle, &n)) P46_Fn4228EB(n, arg);
}
/* P46_TexCall2 — Game.exe 0041d5e7.  Texture download dispatcher.  Flushes batches; if the descriptor d is
   of kind 5 (d+0xc) and a node exists for handle, calls 0042282f (P46_Fn42282F) with d+0x10; otherwise falls
   through to the normal texture download P112_TexDownload(a, b, c, d) (0041f4a1). */
void P46_TexCall2(int32_t a, int32_t b, int32_t c, const uint8_t *d, int32_t handle) {
  P46_TexNode *n;
  int32_t kind, arg;
  P33_FlushBatches();
  memcpy(&kind, d + TEXDESC_KIND, 4);
  if (kind == TEXKIND_NODE && P46_FindTexNode(handle, &n)) {
    memcpy(&arg, d + TEXDESC_ARG, 4);
    P46_Fn42282F(n, arg);
    return;
  }
  P112_TexDownload(a, (uint32_t)b, c, d);   /* 0041f4a1 */
}
/* P46_SetBounds — Game.exe 004d614a.  When slot 0xf is free (IsSlotActive00524473(0xf) == 0), stores the four
   bounds a, b, c, d (TODO(RE): unsure — probably left/top/right/bottom) into A_00B20330[0..15], clears
   G8_00B20344 and calls 004d6354. */
void P46_SetBounds(int32_t a, int32_t b, int32_t c, int32_t d) {
  if (IsSlotActive00524473(0xf) == 0) {
    memcpy(&A_00B20330[0], &a, 4); memcpy(&A_00B20330[4], &b, 4);
    memcpy(&A_00B20330[8], &c, 4); memcpy(&A_00B20330[12], &d, 4);
    G8_00B20344 = 0;
    P46_Fn4D6354();
  }
}
/* P46_UpdateObjects — Game.exe 004defd1.  Runs the wheel physics (P142_WheelPhys, 004df024) for every object
   in the list G6_00B2F30C[0 .. G6_00D0DDC0-1]; the second argument is (object byte +3 == 1). */
void P46_UpdateObjects(void) {
  for (int32_t i = 0; i < G6_00D0DDC0; i++) {
    uint8_t *obj = G6_00B2F30C[i];
    P142_WheelPhys(obj, obj[3] == 1);
  }
}
/* P46_LoadMapA — Game.exe 004ec7f4.  Allocates size bytes (debug tag map.c:0x42b) into P46_MapBufA and
   reads them from the open file in chunks.  On allocation failure the buffer stays NULL and nothing is read. */
void P46_LoadMapA(void *file, int32_t size) {
  void *b = DebugMalloc(size, "D:\\Driver\\Game\\map.c", 0x42b);
  P46_MapBufA = b;
  if (b != NULL) P27_ReadChunked(b, size, 1, file);
}
/* P46_LoadMapB — Game.exe 004ec4ce.  Like P46_LoadMapA (tag map.c:0x39f) into P46_MapBufB; then mirrors the
   pointer into 00bdfbc4 (P46_MapBufC / P58_BlkBuf — one native object since v2.35) and
   calls 0051be3c (P46_Fn51BE3C). */
void P46_LoadMapB(void *file, int32_t size) {
  void *b = DebugMalloc(size, "D:\\Driver\\Game\\map.c", 0x39f);
  P46_MapBufB = b;
  if (b != NULL) {
    P27_ReadChunked(b, size, 1, file);
#ifdef RE_HOOK_BUILD
    P46_MapBufC = P46_MapBufB; P58_BlkBuf = (int32_t *)b;   /* тот же адрес 00bdfbc4 */
#else
    P58_BlkBuf = (int32_t *)b;   /* 00bdfbc4: v2.35 — один объект, P46_MapBufC = его представление (ported46.h) */
#endif
    P46_Fn51BE3C();
  }
}
