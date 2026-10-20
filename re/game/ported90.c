/* Рисование однозаписной модели блока карты — восстановлено из Game.exe (0042a423). */
#include "ported90.h"
#include "ported8.h"
#include "ported85.h"
#include <string.h>
#ifndef RE_HOOK_BUILD
#include "../platform/native/diagnostics.h"
#endif

/* P90_DrawSingle — Game.exe 0042a423, cdecl.  Short form of the block-model renderer 00429143 for map models
   that consist of a single record (flat pieces of ground / road; 004ee4b7 calls it when the model has
   flags 0x2400 without 0x4000 and +0x16 == 1).
   In:  m    — model offset in the level model area (P79_PTR);
        idx  — orientation index into P56_EulerTab (0x40-byte matrices) and the matrix cache P84_MatCache;
        pos  — world position (x, y, z) used as the transform bias;
        mode — low byte selects the record handler table: 0 -> P84_Tab0, 1 -> P84_Tab1, else P84_Tab2.
   Steps: light spheres touching the model (P63_SphereHits) or none; light from above for plane 0 (P81_PosY);
   view x EulerTab[idx] matrix, recomputed only when P84_MatFlag[idx] != P47_SwapCnt (once per frame);
   in mirror mode (P84_Mirror) a copy with column 0 negated and the bias x negated;
   then the handler for the type of the first record (+0x2c) is called with argument 0 (no plane culling).
   Side effects: P44_MatPtr, P44_Bias*, P84_VertRef/Planes, G2_011F4064, P44_XformTag++. */
/* 0042a423 */
void P90_DrawSingle(uint32_t m, int32_t idx, float *pos, int32_t mode) {
  uint8_t *mdl = (uint8_t *)P79_PTR(m);   /* model header: +0x20 vertices, +0x24 planes, +0x2c record list */
#ifndef RE_HOOK_BUILD
  re_diag_model(m);
#endif
  static float local[16];   /* зеркальная копия: в оригинале на стеке, указатель на неё остаётся в P44_MatPtr */
  if (G2_011F43B0 == 0) P63_SphN = 0;
  else P63_SphereHits(pos, (const uint8_t *)mdl);
  P84_LightIn[0] = P81_PosY;
  P44_BiasX = P84_Mirror ? -pos[0] : pos[0];
  P44_BiasY = pos[1];
  P44_BiasZ = pos[2];
  P84_VertRef = *(uint32_t *)(mdl + 0x20);
  P84_Planes = (float *)P79_PTR(*(uint32_t *)(mdl + 0x24));
  float *mat = P84_MatCache[idx];
  if (P84_MatFlag[idx] != (int32_t)P47_SwapCnt) {
    Mat3Mul_0052859A(P44_ViewMat, (const float *)(P56_EulerTab + (size_t)idx * 0x40), mat);
    P84_MatFlag[idx] = (int32_t)P47_SwapCnt;
  }
  P44_MatPtr = mat;
  if (P84_Mirror) {
    memcpy(local, mat, sizeof(local));
    local[0] = -local[0]; local[3] = -local[3]; local[6] = -local[6];
    P44_MatPtr = local;
  }
  G2_011F4064 = (uint8_t *)P79_PTR(*(uint32_t *)(mdl + 0x2c));
  uint32_t type = G2_011F4064[0];
  uint8_t md = (uint8_t)mode;
  const uintptr_t *tab = md == 0 ? P84_Tab0 : md == 1 ? P84_Tab1 : P84_Tab2;
  uintptr_t f = (tab && type < 56) ? tab[type] : 0;   /* type < 56 — охранная проверка (таблицы по 56 указателей), в оригинале её нет */
#ifndef RE_HOOK_BUILD
  re_diag_record(P79_OFF(G2_011F4064), type, !f || f == (uintptr_t)P85_SkipRecord);
#endif
  if (f) ((p84_handler_t)f)(0);
#ifndef RE_HOOK_BUILD
  re_diag_model(UINT32_MAX);
#endif
  P44_XformTag++;
}
